

/*******************************************************************
                        IR music   按键表
*******************************************************************/
#define IRFF00_DECODE_KEY_SHORT			\
/*00*/    MSG_ONE_KEY_TO_RADIO,\
/*01*/    MSG_ONE_KEY_TO_MP3,\
/*02*/    MSG_ONE_KEY_TO_BT,\
/*03*/    MSG_ONE_KEY_TO_USB,\
/*04*/    MSG_ONE_KEY_TO_SD,\
/*05*/    MSG_ONE_KEY_TO_AUX,\
/*06*/    MSG_MUSIC_PREV_FILE,\
/*07*/    MSG_MUSIC_NEXT_FILE,\
/*08*/    MSG_MUSIC_PP,\
/*09*/    MSG_CHANGE_WORKMODE

#define IRFF00_DECODE_KEY_LONG			\
/*00*/	  NO_MSG,\
/*01*/	  NO_MSG,\
/*02*/	  NO_MSG,\
/*03*/	  NO_MSG,\
/*04*/	  NO_MSG,\
/*05*/	  NO_MSG,\
/*06*/	  MSG_VOL_DOWN,\
/*07*/	  MSG_VOL_UP,\
/*08*/	  NO_MSG,\
/*09*/	  MSG_STANBY_KEY

#define IRFF00_DECODE_KEY_HOLD			\
/*00*/	  NO_MSG,\
/*01*/	  NO_MSG,\
/*02*/	  NO_MSG,\
/*03*/	  NO_MSG,\
/*04*/	  NO_MSG,\
/*05*/	  NO_MSG,\
/*06*/	  MSG_VOL_DOWN,\
/*07*/	  MSG_VOL_UP,\
/*08*/	  NO_MSG,\
/*09*/	  NO_MSG

#define IRFF00_DECODE_KEY_LONG_UP 		\
/*00*/    NO_MSG,\
/*01*/    NO_MSG,\
/*02*/    NO_MSG,\
/*03*/    NO_MSG,\
/*04*/    NO_MSG,\
/*05*/    NO_MSG,\
/*06*/    NO_MSG,\
/*07*/    NO_MSG,\
/*08*/    NO_MSG,\
/*09*/    NO_MSG

/*******************************************************************
                          FM   IR按键表
*******************************************************************/
#define IRFF00_FM_KEY_SHORT			\
/*00*/	  MSG_ONE_KEY_TO_RADIO,\
/*01*/	  MSG_ONE_KEY_TO_MP3,\
/*02*/	  MSG_ONE_KEY_TO_BT,\
/*03*/	  MSG_ONE_KEY_TO_USB,\
/*04*/	  MSG_ONE_KEY_TO_SD,\
/*05*/	  MSG_ONE_KEY_TO_AUX,\
/*06*/	  MSG_FM_PREV_STATION,\
/*07*/	  MSG_FM_NEXT_STATION,\
/*08*/	  MSG_FM_SCAN_ALL_INIT,\
/*09*/	  MSG_CHANGE_WORKMODE

#define IRFF00_FM_KEY_LONG			\
/*00*/	  NO_MSG,\
/*01*/	  NO_MSG,\
/*02*/	  NO_MSG,\
/*03*/	  NO_MSG,\
/*04*/	  NO_MSG,\
/*05*/	  NO_MSG,\
/*06*/	  MSG_VOL_DOWN,\
/*07*/	  MSG_VOL_UP,\
/*08*/	  NO_MSG,\
/*09*/	  MSG_STANBY_KEY
#define IRFF00_FM_KEY_HOLD			\
/*00*/	  NO_MSG,\
/*01*/	  NO_MSG,\
/*02*/	  NO_MSG,\
/*03*/	  NO_MSG,\
/*04*/	  NO_MSG,\
/*05*/	  NO_MSG,\
/*06*/	  MSG_VOL_DOWN,\
/*07*/	  MSG_VOL_UP,\
/*08*/	  NO_MSG,\
/*09*/	  NO_MSG

#define IRFF00_FM_KEY_LONG_UP 		\
/*00*/    NO_MSG,\
/*01*/    NO_MSG,\
/*02*/    NO_MSG,\
/*03*/    NO_MSG,\
/*04*/    NO_MSG,\
/*05*/    NO_MSG,\
/*06*/    NO_MSG,\
/*07*/    NO_MSG,\
/*08*/    NO_MSG,\
/*09*/    NO_MSG

/*******************************************************************
                     line        IR按键表
*******************************************************************/
#define IRFF00_AUX_KEY_SHORT			\
/*00*/	  MSG_ONE_KEY_TO_RADIO,\
/*01*/	  MSG_ONE_KEY_TO_MP3,\
/*02*/	  MSG_ONE_KEY_TO_BT,\
/*03*/	  MSG_ONE_KEY_TO_USB,\
/*04*/	  MSG_ONE_KEY_TO_SD,\
/*05*/	  MSG_ONE_KEY_TO_AUX,\
/*06*/	  NO_MSG,\
/*07*/	  NO_MSG,\
/*08*/	  MSG_AUX_PAUSE,\
/*09*/	  MSG_CHANGE_WORKMODE

#define IRFF00_AUX_KEY_LONG			\
/*00*/	  NO_MSG,\
/*01*/	  NO_MSG,\
/*02*/	  NO_MSG,\
/*03*/	  NO_MSG,\
/*04*/	  NO_MSG,\
/*05*/	  NO_MSG,\
/*06*/	  MSG_VOL_DOWN,\
/*07*/	  MSG_VOL_UP,\
/*08*/	  NO_MSG,\
/*09*/	  MSG_STANBY_KEY

#define IRFF00_AUX_KEY_HOLD			\
/*00*/	  NO_MSG,\
/*01*/	  NO_MSG,\
/*02*/	  NO_MSG,\
/*03*/	  NO_MSG,\
/*04*/	  NO_MSG,\
/*05*/	  NO_MSG,\
/*06*/	  MSG_VOL_DOWN,\
/*07*/	  MSG_VOL_UP,\
/*08*/	  NO_MSG,\
/*09*/	  NO_MSG

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
/*09*/    NO_MSG

/*******************************************************************
                        IR BT   按键表
*******************************************************************/

#define IRFF00_BT_SHORT			\
/*00*/	  MSG_ONE_KEY_TO_RADIO,\
/*01*/	  MSG_ONE_KEY_TO_MP3,\
/*02*/	  MSG_ONE_KEY_TO_BT,\
/*03*/	  MSG_ONE_KEY_TO_USB,\
/*04*/	  MSG_ONE_KEY_TO_SD,\
/*05*/	  MSG_ONE_KEY_TO_AUX,\
/*06*/	  MSG_BT_PREV_FILE,\
/*07*/	  MSG_BT_NEXT_FILE,\
/*08*/	  MSG_BT_PP,\
/*09*/	  MSG_CHANGE_WORKMODE
			
#define IRFF00_BT_LONG			\
/*00*/	  NO_MSG,\
/*01*/	  NO_MSG,\
/*02*/	  NO_MSG,\
/*03*/	  NO_MSG,\
/*04*/	  NO_MSG,\
/*05*/	  NO_MSG,\
/*06*/	  MSG_VOL_DOWN,\
/*07*/	  MSG_VOL_UP,\
/*08*/	  NO_MSG,\
/*09*/	  MSG_STANBY_KEY

#define IRFF00_BT_HOLD			\
/*00*/	  NO_MSG,\
/*01*/	  NO_MSG,\
/*02*/	  NO_MSG,\
/*03*/	  NO_MSG,\
/*04*/	  NO_MSG,\
/*05*/	  NO_MSG,\
/*06*/	  MSG_VOL_DOWN,\
/*07*/	  MSG_VOL_UP,\
/*08*/	  NO_MSG,\
/*09*/	  NO_MSG

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
/*09*/    NO_MSG

/*******************************************************************
                      usb      IR按键表
*******************************************************************/
#define IRFF00_USB_KEY_SHORT			\
/*00*/	  MSG_ONE_KEY_TO_RADIO,\
/*01*/	  MSG_ONE_KEY_TO_MP3,\
/*02*/	  MSG_ONE_KEY_TO_BT,\
/*03*/	  MSG_ONE_KEY_TO_USB,\
/*04*/	  MSG_ONE_KEY_TO_SD,\
/*05*/	  MSG_ONE_KEY_TO_AUX,\
/*06*/	  MSG_PC_PLAY_PREV,\
/*07*/	  MSG_PC_PLAY_NEXT,\
/*08*/	  MSG_PC_PP,\
/*09*/	  MSG_CHANGE_WORKMODE
										
#define IRFF00_USB_KEY_LONG			\
/*00*/	  NO_MSG,\
/*01*/	  NO_MSG,\
/*02*/	  NO_MSG,\
/*03*/	  NO_MSG,\
/*04*/	  NO_MSG,\
/*05*/	  NO_MSG,\
/*06*/	  MSG_VOL_DOWN,\
/*07*/	  MSG_VOL_UP,\
/*08*/	  NO_MSG,\
/*09*/	  MSG_STANBY_KEY

#define IRFF00_USB_KEY_HOLD			\
/*00*/	  NO_MSG,\
/*01*/	  NO_MSG,\
/*02*/	  NO_MSG,\
/*03*/	  NO_MSG,\
/*04*/	  NO_MSG,\
/*05*/	  NO_MSG,\
/*06*/	  MSG_VOL_DOWN,\
/*07*/	  MSG_VOL_UP,\
/*08*/	  NO_MSG,\
/*09*/	  NO_MSG


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
/*09*/    NO_MSG

/*******************************************************************
                     MAIN       IR按键表
*******************************************************************/
#define IRFF00_MAIN_KEY_SHORT			\
/*00*/    NO_MSG,\
/*01*/    NO_MSG,\
/*02*/    NO_MSG,\
/*03*/    NO_MSG,\
/*04*/    NO_MSG,\
/*05*/    NO_MSG,\
/*06*/    NO_MSG,\
/*07*/    NO_MSG,\
/*08*/    NO_MSG,\
/*09*/    NO_MSG

#define IRFF00_MAIN_KEY_LONG			\
/*00*/    NO_MSG,\
/*01*/    NO_MSG,\
/*02*/    NO_MSG,\
/*03*/    NO_MSG,\
/*04*/    NO_MSG,\
/*05*/    NO_MSG,\
/*06*/    NO_MSG,\
/*07*/    NO_MSG,\
/*08*/    NO_MSG,\
/*09*/    NO_MSG

#define IRFF00_MAIN_KEY_HOLD			\
/*00*/    NO_MSG,\
/*01*/    NO_MSG,\
/*02*/    NO_MSG,\
/*03*/    NO_MSG,\
/*04*/    NO_MSG,\
/*05*/    NO_MSG,\
/*06*/    NO_MSG,\
/*07*/    NO_MSG,\
/*08*/    NO_MSG,\
/*09*/    NO_MSG

#define IRFF00_MAIN_KEY_LONG_UP 		\
/*00*/    NO_MSG,\
/*01*/    NO_MSG,\
/*02*/    NO_MSG,\
/*03*/    NO_MSG,\
/*04*/    NO_MSG,\
/*05*/    NO_MSG,\
/*06*/    NO_MSG,\
/*07*/    NO_MSG,\
/*08*/    NO_MSG,\
/*09*/    NO_MSG

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
/*09*/	  MSG_STANBY_KEY

#define IRFF00_IDLE_KEY_LONG			\
/*00*/    NO_MSG,\
/*01*/    NO_MSG,\
/*02*/    NO_MSG,\
/*03*/    NO_MSG,\
/*04*/    NO_MSG,\
/*05*/    NO_MSG,\
/*06*/    NO_MSG,\
/*07*/    NO_MSG,\
/*08*/    NO_MSG,\
/*09*/    MSG_STANBY_KEY

#define IRFF00_IDLE_KEY_HOLD			\
/*00*/    NO_MSG,\
/*01*/    NO_MSG,\
/*02*/    NO_MSG,\
/*03*/    NO_MSG,\
/*04*/    NO_MSG,\
/*05*/    NO_MSG,\
/*06*/    NO_MSG,\
/*07*/    NO_MSG,\
/*08*/    NO_MSG,\
/*09*/    NO_MSG

#define IRFF00_IDLE_KEY_LONG_UP 		\
/*00*/    NO_MSG,\
/*01*/    NO_MSG,\
/*02*/    NO_MSG,\
/*03*/    NO_MSG,\
/*04*/    NO_MSG,\
/*05*/    NO_MSG,\
/*06*/    NO_MSG,\
/*07*/    NO_MSG,\
/*08*/    NO_MSG,\
/*09*/    NO_MSG
