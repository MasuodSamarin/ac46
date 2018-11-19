#ifndef TIMER_H
#define TIMER_H

#include "typedef.h"

void timer0_init();
void timer1_init();
void timer0_isr();
void timer1_isr();

void set_tick_timer(u32 hz );
void init_tick_timer(u32 hz);

extern const u32 timer_div[16];
extern volatile u8 sys_halfsec;
#endif

