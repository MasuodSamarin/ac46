#include "app_cfg.h"
#include "os_api.h"
#include "os_cfg.h"
#include "error.h"
#include "system_cfg.h"
#include "msg.h"
#include "task_manage.h"
#include "dac_api.h"
#include "fm_radio.h"
#include "fm_api.h"
#include "fm_key.h"
#include "fm_define.h"
#include "fmrx_driver.h"
#include "fm_resample.h"
#include "play_sel.h"
#include "key.h"
#include "led.h"
#include "fm_prompt.h"
#include "led7_drv.h"
#include "vm_api.h"
#ifdef SUPPORT_PT2313
#include "pt2313.h"
#endif

#include "record.h"
#include "encode.h"

#if FM_RADIO_EN

#if (REC_EN==0)
    #define FM_CHANGE_SYS_CLK       ///>FM运行时，系统时钟设置为38.4Mhz,录音模式96Mhz
#endif

extern void *malloc_fun(void *ptr,u32 len,char *info);
extern void free_fun(void **ptr);

FM_MODE_VAR *fm_mode_var;       ///>FM状态结构体
FM_INFO *fm_info;               ///>FM存台信息
#ifdef FM_SCAN_STOP_LIGHT_ON
bool bFmScanStop=FALSE;
#endif
#ifdef EXIT_BLUE_MODE_DISCONNECT_VOICE
extern bool	prev_task_is_blue;
#endif
#if IR_NUM_INPUT_EN
extern u8 ir_num_timeout_cnt;
#endif
#ifdef SUPPORT_FM_PAUSE
bool bFmPauseFlag=FALSE;
#endif
#ifdef DURING_FM_EXITING_TASK_NOT_RESPOND_KEY_MSG
extern u8 bExitFMStateCnt;
#endif
#if LED_SHOW_VOL_MAX
extern u8 bVolMaxChangeToSmallVolMax;
#endif
#ifdef  SUPPORT_ZY_SA_VOICE
u8 IsFmSearchBegin;
u8 IsFmSearchEnd;  
#ifdef support_fm_aux_rec_voice
bool IsFmRecBegin;  
#endif
#endif
/*----------------------------------------------------------------------------*/
/**@brief  FM提示音
   @param  无
   @return 无
   @note   void fm_tone_play(void)，播放结束后会发出SYS_EVENT_PLAY_SEL_END 消息
*/
/*----------------------------------------------------------------------------*/
void fm_tone_play(void)
{
    tbool psel_enable = 0;

    _PLAY_SEL_PARA *psel_p = NULL;
    psel_p  = (_PLAY_SEL_PARA *)malloc_fun(psel_p ,sizeof(_PLAY_SEL_PARA),0);
    tbool b_res;
    if(NULL != psel_p )
    {
        psel_p->file_number = (u32 *)malloc_fun(psel_p->file_number,sizeof(psel_p->file_number[0]),0);
        if(NULL != psel_p->file_number)
        {
            psel_enable = 1;
            psel_p->max_file_number = 1;
            psel_p->delay = 1;
            psel_p->rpt_time = 1;
#ifdef EXIT_BLUE_MODE_DISCONNECT_VOICE
			if(prev_task_is_blue){
			psel_p->file_number[0] = BPF_DISCONNECT_MP3;
			prev_task_is_blue=FALSE;
			}else
#endif
	  #ifdef SUPPORT_DOUBLE_VOICE
	 		    if(IsVoiceEnable==1)
	 		    {
 			         psel_p->file_number[0] = BPF_RADIO_MP3;		    
	 		    }
			 else	
	 		    if(IsVoiceEnable==2)
	 		    {
 			         psel_p->file_number[0] = BPF_RADIO_MP3_EN;		    
	 		    } 	
	 #else
	 
	 	 #ifdef SUPPORT_VOICE_ONOFF
	 		if(led7_var.bIfHaveVoice)
	 	 #endif
	             psel_p->file_number[0] = BPF_RADIO_MP3;
	 #endif
        }
        else
        {
            free_fun((void**)&psel_p);
        }
    }
    b_res = play_sel(FM_TASK_NAME, 'A', psel_p);
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
/*----------------------------------------------------------------------------*/
/**@brief  FM录音过程消息过滤函数
   @param  msg；接收到的消息
   @return 1：不需要过滤，0：过滤
   @note   static bool fm_msg_filter(int msg)
   @note   FM不同工作状态时，部分消息不能进行处理，如还没初始化不能搜台等操作
*/
/*----------------------------------------------------------------------------*/
#if REC_EN
static bool fm_rec_msg_filter(RECORD_OP_API * rec_fm_api, int msg)
{
    if(rec_fm_api)
    {
        if(rec_fm_api->rec_ctl->enable != ENC_STOP)//正在录音，不响应以下消息
        {
            if((msg == MSG_FM_SCAN_ALL_INIT)
            ||(msg == MSG_FM_SCAN_ALL)
             ||(msg == MSG_FM_SEARCHING)
           ||(msg == MSG_FM_SCAN_ALL_UP)
            ||(msg == MSG_FM_SCAN_ALL_DOWN))
            {
                return 0;
            }
        }
    }
    return 1;
}
#endif

/*----------------------------------------------------------------------------*/
/**@brief  FM消息过滤函数
   @param  msg；接收到的消息
   @return 1：不需要过滤，0：过滤
   @note   static bool fm_msg_filter(int msg)
   @note   FM不同工作状态时，部分消息不能进行处理，如还没初始化不能搜台等操作
*/
/*----------------------------------------------------------------------------*/
static bool fm_msg_filter(int msg)
{
    ///FM 任何情况，都必须响应SYS_EVENT_DEL_TASK消息


    if(fm_mode_var->scan_mode == FM_UNACTIVE)///FM 还没初始化完成(正在播放提示音)，不响应其他消息
    {
        if((msg == SYS_EVENT_DEL_TASK)
            ||(msg == SYS_EVENT_PLAY_SEL_END)
            ||(msg == MSG_ENCODE_ERR)
            ||(msg == SYS_EVENT_DEV_OFFLINE))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if(fm_mode_var->scan_mode >= FM_SCAN_BUSY)    ///FM正在搜台，只响应部分按键
    {
        if((msg == SYS_EVENT_DEL_TASK)||\
            (msg == SYS_EVENT_PLAY_SEL_END)||\
            (msg == MSG_FM_SCAN_ALL)||\
             (msg == MSG_FM_STOP_SCAN_ALL)||\
           (msg == MSG_FM_SCAN_ALL_INIT)||\
           (msg == MSG_FM_SEARCHING)||\		
            (msg == SYS_EVENT_SYSCLK_NOTFIT_DEVMOUNT)||\
            (msg == SYS_EVENT_DEV_MOUNT_ERR)||\
            (msg == MSG_ENCODE_ERR)||\
            (msg == SYS_EVENT_DEV_OFFLINE))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else            ///一般情况下，不进行过滤
    {
        return 1;
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  FM模式主线程
   @param  p：NULL
   @return NULL
   @note   static void fm_radio_task(void *p)
*/
/*----------------------------------------------------------------------------*/
RECORD_OP_API * rec_fm_api = NULL;
static void fm_radio_task(void *p)
{
    int msg[3];
    u8 scan_counter=0;
    u32 res;

    // // fm_puts("\n***********************RADIO TASK********************\n");
#if FM_DGND_DETECT_EN  //IO是否接地检测要不radio
       #ifdef FM_DETECT_LOW_REMOVE
	   if(!FM_IN_CHECK)
	   #else
	   if(FM_IN_CHECK)
	   #endif
	          {
               #ifdef DURING_FM_EXITING_TASK_NOT_RESPOND_KEY_MSG
				bExitFMStateCnt=0;
   				//if(compare_task_name(FM_TASK_NAME)&& !bExitFMStateCnt)bExitFMStateCnt=4;														
               #endif
			   os_taskq_post("MainTask", 1, MSG_CHANGE_WORKMODE);
			  // task_switch(FM_NEXT_MODE, 0,SWITCH_SPEC_TASK);	
			  }
			   else			   
#endif
#ifdef support_jump_fm_mode
     os_taskq_post("MainTask", 1, MSG_CHANGE_WORKMODE);
#endif
{
#ifdef LED_SHOW_FM
	setLedLight(LED_SHOW_FM,led_mode_on,0);
#else
    //led_fre_set(15);
#endif
    fm_open();          //变量初始化，变采样设置

#ifdef  SUPPORT_ZY_SA_VOICE
    if(IsVoiceEnable)
    {
    	fm_tone_play();     //FM提示音播放
    }
    else
    {
		os_taskq_post(FM_TASK_NAME, 1, SYS_EVENT_PLAY_SEL_END);
    }
#elif defined support_off_line_aux_voice
		os_taskq_post(FM_TASK_NAME, 1, SYS_EVENT_PLAY_SEL_END);	
#elif defined support_off_voice
		os_taskq_post(FM_TASK_NAME, 1, SYS_EVENT_PLAY_SEL_END);
	
#else	
    fm_tone_play();     //FM提示音播放
#endif    

    fm_prompt_stopped = 1;
}
    while(1)
    {
        os_taskq_pend(0, ARRAY_SIZE(msg), msg);

        if(!fm_msg_filter(msg[0]))//根据FM状态，过滤消息
            continue;
#if REC_EN
        if(!fm_rec_msg_filter(rec_fm_api, msg[0]))//根据FM录音状态，过滤消息
            continue;
#endif
        switch(msg[0])
        {

        case SYS_EVENT_DEL_TASK:
            // fm_puts("get_SYS_EVENT_DEL_TASK\n");
            if (os_task_del_req_name(OS_TASK_SELF) == OS_TASK_DEL_REQ)
            {
                fm_init_flag = 0;
                play_sel_stop(); //关闭提示音
                SET_UI_UNLOCK();
                #ifdef LED_SWITCH_FM2AUX_SHOW_LINE
                UI_menu(MENU_AUX_MAIN);  
                #elif defined(LED_FM_EXIT_NOT_SHOW_LOAD)
                
                #else                
                UI_menu(MENU_WAIT);
                #endif
                exit_rec_api(&rec_fm_api); //停止录音和释放资源

                dac_set_samplerate(24000,1);
                dac_channel_off(RADIO_CHANNEL, FADE_OFF);
                fm_rev_powerdown();

                if (os_task_del_req(FM_DAC_TASK_NAME) != OS_TASK_NOT_EXIST)
                {
                    os_taskq_post_event(FM_DAC_TASK_NAME, 1, SYS_EVENT_DEL_TASK);
                    do
                    {
                        // fm_puts("fm_wating-02\n");
                        OSTimeDly(1);
                    }
                    while(os_task_del_req(FM_DAC_TASK_NAME) != OS_TASK_NOT_EXIST);
                    // fm_puts("clos_fm_src_succ-02\n");
                }
                // fm_puts("fm_rev_powerdown\n");
                os_task_del_res_name(OS_TASK_SELF);
            }
            break;

        case SYS_EVENT_PLAY_SEL_END: //提示音结束
            // fm_puts("FM_SYS_EVENT_PLAY_SEL_END\n");
            play_sel_stop(); //关闭提示音
            // fm_puts("FM_play_tone_end\n");
            //os_taskq_post_msg(FM_TASK_NAME, 1, MSG_FM_INIT); //触发FM初始化
#ifdef FM_CHANGE_SYS_CLK
            set_sys_freq(FM_SYS_Hz);
#endif

#ifdef FM_PROMPT_EN
            if(fm_prompt_stopped)
            {
                init_fm_rev();
            }
            else
            {
                dac_set_samplerate(32000,1);
                fm_module_mute(0);


		 #ifdef  SUPPORT_ZY_SA_VOICE
		 #ifndef SUPPORT_ONLY_MODE_VOICE
	                if(IsFmSearchBegin)
				    {
				  //  	IsFmSearchBegin = 0;

				    	fm_mode_var->scan_mode = FM_SCAN_STOP;
						os_taskq_post_msg(FM_TASK_NAME, 1, MSG_FM_SCAN_ALL_INIT);
				    }
				    else if(IsFmSearchEnd)
				    {
				   // 	IsFmSearchEnd = 0;
				     	IsFmSearchBegin = 0;
						os_taskq_post_msg(FM_TASK_NAME, 1, MSG_FM_NEXT_STATION);
				    	fm_mode_var->scan_mode = FM_SCAN_STOP;
						
				    	}
				 #ifdef support_fm_aux_rec_voice
				    else if(IsFmRecBegin)
				    {
				     		IsFmRecBegin = 0;
						os_taskq_post_msg(FM_TASK_NAME, 1, MSG_REC_START);						
				    	}					
				 #endif
					
		#endif
		#endif
				
            }
            fm_prompt_stopped = 1;
#else
            init_fm_rev();
#endif

            // fm_puts("init_fm_rev_over\n");
            dac_channel_on(RADIO_CHANNEL, FADE_ON);
            set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);
            // fm_puts("FM_init_over\n");
            break;
			#ifdef SUPPORT_FM_PAUSE
			case MSG_FM_PP:
			bFmPauseFlag=!bFmPauseFlag;
			   if(bFmPauseFlag){
			      fm_module_mute(1);
			      #if LED_PAUSE
			      LED_STATUS|=LED_PAUSE;
			      #endif
			   }else{			   
			   fm_module_mute(0);
               #if LED_PAUSE
			   LED_STATUS&=~LED_PAUSE;
               #endif
			   }
			break;
			#endif

#ifdef  support_fm_stop_scan_key
        case MSG_FM_STOP_SCAN_ALL:		

           if (fm_mode_var->scan_mode == FM_SCAN_ALL)
            	{
             		os_taskq_post_msg(FM_TASK_NAME, 1, MSG_FM_SCAN_ALL_INIT);
            	}	
		   
        	break;
#endif
#ifdef  SUPPORT_ZY_SA_VOICE
#ifndef SUPPORT_ONLY_MODE_VOICE

        case MSG_FM_SEARCHING:		

		if(IsVoiceEnable)
        	{
        		IsFmSearchBegin = 1;
        		IsFmSearchEnd = 0;
		  #ifdef SUPPORT_DOUBLE_VOICE
	 		    if(IsVoiceEnable==1)	        	
	        		fm_prompt_play(BPF_FM_SCAN_MP3);
				else  if(IsVoiceEnable==2)	        	
	        		fm_prompt_play(BPF_FM_SCAN_MP3_EN);
		#else
	        		fm_prompt_play(BPF_FM_SCAN_MP3);
		
		   #endif			
        	}
        	else
        	{
				os_taskq_post_msg(FM_TASK_NAME, 1, MSG_FM_SCAN_ALL_INIT);
        	}
        	break;
#endif
#endif

        case  MSG_FM_SCAN_ALL_INIT:
            // fm_printf("MSG_FM_SCAN_ALL_INIT\n");
           #ifdef FM_SCAN_STOP_LIGHT_ON
            if(bFmScanStop)bFmScanStop=FALSE;
           #endif
            if (fm_mode_var->scan_mode == FM_SCAN_STOP)
            {
                fm_module_mute(1);
                os_time_dly(50);
                fm_info->dat[FM_CHAN]=0;
                fm_info->dat[FM_FRE]=0;
                clear_all_fm_point();
                fm_mode_var->wTotalChannel = 0;
                fm_mode_var->wFreChannel = 0;
                fm_mode_var->wFreq = MIN_FRE - 1;//自动搜索从最低的频点开始
                scan_counter = MAX_CHANNL;
                fm_mode_var->scan_mode = FM_SCAN_ALL;
            }
            else
            {
                #ifdef FM_SCAN_STOP_LIGHT_ON
                bFmScanStop=TRUE;
                #endif
                scan_counter = 1;//再搜索一个频点就停止
            }

        case  MSG_FM_SCAN_ALL:
            #ifdef LED_SHOW_FM
            #ifdef FM_SCAN_STOP_LIGHT_ON
            if(bFmScanStop)
			setLedLight(LED_SHOW_FM,led_mode_on,0);
            else
            #endif
        	setLedLight(LED_SHOW_FM,led_mode_flash_fast,0);
            #else
            //led_fre_set(5);
            #endif
            //// fm_printf("MSG_FM_SCAN_ALL\n");
            if (fm_scan(fm_mode_var->scan_mode))
            {
                if (fm_mode_var->scan_mode == FM_SCAN_ALL)
                {
                #ifdef LED_SHOW_FM //收到台常亮
				setLedLight(LED_SHOW_FM,led_mode_on,0);
                #endif
                    os_time_dly(100);  //// Wait one second
                }
                else
                {
                    fm_mode_var->scan_mode = FM_SCAN_STOP;
                   #ifdef LED_SHOW_FM
                	setLedLight(LED_SHOW_FM,led_mode_on,0);
                  #else
                    //led_fre_set(15);
                   #endif
                    SET_UI_UNLOCK();
                    break;
                }
            }
            scan_counter--;
            if (scan_counter == 0)
            {
                if (fm_mode_var->scan_mode == FM_SCAN_ALL)                 //全频点搜索结束，播放第一个台
                {

			 #ifdef  SUPPORT_ZY_SA_VOICE
			 #ifdef SUPPORT_FM_SCAN_END_VOICE			
		 		if(IsVoiceEnable)
		         	{
		               	 SET_UI_UNLOCK();
			              SET_UI_MAIN(MENU_FM_MAIN);
		         	
					IsFmSearchBegin = 0;
					IsFmSearchEnd = 1;
					fm_prompt_play(BPF_FM_SCAN_END_MP3);	
					break;			
			         }
			 #endif
			 #endif
				
                    os_taskq_post(FM_TASK_NAME, 1, MSG_FM_NEXT_STATION);
                    fm_mode_var->scan_mode = FM_SCAN_STOP;
                    // fm_printf("FM_SCAN_OVER\n");
                }
                else                            //半自动搜索，播放当前频点
                {
                    fm_mode_var->scan_mode = FM_SCAN_STOP;
                    fm_module_mute(0);

                }
               #ifdef LED_SHOW_FM
             	setLedLight(LED_SHOW_FM,led_mode_on,0);
               #else
                //led_fre_set(15);
               #endif
                SET_UI_UNLOCK();
            }
            else       //搜索过程
            {
                os_time_dly(1);
                if(fm_mode_var->scan_mode != FM_SCAN_STOP)
                {
                    os_taskq_post(FM_TASK_NAME, 1, MSG_FM_SCAN_ALL);
                }
            }
            break;

        case MSG_FM_SCAN_ALL_DOWN:
            // fm_printf("MSG_FM_SCAN_ALL_DOWN\n");
            fm_mode_var->scan_mode = FM_SCAN_PREV;
            os_taskq_post(FM_TASK_NAME, 1, MSG_FM_SCAN_ALL);
            break;

        case MSG_FM_SCAN_ALL_UP:
            // fm_printf("MSG_FM_SCAN_ALL_UP\n");
            fm_mode_var->scan_mode = FM_SCAN_NEXT;
            os_taskq_post(FM_TASK_NAME, 1, MSG_FM_SCAN_ALL);
            break;

        case  MSG_FM_PREV_STEP:
            // fm_printf("MSG_FM_PREV_STEP\n");
            res=set_fre(FM_FRE_DEC);
            if(res)
            {
                save_fm_point(fm_mode_var->wFreq - MIN_FRE);
                fm_mode_var->wTotalChannel = get_total_mem_channel();
            }
            fm_mode_var->wFreChannel = get_channel_via_fre(fm_mode_var->wFreq - MIN_FRE);
            fm_info->dat[FM_FRE]=fm_mode_var->wFreq - MIN_FRE;
            fm_info->dat[FM_CHAN]=fm_mode_var->wFreChannel;
            fm_save_info();
            fm_module_mute(0);
            if(!res)
            {
                fm_mode_var->wFreChannel = 0;
            }
            UI_menu(MENU_FM_MAIN);
            break;

        case MSG_FM_NEXT_STEP:
            // fm_printf("MSG_FM_NEXT_STEP\n");
            res=set_fre(FM_FRE_INC);
            if(res)
            {
                save_fm_point(fm_mode_var->wFreq - MIN_FRE);
                fm_mode_var->wTotalChannel = get_total_mem_channel();
            }
            fm_mode_var->wFreChannel = get_channel_via_fre(fm_mode_var->wFreq - MIN_FRE);
            fm_info->dat[FM_FRE]=fm_mode_var->wFreq - MIN_FRE;
            fm_info->dat[FM_CHAN]=fm_mode_var->wFreChannel;
            fm_save_info();
            fm_module_mute(0);
            if(!res)
            {
                fm_mode_var->wFreChannel = 0;
            }
            UI_menu(MENU_FM_MAIN);
            break;
			
#if defined SUPPORT_ZY_SA_VOICE&& !defined SUPPORT_ONLY_MODE_VOICE


        case MSG_FM_PREV_STATION:
            // fm_printf("MSG_FM_PREV_STATION\n");
            
            if (fm_mode_var->wTotalChannel == 0)  break;
            //fm_mode_var->wFreChannel -= 2;

            fm_mode_var->wFreChannel--;
            if(fm_mode_var->wFreChannel == 0)
            {
                fm_mode_var->wFreChannel = fm_mode_var->wTotalChannel;
            }
            
            fm_mode_var->wLastwTotalChannel=fm_mode_var->wTotalChannel;
            fm_mode_var->wFreq = get_fre_via_channle(fm_mode_var->wFreChannel) + MIN_FRE;				//根据台号找频点
            set_fre(FM_CUR_FRE);
            fm_info->dat[FM_FRE]=fm_mode_var->wFreq - MIN_FRE;
            fm_info->dat[FM_CHAN]=fm_mode_var->wFreChannel;
            fm_save_info();
            fm_module_mute(0);
            UI_menu(MENU_FM_CHANNEL);

		  #ifdef SUPPORT_DOUBLE_VOICE
	 		    if(IsVoiceEnable==1)	        	
	        		fm_prompt_play(BPF_LAST_CH_MP3);
				else  if(IsVoiceEnable==2)	        	
	        		fm_prompt_play(BPF_LAST_CH_MP3_EN);
		#else
			if(IsVoiceEnable)
		            {
		            	fm_prompt_play(BPF_LAST_CH_MP3);
		            }		
		   #endif			



            break;


        case MSG_FM_NEXT_STATION:
            // fm_printf("MSG_FM_NEXT_STATION\n");
            if (fm_mode_var->wTotalChannel == 0)
            {
                fm_module_mute(0);
                break;
            }

            fm_mode_var->wFreChannel++;
            if ((fm_mode_var->wFreChannel == 0) || (fm_mode_var->wFreChannel == 0xff))
            {
                fm_mode_var->wFreChannel = fm_mode_var->wTotalChannel;
            }
            else if (fm_mode_var->wFreChannel > fm_mode_var->wTotalChannel)
            {
                fm_mode_var->wTotalChannel = get_total_mem_channel();
                fm_mode_var->wFreChannel = 1;
            }
            fm_mode_var->wLastwTotalChannel=fm_mode_var->wTotalChannel;
            fm_mode_var->wFreq = get_fre_via_channle(fm_mode_var->wFreChannel) + MIN_FRE;				//根据台号找频点
            set_fre(FM_CUR_FRE);
            fm_info->dat[FM_FRE]=fm_mode_var->wFreq - MIN_FRE;
            fm_info->dat[FM_CHAN]=fm_mode_var->wFreChannel;
            fm_save_info();
            fm_module_mute(0);
            UI_menu(MENU_FM_CHANNEL);

	 #ifdef SUPPORT_DOUBLE_VOICE
	 	    if(IsVoiceEnable==1)	        	
	 		fm_prompt_play(BPF_NEXT_CH_MP3);
	 	else  if(IsVoiceEnable==2)	        	
	 		fm_prompt_play(BPF_NEXT_CH_MP3_EN);
		
	 #else
		 #ifdef SUPPORT_FM_SCAN_END_VOICE		
			     if(IsFmSearchEnd)
			    {
			    		IsFmSearchEnd = 0;
			    	}
				else
						
		#endif
		
			 if(IsVoiceEnable)
		         {
		         
		         	fm_prompt_play(BPF_NEXT_CH_MP3);
		         }
		 
	 
		
	 #endif			

            break;

#else

        case MSG_FM_PREV_STATION:
            // fm_printf("MSG_FM_PREV_STATION\n");
            if (fm_mode_var->wTotalChannel == 0)
                break;
            fm_mode_var->wFreChannel -= 2;

        case MSG_FM_NEXT_STATION:
            // fm_printf("MSG_FM_NEXT_STATION\n");
            if (fm_mode_var->wTotalChannel == 0)
            {
                fm_module_mute(0);
                break;
            }

            fm_mode_var->wFreChannel++;
            if ((fm_mode_var->wFreChannel == 0) || (fm_mode_var->wFreChannel == 0xff))
            {
                fm_mode_var->wFreChannel = fm_mode_var->wTotalChannel;
            }
            else if (fm_mode_var->wFreChannel > fm_mode_var->wTotalChannel)
            {
                fm_mode_var->wTotalChannel = get_total_mem_channel();
                fm_mode_var->wFreChannel = 1;
            }
            fm_mode_var->wLastwTotalChannel=fm_mode_var->wTotalChannel;
            fm_mode_var->wFreq = get_fre_via_channle(fm_mode_var->wFreChannel) + MIN_FRE;				//根据台号找频点
            set_fre(FM_CUR_FRE);
            fm_info->dat[FM_FRE]=fm_mode_var->wFreq - MIN_FRE;
            fm_info->dat[FM_CHAN]=fm_mode_var->wFreChannel;
            fm_save_info();
            fm_module_mute(0);
            UI_menu(MENU_FM_CHANNEL);
            break;
#endif
        case MSG_MUSIC_PP:
#if UI_ENABLE
            if (UI_var.bCurMenu == MENU_INPUT_NUMBER)   //暂停和播放
            {
                os_taskq_post(FM_TASK_NAME, 1, MSG_INPUT_TIMEOUT);
                break;
            }
#elif IR_NUM_INPUT_EN
			if(ir_num_timeout_cnt)
			{
				os_taskq_post(FM_TASK_NAME, 1, MSG_INPUT_TIMEOUT);
				break;
			}
#endif
            break;

        case SYS_EVENT_SYSCLK_NOTFIT_DEVMOUNT:
            //puts("------FM_SYS_EVENT_SYSCLK_NOTFIT_DEVMOUNT\n");
#ifdef FM_CHANGE_SYS_CLK
            if(fm_mode_var->scan_mode != FM_UNACTIVE)//FM已经初始化
            {
                fm_module_mute(1);
                set_sys_freq(SYS_Hz);
            }
#endif
            break;

        case SYS_EVENT_DEV_MOUNT_ERR:
            //puts("------FM_SYS_EVENT_DEV_MOUNT_ERR\n");
#ifdef FM_CHANGE_SYS_CLK
            if(fm_mode_var->scan_mode != FM_UNACTIVE)//FM已经初始化
            {
                set_sys_freq(FM_SYS_Hz);
                fm_module_mute(0);
            }
#endif
            break;

        case MSG_INPUT_TIMEOUT:
            /*由红外界面返回*/
            if (input_number <= MAX_CHANNL)							//输入的是台号
            {
                msg[0] = get_fre_via_channle(input_number);
                if (msg[0] != 0xff)
                {
                    fm_mode_var->wFreq = msg[0] + MIN_FRE;
                    fm_mode_var->wFreChannel = input_number;
                    set_fre(FM_CUR_FRE);
                    fm_module_mute(0);
                    UI_menu(MENU_FM_DISP_FRE);
                }
            }
            else if ((input_number >= MIN_FRE) && (input_number <= MAX_FRE)) //输入的是频点
            {
                fm_mode_var->wFreq = input_number;
                fm_mode_var->wFreChannel = get_channel_via_fre(fm_mode_var->wFreq - MIN_FRE);
                set_fre(FM_CUR_FRE);
                fm_module_mute(0);
            }
            input_number = 0;
//          set_memory(MEM_FRE, fm_mode_var.wFreq - MIN_FRE);
//			set_memory(MEM_CHAN, fm_mode_var.bFreChannel);
            UI_menu(MENU_FM_DISP_FRE);
            break;

        case MSG_LOW_POWER:
            puts("fm_low_power\n");
            fm_prompt_play(BPF_LOW_POWER_MP3);
            break;
#if REC_EN
 	    case MSG_REC_EXIT:
			 exit_rec_api(rec_fm_api);
			 break;
#endif

     #ifdef  support_power_off_tone
     	case MSG_VOICE_POWER_OFF:

		fm_prompt_play(BPF_POWER_OFF_MP3);
			
	 	delay_2ms(10);

	      #ifdef LED_SHOW_MP3
	 	   setLedLight(LED_SHOW_MP3,led_mode_off,0);
	      #endif

		
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
			
        	break;		 
     #endif			

#ifdef SUPPORT_VOICE_ONOFF_VOICE	

 		case MSG_FM_VOICE_ONOFF:
			
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
				 
					fm_prompt_play(BPF_VOICE_ON_MP3);
				}
				else
				{
				 #ifdef LED_SHOW_ONOFF
				 	UI_menu(MENU_ONOFF);
				 #endif
		 		 #ifdef support_voice_onoff_mem
		 		 	vm_write_api(VM_SYS_EQ,&led7_var.bIfHaveVoice);
		 		 #endif
					 fm_prompt_play(BPF_VOICE_OFF_MP3);
				}
						
				 

			break; 
#endif

#ifdef  SUPPORT_ZY_SA_VOICE

#ifdef support_fm_aux_rec_voice
		case MSG_FM_REC_START:	
		if(IsVoiceEnable)
        	{
        		IsFmRecBegin = 1;
	        		fm_prompt_play(BPF_REC_MP3);		
        	}
        	else
        	{
				os_taskq_post_msg(FM_TASK_NAME, 1, MSG_REC_START);
        	}			
		break;
#endif

		case MSG_FM_VOICE_SWITCH:	


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
		 					fm_prompt_play(BPF_VOICE_OFF_MP3);
						 else
		 					fm_prompt_play(BPF_VOICE_OFF_MP3_EN);						 	
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
		 					fm_prompt_play(BPF_VOICE_ON_MP3);
						 else
		 					fm_prompt_play(BPF_VOICE_ON_MP3_EN);						 			 				 
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
				
				fm_prompt_play(BPF_VOICE_OFF_MP3);	
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
				
				 fm_prompt_play(BPF_VOICE_ON_MP3);	
			}	
		#endif	
		
		break;	
	 #ifndef SUPPORT_ONLY_MODE_VOICE

		 case MSG_VOICE_MUTE:

			if(IsVoiceEnable)
	    	{
  			 #ifdef SUPPORT_DOUBLE_VOICE
				if(IsVoiceEnable==2)
		    			fm_prompt_play(BPF_MUTE_MP3_EN);
				else
			 #endif    		    		    			
		    			fm_prompt_play(BPF_MUTE_MP3);	
			
	    	}
	    	break;

		case MSG_VOICE_VOLUME_PLUS:

			 if(IsVoiceEnable)
			 {
  			 #ifdef SUPPORT_DOUBLE_VOICE
				if(IsVoiceEnable==2)
		    			fm_prompt_play(BPF_VL_INC_MP3_EN);
				else
			 #endif    	
			 	{
					#ifdef SUPPORT_SMM_SA_VOICE			 	
			 	 	{
						if(dac_var.cur_sys_vol_l ==30) 			
			    				fm_prompt_play(BPF_VL_MAX_MP3);			    		    				 	    		    		    					 
						else		 	 	
			    				fm_prompt_play(BPF_VL_INC_MP3);			    		    				 	    		    		    					 
			 	 	}
					#else
					
			    				fm_prompt_play(BPF_VL_INC_MP3);			    		    				 	    		    		    					 
					#endif
			 	}			 
		 }
			 break;		
		
		case MSG_VOICE_VOLUME_MINUS:

			 if(IsVoiceEnable)
			 {
  			 #ifdef SUPPORT_DOUBLE_VOICE
				if(IsVoiceEnable==2)
		    			fm_prompt_play(BPF_VL_DEC_MP3_EN);
				else
			 #endif    		    		    				 			 
	    			fm_prompt_play(BPF_VL_DEC_MP3);			    		    				 
			 }
			 break;

	    case MSG_MAX_VOICE:

		if(IsVoiceEnable)
	    	{
  			 #ifdef SUPPORT_DOUBLE_VOICE
				if(IsVoiceEnable==2)
		    			fm_prompt_play(BPF_VL_MAX_MP3_EN);
				else
			 #endif    		    		    				 			 
	    			fm_prompt_play(BPF_VL_MAX_MP3);			    		    				 
	    	 		    		    				 
	    	}
	    	break;	

	    case MSG_VOICE_NUMBER:

		if(IsVoiceEnable)
	    	{
			if(bVoiceNumber == 0)	
		            {
		            	fm_prompt_play( BPF_0_MP3);
		            }
		            else if(bVoiceNumber == 1)
		            {
		            	fm_prompt_play( BPF_1_MP3);
		            }
		            else if(bVoiceNumber == 2)
		            {
		            
		            	fm_prompt_play(BPF_2_MP3);
		            }
		            else if(bVoiceNumber == 3)
		            {
		            
		            	fm_prompt_play( BPF_3_MP3);
		            }
		            else if(bVoiceNumber == 4)
		            {
		            
		            	fm_prompt_play( BPF_4_MP3);
		            }
		            else if(bVoiceNumber == 5)
		            {		            
		           		 fm_prompt_play(BPF_6_MP3);
		            }
		            else if(bVoiceNumber == 6)
		            {
		            	fm_prompt_play(BPF_6_MP3);
		            }
		            else if(bVoiceNumber == 7)
		            {
		            
		            	fm_prompt_play(BPF_7_MP3);
		            }
		            else if(bVoiceNumber == 8)
		            {
		            
		            	fm_prompt_play(BPF_8_MP3);
		            }
		            else if(bVoiceNumber == 9)
		            {
		            
		            	fm_prompt_play(BPF_9_MP3);
		            }
	    	 		    		    				 
	    	}
	    	break;	
			

#endif	
#endif	

#ifdef SUPPORT_KEY_6_VOICE
            case MSG_VOICE_YESE:
	    			fm_prompt_play(BPF_VL_MAX_YESE);	
		break;
            case MSG_VOICE_END:
	    			fm_prompt_play(BPF_VL_MAX_END);	
		break;
            case MSG_VOICE_APPLAUD:
	    			fm_prompt_play(BPF_VL_MAX_APPLAUD);	
		break;
            case MSG_VOICE_GUN:
	    			fm_prompt_play(BPF_VL_MAX_GUN);	
		break;
            case MSG_VOICE_ZXC:
	    			fm_prompt_play(BPF_VL_MAX_ZXC);	
		break;
           case MSG_VOICE_BEST_PARTNER:
	    			fm_prompt_play(BPF_VL_MAX_BEST_PARTNER);	
		break;
	
#endif

        case MSG_HALF_SECOND:
		 #if REC_EN
		             updata_enc_time(rec_fm_api);
		 #endif
		 #if 0//REC_EN
		 				   if((g_rec_ctl)&&(ENC_STOP != g_rec_ctl->enable)){
		 				   led7_show_rec_time();			   
		 				   }
		 				   else
		 #endif
	          {
	             UI_menu(MENU_MAIN);
	             UI_menu(MENU_HALF_SEC_REFRESH);
	         #ifdef SUPPORT_FM_PAUSE
	 		 if(bFmPauseFlag)
			   {			      
	       	       #if LED_PAUSE
	 			     LED_STATUS|=LED_PAUSE;
	 	             #endif
	 	           }
		     else 
	 	          {	           
		                 #if LED_PAUSE
		 			     LED_STATUS&=~LED_PAUSE;
		                 #endif
	 	           }
	         #endif	  
	         }
            #if IR_NUM_INPUT_EN
				if(ir_num_timeout_cnt){
				ir_num_timeout_cnt--;
				if(ir_num_timeout_cnt==0)				  
				 os_taskq_post_msg(FM_TASK_NAME, 1, MSG_INPUT_TIMEOUT);
				}
            #endif
            break;

        default:
            rec_msg_del_api(&rec_fm_api, msg);
            break;
        }
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  FM模式主线程初始化
   @param  priv：NULL
   @return NULL
   @note   static void fm_radio_task_init(void *priv)
*/
/*----------------------------------------------------------------------------*/
static void fm_radio_task_init(void *priv)
{
    u32 err;
		
#ifdef FM_DEBUG
    GET_SYS_MEM_STAT();
#endif
#ifdef DURING_FM_EXITING_TASK_NOT_RESPOND_KEY_MSG
	bExitFMStateCnt=2;
#endif

    err = os_task_create(fm_radio_task,
                         (void*)0,
                         TaskFMradioPrio,
                         50
#if OS_TIME_SLICE_EN > 0
                         ,1
#endif
                         ,FM_TASK_NAME);

    if(OS_NO_ERR == err)
    {
        #if KEY_IO_EN
        key_msg_register(FM_TASK_NAME,fm_ad_table,fm_io_table,fm_ir_table,NULL);
	 #elif LED_KEY_MAX
	 #if KEY_AD_EN
	 	key_msg_register("FMRadioTask",fm_led_table,fm_ad_table,NULL,fm_ir_table,NULL);
	 #else
        key_msg_register(FM_TASK_NAME,fm_ad_table,NULL,fm_ir_table,NULL);
	 #endif   
	   
        #else
        key_msg_register(FM_TASK_NAME,fm_ad_table,NULL,fm_ir_table,NULL);
        #endif
    }
#if MP3_VOL_MAX
		if(bVolMaxChangeToSmallVolMax>=0)
		dac_var.cur_sys_vol_l=bVolMaxChangeToSmallVolMax;
		dac_var.cur_sys_vol_r = dac_var.cur_sys_vol_l;
#if PA_EN 
		pa_umute();
#endif 			
		set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);
#elif FM_VOL_MAX
		if(bVolMaxChangeToSmallVolMax>=(SYS_VOL_MAX-FM_VOL_MAX))
		dac_var.cur_sys_vol_l=bVolMaxChangeToSmallVolMax-(SYS_VOL_MAX-FM_VOL_MAX);
		else
		dac_var.cur_sys_vol_l=0;
		dac_var.cur_sys_vol_r = dac_var.cur_sys_vol_l;
		set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);
     #if defined(PA_EN) 
		pa_umute();
     #endif 			
#elif defined(support_mode_change_vol_min_to_min)
		if(dac_var.cur_sys_vol_l<support_mode_change_vol_min_to_min)
		dac_var.cur_sys_vol_l=support_mode_change_vol_min_to_min;
		dac_var.cur_sys_vol_r = dac_var.cur_sys_vol_l;
#if PA_EN 
		pa_umute();
#endif 			
		set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);
#endif 
#ifdef SUPPORT_PT2313
		Pt2313_ChangSource(Aud_SwRadio);
#endif
	
#ifdef support_amP_ab_d
	Set_amp_ab_d_out() ;
	Set_FM_IS_AB();		
#endif 

#ifdef support_sound_4052_control
#if defined sound_4052_io_mode_6 ||defined sound_4052_io_mode_5
	AC4052_IS_FM(); 
#endif
#endif
	
#ifdef SUPPORT_FLASH_CHAR
	if(LED_FLASH_CHAR)
	LED_FLASH_CHAR=0;
 #endif
#if LED_SHOW_BT
	 setLedLight(LED_SHOW_BT,led_mode_off,0);
#endif
#if LED_SHOW_FM
	 setLedLight(LED_SHOW_FM,led_mode_on,0);
#endif
	
#ifdef TF2025A_CONTROL_PB10_ALONG
	TF2025A_SET_PB9_26PIN(0);
#endif  
  #ifdef KOK_DETECT_AUTO_VOL_SET		
 	 store_vol= dac_var.cur_sys_vol_l;
 #endif

#ifdef  SUPPORT_ZY_SA_VOICE
    IsFmSearchBegin = 0;	
    IsFmSearchEnd = 0;	
#endif
#ifdef SUPPORT_USE_ENCODE_AS_MODE_CHANGE	
	bMulitWorkmode=RADIO_WORK_MODE;
#endif

#ifdef SUPPORT_WOKRMODE
	workmode=RADIO_WORK_MODE;
#ifdef SUPPORT_MODE_VM
       vm_write_api(VM_SYS_EQ,&workmode);
#endif
#ifdef SUPPORT_MODE_VM
#ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE
bModeOfAuxContained=mode_aux;
#endif
#endif
#endif
#ifdef support_io_det_mute
		pa_umute1();
#endif
#if defined(LED_ID_JW2781)
led7_var.bEqCircleIfPlay=TRUE;
#endif

}

/*----------------------------------------------------------------------------*/
/**@brief  FM模式退出
   @param  NULL
   @return NULL
   @note   static void fm_radio_task_exit(void)
*/
/*----------------------------------------------------------------------------*/
static void fm_radio_task_exit(void)
{
    /*先关闭FM模块线程，再关闭FM变采样线程*/
    if (os_task_del_req(FM_TASK_NAME) != OS_TASK_NOT_EXIST)
    {
        os_taskq_post_event(FM_TASK_NAME, 1, SYS_EVENT_DEL_TASK);
        do
        {
//            // fm_puts("fm_wating-01\n");
            OSTimeDly(1);
        }
        while(os_task_del_req(FM_TASK_NAME) != OS_TASK_NOT_EXIST);
        // fm_puts("clos_fm_task_succ-01\n");
    }

#ifdef FM_DEBUG
    GET_SYS_MEM_STAT();
#endif

#ifdef FM_CHANGE_SYS_CLK
    set_sys_freq(SYS_Hz);
#endif
       #ifdef SUPPORT_MUTE_FLASH
	   b_muteFlag=FALSE;
      #endif

}

TASK_REGISTER(fm_radio_task_info) =
{
    .name = FM_TASK_NAME,
    .init = fm_radio_task_init,
    .exit = fm_radio_task_exit,
};


#endif
