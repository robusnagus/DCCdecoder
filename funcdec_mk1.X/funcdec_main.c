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

// ATTiny xx14
FUSES = {
	0x00, // WDTCFG{PERIOD=OFF, WINDOW=OFF}
	0x00, // BODCFG{SLEEP=DIS, ACTIVE=DIS, SAMPFREQ=1KHZ, LVL=BODLEVEL0}
	0x02, // OSCCFG{FREQSEL=20MHZ, OSCLOCK=CLEAR}
	{0x00}, // Reserved
	0x00, // TCD0CFG{CMPA=0,CMPB=0,CMPC=0,CMPD=0,CMPAEN=DIS,CMPBEN=DIS,CMPCEN=DIS,CMPDEN=DIS}
	0xF6, // SYSCFG0{EESAVE=CLEAR, RSTPINCFG=UPDI, CRCSRC=NOCRC}
	0x07, // SYSCFG1{SUT=64MS}
	0x00, // APPEND
	0x00, // BOOTEND
};

LOCKBITS = {
	0xC5, // LOCKBIT{LB=NOLOCK}
};

static uint32_t uwTick;         // zegar systemowy

extern void APP_Initialize(void);
extern void APP_TickExec(void);
extern void APP_Execute(void);

void BOARD_MCU_Init(void);
void BOARD_Clock_Init(void);
void BOARD_GPIO_Init(void);
void BOARD_TimB0_Init(void);
void BOARD_PWM_Init(void);

// inicjalizacja procesora
// param: brak
// zwrot: brak
void BOARD_MCU_Init(void)
{
	uint8_t i;
    // low power mode
    for (i = 0; i < 8; i++) {
        *((uint8_t *)&PORTA + 0x10 + i) |= (1 << PORT_PULLUPEN_bp);
        *((uint8_t *)&PORTB + 0x10 + i) |= (1 << PORT_PULLUPEN_bp);
    }
    
} // BOARD_MCU_Init

// inicjalizacja zegara
// param: brak
// zwrot: brak
void BOARD_Clock_Init(void)
{ 
    _PROTECTED_WRITE(CLKCTRL.OSC32KCTRLA, 0x00);    // RUNSTDBY disabled;
    _PROTECTED_WRITE(CLKCTRL.XOSC32KCTRLA, 0x00);   // XOSC32k disabled
    
    _PROTECTED_WRITE(CLKCTRL.OSC20MCTRLA, 0x00);    // RUNSTDBY disabled;
    _PROTECTED_WRITE(CLKCTRL.MCLKCTRLB, CLKCTRL_PDIV_2X_gc |
                                        (1 << CLKCTRL_PEN_bp));
    _PROTECTED_WRITE(CLKCTRL.MCLKCTRLA, CLKCTRL_CLKSEL_OSC20M_gc | 
                                        (0 << CLKCTRL_CLKOUT_bp));   
    _PROTECTED_WRITE(CLKCTRL.MCLKLOCK, 0x00);       // LOCKEN disabled;
    
    while (RTC.STATUS > 0) { 
	}
    RTC.CMP = 0x00;
    RTC.CNT = 0x00;
    RTC.PER = 0xFFFF;
    RTC.CLKSEL     = RTC_CLKSEL_INT32K_gc;
    RTC.DBGCTRL    = 0x00;
    RTC.INTCTRL    = 0x00;
    RTC.PITCTRLA   = RTC_PERIOD_CYC32_gc | (1 << RTC_RTCEN_bp);    
    RTC.PITDBGCTRL = 0x00;
    RTC.PITINTCTRL = (1 << RTC_PI_bp);
    RTC.CTRLA      = RTC_PRESCALER_DIV1_gc | (1 << RTC_RTCEN_bp);
    
} // BOARD_Clock_Init

// inicjalizacja portów
// param: brak
// zwrot: brak
void BOARD_GPIO_Init(void)
{      
    // OUT_ACK     PA6
    PORTA.DIRSET = (1 << PIN6_bp);
    *((uint8_t *)&PORTA + 0x16) = 0x00;
    BOARD_OUTACK_Off();
    
    // DCCIN PA1
    PORTA.DIRCLR = (1 << PIN1_bp);
    
} // BOARD_GPIO_Init

// inicjalizacja timera - odbiornik DCC
// param: brak
// zwrot: brak
void BOARD_TimB0_Init(void)
{
    TCB0.CNT      = 0;
    TCB0.CCMP     = 0;
    TCB0.CTRLB    = TCB_CNTMODE_PW_gc;
    TCB0.EVCTRL   = (0 << TCB_EDGE_bp) |
                    (1 << TCB_CAPTEI_bp);
    TCB0.INTCTRL  = (1 << TCB_CAPT_bp);
    TCB0.INTFLAGS = 0x00;
    TCB0.TEMP     = 0x00;
    TCB0.CTRLA    = TCB_CLKSEL_CLKDIV1_gc |
                    (1 << TCB_ENABLE_bp);
    
    EVSYS.ASYNCCH0 = EVSYS_ASYNCCH0_PORTA_PIN1_gc;
    EVSYS.ASYNCUSER0 = EVSYS_ASYNCUSER0_ASYNCCH0_gc;
    
} // BOARD_TimB0_Init

// inicjalizacja wyjść (ze ściemnianiem)
// param: brak
// zwrot: brak
void BOARD_PWM_Init(void)
{
    // PWM out: PA3 PA4 PA5 PB0 PB1 PB2
    PORTA.DIRSET = ((1 << PIN3_bp) | (1 << PIN4_bp) | (1 << PIN5_bp));
    *((uint8_t *)&PORTA + 0x13) = 0x00;
    *((uint8_t *)&PORTA + 0x14) = 0x00;
    *((uint8_t *)&PORTA + 0x15) = 0x00;
    PORTB.DIRSET = ((1 << PIN0_bp) | (1 << PIN1_bp) | (1 << PIN2_bp));
    *((uint8_t *)&PORTB + 0x10) = 0x00;
    *((uint8_t *)&PORTB + 0x11) = 0x00;
    *((uint8_t *)&PORTB + 0x12) = 0x00;
    
    TCA0.SPLIT.CTRLD    = (1 << TCA_SPLIT_SPLITM_bp);
    TCA0.SPLIT.HPER     = 0xFF;
    TCA0.SPLIT.LPER     = 0xFF;
    TCA0.SPLIT.HCMP0    = 0xFF;
    TCA0.SPLIT.LCMP0    = 0xFF;
    TCA0.SPLIT.HCMP1    = 0xFF;
    TCA0.SPLIT.LCMP1    = 0xFF;
    TCA0.SPLIT.HCMP2    = 0xFF;
    TCA0.SPLIT.LCMP2    = 0xFF;
    TCA0.SPLIT.HCNT     = 0x00;
    TCA0.SPLIT.LCNT     = 0x00;
    TCA0.SPLIT.CTRLB    = 0x00;     // default: OFF
    TCA0.SPLIT.CTRLA    = TCA_SPLIT_CLKSEL_DIV4_gc | (1 << TCA_SPLIT_ENABLE_bp);
 
} // BOARD_PWM_Init

// program główny
int main(void)
{
    uwTick = 0;

	BOARD_MCU_Init();
    BOARD_Clock_Init();
    BOARD_GPIO_Init();
    BOARD_TimB0_Init();
    BOARD_PWM_Init();
    
    APP_Initialize();
    // interrupt enable
	_PROTECTED_WRITE(CPUINT.CTRLA, 0x00);
	CPUINT.LVL0PRI = 0x00;
	CPUINT.LVL1VEC = 0x00;
	SYS_EnableInterrupts();
    
    static uint32_t lastTick = 0;
    // pętla główna
    while (1) {
        if (lastTick != uwTick) {
            APP_TickExec();
            lastTick = uwTick;
        }
		APP_Execute();
    }

    return 0;
    
} // main

// zegar z taktem 1ms - przerwanie
ISR(RTC_PIT_vect)
{
	RTC.PITINTFLAGS = (1 << RTC_PI_bp);
	uwTick++;
}

uint32_t SYS_GetTick(void)
{
    return uwTick;
}

// EOF funcdec_main.c
