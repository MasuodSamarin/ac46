#if 1
/*
*********************************************************************
                        DEBUG MACRO
*********************************************************************
*/
//#define __DEBUG         ////<开启系统打印调试功能


/*
*********************************************************************
                        COMMON MACRO
*********************************************************************
*/
//#define PA_EN                   0    ///<功放mute控制
#define SYS_LVD_EN              1    ///<系统低电检测
#define S10_MODE                0    ///<0:普通SDK     1:S10样机程序
#define POWERUP_DEFAULT_MODE    1    ///<上电默认模式使能
#ifndef BT_TESTER
#define LED_EN                  0    ///<LED指示使能
#define KEY_TONE_EN             0    ///<按键音使能
#else
#define LED_EN                  0    ///<LED指示使能
#define KEY_TONE_EN             0    ///<按键音使能
#endif

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
                        REC MACRO  RTC
*********************************************************************
*/
#ifdef AC46_512K
    #define REC_EN         0         ///512K_SDK
#else
    #define REC_EN         0         ///标准SDK
    #if REC_EN
    #define SUPPORT_ONE_KEY_ENTER_START_REC  //music
    #define ENTER_INTO_REC_MODE_AUTO_START_REC //music
    #define MODE_CHANGE_SKIP_REC_CASE
    #define AFTER_RECORD_PLAY_LAST_RECORDED_FILE
    #define ACCESS_REC_FILE_BY_FOLDER_NAME
    #define FM_AUX_BT_START_REC_KEY_SECOND_PRESS_STOP_REC
    #define SUPPORT_AUX_FM_BT_REPLAY_KEY
    #define SUPPORT_AUX_FM_BT_SHOW_REC_TIME
    #endif
#endif


/*
*********************************************************************
                        FM MACRO  RTC
*********************************************************************
*/
#ifdef AC46_512K
    #define FM_RADIO_EN         0       ///512K_SDK
#else
    #define FM_RADIO_EN         1       ///标准SDK
#endif

/*
*********************************************************************
                        RTC MACRO  RTC
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
#define TEST_INDEX_MODE     1     //指标性能测试(使用MT8852A仪器测试)
#define TEST_FCC_MODE       2     //测试fcc认证
#define TEST_FRE_OFF_MODE   3     //测试频偏(使用频谱分析仪-手提测试仪-中心频率默认2420M)


#define BT_MODE        NORMAL_MODE
#ifndef BT_TESTER
#define BT_BACKMODE         0
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
        #define UI_ENABLE       0     ///>标准SDK UI_显示
    #endif
#endif
#endif


/*
*********************************************************************
                        UI MACRO
*********************************************************************
*/
			/* 外置功放IC，话筒IC*/
//#define SUPPORT_PT2313
#ifdef SUPPORT_PT2313
	//#define PT2313_CLK_DATA_USE_PA15PA14
	//#define PT2313_CLK_DATA_USE_PB10PB9
  //#define PT2313_CLK_DATA_USE_PC10PA6
    #define PT2313_CLK_DATA_USE_PB8PB7
		
	//#define pt2313_use_rf_lf_as_sub
			
			//配套2313 通道设置
			
#define Aud_SwRadio				0x00		//Stereo 2
#define Aud_SwMP3				0x00		//Stereo 2
#define Aud_SwBt			    0x00		//Stereo 2
#define Aud_SwAUX				0x03		//Stereo 3
#define Aud_SwCD				0x01		//Stereo 3
#define Aud_SwVcd				0x02		//Stereo 3
#define Aud_SwNoting			0x03		//Stereo 4  *
			
#define MAIN_VOL_MAX         62
#define VOLUME_DEFUALT       32
#define SWVOL_DEFUALT        22
#define  FLFR_DEFUALT           28  //这个 值是设 左右喇叭的 起始值  软件内没有减价这个值  如果音量过大可以减小这个值  最大31 
#define BASS_DEFAULT 7
#define TREBLE_DEFAULT 9
			
			//#define support_mute_key
		//#define Support_MSG_RESET
			//#define Support_MSG_MUSIC_STOP
		//#define SUPPORT_MSG_FRONT_LEFT
		//#define SUPPORT_MSG_FRONT_RIGHT
#define Support_MSG_BASS
#define Support_MSG_TREBLE
#define Support_MSG_SWVOL
//#define Support_MSG_MIC_ECO_VOL_KEY		
			//#define Support_MSG_DSP
			//#define Support_MSG_LOUDNESS
#define SUPPORT_MAIN_VOL_KEY  
#define supper_user_pt2313_ctrl_main_vol
#define support_menu_mode     //多个模式 MENU键切换  用VOL +- 调节
#define supper_bass_treble_max_28
			//#define MENU_NOT_SWTICH_MAIN_VOL
#define LED_TREBLE_SHOW_H
#define LED_SWVOL_SHOW_b
#define LINE_IN_USE_PT2313
	//#define LINE_LED_SHOW_AC3
#ifdef support_menu_mode
			enum
			{
				   MENU_MAIN_VOL_MODE=0,
				   MENU_TREBLE_MODE,		   
				   MENU_SWVOLL_MODE,
				   MENU_MAX_MODE,
					   MENU_OK_VOL_MODE,
					   MENU_ECHO_MODE,
					   MENU_FRONT_LEFT_MODE,
					   MENU_FRONT_RIGHT_MODE,
					   MENU_BASS_MODE,
					   MENU_SL_MODE, //surround L
					   MENU_SR_MODE //surround R
			};
#endif 
			
#endif
			
//#define SUPPORT_M62429
#ifdef SUPPORT_M62429
#define M62429_CLK_DATA_USE_PA4PA6
	//#define support_use_pin1pin2_as_mic_vol
#define KARAOKE_MIC_DEFAULT_VOL 28
#define KARAOKE_ECHO_DEFAULT_VOL 16
#endif
			
//#define SUPPORT_ENCODER
#ifdef SUPPORT_ENCODER
//#define ENCODE_PIN_USE_PB9PB8
#define ENCODE_PIN_USE_PB9PB10

//#define SUPPORT_TWO_ENCODER
//#define ENCODER1_PIN_USE_PB7PB6
//#define ENCODER1_ADJUST_MIC_VOL
#endif


//****led screen setting******/
#if UI_ENABLE
//#define LED_ID_KF8845AB
#define LED_ID_8848
//#define LED_ID_4018N_2
//#define LCD_ID_JXH_S6002A
//#define LCD_ID_XH600002A
//#define LED_ID_YUNKE01
// #define LED_ID_JW5348_1A

#define LED_7PIN_MODE
//#define SUPPORT_TM1628_MODE
//#define TM1628_MODE 0x03
//#define TM1628_DATA_CLK_STB_USE_PB10PB9PB8

//#define SUPPORT_LCD_4COM_9SEG_MODE //LCD段码屏
//  #define SUPPORT_LCD_5COM_8SEG_MODE
//#define LED_USE_7PIN_PA7__PA11PA14PA15
  #define LED_USE_7PIN_PA4PA6_PA11
//#define LED_USE_7PIN_PB8PB7PB6PA15PA14PA10PA9
//#define LED_USE_7PIN_PA9__PA15PB6PA7
//  #define LCD_USE_COMpb6789_GRIDpa151411_6_4
//   #define LCD_USE_COMpb10_pb6_GRIDpa6_pa15
//#define LED_7PIN_REVERSE
#define LED_COM_MAX 7
#define LED_8NUMS 4
#define LED_8GRIDS 7
#define LED_ICON_NUMS 8
//#define LED_EQ_NUMS  8

#define SUPPORT_FLASH_ICON
#define SUPPORT_FLASH_CHAR

//#define LED_SHOW_SCREEN_FREQUENCE
#ifdef LED_SHOW_SCREEN_FREQUENCE
#define SUPPORT_EQ_FREQUENCE
//#define EQ_ADC_VALUE_DETECT
//#define EQ_DETECT_PIN_USE_PA11
//#define NO_VOICE_EQ_SHOW
#endif
//#define TEST_PANEL_LED
//#define TEST_SHOW_ALL

#ifdef SUPPORT_FLASH_CHAR
#define SUPPORT_LED_BLUE_STRING_FLASH
#define SUPPORT_MUTE_FLASH
//#define MUTE_FLASH_ZERO_VOL
#define MUTE_FLASH_ALL_SCREEN
#endif
#define LED_SHOW_DEVICE_PLUGIN
#define LED_ICON_BT_FLASH
#define LED_SHOW_BT_EQ
#define LED_SHOW_POWER_OFF_STRING " OFF"
#define LED_SHOW_INTRO_STRING "SCAN"
#define LED_SHOW_PREV_NEXT_FOLDER_SWITCH
#define LED_SHOW_MP3_PAUSE
#define LED_SHOW_TWO_THREE_INPUTNUM_POS
//#define POWER_ON_LED_SHOW__q1

#define LED_EXIT_MP3_NOT_SHOW_LOAD
#define MP3_NEXT_MODE_IS_AUX 1
#define EXIT_AUX_TASK_NOT_SHOW_LOAD
//#define LED_SWITCH_FM2AUX_SHOW_LINE
#define LED_FM_EXIT_NOT_SHOW_LOAD
#define EXIT_BT_NOT_SHOW_LOAD
#define LINEIN_INIT_SHOW_AUX_INTIME
#else
#define LED_COM_MAX 7
#define LED_8NUMS 4
#define LED_8GRIDS 7
#define LED_ICON_NUMS 8
#endif


//检测是否外接电源
//#define support_ic_chack_dc_in
//#define chack_dc_in_user_PB10   

//*****BAT DETECT *****//
//#define SUPPORT_BAT_DETECT
#ifdef SUPPORT_BAT_DETECT
#define LED_SCREEN_SHOW_BAT_STATUS
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
#endif 
//key msg 
#define ADK_USE_10KEY_MODE
//#define ADK_USE_11KEY_MODE
//#define ADK_USE_GENERAL_10KEY_MSG
//#define AKD_USE_ZY_15KEY_MSG
//#define ADK_USE_ZY_10KEY_MSG
 // #define ADK_USE_ZY_MOGONG_12KEY_msg
//  #define ADK_USE_ZY_MOGONG_11KEY
//   #define ADK_USE_ZY_YS3608_10Kup_15KEY_SPEC
#define ADK_USE_ZY_10KEY_MSG

//#define  adk_user_6_key_mode_2   
//#define support_led_off_key 
//#define support_change_mode_on_led
#define AD_KEY_MAX 10
#define SUPPORT_ONE_KEY_TO_AUX
#define SUPPORT_ONE_KEY_TO_RADIO
#define SUPPORT_ONE_KEY_TO_MP3
#define SUPPORT_ONE_KEY_TO_USB
#define SUPPORT_ONE_KEY_TO_SD
#define SUPPORT_ONE_KEY_TO_BT
//#define SUPPORT_ONE_KEY_TO_AC3
#define SUPPORT_ONE_KEY_TO_CD
#define SUPPORT_ONE_KEY_TO_DVD

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
#elif defined(ADK_USE_11KEY_MODE)
#define PULL_UP_RESISTANCE 10   //上拉电阻22K
#define KEYA_RES 0   //pp
#define KEY9_RES 1 //next/ff
#define KEY8_RES 2  //prev/fr
#define KEY7_RES 3.3  //mode
#define KEY6_RES 10  //repeat
#define KEY5_RES 15  //eq
#define KEY4_RES 20  //next/v+
#define KEY3_RES 33 //prev/v-
#define KEY2_RES 56 //pp/mode
#define KEY1_RES 100 //stop
#define KEY0_NOKEY_RES 330
#else
#define PULL_UP_RESISTANCE 10   //上拉电阻10K
#define KEYE_RES 0  //prev
#define KEYD_RES 1 //pp
#define KEYC_RES 2  //next
#define KEYB_RES 3.3  //mode
#define KEYA_RES 5.1 //vol-  
#define KEY9_RES 7.5 //vol+
#define KEY8_RES 10 //next/v+
#define KEY7_RES 15  //prev/v-
#define KEY6_RES 20  //
#define KEY5_RES 33  //pp/mode
#define KEY4_RES 56 //repeat
#define KEY3_RES 100 //eq
#define KEY2_RES 180 //stop
#define KEY1_RES 200
#define KEY0_NOKEY_RES 220
#endif

//IR
#define KEY_IR_EN       1   ///<红外遥控使能
#if KEY_IR_EN 
   #define   Ir_user_pa10
       //#define IR_USER_KPL_002    //IR_USER_KPL_001
       //#define IR_FF00_004_21KEY
       //#define ir_user_kpl_ty_msg
       // #define IR_TY_DOUBLE_00FF_807F_23KEY
    #define IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY
     // #define IR_USE_HL_Q1_FF00_22KEY
        //  #define IR_ZY_NEW_DOUBLE_GENERAL_00FF_807F_26KEY
   #define  ir_max_num 	22
   #define IR_NUMS 2
#endif 


#if KEY_TONE_EN
// #define support_all_KEY_TONE_EN   //任意按键都有按键音
// #define   support_vol_max_tone_en    //音量最大 按键音提示
#endif 



//line 
#define   line_user_PC13_PC12 
//line 检测
  //#define AUX_DETECT_EN      
#ifdef AUX_DETECT_EN
   #define  support_line_chack_user_PA5
   #define  support_line_unline_to_next_mode   //AUX 不在线到下一个模式
#endif 

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
#define support_amP_ab_d
#define amp_ab_d_user_PC15
//#define AB_D_HI_LOW_REVISE
//#define ONLY_POWER_ON_MUTE	//amp low mute,power on delay 4s unmute

//MUTE IO 
  //  #define   PA_ENABLE
    #define PA_EN 0
#ifdef PA_ENABLE
        #define   pa_mute_use_pin_PC15
        #define   mute_io_L_is_mute   //  低MUTE   不定义为高MUTE    
        #define support_vol_is_0_mute_amp    //音量到0 MUTE 功放
        #define support_pause_stop_mute_amp
        //#define support_amp_power_control
        #ifdef support_amp_power_control
        #define USE_PA14_CONTROL_AMP_POWER
        #define POWER_ON_KEEP_MUTE_FOR_4S
        #endif
#endif 


//开机 默认模式  
 // #define MP3_AUX_BT_FM
//   #define MP3_BT_FM_AUX
 #define MP3_AUX_FM_BT

//  #define power_on_no_usb_sd_to_bt
 #define POWER_ON_NO_DEV_TO_AUX
 #define PLUG_OUT_DEV_TO_LINEIN_MODE



//默认音量  
#define SYS_DEFAULT_VOL_EN      1    ///<系统开机默认音量使能
#if SYS_DEFAULT_VOL_EN
#define SYS_DEFAULT_VOL         30  ///<系统启动默认音量值
#endif



#define REMOVE_BT_MODE_NOTICE     //关蓝牙模式提示音
#define support_SHORT_PPKEY_Twice_CALL_LAST_NO
#define  support_PP_CALL_ACTIVE_HANGUP_UP   //通话时按PP 挂断电话
//#define support_line_pause    //显示PAUSE
#define support_mode_change_vol_min_to_min   10  // 转换模式时音量小于10  则等于10
#define SUPPORT_MUSIC_STOP
#define REPEAT_NOT_USE_RANDOM_AND_FOLDER
#define REPEAT_NOT_USE_RANDOM
#define support_stanby_mod
//#define SUPPORT_BT_TALK_EN
#define A2DP_AUTO_PLAY_EN 1
#define APPLE_MOBILE_PAUSE_NOT_FLASH_LIGHT_INTIME
//#define EXIT_BLUE_MODE_DISCONNECT_VOICE  //退出不管连接与否都有声音提示
#define MULTIPLE_DEVICE_PLUGOUT_ONE_AUTO_CHANGE_TO_ANOTHER_DEVICE
#define support_mode_key_user_usb_sd
#define BT_POWER_ON_USE_WAIT_VOICE
#define SUPPORT_MUSIC_INTRO_PLAY
#define SUPPORT_MUSIC_FOLDER_OPERATION
#define FM_SCAN_DELAY  
#define LED_SHOW_EQ_WITH_NAME
#define EQ_SEQUENCE_ADJ_ANYWAY
//#define DURING_FM_EXITING_TASK_NOT_RESPOND_KEY_MSG
#define POWER_ON_WITH_USB_AND_SD_PLAY_USB_FIRST
#define support_vt_tone_delay  //回连延时报语音
//#define NOTICE_VOICE_VOL_DEFAULT 20
//#define SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE //no device but want to under at mp3 mode
#ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE
enum{
  mode_cd=0,
  mode_dvd,
  mode_linein_max,
  mode_aux,
  mode_ac3,
  mode_mp3_nodevice,
}MODE_IN_LINEIN;
#define LINEIN_MULTIPLY_DEFAULT_MODE 0
//#define SUPPORT_MP3_IDEL_MODE_IN_LINEIN_MODE
//#define SUPPORT_AC3_MODE_IN_LINEIN_MODE
#define SUPPORT_CD_MODE_IN_LINEIN_MODE
#define SUPPORT_DVD_MODE_IN_LINEIN_MODE
#define MODE_KEY_MP3_PREV_MODE "BtStackTask"
#define MODE_KEY_MP3_NEXT_MODE "LineinTask"
#endif

