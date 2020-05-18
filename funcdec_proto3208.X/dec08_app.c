//
// DCC function decoder prototype
//
// Copyright 2020 Robert Nagowski
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// See gpl-3.0.md file for details.
//

#include "dec08_board.h"
#include "dec08_cvman.h"

extern uint32_t SYS_GetTick(void);

#define FUNC_STATE_INIT         0x00
#define FUNC_STATE_REV          0x80

#define LOGI_DCC_ALL            0x80
#define LOGI_DCC_ONCE           0x01
#define LOGI_DCC_NONE           0x00

uint8_t dccFilter;
uint8_t dccIdle;
char dccOutBuf[24];
extern uint8_t dccPacket[CFG_DCCR_PKTMAXLEN];
extern uint8_t dccPktBuf[CFG_DCCR_PKTMAXLEN];
extern uint8_t dccPktLen;

uint8_t statFunc;       // b7 dir, b4 F0, b3:0 F4:F1
uint8_t statFuncEx;     // F12:F5
uint8_t dimOuts;

char logStr[128];

void APP_Initialize(void);
void APP_Execute(void);
void APP_TickExec(void);
void APP_SetAck(void);
void APP_UpdateOutput(void);
void APP_UpdateFuncOut(void);
void APP_UpdateFuncMap(void);
void APP_UpdateFuncDir(uint8_t value);
void APP_UpdateFuncG1(uint8_t value);
void APP_UpdateFuncG2(uint8_t value);
extern uint8_t DCC_CheckPacket(void);
extern void DCC_DecoderInit(void);
extern void DCC_DecodePacket(void);
extern uint8_t CV_GetValue(uint8_t cv);

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
        if ((dccFilter & (LOGI_DCC_ALL | LOGI_DCC_ONCE)) != 0) {
            tmp = (dccPktBuf[idx] & 0xF0) >> 4;
            if (tmp > 9)
                *(pOutStr++) = tmp + 0x37; else *(pOutStr++) = tmp + 0x30;
            tmp = dccPktBuf[idx] & 0x0F;
            if (tmp > 9)
                *(pOutStr++) = tmp + 0x37; else *(pOutStr++) = tmp + 0x30;
            *(pOutStr++) = ' ';
        }
    }
    if ((dccFilter & (LOGI_DCC_ALL | LOGI_DCC_ONCE)) != 0) {
        dccPktLen = 0;
        if (sum) {
            *(pOutStr++) = 'W';
            *(pOutStr++) = '\r';
            *(pOutStr++) = '\n';
        }
        *pOutStr = 0;
        SERIAL_SendString(dccOutBuf);
        
        if (dccFilter & LOGI_DCC_ONCE) {
            dccFilter = dccFilter & ~(LOGI_DCC_ONCE);
        }
    }
      
    return sum;    
    
} // APP_CheckPacket

void APP_UpdateFuncOut(void)
{     
    uint8_t dimEn = 0;
    
    if (dimOuts & 0x01) {
        BOARD_PWMA_SetDutyCycle(0xFC - (CV_GetValue(CV049_Dim_A) << 2));
        dimEn |= BOARD_PWMA_ENABLE;
    }
    else
        BOARD_AUXDA_Off();
    
    if (dimOuts & 0x02) {
        BOARD_PWMB_SetDutyCycle(0xFC - (CV_GetValue(CV050_Dim_B) << 2));
        dimEn |= BOARD_PWMB_ENABLE;
    }
    else
        BOARD_AUXDB_Off();
    
    if (dimOuts & 0x04) {      
        BOARD_PWMC_SetDutyCycle(0xFC - (CV_GetValue(CV051_Dim_C) << 2));
        dimEn |= BOARD_PWMC_ENABLE;
    }
    else
        BOARD_AUXDC_Off();
    
    if (dimOuts & 0x08) {
        BOARD_PWMD_SetDutyCycle(0xFC - (CV_GetValue(CV052_Dim_D) << 2));
        dimEn |= BOARD_PWMD_ENABLE;
    }
    else
        BOARD_AUXDD_Off();
    
    if (dimOuts & 0x10) {
        BOARD_PWME_SetDutyCycle(0xFC - (CV_GetValue(CV053_Dim_E) << 2));
        dimEn |= BOARD_PWME_ENABLE;
    }
    else
        BOARD_AUXDE_Off();
    
    if (dimOuts & 0x20) {
        BOARD_PWMF_SetDutyCycle(0xFC - (CV_GetValue(CV054_Dim_F) << 2));
        dimEn |= BOARD_PWMF_ENABLE;
    }
    else
        BOARD_AUXDF_Off();
        
    BOARD_PWM_Enable(dimEn);
    
} // APP_UpdateFuncOut

void APP_UpdateFuncMap(void)
{
    uint8_t iout;
    
    dimOuts = 0;
    for (iout = 0; iout < 6; iout++) {
        // F0,F4:F1
        if (0x1F & (statFunc & CV_GetValue(CV033_FuncMap_A1 + (iout * 2))))
            dimOuts |= (1 << iout);
        if (statFuncEx & CV_GetValue(CV033_FuncMap_A1 + (iout * 2) + 1))
            dimOuts |= (1 << iout);
    }
    
    if (statFunc & FUNC_STATE_REV)
        dimOuts = dimOuts & ~(CV_GetValue(CV047_Deactiv_Rev1));
    else
        dimOuts = dimOuts & ~(CV_GetValue(CV045_Deactiv_Fwd1));
    
} // APP_UpdateFuncMap

void APP_UpdateFuncDir(uint8_t value)
{
    if (value & 0x80) {
        // FWD
        statFunc = statFunc & ~FUNC_STATE_REV;
    }
    else {
        // REV
        statFunc |= FUNC_STATE_REV;
    }
    
    APP_UpdateFuncMap();
    APP_UpdateFuncOut();
    
} // APP_UpdateFuncDir

void APP_UpdateFuncG1(uint8_t value)
{
    // F0,F4-F1
    statFunc = (statFunc & 0xE0) | value;
    
    APP_UpdateFuncMap();
    APP_UpdateFuncOut();
    
} // APP_UpdateFuncG1

void APP_UpdateFuncG2(uint8_t value)
{
    if (value & 0x10)
        // F8-F5
        statFuncEx = (statFuncEx & 0xF0) | (value & 0x0F);
    else
        // F12-F9
        statFuncEx = (statFuncEx & 0x0F) | ((value & 0x0F) << 4);
    
    APP_UpdateFuncMap();
    APP_UpdateFuncOut();
    
} // APP_UpdateFuncG2

void APP_SetAck(void)
{
    static uint32_t ackTout;
    
    BOARD_OUTACK_On();
    ackTout = SYS_GetTick() + 6;
    do {}
    while (ackTout > SYS_GetTick());
    BOARD_OUTACK_Off();
    
} // APP_SetAck

void APP_UpdateOutput(void)
{
	static uint16_t blinkHB = 0;
    blinkHB++;
    if (blinkHB == 1) {
        BOARD_LEDHB_On();
    }
    else if (blinkHB == 750) {
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
        BOARD_PWMA_SetDutyCycle(dimVal);
        dimTest = 0;
    }
    
} // APP_UpdateOutput

extern void DCCREC_Init(void);

void APP_Initialize(void)
{
	dccIdle = 0;
    dccFilter = LOGI_DCC_ALL;
    statFunc = FUNC_STATE_INIT;
    statFuncEx = 0;
    dccPktLen = 0;
    DCCREC_Init();
    
    DCC_DecoderInit();
    BOARD_AUXDA_Off();
    BOARD_AUXDB_Off();
    BOARD_AUXDC_Off();
    BOARD_AUXDD_Off();
    BOARD_AUXDE_Off();
    BOARD_AUXDF_Off();
    BOARD_PWM_Enable(BOARD_PWM_NONE);
    
    SERIAL_Initialize();  
    SERIAL_SendString("DCCdec08 v.200517.1\r\n");
    
} // APP_Initialize

void APP_TickExec(void)
{
    APP_UpdateOutput();
}

void APP_Execute(void)
{
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
        dccPktLen = 0;
    }
    
} // APP_Tasks

// EOF dec08_app.c
