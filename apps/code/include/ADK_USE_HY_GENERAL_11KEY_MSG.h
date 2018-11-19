
/*******************************************************************
                        MUSIC   AD按键表
*******************************************************************/
#if defined(ZX_HL601_QGN_K1764_AC4601)||defined(ZX_HL601_QGN2_K1764_AC4601)||defined(ZX_HL601_QGN_2314_AC4601)
#if REC_EN
#define ADKEY_DECODE_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_MUSIC_RPT,\
	/*02*/	  MSG_MUSIC_EQ,\
	/*03*/	  MSG_CHANGE_WORKMODE,\
	/*04*/	  MSG_MUSIC_STOP,\
	/*05*/	  MSG_MENU_MODE,\
	/*06*/	  MSG_MUSIC_NEXT_FILE,\
	/*07*/	  MSG_MUSIC_PREV_FILE,\	
	/*08*/	  MSG_ADD_10,\
	/*09*/	  MSG_ONE_KEY_START_REC,\
	/*0A*/	  MSG_MUSIC_PP
#else
#define ADKEY_DECODE_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_MUSIC_RPT,\
	/*02*/	  MSG_MUSIC_EQ,\
	/*03*/	  MSG_CHANGE_WORKMODE,\
	/*04*/	  MSG_MUSIC_STOP,\
	/*05*/	  MSG_MENU_MODE,\
	/*06*/	  MSG_MUSIC_NEXT_FILE,\
	/*07*/	  MSG_MUSIC_PREV_FILE,\	
	/*08*/	  MSG_ADD_10,\
	/*09*/	  NO_MSG,\
	/*0A*/	  MSG_MUSIC_PP
#endif	
#elif defined(KOK_DETECT_USE_KEY)
#define ADKEY_DECODE_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_MUSIC_RPT,\
	/*02*/	  MSG_MUSIC_EQ,\
	/*03*/	  MSG_CHANGE_WORKMODE,\
	/*04*/	  MSG_MUSIC_STOP,\
	/*05*/	  MSG_MIC_PRIORITY,\
	/*06*/	  MSG_MUSIC_NEXT_FILE,\
	/*07*/	  MSG_MUSIC_PREV_FILE,\	
	/*08*/	  MSG_ADD_10,\
	/*09*/	  NO_MSG,\
	/*0A*/	  MSG_MUSIC_PP
#else
#define ADKEY_DECODE_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  MSG_MUSIC_RPT,\
	/*02*/	  MSG_MUSIC_EQ,\
	/*03*/	  MSG_CHANGE_WORKMODE,\
	/*04*/	  MSG_MUSIC_STOP,\
	/*05*/	  MSG_MUTE,\
	/*06*/	  MSG_MUSIC_NEXT_FILE,\
	/*07*/	  MSG_MUSIC_PREV_FILE,\	
	/*08*/	  MSG_ADD_10,\
	/*09*/	  NO_MSG,\
	/*0A*/	  MSG_MUSIC_PP
#endif
#define ADKEY_DECODE_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_VOICE_ONOFF,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  MSG_VOL_DOWN,\ 
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG

#define ADKEY_DECODE_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  MSG_VOL_DOWN,\ 
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG

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
	/*0A*/	  NO_MSG


/*******************************************************************
                        FM   AD按键表
*******************************************************************/
#if defined(ZX_HL601_QGN_K1764_AC4601)||defined(ZX_HL601_QGN2_K1764_AC4601)||defined(ZX_HL601_QGN_2314_AC4601)
#if REC_EN
#define ADKEY_FM_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_CHANGE_WORKMODE,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  MSG_FM_NEXT_STATION,\
	/*07*/	  MSG_FM_PREV_STATION,\ 
	/*08*/	  MSG_ADD_10,\
	/*09*/	  MSG_REC_START,\
	/*0A*/	  MSG_FM_PP
#else
#define ADKEY_FM_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_CHANGE_WORKMODE,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_MENU_MODE,\
	/*06*/	  MSG_FM_NEXT_STATION,\
	/*07*/	  MSG_FM_PREV_STATION,\ 
	/*08*/	  MSG_ADD_10,\
	/*09*/	  NO_MSG,\
	/*0A*/	  MSG_FM_PP
#endif	
#elif defined(KOK_DETECT_USE_KEY)
#define ADKEY_FM_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_CHANGE_WORKMODE,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_MIC_PRIORITY,\
	/*06*/	  MSG_FM_NEXT_STATION,\
	/*07*/	  MSG_FM_PREV_STATION,\ 
	/*08*/	  MSG_ADD_10,\
	/*09*/	  NO_MSG,\
	/*0A*/	  MSG_FM_PP
#else
#define ADKEY_FM_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_CHANGE_WORKMODE,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_MUTE,\
	/*06*/	  MSG_FM_NEXT_STATION,\
	/*07*/	  MSG_FM_PREV_STATION,\ 
	/*08*/	  MSG_ADD_10,\
	/*09*/	  NO_MSG,\
	/*0A*/	  MSG_FM_PP
#endif
#define ADKEY_FM_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  MSG_VOL_DOWN,\ 
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  MSG_FM_SCAN_ALL_INIT

#define ADKEY_FM_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  MSG_VOL_DOWN,\ 
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG

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
	/*0A*/	  NO_MSG
                        
/*******************************************************************
                         LINE    AD按键表
*******************************************************************/
#if defined(ZX_HL601_QGN_K1764_AC4601)||defined(ZX_HL601_QGN2_K1764_AC4601)||defined(ZX_HL601_QGN_2314_AC4601)
#if REC_EN
#define ADKEY_AUX_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_CHANGE_WORKMODE,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_MENU_MODE,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\ 
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_REC_START,\
	/*0A*/	  MSG_AUX_PAUSE
#else
#define ADKEY_AUX_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_CHANGE_WORKMODE,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_MENU_MODE,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\ 
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  MSG_AUX_PAUSE
#endif	
#elif defined(KOK_DETECT_USE_KEY)
#define ADKEY_AUX_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_CHANGE_WORKMODE,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_MIC_PRIORITY,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\ 
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  MSG_AUX_PAUSE
#else
#define ADKEY_AUX_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_CHANGE_WORKMODE,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_MUTE,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\ 
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  MSG_AUX_PAUSE
#endif
#define ADKEY_AUX_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  MSG_VOL_DOWN,\ 
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG

#define ADKEY_AUX_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  MSG_VOL_DOWN,\ 
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG

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
	/*0A*/	  NO_MSG

/*******************************************************************
                         BT   AD按键表
*******************************************************************/

#if defined(ZX_HL601_QGN_K1764_AC4601)||defined(ZX_HL601_QGN2_K1764_AC4601)||defined(ZX_HL601_QGN_2314_AC4601)
#if REC_EN
#define ADKEY_BT_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  MSG_BT_MUSIC_EQ,\
	/*03*/	  MSG_CHANGE_WORKMODE,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_MENU_MODE,\
	/*06*/	  MSG_BT_NEXT_FILE,\
	/*07*/	  MSG_BT_PREV_FILE,\	
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_REC_START,\
	/*0A*/	  MSG_BT_PP
#else
#define ADKEY_BT_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  MSG_BT_MUSIC_EQ,\
	/*03*/	  MSG_CHANGE_WORKMODE,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_MENU_MODE,\
	/*06*/	  MSG_BT_NEXT_FILE,\
	/*07*/	  MSG_BT_PREV_FILE,\	
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_REC_START,\
	/*0A*/	  MSG_BT_PP
#endif
#elif defined(KOK_DETECT_USE_KEY)
#define ADKEY_BT_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  MSG_BT_MUSIC_EQ,\
	/*03*/	  MSG_CHANGE_WORKMODE,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_MIC_PRIORITY,\
	/*06*/	  MSG_BT_NEXT_FILE,\
	/*07*/	  MSG_BT_PREV_FILE,\	
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  MSG_BT_PP
#else
#define ADKEY_BT_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  MSG_BT_MUSIC_EQ,\
	/*03*/	  MSG_CHANGE_WORKMODE,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_MUTE,\
	/*06*/	  MSG_BT_NEXT_FILE,\
	/*07*/	  MSG_BT_PREV_FILE,\	
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  MSG_BT_PP
#endif	
#define ADKEY_BT_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  MSG_VOL_DOWN,\ 
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG

#define ADKEY_BT_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  MSG_VOL_DOWN,\ 
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG
	
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
	/*0A*/	  NO_MSG

/*******************************************************************
                         USB   AD按键表
*******************************************************************/
#if defined(ZX_HL601_QGN_K1764_AC4601)||defined(ZX_HL601_QGN2_K1764_AC4601)||defined(ZX_HL601_QGN_2314_AC4601)
#define ADKEY_USB_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  MSG_BT_MUSIC_EQ,\
	/*03*/	  MSG_CHANGE_WORKMODE,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_MENU_MODE,\
	/*06*/	  MSG_PC_PLAY_NEXT,\
	/*07*/	  MSG_PC_PLAY_PREV,\	
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  MSG_PC_PP
#else
#define ADKEY_USB_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  MSG_BT_MUSIC_EQ,\
	/*03*/	  MSG_CHANGE_WORKMODE,\
	/*04*/	  NO_MSG,\
	/*05*/	  MSG_MUTE,\
	/*06*/	  MSG_PC_PLAY_NEXT,\
	/*07*/	  MSG_PC_PLAY_PREV,\	
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  MSG_PC_PP
#endif
#define ADKEY_USB_LONG		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  MSG_VOL_DOWN,\ 
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG


#define ADKEY_USB_HOLD		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  MSG_VOL_DOWN,\ 
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG

#define ADKEY_USB_LONG_UP	\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  NO_MSG,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  MSG_VOL_UP,\
	/*07*/	  MSG_VOL_DOWN,\ 
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG

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
	/*0A*/	  NO_MSG

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
	/*0A*/	  NO_MSG

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
	/*0A*/	  NO_MSG

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
	/*0A*/	  NO_MSG

// REC KEY  
#if REC_EN
#define ADKEY_ENC_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_CHANGE_WORKMODE,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\	
	/*08*/	  NO_MSG,\
	/*09*/	  MSG_ONE_KEY_TO_MP3,\
	/*0A*/	  MSG_REC_PP

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
	/*0A*/	  NO_MSG


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
	/*0A*/	  NO_MSG

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
	/*0A*/	  NO_MSG
#endif

//rtc key
#if RTC_CLK_EN
#define ADKEY_RTC_SHORT		\
                        /*00*/    NO_MSG,\
                        /*01*/    NO_MSG,\
                        /*02*/    MSG_STANBY_KEY,\
                        /*03*/    NO_MSG,\
                        /*04*/    NO_MSG,\
                        /*05*/    NO_MSG,\
                        /*06*/    MSG_CHANGE_WORKMODE,\
                        /*07*/    MSG_RTC_PLUS,\
                        /*08*/    MSG_RTC_MINUS,\
                        /*09 MSG_AUX_MUTE*/MSG_RTC_SETTING,

#define ADKEY_RTC_LONG		\
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


#define ADKEY_RTC_HOLD		\
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

#define ADKEY_RTC_LONG_UP	\
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
#endif

/*******************************************************************
                            AD按键表
*******************************************************************/
#define ADKEY_IDLE_SHORT		\
	/*00*/	  NO_MSG,\
	/*01*/	  NO_MSG,\
	/*02*/	  NO_MSG,\
	/*03*/	  MSG_STANBY_KEY,\
	/*04*/	  NO_MSG,\
	/*05*/	  NO_MSG,\
	/*06*/	  NO_MSG,\
	/*07*/	  NO_MSG,\ 
	/*08*/	  NO_MSG,\
	/*09*/	  NO_MSG,\
	/*0A*/	  NO_MSG

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
	/*0A*/	  NO_MSG

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
	/*0A*/	  NO_MSG

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
	/*0A*/	  NO_MSG
                        
