#ifndef _RTC_SETTING_H_
#define _RTC_SETTING_H_

#include "includes.h"
#include "irtc.h"

#define RTC_SETTING_CNT 10
#define ALM_SETTING_CNT 10
enum
{
    RTC_YEAR_SETTING = 0x00,
    RTC_MONTH_SETTING,
    RTC_DAT_SETTING,
    RTC_HOUR_SETTING,
    RTC_MIN_SETTING,
    RTC_SEC_SETTING,
};

//以下2个宏设置时钟设置的范围，可根据显示屏的显示范围设置
#define COORDINATE_MIN  RTC_HOUR_SETTING
#define COORDINATE_MAX  RTC_MIN_SETTING

//RTC显示类型
typedef enum
{
    RTC_DISPLAY = 0,    //RTC显示
    RTC_SET_MODE,        //R设置显示
    ALM_SET_MODE,      //闹钟设置显示
}ENUM_RTC_UI;

////闹钟提示音类型
//typedef enum
//{
//    ALARM_MUSIC_DEFAULT = 0, //默认提示音
//    ALARM_MUSIC_SPIFLASH,    //flash里面文件提示音
//    ALARM_MUSIC_LOCAL,       //本地存储设备文件提示音
//}ENUM_ALM_MUSIC;

//typedef struct _RTC_SETTING_VAR
//{
//    u8  bMode;          //<0：RTC 显示模式 1：RTC 设置模式 2：Alarm 设置模式
//    u8  bCoordinate;    //<设置坐标
//    u8  bAlarmOn;       //<闹钟响闹
//    u8  bLastWorkMode;  //<进入闹钟前的工作模式
//    u8  bStandbyCnt;
//}RTC_SETTING_VAR;

typedef struct _ALM_SET_
{
    RTC_TIME *curr_alm_time;   //当前闹钟时间
    u8 coordinate;            //闹钟设置位
    u8 alm_set_cnt;           //闹钟设置超时计数

    u8 alarm_flag;          //闹钟响闹标志
    u8 alarm_sw;            //闹钟开关
    u8 bAlarmOnCnt ;          //闹钟响闹计时

//    u8 alm_ring_mode;         //闹钟响闹模式
//    u8 alm_music_type;        //闹钟响闹提示音类型
}ALM_SET;

typedef struct _RTC_SET_
{
    RTC_TIME *curr_rtc_time;   //当前万年历时间
    u8 coordinate;            //RTC设置位
    u8 rtc_set_cnt;           //rtc设置超时计数
}RTC_SET;

typedef struct _RTC_SET_MODE_
{
    ALM_SET alarm_set;          //闹钟设置
    RTC_SET calendar_set;       //万年历设置
    u8 rtc_set_mode;            //RTC设置模式
}RTC_SETTING;


/*
**********************************************************************
*                           VARIABLES DECLARE
**********************************************************************
*/
extern RTC_SETTING rtc_set;
//extern u8 rtc_set_mode;
/*
**********************************************************************
*                           FUNCTIONS DECLARE
**********************************************************************
*/
void alm_sw(u8 flag);
void rtc_setting(void);
void calendar_time_minus(RTC_TIME *curr_rtc_time,u8 coordinate);
void calendar_time_plus(RTC_TIME *curr_rtc_time,u8 coordinate);

u16 ymd_to_day(RTC_TIME *time);
void day_to_ymd(u16 day,RTC_TIME *rtc_time);
u16 month_to_day(u16 year,u8 month);
u16 year_to_day(u16 year);
tbool leapyear(u16 year);

#endif
