

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
#define KEY_TONE_EN             1    ///<按键音使能
#define GET_ENERGY_VALUE        1    ///<DAC能量值
#define SYS_LVD_EN              1    ///<系统低电检测
#define S10_MODE                0    ///<0:普通SDK     1:S10样机程序
#define POWERUP_DEFAULT_MODE    1    ///<上电默认模式使能
#define MUSIC_DEC_RECORD_DEV    0    ///<解码记录掉电前最后播放的设备

#define SYS_DEFAULT_VOL_EN      0    ///<系统开机默认音量使能
#if SYS_DEFAULT_VOL_EN
#define SYS_DEFAULT_VOL         25   ///<系统启动默认音量值
#endif

#if S10_MODE
#define DAC_SOUNDTRACK_COMPOUND 1    ///<DAC声道合成
#else
#define DAC_SOUNDTRACK_COMPOUND 0    ///<DAC声道合成
#endif/*S10_MODE*/

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
    #define SDMMC1_EN       1
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
#define POWERUP_DEV_IGNORE       ///<插着设备上电是否响应U盘或SD
/*
*********************************************************************
                        UI MACRO
*********************************************************************
*/

#define UI_ENABLE       1     ///>UI_显示


#if UI_ENABLE
#define support_LED7_USER_PA7PA8PA9PA10PA11PA14PA15
#define support_aux_led_disp_line     //屏上显示"LINE"
#define support_mute_led_all_flish    //MUTE 全屏闪烁
#define support_led_disp_pause
#define aihan_long_led   //不同的LED 长家
#endif 

/**********************  MUZHE ADD **************************/

// adk  
//#define support_adk_user_PA0

#define  adk_user_6_key_mode //adk_user_3_4_6_key_mode
#define KEY_IO_EN       1   ///<IO按键使能
#define KEY_AD_EN       0   ///<AD按键使能

#if KEY_IO_EN
#define support_io_scan_key_user_PA0_PA4_PA6
#define support_sw005_io_scan_mode
#endif   

//IR
#define KEY_IR_EN       1   ///<红外遥控使能
#define   Ir_user_pa5
#define IR_USER_KPL_002    //IR_USER_KPL_001
#define ir_user_kpl_ty_msg
#define  ir_max_num     33


#if KEY_TONE_EN
// #define support_all_KEY_TONE_EN   //任意按键都有按键音
// #define   support_vol_max_tone_en    //音量最大 按键音提示
#endif 

//line 
#define   line_user_PC13_PC12 

//line 检测
//  #define AUX_DETECT_EN      
#ifdef AUX_DETECT_EN
   #define  support_line_chack_user_PC10
   #define  support_line_unline_to_next_mode   //AUX 不在线到下一个模式
#endif 

// PP LED 
#define LED_EN                  1   ///<LED指示使能
#define  PP_LED_USER_PB6



//MUTE IO 
//    #define   PA_ENABLE
#ifdef PA_ENABLE
        #define   pa_mute_use_pin_PC11
        //#define   mute_io_L_is_mute   //  低MUTE   不定义为高MUTE    
        #define support_vol_is_0_mute_amp    //音量到0 MUTE 功放
        #define support_pause_stop_mute_amp
#endif 

#define OFF_BPF_BT_MP3     //关蓝牙模式提示音


//开机 默认模式  
  #define power_on_no_usb_sd_to_bt
#define support_off_phone_call    //关通话 
#define usb_sd_out_to_bt_mode

#define support_off_fm_mode 

