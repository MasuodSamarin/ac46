#include "config.h"
#include "lcd_drv_api.h"
#include "lcd_spi.h"
#include "dc_showres.h"
#include "lcd_drv_interface.h"
#include "ui_con.h"
#include "menu.h"
#include "ui_api.h"

#if LCD_128X64_EN

u8 disp_buf[8*128];             ///<LCD 显示缓存
LCD_INFO *lcd_parm;
extern u8 g_language_mode;


/*----------------------------------------------------------------------------*/
/**@brief   lcd update buf
   @param   void
   @return  void
   @note    void draw_lcd_buf(void)
*/
/*----------------------------------------------------------------------------*/
void draw_lcd_buf(void)
{
     lcd_draw(0 ,LCDPAGE,disp_buf);
}

/*----------------------------------------------------------------------------*/
/**@brief   lcd spi初始化
   @param   void
   @return  void
   @note    void lcd_spi_init(void)
*/
/*----------------------------------------------------------------------------*/
void lcd_clear(void)
{
    memset(disp_buf, 0x00, LCDPAGE*LCDCOLUMN);
//    flush_dcache(disp_buf, LCDPAGE*LCDCOLUMN);//liwenhong
//    lcd_draw(0 ,LCDPAGE,disp_buf);
}


/*----------------------------------------------------------------------------*/
/**@brief   LCD显示初始化,包括：硬件初始化，字体初始化，控件初始化
   @param   void
   @return  void
   @note    void lcd_init(void)
*/
/*----------------------------------------------------------------------------*/
void lcd_init(void)
{
    puts("---lcd_init---!\n");
    memset(disp_buf, 0x0,LCDPAGE*LCDCOLUMN);
    lcd_parm = (LCD_INFO*)&lcd_info;

    ///硬件初始化
    lcd_hardware_init();
//    LCD_BL_ON();

    ///非UI显示接口初始化
    if(!dc_init())
    {
        ui_puts("\ndc init fail   ---!\n");
        return FALSE;
    }
    else
    {
        ui_puts("dc init succ !\n");
    }

    dc_set_screen_scale(1,1);//对屏幕显示进行同步放大

    ///字库接口初始化
    g_language_mode = Chinese_Simplified;//English;//Chinese_Simplified;
    if(!font_init(g_language_mode))
    {
        ui_puts("\nfont init fail  ---! \n");
		return FALSE;
    }
    else
    {
        ui_puts("font init succ!\n");
    }

    ///UI显示接口初始化
    if(!ui_init(SCR_WIDTH,SCR_HEIGHT))
    {
        ui_puts("\nui init fail  ---!\n");
        return FALSE;
    }
    else
    {
        ui_puts("ui init succ!\n");
    }

    lcd_clear();
}

#endif/*LCD_128x64_EN*/

