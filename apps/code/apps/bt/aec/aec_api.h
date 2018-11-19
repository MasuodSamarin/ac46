#ifndef _AEC_API_H_
#define _AEC_API_H_

#include "config.h"

typedef struct
{
    //--MIC和DAC设置--//
    u8 dac_analog_gain;     //dac模拟增益,取值范围:0-30
    u8 mic_analog_gain;		//mic模拟增益,取值范围:0-63
}AEC_CFG;
extern AEC_CFG btcfg_aec;    //aec配置

void btcfg_aec_init(void);
void agc_init();
extern void set_agc_params(u16 gain,u16 NDT_max_gain,u16 NDT_min_gain ,u16 NDT_Fade_Speed);
extern void set_agc_params2(u16 FarEnd_Talk_Threshold,u16 NearEnd_Begin_Threshold,
                            u16 e_slow,u16 x_slow,u16 frame_cnt);
extern void set_argv_params(u16 suppress_coeff1,u16 suppress_coeff2,
                            u16 detect_thr ,u16 detect_min_gain,u16 eq_gain);
extern void set_argv_eq_table(int *eq_tab);

#endif/*_AEC_API_H_*/
