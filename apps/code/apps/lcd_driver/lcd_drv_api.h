#ifndef __LCD_DRV_API_H__
#define __LCD_DRV_API_H__

#include "config.h"

tu16 lcd_get_width(void);
tu16 lcd_get_height(void);
void lcd_clear_area(u8 start_page,u8 end_page);
void lcd_clear_area_with_draw(u8 start_page,u8 end_page);
void lcd_clear_area_rect(u8 start_page,u8 end_page,u8 x0,u8 x1);
tbool lcd_TurnPixelReverse_Page(u8 startpage, u8 pagelen);
tbool lcd_TurnPixelReverse_Rect(u8 left, u8 top, u8 right, u8 bottom);


#endif/*__LCD_DRV_API_H__*/

