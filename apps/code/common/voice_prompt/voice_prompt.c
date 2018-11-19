#include "voice_prompt.h"
#include "play_sel.h"
#include "led7_drv.h"

/*----------------------------------------------------------------------------*/
/**@brief  语音提示播放函数
   @param  father_name调用语音播放的的线程
           file_num语音播放文件好
   @return
   @note   void voice_prompt_play(void *father_name,u8 file_num)
           播放结束后会发出SYS_EVENT_PLAY_SEL_END 消息
*/
/*----------------------------------------------------------------------------*/
void voice_prompt_play(void *father_name,u8 file_num)
{
#ifdef VOICE_PROMPT_EN
  //  puts("-----voice_prompt_play 11----\n");
    tbool psel_enable = 0;

    _PLAY_SEL_PARA *psel_p = NULL;
    psel_p  = (_PLAY_SEL_PARA *)malloc_fun(psel_p ,sizeof(_PLAY_SEL_PARA),0);
    tbool b_res;
    if(NULL != psel_p )
    {
    //    puts("-----voice_prompt_play 22----\n");

        psel_p->file_number = (u32 *)malloc_fun(psel_p->file_number,sizeof(psel_p->file_number[0]),0);
        if(NULL != psel_p->file_number)
        {
   //     puts("-----voice_prompt_play 33----\n");
        
            psel_enable = 1;
            psel_p->max_file_number = 1;
            psel_p->delay = 1;
            psel_p->rpt_time = 1;
	 #ifdef SUPPORT_VOICE_ONOFF_VOICE	
	 	if((BPF_VOICE_ON_MP3==file_num)||(BPF_VOICE_OFF_MP3==file_num))
	             psel_p->file_number[0] = file_num;
	 	else
	 #endif            
	 #ifdef SUPPORT_VOICE_ONOFF
	 #ifndef  SUPPORT_ZY_SA_VOICE
	 	 if(led7_var.bIfHaveVoice)
	 #endif
	 #endif
            psel_p->file_number[0] = file_num;
	 
	printf("===psel_p->file_number[0] === %d\n",psel_p->file_number[0] );
	 
        }
        else
        {
            free_fun((void**)&psel_p);
        }
    }
    b_res = play_sel(father_name, 'A', psel_p);
    if(psel_enable)
    {
        free_fun((void**)&psel_p->file_number);
        free_fun((void**)&psel_p);
    }
    if(!b_res)
    {
        psel_enable = 0;
    }
#endif
}
