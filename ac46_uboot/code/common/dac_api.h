#ifndef __DAC_API_H__
#define __DAC_API_H__

//#include "includes.h"
#include "dac.h"

#define dac_delay(x)    delay(x)

#define DIGITAL_VOL_MAX_L     31        ///<����ͨ������������ڼ���
#define DIGITAL_VOL_MAX_R     31

#define ANALOG_VOL_MAX_L      31        ///<ģ��ͨ������������ڼ���
#define ANALOG_VOL_MAX_R      31

#define FADE_ON      1                  ///<ͨ���л�ʹ�õ��뵭��
#define FADE_OFF     0                  ///<ͨ���л���ʹ�õ��뵭��

#define BT_CHANNEL         DAC_DIGITAL_AVOL
#define MUSIC_CHANNEL      DAC_DIGITAL_AVOL
#define RTC_CHANNEL        DAC_DIGITAL_AVOL
#define RADIO_CHANNEL      DAC_DIGITAL_AVOL
#define LINEIN_CHANNEL     DAC_AMUX2
#define UDISK_CHANNEL      DAC_DIGITAL_AVOL

#define MAX_SYS_VOL_L    30     ///<ϵͳ����������
#define MAX_SYS_VOL_R    30


enum
{
    DAC_SET_AVOL_BIT = 7,                ///<����ģ������
    DAC_SET_DVOL_BIT = 8,                ///<������������
    DAC_NET_AVOL=DAC_SET_AVOL_BIT,     ///<����ͨ������������������ģ������
    DAC_NET_DVOL=DAC_SET_DVOL_BIT,     ///<����ͨ��������������������������
};

enum
{
    DAC_DIGITAL_DVOL = 1,               ///<����ͨ����������������������
    DAC_DIGITAL_AVOL,                   ///<����ͨ��������������ģ������
    DAC_DIGITAL_D_A_VOL,                ///<����ͨ��������������ͬʱ����ģ����������������
    DAC_AMUX0,                          ///>PORTC-10-11
    DAC_AMUX1,                          ///>PORTC-12-13
    DAC_AMUX2,                          ///>PORTC-14-15
    LINE_ONE_IN_TWO_OUT,
    LINE_TWO_IN_ONE_OUT,     ///
};

#define  AUTO_MUTE_ENABLE  BIT(0)
#define  AUTO_UNMUTE_FADE  BIT(1)

typedef struct __DAC_DIGIT_AUTO_MUTE
{
    u16 wVoiceCnt;
    u16 wVoiceThreshold;
    u8 auto_mute_ctl;
    volatile u8 bAutoMute;
    u8 max_cnt;
}DAC_DIGIT_AUTO_MUTE;

typedef struct __DAC_VAR
{
    DAC_DIGIT_AUTO_MUTE d_auto_mute;
    u16 channel_mode;                   ///<ͨ��ģʽ
    u8 cur_sys_vol_l;                   ///<��ǰϵͳ�����ȼ�
    u8 cur_sys_vol_r;
    u8 tem_sys_vol_a;                   ///<��ʱϵͳ�����ȼ�
    u8 tem_sys_vol_d;
    u8 digital_vol_l;                   ///<����ͨ�������ȼ�
    u8 digital_vol_r;
    u8 analog_vol_l;                    ///<ģ��ͨ�������ȼ�
    u8 analog_vol_r;
    u8 fade_vol_l;                    ///<ģ��ͨ�������ȼ�
    u8 fade_vol_r;
    u8 max_analog_vol_l;//ANALOG_VOL_MAX_Lmax_vol
    u8 max_analog_vol_r;
    volatile u8 bfade_in_l;             ///<����Ч��
    volatile u8 bfade_in_r;
    volatile u8 bfade_out_l;            ///<����Ч��
    volatile u8 bfade_out_r;
    volatile u8  bMute;                 ///<mute״̬
}DAC_VAR;

typedef struct __DAC_DIGT_CTL
{
//    u32 dac_rate;
//    volatile tbool enable;
    volatile tbool lr2one;
    volatile tbool mute;
//    u16(*key_voice_busy)();
//    u32(*digit_audio_integration)(s16 *buf,u32 len);
//    void*(*enable_hook)(void*,s16 *,u32 len);
//    u32 obuf_len;
}DAC_DIGT_CTL;


typedef struct __BT_VOL_VAR
{
    u8 a2dp_music_vol;
    u8 hfp_phone_vol;
    u8 set_vol_flag;
}BT_VOL_VAR;

typedef enum
{
    AUDIO_CHANNEL_FAIL = 0,
    AUDIO_CHANNEL_SAME = 0x40000000,
    AUDIO_CHANNEL_SUCC = 0x80000000,
}_AUDIO_CHANNEL;

extern DAC_VAR dac_var;
extern BT_VOL_VAR bt_vol;
extern DAC_DIGT_CTL dac_digt_ctl;

u8 get_dac_phy_vol(bool r);
void dac_close2_fade(u8 fade_en,u8 fade_vol_l,u8 fade_vol_r);
void dac_fade_in(u8 fade_en);
void dac_fade_out(u8 fade_en);
void dac_fade(void);

_AUDIO_CHANNEL dac_channel_on(u8 channel, u8 fade_en);
void dac_channel_off(u8 channel, u8 fade_en);
void dac_channel_off_self(u8 channel, u8 fade_en);
u16 get_cur_dac_channel(void);
void dac_channel_off_self(u8 channel, u8 fade_en);
u16 get_cur_dac_channel(void);
void dac_api_init(u8 max_analog_vol_l,u8 max_analog_vol_r);
void set_max_analog_vol(u8 max_analog_vol_l,u8 max_analog_vol_r);
void set_dac_digital(u32 l_vol, u32 r_vol);
void set_dac_analog(u32 l_vol, u32 r_vol);
void set_vol_mode(u32 mode);
void set_sys_vol(u32 l_vol, u32 r_vol, u8 fade_en);
u16 get_digital_tab_vol(u32 vol);
void digital_vol_ctrl(s16 *buf, u32 len);
void set_digital_vol(u32 l_vol, u32 r_vol);
void set_analog_vol(u32 l_vol, u32 r_vol);
u32 dac_digit_energy_value(s16 *buf,u16 len);
//
extern void digit_auto_mute_set(u8 ctl,u16 packet_cnt,u16 Threshold,u8 max_cnt);
void dac_digital_lr2one(s16 *buff,u32 len);
u32 dac_auto_mute(void);
u32 get_mute_status(void);
void dac_mute(u8 mute_flag, u8 fade_en);

void dac_amux_one_in_two_set(void *channel_on, void *channel_off);
void dac_amux_two_in_one_set(void *channel_on, void *channel_off);
#endif  //__DAC_API_H__
