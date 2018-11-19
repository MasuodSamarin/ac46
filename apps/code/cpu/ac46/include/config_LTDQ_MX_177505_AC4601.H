
#if 1
/*
*********************************************************************
                        特殊功能定义
*********************************************************************
*/

#define support_off_voice

// #define LTDQ_ZY5021_RGB_AC4601

/*
*********************************************************************
                        DEBUG MACRO
*********************************************************************
*/

// #define __DEBUG         ////<开启系统打印调试功能


/*
*********************************************************************
                        COMMON MACRO
*********************************************************************
*/
#define EQ_FILTER_EN            0    ///<EQ滤波器开关
//#define PA_EN                   0    ///<功放mute控制
#define SYS_LVD_EN              1    ///<系统低电检测
#define S10_MODE                0    ///<0:普通SDK     1:S10样机程序
#define POWERUP_DEFAULT_MODE    1    ///<上电默认模式使能
#ifndef BT_TESTER
//#define LED_EN                  0    ///<LED指示使能
#define KEY_TONE_EN             0    ///<按键音使能
#else
#define LED_EN                  0    ///<LED指示使能
#define KEY_TONE_EN             0    ///<按键音使能
#endif

//#define SYS_DEFAULT_VOL_EN      0    ///<系统开机默认音量使能
//#if SYS_DEFAULT_VOL_EN
//#define SYS_DEFAULT_VOL         25   ///<系统启动默认音量值
//#endif

#if S10_MODE
#define KEY_DOUBLE_CLICK             ///<按键双击功能
#define DAC_SOUNDTRACK_COMPOUND 1    ///<DAC声道合成
#else
#define DAC_SOUNDTRACK_COMPOUND 0    ///<DAC声道合成
#endif/*S10_MODE*/

#ifdef AC46_512K
    #define BT_PHONE_NUMBER     0          //来电报号
#else
    #define BT_PHONE_NUMBER     0          //来电报号
#endif

/*
*********************************************************************
                        REC MACRO
*********************************************************************
*/
#ifdef AC46_512K
    #define REC_EN         0         ///512K_SDK
#else
    #define REC_EN         1         ///标准SDK
    #if REC_EN
    #define SUPPORT_ONE_KEY_ENTER_START_REC  //music
    #define ENTER_INTO_REC_MODE_AUTO_START_REC //music
    #define MODE_CHANGE_SKIP_REC_CASE
    #define AFTER_RECORD_PLAY_LAST_RECORDED_FILE
    #define ACCESS_REC_FILE_BY_FOLDER_NAME
    #define FM_AUX_BT_START_REC_KEY_SECOND_PRESS_STOP_REC
    #define SUPPORT_AUX_FM_BT_REPLAY_KEY
    #define SUPPORT_AUX_FM_BT_SHOW_REC_TIME
    #define SUPPORT_REC_DELETE_FILTER_NOT_REC_FILE
    #define SUPPORT_REPLAY_CANCEL_FOLDER_REPEAT_AND_PLAY_NOT_REC_FILES
    #define SUPPORT_PRESS_REC_KEY_AGAIN_STOP_AND_PLAY_LAST_REC_FILE
   // #define MODIFY_REC_FILE_NAME_FOR_ZY

		 #ifdef AFTER_RECORD_PLAY_LAST_RECORDED_FILE
		 extern bool bIfRecordFolder;
		 #endif		 

	
    #endif
#endif


/*
*********************************************************************
                        FM MACRO
*********************************************************************
*/
#ifdef AC46_512K
    #define FM_RADIO_EN         0       ///512K_SDK
#else
    #define FM_RADIO_EN         1       ///标准SDK
#endif

/*
*********************************************************************
                        RTC MACRO
*********************************************************************
*/
#ifdef AC46_512K
    #define RTC_CLK_EN              0       ///<512K_SDK RTC时钟模式
    #define RTC_ALM_EN          	0       ///<512K_SDK RTC闹钟模式
#else

    #define RTC_CLK_EN              0       ///<标准SDK RTC时钟模式
    #if RTC_CLK_EN
        #define RTC_ALM_EN          1       ///<标准SDK RTC闹钟模式
    #endif

#endif

/*
*********************************************************************
                        BT MACRO
*********************************************************************
*/
//配置测试盒测试功能
#define NON_TEST         0       //没频偏和距离测试
#define FRE_OFFSET_TEST  BIT(0)  //频偏测试
#define DISTANCE_TEST    BIT(1)  //距离测试


#define NORMAL_MODE         0
#define TEST_INDEX_MODE     1     //指标性能测试(使用MT8852A仪器测试,过认证的时候使用)
#define TEST_FCC_MODE       2     //测试fcc认证
#define TEST_FRE_OFF_MODE   3     //测试频偏(使用频谱分析仪-手提测试仪-中心频率默认2422M)
#define TEST_PERFOR_MODE    4    //指标性能测试(使用MT8852A仪器测试,测试芯片性能的时候使用)


#define BT_MODE        NORMAL_MODE
#ifndef BT_TESTER
#define BT_BACKMODE         0             //录音与蓝牙后台不能共存
#if !BT_BACKMODE
    #define BT_HID_INDEPENDENT_MODE  0    //HID拍照的独立模式只支持非后台
#endif
#else
#define BT_BACKMODE         0
#endif
/*
*********************************************************************
                        UART MACRO
*********************************************************************
*/


#define UART0   0
#define UART1   1
#define UART2   2
#define UART_NO 0xFF

#ifdef __DEBUG
#if S10_MODE
#define S10_UART_DEBUG    0
#if S10_UART_DEBUG
#define DEBUG_UART   UART1
#else
#define DEBUG_UART   UART_NO
#endif/*S10_UART_DEBUG*/
#else
#ifdef BT_TESTER
#define DEBUG_UART   UART1  /*标准SDK打印口*/
#else
#define DEBUG_UART   UART0  /*标准SDK打印口*/
#endif
#endif/*S10_MODE*/

#else
#define DEBUG_UART UART_NO
#endif/*__DEBUG*/

/*
*********************************************************************
                        DAC MACRO
*********************************************************************
*/
#define DAC_EN          1
#if DAC_EN
#define DAC_FADE_EN     1
#else
#define DAC_FADE_EN     0
#endif

/*
*********************************************************************
                        DEVICE MACRO
*********************************************************************
*/
#ifdef BT_TESTER
    #define SDMMC0_EN       0    ///<SD0使能
    #define SDMMC1_EN       0    ///<SD1使能
#else
    #if S10_MODE
    #define SDMMC0_EN       1
    #define SDMMC1_EN       0
    #else
    #define SDMMC0_EN       1
    #define SDMMC1_EN       0 // 1
    #endif/*S10_MODE*/
#endif

#ifdef AC46_512K
    #define USB_DISK_EN     0    ///<512K 不添加 U盘 PC 功能
    #define USB_PC_EN       0    ///<512K 不添加 U盘 PC 功能
#else
    #if S10_MODE
        #define USB_DISK_EN     0    ///<U盘使能
        #define USB_PC_EN       0    ///<PC使能
    #else
        #define USB_DISK_EN     1    ///<标准SDK
        #define USB_PC_EN       1    ///<标准SDK
    #endif/*S10_MODE*/
#endif

#define SPI_FLASH_BLK_NUM   8
//#define POWERUP_DEV_IGNORE       ///<插着设备上电是否响应U盘或SD
//#define AUX_OUT_WITHOUT_CNT
/*
*********************************************************************
                        UI MACRO
*********************************************************************
*/

#ifdef BT_TESTER
    #define UI_ENABLE           0     ///>UI_显示
#else

    #ifdef AC46_512K
        #define UI_ENABLE       0     ///>512K_SDK UI_显示
    #else
        #define UI_ENABLE       1     ///>标准SDK UI_显示
    #endif
#endif
#endif


/*
*********************************************************************
                        UI MACRO
*********************************************************************
*/

//****led screen setting******/
#if UI_ENABLE
//#define LED_ID_KF8845AB

#if defined ZY_5021_8848_MX_SG_AC4601

#define LED_ID_8848
#define LED_ICON_NUMS 8

#define LED_7PIN_MODE
//#define LED_USE_7PIN_PA7__PA11PA14PA15
#define LED_USE_7PIN_PA4PA6PA7PA8PA9PA10PA11
//#define LED_USE_7PIN_PB8PB7PB6PA15PA14PA10PA9
//#define LED_USE_7PIN_PA9__PA15PB6PA7
#define LED_7PIN_REVERSE

#elif defined ZY_5021_MX_8848_TY_AC4601
#define LED_ID_8848
#define LED_ICON_NUMS 8

#define LED_7PIN_MODE
//#define LED_USE_7PIN_PA7__PA11PA14PA15
#define LED_USE_7PIN_PA4PA6PA7PA8PA9PA10PA11
//#define LED_USE_7PIN_PB8PB7PB6PA15PA14PA10PA9
//#define LED_USE_7PIN_PA9__PA15PB6PA7
//#define LED_7PIN_REVERSE
#elif  1//defined LTDQ_ZY5021_RGB_AC4601 
#define LED_ID_4018N_2
#define LED_7PIN_MODE

#define LED_USE_7PIN_PA4PA6PA7PA9PA10PA11PA15
#define LED_SCREEN_SHOW_BAT_STATUS

#define LED_ICON_NUMS 7
// #define LED_7PIN_REVERSE

#else // 1//defined ZY_5021_MX_4018N_2_AC4601

#define LED_ID_4018N_2
#define LED_7PIN_MODE

#define LED_USE_7PIN_PA4PA6PA7PA8PA9PA10PA11
#define LED_SCREEN_SHOW_BAT_STATUS

#define LED_ICON_NUMS 7
// #define LED_7PIN_REVERSE

#endif

#define LED_COM_MAX 7
#define LED_8NUMS 4
#define LED_8GRIDS 7
#define SUPPORT_FLASH_ICON
#define SUPPORT_FLASH_CHAR

#ifdef SUPPORT_FLASH_CHAR
#define SUPPORT_LED_BLUE_STRING_FLASH
#define SUPPORT_MUTE_FLASH
//#define MUTE_FLASH_ZERO_VOL
#define MUTE_FLASH_ALL_SCREEN
#endif
#if defined ZY_5021B
#define LED_BT_STATE_SHOW_STRING_BLUC  // jsuo 20151118 add
#endif

#define LED_SHOW_DEVICE_PLUGIN
#define LED_SHOW_BT_EQ
#define LED_SHOW_MP3_PAUSE
#define LED_SHOW_POWER_OFF_STRING " OFF"
#define LED_SHOW_INTRO_STRING "SCAN"
#define BT_NOT_SHOW_ICON_PLAY_PAUSE


#define LED_EXIT_MP3_NOT_SHOW_LOAD
#define MP3_NEXT_MODE_IS_AUX 0
#define EXIT_AUX_TASK_NOT_SHOW_LOAD
//#define LED_SWITCH_FM2AUX_SHOW_LINE
#define LED_FM_EXIT_NOT_SHOW_LOAD
#define EXIT_BT_NOT_SHOW_LOAD
#define LINEIN_INIT_SHOW_AUX_INTIME
#define LED_SHOW_ONOFF
#endif


//检测是否外接电源
//#define support_ic_chack_dc_in
//#define chack_dc_in_user_PB10   

//*****BAT DETECT *****//
 #define SUPPORT_BAT_DETECT
#ifdef SUPPORT_BAT_DETECT
#define SUPPORT_BAT_DETECT_USE_IO
#define DETECT_EXTERNAL_BAT_USE_PA14
//#define LED_SCREEN_SHOW_BAT_STATUS
//#define LOW_POWER_OFF_STEPS  40 //6v low power mode
//#define LOW_POWER_DIRECT_INTO_IDLE_MODE
#if defined ZY_5021_MX_4018_24_AC4601
#define support_bat_hight_24  
#endif
#define support_power_on_low_power_io_delay  
#ifdef support_power_on_low_power_io_delay
 extern u8  power_delay;
#endif



#define support_low_power_use_extern_io
#ifdef support_low_power_use_extern_io
#define support_low_power_io_pb9
#define support_low_power_io_off
#if 1//def support_low_power_off_control_io
#define support_low_power_show_bat_flash
#define support_low_power_mute_and_amp_power_off
#define support_low_power_no_mute_amp
#endif
//#define support_low_power_io_pc10
#define low_power_value   19
extern bool low_power_sw; // 1  low power  timer  onoff  
#endif

#endif

/**********************  MUZHE ADD **************************/

// adk  
#define KEY_IO_EN      0  ///<IO按键使能
#define KEY_AD_EN      1   ///<AD按键使能
#if KEY_IO_EN
    #define support_io_scan_key_user_PA0_PA4_PA6
    #define support_YHD328_io_scan_mode
#endif   
#if KEY_AD_EN
  #define support_adk_user_PA0
 // #define AD_INTERNAL_PULL_UP //10K
#endif 
//key msg 
//#define ADK_USE_10KEY_MODE
#define ADK_USE_15KEY_MODE
//#define ADK_USE_GENERAL_10KEY_MSG
//#define AKD_USE_ZY_15KEY_MSG
//#define ADK_USE_ZY_10KEY_MSG_JD_SPEC
//#define ADK_USE_ZY_10KEY_MSG_JP_SPEC
//#define  adk_user_6_key_mode_2   
//#define support_led_off_key 
//#define support_change_mode_on_led
#if 0//ndef support_zy_ty_ad_key
// PREV:0R   NEXT:3.3K   MODE: 10K REP:20K  PLAY:33K 
// 0 1 2 3.3 5.1 7.5 10 15 20 33
#define ADK_USE_ZY_GENERAL_10Kup_15KEY_REC_SPEC6
#else
// MODE: 3.3K REP:10K PREV:33K PLAY:0R NEXT:20K
//#define ADK_USE_ZY_GENERAL_10Kup_15KEY_REC_SPEC1
#define ADK_USE_LT_GENERAL_10Kup_15KEY_REC_SPEC
#endif


#define AD_KEY_MAX 15
#define SUPPORT_ONE_KEY_TO_AUX
#define SUPPORT_ONE_KEY_TO_RADIO
#define SUPPORT_ONE_KEY_TO_MP3
#define SUPPORT_ONE_KEY_TO_USB
#define SUPPORT_ONE_KEY_TO_SD
#define SUPPORT_ONE_KEY_TO_BT
//#define SUPPORT_VOICE_ONOFF


#ifdef ADK_USE_10KEY_MODE
#define PULL_UP_RESISTANCE 22   //上拉电阻22K
#define KEY9_RES 0   //PP
#define KEY8_RES 3.3 //MODE
#define KEY7_RES 7.5  //BT
#define KEY6_RES 10  //repeat
#define KEY5_RES 15  //eq
#define KEY4_RES 20  //next/v+ 
#define KEY3_RES 33  //prev/v-
#define KEY2_RES 56  //standby
#define KEY1_RES 100  //stop
#define KEY0_NOKEY_RES 220
#else
#if defined ZY_5021_MX_4018N_2_AC4601
// mode-3.3   prev-33 pp-0r next-20  rep-10k
#endif

#define PULL_UP_RESISTANCE 10   //上拉电阻10K
#define KEYE_RES 0  //PP/rec
#define KEYD_RES 1 //next/ff
#define KEYC_RES 2  //prev/fr
#define KEYB_RES 3.3  //mode/rec_play
#define KEYA_RES 5.1  //v-
#define KEY9_RES 7.5 //v+
#define KEY8_RES 10 //repeat /rec del 
#define KEY7_RES 15  //eq
#define KEY6_RES 20  //next/v+
#define KEY5_RES 33  //prev/v-
#define KEY4_RES 56 //pp/mode
#define KEY3_RES 100 //stop
#define KEY2_RES 200 //bt
#define KEY1_RES 210
#define KEY0_NOKEY_RES 220
#endif

//IR
#define KEY_IR_EN       1   ///<红外遥控使能
#if KEY_IR_EN 
    #define   Ir_user_pa5
    //#define IR_USER_KPL_002    //IR_USER_KPL_001
    //#define IR_FF00_004_21KEY
    //#define ir_user_kpl_ty_msg
    // #define IR_TY_DOUBLE_00FF_807F_23KEY
     #define IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_5
//       #define IR_ZY_NEW_DOUBLE_GENERAL_00FF_807F_26KEY
//     #define IR_SUOAI_001_FF00_21KEY
#define  ir_max_num  22
#define IR_NUMS 2
#endif 


#if KEY_TONE_EN
// #define support_all_KEY_TONE_EN   //任意按键都有按键音
// #define   support_vol_max_tone_en    //音量最大 按键音提示
#endif 



//line 
//#define   line_user_PC13_PC12 
#if 1//def LTDQ_ZY5021_RGB_AC4601
#define AUX_INPUT_SEL_PC13
#else
#define   line_user_PC13_PC12 
#endif

//line 检测
  //#define AUX_DETECT_EN      
#ifdef AUX_DETECT_EN
   #define  support_line_chack_user_PA5
   #define  support_line_unline_to_next_mode   //AUX 不在线到下一个模式
#endif 

//IO接电子地，要相应功能就不接地
#define FM_DGND_DETECT_EN 0
#define FM_DGND_DETECT_USE_PB6
//#define FM_DETECT_LOW_REMOVE
#define AUX_DGND_DETECT_EN 0
#define AUX_DGND_DETECT_USE_PC11

// PP LED 
#define LED_EN                  0   ///<LED指示使能
//#define  PP_LED_USER_PB6 //PB7
//led light
#define NEW_LED_SHOW_METHOD
#ifdef NEW_LED_SHOW_METHOD
#define LED_NUMS 1
#define LED_SHOW_BT 1
#define LED_SHOW_MP3 1
#define LED_SHOW_AUX 1
#define LED_SHOW_FM 1
#define LED_SHOW_IDLE 1
#define LED_SHOW_POWER 1
//#define ALL_LED_CONTROL_TOGETHER
//#define USE_KEY_SWITCH_LED_MODE
//#define LED_SCREEN_SHOW_LED_MODE
#define FM_SCAN_STOP_LIGHT_ON
#endif


//AB/D
//#define support_amP_ab_d
//#define amp_ab_d_user_PA11
//#define ONLY_POWER_ON_MUTE	//amp low mute,power on delay 4s unmute

//MUTE IO 
    #define PA_ENABLE
    #define PA_EN 1
#ifdef PA_ENABLE

        #define   suppoet_mute_user_PB8
        //#define   mute_io_L_is_mute   //  低MUTE   不定义为高MUTE    
        #define support_vol_is_0_mute_amp    //音量到0 MUTE 功放
        #define support_pause_stop_mute_amp
        #define ONLY_POWER_ON_MUTE

       //#define support_amp_power_control
     		//	#define USE_PA14_CONTROL_AMP_POWER
       #define USE_PB7_CONTROL_AMP_POWER
      // #define POWER_ON_KEEP_MUTE_FOR_4S

      #define AMP_IC_WORK_ONFF
	#define support_idle_mode_only_mute_amp

	  //jsuo 20151114 add
      #define support_power_no_media_to_bt
	 #ifdef ONLY_POWER_ON_MUTE
	 extern u8 bPowerOnMuteCnt;
	 #endif
      #define support_bt_disconnect_pause_mute_dac
	  
#if 1//defined ZY_5021B
	 #define support_io_det_mute
	 #ifdef support_io_det_mute
	 #define auto_mute_det_io_use_pb10
	   extern bool auto_mute_sw;
	 extern u8 bt_automute_sw;
	 #endif
	 
	 #define LINE_INIT_MUTE_IO
	 #define POWER_ON_VALUE      9

	// #define  support_aux_plus_in_power_on_mute_moment

	 #define SUPPORT_WOKRMODE
	 #ifdef SUPPORT_WOKRMODE
	 extern u8 workmode;
	 #endif
#endif

#endif 


//开机 默认模式  
 // #define MP3_AUX_BT_FM
 //  #define MP3_BT_FM_AUX
 #define MP3_AUX_FM_BT
 // #define power_on_no_usb_sd_to_bt
#if 1//defined ZY_5021B
 #define POWER_ON_NO_DEV_TO_AUX
 #define PLUG_OUT_DEV_TO_LINEIN_MODE
 #else
 #define usb_sd_out_to_bt_mode
#endif 
 //#define power_on_no_usb_sd_to_LINE
 // #define support_off_fm_mode
//#define POWER_ON_DIRECT_INTO_IDLE
#ifdef POWER_ON_DIRECT_INTO_IDLE
#define IDLE_RESUME_DIRECT_TO_MODE "LineinTask"
#define IDLE_MODE_NOT_RESPONSE_DEVICE_PLUGIN
#define STANDBY_ON_FIND_DEVICE_FIRST
#define POWER_ON_WITH_DEVICE_PLAY_USB_SD_VOICE
#endif

//默认音量  
#define SYS_DEFAULT_VOL_EN      1    ///<系统开机默认音量使能
#if SYS_DEFAULT_VOL_EN
#define SYS_DEFAULT_VOL         30  ///<系统启动默认音量值
#endif



//#define REMOVE_BT_MODE_NOTICE//关蓝牙模式提示音
//#define BT_POWER_ON_USE_WAIT_VOICE
#define POWER_ON_NOT_USE_DISCONNECT_VOICE

#define support_SHORT_PPKEY_Twice_CALL_LAST_NO
#define  support_PP_CALL_ACTIVE_HANGUP_UP   //通话时按PP 挂断电话
#define support_line_pause    //显示PAUSE
#define support_mode_change_vol_min_to_min   10  // 转换模式时音量小于10  则等于10
#define SUPPORT_MUSIC_STOP
#define support_stanby_mod
#define REPEAT_NOT_USE_RANDOM_AND_FOLDER
#define MULTIPLE_DEVICE_PLUGOUT_ONE_AUTO_CHANGE_TO_ANOTHER_DEVICE
#define support_mode_key_user_usb_sd
#define A2DP_AUTO_PLAY_EN 1
#define SUPPORT_BT_TALK_EN 1
#define APPLE_MOBILE_PAUSE_NOT_FLASH_LIGHT_INTIME
#define REPEAT_NOT_USE_RANDOM
#define LED_SHOW_EQ_WITH_NAME
#define EQ_SEQUENCE_ADJ_ANYWAY
//#define DURING_FM_EXITING_TASK_NOT_RESPOND_KEY_MSG //aux exit state press mode key fast and more times system die
#define POWER_ON_WITH_USB_AND_SD_PLAY_USB_FIRST
//#define IO_MUTE_DELAY_ALL_STATE 
//#define BT_NOT_PLAY_IO_MUTE
#define SUPPORT_MUSIC_INTRO_PLAY
#define PROMOTE_SD_PROCESS_SPEED
#define NOTICE_VOICE_VOL_DEFAULT 17

//#define MUSIC_PROMPT_EN
#ifdef MUSIC_PROMPT_EN
#define MUSIC_PROMPT_MODIFY  // USB  SD  erro
#ifdef MUSIC_PROMPT_MODIFY
extern bool power_on_flag;
#endif
#endif
#define USE_BT_MODE_VOICE
//#define SUPPORT_WELCOME_VOICE
//#define POWER_ON_WELCOME_VOICE_PLAYED_IN_IDLE_MODE
#define support_vt_tone_delay  //回连延时报语音

//karaoke detect
#define EXTERN_KOK_DETECT_USE_IO_EN 1
#if EXTERN_KOK_DETECT_USE_IO_EN
//  #define KOK_DETECT_USE_KEY
 #define KOK_DETECT_AUTO_VOL_SET
#ifdef  KOK_DETECT_AUTO_VOL_SET
  extern bool auto_vol_sw; // 0 off   1 on
 extern u8 store_vol;
#endif 
 #define AUTO_VOL_SET_DEC  15
//  #define KOK_DETECT_USE_IO_ADC_VALUE
  #define KOK_DETECT_USE_PB6
//#define KOK_DETECT_USE_PA4
//#define KOK_DETECT_USE_PA11
#endif
#if 1//def LTDQ_ZY5021_RGB_AC4601
#define SUPPORT_RGB_BREATH_LAMP
#endif
#ifdef SUPPORT_RGB_BREATH_LAMP
#define RGB_BREATH_LAMP_IO_PC11PC10PC12
#define RGB_ADC_VALUE_DETECT
#define RGB_DETECT_PIN_USE_PA8
#endif

