#include "config.h"
#include "ui_api.h"
#include "led7_drv.h"
#include "lcd_drv_api.h"
#include "lcd_disp.h"
#include "key.h"
#include "msg.h"

#if UI_ENABLE

UI_VAR      UI_var;   //UI 显示变量
UI_DISP_API * ui_disp_api;

#if LED_7_EN
static const UI_DISP_API ui_led7 =
{
    .ui_string_menu = led7_show_string_menu,

    .ui_music_main =led7_show_music_main,

    .ui_vol_set = led7_show_volume,
    .ui_eq_set = led7_show_eq,
    .ui_file_num =led7_show_filenumber,
    .ui_play_mode =led7_show_playmode,

	.ui_FM_main = led7_show_fm_main,
	.ui_FM_channel=led7_show_fm_station,

	.ui_RTC_main=led7_show_RTC_main,
	.ui_RTC_set=led7_show_RTC_main,
	.ui_ALM_set=led7_show_alarm,

	.ui_REC_main=led7_show_rec_main,

    .ui_clear =led7_clear_icon,
};
#endif

#if LCD_128X64_EN
static const UI_DISP_API ui_lcd12864 =
{
    .ui_string_menu = lcd_disp_string_menu,

    .ui_music_main =lcd_null_dis,

    .ui_vol_set = lcd_null_dis,
    .ui_eq_set = lcd_null_dis,
    .ui_file_num =lcd_null_dis,
    .ui_play_mode =lcd_null_dis,

	.ui_FM_main = lcd_fm_main,
	.ui_FM_channel=lcd_fm_channel,

	.ui_RTC_main=lcd_null_dis,
	.ui_RTC_set=lcd_null_dis,
	.ui_ALM_set=lcd_null_dis,

	.ui_REC_main=lcd_null_dis,

    .ui_clear =lcd_clear,
};
#endif

void ui_init_api(void)
{

#if LED_7_EN
    led7_init();
    ui_disp_api = &ui_led7;
#endif

#if LCD_128X64_EN
    lcd_init();
    ui_disp_api = &ui_lcd12864;
#endif

}

/*----------------------------------------------------------------------------*/
/**@brief   UI 显示界面处理函数
   @param   menu：需要显示的界面
   @return  无
   @note    void UI_menu_api(u8 menu)
*/
/*----------------------------------------------------------------------------*/
void ui_menu_api(u8 menu)
{

    if(UI_var.bLockMenu != 0)
    {
        if(menu != UI_var.bLockMenu)
            return;
    }

    /*界面属性-非主界面自动返回*/
    if (menu == MENU_MAIN)
    {
        if (UI_var.bMenuReturnCnt < UI_RETURN)
        {
            UI_var.bMenuReturnCnt++;
            if (UI_var.bMenuReturnCnt == UI_RETURN)
            {
                ui_disp_api->ui_clear();
                if (UI_var.bCurMenu == MENU_INPUT_NUMBER)
                {
                    os_taskq_post_msg(keymsg_task_name, 1, MSG_INPUT_TIMEOUT);
                }
                else
                {
                    UI_var.bCurMenu = UI_var.bMainMenu;
                }
            }
        }
        else
        {
            /*等待界面不重复刷新界面*/
            if (UI_var.bCurMenu == UI_var.bMainMenu)
                return;
            UI_var.bCurMenu = UI_var.bMainMenu;
        }
    }
    else
    {
        if (menu > 0x80)    //仅在当前界面为主界面时刷新界面,例如：在主界面刷新播放时间
        {
            if (UI_var.bCurMenu != UI_var.bMainMenu)
                return;
        }
        else
        {
            ui_disp_api->ui_clear();
            /*非主界面需要启动返回计数器*/
            if (menu != UI_var.bMainMenu)
                UI_var.bMenuReturnCnt = 0;
            UI_var.bCurMenu = menu;
            if (menu != MENU_INPUT_NUMBER)
                input_number = 0;
        }
    }

#if LED_7_EN
    led7_setX(0);
#endif

    switch(UI_var.bCurMenu)
    {
    /*-----System Power On UI*/
    case MENU_POWER_UP:
    case MENU_WAIT:

    case MENU_BT_MAIN:

    case MENU_PC_MAIN:
    case MENU_PC_VOL_UP:
    case MENU_PC_VOL_DOWN:

    case MENU_AUX_MAIN:
#ifdef RTC_ALM_EN
    case MENU_ALM_UP:
#endif
        ui_disp_api->ui_string_menu(UI_var.bCurMenu);
        break;

        /*-----Common Info UI*/
    case MENU_MAIN_VOL:
        ui_disp_api->ui_vol_set();
        break;

    case MENU_INPUT_NUMBER:
        //led7_show_IR_number();
        break;

        /*-----Music Related UI*/
    case MENU_MUSIC_MAIN:
    case MENU_PAUSE:
        ui_disp_api->ui_music_main();
        //led7_show_music_main();
        break;
    case MENU_FILENUM:
        ui_disp_api->ui_file_num();
        //led7_show_filenumber();
        break;
    case MENU_EQ:
        ui_disp_api->ui_eq_set();
        //led7_show_eq();
        break;

    case MENU_PLAYMODE:
        ui_disp_api->ui_play_mode();
        //led7_show_playmode();
        break;

        /*-----FM Related UI*/
    case MENU_FM_MAIN:
    case MENU_FM_DISP_FRE:
        ui_disp_api->ui_FM_main();
        //led7_show_fm_main();
        break;
    case MENU_FM_FIND_STATION:
    case MENU_FM_CHANNEL:
        ui_disp_api->ui_FM_channel();
        //led7_show_fm_station();
        break;


#if RTC_CLK_EN
    case MENU_RTC_MAIN:
        //RTC_setting_var.bMode = 0;    //模式与界面同步返回
    case MENU_RTC_SET:
        ui_disp_api->ui_RTC_main();
        //led7_show_RTC_main();
        break;

#if RTC_ALM_EN
    case MENU_ALM_SET:
        ui_disp_api->ui_ALM_set();
        //led7_show_alarm();
        break;
#endif/*RTC_ALM_EN*/

#if REC_EN
    case MENU_RECODE_MAIN:
        ui_disp_api->ui_REC_main();
        //led7_show_rec_main();
        break;
#endif/*REC_EN*/

#endif/*RTC_CLK_EN*/

    default:
        break;
    }

#if LCD_128X64_EN
    draw_lcd_buf();
#endif
}
#endif
