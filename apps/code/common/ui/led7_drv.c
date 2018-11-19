/*--------------------------------------------------------------------------*/
/**@file    LED.c
   @brief   LED Ã„Â£Â¿Ã©Ã‡Ã½Â¶Â¯Â½Ã“Â¿ÃšÂºÂ¯ÃŠÃ½
   @details
   @author  bingquan Cai
   @date    2012-8-30
   @note    AC319N
*/
/*----------------------------------------------------------------------------*/
#include "ui_api.h"

#if UI_ENABLE

#include "ui_common.h"
#include "led7_drv.h"
#include "fm_radio.h"
#include "decoder_phy.h"
#include "music.h"
#include "timer.h"
#include "key.h"
#include "file_op.h"
//#include "play_file.h"
#include "dac.h"
#include "msg.h"
#include "led.h"
#include "irtc.h"
#include "rtc_setting.h"
#if REC_EN
#include "encode.h"
#endif

#ifdef LED_SHOW_DEVICE_PLUGIN
#include "device_driver.h"
#include "drv_manage.h"
#endif
#ifdef SUPPORT_M62429
#include "M62429.h"
#endif
#ifdef SUPPORT_PT2313
#include "pt2313.h"
#endif
#ifdef KOK_DETECT_USE_KEY
#include "kok_detect.h"
#endif

#if 1//def 
#include "key_drv_ad.h"
#endif
LED7_VAR led7_var;
#ifdef SUPPORT_MUTE_FLASH
bool b_muteFlag=FALSE;
#endif
#ifdef support_line_pause
bool   aux_pause_mark;
#endif 
#ifdef USE_KEY_TO_CONTROL_HT1628_LIGHTS_ONOFF
 bool ifRunTimer=TRUE;
#endif
#ifdef support_led_off_key
 extern bool  led_on_flag;    // 0 Â¹Ã˜ 1 Â¿Âª
#endif 

#if LED_SHOW_VOL_MAX
extern u8 bVolMaxChangeToSmallVolMax;
#endif
#ifdef SUPPORT_AUX_FM_BT_SHOW_REC_TIME
extern u32 dwAuxFmBtRecordTimeCnt;
#endif
#ifdef LED_ONOFF_CONTROL_WITH_KEY
extern u8 bRgbMode;
#endif

#ifdef SUPPORT_IR_INPUT_2_3NUMS
extern bool bir_2_nums;
extern bool bir_3_nums;
#endif
#ifdef EQ_ADC_VALUE_DETECT
#include "key_drv_ad.h"
extern u16 adc_value[MAX_AD_CHANNEL];
#endif
#if defined(support_bt_waiting_conn_filsh_led) 
#include "spp_profile.h"
 u8 bt_line_mode;
#endif 
#ifdef support_menu_mode
u8 menumode;
#endif
#ifdef TEST_PANEL_LED
u8 bledComValue=0;
u8 bledGridValue=0;
#endif
#ifdef led_icon_disp_vat_volage
#ifdef support_battery_mode_check
 extern u8  ldo_power_mod;  
/*
   1;	    //Ã‚Ãº
   2;     //  Â¸ÃŸ
   3;    //Â°Ã«
   4;   //ÂµÃ
   5;   //ÂµÃÂµÃ
   6;    //ÂµÃÂ¹Ã˜Â»Ãº
   */
#endif 
#endif 


#ifdef support_user_dsp_eq
   #if defined(support_yl_3520) 
    #include "yl_3520_led_eq.c"
   #endif 
#endif 

const  u8 LED_NUMBER[10] =
{
    /*0*/
    (u8)(LED_A | LED_B | LED_C | LED_D | LED_E | LED_F),
    /*1*/
    (u8)(LED_B | LED_C),
    /*2*/
    (u8)(LED_A | LED_B | LED_D | LED_E | LED_G),
    /*3*/
    (u8)(LED_A | LED_B | LED_C | LED_D | LED_G),
    /*4*/
    (u8)(LED_B | LED_C | LED_F | LED_G),
    /*5*/
    (u8)(LED_A | LED_C | LED_D | LED_F | LED_G),
    /*6*/
    (u8)(LED_A | LED_C | LED_D | LED_E | LED_F | LED_G),
    /*7*/
    (u8)(LED_A | LED_B | LED_C),
    /*8*/
    (u8)(LED_A | LED_B | LED_C | LED_D | LED_E | LED_F | LED_G),
    /*9*/
    (u8)(LED_A | LED_B | LED_C | LED_D | LED_F | LED_G),
};

const  u8 LED_LARGE_LETTER[26] =
{
    0x77,0x7c,0x39,0x5e,0x79,///<ABCDE
    0x71,0x40,0x76,0x06,0x0E,///<FGHIJ
    0x40,0x38,0x40,0x37,0x3f,///<KLMNO
    0x73,0x40,0x50,0x6d,0x78,///<PQRST
    0x3e,0x3e,0x40,0x76,0x40,///<UVWXY
    0x5B///<Z
};

const  u8 LED_SMALL_LETTER[26] =
{
    0x77,0x7c,0x58,0x5e,0x79,///<abcde
    0x71,0x40,0x40,0x30,0x0E,///<fghij
    0x40,0x38,0x40,0x54,0x5c,///<klmno
    0x73,0x67,0x50,0x40,0x78,///<pqrst
    0x3e,0x3e,0x40,0x40,0x40,///<uvwxy
    0x40///<z
};
#ifdef LED_ID_KF8845AB
/*BT	USB   8 8:8.8   BAT01 BAT02 BAT03 */
/*SD REC		       REPLAY*/
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ ///7PIN LED
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0002,0x0004,0x0301,0x0401,0x0008,0x0101,0x0201},
/*num1*/ 	{0x0104,0x0108,0x0402,0x0120,0x0110,0x0202,0x0302},
/*num2*/ 	{0x0408,0x0210,0x0310,0x501,0x0504,0x0304,0x0404},
/*num3*/ 	{0x0620,0x0540,0x0420,0x0508,0x0320,0x0510,0x0440},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
  //LED_BT,    LED_USB,   LED_SD,  LED_REC, LED_2POINT, LED_DOT,LED_REPLAY,LED_BAT01,LED_BAT02,LED_BAT03
     0X0601, 0X0502,  0X0010, 0X0602,  0X0208,  0X0610,  0X0608,   0X0040,  0x0140, 0x0340
};

#elif defined LED_ID_27N60_8

/*
	tf	   fm
|||| 88:8.8 ||||
	usb	  aux
*/

	  
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0002,0x0004,0x0301,0x0401,0x0008,0x0101,0x0201},
/*num1*/ 	{0x0104,0x0108,0x0402,0x0120,0x0110,0x0202,0x0302},
/*num2*/ 	{0x0408,0x0210,0x0310,0x501,0x0504,0x0304,0x0404},
/*num3*/ 	{0x0608,0x0340,0x0040,0x0508,0x0320,0x0601,0x0140},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_SD,LED_USB,LED_FM,LED_AUX,LED_2POINT,LED_DOT
	0X0020, 0X0502,0X0240,0X0604,0X0208, 0X0602
};
const u16 led_EQ[LED_EQ_NUMS]={ 
    0x0420,0x0510,0x0010,0x0220,0x0440,0x0610,0x0620,0x0540
};

#elif defined(LED_ID_8848)
/*PLAY	USB  8 8:8.8 FM */
/*PAUSE   SD		   MP3*/
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ ///7PIN LED
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0002,0x0004,0x0301,0x0401,0x0008,0x0101,0x0201},
/*num1*/ 	{0x0104,0x0108,0x0402,0x0120,0x0110,0x0202,0x0302},
/*num2*/ 	{0x0408,0x0210,0x0310,0x501,0x0504,0x0304,0x0404},
/*num3*/ 	{0x0620,0x0540,0x0420,0x0508,0x0320,0x0510,0x0440},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
   //LED_PLAY,LED_PAUSE,LED_USB,  LED_SD, LED_FM,  LED_MP3,LED_DOT,LED_2POINT
     0X0020, 0X0220,  0X0502,0X0010,0X0604, 0X0240,0X0610,0X0208,
//	 0X0020, 0X0220,	0X0502,0X0010,0X0604, 0X0240,0X0612,0X0208, //led 8426 ¶àÁËLED_MHZ 0x0602
};
#elif defined(LCD_ID_ZSLCD)
/*
	sd		   (fm radio |||
	usb	88:8.8  mzhe) --same fm_dot
	folder mute rec bt
*/
const  u16 led_nums[LED_8NUMS][LED_8GRIDS] ={ ///< ÃÃ‚7Â¶ÃÃŠÃ½Ã‚Ã«Â¹ÃœÃ—ÂªÂ»Â»Â±Ã­
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0301,0x0302,0x0304,0x0308,0x0310,0x0320,0x0340},
/*num1*/ 	{0x0201,0x0202,0x0204,0x0208,0x0210,0x0220,0x0240},
/*num2*/ 	{0x0101,0x0102,0x0104,0x0108,0x0110,0x0120,0x0140},
/*num3*/ 	{0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040},
};

#elif defined(LED_ID_JW_24017_1B)

/*PLAY	USB  8 8:8.8 BAT_H */
/*PAUSE   SD		   BAT_L*/
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ ///7PIN LED
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0002,0x0004,0x0301,0x0401,0x0008,0x0101,0x0201},
/*num1*/ 	{0x0104,0x0108,0x0402,0x0120,0x0110,0x0202,0x0302},
/*num2*/ 	{0x0408,0x0210,0x0310,0x501,0x0504,0x0304,0x0404},
/*num3*/ 	{0x0620,0x0540,0x0420,0x0508,0x0320,0x0510,0x0440},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
   //LED_PLAY,LED_PAUSE,LED_USB,  LED_SD, LED_BAT_FULL,  LED_BAT_HALF,LED_DOT,LED_2POINT
     0X0020, 0X0220,  0X0502,0X0010,0X0604, 0X0240,0X0610,0X0208,
//	 0X0020, 0X0220,	0X0502,0X0010,0X0604, 0X0240,0X0612,0X0208, //led 8426 ¶àÁËLED_MHZ 0x0602
};

#elif defined(LED_ID_8848_BAT)
/*PLAY	USB  8 8:8.8 BAT_H */
/*PAUSE   SD		   BAT_L*/
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ ///7PIN LED
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0002,0x0004,0x0301,0x0401,0x0008,0x0101,0x0201},
/*num1*/ 	{0x0104,0x0108,0x0402,0x0120,0x0110,0x0202,0x0302},
/*num2*/ 	{0x0408,0x0210,0x0310,0x501,0x0504,0x0304,0x0404},
/*num3*/ 	{0x0620,0x0540,0x0420,0x0508,0x0320,0x0510,0x0440},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
   //LED_PLAY,LED_PAUSE,LED_USB,  LED_SD, LED_BAT_FULL,  LED_BAT_HALF,LED_DOT,LED_2POINT
     0X0020, 0X0220,  0X0502,0X0010,0X0604, 0X0240,0X0610,0X0208,
//	 0X0020, 0X0220,	0X0502,0X0010,0X0604, 0X0240,0X0612,0X0208, //led 8426 ¶àÁËLED_MHZ 0x0602
};
#elif defined(LED_ID_TY_8848)
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */	  
/*num0*/ 	{0x0101,0x0201,0x0301,0x0401,0x0501,0x0601,0x0202},
/*num1*/	{0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0104},
/*num2*/ 	{0x0304,0x0404,0x0504,0x0604,0x0408,0x0508,0x0608},
/*num3*/	{0x0208,0x0210,0x0220,0x0240,0x0310,0x0320,0x0340},
};
const u16 led_icon_value[LED_ICON_NUMS]={
	//ICON_PLAY,ICON_PAUSE,ICON_USB,ICON_SD,ICON_FM,ICON_MP3,ICON_MINSEC_DEVIATE,ICON_DECIMAL
	   0X0302, 0X0110,	0X0120,0X0140,0X0502, 0X0602,0X0108
};
#elif defined(LED_ID_XTX2401_KB)
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */	  
/*num0*/ 	{0x0101,0x0201,0x0301,0x0401,0x0501,0x0601,0x0202},
/*num1*/	{0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0104},
/*num2*/ 	{0x0304,0x0404,0x0504,0x0604,0x0408,0x0508,0x0608},
/*num3*/	{0x0208,0x0210,0x0220,0x0240,0x0310,0x0320,0x0340},
};
const u16 led_icon_value[LED_ICON_NUMS]={
	//ICON_PLAY,ICON_PAUSE,ICON_USB,ICON_SD,ICON_FM,ICON_MP3,ICON_MINSEC_DEVIATE
	   0X0302, 0X0402,	0X0502,0X0602,0X0120, 0X0140,0X0108
};
#elif defined(LED_ID_XS700037A11)
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */	  
/*num0*/ 	{0x0101,0x0201,0x0301,0x0401,0x0501,0x0601,0x0202},
/*num1*/	{0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0104},
/*num2*/ 	{0x0304,0x0404,0x0504,0x0604,0x0408,0x0508,0x0608},
/*num3*/	{0x0208,0x0210,0x0220,0x0240,0x0310,0x0320,0x0340},
};
const u16 led_icon_value[LED_ICON_NUMS]={
	//ICON_PLAY,ICON_PAUSE,ICON_USB,ICON_SD,ICON_FM,ICON_MP3,ICON_MINSEC_DEVIATE
	   0X0302, 0X0402,	0X0502,0X0602,0X0120, 0X0140,0X0108
};
#elif defined(LED_ID_SDX_88T48)
/*PLAY	USB  8 8:8.8 BT */
/*PAUSE   SD		   MP3*/
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */	  
/*num0*/ 	{0x0101,0x0201,0x0301,0x0401,0x0501,0x0601,0x0202},
/*num1*/	{0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0104},
/*num2*/ 	{0x0304,0x0404,0x0504,0x0604,0x0408,0x0508,0x0608},
/*num3*/	{0x0208,0x0210,0x0220,0x0240,0x0310,0x0320,0x0340},
};
const u16 led_icon_value[LED_ICON_NUMS]={
	//ICON_PLAY,ICON_PAUSE,ICON_USB,ICON_SD,ICON_BT,ICON_FM,ICON_MINSEC_DEVIATE,ICON_DECIMAL
	   0X0302, 0X0402,	0X0502,0X0602,0X0120, 0X0140,0X0108,0x0110
};

#elif defined(LED_ID_4018N_2B)
/*  8 8:8.8*/
/*  aux sd usb fm bat*/
//   usb sd fm aux bat

const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0002,0x0004,0x0301,0x0401,0x0008,0x0101,0x0201},
/*num1*/ 	{0x0104,0x0108,0x0402,0x0120,0x0110,0x0202,0x0302},
/*num2*/ 	{0x0408,0x0210,0x0310,0x0501,0x0504,0x0304,0x0404},
/*num3*/ 	{0x0620,0x0540,0x0420,0x0508,0x0320,0x0510,0x0440},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 

	//LED_AUX,LED_USB,LED_USB,LED_FM,LED_2POINT,LED_DOT,LED_BAT
	
	   0X0020, 0X0220,	0X0502,0X0010,0X0208, 0X0610,0X0240
};

#elif defined(LED_ID_4018N_2)
/*  8 8:8.8*/
/*  usb sd fm aux bat*/
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0002,0x0004,0x0301,0x0401,0x0008,0x0101,0x0201},
/*num1*/ 	{0x0104,0x0108,0x0402,0x0120,0x0110,0x0202,0x0302},
/*num2*/ 	{0x0408,0x0210,0x0310,0x0501,0x0504,0x0304,0x0404},
/*num3*/ 	{0x0620,0x0540,0x0420,0x0508,0x0320,0x0510,0x0440},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_USB,LED_SD,LED_FM,LED_AUX,LED_2POINT,LED_DOT,LED_BAT
	   0X0020, 0X0220,	0X0502,0X0010,0X0208, 0X0610,0X0240
};
#elif defined(LED_ID_40N18SRB_15)
/*  8 8:8.8*/
/*  MP3 SD USB RECO REPLAY*/
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0101,0x0201,0x0008,0x0010,0x0301,0x0002,0x0004},
/*num1*/ 	{0x0202,0x0302,0x0110,0x0502,0x0402,0x0104,0x0108},
/*num2*/ 	{0x0310,0x0404,0x0408,0x0020,0x0220,0x0208,0x0210},
/*num3*/ 	{0x0540,0x0620,0x0510,0x0320,0x0508,0x0420,0x0610},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_MP3,LED_SD,LED_USB,LED_RECO,LED_2POINT,LED_DOT,LED_REPLAY
	   0X0501, 0X0504,	0X0120,0X0401,0X0304, 0X0440,0X0604
};
#elif defined(LED_ID_JW4018D_3)
/*  8 8:8.8*/
/*  aux usb sd fm mp3 bat01 bat02 bat03*/
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0002,0x0004,0x0301,0x0401,0x0008,0x0101,0x0201},
/*num1*/ 	{0x0104,0x0108,0x0402,0x0120,0x0110,0x0202,0x0302},
/*num2*/ 	{0x0408,0x0210,0x0310,0x0501,0x0504,0x0304,0x0404},
/*num3*/ 	{0x0620,0x0540,0x0420,0x0508,0x0320,0x0510,0x0440},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_AUX,LED_USB,LED_SD,LED_FM,LED_MP3,LED_2POINT,LED_DOT,LED_BAT01,LED_BAT02,LED_BAT03
	  0X0020, 0X0502,0X0220,0X0010,0X0604, 0X0208,0X0610,0X0040,0X0140,0X0340
};

#elif defined(LED_ID_40T18SRB)
/*  8 8:8.8*/
/*  bt sd usb reco replay  bat01 bat02 bat03*/
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0101,0x0201,0x0008,0x0010,0x0301,0x0002,0x0004},
/*num1*/	{0x0202,0x0302,0x0110,0x0502,0x0402,0x0104,0x0108},
/*num2*/ 	{0x0310,0x0404,0x0408,0x0020,0x0220,0x0208,0x0210},
/*num3*/	{0x0540,0x0620,0x0510,0x0320,0x0508,0x0420,0x0610},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_BT,LED_SD,LED_USB,LED_RECO,LED_REPLAY,LED_2POINT,LED_DOT,LED_BAT01,LED_BAT02,LED_BAT03
	0X0040, 0X0401,0X0120,0X0140,0X0340, 0X0304,0X0440,0X0601,0X0602,0X0608
};
#elif defined(LED_ID_4018_73)
/*  8 8:8.8*/
/*  bt sd usb reco replay  bat01 bat02 bat03*/
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0101,0x0201,0x0008,0x0010,0x0301,0x0002,0x0004},
/*num1*/	{0x0202,0x0302,0x0110,0x0502,0x0402,0x0104,0x0108},
/*num2*/ 	{0x0310,0x0404,0x0408,0x0020,0x0220,0x0208,0x0210},
/*num3*/	{0x0540,0x0620,0x0510,0x0320,0x0508,0x0420,0x0610},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_BT,LED_SD,LED_USB,LED_RECO,LED_REPLAY,LED_2POINT,LED_DOT,LED_BAT01,LED_BAT02,LED_BAT03
	0X0540, 0X0120,0X0504,0X0401,0X0604, 0X0304,0X0440,0X0040,0X0140,0X0340
};

#elif defined(LED_ID_JW4018D_1A)
/*  8 8:8.8*/
/*  play usb pause sd fm  bat01 bat02 bat03*/
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0002,0x0004,0x0301,0x0401,0x0008,0x0101,0x0201},
/*num1*/ 	{0x0104,0x0108,0x0402,0x0120,0x0110,0x0202,0x0302},
/*num2*/ 	{0x0408,0x0210,0x0310,0x0501,0x0504,0x0304,0x0404},
/*num3*/ 	{0x0620,0x0540,0x0420,0x0508,0x0320,0x0510,0x0440},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_PLAY,LED_USB,LED_PAUSE,LED_SD,LED_FM,LED_2POINT,LED_DOT,LED_BAT01,LED_BAT02,LED_BAT03
	  0X0020, 0X0502,0X0220,0X0010,0X0604, 0X0208,0X0610,0X0040,0X0140,0X0340
};

#elif defined(LED_ID_JW54627_1BB) //ÃŒÃ¬Â·Ã¥
/*  8 8:8.8*/

const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0002,0x0004,0x0301,0x0401,0x0008,0x0101,0x0201},
/*num1*/ 	{0x0104,0x0108,0x0402,0x0120,0x0110,0x0202,0x0302},
/*num2*/ 	{0x0408,0x0210,0x0310,0x0501,0x0504,0x0304,0x0404},
/*num3*/ 	{0x0620,0x0540,0x0420,0x0508,0x0320,0x0510,0x0440},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_2POINT,LED_DOT
	0X0208, 0X0610
};

#elif defined(LED_ID_JW4018D_1B) //ÃŒÃ¬Â·Ã¥
/*  8 8:8.8*/
/*  bt sd usb reco replay  bat01 bat02 bat03*/
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0002,0x0004,0x0301,0x0401,0x0008,0x0101,0x0201},
/*num1*/ 	{0x0104,0x0108,0x0402,0x0120,0x0110,0x0202,0x0302},
/*num2*/ 	{0x0408,0x0210,0x0310,0x0501,0x0504,0x0304,0x0404},
/*num3*/ 	{0x0620,0x0540,0x0420,0x0508,0x0320,0x0510,0x0440},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_BT,LED_SD,LED_USB,LED_RECO,LED_REPLAY,LED_2POINT,LED_DOT,LED_BAT01,LED_BAT02,LED_BAT03
	0X0020, 0X0502,0X0220,0X0010,0X0604, 0X0208,0X0610,0X0040,0X0140,0X0340
};
#elif defined(LED_ID_4018_72) //ÃŒÃ¬Â·Ã¥
/*  8 8:8.8*/
/*  bt sd usb reco replay  bat01 bat02 bat03*/
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/	  {0x0002,0x0004,0x0301,0x0401,0x0008,0x0101,0x0201},
/*num1*/	  {0x0104,0x0108,0x0402,0x0120,0x0110,0x0202,0x0302},
/*num2*/	  {0x0408,0x0210,0x0310,0x0501,0x0504,0x0304,0x0404},
/*num3*/	  {0x0620,0x0540,0x0420,0x0508,0x0320,0x0510,0x0440},
};
#ifdef GW_011_AC4601
const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_BT,LED_SD,LED_USB,LED_RECO,LED_REPLAY,LED_2POINT,LED_DOT,LED_BAT01,LED_BAT02,LED_BAT03
	0X0601, 0X0010,0X0502,0X0000,0X0000, 0X0208,0X0610,0X0040,0X0140,0X0340
};
#else
const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_BT,LED_SD,LED_USB,LED_RECO,LED_REPLAY,LED_2POINT,LED_DOT,LED_BAT01,LED_BAT02,LED_BAT03
	0X0601, 0X0010,0X0502,0X0602,0X0608, 0X0208,0X0610,0X0040,0X0140,0X0340
};
#endif
#elif defined(LED_ID_KF33T1) //ÃŒÃ¬Â·Ã¥
/*usb  8 8:8.8   bat01  */
/*TF              bat02 */
/*repeat           bat03*/
/*FM                bat04  bat_frame*/
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/	  {0x0002,0x0004,0x0301,0x0401,0x0008,0x0101,0x0201},
/*num1*/	  {0x0104,0x0108,0x0402,0x0120,0x0110,0x0202,0x0302},
/*num2*/	  {0x0408,0x0210,0x0310,0x0501,0x0504,0x0304,0x0404},
/*num3*/	  {0x0620,0x0540,0x0420,0x0508,0x0320,0x0510,0x0440},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_USB,LED_SD,LED_REPEAT,LED_FM,LED_2POINT,LED_DOT,LED_BAT01,LED_BAT02,LED_BAT03,LED_BAT04,LED_BAT_FRAME
	0X0020, 0X0220,0X0502,0X0010,0X0208,0X0610,0X0040,0X0601,0X0140,0x0602,0x060C
};
#elif defined(LED_ID_KD048AR_P15)
/*PLAY	USB  8 8:8.8 FM */
/*PAUSE   SD		   MP3*/
/*TF	REC  8 8:8.8    BAT_FULL */
/*FM  REPEAT		   BAT_HALF*/

const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ ///7PIN LED
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0002,0x0004,0x0301,0x0401,0x0008,0x0101,0x0201},
/*num1*/ 	{0x0104,0x0108,0x0402,0x0120,0x0110,0x0202,0x0302},
/*num2*/ 	{0x0408,0x0210,0x0310,0x501,0x0504,0x0304,0x0404},
/*num3*/ 	{0x0620,0x0540,0x0420,0x0508,0x0320,0x0510,0x0440},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
   // LED_TF,   LED_FM,  LED_REC, LED_REPEAT, LED_BAT_FULL,  LED_BAT_HALF,LED_DOT,LED_2POINT
     0X0020, 0X0220,  0X0502,0X0010,0X0604, 0X0240,0X0610,0X0208,
	 //0X0020, 0X0220,	0X0502,0X0010,0X0604, 0X0240,0X0612,0X0208, //led 8426 ¶àÁËLED_MHZ 0x0602
};
#elif defined(LED_ID_SD28N20)
//repeat bat_half bat_full
/*	  8 8:8.8 */
/*rec usb tf mic_priority */
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ ///7PIN LED
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0002,0x0004,0x0301,0x0401,0x0008,0x0101,0x0201},
/*num1*/ 	{0x0104,0x0108,0x0402,0x0120,0x0110,0x0202,0x0302},
/*num2*/ 	{0x0408,0x0210,0x0310,0x501,0x0504,0x0304,0x0404},
/*num3*/ 	{0x0620,0x0540,0x0420,0x0508,0x0320,0x0510,0x0440},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
   // LED_TF,   LED_USB,  LED_REC, LED_REPEAT, LED_MIC,LED_BAT_FULL,  LED_BAT_HALF,LED_DOT,LED_2POINT
     0X0010,  0X0502,  0X0220,  0X0020,  0X0240, 0X0604,    0X0140,    0x0610, 0X0208
	 //0X0020, 0X0220,	0X0502,0X0010,0X0604, 0X0240,0X0612,0X0208, //led 8426 ¶àÁËLED_MHZ 0x0602
};
#elif defined(LCD_ID_JXH_S6002A)
const  u16 led_nums[LED_8NUMS][LED_8GRIDS] ={ ///< ÃÃ‚7Â¶ÃÃŠÃ½Ã‚Ã«Â¹ÃœÃ—ÂªÂ»Â»Â±Ã­
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040},
/*num1*/ 	{0x0101,0x0102,0x0104,0x0108,0x0110,0x0120,0x0140},
/*num2*/ 	{0x0201,0x0202,0x0204,0x0208,0x0210,0x0220,0x0240},
/*num3*/ 	{0x0301,0x0302,0x0304,0x0308,0x0310,0x0320,0x0340},
};
//const u16 led_icon_nums[LED_ICON_NUMS]={ ///Â¶Ã”Ã“Â¦16ÃŽÂ»BIT
  //ICON_USB,ICON_SD,ICON_FM,ICON_DECIMAL,ICON_MINSEC_DEVIATE,ICON_MUTE,ICON_RAN,ICON_REPEAT,
//     0X0000, 0X0000,  0X0000,0X0000,0X0000, 0X0000,0X0000,0X0000,
//};

#elif defined(LCD_ID_XH600002A)
const  u16 led_nums[LED_8NUMS][LED_8GRIDS] ={ ///< ÃÃ‚7Â¶ÃÃŠÃ½Ã‚Ã«Â¹ÃœÃ—ÂªÂ»Â»Â±Ã­
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040},
/*num1*/ 	{0x0101,0x0102,0x0104,0x0108,0x0110,0x0120,0x0140},
/*num2*/ 	{0x0201,0x0202,0x0204,0x0208,0x0210,0x0220,0x0240},
/*num3*/ 	{0x0301,0x0302,0x0304,0x0308,0x0310,0x0320,0x0340},
};
//const u16 led_icon_nums[LED_ICON_NUMS]={ ///Â¶Ã”Ã“Â¦16ÃŽÂ»BIT
  //ICON_USB,ICON_SD,ICON_FM,ICON_DECIMAL,ICON_MINSEC_DEVIATE,ICON_MUTE,ICON_RAN,ICON_REPEAT,
//     0X0000, 0X0000,  0X0000,0X0000,0X0000, 0X0000,0X0000,0X0000,
//};
#elif defined(LCD_ID_HL_21716HNT)
const  u16 led_nums[LED_8NUMS][LED_8GRIDS] ={ ///< ÃÃ‚7Â¶ÃÃŠÃ½Ã‚Ã«Â¹ÃœÃ—ÂªÂ»Â»Â±Ã­
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0002,0x0102,0x0202,0x0302,0x0201,0x0001,0x0101},
/*num1*/ 	{0x0008,0x0108,0x0208,0x0308,0x0204,0x0004,0x0104},
/*num2*/ 	{0x0020,0x0120,0x0220,0x0320,0x0210,0x0010,0x0110},
/*num3*/ 	{0x0080,0x0180,0x0280,0x0380,0x0240,0x0040,0x0140},
};
//const u16 led_icon_nums[LED_ICON_NUMS]={ ///Â¶Ã”Ã“Â¦16ÃŽÂ»BIT
  //LED_2POINT,LED_SD,LED_USB,LED_DOT,LED_BT,LED_RECO,LED_MUTE,LED_FOLDER,
//     0X0000, 0X0000,  0X0000,0X0000,0X0000, 0X0000,0X0000,0X0000,
//};
#elif defined(LED_ID_KF8426GH) //ÃŒÃ¬Â·Ã¥
/* play 8 8:8.8  mp3*/
/* pause         aux*/
/* usb            bt*/
/*sd              mhz*/
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0002,0x0004,0x0301,0x0401,0x0008,0x0101,0x0201},
/*num1*/ 	{0x0104,0x0108,0x0402,0x0120,0x0110,0x0202,0x0302},
/*num2*/ 	{0x0408,0x0210,0x0310,0x0501,0x0504,0x0304,0x0404},
/*num3*/ 	{0x0620,0x0540,0x0420,0x0508,0x0320,0x0510,0x0440},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_PLAY,LED_PAUSE,LED_USB,LED_SD,LED_2POINT,LED_DOT,LED_MP3,LED_AUX,LED_BT,LED_MHZ
	0X0020, 0X0220,0X0502,0X0010,0X0208, 0X0610,0X0240,0X0601,0X0604,0X0602
};
#elif defined(LED_ID_ZY3053) //ÃŒÃ¬Â·Ã¥
/* play 8 8:8.8  mp3*/
/* pause         aux*/
/* usb            fm*/
/*sd              mhz*/
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0A01,0x0A02,0x0A10,0x0A20,0x0A80,0x0A04,0x0A40},
/*num1*/ 	{0x0C01,0x0C02,0x0C10,0x0C20,0x0C80,0x0C04,0x0C40},
/*num2*/ 	{0x0801,0x0802,0x0810,0x0820,0x0880,0x0804,0x0840},
/*num3*/ 	{0x0601,0x0602,0x0610,0x0620,0x0680,0x0604,0x0640},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_PLAY,LED_PAUSE,LED_USB,LED_SD,LED_2POINT,LED_DOT,LED_MP3,LED_AUX,LED_FM,LED_MHZ
	0X0202, 0X0401,0X0402,0X0410,0X0480, 0X0240,0X0201,0X0404,0X0420,0X0440
};
#elif defined(VFD_ID_YDL2001_35) //ÃŒÃ¬Â·Ã¥
/*  8 8:8.8*/
/*  bt sd usb reco replay  bat01 bat02 bat03*/
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0910,0x0920,0x0908,0x0902,0x0904,0x0940,0x0980},
/*num1*/ 	{0x0710,0x0720,0x0708,0x0702,0x0704,0x0740,0x0780},
/*num2*/ 	{0x0640,0x0620,0x0604,0x0601,0x0602,0x0610,0x0608},
/*num3*/ 	{0x0510,0x0520,0x0508,0x0502,0x0504,0x0540,0x0580},
/*num4*/	{0x0440,0x0420,0x0404,0x0401,0x0402,0x0410,0x0408},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_MP3,LED_ALL,LED_REPEAT,LED_PLAY,LED_PAUSE,LED_2POINT,LED_H2POINT,LED_C01,LED_C02,LED_C03
	0X0810, 0X0808,0X0804,0X0802,0X0801, 0X0501,0X0901,0X0820,0X0840,0X0880
};
const u16 led_EQ[LED_EQ_NUMS][LED_EQ_BAR_GRIDS]={ 
/*BAR0*/	{0x0301,0x0302,0x0304,0x0308,0x0380,0x0340,0x0320,0x0310},
/*BAR1*/	{0x0201,0x0202,0x0204,0x0208,0x0210,0x0220,0x0240,0x0280},
/*BAR2*/	{0x0101,0x0102,0x0104,0x0108,0x0180,0x0140,0x0120,0x0110},
/*BAR3*/	{0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080},
};
#elif defined(LED_ID_JW8222_1B)
/*  eq03 eq02 eq01 eq0 8 8:8.8  eq04 eq05 eq06 eq07*/
/*         swvol tre dvd mp3 fm bt volume         */
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0001,0x0201,0x0401,0x0601,0x0801,0x0a01,0x0c01},
/*num1*/ 	{0x0002,0x0202,0x0402,0x0602,0x0802,0x0a02,0x0c02},
/*num2*/ 	{0x0004,0x0204,0x0404,0x0604,0x0804,0x0a04,0x0c04},
/*num3*/ 	{0x0008,0x0208,0x0408,0x0608,0x0808,0x0a08,0x0c08},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_SWVOL,LED_TRE,LED_DVD,LED_MP3,LED_2POINT,LED_DOT,LED_FM,LED_BT,LED_VOLUME,LED_SUBWOOFER
	0X0A20, 0X0680,0X0620,0X0420,0X0C20, 0X0880,0X0220,0X0C10,0X0280,0X00A0
};
const u16 led_EQ[LED_EQ_NUMS]={ 
    0x0a10,0x0010,0x0610,0x0210,0x0240,0x0040,0x0440,0x0840
};

#elif defined(LED_ID_YUNKE01)
/*  eq03 eq02 eq01 eq0 8 8:8.8  eq04 eq05 eq06 eq07*/
/*         swvol tre dvd mp3 fm bt volume         */
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0102,0x0101,0x0080,0x0040,0x0020,0x0010,0x0008},
/*num1*/ 	{0x0302,0x0301,0x0280,0x0240,0x0220,0x0210,0x0208},
/*num2*/ 	{0x0502,0x0501,0x0480,0x0440,0x0420,0x0410,0x0408},
/*num3*/ 	{0x0702,0x0701,0x0680,0x0640,0x0620,0x0610,0x0608},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_SD,LED_USB,LED_DVD,LED_FM,LED_2POINT,LED_DOT,LED_AUX,LED_BT,LED_SUBWOOFER
	0X0004, 0X0002,0X0401,0X0402,0X0C02, 0X0C01,0X0602,0X0604,0X0207
};
//const u16 led_EQ[LED_EQ_NUMS]={ 
//    0x0a10,0x0010,0x0610,0x0210,0x0240,0x0040,0x0440,0x0840
//};

#elif defined(LED_ID_SD40C18SRB)
/*
	eq00 eq01 eq02 eq03 eq04
	eq10 eq21 eq22 eq23 eq24	
			8 8:8.8	
BT   SD  USB  REC RECPLAY  BAT1 2 3

*/
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0010,0x0210,0x0410,0x0610,0x0e10,0x0c10,0x0a10},
/*num1*/ 	{0x0008,0x0208,0x0408,0x0608,0x0e08,0x0c08,0x0a08},
/*num2*/ 	{0x0004,0x0204,0x0404,0x0604,0x0e04,0x0c04,0x0a04},
/*num3*/ 	{0x0002,0x0202,0x0402,0x0602,0x0e02,0x0c02,0x0a02},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
  //LED_BT,    LED_USB,   LED_SD,  LED_REC, LED_2POINT, LED_2POINT1,LED_DOT,LED_REPLAY,LED_BAT01,LED_BAT02,LED_BAT03
     0X0810,           0X0201,  0X0001,   0X0401,      0X0804,          0X0808,      0X0601,   0X0802,      0x0e01,      0x0c01,      0x0a01
};
const u16 led_EQ[LED_EQ_NUMS]={ 
    0x0f02,0x0f01,0x0e80,0x0e40,0x0e20,
    0x0d02,0x0d01,0x0d80,0x0d40,0x0d20
};

#elif defined(LED_ID_JW5348_1A)
/*  eq03 eq02 eq01 eq0 8 8:8.8  eq04 eq05 eq06 eq07*/
/*         swvol tre dvd mp3 fm bt volume         */
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040},
/*num1*/ 	{0x0201,0x0202,0x0204,0x0208,0x0210,0x0220,0x0240},
/*num2*/ 	{0x0401,0x0402,0x0404,0x0408,0x0410,0x0420,0x0440},
/*num3*/ 	{0x0601,0x0602,0x0604,0x0608,0x0610,0x0620,0x0640},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_MP3,LED_DVD,LED_FM,LED_VOLUME,LED_2POINT,LED_DOT,LED_BT,LED_MHZ,LED_POWER
	0X0801, 0X0802,0X0804,0X0a03,0X0680, 0X0480,0X0a10,0X0a40,0X0880
};
const u16 led_EQ[LED_EQ_NUMS]={ 
    0x0c08,0x0c04,0x0c02,0x0c01
    ,0x0c80,0x0c40,0x0c20,0x0c10
};
#elif defined(LED_ID_8812)
//  AUX  BAT_FUL BAT_HALF
/*	8 8:88             */
/* USB  CARD	      FM  */
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ ///7PIN LED
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0108,0x0302,0x0104,0x0002,0x0101,0x0202,0x0201},
/*num1*/ 	{0x0140,0x0110,0x0310,0x0208,0x0404,0x0304,0x0210},
/*num2*/ 	{0x0502,0x0504,0x0420,0x0510,0x0508,0x0220,0x0320},
/*num3*/ 	{0x0240,0x0608,0x0540,0x0620,0x0610,0x0340,0x0440},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
   //LED_AUX,LED_BAT_FULL,LED_BAT_HALF,  LED_USB, LED_CARD,  LED_FM,LED_2POINT
     0X0401,  0X0010,    0X0604,    0X0120,0X0402, 0X0602  ,0X0408,
};

#elif defined(LED_ID_DOUBLE_PANEL)

// 88:8.8    88:8.8

const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ ///7PIN LED
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0d02,0x0902,0x0502,0x0302,0x0102,0x0b02,0x0702},
/*num1*/ 	{0x0d01,0x0901,0x0501,0x0301,0x0101,0x0b01,0x0701},
/*num2*/ 	{0x0c80,0x0880,0x0480,0x0280,0x0080,0x0a80,0x0680},
/*num3*/ 	{0x0c40,0x0840,0x0440,0x0240,0x0040,0x0a40,0x0640},
/*num4*/	{0x0c04,0x0804,0x0404,0x0204,0x0004,0x0a04,0x0604},
/*num5*/	{0x0c08,0x0808,0x0408,0x0208,0x0008,0x0a08,0x0608},
/*num6*/	{0x0c10,0x0810,0x0410,0x0210,0x0010,0x0a10,0x0610},
/*num7*/	{0x0c02,0x0802,0x0402,0x0202,0x0002,0x0a02,0x0602},
};

const u16 led_icon_value[LED_ICON_NUMS]={ 
   //LED_1PONIT,LED_2PONIT,LED_FM,   
     0X0001,0X0020,0X0620,0X0601
};

#elif defined(LED_ID_WLD007)
//usb play  888:88:88 repeat
/* sd pause            dts  */
/* mp3 fm    	         ac3  */
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ ///7PIN LED
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0008,0x0208,0x0408,0x0608,0x0808,0x0A08,0x0C08},
/*num1*/ 	{0x0010,0x0210,0x0410,0x0610,0x0810,0x0A10,0x0C10},
/*num2*/ 	{0x0004,0x0204,0x0404,0x0604,0x0804,0x0A04,0x0C04},
/*num3*/ 	{0x0020,0x0220,0x0420,0x0620,0x0820,0x0A20,0x0C20},
/*num4*/	{0x0040,0x0240,0x0440,0x0640,0x0840,0x0A40,0x0C40},
/*num5*/	{0x0080,0x0280,0x0480,0x0680,0x0880,0x0A80,0x0C80},
/*num6*/	{0x0101,0x0301,0x0501,0x0701,0x0901,0x0b01,0x0d01},
};

const u16 led_icon_value[LED_ICON_NUMS]={ 
   //LED_USB,LED_SD,LED_MP3,  LED_FM, LED_PLAY,  LED_PAUSE,LED_2POINT,LED_REPEAT,LED_2POINT1
     0X0001,0X0201,0X0401,0X0601,0X0801,   0X0a01  ,0X0502,0X0102,0x0302
};
const u16 led_circle_value[8]={ 
  0x0c01,0x0002,0x0202,0x0a02,0x0c02,0x0602,0x0402,0x0802
};

#elif defined(LED_ID_JW2781)
//usb play  888:88:88 repeat
/* sd pause            dts  */
/* mp3 fm    	         ac3  */
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ ///7PIN LED
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0001,0x0201,0x0401,0x0601,0x0801,0x0A01,0x0C01},
/*num1*/ 	{0x0002,0x0202,0x0402,0x0602,0x0802,0x0A02,0x0C02},
/*num2*/ 	{0x0080,0x0280,0x0480,0x0680,0x0880,0x0A80,0x0C80},
/*num3*/ 	{0x0004,0x0204,0x0404,0x0604,0x0804,0x0A04,0x0C04},
/*num4*/	{0x0008,0x0208,0x0408,0x0608,0x0808,0x0A08,0x0C08},
/*num5*/	{0x0010,0x0210,0x0410,0x0610,0x0810,0x0A10,0x0C10},
/*num6*/	{0x0020,0x0220,0x0420,0x0620,0x0820,0x0A20,0x0C20},
};
#ifdef LED_ID_XL2781_2BYRG
const u16 led_icon_value[LED_ICON_NUMS]={ 
   //LED_USB,LED_SD,LED_MP3,  LED_FM, LED_PLAY,  LED_PAUSE,LED_2POINT,LED_REPEAT,LED_EN_LED
     0X0102,0X0302,0X0502,0X0702,0X0902,   0X0B02  ,0X0440,0X0040,0X0a40
};
#elif defined LED_ID_JW2781_J_HD03_A
const u16 led_icon_value[LED_ICON_NUMS]={ 
   //LED_USB,LED_SD,LED_MP3,  LED_FM, LED_PLAY,  LED_PAUSE,LED_2POINT,LED_REPEAT
     0X0102,0X0302,0X0502,0X0702,0X0902,   0X0B02  ,0X0440,0X0040,0X0a40
};
#else
const u16 led_icon_value[LED_ICON_NUMS]={ 
   //LED_USB,LED_SD,LED_MP3,  LED_FM, LED_PLAY,  LED_PAUSE,LED_2POINT,LED_REPEAT
     0X0102,0X0302,0X0502,0X0702,0X0902,   0X0B02  ,0X0440,0X0040
};
#endif
const u16 led_circle_value[8]={ 
  0x0901,0x0d02,0x0101,0x0301,0x0b01,0x0d01,0x0701,0x0501
};
#elif defined(LED_ID_ZX001)
/*  play pause mp5 mp3 dvd tv srs    - - - - - */
/*  8:88:8.8                         - - - - - */
/*                                   - - - - - */
/*                                   - - - - - */
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0001,0x0201,0x0401,0x0601,0x0801,0x0a01,0x0c01},
/*num1*/ 	{0x0002,0x0202,0x0402,0x0602,0x0802,0x0a02,0x0c02},
/*num2*/ 	{0x0004,0x0204,0x0404,0x0604,0x0804,0x0a04,0x0c04},
/*num3*/ 	{0x0008,0x0208,0x0408,0x0608,0x0808,0x0a08,0x0c08},
/*num4*/	{0x0010,0x0210,0x0410,0x0610,0x0810,0x0a10,0x0c10},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_PLAY,LED_PAUSE,LED_2POINT,LED_2POINT1,LED_DOT,LED_MP3,LED_DVD,LED_SRS
	0X0020, 0X0220,   0X0240 ,   0X0040,  0X0440, 0X0620,0X0820,0X0C20
};
const u16 led_EQ[LED_EQ_NUMS][LED_EQ_BAR_GRIDS]={ 
/*BAR0*/	{0x0C40,0x0A40,0x0840,0x0640},
/*BAR1*/	{0x0680,0x0480,0x0280,0x0080},
/*BAR2*/	{0x0101,0x0C80,0x0A80,0x0880},
/*BAR3*/	{0x0901,0x0701,0x0501,0x0301},
/*BAR4*/	{0x0302,0x0102,0x0D01,0x0B01},
};


#elif defined(LED_ID_JM_950)

/*  
multimedia
---------
188.8
-- --
-- --
-- --
-- --
-- --
-- --
cd  dvd
volume front.vol
surr.vol cen.vol
sw.vol mic.vol echo
am  usb fm

*/
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0101,0x0008,0x0008,0x0101,0x0101,0x0101,0x0101},
/*num1*/ 	{0x0001,0x0201,0x0401,0x0601,0x0801,0x0a01,0x0c01},
/*num2*/ 	{0x0002,0x0202,0x0402,0x0602,0x0802,0x0a02,0x0c02},
/*num3*/ 	{0x0004,0x0204,0x0404,0x0604,0x0804,0x0a04,0x0c04},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_DOT,LED_CD,LED_DVD,LED_VOL,LED_FR,LED_SUR,LED_CEN,LED_SW,LED_SW,LED_ECHO,LED_AM,LED_USB,LED_FM
	0X0404, 0X0040, 0X0240 , 0X0440,  0X0640, 0X0840,0X0A40,0X0C40,0X0080,0X0280,0X0480,0X0680,0X0880
};
const u16 led_EQ[LED_EQ_NUMS][LED_EQ_BAR_GRIDS]={ 
/*BAR0*/	{0x0620,0x0220,0x0C10,0x0810,0x0410,0x0010},
/*BAR1*/	{0x0820,0x0220,0x0C10,0x0810,0x0410,0x0010},
/*BAR2*/	{0x0A20,0x0420,0x0020,0x0A10,0x0610,0x0210},
/*BAR3*/	{0x0C20,0x0420,0x0020,0x0A10,0x0610,0x0210},
};


#elif defined(LED_ID_JM_4169_B)
/*  play pause mp5 mp3 dvd tv srs    - - - - - */
/*  8:88:8.8                         - - - - - */
/*                                   - - - - - */
/*                                   - - - - - */
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0d02,0x0b02,0x0902,0x0702,0x0502,0x0302,0x0102},
/*num1*/ 	{0x0d01,0x0b01,0x0901,0x0701,0x0501,0x0301,0x0101},
/*num2*/ 	{0x0c80,0x0a80,0x0880,0x0680,0x0480,0x0280,0x0080},
/*num3*/ 	{0x0c01,0x0a01,0x0801,0x0601,0x0401,0x0201,0x0001},
/*num4*/	{0x0c02,0x0a02,0x0802,0x0602,0x0402,0x0202,0x0002},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_PLAY,LED_PAUSE,LED_2POINT,LED_2POINT1,LED_DOT,LED_MP3,LED_DVD,LED_SRS
	0X0c04, 0X0a04,   0X0a08 ,   0X0c08,  0X0808, 0X0604,0X0404,0X0004
};
const u16 led_EQ[LED_EQ_NUMS][LED_EQ_BAR_GRIDS]={ 
/*BAR0*/	{0x0008,0x0208,0x0408,0x0608},
/*BAR1*/	{0x0610,0x0810,0x0a10,0x0c10},
/*BAR2*/	{0x0c20,0x0010,0x0210,0x0410},
/*BAR3*/	{0x0420,0x0620,0x0820,0x0a20},
/*BAR4*/	{0x0a40,0x0c40,0x0020,0x0220},
};

#elif defined(LED_ID_JW1676_1B)
/*  play pause mp5 mp3 dvd tv srs    - - - - - */
/*  8:88:8.8                         - - - - - */
/*                                   - - - - - */
/*                                   - - - - - */
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0102,0x0302,0x0502,0x0702,0x0902,0x0B02,0x0D02},
/*num1*/ 	{0x0101,0x0301,0x0501,0x0701,0x0901,0x0B01,0x0D01},
/*num2*/ 	{0x0080,0x0280,0x0480,0x0680,0x0880,0x0a80,0x0c80},
/*num3*/ 	{0x0001,0x0201,0x0401,0x0601,0x0801,0x0a01,0x0c01},
/*num4*/	{0x0002,0x0202,0x0402,0x0602,0x0802,0x0a02,0x0c02},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_PLAY,LED_PAUSE,LED_2POINT,LED_2POINT1,LED_DOT,LED_MP3,LED_DVD,LED_SRS
	0X0004, 0X0204,   0X0208 ,   0X0008,  0X0408, 0X0604,0X0804,0X0C04
};
const u16 led_EQ[LED_EQ_NUMS][LED_EQ_BAR_GRIDS]={ 
/*BAR0*/	{0x0608,0x0808,0x0A08,0x0C08},
/*BAR1*/	{0x0010,0x0210,0x0410,0x0610},
/*BAR2*/	{0x0810,0x0A10,0x0C10,0x0040},
/*BAR3*/	{0x0240,0x0440,0x0640,0x0840},
/*BAR4*/	{0x0A40,0x0C40,0x0020,0x0220},
};
#elif defined(LED_ID_JW4520_2A) //13pin led
const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040},
/*num1*/ 	{0x0101,0x0102,0x0104,0x0108,0x0110,0x0120,0x0140},
/*num2*/ 	{0x0201,0x0202,0x0204,0x0208,0x0210,0x0220,0x0240},
/*num3*/ 	{0x0301,0x0302,0x0304,0x0308,0x0310,0x0320,0x0340},
};
const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_PLAY,LED_PAUSE,LED_2POINT,LED_DOT,LED_MP3,LED_USB,LED_SD,LED_IPHONE,LED_AUX,LED_FM,LED_MHZ
	  0X0502, 0X0401,   0X0410 ,0X0540,0X0501,0X0402,0X0404,0X050C, 0x0420,0x0408,0x0440
};

#elif defined(LED_ID_JW8426C7_1B) 
/*
	PLAY				MP3
	PAUSE 	8:88:8.8      	AUX
	USB					FM
	SD					MHZ
*/

const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0001,0x0002,0x0301,0x0401,0x0008,0x0101,0x0201},
/*num1*/ 	{0x0104,0x0108,0x0402,0x0120,0x0110,0x0202,0x0302},
/*num2*/ 	{0x0408,0x0210,0x0310,0x0501,0x0504,0x0304,0x0404},
/*num3*/ 	{0x0620,0x0540,0x0420,0x0508,0x0320,0x0510,0x0440},
};


const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_PLAY,LED_PAUSE,LED_USB,LED_SD,LED_2POINT,LED_DOT,LED_MP3,LED_AUX,LED_FM,LED_MHZ
	  0X0020, 0X0220,   0X0502 ,0X0010,0X0208,0X0610,0X0240,0X0601, 0x0604,0x0602
};

#elif defined(LED_ID_JW84267_4) 
/*
	PLAY				MP3
	PAUSE 	8:88:8.8      	AUX
	USB					FM
	SD					MHZ
*/

const u16 led_8grid_value[LED_8NUMS][LED_8GRIDS] ={ 
      /*   LED_A   LED_B   LED_C  LED_D   LED_E   LED_F  LED_G */
/*num0*/ 	{0x0002,0x0004,0x0301,0x0401,0x0008,0x0101,0x0201},
/*num1*/ 	{0x0104,0x0108,0x0402,0x0120,0x0110,0x0202,0x0302},
/*num2*/ 	{0x0408,0x0210,0x0310,0x0501,0x0504,0x0304,0x0404},
/*num3*/ 	{0x0620,0x0540,0x0420,0x0508,0x0320,0x0510,0x0440},
};

const u16 led_icon_value[LED_ICON_NUMS]={ 
	//LED_PLAY,LED_PAUSE,LED_USB,LED_SD,LED_2POINT,LED_DOT,LED_MP3,LED_AUX,LED_FM,LED_MHZ
	  0X0020, 0X0220,   0X0502 ,0X0010,0X0208,0X0610,0X0240,0X0601, 0x0604,0x0602
};

#endif

#if LED_8NUMS==7

#ifdef LED_ID_JW2781

	 const u8 playmodestr[][8] =
	 {
	     "  ALL  ",
	     "  Fold ",
	     "  ONE  ",
	     "  rAn  ",
	 };
	 
	 const u8 menu_string[][8] =
	 {
	     " HELLO ",
	     "LOAdIN9",
	     #ifdef LED_SHOW_BLUE_STRING____
	     "-------",
	     #elif defined(LED_BT_STATE_SHOW_STRING_Bt)
	     " bt    ",
	     #elif defined(LED_BT_STATE_SHOW_STRING_BLUE_IN)
	     "bLUE IN",
	     #elif defined(LED_BT_STATE_SHOW_STRING_BLUC)
	     "  bLUC ",	     
	     #else
	     "  bLUE ",
	     #endif
	     "  PC   ",
	     "  UP   ",
	     "  dN   ",
	 #ifdef LED_LINEIN_SHOW_AUX_IN
	     "AUH IN ",
	 #else
	     "LINE IN",
	 #endif    
	     " -AL-  ",
	 #ifdef SUPPORT_MP3_IDEL_MODE_IN_LINEIN_MODE
	 //    "  NO   ",
	 #ifdef LED_MP3_IDLE_MODE_SHOW_NO_USB
	 	  " NO USb",
	 #else
	 	  " NO",
	 #endif
	 
	 #endif
	 #ifdef SUPPORT_AC3_MODE_IN_LINEIN_MODE
	     "  AC-3 ",
	 #endif
	 #ifdef support_stanby_mod
	     "       ",
	     " 0FF   ",
	  #endif 
	 };
	 const u8 other_string[][8]=
	 {
	     "   Eq ",
	     " VOL ",
	     "   P ",
	     " NOP   ",
	 };
	 #ifdef LED_SHOW_DEVICE_PLUGIN
	 const u8 device_string[][8]=
	 {
	   "USb----",
	   "Sd-----"
	 };
	 #endif

#else
const u8 playmodestr[][8] =
{
    "ALL    ",
    "Fold   ",
    "ONE    ",
    "rAn    ",
};

const u8 menu_string[][8] =
{
#ifdef POWER_ON_LED_SHOW__HI_
    " -HI-  ",
#else
    "HELLO  ",
#endif    
#ifdef LED_ID_WLD007
    "LOAd   ",
#else
    "LOAdIN9",
#endif    
    #ifdef LED_SHOW_BLUE_STRING____
    "-------",
    #elif defined(LED_BT_STATE_SHOW_STRING_Bt)
    " bt    ",
    #else
    "bLUE   ",
    #endif
    "PC     ",
    "UP     ",
    "dN     ",
#ifdef LED_LINEIN_SHOW_AUX_IN
    "AUH IN ",
#else
    "LINE IN",
#endif    
    " -AL-  ",
#ifdef SUPPORT_MP3_IDEL_MODE_IN_LINEIN_MODE
    "  NO   ",
#endif
#ifdef SUPPORT_AC3_MODE_IN_LINEIN_MODE
    "AC-3   ",
#endif
#ifdef support_stanby_mod
    "       ",
    " 0FF   ",
 #endif 
};
const u8 other_string[][8]=
{
    "   Eq ",
    "  VOL",
    "   P ",
    " NOP   ",
    #if REC_EN
    " rec   ",	
    #endif    
};
#ifdef LED_SHOW_DEVICE_PLUGIN
const u8 device_string[][8]=
{
  "USb    ",
  "Sd     "
};
#endif

#endif

#elif LED_8NUMS==5
const u8 playmodestr[][6] =
{
    " ALL ",
    " Fold",
    " ONE ",
    " rAn ",
};

const u8 menu_string[][6] =
{
#ifdef POWER_ON_LED_SHOW__HI_
    " -HI-",
#else
    "HELLO",
#endif    
    " LOAd",
    #ifdef LED_SHOW_BLUE_STRING____
    "-----",
    #elif defined(LED_BT_STATE_SHOW_STRING_Bt)
    " bt ",
    #else
    " bLUE",
    #endif
    " PC ",
    " UP ",
    " dN ",
#ifdef support_aux_led_disp_line
    " LINE",
#elif defined(LINE_LED_SHOW_AC3)
    "AC-3"
#else 
    " AUX ",
#endif     
    " -AL-",
#ifdef SUPPORT_MP3_IDEL_MODE_IN_LINEIN_MODE
    "  NO ",
#endif
#ifdef SUPPORT_AC3_MODE_IN_LINEIN_MODE
    "AC-3",
#endif
#ifdef support_stanby_mod
   "     ",
  " 0FF",
 #endif 
};
const u8 other_string[][6]=
{
    " Eq ",
    "VOL",
    " P ",
    " NOP",
    #if REC_EN
	" rec ",
    #endif
};
#ifdef LED_SHOW_DEVICE_PLUGIN
const u8 device_string[][6]=
{
  " USb ",
  "  Sd "
};
#endif

#elif LED_8NUMS==8

const u8 playmodestr[][5] =
{
    " ALL",
    "Fold",
    " ONE",
    " rAn",
};

const u8 menu_string[][8] =
{
#ifdef POWER_ON_LED_SHOW__HI_
    "-HI-",
#elif defined(POWER_ON_LED_SHOW__q1)
    " q1 ",
#else
    " HI     ",
#endif    
    " Lod    ",
    #ifdef LED_SHOW_BLUE_STRING____
    "----",
    #elif defined(LED_BT_STATE_SHOW_STRING_Bt)
    " bt ",
    #elif defined(LED_BT_STATE_SHOW_STRING__Bt_)
    "-bt-",    
    #elif defined(LED_BT_STATE_SHOW_STRING_BLUC)
    "bLUC",        
    #else
    "bLUE",
    #endif
    " PC ",
    " UP ",
    " dN ",
#ifdef support_aux_led_disp_line
    "LINE",
#elif defined support_nop_show_nodi
    "NOdi",    
#elif defined support_nop_show_usb
    " USb",
#else 
    " AUX",
#endif     
    "-AL-",
#ifdef SUPPORT_MP3_IDEL_MODE_IN_LINEIN_MODE
#ifdef support_nop_show_usb
    " USb",
#elif defined support_nop_show_nodi
    "NOdi",
  #else
    " NO ",
#endif
#endif
#if defined(SUPPORT_AC3_MODE_IN_LINEIN_MODE)
#ifdef support_ac3_show_OPTI_CHAR
    "OPTi",
 #else
    "AC-3",
#endif	
#endif
#if defined(SUPPORT_CD_MODE_IN_LINEIN_MODE)
    " Cd ",
#endif
#if defined(SUPPORT_DVD_MODE_IN_LINEIN_MODE)
    " dUd",
#endif

#ifdef support_stanby_mod
   "        ",
  " 0FF    ",
 #endif 
};
const u8 other_string[][4]=
{
    "Eq ",
    " V",
    " P",
    " NOP",
	" rec",
};
#ifdef LED_SHOW_DEVICE_PLUGIN
const u8 device_string[][4]=
{
  " USb",
  " Sd "
};
#endif

#else

const u8 playmodestr[][5] =
{
    " ALL",
    "Fold",
    " ONE",
    " rAn",
};

const u8 menu_string[][5] =
{
#ifdef POWER_ON_LED_SHOW__HI_
    "-HI-",
#elif defined(POWER_ON_LED_SHOW__q1)
    " q1 ",
#else
    " HI ",
#endif    
    " Lod",
    #ifdef LED_SHOW_BLUE_STRING____
    "----",
    #elif defined(LED_BT_STATE_SHOW_STRING_Bt)
    " bt ",
    #elif defined(LED_BT_STATE_SHOW_STRING__Bt_)
    "-bt-",    
    #elif defined(LED_BT_STATE_SHOW_STRING_BLUC)
    "bLUC",        
    #else
    "bLUE",
    #endif
    " PC ",
    " UP ",
    " dN ",
#ifdef support_aux_led_disp_line
    "LINE",
#elif defined support_nop_show_nodi
    "NOdi",    
#elif defined support_nop_show_usb
    " USb",
#else 
    " AUX",
#endif     
    "-AL-",
#ifdef SUPPORT_MP3_IDEL_MODE_IN_LINEIN_MODE
#ifdef support_nop_show_usb
    " USb",
#elif defined support_nop_show_nodi
    "NOdi",
  #else
    " NO ",
#endif
#endif
#if defined(SUPPORT_AC3_MODE_IN_LINEIN_MODE)
#ifdef support_ac3_show_OPTI_CHAR
    "OPTi",
 #elif defined(support_ac3_show_vide_CHAR)
       "UIdE",
  #elif defined(SUPPORT_AC3_MODE_SHOW_AUX)
    " AUX",      
 #else
    "AC-3",
#endif	
#endif
#if defined(SUPPORT_CD_MODE_IN_LINEIN_MODE)
    " Cd ",
#endif
#if defined(SUPPORT_DVD_MODE_IN_LINEIN_MODE)
    " dUd",
#endif

#ifdef support_stanby_mod
   "    ",
  " 0FF",
 #endif 
};
const u8 other_string[][4]=
{
    "Eq ",
    " V",
    " P",
    " NOP",
	" rec",
};
#ifdef LED_SHOW_DEVICE_PLUGIN
const u8 device_string[][4]=
{
#ifdef SUPPORT_USB_SD_SHOW_U_S
  "  U ",
  "  S "
#else
  " USb",
  " Sd "
#endif  
};
#endif

#endif
/*----------------------------------------------------------------------------*/
/**@brief   led7_drv Ã—Â´ÃŒÂ¬ÃŽÂ»Â»ÂºÂ´Ã¦Ã‡Ã¥Â³Ã½ÂºÂ¯ÃŠÃ½
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_clear_icon(void)
*/
/*----------------------------------------------------------------------------*/
void led7_clear_icon(void)
{
    led7_var.bFlashChar = 0;
    led7_var.wFlashIcon = 0;
    led7_var.wLedIcon=0;	
}

/*----------------------------------------------------------------------------*/
/**@brief   led7_drv ÃÃ”ÃŠÂ¾Ã—Ã¸Â±ÃªÃ‰Ã¨Ã–Ãƒ
   @param   xÂ£ÂºÃÃ”ÃŠÂ¾ÂºÃ¡Ã—Ã¸Â±Ãª
   @return  void
   @author  Change.tsai
   @note    void led7_setX(u8 X)
*/
/*----------------------------------------------------------------------------*/
void led7_setX(u8 X)
{
    led7_var.bCoordinateX = X;
}

/*----------------------------------------------------------------------------*/
/**@brief   LED Ã‡Ã¥Ã†ÃÂºÂ¯ÃŠÃ½
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_show_null(void)
*/
/*----------------------------------------------------------------------------*/
void led7_show_null(void)
{
    led7_clear_icon();
    led7_var.bShowBuff[0] = 0;
    led7_var.bShowBuff[1] = 0;
    led7_var.bShowBuff[2] = 0;
    led7_var.bShowBuff[3] = 0;
    #if LED_8NUMS>=5
    led7_var.bShowBuff[4] = 0;
    #endif
    #if LED_8NUMS>=7
    led7_var.bShowBuff[5] = 0;
    led7_var.bShowBuff[6] = 0;
    #endif
    #if LED_8NUMS>=8
    led7_var.bShowBuff[7] = 0;
    #endif	
	
    #ifdef USE_HT1628_CONTROL_TENS_OF_RGB_LIGHTS
    led7_var.bLightDataBuf[0]=0;
    led7_var.bLightDataBuf[1]=0;
    led7_var.bLightDataBuf[2]=0;
    led7_var.bLightDataBuf[3]=0;
    led7_var.bLightDataBuf[4]=0;
    led7_var.bLightDataBuf[5]=0;
    led7_var.bLightDataBuf[6]=0;
    #endif
    #if defined(SUPPORT_LCD_4COM_9SEG_MODE)||defined(SUPPORT_LCD_5COM_8SEG_MODE)
    LCD_SEG_CLEAR();
    #endif
}

/*----------------------------------------------------------------------------*/
/**@brief   led7_drv Ã‰Â¨ÃƒÃ¨ÂºÂ¯ÃŠÃ½
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_init(void)
*/
/*----------------------------------------------------------------------------*/
void led7_init(void)
{
    led7_clear();
}


#ifdef led_icon_disp_vat_volage


#if defined(support_frd_7led) //ÂµÂ¥ÂµÃ§Â³Ã˜Â·Ã»ÂºÃ…

void  AT(.comm)  LED_display_bat_mode(void)
{

  static u16  bat_cnt;

          if(lod_power_mod>3 ) //ÂµÃÃ“Ãš3.5vÂ¿ÂªÃŠÂ¼Ã‰Ã
          {
           	bat_cnt++;
        	if (bat_cnt >=250)
                LED_STATUS |= LED_BAT_L;
     	      else //if (bat_cnt ==1)
              LED_STATUS &= ~LED_BAT_L;

        	if (bat_cnt >500)
                 bat_cnt=0;
          }
    	  else 
    	  {
    	   LED_STATUS  &= ~LED_BAT_L;
    	  }
}

#elif defined(support_33T14_long_bt_icon_led)


//voltage                          -    41   -     37  -    34   -   31  -
// lod_power_mod            1    -    2     -    3     -    4     -    5

void  AT(.comm)  LED_display_bat_mode(void)
{

  static u16  bat_cnt;
 static u16  bat_times;


#ifdef suppot_stanby_to_line_mode
       if(stanby_flag)
 	return;
#endif

#ifdef MAIN_APP
return; 
#endif  


#ifdef MUSIC_APP
if( g_isreturn||play_case_info)
  return;
#endif 

  
bat_times++;
if(bat_times<400)
{
return;
}
else  bat_times=1001;

     LED_STATUS2  =    LED_BAT;  //ÂµÃ§Â³Ã˜Â·Ã»ÂºÃ…ÃÃ¢Â¿Ã²
     LED_STATUS  &= ~LED_BAT_FULL;

   	if( lod_power_mod==1)   //>4.1
   		{

		LED_STATUS2 |= LED_BAT_HALF |LED_BAT_HALF_LOW |LED_BAT_LOW;
              LED_STATUS|=LED_BAT_FULL;
	        }
    else  if( lod_power_mod==2)  //>3.7
   		{
		   LED_STATUS2 |=LED_BAT_HALF |LED_BAT_HALF_LOW |LED_BAT_LOW;
	        }
    else  if( lod_power_mod==3)  //>3.4
   		{
		   LED_STATUS2 |=LED_BAT_HALF_LOW |LED_BAT_LOW;
	        }
    else  if( lod_power_mod==4)  //>3.1
   		{
		   LED_STATUS2 |=LED_BAT_LOW ;
	        }	
    else  if( lod_power_mod==5) //<=3.1
		{

			if (bat_cnt <=250)
			LED_STATUS2 |= LED_BAT_LOW;
		//	else if (bat_cnt ==1)
		//	LED_STATUS2 &= ~LED_BAT_LOW;

		      	bat_cnt++;
			if (bat_cnt >500)
			bat_cnt=0;   
		}

}



#elif defined(support_led_user_3314ab)||defined(support_led_user_3314ab_2)||defined(support_hf_long_bt_icon_led)||defined(support_xs2_long_bt_icon_led)

#if defined( customer_MEW_CN_JM3) 

void  AT(.comm)  LED_display_bat_mode(void)
{

  static u16  bat_cnt;
  static u16  bat_times;

        bat_times++;
         if(bat_times<1000)
           {
           return;
           }
        else  bat_times=1001;

#ifdef suppot_stanby_to_line_mode
       if(stanby_flag)
 	return;
#endif


#ifdef MAIN_APP
return; 
#endif  

           	bat_cnt++;

    #ifdef  support_ic_chack_dc_in

	
       DC_DET_IO_IS_IN();
       if(DC_DET_READ())
       	{
       		if( lod_power_mod>1) //Â³Ã¤ÂµÃ§
			{
			if (bat_cnt ==250)
			LED_STATUS |= LED_BAT_L;
			else if (bat_cnt ==1)
			LED_STATUS &= ~LED_BAT_L;
			if (bat_cnt >500)
			bat_cnt=0;   
			}

			else 
			{
			LED_STATUS  |= LED_BAT_L;   //Ã‚ÃºÂµÃ§
			}
       	}
	 else 
	#endif  
			{
			if(lod_power_mod>2 ) //ÂµÃÃ“Ãš3.5v  Â¹Ã˜ÂµÃ§Â³Ã˜Â·Ã»ÂºÃ…
				LED_STATUS &= ~LED_BAT_L;
			else 
		              LED_STATUS  |= LED_BAT_L;
			}

    	  
}
#elif defined(support_xs2_long_bt_icon_led)
void  AT(.comm)  LED_display_bat_mode(void)
{

  static u16  bat_cnt;
  static u16  bat_times;

bat_times++;
if(bat_times<1000)
{
return;
}
else  bat_times=1001;




#ifdef MAIN_APP
return; 
#endif  

      	bat_cnt++;

       DC_DET_IO_IS_IN();
	   
	 if ( DC_DET_READ() ) 
	    {
            if( lod_power_mod>1)
             	{
  		
  	    //  	if (bat_cnt ==250)
                 LED_STATUS |= LED_BAT_L;
       	//      else if (bat_cnt ==1)
             //   LED_STATUS &= ~LED_BAT_L;
             	}
	     else 
		LED_STATUS  &= ~LED_BAT_L;   //Ã‚ÃºÂµÃ§ÃƒÃ°
		 
               if (bat_cnt >500)
                bat_cnt=0;   
			
	     }
	 else if(lod_power_mod>3)           	
          {
        	if (bat_cnt ==100)
                LED_STATUS |= LED_BAT_L;
     	      else if (bat_cnt ==1)
              LED_STATUS &= ~LED_BAT_L;
			  
               if (bat_cnt >200)
                bat_cnt=0;      
          }
    	  else 
    	  {
    //	   LED_STATUS  |= LED_BAT_L;
     LED_STATUS &= ~LED_BAT_L;
    	  }

	     


    	  
}

#else 

void  AT(.comm)  LED_display_bat_mode(void)
{

  static u16  bat_cnt;
  static u16  bat_times;

bat_times++;
if(bat_times<1000)
{
return;
}
else  bat_times=1001;




#ifdef MAIN_APP
return; 
#endif  

           	bat_cnt++;

#ifdef support_xs_power_off_bat_led

#else 
          #ifdef suppot_stanby_to_line_mode
                 if(stanby_flag)
           	return;
          #endif
          #if defined(support_line_power_off_bat_display)
                #ifdef LINEIN_APP
                     	if(power_off_flag )
                     	 lod_power_mod=2; //Â²Â»Ã„ÃœÂ¼Ã¬Â²Ã¢ÂµÃ§Ã‘Â¹Â¹Ã‹Ã’Â»Ã–Â±Â½Â»ÃŒÃ¦Ã‰Ã
                #endif 
          
          #endif
#endif 

    #ifdef  support_ic_chack_dc_in
       DC_DET_IO_IS_IN();
	 if ( DC_DET_READ() && lod_power_mod>1) 
	    {
	            	if (bat_cnt ==250)
                LED_STATUS |= LED_BAT_L;
     	      else if (bat_cnt ==1)
              LED_STATUS &= ~LED_BAT_L;
               if (bat_cnt >500)
                bat_cnt=0;   
	     }
	 else if(lod_power_mod>3)           	
          {
        	if (bat_cnt ==100)
                LED_STATUS |= LED_BAT_L;
     	      else if (bat_cnt ==1)
              LED_STATUS &= ~LED_BAT_L;
			  
               if (bat_cnt >200)
                bat_cnt=0;      
          }
    	  else 
    	  {
    	   LED_STATUS  |= LED_BAT_L;
    	  }

	     
	#else 
       if(lod_power_mod>3 ) //ÂµÃÃ“Ãš3.5vÂ¿ÂªÃŠÂ¼Ã‰Ã
           	
          {
        	if (bat_cnt ==250)
                LED_STATUS |= LED_BAT_L;
     	      else if (bat_cnt ==1)
              LED_STATUS &= ~LED_BAT_L;

          }
    	  else 
    	  {
    	   LED_STATUS  |= LED_BAT_L;
    	  }
	    if (bat_cnt >500)
           bat_cnt=0;
	#endif 

    	  
}

#endif 


#elif defined(support_sw_led_003)

 // lod_power_mod;   // //1 :> 4.2   2:   4.2v--3v7   3:  3v7-  3v3  4 :<3v3
void  AT(.comm)  LED_display_bat_mode(void)
{

#ifdef MAIN_APP

 
 
#else 
  static u16  bat_cnt;
#ifdef suppot_stanby_to_line_mode
	if(stanby_flag)
		return;
#endif


  #if 0//def supper_change_power_dec
       charge_detect_in();

 
              if(charge_status_port)  //Ã“ÃÃÃ¢ÂµÃ§Â½Ã“ÃˆÃ«
          	{	
 		    if(power_value > 42)
 		    {
 		      current_ldo_voltage=1;	  
 		    }
      	  	else  // Ã•Ã½Ã”ÃšÂ³Ã¤ÂµÃ§
      	  	{
 		 #ifdef charge_show_use_high_low
 		 	current_ldo_voltage=5;
 		 #else
 		 	current_ldo_voltage=4;
 		 #endif
      	  	}	
      	}
 			
 #endif 	


		LED_STATUS2  =0;

		switch (lod_power_mod)
		{
			case  1 :
				LED_STATUS2 |= (LED_BAT_FULL |LED_BAT_HALF|LED_BAT_LOW);
			case 2:
				LED_STATUS2 |= (LED_BAT_HALF|LED_BAT_LOW);
			break;
			case 3:
				LED_STATUS2 |=LED_BAT_LOW;
			break;

			case 4:
				bat_cnt++;
				if (bat_cnt >250)
				LED_STATUS2 |= LED_BAT_LOW;
				else
				LED_STATUS2 &= ~LED_BAT_LOW;

				if (bat_cnt >500)
				bat_cnt=0;
			break;
		}
	 
#endif 
 }
#else 
//extern  u8  lod_power_mod;    // //1 :> 4.2   2:   4.2v--3v7   3:  3v7-  3v3  4 :<3v3

void   LED_display_bat_mode(void)
{

  static u16  bat_cnt;

   LED_STATUS  &= ~(LED_BAT_L|LED_BAT_H);


#ifdef  support_ic_chack_dc_in
		DC_DET_IO_IS_IN();
		if( DC_DET_READ())
		{
		 if(ldo_power_mod==1)
		     LED_STATUS |= LED_BAT_H;
		 else
			{
			bat_cnt++;
		  if (bat_cnt >800)
		           bat_cnt=0;

			if (bat_cnt >550)
		  {
		  	   LED_STATUS |= LED_BAT_H;
		          LED_STATUS |= LED_BAT_L;
		  }
		      else if (bat_cnt >300)
		      LED_STATUS |= LED_BAT_L;

			 }
		 }
		else
#endif

  /*   1;	  //Ã‚Ãº     2;  Â¸ÃŸ   3;   Â°Ã«   4; ÂµÃ   5;  ÂµÃÂµÃ   6;   ÂµÃÂ¹Ã˜Â»Ãº   */

  {
             switch (ldo_power_mod)
             	{
             	case   0:   break;    //Â¿ÂªÂ»ÃºÃƒÂ»Â¼Ã¬Â²Ã¢ÂµÂ½Ã—Â´ÃŒÂ¬ÃŠÂ±
              case  1 :
              case  2:
	  	case  3:

          	LED_STATUS |= LED_BAT_H;
     #ifdef  bat_full_disp_bat_h_l  	
             LED_STATUS |= LED_BAT_L;
     #endif         
               break;
              case 4:
          	//LED_STATUS |= LED_BAT_H;
                LED_STATUS |= LED_BAT_L;
        	break;

          case 5:
          case 6:
        	bat_cnt++;
        	if (bat_cnt >250)
                LED_STATUS |= LED_BAT_L;
       // 	else
         //       LED_STATUS &= ~LED_BAT_L;

        	if (bat_cnt >500)
                 bat_cnt=0;
        	break;

             	}
    }

 }
#endif 
#endif



/*----------------------------------------------------------------------------*/
/**@brief   led7_drv ÂµÂ¥Â¸Ã¶Ã—Ã–Â·Ã»ÃÃ”ÃŠÂ¾ÂºÂ¯ÃŠÃ½
   @param   chardataÂ£ÂºÃÃ”ÃŠÂ¾Ã—Ã–Â·Ã»
   @return  void
   @author  Change.tsai
   @note    void led7_show_char(u8 chardata)
*/
/*----------------------------------------------------------------------------*/
void led7_show_char(u8 chardata)
{
    //Â±Ã˜ÃÃ«Â±Â£Ã–Â¤Â´Â«ÃˆÃ«ÂµÃ„Â²ÃŽÃŠÃ½Â·Ã»ÂºÃÂ·Â¶ÃŽÂ§Â£Â¬Â³ÃŒÃÃ²Â²Â»Ã—Ã·Ã…ÃÂ¶Ã
    //if ((chardata < ' ') || (chardata > '~') || (led7_var.bCoordinateX > 4))
    //{
    //    return;
    //}
    if ((chardata >= '0') && (chardata <= '9'))
    {
        led7_var.bShowBuff[led7_var.bCoordinateX++] = LED_NUMBER[chardata - '0'];
    }
    else if ((chardata >= 'a') && (chardata <= 'z'))
    {
        led7_var.bShowBuff[led7_var.bCoordinateX++] = LED_SMALL_LETTER[chardata - 'a'];
    }
    else if ((chardata >= 'A') && (chardata <= 'Z'))
    {
        led7_var.bShowBuff[led7_var.bCoordinateX++] = LED_LARGE_LETTER[chardata - 'A'];
    }
    else if (chardata == ':')
    {
        LED_STATUS |= LED_2POINT;
    }
    else if (chardata == ' ')
    {
        led7_var.bShowBuff[led7_var.bCoordinateX++] = 0;
    }
    else //if (chardata == '-')     //Â²Â»Â¿Ã‰ÃÃ”ÃŠÂ¾
    {
        led7_var.bShowBuff[led7_var.bCoordinateX++] = BIT(6);
    }
}

/*----------------------------------------------------------------------------*/
/**@brief   led7_drv Ã—Ã–Â·Ã»Â´Â®ÃÃ”ÃŠÂ¾ÂºÂ¯ÃŠÃ½
   @param   *strÂ£ÂºÃ—Ã–Â·Ã»Â´Â®ÂµÃ„Ã–Â¸Ã•Ã«   offsetÂ£ÂºÃÃ”ÃŠÂ¾Ã†Â«Ã’Ã†ÃÂ¿
   @return  void
   @author  Change.tsai
   @note    void led7_show_string(u8 *str)
*/
/*----------------------------------------------------------------------------*/
void led7_show_string(u8 *str)
{
    while (0 != *str)
    {
        led7_show_char(*str++);
    }
}

/*----------------------------------------------------------------------------*/
/**@brief   MusicÃ„Â£ÃŠÂ½ Ã‰Ã¨Â±Â¸ÃÃ”ÃŠÂ¾
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_show_dev(void)
*/
/*----------------------------------------------------------------------------*/
void led7_show_dev(void)
{
//    /*Music Device type*/

    if((music_ui.ui_curr_device == SD0_DEVICE)||(music_ui.ui_curr_device == SD1_DEVICE))
    {
        LED_STATUS |= LED_SD;
        LED_STATUS&= ~LED_USB;
	#if LED_8NUMS==8
   	  led7_setX(4);	
	led7_show_string((u8 *)" Sd ");
	#endif

		
    }
    else if(music_ui.ui_curr_device == USB_DEVICE)
    {
        LED_STATUS |= LED_USB;
        LED_STATUS &= ~LED_SD;
	#if LED_8NUMS==8
 	    led7_setX(4);		
	led7_show_string((u8 *)" USb");	
	#endif
		
	}
}
#ifdef LED_SHOW_DEVICE_TYPE_SWITCH
void led7_show_device_switch()
{
if((music_ui.ui_curr_device == SD0_DEVICE)||(music_ui.ui_curr_device == SD1_DEVICE))
{
	LED_STATUS |= LED_USB;
	#if LED_8NUMS==5
	led7_show_string((u8 *)" USb ");
	#elif LED_8NUMS==7
	led7_show_string((u8 *)"USb    ");
	#elif LED_8NUMS==8
	led7_show_string((u8 *)" USb");	
	#else
	led7_show_string((u8 *)" USb");
	#endif
}
else if(music_ui.ui_curr_device == USB_DEVICE)
{
	LED_STATUS |= LED_SD;
    #if LED_8NUMS==5
	led7_show_string((u8 *)"  Sd ");
    #elif LED_8NUMS==7
	led7_show_string((u8 *)"Sd     ");
	#elif LED_8NUMS==8	
	led7_show_string((u8 *)" Sd ");
    #else
	led7_show_string((u8 *)" Sd ");
	#endif
}
}
#endif

#ifdef LED_SHOW_DEVICE_PLUGIN
void led7_show_plugin_dev(void)
{
    if(led7_var.dwDeviceID==usb ||led7_var.blast_play_device==2)
    {
        LED_STATUS |= LED_USB;
		led7_show_string((u8 *)device_string[0]);
    }
    else if(led7_var.dwDeviceID==sd0 ||led7_var.blast_play_device==1)
    {
        LED_STATUS |= LED_SD;
		led7_show_string((u8 *)device_string[1]);
    }
}
#endif

#ifdef support_menu_mode
void LED7_SHOW_VOL_MENU(void)
{
  u8 temp;
  switch(menumode){    
         #ifdef Support_MSG_MIC_ECO_VOL_KEY
		  case	MENU_OK_VOL_MODE:
		      #if LED_8NUMS==5
			  led7_show_string((u8 *)" N ");			  
		      #else
			  led7_show_string((u8 *)" N");
			  #endif
			  itoa2(M62429Data[0]);
			  led7_show_string((u8 *)bcd_number);
			  break;  
		  case	MENU_ECHO_MODE:		  
              #if LED_8NUMS==5
			  led7_show_string((u8 *)" E ");
              #else
			  led7_show_string((u8 *)" E");
			  #endif
			  itoa2(M62429Data[1]);
			  led7_show_string((u8 *)bcd_number);
			  break;
         #endif
		 
         #ifdef SUPPORT_MAIN_VOL_KEY
		 case  MENU_MAIN_VOL_MODE:
             #if LED_8NUMS==5
			 led7_show_string((u8 *)" V ");
	      #elif LED_8NUMS==7
			 led7_show_string((u8 *)"VOL ");			 
             #else
			 led7_show_string((u8 *)" V");
		 #endif
		 #if AudVOLMAX>=100
			 itoa3(pt2313data[PT_VOLUME]);		 
		 #else
			 itoa2(pt2313data[PT_VOLUME]);
		 #endif
			 led7_show_string((u8 *)bcd_number);
		 break;
		 #endif
        #ifdef SUPPORT_MSG_FRONT_LEFT
		 case  MENU_FRONT_LEFT_MODE:
            #if LED_8NUMS==5
			led7_show_string((u8 *)" FL");
            #else
			 led7_show_string((u8 *)"FL");
			#endif
			 itoa2(pt2313data[PT_FL]);
			 led7_show_string((u8 *)bcd_number);
		 break;
        #endif
        #ifdef SUPPORT_MSG_FRONT_RIGHT
		 case  MENU_FRONT_RIGHT_MODE:
             #if LED_8NUMS==5
			 led7_show_string((u8 *)" Fr");
             #else
			 led7_show_string((u8 *)"Fr");
			 #endif
			 itoa2(pt2313data[PT_FR]);
			 led7_show_string((u8 *)bcd_number);
		 break;
       #endif
         #ifdef Support_MSG_SWVOL
		 case  MENU_SWVOLL_MODE:
		    #ifdef LED_SWVOL_SHOW_b		       
	               #if LED_8NUMS==5
	 			    led7_show_string((u8 *)" b ");
	               #else
	 				led7_show_string((u8 *)"b ");
	 		  #endif
		    #else 
	               #if LED_8NUMS==5
	 			     led7_show_string((u8 *)" Sb");
	 	      #elif LED_8NUMS==7
	 			 led7_show_string((u8 *)"SUb ");			 			  				   
	               #else
	 	 			 led7_show_string((u8 *)"Sb");
 	 		  #endif
			#endif

		 #if AudBALMAX>=100
	    		#ifdef pt2313_use_rf_lf_as_sub// 0x0a
				 itoa3(pt2313data[PT_FL]);
	     		#else
				 itoa3(pt2313data[PT_RL]);
	    		#endif
		 #else
	    		#ifdef pt2313_use_rf_lf_as_sub// 0x0a
				 itoa3(pt2313data[PT_FL]);
	     		#else
				 itoa3(pt2313data[PT_RL]);
	    		#endif
		 #endif
			
			 led7_show_string((u8 *)bcd_number);
			 break;
         #endif
         #ifdef Support_MSG_BASS
		 case  MENU_BASS_MODE:
			 temp =pt2313data[PT_BASS];  //PT_BASS		 		 
			 if(temp<MAX_TONE/2)
			 {
				 temp = MAX_TONE/2-temp;
		                 #if LED_8NUMS==5
		 				 led7_show_string((u8 *)" b-");
			 	      #elif LED_8NUMS==7
			 			 led7_show_string((u8 *)"baS -");			 			  						 
		                 #else
		 				 led7_show_string((u8 *)"b-");
		  		 #endif
			 }
			 else
			 {
				 temp = temp-MAX_TONE/2;
				 #if LED_8NUMS==5
				 led7_show_string((u8 *)" b ");
		 	      #elif LED_8NUMS==7
		 			 led7_show_string((u8 *)"baS  ");			 			  				 
				 #else
				 led7_show_string((u8 *)"b ");
				 #endif
			 }	 
        	#ifdef supper_bass_treble_max_28
				 temp*=2;
          	#endif
          	itoa2(temp);
			led7_show_string((u8 *)bcd_number);		 
			 break;
        #endif
        #ifdef Support_MSG_TREBLE
		case  MENU_TREBLE_MODE:		
			temp =pt2313data[PT_TREB];
			if(temp<MAX_TONE/2)
			{
				temp = MAX_TONE/2-temp;
				#ifdef LED_TREBLE_SHOW_H
				    #if LED_8NUMS==5
	  				led7_show_string((u8 *)" H-");
		 	      #elif LED_8NUMS==7
		 			 led7_show_string((u8 *)"trb -");			 			  				 
				    #else
	  				led7_show_string((u8 *)"H-");
	  				#endif
				#else
				    #if LED_8NUMS==5
					led7_show_string((u8 *)" t-");
		 	      #elif LED_8NUMS==7
		 			 led7_show_string((u8 *)"trb -");			 			  				 					
				    #else
					led7_show_string((u8 *)"t-");
					#endif
				#endif
			}
			else
			{
				temp = temp-MAX_TONE/2;
               #ifdef LED_TREBLE_SHOW_H
                   #if LED_8NUMS==5
				   led7_show_string((u8 *)" H ");
	 	      #elif LED_8NUMS==7
	 			 led7_show_string((u8 *)"trb  ");					   
                   #else
				   led7_show_string((u8 *)"H ");
				   #endif
               #else
                  #if LED_8NUMS==5
					led7_show_string((u8 *)" t ");
	 	      #elif LED_8NUMS==7
	 			 led7_show_string((u8 *)"trb  ");					  
                  #else
					led7_show_string((u8 *)"t ");
				  #endif
			   #endif
			}	
     		#ifdef supper_bass_treble_max_28
					temp*=2;
    		#endif
    		itoa2(temp);
    		led7_show_string((u8 *)bcd_number); 	 
			break;
        #endif
  }
}
#endif

#ifdef Support_MSG_RESET  
void LED7_SHOW_RESET(void)
{   
    #if LED_8NUMS==5
	led7_show_string((u8 *)"rESEt"); 	 
    #else
    led7_show_string((u8 *)"rESt");		
    #endif
}
#endif

#ifdef SUPPORT_MIC_LED_SHOW_ONOFF
void led7_show_led_mic_onoff(void)
{   
    if(g_kok_var.bKokKeyOpenFlag)
	led7_show_string((u8 *)"OPEN"); 	
	else
    led7_show_string((u8 *)" OFF");	
}
#endif

#ifdef LED_SHOW_ONOFF
void LED7_SHOW_LED_ONOFF(void)
{   
  #ifdef LED_ONOFF_CONTROL_WITH_KEY
	    if(bRgbMode)
		led7_show_string((u8 *)" On "); 	
		else
	    led7_show_string((u8 *)" OFF");	
		
  #elif defined(SUPPORT_ZY_SA_VOICE)   
	 #ifdef LED_SHOW_VOICE_C_ONOFF  
	 	   if(led7_var.bIfHaveVoice==0)
	 		   led7_show_string((u8 *)"COFF");	  
	 	   else
	 		   led7_show_string((u8 *)"C-ON"); 	
	 #else
	 	   if(led7_var.bIfHaveVoice==1)
	 		   led7_show_string((u8 *)" CH ");	  
	 	   else if(led7_var.bIfHaveVoice==2)
	 		   led7_show_string((u8 *)" EN "); 
	 	   else
	 		   led7_show_string((u8 *)" OFF "); 	
	 #endif
  #elif defined(SUPPORT_VOICE_ONOFF)   
  
	   #if LED_8NUMS==5
		   if(led7_var.bIfHaveVoice)
		   led7_show_string((u8 *)" On  ");	  
		   else
		   led7_show_string((u8 *)" OFF "); 
	   #elif LED_8NUMS==7
		   if(led7_var.bIfHaveVoice)
		   led7_show_string((u8 *)"   ON  "); 	   
		   else
		   led7_show_string((u8 *)"  OFF  "); 	   
	   #else
		   if(led7_var.bIfHaveVoice)
		   led7_show_string((u8 *)" On ");	  
		   else
		   led7_show_string((u8 *)" OFF"); 
	   #endif
	   
  #endif
}
#endif
/*----------------------------------------------------------------------------*/
/** @brief:
    @param:
    @return:
    @author:
    @note:
*/
/*----------------------------------------------------------------------------*/
void led7_show_string_menu(u8 menu)
{

#ifdef support_bt_waiting_conn_filsh_led 
     if(menu==2 )
     {
#if LED_BT>0 && !defined(LED_FLASH_BT_ICON_USE_LIGHTS)
         if( (BT_STATUS_INITING == bt_line_mode||BT_STATUS_WAITINT_CONN == bt_line_mode)) 
	      led7_var.bFlashIcon |= LED_BT;
	       else 
             led7_var.bFlashIcon = 0;
#else
         if( (BT_STATUS_INITING == bt_line_mode||BT_STATUS_WAITINT_CONN == bt_line_mode)) 
     	 led7_var.bFlashChar |= 0xF;
         else 
              led7_var.bFlashChar = 0x0;
#endif 	 
     }
#endif     

#ifdef LED_AUX
#ifndef support_only_use_bt_mp3
   if(menu==MENU_AUX_MAIN)
	 LED_STATUS |= LED_AUX;
#endif
#endif 


#if LED_DVD
if(menu==MENU_AUX_MAIN)
  LED_STATUS |= LED_DVD;
#endif
#if LED_BT>0 && !defined(LED_FLASH_BT_ICON_USE_LIGHTS)
   if(menu==MENU_BT_MAIN)
	 LED_STATUS |= LED_BT;
#endif 




#if 0//def support_stanby_mod
      if(workmode==STANBY_WORK_MODE && menu==MENU_WAIT)
      {
      led7_show_string((u8 *)"    ");
      }
     else 
#endif 

#ifdef SUPPORT_LOD_STATE_ALL_ICON_OFF
   if(menu==MENU_WAIT)
	 LED_STATUS = 0;
#endif

#if REC_EN

    LED_STATUS &= ~(LED_PLAY | LED_PAUSE);
    LED_STATUS &= ~(LED_SD|LED_USB);
	LED_STATUS &=~LED_RECO;
	 #ifdef LED_2POINT1	
	 	LED_STATUS &=~(LED_2POINT|LED_2POINT1);
	 #else
	 	LED_STATUS &=~(LED_2POINT);
	 #endif
	#if LED_8NUMS==8
	   LED_STATUS  &=~(LED_2POINT2);
	#endif
	
#ifdef SUPPORT_AC3_MODE_IN_LINEIN_MODE	,
    if((menu == MENU_AUX_MAIN)||(menu == MENU_AC3_MAIN)||(menu == MENU_BT_MAIN))
#else	
    if((menu == MENU_AUX_MAIN)||(menu == MENU_BT_MAIN))
#endif		
    {
        if((g_rec_ctl)&&(ENC_STOP != g_rec_ctl->enable))
        {
            if (ENC_STAR == g_rec_ctl->enable)
                LED_STATUS |= LED_PLAY;
            else if(ENC_PAUS == g_rec_ctl->enable)
                LED_STATUS |= LED_PAUSE;
                LED_STATUS|=LED_RECO;

		#if LED_8NUMS==8
	 	    led7_setX(4);		
		#else
		    led7_show_dev();		
		#endif
				

       #ifdef SUPPORT_AUX_FM_BT_SHOW_REC_TIME

	 	#if LED_8NUMS==8
	 	   LED_STATUS |=(LED_2POINT2);
	       #else
	 		 #ifdef LED_2POINT1	
	 		 	   LED_STATUS |=(LED_2POINT|LED_2POINT1);
	 		 #else
	 		 	   LED_STATUS |=(LED_2POINT);
	 		 #endif
	 	  
	 	#endif
	   

	 #if LED_8NUMS==5
	 	   itoa1((u16)dwAuxFmBtRecordTimeCnt/3600);
	 	   led7_show_string((u8 *)bcd_number);		  
	 	   itoa2((u16)dwAuxFmBtRecordTimeCnt%3600/60);
	 	   led7_show_string((u8 *)bcd_number);
	 #else
	 	   itoa2((u16)dwAuxFmBtRecordTimeCnt/60);
	 	   led7_show_string((u8 *)bcd_number);
	 #endif	   
	   itoa2((u16)dwAuxFmBtRecordTimeCnt%60);
	   led7_show_string((u8 *)bcd_number);
       #endif
        }
        else
#ifdef TEST_IR_CODE_MACHINE
	  if(menu == MENU_AUX_MAIN)
    	{
    		if(ir_sys_sw)
		{
		    itoa4(ir_code_data);
		    led7_show_string((u8 *)bcd_number);    	
		}
		else
		{
		    itoa4(sys_code);
		    led7_show_string((u8 *)bcd_number);    	
		}
    	
		if(!ir_sys_sw)
		 {
			 if(((sys_code & 0xf000)>>12)<=9)
			 	  led7_var.bShowBuff[0]=LED_NUMBER[(u8)((sys_code & 0xf000)>>12)]; //b
			 else 
			 	  led7_var.bShowBuff[0]=LED_LARGE_LETTER[(u8)(((sys_code & 0xf000)>>12)-10)]; //b
			 	 
			 if(((sys_code & 0x0f00)>>8)<=9)
			 	  led7_var.bShowBuff[1]=LED_NUMBER[(u8)((sys_code & 0x0f00)>>8)]; //b
			 else 
			 	  led7_var.bShowBuff[1]=LED_LARGE_LETTER[(u8)(((sys_code & 0x0f00)>>8)-10)]; //b		 	 

			 if(((sys_code & 0x00f0)>>4)<=9)
			 	  led7_var.bShowBuff[2]=LED_NUMBER[(u8)((sys_code & 0x00f0)>>4)]; //b
			 else 
			 	  led7_var.bShowBuff[2]=LED_LARGE_LETTER[(u8)(((sys_code & 0x00f0)>>4)-10)]; //b		
			 	 
			 if((sys_code & 0x000f)<=9)
			 	  led7_var.bShowBuff[3]=LED_NUMBER[(u8)(sys_code & 0x000f)]; //b
			 else 
			 	  led7_var.bShowBuff[3]=LED_LARGE_LETTER[(u8)((sys_code & 0x000f)-10)]; //b				 	 
		 }
		 else
		 {
			 if(((ir_code_data & 0xf000)>>12)<=9)
			 	  led7_var.bShowBuff[0]=LED_NUMBER[(u8)((ir_code_data & 0xf000)>>12)]; //b
			 else 
			 	  led7_var.bShowBuff[0]=LED_LARGE_LETTER[(u8)(((ir_code_data & 0xf000)>>12)-10)]; //b
			 	 
			 if(((ir_code_data & 0x0f00)>>8)<=9)
			 	  led7_var.bShowBuff[1]=LED_NUMBER[(u8)((ir_code_data & 0x0f00)>>8)]; //b
			 else 
			 	  led7_var.bShowBuff[1]=LED_LARGE_LETTER[(u8)(((ir_code_data & 0x0f00)>>8)-10)]; //b		 	 

			 if(((ir_code_data & 0x00f0)>>4)<=9)
			 	  led7_var.bShowBuff[2]=LED_NUMBER[(u8)((ir_code_data & 0x00f0)>>4)]; //b
			 else 
			 	  led7_var.bShowBuff[2]=LED_LARGE_LETTER[(u8)(((ir_code_data & 0x00f0)>>4)-10)]; //b		
			 	 
			 if((ir_code_data & 0x000f)<=9)
			 	  led7_var.bShowBuff[3]=LED_NUMBER[(u8)(ir_code_data & 0x000f)]; //b
			 else 
			 	  led7_var.bShowBuff[3]=LED_LARGE_LETTER[(u8)((ir_code_data & 0x000f)-10)]; //b		
			 	 
		 }	
	 
    	}
else	
#endif

#if 0  // test  ZY_6003_MP5_AC4601
	   if( bModeOfAuxContained==mode_ac3)
	 {
//		    itoa2(send_timer);
//		    led7_show_string((u8 *)bcd_number);    	
		    itoa4(send_end);
		    led7_show_string((u8 *)bcd_number);    	
	 }
	 else
	 	
#endif	 	

	{
  	 #ifdef LED_ID_KF8426GH
  	 	 LED_STATUS = 0;			
  	 #endif
	#if LED_8NUMS==8
 	    led7_setX(4);			 
          led7_show_string((u8 *)menu_string[menu]);    
	#else
          led7_show_string((u8 *)menu_string[menu]);    	
 	#endif
         dwAuxFmBtRecordTimeCnt=0; 
        }
    }

	else
	{
	    led7_show_string((u8 *)menu_string[menu]);
	}
#else
#ifdef support_aux_freq
	  if(menu != MENU_AUX_MAIN)
#endif
    led7_show_string((u8 *)menu_string[menu]);
#endif
       
}

#ifdef LED_SHOW_POWER_OFF_STRING
void led7_show_string_standby()
{
#ifdef SUPPORT_POWER_OFF_2POINT_FLASH
	LED_STATUS= LED_2POINT;
	led7_var.wFlashIcon = LED_2POINT;
	led7_show_string((u8 *)"    ");
#else
	 #ifdef POWER_ON_WELCOME_VOICE_PLAYED_IN_IDLE_MODE
	 	if(led7_var.bIfPlayWelcomeVoice)    
	 	led7_show_string((u8 *)" HI ");
	 	else
	 #endif	
	 	led7_show_string((u8 *)LED_SHOW_POWER_OFF_STRING);
#endif
}
#endif

#ifdef LED_SHOW_INTRO_STRING
void led7_show_string_intro(bool ifIntro)
{
    if(ifIntro)
	led7_show_string((u8 *)LED_SHOW_INTRO_STRING);
	else
	#if LED_8NUMS==5
	led7_show_string((u8 *)" Nor ");
  #elif LED_8NUMS==8
    led7_setX(4);
	led7_show_string((u8 *)"Nor ");

	#else
	led7_show_string((u8 *)"Nor ");
	#endif
}
#endif
#ifdef LED_SHOW_PREV_NEXT_FOLDER_SWITCH
void led7_show_prev_next_folder(bool bPrevNext)
{
  #if LED_8NUMS==5
    if(bPrevNext)
    led7_show_string((u8 *)" P--F");
    else
    led7_show_string((u8 *)" N--F");
  #elif LED_8NUMS==8

    led7_setX(4);
	
    if(bPrevNext)
	led7_show_string((u8 *)"P--F");
	else
	led7_show_string((u8 *)"N--F");
	
#else

    if(bPrevNext)
	led7_show_string((u8 *)"P--F");
	else
	led7_show_string((u8 *)"N--F");
  #endif
}
#endif
#ifdef LED_SHOW_REPEAT_ALL_ONE_FOLDER_NORMAL
void led7_show_user_repeat_mode(u8 repeat_mode)
{
    u8 *str=NULL;
    switch(repeat_mode){
      case rpt_normal:
      str="Nor ";
      break;
      case rpt_all:
      str="ALL ";
      break;
      case rpt_one:
      str="ONE ";
      break;
      case rpt_folder:
      str="FOLd";
      break;
      case rpt_random:
      str="rAnd";
      break;
      default:
      break;
    }
	led7_show_string((u8 *)str);
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief   Music Â²Â¥Â·Ã…ÃŽÃ„Â¼Ã¾ÂºÃ…ÃÃ”ÃŠÂ¾ÂºÂ¯ÃŠÃ½
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_show_filenumber(void)
*/
/*----------------------------------------------------------------------------*/
void led7_show_filenumber(void)
{
    /*Music File Number info*/
    //printf("ui_music.ui_play_file_num = %u----\n",ui_music.ui_play_file_num);

#ifdef LED_SHOW_DEL_MODIFY
      #ifdef SUPPORT_LED_SHOW_DEL			  
      if(bLedShowDelCnt>0)
           {     
		 #if LED_8NUMS==7         
		 	led7_show_string((u8 *)"   dELE");

		#elif LED_8NUMS==8
		    led7_setX(4);
		 	led7_show_string((u8 *)"dELE");		
		 #else
		 	led7_show_string((u8 *)"dELE");		 
		 #endif
            }
      else
      #endif
#endif

{

#ifdef LED_FILE_NUM_NOT_SHOW_PREVIOUS_ZERO

    #if LED_8NUMS==5
    if(music_ui.ui_curr_file<10){
       led7_show_string((u8 *)"    ");
	   led7_show_char(asc_number[music_ui.ui_curr_file]);       
	}else
    if(music_ui.ui_curr_file<100){
   	   itoa2(music_ui.ui_curr_file);	
       led7_show_string((u8 *)"   ");
	   led7_show_string((u8 *)bcd_number);
	}else
	if(music_ui.ui_curr_file<1000){
	   itoa3(music_ui.ui_curr_file);	
       led7_show_string((u8 *)"  ");
	   led7_show_string((u8 *)bcd_number);
	}else
    #else
    if(music_ui.ui_curr_file<10){
       led7_show_string((u8 *)"   ");
	   led7_show_char(asc_number[music_ui.ui_curr_file]);       
	}else
    if(music_ui.ui_curr_file<100){
   	   itoa2(music_ui.ui_curr_file);	
       led7_show_string((u8 *)"  ");
	   led7_show_string((u8 *)bcd_number);
	}else
	if(music_ui.ui_curr_file<1000){
	   itoa3(music_ui.ui_curr_file);	
	   led7_show_char(' ');
	   led7_show_string((u8 *)bcd_number);
	}else
	#endif
    #endif
    {
    #if LED_8NUMS==5
	led7_show_char('0');
	#elif LED_8NUMS==7
	led7_show_string((u8 *)"   ");
    #endif
    itoa4(music_ui.ui_curr_file);
    led7_show_string((u8 *)bcd_number);
    }
}	
    led7_show_dev();
}


/*----------------------------------------------------------------------------*/
/**@brief   ÂºÃ¬ÃÃ¢ÃŠÃ¤ÃˆÃ«ÃŽÃ„Â¼Ã¾ÂºÃ…ÃÃ”ÃŠÂ¾ÂºÂ¯ÃŠÃ½
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_show_IR_number(void)
*/
/*----------------------------------------------------------------------------*/
void led7_show_IR_number(void)
{
    /*IR File Number info*/
#ifdef LED_IR_NUM_NOT_SHOW_PREVIOUS_ZERO
  #if LED_8NUMS==5

	if(input_number<10){
  	 led7_show_string((u8 *)"    ");
  	 led7_show_char(asc_number[input_number]);
    }else
    if(input_number<100){
  	 itoa2(input_number); 
  	 led7_show_string((u8 *)"   ");
  	 led7_show_string((u8 *)bcd_number);
    }else
    if(input_number<1000){
  	 itoa3(input_number); 
	 led7_show_string((u8 *)"  ");
  	 led7_show_string((u8 *)bcd_number);
    }else
  #elif LED_8NUMS==7

	if(input_number<10){
  	 led7_show_string((u8 *)"      ");
  	 led7_show_char(asc_number[input_number]);
    }else
    if(input_number<100){
  	 itoa2(input_number); 
  	 led7_show_string((u8 *)"     ");
  	 led7_show_string((u8 *)bcd_number);
    }else
    if(input_number<1000){
  	 itoa3(input_number); 
	 led7_show_string((u8 *)"    ");
  	 led7_show_string((u8 *)bcd_number);
    }else
    
  #else
    if(input_number<10){
       led7_show_string((u8 *)"   ");
	   led7_show_char(asc_number[input_number]);
	}else
    if(input_number<100){
   	   itoa2(input_number);	
       led7_show_string((u8 *)"  ");
	   led7_show_string((u8 *)bcd_number);
	}else
	if(input_number<1000){
	   itoa3(input_number);	
	   led7_show_char(' ');
	   led7_show_string((u8 *)bcd_number);
	}else
  #endif	
  
#elif defined(SUPPORT_IR_INPUT_2_3NUMS)
   if(bir_2_nums){
    led7_show_string((u8 *)"  ");
    if(input_number==0)
	 	led7_show_string((u8 *)"--");
	else if(input_number<10){	
	   led7_show_char('-');
       led7_show_char(asc_number[input_number]);
      }
      else if(input_number<100){
       itoa2(input_number);
	   led7_show_string((u8 *)bcd_number);
      }       
   }
   else  if(bir_3_nums){   
   led7_show_char(' ');
   if(input_number==0)
	   led7_show_string((u8 *)"---");
    else if(input_number<10){
		led7_show_string((u8 *)"--");
		led7_show_char(asc_number[input_number]);
      }
     else if(input_number<100){
		 led7_show_char('-');
		 itoa2(input_number);
		 led7_show_string((u8 *)bcd_number);		 
      }
      else if(input_number<1000){
		  itoa3(input_number);
		  led7_show_string((u8 *)bcd_number);		  
        }
    
   }else
#endif    
    {    
   #if LED_8NUMS==5
   	led7_show_char('0');
   #elif LED_8NUMS==7
    led7_show_string((u8 *)"   ");
   #endif
    itoa4(input_number);
    led7_show_string((u8 *)bcd_number);
    }
}

/*----------------------------------------------------------------------------*/
/**@brief   MusicÃ„Â£ÃŠÂ½ ÃÃ”ÃŠÂ¾Â½Ã§ÃƒÃ¦
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_show_music_main(void)
*/
/*----------------------------------------------------------------------------*/
extern bool music_prompt_stopped;

extern u32 get_decode_time(void);
void led7_show_music_main(void)
{
    //led7_show_string((u8*)"MUSI");
    u16 play_time;

    /*Music Play time info*/
    play_time = get_decode_time();

if(!music_prompt_stopped)	
	return;

#ifdef support_led_disp_pause
#ifdef support_music_pp_state
   if (bPause_state == 1)
#else
   if (*music_ui.ui_curr_statu == DECODER_PAUSE)
#endif
     {     
   #if LED_8NUMS==5
     led7_show_string((u8 *)"PAUSE");
   #elif LED_8NUMS==7
     led7_show_string((u8 *)" PAUSE ");
   #else
   
   
     led7_show_string((u8 *)"PAUS")	;
   #endif
     LED_STATUS |= LED_MP3;
     LED_STATUS &=~ LED_2POINT;

      }
   else 
#endif 
{
#if 0
//itoa5( get_dac_energy_value());
//itoa4(get_battery_value());
//  itoa4(adc_value[AD_CH_EQ]);
//itoa4(adc_value[AD_CH_EQ]);
itoa4(kok_is_online());

#if LED_8NUMS==5
	led7_show_char('0');
#endif
 // itoa4(led7_var.wEqADC_Value);
//  itoa4(led7_var.dwDeviceID);
//itoa4(music_judge_JL_REC_folder());
led7_show_string((u8 *)bcd_number);
#else



    #if LED_8NUMS==5
    led7_show_char('0');
		 #ifdef LED_2POINT1	
		 	   LED_STATUS |=(LED_2POINT1);
		 #endif
    #elif LED_8NUMS==7  //show cur file num
    itoa3(music_ui.ui_curr_file%1000);
    led7_show_string((u8 *)bcd_number);
    #endif
	
    itoa2(play_time/60);
    led7_show_string((u8 *)bcd_number);
	
    itoa2(play_time%60);
    led7_show_string((u8 *)bcd_number);
#endif
#ifdef LED_ID_SD40C18SRB
    LED_STATUS |= LED_2POINT1;
#endif
    LED_STATUS |= LED_2POINT | LED_MP3;
}

    led7_show_dev();


#ifdef support_music_pp_state
   if (bPause_state == 0)
#else
    if (*music_ui.ui_curr_statu == DECODER_PLAY)
#endif
    {
        LED_STATUS |= LED_PLAY;
        LED_STATUS &= ~LED_PAUSE;
        #ifndef LED_2POINT_NOT_FLASH
        led7_var.wFlashIcon |= LED_2POINT;
	 #ifdef LED_ID_SD40C18SRB
	     led7_var.wFlashIcon |= LED_2POINT1;
	 #endif		
        #endif
        #if 	defined(LED_ID_JW2781)
		led7_var.bEqCircleIfPlay=TRUE;
	#endif		
    }
#ifdef support_music_pp_state
  else if (bPause_state == 1)
#else
    else if (*music_ui.ui_curr_statu == DECODER_PAUSE)
#endif
	
    {
        LED_STATUS &= ~LED_PLAY;
        LED_STATUS |= LED_PAUSE;

	  LED_STATUS &=~ LED_2POINT;		
       #if 	   defined(LED_ID_JW2781)
		led7_var.bEqCircleIfPlay=FALSE;
       #endif	  
    }

//
//    if(mute)
//    {
//        led7_var.bFlashIcon |= LED_MP3;
//        led7_var.bFlashChar = 0x0f;
//    }
//    else
//    {
//        led7_var.bFlashIcon &= ~LED_MP3;
//        led7_var.bFlashChar = 0x00;
//    }
}


#if defined(support_line_pause )||defined(LED_SHOW_MP3_PAUSE)
void led7_show_AUX_PAUSE(void)
 {
 
     #if LED_8NUMS==5
     led7_show_string((u8 *)"PAUSE");
     #elif LED_8NUMS==7
     led7_show_string((u8 *)"PAUSE  ");
	#elif LED_8NUMS==8
	     led7_setX(4);
   	 led7_show_string((u8 *)"PAUS")	;	 
     #else
     led7_show_string((u8 *)"PAUS")	;
     #endif
	 
      #if LED_PAUSE
      LED_STATUS|=LED_PAUSE;
      #else
      //LED_STATUS=0;
      #endif

      LED_STATUS &=~ LED_2POINT;
#ifdef LED_2POINT1
	    LED_STATUS &=~ LED_2POINT1;
#endif


  }
#endif
#ifdef SUPPORT_MUSIC_STOP
void led7_show_stop(void)
{
    #if LED_8NUMS==5
	led7_show_string((u8 *)" STOP");
	#elif LED_8NUMS==7
	led7_show_string((u8 *)"STOP   ");
	#elif LED_8NUMS==8
	     led7_setX(4);

	led7_show_string((u8 *)"STOP");
	
    #else
	led7_show_string((u8 *)"STOP");
	#endif
	
	 LED_STATUS=0;
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief   EQÃÃ”ÃŠÂ¾ÂºÂ¯ÃŠÃ½
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_show_volume(void)
*/
/*----------------------------------------------------------------------------*/
//extern u8 eq_mode;
void led7_show_eq(void)
{

#ifdef LED_SHOW_EQ_WITH_NAME
   u8 *str=NULL,mode=0;      

    #ifdef support_bt_mode_eq_adjust_icon_play_off
    	if(workmode==BT_WORK_MODE)
    		LED_STATUS =0;
    #endif
#ifdef LED_SHOW_BT_EQ
   if(compare_task_name("BtStackTask"))
    mode= led7_var.bBtEqMode;
   else
#endif   	
	mode=eq_mode;
   #if LED_8NUMS==5
   switch(mode){
     case 0:
		str=" NOr ";
		break;
	case 1:
		str=" rOC ";
		break;
	case 2:
		str=" POP ";
		break;
	case 3:
		str=" CLA ";
		break;
	case 4:
		str=" JAZ ";
		break;
	case 5:
		str=" COU ";
		break;
	case 6:
		str=" bAS ";
		break;
	default:
	    break;
   }
   #elif LED_8NUMS==7
   switch(mode){
     case 0:
		str="NOr    ";
		break;
	case 1:
		str="rOC    ";
		break;
	case 2:
		str="POP    ";
		break;
	case 3:
		str="CLA    ";
		break;
	case 4:
		str="JAZ    ";
		break;
	case 5:
		str="COU    ";
		break;
	case 6:
		str="bAS    ";
		break;
	default:
	    break;
   }
   #else

	#ifdef  SUPPORT_ZY_SA_VOICE
	   switch(mode)
	   	{
		     case 0:
				str=" NOr";
				break;
			case 1:
				str=" rOC";
				break;
			case 2:
				str=" POP";
				break;
			case 3:
				str=" CLA";
				break;
			case 4:
				str=" JAZ";
				break;
			case 5:
				str=" SOF";
				break;
			default:
			    break;
	   }	
	#else
	   switch(mode)
	   	{
		     case 0:
				str=" NOr";
				break;
			case 1:
				str=" rOC";
				break;
			case 2:
				str=" POP";
				break;
			case 3:
				str=" CLA";
				break;
			case 4:
				str=" JAZ";
				break;
			case 5:
				str=" COU";
				break;
			case 6:
				str=" bAS";
				break;
			default:
			    break;
	   }
   	#endif
   
   #endif
   
   led7_show_string((u8 *)str);
#else

 #ifdef LED_EQ_SHOW_ONLY_TWO_CHAR_EX_AT_MIDDLE
    led7_show_string((u8 *)" E");
    led7_show_char(eq_mode%10 + '0');    
    led7_show_char(' ');
 #else

  #if LED_8NUMS==8
     led7_setX(4);
  #endif
  
    led7_show_string((u8 *)other_string[0]);    
   #ifdef LED_SHOW_BT_EQ
    if(compare_task_name("BtStackTask"))
		led7_show_char(led7_var.bBtEqMode%10 + '0');
		else
   #endif
	   #ifdef support_music_eq_show_1to6
	     led7_show_char(eq_mode%10 + '1');	 
	   #else
	     led7_show_char(eq_mode%10 + '0');
	   #endif
 #endif
#endif
}


/*----------------------------------------------------------------------------*/
/**@brief   Ã‘Â­Â»Â·Ã„Â£ÃŠÂ½ÃÃ”ÃŠÂ¾ÂºÂ¯ÃŠÃ½
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_show_volume(void)
*/
/*----------------------------------------------------------------------------*/
//extern u8 play_mode;
void led7_show_playmode(void)
{
    led7_show_string((u8 *)&playmodestr[play_mode-FOP_MAX-1][0]);
}

/*----------------------------------------------------------------------------*/
/**@brief   Ã’Ã´ÃÂ¿ÃÃ”ÃŠÂ¾ÂºÂ¯ÃŠÃ½
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_show_volume(void)
*/

/*----------------------------------------------------------------------------*/
void led7_show_volume(void)
{

    #ifdef support_vol_adjust_icon_play_off
    	if(workmode==BT_WORK_MODE)
    		LED_STATUS =0;
    #endif

    #if LED_8NUMS==8
	led7_setX(4);
     #endif	

    led7_show_string((u8 *)other_string[1]);
    #if LED_SHOW_VOL_MAX    
     #if MP3_VOL_MAX
 	 if(compare_task_name("MusicTask"))
		itoa2(bVolMaxChangeToSmallVolMax);
	 else
		itoa2(dac_var.cur_sys_vol_l);
 	 #else
       itoa2(bVolMaxChangeToSmallVolMax);
    #endif
    #else
    itoa2(dac_var.cur_sys_vol_l);
    #endif

    led7_show_string((u8 *)bcd_number);
}

/*----------------------------------------------------------------------------*/
/**@brief   FM Ã„Â£ÃŠÂ½Ã–Ã·Â½Ã§ÃƒÃ¦
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_show_fm_main(void)
*/
/*----------------------------------------------------------------------------*/
void led7_show_fm_main(void)
{

#if FM_RADIO_EN

#if !REC_EN
    /*FM - Frequency*/
    #if LED_8NUMS==5
        led7_show_char(' ');  
    #elif LED_8NUMS==7
	led7_show_char('p');  
    itoa2(fm_mode_var->wFreChannel%100);
    led7_show_string((u8 *)bcd_number);	
    #endif
    itoa4(fm_mode_var->wFreq);
    if (fm_mode_var->wFreq <= 999)
        bcd_number[0] = ' ';
    led7_show_string((u8 *)bcd_number);
    LED_STATUS |= LED_FM|LED_DOT;	
#endif

#if REC_EN
    LED_STATUS &= ~(LED_PLAY | LED_PAUSE);
    LED_STATUS &= ~(LED_SD|LED_USB);
	LED_STATUS &=~LED_RECO;
	LED_STATUS &=~(LED_FM|LED_DOT);
	 #ifdef LED_2POINT1	
	 	LED_STATUS&=~(LED_2POINT|LED_2POINT1);
	 #else
	 	LED_STATUS &=~(LED_2POINT);
	 #endif
	
    if((g_rec_ctl)&&(ENC_STOP != g_rec_ctl->enable))
    {
	      #if LED_8NUMS!=8    
		        led7_show_dev();
		  #endif
		  
        if (ENC_STAR == g_rec_ctl->enable)
            LED_STATUS |= LED_PLAY;
        else if(ENC_PAUS == g_rec_ctl->enable)
            LED_STATUS |= LED_PAUSE;
            LED_STATUS|=LED_RECO;         
        #ifdef SUPPORT_AUX_FM_BT_SHOW_REC_TIME        
	 #ifdef LED_2POINT1	
		  LED_STATUS |=(LED_2POINT|LED_2POINT1);
	 #else
		  LED_STATUS |=(LED_2POINT);
	 #endif
		
		 #if LED_8NUMS==5
		         itoa1((u16)dwAuxFmBtRecordTimeCnt/3600);
		         led7_show_string((u8 *)bcd_number);        
		         itoa2((u16)dwAuxFmBtRecordTimeCnt%3600/60);
		         led7_show_string((u8 *)bcd_number);
		 #else
		 		  itoa2((u16)dwAuxFmBtRecordTimeCnt/60);
		 		  led7_show_string((u8 *)bcd_number);
		 #endif		  
		  itoa2((u16)dwAuxFmBtRecordTimeCnt%60);
		  led7_show_string((u8 *)bcd_number);
        #endif
	      #if LED_8NUMS==8    
		  if(sys_halfsec)
		  	{
				led7_setX(4);
				led7_show_string((u8 *)"    ");
		  	}
		  else		  	
		        led7_show_dev();
		#endif
		
    }
    else
	    {
	      dwAuxFmBtRecordTimeCnt=0;
		  
	     #if LED_8NUMS==5
		  led7_show_char(' ');	
	     #elif LED_8NUMS==7
		  led7_show_char('P');	
		  itoa2(fm_mode_var->wFreChannel%100);
		  led7_show_string((u8 *)bcd_number);		  	  
	     #endif
		  itoa4(fm_mode_var->wFreq);
		  if (fm_mode_var->wFreq <= 999)
			  bcd_number[0] = ' ';
		  led7_show_string((u8 *)bcd_number);
		  
	      #if LED_8NUMS==8
 		led7_setX(4);
 		led7_show_string((u8 *)"P ");
 		itoa2(fm_mode_var->wFreChannel%100);
 		led7_show_string((u8 *)bcd_number);	
		#endif
		
		  LED_STATUS |= LED_FM|LED_DOT;   
	    }
		
#endif
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief   FM Ã„Â£ÃŠÂ½Ã–Ã·Â½Ã§ÃƒÃ¦
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_show_fm_main(void)
*/
/*----------------------------------------------------------------------------*/
void led7_show_fm_station(void)
{
#if FM_RADIO_EN

 #if (LED_8NUMS==7||LED_8NUMS==8||defined SUPPORT_FM_SCAN_STEP_NO_SHOW_STATION)

	led7_show_fm_main();
 
#else

//    /*FM - Station*/
    led7_show_string((u8 *)other_string[2]);
    itoa2(fm_mode_var->wFreChannel);
    led7_show_string((u8 *)bcd_number);

	
    LED_STATUS |= LED_FM;	
#endif

#endif    
}

#if RTC_CLK_EN
/*----------------------------------------------------------------------------*/
/**@brief   RTC ÏÔÊ¾½çÃæ
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_show_RTC_main(void)
*/
/*----------------------------------------------------------------------------*/
void led7_show_RTC_main(void)
{
    itoa2(current_time.bHour);
    led7_show_string((u8 *)bcd_number);
    itoa2(current_time.bMin);
    led7_show_string((u8 *)bcd_number);

    led7_var.wFlashIcon |= LED_2POINT;
    LED_STATUS |= LED_2POINT;

    if(rtc_set.rtc_set_mode == RTC_SET_MODE)
    {
        if(rtc_set.calendar_set.coordinate == COORDINATE_MIN)
            led7_var.bFlashChar = BIT(0)|BIT(1);
        else
            led7_var.bFlashChar = BIT(2)|BIT(3);
    }
    else
        led7_var.bFlashChar = 0;

}

/*----------------------------------------------------------------------------*/
/**@brief   Alarm ÏÔÊ¾½çÃæ
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_show_alarm(void)
*/
/*----------------------------------------------------------------------------*/
#if RTC_ALM_EN
void led7_show_alarm(void)
{
    puts("led7_show_alarm\n");
    itoa2(current_alarm.bHour);
    led7_show_string((u8 *)bcd_number);
    itoa2(current_alarm.bMin);
    led7_show_string((u8 *)bcd_number);

    LED_STATUS |= LED_2POINT;

    if(rtc_set.rtc_set_mode == ALM_SET_MODE)
    {
        if(rtc_set.alarm_set.coordinate == COORDINATE_MIN)
            led7_var.bFlashChar = BIT(0)|BIT(1);
        else
            led7_var.bFlashChar = BIT(2)|BIT(3);
    }

    /*Alarm info - Switch On/Off*/
    if (rtc_set.alarm_set.alarm_sw)
    {
        LED_STATUS |= LED_PLAY;
    }
    else
    {
        LED_STATUS |= LED_PAUSE;
    }
}
#endif
#endif

void music_flash(void)
{
//    led7_var.bFlashIcon |= LED_2POINT | LED_MP3;
//    if (Music_Play_var.bPlayStatus == MAD_PLAY)
//        led7_var.bFlashIcon |= LED_PLAY;
//    else if (Music_Play_var.bPlayStatus == MAD_PAUSE)
//        led7_var.bFlashIcon |= LED_PAUSE;
//    if (device_active == DEVICE_SDMMCA)
//        led7_var.bFlashIcon |= LED_SD;
//    else if (device_active == DEVICE_UDISK)
//        led7_var.bFlashIcon |= LED_USB;
}
#if REC_EN
/*----------------------------------------------------------------------------*/
/**@brief   REC ÏÔÊ¾½çÃæ
   @param   void
   @return  void
   @note    void led7_show_rec_start(void)
*/
/*----------------------------------------------------------------------------*/
void led7_show_rec_start(void)
{
    u32 rec_time;

    //LED_STATUS &= ~(LED_PLAY | LED_PAUSE);
    if(g_rec_ctl)
    {
        rec_time = g_rec_ctl->file_info.enc_time_cnt;
		
        #if LED_8NUMS==5
        itoa1(rec_time/3600);
        led7_show_string((u8 *)bcd_number);        
        itoa2(rec_time%3600/60);
        led7_show_string((u8 *)bcd_number);
	 #ifdef LED_2POINT1	
        LED_STATUS|=LED_2POINT1;
	 #endif

	#elif LED_8NUMS==7
	    led7_show_string((u8 *)"rec");
        itoa2(rec_time/60);
        led7_show_string((u8 *)bcd_number);	
        #else
        itoa2(rec_time/60);
        led7_show_string((u8 *)bcd_number);
        #endif
		
        itoa2(rec_time%60);
        led7_show_string((u8 *)bcd_number);
		
      #if LED_8NUMS==8    
	  if(sys_halfsec)
	  	{
			led7_setX(4);
			led7_show_string((u8 *)"    ");
	  	}
	  else		  	
	#endif

        led7_show_dev();

        LED_STATUS |= LED_2POINT; //| LED_PLAY;
#ifdef LED_2POINT1
	    LED_STATUS |= LED_2POINT1;
#endif

#ifdef support_rec_media_icon_flash
    if((music_ui.ui_curr_device == SD0_DEVICE)||(music_ui.ui_curr_device == SD1_DEVICE))
    {
	  led7_var.wFlashIcon |= LED_SD;    
        LED_STATUS&= ~LED_USB;
		
    }
    else if(music_ui.ui_curr_device == USB_DEVICE)
    {
	  led7_var.wFlashIcon |= LED_USB;    		
         LED_STATUS &= ~LED_SD;
	}
#endif

        if (ENC_STAR == g_rec_ctl->enable)
            LED_STATUS |= LED_PLAY;
        else if (ENC_PAUS == g_rec_ctl->enable)
            LED_STATUS |= LED_PAUSE;
    }
}

/*----------------------------------------------------------------------------*/
/**@brief   REC ÏÔÊ¾½çÃæ
   @param   void
   @return  void
   @note    void led7_show_rec_main(void)
*/
/*----------------------------------------------------------------------------*/
void led7_show_rec_main(void)
{
    LED_STATUS &= ~(LED_PLAY | LED_PAUSE);
#ifdef LED_2POINT1	
	LED_STATUS &= ~(LED_2POINT|LED_2POINT1); //| LED_PLAY;
#else
	LED_STATUS &= ~(LED_2POINT); //| LED_PLAY;
#endif
   LED_STATUS &= ~(LED_SD|LED_USB);

    if((g_rec_ctl)&&(ENC_STOP != g_rec_ctl->enable))
    {
        led7_show_rec_start();
    }
    else
    {
        led7_show_string((u8 *)other_string[4]);
    }

}

void led7_show_rec_time(void)
{
    LED_STATUS &= ~(LED_PLAY | LED_PAUSE);
#ifdef LED_2POINT1	
	LED_STATUS &= ~(LED_2POINT|LED_2POINT1); //| LED_PLAY;
#else
	LED_STATUS &= ~(LED_2POINT); //| LED_PLAY;
#endif
    LED_STATUS &= ~(LED_SD|LED_USB);
        led7_show_rec_start();
}

void led7_show_rec(void)
{
    LED_STATUS &= ~(LED_PLAY | LED_PAUSE);
#ifdef LED_2POINT1	
	LED_STATUS &= ~(LED_2POINT|LED_2POINT1); //| LED_PLAY;
#else
	LED_STATUS &= ~(LED_2POINT); //| LED_PLAY;
#endif
    LED_STATUS &= ~(LED_SD|LED_USB);
    led7_show_string((u8 *)other_string[4]);
}
#ifdef LED_SHOW_DEL
void led7_show_del(void)
{
    led7_show_string((u8 *)" dEL");
}
#endif
#endif

#if 0
void LED_drive7(void)
{
    u8 k,i,j,temp;
    k=0;

//    led7_var.bShowBuff[0]=0xff;
//    led7_var.bShowBuff[1]=0xff;
//    led7_var.bShowBuff[2]=0xff;
//    led7_var.bShowBuff[3]=0xff;
//    led7_var.bShowBuff[4]=0xff;

    led7_var.bShowBuff1[0]=0;
    led7_var.bShowBuff1[1]=0;
    led7_var.bShowBuff1[2]=0;
    led7_var.bShowBuff1[3]=0;
    led7_var.bShowBuff1[4]=0;
    led7_var.bShowBuff1[5]=0;
    led7_var.bShowBuff1[6]=0;


#if defined(support_yl_3520)
    for(i=0;i<6;i++)
#else 
    for(i=0;i<5;i++)
#endif 		
    {
        temp = led7_var.bShowBuff[i];

        if (sys_halfsec)
        {

#ifdef support_mute_led_all_flish        
      #ifdef support_line_pause
             if( aux_pause_mark==0 &&dac_var.bMute)
                    temp = 0x0;		
                 else	 
      #else 
                  if(dac_var.bMute)
      		   temp = 0x0;		
                 else
      #endif 		   	
#endif 		   	
   	if ((led7_var.bFlashIcon) && (i == 4))
            {
                temp = LED_STATUS & (~led7_var.bFlashIcon);
            }
        else if (led7_var.bFlashChar & BIT(i))	
            {
                temp = 0x0;
            }
        }

        for(j=0;j<7;j++)
        {
            if(temp & bit_table[j])
            {
                led7_var.bShowBuff1[led_7[k][0]] |= bit_table[led_7[k][1]];
            }
            k++;
        }
        if(j == 7)
        {
            if(temp & bit_table[j])
                led7_var.bShowBuff1[led_7[35][0]] |= bit_table[led_7[35][1]];
        }
    }
}
#endif
#ifdef LED_SCREEN_SHOW_LED_MODE
void led7_show_RGB_led_mode(void)
{
    led7_show_string((u8 *)" L");
    itoa2(bRGBMode);
    led7_show_string((u8 *)bcd_number);
}
#endif

#ifdef SUPPORT_MUTE_FLASH
void led7_mute_flash(void)
{

#ifdef support_low_power_use_extern_io
#ifndef support_zy_low_power_standby
#ifdef support_low_power_show_bat_flash
	if(low_power_sw)
	{
		 if(sys_halfsec)
		 {
			 led7_var.bShowBuff[0]=0;
			 led7_var.bShowBuff[1]=0x7c;
			 led7_var.bShowBuff[2]=0x77;
			 led7_var.bShowBuff[3]=0x78;
			 LED_STATUS=0;	
		 }
		 else
		 {
			 led7_var.bShowBuff[0]=0;
			 led7_var.bShowBuff[1]=0;
			 led7_var.bShowBuff[2]=0;
			 led7_var.bShowBuff[3]=0;
			 LED_STATUS=0;
		 }
//		LED_FLASH_CHAR=0xff;
//		LED_FLASH_ICON=0xffff;
		 return;
	}
#else  // show bat  flash
	if(low_power_sw)
		{
			LED_FLASH_CHAR=0xff;
			LED_FLASH_ICON=0xffff;
			return;	 
		}

#endif	
#endif	
#endif



  if(!b_muteFlag){
  #if LED_MUTE>0
   LED_STATUS&=~LED_MUTE;
   LED_FLASH_ICON&=~LED_MUTE;
  #endif
  return;
  }
  #ifdef MUTE_FLASH_ZERO_VOL  
     LED_STATUS&=~(LED_2POINT|LED_DOT);
     #ifdef SUPPORT_FLASH_ICON
     LED_FLASH_ICON&=~(LED_2POINT|LED_DOT);
     #endif
     
     LED_FLASH_CHAR=0xff;
     led7_var.bShowBuff[0]=LED_LARGE_LETTER['V'-'A'];
     led7_var.bShowBuff[1]=0;
     led7_var.bShowBuff[2]=LED_NUMBER[0]; 
     led7_var.bShowBuff[3]=LED_NUMBER[0];
  #elif defined(MUTE_FLASH_ONLY_TIME)
    #if LED_8NUMS==7
     LED_FLASH_CHAR=0x78;
     LED_FLASH_ICON=LED_2POINT;
    #endif	 
  #elif defined(MUTE_FLASH_ALL_SCREEN)
     LED_FLASH_CHAR=0xff;
     LED_FLASH_ICON=0xffff;
  #elif LED_MUTE
     LED_STATUS|=LED_MUTE;
     LED_FLASH_ICON|=LED_MUTE;
  #else
   	LED_STATUS&=~LED_2POINT;
       #ifdef SUPPORT_FLASH_ICON
   	LED_FLASH_ICON&=~LED_2POINT;
       #endif
     led7_var.bShowBuff[0]=LED_LARGE_LETTER['N'-'A'];
     led7_var.bShowBuff[1]=LED_LARGE_LETTER['U'-'A'];
     led7_var.bShowBuff[2]=LED_LARGE_LETTER['T'-'A']; 
     led7_var.bShowBuff[3]=LED_LARGE_LETTER['E'-'A'];
  #endif
}
#endif
#ifdef LED_SCREEN_SHOW_BAT_STATUS
#define BAT_15 1023*15/33
#define BAT_16 1023*16/33
#define BAT_17 1023*17/33
#define BAT_18 1023*18/33
#define BAT_19 1023*19/33
#define BAT_21 1023*21/33
#define BAT_23 1023*23/33
#define BAT_24 1023*24/33
#define BAT_25 1023*25/33

#define BAT_27 1023*27/33 
#define BAT_31 1023*31/33
#define BAT_30 1023*30/33

#define BAT_153 1023*153/330  //9V
#define BAT_161 1023*161/330  //9V-/-12v
#define BAT_196 1023*196/330  // 11v -/- 12v

#define BAT_275 1023*275/330  //7.5V
#define BAT_270 1023*270/330  //7.5V


#define BAT_174 1023*174/330  //7.5V
#define BAT_166 1023*166/330  //7V
#define BAT_163 1023*163/330  //7V
#define BAT_152 1023*152/330  //6.5V
#define BAT_151 1023*151/330  //6.5V
#define BAT_148 1023*148/330  //6.2V
#define BAT_144 1023*144/330  //6.2V
#define BAT_135 1023*135/330  //6V  low power mode

void led7_show_bat_status(void)
{
  #ifdef SUPPORT_BAT_DETECT_USE_IO
	   u16 bat_value=adc_value[AD_CH_BAT];//1023;//led7_var.wAdc_value;
	   

//	printf("\n bat_value %x \n",bat_value);

   #if defined LED_ID_4018N_2||defined LED_ID_4018N_2B

//	   LED_STATUS|=LED_BAT;
//	   LED_FLASH_ICON&=~LED_BAT;
//	   if(bat_value<BAT_21)
//		   LED_FLASH_ICON|=LED_BAT;  
	   
        static u8 bCnt=0,bTimeCnt=0;
        static u8 btemp1=0,btemp2=0;
        bCnt++;
		
	 #ifdef support_power_on_30s_bat_icon_on // jsuo add
	 	if((bat_icon_timer>58))
	 	{
		    LED_STATUS&=~LED_BAT;
		    LED_FLASH_ICON&=~LED_BAT;			
	 	}	 
	 	else if((bat_icon_timer>0))
	 	{
		    LED_STATUS|=LED_BAT;
		    LED_FLASH_ICON&=~LED_BAT;			
	 	}
		else			
	 #endif
	   {
	        if(bCnt>2)
			{
			        bCnt=0;
			        bTimeCnt++;
				 #ifdef ZY_5017_SG_2_AC4601		        
				 	if(bat_value>BAT_153)btemp1++;
				 	else btemp2++;
				 #else
				 	if(bat_value>BAT_21)btemp1++;
				 	else btemp2++;
				 #endif
			        if(bTimeCnt==10)
				{
					LED_STATUS&=~LED_BAT;
					LED_FLASH_ICON&=~LED_BAT;	
					
					if(btemp1)
					LED_STATUS|=LED_BAT;
					else if(btemp2)
					{
					   LED_STATUS|=LED_BAT;
					   LED_FLASH_ICON|=LED_BAT;
					   }
				   bTimeCnt=0;	
				   btemp1=0;
				   btemp2=0;

				 }
		      }
		}
	 
   #elif defined LED_ID_4018_72 ||defined(LED_ID_40T18SRB)

   
	   LED_STATUS|=LED_BAT01|LED_BAT02|LED_BAT03;
	   #ifdef GW_011_AC4601
		   if(bat_value<BAT_144)
			   LED_STATUS&=~LED_BAT03;
		   if(bat_value<BAT_151)
			   LED_STATUS&=~LED_BAT02;
		   if(bat_value<BAT_174)
			   LED_STATUS&=~LED_BAT01;	 
		   #ifdef LOW_POWER_DIRECT_INTO_IDLE_MODE
		    if(bat_value<BAT_135){
		    os_taskq_post("MainTask", 1, MSG_STANBY_KEY);
		    }
		   #endif
		   
       #elif defined(ZY_3016_REC_AC4601_V10)		   
	   if(bat_value<=BAT_19)
		   LED_STATUS&=~LED_BAT03;
	   if(bat_value<=BAT_21)
		   LED_STATUS&=~LED_BAT02;
	   if(bat_value<=BAT_25)
		   LED_STATUS&=~LED_BAT01;	 
	   #else
		   if(bat_value<=BAT_19)
			   LED_STATUS&=~LED_BAT03;
		   if(bat_value<=BAT_21)
			   LED_STATUS&=~LED_BAT02;
		   if(bat_value<=BAT_25)
			   LED_STATUS&=~LED_BAT01;	 
	   #endif
	   
   #elif defined(LED_ID_JW4018D_1B) 
           static u8 bCnt=0,bTimeCnt=0;
        static u8 btemp1=0,btemp2=0,btemp3=0,btemp4=0;
		
        bCnt++;
		
	if((fm_mode_var->scan_mode == FM_SCAN_ALL)||(UI_var.bCurMenu==MENU_MAIN_VOL))
	{
//		       if(bCnt>2)
		 	{
		 	        bCnt=0;
		 	        bTimeCnt++;

			   #ifdef ZY_6003_4018D_3_AC4601		
			       /*
			 		1.7v low power voice
			 		1.8v half_flash
			 		1.9v half on
			 		2.4v  full on	
			 		*/
			 
			 		 		if(bat_value>BAT_24)btemp1++;
			 		 		else if(bat_value>BAT_19)btemp2++;
			 		 		else if(bat_value>BAT_18)btemp3++;		
			 		 		else btemp4++;		
			 #else
			 
			 #ifdef support_bat_hight_24		 		
			 		 		if(bat_value>BAT_24)btemp1++;
			 #else
			 		 		if(bat_value>BAT_25)btemp1++;
			 #endif
			 		 		else if(bat_value>BAT_23)btemp2++;
			 		 		else if(bat_value>BAT_21)btemp3++;		
			 		 		else btemp4++;
			 #endif		 		
//		         if(bTimeCnt==10)
		 	{
		 		LED_STATUS&=~(LED_BAT01|LED_BAT02|LED_BAT03);
		 		LED_FLASH_ICON&=~LED_BAT03;	
		 		
		 		if(btemp1)
		 		{
		 			LED_STATUS|=(LED_BAT01|LED_BAT02|LED_BAT03);
		 		}
		 		else if(btemp2)
		 		{
		 			LED_STATUS|=(LED_BAT02|LED_BAT03);
		 		}
		 		else if(btemp3)
		 		{
		 			LED_STATUS|=(LED_BAT03);
		 		}		
		 		else if(btemp4)
		 		{
		 			   LED_STATUS|=LED_BAT03;
		 			   LED_FLASH_ICON|=LED_BAT03;
		 		  }
		 		   bTimeCnt=0;	
		 		   btemp1=0;
		 		   btemp2=0;
		 		   btemp3=0;
		 		   btemp4=0;
		 	 }
		       }
		}
		else
		 {
		 		       if(bCnt>2)
		 		 	{
		 		 	        bCnt=0;
		 		 	        bTimeCnt++;
		 		 		
		 #ifdef support_bat_hight_24		 		
		 		 		if(bat_value>BAT_24)btemp1++;
		 #else
		 		 		if(bat_value>BAT_25)btemp1++;
		 #endif
		 		 		else if(bat_value>BAT_23)btemp2++;
		 		 		else if(bat_value>BAT_21)btemp3++;		
		 		 		else btemp4++;
		 		 		
		 		         if(bTimeCnt==10)
		 		 	{
		 		 		LED_STATUS&=~(LED_BAT01|LED_BAT02|LED_BAT03);
		 		 		LED_FLASH_ICON&=~LED_BAT03;	
		 		 		
		 		 		if(btemp1)
		 		 		{
		 		 			LED_STATUS|=(LED_BAT01|LED_BAT02|LED_BAT03);
		 		 		}
		 		 		else if(btemp2)
		 		 		{
		 		 			LED_STATUS|=(LED_BAT02|LED_BAT03);
		 		 		}
		 		 		else if(btemp3)
		 		 		{
		 		 			LED_STATUS|=(LED_BAT03);
		 		 		}		
		 		 		else if(btemp4)
		 		 		{
		 		 			   LED_STATUS|=LED_BAT03;
		 		 			   LED_FLASH_ICON|=LED_BAT03;
		 		 		  }
		 		 		   bTimeCnt=0;	
		 		 		   btemp1=0;
		 		 		   btemp2=0;
		 		 		   btemp3=0;
		 		 		   btemp4=0;
		 		 	 }
		 		       }
		 		}
		
   #elif defined(LED_ID_4018_73)

           static u8 bCnt=0,bTimeCnt=0;
        static u8 btemp1=0,btemp2=0,btemp3=0,btemp4=0;
		
        bCnt++;
		
		 {
		 		       if(bCnt>2)
		 		 	{
		 		 	        bCnt=0;
		 		 	        bTimeCnt++;
		 		 		
		 		 		if(bat_value>BAT_24)btemp1++;
		 		 		else if(bat_value>BAT_19)btemp2++;
		 		 		else if(bat_value>BAT_18)btemp3++;		
		 		 		else btemp4++;
		 		 		
		 		         if(bTimeCnt==10)
		 		 	{
		 		 		LED_STATUS&=~(LED_BAT01|LED_BAT02|LED_BAT03);
		 		 		LED_FLASH_ICON&=~LED_BAT03;	
		 		 		
		 		 		if(btemp1)
		 		 		{
		 		 			LED_STATUS|=(LED_BAT01|LED_BAT02|LED_BAT03);
		 		 		}
		 		 		else if(btemp2)
		 		 		{
		 		 			LED_STATUS|=(LED_BAT02|LED_BAT03);
		 		 		}
		 		 		else if(btemp3)
		 		 		{
		 		 			LED_STATUS|=(LED_BAT03);
		 		 		}		
		 		 		else if(btemp4)
		 		 		{
		 		 			   LED_STATUS|=LED_BAT03;
		 		 			   LED_FLASH_ICON|=LED_BAT03;
		 		 		  }
		 		 		   bTimeCnt=0;	
		 		 		   btemp1=0;
		 		 		   btemp2=0;
		 		 		   btemp3=0;
		 		 		   btemp4=0;
		 		 	 }
		 		       }
		 		}		  
		 
   #elif defined(LED_ID_SD40C18SRB)


           static u8 bCnt=0,bTimeCnt=0;
        static u8 btemp1=0,btemp2=0,btemp3=0,btemp4=0;
		
        bCnt++;
		
		 {
		 		       if(bCnt>2)
		 		 	{
		 		 	        bCnt=0;
		 		 	        bTimeCnt++;
		 		 		
		 		 		if(bat_value>BAT_25)btemp1++;
		 		 		else if(bat_value>BAT_23)btemp2++;
		 		 		else if(bat_value>BAT_21)btemp3++;		
		 		 		else btemp4++;
		 		 		
		 		         if(bTimeCnt==10)
		 		 	{
		 		 		LED_STATUS&=~(LED_BAT01|LED_BAT02|LED_BAT03);
		 		 		LED_FLASH_ICON&=~LED_BAT03;	
		 		 		
		 		 		if(btemp1)
		 		 		{
		 		 			LED_STATUS|=(LED_BAT01|LED_BAT02|LED_BAT03);
		 		 		}
		 		 		else if(btemp2)
		 		 		{
		 		 			LED_STATUS|=(LED_BAT02|LED_BAT03);
		 		 		}
		 		 		else if(btemp3)
		 		 		{
		 		 			LED_STATUS|=(LED_BAT03);
		 		 		}		
		 		 		else if(btemp4)
		 		 		{
		 		 			   LED_STATUS|=LED_BAT03;
		 		 			   LED_FLASH_ICON|=LED_BAT03;
		 		 		  }
		 		 		   bTimeCnt=0;	
		 		 		   btemp1=0;
		 		 		   btemp2=0;
		 		 		   btemp3=0;
		 		 		   btemp4=0;
		 		 	 }
		 		       }
		 		}	
		 
   #elif defined(LED_ID_8848_BAT)||defined(LED_ID_JW_24017_1B)||defined(LED_ID_JW_24017_1B)

	    #ifdef SUPPORT_BAT_12v_100K_22K_VOLAT
	    
	 		     static u8 bCnt=0,bTimeCnt=0;
	 		        static u8 btemp1=0,btemp2=0,btemp3=0;
	 		        bCnt++;
	 		        if(bCnt>100){
	 		        bCnt=0;
	 		        bTimeCnt++;
				/*
				
					9Vʱ��1��61V
					11Vʱ��1��96V	
				
				*/

	 				if(bat_value>=BAT_196)btemp1++;  
	 				else if(bat_value>=BAT_161)btemp2++;		
	 				else btemp3++;
	 				
	 		        if(bTimeCnt==10)
	 				{
	 					LED_STATUS&=~(LED_BAT_FULL|LED_BAT_HALF);
	 					LED_FLASH_ICON&=~LED_BAT_HALF;	
	 					
	 					if(btemp1)
	 					LED_STATUS|=LED_BAT_FULL;
	 					else if(btemp2)
	 						LED_STATUS|=LED_BAT_HALF;
	 					else if(btemp3)
	 					{
	 						   LED_STATUS|=LED_BAT_HALF;
	 						   LED_FLASH_ICON|=LED_BAT_HALF;
	 					   }
	 					   bTimeCnt=0;	
	 					   btemp1=0;
	 					   btemp2=0;
	 					   btemp3=0;
	 				 }
	 		      }
	 
	    #else
	 		     static u8 bCnt=0,bTimeCnt=0;
	 		        static u8 btemp1=0,btemp2=0,btemp3=0;
	 		        bCnt++;
	 		        if(bCnt>100){
	 		        bCnt=0;
	 		        bTimeCnt++;
	 		        /*
	 				1.7v low power voice
	 				1.8v half_flash
	 				1.9v half on
	 				2.4v  full on	
	 				*/
	 				
	 				if(bat_value>=BAT_19)btemp1++;  
	 				else if(bat_value>=BAT_18)btemp2++;		
	 				else btemp3++;
	 				
	 		        if(bTimeCnt==10)
	 				{
	 					LED_STATUS&=~(LED_BAT_FULL|LED_BAT_HALF);
	 					LED_FLASH_ICON&=~LED_BAT_HALF;	
	 					
	 					if(btemp1)
	 					LED_STATUS|=LED_BAT_FULL;
	 					else if(btemp2)
	 						LED_STATUS|=LED_BAT_HALF;
	 					else if(btemp3)
	 					{
	 						   LED_STATUS|=LED_BAT_HALF;
	 						   LED_FLASH_ICON|=LED_BAT_HALF;
	 					   }
	 					   bTimeCnt=0;	
	 					   btemp1=0;
	 					   btemp2=0;
	 					   btemp3=0;
	 				 }
	 		      }
	 		
	 	  #endif
	  
   #elif defined(LED_ID_KF33T1)
   
	   LED_STATUS|=LED_BAT01|LED_BAT02|LED_BAT03|LED_BAT04|LED_BAT_FRAME;   
	   LED_FLASH_ICON&=~LED_BAT_FRAME;
       if(bat_value<BAT_15){
		   LED_STATUS&=~LED_BAT01;
		   LED_FLASH_ICON|=LED_BAT_FRAME;
		   }
	   if(bat_value<BAT_16)
		   LED_STATUS&=~LED_BAT02;
	   if(bat_value<BAT_17)
		   LED_STATUS&=~LED_BAT03;
	   if(bat_value<BAT_18)
		   LED_STATUS&=~LED_BAT04;
	   
    #elif defined(LED_ID_KD048AR_P15)||defined(LED_ID_SD28N20)
	
        static u8 bCnt=0,bTimeCnt=0;
        static u8 btemp1=0,btemp2=0,btemp3=0;
        bCnt++;
        if(bCnt>100){
        bCnt=0;
        bTimeCnt++;
        
		if(bat_value>BAT_166)btemp1++;
		else if(bat_value>BAT_152)btemp2++;
		else btemp3++;
		
        if(bTimeCnt==10){
		LED_STATUS&=~(LED_BAT_FULL|LED_BAT_HALF);
		LED_FLASH_ICON&=~LED_BAT_HALF;	
		
		if(btemp1)
		LED_STATUS|=LED_BAT_FULL;
		else if(btemp2)
			LED_STATUS|=LED_BAT_HALF;
		else if(btemp3){
		   LED_STATUS|=LED_BAT_HALF;
		   LED_FLASH_ICON|=LED_BAT_HALF;
		   }
	   bTimeCnt=0;	
	   btemp1=0;
	   btemp2=0;
	   btemp3=0;
	 }
      }
		
   #endif
   
  #else
   u16 bat_value;
   #if SYS_LVD_EN
   bat_value=get_battery_value();
   #endif
   #if defined LED_ID_4018N_2||defined LED_ID_4018N_2B
	   LED_STATUS|=LED_BAT;
	   LED_FLASH_ICON&=~LED_BAT;
	   if(bat_value<BAT_21)
		   LED_FLASH_ICON|=LED_BAT;  
	   
   #elif defined(LED_ID_8812)
   LED_STATUS|=LED_BAT_FULL|LED_BAT_HALF;
   if(bat_value<38)LED_STATUS&=~LED_BAT_FULL;
   if(bat_value<34)LED_STATUS&=~LED_BAT_HALF;
   #else
   if(bat_value>40){
   LED_STATUS|=LED_BAT01|LED_BAT02|LED_BAT03;
   LED_FLASH_ICON&=~LED_BAT03;
   }
   else if(bat_value>34 && bat_value<=40){   
   LED_STATUS|=LED_BAT02|LED_BAT03;
   LED_STATUS&=~LED_BAT01;
   LED_FLASH_ICON&=~LED_BAT03;
   }
   else if( bat_value<=34)
   {
	LED_STATUS&=~(LED_BAT01|LED_BAT02);
	LED_STATUS|=LED_BAT03;
	LED_FLASH_ICON|=LED_BAT03;
   }
  #endif
  #endif
}    
#endif
void blueToothLedProc(void)
{

	 #ifdef support_change_mode_bt_icon_off
		 if(exit_bt_sw==1)
		 {
			 #ifndef LED_FLASH_BT_ICON_USE_LIGHTS
			 	  #if LED_BT
			 	    LED_STATUS&=~LED_BT;    
			 	    LED_FLASH_ICON&=~LED_BT;
			 	  #endif
			 #endif	 
		 }	 
		else
	  #endif
	  
 	  {	 
 	 	if(led7_var.bBtIfConnect)
 	 	{
 	 				 #ifndef LED_FLASH_BT_ICON_USE_LIGHTS
 	 				 	  #if LED_BT
 	 				 	    LED_STATUS|=LED_BT;    
 	 				 	    LED_FLASH_ICON&=~LED_BT;
 	 				 	  #endif
 	 				 #endif
 	 				 #if LED_BT_MUSIC
 	 				 	   LED_STATUS|=LED_BT_MUSIC;
 	 				 	   LED_FLASH_ICON&=~LED_BT_MUSIC;
 	 				 #endif
 	 				 #ifdef SUPPORT_LED_BLUE_STRING_FLASH
 	 				 	   LED_FLASH_CHAR=0;
 	 				 #endif
 	 	}
	 	 	else{
	 	 			 #ifndef LED_FLASH_BT_ICON_USE_LIGHTS
	 	 			    #if LED_BT
	 	 			     LED_STATUS|=LED_BT;
	 	 			     LED_FLASH_ICON|=LED_BT;
	 	 			    #endif
	 	 			 #endif   
	 	 			 #if LED_BT_MUSIC
	 	 			    LED_STATUS|=LED_BT_MUSIC;
	 	 			    LED_FLASH_ICON|=LED_BT_MUSIC;
	 	 			 #endif
	 	 			 #ifdef SUPPORT_LED_BLUE_STRING_FLASH
	 	 			 #ifdef SUPPORT_LED_BLUE_FLASH_HIGH_4BIT
	 	 			 	LED_FLASH_CHAR=0xf0;
	 	 			 #else
	 	 			 	LED_FLASH_CHAR=0xff;
	 	 			 #endif
	 	 			 #endif
	 	  }
 	  }
}
#if defined(VFD_ID_YDL2001_35)||defined(LED_ID_JW2781)||defined(LED_ID_WLD007)
void LED_CIRCLE_PROCESS(void)
{
static u8 cnt=0;
static u8 mode=0;
#if defined(LED_ID_JW2781)
	  if(compare_task_name("MusicTask"))
	  {
	 	 led7_var.bCircleBuf=0xff;
	 	 switch(mode)
		 {
		 	   case 0:
		 		   led7_var.bCircleBuf&=~(BIT(0)|BIT(4));
		   	       break;
		 	   case 1:
		 		   led7_var.bCircleBuf&=~(BIT(1)|BIT(5));
		 	       break;
		 	   case 2:
		 		   led7_var.bCircleBuf&=~(BIT(2)|BIT(6));
		 	       break;
		 	   case 3:
		 		   led7_var.bCircleBuf&=~(BIT(3)|BIT(7));
		 	      break;
	 	 }
	 	 if(*music_ui.ui_curr_statu != DECODER_PAUSE)
		 	 cnt++;
	 	 if(cnt>2)
		 {
		 	 cnt=0;
		 	 mode++;
		 	 if(mode>3)mode=0;
	 	 }
	  }
 
	 else
	 	led7_var.bCircleBuf=0;
#elif defined(LED_ID_WLD007)
	  if(compare_task_name("MusicTask"))
	  {
	 	 led7_var.bCircleBuf=0xff;
	 	 switch(mode)
		 {
		 	   case 0:
		 		   led7_var.bCircleBuf&=~(BIT(0)|BIT(4));
		   	       break;
		 	   case 1:
		 		   led7_var.bCircleBuf&=~(BIT(1)|BIT(5));
		 	       break;
		 	   case 2:
		 		   led7_var.bCircleBuf&=~(BIT(2)|BIT(6));
		 	       break;
		 	   case 3:
		 		   led7_var.bCircleBuf&=~(BIT(3)|BIT(7));
		 	      break;
	 	 }
	 	 if(*music_ui.ui_curr_statu != DECODER_PAUSE)
		 	 cnt++;
	 	 if(cnt>10)
		 {
		 	 cnt=0;
		 	 mode++;
		 	 if(mode>3)mode=0;
	 	 }
	  }
 
	 else
	 	led7_var.bCircleBuf=0; 
#else
LED_STATUS&=~(LED_CIRCLE_01|LED_CIRCLE_02|LED_CIRCLE_03);
if(compare_task_name("MusicTask"))
{
 switch(mode){
   case 0:
   LED_STATUS|=LED_CIRCLE_01;
   break;
   case 1:
   LED_STATUS|=LED_CIRCLE_02;
   break;
   case 2:
   LED_STATUS|=LED_CIRCLE_03;
   break;
 }
 if(*music_ui.ui_curr_statu != DECODER_PAUSE)
 cnt++;
 if(cnt>40){
 cnt=0;
 mode++;
 if(mode>2)mode=0;
 }
}
#endif
}
#endif
#ifdef LED_VOLUME_ICON_PROCESS
void LED_PROCESS_VOLUME_ICON(void)
{
  LED_STATUS&=~(LED_VOLUME|LED_SUBWOOFER);
  //process sw.vol treble icons    
  LED_STATUS&=~(LED_TRE|LED_SWVOL);
  
  if(!compare_task_name("IdleTask")){  
  if(!b_muteFlag)
    LED_STATUS|=LED_VOLUME|LED_SUBWOOFER;
    
  if(menumode==MENU_TREBLE_MODE)
     LED_STATUS|=LED_TRE;
  else if (menumode==MENU_SWVOLL_MODE)
	  LED_STATUS|=LED_SWVOL;
	  }  
}
#endif
#ifdef SUPPORT_LCD_4COM_9SEG_MODE
#ifdef LCD_ID_HL_21716HNT
void LED_drive7(void)
{
    u8 i,j,temp,temp2;
    u8 temp1;

    led7_var.bShowBuff1[0]=0;
    led7_var.bShowBuff1[1]=0;
    led7_var.bShowBuff1[2]=0;
    led7_var.bShowBuff1[3]=0;
    
    if(compare_task_name("BtStackTask")){
      if(led7_var.bBtIfConnect){
       LED_STATUS|=LED_BT;
       LED_FLASH_ICON&=~LED_BT;
      }
      else{
		  LED_STATUS|=LED_BT;
		  LED_FLASH_ICON|=LED_BT;
		  }
    }
    else{
		LED_STATUS&=~LED_BT;
		LED_FLASH_ICON&=~LED_BT;
    }
   if(compare_task_name("MusicTask"))
    {
    #if LED_REPLAY
		if(play_mode==REPEAT_ONE)
		{
		   LED_STATUS|=LED_REPLAY;
        #ifdef SUPPORT_FLASH_ICON
		   LED_FLASH_ICON|=LED_REPLAY;
        #endif
		}
		else{
			LED_STATUS&=~LED_REPLAY;
         #ifdef SUPPORT_FLASH_ICON
			LED_FLASH_ICON&=~LED_REPLAY;
      #endif
 		}
    #endif
#if 0//LED_FOLDER
		if(play_mode==REPEAT_FOLDER)
		{
		   LED_STATUS|=LED_FOLDER;
	#ifdef SUPPORT_FLASH_ICON
		   LED_FLASH_ICON|=LED_FOLDER;
	#endif
		}
		else{
			LED_STATUS&=~LED_FOLDER;
	 #ifdef SUPPORT_FLASH_ICON
			LED_FLASH_ICON&=~LED_FOLDER;
  #endif
 		}
#endif
    }
    else
 {
  #if LED_REPLAY
	  LED_STATUS|=LED_REPLAY;
  #ifdef SUPPORT_FLASH_ICON
	 LED_FLASH_ICON|=LED_REPLAY;
  #endif
  #endif
    
  #if LED_FOLDER
	LED_STATUS&=~LED_FOLDER;
	LED_FLASH_ICON&=~LED_FOLDER;
  #endif
    }
    #ifdef LED_SCREEN_SHOW_BAT_STATUS
	 led7_show_bat_status();
    #endif
    #ifdef SUPPORT_MUTE_FLASH
    led7_mute_flash();
    #endif

	
	temp1=led7_var.wLedIcon;
    #ifdef SUPPORT_FLASH_ICON
	if(sys_halfsec &&led7_var.wFlashIcon)
	temp1&=~(led7_var.wFlashIcon);
    #endif


	if(temp1&LED_2POINT) led7_var.bShowBuff1[3]|=BIT(10);
	if(temp1&LED_SD) led7_var.bShowBuff1[0]|=BIT(4);
	if(temp1&LED_USB) led7_var.bShowBuff1[1]|=BIT(4);
	if(temp1&LED_DOT) led7_var.bShowBuff1[3]|=BIT(14);

	if(temp1&LED_BT) led7_var.bShowBuff1[3]|=BIT(4);
	if(temp1&LED_RECO) led7_var.bShowBuff1[3]|=BIT(8);
	if(temp1&LED_MUTE) led7_var.bShowBuff1[3]|=BIT(6);
	if(temp1&LED_FOLDER) led7_var.bShowBuff1[2]|=BIT(4);

	for(i=0;i<LED_8NUMS;i++){
	 temp=led7_var.bShowBuff[i];
     #ifdef SUPPORT_FLASH_CHAR
	 if(sys_halfsec &&(led7_var.bFlashChar & BIT(i)))
	 temp=0;
     #endif

	 for(j=0;j<LED_8GRIDS;j++)	 
		 if(temp&BIT(j)){
		    temp2=led_nums[i][j];
		    switch(temp2){
		      case 0x01:
				  led7_var.bShowBuff1[led_nums[i][j]>>8]|=BIT(6);
			      break;
		      case 0x02:
				  led7_var.bShowBuff1[led_nums[i][j]>>8]|=BIT(7);
			      break;
		      case 0x04:
				  led7_var.bShowBuff1[led_nums[i][j]>>8]|=BIT(8);
			      break;
		      case 0x08:
				  led7_var.bShowBuff1[led_nums[i][j]>>8]|=BIT(9);
			      break;
		      case 0x10:
				  led7_var.bShowBuff1[led_nums[i][j]>>8]|=BIT(10);
			      break;
		      case 0x20:
				  led7_var.bShowBuff1[led_nums[i][j]>>8]|=BIT(11);
			      break;
		      case 0x40:
				  led7_var.bShowBuff1[led_nums[i][j]>>8]|=BIT(14);
			      break;
		      case 0x80:
				  led7_var.bShowBuff1[led_nums[i][j]>>8]|=BIT(15);
			      break;
		    }
		 }
	 }
}

#elif defined LCD_ID_ZSLCD

void LED_drive7(void)
{
    u8 i,j,temp,temp2;
    u8 temp1;

    led7_var.bShowBuff1[0]=0;
    led7_var.bShowBuff1[1]=0;
    led7_var.bShowBuff1[2]=0;
    led7_var.bShowBuff1[3]=0;
    
    if(compare_task_name("BtStackTask")){
      if(led7_var.bBtIfConnect){
       LED_STATUS|=LED_BT;
       LED_FLASH_ICON&=~LED_BT;
      }
      else{
		  LED_STATUS|=LED_BT;
		  LED_FLASH_ICON|=LED_BT;
		  }
    }
    else{
		LED_STATUS&=~LED_BT;
		LED_FLASH_ICON&=~LED_BT;
    }
   if(compare_task_name("MusicTask"))
    {
    #if LED_REPLAY
		if(play_mode==REPEAT_ONE)
		{
		   LED_STATUS|=LED_REPLAY;
        #ifdef SUPPORT_FLASH_ICON
		   LED_FLASH_ICON|=LED_REPLAY;
        #endif
		}
		else{
			LED_STATUS&=~LED_REPLAY;
         #ifdef SUPPORT_FLASH_ICON
			LED_FLASH_ICON&=~LED_REPLAY;
      #endif
 		}
    #endif
#if 0//LED_FOLDER
		if(play_mode==REPEAT_FOLDER)
		{
		   LED_STATUS|=LED_FOLDER;
	#ifdef SUPPORT_FLASH_ICON
		   LED_FLASH_ICON|=LED_FOLDER;
	#endif
		}
		else{
			LED_STATUS&=~LED_FOLDER;
	 #ifdef SUPPORT_FLASH_ICON
			LED_FLASH_ICON&=~LED_FOLDER;
  #endif
 		}
#endif
    }
    else{
  #if LED_REPLAY
	  LED_STATUS|=LED_REPLAY;
  #ifdef SUPPORT_FLASH_ICON
	 LED_FLASH_ICON|=LED_REPLAY;
  #endif
  #endif
    
  #if LED_FOLDER
	LED_STATUS&=~LED_FOLDER;
	LED_FLASH_ICON&=~LED_FOLDER;
  #endif
    }
    #ifdef LED_SCREEN_SHOW_BAT_STATUS
	 led7_show_bat_status();
    #endif
    #ifdef SUPPORT_MUTE_FLASH
    led7_mute_flash();
    #endif
	temp1=led7_var.wLedIcon;
    #ifdef SUPPORT_FLASH_ICON
	if(sys_halfsec &&led7_var.wFlashIcon)
	temp1&=~(led7_var.wFlashIcon);
    #endif


	if(temp1&LED_2POINT) led7_var.bShowBuff1[3]|=BIT(14);
	if(temp1&LED_SD) led7_var.bShowBuff1[2]|=BIT(14);
	if(temp1&LED_USB) led7_var.bShowBuff1[1]|=BIT(14);
	if(temp1&LED_DOT) led7_var.bShowBuff1[0]|=BIT(14);

	if(temp1&LED_BT) led7_var.bShowBuff1[3]|=BIT(15);
	if(temp1&LED_RECO) led7_var.bShowBuff1[2]|=BIT(15);
	if(temp1&LED_MUTE) led7_var.bShowBuff1[1]|=BIT(15);
	if(temp1&LED_FOLDER) led7_var.bShowBuff1[0]|=BIT(15);

	for(i=0;i<LED_8NUMS;i++){
	 temp=led7_var.bShowBuff[i];
     #ifdef SUPPORT_FLASH_CHAR
	 if(sys_halfsec &&(led7_var.bFlashChar & BIT(i)))
	 temp=0;
     #endif
	 // 1100 1111 1101 0000

	 for(j=0;j<LED_8GRIDS;j++)	 
		 if(temp&BIT(j)){
		    temp2=led_nums[i][j];
		    switch(temp2){
		      case 0x01:
				  led7_var.bShowBuff1[led_nums[i][j]>>8]|=BIT(4);
			      break;
		      case 0x02:
				  led7_var.bShowBuff1[led_nums[i][j]>>8]|=BIT(6);
			      break;
		      case 0x04:
				  led7_var.bShowBuff1[led_nums[i][j]>>8]|=BIT(7);
			      break;
		      case 0x08:
				  led7_var.bShowBuff1[led_nums[i][j]>>8]|=BIT(8);
			      break;
		      case 0x10:
				  led7_var.bShowBuff1[led_nums[i][j]>>8]|=BIT(9);
			      break;
		      case 0x20:
				  led7_var.bShowBuff1[led_nums[i][j]>>8]|=BIT(10);
			      break;
		      case 0x40:
				  led7_var.bShowBuff1[led_nums[i][j]>>8]|=BIT(11);
			      break;
		      case 0x80:
				  led7_var.bShowBuff1[led_nums[i][j]>>8]|=BIT(12);
			      break;
		    }
		 }
	 }
}
#else
void LED_drive7(void)
{
    u8 i,j,temp;
    u8 temp1;

    led7_var.bShowBuff1[0]=0;
    led7_var.bShowBuff1[1]=0;
    led7_var.bShowBuff1[2]=0;
    led7_var.bShowBuff1[3]=0;

	   if(compare_task_name("MusicTask"))
		{
		    #if LED_REPLAY
			if(play_mode==REPEAT_ONE)
			{
			   LED_STATUS|=LED_REPLAY;
				 #ifdef SUPPORT_FLASH_ICON
				 	LED_FLASH_ICON|=LED_REPLAY;
				 #endif
			}
			else{
				LED_STATUS&=~LED_REPLAY;
			          #ifdef SUPPORT_FLASH_ICON
			 				LED_FLASH_ICON&=~LED_REPLAY;
			       #endif
			}
		    #endif
		#if LED_FOLDER
			if(play_mode==REPEAT_FOLDER)
			{
			   LED_STATUS|=LED_FOLDER;
			 #ifdef SUPPORT_FLASH_ICON
			 	LED_FLASH_ICON|=LED_FOLDER;
			 #endif
			}
			else
			{
				LED_STATUS&=~LED_FOLDER;
				 #ifdef SUPPORT_FLASH_ICON
				 	LED_FLASH_ICON&=~LED_FOLDER;
				 #endif
			}
		 #endif
		 
		}
		else
		{
			  #if LED_REPLAY
				  LED_STATUS|=LED_REPLAY;
				  #ifdef SUPPORT_FLASH_ICON
					 LED_FLASH_ICON|=LED_REPLAY;
				  #endif
			  #endif
			
			 #if LED_FOLDER
				 LED_STATUS&=~LED_FOLDER;
				 LED_FLASH_ICON&=~LED_FOLDER;
			 #endif
	     }
    
    #ifdef LED_SCREEN_SHOW_BAT_STATUS
	 led7_show_bat_status();
    #endif
    #ifdef SUPPORT_MUTE_FLASH
    led7_mute_flash();
    #endif
	temp1=led7_var.wLedIcon;
    #ifdef SUPPORT_FLASH_ICON
	if(sys_halfsec &&led7_var.wFlashIcon)
	temp1&=~(led7_var.wFlashIcon);
    #endif


	if(temp1&LED_2POINT) led7_var.bShowBuff1[0]|=BIT(6);
	if(temp1&LED_SD) led7_var.bShowBuff1[1]|=BIT(6);
	if(temp1&LED_USB) led7_var.bShowBuff1[2]|=BIT(6);
	if(temp1&LED_DOT) led7_var.bShowBuff1[3]|=BIT(6);

	if(temp1&LED_BT) led7_var.bShowBuff1[0]|=BIT(4);
	if(temp1&LED_RECO) led7_var.bShowBuff1[1]|=BIT(4);
	if(temp1&LED_MUTE) led7_var.bShowBuff1[2]|=BIT(4);
	if(temp1&LED_FOLDER) led7_var.bShowBuff1[3]|=BIT(4);

	for(i=0;i<LED_8NUMS;i++){
	 temp=led7_var.bShowBuff[i];
     #ifdef SUPPORT_FLASH_CHAR
	 if(sys_halfsec &&(led7_var.bFlashChar & BIT(i)))
	 temp=0;
     #endif
	 for(j=0;j<LED_8GRIDS;j++)	 
		 if(temp&BIT(j)){
		   switch(j){
		     case 0:
		      led7_var.bShowBuff1[i]|=BIT(15);
		     break;
		     case 1:
		      led7_var.bShowBuff1[i]|=BIT(14);
		     break;
		     case 2:
		      led7_var.bShowBuff1[i]|=BIT(11);
		     break;
		     case 3:
		      led7_var.bShowBuff1[i]|=BIT(10);
		     break;
		     case 4:
		      led7_var.bShowBuff1[i]|=BIT(9);
		     break;
		     case 5:
		      led7_var.bShowBuff1[i]|=BIT(8);
		     break;
		     case 6:
		      led7_var.bShowBuff1[i]|=BIT(7);
		     break;
		   }
		 }
	 }
}
#endif

#elif defined(SUPPORT_LCD_5COM_8SEG_MODE)

	 #ifdef LCD_ID_XS700038B

		 void LED_drive7(void)
	 	{

			 	led7_var.bShowBuff1[0]=0;
			 	led7_var.bShowBuff1[1]=0;
			 	led7_var.bShowBuff1[2]=0;
			 	led7_var.bShowBuff1[3]=0;
			 	led7_var.bShowBuff1[4]=0;
			 
			 	led7_var.bShowBuff1[0]=(((led7_var.wLedIcon&0x01)<<14)|((led7_var.wLedIcon&0x02)<<9)\
			 							|((led7_var.wLedIcon&0x04)<<7)|((led7_var.wLedIcon&0x20)<<3)\
			 							|((led7_var.wLedIcon&0x40)<<1)); //14 10 9 8 7 15 11    bt sd usd     rec  recp bat0 bat3
			 
			 	led7_var.bShowBuff1[1]=(((led7_var.bShowBuff[0]&0x08)<<11)|((led7_var.bShowBuff[1]&0x08)<<7)\   
			 							|((led7_var.bShowBuff[2]&0x08)<<5)|((led7_var.bShowBuff[3]&0x08)<<3)\  
			 							|((led7_var.wLedIcon&0x10)<<3)|((led7_var.wLedIcon&0x08)<<6) );//  1  6 /1D2D/3D4D/BT DOT/2DOT   					   
			 
			 	led7_var.bShowBuff1[2]=(((led7_var.bShowBuff[0]&0x04)<<12)|((led7_var.bShowBuff[0]&0x10)<<11)\  
			 							|((led7_var.bShowBuff[1]&0x04)<<8)  |((led7_var.bShowBuff[1]&0x10)<<7)\ 
			 							|((led7_var.bShowBuff[2]&0x04)<<6)  |((led7_var.bShowBuff[2]&0x10)<<5)\	
			 							|((led7_var.bShowBuff[3]&0x04)<<4)  |((led7_var.bShowBuff[3]&0x10)<<3));   //  1  6 /1C1E/2C2E/3C3E/4C4E/	
			 
			 	led7_var.bShowBuff1[3]=(((led7_var.bShowBuff[0]&0x02)<<13)|((led7_var.bShowBuff[0]&0x40)<<9)\
			 							|((led7_var.bShowBuff[1]&0x02)<<9)  |((led7_var.bShowBuff[1]&0x40)<<5)\
			 							|((led7_var.bShowBuff[2]&0x02)<<7)  |((led7_var.bShowBuff[2]&0x40)<<3)\		
			 							|((led7_var.bShowBuff[3]&0x02)<<5)  |((led7_var.bShowBuff[3]&0x40)<<1));  //  1  6 /1B1G/2B2G/3B3G/4B4G/
			 
			 	led7_var.bShowBuff1[4]=(((led7_var.bShowBuff[0]&0x01)<<14)|((led7_var.bShowBuff[0]&0x20)<<10)\
			 							|((led7_var.bShowBuff[1]&0x01)<<10)|((led7_var.bShowBuff[1]&0x20)<<6)\  
			 							|((led7_var.bShowBuff[2]&0x01)<<8)  |((led7_var.bShowBuff[2]&0x20)<<4)\	
			 							|((led7_var.bShowBuff[3]&0x01)<<6)  |((led7_var.bShowBuff[3]&0x20)<<2)) ; //   0   5   /1A1F/2A2F/3A3F/4A4F/
							
	 	};

	 #else
	 
	 void LED_drive7(void)
	 {
	     u8 i,j,temp;
	 	u8 temp1,temp2;
	 
	 
	     led7_var.bShowBuff1[0]=0;
	     led7_var.bShowBuff1[1]=0;
	     led7_var.bShowBuff1[2]=0;
	     led7_var.bShowBuff1[3]=0;
	     led7_var.bShowBuff1[4]=0;
	 	
	    if(compare_task_name("MusicTask"))
	 	{
	 	    #if LED_REPLAY
	 				if(play_mode==REPEAT_ONE)
	 				{
	 				   LED_STATUS|=LED_REPLAY;
	 				 #ifdef SUPPORT_FLASH_ICON
	 				 	LED_FLASH_ICON|=LED_REPLAY;
	 				 #endif
	 				}
	 				else{
	 					LED_STATUS&=~LED_REPLAY;
	 					 #ifdef SUPPORT_FLASH_ICON
	 					 	LED_FLASH_ICON&=~LED_REPLAY;
	 					 #endif
	 				}
	 	    #endif
	 	
	 	 	 #if LED_FOLDER
	 	 	 		if(play_mode==REPEAT_FOLDER)
	 	 	 		{
	 	 	 		   LED_STATUS|=LED_FOLDER;
	 	 	 			 #ifdef SUPPORT_FLASH_ICON
	 	 	 			 	LED_FLASH_ICON|=LED_FOLDER;
	 	 	 			 #endif
	 	 	 		}
	 	 	 		else
	 	 	 		{
	 	 	 			LED_STATUS&=~LED_FOLDER;
	 	 	 			 #ifdef SUPPORT_FLASH_ICON
	 	 	 			 	LED_FLASH_ICON&=~LED_FOLDER;
	 	 	 			 #endif
	 	 	 		}
	 	 	 #endif	 
	 	}
	 	else
	 	{
	 	   #if LED_REPLAY
	 	 		  LED_STATUS&=~LED_REPLAY;
	 	   #ifdef SUPPORT_FLASH_ICON
	 	 		 LED_FLASH_ICON&=~LED_REPLAY;
	 	   #endif
	 	   #endif
	 	
	 	   #if LED_FOLDER
	 	 		LED_STATUS&=~LED_FOLDER;
	 	 		LED_FLASH_ICON&=~LED_FOLDER;
	 	   #endif
	 	}
	     
	     #ifdef LED_SCREEN_SHOW_BAT_STATUS
	 	 led7_show_bat_status();
	     #endif
	     #ifdef SUPPORT_MUTE_FLASH
	     led7_mute_flash();
	     #endif
	     #if defined(SUPPORT_EQ_FREQUENCE)
	     LED_FREQUENCE_PROCESS();
	     #endif
	 	temp1=led7_var.wLedIcon;
	     #ifdef SUPPORT_FLASH_ICON
	 	if(sys_halfsec &&led7_var.wFlashIcon)
	 	temp1&=~(led7_var.wFlashIcon);
	     #endif
	 
	 
	 
	 
	 	if(temp1&LED_2POINT) led7_var.bShowBuff1[0]|=BIT(15);
	 	if(temp1&LED_SD) led7_var.bShowBuff1[1]|=BIT(15);
	 	if(temp1&LED_USB) led7_var.bShowBuff1[2]|=BIT(15);
	 	if(temp1&LED_DOT) led7_var.bShowBuff1[3]|=BIT(15);
	 	if(temp1&LED_REPLAY) led7_var.bShowBuff1[4]|=BIT(14);
	 	if(temp1&LED_MUTE) led7_var.bShowBuff1[4]|=BIT(15);
	 
	 #ifdef SUPPORT_EQ_FREQUENCE
	     temp2=led7_var.bEqIconBuf;
	 	if(temp2&EQ_00) led7_var.bShowBuff1[4]|=BIT(6);
	 	if(temp2&EQ_01) led7_var.bShowBuff1[4]|=BIT(7);
	 	if(temp2&EQ_02) led7_var.bShowBuff1[4]|=BIT(8);
	 	if(temp2&EQ_03) led7_var.bShowBuff1[4]|=BIT(9);
	 #endif
	 
	 
	 
	 	for(i=0;i<LED_8NUMS;i++){
	 	 temp=led7_var.bShowBuff[i];
	      #ifdef SUPPORT_FLASH_CHAR
	 	 if(sys_halfsec &&(led7_var.bFlashChar & BIT(i)))
	 	 temp=0;
	      #endif
	 	 for(j=0;j<LED_8GRIDS;j++)	 
	 		 if(temp&BIT(j)){
	 		   switch(j){
	 		     case 0:
	 		      led7_var.bShowBuff1[i]|=BIT(6);
	 		     break;
	 		     case 1:
	 		      led7_var.bShowBuff1[i]|=BIT(7);
	 		     break;
	 		     case 2:
	 		      led7_var.bShowBuff1[i]|=BIT(8);
	 		     break;
	 		     case 3:
	 		      led7_var.bShowBuff1[i]|=BIT(9);
	 		     break;
	 		     case 4:
	 		      led7_var.bShowBuff1[i]|=BIT(10);
	 		     break;
	 		     case 5:
	 		      led7_var.bShowBuff1[i]|=BIT(11);
	 		     break;
	 		     case 6:
	 		      led7_var.bShowBuff1[i]|=BIT(14);
	 		     break;
	 		     case 7:
	 		      led7_var.bShowBuff1[i]|=BIT(15);
	 		     break;			 
	 		   }
	 		 }
	 	 }
	 }
	 
	 #endif


#elif defined(SUPPORT_PT6312_MODE)
void LED_drive7(void)
{
    u8 i,j,temp,temp2;
    u16 temp1;

    led7_var.bShowBuff1[0]=0;
    led7_var.bShowBuff1[1]=0;
    led7_var.bShowBuff1[2]=0;
    led7_var.bShowBuff1[3]=0;
    led7_var.bShowBuff1[4]=0;
    led7_var.bShowBuff1[5]=0;
    led7_var.bShowBuff1[6]=0;    
    led7_var.bShowBuff1[7]=0;
    led7_var.bShowBuff1[8]=0;
    led7_var.bShowBuff1[9]=0;
    
    if(compare_task_name("BtStackTask"))
     blueToothLedProc();
    #ifdef VFD_ID_YDL2001_35
    LED_CIRCLE_PROCESS();
    #endif
#if LED_REPLAY
    if(compare_task_name("MusicTask"))
    
    if(play_mode==REPEAT_ONE)
    {
       LED_STATUS|=LED_REPLAY;
   #ifdef SUPPORT_FLASH_ICON
       LED_FLASH_ICON|=LED_REPLAY;
   #endif
    }
    else{
		LED_STATUS&=~LED_REPLAY;
  #ifdef SUPPORT_FLASH_ICON
		LED_FLASH_ICON&=~LED_REPLAY;
  #endif
    }
#endif
#if LED_REPEAT_ONE||LED_REPEAT_ALL
LED_STATUS&=~(LED_REPEAT_ONE|LED_REPEAT_ALL);
#ifdef SUPPORT_FLASH_ICON
LED_FLASH_ICON&=~LED_REPEAT_ONE;
#endif
if(compare_task_name("MusicTask")){
if(play_mode==REPEAT_ONE){
    LED_STATUS|=LED_REPEAT_ONE;
    #ifdef SUPPORT_FLASH_ICON
	LED_FLASH_ICON|=LED_REPEAT_ONE;
    #endif
    }
else if(play_mode==REPEAT_ALL)
	LED_STATUS|=LED_REPEAT_ALL;
#endif
}
    #ifdef LED_SCREEN_SHOW_BAT_STATUS
	 led7_show_bat_status();
    #endif
    #ifdef SUPPORT_MUTE_FLASH
    led7_mute_flash();
    #endif
   
	temp1=led7_var.wLedIcon;
    #ifdef SUPPORT_FLASH_ICON
	if(sys_halfsec &&led7_var.wFlashIcon)
	temp1&=~(led7_var.wFlashIcon);
    #endif

	#if LED_ICON_NUMS>=LED_8NUMS
	for(i=0;i<LED_ICON_NUMS;i++){
	 if(temp1&BIT(i))
	 led7_var.bShowBuff1[led_icon_value[i]>>8]|=led_icon_value[i];	 
    #ifdef LED_EQ_BAR_SHOW
     if(i<LED_EQ_NUMS){
        temp2=led7_var.bEqBarBuf[i];
        for(j=0;j<LED_EQ_BAR_GRIDS;j++)
          if(temp2&BIT(j))
          led7_var.bShowBuff1[led_EQ[i][j]>>8]|=led_EQ[i][j];
     }
    #endif
	 if(i<LED_8NUMS){
	 temp=led7_var.bShowBuff[i];
     #ifdef SUPPORT_FLASH_CHAR
	 if(sys_halfsec &&(led7_var.bFlashChar & BIT(i)))
	 temp=0;
     #endif
	 for(j=0;j<LED_8GRIDS;j++)	 
		 if(temp&BIT(j))
		 led7_var.bShowBuff1[led_8grid_value[i][j]>>8]|=led_8grid_value[i][j]; 
	 }
	 }
    #else   
	for(i=0;i<LED_8NUMS;i++){	
	if(i<LED_ICON_NUMS){
	 if(temp1&BIT(i))
	 led7_var.bShowBuff1[led_icon_value[i]>>8]|=led_icon_value[i];
	 }
	 
	temp=led7_var.bShowBuff[i];
    #ifdef SUPPORT_FLASH_CHAR
	if(sys_halfsec &&(led7_var.bFlashChar & BIT(i)))
	temp=0;
    #endif
	for(j=0;j<LED_8GRIDS;j++)	
		if(temp&BIT(j))
		led7_var.bShowBuff1[led_8grid_value[i][j]>>8]|=led_8grid_value[i][j];
	}	
   #endif
}


#elif defined(SUPPORT_HT1621C_MODE)
void LED_drive7(void)
{

#ifdef LED_ID_SD40C18SRB			  
	u16 temp2;
	u8 i,j,temp;
#else
	u8 i,j,temp,temp2,temp3;
#endif

    u16 temp1;

    led7_var.bShowBuff1[0]=0;
    led7_var.bShowBuff1[1]=0;
    led7_var.bShowBuff1[2]=0;
    led7_var.bShowBuff1[3]=0;
    led7_var.bShowBuff1[4]=0;
    led7_var.bShowBuff1[5]=0;
    led7_var.bShowBuff1[6]=0;
    led7_var.bShowBuff1[7]=0;
    led7_var.bShowBuff1[8]=0;
    led7_var.bShowBuff1[9]=0;
    led7_var.bShowBuff1[10]=0;
    led7_var.bShowBuff1[11]=0;
    led7_var.bShowBuff1[12]=0;  
    #if LED_COM_MAX>=14
    led7_var.bShowBuff1[13]=0;
    #endif
    #if LED_COM_MAX>=15
    led7_var.bShowBuff1[14]=0;    
    #endif
    if(compare_task_name("BtStackTask"))
     blueToothLedProc();
    #if defined(VFD_ID_YDL2001_35)||defined(LED_ID_JW2781)||defined(LED_ID_WLD007)
    LED_CIRCLE_PROCESS();
    #endif    
    #ifdef LED_VOLUME_ICON_PROCESS
	 LED_PROCESS_VOLUME_ICON();
	#endif

#if 0//LED_REPLAY
    if(compare_task_name("MusicTask"))
    
    if(play_mode==REPEAT_ONE)
    {
	       LED_STATUS|=LED_REPLAY;
	   #ifdef SUPPORT_FLASH_ICON
	       LED_FLASH_ICON|=LED_REPLAY;
	   #endif
    }
    else
	{
		LED_STATUS&=~LED_REPLAY;
		  #ifdef SUPPORT_FLASH_ICON
				LED_FLASH_ICON&=~LED_REPLAY;
		  #endif
  	  }
#endif

 #if LED_REPEAT_ONE||LED_REPEAT_ALL
 
 		LED_STATUS&=~(LED_REPEAT_ONE|LED_REPEAT_ALL);
 		 #ifdef SUPPORT_FLASH_ICON
 		 	LED_FLASH_ICON&=~LED_REPEAT_ONE;
 		 #endif
 		 
 	if(compare_task_name("MusicTask"))
 	{
 		if(play_mode==REPEAT_ONE)
 		{
 		    LED_STATUS|=LED_REPEAT_ONE;
 		    #ifdef SUPPORT_FLASH_ICON
 			LED_FLASH_ICON|=LED_REPEAT_ONE;
 		    #endif
 		}
 		else if(play_mode==REPEAT_ALL)
 			LED_STATUS|=LED_REPEAT_ALL;
 	}
 #endif
 
	  if(compare_task_name("IdleTask")){ 	 	  
      #if LED_SHOW_VFD
		setLedLight(LED_SHOW_VFD,led_mode_off,0);
		led7_var.bShowBuff1[0]&=~0x01;
		led7_var.bShowBuff1[0x06]&=~0x01;
		led7_var.bShowBuff1[0x04]&=~0x04;
		led7_var.bShowBuff1[0x02]&=~0x07;
      #endif
	  
      #if LED_POWER
        LED_STATUS&=~LED_POWER;
      #endif
      #if LED_VOLUME
	   LED_STATUS&=~LED_VOLUME;
      #endif
		}
	  else{
       #if LED_SHOW_VFD
		setLedLight(LED_SHOW_VFD,led_mode_on,0);
		led7_var.bShowBuff1[0]|=0x01;
		led7_var.bShowBuff1[0x06]|=0x01;
		led7_var.bShowBuff1[0x04]|=0x04;
		led7_var.bShowBuff1[0x02]|=0x07;
      #endif
     #if LED_POWER
        LED_STATUS|=LED_POWER;
     #endif
     #if LED_VOLUME
	  LED_STATUS|=LED_VOLUME;
     #endif
		}

    #ifdef LED_SCREEN_SHOW_BAT_STATUS
//	if(!compare_task_name("IdleTask"))
	 led7_show_bat_status();

    #endif
    #ifdef SUPPORT_MUTE_FLASH
    led7_mute_flash();
    #endif
  #if defined(LED_ID_JW2781)
    temp3=led7_var.bCircleBuf;
	if(sys_halfsec&&b_muteFlag)
	temp3=0;
#endif
 
	temp1=led7_var.wLedIcon;
    #ifdef SUPPORT_FLASH_ICON
	if(sys_halfsec &&led7_var.wFlashIcon)
	temp1&=~(led7_var.wFlashIcon);
    #endif

	

	#if LED_ICON_NUMS>=LED_8NUMS
	for(i=0;i<LED_ICON_NUMS;i++)
	{
		 if(temp1&BIT(i))
		 {
				 led7_var.bShowBuff1[led_icon_value[i]>>8]|=led_icon_value[i];		 
		             #ifdef LED_ID_JW8222_1B
		   	       if(i==9){         
		   			 led7_var.bShowBuff1[4]|=0x80;
		   			 led7_var.bShowBuff1[10]|=0x80;
		   			 led7_var.bShowBuff1[12]|=0x80;
		   	       }
		   	      #elif defined(LED_ID_JW5348_1A)
		   		  if(i==8){ 		
		   			led7_var.bShowBuff1[0x0a]|=0x80;
		   		  }	
		   	      #elif defined(LED_ID_WLD007)
		   		  if(i==8){ 		
		   			led7_var.bShowBuff1[0x03]|=0x02;
		   		  }	
				  
		   	      #elif defined(LED_ID_SD40C18SRB)
				  
		   		  if(i==8){ 		
		   			led7_var.bShowBuff1[0x0e]|=0x01;
		   		  }		
		   		  if(i==9){ 		
		   			led7_var.bShowBuff1[0x0c]|=0x01;
		   		  }						  
		   		  if(i==10){ 		
		   			led7_var.bShowBuff1[0x0a]|=0x01;
		   		  }						  
		            #endif
		 }
		 
		#if defined(LED_ID_JW2781) ||defined(LED_ID_WLD007) //circle process
			if(i<8 && (led7_var.bCircleBuf&BIT(i)))
				led7_var.bShowBuff1[led_circle_value[i]>>8]|=led_circle_value[i];
		#endif
	
	    #ifdef LED_EQ_BAR_SHOW
		     if(i<LED_EQ_NUMS)
			{
			        temp2=led7_var.bEqBarBuf[i];
			        for(j=0;j<LED_EQ_BAR_GRIDS;j++)
			          if(temp2&BIT(j))
			          led7_var.bShowBuff1[led_EQ[i][j]>>8]|=led_EQ[i][j];
		     }
		
	    #elif defined(SUPPORT_EQ_FREQUENCE)
		
		
	     temp2=led7_var.bEqIconBuf;
//	     temp2=0xff;
		
	     if(i<LED_EQ_NUMS)
	   {
	       if(temp2&BIT(i)){
		   	
	          #ifdef LED_ID_YUNKE01
		          switch(i){
		            case 0:
						led7_var.bShowBuff1[0x09]|=0x02;
						led7_var.bShowBuff1[0x0b]|=0x02;
						led7_var.bShowBuff1[0x08]|=0x04;
						led7_var.bShowBuff1[0x0d]|=0x02;
		            break;
		            case 1:
						led7_var.bShowBuff1[0x09]|=0x01;
						led7_var.bShowBuff1[0x0b]|=0x01;
						led7_var.bShowBuff1[0x08]|=0x02;
						led7_var.bShowBuff1[0x0d]|=0x01;
		            break;
		            case 2:
						led7_var.bShowBuff1[0x08]|=0x80;
						led7_var.bShowBuff1[0x0a]|=0x80;
						led7_var.bShowBuff1[0x08]|=0x01;
						led7_var.bShowBuff1[0x0c]|=0x80;
		            break;
		            case 3:
						led7_var.bShowBuff1[0x08]|=0x40;
						led7_var.bShowBuff1[0x0a]|=0x40;
						led7_var.bShowBuff1[0x0a]|=0x04;
						led7_var.bShowBuff1[0x0c]|=0x40;
		            break;
		            case 4:
						led7_var.bShowBuff1[0x08]|=0x20;
						led7_var.bShowBuff1[0x0a]|=0x20;
						led7_var.bShowBuff1[0x0a]|=0x02;
						led7_var.bShowBuff1[0x0c]|=0x20;
		            break;
		            case 5:
						led7_var.bShowBuff1[0x08]|=0x10;
						led7_var.bShowBuff1[0x0a]|=0x10;
						led7_var.bShowBuff1[0x0a]|=0x01;
						led7_var.bShowBuff1[0x0c]|=0x10;
		            break;
		            case 6:
						led7_var.bShowBuff1[0x08]|=0x08;
						led7_var.bShowBuff1[0x0a]|=0x08;
						led7_var.bShowBuff1[0x0c]|=0x04;
						led7_var.bShowBuff1[0x0c]|=0x08;
		            break;
		          }

	          #else
			  
	          led7_var.bShowBuff1[led_EQ[i]>>8]|=led_EQ[i];
			  
	          #ifdef LED_ID_JW8222_1B
	            if(i==2){
	              led7_var.bShowBuff1[6]|=0x40;
	              led7_var.bShowBuff1[8]|=0x10;
	            }
	            if(i==3){
	              led7_var.bShowBuff1[4]|=0x10;
	              led7_var.bShowBuff1[10]|=0x40;
	            }
	          #endif
			  
		#ifdef LED_ID_SD40C18SRB			  
	            if(i==7){
	              led7_var.bShowBuff1[0x0c]|=0x80;
	            }
	            if(i==8){
	              led7_var.bShowBuff1[0x0c]|=0x40;
	            }	
	            if(i==9){
	              led7_var.bShowBuff1[0x0c]|=0x20;
		  #endif
			  
	            }					
	        #endif
	       }
	     }
	    #endif


	
		 if(i<LED_8NUMS){
		 temp=led7_var.bShowBuff[i];
	     #ifdef SUPPORT_FLASH_CHAR
		 if(sys_halfsec &&(led7_var.bFlashChar & BIT(i)))
		 temp=0;
	     #endif
		 for(j=0;j<LED_8GRIDS;j++)	 
			 if(temp&BIT(j))
			 led7_var.bShowBuff1[led_8grid_value[i][j]>>8]|=led_8grid_value[i][j]; 
		 }
	 }
    #else   



 	for(i=0;i<LED_8NUMS;i++)
 	{	
 		if(i<LED_ICON_NUMS)
 		{
 			 if(temp1&BIT(i))
 			 led7_var.bShowBuff1[led_icon_value[i]>>8]|=led_icon_value[i];
 		 }
 		 
 		temp=led7_var.bShowBuff[i];
 	    #ifdef SUPPORT_FLASH_CHAR
 		if(sys_halfsec &&(led7_var.bFlashChar & BIT(i)))
 		temp=0;
 	    #endif
 		for(j=0;j<LED_8GRIDS;j++)	
 			if(temp&BIT(j))
 			led7_var.bShowBuff1[led_8grid_value[i][j]>>8]|=led_8grid_value[i][j];
 	}


   #endif
}
#elif defined(SUPPORT_TM1628_MODE)

void LED_drive7(void)
{

#ifdef LED_ID_SD40C18SRB			  
	u16 temp2;
	u8 i,j,temp;
#else
	u8 i,j,temp,temp2,temp3;
#endif

    u16 temp1;

    led7_var.bShowBuff1[0]=0;
    led7_var.bShowBuff1[1]=0;
    led7_var.bShowBuff1[2]=0;
    led7_var.bShowBuff1[3]=0;
    led7_var.bShowBuff1[4]=0;
    led7_var.bShowBuff1[5]=0;
    led7_var.bShowBuff1[6]=0;
    led7_var.bShowBuff1[7]=0;
    led7_var.bShowBuff1[8]=0;
    led7_var.bShowBuff1[9]=0;
    led7_var.bShowBuff1[10]=0;
    led7_var.bShowBuff1[11]=0;
    led7_var.bShowBuff1[12]=0;  
    #if LED_COM_MAX>=14
    led7_var.bShowBuff1[13]=0;
    #endif
    #if LED_COM_MAX>=15
    led7_var.bShowBuff1[14]=0;    
    #endif
    if(compare_task_name("BtStackTask"))
     blueToothLedProc();
    #if defined(VFD_ID_YDL2001_35)||defined(LED_ID_JW2781)||defined(LED_ID_WLD007)
    LED_CIRCLE_PROCESS();
    #endif    
    #ifdef LED_VOLUME_ICON_PROCESS
	 LED_PROCESS_VOLUME_ICON();
	#endif

#if 0//LED_REPLAY
    if(compare_task_name("MusicTask"))
    
    if(play_mode==REPEAT_ONE)
    {
	       LED_STATUS|=LED_REPLAY;
	   #ifdef SUPPORT_FLASH_ICON
	       LED_FLASH_ICON|=LED_REPLAY;
	   #endif
    }
    else
	{
		LED_STATUS&=~LED_REPLAY;
		  #ifdef SUPPORT_FLASH_ICON
				LED_FLASH_ICON&=~LED_REPLAY;
		  #endif
  	  }
#endif

 #if LED_REPEAT_ONE||LED_REPEAT_ALL
 
 		LED_STATUS&=~(LED_REPEAT_ONE|LED_REPEAT_ALL);
 		 #ifdef SUPPORT_FLASH_ICON
 		 	LED_FLASH_ICON&=~LED_REPEAT_ONE;
 		 #endif
 		 
 	if(compare_task_name("MusicTask"))
 	{
 		if(play_mode==REPEAT_ONE)
 		{
 		    LED_STATUS|=LED_REPEAT_ONE;
 		    #ifdef SUPPORT_FLASH_ICON
 			LED_FLASH_ICON|=LED_REPEAT_ONE;
 		    #endif
 		}
 		else if(play_mode==REPEAT_ALL)
 			LED_STATUS|=LED_REPEAT_ALL;
 	}
 #endif
 
	  if(compare_task_name("IdleTask")){ 	 	  
      #if LED_SHOW_VFD
		setLedLight(LED_SHOW_VFD,led_mode_off,0);
		led7_var.bShowBuff1[0]&=~0x01;
		led7_var.bShowBuff1[0x06]&=~0x01;
		led7_var.bShowBuff1[0x04]&=~0x04;
		led7_var.bShowBuff1[0x02]&=~0x07;
      #endif
	  
      #if LED_POWER
        LED_STATUS&=~LED_POWER;
      #endif
      #if LED_VOLUME
	   LED_STATUS&=~LED_VOLUME;
      #endif
		}
	  else{
       #if LED_SHOW_VFD
		setLedLight(LED_SHOW_VFD,led_mode_on,0);
		led7_var.bShowBuff1[0]|=0x01;
		led7_var.bShowBuff1[0x06]|=0x01;
		led7_var.bShowBuff1[0x04]|=0x04;
		led7_var.bShowBuff1[0x02]|=0x07;
      #endif
     #if LED_POWER
        LED_STATUS|=LED_POWER;
     #endif
     #if LED_VOLUME
	  LED_STATUS|=LED_VOLUME;
     #endif
		}

    #ifdef LED_SCREEN_SHOW_BAT_STATUS
//	if(!compare_task_name("IdleTask"))
	 led7_show_bat_status();

    #endif
    #ifdef SUPPORT_MUTE_FLASH
    led7_mute_flash();
    #endif
  #if defined(LED_ID_JW2781)
    temp3=led7_var.bCircleBuf;
	if(sys_halfsec&&b_muteFlag)
	temp3=0;
#endif
 
	temp1=led7_var.wLedIcon;
    #ifdef SUPPORT_FLASH_ICON
	if(sys_halfsec &&led7_var.wFlashIcon)
	temp1&=~(led7_var.wFlashIcon);
    #endif

	

	#if LED_ICON_NUMS>=LED_8NUMS
	for(i=0;i<LED_ICON_NUMS;i++)
	{
		 if(temp1&BIT(i))
		 {
				 led7_var.bShowBuff1[led_icon_value[i]>>8]|=led_icon_value[i];		 
		             #ifdef LED_ID_JW8222_1B
		   	       if(i==9){         
		   			 led7_var.bShowBuff1[4]|=0x80;
		   			 led7_var.bShowBuff1[10]|=0x80;
		   			 led7_var.bShowBuff1[12]|=0x80;
		   	       }
		   	      #elif defined(LED_ID_JW5348_1A)
		   		  if(i==8){ 		
		   			led7_var.bShowBuff1[0x0a]|=0x80;
		   		  }	
		   	      #elif defined(LED_ID_WLD007)
		   		  if(i==8){ 		
		   			led7_var.bShowBuff1[0x03]|=0x02;
		   		  }	
				  
		   	      #elif defined(LED_ID_SD40C18SRB)
				  
		   		  if(i==8){ 		
		   			led7_var.bShowBuff1[0x0e]|=0x01;
		   		  }		
		   		  if(i==9){ 		
		   			led7_var.bShowBuff1[0x0c]|=0x01;
		   		  }						  
		   		  if(i==10){ 		
		   			led7_var.bShowBuff1[0x0a]|=0x01;
		   		  }						  
		            #endif
		 }
		 
		#if defined(LED_ID_JW2781) ||defined(LED_ID_WLD007) //circle process
			if(i<8 && (led7_var.bCircleBuf&BIT(i)))
				led7_var.bShowBuff1[led_circle_value[i]>>8]|=led_circle_value[i];
		#endif
	
	    #ifdef LED_EQ_BAR_SHOW
		     if(i<LED_EQ_NUMS)
			{
			        temp2=led7_var.bEqBarBuf[i];
			        for(j=0;j<LED_EQ_BAR_GRIDS;j++)
			          if(temp2&BIT(j))
			          led7_var.bShowBuff1[led_EQ[i][j]>>8]|=led_EQ[i][j];
		     }
		
	    #elif defined(SUPPORT_EQ_FREQUENCE)
		
		
	     temp2=led7_var.bEqIconBuf;
//	     temp2=0xff;
		
	     if(i<LED_EQ_NUMS)
	   {
	       if(temp2&BIT(i)){
		   	
	          #ifdef LED_ID_YUNKE01
		          switch(i){
		            case 0:
						led7_var.bShowBuff1[0x09]|=0x02;
						led7_var.bShowBuff1[0x0b]|=0x02;
						led7_var.bShowBuff1[0x08]|=0x04;
						led7_var.bShowBuff1[0x0d]|=0x02;
		            break;
		            case 1:
						led7_var.bShowBuff1[0x09]|=0x01;
						led7_var.bShowBuff1[0x0b]|=0x01;
						led7_var.bShowBuff1[0x08]|=0x02;
						led7_var.bShowBuff1[0x0d]|=0x01;
		            break;
		            case 2:
						led7_var.bShowBuff1[0x08]|=0x80;
						led7_var.bShowBuff1[0x0a]|=0x80;
						led7_var.bShowBuff1[0x08]|=0x01;
						led7_var.bShowBuff1[0x0c]|=0x80;
		            break;
		            case 3:
						led7_var.bShowBuff1[0x08]|=0x40;
						led7_var.bShowBuff1[0x0a]|=0x40;
						led7_var.bShowBuff1[0x0a]|=0x04;
						led7_var.bShowBuff1[0x0c]|=0x40;
		            break;
		            case 4:
						led7_var.bShowBuff1[0x08]|=0x20;
						led7_var.bShowBuff1[0x0a]|=0x20;
						led7_var.bShowBuff1[0x0a]|=0x02;
						led7_var.bShowBuff1[0x0c]|=0x20;
		            break;
		            case 5:
						led7_var.bShowBuff1[0x08]|=0x10;
						led7_var.bShowBuff1[0x0a]|=0x10;
						led7_var.bShowBuff1[0x0a]|=0x01;
						led7_var.bShowBuff1[0x0c]|=0x10;
		            break;
		            case 6:
						led7_var.bShowBuff1[0x08]|=0x08;
						led7_var.bShowBuff1[0x0a]|=0x08;
						led7_var.bShowBuff1[0x0c]|=0x04;
						led7_var.bShowBuff1[0x0c]|=0x08;
		            break;
		          }

	          #else
			  
	          led7_var.bShowBuff1[led_EQ[i]>>8]|=led_EQ[i];
			  
	          #ifdef LED_ID_JW8222_1B
	            if(i==2){
	              led7_var.bShowBuff1[6]|=0x40;
	              led7_var.bShowBuff1[8]|=0x10;
	            }
	            if(i==3){
	              led7_var.bShowBuff1[4]|=0x10;
	              led7_var.bShowBuff1[10]|=0x40;
	            }
	          #endif
			  
		#ifdef LED_ID_SD40C18SRB			  
	            if(i==7){
	              led7_var.bShowBuff1[0x0c]|=0x80;
	            }
	            if(i==8){
	              led7_var.bShowBuff1[0x0c]|=0x40;
	            }	
	            if(i==9){
	              led7_var.bShowBuff1[0x0c]|=0x20;
		  #endif
			  
	            }					
	        #endif
	       }
	     }
	    #endif


	
		 if(i<LED_8NUMS){
		 temp=led7_var.bShowBuff[i];
	     #ifdef SUPPORT_FLASH_CHAR
		 if(sys_halfsec &&(led7_var.bFlashChar & BIT(i)))
		 temp=0;
	     #endif
		 for(j=0;j<LED_8GRIDS;j++)	 
			 if(temp&BIT(j))
			 led7_var.bShowBuff1[led_8grid_value[i][j]>>8]|=led_8grid_value[i][j]; 
		 }
	 }
    #else   



 	for(i=0;i<LED_8NUMS;i++)
 	{	
 		if(i<LED_ICON_NUMS)
 		{
 			 if(temp1&BIT(i))
 			 led7_var.bShowBuff1[led_icon_value[i]>>8]|=led_icon_value[i];
 		 }
 		 
 		temp=led7_var.bShowBuff[i];
 	    #ifdef SUPPORT_FLASH_CHAR
 		if(sys_halfsec &&(led7_var.bFlashChar & BIT(i)))
 		temp=0;
 	    #endif
 		for(j=0;j<LED_8GRIDS;j++)	
 			if(temp&BIT(j))
 			led7_var.bShowBuff1[led_8grid_value[i][j]>>8]|=led_8grid_value[i][j];
 	}


   #endif
}
#elif defined(LED_7PIN_MODE)||defined(LED_13PIN_MODE)
#if defined(LED_7PIN_PROMOTE_SPEED)
u8 GetIconID(u16 value)
{  
  u8 temp=0;
  switch(value){
    case 0x01:
    temp=0;
    break;
    case 0x02:
    temp=1;
    break;
    case 0x04:
    temp=2;
    break;
    case 0x08:
    temp=3;
    break;
    case 0x10:
    temp=4;
    break;
    case 0x20:
    temp=5;
    break;
    case 0x40:
    temp=6;
    break;
    case 0x80:
    temp=7;
    break;
    case 0x0100:
    temp=8;
    break;
    case 0x0200:
    temp=9;
    break;
  }
  return temp;
}
void LED_drive7(void)
{
    u8 i,j,temp;
    u16 temp1;

    led7_var.bShowBuff1[0]=0;
    led7_var.bShowBuff1[1]=0;
    led7_var.bShowBuff1[2]=0;
    led7_var.bShowBuff1[3]=0;
    led7_var.bShowBuff1[4]=0;
    led7_var.bShowBuff1[5]=0;
    led7_var.bShowBuff1[6]=0;
    
    if(compare_task_name("BtStackTask"))
     blueToothLedProc();


#ifdef SUPPORT_POWER_OFF_2POINT_FLASH
    if(compare_task_name("IdleTask"))
	led7_show_string_standby();
#endif

  #if REC_EN
    if((g_rec_ctl)&&(ENC_STOP != g_rec_ctl->enable))
    LED_STATUS|=LED_RECO;
    else
	LED_STATUS&=~LED_RECO;
  #endif

    
#if LED_REPLAY

#ifdef SUPPORT_REC_DELETE_FILTER_NOT_REC_FILE
if(!bIfRecordFolder)break;
#endif	

    if(compare_task_name("MusicTask"))
    
    if(play_mode==REPEAT_ONE)
    {
       LED_STATUS|=LED_REPLAY;
   #ifdef SUPPORT_FLASH_ICON
       LED_FLASH_ICON|=LED_REPLAY;
   #endif
    }
    else{
		LED_STATUS&=~LED_REPLAY;
  #ifdef SUPPORT_FLASH_ICON
		LED_FLASH_ICON&=~LED_REPLAY;
  #endif
    }
#endif

    #ifdef LED_SCREEN_SHOW_BAT_STATUS
	if(!compare_task_name("IdleTask"))
	 led7_show_bat_status();
	else
	LED_STATUS=0;
    #endif
    #ifdef SUPPORT_MUTE_FLASH
	    led7_mute_flash();
    #endif
	temp1=led7_var.wLedIcon;
    #ifdef SUPPORT_FLASH_ICON
	if(sys_halfsec &&led7_var.wFlashIcon)
	temp1&=~(led7_var.wFlashIcon);
    #endif

      if(temp1&LED_PLAY)led7_var.bShowBuff1[GetIconID(LED_PLAY)]|=LED_PLAY;
      if(temp1&LED_PAUSE)led7_var.bShowBuff1[GetIconID(LED_PAUSE)]|=LED_PAUSE;
      if(temp1&LED_USB)led7_var.bShowBuff1[GetIconID(LED_USB)]|=LED_USB;
      if(temp1&LED_SD)led7_var.bShowBuff1[GetIconID(LED_SD)]|=LED_SD;
      if(temp1&LED_FM)led7_var.bShowBuff1[GetIconID(LED_FM)]|=LED_FM;
      if(temp1&LED_2POINT)led7_var.bShowBuff1[GetIconID(LED_2POINT)]|=LED_2POINT;
      if(temp1&LED_DOT)led7_var.bShowBuff1[GetIconID(LED_DOT)]|=LED_DOT;

	 for(i=0;i<LED_8NUMS;i++){
	 temp=led7_var.bShowBuff[i];
   #ifdef SUPPORT_FLASH_CHAR
	 if(sys_halfsec &&(led7_var.bFlashChar & BIT(i)))
	 temp=0;
  #endif
	 for(j=0;j<LED_8GRIDS;j++)	 
		 if(temp&BIT(j))
		 led7_var.bShowBuff1[led_8grid_value[i][j]>>8]|=led_8grid_value[i][j]; 
	 }
}



#else
void LED_drive7(void)
{
    u8 i,j,temp;
    u16 temp1;
  #ifdef SUPPORT_EQ_FREQUENCE	 
  	u16 temp2;
  #endif
//	for(i=0;i<LED_COM_MAX;i++)
//		led7_var.bShowBuff1[i]=0;
    led7_var.bShowBuff1[0]=0;
    led7_var.bShowBuff1[1]=0;
    led7_var.bShowBuff1[2]=0;
    led7_var.bShowBuff1[3]=0;
    led7_var.bShowBuff1[4]=0;
    led7_var.bShowBuff1[5]=0;
    led7_var.bShowBuff1[6]=0;


#if defined(SUPPORT_EQ_FREQUENCE)
#ifdef support_aux_freq
	 if(workmode==LINE_WORK_MODE)
	 	{
		   if(UI_var.bCurMenu==MENU_AUX_MAIN)  		 	
	  			LED_FREQUENCE_PROCESS();
	 	}
	 else
	 	 led7_var.bEqIconBuf=0;
#else
	 LED_FREQUENCE_PROCESS();
#endif
#endif

	
    if(compare_task_name("BtStackTask"))
     blueToothLedProc();
  #if REC_EN
    if((g_rec_ctl)&&(ENC_STOP != g_rec_ctl->enable))
    LED_STATUS|=LED_RECO;
    else
	LED_STATUS&=~LED_RECO;
  #endif
#ifdef KOK_DETECT_USE_KEY
#ifdef LED_MIC_PRIORY
   if(g_kok_var.bKokKeyOpenFlag)      
	  LED_STATUS|=LED_MIC_PRIORY;
   else
	  LED_STATUS&=~LED_MIC_PRIORY;
#endif   
#endif

#ifdef SUPPORT_SSM_LED_REC_RECPLAY_ICON_SET
       if(compare_task_name("MusicTask"))
   	{
   #ifdef SUPPORT_REC_DELETE_FILTER_NOT_REC_FILE
   	if(bIfRecordFolder)
   #endif	
        	{
		           LED_STATUS|=LED_RECO;
		       #ifdef SUPPORT_FLASH_ICON
		           LED_FLASH_ICON|=LED_RECO;
		       #endif

		    		LED_STATUS&=~LED_REPLAY;
		      #ifdef SUPPORT_FLASH_ICON
		    		LED_FLASH_ICON&=~LED_REPLAY;
		      #endif	
	 	         if(play_mode==REPEAT_ONE)
	 	         {
	 	            LED_STATUS|=LED_REPLAY;
	 	 	       #ifdef SUPPORT_FLASH_ICON
	 	 	           LED_FLASH_ICON|=LED_REPLAY;
	 	 	       #endif
	 	         }
	 	         else{
	 	     		LED_STATUS&=~LED_REPLAY;
	 	 	       #ifdef SUPPORT_FLASH_ICON
	 	      		LED_FLASH_ICON&=~LED_REPLAY;
	 	 	       #endif
	 	         }			  
        	}
	   else
        	{
		        if(play_mode==REPEAT_ONE)
		        {
		           LED_STATUS|=LED_REPLAY;
		       #ifdef SUPPORT_FLASH_ICON
		           LED_FLASH_ICON|=LED_REPLAY;
		       #endif
		        }
		        else{
		    		LED_STATUS&=~LED_REPLAY;
		      #ifdef SUPPORT_FLASH_ICON
		    		LED_FLASH_ICON&=~LED_REPLAY;
		      #endif
		        }
		    	
        	}	   	
   	}
#elif defined SUPPORT_LED_RECPLAY_ICON_SHOW
       if(compare_task_name("MusicTask"))
   	{
	   #ifdef SUPPORT_REC_DELETE_FILTER_NOT_REC_FILE
	   	if(bIfRecordFolder)
	   #endif	
	        	{
		    		LED_STATUS|=LED_REPLAY;					  
	        	}
	        else
			{
				 LED_STATUS&=~LED_REPLAY;
			}			
   	}

#else
	#ifdef LED_REPLAY        
        if(compare_task_name("MusicTask"))
        
        if(play_mode==REPEAT_ONE)
        {
	           LED_STATUS|=LED_REPLAY;
	       #ifdef SUPPORT_FLASH_ICON
	           LED_FLASH_ICON|=LED_REPLAY;
	       #endif
        }
        else{
	    		LED_STATUS&=~LED_REPLAY;

	       #ifdef SUPPORT_FLASH_ICON
     		LED_FLASH_ICON&=~LED_REPLAY;
	       #endif
      }
    #endif
#endif


#if LED_REPEAT_ONE||LED_REPEAT_ALL
	LED_STATUS&=~(LED_REPEAT_ONE|LED_REPEAT_ALL);
#ifdef SUPPORT_FLASH_ICON
	LED_FLASH_ICON&=~LED_REPEAT_ONE;
#endif
	if(compare_task_name("MusicTask")){
	if(play_mode==REPEAT_ONE){
		LED_STATUS|=LED_REPEAT_ONE;
    #ifdef SUPPORT_FLASH_ICON
		LED_FLASH_ICON|=LED_REPEAT_ONE;
    #endif
		}
	else if(play_mode==REPEAT_ALL)
		LED_STATUS|=LED_REPEAT_ALL;
		}
#endif

    #ifdef LED_SCREEN_SHOW_BAT_STATUS
	if(!compare_task_name("IdleTask"))
	 led7_show_bat_status();
	else
	LED_STATUS=0;
    #endif
    #ifdef SUPPORT_MUTE_FLASH
    led7_mute_flash();
	
    #endif

	
	temp1=led7_var.wLedIcon;
    #ifdef SUPPORT_FLASH_ICON
	if(sys_halfsec &&led7_var.wFlashIcon)
	temp1&=~(led7_var.wFlashIcon);
    #endif

	 
	#if LED_EQ_NUMS >=LED_ICON_NUMS
	
		 	for(i=0;i<LED_EQ_NUMS;i++)
		 	{

			 	 #ifdef SUPPORT_EQ_FREQUENCE	 // LED_ID_27N60_8
		 		 	temp2=led7_var.bEqIconBuf;		 			   				 
		 		       if(temp2&BIT(i))	
		 		          led7_var.bShowBuff1[led_EQ[i]>>8]|=led_EQ[i];			 			   
			 	 #endif
		 	
		 		if(i<LED_ICON_NUMS)
		 		{
				 	temp1=led7_var.wLedIcon;
				     #ifdef SUPPORT_FLASH_ICON
				 	if(sys_halfsec &&led7_var.wFlashIcon)
				 	temp1&=~(led7_var.wFlashIcon);
				     #endif		 		
			 		 if(temp1&BIT(i))
			 		 {
			 			 led7_var.bShowBuff1[led_icon_value[i]>>8]|=led_icon_value[i];
			 		 }
		 		}
				 
		 		 if(i<LED_8NUMS)
				 {
			 		 temp=led7_var.bShowBuff[i];
			 	     #ifdef SUPPORT_FLASH_CHAR
			 		 if(sys_halfsec &&(led7_var.bFlashChar & BIT(i)))
			 			 temp=0;
			 	     #endif
			 		 for(j=0;j<LED_8GRIDS;j++)	 
			 			 if(temp&BIT(j))
			 			 led7_var.bShowBuff1[led_8grid_value[i][j]>>8]|=led_8grid_value[i][j]; 
		 		 }

				 
		 	 }


	#elif LED_ICON_NUMS>=LED_8NUMS

	 	for(i=0;i<LED_ICON_NUMS;i++)
	 	{
	 		 if(temp1&BIT(i))
	 		 {
	 			 led7_var.bShowBuff1[led_icon_value[i]>>8]|=led_icon_value[i];
	 			   #ifdef LED_ID_KF33T1
	 			     if(i==10){
	 			       led7_var.bShowBuff1[2]|=0x40;
	 			       led7_var.bShowBuff1[3]|=0x40;
	 			     }
	 			   #endif
	 		 }

			     #if defined(SUPPORT_EQ_FREQUENCE)
			      temp2=led7_var.bEqIconBuf;
			      if(i<LED_EQ_NUMS)
			 	   {
			 	        if(temp2&BIT(i))
			 			{
			 		 	   	
			 		           #ifdef LED_ID_JW4520_2A
			 		 		  
			 		           switch(i)
			 				 {
			 			             case 0:
			 			 				led7_var.bShowBuff1[0]|=0x30;					
			 			             break;
			 			             case 1:
			 			 				led7_var.bShowBuff1[0]|=0x06;
			 			             break;
			 			             case 2:
			 			 				led7_var.bShowBuff1[1]|=0x30;	
			 			             break;
			 			             case 3:
			 			 				led7_var.bShowBuff1[1]|=0x06;	 
			 			             break;
			 			             case 4:
			 			  				led7_var.bShowBuff1[2]|=0x30;
			 			            break;
			 			             case 5:
			 		 					led7_var.bShowBuff1[2]|=0x06;
			 		 			break;
			 			             case 6:
			 			 				led7_var.bShowBuff1[3]|=0x30;
			 			             break;				
			 			             case 7:
			 			 				led7_var.bShowBuff1[3]|=0x06;
			 			             break;
			 			           }
			 	        	  #endif
			 		 		  
			 		      }
			  		      }
			          #endif

		  
	 		 if(i<LED_8NUMS)
			 {
		 		 temp=led7_var.bShowBuff[i];
		 	     #ifdef SUPPORT_FLASH_CHAR
		 		 if(sys_halfsec &&(led7_var.bFlashChar & BIT(i)))
		 		 temp=0;
		 	     #endif
		 		 for(j=0;j<LED_8GRIDS;j++)	 
		 			 if(temp&BIT(j))
		 			 led7_var.bShowBuff1[led_8grid_value[i][j]>>8]|=led_8grid_value[i][j]; 
	 		 }
			 
	 	 }
   #else   
	for(i=0;i<LED_8NUMS;i++){	
	if(i<LED_ICON_NUMS){
	 if(temp1&BIT(i))
	 led7_var.bShowBuff1[led_icon_value[i]>>8]|=led_icon_value[i];
	 }
	 
	temp=led7_var.bShowBuff[i];
    #ifdef SUPPORT_FLASH_CHAR
	if(sys_halfsec &&(led7_var.bFlashChar & BIT(i)))
	temp=0;
    #endif
	for(j=0;j<LED_8GRIDS;j++)	
		if(temp&BIT(j))
		led7_var.bShowBuff1[led_8grid_value[i][j]>>8]|=led_8grid_value[i][j];
	}	
   #endif
}
#endif
#endif
/*----------------------------------------------------------------------------*/
/**@brief   LEDÃ‡Ã¥Ã†ÃÂºÂ¯ÃŠÃ½
   @param   xÂ£ÂºÃÃ”ÃŠÂ¾ÂºÃ¡Ã—Ã¸Â±Ãª
   @return  void
   @author  Change.tsai
   @note    void led7_clear(void)
*/
/*----------------------------------------------------------------------------*/



void led7_clear(void)
{
   #if defined(LED_7PIN_MODE)||defined(LED_13PIN_MODE)
	LED_INIT_PIN();
   #elif defined(SUPPORT_LCD_4COM_9SEG_MODE)||defined(SUPPORT_LCD_5COM_8SEG_MODE)
	   LCD_SEG_CLEAR();
	#elif  defined(SUPPORT_HT1621C_MODE)		
		HT1621_INIT() ;
   #endif
}
#if defined(SUPPORT_HT1628_DRIVER)||defined(SUPPORT_PT6312_MODE)||defined(SUPPORT_TM1628_MODE)

#define  delayus()  delay(5)
void AT(.comm) WR_HT1628_Byte(u8 data)
{
    u8 i;


    for(i=0; i<8; i++)
    {
        HT1628_DATA(data&0x01);
        HT1628_CLK(0);  //---------|
        delayus();
        data>>=1;//-------|
        HT1628_CLK(1);  ;//---------|___|----/Ã‰ÃÃ‰Ã½Ã‘Ã˜Ã“ÃÃÂ§
        delayus();
    }
    HT1628_DATA(0);
}



void AT(.comm) WR_HT1628_CMD(u8 cmd)
{


    HT1628_STB(0) ;//Ã†Â¬Ã‘Â¡Â£Â¬0Ã“ÃÃÂ§
    delayus();
    WR_HT1628_Byte(cmd);
    HT1628_STB(1);//Ã†Â¬Ã‘Â¡Â£Â¬0Ã“ÃÃÂ§
    HT1628_DATA(0);
    delayus();
    delayus();

}

#ifdef SUPPORT_TM1628_KEY_READ
u8 HT1628_READ_BYTE(void)
{
 u8 i,btemp=0;
 for(i=0;i<8;i++){   
   HT1628_CLK(0);  //---------|
   delayus();    
   delayus(); 
   HT1628_CLK(1);
   delayus(); 
   if(HT1628_DATA_READ())
   btemp|=BIT(i);
   delayus();   
   delayus();
}
  return btemp;
}
void HT1628_READ_KEY_PROCESS(void)
{
   u8 i;
   HT1628_STB(0);   
   delayus();
   WR_HT1628_Byte(0x42);
   delayus();
   delayus();
  // HT1628_DATA(1);
  // delayus();
   HT1628_DATA_IN();   
   delayus();
   for(i=0;i<TM1628_SCAN_BYTE;i++)
   	{
	   led7_var.wTm1628KeyData=((i<<8)|HT1628_READ_BYTE());
	   if(led7_var.wTm1628KeyData&0x00ff)break;
   }      
   delayus();
   HT1628_STB(1);
   HT1628_DATA_OUT();

   
}
 tu8 get_led_driver_key_value(void)
{

#if defined(LED_ID_JW2781_J_HD03_A)

#if 1


	if(led7_var.wTm1628KeyData==0x0002) return 5;  //mode
	if(led7_var.wTm1628KeyData==0x0110) return 4;  // prev
	if(led7_var.wTm1628KeyData==0x0202) return 0; // next 
	if(led7_var.wTm1628KeyData==0x0210) return 2; //  pp 
	
	  return 0xff;

#else
	printf("wTm1628KeyData:0x%04x	\n",led7_var.wTm1628KeyData);

	if(led7_var.wTm1628KeyData==0x0001) return 0;
	if(led7_var.wTm1628KeyData==0x0002) return 1;
	if(led7_var.wTm1628KeyData==0x0004) return 2;
	if(led7_var.wTm1628KeyData==0x0008) return 3;
	if(led7_var.wTm1628KeyData==0x0010) return 4;
	if(led7_var.wTm1628KeyData==0x0020) return 5;
	if(led7_var.wTm1628KeyData==0x0040) return 6;
	if(led7_var.wTm1628KeyData==0x0080) return 7;
	if(led7_var.wTm1628KeyData==0x0101) return 8;
	if(led7_var.wTm1628KeyData==0x0102) return 9;
	
#endif

  #endif
  
  return LED_KEY_NULL;
} 

#endif


#elif  defined(SUPPORT_HT1621C_MODE)

#define  delayus()  delay(5)

void WR_HT1621_DATA(u8 data,u8 cnt)
{
    u8 i;

    for(i=0; i<cnt; i++)
    {
         HT1621_CLK(0);  //---------|
        delayus();
       HT1621_DATA(data&0x80);
        delayus();
        HT1621_CLK(1);  ;
        delayus();
        data<<=1;//-------|
    }
}

void WR_HT1621_CMD(u8 cmd)
{

 
    HT1621_STB(0) ;
    delayus();
    WR_HT1621_DATA(0x80,4);
    WR_HT1621_DATA(cmd,8);
    HT1621_STB(1);
    delayus();

}

void WR_HT1621_ONE_DATA(u8 addr,u8 data)
{

    HT1621_STB(0) ;
    delayus();
    WR_HT1621_DATA(0xa0,3);// write data mark 101
    WR_HT1621_DATA(addr<<2,6); // write addr data
    WR_HT1621_DATA(addr<<4,4);	 // write data
    HT1621_STB(1);
    delayus();

}

void WR_HT1621_ALL_DATA(u8 addr,u8 *buf_p,u8 cnt)
{
u8 i;

    HT1621_STB(0) ;
    delayus();
    WR_HT1621_DATA(0xa0,3);// write data mark 101
    WR_HT1621_DATA(addr<<2,6); // write addr data

	for (i=0;i<cnt;i++)
	      {
		        WR_HT1621_DATA(*buf_p,8);  // write data
		        buf_p++;
	       }

    HT1621_STB(1);
}

/*
void lcd_backlight_ctrl(bool on)
{
	if(on){
    		LCD_BACKLIGHT_HIGH();
	}
	else{
    		LCD_BACKLIGHT_LOW();
	}
}
	*/
	
void  HT1621_INIT(void)
{
	HT1621_IO_INIT() ;
	
	delayus();
	WR_HT1621_CMD(HT1621_CMD_MODE);
	WR_HT1621_CMD(HT1621_CMD_RC_MODE); 
	WR_HT1621_CMD(HT1621_CMD_SYSDIS_OFF);
	WR_HT1621_CMD(HT1621_CMD_WDTDIS);	
	WR_HT1621_CMD(HT1621_CMD_SYSDIS_ON);
	WR_HT1621_CMD(HT1621_CMD_LCD_ON); 
		
}


#endif
#if defined(TF_2008A_HT1628)//||defined(TF_2025A)
void rgbLightOnOff(bool ifOn)
{
   u8 bData=0;
   if(ifOn)bData=0xff;
   else bData=0;
    led7_var.bLightDataBuf[0]=bData;
    led7_var.bLightDataBuf[1]=bData;
    led7_var.bLightDataBuf[2]=bData;
    led7_var.bLightDataBuf[3]=bData;
    led7_var.bLightDataBuf[4]=bData;
    led7_var.bLightDataBuf[5]=bData;
}
void ht1628_cotrol_rgb_show(u8 mode)
{
    static u8 max_period=0,cnt=0,cnt1=0;
    u8 temp=0;
    
  switch(mode){
    case 0://close all
    rgbLightOnOff(FALSE);
    break;
    case 1://all on
    rgbLightOnOff(true);
    break;
    case 2://all flash slow
	if(compare_task_name("FMRadioTask")) //ÃŠÃ•Ã’Ã´Â¸Ã‰ÃˆÃ…  
	{
		if(sys_halfsec)
		rgbLightOnOff(FALSE);
		else
		rgbLightOnOff(TRUE);
	} 	
	else{
    if(sys_halfsec)
    rgbLightOnOff(FALSE);
    else
	rgbLightOnOff(TRUE);
    }
    break;
    case 3://all flash fast
		if(compare_task_name("FMRadioTask")) //ÃŠÃ•Ã’Ã´Â¸Ã‰ÃˆÃ…  
		{
			if(sys_5sec)
			rgbLightOnOff(FALSE);
			else
			rgbLightOnOff(TRUE);
		} 	
		else{
    if(sys_5sec)
    rgbLightOnOff(FALSE);
    else
	rgbLightOnOff(TRUE);
	}
    break;
    case 4: //Â¶Ã¾Ã–Ã–ÂµÃ†ÃˆÃ½Â½Ã…Ã—Âª
    
	cnt++;
	if(compare_task_name("FMRadioTask")) //ÃŠÃ•Ã’Ã´Â¸Ã‰ÃˆÃ…  
	{if(cnt>2)cnt=0;} 	
	else
	{if(cnt>50)cnt=0;}
    if(cnt==0){
    if(max_period<5){
	temp=0x03;
    temp<<=max_period;
    led7_var.bLightDataBuf[0]=temp;
    led7_var.bLightDataBuf[4]=0;
    led7_var.bLightDataBuf[5]=temp;
    led7_var.bLightDataBuf[3]=0;
    led7_var.bLightDataBuf[2]=temp;
    led7_var.bLightDataBuf[1]=0;
    }else if(max_period<11){   
    temp=0x30;
	temp>>=(max_period-5);
    led7_var.bLightDataBuf[0]=0;
    led7_var.bLightDataBuf[4]=temp;
    led7_var.bLightDataBuf[5]=0;
    led7_var.bLightDataBuf[3]=temp;
    led7_var.bLightDataBuf[2]=0;
    led7_var.bLightDataBuf[1]=temp;
    }
	
    max_period++;
    if(max_period>10)
    max_period=0;
    }
    break;
    case 5://gbÃÃˆÃˆÂ«ÃÃÃ’Â»Ã–Ã–Â£Â¬ÂºÃ¬ÂµÃ†Ã‰Â¨ÃƒÃ¨Â²Â¢Â½Â«Ã‡Â°ÃƒÃ¦Ã‰ÃÂµÃ„ÂµÃ†Ã’Â»Â¸Ã¶Ã’Â»Â¸Ã¶ÃƒÃ°ÂµÃ´
      switch(cnt){
        case 0:        //all show green
        if(max_period!=0)break;
		led7_var.bLightDataBuf[0]=0x12;
		led7_var.bLightDataBuf[4]=0x12;
		led7_var.bLightDataBuf[5]=0x12;
		led7_var.bLightDataBuf[3]=0x12;
		led7_var.bLightDataBuf[2]=0x12;
		led7_var.bLightDataBuf[1]=0x12;
        break;
        case 1: //all show blue       
        if(max_period!=0)break;
			led7_var.bLightDataBuf[0]=0x24;
			led7_var.bLightDataBuf[4]=0x09;
			led7_var.bLightDataBuf[5]=0x24;
			led7_var.bLightDataBuf[3]=0x09;
			led7_var.bLightDataBuf[2]=0x24;
			led7_var.bLightDataBuf[1]=0x09;
        break;
      }
    cnt1++;
	if(compare_task_name("FMRadioTask")) //ÃŠÃ•Ã’Ã´Â¸Ã‰ÃˆÃ…  
	{if(cnt1>2)cnt1=0;} 	
	else
    {if(cnt1>30)cnt1=0;}
    if(cnt1==0){
      switch(max_period){
      case 0:      
	  led7_var.bLightDataBuf[0]|=0x01;
	  if(cnt==0)
	  led7_var.bLightDataBuf[0]&=~0x02;
	  else
	  led7_var.bLightDataBuf[0]&=~0x04;
      break;
      case 1:      
	  led7_var.bLightDataBuf[0]|=0x08;
	  if(cnt==0)
	  led7_var.bLightDataBuf[0]&=~0x10;
	  else
	  led7_var.bLightDataBuf[0]&=~0x20;
      break;
      case 2:      
	  led7_var.bLightDataBuf[4]|=0x20;
	  if(cnt==0)
	  led7_var.bLightDataBuf[4]&=~0x10;
	  else
	  led7_var.bLightDataBuf[4]&=~0x08;
      break;
      case 3:      
	  led7_var.bLightDataBuf[4]|=0x04;
	  if(cnt==0)
	  led7_var.bLightDataBuf[4]&=~0x02;
	  else
	  led7_var.bLightDataBuf[4]&=~0x01;
      break;
      case 4:      
	  led7_var.bLightDataBuf[5]|=0x01;
	  if(cnt==0)
	  led7_var.bLightDataBuf[5]&=~0x02;
	  else
	  led7_var.bLightDataBuf[5]&=~0x04;
      break;
      case 5:      
	  led7_var.bLightDataBuf[5]|=0x08;
	  if(cnt==0)
	  led7_var.bLightDataBuf[5]&=~0x10;
	  else
	  led7_var.bLightDataBuf[5]&=~0x20;
      break;
      case 6:      
	  led7_var.bLightDataBuf[3]|=0x20;
	  if(cnt==0)
	  led7_var.bLightDataBuf[3]&=~0x10;
	  else
	  led7_var.bLightDataBuf[3]&=~0x08;
      break;
      case 7:      
	  led7_var.bLightDataBuf[3]|=0x04;
	  if(cnt==0)
	  led7_var.bLightDataBuf[3]&=~0x02;
	  else
	  led7_var.bLightDataBuf[3]&=~0x01;
      break;
      case 8:      
	  led7_var.bLightDataBuf[2]|=0x01;
	  if(cnt==0)
	  led7_var.bLightDataBuf[2]&=~0x02;
	  else
	  led7_var.bLightDataBuf[2]&=~0x04;
      break;
      case 9:      
	  led7_var.bLightDataBuf[2]|=0x08;
	  if(cnt==0)
	  led7_var.bLightDataBuf[2]&=~0x10;
	  else
	  led7_var.bLightDataBuf[2]&=~0x20;
      break;
      case 10:      
	  led7_var.bLightDataBuf[1]|=0x20;
	  if(cnt==0)
	  led7_var.bLightDataBuf[1]&=~0x10;
	  else
	  led7_var.bLightDataBuf[1]&=~0x08;
      break;
      case 11:      
	  led7_var.bLightDataBuf[1]|=0x04;
	  if(cnt==0)
	  led7_var.bLightDataBuf[1]&=~0x02;
	  else
	  led7_var.bLightDataBuf[1]&=~0x01;
      break;
      }
      
	  max_period++;
	  if(max_period>11){
	  max_period=0;
	  if(cnt)cnt=0;
	  else cnt=1;
	  }
    }
    break;    
    case 6:
		  switch(cnt){
			case 0: 	   //all show green
			if(max_period!=0)break;
			led7_var.bLightDataBuf[0]=0x12;
			led7_var.bLightDataBuf[4]=0x12;
			led7_var.bLightDataBuf[5]=0x12;
			led7_var.bLightDataBuf[3]=0x12;
			led7_var.bLightDataBuf[2]=0x12;
			led7_var.bLightDataBuf[1]=0x12;
			break;
			case 1: //all show blue 	  
			if(max_period!=0)break;
				led7_var.bLightDataBuf[0]=0x24;
				led7_var.bLightDataBuf[4]=0x09;
				led7_var.bLightDataBuf[5]=0x24;
				led7_var.bLightDataBuf[3]=0x09;
				led7_var.bLightDataBuf[2]=0x24;
				led7_var.bLightDataBuf[1]=0x09;
			break;
		  }
		cnt1++;
		if(compare_task_name("FMRadioTask")) //ÃŠÃ•Ã’Ã´Â¸Ã‰ÃˆÃ…  
		{if(cnt1>1)cnt1=0;}		
		else
		{if(cnt1>30)cnt1=0;}		
		if(cnt1==0){
		  switch(max_period){
		  case 0:	   
		  led7_var.bLightDataBuf[0]|=0x01;//r
		  led7_var.bLightDataBuf[3]|=0x20;
		  led7_var.bLightDataBuf[5]&=~0x08;
		  led7_var.bLightDataBuf[1]&=~0x04;

		  if(cnt==0){//Â¶Ã”Ã‰Â¨Ã€Â¶ÂµÃ†		  
  		  led7_var.bLightDataBuf[4]&=~0x01;//r
  		  led7_var.bLightDataBuf[2]&=~0x20;
		  led7_var.bLightDataBuf[5]|=0x04;//r
		  led7_var.bLightDataBuf[1]|=0x08;
		  }else{//Â¶Ã”Ã‰Â¨Ã‚ÃŒÂµÃ†		  
		  led7_var.bLightDataBuf[4]&=~0x02;//r
		  led7_var.bLightDataBuf[2]&=~0x10;
		  led7_var.bLightDataBuf[5]|=0x02;//r
		  led7_var.bLightDataBuf[1]|=0x10;
		  }
		  
		  break;
		  case 1:		  
			  led7_var.bLightDataBuf[0]|=0x08;
			  led7_var.bLightDataBuf[3]|=0x04;
			  led7_var.bLightDataBuf[0]&=~0x01;
			  led7_var.bLightDataBuf[3]&=~0x20;
			  if(cnt==0){//Â¶Ã”Ã‰Â¨Ã€Â¶ÂµÃ† 	  
			  led7_var.bLightDataBuf[5]&=~0x04;//r
			  led7_var.bLightDataBuf[1]&=~0x08;
			  led7_var.bLightDataBuf[5]|=0x20;//r
			  led7_var.bLightDataBuf[1]|=0x01;
			  }else{//Â¶Ã”Ã‰Â¨Ã‚ÃŒÂµÃ†
				  led7_var.bLightDataBuf[5]&=~0x02;//r
				  led7_var.bLightDataBuf[1]&=~0x10;
				  led7_var.bLightDataBuf[5]|=0x10;//r
				  led7_var.bLightDataBuf[1]|=0x02;
			  }
		  break;
		  case 2:	   
			  led7_var.bLightDataBuf[4]|=0x20;
			  led7_var.bLightDataBuf[2]|=0x01;
			  led7_var.bLightDataBuf[0]&=~0x08;
			  led7_var.bLightDataBuf[3]&=~0x04;
			  if(cnt==0){//Â¶Ã”Ã‰Â¨Ã€Â¶ÂµÃ† 	  
			  led7_var.bLightDataBuf[5]&=~0x20;//r
			  led7_var.bLightDataBuf[1]&=~0x01;
			  led7_var.bLightDataBuf[0]|=0x04;//r
			  led7_var.bLightDataBuf[3]|=0x08;
			  }else{//Â¶Ã”Ã‰Â¨Ã‚ÃŒÂµÃ†
				  led7_var.bLightDataBuf[5]&=~0x10;//r
				  led7_var.bLightDataBuf[1]&=~0x02;
				  led7_var.bLightDataBuf[0]|=0x02;//r
				  led7_var.bLightDataBuf[3]|=0x10;
			  }
		  break;
		  case 3:
			  led7_var.bLightDataBuf[4]|=0x04;
			  led7_var.bLightDataBuf[2]|=0x08;
			  led7_var.bLightDataBuf[4]&=~0x20;
			  led7_var.bLightDataBuf[2]&=~0x01;
			  if(cnt==0){//Â¶Ã”Ã‰Â¨Ã€Â¶ÂµÃ† 	
			  led7_var.bLightDataBuf[0]&=~0x04;//r
			  led7_var.bLightDataBuf[3]&=~0x08;
			  led7_var.bLightDataBuf[0]|=0x20;//r
			  led7_var.bLightDataBuf[3]|=0x01;
			  }else{//Â¶Ã”Ã‰Â¨Ã‚ÃŒÂµÃ†
				  led7_var.bLightDataBuf[0]&=~0x02;//r
				  led7_var.bLightDataBuf[3]&=~0x10;
				  led7_var.bLightDataBuf[0]|=0x10;//r
				  led7_var.bLightDataBuf[3]|=0x02;
			  }
		  break;
		  case 4:	   
			  led7_var.bLightDataBuf[5]|=0x01;
			  led7_var.bLightDataBuf[1]|=0x20;
			  led7_var.bLightDataBuf[4]&=~0x04;
			  led7_var.bLightDataBuf[2]&=~0x08;
			  if(cnt==0){//Â¶Ã”Ã‰Â¨Ã€Â¶ÂµÃ† 	  			  
			  led7_var.bLightDataBuf[0]&=~0x20;//r
			  led7_var.bLightDataBuf[3]&=~0x01;
			  led7_var.bLightDataBuf[4]|=0x08;//r
			  led7_var.bLightDataBuf[2]|=0x04;
			  }else{//Â¶Ã”Ã‰Â¨Ã‚ÃŒÂµÃ†
				  led7_var.bLightDataBuf[0]&=~0x10;//r
				  led7_var.bLightDataBuf[3]&=~0x02;
				  led7_var.bLightDataBuf[4]|=0x10;//r
				  led7_var.bLightDataBuf[2]|=0x02;
			  }
		  break;
		  case 5:
			  led7_var.bLightDataBuf[5]|=0x08;
			  led7_var.bLightDataBuf[1]|=0x04;
			  led7_var.bLightDataBuf[5]&=~0x01;
			  led7_var.bLightDataBuf[1]&=~0x20;
			  if(cnt==0){//Â¶Ã”Ã‰Â¨Ã€Â¶ÂµÃ† 	  
				  led7_var.bLightDataBuf[4]&=~0x08;//r
				  led7_var.bLightDataBuf[2]&=~0x04;
			  led7_var.bLightDataBuf[4]|=0x01;//r
			  led7_var.bLightDataBuf[2]|=0x20;
			  }else{//Â¶Ã”Ã‰Â¨Ã‚ÃŒÂµÃ†
				  led7_var.bLightDataBuf[4]&=~0x10;//r
				  led7_var.bLightDataBuf[2]&=~0x02;
				  led7_var.bLightDataBuf[4]|=0x02;//r
				  led7_var.bLightDataBuf[2]|=0x10;
			  }
		  break;
		  }
		  
		  max_period++;
		  if(max_period>5){
		  max_period=0;
		  if(cnt)cnt=0;
		  else cnt=1;
		  }
		}
		break;	  
    break;
    case 7://ÃˆÃ½Ã–Ã–ÂµÃ†ÃˆÃ½Â½Ã…Ã—Âª
    
	cnt++;
	if(compare_task_name("FMRadioTask")) //ÃŠÃ•Ã’Ã´Â¸Ã‰ÃˆÃ…  
	{if(cnt>1)cnt=0;}
	else
	{if(cnt>80)cnt=0;}
    if(cnt==1){
    if(max_period<4){
	temp=0x07;
    temp<<=max_period;
    led7_var.bLightDataBuf[0]=temp;
    led7_var.bLightDataBuf[4]=0;
    led7_var.bLightDataBuf[5]=temp;
    led7_var.bLightDataBuf[3]=0;
    led7_var.bLightDataBuf[2]=temp;
    led7_var.bLightDataBuf[1]=0;
    }else if(max_period<10){   
    temp=0x70;
	temp>>=(max_period-4);
    led7_var.bLightDataBuf[0]=0;
    led7_var.bLightDataBuf[4]=temp;
    led7_var.bLightDataBuf[5]=0;
    led7_var.bLightDataBuf[3]=temp;
    led7_var.bLightDataBuf[2]=0;
    led7_var.bLightDataBuf[1]=temp;
    }
	
    max_period++;
    if(max_period>9)
    max_period=0;
    }
    break;
  }
}
void show_rgb(void)
{
  static u16 cnt=0,time_interval=30;
  
  if(compare_task_name("FMRadioTask")){ //ÃŠÃ•Ã’Ã´Â¸Ã‰ÃˆÃ…  
	if(cnt<time_interval*1)
	ht1628_cotrol_rgb_show(1);
	else if(cnt<time_interval*2)
		ht1628_cotrol_rgb_show(2);
	else if(cnt<time_interval*5)
		ht1628_cotrol_rgb_show(3);
	else if(cnt<time_interval*8)
		ht1628_cotrol_rgb_show(4);
	else if(cnt<time_interval*11)
		ht1628_cotrol_rgb_show(5);
	else if(cnt<time_interval*14)
		ht1628_cotrol_rgb_show(6);
	else if(cnt<time_interval*17)
		ht1628_cotrol_rgb_show(7);
   cnt++;
  if(cnt>=time_interval*17)cnt=time_interval;	
  }else{
  if(cnt<800*1)
  ht1628_cotrol_rgb_show(1);
  else if(cnt<800*2)
	  ht1628_cotrol_rgb_show(2);
  else if(cnt<800*5)
	  ht1628_cotrol_rgb_show(3);
  else if(cnt<800*8)
	  ht1628_cotrol_rgb_show(4);
  else if(cnt<800*11)
	  ht1628_cotrol_rgb_show(5);
  else if(cnt<800*14)
	  ht1628_cotrol_rgb_show(6);
  else if(cnt<800*17)
	  ht1628_cotrol_rgb_show(7);
 cnt++;
if(cnt>=800*17)cnt=800;	  
}
}
void ht1628_scan(void)
{
     u8 i;
     HT1628_IO_INIT();
     
#ifdef USE_KEY_TO_CONTROL_HT1628_LIGHTS_ONOFF
    if(ifRunTimer)
    show_rgb();
    else
    rgbLightOnOff(FALSE);
#else
show_rgb();
#endif
    // ht1628_cotrol_rgb_show(6);
	 WR_HT1628_CMD(HT1628_CMD_MODE);	
	 WR_HT1628_CMD(HT1628_CMD_SPEC_ADDR);
	for(i=0;i<6;i++){
	   HT1628_STB(0);
	   WR_HT1628_Byte(HT1628_CMD_ADDR_SET+2*i);//ÃÃ”ÃŠÂ¾ÃŠÃ½Â¾Ã	add-C0	C2
	   WR_HT1628_Byte(led7_var.bLightDataBuf[i]);
	   HT1628_STB(1);
		   }
	   WR_HT1628_CMD(0x8f);//Ã‹ÃÃÃÂ¶ÃˆÃ–Â¸ÃÃ®
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief   LEDÃ‰Â¨ÃƒÃ¨ÂºÂ¯ÃŠÃ½
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_scan(void)
*/
/*----------------------------------------------------------------------------*/


const u8 Ht1621Tab[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const u8 Ht1621Tab1[]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
const u8 Ht1621Tab2[]={0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f};
void led7_scan(void)
{

#if defined(SUPPORT_LCD_4COM_9SEG_MODE)||defined(SUPPORT_LCD_5COM_8SEG_MODE)


	LED_drive7();

	COM0_SEG(led7_var.bShowBuff1[0]);
	COM1_SEG(led7_var.bShowBuff1[1]);
	COM2_SEG(led7_var.bShowBuff1[2]);
	COM3_SEG(led7_var.bShowBuff1[3]);
	#if defined(SUPPORT_LCD_5COM_8SEG_MODE)
	COM4_SEG(led7_var.bShowBuff1[4]);
	#endif
	
#elif defined(SUPPORT_PT6312_MODE)
	   #ifdef TEST_PANEL_LED
	   	static u8 flash_cnt=0,cnt=0;                                     
	   	u8 i,j,seg;	 	 
	   	cnt++;	
	   	HT1628_IO_INIT();
	   #ifdef TEST_SHOW_ALL
	   //  HT1628_IO_INIT();
	    // HT1628_CLK(1);
	    // HT1628_DATA(1);
	    // HT1628_STB(1);
	      #if 1
	   	WR_HT1628_CMD(0x02);										   
	   	for(i=0;i<LED_COM_MAX;i++){
	   		HT1628_STB(0) ;
	   		WR_HT1628_Byte(0xc0+i);//ÏÔÊ¾Êý¾Ý	add-C0	C2
	   		WR_HT1628_Byte(0xff);
	   		HT1628_STB(1) ;
	   	}
	   	 WR_HT1628_CMD(0x8f);//ËÍÁÁ¶ÈÖ¸Áî
	   #endif
	   #else
	   	WR_HT1628_CMD(0x02);//ÏÔÊ¾Ä£Ê½  7Î» 10¶Î
	   	HT1628_STB(0) ;//Æ¬Ñ¡£¬0ÓÐÐ§
	   	if(cnt>=LED_COM_MAX) cnt=0;
	   	if(bledComValue==cnt)
	   	{   flash_cnt++;
	   		WR_HT1628_Byte(0xc0+cnt);//ÏÔÊ¾Êý¾ÝµØÖ·
	   		if(flash_cnt<10){
	   		WR_HT1628_Byte(0xff);//ÏÔÊ¾Êý¾Ý	  add-0
	   		}
	   		else{
	   		if(flash_cnt==20)flash_cnt=0;
	   		WR_HT1628_Byte(0xff&(~BIT(bledGridValue)));//ÏÔÊ¾Êý¾Ý	  add-0
	   	  	}											 
	   	}
	   	else
	   	{
	   		WR_HT1628_Byte(0xc0+cnt);//ÏÔÊ¾Êý¾ÝµØÖ·
	   		WR_HT1628_Byte(0);//ÏÔÊ¾Êý¾Ý	  add-0
	   	}
	   	HT1628_STB(1) ;//Æ¬Ñ¡£¬1ÊÍ·Å
	   	delayus();
	   	delayus();
	   	WR_HT1628_CMD(0x8f);//ËÍÁÁ¶ÈÖ¸Áî
	   #endif
	   #else
	   static u8	cnt=0;//,
	   u8 i;
	   
	   switch(cnt){
	   case 0:
	   /*vfd mem show proc*/  
	   //LED7_DRIVE_disp_eq();
	   #ifdef support_freq_display
	   //Disp_freq();
	   #endif
	   #ifdef LED_EQ_BAR_SHOW
	    LED_EQ_BAR_PROCESS(led7_var.bEqMode);
	   #endif
	   LED_drive7();
	   
	   break;				
	   case 1:
	   HT1628_IO_INIT();
	   WR_HT1628_CMD(0x02);											
	   for(i=0;i<LED_COM_MAX;i++){
	   HT1628_STB(0) ;
	   WR_HT1628_Byte(0xc0+i);//ÏÔÊ¾Êý¾Ý	 add-C0  C2
	   WR_HT1628_Byte(led7_var.bShowBuff1[i]);
	   HT1628_STB(1) ;
	   }
	   WR_HT1628_CMD(0x8f);//ËÍÁÁ¶ÈÖ¸Áî
	   //show_led_light(pt6311_led_byte);
	   // READ_tw1628_KEY();	  
	   break;
	   }
	   cnt++;
	   if(cnt>1) cnt=0;
	   #endif
  
#elif defined(SUPPORT_HT1621C_MODE)

#if 1//def TEST_PANEL_LED



	HT1621_IO_INIT() ;
	WR_HT1621_ALL_DATA(0,Ht1621Tab2,16); 
//    WR_HT1621_ALL_DATA(0,Ht1621Tab1,16); 

   
#else

		 static u8	cnt=0;//,
		 u8 i;
		 
		 
		 switch(cnt){
		 case 0:

		 LED_drive7();
		 break;				
		 case 1:
		 HT1628_IO_INIT();
		 WR_HT1628_CMD(0x28);		// 1/2  4com
		 WR_HT1628_CMD(0x44); //auto increment
		  // WR_HT1628_CMD(0xc0);//ÏÔÊ¾µØÖ·    add-b
		   for(i=0;i<3;i++){  
		   HT1628_STB(0) ;
		   WR_HT1628_Byte(0xc0+i);//ÏÔÊ¾Êý¾Ý  add-C0  C2
		 WR_HT1628_Byte(led7_var.bShowBuff1[i]);
		 HT1628_STB(1) ;
		 }
		 break;
		 case 2:
		 	  for(i=3;i<6;i++)
		 		  {  
		 			HT1628_STB(0) ;
		 			WR_HT1628_Byte(0xc0+i);//ÏÔÊ¾Êý¾Ý  add-C0  C2
		 		  WR_HT1628_Byte(led7_var.bShowBuff1[i]);
		 		  HT1628_STB(1) ;
		 		  }
		 break;
		 case 3:
		 	  for(i=6;i<9;i++)
		 		  {  
		 			HT1628_STB(0) ;
		 			WR_HT1628_Byte(0xc0+i);//ÏÔÊ¾Êý¾Ý  add-C0  C2
		 		  WR_HT1628_Byte(led7_var.bShowBuff1[i]);
		 		  HT1628_STB(1) ;
		 		  }
		 break;
		 #if LED_COM_MAX==13
		 case 4:
		 	  for(i=9;i<LED_COM_MAX;i++)
		 		  {  
		 			HT1628_STB(0) ;
		 			WR_HT1628_Byte(0xc0+i);//ÏÔÊ¾Êý¾Ý  add-C0  C2
		 		  WR_HT1628_Byte(led7_var.bShowBuff1[i]);
		 		  HT1628_STB(1) ;
		 		  }
		 	WR_HT1628_CMD(0x8f);//ËÍÁÁ¶ÈÖ¸Áî
		 break;
		 
		 #ifdef SUPPORT_TM1628_KEY_READ
		 case 5:
		   HT1628_READ_KEY_PROCESS();
		   break;
		 #endif
		 
		 
		 #else
		 case 4:
		 	  for(i=9;i<12;i++)
		 		  {  
		 			HT1628_STB(0) ;
		 			WR_HT1628_Byte(0xc0+i);//ÏÔÊ¾Êý¾Ý  add-C0  C2
		 		  WR_HT1628_Byte(led7_var.bShowBuff1[i]);
		 		  HT1628_STB(1) ;
		 		  }
		 break;
		 
		 case 5:
		 	  for(i=12;i<LED_COM_MAX;i++)
		 		  {  
		 			HT1628_STB(0) ;
		 			WR_HT1628_Byte(0xc0+i);//ÏÔÊ¾Êý¾Ý  add-C0  C2
		 		  WR_HT1628_Byte(led7_var.bShowBuff1[i]);
		 		  HT1628_STB(1) ;
		 		  }
		 	WR_HT1628_CMD(0x8f);//ËÍÁÁ¶ÈÖ¸Áî
		 break;
		 #ifdef SUPPORT_TM1628_KEY_READ
		 case 6:
		   HT1628_READ_KEY_PROCESS();
		   break;
		 #endif
		 
		 #endif
		 }
		 cnt++;
		 #if LED_COM_MAX==13 
		   #ifdef SUPPORT_TM1628_KEY_READ
		    if(cnt>5) cnt=0;
		   #else
		    if(cnt>4) cnt=0;
		   #endif
		 #else
		    #ifdef SUPPORT_TM1628_KEY_READ
		    if(cnt>6) cnt=0;
		    #else
		    if(cnt>5) cnt=0;
		    #endif
		 #endif


#endif

#elif defined(SUPPORT_TM1628_MODE)

#ifdef TEST_PANEL_LED
	 	static u8 flash_cnt=0,cnt=0;                                     
	 	u8 i,j,seg;	 	 
	 	cnt++;	
	 	HT1628_IO_INIT();
		 #ifdef TEST_SHOW_ALL
		 //  HT1628_IO_INIT();
		  // HT1628_CLK(1);
		  // HT1628_DATA(1);
		  // HT1628_STB(1);
		    #if 1
		 	WR_HT1628_CMD(TM1628_MODE);										   
		 	for(i=0;i<LED_COM_MAX;i++){
		 		HT1628_STB(0) ;
		 		WR_HT1628_Byte(0xc0+i);//ÏÔÊ¾Êý¾Ý	add-C0	C2
		 		WR_HT1628_Byte(0xff);
		 		HT1628_STB(1) ;
		 	}
		 	 WR_HT1628_CMD(0x8f);//ËÍÁÁ¶ÈÖ¸Áî
		 #endif
		 #else	
		 	WR_HT1628_CMD(TM1628_MODE);//ÏÔÊ¾Ä£Ê½  7Î» 10¶Î
		 	HT1628_STB(0) ;//Æ¬Ñ¡£¬0ÓÐÐ§
		 	if(cnt>14) cnt=0;
		 	if(bledComValue==cnt)
		 	{   //flash_cnt++;
		 		WR_HT1628_Byte(0xc0+cnt);//ÏÔÊ¾Êý¾ÝµØÖ·
		 //		if(flash_cnt<10){
		 //		WR_HT1628_Byte(0xff);//ÏÔÊ¾Êý¾Ý	  add-0
		 //		}
		 //		else{
		 //		if(flash_cnt==20)flash_cnt=0;
		 //		WR_HT1628_Byte(0xff&(~BIT(bledGridValue)));//ÏÔÊ¾Êý¾Ý	  add-0
		 //	  	}											 
		 		WR_HT1628_Byte(BIT(bledGridValue));//ÏÔÊ¾Êý¾Ý	  add-0
		 	}
		 	else
		 	{
		 		WR_HT1628_Byte(0xc0+cnt);//ÏÔÊ¾Êý¾ÝµØÖ·
		 		WR_HT1628_Byte(0);//ÏÔÊ¾Êý¾Ý	  add-0
		 	}
		 	HT1628_STB(1) ;//Æ¬Ñ¡£¬1ÊÍ·Å
		 	delayus();
		 	delayus();
		 	WR_HT1628_CMD(0x8f);//ËÍÁÁ¶ÈÖ¸Áî
		 #endif
#else
static u8	cnt=0;//,
u8 i;

#if defined LED_ID_YUNKE01||defined LED_ID_JM_4169_B||defined LED_ID_DOUBLE_PANEL\
	||defined LED_ID_SD40C18SRB||defined LED_ID_JW2781||defined LED_ID_ZX001\
	||defined LED_ID_JW1676_1B||defined LED_ID_WLD007
switch(cnt){
case 0:
/*vfd mem show proc*/  
//LED7_DRIVE_disp_eq();
#ifdef support_freq_display
//Disp_freq();
#endif
#ifdef LED_EQ_BAR_SHOW
 LED_EQ_BAR_PROCESS(led7_var.bEqMode);
#elif defined(SUPPORT_EQ_FREQUENCE)
#if 0//defined(LED_ID_DOUBLE_PANEL)
#else
	 LED_FREQUENCE_PROCESS();
#endif

#endif
LED_drive7();
break;				
case 1:
HT1628_IO_INIT();
WR_HT1628_CMD(TM1628_MODE);		
WR_HT1628_CMD(0x44); //auto increment
 // WR_HT1628_CMD(0xc0);//ÏÔÊ¾µØÖ·    add-b
  for(i=0;i<3;i++){  
  HT1628_STB(0) ;
  WR_HT1628_Byte(0xc0+i);//ÏÔÊ¾Êý¾Ý  add-C0  C2
WR_HT1628_Byte(led7_var.bShowBuff1[i]);
HT1628_STB(1) ;
}
break;
case 2:
	  for(i=3;i<6;i++)
		  {  
			HT1628_STB(0) ;
			WR_HT1628_Byte(0xc0+i);//ÏÔÊ¾Êý¾Ý  add-C0  C2
		  WR_HT1628_Byte(led7_var.bShowBuff1[i]);
		  HT1628_STB(1) ;
		  }
break;
case 3:
	  for(i=6;i<9;i++)
		  {  
			HT1628_STB(0) ;
			WR_HT1628_Byte(0xc0+i);//ÏÔÊ¾Êý¾Ý  add-C0  C2
		  WR_HT1628_Byte(led7_var.bShowBuff1[i]);
		  HT1628_STB(1) ;
		  }
break;
#if LED_COM_MAX==13
case 4:
	  for(i=9;i<LED_COM_MAX;i++)
		  {  
			HT1628_STB(0) ;
			WR_HT1628_Byte(0xc0+i);//ÏÔÊ¾Êý¾Ý  add-C0  C2
		  WR_HT1628_Byte(led7_var.bShowBuff1[i]);
		  HT1628_STB(1) ;
		  }
	WR_HT1628_CMD(0x8f);//ËÍÁÁ¶ÈÖ¸Áî
break;

#ifdef SUPPORT_TM1628_KEY_READ
case 5:
  HT1628_READ_KEY_PROCESS();
  break;
#endif


#else
case 4:
	  for(i=9;i<12;i++)
		  {  
			HT1628_STB(0) ;
			WR_HT1628_Byte(0xc0+i);//ÏÔÊ¾Êý¾Ý  add-C0  C2
		  WR_HT1628_Byte(led7_var.bShowBuff1[i]);
		  HT1628_STB(1) ;
		  }
break;

case 5:
	  for(i=12;i<LED_COM_MAX;i++)
		  {  
			HT1628_STB(0) ;
			WR_HT1628_Byte(0xc0+i);//ÏÔÊ¾Êý¾Ý  add-C0  C2
		  WR_HT1628_Byte(led7_var.bShowBuff1[i]);
		  HT1628_STB(1) ;
		  }
	WR_HT1628_CMD(0x8f);//ËÍÁÁ¶ÈÖ¸Áî
break;
#ifdef SUPPORT_TM1628_KEY_READ
case 6:
  HT1628_READ_KEY_PROCESS();
  break;
#endif

#endif
}
cnt++;
#if LED_COM_MAX==13 
  #ifdef SUPPORT_TM1628_KEY_READ
   if(cnt>5) cnt=0;
  #else
   if(cnt>4) cnt=0;
  #endif
#else
   #ifdef SUPPORT_TM1628_KEY_READ
   if(cnt>6) cnt=0;
   #else
   if(cnt>5) cnt=0;
   #endif
#endif


#else
switch(cnt){
case 0:
/*vfd mem show proc*/  
//LED7_DRIVE_disp_eq();
#ifdef support_freq_display
//Disp_freq();
#endif
#ifdef LED_EQ_BAR_SHOW
 LED_EQ_BAR_PROCESS(led7_var.bEqMode);
#elif defined(SUPPORT_EQ_FREQUENCE)
 LED_FREQUENCE_PROCESS();
#endif
LED_drive7();
#ifdef SUPPORT_TM1628_KEY_READ 
  HT1628_READ_KEY_PROCESS();
#endif
break;				
case 1:
HT1628_IO_INIT();
WR_HT1628_CMD(TM1628_MODE);		
WR_HT1628_CMD(HT1628_CMD_SPEC_ADDR);
  for(i=0;i<7;i++){
HT1628_STB(0) ;
WR_HT1628_Byte(0xc0+2*i);//ÏÔÊ¾Êý¾Ý	 add-C0  C2
WR_HT1628_Byte(led7_var.bShowBuff1[2*i]);
HT1628_STB(1) ;
}
WR_HT1628_CMD(0x8f);//ËÍÁÁ¶ÈÖ¸Áî
//show_led_light(pt6311_led_byte);
// READ_tw1628_KEY();	  
break;
}
cnt++;
if(cnt>1) cnt=0;
#endif
#endif
#elif defined(LED_13PIN_MODE)
static u8 cnt;
u16 seg,j;
#ifdef TEST_PANEL_LED
cnt=bledComValue;
seg=BIT(bledGridValue);
#else

#if 0//def SUPPORT_HT1628_DRIVER
ht1628_scan();
#endif

LED_drive7();
seg = led7_var.bShowBuff1[cnt];
#endif
led7_clear();
switch(cnt){
  case 0:
  LED_SET_COM1(0);
  break;
  case 1:
	  LED_SET_COM2(0);
  break;
  case 2:
	  LED_SET_COM3(0);
  break;
  case 3:
	  LED_SET_COM4(0);
  break;
  case 4:
	  LED_SET_COM5(0);
  break;
  case 5:
	  LED_SET_COM6(0);
  break;
  default:
  break;
}
if(seg&BIT(0)) LED_SET_SEG1(1);
if(seg&BIT(1)) LED_SET_SEG2(1);
if(seg&BIT(2)) LED_SET_SEG3(1);
if(seg&BIT(3)) LED_SET_SEG4(1);
if(seg&BIT(4)) LED_SET_SEG5(1);
if(seg&BIT(5)) LED_SET_SEG6(1);
if(seg&BIT(6)) LED_SET_SEG7(1); 

cnt = (cnt >= LED_COM_MAX-1) ? 0 : cnt+1;	
#else
    static u8 cnt;
    u8 seg,j;
	#ifdef TEST_PANEL_LED
	cnt=bledComValue;
	seg=BIT(bledGridValue);
	#else
	
    #if 0//def SUPPORT_HT1628_DRIVER
	ht1628_scan();
	#endif
    LED_drive7();
    seg = led7_var.bShowBuff1[cnt];
    #endif
    led7_clear();
	switch(cnt){
	  case 0:
		LED_SET_PIN1(1);
	  break;
	  case 1:
		LED_SET_PIN2(1);
	  break;
	  case 2:
		LED_SET_PIN3(1);
	  break;
	  case 3:
		LED_SET_PIN4(1);
	  break;
	  case 4:
		LED_SET_PIN5(1);
	  break;
	  case 5:
		LED_SET_PIN6(1);
	  break;
	  case 6:
		LED_SET_PIN7(1);
	  break;
	  default:
	  break;
	}
	if(seg&BIT(0)) LED_SET_PIN1(0);
	if(seg&BIT(1)) LED_SET_PIN2(0);
	if(seg&BIT(2)) LED_SET_PIN3(0);
	if(seg&BIT(3)) LED_SET_PIN4(0);
	if(seg&BIT(4)) LED_SET_PIN5(0);
	if(seg&BIT(5)) LED_SET_PIN6(0);
	if(seg&BIT(6)) LED_SET_PIN7(0);	
	cnt = (cnt >= LED_COM_MAX-1) ? 0 : cnt+1;	
#endif	
}
#ifdef LED_SHOW_SCREEN_FREQUENCE
#ifdef LED_EQ_BAR_SHOW
u8 STEPS_TO_HEX(u8 steps)
{
u8 returnResult=0;
switch(steps){
   case 0:
    returnResult=0;
   case 1:
   returnResult=0x01;
   break;
   case 2:
   returnResult=0x03;
   break;
   case 3:
   returnResult=0x07;
   break;
   case 4:
   returnResult=0x0f;
   break;
   case 5:
   returnResult=0x1f;
   break;
   case 6:
   returnResult=0x3f;
   break;
   case 7:
   returnResult=0x7f;
   break;
   case 8:
   returnResult=0xff;
   break;
   
}
return returnResult;
}
void LED_SHOW_EQ_BAR(u8 barNum,int mode,u8 steps)
{
  if(mode==-1){ //clear all eq bar value
   led7_var.bEqBarBuf[0]=0;
   led7_var.bEqBarBuf[1]=0;
   led7_var.bEqBarBuf[2]=0;
   led7_var.bEqBarBuf[3]=0;
   #if LED_EQ_NUMS>=5
   led7_var.bEqBarBuf[4]=0;
   #endif
  }else{
     switch(mode){
         case 0://bottom to top grid by grid
         led7_var.bEqBarBuf[barNum]=STEPS_TO_HEX(steps);
         break;
         case 1://top to bottom grid by grid
         led7_var.bEqBarBuf[barNum]=STEPS_TO_HEX(steps)<<((LED_EQ_BAR_GRIDS)-steps);
         break;
         case 2://only one grid bottom to top
         led7_var.bEqBarBuf[barNum]=BIT(steps);
         break;     
         case 3://only one grid top to bottom
         led7_var.bEqBarBuf[barNum]=BIT((LED_EQ_BAR_GRIDS)-steps);
         break;     
     }    
  }
}

void LED_SHOW_EQ_IDLE(void)
{
   static u8 cnt,steps,mode;
   cnt++;
   if(cnt>10){
      cnt=0;
      steps++;
      if(steps>(LED_EQ_BAR_GRIDS)){
      steps=1;
      mode++;
      if(mode>3)mode=0;
      }
      }
   if(cnt==10){
      LED_SHOW_EQ_BAR(0,mode,steps);
      LED_SHOW_EQ_BAR(1,mode,steps);
      LED_SHOW_EQ_BAR(2,mode,steps);      
      LED_SHOW_EQ_BAR(3,mode,steps);
      #if LED_EQ_NUMS>=5
      LED_SHOW_EQ_BAR(4,mode,steps);
      #endif
   }
}
#if LED_EQ_BAR_GRIDS==8
#define EN_18 65500*1/8
#define EN_28 65500*2/8
#define EN_38 65500*3/8
#define EN_48 65500*4/8
#define EN_58 65500*5/8
#define EN_68 65500*6/8
#define EN_78 65500*7/8
#define EN_88 65500
#elif LED_EQ_BAR_GRIDS==4
#ifdef EQ_ADC_VALUE_DETECT

#define EN_PER 1023*20/(33*4)
#define EN_14 EN_PER*1
#define EN_24 EN_PER*2
#define EN_34 EN_PER*3
#define EN_44 EN_PER*4

#else
#define EN_14 65500*1/4
#define EN_24 65500*2/4
#define EN_34 65500*3/4
#define EN_44 65500
#endif
#endif
#ifdef EQ_DETECT_ANALOG_SIGNAL
#define ADC_COUNT_NUM 8
u8 bTempAdcAudio=0x3F,bAdcAvarageAudioBuf[ADC_COUNT_NUM]={0x3F};
bool PROCESS_ANALOG_SIGNAL_TO_STEP()
 {
   static u8 cnt1=0,cnt2=0;
   u8 i;
   u16 wAdcValue;
   wAdcValue=adc_value[AD_CH_EQ];
   if((wAdcValue>>4)>0x3F)
     bTempAdcAudio=(u8)((wAdcValue>>4)-0x3F);
   else
	 bTempAdcAudio=(u8)((wAdcValue>>4)-0x3F);
   if(cnt1<ADC_COUNT_NUM){
     bAdcAvarageAudioBuf[cnt1]=bTempAdcAudio;
     cnt1++;
     return FALSE;
   }else cnt1=0;

   bTempAdcAudio=0;
   for(i=0;i<ADC_COUNT_NUM;i++)
     bTempAdcAudio+=bAdcAvarageAudioBuf[i];
   #if 0//LED_EQ_NUMS
   led7_var.wEqADC_Value[cnt2]=(u8)bTempAdcAudio/ADC_COUNT_NUM;
   if(led7_var.wEqADC_Value[cnt2]>=LED_EQ_BAR_GRIDS)led7_var.wEqADC_Value[cnt2]=LED_EQ_BAR_GRIDS;
   cnt2++;
   if(cnt2>=LED_EQ_NUMS)cnt2=0;
   #else
   led7_var.wEqADC_Value=(u8)(bTempAdcAudio/ADC_COUNT_NUM);
   if(led7_var.wEqADC_Value>=LED_EQ_BAR_GRIDS)led7_var.wEqADC_Value=LED_EQ_BAR_GRIDS;
   #endif
   
   return TRUE;
   
 }
#endif
u8 ENERGY_TO_STEPS(u16 energy)
{
#if LED_EQ_BAR_GRIDS==8
  if(energy<=EN_18)return 0;
  if(energy<=EN_28)return 1;
  if(energy<=EN_38)return 2;
  if(energy<=EN_48)return 3;
  if(energy<=EN_58)return 4;
  if(energy<=EN_68)return 5;
  if(energy<=EN_78)return 6;
  if(energy<=EN_88)return 7;
  return 7; //default 
#elif LED_EQ_BAR_GRIDS==4
  #if defined LED_ID_ZX001||defined LED_ID_JW1676_1B||defined LED_ID_JM_4169_B
  if(energy<100)return 0;
  else if((energy>=100)&&(energy<EN_14))return 1;
  else if((energy>=EN_14)&&(energy<EN_24))return 2;
  else if((energy>=EN_24)&&(energy<EN_34))return 3;
  else if((energy>=EN_34)&&(energy<=EN_44))return 4;
  else return 4;
  #else
  if(energy<=EN_14)return 0;
  if(energy<=EN_24)return 1;
  if(energy<=EN_34)return 2;
  if(energy<=EN_44)return 3;
  return 3;
  #endif
#endif
}
void GET_LED_EQ_BAR_VALUE(void)
{
   static u8 cnt=0;
#ifdef EQ_ADC_VALUE_DETECT	
   led7_var.bEqBarEnergyValueBuf[cnt]=adc_value[AD_CH_EQ];
#else
   led7_var.bEqBarEnergyValueBuf[cnt]=get_dac_energy_value();
#endif   
   cnt++;
   if(cnt>=LED_EQ_NUMS)
   cnt=0;
}
void LED_EQ_BAR_PROCESS(u8 mode)
{
  static u8 cnt=0,bPowerOnCnt,bIdledCnt,barCnt=0;
  bPowerOnCnt++;
  if(bPowerOnCnt>25)bPowerOnCnt=26;
  if(bPowerOnCnt<25)return; //eq show too earlier
  if(compare_task_name("IdleTask")){
      LED_SHOW_EQ_BAR(0,-1,0);
      LED_SHOW_EQ_BAR(1,-1,0);
      LED_SHOW_EQ_BAR(2,-1,0);
      LED_SHOW_EQ_BAR(3,-1,0);
      #if LED_EQ_NUMS>=5
      LED_SHOW_EQ_BAR(4,-1,0);
      #endif
      return;
  }  
#ifdef SUPPORT_MUTE_FLASH
  #ifdef EQ_ADC_VALUE_DETECT  
    #ifdef SUPPORT_PT2313
  	if(b_muteFlag|| adc_value[AD_CH_EQ]<10 ||pt2313data[PT_VOLUME]==0){
   #else
 	 if(b_muteFlag|| adc_value[AD_CH_EQ]<10){
	#endif
  #else
  #ifdef SUPPORT_PT2313
  if(b_muteFlag|| get_dac_energy_value()<100 ||pt2313data[PT_VOLUME]==0){
  #else
  if(b_muteFlag|| get_dac_energy_value()<100){
  #endif
  #endif
   if(bIdledCnt<10)
   bIdledCnt++;
  if(bIdledCnt==10){
  LED_SHOW_EQ_IDLE();
  return;
  }
  }
  else{
  bIdledCnt=0;
  //led7_var.bEqCircleIfPlay=TRUE;
  }
#endif
// cnt++;
// if(cnt>1)cnt=0;
//  if(cnt==0){
 #ifdef EQ_DETECT_ANALOG_SIGNAL
   LED_SHOW_EQ_BAR(0,mode,led7_var.wEqADC_Value);
   LED_SHOW_EQ_BAR(1,mode,led7_var.wEqADC_Value);  
   LED_SHOW_EQ_BAR(2,mode,led7_var.wEqADC_Value);  
   LED_SHOW_EQ_BAR(3,mode,led7_var.wEqADC_Value);
  #if LED_EQ_NUMS>=5
   LED_SHOW_EQ_BAR(4,mode,led7_var.wEqADC_Value);
  #endif
 #else
  LED_SHOW_EQ_BAR(0,mode,ENERGY_TO_STEPS(led7_var.bEqBarEnergyValueBuf[0]));
  LED_SHOW_EQ_BAR(1,mode,ENERGY_TO_STEPS(led7_var.bEqBarEnergyValueBuf[1]));  
  LED_SHOW_EQ_BAR(2,mode,ENERGY_TO_STEPS(led7_var.bEqBarEnergyValueBuf[2]));  
  LED_SHOW_EQ_BAR(3,mode,ENERGY_TO_STEPS(led7_var.bEqBarEnergyValueBuf[3]));
  #if LED_EQ_NUMS>=5
  LED_SHOW_EQ_BAR(4,mode,ENERGY_TO_STEPS(led7_var.bEqBarEnergyValueBuf[4]));
  #endif
 #endif
//  }
  //cnt++;
  
//  if(compare_task_name("FMRadioTask")){
  //if(cnt>5){
 // cnt=0;
 // barCnt++;
 // if(barCnt>(LED_EQ_NUMS-1))barCnt=0;
 // }
//  }else{
//	  if(cnt>20){
//	  cnt=0;
//	  barCnt++;
//	  if(barCnt>(LED_EQ_NUMS-1))barCnt=0;
//	  }
//  }
}
#elif defined(SUPPORT_EQ_FREQUENCE)
   #ifdef EQ_ADC_VALUE_DETECT
     #ifdef LED_ID_YUNKE01
       #define EQ_AD17 1023*1/7
       #define EQ_AD27 1023*2/7
       #define EQ_AD37 1023*3/7
       #define EQ_AD47 1023*4/7
       #define EQ_AD57 1023*5/7
       #define EQ_AD67 1023*6/7
       #define EQ_AD77 1023
   #elif defined LED_ID_JW4520_2A
   
       #define EQ_AD18 1023*1/10
       #define EQ_AD28 1023*1/9
       #define EQ_AD38 1023*1/8
       #define EQ_AD48 1023*1/7
       #define EQ_AD58 1023*1/6
       #define EQ_AD68 1023*1/5
       #define EQ_AD78 1023*1/3  
       #define EQ_AD88 1023	*1/1
	   
   #elif defined LED_ID_DOUBLE_PANEL
   


	   #define EQ_AD0 588
 
	   #define EQ_AD1 600
	   #define EQ_AD2 633
	   #define EQ_AD3 666
	   #define EQ_AD4 722
	   #define EQ_AD5 799
	   #define EQ_AD6 844
	   #define EQ_AD7 922
	   #define EQ_AD8 1023

	   
   #elif defined LED_ID_SD40C18SRB
	   #define EQ_AD1 1023*1/5
	   #define EQ_AD2 1023*2/5
	   #define EQ_AD3 1023*3/5
	   #define EQ_AD4 1023*4/5
	   #define EQ_AD5 1023   
     #else
	   #define EQ_AD14 1023*1/4
	   #define EQ_AD24 1023*2/4
	   #define EQ_AD34 1023*3/4
	   #define EQ_AD44 1023   
	 #endif
   #else
     #if LED_EQ_NUMS>=7
       #define EN_MAX 65500
 //    #else
	   #define EN_14 65500*1/4
	   #define EN_24 65500*2/4
	   #define EN_34 65500*3/4
	   #define EN_44 65500
     #endif

	 
   #endif
   
   u8 ENERGY_TO_STEPS(u16 energy)
   {     
    #ifdef EQ_ADC_VALUE_DETECT
       #ifdef LED_ID_YUNKE01
	  	   if(energy<=5)return 0;
	  	   if(energy<=EQ_AD17)return 1;
	  	   if(energy<=EQ_AD27)return 2;
	  	   if(energy<=EQ_AD37)return 3;
	  	   if(energy<=EQ_AD47)return 4;
	  	   if(energy<=EQ_AD57)return 5;
	  	   if(energy<=EQ_AD67)return 6;	  	   
	  	   return 7; //default 
	   #elif defined LED_ID_JW4520_2A   
	   
	 	if( b_muteFlag==TRUE)
	 		return 0;
	   
	  	   if(energy<=25)return 0;
	  	   if(energy<=EQ_AD18)return 1;
	  	   if(energy<=EQ_AD28)return 2;
	  	   if(energy<=EQ_AD38)return 3;
	  	   if(energy<=EQ_AD48)return 4;
	  	   if(energy<=EQ_AD58)return 5;
	  	   if(energy<=EQ_AD68)return 6;	  	   
	  	   if(energy<=EQ_AD78)return 7;	  	   		   
	  	   return 8; //default 	  	   
     #elif defined LED_ID_SD40C18SRB
		  	if(energy<=0)return 0;
		  	if(energy<=EQ_AD1)return 1;
		  	if(energy<=EQ_AD2)return 2;
		  	if(energy<=EQ_AD3)return 3;
		  	if(energy<=EQ_AD4)return 4;
		  	if(energy<=EQ_AD5)return 5;
		  	return 5; //default 

     #elif defined LED_ID_DOUBLE_PANEL

   	{
	  	if(energy<=EQ_AD0)return 0;
	  	if(energy<=EQ_AD1)return 1;
	  	if(energy<=EQ_AD2)return 2;
	  	if(energy<=EQ_AD3)return 3;
	  	if(energy<=EQ_AD4)return 4;
	  	if(energy<=EQ_AD5)return 5;
	  	if(energy<=EQ_AD6)return 6;
	  	if(energy<=EQ_AD7)return 7;
   	}

	  	return LED_EQ_NUMS;
		  	
          #else
		  	if(energy<=0)return 0;
		  	if(energy<=EQ_AD14)return 1;
		  	if(energy<=EQ_AD24)return 2;
		  	if(energy<=EQ_AD34)return 3;
		  	if(energy<=EQ_AD44)return 4;
		  	return 4; //default 
	  	#endif
    #else       

	
		 if(energy<=600 ||b_muteFlag||(dac_var.bMute))return 0;
		 
		#if LED_EQ_NUMS==7
		
		 if(energy<=EN_MAX*1/LED_EQ_NUMS)return 1;
		 if(energy<=EN_MAX*2/LED_EQ_NUMS)return 2;
		 if(energy<=EN_MAX*3/LED_EQ_NUMS)return 3;
		 if(energy<=EN_MAX*4/LED_EQ_NUMS)return 4;
		 if(energy<=EN_MAX*5/LED_EQ_NUMS)return 5;
		 if(energy<=EN_MAX*6/LED_EQ_NUMS)return 6;
		 return LED_EQ_NUMS;
	 
		 
		#else
		 if(energy<=EN_14)return 1;
		 if(energy<=EN_24)return 2;
		 if(energy<=EN_34)return 3;
		 if(energy<=EN_44)return 4;
		 return 4; //default 
	      #endif
   
    #endif
   }
   
   u8 STEPS_TO_HEX(u8 steps)
   {
   u8 returnResult=0;
   switch(steps){
	  case 0:
	  returnResult=0x01;
	  break;
	  case 1:
	  returnResult=0x03;
	  break;
	  case 2:
	  returnResult=0x07;
	  break;
	  case 3:
	  returnResult=0x0f;
	  break;
	  case 4:
	  returnResult=0x1f;
	  break;
	  case 5:
	  returnResult=0x3f;
	  break;
	  case 6:
	  returnResult=0x7f;
	  break;
	  case 7:
	  returnResult=0xff;
	  break;
   }
   return returnResult;
   }
   
  #ifdef NO_VOICE_EQ_SHOW
  void LED_NO_VOICE_EQ_PROCESS(void)
  {
    static u8 mode=0,steps=0,cnt=0;
    if(cnt==0)
		{
    switch(mode){
       case 0:
          led7_var.bEqIconBuf=STEPS_TO_HEX(steps);
        break;
       case 1:
		  led7_var.bEqIconBuf=STEPS_TO_HEX(steps)<<(7-steps);
        break;
       case 2:
          led7_var.bEqIconBuf=BIT(steps);
        break;
       case 3:
		  led7_var.bEqIconBuf=BIT(7-steps);
        break;
    }
}
   cnt++;
   if(cnt==8)
   	{
	   cnt=0;
	   steps++;
	   if(steps>=LED_EQ_NUMS)
	   {
		   steps=0;
		     mode++;
		     if(mode>3)mode=0;
	    }
   }
  }
  #endif

 #if defined LED_ID_DOUBLE_PANEL	   
		  
void	led_no_single_freq(void)
{
   static u8 cnt=1;
	
     switch(cnt)
	   {	 	
	        case 1:
	        case 15:
	 
	 		 {
	 		 	led7_var.bShowBuff[0]=0x30;
	 		 	led7_var.bShowBuff[1]=0;
	 		 	led7_var.bShowBuff[2]=0;
	 		 	led7_var.bShowBuff[3]=0;		
	 		 }
	 
	        break;
	 	   
	        case 2:
	        case 14:

	 		 {
	 			led7_var.bShowBuff[0]=0x36;
	 			led7_var.bShowBuff[1]=0;
	 			led7_var.bShowBuff[2]=0;
	 			led7_var.bShowBuff[3]=0;		
	 		 }
	 	   
	        break;
	        case 3:
	        case 13:

	 		 {
	 		       led7_var.bShowBuff[0]=0x36;	   	
	 		       led7_var.bShowBuff[1]=0x30;
	 		    	led7_var.bShowBuff[2]=0;
	 			led7_var.bShowBuff[3]=0;	
	 		 } 	  	
	 	
	    break;
	        case 4:
	        case 12:

	 		 {
	 			led7_var.bShowBuff[0]=0x36;
	 			led7_var.bShowBuff[1]=0x36;
	 			led7_var.bShowBuff[2]=0;
	 			led7_var.bShowBuff[3]=0;		
	 		 }	   	
	      break;
	 	 
	        case 5:
	        case 11:

	 		 {
	 		       led7_var.bShowBuff[0]=0x36;
	 		       led7_var.bShowBuff[1]=0x36;
	 		        led7_var.bShowBuff[2]=0x30;
	 			led7_var.bShowBuff[3]=0;		
	 		 }
	 	   	
	     break;
	 	
	        case 6:
	        case 10:

	 
	 		 {
	 		      led7_var.bShowBuff[0]=0x36;
	 		       led7_var.bShowBuff[1]=0x36;
	 		        led7_var.bShowBuff[2]=0x36;
	 			led7_var.bShowBuff[3]=0;		
	 		 }   
	 	
	        break;
	        case 7:
	        case 9:	 	   

	 		 {
	 		       led7_var.bShowBuff[0]=0x36;
	 		       led7_var.bShowBuff[1]=0x36;
	 		        led7_var.bShowBuff[2]=0x36;
	 		        led7_var.bShowBuff[3]=0x30;
	 		 }
	 	
	        break;
	        case 8:

	 		 {
	 		       led7_var.bShowBuff[0]=0x36;
	 		       led7_var.bShowBuff[1]=0x36;
	 		        led7_var.bShowBuff[2]=0x36;
	 		        led7_var.bShowBuff[3]=0x36;
	 		 }
	 		
	        break;	 
			
	default:
		led7_var.bShowBuff[0]=0;
		led7_var.bShowBuff[1]=0;
		led7_var.bShowBuff[2]=0;
		led7_var.bShowBuff[3]=0;		

	break;
	 
	 }
	cnt++;
if(cnt>=17)
	cnt=0;
 }
 
#elif defined LED_ID_27N60_8

void	led_no_single_freq(void)
{
   static u8 cnt=1;

     switch(cnt)
	   {	 	
       case 1:
       case 7:
       case 19:	   	
	       led7_var.bEqIconBuf=EQ_00|EQ_04;
       break;
       case 2:
       case 6:
	       led7_var.bEqIconBuf=EQ_01|EQ_05;
       break;
       case 3:
       case 5:
	       led7_var.bEqIconBuf=EQ_02|EQ_06;
       break;
       case 4:
       case 13:
	       led7_var.bEqIconBuf=EQ_03|EQ_07;
       break;
	   
       case 8:
       case 18:	   	
	       led7_var.bEqIconBuf=EQ_00|EQ_01|EQ_04|EQ_05;
       break;
	   
       case 9:
       case 17:
	       led7_var.bEqIconBuf=EQ_00|EQ_01|EQ_02|EQ_04|EQ_05|EQ_06;
       break;
	   
       case 10:
       case 16:	   	
       case 21:	   	
       case 23:	   	
       case 25:	   	
	       led7_var.bEqIconBuf=0xff;
       break;

       case 11:
       case 15:
	       led7_var.bEqIconBuf=EQ_01|EQ_02|EQ_03|EQ_05|EQ_06|EQ_07;
       break;	   
	   
       case 12:
       case 14:
	       led7_var.bEqIconBuf=EQ_02|EQ_03|EQ_06|EQ_07;
       break;	   

			
	default:

	       led7_var.bEqIconBuf=0;	
	break;
	 
	 }
	cnt++;
if(cnt>=26)
	cnt=0;
 }

#endif

  void LED_FREQUENCE_PROCESS(void)
  {
  
    static u8  cnt=0;
  static  u8  cnt1=0;
	 

#if defined(LED_ID_DOUBLE_PANEL)
   if((workmode!=LINE_WORK_MODE)&&(workmode!=BT_WORK_MODE))
	return;
#endif

#if defined(LED_ID_JW4520_2A)
   if((workmode!=LINE_WORK_MODE))
	return;
#endif
	 
    cnt++;

  #if defined LED_ID_SD40C18SRB	
    if(cnt<1)return;
    if(cnt==1)cnt=0;
	
#elif defined LED_ID_JW4520_2A	


   if(cnt<4)return;
    if(cnt==4)cnt=0;	

#if 1
        led7_var.bShowBuff[0]=0;
        led7_var.bShowBuff[1]=0;
        led7_var.bShowBuff[2]=0;
        led7_var.bShowBuff[3]=0;	
#endif

#elif defined LED_ID_DOUBLE_PANEL	   
    if(cnt<1)return;
    if(cnt==1)cnt=0;	
#elif defined LED_ID_27N60_8	   
    if(cnt<30)return;
    if(cnt==30)cnt=0;	
#else
    if(cnt<25)return;
    if(cnt==25)cnt=0;
#endif	

   //  printf("111   (ENERGY_TO_STEPS(get_dac_energy_value())) %d \n",get_dac_energy_value());

  #ifdef EQ_ADC_VALUE_DETECT
    switch(ENERGY_TO_STEPS(adc_value[AD_CH_EQ])){
  #else
    switch(ENERGY_TO_STEPS(get_dac_energy_value())){
  #endif
       case 0:
	   	
         #ifdef NO_VOICE_EQ_SHOW

		#ifdef LED_ID_JW4520_2A
		
		#if 0
	
				{					
				        led7_var.bShowBuff[0]=0;
				        led7_var.bShowBuff[1]=0;
				        led7_var.bShowBuff[2]=0;
				        led7_var.bShowBuff[3]=0;			
		     			 led7_var.bEqIconBuf=EQ_00|EQ_01|EQ_02;

				   //     LED_NO_VOICE_EQ_PROCESS();	
				}		
		#else
			cnt1++;
			if(cnt1>=100)			
				{					
					cnt1=101;
				        LED_NO_VOICE_EQ_PROCESS();
				}
			else	  
			{
				//		cnt1=0;
			        led7_var.bEqIconBuf=0;		
			        led7_var.bShowBuff[0]=0;
			        led7_var.bShowBuff[1]=0;
			        led7_var.bShowBuff[2]=0;
			        led7_var.bShowBuff[3]=0;	
				}	
		#endif 
		
		#else
	          	LED_NO_VOICE_EQ_PROCESS();
		#endif
	
          #elif 0//defined LED_ID_27N60_8	   
		    		
  		cnt1++;
  
	      	 if(cnt1>=15)
	      	   {	   
	      		   cnt1=9;
	   		led7_var.bEqIconBuf=0;				   
	      		   led_no_single_freq();	
	      		}
			 
           #elif defined LED_ID_DOUBLE_PANEL	   
 	
  		led7_var.bEqIconBuf=0;
  		
  		cnt1++;
  
	      	 if(cnt1>=25)
	      	   {	   
	      		   cnt1=15;
	      		   led_no_single_freq();	
	      		}
  
         #else
          	led7_var.bEqIconBuf=0;
         #endif
	   
       break;
	   
     #if defined LED_ID_YUNKE01
	 
       case 1:
       led7_var.bEqIconBuf=EQ_00;
       break;
       case 2:
       led7_var.bEqIconBuf=EQ_00|EQ_01;
       break;
       case 3:
       led7_var.bEqIconBuf=EQ_00|EQ_01|EQ_02;
       break;
       case 4:
       led7_var.bEqIconBuf=EQ_00|EQ_01|EQ_02|EQ_03;
       break;
       case 5:
       led7_var.bEqIconBuf=EQ_00|EQ_01|EQ_02|EQ_03|EQ_04;
       break;
       case 6:
       led7_var.bEqIconBuf=EQ_00|EQ_01|EQ_02|EQ_03|EQ_04|EQ_05;
       break;
       case 7:
       led7_var.bEqIconBuf=EQ_00|EQ_01|EQ_02|EQ_03|EQ_04|EQ_05|EQ_06;       
       break;
       case 8:
       led7_var.bEqIconBuf=0xff;
       break;
	   
     #elif defined LED_ID_JW4520_2A
	 
       case 1:
		cnt1=0;	   		   	
		       led7_var.bEqIconBuf=EQ_00;

       break;
       case 2:
		cnt1=0;	   	
     			 led7_var.bEqIconBuf=EQ_00|EQ_01;
       break;
       case 3:
		cnt1=0;	   	
     			 led7_var.bEqIconBuf=EQ_00|EQ_01|EQ_02;
       break;
       case 4:
		cnt1=0;	   	
      			 led7_var.bEqIconBuf=EQ_00|EQ_01|EQ_02|EQ_03;
       break;
       case 5:
		cnt1=0;	   	
		       led7_var.bEqIconBuf=EQ_00|EQ_01|EQ_02|EQ_03|EQ_04;
	   
       break;
       case 6:
		cnt1=0;	   	
		       led7_var.bEqIconBuf=EQ_00|EQ_01|EQ_02|EQ_03|EQ_04|EQ_05;

       break;
       case 7:
		cnt1=0;	   	
		       led7_var.bEqIconBuf=EQ_00|EQ_01|EQ_02|EQ_03|EQ_04|EQ_05|EQ_06;       
       break;
       case 8:
		cnt1=0;	   	
      				 led7_var.bEqIconBuf=0xff;	   
       break;
	   
     #elif defined LED_ID_DOUBLE_PANEL
	 
	#if 1
	
       case 1:
	   cnt1=0;	   	

		 {
		 	led7_var.bShowBuff[0]=0x30;
		 	led7_var.bShowBuff[1]=0;
		 	led7_var.bShowBuff[2]=0;
		 	led7_var.bShowBuff[3]=0;		
		 }

       break;
	   
       case 2:
	   cnt1=0;
		 {
			led7_var.bShowBuff[0]=0x36;
			led7_var.bShowBuff[1]=0;
			led7_var.bShowBuff[2]=0;
			led7_var.bShowBuff[3]=0;		
		 }
	   
       break;
       case 3:
	   cnt1=0;	
		 {
		       led7_var.bShowBuff[0]=0x36;	   	
		       led7_var.bShowBuff[1]=0x30;
		    	led7_var.bShowBuff[2]=0;
			led7_var.bShowBuff[3]=0;	
		 } 	  	
	
   break;
       case 4:
  	   cnt1=0;	
		 {
			led7_var.bShowBuff[0]=0x36;
			led7_var.bShowBuff[1]=0x36;
			led7_var.bShowBuff[2]=0;
			led7_var.bShowBuff[3]=0;		
		 }	   	
     break;
	 
       case 5:
	   cnt1=0;	
		 {
		       led7_var.bShowBuff[0]=0x36;
		       led7_var.bShowBuff[1]=0x36;
		        led7_var.bShowBuff[2]=0x30;
			led7_var.bShowBuff[3]=0;		
		 }
	   	
    break;
	
       case 6:
 	   cnt1=0;	  

		 {
		      led7_var.bShowBuff[0]=0x36;
		       led7_var.bShowBuff[1]=0x36;
		        led7_var.bShowBuff[2]=0x36;
			led7_var.bShowBuff[3]=0;		
		 }   
	
       break;
	   
       case 7:
	   cnt1=0;	
		 {
		       led7_var.bShowBuff[0]=0x36;
		       led7_var.bShowBuff[1]=0x36;
		        led7_var.bShowBuff[2]=0x36;
		        led7_var.bShowBuff[3]=0x30;
		 }
	
       break;
       case 8:
	   cnt1=0;
		 {
		       led7_var.bShowBuff[0]=0x36;
		       led7_var.bShowBuff[1]=0x36;
		        led7_var.bShowBuff[2]=0x36;
		        led7_var.bShowBuff[3]=0x36;
		 }
		
       break;	 
	#endif

     #elif defined LED_ID_SD40C18SRB

          #if 0
          	default:
                 led7_var.bEqIconBuf=EQ_00|EQ_01|EQ_05|EQ_06;
          	break;
          
          #else
                 case 1:
                 led7_var.bEqIconBuf=EQ_00|EQ_05;
                 break;
                 case 2:
                 led7_var.bEqIconBuf=EQ_00|EQ_01|EQ_05|EQ_06;
                 break;
                 case 3:
                 led7_var.bEqIconBuf=EQ_00|EQ_01|EQ_02|EQ_05|EQ_06|EQ_07;
                 break;
                 case 4:
                 led7_var.bEqIconBuf=EQ_00|EQ_01|EQ_02|EQ_03|EQ_05|EQ_06|EQ_07|EQ_08;
                 break;
                 case 5:
                 led7_var.bEqIconBuf=EQ_00|EQ_01|EQ_02|EQ_03|EQ_04|EQ_05|EQ_06|EQ_07|EQ_08|EQ_09;
                 break;	 
                 case 6:
                 led7_var.bEqIconBuf=0xfff;
                 break;
          #endif

    #else
	
       case 1:
       led7_var.bEqIconBuf=EQ_00|EQ_04;
       break;
       case 2:
       led7_var.bEqIconBuf=EQ_00|EQ_01|EQ_04|EQ_05;
       break;
       case 3:
       led7_var.bEqIconBuf=EQ_00|EQ_01|EQ_02|EQ_04|EQ_05|EQ_06;
       break;
       case 4:
       led7_var.bEqIconBuf=0xff;
       break;
	   
    #endif
    }

	
  }
#endif
#endif



#endif



