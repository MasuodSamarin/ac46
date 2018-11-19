
/*******************************************************************
                        MUSIC   AD������
*******************************************************************/
#define ADKEY_DECODE_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_MUSIC_EQ,\
	/*02rec*/	  NO_MSG,\
	/*03*/	  MSG_MUSIC_STOP,\
	/*04*/	  MSG_CHANGE_WORKMODE,\
	/*05*/	  MSG_MUSIC_PREV_FILE,\
	/*06*/	  MSG_MUSIC_NEXT_FILE,\
	/*07*/	  MSG_MUSIC_EQ,\
	/*08*/	  MSG_MUSIC_RPT,\
	/*09*/	  MSG_MUSIC_NEXT_FILE,\
	/*0A*/	  MSG_MUSIC_PREV_FILE,\
	/*0B*/	  MSG_MUSIC_PP
#define ADKEY_DECODE_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02rec*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  MSG_STANBY_KEY,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_MUSIC_FF,\
	/*0A*/	  MSG_MUSIC_FR,\
	/*0B*/	  NO_MSG

#define ADKEY_DECODE_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02rec*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG

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
                        FM   AD������
*******************************************************************/

#define ADKEY_FM_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02rec*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  MSG_CHANGE_WORKMODE,\
	/*05*/	  MSG_FM_PREV_STATION,\
	/*06*/	  MSG_FM_NEXT_STATION,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_FM_NEXT_STATION,\
	/*0A*/	  MSG_FM_PREV_STATION,\
	/*0B*/	  MSG_FM_SCAN_ALL_INIT

#define ADKEY_FM_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02rec*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  MSG_STANBY_KEY,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_FM_NEXT_STEP,\
	/*0A*/	  MSG_FM_PREV_STEP,\
	/*0B*/	  NO_MSG


#define ADKEY_FM_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02rec*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_DOWN,\
	/*0A*/	  MSG_VOL_UP,\
	/*0B*/	  NO_MSG

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
                         LINE    AD������
*******************************************************************/

#define ADKEY_AUX_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02rec*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  MSG_CHANGE_WORKMODE,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_UP,\
	/*0A*/	  MSG_VOL_DOWN,\
	/*0B*/	  MSG_AUX_PAUSE

#define ADKEY_AUX_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02rec*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  MSG_STANBY_KEY,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_DOWN,\
	/*0A*/	  MSG_VOL_UP,\
	/*0B*/	  NO_MSG


#define ADKEY_AUX_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02rec*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_DOWN,\
	/*0A*/	  MSG_VOL_UP,\
	/*0B*/	  NO_MSG

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
                         BT   AD������
*******************************************************************/


#define ADKEY_BT_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_BT_MUSIC_EQ,\
	/*02rec*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  MSG_CHANGE_WORKMODE,\
	/*05*/	  MSG_BT_PREV_FILE,\
	/*06*/	  MSG_BT_NEXT_FILE,\
	/*07*/	  MSG_BT_MUSIC_EQ,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_BT_NEXT_FILE,\
	/*0A*/	  MSG_BT_PREV_FILE,\
	/*0B*/	  MSG_BT_PP

#define ADKEY_BT_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02rec*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  MSG_STANBY_KEY,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_DOWN,\
	/*0A*/	  MSG_VOL_UP,\
	/*0B*/	  NO_MSG


#define ADKEY_BT_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02rec*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_DOWN,\
	/*0A*/	  MSG_VOL_UP,\
	/*0B*/	  NO_MSG

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
                         USB   AD������
*******************************************************************/
#define ADKEY_USB_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02rec*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  MSG_CHANGE_WORKMODE,\
	/*05*/	  MSG_PC_PLAY_PREV,\
	/*06*/	  MSG_PC_PLAY_NEXT,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_PC_PLAY_NEXT,\
	/*0A*/	  MSG_PC_PLAY_PREV,\
	/*0B*/	  MSG_PC_PP

#define ADKEY_USB_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02rec*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  MSG_STANBY_KEY,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_DOWN,\
	/*0A*/	  MSG_VOL_UP,\
	/*0B*/	  NO_MSG


#define ADKEY_USB_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02rec*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_VOL_DOWN,\
	/*0A*/	  MSG_VOL_UP,\
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
                            main ������
*******************************************************************/
#define ADKEY_MAIN_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  MSG_CHANGE_WORKMODE,\
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
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG

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
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG


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
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG

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
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG

/*******************************************************************
                            AD������
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
	/*0A*/	  MSG_STANBY_KEY,\
	/*0B*/	  MSG_STANBY_KEY

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
                        
