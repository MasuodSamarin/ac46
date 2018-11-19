
#if 1
/*
*********************************************************************
                        DEBUG MACRO
*********************************************************************
*/

// #define __DEBUG         ////<开启系统打印调试功能

//  #define SSM_Q535_2REC_8426_AC461_V10  

 #define SSM_Q535_2REC_4018_2_AC461_V10  
 
#define modify_20151025    //通用
#define suppport_aux_singe_no_swap // aux 输出 不反相 

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
    #define BT_PHONE_NUMBER     1          //来电报号
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
//        #define FM_AUX_BT_START_REC_KEY_SECOND_PRESS_STOP_REC
        #define SUPPORT_AUX_FM_BT_REPLAY_KEY
        #define SUPPORT_AUX_FM_BT_SHOW_REC_TIME
        #define SUPPORT_REC_DELETE_FILTER_NOT_REC_FILE
        #define SUPPORT_REPLAY_CANCEL_FOLDER_REPEAT_AND_PLAY_NOT_REC_FILES
        #define SUPPORT_PRESS_REC_KEY_AGAIN_STOP_AND_PLAY_LAST_REC_FILE
        //#define MODIFY_REC_FILE_NAME_FOR_ZY
    
         #ifdef modify_20151025	 
		 #ifdef AFTER_RECORD_PLAY_LAST_RECORDED_FILE
		 extern bool bIfRecordFolder;
		 #endif		 
            #define LED_SHOW_DEL
			
            #define SUPPORT_LED_SHOW_DEL // JSUO 20151026 MODIFY

		 #ifdef LED_SHOW_DEL
		 #define LED_SHOW_DEL_MODIFY  // JSUO ADD  20151025
		 extern u8 bLedShowDelCnt;
		 #endif
			
            #define SUPPORT_SSM_LED_REC_RECPLAY_ICON_SET // JSUO ADD  20151025

		#define SUPPORT_LYX_RECPLAY_REPEAT_ONE
		
 		#define support_rec_play_first_mute_after_rec
        
	#define support_rec_cancel_repeat_state_changemode_and_plus_out //jsuo 20160307 add
	   	 
            //    #define support_rec_recplay_notice
//            #define SUPPORT_REC_STOP_PLAY_REC_FILE
            #ifdef SUPPORT_REC_STOP_PLAY_REC_FILE
            extern u32 curr_dir_file_num;
            extern  bool  play_rec_last_file;   
            extern  bool  aux_fm_rec_sw;   
            #endif  

//            #define SUPPORT_REC_KEY_FIRST_CANCEL_RECPLAY_STATE
            #ifdef SUPPORT_REC_KEY_FIRST_CANCEL_RECPLAY_STATE
            extern  u8  bCancelRecplayFlag;   
            #endif  
			
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

//#define UI_ENABLE       1     ///>UI_显示
#if UI_ENABLE==0  // have no led screen enable the ir number input function
#define IR_NUM_INPUT_EN 1
#endif

//LED    
//****led screen setting******/
#if UI_ENABLE
//#define LED_ID_KF8845AB
//#define LED_ID_8848
//#define LED_ID_4018N_2
//#define LED_ID_JW4018D_1

//#define LED_ID_XTX2401_KB
#define LED_7PIN_MODE
//#define LED_7PIN_PROMOTE_SPEED
//#define LED_USE_7PIN_PA7__PA11PA14PA15
//#define LED_USE_7PIN_PB8PB7PB6PA15PA14PA10PA9
//#define LED_USE_7PIN_PA9__PA15PB6PA7
#define LED_USE_7PIN_PA6PA7_PA9PA10PA11PA14PA15
#define LED_7PIN_REVERSE
#define LED_COM_MAX 7
#define LED_8NUMS 4
#define LED_8GRIDS 7

#define support_aux_led_disp_line

#ifdef SSM_Q535_2REC_8426_AC461_V10
  #define LED_ID_KF8426GH
  #ifdef LED_ID_KF8426GH
  #define LED_NO_BT_ICON  //JW-84267-2
  #endif
#define LED_ICON_NUMS 10
#else
#define LED_ID_40N18SRB_15
//#define LED_ID_SDX_88T48
#define LED_ICON_NUMS 7
#endif
#define SUPPORT_FLASH_ICON
#define SUPPORT_FLASH_CHAR

#ifdef SUPPORT_FLASH_CHAR
#define SUPPORT_LED_BLUE_STRING_FLASH
#define SUPPORT_MUTE_FLASH
//#define MUTE_FLASH_ZERO_VOL
#define MUTE_FLASH_ALL_SCREEN
#endif
//#define LED_SHOW_DEVICE_PLUGIN
#define LED_SHOW_POWER_OFF_STRING " OFF"
#define LED_SHOW_INTRO_STRING "SCAN"
#define LED_FILE_NUM_NOT_SHOW_PREVIOUS_ZERO
#define LED_IR_NUM_NOT_SHOW_PREVIOUS_ZERO
#define LED_SHOW_BT_EQ
//#define TEST_PANEL_LED
#define LED_SHOW_PREV_NEXT_FOLDER_SWITCH
#define LED_SHOW_MP3_PAUSE
//#define LED_SHOW_DEVICE_PLUGIN
//#define LED_SHOW_DEVICE_TYPE_SWITCH
//#define LED_BT_STATE_SHOW_STRING_Bt
#define POWER_ON_LED_SHOW__HI_
//#define LED_BT_STATE_SHOW_STRING_Bt
#define support_line_pause    //显示PAUSE
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
    #define adk_user_6_key_mode
#endif   

#if KEY_AD_EN
  //#define support_adk_user_PA0
 // #define support_adk_user_PA8
 #define SUPPORT_PANEL_KEY_USE_TWO_AD_IO
 //#define TWO_AD_IO_USE_DIFF_RESISTANCE
 #define adk_io_use_pa0pa8
 //#define ADK_PANEL_KEY_REVERSE
#endif 
//key msg 
#define ADK_USE_12KEY_MODE
//#define ADK_USE_15KEY_MODE
//#define ADK_USE_GENERAL_10KEY_MSG
//  #define ADK_USE_TF_10KEY_MSG
//#define ADK_USE_SSM_24KEY_MSG
#ifdef SSM_Q535_2REC_4018_2_AC461_V10
#define ADK_USE_SSM_24KEY_REC_MSG_7
#else
#define ADK_USE_SSM_24KEY_REC_MSG_1
#endif
//#define AKD_USE_ZY_15KEY_MSG
//#define  adk_user_6_key_mode_2   
//#define support_led_off_key 
//#define support_change_mode_on_led
#define AD_KEY_MAX 24
#define SUPPORT_ONE_KEY_TO_AUX
#define SUPPORT_ONE_KEY_TO_RADIO
#define SUPPORT_ONE_KEY_TO_MP3
#define SUPPORT_ONE_KEY_TO_USB
#define SUPPORT_ONE_KEY_TO_SD
#define SUPPORT_ONE_KEY_TO_BT
#define SUPPORT_VOICE_ONOFF

#ifdef ADK_USE_12KEY_MODE
#define PULL_UP_RESISTANCE 22   //上拉电阻22K
#define KEYB_RES 0   //pp
#define KEYA_RES 2.2   //10+
#define KEY9_RES 4.7 //rep-->long press folder repeat
#define KEY8_RES 7.5  //prev folder/fr
#define KEY7_RES 12  //next folder/ff
#define KEY6_RES 16  //eq
#define KEY5_RES 24  //next/v+
#define KEY4_RES 36  //prev/v-
#define KEY3_RES 51 //mode/file del
#define KEY2_RES 91 //standby改为random play
#define KEY1_RES 220 //replay/rec
#define KEY0_NOKEY_RES 330
#ifdef TWO_AD_IO_USE_DIFF_RESISTANCE
#define PULL_UP_RESISTANCE1 22   //上拉电阻20K
#define KEYB_RES1 0   //0
#define KEYA_RES1 2.2   //  1
#define KEY9_RES1 4.7 // 2
#define KEY8_RES1 7.5  // 3
#define KEY7_RES1 12  // 4
#define KEY6_RES1 16  // 5
#define KEY5_RES1 24  // 6
#define KEY4_RES1 36  // 7
#define KEY3_RES1 51 // 8
#define KEY2_RES1 91 //  
#define KEY1_RES1 220 //9
#define KEY0_NOKEY_RES1 330
#endif
#elif defined(ADK_USE_10KEY_MODE)
#define PULL_UP_RESISTANCE 22   //上拉电阻22K
#define KEY9_RES 0   //
#define KEY8_RES 3.3 //pp
#define KEY7_RES 7.5  //prev/v-
#define KEY6_RES 13  //next/v+
#define KEY5_RES 20  //mode
#define KEY4_RES 30  //record
#define KEY3_RES 68  //repeat
#define KEY2_RES 120 //mute
#define KEY1_RES 240 //eq
#define KEY0_NOKEY_RES 330
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
    //#define IR_SSM_THREE_GENERAL_FF00_7F80_FE01
#ifdef SSM_Q535_2REC_4018_2_AC461_V10    
#define IR_SSM_THREE_GENERAL_FF00_7F80_FE01_REC_7
#define SUPPORT_FM_PAUSE
#else
    #define IR_SSM_THREE_GENERAL_FF00_7F80_FE01_REC_2 // LONG -REC   SHORT_RECPLAY
#endif
    #define  ir_max_num     27
    #define IR_NUMS 3
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
#define FM_DGND_DETECT_EN 1
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
  // #define power_on_no_usb_sd_to_bt
   #define POWER_ON_NO_DEV_TO_AUX
#define PLUG_OUT_DEV_TO_LINEIN_MODE



//默认音量  
#define SYS_DEFAULT_VOL_EN      1    ///<系统开机默认音量使能
#if SYS_DEFAULT_VOL_EN
#define SYS_DEFAULT_VOL         30  ///<系统启动默认音量值
#endif
//#define BT_VOL_MAX 29



#define REMOVE_BT_MODE_NOTICE     //关蓝牙模式提示音
#define support_SHORT_PPKEY_Twice_CALL_LAST_NO
#define  support_PP_CALL_ACTIVE_HANGUP_UP   //通话时按PP 挂断电话
#define support_mode_change_vol_min_to_min   10  // 转换模式时音量小于10  则等于10
#define SUPPORT_MUSIC_STOP
#define SUPPORT_MUSIC_FOLDER_OPERATION
#define SUPPORT_MUSIC_RANDOM_KEY
#define REPEAT_NOT_USE_RANDOM_AND_FOLDER
#define support_stanby_mod
#define support_mode_key_user_usb_sd
#define BT_POWER_ON_USE_WAIT_VOICE
#define A2DP_AUTO_PLAY_EN 0
#define APPLE_MOBILE_PAUSE_NOT_FLASH_LIGHT_INTIME
#define MULTIPLE_DEVICE_PLUGOUT_ONE_AUTO_CHANGE_TO_ANOTHER_DEVICE
#define SUPPORT_FM_SCAN_STEP_NO_SHOW_STATION

//#define SUPPORT_POWER_OFF_REMEMBER_LAST_MODE
#ifdef SUPPORT_POWER_OFF_REMEMBER_LAST_MODE
enum{
music_mode=0,
linein_mode,
bluetooth_mode,
radio_mode,
mode_max
}SWITCH_MODE;
#define POWER_UP_DEFAULT_MODE linein_mode
#endif
#define SUPPORT_MUSIC_INTRO_PLAY
//#define DURING_FM_EXITING_TASK_NOT_RESPOND_KEY_MSG //aux exit state press mode key fast and more times system die
#define POWER_ON_WITH_USB_AND_SD_PLAY_USB_FIRST

#define support_vt_tone_delay  //回连延时报语音


#define SUPPORT_WOKRMODE
#ifdef SUPPORT_WOKRMODE
extern u8 workmode;
#endif




