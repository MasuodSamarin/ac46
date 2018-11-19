#include "lcd_drv_api.h"
#include "lcd_drv.h"
#include "lcd_cfg.h"



tu16 lcd_get_width(void)
{
//    return g_lcd_width;
}

tu16 lcd_get_height(void)
{
//    return g_lcd_height;
}


/*----------------------------------------------------------------------------*/
/**@brief    清屏的指定区域，只清BUFF但不更新
   @param    p1:起始 page
   @param    p2:结束page
   @return
   @note     void LCDClearArea(u8 p1,u8 p2)
*/
/*----------------------------------------------------------------------------*/
void lcd_clear_area(u8 start_page,u8 end_page)
{
    for (; start_page < end_page; start_page++)
    {
        my_memset((disp_buf + start_page *LCDCOLUMN), 0x00, LCDCOLUMN);
    }
}


/*----------------------------------------------------------------------------*/
/**@brief    清屏的指定区域，只清BUFF并且更新到显存
   @param    p1:起始 page
   @param    p2:结束page
   @return
   @note     void lcd_clear_area_with_draw(u8 start_page,u8 end_page)
*/
/*----------------------------------------------------------------------------*/
void lcd_clear_area_with_draw(u8 start_page,u8 end_page)
{
    for (; start_page < end_page; start_page++)
    {
        my_memset((disp_buf + start_page *LCDCOLUMN), 0x00, LCDCOLUMN);
        lcd_draw(start_page, 1, disp_buf);
    }
}


/*----------------------------------------------------------------------------*/
/**@brief    清屏的指定区域的指定宽度，只清BUFF但不更新
   @param    p1:起始 page
   @param    p2:结束page
   @param    x0:起始列
   @param    x1:结束列
   @return
   @note     void lcd_clear_area_rect(u8 start_page,u8 end_page,u8 x0,u8 x1)
*/
/*----------------------------------------------------------------------------*/
void lcd_clear_area_rect(u8 start_page,u8 end_page,u8 x0,u8 x1)
{
    for (; start_page < end_page; start_page++)
    {
        my_memset((disp_buf + start_page *LCDCOLUMN + x0), 0x00, x1- x0);
    }
}

/*----------------------------------------------------------------------------*/
/**@brief    页区域取反实现函数
   @param    startpage: 取反page
   @param    pagelen：  取反page的个数
   @return   返回取反结果
   @note     tbool lcd_TurnPixelReverse_Page(u8 startpage, u8 pagelen)
*/
/*----------------------------------------------------------------------------*/
tbool lcd_TurnPixelReverse_Page(u8 startpage, u8 pagelen)
{
    u8 hnum,l;

    if( (startpage > LCDPAGE) || (pagelen > LCDPAGE) )
        return FALSE;

    for(hnum=startpage; hnum<startpage+pagelen; hnum=hnum+1)
    {
        for(l=0; l<LCDCOLUMN; l++)
        {
            *(disp_buf+hnum*LCDCOLUMN+l) =  ~(*(disp_buf+hnum*LCDCOLUMN+l));
        }
    }
    return TRUE;
}

/*----------------------------------------------------------------------------*/
/**@brief    区域取反实现函数
   @param    left:   取反区域的左边界限
   @param    top：   取反区域的顶部界限
   @param    right： 取反区域的右边界限
   @param    bottom：取反区域的底部界限
   @param    left、right取值范围：0--(LCDCOLUMN-1)  ;  top、bottom取值范围：0--(LCDPAGE-1)
   @return   返回取反结果
   @note     tbool lcd_TurnPixelReverse_Rect(u8 left, u8 top, u8 right, u8 bottom)
*/
/*----------------------------------------------------------------------------*/
tbool lcd_TurnPixelReverse_Rect(u8 left, u8 top, u8 right, u8 bottom)
{
    u8 hnum,l;

    if( (left>=LCDCOLUMN) || (top>=LCDPAGE) || (left>=right) || (top>=bottom) )
        return FALSE;

    for(hnum = top; hnum < bottom + 1; hnum = hnum + 1)
    {
        for(l=left; l < right; l++)
        {
            *(disp_buf+hnum*LCDCOLUMN+l) = ~(*(disp_buf+hnum*LCDCOLUMN+l));
        }
    }

    return TRUE;
}
