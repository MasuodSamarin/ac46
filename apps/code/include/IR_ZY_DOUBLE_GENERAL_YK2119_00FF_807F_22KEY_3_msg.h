

/*******************************************************************
                        IR music   按键表
*******************************************************************/

#define IRFF00_DECODE_KEY_SHORT			\
	/*00*/	  MSG_STANBY_KEY,\
	/*01*/	  MSG_CHANGE_WORKMODE,\
	/*02*/	  MSG_MUTE,\
	/*03*/	  MSG_MUSIC_PP,\
	/*04*/	  MSG_MUSIC_PREV_FILE,\
	/*05*/	  MSG_MUSIC_NEXT_FILE,\
	/*06*/	  MSG_MUSIC_EQ,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  MSG_0,\
	/*10*/	  MSG_MUSIC_RPT,\
	/*11*/	  MSG_FOLDER_NEXT,\
	/*12*/	  MSG_1,\
	/*13*/	  MSG_2,\
	/*14*/	  MSG_3,\
	/*15*/	  MSG_4,\
	/*16*/	  MSG_5,\
	/*17*/	  MSG_6,\
	/*18*/	  MSG_7,\
	/*19*/	  MSG_8,\
	/*20*/	  MSG_9,\
	/*21*/	 MSG_MUSIC_STOP

#if REC_EN
#define IRFF00_DECODE_KEY_LONG			\
	 /*00*/    NO_MSG,\
	 /*01*/    NO_MSG,\
	 /*02*/    NO_MSG,\
	 /*03*/    NO_MSG,\
	 /*04*/    MSG_MUSIC_FR,\
	 /*05*/    MSG_MUSIC_FF,\
	 /*06*/    MSG_ONE_KEY_START_REC,\
	 /*07*/    MSG_VOL_DOWN,\
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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG

#else
#define IRFF00_DECODE_KEY_LONG			\
	 /*00*/    NO_MSG,\
	 /*01*/    NO_MSG,\
	 /*02*/    NO_MSG,\
	 /*03*/    NO_MSG,\
	 /*04*/    MSG_MUSIC_FR,\
	 /*05*/    MSG_MUSIC_FF,\
	 /*06*/    NO_MSG,\
	 /*07*/    MSG_VOL_DOWN,\
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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG
#endif
#define IRFF00_DECODE_KEY_HOLD			\
	 /*00*/    NO_MSG,\
	 /*01*/    NO_MSG,\
	 /*02*/    NO_MSG,\
	 /*03*/    NO_MSG,\
	/*04*/	  MSG_MUSIC_FR,\
	/*05*/	  MSG_MUSIC_FF,\
	 /*06*/    NO_MSG,\
	 /*07*/    MSG_VOL_DOWN,\
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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG



#define IRFF00_DECODE_KEY_LONG_UP 		\
	 /*00*/    NO_MSG,\
	 /*01*/    NO_MSG,\
	 /*02*/    NO_MSG,\
	 /*03*/    NO_MSG,\
	 /*04*/    NO_MSG,\
	 /*05*/    NO_MSG,\
	 /*06*/    NO_MSG,\
	 /*07*/    NO_MSG,\
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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG







/*******************************************************************
                          FM   IR按键表
*******************************************************************/
#define IRFF00_FM_KEY_SHORT			\
	/*00*/	  MSG_STANBY_KEY,\
	/*01*/	  MSG_CHANGE_WORKMODE,\
	/*02*/	  MSG_MUTE,\
	/*03*/	  MSG_FM_SCAN_ALL_INIT,\
	/*04*/	  MSG_FM_PREV_STATION,\
	/*05*/	  MSG_FM_NEXT_STATION,\
	/*06*/	  MSG_REC_STOP,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  MSG_0,\
	/*10*/	  MSG_MUSIC_RPT,\
	/*11*/	  NO_MSG,\
	/*12*/	  MSG_1,\
	/*13*/	  MSG_2,\
	/*14*/	  MSG_3,\
	/*15*/	  MSG_4,\
	/*16*/	  MSG_5,\
	/*17*/	  MSG_6,\
	/*18*/	  MSG_7,\
	/*19*/	  MSG_8,\
	/*20*/	  MSG_9,\
	/*21*/	 NO_MSG

#if REC_EN
#define IRFF00_FM_KEY_LONG			\
	 /*00*/    NO_MSG,\
	 /*01*/    NO_MSG,\
	 /*02*/    NO_MSG,\
	 /*03*/    NO_MSG,\
	 /*04*/    NO_MSG,\
	 /*05*/    NO_MSG,\
	 /*06*/    MSG_REC_START,\
	 /*07*/    MSG_VOL_DOWN,\
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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG
#else
#define IRFF00_FM_KEY_LONG			\
	 /*00*/    NO_MSG,\
	 /*01*/    NO_MSG,\
	 /*02*/    NO_MSG,\
	 /*03*/    NO_MSG,\
	 /*04*/    NO_MSG,\
	 /*05*/    NO_MSG,\
	 /*06*/    NO_MSG,\
	 /*07*/    MSG_VOL_DOWN,\
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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG
#endif	
#define IRFF00_FM_KEY_HOLD			\
	 /*00*/    NO_MSG,\
	 /*01*/    NO_MSG,\
	 /*02*/    NO_MSG,\
	 /*03*/    NO_MSG,\
	 /*04*/    NO_MSG,\
	 /*05*/    NO_MSG,\
	 /*06*/    NO_MSG,\
	 /*07*/    MSG_VOL_DOWN,\
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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG

#define IRFF00_FM_KEY_LONG_UP 		\
	 /*00*/    NO_MSG,\
	 /*01*/    NO_MSG,\
	 /*02*/    NO_MSG,\
	 /*03*/    NO_MSG,\
	 /*04*/    NO_MSG,\
	 /*05*/    NO_MSG,\
	 /*06*/    NO_MSG,\
	 /*07*/    NO_MSG,\
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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG



/*******************************************************************
                     line        IR按键表
*******************************************************************/
#define IRFF00_AUX_KEY_SHORT			\
	/*00*/	  MSG_STANBY_KEY,\
	/*01*/	  MSG_CHANGE_WORKMODE,\
	/*02*/	  MSG_MUTE,\
	/*03*/	  MSG_AUX_PAUSE,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  MSG_REC_STOP,\
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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG,
#if REC_EN
#define IRFF00_AUX_KEY_LONG			\
							/*00*/    NO_MSG,\
							/*01*/    NO_MSG,\
							/*02*/    NO_MSG,\
							/*03*/    NO_MSG,\
							/*04*/    NO_MSG,\
							/*05*/    NO_MSG,\
							/*06*/    MSG_REC_START,\
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
                        	/*20*/	  NO_MSG,\
                        	/*21*/	 NO_MSG

#else
#define IRFF00_AUX_KEY_LONG			\
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
                        	/*20*/	  NO_MSG,\
                        	/*21*/	 NO_MSG

#endif
#define IRFF00_AUX_KEY_HOLD			\
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
                        	/*20*/	  NO_MSG,\
                        	/*21*/	 NO_MSG

#define IRFF00_AUX_KEY_LONG_UP 		\
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
                          	/*20*/	  NO_MSG,\
                          	/*21*/	 NO_MSG



/*******************************************************************
                        IR BT   按键表
*******************************************************************/



#define IRFF00_BT_SHORT			\
	/*00*/	  MSG_STANBY_KEY,\
	/*01*/	  MSG_CHANGE_WORKMODE,\
	/*02*/	  MSG_MUTE,\
	/*03*/	  MSG_BT_PP,\
	/*04*/	  MSG_BT_PREV_FILE,\
	/*05*/	  MSG_BT_NEXT_FILE,\
	/*06*/	  MSG_REC_STOP,\
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
	/*20*/	  MSG_9,\
	/*21*/	 NO_MSG
#if REC_EN
#define IRFF00_BT_LONG			\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  MSG_REC_START,\
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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG
#else			
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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG
#endif
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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG


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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG



/*******************************************************************
                      usb      IR按键表
*******************************************************************/



#define IRFF00_USB_KEY_SHORT			\
	/*00*/	  MSG_STANBY_KEY,\
	/*01*/	  MSG_CHANGE_WORKMODE,\
	/*02*/	  MSG_MUTE,\
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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG
										

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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG

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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG


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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG

#if REC_EN
#define IRFF00_ENC_KEY_SHORT			\
	/*00*/	  MSG_STANBY_KEY,\
	/*01*/	  MSG_CHANGE_WORKMODE,\
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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG



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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG

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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG

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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG

#endif
/*******************************************************************
                     MAIN       IR按键表
*******************************************************************/
#define IRFF00_MAIN_KEY_SHORT			\
	/*00*/	  MSG_STANBY_KEY,\
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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG



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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG


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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG

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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG


/*******************************************************************
                            IR按键表
*******************************************************************/
#define IRFF00_IDLE_KEY_SHORT			\
	/*00*/	  MSG_STANBY_KEY,\
	/*01*/	  MSG_CHANGE_WORKMODE,\
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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG


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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG

#define IRFF00_IDLE_KEY_HOLD			\
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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG


#define IRFF00_IDLE_KEY_LONG_UP 		\
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
	/*20*/	  NO_MSG,\
	/*21*/	 NO_MSG




