#ifndef _IRTC_H_
#define _IRTC_H_

#include "includes.h"
#include "typedef.h"
#include "config.h"
#include "clock.h"
#include "HWI.h"
#include "rtc.h"

#define RTC_CON_WR          0x20
#define RTC_CON_RD          0xA0
#define RTC_PR_HD_IN_WR     0x21
#define RTC_PR_HD_IN_RD     0xA1
#define RTC_PR_DIR_OUT_WR   0x22
#define RTC_PR_DIR_OUT_RD   0xA2
#define RTC_PR_PD_PU_WR     0x23
#define RTC_PR_PD_PU_RD     0xA3
#define RTC_WK_EDG_EN_WR    0x24
#define RTC_WK_EDG_EN_RD    0xA4
#define RTC_WK_PND_WR       0x25
#define RTC_WK_PND_RD       0xA5
#define RTC_OSC_WR          0x26
#define RTC_OSC_RD          0xA6

#define IRTC_CS_EN			IRTC_CON |= BIT(0)
#define IRTC_CS_DIS			IRTC_CON &= ~BIT(0)

#define IRTC_X2IE(x)		IRTC_CON = ((IRTC_CON & ~(BIT(2))) | (x & 0x01)<<2)
#define IRTC_X512IE(x)		IRTC_CON = ((IRTC_CON & ~(BIT(4))) | (x & 0x01)<<4)
#define IRTC_WKIE(x)	    IRTC_CON = ((IRTC_CON & ~(BIT(6))) | (x & 0x01)<<6)

#define IRTC_WKCLRPND       IRTC_CON |= BIT(15)
#define IRTC_X512CLRPND     IRTC_CON |= BIT(13)
#define IRTC_X2CLRPND       IRTC_CON |= BIT(11)

#define WRITE_RTC 			0x40
#define READ_RTC  			0xC0
#define WRITE_ALM  			0x10
#define READ_ALM  			0x90

#define YEAR 		1927U//1925U
#define MONTH 		1
#define DAY 		1
#define HOUR 		0
#define MINUTES 	0
#define SECOND 		0

#define DATE 		4

enum
{
    PR0 = 0X10,
    PR1 = 0X20,
    PR2 = 0X40,
    PR3 = 0X80
};

typedef struct _RTC_TIME
{
    u16 dYear;		///<年份
    u8 	bMonth;		///<月份
    u8 	bDay;		///<天数
    u8 	bHour;		///<时
    u8 	bMin;		///<分
    u8 	bSec;		///<秒
//    u8 	bWeekday;	///<星期几
} RTC_TIME;

//typedef struct _ALM_TIME
//{
//    u8 	bHour;		///<时
//    u8 	bMin;		///<分
//    u8 	bSw;		///<闹钟开关
//    u8  bmWeekdays; ///<响闹日期
//}ALM_TIME;


#define PORTR0              BIT(0)
#define PORTR1              BIT(1)
#define PORTR2              BIT(2)
#define PORTR3              BIT(3)

void PORTR_DIR(u8 port, u8 val);
void PORTR_OUT(u8 port, u8 val);
void PORTR_HD(u8 port, u8 val);
void PORTR_PU(u8 port, u8 val);
void PORTR_PD(u8 port, u8 val);
void PORTR_ADCEN(u8 port,u8 val);
u8 PORTR_IN(u8 port);
//example:  PORTR_HD(PORTR0,1);//开启强驱
//example:  PORTR_DIR(PORTR0,1);//设置输入
//note：一次只能设置一个IO口

RTC_TIME current_time;
RTC_TIME current_alarm;

u8 irtc_sr_byte(u8 dat);

void write_rtc_time(RTC_TIME *curr_time);
void read_rtc_time(RTC_TIME *curr_time);
void write_alm_time(RTC_TIME *curr_time);
void updata_alm_time(RTC_TIME *curr_time,RTC_TIME *curr_alm);

void write_RTC_reg(u8 reg, u8 dat);
u8 read_RTC_reg(u8 reg);

void irtc_init(void);
void ireset_rtc(void);
void irtc_hw_init(void);

#endif
