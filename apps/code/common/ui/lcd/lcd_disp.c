#include "config.h"
#include "dac_api.h"
#include "lcd_disp.h"
#include "ui_con.h"
#include "ui.h"
#include "ui_api.h"

#if  LCD_128X64_EN

const char lcd_string[][16] =
{
    "HELLO",
    "LOADING",
    "����ģʽ",
    "PCģʽ",
    "UP",
    "DOWN",
    "AUXģʽ",
    "-AUX-",

    "����ģʽ",
    "����ģʽ",
    "ʱ��ģʽ",
    "¼��ģʽ",
};

/*----------------------------------------------------------------------------*/
/**@brief   LCD�ı���ʾ
   @param   void
   @return  void
   @note    void lcd_disp_text(void)
*/
/*----------------------------------------------------------------------------*/
void lcd_disp_text(u8 str_num)
{
    DTEXT disp_txt;

    disp_txt.buf = lcd_string[str_num];

    disp_txt.flags = ANSI;
    disp_txt.len = strlen((char *)disp_txt.buf);
    ui_text(DVcTxt1_1, &disp_txt);
}

/*----------------------------------------------------------------------------*/
/**@brief   LCD������ʾ
   @param   void
   @return  void
   @note    void lcd_disp_welcome(void)
*/
/*----------------------------------------------------------------------------*/
void lcd_disp_welcome(void)
{
//    ui_pic(DVcRzImg1_1,NULL,0);
    lcd_disp_text(0);
}

/*----------------------------------------------------------------------------*/
/**@brief   LCD������Ŀ��ʾ
   @param   void
   @return  void
   @note    void lcd_disp_bt(void)
*/
/*----------------------------------------------------------------------------*/
void lcd_disp_bt(void)
{
//    ui_pic(DVcRzImg3_4,NULL,0);
//    ui_pic(DVcRzImg1_4,NULL,0);
//    ui_pic(DVcRzImg2_4,NULL,0);
    lcd_disp_text(0);
}

void lcd_disp_string_menu(u8 menu)
{
    lcd_disp_text(menu);
}

/*----------------------------------------------------------------------------*/
/**@brief   LCD������ʾ����
   @param   void
   @return  void
   @note    void lcd_disp_vol(u8 vol)
*/
/*----------------------------------------------------------------------------*/
u16 hook_lcd_set_vol(u8 mode, DSLIDER* slider)
{
    slider->min_val = 0;
    slider->max_val = 30;
    slider->curr_val = dac_var.cur_sys_vol_l;
}

void lcd_disp_vol(void)
{
//    ui_slider(DVcMove1_3,hook_lcd_set_vol,0);
}

void lcd_fm_main(void)
{
    lcd_disp_text(9);
}

void lcd_fm_channel(void)
{

}

void lcd_null_dis(void)
{
    GUI_POINT pos;
    pos.x = 10;
    pos.y = 10;
    ui_pic(DVcRzImg1_1,&pos,0);
}
#endif/*LCD_128x64_EN*/
