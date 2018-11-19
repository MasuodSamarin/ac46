#ifndef _INCLUDES_
#define _INCLUDES_

#include "typedef.h"
//#include "cpu.h"
#include "clock.h"
#include "config.h"
#include "hwi.h"
#include "printf.h"
#include "uart.h"
#include "string.h"
//#include "os_api.h"
//#include "err.h"
//#include "malloc.h"

typedef struct __SYS_INFO
{
    /*----------------------*/
    u32 sys_clk;
    u32 lsb_clk;
    s8 vol;
    s8 eq;
}_SYS_INFO;

#ifndef __SYS_INFO__
#define __SYS_INFO__
    _SYS_INFO sys_info;
#else
    extern _SYS_INFO sys_info;
#endif

#endif

