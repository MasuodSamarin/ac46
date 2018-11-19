
/*******************************************************************
                        MUSIC   AD按键表
*******************************************************************/
#define ADKEY_DECODE_SHORT		\
    /*00*/    NO_MSG,\
    /*01*/    NO_MSG,\
    /*02*/    NO_MSG,\
    /*03*/    NO_MSG,\
    /*04*/    NO_MSG,\
    /*05*/    MSG_ONE_KEY_START_REC,\
    /*06*/    MSG_CHANGE_WORKMODE,\
    /*07*/    MSG_MUSIC_PP,\
    /*08*/    MSG_MUSIC_NEXT_FILE,\
    /*09*/    MSG_MUSIC_PREV_FILE,

#define ADKEY_DECODE_LONG		\
    /*00*/    NO_MSG,\
    /*01*/    NO_MSG,\
    /*02*/    NO_MSG,\
    /*03*/    NO_MSG,\
    /*04*/    NO_MSG,\
    /*05*/    MSG_MUSIC_DEL_FILE,\
    /*06*/    MSG_MUSIC_RPT,\
    /*07*/    NO_MSG,\
    /*08*/    MSG_VOL_UP,\
    /*09*/    MSG_VOL_DOWN,


#define ADKEY_DECODE_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  MSG_VOL_DOWN,

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
    /*09*/    NO_MSG,

/*******************************************************************
                        FM   AD按键表
*******************************************************************/

#define ADKEY_FM_SHORT		\
    /*00*/    NO_MSG,\
    /*01*/    NO_MSG,\
    /*02*/    NO_MSG,\
    /*03*/    NO_MSG,\
    /*04*/    NO_MSG,\
    /*05*/    MSG_REC_START,\
    /*06*/    MSG_CHANGE_WORKMODE,\
    /*07*/    MSG_FM_SCAN_ALL_INIT,\
    /*08*/    MSG_FM_NEXT_STATION,\
    /*09*/    MSG_FM_PREV_STATION,

#define ADKEY_FM_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_COM_REC_REPLAY,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  MSG_VOL_DOWN,


#define ADKEY_FM_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_COM_REC_REPLAY,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  MSG_VOL_DOWN,


#define ADKEY_FM_LONG_UP	\
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
                         LINE    AD按键表
*******************************************************************/

#define ADKEY_AUX_SHORT		\
    /*00*/    NO_MSG,\
    /*01*/    NO_MSG,\
    /*02*/    NO_MSG,\
    /*03*/    NO_MSG,\
    /*04*/    NO_MSG,\
    /*05*/    MSG_REC_START,\
    /*06*/    MSG_CHANGE_WORKMODE,\
    /*07*/    NO_MSG,\
    /*08*/    NO_MSG,\
    /*09*/    MSG_AUX_MUTE

#define ADKEY_AUX_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_COM_REC_REPLAY,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  MSG_VOL_DOWN,


#define ADKEY_AUX_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  MSG_VOL_DOWN,

#define ADKEY_AUX_LONG_UP	\
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
                         BT   AD按键表
*******************************************************************/


#define ADKEY_BT_SHORT		\
    /*00*/    NO_MSG,\
    /*01*/    NO_MSG,\
    /*02*/    NO_MSG,\
    /*03*/    NO_MSG,\
    /*04*/    NO_MSG,\
    /*05*/    MSG_REC_START,\
    /*06*/    MSG_CHANGE_WORKMODE,\
    /*07*/    NO_MSG,\
    /*08*/    MSG_BT_NEXT_FILE,\
    /*09*/    MSG_BT_PREV_FILE

#define ADKEY_BT_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_COM_REC_REPLAY,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  MSG_VOL_DOWN,


#define ADKEY_BT_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  MSG_VOL_DOWN,

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


/*******************************************************************
                         USB   AD按键表
*******************************************************************/
#define ADKEY_USB_SHORT		\
    /*00*/    NO_MSG,\
    /*01*/    NO_MSG,\
    /*02*/    NO_MSG,\
    /*03*/    NO_MSG,\
    /*04*/    NO_MSG,\
    /*05*/    NO_MSG,\
    /*06*/    MSG_CHANGE_WORKMODE,\
    /*07*/    NO_MSG,\
    /*08*/    MSG_PC_PLAY_NEXT,\
    /*09*/    MSG_PC_PLAY_PREV

#define ADKEY_USB_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  MSG_VOL_DOWN,


#define ADKEY_USB_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  MSG_VOL_DOWN,

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

// REC KEY  
#if REC_EN
#define ADKEY_ENC_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
    /*05*/     MSG_ONE_KEY_TO_MP3,\
    /*06*/     MSG_CHANGE_WORKMODE,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG

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
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,

#define ADKEY_MAIN_LONG		\
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



// STANBY  

#define ADKEY_STANBY_SHORT		\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09 MSG_AUX_MUTE*/    NO_MSG ,

#define ADKEY_STANBY_LONG		\
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


#define ADKEY_STANBY_HOLD		\
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

#define ADKEY_STANBY_LONG_UP	\
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
                        /*00*/    MSG_IDLE_CTL,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,

#define ADKEY_IDLE_LONG		\
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


