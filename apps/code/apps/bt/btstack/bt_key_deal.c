#include "bt_key_deal.h"
#include "os_api.h"
#include "error.h"
#include "msg.h"
#include "app_cfg.h"
#include "avctp_user.h"
#include "task_manage.h"
#include "play_sel.h"
#include "decoder_phy.h"
#include "led.h"
#include "dac_api.h"
#include "ui_api.h"
#include "bt_key_msg.h"
#include "key.h"
#include "run_loop.h"
#include "record.h"
#include "encode.h"
#include "led7_drv.h"
#include "vm_api.h"

#ifdef BT_TESTER
	#include "bt_test_key_msg.h"
#endif

#define BT_REC_Hz  120000000L

#ifdef EQ_SEQUENCE_ADJ_ANYWAY
#include "ef_api.h"
u8 bt_eq_sequence_mode=eq_normal;
#endif
#ifdef BT_NOT_PLAY_IO_MUTE
u8 bBtIOMuteDelayCnt=0;
#endif
#if BT_BACKMODE
bool bFirstPowerFlag=FALSE;
#endif
#if LED_SHOW_BT
bool bBtPlayFlag=FALSE;
#endif
#if LED_SHOW_VOL_MAX
extern u8 bVolMaxChangeToSmallVolMax;
#endif
#ifdef support_change_mode_bt_icon_off
bool  exit_bt_sw;
#endif

RECORD_OP_API * rec_bt_api = NULL;

struct user_ctrl{
    u8 is_phone_number_come;
    u8 play_phone_number_flag;
    u8 phone_prompt_tone_playing_flag;
    u8 phone_num_len;
    u8 income_phone_num[15];
    u8 user_cmd_param_buf[30];
    u8 bt_eq_mode;
    u8 tone_by_file_num;
};

#ifdef HAVE_MALLOC
_PLAY_SEL_PARA *psel_p = NULL;
#else
_PLAY_SEL_PARA __psel_p;
#define psel_p (&__psel_p)
#endif

static struct user_ctrl __user_val;
#define user_val (&__user_val)

extern tbool mutex_resource_apply(char *resource,int prio ,void (*apply_response)(), void (*release_request)());
extern void delete_stack_task(void);
extern void delete_lmp_task(void);
extern bool is_lmp_link_conn_state();
extern void h4_upload_wakeup();
extern u8 a2dp_get_status(void);
OS_MUTEX tone_manage_semp ; //= OS_MUTEX_INIT();

void create_bt_msg_task(char *task_name)
{
    u32 err;
    err = os_task_create(TaskBtMsgStack,(void *)0,TaskBTMSGPrio,30,task_name);
    if(OS_NO_ERR != err)
    {
        // puts("create bt msg fail\n");
        while(1);
    }
}

/*提示音开始，资源管理线程接口，用户不能调用*/
void tone_mutex_play()
{
    play_sel("resourse",'A',psel_p);
    if(psel_p->max_file_number > 3) //报号开始
    {
        user_val->play_phone_number_flag = 1;
    }
    free_fun((void **)&psel_p->file_number);
    free_fun((void **)&psel_p);
    os_sem_post(&tone_manage_semp);
}
/*资源管理线程接口，用户不能调用*/
void tone_mutex_stop()
{
    play_sel_stop();

    dac_channel_on(BT_CHANNEL, FADE_OFF);
    set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);

    // puts("--------tone_mutex_stop------------------\n");

    //os_sem_post(&tone_manage_semp);
    if( user_val->play_phone_number_flag == 1)
    {   //来电报号提示音播完后要播要循环播提示声
        user_val->play_phone_number_flag = 0;
        update_bt_current_status(BT_STATUS_PHONE_INCOME,BT_STATUS_TAKEING_PHONE);
    }
}

/*获取到来电电话号码，用于报号功能*/
void hook_hfp_incoming_phone_number(char* number, u16 length)
{
    if(user_val->is_phone_number_come == 0)
    {
        //put_buf((u8 *)number,length);
        user_val->is_phone_number_come = 1;
        user_val->phone_num_len = length;
        memcpy(user_val->income_phone_num,number,length);
        update_bt_current_status(BT_STATUS_PHONE_NUMBER,0);
    }
    //put_buf(user_val->income_phone_num,user_val->phone_num_len);
}

/*封装函数根据状态选择提示音*/
void user_ctrl_prompt_tone_play(u8 status,void *ptr)
{
#ifdef BT_TESTER
    return;
#endif

#ifdef support_off_voice
    return;
#endif

    // puts("play_tone\n");
    if(get_remote_test_flag()&&(status == BT_STATUS_CONNECTED))   //测试盒测试不播放提示音
    {
        return;
    }
    if(play_sel_busy())
    {
        play_sel_stop();
        //os_sem_pend(&tone_manage_semp,0);
        // puts("------------play_sel_stop----------\n");
    }
    psel_p  = malloc_fun(psel_p ,sizeof(_PLAY_SEL_PARA),0);
    if(psel_p == NULL)
    {
        return ;
    }
    psel_p->file_number = malloc_fun(psel_p->file_number,15*4,0); //电话号码至少需要11

    if(NULL == psel_p->file_number)
    {
        free_fun((void **)&psel_p);
        return ;
    }

    switch(status)
    {
        case BT_STATUS_POWER_ON:
            psel_p->max_file_number = 1;
            psel_p->delay = 10;
            psel_p->rpt_time = 1;
#ifdef REMOVE_BT_MODE_NOTICE
        #if BT_HID_INDEPENDENT_MODE || USER_SUPPORT_PROFILE_HID
            if(__get_hid_independent_flag())
            {
                //HID独立提示音
                psel_p->file_number[1] = BPF_DISCON_HID_MP3;
            }else
        #endif
            {
            
		 #ifdef SUPPORT_DOUBLE_VOICE
	              #ifdef SUPPORT_VOICE_ONOFF
				if(IsVoiceEnable==0)
		                psel_p->file_number[0] = BPF_WAIT_MP3_NOTICE;
				else
	             #endif
		 
			if(IsVoiceEnable==1)
		                psel_p->file_number[0] = BPF_WAIT_MP3;
			else if(IsVoiceEnable==2)
		                psel_p->file_number[0] = BPF_WAIT_MP3_EN;			
            #else
			
	              #ifdef SUPPORT_VOICE_ONOFF
					if(led7_var.bIfHaveVoice)
	             #endif
	             {
	               #ifdef BT_POWER_ON_USE_WAIT_VOICE
	   			    psel_p->file_number[0] = BPF_WAIT_MP3;
	               #else
	                psel_p->file_number[0] = BPF_DISCONNECT_MP3;
	               #endif
	             }
	             #ifdef SUPPORT_BT_TWO_TYPE_VOICE
	             else{
					 psel_p->file_number[0] = BPF_DISCONNECT1_MP3;
	             }
	             #endif
		#endif	 
            }
#else
           #ifdef SUPPORT_VOICE_ONOFF
			if(led7_var.bIfHaveVoice)
           #endif
            #if (S10_MODE)
                psel_p->file_number[0] = BPF_WAIT_MP3;
            #else
                psel_p->file_number[0] = BPF_BT_MP3;
            #endif
             #ifdef SUPPORT_BT_TWO_TYPE_VOICE
	             else
			{
				psel_p->file_number[0] = BPF_BT1_MP3;
	             }
             #endif				
			
#ifndef POWER_ON_NOT_USE_DISCONNECT_VOICE            
#if BT_HID_INDEPENDENT_MODE || USER_SUPPORT_PROFILE_HID
            if(__get_hid_independent_flag())
            {
                //HID独立提示音
                psel_p->file_number[1] = BPF_DISCON_HID_MP3;
            }else
#endif
            {
	            #ifdef SUPPORT_VOICE_ONOFF
	            	 if(led7_var.bIfHaveVoice)
	            #endif
	              	  psel_p->file_number[1] = BPF_DISCONNECT_MP3;
            }
#endif
#endif
            break;
        case BT_STATUS_RESUME:
            psel_p->max_file_number = 2;
            psel_p->delay = 10;
            psel_p->rpt_time = 1;
            
#ifdef SUPPORT_VOICE_ONOFF
	 if(led7_var.bIfHaveVoice)
#endif
            #if (S10_MODE)
                psel_p->file_number[0] = BPF_WAIT_MP3;
            #else
                psel_p->file_number[0] = BPF_BT_MP3;
            #endif

            if(get_curr_channel_state() != 0)
            {
                psel_p->file_number[1] = BPF_CONNECT_MP3;
            }
            else
            {
            
#ifdef SUPPORT_VOICE_ONOFF
		 if(led7_var.bIfHaveVoice)
#endif
                psel_p->file_number[1] = BPF_DISCONNECT_MP3;
         #ifdef SUPPORT_BT_TWO_TYPE_VOICE
			   else{
				   psel_p->file_number[1] = BPF_DISCONNECT1_MP3;
			   }
         #endif
            }
            break;
        case BT_STATUS_CONNECTED:
            psel_p->max_file_number = 1;
            psel_p->delay = 10;
            psel_p->rpt_time = 1;
#if BT_HID_INDEPENDENT_MODE || USER_SUPPORT_PROFILE_HID
            if(__get_hid_independent_flag())
            {   //HID独立提示音
                psel_p->file_number[0] = BPF_CONN_HID_MP3;
            }else
#endif
            {
 		 #ifdef SUPPORT_DOUBLE_VOICE
	              #ifdef SUPPORT_VOICE_ONOFF
				if(IsVoiceEnable==0)
		                psel_p->file_number[0] = BPF_CONNECT_MP3_NOTICE;
				else
	             #endif
		 
			if(IsVoiceEnable==1)
		                psel_p->file_number[0] = BPF_CONNECT_MP3;
			else if(IsVoiceEnable==2)
		                psel_p->file_number[0] = BPF_CONNECT_MP3_EN;	
		#else
			  #ifdef SUPPORT_VOICE_ONOFF
				 			 if(led7_var.bIfHaveVoice)
				 #endif
		                psel_p->file_number[0] = BPF_CONNECT_MP3;
		          #ifdef SUPPORT_BT_TWO_TYPE_VOICE
					else{
						psel_p->file_number[0] = BPF_CONNECT1_MP3;
					}
		         #endif
		 #endif
            }
            break;
        case BT_STATUS_DISCONNECT:
            psel_p->max_file_number = 1;
            psel_p->delay = 10;
            psel_p->rpt_time = 1;
#if BT_HID_INDEPENDENT_MODE || USER_SUPPORT_PROFILE_HID
            if(__get_hid_independent_flag())
            {   //HID独立提示音
                psel_p->file_number[0] = BPF_DISCON_HID_MP3;
            }else
#endif
            {
 		 #ifdef SUPPORT_DOUBLE_VOICE
	              #ifdef SUPPORT_VOICE_ONOFF
				if(IsVoiceEnable==0)
		                psel_p->file_number[0] = BPF_DISCONNECT_MP3_NOTICE;
				else
	             #endif
			if(IsVoiceEnable==1)
		                psel_p->file_number[0] = BPF_DISCONNECT_MP3;
			else if(IsVoiceEnable==2)
		                psel_p->file_number[0] = BPF_DISCONNECT_MP3_EN;	
		#else
		
			 #ifdef SUPPORT_VOICE_ONOFF
			 			 if(led7_var.bIfHaveVoice)
			 #endif
			                 psel_p->file_number[0] = BPF_DISCONNECT_MP3;
			  #ifdef SUPPORT_BT_TWO_TYPE_VOICE
			 			   else{
			 				   psel_p->file_number[0] = BPF_DISCONNECT1_MP3;
			 			   }
			 #endif
		#endif
            }

            break;
        case BT_STATUS_TONE_BY_FILE_NUM:
            psel_p->max_file_number = 1;
            psel_p->delay = 10;
            psel_p->rpt_time = 1;
            
		 #if 0//def SUPPORT_VOICE_ONOFF
		 	  if(led7_var.bIfHaveVoice)
		 #endif
            psel_p->file_number[0] = user_val->tone_by_file_num;
            break;
        case BT_STATUS_PHONE_INCOME:
            psel_p->max_file_number = 1;
            psel_p->delay = 10;
            psel_p->rpt_time = 0;
#ifdef SUPPORT_VOICE_ONOFF
			 if(led7_var.bIfHaveVoice)
#endif
            psel_p->file_number[0] = BPF_RING_MP3;
            user_val->play_phone_number_flag = 0;
            user_val->phone_prompt_tone_playing_flag = 1;
            break;
#if BT_PHONE_NUMBER
        case BT_STATUS_PHONE_NUMBER:
            if(user_val->is_phone_number_come)   //有电话号码就播放
            {
                int i;
                psel_p->max_file_number = user_val->phone_num_len;
                psel_p->delay = 20;
                psel_p->rpt_time = 1;
                for(i = 0;i < user_val->phone_num_len; i++)
                {
                
		 #ifdef SUPPORT_VOICE_ONOFF
		 	 if(led7_var.bIfHaveVoice)
		 #endif
                    psel_p->file_number[i] = BPF_0_MP3 + (user_val->income_phone_num[i] - 0x30);
                }
                user_val->phone_prompt_tone_playing_flag = 1;
                break;//break要放在if里面，不播放直接free了
            }
#endif
        default:
            free_fun((void **)&psel_p->file_number);
            free_fun((void **)&psel_p);
            return;
    }

    mutex_resource_apply("tone",3,tone_mutex_play,tone_mutex_stop);
    os_sem_pend(&tone_manage_semp,0);
}

/*封装一层方便直接使用文件号播放*/
void bt_prompt_play(u8 file_num)
{
#ifdef BT_PROMPT_EN         //定义在avctp_user.h
    // puts("bt_prompt_play\n");
    user_val->tone_by_file_num = file_num;
    user_ctrl_prompt_tone_play(BT_STATUS_TONE_BY_FILE_NUM, NULL);
#endif
}
/*协议栈状态变化用户处理接口*/
void btstack_status_change_deal(void *ptr)
{
    if(get_bt_newest_status() != get_bt_prev_status())
    {
        if(get_bt_prev_status() == BT_STATUS_SUSPEND)
        {
            if(get_bt_newest_status() != BT_STATUS_RESUME
               && get_bt_newest_status() != BT_STATUS_RESUME_BTSTACK)
            {
                if(get_bt_newest_status() == BT_STATUS_CONNECTED)
				{   //当蓝牙处于后台连接成功时给main发送事件通知。用户自行选择处理方式
                    os_taskq_post_event("MainTask", 1, SYS_EVENT_BT_BACKCON);
				}
                if(get_bt_newest_status() == BT_STATUS_DISCONNECT)
				{   //当蓝牙处于后台断开成功时给main发送事件通知。用户自行选择处理方式
                    os_taskq_post_event("MainTask", 1, SYS_EVENT_BT_BACKDISCON);
				}
                // puts("BT_STATUS_SUSPEND\n");
                return ;
            }
        }
        update_bt_prev_status(get_bt_newest_status());
        switch(get_bt_newest_status())
        {
            case BT_STATUS_RESUME:
//               if(get_curr_channel_state() == 0)   //默认切模式回蓝牙不回连
//               {   //当前没连接，进行回连
//                   // puts("start conn\n");
//                   user_send_cmd_prepare(USER_CTRL_START_CONNECTION,0,NULL);
//               }
               user_ctrl_prompt_tone_play(BT_STATUS_RESUME,NULL);
              #if LED_SHOW_BT
				setLedLight(LED_SHOW_BT,led_mode_flash_fast,0);
              #else
			   // led_fre_set(5);
              #endif	
             #if UI_ENABLE
				led7_var.bBtIfConnect=FALSE;
             #endif
               break;
            case BT_STATUS_RESUME_BTSTACK:
               //协议栈要求回
               break;
            case BT_STATUS_POWER_ON:
//               user_ctrl_prompt_tone_play(BT_STATUS_POWER_ON,NULL);
               #if LED_SHOW_BT
				setLedLight(LED_SHOW_BT,led_mode_flash_fast,0);
               #else
			   // led_fre_set(5);
               #endif 
              #if UI_ENABLE
				led7_var.bBtIfConnect=FALSE;
              #endif
               break;
             case BT_STATUS_INIT_OK:
               user_send_cmd_prepare(USER_CTRL_START_CONNECTION,0,NULL);
               break;
            case BT_STATUS_CONNECTED:
		   #if defined ONLY_POWER_ON_MUTE &&defined support_power_no_media_to_bt 
		 	 pa_umute1();
	 		 #ifdef support_bt_disconnect_pause_mute_dac
	 		 	 dac_mute(0,1);
	 		 #endif
		 	bPowerOnMuteCnt=16;			
		   #endif				
		 #ifdef support_io_det_mute
		 	 bt_automute_sw=7;  // bt 报语音 时不mute
		 #endif
		 #if 1//def support_bt_dac_mute_off
			 dac_mute(0,1);
		 #endif
               //if(is_auto_connect()){}  //可以判断“是回连成功返回1，非回连连接返回0”
               user_ctrl_prompt_tone_play(BT_STATUS_CONNECTED,NULL);
              #if LED_SHOW_BT
                #ifdef LED_BT_ICON_CONNECT_NOT_FLASH
				 setLedLight(LED_SHOW_BT,led_mode_on,0);
                #else
				setLedLight(LED_SHOW_BT,led_mode_flash_slow,0);
                #endif
              #else
			   // led_fre_set(0);
              #endif
              #if UI_ENABLE
			  led7_var.bBtIfConnect=TRUE;
              #endif
               break;
            case BT_STATUS_DISCONNECT:
		 #ifdef support_bt_disconnect_pause_mute_dac
		 	 dac_mute(0,1);
			 bPowerOnMuteCnt=7;
		 #endif
		 #ifdef support_io_det_mute
		 	 bt_automute_sw=7;  // bt 报语音 时不mute
		 #endif
		 #if 1//def support_bt_dac_mute_off
			 dac_mute(0,1);
		 #endif
				
               user_ctrl_prompt_tone_play(BT_STATUS_DISCONNECT,NULL);
               #if LED_SHOW_BT
				 setLedLight(LED_SHOW_BT,led_mode_flash_fast,0);
               #else
				 //led_fre_set(5);
               #endif
              #if UI_ENABLE
			   led7_var.bBtIfConnect=FALSE;
              #endif
             #ifndef BT_NOT_SHOW_ICON_PLAY_PAUSE
              #if LED_PAUSE
				 LED_STATUS&=~LED_PLAY;
				 LED_STATUS&=~LED_PAUSE;
              #endif
             #endif
            #if BT_BACKMODE
			 os_taskq_post_event("MainTask", 1, SYS_EVENT_BT_BACKDISCON);
            #endif
               break;
            case BT_STATUS_PHONE_INCOME:
                user_send_cmd_prepare(USER_CTRL_HFP_CALL_CURRENT,0,NULL);//发命令获取电话号码
                user_ctrl_prompt_tone_play(BT_STATUS_PHONE_INCOME,NULL);
#if REC_EN
                set_sys_freq(BT_REC_Hz);
#endif
               break;
            case BT_STATUS_PHONE_OUT:
#if REC_EN
                set_sys_freq(BT_REC_Hz);
#endif
               break;

#if BT_PHONE_NUMBER
            case BT_STATUS_PHONE_NUMBER:
               user_ctrl_prompt_tone_play(BT_STATUS_PHONE_NUMBER,NULL);
               break;
#endif
            case BT_STATUS_PHONE_ACTIVE:
                user_val->play_phone_number_flag = 0;
                if(user_val->phone_prompt_tone_playing_flag)
                {
                    play_sel_stop();
                    user_val->phone_prompt_tone_playing_flag = 0;
                }
                break;
            case BT_STATUS_PHONE_HANGUP:
               user_val->play_phone_number_flag = 0;
               user_val->is_phone_number_come = 0;
               if(user_val->phone_prompt_tone_playing_flag)
               {
                   play_sel_stop();
                   user_val->phone_prompt_tone_playing_flag = 0;
               }

                if(get_suspend_flag()) //后台电话回来，电话完了自动退出
                {
                    hook_btstack_suspend();
                }
#if REC_EN
               os_taskq_post(OS_TASK_SELF, 1, MSG_REC_STOP);
               set_sys_freq(SYS_Hz);
#endif
               break;
            default:
               break;
        }
    }
}


void btstack_key_handler(void *ptr,int key)
{
	switch(key){
        case MSG_BT_PP:
            // puts("MSG_BT_PP\n");
            if ((get_call_status() == BT_CALL_OUTGOING) ||
				(get_call_status() == BT_CALL_ALERT) ){
				 user_send_cmd_prepare(USER_CTRL_HFP_CALL_HANGUP,0,NULL);
			}else if(get_call_status() == BT_CALL_INCOMING){
				 user_send_cmd_prepare(USER_CTRL_HFP_CALL_ANSWER,0,NULL);
			}else if(get_call_status() == BT_CALL_ACTIVE){
			    user_send_cmd_prepare(USER_CTRL_SCO_LINK,0,NULL);
			}else{

				 #ifdef  SUPPORT_ZY_SA_VOICE
					 #if !defined suppport_bt_pp_no_voice &&  !defined support_off_bt_pp_prev_next_voice
		 				 #ifdef SUPPORT_DOUBLE_VOICE
		 					if(IsVoiceEnable==1)
		 					{
		 						{
		 							  if(BT_MUSIC_STATUS_STARTING != a2dp_get_status())    
		 							  { 
		 							  	bt_prompt_play(BPF_PLAY_MP3);							   		
		 							  }
		 							  else
		 							  {
		 							  	bt_prompt_play(BPF_PAUSE_MP3);										
		 							  }
		 						}
		 					}
		 					else	 if(IsVoiceEnable==2)
		 					{
		 						{
		 							  if(BT_MUSIC_STATUS_STARTING != a2dp_get_status())    
		 							  { 
		 							  	bt_prompt_play(BPF_PLAY_MP3_EN);							   		
		 							  }
		 							  else
		 							  {
		 							  	bt_prompt_play(BPF_PAUSE_MP3_EN);										
		 							  }
		 						}
		 					}						
		 				 #else
		 				 
		 					if(IsVoiceEnable)					
		 					{
		 //						if (BT_STATUS_PLAYING_MUSIC == get_bt_connect_status())             
		 						{
		 							  if(BT_MUSIC_STATUS_STARTING != a2dp_get_status())    
		 							  { 
		 							  	bt_prompt_play(BPF_PLAY_MP3);							   		
		 							  }
		 							  else
		 							  {
		 							  	bt_prompt_play(BPF_PAUSE_MP3);										
		 							  }
		 						}
		 					}
		 				#endif				
					 #endif				
				 #endif				

			
				user_send_cmd_prepare(USER_CTRL_AVCTP_OPID_PLAY,0,NULL);
			}
            break;

        case MSG_BT_NEXT_FILE:
            // puts("MSG_BT_NEXT_FILE\n");
            user_send_cmd_prepare(USER_CTRL_AVCTP_OPID_NEXT,0,NULL);

		 #if !defined SUPPORT_ONLY_MODE_VOICE &&  !defined support_off_bt_pp_prev_next_voice
		 #ifdef  SUPPORT_ZY_SA_VOICE
		 
	            if((BT_STATUS_CONNECTING == get_bt_connect_status())   ||
	               (BT_STATUS_TAKEING_PHONE == get_bt_connect_status())||
	               (BT_STATUS_PLAYING_MUSIC == get_bt_connect_status()))/*连接状态*/		 
	            	{
				 #ifdef SUPPORT_DOUBLE_VOICE
					if(IsVoiceEnable==1)
					{
		           			 bt_prompt_play(BPF_NEXT_MP3);	 
		           		}
					else if(IsVoiceEnable==2)
					{
		           			 bt_prompt_play(BPF_NEXT_MP3_EN);
		           		}						
				#else			 
					if(IsVoiceEnable)
					{
		           		 bt_prompt_play(BPF_NEXT_MP3);	 
		           		}
				#endif
	            	}
		#endif	
		#endif	
		
            break;

        case MSG_BT_PREV_FILE:
            // puts("MSG_BT_PREV_FILE\n");
            user_send_cmd_prepare(USER_CTRL_AVCTP_OPID_PREV,0,NULL);
			
		 #ifdef  SUPPORT_ZY_SA_VOICE
	            if((BT_STATUS_CONNECTING == get_bt_connect_status())   ||
	               (BT_STATUS_TAKEING_PHONE == get_bt_connect_status())||
	               (BT_STATUS_PLAYING_MUSIC == get_bt_connect_status()))/*连接状态*/		 
	            		{
	            		
			 #if !defined SUPPORT_ONLY_MODE_VOICE &&  !defined support_off_bt_pp_prev_next_voice
			 
				 #ifdef SUPPORT_DOUBLE_VOICE
				if(IsVoiceEnable==1)
					{
		           			 bt_prompt_play(BPF_PREV_MP3);	 
		           		}
					else if(IsVoiceEnable==2)
					{
		           			 bt_prompt_play(BPF_PREV_MP3_EN);
		           		}						
				#else			 
					if(IsVoiceEnable)
					{
		           		 bt_prompt_play(BPF_PREV_MP3);	 
		           		}
				#endif
				#endif

				}
		#endif			
			
            break;
         case MSG_BT_MUSIC_EQ:
            #ifdef EQ_SEQUENCE_ADJ_ANYWAY
				 bt_eq_sequence_mode++;
				 if(bt_eq_sequence_mode>=eq_max)bt_eq_sequence_mode=eq_normal;
				 switch(bt_eq_sequence_mode){
				   case eq_normal:
					   user_val->bt_eq_mode=0;
					   break;
				   case eq_pop:
					   user_val->bt_eq_mode=2;
					   break;
				   case eq_rock:
					   user_val->bt_eq_mode=1;
					   break;
				   case eq_jazz:
					   user_val->bt_eq_mode=4;
					   break;
				   case eq_classic:
					   user_val->bt_eq_mode=3;
					   break;
				   case eq_country:
					   user_val->bt_eq_mode=5;
					   break;
				   case eq_bass:
					   user_val->bt_eq_mode=6;
					   break;
				   default:
					   break;
				 }
             #else
             user_val->bt_eq_mode++;
             if(user_val->bt_eq_mode > 5)
             {
            	 user_val->bt_eq_mode = 0;
             }
            #endif			  
            // puts("MSG_BT_EQ\n");
            __set_a2dp_music_eq(user_val->bt_eq_mode);
            
           #ifdef LED_SHOW_BT_EQ	           
			 led7_var.bBtEqMode=user_val->bt_eq_mode;
            UI_menu(MENU_EQ);
           #endif
            break;
        case MSG_BT_ANSWER_CALL:
            // puts("MSG_BT_ANSWER_CALL\n");
            if(get_call_status() == BT_CALL_INCOMING){
                user_send_cmd_prepare(USER_CTRL_HFP_CALL_ANSWER,0,NULL);
            }
            break;

        case MSG_BT_CALL_LAST_NO:
            // puts("MSG_BT_CALL_LAST_NO\n");
            if(get_call_status()!=BT_CALL_HANGUP)
                break;
            if(get_last_call_type()== BT_CALL_OUTGOING)
            {
                user_send_cmd_prepare(USER_CTRL_HFP_CALL_LAST_NO,0,NULL);
            }else if(get_last_call_type() == BT_CALL_INCOMING){
                user_send_cmd_prepare(USER_CTRL_DIAL_NUMBER,user_val->phone_num_len,
                                                            user_val->income_phone_num);
            }
            break;

        case MSG_BT_CALL_REJECT:
            // puts("MSG_BT_CALL_REJECT\n");
            if(get_call_status() != BT_CALL_HANGUP)
            {
                user_send_cmd_prepare(USER_CTRL_HFP_CALL_HANGUP,0,NULL);
            }
            break;

        case MSG_BT_CALL_CONTROL:   //物理按键少的时候合用
            if(get_call_status() != BT_CALL_HANGUP)
            {
                user_send_cmd_prepare(USER_CTRL_HFP_CALL_HANGUP,0,NULL);
            }
            else
            {
                if(get_last_call_type() == BT_CALL_OUTGOING)
                {
                    user_send_cmd_prepare(USER_CTRL_HFP_CALL_LAST_NO,0,NULL);
                }else if(get_last_call_type() == BT_CALL_INCOMING){
                    user_send_cmd_prepare(USER_CTRL_DIAL_NUMBER,user_val->phone_num_len,
                                                                user_val->income_phone_num);
                }
            }
            break;

        case MSG_BT_CONNECT_CTL:
            // puts("MSG_BT_CONNECT_CTL\n");
            if((BT_STATUS_CONNECTING == get_bt_connect_status())   ||
               (BT_STATUS_TAKEING_PHONE == get_bt_connect_status())||
               (BT_STATUS_PLAYING_MUSIC == get_bt_connect_status()))/*连接状态*/
            {
                // puts("bt_disconnect\n");/*手动断开连接*/
                user_send_cmd_prepare(USER_CTRL_DISCONNECTION_HCI,0,NULL);
            }
            else
            {
                // puts("bt_connect\n");/*手动连接*/
                user_send_cmd_prepare(USER_CTRL_START_CONNECTION,0,NULL);
            }
            break;
        case MSG_BT_HID_CTRL:
            // puts("MSG_BT_HID_CTRL\n");
            if(get_curr_channel_state() & HID_CH)
            {
                user_send_cmd_prepare(USER_CTRL_HID_DISCONNECT,0,NULL);
            }else{
                user_send_cmd_prepare(USER_CTRL_HID_CONN,0,NULL);
            }

            break;
        case MSG_BT_HID_TAKE_PIC:
            // puts("MSG_BT_HID_TAKE_PIC\n");
            if(get_curr_channel_state() & HID_CH)
            {
                 user_send_cmd_prepare(USER_CTRL_HID_BOTH,0,NULL);
            }
            break;

        case MSG_LOW_POWER:
            // puts("bt_low_power\n");
            bt_prompt_play(BPF_LOW_POWER_MP3);
            break;

     #ifdef  support_power_off_tone
     	case MSG_VOICE_POWER_OFF:
	 	power_on_flag=0;
		power_off_timer=3;
		bt_prompt_play(BPF_POWER_OFF_MP3);						
        	break;		 
     #endif			
#ifdef SUPPORT_VOICE_ONOFF_VOICE	

 		case MSG_BT_VOICE_ONOFF:
			
//		 	led7_var.bIfHaveVoice=!led7_var.bIfHaveVoice;		
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
	 			 #ifdef support_bt_disconnect_pause_mute_dac
	 				 dac_mute(0,1);
					 bPowerOnMuteCnt=7;				 				 
	 			 #endif			
		 		 #ifdef support_io_det_mute
		 		 	 bt_automute_sw=7;  // bt 报语音 时不mute
		 		 #endif				 
					bt_prompt_play(BPF_VOICE_ON_MP3);
				}
				else
				{
				 #ifdef LED_SHOW_ONOFF
				 	UI_menu(MENU_ONOFF);
				 #endif
		 		 #ifdef support_voice_onoff_mem
		 		 	vm_write_api(VM_SYS_EQ,&led7_var.bIfHaveVoice);
		 		 #endif
	 			 #ifdef support_bt_disconnect_pause_mute_dac
	 				 dac_mute(0,1);
					 bPowerOnMuteCnt=7;				 
	 			 #endif										 
					 bt_prompt_play(BPF_VOICE_OFF_MP3);
				}
						
				 

			break; 
#endif


#ifdef  SUPPORT_ZY_SA_VOICE

		case MSG_BT_VOICE_SWITCH:	


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
		 					bt_prompt_play(BPF_VOICE_OFF_MP3);
						 else
		 					bt_prompt_play(BPF_VOICE_OFF_MP3_EN);						 	
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
		 					bt_prompt_play(BPF_VOICE_ON_MP3);
						 else
		 					bt_prompt_play(BPF_VOICE_ON_MP3_EN);						 			 				 
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
		 		 #ifdef support_voice_onoff_mem
		 		 	vm_write_api(VM_SYS_EQ,&IsVoiceEnable);
		 		 #endif
				
			 	led7_var.bIfHaveVoice=IsVoiceEnable;
			 #ifdef LED_SHOW_ONOFF
			 	UI_menu(MENU_ONOFF); 
			 #endif	
			 
				bt_prompt_play(BPF_VOICE_OFF_MP3);
			}
			else
			{
				IsVoiceEnable = 1;
		 		 #ifdef support_voice_onoff_mem
		 		 	vm_write_api(VM_SYS_EQ,&IsVoiceEnable);
		 		 #endif
				
			 	led7_var.bIfHaveVoice=IsVoiceEnable;
			 #ifdef LED_SHOW_ONOFF
			 	UI_menu(MENU_ONOFF); 
			 #endif				
				
				bt_prompt_play(BPF_VOICE_ON_MP3);
			}
			
		#endif

			break;
 #ifndef SUPPORT_ONLY_MODE_VOICE

	    case MSG_VOICE_MUTE:

		if(IsVoiceEnable)
	    	{
  			 #ifdef SUPPORT_DOUBLE_VOICE
				if(IsVoiceEnable==2)
		    			bt_prompt_play(BPF_MUTE_MP3_EN);
				else
			 #endif    		    		    				 			 
	    			bt_prompt_play(BPF_MUTE_MP3);			    		    				 	    		    		    	
	    	}
	    	break;

	    case MSG_VOICE_VOLUME_PLUS:

			if(IsVoiceEnable)
	    	{
  			 #ifdef SUPPORT_DOUBLE_VOICE
				if(IsVoiceEnable==2)
		    			bt_prompt_play(BPF_VL_INC_MP3_EN);
				else
			 #endif    	
				#ifdef SUPPORT_SMM_SA_VOICE			 	
		 	 	{
					if(dac_var.cur_sys_vol_l ==30) 			
		    				bt_prompt_play(BPF_VL_MAX_MP3);			    		    				 	    		    		    					 
					else		 	 	
		    				bt_prompt_play(BPF_VL_INC_MP3);			    		    				 	    		    		    					 
		 	 	}
				#else
				
		    				bt_prompt_play(BPF_VL_INC_MP3);			    		    				 	    		    		    					 
				#endif			 
			}
	    	break;

	    case MSG_VOICE_VOLUME_MINUS:

			if(IsVoiceEnable)
	    	{
  			 #ifdef SUPPORT_DOUBLE_VOICE
				if(IsVoiceEnable==2)
		    			bt_prompt_play(BPF_VL_DEC_MP3_EN);
				else
			 #endif    		    		    				 			 
	    			bt_prompt_play(BPF_VL_DEC_MP3);			    		    				 	    		    		    	
	    	}
	    	break;

	    case MSG_MAX_VOICE:

			if(IsVoiceEnable)
	    	{
  			 #ifdef SUPPORT_DOUBLE_VOICE
				if(IsVoiceEnable==2)
		    			bt_prompt_play(BPF_VL_MAX_MP3_EN);
				else
			 #endif    		    		    				 			 
	    			bt_prompt_play(BPF_VL_MAX_MP3);			    		    				 	    	
	    	}
	    	break;
			
#endif
#endif

#ifdef SUPPORT_KEY_6_VOICE
            case MSG_VOICE_YESE:
	    			bt_prompt_play(BPF_VL_MAX_YESE);	
		break;
            case MSG_VOICE_END:
	    			bt_prompt_play(BPF_VL_MAX_END);	
		break;
            case MSG_VOICE_APPLAUD:
	    			bt_prompt_play(BPF_VL_MAX_APPLAUD);	
		break;
            case MSG_VOICE_GUN:
	    			bt_prompt_play(BPF_VL_MAX_GUN);	
		break;
            case MSG_VOICE_ZXC:
	    			bt_prompt_play(BPF_VL_MAX_ZXC);	
		break;
           case MSG_VOICE_BEST_PARTNER:
	    			bt_prompt_play(BPF_VL_MAX_BEST_PARTNER);	
		break;
	
#endif

        case MSG_HALF_SECOND:
            //// puts(" BT_H ");

	 	      #ifdef  support_power_off_tone
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
	 	 	 #endif			
			
            if((BT_STATUS_CONNECTING == get_bt_connect_status())   ||
               (BT_STATUS_TAKEING_PHONE == get_bt_connect_status())||
               (BT_STATUS_PLAYING_MUSIC == get_bt_connect_status()))/*连接状态*/
            {
                if(BT_MUSIC_STATUS_STARTING == a2dp_get_status())       /*播歌状态*/
                {
                
                
                     #ifdef LED_SHOW_BT
                       if(!bBtPlayFlag){
                        bBtPlayFlag=TRUE;

			     #if defined ONLY_POWER_ON_MUTE &&defined support_power_no_media_to_bt 	  	
				 bPowerOnMuteCnt=1;
			     #endif						
				 
			 #ifdef support_bt_disconnect_pause_mute_dac
				 dac_mute(0,1);
			 #endif						
                       #ifdef LED_BT_ICON_CONNECT_NOT_FLASH
	          			 setLedLight(LED_SHOW_BT,led_mode_on,0);
                       #else
	        			 setLedLight(LED_SHOW_BT,led_mode_flash_slow,0);
            		   #endif
            		   }
                     #else
                    //led_fre_set(15);                                /*播歌慢闪*/
                     #endif 
					 
                 #ifndef BT_NOT_SHOW_ICON_PLAY_PAUSE
                     #if LED_PLAY
                     LED_STATUS|=LED_PLAY;
					 LED_STATUS&=~LED_PAUSE;
                     #endif
                 #endif
                     #ifdef APPLE_MOBILE_PAUSE_NOT_FLASH_LIGHT_INTIME                                            
			if(dac_digt_ctl.mute)
			{		
                           #ifndef BT_NOT_SHOW_ICON_PLAY_PAUSE
                               #if LED_PLAY
   						   LED_STATUS&=~LED_PLAY;
   						   LED_STATUS|=LED_PAUSE;
                              #endif
                           #endif
						   
                           #ifdef BT_NOT_PLAY_IO_MUTE						   
                            #ifdef PA_ENABLE
                             #ifdef ONLY_POWER_ON_MUTE
                                 #ifdef BT_MODE_ONLY_MUTE_DAC
							     dac_mute(1,1);								
                                 #else
  							     pa_mute1();
  							     #endif
                             #else
                             		 pa_mute();
                             #endif
                            #endif
                           #endif
						   
                             #if 0//def LED_SHOW_BT
                             bBtPlayFlag=FALSE;
				 setLedLight(LED_SHOW_BT,led_mode_on,0);
				 #endif
	  			}
				else
	  			{
					 #ifdef BT_NOT_PLAY_IO_MUTE
					 #ifdef PA_ENABLE
					 #ifdef ONLY_POWER_ON_MUTE
					 #ifdef BT_MODE_ONLY_MUTE_DAC
					 	dac_mute(0,1);
					 #else
					 	pa_umute1();
					 #endif
					 #else
					 	pa_umute();
					 #endif
					 #endif
					 #endif
	  			}
                     #endif	
					 
			#ifdef support_io_det_mute
					pa_umute1();
			#endif
		 
                }
                else
                {
	               #ifdef LED_SHOW_BT
	               bBtPlayFlag=FALSE;
	 			   setLedLight(LED_SHOW_BT,led_mode_on,0);
	                #else
	 			   //led_fre_set(0);								 /*暂停常亮*/
	               #endif
		 			  
	 		 #ifdef support_bt_disconnect_pause_mute_dac
	 			 if(bPowerOnMuteCnt==0)
	 				{
	 			 		dac_mute(1,1);
	 				}
	 		 #endif	
			 
		           #ifndef BT_NOT_SHOW_ICON_PLAY_PAUSE
		               #if LED_PAUSE
		 			  LED_STATUS&=~LED_PLAY;
		 			  LED_STATUS|=LED_PAUSE;
		               #endif
		           #endif
				   
			 
			 #ifdef support_io_det_mute
			   if((auto_mute_sw)&&(bt_automute_sw==0))
			   {
				pa_mute1();
			   }
			 #endif
				   
		               #ifdef BT_NOT_PLAY_IO_MUTE
		                #ifdef PA_ENABLE
		                 #ifdef ONLY_POWER_ON_MUTE
		                    #ifdef BT_MODE_ONLY_MUTE_DAC
		 				  dac_mute(1,1);
		                   #else
		 				  pa_mute1();
		 				  #endif
		                 #else
		    			   pa_mute();
		    			    #endif
		                #endif
		               #endif
                }
            }
            else
	      {
	               #ifdef BT_NOT_PLAY_IO_MUTE
				if(!bBtIOMuteDelayCnt)
				{			 
		                  #ifdef PA_ENABLE
		                   #ifdef ONLY_POWER_ON_MUTE
		                       #ifdef BT_MODE_ONLY_MUTE_DAC
		   				       dac_mute(1,1);
		                       #else
							   pa_mute1();
					   #endif
		                    #else
							 pa_mute();
		                   #endif
		                  #endif
	                  }                  
	              #endif

			 #ifdef support_io_det_mute
			   if((auto_mute_sw)&&(bt_automute_sw==0))
			   {
				pa_mute1();
			   }
			 #endif
				  
			 #ifdef support_bt_disconnect_pause_mute_dac
				 if(bPowerOnMuteCnt==0)
					{
				 		dac_mute(1,1);
					}
			 #endif
			  
	                #if BT_BACKMODE                   
					if(!bFirstPowerFlag){
	   				bFirstPowerFlag=TRUE;
					   os_taskq_post_event("MainTask", 1, SYS_EVENT_BT_BACKDISCON);
					   }
	                #endif
                   }


			 #ifdef support_io_det_mute
				 if(bt_automute_sw>1)
				 	 bt_automute_sw--;  // bt 报语音 时不mute
				else if(bt_automute_sw==1)
				 	 bt_automute_sw=0;  // bt 报语音 时不mute				 	
			 #endif

                   
            #ifdef BT_NOT_PLAY_IO_MUTE
				 if(bBtIOMuteDelayCnt){
				 bBtIOMuteDelayCnt--;				 
                 #ifdef PA_ENABLE                 
                   #ifdef BT_MODE_ONLY_MUTE_DAC
  				   dac_mute(0,1);
                   #else
				 pa_umute();
				 #endif
				 #endif
				 if(bBtIOMuteDelayCnt==0)
				 {
                  #ifdef PA_ENABLE
                   #ifdef ONLY_POWER_ON_MUTE
                      #ifdef BT_MODE_ONLY_MUTE_DAC
				     dac_mute(1,1);
                     #else
					  pa_mute1();
					 #endif
                   #else
					 pa_mute();
                  #endif
                 #endif
                }
            }
           #endif
           
           UI_menu(MENU_MAIN);
           UI_menu(MENU_HALF_SEC_REFRESH);
            break;

        case MSG_BT_STACK_STATUS_CHANGE:
            //该消息比较特殊，不属于按键产生，是协议栈状态变化产生。
            // puts("MSG_BT_STACK_STATUS_CHANGE\n");
            btstack_status_change_deal(NULL);
            break;
        case SYS_EVENT_DEL_TASK:
            // puts("SYS_EVENT_DEL_TASK\n");
            update_bt_current_status(BT_STATUS_SUSPEND,0);
            //断开和关闭协议栈
            user_send_cmd_prepare(USER_CTRL_POWER_OFF,0,NULL);
            h4_upload_wakeup();
            //删除LMP线程
            delete_lmp_task();
            // puts("del lmp ok\n");
            //删除协议栈
            delete_stack_task();
            // puts("del stack ok\n");
            play_sel_stop();
            //删除消息线程
            if (os_task_del_req_name(OS_TASK_SELF) == OS_TASK_DEL_REQ)
            {
                // puts("del_ket_masg");
                exit_rec_api(&rec_bt_api);
                os_task_del_res_name(OS_TASK_SELF); 	//确认可删除，此函数不再返回
            }
            break;
		default:
			break;
	}
}
#if REC_EN
void bt_rec_msg_del(int *msg)
{
    if((BT_STATUS_TAKEING_PHONE != get_bt_connect_status())&&(msg[0] == MSG_REC_START))//非通话按
    {
        return;
    }

    rec_msg_del(&rec_bt_api, msg);
}
#endif
/*消息处理*/
void TaskBtMsgStack(void *p_arg)
{
    p_arg = p_arg;

    os_sem_create(&tone_manage_semp, 0);

    while(1)
    {
        int msg[3];
		u32 res;
        //res = os_taskq_pend(0,1, &msg);
        res = os_taskq_pend(0, ARRAY_SIZE(msg), msg);
        if(res != OS_NO_ERR)
        {
            msg[0] = 0xff;
        }
#ifdef BT_TESTER
        btstack_key_handler_for_bttest(NULL,msg[0]);
#else
        btstack_key_handler(NULL, msg[0]);
#endif
        h4_upload_wakeup();
#if REC_EN
        bt_rec_msg_del(msg);
#endif
    }

}

/*主要处理上电或者有些情况蓝牙处于不能切换模式状态*/
int msg_mask_off_in_bt()
{
    //printf("bt_busy_flag::%d",stack.bt_busy_flag);
#if BT_BACKMODE
    return is_bt_stack_cannot_exist();
#else
    return false;
#endif
}

/*蓝牙协议栈建立线程时回调接口*/
void btstack_task_create()
{
    // puts("\n************************BLUETOOTH TASK********************\n");
#ifndef BT_NOT_USE_INIT_VOICE
  #if defined ONLY_POWER_ON_MUTE &&defined support_power_no_media_to_bt 
	 pa_umute1();
	bPowerOnMuteCnt=10;
  #endif
  
#ifdef support_bt_disconnect_pause_mute_dac
	 dac_mute(0,1);
#endif
 #ifdef support_io_det_mute
 	 bt_automute_sw=7;  // bt 报语音 时不mute
 #endif

    user_ctrl_prompt_tone_play(BT_STATUS_POWER_ON,NULL);
#endif    

#ifdef BT_NOT_PLAY_IO_MUTE
		 bBtIOMuteDelayCnt=6;
#endif
#ifdef DURING_FM_EXITING_TASK_NOT_RESPOND_KEY_MSG
		bExitFMStateCnt=2;
#endif

#if LED_SHOW_MP3
		setLedLight(LED_SHOW_MP3,led_mode_off,0);
#endif
#if LED_SHOW_AUX
		setLedLight(LED_SHOW_AUX,led_mode_off,0);
#endif
#if LED_SHOW_FM
		setLedLight(LED_SHOW_FM,led_mode_off,0);
#endif
	
#ifdef LED_SHOW_BT
		setLedLight(LED_SHOW_BT,led_mode_flash_fast,0);
#else
		//led_fre_set(5);
#endif
}

/*通过任务切换进入蓝牙时回调接口*/
void enter_btstack_task()
{
    // puts("btstack_init\n");
#ifdef BT_TESTER
    key_msg_register("btmsg",bt_test_ad_table,bt_test_io_table,bt_test_ir_table,NULL);
#else
   #if KEY_IO_EN
    key_msg_register("btmsg",bt_ad_table,bt_io_table,bt_ir_table,NULL);
#elif LED_KEY_MAX
	 #if KEY_AD_EN
	 	key_msg_register("btmsg",bt_led_table,bt_ad_table,NULL,bt_ir_table,NULL);
	 #else
	 	key_msg_register("btmsg",bt_led_table,NULL,bt_io_table,bt_ir_table,NULL);
	 #endif   
   #else
    key_msg_register("btmsg",bt_ad_table,NULL,bt_ir_table,NULL);
   #endif
#endif
    dac_channel_on(BT_CHANNEL, FADE_OFF);
#if MP3_VOL_MAX||FM_VOL_MAX
	if(bVolMaxChangeToSmallVolMax>=0)
	dac_var.cur_sys_vol_l=bVolMaxChangeToSmallVolMax;
	dac_var.cur_sys_vol_r = dac_var.cur_sys_vol_l;
#if defined(PA_EN) 
	pa_umute();
#endif 			
	set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);	
#elif defined(BT_VOL_MAX)
	if(dac_var.cur_sys_vol_l>BT_VOL_MAX)
	dac_var.cur_sys_vol_l=BT_VOL_MAX;
	dac_var.cur_sys_vol_r = dac_var.cur_sys_vol_l;
#if defined(PA_EN) 
	pa_umute();
#endif 			
	set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);
#elif defined(support_mode_change_vol_min_to_min)
	if(dac_var.cur_sys_vol_l<support_mode_change_vol_min_to_min)
	dac_var.cur_sys_vol_l=support_mode_change_vol_min_to_min;
	dac_var.cur_sys_vol_r = dac_var.cur_sys_vol_l;
#if defined(PA_EN) 
	pa_umute();
#endif 			
	set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);
#endif 
   // set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);
#ifdef SUPPORT_PT2313
	Pt2313_ChangSource(Aud_SwBt);
#endif
#ifdef support_amP_ab_d
	Set_amp_ab_d_out() ;
	Set_AMP_IS_D();	 
#endif 

#ifdef support_sound_4052_control
#if defined sound_4052_io_mode_6 ||defined sound_4052_io_mode_5
	AC4052_IS_BT(); 
#endif
#endif

#ifdef KOK_DETECT_AUTO_VOL_SET		
	 store_vol= dac_var.cur_sys_vol_l;
#endif

#ifdef SUPPORT_USE_ENCODE_AS_MODE_CHANGE	
	bMulitWorkmode=BT_WORK_MODE;
#endif

#ifdef SUPPORT_WOKRMODE
	workmode=BT_WORK_MODE;
#ifdef SUPPORT_MODE_VM
       vm_write_api(VM_SYS_EQ,&workmode);
#endif
#ifdef SUPPORT_MODE_VM
#ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE
bModeOfAuxContained=mode_aux;
#endif
#endif
#endif

#ifdef support_change_mode_bt_icon_off
	exit_bt_sw=0;
#endif

    SET_UI_MAIN(MENU_BT_MAIN);
    UI_menu(MENU_BT_MAIN);
}

extern void no_background_suspend();
extern void background_suspend();
/*通过任务切换退出蓝牙时回调接口*/
void exist_btstack_task()
{
    // puts("----BTSTACK BACKGROUND---\n");

#ifdef support_change_mode_bt_icon_off
	exit_bt_sw=1;
#endif
    dac_channel_off(BT_CHANNEL, FADE_OFF);
#ifndef  EXIT_BT_NOT_SHOW_LOAD
    SET_UI_MAIN(MENU_WAIT);
    UI_menu(MENU_WAIT);
#endif
  #if UI_ENABLE
	   led7_var.bBtIfConnect=FALSE;
  #endif
	
#if BT_BACKMODE
    background_suspend();
#else
    no_background_suspend();
#endif
       #ifdef SUPPORT_MUTE_FLASH
	   b_muteFlag=FALSE;
      #endif

}

u8 auto_connection_counter;
void auto_connected_timeout_handler_user(timer_source_t *ts)
{
    if(get_hci_connect_handle())
    {
        auto_connection_counter = 0;
    }
    else{
        auto_connection_counter--;
        user_send_cmd_prepare(USER_CTRL_START_CONNECTION,0,NULL);
    }
}

void bt_discon_complete_handle(int reason)
{
	if (reason == 0x16){
		hci_connectable_control(1);
		hci_discoverable_control(1);
	} else if(reason == 0x08){
		//connnection timeout
		if(!get_remote_test_flag())
		{
            auto_connection_counter = 10;
            if(get_bt_prev_status() != BT_STATUS_SUSPEND)
            {
                user_send_cmd_prepare(USER_CTRL_START_CONNECTION,0,NULL);
            }
		}
		else
		{
		    auto_connection_counter = 0;
            hci_connectable_control(1);
            update_bt_current_status(0,BT_STATUS_WAITINT_CONN);
		}
	}else if(reason == 0x04){
		//page timeout
		if(!auto_connection_counter){
		    // puts("page timeout\n");
		    if(get_current_search_index() >= 1)
		    {    //继续搜索下一个设备
                 user_send_cmd_prepare(USER_CTRL_START_CONNECTION,0,NULL);
		    }else{
                hci_connectable_control(1);
                update_bt_current_status(0,BT_STATUS_WAITINT_CONN);
		    }
		} else {
		    if(get_bt_prev_status() != BT_STATUS_SUSPEND)
		    {
                auto_connect_timer_register(5000 , auto_connected_timeout_handler_user);
		    }
		}
	} else if(reason == 0x0b){
		//connection exist
		user_send_cmd_prepare(USER_CTRL_START_CONNECTION,0,NULL);
	}
}
