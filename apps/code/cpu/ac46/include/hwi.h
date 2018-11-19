/*******************************************************************************************
 File Name: HWI.h

 Version: 1.00

 Discription:


 Author:yulin deng

 Email :flowingfeeze@163.com

 Date:2013-09-14 16:47:39

 Copyright:(c)JIELI  2011  @ , All Rights Reserved.
*******************************************************************************************/
#ifndef HWI_h
#define HWI_h
#include "includes.h"

#define TICK_TIME_INIT  0
#define EXCEPTION_INIT  1
#define TIME0_INIT      2
#define TIME1_INIT      3
#define TIME2_INIT      4
#define TIME3_INIT      5
#define USB_SOF     6
#define USB_CTRL    7
#define RTC_INIT        8
#define ALINK_INIT      9
#define DAC_INIT        10
#define PORT_INIT       11
#define SPI0_INIT       12
#define SPI1_INIT       13
#define SD0_INIT       14
#define SD1_INIT       15
#define UART0_INIT      16
#define UART1_INIT      17
#define UART2_INIT      18
#define PAP_INIT        19
#define IIC_INIT        20
#define SARADC_INIT     21
#define FM_HWFE_INIT    22
#define FM_INIT         23
#define FM_LOFC_INIT    24
#define BT_INIT         25
#define BT_LOFC_INIT    26
#define BT_DBG_INIT     27
#define BT_PCM_INIT     28
#define NFC_INIT        29
#define SOFT0_INIT      30
#define SOFT_INIT       31



#define SYS_INT_BASE    0x1ff80







void HWI_Install(u32 index, void *isr,u32 Priority);
#define INTALL_HWI(a,b,c)\
extern void handle__##b();\
HWI_Install(a,handle__##b,c)

void ENABLE_INT();
void DISABLE_INT();

void DisableOSInt() ;
void EnableOSInt() ;
void hwi_init(void);
void hwi_init() ;

#endif
