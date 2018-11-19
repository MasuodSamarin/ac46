#ifndef  __LCD_DRV_H__
#define  __LCD_DRV_H__

#include "config.h"

extern u8 disp_buf[];


void lcd_sendcmd(u8 cmd);
tu8  lcd_write_dma(u8 * pbuf);
void lcd_draw(u8 start_page, u8 page_len,u8 * pbuf);
void lcd_spi_init(void);

#endif/*__LCD_DRV_H__*/
