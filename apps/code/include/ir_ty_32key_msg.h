

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
										/*18*/    MSG_MUSIC_U_SD,\
										/*19*/    MSG_MUSIC_EQ,\
										/*20*/    MSG_MUSIC_RPT,\
										/*21*/    NO_MSG,\
										/*22*/    NO_MSG,\
										/*23*/    NO_MSG,\
										/*24*/    MSG_ADD_100,\
										/*25*/    MSG_MUSIC_PREV_FILE,\
										/*26*/    MSG_MUSIC_NEXT_FILE,\
										/*27*/    MSG_MUSIC_STOP,\
										/*28*/    MSG_MUSIC_U_SD,\
										/*29*/    MSG_MUSIC_PP,\
										/*30*/    NO_MSG,\
										/*31*/    NO_MSG,\
										/*32*/    NO_MSG
								



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
								/*15*/    MSG_MUSIC_NEXT_FILE,\
								/*16*/    MSG_VOL_UP,\
								/*17*/    MSG_VOL_DOWN,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG,\
								/*23*/    NO_MSG,\
								/*24*/    NO_MSG,\
								/*25*/    MSG_MUSIC_FR,\
								/*26*/    MSG_MUSIC_FF,\
								/*27*/    NO_MSG,\
								/*28*/    NO_MSG,\
								/*29*/    NO_MSG,\
								/*30*/    NO_MSG,\
								/*31*/    NO_MSG,\
								/*32*/    NO_MSG	

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
								/*15*/    MSG_MUSIC_NEXT_FILE,\
								/*16*/    MSG_VOL_UP,\
								/*17*/    MSG_VOL_DOWN,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG,\
								/*23*/    NO_MSG,\
								/*24*/    NO_MSG,\
								/*25*/    MSG_MUSIC_FR,\
								/*26*/    MSG_MUSIC_FF,\
								/*27*/    NO_MSG,\
								/*28*/    NO_MSG,\
								/*29*/    NO_MSG,\
								/*30*/    NO_MSG,\
								/*31*/    NO_MSG,\
								/*32*/    NO_MSG	


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
								/*22*/    NO_MSG,\
								/*23*/    NO_MSG,\
								/*24*/    NO_MSG,\
								/*25*/    NO_MSG,\
								/*26*/    NO_MSG,\
								/*27*/    NO_MSG,\
								/*28*/    NO_MSG,\
								/*29*/    NO_MSG,\
								/*30*/    NO_MSG,\
								/*31*/    NO_MSG,\
								/*32*/    NO_MSG	






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
							/*13*/    MSG_FM_SCAN_ALL_INIT,\
							/*14*/    MSG_FM_PREV_STATION,\
							/*15*/    MSG_FM_NEXT_STATION,\
							/*16*/    MSG_VOL_UP,\
							/*17*/    MSG_VOL_DOWN,\
							/*18*/    NO_MSG,\
							/*19*/    NO_MSG,\
							/*20*/    NO_MSG,\
							/*21*/    MSG_FM_NEXT_STATION,\
							/*22*/    MSG_FM_PREV_STATION,\
							/*23*/    NO_MSG,\
							/*24*/    NO_MSG,\
							/*25*/    MSG_FM_PREV_STEP ,\
							/*26*/    MSG_FM_NEXT_STEP ,\
							/*27*/    NO_MSG,\
							/*28*/    MSG_FM_SCAN_ALL_INIT,\
							/*29*/    NO_MSG,\
							/*30*/    NO_MSG,\
							/*31*/    NO_MSG,\
							/*32*/    NO_MSG



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
							/*13*/    NO_MSG,\
							/*14*/    MSG_FM_SCAN_ALL_DOWN,\
							/*15*/    MSG_FM_SCAN_ALL_UP,\
							/*16*/    MSG_VOL_UP,\
							/*17*/    MSG_VOL_DOWN,\
							/*18*/    NO_MSG,\
							/*19*/    NO_MSG,\
							/*20*/    NO_MSG,\
							/*21*/    MSG_FM_SCAN_ALL_UP,\
							/*22*/    MSG_FM_SCAN_ALL_DOWN,\
							/*23*/    NO_MSG,\
							/*24*/    NO_MSG,\
							/*25*/    MSG_FM_PREV_STEP ,\
							/*26*/    MSG_FM_NEXT_STEP ,\
							/*27*/    NO_MSG,\
							/*28*/    NO_MSG,\
							/*29*/    NO_MSG,\
							/*30*/    NO_MSG,\
							/*31*/    NO_MSG,\
							/*32*/    NO_MSG

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
							/*22*/    NO_MSG,\
							/*23*/    NO_MSG,\
							/*24*/    NO_MSG,\
							/*25*/    MSG_FM_PREV_STEP ,\
							/*26*/    MSG_FM_NEXT_STEP ,\
							/*27*/    NO_MSG,\
							/*28*/    NO_MSG,\
							/*29*/    NO_MSG,\
							/*30*/    NO_MSG,\
							/*31*/    NO_MSG,\
							/*32*/    NO_MSG

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
							/*22*/    NO_MSG,\
							/*23*/    NO_MSG,\
							/*24*/    NO_MSG,\
							/*25*/    NO_MSG ,\
							/*26*/    NO_MSG ,\
							/*27*/    NO_MSG,\
							/*28*/    NO_MSG,\
							/*29*/    NO_MSG,\
							/*30*/    NO_MSG,\
							/*31*/    NO_MSG,\
							/*32*/    NO_MSG



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
							/*13*/    NO_MSG,\
							/*14*/    NO_MSG,\
							/*15*/    NO_MSG,\
							/*16*/    MSG_VOL_UP,\
							/*17*/    MSG_VOL_DOWN,\
							/*18*/    NO_MSG,\
							/*19*/    NO_MSG,\
							/*20*/    NO_MSG,\
							/*21*/    NO_MSG,\
							/*22*/    NO_MSG,\
							/*23*/    NO_MSG,\
							/*24*/    NO_MSG,\
							/*25*/    NO_MSG ,\
							/*26*/    NO_MSG ,\
							/*27*/    NO_MSG,\
							/*28*/    NO_MSG,\
							/*29*/    NO_MSG,\
							/*30*/    NO_MSG,\
							/*31*/    NO_MSG,\
							/*32*/    NO_MSG


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
							/*22*/    NO_MSG,\
							/*23*/    NO_MSG,\
							/*24*/    NO_MSG,\
							/*25*/    NO_MSG ,\
							/*26*/    NO_MSG ,\
							/*27*/    NO_MSG,\
							/*28*/    NO_MSG,\
							/*29*/    NO_MSG,\
							/*30*/    NO_MSG,\
							/*31*/    NO_MSG,\
							/*32*/    NO_MSG


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
							/*22*/    NO_MSG,\
							/*23*/    NO_MSG,\
							/*24*/    NO_MSG,\
							/*25*/    NO_MSG ,\
							/*26*/    NO_MSG ,\
							/*27*/    NO_MSG,\
							/*28*/    NO_MSG,\
							/*29*/    NO_MSG,\
							/*30*/    NO_MSG,\
							/*31*/    NO_MSG,\
							/*32*/    NO_MSG

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
							/*22*/    NO_MSG,\
							/*23*/    NO_MSG,\
							/*24*/    NO_MSG,\
							/*25*/    NO_MSG ,\
							/*26*/    NO_MSG ,\
							/*27*/    NO_MSG,\
							/*28*/    NO_MSG,\
							/*29*/    NO_MSG,\
							/*30*/    NO_MSG,\
							/*31*/    NO_MSG,\
							/*32*/    NO_MSG



/*******************************************************************
                        IR BT   按键表
*******************************************************************/



#define IRFF00_BT_SHORT			\
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
								/*13*/    MSG_BT_PP,\
								/*14*/    MSG_BT_PREV_FILE,\
								/*15*/    MSG_BT_NEXT_FILE,\
								/*16*/    MSG_VOL_UP,\
								/*17*/    MSG_VOL_DOWN,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG,\
								/*23*/    NO_MSG,\
								/*24*/    NO_MSG,\
								/*25*/    MSG_BT_PREV_FILE,\
								/*26*/    MSG_BT_NEXT_FILE,\
								/*27*/    NO_MSG,\
								/*28*/    NO_MSG,\
								/*29*/    MSG_BT_PP,\
								/*30*/    NO_MSG,\
								/*31*/    NO_MSG,\
								/*32*/    NO_MSG



			//		/*09*/    MSG_BT_HID_CTRL,\
                     //           /*10*/    MSG_BT_HID_DISCONN,\
			
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
								/*22*/    NO_MSG,\
								/*23*/    NO_MSG,\
								/*24*/    NO_MSG,\
								/*25*/    NO_MSG,\
								/*26*/    NO_MSG,\
								/*27*/    NO_MSG,\
								/*28*/    NO_MSG,\
								/*29*/    NO_MSG,\
								/*30*/    NO_MSG,\
								/*31*/    NO_MSG,\
								/*32*/    NO_MSG

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
								/*22*/    NO_MSG,\
								/*23*/    NO_MSG,\
								/*24*/    NO_MSG,\
								/*25*/    NO_MSG,\
								/*26*/    NO_MSG,\
								/*27*/    NO_MSG,\
								/*28*/    NO_MSG,\
								/*29*/    NO_MSG,\
								/*30*/    NO_MSG,\
								/*31*/    NO_MSG,\
								/*32*/    NO_MSG


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
								/*22*/    NO_MSG,\
								/*23*/    NO_MSG,\
								/*24*/    NO_MSG,\
								/*25*/    NO_MSG,\
								/*26*/    NO_MSG,\
								/*27*/    NO_MSG,\
								/*28*/    NO_MSG,\
								/*29*/    NO_MSG,\
								/*30*/    NO_MSG,\
								/*31*/    NO_MSG,\
								/*32*/    NO_MSG



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
										/*22*/    NO_MSG,\
										/*23*/    NO_MSG,\
										/*24*/    NO_MSG,\
										/*25*/    MSG_PC_PLAY_PREV,\
										/*26*/    MSG_PC_PLAY_NEXT,\
										/*27*/    NO_MSG,\
										/*28*/    NO_MSG,\
										/*29*/    MSG_PC_PP,\
										/*30*/    NO_MSG,\
										/*31*/    NO_MSG,\
										/*32*/    NO_MSG
										

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
								/*16*/    MSG_VOL_UP,\
								/*17*/    MSG_VOL_DOWN,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG,\
								/*23*/    NO_MSG,\
								/*24*/    NO_MSG,\
								/*25*/    NO_MSG,\
								/*26*/    NO_MSG,\
								/*27*/    NO_MSG,\
								/*28*/    NO_MSG,\
								/*29*/    NO_MSG,\
								/*30*/    NO_MSG,\
								/*31*/    NO_MSG,\
								/*32*/    NO_MSG

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
								/*16*/    MSG_VOL_UP,\
								/*17*/    MSG_VOL_DOWN,\
								/*18*/    NO_MSG,\
								/*19*/    NO_MSG,\
								/*20*/    NO_MSG,\
								/*21*/    NO_MSG,\
								/*22*/    NO_MSG,\
								/*23*/    NO_MSG,\
								/*24*/    NO_MSG,\
								/*25*/    NO_MSG,\
								/*26*/    NO_MSG,\
								/*27*/    NO_MSG,\
								/*28*/    NO_MSG,\
								/*29*/    NO_MSG,\
								/*30*/    NO_MSG,\
								/*31*/    NO_MSG,\
								/*32*/    NO_MSG


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
								/*22*/    NO_MSG,\
								/*23*/    NO_MSG,\
								/*24*/    NO_MSG,\
								/*25*/    NO_MSG,\
								/*26*/    NO_MSG,\
								/*27*/    NO_MSG,\
								/*28*/    NO_MSG,\
								/*29*/    NO_MSG,\
								/*30*/    NO_MSG,\
								/*31*/    NO_MSG,\
								/*32*/    NO_MSG


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
								/*22*/    NO_MSG,\
								/*23*/    NO_MSG,\
								/*24*/    NO_MSG,\
								/*25*/    NO_MSG,\
								/*26*/    NO_MSG,\
								/*27*/    NO_MSG,\
								/*28*/    NO_MSG,\
								/*29*/    NO_MSG,\
								/*30*/    NO_MSG,\
								/*31*/    NO_MSG,\
								/*32*/    NO_MSG



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
								/*22*/    NO_MSG,\
								/*23*/    NO_MSG,\
								/*24*/    NO_MSG,\
								/*25*/    NO_MSG,\
								/*26*/    NO_MSG,\
								/*27*/    NO_MSG,\
								/*28*/    NO_MSG,\
								/*29*/    NO_MSG,\
								/*30*/    NO_MSG,\
								/*31*/    NO_MSG,\
								/*32*/    NO_MSG


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
								/*22*/    NO_MSG,\
								/*23*/    NO_MSG,\
								/*24*/    NO_MSG,\
								/*25*/    NO_MSG,\
								/*26*/    NO_MSG,\
								/*27*/    NO_MSG,\
								/*28*/    NO_MSG,\
								/*29*/    NO_MSG,\
								/*30*/    NO_MSG,\
								/*31*/    NO_MSG,\
								/*32*/    NO_MSG


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
								/*22*/    NO_MSG,\
								/*23*/    NO_MSG,\
								/*24*/    NO_MSG,\
								/*25*/    NO_MSG,\
								/*26*/    NO_MSG,\
								/*27*/    NO_MSG,\
								/*28*/    NO_MSG,\
								/*29*/    NO_MSG,\
								/*30*/    NO_MSG,\
								/*31*/    NO_MSG,\
								/*32*/    NO_MSG



/*******************************************************************
                     IDE        IR按键表
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
							/*12*/    MSG_MUTE,\
							/*13*/    NO_MSG,\
							/*14*/    NO_MSG,\
							/*15*/    NO_MSG,\
							/*16*/    NO_MSG,\
							/*17*/    NO_MSG,\
							/*18*/    NO_MSG,\
							/*19*/    NO_MSG,\
							/*20*/    NO_MSG,\
							/*21*/    NO_MSG,\
							/*22*/    NO_MSG,\
							/*23*/    NO_MSG,\
							/*24*/    NO_MSG,\
							/*25*/    NO_MSG ,\
							/*26*/    NO_MSG ,\
							/*27*/    NO_MSG,\
							/*28*/    NO_MSG,\
							/*29*/    NO_MSG,\
							/*30*/    NO_MSG,\
							/*31*/    NO_MSG,\
							/*32*/    NO_MSG


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
							/*22*/    NO_MSG,\
							/*23*/    NO_MSG,\
							/*24*/    NO_MSG,\
							/*25*/    NO_MSG ,\
							/*26*/    NO_MSG ,\
							/*27*/    NO_MSG,\
							/*28*/    NO_MSG,\
							/*29*/    NO_MSG,\
							/*30*/    NO_MSG,\
							/*31*/    NO_MSG,\
							/*32*/    NO_MSG


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
							/*22*/    NO_MSG,\
							/*23*/    NO_MSG,\
							/*24*/    NO_MSG,\
							/*25*/    NO_MSG ,\
							/*26*/    NO_MSG ,\
							/*27*/    NO_MSG,\
							/*28*/    NO_MSG,\
							/*29*/    NO_MSG,\
							/*30*/    NO_MSG,\
							/*31*/    NO_MSG,\
							/*32*/    NO_MSG

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
							/*22*/    NO_MSG,\
							/*23*/    NO_MSG,\
							/*24*/    NO_MSG,\
							/*25*/    NO_MSG ,\
							/*26*/    NO_MSG ,\
							/*27*/    NO_MSG,\
							/*28*/    NO_MSG,\
							/*29*/    NO_MSG,\
							/*30*/    NO_MSG,\
							/*31*/    NO_MSG,\
							/*32*/    NO_MSG

