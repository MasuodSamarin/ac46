#include "config.h"

void delay(volatile u32 t)
{
    while(t--)
    {
        asm("nop");
    }
}

