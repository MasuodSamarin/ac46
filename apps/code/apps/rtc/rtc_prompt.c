#include "rtc_prompt.h"
#include "play_sel.h"
#include "voice_prompt.h"

bool rtc_prompt_stopped;
/*----------------------------------------------------------------------------*/
/**@brief  RTC
   @param  file_num
   @return NULL
   @note   void rtc_prompt_play(u8 file_num)
*/
/*----------------------------------------------------------------------------*/
void rtc_prompt_play(u8 file_num)
{
#ifdef RTC_PROMPT_EN
    if(!rtc_prompt_stopped)
        return;
    rtc_prompt_stopped = 0;
    voice_prompt_play("RTCTask",file_num);
#endif
}
