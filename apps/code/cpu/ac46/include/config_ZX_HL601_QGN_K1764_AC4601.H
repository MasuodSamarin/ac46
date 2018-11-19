

/*
*********************************************************************
                        DEBUG MACRO
*********************************************************************
*/
//#define __DEBUG         ////<开启系统打印调试功能


#ifdef __DEBUG

//#define DEV_MANAGE_DEBUG
#ifdef DEV_MANAGE_DEBUG
#define FILE_OP_DEBUG
#define LOGDEV_LIST_DEBUG
#define VFS_DEBUG
#define MBR_DEBUG
#define DRV_MANAGE_DEBUG
#endif

#endif

/*
*********************************************************************
                        COMMON MACRO
*********************************************************************
*/
#define PA_EN                   0    ///<功放mute控制
#define SYS_LVD_EN              1    ///<系统低电检测
#define S10_MODE                0    ///<0:普通SDK     1:S10样机程序
#define POWERUP_DEFAULT_MODE    1    ///<上电默认模式使能
#define MUSIC_DEC_RECORD_DEV    0    ///<解码记录掉电前最后播放的设备
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

/*
*********************************************************************
                        FM MACRO  RTC
*********************************************************************
*/
#ifdef AC46_512K
    #define FM_RADIO_EN         0       ///
#else
    #define FM_RADIO_EN         1
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
    #ifdef AC46_512K
        #define BT_HID_INDEPENDENT_MODE     0          //512K_HID拍照的独立模式只支持非后台
    #else
        #define BT_HID_INDEPENDENT_MODE     0          //HID拍照的独立模式只支持非后台
    #endif
#endif
#else
#define BT_BACKMODE         0
#endif

#ifdef AC46_512K
    #define BT_PHONE_NUMBER     0          //来电报号
#else
    #define BT_PHONE_NUMBER     0          //来电报号
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
#define DEBUG_UART   UART0  /*标准SDK打印口*/
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
    #define SDMMC1_EN       0   // 1
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
        #define USB_DISK_EN     1
        #define USB_PC_EN       1
    #endif/*S10_MODE*/
#endif

#define SPI_FLASH_BLK_NUM   8
#define POWERUP_DEV_IGNORE       ///<插着设备上电是否响应U盘或SD
#define AUX_OUT_WITHOUT_CNT

/*
*********************************************************************
                        UI MACRO
*********************************************************************
*/
		/* 外置功放IC，话筒IC*/
#define SUPPORT_PT2313
#ifdef SUPPORT_PT2313
//#define PT2313_CLK_DATA_USE_PA15PA14
//#define PT2313_CLK_DATA_USE_PB10PB9



  #define PT2313_CLK_DATA_USE_PC10PA6

#define pt2313_use_rf_lf_as_sub
		
		//配套2313 通道设置
		
#define Aud_SwRadio				0x00		//Stereo 2
#define Aud_SwMP3				0x00		//Stereo 2
#define Aud_SwBt			    0x00		//Stereo 2
#define Aud_SwAUX				0x01		//Stereo 3
#define Aud_SwCD				0x02		//Stereo 3
#define Aud_SwVcd				0x03		//Stereo 3
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
#define Support_MSG_MIC_ECO_VOL_KEY		
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
  			   MENU_OK_VOL_MODE,
  			   MENU_ECHO_MODE,
			   MENU_MAX_MODE,
				   MENU_FRONT_LEFT_MODE,
				   MENU_FRONT_RIGHT_MODE,
				   MENU_BASS_MODE,
				   MENU_SL_MODE, //surround L
				   MENU_SR_MODE //surround R
		};
#endif 
		
#endif
		
#define SUPPORT_M62429
#ifdef SUPPORT_M62429

#define M62429_CLK_DATA_USE_PA4PA6


//#define support_use_pin1pin2_as_mic_vol
#define KARAOKE_MIC_DEFAULT_VOL 28
#define KARAOKE_ECHO_DEFAULT_VOL 16
#endif
		
#define SUPPORT_ENCODER
#ifdef SUPPORT_ENCODER

#define ENCODE_PIN_USE_PB9PB8


#endif

#define UI_ENABLE       1     ///>UI_显示

//LED    
#if 0//UI_ENABLE
#define support_LED7_USER_PA7PA8PA9PA10PA11PA14PA15
#define led_io_180_mirror
#define support_aux_led_disp_line     //屏上显示"LINE"
#define support_mute_led_all_flish    //MUTE 全屏闪烁
#define support_led_disp_pause
#define  support_yl_3520


//电池符号 
  #define   led_icon_disp_vat_volage
  #ifdef led_icon_disp_vat_volage
  #define  support_battery_mode_check    //电压状态显示 
  #endif 
  
#define   support_user_dsp_eq     //频谱显示
#define support_bt_waiting_conn_filsh_led   //等待连接 LED 闪闪
#endif 
//****led screen setting******/
#define LED_SCREEN_EN
#ifdef LED_SCREEN_EN
//#define LED_ID_KF8845AB
#define LED_ID_8848
//#define LED_ID_4018N_2
//#define LED_ID_JW4018D_1A
#define LED_7PIN_MODE
#define LED_USE_7PIN_PA7__PA11PA14PA15
//#define LED_USE_7PIN_PB8PB7PB6PA15PA14PA10PA9
//#define LED_USE_7PIN_PA9__PA15PB6PA7
//#define LED_USE_7PIN_PA6PA7_PA9PA10PA11PA14PA15
#define LED_7PIN_REVERSE
#define LED_COM_MAX 7
#define LED_8NUMS 4
#define LED_8GRIDS 7
#define LED_ICON_NUMS 8
#define SUPPORT_FLASH_ICON
#define SUPPORT_FLASH_CHAR

#ifdef SUPPORT_FLASH_CHAR
#define SUPPORT_LED_BLUE_STRING_FLASH
#define SUPPORT_MUTE_FLASH
//#define MUTE_FLASH_ZERO_VOL
#define MUTE_FLASH_ALL_SCREEN
#endif
//#define LED_SHOW_DEVICE_PLUGIN

//#define TEST_PANEL_LED
//#define LED_EQ_SHOW_ONLY_TWO_CHAR_EX_AT_MIDDLE

#define LED_SHOW_DEVICE_PLUGIN
#define LED_SHOW_BT_EQ
#define LED_SHOW_MP3_PAUSE
#define LED_SHOW_POWER_OFF_STRING " OFF"
#define LED_SHOW_INTRO_STRING "SCAN"

#define LED_EXIT_MP3_NOT_SHOW_LOAD
#define MP3_NEXT_MODE_IS_AUX 0
#define EXIT_AUX_TASK_NOT_SHOW_LOAD
//#define LED_SWITCH_FM2AUX_SHOW_LINE
#define LED_FM_EXIT_NOT_SHOW_LOAD
#define EXIT_BT_NOT_SHOW_LOAD
#define LINEIN_INIT_SHOW_AUX_INTIME
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
#define KEY_IO_EN      0 ///<IO按键使能
#define KEY_AD_EN      1   ///<AD按键使能
#if KEY_IO_EN
    #define support_io_scan_key_user_PA0_PA4_PA6
    #define support_YHD328_io_scan_mode
    #define adk_user_6_key_mode
#endif   
#if KEY_AD_EN
  #define support_adk_user_PA0
 // #define SUPPORT_PANEL_KEY_USE_TWO_AD_IO
//  #define TWO_AD_IO_USE_DIFF_RESISTANCE
//  #define adk_io_use_pa0pa8
#endif 
//key msg 
#define ADK_USE_11KEY_MODE
//#define ADK_USE_15KEY_MODE
//#define ADK_USE_GENERAL_10KEY_MSG
//  #define ADK_USE_TF_10KEY_MSG
#define ADK_USE_HY_GENERAL_11KEY
//#define AKD_USE_ZY_15KEY_MSG
//#define  adk_user_6_key_mode_2   
//#define support_led_off_key 
//#define support_change_mode_on_led
#define AD_KEY_MAX 11
#define SUPPORT_ONE_KEY_TO_AUX
#define SUPPORT_ONE_KEY_TO_RADIO
#define SUPPORT_ONE_KEY_TO_MP3
#define SUPPORT_ONE_KEY_TO_USB
#define SUPPORT_ONE_KEY_TO_SD
#define SUPPORT_ONE_KEY_TO_BT
#define SUPPORT_ONE_KEY_TO_AC3

#ifdef ADK_USE_11KEY_MODE
#define PULL_UP_RESISTANCE 22   //上拉电阻22K
#define KEYA_RES 0   //pp
#define KEY9_RES 1   //rec
#define KEY8_RES 3.3 //10+
#define KEY7_RES 6.2 //prev/v-
#define KEY6_RES 9.1  //next/v+
#define KEY5_RES 15  //mute
#define KEY4_RES 24  //stop
#define KEY3_RES 51  //mode
#define KEY2_RES 100  //eq
#define KEY1_RES 220 //repeat
#define KEY0_NOKEY_RES 330
#ifdef TWO_AD_IO_USE_DIFF_RESISTANCE
#define PULL_UP_RESISTANCE1 22   //上拉电阻20K
#define KEYA_RES1 0  //  0  
#define KEY9_RES1 3 //  9
#define KEY8_RES1 6.2 //  8
#define KEY7_RES1 9.1  //  3
#define KEY6_RES1 15  //  6
#define KEY5_RES1 24  // 2
#define KEY4_RES1 33 //  1
#define KEY3_RES1 51 //  5
#define KEY2_RES1 100 // 4
#define KEY1_RES1 220  //  7
#define KEY0_NOKEY_RES1 330
#endif
#else
#define PULL_UP_RESISTANCE 22   //上拉电阻10K
#define KEYE_RES 0  //one key to aux
#define KEYD_RES 1 //stop
#define KEYC_RES 3.3  //pp
#define KEYB_RES 6.2  //usb/sd
#define KEYA_RES 9.1  //mode  
#define KEY9_RES 4.3 //vol-
#define KEY8_RES 5.6 //next/vol+  
#define KEY7_RES 16  //repeat
#define KEY6_RES 20  //eq
#define KEY5_RES 27  //one key to radio
#define KEY4_RES 47 //prev/vol-
#define KEY3_RES 91 //vol+
#define KEY2_RES 180
#define KEY1_RES 200
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
    // #define IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY
    //#define IR_TF_THREE_GENERAL_FF00_FD02_7F80
 //#define IR_ZX_ONE_00FF_GENERAL_21KEY
  #define IR_ZX_HL601_QGN_FF00_35KEY
 #define  ir_max_num	 36
 #define IR_NUMS 1
#endif 


#if KEY_TONE_EN
// #define support_all_KEY_TONE_EN   //任意按键都有按键音
// #define   support_vol_max_tone_en    //音量最大 按键音提示
#endif 



//line 
#define   line_user_PC13_PC12 
//line 检测
 // #define AUX_DETECT_EN      
#ifdef AUX_DETECT_EN
   #define  support_line_chack_user_PC11
   #define  support_line_unline_to_next_mode   //AUX 不在线到下一个模式
#endif 

//IO接电子地，要相应功能就不接地
#define FM_DGND_DETECT_EN 0
#define FM_DGND_DETECT_USE_PC10
#define AUX_DGND_DETECT_EN 0
#define AUX_DGND_DETECT_USE_PC11

// PP LED 
#define LED_EN                  0   ///<LED指示使能
//#define  PP_LED_USER_PB6 //PB7
//led light
//#define NEW_LED_SHOW_METHOD
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



//MUTE IO 
    #define   PA_ENABLE
#ifdef PA_ENABLE
        #define   pa_mute_use_pin_PC11
        //#define   mute_io_L_is_mute   //  低MUTE   不定义为高MUTE    
        #define support_vol_is_0_mute_amp    //音量到0 MUTE 功放
        #define support_pause_stop_mute_amp
#endif 


  //开机 默认模式  
    #define MP3_AUX_BT_FM
  // #define MP3_BT_FM_AUX
   // #define power_on_no_usb_sd_to_bt
     #define POWER_ON_NO_DEV_TO_AUX
  #define PLUG_OUT_DEV_TO_LINEIN_MODE



//默认音量  
#define SYS_DEFAULT_VOL_EN      1    ///<系统开机默认音量使能
#if SYS_DEFAULT_VOL_EN
#define SYS_DEFAULT_VOL         30  ///<系统启动默认音量值
#endif
#define SYS_VOL_MAX   30
//#define LED_SHOW_VOL_MAX 30

#define OFF_BPF_BT_MP3     //关蓝牙模式提示音
#define support_SHORT_PPKEY_Twice_CALL_LAST_NO
#define  support_PP_CALL_ACTIVE_HANGUP_UP   //通话时按PP 挂断电话
#define support_line_pause    //显示PAUSE
#define support_mode_change_vol_min_to_min   10  // 转换模式时音量小于10  则等于10
#define SUPPORT_MUSIC_STOP
#define support_stanby_mod
#define support_mode_key_user_usb_sd
#define APPLE_MOBILE_PAUSE_NOT_FLASH_LIGHT_INTIME
#define EXIT_BLUE_MODE_DISCONNECT_VOICE  //退出不管连接与否都有声音提示
#define SUPPORT_MUSIC_INTRO_PLAY
#define A2DP_AUTO_PLAY_EN 1
//#define support_aux_led_disp_line
#define support_off_phone_call
#define SUPPORT_FM_PAUSE
#define DURING_FM_EXITING_TASK_NOT_RESPOND_KEY_MSG //aux exit state press mode key fast and more times system die
extern u8 bExitFMStateCnt;
#define REPEAT_NOT_USE_RANDOM_AND_FOLDER
#define POWER_ON_WITH_USB_AND_SD_PLAY_USB_FIRST
#define MULTIPLE_DEVICE_PLUGOUT_ONE_AUTO_CHANGE_TO_ANOTHER_DEVICE
#define SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE //no device but want to under at mp3 mode
#ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE
enum{
  mode_aux=0,
  mode_ac3,
  mode_linein_max,
  mode_mp3_nodevice,
  mode_cd,
  mode_dvd,
}MODE_IN_LINEIN;
#define LINEIN_MULTIPLY_DEFAULT_MODE 1
//#define SUPPORT_MP3_IDEL_MODE_IN_LINEIN_MODE
#define SUPPORT_AC3_MODE_IN_LINEIN_MODE
#define SUPPORT_CD_MODE_IN_LINEIN_MODE
#define SUPPORT_DVD_MODE_IN_LINEIN_MODE
#define MODE_KEY_MP3_PREV_MODE "BtStackTask"
#define MODE_KEY_MP3_NEXT_MODE "LineinTask"
#endif

#define support_vt_tone_delay  //回连延时报语音

