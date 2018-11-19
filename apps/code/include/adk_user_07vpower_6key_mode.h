




#define      PKEY_LIGHT                          2
#define      PKEY_MODE                              3
#define      PKEY_NEXT                             4
#define      PKEY_PREV                             5
#define      PKEY_PP                                 6
#define      PKEY_POWER_OFF                8

/*******************************************************************
                        MUSIC   AD按键表
*******************************************************************/

#define ADKEY_DECODE_SHORT		\
							/*00  220k */    NO_MSG,\
							/*01  100k*/    NO_MSG,\
							/*02   51k*/    MSG_LIGHT_KEY,\
							/*03   33k*/    MSG_CHANGE_WORKMODE,\
							/*04   24k*/    MSG_MUSIC_NEXT_FILE,\
							/*05   15k*/    MSG_MUSIC_PREV_FILE,\
							/*06  9k1*/    MSG_MUSIC_PP ,\
							/*07 6K2*/    NO_MSG,\
							/*08 3K1*/    NO_MSG,\
							/*09 0R */    NO_MSG,

#define ADKEY_DECODE_LONG		\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    MSG_VOL_UP,\
                        /*05*/    MSG_VOL_DOWN,\
                        /*06*/    NO_MSG,\
                        /*07*/    MSG_POWER_OFF,\
                        /*08*/    MSG_POWER_OFF,\
                        /*09*/    MSG_POWER_OFF,


#define ADKEY_DECODE_HOLD		\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    MSG_VOL_UP,\
                        /*05*/    MSG_VOL_DOWN,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,

#define ADKEY_DECODE_LONG_UP	\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,




/*******************************************************************
                        FM   AD按键表
*******************************************************************/

#define ADKEY_FM_SHORT		\
							/*00  220k */   NO_MSG,\
							/*01  100k*/    NO_MSG,\
							/*02   51k*/     MSG_LIGHT_KEY,\
							/*03   33k*/     MSG_CHANGE_WORKMODE,\
							/*04   24k*/     MSG_FM_NEXT_STATION,\
							/*05   15k*/     MSG_FM_PREV_STATION,\
							/*06  9k1*/      MSG_FM_SCAN_ALL_INIT ,\
							/*07 6K2*/       NO_MSG,\
							/*08 3K1*/       NO_MSG,\
							/*09 0R */        NO_MSG,

#define ADKEY_FM_LONG		\
                                              /*00*/    NO_MSG,\
                                              /*01*/    NO_MSG,\
                                              /*02*/    NO_MSG,\
                                              /*03*/    NO_MSG,\
                                              /*04*/    MSG_VOL_UP,\
                                              /*05*/    MSG_VOL_DOWN,\
                                              /*06*/    NO_MSG,\
                                              /*07*/    MSG_POWER_OFF,\
                                              /*08*/    MSG_POWER_OFF,\
                                              /*09*/    MSG_POWER_OFF

#define ADKEY_FM_HOLD		\
                                           /*00*/    NO_MSG,\
                                           /*01*/    NO_MSG,\
                                           /*02*/    NO_MSG,\
                                           /*03*/    NO_MSG,\
                                           /*04*/    MSG_VOL_UP,\
                                           /*05*/    MSG_VOL_DOWN,\
                                           /*06*/    NO_MSG,\
                                           /*07*/    NO_MSG,\
                                           /*08*/    NO_MSG,\
                                           /*09*/    NO_MSG

#define ADKEY_FM_LONG_UP	\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,
                        
/*******************************************************************
                         LINE    AD按键表
*******************************************************************/

#define ADKEY_AUX_SHORT		\
							/*00  220k */    NO_MSG,\
							/*01  100k*/    NO_MSG,\
							/*02   51k*/    MSG_LIGHT_KEY,\
							/*03   33k*/    MSG_CHANGE_WORKMODE,\
							/*04   24k*/    MSG_VOL_UP,\
							/*05   15k*/    MSG_VOL_DOWN,\
							/*06  9k1*/     MSG_AUX_MUTE ,\
							/*07 6K2*/     NO_MSG,\
							/*08 3K1*/     NO_MSG,\
							/*09 0R */     NO_MSG,



#define ADKEY_AUX_LONG		\
                                           /*00*/    NO_MSG,\
                                           /*01*/    NO_MSG,\
                                           /*02*/    NO_MSG,\
                                           /*03*/    NO_MSG,\
                                           /*04*/    MSG_VOL_UP,\
                                           /*05*/    MSG_VOL_DOWN,\
                                           /*06*/    NO_MSG,\
                                           /*07*/    MSG_POWER_OFF,\
                                           /*08*/    MSG_POWER_OFF,\
                                           /*09*/    MSG_POWER_OFF



#define ADKEY_AUX_HOLD		\
                                           /*00*/    NO_MSG,\
                                           /*01*/    NO_MSG,\
                                           /*02*/    NO_MSG,\
                                           /*03*/    NO_MSG,\
                                           /*04*/    MSG_VOL_UP,\
                                           /*05*/    MSG_VOL_DOWN,\
                                           /*06*/    NO_MSG,\
                                           /*07*/    NO_MSG,\
                                           /*08*/    NO_MSG,\
                                           /*09*/    NO_MSG

#define ADKEY_AUX_LONG_UP	\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,


/*******************************************************************
                         BT   AD按键表
*******************************************************************/


#define ADKEY_BT_SHORT		\
							/*00  220k */   NO_MSG,\
							/*01  100k*/    NO_MSG,\
							/*02   51k*/     MSG_LIGHT_KEY,\
							/*03   33k*/     MSG_CHANGE_WORKMODE,\
							/*04   24k*/     MSG_BT_NEXT_FILE,\
							/*05   15k*/     MSG_BT_PREV_FILE,\
							/*06  9k1*/      MSG_BT_PP ,\
							/*07 6K2*/       NO_MSG,\
							/*08 3K1*/       NO_MSG,\
							/*09 0R */        NO_MSG,


#define ADKEY_BT_LONG		\
	                                     /*00*/    NO_MSG,\
                                           /*01*/    NO_MSG,\
                                           /*02*/    NO_MSG,\
                                           /*03*/    NO_MSG,\
                                           /*04*/    MSG_VOL_UP,\
                                           /*05*/    MSG_VOL_DOWN,\
                                           /*06*/    MSG_BT_CALL_REJECT,\
                                           /*07*/    MSG_POWER_OFF,\
                                           /*08*/    MSG_POWER_OFF,\
                                           /*09*/    MSG_POWER_OFF



#define ADKEY_BT_HOLD		\
                                           /*00*/    NO_MSG,\
                                           /*01*/    NO_MSG,\
                                           /*02*/    NO_MSG,\
                                           /*03*/    NO_MSG,\
                                           /*04*/    MSG_VOL_UP,\
                                           /*05*/    MSG_VOL_DOWN,\
                                           /*06*/    NO_MSG,\
                                           /*07*/    NO_MSG,\
                                           /*08*/    NO_MSG,\
                                           /*09*/    NO_MSG

#define ADKEY_BT_LONG_UP	\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,


/*******************************************************************
                         USB   AD按键表
*******************************************************************/
#define ADKEY_USB_SHORT		\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    MSG_CHANGE_WORKMODE,\
                        /*04*/    MSG_PC_PLAY_NEXT,\
                        /*05*/    MSG_PC_PLAY_PREV,\
                        /*06*/    MSG_PC_PP,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG ,

#define ADKEY_USB_LONG		\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    MSG_PC_VOL_UP,\
                        /*05*/    MSG_PC_VOL_DOWN,\
                        /*06*/    NO_MSG,\
                        /*07*/    MSG_POWER_OFF,\
                        /*08*/    MSG_POWER_OFF,\
                        /*09*/    MSG_POWER_OFF,


#define ADKEY_USB_HOLD		\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    MSG_PC_VOL_UP,\
                        /*05*/    MSG_PC_VOL_DOWN,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,

#define ADKEY_USB_LONG_UP	\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,

/*******************************************************************
                            main 按键表
*******************************************************************/
#define ADKEY_MAIN_SHORT		\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,

#define ADKEY_MAIN_LONG		\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    MSG_POWER_OFF,\
                        /*08*/    MSG_POWER_OFF,\
                        /*09*/    MSG_POWER_OFF,


#define ADKEY_MAIN_HOLD		\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,

#define ADKEY_MAIN_LONG_UP	\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,

/*******************************************************************
                            AD按键表
*******************************************************************/
#define ADKEY_IDLE_SHORT		\
                        /*00*/    MSG_IDLE_CTL,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,

#define ADKEY_IDLE_LONG		\
                        /*00*/    MSG_CHANGE_WORKMODE,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,


#define ADKEY_IDLE_HOLD		\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,

#define ADKEY_IDLE_LONG_UP	\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    NO_MSG,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    NO_MSG,\
                        /*07*/    NO_MSG,\
                        /*08*/    NO_MSG,\
                        /*09*/    NO_MSG,

