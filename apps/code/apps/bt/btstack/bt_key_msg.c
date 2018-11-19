#include "includes.h"
#include "bt_key_msg.h"
#include "msg.h"

#if 1
#include "key_msg.h"



#ifdef SUPPORT_TM1628_KEY_READ  
   #if LED_KEY_MAX
   const u8 bt_led_table[4][LED_KEY_MAX]=
   #else
   const u8 bt_led_table[4][10] =			  //AD&IO按键转换表
  #endif	 
   {
	   /*短按*/ 	  {LEDKEY_BT_SHORT},
	   /*长按*/ 	  {LEDKEY_BT_LONG},
	   /*连按*/ 	  {LEDKEY_BT_HOLD},
	   /*长按抬起*/ {LEDKEY_BT_LONG_UP},
   };
#endif


#if AD_KEY_MAX
const u8 bt_ad_table[4][AD_KEY_MAX]=
#else
const u8 bt_ad_table[4][10] =
#endif
{
    /*短按*/	    {ADKEY_BT_SHORT},
    /*长按*/		{ADKEY_BT_LONG},
    /*连按*/		{ADKEY_BT_HOLD},
    /*长按抬起*/	{ADKEY_BT_LONG_UP},
};



#if ir_max_num
const u8 bt_ir_table[4][ir_max_num] =
#else 
const u8 bt_ir_table[4][21] =
#endif 
{
    /*短按*/	    {IRFF00_BT_SHORT},
    /*长按*/		{IRFF00_BT_LONG},
    /*连按*/		{IRFF00_BT_HOLD},
    /*长按抬起*/	{IRFF00_BT_LONG_UP},
};
#else
/*蓝牙红外按键表*/
#define IRFF00_BT_SHORT			\
                                /*00*/    MSG_POWER_OFF,\
							    /*01*/    MSG_CHANGE_WORKMODE,\
								/*02*/    MSG_MUTE,\
								/*03*/    MSG_BT_PP,\
								/*04*/    MSG_BT_PREV_FILE,\
								/*05*/    MSG_BT_NEXT_FILE,\
								/*06*/    MSG_BT_MUSIC_EQ,\
								/*07*/    MSG_VOL_DOWN,\
								/*08*/    MSG_VOL_UP,\
								/*09*/    MSG_BT_HID_CTRL,\
                                /*10*/    MSG_BT_HID_TAKE_PIC,\
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

#define IRFF00_BT_LONG			\
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

#define IRFF00_BT_HOLD			\
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


#define IRFF00_BT_LONG_UP 		\
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

const u8 bt_ir_table[4][21] =				//红外遥控转换表
{
    /*短按*/	    {IRFF00_BT_SHORT},
    /*长按*/		{IRFF00_BT_LONG},
    /*连按*/		{IRFF00_BT_HOLD},
    /*长按抬起*/	{IRFF00_BT_LONG_UP},
};

#define ADKEY_BT_SHORT		\
                        /*00*/    MSG_BT_PP,\
                        /*01*/    MSG_BT_NEXT_FILE,\
                        /*02*/    MSG_BT_PREV_FILE,\
                        /*03*/    MSG_BT_CALL_LAST_NO,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    MSG_REC_PP,\
                        /*08*/    MSG_REC_START,\
                        /*09*/    MSG_REC_STOP,

#define ADKEY_BT_LONG		\
                        /*00*/    MSG_CHANGE_WORKMODE,\
                        /*01*/    MSG_VOL_UP,\
                        /*02*/    MSG_VOL_DOWN,\
                        /*03*/    MSG_BT_CALL_REJECT,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,


#define ADKEY_BT_HOLD		\
                        /*00*/    NO_MSG,\
                        /*01*/    MSG_VOL_UP,\
                        /*02*/    MSG_VOL_DOWN,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,

#define ADKEY_BT_LONG_UP	\
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

const u8 bt_ad_table[4][10] =				//AD&IO按键转换表
{
    /*短按*/	    {ADKEY_BT_SHORT},
    /*长按*/		{ADKEY_BT_LONG},
    /*连按*/		{ADKEY_BT_HOLD},
    /*长按抬起*/	{ADKEY_BT_LONG_UP},
};

#endif

#if KEY_IO_EN
#define IOKEY_BT_SHORT		\
                        /*00*/    MSG_BT_PP,\
                        /*01*/    MSG_BT_NEXT_FILE,\
                        /*02*/    MSG_BT_PREV_FILE,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    MSG_BT_CALL_LAST_NO,

#define IOKEY_BT_LONG		\
                        /*00*/    MSG_CHANGE_WORKMODE,\
                        /*01*/    MSG_VOL_UP,\
                        /*02*/    MSG_VOL_DOWN,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,


#define IOKEY_BT_HOLD		\
                        /*00*/    NO_MSG,\
                        /*01*/    MSG_VOL_UP,\
                        /*02*/    MSG_VOL_DOWN,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,

#define IOKEY_BT_LONG_UP	\
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

const u8 bt_io_table[4][10] =				//AD&IO按键转换表
{
    /*短按*/	    {IOKEY_BT_SHORT},
    /*长按*/		{IOKEY_BT_LONG},
    /*连按*/		{IOKEY_BT_HOLD},
    /*长按抬起*/	{IOKEY_BT_LONG_UP},
};
#endif
