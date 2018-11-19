#ifndef __AUDIO_EFFECT_H__
#define __AUDIO_EFFECT_H__

#include "string.h"
#include "typedef.h"

#define  AUDIO_EF_TASK_PRIO           20


typedef enum        ///<�ɹ�ѡ���Ч����������
{
    AUDIO_EFFECT_CHG_FRE =0 ,       ///<�����
    AUDIO_EFFECT_CHL_ADD,           ///<ͨ�����ӣ�audio_channle_flag��ͬ��ͨ�����е���
    AUDIO_EFFECT_AHL_CTL,           ///<��������  MUC_CHL_CTL
    AUDIO_EFFECT_CHG_VOL,           ///<AUDIO_EFFECT_VOL
    AUDIO_EFFECT_CHG_SPD,           ///<AUDIO_EFFECT_SPD
    AUDIO_EFFECT_CHG_EQ,            ///<AUDIO_EFFECT_EQ
    AUDIO_EFFECT_CHG_SPC,           ///<AUDIO_EFFECT_SPC
    AUDIO_EFFECT_MAX
}AUDIO_EFFECT_TYPE;

//-------order-------------------------
enum{
	EFFECT_CMD_NORMAL=0,	///<����ִ��
	EFFECT_CMD_STOP,		///<ֹͣЧ��
	EFFECT_CMD_CHG,			///<�޸�Ч������
};

//-------special mode-------------------
enum{
	EF_NON            =0x00,              ///<����Ч��

	ECHO_ON            =0x05,             ///<����
	REVERB_H_ON     =0x06,                ///<��һ�ֻ���
	REVERB_ON          =0X07,             ///<�ڶ��ֻ���

	RORBORT_EFFECT_ON = 0x80,             ///<������
	VIBRATO_EFFECT_ON = 0x90,             ///<����
	RADIO_EFFECT_ON = 0xa0,               ///<FM
	VOCNL_EFFECT_ON = 0xb0,               ///<��������
};

typedef enum
{
    MODIFY_NONE = 0,
    MODIFY_FM,                      ///<FMЧ��
    MODIFY_MACHINE,                 ///<������
    MODIFY_QUIVER,                  ///<����
    MODIFY_KTV,                     ///<��������
}MUC_SPEC_EFFCT;

typedef enum
{
    MODIFY_ECHO=0,                    ///<����
    MODIFY_MIX,                       ///<����
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


typedef struct __AUDIO_EFFECT_VOL__   ///<��������Ч�������������ڣ����뵭�����Զ�mute��������
{
    u32 vol;                ///<����
    u8  bfade_out_in;       ///<�Ƿ��뵭��
    u8  bauto_mute;         ///<�Ƿ��Զ�mute
}AUDIO_EFFECT_VOL;

typedef struct __AUDIO_EFFECT_SPD__     ///<���ٱ����Ϊһ�����崦��
{
    u32 speed_parm[2];      ///<���ٲ���
    u32 tone_parm[2];       ///<�������
}AUDIO_EFFECT_SPD;

typedef struct __AUDIO_EFFECT_EQ__      ///<EQ��Ƶ����Ϊһ�����崦��
{
    void *eq;                   ///<EQЧ����
    void *fre;                  ///<���Ƶ����
}AUDIO_EFFECT_EQ;

typedef struct __AUDIO_EFFECT_SPC__     ///<��Ч�ͻ���/����һ����
{
    MUC_SPEC_EFFCT spc_type;    ///<��Ч����
    void *spc_parm;             ///<��Ч����
    MUC_SPEC_ECH   ech_type;    ///<�������߻���
    void *ech_parm;             ///<����
}AUDIO_EFFECT_SPC;


typedef struct _AUDIO_CHL_EFFECT_ITEM_  ///<ÿ��Ч����������Ч�����ͺ�Ч������������
{
    AUDIO_EFFECT_TYPE cur_type;     ///<Ч������
    void *parm;                     ///<����
    u32 enable;                      ///<Ч��ʹ��
}AUDIO_CHL_EFFECT_ITEM;

//-----effect process---------------
typedef struct _AUDIO_CHL_EFFECT_       ///<ÿ������ͨ����Ҫ�����Ч��
{
    u32 total_ef;                   ///<һ����Ҫ�����Ч��
    AUDIO_CHL_EFFECT_ITEM *parm;    ///<Ч������
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
	u32 (*need_buf_size)();                                     //������Ҫ����ռ�Ĵ�С
	u32 (*set_switch)(u8 *ptr,u16 switch_val);                  //������Ч���أ��᷵�س��ȣ����������곤��֮������buf
	u32 (*open)(u8 *ptr,u8 *effect_buf,audio_ef_io *audio_io);  //����ǰ�����ƬBuf����IO����open
    u32 (*set_info)(u8 *ptr,AUDIO_DATA_INFO *audio_info, void *eq_parm, void  *rs_parm,void *vol_parm,void *ps_parm);  //������Ч��Ϣ
    u32 (*run)(u8 *ptr,s16 *buf,u32 len,short runType,u16 val_0,void *val_1);
	u32 (*effect_get_freq)(u8 *ptr,u32 *dest_freq);                    //��ȡƵ��,dest_freq��СΪ5��u32,5��Ƶ��

}AUDIO_EF_OPS;


#endif
