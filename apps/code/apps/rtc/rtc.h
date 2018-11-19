#ifndef _RTC_H_
#define _RTC_H_

#include "irtc.h"
#include "includes.h"

#define RTC_TASK_NAME   "RTCTask"

#define rtc_puts     puts
#define rtc_printf   printf


//typedef struct _ALM_VOL_INFO
//{
//    u8  bRtcVolr;    //<响闹前的右声道音量
//    u8  bRtcVoll;    //<响闹前的左声道音量
//    u8  bMute;       //<1：mute  0:unmunt
//}ALM_VOL_INFO;

//extern RTC_SETTING_VAR RTC_setting_var;
extern const struct task_info rtc_task_info;
extern void updata_time_1s(void);



/////////////////////////////////////////////////
//                TEST
/////////////////////////////////////////////////
//extern void rtc_clk_out(RTC_TIME *curr_time);
/////////////////////////////////////////////////
//                TEST
/////////////////////////////////////////////////

#endif

