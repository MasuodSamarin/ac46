#ifndef __AUDIO_EF_H_
#define __AUDIO_EF_H_
#include "audio_ef_parm.h"
#include "audio_effect.h"
#include "sup_dec_op.h"
//#define EF_DEBUG
#ifdef EF_DEBUG
#define ef_deg             printf
#define ef_deg_puts        puts
#define ef_deg_buf         printf_buf
#define ef_deg_data        printf_data
#else
#define ef_deg(...)
#define ef_deg_puts(...)
#define ef_deg_buf(...)
#define ef_deg_data(...)
#endif

typedef enum
{
    EQ_EF = 0,                      ///<EQ
    RESAMPLE_16,             ///<16阶变采样
	RESAMPLE_8 ,             ///<8阶变采样
	RESAMPLE_Q ,             ///<快速变采样
	RESAMPLE_ON ,
    PITCH_SPEED,              ///<变速变调
	VOL,
	MAX_EF
}_EF_CLASS;

typedef struct __EF_DATA
{
    u8 vol_r;
    u8 vol_l;
    u8 eq;
    void *inf;
    void *output;
}_EF_DATA;

typedef struct __EF_INFO
{
    AUDIO_EF_OPS *ef_ops;
    u8 *ef_buff0;
	u8 *ef_buff1;
    u32 *eq_filt_table;
	ENUM_EFFECT switch_val;
	void *ef_parm[MAX_EF];
	ENUM_EFFECT_STATUS status[MAX_EF];
	AUDIO_DATA_INFO *audio_info;
	volatile tbool reset_ef;
	volatile tbool enable_ef;
	void *output;
}_EF_INFO;



extern const u16 digital_vol_tab[];

s16 ef_vol_change(_EF_INFO *ef_info,s16 vol,s16 step);


u32 ef_output(void *ptr,s16 *data,u32 len);
void *ef_input(void *priv, void *buf, u32 len);

_EF_INFO *ef_speed_info_set(_EF_INFO *ef_info,ENUM_EFFECT_STATUS status);
_EF_INFO *ef_vol_info_set(_EF_INFO *ef_info,ENUM_EFFECT_STATUS status,s16 l_vol,s16 r_vol);
_EF_INFO *ef_resample_info_set(_EF_INFO *ef_info,ENUM_EFFECT_STATUS status,u32 sr);
_EF_INFO * ef_eq_info_set(_EF_INFO *ef_info,ENUM_EFFECT_STATUS status,u32 eq_type);

_EF_INFO *ef_free(_EF_INFO *ef_info);
_EF_INFO * ef_init(_EF_INFO *ef_info,_EF_DATA *ef_data);
void ef_reset_audio_sr(_EF_INFO *ef_info,AUDIO_DATA_INFO *audio_info);
u32 ef_run(_EF_INFO *ef_info,u8*buf,u32 len);
tbool ef_enable_api(_EF_INFO **p_ef_info,_OP_IO *input,u8 enable,_EF_DATA *ef_data);

#endif

