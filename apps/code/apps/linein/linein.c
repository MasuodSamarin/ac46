#include "app_cfg.h"
#include "os_api.h"
#include "os_cfg.h"
#include "error.h"
#include "system_cfg.h"
#include "msg.h"
#include "task_manage.h"
#include "linein_key.h"
#include "linein.h"
#include "dac_api.h"
#include "play_sel.h"
#include "key.h"
#include "led.h"
#include "dac_api.h"
#include "dev_linein.h"
#include "ui_api.h"
#include "ladc.h"
#include "linein_prompt.h"
#include "led7_drv.h"
#include "vm_api.h"
#ifdef SUPPORT_PT2313
#include "pt2313.h"
#endif

#include "record.h"
#include "encode.h"
#if defined(line_user_dac_R)
extern u8 tone_mute;
#endif

extern void *malloc_fun(void *ptr,u32 len,char *info);
extern void free_fun(void **ptr);

#ifdef support_line_pause
extern bool   aux_pause_mark;
#endif
#ifdef DURING_FM_EXITING_TASK_NOT_RESPOND_KEY_MSG
extern u8 bExitFMStateCnt;
#endif
#ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE
extern u8 bModeOfAuxContained;
#endif
#ifdef ONLY_POWER_ON_MUTE
extern u8 bPowerOnMuteCnt;
#endif
#if LED_SHOW_VOL_MAX
extern u8 bVolMaxChangeToSmallVolMax;
#endif
#ifdef POWER_ON_KEEP_MUTE_FOR_4S
extern u8 bAmpPowerOnMuteCnt;
#endif
#ifdef support_send_ir_code // MP5 OFF
u8 show_val; // ac3 led7 flash  problem 
#endif
#ifdef support_fm_aux_rec_voice
bool IsAuxRecBegin;					
#endif				

/*----------------------------------------------------------------------------*/
/**@brief  LINE_TWO_IN_ONE_OUT(AUX两输入一输出设置)
   @param  无
   @return 无
   @note   void dac_amux_two_in_one_on(void)
*/
/*----------------------------------------------------------------------------*/
void amux_two_in_one_on(void)
{
//    LR_2_L(0);
//    LR_2_R(0);
//
//    PORTC_DIE &= ~(BIT(14)|BIT(15));
//    PORTC_DIR |= BIT(14)|BIT(15);
//
//    LIN2_CHANNL_L_EN(0);
//    LIN2_CHANNL_R_EN(0);
}

/*----------------------------------------------------------------------------*/
/**@brief  LINE_ONE_IN_TWO_OUT(AUX两输入一输出关闭)
   @param  无
   @return 无
   @note   void dac_amux_two_in_one_off(void)
*/
/*----------------------------------------------------------------------------*/
void amux_two_in_one_off(void)
{
//    LIN2_CHANNL_L_EN(0);
//    LIN2_CHANNL_R_EN(0);
}

void amux_two_in_one_set(void)
{
    dac_amux_two_in_one_set(amux_two_in_one_on,amux_two_in_one_off);
}

/*----------------------------------------------------------------------------*/
/**@brief  LINE_ONE_IN_TWO_OUT(AUX一输入两输出设置)
   @param  无
   @return 无
   @note   void dac_amux_one_in_two_set(void)
*/
/*----------------------------------------------------------------------------*/
void amux_one_in_two_on(void)
{
#if S10_MODE
    LR_2_L(1);
    LR_2_R(1);
    PORTC_DIE &= ~BIT(15);
    PORTC_DIR |= BIT(15);
    LIN2_CHANNL_R_EN(1);//PC15
#elif defined(AUX_INPUT_SEL_PC13)
	PORTC_DIE &= ~BIT(13);
	PORTC_DIR |= BIT(13);
	LIN1_CHANNL_R_EN(1);//PC13
#else
	LR_2_L(1);
    LR_2_R(1);
    PORTC_DIE &= ~BIT(14);
    PORTC_DIR |= BIT(14);
    LIN2_CHANNL_L_EN(1);//PC14
#endif
}


/*----------------------------------------------------------------------------*/
/**@brief  LINE_ONE_IN_TWO_OUT(AUX一输入两输出关闭)
   @param  无
   @return 无
   @note   void dac_amux_one_in_two_off(void)
*/
/*----------------------------------------------------------------------------*/
void amux_one_in_two_off(void)
{
#if S10_MODE
    	LIN2_CHANNL_R_EN(0);
#elif defined(AUX_INPUT_SEL_PC13)
	LIN1_CHANNL_L_EN(0);
#else
	LIN2_CHANNL_L_EN(0);
#endif
}

void amux_one_in_two_set(void)
{
    dac_amux_one_in_two_set(amux_one_in_two_on, amux_one_in_two_off);
}

/*----------------------------------------------------------------------------*/
/**@brief  AUX DAC通道选择，关闭
   @param  无
   @return 无
   @note   void aux_dac_channel_off(void)
*/
/*----------------------------------------------------------------------------*/
void aux_dac_channel_off(void)
{
#if S10_MODE
    dac_channel_off(LINE_ONE_IN_TWO_OUT, FADE_OFF);
#ifdef DAC_VDD_EN
    LDO1_EN(1);
#else
    LDO2_EN(1);
#endif/*DAC_VDD_EN*/
    os_time_dly(2);
    TRIM_EN(0);
#elif defined(line_user_dac_L)||defined(line_user_dac_R)
 
       dac_channel_off(DAC_DIGITAL_AVOL, FADE_OFF);
       AMUX_G(0); 
       HP_L_EN(1); 
       HP_R_EN(1); 
       LR_2_L(0); 
       LR_2_R(0);
       set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);
	   
#elif defined(AUX_INPUT_SEL_PC13)
	dac_channel_off(LINE_ONE_IN_TWO_OUT, FADE_OFF);
	#ifdef DAC_VDD_EN
	LDO1_EN(1);
	#else
	LDO2_EN(1);
	#endif/*DAC_VDD_EN*/
	os_time_dly(2);
	TRIM_EN(0);
#elif defined(line_user_PC14)
    dac_channel_off(LINE_ONE_IN_TWO_OUT, FADE_OFF);	
#else
    dac_channel_off(LINEIN_CHANNEL, FADE_OFF);
    os_time_dly(2);
    //TRIM_EN(0);
#endif/*S10_MODE*/
    dac_mute(0,1);
}
/*----------------------------------------------------------------------------*/
/**@brief  AUX DAC通道选择，开启
   @param  无
   @return 无
   @note   void aux_dac_channel_on(void)
*/
/*----------------------------------------------------------------------------*/
void aux_dac_channel_on(void)
{
#if S10_MODE
    TRIM_EN(1);
    LDO1_EN(0);
    LDO2_EN(0);
    amux_one_in_two_set();
    dac_mute(1,1);
    dac_channel_on(LINE_ONE_IN_TWO_OUT, FADE_OFF);
    os_time_dly(3);
    dac_mute(0,1);
#elif defined(AUX_INPUT_SEL_PC13)
	amux_one_in_two_set();
	dac_mute(1,1);
	dac_channel_on(LINE_ONE_IN_TWO_OUT, FADE_OFF);
	os_time_dly(3);
	dac_mute(0,1);
#elif defined(line_user_PC14)
    amux_one_in_two_set();
    dac_mute(1,1);
    dac_channel_on(LINE_ONE_IN_TWO_OUT, FADE_OFF);
    os_time_dly(3);
    dac_mute(0,1);
	
#elif defined(line_user_dac_L)
        #if defined(PA_ENABLE) 
        	    pa_mute();
        #endif 
          dac_mute(1,1);
          dac_channel_on(DAC_DIGITAL_AVOL, FADE_OFF);
          os_time_dly(15);  //这个参数会影响到上电第一次进入line in的冲击声。可以根据样机调整
          dac_mute(0,1);
          
          AMUX_G(1); 
          HP_L_EN(0); 
          HP_R_EN(1); 
          LR_2_L(1); 
          LR_2_R(1); 
          LIN1_CHANNL_L_EN(0); 
          LIN1_CHANNL_R_EN(0);
          LIN0_CHANNL_L_EN(0); 
          LIN0_CHANNL_R_EN(0);
                  os_time_dly(15);  //这个参数会影响到上电第一次进入line in的冲击声。可以根据样机调整
                dac_mute(0,1);
#elif defined(line_user_dac_R)
                // puts("line_user_dac_R  11\n");

         #if defined(PA_ENABLE) 
         	    pa_mute();
         #endif 
         
	// puts("line_user_dac_R  22\n");
	dac_mute(1,1);
	dac_channel_on(DAC_DIGITAL_AVOL, FADE_OFF);
	os_time_dly(30);  //这个参数会影响到上电第一次进入line in的冲击声。可以根据样机调整
	dac_mute(0,1);
	// puts("line_user_dac_R  33\n");

	AMUX_G(1); 
	HP_L_EN(1); 
	HP_R_EN(0); 
	LR_2_L(1); 
	LR_2_R(1); 
	LIN1_CHANNL_L_EN(0); 
	LIN1_CHANNL_R_EN(0);
	LIN0_CHANNL_L_EN(0); 
	LIN0_CHANNL_R_EN(0);  
	os_time_dly(40);  //这个参数会影响到上电第一次进入line in的冲击声。可以根据样机调整
	dac_mute(0,1);
                       // puts("line_user_dac_R  44\n");
#elif defined SUPPORT_AUX_REC_OFF_DAC_OUT

    //TRIM_EN(1);
    dac_mute(1,1);
    dac_channel_on(LINEIN_CHANNEL, FADE_OFF);
     set_sys_vol(1, 1, FADE_OFF);	
//    os_time_dly(15);  //这个参数会影响到上电第一次进入line in的冲击声。可以根据样机调整
    dac_mute(0,1);
     dac_mute(1,1);	
   HP_L_EN(0); 
    HP_R_EN(0); 	
					 
#elif defined support_nop_show_nodi
    dac_mute(0,1);
  aux_dac_channel_off(); 
	
#else
    //TRIM_EN(1);
    dac_mute(1,1);
    dac_channel_on(LINEIN_CHANNEL, FADE_OFF);
    os_time_dly(15);  //这个参数会影响到上电第一次进入line in的冲击声。可以根据样机调整
    dac_mute(0,1);
#endif

	
    #ifdef line_user_dac_L
        set_sys_vol(2, dac_var.cur_sys_vol_r, FADE_OFF);
    #elif defined(line_user_dac_R)
        set_sys_vol(dac_var.cur_sys_vol_l, 2, FADE_OFF);
    #else     
         set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);
    #endif 
}



/*----------------------------------------------------------------------------*/
/**@brief  LINE IN模式提示音播放
   @param  无
   @return 无
   @note   void aux_tone_play(void)
*/
/*----------------------------------------------------------------------------*/
void aux_tone_play(void)
{
    tbool psel_enable = 0;
 #ifdef POWER_ON_KEEP_MUTE_FOR_4S
	 bAmpPowerOnMuteCnt=1;
 #endif

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
	 #ifdef SUPPORT_DOUBLE_VOICE
	 	if(IsVoiceEnable==1)
		            psel_p->file_number[0] = BPF_LINEIN_MP3;
		else if(IsVoiceEnable==2)
		            psel_p->file_number[0] = BPF_LINEIN_MP3_EN;	
	#elif defined support_ac3_voice
	 	if(bModeOfAuxContained==mode_ac3)
		            psel_p->file_number[0] = BPF_AC3_MP3;
		else
		            psel_p->file_number[0] = BPF_LINEIN_MP3;			
	#else
            #ifdef SUPPORT_VOICE_ONOFF
			  if(led7_var.bIfHaveVoice)
            #endif
            	{
                #ifdef SUPPORT_VOICE_ONOFF            	
			 #ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE            	
	 	 		if(bModeOfAuxContained==mode_mp3_nodevice)
	           		  	psel_p->file_number[0] = BPF_MUSIC_MP3;
	 			else			
			 #endif				
		  #endif				
          			  psel_p->file_number[0] = BPF_LINEIN_MP3;
            	}
	#endif
	
        }
        else
        {
            free_fun((void**)&psel_p);
        }
    }
    b_res = play_sel(LINEIN_TASK_NAME, 'A', psel_p);
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
void aux_info_init(void)
{

 #ifdef SUPPORT_PT2313
 	Pt2313_ChangSource(Aud_SwAUX);
 #endif


#if KEY_TONE_EN==0
 TRIM_EN(1); 
#endif
 
#ifdef support_sound_4052_control

	AC4052_IS_AUX();
#if defined sound_4052_io_mode_6 ||defined sound_4052_io_mode_5
	  	aux_dac_channel_on();
#endif
 #else
	   #ifndef LINE_IN_USE_PT2313
	  	aux_dac_channel_on();
	  #endif
#endif
	
#if (REC_EN==0)
   ladc_reg_init(ENC_DAC_CHANNEL,LADC_SR16000);   //获取能量要初始化用于采数
#endif

#ifndef suppport_aux_singe_no_swap
	DAA_CON2 |= (BIT(14)|BIT(15));//bypass控制正相反相 // BTI14左声道 bit15右声道
#endif


    SET_UI_MAIN(MENU_AUX_MAIN);
    UI_menu(MENU_AUX_MAIN);
}
#ifdef SUPPORT_MP3_IDEL_MODE_IN_LINEIN_MODE
void mp3IdleMode_init(void)
{
    aux_dac_channel_off();
    SET_UI_MAIN(MENU_MP3_IDLE_MAIN);
    UI_menu(MENU_MP3_IDLE_MAIN);

#ifdef support_sound_4052_control
	AC4052_IS_MP3();
#endif
}
#endif
#ifdef SUPPORT_AC3_MODE_IN_LINEIN_MODE
void AC3_mode_init(void)
{
	 
#if KEY_TONE_EN==0
 TRIM_EN(1); 
#endif

#ifdef support_ac3_dac_channle_aux2
    //TRIM_EN(1);
    dac_mute(1,1);
    dac_channel_on(DAC_AMUX2, FADE_OFF);
    os_time_dly(15);  //这个参数会影响到上电第一次进入line in的冲击声。可以根据样机调整
    dac_mute(0,1);
#elif defined support_ac3_dac_channle_aux0
    //TRIM_EN(1);
    dac_mute(1,1);
    dac_channel_on(DAC_AMUX0, FADE_OFF);
    os_time_dly(15);  //这个参数会影响到上电第一次进入line in的冲击声。可以根据样机调整
    dac_mute(0,1);
#ifndef suppport_aux_singe_no_swap
	{
		DAA_CON2 |= (BIT(14)|BIT(15));//bypass控制正相反相 // BTI14左声道 bit15右声道			 
	}			 
#endif	
#else
	  aux_dac_channel_off();
#endif

#ifdef SUPPORT_PT2313
	 Pt2313_ChangSource(Aud_SwCD);
#endif
#ifdef support_sound_4052_control
#if defined sound_4052_io_mode_7 ||defined sound_4052_io_mode_5
	AC4052_IS_AC3(); 
#endif
#endif


   SET_UI_MAIN(MENU_AC3_MAIN);
   UI_menu(MENU_AC3_MAIN);
}
#endif
#ifdef SUPPORT_CD_MODE_IN_LINEIN_MODE
void cd_mode_init(void)
{
  aux_dac_channel_off();
#ifdef SUPPORT_PT2313
	 Pt2313_ChangSource(Aud_SwCD);
#endif
#ifdef support_sound_4052_control
	AC4052_IS_CD(); 
#endif

   SET_UI_MAIN(MENU_CD_MAIN);
   UI_menu(MENU_CD_MAIN);
}
#endif
#ifdef SUPPORT_DVD_MODE_IN_LINEIN_MODE
void dvd_mode_init(void)
{
  aux_dac_channel_off();
#ifdef SUPPORT_PT2313
	 Pt2313_ChangSource(Aud_SwVcd);
#endif

#ifdef support_sound_4052_control
	AC4052_IS_DVD();
#endif

   SET_UI_MAIN(MENU_DVD_MAIN);
   UI_menu(MENU_DVD_MAIN);
}
#endif

/*----------------------------------------------------------------------------*/
/**@brief  LINE IN 任务
   @param  p：任务间参数传递指针
   @return 无
   @note   static void linein_task(void *p)
*/
/*----------------------------------------------------------------------------*/
static void linein_task(void *p)
{
	int msg[3];

    RECORD_OP_API * rec_linin_api = NULL;

	// aux_// puts("\n************************LINEIN TASK********************\n");
    #ifdef LED_SHOW_AUX
    	setLedLight(LED_SHOW_AUX,led_mode_on,0);
    #else
    	//led_fre_set(15);
    #endif

	
#if defined(AUX_DETECT_EN) && defined(support_line_unline_to_next_mode)   // muzhe add
    if(0 == aux_is_online()) //AUX离线
    {
        os_taskq_post("MainTask", 1, MSG_CHANGE_WORKMODE);
    }
    else
#endif
#if AUX_DGND_DETECT_EN  //IO是否接地检测要不LINEIN
   #ifdef AUX_DETECT_LOW_REMOVE
     #ifdef SUPPORT_MP3_IDEL_MODE_IN_LINEIN_MODE
	  if(!AUX_IN_CHECK && bModeOfAuxContained!=mode_mp3_nodevice)
     #else
      if(!AUX_IN_CHECK)
     #endif
   #else
     #ifdef SUPPORT_MP3_IDEL_MODE_IN_LINEIN_MODE
    	if(AUX_IN_CHECK && bModeOfAuxContained!=mode_mp3_nodevice)
     #else
     if(AUX_IN_CHECK)
     #endif
   #endif
		   os_taskq_post("MainTask", 1, MSG_CHANGE_WORKMODE);
   else
#endif
    {
	 #ifdef SUPPORT_ZY_SA_VOICE
	 
	 	if(IsVoiceEnable)
		     {
		     	aux_tone_play(); //line in提示音播放
		     }
		     else
		     {
		     	os_taskq_post(LINEIN_TASK_NAME, 1, SYS_EVENT_PLAY_SEL_END);
		     }
		 
	#elif defined support_off_voice
	     	os_taskq_post(LINEIN_TASK_NAME, 1, SYS_EVENT_PLAY_SEL_END);
	#elif defined support_off_line_aux_voice
	     	os_taskq_post(LINEIN_TASK_NAME, 1, SYS_EVENT_PLAY_SEL_END);	
        #elif defined SUPPORT_MP3_IDEL_MODE_IN_LINEIN_MODE 

		 #ifdef  support_only_use_bt_mp3	
		 	os_taskq_post(LINEIN_TASK_NAME, 1, SYS_EVENT_PLAY_SEL_END);		 
		 #else			
	 		 #if defined(PA_EN)
				#ifdef ONLY_POWER_ON_MUTE			 
	 		 		pa_umute1();
				#endif
	 		 #endif
		 	aux_tone_play(); //line in提示音播放	
		 #endif				
	 	     		
	 #else
	 
		 #ifdef ONLY_POWER_ON_MUTE
		   #ifndef LINE_INIT_MUTE_IO
		   if(bPowerOnMuteCnt){
		   bPowerOnMuteCnt=0;
		 	  pa_umute1();
		   }
		   #endif
		 #endif
	 
	     aux_tone_play(); //line in提示音播放
	  #endif
    }
	while(1)
	{
		os_taskq_pend(0, ARRAY_SIZE(msg), msg);
       #ifdef SUPPORT_MP3_IDEL_MODE_IN_LINEIN_MODE
		   if(bModeOfAuxContained==mode_mp3_nodevice){
		   if(msg[0]==MSG_AUX_PAUSE)continue;
		   }
      #endif
		switch(msg[0])
		{
			case SYS_EVENT_DEL_TASK:
				
				if (os_task_del_req_name(OS_TASK_SELF) == OS_TASK_DEL_REQ)
				{
				
				   #ifndef EXIT_AUX_TASK_NOT_SHOW_LOAD
				   	 UI_menu(MENU_WAIT);
				   #endif
				    // aux_// puts("AUX_SYS_EVENT_DEL_TASK\n");

                   		    exit_rec_api(&rec_linin_api); //停止录音和释放资源

				    disable_ladc(ENC_DAC_CHANNEL);
				    aux_dac_channel_off();
				    play_sel_stop(); //关闭提示音
				    os_task_del_res_name(OS_TASK_SELF);
				}
				break;
				
 		#ifdef ZY_5028_MP3_AUX_FM_BT	
	            case MSG_AUX_VOICE_PLAY: //提示音结束
	//            printf("111111111MSG_AUX_VOICE_PLAY 111111111\n");
	//	     		aux_tone_play(); //line in提示音播放
			 #if defined(PA_EN)
			 	pa_umute1();
			 #endif	
	 			linein_prompt_play(BPF_LINEIN_MP3);			    		    				 	    		    		    					 					 	    			
				os_time_dly(124);
 		#endif
		
 		#ifdef support_ac3_voice	
	            case MSG_AC3_VOICE_PLAY: //提示音结束
	            	            
	//            printf("111111111MSG_AUX_VOICE_PLAY 111111111\n");
	//	     		aux_tone_play(); //line in提示音播放
	 			linein_prompt_play(BPF_AC3_MP3);	
	 		
//			aux_tone_play2();
			os_time_dly(99);


			 #ifdef support_send_ir_code
				send_end=0;
			 #endif				 

			break;
 		#endif
	
            case SYS_EVENT_PLAY_SEL_END: //提示音结束
		 #ifdef support_aux_plus_in_power_on_mute_moment            
		   #ifdef ONLY_POWER_ON_MUTE		 
		  	 bPowerOnMuteCnt=5;  
		 	 pa_mute1();
		   #endif			
		 #endif
		 
		// printf("-----bModeOfAuxContained------ %d\n",bModeOfAuxContained);
                // aux_// puts("AUX_SYS_EVENT_PLAY_SEL_END\n");
                play_sel_stop(); //关闭提示音
                // aux_// puts("AUX_play_tone_end\n");
                linein_prompt_stopped = 1;
		 #ifdef support_fm_aux_rec_voice
		 	 if(IsAuxRecBegin)
		 	{
			 	// 	IsFmSearchEnd = 0;
			 	IsAuxRecBegin = 0;
			 	os_taskq_post_msg(LINEIN_TASK_NAME, 1, MSG_REC_START);
		 	}					
		 #endif				
                os_taskq_post_msg(LINEIN_TASK_NAME, 1, MSG_AUX_INIT); //触发AUX模块初始化
                break;

            case MSG_AUX_INIT:

		 #ifdef SUPPORT_WOKRMODE
	    		 #ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE
	    		 	if( bModeOfAuxContained==mode_ac3)
	    		 		workmode=AC3_WORK_MODE;
	    		 	else
	    		 #endif
		 		workmode=LINE_WORK_MODE;
	 		 #ifdef SUPPORT_MODE_VM
	 		        vm_write_api(VM_SYS_EQ,&workmode);
	 		 #endif
		 #endif

                  puts("-------MSG_AUX_INIT-------\n");
//		printf("bModeOfAuxContained 1111 %d \n",bModeOfAuxContained)		 ;

               #ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE
               switch(bModeOfAuxContained)
			{
                 case mode_mp3_nodevice:
			 #ifdef SUPPORT_USE_ENCODE_AS_MODE_CHANGE	
			 	bMulitWorkmode=MUSIC_WORK_MODE;
			 #endif
				 	
                     #ifdef SUPPORT_MP3_IDEL_MODE_IN_LINEIN_MODE
					 mp3IdleMode_init();
					 #endif
	                 break;
					 
                 case mode_aux:

			workmode=LINE_WORK_MODE;				 	
			aux_info_init();
                 break;
				 
	             case mode_ac3:
			
			 #ifdef SUPPORT_USE_ENCODE_AS_MODE_CHANGE	
			 	bMulitWorkmode=AC3_WORK_MODE;
			 #endif

				 
	                 #ifdef SUPPORT_AC3_MODE_IN_LINEIN_MODE
		                 AC3_mode_init();
			  #if 0//def support_send_ir_code // MP5 ON
						 #if 0//def support_send_ir_code
				 	send_timer=0;
				 	vol_key_sw=0;		
				 	send_timer=0;
				 	vol_key_sw=0;		
				 
				 #endif				 
	  
			  	IRSendInital(MP5_PANEL_ON);
			 	os_time_dly(5);		
			  	IRSendInital(MP5_PANEL_ON);	
			 	os_time_dly(5);		
			  	IRSendInital(MP5_PANEL_ON);					
		
				#endif

	  	  		 #if 0//def support_send_ir_code
	  	  		 	hw_IRsend_Pin_Init();
	  	  		 #endif
				 
	    		 #ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE
    		 		workmode=AC3_WORK_MODE;
	    		 #endif
									 
	                 #endif
	                 break;
					 
                 case mode_cd:
			 #ifdef SUPPORT_USE_ENCODE_AS_MODE_CHANGE	
			 	bMulitWorkmode=CD_WORK_MODE;
			 #endif
				 	
                    #ifdef SUPPORT_CD_MODE_IN_LINEIN_MODE
	                 cd_mode_init();
                    #endif
	                 break;
                 case mode_dvd:
			 #ifdef SUPPORT_USE_ENCODE_AS_MODE_CHANGE	
			 	bMulitWorkmode=DVD_WORK_MODE;
			 #endif
				 	
                    #ifdef SUPPORT_DVD_MODE_IN_LINEIN_MODE
	                 dvd_mode_init();
                    #endif
	                 break;
                 default:
					 aux_info_init();
                     break;
               }
               #else
                aux_info_init();
			   
               #endif

		 #ifdef  SUPPORT_ONE_KEY_AUX_REC	,	
		 	 if(bOneKeyAuxRecFlag)
		 	 	{		 	 	
                  			  dac_mute(0,1);	 	 	
					bOneKeyAuxRecFlag=0;
					os_taskq_post(LINEIN_TASK_NAME, 1, MSG_REC_START);		 
		 	 	}
			else		 	
		 #endif
			   			   
                break;

#ifdef support_line_pause
           case MSG_AUX_PAUSE:
		   	
#ifdef TEST_IR_CODE_MACHINE

		ir_sys_sw=!ir_sys_sw;
                UI_menu(MENU_AUX_MAIN);

	break;
#endif

                if(get_mute_status())
                {
                  #ifdef SUPPORT_PT2313
                   PT2313Mute(FALSE);
                  #endif
                    dac_mute(0,1);
                    #ifdef LED_SHOW_AUX
					//setLedLight(LED_SHOW_AUX,led_mode_flash_fast,0);
                    #else
                    //led_fre_set(15);
                    #endif
					
			 #ifndef suppport_aux_singe_no_swap
			 	{
			 		DAA_CON2 |= (BIT(14)|BIT(15));//bypass控制正相反相 // BTI14左声道 bit15右声道			 
			 	}			 
			 #endif
					
                 #ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE
                  switch(bModeOfAuxContained){
                     case mode_aux:
					  SET_UI_MAIN(MENU_AUX_MAIN);
					  UI_menu(MENU_AUX_MAIN);
                     break;
                     case mode_ac3:
#ifdef SUPPORT_AC3_MODE_IN_LINEIN_MODE
					 SET_UI_MAIN(MENU_AC3_MAIN);
					 UI_menu(MENU_AC3_MAIN);
#endif
                     break;
#ifdef SUPPORT_CD_MODE_IN_LINEIN_MODE

                     case mode_cd:
						 SET_UI_MAIN(MENU_CD_MAIN);
						 UI_menu(MENU_CD_MAIN);
	                     break;
#endif
#ifdef SUPPORT_DVD_MODE_IN_LINEIN_MODE

                     case mode_dvd:
						 SET_UI_MAIN(MENU_DVD_MAIN);
						 UI_menu(MENU_DVD_MAIN);
	                     break;
#endif
                     default:
						 SET_UI_MAIN(MENU_AUX_MAIN);
						 UI_menu(MENU_AUX_MAIN);
                      break;
                  }
                 #else
	             SET_UI_MAIN(MENU_AUX_MAIN);
                   UI_menu(MENU_AUX_MAIN);
                 #endif
#ifdef support_line_pause
				 
		     aux_pause_mark=0;
#endif
         #ifndef LED_LINEIN_PAUSE_NOT_SHOW_ICON_PLAY_PAUSE
              #if LED_PAUSE
	  	       LED_STATUS&=~LED_PAUSE;
              #endif
         #endif
		 
                }
                else
                {
                
		 	SET_UI_MAIN(MENU_AUX_PAUSE);
		 	UI_menu(MENU_AUX_PAUSE);
             //                  UI_menu(MENU_MAIN);
                UI_menu(MENU_HALF_SEC_REFRESH);
                    dac_mute(1,1);
                      #ifdef LED_SHOW_AUX
					 //setLedLight(LED_SHOW_AUX,led_mode_on,0);
                      #else
					 //led_fre_set(0);
                      #endif
#ifdef support_line_pause
					  
	  	     aux_pause_mark=1;
#endif
        #ifndef LED_LINEIN_PAUSE_NOT_SHOW_ICON_PLAY_PAUSE
	  	     #if LED_PAUSE
	  	       LED_STATUS|=LED_PAUSE;
	  	     #endif
       #endif

       #ifdef SUPPORT_PT2313
       	PT2313Mute(TRUE);
       #endif
                }

	   	break;
#else
           case MSG_AUX_PAUSE:
#endif
            case MSG_AUX_MUTE:

	 #if defined SUPPORT_AUX_REC_OFF_DAC_OUT
	 	break;
	 #endif
				
                if(get_mute_status())
                {
                    // aux_// puts("MSG_AUX_UNMUTE\n");
                    dac_mute(0,1);
                    //led_fre_set(15);
             #ifdef support_line_pause
                aux_pause_mark=0;
             #endif
            #ifdef PA_ENABLE
            	   pa_umute();
            #endif

                }
                else
                {
                    // aux_// puts("MSG_AUX_MUTE\n");
                    dac_mute(1,1);
            #ifdef PA_ENABLE
            	   pa_mute();
            #endif
                    //led_fre_set(0);
             #ifdef support_line_pause
                aux_pause_mark=1;
             #endif

                }
                break;

            case MSG_LOW_POWER:
                // puts("aux_low_power\n");
                linein_prompt_play(BPF_LOW_POWER_MP3);
                break;

     #ifdef  support_power_off_tone
     	case MSG_VOICE_POWER_OFF:
		 power_on_flag=0;
		 power_off_timer=3;		 
		 linein_prompt_play(BPF_POWER_OFF_MP3);
		
        	break;		 
     #endif	
	 
#ifdef SUPPORT_VOICE_ONOFF_VOICE	

 		case MSG_AUX_VOICE_ONOFF:
			
			  if(led7_var.bIfHaveVoice==1)		
			  	led7_var.bIfHaveVoice=0;
			  else 
			  	led7_var.bIfHaveVoice=1;
			  
				if(led7_var.bIfHaveVoice)
				{
				 #ifdef LED_SHOW_ONOFF
				 	UI_menu(MENU_ONOFF);
				 #endif
		 		 #ifdef support_voice_onoff_mem
		 		 	vm_write_api(VM_SYS_EQ,&led7_var.bIfHaveVoice);
		 		 #endif
					linein_prompt_play(BPF_VOICE_ON_MP3);
				}
				else
				{
				 #ifdef LED_SHOW_ONOFF
				 	UI_menu(MENU_ONOFF);
				 #endif
		 		 #ifdef support_voice_onoff_mem
		 		 	vm_write_api(VM_SYS_EQ,&led7_var.bIfHaveVoice);
		 		 #endif
				 
					 linein_prompt_play(BPF_VOICE_OFF_MP3);
				}
						
				 

			break; 
#endif

#ifdef SUPPORT_ZY_SA_VOICE

#ifdef support_fm_aux_rec_voice
		case MSG_AUX_REC_START:	
		if(IsVoiceEnable)
        	{
        		IsAuxRecBegin = 1;
	        		linein_prompt_play(BPF_REC_MP3);		
        	}
        	else
        	{
				os_taskq_post_msg(LINEIN_TASK_NAME, 1, MSG_REC_START);
        	}			
		break;
#endif


		case MSG_AUX_VOICE_SWITCH:
			 #if defined SUPPORT_DOUBLE_VOICE

				 #ifdef SUPPORT_SSM_VOICE

					 if(IsVoiceEnable)
					 {
					 	voice_save=IsVoiceEnable;
					 	IsVoiceEnable = 0;
		 				 #ifdef LED_SHOW_ONOFF
		 				 	UI_menu(MENU_ONOFF);
		 				 #endif
		 		 		 #ifdef support_voice_onoff_mem
		 		 		 	vm_write_api(VM_SYS_EQ,&IsVoiceEnable);
		 		 		 #endif
		 				 if(voice_save==1)
		 					linein_prompt_play(BPF_VOICE_OFF_MP3);
						 else
		 					linein_prompt_play(BPF_VOICE_OFF_MP3_EN);						 	
					 }
					 else
					 {
					 	IsVoiceEnable=voice_save;
						
		 				 #ifdef LED_SHOW_ONOFF
		 				 	UI_menu(MENU_ONOFF);
		 				 #endif
		 		 		 #ifdef support_voice_onoff_mem
		 		 		 	vm_write_api(VM_SYS_EQ,&IsVoiceEnable);
		 		 		 #endif
		 				 if(IsVoiceEnable==1)
		 					linein_prompt_play(BPF_VOICE_ON_MP3);
						 else
		 					linein_prompt_play(BPF_VOICE_ON_MP3_EN);						 			 				 
					 }
					 
					 	led7_var.bIfHaveVoice=IsVoiceEnable;		
						
				#else
						
					if(IsVoiceEnable==0)
					{
						IsVoiceEnable = 1;
				 		 #ifdef support_voice_onoff_mem
				 		 	vm_write_api(VM_SYS_EQ,&IsVoiceEnable);
				 		 #endif
						
					 	led7_var.bIfHaveVoice=IsVoiceEnable;
					 #ifdef LED_SHOW_ONOFF
					 	UI_menu(MENU_ONOFF); 
					 #endif								
					}
					else 
					if(IsVoiceEnable==1)
					{
						IsVoiceEnable = 2;
				 		 #ifdef support_voice_onoff_mem
				 		 	vm_write_api(VM_SYS_EQ,&IsVoiceEnable);
				 		 #endif
						
					 	led7_var.bIfHaveVoice=IsVoiceEnable;
					 #ifdef LED_SHOW_ONOFF
					 	UI_menu(MENU_ONOFF); 
					 #endif							
					}
					else if(IsVoiceEnable==2)
					{
		 						IsVoiceEnable = 0;
				 		 #ifdef support_voice_onoff_mem
				 		 	vm_write_api(VM_SYS_EQ,&IsVoiceEnable);
				 		 #endif
						
					 	led7_var.bIfHaveVoice=IsVoiceEnable;
					 #ifdef LED_SHOW_ONOFF
					 	UI_menu(MENU_ONOFF); 
					 #endif								
					}
				#endif
			
			#else	
			
				if(IsVoiceEnable)
				{
					IsVoiceEnable = 0;
				 	led7_var.bIfHaveVoice=IsVoiceEnable;
				 #ifdef LED_SHOW_ONOFF
				 	UI_menu(MENU_ONOFF);
				 #endif
		 		 #ifdef support_voice_onoff_mem
		 		 	vm_write_api(VM_SYS_EQ,&IsVoiceEnable);
		 		 #endif
				 
					linein_prompt_play(BPF_VOICE_OFF_MP3);
				}
				else
				{
					IsVoiceEnable = 1;
					 	led7_var.bIfHaveVoice=IsVoiceEnable;
					 #ifdef LED_SHOW_ONOFF
					 	UI_menu(MENU_ONOFF);
					 #endif
		 		 #ifdef support_voice_onoff_mem
		 		 	vm_write_api(VM_SYS_EQ,&IsVoiceEnable);
		 		 #endif
					 linein_prompt_play(BPF_VOICE_ON_MP3);
				}
				
			#endif
			
			break;
 #if  !defined SUPPORT_ONLY_MODE_VOICE

		case MSG_VOICE_MUTE:

			if(IsVoiceEnable)
			{
  			 #ifdef SUPPORT_DOUBLE_VOICE
				if(IsVoiceEnable==2)
		    			linein_prompt_play(BPF_MUTE_MP3_EN);
				else
			 #endif    		    		    				 			 
	    			linein_prompt_play(BPF_MUTE_MP3);			    		    				 	    		    		    	
			}
			break;

		case MSG_VOICE_VOLUME_PLUS:

			 if(IsVoiceEnable)
			 {
  			 #ifdef SUPPORT_DOUBLE_VOICE
				if(IsVoiceEnable==2)
		    			linein_prompt_play(BPF_VL_INC_MP3_EN);
				else
			 #endif    
			 	{
					#ifdef SUPPORT_SMM_SA_VOICE			 	
			 	 	{
						if(dac_var.cur_sys_vol_l ==30) 			
			    				linein_prompt_play(BPF_VL_MAX_MP3);			    		    				 	    		    		    					 
						else		 	 	
			    				linein_prompt_play(BPF_VL_INC_MP3);			    		    				 	    		    		    					 
			 	 	}
					#else
					
			    				linein_prompt_play(BPF_VL_INC_MP3);			    		    				 	    		    		    					 
					#endif
			 	}
			 }
			 break;

		case MSG_VOICE_VOLUME_MINUS:

			 if(IsVoiceEnable)
			 {
  			 #ifdef SUPPORT_DOUBLE_VOICE
				if(IsVoiceEnable==2)
		    			linein_prompt_play(BPF_VL_DEC_MP3_EN);
				else
			 #endif    		    		    				 			 
	    			linein_prompt_play(BPF_VL_DEC_MP3);			    		    				 	    		    		    					 					 
			 }
			 break;

		case MSG_MAX_VOICE:

			if(IsVoiceEnable)
			{
  			 #ifdef SUPPORT_DOUBLE_VOICE
				if(IsVoiceEnable==2)
		    			linein_prompt_play(BPF_VL_MAX_MP3_EN);
				else
			 #endif    		    		    				 			 
	    			linein_prompt_play(BPF_VL_MAX_MP3);			    		    				 	    		    		    					 					 	    			
			}
			break;
	#endif
#endif


#ifdef SUPPORT_KEY_6_VOICE
            case MSG_VOICE_YESE:
	    			linein_prompt_play(BPF_VL_MAX_YESE);	
		break;
            case MSG_VOICE_END:
	    			linein_prompt_play(BPF_VL_MAX_END);	
		break;
            case MSG_VOICE_APPLAUD:
	    			linein_prompt_play(BPF_VL_MAX_APPLAUD);	
		break;
            case MSG_VOICE_GUN:
	    			linein_prompt_play(BPF_VL_MAX_GUN);	
		break;
            case MSG_VOICE_ZXC:
	    			linein_prompt_play(BPF_VL_MAX_ZXC);	
		break;
           case MSG_VOICE_BEST_PARTNER:
	    			linein_prompt_play(BPF_VL_MAX_BEST_PARTNER);	
		break;
	
#endif

		
            case MSG_HALF_SECOND:

		 #ifdef SUPPORT_MUSIC_REC_USE_AUX_REC
		 
		 if(bMusicToAuxRecFlag)
		 {
		  	if(bMusicToAuxRecFlag>1)
				bMusicToAuxRecFlag--;
			else if(bMusicToAuxRecFlag==1)
			{
				bMusicToAuxRecFlag=0;
				 os_taskq_post("LineinTask", 1 , MSG_REC_START);
			}
				
		 }
		 #endif


//			printf("111111 send_timer %x \n",send_timer);	
//			printf("111111 send_val %x \n",send_val);

	 	      #ifdef  line_user_dac_R
			 	 	if(tone_mute>1)			
						tone_mute--;
					else if(tone_mute==1)
		 	 	 		{	 	 
		 		 	 		tone_mute=0;
							pa_umute();
		 	 	 		 	dac_mute(0,1);	 					 
		 	 				break;	 
		 	 	 		}
	 	 	 #endif	


	 	      #ifdef  support_power_off_tone
			  if(power_on_flag==0)
			  	{
			 	 	if(power_off_timer>1)			
						power_off_timer--;
					else if(power_off_timer==1)
		 	 	 		{	 	 
		 		 	 		power_off_timer=0;
		 	 	 		      #ifdef LED_SHOW_MP3
		 	 	 		 	   setLedLight(LED_SHOW_MP3,led_mode_off,0);
		 	 	 		      #endif
		 
		 	 	 		 	Set_power_on_off_io_is_out();
		 	 	 		 	Set_power_on_off_io_is_LOW();
		 	 	 	 	 			
		 	 	 		 	dac_mute(1,1);
		 	 	 			 #if defined(PA_ENABLE)
		 	 	 			 	pa_mute();
		 	 	 			 #endif
		 					 
		 	 				break;	 
		 	 	 		}
			  	}
	 	 	 #endif			

			 #ifdef support_aux_energy_det
			 	aux_auto_mute();
			 #endif

			 #ifdef support_io_det_mute
			 	#if defined support_off_voice
			 			if(bPowerOnMuteCnt==0)
			 				{
			 				 	if(auto_mute_sw)
			 				 	{
			 				 		pa_mute1();
			 				 	}
			 				 	else 
			 				 		pa_umute1();			 			 
			 			    }				
			 	#else		 
			 			if(bPowerOnMuteCnt==0)
			 				{
			 				 	if((auto_mute_sw)&&(bt_automute_sw==0))
			 				 	{
			 				 		pa_mute1();
			 				 	}
			 				 	else 
			 				 		pa_umute1();
			 
			 					if(bt_automute_sw>1)
			 					 	 bt_automute_sw--;  // bt 报语音 时不mute
			 					else if(bt_automute_sw==1)
			 					 	 bt_automute_sw=0;  // bt 报语音 时不mute
			 
			 			}
				 #endif			
			 #endif

                //// aux_// puts(" Aux_H ");
           #if 0//REC_EN
				  if((g_rec_ctl)&&(ENC_STOP != g_rec_ctl->enable)){
				  led7_show_rec_time();
				  }
				  else
           #endif
                {
			 #ifdef support_send_ir_code // MP5 OFF
		 		if(show_val>1)
				 show_val--;
		 		else if(show_val==1)
	 			{
		 			show_val=0;
	 		                UI_menu(MENU_MAIN);
	 		                UI_menu(MENU_HALF_SEC_REFRESH);
				}				
			#else
	 			{
	 		                UI_menu(MENU_MAIN);
	 		                UI_menu(MENU_HALF_SEC_REFRESH);
				}					
			 #endif

                
			            #ifndef LED_LINEIN_PAUSE_NOT_SHOW_ICON_PLAY_PAUSE
			            #ifdef support_line_pause
							if(aux_pause_mark){
			                  #if LED_PAUSE
							  LED_STATUS|=LED_PAUSE;
			                  #endif
			                  }
			                else{
			                  #if LED_PAUSE
								LED_STATUS&=~LED_PAUSE;
			                  #endif
			                  }
			            #endif
			            #endif
              }
                break;

            default:
               #if REC_EN
                rec_msg_del_api(&rec_linin_api, msg);
               #endif
                break;
		}
	}
}


/*----------------------------------------------------------------------------*/
/**@brief  LINE IN 任务创建
   @param  priv：任务间参数传递指针
   @return 无
   @note   static void linein_task_init(void *priv)
*/
/*----------------------------------------------------------------------------*/
static void linein_task_init(void *priv)
{
    u32 err;
    #if 0//def LINEIN_INIT_SHOW_AUX_INTIME
#ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE
	 switch(bModeOfAuxContained){
		case mode_mp3_nodevice:
		 SET_UI_MAIN(MENU_MP3_IDLE_MAIN);
		 UI_menu(MENU_MP3_IDLE_MAIN);
		break;
		case mode_aux:
		 SET_UI_MAIN(MENU_AUX_MAIN);
		 UI_menu(MENU_AUX_MAIN);
		break;		
		case mode_ac3:
		#ifdef SUPPORT_AC3_MODE_IN_LINEIN_MODE
		SET_UI_MAIN(MENU_AC3_MAIN);
		UI_menu(MENU_AC3_MAIN);
		#endif
		break;
		case mode_cd:
			SET_UI_MAIN(MENU_CD_MAIN);
			UI_menu(MENU_CD_MAIN);
			break;
		case mode_dvd:
			SET_UI_MAIN(MENU_DVD_MAIN);
			UI_menu(MENU_DVD_MAIN);
			break;
		default:
			SET_UI_MAIN(MENU_AUX_MAIN);
			UI_menu(MENU_AUX_MAIN);
		 break;
	 }
#else
    {
    SET_UI_MAIN(MENU_AUX_MAIN);
    UI_menu(MENU_AUX_MAIN);
    }
    #endif
#endif
#if 0//def ONLY_POWER_ON_MUTE
  #ifndef LINE_INIT_MUTE_IO
  if(bPowerOnMuteCnt){
  bPowerOnMuteCnt=0;
	//  pa_umute1();
  }
  #endif
#endif
#ifdef DURING_FM_EXITING_TASK_NOT_RESPOND_KEY_MSG
			// if(bExitFMStateCnt)break;
			 bExitFMStateCnt=2;
#endif
	err = os_task_create(linein_task,
			(void*)0,
			TaskLineinPrio,
			10
#if OS_TIME_SLICE_EN > 0
			,1
#endif
			,LINEIN_TASK_NAME);

    if(OS_NO_ERR == err)
    {
       #if KEY_IO_EN
	   key_msg_register(LINEIN_TASK_NAME, linein_ad_table, linein_io_table, linein_ir_table, NULL);
	 #elif LED_KEY_MAX
	 #if KEY_AD_EN
	 	key_msg_register("LineinTask",linein_led_table,linein_ad_table,NULL,linein_ir_table,NULL);
	 #else
        key_msg_register(LINEIN_TASK_NAME, linein_ad_table, NULL, linein_ir_table, NULL);
	 #endif   
	   
      #else
        key_msg_register(LINEIN_TASK_NAME, linein_ad_table, NULL, linein_ir_table, NULL);
       #endif
    }
#if MP3_VOL_MAX||FM_VOL_MAX
	if(bVolMaxChangeToSmallVolMax>=0)
	dac_var.cur_sys_vol_l=bVolMaxChangeToSmallVolMax;
	dac_var.cur_sys_vol_r = dac_var.cur_sys_vol_l;
#if defined(PA_EN)
	pa_umute();
#endif
	set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);
#elif defined(AUX_VOL_DOWN)
	if(dac_var.cur_sys_vol_l>(SYS_VOL_MAX-AUX_VOL_DOWN))
		dac_var.cur_sys_vol_l=SYS_VOL_MAX-AUX_VOL_DOWN;
		dac_var.cur_sys_vol_r = dac_var.cur_sys_vol_l;
	set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);
#if defined(PA_EN)
	pa_umute();
#endif
#elif defined(support_mode_change_vol_min_to_min)
	if(dac_var.cur_sys_vol_l<support_mode_change_vol_min_to_min)
	dac_var.cur_sys_vol_l=support_mode_change_vol_min_to_min;
	dac_var.cur_sys_vol_r = dac_var.cur_sys_vol_l;
#if defined(PA_EN)
	pa_umute();
#endif
	set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);
#endif


#ifdef support_amP_ab_d
  Set_amp_ab_d_out() ;
   Set_AMP_IS_D();
#endif

#ifdef SUPPORT_FLASH_CHAR
  if(LED_FLASH_CHAR)
  LED_FLASH_CHAR=0;
#endif
#if LED_SHOW_BT
 setLedLight(LED_SHOW_BT,led_mode_off,0);
#endif

#ifdef TF2025A_CONTROL_PB10_ALONG
	TF2025A_SET_PB9_26PIN(1);
#endif
#ifdef KOK_DETECT_AUTO_VOL_SET
	 store_vol= dac_var.cur_sys_vol_l;
#endif
#ifdef support_aux_energy_det
	   aux_mode_sw=1;
#endif

#ifdef SUPPORT_WOKRMODE
#ifndef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE
	workmode=LINE_WORK_MODE;
#endif
#endif

#ifdef support_io_det_mute
	 bt_automute_sw=5;  // bt 报语音 时不mute
#endif
#if defined(LED_ID_JW2781)

led7_var.bEqCircleIfPlay=TRUE;
#endif
#ifdef OFF_AUX_SHOW_ERRO_MESSAGE
    SET_UI_MAIN(MENU_AUX_MAIN);
    UI_menu(MENU_AUX_MAIN);
#endif	

}


/*----------------------------------------------------------------------------*/
/**@brief  LINE IN 任务删除退出
   @param  无
   @return 无
   @note   static void linein_task_exit(void)
*/
/*----------------------------------------------------------------------------*/
static void linein_task_exit(void)
{


	if (os_task_del_req(LINEIN_TASK_NAME) != OS_TASK_NOT_EXIST)
	{
		os_taskq_post_event(LINEIN_TASK_NAME, 1, SYS_EVENT_DEL_TASK);
		do{
			OSTimeDly(1);
		} while(os_task_del_req(LINEIN_TASK_NAME) != OS_TASK_NOT_EXIST);
		// aux_// puts("del_linein_task: succ\n");
	}

 #if 0//def support_send_ir_code // MP5 OFF
//				 	 if(bModeOfAuxContained==mode_ac3)
// off panel  

	IRSendInital(MP5_PANEL_OFF);
	
	os_time_dly(25); 
 #endif


      #ifdef SUPPORT_MP3_IDLE_IN_LINEIN_MODE
	   if(bMp3IdleMode)bMp3IdleMode=FALSE;
      #endif
       #ifdef SUPPORT_MUTE_FLASH
	   b_muteFlag=FALSE;
      #endif

#ifdef support_power_off_tone
#ifdef support_io_det_mute
	pa_umute1();
#endif    	  
#endif    	  


#ifdef support_sound_4052_control
	AC4052_IS_MP3();
#endif

#if 0//def support_send_ir_code
	hw_IRsend_Pin_in_Init();
#endif

 #if KEY_TONE_EN==0
 TRIM_EN(0); 
#endif

#if defined SUPPORT_AUX_REC_OFF_DAC_OUT
    HP_L_EN(1); 
    HP_R_EN(1); 	
#endif
}


/*----------------------------------------------------------------------------*/
/**@brief  LINE IN 任务信息
   @note   const struct task_info linein_task_info
*/
/*----------------------------------------------------------------------------*/
TASK_REGISTER(linein_task_info) = {
	.name = LINEIN_TASK_NAME,
	.init = linein_task_init,
	.exit = linein_task_exit,
};
