
// PREV:0R   NEXT:3.3K   MODE: 10K REP:20K  PLAY:33K 
// 0 1 2 3.3 5.1 7.5 10 15 20 33


/*******************************************************************
                        MUSIC   AD按键表
*******************************************************************/
#define ADKEY_DECODE_SHORT		\
	/*00*/    NO_MSG,\
	/*01*/    NO_MSG,\
	/*02*/    NO_MSG,\
	/*03*/    NO_MSG,\
	/*04*/    NO_MSG,\
	/*05*/    MSG_MUSIC_PP,\
	/*06*/    MSG_MUSIC_RPT,\
	/*07*/    NO_MSG,\
	/*08*/    MSG_CHANGE_WORKMODE,\
	/*09*/    NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  MSG_MUSIC_NEXT_FILE,\
	/*0C*/	  NO_MSG,\
	/*0D*/	  NO_MSG,\
	/*0E*/	  MSG_MUSIC_PREV_FILE

#define ADKEY_DECODE_LONG		\
    /*00*/    NO_MSG,\
    /*01*/    NO_MSG,\
    /*02*/    NO_MSG,\
    /*03*/    NO_MSG,\
    /*04*/    NO_MSG,\
    /*05*/    MSG_ONE_KEY_START_REC,\
    /*06*/    MSG_MUSIC_DEL_FILE,\
    /*07*/    NO_MSG,\
    /*08*/    MSG_REC_REPLAY,\
    /*09*/    NO_MSG,\
	/*0A*/	 NO_MSG,\
	/*0B*/	 MSG_VOL_UP,\
	/*0C*/	 NO_MSG,\
	/*0D*/	 NO_MSG,\
	/*0E*/	 MSG_VOL_DOWN

#define ADKEY_DECODE_HOLD		\
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
	/*0B*/	 MSG_VOL_UP,\
	/*0C*/	 NO_MSG,\
	/*0D*/	 NO_MSG,\
	/*0E*/	 MSG_VOL_DOWN

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
	/*02*/    NO_MSG,\
	/*03*/    NO_MSG,\
	/*04*/    NO_MSG,\
	/*05*/    MSG_FM_SCAN_ALL_INIT,\
	/*06*/    NO_MSG,\
	/*07*/    NO_MSG,\
	/*08*/    MSG_CHANGE_WORKMODE,\
	/*09*/    NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  MSG_FM_NEXT_STATION,\
	/*0C*/	  NO_MSG,\
	/*0D*/	  NO_MSG,\
	/*0E*/	  MSG_FM_PREV_STATION
	
#define ADKEY_FM_LONG		\
    /*00*/    NO_MSG,\
    /*01*/    NO_MSG,\
    /*02*/    NO_MSG,\
    /*03*/    NO_MSG,\
    /*04*/    NO_MSG,\
    /*05*/    MSG_REC_START,\
    /*06*/    NO_MSG,\
    /*07*/    NO_MSG,\
    /*08*/    MSG_COM_REC_REPLAY,\
    /*09*/    NO_MSG,\
	/*0A*/	 NO_MSG,\
	/*0B*/	 MSG_VOL_UP,\
	/*0C*/	 NO_MSG,\
	/*0D*/	 NO_MSG,\
	/*0E*/	 MSG_VOL_DOWN

	
#define ADKEY_FM_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
    /*08*/    NO_MSG,\
    /*09*/    NO_MSG,\
	/*0A*/	 NO_MSG,\
	/*0B*/	 MSG_VOL_UP,\
	/*0C*/	 NO_MSG,\
	/*0D*/	 NO_MSG,\
	/*0E*/	 MSG_VOL_DOWN

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
	/*02*/    NO_MSG,\
	/*03*/    NO_MSG,\
	/*04*/    NO_MSG,\
	/*05*/    MSG_AUX_PAUSE,\
	/*06*/    NO_MSG,\
	/*07*/    NO_MSG,\
	/*08*/    MSG_CHANGE_WORKMODE,\
	/*09*/    NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\
	/*0D*/	  NO_MSG,\
	/*0E*/	  NO_MSG
	

#define ADKEY_AUX_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_REC_START,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  MSG_COM_REC_REPLAY,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	 MSG_VOL_UP,\
	/*0C*/	 NO_MSG,\
	/*0D*/	 NO_MSG,\
	/*0E*/	 MSG_VOL_DOWN


#define ADKEY_AUX_HOLD		\
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
	/*0B*/	 MSG_VOL_UP,\
	/*0C*/	 NO_MSG,\
	/*0D*/	 NO_MSG,\
	/*0E*/	 MSG_VOL_DOWN

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
	/*02*/    NO_MSG,\
	/*03*/    NO_MSG,\
	/*04*/    NO_MSG,\
	/*05*/    MSG_BT_PP,\
	/*06*/    NO_MSG,\
	/*07*/    NO_MSG,\
	/*08*/    MSG_CHANGE_WORKMODE,\
	/*09*/    NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  MSG_BT_NEXT_FILE,\
	/*0C*/	  NO_MSG,\
	/*0D*/	  NO_MSG,\
	/*0E*/	  MSG_BT_PREV_FILE
	
#define ADKEY_BT_LONG		\
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
	/*0B*/	 MSG_VOL_UP,\
	/*0C*/	 NO_MSG,\
	/*0D*/	 NO_MSG,\
	/*0E*/	 MSG_VOL_DOWN


#define ADKEY_BT_HOLD		\
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
	/*0B*/	 MSG_VOL_UP,\
	/*0C*/	 NO_MSG,\
	/*0D*/	 NO_MSG,\
	/*0E*/	 MSG_VOL_DOWN

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
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_PC_PP,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  MSG_CHANGE_WORKMODE,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  MSG_PC_PLAY_NEXT,\
	/*0C*/	  NO_MSG,\
	/*0D*/	  NO_MSG,\
	/*0E*/	  MSG_PC_PLAY_PREV

#define ADKEY_USB_LONG		\
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
	/*0B*/	 MSG_VOL_UP,\
	/*0C*/	 NO_MSG,\
	/*0D*/	 NO_MSG,\
	/*0E*/	 MSG_VOL_DOWN


#define ADKEY_USB_HOLD		\
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
	/*0B*/	 MSG_VOL_UP,\
	/*0C*/	 NO_MSG,\
	/*0D*/	 NO_MSG,\
	/*0E*/	 MSG_VOL_DOWN

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

// REC KEY  
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
	/*09*/	  NO_MSG,\
	/*0A*/	 NO_MSG,\
	/*0B*/	 NO_MSG,\
	/*0C*/	 NO_MSG,\
	/*0D*/	 NO_MSG,\
	/*0E*/	 NO_MSG

#define ADKEY_ENC_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_ONE_KEY_TO_MP3,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	 NO_MSG,\
	/*0B*/	 NO_MSG,\
	/*0C*/	 NO_MSG,\
	/*0D*/	 NO_MSG,\
	/*0E*/	 NO_MSG


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
	/*09*/	  NO_MSG,\
	/*0A*/	 NO_MSG,\
	/*0B*/	 NO_MSG,\
	/*0C*/	 NO_MSG,\
	/*0D*/	 NO_MSG,\
	/*0E*/	 NO_MSG

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
	/*09*/	  NO_MSG,\
	/*0A*/	 NO_MSG,\
	/*0B*/	 NO_MSG,\
	/*0C*/	 NO_MSG,\
	/*0D*/	 NO_MSG,\
	/*0E*/	 NO_MSG
#endif

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

/*******************************************************************
                            AD按键表
*******************************************************************/
#define ADKEY_IDLE_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  MSG_STANBY_KEY,\
	/*05*/	  NO_MSG,\
	/*06*/	  MSG_STANBY_KEY,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	 NO_MSG,\
	/*0B*/	 MSG_STANBY_KEY,\
	/*0C*/	 NO_MSG,\
	/*0D*/	 MSG_STANBY_KEY,\
	/*0E*/	 MSG_STANBY_KEY

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
                        
