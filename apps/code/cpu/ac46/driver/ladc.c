#include "includes.h"
#include "circular_buf.h"
#include "dac.h"
#include "ladc.h"
#include "mango_dev_usb_slave.h"
#include "task_manage.h"

extern void fill_adc_ref_buf(s16 *buf,u16 len);
volatile LADC_CTL *p_ladc = NULL;
static cbuffer_t adc_cb ;
s16 ladc_buf[2*4][DAC_SAMPLE_POINT] __attribute__((aligned(4)));
extern volatile u32 dac_energy_value;
void ladc_buf_init(void)
{
    u8 *outbuf;
    outbuf = malloc(1024);
	if (outbuf == 0) {
		puts("out buf malloc err\r\n");
	}

	cbuf_init(&adc_cb, outbuf, 512) ;
}


//adc通道设置
//通道为DAC_CHANNEL，必须先设置dac_channel_on()选择通道
void ladc_reg_init(u8 ch_sel, u8 sr)
{
    u16 ch_cnt;
    //CLK_CON2 |= BIT(7);//|BIT(6);
    CLK_CON1 &= ~(BIT(7));
    //line in的能量分析也要用到这个函数初始化，当line in使用其他输入时记得区分修改
    //注意：ladc通道输入源只支持PC15,PC12,PC13和DAC的左右声道。详细情况AC46的用户手册
    #if !defined(ZY_5015_SG_AC4602)&&!defined(KOK_DETECT_USE_PC15)
    PORTC_DIE &=~BIT(15);
    PORTC_DIR |= BIT(15);
    PORTC_PD &=~BIT(15);
    PORTC_PU &=~BIT(15);
    #endif
    LADC_CON = 0;
    LADC_CON1 = 0;
    LADC_CON2 = 0;

    LADC_CON  |= BIT(15)|BIT(14)|BIT(13)|BIT(12);//DCCS3~DCCS0   去直流滤波


    if(ch_sel == ENC_MIC_CHANNEL)
    {
        LADC_CON2 |= LADC_CH_MIC << LADC_CH0_BIT; //0通道 来源mic(PC15)

        MIC_GAIN(10);
        MIC_EN(1);
        ch_cnt = LADC_ONE_CH;
    }
    else if(ch_sel == ENC_DAC_CHANNEL)
    {
        LADC_CON2 |= LADC_CH_DACL << LADC_CH0_BIT; //通道0  来源DACL
        LADC_CON2 |= LADC_CH_DACR << LADC_CH1_BIT; //通道1  来源DACL

        if(dac_var.channel_mode == DAC_AMUX0)
        {
            LIN0L_BIAS_EN(1);
            LIN0R_BIAS_EN(1);
        }
        else if(dac_var.channel_mode == DAC_AMUX1)
        {
            LIN1L_BIAS_EN(1);
            LIN1R_BIAS_EN(1);
        }
        else if(dac_var.channel_mode == DAC_AMUX2)
        {
            LIN2L_BIAS_EN(1);
            LIN2R_BIAS_EN(1);
        }

        AMUX_BIAS_EN(1);
        ADC_BUF_GAIN(3);
        ADC_BUF_BP(1);
        ADC_BUF_EN(1);

        ch_cnt = LADC_TWO_CH;
    }
    else    //USER_CHANNEL
    {
        puts("USER_CHANNEL\n");
    }

    LADC_CON1 |= LADC_ANALOG_RESET | LADC_ANALOG_ELE(0) | LADC_ANALOG_EN | LADC_CLK(7);
    LADC_CON  |= sr | BIT(5) | BIT(6) | ch_cnt;

    //DAA_CON0 |= BIT(3);
    DAA_CON2 |= BIT(9);

    my_memset(ladc_buf[0], 0x00, sizeof(ladc_buf));
    LADC_ADR  = (u32)ladc_buf;

    LADC_CON |= BIT(4);

}

void disable_ladc(u8 ch_sel)//ADC_channel
{
    LADC_CON = 0;
    LADC_CON1 = 0;
    LADC_CON2 = 0;
    if(ch_sel == ENC_MIC_CHANNEL)
    {
        MIC_GAIN(0);
        MIC_EN(0);
    }
    else if(ch_sel == ENC_DAC_CHANNEL)
    {
        if(dac_var.channel_mode == DAC_AMUX0)       //DAC_channel
        {
            LIN0L_BIAS_EN(0);
            LIN0R_BIAS_EN(0);
        }
        else if(dac_var.channel_mode == DAC_AMUX1)  //DAC_channel
        {
            LIN1L_BIAS_EN(0);
            LIN1R_BIAS_EN(0);
        }
        else if(dac_var.channel_mode == DAC_AMUX2)  //DAC_channel
        {
            LIN2L_BIAS_EN(0);
            LIN2R_BIAS_EN(0);
        }

        AMUX_BIAS_EN(0);
        ADC_BUF_BP(0);
        ADC_BUF_EN(0);
    }
    else
    {
        puts("USER_CHANNEL\n");
    }
}


void cbuf_read_adc(s16 * buf,u32 len)
{
    cbuf_read(&adc_cb,buf,len);
}

void ladc_isr(void)
{
    u32 *res;
    u8 ch_cnt, i;

    if( (LADC_CON&BIT(7)) && (LADC_CON&BIT(5)) )
    {
        LADC_CON |= BIT(6);
        ///*********录音用***************///
        if(NULL != p_ladc)
        {
            if((p_ladc->source_chl == ENC_MIC_CHANNEL)
            ||(p_ladc->source_chl == ENC_DAC_CHANNEL))
            {
                ch_cnt = (LADC_CON & (BIT(10) |BIT(11))) >> 10;
                if((LADC_CON & BIT(8)))//DUAL BUFF
                {
                    for(i = 0; i <= ch_cnt; i++) //rec_ctl
                    {
                        if(p_ladc->save_ladc_buf)
                        {
                            p_ladc->save_ladc_buf((void *)p_ladc, &ladc_buf[i*2][0], i,DAC_DUAL_BUF_LEN);
                        }
                    }
                }
                else
                {
                    for(i = 0;i <= ch_cnt;i++)
                    {
                        if(p_ladc->save_ladc_buf)
                        {
                            p_ladc->save_ladc_buf((void *)p_ladc, &ladc_buf[i*2+1][0], i,DAC_DUAL_BUF_LEN);
                        }
                    }
                }
            }
        }

        ///*********蓝牙用***************///
        if(curr_task)
        {
            if(LADC_CON & BIT(8))
                res = (u32 *)&ladc_buf[0][0];
            else
                res = (u32 *)&ladc_buf[1][0];
#if USB_PC_EN
            ///for usb mic
            usb_mic_ladc_input((s16 *)res, DAC_SAMPLE_POINT);
#endif

            dac_energy_value = dac_digit_energy_value((s16 *)res,DAC_SAMPLE_POINT);

            if(!strcmp(curr_task->name,"BtStackTask"))
            {
#ifdef BT_TESTER
                a2dp_send_media_get_adc_to_sbc_encoder(res, 2 * DAC_SAMPLE_POINT);
#else
                fill_adc_ref_buf((s16 *)res,32*sizeof(short));  //回声消除
                //cbuf_write(&adc_cb,(u8 *)res,64*sizeof(short));
#endif
            }
        }
    }
}
