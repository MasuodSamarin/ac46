#ifndef __LCD_DRV_API_H__
#define __LCD_DRV_API_H__

#include "config.h"

///************************************************************/
///****************配置屏幕的大小
///****************说明：点阵屏是一个点对应一个bit
///************************************************************/
#define  LCDPAGE            8
#define  LCDCOLUMN          128

#define SCR_WIDTH           LCDCOLUMN
#define SCR_HEIGHT          (LCDPAGE*8)

//SPI1接口选择
#define LCD_DATA_OUT()      do{PORTB_DIR &= ~BIT(7); PORTB_OUT |= BIT(7);}while(0)
#define	LCD_CLK_OUT()	    do{PORTB_DIR &= ~BIT(6); PORTB_OUT |= BIT(6);}while(0)

#define	LCD_A0_OUT()	    do{PORTA_DIR &= ~BIT(15);}while(0)
#define	LCD_A0_L()	        do{PORTA_OUT &= ~BIT(15);}while(0)
#define	LCD_A0_H()	        do{PORTA_OUT |= BIT(15);}while(0)

#define LCD_RES_OUT()	    do{PORTA_DIR &= ~BIT(14);}while(0)
#define LCD_RES_L()	        do{PORTA_OUT &= ~BIT(14);}while(0)
#define LCD_RES_H()	        do{PORTA_OUT |= BIT(14);}while(0)

#define LCD_CS_OUT()	    do{PORTA_DIR &= ~BIT(13);}while(0)
#define LCD_CS_L()	        do{PORTA_OUT &= ~BIT(13);}while(0)
#define LCD_CS_H()	        do{PORTA_OUT |= BIT(13);}while(0)


#define LCD_BL_ON()         //do{PORTB_DIR &= ~BIT(2); PORTB_OUT |= BIT(2);}while(0)
#define LCD_PORT_OUT()      do{LCD_DATA_OUT();LCD_CLK_OUT();LCD_A0_OUT();LCD_RES_OUT();LCD_CS_OUT();}while(0)
#define LCD_PORT_OUT_H()    do{LCD_DATA_OUT();LCD_CLK_OUT();LCD_A0_H();  LCD_RES_H();	LCD_CS_H();}while(0)

//全局变量声明
extern u8 disp_buf[];

//函数声明
void draw_lcd_buf(void);
void lcd_clear(void);
void lcd_init(void);

#endif/*__LCD_DRV_API_H__*/
