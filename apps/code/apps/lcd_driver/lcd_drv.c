#include "os_api.h"
#include "lcd_drv.h"
#include "lcd_cfg.h"
#include "spi1.h"
#include "menu.h"
#include "lcd_128x64_drv.h"
//#include "ui_time_count.h"
#include "dc_showres.h"
#include "lcd_drv_api.h"
//#include "ui.h"
#include "ui_con.h"
//#include "irtc.h"
u8 disp_buf[8*128];//LCD 显示缓存
volatile bool lcd_busy;     ///<LCD硬件忙标记
u8 lcd_currPage;                ///<当前PAGE
u8 lcd_updata_page_len;         ///跟新的PAGE数目
LCD_INFO *lcd_parm;
extern u8 g_language_mode;
//extern OS_TCB  task_ui_tcb  ;             ///<显示线程句柄liwenhong

/*
    LCD 接口函数
*/
const UI_LCD_IO ui_lcd_io =
{
    .lcd_clear_area_callback            = lcd_clear_area,
    .lcd_clear_area_with_draw_callback  = lcd_clear_area_with_draw,
    .lcd_clear_area_rect_callback       = lcd_clear_area_rect,
    .lcd_TurnPixelReverse_Page_callback = lcd_TurnPixelReverse_Page,
    .lcd_TurnPixelReverse_Rect_callback = lcd_TurnPixelReverse_Rect,
};
/*
    LCD控件接口
*/
const LCD_INFO lcd_info =
{
    .ui_lcd_callback = (UI_LCD_IO *)&ui_lcd_io,
    .lcd_height = SCR_HEIGHT,
    .lcd_width = SCR_WIDTH,
    .lcd_buff = disp_buf,

};

void dc_clear_screen_area(u32 x, u32 y, u32 width, u32 height)
{
    u32 i;
    u32 h, w;
    if(x>=SCR_WIDTH || y>=SCR_HEIGHT){
        return;
    }

    h = ((y+height)>SCR_HEIGHT) ? (SCR_HEIGHT-y) : height;
    w = ((x+width)>SCR_WIDTH) ? (SCR_WIDTH-x) : width;

    for(i=0; i<h; i++){
        memset((u8*)&disp_buf[(y+i)*128+x], 0x00, w);
    }

    //lcd_draw_screen(0, dc_screen_height, dc_displaybuf);
}


void lcd_set(u8 page,u8 column)
{
//#ifdef LCD_192x64_EN
//    lcd_192x64_set(page, column);
//#endif

//#ifdef LCD_128x64_EN
    lcd_128x64_set(page, column);
//#endif
}

void draw_lcd_buf(void)
{
     lcd_draw(0 ,LCDPAGE,disp_buf);
}


void lcd_clear(void)
{
    memset(disp_buf, 0x00, LCDPAGE*LCDCOLUMN);
//    flush_dcache(disp_buf, LCDPAGE*LCDCOLUMN);//liwenhong
    lcd_draw(0 ,LCDPAGE,disp_buf);
}


void lcd_sendcmd(u8 cmd)
{
    SPI1_init(0, 0x10);
    LCD_A0_L();
    delay(10);
    LCD_CS_L();
    delay(10);
    SPI1_WriteByte(cmd);
    LCD_CS_H();
}


/*----------------------------------------------------------------------------*/
/**@brief   物理DMA到LCD
   @param   无
   @return  0：要DMA的页完毕 1：要DMA的页还没完
   @note     tu8 lcd_write_dma(void)
*/
/*----------------------------------------------------------------------------*/
tu8 lcd_write_dma(u8 * pbuf)
{
    tu8 i;
    SPI1_init(0, 0x10);
    LCD_CS_H();
    if (lcd_updata_page_len == 0)
    {

        lcd_busy = 0;
        return 0;
    }
    lcd_busy = 1;
    lcd_set(lcd_currPage, 0);
    LCD_A0_H();
    delay(10);
    LCD_CS_L();

    SPI1_DmaWrite(pbuf + lcd_currPage*LCDCOLUMN, LCDCOLUMN);
//    for(i = 0;i<LCDCOLUMN;i++)
//        SPI1_WriteByte(pbuf[lcd_currPage*LCDCOLUMN+i]);

    lcd_currPage++;
    lcd_updata_page_len--;

    return 1 ;
}



/*----------------------------------------------------------------------------*/
/**@brief   更新显存的内容到LCD
   @param   start_page ：更新开始的起始Page
   @param   page_len ：更新的Page数
   @return
   @note    void draw_lcd(u8 start_page, u8 page_len)
*/
/*----------------------------------------------------------------------------*/
void lcd_draw(u8 start_page, u8 page_len,u8 * pbuf)
{
    //flush_dcache(pbuf, LCDPAGE*LCDCOLUMN);//liwenhong
    while (lcd_busy);
    lcd_currPage = start_page;
    lcd_updata_page_len = page_len;
    //printf_buf(pbuf,128*8);
    while(lcd_write_dma(pbuf));
//    printf("over");
}


/*----------------------------------------------------------------------------*/
/**@brief   lcd spi初始化
   @param   void
   @return  void
   @note    void lcd_spi_init(void)
*/
/*----------------------------------------------------------------------------*/
void lcd_spi_init(void)
{

    printf("\nlcd_spi_init");
//    printf("apb clk: %d \n",get_apb_clk());

    SPI1_init(0, 0x10);//两线模式，波特率系数为16

    LCD_PORT_OUT();
    LCD_PORT_OUT_H();

    SPI1_init(0, 0x10);//两线模式，波特率系数为16

    printf("\nlcd_spi_init end");
    LCD_RES_L();
    delay(10);
    LCD_RES_H();
    delay(10);
}

//extern void test_ui_menu(void);


//typedef struct _UI_LCD_IO
//{
//    void  (*lcd_clear_area_callback)(u8 start_page, u8 end_page);
//    void  (*lcd_clear_area_with_draw_callback)(u8 start_page, u8 end_page);
//    void  (*lcd_clear_area_rect_callback)(u8 start_page, u8 end_page, u8 x0, u8 x1);
//    tbool (*lcd_TurnPixelReverse_Page_callback)(u8 startpage, u8 pagelen);
//    tbool (*lcd_TurnPixelReverse_Rect_callback)(u8 left, u8 top, u8 right, u8 bottom);
//}UI_LCD_IO;
//
//
//typedef struct _LCD_INFO
//{
//    UI_LCD_IO *ui_lcd_callback;
//    u16 lcd_width;  ///lcd屏的宽度
//    u16 lcd_height; ///lcd屏的高度
//    u8 *lcd_buff;    ///显示buff
//}LCD_INFO;
//extern LCD_INFO lcd_parm;


/*----------------------------------------------------------------------------*/
/**@brief   LCD显示初始化,包括：硬件初始化，字体初始化，控件初始化
   @param   void
   @return  void
   @note    void lcd_init(void)
*/
/*----------------------------------------------------------------------------*/

void lcd_init(void)
{
    memset(disp_buf, 0x0,LCDPAGE*LCDCOLUMN);
    lcd_parm = (LCD_INFO*)&lcd_info;


    ///硬件初始化
    lcd_hardware_init();
//    LCD_BL_ON();

    ///非UI显示接口初始化
    if(!dc_init())
    {
        printf("\ndc init fail   ---!");
        return FALSE;
    }
    else
    {
        printf("dc init succ !\n");
    }

    dc_set_screen_scale(1,1);//对屏幕显示进行同步放大
    ///字库接口初始化
    g_language_mode = Chinese_Simplified;//English;//Chinese_Simplified;
    if(!font_init(g_language_mode))
    {
        printf("\nfont init fail  ! ");
		return FALSE;
    }
    else
    {
        printf("\n font init succ!");
    }


    ///UI显示接口初始化
    if(!ui_init(SCR_WIDTH,SCR_HEIGHT))
    {
        printf("\nui init fail!");
        return FALSE;
    }
    else
    {
        printf("\nui init succ!");
    }
    lcd_clear();

}

