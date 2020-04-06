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

#include "funcdec_board.h"

// stan odbiornika DCC
typedef enum {
    DCCRpreamble,
    DCCRstartbit,
    DCCRdatarecv,
    DCCRstopbit,
} DCCRecState_td; 

uint8_t dccPktBuf[CFG_DCCR_PKTMAXLEN];  // bufor pakietu DCC
uint8_t dccPktLen;                      // ilość danych w buforze

DCCRecState_td dccrecState;     // stan odbiornika DCC
uint8_t dccBitCnt;
uint8_t dccByteCnt;
uint8_t dccBuf;
static uint8_t  dccBit;
static uint16_t dccBitTime;

void DCCREC_Init(void);

// odbiornik DCC - obsługa przerwania
BOARD_DCCREC_Handler()
{
    dccBitTime = BOARD_DCCREC_GetBitTime();
    if (dccBitTime < CFG_DCCR_ONEBTIME) {
        dccBit = 1;
    }   
    else {
        dccBit = 0;
    }
        
    switch (dccrecState) {
        case DCCRpreamble:
            // odbiór preambuły
            if (dccBit) {
                dccBitCnt++;
                if (dccBitCnt > CFG_DCCR_PREAMBMIN) {
                    dccrecState = DCCRstartbit;
                }
            }
            else {
                // nie preambuła, czekaj od nowa
                dccBitCnt = 0;
            }
            break;
        case DCCRstartbit:
            // bit startu
            if (dccBit) {
                // jeszcze preambuła
                dccBitCnt++;
            }
            else {
                if (dccPktLen) {
                    // problem: poprzedni pakiet nie odebrany
                    dccBitCnt = 0;
                    dccrecState = DCCRpreamble;
                }
                else {
                    // początek pakietu
                dccBitCnt = 0;
                dccByteCnt = 0;
                dccBuf = 0;
                dccrecState = DCCRdatarecv;
                } 
            }
            break;
        case DCCRdatarecv:
            // odbiór danych
            dccBuf = (dccBuf << 1) | dccBit;
            if (dccBitCnt < 7) {
                // oczekiwanie na kolejny bit
                dccBitCnt++;
            }
            else {
                // kompletny oktet
                dccPktBuf[dccByteCnt] = dccBuf;
                dccrecState = DCCRstopbit;
            }
            break;
        case DCCRstopbit:
            // bit stopu
            dccByteCnt++;
            if (dccBit) {
                // koniec pakietu
                dccPktLen = dccByteCnt;
                dccBitCnt = 1;
                dccrecState = DCCRpreamble;
            }
            else {
                // koniec oktetu
                dccBitCnt = 0;
                dccBuf = 0;
                dccrecState = DCCRdatarecv;
            }
            break;
        default: 
            // błąd - nowy początek
            dccrecState = DCCRpreamble;
            dccBitCnt = 0;
            break;
    } // switch dccrecState
    
} // BOARD_DCCREC_Handler       

// inicjalizacja odbiornika DCC
// param: brak
// zwrot: brak
void DCCREC_Init(void)
{
    dccrecState = DCCRpreamble;
    dccBitCnt = 0;
}

// EOF funcdec_recv.c
