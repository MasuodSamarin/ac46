#include "lcd_128x64_drv.h"
#include "config.h"
#include "lcd_cfg.h"
#include "lcd_drv.h"
/*
	*lcd 初始化命令表
*/
const u8 lcd_init_table[] =
{
	LCD_SOFT_RST,
	LCD_BIAS_SET | 0x00,   //lcd bias setting
	LCD_ADC_SEL,           //0XA0 ADC
	LCD_COMMON_MODE,       //0xc8 common output mode
	(LCD_V0_RATIO | 0x03),   //Resistor Ratio
	LCD_POWER_MODE,        //0x2f lcd power control
	LCD_START_LINE | 0,    //0x40
	LCD_ON,
	LCD_ELE_VOLUME,        //0X81 /electronic Volume
	0x22, //0x32//
	LCD_DISP_BW,
};   ///<lcd 初始化命令表


/*----------------------------------------------------------------------------*/
/**@brief    设置显示的起始坐标
   @param     x:列坐标
   @param     y:行坐标
   @return
   @note      void lcd_set(u8 y,u8 x)
*/
/*----------------------------------------------------------------------------*/
void lcd_128x64_set(u8 page,u8 column)
{
    lcd_sendcmd(LCD_COLUMN_HIGH | column>>4);
    lcd_sendcmd(LCD_COLUMN_LOW | (0x0f & column));
    lcd_sendcmd(LCD_PAGE_ADDR | page);
}


/*----------------------------------------------------------------------------*/
/**@brief    设置对比度,lcd对比度范围可以是0-63
   @param    c:对比度的值，lcd对比度范围可以是0~60
   @return
   @note     void lcd_set_contrast(u8 c)
*/
/*----------------------------------------------------------------------------*/
void lcd_set_contrast(u8 c)
{
    if(c > 60)    //c < 0 ||
	{
		c = 34;
	}
    lcd_sendcmd(0x81);
    lcd_sendcmd(c);//lcd对比度范围可以是27-43
}


/*----------------------------------------------------------------------------*/
/**@brief    LCD 硬件初始化
   @param    无
   @return
   @note     void lcd_hardware_init(void)
*/
/*----------------------------------------------------------------------------*/
void lcd_hardware_init(void)
{
    tu8 i;
    u8 flag;

    lcd_spi_init();///LCD SPI init
    printf("\nlcd_hardware_init");

    for(i = 0; i < sizeof(lcd_init_table); i++)
	{
		lcd_sendcmd(lcd_init_table[i]);
		delay(10);
	}


    lcd_set_contrast(48);

    lcd_clear();
    puts("\nLCD init OK");
}

//void my_putchar1(u8 *buf,u16 width,u16 height,u16 x,u16 y)
//{
//     u8 c;
//     u16 iRow,iCol;
//	 s8 h;
//
////    puts("\nmyputchar1");
//     for(iRow = 0;iRow < (height+7)/8;iRow++)
//     {
//          for(iCol = 0; iCol<width;iCol++)
//          {
//               u8 pixel = buf[iRow*width+iCol];
//               if(iRow == ((height+7)/8-1))
//               {
//                    if(height%8 != 0)
//                         c = height%8;
//                    else
//                         c = 8;
//               }
//               else
//                    c = 8;
//
//               for(h=c-1;h>=0;h--)
//               {
//					u16 xx,yy;
//					xx = x+iCol;
//					yy = y+iRow*8+h;
//					if(pixel & BIT(h))
//					{
////						lcd_buf[yy/8][xx] |= BIT(yy%8);
//                        *(disp_buf + (yy/8)*SCR_WIDTH + xx) |= BIT(yy%8);
//					}
//               }
//          }
//     }
//}

//void spi_flash_read(u8 *buf,u32 addr,u32 len)
//{
//    sd_phyread(FALSE,buf,addr,len);
//}

