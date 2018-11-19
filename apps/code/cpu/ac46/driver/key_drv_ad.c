#include "includes.h"
#include "key_drv_ad.h"
#include "key.h"

#ifdef SUPPORT_USE_ADKEY_AS_AD_AND_LED
bool g_ad_led_flag;
#endif
#if 1//(!S10_MODE)
//u16 adc_value[3];
u16 adc_value[MAX_AD_CHANNEL];
const u32 ad_table[] =
{
#if  KEY_AD_EN      
    #ifdef support_adk_user_PA0
			AD_KEY_PA0,
    #elif defined(support_adk_user_PA8)
			AD_KEY_PA8,
    #elif defined(support_adk_user_PA14)
			AD_KEY_PA14,
    #elif defined(adk_io_use_pa0pa8)
        #ifdef ADK_PANEL_KEY_REVERSE
			AD_KEY_PA0, 	
			AD_KEY_PA8,
        #else
			AD_KEY_PA8, 	
			AD_KEY_PA0,
	    #endif
	#elif defined(adk_io_use_pa0pa11)
			AD_KEY_PA0,
			AD_KEY_PA11,	
    #else   //support_adk_user_PA14
			AD_KEY_PA14,
    #endif  
#endif 
//------11-------------------------
#ifdef DETECT_EXTERNAL_BAT_USE_PA8
			AD_KEY_PA8,
#elif defined(DETECT_EXTERNAL_BAT_USE_PA14)
			AD_KEY_PA14,			
#elif defined(DETECT_EXTERNAL_BAT_USE_PA0)
			AD_KEY_PA0,			
#endif
//------2222-------------------------

#ifdef EQ_ADC_VALUE_DETECT
    #ifdef EQ_DETECT_PIN_USE_PA11
		   AD_KEY_PA11,
    #elif defined(EQ_DETECT_PIN_USE_PA1)
		   AD_KEY_PA1,	
    #elif defined(EQ_DETECT_PIN_USE_PA8)
	       AD_KEY_PA8,
	#elif defined(EQ_DETECT_PIN_USE_PA14)
		   AD_KEY_PA14,
    #endif
#endif
//------3333-------------------------

#ifdef RGB_ADC_VALUE_DETECT
    #ifdef RGB_DETECT_PIN_USE_PA8
	       AD_KEY_PA8,
    #endif
#endif
//------444-------------------------

#ifdef KOK_DETECT_USE_IO_ADC_VALUE
	#ifdef KOK_DETECT_USE_PA11
		  AD_KEY_PA11,
	#elif defined KOK_DETECT_USE_PA14
		   AD_KEY_PA14,	
	#endif
#endif
//------5555-------------------------

		AD_KEY_LDOIN,
		AD_KEY_LDOREF,
};
#ifndef BT_TESTER
#if defined(ADK_USE_10KEY_MODE)
#define AD_RES_PULL  (u32)(PULL_UP_RESISTANCE*1000)

#define AD_RES1     (u32)(KEY0_NOKEY_RES*1000)
#define AD_RES2     (u32)(KEY1_RES*1000)
#define AD_RES3     (u32)(KEY2_RES*1000)
#define AD_RES4     (u32)(KEY3_RES*1000)
#define AD_RES5     (u32)(KEY4_RES*1000)
#define AD_RES6     (u32)(KEY5_RES*1000)
#define AD_RES7     (u32)(KEY6_RES*1000)
#define AD_RES8     (u32)(KEY7_RES*1000)
#define AD_RES9     (u32)(KEY8_RES*1000)
#define AD_RESA     (u32)(KEY9_RES*1000)

#define AD_VDD      (u32)0x3FF
#define AD_VOL1     (u32)(AD_RES1*100/(AD_RES1+AD_RES_PULL))*AD_VDD/100  // 2.97
#define AD_VOL2     (u32)(AD_RES2*100/(AD_RES2+AD_RES_PULL))*AD_VDD/100
#define AD_VOL3     (u32)(AD_RES3*100/(AD_RES3+AD_RES_PULL))*AD_VDD/100
#define AD_VOL4     (u32)(AD_RES4*100/(AD_RES4+AD_RES_PULL))*AD_VDD/100
#define AD_VOL5     (u32)(AD_RES5*100/(AD_RES5+AD_RES_PULL))*AD_VDD/100
#define AD_VOL6     (u32)(AD_RES6*100/(AD_RES6+AD_RES_PULL))*AD_VDD/100
#define AD_VOL7     (u32)(AD_RES7*100/(AD_RES7+AD_RES_PULL))*AD_VDD/100
#define AD_VOL8     (u32)(AD_RES8*100/(AD_RES8+AD_RES_PULL))*AD_VDD/100
#define AD_VOL9     (u32)(AD_RES9*100/(AD_RES9+AD_RES_PULL))*AD_VDD/100
#define AD_VOLA     (u32)0x0000

#define AD_GND      (u32)0x0000

#define AD_NOKEY    ((((u16)AD_VDD - AD_VOL1)/2) + AD_VOL1)
#define ADKEY1_0     ((((u16)AD_VOL1 - AD_VOL2)/2) + AD_VOL2)
#define ADKEY1_1     ((((u16)AD_VOL2 - AD_VOL3)/2) + AD_VOL3)
#define ADKEY1_2     ((((u16)AD_VOL3 - AD_VOL4)/2) + AD_VOL4)
#define ADKEY1_3     ((((u16)AD_VOL4 - AD_VOL5)/2) + AD_VOL5)
#define ADKEY1_4    ((((u16)AD_VOL5 - AD_VOL6)/2) + AD_VOL6)
#define ADKEY1_5     ((((u16)AD_VOL6 - AD_VOL7)/2) + AD_VOL7)
#define ADKEY1_6     ((((u16)AD_VOL7 - AD_VOL8)/2) + AD_VOL8)
#define ADKEY1_7     ((((u16)AD_VOL8 - AD_VOL9)/2) + AD_VOL9)
#define ADKEY1_8     ((((u16)AD_VOL9- AD_VOLA)/2) + AD_VOLA)

#elif defined(ADK_USE_11KEY_MODE)
#define AD_RES_PULL  (u32)(PULL_UP_RESISTANCE*1000)

#define AD_RES1     (u32)(KEY0_NOKEY_RES*1000)
#define AD_RES2     (u32)(KEY1_RES*1000)
#define AD_RES3     (u32)(KEY2_RES*1000)
#define AD_RES4     (u32)(KEY3_RES*1000)
#define AD_RES5     (u32)(KEY4_RES*1000)
#define AD_RES6     (u32)(KEY5_RES*1000)
#define AD_RES7     (u32)(KEY6_RES*1000)
#define AD_RES8     (u32)(KEY7_RES*1000)
#define AD_RES9     (u32)(KEY8_RES*1000)
#define AD_RESA     (u32)(KEY9_RES*1000)
#define AD_RESB     (u32)(KEYA_RES*1000)


#define AD_VDD      (u32)0x3FF
#define AD_VOL1     (u32)(AD_RES1*100/(AD_RES1+AD_RES_PULL))*AD_VDD/100
#define AD_VOL2     (u32)(AD_RES2*100/(AD_RES2+AD_RES_PULL))*AD_VDD/100
#define AD_VOL3     (u32)(AD_RES3*100/(AD_RES3+AD_RES_PULL))*AD_VDD/100
#define AD_VOL4     (u32)(AD_RES4*100/(AD_RES4+AD_RES_PULL))*AD_VDD/100
#define AD_VOL5     (u32)(AD_RES5*100/(AD_RES5+AD_RES_PULL))*AD_VDD/100
#define AD_VOL6     (u32)(AD_RES6*100/(AD_RES6+AD_RES_PULL))*AD_VDD/100
#define AD_VOL7     (u32)(AD_RES7*100/(AD_RES7+AD_RES_PULL))*AD_VDD/100
#define AD_VOL8     (u32)(AD_RES8*100/(AD_RES8+AD_RES_PULL))*AD_VDD/100
#define AD_VOL9     (u32)(AD_RES9*100/(AD_RES9+AD_RES_PULL))*AD_VDD/100
#define AD_VOLA     (u32)(AD_RESA*100/(AD_RESA+AD_RES_PULL))*AD_VDD/100
#define AD_VOLB     (u32)0x0000

#define AD_GND      (u32)0x0000

#define AD_NOKEY    ((((u16)AD_VDD - AD_VOL1)/2) + AD_VOL1)
#define ADKEY1_0     ((((u16)AD_VOL1 - AD_VOL2)/2) + AD_VOL2)
#define ADKEY1_1     ((((u16)AD_VOL2 - AD_VOL3)/2) + AD_VOL3)
#define ADKEY1_2     ((((u16)AD_VOL3 - AD_VOL4)/2) + AD_VOL4)
#define ADKEY1_3     ((((u16)AD_VOL4 - AD_VOL5)/2) + AD_VOL5)
#define ADKEY1_4    ((((u16)AD_VOL5 - AD_VOL6)/2) + AD_VOL6)
#define ADKEY1_5     ((((u16)AD_VOL6 - AD_VOL7)/2) + AD_VOL7)
#define ADKEY1_6     ((((u16)AD_VOL7 - AD_VOL8)/2) + AD_VOL8)
#define ADKEY1_7     ((((u16)AD_VOL8 - AD_VOL9)/2) + AD_VOL9)
#define ADKEY1_8     ((((u16)AD_VOL9- AD_VOLA)/2) + AD_VOLA)
#define ADKEY1_9     ((((u16)AD_VOLA- AD_VOLB)/2) + AD_VOLB)

#ifdef TWO_AD_IO_USE_DIFF_RESISTANCE
#define AD_RES_PULL1  (u32)(PULL_UP_RESISTANCE1*1000)

#define AD_RES11     (u32)(KEY0_NOKEY_RES1*1000)
#define AD_RES21     (u32)(KEY1_RES1*1000)
#define AD_RES31     (u32)(KEY2_RES1*1000)
#define AD_RES41     (u32)(KEY3_RES1*1000)
#define AD_RES51     (u32)(KEY4_RES1*1000)
#define AD_RES61     (u32)(KEY5_RES1*1000)
#define AD_RES71     (u32)(KEY6_RES1*1000)
#define AD_RES81     (u32)(KEY7_RES1*1000)
#define AD_RES91     (u32)(KEY8_RES1*1000)
#define AD_RESA1     (u32)(KEY9_RES1*1000)
#define AD_RESB1     (u32)(KEYA_RES1*1000)


#define AD_VDD1      (u32)0x3FF
#define AD_VOL11     (u32)(AD_RES11*100/(AD_RES11+AD_RES_PULL1))*AD_VDD1/100
#define AD_VOL21     (u32)(AD_RES21*100/(AD_RES21+AD_RES_PULL1))*AD_VDD1/100
#define AD_VOL31     (u32)(AD_RES31*100/(AD_RES31+AD_RES_PULL1))*AD_VDD1/100
#define AD_VOL41     (u32)(AD_RES41*100/(AD_RES41+AD_RES_PULL1))*AD_VDD1/100
#define AD_VOL51     (u32)(AD_RES51*100/(AD_RES51+AD_RES_PULL1))*AD_VDD1/100
#define AD_VOL61     (u32)(AD_RES61*100/(AD_RES61+AD_RES_PULL1))*AD_VDD1/100
#define AD_VOL71     (u32)(AD_RES71*100/(AD_RES71+AD_RES_PULL1))*AD_VDD1/100
#define AD_VOL81     (u32)(AD_RES81*100/(AD_RES81+AD_RES_PULL1))*AD_VDD1/100
#define AD_VOL91     (u32)(AD_RES91*100/(AD_RES91+AD_RES_PULL1))*AD_VDD1/100
#define AD_VOLA1     (u32)(AD_RESA1*100/(AD_RESA1+AD_RES_PULL1))*AD_VDD1/100
#define AD_VOLB1     (u32)0x0000

#define AD_GND1      (u32)0x0000

#define AD_NOKEY1    ((((u16)AD_VDD1 - AD_VOL11)/2) + AD_VOL11)
#define ADKEY1_01     ((((u16)AD_VOL11 - AD_VOL21)/2) + AD_VOL21)
#define ADKEY1_11     ((((u16)AD_VOL21 - AD_VOL31)/2) + AD_VOL31)
#define ADKEY1_21     ((((u16)AD_VOL31 - AD_VOL41)/2) + AD_VOL41)
#define ADKEY1_31     ((((u16)AD_VOL41 - AD_VOL51)/2) + AD_VOL51)
#define ADKEY1_41    ((((u16)AD_VOL51 - AD_VOL61)/2) + AD_VOL61)
#define ADKEY1_51     ((((u16)AD_VOL61 - AD_VOL71)/2) + AD_VOL71)
#define ADKEY1_61     ((((u16)AD_VOL71 - AD_VOL81)/2) + AD_VOL81)
#define ADKEY1_71     ((((u16)AD_VOL81 - AD_VOL91)/2) + AD_VOL91)
#define ADKEY1_81     ((((u16)AD_VOL91- AD_VOLA1)/2) + AD_VOLA1)
#define ADKEY1_91     ((((u16)AD_VOLA1- AD_VOLB1)/2) + AD_VOLB1)
#endif
#elif defined(ADK_USE_12KEY_MODE)
#define AD_RES_PULL  (u32)(PULL_UP_RESISTANCE*1000)

#define AD_RES1     (u32)(KEY0_NOKEY_RES*1000)
#define AD_RES2     (u32)(KEY1_RES*1000)
#define AD_RES3     (u32)(KEY2_RES*1000)
#define AD_RES4     (u32)(KEY3_RES*1000)
#define AD_RES5     (u32)(KEY4_RES*1000)
#define AD_RES6     (u32)(KEY5_RES*1000)
#define AD_RES7     (u32)(KEY6_RES*1000)
#define AD_RES8     (u32)(KEY7_RES*1000)
#define AD_RES9     (u32)(KEY8_RES*1000)
#define AD_RESA     (u32)(KEY9_RES*1000)
#define AD_RESB     (u32)(KEYA_RES*1000)
#define AD_RESC     (u32)(KEYB_RES*1000)

#define AD_VDD      (u32)0x3FF
#define AD_VOL1     (u32)(AD_RES1*100/(AD_RES1+AD_RES_PULL))*AD_VDD/100
#define AD_VOL2     (u32)(AD_RES2*100/(AD_RES2+AD_RES_PULL))*AD_VDD/100
#define AD_VOL3     (u32)(AD_RES3*100/(AD_RES3+AD_RES_PULL))*AD_VDD/100
#define AD_VOL4     (u32)(AD_RES4*100/(AD_RES4+AD_RES_PULL))*AD_VDD/100
#define AD_VOL5     (u32)(AD_RES5*100/(AD_RES5+AD_RES_PULL))*AD_VDD/100
#define AD_VOL6     (u32)(AD_RES6*100/(AD_RES6+AD_RES_PULL))*AD_VDD/100
#define AD_VOL7     (u32)(AD_RES7*100/(AD_RES7+AD_RES_PULL))*AD_VDD/100
#define AD_VOL8     (u32)(AD_RES8*100/(AD_RES8+AD_RES_PULL))*AD_VDD/100
#define AD_VOL9     (u32)(AD_RES9*100/(AD_RES9+AD_RES_PULL))*AD_VDD/100
#define AD_VOLA     (u32)(AD_RESA*100/(AD_RESA+AD_RES_PULL))*AD_VDD/100
#define AD_VOLB     (u32)(AD_RESB*100/(AD_RESB+AD_RES_PULL))*AD_VDD/100
#define AD_VOLC     (u32)0x0000

#define AD_GND      (u32)0x0000

#define AD_NOKEY    ((((u16)AD_VDD - AD_VOL1)/2) + AD_VOL1)
#define ADKEY1_0     ((((u16)AD_VOL1 - AD_VOL2)/2) + AD_VOL2)
#define ADKEY1_1     ((((u16)AD_VOL2 - AD_VOL3)/2) + AD_VOL3)
#define ADKEY1_2     ((((u16)AD_VOL3 - AD_VOL4)/2) + AD_VOL4)
#define ADKEY1_3     ((((u16)AD_VOL4 - AD_VOL5)/2) + AD_VOL5)
#define ADKEY1_4    ((((u16)AD_VOL5 - AD_VOL6)/2) + AD_VOL6)
#define ADKEY1_5     ((((u16)AD_VOL6 - AD_VOL7)/2) + AD_VOL7)
#define ADKEY1_6     ((((u16)AD_VOL7 - AD_VOL8)/2) + AD_VOL8)
#define ADKEY1_7     ((((u16)AD_VOL8 - AD_VOL9)/2) + AD_VOL9)
#define ADKEY1_8     ((((u16)AD_VOL9- AD_VOLA)/2) + AD_VOLA)
#define ADKEY1_9     ((((u16)AD_VOLA- AD_VOLB)/2) + AD_VOLB)
#define ADKEY1_A     ((((u16)AD_VOLB- AD_VOLC)/2) + AD_VOLC)


#ifdef TWO_AD_IO_USE_DIFF_RESISTANCE
#define AD_RES_PULL1  (u32)(PULL_UP_RESISTANCE1*1000)

#define AD_RES11     (u32)(KEY0_NOKEY_RES1*1000)
#define AD_RES21     (u32)(KEY1_RES1*1000)
#define AD_RES31     (u32)(KEY2_RES1*1000)
#define AD_RES41     (u32)(KEY3_RES1*1000)
#define AD_RES51     (u32)(KEY4_RES1*1000)
#define AD_RES61     (u32)(KEY5_RES1*1000)
#define AD_RES71     (u32)(KEY6_RES1*1000)
#define AD_RES81     (u32)(KEY7_RES1*1000)
#define AD_RES91     (u32)(KEY8_RES1*1000)
#define AD_RESA1     (u32)(KEY9_RES1*1000)
#define AD_RESB1     (u32)(KEYA_RES1*1000)
#define AD_RESC1     (u32)(KEYB_RES1*1000)

#define AD_VDD1      (u32)0x3FF
#define AD_VOL11     (u32)(AD_RES11*100/(AD_RES11+AD_RES_PULL1))*AD_VDD1/100
#define AD_VOL21     (u32)(AD_RES21*100/(AD_RES21+AD_RES_PULL1))*AD_VDD1/100
#define AD_VOL31     (u32)(AD_RES31*100/(AD_RES31+AD_RES_PULL1))*AD_VDD1/100
#define AD_VOL41     (u32)(AD_RES41*100/(AD_RES41+AD_RES_PULL1))*AD_VDD1/100
#define AD_VOL51     (u32)(AD_RES51*100/(AD_RES51+AD_RES_PULL1))*AD_VDD1/100
#define AD_VOL61     (u32)(AD_RES61*100/(AD_RES61+AD_RES_PULL1))*AD_VDD1/100
#define AD_VOL71     (u32)(AD_RES71*100/(AD_RES71+AD_RES_PULL1))*AD_VDD1/100
#define AD_VOL81     (u32)(AD_RES81*100/(AD_RES81+AD_RES_PULL1))*AD_VDD1/100
#define AD_VOL91     (u32)(AD_RES91*100/(AD_RES91+AD_RES_PULL1))*AD_VDD1/100
#define AD_VOLA1     (u32)(AD_RESA1*100/(AD_RESA1+AD_RES_PULL1))*AD_VDD1/100
#define AD_VOLB1     (u32)(AD_RESB1*100/(AD_RESB1+AD_RES_PULL1))*AD_VDD1/100
#define AD_VOLC1     (u32)0x0000

#define AD_GND1      (u32)0x0000

#define AD_NOKEY1    ((((u16)AD_VDD1 - AD_VOL11)/2) + AD_VOL11)
#define ADKEY1_01     ((((u16)AD_VOL11 - AD_VOL21)/2) + AD_VOL21)
#define ADKEY1_11     ((((u16)AD_VOL21 - AD_VOL31)/2) + AD_VOL31)
#define ADKEY1_21     ((((u16)AD_VOL31 - AD_VOL41)/2) + AD_VOL41)
#define ADKEY1_31     ((((u16)AD_VOL41 - AD_VOL51)/2) + AD_VOL51)
#define ADKEY1_41    ((((u16)AD_VOL51 - AD_VOL61)/2) + AD_VOL61)
#define ADKEY1_51     ((((u16)AD_VOL61 - AD_VOL71)/2) + AD_VOL71)
#define ADKEY1_61     ((((u16)AD_VOL71 - AD_VOL81)/2) + AD_VOL81)
#define ADKEY1_71     ((((u16)AD_VOL81 - AD_VOL91)/2) + AD_VOL91)
#define ADKEY1_81     ((((u16)AD_VOL91- AD_VOLA1)/2) + AD_VOLA1)
#define ADKEY1_91     ((((u16)AD_VOLA1- AD_VOLB1)/2) + AD_VOLB1)
#define ADKEY1_A1     ((((u16)AD_VOLB1- AD_VOLC1)/2) + AD_VOLC1)
#endif
#elif defined(ADK_USE_13KEY_MODE)
#define AD_RES_PULL  (u32)(PULL_UP_RESISTANCE*1000)

#define AD_RES1     (u32)(KEY0_NOKEY_RES*1000)
#define AD_RES2     (u32)(KEY1_RES*1000)
#define AD_RES3     (u32)(KEY2_RES*1000)
#define AD_RES4     (u32)(KEY3_RES*1000)
#define AD_RES5     (u32)(KEY4_RES*1000)
#define AD_RES6     (u32)(KEY5_RES*1000)
#define AD_RES7     (u32)(KEY6_RES*1000)
#define AD_RES8     (u32)(KEY7_RES*1000)
#define AD_RES9     (u32)(KEY8_RES*1000)
#define AD_RESA     (u32)(KEY9_RES*1000)
#define AD_RESB     (u32)(KEYA_RES*1000)
#define AD_RESC     (u32)(KEYB_RES*1000)
#define AD_RESD     (u32)(KEYC_RES*1000)

#define AD_VDD      (u32)0x3FF
#define AD_VOL1     (u32)(AD_RES1*100/(AD_RES1+AD_RES_PULL))*AD_VDD/100
#define AD_VOL2     (u32)(AD_RES2*100/(AD_RES2+AD_RES_PULL))*AD_VDD/100
#define AD_VOL3     (u32)(AD_RES3*100/(AD_RES3+AD_RES_PULL))*AD_VDD/100
#define AD_VOL4     (u32)(AD_RES4*100/(AD_RES4+AD_RES_PULL))*AD_VDD/100
#define AD_VOL5     (u32)(AD_RES5*100/(AD_RES5+AD_RES_PULL))*AD_VDD/100
#define AD_VOL6     (u32)(AD_RES6*100/(AD_RES6+AD_RES_PULL))*AD_VDD/100
#define AD_VOL7     (u32)(AD_RES7*100/(AD_RES7+AD_RES_PULL))*AD_VDD/100
#define AD_VOL8     (u32)(AD_RES8*100/(AD_RES8+AD_RES_PULL))*AD_VDD/100
#define AD_VOL9     (u32)(AD_RES9*100/(AD_RES9+AD_RES_PULL))*AD_VDD/100
#define AD_VOLA     (u32)(AD_RESA*100/(AD_RESA+AD_RES_PULL))*AD_VDD/100
#define AD_VOLB     (u32)(AD_RESB*100/(AD_RESB+AD_RES_PULL))*AD_VDD/100
#define AD_VOLC     (u32)(AD_RESC*100/(AD_RESC+AD_RES_PULL))*AD_VDD/100
#define AD_VOLD     (u32)0x0000


#define AD_GND      (u32)0x0000

#define AD_NOKEY    ((((u16)AD_VDD - AD_VOL1)/2) + AD_VOL1)
#define ADKEY1_0     ((((u16)AD_VOL1 - AD_VOL2)/2) + AD_VOL2)
#define ADKEY1_1     ((((u16)AD_VOL2 - AD_VOL3)/2) + AD_VOL3)
#define ADKEY1_2     ((((u16)AD_VOL3 - AD_VOL4)/2) + AD_VOL4)
#define ADKEY1_3     ((((u16)AD_VOL4 - AD_VOL5)/2) + AD_VOL5)
#define ADKEY1_4    ((((u16)AD_VOL5 - AD_VOL6)/2) + AD_VOL6)
#define ADKEY1_5     ((((u16)AD_VOL6 - AD_VOL7)/2) + AD_VOL7)
#define ADKEY1_6     ((((u16)AD_VOL7 - AD_VOL8)/2) + AD_VOL8)
#define ADKEY1_7     ((((u16)AD_VOL8 - AD_VOL9)/2) + AD_VOL9)
#define ADKEY1_8     ((((u16)AD_VOL9- AD_VOLA)/2) + AD_VOLA)
#define ADKEY1_9     ((((u16)AD_VOLA- AD_VOLB)/2) + AD_VOLB)
#define ADKEY1_A     ((((u16)AD_VOLB- AD_VOLC)/2) + AD_VOLC)
#define ADKEY1_B     ((((u16)AD_VOLC- AD_VOLD)/2) + AD_VOLD)

#elif defined(ADK_USE_15KEY_MODE)

#define AD_RES_PULL  (u32)(PULL_UP_RESISTANCE*1000)

#define AD_RES1     (u32)(KEY0_NOKEY_RES*1000)
#define AD_RES2     (u32)(KEY1_RES*1000)
#define AD_RES3     (u32)(KEY2_RES*1000)
#define AD_RES4     (u32)(KEY3_RES*1000)
#define AD_RES5     (u32)(KEY4_RES*1000)
#define AD_RES6     (u32)(KEY5_RES*1000)
#define AD_RES7     (u32)(KEY6_RES*1000)
#define AD_RES8     (u32)(KEY7_RES*1000)
#define AD_RES9     (u32)(KEY8_RES*1000)
#define AD_RESA     (u32)(KEY9_RES*1000)
#define AD_RESB     (u32)(KEYA_RES*1000)
#define AD_RESC     (u32)(KEYB_RES*1000)
#define AD_RESD     (u32)(KEYC_RES*1000)
#define AD_RESE     (u32)(KEYD_RES*1000)
#define AD_RESF     (u32)(KEYE_RES*1000)


#define AD_VDD      (u32)0x3FF
#define AD_VOL1     (u32)(AD_RES1*100/(AD_RES1+AD_RES_PULL))*AD_VDD/100
#define AD_VOL2     (u32)(AD_RES2*100/(AD_RES2+AD_RES_PULL))*AD_VDD/100
#define AD_VOL3     (u32)(AD_RES3*100/(AD_RES3+AD_RES_PULL))*AD_VDD/100
#define AD_VOL4     (u32)(AD_RES4*100/(AD_RES4+AD_RES_PULL))*AD_VDD/100
#define AD_VOL5     (u32)(AD_RES5*100/(AD_RES5+AD_RES_PULL))*AD_VDD/100
#define AD_VOL6     (u32)(AD_RES6*100/(AD_RES6+AD_RES_PULL))*AD_VDD/100
#define AD_VOL7     (u32)(AD_RES7*100/(AD_RES7+AD_RES_PULL))*AD_VDD/100
#define AD_VOL8     (u32)(AD_RES8*100/(AD_RES8+AD_RES_PULL))*AD_VDD/100
#define AD_VOL9     (u32)(AD_RES9*100/(AD_RES9+AD_RES_PULL))*AD_VDD/100
#define AD_VOLA     (u32)(AD_RESA*100/(AD_RESA+AD_RES_PULL))*AD_VDD/100
#define AD_VOLB     (u32)(AD_RESB*100/(AD_RESB+AD_RES_PULL))*AD_VDD/100
#define AD_VOLC     (u32)(AD_RESC*100/(AD_RESC+AD_RES_PULL))*AD_VDD/100
#define AD_VOLD     (u32)(AD_RESD*100/(AD_RESD+AD_RES_PULL))*AD_VDD/100
#define AD_VOLE     (u32)(AD_RESE*100/(AD_RESE+AD_RES_PULL))*AD_VDD/100
#define AD_VOLF     (u32)0x0000

#define AD_GND      (u32)0x0000

#define AD_NOKEY    ((((u16)AD_VDD - AD_VOL1)/2) + AD_VOL1)
#define ADKEY1_0     ((((u16)AD_VOL1 - AD_VOL2)/2) + AD_VOL2)
#define ADKEY1_1     ((((u16)AD_VOL2 - AD_VOL3)/2) + AD_VOL3)
#define ADKEY1_2     ((((u16)AD_VOL3 - AD_VOL4)/2) + AD_VOL4)
#define ADKEY1_3     ((((u16)AD_VOL4 - AD_VOL5)/2) + AD_VOL5)
#define ADKEY1_4    ((((u16)AD_VOL5 - AD_VOL6)/2) + AD_VOL6)
#define ADKEY1_5     ((((u16)AD_VOL6 - AD_VOL7)/2) + AD_VOL7)
#define ADKEY1_6     ((((u16)AD_VOL7 - AD_VOL8)/2) + AD_VOL8)
#define ADKEY1_7     ((((u16)AD_VOL8 - AD_VOL9)/2) + AD_VOL9)
#define ADKEY1_8     ((((u16)AD_VOL9- AD_VOLA)/2) + AD_VOLA)
#define ADKEY1_9     ((((u16)AD_VOLA- AD_VOLB)/2) + AD_VOLB)
#define ADKEY1_A     ((((u16)AD_VOLB- AD_VOLC)/2) + AD_VOLC)
#define ADKEY1_B     ((((u16)AD_VOLC- AD_VOLD)/2) + AD_VOLD)
#define ADKEY1_C     ((((u16)AD_VOLD- AD_VOLE)/2) + AD_VOLE)
#define ADKEY1_D     ((((u16)AD_VOLE- AD_VOLF)/2) + AD_VOLF)

#else

#define ADC10_33   (0x3ffL)
#define ADC10_30   (0x3ffL*30/33)
#define ADC10_27   (0x3ffL*27/33)
#define ADC10_23   (0x3ffL*23/33)
#define ADC10_20   (0x3ffL*20/33)
#define ADC10_17   (0x3ffL*17/33)
#define ADC10_13   (0x3ffL*13/33)
#define ADC10_10   (0x3ffL*10/33)
#define ADC10_07   (0x3ffL*07/33)
#define ADC10_04   (0x3ffL*04/33)
#define ADC10_00   (0)

#define AD_NOKEY        ((ADC10_33 + ADC10_30)/2)
#define ADKEY1_0		((ADC10_30 + ADC10_27)/2)
#define ADKEY1_1		((ADC10_27 + ADC10_23)/2)
#define ADKEY1_2		((ADC10_23 + ADC10_20)/2)
#define ADKEY1_3		((ADC10_20 + ADC10_17)/2)
#define ADKEY1_4		((ADC10_17 + ADC10_13)/2)
#define ADKEY1_5		((ADC10_13 + ADC10_10)/2)
#define ADKEY1_6		((ADC10_10 + ADC10_07)/2)
#define ADKEY1_7		((ADC10_07 + ADC10_04)/2)
#define ADKEY1_8		((ADC10_04 + ADC10_00)/2)
#endif
#ifdef ADK_USE_15KEY_MODE
const u16 ad_key_table[] =
{
    ADKEY1_0,ADKEY1_1,ADKEY1_2,ADKEY1_3,ADKEY1_4,
    ADKEY1_5,ADKEY1_6,ADKEY1_7,ADKEY1_8,ADKEY1_9,
    ADKEY1_A,ADKEY1_B,ADKEY1_C,ADKEY1_D
};
#elif defined(ADK_USE_13KEY_MODE)
const u16 ad_key_table[] =
{
    ADKEY1_0,ADKEY1_1,ADKEY1_2,ADKEY1_3,ADKEY1_4,
    ADKEY1_5,ADKEY1_6,ADKEY1_7,ADKEY1_8,ADKEY1_9,
    ADKEY1_A,ADKEY1_B
};
#elif defined(ADK_USE_12KEY_MODE)
const u16 ad_key_table[] =
{
    ADKEY1_0,ADKEY1_1,ADKEY1_2,ADKEY1_3,ADKEY1_4,
    ADKEY1_5,ADKEY1_6,ADKEY1_7,ADKEY1_8,ADKEY1_9,
    ADKEY1_A,
};
#ifdef TWO_AD_IO_USE_DIFF_RESISTANCE
const u16 ad_key_table1[] =
{
    ADKEY1_01,ADKEY1_11,ADKEY1_21,ADKEY1_31,ADKEY1_41,
    ADKEY1_51,ADKEY1_61,ADKEY1_71,ADKEY1_81,ADKEY1_91,
    ADKEY1_A1
};
#endif
#elif defined(ADK_USE_11KEY_MODE)
const u16 ad_key_table[] =
{
    ADKEY1_0,ADKEY1_1,ADKEY1_2,ADKEY1_3,ADKEY1_4,
    ADKEY1_5,ADKEY1_6,ADKEY1_7,ADKEY1_8,ADKEY1_9
};
#ifdef TWO_AD_IO_USE_DIFF_RESISTANCE
const u16 ad_key_table1[] =
{
    ADKEY1_01,ADKEY1_11,ADKEY1_21,ADKEY1_31,ADKEY1_41,
    ADKEY1_51,ADKEY1_61,ADKEY1_71,ADKEY1_81,ADKEY1_91
};
#endif
#else
const u16 ad_key_table[] =
{
    ADKEY1_0,ADKEY1_1,ADKEY1_2,ADKEY1_3,ADKEY1_4,
    ADKEY1_5,ADKEY1_6,ADKEY1_7,ADKEY1_8
};
#endif

#else

#define ADC10_33   (0x3ffL)
#define ADC10_30   (0x3ffL*30/33)
#define ADC10_27   (0x3ffL*27/33)
#define ADC10_23   (0x3ffL*23/33)
#define ADC10_20   (0x3ffL*20/33)
#define ADC10_17   (0x3ffL*17/33)
#define ADC10_13   (0x3ffL*13/33)
#define ADC10_10   (0x3ffL*10/33)
#define ADC10_07   (0x3ffL*07/33)
#define ADC10_05   (0x3ffL*05/33)
#define ADC10_00   (0)

#define AD_NOKEY        ((ADC10_33 + ADC10_30)/2)
#define ADKEY1_0		((ADC10_30 + ADC10_27)/2)
#define ADKEY1_1		((ADC10_27 + ADC10_23)/2)
#define ADKEY1_2		((ADC10_23 + ADC10_20)/2)
#define ADKEY1_3		((ADC10_20 + ADC10_17)/2)
#define ADKEY1_4		((ADC10_17 + ADC10_13)/2)
#define ADKEY1_5		((ADC10_13 + ADC10_10)/2)
#define ADKEY1_6		((ADC10_10 + ADC10_07)/2)
#define ADKEY1_7		((ADC10_07 + ADC10_05)/2)
#define ADKEY1_8		((ADC10_05 + ADC10_00)/2)

const u16 ad_key_table[] =
{
    ADKEY1_0,ADKEY1_1,ADKEY1_2,ADKEY1_3,ADKEY1_4,
    ADKEY1_5,ADKEY1_6,ADKEY1_7,ADKEY1_8
};

#endif

/*根据系统时钟配置adc采样时钟*/
const u32 sys2adc_clk_info[] =
{
    128000000L,
    96000000L,
    72000000L,
    48000000L,
    24000000L,
    12000000L,
    6000000L,
    1000000L,
};
void set_adc_clk(void)
{
    u32 adc_clk;
    u32 i;
    u8 cnt;

    //ADC 时钟配置
    adc_clk = clock_get_lsb_freq();
    cnt = sizeof(sys2adc_clk_info)/sizeof(sys2adc_clk_info[0]);
    for(i = 0;i< cnt;i++ )
    {
        if( adc_clk > sys2adc_clk_info[i])
        {
            break;
        }
    }

    if(i < cnt)
    {
        i = cnt -i;
    }
    else
    {
        i = cnt -1;
    }

    key_printf("ADC_DIV = %d\n",i);
    ADC_CON &= ~(BIT(2) | BIT(1) | BIT(0));
    ADC_CON |= (i & 0x7L );
}

/*----------------------------------------------------------------------------*/
/**@brief   ad按键初始化
   @param   void
   @param   void
   @return  void
   @note    void ad_key0_init(void)
*/
/*----------------------------------------------------------------------------*/
void ad_key0_init(void)
{
    key_puts("ad key init\n");

#if SYS_LVD_EN
    //LDO初始化
    LDO_CON |= BIT(0);
#endif

#if KEY_AD_EN   //Ã„Â²Ã•Ãœ20150506 
    #ifdef support_adk_user_PA0
        //AD IOÂ¿ÃšÂ³ÃµÃŠÂ¼Â»Â¯
        PORTA_PD &= ~BIT(0);
        #ifdef AD_INTERNAL_PULL_UP
        PORTA_PU |= BIT(0);
        #else
        PORTA_PU &= ~BIT(0);
        #endif
        PORTA_DIR |= BIT(0);
        PORTA_DIE &= ~BIT(0);
    #elif defined(support_adk_user_PA8)
    	PORTA_PD &= ~BIT(8);    	
        #ifdef AD_INTERNAL_PULL_UP
    	PORTA_PU |= BIT(8);
        #else
    	PORTA_PU &= ~BIT(8);
    	#endif
    	PORTA_DIR |= BIT(8);
    	PORTA_DIE &= ~BIT(8);
    #elif defined(adk_io_use_pa0pa8)        
    	PORTA_PD &= ~BIT(8);
    	PORTA_PU &= ~BIT(8);
    	PORTA_DIR |= BIT(8);
    	PORTA_DIE &= ~BIT(8);
    	
        PORTA_PD &= ~BIT(0);
        PORTA_PU &= ~BIT(0);
        PORTA_DIR |= BIT(0);
        PORTA_DIE &= ~BIT(0);   
   #elif defined(adk_io_use_pa0pa11)
	   PORTA_PD &= ~BIT(11);
	   PORTA_PU &= ~BIT(11);
	   PORTA_DIR |= BIT(11);
	   PORTA_DIE &= ~BIT(11);
	   
	   PORTA_PD &= ~BIT(0);
	   PORTA_PU &= ~BIT(0);
	   PORTA_DIR |= BIT(0);
	   PORTA_DIE &= ~BIT(0);   
   #elif defined(AD_KEY_PA14)
        PORTA_PD &= ~BIT(14);
        PORTA_PU &= ~BIT(14);
        PORTA_DIR |= BIT(14);
        PORTA_DIE &= ~BIT(14);
	   
    #else //support_adk_user_PA14
        //AD IOÂ¿ÃšÂ³ÃµÃŠÂ¼Â»Â¯
        PORTA_PD &= ~BIT(14);
        PORTA_PU &= ~BIT(14);
        PORTA_DIR |= BIT(14);
        PORTA_DIE &= ~BIT(14);
    #endif 
#endif 
#ifdef SUPPORT_BAT_DETECT_USE_IO
#ifdef DETECT_EXTERNAL_BAT_USE_PA8
        PORTA_PD &= ~BIT(8);
        PORTA_PU &= ~BIT(8);
        PORTA_DIR |= BIT(8);
        PORTA_DIE &= ~BIT(8);
    #elif defined(DETECT_EXTERNAL_BAT_USE_PA14)
        PORTA_PD &= ~BIT(14);
        PORTA_PU &= ~BIT(14);
        PORTA_DIR |= BIT(14);
        PORTA_DIE &= ~BIT(14);		
    #elif defined(DETECT_EXTERNAL_BAT_USE_PA0)
        PORTA_PD &= ~BIT(0);
        PORTA_PU &= ~BIT(0);
        PORTA_DIR |= BIT(0);
        PORTA_DIE &= ~BIT(0);				
#endif
#endif
#ifdef EQ_ADC_VALUE_DETECT
    #ifdef EQ_DETECT_PIN_USE_PA11
	   	PORTA_PD &= ~BIT(11);
	   	PORTA_PU &= ~BIT(11);
	   	PORTA_DIR |= BIT(11);
	   	PORTA_DIE &= ~BIT(11);
    #elif defined(EQ_DETECT_PIN_USE_PA1)
	   	PORTA_PD &= ~BIT(1);
	   	PORTA_PU &= ~BIT(1);
	   	PORTA_DIR |= BIT(1);
	   	PORTA_DIE &= ~BIT(1);
		
    #elif defined(EQ_DETECT_PIN_USE_PA8)
		PORTA_PD &= ~BIT(8);
		PORTA_PU &= ~BIT(8);
		PORTA_DIR |= BIT(8);
		PORTA_DIE &= ~BIT(8);
   #elif defined(EQ_DETECT_PIN_USE_PA14)
        PORTA_PD |= BIT(14);
        PORTA_PU &= ~BIT(14);
        PORTA_DIR |= BIT(14);
        PORTA_DIE &= ~BIT(14);
   #endif
#endif
#ifdef RGB_ADC_VALUE_DETECT
    #ifdef RGB_DETECT_PIN_USE_PA8
		PORTA_PD &=~ BIT(8);
		PORTA_PU &= ~BIT(8);
		PORTA_DIR |= BIT(8);
		PORTA_DIE &= ~BIT(8);
    #endif
#endif

#ifdef KOK_DETECT_USE_IO_ADC_VALUE
	#ifdef KOK_DETECT_USE_PA11
		PORTA_PD &= ~BIT(11);
		PORTA_PU &= ~BIT(11);
		PORTA_DIR |= BIT(11);
		PORTA_DIE &= ~BIT(11);
	#elif defined KOK_DETECT_USE_PA14
	        PORTA_PD &= ~BIT(14);
	        PORTA_PU &= ~BIT(14);
	        PORTA_DIR |= BIT(14);
	        PORTA_DIE &= ~BIT(14);		
	#endif
#endif

    ADC_CON = 0;
#if 1 //KEY_AD_EN
    set_adc_clk();           //ÉèÖÃÊ±ÖÓ
#endif
    ADC_CON |= (0XF<<12);    //启动延时控制
    ADC_CON |= ad_table[0];  //AD口选择
    ADC_CON |= BIT(3);       //ADC模拟模块使能
    ADC_CON |= BIT(4);       //ADC控制器使能
    ADC_CON |= BIT(6);       //启动ADC
}

/*----------------------------------------------------------------------------*/
/**@brief   ad通道采样函数
   @param   void
   @param   void
   @return  void
   @note    void adc_scan(void)
*/
/*----------------------------------------------------------------------------*/
void adc_scan(void)
{
    static u8 channel;

	
    while(!(BIT(7) & ADC_CON));
    adc_value[channel++] = ADC_RES;

    if (channel == MAX_AD_CHANNEL)
        channel = 0;
	
#ifdef SUPPORT_USE_ADKEY_AS_AD_AND_LED
#ifdef support_adk_user_PA14
    if(channel==0)
    {
	g_ad_led_flag=1;

	PORTA_PD &= ~BIT(14);
	PORTA_PU &= ~BIT(14);
	PORTA_DIR |= BIT(14);
	PORTA_DIE &= ~BIT(14);   
	
    }		
    else
    {    
        g_ad_led_flag=0;

        PORTA_PD |= BIT(14);
        PORTA_DIR &=~ BIT(14);
        PORTA_PU &=~BIT(14);		
        PORTA_DIE |= BIT(14);		
		
    }
#else
    if(channel==0)
    {
	g_ad_led_flag=1;

	PORTA_PD &= ~BIT(0);
	PORTA_PU &= ~BIT(0);
	PORTA_DIR |= BIT(0);
	PORTA_DIE &= ~BIT(0);   
	
    }		
    else
    {    
        g_ad_led_flag=0;

        PORTA_PD |= BIT(0);
        PORTA_DIR &=~ BIT(0);
        PORTA_PU &=~BIT(0);		
        PORTA_DIE |= BIT(0);		
		
    }
#endif
#endif
	
    ADC_CON &= ~0x0f00;            //AD口clear
    ADC_CON |= ad_table[channel];  //AD口选择
    ADC_CON |= BIT(6);             //启动ADC
}

/*----------------------------------------------------------------------------*/
/**@brief   获取ad按键值
   @param   void
   @param   void
   @return  key_number
   @note    tu8 get_adkey_value(void)
*/
/*----------------------------------------------------------------------------*/
tu8 get_adkey_value(void)
{
#if KEY_AD_EN
		tu8 key_number;
		u32 key_value;
		
	 #ifdef DURING_FM_EXITING_TASK_NOT_RESPOND_KEY_MSG
	 	  if(bExitFMStateCnt)
		  {
		 	  return NO_KEY;
	 	  }
	 #endif
		key_value = adc_value[AD_CH_KEY];

		
	 #ifdef support_line_chack_user_ad
	 	if (key_value > VOL_AD_NOKEY)
	 		{	  
	 			return NO_KEY;
	 		}
	 	else if (key_value > VOL_AD_AUX_IN)
			{	  
	 			return NO_KEY;
	 		}
	 #else
	 	if (key_value > AD_NOKEY)
	 		{	  
	 			 #ifdef SUPPORT_PANEL_KEY_USE_TWO_AD_IO
	 			 	key_value=adc_value[AD_CH_KEY1];
	 			 	if(key_value>AD_NOKEY)		
	 			 #endif
	 			return NO_KEY;
	 		}
	 #endif

	 #ifdef TWO_AD_IO_USE_DIFF_RESISTANCE		
		  if(adc_value[AD_CH_KEY]>AD_NOKEY)
		  	{
			  for (key_number = 0; key_number < sizeof (ad_key_table1) / sizeof (ad_key_table1[0]); key_number++)
			  {    
				  if (key_value > ad_key_table1[key_number])
					  break;
			  }
		  }
		  else
	 #endif
	 
		for (key_number = 0; key_number < sizeof (ad_key_table) / sizeof (ad_key_table[0]); key_number++)
		{
			if (key_value > ad_key_table[key_number])
				break;
		}
//		printf("adkey_value:0x%03x	 key_num:0x%x\n",key_value,key_number);
//		printf("AD_NOKEY:0x%03x	 ADKEY1_0:0x%03x\n",AD_NOKEY,ADKEY1_0);
	    #ifdef SUPPORT_PANEL_KEY_USE_TWO_AD_IO
			if(adc_value[AD_CH_KEY]>AD_NOKEY)
	 	    #ifdef ADK_USE_11KEY_MODE
	 			key_number+=11;
	 	    #elif defined(ADK_USE_12KEY_MODE)
	 			key_number+=12;
	 	    #elif defined(ADK_USE_13KEY_MODE)
	 			key_number+=13;
	 	    #endif
	    #endif
		return key_number;
#else 
			return NO_KEY;
#endif     
}

#else

u16 adc_value[3];
const u32 ad_table[] =
{
    AD_KEY_PA8,
    AD_KEY_LDOIN,
    AD_KEY_LDOREF,
};

#define ADC10_33   (0x3ffL)
#define ADC10_30   (0x3ffL*30/33)
#define ADC10_27   (0x3ffL*27/33)
#define ADC10_23   (0x3ffL*23/33)
#define ADC10_20   (0x3ffL*20/33)
#define ADC10_17   (0x3ffL*17/33)
#define ADC10_13   (0x3ffL*13/33)
#define ADC10_10   (0x3ffL*10/33)
#define ADC10_07   (0x3ffL*07/33)
#define ADC10_04   (0x3ffL*04/33)
#define ADC10_00   (0)

#define AD_NOKEY        ((ADC10_33 + ADC10_20)/2)
//#define AD_NOKEY        ((ADC10_10 + ADC10_00)/2)
#define ADKEY1_0		((ADC10_20 + ADC10_10)/2)
#define ADKEY1_1		((ADC10_10 + ADC10_00)/2)
#define ADKEY1_2		((ADC10_33 + ADC10_20)/2)
#define ADKEY1_3		((ADC10_33 + ADC10_20)/2)
#define ADKEY1_4		((ADC10_33 + ADC10_20)/2)
#define ADKEY1_5		((ADC10_33 + ADC10_20)/2)
#define ADKEY1_6		((ADC10_33 + ADC10_20)/2)
#define ADKEY1_7		((ADC10_33 + ADC10_20)/2)
#define ADKEY1_8		((ADC10_33 + ADC10_20)/2)

const u16 ad_key_table[] =
{
    ADKEY1_0,ADKEY1_1/*,ADKEY1_2,ADKEY1_3,ADKEY1_4,
    ADKEY1_5,ADKEY1_6,ADKEY1_7,ADKEY1_8*/
};

/*根据系统时钟配置adc采样时钟*/
const u32 sys2adc_clk_info[] =
{
    128000000L,
    96000000L,
    72000000L,
    48000000L,
    24000000L,
    12000000L,
    6000000L,
    1000000L,
};
void set_adc_clk(void)
{
    u32 adc_clk;
    u32 i;
    u8 cnt;

    //ADC 时钟配置
    adc_clk = clock_get_lsb_freq();
    cnt = sizeof(sys2adc_clk_info)/sizeof(sys2adc_clk_info[0]);
    for(i = 0;i< cnt;i++ )
    {
        if( adc_clk > sys2adc_clk_info[i])
        {
            break;
        }
    }

    if(i < cnt)
    {
        i = cnt -i;
    }
    else
    {
        i = cnt -1;
    }

    key_printf("ADC_DIV = %d\n",i);
    ADC_CON &= ~(BIT(2) | BIT(1) | BIT(0));
    ADC_CON |= (i & 0x7L );
}
/*----------------------------------------------------------------------------*/
/**@brief   ad按键初始化
   @param   void
   @param   void
   @return  void
   @note    void ad_key0_init(void)
*/
/*----------------------------------------------------------------------------*/
void ad_key0_init(void)
{
    key_puts("ad key init\n");
    u32 i;

#if SYS_LVD_EN
    //LDO初始化
    LDO_CON |= BIT(0);
#endif

    //AD IO口初始化
    PORTA_PD &= ~BIT(8);
    PORTA_PU |= BIT(8);
    PORTA_DIR |= BIT(8);
    PORTA_DIE &= ~BIT(8);

    ADC_CON = 0;
#if KEY_AD_EN
    set_adc_clk();           //设置时钟
#endif
    ADC_CON |= (0XF<<12);    //启动延时控制
    ADC_CON |= ad_table[0];  //AD口选择
    ADC_CON |= BIT(3);       //ADC模拟模块使能
    ADC_CON |= BIT(4);       //ADC控制器使能
    ADC_CON |= BIT(6);       //启动ADC
}

/*----------------------------------------------------------------------------*/
/**@brief   ad通道采样函数
   @param   void
   @param   void
   @return  void
   @note    void adc_scan(void)
*/
/*----------------------------------------------------------------------------*/
void adc_scan(void)
{
    static u8 channel;
    while(!(BIT(7) & ADC_CON));
    adc_value[channel++] = ADC_RES;

    if (channel == MAX_AD_CHANNEL)
        channel = 0;
    ADC_CON &= ~0x0f00;            //AD口clear
    ADC_CON |= ad_table[channel];  //AD口选择
    ADC_CON |= BIT(6);             //启动ADC
}

/*----------------------------------------------------------------------------*/
/**@brief   获取ad按键值
   @param   void
   @param   void
   @return  key_number
   @note    tu8 get_adkey_value(void)
*/
/*----------------------------------------------------------------------------*/
tu8 get_adkey_value(void)
{
    tu8 key_number;
    u32 key_value;

    key_value = adc_value[AD_CH_KEY];
    if (key_value > AD_NOKEY)
        return NO_KEY;

    for (key_number = 0; key_number < sizeof (ad_key_table) / sizeof (ad_key_table[0]); key_number++)
    {
        if (key_value > ad_key_table[key_number])
            break;
    }
    key_printf("adkey_value:0x%03x   key_num:0x%x\n",key_value*33/0x3ff,key_number);
    return key_number;
}
#endif
