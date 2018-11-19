
#include "usb_key.h"
#include "msg.h"

#if USB_PC_EN
#if 1
#include "key_msg.h"

#ifdef SUPPORT_TM1628_KEY_READ  
   #if LED_KEY_MAX
	   const u8 usb_led_table[4][LED_KEY_MAX]=
   #else
	   const u8 usb_led_table[4][10] =			  //AD&IO����ת����
  #endif	 
	   {
		   /*�̰�*/ 	  {LEDKEY_USB_SHORT},
		   /*����*/ 	  {LEDKEY_USB_LONG},
		   /*����*/ 	  {LEDKEY_USB_HOLD},
		   /*����̧��*/ {LEDKEY_USB_LONG_UP},
	   };
#endif

#if AD_KEY_MAX
const u8 adkey_msg_usb_table[4][AD_KEY_MAX]=
#else
const u8 adkey_msg_usb_table[4][10] =
#endif
{
    /*�̰�*/	    {ADKEY_USB_SHORT},
    /*����*/		{ADKEY_USB_LONG},
    /*����*/		{ADKEY_USB_HOLD},
    /*����̧��*/	{ADKEY_USB_LONG_UP},
};
#if KEY_IO_EN

/*******************************************************************
                            I/O������
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
    /*�̰�*/	    {IOKEY_USB_SHORT},
    /*����*/		{IOKEY_USB_LONG},
    /*����*/		{IOKEY_USB_HOLD},
    /*����̧��*/	{IOKEY_USB_LONG_UP},
};
#endif


#if ir_max_num
const u8 irff00_msg_usb_table[4][ir_max_num] =
#else 
const u8 irff00_msg_usb_table[4][21] =
#endif 
{
    /*�̰�*/	    {IRFF00_USB_KEY_SHORT},
    /*����*/		{IRFF00_USB_KEY_LONG},
    /*����*/		{IRFF00_USB_KEY_HOLD},
    /*����̧��*/	{IRFF00_USB_KEY_LONG_UP},
};
#else
/*******************************************************************
                            AD������
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
    /*�̰�*/	    {ADKEY_USB_SHORT},
    /*����*/		{ADKEY_USB_LONG},
    /*����*/		{ADKEY_USB_HOLD},
    /*����̧��*/	{ADKEY_USB_LONG_UP},
};
/*******************************************************************
                            IR������
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
    /*�̰�*/	    {IRFF00_USB_KEY_SHORT},
    /*����*/		{IRFF00_USB_KEY_LONG},
    /*����*/		{IRFF00_USB_KEY_HOLD},
    /*����̧��*/	{IRFF00_USB_KEY_LONG_UP},
};

/*******************************************************************
                            touchkey������
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
    /*�̰�*/	    {TOUCHKEY_USB_SHORT},
    /*����*/		{TOUCHKEY_USB_LONG},
    /*����*/		{TOUCHKEY_USB_HOLD},
    /*����̧��*/	{TOUCHKEY_USB_LONG_UP},
};
#endif
#endif
