//
// DCC function decoder
//
// Copyright 2020 Robert Nagowski
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// See gpl-3.0.md file for details.
//

#include <avr/eeprom.h>

#include "funcdec_board.h"
#include "funcdec_cvlist.h"

#define DECCFG_DIRREV           0x01
#define DECCFG_FLFUNCG          0x02
#define DECCFG_BIDICOM          0x08
#define DECCFG_LONGADDR         0x20
#define DECCFG_MASK             0x2B

#define DCC_TYPE_MASK           0xE0
#define DCC_TYPE_ADVOPER        0x20
#define DCC_TYPE_REVSPEED       0x40
#define DCC_TYPE_FWDSPEED       0x60
#define DCC_TYPE_FUNCTION1      0x80
#define DCC_TYPE_FUNCTION2      0xA0
#define DCC_TYPE_CONFVAR        0xE0       

#define DCC_AOPER_MASK          0x1F
#define DCC_AOPER_128SPD        0x1F

#define DCC_CVOP_BYTEVERIFY     0x04
#define DCC_CVOP_BYTEWRITE      0x0C
#define DCC_CVOP_BITMANIP       0x08

#define DEC_STAT_RESETD         0x01
#define DEC_STAT_SERVICE        0x80
#define DEC_STAT_RUNNING        0x00

uint8_t dccPacket[CFG_DCCR_PKTMAXLEN];
extern uint8_t dccPktBuf[CFG_DCCR_PKTMAXLEN];
extern uint8_t dccPktLen;

// podręczne dane
uint8_t decAddr;        // krótki adres
uint8_t decAddrH;       // długi adres
uint8_t decAddrL;
uint8_t decConf;        // konfiguracja
uint8_t decState;       // stan dekodera

uint8_t cvWrPkt[3];
uint8_t cvWrCnt;

uint8_t decConfig[CFG_DCCD_CVMAX] EEMEM;

uint8_t        CV_GetValue(uint8_t cv);
void           CV_SetValue(uint8_t cv, uint8_t value);
extern void    CV_RestoreDefault(uint8_t *config);
extern uint8_t CV_validate(uint8_t cv, uint8_t value);

uint8_t DCC_CheckPacket(void);
void DCC_DecoderInit(void);
void DCC_DecodePacket(void);
void DCC_AdvOperation(uint8_t idx);
void DCC_LongService(uint8_t idx);
void DCC_RestoreDefault(void);

extern void APP_Initialize(void);
extern void APP_SetAck(void);
extern void APP_UpdateFuncDir(uint8_t value);
extern void APP_UpdateFuncG1(uint8_t value);
extern void APP_UpdateFuncG2(uint8_t value);

// pobranie zawartości CV
// cv:    numer cv-1
// zwrot: zawartość CV, 0xFF gdy nie znalezione
uint8_t CV_GetValue(uint8_t cv)
{
    if (cv < CFG_DCCD_CVMAX) {
        eeprom_busy_wait();
        return eeprom_read_byte(&(decConfig[cv]));
    }   
    return 0xFF;
    
} // CV_GetValue

// ustawienie CV
// cv:    numer cv-1
// value: nowa wartość CV
// zwrot: brak
void CV_SetValue(uint8_t cv, uint8_t value)
{
    if (cv >= CFG_DCCD_CVMAX) {
        return;
    }
    
    // parametry standardowe
    if (cv == CV001_DecAddr) {
        if ((value < 1) || (value > 127))
            value = CVDEF_DecAddr;
            decAddr = value;
    } 
    else if (cv == CV007_Version) {
        return;
    }
    else if (cv == CV008_ManfID) {
        if (value == 32)
            DCC_RestoreDefault();
        return;
    }
    else if (cv == CV017_DecAddrH) {
        if ((value < 192) && (value > 232))
            value = CVDEF_DecAddrH;
        decAddrH = value;
    }
    else if (cv == CV018_DecAddrL) {
        decAddrL = value;
    }
    else if (cv == CV029_Config) {
        value = value & DECCFG_MASK;
        decConf = value;
    }
    else {
        value = CV_validate(cv, value);
    }
    
    eeprom_busy_wait();
    eeprom_update_byte(&(decConfig[cv]), value);

} // CV_SetValue

// przywrócenie domyślnej konfiguracji
// param: brak
// zwrot: brak
void DCC_RestoreDefault(void)
{
    CV_RestoreDefault(decConfig);
    
    decAddr  = CVDEF_DecAddr;
    decAddrH = CVDEF_DecAddrH;
    decAddrL = CVDEF_DecAddrL;
    decConf  = CVDEF_Config;
    
} // DCC_RestoreDefault

// sprawdzenie sumy kontrolnej pakietu DCC
// param: brak
// zwrot: 0 gdy OK
uint8_t DCC_CheckPacket(void)
{
    uint8_t idx;
    uint8_t sum = 0;
    for (idx = 0; idx < dccPktLen; idx++) {
        dccPacket[idx] = dccPktBuf[idx];
        sum = sum ^ dccPktBuf[idx];
    }
    return sum;
    
} // DCC_CheckPacket

// pakiet Decoder and CC: Advanced Operations
// idx:   pozycja w pakiecie
// zwrot: brak
void DCC_AdvOperation(uint8_t idx)
{
    uint8_t arg = dccPacket[idx + 1]; 
    switch (dccPacket[idx] & DCC_AOPER_MASK) {
        case DCC_AOPER_128SPD:
            APP_UpdateFuncDir(arg & 0x80);
            break;
        default:
            break;
    } // switch DCC_AOPER_MASK
    
} // DCC_AdvOperation

// przetwarzanie: pakiet serwisowy wersja długa
// idx:   pozycja w pakiecie
// zwrot: brak
void DCC_LongService(uint8_t idx)
{
    uint8_t dat = dccPacket[idx + 2];
    uint8_t cvv;
    switch (dccPacket[idx] & 0x0C) {
        case DCC_CVOP_BYTEVERIFY:
            cvv = CV_GetValue(dccPacket[idx + 1]);
            if (cvv == dat) {
                APP_SetAck();
            }
            cvWrPkt[0] = 0;
            break;
        case DCC_CVOP_BYTEWRITE:
            if ((cvWrPkt[0] == dccPacket[idx]) &&
                (cvWrPkt[1] == dccPacket[idx + 1]) && 
                (cvWrPkt[2] == dccPacket[idx + 2])) {
                cvWrCnt++;
                if (cvWrCnt == 2) {
                    CV_SetValue(dccPacket[idx + 1], dat);
                    APP_SetAck();
                }
            }
            else {
                cvWrPkt[0] = dccPacket[idx];
                cvWrPkt[1] = dccPacket[idx + 1];
                cvWrPkt[2] = dccPacket[idx + 2];
                cvWrCnt = 1;
            }
            break;
        case DCC_CVOP_BITMANIP:
            cvv = CV_GetValue(dccPacket[idx + 1]);
            if (dat & 0x10) {
                // write bit
                if ((cvWrPkt[0] == dccPacket[idx]) &&
                    (cvWrPkt[1] == dccPacket[idx + 1]) &&
                    (cvWrPkt[2] == dccPacket[idx + 2])) {
                    cvWrCnt++;
                    if (cvWrCnt == 2) {
                        if (dat & 0x08)
                            cvv |= (1 << (dat & 0x07));
                        else 
                            cvv &= ~(1 << (dat & 0x07));
                        CV_SetValue(dccPacket[idx + 1], cvv);
                        APP_SetAck();
                    }
                }
                else {
                    cvWrPkt[0] = dccPacket[idx];
                    cvWrPkt[1] = dccPacket[idx + 1];
                    cvWrPkt[2] = dccPacket[idx + 2];
                    cvWrCnt = 1;
                }                
            }
            else {
                // verify bit
                if (dat & 0x08) {
                    // czy bit == 1
                    if ((cvv & (1 << (dat & 0x07))) != 0)
                        APP_SetAck();
                }
                else {
                    // czy bit == 0
                    if ((cvv & (1 << (dat & 0x07))) == 0)
                        APP_SetAck();
                }                    
                cvWrPkt[0] = 0;
            }
            break;
        default:
            break;
    } // switch CV_OP
    
} // DCC_LongService

// przetwarzanie pakietu DCC
// param: brak
// zwrot: brak
void DCC_DecodePacket(void)
{
    uint8_t idx;
    
    if ((dccPacket[0] == 0x00) && (dccPacket[1] == 0x00)) {
        if (decState & DEC_STAT_RESETD)
            // już zresetowany
            return;
        
        decState = DEC_STAT_RESETD;
        APP_Initialize(); 
        return;
    } 
     
    // sprawdzenie adresu
    if ((dccPacket[0] > 111) && (dccPacket[0] < 128)) {
        // pakiet serwisowy
        if (decState == DEC_STAT_RESETD) {
            decState = DEC_STAT_SERVICE;
        }  
        if ((decState & DEC_STAT_SERVICE) != 0) {
            DCC_LongService(0);
        }
        return;
    }
        
    if (decConf & DECCFG_LONGADDR) {
        if ((dccPacket[0] != decAddrH) || (dccPacket[1] != decAddrL))
            return;
        idx = 2;
    }
    else {
        // krótki adres
        if (dccPacket[0] != decAddr)
            return;
        idx = 1;
    }
       
    // zwykły pakiet
    decState = DEC_STAT_RUNNING;
    switch (dccPacket[idx] & DCC_TYPE_MASK) {
        case DCC_TYPE_ADVOPER:
            DCC_AdvOperation(idx);
            break;
        case DCC_TYPE_REVSPEED:
            APP_UpdateFuncDir(0x00);
            break;
        case DCC_TYPE_FWDSPEED:
            APP_UpdateFuncDir(0x80);
            break;
        case DCC_TYPE_FUNCTION1:
            if (decConf & DECCFG_FLFUNCG)
                APP_UpdateFuncG1(dccPacket[idx] & 0x1F);
            else
                APP_UpdateFuncG1(dccPacket[idx] & 0x0F);
            break;
        case DCC_TYPE_FUNCTION2:
            APP_UpdateFuncG2(dccPacket[idx] & 0x1F);
            break;    
        case DCC_TYPE_CONFVAR:
            if ((dccPacket[idx] & 0x10) == 0)
                DCC_LongService(idx);
            break;
        default:   
            break;
    } // switch DCC_TYPE_MASK
    
} // DCC_DecodePacket

// inicjalizacja dekodera DCC
// param: brak
// zwrot: brak
void DCC_DecoderInit(void)
{  
    decAddr  = CV_GetValue(CV001_DecAddr);
    if (decAddr == 0xFF) {       
        DCC_RestoreDefault();
    }
    else {
        decAddrH = CV_GetValue(CV017_DecAddrH);
        decAddrL = CV_GetValue(CV018_DecAddrL);
        decConf  = CV_GetValue(CV029_Config);   
    }
    
} // DCC_DecoderInit

// EOF funcdec_decode.c
