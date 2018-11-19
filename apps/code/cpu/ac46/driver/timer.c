/***********************************Jieli tech************************************************
  File : timer.c
  By   : Juntham
  date : 2014-07-04 11:21
********************************************************************************************/
#include "includes.h"
#include "timer.h"
#include "jiffies.h"
#include "key.h"
#include "led.h"
#include "dac_api.h"
#include "key_drv_ad.h"
#include "key_drv_ir.h"
#include "key_drv_tch.h"
#include "avctp_user.h"
#include "config.h"
#include "msg.h"
#include "led7_drv.h"
#ifdef SUPPORT_ENCODER
#include "encoder.h"
#endif
#if REC_EN
#include "encode.h"
#endif

#ifdef DURING_FM_EXITING_TASK_NOT_RESPOND_KEY_MSG
extern u8 bExitFMStateCnt;
#endif
#ifdef ONLY_POWER_ON_MUTE
extern u8 bPowerOnMuteCnt;
#endif
#ifdef IO_MUTE_DELAY_ALL_STATE
extern u8 bMuteDelayCnt;
#endif
#ifdef support_amp_power_control
 #ifdef POWER_ON_KEEP_MUTE_FOR_4S	
extern u8 bAmpPowerOnMuteCnt;
#endif
#endif
extern int rand(void);
extern void srand(unsigned int seed);
extern volatile unsigned long jiffies;
extern void btstack_timer_schedule(void);
#ifdef SUPPORT_AUX_FM_BT_SHOW_REC_TIME
u32 dwAuxFmBtRecordTimeCnt=0;
#endif

volatile u8 sys_halfsec;

const u32 timer_div[] =
{
    /*0000*/    1,
    /*0001*/    4,
    /*0010*/    16,
    /*0011*/    64,
    /*0100*/    2,
    /*0101*/    8,
    /*0110*/    32,
    /*0111*/    128,
    /*1000*/    256,
    /*1001*/    4*256,
    /*1010*/    16*256,
    /*1011*/    64*256,
    /*1100*/    2*256,
    /*1101*/    8*256,
    /*1110*/    32*256,
    /*1111*/    128*256,
};

void init_tick_timer(u32 hz )
{
    set_tick_timer(hz);
    INTALL_HWI(0,OSTimeTick,1) ;
}

u32 rand_num_maker(u32 max, u32 min, u32 seed)
{
    u32 rand_num;

    srand(seed); //随机数初始化
    rand_num = rand() % (max - min + 1) + min; //产生max到min范围内的随机数

    return rand_num;
}

extern int uart_key;
#define KEY_IN() do{PORTA_PU |= BIT(5);PORTA_DIR |= BIT(5);}while(0)
#define IS_KEY_DOWN()    (!(PORTA_IN&BIT(5)))

volatile u32 g_2ms_seed ;
volatile u32 g_rand_seed ;
void delay_n2ms(u32 cnt)
{
    g_2ms_seed = 0;
    while(g_2ms_seed < cnt);
}


//#ifdef SUPPORT_BREATH_LIGHT
#if defined(SUPPORT_BREATH_LIGHT)
void timer0_isr()
{
    static u32 cnt1;

    TMR0_CON |= BIT(14);
    DSP_CLR_ILAT = BIT(TIME0_INIT);
    cnt1++;

    //g_os_time++;
    g_2ms_seed++;
    g_rand_seed++; //随机数种子
    //printf("g_2ms_seed_1= 0x%x\n", g_2ms_seed);
    //delay_count();
    dac_fade();

    /*ir_code.boverflow++;
    if (ir_code.boverflow > 56) //56*2ms = 112ms
    {
        ir_code.bState = 0;
    }*/
    //usb_host_detect_api();
    //usb_online_check(20);
    //


    /*if(getbyte() != 0){
    	putchar('C');
    	if(uart_key == 0)
    	{
    		uart_key = 2;
    	}
    	btstack_wakeup();
    }*/

#if UI_ENABLE

#if 0//def LED_SHOW_SCREEN_FREQUENCE
#if defined(LED_ID_DOUBLE_PANEL)
	if(cnt1%(12)==0)   	
	 LED_FREQUENCE_PROCESS();
#endif
#endif
#ifdef NO_PANEL_LED

#elif defined(SUPPORT_LCD_4COM_9SEG_MODE)||defined(SUPPORT_LCD_5COM_8SEG_MODE)
	if(cnt1%(2*20)==0)	
		led7_scan();	
	#elif defined(LED_7PIN_MODE)
		led7_scan();	
	#elif defined(SUPPORT_PT6312_MODE)||defined(SUPPORT_TM1628_MODE)	 
		//if(compare_task_name("FMRadioTask")){
		#if defined(LED_ID_ZX001)||defined(LED_ID_JW1676_1B)||defined(LED_ID_JM_4169_B)||defined(LED_ID_DOUBLE_PANEL)
		if(cnt1%(2*4)==0)
		#else
		if(cnt1%(2*10)==0)
		#endif
		led7_scan();	
		//}
		//else
		//	led7_scan();		
	#else
	led7_scan();	
#endif
#ifdef LED_EQ_BAR_SHOW
#ifdef EQ_DETECT_ANALOG_SIGNAL
  PROCESS_ANALOG_SIGNAL_TO_STEP();
#else  
  GET_LED_EQ_BAR_VALUE();
#endif  
#endif
#endif
#if KEY_TCH_EN
    scan_capkey();
#endif

#if KEY_IR_EN
    ir_timeout();
#endif

#ifdef SUPPORT_ENCODER   
if(cnt1%2==0){
	ENC_Encoder();
	#ifdef SUPPORT_TWO_ENCODER
	ENC_Encoder1();
	#endif
	}
#endif

#if 1 //  KEY_AD_EN 牟哲 20150505  无AD键开AD检测
    adc_scan();
#endif
#ifdef USE_HT1628_CONTROL_TENS_OF_RGB_LIGHTS
if(compare_task_name("FMRadioTask"))
{
if(cnt1%50==0)
	ht1628_scan();
}
else
	ht1628_scan();
#endif
#if SYS_LVD_EN
    battery_check();
#endif
#ifdef NEW_LED_SHOW_METHOD
	if((cnt1 % (2*10)) == 0)
	led_scan();
#endif
#ifdef SUPPORT_BREATH_LIGHT

	    AUTO_DETECT_VOICE_AND_PRODUCE_PWM_VALUE();
	    LightRunPWM();
	  //  if(cnt1%84==0)
	 //   AUTO_CHANGE_LIGHT_DUTY_STEPS();
#endif



    jiffies++;
    btstack_timer_schedule();
    if((cnt1 % (2*5)) == 0)
    {

		key_scan();
#ifdef  support_led_eq_disp    
             led_disp_eq();
#endif 
    }

#ifdef BT_TESTER
    if((cnt1 % 4) == 0)
    {
        get_pcm_data_from_flash();
    }
    if((cnt1 % 50) == 0)
    {
        led_control_for_tester();
    }
#endif
    if (cnt1 == (2*250))
    {
        // put_buf(h4_mem_pool,20);
        if(keymsg_task_name)
        {
            os_taskq_post_msg(keymsg_task_name, 1, MSG_HALF_SECOND);
        }
        //sys_idle_check();
        usre_cmd_timeout_check();
        cnt1 = 0;
#if SYS_LVD_EN
        get_battery_value();
#endif
#ifdef DURING_FM_EXITING_TASK_NOT_RESPOND_KEY_MSG
	if(bExitFMStateCnt)bExitFMStateCnt--;
#endif
#ifdef ONLY_POWER_ON_MUTE
	  if(bPowerOnMuteCnt){
	  bPowerOnMuteCnt--;
	  if(bPowerOnMuteCnt==0){  //unmute
	  pa_umute1();
    }
   }
#endif
#ifdef IO_MUTE_DELAY_ALL_STATE
	if(bMuteDelayCnt){
	bMuteDelayCnt--;
	 pa_mute();
	if(bMuteDelayCnt==0){	
	 // dac_mute(0,1);
	  pa_umute();
	  }
	}
#endif

   sys_halfsec = !sys_halfsec;
   
#ifdef SUPPORT_AUX_FM_BT_SHOW_REC_TIME
   if((g_rec_ctl)&&(ENC_STOP != g_rec_ctl->enable)){
   if(sys_halfsec&&(ENC_STAR == g_rec_ctl->enable)){
    dwAuxFmBtRecordTimeCnt++;
    if(dwAuxFmBtRecordTimeCnt>4294967295)dwAuxFmBtRecordTimeCnt=0;
    }
    }
#endif
       //puts("#");
    }

    //PORTA_OUT ^= BIT(9);
}

#elif defined SUPPORT_ZY_4LED_RGB  ||defined SUPPORT_RGB_BREATH_LAMP 

void timer0_isr()
{
    static u32 cnt1;

    TMR0_CON |= BIT(14);
    DSP_CLR_ILAT = BIT(TIME0_INIT);
    cnt1++;

    //g_os_time++;
    g_2ms_seed++;
    g_rand_seed++; //随机数种子
    //printf("g_2ms_seed_1= 0x%x\n", g_2ms_seed);
    //delay_count();
if(cnt1%20==0)    
    dac_fade();

    /*ir_code.boverflow++;
    if (ir_code.boverflow > 56) //56*2ms = 112ms
    {
        ir_code.bState = 0;
    }*/
    //usb_host_detect_api();
    //usb_online_check(20);
    //


    /*if(getbyte() != 0){
    	putchar('C');
    	if(uart_key == 0)
    	{
    		uart_key = 2;
    	}
    	btstack_wakeup();
    }*/

	

#if UI_ENABLE
#ifdef NO_PANEL_LED

#elif defined(SUPPORT_LCD_4COM_9SEG_MODE)||defined(SUPPORT_LCD_5COM_8SEG_MODE)
//	if(cnt1%2==0)	
		led7_scan();	
	#elif defined(LED_7PIN_MODE)
		if(cnt1%20==0)	
		led7_scan();	
	#elif defined(SUPPORT_PT6312_MODE)||defined(SUPPORT_TM1628_MODE)	 
		//if(compare_task_name("FMRadioTask")){
		#if defined(LED_ID_ZX001)||defined(LED_ID_JM_4169_B)||defined(LED_ID_JW1676_1B)||defined(LED_ID_DOUBLE_PANEL)||defined(LED_ID_SD40C18SRB)
		if(cnt1%4==0)
		#else
		if(cnt1%10==0)
		#endif
		led7_scan();	
		//}
		//else
		//	led7_scan();		
	#else
	led7_scan();	
#endif

#endif


#if KEY_IR_EN
if(cnt1%20==0)
    ir_timeout();
#endif

#ifdef support_io_det_mute
if(cnt1%20*20==0)
//if(bPowerOnMuteCnt==0)
	pa_automute();
#endif


#if 1 //  KEY_AD_EN 牟哲 20150505  无AD键开AD检测
  if(cnt1%20==0)
    adc_scan();
#endif
#ifdef USE_HT1628_CONTROL_TENS_OF_RGB_LIGHTS
if(compare_task_name("FMRadioTask"))
{
if(cnt1%50==0)
	ht1628_scan();
}
else
	ht1628_scan();
#endif
#if SYS_LVD_EN

#ifdef support_low_power_use_extern_io
	if(cnt1%(10*20)==0)
		 battery_check();
#else
	if(cnt1%(20)==0)
	battery_check();
#endif

#endif
#ifdef SUPPORT_BREATH_LIGHT
   AUTO_DETECT_VOICE_AND_PRODUCE_PWM_VALUE();
   LightRunPWM();
   #ifndef ONLY_SWITCH_RGB_LIGHT
   if(cnt1%84==0)
   AUTO_CHANGE_LIGHT_DUTY_STEPS();
   #endif
#elif defined(ONLY_SWITCH_RGB_LIGHT)
 SHOW_bRgbMode_1_LIGHT_INTIME();
#endif

#ifdef NEW_LED_SHOW_METHOD
	if((cnt1 % (10*20)) == 0)
	led_scan();
#endif

if(cnt1%20==0)    
    jiffies++;

if((cnt1 % (20)) == 0)
    btstack_timer_schedule();
    if((cnt1 % (5*20)) == 0)
    {

		key_scan();
	 #ifdef  support_led_eq_disp    
		 led_disp_eq();
	 #endif 
    }

	
 #ifdef KOK_DETECT_AUTO_VOL_SET			
 if(cnt1%(55*20)==0)
	vol_auto_inc();
#endif

#ifdef BT_TESTER
    if((cnt1 % 4) == 0)
    {
        get_pcm_data_from_flash();
    }
    if((cnt1 % 50) == 0)
    {
        led_control_for_tester();
    }
#endif

#ifdef SUPPORT_ENCODE_flash_led
    if((cnt1 % (10*20)) == 0)
		ENC_Encoder_Led();
#endif

#if defined SUPPORT_ZY_4LED_RGB  ||defined SUPPORT_RGB_BREATH_LAMP 
	 pwm_led_rgb_scan();
	if(cnt1%(50)==0)	// 5ms
		freq_det_main();
#endif


    if (cnt1 == (250*20))
    {
        // put_buf(h4_mem_pool,20);
        if(keymsg_task_name)
        {
            os_taskq_post_msg(keymsg_task_name, 1, MSG_HALF_SECOND);
        }
        //sys_idle_check();
        usre_cmd_timeout_check();
        cnt1 = 0;
#if SYS_LVD_EN
        get_battery_value();
#endif
#ifdef DURING_FM_EXITING_TASK_NOT_RESPOND_KEY_MSG
	if(bExitFMStateCnt)bExitFMStateCnt--;
#endif
#ifdef ONLY_POWER_ON_MUTE
	  if(bPowerOnMuteCnt)
	  {
	     #if defined ONLY_POWER_ON_MUTE &&defined support_power_no_media_to_bt 	  	
		 if(bPowerOnMuteCnt==8)
		 {
		 	  pa_mute1();
		 }
	   #endif
    	  bPowerOnMuteCnt--;
    	  if(bPowerOnMuteCnt==0)
    	  {  //unmute
    	  pa_umute1();
      	  }
   }
#endif
#ifdef IO_MUTE_DELAY_ALL_STATE
	if(bMuteDelayCnt){
	bMuteDelayCnt--;
	 pa_mute();
	if(bMuteDelayCnt==0){	
	 // dac_mute(0,1);
	  pa_umute();
	  }
	}
#endif
#ifdef support_amp_power_control
 #ifdef POWER_ON_KEEP_MUTE_FOR_4S	
	if(bAmpPowerOnMuteCnt){
	bAmpPowerOnMuteCnt--;
	AMP_POWER_ONOFF(0);
	if(bAmpPowerOnMuteCnt==0)
		AMP_POWER_ONOFF(1);
	}
 #endif
#endif

   sys_halfsec = !sys_halfsec;
   
#ifdef SUPPORT_AUX_FM_BT_SHOW_REC_TIME
   if((g_rec_ctl)&&(ENC_STOP != g_rec_ctl->enable)){
   if(sys_halfsec&&(ENC_STAR == g_rec_ctl->enable)){
    dwAuxFmBtRecordTimeCnt++;
    if(dwAuxFmBtRecordTimeCnt>4294967295)dwAuxFmBtRecordTimeCnt=0;
    }
    }
#endif
       //puts("#");
    }

    //PORTA_OUT ^= BIT(9);
}


#else
void timer0_isr()
{
    static u32 cnt1;

    TMR0_CON |= BIT(14);
    DSP_CLR_ILAT = BIT(TIME0_INIT);
    cnt1++;

    //g_os_time++;
    g_2ms_seed++;
    g_rand_seed++; //随机数种子
    //printf("g_2ms_seed_1= 0x%x\n", g_2ms_seed);
    //delay_count();
    dac_fade();

    /*ir_code.boverflow++;
    if (ir_code.boverflow > 56) //56*2ms = 112ms
    {
        ir_code.bState = 0;
    }*/
    //usb_host_detect_api();
    //usb_online_check(20);
    //


    /*if(getbyte() != 0){
    	putchar('C');
    	if(uart_key == 0)
    	{
    		uart_key = 2;
    	}
    	btstack_wakeup();
    }*/

#if UI_ENABLE
#ifdef NO_PANEL_LED

#elif defined(SUPPORT_LCD_4COM_9SEG_MODE)||defined(SUPPORT_LCD_5COM_8SEG_MODE)
//	if(cnt1%2==0)	
		led7_scan();	
	#elif defined(LED_7PIN_MODE)
	 		led7_scan();	
	#elif defined(SUPPORT_PT6312_MODE)||defined(SUPPORT_TM1628_MODE)	 
		//if(compare_task_name("FMRadioTask")){
		#if defined(LED_ID_ZX001)||defined(LED_ID_JM_4169_B)||defined(LED_ID_JW1676_1B)||defined(LED_ID_DOUBLE_PANEL)||defined(LED_ID_SD40C18SRB)
		if(cnt1%4==0)
		#else
		if(cnt1%10==0)
		#endif
		led7_scan();	
		//}
		//else
		//	led7_scan();	
	#elif defined(SUPPORT_HT1621C_MODE)
		if(cnt1%2==0)
		led7_scan();	
		
	#else
	led7_scan();	
#endif


#ifdef LED_EQ_BAR_SHOW
#ifdef EQ_DETECT_ANALOG_SIGNAL
  PROCESS_ANALOG_SIGNAL_TO_STEP();
#else  
  GET_LED_EQ_BAR_VALUE();
#endif  
#endif
#endif
#if KEY_TCH_EN
    scan_capkey();
#endif

#if KEY_IR_EN
    ir_timeout();
#endif

#ifdef support_io_det_mute
if(cnt1%20==0)
	pa_automute();

#endif

#ifdef SUPPORT_ENCODER   

	if(cnt1%2==0)
		{
			ENC_Encoder();
			#ifdef SUPPORT_TWO_ENCODER
			ENC_Encoder1();
			#endif
		}
#endif


#if 1 //  KEY_AD_EN 牟哲 20150505  无AD键开AD检测
    adc_scan();
#endif
#ifdef USE_HT1628_CONTROL_TENS_OF_RGB_LIGHTS
if(compare_task_name("FMRadioTask"))
{
if(cnt1%50==0)
	ht1628_scan();
}
else
	ht1628_scan();
#endif
#if SYS_LVD_EN

#ifdef support_low_power_use_extern_io
	if(cnt1%10==0)
		 battery_check();
#else
	battery_check();
#endif

#endif
#ifdef SUPPORT_BREATH_LIGHT
   AUTO_DETECT_VOICE_AND_PRODUCE_PWM_VALUE();
   LightRunPWM();
   #ifndef ONLY_SWITCH_RGB_LIGHT
   if(cnt1%84==0)
   AUTO_CHANGE_LIGHT_DUTY_STEPS();
   #endif
#elif defined(ONLY_SWITCH_RGB_LIGHT)
 SHOW_bRgbMode_1_LIGHT_INTIME();
#endif

#ifdef NEW_LED_SHOW_METHOD
	if((cnt1 % 10) == 0)
	led_scan();
#endif
    jiffies++;
    btstack_timer_schedule();
    if((cnt1 % 5) == 0)
    {

		key_scan();
#ifdef  support_led_eq_disp    
             led_disp_eq();
#endif 
    }

	
 #ifdef KOK_DETECT_AUTO_VOL_SET			
 if(cnt1%55==0)
	vol_auto_inc();
#endif

#ifdef BT_TESTER
    if((cnt1 % 4) == 0)
    {
        get_pcm_data_from_flash();
    }
    if((cnt1 % 50) == 0)
    {
        led_control_for_tester();
    }
#endif

#ifdef SUPPORT_ENCODE_flash_led
    if((cnt1 % 10) == 0)
		ENC_Encoder_Led();
#endif
 #ifdef support_send_ir_code
     if((cnt1 % 5) == 0)
	IRSendData();
#endif

	 #ifdef SUPPORT_USE_ENCODE_AS_MODE_CHANGE	
	     if((cnt1 % 185) == 0)
	    	{
		 	if(bChangeModeTimer)
		 	{
		 		if(bChangeModeTimer>1)
		 			bChangeModeTimer--;
		 
		 		else if(bChangeModeTimer==1)
		 		{
		 			bChangeModeTimer=0;
		 			 encode_change_workmode_control();
		 		}
		 	}
	    	}
	 #endif	

	 #ifdef support_vol_io_control
	     if((cnt1 % 50) == 0)
	     	{
			 if(bVolTimer)
			 	{
					bVolTimer--;
					 if(bVolTimer==1)			
					 	VOL_IO_OFF();			
				 }
	     	}
	 #endif

    if (cnt1 == 250)
    {


    
	 #ifdef support_battery_mode_check
	   LED_io_display_bat_mode();
	 #endif

	 
	 #ifdef support_power_on_30s_bat_icon_on // jsuo add
	 	if(bat_icon_timer>1)
	 		bat_icon_timer--;
	 	else if(bat_icon_timer==1)
	 	{
	 		bat_icon_timer=0;
	 	}
	 #endif

		  #ifdef SUPPORT_OUT_POWER_CONTROL		
			  if(power_on_timer>0)			  	
				power_on_timer--;
		  
			 out_power_control();
		 #endif


        // put_buf(h4_mem_pool,20);
        if(keymsg_task_name)
        {
            os_taskq_post_msg(keymsg_task_name, 1, MSG_HALF_SECOND);
        }
        //sys_idle_check();
        usre_cmd_timeout_check();
        cnt1 = 0;
#if SYS_LVD_EN
        get_battery_value();
#endif
#ifdef DURING_FM_EXITING_TASK_NOT_RESPOND_KEY_MSG
	if(bExitFMStateCnt)bExitFMStateCnt--;
#endif
#ifdef ONLY_POWER_ON_MUTE
	  if(bPowerOnMuteCnt)
	  {
	     #if defined ONLY_POWER_ON_MUTE &&defined support_power_no_media_to_bt 	  	
		 if(bPowerOnMuteCnt==8)
		 {
		 	  pa_mute1();
		 }
	   #endif
    	  bPowerOnMuteCnt--;
    	  if(bPowerOnMuteCnt==0)
    	  {  //unmute
		 #ifdef support_power_off_tone
		 #ifdef support_io_det_mute
		 	if(workmode!=LINE_WORK_MODE)
		 #endif    	  
		 #endif    	  
	    	  pa_umute1();
      	  }
   }
#endif
#ifdef IO_MUTE_DELAY_ALL_STATE
	if(bMuteDelayCnt){
	bMuteDelayCnt--;
	 pa_mute();
	if(bMuteDelayCnt==0){	
	 // dac_mute(0,1);
	  pa_umute();
	  }
	}
#endif
#ifdef support_amp_power_control
 #ifdef POWER_ON_KEEP_MUTE_FOR_4S	
	if(bAmpPowerOnMuteCnt){
	bAmpPowerOnMuteCnt--;
	AMP_POWER_ONOFF(0);
	if(bAmpPowerOnMuteCnt==0)
		AMP_POWER_ONOFF(1);
	}
 #endif
#endif

   sys_halfsec = !sys_halfsec;
   
#ifdef SUPPORT_AUX_FM_BT_SHOW_REC_TIME
   if((g_rec_ctl)&&(ENC_STOP != g_rec_ctl->enable)){
   if(sys_halfsec&&(ENC_STAR == g_rec_ctl->enable)){
    dwAuxFmBtRecordTimeCnt++;
    if(dwAuxFmBtRecordTimeCnt>4294967295)dwAuxFmBtRecordTimeCnt=0;
    }
    }
#endif
       //puts("#");
    }

    //PORTA_OUT ^= BIT(9);
}
#endif
#define MAX_TIME_CNT 0x7fff
#define MIN_TIME_CNT 0x100

void timer0_init()
{
    u32 clk;
    u32 prd_cnt;
    u8 index;

    clk = clock_get_lsb_freq();
//    printf("\n timer0_init ---\nlsb = %u\n",clk);

    clk /=1000;
    #if defined(SUPPORT_BREATH_LIGHT)
	clk *=1;//1ms
#elif defined SUPPORT_ZY_4LED_RGB  ||defined SUPPORT_RGB_BREATH_LAMP 
	    clk *=0.1;//2ms
    #else
    clk *=2;//2ms
    #endif
    for(index=0; index<(sizeof(timer_div)/sizeof(timer_div[0])); index++)
    {
        prd_cnt = clk/timer_div[index];
        if(prd_cnt>MIN_TIME_CNT && prd_cnt<MAX_TIME_CNT)
        {
            break;
        }
    }

    //printf("prd_cnt = %u\nindex = %d\n",prd_cnt,index);

    //index = index;//获取index值

    TMR0_CNT = 0;
    TMR0_PRD = prd_cnt;
    TMR0_CON = (index<<4)| BIT(0);

//
//#if 0//LSB48M   16分频
//    TMR0_CNT = 0;
//    TMR0_PRD = 6000; //2ms
//    TMR0_CON = BIT(0) | BIT(5);//| BIT(5);  // LSB48  16分频
//#endif
//
//#if 0     //LSB 30M   64分频
//    TMR0_CNT = 0;
//
//    //TMR0_PRD = 937/4; //500us
//    //TMR0_PRD = 937/2; //1ms
//    TMR0_PRD = 937; //2ms
//    //TMR0_PRD = 937*2; //4ms
//    //TMR0_PRD = 937*25; //50ms
//    //TMR0_PRD = 65535; //139.8ms
//    TMR0_CON = BIT(0) | BIT(4)| BIT(5);  // LSB 30M  64分频
//#endif
//
//#if 0     //LSB 30M   16分频
//    TMR0_CNT = 0;
//
//    //TMR0_PRD = 3750/5; //400us
//    //TMR0_PRD = 3750/2; //1ms
//    TMR0_PRD = 3750; //2ms
//    //TMR0_PRD = 3750*10; //20ms
//    //TMR0_PRD = 65535; //34.95ms
//
//    TMR0_CON = BIT(0) |  BIT(5);  //
//#endif
//
//#if 0     //LSB 30M   4分频
//    TMR0_CNT = 0;
//
//    //TMR0_PRD = 15000/4; //500us
//    TMR0_PRD = 15000; //2ms
//    //TMR0_PRD = 65535; //8.7ms
//
//    TMR0_CON = BIT(0) |  BIT(4);  //
//#endif
//
//#if 0     //LSB 30M   0分频
//    TMR0_CNT = 0;
//
//    //TMR0_PRD = 60000/4; //500us
//    TMR0_PRD = 60000; //2ms
//    //TMR0_PRD = 65535; //2.18ms
//
//    TMR0_CON = BIT(0);  //
//#endif
//
//
//
//#if 0     //OSC 12M   64分频
//    TMR0_CNT = 0;
//
//    //TMR0_PRD = 375/4; //500us
//    TMR0_PRD = 375; //2ms
//    //TMR0_PRD = 65535; //349.5ms
//
//    TMR0_CON = BIT(0) | BIT(3)| BIT(4)| BIT(5);
//#endif
//
//#if 0     //OSC 12M   16分频
//    TMR0_CNT = 0;
//
//    //TMR0_PRD = 1500/4; //500us
//    TMR0_PRD = 1500; //2ms
//    //TMR0_PRD = 1500*25; //50ms
//
//    TMR0_CON = BIT(0) | BIT(3)| BIT(5);  //
//#endif
//
//#if 0     //OSC 12M   4分频
//    TMR0_CNT = 0;
//
//    //TMR0_PRD = 6000/4; //500us
//    TMR0_PRD = 6000; //2ms
//    //TMR0_PRD = 6000*10; //20ms
//
//    TMR0_CON = BIT(0) | BIT(3)| BIT(4);  //
//#endif
//
//#if 0     //OSC 12M   0分频
//    TMR0_CNT = 0;
//
//    //TMR0_PRD = 24000/4; //500us
//    TMR0_PRD = 24000; //2ms
//
//    TMR0_CON = BIT(0) | BIT(3);  //
//#endif

    INTALL_HWI(TIME0_INIT, timer0_isr, 1) ; //timer0_isr
}
