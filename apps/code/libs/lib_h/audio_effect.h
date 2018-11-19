#ifndef __AUDIO_EFFECT_H__
#define __AUDIO_EFFECT_H__

#include "string.h"
#include "typedef.h"

#define  AUDIO_EF_TASK_PRIO           20


typedef enum        ///<可供选择的效果处理类型
{
    AUDIO_EFFECT_CHG_FRE =0 ,       ///<变采样
    AUDIO_EFFECT_CHL_ADD,           ///<通道叠加，audio_channle_flag相同的通道进行叠加
    AUDIO_EFFECT_AHL_CTL,           ///<声道控制  MUC_CHL_CTL
    AUDIO_EFFECT_CHG_VOL,           ///<AUDIO_EFFECT_VOL
    AUDIO_EFFECT_CHG_SPD,           ///<AUDIO_EFFECT_SPD
    AUDIO_EFFECT_CHG_EQ,            ///<AUDIO_EFFECT_EQ
    AUDIO_EFFECT_CHG_SPC,           ///<AUDIO_EFFECT_SPC
    AUDIO_EFFECT_MAX
}AUDIO_EFFECT_TYPE;

//-------order-------------------------
enum{
	EFFECT_CMD_NORMAL=0,	///<正常执行
	EFFECT_CMD_STOP,		///<停止效果
	EFFECT_CMD_CHG,			///<修改效果参数
};

//-------special mode-------------------
enum{
	EF_NON            =0x00,              ///<不做效果

	ECHO_ON            =0x05,             ///<回声
	REVERB_H_ON     =0x06,                ///<第一种混响
	REVERB_ON          =0X07,             ///<第二种混响

	RORBORT_EFFECT_ON = 0x80,             ///<机器音
	VIBRATO_EFFECT_ON = 0x90,             ///<颤音
	RADIO_EFFECT_ON = 0xa0,               ///<FM
	VOCNL_EFFECT_ON = 0xb0,               ///<人声消除
};

typedef enum
{
    MODIFY_NONE = 0,
    MODIFY_FM,                      ///<FM效果
    MODIFY_MACHINE,                 ///<机器人
    MODIFY_QUIVER,                  ///<颤音
    MODIFY_KTV,                     ///<人声消除
}MUC_SPEC_EFFCT;

typedef enum
{
    MODIFY_ECHO=0,                    ///<回声
    MODIFY_MIX,                       ///<混响
}MUC_SPEC_ECH;

//-------EQ mode-------------------
typedef enum
{
    NORMAL = 0,
    ROCK,
    POP,
    CLASSIC,
    JAZZ,
    COUNTRY,
    MAX_EQ
}ENUM_EQ_MODE;

//----music channel control----------
typedef enum
{
    MUSIC_CHANNEL_DEFAULT = 0,      ///<L=L,R=R
    MUISC_CHANNEL_ADD,              ///<L=R=L+R
    MUISC_CHANNEL_HALFADD,          ///<L=R=(L+R)/2
    MUISC_CHANNEL_SUB,              ///<L=R=(L-R)
}MUC_CHL_CTL;


typedef struct __AUDIO_EFFECT_VOL__   ///<音量处理效果包含音量调节，淡入淡出，自动mute三个部分
{
    u32 vol;                ///<音量
    u8  bfade_out_in;       ///<是否淡入淡出
    u8  bauto_mute;         ///<是否自动mute
}AUDIO_EFFECT_VOL;

typedef struct __AUDIO_EFFECT_SPD__     ///<变速变调作为一个整体处理
{
    u32 speed_parm[2];      ///<变速参数
    u32 tone_parm[2];       ///<变调参数
}AUDIO_EFFECT_SPD;

typedef struct __AUDIO_EFFECT_EQ__      ///<EQ和频谱作为一个整体处理
{
    void *eq;                   ///<EQ效果表
    void *fre;                  ///<输出频率线
}AUDIO_EFFECT_EQ;

typedef struct __AUDIO_EFFECT_SPC__     ///<特效和回声/混响一起处理
{
    MUC_SPEC_EFFCT spc_type;    ///<特效类型
    void *spc_parm;             ///<特效参数
    MUC_SPEC_ECH   ech_type;    ///<回声或者混响
    void *ech_parm;             ///<参数
}AUDIO_EFFECT_SPC;


typedef struct _AUDIO_CHL_EFFECT_ITEM_  ///<每种效果处理，包含效果类型和效果参数两部分
{
    AUDIO_EFFECT_TYPE cur_type;     ///<效果类型
    void *parm;                     ///<参数
    u32 enable;                      ///<效果使能
}AUDIO_CHL_EFFECT_ITEM;

//-----effect process---------------
typedef struct _AUDIO_CHL_EFFECT_       ///<每个解码通道需要处理的效果
{
    u32 total_ef;                   ///<一共需要处理的效果
    AUDIO_CHL_EFFECT_ITEM *parm;    ///<效果链表
}AUDIO_CHL_EFFECT;


typedef  struct   __AUDIO_DATA_INFO_
{
     u16 sr;            ///<sample rate
     u16 br;            ///<bit  rate
     u32 nch;
} AUDIO_DATA_INFO;


typedef  struct  __audio_ef_io__
{
	void *priv;
	u32 (*output)(void *priv,s16 *data, u32 len);
}audio_ef_io;



typedef struct _AUDIO_EF_OPS_
{
	u32 (*need_buf_size)();                                     //返回需要申请空间的大小
	u32 (*set_switch)(u8 *ptr,u16 switch_val);                  //设置音效开关，会返回长度，外面设置完长度之后，申请buf
	u32 (*open)(u8 *ptr,u8 *effect_buf,audio_ef_io *audio_io);  //传入前面的两片Buf，跟IO进行open
    u32 (*set_info)(u8 *ptr,AUDIO_DATA_INFO *audio_info, void *eq_parm, void  *rs_parm,void *vol_parm,void *ps_parm);  //设置音效信息
    u32 (*run)(u8 *ptr,s16 *buf,u32 len,short runType,u16 val_0,void *val_1);
	u32 (*effect_get_freq)(u8 *ptr,u32 *dest_freq);                    //获取频谱,dest_freq大小为5个u32,5段频谱

}AUDIO_EF_OPS;


#endif
