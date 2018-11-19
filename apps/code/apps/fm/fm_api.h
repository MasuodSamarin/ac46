/*--------------------------------------------------------------------------*/
/**@file    fm_api.h
   @brief   FM 模式功能接口
   @details
   @author  guowei
   @date    2014-9-15
   @note    DV10
*/
/*----------------------------------------------------------------------------*/
#ifndef	_FM_API_H_
#define _FM_API_H_

#include "typedef.h"
#include "fm_resample.h"
#include "app_cfg.h"

#define FM_CUR_FRE          0
#define FM_FRE_DEC          1
#define FM_FRE_INC			2


//#define MEM_FM_LEN     26
//#define MAX_FRE    108000UL
//#define MIN_FRE	   87500UL
//#define FM_STEP    100
//
//#define MAX_CHANNL ((MAX_FRE - MIN_FRE)/FM_STEP + 1)

#define FM_POINT_TRUE   15  ///>FM真假台阀值，真台满值128

#define MEM_FM_LEN     26
#define MAX_FRE    1080
#define MIN_FRE	   875
#define FM_STEP    100
#define MAX_CHANNL (MAX_FRE - MIN_FRE + 1)


enum
{
    FM_FRE=0,
    FM_CHAN,
    FM_CHANNL,
};

extern FM_INFO *fm_info;
extern FM_RS_USE *fm_rs_objt;      ///>FM变采样
extern bool fm_init_flag;

/*****************************
        Function Declare
*****************************/
extern tbool init_fm_rev(void);
extern void fm_rev_powerdown(void);

extern void fm_info_init(void);

extern tbool set_fre(u8 mode);
extern void fm_module_mute(u8 flag);

extern tu8 get_total_mem_channel(void);
extern tu8 get_channel_via_fre(u8 fre);

extern tbool fm_scan(u8 mode);
extern tu8 get_fre_via_channle(u8 channel);

extern void save_fm_point(u8 fre);
extern void delete_fm_point(u8 fre);
extern void clear_all_fm_point(void);

extern void ch_save(void);

extern u8 fmrx_set_stereo(u8 set);//立体声设置
extern u8 fmrx_set_amute(u8 set);
void fm_open(void);

extern void fm_read_info(void);
extern void fm_save_info(void);

extern u32 fm_cbuf_write(s16 * buf,u32 len);
extern u32 fm_cbuf_read(s16 * buf,u32 len);
extern void fm_cbuf_init(void);
extern void fm_cbuf_close(void);
#endif
