#ifndef __LINEIN_KEY_H__
#define __LINEIN_KEY_H__

#include "config.h"

#if AD_KEY_MAX
extern const u8 linein_ad_table[4][AD_KEY_MAX];
#else
extern const u8 linein_ad_table[4][10];
#endif
extern const u8 linein_io_table[4][10];
#ifdef ir_max_num
extern const u8 linein_ir_table[4][ir_max_num];
#else 
extern const u8 linein_ir_table[4][21];
#endif 
#if KEY_TCH_EN
extern const u8 linein_touch_table[4][10];
#endif
#ifdef SUPPORT_TM1628_KEY_READ
  #if LED_KEY_MAX
 extern const u8 linein_led_table[4][LED_KEY_MAX];
  #else
 extern const u8 linein_led_table[4][10];
  #endif
#endif

#endif
