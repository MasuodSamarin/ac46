#ifndef	_TOUCH_KEY_API_H_
#define _TOUCH_KEY_API_H_

#include "includes.h"
#include "key.h"

#if KEY_TCH_EN

#define TOUCH_KEY_CH_MAX	3//16

typedef struct _CTM_KEY_VAR
{
    s32 touch_release_buf[TOUCH_KEY_CH_MAX]; 		//�����ͷ�ֵ�˲���buffer
    u16 touch_cnt_buf[TOUCH_KEY_CH_MAX];			//��������ֵ�˲���buffer
    s16 FLT1CFG1;					//�˲���1���ò���1
    s16 FLT1CFG2;					//�˲���1���ò���2, ����(-RELEASECFG0)<<FLT1CFG0
    s16 PRESSCFG;					//�����о�����
    s16 RELEASECFG0;				//�ͷ��о�����0
    s16 RELEASECFG1;				//�ͷ��о�����1
    s8  FLT0CFG;					//�˲���0���ò���(0/1/2/3)
    s8  FLT1CFG0;					//�˲���1���ò���0
    u16 touch_key_state;			//����״̬��־����ʱ���ܱ��жϸ�д���������������Ҫ���˱�־���Ƴ������д���
    u8  touch_init_cnt[TOUCH_KEY_CH_MAX];				//��ʼ������������0ʱ���г�ʼ��
} sCTM_KEY_VAR;



tu8 get_tchkey_value(void);
void tch_key_init(void);
void scan_capkey(void);

extern u8 touchkey_short_msg;
extern u8 g_touch_len; //����������

#endif

#endif  /*  _TOUCH_KEY_API_H_   */


