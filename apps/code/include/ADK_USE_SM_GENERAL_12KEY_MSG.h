
/*******************************************************************
                        MUSIC   AD按键表
*******************************************************************/

#define ADKEY_DECODE_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_MUSIC_EQ,\
	/*02*/	  MSG_MUSIC_RPT,\
	/*03*/	  MSG_STANBY_KEY,\
	/*04*/	  MSG_MUSIC_PREV_FILE,\
	/*05*/	  MSG_MUSIC_NEXT_FILE,\
	/*06*/	  MSG_VOL_DOWN,\
	/*07*/	  MSG_VOL_UP,\
	/*08*/	  MSG_CHANGE_WORKMODE,\
	/*09*/	  MSG_MUSIC_NEXT_FILE,\
	/*0A*/	  MSG_MUSIC_PP,\
	/*0B*/	  MSG_MUSIC_PREV_FILE
#define ADKEY_DECODE_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  MSG_VOL_DOWN,\
	/*07*/	  MSG_VOL_UP,\
	/*08*/	  MSG_STANBY_KEY,\
	/*09*/	  MSG_VOL_UP,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  MSG_VOL_DOWN

#define ADKEY_DECODE_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  MSG_VOL_DOWN,\
	/*07*/	  MSG_VOL_UP,\
	/*08*/	  MSG_STANBY_KEY,\
	/*09*/	  MSG_VOL_UP,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  MSG_VOL_DOWN

#define ADKEY_DECODE_LONG_UP	\
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
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG

/*******************************************************************
                        FM   AD按键表
*******************************************************************/

#define ADKEY_FM_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  MSG_FM_PREV_STATION,\
	/*03*/	  MSG_STANBY_KEY,\
	/*04*/	  MSG_FM_PREV_STEP,\
	/*05*/	  MSG_FM_NEXT_STEP,\
	/*06*/	  MSG_VOL_DOWN,\
	/*07*/	  MSG_VOL_UP,\
	/*08*/	  MSG_CHANGE_WORKMODE,\
	/*09*/	  MSG_FM_NEXT_STEP,\
	/*0A*/	  MSG_FM_NEXT_STATION,\
	/*0B*/	  MSG_FM_PREV_STEP

#define ADKEY_FM_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  MSG_VOL_DOWN,\
	/*05*/	  MSG_VOL_UP,\
	/*06*/	  MSG_VOL_DOWN,\
	/*07*/	  MSG_VOL_UP,\
	/*08*/	  MSG_STANBY_KEY,\
	/*09*/	  MSG_FM_NEXT_STATION,\
	/*0A*/	  MSG_FM_SCAN_ALL_INIT,\
	/*0B*/	  MSG_FM_PREV_STATION


#define ADKEY_FM_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  MSG_VOL_DOWN,\
	/*05*/	  MSG_VOL_UP,\
	/*06*/	  MSG_VOL_DOWN,\
	/*07*/	  MSG_VOL_UP,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_UP,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  MSG_VOL_DOWN

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
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG
                        
/*******************************************************************
                         LINE    AD按键表
*******************************************************************/

#define ADKEY_AUX_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_STANBY_KEY,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  MSG_VOL_DOWN,\
	/*07*/	  MSG_VOL_UP,\
	/*08*/	  MSG_CHANGE_WORKMODE,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG

#define ADKEY_AUX_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  MSG_VOL_DOWN,\
	/*05*/	  MSG_VOL_UP,\
	/*06*/	  MSG_VOL_DOWN,\
	/*07*/	  MSG_VOL_UP,\
	/*08*/	  MSG_STANBY_KEY,\
	/*09*/	  MSG_VOL_UP,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  MSG_VOL_DOWN


#define ADKEY_AUX_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  MSG_VOL_DOWN,\
	/*05*/	  MSG_VOL_UP,\
	/*06*/	  MSG_VOL_DOWN,\
	/*07*/	  MSG_VOL_UP,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_UP,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  MSG_VOL_DOWN

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
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG


/*******************************************************************
                         BT   AD按键表
*******************************************************************/


#define ADKEY_BT_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_BT_MUSIC_EQ,\
	/*02*/	  MSG_MUSIC_RPT,\
	/*03*/	  MSG_STANBY_KEY,\
	/*04*/	  MSG_BT_PREV_FILE,\
	/*05*/	  MSG_BT_NEXT_FILE,\
	/*06*/	  MSG_VOL_DOWN,\
	/*07*/	  MSG_VOL_UP,\
	/*08*/	  MSG_CHANGE_WORKMODE,\
	/*09*/	  MSG_BT_NEXT_FILE,\
	/*0A*/	  MSG_BT_PP,\
	/*0B*/	  MSG_BT_PREV_FILE

#define ADKEY_BT_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  MSG_VOL_DOWN,\
	/*05*/	  MSG_VOL_UP,\
	/*06*/	  MSG_VOL_DOWN,\
	/*07*/	  MSG_VOL_UP,\
	/*08*/	  MSG_STANBY_KEY,\
	/*09*/	  MSG_VOL_UP,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  MSG_VOL_DOWN


#define ADKEY_BT_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  MSG_VOL_DOWN,\
	/*05*/	  MSG_VOL_UP,\
	/*06*/	  MSG_VOL_DOWN,\
	/*07*/	  MSG_VOL_UP,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_UP,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  MSG_VOL_DOWN

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
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG


/*******************************************************************
                         USB   AD按键表
*******************************************************************/
#define ADKEY_USB_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_STANBY_KEY,\
	/*04*/	  MSG_PC_PLAY_PREV,\
	/*05*/	  MSG_PC_PLAY_NEXT,\
	/*06*/	  MSG_VOL_DOWN,\
	/*07*/	  MSG_VOL_UP,\
	/*08*/	  MSG_CHANGE_WORKMODE,\
	/*09*/	  MSG_PC_PLAY_NEXT,\
	/*0A*/	  MSG_PC_PP,\
	/*0B*/	  MSG_PC_PLAY_PREV

#define ADKEY_USB_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  MSG_VOL_DOWN,\
	/*07*/	  MSG_VOL_UP,\
	/*08*/	  MSG_STANBY_KEY,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG

#define ADKEY_USB_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  MSG_VOL_DOWN,\
	/*07*/	  MSG_VOL_UP,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG

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
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG

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
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG

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
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG


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
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG

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
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG

/*******************************************************************
                            AD按键表
*******************************************************************/
#define ADKEY_IDLE_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  MSG_STANBY_KEY,\
	/*03*/	  MSG_STANBY_KEY,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  MSG_STANBY_KEY,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG

#define ADKEY_IDLE_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  MSG_STANBY_KEY,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG


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
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG

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
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG
                        
