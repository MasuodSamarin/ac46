
/*



1				1K
2				2K
3				3K3
4				5K1
5				7K5
6				10K
7				15K
8				20K
9				33K
0				47K
FOL+			68K
REPLAY			100K

P/P				0R
U/SD			1K
MODE			3K3
VOL+			5K2
VOL-			7K5
STOP			11K
EQ				15K
NEXT			20K
PRE				33K
FM				47K
AUX			68K
REP/DEL		100K

1				1K
2				2K
3				3K3
4				5K1
5				7K5
6				10K
7				15K
8				20K
9				33K
0				47K
FOL+			68K
REPLAY			100K

*/
/*******************************************************************
                        MUSIC   AD按键表
*******************************************************************/

#define ADKEY_DECODE_SHORT		\
	/*00*/	  MSG_MUSIC_STOP,\
	/*01*/	  MSG_ONE_KEY_TO_AUX,\
	/*02*/	  MSG_ONE_KEY_TO_RADIO,\
	/*03*/	  MSG_MUSIC_PREV_FILE,\
	/*04*/	  MSG_MUSIC_NEXT_FILE,\
	/*05*/	  MSG_MUSIC_EQ ,\
	/*06*/	  MSG_MUSIC_RPT ,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  MSG_CHANGE_WORKMODE,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  MSG_MUSIC_U_SD,\
	/*0C*/	  MSG_MUSIC_PP,\	
	/*00*/	   MSG_ONE_KEY_START_REC,\
	/*01*/	   MSG_FOLDER_NEXT,\
	/*02*/	   MSG_0,\
	/*03*/	   MSG_9,\
	/*04*/	   MSG_8,\
	/*05*/	   MSG_7,\
	/*06*/	   MSG_6,\
	/*07*/	   MSG_5,\
	/*08*/	   MSG_4,\
	/*09*/	   MSG_3,\
	/*0A*/	   MSG_2,\
	/*0B*/	   MSG_1,\
	/*0C*/	  NO_MSG
	
#define ADKEY_DECODE_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOL_DOWN,\
	/*04*/	  MSG_VOL_UP,\
	/*05*/	  NO_MSG ,\
	/*06*/	  MSG_MUSIC_DEL_FILE ,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\		
	/*00*/	  MSG_REC_REPLAY,\
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

#define ADKEY_DECODE_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOL_DOWN,\
	/*04*/	  MSG_VOL_UP,\
	/*05*/	  NO_MSG ,\
	/*06*/	  NO_MSG ,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
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
                        FM   AD按键表
*******************************************************************/

#define ADKEY_FM_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_ONE_KEY_TO_AUX,\
	/*02*/	  MSG_ONE_KEY_TO_RADIO,\
	/*03*/	  MSG_FM_PREV_STATION,\
	/*04*/	  MSG_FM_NEXT_STATION,\
	/*05*/	  NO_MSG ,\
	/*06*/	  NO_MSG ,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  MSG_CHANGE_WORKMODE,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  MSG_FM_SCAN_ALL_INIT,\	
	/*00*/	   MSG_REC_START,\
	/*01*/	   NO_MSG,\
	/*02*/	   MSG_0,\
	/*03*/	   MSG_9,\
	/*04*/	   MSG_8,\
	/*05*/	   MSG_7,\
	/*06*/	   MSG_6,\
	/*07*/	   MSG_5,\
	/*08*/	   MSG_4,\
	/*09*/	   MSG_3,\
	/*0A*/	   MSG_2,\
	/*0B*/	   MSG_1,\
	/*0C*/	  NO_MSG
	
#define ADKEY_FM_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOL_DOWN,\
	/*04*/	  MSG_VOL_UP,\
	/*05*/	  NO_MSG ,\
	/*06*/	  NO_MSG ,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\	
	/*00*/	  MSG_COM_REC_REPLAY,\
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


#define ADKEY_FM_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOL_DOWN,\
	/*04*/	  MSG_VOL_UP,\
	/*05*/	  NO_MSG ,\
	/*06*/	  NO_MSG ,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
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
                         LINE    AD按键表
*******************************************************************/

#define ADKEY_AUX_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_ONE_KEY_TO_AUX,\
	/*02*/	  MSG_ONE_KEY_TO_RADIO,\
	/*03*/	  MSG_VOL_DOWN,\
	/*04*/	  MSG_VOL_UP,\
	/*05*/	  NO_MSG ,\
	/*06*/	  NO_MSG ,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  MSG_CHANGE_WORKMODE,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  MSG_AUX_PAUSE,\	
	/*00*/	   MSG_REC_START,\
	/*01*/	   NO_MSG,\
	/*02*/	   NO_MSG,\
	/*03*/	   NO_MSG,\
	/*04*/	   NO_MSG,\
	/*05*/	   NO_MSG,\
	/*06*/	   NO_MSG,\
	/*07*/	   NO_MSG,\
	/*08*/	   NO_MSG,\
	/*09*/	   NO_MSG,\
	/*0A*/	   NO_MSG,\
	/*0B*/	   NO_MSG,\
	/*0C*/	  NO_MSG
	


#define ADKEY_AUX_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOL_DOWN,\
	/*04*/	  MSG_VOL_UP,\
	/*05*/	  NO_MSG ,\
	/*06*/	  NO_MSG ,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  NO_MSG,\	
	/*00*/	  MSG_COM_REC_REPLAY,\
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
	

#define ADKEY_AUX_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOL_DOWN,\
	/*04*/	  MSG_VOL_UP,\
	/*05*/	  NO_MSG ,\
	/*06*/	  NO_MSG ,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
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
	/*01*/	  MSG_ONE_KEY_TO_AUX,\
	/*02*/	  MSG_ONE_KEY_TO_RADIO,\
	/*03*/	  MSG_BT_PREV_FILE,\
	/*04*/	  MSG_BT_NEXT_FILE,\
	/*05*/	  NO_MSG ,\
	/*06*/	  NO_MSG ,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  MSG_CHANGE_WORKMODE,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  MSG_BT_PP,\	
	/*00*/	   NO_MSG,\
	/*01*/	   NO_MSG,\
	/*02*/	   NO_MSG,\
	/*03*/	   NO_MSG,\
	/*04*/	   NO_MSG,\
	/*05*/	   NO_MSG,\
	/*06*/	   NO_MSG,\
	/*07*/	   NO_MSG,\
	/*08*/	   NO_MSG,\
	/*09*/	   NO_MSG,\
	/*0A*/	   NO_MSG,\
	/*0B*/	   NO_MSG,\
	/*0C*/	  NO_MSG


#define ADKEY_BT_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOL_DOWN,\
	/*04*/	  MSG_VOL_UP,\
	/*05*/	  NO_MSG ,\
	/*06*/	  NO_MSG ,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
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


#define ADKEY_BT_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOL_DOWN,\
	/*04*/	  MSG_VOL_UP,\
	/*05*/	  NO_MSG ,\
	/*06*/	  NO_MSG ,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
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
	/*01*/	  MSG_ONE_KEY_TO_AUX,\
	/*02*/	  MSG_ONE_KEY_TO_RADIO,\
	/*03*/	  MSG_PC_PLAY_PREV,\
	/*04*/	  MSG_PC_PLAY_NEXT,\
	/*05*/	  NO_MSG ,\
	/*06*/	  NO_MSG ,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
	/*09*/	  MSG_CHANGE_WORKMODE,\
	/*0A*/	  NO_MSG,\
	/*0B*/	  NO_MSG,\
	/*0C*/	  MSG_PC_PP,\	
	/*00*/	   NO_MSG,\
	/*01*/	   NO_MSG,\
	/*02*/	   NO_MSG,\
	/*03*/	   NO_MSG,\
	/*04*/	   NO_MSG,\
	/*05*/	   NO_MSG,\
	/*06*/	   NO_MSG,\
	/*07*/	   NO_MSG,\
	/*08*/	   NO_MSG,\
	/*09*/	   NO_MSG,\
	/*0A*/	   NO_MSG,\
	/*0B*/	   NO_MSG,\
	/*0C*/	  NO_MSG



#define ADKEY_USB_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOL_DOWN,\
	/*04*/	  MSG_VOL_UP,\
	/*05*/	  NO_MSG ,\
	/*06*/	  NO_MSG ,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
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


#define ADKEY_USB_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOL_DOWN,\
	/*04*/	  MSG_VOL_UP,\
	/*05*/	  NO_MSG ,\
	/*06*/	  NO_MSG ,\
	/*07*/	  MSG_VOL_DOWN,\
	/*08*/	  MSG_VOL_UP,\
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
	/*00*/	  MSG_ONE_KEY_TO_MP3,\
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
                        
