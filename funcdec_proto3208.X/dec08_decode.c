//
// Project: DCC decoder proto M3208
// File:    dec08_decode.c
// Author:  Nagus
// Version: 20200323
//

#include <stdio.h>
#include <string.h>

#include "dec08_board.h"
#include "dec08_cvman.h"

#define DCC_TYPE_MASK           0xE0
#define DCC_TYPE_ADVOPER        0x20
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

uint8_t decAddr;
uint8_t decAddrH;
uint8_t decAddrL;
uint8_t decConf;
uint8_t decState;

uint8_t cvWrPkt[3];
uint8_t cvWrCnt;

extern char logStr[128];

void DCC_DecoderInit(void);
void DCC_DecodePacket(void);
void DCC_AdvOperation(uint8_t idx);
void DCC_LongService(uint8_t idx);
extern void APP_Initialize(void);
extern void APP_SetAck(void);
extern void APP_UpdateFuncFL(uint8_t value);
extern void APP_UpdateFuncG1(uint8_t value);

void DCC_AdvOperation(uint8_t idx)
{
    uint8_t arg = dccPacket[idx + 1]; 
    switch (dccPacket[idx] & DCC_AOPER_MASK) {
        case DCC_AOPER_128SPD:
            APP_UpdateFuncFL(arg & 0x80);
            break;
        default:
            break;
    } // switch DCC_AOPER_MASK
    
} // DCC_AdvOperation

void DCC_LongService(uint8_t idx)
{
    //sprintf(logStr, "LongService %d\r\n", idx);
    //SERIAL_SendString(logStr);
    uint8_t dat = dccPacket[idx + 2];
    uint8_t cvv;
    switch (dccPacket[idx] & 0x0C) {
        case DCC_CVOP_BYTEVERIFY:
            cvv = CV_GetValue(dccPacket[idx + 1]);
            sprintf(logStr, "Byte verify, cvv: %02X from %02X\r\n", 
                    cvv, dccPacket[idx + 1]);
            SERIAL_SendString(logStr);
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
            sprintf(logStr, "Bit manip, cvv: %02X from %02X\r\n", 
                    cvv, dccPacket[idx + 1]);
            SERIAL_SendString(logStr);
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
                sprintf(logStr, "Bit dat: %02X\r\n", dat);
                SERIAL_SendString(logStr);
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
            sprintf(logStr, "Wrong oper: %02X\r\n", dccPacket[idx]);
            SERIAL_SendString(logStr);
            break;
    } // switch CV_OP
    
} // DCC_LongService

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
        case DCC_TYPE_FUNCTION1:
            APP_UpdateFuncG1(dccPacket[idx] & 0x1F);
            break;
        case DCC_TYPE_CONFVAR:
            //if ((dccPacket[idx] & 0x10) == 0)
                DCC_LongService(idx);
            break;
        default:
            sprintf(logStr, "Invalid DCC type: %02X", dccPacket[idx]);
            SERIAL_SendString(logStr);        
            break;
    } // switch DCC_TYPE_MASK
    
} // DCC_DecodePacket

void DCC_DecoderInit(void)
{  
    SERIAL_SendString("Decoder init\r\n");
    decAddr  = CV_GetValue(CV001_DecAddr);
    if (decAddr == 0xFF) {
        CV_RestoreDefault();
    }
    else {
        decAddrH = CV_GetValue(CV017_DecAddrH);
        decAddrL = CV_GetValue(CV018_DecAddrL);
        decConf  = CV_GetValue(CV029_Config);
        BOARD_PWM0_SetDutyCycle(CV_GetValue(CV047_DimComp));
        BOARD_PWM1_SetDutyCycle(CV_GetValue(CV048_DimAisle)); 
        //BOARD_PWM3_SetDutyCycle(CV_GetValue(CV049_DimToil));
        BOARD_PWM4_SetDutyCycle(CV_GetValue(CV050_DimTrEnd));        
    }
   
} // DCC_DecoderInit

// EOF dec08_decode.c
