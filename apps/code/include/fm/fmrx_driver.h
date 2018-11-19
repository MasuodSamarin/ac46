#ifndef _FM_DRIVER_
#define _FM_DRIVER_

#include "typedef.h"

#define FM_NMG 1.3f

struct fm_config_dat
{
    u8 nrs;    // 2 - 7
    u8 nc1;    // 50 - 100
    u8 nc2;    // 30 - 80
    u8 ncc;    // 20 - 60
    u32 osc_clk;
    u8 fm_pf_en;
    u8 fmif_g;
};

struct res_freq_analy
{
    s16 rssi;       //
    s16 ifc1;       // zero crossing
    s16 ifc2;       //
    s16 ifcc;       // ifc1 - ifc2
};

extern void fm_analog_init(void);
extern void fmrx_anlog_freq_set(unsigned long freq, unsigned long ref_clk);
extern void fmrx_digital_init(unsigned char mid_freq_sel);
extern void fmrx_initial(u8 mode);
extern struct res_freq_analy fmrx_freq_analy(void);
extern void fmrx_delay(u8 n);
extern u32 fm_pf_function(unsigned long t);

extern u8 fmrx_get_busy(void);
extern void fmrx_send_cmd(u8 cmd);
extern u8 fmrx_set_freq(u32 freq);

extern u8 fmrx_set_fft(u8 fft_nu, u8 acc_nu);
extern u8 fmrx_set_stereo(u8 set);
extern u8 fmrx_set_abw(u8 set);
extern u8 fmrx_get_rssi(void);
extern u8 fmrx_get_pilot(void);
extern u8 fmrx_get_adcs(void);
extern u8 fmrx_set_amute(u8 set);
extern u8 fmrx_get_avalid(void);
extern void fmrx_scan(u8 fft_max);

extern volatile unsigned long lofc_res32;
extern s32 * fmrx_ctlbuf;
extern u8 volatile fmrx_tmr;

extern const long fm_config0[64];
extern const long fm_config1[32];
extern const s16 hwfe_if200k[20+1+64];
extern const s16 hwfe_if175k[20+1+64];
extern const s16 hwfe_if125k[20+1+64];
extern const s16 hwfe_tb1[32+1+64];
extern struct fm_config_dat  fm_set;
#endif





