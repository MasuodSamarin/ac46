#include "pc_prompt.h"
#include "play_sel.h"
#include "voice_prompt.h"
#include "usb_device.h"

#if USB_PC_EN

volatile bool pc_prompt_playing = 0;

void pc_prompt_play(u8 file_num)
{
#ifdef PC_PROMPT_EN
    if(pc_prompt_playing)
    {
        puts("pc_prompt_playing\n");
        return;
    }
    pc_prompt_playing = 1;
    voice_prompt_play(PC_TASK_NAME,file_num);
#endif
}

#endif
