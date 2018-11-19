
/*******************************************************************
                        MUSIC   AD按键表
*******************************************************************/
#define ADKEY_DECODE_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_MUSIC_STOP,\
	/*02*/	  MSG_STANBY_KEY,\
	/*03*/	  MSG_MUSIC_PREV_FILE,\
	/*04*/	  MSG_MUSIC_NEXT_FILE,\
	/*05*/	  MSG_MUSIC_EQ,\
	/*06*/	  MSG_MUSIC_RPT,\
	/*07*/	  MSG_ONE_KEY_TO_BT,\
	/*08*/	  MSG_CHANGE_WORKMODE,\
	/*09*/	  MSG_MUSIC_PP
#ifdef ZY_3058B_AC4601_BT_CY_V10_1
#define ADKEY_DECODE_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOL_DOWN,\
	/*04*/	  MSG_VOL_UP,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG
#else
#define ADKEY_DECODE_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOL_DOWN,\
	/*04*/	  MSG_VOL_UP,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  MSG_REC_REPLAY,\
	/*09*/	  MSG_ONE_KEY_START_REC
#endif

#define ADKEY_DECODE_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOL_DOWN,\
	/*04*/	  MSG_VOL_UP,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG

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
	/*09*/	  NO_MSG
/*******************************************************************
                        FM   AD按键表
*******************************************************************/

#define ADKEY_FM_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  MSG_STANBY_KEY,\
	/*03*/	  MSG_FM_PREV_STATION,\
	/*04*/	  MSG_FM_NEXT_STATION,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  MSG_ONE_KEY_TO_BT,\
	/*08*/	  MSG_CHANGE_WORKMODE,\
	/*09*/	  MSG_FM_SCAN_ALL_INIT
	
#ifdef ZY_3058B_AC4601_BT_CY_V10_1
#define ADKEY_FM_LONG		\
		/*00*/	  NO_MSG,\
		/*01*/	  NO_MSG,\
		/*02*/	  NO_MSG,\
		/*03*/	  MSG_VOL_DOWN,\
		/*04*/	  MSG_VOL_UP,\
		/*05*/	  NO_MSG,\
		/*06*/	  NO_MSG,\
		/*07*/	  NO_MSG,\
		/*08*/	  NO_MSG,\
		/*09*/	  NO_MSG
#else

#define ADKEY_FM_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOL_DOWN,\
	/*04*/	  MSG_VOL_UP,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  MSG_COM_REC_REPLAY,\
	/*09*/	  MSG_REC_START,
#endif

#define ADKEY_FM_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOL_DOWN,\
	/*04*/	  MSG_VOL_UP,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,

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
	/*09*/	  NO_MSG,
                        
/*******************************************************************
                         LINE    AD按键表
*******************************************************************/

#define ADKEY_AUX_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  MSG_STANBY_KEY,\
	/*03*/	  MSG_VOL_DOWN,\
	/*04*/	  MSG_VOL_UP,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  MSG_ONE_KEY_TO_BT,\
	/*08*/	  MSG_CHANGE_WORKMODE,\
	/*09*/	  MSG_AUX_PAUSE

#ifdef ZY_3058B_AC4601_BT_CY_V10_1
#define ADKEY_AUX_LONG		\
		/*00*/	  NO_MSG,\
		/*01*/	  NO_MSG,\
		/*02*/	  NO_MSG,\
		/*03*/	  MSG_VOL_DOWN,\
		/*04*/	  MSG_VOL_UP,\
		/*05*/	  NO_MSG,\
		/*06*/	  NO_MSG,\
		/*07*/	  NO_MSG,\
		/*08*/	  NO_MSG,\
		/*09*/	  NO_MSG
#else
#define ADKEY_AUX_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOL_DOWN,\
	/*04*/	  MSG_VOL_UP,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  MSG_COM_REC_REPLAY,\
	/*09*/	  MSG_REC_START
#endif

#define ADKEY_AUX_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOL_DOWN,\
	/*04*/	  MSG_VOL_UP,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG

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
	/*09*/	  NO_MSG,


/*******************************************************************
                         BT   AD按键表
*******************************************************************/


#define ADKEY_BT_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  MSG_STANBY_KEY,\
	/*03*/	  MSG_BT_PREV_FILE,\
	/*04*/	  MSG_BT_NEXT_FILE,\
	/*05*/	  MSG_BT_MUSIC_EQ,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  MSG_CHANGE_WORKMODE,\
	/*09*/	  MSG_BT_PP

#ifdef ZY_3058B_AC4601_BT_CY_V10_1
#define ADKEY_BT_LONG		\
		/*00*/	  NO_MSG,\
		/*01*/	  NO_MSG,\
		/*02*/	  NO_MSG,\
		/*03*/	  MSG_VOL_DOWN,\
		/*04*/	  MSG_VOL_UP,\
		/*05*/	  NO_MSG,\
		/*06*/	  NO_MSG,\
		/*07*/	  NO_MSG,\
		/*08*/	  NO_MSG,\
		/*09*/	  NO_MSG
#else
#define ADKEY_BT_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOL_DOWN,\
	/*04*/	  MSG_VOL_UP,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG
#endif

#define ADKEY_BT_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOL_DOWN,\
	/*04*/	  MSG_VOL_UP,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG

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
	/*09*/	  NO_MSG,

/*******************************************************************
                         REC KEY     AD按键表
*******************************************************************/
#if REC_EN

#define ADKEY_ENC_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_COM_REC_REPLAY


#define ADKEY_ENC_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG
	
#define ADKEY_ENC_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG
	

#define ADKEY_ENC_LONG_UP	\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG
	
#endif


/*******************************************************************
                         USB   AD按键表
*******************************************************************/
#define ADKEY_USB_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  MSG_STANBY_KEY,\
	/*03*/	  MSG_PC_PLAY_PREV,\
	/*04*/	  MSG_PC_PLAY_NEXT,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  MSG_CHANGE_WORKMODE,\
	/*09*/	  MSG_PC_PP

#ifdef ZY_3058B_AC4601_BT_CY_V10_1
#define ADKEY_USB_LONG		\
		/*00*/	  NO_MSG,\
		/*01*/	  NO_MSG,\
		/*02*/	  NO_MSG,\
		/*03*/	  MSG_VOL_DOWN,\
		/*04*/	  MSG_VOL_UP,\
		/*05*/	  NO_MSG,\
		/*06*/	  NO_MSG,\
		/*07*/	  NO_MSG,\
		/*08*/	  NO_MSG,\
		/*09*/	  NO_MSG
#else
#define ADKEY_USB_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOL_DOWN,\
	/*04*/	  MSG_VOL_UP,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG
#endif

#define ADKEY_USB_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOL_DOWN,\
	/*04*/	  MSG_VOL_UP,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG

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
	/*09*/	  NO_MSG

/*******************************************************************
                            main 按键表
*******************************************************************/
#define ADKEY_MAIN_SHORT		\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    MSG_CHANGE_WORKMODE,\
                        /*09*/    NO_MSG,

#define ADKEY_MAIN_LONG		\
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


#define ADKEY_MAIN_HOLD		\
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

#define ADKEY_MAIN_LONG_UP	\
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

/*******************************************************************
                            AD按键表
*******************************************************************/
#define ADKEY_IDLE_SHORT		\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    MSG_STANBY_KEY,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    MSG_STANBY_KEY,

#define ADKEY_IDLE_LONG		\
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


#define ADKEY_IDLE_HOLD		\
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

#define ADKEY_IDLE_LONG_UP	\
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
                        
