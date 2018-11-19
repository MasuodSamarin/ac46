#ifndef _MUSIC_PROMPT_H_
#define _MUSIC_PROMPT_H_

#include "includes.h"
#include "config.h"
#include "decoder_phy.h"
#include "music_api.h"

//#define MUSIC_PROMPT_EN

typedef enum
{
    PROMPT_STATUS_PLAY,
    PROMPT_STATUS_PAUSE,
    PROMPT_STATUS_STOP,
    PROMPT_STATUS_RESET,
    PROMPT_STATUS_PREV,
    PROMPT_STATUS_NEXT,
#ifdef MUSIC_PROMPT_EN
	PROMPT_STATUS_DEVICE,
#endif    
}PROMPT_MUSIC_STATUS;

extern bool prompt_played;
extern bool music_prompt_stopped;
extern PROMPT_MUSIC_STATUS music_prompt_flag;
extern _DECODE_STATUS dec_status;

u32 music_prompt_play(u8 play_msg,MUSIC_OP_API *m_op_api);
u32 prompt_play_end(MUSIC_OP_API *m_op_api);

#endif
