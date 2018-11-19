#include "app_cfg.h"
#include "os_api.h"
#include "os_cfg.h"
#include "error.h"
#include "system_cfg.h"
#include "msg.h"
#include "config.h"
#include "task_manage.h"
#include "rtc_key.h"
#include "irtc.h"
#include "rtc.h"
#include "rtc_low_power.h"
#include "rtc_setting.h"
#include "dac_api.h"
#include "play_sel.h"
#include "key.h"
#include "key_voice.h"
#include "led.h"
#include "dac_api.h"
#include "ui_api.h"
#include "rtc_prompt.h"


extern void *malloc_fun(void *ptr,u32 len,char *info);
extern void free_fun(void **ptr);

#if RTC_CLK_EN

RTC_TIME current_time;
RTC_TIME current_alarm;



/////////////////////////////////////////////////
//                TEST
/////////////////////////////////////////////////
void rtc_clk_out(RTC_TIME *curr_time)
{
    rtc_printf("YMDHMS %d:",curr_time->dYear);
    rtc_printf("%d:",curr_time->bMonth);
    rtc_printf("%d:",curr_time->bDay);
    rtc_printf("%d:",curr_time->bHour);
    rtc_printf("%d:",curr_time->bMin);
    rtc_printf("%d\n",curr_time->bSec);
}
/////////////////////////////////////////////////
//                TEST
/////////////////////////////////////////////////

/*----------------------------------------------------------------------------*/
/**@brief  ��������
   @param  ��
   @return ��
   @note   u8 alm_on(void)
*/
/*----------------------------------------------------------------------------*/
u8 is_alm_on(void)
{
    return rtc_set.alarm_set.alarm_flag;
}

/*----------------------------------------------------------------------------*/
/**@brief  RTC DACͨ��ѡ�񣬿���
   @param  ��
   @return ��
   @note   void aux_dac_channel_on(void)
*/
/*----------------------------------------------------------------------------*/
void rtc_dac_channel_on(void)
{
    dac_mute(1,1);
    dac_channel_on(RTC_CHANNEL, FADE_OFF);
    os_time_dly(15);  //���������Ӱ�쵽�ϵ��һ�ν���line in�ĳ���������Ը�����������
    dac_mute(0,1);

    set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);
#ifdef KOK_DETECT_AUTO_VOL_SET		
	 store_vol= dac_var.cur_sys_vol_l;
#endif
	
}

/*----------------------------------------------------------------------------*/
/**@brief  RTC DACͨ��ѡ�񣬹ر�
   @param  ��
   @return ��
   @note   void aux_dac_channel_off(void)
*/
/*----------------------------------------------------------------------------*/
void rtc_dac_channel_off(void)
{
    dac_channel_off(RTC_CHANNEL, FADE_OFF);
    dac_mute(0,1);
}

/*----------------------------------------------------------------------------*/
/**@brief  RTCģʽ��ʾ������
   @param  ��
   @return ��
   @note   void aux_tone_play(void)
*/
/*----------------------------------------------------------------------------*/
void rtc_tone_play(void)
{
    tbool psel_enable = 0;

    _PLAY_SEL_PARA *psel_p = NULL;
    psel_p  = malloc_fun(psel_p ,sizeof(_PLAY_SEL_PARA),0);
    tbool b_res;
    if(NULL != psel_p )
    {
        psel_p->file_number = malloc_fun(psel_p->file_number,sizeof(psel_p->file_number[0]),0);
        if(NULL != psel_p->file_number)
        {
            psel_enable = 1;
            psel_p->max_file_number = 1;
            psel_p->delay = 1;
            psel_p->rpt_time = 1;
            psel_p->file_number[0] = BPF_RTC_MP3;
        }
        else
        {
            free_fun((void**)&psel_p);
        }
    }
    b_res = play_sel(RTC_TASK_NAME, 'A', psel_p);
    if(psel_enable)
    {
        free_fun((void**)&psel_p->file_number);
        free_fun((void**)&psel_p);
    }
    if(!b_res)
    {
        psel_enable = 0;
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  RTC��ʼ��
   @param  void
   @return ��
   @note   void rtc_info_init(void)
*/
/*----------------------------------------------------------------------------*/
void rtc_info_init(void)
{
    irtc_init();//оƬ�ڲ�irtcģ���ʼ��
    alm_sw(rtc_set.alarm_set.alarm_sw);

    rtc_dac_channel_on();
    SET_UI_MAIN(MENU_RTC_MAIN);
    UI_menu(MENU_RTC_MAIN);
}

void stop_alm(void)
{
    rtc_set.alarm_set.alarm_flag = 0;
    SET_UI_MAIN(MENU_RTC_MAIN);
    UI_menu(MENU_RTC_MAIN);
}
/*----------------------------------------------------------------------------*/
/**@brief  RTC ����
   @param  p��������������ָ��
   @return ��
   @note   static void rtc_task(void *p)
*/
/*----------------------------------------------------------------------------*/
extern void RTC_alm_rtc_ini(void);
static void rtc_task(void *p)
{
    int msg[3];

    rtc_puts("\n************************RTC TASK********************\n");
    #if LED_SHOW_RTC
    setLedLight(LED_SHOW_RTC,led_mode_flash_slow,0);
    #else
    //led_fre_set(15);
    #endif
    rtc_tone_play(); //line in��ʾ������

    while(1)
    {
        os_taskq_pend(0, ARRAY_SIZE(msg), msg);

        if(rtc_set.alarm_set.alarm_flag)        //�������ʱ�򣬲��ְ�����ϢתΪֹͣ���ӹ���
        {
            if((msg[0]==MSG_RTC_SETTING)
               ||(msg[0]==MSG_ALM_SETTING)
               ||(msg[0]==MSG_ALM_SW)
               ||(msg[0]==MSG_RTC_POWER_DOWN))
            {
                stop_alm();
                continue;
            }
        }

        switch(msg[0])
        {
        case SYS_EVENT_DEL_TASK:
            if (os_task_del_req_name(OS_TASK_SELF) == OS_TASK_DEL_REQ)
            {
                UI_menu(MENU_WAIT);
                rtc_puts("AUX_SYS_EVENT_DEL_TASK\n");
                rtc_set.alarm_set.alarm_flag = 0;//�����ӱ�־
                rtc_dac_channel_off();
                play_sel_stop(); //�ر���ʾ��
                os_task_del_res_name(OS_TASK_SELF);
            }
            break;

        case SYS_EVENT_PLAY_SEL_END: //��ʾ������
            rtc_puts("RTC_SYS_EVENT_PLAY_SEL_END\n");
            play_sel_stop(); //�ر���ʾ��
            rtc_puts("RTC_play_tone_end\n");
            rtc_prompt_stopped = 1;
            os_taskq_post_msg(RTC_TASK_NAME, 1, MSG_RTC_INIT); //����AUXģ���ʼ��
            break;

        case MSG_RTC_INIT:
            rtc_puts("MSG_RTC_INIT\n");
            rtc_info_init();
            break;

        case MSG_RTC_SETTING:                  ///RTCʱ������
            rtc_puts("MSG_RTC_SETTING\n");
            rtc_set.rtc_set_mode = RTC_SET_MODE;
            rtc_setting();
            break;

#if RTC_ALM_EN
        case MSG_ALM_SETTING:                     ///����ʱ������
            rtc_puts("MSG_ALM_SETTING\n");
            rtc_set.alarm_set.alarm_sw = 1;
            alm_sw(rtc_set.alarm_set.alarm_sw);
            rtc_set.rtc_set_mode = ALM_SET_MODE;
            rtc_setting();
            break;
#endif

        case MSG_ALM_SW:
            if(rtc_set.alarm_set.alarm_sw)
            {
                rtc_set.alarm_set.alarm_sw = 0;
            }
            else
            {
                rtc_set.alarm_set.alarm_sw = 1;
            }
            alm_sw(rtc_set.alarm_set.alarm_sw);
            UI_menu(MENU_ALM_SET);
            break;

        case MSG_RTC_POWER_DOWN:
            rtc_lowpower_api();
            break;

        case MSG_LOW_POWER:
            puts("rtc_low_power\n");
            rtc_prompt_play(BPF_LOW_POWER_MP3);
            break;

        case MSG_HALF_SECOND:
            //puts(" rtc_H ");
            if(rtc_set.alarm_set.alarm_flag)
            {
                SET_UI_MAIN(MENU_ALM_UP);
                UI_menu(MENU_ALM_UP);
                send_key_voice(500);
            }
            read_rtc_time(&current_time);
            UI_menu(MENU_MAIN);
            UI_menu(MENU_HALF_SEC_REFRESH);
            rtc_clk_out(&current_time);
            break;

        default:
            break;
        }
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  RTC ���񴴽�
   @param  priv��������������ָ��
   @return ��
   @note   static void rtc_task_init(void *priv)
*/
/*----------------------------------------------------------------------------*/
static void rtc_task_init(void *priv)
{
    u32 err;
    err = os_task_create(rtc_task,
                         (void*)0,
                         TaskRTCPrio,
                         10
#if OS_TIME_SLICE_EN > 0
                         ,1
#endif
                         ,RTC_TASK_NAME);

    if(OS_NO_ERR == err)
    {  
    #if KEY_IO_EN
	     key_msg_register(RTC_TASK_NAME, rtc_ad_table, rtc_io_table, rtc_ir_table, NULL);
    #else
        key_msg_register(RTC_TASK_NAME, rtc_ad_table, NULL, rtc_ir_table, NULL);
    #endif
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  RTC ����ɾ���˳�
   @param  ��
   @return ��
   @note   static void rtc_task_exit(void)
*/
/*----------------------------------------------------------------------------*/
static void rtc_task_exit(void)
{
    if (os_task_del_req(RTC_TASK_NAME) != OS_TASK_NOT_EXIST)
    {
        os_taskq_post_event(RTC_TASK_NAME, 1, SYS_EVENT_DEL_TASK);
        do
        {
            OSTimeDly(1);
        }
        while(os_task_del_req(RTC_TASK_NAME) != OS_TASK_NOT_EXIST);
        rtc_puts("del_linein_task: succ\n");
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  RTC ������Ϣ
   @note   const struct task_info linein_task_info
*/
/*----------------------------------------------------------------------------*/
TASK_REGISTER(rtc_task_info) =
{
    .name = RTC_TASK_NAME,
    .init = rtc_task_init,
    .exit = rtc_task_exit,
};

#endif
