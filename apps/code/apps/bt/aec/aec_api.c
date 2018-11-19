#include "aec_api.h"
#include "config.h"

AEC_CFG btcfg_aec;    //aec配置
int eq_tab[65] =
{
#if 1
32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,
32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,
32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,
32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,
#else
32768,32768,32768,36601,48867,51321,51811,51909,51929,51933,51934,51934,51934,51934,51934,51934,51934,
51934,51934,51934,51934,51934,51934,51934,48101,35835,33381,32891,32793,32773,32769,32768,32768,32768,
32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,
32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,32768,
#endif
};
void btcfg_aec_init(void)
{
    btcfg_aec.dac_analog_gain = 23;    //dac最大模拟增益
    btcfg_aec.mic_analog_gain = 10;    //mic模拟增益
}

void agc_init()
{
    //void set_agc_params(u16 gain,u16 NDT_max_gain,u16 NDT_min_gain ,u16 NDT_Fade_Speed)
     set_agc_params(64 , 168, 16, 20);

    //set_agc_params2(u16 FarEnd_Talk_Threshold,u16 NearEnd_Begin_Threshold,u16 e_slow,u16 x_slow,u16 frame_cnt)
    set_agc_params2(1000 , 130, 0, 0, 0);

    //set_argv_params(u16 suppress_coeff1,u16 suppress_coeff2,u16 detect_thr ,u16 detect_min_gain,u16 eq_gain)
    set_argv_params(2 ,1000, 56 , 64 , 256);

    //set_argv_eq_table(int *eq_tab)
    set_argv_eq_table(eq_tab);

}
