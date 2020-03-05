//
// Project: DCC decoder proto M3208
// File:    dec08_main.c
// Author:  Nagus
// Version: 20200111
//

#include "dec08_board.h"

static uint32_t uwTick;

extern void APP_Initialize(void);
extern void APP_Tasks(void);

void BOARD_MCU_Init(void);
void BOARD_Clock_Init(void);
void BOARD_GPIO_Init(void);
void BOARD_TimB0_Init(void);
void BOARD_PWM_Init(void);
void BOARD_UART_Init(void);

uint32_t SYS_GetTick(void);

void BOARD_MCU_Init(void)
{
	uint8_t i;
    // low power mode
    for (i = 0; i < 8; i++) {
        *((uint8_t *)&PORTE + 0x10 + i) |= (1 << PORT_PULLUPEN_bp);
        *((uint8_t *)&PORTF + 0x10 + i) |= (1 << PORT_PULLUPEN_bp);
        *((uint8_t *)&PORTA + 0x10 + i) |= (1 << PORT_PULLUPEN_bp);
        *((uint8_t *)&PORTB + 0x10 + i) |= (1 << PORT_PULLUPEN_bp);
        *((uint8_t *)&PORTC + 0x10 + i) |= (1 << PORT_PULLUPEN_bp);
        *((uint8_t *)&PORTD + 0x10 + i) |= (1 << PORT_PULLUPEN_bp);
    }
    
} // BOARD_MCU_Init

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

void BOARD_GPIO_Init(void)
{
    // AUX1-4           PD2 PD3 PD4 PD5 
    PORTD.DIRSET = ((1 << PIN5_bp) | (1 << PIN4_bp) |
                    (1 << PIN3_bp) | (1 << PIN2_bp));
    *((uint8_t *)&PORTD + 0x15) = 0x00;
    *((uint8_t *)&PORTD + 0x14) = 0x00;
    *((uint8_t *)&PORTD + 0x13) = 0x00;
    *((uint8_t *)&PORTD + 0x12) = 0x00;
    BOARD_AUX01_Off();
    BOARD_AUX02_Off();
    BOARD_AUX03_Off();
    BOARD_AUX04_Off();        
    // AUX_FL AUX_RL    PA7 PA6
    PORTA.DIRSET = ((1 << PIN7_bp) | (1 << PIN6_bp));
    *((uint8_t *)&PORTA + 0x17) = 0x00;
    *((uint8_t *)&PORTA + 0x16) = 0x00;
    BOARD_AUXFL_Off();
    BOARD_AUXRL_Off();
    // OUT_ACK OUT_HB   PF2 PF5
    PORTF.DIRSET = ((1 << PIN5_bp) | (1 << PIN2_bp));
    *((uint8_t *)&PORTF + 0x15) = 0x00;
    *((uint8_t *)&PORTF + 0x12) = 0x00;
    BOARD_OUTACK_Off();
    BOARD_LEDHB_Off();
    
    // DCCIN PA3
    PORTA.DIRCLR = (1 << PIN3_bp);
    
} // BOARD_GPIO_Init

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
    
    EVSYS.CHANNEL0 = EVSYS_GENERATOR_PORT0_PIN3_gc;
    EVSYS.USERTCB0 = EVSYS_CHANNEL_CHANNEL0_gc;
    
} // BOARD_TimB0_Init

void BOARD_PWM_Init(void)
{
    // PWM out: PF0 PF1 PF3 PF4
    PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTF_gc;
    PORTF.DIRSET = ((1 << PIN0_bp) | (1 << PIN1_bp) |
                    (1 << PIN3_bp) | (1 << PIN4_bp));
    *((uint8_t *)&PORTF + 0x10) = 0x00;
    *((uint8_t *)&PORTF + 0x11) = 0x00;
    *((uint8_t *)&PORTF + 0x13) = 0x00;
    *((uint8_t *)&PORTF + 0x14) = 0x00;
    
    TCA0.SPLIT.CTRLD    = (1 << TCA_SPLIT_SPLITM_bp);
    TCA0.SPLIT.HPER     = 0xFF;
    TCA0.SPLIT.LPER     = 0xFF;
    TCA0.SPLIT.HCMP0    = 0x10;
    TCA0.SPLIT.LCMP0    = 0x20;
    TCA0.SPLIT.HCMP1    = 0x30;
    TCA0.SPLIT.LCMP1    = 0x40;
    TCA0.SPLIT.HCNT     = 0xC0;
    TCA0.SPLIT.LCNT     = 0x00;
    TCA0.SPLIT.CTRLB    = ((1 << TCA_SPLIT_HCMP0EN_bp) | 
                           (1 << TCA_SPLIT_HCMP1EN_bp) |
                           (1 << TCA_SPLIT_LCMP0EN_bp) | 
                           (1 << TCA_SPLIT_LCMP1EN_bp));
    TCA0.SPLIT.CTRLA    = TCA_SPLIT_CLKSEL_DIV4_gc | (1 << TCA_SPLIT_ENABLE_bp);
    
} // BOARD_PWM_Init

void BOARD_UART_Init(void)
{
    // UART TX RX       PA0 PA1
    PORTA.DIRSET = (1 << PIN0_bp);
	PORTA.OUTCLR = (1 << PIN0_bp);
	PORTA.DIRCLR = (1 << PIN1_bp);
	*((uint8_t *)&PORTA + 0x11) &= ~(1 << PORT_PULLUPEN_bp);

	USART0.BAUD = (uint16_t)((float)(10000000.0 * 64 / 
                                    (16 * (float)SER_BRATE)) + 0.5);
	USART0.CTRLA = (1 << USART_RXCIE_bp);
	USART0.CTRLB = (1 << USART_RXEN_bp) | (1 << USART_TXEN_bp)
				   | USART_RXMODE_NORMAL_gc;
	USART0.CTRLC = USART_CMODE_ASYNCHRONOUS_gc | USART_CHSIZE_8BIT_gc
				   | USART_PMODE_DISABLED_gc | USART_SBMODE_1BIT_gc;
    
} // BOARD_UART_Init

int main(void)
{
	uwTick = 0;

	BOARD_MCU_Init();
    BOARD_Clock_Init();
    BOARD_GPIO_Init();
    BOARD_UART_Init();
    BOARD_TimB0_Init();
    BOARD_PWM_Init();
    
    APP_Initialize();
    // enable interrupts
	_PROTECTED_WRITE(CPUINT.CTRLA, 0x00);
	CPUINT.LVL0PRI = 0x00;
	CPUINT.LVL1VEC = 0x00;
	SYS_EnableInterrupts();
    
    // główna pętla
    while (1) {
        APP_Tasks();
    }

    return 0;
    
} // main

ISR(RTC_PIT_vect)
{
	RTC.PITINTFLAGS = (1 << RTC_PI_bp);
	uwTick++;
}

uint32_t SYS_GetTick(void)
{
    return uwTick;
}

// EOF dec08_main.c
