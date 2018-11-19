

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

#define KEY_TONE_EN             1   ///<按键音使能
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

#define UI_ENABLE       0     ///>UI_显示

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
#endif 

/**********************  MUZHE ADD **************************/

// adk  
#define KEY_IO_EN     0  ///<IO按键使能
#define KEY_AD_EN      1   ///<AD按键使能
#if 0//KEY_IO_EN
    #define support_io_scan_key_user_PA5_PA6_PA7
    #define support_ylt_k2536_io_scan_mode
#endif   

#if KEY_AD_EN
  #define support_adk_user_PA0
#endif 


//key msg 
#define  adk_user_07vpower_6key_mode   
#define  support_msg_light_key
#ifdef support_msg_light_key
#define Light_max_mode   2
#define  support_default_light_on
#endif 

//IR
#define KEY_IR_EN       0  ///<红外遥控使能
#if KEY_IR_EN 
    #define   Ir_user_pa5
    #define IR_USER_KPL_002    //IR_USER_KPL_001
    #define ir_user_kpl_ty_msg
    #define  ir_max_num     33
#endif 


#if KEY_TONE_EN
// #define support_all_KEY_TONE_EN   //任意按键都有按键音
// #define   support_vol_max_tone_en    //音量最大 按键音提示
#define support_off_low_power_vioce   //关闭低电提示音
#endif 



//line 
#define   line_user_PC13_PC12 
//line 检测
 #define AUX_DETECT_EN      
#ifdef AUX_DETECT_EN
   #define  support_line_chack_user_PC10
//  #define  support_line_unline_to_next_mode   //AUX 不在线到下一个模式
#endif 

// PP LED 
#define LED_EN                  1  ///<LED指示使能
#define  PP_LED_USER_PA15


// 频谱显示
#define support_led_eq_disp    //支持发光管频谱显示
#define support_led_eq_user_PB6PB7PB8PB9PB10
#define support_led_eq_is_5led_user_sw    //六个灯无开关模式 

//软开机设置
#define power_on_wait_power_key_down
#define support_io_power_on_off    //控制MOS管
#define  power_on_off_user_PA4
#define support_power_off_voice
//#define ENABLE_POWER_ON_KEY_WAIT

//MUTE IO 
    #define   PA_ENABLE
#ifdef PA_ENABLE
        #define   pa_mute_use_pin_PC11
        //#define   mute_io_L_is_mute   //  低MUTE   不定义为高MUTE    
        #define support_vol_is_0_mute_amp    //音量到0 MUTE 功放
        #define support_pause_stop_mute_amp
#endif 


//开机 默认模式  
  #define power_on_no_usb_sd_to_bt
#define usb_sd_out_to_bt_mode

//默认音量  
#define SYS_DEFAULT_VOL_EN      1    ///<系统开机默认音量使能
#if SYS_DEFAULT_VOL_EN
#define SYS_DEFAULT_VOL         20   ///<系统启动默认音量值
#endif


#define OFF_BPF_BT_MP3     //关蓝牙模式提示音
#define support_SHORT_PPKEY_Twice_CALL_LAST_NO
#define  support_PP_CALL_ACTIVE_HANGUP_UP   //通话时按PP 挂断电话

#define support_vt_tone_delay  //回连延时报语音


