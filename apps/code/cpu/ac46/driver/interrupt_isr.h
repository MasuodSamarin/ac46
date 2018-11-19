#ifndef _INTERRUPT_IST_H_
#define _INTERRUPT_IST_H_

#include "config.h"

void timer2_isr();
void timer3_isr();
void uart0_isr();
void uart1_isr();
void uart2_isr();
void iic_isr();
void spi1_isr();

#endif
