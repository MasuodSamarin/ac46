#include "rtc_key.h"
#include "msg.h"
#include "config.h"

#if RTC_CLK_EN
#if 1
#include "key_msg.h"
#if AD_KEY_MAX
const u8 rtc_ad_table[4][AD_KEY_MAX]=
#else
const u8 rtc_ad_table[4][10] =
#endif
{
    /*短按*/	    {ADKEY_RTC_SHORT},
    /*长按*/		{ADKEY_RTC_LONG},
    /*连按*/		{ADKEY_RTC_HOLD},
    /*长按抬起*/	{ADKEY_RTC_LONG_UP},
};

#if ir_max_num
const u8 rtc_ir_table[4][ir_max_num] =
#else 
const u8 rtc_ir_table[4][21] =
#endif 
{
    /*短按*/	    {IRFF00_RTC_KEY_SHORT},
    /*长按*/		{IRFF00_RTC_KEY_LONG},
    /*连按*/		{IRFF00_RTC_KEY_HOLD},
    /*长按抬起*/	{IRFF00_RTC_KEY_LONG_UP},
};
#else
/*******************************************************************
                            AD按键表
*******************************************************************/
#define ADKEY_RTC_SHORT		\
                        /*00*/    MSG_RTC_POWER_DOWN,\
                        /*01*/    MSG_RTC_SETTING,\
                        /*02*/    MSG_ALM_SETTING,\
                        /*03*/    MSG_RTC_PLUS,\
                        /*04*/    MSG_RTC_MINUS,\
                        /*05*/    MSG_ALM_SW,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,

#define ADKEY_RTC_LONG		\
                        /*00*/    MSG_CHANGE_WORKMODE,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    MSG_RTC_PLUS,\
                        /*04*/    MSG_RTC_MINUS,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,


#define ADKEY_RTC_HOLD		\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    MSG_RTC_PLUS,\
                        /*04*/    MSG_RTC_MINUS,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,

#define ADKEY_RTC_LONG_UP	\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,

const u8 rtc_ad_table[4][10] =
{
    /*短按*/	    {ADKEY_RTC_SHORT},
    /*长按*/		{ADKEY_RTC_LONG},
    /*连按*/		{ADKEY_RTC_HOLD},
    /*长按抬起*/	{ADKEY_RTC_LONG_UP},
};

/*******************************************************************
                            I/O按键表
*******************************************************************/
#define IOKEY_RTC_SHORT		\
                        /*00*/    MSG_RTC_POWER_DOWN,\
                        /*01*/    MSG_RTC_SETTING,\
                        /*02*/    MSG_ALM_SETTING,\
                        /*03*/    MSG_RTC_PLUS,\
                        /*04*/    MSG_RTC_MINUS,\
                        /*05*/    MSG_ALM_SW,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,

#define IOKEY_RTC_LONG		\
                        /*00*/    MSG_CHANGE_WORKMODE,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    MSG_RTC_PLUS,\
                        /*04*/    MSG_RTC_MINUS,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,


#define IOKEY_RTC_HOLD		\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    MSG_RTC_PLUS,\
                        /*04*/    MSG_RTC_MINUS,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,

#define IOKEY_RTC_LONG_UP	\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,

const u8 rtc_io_table[4][10] =
{
    /*短按*/	    {IOKEY_RTC_SHORT},
    /*长按*/		{IOKEY_RTC_LONG},
    /*连按*/		{IOKEY_RTC_HOLD},
    /*长按抬起*/	{IOKEY_RTC_LONG_UP},
};

/*******************************************************************
                            IR按键表
*******************************************************************/
#define IRFF00_RTC_KEY_SHORT			\
                                /*00*/    MSG_POWER_OFF,\
							    /*01*/    MSG_CHANGE_WORKMODE,\
								/*02*/    MSG_ALM_SW,\
								/*03*/    MSG_RTC_SETTING,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    MSG_ALM_SETTING,\
								/*07*/    MSG_RTC_MINUS,\
								/*08*/    MSG_RTC_PLUS,\
								/*09*/    NO_MSG,\
                                /*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
								/*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG


#define IRFF00_RTC_KEY_LONG			\
								/*00*/    NO_MSG,\
                                /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    MSG_VOL_DOWN,\
								/*08*/    MSG_VOL_UP,\
								/*09*/    NO_MSG,\
                                /*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
								/*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG

#define IRFF00_RTC_KEY_HOLD			\
								/*00*/    NO_MSG,\
                                /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    MSG_VOL_DOWN,\
								/*08*/    MSG_VOL_UP,\
								/*09*/    NO_MSG,\
                                /*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
								/*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG


#define IRFF00_RTC_KEY_LONG_UP 		\
								/*00*/    NO_MSG,\
                                /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    NO_MSG,\
								/*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
								/*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
                                /*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG
const u8 rtc_ir_table[4][21] =
{
    /*短按*/	    {IRFF00_RTC_KEY_SHORT},
    /*长按*/		{IRFF00_RTC_KEY_LONG},
    /*连按*/		{IRFF00_RTC_KEY_HOLD},
    /*长按抬起*/	{IRFF00_RTC_KEY_LONG_UP},
};


/*******************************************************************
                            touchkey按键表
*******************************************************************/
#define TOUCHKEY_RTC_SHORT		\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,

#define TOUCHKEY_RTC_LONG		\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,


#define TOUCHKEY_RTC_HOLD		\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,

#define TOUCHKEY_RTC_LONG_UP	\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,

const u8 rtc_touch_table[4][10] =
{
    /*短按*/	    {TOUCHKEY_RTC_SHORT},
    /*长按*/		{TOUCHKEY_RTC_LONG},
    /*连按*/		{TOUCHKEY_RTC_HOLD},
    /*长按抬起*/	{TOUCHKEY_RTC_LONG_UP},
};
#endif
#endif
