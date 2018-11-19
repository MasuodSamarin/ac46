
/*******************************************************************
MUSIC   AD按键表
*******************************************************************/

#define ADKEY_DECODE_SHORT		\
/*00*/    NO_MSG,\
/*01*/    NO_MSG,\
/*02*/    MSG_MENU_MODE,\
/*03*/    MSG_MUSIC_PP,\
/*04*/    MSG_MUSIC_RPT,\
/*05*/    MSG_MUSIC_NEXT_FILE,\
/*06*/    MSG_MUSIC_NEXT_FILE,\
/*07*/    MSG_MUTE,\
/*08*/    MSG_MUSIC_NEXT_FILE,\
/*09*/    MSG_MUSIC_PREV_FILE,\
/*0A*/	  MSG_MUSIC_PREV_FILE,\
/*0B*/	  MSG_MUSIC_NEXT_FILE,\
/*0C*/	  MSG_VOL_UP,\
/*0D*/	  MSG_VOL_DOWN,\
/*0E*/	  MSG_CHANGE_WORKMODE


#define ADKEY_DECODE_LONG		\
/*00*/    NO_MSG,\
/*01*/    NO_MSG,\
/*02*/    NO_MSG,\
/*03*/    NO_MSG,\
/*04*/    NO_MSG,\
/*05*/    MSG_VOL_UP,\
/*06*/    NO_MSG,\
/*07*/    NO_MSG,\
/*08*/    MSG_VOL_UP,\
/*09*/    MSG_VOL_DOWN,\
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 MSG_VOL_UP,\
/*0D*/	 MSG_VOL_DOWN,\
/*0E*/	 NO_MSG

#define ADKEY_DECODE_HOLD		\
/*00*/    NO_MSG,\
/*01*/    NO_MSG,\
/*02*/    NO_MSG,\
/*03*/    NO_MSG,\
/*04*/    NO_MSG,\
/*05*/    MSG_VOL_UP,\
/*06*/    NO_MSG,\
/*07*/    NO_MSG,\
/*08*/    MSG_VOL_UP,\
/*09*/    MSG_VOL_DOWN,\
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 MSG_VOL_UP,\
/*0D*/	 MSG_VOL_DOWN,\
/*0E*/	 NO_MSG


#define ADKEY_DECODE_LONG_UP	\
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
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 NO_MSG,\
/*0D*/	 NO_MSG,\
/*0E*/	 NO_MSG



/*******************************************************************
FM   AD按键表
*******************************************************************/

#define ADKEY_FM_SHORT		\
/*00*/    NO_MSG,\
/*01*/    NO_MSG,\
/*02*/    MSG_MENU_MODE,\
/*03*/    MSG_FM_SCAN_ALL_INIT,\
/*04*/    NO_MSG,\
/*05*/    MSG_FM_NEXT_STATION,\
/*06*/    MSG_STANBY_KEY,\
/*07*/    MSG_MUTE,\
/*08*/    MSG_FM_NEXT_STATION,\
/*09*/   MSG_FM_PREV_STATION,\
/*0A*/	  MSG_FM_PREV_STATION,\
/*0B*/	  MSG_FM_NEXT_STATION,\
/*0C*/	  MSG_VOL_UP,\
/*0D*/	  MSG_VOL_DOWN,\
/*0E*/	  MSG_CHANGE_WORKMODE


#define ADKEY_FM_LONG		\
/*00*/    NO_MSG,\
/*01*/    NO_MSG,\
/*02*/    NO_MSG,\
/*03*/    NO_MSG,\
/*04*/    NO_MSG,\
/*05*/    MSG_VOL_UP,\
/*06*/    NO_MSG,\
/*07*/    NO_MSG,\
/*08*/    MSG_VOL_UP,\
/*09*/    MSG_VOL_DOWN,\
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 MSG_VOL_UP,\
/*0D*/	 MSG_VOL_DOWN,\
/*0E*/	 NO_MSG



#define ADKEY_FM_HOLD		\
/*00*/    NO_MSG,\
/*01*/    NO_MSG,\
/*02*/    NO_MSG,\
/*03*/    NO_MSG,\
/*04*/    NO_MSG,\
/*05*/    MSG_VOL_UP,\
/*06*/    NO_MSG,\
/*07*/    NO_MSG,\
/*08*/    MSG_VOL_UP,\
/*09*/    MSG_VOL_DOWN,\
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 MSG_VOL_UP,\
/*0D*/	 MSG_VOL_DOWN,\
/*0E*/	 NO_MSG


#define ADKEY_FM_LONG_UP	\
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
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 NO_MSG,\
/*0D*/	 NO_MSG,\
/*0E*/	 NO_MSG

/*******************************************************************
LINE    AD按键表
*******************************************************************/

#define ADKEY_AUX_SHORT		\
/*00*/    NO_MSG,\
/*01*/    NO_MSG,\
/*02*/    MSG_MENU_MODE,\
/*03*/    MSG_AUX_PAUSE,\
/*04*/    NO_MSG,\
/*05*/    MSG_VOL_UP,\
/*06*/    MSG_STANBY_KEY,\
/*07*/    MSG_MUTE,\
/*08*/    NO_MSG,\
/*09*/   NO_MSG,\
/*0A*/	  NO_MSG,\
/*0B*/	  NO_MSG,\
/*0C*/	  MSG_VOL_UP,\
/*0D*/	  MSG_VOL_DOWN,\
/*0E*/	  MSG_CHANGE_WORKMODE



#define ADKEY_AUX_LONG		\
/*00*/    NO_MSG,\
/*01*/    NO_MSG,\
/*02*/    NO_MSG,\
/*03*/    NO_MSG,\
/*04*/    NO_MSG,\
/*05*/    MSG_VOL_UP,\
/*06*/    NO_MSG,\
/*07*/    NO_MSG,\
/*08*/    MSG_VOL_UP,\
/*09*/    MSG_VOL_DOWN,\
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 MSG_VOL_UP,\
/*0D*/	 MSG_VOL_DOWN,\
/*0E*/	 NO_MSG



#define ADKEY_AUX_HOLD		\
/*00*/    NO_MSG,\
/*01*/    NO_MSG,\
/*02*/    NO_MSG,\
/*03*/    NO_MSG,\
/*04*/    NO_MSG,\
/*05*/    MSG_VOL_UP,\
/*06*/    NO_MSG,\
/*07*/    NO_MSG,\
/*08*/    MSG_VOL_UP,\
/*09*/    MSG_VOL_DOWN,\
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 MSG_VOL_UP,\
/*0D*/	 MSG_VOL_DOWN,\
/*0E*/	 NO_MSG


#define ADKEY_AUX_LONG_UP	\
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
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 NO_MSG,\
/*0D*/	 NO_MSG,\
/*0E*/	 NO_MSG


/*******************************************************************
BT   AD按键表
*******************************************************************/


#define ADKEY_BT_SHORT		\
/*00*/    NO_MSG,\
/*01*/    NO_MSG,\
/*02*/    MSG_MENU_MODE,\
/*03*/    MSG_BT_PP,\
/*04*/    NO_MSG,\
/*05*/    MSG_BT_NEXT_FILE,\
/*06*/    MSG_STANBY_KEY,\
/*07*/    MSG_MUTE,\
/*08*/    MSG_BT_NEXT_FILE,\
/*09*/   MSG_BT_PREV_FILE,\
/*0A*/	  MSG_BT_PREV_FILE,\
/*0B*/	  MSG_BT_NEXT_FILE,\
/*0C*/	  MSG_VOL_UP,\
/*0D*/	  MSG_VOL_DOWN,\
/*0E*/	  MSG_CHANGE_WORKMODE


#define ADKEY_BT_LONG		\
/*00*/    NO_MSG,\
/*01*/    NO_MSG,\
/*02*/    NO_MSG,\
/*03*/    NO_MSG,\
/*04*/    NO_MSG,\
/*05*/    MSG_VOL_UP,\
/*06*/    NO_MSG,\
/*07*/    NO_MSG,\
/*08*/    MSG_VOL_UP,\
/*09*/    MSG_VOL_DOWN,\
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 MSG_VOL_UP,\
/*0D*/	 MSG_VOL_DOWN,\
/*0E*/	 NO_MSG


#define ADKEY_BT_HOLD		\
/*00*/    NO_MSG,\
/*01*/    NO_MSG,\
/*02*/    NO_MSG,\
/*03*/    NO_MSG,\
/*04*/    NO_MSG,\
/*05*/    MSG_VOL_UP,\
/*06*/    NO_MSG,\
/*07*/    NO_MSG,\
/*08*/    MSG_VOL_UP,\
/*09*/    MSG_VOL_DOWN,\
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 MSG_VOL_UP,\
/*0D*/	 MSG_VOL_DOWN,\
/*0E*/	 NO_MSG


#define ADKEY_BT_LONG_UP	\
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
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 NO_MSG,\
/*0D*/	 NO_MSG,\
/*0E*/	 NO_MSG


/*******************************************************************
USB   AD按键表
*******************************************************************/
#define ADKEY_USB_SHORT		\
/*00*/	  NO_MSG,\
/*01*/	  NO_MSG,\
/*02*/	  NO_MSG,\
/*03*/	  MSG_VOL_UP,\
/*04*/	  MSG_PC_PLAY_PREV,\
/*05*/	  MSG_ONE_KEY_TO_RADIO,\
/*06*/	  MSG_BT_MUSIC_EQ,\
/*07*/	  MSG_MUSIC_RPT,\
/*08*/	  MSG_PC_PLAY_NEXT,\
/*09*/	  MSG_VOL_DOWN,\
/*0A*/	  MSG_CHANGE_WORKMODE,\
/*0B*/	  MSG_MUSIC_U_SD,\
/*0C*/	  MSG_PC_PP,\
/*0D*/	  MSG_MUSIC_STOP,\
/*0E*/	  MSG_ONE_KEY_TO_AUX

#define ADKEY_USB_LONG		\
/*00*/	  NO_MSG,\
/*01*/	  NO_MSG,\
/*02*/	  NO_MSG,\
/*03*/	  MSG_VOL_UP,\
/*04*/	  MSG_VOL_DOWN,\
/*05*/	  NO_MSG,\
/*06*/	  NO_MSG,\
/*07*/	  NO_MSG,\
/*08*/	  MSG_VOL_UP,\
/*09*/	  MSG_VOL_DOWN,\
/*0A*/	 MSG_STANBY_KEY,\
/*0B*/	 NO_MSG,\
/*0C*/	 NO_MSG,\
/*0D*/	 NO_MSG,\
/*0E*/	 NO_MSG


#define ADKEY_USB_HOLD		\
/*00*/	  NO_MSG,\
/*01*/	  NO_MSG,\
/*02*/	  NO_MSG,\
/*03*/	  MSG_VOL_UP,\
/*04*/	  MSG_VOL_DOWN,\
/*05*/	  NO_MSG,\
/*06*/	  NO_MSG,\
/*07*/	  NO_MSG,\
/*08*/	  MSG_VOL_UP,\
/*09*/	  MSG_VOL_DOWN,\
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 MSG_BT_ANSWER_CALL,\
/*0D*/	 NO_MSG,\
/*0E*/	 NO_MSG

#define ADKEY_USB_LONG_UP	\
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
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 NO_MSG,\
/*0D*/	 NO_MSG,\
/*0E*/	 NO_MSG

/*******************************************************************
main 按键表
*******************************************************************/
#define ADKEY_MAIN_SHORT		\
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
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 NO_MSG,\
/*0D*/	 NO_MSG,\
/*0E*/	 NO_MSG

#define ADKEY_MAIN_LONG		\
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
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 NO_MSG,\
/*0D*/	 NO_MSG,\
/*0E*/	 NO_MSG


#define ADKEY_MAIN_HOLD		\
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
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 NO_MSG,\
/*0D*/	 NO_MSG,\
/*0E*/	 NO_MSG

#define ADKEY_MAIN_LONG_UP	\
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
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 NO_MSG,\
/*0D*/	 NO_MSG,\
/*0E*/	 NO_MSG


// STANBY  

#define ADKEY_STANBY_SHORT		\
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
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 MSG_STANBY_KEY,\
/*0D*/	 NO_MSG,\
/*0E*/	 NO_MSG

#define ADKEY_STANBY_LONG		\
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
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 NO_MSG,\
/*0D*/	 NO_MSG,\
/*0E*/	 NO_MSG


#define ADKEY_STANBY_HOLD		\
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
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 NO_MSG,\
/*0D*/	 NO_MSG,\
/*0E*/	 NO_MSG

#define ADKEY_STANBY_LONG_UP	\
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
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 NO_MSG,\
/*0D*/	 NO_MSG,\
/*0E*/	 NO_MSG

/*******************************************************************
AD按键表
*******************************************************************/
#define ADKEY_IDLE_SHORT		\
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
/*0A*/	 MSG_STANBY_KEY,\
/*0B*/	 NO_MSG,\
/*0C*/	 MSG_STANBY_KEY,\
/*0D*/	 NO_MSG,\
/*0E*/	 NO_MSG

#define ADKEY_IDLE_LONG		\
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
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 NO_MSG,\
/*0D*/	 NO_MSG,\
/*0E*/	 NO_MSG


#define ADKEY_IDLE_HOLD		\
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
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 NO_MSG,\
/*0D*/	 NO_MSG,\
/*0E*/	 NO_MSG

#define ADKEY_IDLE_LONG_UP	\
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
/*0A*/	 NO_MSG,\
/*0B*/	 NO_MSG,\
/*0C*/	 NO_MSG,\
/*0D*/	 NO_MSG,\
/*0E*/	 NO_MSG

