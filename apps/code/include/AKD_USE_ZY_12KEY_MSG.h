


/*

0R P/P 1K-REC 3.3K-MODE    5.1K- VOL+  7.5K-VOL- 
 10K-REP/DEL15K-EQ   20K-NEXT  33K-PREV 47K-FOL+ 68K U/SD 
 100KSTOP  
 
*/


/*******************************************************************
                        MUSIC   AD按键表
*******************************************************************/

#define ADKEY_DECODE_SHORT		\
                        /*00*/    MSG_MUSIC_STOP,\
                        /*01*/    MSG_MUSIC_U_SD,\
                        /*02*/    MSG_FOLDER_NEXT,\
                        /*03*/    MSG_MUSIC_PREV_FILE,\
                        /*04*/    MSG_MUSIC_NEXT_FILE,\
                        /*05*/    MSG_MUSIC_EQ,\
                        /*06*/    MSG_MUSIC_RPT,\
                        /*07*/    MSG_VOL_DOWN,\
                        /*08*/    MSG_VOL_UP,\
                        /*09*/    MSG_CHANGE_WORKMODE,\
                      	/*0A*/	  MSG_REC_REPLAY,\
                      	/*0B*/	  MSG_MUSIC_PP

#define ADKEY_DECODE_LONG		\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    MSG_MUSIC_DEL_FILE,\
                        /*07*/    MSG_VOL_DOWN,\
                        /*08*/    MSG_VOL_UP,\
                        /*09*/    NO_MSG,\
                    	/*0A*/	 MSG_REC_START,\
                    	/*0B*/	 NO_MSG

#define ADKEY_DECODE_HOLD		\
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
						/*0A*/	 NO_MSG,\
						/*0B*/	 NO_MSG


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
					/*0A*/	 NO_MSG,\
					/*0B*/	 NO_MSG



/*******************************************************************
                        FM   AD按键表
*******************************************************************/

#define ADKEY_FM_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOL_UP,\
	/*04*/	  MSG_FM_PREV_STATION,\
	/*05*/	  MSG_ONE_KEY_TO_RADIO,\
	/*06*/	  MSG_MUSIC_EQ,\
	/*07*/	  MSG_MUSIC_RPT,\
	/*08*/	  MSG_FM_NEXT_STATION,\
	/*09*/	  MSG_VOL_DOWN,\
	/*0A*/	  MSG_CHANGE_WORKMODE,\
	/*0B*/	  MSG_MUSIC_U_SD,\
	/*0C*/	  MSG_FM_SCAN_ALL_INIT,\
	/*0D*/	  MSG_MUSIC_STOP,\
	/*0E*/	  MSG_ONE_KEY_TO_AUX

#define ADKEY_FM_LONG		\
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
	/*0A*/	 NO_MSG,\
	/*0B*/	 NO_MSG


#define ADKEY_FM_HOLD		\
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
	/*0A*/	 NO_MSG,\
	/*0B*/	 NO_MSG

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
	/*0B*/	 NO_MSG
                        
/*******************************************************************
                         LINE    AD按键表
*******************************************************************/

#define ADKEY_AUX_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOL_UP,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_ONE_KEY_TO_RADIO,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_DOWN,\
	/*0A*/	  MSG_CHANGE_WORKMODE,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  MSG_AUX_PAUSE,\
	/*0D*/	  NO_MSG,\
	/*0E*/	  MSG_ONE_KEY_TO_AUX

#define ADKEY_AUX_LONG		\	
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
	/*0A*/	 NO_MSG,\
	/*0B*/	 NO_MSG
	



#define ADKEY_AUX_HOLD		\
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
	/*0A*/	 NO_MSG,\
	/*0B*/	 NO_MSG

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
	/*0B*/	 NO_MSG


/*******************************************************************
                         BT   AD按键表
*******************************************************************/


#define ADKEY_BT_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOL_UP,\
	/*04*/	  MSG_BT_PREV_FILE,\
	/*05*/	  MSG_ONE_KEY_TO_RADIO,\
	/*06*/	  MSG_BT_MUSIC_EQ,\
	/*07*/	  MSG_MUSIC_RPT,\
	/*08*/	  MSG_BT_NEXT_FILE,\
	/*09*/	  MSG_VOL_DOWN,\
	/*0A*/	  MSG_CHANGE_WORKMODE,\
	/*0B*/	  MSG_MUSIC_U_SD,\
	/*0C*/	  MSG_BT_PP,\
	/*0D*/	  MSG_BT_PP,\
	/*0E*/	  MSG_ONE_KEY_TO_AUX

#define ADKEY_BT_LONG		\
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
	/*0A*/	 NO_MSG,\
	/*0B*/	 NO_MSG



#define ADKEY_BT_HOLD		\
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
	/*0A*/	 NO_MSG,\
	/*0B*/	 NO_MSG


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
	/*0B*/	 NO_MSG


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
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  NO_MSG,\
	/*0A*/	 NO_MSG,\
	/*0B*/	 NO_MSG



#define ADKEY_USB_HOLD		\
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
	/*0A*/	 NO_MSG,\
	/*0B*/	 NO_MSG


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
	/*0B*/	 NO_MSG

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
	/*0B*/	 NO_MSG

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
	/*0B*/	 NO_MSG


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
	/*0B*/	 NO_MSG

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
	/*0B*/	 NO_MSG


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
	/*0B*/	 NO_MSG

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
	/*0B*/	 NO_MSG

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
	/*0B*/	 NO_MSG

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
	/*0B*/	 NO_MSG

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
	/*0A*/	 NO_MSG,\
	/*0B*/	 NO_MSG

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
	/*0B*/	 NO_MSG


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
	/*0B*/	 NO_MSG


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
	/*0B*/	 NO_MSG


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
		/*09*/	  MSG_ONE_KEY_TO_MP3,\
		/*0A*/	  MSG_REC_PP
	
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
		/*0A*/	  NO_MSG
	
	
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
		/*0A*/	  NO_MSG
	
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
		/*0A*/	  NO_MSG
#endif

                        
