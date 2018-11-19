#ifndef __KEY_DRV_AD_H__
#define __KEY_DRV_AD_H__

#define ADC_KEY_NUMBER 10

#if KEY_AD_EN
#define  USE_AD_KEY0   1
#define  USE_AD_KEY1   0
#endif

#ifdef support_line_chack_user_ad  //330K

#define VOL_AD_NOKEY   (0x3ffL*32/33)   
#define VOL_AD_AUX_IN   (0x3ffL*29/33)

#endif
//AD channel define
#define AD_KEY_PA0    (0<<8)
#define AD_KEY_PA1    (1<<8)
#define AD_KEY_PA2    (2<<8)
#define AD_KEY_PA3    (3<<8)
#define AD_KEY_PA5    (4<<8)
#define AD_KEY_PA8    (5<<8)
#define AD_KEY_PA11   (6<<8)
#define AD_KEY_PA14   (7<<8)
#define AD_KEY_PB1    (8<<8)
#define AD_KEY_PB2    (9<<8)
#define AD_KEY_PB3    (0xA<<8)
#define AD_KEY_PB5    (0xB<<8)
#define AD_KEY_PR0    (0xC<<8)
#define AD_KEY_PR1    (0xD<<8)
#define AD_KEY_LDOIN  (0xE<<8)
#define AD_KEY_LDOREF (0xF<<8)

/*ADĶØµĄ¶ØŅå*/
enum
{

#if KEY_AD_EN   //Ã„Â²Ã•Ãœ20150506 
		AD_CH_KEY = 0,
    #ifdef SUPPORT_PANEL_KEY_USE_TWO_AD_IO
		AD_CH_KEY1,
    #endif
#ifdef SUPPORT_BAT_DETECT_USE_IO
		AD_CH_BAT,
#endif
#ifdef EQ_ADC_VALUE_DETECT
		AD_CH_EQ,
#endif
#ifdef RGB_ADC_VALUE_DETECT
		AD_CH_RGB,
#endif

#ifdef KOK_DETECT_USE_IO_ADC_VALUE
		AD_CH_KOK,
#endif
		AD_CH_LDOIN,
#else 
		AD_CH_LDOIN =0,
#endif    
    AD_CH_LDOREF,
    MAX_AD_CHANNEL,
    
};



#if USE_AD_KEY0
//extern u16 adc_value[3];
extern u16 adc_value[MAX_AD_CHANNEL];
extern void ad_key0_init(void);
extern tu8 get_adkey_value();
extern  u8  ad_key0_get_value(void);
extern  u8  ad_key0_pressed_to_msg(u8 key_style, u8 key_num);
#endif/*USE_AD_KEY0*/


#if USE_AD_KEY1
extern void ad_key1_init(void);
extern  u8  ad_key1_get_value(void);
extern  u8  ad_key1_pressed_to_msg(u8 key_style, u8 key_num);
#endif /*USE_AD_KEY1*/

void adc_scan(void);

#endif/*__KEY_DRV_AD_H__*/
