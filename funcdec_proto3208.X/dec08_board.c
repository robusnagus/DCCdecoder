//
// Project: DCC decoder proto M3208
// File:    dec08_board.c
// Author:  Nagus
// Version: 20191228
//

#include "dec08_board.h"

FUSES = {
	.APPEND  = 0,
	.BODCFG  = ACTIVE_DIS_gc | LVL_BODLEVEL0_gc | SAMPFREQ_1KHZ_gc | SLEEP_DIS_gc,
	.BOOTEND = 0,
	.OSCCFG  = FREQSEL_20MHZ_gc,
	.SYSCFG0 = CRCSRC_NOCRC_gc | RSTPINCFG_RST_gc,
	.SYSCFG1 = SUT_64MS_gc,
	.WDTCFG  = PERIOD_OFF_gc | WINDOW_OFF_gc,
}; // FUSES

// obsługa portu szeregowego
uint8_t serRxBuf[SER_RX_DATASIZE];
uint8_t serRxPos;
uint8_t serTxBuf[SER_TX_DATASIZE];
uint8_t serTxHead;
uint8_t serTxTail;

void SERIAL_Initialize(void)
{
	serRxPos = 0;
    serTxHead = 0;
    serTxTail = 0;
}

uint8_t SERIAL_SendByte(uint8_t data)
{
	if (serTxHead == serTxTail) {
        if (BOARD_SERIAL_IsTXEmpty()) {
            BOARD_SERIAL_PutByte(data);
            return 0;
        }
    }

    BOARD_SERIAL_TXStart();
    uint16_t inext = serTxTail + 1;
    if (inext == SER_TX_DATASIZE)
        inext = 0;
    if (inext == serTxHead)
        return 1;
    serTxBuf[serTxTail] = data;
    serTxTail = inext;
	return 0;

} // SERIAL_SendByte

uint8_t SERIAL_SendString(char* data)
{
	BOARD_SERIAL_TXStop();
    uint16_t inext;
    while (*data) {
        inext = serTxTail + 1;
        if (inext == SER_TX_DATASIZE)
            inext = 0;
        if (inext == serTxHead) {
            BOARD_SERIAL_TXStart();
            return 1;
        }
        else {
            serTxBuf[serTxTail] = *(data++);
            serTxTail = inext;
        }
    }

    if (BOARD_SERIAL_IsTXEmpty()) {
        BOARD_SERIAL_PutByte(serTxBuf[serTxHead]);
        serTxHead++;
        if (serTxHead == SER_TX_DATASIZE)
            serTxHead = 0;
    }
    BOARD_SERIAL_TXStart();
	return 0;

} // SERIAL_SendString

BOARD_SERIAL_RXHandler()
{
    uint8_t ch;
    if (BOARD_SERIAL_IsRXPend()) {
        ch = BOARD_SERIAL_GetByte();
        if (serRxPos == 0) {
            if (ch == '~') {
                // początek datagramu
                serRxBuf[serRxPos++] = ch;
            }
        }
        else {
            serRxBuf[serRxPos++] = ch;
            if ((ch == '\n') || (serRxPos == SER_RX_DATASIZE)) {
                BOARD_SERIAL_RXStop();
                serRxBuf[serRxPos] = 0;
                SERIAL_ProcessMessage(serRxBuf);
                serRxPos = 0;
                BOARD_SERIAL_RXStart();
            }
        }
    }

} // BOARD_SERIAL_RXHandler

// wysłanie danych przez port szeregowy
BOARD_SERIAL_TXHandler()
{
    if (BOARD_SERIAL_IsTXEmpty()) {
        if (serTxHead != serTxTail) {
            BOARD_SERIAL_PutByte(serTxBuf[serTxHead]);
            serTxHead++;
            if (serTxHead == SER_TX_DATASIZE)
                serTxHead = 0;
        }
        else
            BOARD_SERIAL_TXStop();
    }

} // BOARD_SERIAL_TXHandler

// EOF dec08_board.c
