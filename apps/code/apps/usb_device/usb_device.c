#include "app_cfg.h"
#include "os_api.h"
#include "os_cfg.h"
#include "error.h"
#include "system_cfg.h"
#include "msg.h"
#include "task_manage.h"
#include "usb_device.h"
#include "mango_dev_usb_slave.h"
#include "usb_key.h"
#include "dac.h"
#include "dac_api.h"
#include "play_sel.h"
#include "dev_pc.h"
#include "key.h"
#include "ui_api.h"
#include "dev_ctl.h"
#include "pc_prompt.h"
#include "led.h"
extern void *malloc_fun(void *ptr,u32 len,char *info);
extern void free_fun(void **ptr);

#if USB_PC_EN
/*----------------------------------------------------------------------------*/
/**@brief  PC������ ����
   @param  p��������������ָ��
   @return ��
   @note   static void pc_card_task(void *p)
*/
/*----------------------------------------------------------------------------*/
static void pc_card_task(void *p)
{
	int msg[3];

	pc_puts("--------pc_card_task-----\n");
	while(1)
	{
		os_taskq_pend(0, ARRAY_SIZE(msg), msg);
		switch(msg[0])
		{
			case SYS_EVENT_DEL_TASK:
                pc_puts("PCCARD_SYS_EVENT_DEL_TASK\n");
				if (os_task_del_req_name(OS_TASK_SELF) == OS_TASK_DEL_REQ)
				{
					os_task_del_res_name(OS_TASK_SELF);
				}
				break;
		}
		while(1)
		{
		    if(0 == usb_slave_online_status())
		    {
		        pc_puts("pc_tast_offline\n");
		        break; //PC����
		    }
		    if(0 == ((USB_SLAVE_VAR *)msg[0])->card_reader.working)
		    {
		        pc_puts("pc_card_notworking\n");
		        break;
		    }
		    ((USB_SLAVE_VAR *)msg[0])->card_reader.busy = 1;
		    usb_slave_masstorage(&(((USB_SLAVE_VAR *)msg[0])->card_reader)); //����������
		}
		((USB_SLAVE_VAR *)msg[0])->card_reader.busy = 0;
	}
}


/*----------------------------------------------------------------------------*/
/**@brief  PC������ ���񴴽�
   @param  priv��������������ָ��
   @return ��
   @note   static void pc_card_task_init(void *priv)
*/
/*----------------------------------------------------------------------------*/
static void pc_card_task_init(void *priv)
{

	os_task_create(pc_card_task,
			(void*)0,
			TaskPcCardPrio,
			10
#if OS_TIME_SLICE_EN > 0
			,1
#endif
			,PC_CARD_TASK_NAME);

}


/*----------------------------------------------------------------------------*/
/**@brief  PC������ ����ɾ���˳�
   @param  ��
   @return ��
   @note   static void pc_card_task_exit(void)
*/
/*----------------------------------------------------------------------------*/
static void pc_card_task_exit(void)
{
	if (os_task_del_req(PC_CARD_TASK_NAME) != OS_TASK_NOT_EXIST)
	{
	    puts("send pc SYS_EVENT_DEL_TASK\n");
		os_taskq_post_event(PC_CARD_TASK_NAME, 1, SYS_EVENT_DEL_TASK);
		do
		{
			OSTimeDly(1);
			putchar('D');
		}while(os_task_del_req(PC_CARD_TASK_NAME) != OS_TASK_NOT_EXIST);
		pc_puts("del_pc_card_task: succ\n");
	}
}


/*----------------------------------------------------------------------------*/
/**@brief  PC ������Դ�ͷ�
   @param  susb_var��PCģʽ����ı�����Դָ��
   @return ��
   @note   static void free_usb_slave_resource(USB_SLAVE_VAR *susb_var)
*/
/*----------------------------------------------------------------------------*/
static void free_usb_slave_resource(USB_SLAVE_VAR *susb_var)
{
    if(susb_var)
    {
        susb_var->card_reader.working = 0;
        while(susb_var->card_reader.busy)
        {
            pc_puts("-busy-");
            os_time_dly(5);
        }
        usb_slave_hold(); //holdסPC״̬��ͬʱ�ͷ�DMA��Դ
        free(susb_var);   //�ͷŴӻ�����
    }

    pc_card_task_exit(); //ɾ������������
    pc_dac_off(); //��PC DACͨ��
}


/*----------------------------------------------------------------------------*/
/**@brief  PC ģʽ��ʾ������
   @param  ��
   @return ��
   @note   void pc_tone_play(void)
*/
/*----------------------------------------------------------------------------*/
void pc_tone_play(void)
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
            psel_p->file_number[0] = BPF_PC_MP3;
        }
        else
        {
            free_fun((void**)&psel_p);
        }
    }
    b_res = play_sel(PC_TASK_NAME, 'A', psel_p);
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
/**@brief  PC ����
   @param  p��������������ָ��
   @return ��
   @note   static void pc_task(void *p)
*/
/*----------------------------------------------------------------------------*/
static void pc_task(void *p)
{
	int msg[3];
	u32 pc_mute_status = 0;
    USB_SLAVE_VAR *susb_var = NULL;

	pc_puts("\n************************PC TASK********************\n");
	pc_tone_play(); //PCģʽ��ʾ������
	pc_prompt_playing = 0;
	#if LED_SHOW_PC
	setLedLight(LED_SHOW_PC,led_mode_flash_slow,0);
	#else
	//led_fre_set(15);
	#endif
/*
    if(0 == usb_slave_online_status()) //PC����
    {
        os_taskq_post("MainTask", 1, MSG_CHANGE_WORKMODE);
    }
    else
    {
        //os_taskq_post_msg(PC_TASK_NAME, 1, MSG_PC_MODE_INIT); //�����ӻ�������ʼ��
    }
*/
	while(1)
	{
		os_taskq_pend(0, ARRAY_SIZE(msg), msg);
		switch(msg[0])
		{
			case SYS_EVENT_DEL_TASK:
                pc_puts("PC_SYS_EVENT_DEL_TASK\n");
				if (os_task_del_req_name(OS_TASK_SELF) == OS_TASK_DEL_REQ)
				{
				    UI_menu(MENU_WAIT);
				    free_usb_slave_resource(susb_var);
				    play_sel_stop(); //�ر���ʾ��
					os_task_del_res_name(OS_TASK_SELF);
				}
				break;

            case SYS_EVENT_PLAY_SEL_END: //��ʾ������
                pc_puts("PC_SYS_EVENT_PLAY_SEL_END\n");
                play_sel_stop(); //�ر���ʾ��
#ifdef PC_PROMPT_EN
                if(pc_prompt_playing)
                {
                    pc_puts("PC_play_tone_end_1\n");
                    pc_prompt_playing = 0;
                    dac_set_samplerate(48000,0); //DAC����������Ϊ48K
                    pc_dac_on(); //��PC DACģ��ͨ��
                }
                else
#endif
                {
                    pc_puts("PC_play_tone_end_2\n");
                    os_taskq_post_msg(PC_TASK_NAME, 1, MSG_PC_MODE_INIT); //�����ӻ�������ʼ��
                }
                break;

            case MSG_PC_MODE_INIT:
                pc_puts("MSG_PC_MODE_INIT\n");
                susb_var = usb_slave_init();
                susb_var->card_reader.busy = 1;
                SET_UI_MAIN(MENU_PC_MAIN);
                UI_menu(MENU_PC_MAIN);
                os_taskq_post_msg(PC_TASK_NAME, 1, MSG_PC_CARD_READER);
                break;

            /*************** for CARD READER ******************/
            case MSG_PC_CARD_READER:
                pc_puts("MSG_PC_CARD_READER\n");
                susb_var->card_reader.working = 1;
                os_taskq_post_msg(PC_CARD_TASK_NAME, 1, susb_var);
                break;

            /*************** for AUDIO ******************/
            case MSG_PC_SPK_MUTE:
                pc_puts("MSG_PC_SPK_MUTE\n");
                pc_mute_status = 1;
                pc_dac_mute(1, FADE_ON);
                break;

            case MSG_PC_SPK_UNMUTE:
                pc_puts("MSG_PC_SPK_UNMUTE\n");
                pc_mute_status = 0;
                pc_dac_mute(0, FADE_ON);
                os_taskq_post_msg(PC_TASK_NAME, 1, MSG_PC_SPK_VOL);
                break;

            case MSG_PC_SPK_VOL:
                //pc_puts("MSG_PC_SPK_VOL\n");
                pc_set_speaker_vol(&(susb_var->ep0_var), pc_mute_status);
                break;

            /*************** for HID KEY ******************/
            case MSG_PC_MUTE:
                pc_puts("p_m\n");
                usb_slave_hid(USB_AUDIO_MUTE);
                break;
            case MSG_PC_VOL_DOWN:
                pc_puts("vd\n");
                usb_slave_hid(USB_AUDIO_VOLDOWN);
                UI_menu(MENU_PC_VOL_DOWN);
                break;
            case MSG_PC_VOL_UP:
                pc_puts("vu\n");
                usb_slave_hid(USB_AUDIO_VOLUP);
                UI_menu(MENU_PC_VOL_UP);
                break;
            case MSG_PC_PP:
                pc_puts("pp\n");
                usb_slave_hid(USB_AUDIO_PP);
                break;
            case MSG_PC_PLAY_NEXT:
                pc_puts("ne\n");
                usb_slave_hid(USB_AUDIO_NEXTFILE);
                break;
            case MSG_PC_PLAY_PREV:
                pc_puts("pr\n");
                usb_slave_hid(USB_AUDIO_PREFILE);
                break;

            case MSG_LOW_POWER:
                puts("pc_low_power\n");
                pc_prompt_play(BPF_LOW_POWER_MP3);
                break;

            /*************** for PC UPDATA ******************/
            case MSG_PC_UPDATA:
                pc_puts("MSG_PC_UPDATA\n");
                dev_updata_mode(NULL, PC_UPDATA); //����PC����ģʽ
                break;

            case MSG_HALF_SECOND:
                pc_puts(" PC_H ");
                UI_menu(MENU_MAIN);
                UI_menu(MENU_HALF_SEC_REFRESH);
                break;

			default:
                //pc_puts("pc_default\n");
				break;
		}
	}
}


/*----------------------------------------------------------------------------*/
/**@brief  PC�����PC���������񴴽�
   @param  priv��������������ָ��
   @return ��
   @note   static void pc_task_init(void *priv)
*/
/*----------------------------------------------------------------------------*/
static void pc_task_init(void *priv)
{
    u32 err;

    //��ʼ��PC����
	err = os_task_create(pc_task,
			(void*)0,
			TaskPcPrio,
			10
#if OS_TIME_SLICE_EN > 0
			,1
#endif
			,PC_TASK_NAME);

    //��ʼ������������
    pc_card_task_init(NULL);

    //����ӳ��
    if(OS_NO_ERR == err)
    {
      #if KEY_IO_EN
	    key_msg_register(PC_TASK_NAME, adkey_msg_usb_table, iokey_msg_usb_table, irff00_msg_usb_table, NULL);
	 #elif LED_KEY_MAX
	 #if KEY_AD_EN
	        key_msg_register(PC_TASK_NAME, usb_led_table,adkey_msg_usb_table, NULL, irff00_msg_usb_table, NULL);	 
	 #else
      	  key_msg_register(PC_TASK_NAME, adkey_msg_usb_table, NULL, irff00_msg_usb_table, NULL);
	 #endif   
      #else
        key_msg_register(PC_TASK_NAME, adkey_msg_usb_table, NULL, irff00_msg_usb_table, NULL);
      #endif
    }
}


/*----------------------------------------------------------------------------*/
/**@brief  PC ����ɾ���˳�
   @param  ��
   @return ��
   @note   static void pc_task_exit(void)
*/
/*----------------------------------------------------------------------------*/
static void pc_task_exit(void)
{
	if (os_task_del_req(PC_TASK_NAME) != OS_TASK_NOT_EXIST)
	{
		os_taskq_post_event(PC_TASK_NAME, 1, SYS_EVENT_DEL_TASK);
		do
		{
			OSTimeDly(1);
		}while(os_task_del_req(PC_TASK_NAME) != OS_TASK_NOT_EXIST);
		pc_puts("del_pc_task: succ\n");
	}
}


/*----------------------------------------------------------------------------*/
/**@brief  PC ������Ϣ
   @note   const struct task_info pc_task_info
*/
/*----------------------------------------------------------------------------*/
TASK_REGISTER(pc_task_info) = {
	.name = PC_TASK_NAME,
	.init = pc_task_init,
	.exit = pc_task_exit,
};
#endif
