//
// Project: DCC decoder proto M3208
// File:    dec08_recv.c
// Author:  Nagus
// Version: 20200107
//

#include "dec08_board.h"

// stan odbiornika DCC
typedef enum {
    DCCRpreamble,
    DCCRstartbit,
    DCCRdatarecv,
    DCCRstopbit,
} DCCRecState_td; 

uint8_t dccPktBuf[CFG_DCCR_PKTMAXLEN];
uint8_t dccPktLen;

DCCRecState_td dccrecState;     // stan odbiornika DCC
uint8_t dccBitCnt;
uint8_t dccByteCnt;
uint8_t dccBuf;
static uint8_t  dccBit;
static uint16_t dccBitTime;

void DCCREC_Init(void);

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

void DCCREC_Init(void)
{
    dccrecState = DCCRpreamble;
    dccBitCnt = 0;
}

// EOF dec08_recv.c
