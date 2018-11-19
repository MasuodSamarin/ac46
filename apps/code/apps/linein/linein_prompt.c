#include "linein_prompt.h"
#include "play_sel.h"
#include "voice_prompt.h"
#include "dac.h"

bool linein_prompt_stopped;
/*----------------------------------------------------------------------------*/
/**@brief  Linein语音播放函数
   @param  file_num：语音文件号
   @return NULL
   @note   void linein_prompt_play(u8 file_num)
*/
/*----------------------------------------------------------------------------*/
void linein_prompt_play(u8 file_num)
{
#ifdef LINEIN_PROMPT_EN

    if(!linein_prompt_stopped)
        return;
#ifdef support_io_det_mute
	 bt_automute_sw=5;  // bt 报语音 时不mute
#endif

 #if KEY_TONE_EN==0
 TRIM_EN(0); 
#endif
	
    linein_prompt_stopped = 0;
    voice_prompt_play("LineinTask",file_num);
#endif
}
