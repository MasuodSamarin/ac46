/*******************************************************************************************
  File Name: dac.c

Version: 1.00

Discription:


Author:yulin deng

Email :flowingfeeze@163.com

Date:2014-01-13 17:00:21

Copyright:(c)JIELI  2011  @ , All Rights Reserved.
 *******************************************************************************************/
#include "config.h"
#include "dac.h"
#include "hwi.h"
#include "app_cfg.h"
#include "os_api.h"

//*********************************************************
//                   alnk_init
//*********************************************************
void alnk_init()
{
    INTALL_HWI(ALINK_INIT, alink_isr, 3);    //interrupt init
    IOMC0 |= BIT(6);
    PORTA_DIR &= ~(BIT(8) | BIT(12) | BIT(13) | BIT(14)); //PA10:data out, PA12:SCLK, PA13:LRCLK, PA14:MCLK
    ALNK_ADR0 = dac_buf;
    ALNK_CON0 = BIT(11) | BIT(8) | BIT(7) | BIT(4) |  BIT(1) | BIT(9);
    ALNK_CON1 = BIT(0);
    ALNK_CON2 = 0x0f | (DAC_SAMPLE_CON << 8);      //clear all pending
    printf("alink init:%08x\r\n",ALNK_CON2);
}

void alink_isr()
{
    /* puts_without_lock("iis isr\r\n"); */
    if(ALNK_CON2 & BIT(4))
    {
        ALNK_CON2 |= BIT(0);
        if(ALNK_CON0 & BIT(12))
        {
            dac_used_buf = 0 ;
        }else
        {
            dac_used_buf = 1;
        }

        if(cbuf_read(&audio_cb,dac_buf[dac_used_buf],DAC_BUF_LEN)!= DAC_BUF_LEN)
        {
            /* putbyte('s') ; */
            memset(dac_buf[dac_used_buf],0x0, DAC_BUF_LEN) ;
            os_sem_set(&audio_sem,0) ;
            os_sem_post(&audio_sem);
        }

        /* flush_dcache(dac_buf[dac_used_buf],DAC_SAMPLE_POINT); */
        if( ((audio_cb.total_len - audio_cb.data_len)>=DAC_BUF_LEN))//audio_cb.total_len/2))
        {
            /* putbyte('s') ; */
            os_sem_set(&audio_sem,0) ;
            os_sem_post(&audio_sem);
        }
    }
    DSP_CLR_ILAT = BIT(ALINK_INIT) ;
}
