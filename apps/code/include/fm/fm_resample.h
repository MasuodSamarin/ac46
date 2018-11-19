#ifndef __BT15_FM_RESAMPLE_H__
#define __BT15_FM_RESAMPLE_H__

#include "includes.h"

#define  DEST_32K   9600        //32K
#define  DEST_44K   13230       //44.1K
#define  DEST_48K   14400       //48K
#define  FM_SR      12500       //41.666..K

#define  FM_SAMPLE_UP     DEST_48K
#define  FM_SAMPLE_DOWN   DEST_32K

#define  FM_RSAMPLE_RUN_OK      0
#define  FM_RSAMPLE_RUN_ERR     1

typedef struct _FM_RS_IO_
{
    void   *priv;
    void   (*output_data)(void *priv,char *buf, short len);
} FM_RS_IO;

typedef struct __FM_resample_conext
{
    u32 (*need_buf)();                                     //��ȡ��Ҫ�Ŀռ��С�����ⲿ���ٴ���
    void (*open)(s8 *ptr,FM_RS_IO *fm_io);         //������������ӿ�
    u32 (*set_config)(s8 *ptr ,u32 new_insample,u32 new_outsample,s16 nch); //���ò�����������Ϣ
    u32 (*run)(u8 *ptr,s8 *inbuf,u16 len);                                //���У���������0������������1
} FM_resample_conext;

typedef struct __FM_RS_USE
{
    FM_resample_conext *frc;       //���������ָ��ṹ��
    FM_RS_IO *fm_testIO;           //�������IO�ṹ�壬open�����free��������ʵ���Բ�Ҫ���������Ծֲ�
    s8 *tmpbuf;                   //�������Ҫ��buf�ṹ��
} FM_RS_USE;

extern FM_resample_conext * get_fmRS_ops();

#endif
