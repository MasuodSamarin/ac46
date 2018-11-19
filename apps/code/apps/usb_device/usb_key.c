
#include "usb_key.h"
#include "msg.h"

#if USB_PC_EN
#if 1
#include "key_msg.h"

#ifdef SUPPORT_TM1628_KEY_READ  
   #if LED_KEY_MAX
	   const u8 usb_led_table[4][LED_KEY_MAX]=
   #else
	   const u8 usb_led_table[4][10] =			  //AD&IO按键转换表
  #endif	 
	   {
		   /*短按*/ 	  {LEDKEY_USB_SHORT},
		   /*长按*/ 	  {LEDKEY_USB_LONG},
		   /*连按*/ 	  {LEDKEY_USB_HOLD},
		   /*长按抬起*/ {LEDKEY_USB_LONG_UP},
	   };
#endif

#if AD_KEY_MAX
const u8 adkey_msg_usb_table[4][AD_KEY_MAX]=
#else
const u8 adkey_msg_usb_table[4][10] =
#endif
{
    /*短按*/	    {ADKEY_USB_SHORT},
    /*长按*/		{ADKEY_USB_LONG},
    /*连按*/		{ADKEY_USB_HOLD},
    /*长按抬起*/	{ADKEY_USB_LONG_UP},
};
#if KEY_IO_EN

/*******************************************************************
                            I/O按键表
*******************************************************************/
#define IOKEY_USB_SHORT		\
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

#define IOKEY_USB_LONG		\
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


#define IOKEY_USB_HOLD		\
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

#define IOKEY_USB_LONG_UP	\
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

const u8 iokey_msg_usb_table[4][10] =
{
    /*短按*/	    {IOKEY_USB_SHORT},
    /*长按*/		{IOKEY_USB_LONG},
    /*连按*/		{IOKEY_USB_HOLD},
    /*长按抬起*/	{IOKEY_USB_LONG_UP},
};
#endif


#if ir_max_num
const u8 irff00_msg_usb_table[4][ir_max_num] =
#else 
const u8 irff00_msg_usb_table[4][21] =
#endif 
{
    /*短按*/	    {IRFF00_USB_KEY_SHORT},
    /*长按*/		{IRFF00_USB_KEY_LONG},
    /*连按*/		{IRFF00_USB_KEY_HOLD},
    /*长按抬起*/	{IRFF00_USB_KEY_LONG_UP},
};
#else
/*******************************************************************
                            AD按键表
*******************************************************************/
#define ADKEY_USB_SHORT		\
                        /*00*/    MSG_PC_MUTE,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    MSG_PC_PLAY_PREV,\
                        /*04*/    MSG_PC_PLAY_NEXT,\
                        /*05*/    MSG_PC_PP,\
                        /*06*/    MSG_PC_VOL_DOWN,\
                        /*07*/    MSG_PC_VOL_UP,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,

#define ADKEY_USB_LONG		\
                        /*00*/    MSG_CHANGE_WORKMODE,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,


#define ADKEY_USB_HOLD		\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    MSG_PC_VOL_DOWN,\
                        /*07*/    MSG_PC_VOL_UP,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,

#define ADKEY_USB_LONG_UP	\
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

const u8 adkey_msg_usb_table[4][10] =
{
    /*短按*/	    {ADKEY_USB_SHORT},
    /*长按*/		{ADKEY_USB_LONG},
    /*连按*/		{ADKEY_USB_HOLD},
    /*长按抬起*/	{ADKEY_USB_LONG_UP},
};
/*******************************************************************
                            IR按键表
*******************************************************************/
#define IRFF00_USB_KEY_SHORT			\
                                /*00*/    MSG_POWER_OFF,\
							    /*01*/    MSG_CHANGE_WORKMODE,\
								/*02*/    MSG_PC_MUTE,\
								/*03*/    MSG_PC_PP,\
								/*04*/    MSG_PC_PLAY_PREV,\
								/*05*/    MSG_PC_PLAY_NEXT,\
								/*06*/    NO_MSG,\
								/*07*/    MSG_PC_VOL_DOWN,\
								/*08*/    MSG_PC_VOL_UP,\
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


#define IRFF00_USB_KEY_LONG			\
								/*00*/    NO_MSG,\
                                /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    MSG_PC_VOL_DOWN,\
								/*08*/    MSG_PC_VOL_UP,\
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

#define IRFF00_USB_KEY_HOLD			\
								/*00*/    NO_MSG,\
                                /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    MSG_PC_VOL_DOWN,\
								/*08*/    MSG_PC_VOL_UP,\
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


#define IRFF00_USB_KEY_LONG_UP 		\
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
const u8 irff00_msg_usb_table[4][21] =
{
    /*短按*/	    {IRFF00_USB_KEY_SHORT},
    /*长按*/		{IRFF00_USB_KEY_LONG},
    /*连按*/		{IRFF00_USB_KEY_HOLD},
    /*长按抬起*/	{IRFF00_USB_KEY_LONG_UP},
};

/*******************************************************************
                            touchkey按键表
*******************************************************************/
#define TOUCHKEY_USB_SHORT		\
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

#define TOUCHKEY_USB_LONG		\
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


#define TOUCHKEY_USB_HOLD		\
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

#define TOUCHKEY_USB_LONG_UP	\
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

const u8 touchkey_msg_usb_table[4][10] =
{
    /*短按*/	    {TOUCHKEY_USB_SHORT},
    /*长按*/		{TOUCHKEY_USB_LONG},
    /*连按*/		{TOUCHKEY_USB_HOLD},
    /*长按抬起*/	{TOUCHKEY_USB_LONG_UP},
};
#endif
#endif
