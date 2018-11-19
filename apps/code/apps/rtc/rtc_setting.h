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

//����2��������ʱ�����õķ�Χ���ɸ�����ʾ������ʾ��Χ����
#define COORDINATE_MIN  RTC_HOUR_SETTING
#define COORDINATE_MAX  RTC_MIN_SETTING

//RTC��ʾ����
typedef enum
{
    RTC_DISPLAY = 0,    //RTC��ʾ
    RTC_SET_MODE,        //R������ʾ
    ALM_SET_MODE,      //����������ʾ
}ENUM_RTC_UI;

////������ʾ������
//typedef enum
//{
//    ALARM_MUSIC_DEFAULT = 0, //Ĭ����ʾ��
//    ALARM_MUSIC_SPIFLASH,    //flash�����ļ���ʾ��
//    ALARM_MUSIC_LOCAL,       //���ش洢�豸�ļ���ʾ��
//}ENUM_ALM_MUSIC;

//typedef struct _RTC_SETTING_VAR
//{
//    u8  bMode;          //<0��RTC ��ʾģʽ 1��RTC ����ģʽ 2��Alarm ����ģʽ
//    u8  bCoordinate;    //<��������
//    u8  bAlarmOn;       //<��������
//    u8  bLastWorkMode;  //<��������ǰ�Ĺ���ģʽ
//    u8  bStandbyCnt;
//}RTC_SETTING_VAR;

typedef struct _ALM_SET_
{
    RTC_TIME *curr_alm_time;   //��ǰ����ʱ��
    u8 coordinate;            //��������λ
    u8 alm_set_cnt;           //�������ó�ʱ����

    u8 alarm_flag;          //�������ֱ�־
    u8 alarm_sw;            //���ӿ���
    u8 bAlarmOnCnt ;          //�������ּ�ʱ

//    u8 alm_ring_mode;         //��������ģʽ
//    u8 alm_music_type;        //����������ʾ������
}ALM_SET;

typedef struct _RTC_SET_
{
    RTC_TIME *curr_rtc_time;   //��ǰ������ʱ��
    u8 coordinate;            //RTC����λ
    u8 rtc_set_cnt;           //rtc���ó�ʱ����
}RTC_SET;

typedef struct _RTC_SET_MODE_
{
    ALM_SET alarm_set;          //��������
    RTC_SET calendar_set;       //����������
    u8 rtc_set_mode;            //RTC����ģʽ
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
