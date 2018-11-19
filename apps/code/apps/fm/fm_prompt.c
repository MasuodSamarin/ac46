#include "fm_prompt.h"
#include "play_sel.h"
#include "voice_prompt.h"
#include "fm_radio.h"
#include "os_api.h"
#include "fm_api.h"
#include "msg.h"

#if FM_RADIO_EN

volatile bool fm_prompt_stopped;
/*----------------------------------------------------------------------------*/
/**@brief  FM语音提示函数
   @param  file_num：语音文件号
   @return NULL
   @note   void fm_prompt_play(u8 file_num)
*/
/*----------------------------------------------------------------------------*/
void fm_prompt_play(u8 file_num)
{
#ifdef FM_PROMPT_EN
    if(!fm_prompt_stopped)
        return;
    fm_prompt_stopped = 0;
    fm_module_mute(1);
    fm_save_info();
    voice_prompt_play("FMRadioTask",file_num);
#endif
}

#endif
