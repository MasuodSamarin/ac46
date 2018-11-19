/*******************************************************************************************
File Name: 	key_drv_tch.c

Version: 	1.00

Discription AC5100 Toutch Key API

Author:     bingquan Cai

Email:      bingquan_cai@zh-jieli.com

Date:		2013.05.09

Copyright (c) 2010 - 2012 JieLi. All Rights Reserved.
*******************************************************************************************/
#include "key_drv_tch.h"
#include "includes.h"
#include "key.h"
#include "ac46.h"

#if KEY_TCH_EN

u8 g_touch_len;        //����������
u8 touchkey_short_msg; //���������̰���Ϣλ��
u8  bCapState;          //���ݳ�ŵ�״̬
u8  bCap_ch;            //����ͨ��
u16 Touchkey_value_old,Touchkey_value_new;
sCTM_KEY_VAR ctm_key_value;
u8 touchkey_msg_table[4][10];

#define PA811 0
#define PB811 1

#define TOUCH_IO PA811

sCTM_KEY_VAR *ctm_key_var;


void ctm_key_var_init(sCTM_KEY_VAR *ptr)
{
	ctm_key_var = ptr;
}


static void ctm_irq(u16 ctm_res, u8 ch)
{
    u16 temp_u16_0, temp_u16_1;
    s16 temp_s16_0, temp_s16_1;
    s32 temp_s32_0;
//..............................................................................................
//ȡ����ֵ/ͨ���ж�
//..............................................................................................


    if(ctm_key_var->touch_init_cnt[ch])
    {
        ctm_key_var->touch_init_cnt[ch]--;
//		touch_cnt_buf[ch] = rvalue << FLT0CFG;
//		touch_release_buf[ch] = (long)(rvalue) << FLT1CFG0;
        ctm_key_var->touch_cnt_buf[ch] = (u32)ctm_res<<ctm_key_var->FLT0CFG;
        ctm_key_var->touch_release_buf[ch] = (u32)ctm_res<<ctm_key_var->FLT1CFG0;
    }

//..............................................................................................
//��ǰ����ֵȥ�����˲���
//..............................................................................................
    temp_u16_0 = ctm_key_var->touch_cnt_buf[ch];
    temp_u16_1 = temp_u16_0;
    temp_u16_1 -= (temp_u16_1 >> ctm_key_var->FLT0CFG);
    temp_u16_1 += ctm_res;//temp_u16_1 += rvalue;
    ctm_key_var->touch_cnt_buf[ch] = temp_u16_1;
    temp_u16_0 += temp_u16_1;
    temp_u16_0 >>= (ctm_key_var->FLT0CFG + 1);


//..............................................................................................
//��ͨ�������ͷż���ֵ�˲���
//..............................................................................................
    temp_s32_0 = ctm_key_var->touch_release_buf[ch];
    temp_u16_1 = temp_s32_0 >> ctm_key_var->FLT1CFG0;	//����˲���֮��İ����ͷ�ֵ
    temp_s16_0 = temp_u16_0 - temp_u16_1;	//��úͱ��μ��ֵ�Ĳ�ֵ�����°���Ϊ��ֵ���ͷŰ���Ϊ��ֵ
    temp_s16_1 = temp_s16_0;

//    	if(ch == 0)
//    	{
//    		printf("ch%d: %d  %d", (short)ch, temp_u16_0, temp_s16_1);
//    	}

    if(ctm_key_var->touch_key_state & BIT(ch))		//�����ͨ������Ŀǰ�Ǵ����ͷ�״̬
    {
        if(temp_s16_1 >= 0)		//��ǰ����ֵ���ڵ�ֵͨ���Ŵ���������
        {
            if(temp_s16_1 < (ctm_key_var->FLT1CFG2 >> 3))
            {
                temp_s16_1 <<= 3;	//�Ŵ���������
            }
            else
            {
                temp_s16_1 = ctm_key_var->FLT1CFG2;	//���ͣ���ֹĳЩ�ϴ����ƫ��´���
            }
        }
        else if(temp_s16_1 >= ctm_key_var->FLT1CFG1)	//��ǰ����ֵС�ڵ�ֵͨ���࣬������������
        {
        }
        else				//��ǰ����ֵС�ڵ�ֵͨ�ܶ࣬��С��������� (�з����������Զ���չ����λ???)
        {
            temp_s16_1 >>= 3;
        }
    }
    else			//�����ͨ������Ŀǰ�Ǵ��ڰ���״̬, ���������ͷż���ֵ
    {
        if(temp_s16_1 <= ctm_key_var->RELEASECFG1)
        {
            temp_s16_1 >>= 3;		//��С���������
        }
        else
        {
            temp_s16_1 = 0;
        }
    }

    temp_s32_0 += (s32)temp_s16_1;
    ctm_key_var->touch_release_buf[ch] = temp_s32_0;

//..............................................................................................
//�����������ͷż��
//..............................................................................................
    if(temp_s16_0 <= ctm_key_var->PRESSCFG)				//��������
    {
        ctm_key_var->touch_key_state &= ~BIT(ch);
    }
    else if(temp_s16_0 >= ctm_key_var->RELEASECFG0)		//�����ͷ�
    {
        ctm_key_var->touch_key_state |= BIT(ch);
    }
}


tu8 get_tchkey_value(void)
{
    u8 key;
    u8 i;

    for (i = 0; i < g_touch_len; i++)
    {
        if (!(ctm_key_value.touch_key_state & (u8)(BIT(i))))
            break;
    }
    key = (i < g_touch_len) ? i : NO_KEY;

//    if(key != NO_KEY)
//        printf("tch %x\n", key);
//    else
//        puts("\n");

    return key;
}



void set_port_out(u8 chan)
{
    switch(chan)
    {
#if (TOUCH_IO == PA811)
        case 0:
            PORTA_DIR &= ~BIT(8);
            break;
        case 1:
            PORTA_DIR &= ~BIT(9);
            break;
        case 2:
            PORTA_DIR &= ~BIT(10);
            break;
        case 3:
            PORTA_DIR &= ~BIT(11);
            break;
#else
        case 0:
            PORTB_DIR &= ~BIT(8);
            break;
        case 1:
            PORTB_DIR &= ~BIT(9);
            break;
        case 2:
            PORTB_DIR &= ~BIT(10);
            break;
        case 3:
            PORTB_DIR &= ~BIT(11);
            break;
#endif
    }
}

void set_port_out_H(u8 chan)
{
    switch(chan)
    {
#if (TOUCH_IO == PA811)
        case 0:
            PORTA_OUT |= BIT(8);
            break;
        case 1:
            PORTA_OUT |= BIT(9);
            break;
        case 2:
            PORTA_OUT |= BIT(10);
            break;
        case 3:
            PORTA_OUT |= BIT(11);
            break;
#else
        case 0:
            PORTB_OUT |= BIT(8);
            break;
        case 1:
            PORTB_OUT |= BIT(9);
            break;
        case 2:
            PORTB_OUT |= BIT(10);
            break;
        case 3:
            PORTB_OUT |= BIT(11);
            break;
#endif
    }
}

void set_port_pd(u8 chan)
{
    switch(chan)
    {
#if (TOUCH_IO == PA811)
        case 0:
            PORTA_PD |= BIT(8);
            break;
        case 1:
            PORTA_PD |= BIT(9);
            break;
        case 2:
            PORTA_PD |= BIT(10);
            break;
        case 3:
            PORTA_PD |= BIT(11);
            break;
#else
        case 0:
            PORTB_PD |= BIT(8);
            break;
        case 1:
            PORTB_PD |= BIT(9);
            break;
        case 2:
            PORTB_PD |= BIT(10);
            break;
        case 3:
            PORTB_PD |= BIT(11);
            break;
#endif
    }
}

void set_port_in(u8 chan)
{
    switch(chan)
    {
#if (TOUCH_IO == PA811)
        case 0:
            PORTA_DIR |= BIT(8);
            break;
        case 1:
            PORTA_DIR |= BIT(9);
            break;
        case 2:
            PORTA_DIR |= BIT(10);
            break;
        case 3:
            PORTA_DIR |= BIT(11);
            break;
#else
        case 0:
            PORTB_DIR |= BIT(8);
            break;
        case 1:
            PORTB_DIR |= BIT(9);
            break;
        case 2:
            PORTB_DIR |= BIT(10);
            break;
        case 3:
            PORTB_DIR |= BIT(11);
            break;
#endif
    }
}

u8 g_touch_port(u8 chan)
{
#if (TOUCH_IO == PA811)
    u8 first_chan = 9 -1;
    return (first_chan + chan);
#else
    u8 first_chan = 25 -1;
    return (first_chan + chan);
#endif
}

void set_touch_io(u8 chan_id)
{
    IOMC2 &= ~(0xff0000);
    IOMC2 |= g_touch_port(chan_id)<< 16;    ///ѡ���ɣ�
    set_port_in(chan_id);///����Ϊ����
}


void scan_capkey(void)
{
    u16 temp;
    u16 Touchkey_value_delta;

    if(0 == g_touch_len)
    {
        return;
    }

    if (bCapState == 0)
    {
      	bCapState = 1;
        Touchkey_value_new = PLCNTVL;   ///��ȡ����ֵ

//        if(Touchkey_value_old> Touchkey_value_new)
//            Touchkey_value_new += 0x10000;

        Touchkey_value_delta = Touchkey_value_new - Touchkey_value_old;

//        if(bCap_ch == 0)
//        {
//            printf("\n old: %x   new: %x", Touchkey_value_old, Touchkey_value_new );
//            if(Touchkey_value_delta > 0x100)
//                printf("value: %x\n", Touchkey_value_delta);
//        }

        Touchkey_value_old = Touchkey_value_new;	///��¼��ֵ
        temp = 6800L - Touchkey_value_delta*1;      ///1�仯������

//        printf("\nTouchkey_value_delta: %d  ch: %d", Touchkey_value_delta, bCap_ch);puts("\n");
//        if(bCap_ch == 0)
//        {
//             printf("temp: %d\n", Touchkey_value_delta);//puts("\n");
//        }


        /*�����˲��㷨*/
        ctm_irq(temp, bCap_ch);


        /*���ǰһ��ͨ��״̬������PLL CNT*/
        set_port_out(bCap_ch);

        /*�л�ͨ������ʼ��磬PLL CNT ����Mux �л�*/
        bCap_ch++;
        bCap_ch %= g_touch_len;
        //bCap_ch = (bCap_ch >= g_touch_len) ? 0 : bCap_ch;

        set_port_out_H(bCap_ch);
        set_port_out(bCap_ch);
    }
    else
    {
    	bCapState = 0;
    	set_touch_io(bCap_ch);
    }
}



void tch_key_init(void)
{
    u8 i;

	ctm_key_var_init(&ctm_key_value);

  	my_memset((u8 *)&ctm_key_value, 0x0, sizeof(sCTM_KEY_VAR));
    /*����������������*/
    ctm_key_value.FLT0CFG = 0;
    ctm_key_value.FLT1CFG0 = 7;
    ctm_key_value.FLT1CFG1 = -80;
    ctm_key_value.FLT1CFG2 = (-(-10)) << 7; //1280

    ///���������ȵ���Ҫ����
    ctm_key_value.PRESSCFG = -70;
    ctm_key_value.RELEASECFG0 = -50;
    ctm_key_value.RELEASECFG1 = -80;//-81;

    my_memset((u8 *)&(ctm_key_value.touch_init_cnt[0]), 0x10, TOUCH_KEY_CH_MAX);

    ctm_key_value.touch_key_state = 0xffff; //<����Ĭ���ͷ�

  	///��ʼ�����������ã�
  	PLCNTCON &= ~(0xc);	//
  	PLCNTCON |= BIT(2);	//ѡ��PLL 96Mʱ�Ӽ���
    PLCNTCON |= BIT(1);	//ʹ��ʹ�ܼ�����

    g_touch_len = TOUCH_KEY_CH_MAX;

    bCapState = 1;
    Touchkey_value_old = PLCNTVL;   ///��ȡ����ֵ
    set_port_out_H(bCap_ch);
    set_port_out(bCap_ch);

#if 1       //����ⲿ���������裬�ɲ�����оƬ�ڲ�����
    for (i = 0; i < g_touch_len; i++)
    {
        set_port_pd(i);
    }
#endif

    puts("touch_key_init \n");
}

#endif
