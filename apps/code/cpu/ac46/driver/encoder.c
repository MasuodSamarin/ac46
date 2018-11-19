#include "config.h"

#ifdef SUPPORT_ENCODER
#include "encoder.h"
#include "msg.h"
#include "os_api.h"
#include "led7_drv.h"

u8  enc_value_temp=0;
u8  enc_value_temp1=0;

#ifdef SUPPORT_ENCODE_flash_led
 u8    ENCODE_flash_led_time;


void ENC_Encoder_Led(void)
{
	static u8 cnt=0;

#ifdef support_encode_use_tm1628_io	

	if(workmode==STANBY_WORK_MODE)
	{
	 		LED_STATUS&=~LED_EN_LED;
		return;
	}
	
	 if(ENCODE_flash_led_time>0)
	 {
		    cnt++;	 
		   if(cnt==1)
		   	{
			 	LED_STATUS|=LED_EN_LED;
		   	}
		 else if(cnt==20)
		 	{
			 	LED_STATUS&=~LED_EN_LED;
		 	}
		if(cnt==40)
			{
				cnt=0;
				ENCODE_flash_led_time--;		
			}		 
	 }
	 else
	 	{
			 	LED_STATUS|=LED_EN_LED;
			cnt=0;
	 	}
	 
#else	

	ENC_LED_INIT_EN();

	 if(ENCODE_flash_led_time>0)
	 {
		    cnt++;	 
		   if(cnt==1)
		   	{
		 	ENC_LED_ON();
		   	}
		 else if(cnt==20)
		 	{
		 		ENC_LED_OFF();	
		 	}
		if(cnt==40)
			{
				cnt=0;
				ENCODE_flash_led_time--;		
			}		 
	 }
	 else
	 	{
		 	ENC_LED_ON();	 	
			cnt=0;
	 	}
	 
#endif

}

#endif 

void ENC_Encoder(void)
{
    u8 temp_ch=0,enc_vol_dir;

#if 0//def mute_after_onlt_user_mute_key
    if(mute)
        return;
#endif

#ifdef support_power_on_vo_0_to_VOLUME_DEFUALT
    if(vol_auto_add_to_def_flag!=0)
        return ;
#endif
#ifdef suppot_stanby_to_line_mode
	if(stanby_flag==1)
		return;
#endif

    ENCODE_PORTB_IN();

    if (BM_UP_IS_H()){
        temp_ch = 2;
    	}
    if (BM_DN_IS_H()){
        temp_ch++;
    	}
    if(enc_value_temp!=temp_ch)
    {
        if(temp_ch>enc_value_temp)
            enc_vol_dir = temp_ch-enc_value_temp;
        else
            enc_vol_dir = enc_value_temp -temp_ch;
		
        if(enc_vol_dir)
        {
            if((enc_value_temp1>0) && (temp_ch==0))
            {
#if defined(ZX_HL601_QGN2_K1764_AC4601) ||defined(ZX_HL601_QGN_JM4169_AC4601)||defined(AZS_AZS020_AC4601)&&defined(support_menu_mode)

	 #ifdef SUPPORT_ENCODE_flash_led
	 #ifdef LED_1628_hs_sd
	                 ENCODE_flash_led_time=4;
	 #else
	                 ENCODE_flash_led_time=4;
	 
	 #endif
	 #endif

	 #ifndef MAIN_APP
	                 if(menumode == MENU_MAIN_VOL_MODE )
	                 {
	                     if(enc_vol_dir>enc_value_temp1)
	                         os_taskq_post("MainTask", 1, MSG_VOL_UP);
	                     else if(enc_vol_dir<enc_value_temp1)
	     					os_taskq_post("MainTask", 1, MSG_VOL_DOWN);
	                 }
	 		#ifdef Support_MSG_MIC_ECO_VOL_KEY
	 		#if !defined(ENCODER1_ADJUST_MIC_VOL)
	 		else if(menumode== MENU_OK_VOL_MODE)      		
	 			{
	 	                    if(enc_vol_dir>enc_value_temp1)
	                             os_taskq_post("MainTask", 1, MSG_MIC_UP);
	 	                    else if(enc_vol_dir<enc_value_temp1)
	 						    os_taskq_post("MainTask", 1, MSG_MIC_DN);
	 			}		
	 		#endif
	 		else if( menumode == MENU_ECHO_MODE)      		
	 			{
	 	                    if(enc_vol_dir>enc_value_temp1)
	 						    os_taskq_post("MainTask", 1, MSG_ECHO_UP);
	 	                    else if(enc_vol_dir<enc_value_temp1)
	 						    os_taskq_post("MainTask", 1, MSG_ECHO_DN);
	 			}  
	         #endif			
	                 else if( menumode == MENU_BASS_MODE)
	                 {
	                     if(enc_vol_dir>enc_value_temp1)
	 					    os_taskq_post("MainTask", 1, MSG_BASS_UP+(menumode-MENU_BASS_MODE)*2);
	                     else if(enc_vol_dir<enc_value_temp1)
	 					    os_taskq_post("MainTask", 1, MSG_BASS_DN+(menumode-MENU_BASS_MODE)*2);
	                 }
	                 else if( menumode == MENU_TREBLE_MODE)
	                 {
	                     if(enc_vol_dir>enc_value_temp1)
	 					   os_taskq_post("MainTask", 1, MSG_TREBLE_UP+(menumode-MENU_TREBLE_MODE)*2);
	                     else if(enc_vol_dir<enc_value_temp1)
	 					    os_taskq_post("MainTask", 1, MSG_TREBLE_DN+(menumode-MENU_TREBLE_MODE)*2);
	                 }
	                 else if( menumode == MENU_SWVOLL_MODE)
	                 {
	                     if(enc_vol_dir>enc_value_temp1)
	 					    os_taskq_post("MainTask", 1, MSG_SWVOL_UP+(menumode-MENU_SWVOLL_MODE)*2);
	                     else if(enc_vol_dir<enc_value_temp1)
	     					os_taskq_post("MainTask", 1, MSG_SWVOL_DN+(menumode-MENU_SWVOLL_MODE)*2);
	                 }
	                #ifdef MENU_FRONT_LEFT_MODE
	                 else if( menumode == MENU_FRONT_LEFT_MODE)
	                 {
	                     if(enc_vol_dir>enc_value_temp1)
	 					    os_taskq_post("MainTask", 1, MSG_FRONT_LEFT_UP);
	                     else if(enc_vol_dir<enc_value_temp1)
	     					os_taskq_post("MainTask", 1, MSG_FRONT_LEFT_DN);
	                 }
	                 #endif
	                #ifdef MENU_FRONT_RIGHT_MODE
	 				 else if( menumode == MENU_FRONT_RIGHT_MODE)
	 				 {
	 					 if(enc_vol_dir>enc_value_temp1)
	 						 os_taskq_post("MainTask", 1, MSG_FRONT_RIGHT_UP);
	 					 else if(enc_vol_dir<enc_value_temp1)
	 						 os_taskq_post("MainTask", 1, MSG_FRONT_RIGHT_DN);
	 				 }
	                #endif
	 
	 
	 #ifdef LED1_ENCODE_STATE_FLASH
		 flashled(1,4,20);
	 #endif
	 
	 #endif

#elif defined SUPPORT_USE_ENCODE_AS_MODE_CHANGE

	 #ifdef SUPPORT_ENCODE_flash_led
	 #ifdef LED_1628_hs_sd
	                 ENCODE_flash_led_time=4;
	 #else
	                 ENCODE_flash_led_time=4;
	 
	 #endif
	 #endif
	 
	 #ifndef MAIN_APP

		 #if 0
		 	                 if(enc_vol_dir>enc_value_temp1)
		 	 				    os_taskq_post("MainTask", 1, MSG_VOL_UP);
		 	                 else if(enc_vol_dir<enc_value_temp1)
		 	 				    os_taskq_post("MainTask", 1, MSG_VOL_DOWN);
		 
		 #else
		                  if(enc_vol_dir>enc_value_temp1)
		  				    os_taskq_post("MainTask", 1, MSG_CHANGE_NEXT_MODE);
		                  else if(enc_vol_dir<enc_value_temp1)
		  				    os_taskq_post("MainTask", 1, MSG_CHANGE_PREV_MODE);
		 #endif

	 #ifdef LED1_ENCODE_STATE_FLASH
	 				flashled(1,4,20);
	 #endif
	 
	 #endif
	 

#else

	 #ifdef SUPPORT_ENCODE_flash_led
	 #ifdef LED_1628_hs_sd
	                 ENCODE_flash_led_time=4;
	 #else
	                 ENCODE_flash_led_time=4;
	 
	 #endif
	 #endif
	 #ifndef MAIN_APP
	                 #if defined(ZY_K1676_TM1622_LCD)
	                 if(menumode == MENU_MAIN_VOL_MODE )
	                 {
	                     if(enc_vol_dir>enc_value_temp1)
	 					    os_taskq_post("MainTask", 1, MSG_VOL_UP);
	                     else if(enc_vol_dir<enc_value_temp1)
	 					    os_taskq_post("MainTask", 1, MSG_VOL_DOWN);
	                 }      
	                 #elif defined(ENCODE_KEY_FOR_PREV_NEXT)                
	 				if(compare_task_name("MusicTask")){
	                 if(enc_vol_dir>enc_value_temp1)
	 				    os_taskq_post_msg("MusicTask", 1, MSG_MUSIC_NEXT_FILE);
	                 else if(enc_vol_dir<enc_value_temp1)
	 				    os_taskq_post_msg("MusicTask", 1, MSG_MUSIC_PREV_FILE);
	 				    }
	 				else if(compare_task_name("FMRadioTask")){
	 					if(enc_vol_dir>enc_value_temp1)
	 						os_taskq_post_msg("FMRadioTask", 1, MSG_FM_NEXT_STATION);
	 					else if(enc_vol_dir<enc_value_temp1)
	 						os_taskq_post_msg("FMRadioTask", 1, MSG_FM_PREV_STATION);
	 						}
	 				else if(compare_task_name("BtStackTask")){
	 					if(enc_vol_dir>enc_value_temp1)
	 						os_taskq_post_msg("BtStackTask", 1, MSG_BT_NEXT_FILE);
	 					else if(enc_vol_dir<enc_value_temp1)
	 						os_taskq_post_msg("BtStackTask", 1, MSG_BT_PREV_FILE);
	 						}
	                 #else
	                 if(enc_vol_dir>enc_value_temp1)
	 				    os_taskq_post("MainTask", 1, MSG_VOL_UP);
	                 else if(enc_vol_dir<enc_value_temp1)
	 				    os_taskq_post("MainTask", 1, MSG_VOL_DOWN);
	                 #endif
	 #ifdef LED1_ENCODE_STATE_FLASH
	 				flashled(1,4,20);
	 #endif
	 
	 #endif
#endif
            }
            enc_value_temp1 = enc_vol_dir;
        }
        if(!temp_ch||temp_ch == 3)
            enc_value_temp1 = 0;
        enc_value_temp = temp_ch;
    }
}

#ifdef SUPPORT_TWO_ENCODER
u8  enc_value_tempB=0;
u8  enc_value_temp1B=0;
void ENC_Encoder1(void)
{
    u8 temp_ch=0,enc_vol_dir;

#if 0//def mute_after_onlt_user_mute_key
    if(mute)
        return;
#endif

#ifdef support_power_on_vo_0_to_VOLUME_DEFUALT
    if(vol_auto_add_to_def_flag!=0)
        return ;
#endif
#ifdef suppot_stanby_to_line_mode
	if(stanby_flag==1)
		return;
#endif

    ENCODE_PORTB_IN1();

    if (BM_UP_IS_H1()){
        temp_ch = 2;
    	}
    if (BM_DN_IS_H1()){
        temp_ch++;
    	}
    if(enc_value_tempB!=temp_ch)
    {
        if(temp_ch>enc_value_tempB)
            enc_vol_dir = temp_ch-enc_value_tempB;
        else
            enc_vol_dir = enc_value_tempB -temp_ch;
        if(enc_vol_dir)
        {
            if((enc_value_temp1B>0) && (temp_ch==0))
            {
#if 0//defined(SJ_K1673_SP2234)||defined(HY_MK_JL2_V20)//||defined(ZY_3082_8426YH)||defined(ZY_K1676_TM1622_LCD)//defined(JC_2271_TW1628_PT2313_62429)&&defined(support_menu_mode)
#ifndef MAIN_APP
                if(menumode == MENU_MAIN_VOL_MODE )
                {
                    if(enc_vol_dir>enc_value_temp1)
                        os_taskq_post("MainTask", 1, MSG_MAIN_VOL_UP);
                    else if(enc_vol_dir<enc_value_temp1)
    					os_taskq_post("MainTask", 1, MSG_MAIN_VOL_DN);
                }
		#ifdef Support_MSG_MIC_ECO_VOL_KEY
		else if(menumode== MENU_OK_VOL_MODE)      		
			{
	                    if(enc_vol_dir>enc_value_temp1)
                            os_taskq_post("MainTask", 1, MSG_MIC_UP);
	                    else if(enc_vol_dir<enc_value_temp1)
						    os_taskq_post("MainTask", 1, MSG_MIC_DN);
			}		
		else if( menumode == MENU_ECHO_MODE)      		
			{
	                    if(enc_vol_dir>enc_value_temp1)
						    os_taskq_post("MainTask", 1, MSG_ECHO_UP);
	                    else if(enc_vol_dir<enc_value_temp1)
						    os_taskq_post("MainTask", 1, MSG_ECHO_DN);
			}  
        #endif			
                else if( menumode == MENU_BASS_MODE)
                {
                    if(enc_vol_dir>enc_value_temp1)
					    os_taskq_post("MainTask", 1, MSG_BASS_UP+(menumode-MENU_BASS_MODE)*2);
                    else if(enc_vol_dir<enc_value_temp1)
					    os_taskq_post("MainTask", 1, MSG_BASS_DN+(menumode-MENU_BASS_MODE)*2);
                }
                else if( menumode == MENU_TREBLE_MODE)
                {
                    if(enc_vol_dir>enc_value_temp1)
					   os_taskq_post("MainTask", 1, MSG_TREBLE_UP+(menumode-MENU_TREBLE_MODE)*2);
                    else if(enc_vol_dir<enc_value_temp1)
					    os_taskq_post("MainTask", 1, MSG_TREBLE_DN+(menumode-MENU_TREBLE_MODE)*2);
                }
                else if( menumode == MENU_SWVOLL_MODE)
                {
                    if(enc_vol_dir>enc_value_temp1)
					    os_taskq_post("MainTask", 1, MSG_SWVOL_UP+(menumode-MENU_SWVOLL_MODE)*2);
                    else if(enc_vol_dir<enc_value_temp1)
    					os_taskq_post("MainTask", 1, MSG_SWVOL_DN+(menumode-MENU_SWVOLL_MODE)*2);
                }
               #ifdef MENU_FRONT_LEFT_MODE
                else if( menumode == MENU_FRONT_LEFT_MODE)
                {
                    if(enc_vol_dir>enc_value_temp1)
					    os_taskq_post("MainTask", 1, MSG_FRONT_LEFT_UP);
                    else if(enc_vol_dir<enc_value_temp1)
    					os_taskq_post("MainTask", 1, MSG_FRONT_LEFT_DN);
                }
                #endif
               #ifdef MENU_FRONT_RIGHT_MODE
				 else if( menumode == MENU_FRONT_RIGHT_MODE)
				 {
					 if(enc_vol_dir>enc_value_temp1)
						 os_taskq_post("MainTask", 1, MSG_FRONT_RIGHT_UP);
					 else if(enc_vol_dir<enc_value_temp1)
						 os_taskq_post("MainTask", 1, MSG_FRONT_RIGHT_DN);
				 }
               #endif
#ifdef SUPPORT_ENCODE_flash_led
                ENCODE_flash_led_time=8;
#endif
#ifdef LED1_ENCODE_STATE_FLASH
flashled(1,4,20);
#endif

#endif
#else

#ifdef SUPPORT_ENCODE_flash_led
#ifdef LED_1628_hs_sd
                ENCODE_flash_led_time=4;
#else
                ENCODE_flash_led_time=6;

#endif
#endif
#ifndef MAIN_APP
                #if defined(ZY_K1676_TM1622_LCD)
                if(menumode == MENU_MAIN_VOL_MODE )
                {
                    if(enc_vol_dir>enc_value_temp1B)
					    os_taskq_post("MainTask", 1, MSG_VOL_UP);
                    else if(enc_vol_dir<enc_value_temp1B)
					    os_taskq_post("MainTask", 1, MSG_VOL_DOWN);
                }      
                #elif defined(ENCODE_KEY_FOR_PREV_NEXT)                
				if(compare_task_name("MusicTask")){
                if(enc_vol_dir>enc_value_temp1B)
				    os_taskq_post_msg("MusicTask", 1, MSG_MUSIC_NEXT_FILE);
                else if(enc_vol_dir<enc_value_temp1B)
				    os_taskq_post_msg("MusicTask", 1, MSG_MUSIC_PREV_FILE);
				    }
				else if(compare_task_name("FMRadioTask")){
					if(enc_vol_dir>enc_value_temp1B)
						os_taskq_post_msg("FMRadioTask", 1, MSG_FM_NEXT_STATION);
					else if(enc_vol_dir<enc_value_temp1B)
						os_taskq_post_msg("FMRadioTask", 1, MSG_FM_PREV_STATION);
						}
				else if(compare_task_name("BtStackTask")){
					if(enc_vol_dir>enc_value_temp1B)
						os_taskq_post_msg("BtStackTask", 1, MSG_BT_NEXT_FILE);
					else if(enc_vol_dir<enc_value_temp1B)
						os_taskq_post_msg("BtStackTask", 1, MSG_BT_PREV_FILE);
						}
				#elif defined(ENCODER1_ADJUST_MIC_VOL)
	   				if(enc_vol_dir>enc_value_temp1B)
	   					os_taskq_post("MainTask", 1, MSG_MIC_UP);
	   				else if(enc_vol_dir<enc_value_temp1B)
	   					os_taskq_post("MainTask", 1, MSG_MIC_DN);
                #else                
                if(enc_vol_dir>enc_value_temp1B)
				    os_taskq_post("MainTask", 1, MSG_VOL_UP);
                else if(enc_vol_dir<enc_value_temp1B)
				    os_taskq_post("MainTask", 1, MSG_VOL_DOWN);
                #endif
#ifdef LED1_ENCODE_STATE_FLASH
				flashled(1,4,20);
#endif

#if 0//def SUPPORT_ENCODE_flash_led
                ENCODE_flash_led_time=2;
#endif				
#endif
#endif
            }
            enc_value_temp1B = enc_vol_dir;
        }
        if(!temp_ch||temp_ch == 3)
            enc_value_temp1B = 0;
        enc_value_tempB = temp_ch;
    }
}
#endif
#endif
