
#include "play_sel.h"
#include "app_cfg.h"
#include "os_api.h"
#include "os_cfg.h"
#include "error.h"
#include "mango_dev_sd.h"
#include "system_cfg.h"
#include "stdarg.h"
#include "msg.h"
#include "task_manage.h"
#include "music_api.h"
#include "dac_api.h"


#define PLAY_SEL_TASK_NAME      "play_sel"
#define PLAY_SEL_DEC_PHY_NAME   "play_sel_phy"


const struct task_info play_sel_task_info;

void play_sel_stop_decoder(_MUSIC_API *mapi,_PLAY_SEL_API *psel)
{
    dsel_printf("dec sel stop\r");
    stop_decoder(&mapi->dec_api);

    if(psel->busy)
    {
        dsel_printf("psel busy\r");
        if(psel->file_par)
        {
            free_fun((void**)&psel->file_par->file_number);
            free_fun((void**)&psel->file_par);
        }
        psel->busy = 0;
        if(NULL != psel->father_name)
        {
            os_taskq_post_event((char *)psel->father_name, 1, SYS_EVENT_PLAY_SEL_END);
        }
    }
    else
    {
        dsel_printf("psel idle\r");
    }

}

extern void *sup_dec_phy_op(void *priv  ,void *data, u32 len);
static void play_sel_task(void *p)
{
    u32 err;
    tbool flag = 0;
	int msg[3];
	u32 file_cnt = 0;
	u32 rpt_time = 0;
	msg[0] = 0;
    _PLAY_SEL_API *psel = p;
//    _MUSIC_API *mapi = NULL;
    MUSIC_OP_API *mapi=NULL;
    tbool enable = 1;

    mapi = malloc_fun(mapi,sizeof(MUSIC_OP_API),0);
    if(NULL == mapi)
    {
        while(1);
    }
    dsel_printf("PLAY SEL TASK\r");
    /*-------解码接口资源申请----------------*/
    mapi->dop_api=malloc_fun(mapi->dop_api,sizeof(_MUSIC_API),0);
    if(NULL == mapi->dop_api)
    {
        dsel_printf("malloc mapi->dop_api fail\r");
        psel->busy = 0;
        goto __run_loop_psel;
    }

    /*-------文件操作器资源申请--------------*/
    mapi->fop_api = (void*)malloc_fun(mapi->fop_api,sizeof(FILE_OPERATE),0);
    if(NULL==mapi->fop_api)
    {
        dsel_printf(" if(NULL==mapi->fop_api) \r\n");
        while(1);
    }
    mapi->dop_api->dec_api.format_name = 0;//"WAVWMAMP3";
#ifdef AC46_512K
    mapi->dop_api->dec_api.type_enable |=  DEC_PHY_MP3;//使能响应的解码库
    mapi->dop_api->file_type = "MP3";
#else
    mapi->dop_api->dec_api.type_enable |= DEC_PHY_WAV | DEC_PHY_MP3;//使能响应的解码库
    mapi->dop_api->file_type = "WAVWMAMP3";
#endif

    mapi->dop_api->dec_api.dec_phy_name = PLAY_SEL_DEC_PHY_NAME;

    dsel_printf("build dec phy\r");
    dsel_printf("mapi  2=%08x  \n",(u32)mapi);
    err = os_task_create(decoder_phy_task, 0, TaskPselPhyDecPrio, 50, mapi->dop_api->dec_api.dec_phy_name);
    if(OS_NO_ERR != err)
    {
        dsel_printf("build dec phy fail %02x\r",err);
        psel->busy = 0;
        goto __run_loop_psel;
    }
    if(NULL == mapi->dop_api->io)
    {
        mapi->dop_api->io = (void *)malloc_fun(mapi->dop_api->io,sizeof(DEC_API),0);
        if(NULL == mapi->dop_api->io)
        {
            //dsel_printf(" if(NULL == mapi->dec_io) \r\n");
            psel->busy = 0;
            dsel_printf("malloc mapi->dop_api->io fail\r");
            goto __run_loop_psel;
        }
    }
    /*-------文件操作器初始化信息资源申请--------------*/
	mapi->fop_api->fop_init = (void*)malloc_fun(mapi->fop_api->fop_init,sizeof(FILE_OPERATE_INIT),0);
    if(mapi->fop_api->fop_init==NULL)
    {
        dsel_printf("mem err fop_init \n");
        goto __run_loop_psel;
    }
    mapi->dop_api->file_num = (u32)psel->file_par;
    rpt_time = psel->file_par->rpt_time ;
    mapi->dop_api->io->father_name = PLAY_SEL_TASK_NAME;//解码结束的消息返回给谁
	msg[0] = SYS_EVENT_BEGIN_DEC;
	flag = 1;
	

    dac_channel_on(MUSIC_CHANNEL, FADE_OFF);
    #if NOTICE_VOICE_VOL_DEFAULT
    set_sys_vol(NOTICE_VOICE_VOL_DEFAULT, NOTICE_VOICE_VOL_DEFAULT, FADE_OFF);
    #else
    set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);
    #endif
             #ifdef SUPPORT_MUTE_FLASH
		   if(b_muteFlag)
			dac_mute(0,1);
             #endif

	while(1)
	{
__run_loop_psel:
        err = 0;
		if(!flag)
		{
            dsel_printf("play sel pend\r");
            os_taskq_pend(0, ARRAY_SIZE(msg), msg);
            dsel_printf("play sel pend~\r");
		}
		flag = 0;
        if((!enable) && (SYS_EVENT_DEL_TASK != msg[0]))
        {
            continue;
        }
        switch(msg[0])
		{
		    case SYS_EVENT_BEGIN_DEC:
                if ((psel->file_par) && (file_cnt < psel->file_par->max_file_number))
                {
                    mapi->dop_api->file_num = psel->file_par->file_number[file_cnt];
                    dsel_printf("file A :%08x\r",mapi->dop_api->file_num);
                    err = music_play(mapi,DEV_SEL_SPEC,psel->device_sel,PLAY_SPEC_FILE,&mapi->dop_api->file_num);
                }
                else
                {
                    play_sel_stop_decoder(mapi->dop_api,psel);
                }
                break;
            case SYS_EVENT_DEC_FR_END:
            case SYS_EVENT_DEC_FF_END:
            case SYS_EVENT_DEC_END:

             #ifdef SUPPORT_MUTE_FLASH
		   if(b_muteFlag)
			dac_mute(1,1);
             #endif
				
                dsel_printf("SYS_EVENT_DEC_END\r");
                if(NULL == psel->file_par)
                {
                    break;
                }
                file_cnt++;
                if (file_cnt < psel->file_par->max_file_number)
                {
                    OSTimeDly(psel->file_par->delay);
                    mapi->dop_api->file_num = psel->file_par->file_number[file_cnt];
                    dsel_printf("file B : %08x %08x\r",psel->device_sel,mapi->dop_api->file_num);
                    err = music_play(mapi,DEV_SEL_CUR,psel->device_sel,PLAY_SPEC_FILE,&mapi->dop_api->file_num);
                }
                else
                {
                    tbool rpt;
                    rpt = 0;
                    if(0 == psel->file_par->rpt_time)
                    {
                        rpt = 1;
                    }
                    if(rpt_time)
                    {
                        rpt_time--;
                        if(rpt_time)
                        {
                            rpt = 1;
                        }
                    }
                    if(rpt)
                    {
                        file_cnt = 0;
                        OSTimeDly(psel->file_par->delay);
                        mapi->dop_api->file_num = psel->file_par->file_number[file_cnt];
                        dsel_printf("file C :%08x\r",mapi->dop_api->file_num);
                        err = music_play(mapi,DEV_SEL_CUR,psel->device_sel,PLAY_SPEC_FILE,&mapi->dop_api->file_num);
                    }
                    else
                    {
                        play_sel_stop_decoder(mapi->dop_api,psel);
                    }

                }
                break;
            case SYS_EVENT_DEC_DEVICE_ERR:
                play_sel_stop_decoder(mapi->dop_api,psel);
                break;
			case SYS_EVENT_DEL_TASK:
                play_sel_stop_decoder(mapi->dop_api,psel);
                dac_channel_off(MUSIC_CHANNEL, FADE_OFF);
                if(mapi->dop_api->dec_api.dec_phy_name)
                {
                    if (os_task_del_req(mapi->dop_api->dec_api.dec_phy_name) != OS_TASK_NOT_EXIST)
                    {
                        os_taskq_post_event(mapi->dop_api->dec_api.dec_phy_name, 1, SYS_EVENT_DEL_TASK);
                        do
                        {
                            OSTimeDly(1);
                        }while(os_task_del_req(mapi->dop_api->dec_api.dec_phy_name) != OS_TASK_NOT_EXIST);
                        mapi->dop_api->dec_api.dec_phy_name = NULL;
                        // puts("del music dec phy succ\n");
                    }
                }
				enable = 0;
				///<释放文件操作器初始化信息
                free_fun((void**)&mapi->fop_api->fop_init);
                free_fun((void**)&mapi->fop_api);
				///<关闭文件操作器，释放资源

                free_fun((void**)&mapi->dop_api->io);
                free_fun((void**)&mapi->dop_api);
                free_fun((void**)&mapi);
				if (os_task_del_req_name(OS_TASK_SELF) == OS_TASK_DEL_REQ)
				{
					os_task_del_res_name(OS_TASK_SELF); 	//确认可删除，此函数不再返回
				}

				break;
			default:
                dsel_printf("psel default %08x\r",msg[0]);
				break;
		}
		while(0 != err)
		{
		    if(SUCC_MUSIC_START_DEC == err)
		    {
		        err = 0;
		        break;
		    }
		    dsel_printf("************************\r       psel default %08x\r\n",err);
		    play_sel_stop_decoder(mapi->dop_api,psel);
		    err = 0;
		}

	}
}


static void psel_task_init(void *priv)
{
	u32 err;
	_PLAY_SEL_API *psel = priv;
    psel->alive = 1;
    psel->busy = 1;
	err = os_task_create(play_sel_task, priv, TaskPselPrio, 50, PLAY_SEL_TASK_NAME);
    if(OS_NO_ERR == err)
    {

        dsel_printf("build play sel succ\r");
        //key_msg_register(PLAY_SEL_TASK_NAME,music_ad_table,music_io_table,music_ir_table,NULL);
    }
    else
    {
        psel->alive = 0;
        psel->busy = 0;
        dsel_printf("build play sel fail\r");
    }
}


static void psel_task_exit()
{
	if (os_task_del_req(PLAY_SEL_TASK_NAME) != OS_TASK_NOT_EXIST)
	{
		os_taskq_post_event(PLAY_SEL_TASK_NAME, 1, SYS_EVENT_DEL_TASK);
		do{
			OSTimeDly(1);
		} while(os_task_del_req(PLAY_SEL_TASK_NAME) != OS_TASK_NOT_EXIST);
		// puts("del_music_task: succ\n");
	}

}


TASK_REGISTER(play_sel_task_info) = {
	.name = PLAY_SEL_TASK_NAME,
	.init = psel_task_init,
	.exit = psel_task_exit,
};
_PLAY_SEL_API *psel = NULL;

tbool play_sel(void *name,u32 device_sel,_PLAY_SEL_PARA *file_par)
{
    if(NULL == psel)
    {
        psel = (void *)malloc_fun(psel,sizeof(_PLAY_SEL_API),0);
        if(NULL == psel)
        {
            dsel_printf("play sel fail 00\r");
            return false;
        }
    }
    if(psel->alive)
    {
        dsel_printf("play sel ~play_sel\r");
        psel_task_exit();
        psel->alive = 0;
    }
    if(NULL == file_par)
    {
        return false;
    }
    if(NULL != psel->file_par)
    {
        return false;
    }
	psel->file_par  = (void *)malloc_fun(psel->file_par ,sizeof(_PLAY_SEL_PARA),0);
	if(NULL != psel->file_par )
	{
	    memcpy(psel->file_par,file_par,sizeof(_PLAY_SEL_PARA));
	    psel->file_par->file_number = NULL;
	    psel->file_par->file_number = (u32 *)malloc_fun(psel->file_par->file_number,file_par->max_file_number*4,0);
	    if(NULL != psel->file_par->file_number)
	    {
	        memcpy(psel->file_par->file_number,file_par->file_number,file_par->max_file_number*4);
	    }
	    else
	    {
	        free_fun((void**)&psel->file_par);
            return false;
	    }
	}
	else
	{
        return false;
	}
    dsel_printf("play sel a\r");
    psel->device_sel = device_sel;
    //psel->file_par = file_par;
    psel->father_name = name;
    psel_task_init(psel);
    if(0 == psel->alive)
    {
        free_fun((void**)&psel->file_par->file_number);
        free_fun((void**)&psel->file_par);
    }
    return true;
}
tbool play_sel_busy(void)
{
    if(NULL == psel)
    {
        return 0;
    }
    return psel->busy;
}

tbool play_sel_stop(void)
{
    if(NULL == psel)
    {
        return true;
    }
    if(psel->alive)
    {
        dsel_printf("play sel ~\r");
        psel_task_exit();
        psel->alive = 0;
    }
    return true;
}

