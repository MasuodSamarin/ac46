#include "config.h"

#ifdef NEW_LED_SHOW_METHOD
#include "led.h"
#include "led7_drv.h"
#ifdef EQ_ADC_VALUE_DETECT
#include "key_drv_ad.h"
#include "dac_api.h"
extern u16 adc_value[MAX_AD_CHANNEL];
#endif

#ifdef GW_827BT
bool bIfRunTimer=TRUE;
u8 bRGBMode=2;
#endif
#ifdef LED_ONOFF_CONTROL_WITH_KEY
bool bRgbIfRun=TRUE;
u8 bRgbMode=2;
bool brevise=FALSE;
#endif
#ifdef SUPPORT_BREATH_LIGHT
u8 blightDutySteps;
bool blightIfRunPwm;
#endif

u8 show_led_num[LED_NUMS];
u8 show_led_mode[LED_NUMS];
u8 show_led_time[LED_NUMS];

void setLedLight(u8 ledId,u8 showMode,u8 falshTime)//set one light how to show
{
    show_led_num[ledId-1]=ledId;
    show_led_mode[ledId-1]=showMode;
    show_led_time[ledId-1]=falshTime;
}
void showLed(u8 ledId,bool onOff){
  switch(ledId){
  #if LED_NUMS>=1
		 case 1:
		   if(onOff){LED1_ON();}
		   else
		   	{LED1_OFF();}
		  break;
  #endif
  #if LED_NUMS>=2
		 case 2:
		   if(onOff){LED2_ON();}
		   else {LED2_OFF();}
		  break;
  #endif	
#if LED_NUMS>=3
		 case 3:
		   if(onOff){LED3_ON();}
		   else {LED3_OFF();}
		  break;
#endif	  
#if LED_NUMS>=4
		  case 4:
			if(onOff){LED4_ON();}
			else {LED4_OFF();}
		   break;
#endif	 
#if LED_NUMS>=5
		  case 5:
			if(onOff){LED5_ON();}
			else {LED5_OFF();}
		   break;
#endif	  
#if LED_NUMS>=6
		  case 6:
			if(onOff){LED6_ON();}
			else {LED6_OFF();}
		   break;
#endif	  
#if LED_NUMS>=7
			 case 7:
			   if(onOff){LED7_ON();}
			   else {LED7_OFF();}
			  break;
#endif	  

   default:
   	break;
  }
}
void showLedMode(u8 *ledNum,u8 *showMode,u8 *flashTime){
   static u8 cnt_led[LED_NUMS],i;
   for(i=0;i<LED_NUMS;i++){
#ifdef SUPPORT_BREATH_LIGHT
	if((bRgbMode==1)&&(i!=3))continue;
#elif defined(ONLY_SWITCH_RGB_LIGHT)	
    if((bRgbMode==1)&&(i!=3))continue;
#endif
   switch(showMode[i]){
     case 0: //light off
	 showLed(ledNum[i],FALSE);
	 break;
	 case 1://light on
	 showLed(ledNum[i],TRUE);
	 break;
	 case 2://light flash fast all the time
		 cnt_led[i]++;
		 if(cnt_led[i] > 16)
		 {
			 cnt_led[i] = 0;
		 }
		 
		 if(cnt_led[i] > 8) //50ms
		 {
			 showLed(ledNum[i],TRUE);
		 }
		 else
		 {
			 showLed(ledNum[i],FALSE);
		 }		 	 
	 break;
	 case 3://light flash slowly all the time
		 cnt_led[i]++;
		 if(cnt_led[i] > 100)
		 {
			 cnt_led[i] = 0;
		 }
		 
		 if(cnt_led[i] > 50)
		 {
			 showLed(ledNum[i],TRUE);
		 }
		 else
		 {
			 showLed(ledNum[i],FALSE);
		 }	 	
	 break;
	 case 4://light flash fast for a moment
	 flashTime[i]--;
	 if(flashTime[i]>0){
		 cnt_led[i]++;
		 if(cnt_led[i] > 16)
		 {
			 cnt_led[i] = 0;
		 }
		 
		 if(cnt_led[i] > 8) //50ms
		 {
			 showLed(ledNum[i],TRUE);
		 }
		 else
		 {
			 showLed(ledNum[i],FALSE);
		 }		 	 
	 }	else {
	 showMode[i]=led_mode_on; //after flashing the moment default setting light on
	 flashTime[i]=0;
	 }
	 break;
	 case 5://light on for a moment then light off
	 if(flashTime[i])
	 flashTime[i]--;
	 if(flashTime[i])
	 showLed(ledNum[i],TRUE);
	 if(flashTime[i]==0)
	 showLed(ledNum[i],FALSE);
	 break;
   }
   	}
}

#ifdef SUPPORT_RGB_BREATH_LAMP

enum
{
LED_OFF=0,
LED_RED,
LED_GREEN,
LED_BLUE,
LED_RG,
LED_GB,
LED_RB,
LED_RGB,
};

void RGB_LIGHT_MODE(u8 mode)
{
#if 1
  switch(mode){
  case 0: //all close
    LED_R_OFF();; //r
    LED_G_OFF(); //g
    LED_B_OFF(); //b
    break;
  case 1: //red on
    LED_R_ON();; //r
    LED_G_OFF(); //g
    LED_B_OFF(); //b
    break;
  case 2: //green on
	    LED_R_OFF();; //r
	    LED_G_ON(); //g
	    LED_B_OFF(); //b
	break;
  case 3: //blue on
	    LED_R_OFF();; //r
	    LED_G_OFF(); //g
	    LED_B_ON(); //b
	break;		
  case 4: //red and green on
	    LED_R_ON();; //r
	    LED_G_ON(); //g
	    LED_B_OFF(); //b
	break;		
  case 5: //green and blue on
	    LED_R_OFF();; //r
	    LED_G_ON(); //g
	    LED_B_ON(); //b
	break;		
  case 6: //red and blue on
	    LED_R_ON();; //r
	    LED_G_OFF(); //g
	    LED_B_ON(); //b
	break;	
  case 7: //red green blue on
	    LED_R_ON();; //r
	    LED_G_ON(); //g
	    LED_B_ON(); //b
	break;		
  default:
    break;    
	}
#endif
}
u8 led_mode;
u8 rgb_mode;
u8 led_rgb_mode;

void pwm_led_rgb_scan(void)  // 0.1ms
{	
	led_rbg_main(led_mode,rgb_mode);
}


void pwm_r_led(u16 white_timer)
{ 
	static u16 cnt;

	if(cnt<=white_timer*8)
	{
		LED_R_ON();
	}
	else
	{
		LED_R_OFF();
	}

	cnt++;
	if(cnt==160)
		cnt=0;	
}
void pwm_g_led(u16 white_timer)
{ 
	static u16 cnt;

	if(cnt<=white_timer*8)
	{
		LED_G_ON();
	}
	else
	{
		LED_G_OFF();
	}

	cnt++;
	if(cnt==160)
		cnt=0;	
}
void pwm_b_led(u16 white_timer)
{ 
	static u16 cnt;

	if(cnt<=white_timer*8)
	{
		LED_B_ON();
	}
	else
	{
		LED_B_OFF();
	}

	cnt++;
	if(cnt==160)
		cnt=0;		
}
void pwm_rg_led(u16 white_timer)
{ 
	static u16 cnt;

	if(cnt<=white_timer*8)
		{
			LED_R_ON();
			LED_G_ON();
		}
		else
		{
			LED_R_OFF();
			LED_G_OFF();
		}
	cnt++;
	if(cnt==160)
		cnt=0;	
	
}
void pwm_rb_led(u16 white_timer)
{ 
	static u16 cnt;
	
	if(cnt<=white_timer*8)
		{
			LED_R_ON();
			LED_B_ON();
		}
		else
		{
			LED_R_OFF();
			LED_B_OFF();
		}
	cnt++;
	if(cnt==160)
		cnt=0;	

}
void pwm_gb_led(u16 white_timer)
{ 
	static u16 cnt;

	if(cnt<=white_timer*8)
		{
			LED_G_ON();
			LED_B_ON();
		}
		else
		{
			LED_G_OFF();
			LED_B_OFF();
		}

	cnt++;
	if(cnt==160)
		cnt=0;	
		
}

void pwm_rgb_led(u16 white_timer)
{ 
	static u16 cnt;

	if(cnt<=white_timer*8)
		{
			LED_R_ON();
			LED_G_ON();
			LED_B_ON();
		}
		else
		{
			LED_R_OFF();		
			LED_G_OFF();
			LED_B_OFF();
		}

	cnt++;
	if(cnt==160)
		cnt=0;	
		
}

#define ADC_1 1023*1/14
#define ADC_2 1023*3/14
#define ADC_3 1023*5/14
#define ADC_4 1023*7/14
#define ADC_5 1023*9/14
#define ADC_6 1023*11/14
#define ADC_7 1023*13/14


u8 adc_energy_steps(u32 energy)
{

//	printf(" energy  1111  %d \n",energy);

    if (energy<=ADC_1/2)return 0;
    if (energy<=ADC_1)return 1;
    if (energy<=ADC_2)return 2;
    if (energy<=ADC_3)return 3;
    if (energy<=ADC_4)return 4;
    if (energy<=ADC_5)return 5;
    if (energy<=ADC_6)return 6;
    if (energy<=ADC_7)return 7;	
	return 8;
	
}


u8 freq_val;
#include "key_drv_ad.h"
void freq_det_main()
{
	static u8 cnt,cnt1;
	
//	freq_val=(adc_energy_steps(get_dac_energy_value()>>16));
		freq_val=(adc_energy_steps(adc_value[AD_CH_RGB]));

//	printf(" (adc_energy_steps(adc_value[AD_CH_RGB])): %x \n",(freq_val));
#if 1	

	if(freq_val<=0)
	{
		if(++cnt>=50)
		{
			cnt=0;
			cnt1=0;			
			led_mode=0;
			rgb_mode=1;
		}	
	}	
	else
	{
		if(++cnt1>=50)
		{
			cnt1=0;			
			cnt=0;
			led_mode=0;
			rgb_mode=2;
		}	
	}	
#endif	

}

void led_rbg_main(u8 mode,u8 rgbmode)  // 0.1ms
{
	static u32 Cnt,cnt1;

	mode=mode;	
	
	
	switch(rgbmode)
 	  	{
	 		case 1: 

			RGB_LIGHT_MODE(0); // off_rgb

#if 1  // °×-ºì-ÂÌ-À¶-ÂÌ-×Ï-Çà
				Cnt++;
				
				if(Cnt<30000) //r++
				{				
						RGB_LIGHT_MODE(LED_RGB); // 
				}					
				else if(Cnt<=90000)  //g++
				{		
						RGB_LIGHT_MODE(LED_RED); // 
				}					
				else if(Cnt<=120000) //g --
				{			
						RGB_LIGHT_MODE(LED_GREEN); // 
				}	
				
				else if(Cnt<=150000)  //b++
				{			
						RGB_LIGHT_MODE(LED_BLUE); // 
				}	
				else if(Cnt<=180000)  //b--
				{			
						RGB_LIGHT_MODE(LED_GREEN); // 
				}	
				
				else if(Cnt<=210000)  //rg++
				{			
						RGB_LIGHT_MODE(LED_RB); // 
				}	
				else if(Cnt<=240000)  // rg--
				{			
						RGB_LIGHT_MODE(LED_GB); // 
				}							
				else if(Cnt>=240000) //--
					{
 					 	Cnt=6;
						RGB_LIGHT_MODE(LED_RGB); // 
					}
#else
				Cnt++;
				 // r++ -- g++ --  b++ --  rg++ --  rb++ --  gb++ --  rgb++ --
				if(Cnt<30000) //r++
				{				
					pwm_rgb_led(Cnt/1034+1);					
				}					
				else if(Cnt<60000) //r --
				{				
					pwm_rgb_led((60000-Cnt)/1071+1);					
				}
				else if(Cnt<=90000)  //g++
				{		
					pwm_r_led((Cnt-60000)/1034+1);					
				}					
				else if(Cnt<=120000) //g --
				{			
					pwm_r_led((120000-Cnt)/1071+1);					
				}	
				
				else if(Cnt<=150000)  //b++
				{			
					pwm_g_led((Cnt-120000)/1034+1);					
				}	
				else if(Cnt<=180000)  //b--
				{			
					pwm_g_led((180000-Cnt)/1071+1);					
				}	
				
				else if(Cnt<=210000)  //rg++
				{			
					pwm_b_led((Cnt-180000)/1034+1);					
				}	
				else if(Cnt<=240000)  // rg--
				{			
					pwm_b_led((240000-Cnt)/1071+1);					
				}			

				else if(Cnt<=270000)  //rb++
				{			
					pwm_rgb_led((Cnt-240000)/1034+1);					
				}	
				else if(Cnt<=300000)  //rb--
				{			
					pwm_rgb_led((300000-Cnt)/1071+1);					
				}

				else if(Cnt<=330000)  //gb++
				{			
					pwm_g_led((Cnt-300000)/1034+1);					
				}	
				else if(Cnt<=360000)  //gb--
				{			
					pwm_g_led((360000-Cnt)/1071+1);					
				}

				else if(Cnt<=390000)  //rgb++
				{			
					pwm_rb_led((Cnt-360000)/1034+1);					
				}	
				else if(Cnt<=420000)  //rgb--
				{			
					pwm_rb_led((420000-Cnt)/1071+1);					
				}

				else if(Cnt<=450000)  //rgb++
				{			
					pwm_gb_led((Cnt-420000)/1034+1);					
				}	
				else if(Cnt<=480000)  //rgb--
				{			
					pwm_gb_led((480000-Cnt)/1071+1);					
				}	
				
				else if(Cnt>=480000) //--
					{
 					 	Cnt=6;
						pwm_r_led(Cnt/1034+1);					
					}
#endif		
	 			break;
				
	 		case 2: 

#if 1
				cnt1++;
				 // rb b g rg r
				if(cnt1==400) 
					{
						RGB_LIGHT_MODE(0); // off_rgb					
						cnt1=0;
						if(freq_val>1)
						{											
							RGB_LIGHT_MODE(freq_val-1);
						}			
						else
							RGB_LIGHT_MODE(freq_val);					
					}
#else
				cnt1++;
				 // rb b g rg r
				if(cnt1<30000) //°×
				{											
					pwm_rgb_led(freq_val);					
				}					
				else if(cnt1<=60000)  //ºç
				{						
					pwm_r_led(freq_val);					
				}					
				else if(cnt1<=90000) // ÂÌ
				{						
					pwm_g_led(freq_val);					
				}		
				else if(cnt1<=120000)  // À¶
				{						
					pwm_b_led(freq_val);					
				}	
				else if(cnt1<=150000)  // °×
				{						
					pwm_rgb_led(freq_val);					
				}	

				else if(cnt1<=180000) // ÂÌ
				{						
					pwm_g_led(freq_val);					
				}			
				else if(cnt1<=210000) //×Ï
				{						
					pwm_rb_led(freq_val);					
				}	
				else if(cnt1<=240000) // Çà
				{						
					pwm_gb_led(freq_val);					
				}	
				
				else if(cnt1>=150000) //
					{
 					 	cnt1=0;
 						pwm_r_led(freq_val);											
					}
#endif			
			break;
				
	 		default:
	 			break;
 	 	 }
  
}


#endif


#ifdef SUPPORT_ZY_4LED_RGB

enum
{
LED_RED=0,
LED_GREEN,
LED_BLUE,
LED_RG,
LED_GB,
LED_RB,
};

void RGB_LIGHT_MODE(u8 mode)
{
#if 1
  switch(mode){
  case 0: //all close
    LED_R_OFF();; //r
    LED_G_OFF(); //g
    LED_B_OFF(); //b
    break;
  case 1: //red on
    LED_R_ON();; //r
    LED_G_OFF(); //g
    LED_B_OFF(); //b
    break;
  case 2: //green on
	    LED_R_OFF();; //r
	    LED_G_ON(); //g
	    LED_B_OFF(); //b
	break;
  case 3: //blue on
	    LED_R_OFF();; //r
	    LED_G_OFF(); //g
	    LED_B_ON(); //b
	break;		
  case 4: //red and green on
	    LED_R_ON();; //r
	    LED_G_ON(); //g
	    LED_B_OFF(); //b
	break;		
  case 5: //green and blue on
	    LED_R_OFF();; //r
	    LED_G_ON(); //g
	    LED_B_ON(); //b
	break;		
  case 6: //red and blue on
	    LED_R_ON();; //r
	    LED_G_OFF(); //g
	    LED_B_ON(); //b
	break;		
  default:
    break;    
	}
#endif
}
u8 led_mode;
u8 rgb_mode;
u8 led_rgb_mode;

void pwm_led_rgb_scan(void)  // 0.1ms
{

			
	led_rbg_main(led_mode,rgb_mode);

}

void pwm_white_led(u16 white_timer)
{ 
	static u16 cnt;

	if(cnt<=white_timer*40)
	{
		LED_W_ON();
	}
	else
	{
		LED_W_OFF();
	}

	cnt++;
	if(cnt==120)
		cnt=0;	
}

void pwm_r_led(u16 white_timer)
{ 
	static u16 cnt;

	if(cnt<=white_timer*16)
	{
		LED_R_ON();
	}
	else
	{
		LED_R_OFF();
	}

	cnt++;
	if(cnt==160)
		cnt=0;	
}
void pwm_g_led(u16 white_timer)
{ 
	static u16 cnt;

	if(cnt<=white_timer*16)
	{
		LED_G_ON();
	}
	else
	{
		LED_G_OFF();
	}

	cnt++;
	if(cnt==160)
		cnt=0;	
}
void pwm_b_led(u16 white_timer)
{ 
	static u16 cnt;

	if(cnt<=white_timer*16)
	{
		LED_B_ON();
	}
	else
	{
		LED_B_OFF();
	}

	cnt++;
	if(cnt==160)
		cnt=0;		
}
void pwm_rg_led(u16 white_timer)
{ 
	static u16 cnt;

	if(cnt<=white_timer*16)
		{
			LED_R_ON();
			LED_G_ON();
		}
		else
		{
			LED_R_OFF();
			LED_G_OFF();
		}
	cnt++;
	if(cnt==160)
		cnt=0;	
	
}
void pwm_rb_led(u16 white_timer)
{ 
	static u16 cnt;
	
	if(cnt<=white_timer*16)
		{
			LED_R_ON();
			LED_B_ON();
		}
		else
		{
			LED_R_OFF();
			LED_B_OFF();
		}
	cnt++;
	if(cnt==160)
		cnt=0;	

}
void pwm_gb_led(u16 white_timer)
{ 
	static u16 cnt;

	if(cnt<=white_timer*16)
		{
			LED_G_ON();
			LED_B_ON();
		}
		else
		{
			LED_G_OFF();
			LED_B_OFF();
		}

	cnt++;
	if(cnt==160)
		cnt=0;	
		
}



#define ADC_1 0x0F
#define ADC_2 0x10
#define ADC_3 0x20
#define ADC_4 0x30
#define ADC_5 0x40
#define ADC_6 0x50
#define ADC_7 0x60


u8 adc_energy_steps(u32 energy)
{

//	printf(" energy  1111  %d \n",energy);

    if (energy<=ADC_1/2)return 0;
    if (energy<=ADC_1)return 1;
    if (energy<=ADC_2)return 2;
    if (energy<=ADC_3)return 3;
    if (energy<=ADC_4)return 4;
    if (energy<=ADC_5)return 5;
    if (energy<=ADC_6)return 6;
    if (energy<=ADC_7)return 7;	
	return 8;	
}


u8 freq_val;

void freq_det_main()
{
	freq_val=(adc_energy_steps(get_dac_energy_value()>>16));
	
//	printf(" (get_dac_energy_value())  1111 %x \n",(get_dac_energy_value()));
	
}

void led_rbg_main(u8 mode,u8 rgbmode)
{

	static u32 Cnt,cnt1;
	
	if(led_rgb_mode==0)
	{
		if(mode==0)
		{
			RGB_LIGHT_MODE(0); // off_rgb
		       LED_W_OFF();	 // off w_led	
		}
		else if(mode<=3)
		{
			RGB_LIGHT_MODE(0); // off_rgb
			pwm_white_led(mode);  // 
		}
	
	}

else 
	{
		//  r b g rb  gb    
		
// RGB_LIGHT_MODE ²ÎÊý ( 1 -R  2-G 3-B 4-RG 5-GB 6-rb)
	
#if 1
	       LED_W_OFF();		
		RGB_LIGHT_MODE(0); // off_rgb
		
		switch(rgbmode)
	 	  	{
		 		case 0: //R 	
		 			Cnt=10;		 		
		 			RGB_LIGHT_MODE(1);
		 		break;
		 		case 1: //B
		 			RGB_LIGHT_MODE(3);
		 		break;
		 		case 2: //G
		 			RGB_LIGHT_MODE(2);
		 		break;
		 		case 3: //rb
		 			RGB_LIGHT_MODE(6);
		 		break;
		 		case 4: //gb
		 			RGB_LIGHT_MODE(5);
		 		break;				
		 		case 5: 

#if 1
				/* G->GR++->RG-- ->rb++ ->br-- ->bg++ -> gb--
		 		*/
		 		
					Cnt++;
					 // rb  r rg  g  gb  b 
					if(Cnt<30000) //++
					{				
		 				RGB_LIGHT_MODE(LED_GREEN);
						pwm_r_led(Cnt/1875+1);					
					}					
					else if(Cnt<60000) // --
					{				
		 				RGB_LIGHT_MODE(LED_RED);
						pwm_g_led((60000-Cnt)/1875+1);					
					}
					else if(Cnt<=90000)  //++
					{		
		 				RGB_LIGHT_MODE(LED_RED);					
						pwm_b_led((Cnt-60000)/1875+1);					
					}					
					else if(Cnt<=120000) // --
					{			
		 				RGB_LIGHT_MODE(LED_BLUE);					
						pwm_r_led((120000-Cnt)/1875+1);					
					}		
					else if(Cnt<=150000)  //++
					{			
		 				RGB_LIGHT_MODE(LED_BLUE);					
						pwm_g_led((Cnt-120000)/1875+1);					
					}	
					else if(Cnt<=180000)  //--
					{			
		 				RGB_LIGHT_MODE(LED_GREEN);					
						pwm_b_led((180000-Cnt)/1875+1);					
					}						
					else if(Cnt>=180000) //--
						{
	 					 	Cnt=6;
	 						pwm_rb_led(1);											
						}
#else
				/* µ­×ÏÉ«-×ÏÉ«
				    ºìÉ«
				    ½ÛÉ«
				    »ÆÉ«
				    µ­ÂÌ-ÂÌ
				    µ­À¶-À¶				    		 		
		 		*/
		 		
					Cnt++;
					 // rb  r rg  g  gb  b 
					if(Cnt<30000) //++
					{											
						pwm_rb_led(Cnt/1875+1);					
					}					
					else if(Cnt<60000) // --
					{						
						pwm_rb_led((60000-Cnt)/1875+1);					
					}
					else if(Cnt<=90000)  //++
					{						
						pwm_r_led((Cnt-60000)/1875+1);					
					}					
					else if(Cnt<=120000) // --
					{						
						pwm_r_led((120000-Cnt)/1875+1);					
					}		
					else if(Cnt<=150000)  //++
					{						
						pwm_rg_led((Cnt-120000)/1875+1);					
					}	
					else if(Cnt<=180000)  //--
					{						
						pwm_rg_led((180000-Cnt)/1875+1);					
					}		
					else if(Cnt<=210000)  //++
					{						
						pwm_g_led((Cnt-180000)/1875+1);					
					}	
					else if(Cnt<=240000)  //--
					{						
						pwm_g_led((240000-Cnt)/1875+1);					
					}		
					else if(Cnt<=270000)  //++
					{						
						pwm_gb_led((Cnt-240000)/1875+1);					
					}	
					else if(Cnt<=300000)  //--
					{						
						pwm_gb_led((300000-Cnt)/1875+1);					
					}	
					
					else if(Cnt>=300000) //--
						{
	 					 	Cnt=6;
	 						pwm_rb_led(1);											
						}
#endif					
		 			break;
		 		case 6: 
#if 1
					if(freq_val<=0)
						break;
					cnt1++;
					 // rb b g rg r
					if(cnt1<30000) //×Ï
					{											
						pwm_rb_led(freq_val);					
					}					
					else if(cnt1<=60000)  // À¶
					{						
						pwm_b_led(freq_val);					
					}					
					else if(cnt1<=90000) // ÂÌ
					{						
						pwm_g_led(freq_val);					
					}		
					else if(cnt1<=120000)  // »Æ
					{						
						pwm_rg_led(freq_val);					
					}	
					else if(cnt1<=150000)  // ºì
					{						
						pwm_r_led(freq_val);					
					}							
					else if(cnt1>=150000) //
						{
	 					 	cnt1=0;
	 						pwm_r_led(freq_val);											
						}
#else
					if(freq_val<=0)
						break;
					cnt1++;
					 // r b gb g rb
					if(cnt1<30000) //ºì
					{											
						pwm_r_led(freq_val);					
					}					
					else if(cnt1<=60000)  // À¶
					{						
						pwm_b_led(freq_val);					
					}					
					else if(cnt1<=90000) // µ­À¶
					{						
						pwm_gb_led(freq_val);					
					}		
					else if(cnt1<=120000)  // ÂÌ
					{						
						pwm_g_led(freq_val);					
					}	
					else if(cnt1<=150000)  // »Æ
					{						
						pwm_rg_led(freq_val);					
					}							
					else if(cnt1>=150000) //
						{
	 					 	cnt1=0;
	 						pwm_r_led(freq_val);											
						}	
#endif					
				break;
					
		 		default:
		 			break;
	 	 	 }


#else

					Cnt++;
					 
					if(Cnt<3000)
					{											
						pwm_rb_led(Cnt/6);					
					}
					else if(Cnt<6000)
					{						
						pwm_r_led((6000-Cnt)/6);					
					}
					else if(Cnt<=9000)
					{						
						pwm_rg_led((9000-Cnt)/6);					
					}
					else if(Cnt<=12000)
					{						
						pwm_g_led((Cnt-9000+6)/6);					
					}		
					else if(Cnt<=15000)
					{						
						pwm_b_led((Cnt-12000+6)/6);					
					}											
					else if(Cnt>=15000)
						{
	 					 	Cnt=6;
	 						pwm_rb_led(Cnt/6);											
						}

#endif		
	  
		 }
}


#endif

#if defined(GW_827BT)||defined(DJ_AC4601D_AC4601)

void RGB_LIGHT_MODE(u8 mode)
{
  switch(mode){
  case 0: //all close
    setLedLight(1,led_mode_off,0); //r
    setLedLight(2,led_mode_off,0); //g
    setLedLight(3,led_mode_off,0); //b
    break;
  case 1: //red on
	setLedLight(1,led_mode_on,0); //r
	setLedLight(2,led_mode_off,0); //g
	setLedLight(3,led_mode_off,0); //b
    break;
  case 2: //green on
	setLedLight(1,led_mode_off,0); //r
	setLedLight(2,led_mode_on,0); //g
	setLedLight(3,led_mode_off,0); //b
	break;
  case 3: //blue on
	setLedLight(1,led_mode_off,0); //r
	setLedLight(2,led_mode_off,0); //g
	setLedLight(3,led_mode_on,0); //b
	break;	
  case 4: //green on
	setLedLight(1,led_mode_off,0); //r
	setLedLight(2,led_mode_on,0); //g
	setLedLight(3,led_mode_off,0); //b
	break;	
  case 5: //red and green on
	setLedLight(1,led_mode_on,0); //r
	setLedLight(2,led_mode_on,0); //g
	setLedLight(3,led_mode_off,0); //b
	break;		
  case 6: //red and blue on
	setLedLight(1,led_mode_on,0); //r
	setLedLight(2,led_mode_off,0); //g
	setLedLight(3,led_mode_on,0); //b
	break;	
  case 7: //green and blue on
	setLedLight(1,led_mode_off,0); //r
	setLedLight(2,led_mode_on,0); //g
	setLedLight(3,led_mode_on,0); //b
	break;		
  case 8: //all on
    setLedLight(1,led_mode_on,0); //r
	setLedLight(2,led_mode_on,0); //g
	setLedLight(3,led_mode_on,0); //b
	break;	
  case 9: //red flash fast
	setLedLight(1,led_mode_flash_fast,0); //r
	setLedLight(2,led_mode_off,0); //g
	setLedLight(3,led_mode_off,0); //b
	break;	  
  case 10: //green flash fast
	setLedLight(1,led_mode_off,0); //r
	setLedLight(2,led_mode_flash_fast,0); //g
	setLedLight(3,led_mode_off,0); //b
	break;		
  case 11: //blue flash fast
	setLedLight(1,led_mode_off,0); //r
	setLedLight(2,led_mode_off,0); //g
	setLedLight(3,led_mode_flash_fast,0); //b
	break;
  case 12: //red and green flash fast
	setLedLight(1,led_mode_flash_fast,0); //r
	setLedLight(2,led_mode_flash_fast,0); //g
	setLedLight(3,led_mode_off,0); //b
	break;	
  case 13: //red and blue flash fast
	setLedLight(1,led_mode_flash_fast,0); //r
	setLedLight(2,led_mode_off,0); //g
	setLedLight(3,led_mode_flash_fast,0); //b
	break;		
  case 14: //green and blue flash fast
	setLedLight(1,led_mode_off,0); //r
	setLedLight(2,led_mode_flash_fast,0); //g
	setLedLight(3,led_mode_flash_fast,0); //b
	break;
  case 15: //red flash fast ,green on
	setLedLight(1,led_mode_flash_fast,0); //r
	setLedLight(2,led_mode_on,0); //g
	setLedLight(3,led_mode_off,0); //b
	break;		
  case 16: //red on ,green flash fast
	setLedLight(1,led_mode_on,0); //r
	setLedLight(2,led_mode_flash_fast,0); //g
	setLedLight(3,led_mode_off,0); //b
	break;	
  case 17: //red flash fast ,blue on
	setLedLight(1,led_mode_flash_fast,0); //r
	setLedLight(2,led_mode_off,0); //g
	setLedLight(3,led_mode_on,0); //b
	break;		
  case 18: //red on ,blue flash fast
	setLedLight(1,led_mode_on,0); //r
	setLedLight(2,led_mode_off,0); //g
	setLedLight(3,led_mode_flash_fast,0); //b
	break;		
  case 19: //green flash fast ,blue on
	setLedLight(1,led_mode_off,0); //r
	setLedLight(2,led_mode_flash_fast,0); //g
	setLedLight(3,led_mode_on,0); //b
	break;		
  case 20: //green on ,blue flash fast
	setLedLight(1,led_mode_off,0); //r
	setLedLight(2,led_mode_on,0); //g
	setLedLight(3,led_mode_flash_fast,0); //b
	break;	  
  case 21: //rgb all flash fast
	setLedLight(1,led_mode_flash_fast,0); //r
	setLedLight(2,led_mode_flash_fast,0); //g
	setLedLight(3,led_mode_flash_fast,0); //b
	break;		
  default:
    break;    
	}
}

#ifdef DJ_AC4601D_AC4601
void RGB_LIGHT_ARRAY_SHOW(bool ifRun,u8 mode)
	{
		static u16 cnt=0;//factory_random_cnt;	 
		static u8 not_flash_mode=1;//,flash_slow=22,flash_mode=9;
		
		//u8 random_value;
		
		//factory_random_cnt++;
		//if(factory_random_cnt>6000)factory_random_cnt=0;
		
	  if(mode==0)cnt=0; //press key off led light intime
	  if(!ifRun)return;
	  if(cnt==0){
	  switch(mode){
		case 0:  //close all
			RGB_LIGHT_MODE(0);
			break;
		case 1: //not flash mode
		case 2:
			if(mode==2){
			    #ifdef SUPPORT_BREATH_LIGHT
				blightDutySteps=0;
				#endif
				brevise=FALSE;
			}
			not_flash_mode++;
			if(not_flash_mode>8)not_flash_mode=1;
			RGB_LIGHT_MODE(not_flash_mode);
			break;
		default:
			break;
	  }
	  }
	  
	  cnt++;
	  if(mode==1){	
	  if(cnt>5)cnt=0;
	  }else{
	  if(cnt>200)cnt=0;
	  }
	}	
#else
void RGB_LIGHT_ARRAY_SHOW(bool ifRun,u8 mode)
{
	static u16 cnt,factory_random_cnt;   
	static u8 not_flash_mode=1,flash_mode=9;
	u8 random_value;
	
	factory_random_cnt++;
	if(factory_random_cnt>6000)factory_random_cnt=0;
	
	cnt++;
	if(cnt>200)cnt=0;
	
  if(!ifRun)return;
  if(cnt==200){
  switch(mode){
    case 0:  //close all
        RGB_LIGHT_MODE(0);
        break;
    case 1: //not flash mode
        not_flash_mode++;
        if(not_flash_mode>8)not_flash_mode=1;
        RGB_LIGHT_MODE(not_flash_mode);
        break;
    case 2: //flash mode
		flash_mode++;
		if(flash_mode>21)flash_mode=9;
		RGB_LIGHT_MODE(flash_mode);
		break;
	case 3://all flash all the time
	    RGB_LIGHT_MODE(21);
	    break;
    case 4://random mode
        random_value=((factory_random_cnt/21+cnt)*7)%22;
        if(random_value==0) random_value=1;
		RGB_LIGHT_MODE(random_value);
        break;
    default:
        break;
  }
  }
}
#endif
#endif

#if 0//def SUPPORT_BREATH_LIGHT
#ifdef EQ_ADC_VALUE_DETECT
void AUTO_DETECT_VOICE_AND_PRODUCE_PWM_VALUE(void)
{
    u8 sysVol;
	if(compare_task_name("IdleTask"))
		return;
	if((bRgbMode!=1)&&(bRgbMode!=2))return;
	if(adc_value[AD_CH_EQ]<10){
    	bRgbMode=2;
    	bRgbIfRun=TRUE;
	}
	else{	
	bRgbMode=1;
	bRgbIfRun=TRUE;
	blightIfRunPwm=TRUE;
	
	//10 15 20 25 30Â·Ã–Â±Ã°ÃŠÃ‡180 450 670 740 750
sysVol=dac_var.cur_sys_vol_l;
if(sysVol<=10){
	if(adc_value[AD_CH_EQ]<100)blightDutySteps=0;
	else
	blightDutySteps=PWM_STEPS_MAX;
}

else if(sysVol<=15){
	if(adc_value[AD_CH_EQ]<400)blightDutySteps=0;
	else
	blightDutySteps=PWM_STEPS_MAX;
}
	else if(sysVol<=20){
		if(adc_value[AD_CH_EQ]<600)blightDutySteps=0;
		else
		blightDutySteps=PWM_STEPS_MAX;
	}
	else if(sysVol<=25){
		if(adc_value[AD_CH_EQ]<680)blightDutySteps=0;
		else
		blightDutySteps=PWM_STEPS_MAX;
	}
	else if(sysVol<=30){
		if(adc_value[AD_CH_EQ]<720)blightDutySteps=0;
		else
		blightDutySteps=PWM_STEPS_MAX;
	}
}
}
#endif

#elif defined(ONLY_SWITCH_RGB_LIGHT)
	 #ifdef EQ_ADC_VALUE_DETECT
	 void AUTO_DETECT_VOICE_AND_PRODUCE_PWM_VALUE(void)
	 {
	     u8 sysVol;
	 	if(compare_task_name("IdleTask"))
	 		return;
	 	if((bRgbMode!=1)&&(bRgbMode!=2))return;
	 	if(adc_value[AD_CH_EQ]<10){
	     	bRgbMode=2;
	     	bRgbIfRun=TRUE;
	 	}
	 	else{	
	 	bRgbMode=1;
	 	bRgbIfRun=TRUE;	
	 	
	 	sysVol=dac_var.cur_sys_vol_l;
	 	if(sysVol<=10){
	 		if(adc_value[AD_CH_EQ]<30)blightDutySteps=0;
	 		else
	 		blightDutySteps=1;
	 	}
	 	
	 	else if(sysVol<=15){
	 		if(adc_value[AD_CH_EQ]<230)blightDutySteps=0;
	 		else
	 		blightDutySteps=1;
	 	}
	 		else if(sysVol<=20){
	 			if(adc_value[AD_CH_EQ]<310)blightDutySteps=0;
	 			else
	 			blightDutySteps=1;
	 		}
	 		else if(sysVol<=25){
	 			if(adc_value[AD_CH_EQ]<480)blightDutySteps=0;
	 			else
	 			blightDutySteps=1;
	 		}
	 		else if(sysVol<=30){
	 			if(adc_value[AD_CH_EQ]<650)blightDutySteps=0;
	 			else
	 			blightDutySteps=1;
	 		}
	 }
	 }
	 void SHOW_bRgbMode_1_LIGHT_INTIME(void)
	 {
	 	  if((bRgbMode!=1))return;
	 	  LIGHT_IO_INIT();
	 	  
	 	  if(blightDutySteps==1)	  
	 		 { 
	 		 if(bRgbMode==1){
	 		 if(show_led_mode[0]>0)
	 			 LIGHT_01(1);
	 		 if(show_led_mode[1]>0)
	 			 LIGHT_02(1);
	 		 if(show_led_mode[2]>0)
	 			 LIGHT_03(1);
	 			}else{
	 				 LIGHT_01(1);
	 				 LIGHT_02(1);
	 				 LIGHT_03(1);
	 			}
	 		 }
	 		 else
	 		 {
	 			 LIGHT_01(0);
	 			 LIGHT_02(0);
	 			 LIGHT_03(0);
	 		 }
	 }
	 #endif
#endif

#if 0//def SUPPORT_BREATH_LIGHT
void AUTO_CHANGE_LIGHT_DUTY_STEPS(void)
{
  static u8 cnt=0;
  
	if(bRgbMode!=2)return;
   if(cnt==0){
     if(!brevise){blightDutySteps++;
     if(blightDutySteps==PWM_STEPS_MAX)brevise=TRUE;
     }
     else {
     blightDutySteps--;
     if(blightDutySteps==0)brevise=FALSE;    
  }
  }
  cnt++;
  if(cnt>1)cnt=0;
}
void LightRunPWM()
{
  static u8 cnt;
  if((bRgbMode!=1))return;
  LIGHT_IO_INIT();
  cnt++;
  
  if(cnt<=blightDutySteps)    
     { 
     if(bRgbMode==1){
     if(show_led_mode[0]>0)
	     LIGHT_01(1);
     if(show_led_mode[1]>0)
	     LIGHT_02(1);
     if(show_led_mode[2]>0)
	     LIGHT_03(1);
	    }else{
			 LIGHT_01(1);
			 LIGHT_02(1);
			 LIGHT_03(1);
	    }
     }
     else
	 {
		 LIGHT_01(0);
		 LIGHT_02(0);
		 LIGHT_03(0);
	 }
  if(cnt>PWM_STEPS_MAX)
    cnt=0;
}
#endif

void led_scan(void)
{
#ifdef PLAY_SATU_LED_PORT_PA11		
    if(g_ad_led_flag)
        return;
#endif
#ifdef SUPPORT_USE_ADKEY_AS_AD_AND_LED		
    if(g_ad_led_flag)
        return;		
#endif

#ifdef GW_827BT
RGB_LIGHT_ARRAY_SHOW(bIfRunTimer,bRGBMode);
#elif defined(DJ_AC4601D_AC4601)
RGB_LIGHT_ARRAY_SHOW(bRgbIfRun,bRgbMode);
#endif

showLedMode(show_led_num,show_led_mode,show_led_time);
}

#ifdef ALL_LED_CONTROL_TOGETHER
void all_led_control_together(u8 mode)
{
  u8 i;
  for(i=0;i<LED_NUMS;i++)
  	setLedLight(i+1,mode,0);
}
#endif

#endif

