#ifndef _PLAY_SEL_H_
#define _PLAY_SEL_H_

#include "includes.h"
#include "config.h"
#include "avctp_user.h"

// #define DEC_SEL_DEBUG
#ifdef DEC_SEL_DEBUG
#define dsel_printf printf
#define dsel_puts puts
#else
#define dsel_printf(...)
#define dsel_puts(...)
#endif

enum
{
    BT_CFG_FILE = 0x01,  /*蓝牙配置文件默认放在第一个文件，与库对应，不可修改成其它值*/
    EQ_CFG_FILE,
    BPF_MUSIC_MP3,
#ifdef MUSIC_PROMPT_EN
	BPF_SD_MP3,
	BPF_USB_MP3,
#endif
#if FM_RADIO_EN
    BPF_RADIO_MP3,
#endif
    BPF_LINEIN_MP3,
    BPF_WAIT_MP3,
    BPF_CONNECT_MP3,
    BPF_DISCONNECT_MP3,
    BPF_RING_MP3,

#if BT_PHONE_NUMBER
    BPF_0_MP3,
    BPF_1_MP3,
    BPF_2_MP3,
    BPF_3_MP3,
    BPF_4_MP3,
    BPF_5_MP3,
    BPF_6_MP3,
    BPF_7_MP3,
    BPF_8_MP3,
    BPF_9_MP3,
#endif
#if USB_PC_EN
    BPF_PC_MP3,
#endif
    BPF_BT_MP3,
#if defined(SUPPORT_WELCOME_VOICE)||defined(POWER_ON_WELCOME_VOICE_PLAYED_IN_IDLE_MODE)
    BPF_WELCOME_MP3,
#endif
#ifdef SUPPORT_BT_TWO_TYPE_VOICE
	BPF_BT1_MP3,
    BPF_CONNECT1_MP3,
    BPF_DISCONNECT1_MP3,
#endif

#ifdef SUPPORT_VOICE_ONOFF_VOICE
	BPF_VOICE_ON_MP3,
	BPF_VOICE_OFF_MP3,
#endif

#if BT_HID_INDEPENDENT_MODE || USER_SUPPORT_PROFILE_HID
    BPF_CONN_HID_MP3,
    BPF_DISCON_HID_MP3,
#endif
    BPF_LOW_POWER_MP3,
#if RTC_CLK_EN
    BPF_RTC_MP3,
#endif
#ifdef support_ac3_voice
    BPF_AC3_MP3,
#endif

#if REC_EN
#ifdef support_rec_recplay_notice    
    BPF_REC_MP3,
    BPF_RECPLAY_MP3,
#endif    
#endif

#ifdef  support_power_off_tone
	BPF_POWER_OFF_MP3,
#endif

#ifdef  support_power_on_tone
	BPF_POWER_ON_MP3,
#endif

#ifdef SUPPORT_KEY_6_VOICE            
	    BPF_VL_MAX_YESE,
	    BPF_VL_MAX_END,	
	    BPF_VL_MAX_APPLAUD,
	    BPF_VL_MAX_GUN,
	    BPF_VL_MAX_ZXC,
	    BPF_VL_MAX_BEST_PARTNER,
#endif

#ifdef  SUPPORT_ZY_SA_VOICE
#if defined SUPPORT_ONLY_MODE_VOICE

	BPF_MUSIC_MP3_EN,
	BPF_SD_MP3_EN,
	BPF_USB_MP3_EN,
	BPF_RADIO_MP3_EN,
	BPF_LINEIN_MP3_EN,
	BPF_WAIT_MP3_EN,
	BPF_CONNECT_MP3_EN,
	BPF_DISCONNECT_MP3_EN,
	BPF_BT_MP3_EN,    
#if REC_EN
#ifdef support_rec_recplay_notice    
	BPF_REC_MP3_EN,
	BPF_RECPLAY_MP3_EN,
#endif
#endif
  #ifdef SUPPORT_VOICE_ONOFF
	BPF_WAIT_MP3_NOTICE,
	BPF_CONNECT_MP3_NOTICE,
	BPF_DISCONNECT_MP3_NOTICE,
#endif

#ifdef SUPPORT_VOICE_ONOFF_VOICE
	BPF_VOICE_ON_MP3_EN,
	BPF_VOICE_OFF_MP3_EN,
#endif

#else

	BPF_PLAY_MP3,
	BPF_PAUSE_MP3,
	BPF_PREV_MP3,
	BPF_NEXT_MP3,

	BPF_REP_ONE_MP3,
	BPF_REP_ALL_MP3,

	BPF_NORMAL_MP3,
	BPF_POP_MP3,
	BPF_ROCK_MP3,
	BPF_JAZZ_MP3,
	BPF_CLASS_MP3,
	BPF_SOFT_MP3,
	
	BPF_VL_DEC_MP3,
	BPF_VL_INC_MP3,
	BPF_VL_MAX_MP3,
	BPF_MUTE_MP3,


	BPF_FM_SCAN_MP3,
	BPF_LAST_CH_MP3,
	BPF_NEXT_CH_MP3,
#ifdef SUPPORT_FM_SCAN_END_VOICE
	BPF_FM_SCAN_END_MP3,
#endif

#ifdef SUPPORT_DOUBLE_VOICE
	BPF_MUSIC_MP3_EN,
	BPF_SD_MP3_EN,
	BPF_USB_MP3_EN,
	BPF_RADIO_MP3_EN,
	BPF_LINEIN_MP3_EN,
	BPF_WAIT_MP3_EN,
	BPF_CONNECT_MP3_EN,
	BPF_DISCONNECT_MP3_EN,
	BPF_BT_MP3_EN,    
#if REC_EN
#ifdef support_rec_recplay_notice    
	BPF_REC_MP3_EN,
	BPF_RECPLAY_MP3_EN,
#endif
#endif
	BPF_PLAY_MP3_EN,
	BPF_PAUSE_MP3_EN,
	BPF_PREV_MP3_EN,
	BPF_NEXT_MP3_EN,
	BPF_REP_ONE_MP3_EN,
	BPF_REP_ALL_MP3_EN,
	BPF_NORMAL_MP3_EN,
	BPF_POP_MP3_EN,
	BPF_ROCK_MP3_EN,
	BPF_JAZZ_MP3_EN,
	BPF_CLASS_MP3_EN,
	BPF_SOFT_MP3_EN,	
	BPF_VL_DEC_MP3_EN,
	BPF_VL_INC_MP3_EN,
	BPF_VL_MAX_MP3_EN,
	BPF_MUTE_MP3_EN,
	BPF_FM_SCAN_MP3_EN,
	BPF_LAST_CH_MP3_EN,
	BPF_NEXT_CH_MP3_EN,	
	
//	BPF_VOICE_ON_MP3_EN,
//	BPF_VOICE_OFF_MP3_EN,
#else
	BPF_VOICE_ON_MP3,
	BPF_VOICE_OFF_MP3,
#endif
		
#endif

#endif

};

////*
typedef struct __PLAY_SEL_PARA //para
{
    u32 max_file_number;
    u32 rpt_time;
    u32 delay;
    u32 *file_number;
} _PLAY_SEL_PARA;
/////*/

typedef struct __PLAY_SEL_API
{
    u32 device_sel;
    _PLAY_SEL_PARA *file_par;
    tbool busy;
    tbool alive;
    void *father_name;
} _PLAY_SEL_API;

tbool play_sel(void *name,u32 device_sel,_PLAY_SEL_PARA *file_par);
tbool play_sel_busy(void);
tbool play_sel_stop(void);

#endif
