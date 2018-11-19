#ifndef _FM_PROMPT_H_
#define _FM_PROMPT_H_

#include "config.h"
//#define FM_PROMPT_EN

extern volatile bool fm_prompt_stopped;
void fm_prompt_play(u8 file_num);
#endif
