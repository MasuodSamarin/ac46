

/*
#define PULL_UP_RESISTANCE 10   //上拉电阻22K
#define KEYC_RES 0   //pp
#define KEYB_RES 3.3   //mode
#define KEYA_RES 5.1   //fm
#define KEY9_RES 7.5 //aux
#define KEY8_RES 10  //repeat/del
#define KEY7_RES 15  //eq
#define KEY6_RES 20  //next/v+
#define KEY5_RES 33  //prev/v-
#define KEY4_RES 47  //usb/sd
#define KEY3_RES 56 //v+
#define KEY2_RES 68 //v-
#define KEY1_RES 100 //stop
#define KEY0_NOKEY_RES 330
*/
/*******************************************************************
                        MUSIC   AD按键表
*******************************************************************/

#define ADKEY_DECODE_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_MUSIC_STOP,\
	/*02*/	  MSG_VOL_DOWN,\
	/*03*/	  MSG_VOL_UP,\
	/*04*/	  MSG_MUSIC_U_SD,\
	/*05*/	  MSG_MUSIC_PREV_FILE,\
	/*06*/	  MSG_MUSIC_NEXT_FILE,\
	/*07*/	  MSG_MUSIC_EQ,\
	/*08*/	  MSG_MUSIC_RPT,\
	/*09*/	  MSG_ONE_KEY_TO_AUX,\
	/*0A*/	  MSG_ONE_KEY_TO_RADIO,\
	/*0B*/	  MSG_CHANGE_WORKMODE,\
	/*0C*/	  MSG_MUSIC_PP,\	
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_ONE_KEY_START_REC,\
	/*02*/	  MSG_FOLDER_NEXT,\
	/*03*/	  MSG_0,\
	/*04*/	  MSG_9,\
	/*05*/	  MSG_8,\
	/*06*/	  MSG_7,\
	/*07*/	  MSG_6,\
	/*08*/	  MSG_5,\
	/*09*/	  MSG_4,\
	/*0A*/	  MSG_3,\
	/*0B*/	  MSG_2,\
	/*0C*/	  MSG_1
#define ADKEY_DECODE_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  MSG_VOL_DOWN,\
	/*03*/	  MSG_VOL_UP,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  MSG_MUSIC_DEL_FILE,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  MSG_STANBY_KEY,\
	/*0C*/	  NO_MSG,\	
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_REC_REPLAY,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG

#define ADKEY_DECODE_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  MSG_VOL_DOWN,\
	/*03*/	  MSG_VOL_UP,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\	
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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG

#define ADKEY_DECODE_LONG_UP	\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  MSG_VOL_DOWN,\
	/*03*/	  MSG_VOL_UP,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\	
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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG

/*******************************************************************
                        FM   AD按键表
*******************************************************************/

#define ADKEY_FM_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_MUSIC_STOP,\
	/*02*/	  MSG_VOL_DOWN,\
	/*03*/	  MSG_VOL_UP,\
	/*04*/	  MSG_MUSIC_U_SD,\
	/*05*/	  MSG_FM_PREV_STATION,\
	/*06*/	  MSG_FM_NEXT_STATION,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_ONE_KEY_TO_AUX,\
	/*0A*/	  MSG_ONE_KEY_TO_RADIO,\
	/*0B*/	  MSG_CHANGE_WORKMODE,\
	/*0C*/	  MSG_FM_SCAN_ALL_INIT,\	
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_REC_START,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_0,\
	/*04*/	  MSG_9,\
	/*05*/	  MSG_8,\
	/*06*/	  MSG_7,\
	/*07*/	  MSG_6,\
	/*08*/	  MSG_5,\
	/*09*/	  MSG_4,\
	/*0A*/	  MSG_3,\
	/*0B*/	  MSG_2,\
	/*0C*/	  MSG_1

#define ADKEY_FM_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  MSG_VOL_DOWN,\
	/*03*/	  MSG_VOL_UP,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  MSG_STANBY_KEY,\
	/*0C*/	  NO_MSG,\	
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_COM_REC_REPLAY,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG


#define ADKEY_FM_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  MSG_VOL_DOWN,\
	/*03*/	  MSG_VOL_UP,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\	
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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG

#define ADKEY_FM_LONG_UP	\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  MSG_VOL_DOWN,\
	/*03*/	  MSG_VOL_UP,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\	
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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG
                        
/*******************************************************************
                         LINE    AD按键表
*******************************************************************/

#define ADKEY_AUX_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_MUSIC_STOP,\
	/*02*/	  MSG_VOL_DOWN,\
	/*03*/	  MSG_VOL_UP,\
	/*04*/	  MSG_MUSIC_U_SD,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_ONE_KEY_TO_AUX,\
	/*0A*/	  MSG_ONE_KEY_TO_RADIO,\
	/*0B*/	  MSG_CHANGE_WORKMODE,\
	/*0C*/	  MSG_AUX_PAUSE,\	
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_REC_START,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG

#define ADKEY_AUX_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  MSG_VOL_DOWN,\
	/*03*/	  MSG_VOL_UP,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  MSG_STANBY_KEY,\
	/*0C*/	  NO_MSG,\	
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_COM_REC_REPLAY,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG


#define ADKEY_AUX_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  MSG_VOL_DOWN,\
	/*03*/	  MSG_VOL_UP,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\	
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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG

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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\	
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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG


/*******************************************************************
                         BT   AD按键表
*******************************************************************/


#define ADKEY_BT_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_MUSIC_STOP,\
	/*02*/	  MSG_VOL_DOWN,\
	/*03*/	  MSG_VOL_UP,\
	/*04*/	  MSG_MUSIC_U_SD,\
	/*05*/	  MSG_BT_PREV_FILE,\
	/*06*/	  MSG_BT_NEXT_FILE,\
	/*07*/	  MSG_BT_MUSIC_EQ,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_ONE_KEY_TO_AUX,\
	/*0A*/	  MSG_ONE_KEY_TO_RADIO,\
	/*0B*/	  MSG_CHANGE_WORKMODE,\
	/*0C*/	  MSG_BT_PP,\	
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_REC_START,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG

#define ADKEY_BT_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  MSG_VOL_DOWN,\
	/*03*/	  MSG_VOL_UP,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  MSG_STANBY_KEY,\
	/*0C*/	  NO_MSG,\	
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_COM_REC_REPLAY,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG


#define ADKEY_BT_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  MSG_VOL_DOWN,\
	/*03*/	  MSG_VOL_UP,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\	
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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG

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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\	
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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG


/*******************************************************************
                         USB   AD按键表
*******************************************************************/
#define ADKEY_USB_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_MUSIC_STOP,\
	/*02*/	  MSG_VOL_DOWN,\
	/*03*/	  MSG_VOL_UP,\
	/*04*/	  MSG_MUSIC_U_SD,\
	/*05*/	  MSG_PC_PLAY_PREV,\
	/*06*/	  MSG_PC_PLAY_NEXT,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_ONE_KEY_TO_AUX,\
	/*0A*/	  MSG_ONE_KEY_TO_RADIO,\
	/*0B*/	  MSG_CHANGE_WORKMODE,\
	/*0C*/	  MSG_PC_PP,\	
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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG

#define ADKEY_USB_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  MSG_VOL_DOWN,\
	/*03*/	  MSG_VOL_UP,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  MSG_STANBY_KEY,\
	/*0C*/	  NO_MSG,\	
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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG


#define ADKEY_USB_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  MSG_VOL_DOWN,\
	/*03*/	  MSG_VOL_UP,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_VOL_DOWN,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\	
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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG

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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\	
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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG
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
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\	
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_ONE_KEY_TO_MP3,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG

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
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\	
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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG


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
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\	
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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG

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
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\	
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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG
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
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\	
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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG

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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\	
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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG


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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\	
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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG

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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\	
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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG

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
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\	
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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG

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
	/*0B*/	  MSG_STANBY_KEY,\
	/*0C*/	  NO_MSG,\	
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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG


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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\	
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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG

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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\	
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
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG
                        
