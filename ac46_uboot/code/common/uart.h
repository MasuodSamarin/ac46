#ifndef _UART_
#define _UART_

#include "typedef.h"


/*强制声明*/
int   memcmp(const void *, const void *, long unsigned int);
void *memcpy(void *, const void *, long unsigned int);
void *memset(void *, int, long unsigned int);
int   printf(const char *format, ...);


extern void uart_init(void);
void putchar(char a);
extern int puts(char *out);
extern void put_buf(u8 *buf, u32 len);

#endif

