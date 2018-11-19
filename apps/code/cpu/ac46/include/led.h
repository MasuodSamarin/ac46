#ifndef _LED_H_
#define _LED_H_
#include "config.h"

#ifdef NEW_LED_SHOW_METHOD
//#include "config_user_gpio.h"
#ifdef GW_827BT
extern bool bIfRunTimer;
extern u8 bRGBMode;
#endif

extern u8 show_led_num[LED_NUMS];
extern u8 show_led_mode[LED_NUMS];
extern u8 show_led_time[LED_NUMS];

enum 
{
led_mode_off=0,
led_mode_on,
led_mode_flash_fast,
led_mode_flash_slow,
led_mode_flash_fast_one_period,
led_mode_on_one_period
}led_show_mode;

void led_scan(void);
void setLedLight(u8 ledId,u8 showMode,u8 falshTime);
void all_led_control_together(u8 mode);
#ifdef EQ_ADC_VALUE_DETECT
void AUTO_DETECT_VOICE_AND_PRODUCE_PWM_VALUE(void);
#endif

#if defined SUPPORT_ZY_4LED_RGB||defined SUPPORT_RGB_BREATH_LAMP	
void pwm_led_rgb_scan(void);
void freq_det_main(void);
void led_rbg_main(u8 mode,u8 rgbmode);
void pwm_control_led_dim(u8 led_pos,u16 white_timer,bool onoff);

#endif
#endif
#endif/*_LED_H_*/

