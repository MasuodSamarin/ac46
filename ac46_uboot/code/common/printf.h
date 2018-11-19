#ifndef _PRINTF_DEFINED_
#define _PRINTF_DEFINED_

#include <stdarg.h>
#include <typedef.h>
#ifndef NULL
#define NULL ((void *)0)
#endif

int printf(const char *format, ...);
int sprintf(char *out, const char *format, ...);


#endif
