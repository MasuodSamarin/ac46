#ifndef _LDAC_H_
#define _LDAC_H_
#include "includes.h"
#include "circular_buf.h"

/*-------------------------------------------------------*/
#define LADC_ONE_CH    (0<<10)
#define LADC_TWO_CH    (1<<10)
#define LADC_THREE_CH  (2<<10)
#define LADC_FOUR_CH   (3<<10)

/*-------------------------------------------------------*/
#define LADC_CH_DACL   0
#define LADC_CH_DACR   1
#define LADC_CH_MIC    2        ///MIC的放大器输入
#define LADC_CH_PC15   3
#define LADC_CH_PC12   6
#define LADC_CH_PC13   7

#define LADC_CH0_BIT   0
#define LADC_CH1_BIT   4
#define LADC_CH2_BIT   8
#define LADC_CH3_BIT   12
/*-------------------------------------------------------*/
#define LADC_SR44100    0
#define LADC_SR48000    1
#define LADC_SR32000    2

#define LADC_SR22050    4
#define LADC_SR24000    5
#define LADC_SR16000    6

#define LADC_SR11025    8
#define LADC_SR12000    9
#define LADC_SR8000     0xa


#define LADC_ANALOG_RESET       BIT(13)  //analog
#define LADC_ANALOG_ELE(n)  ((n)<<14)
#define LADC_ANALOG_EN      BIT(12)
#define LADC12_START        BIT(10)
#define LADC_OSR8           BIT(8)
#define LADC_CLK(n)  ((n)<<5)


typedef struct _LADC_CTL
{
    cbuffer_t *c_buff[4];
    u8 *buff[4];
    void (*save_ladc_buf)(void *,void *,u8, u32);
    u8  source_chl;
}LADC_CTL;

extern volatile LADC_CTL *p_ladc;
extern volatile LADC_CTL *fm_ladc;

#define ENC_MIC_CHANNEL      0
#define ENC_DAC_CHANNEL      1      //与当前dac的模拟通道源一致
#define ENC_FM_CHANNEL       2      //即DAC通道
#define ENC_BT_CHANNEL       3      //蓝牙
#define ENC_USER_CHANNEL     4      //用户自定义


void disable_ladc(u8 ch_sel);           //ch_sel 传参 ENC_MIC_CHANNEL/ENC_DAC_CHANNEL/ENC_FM_CHANNEL
void ladc_reg_init(u8 ch_sel, u8 sr);   //ch_sel 传参 ENC_MIC_CHANNEL/ENC_DAC_CHANNEL/ENC_FM_CHANNEL

void ladc_isr(void);

#endif
