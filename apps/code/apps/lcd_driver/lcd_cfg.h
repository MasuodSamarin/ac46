#ifndef __LCD_CFG_H__
#define __LCD_CFG_H__

#include "config.h"



//#define LCD_192x64_EN
#define LCD_128x64_EN


///************************************************************/
///****************配置屏幕的大小
///****************说明：点阵屏是一个点对应一个bit
///************************************************************/
#if defined(LCD_192x64_EN)
#define  LCDPAGE            8
#define  LCDCOLUMN          192
#elif defined(LCD_128x64_EN)
#define  LCDPAGE            8
#define  LCDCOLUMN          128


#endif

#define SCR_WIDTH           LCDCOLUMN
#define SCR_HEIGHT          (LCDPAGE*8)

//SPI1接口选择
#if SPI1_OUT == 0
#define LCD_DATA_OUT()      do{PORTB_DIR &= ~BIT(7); PORTB_OUT |= BIT(7);}while(0)
#define	LCD_CLK_OUT()	    do{PORTB_DIR &= ~BIT(6); PORTB_OUT |= BIT(6);}while(0)
#else
#define LCD_DATA_OUT()      do{PORTC_DIR &= ~BIT(2); PORTC_OUT |= BIT(2);}while(0)
#define	LCD_CLK_OUT()	    do{PORTC_DIR &= ~BIT(1); PORTC_OUT |= BIT(1);}while(0)
#endif

#define	LCD_A0_OUT()	    do{PORTC_DIR &= ~BIT(2); }while(0)
#define	LCD_A0_L()	        do{PORTC_OUT &= ~BIT(2);}while(0)
#define	LCD_A0_H()	        do{PORTC_OUT |= BIT(2);}while(0)

#define LCD_RES_OUT()	    do{PORTC_DIR &= ~BIT(1); }while(0)
#define LCD_RES_L()	        do{PORTC_OUT &= ~BIT(1);}while(0)
#define LCD_RES_H()	        do{ PORTC_OUT |= BIT(1);}while(0)

#define LCD_CS_OUT()	    do{PORTC_DIR &= ~BIT(0); }while(0)
#define LCD_CS_L()	        do{PORTC_OUT &= ~BIT(0);}while(0)
#define LCD_CS_H()	        do{ PORTC_OUT |= BIT(0);}while(0)



#define LCD_BL_ON()         //do{PORTB_DIR &= ~BIT(2); PORTB_OUT |= BIT(2);}while(0)

#define LCD_PORT_OUT()      do{LCD_DATA_OUT();LCD_CLK_OUT();LCD_A0_OUT();LCD_RES_OUT();LCD_CS_OUT();}while(0)
#define LCD_PORT_OUT_H()    do{LCD_DATA_OUT();LCD_CLK_OUT();LCD_A0_H();  LCD_RES_H();	LCD_CS_H();}while(0)





#endif/*__LCD_CFG_H__*/


