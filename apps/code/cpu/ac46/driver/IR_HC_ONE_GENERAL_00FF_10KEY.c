

#define IR_SYS_CODE			0xff00

#define       IRC_FM           			 0 /*21*/
#define       IRC_MP3                         	1      /*01*/
#define       IRC_BT       			     2 /*22*/
#define       IRC_USB             3     /*03*/ 
#define       IRC_SD                         4     /*04*/
#define       IRC_AUX                          5   /*05*/  
#define       IRC_PREV                             6   /*06*/
#define       IRC_NEXT                   7       /*07*/ 
#define       IRC_PLAY_PAUSE                    8/*08*/ 
#define       IRC_MODE                            9  /*09*/ 

/* 0XFF00  10KEY
FM  MP3  BT
01  02   03

USB  SD  AUX
04   05   06

PREV  NEXT  PP
07     09   15

MODE
44

*/

const u8 IRTab0[] = 	   /*user code is 0xFF00*/
{
	/*0x00*/0XFF,//0
	/*0x01*/IRC_FM,// 1
	/*0x02*/IRC_MP3,//02
	/*0x03*/IRC_BT,//03
	/*0x04*/IRC_USB,//04
	/*0x05*/IRC_SD,//05
	/*0x06*/IRC_AUX,//06
	/*0x07*/IRC_PREV,//07
	/*0x08*/0XFF,//08
	/*0x09*/IRC_NEXT,//09
	/*0x0a*/0XFF,//10
	/*0x0b*/0XFF,//11
	/*0x0c*/0XFF,//12
	/*0x0d*/0XFF,//13
	/*0x0e*/0XFF ,//14
	/*0x0f*/IRC_PLAY_PAUSE,//15
	/*0x10*/0XFF,//16
	/*0x11*/0XFF,//17
	/*0x12*/0XFF,//18
	/*0x13*/0XFF,//19
	/*0x14*/0XFF,//20
	/*0x15*/0XFF,//21
	/*0x16*/0XFF,//22
	/*0x17*/0XFF,//23
	/*0x18*/0XFF,//24
	/*0x19*/0XFF,//25
	/*0x1a*/0XFF,//26
	/*0x1b*/0XFF,//27
	/*0x1c*/0XFF,//28
	/*0x1d*/0XFF,//29
	/*0x1e*/0XFF,//30
	/*0x1f*/0XFF,//31
	
	//NKEY_20, NKEY_21, NKEY_22, NKEY_23, NKEY_24, NKEY_25, NKEY_26, NKEY_27, NKEY_28, NKEY_29, NKEY_2A, NKEY_2B, NKEY_2C, NKEY_2D, NKEY_2E, NKEY_2F,
	//NKEY_30, NKEY_31, NKEY_32, NKEY_33, NKEY_34, NKEY_35, NKEY_36, NKEY_37, NKEY_38, NKEY_39, NKEY_3A, NKEY_3B, NKEY_3C, NKEY_3D, NKEY_3E, NKEY_3F,
	
	/*0x40*/0XFF,//64
	/*0x41*/0XFF,// 65
	/*0x42*/0XFF,//66
	/*0x43*/0XFF,//67
	/*0x44*/IRC_MODE,//68
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
	/*0x5c*/0XFF,//92
	/*0x5d*/0XFF,//93
	/*0x5e*/0XFF,//94
	/*0x5f*/0XFF,//95
};







