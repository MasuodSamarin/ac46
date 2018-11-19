#include "app_cfg.h"
#include "os_api.h"
#include "error.h"
#include "drv_manage.h"
#include "music.h"
#include "msg.h"
#include "task_manage.h"
#include "mango_dev_sd.h"
#include "dac_api.h"
#include "dev_ctl.h"
#include "main_key.h"
#include "linein.h"
#include "usb_device.h"
#include "fm_radio.h"
#include "sys_detect.h"
#include "vm_api.h"
#include "file_op.h"
//#include "resource_manage.h"
#include "key.h"
#include "key_voice.h"
#include "sys_cfg.h"
#include "config.h"
#include "led.h"
#if REC_EN
    #include "record.h"
    #include "encode.h"
#endif
#if 1//UI_ENABLE
#include "led7_drv.h"
#endif
#ifdef SUPPORT_PT2313
#include "pt2313.h"
#endif
#ifdef SUPPORT_M62429
#include "M62429.h"
#endif
#ifdef KOK_DETECT_USE_KEY
#include "kok_detect.h"
#endif
#ifdef MUSIC_PROMPT_EN
#include "play_sel.h"
#endif

#ifdef LED_ONOFF_CONTROL_WITH_KEY
extern bool bRgbIfRun;
extern u8 bRgbMode;
#endif

#if IR_NUM_INPUT_EN
u8 ir_num_timeout_cnt=0;
#endif
#ifdef EXIT_BLUE_MODE_DISCONNECT_VOICE
bool prev_task_is_blue=FALSE;
#endif
#if LED_SHOW_VOL_MAX
u8 bVolMaxChangeToSmallVolMax=LED_SHOW_VOL_MAX;
#endif
#if BT_VOL_MAX
u8 bBtTempVol=BT_VOL_MAX;
#endif
bool bir_5_plus=false;
bool bir_10_plus=false;
bool bir_100_plus=false;
bool bir_200_plus=false;
#ifdef SUPPORT_IR_INPUT_2_3NUMS
bool bir_2_nums=FALSE;
bool bir_3_nums=FALSE;
#endif
#ifdef DURING_FM_EXITING_TASK_NOT_RESPOND_KEY_MSG
u8 bExitFMStateCnt=0;
#endif
#ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE
#if LINEIN_MULTIPLY_DEFAULT_MODE
u8 bModeOfAuxContained=LINEIN_MULTIPLY_DEFAULT_MODE;
#else
u8 bModeOfAuxContained=0;
#endif
#endif
#ifdef SUPPORT_ONE_KEY_TO_USB
bool bOneKeyToUsb_flag=FALSE;
#endif
#ifdef SUPPORT_ONE_KEY_TO_SD
bool bOneKeyToSd_flag=FALSE;
#endif
#ifdef ONLY_POWER_ON_MUTE
u8 bPowerOnMuteCnt=0;
#endif
#ifdef IO_MUTE_DELAY_ALL_STATE
u8 bMuteDelayCnt=0;
#endif
#ifdef support_amp_power_control
 #ifdef POWER_ON_KEEP_MUTE_FOR_4S
u8 bAmpPowerOnMuteCnt=0;
 #endif
#endif
#ifdef AFTER_RECORD_PLAY_LAST_RECORDED_FILE
u8 bExitRecordModePlayLastRecordedFileFlag=FALSE;
#endif
#ifdef MUSIC_PROMPT_EN
u8 device_file_num;
#endif
#ifdef LED_MIC_PRIORITY_FLASH_FAST
u8 bLedModeBake=0;
#endif
#ifdef support_mode_key_user_usb_sd
bool  usb_to_sd_flag;    // USB SD √É‚Äî√Ç¬™√Ç¬ª√Ç¬ª√É‚Äô√Ç¬ª√Ç¬¥√É≈Ω√Ç¬±√É¬™√Ç¬º√É‚Ä°
#endif 

#ifdef support_power_on_low_power_io_delay
 u8  power_delay=250;
#endif

#ifdef MUSIC_PROMPT_MODIFY
 bool power_on_flag ;
#endif 

#ifdef  SUPPORT_ZY_SA_VOICE
u8 IsVoiceEnable;	
#endif

#ifdef SUPPORT_WOKRMODE // jsuo add
 u8 workmode;
#endif
#ifdef support_power_on_30s_bat_icon_on // jsuo add
 u8 bat_icon_timer=60; 
#endif

#ifdef SUPPORT_REC_KEY_FIRST_CANCEL_RECPLAY_STATE
u8 bCancelRecplayFlag=0; 
#endif
#ifdef power_on_wait_power_key_down
bool  power_on_flag=0;
#ifdef  support_power_off_tone
u8 power_off_timer;
#endif
#ifdef support_power_on_muisc_pause_state				
bool	power_on_first_sw=0;
#endif
#endif
#if defined(line_user_dac_R)
u8 tone_mute;
#endif
#ifdef SUPPORT_MUSIC_REC_USE_AUX_REC
u8 bMusicToAuxRecFlag;
#endif
#ifdef  SUPPORT_ONE_KEY_AUX_REC	,	
bool bOneKeyAuxRecFlag=0;
#endif
#ifdef SUPPORT_USE_ENCODE_AS_MODE_CHANGE	
u8 bMulitWorkmode=MUSIC_WORK_MODE;
u8 bChangeModeTimer;
#endif

#ifdef support_vol_io_control
u8 bVolTimer;
#endif	
#ifdef  SUPPORT_NUMBER_VOICE
u8 bVoiceNumber;
#endif

#define MAIN_TASK_NAME 			"MainTask"

SYS_CFG g_sys_cfg;

extern volatile u8 new_lg_dev_let;
extern u8 get_bt_test_state();
extern void init_spp_ctrl();
extern inline bool is_phone_active();

u8 usb_in_flag=0;
u8 sd_in_flag=0;
#ifdef MUSIC_PROMPT_EN
extern u32 curr_device_using;
#endif
#ifdef SUPPORT_WELCOME_VOICE
void main_tone_play(void)
{
    tbool psel_enable = 0;

    _PLAY_SEL_PARA *psel_p = NULL;
    psel_p  = malloc_fun(psel_p ,sizeof(_PLAY_SEL_PARA),0);
    tbool b_res;
    if(NULL != psel_p )
    {
        psel_p->file_number = malloc_fun(psel_p->file_number,sizeof(psel_p->file_number[0]),0);
        if(NULL != psel_p->file_number)
        {
            psel_enable = 1;
            psel_p->max_file_number = 1;
            psel_p->delay = 1;
            psel_p->rpt_time = 1;
            psel_p->file_number[0] = BPF_WELCOME_MP3;
        }
        else
        {
            free_fun((void**)&psel_p);
        }
    }
    b_res = play_sel(MAIN_TASK_NAME, 'A', psel_p);
    if(psel_enable)
    {
        free_fun((void**)&psel_p->file_number);
        free_fun((void**)&psel_p);
    }
    if(!b_res)
    {
        psel_enable = 0;
    }
}
#endif

#ifdef support_power_on_tone
void power_on_tone_play(void)
{
    tbool psel_enable = 0;

    _PLAY_SEL_PARA *psel_p = NULL;
    psel_p  = malloc_fun(psel_p ,sizeof(_PLAY_SEL_PARA),0);
    tbool b_res;
    if(NULL != psel_p )
    {
        psel_p->file_number = malloc_fun(psel_p->file_number,sizeof(psel_p->file_number[0]),0);
        if(NULL != psel_p->file_number)
        {
            psel_enable = 1;
            psel_p->max_file_number = 1;
            psel_p->delay = 1;
            psel_p->rpt_time = 1;
            psel_p->file_number[0] = BPF_POWER_ON_MP3;
        }
        else
        {
            free_fun((void**)&psel_p);
        }
    }
    b_res = play_sel(MAIN_TASK_NAME, 'A', psel_p);
    if(psel_enable)
    {
        free_fun((void**)&psel_p->file_number);
        free_fun((void**)&psel_p);
    }
    if(!b_res)
    {
        psel_enable = 0;
    }
}
#endif


#if LED_SHOW_VOL_MAX
void sysVolMaxChangeToUserVolMaxProc(bool bVolIncOrMinus)
{
 #if SYS_VOL_MAX==25 && LED_SHOW_VOL_MAX==15
  if(bVolIncOrMinus){ //vol plus
    bVolMaxChangeToSmallVolMax++;
    if(bVolMaxChangeToSmallVolMax>15){
        bVolMaxChangeToSmallVolMax=15;
        dac_var.cur_sys_vol_l=SYS_VOL_MAX;
        }
    else if(bVolMaxChangeToSmallVolMax<=5)
       dac_var.cur_sys_vol_l+=2;
    else
       dac_var.cur_sys_vol_l++;
  }else{//vol minus
    if(bVolMaxChangeToSmallVolMax) bVolMaxChangeToSmallVolMax--;
    if(bVolMaxChangeToSmallVolMax==0) dac_var.cur_sys_vol_l=0;

    if(bVolMaxChangeToSmallVolMax>5) dac_var.cur_sys_vol_l--;
    else if(bVolMaxChangeToSmallVolMax>0) dac_var.cur_sys_vol_l-=2;
  }
#elif SYS_VOL_MAX==27 && LED_SHOW_VOL_MAX==32
  if(bVolIncOrMinus){//vol plus
   bVolMaxChangeToSmallVolMax++;
   if(bVolMaxChangeToSmallVolMax>32){
      bVolMaxChangeToSmallVolMax=32;
      dac_var.cur_sys_vol_l=SYS_VOL_MAX;
      }
      else if (bVolMaxChangeToSmallVolMax<=5)
		  dac_var.cur_sys_vol_l+=0;
		  else
			  dac_var.cur_sys_vol_l++;
  }
   else{//vol minus
	   if(bVolMaxChangeToSmallVolMax) bVolMaxChangeToSmallVolMax--;
	   if(bVolMaxChangeToSmallVolMax==0) dac_var.cur_sys_vol_l=0;
	   
	   if(bVolMaxChangeToSmallVolMax>5) dac_var.cur_sys_vol_l--;
	     else if(bVolMaxChangeToSmallVolMax>0) dac_var.cur_sys_vol_l-=0;
   }
   
#elif SYS_VOL_MAX==30 && LED_SHOW_VOL_MAX==32

 #ifdef SUPPORT_OUT_POWER_CONTROL		
  if(out_power_max_val==22)
 	{
		   if(bVolIncOrMinus){//vol plus
		   bVolMaxChangeToSmallVolMax++;
		   if(bVolMaxChangeToSmallVolMax>32)
		   	{
			      bVolMaxChangeToSmallVolMax=32;
			      dac_var.cur_sys_vol_l=22;
		      }
		      else if (bVolMaxChangeToSmallVolMax<=2)
				  dac_var.cur_sys_vol_l =0;
		  	else
			  dac_var.cur_sys_vol_l=bVolMaxChangeToSmallVolMax*11/15;
		  }
		   else{//vol minus
			   if(bVolMaxChangeToSmallVolMax) bVolMaxChangeToSmallVolMax--;
			   
			   if(bVolMaxChangeToSmallVolMax==0)
			   	dac_var.cur_sys_vol_l=0;			   
			   else if(bVolMaxChangeToSmallVolMax==0)
			   	dac_var.cur_sys_vol_l=bVolMaxChangeToSmallVolMax*11/15;;

		   }
	}
   else
#endif

  if(bVolIncOrMinus){//vol plus
   bVolMaxChangeToSmallVolMax++;
   if(bVolMaxChangeToSmallVolMax>32){
      bVolMaxChangeToSmallVolMax=32;
      dac_var.cur_sys_vol_l=SYS_VOL_MAX;
      }
      else if (bVolMaxChangeToSmallVolMax<=2)
		  dac_var.cur_sys_vol_l+=0;
		  else
			  dac_var.cur_sys_vol_l++;
  }
   else{//vol minus
	   if(bVolMaxChangeToSmallVolMax) bVolMaxChangeToSmallVolMax--;
	   if(bVolMaxChangeToSmallVolMax==0) dac_var.cur_sys_vol_l=0;
	   
	   if(bVolMaxChangeToSmallVolMax>2) dac_var.cur_sys_vol_l--;
	     else if(bVolMaxChangeToSmallVolMax>0) dac_var.cur_sys_vol_l-=0;
   }
 #elif SYS_VOL_MAX==27 && LED_SHOW_VOL_MAX==30
	 if(bVolIncOrMinus){//vol plus
	  bVolMaxChangeToSmallVolMax++;
	  if(bVolMaxChangeToSmallVolMax>30){
		 bVolMaxChangeToSmallVolMax=30;
		 dac_var.cur_sys_vol_l=SYS_VOL_MAX;
		 }
		 else if (bVolMaxChangeToSmallVolMax<=4)
			 dac_var.cur_sys_vol_l+=0;
			 else
				 dac_var.cur_sys_vol_l++;
	 }
	  else{//vol minus
		  if(bVolMaxChangeToSmallVolMax) bVolMaxChangeToSmallVolMax--;
		  if(bVolMaxChangeToSmallVolMax==0) dac_var.cur_sys_vol_l=0;
		  
		  if(bVolMaxChangeToSmallVolMax>4) dac_var.cur_sys_vol_l--;
			else if(bVolMaxChangeToSmallVolMax>0) dac_var.cur_sys_vol_l-=0;
	  }  
   
#elif SYS_VOL_MAX==26 && LED_SHOW_VOL_MAX==30
	 if(bVolIncOrMinus){//vol plus
	  bVolMaxChangeToSmallVolMax++;
	  if(bVolMaxChangeToSmallVolMax>30){
		 bVolMaxChangeToSmallVolMax=30;
		 dac_var.cur_sys_vol_l=SYS_VOL_MAX;
		 }
		 else if (bVolMaxChangeToSmallVolMax<=4)
			 dac_var.cur_sys_vol_l+=0;
			 else
				 dac_var.cur_sys_vol_l++;
	 }
	  else{//vol minus
		  if(bVolMaxChangeToSmallVolMax) bVolMaxChangeToSmallVolMax--;
		  if(bVolMaxChangeToSmallVolMax==0) dac_var.cur_sys_vol_l=0;
		  
		  if(bVolMaxChangeToSmallVolMax>4) dac_var.cur_sys_vol_l--;
			else if(bVolMaxChangeToSmallVolMax>0) dac_var.cur_sys_vol_l-=0;
	  }
#elif MP3_VOL_MAX==26 && LED_SHOW_VOL_MAX==30
		   if(bVolIncOrMinus){//vol plus
			bVolMaxChangeToSmallVolMax++;
			if(bVolMaxChangeToSmallVolMax>30){
			   bVolMaxChangeToSmallVolMax=30;
			   dac_var.cur_sys_vol_l=MP3_VOL_MAX;
			   }
			   else if (bVolMaxChangeToSmallVolMax<=4)
				   dac_var.cur_sys_vol_l+=0;
				   else
					   dac_var.cur_sys_vol_l++;
		   }
			else{//vol minus
				if(bVolMaxChangeToSmallVolMax) bVolMaxChangeToSmallVolMax--;
				if(bVolMaxChangeToSmallVolMax==0) dac_var.cur_sys_vol_l=0;
				
				if(bVolMaxChangeToSmallVolMax>4) dac_var.cur_sys_vol_l--;
				  else if(bVolMaxChangeToSmallVolMax>0) dac_var.cur_sys_vol_l-=0;
			}
#elif FM_VOL_MAX==25 && LED_SHOW_VOL_MAX==30
		   if(bVolIncOrMinus){//vol plus
			bVolMaxChangeToSmallVolMax++;
			if(bVolMaxChangeToSmallVolMax>30){
			   bVolMaxChangeToSmallVolMax=30;
			   dac_var.cur_sys_vol_l=FM_VOL_MAX;
			   }
			   else if (bVolMaxChangeToSmallVolMax<=5)
				   dac_var.cur_sys_vol_l+=0;
				   else
					   dac_var.cur_sys_vol_l++;
		   }
			else{//vol minus
				if(bVolMaxChangeToSmallVolMax) bVolMaxChangeToSmallVolMax--;
				if(bVolMaxChangeToSmallVolMax==0) dac_var.cur_sys_vol_l=0;
				
				if(bVolMaxChangeToSmallVolMax>5) dac_var.cur_sys_vol_l--;
				  else if(bVolMaxChangeToSmallVolMax>0) dac_var.cur_sys_vol_l-=0;
			}			
 #elif 	SYS_VOL_MAX==30 && LED_SHOW_VOL_MAX==64		
 if(bVolIncOrMinus){//vol plus
  bVolMaxChangeToSmallVolMax++;
  if(bVolMaxChangeToSmallVolMax>64){
	 bVolMaxChangeToSmallVolMax=64;
	 dac_var.cur_sys_vol_l=SYS_VOL_MAX;
	 }else
	   if (bVolMaxChangeToSmallVolMax<=4)
		 dac_var.cur_sys_vol_l=0;
		 else if(bVolMaxChangeToSmallVolMax%2==0){
		 if(dac_var.cur_sys_vol_l < dac_var.max_analog_vol_l)
		dac_var.cur_sys_vol_l++;
		}
 }
  else{//vol minus
	  if(bVolMaxChangeToSmallVolMax) bVolMaxChangeToSmallVolMax--;
	  if(bVolMaxChangeToSmallVolMax==63)dac_var.cur_sys_vol_l=SYS_VOL_MAX;
	  if(bVolMaxChangeToSmallVolMax<=4) {
	    dac_var.cur_sys_vol_l=0;
	  }
	  if(bVolMaxChangeToSmallVolMax>=4) {
	    if(bVolMaxChangeToSmallVolMax%2==0) {
	         if(dac_var.cur_sys_vol_l)
	          dac_var.cur_sys_vol_l--;
	          }
	  }
  }
#endif
}
//#elif BT_VOL_MAX

#endif

static void TaskSecond(void *p_arg)
{
    while(1)
    {
        os_time_dly(200);
        //// puts(".");
        //bt’˝≥£π§◊˜ƒ£ Ω ±≤Ÿ◊˜–¥vm£¨Ω¯»Î≤‚ ‘ƒ£ Ω ±∫Ú≤ª–¥vm
        if(!get_bt_test_state())
        {
            vm_cache_submit();
        }
    }
}

void vm_start(void)
{
//    vm_init_api(&g_sys_cfg.flash_cfg);

//    vm_open_all();
    os_task_create(TaskSecond,
                   (void*)0,
                   SecondPrio,
                   10,
#if OS_TIME_SLICE_EN > 0
                   1,
#endif
                   "test"
                  );
}


#ifdef power_on_wait_power_key_down

void  main_powerup_wait(void)
{
	int key_statu = 0xff;
#if defined(ENABLE_POWER_ON_KEY_WAIT)&&defined(support_io_power_on_off)
	u8 time_cnt0=0;
#endif

#ifdef support_io_power_on_off
	Set_power_on_off_io_is_out();
	Set_power_on_off_io_is_LOW();
#endif

//	led_fre_set(0);   //ø™PP LED

#ifdef support_short_push_key_power_on
	Set_power_on_off_io_is_out();
	Set_power_on_off_io_is_HIGH(); ;
//	// puts("########### \n ");
	power_on_flag=1;

#else

	while(1)
	{
		os_taskq_pend(0, 1, &key_statu);

		switch(key_statu)
		{
			case MSG_POWER_OFF:
			//	// puts("main_MSG_POWER_DOWN \n ");
                   #ifdef support_io_power_on_off
                   	Set_power_on_off_io_is_out();
                   	Set_power_on_off_io_is_HIGH();
			power_on_flag=1;
			 #ifdef  support_power_off_tone
			 power_off_timer=0;
			 #endif

                   #endif
				return;
		   
			case MSG_HALF_SECOND:
		#if defined(ENABLE_POWER_ON_KEY_WAIT)&&defined(support_io_power_on_off)
				if(time_cnt0++>6)
				{
					#ifdef support_power_on_muisc_pause_state				
						power_on_first_sw=1;
					#endif
					Set_power_on_off_io_is_out();
					Set_power_on_off_io_is_HIGH();
					power_on_flag=1;
					return;
				}
		#endif
			//	// puts(" powerup_half\n ");
				break;
		}
	}
#endif
}
#endif



//#include "irtc.h"
static void TaskMain(void *p)
{
	int msg[6];
	u32 status;
    u32 bt_status;
    u32 bplay_predev;
	curr_task = NULL;


	
#ifdef SUPPORT_WOKRMODE
	workmode=MAIN_WORK_MODE;
#endif
 #ifdef SUPPORT_OUT_POWER_CONTROL		
	power_on_timer=6;
	out_power_max_val=30; 
#endif
#ifdef support_power_on_30s_bat_icon_on // jsuo add
	 bat_icon_timer=60; 
#endif
	
#ifdef POWER_ON_WELCOME_VOICE_PLAYED_IN_IDLE_MODE
	   led7_var.bIfPlayWelcomeVoice=TRUE;
#endif	

#ifndef SUPPORT_SSM_VOICE
	 #ifdef SUPPORT_VOICE_ONOFF
	 #ifdef SUPPORT_MODE_VOICE_AND_NOTICE_ONOFF_MEM
	 
	 		vm_read_api(VM_SYS_EQ,&led7_var.bIfHaveVoice);
	 
	 	 #ifdef SUPPORT_DOUBLE_VOICE
	 	 	if(led7_var.bIfHaveVoice>2)
	 	 #else
	 	 	if(led7_var.bIfHaveVoice>1)
	 	 #endif
	 		{
	 			led7_var.bIfHaveVoice=POWER_ON_VOICE_DEFAULT;
	 		}		
			#ifdef  SUPPORT_ZY_SA_VOICE		 
	 			IsVoiceEnable=led7_var.bIfHaveVoice;
			 #endif
	 #else
	 
	     #ifdef POWER_ON_VOICE_DEFAULT
	 	led7_var.bIfHaveVoice=POWER_ON_VOICE_DEFAULT;
	     #else
	 	led7_var.bIfHaveVoice=TRUE;
	 	#endif
	 #endif	
	 #endif	
#endif

#ifdef support_send_ir_code
	send_timer=0;
	vol_key_sw=0;		
#endif				 

  #ifdef LED_SHOW_DEVICE_TYPE_SWITCH
	  led7_var.blast_play_device=0;
  #endif
#ifdef LED_EQ_BAR_SHOW
   led7_var.bEqMode=EQ_BAR_MODE_DEFAULT;
#endif   
  #ifdef KEY_CONTROL_LED_SCREEN_COLOR_MODE
	  led7_var.bScreenColorMode=LED_SCREEN_COLOR_DEFAULT;
  #endif

  #ifdef support_power_on_low_power_io_delay
   power_delay=250;
#endif

    #ifdef power_on_wait_power_key_down
           main_powerup_wait();
    #endif


  #ifdef AMP_IC_WORK_ONFF
	  Set_amp_power_out();		   
	  Set_AMP_ON(); 				
 #endif
 
#ifdef support_backlight_led
	backlight_led_d_out();
	Set_backlight_led_h();
#endif

#if UI_ENABLE
 	led7_init();
#endif

 #ifdef support_vol_io_control
 	VOL_IO_OFF();
 #endif        

#ifdef support_amp_power_control
 #ifdef POWER_ON_KEEP_MUTE_FOR_4S
 AMP_POWER_ONOFF(0);
 bAmpPowerOnMuteCnt=6;
 #endif
#endif
  #ifdef ONLY_POWER_ON_MUTE
 #if defined support_power_no_media_to_bt 
#ifdef  POWER_ON_VALUE
	 bPowerOnMuteCnt=POWER_ON_VALUE;  
#else
	 bPowerOnMuteCnt=18;  
#endif
 #else
 	 bPowerOnMuteCnt=10;  
#endif  
	 pa_mute1();
  #endif
 #if PA_EN
	 pa_mute();
 #endif 	
#ifdef IO_MUTE_DELAY_ALL_STATE
   bMuteDelayCnt=6;
#endif
#ifdef KOK_DETECT_USE_KEY
		g_kok_var.bKokKeyOpenFlag=FALSE;
	#if LED_SHOW_MIC_PRIORITY
		setLedLight(LED_SHOW_MIC_PRIORITY,g_kok_var.bKokKeyOpenFlag,0);
	#endif
#endif
#ifdef SUPPORT_WELCOME_VOICE
		 // pa_umute();

		  // voice_prompt_play(MAIN_TASK_NAME,BPF_WELCOME_MP3);
		  //main_tone_play();
		  //OSTimeDly(200);
#endif

	dev_ctrl_sys_init(0);
    digit_auto_mute_set(AUTO_MUTE_ENABLE,4,1200,200);
    vm_start();

#ifdef MUSIC_PROMPT_MODIFY
	 power_on_flag=1 ;
#endif 

#ifdef  SUPPORT_ZY_SA_VOICE
#ifdef support_voice_onoff_mem

		vm_read_api(VM_SYS_EQ,&IsVoiceEnable);

	 #ifdef  POWER_ON_VOICE_DEFAULT  

		if(IsVoiceEnable>2)
		{
			IsVoiceEnable=POWER_ON_VOICE_DEFAULT;
		}
		 #ifdef SUPPORT_SSM_VOICE
			voice_save=POWER_ON_VOICE_DEFAULT;
		 #endif
	 #else
		if(IsVoiceEnable>1)
		{
			IsVoiceEnable=0;
		}
		
	 #endif

		led7_var.bIfHaveVoice	=IsVoiceEnable;
		
#else
	 #ifdef  POWER_ON_VOICE_DEFAULT  
	 		IsVoiceEnable=POWER_ON_VOICE_DEFAULT;
	 #else
	 		IsVoiceEnable=1;
	 #endif
#ifdef SUPPORT_VOICE_ONOFF

	 led7_var.bIfHaveVoice=IsVoiceEnable;
#endif
#endif
#endif	
	audio_init();
	system_cfg_file_init();
	sys_power_up_check();
	
	
  #if defined(SUPPORT_LCD_4COM_9SEG_MODE)||defined(SUPPORT_LCD_5COM_8SEG_MODE)
	  LCD_INIT();
  #endif
 #ifdef SUPPORT_PT2313
		  PT2313_Init();
	#ifdef SWVOL_LED_SHOW_MAX
		swvol_temp_vol=SWVOL_LED_SHOW_DEFAULT;
	#endif
  #endif
#ifdef SUPPORT_M62429
		  M62429Init();
   #ifdef MIC_LED_SHOW_MAX
		  mic_temp_vol=MIC_LED_SHOW_DEFAULT_VOL;
   #endif
   #ifdef MIC_ECHO_LED_SHOW_MAX
		  mic_echo_temp_vol=MIC_ECHO_LED_SHOW_DEFAULT;
   #endif
#endif
    /*Hello UI*/
    UI_menu(MENU_POWER_UP);

#if FM_DGND_DETECT_EN
	   FM_DIR_SET;
	   FM_PU_SET;
	   FM_PD_SET;
#endif
#if AUX_DGND_DETECT_EN
	   AUX_DIR_SET;
	   AUX_PU_SET;
#endif
#if IR_SAME_SYSCODE_DETECT_EN
	   IR_DIR_SET;
	   IR_DET_PU_SET;
#endif

	init_spp_ctrl();
	os_time_dly(10);
#if PA_EN       
       #ifndef IO_MUTE_DELAY_ALL_STATE
			pa_umute();
	   #endif
#endif 

	while(1)
	{
		os_taskq_pend(0, ARRAY_SIZE(msg), msg);

		/*GET_SYS_MEM_STAT();*/
        //¿∂—¿≥ı ºªØ∫ÕÀ—À˜–Ë“™∆¡±Œ“ª–©«–ªªƒ£ Ωµƒœ˚œ¢
        bt_status= msg_mask_off_in_bt();
        if(bt_status)
        {
            if((SYS_EVENT_LGDEV_ONLINE!=msg[0])
               &&(SYS_EVENT_LGDEV_OFFLINE!=msg[0])
               &&(MSG_VOL_DOWN!=msg[0])
               &&(MSG_VOL_UP!=msg[0])
               &&(MSG_MUTE!=msg[0])
            #if BT_BACKMODE
				&&(SYS_EVENT_BT_BACKDISCON!=msg[0])
            #endif
           #ifdef SUPPORT_WELCOME_VOICE
				//&&(SYS_EVENT_PLAY_SEL_END!=msg[0])
           #endif
               &&(SYS_EVENT_TASK_RUN_REQ!=msg[0]))
               continue;
        }
        
      #ifdef IDLE_MODE_NOT_RESPONSE_DEVICE_PLUGIN

	  #ifdef power_on_wait_power_key_down
	           if (compare_task_name("IdleTask")){
	             if((MSG_STANBY_KEY!=msg[0])&&(MSG_POWER_OFF!=msg[0]))
	           	  continue;          
	           }	 
	 #else	  
	           if (compare_task_name("IdleTask")){
	             if(MSG_STANBY_KEY!=msg[0])
	           	  continue;          
	           }
	 #endif		  
      #endif
		switch(msg[0])
		{
	      #ifdef SUPPORT_WELCOME_VOICE
		   // case SYS_EVENT_PLAY_SEL_END:		    
			  // play_sel_stop(); //πÿ±’Ã· æ“Ù
		   //    break;
		  #endif
            case SYS_EVENT_LGDEV_ONLINE:
                 printf("LGDEV ONLINE--%08x-%08x\n",msg[1],msg[2]);
                #ifdef MUSIC_PROMPT_EN
				  // if(0x0009ff40==msg[1])
				 if(usb==msg[1])
				   {
					   curr_device_using=usb;
					   device_file_num=BPF_USB_MP3;
				   }
				  // else if(0x0009fec0 == msg[1])
					   else if(sd0 == msg[1])
				   {
					   curr_device_using=sd0;
					   device_file_num=BPF_SD_MP3;
				   }
                #endif
                status=lg_dev_status_chg(SYS_EVENT_LGDEV_ONLINE,(void *)msg[1],msg[2]);
                if((status!=FILE_OP_ERR_LGDEV_FULL)/*&&(status!='A')*/)
                {
                    if((status=='A'))       ///< SPIFLASH…Ë±∏mount
                    {
                        lg_dev_mount((void *)msg[1],status,msg[2]);
                        //// puts("power up\n");
#ifdef BT_TESTER
                        disp_task_init();
#endif

		           #ifdef support_power_on_tone
				 #ifdef  SUPPORT_ZY_SA_VOICE
				 	if(IsVoiceEnable)
				 #endif				   
				 	{
			          #if defined(PA_ENABLE)
		                          pa_umute();
		                  #endif
						  
					#ifdef POWER_ON_WELCOME_VOICE_DELAY						  
				           	os_time_dly(POWER_ON_WELCOME_VOICE_DELAY);
					#endif						  
				               power_on_tone_play();
				           	os_time_dly(250);
						
				 	}
		           #endif


                        bplay_predev=power_up_task();
                        os_taskq_post_event((char *)"CheckTask", 1, SYS_EVENT_LGDEV_ONLINE);
                        break;
                    }
                    else
                    {
                        new_lg_dev_let=status;
                    }
#if defined POWERUP_DEV_IGNORE||defined support_vm_mode_bass_treb_echo
                    if(!msg[3])
                        break;
#endif

                    #if S10_MODE
                    if(!strcmp(curr_task->name,"BtStackTask"))
                        break;
                    #endif/*S10_MODE*/
#ifndef BT_TESTER
                    if(!bt_status)
                    {
                        if(compare_task_name("USBdevTask")) ///<PC Audioƒ£ Ω≤Â»Î…Ë±∏≤ª«–ªªmusic
                            break;
 #ifdef LED_SHOW_DEVICE_PLUGIN	  
							 led7_var.dwDeviceID= msg[1];			 
#endif
                        if((task_switch("MusicTask", 0,SWITCH_SPEC_TASK)==RUN_TASK_ERR_HAS_RPT))
                        {
                               // printf("music has run  \n");
                               os_taskq_post_event((char *)"MusicTask", 2, SYS_EVENT_DEV_ONLINE,status);
                        }
                    }
#endif
                }
                break;
#ifndef BT_TESTER
            case SYS_EVENT_LGDEV_OFFLINE:
                // printf("dev offline ---\n");
                os_taskq_post_event((char *)keymsg_task_name, 2, SYS_EVENT_DEV_OFFLINE,msg[1]);
                lg_dev_status_chg(SYS_EVENT_LGDEV_OFFLINE,(void *)msg[1],1);
                break;
#endif
			case SYS_EVENT_AUX_IN:
                // puts("SYS_EVENT_AUX_IN\n");
#ifdef BT_TESTER
                set_aux_media();
#else
#ifdef POWERUP_DEV_IGNORE
                    if(!msg[1])
                        break;
#endif
                task_switch(LINEIN_TASK_NAME,0,SWITCH_SPEC_TASK);
#endif
                break;
			case SYS_EVENT_AUX_OUT:
                // puts("SYS_EVENT_AUX_OUT\n");
#ifdef BT_TESTER
                set_aux_media();
#else
                if(compare_task_name("LineinTask"))
                    task_switch(0,0,SWITCH_NEXT_TASK);
#endif
                break;
#ifndef BT_TESTER
            case SYS_EVENT_PC_IN:
                // puts("SYS_EVENT_PC_IN\n");
#ifdef POWERUP_DEV_IGNORE
                    if(!msg[1])
                        break;
#endif
                task_switch(PC_TASK_NAME,0,SWITCH_SPEC_TASK);
                break;
            case SYS_EVENT_PC_OUT:
                // puts("SYS_EVENT_PC_OUT\n");
                if(compare_task_name("USBdevTask"))
                    task_switch(0,0,SWITCH_NEXT_TASK);

                break;
            case SYS_EVENT_BT_BACKCON:
                // puts("SYS_EVENT_BT_BACKCON\n");
                break;
            case SYS_EVENT_BT_BACKDISCON:
                // puts("SYS_EVENT_BT_BACKDISCON\n");
               #ifdef BT_DISCONNECT_TO_AUX
				 task_switch(LINEIN_TASK_NAME,0,SWITCH_SPEC_TASK);
               #endif
                break;
            case SYS_EVENT_SYSCLK_NOTFIT_DEVMOUNT:
                //task_switch("MusicTask", 0,SWITCH_SPEC_TASK);
                if(compare_task_name("FMRadioTask"))
                {
                   os_taskq_post_event((char *)"FMRadioTask", 1, SYS_EVENT_SYSCLK_NOTFIT_DEVMOUNT);
                }
                break;

            case MSG_ENTER_IDLE_TASK:
                // puts("MSG_ENTER_IDLE_TASK\n");
                task_switch("IdleTask",0,SWITCH_SPEC_TASK);
                break;

            case MSG_EXIT_IDLE_TASK:
                // puts("MSG_EXIT_IDLE_TASK\n");
                task_switch("BtStackTask",0,SWITCH_SPEC_TASK);
                break;

#if RTC_ALM_EN
            case MSG_ALM_ON:
                // puts("\n\n\n\n------MSG_ALM_ON\n");
                task_switch("RTCTask",0,SWITCH_SPEC_TASK);
                break;
#endif

#ifdef SUPPORT_USE_ENCODE_AS_MODE_CHANGE	

		case MSG_CHANGE_NEXT_MODE:
#if 1
		
		 if(bMulitWorkmode>=RADIO_WORK_MODE)
			bMulitWorkmode=AC3_WORK_MODE;
		else	 if(bMulitWorkmode==CD_WORK_MODE)
		 	{
			 	if((file_operate_get_total_phydev()))	 
					bMulitWorkmode=MUSIC_WORK_MODE;		 
				else
					bMulitWorkmode=LINE_WORK_MODE;		 					
		 	}
		else
		 	bMulitWorkmode++;

		bChangeModeTimer=5;
			
			
		 if(bMulitWorkmode==AC3_WORK_MODE)
		 	{
				AC4052_IS_AC3();
		 	}
		 else  if(bMulitWorkmode==DVD_WORK_MODE)
		 	{
				AC4052_IS_DVD();
		 	}
		 else  if(bMulitWorkmode==CD_WORK_MODE)
		 	{
				AC4052_IS_CD();
		 	}
		 else  if((bMulitWorkmode==MUSIC_WORK_MODE)||(bMulitWorkmode==LINE_WORK_MODE)||(bMulitWorkmode>=RADIO_WORK_MODE))
		 	{
				AC4052_IS_MP3();
		 	}

              	   printf("bMulitWorkmode = %d\n",bMulitWorkmode);


				   			
#else
			 if(bMulitWorkmode>=BT_WORK_MODE)
				bMulitWorkmode=MUSIC_WORK_MODE;
			 else
			 	bMulitWorkmode++;

			bChangeModeTimer=5;
			
			  if(compare_task_name(LINEIN_TASK_NAME))
			  {
				  bModeOfAuxContained++;
					  
					   
				 if(bModeOfAuxContained<mode_linein_max)
				 {				  
					 	 os_taskq_post_msg(LINEIN_TASK_NAME, 1, MSG_AUX_INIT); //¬¥¬•¬∑¬¢AUX√Ñ¬£¬ø√©¬≥√µ√ä¬º¬ª¬Ø
					 break;
				 }
				 else
				 	{
						bModeOfAuxContained=0;		 
				 	}
			 }


				task_switch(0,0,SWITCH_NEXT_TASK);					
#endif		

		break;
		
		case MSG_CHANGE_PREV_MODE:
#if 1

		  if(bMulitWorkmode<=LINE_WORK_MODE)
			bMulitWorkmode=CD_WORK_MODE;
		 else if(bMulitWorkmode==AC3_WORK_MODE)
		 	{
			 	if((file_operate_get_total_phydev()))	 
					bMulitWorkmode=MUSIC_WORK_MODE;		 
				else
					bMulitWorkmode=LINE_WORK_MODE;		 					
		 	}
		 else
		 	bMulitWorkmode--;

			bChangeModeTimer=5;

		 if(bMulitWorkmode==AC3_WORK_MODE)
		 	{
				AC4052_IS_AC3();
		 	}
		 else  if(bMulitWorkmode==DVD_WORK_MODE)
		 	{
				AC4052_IS_DVD();
		 	}
		 else  if(bMulitWorkmode==CD_WORK_MODE)
		 	{
				AC4052_IS_CD();
		 	}
		 else  if((bMulitWorkmode==MUSIC_WORK_MODE)||(bMulitWorkmode==LINE_WORK_MODE)||(bMulitWorkmode>=RADIO_WORK_MODE))
		 	{
				AC4052_IS_MP3();
		 	}

			
           	   printf("bMulitWorkmode = %d\n",bMulitWorkmode);
			
#else	
		 if(bMulitWorkmode<=MUSIC_WORK_MODE)
				bMulitWorkmode=BT_WORK_MODE;
			 else
			 	bMulitWorkmode--;

			  if(compare_task_name(LINEIN_TASK_NAME))
			  {
			  
				 if((bModeOfAuxContained>1)&&(bModeOfAuxContained<mode_linein_max))
				 {				  
					   bModeOfAuxContained--;							 
					 	 os_taskq_post_msg(LINEIN_TASK_NAME, 1, MSG_AUX_INIT); //¬¥¬•¬∑¬¢AUX√Ñ¬£¬ø√©¬≥√µ√ä¬º¬ª¬Ø
					 break;
				 }
				 else
				 	{
						bModeOfAuxContained=0;		 
				 	}
			  }
			else  if(compare_task_name(FM_TASK_NAME))
			{
				bModeOfAuxContained=mode_cd;		 			
			     task_switch(FM_TASK_NAME,0,SWITCH_SPEC_TASK);    				 	   				
				break;
			}

				task_switch(0,0,SWITCH_PRE_TASK);	
#endif
		break;

#endif


			case MSG_CHANGE_WORKMODE:
						
                // puts("MSG_CHANGE_WORKMODE\n");
               #ifdef DURING_FM_EXITING_TASK_NOT_RESPOND_KEY_MSG
				 if(bExitFMStateCnt)break;
				 //if(compare_task_name(FM_TASK_NAME)&& !bExitFMStateCnt)bExitFMStateCnt=4; 													 
              #endif
			  
              #ifdef SUPPORT_FLASH_CHAR
 			    LED_FLASH_CHAR=0;
              #endif

		 #ifdef SUPPORT_CHANGEMODE_NO_IN_AUX
			 // next mode is music and no media;work mode is music and change mode ;jump aux mode
			 //-----------------------------------------------------
			  if(((workmode==RADIO_WORK_MODE)&&(!(file_operate_get_total_phydev())))\
			  	||((workmode==MUSIC_WORK_MODE)&&usb_to_sd_flag))
				{
					{
						 	  task_switch("BtStackTask",0,SWITCH_SPEC_TASK);									
						break;
					}
				}		 
			 //-----------------------------------------------------		  
		 #endif
		 
		 #ifdef SUPPORT_NO_USE_BT_MODE
			 #ifdef MP3_AUX_BT_FM
				  if(workmode==LINE_WORK_MODE)
					{
	       				 #if FM_DGND_DETECT_EN  //IO «∑ÒΩ”µÿºÏ≤‚“™≤ªradio
		 					 #ifdef FM_DETECT_LOW_REMOVE  
		 					 	if(FM_IN_CHECK)
		 					 #else
		 					 	if(!FM_IN_CHECK)
		 					 #endif
	       				 	   	{
								     task_switch(FM_TASK_NAME,0,SWITCH_SPEC_TASK);    				 	   	
	       				 			break;
	       				 	   	}
	       				 	   else
	       				 #endif	
						if(!(file_operate_get_total_phydev()))	 
						{
							break;
						}
						else
				   		{
							   task_switch("MusicTask",0,SWITCH_SPEC_TASK);

							   break;
			 			}
					}	
			#elif defined MP3_AUX_FM_BT
			
				  if(workmode==RADIO_WORK_MODE)
					{
						if(!(file_operate_get_total_phydev()))	 
						{
					  		 task_switch(LINEIN_TASK_NAME,0,SWITCH_SPEC_TASK);						
							break;
						}
						else
				   		{
							   task_switch("MusicTask",0,SWITCH_SPEC_TASK);
							   break;
			 			}
					}		
				  
			 #endif
			 #endif

#if !defined support_only_use_bt_mp3 && !defined ssm_no_use_aux_mode	&& !defined SUPPORT_USE_ENCODE_AS_MODE_CHANGE	   

			  
           #ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE

			#if defined ZY_5028_MP3_AUX_FM_BT	

			  if(workmode==BT_WORK_MODE)
				{
					if(!(file_operate_get_total_phydev()))	 
					{
						bModeOfAuxContained=1;
					  	 task_switch(LINEIN_TASK_NAME,0,SWITCH_SPEC_TASK);
						break;
					}	
					else
					{
						   task_switch("MusicTask",0,SWITCH_SPEC_TASK);			
						   break;
					}
				}	
			  
			  if(compare_task_name(LINEIN_TASK_NAME))
			  {
				if(bModeOfAuxContained==0)
				{
				      bModeOfAuxContained=mode_aux;
					 os_taskq_post_msg(LINEIN_TASK_NAME, 1, MSG_AUX_VOICE_PLAY); //¬¥¬•¬∑¬¢AUX√Ñ¬£¬ø√©¬≥√µ√ä¬º¬ª¬Ø
				   break;
				}
			  }
			#elif defined SUPPORT_MULTIPLE_ZY_MP3_AUX_FM_BT
			
			  if(workmode==BT_WORK_MODE)
				{
					if(!(file_operate_get_total_phydev()))	 
					{
						bModeOfAuxContained=1;
					  	 task_switch(LINEIN_TASK_NAME,0,SWITCH_SPEC_TASK);
						break;
					}	
					else
					{
						   task_switch("MusicTask",0,SWITCH_SPEC_TASK);			
						   break;
					}
				}	
			  			  
			#endif
			
			  if(compare_task_name(LINEIN_TASK_NAME))
			  {
				  bModeOfAuxContained++;
					  
		               #if AUX_DGND_DETECT_EN  //aux use io  connect GND to judge if into linein mode
		            	  #ifdef AUX_DETECT_LOW_REMOVE	
		 				if(!AUX_IN_CHECK)
		         	  #else   
		 			   if(AUX_IN_CHECK)
		         	  #endif
 					{
	 					if(bModeOfAuxContained==mode_aux)
	 					   bModeOfAuxContained++;
 					}
		               #endif   
					   
				 if(bModeOfAuxContained<mode_linein_max)
				 {				  
					 #ifdef support_ac3_voice	
					 	 os_taskq_post_msg(LINEIN_TASK_NAME, 1, MSG_AC3_VOICE_PLAY); //¬¥¬•¬∑¬¢AUX√Ñ¬£¬ø√©¬≥√µ√ä¬º¬ª¬Ø
					 #else
					 	 os_taskq_post_msg(LINEIN_TASK_NAME, 1, MSG_AUX_INIT); //¬¥¬•¬∑¬¢AUX√Ñ¬£¬ø√©¬≥√µ√ä¬º¬ª¬Ø
					 #endif				 
					 break;
				 }
				 else
				 	bModeOfAuxContained=0;		 
			 }
            #ifdef SUPPORT_MP3_IDEL_MODE_IN_LINEIN_MODE
				 else if(compare_task_name("MusicTask"))
				 {
		 		     #if AUX_DGND_DETECT_EN
						  #ifdef AUX_DETECT_LOW_REMOVE	
							if(AUX_IN_CHECK)
						  #else 
						   if(!AUX_IN_CHECK)
						  #endif
					 	  {
						   bModeOfAuxContained=mode_aux;
						   task_switch(0,0,SWITCH_NEXT_TASK);
						   break;
						}
						else 
						  	bModeOfAuxContained=mode_aux; 		
				     #endif
					 
					 #if FM_DGND_DETECT_EN 			   
	 					 #ifdef FM_DETECT_LOW_REMOVE  
	 					 	if(FM_IN_CHECK)
	 					 #else
	 					 	if(!FM_IN_CHECK)
	 					 #endif
					 	{
						 	task_switch(0,0,SWITCH_NEXT_TASK);
						 	break;
					 	}
					 #endif
					 
						#if defined ZY_5028_MP3_AUX_FM_BT	
							   if(usb_to_sd_flag==0 && compare_task_name("MusicTask")&& file_operate_get_total_phydev()>1)
							   {
								   os_taskq_post_msg("MusicTask", 1, MSG_MUSIC_U_SD);
								   usb_to_sd_flag =1;
								   break;
							   }								   
							else
							{
							   bModeOfAuxContained=mode_aux;
							   task_switch(LINEIN_TASK_NAME, 0,SWITCH_SPEC_TASK);
							   break;
							   }
						#elif defined SUPPORT_MULTIPLE_ZY_MP3_AUX_FM_BT
							   if(usb_to_sd_flag==0 && compare_task_name("MusicTask")&& file_operate_get_total_phydev()>1)
							   {
								   os_taskq_post_msg("MusicTask", 1, MSG_MUSIC_U_SD);
								   usb_to_sd_flag =1;
								   break;
							   }								   
							else
							{
							   bModeOfAuxContained=mode_cd;
							   task_switch(LINEIN_TASK_NAME, 0,SWITCH_SPEC_TASK);
							   break;
							   }
						#else
							bModeOfAuxContained=mode_mp3_nodevice;
							if(usb_to_sd_flag&&(file_operate_get_total_phydev()>1)){
								task_switch("FMRadioTask", 0,SWITCH_SPEC_TASK);
							break;
							}
							else if(file_operate_get_total_phydev()<=1)
							{
							  	 task_switch("FMRadioTask", 0,SWITCH_SPEC_TASK);
							   break;
							   }
						#endif
				}
           #endif
        #endif
 #endif //#ifndef support_only_use_bt_mp3	
 

       
		 #ifdef support_mode_key_user_usb_sd
			   if(usb_to_sd_flag==0 && compare_task_name("MusicTask")&& file_operate_get_total_phydev()>1)
			   {
			   os_taskq_post_msg("MusicTask", 1, MSG_MUSIC_U_SD);
			   usb_to_sd_flag =1;
			   break;
			   }
		 #endif	 
		 
	
		#if defined support_only_use_bt_mp3	||defined ssm_no_use_aux_mode	   		 
			if(compare_task_name("MusicTask"))
				{
				   task_switch("BtStackTask",0,SWITCH_SPEC_TASK);			
				   break;
				}			
			else if(compare_task_name("BtStackTask")&&(file_operate_get_total_phydev()))		
				{
				   task_switch("MusicTask",0,SWITCH_SPEC_TASK);			
				   break;
				}
			else if(compare_task_name("BtStackTask")&&(!file_operate_get_total_phydev()))		
				{
				   break;
				}			
		#endif

                #if S10_MODE
                    if(!strcmp(curr_task->name,"BtStackTask"))
                        os_taskq_post_msg("btmsg", 1, MSG_BT_CALL_REJECT);
                    else
                        task_switch(0,0,SWITCH_NEXT_TASK);
                #else

                    task_switch(0,0,SWITCH_NEXT_TASK);
		#endif
		
		break;
		
            case MSG_LAST_WORKMOD:
                task_switch(0,0,SWITCH_LAST_TASK);
                break;
            case SYS_EVENT_TASK_RUN_REQ:
				task_switch((char *)msg[1], 0,SWITCH_SPEC_TASK);
				break;

            case MSG_VOL_DOWN:

		 #ifdef support_vol_io_control
		 	VOL_DEC_SET();
			 bVolTimer=2;
		 #endif	
				
	 	 #if defined SUPPORT_AUX_REC_OFF_DAC_OUT
	 		if(compare_task_name("LineinTask"))
	 	 	break;
	 	 #endif

				
              #ifdef SUPPORT_PT2313
				  PT2313_KEY_PROCESS(menumode,FALSE);
              #else
                 #ifdef LED_SHOW_VOL_MAX
               	  #if MP3_VOL_MAX
					if(compare_task_name("MusicTask"))
					sysVolMaxChangeToUserVolMaxProc(FALSE);
					else if(bVolMaxChangeToSmallVolMax){
					bVolMaxChangeToSmallVolMax--;
					dac_var.cur_sys_vol_l=bVolMaxChangeToSmallVolMax;
					}
                  #elif FM_VOL_MAX
	 				  if(compare_task_name("FMRadioTask"))
	 				  sysVolMaxChangeToUserVolMaxProc(FALSE);
	 				  else if(bVolMaxChangeToSmallVolMax){
	 				  bVolMaxChangeToSmallVolMax--;
	 				  dac_var.cur_sys_vol_l=bVolMaxChangeToSmallVolMax;
	 				  }
               	  #else
					sysVolMaxChangeToUserVolMaxProc(FALSE);
                  #endif
               #else
				  if(dac_var.cur_sys_vol_l)
						  dac_var.cur_sys_vol_l--;
               #endif
                // printf("V- = %d\n",dac_var.cur_sys_vol_l);
                dac_var.cur_sys_vol_r = dac_var.cur_sys_vol_l;
		  #ifdef KOK_DETECT_AUTO_VOL_SET		
		 	 store_vol= dac_var.cur_sys_vol_l;
		 #endif
				
              #endif
             #ifdef SUPPORT_PT2313
			  if(dac_var.bMute && (pt2313data[PT_VOLUME]>0))/*muteÁä∂ÊÄÅ‰∏ãÔºåÂä†ÂáèÈü≥ÈáèËß£mute*/
            #else
                if(dac_var.bMute)/*mute◊¥Ã¨œ¬£¨º”ºı“Ù¡øΩ‚mute*/
            #endif
                {
                    dac_mute(0,1);
                  #if PA_EN
					 pa_umute();
                  #endif
					 //led_fre_set(15); 				   
                  #ifdef SUPPORT_MUTE_FLASH
					  if(b_muteFlag){
					  b_muteFlag=FALSE;
					  LED_FLASH_CHAR=0;
					  LED_FLASH_ICON=0;
					  }
                 #endif
                 #if LED_SHOW_MUTE
					  if(compare_task_name("BtStackTask")||compare_task_name("MusicTask"))
					  setLedLight(LED_SHOW_MUTE,led_mode_flash_slow,0);
					  else				  
					  setLedLight(LED_SHOW_MUTE,led_mode_on,0);
                #endif
                }
               #if PA_EN &&defined(support_vol_is_0_mute_amp)  
            	 #ifdef SUPPORT_PT2313
				 if((pt2313data[PT_VOLUME]==0)&&!b_muteFlag)
					 os_taskq_post("MainTask", 1, MSG_MUTE);
            	 #else
				   if( dac_var.cur_sys_vol_l==0)
					  { 
					  dac_mute(1,1);
					  pa_mute();					 
					  }
            	 #endif
              #endif 
			  
             #ifdef SUPPORT_PT2313				
               #if UI_ENABLE
			  UI_menu(MENU_VOL_MENU);
               #endif
             #else
			 
		     #ifdef line_user_dac_L
			 if(workmode==LINE_WORK_MODE)
		         set_sys_vol(2, dac_var.cur_sys_vol_r, FADE_OFF);
			 else
		     #elif defined(line_user_dac_R)
			 if(workmode==LINE_WORK_MODE)		 
		         set_sys_vol(dac_var.cur_sys_vol_l, 2, FADE_OFF);
			 else		 
		     #endif 
			 
                set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);
                if(!is_phone_active())
                {
	 		 #ifndef suppport_aux_singe_no_swap
			 	if(compare_task_name("LineinTask"))		 
	 		 	DAA_CON2 |= (BIT(14)|BIT(15));//bypassøÿ÷∆’˝œ‡∑¥œ‡ // BTI14◊Û…˘µ¿ bit15”“…˘µ¿
	 		 #endif         
		#ifndef support_vm_mode_bass_treb_echo	 
                    vm_cache_write(VM_SYS_VOL,&dac_var.cur_sys_vol_l,2);
		#endif
                }
                #ifdef SUPPORT_MUSIC_STOP
	                bPause_state=0;
                #endif
				
		 #ifdef support_send_ir_code // MP5 OFF
	 		show_val=6;
		 #endif
				
                UI_menu(MENU_MAIN_VOL);
				
		#ifdef  SUPPORT_ZY_SA_VOICE		
		 #ifndef SUPPORT_ONLY_MODE_VOICE
		  if (UI_var.bMenuReturnCnt == 0)		
                os_taskq_post_msg(keymsg_task_name, 1, MSG_VOICE_VOLUME_MINUS);                
		#endif			   
		#endif			   
				
             #endif                
		 
                break;
		 
            case MSG_VOL_UP:

		 #ifdef support_vol_io_control
		 	VOL_INC_SET();
			 bVolTimer=2;		 
		 #endif
				
	 	 #if defined SUPPORT_AUX_REC_OFF_DAC_OUT
	 		if(compare_task_name("LineinTask"))
	 	 	break;
	 	 #endif
				
              #ifdef SUPPORT_PT2313
				 PT2313_KEY_PROCESS(menumode,TRUE);
              #else
                #ifdef LED_SHOW_VOL_MAX
            	  #if MP3_VOL_MAX
					 if(compare_task_name("MusicTask"))
					 sysVolMaxChangeToUserVolMaxProc(TRUE);
					 else if(bVolMaxChangeToSmallVolMax < SYS_VOL_MAX){
					 bVolMaxChangeToSmallVolMax++;
					 dac_var.cur_sys_vol_l=bVolMaxChangeToSmallVolMax;
					 }
				  #elif FM_VOL_MAX
					  if(compare_task_name("FMRadioTask"))
					  sysVolMaxChangeToUserVolMaxProc(TRUE);
					  else if(bVolMaxChangeToSmallVolMax < SYS_VOL_MAX){
					  bVolMaxChangeToSmallVolMax++;
					  dac_var.cur_sys_vol_l=bVolMaxChangeToSmallVolMax;
					  }
                  #else
					  sysVolMaxChangeToUserVolMaxProc(TRUE);
         	      #endif
                #else
				   if(dac_var.cur_sys_vol_l < dac_var.max_analog_vol_l) 			   
					   dac_var.cur_sys_vol_l++;
              #endif
				
               #if KEY_TONE_EN && defined(support_vol_max_tone_en)
				   if(dac_var.cur_sys_vol_l == dac_var.max_analog_vol_l)
				   	{
					   send_key_voice(500);
		   			   tone_mute=2; 
				   	}
               #endif
				   // printf("V+ = %d\n",dac_var.cur_sys_vol_l);
				   dac_var.cur_sys_vol_r = dac_var.cur_sys_vol_l;
		  #ifdef KOK_DETECT_AUTO_VOL_SET		
		 	 store_vol= dac_var.cur_sys_vol_l;
		 #endif				   
             #endif
                if(dac_var.bMute)/*mute◊¥Ã¨œ¬£¨º”ºı“Ù¡øΩ‚mute*/
                {
                    dac_mute(0,1);
                    #if PA_EN
                   	 pa_umute();
                    #endif
                   #ifdef SUPPORT_MUTE_FLASH
					   if(b_muteFlag){
					   b_muteFlag=FALSE;
					   LED_FLASH_CHAR=0;
					   LED_FLASH_ICON=0;
					   }
                   #endif
					 
                   #if LED_SHOW_MUTE				   
					 if(compare_task_name("BtStackTask")||compare_task_name("MusicTask"))
					 setLedLight(LED_SHOW_MUTE,led_mode_flash_slow,0);
					 else				 
					 setLedLight(LED_SHOW_MUTE,led_mode_on,0);
                   #endif
                }
                #if PA_EN &&defined(support_vol_is_0_mute_amp)
					 if( dac_var.cur_sys_vol_l==1)
						 pa_umute();
                #endif 
               #ifdef SUPPORT_PT2313
                 #if UI_ENABLE
				  UI_menu(MENU_VOL_MENU);
                 #endif
               #else
			   
	     #ifdef line_user_dac_L
		 if(workmode==LINE_WORK_MODE)
	         set_sys_vol(2, dac_var.cur_sys_vol_r, FADE_OFF);
		 else
	     #elif defined(line_user_dac_R)
		 if(workmode==LINE_WORK_MODE)	
		 	{
		          set_sys_vol(dac_var.cur_sys_vol_l, 2, FADE_OFF);
		 	}
		 else		 
	     #endif 
	          set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);

			   
                if(!is_phone_active())
                {
	 		 #ifndef suppport_aux_singe_no_swap
			 	if(compare_task_name("LineinTask"))		 
	 		 	DAA_CON2 |= (BIT(14)|BIT(15));//bypassøÿ÷∆’˝œ‡∑¥œ‡ // BTI14◊Û…˘µ¿ bit15”“…˘µ¿
	 		 #endif
                #ifndef support_vm_mode_bass_treb_echo
                    vm_cache_write(VM_SYS_VOL,&dac_var.cur_sys_vol_l,2);
		#endif
                }
                #ifdef SUPPORT_MUSIC_STOP
	                bPause_state=0;
                #endif
				
		 #ifdef support_send_ir_code // MP5 OFF
	 		show_val=6;
		 #endif				
                UI_menu(MENU_MAIN_VOL);
               #endif
		#ifdef  SUPPORT_ZY_SA_VOICE		
		 #ifndef SUPPORT_ONLY_MODE_VOICE
		  if (UI_var.bMenuReturnCnt == 0)				
                os_taskq_post_msg(keymsg_task_name, 1, MSG_VOICE_VOLUME_PLUS);                
		#endif			   
		#endif		
		
                break;

            case MSG_MUTE:
                if(dac_var.bMute)
                {
				
                    dac_mute(0,1);
                   #if PA_EN
  				    pa_umute();
                   #endif	   
                   #ifdef SUPPORT_MUTE_FLASH
			   if(b_muteFlag)
			   	{
					   b_muteFlag=FALSE;
					   LED_FLASH_CHAR=0;
					   LED_FLASH_ICON=0;
				   }
                  #endif
				  
              #if LED_SHOW_MUTE
				if(compare_task_name("BtStackTask")||compare_task_name("MusicTask"))
				setLedLight(LED_SHOW_MUTE,led_mode_flash_slow,0);
				else				  
				setLedLight(LED_SHOW_MUTE,led_mode_on,0);
             #endif
			 
			 #ifndef suppport_aux_singe_no_swap
			 	if(compare_task_name("LineinTask"))		 
			 	{
			 		DAA_CON2 |= (BIT(14)|BIT(15));//bypassøÿ÷∆’˝œ‡∑¥œ‡ // BTI14◊Û…˘µ¿ bit15”“…˘µ¿			 
			 	}			 
			 #endif
			 
		 #ifdef support_sound_4052_control
		 #ifdef support_sound_4052_mute_state_control
		 #ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE
		 	 if(compare_task_name("LineinTask"))
		 	 	{
		 	 	   if(bModeOfAuxContained==mode_dvd)
		 	 	   	{
		 	 			AC4052_IS_DVD();	
		 	 	   	}
		 		   else  if(bModeOfAuxContained==mode_cd)
		 		   	{
				   		AC4052_IS_CD();
		 		   	}
		 		   else  if(bModeOfAuxContained==mode_aux)
		 		   	{
		 	 			AC4052_IS_AUX();
		 		   	}
		 	 	}				 
		 #endif			 				 
		 #endif
		 #endif

			 
                }
                else
                {
		 #if KEY_TONE_EN==0
		 	 if(compare_task_name("LineinTask"))		 
				  TRIM_EN(0); 
		 #endif

                    dac_mute(1,1);
					
                 #if PA_EN
				    pa_mute();
                 #endif 
                 #ifdef SUPPORT_MUTE_FLASH
				   b_muteFlag=TRUE;
				   //LED_FLASH_CHAR=0xff;
                 #endif
                #if LED_SHOW_MUTE
				 setLedLight(LED_SHOW_MUTE,led_mode_flash_fast,0);
                #endif
				 #ifdef support_sound_4052_control
			 #ifdef support_sound_4052_mute_state_control
				 if(compare_task_name("LineinTask"))
				 	{
				 	AC4052_IS_MP3();					   
				 	}
			 #endif
			 #endif
			


		#ifdef  SUPPORT_ZY_SA_VOICE		
		 #ifndef SUPPORT_ONLY_MODE_VOICE
                     os_taskq_post_msg(keymsg_task_name, 1, MSG_VOICE_MUTE);				
		#endif
		#endif
		
                }
                break;

            case MSG_LOW_POWER:
                // puts("MSG_LOW_POWER");
                break;

            case MSG_0:
            case MSG_1:
            case MSG_2:
            case MSG_3:
            case MSG_4:
            case MSG_5:
            case MSG_6:
            case MSG_7:
            case MSG_8:
            case MSG_9:
				  if (input_number > 999)
					  input_number = 0;
               #if 0   
				  if(bir_10_plus){
					  input_number=10+input_number%10+msg[0];
					  if(input_number>19)input_number=10;
				  }else
              #endif
				  
				  if(bir_100_plus){
					  input_number=(input_number/100)*100+(input_number%100)*10+ msg[0];
				//	  if(input_number>199)input_number=100;
				  }else
				  
				  if(bir_200_plus){
					  input_number=(input_number/100)*100+(input_number%100)*10+ msg[0];
					//  if(input_number>299)input_number=200;
				  }else
					  input_number = input_number * 10 + msg[0];
				  //// printf("input_number = %u	\n",input_number);
				  
               #ifdef SUPPORT_IR_INPUT_2_3NUMS
				  if(bir_2_nums){
					 if(input_number>99)input_number=0; 	  
					 }
				  else if(bir_3_nums){
					  if(input_number>999)input_number=0;	   
					 }
              #endif

              #if UI_ENABLE
  			   UI_menu(MENU_INPUT_NUMBER);
              #elif IR_NUM_INPUT_EN
  			   ir_num_timeout_cnt=7;
              #endif
			  
		#ifdef  SUPPORT_NUMBER_VOICE
			bVoiceNumber=msg[0];
                     os_taskq_post_msg(keymsg_task_name, 1, MSG_VOICE_NUMBER);				
		#endif				
			  
                break;
				  case MSG_ADD_100:
				  input_number+=100;
				  bir_100_plus=TRUE;
				  bir_10_plus=FALSE;
				  bir_200_plus=FALSE;
               #if UI_ENABLE
				  UI_menu(MENU_INPUT_NUMBER);
               #elif IR_NUM_INPUT_EN
				  ir_num_timeout_cnt=7;
               #endif
				  break;	  
				  
				  case MSG_ADD_200:
				  bir_200_plus=TRUE;
				  bir_10_plus=FALSE;
				  bir_100_plus=FALSE;
				  input_number+=200;
                #if UI_ENABLE
				  UI_menu(MENU_INPUT_NUMBER);
                #elif IR_NUM_INPUT_EN
				  ir_num_timeout_cnt=7;
                #endif
				  break;
				  
				 case MSG_ADD_10:
				 bir_10_plus=TRUE;
				 bir_100_plus=FALSE;
				 bir_200_plus=FALSE;
				  input_number+=10;
               #if UI_ENABLE
				  UI_menu(MENU_INPUT_NUMBER);
               #elif IR_NUM_INPUT_EN
				  ir_num_timeout_cnt=7;
              #endif
				  break;
			  
				 case MSG_ADD_5:
				 bir_5_plus=TRUE;				 	
				 bir_10_plus=FALSE;
				 bir_100_plus=FALSE;
				 bir_200_plus=FALSE;
				  input_number+=5;
               #if UI_ENABLE
				  UI_menu(MENU_INPUT_NUMBER);
               #elif IR_NUM_INPUT_EN
				  ir_num_timeout_cnt=7;
              #endif
				  break;
			  
              #ifdef SUPPORT_IR_INPUT_2_3NUMS
				case MSG_TWO_IR_NUMS:
					bir_2_nums=TRUE;  
					bir_3_nums=FALSE; 
					input_number=0;
					UI_menu(MENU_INPUT_NUMBER);
					break;
				case MSG_THREE_IR_NUMS:
					bir_3_nums=TRUE;
					bir_2_nums=FALSE; 
					input_number=0; 			
					UI_menu(MENU_INPUT_NUMBER);
					break;
              #endif

#endif

#ifdef support_stanby_mod
			   case MSG_STANBY_KEY:
			  if(!compare_task_name("IdleTask"))
			  	{
					 #ifdef support_backlight_led
					 	backlight_led_d_out();
					 	Set_backlight_led_l();
					 #endif
			  	
				  task_switch("IdleTask", 0,SWITCH_SPEC_TASK);					
				 }
			  else
			  {

				 #ifdef support_backlight_led
				 	backlight_led_d_out();
				 	Set_backlight_led_h();
				 #endif
				 
             #if defined(SUPPORT_LCD_4COM_9SEG_MODE)||defined(SUPPORT_LCD_5COM_8SEG_MODE)
				  LCD_INIT();
             #endif
             
	         #ifdef POWER_ON_WELCOME_VOICE_PLAYED_IN_IDLE_MODE					
	 			 if(led7_var.bIfPlayWelcomeVoice){	 
	         #endif			 
                #ifdef STANDBY_ON_FIND_DEVICE_FIRST
				
			status=lg_dev_status_chg(SYS_EVENT_LGDEV_ONLINE,(void *)msg[1],msg[2]);
			if(!bt_status)
			{
					 set_bt_busy_flag(0);					 
					 os_time_dly(25);
					 
	             #ifdef LED_SHOW_DEVICE_PLUGIN  
					led7_var.dwDeviceID= msg[1];			 
	             #endif
	 	          #ifdef POWER_ON_WITH_DEVICE_PLAY_USB_SD_VOICE
	 		               #ifdef MUSIC_PROMPT_EN
	 		 				   // if(0x0009ff40==msg[1])
	 		 				  if(usb==msg[1])
	 		 					{
	 		 						curr_device_using=usb;
	 		 						device_file_num=BPF_USB_MP3;
	 		 					}
	 		 				   // else if(0x0009fec0 == msg[1])
	 		 						else if(sd0 == msg[1])
	 		 					{
	 		 						curr_device_using=sd0;
	 		 						device_file_num=BPF_SD_MP3;
	 		 					}
	 		              #endif
	              #endif
	                 puts(" MSG_STANBY_KEY 111 \n");
		 
			 #ifdef support_power_on_det_media_no_media_to_bt_mode			 
			 	            if(!file_operate_get_total_phydev())
			 	            	{
					                 puts(" MSG_STANBY_KEY 2 bt \n");
			 	            	
			 	                #ifdef POWER_ON_NO_DEV_TO_AUX
			 				 #ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE
			 				 	bModeOfAuxContained=0;
			 				 #endif				
			 		                task_switch("LineinTask", 0,SWITCH_SPEC_TASK);
			 	                #else
			 	                	task_switch("BtStackTask", 0,SWITCH_SPEC_TASK);
			 	                #endif
								break;
			 	            	}
			 	            else		
			 	            	{
					                 puts(" MSG_STANBY_KEY 2 music \n");
			 	            	
			 				  task_switch(IDLE_RESUME_DIRECT_TO_MODE, 0,SWITCH_SPEC_TASK);
							break;
			 	            	}							
			 #else				
					//detect hot plugin dev  and sent msg to music mode 						
					if((task_switch("MusicTask", 0,SWITCH_SPEC_TASK)==RUN_TASK_ERR_HAS_RPT))
					{
						// printf("music has run  \n");
						os_taskq_post_event((char *)"MusicTask", 2, SYS_EVENT_DEV_ONLINE,status);
					}
			 #endif		
					                 puts(" MSG_STANBY_KEY 3333 \n");
			 
					//else task_switch(IDLE_RESUME_DIRECT_TO_MODE, 0,SWITCH_SPEC_TASK);
				  }else
			  #endif			  
              #ifdef IDLE_RESUME_DIRECT_TO_MODE  		
				  task_switch(IDLE_RESUME_DIRECT_TO_MODE, 0,SWITCH_SPEC_TASK);
              #else             
				  task_switch(0,0,SWITCH_LAST_TASK);
              #endif
      #ifdef POWER_ON_WELCOME_VOICE_PLAYED_IN_IDLE_MODE	
             }else {
             task_switch(0,0,SWITCH_LAST_TASK);               
             }
             led7_var.bIfPlayWelcomeVoice=FALSE;
      #endif              
			  }
					break;	
#endif
 #ifdef SUPPORT_ONE_KEY_TO_AUX
			   case MSG_ONE_KEY_TO_AUX: 	
			   	
			    #ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE   
			 
			 		 #ifdef ZY_5028_MP3_AUX_FM_BT	
			 			#if 1
			 
			 			     if((!file_operate_get_total_phydev())&&(compare_task_name("MusicTask")))
			 			     	{
			 				 	bModeOfAuxContained=mode_mp3_nodevice;
			 	 				task_switch(LINEIN_TASK_NAME,0,SWITCH_SPEC_TASK);				
			 				 }
			 				 else
			 		 			   if(!compare_task_name(LINEIN_TASK_NAME)){
			 		 				bModeOfAuxContained=mode_aux;	 
			 		 				task_switch(LINEIN_TASK_NAME,0,SWITCH_SPEC_TASK);
			 		 			   }else{
			 		 				 if(bModeOfAuxContained!=mode_aux){
			 		 				  bModeOfAuxContained=mode_aux; 	 
			 		 				  os_taskq_post_msg(LINEIN_TASK_NAME, 1, MSG_AUX_INIT); //¬¥¬•¬∑¬¢AUX√Ñ¬£¬ø√©¬≥√µ√ä¬º¬ª¬Ø
			 		 				  }						 	
			 		 			   }
			 			#else
			 			 {			 
			 			 	bModeOfAuxContained=mode_mp3_nodevice;
			  				task_switch(LINEIN_TASK_NAME,0,SWITCH_SPEC_TASK);				
			 			 }
			 		   	#endif
			 		#elif defined PLUG_OUT_DEV_TO_IDLE_MODE			
			 		 			   if(!compare_task_name(LINEIN_TASK_NAME)){
			 		 				bModeOfAuxContained=mode_mp3_nodevice;	 
			 		 				task_switch(LINEIN_TASK_NAME,0,SWITCH_SPEC_TASK);
			 		 			   }else{
			 		 				 if(bModeOfAuxContained!=mode_aux){
			 		 				  bModeOfAuxContained=mode_mp3_nodevice; 	 
			 		 				  os_taskq_post_msg(LINEIN_TASK_NAME, 1, MSG_AUX_INIT); //¬¥¬•¬∑¬¢AUX√Ñ¬£¬ø√©¬≥√µ√ä¬º¬ª¬Ø
			 		 				  }
			 		 			   }							
			 		#elif defined PLUG_OUT_DEV_TO_DVD_MODE			
			 		 			   if(!compare_task_name(LINEIN_TASK_NAME)){
			 		 				bModeOfAuxContained=mode_dvd;	 
			 		 				task_switch(LINEIN_TASK_NAME,0,SWITCH_SPEC_TASK);
			 		 			   }else{
			 		 				 if(bModeOfAuxContained!=mode_aux){
			 		 				  bModeOfAuxContained=mode_dvd; 	 
			 		 				  os_taskq_post_msg(LINEIN_TASK_NAME, 1, MSG_AUX_INIT); //¬¥¬•¬∑¬¢AUX√Ñ¬£¬ø√©¬≥√µ√ä¬º¬ª¬Ø
			 		 				  }
			 		 			   }		
			 		 #else   
			 		 			   if(!compare_task_name(LINEIN_TASK_NAME)){
			 		 				bModeOfAuxContained=mode_aux;	 
			 		 				task_switch(LINEIN_TASK_NAME,0,SWITCH_SPEC_TASK);
			 		 			   }else{
			 		 				 if(bModeOfAuxContained!=mode_aux){
			 		 				  bModeOfAuxContained=mode_aux; 	 
			 		 				  os_taskq_post_msg(LINEIN_TASK_NAME, 1, MSG_AUX_INIT); //¬¥¬•¬∑¬¢AUX√Ñ¬£¬ø√©¬≥√µ√ä¬º¬ª¬Ø
			 		 				  }
			 		 			   }
			 		 #endif			   
			    #else
			 			   if(!compare_task_name(LINEIN_TASK_NAME))
			 				   task_switch(LINEIN_TASK_NAME,0,SWITCH_SPEC_TASK);
			    #endif
				   break;
 #endif
 #ifdef SUPPORT_ONE_KEY_TO_AC3
				 case MSG_ONE_KEY_TO_AC3:
				 #ifdef SUPPORT_USE_ENCODE_AS_MODE_CHANGE	
	 				AC4052_IS_AC3();			 
				 #endif	
				 	
       #ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE   
					 if(!compare_task_name(LINEIN_TASK_NAME)){
					  bModeOfAuxContained=mode_ac3;    
					  task_switch(LINEIN_TASK_NAME,0,SWITCH_SPEC_TASK);
					 }else{
					   if(bModeOfAuxContained!=mode_ac3){
						bModeOfAuxContained=mode_ac3;	   
						os_taskq_post_msg(LINEIN_TASK_NAME, 1, MSG_AUX_INIT); //¬¥¬•¬∑¬¢AUX√Ñ¬£¬ø√©¬≥√µ√ä¬º¬ª¬Ø
						}
					 }
	  #endif
				  break;
 #endif
 
#ifdef SUPPORT_ONE_KEY_TO_CD
				 case MSG_ONE_KEY_TO_CD:
				 #ifdef SUPPORT_USE_ENCODE_AS_MODE_CHANGE		 			
	 				AC4052_IS_CD();			 
				 #endif	
				 	
	  #ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE	
					 if(!compare_task_name(LINEIN_TASK_NAME)){
					  bModeOfAuxContained=mode_cd;    
					  task_switch(LINEIN_TASK_NAME,0,SWITCH_SPEC_TASK);
					 }else{
					   if(bModeOfAuxContained!=mode_cd){
						bModeOfAuxContained=mode_cd;	   
						os_taskq_post_msg(LINEIN_TASK_NAME, 1, MSG_AUX_INIT); //¬¥¬•¬∑¬¢AUX√Ñ¬£¬ø√©¬≥√µ√ä¬º¬ª¬Ø
						}
					 }
	 #endif
				  break;
#endif
#ifdef SUPPORT_ONE_KEY_TO_DVD
				 case MSG_ONE_KEY_TO_DVD:

				 #ifdef SUPPORT_USE_ENCODE_AS_MODE_CHANGE	
		 				AC4052_IS_DVD();				 
				 #endif	


		 	  #ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE	
		 					 if(!compare_task_name(LINEIN_TASK_NAME)){
		 					  bModeOfAuxContained=mode_dvd;    
		 					  task_switch(LINEIN_TASK_NAME,0,SWITCH_SPEC_TASK);
		 					 }else{
		 					   if(bModeOfAuxContained!=mode_dvd){
		 						bModeOfAuxContained=mode_dvd;	   
		 						os_taskq_post_msg(LINEIN_TASK_NAME, 1, MSG_AUX_INIT); //¬¥¬•¬∑¬¢AUX√Ñ¬£¬ø√©¬≥√µ√ä¬º¬ª¬Ø
		 						}
		 					 }
		 	 #endif
			 
				  break;
#endif

 #ifdef SUPPORT_ONE_KEY_TO_RADIO
			   case MSG_ONE_KEY_TO_RADIO:					  
			   if(!compare_task_name(FM_TASK_NAME))
				   task_switch(FM_TASK_NAME,0,SWITCH_SPEC_TASK);
				   break;
#endif

 #ifdef SUPPORT_ONE_KEY_TO_MP3
			   case MSG_ONE_KEY_TO_MP3: 				  
			   if(!compare_task_name(MUSIC_TASK_NAME))
			  {
			       #ifdef SUPPORT_MP3_IDEL_MODE_IN_LINEIN_MODE
					   if(!file_operate_get_total_phydev()){	   
					   bModeOfAuxContained=mode_mp3_nodevice;
					   if(!compare_task_name(LINEIN_TASK_NAME))
						   task_switch(LINEIN_TASK_NAME,0,SWITCH_SPEC_TASK);
					   else    
						   os_taskq_post_msg(LINEIN_TASK_NAME, 1, MSG_AUX_INIT); //¬¥¬•¬∑¬¢AUX√Ñ¬£¬ø√©¬≥√µ√ä¬º¬ª¬Ø
					   }else
			       #endif
			   
				   if(file_operate_get_total_phydev())
					   task_switch(MUSIC_TASK_NAME,0,SWITCH_SPEC_TASK);
				 #ifdef SUPPORT_USE_ENCODE_AS_MODE_CHANGE	
				 	else  if(!compare_task_name(LINEIN_TASK_NAME))
				 		{
					 		 bModeOfAuxContained=0;
					 		task_switch(LINEIN_TASK_NAME,0,SWITCH_SPEC_TASK);				 
				 		}
					   else   
					   	{
					 		 bModeOfAuxContained=0;					   	
						  	 os_taskq_post_msg(LINEIN_TASK_NAME, 1, MSG_AUX_INIT); //¬¥¬•¬∑¬¢AUX√Ñ¬£¬ø√©¬≥√µ√ä¬º¬ª¬Ø
					   	}
				
				 #endif				   
				   
				   }
				   break;
#endif

 #ifdef SUPPORT_ONE_KEY_TO_USB
				case MSG_ONE_KEY_TO_USB:	
				if(!file_operate_get_total_phydev()){		
					bOneKeyToUsb_flag=TRUE;
					if(!compare_task_name(MUSIC_TASK_NAME))
						task_switch(MUSIC_TASK_NAME,0,SWITCH_SPEC_TASK);
					}
					break;
#endif

 #ifdef SUPPORT_ONE_KEY_TO_SD
				case MSG_ONE_KEY_TO_SD:
					if(!file_operate_get_total_phydev()){		
					bOneKeyToSd_flag=TRUE;
					if(!compare_task_name(MUSIC_TASK_NAME))
						task_switch(MUSIC_TASK_NAME,0,SWITCH_SPEC_TASK);
					}
					break;
#endif

#ifdef  SUPPORT_ONE_KEY_AUX_REC	,	
			   case MSG_ONE_KEY_AUX_REC: 				  
			   if((compare_task_name(MUSIC_TASK_NAME))&&(file_operate_get_total_phydev()))
				   {
					   bOneKeyAuxRecFlag=1;			   
					   task_switch(LINEIN_TASK_NAME,0,SWITCH_SPEC_TASK);				   
				  }
			   break;	
#endif
			
 #ifdef SUPPORT_ONE_KEY_TO_BT
			   case MSG_ONE_KEY_TO_BT:					  
			   if(!compare_task_name("BtStackTask"))
				   task_switch("BtStackTask",0,SWITCH_SPEC_TASK);
				   break;
#endif
#ifdef USE_KEY_TO_CONTROL_HT1628_LIGHTS_ONOFF
			  case MSG_HT1628_LIGHTS_ONOFF:
				  ifRunTimer=!ifRunTimer;
				  break;
#endif
#ifdef SUPPORT_ONE_KEY_ENTER_START_REC
              case MSG_ONE_KEY_START_REC:     

		 #ifdef SUPPORT_MUSIC_REC_USE_AUX_REC
	                  if(workmode==MUSIC_WORK_MODE)
	 
	            		{
		            			bMusicToAuxRecFlag=2;
		 			      task_switch("LineinTask", 0,SWITCH_SPEC_TASK);		 
		            	}
		 else
		      task_switch("RECTask", 0,SWITCH_SPEC_TASK);			      
                   break;		 	
		 #else
		            #ifdef SUPPORT_REC_KEY_FIRST_CANCEL_RECPLAY_STATE
		 			//bRecReplayFlag=!bRecReplayFlag;
		                  if((workmode==MUSIC_WORK_MODE)&&(bIfRecordFolder))
		                  	{
		 				bCancelRecplayFlag=1;
		 				 os_taskq_post("MusicTask", 1 , MSG_MUSIC_REC_REPLAY_CANCEL);				 
		 			 }
		 			else
		            #endif				
		 			      task_switch("RECTask", 0,SWITCH_SPEC_TASK);			      
		                   break;
		 #endif				  
#endif

#ifdef SUPPORT_AUX_FM_BT_REPLAY_KEY
			  case MSG_COM_REC_REPLAY:
			  if(compare_task_name(FM_TASK_NAME)||compare_task_name(LINEIN_TASK_NAME)||compare_task_name("BtStackTask")||compare_task_name("RECTask"))
			  {			  
				    if((g_rec_ctl)&&(ENC_STOP != g_rec_ctl->enable)){	//recording,stop first
				      if(compare_task_name(FM_TASK_NAME))
		                  os_taskq_post(FM_TASK_NAME, 1, MSG_REC_STOP);
		                  
					      else if(compare_task_name(LINEIN_TASK_NAME))
		                  os_taskq_post(LINEIN_TASK_NAME, 1, MSG_REC_STOP);
		                  
					      else if(compare_task_name("BtStackTask"))
		                  os_taskq_post("BtStackTask", 1, MSG_REC_STOP);
					      else if(compare_task_name("RECTask"))
		                  os_taskq_post("RECTask", 1, MSG_REC_STOP);
						  
		                  os_time_dly(100);
			    }
					
                if(file_operate_get_total_phydev()){
                  bExitRecordModePlayLastRecordedFileFlag=TRUE;
                  os_taskq_post("MainTask", 1, MSG_ONE_KEY_TO_MP3);                  
                }
			  }
            #if 0//def SUPPORT_REPLAY_CANCEL_FOLDER_REPEAT_AND_PLAY_NOT_REC_FILES
			  else if(compare_task_name(MUSIC_TASK_NAME))
                os_taskq_post(MUSIC_TASK_NAME, 1, MSG_MUSIC_REC_REPLAY_CANCEL);
            #endif
			  break;
#endif

#ifdef USE_KEY_SWITCH_LED_MODE
			case MSG_SWITCH_LED_MODE:
				if(!bRGBMode)
				bIfRunTimer=TRUE;
				bRGBMode++;
				if(bRGBMode>4)bRGBMode=0;
	#ifdef LED_SCREEN_SHOW_LED_MODE
				 UI_menu(MENU_LED_MODE);
	#endif
				break;
#endif
#ifdef KEY_CONTROL_LED_SCREEN_COLOR_MODE
				 case  MSG_SWITCH_LED_SCREEN_COLOR:
				 led7_var.bScreenColorMode++;
				 if(led7_var.bScreenColorMode>=LED_SCREEN_COLOR_MODE_MAX)
				 led7_var.bScreenColorMode=0;
				 break;
#endif
			
#ifdef EQ_MODE_CONTROL_WITH_KEY
			  case MSG_EQ_BAR_MODE:
				  led7_var.bEqMode++;
				  if(led7_var.bEqMode>=EQ_BAR_MODE_MAX)
				  led7_var.bEqMode=0;
				  break;
#endif
#ifdef SUPPORT_MAIN_VOL_KEY
			  case MSG_MAIN_VOL_UP:
			  case MSG_MAIN_VOL_DN: 
			   menumode=MENU_MAIN_VOL_MODE;
   #ifdef supper_user_pt2313_ctrl_main_vol
			   // PT_VOL_NOMAL	  0x00	   PT_VOL_UP  0x01		 PT_VOL_DN		  0x02
						   PT2313SetData(msg[0]-MSG_MAIN_VOL_UP+1 ,1);
   #endif	
   #ifdef SWOL_ACTION_WITH_MAIN_VOL_ADJUST
					  PT2313SetData(msg[0]-MSG_MAIN_VOL_UP+0x04 ,2);
   #endif
   #if UI_ENABLE
			   UI_menu(MENU_VOL_MENU);
   #endif
				 break;
#endif
#ifdef SUPPORT_MSG_FRONT_LEFT
			 case MSG_FRONT_LEFT_UP:
			 case MSG_FRONT_LEFT_DN:	
				 menumode=MENU_FRONT_LEFT_MODE;
				PT2313SetData(msg[0]-MSG_FRONT_LEFT_UP+0x0A ,1);
    #if UI_ENABLE
				UI_menu(MENU_VOL_MENU);
    #endif
				break;
#endif
#ifdef SUPPORT_MSG_FRONT_RIGHT
			 case MSG_FRONT_RIGHT_UP:
			 case MSG_FRONT_RIGHT_DN:	 
				 menumode=MENU_FRONT_RIGHT_MODE;
				PT2313SetData(msg[0]-MSG_FRONT_RIGHT_UP+0x0D ,1);
    #if UI_ENABLE
				UI_menu(MENU_VOL_MENU);
    #endif
				break;
#endif
#ifdef	Support_MSG_BASS
			 case MSG_BASS_UP:
			 case MSG_BASS_DN:
				 menumode=MENU_BASS_MODE;
				// PT_BASS_NOMAL  0x0F	  PT_BASS_UP	   0x10    PT_BASS_DN	   0x11
				PT2313SetData(msg[0]-MSG_BASS_UP+0x10 ,1);
    #if UI_ENABLE
				UI_menu(MENU_VOL_MENU);
    #endif
			   break;
#endif 
  #ifdef  Support_MSG_TREBLE
				case MSG_TREBLE_UP:
				case MSG_TREBLE_DN:
					menumode= MENU_TREBLE_MODE;
					// PT_TREB_NOMAL	0x12	PT_TREB_UP		0x13   PT_TREB_DN		0x14
					PT2313SetData(msg[0]-MSG_TREBLE_UP+0x13 ,1);
        #if UI_ENABLE
					UI_menu(MENU_VOL_MENU);
        #endif
						break;
  #endif 
  #ifdef Support_MSG_SWVOL
				 case MSG_SWVOL_UP:
				 case MSG_SWVOL_DN: 	 
					menumode= MENU_SWVOLL_MODE;
					// PT_RL_NOMAL	0x03	  PT_RL_UP		 0x04		PT_RL_DN	   0x05
					// PT_FL_NOMAL	0x09	  PT_FL_UP		 0x0A		PT_FL_DN	   0x0B
					/*¬æ√õ¬≥¬ø √ä¬π√ì√É RR RL √ó√∂√ñ√ò¬µ√ç√í√¥ 
					¬π√∫√é¬¢911√ä¬π√ì√ÉFL FR√ó√∂√ñ√ò¬µ√ç√í√¥*/
        #ifdef pt2313_use_rf_lf_as_sub	// 0x0a    
					PT2313SetData(msg[0]-MSG_SWVOL_UP+0x0A ,2); // 2 √ê√®√ì√É√ç¬¨√ä¬±¬µ√∑ RR RL
        #else
					PT2313SetData(msg[0]-MSG_SWVOL_UP+0x04 ,2); // 2 √ê√®√ì√É√ç¬¨√ä¬±¬µ√∑ RR RL 		  
        #endif
        #if UI_ENABLE
					UI_menu(MENU_VOL_MENU);
        #endif
					break;
   #endif 
#ifdef support_menu_mode   
				   case MSG_MENU_MODE:	  
				   menumode++;
				   #ifdef ENCODER1_ADJUST_MIC_VOL
				   if(menumode==MENU_OK_VOL_MODE)menumode=MENU_ECHO_MODE;
				   #endif
				  if(menumode>=MENU_MAX_MODE)
				   {
      #ifdef MENU_NOT_SWTICH_MAIN_VOL
					menumode=1;
      #else		
				   menumode=0;
     #endif
				   }
    #if UI_ENABLE
				  UI_menu(MENU_VOL_MENU);
    #endif
				   break;			  
 #endif
  #ifdef Support_MSG_RESET
				case MSG_RESET_KEY:
     #ifdef	SUPPORT_PT2313	
					PT2313_reset();
     #endif		
				menumode=MENU_MAIN_VOL_MODE;
	#if UI_ENABLE
				 UI_menu(MENU_RESET);
	#endif
				break;	 
 #endif 
			 
#if defined(SUPPORT_M62429) 
				case MSG_MIC_UP:
   	       #ifdef support_use_pin1pin2_as_mic_vol
						M62429MenuPro(4);	//	4 -> ok vol ++	  1-> ehco ++		
		   #else
						M62429MenuPro(1);	//	4 -> ok vol ++	  1-> ehco ++		
		   #endif
						menumode=MENU_OK_VOL_MODE;
          #if UI_ENABLE
						 UI_menu(MENU_VOL_MENU);
          #endif
				 break; 	 
				 
				case MSG_ECHO_UP:
           #ifdef support_use_pin1pin2_as_mic_vol
						M62429MenuPro(1);
		   #else
						M62429MenuPro(4);	//	4 -> ok vol ++	  1-> ehco ++		
		   #endif
						menumode=MENU_ECHO_MODE;	
		   
					 #ifdef SUPPORT_MIC_ECHO_VM	
 		 					vm_write_api(VM_MIC_ECHO,&M62429Data[1]);					 
					 #endif
		   
          #if UI_ENABLE
						UI_menu(MENU_VOL_MENU);
          #endif
				 break;
				 
				case MSG_MIC_DN:
           #ifdef support_use_pin1pin2_as_mic_vol
						M62429MenuPro(5);
           #else
						M62429MenuPro(2);	//	5 -> ok vol --	  2-> ehco --	  
		   #endif
						menumode=MENU_OK_VOL_MODE;			
           #if UI_ENABLE
						 UI_menu(MENU_VOL_MENU);
           #endif
					 break;  
			 
				case MSG_ECHO_DN:
           #ifdef support_use_pin1pin2_as_mic_vol
						M62429MenuPro(2);
           #else
						M62429MenuPro(5);	//	5 -> ok vol --	  2-> ehco --	   
		   #endif
						menumode=MENU_ECHO_MODE;	
					 #ifdef SUPPORT_MIC_ECHO_VM	
 		 					vm_write_api(VM_MIC_ECHO,&M62429Data[1]);					 
					 #endif
		   
           #if UI_ENABLE
						 UI_menu(MENU_VOL_MENU);
           #endif
					 break;  
#endif

#ifdef KOK_DETECT_USE_KEY
          case MSG_MIC_PRIORITY:
             g_kok_var.bKokKeyOpenFlag=!g_kok_var.bKokKeyOpenFlag;     
            #if LED_SHOW_MIC_PRIORITY
             #ifdef LED_MIC_PRIORITY_FLASH_FAST
              if(g_kok_var.bKokKeyOpenFlag){
                  bLedModeBake=show_led_mode[0];
				  setLedLight(LED_SHOW_MIC_PRIORITY,led_mode_flash_fast,0);
				  }
			  else
				  setLedLight(LED_SHOW_MIC_PRIORITY,bLedModeBake,0);
             #else
			 setLedLight(LED_SHOW_MIC_PRIORITY,g_kok_var.bKokKeyOpenFlag,0);
			 #endif
	     #elif defined SUPPORT_MIC_LED_SHOW_ONOFF
					UI_menu(MENU_MIC_ONOFF); 
            #endif
             break;
#endif
#ifdef LED_ONOFF_CONTROL_WITH_KEY
				   case MSG_LED_ONOFF:
#if 1
					   if(bRgbMode)
					   bRgbMode=0;
					   else
					   bRgbMode=1;
					   bRgbIfRun=TRUE;
#else
					 bRgbIfRun=TRUE;
					 bRgbMode++;
					 if(bRgbMode>7){
						bRgbMode=0;
						//bRgbIfRun=FALSE;
					}
       #ifdef SUPPORT_BREATH_LIGHT
					  blightIfRunPwm=FALSE;
       #endif
					if(bRgbMode==7){//∆µ∆◊ƒ£ Ω
					   bRgbIfRun=TRUE;
          #ifdef SUPPORT_BREATH_LIGHT
						  blightIfRunPwm=TRUE;
          #endif
					}
#endif        
        #ifdef LED_SHOW_ONOFF
					UI_menu(MENU_ONOFF); 
		#endif
				   break;
#endif

#ifdef SUPPORT_VOICE_ONOFF
            case MSG_VOICE_ONOFF:				
		 	led7_var.bIfHaveVoice=!led7_var.bIfHaveVoice;				
		 #ifdef SUPPORT_MODE_VOICE_AND_NOTICE_ONOFF_MEM
 		 	vm_write_api(VM_SYS_EQ,&led7_var.bIfHaveVoice);
 		 #endif

              #ifdef LED_SHOW_ONOFF
				UI_menu(MENU_ONOFF); 
              #endif
			  
			   break;
#endif

#ifdef SUPPORT_SSM_VOICE
 #ifdef SUPPORT_CHANGE_VOICE_EN_CH
           case MSG_CHANGE_VOICE_EN_CH:
//		printf("--IsVoiceEnable--\n",IsVoiceEnable);
//		printf("--led7_var.bIfHaveVoice--\n",IsVoiceEnable);

			if(led7_var.bIfHaveVoice==0)	
				break;
			
			if(led7_var.bIfHaveVoice==1)
			{
				led7_var.bIfHaveVoice=2;
			}
			else if(led7_var.bIfHaveVoice==2)
			{
				led7_var.bIfHaveVoice=1;
			}			
				IsVoiceEnable=led7_var.bIfHaveVoice;

		 #ifdef SUPPORT_MODE_VOICE_AND_NOTICE_ONOFF_MEM
 		 	vm_write_api(VM_SYS_EQ,&IsVoiceEnable);
 		 #endif

              #ifdef LED_SHOW_ONOFF
				UI_menu(MENU_ONOFF); 
              #endif
			  
		   break;
#endif
#endif



#ifdef SUPPORT_STOP_REC_PP_IN_ONE_KEY

		case MSG_PP_STOP_REC:

//			  if(compare_task_name(FM_TASK_NAME)||compare_task_name(LINEIN_TASK_NAME)||compare_task_name("BtStackTask")||compare_task_name("RECTask"))
			  {		
			  
#if 1
		 		if((g_rec_ctl)&&(ENC_STOP != g_rec_ctl->enable))
				{	//recording,stop first
					if(compare_task_name(FM_TASK_NAME))
						os_taskq_post(FM_TASK_NAME, 1, MSG_REC_STOP);
					else if(compare_task_name(LINEIN_TASK_NAME))
						os_taskq_post(LINEIN_TASK_NAME, 1, MSG_REC_STOP);		                   		 
					else if(compare_task_name("RECTask"))
						{
						os_taskq_post("RECTask", 1, MSG_REC_START);
//				  	         os_taskq_post("MainTask", 1, MSG_ONE_KEY_START_REC);
						}
					os_time_dly(100);
					
			                if(file_operate_get_total_phydev())
					{
			                  bExitRecordModePlayLastRecordedFileFlag=TRUE;
			                  os_taskq_post("MainTask", 1, MSG_ONE_KEY_TO_MP3);                  
			                }
						
				}
				else
#endif					
				{
					if(compare_task_name(FM_TASK_NAME))
						os_taskq_post(FM_TASK_NAME, 1, MSG_FM_SCAN_ALL_INIT);
					else if(compare_task_name(LINEIN_TASK_NAME))
						os_taskq_post(LINEIN_TASK_NAME, 1, MSG_AUX_PAUSE);		                   		 
					else if(compare_task_name("MusicTask"))
						os_taskq_post("MusicTask", 1, MSG_MUSIC_PP);
				}

			  }
			  break;

#endif

#ifdef SUPPORT_ZY_4LED_RGB

            case MSG_LED_WHITE:
		if(led_rgb_mode==0)
			{
			if(led_mode<3)
				led_mode++;
			else
			   led_mode=0;
			}
                break;
				
            case MSG_LED_RGB:
		if(led_rgb_mode==0)
			{
			if(led_mode<3)
				led_mode++;
			else
			   led_mode=0;
			}
		else
		{
			if(rgb_mode<6)
				rgb_mode++;
			else
			      rgb_mode=0;
		}
                break;
				
            case MSG_LED_RGB_SWTICH:
				
			if(led_rgb_mode==0)
				{
					led_rgb_mode=1;
					rgb_mode=0;
				}
			else
				   led_rgb_mode=0;
						
                break;

#endif  

 #ifdef power_on_wait_power_key_down
 #ifdef support_io_power_on_off
           case MSG_POWER_OFF:

		 #ifdef  support_power_off_tone
		 	os_taskq_post_msg(keymsg_task_name, 1, MSG_VOICE_POWER_OFF);                
		 #else			
		 	dac_mute(1,1);
			 #if defined(PA_ENABLE)
			 	pa_mute();
			 #endif
			 	power_on_flag=0;
			 #ifdef support_msg_light_key
			 	light_mode_mark=0;
			 #endif
		 
		 	Set_power_on_off_io_is_out();
		 	Set_power_on_off_io_is_LOW();
		 	delay_2ms(10);
		 #endif
		 
		break;
#endif
#endif

#ifdef support_reset_vol	

			case MSG_RESET_VOL:
			 	dac_var.cur_sys_vol_l=30;
			 	dac_var.cur_sys_vol_r = dac_var.cur_sys_vol_l;
			 
			 	if(dac_var.bMute)/*mute◊¥Ã¨œ¬£¨º”ºı“Ù¡øΩ‚mute*/
			 	{
				 	dac_mute(0,1);
					 #if PA_EN
					 	pa_mute();
					 #endif
					 #ifdef SUPPORT_MUTE_FLASH
					 	if(b_muteFlag)
						{
						 	b_muteFlag=FALSE;
						 	LED_FLASH_CHAR=0;
						 	LED_FLASH_ICON=0;
				 		}
					 #endif
				 
					 #if LED_SHOW_MUTE				   
					 	if(compare_task_name("BtStackTask")||compare_task_name("MusicTask"))
					 	setLedLight(LED_SHOW_MUTE,led_mode_flash_slow,0);
					 	else				 
					 	setLedLight(LED_SHOW_MUTE,led_mode_on,0);
					 #endif
			 	}
			 
			 #ifdef line_user_dac_L
			 	if(workmode==LINE_WORK_MODE)
			 	set_sys_vol(2, dac_var.cur_sys_vol_r, FADE_OFF);
			 	else
			 #elif defined(line_user_dac_R)
			 	if(workmode==LINE_WORK_MODE)		 
			 	set_sys_vol(dac_var.cur_sys_vol_l, 2, FADE_OFF);
			 	else		 
			 #endif 
			 
			 	set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);
		                #ifndef support_vm_mode_bass_treb_echo
	 
			 	if(!is_phone_active())
			 	{
			 	vm_cache_write(VM_SYS_VOL,&dac_var.cur_sys_vol_l,2);
			 	}
			  #endif
			 #ifdef SUPPORT_MUSIC_STOP
			 	bPause_state=0;
			 #endif
			 
			 	UI_menu(MENU_MAIN_VOL);

			 
			 #ifdef  SUPPORT_ZY_SA_VOICE				
			 #ifndef SUPPORT_ONLY_MODE_VOICE
		 	os_taskq_post_msg(keymsg_task_name, 1, MSG_VOICE_VOLUME_PLUS);                
			 #endif	
			 #endif	
		
			break;
#endif


            case MSG_HALF_SECOND:

				
                // puts(" Main_H ");
                break;

            case SYS_EVNET_DEV_BEGIN_MOUNT:
                if(compare_task_name("MusicTask"))
                {
                   os_taskq_post_event((char *)"MusicTask", 1, SYS_EVNET_DEV_BEGIN_MOUNT);
                }
                break;
            case SYS_EVENT_DEV_MOUNT_ERR:
                if(compare_task_name("MusicTask")||compare_task_name("FMRadioTask"))
                {
                   os_taskq_post_event((char *)curr_task->name, 1, SYS_EVENT_DEV_MOUNT_ERR);
                }
                break;
			default:
				break;
		}
		memset(msg,0,sizeof(msg));
	}
}




int main_task_init()
{
    u32 err;

    err = os_task_create(TaskMain,
                   (void*)0,
                   TaskMainPrio,
                   10
#if OS_TIME_SLICE_EN > 0
                   ,1
#endif
                   ,MAIN_TASK_NAME
                  );

    if(OS_NO_ERR == err)
    {
      #if KEY_IO_EN
	    key_msg_register(MAIN_TASK_NAME, main_ad_table, main_io_table, main_ir_table, NULL);
	 #elif LED_KEY_MAX
	 #if KEY_AD_EN
	        key_msg_register(MAIN_TASK_NAME, main_led_table,main_ad_table, NULL, main_ir_table, NULL);	 
	 #else
        key_msg_register(MAIN_TASK_NAME, main_ad_table, NULL, main_ir_table, NULL);
	 #endif   
      #else
        key_msg_register(MAIN_TASK_NAME, main_ad_table, NULL, main_ir_table, NULL);
      #endif
    }

	return 0;
}

 #ifdef KOK_DETECT_AUTO_VOL_SET		
 
void vol_auto_inc(void)
{
//        // printf("1111111111  auto_vol_sw - = %d\n",auto_vol_sw);
//        // printf("1111111111  dac_var.cur_sys_vol_l - = %d\n",dac_var.cur_sys_vol_l);
	static bool store_vol_sw;

	if(store_vol_sw!=auto_vol_sw)
	{
		if((auto_vol_sw==1)&&(dac_var.cur_sys_vol_l >AUTO_VOL_SET_DEC))
		{
			dac_var.cur_sys_vol_l=AUTO_VOL_SET_DEC;
			dac_var.cur_sys_vol_r=dac_var.cur_sys_vol_l;
	                set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);
		      if(!is_phone_active())
	                {
	                    vm_cache_write(VM_SYS_VOL,&dac_var.cur_sys_vol_l,2);	
	                }	
		}
	}
	
	 if((auto_vol_sw==0)&&(dac_var.cur_sys_vol_l <store_vol))
	  {
		dac_var.cur_sys_vol_l++;
		
		dac_var.cur_sys_vol_r=dac_var.cur_sys_vol_l;
		 #if 0//(LED_SHOW_VOL_MAX==32)	
		 	bVolMaxChangeToSmallVolMax=dac_var.cur_sys_vol_l+2;
		 #endif
	 		 if(workmode==LINE_WORK_MODE)			 
	 		 	DAA_CON2 |= (BIT(14)|BIT(15));//bypassøÿ÷∆’˝œ‡∑¥œ‡ // BTI14◊Û…˘µ¿ bit15”“…˘µ¿                		 

                set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);
	 		 if(workmode==LINE_WORK_MODE)			 
	 		 	DAA_CON2 |= (BIT(14)|BIT(15));//bypassøÿ÷∆’˝œ‡∑¥œ‡ // BTI14◊Û…˘µ¿ bit15”“…˘µ¿                

		 #if (LED_SHOW_VOL_MAX!=32)						
                UI_menu(MENU_MAIN_VOL);
		#endif

                if(dac_var.cur_sys_vol_l ==store_vol)
                {
                    vm_cache_write(VM_SYS_VOL,&dac_var.cur_sys_vol_l,2);	
                }		   
	}
	 
	store_vol_sw=auto_vol_sw;

}
 
#endif




 #ifdef SUPPORT_OUT_POWER_CONTROL		
u8 out_power_max_val;
u8 power_on_timer;
 
void out_power_control(void)
{
static bool cnt_sw;
	if(power_on_timer>0)
		return;
	
		OUT_POWER_DET_IO_IS_IN();
	
		if((OUT_POWER_DET_READ())&&(cnt_sw==0))
		{
		//	printf("------OUT_POWER_DET_READ--------\n");
		
			if(dac_var.cur_sys_vol_l>VOL_OUT_POWER-2)	
			{
			//	printf("------(dac_var.cur_sys_vol_l>VOL_OUT_POWER-2)------\n");			
				cnt_sw=1;
				dac_var.cur_sys_vol_l=22;
				bVolMaxChangeToSmallVolMax=32;
				out_power_max_val=22;
				store_vol=dac_var.cur_sys_vol_l;				
				dac_var.cur_sys_vol_r=dac_var.cur_sys_vol_l;
		                set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);
			}
		}
		else if((!(OUT_POWER_DET_READ()))&&(cnt_sw==1))
		{
			cnt_sw=0;
			dac_var.cur_sys_vol_l=30;
			bVolMaxChangeToSmallVolMax=32;
			out_power_max_val=30;
			store_vol=dac_var.cur_sys_vol_l;				
			dac_var.cur_sys_vol_r=dac_var.cur_sys_vol_l;
	                set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);
						
		}

}
 
#endif

#ifdef SUPPORT_USE_ENCODE_AS_MODE_CHANGE	
void encode_change_workmode_control(void)
{

		printf("------encode_change_workmode_control--------\n");

		switch(bMulitWorkmode)
		{
			case MUSIC_WORK_MODE:
		                  os_taskq_post("MainTask", 1, MSG_ONE_KEY_TO_MP3);                  
			break;		
			case LINE_WORK_MODE:
		                  os_taskq_post("MainTask", 1, MSG_ONE_KEY_TO_AUX);                  
			break;				
			case AC3_WORK_MODE:
		                  os_taskq_post("MainTask", 1, MSG_ONE_KEY_TO_AC3);                  
			break;		
			case DVD_WORK_MODE:
		                  os_taskq_post("MainTask", 1, MSG_ONE_KEY_TO_DVD);                  
			break;		
			case CD_WORK_MODE:
		                  os_taskq_post("MainTask", 1, MSG_ONE_KEY_TO_CD);                  
			break;		
			case RADIO_WORK_MODE:
		                  os_taskq_post("MainTask", 1, MSG_ONE_KEY_TO_RADIO);                  
			break;		
			case BT_WORK_MODE:
		                  os_taskq_post("MainTask", 1, MSG_ONE_KEY_TO_BT);                  
			break;				
			}
	
}
#endif

