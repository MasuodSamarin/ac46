#ifndef _PC_PROMPT_H_
#define _PC_PROMPT_H_

#include "config.h"

//#define PC_PROMPT_EN

extern volatile bool pc_prompt_playing;
void pc_prompt_play(u8 file_num);

#endif
