
/*******************************************************************
                        MUSIC   AD按键表
*******************************************************************/
#define ADKEY_DECODE_SHORT		\
                        /*00*/    NO_MSG,\
                        /*01*/    MSG_ONE_KEY_TO_BT,\
                        /*02*/    MSG_ONE_KEY_TO_BT,\
                        /*03*/    MSG_MUSIC_STOP,\
                        /*04*/    MSG_STANBY_KEY,\
                        /*05*/    MSG_MUSIC_PREV_FILE,\
                        /*06*/    MSG_MUSIC_NEXT_FILE,\
                        /*07*/    MSG_MUSIC_EQ,\
                        /*08*/    MSG_MUSIC_RPT,\
                        /*09*/    MSG_VOL_UP,\
                      	/*0A*/	  MSG_VOL_DOWN,\
                      	/*0B*/	  MSG_CHANGE_WORKMODE,\
                      	/*0C*/	  MSG_REC_REPLAY,\
                      	/*0D*/	  MSG_ONE_KEY_START_REC,\
                      	/*0E*/	  MSG_MUSIC_PP

#define ADKEY_DECODE_LONG		\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    MSG_VOL_DOWN,\
                        /*06*/    MSG_VOL_UP,\
                        /*07*/    NO_MSG,\
                        /*08*/    MSG_MUSIC_DEL_FILE,\
                        /*09*/    MSG_VOL_UP,\
                    	/*0A*/	 MSG_VOL_DOWN,\
                    	/*0B*/	 NO_MSG,\
                    	/*0C*/	 NO_MSG,\
                    	/*0D*/	 NO_MSG,\
                    	/*0E*/	 NO_MSG

#define ADKEY_DECODE_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_UP,\
	/*0A*/	 MSG_VOL_DOWN,\
	/*0B*/	 NO_MSG,\
	/*0C*/	 NO_MSG,\
	/*0D*/	 NO_MSG,\
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
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_ONE_KEY_TO_BT,\
	/*02*/	  MSG_ONE_KEY_TO_BT,\
	/*03*/	  NO_MSG,\
	/*04*/	  MSG_STANBY_KEY,\
	/*05*/	  MSG_FM_PREV_STATION,\
	/*06*/	  MSG_FM_NEXT_STATION,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_UP,\
	/*0A*/	  MSG_VOL_DOWN,\
	/*0B*/	  MSG_CHANGE_WORKMODE,\
	/*0C*/	  MSG_COM_REC_REPLAY,\
	/*0D*/	  MSG_REC_START,\
	/*0E*/	  MSG_FM_SCAN_ALL_INIT

#define ADKEY_FM_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_UP,\
	/*0A*/	  MSG_VOL_DOWN,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\
	/*0D*/	  NO_MSG,\
	/*0E*/	  NO_MSG


#define ADKEY_FM_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_UP,\
	/*0A*/	  MSG_VOL_DOWN,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\
	/*0D*/	  NO_MSG,\
	/*0E*/	  NO_MSG

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
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_ONE_KEY_TO_BT,\
	/*02*/	  MSG_ONE_KEY_TO_BT,\
	/*03*/	  NO_MSG,\
	/*04*/	  MSG_STANBY_KEY,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_UP,\
	/*0A*/	  MSG_VOL_DOWN,\
	/*0B*/	  MSG_CHANGE_WORKMODE,\
	/*0C*/	  MSG_COM_REC_REPLAY,\
	/*0D*/	  MSG_REC_START,\
	/*0E*/	  MSG_AUX_PAUSE

#define ADKEY_AUX_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_UP,\
	/*0A*/	  MSG_VOL_DOWN,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\
	/*0D*/	  NO_MSG,\
	/*0E*/	  NO_MSG


#define ADKEY_AUX_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_UP,\
	/*0A*/	  MSG_VOL_DOWN,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\
	/*0D*/	  NO_MSG,\
	/*0E*/	  NO_MSG

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
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_ONE_KEY_TO_BT,\
	/*02*/	  MSG_ONE_KEY_TO_BT,\
	/*03*/	  NO_MSG,\
	/*04*/	  MSG_STANBY_KEY,\
	/*05*/	  MSG_BT_PREV_FILE,\
	/*06*/	  MSG_BT_NEXT_FILE,\
	/*07*/	  MSG_BT_MUSIC_EQ,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_UP,\
	/*0A*/	  MSG_VOL_DOWN,\
	/*0B*/	  MSG_CHANGE_WORKMODE,\
	/*0C*/	  MSG_COM_REC_REPLAY,\
	/*0D*/	  NO_MSG,\
	/*0E*/	  MSG_BT_PP

#define ADKEY_BT_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_UP,\
	/*0A*/	  MSG_VOL_DOWN,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\
	/*0D*/	  NO_MSG,\
	/*0E*/	  NO_MSG


#define ADKEY_BT_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_UP,\
	/*0A*/	  MSG_VOL_DOWN,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\
	/*0D*/	  NO_MSG,\
	/*0E*/	  NO_MSG

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
	/*01*/	  MSG_ONE_KEY_TO_BT,\
	/*02*/	  MSG_ONE_KEY_TO_BT,\
	/*03*/	  NO_MSG,\
	/*04*/	  MSG_STANBY_KEY,\
	/*05*/	  MSG_PC_PLAY_PREV,\
	/*06*/	  MSG_PC_PLAY_NEXT,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_UP,\
	/*0A*/	  MSG_VOL_DOWN,\
	/*0B*/	  MSG_CHANGE_WORKMODE,\
	/*0C*/	  NO_MSG,\
	/*0D*/	  NO_MSG,\
	/*0E*/	  MSG_PC_PP

#define ADKEY_USB_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_UP,\
	/*0A*/	  MSG_VOL_DOWN,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\
	/*0D*/	  NO_MSG,\
	/*0E*/	  NO_MSG


#define ADKEY_USB_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_UP,\
	/*0A*/	  MSG_VOL_DOWN,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\
	/*0D*/	  NO_MSG,\
	/*0E*/	  NO_MSG

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
	/*0D*/	 MSG_COM_REC_REPLAY,\
	/*0E*/	 NO_MSG

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
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	 NO_MSG,\
	/*0B*/	 NO_MSG,\
	/*0C*/	 NO_MSG,\
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
                        
