
#define IR_SYS_CODE			0xff00

#define IR_PREV_FOLDER            0  //
#define IR_MODE                   1
#define IR_NEXT_FOLDER            2
#define IR_PREV                   3
#define IR_NEXT                   4
#define IR_PLAY_PAUSE             5
#define IR_VOL_DN                 6
#define IR_VOL_UP                 7
#define IR_EQ                     8
#define IR_NUM0                   9
#define IR_10_PLUS                10
#define IR_100_PLUS               11
#define IR_NUM1                   12
#define IR_NUM2                   13
#define IR_NUM3                   14
#define IR_NUM4                   15
#define IR_NUM5                   16
#define IR_NUM6                   17
#define IR_NUM7                   18
#define IR_NUM8                   19
#define IR_NUM9                   20


/*      
MODE  PREV_FOLDER   NEXT_FOLDER
 45      46       47

PREV     NEXT     PP
44      40  	43

V-    V+     EQ  
07 	   15 	09

0     10+     100+
16       19  	0d

1        2		3
0c 	  18		 5e

4	  5		6
08	 1c 		5a

7	  8		9
42	 52 		4a

*/


const u8 IRTab0[] = 	   /*user code is 0xFF00*/
{
/*0x00*/0XFF,//0
/*0x01*/0XFF,// 1
/*0x02*/0XFF,//02
/*0x03*/0XFF,//03
/*0x04*/0XFF,//04
/*0x05*/0XFF,//05
/*0x06*/0XFF,//06
/*0x07*/IR_VOL_DN,//07
/*0x08*/IR_NUM4,//08
/*0x09*/IR_EQ,//09
/*0x0a*/0XFF,//10
/*0x0b*/0XFF,//11
/*0x0c*/IR_NUM1,//12
/*0x0d*/IR_100_PLUS,//13
/*0x0e*/0XFF ,//14
/*0x0f*/0XFF,//15
/*0x10*/0XFF,//16
/*0x11*/0XFF,//17
/*0x12*/0XFF,//18
/*0x13*/0XFF,//19
/*0x14*/0XFF,//20
/*0x15*/IR_VOL_UP,//21
/*0x16*/IR_NUM0,//22
/*0x17*/0XFF,//23
/*0x18*/IR_NUM2,//24
/*0x19*/IR_10_PLUS,//25
/*0x1a*/0XFF,//26
/*0x1b*/0XFF,//27
/*0x1c*/IR_NUM5,//28
/*0x1d*/0XFF,//29
/*0x1e*/0XFF,//30
/*0x1f*/0XFF,//31

//NKEY_20, NKEY_21, NKEY_22, NKEY_23, NKEY_24, NKEY_25, NKEY_26, NKEY_27, NKEY_28, NKEY_29, NKEY_2A, NKEY_2B, NKEY_2C, NKEY_2D, NKEY_2E, NKEY_2F,
//NKEY_30, NKEY_31, NKEY_32, NKEY_33, NKEY_34, NKEY_35, NKEY_36, NKEY_37, NKEY_38, NKEY_39, NKEY_3A, NKEY_3B, NKEY_3C, NKEY_3D, NKEY_3E, NKEY_3F,

/*0x40*/IR_NEXT,//64
/*0x41*/0XFF,// 65
/*0x42*/IR_NUM7,//66
/*0x43*/IR_PLAY_PAUSE,//67
/*0x44*/IR_PREV,//68
/*0x45*/IR_MODE,//69
/*0x46*/IR_PREV_FOLDER,//70
/*0x47*/IR_NEXT_FOLDER,//71
/*0x48*/0XFF,//72
/*0x49*/0XFF,//73
/*0x4a*/IR_NUM9,//74
/*0x4b*/0XFF,//75
/*0x4c*/0XFF,//76
/*0x4d*/0XFF,//77
/*0x4e*/0XFF,//78
/*0x4f*/0XFF,//79
/*0x50*/0XFF,//80
/*0x51*/0XFF,//81
/*0x52*/IR_NUM8,//82
/*0x53*/0XFF,//83
/*0x54*/0XFF,//84
/*0x55*/0XFF,//85
/*0x56*/0XFF,//86
/*0x57*/0XFF,//87
/*0x58*/0XFF,//88
/*0x59*/0XFF,//89
/*0x5a*/IR_NUM6,//90
/*0x5b*/0XFF,//91
/*0x5c*/0XFF,//92
/*0x5d*/0XFF,//93
/*0x5e*/IR_NUM3,//94
/*0x5f*/0XFF,//95
};









