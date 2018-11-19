#include "includes.h"
#include "config.h"
#include "sys_detect.h"
#include "key_drv_ad.h"
#include "task_manage.h"
#include "file_op.h"
#include "led.h"
#include "dev_linein.h"
#include "fm_radio.h"
//#include "irtc.h"
#include "key.h"
#include "key_voice.h"
#include "led7_drv.h"
OS_SEM  power_sem ;
#ifdef SUPPORT_MUTE_FLASH
extern bool b_muteFlag;
#endif
#include "msg.h"




/*
*******************************************************************************
                                POWER AMPLIFIER MODULE
*******************************************************************************
*/
/*----------------------------------------------------------------------------*/
/**@brief   ÂäüÊîæmuteÂáΩÊï∞
   @param   void
   @param   void
   @return  void
   @note    void pa_mute(void)
*/
/*----------------------------------------------------------------------------*/
void pa_mute(void)
{
#if PA_EN
    sys_det_puts("pa_mute\n");
#ifdef ONLY_POWER_ON_MUTE
		return;
#endif
#ifdef SUPPORT_PT2313
	 PT2313Mute(TRUE);
#endif
		  set_mute_io_is_out();    
#ifdef  mute_io_L_is_mute  
		set_mute_io_low();		
#else
		  set_mute_io_high();		
#endif 
#endif
}
/*----------------------------------------------------------------------------*/
/**@brief   ÂäüÊîæumuteÂáΩÊï∞
   @param   void
   @param   void
   @return  void
   @note    void pa_umute(void)
*/
/*----------------------------------------------------------------------------*/
void pa_umute(void)
{
#if PA_EN
    sys_det_puts("pa_umute\n");
#ifdef PHONE_CHECK_ENABLE	     //ﬂ≤‚π¶MUTE
	if(phone_is_online())
		return; 
#endif 
#ifdef SUPPORT_MUTE_FLASH
	if(b_muteFlag){
	b_muteFlag=FALSE;
	LED_FLASH_CHAR=0;
	LED_FLASH_ICON=0;
	}
#endif
#ifdef ONLY_POWER_ON_MUTE
			return;
#endif
#ifdef SUPPORT_PT2313
	  PT2313Mute(FALSE);
#endif
	
 #ifdef IO_MUTE_DELAY_ALL_STATE
		  if(bMuteDelayCnt)return;
#endif
	
		set_mute_io_is_out();
	   
#ifdef  mute_io_L_is_mute  
		  set_mute_io_high();	   
#else
		  set_mute_io_low();	
#endif 
#endif
}

#ifdef ONLY_POWER_ON_MUTE
void  pa_mute1(void)
{
      set_mute_io_is_out();	   
#ifdef  mute_io_L_is_mute  
	set_mute_io_low();   	
#else
  	  set_mute_io_high();       
#endif 
}
/*----------------------------------------------------------------------------*/
/**@brief  umute
   @param   void
   @return  void
   @author  minzong zhang
   @note    void pa_umute()
*/
/*----------------------------------------------------------------------------*/
void pa_umute1(void)
{

#ifdef PHONE_CHECK_ENABLE	     //ﬂ≤‚π¶MUTE
if(phone_is_online())
    return;	
#endif 
#ifdef SUPPORT_MUTE_FLASH
if(b_muteFlag){
b_muteFlag=FALSE;
LED_FLASH_CHAR=0;
LED_FLASH_ICON=0;
}
#endif

 	set_mute_io_is_out();
   
#ifdef  mute_io_L_is_mute  
	  set_mute_io_high();      
#else
  	  set_mute_io_low();   	
#endif 
}
#endif


#ifdef support_io_det_mute
#ifdef SUPPORT_MUSIC_STOP
extern u8 bPause_state;
#endif
u8 bt_automute_sw;  // bt ±®”Ô“Ù  ±≤ªmute
#include "avctp_user.h"

bool auto_mute_sw;
bool pa_auto_mute_state()
{
	if ((workmode==LINE_WORK_MODE)||((workmode==MUSIC_WORK_MODE)&&(bPause_state==1))||
	    ((workmode==BT_WORK_MODE)&&(bt_automute_sw==0)&&
              ((BT_STATUS_CONNECTING != get_bt_connect_status())||(BT_STATUS_PLAYING_MUSIC != get_bt_connect_status()))))
               return	1;
	else 
		return 0;
}

void  pa_automute(void)
{
	static bool auto_mute_sw1;

	AUTOMUTE_IO_SET;

	if(AUTOMUTE_IO_CHECK)
	auto_mute_sw=1;
	else
	auto_mute_sw=0;

	if (auto_mute_sw1!= auto_mute_sw)
	{
		auto_mute_sw1 =auto_mute_sw;
		#if 1		
		if (auto_mute_sw1)
		{

			if (pa_auto_mute_state())
				{			
					set_mute_io_is_out();  
					set_mute_io_high(); 			
				}
		}
		else  
		{
			set_mute_io_is_out();  
			set_mute_io_low(); 		
		}
		#endif		
	}		
}

#endif



/*
*******************************************************************************
                                LVD MODULE
*******************************************************************************
*/
#if SYS_LVD_EN
extern u16 adc_value[MAX_AD_CHANNEL];
#define POWER_CHEAK_CNT_NORMAL   40
#define POWER_CHEAK_CNT_LOW      40
#define POWER_CHEAK_CNT_LOW1     300
#define POWER_CHEAK_CNT_LOW2     400



#ifdef support_battery_mode_check

 u8  ldo_power_mod;  
#define BAT_ADC_FULL              20
#define  BAT_ADC_HIGH            20
#define BAT_ADC_HALF              18
#define BAT_ADC_LOW               16
#define BAT_ADC_LOW_OFF       0

 #endif 


/*----------------------------------------------------------------------------*/
/**@brief  Á≥ªÁªüÁîµÈáèÊ£ÄÊµã
   @param  void
   @return void
   @note   u16 get_battery_value()
*/
/*----------------------------------------------------------------------------*/
u16 get_battery_value()
{
#ifdef SUPPORT_BAT_DETECT_USE_IO
    u16 battery_value,LDOIN_12;
    LDOIN_12 = adc_value[AD_CH_BAT];
	
#if low_power_value>100
    battery_value= LDOIN_12*33/0x3ff*10;
#else
    battery_value= LDOIN_12*33/0x3ff;
#endif
//  if(aaaa==1)
//  printf("battery_value: 0x%x    %d\n",LDOIN_12,battery_value);	
  // aaaa++;
//if(aaaa>200)
	//aaaa=0;

    return battery_value;

#else
    u16 battery_value,LDOIN_12,LDO_ref;
	
    LDOIN_12 = adc_value[AD_CH_LDOIN];
    LDO_ref  = adc_value[AD_CH_LDOREF];

    battery_value = (((u16)LDOIN_12*381+20)/10)/((u16)LDO_ref*3/2);
    //sys_det_printf("battery_value: 0x%x    0x%x   %d\n",LDOIN_12,LDO_ref,battery_value);
#endif

    return battery_value;
}
/*----------------------------------------------------------------------------*/
/**@brief  ÂÆûÊó∂ÁîµÈáèÊ£ÄÊµã
   @param  void
   @return void
   @note   void battery_check()
*/
/*----------------------------------------------------------------------------*/
#ifdef support_low_power_use_extern_io
bool low_power_sw;
#endif
void battery_check()
{
    u16 val;
    tbool enter_low_power_flag = 0;
    static u16 low_power_cnt,normal_power_cnt,low_power_notice_cnt;
    static u8 low_power_voice_cnt;
    val = get_battery_value();
   //sys_det_printf("val:%d\n",val);

#ifdef support_battery_mode_check
    static u8 ldo_power_count, current_ldo_voltage,old_ldo_voltage;
#endif 

#ifdef support_power_on_low_power_io_delay
static  u16 low_power_cnt2;

	if((power_delay>=1)&&(val < low_power_value))
	{
	  	power_delay--;
		val=20;
	}
	else
		power_delay=0;

#endif

#ifdef support_low_power_use_extern_io

#ifdef support_low_power_io_off
	if(low_power_sw==1)
	{

//                printf("--------22222- battery_check--------\n");
	#ifdef LOWER_POWER_TIMER_VAL
	    if(low_power_cnt2 > 50*LOWER_POWER_TIMER_VAL) //20s 
	  #else
	  	  if(low_power_cnt2 > 50*20) //20s 
	#endif
	    	{
			low_power_onoff(0);
			low_power_cnt2=0;
			low_power_sw=0;
			 #ifdef support_low_power_mute_dac
				dac_mute(1,1);
			 #endif

	 		  #ifdef support_send_ir_code // MP5 ON
	 		  	IRSendInital(MP5_PANEL_ON);
	 		  	os_time_dly(25);
	 		  #endif
			 
			 #ifdef support_low_power_standby_delya_xs
	              	 os_taskq_post_msg("MainTask", 1, MSG_STANBY_KEY);			   			 
			 #endif
			 
	    	}
		else
		low_power_cnt2++;	
	}	
#endif	
#endif	

    if(curr_task == NULL)
    {
	 #if defined support_low_power_stanby
	 
	     #ifdef low_power_value
	             if(val < low_power_value)
	     #else
	             if(val < 17)
	     #endif				 
	         {
	             low_power_cnt++;
	             normal_power_cnt = 0;
	             if(low_power_cnt > POWER_CHEAK_CNT_LOW)
	             {
	                 sys_det_puts("-------------[M Enter Low Power Mode]-----------\n");
	                 low_power_cnt = 0;
	                 enter_low_power_flag = 0;
	                // led_close();
	             }
	         }
	 #else
	 
	 	 #ifdef low_power_value
	 	         if(val < 0)
	 	 #else
	 	         if(val < 29)
	 	 #endif			
	         {
	             low_power_cnt++;
	             normal_power_cnt = 0;
	             if(low_power_cnt > POWER_CHEAK_CNT_LOW)
	             {
	                 sys_det_puts("-------------[M Enter Low Power Mode]-----------\n");
	                 low_power_cnt = 0;
	                 enter_low_power_flag = 0;
	                // led_close();
	             }
	         }
	 	 
	 #endif
	 
        else
        {
            low_power_cnt = 0;
            normal_power_cnt++;
            if(enter_low_power_flag)
            {
                enter_low_power_flag = 0;
                if((normal_power_cnt > POWER_CHEAK_CNT_NORMAL) && (val > 35))
                {
                    sys_det_puts("-------------[Recover To Normal Power Mode 1]----------\n");
                   // led_init();
                    normal_power_cnt = 0;
                    os_sem_set(&power_sem,0) ;
                    os_sem_post(&power_sem);
                }
            }
            else
            {
                if(normal_power_cnt > POWER_CHEAK_CNT_NORMAL)
                {
                    sys_det_puts("-------------[Recover To Normal Power Mode 2]----------\n");
                    //led_init();
                    normal_power_cnt = 0;
                    os_sem_set(&power_sem,0) ;
                    os_sem_post(&power_sem);
                }
            }
        }

    }
    else
    {

	 #ifdef support_power_down_fast_mute
	    #ifdef ZY_5017_SG_2_AC4601
	            if(val < 144)
	    #else
	        #ifdef low_power_value
	                if(val < low_power_value)
	        #else
	                if(val < 15)
	        #endif			
	    #endif
	       	{
	 		 #ifdef support_low_power_mute_and_amp_power_off
	 			 #ifdef support_low_power_mute_dac
	 				dac_mute(1,1);
	 			 #endif		 
	 			#ifdef ONLY_POWER_ON_MUTE
	 			 	pa_mute1();	
	 			#else
	 			 	pa_mute();	
	 			#endif
	 			 #ifdef AMP_IC_WORK_ONFF
	 			 	Set_amp_power_out();		   
	 			 	Set_AMP_OFF(); 				
	 			 #endif
	 		#endif
	 	}
	   else
	 #endif	

#if defined  support_low_power_stanby
    #ifdef low_power_value
            if(val < low_power_value)
    #else
            if(val < 17)
    #endif			
     {
        pa_mute();
         low_power_cnt++;
         if(low_power_cnt > POWER_CHEAK_CNT_LOW1)
         {
//		                 sys_det_puts("-------------[Enter Low Power Mode]-----------\n");
             low_power_cnt = 0;
             PWR_CON |= BIT(4);/*‰ΩéÁîµÂ§ç‰Ωç*/
         }
     }
		
#else

    #ifdef low_power_value
            if(val < low_power_value)
    #else
            if(val < 31)
    #endif			
        {
        
	 #ifdef support_low_power_use_extern_io
	 
	         low_power_cnt++;
	         if(low_power_cnt > 50*5)
	         {
		 #ifdef support_low_power_mute_and_amp_power_off
			#ifndef support_low_power_no_mute_amp		
			#ifdef ONLY_POWER_ON_MUTE
			 	pa_mute1();	
			#else
			 	pa_mute();	
			#endif
			 #ifdef AMP_IC_WORK_ONFF
			 	Set_amp_power_out();		   
			 	Set_AMP_OFF(); 				
			 #endif
			 #endif
		#endif
		
			 #ifdef support_zy_low_power_standby
				 if(low_power_sw==0)
	              	 os_taskq_post_msg("MainTask", 1, MSG_STANBY_KEY);			   			 
			 #endif
		
//                printf("--------11111111111111111- low_power_sw %d \n",low_power_sw);
		
		      #if 0//def LED_SHOW_MP3
		 	 setLedLight(LED_SHOW_MP3,led_mode_flash_slow,0);
		      #endif
				  
			  #ifdef support_low_power_use_extern_io
			 	    low_power_sw=1;
			 #endif	
			 
			 
		         }
			 

	 #else			
		
            low_power_cnt++;
            if(low_power_cnt > POWER_CHEAK_CNT_LOW1)
            {
                sys_det_puts("-------------[Enter Low Power Mode]-----------\n");
                low_power_cnt = 0;
                PWR_CON |= BIT(4);/*‰ΩéÁîµÂ§ç‰Ωç*/
            }
	#endif		

			
        }

#endif				 


#ifdef support_low_power_tone
      else  if(val < low_power_tone_val)
      	{
            low_power_cnt = 0;
            low_power_notice_cnt++;
            if(low_power_notice_cnt > POWER_CHEAK_CNT_LOW1)
            {
                sys_det_puts("**Low_Power**\n");
                low_power_notice_cnt = 0;		

	          low_power_voice_cnt++;		   
               if(low_power_voice_cnt > 50)    // 50x300=1500 1500/50=30√Î
                    low_power_voice_cnt=0;
			   
	       if(low_power_voice_cnt==1)   //√ø30√Î±®”Ô“Ù“ª¥Œ
	               os_taskq_post_msg(keymsg_task_name, 1, MSG_LOW_POWER);			   

            }
        }
#endif	

#ifndef low_power_value

        else if(val < 34)
        {
            low_power_cnt = 0;
            low_power_notice_cnt++;
            if(low_power_notice_cnt > POWER_CHEAK_CNT_LOW1)
            {
                sys_det_puts("**Low_Power**\n");
                low_power_notice_cnt = 0;
                if(low_power_voice_cnt < 10)/*‰ΩéÁîµÊèêÁ§∫Èü≥*/
                {
                    low_power_voice_cnt++;
                    send_key_voice(500);
                }

            }
        }
#endif		
        else/*ÁîµÈáèÊ≠£Â∏∏*/
        {
            low_power_voice_cnt = 0;
            low_power_cnt = 0;
            low_power_notice_cnt = 0;
        }
    }

#ifdef support_battery_mode_check

/* LOD µÁ—π◊¥Ã¨ */

    old_ldo_voltage=current_ldo_voltage;

   if(val > BAT_ADC_FULL)  //    4.1V  
    {
      current_ldo_voltage=1;	    //¬˙
    }
    else if(val > BAT_ADC_HIGH)   // 3.9v  
    {
      current_ldo_voltage=2;     //  ∏ﬂ
    }
    else if(val > BAT_ADC_HALF)   // 3.7V   
    {
      current_ldo_voltage=3;    //∞Î
    }
    else if(val > BAT_ADC_LOW)   //    //3.3V   
    {
      current_ldo_voltage=4;   //µÕ
    }
    else if(val > BAT_ADC_LOW_OFF)    //  3V   
    {
      current_ldo_voltage=5;   //µÕµÕ
    }
    else
     current_ldo_voltage=6;    //µÕπÿª˙

	 
    if( current_ldo_voltage==old_ldo_voltage)	 	
             ldo_power_count++;
	 else 
	 	ldo_power_count=0;
	 
        if(ldo_power_count>50)
        {
            ldo_power_mod = old_ldo_voltage;
		ldo_power_count=55;  //±‹√‚++“Á≥ˆ	
        }

#endif 
	
}
#endif

void sys_power_up_check(void)
{
#if SYS_LVD_EN
    os_sem_pend(&power_sem,0);
#endif
}

/*
*******************************************************************************
                                POWER_UP MODULE
*******************************************************************************
*/
/*----------------------------------------------------------------------------*/
/**@brief
   @param  void
   @return void
   @note   void bt_mp3_detect(void)
*/
/*----------------------------------------------------------------------------*/
u8 bt_mp3_detect(void)
{
    u8 app;
    PORTC_DIR |= BIT(14);
    PORTC_PU &= ~BIT(14);
    PORTC_PD &= ~BIT(14);
    delay(200);
    if(PORTC_IN&BIT(14))
    {
        sys_det_puts(">>>>>>>>>>>>>>>>>>>>>>>>>[MP3_MODE]<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        app = POWERUP_TASK_MP3;
    }
    else
    {
        sys_det_puts(">>>>>>>>>>>>>>>>>>>>>>>>>[BT_MODE]<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        app = POWERUP_TASK_BT;
    }
    return app;
}
extern void set_bt_busy_flag(u32 flag);
u32 power_up_task(void)
{
#if 0//S10_MODE
    if(POWERUP_TASK_BT == bt_mp3_detect())
        task_switch("BtStackTask", 0,SWITCH_SPEC_TASK);
    else
    {
        set_bt_busy_flag(0);
        if(!file_operate_get_total_phydev())
            task_switch("FMRadioTask", 0,SWITCH_SPEC_TASK);
        else
            task_switch("MusicTask", 0,SWITCH_SPEC_TASK);
    }
    return false;
#else
    #if 0//BT_BACKMODE
        task_switch("BtStackTask", 0,SWITCH_SPEC_TASK);
    #else
        set_bt_busy_flag(0);
#if defined POWERUP_DEV_IGNORE||defined support_vm_mode_bass_treb_echo
		os_time_dly(50);	
#endif
		os_time_dly(35);

        #ifndef POWERUP_DEV_IGNORE

		#ifdef SUPPORT_MODE_VM
		
		     vm_read_api(VM_SYS_EQ,&workmode);
			 os_time_dly(2);

		//	printf("11111111111 workmode:%d \n",workmode);

		
			if(workmode==MUSIC_WORK_MODE)
			{
			      	if(file_operate_get_total_phydev())
		         	task_switch("MusicTask", 0,SWITCH_SPEC_TASK);
		         	else 
		         	task_switch("LineinTask", 0,SWITCH_SPEC_TASK);		
			}
			else	if(workmode==RADIO_WORK_MODE)			 
			{
		         	task_switch("FMRadioTask", 0,SWITCH_SPEC_TASK);		
			}
			else	if(workmode==BT_WORK_MODE)			 
			{
		         	task_switch("BtStackTask", 0,SWITCH_SPEC_TASK);		
			}			
			else	if(workmode==LINE_WORK_MODE)			 
			{
				#ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE
					bModeOfAuxContained=mode_aux;
				#endif
		         	task_switch("LineinTask", 0,SWITCH_SPEC_TASK);		
			}			
			#ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE			
				else	if(workmode==AC3_WORK_MODE)			 
				{
				#ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE			
					bModeOfAuxContained=mode_ac3;
				#endif
					
			         	task_switch("LineinTask", 0,SWITCH_SPEC_TASK);		
				}
			#endif
		
			else
				
		#endif
		

        #if RTC_CLK_EN
            if(is_alm_on())//ALM_WK
                task_switch("RTCTask", 0,SWITCH_SPEC_TASK);
            else
        #endif
		
            #ifdef POWER_ON_DIRECT_INTO_IDLE

  			    task_switch("IdleTask", 0,SWITCH_SPEC_TASK);
	     #elif defined(power_on_no_usb_sd_to_LINE)
		      	if(file_operate_get_total_phydev())
	         		task_switch("MusicTask", 0,SWITCH_SPEC_TASK);
	         	else 
	         		{
				#ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE
	       		 	bModeOfAuxContained=0;
				#endif
					
			         	task_switch("LineinTask", 0,SWITCH_SPEC_TASK);					
	         		}			
            #else
			
	            if(!file_operate_get_total_phydev())
	            	{
	 	                #ifdef POWER_ON_NO_DEV_TO_AUX
	 				 #ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE
					    #ifdef LINEIN_MULTIPLY_DEFAULT_MODE
		 				 	bModeOfAuxContained=LINEIN_MULTIPLY_DEFAULT_MODE;
	 				 	#else
		 				 	bModeOfAuxContained=0;						
						#endif
	 				 #endif				
	 		                task_switch("LineinTask", 0,SWITCH_SPEC_TASK);
	 			#elif defined POWER_ON_NO_DEV_TO_DVD
	 				 	bModeOfAuxContained=0;
	 		                task_switch("LineinTask", 0,SWITCH_SPEC_TASK);					 
	 			#elif defined POWER_ON_NO_DEV_TO_FM
	 		                task_switch("FMRadioTask", 0,SWITCH_SPEC_TASK);					 
	 			#elif defined POWER_ON_NO_DEV_TO_AC3
	 				 #ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE
	 				 	bModeOfAuxContained=mode_ac3;
	 				 #endif				
	 		                task_switch("LineinTask", 0,SWITCH_SPEC_TASK);			
	 	                #else
	 	                	task_switch("BtStackTask", 0,SWITCH_SPEC_TASK);
	 	                #endif
	            	}
	            else
			{                
				 #ifdef support_power_on_in_media_pause_state
				 	media_pause_timer=5;	
				 #endif			
	               	 task_switch("MusicTask", 0,SWITCH_SPEC_TASK);
	                }
                
            #endif
			
        #else
		 #ifdef POWER_ON_DIRECT_INTO_IDLE
		 
		 	task_switch("IdleTask", 0,SWITCH_SPEC_TASK);
		 #else		
		 	task_switch("BtStackTask", 0,SWITCH_SPEC_TASK);
		 #endif
        #endif/*POWERUP_DEV_IGNORE*/
    #endif/*BT_BACKMODE*/
        if(file_operate_get_total_phydev()>1)
            return true;
        return false;
#endif/*S10_MODE*/
}

/*----------------------------------------------------------------------------*/
/**@brief  ÊÅ¢Â§çUSBÂè£‰∏∫ÊôÆÈÄöIOÂè£
   @param  void
   @return void
   @note   void usb_2_io(void)
*/
/*----------------------------------------------------------------------------*/
void usb_2_io(void)
{
    sys_det_puts("USB_2_IO\n");
    USB_CON0 |= BIT(0)|BIT(1);//PHY_ON(enable)  IO_MODE(enable)
    USB_IO_CON = 0;
}

static void fm_powerdown_init(void)
{
    FMA_CON0  = 0;
    FMA_CON1  = 0;
    FMA_CON2  = 0;
    FMA_CON3  = 0;
    FM_DSADC_CON = 0;
    FM_HWFE_CON = 0;
    FM_DSP_CON = 0;

    FM2CPU_PND  = 0;
    SFR(FM2CPU_IE, 9, 1,  0);      // FM_LOFC_IE
    SFR(FM2CPU_IE, 2, 1,  0);      // FM_VOICE_IE
    FM_LOFC_CON = 0;
    RFI_CON &= ~(1<<0);         // fm_rst
    delay(500);
    SFR(CLK_CON1, 12, 2, 3);    // CLOSE 80M 96M
}

/*----------------------------------------------------------------------------*/
/**@brief
   @param  void
   @return void
   @note   void sys_init(void)
*/
/*----------------------------------------------------------------------------*/
void sys_init(void)
{
    u8 err;
    err = os_sem_create(&power_sem,0) ;
	if(err != OS_NO_ERR)
	{
		sys_det_puts("create power_sem err \r\n") ;
		return ;
	}
#if S10_MODE
    usb_2_io();
#endif
	key_init();
	pa_umute();

#if FM_RADIO_EN
	fm_hw_init();
#endif

#if RTC_CLK_EN
    irtc_hw_init();
#endif

	fm_powerdown_init();

	aux_init_api();
	//led_init();
}

#ifdef support_send_ir_code
 u8 send_val;// send code  val
 u8 send_timer; // send code  timer   11--108ms 
 bool vol_key_sw; // vol_key  0:false  1:true

//muzhe 2012 02 04
#if 1
#define ir_send_num1    1630// 900     9ms         ∆ º µ◊
#define ir_send_num2    818//400//  4.5ms       ∆ º ∏ﬂ
#define ir_send_num3    102 //50    0.56ms             ˝æ›0
#define ir_send_num4    280   //   1.56 ms             ˝æ› 1
#else
#define ir_send_num1    900// 900     9ms         ∆ º µ◊
#define ir_send_num2    450//400//  4.5ms       ∆ º ∏ﬂ
#define ir_send_num3    56 //50    0.56ms             ˝æ›0
#define ir_send_num4    156   //   1.56 ms             ˝æ› 1
#endif

void   IRSendDelay(u16 delay_data)
{
   u16  i;
    for(i=0;i<delay_data;i++)
    {
	    delay(64);
    }
}


//#include "msg.h"

//	

 bool send_end;
void   IRSendData(void)
{
#if 1

//   if((workmode==AC3_WORK_MODE)&&(bModeOfAuxContained==mode_ac3))
   if(workmode==AC3_WORK_MODE)
   	{
   		if((send_timer==1))	// 108ms µΩ	
   			{
//				if(send_end==1)
//				return;
//				send_end=1;
				IRSendInital( send_val);
			puts("121\n");

	
//				send_end=0;	  
			}
	}

#else
   if((workmode==AC3_WORK_MODE)&&(bModeOfAuxContained==mode_ac3))
//   if((bModeOfAuxContained==mode_ac3))
 	{
		if((send_timer==1)||((vol_key_sw==1)&&(send_timer==1)))	// 108ms µΩ
		{
			if(send_end==1)
			return;

			send_end=1;

			IRSendInital( send_val);
			send_end=0;			
		}
		else if((vol_key_sw==1)&&(send_timer%11==1))	// long  send code
		{
			if(send_end==1)
			return;

			send_end=1;

			IRSendLongInital();
			send_end=0;			
		}
 	}
	

//   if((workmode==AC3_WORK_MODE)&&(bModeOfAuxContained==mode_ac3))
   if((bModeOfAuxContained==mode_ac3))
 	{
		if((send_timer==1)||((vol_key_sw==1)&&(send_timer==1)))	// 108ms µΩ
		{
			if(send_end==1)
			return;

			send_end=1;

			IRSendInital( send_val);
			send_end=0;			
		}
		else if((vol_key_sw==1)&&(send_timer%11==1))	// long  send code
		{
			if(send_end==1)
			return;

			send_end=1;

			IRSendLongInital();
			send_end=0;			
		}
 	}

   
   if((workmode==AC3_WORK_MODE)&&(bModeOfAuxContained==mode_ac3))
 	{
		if(send_end==1)
			return;

		
		if(send_val==0xff)	
			return;
		
		send_end=1;

		IRSendInital( send_val);
		send_end=0;			
 	}
#endif   
}

void   IRSendLongInital(void)
{
     u8 i;
	 


	// ¡¨∑¢¬Î  IR CODE  9ms+2.25ms	  
	     hw_ClrIRsend_Pin();        
	     IRSendDelay(ir_send_num1);  //9ms
	     hw_SetIRsend_Pin();
	     IRSendDelay(ir_send_num4);   //4// 1.65ms
	     hw_ClrIRsend_Pin();        
	     IRSendDelay(ir_send_num3);  // 0.65ms

             hw_SetIRsend_Pin();     
 //            IRSendDelay(ir_send_num3);   //0.56ms
	      	
		 //  Delay1ms(10);
	//	     INT_EN();

	 return;
}
void   IRSendInital(u8  ComData)
{
     u8 i,SendDATA,j;
	 

	
     //  DvdChangeCode(DATACODE);
   SendDATA =  ComData;// DVD_ChangeCode(ComData);

//    INT_DIS();  


	// HEARD  IR CODE	  
	     hw_ClrIRsend_Pin();        
	     IRSendDelay(ir_send_num1);  //9ms
	     hw_SetIRsend_Pin();
		// ResetTimer2(); 
	     IRSendDelay(ir_send_num2);   //4//4.5ms


	//   SYS IR CODE   0x01fe
	     for(i=0;i<8;i++) 
	        {
		          hw_ClrIRsend_Pin();      
		          IRSendDelay(ir_send_num3);   //0.56ms
		          hw_SetIRsend_Pin();     
			if(i==0)		  
		           IRSendDelay(ir_send_num4);   //0.56ms
			else           
		           IRSendDelay(ir_send_num3);   //0.56ms
	        }
	     
	       for(i=0;i<8;i++)
	        {
		         hw_ClrIRsend_Pin();      
		         IRSendDelay(ir_send_num3);   //0.56ms
		        hw_SetIRsend_Pin();        
			if(i==0)		  
		           IRSendDelay(ir_send_num3);   //0.56ms
			else           
		         IRSendDelay(ir_send_num4); // 1.56ms
	        }

	//   CODE IR CODE   
	    //=========================
	       j=0x01;
	       for(i=0;i<8;i++)
	        {
	         hw_ClrIRsend_Pin();     
	          IRSendDelay(ir_send_num3);   //0.56ms
	           if(SendDATA&j)         
	            {         
	              j <<=1;           
	             hw_SetIRsend_Pin();        
	             IRSendDelay(ir_send_num4); // 1.56ms
	            }
	        else
	            { 
	              j <<=1;              
	               hw_SetIRsend_Pin();        
	               IRSendDelay(ir_send_num3);   //0.56ms
	            }
	                    
	        }

	//   COMPLEMENT IR CODE          
	   //===================
	        SendDATA =~SendDATA;
	        j =0x01;
	        for(i=0;i<8;i++)
	        {
	          hw_ClrIRsend_Pin();     
	           IRSendDelay(ir_send_num3);   //0.56ms
	        
	         if(SendDATA&j)
	            {
	              j <<=1;
	               hw_SetIRsend_Pin();     
	              IRSendDelay(ir_send_num4); // 1.56ms
	            }
	        else
	            {
	              j<<=1;
	                hw_SetIRsend_Pin();       
	            
	               IRSendDelay(ir_send_num3);   //0.56ms
	            }
	                    
	        }        
	          hw_ClrIRsend_Pin();     
	           IRSendDelay(ir_send_num3);   //0.56ms
	            hw_SetIRsend_Pin();     

		     IRSendDelay(ir_send_num3);   //0.56ms	 	
		 //  Delay1ms(10);
	//	     INT_EN();

	 return;
}

#endif 



#ifdef support_battery_mode_check

void  LED_io_display_bat_mode(void)
{

  static bool  bat_cnt;

     switch (ldo_power_mod)
     	{
		case   0:   
			break;
		case  1 :
		case  2:
			LED_BAT_1_ON();
			LED_BAT_2_ON();
			LED_BAT_3_ON();
		break;
		
		case  3:
			LED_BAT_1_ON();
			LED_BAT_2_ON();
			LED_BAT_3_OFF();
		break;
		
		case  4:
			LED_BAT_1_ON();
			LED_BAT_2_OFF();
			LED_BAT_3_OFF();
		break;		
		case 5:
		case 6:
			LED_BAT_2_OFF();
			LED_BAT_3_OFF();			
			bat_cnt=~bat_cnt;
			if (bat_cnt )
				{
					LED_BAT_1_ON();
				}
			else
				{
					LED_BAT_1_OFF();
				}
		break;

     	}

 }

#endif 


