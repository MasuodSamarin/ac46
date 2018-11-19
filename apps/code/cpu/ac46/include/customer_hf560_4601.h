

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

#define KEY_TONE_EN             1   ///<������ʹ��
#define GET_ENERGY_VALUE        1    ///<DAC����ֵ
#define SYS_LVD_EN              1    ///<ϵͳ�͵���
#define S10_MODE                0    ///<0:��ͨSDK     1:S10��������
#define POWERUP_DEFAULT_MODE    1    ///<�ϵ�Ĭ��ģʽʹ��
#define MUSIC_DEC_RECORD_DEV    0    ///<�����¼����ǰ��󲥷ŵ��豸



#if S10_MODE
#define DAC_SOUNDTRACK_COMPOUND 1    ///<DAC�����ϳ�
#else
#define DAC_SOUNDTRACK_COMPOUND 0    ///<DAC�����ϳ�
#endif/*S10_MODE*/

/*
*********************************************************************
                        BT MACRO
*********************************************************************
*/
//���ò��Ժв��Թ���
#define NON_TEST         0       //ûƵƫ�;������
#define FRE_OFFSET_TEST  BIT(0)  //Ƶƫ����
#define DISTANCE_TEST    BIT(1)  //�������



#define NORMAL_MODE         0
#define TEST_INDEX_MODE     1     //ָ�����ܲ���(ʹ��MT8852A��������)
#define TEST_FCC_MODE       2     //����fcc��֤
#define TEST_FRE_OFF_MODE   3     //����Ƶƫ(ʹ��Ƶ�׷�����-���������-����Ƶ��Ĭ��2420M)


#define BT_MODE        NORMAL_MODE
#define BT_BACKMODE         0   //�Ƿ��� ��̨ 0 �� 1��
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
        
     #else /*��׼SDK*/
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
    #define SDMMC0_EN       0    ///<SD0ʹ��
    #define SDMMC1_EN       0    ///<SD1ʹ��
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
    #define USB_DISK_EN     0    ///<U��ʹ��
    #define USB_PC_EN       0    ///<PCʹ��
#else
    #define USB_DISK_EN     1
    #define USB_PC_EN       1
#endif/*S10_MODE*/

#define SPI_FLASH_BLK_NUM   8
#define POWERUP_DEV_IGNORE       ///<�����豸�ϵ��Ƿ���ӦU�̻�SD
/*
*********************************************************************
                        UI MACRO
*********************************************************************
*/

#define UI_ENABLE       0     ///>UI_��ʾ

//LED    
#if 0//UI_ENABLE
      #define support_LED7_USER_PA7PA8PA9PA10PA11PA14PA15
      #define led_io_180_mirror
      #define support_aux_led_disp_line     //������ʾ"LINE"
      #define support_mute_led_all_flish    //MUTE ȫ����˸
      #define support_led_disp_pause
      #define  support_yl_3520
      
      
      //��ط��� 
        #define   led_icon_disp_vat_volage
        #ifdef led_icon_disp_vat_volage
        #define  support_battery_mode_check    //��ѹ״̬��ʾ 
        #endif 
        
      #define   support_user_dsp_eq     //Ƶ����ʾ
#endif 

/**********************  MUZHE ADD **************************/

// adk  
#define KEY_IO_EN     0  ///<IO����ʹ��
#define KEY_AD_EN      1   ///<AD����ʹ��
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
#define KEY_IR_EN       0  ///<����ң��ʹ��
#if KEY_IR_EN 
    #define   Ir_user_pa5
    #define IR_USER_KPL_002    //IR_USER_KPL_001
    #define ir_user_kpl_ty_msg
    #define  ir_max_num     33
#endif 


#if KEY_TONE_EN
// #define support_all_KEY_TONE_EN   //���ⰴ�����а�����
// #define   support_vol_max_tone_en    //������� ��������ʾ
#define support_off_low_power_vioce   //�رյ͵���ʾ��
#endif 



//line 
#define   line_user_PC13_PC12 
//line ���
 #define AUX_DETECT_EN      
#ifdef AUX_DETECT_EN
   #define  support_line_chack_user_PC10
//  #define  support_line_unline_to_next_mode   //AUX �����ߵ���һ��ģʽ
#endif 

// PP LED 
#define LED_EN                  1  ///<LEDָʾʹ��
#define  PP_LED_USER_PA15


// Ƶ����ʾ
#define support_led_eq_disp    //֧�ַ����Ƶ����ʾ
#define support_led_eq_user_PB6PB7PB8PB9PB10
#define support_led_eq_is_5led_user_sw    //�������޿���ģʽ 

//��������
#define power_on_wait_power_key_down
#define support_io_power_on_off    //����MOS��
#define  power_on_off_user_PA4
#define support_power_off_voice
//#define ENABLE_POWER_ON_KEY_WAIT

//MUTE IO 
    #define   PA_ENABLE
#ifdef PA_ENABLE
        #define   pa_mute_use_pin_PC11
        //#define   mute_io_L_is_mute   //  ��MUTE   ������Ϊ��MUTE    
        #define support_vol_is_0_mute_amp    //������0 MUTE ����
        #define support_pause_stop_mute_amp
#endif 


//���� Ĭ��ģʽ  
  #define power_on_no_usb_sd_to_bt
#define usb_sd_out_to_bt_mode

//Ĭ������  
#define SYS_DEFAULT_VOL_EN      1    ///<ϵͳ����Ĭ������ʹ��
#if SYS_DEFAULT_VOL_EN
#define SYS_DEFAULT_VOL         20   ///<ϵͳ����Ĭ������ֵ
#endif


#define OFF_BPF_BT_MP3     //������ģʽ��ʾ��
#define support_SHORT_PPKEY_Twice_CALL_LAST_NO
#define  support_PP_CALL_ACTIVE_HANGUP_UP   //ͨ��ʱ��PP �Ҷϵ绰

#define support_vt_tone_delay  //������ʱ������


