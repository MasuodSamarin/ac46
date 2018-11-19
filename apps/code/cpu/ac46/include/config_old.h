/*--------------------------------------------------------------------------*/
/**@file     config.h
   @brief    ϵͳ����
   @details
   @author
   @date    2011-3-7
   @note    CD003
*/
/*----------------------------------------------------------------------------*/

#ifndef _CONFIG_
#define _CONFIG_

#include "typedef.h"
#include "common.h"
#include "printf.h"
#include "uart.h"
#include "interrupt.h"
#include "string.h"


#if 1
/*
*********************************************************************
                        DEBUG MACRO
*********************************************************************
*/
#define __DEBUG         ////<����ϵͳ��ӡ���Թ���


/*
*********************************************************************
                        COMMON MACRO
*********************************************************************
*/
#define EQ_FILTER_EN            0    ///<EQ�˲�������
#define PA_EN                   0    ///<����mute����
#define SYS_LVD_EN              1    ///<ϵͳ�͵���
#define S10_MODE                0    ///<0:��ͨSDK     1:S10��������
#define POWERUP_DEFAULT_MODE    1    ///<�ϵ�Ĭ��ģʽʹ��
#ifndef BT_TESTER
#define LED_EN                  1    ///<LEDָʾʹ��
#define KEY_TONE_EN             1    ///<������ʹ��
#else
#define LED_EN                  0    ///<LEDָʾʹ��
#define KEY_TONE_EN             0    ///<������ʹ��
#endif

#define SYS_DEFAULT_VOL_EN      0    ///<ϵͳ����Ĭ������ʹ��
#if SYS_DEFAULT_VOL_EN
#define SYS_DEFAULT_VOL         25   ///<ϵͳ����Ĭ������ֵ
#endif

#if S10_MODE
#define KEY_DOUBLE_CLICK             ///<����˫������
#define DAC_SOUNDTRACK_COMPOUND 1    ///<DAC�����ϳ�
#else
#define DAC_SOUNDTRACK_COMPOUND 0    ///<DAC�����ϳ�
#endif/*S10_MODE*/

#ifdef AC46_512K
    #define BT_PHONE_NUMBER     0          //���籨��
#else
    #define BT_PHONE_NUMBER     1          //���籨��
#endif
/*
*********************************************************************
                        REC MACRO
*********************************************************************
*/
#ifdef AC46_512K
    #define REC_EN         0         ///512K_SDK
#else
    #define REC_EN         1         ///��׼SDK
#endif


/*
*********************************************************************
                        FM MACRO
*********************************************************************
*/
#ifdef AC46_512K
    #define FM_RADIO_EN         0       ///512K_SDK
#else
    #define FM_RADIO_EN         1       ///��׼SDK
#endif

/*
*********************************************************************
                        RTC MACRO
*********************************************************************
*/
#ifdef AC46_512K
    #define RTC_CLK_EN              0       ///<512K_SDK RTCʱ��ģʽ
    #define RTC_ALM_EN          	0       ///<512K_SDK RTC����ģʽ
#else

    #define RTC_CLK_EN              1       ///<��׼SDK RTCʱ��ģʽ
    #if RTC_CLK_EN
        #define RTC_ALM_EN          1       ///<��׼SDK RTC����ģʽ
    #endif

#endif

/*
*********************************************************************
                        BT MACRO
*********************************************************************
*/
//���ò��Ժв��Թ���
#define NON_TEST         0       //ûƵƫ�;������
#define FRE_OFFSET_TEST  BIT(0)  //Ƶƫ����
#define DISTANCE_TEST    BIT(1)  //�������




#define NORMAL_MODE         0
#define TEST_INDEX_MODE     1     //ָ�����ܲ���(ʹ��MT8852A��������,����֤��ʱ��ʹ��)
#define TEST_FCC_MODE       2     //����fcc��֤
#define TEST_FRE_OFF_MODE   3     //����Ƶƫ(ʹ��Ƶ�׷�����-���������-����Ƶ��Ĭ��2422M)
#define TEST_PERFOR_MODE    4    //ָ�����ܲ���(ʹ��MT8852A��������,����оƬ���ܵ�ʱ��ʹ��)


#define BT_MODE        NORMAL_MODE
#ifndef BT_TESTER
#define BT_BACKMODE         0             //¼����������̨���ܹ���
#if !BT_BACKMODE
    #define BT_HID_INDEPENDENT_MODE  0    //HID���յĶ���ģʽֻ֧�ַǺ�̨
#endif
#else
#define BT_BACKMODE         0
#endif
/*
*********************************************************************
                        UART MACRO
*********************************************************************
*/


#define UART0   0
#define UART1   1
#define UART2   2
#define UART_NO 0xFF

#ifdef __DEBUG
#if S10_MODE
#define S10_UART_DEBUG    0
#if S10_UART_DEBUG
#define DEBUG_UART   UART1
#else
#define DEBUG_UART   UART_NO
#endif/*S10_UART_DEBUG*/
#else
#ifdef BT_TESTER
#define DEBUG_UART   UART1  /*��׼SDK��ӡ��*/
#else
#define DEBUG_UART   UART0  /*��׼SDK��ӡ��*/
#endif
#endif/*S10_MODE*/

#else
#define DEBUG_UART UART_NO
#endif/*__DEBUG*/

/*
*********************************************************************
                        DAC MACRO
*********************************************************************
*/
#define DAC_EN          1
#if DAC_EN
#define DAC_FADE_EN     1
#else
#define DAC_FADE_EN     0
#endif

/*
*********************************************************************
                        DEVICE MACRO
*********************************************************************
*/
#ifdef BT_TESTER
    #define SDMMC0_EN       0    ///<SD0ʹ��
    #define SDMMC1_EN       0    ///<SD1ʹ��
#else
    #if S10_MODE
    #define SDMMC0_EN       1
    #define SDMMC1_EN       0
    #else
    #define SDMMC0_EN       1
    #define SDMMC1_EN       1
    #endif/*S10_MODE*/
#endif

#ifdef AC46_512K
    #define USB_DISK_EN     0    ///<512K ����� U�� PC ����
    #define USB_PC_EN       0    ///<512K ����� U�� PC ����
#else
    #if S10_MODE
        #define USB_DISK_EN     0    ///<U��ʹ��
        #define USB_PC_EN       0    ///<PCʹ��
    #else
        #define USB_DISK_EN     1    ///<��׼SDK
        #define USB_PC_EN       1    ///<��׼SDK
    #endif/*S10_MODE*/
#endif

#define SPI_FLASH_BLK_NUM   8
#define POWERUP_DEV_IGNORE       ///<�����豸�ϵ��Ƿ���ӦU�̻�SD
#define AUX_OUT_WITHOUT_CNT
/*
*********************************************************************
                        UI MACRO
*********************************************************************
*/

#ifdef BT_TESTER
    #define UI_ENABLE           0     ///>UI_��ʾ
#else

    #ifdef AC46_512K
        #define UI_ENABLE       0     ///>512K_SDK UI_��ʾ
    #else
        #define UI_ENABLE       1     ///>��׼SDK UI_��ʾ
    #endif
#endif
#endif
#endif
