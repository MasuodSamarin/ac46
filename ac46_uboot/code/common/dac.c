/*******************************************************************************************
  File Name: dac.c

Version: 1.00

Discription:


Author:yulin deng

Email :flowingfeeze@163.com

Date:2014-01-13 17:00:21

Copyright:(c)JIELI  2011  @ , All Rights Reserved.
 *******************************************************************************************/
#include "dac.h"
#include "hwi.h"
#include "dac_api.h"
#include "key_voice.h"
#include "circular_buf.h"

#define OUTPUT_BUF_SIZE  576*2*2*3  //1024*6//
#define SFR(sfr, start, len, dat) (sfr = (sfr & ~((~(0xffffffff << (len))) << (start))) | (((dat) & (~(0xffffffff << (len)))) << (start)))
static u32 dac_buf[2][DAC_SAMPLE_POINT] AT(.dac_buf_sec);//__attribute__((aligned(4)));
cbuffer_t audio_cb ;
u8 dac_read_en;
const u16 digital_vol_tab[]=
{
    0	  ,
    93	  ,
    111	  ,
    132	  ,
    158	  ,
    189	  ,
    226	  ,
    270	  ,
    323	  ,
    386	  ,//9
    462	  ,
    552	  ,
    660	  ,
    789	  ,
    943	  ,
    1127  ,
    1347  ,
    1610  ,
    1925  ,
    2301  ,//19
    2751  ,
    3288  ,
    3930  ,
    4698  ,
    5616  ,
    6713  ,
    8025  ,
    9592  ,
    11466 ,
    15200 ,//29
    16000 ,
    16384
};
void dac_reg_init()
{
    dac_read_en = 0;
    memset(dac_buf,0x00, sizeof(dac_buf)) ;
    PLL_CON |= BIT(9);
    DAC_ADR = (u32)dac_buf;

    adda_analog_init();
}

void clear_dac_dma_buf(void)
{
    memset(dac_buf,0x00, sizeof(dac_buf)) ;
}
u8 outbuf[OUTPUT_BUF_SIZE];
void dac_buf_init()
{
    u8 err ;
    u8 *outbuf;
	//err = os_sem_create(&audio_sem,0) ;
//	if(err != OS_NO_ERR)
//	{
//		puts("create dac mut err \r\n") ;
//		return ;
//	}
//	outbuf = malloc(OUTPUT_BUF_SIZE);
//	if (outbuf == 0) {
//		puts("out buf malloc err\r\n");
//	}

	cbuf_init(&audio_cb, outbuf, OUTPUT_BUF_SIZE) ;
}

void dac_set_samplerate(u16 rate,tbool wait)
{
    u8 sr=0 ;
    switch(rate)
    {
        case 44100:
            sr = 0 ;
            break ;
        case 48000:
            sr = 1 ;
            break ;
        case 32000:
            sr = 2 ;
            break ;

        case 22050:
            sr = 4 ;
            break ;
        case 24000:
            sr = 5 ;
            break ;
        case 16000:
            sr = 6 ;
            break ;

        case 11025:
            sr = 8 ;
            break ;
        case 12000:
            sr = 9 ;
            break ;
        case 8000:
            sr = 0x0a ;
            break ;

    }
    key_voice.dac_rate = rate;
    DAC_SR(sr) ;
}


void dac_write(u8 *buf ,u32 len)
{
    u8 err ;
    u32 wlen;
    //return ;
    while(1)
    {
        wlen = cbuf_write(&audio_cb,buf,len);
        len -= wlen;
        if (len == 0) break;
        buf += wlen;
        /* putchar('-') ; */
//        err = os_sem_pend(&audio_sem,0) ;
        /* putchar('*') ; */
//        if(err != OS_NO_ERR)
//        {
//
//        }
    }
}

void cbuf_write_dac(s16 * buf,u32 len)
{
    cbuf_write(&audio_cb,buf,len);
}

void dac_isr()
{
    u8 dac_used_buf;
    if(DAC_CON & BIT(7))
    {
        DAC_CON |= BIT(6);
        if(DAC_CON & (BIT(8)))
        {
            dac_used_buf = 0 ;
        }
        else
        {
            dac_used_buf = 1;
        }
		if (!dac_read_en){
			if (cbuf_get_data_size(&audio_cb) < OUTPUT_BUF_SIZE/2){
				memset(dac_buf[dac_used_buf], 0x00, DAC_BUF_LEN) ;
                add_key_voice((s16 *)dac_buf[dac_used_buf],DAC_SAMPLE_POINT*2);
				return;
			}
			dac_read_en = 1;
		}
		if(cbuf_read(&audio_cb, dac_buf[dac_used_buf], DAC_BUF_LEN)!= DAC_BUF_LEN)
		{
			dac_read_en = 0;
			memset(dac_buf[dac_used_buf], 0x00, DAC_BUF_LEN) ;
		}
        add_key_voice((s16 *)dac_buf[dac_used_buf],DAC_SAMPLE_POINT*2);

        if(dac_digt_ctl.lr2one) /*L_R_2_ONE*/
        {
            dac_digital_lr2one((s16 *)dac_buf[dac_used_buf],DAC_SAMPLE_POINT*2);
        }

		if( ((audio_cb.total_len - audio_cb.data_len)>=DAC_BUF_LEN ))
		{
			/* putbyte('s') ; */
			//os_sem_set(&audio_sem,0) ;
			//os_sem_post(&audio_sem);
		}
    }

}

int dac_get_inbuf_len(void *priv)
{
    return audio_cb.data_len;
}

int dac_get_inbuf_totlen(void *priv)
{
    return audio_cb.total_len;
}


/*----------------------------------------------------------------------------*/
/** @brief: 初始化LDO等消息
    @param:
    @return:
    @author:
    @note:
*/
/*----------------------------------------------------------------------------*/
void dac_on_init(void)
{
	DAC_CON = 0;

	SFR(DAA_CON0,  7,  1,  1); //MUTE

#ifdef DAC_VDD_EN
    dac_on(0,1);
#else
 #ifdef VCOMO_EN
    dac_on(1,0);
 #else
    dac_on(0,0);
 #endif  /*  VCOMO_EN    */
#endif  /*  DAC_VDD_EN  */

}

void audio_isr(void)
{
    dac_isr();
    DSP_CLR_ILAT = BIT(DAC_INIT) ;
}
REG_INIT_HANDLE(audio_isr);
void audio_init(void)
{
    dac_on_init();
    digit_auto_mute_set(-1,0,0,0);
    key_voice_init();

    dac_buf_init();
    dac_reg_init();

    //dac_trim_init((void*)dac_buf);//dac trim

    INTALL_HWI(DAC_INIT,audio_isr,3) ;

    SFR(DAA_CON0,  7,  1,  0); //MUTE

    memset(dac_buf,0x00, sizeof(dac_buf)) ;
    DAC_CON = 0;
    DAC_CON = 0xe030 | (DAC_SAMPLE_CON << 10) ;

    set_max_analog_vol(MAX_SYS_VOL_L,MAX_SYS_VOL_R);
    dac_digt_ctl.lr2one = 1;
    dac_var.cur_sys_vol_l = 30;
    dac_var.cur_sys_vol_r = dac_var.cur_sys_vol_l;
}

void audio_set(void)
{
    ENABLE_INT();
    dac_set_samplerate(8000,0);
    dac_channel_on(MUSIC_CHANNEL, FADE_OFF);
    set_sys_vol(30, 30, FADE_OFF);
}

bool is_auto_mute()
{
    return dac_var.d_auto_mute.bAutoMute;
}
