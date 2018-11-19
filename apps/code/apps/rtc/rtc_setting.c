/*
********************************************************************************
*
*                                   RTC SETTING
*
* Filename      : rtc_setting.c
* Version       : V1.0
* Programmer(s) : WGW
********************************************************************************
*/
#include "app_cfg.h"
#include "os_api.h"
#include "os_cfg.h"
#include "error.h"
#include "system_cfg.h"
#include "config.h"
#include "msg.h"
#include "ui_api.h"
#include "rtc_setting.h"
#include "irtc.h"


#if RTC_CLK_EN

RTC_SETTING rtc_set;

/*******************************************************
				CONST
********************************************************/
//const u16 year_tab[]={365,366};
const u8 month_tab1[] = {31,28,31,30,31,30,31,31,30,31,30,31};		   ///<非闰年每月的天数
const u8 month_tab2[] = {31,29,31,30,31,30,31,31,30,31,30,31};		   ///<闰年每月的天数

const u16 smonth_tab1[]= {0,31,59,90,120,151,181,212,243,273,304,334,365};	  ///<非闰年的当月累计天数
const u16 smonth_tab2[]= {0,31,60,91,121,152,182,213,244,274,305,335,366};	  ///<	闰年的当月累计天数


/*----------------------------------------------------------------------------*/
/**@brief	判断闰年
   @param 	year:年份
   @return  真假
   @note	bool leapyear(u16 year)
*/
/*----------------------------------------------------------------------------*/
tbool leapyear(u16 year)
{
    if ((year%4==0 && year%100!=0)||(year%400==0))
        return TRUE;
    else
        return FALSE;
}

/*----------------------------------------------------------------------------*/
/**@brief	年份换算为天数
   @param 	day：总日数
   @return  星期的日数
   @note	u16 year_to_day(u16 year)
*/
/*----------------------------------------------------------------------------*/
u16 year_to_day(u16 year)
{
    if (leapyear(year))
        return 366;
    else
        return 365;
}

/*----------------------------------------------------------------------------*/
/**@brief	月份换算为天数
   @param 	day：总日数
   @return  星期的日数
   @note	u8 month_to_day(u8 month)
*/
/*----------------------------------------------------------------------------*/
u16 month_to_day(u16 year,u8 month)
{
    if (leapyear(year))
        return smonth_tab2[month];
    else
        return smonth_tab1[month];
}

/*----------------------------------------------------------------------------*/
/**@brief	总日数换算为星期的日数
   @param 	day：总日数
   @return  星期的日数
   @note	u8 day_to_weekday(u16 day)
*/
///*----------------------------------------------------------------------------*/
//u8 day_to_weekday(u16 day)
//{
//    tu16 tmp;
//    tu8 weekday;
//
//    tmp = day + DATE;
//    weekday = tmp % 7;
//
//    if (tmp < 7)
//        return tmp;
//    else if (weekday)
//        return (tmp % 7);
//    else
//        return 7;
//}

/*----------------------------------------------------------------------------*/
/**@brief	总天数换算为年份/月份/日期
   @param 	day：总天数；time:当前日期
   @return  星期的天数
   @note	void day_to_ymd(u16 day,sRTC_TIME *rtc_time)
*/
/*----------------------------------------------------------------------------*/
void day_to_ymd(u16 day,RTC_TIME *rtc_time)
{
    tu8 tmp;

    tmp = 0;
    while (day >= year_to_day(YEAR+tmp))
    {
        day -= year_to_day(YEAR+tmp);
        tmp++;
    }
    rtc_time->dYear = YEAR+tmp;

    tmp = 0;
    while (day >= month_to_day(rtc_time->dYear, MONTH + tmp))
    {
        tmp++;
    }
    day -= month_to_day(rtc_time->dYear, MONTH+tmp - 1);
    rtc_time->bMonth = MONTH+tmp;

    rtc_time->bDay = DAY+day;
}

/*----------------------------------------------------------------------------*/
/**@brief	当前年份/月份/日期换算成总天数
   @param 	time:当前日期
   @return  星期的天数
   @note	u16 ymd_to_day(sRTC_TIME *time,u16 day)
*/
/*----------------------------------------------------------------------------*/
u16 ymd_to_day(RTC_TIME *time)
{
    tu16 tmp_year;
    tu16 tmp_day = 0;

    for (tmp_year=YEAR; tmp_year<time->dYear; tmp_year++)			//年->日，当年不算在内，所以是<
    {
        tmp_day += year_to_day(tmp_year);
    }

    if (leapyear(time->dYear))						//月->日
        tmp_day += smonth_tab2[time->bMonth-1];
    else
        tmp_day += smonth_tab1[time->bMonth-1];

    tmp_day += (time->bDay-1);						//日->日,当日不算在内，所以日应该减1

    return tmp_day;
}

/*
*************************************************************
*Description: RTC时间“加”操作
*Arguments  : NULL
*Returns    : NULL
*Note       :
*By         :WGW
*************************************************************
*/
void calendar_time_plus(RTC_TIME *curr_rtc_time,u8 coordinate)
{
    if (coordinate == 0)
    {
        curr_rtc_time->dYear+=1;
        if (curr_rtc_time->dYear>2100)	curr_rtc_time->dYear=1925;
    }
    if (coordinate == 1)
    {
        curr_rtc_time->bMonth+=1;
        if (curr_rtc_time->bMonth>12)		curr_rtc_time->bMonth=1;
    }
    if (coordinate == 2)
    {
        curr_rtc_time->bDay+=1;
        if(curr_rtc_time->bDay > month_to_day(curr_rtc_time->bMonth,curr_rtc_time->dYear))
            curr_rtc_time->bDay=1;
    }

    if (coordinate == 3)
    {
        curr_rtc_time->bHour += 1;
        if (curr_rtc_time->bHour > 23)		curr_rtc_time->bHour = 0;
    }
    if (coordinate == 4)
    {
        curr_rtc_time->bMin += 1;
        if (curr_rtc_time->bMin > 59)		curr_rtc_time->bMin = 0;
    }
    if (coordinate == 5)
    {
        curr_rtc_time->bSec += 1;
        if (curr_rtc_time->bSec > 59)		curr_rtc_time->bSec = 0;
    }
}
/*
*************************************************************
*Description: RTC时间“减”操作
*Arguments  : NULL
*Returns    : NULL
*Note       :
*By         :WGW
*************************************************************
*/
void calendar_time_minus(RTC_TIME *curr_rtc_time,u8 coordinate)
{
    if (coordinate == 0)
    {
        curr_rtc_time->dYear -= 1;
        if (curr_rtc_time->dYear < 1925)curr_rtc_time->dYear = 2100;
    }
    if (coordinate == 1)
    {
        curr_rtc_time->bMonth -= 1;
        if (curr_rtc_time->bMonth < 1)	curr_rtc_time->bMonth = 12;
    }
    if (coordinate == 2)
    {
        curr_rtc_time->bDay -= 1;
        if (curr_rtc_time->bDay < 1)
            curr_rtc_time->bDay = month_to_day(curr_rtc_time->bMonth,curr_rtc_time->dYear);
    }

    if (coordinate == 3)
    {
        if (curr_rtc_time->bHour < 1)	curr_rtc_time->bHour = 24;
        curr_rtc_time->bHour -= 1;
    }
    if (coordinate == 4)
    {
        if (curr_rtc_time->bMin < 1)	curr_rtc_time->bMin = 60;
        curr_rtc_time->bMin -= 1;
    }
    if (coordinate == 5)
    {
        if (curr_rtc_time->bSec < 1)	curr_rtc_time->bSec = 60;
        curr_rtc_time->bSec -= 1;
    }
}

/*
*************************************************************
*Description: 开关ALM
*Arguments  : 1：打开闹钟；0：关闭闹钟
*Returns    : NULL
*Note       :
*By         :WGW
*************************************************************
*/
void alm_sw(u8 flag)
{
    u8 reg;
    if(flag)
    {
        puts("-open alarm-\n");
        reg = read_RTC_reg(RTC_CON_RD);
        write_RTC_reg(RTC_CON_WR,reg|BIT(5)); //ALM ON
    }
    else
    {
        puts("-close alarm-\n");
        reg = read_RTC_reg(RTC_CON_RD);
        write_RTC_reg(RTC_CON_WR,reg&(~BIT(5)));//ALM OFF
    }
}

/*
*************************************************************
*Description: RTC时间设置
*Arguments  : NULL
*Returns    : NULL
*Note       :
*By         : WGW
*************************************************************
*/
void rtc_setting(void)
{
    int msg[3];

    rtc_set.calendar_set.curr_rtc_time = &current_time;
    rtc_set.alarm_set.curr_alm_time = &current_alarm;

    rtc_set.calendar_set.coordinate = COORDINATE_MIN;
    rtc_set.alarm_set.coordinate = COORDINATE_MIN;

    rtc_set.calendar_set.rtc_set_cnt = 0;
    rtc_set.alarm_set.alm_set_cnt = 0;

    if(rtc_set.rtc_set_mode == RTC_SET_MODE)
        UI_menu(MENU_RTC_MAIN);
    else
        UI_menu(MENU_ALM_SET);

    while(1)
    {
        os_taskq_pend(0, ARRAY_SIZE(msg), msg);

        if(MSG_HALF_SECOND!= msg[0])
        {
            rtc_set.calendar_set.rtc_set_cnt = 0;
            rtc_set.alarm_set.alm_set_cnt = 0;
        }

        switch(msg[0])
        {
//        case MSG_KEY_OK: //确定返回
//            printf("rtc set OK\n");
//            rtc_set.rtc_set_mode = RTC_DISPLAY;
////            ui_display(MSG_UI_RTC_TIME,&rtc_set,sizeof(RTC_SET),1);
//            goto _rtc_setting_exit;

        case MSG_RTC_SETTING://移动光标到下一项
            rtc_set.rtc_set_mode = RTC_SET_MODE;
            rtc_set.calendar_set.coordinate++;

            if(rtc_set.calendar_set.coordinate > COORDINATE_MAX)   //LED显示时只显示“时”、“分”，设置也只设置这两个
            {
                rtc_set.calendar_set.coordinate = COORDINATE_MIN;
            }
            UI_menu(MENU_RTC_MAIN);
            break;

        case MSG_ALM_SETTING://移动光标到下一项
            rtc_set.rtc_set_mode = ALM_SET_MODE;
            rtc_set.alarm_set.coordinate++;

            if(rtc_set.alarm_set.coordinate > COORDINATE_MAX)   //LED显示时只显示“时”、“分”，设置也只设置这两个
            {
                rtc_set.alarm_set.coordinate = COORDINATE_MIN;
            }
            UI_menu(MENU_ALM_SET);
            break;

        case MSG_RTC_PLUS:
            if(rtc_set.rtc_set_mode == RTC_SET_MODE)  //万年历
            {
                calendar_time_plus(rtc_set.calendar_set.curr_rtc_time,rtc_set.calendar_set.coordinate);
                write_rtc_time(rtc_set.calendar_set.curr_rtc_time);
                //rtc_clk_out(rtc_set.calendar_set.curr_rtc_time);
                UI_menu(MENU_RTC_MAIN);
            }
            else if(rtc_set.rtc_set_mode == ALM_SET_MODE)
            {
                calendar_time_plus(rtc_set.alarm_set.curr_alm_time,rtc_set.alarm_set.coordinate);
                write_alm_time(rtc_set.alarm_set.curr_alm_time);
                //rtc_clk_out(rtc_set.alarm_set.curr_alm_time);
                UI_menu(MENU_ALM_SET);
            }
            break;

        case MSG_RTC_MINUS:
            if(rtc_set.rtc_set_mode == RTC_SET_MODE)  	//万年历
            {
                calendar_time_minus(rtc_set.calendar_set.curr_rtc_time,rtc_set.calendar_set.coordinate);
                write_rtc_time(rtc_set.calendar_set.curr_rtc_time);
                //rtc_clk_out(rtc_set.calendar_set.curr_rtc_time);
                UI_menu(MENU_RTC_MAIN);
            }
            else if(rtc_set.rtc_set_mode == ALM_SET_MODE)
            {
                calendar_time_minus(rtc_set.alarm_set.curr_alm_time, rtc_set.alarm_set.coordinate);
                write_alm_time(rtc_set.alarm_set.curr_alm_time);
                //rtc_clk_out(rtc_set.alarm_set.curr_alm_time);
                UI_menu(MENU_ALM_SET);
            }
            break;

        case MSG_ALM_SW:
            //按键开关闹钟时候，自动改为设置闹钟模式
            rtc_set.rtc_set_mode = ALM_SET_MODE;
            if(rtc_set.alarm_set.alarm_sw)
            {
                rtc_set.alarm_set.alarm_sw = 0;
            }
            else
            {
                rtc_set.alarm_set.alarm_sw = 1;
            }
            alm_sw(rtc_set.alarm_set.alarm_sw);
            UI_menu(MENU_ALM_SET);
            break;

        case MSG_HALF_SECOND:
            //时间设置计时
            if(rtc_set.rtc_set_mode == RTC_SET_MODE)
            {
                rtc_set.calendar_set.rtc_set_cnt++;
                //时间设置超时退出
                if(rtc_set.calendar_set.rtc_set_cnt == RTC_SETTING_CNT)
                {
                    rtc_set.calendar_set.rtc_set_cnt = 0;
                    printf("calendar_set timeout\n");
                    goto _rtc_setting_exit;
                }
            }

            if(rtc_set.rtc_set_mode == ALM_SET_MODE)
            {
                rtc_set.alarm_set.alm_set_cnt++;
                if(rtc_set.alarm_set.alm_set_cnt == ALM_SETTING_CNT)
                {
                    rtc_set.alarm_set.alm_set_cnt = 0;
                    printf("Alarm Set TimeOut\n");
                    goto _rtc_setting_exit;
                }
            }
//            UI_menu(MENU_MAIN);
//            UI_menu(MENU_HALF_SEC_REFRESH);
            break;

        default:
            printf("default : %d\n",msg[0]);
            if(msg[0] != MSG_RTC_POWER_DOWN)//MSG_RTC_POWER_DOWN消息返回不转发
                os_taskq_post(RTC_TASK_NAME, 1, msg[0]);//其他非设置的按键将转发回主线程
            goto _rtc_setting_exit;
                break;
        }
    }

_rtc_setting_exit:
    puts("_rtc_setting_exit\n");
    updata_alm_time(rtc_set.calendar_set.curr_rtc_time,rtc_set.alarm_set.curr_alm_time);
    rtc_set.rtc_set_mode = RTC_DISPLAY;
    read_rtc_time(rtc_set.calendar_set.curr_rtc_time);
    UI_menu(MENU_RTC_MAIN);
    return;
}

#endif  /*RTC_CLK_EN*/
