

									

/*      
POWER  MODE   MUTE
 45      46       47

PP	PREV     NEXT
44      40  	43

EQ	   V-     	V+		   
07 	   15 	09

0	 REP    	u/sd
16       19  	0d

1        2		3
0c 	  18		 5e

4	  5		6
08	 1c 		5a

7	  8		9
42	 52 		4a

*/

/*******************************************************************
                        IR music   按键表
*******************************************************************/


#define IRFF00_DECODE_KEY_SHORT			\
										/*00*/    MSG_0,\
										/*01*/    MSG_1,\
										/*02*/    MSG_2,\
										/*03*/    MSG_3,\
										/*04*/    MSG_4,\
										/*05*/    MSG_5,\
										/*06*/    MSG_6,\
										/*07*/    MSG_7,\
										/*08*/    MSG_8,\
										/*09*/    MSG_9,\
										/*10*/    MSG_STANBY_KEY,\
										/*11*/    MSG_CHANGE_WORKMODE,\
										/*12*/    MSG_MUTE,\
										/*13*/    MSG_MUSIC_PP,\
										/*14*/    MSG_MUSIC_PREV_FILE,\
										/*15*/    MSG_MUSIC_NEXT_FILE,\
										/*16*/    MSG_VOL_UP,\
										/*17*/    MSG_VOL_DOWN,\
										/*18*/    MSG_MUSIC_EQ,\
										/*19*/    MSG_MUSIC_RPT,\
										/*20*/    MSG_MUSIC_U_SD,\
										/*21*/    MSG_MUSIC_PREV_FILE,\
										/*22*/    MSG_MUSIC_NEXT_FILE

#define IRFF00_DECODE_KEY_LONG			\
		                                         /*00*/    NO_MSG,\
                                                      /*01*/    NO_MSG,\
                                                      /*02*/    NO_MSG,\
                                                      /*03*/    NO_MSG,\
                                                      /*04*/    NO_MSG,\
                                                      /*05*/    NO_MSG,\
                                                      /*06*/    NO_MSG,\
                                                      /*07*/    NO_MSG,\
                                                      /*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
								/*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
								/*14*/    MSG_MUSIC_FR,\
								/*15*/    MSG_MUSIC_FF,\
								/*16*/    MSG_VOL_UP,\
								/*17*/    MSG_VOL_DOWN,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG
								
#define IRFF00_DECODE_KEY_HOLD			\
		                                         /*00*/    NO_MSG,\
                                                      /*01*/    NO_MSG,\
                                                      /*02*/    NO_MSG,\
                                                      /*03*/    NO_MSG,\
                                                      /*04*/    NO_MSG,\
                                                      /*05*/    NO_MSG,\
                                                      /*06*/    NO_MSG,\
                                                      /*07*/    NO_MSG,\
                                                      /*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
								/*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
								/*14*/    MSG_MUSIC_FR,\
								/*15*/    MSG_MUSIC_FF,\
								/*16*/    MSG_VOL_UP,\
								/*17*/    MSG_VOL_DOWN,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG

#define IRFF00_DECODE_KEY_LONG_UP 		\
		                                         /*00*/    NO_MSG,\
                                                      /*01*/    NO_MSG,\
                                                      /*02*/    NO_MSG,\
                                                      /*03*/    NO_MSG,\
                                                      /*04*/    NO_MSG,\
                                                      /*05*/    NO_MSG,\
                                                      /*06*/    NO_MSG,\
                                                      /*07*/    NO_MSG,\
                                                      /*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
								/*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
								/*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG

/*******************************************************************
                          FM   IR按键表
*******************************************************************/

#define IRFF00_FM_KEY_SHORT			\
							/*00*/    MSG_0,\
							/*01*/    MSG_1,\
							/*02*/    MSG_2,\
							/*03*/    MSG_3,\
							/*04*/    MSG_4,\
							/*05*/    MSG_5,\
							/*06*/    MSG_6,\
							/*07*/    MSG_7,\
							/*08*/    MSG_8,\
							/*09*/    MSG_9,\
							/*10*/    MSG_STANBY_KEY,\
							/*11*/    MSG_CHANGE_WORKMODE,\
							/*12*/    MSG_MUTE,\
							/*13*/    MSG_FM_PP,\
							/*14*/    MSG_FM_PREV_STATION,\
							/*15*/    MSG_FM_NEXT_STATION,\
							/*16*/    MSG_VOL_UP,\
							/*17*/    MSG_VOL_DOWN,\
							/*18*/    NO_MSG,\
							/*19*/    NO_MSG,\
							/*20*/    MSG_FM_SCAN_ALL_INIT,\
							/*21*/    MSG_FM_PREV_STATION,\
							/*22*/    MSG_FM_NEXT_STATION
							
#define IRFF00_FM_KEY_LONG			\
							/*00*/    NO_MSG,\
							/*01*/    NO_MSG,\
							/*02*/    NO_MSG,\
							/*03*/    NO_MSG,\
							/*04*/    NO_MSG,\
							/*05*/    NO_MSG,\
							/*06*/    NO_MSG,\
							/*07*/    NO_MSG,\
							/*08*/    NO_MSG,\
							/*09*/    NO_MSG,\
							/*10*/    NO_MSG,\
							/*11*/    NO_MSG,\
							/*12*/    NO_MSG,\
							/*13*/    MSG_FM_SCAN_ALL_INIT,\
							/*14*/    NO_MSG,\
							/*15*/    NO_MSG,\
							/*16*/    MSG_VOL_UP,\
							/*17*/    MSG_VOL_DOWN,\
							/*18*/    NO_MSG,\
							/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG
				
#define IRFF00_FM_KEY_HOLD			\
							/*00*/    NO_MSG,\
							/*01*/    NO_MSG,\
							/*02*/    NO_MSG,\
							/*03*/    NO_MSG,\
							/*04*/    NO_MSG,\
							/*05*/    NO_MSG,\
							/*06*/    NO_MSG,\
							/*07*/    NO_MSG,\
							/*08*/    NO_MSG,\
							/*09*/    NO_MSG,\
							/*10*/    NO_MSG,\
							/*11*/    NO_MSG,\
							/*12*/    NO_MSG,\
							/*13*/    NO_MSG,\
							/*14*/    NO_MSG,\
							/*15*/    NO_MSG,\
							/*16*/    MSG_VOL_UP,\
							/*17*/    MSG_VOL_DOWN,\
							/*18*/    NO_MSG,\
							/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG

#define IRFF00_FM_KEY_LONG_UP 		\
							/*00*/    NO_MSG,\
							/*01*/    NO_MSG,\
							/*02*/    NO_MSG,\
							/*03*/    NO_MSG,\
							/*04*/    NO_MSG,\
							/*05*/    NO_MSG,\
							/*06*/    NO_MSG,\
							/*07*/    NO_MSG,\
							/*08*/    NO_MSG,\
							/*09*/    NO_MSG,\
							/*10*/    NO_MSG,\
							/*11*/    NO_MSG,\
							/*12*/    NO_MSG,\
							/*13*/    NO_MSG,\
							/*14*/    NO_MSG,\
							/*15*/    NO_MSG,\
							/*16*/    NO_MSG,\
							/*17*/    NO_MSG,\
							/*18*/    NO_MSG,\
							/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG

/*******************************************************************
                     line        IR按键表
*******************************************************************/
#define IRFF00_AUX_KEY_SHORT			\
							/*00*/    NO_MSG,\
							/*01*/    NO_MSG,\
							/*02*/    NO_MSG,\
							/*03*/    NO_MSG,\
							/*04*/    NO_MSG,\
							/*05*/    NO_MSG,\
							/*06*/    NO_MSG,\
							/*07*/    NO_MSG,\
							/*08*/    NO_MSG,\
							/*09*/    NO_MSG,\
							/*10*/    MSG_STANBY_KEY,\
							/*11*/    MSG_CHANGE_WORKMODE,\
							/*12*/    MSG_MUTE,\
							/*13*/    MSG_AUX_MUTE,\
							/*14*/    NO_MSG,\
							/*15*/    NO_MSG,\
							/*16*/    MSG_VOL_UP,\
							/*17*/    MSG_VOL_DOWN,\
							/*18*/    NO_MSG,\
							/*19*/    NO_MSG,\
							/*20*/    NO_MSG,\
							/*21*/    NO_MSG,\
							/*22*/    NO_MSG

#define IRFF00_AUX_KEY_LONG			\
							/*00*/    NO_MSG,\
							/*01*/    NO_MSG,\
							/*02*/    NO_MSG,\
							/*03*/    NO_MSG,\
							/*04*/    NO_MSG,\
							/*05*/    NO_MSG,\
							/*06*/    NO_MSG,\
							/*07*/    NO_MSG,\
							/*08*/    NO_MSG,\
							/*09*/    NO_MSG,\
							/*10*/    NO_MSG,\
							/*11*/    NO_MSG,\
							/*12*/    NO_MSG,\
							/*13*/    NO_MSG,\
							/*14*/    NO_MSG,\
							/*15*/    NO_MSG,\
							/*16*/    MSG_VOL_UP,\
							/*17*/    MSG_VOL_DOWN,\
							/*18*/    NO_MSG,\
							/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG

#define IRFF00_AUX_KEY_HOLD			\
							/*00*/    NO_MSG,\
							/*01*/    NO_MSG,\
							/*02*/    NO_MSG,\
							/*03*/    NO_MSG,\
							/*04*/    NO_MSG,\
							/*05*/    NO_MSG,\
							/*06*/    NO_MSG,\
							/*07*/    NO_MSG,\
							/*08*/    NO_MSG,\
							/*09*/    NO_MSG,\
							/*10*/    NO_MSG,\
							/*11*/    NO_MSG,\
							/*12*/    NO_MSG,\
							/*13*/    NO_MSG,\
							/*14*/    NO_MSG,\
							/*15*/    NO_MSG,\
							/*16*/    MSG_VOL_UP,\
							/*17*/    MSG_VOL_DOWN,\
							/*18*/    NO_MSG,\
							/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG

#define IRFF00_AUX_KEY_LONG_UP 		\
							/*00*/    NO_MSG,\
							/*01*/    NO_MSG,\
							/*02*/    NO_MSG,\
							/*03*/    NO_MSG,\
							/*04*/    NO_MSG,\
							/*05*/    NO_MSG,\
							/*06*/    NO_MSG,\
							/*07*/    NO_MSG,\
							/*08*/    NO_MSG,\
							/*09*/    NO_MSG,\
							/*10*/    NO_MSG,\
							/*11*/    NO_MSG,\
							/*12*/    NO_MSG,\
							/*13*/    NO_MSG,\
							/*14*/    NO_MSG,\
							/*15*/    NO_MSG,\
							/*16*/    NO_MSG,\
							/*17*/    NO_MSG,\
							/*18*/    NO_MSG,\
							/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG

/*******************************************************************
                        IR BT   按键表
*******************************************************************/

#define IRFF00_BT_SHORT			\
		                                         /*00*/    NO_MSG,\
                                                      /*01*/    NO_MSG,\
                                                      /*02*/    NO_MSG,\
                                                      /*03*/    NO_MSG,\
                                                      /*04*/    NO_MSG,\
                                                      /*05*/    NO_MSG,\
                                                      /*06*/    NO_MSG,\
                                                      /*07*/    NO_MSG,\
                                                      /*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
								/*10*/    MSG_STANBY_KEY,\
								/*11*/    MSG_CHANGE_WORKMODE,\
								/*12*/    MSG_MUTE,\
								/*13*/    MSG_BT_PP,\
								/*14*/    MSG_BT_PREV_FILE,\
								/*15*/    MSG_BT_NEXT_FILE,\
								/*16*/    MSG_VOL_UP,\
								/*17*/    MSG_VOL_DOWN,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    MSG_BT_PREV_FILE,\
								/*22*/    MSG_BT_NEXT_FILE



			
#define IRFF00_BT_LONG			\
                                                      /*00*/    NO_MSG,\
                                                      /*01*/    NO_MSG,\
                                                      /*02*/    NO_MSG,\
                                                      /*03*/    NO_MSG,\
                                                      /*04*/    NO_MSG,\
                                                      /*05*/    NO_MSG,\
                                                      /*06*/    NO_MSG,\
                                                      /*07*/    NO_MSG,\
                                                      /*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
								/*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
								/*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    MSG_VOL_UP,\
								/*17*/    MSG_VOL_DOWN,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG

#define IRFF00_BT_HOLD			\
                                                      /*00*/    NO_MSG,\
                                                      /*01*/    NO_MSG,\
                                                      /*02*/    NO_MSG,\
                                                      /*03*/    NO_MSG,\
                                                      /*04*/    NO_MSG,\
                                                      /*05*/    NO_MSG,\
                                                      /*06*/    NO_MSG,\
                                                      /*07*/    NO_MSG,\
                                                      /*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
								/*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
								/*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    MSG_VOL_UP,\
								/*17*/    MSG_VOL_DOWN,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG


#define IRFF00_BT_LONG_UP 		\
                                                      /*00*/    NO_MSG,\
                                                      /*01*/    NO_MSG,\
                                                      /*02*/    NO_MSG,\
                                                      /*03*/    NO_MSG,\
                                                      /*04*/    NO_MSG,\
                                                      /*05*/    NO_MSG,\
                                                      /*06*/    NO_MSG,\
                                                      /*07*/    NO_MSG,\
                                                      /*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
								/*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
								/*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG

/*******************************************************************
                      usb      IR按键表
*******************************************************************/

#define IRFF00_USB_KEY_SHORT			\
										/*00*/    NO_MSG,\
										/*01*/    NO_MSG,\
										/*02*/    NO_MSG,\
										/*03*/    NO_MSG,\
										/*04*/    NO_MSG,\
										/*05*/    NO_MSG,\
										/*06*/    NO_MSG,\
										/*07*/    NO_MSG,\
										/*08*/    NO_MSG,\
										/*09*/    NO_MSG,\
										/*10*/    MSG_STANBY_KEY,\
										/*11*/    MSG_CHANGE_WORKMODE,\
										/*12*/    MSG_MUTE,\
										/*13*/    MSG_PC_PP,\
										/*14*/    MSG_PC_PLAY_PREV,\
										/*15*/    MSG_PC_PLAY_NEXT,\
										/*16*/    MSG_VOL_UP,\
										/*17*/    MSG_VOL_DOWN,\
										/*18*/    NO_MSG,\
										/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG

#define IRFF00_USB_KEY_LONG			\
                                                      /*00*/    NO_MSG,\
                                                      /*01*/    NO_MSG,\
                                                      /*02*/    NO_MSG,\
                                                      /*03*/    NO_MSG,\
                                                      /*04*/    NO_MSG,\
                                                      /*05*/    NO_MSG,\
                                                      /*06*/    NO_MSG,\
                                                      /*07*/    NO_MSG,\
                                                      /*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
								/*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
								/*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG

#define IRFF00_USB_KEY_HOLD			\
                                                      /*00*/    NO_MSG,\
                                                      /*01*/    NO_MSG,\
                                                      /*02*/    NO_MSG,\
                                                      /*03*/    NO_MSG,\
                                                      /*04*/    NO_MSG,\
                                                      /*05*/    NO_MSG,\
                                                      /*06*/    NO_MSG,\
                                                      /*07*/    NO_MSG,\
                                                      /*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
								/*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
								/*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG


#define IRFF00_USB_KEY_LONG_UP 		\
                                                      /*00*/    NO_MSG,\
                                                      /*01*/    NO_MSG,\
                                                      /*02*/    NO_MSG,\
                                                      /*03*/    NO_MSG,\
                                                      /*04*/    NO_MSG,\
                                                      /*05*/    NO_MSG,\
                                                      /*06*/    NO_MSG,\
                                                      /*07*/    NO_MSG,\
                                                      /*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
								/*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
								/*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG


/*******************************************************************
                     MAIN       IR按键表
*******************************************************************/
#define IRFF00_MAIN_KEY_SHORT			\
                                                      /*00*/    NO_MSG,\
                                                      /*01*/    NO_MSG,\
                                                      /*02*/    NO_MSG,\
                                                      /*03*/    NO_MSG,\
                                                      /*04*/    NO_MSG,\
                                                      /*05*/    NO_MSG,\
                                                      /*06*/    NO_MSG,\
                                                      /*07*/    NO_MSG,\
                                                      /*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
								/*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
								/*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG

#define IRFF00_MAIN_KEY_LONG			\
                                                      /*00*/    NO_MSG,\
                                                      /*01*/    NO_MSG,\
                                                      /*02*/    NO_MSG,\
                                                      /*03*/    NO_MSG,\
                                                      /*04*/    NO_MSG,\
                                                      /*05*/    NO_MSG,\
                                                      /*06*/    NO_MSG,\
                                                      /*07*/    NO_MSG,\
                                                      /*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
								/*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
								/*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG

#define IRFF00_MAIN_KEY_HOLD			\
                                                      /*00*/    NO_MSG,\
                                                      /*01*/    NO_MSG,\
                                                      /*02*/    NO_MSG,\
                                                      /*03*/    NO_MSG,\
                                                      /*04*/    NO_MSG,\
                                                      /*05*/    NO_MSG,\
                                                      /*06*/    NO_MSG,\
                                                      /*07*/    NO_MSG,\
                                                      /*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
								/*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
								/*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG

#define IRFF00_MAIN_KEY_LONG_UP 		\
                                                      /*00*/    NO_MSG,\
                                                      /*01*/    NO_MSG,\
                                                      /*02*/    NO_MSG,\
                                                      /*03*/    NO_MSG,\
                                                      /*04*/    NO_MSG,\
                                                      /*05*/    NO_MSG,\
                                                      /*06*/    NO_MSG,\
                                                      /*07*/    NO_MSG,\
                                                      /*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
								/*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
								/*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG


/*******************************************************************
                            IR按键表
*******************************************************************/
#define IRFF00_IDLE_KEY_SHORT			\
                                /*00*/    NO_MSG,\
							    /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    NO_MSG,\
								/*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
				                                /*10*/    MSG_STANBY_KEY,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
								/*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG

#define IRFF00_IDLE_KEY_LONG			\
								/*00*/    NO_MSG,\
                               					 /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    NO_MSG,\
								/*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
								/*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
								/*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG

#define IRFF00_IDLE_KEY_HOLD			\
								/*00*/    NO_MSG,\
                                                         /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    NO_MSG,\
								/*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
                                                         /*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
								/*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG


#define IRFF00_IDLE_KEY_LONG_UP 		\
								/*00*/    NO_MSG,\
                                                          /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    NO_MSG,\
								/*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
								/*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
                                                        /*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG
								
/*******************************************************************
                           REC  IR按键表
*******************************************************************/
#if REC_EN

#define IRFF00_ENC_KEY_SHORT			\
                                /*00*/    NO_MSG,\
							    /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    NO_MSG,\
								/*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
                                /*10*/    NO_MSG,\
								/*11*/    MSG_CHANGE_WORKMODE,\
								/*12*/    MSG_REC_STOP,\
								/*13*/    MSG_REC_START,\
								/*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG


#define IRFF00_ENC_KEY_LONG			\
								/*00*/    NO_MSG,\
                                /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    NO_MSG,\
								/*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
                                /*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
								/*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG

#define IRFF00_ENC_KEY_HOLD			\
								/*00*/    NO_MSG,\
                                /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    NO_MSG,\
								/*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
                                /*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
								/*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG


#define IRFF00_ENC_KEY_LONG_UP 		\
								/*00*/    NO_MSG,\
                                /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    NO_MSG,\
								/*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
								/*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
                                /*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG
#endif								
/*******************************************************************
                           RTC  IR按键表
*******************************************************************/
#if RTC_CLK_EN

#define IRFF00_RTC_KEY_SHORT			\
                                /*00*/    MSG_POWER_OFF,\
							    /*01*/    MSG_CHANGE_WORKMODE,\
								/*02*/    MSG_ALM_SW,\
								/*03*/    MSG_RTC_SETTING,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    MSG_ALM_SETTING,\
								/*07*/    MSG_RTC_MINUS,\
								/*08*/    MSG_RTC_PLUS,\
								/*09*/    NO_MSG,\
                                /*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
								/*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG


#define IRFF00_RTC_KEY_LONG			\
								/*00*/    NO_MSG,\
                                /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    MSG_VOL_DOWN,\
								/*08*/    MSG_VOL_UP,\
								/*09*/    NO_MSG,\
                                /*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
								/*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG

#define IRFF00_RTC_KEY_HOLD			\
								/*00*/    NO_MSG,\
                                /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    MSG_VOL_DOWN,\
								/*08*/    MSG_VOL_UP,\
								/*09*/    NO_MSG,\
                                /*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
								/*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG


#define IRFF00_RTC_KEY_LONG_UP 		\
								/*00*/    NO_MSG,\
                                /*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    NO_MSG,\
								/*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
								/*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,\
                                /*14*/    NO_MSG,\
								/*15*/    NO_MSG,\
								/*16*/    NO_MSG,\
								/*17*/    NO_MSG,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG
#endif
