
#define IR_SYS_CODE			0xFE01


#define       IRC_BT           			 0 /*21*/
#define       IRC_STANBY                 1      /*01*/
#define       IRC_CD_DVD       			     2 /*22*/
#define       IRC_USB_SD             3     /*03*/ 
#define       IRC_FM                         4     /*04*/
#define       IRC_CH_UP                          5   /*05*/  
#define       IRC_CH_DN                             6   /*06*/
#define       IRC_VOL_DN                   7       /*07*/ 
#define       IRC_VOL_UP                    8/*08*/ 
#define       IRC_RESET                             9  /*09*/ 
#define       IRC_FL_UP                   10/*10*/ 
#define       IRC_FL_DN				11/*11*/
#define       IRC_FR_UP                             12 /*12*/
#define       IRC_FR_DN                             13/*13*/
#define       IRC_TRE_UP                            14/*14*/
#define       IRC_TRE_DN                            15/*15*/
#define       IRC_MIC_UP                            16/*16*/ 
#define       IRC_MIC_DN                            17/*17*/ 
#define       IRC_ECHO_UP                            18/*18*/ 
#define       IRC_ECHO_DN                            19/*19*/
#define       IRC_SUB_UP                            20 /*20*/
#define       IRC_SUB_DN				21/*21*/
#define       IRC_MUTE                            22 /*22*/
#define       IRC_PREV                   23
#define       IRC_NEXT                  24
#define       IRC_PLAY_PAUSE             25


/*    0XFE01          
BT  STANDBY	
10      12       

CD/DVD	  USB/SD	 FM
01  	     02        03

CH+  	CH-		RESET
04 	     05 	      06

FL+	  TRE+	     FR+
07     08  	     09

FL-    TRE-        FR-
4a 	  00		     0b

MIC.VOL+	  		ECHO+
5a	               14

	  VOLUME+		
         1b

SUB-    MUTE      SUB+
1e       17        1a

       VOLUME-
         1f
       
MIC.VOL-           ECHO-
55                  18

PREV       PP       NEXT
42          41        40
*/


// 006  0xfe01
const u8 IRTab0[] = 
{
/*0x00*/IRC_TRE_DN,//0
/*0x01*/IRC_CD_DVD,// 1
/*0x02*/IRC_USB_SD,//02
/*0x03*/IRC_FM,//03
/*0x04*/IRC_CH_UP,//04
/*0x05*/IRC_CH_DN,//05
/*0x06*/IRC_RESET,//06
/*0x07*/IRC_FL_UP,//07
/*0x08*/IRC_TRE_UP,//08
/*0x09*/IRC_FR_UP,//09
/*0x0a*/0XFF,//10
/*0x0b*/IRC_FR_DN,//11
/*0x0c*/0XFF,//12
/*0x0d*/0XFF,//13
/*0x0e*/0XFF ,//14
/*0x0f*/0XFF,//15
/*0x10*/IRC_BT,//16
/*0x11*/0XFF,//17
/*0x12*/IRC_STANBY,//18
/*0x13*/0XFF,//19
/*0x14*/IRC_ECHO_UP,//20
/*0x15*/0XFF,//21
/*0x16*/0XFF,//22
/*0x17*/IRC_MUTE,//23
/*0x18*/IRC_ECHO_DN,//24
/*0x19*/0XFF,//25
/*0x1a*/IRC_SUB_UP,//26
/*0x1b*/IRC_VOL_UP,//27
/*0x1c*/0XFF,//28
/*0x1d*/0XFF,//29
/*0x1e*/IRC_SUB_DN,//30
/*0x1f*/IRC_VOL_DN,//31

//NKEY_20, NKEY_21, NKEY_22, NKEY_23, NKEY_24, NKEY_25, NKEY_26, NKEY_27, NKEY_28, NKEY_29, NKEY_2A, NKEY_2B, NKEY_2C, NKEY_2D, NKEY_2E, NKEY_2F,
//NKEY_30, NKEY_31, NKEY_32, NKEY_33, NKEY_34, NKEY_35, NKEY_36, NKEY_37, NKEY_38, NKEY_39, NKEY_3A, NKEY_3B, NKEY_3C, NKEY_3D, NKEY_3E, NKEY_3F,

/*0x40*/IRC_NEXT,//64
/*0x41*/IRC_PLAY_PAUSE,// 65
/*0x42*/IRC_PREV,//66
/*0x43*/0XFF,//67
/*0x44*/0XFF,//68
/*0x45*/0XFF,//69
/*0x46*/0XFF,//70
/*0x47*/0XFF,//71
/*0x48*/0XFF,//72
/*0x49*/0XFF,//73
/*0x4a*/IRC_FL_DN,//74
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
/*0x55*/IRC_MIC_DN,//85
/*0x56*/0XFF,//86
/*0x57*/0XFF,//87
/*0x58*/0XFF,//88
/*0x59*/0XFF,//89
/*0x5a*/IRC_MIC_UP,//90
/*0x5b*/0XFF,//91
/*0x5c*/0XFF,//92
/*0x5d*/0XFF,//93
/*0x5e*/0XFF,//94
/*0x5f*/0XFF,//95
};

