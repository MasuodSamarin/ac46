#ifndef _COMMON_
#define _COMMON_



extern volatile u32 delay_cnt;

void delay(volatile u32  t);

#define my_memzero(addr,len)    memset((addr),0x00,(len))

#endif
