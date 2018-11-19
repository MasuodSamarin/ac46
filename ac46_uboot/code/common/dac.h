/*******************************************************************************************
 File Name: dac.h

 Version: 1.00

 Discription:


 Author:yulin deng

 Email :flowingfeeze@163.com

 Date:2014-01-13 17:09:41

 Copyright:(c)JIELI  2011  @ , All Rights Reserved.
*******************************************************************************************/
#ifndef dac_h
#define dac_h
#include "circular_buf.h"
#include "dac_api.h"

/*------------------------------------------------------------------

    ------------DAC 配置选项 - 2----------------

    DACVDD_VCOMO选择，DAC_VDD和VCOMO是同一PIN，
    同时只能选择其中一种功能，也可以两种都不选(DAC_VDD悬空)
-------------------------------------------------------------------*/
#define DAC_VDD_EN                      //DAC_VDD外接电容，SNR可以提高1.5dB

//是否选择VCMO直推耳机
#ifndef DAC_VDD_EN
#define VCOMO_EN
#endif

/*------------------------------------------------------------------

    ------------DAC 配置选项 - 4----------------

    数字通道发声时调节音量控制
        ——DECODER_ANALOG_MAX ： 此时调节数字音量，模拟音量为最大
        ——DECODER_DIGITAL_MAX ： 此时调节模拟音量，数字音量为最大
-------------------------------------------------------------------*/
#define DECODER_ANALOG_MAX  0
#define DECODER_DIGITAL_MAX BIT(7)

/*---DAC_CON sfr Setting----*/
/* #define DAC_SR(x)           DAC_CON = ((DAC_CON & ~(BIT(0)|BIT(1)|BIT(2)|BIT(3))) | (x & 0xf)) */
#define DAC_SR(x)           DAC_CON = ((DAC_CON & ~(BIT(0)|BIT(1)|BIT(2)|BIT(3))) | (x & 0xf))
#define DAC_DIGITAL_EN(x)   DAC_CON = ((DAC_CON & ~BIT(4)) | ((x & 0x1)<<4))
#define DAC_IE(x)           DAC_CON = ((DAC_CON & ~BIT(5)) | ((x & 0x1)<<5))
#define DAC_CPND(x)         DAC_CON |= BIT(6)
#define DAC_DCCS(x)         DAC_CON = ((DAC_CON & ~(BIT(12)|BIT(13)|BIT(14)|BIT(15))) | ((x & 0xf)<<12))

/*---LADC_CON sfr Setting----*/
#define LADC_SR(x)          LADC_CON = ((LADC_CON & ~(BIT(0)|BIT(1)|BIT(2)|BIT(3))) | (x & 0xf))
#define LADC_DIGITAL_EN(x)  LADC_CON = ((LADC_CON & ~BIT(4)) | ((x & 0x1)<<4))
#define LADC_IE(x)          LADC_CON = ((LADC_CON & ~BIT(5)) | ((x & 0x1)<<5))
#define LADC_CPND(x)        LADC_CON |= BIT(6)
#define LADC_DCCS(x)        LADC_CON = ((LADC_CON & ~(BIT(12)|BIT(13)|BIT(14)|BIT(15))) | ((x & 0xf)<<12))

#define LADC_EXS(x)         LADC_CON = ((LADC_CON & ~(BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4))) | (x & 0x1f))
#define LADC_CLK_DIV(x)     LADC_CON = ((LADC_CON & ~(BIT(5)|BIT(6)|BIT(7))) | ((x & 0x7)<<5))
#define LADC_OVER_SAPMLE(x) LADC_CON = ((LADC_CON & ~BIT(8)) | ((x & 0x1)<<8))
#define LADC_M10BIT(x)      LADC_CON = ((LADC_CON & ~BIT(9)) | ((x & 0x1)<<9))
#define LADC_EN(x)          LADC_CON = ((LADC_CON & ~BIT(10)) | ((x & 0x1)<<10))
#define LADC_RESET(x)       LADC_CON = ((LADC_CON & ~BIT(11)) | ((x & 0x1)<<11))
#define LADC_CHANNEL_SEL(x) LADC_CON = ((LADC_CON & ~(BIT(12)|BIT(13))) | ((x & 0x3)<<12))

/*---MADC_CON sfr Setting----*/
#define MADC_SR(x)          MADC_CON = ((MADC_CON & ~(BIT(0)|BIT(1)|BIT(2)|BIT(3))) | (x & 0xf))
#define MADC_DIGITAL_EN(x)  MADC_CON = ((MADC_CON & ~BIT(4)) | ((x & 0x1)<<4))
#define MADC_IE(x)          MADC_CON = ((MADC_CON & ~BIT(5)) | ((x & 0x1)<<5))
#define MADC_CPND(x)        MADC_CON |= BIT(6)
#define MADC_DCCS(x)        MADC_CON = ((MADC_CON & ~(BIT(12)|BIT(13)|BIT(14)|BIT(15))) | ((x & 0xf)<<12))


/*---DAA_CON0 sfr Setting----*/
#define DAC_ANALOG_EN(x)    DAA_CON0 = ((DAA_CON0 & ~BIT(0)) | (x & 0x1))
#define LDO1_EN(x)          DAA_CON0 = ((DAA_CON0 & ~BIT(2)) | ((x & 0x1)<<2))
#define LDO2_EN(x)          DAA_CON0 = ((DAA_CON0 & ~BIT(3)) | ((x & 0x1)<<3))
#define HP_L_EN(x)          DAA_CON0 = ((DAA_CON0 & ~BIT(4)) | ((x & 0x1)<<4))
#define HP_R_EN(x)          DAA_CON0 = ((DAA_CON0 & ~BIT(5)) | ((x & 0x1)<<5))
#define PNS_EN(x)           DAA_CON0 = ((DAA_CON0 & ~BIT(6)) | ((x & 0x1)<<6))
#define MUTE_EN(x)          DAA_CON0 = ((DAA_CON0 & ~BIT(7)) | ((x & 0x1)<<7))

#define ADC_BUF_GAIN(x)     DAA_CON0 = ((DAA_CON0 & ~(BIT(8)|BIT(9)|BIT(10))) | ((x & 0x7)<<8))
#define ADC_BUF_BP(x)       DAA_CON0 = ((DAA_CON0 & ~BIT(11)) | ((x & 0x1)<<11))
#define ADC_BUF_EN(x)       DAA_CON0 = ((DAA_CON0 & ~BIT(12)) | ((x & 0x1)<<12))
#define TRIM_EN(x)          DAA_CON0 = ((DAA_CON0 & ~BIT(13)) | ((x & 0x1)<<13))
#define TRIM_SEL(x)         DAA_CON0 = ((DAA_CON0 & ~BIT(14)) | ((x & 0x1)<<14))
#define TRIM_SW(x)          DAA_CON0 = ((DAA_CON0 & ~BIT(15)) | ((x & 0x1)<<15))

/*---DAA_CON1 sfr Setting----*/
#define CHANNEL_L_GAIN(x)   DAA_CON1 = ((DAA_CON1 & ~(BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4))) | (x & 0x1f))
#define VREF_SEL(x)         DAA_CON1 = ((DAA_CON1 & ~BIT(5)) | ((x & 0x1)<<5))
#define LR_2_L(x)           DAA_CON1 = ((DAA_CON1 & ~BIT(6)) | ((x & 0x1)<<6))
#define LR_2_R(x)           DAA_CON1 = ((DAA_CON1 & ~BIT(7)) | ((x & 0x1)<<7))

#define CHANNEL_R_GAIN(x)   DAA_CON1 = ((DAA_CON1 & ~(BIT(8)|BIT(9)|BIT(10)|BIT(11)|BIT(12))) | ((x & 0x1f)<<8))
#define MIC_2_L(x)          DAA_CON1 = ((DAA_CON1 & ~BIT(14)) | ((x & 0x1)<<14))
#define MIC_2_R(x)          DAA_CON1 = ((DAA_CON1 & ~BIT(15)) | ((x & 0x1)<<15))


/*---DAA_CON2 sfr Setting----*/
#define LIN0_CHANNL_L_EN(x) DAA_CON2 = ((DAA_CON2 & ~BIT(0)) | (x & 0x1))
#define LIN0_CHANNL_R_EN(x) DAA_CON2 = ((DAA_CON2 & ~BIT(1)) | ((x & 0x1)<<1))
#define LIN1_CHANNL_L_EN(x) DAA_CON2 = ((DAA_CON2 & ~BIT(2)) | ((x & 0x1)<<2))
#define LIN1_CHANNL_R_EN(x) DAA_CON2 = ((DAA_CON2 & ~BIT(3)) | ((x & 0x1)<<3))
#define LIN2_CHANNL_L_EN(x) DAA_CON2 = ((DAA_CON2 & ~BIT(4)) | ((x & 0x1)<<4))
#define LIN2_CHANNL_R_EN(x) DAA_CON2 = ((DAA_CON2 & ~BIT(5)) | ((x & 0x1)<<5))
#define AMUX_G(x)           DAA_CON2 = ((DAA_CON2 & ~BIT(6)) | ((x & 0x1)<<6))
#define AMUX_EN(x)          DAA_CON2 = ((DAA_CON2 & ~BIT(7)) | ((x & 0x1)<<7))
#define AMUX_MUTE(x)        DAA_CON2 = ((DAA_CON2 & ~BIT(13)) | ((x & 0x1)<<13))


#define VCM_DET_EN(x)       DAA_CON2 = ((DAA_CON2 & ~BIT(8)) | ((x & 0x1)<<8))
#define VCM_EN(x)           DAA_CON2 = ((DAA_CON2 & ~BIT(9)) | ((x & 0x1)<<9))
#define VCM_OUT_EN(x)       DAA_CON2 = ((DAA_CON2 & ~BIT(10)) | ((x & 0x1)<<10))
#define VCM_OUT_PD(x)       DAA_CON2 = ((DAA_CON2 & ~BIT(11)) | ((x & 0x1)<<11))
#define DAC_OE(x)           DAA_CON2 = ((DAA_CON2 & ~BIT(12)) | ((x & 0x1)<<12))
#define DCK_OE(x)           DAA_CON2 = ((DAA_CON2 & ~BIT(13)) | ((x & 0x1)<<13))
#define DAC_EXT(x)          DAA_CON2 = ((DAA_CON2 & ~BIT(14)) | ((x & 0x1)<<14))


#define DAC_SAMPLE_CON      (0)
#define DAC_SAMPLE_POINT    (32 * (1 << DAC_SAMPLE_CON))
#define DAC_BUF_LEN         (DAC_SAMPLE_POINT*2*2)
#define DAC_DUAL_BUF_LEN    (DAC_SAMPLE_POINT * 2)

//extern u8 g_sys_vol;

extern cbuffer_t dac_cb ;
void audio_init(void);
void audio_set(void);
void dac_on_init(void);
void dac_set_samplerate(u16 rate,tbool wait);
void dac_write(u8 *buf ,u32 len);
int dac_get_inbuf_totlen(void *priv);
void cbuf_write_dac(s16 * buf,u32 len);
void clear_dac_dma_buf(void);
void dac_trim_init(void *buf);
u32 get_dac_energy_value();
enum
{
    SR_441K = 0x0,
    SR_48K,
    SR_32K,
    SR_2205K = 0x4,
    SR_24K,
    SR_16K,
    SR_11025K = 0x8,
    SR_12K = 0x9,
    SR_8K = 0xA,
};

#if 1
    #define dac_puts(...)
    #define dac_u32d(...)
    #define dac_u32hex0(...)
    #define dac_u32hex(...)
    #define dac_printf(...)
#else
    #define dac_puts           puts
    #define dac_u32d           put_u32d
    #define dac_u32hex0        put_u32hex0
    #define dac_u32hex         put_u32hex
    #define dac_printf         printf
#endif

#endif
