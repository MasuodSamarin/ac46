#ifndef _UART_
#define _UART_

#include "typedef.h"

#define UART_TXPND       15
#define UART_RXPND       14
#define UART_CTXPND      13
#define UART_CRXPND      12
#define UART_OTPND       11
#define UART_COTPND      10
#define UART_TB8         9
#define UART_RB8         8
#define UART_RDC         7
#define UART_DMA_EN      6
#define UART_OT_IEN      5
#define UART_DIV3N4      4
#define UART_RX_IEN      3
#define UART_TX_IEN      2
#define UART_9BIT_EN     1
#define UART_EN          0

void uart1_init (void);
void uart0_init(u32 baudrate);
int puts_without_lock(char *out);
/* int putchar(int a) ; */
void uart0_putbuf(u8 *uart_buf, u16 buf_len);
char getbyte();
char uart0_getbyte();
bool init_uart_mutex();
char putbyte(char a);


int puts(char *out);

int putchar(int a);
void put_buf(u8 *buf, u32 len );
void put_u8hex(u8 dat);
void put_u8hex0(u8 dat);
void put_u32hex(u32 dat);
void put_u32hex0(u32 dat);
void put_u16hex(u16 dat);

#endif

