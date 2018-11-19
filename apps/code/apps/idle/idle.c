#include "app_cfg.h"
#include "os_api.h"
#include "os_cfg.h"
#include "error.h"
#include "system_cfg.h"
#include "msg.h"
#include "task_manage.h"
#include "idle_key.h"
#include "idle.h"
#include "dac_api.h"
#include "play_sel.h"
#include "key.h"
#include "low_power.h"
#include "led.h"
#include "led7_drv.h"
#include "UI_api.h"
#ifdef SUPPORT_PT2313
#include "pt2313.h"
#endif

extern void *malloc_fun(void *ptr,u32 len,char *info);
extern void free_fun(void **ptr);

#ifdef LED_SHOW_POWER_OFF_STRING
u8 show_standby_info_cnt=0;
#endif
#ifdef ONLY_POWER_ON_MUTE
extern u8 bPowerOnMuteCnt;
#endif
/*----------------------------------------------------------------------------*/
/**@brief  IDLE模式提示音播放
   @param  无
   @return 无
   @note   void idle_tone_play(void)
*/
/*----------------------------------------------------------------------------*/
void idle_tone_play(void)
{
#ifdef POWER_ON_WELCOME_VOICE_PLAYED_IN_IDLE_MODE
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
#ifdef SUPPORT_VOICE_ONOFF
			 if(led7_var.bIfHaveVoice)
#endif
            psel_p->file_number[0] = BPF_WELCOME_MP3;
        }
        else
        {
            free_fun((void**)&psel_p);
        }
    }
    b_res = play_sel(IDLE_TASK_NAME, 'A', psel_p);
    if(psel_enable)
    {
        free_fun((void**)&psel_p->file_number);
        free_fun((void**)&psel_p);
    }
    if(!b_res)
    {
        psel_enable = 0;
    }
#endif    
}

/*----------------------------------------------------------------------------*/
/**@brief  Idle 任务
   @param  p：任务间参数传递指针
   @return 无
   @note   static void idle_task(void *p)
*/
/*----------------------------------------------------------------------------*/
static void idle_task(void *p)
{
	int msg[3];

	idle_puts("\n************************Idle TASK********************\n");
   #if LED_SHOW_BT
	setLedLight(LED_SHOW_BT,led_mode_off,0);
   #endif
	#if LED_SHOW_IDLE
	#ifdef LED_IDLE_MODE_ON_ALL_THE_TIME
	setLedLight(LED_SHOW_IDLE,led_mode_on,0);
	#else
	setLedLight(LED_SHOW_IDLE,led_mode_off,0);
	#endif
	#else
	//led_fre_set(15);
    #endif
#ifdef ONLY_POWER_ON_MUTE
	   bPowerOnMuteCnt=0;	
       pa_mute1();
#endif
#ifdef SUPPORT_PT2313
	Pt2313_ChangSource(Aud_SwNoting);
#endif
#ifdef POWER_ON_WELCOME_VOICE_PLAYED_IN_IDLE_MODE
    if(led7_var.bIfPlayWelcomeVoice){    
	pa_umute();
    idle_tone_play(); //Idle提示音播放
    }
#endif    

#if defined SUPPORT_ZY_SA_VOICE&& !defined SUPPORT_ONLY_MODE_VOICE
  if(IsVoiceEnable)
    {
    	idle_tone_play(); //Idle提示音播放
    }
    else
    {
    	os_taskq_post(IDLE_TASK_NAME, 1, SYS_EVENT_PLAY_SEL_END);
    }
#else
    os_taskq_post_msg(IDLE_TASK_NAME, 1, MSG_IDLE_MODE); //触发AUX模块初始化
#endif    
	while(1)
	{
		os_taskq_pend(0, ARRAY_SIZE(msg), msg);
		switch(msg[0])
		{
			case SYS_EVENT_DEL_TASK:
				if (os_task_del_req_name(OS_TASK_SELF) == OS_TASK_DEL_REQ)
				{
				    idle_puts("IDLE_SYS_EVENT_DEL_TASK\n");				    
		                   #ifdef POWER_ON_WELCOME_VOICE_PLAYED_IN_IDLE_MODE                   
						   if(led7_var.bIfPlayWelcomeVoice)    
						    play_sel_stop(); //关闭提示音
		 		     #endif
					os_task_del_res_name(OS_TASK_SELF);
				}
				break;

            case SYS_EVENT_PLAY_SEL_END: //提示音结束                
              #ifdef POWER_ON_WELCOME_VOICE_PLAYED_IN_IDLE_MODE   
			  if(led7_var.bIfPlayWelcomeVoice){	  
				  play_sel_stop(); //关闭提示音
		                os_taskq_post_msg("MainTask", 1, MSG_STANBY_KEY);              
			  //led7_var.bIfPlayWelcomeVoice=0;  
              }
              #else
                idle_puts("IDLE_SYS_EVENT_PLAY_SEL_END\n");
                //play_sel_stop(); //关闭提示音
                idle_puts("IDEL_play_tone_end\n");
                os_taskq_post_msg(IDLE_TASK_NAME, 1, MSG_IDLE_MODE);
              #endif
                break;

            case MSG_IDLE_MODE:
                puts("MSG_IDLE_MODE\n");
                //low_power_mode(WAKEUP_13,WAKEUP_DOWN_EDGE);
                break;

            case MSG_IDLE_CTL:
                puts("MSG_IDLE_CTL\n");
                os_taskq_post_msg("MainTask", 1, MSG_EXIT_IDLE_TASK);
                break;

#ifdef SUPPORT_ZY_4LED_RGB

            case MSG_IDLE_LED_WHITE:
		if(led_rgb_mode==0)
			{
			if(led_mode<3)
				led_mode++;
			else
			   led_mode=0;
			}
                break;
				
            case MSG_IDLE_LED_RGB:
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
				
            case MSG_IDLE_LED_RGB_SWTICH:
				
			if(led_rgb_mode==0)
				{
					led_rgb_mode=1;
					rgb_mode=0;
				}
			else
				   led_rgb_mode=0;
						
                break;

#endif  

            case MSG_HALF_SECOND:
                idle_puts(" Idle_H ");
               #ifdef LED_SHOW_POWER_OFF_STRING                  
				  if(show_standby_info_cnt){
				  show_standby_info_cnt--;	
				   UI_menu_api(MENU_STANDBY);
		 #ifndef 	SUPPORT_POWER_OFF_2POINT_FLASH
		     if(show_standby_info_cnt==0)
			{
				 #if UI_ENABLE
				 	led7_show_null();
				 #endif
				 #if defined(SUPPORT_LCD_4COM_9SEG_MODE)||defined(SUPPORT_LCD_5COM_8SEG_MODE)
				 	LCD_SEG_CLOSE();
				 #endif				  
             		 }
                 #endif

                }                  
              #endif
                break;

			default:
				break;
		}
	}
}


/*----------------------------------------------------------------------------*/
/**@brief  IDLE 任务创建
   @param  priv：任务间参数传递指针
   @return 无
   @note   static void idle_task_init(void *priv)
*/
/*----------------------------------------------------------------------------*/
static void idle_task_init(void *priv)
{
    u32 err;
	err = os_task_create(idle_task,
			(void*)0,
			TaskIdlePrio,
			10
#if OS_TIME_SLICE_EN > 0
			,1
#endif
			,IDLE_TASK_NAME);

    if(OS_NO_ERR == err)
    {
        #if KEY_IO_EN
        key_msg_register(IDLE_TASK_NAME, idle_ad_table, idle_io_table, idle_ir_table, NULL);
	 #elif LED_KEY_MAX
	 #if KEY_AD_EN
	 	key_msg_register("IdleTask",idle_led_table,idle_ad_table,NULL,idle_ir_table,NULL);
	 #else
        key_msg_register(IDLE_TASK_NAME, idle_ad_table, NULL, idle_ir_table, NULL);
	 #endif   
        #else
        key_msg_register(IDLE_TASK_NAME, idle_ad_table, NULL, idle_ir_table, NULL);
        #endif
    }
 #ifdef AMP_IC_WORK_ONFF
#ifndef support_idle_mode_only_mute_amp 
	  Set_amp_power_out();		   
	  Set_AMP_OFF(); 				
#endif	  
#endif
  #ifdef IDLE_MODE_IO_MUTE
    #ifdef PA_EN
    #ifdef ONLY_POWER_ON_MUTE
	pa_mute1();
    #else
     pa_mute();
    #endif
    #endif
  #endif

#if defined(LED_ID_JW2781)
   led7_var.bEqCircleIfPlay=FALSE;
#endif
  
#ifdef SUPPORT_FLASH_CHAR
  if(LED_FLASH_CHAR)
  LED_FLASH_CHAR=0;
 #endif
 #ifdef LED_SHOW_POWER_OFF_STRING
    show_standby_info_cnt=5;    
    UI_menu_api(MENU_STANDBY);
 #else
    #if UI_ENABLE
    led7_show_null();
    #endif
#if defined(SUPPORT_LCD_4COM_9SEG_MODE)||defined(SUPPORT_LCD_5COM_8SEG_MODE)
    LCD_SEG_CLOSE();
    #endif
 #endif
#if LED_SHOW_IDLE
#ifdef LED_IDLE_MODE_ON_ALL_THE_TIME
 setLedLight(LED_SHOW_IDLE,led_mode_on,0);
#else
 setLedLight(LED_SHOW_IDLE,led_mode_off,0);
#endif 
#endif
}


/*----------------------------------------------------------------------------*/
/**@brief  IDLE 任务删除退出
   @param  无
   @return 无
   @note   static void idle_task_exit(void)
*/
/*----------------------------------------------------------------------------*/
static void idle_task_exit(void)
{
	if (os_task_del_req(IDLE_TASK_NAME) != OS_TASK_NOT_EXIST)
	{
		os_taskq_post_event(IDLE_TASK_NAME, 1, SYS_EVENT_DEL_TASK);
		do{
			OSTimeDly(1);
		} while(os_task_del_req(IDLE_TASK_NAME) != OS_TASK_NOT_EXIST);
		idle_puts("del_idle_task: succ\n");
		#if UI_ENABLE
		UI_menu_api(MENU_POWER_UP);
		#endif
       #ifdef LED_SHOW_POWER_OFF_STRING				  
		  show_standby_info_cnt=0;
	   #endif
 #ifdef AMP_IC_WORK_ONFF
		 Set_amp_power_out();		  
		 Set_AMP_ON();				   
#endif
#ifdef ONLY_POWER_ON_MUTE
		  bPowerOnMuteCnt=6;  
#ifndef  support_standby_on_delay_umute_amp
		  pa_umute1();
#endif
#endif
	}
}


/*----------------------------------------------------------------------------*/
/**@brief  IDLE 任务信息
   @note   const struct task_info idle_task_info
*/
/*----------------------------------------------------------------------------*/
TASK_REGISTER(idle_task_info) = {
	.name = IDLE_TASK_NAME,
	.init = idle_task_init,
	.exit = idle_task_exit,
};
