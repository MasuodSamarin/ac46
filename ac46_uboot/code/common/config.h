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


/*���ڴ�ӡ������IO��ռ��*/
//#define UART_PA8

/*��ӡ������Ϣ*/
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


/*�豸�������LED������*/
#define UPDATA_LED_REMIND    //�������LED����
#define UPDATA_VOICE_REMIND  //������ɡ��ε���������

#endif
