#include "includes.h"
#include "hwi.h"
#include "clock.h"
#include "config.h"
#include "clock_api.h"


OS_EVENT  uart_mutex;
volatile u32 uart0_rx_count ;
char putbyte(char a);


#if (DEBUG_UART == UART0)
#ifndef BT_TESTER
//#define UART_TXPA8_RXPA9
//#define UART_TXPB10_RXPB11
#define UART_TXPC6_RXPC7
//#define UART_TXPD6_RXPD7
#else
#define UART_TXPD6_RXPD7
#endif
#endif

#if (DEBUG_UART == UART1)
//#define UART_TXPA6_RXPA7
#define UART_TXPB2_RXPB3
//#define UART_TXPB6_RXPB7
//#define UART_USBP_USBM
#endif

#if (DEBUG_UART == UART2)
//#define UART_TXPA4_RXPA5
#define UART_TXPA10_RXPA11
//#define UART_TXPB8_RXPB9
//#define UART_TXPC12_RXPC13
#endif

u32 g_debug ;

void uart1_init()
{
#if (DEBUG_UART == UART0)
#ifdef UART_TXPA8_RXPA9
    IOMC0 &=~(BIT(7)|BIT(6));
    PORTA_OUT |= BIT(8) ;
    PORTA_DIR |= BIT(9) ;
    PORTA_DIR &=~BIT(8) ;
#endif/*UART_TXPA8_RXPA9*/

#ifdef UART_TXPB10_RXPB11
    IOMC0 &=~(BIT(7)|BIT(6));
    IOMC0 |= BIT(6);
    PORTB_OUT |= BIT(10) ;
    PORTB_DIR |= BIT(11) ;
    PORTB_DIR &=~BIT(10) ;
#endif/*UART_TXPB10_RXPB11*/

#ifdef UART_TXPC6_RXPC7
    IOMC0 &=~(BIT(7)|BIT(6));
    IOMC0 |= BIT(7);
    PORTC_OUT |= BIT(6) ;
    PORTC_DIR |= BIT(7) ;
    PORTC_DIR &=~BIT(6) ;
#endif/*UART_TXPC6_RXPC7*/

#ifdef UART_TXPD6_RXPD7
    IOMC0 |= BIT(7)|BIT(6);
    PORTD_OUT |= BIT(6) ;
    PORTD_DIR |= BIT(7) ;
    PORTD_DIR &=~BIT(6) ;
#endif/*UART_TXPD6_RXPD7*/
#ifndef BT_TESTER
    UT0_BAUD = (UART_CLK/115200)/4;
#else
    UT0_BAUD = (UART_CLK/460800)/4;
#endif
    UT0_CON = BIT(13) | BIT(12) | BIT(0);       //rx_ie , CLR RX PND

#elif (DEBUG_UART == UART1)
#ifdef UART_TXPA6_RXPA7
    IOMC1 &= ~(BIT(3)|BIT(2));
    PORTA_OUT |= BIT(6) ;
    PORTA_DIR |= BIT(7) ;
    PORTA_DIR &=~BIT(6) ;
#endif/*UART_TXPA6_RXPA7*/

#ifdef UART_TXPB2_RXPB3
    IOMC1 &= ~(BIT(3)|BIT(2));
    IOMC1 |= BIT(2);
    PORTB_OUT |= BIT(2) ;
    PORTB_DIR |= BIT(3) ;
    PORTB_DIR &=~BIT(2) ;
#endif/*UART_TXPB2_RXPB3*/

#ifdef UART_TXPB6_RXPB7
    IOMC1 &= ~(BIT(3)|BIT(2));
    IOMC1 |= BIT(3);
    PORTB_OUT |= BIT(6) ;
    PORTB_DIR |= BIT(7) ;
    PORTB_DIR &=~BIT(6) ;
#endif/*UART_TXPB6_RXPB7*/

#ifdef UART_USBP_USBM
    IOMC1 |= BIT(3)|BIT(2);
    USB_CON0 |= BIT(0)|BIT(1);
    USB_IO_CON = 0;
    USB_IO_CON |= BIT(0); //tx dp
    USB_IO_CON |= BIT(3);//rx dm
    USB_IO_CON &= ~BIT(2);//tx dp
#endif
#ifndef BT_TESTER
    UT1_BAUD = (UART_CLK/115200)/4;
#else
    UT1_BAUD = (UART_CLK/460800)/4;
#endif
    UT1_CON = BIT(13) | BIT(12) | BIT(0);       //rx_ie , CLR RX PND

#elif (DEBUG_UART == UART2)
#ifdef UART_TXPA4_RXPA5
    IOMC1 &= ~(BIT(15)|BIT(14));
    PORTA_OUT |= BIT(4) ;
    PORTA_DIR |= BIT(5) ;
    PORTA_DIR &=~BIT(4) ;
#endif/*UART_TXPA4_RXPA5*/

#ifdef UART_TXPA10_RXPA11
    IOMC1 &= ~(BIT(15)|BIT(14));
    IOMC1 |= BIT(14);
    PORTA_OUT |= BIT(10) ;
    PORTA_DIR |= BIT(11) ;
    PORTA_DIR &=~BIT(10) ;
#endif/*UART_TXPA10_RXPA11*/

#ifdef UART_TXPB8_RXPB9
    IOMC1 &= ~(BIT(15)|BIT(14));
    IOMC1 |= BIT(15);
    PORTB_OUT |= BIT(8) ;
    PORTB_DIR |= BIT(9) ;
    PORTB_DIR &=~BIT(8) ;
#endif/*UART_TXPB8_RXPB9*/

#ifdef UART_TXPC12_RXPC13
    IOMC1 |= BIT(15)|BIT(14);
    PORTC_OUT |= BIT(12) ;
    PORTC_DIR |= BIT(13) ;
    PORTC_DIR &=~BIT(12) ;
#endif/*UART_TXPC12_RXPC13*/
    UT2_BAUD = (UART_CLK/115200)/4;
    UT2_CON = BIT(13) | BIT(12) | BIT(0);       //rx_ie , CLR RX PND
#endif
}

bool init_uart_mutex()
{
    u16 err;

    err = OSMutexCreate(&uart_mutex);

    if(err != OS_NO_ERR)
    {
        puts_without_lock("create uart mutex err \r\n") ;
        return 0 ;
    }

    return 1 ;
}

#if (DEBUG_UART == UART2)
char putbyte(char a) sec(.comm);
char putbyte(char a)
{
    if(a == '\n'){
        UT2_BUF = '\r';
        while((UT2_CON & BIT(15)) == 0);
    }
    UT2_BUF = a;
    while((UT2_CON & BIT(15)) == 0);     //TX IDLE
    return a;
}

char getbyte()
{
    char c=0;

    if((UT2_CON & BIT(14))){
        c = UT2_BUF;
        UT2_CON |= BIT(12);
    }

    return c;
}
#elif (DEBUG_UART == UART1)
char putbyte(char a) sec(.comm);
char putbyte(char a)
{
    if(a == '\n'){
        UT1_BUF = '\r';
        while((UT1_CON & BIT(15)) == 0);
    }
    UT1_BUF = a;
    while((UT1_CON & BIT(15)) == 0);     //TX IDLE
    return a;
}

char getbyte()
{
    char c=0;

    if((UT1_CON & BIT(14))){
        c = UT1_BUF;
        UT1_CON |= BIT(12);
    }

    return c;
}
#elif (DEBUG_UART == UART0)
char putbyte(char a) sec(.comm);
char putbyte(char a)
{
    if(a == '\n'){
        UT0_BUF = '\r';
        while((UT0_CON & BIT(15)) == 0);
    }
    UT0_BUF = a;
    while((UT0_CON & BIT(15)) == 0);     //TX IDLE
    return a;
}

char getbyte()
{
    char c=0;

    if((UT0_CON & BIT(14))){
        c = UT0_BUF;
        UT0_CON |= BIT(12);
    }

    return c;
}
#elif (DEBUG_UART == UART_NO)
char putbyte(char a) sec(.comm);
char putbyte(char a)
{
}
char getbyte()
{

}
#endif


/*----------------------------------------------------------------------------*/
/**@brief   ´®¿ÚÊä³öÒ»¸ö×Ö·û
   @param   void
   @return  void
   @author  Change.tsai
   @note    void putchar(char)
*/
/*----------------------------------------------------------------------------*/
int putchar(int a) sec(.comm);
int putchar(int a)
{
	/*CPU_SR_ALLOC();*/
	/*CPU_INT_DIS();*/
    if((a == '\n') || (a == '\r'))
    {
        putbyte(0x0d);
        putbyte(0x0a);
    }
    else
        putbyte(a);
	/*CPU_INT_EN();*/

    return a;
}

void put_u4hex(u8 dat)
{
    dat = 0xf & dat;
    if(dat>9)
    {
        putbyte(dat-10 + 'A');
    }
    else
    {
        putbyte(dat + '0');
    }
}

void put_u32hex(u32 dat)
{
    //   dsp_lock(UART_LOCK) ;
    //u32 cpu_sr ;
    //OS_ENTER_CRITICAL_WITHOUT_LOCK();
    //dsp_lock(UART_LOCK) ;
    put_u4hex(dat>>28);
    put_u4hex(dat>>24);

    put_u4hex(dat>>20);
    put_u4hex(dat>>16);

    put_u4hex(dat>>12);
    put_u4hex(dat>>8);

    put_u4hex(dat>>4);
    put_u4hex(dat);
    putchar('\n');

    //OS_EXIT_CRITICAL_WITHOUT_LOCK();
    //dsp_lock(UART_LOCK) ;
    //   dsp_unlock(UART_LOCK) ;
}

void put_u16hex(u16 dat)
{
    putbyte('0');
    putbyte('x');


    put_u4hex(dat>>12);
    put_u4hex(dat>>8);

    put_u4hex(dat>>4);
    put_u4hex(dat);
    putchar('\n');
}
void put_u32hex0(u32 dat)
{

    //OS_ENTER_CRITICAL_WITHOUT_LOCK();
    //dsp_lock(UART_LOCK) ;
    /* UART_DSP_LOCK() ; */
    putbyte('0');
    putbyte('x');
    put_u4hex(dat>>28);
    put_u4hex(dat>>24);

    put_u4hex(dat>>20);
    put_u4hex(dat>>16);

    put_u4hex(dat>>12);
    put_u4hex(dat>>8);

    put_u4hex(dat>>4);
    put_u4hex(dat);
    putchar(' ');
    /* UART_DSP_UNLOCK() ; */
    //OS_EXIT_CRITICAL_WITHOUT_LOCK();
}
void put_u8hex0(u8 dat)
{
        //OS_ENTER_CRITICAL_WITHOUT_LOCK();
    //dsp_lock(UART_LOCK) ;
    //UART_DSP_LOCK() ;
    //   dsp_lock(UART_LOCK) ;
    putbyte('0');
    putbyte('x');
    put_u4hex(dat>>4);
    put_u4hex(dat);
    putchar(' ');
    //UART_DSP_UNLOCK() ;
    //    dsp_unlock(UART_LOCK) ;
    //OS_EXIT_CRITICAL_WITHOUT_LOCK();
    //   dsp_unlock(UART_LOCK) ;
}
void put_u8hex(u8 dat)
{
    put_u4hex(dat>>4);
    put_u4hex(dat);
    putchar(' ');
}

void put_buf(u8 *buf, u32 len )
{
    u32 i ;
    for(i = 0 ; i < len ; i++)
    {
        if((i%16)==0)
        {
            putbyte('\n') ;
        }
        put_u8hex(buf[i]) ;
    }
    putbyte('\n') ;
}
void printf_buf(u8 *buf, u32 len )
{
    u32 i ;
   put_u32hex0((u32)buf) ;

    for(i = 0 ; i < len ; i++)
    {
        if((i%16)==0)
        {
            putbyte('\n') ;
        }
        put_u8hex(buf[i]) ;
    }
    putbyte('\n') ;
}

int puts(char *out)
{
    /* os_mutex_pend(&uart_mutex,0);               [> Acquire semaphore to perform random numbers        <] */
    puts_without_lock(out) ;
    /* os_mutex_post(&uart_mutex);               [> Release semaphore                                  <] */
    return 0;
}

int printf_without_lock(char* out)
{
    return puts_without_lock(out) ;
}

int puts_without_lock(char *out)
{
    while(*out != '\0')
    {
        putchar(*out);
        out++;
    }
    return 0;
}

volatile u8 uart0_tx_ok ;

void printf_data(void *ptr ,u32 len)
{
    uart0_tx_ok  = 0 ;
     /* UT0_TXADR = ptr ; */
     /* UT0_TXCNT = len ; */
     //while((UT0_CON & BIT(15)) == 0);     //TX IDLE
     //UT0_CON |= BIT(13) ;
     while(!uart0_tx_ok) ;
     puts_without_lock("printf data over \r\n") ;

}





