//
// Project: DCC decoder proto M3208
// File:    dec08_board.h
// Author:  Nagus
// Version: 20200108
//

#ifndef DEC08_BOARD_H
#define	DEC08_BOARD_H

#include <avr/io.h>
#include <avr/interrupt.h>

#include "dec08_config.h"

// DCCIN            PA3
// AUX1 AUX2        PD2 PD3
// AUX3 AUX4        PD4 PD5
// AUX_FL AUX_RL    PA7 PA6
// OUT_ACK OUT_HB   PF2 PF5
// PWM1 PWM2        PF0 PF1
// PWM3 PWM4        PF3 PF4
// UART TX RX       PA0 PA1

#define BOARD_AUXFL_On()            PORTA.OUTCLR = (1 << PIN7_bp)
#define BOARD_AUXFL_Off()           PORTA.OUTSET = (1 << PIN7_bp)
#define BOARD_AUXFL_Toggle()        PORTA.OUTTGL = (1 << PIN7_bp)
#define BOARD_AUXRL_On()            PORTA.OUTCLR = (1 << PIN6_bp)
#define BOARD_AUXRL_Off()           PORTA.OUTSET = (1 << PIN6_bp)
#define BOARD_AUXRL_Toggle()        PORTA.OUTTGL = (1 << PIN6_bp)
#define BOARD_AUX01_On()            PORTD.OUTCLR = (1 << PIN2_bp)
#define BOARD_AUX01_Off()           PORTD.OUTSET = (1 << PIN2_bp)
#define BOARD_AUX01_Toggle()        PORTD.OUTTGL = (1 << PIN2_bp)
#define BOARD_AUX02_On()            PORTD.OUTCLR = (1 << PIN3_bp)
#define BOARD_AUX02_Off()           PORTD.OUTSET = (1 << PIN3_bp)
#define BOARD_AUX02_Toggle()        PORTD.OUTTGL = (1 << PIN3_bp)
#define BOARD_AUX03_On()            PORTD.OUTCLR = (1 << PIN4_bp)
#define BOARD_AUX03_Off()           PORTD.OUTSET = (1 << PIN4_bp)
#define BOARD_AUX03_Toggle()        PORTD.OUTTGL = (1 << PIN4_bp)
#define BOARD_AUX04_On()            PORTD.OUTCLR = (1 << PIN5_bp)
#define BOARD_AUX04_Off()           PORTD.OUTSET = (1 << PIN5_bp)
#define BOARD_AUX04_Toggle()        PORTD.OUTTGL = (1 << PIN5_bp)
#define BOARD_OUTACK_On()           PORTF.OUTSET = (1 << PIN2_bp)
#define BOARD_OUTACK_Off()          PORTF.OUTCLR = (1 << PIN2_bp)
#define BOARD_OUTACK_Toggle()       PORTF.OUTTGL = (1 << PIN2_bp)
#define BOARD_LEDHB_On()            PORTF.OUTCLR = (1 << PIN5_bp)
#define BOARD_LEDHB_Off()           PORTF.OUTSET = (1 << PIN5_bp)
#define BOARD_LEDHB_Toggle()        PORTF.OUTTGL = (1 << PIN5_bp)

#define BOARD_DCCREC_Handler()      ISR(TCB0_INT_vect)
#define BOARD_DCCREC_SetReady()     TCB0.INTFLAGS = (1 << TCB_CAPT_bp)
#define BOARD_DCCREC_GetBitTime()   TCB0.CCMP

#define BOARD_PWM0_SetDutyCycle(x)  TCA0.SPLIT.HCMP0 = x
#define BOARD_PWM1_SetDutyCycle(x)  TCA0.SPLIT.HCMP1 = x
#define BOARD_PWM3_SetDutyCycle(x)  TCA0.SPLIT.LCMP0 = x
#define BOARD_PWM4_SetDutyCycle(x)  TCA0.SPLIT.LCMP1 = x

#define BOARD_SERIAL_RXHandler()    ISR(USART0_RXC_vect)
#define BOARD_SERIAL_TXHandler()    ISR(USART0_DRE_vect)
#define BOARD_SERIAL_PutByte(x)     USART0.TXDATAL = x
#define BOARD_SERIAL_GetByte()      USART0.RXDATAL
#define BOARD_SERIAL_TXStart()      USART0.CTRLA |= (1 << USART_DREIE_bp)
#define BOARD_SERIAL_TXStop()       USART0.CTRLA &= ~(1 << USART_DREIE_bp)
#define BOARD_SERIAL_IsTXEmpty()    ((USART0.STATUS & USART_DREIF_bm) != 0)
#define BOARD_SERIAL_RXStart()      USART0.CTRLA |= (1 << USART_RXCIE_bp)
#define BOARD_SERIAL_RXStop()       USART0.CTRLA &= ~(1 << USART_RXCIE_bp)
#define BOARD_SERIAL_IsRXPend()     ((USART0.STATUS & USART_RXCIF_bm) != 0)

void    SERIAL_Initialize(void);
uint8_t SERIAL_SendByte(uint8_t data);
uint8_t SERIAL_SendString(char* data);
void    SERIAL_ProcessMessage(uint8_t *message);

#define _PROTECTED_WRITE(reg, value)				\
    __asm__ __volatile__("out %[ccp], %[ccp_ioreg]" "\n\t"	\
                         "sts %[ioreg], %[val]"			    \
                         :					                \
                         : [ccp] "I" (_SFR_IO_ADDR(CCP)),	\
                         [ccp_ioreg] "d" ((uint8_t)CCP_IOREG_gc),	\
                         [ioreg] "n" (_SFR_MEM_ADDR(reg)),	\
                         [val] "r" ((uint8_t)value))

#define SYS_EnableInterrupts()     __asm__ __volatile__ ( "sei" ::: "memory")

#endif	// DEC08_BOARD_H
