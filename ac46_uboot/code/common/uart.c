#include "config.h"
#include "clock.h"
#include "uart.h"

#define UART0   0
#define UART1   1
#define UART2   2
#define DEBUG_UART   UART0

#if (DEBUG_UART == UART1)
void uart_init(void)
{
    CLK_CON1 &= ~(3 << 10);
    CLK_CON1 |= 2 << 10;//sys clk
    PORTA_DIR |= BIT(7);
    PORTA_DIR &= ~BIT(6);
    UT1_BAUD = (get_sys_clk() / 115200) / 4 - 1;
    UT1_CON = BIT(13) | BIT(12) | BIT(0);
}
#elif (DEBUG_UART == UART0)
void uart_init(void)
{
    CLK_CON1 &= ~(3 << 10);
    CLK_CON1 |= 2 << 10;//sys clk
#ifdef UART_PA8
    IOMC0 &= ~(BIT(6)|BIT(7)); //Ñ¡ÖÐPA¿Ú
    IOMC1 &= ~(BIT(13) | BIT(12) | BIT(11));

    PORTA_DIE |= BIT(8);
    PORTA_DIR &= ~BIT(8);
    UT0_BAUD = (get_sys_clk() / 115200) / 4 - 1;
    UT0_CON = BIT(13) | BIT(12) | BIT(0);
#endif/*UART_PA8*/
}
#endif


#ifdef DEG_INFO
int puts(char *out)
{
    while(*out != '\0')
    {
        putchar(*out);
        out++;
    }

    return 0;
}

#if (DEBUG_UART == UART1)
void putbyte(char a)
{
    if(a == '\n')
    {
        UT1_BUF = '\r';

        while((UT1_CON & BIT(15)) == 0);
    }

    UT1_BUF = a;

    while((UT1_CON & BIT(15)) == 0);     //TX IDLE
}
#elif (DEBUG_UART == UART0)
void putbyte(char a)
{
    if(a == '\n')
    {
        UT0_BUF = '\r';

        while((UT0_CON & BIT(15)) == 0);
    }

    UT0_BUF = a;

    while((UT0_CON & BIT(15)) == 0);     //TX IDLE
}
#endif

void putchar(char a)
{
    if(a == '\n')
    {
        putbyte(0x0d);
        putbyte(0x0a);
    }
    else
    {
        putbyte(a);
    }
}

void put_u4hex(u8 dat)
{
    dat = 0xf & dat;

    if(dat > 9)
    {
        putbyte(dat - 10 + 'A');
    }
    else
    {
        putbyte(dat + '0');
    }
}
void put_u32hex(u32 dat)
{
    putbyte('0');
    putbyte('x');
    put_u4hex(dat >> 28);
    put_u4hex(dat >> 24);

    put_u4hex(dat >> 20);
    put_u4hex(dat >> 16);

    put_u4hex(dat >> 12);
    put_u4hex(dat >> 8);

    put_u4hex(dat >> 4);
    put_u4hex(dat);
    putchar('\n');
}

void put_u16hex(u16 dat)
{
    putbyte('0');
    putbyte('x');


    put_u4hex(dat >> 12);
    put_u4hex(dat >> 8);

    put_u4hex(dat >> 4);
    put_u4hex(dat);
    putchar(' ');
}

void put_u8hex(u8 dat)
{
    put_u4hex(dat >> 4);
    put_u4hex(dat);
    putchar(' ');
}
void printf_buf(u8 *buf, u32 len)
{

    u32 i ;

    for(i = 0 ; i < len ; i++)
    {
        if((i % 16) == 0)
        {
            putbyte('\n') ;
        }

        put_u8hex(buf[i]) ;
    }

    putbyte('\n') ;

}
#else
int puts(char *out)
{
    while(*out != '\0')
    {
        putchar(*out);
        out++;
    }

    return 0;
}

#if (DEBUG_UART == UART1)
void putbyte(char a)
{
    if(a == '\n')
    {
        UT1_BUF = '\r';

        while((UT1_CON & BIT(15)) == 0);
    }

    UT1_BUF = a;

    while((UT1_CON & BIT(15)) == 0);     //TX IDLE
}
#elif (DEBUG_UART == UART0)
void putbyte(char a)
{
    if(a == '\n')
    {
        UT0_BUF = '\r';

        while((UT0_CON & BIT(15)) == 0);
    }

    UT0_BUF = a;

    while((UT0_CON & BIT(15)) == 0);     //TX IDLE
}
#endif

void putchar(char a)
{
    if(a == '\n')
    {
        putbyte(0x0d);
        putbyte(0x0a);
    }
    else
    {
        putbyte(a);
    }
}
#endif
