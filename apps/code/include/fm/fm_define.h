#ifndef  _FM_DEFINE_COEF_
#define  _FM_DEFINE_COEF_
//================================================
//   fm  sfr address define
//===============================================

#define  MID_FREQ      175

#define  FM_BASE_ADDR           0Xffc00L
#define  FM_DSP_CON             (*(volatile unsigned long  *)(FM_BASE_ADDR + 0*4))
#define  CPU2FM_PND             (*(volatile unsigned long  *)(FM_BASE_ADDR + 1*4))
#define  FM2CPU_PND             (*(volatile unsigned long  *)(FM_BASE_ADDR + 2*4))
#define  FM2CPU_IE              (*(volatile unsigned long  *)(FM_BASE_ADDR + 3*4))

#define  FM_DIVA                (*(volatile unsigned long  *)(FM_BASE_ADDR + 8*4))
#define  FM_DIVB                (*(volatile unsigned long  *)(FM_BASE_ADDR + 9*4))
#define  FM_DIVRES              (*(volatile unsigned long  *)(FM_BASE_ADDR + 10*4))
#define  FM_HWFE_CON            (*(volatile unsigned long  *)(FM_BASE_ADDR + 11*4))
#define  FM_HWFE_CRAM           (*(volatile unsigned long  *)(FM_BASE_ADDR + 12*4))
#define  FM_HWFE_DRAM           (*(volatile unsigned long  *)(FM_BASE_ADDR + 13*4))
#define  FM_DSADC_CON           (*(volatile unsigned long  *)(FM_BASE_ADDR + 14*4))
#define  FM_LOFC_CON            (*(volatile unsigned long  *)(FM_BASE_ADDR + 15*4))
#define  FM_LOFC_RES            (*(volatile unsigned long  *)(FM_BASE_ADDR + 16*4))
//#define  FM_CON                 (*(volatile unsigned long  *)(FM_BASE_ADDR + 17*4))
#define  FM_IADC                (*(volatile unsigned long  *)(FM_BASE_ADDR + 18*4))

#define  FMA_CON0               (*(volatile unsigned long  *)(FM_BASE_ADDR + 19*4))
#define  FMA_CON1               (*(volatile unsigned long  *)(FM_BASE_ADDR + 20*4))
#define  FMA_CON2               (*(volatile unsigned long  *)(FM_BASE_ADDR + 21*4))
#define  FMA_CON3               (*(volatile unsigned long  *)(FM_BASE_ADDR + 22*4))
#define  FMA_CON4               (*(volatile unsigned long  *)(FM_BASE_ADDR + 23*4))
//==========================================================================//
//                fm  dsp adr mapping
//==========================================================================//
#define FM_DATIN_ADR          0XF000
#define FM_VOICE_ADR          0XF200   // 32 *2 * 2
#define FM_TRANF_ADR          0XF280   // 2 + 64
//fmdsp sp 0xf300 - f2f0

//==========================================================================//
//                fm cpu adr
//==========================================================================//
#define CPU_RVOIVE_ADR       ((FM_VOICE_ADR - 0xF000)*4 + 0xFC000)
#define CPU_TRANF_ADR        ((FM_TRANF_ADR - 0XF000)*4 + 0xFc000)           // cpu  and fm transfer data base address
#define CPU_FFTRES_ADR       (CPU_TRANF_ADR + 8)
#define FM_VOICE_LEN         32
//==========================================================================//
//                fm  dsp coef ram adr
//==========================================================================//
#define  FMTRANF_ADDR         (*(volatile unsigned long  *)((0xf063 - 0xf000)*4 + 0xFc000))                //   !!!


#define  FMIN_ADDR            (unsigned long) (0xf062)
#define  fmscan_data_adr      (unsigned long) (0xf070)
#define  FFT_N                (unsigned long) (fmscan_data_adr + 0 ) //   fft_coef_baseadr + -7      ; 128
#define  LOG2_FFT_N           (unsigned long) (fmscan_data_adr + 1 ) //   fft_coef_baseadr + -6      ; 7
#define  FFTACC_NU            (unsigned long) (fmscan_data_adr + 2 ) //   fft_coef_baseadr + -5      ; 64
#define  FFT_ASHR             (unsigned long) (fmscan_data_adr + 3 ) //   fft_coef_baseadr + -4      ; //LOG2_FFTN + (LOG2_maxin - LOG2_MAXOUT)   5 = 7 + (14 -16)
#define  FFTACC_ASHR          (unsigned long) (fmscan_data_adr + 4 ) //   fft_coef_baseadr + -3      ; read only
#define  HAN_ADD              (unsigned long) (fmscan_data_adr + 13 )  //   fft_coef_baseadr + 6     ; read only

#define  fmrx_coef_adr        (unsigned long) (0xf080)
#define  DCC2_C1              (unsigned long) (fmrx_coef_adr + 0  )// -7
#define  DCC2_C2              (unsigned long) (fmrx_coef_adr + 1  )// -6   ;DC cancelling filter 2
#define  DCC2_SC              (unsigned long) (fmrx_coef_adr + 2  )// -5
#define  PI                   (unsigned long) (fmrx_coef_adr + 3  )// -4   ;16380
#define  PID4                 (unsigned long) (fmrx_coef_adr + 4  )// -3   ;-4095
#define  FOUT_C               (unsigned long) (fmrx_coef_adr + 5  )// -2
#define  STEREO               (unsigned long) (fmrx_coef_adr + 6  )// -1   ;
#define  FREQ_DEPTH           (unsigned long) (fmrx_coef_adr + 7  )//  0

#define  PT_C1                (unsigned long) (fmrx_coef_adr + 8  )//  1
#define  PT_C2                (unsigned long) (fmrx_coef_adr + 9  )//  2   ;phase tuning
#define  PT_SC                (unsigned long) (fmrx_coef_adr + 10 )//  3
#define  PU1_GAIN             (unsigned long) (fmrx_coef_adr + 11 )//  4
#define  PU1_C2               (unsigned long) (fmrx_coef_adr + 12 )//  5
#define  PU1_C3               (unsigned long) (fmrx_coef_adr + 13 )//  6   ;19KHz PIck-up
#define  PU1_C4               (unsigned long) (fmrx_coef_adr + 14 )//  7
#define  PU1_C1               (unsigned long) (fmrx_coef_adr + 15 )//  8

#define  PU2_C1               (unsigned long) (fmrx_coef_adr + 16 )//  -7
#define  PU2_C2               (unsigned long) (fmrx_coef_adr + 17 )//  -6  ;38KHz PIck-up
#define  PU2_C3               (unsigned long) (fmrx_coef_adr + 18 )//  -5
#define  PU2_C4               (unsigned long) (fmrx_coef_adr + 19 )//  -4
#define  PU2_GAIN             (unsigned long) (fmrx_coef_adr + 20 )//  -3
#define  PU3_C1               (unsigned long) (fmrx_coef_adr + 21 )//  -2
#define  CSR_C                (unsigned long) (fmrx_coef_adr + 22 )//  -1
#define  PU3_C3               (unsigned long) (fmrx_coef_adr + 23 )//   0
#define  PU3_C4               (unsigned long) (fmrx_coef_adr + 24 )//   1
#define  DEM_C1               (unsigned long) (fmrx_coef_adr + 25 )//   2
#define  DEM_C2               (unsigned long) (fmrx_coef_adr + 26 )//   3   ;de-emphasis
#define  PU38KSAT             (unsigned long) (fmrx_coef_adr + 27 )//   4   ;SAT TO 16BIT = 23 - 16 = 7

#define  LS                   (unsigned long) (fmrx_coef_adr + 28 )//   5
#define  RS                   (unsigned long) (fmrx_coef_adr + 29 )//   6
#define  PU3_GAIN             (unsigned long) (fmrx_coef_adr + 30 )//   7  // >> =  LRSC -  BWL_SC
#define  LRSC                 (unsigned long) (fmrx_coef_adr + 31 )//   8  // >> =  LRSC -  BWL_SC
#define  PU3_C2               (unsigned long) (fmrx_coef_adr + 32 )//   9  ;38KHz PIck-up

#define  BWL_SC               (unsigned long) (fmrx_coef_adr + 33 )//   10
#define  BWL_C1               (unsigned long) (fmrx_coef_adr + 34 )//   11
#define  BWL_C2               (unsigned long) (fmrx_coef_adr + 35 )//   12
#define  DEM_SC               (unsigned long) (fmrx_coef_adr + 36 )//   13

#define  RSSI_C1              (unsigned long) (fmrx_coef_adr + 37 )
#define  RSSI_C2              (unsigned long) (fmrx_coef_adr + 38 )
#define  FMOUT_ADDR           (unsigned long) (fmrx_coef_adr + 39 )
#define  FMBUF_LEN            (unsigned long) (fmrx_coef_adr + 40 )

#define  MIDFREQ_RSSI         (unsigned long) (fmrx_coef_adr + 45 )
#define  FMAX_PP              (unsigned long) (fmrx_coef_adr + 46 )
#define  FDC_SET              (unsigned long) (fmrx_coef_adr + 47 )
#define  FE_DLY               (unsigned long) (fmrx_coef_adr + 48 )
#define  FP_FLAG              (unsigned long) (fmrx_coef_adr + 49 )
#define  AMIDFREQ_RSSI        (unsigned long) (fmrx_coef_adr + 51 )

#define  PILOT_RSSI           (unsigned long) (fmrx_coef_adr + 73 )

#endif


