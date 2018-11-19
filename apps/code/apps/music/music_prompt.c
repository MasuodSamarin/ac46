#include "music_prompt.h"
#include "play_sel.h"
#include "voice_prompt.h"
#include "msg.h"
#include "drv_manage.h"
 #ifdef  support_power_off_tone
#include "led.h"
#endif
#include "dac_api.h"

extern u8 usb_in_flag;
extern u8 sd_in_flag;
extern u32 curr_device_using;
#ifdef AFTER_RECORD_PLAY_LAST_RECORDED_FILE
extern u8 bExitRecordModePlayLastRecordedFileFlag;
#endif
#ifdef HANDLER_POWER_ON_DEVICE_VOICE_ERROR
 u8 bPowerOnWithUsbSdFlag=0;
#endif
#ifdef SUPPORT_VOICE_ONOFF_VOICE	
#include "led7_drv.h"
#endif
extern u32  music_play_by_path_rec(MUSIC_OP_API *mapi);
#ifdef  SUPPORT_ZY_SA_VOICE
extern u8 play_mode;
extern u8 eq_mode;
#endif

bool prompt_played,music_prompt_stopped;
PROMPT_MUSIC_STATUS music_prompt_flag;
_DECODE_STATUS dec_status;
extern u32 music_play_api(MUSIC_OP_API *m_op_api,ENUM_DEV_SEL_MODE dev_sel,u32 dev_let,ENUM_FILE_SELECT_MODE file_sel,void *pra);
u32 prompt_play_end(MUSIC_OP_API *m_op_api)
{
#ifdef MUSIC_PROMPT_EN
    u32 err;
    puts("prompt_play_end\n");
    music_prompt_stopped = 1;
	printf("--music_prompt_flag---%d\n",music_prompt_flag)	;
	
    switch(music_prompt_flag)
    {
        case PROMPT_STATUS_PLAY:
			
 #ifndef MUSIC_PROMPT_MODIFY	 
 
	 #ifdef HANDLER_POWER_ON_DEVICE_VOICE_ERROR
	 		if(bPowerOnWithUsbSdFlag<3)
	 		 bPowerOnWithUsbSdFlag++;
	 #endif        
	 
	  #ifdef POWER_ON_WITH_USB_AND_SD_PLAY_USB_FIRST
 			 if(file_operate_get_total_phydev()>1)
			 { 			   
				 #ifdef LED_SHOW_DEVICE_TYPE_SWITCH
					    if(led7_var.blast_play_device==1)
					     {
					 		err = music_play_api(m_op_api,DEV_SEL_SPEC,(u32)sd0,PLAY_BREAK_POINT,&(mapi->dop_api->file_num));
					    }
					  else
				 #endif
				 
				  #if 0//REC_EN
				    #ifdef AFTER_RECORD_PLAY_LAST_RECORDED_FILE
				 			   if(bExitRecordModePlayLastRecordedFileFlag){
				 				 bExitRecordModePlayLastRecordedFileFlag=FALSE; 				 
				 				 //err = music_play_api(mapi,DEV_SEL_SPEC,(u32)usb,PLAY_LAST_FILE,&(mapi->dop_api->file_num));
				 				 err = music_play_by_path_rec(m_op_api);
				 			   }else
				    #endif
				  #endif
	  
			 	 #ifdef HANDLER_POWER_ON_DEVICE_VOICE_ERROR
			 	 	   if(bPowerOnWithUsbSdFlag==2){
			 	 	   //bPowerOnWithUsbSdFlag=0;
			 	 	   curr_device_using=usb;
			 	 	 err = music_play_api(m_op_api,DEV_SEL_SPEC,(u32)usb,PLAY_BREAK_POINT,&(m_op_api->dop_api->file_num));
			 	 	 }else
			 	 #endif
 			 err = music_play_api(m_op_api,DEV_SEL_SPEC,(u32)curr_device_using,PLAY_BREAK_POINT,&(m_op_api->dop_api->file_num));
 			 }
 			 else
	  #endif
 #endif
 
 #if 0//REC_EN
   #ifdef AFTER_RECORD_PLAY_LAST_RECORDED_FILE
			   if(bExitRecordModePlayLastRecordedFileFlag){
				 bExitRecordModePlayLastRecordedFileFlag=FALSE; 				 
				 //err = music_play_api(mapi,DEV_SEL_SPEC,0,PLAY_LAST_FILE,&(mapi->dop_api->file_num));
				 err = music_play_by_path_rec(m_op_api);
			   }else
  #endif
#endif
            err = music_play_api(m_op_api,DEV_SEL_SPEC,0,PLAY_BREAK_POINT,&(m_op_api->dop_api->file_num));
            dec_status = m_op_api->dop_api->dec_api.phy_ops->status;

	 #ifdef MUSIC_PROMPT_MODIFY	 
	 
	 #ifdef SUPPORT_ZY_SA_VOICE	 	 
 	   if(IsVoiceEnable)
	 #endif	   	
	     if(power_on_flag)   
	     {
	           power_on_flag=0;	
	           music_prompt_play(SYS_EVENT_DEV_ONLINE,m_op_api);
	     	}

	 #endif						
			
            break;
		case PROMPT_STATUS_DEVICE:
			err = music_play_api(m_op_api,DEV_SEL_NEXT,0,PLAY_BREAK_POINT,&(m_op_api->dop_api->file_num));
			dec_status = m_op_api->dop_api->dec_api.phy_ops->status;
			break;
        case PROMPT_STATUS_PAUSE:
        case PROMPT_STATUS_STOP:
            break;
        case PROMPT_STATUS_PREV:
            prompt_played = 1;
            os_taskq_post("MusicTask", 1, MSG_MUSIC_PREV_FILE);
            break;
        case PROMPT_STATUS_NEXT:
            prompt_played = 1;
            os_taskq_post("MusicTask", 1, MSG_MUSIC_NEXT_FILE);
            break;
        default:
            break;
    }
    return err;
#endif
}
/*----------------------------------------------------------------------------*/
/**@brief  Music语音播放函数
   @param  file_num：语音文件号
           m_op_api：节目接口
   @return NULL
   @note   u32 music_prompt_play(u8 play_msg,MUSIC_OP_API *m_op_api)
*/
/*----------------------------------------------------------------------------*/
u32 music_prompt_play(u8 play_msg,MUSIC_OP_API *m_op_api)
{

#ifdef MUSIC_PROMPT_EN
    if(music_prompt_stopped)
    {
        puts("music_prompt_stopped ok\n");
        if(!prompt_played)
            music_prompt_stopped = 0;
    }
    else
    {
        puts("music_prompt_stopped err\n");
        return 1;
    }

    switch(play_msg)
    {
        case MSG_LOW_POWER:
            music_prompt_flag = PROMPT_STATUS_PLAY;
            m_op_api->dop_api->dec_api.save_brk = 1;
            music_stop_decoder(m_op_api);
            voice_prompt_play("MusicTask",BPF_LOW_POWER_MP3);
            break;
  	 case MSG_MUSIC_U_SD:
  		music_prompt_flag = PROMPT_STATUS_DEVICE;
  		m_op_api->dop_api->dec_api.save_brk = 1;
  		music_stop_decoder(m_op_api);
	 #ifdef SUPPORT_DOUBLE_VOICE
	 	if(IsVoiceEnable==2)
	 	{
	  		if(sd0==curr_device_using)
	  			voice_prompt_play("MusicTask",BPF_SD_MP3_EN);
	  		else// if(sd_in_flag)
	  			voice_prompt_play("MusicTask",BPF_USB_MP3_EN);
	 	}			
	 	else	 
	 #endif
	 	{
	  		if(sd0==curr_device_using)
	  			voice_prompt_play("MusicTask",BPF_SD_MP3);
	  		else// if(sd_in_flag)
	  			voice_prompt_play("MusicTask",BPF_USB_MP3);
	 	}
  		break;	//PROMPT_STATUS_DEVICE
   	 case SYS_EVENT_DEV_ONLINE:
  		music_prompt_flag = PROMPT_STATUS_PLAY;
  		m_op_api->dop_api->dec_api.save_brk = 1;
  		music_stop_decoder(m_op_api);
	 #ifdef SUPPORT_DOUBLE_VOICE
	 	if(IsVoiceEnable==2)
	 	{
	  		if(sd0==curr_device_using)
	  			voice_prompt_play("MusicTask",BPF_SD_MP3_EN);
	  		else// if(sd_in_flag)
	  			voice_prompt_play("MusicTask",BPF_USB_MP3_EN);
	 	}			
	 	else	 
	 #endif
	 	{
	  		if(sd0==curr_device_using)
	  			voice_prompt_play("MusicTask",BPF_SD_MP3);
	  		else// if(sd_in_flag)
	  			voice_prompt_play("MusicTask",BPF_USB_MP3);
	 	}
  		break;	//PROMPT_STATUS_DEVICE
  #ifdef support_rec_recplay_notice	
     	 case MSG_REC_REPLAY:
  		music_prompt_flag = PROMPT_STATUS_PLAY;
  		m_op_api->dop_api->dec_api.save_brk = 1;
  		music_stop_decoder(m_op_api);
	 #ifdef SUPPORT_DOUBLE_VOICE
	 	if(IsVoiceEnable==2)
	 	{
  			voice_prompt_play("MusicTask",BPF_RECPLAY_MP3_EN);
	 	}			
	 	else	 
	 #endif	
  			voice_prompt_play("MusicTask",BPF_RECPLAY_MP3);
	 
	           prompt_played = 0;
	           music_prompt_stopped = 1;

  		break;	//PROMPT_STATUS_DEVICE
#endif


     #ifdef  support_power_off_tone
     	case MSG_VOICE_POWER_OFF:
        	music_prompt_flag = PROMPT_STATUS_PAUSE;
            m_op_api->dop_api->dec_api.save_brk = 1;
            music_stop_decoder(m_op_api);  
 	   power_on_flag=0;
			
            voice_prompt_play("MusicTask", BPF_POWER_OFF_MP3);  

        	break;		 
     #endif			


#ifdef  SUPPORT_ZY_SA_VOICE
#if  !defined SUPPORT_ONLY_MODE_VOICE

        case MSG_MUSIC_PAUSE:

        	music_prompt_flag = PROMPT_STATUS_PAUSE;
            m_op_api->dop_api->dec_api.save_brk = 1;
            music_stop_decoder(m_op_api);
	 #ifdef SUPPORT_DOUBLE_VOICE
	 	if(IsVoiceEnable==2)
	 	{
  			voice_prompt_play("MusicTask",BPF_PAUSE_MP3_EN);
	 	}			
	 	else	 
	 #endif	            
            voice_prompt_play("MusicTask", BPF_PAUSE_MP3);
            break;

        case MSG_MUSIC_PLAY:

        	music_prompt_flag = PROMPT_STATUS_PLAY;
            m_op_api->dop_api->dec_api.save_brk = 1;
            music_stop_decoder(m_op_api);
	 #ifdef SUPPORT_DOUBLE_VOICE
	 	if(IsVoiceEnable==2)
	 	{
  			voice_prompt_play("MusicTask",BPF_PLAY_MP3_EN);
	 	}			
	 	else	 
	 #endif	            			
            voice_prompt_play("MusicTask", BPF_PLAY_MP3);
            break;
            
        case MSG_MUSIC_NEXT_FILE:	

        	 music_prompt_flag = PROMPT_STATUS_PLAY;
            m_op_api->dop_api->dec_api.save_brk = 1;
            music_stop_decoder(m_op_api);
	 #ifdef SUPPORT_DOUBLE_VOICE
	 	if(IsVoiceEnable==2)
	 	{
  			voice_prompt_play("MusicTask",BPF_NEXT_MP3_EN);
	 	}			
	 	else	 
	 #endif	            			            
            voice_prompt_play("MusicTask", BPF_NEXT_MP3);
	           prompt_played = 0;
	           music_prompt_stopped = 1;
			   
            break;

        case MSG_MUSIC_PREV_FILE:

        	music_prompt_flag = PROMPT_STATUS_PLAY;
            m_op_api->dop_api->dec_api.save_brk = 1;
            music_stop_decoder(m_op_api);
	 #ifdef SUPPORT_DOUBLE_VOICE
	 	if(IsVoiceEnable==2)
	 	{
  			voice_prompt_play("MusicTask",BPF_PREV_MP3_EN);
	 	}			
	 	else	 
	 #endif	            			                        
            voice_prompt_play("MusicTask", BPF_PREV_MP3);
	           prompt_played = 0;
	           music_prompt_stopped = 1;

		   break;    

		case MSG_MUSIC_RPT:

			music_prompt_flag = PROMPT_STATUS_PLAY;
            m_op_api->dop_api->dec_api.save_brk = 1;
            music_stop_decoder(m_op_api);
            
	if(play_mode == REPEAT_ALL)
            {            	
		 	 #ifdef SUPPORT_DOUBLE_VOICE
		 	 	if(IsVoiceEnable==2)
		 	 	{
		   			voice_prompt_play("MusicTask",BPF_REP_ALL_MP3_EN);
		 	 	}			
		 	 	else	 
		 	 #endif	            			                                    
				voice_prompt_play("MusicTask", BPF_REP_ALL_MP3);
            } 
            else
            {
		 	 #ifdef SUPPORT_DOUBLE_VOICE
		 	 	if(IsVoiceEnable==2)
		 	 	{
		   			voice_prompt_play("MusicTask",BPF_REP_ONE_MP3_EN);
		 	 	}			
		 	 	else	 
		 	 #endif	            			                                                
				voice_prompt_play("MusicTask", BPF_REP_ONE_MP3);
            }
            break;

		case MSG_MUSIC_EQ:	

		music_prompt_flag = PROMPT_STATUS_PLAY;
            	m_op_api->dop_api->dec_api.save_brk = 1;
            	music_stop_decoder(m_op_api);

		if(eq_mode == 0)	
	            {
		 	 #ifdef SUPPORT_DOUBLE_VOICE
		 	 	if(IsVoiceEnable==2)
		 	 	{
		   			voice_prompt_play("MusicTask",BPF_NORMAL_MP3_EN);
		 	 	}			
		 	 	else	 
		 	 #endif	            			                                                	            
	            	voice_prompt_play("MusicTask", BPF_NORMAL_MP3);
	            }
	            else if(eq_mode == 1)
	            {
		 	 #ifdef SUPPORT_DOUBLE_VOICE
		 	 	if(IsVoiceEnable==2)
		 	 	{
		   			voice_prompt_play("MusicTask",BPF_ROCK_MP3_EN);
		 	 	}			
		 	 	else	 
		 	 #endif	            			                                                	            	            
	            	voice_prompt_play("MusicTask", BPF_ROCK_MP3);
	            }
	            else if(eq_mode == 2)
	            {
		 	 #ifdef SUPPORT_DOUBLE_VOICE
		 	 	if(IsVoiceEnable==2)
		 	 	{
		   			voice_prompt_play("MusicTask",BPF_POP_MP3_EN);
		 	 	}			
		 	 	else	 
		 	 #endif	            			                                                	            
	            
	            	voice_prompt_play("MusicTask", BPF_POP_MP3);
	            }
	            else if(eq_mode == 3)
	            {
		 	 #ifdef SUPPORT_DOUBLE_VOICE
		 	 	if(IsVoiceEnable==2)
		 	 	{
		   			voice_prompt_play("MusicTask",BPF_CLASS_MP3_EN);
		 	 	}			
		 	 	else	 
		 	 #endif	            			                                                	            
	            
	            	voice_prompt_play("MusicTask", BPF_CLASS_MP3);
	            }
	            else if(eq_mode == 4)
	            {
		 	 #ifdef SUPPORT_DOUBLE_VOICE
		 	 	if(IsVoiceEnable==2)
		 	 	{
		   			voice_prompt_play("MusicTask",BPF_JAZZ_MP3_EN);
		 	 	}			
		 	 	else	 
		 	 #endif	            			                                                	            
	            
	            	voice_prompt_play("MusicTask", BPF_JAZZ_MP3);
	            }
	            else if(eq_mode == 5)
	            {
		 	 #ifdef SUPPORT_DOUBLE_VOICE
		 	 	if(IsVoiceEnable==2)
		 	 	{
		   			voice_prompt_play("MusicTask",BPF_SOFT_MP3_EN);
		 	 	}			
		 	 	else	 
		 	 #endif	            			                                                	            
	            
	           		 voice_prompt_play("MusicTask", BPF_SOFT_MP3);
	            }
	            break;

		case MSG_VOICE_MUTE:

			music_prompt_flag = PROMPT_STATUS_PLAY;
	            m_op_api->dop_api->dec_api.save_brk = 1;
	            music_stop_decoder(m_op_api);
		 	 #ifdef SUPPORT_DOUBLE_VOICE
		 	 	if(IsVoiceEnable==2)
		 	 	{
		   			voice_prompt_play("MusicTask",BPF_MUTE_MP3_EN);
		 	 	}			
		 	 	else	 
		 	 #endif	            			                                                	            
			
		            voice_prompt_play("MusicTask",BPF_MUTE_MP3);
            break;

        case MSG_VOICE_VOLUME_PLUS:

        	music_prompt_flag = PROMPT_STATUS_PLAY;
            m_op_api->dop_api->dec_api.save_brk = 1;
            music_stop_decoder(m_op_api);


		 	 #ifdef SUPPORT_DOUBLE_VOICE
		 	 	if(IsVoiceEnable==2)
		 	 	{
		   			voice_prompt_play("MusicTask",BPF_VL_INC_MP3_EN);
		 	 	}			
		 	 	else	 
		 	 #endif	            			                                                	            
		 	 	{
					#ifdef SUPPORT_SMM_SA_VOICE			 	
			 	 	{
						if(dac_var.cur_sys_vol_l ==30) 			
							voice_prompt_play("MusicTask",BPF_VL_MAX_MP3);
						else		 	 	
							voice_prompt_play("MusicTask",BPF_VL_INC_MP3);
			 	 	}
					#else
					
							voice_prompt_play("MusicTask",BPF_VL_INC_MP3);
					#endif			 
		 	 	}
            break;


         case MSG_VOICE_VOLUME_MINUS:

        	music_prompt_flag = PROMPT_STATUS_PLAY;
            m_op_api->dop_api->dec_api.save_brk = 1;
            music_stop_decoder(m_op_api);
		 	 #ifdef SUPPORT_DOUBLE_VOICE
		 	 	if(IsVoiceEnable==2)
		 	 	{
		   			voice_prompt_play("MusicTask",BPF_VL_DEC_MP3_EN);
		 	 	}			
		 	 	else	 
		 	 #endif	            			                                                	            
            
            voice_prompt_play("MusicTask",BPF_VL_DEC_MP3);
            break;

         case MSG_MAX_VOICE:

         	music_prompt_flag = PROMPT_STATUS_PLAY;
            m_op_api->dop_api->dec_api.save_brk = 1;
            music_stop_decoder(m_op_api);
	 	 #ifdef SUPPORT_DOUBLE_VOICE
	 	 	if(IsVoiceEnable==2)
	 	 	{
	   			voice_prompt_play("MusicTask",BPF_VL_MAX_MP3_EN);
	 	 	}			
	 	 	else	 
	 	 #endif	            			                                                	            
            
            voice_prompt_play("MusicTask",BPF_VL_MAX_MP3);
            break;
 #endif		
	
	case MSG_MUSIC_VOICE_SWITCH:	

		music_prompt_flag = PROMPT_STATUS_PLAY;

		m_op_api->dop_api->dec_api.save_brk = 1;
		music_stop_decoder(m_op_api);		            

		 #if defined SUPPORT_DOUBLE_VOICE
			if(IsVoiceEnable==1)
			{
				voice_prompt_play("MusicTask",BPF_VOICE_ON_MP3);
			}			
			else if(IsVoiceEnable==2)
			{
				voice_prompt_play("MusicTask",BPF_VOICE_ON_MP3_EN);
			}				
			else if(voice_save==1)
			{
				voice_prompt_play("MusicTask",BPF_VOICE_OFF_MP3);
			}
			else if(voice_save==2)
			{
				voice_prompt_play("MusicTask",BPF_VOICE_OFF_MP3_EN);
			}
		 #else
			if(IsVoiceEnable)
			{
				voice_prompt_play("MusicTask",BPF_VOICE_ON_MP3);
			}
			else
			{
				voice_prompt_play("MusicTask",BPF_VOICE_OFF_MP3);
			}		 
		 #endif
	break;

#endif


#ifdef  SUPPORT_NUMBER_VOICE

		case MSG_VOICE_NUMBER:	

			music_prompt_flag = PROMPT_STATUS_PLAY;
			m_op_api->dop_api->dec_api.save_brk = 1;
			music_stop_decoder(m_op_api);
			                                            	                        
		if(bVoiceNumber == 0)	
	            {
	            	voice_prompt_play("MusicTask", BPF_0_MP3);
	            }
	            else if(bVoiceNumber == 1)
	            {
	            	voice_prompt_play("MusicTask", BPF_1_MP3);
	            }
	            else if(bVoiceNumber == 2)
	            {
	            
	            	voice_prompt_play("MusicTask", BPF_2_MP3);
	            }
	            else if(bVoiceNumber == 3)
	            {
	            
	            	voice_prompt_play("MusicTask", BPF_3_MP3);
	            }
	            else if(bVoiceNumber == 4)
	            {
	            
	            	voice_prompt_play("MusicTask", BPF_4_MP3);
	            }
	            else if(bVoiceNumber == 5)
	            {
	            
	           		 voice_prompt_play("MusicTask", BPF_5_MP3);
	            }
	            else if(bVoiceNumber == 6)
	            {
	            	voice_prompt_play("MusicTask", BPF_6_MP3);
	            }
	            else if(bVoiceNumber == 7)
	            {
	            
	            	voice_prompt_play("MusicTask", BPF_7_MP3);
	            }
	            else if(bVoiceNumber == 8)
	            {
	            
	            	voice_prompt_play("MusicTask", BPF_8_MP3);
	            }
	            else if(bVoiceNumber == 9)
	            {
	            
	            	voice_prompt_play("MusicTask", BPF_9_MP3);
	            }

								
	            break;
				
#endif
#ifdef SUPPORT_VOICE_ONOFF_VOICE	

	case MSG_MUSIC_VOICE_ONOFF:	

		music_prompt_flag = PROMPT_STATUS_PLAY;

		m_op_api->dop_api->dec_api.save_brk = 1;
		music_stop_decoder(m_op_api);		            

		if(led7_var.bIfHaveVoice)
		{
			voice_prompt_play("MusicTask",BPF_VOICE_ON_MP3);
		}
		else
		{
			voice_prompt_play("MusicTask",BPF_VOICE_OFF_MP3);
		}
		
		break;
	
#endif

#ifdef SUPPORT_KEY_6_VOICE

            case MSG_VOICE_YESE:
		music_prompt_flag = PROMPT_STATUS_PLAY;

		m_op_api->dop_api->dec_api.save_brk = 1;
		music_stop_decoder(m_op_api);		            

		{
			voice_prompt_play("MusicTask",BPF_VL_MAX_YESE);
		}
		
		break;				
            case MSG_VOICE_END:
		music_prompt_flag = PROMPT_STATUS_PLAY;

		m_op_api->dop_api->dec_api.save_brk = 1;
		music_stop_decoder(m_op_api);		            

		{
			voice_prompt_play("MusicTask",BPF_VL_MAX_END);
		}
		
		break;						
            case MSG_VOICE_APPLAUD:
		music_prompt_flag = PROMPT_STATUS_PLAY;

		m_op_api->dop_api->dec_api.save_brk = 1;
		music_stop_decoder(m_op_api);		            

		{
			voice_prompt_play("MusicTask",BPF_VL_MAX_APPLAUD);
		}
		
		break;						
            case MSG_VOICE_GUN:
		music_prompt_flag = PROMPT_STATUS_PLAY;

		m_op_api->dop_api->dec_api.save_brk = 1;
		music_stop_decoder(m_op_api);		            

		{
			voice_prompt_play("MusicTask",BPF_VL_MAX_GUN);
		}
		
		break;						
            case MSG_VOICE_ZXC:
		music_prompt_flag = PROMPT_STATUS_PLAY;

		m_op_api->dop_api->dec_api.save_brk = 1;
		music_stop_decoder(m_op_api);		            

		{
			voice_prompt_play("MusicTask",BPF_VL_MAX_ZXC);
		}
		
		break;						
           case MSG_VOICE_BEST_PARTNER:
		music_prompt_flag = PROMPT_STATUS_PLAY;

		m_op_api->dop_api->dec_api.save_brk = 1;
		music_stop_decoder(m_op_api);		            

		{
			voice_prompt_play("MusicTask",BPF_VL_MAX_BEST_PARTNER);
		}
		
		break;	
#endif


        default:
            break;
    }
    return 0;
#endif
}
