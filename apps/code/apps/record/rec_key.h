#ifndef __REC_KEY_H__
#define __REC_KEY_H__

#include "includes.h"

#if AD_KEY_MAX
extern const u8 adkey_msg_rec_table[4][AD_KEY_MAX];
#else
extern const u8 adkey_msg_rec_table[4][10];
#endif
extern const u8 iokey_msg_rec_table[4][10];
#if ir_max_num
extern const u8 irff00_msg_rec_table[4][ir_max_num];
#else
extern const u8 irff00_msg_rec_table[4][21];
#endif

#if KEY_TCH_EN
extern const u8 touchkey_msg_rec_table[4][10];
#endif

#endif/*__REC_KEY_H__*/
