#define IR_SYS_CODE			0xff00
#define IR_SYS_CODE1		0x7F80
#define IR_SYS_CODE2		0xFE01

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
#define       IRC_FR                            21 /*20*/
#define       IRC_FF                            22 /*20*/
#define       IRC_CH_DN                         23 /*20*/
#define       IRC_CH_UP                            24 /*20*/
#define       IRC_STOP                            25 /*20*/

/*              
power mode   mute
 45      46       47

pp		prev    next    
44  	     40  	43

eq		vol-     vol+ 
7 	   15 		09

0       rep     usb/sd
16       19  		0D

1        2		3
0C 	  18		 5E

4	  5		6
8	 1C 		5A

7	  8		9
42	 52 		4A

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
/*0x07*/IRC_EQ,//07
/*0x08*/IRC_NUM4,//08
/*0x09*/IRC_VOL_UP,//09
/*0x0a*/0XFF,//10
/*0x0b*/0XFF,//11
/*0x0c*/IRC_NUM1,//12
/*0x0d*/IRC_USB_SD,//13
/*0x0e*/0XFF,//14
/*0x0f*/0XFF,//15
/*0x10*/0XFF,//16
/*0x11*/0XFF,//17
/*0x12*/0XFF,//18
/*0x13*/0XFF,//19
/*0x14*/0XFF,//20
/*0x15*/IRC_VOL_DN,//21
/*0x16*/IRC_NUM0,//22
/*0x17*/0XFF,//23
/*0x18*/IRC_NUM2,//24
/*0x19*/IRC_REPEAT,//25
/*0x1a*/0XFF,//26
/*0x1b*/0XFF,//27
/*0x1c*/IRC_NUM5,//28
/*0x1d*/0XFF,//29
/*0x1e*/0XFF,//30
/*0x1f*/0XFF,//31


/*0x40*/IRC_PREV,//64
/*0x41*/0XFF,// 65
/*0x42*/IRC_NUM7,//66
/*0x43*/IRC_NEXT,//67
/*0x44*/IRC_PLAY_PAUSE,//68
/*0x45*/IRC_STANBY,//69
/*0x46*/IRC_MODE,//70
/*0x47*/IRC_MUTE,//71
/*0x48*/0XFF,//72
/*0x49*/0XFF,//73
/*0x4a*/IRC_NUM9,//74
/*0x4b*/0XFF,//75
/*0x4c*/0XFF,//76
/*0x4d*/0XFF,//77
/*0x4e*/0XFF,//78
/*0x4f*/0XFF,//79
/*0x50*/0XFF,//80
/*0x51*/0XFF,//81
/*0x52*/IRC_NUM8,//82
/*0x53*/0XFF,//83
/*0x54*/0XFF,//84
/*0x55*/0XFF,//85
/*0x56*/0XFF,//86
/*0x57*/0XFF,//87
/*0x58*/0XFF,//88
/*0x59*/0XFF,//89
/*0x5a*/IRC_NUM6,//90
/*0x5b*/0XFF,//91
/*0x5c*/0XFF,//92
/*0x5d*/0XFF,//93
/*0x5e*/IRC_NUM3,//94
/*0x5f*/0XFF,//95
};


/*      
power mode   mute
 12      1a       1e

pp         pre  next
01  	     02  	03

eq     voldec  volinc
04 	   05 	06

0        rep      usb/scan
07       08  	09

1        2		3
0a 	  1b		 1f

4	  5		6
0c	 0d 		0e

7	  8		9
00	 0f 		19

*/


const u8 IRTab1[] = 	  //7F80
{
/*0x00*/IRC_NUM7,//0
/*0x01*/IRC_PLAY_PAUSE,// 1
/*0x02*/IRC_PREV,//02
/*0x03*/IRC_NEXT,//03
/*0x04*/IRC_EQ,//04
/*0x05*/IRC_VOL_DN,//05
/*0x06*/IRC_VOL_UP,//06
/*0x07*/IRC_NUM0,//07
/*0x08*/  IRC_REPEAT,//08
/*0x09*/IRC_USB_SD,//09
/*0x0a*/  IRC_NUM1,//10
/*0x0b*/ 0XFF,//11
/*0x0c*/IRC_NUM4,//12
/*0x0d*/IRC_NUM5,//13
/*0x0e*/ IRC_NUM6,//14
/*0x0f*/IRC_NUM8,//15
/*0x10*/0XFF,//16
/*0x11*/0XFF,//17
/*0x12*/IRC_STANBY,//18
/*0x13*/0XFF,//19
/*0x14*/0XFF,//20
/*0x15*/0XFF,//21
/*0x16*/0XFF,//22
/*0x17*/ 0XFF,//23
/*0x18*/ 0XFF,//24
/*0x19*/IRC_NUM9,//25
/*0x1a*/ IRC_MODE,//26
/*0x1b*/IRC_NUM2,//27
/*0x1c*/0XFF,//28
/*0x1d*/0XFF,//29
/*0x1e*/IRC_MUTE,//30
/*0x1f*/IRC_NUM3,//31

//NKEY_20, NKEY_21, NKEY_22, NKEY_23, NKEY_24, NKEY_25, NKEY_26, NKEY_27, NKEY_28, NKEY_29, NKEY_2A, NKEY_2B, NKEY_2C, NKEY_2D, NKEY_2E, NKEY_2F,
//NKEY_30, NKEY_31, NKEY_32, NKEY_33, NKEY_34, NKEY_35, NKEY_36, NKEY_37, NKEY_38, NKEY_39, NKEY_3A, NKEY_3B, NKEY_3C, NKEY_3D, NKEY_3E, NKEY_3F,

/*0x40*/ 0XFF,//64
/*0x41*/0XFF,// 65
/*0x42*/0XFF,//66
/*0x43*/0XFF,//67
/*0x44*/0XFF,//68
/*0x45*/0XFF,//69
/*0x46*/ 0XFF,//70
/*0x47*/ 0XFF,//71
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
/*0x52*/ 0XFF,//82
/*0x53*/0XFF,//83
/*0x54*/0XFF,//84
/*0x55*/ 0XFF,//85
/*0x56*/ 0XFF,//86
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

/*      0xFE01        
prev     pp	  next    
47  	     1E     55
*/

	/*	0xFE01   //two same sys code ir
	mode 1	 2	  3
	 59  58  18   19 
	
	4	  5    6	7	  
	4D	 0E   0D  51
	
	8	  9 	 0
	12	 11	45
	
	repeat		  mute	
	06				05
	
		   vol+
			5A
	
	prev	    pp		next
	1A		1B		 16 
	
		   vol-
		   15
	ch- 		   ch+
	52			50
	
	fr	   ff	  stop	  eq
	10	  13	       56	      54
	*/

const u8 IRTab2[] = 	   /*user code is 0xFF00*/
{
/*0x00*/0XFF,//0
/*0x01*/0XFF,// 1
/*0x02*/0XFF,//02
/*0x03*/0XFF,//03
/*0x04*/0XFF,//04
/*0x05*/IRC_MUTE,//05
/*0x06*/IRC_REPEAT,//06
/*0x07*/0XFF,//07
/*0x08*/0XFF,//08
/*0x09*/0XFF,//09
/*0x0a*/0XFF,//10
/*0x0b*/0XFF,//11
/*0x0c*/0XFF,//12
/*0x0d*/IRC_NUM6,//13
/*0x0e*/IRC_NUM5,//14
/*0x0f*/0XFF,//15
/*0x10*/IRC_FR,//16
/*0x11*/IRC_NUM9,//17
/*0x12*/IRC_NUM8,//18
/*0x13*/IRC_FF,//19
/*0x14*/0XFF,//20
/*0x15*/IRC_VOL_DN,//21
/*0x16*/IRC_NEXT,//22
/*0x17*/0XFF,//23
/*0x18*/IRC_NUM2,//24
/*0x19*/IRC_NUM3,//25
/*0x1a*/IRC_PREV,//26
/*0x1b*/IRC_PLAY_PAUSE,//27
/*0x1c*/0XFF,//28
/*0x1d*/0XFF,//29
/*0x1e*/IRC_PLAY_PAUSE,//30
/*0x1f*/0XFF,//31


/*0x40*/0XFF,//64
/*0x41*/0XFF,// 65
/*0x42*/0XFF,//66
/*0x43*/0XFF,//67
/*0x44*/0XFF,//68
/*0x45*/IRC_NUM0,//69
/*0x46*/0XFF,//70
/*0x47*/IRC_PREV,//71
/*0x48*/0XFF,//72
/*0x49*/0XFF,//73
/*0x4a*/0XFF,//74
/*0x4b*/0XFF,//75
/*0x4c*/0XFF,//76
/*0x4d*/IRC_NUM4,//77
/*0x4e*/0XFF,//78
/*0x4f*/0XFF,//79
/*0x50*/IRC_CH_UP,//80
/*0x51*/IRC_NUM7,//81
/*0x52*/IRC_CH_DN,//82
/*0x53*/0XFF,//83
/*0x54*/IRC_EQ,//84
/*0x55*/IRC_NEXT,//85
/*0x56*/IRC_STOP,//86
/*0x57*/0XFF,//87
/*0x58*/IRC_NUM1,//88
/*0x59*/IRC_MODE,//89
/*0x5a*/IRC_VOL_UP,//90
/*0x5b*/0XFF,//91
/*0x5c*/0XFF,//92
/*0x5d*/0XFF,//93
/*0x5e*/0XFF,//94
/*0x5f*/0XFF,//95
};


/*      
mode 1   2    3
 3D  8D  B6   5F 

4     5    6    7     
49  	 4A   04  05

8     9      0
00 	   06 	0A

repeat        mute  
9B          	80

       vol+
        85

prev    pp      next
87      82       88 

       vol-
       86
ch-            ch+
92              81

fr     ff     stop    eq
94    C1      8B      4C
*/

#if 0
const u8 IRTab1[] = 	  //7F80
{
/*0x00*/IRC_NUM8,//0
/*0x01*/0XFF,// 1
/*0x02*/0XFF,//02
/*0x03*/0XFF,//03
/*0x04*/IRC_NUM6,//04
/*0x05*/IRC_NUM7,//05
/*0x06*/IRC_NUM9,//06
/*0x07*/0XFF,//07
/*0x08*/0XFF,//08
/*0x09*/0XFF,//09
/*0x0a*/IRC_NUM0,//10
/*0x0b*/0XFF,//11
/*0x0c*/0XFF,//12
/*0x0d*/0XFF,//13
/*0x0e*/0XFF,//14
/*0x0f*/0XFF,//15
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
    /*0x20*/ 0XFF,//20
	/*0x21*/ 0XFF,//20
	/*0x22*/ 0XFF,//20
	/*0x23*/ 0XFF,//20
	/*0x24*/ 0XFF,//20
	/*0x25*/ 0XFF,//20
	/*0x26*/ 0XFF,//20
	/*0x27*/ 0XFF,//20
	/*0x28*/ 0XFF,//20
	/*0x29*/ 0XFF,//20
	/*0x2A*/ 0XFF,//20
	/*0x2B*/ 0XFF,//20
	/*0x2C*/ 0XFF,//20
	/*0x2D*/ 0XFF,//20
	/*0x2E*/ 0XFF,//20
	/*0x2F*/ 0XFF,//20

    /*0x30*/ 0XFF,//30
	/*0x31*/ 0XFF,//30
	/*0x32*/ 0XFF,//30
	/*0x33*/ 0XFF,//30
	/*0x34*/ 0XFF,//30
	/*0x35*/ 0XFF,//30
	/*0x36*/ 0XFF,//30
	/*0x37*/ 0XFF,//30
	/*0x38*/ 0XFF,//30
	/*0x39*/ 0XFF,//30
	/*0x3A*/ 0XFF,//30
	/*0x3B*/ 0XFF,//30
	/*0x3C*/ 0XFF,//30
	/*0x3D*/ IRC_MODE,//30
	/*0x3E*/ 0XFF,//30
	/*0x3F*/ 0XFF,//30

/*0x40*/ 0XFF,//64
/*0x41*/0XFF,// 65
/*0x42*/0XFF,//66
/*0x43*/0XFF,//67
/*0x44*/0XFF,//68
/*0x45*/0XFF,//69
/*0x46*/0XFF,//70
/*0x47*/0XFF,//71
/*0x48*/0XFF,//72
/*0x49*/IRC_NUM4,//73
/*0x4a*/IRC_NUM5,//74
/*0x4b*/0XFF,//75
/*0x4c*/IRC_EQ,//76
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
/*0x5f*/IRC_NUM3,//95

 /*0x80*/ IRC_MUTE,//80
 /*0x81*/ IRC_CH_UP,//20
 /*0x82*/ IRC_PLAY_PAUSE,//20
 /*0x83*/ 0XFF,//20
 /*0x84*/ 0XFF,//20
 /*0x85*/ IRC_VOL_UP,//20
 /*0x86*/ IRC_VOL_DN,//20
 /*0x87*/ IRC_PREV,//20
 /*0x88*/ IRC_NEXT,//20
 /*0x89*/ 0XFF,//20
 /*0x8A*/ 0XFF,//20
 /*0x8B*/ IRC_STOP,//20
 /*0x8C*/ 0XFF,//20
 /*0x8D*/ IRC_NUM1,//20
 /*0x8E*/ 0XFF,//20
 /*0x8F*/ 0XFF,//20

 /*0x90*/ 0XFF,//90
 /*0x91*/ 0XFF,//20
 /*0x92*/ IRC_CH_DN,//20
 /*0x93*/ 0XFF,//20
 /*0x94*/ IRC_FR,//20
 /*0x95*/ 0XFF,//20
 /*0x96*/ 0XFF,//20
 /*0x97*/ 0XFF,//20
 /*0x98*/ 0XFF,//20
 /*0x99*/ 0XFF,//20
 /*0x9A*/ 0XFF,//20
 /*0x9B*/ IRC_REPEAT,//20
 /*0x9C*/ 0XFF,//20
 /*0x9D*/ 0XFF,//20
 /*0x9E*/ 0XFF,//20
 /*0x9F*/ 0XFF,//20

 /*0xA0*/ 0XFF,//A0
 /*0xA1*/ 0XFF,//20
 /*0xA2*/ 0XFF,//20
 /*0xA3*/ 0XFF,//20
 /*0xA4*/ 0XFF,//20
 /*0xA5*/ 0XFF,//20
 /*0xA6*/ 0XFF,//20
 /*0xA7*/ 0XFF,//20
 /*0xA8*/ 0XFF,//20
 /*0xA9*/ 0XFF,//20
 /*0xAA*/ 0XFF,//20
 /*0xAB*/ 0XFF,//20
 /*0xAC*/ 0XFF,//20
 /*0xAD*/ 0XFF,//20
 /*0xAE*/ 0XFF,//20
 /*0xAF*/ 0XFF,//20

 /*0xB0*/ 0XFF,//B0
 /*0xB1*/ 0XFF,//20
 /*0xB2*/ 0XFF,//20
 /*0xB3*/ 0XFF,//20
 /*0xB4*/ 0XFF,//20
 /*0xB5*/ 0XFF,//20
 /*0xB6*/ IRC_NUM2,//20
 /*0xB7*/ 0XFF,//20
 /*0xB8*/ 0XFF,//20
 /*0xB9*/ 0XFF,//20
 /*0xBA*/ 0XFF,//20
 /*0xBB*/ 0XFF,//20
 /*0xBC*/ 0XFF,//20
 /*0xBD*/ 0XFF,//20
 /*0xBE*/ 0XFF,//20
 /*0xBF*/ 0XFF,//20

 /*0xC0*/ 0XFF,//C0
 /*0xC1*/ IRC_FF,//20
 /*0xC2*/ 0XFF,//20
 /*0xC3*/ 0XFF,//20
 /*0xC4*/ 0XFF,//20
 /*0xC5*/ 0XFF,//20
 /*0xC6*/ 0XFF,//20
 /*0xC7*/ 0XFF,//20
 /*0xC8*/ 0XFF,//20
 /*0xC9*/ 0XFF,//20
 /*0xCA*/ 0XFF,//20
 /*0xCB*/ 0XFF,//20
 /*0xCC*/ 0XFF,//20
 /*0xCD*/ 0XFF,//20
 /*0xCE*/ 0XFF,//20
 /*0xCF*/ 0XFF,//20

 };
 #endif
