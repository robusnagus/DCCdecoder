//
// Project: DCC decoder proto M3208
// File:    dec08_app.c
// Author:  Nagus
// Version: 20200118
//

#include "dec08_board.h"
#include "dec08_cvman.h"

extern uint32_t SYS_GetTick(void);

#define FUNC_STATE_INIT         0x00
#define FUNC_STATE_REV          0x80
#define FUNC_STATE_FL           0x10
#define FUNC_STATE_AU1          0x08
#define FUNC_STATE_AU2          0x04
#define FUNC_STATE_AU3          0x02
#define FUNC_STATE_AU4          0x01

uint8_t dccIdle;
char dccOutBuf[24];
extern uint8_t dccPacket[CFG_DCCR_PKTMAXLEN];
extern uint8_t dccPktBuf[CFG_DCCR_PKTMAXLEN];
extern uint8_t dccPktLen;

uint8_t funcState;

void APP_Initialize(void);
void APP_Tasks(void);
void APP_UpdateOutput(void);
void APP_UpdateFuncOut(void);
void APP_UpdateFrontL(void);
void APP_SetAck(void);
void APP_UpdateFuncFL(uint8_t value);
void APP_UpdateFuncG1(uint8_t value);
uint8_t APP_CheckPacket(void);
extern void DCC_DecoderInit(void);
extern void DCC_DecodePacket(void);

void SERIAL_ProcessMessage(uint8_t *message)
{
}

uint8_t APP_CheckPacket(void)
{
    uint8_t idx;
    uint8_t tmp;
    uint8_t sum = 0;
    char* pOutStr = dccOutBuf;    
    
    for (idx = 0; idx < dccPktLen; idx++) {
        tmp = dccPktBuf[idx];
        dccPacket[idx] = tmp;
        sum = sum ^ tmp;
        tmp = (dccPktBuf[idx] & 0xF0) >> 4;
        if (tmp > 9)
            *(pOutStr++) = tmp + 0x37; else *(pOutStr++) = tmp + 0x30;
        tmp = dccPktBuf[idx] & 0x0F;
        if (tmp > 9)
            *(pOutStr++) = tmp + 0x37; else *(pOutStr++) = tmp + 0x30;
        *(pOutStr++) = ' ';
    }
    dccPktLen = 0;
    if (sum)
        *(pOutStr++) = 'W';
    *(pOutStr++) = '\r';
    *(pOutStr++) = '\n';
    *pOutStr = 0;
    SERIAL_SendString(dccOutBuf);
    
    return sum;    
    
} // DCC_ProcessPacket

void APP_UpdateFrontL(void)
{
    if (funcState & FUNC_STATE_REV) {
        BOARD_AUXFL_Off();
        BOARD_AUXRL_On();
    }
    else {
        BOARD_AUXFL_On();
        BOARD_AUXRL_Off();
    }
    
} // APP_UpdateFrontL

void APP_UpdateFuncOut(void)
{     
    if (funcState & FUNC_STATE_AU1) {
        BOARD_PWM0_SetDutyCycle(CV_GetValue(CV047_DimComp));
        BOARD_AUX01_On();
    }
    else
        BOARD_AUX01_Off();
    
    if (funcState & FUNC_STATE_AU2) {
        BOARD_PWM1_SetDutyCycle(CV_GetValue(CV048_DimAisle));
        BOARD_AUX02_On();
    }
    else
        BOARD_AUX02_Off();
    
    if (funcState & FUNC_STATE_AU3) {
        BOARD_PWM3_SetDutyCycle(CV_GetValue(CV049_DimToil));
        BOARD_AUX03_On();
    }
    else
        BOARD_AUX03_Off();
    
    if (funcState & FUNC_STATE_AU4) {
        BOARD_PWM4_SetDutyCycle(CV_GetValue(CV050_DimTrEnd));
        BOARD_AUX04_On();
    }
    else
        BOARD_AUX04_Off();
    
} // APP_UpdateFuncOut

void APP_SetAck(void)
{
    static uint32_t ackTout;
    
    BOARD_OUTACK_On();
    ackTout = SYS_GetTick() + 6;
    SERIAL_SendString("ACK\r\n");
    do {}
    while (ackTout > SYS_GetTick());
    BOARD_OUTACK_Off();
    
} // APP_SetAck

void APP_UpdateFuncG1(uint8_t value)
{
    funcState = (funcState & 0xE0) | value;
    APP_UpdateFuncOut();
}

void APP_UpdateFuncFL(uint8_t value)
{
    if (value & 0x80)
        funcState = funcState & ~FUNC_STATE_REV;
    else
        funcState |= FUNC_STATE_REV;
    APP_UpdateFrontL();
    
} // APP_UpdateFuncFL

void APP_UpdateOutput(void)
{
	static uint16_t blinkHB = 0;
    blinkHB++;
    if (blinkHB == 1) {
        BOARD_LEDHB_On();
    }
    else if (blinkHB == 500) {
        BOARD_LEDHB_Off();
    }
    else if (blinkHB > 1000) {
        blinkHB = 0;
    }
    
    static uint16_t dimTest = 0;
    static uint8_t  dimVal = 0x10;
    dimTest++;
    if (dimTest > 250) {
        dimVal += 0x10;
        BOARD_PWM3_SetDutyCycle(dimVal);
        dimTest = 0;
    }
    
} // APP_UpdateOutput

extern void DCCREC_Init(void);

void APP_Initialize(void)
{
	dccIdle = 0;
    funcState = FUNC_STATE_INIT;
    
    dccPktLen = 0;
    DCCREC_Init();
    DCC_DecoderInit();
    
    SERIAL_Initialize();  
    SERIAL_SendString("DCCdec08 v.200118.8\r\n");
    
} // APP_Initialize

void APP_Tasks(void)
{
    static uint32_t lastTick = 0;

    if (lastTick != SYS_GetTick()) {
        // operacje aktualizowane z upływem czasu
        APP_UpdateOutput();

        lastTick = SYS_GetTick();
    }

    if (dccPktLen) {
        if ((dccPktBuf[0] == 0xFF) && (dccPktBuf[1] == 0x00)) {
            if (dccIdle == 0) {
                SERIAL_SendString("IDLE\r\n");
                dccIdle = 1;
            }
            dccPktLen = 0;
            return;
        }
        dccIdle = 0;
        
        if (APP_CheckPacket() == 0) {
            DCC_DecodePacket();
        }   
    }
    
} // APP_Tasks

// EOF dec08_app.c
