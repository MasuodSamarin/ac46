#ifndef _CONFIG_
#define _CONFIG_

#include <string.h>
#include "bt15.h"
#include "typedef.h"
#include "common.h"
#include "clock.h"
#include "uart.h"
#include "printf.h"
#include "hwi.h"


/*串口打印控制器IO口占据*/
//#define UART_PA8

/*打印调试信息*/
#ifdef UART_PA8
    #define DEG_INFO
    #define MUST_INFO
#endif/*UART_PA8*/

#ifdef  DEG_INFO
    #define deg_puts        puts
    #define deg_printf      printf
    #define deg_printf_buf  printf_buf
    #define deg_put_u32hex  put_u32hex
#else
    #define deg_puts(...)
    #define deg_printf(...)
    #define deg_printf_buf(...)
    #define deg_put_u32hex(...)
#endif/*DEG_INFO*/

#ifdef  MUST_INFO
    #define must_puts        puts
#else
    #define must_puts(...)
#endif/*MUST_INFO*/


/*设备升级完成LED灯提醒*/
#define UPDATA_LED_REMIND    //升级完成LED提醒
#define UPDATA_VOICE_REMIND  //升级完成“滴滴声”提醒

#endif
