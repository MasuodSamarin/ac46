/*--------------------------------------------------------------------------*/
/**@file    LED_UI_API.c
   @brief   LED 显示界面接口函数
   @details
   @author  bingquan Cai
   @date    2012-8-30
   @note    AC319N
*/
/*----------------------------------------------------------------------------*/
#include "ui_api.h"
#include "config.h"

#if UI_ENABLE

#include "led7_drv.h"
#include "key.h"
#include "msg.h"

#ifdef SUPPORT_MUSIC_INTRO_PLAY
extern bool mp3_intro_play;
#endif
#ifdef LED_SHOW_REPEAT_ALL_ONE_FOLDER_NORMAL
extern u8 repeat_mode;
#endif
extern bool bir_5_plus;
extern bool bir_10_plus;
extern bool bir_100_plus;
extern bool bir_200_plus;
#ifdef SUPPORT_IR_INPUT_2_3NUMS
extern bool bir_2_nums;
extern bool bir_3_nums;
#endif

UI_VAR UI_var;   /*UI 显示变量*/
/*----------------------------------------------------------------------------*/
/**@brief   UI 显示界面处理函数
   @param   menu：需要显示的界面
   @return  无
   @note    void UI_menu_api(u8 menu)
*/
/*----------------------------------------------------------------------------*/
void UI_menu_api(u8 menu)
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
                led7_clear_icon();
                #ifdef support_menu_mode
				   menumode=0;
                #endif
								
                if (UI_var.bCurMenu == MENU_INPUT_NUMBER)
                {
                    //put_msg_lifo(MSG_INPUT_TIMEOUT);    //输入超时
                    os_taskq_post_msg(keymsg_task_name, 1, MSG_INPUT_TIMEOUT);
                    bir_200_plus=FALSE;
                    bir_100_plus=FALSE;
                    bir_10_plus=FALSE;
                    bir_5_plus=FALSE;
					
                  #ifdef SUPPORT_IR_INPUT_2_3NUMS
					bir_2_nums=FALSE;
					bir_3_nums=FALSE;
                  #endif
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
         #ifdef LED_SHOW_MP3_PAUSE
			  if(menu!=MENU_AUX_PAUSE)
	     #endif
            led7_clear_icon();
            /*非主界面需要启动返回计数器*/
            if (menu != UI_var.bMainMenu)
                UI_var.bMenuReturnCnt = 0;
            UI_var.bCurMenu = menu;
            if (menu != MENU_INPUT_NUMBER)
                input_number = 0;
        }
    }
	
    led7_setX(0);

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
#ifdef SUPPORT_MP3_IDEL_MODE_IN_LINEIN_MODE
	case MENU_MP3_IDLE_MAIN:
#endif
#ifdef SUPPORT_AC3_MODE_IN_LINEIN_MODE
	case MENU_AC3_MAIN: 
#endif
#ifdef SUPPORT_DVD_MODE_IN_LINEIN_MODE
	case MENU_DVD_MAIN: 
#endif
#ifdef SUPPORT_CD_MODE_IN_LINEIN_MODE
	case MENU_CD_MAIN: 
#endif

        led7_show_string_menu(UI_var.bCurMenu);
        break;
 #ifdef LED_SHOW_POWER_OFF_STRING
	 case MENU_STANDBY:
	   led7_show_string_standby();
	   break;
 #endif
#ifdef LED_SHOW_INTRO_STRING
	 case MENU_MUSIC_INTRO:
	   led7_show_string_intro(mp3_intro_play);
	   break;
#endif
        /*-----Common Info UI*/
    case MENU_MAIN_VOL:
        led7_show_volume();
        break;

    case MENU_INPUT_NUMBER:
        led7_show_IR_number();
        break;

        /*-----Music Related UI*/
    case MENU_MUSIC_MAIN:
    case MENU_PAUSE:
        led7_show_music_main();
        break;
#ifdef LED_ID_WLD007		
        led7_show_music_main();
        break;
#else
    case MENU_FILENUM:
        led7_show_filenumber();
        break;
#endif		
    case MENU_EQ:
        led7_show_eq();
        break;

    case MENU_PLAYMODE:
        led7_show_playmode();
        break;

        /*
            case MENU_NUM:
              led7_show_num(ui_sample_rate,ui_bit_rate);
              break;
        */
        /*-----FM Related UI*/
    case MENU_FM_MAIN:
    case MENU_FM_DISP_FRE:
        led7_show_fm_main();
        break;
    case MENU_FM_FIND_STATION:
    case MENU_FM_CHANNEL:
        led7_show_fm_station();
        break;


#if RTC_CLK_EN
    case MENU_RTC_MAIN:
        //RTC_setting_var.bMode = 0;    //模式与界面同步返回
    case MENU_RTC_SET:
        led7_show_RTC_main();
        break;

#if RTC_ALM_EN
    case MENU_ALM_SET:
        led7_show_alarm();
        break;
#endif

#if REC_EN
//    case MENU_RECODE_START:
//        led7_show_rec_start();
//        break;

    case MENU_RECODE_MAIN:
        led7_show_rec_main();
        break;
#ifdef LED_SHOW_DEL
	case MENU_REC_DEL:
	    led7_show_del();
	    break;
#endif
        
#endif

#endif

#if defined(support_line_pause  )||defined(LED_SHOW_MP3_PAUSE)
    #if defined(LED_SHOW_MP3_PAUSE)
    case MENU_MP3_PAUSE:
    #endif
    case MENU_AUX_PAUSE:
        led7_show_AUX_PAUSE();
	break;	
#endif

#ifdef SUPPORT_MUSIC_STOP
		case MENU_MUSIC_STOP:
			led7_show_stop();
			break;
#endif
#ifdef LED_SHOW_DEVICE_PLUGIN
			case MENU_DEIVCE:
			led7_show_plugin_dev(); 
			break;
#endif
      #ifdef LED_SHOW_DEVICE_TYPE_SWITCH
			 case MENU_DEVICE_SWITCH:
			 led7_show_device_switch();
			 break;
      #endif
	
#ifdef LED_SHOW_PREV_NEXT_FOLDER_SWITCH
		case MENU_PREV_FOLDER:
		led7_show_prev_next_folder(TRUE); 
		break;
		case MENU_NEXT_FOLDER:
		led7_show_prev_next_folder(FALSE); 
		break;
#endif
#ifdef LED_SHOW_REPEAT_ALL_ONE_FOLDER_NORMAL
		case MENU_USER_REPEAT_MODE:
		   led7_show_user_repeat_mode(repeat_mode); 
		break;
#endif
#ifdef support_menu_mode
		case MENU_VOL_MENU:
			LED7_SHOW_VOL_MENU();
			break;
#endif
#ifdef Support_MSG_RESET
		case MENU_RESET:
		   LED7_SHOW_RESET();
		   break;
#endif
#ifdef LED_SCREEN_SHOW_LED_MODE
		case MENU_LED_MODE:
		 led7_show_RGB_led_mode();
		  break;
#endif
#ifdef LED_SHOW_ONOFF
      case MENU_ONOFF:
         LED7_SHOW_LED_ONOFF();
         break;
#endif
#ifdef KEY_CONTROL_LED_SCREEN_COLOR_MODE
		case MENU_LED_SCREEN_COLOR_TYPE:
		led7_show_led_screen_color_type();
		break;
#endif

#ifdef SUPPORT_MIC_LED_SHOW_ONOFF	,
	case MENU_MIC_ONOFF:
	led7_show_led_mic_onoff();
	break;	
#endif
	

    default:
        break;
    }
}
#endif
