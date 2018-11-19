
#define IR_SYS_CODE			0xff00


#define       IRC_STANBY           			 0 /*21*/
#define       IRC_MODE                         	1      /*01*/
#define       IRC_MUTE       			     2 /*22*/
#define       IRC_PLAY_PAUSE             3     /*03*/ 
#define       IRC_PREV                         4     /*04*/
#define       IRC_NEXT                          5   /*05*/  
#define       IRC_EQ                             6   /*06*/
#define       IRC_VOL_DN                   7       /*07*/ 
#define       IRC_VOL_UP                    8/*08*/ 
#define       IRC_STOP				9  /*09*/ 
#define       IRC_REPEAT                   10/*10*/ 
#define       IRC_FM_SCAN				11/*11*/
#define       IRC_TRE_DN   12
#define       IRC_TRE_UP  13
#define       IRC_BASS_DN 14
#define       IRC_BASS_UP 15
#define       IRC_SUB_DN  16
#define       IRC_SUB_UP  17
#define       IRC_RESET	18
#define       IRC_FM_SCAN_DN			19
#define       IRC_FM_SCAN_UP			20



/*              

POWER  	MODE  MUTE
 45      	46       44

		V+
		43
		
PREV/C-		NEXT/C+
0C				5E

		V-
		09
		
REP  	   PP		STOP
1C		18		5A

TUN+	TUN-   SCAN
52		42		4A

TRE+	RESET	BASS+
16		07		47

TRE-  	EQ		BASS-
19		08		0D

SUB+			SUB-
40				15

*/


// 003 ff00
const u8 IRTab0[] = 	   /*user code is 0xFF00*/
{
/*0x00*/0XFF,//0
/*0x01*/0XFF,// 1
/*0x02*/0XFF,//02
/*0x03*/0XFF,//03
/*0x04*/0XFF,//04
/*0x05*/0XFF,//05
/*0x06*/0XFF,//06
/*0x07*/IRC_PREV,//07
/*0x08*/IRC_EQ,//08
/*0x09*/IRC_VOL_DN,//09
/*0x0a*/0XFF,//10
/*0x0b*/0XFF,//11
/*0x0c*/IRC_PREV,//12
/*0x0d*/IRC_BASS_DN,//13
/*0x0e*/0XFF ,//14
/*0x0f*/0XFF,//15
/*0x10*/0XFF,//16
/*0x11*/0XFF,//17
/*0x12*/0XFF,//18
/*0x13*/0XFF,//19
/*0x14*/0XFF,//20
/*0x15*/IRC_SUB_DN,//21
/*0x16*/IRC_TRE_UP,//22
/*0x17*/0XFF,//23
/*0x18*/IRC_PLAY_PAUSE,//24
/*0x19*/IRC_TRE_DN,//25
/*0x1a*/0XFF,//26
/*0x1b*/0XFF,//27
/*0x1c*/IRC_REPEAT,//28
/*0x1d*/0XFF,//29
/*0x1e*/0XFF,//30
/*0x1f*/0XFF,//31

//NKEY_20, NKEY_21, NKEY_22, NKEY_23, NKEY_24, NKEY_25, NKEY_26, NKEY_27, NKEY_28, NKEY_29, NKEY_2A, NKEY_2B, NKEY_2C, NKEY_2D, NKEY_2E, NKEY_2F,
//NKEY_30, NKEY_31, NKEY_32, NKEY_33, NKEY_34, NKEY_35, NKEY_36, NKEY_37, NKEY_38, NKEY_39, NKEY_3A, NKEY_3B, NKEY_3C, NKEY_3D, NKEY_3E, NKEY_3F,

/*0x40*/ IRC_SUB_UP,//64
/*0x41*/0XFF,// 65
/*0x42*/IRC_FM_SCAN_DN,//66
/*0x43*/IRC_VOL_UP,//67
/*0x44*/IRC_MUTE,//68
/*0x45*/IRC_STANBY,//69
/*0x46*/IRC_MODE,//70
/*0x47*/IRC_BASS_UP,//71
/*0x48*/0XFF,//72
/*0x49*/0XFF,//73
/*0x4a*/IRC_FM_SCAN,//74
/*0x4b*/0XFF,//75
/*0x4c*/0XFF,//76
/*0x4d*/0XFF,//77
/*0x4e*/0XFF,//78
/*0x4f*/0XFF,//79
/*0x50*/0XFF,//80
/*0x51*/0XFF,//81
/*0x52*/ IRC_FM_SCAN_UP,//82
/*0x53*/0XFF,//83
/*0x54*/0XFF,//84
/*0x55*/ 0XFF,//85
/*0x56*/ 0XFF,//86
/*0x57*/0XFF,//87
/*0x58*/0XFF,//88
/*0x59*/0XFF,//89
/*0x5a*/IRC_STOP,//90
/*0x5b*/0XFF,//91
/*0x5c*/0XFF,//92
/*0x5d*/0XFF,//93
/*0x5e*/IRC_NEXT,//94
/*0x5f*/0XFF,//95
};



