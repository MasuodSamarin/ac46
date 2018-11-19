#ifndef _LCD_DISP_H_
#define _LCD_DISP_H_

#include "config.h"

void lcd_disp_welcome(void);
void lcd_disp_bt(void);
void lcd_disp_text(u8 str_num);
void lcd_disp_vol(void);
void lcd_disp_string_menu(u8 menu);
void lcd_fm_main(void);
void lcd_fm_channel(void);

void lcd_null_dis(void);

#endif/*_LCD_DISP_H_*/
