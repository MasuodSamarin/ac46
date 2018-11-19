#ifndef _AUDIO_EF_PARM_H
#define _AUDIO_EF_PARM_H

typedef enum
{
    EF_EQ =0x0001,                      ///<EQ
    EF_RESAMPLE_16 =0x0002,             ///<16阶变采样
	EF_RESAMPLE_8  =0x0004,             ///<8阶变采样
	EF_RESAMPLE_Q  =0x0008,             ///<快速变采样
	EF_RESAMPLE_ON =0x0010,
    EF_PITCH_SPEED =0x0020,              ///<变速变调
	EF_VOL =0x0040
}ENUM_EFFECT;

typedef enum
{
	EF_NORMAL =0x01,
	EF_CHANGE_COEF,
	EF_DISABLE,
	EF_ENABLE,
	EF_FREE,
	EF_INIT = 0x20,
}ENUM_EFFECT_STATUS;


typedef enum                           ///<传参错误
{
	EF_ERR_EQ = 0x0011,
	EF_ERR_RESAMPLE_16,
	EF_ERR_RESAMPLE_8,
	EF_ERR_RESAMPLE_Q,
	EF_ERR_PITCH_SPEED,
	EF_ERR_VOL
}ENUM_EFFECT_ERR;

typedef struct _AD_VOL_PARM_
{
	short cur_vol[2];
	short energy_dectect;
	short LowPass_Coef;
	short auto_mute;                ///<自动mute开启位
	int energy_threshold;           ///<自动mute阀值
}AD_VOL_PARM;

typedef struct _AD_RESAMPLE_PARM_
{
	unsigned short des_sample_rate;        ///目标采样率
}AD_RESAMPLE_PARM;

typedef struct _AD_CH_ADD_PARM_
{
	short kind;           /// 0：L=L,R=R; 1.L=R=L+R; 2.L=R=(L+R)/2; 3.L=R=(L-R)
}AD_CH_ADD_PARM;

typedef struct _AD_CH_MIX_UNIT_
{
    unsigned int ef_chl;
    unsigned int ef_list;
    unsigned int vol_val;
}AD_CH_MIX_UNIT;

typedef struct _AD_CH_MIX_PARM_
{
    short nch;
    AD_CH_MIX_UNIT  chmix_val[5];
}AD_CH_MIX_PARM;

typedef struct _AD_SPEED_PARM_
{
    unsigned short  speed_val;    ///60-120
    unsigned short  pitch_val;
    unsigned short  pitch_on;     //变调开关
}AD_SPEED_PARM;


typedef struct  _AD_EQ_PARM_
{
    unsigned int filt_tab[3];
	short  filt_cnt;
    short  EQ_type;
    short  global_gain;
	char EQtab_v[5];
}AD_EQ_PARM;

typedef  struct  _AD_SPECIAL_EF_PARM_
{
    short  effect_switch;
    short  parm[6];
}AD_SPECIAL_EF_PARM;


#endif
