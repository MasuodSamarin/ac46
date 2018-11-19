#ifndef _UI_API_H_
#define _UI_API_H_

#include "includes.h"
#include "config.h"
#include "DECODER_PHY.H"

enum
{
    MENU_POWER_UP = 0,
    MENU_WAIT,
    MENU_BT_MAIN,
    MENU_PC_MAIN,
    MENU_PC_VOL_UP,
    MENU_PC_VOL_DOWN,
    MENU_AUX_MAIN,
    MENU_ALM_UP,

    
    /***以上数据对应menu_string数组，顺序不能修改***/
#ifdef SUPPORT_MP3_IDEL_MODE_IN_LINEIN_MODE
	MENU_MP3_IDLE_MAIN,
#endif
#ifdef SUPPORT_AC3_MODE_IN_LINEIN_MODE
	MENU_AC3_MAIN,
#endif
#ifdef SUPPORT_CD_MODE_IN_LINEIN_MODE
		MENU_CD_MAIN,
#endif
#ifdef SUPPORT_DVD_MODE_IN_LINEIN_MODE
		MENU_DVD_MAIN,
#endif

    MENU_PLAY,
    MENU_PLAYMODE,
    MENU_MAIN_VOL,
    MENU_EQ,

    MENU_NOFILE,
    MENU_NODEVICE,
    MENU_PLAY_TIME,
    MENU_FILENUM,
    MENU_INPUT_NUMBER,
    MENU_MUSIC_MAIN,
    MENU_PAUSE,

    MENU_FM_MAIN,
    MENU_FM_DISP_FRE,
    MENU_FM_FIND_STATION,
    MENU_FM_CHANNEL,

    MENU_USBREMOVE,
    MENU_SDREMOVE,
    MENU_SCAN_DISK,

    MENU_NOP,
    MENU_NUM,

    MENU_RTC_MAIN,
    MENU_RTC_SET,
    MENU_RTC_PWD,
    MENU_ALM_SET,
	MENU_ALM_REQUEST,

    MENU_BT_SEARCH_DEVICE,
    MENU_BT_CONNECT_DEVICE,
    MENU_BT_DEVICE_ADD,
    MENU_BT_DEVICE_NAME,

    BLUETOOTH_SHOW_DEVICE_ADDR_NAME_DEFAULT,
    BLUETOOTH_CLEAR_LCD,
    BLUETOOTH_TEST_A2DP,
    BLUETOOTH_TEST_HFP,
    BLUETOOTH_TEST_HID,
    BLUETOOTH_TEST_OFFSET,
    BLUETOOTH_VALUE_OFFSET,

    MENU_RECODE_MAIN,
#ifdef SUPPORT_MIC_LED_SHOW_ONOFF
	MENU_MIC_ONOFF,
#endif
#ifdef LED_SHOW_DEL
		MENU_REC_DEL,
#endif
#if defined support_line_pause||  defined LED_SHOW_MP3_PAUSE
	MENU_AUX_PAUSE,
#endif 
#ifdef LED_SHOW_MP3_PAUSE
    MENU_MP3_PAUSE,
#endif
#ifdef SUPPORT_MUSIC_STOP
	MENU_MUSIC_STOP,
#endif
#ifdef LED_SCREEN_SHOW_LED_MODE
	MENU_LED_MODE,
#endif
#ifdef KEY_CONTROL_LED_SCREEN_COLOR_MODE
	MENU_LED_SCREEN_COLOR_TYPE,
#endif
#ifdef LED_SHOW_DEVICE_PLUGIN
	MENU_DEIVCE,
#endif
#ifdef LED_SHOW_DEVICE_TYPE_SWITCH
	MENU_DEVICE_SWITCH,
#endif
#ifdef LED_SHOW_POWER_OFF_STRING
    MENU_STANDBY,
#endif
#ifdef SUPPORT_MUSIC_INTRO_PLAY
    MENU_MUSIC_INTRO,
#endif
#ifdef LED_SHOW_PREV_NEXT_FOLDER_SWITCH
	MENU_PREV_FOLDER,
	MENU_NEXT_FOLDER,
#endif
#ifdef LED_SHOW_REPEAT_ALL_ONE_FOLDER_NORMAL
	MENU_USER_REPEAT_MODE,
#endif
#ifdef support_menu_mode
	MENU_VOL_MENU,
#endif
#ifdef Support_MSG_RESET
	MENU_RESET,
#endif
#ifdef LED_SHOW_ONOFF
    MENU_ONOFF,
#endif

    MENU_200MS_REFRESH = 0x80,
    MENU_100MS_REFRESH,
    MENU_SET_EQ,
    MENU_SET_PLAY_MODE,
    MENU_HALF_SEC_REFRESH,
	MENU_POWER_DOWN,
    MENU_SPEC,
    MENU_MAIN = 0xFF,
};


typedef struct _UI_VAR
{
    u8  bCurMenu;
    u8  bMainMenu;
    u8  bMenuReturnCnt;
    u8  bLockMenu;
}UI_VAR;

extern void set_LED_fade_out(void);
extern void set_LED_all_on(void);

void UI_menu_api(u8 menu);

#if UI_ENABLE
#define UI_menu(x)      UI_menu_api(x)
#define SET_UI_MAIN(x)  UI_var.bMainMenu = x
#define SET_UI_LOCK(x)   UI_var.bLockMenu = x
#define SET_UI_UNLOCK(x) UI_var.bLockMenu = 0
#else
#define UI_menu(...)
#define SET_UI_MAIN(...)
#define SET_UI_LOCK(...)
#define SET_UI_UNLOCK(...)
#endif

extern UI_VAR _data UI_var;

#define UI_RETURN       5

#endif  /*  _LED_UI_API_H_  */
