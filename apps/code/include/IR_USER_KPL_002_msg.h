
#if 0

#define       IRC_ADD100				0 /*21*/
#define       IRC_MODE                         	1      /*01*/
#define       IRC_MUTE       			     2 /*22*/
#define       IRC_PLAY_PAUSE             3     /*03*/ 
#define       IRC_PREV                         4     /*04*/
#define       IRC_NEXT                          5   /*05*/  
#define       IRC_EQ                             6   /*06*/
#define       IRC_VOL_DN                   7       /*07*/ 
#define       IRC_VOL_UP                    8/*08*/ 
#define       IRC_NUM0                             9  /*09*/ 
#define       IRC_CHINC                   10/*10*/ 
#define       IRC_CHDEC				11/*11*/
#define       IRC_NUM1                             12 /*12*/
#define       IRC_NUM2                             13/*13*/
#define       IRC_NUM3                            14/*14*/
#define       IRC_NUM4                            15/*15*/
#define       IRC_NUM5                            16/*16*/ 
#define       IRC_NUM6                            17/*17*/ 
#define       IRC_NUM7                            18/*18*/ 
#define       IRC_NUM8                            19/*19*/
#define       IRC_NUM9                            20 /*20*/

#endif

/*******************************************************************
                        IR music   按键表
*******************************************************************/

#define IRFF00_DECODE_KEY_SHORT			\
	/*00*/	  MSG_ADD_100,\
	/*01*/	  MSG_CHANGE_WORKMODE,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_MUSIC_RPT,\
	/*04*/	  MSG_MUSIC_PREV_FILE,\
	/*05*/	  MSG_MUSIC_NEXT_FILE,\
	/*06*/	  MSG_MUSIC_EQ,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  MSG_0,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  MSG_1,\
	/*13*/	  MSG_2,\
	/*14*/	  MSG_3,\
	/*15*/	  MSG_4,\
	/*16*/	  MSG_5,\
	/*17*/	  MSG_6,\
	/*18*/	  MSG_7,\
	/*19*/	  MSG_8,\
	/*20*/	  MSG_9

#define IRFF00_DECODE_KEY_LONG			\
	/*00*/     NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  MSG_MUSIC_FR,\
	/*05*/	  MSG_MUSIC_FF,\
	/*06*/	  NO_MSG,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG
#define IRFF00_DECODE_KEY_HOLD			\
	/*00*/     NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

#define IRFF00_DECODE_KEY_LONG_UP 		\
	/*00*/     NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

/*******************************************************************
                          FM   IR按键表
*******************************************************************/
#define IRFF00_FM_KEY_SHORT			\
	/*00*/	  MSG_STANBY_KEY,\
	/*01*/	  MSG_CHANGE_WORKMODE,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_FM_PP,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  MSG_MUSIC_EQ,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  MSG_0,\
	/*10*/	  MSG_FM_NEXT_STATION,\
	/*11*/	  MSG_FM_PREV_STATION,\
	/*12*/	  MSG_1,\
	/*13*/	  MSG_2,\
	/*14*/	  MSG_3,\
	/*15*/	  MSG_4,\
	/*16*/	  MSG_5,\
	/*17*/	  MSG_6,\
	/*18*/	  MSG_7,\
	/*19*/	  MSG_8,\
	/*20*/	  MSG_9
#define IRFF00_FM_KEY_LONG			\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_FM_SCAN_ALL_INIT,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG
#define IRFF00_FM_KEY_HOLD			\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

#define IRFF00_FM_KEY_LONG_UP 		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

/*******************************************************************
                     line        IR按键表
*******************************************************************/
#define IRFF00_AUX_KEY_SHORT			\
	/*00*/	  MSG_STANBY_KEY,\
	/*01*/	  MSG_CHANGE_WORKMODE,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_AUX_PAUSE,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG
#define IRFF00_AUX_KEY_LONG			\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

#define IRFF00_AUX_KEY_HOLD			\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

#define IRFF00_AUX_KEY_LONG_UP 		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

/*******************************************************************
                        IR BT   按键表
*******************************************************************/
#define IRFF00_BT_SHORT			\
	/*00*/	  MSG_STANBY_KEY,\
	/*01*/	  MSG_CHANGE_WORKMODE,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_BT_PP,\
	/*04*/	  MSG_BT_PREV_FILE,\
	/*05*/	  MSG_BT_NEXT_FILE,\
	/*06*/	  NO_MSG,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG
	
#define IRFF00_BT_LONG			\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

#define IRFF00_BT_HOLD			\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

#define IRFF00_BT_LONG_UP 		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG
/*******************************************************************
                      usb      IR按键表
*******************************************************************/
#define IRFF00_USB_KEY_SHORT			\
	/*00*/	  MSG_STANBY_KEY,\
	/*01*/	  MSG_CHANGE_WORKMODE,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_PC_PP,\
	/*04*/	  MSG_PC_PLAY_PREV,\
	/*05*/	  MSG_PC_PLAY_NEXT,\
	/*06*/	  NO_MSG,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

#define IRFF00_USB_KEY_LONG			\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

#define IRFF00_USB_KEY_HOLD			\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

#define IRFF00_USB_KEY_LONG_UP 		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

//record mode key
#if REC_EN
#define IRFF00_ENC_KEY_SHORT			\
	/*00*/	  MSG_REC_INIT,\
	/*01*/	  MSG_CHANGE_WORKMODE,\
	/*02*/	  MSG_REC_PP,\
	/*03*/	  MSG_REC_START,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

#define IRFF00_ENC_KEY_LONG			\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

#define IRFF00_ENC_KEY_HOLD			\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

#define IRFF00_ENC_KEY_LONG_UP 		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

#endif

//rtc alarm key
#if RTC_CLK_EN
#define IRFF00_RTC_KEY_SHORT			\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

#define IRFF00_RTC_KEY_LONG			\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

#define IRFF00_RTC_KEY_HOLD			\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

#define IRFF00_RTC_KEY_LONG_UP 		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

#endif

/*******************************************************************
                     MAIN       IR按键表
*******************************************************************/
#define IRFF00_MAIN_KEY_SHORT			\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

#define IRFF00_MAIN_KEY_LONG			\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

#define IRFF00_MAIN_KEY_HOLD			\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

#define IRFF00_MAIN_KEY_LONG_UP 		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

/*******************************************************************
                            IR按键表
*******************************************************************/
#define IRFF00_IDLE_KEY_SHORT			\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG
#define IRFF00_IDLE_KEY_LONG			\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

#define IRFF00_IDLE_KEY_HOLD			\
	/*00*/	  NO_MSG,\
	/*01*/    NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*10*/    NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG

#define IRFF00_IDLE_KEY_LONG_UP 		\
	/*00*/	  NO_MSG,\
	/*01*/	NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*10*/	  NO_MSG,\
	/*11*/	  NO_MSG,\
	/*12*/	  NO_MSG,\
	/*13*/	  NO_MSG,\
	/*14*/	  NO_MSG,\
	/*15*/	  NO_MSG,\
	/*16*/	  NO_MSG,\
	/*17*/	  NO_MSG,\
	/*18*/	  NO_MSG,\
	/*19*/	  NO_MSG,\
	/*20*/	  NO_MSG


