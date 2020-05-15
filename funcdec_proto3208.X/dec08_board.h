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

#ifndef DEC08_BOARD_H
#define	DEC08_BOARD_H

#include <avr/io.h>
#include <avr/interrupt.h>

#include "dec08_config.h"

// DCCIN            PA3
// OUT_ACK OUT_HB   PA2 PA7
// AUXD_A AUXD_B    PF0 PF1
// AUXD_C AUXD_D    PF2 PF3
// AUXD_E AUXD_F    PF4 PF5
// UART TX RX       PA0 PA1

#define BOARD_AUXDA                 0
#define BOARD_AUXDA_On()            PORTF.OUTCLR = (1 << PIN0_bp)
#define BOARD_AUXDA_Off()           PORTF.OUTSET = (1 << PIN0_bp)
#define BOARD_AUXDA_Toggle()        PORTF.OUTTGL = (1 << PIN0_bp)
#define BOARD_AUXDB                 1
#define BOARD_AUXDB_On()            PORTF.OUTCLR = (1 << PIN1_bp)
#define BOARD_AUXDB_Off()           PORTF.OUTSET = (1 << PIN1_bp)
#define BOARD_AUXDB_Toggle()        PORTF.OUTTGL = (1 << PIN1_bp)
#define BOARD_AUXDC                 2
#define BOARD_AUXDC_On()            PORTF.OUTCLR = (1 << PIN2_bp)
#define BOARD_AUXDC_Off()           PORTF.OUTSET = (1 << PIN2_bp)
#define BOARD_AUXDC_Toggle()        PORTF.OUTTGL = (1 << PIN2_bp)
#define BOARD_AUXDD                 3
#define BOARD_AUXDD_On()            PORTF.OUTCLR = (1 << PIN3_bp)
#define BOARD_AUXDD_Off()           PORTF.OUTSET = (1 << PIN3_bp)
#define BOARD_AUXDD_Toggle()        PORTF.OUTTGL = (1 << PIN3_bp)
#define BOARD_AUXDE                 4
#define BOARD_AUXDE_On()            PORTF.OUTCLR = (1 << PIN4_bp)
#define BOARD_AUXDE_Off()           PORTF.OUTSET = (1 << PIN4_bp)
#define BOARD_AUXDE_Toggle()        PORTF.OUTTGL = (1 << PIN4_bp)
#define BOARD_AUXDF                 5
#define BOARD_AUXDF_On()            PORTF.OUTCLR = (1 << PIN5_bp)
#define BOARD_AUXDF_Off()           PORTF.OUTSET = (1 << PIN5_bp)
#define BOARD_AUXDF_Toggle()        PORTF.OUTTGL = (1 << PIN5_bp)

#define BOARD_OUTACK_On()           PORTA.OUTSET = (1 << PIN2_bp)
#define BOARD_OUTACK_Off()          PORTA.OUTCLR = (1 << PIN2_bp)
#define BOARD_OUTACK_Toggle()       PORTA.OUTTGL = (1 << PIN2_bp)
#define BOARD_LEDHB_On()            PORTA.OUTCLR = (1 << PIN7_bp)
#define BOARD_LEDHB_Off()           PORTA.OUTSET = (1 << PIN7_bp)
#define BOARD_LEDHB_Toggle()        PORTA.OUTTGL = (1 << PIN7_bp)

#define BOARD_DCCREC_Handler()      ISR(TCB0_INT_vect)
#define BOARD_DCCREC_SetReady()     TCB0.INTFLAGS = (1 << TCB_CAPT_bp)
#define BOARD_DCCREC_GetBitTime()   TCB0.CCMP

#define BOARD_PWM_Enable(x)         TCA0.SPLIT.CTRLB = x
#define BOARD_PWM_NONE              0x00
#define BOARD_PWMA_ENABLE           (1 << TCA_SPLIT_LCMP0EN_bp)
#define BOARD_PWMB_ENABLE           (1 << TCA_SPLIT_LCMP1EN_bp)
#define BOARD_PWMC_ENABLE           (1 << TCA_SPLIT_LCMP2EN_bp)
#define BOARD_PWMD_ENABLE           (1 << TCA_SPLIT_HCMP0EN_bp)
#define BOARD_PWME_ENABLE           (1 << TCA_SPLIT_HCMP1EN_bp)
#define BOARD_PWMF_ENABLE           (1 << TCA_SPLIT_HCMP2EN_bp)
#define BOARD_PWMA_SetDutyCycle(x)  TCA0.SPLIT.LCMP0 = x
#define BOARD_PWMB_SetDutyCycle(x)  TCA0.SPLIT.LCMP1 = x
#define BOARD_PWMC_SetDutyCycle(x)  TCA0.SPLIT.LCMP2 = x
#define BOARD_PWMD_SetDutyCycle(x)  TCA0.SPLIT.HCMP0 = x
#define BOARD_PWME_SetDutyCycle(x)  TCA0.SPLIT.HCMP1 = x
#define BOARD_PWMF_SetDutyCycle(x)  TCA0.SPLIT.HCMP2 = x

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
