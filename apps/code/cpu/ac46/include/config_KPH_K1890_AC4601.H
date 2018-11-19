

//#define __DEBUG

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
#define KEY_TONE_EN             0   ///<按键音使能
#define GET_ENERGY_VALUE        1    ///<DAC能量值
#define SYS_LVD_EN              1    ///<系统低电检测
#define S10_MODE                0    ///<0:普通SDK     1:S10样机程序
#define POWERUP_DEFAULT_MODE    1    ///<上电默认模式使能
#define MUSIC_DEC_RECORD_DEV    0    ///<解码记录掉电前最后播放的设备



#if S10_MODE
#define DAC_SOUNDTRACK_COMPOUND 1    ///<DAC声道合成
#else
#define DAC_SOUNDTRACK_COMPOUND 0    ///<DAC声道合成
#endif/*S10_MODE*/



/*
*********************************************************************
                        REC MACRO
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
        
	   	 
            //    #define support_rec_recplay_notice
//            #define SUPPORT_REC_STOP_PLAY_REC_FILE
            #ifdef SUPPORT_REC_STOP_PLAY_REC_FILE
            extern u32 curr_dir_file_num;
            extern  bool  play_rec_last_file;   
            extern  bool  aux_fm_rec_sw;   
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
#define TEST_INDEX_MODE     1     //指标性能测试(使用MT8852A仪器测试)
#define TEST_FCC_MODE       2     //测试fcc认证
#define TEST_FRE_OFF_MODE   3     //测试频偏(使用频谱分析仪-手提测试仪-中心频率默认2420M)


#define BT_MODE        NORMAL_MODE
#define BT_BACKMODE         0   //是否跑 后台 0 否 1是
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
           #define KEY_DOUBLE_CLICK
           #define S10_UART_DEBUG    0
        
             #if S10_UART_DEBUG
             #define DEBUG_UART   UART1
             #else
             #define DEBUG_UART   UART_NO
             #endif/*S10_UART_DEBUG*/
        
     #else /*标准SDK*/
        #define DEBUG_UART   UART0
       #endif/*S10_MODE*/

#else
     #define DEBUG_UART UART_NO
#endif

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
    #define SDMMC1_EN      0// 1
    #endif/*S10_MODE*/
#endif

#if S10_MODE
    #define USB_DISK_EN     0    ///<U盘使能
    #define USB_PC_EN       0    ///<PC使能
#else
    #define USB_DISK_EN     1
    #define USB_PC_EN       1
#endif/*S10_MODE*/

#define SPI_FLASH_BLK_NUM   8
//#define POWERUP_DEV_IGNORE       ///<插着设备上电是否响应U盘或SD

/*
*********************************************************************
                        UI MACRO
*********************************************************************
*/

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
#define LED_7PIN_MODE
#define LED_USE_7PIN_PA7__PA11PA14PA15
//#define LED_USE_7PIN_PB8PB7PB6PA15PA14PA10PA9
//#define LED_USE_7PIN_PA9__PA15PB6PA7
#define LED_7PIN_REVERSE
#define LED_COM_MAX 7
#define LED_8NUMS 4
#define LED_8GRIDS 7
#define LED_ICON_NUMS 8
#define SUPPORT_FLASH_ICON
#define SUPPORT_FLASH_CHAR

#ifdef SUPPORT_FLASH_CHAR
//#define SUPPORT_LED_BLUE_STRING_FLASH
#define SUPPORT_MUTE_FLASH
//#define MUTE_FLASH_ZERO_VOL
#define MUTE_FLASH_ALL_SCREEN
#define LED_2POINT_NOT_FLASH
#endif
#define LED_SHOW_DEVICE_PLUGIN
#define LED_SHOW_BT_EQ
#define LED_SHOW_POWER_OFF_STRING " OFF"
#define LED_SHOW_INTRO_STRING "SCAN"

#define LED_SHOW_MP3_PAUSE

#define LED_EXIT_MP3_NOT_SHOW_LOAD
//#define MP3_NEXT_MODE_IS_AUX 0
#define EXIT_AUX_TASK_NOT_SHOW_LOAD
//#define LED_SWITCH_FM2AUX_SHOW_LINE
#define LED_FM_EXIT_NOT_SHOW_LOAD
#define EXIT_BT_NOT_SHOW_LOAD
#define LINEIN_INIT_SHOW_AUX_INTIME
#define OFF_AUX_SHOW_ERRO_MESSAGE

#endif


//检测是否外接电源
//#define support_ic_chack_dc_in
//#define chack_dc_in_user_PB10   

//*****BAT DETECT *****//
#define SUPPORT_BAT_DETECT
#ifdef SUPPORT_BAT_DETECT
#define LED_SCREEN_SHOW_BAT_STATUS
#endif

/**********************  MUZHE ADD **************************/

// adk  
#define KEY_IO_EN      1  ///<IO按键使能
#define KEY_AD_EN      0   ///<AD按键使能
#if KEY_IO_EN
    #define support_io_scan_key_user_PA0_PA4_PA6
    #define SUPPORT_MSJ_K1719_IO_KEY_VALUE
    #define adk_user_6_key_mode
#endif   
#if KEY_AD_EN
  #define support_adk_user_PA0
#endif 
//key msg 
//#define ADK_USE_10KEY_MODE
#define ADK_USE_15KEY_MODE
//#define ADK_USE_GENERAL_10KEY_MSG
//#define AKD_USE_ZY_15KEY_MSG
//#define  adk_user_6_key_mode_2   
//#define support_led_off_key 
//#define support_change_mode_on_led
//#define AD_KEY_MAX 15
#define SUPPORT_ONE_KEY_TO_AUX
#define SUPPORT_ONE_KEY_TO_RADIO

#ifdef ADK_USE_10KEY_MODE
#define PULL_UP_RESISTANCE 22   //上拉电阻22K
#define KEY9_RES 0   //PP
#define KEY8_RES 3 //PREV/V-
#define KEY7_RES 6.2  //NEXT/V+
#define KEY6_RES 9.1  //MODE
#define KEY5_RES 15  //receive call
#define KEY4_RES 24
#define KEY3_RES 33
#define KEY2_RES 51
#define KEY1_RES 100
#define KEY0_NOKEY_RES 220
#else
#define PULL_UP_RESISTANCE 10   //上拉电阻10K
#define KEYE_RES 0  //one key to aux
#define KEYD_RES 0.56 //stop
#define KEYC_RES 1.2  //pp
#define KEYB_RES 2.4  //usb/sd
#define KEYA_RES 3.3  //mode  
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
 #define IR_TY_DOUBLE_00FF_807F_26KEY
    // #define IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY
//     #define IR_MSJ_DOUBLE_GENERAL_FF00_7F80
    #define  ir_max_num     26
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

//IO接电子地，要相应功能就不接地
#define FM_DGND_DETECT_EN 0
#define FM_DGND_DETECT_USE_PB6
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
#endif



//MUTE IO 
    #define PA_ENABLE
    #define PA_EN 1
#ifdef PA_ENABLE
        #define   pa_mute_use_pin_PC11
        //#define   mute_io_L_is_mute   //  低MUTE   不定义为高MUTE    
        #define support_vol_is_0_mute_amp    //音量到0 MUTE 功放
        #define support_pause_stop_mute_amp
    //    #define ONLY_POWER_ON_MUTE

#endif 

//AB/D
#define support_amP_ab_d
#define amp_ab_d_user_PC10
//#define ONLY_POWER_ON_MUTE	//amp low mute,power on delay 4s unmute

//开机 默认模式  
   #define MP3_AUX_BT_FM
  // #define power_on_no_usb_sd_to_bt
//#define PLUG_OUT_DEV_TO_LINEIN_MODE
#define power_on_no_usb_sd_to_LINE
#define PLUG_OUT_DEV_TO_LINEIN_MODE



//默认音量  
#define SYS_DEFAULT_VOL_EN      0    ///<系统开机默认音量使能
#if SYS_DEFAULT_VOL_EN
#define SYS_DEFAULT_VOL         30  ///<系统启动默认音量值
#endif



#define OFF_BPF_BT_MP3     //关蓝牙模式提示音
#define support_SHORT_PPKEY_Twice_CALL_LAST_NO
#define  support_PP_CALL_ACTIVE_HANGUP_UP   //通话时按PP 挂断电话
#define support_line_pause    //显示PAUSE
#define support_mode_change_vol_min_to_min   10  // 转换模式时音量小于10  则等于10
#define SUPPORT_MUSIC_STOP
#define SUPPORT_MUSIC_INTRO_PLAY
#define support_stanby_mod
#define support_off_phone_call
#define A2DP_AUTO_PLAY_EN 1
//#define EXIT_BLUE_MODE_DISCONNECT_VOICE  //退出不管连接与否都有声音提示
#define BT_POWER_ON_USE_WAIT_VOICE
#define REPEAT_NOT_USE_RANDOM_AND_FOLDER
#define APPLE_MOBILE_PAUSE_NOT_FLASH_LIGHT_INTIME
#define DURING_FM_EXITING_TASK_NOT_RESPOND_KEY_MSG //aux exit state press mode key fast and more times system die
#define LED_SHOW_EQ_WITH_NAME
#define EQ_SEQUENCE_ADJ_ANYWAY
#define POWER_ON_WITH_USB_AND_SD_PLAY_USB_FIRST
#ifdef DURING_FM_EXITING_TASK_NOT_RESPOND_KEY_MSG
extern u8 bExitFMStateCnt;
#endif

#define support_vt_tone_delay  //回连延时报语音

