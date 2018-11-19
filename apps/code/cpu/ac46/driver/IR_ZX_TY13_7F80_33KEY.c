

#define IR_SYS_CODE			0x7F80

#define       IRC_STANBY           			 0 /*21*/
#define       IRC_MODE                         	1      /*01*/
#define       IRC_MUTE       			     2 /*22*/
#define       IRC_PLAY_PAUSE             3     /*03*/ 
#define       IRC_PREV                         4     /*04*/
#define       IRC_NEXT                          5   /*05*/  
#define       IRC_EQ                             6   /*06*/
#define       IRC_VOL_DN                   7       /*07*/ 
#define       IRC_VOL_UP                    8/*08*/ 
#define       IRC_NUM0                             9  /*09*/ 
#define       IRC_REPEAT                   10/*10*/ 
#define       IRC_USB_SD				11/*11*/
#define       IRC_NUM1                             12 /*12*/
#define       IRC_NUM2                             13/*13*/
#define       IRC_NUM3                            14/*14*/
#define       IRC_NUM4                            15/*15*/
#define       IRC_NUM5                            16/*16*/ 
#define       IRC_NUM6                            17/*17*/ 
#define       IRC_NUM7                            18/*18*/ 
#define       IRC_NUM8                            19/*19*/
#define       IRC_NUM9                            20 /*20*/
#define       IRC_VOICE      21
#define       IRC_REC      22
#define       IRC_REPLAY     23
#define       IRC_REC_DEL  24
#define       IRC_MIC_PRIORITY  25
#define       IRC_TRE_DN   26
#define       IRC_TRE_UP  27
#define       IRC_BASS_DN 28
#define       IRC_BASS_UP 29
#define       IRC_SUB_DN  30
#define       IRC_SUB_UP  31
#define       IRC_MIC_DN  32
#define       IRC_MIC_UP  33
#define       IRC_ECHO_DN 34
#define       IRC_ECHO_UP 35

/*      0X7F80
 MUTE     power
 1E      12       

PREV    PP   NEXT      
0A      1B  	1F

MODE     VOICE    REPEAT    
0C 	     0D   	0E

REC     REPLAY     R-DEL
00       0F   	19

ECHO-  ECHO+  M-PRI
09      07      1A

BASS- BASS+  TREBLE- TEREBLE+
08     17      16      15

M.VOL+   EQ     VOL+
02       01      06

M.VOL-  0       VOL-
03      04       05

1        2		3
14 	  18		    13

4	  5		6
11	 10 		0B

7	  8		9
5C	 1D 		1C

*/

const u8 IRTab0[] = 	   /*user code is 0xFF00*/
{
	/*0x00*/IRC_REC,//0
	/*0x01*/IRC_EQ,// 1
	/*0x02*/IRC_MIC_UP,//02
	/*0x03*/IRC_MIC_DN,//03
	/*0x04*/IRC_NUM0,//04
	/*0x05*/IRC_VOL_DN,//05
	/*0x06*/IRC_VOL_UP,//06
	/*0x07*/IRC_ECHO_UP,//07
	/*0x08*/IRC_BASS_DN,//08
	/*0x09*/IRC_ECHO_DN,//09
	/*0x0a*/IRC_PREV,//10
	/*0x0b*/IRC_NUM6,//11
	/*0x0c*/IRC_MODE,//12
	/*0x0d*/IRC_VOICE,//13
	/*0x0e*/IRC_REPEAT,//14
	/*0x0f*/IRC_REPLAY,//15
	/*0x10*/IRC_NUM5,//16
	/*0x11*/IRC_NUM4,//17
	/*0x12*/IRC_STANBY,//18
	/*0x13*/IRC_NUM3,//19
	/*0x14*/IRC_NUM1,//20
	/*0x15*/IRC_TRE_UP,//21
	/*0x16*/IRC_TRE_DN,//22
	/*0x17*/IRC_BASS_UP,//23
	/*0x18*/IRC_NUM2,//24
	/*0x19*/IRC_REC_DEL,//25
	/*0x1a*/IRC_MIC_PRIORITY,//26
	/*0x1b*/IRC_PLAY_PAUSE,//27
	/*0x1c*/IRC_NUM9,//28
	/*0x1d*/IRC_NUM8,//29
	/*0x1e*/IRC_MUTE,//30
	/*0x1f*/IRC_NEXT,//31
	
	//NKEY_20, NKEY_21, NKEY_22, NKEY_23, NKEY_24, NKEY_25, NKEY_26, NKEY_27, NKEY_28, NKEY_29, NKEY_2A, NKEY_2B, NKEY_2C, NKEY_2D, NKEY_2E, NKEY_2F,
	//NKEY_30, NKEY_31, NKEY_32, NKEY_33, NKEY_34, NKEY_35, NKEY_36, NKEY_37, NKEY_38, NKEY_39, NKEY_3A, NKEY_3B, NKEY_3C, NKEY_3D, NKEY_3E, NKEY_3F,
	
	/*0x40*/0XFF,//64
	/*0x41*/0XFF,// 65
	/*0x42*/0XFF,//66
	/*0x43*/0XFF,//67
	/*0x44*/0XFF,//68
	/*0x45*/0XFF,//69
	/*0x46*/0XFF,//70
	/*0x47*/0XFF,//71
	/*0x48*/0XFF,//72
	/*0x49*/0XFF,//73
	/*0x4a*/0XFF,//74
	/*0x4b*/0XFF,//75
	/*0x4c*/0XFF,//76
	/*0x4d*/0XFF,//77
	/*0x4e*/0XFF,//78
	/*0x4f*/0XFF,//79
	/*0x50*/0XFF,//80
	/*0x51*/0XFF,//81
	/*0x52*/0XFF,//82
	/*0x53*/0XFF,//83
	/*0x54*/0XFF,//84
	/*0x55*/0XFF,//85
	/*0x56*/0XFF,//86
	/*0x57*/0XFF,//87
	/*0x58*/0XFF,//88
	/*0x59*/0XFF,//89
	/*0x5a*/0XFF,//90
	/*0x5b*/0XFF,//91
	/*0x5c*/IRC_NUM7,//92
	/*0x5d*/0XFF,//93
	/*0x5e*/0XFF,//94
	/*0x5f*/0XFF,//95
};







