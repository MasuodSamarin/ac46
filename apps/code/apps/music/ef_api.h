#ifndef _EF_API_H
#define _EF_API_H

#include "typedef.h"

#define EF_VOL    BIT(0)
#define EF_EQ     BIT(1)

#define EQ_FILTER_CFG_LEN 304 //2(crc) + 2(len) + 300(data)

#ifdef EQ_SEQUENCE_ADJ_ANYWAY
extern int const EQ_TableCode[7][5];
extern int const EQ_GainTableCode[7];
#else
extern int const EQ_TableCode[6][5];
extern int const EQ_GainTableCode[6];
#endif
extern int const eq_filt_0[];
extern int const eq_filt_1[];
extern int const eq_filt_2[];

bool read_cfg_file(u8* buff,u8 cfg_file_num,u16 cfg_len);
#ifdef EQ_SEQUENCE_ADJ_ANYWAY
enum EQ_MODE_SEQ{
eq_normal=0,
eq_pop,
eq_rock,
eq_jazz,
eq_classic,
eq_country,
#ifdef GW_LCD_SEG_001_1_AC4601
eq_bass,
eq_max
#else
eq_max,
eq_bass
#endif
};
#endif

#endif
