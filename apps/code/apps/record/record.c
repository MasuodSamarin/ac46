#include "includes.h"
#include "config.h"
#include "app_cfg.h"
#include "msg.h"
#include "task_manage.h"
#include "play_sel.h"
#include "sd_host_api.h"
#include "rec_key.h"
#include "mp2_encode_api.h"
#include "record.h"
#include "encode.h"
#include "dac_api.h"
#include "ui_api.h"
#include "dev_write_api.h"
#include "led.h"
#include "music.h"
#include "fm_radio.h"
#include "linein.h"
#ifdef AFTER_RECORD_PLAY_LAST_RECORDED_FILE
extern u8 bExitRecordModePlayLastRecordedFileFlag;
#endif
#ifdef FM_AUX_BT_START_REC_KEY_SECOND_PRESS_STOP_REC
u8 bFmAuxBtRecordCnt=0;
#endif
extern void *malloc_fun(void *ptr,u32 len,char *info);
extern void free_fun(void **ptr);
extern volatile u8 new_lg_dev_let;

#if REC_EN

#define REC_FILE    1  //1：录MP3文件       0：录WAV文件

const u16 enc_bitrate_h[]=
{
    ///>(44100), (48000), (32000) 采样率可配置以下比特率
    32,48,56,64,80,96,112,128
};
const u16 enc_bitrate_l[]=
{
    ///>(44.1K/2,/4),  (48k/2,/4),  (32K/2,/4) 采样率可配置以下比特率
    8,16,24,32,40,48,56,64,80,96,112,128
};
#ifdef MODIFY_REC_FILE_NAME_FOR_ZY
char rec_folder_name[] = "/JLREC";                   //录音文件夹  //仅支持一层目录

#if REC_FILE
    char rec_file_name[] =   "/JLREC/REC0000.MP3";      //MP3录音文件名（含路径）
#else
    char rec_file_name[] =   "/JLREC/REC0000.WAV";      //ADPCM录音文件名（含路径）
#endif
#else
char rec_folder_name[] = "/JL_REC";                   //录音文件夹  //仅支持一层目录

#if REC_FILE
    char rec_file_name[] =   "/JL_REC/AC460000.MP3";      //MP3录音文件名（含路径）
#else
    char rec_file_name[] =   "/JL_REC/AC460000.WAV";      //ADPCM录音文件名（含路径）
#endif
#endif
u32 rec_fname_cnt;       //录音文件名计数
u32 rec_total_number;    //录音文件数计数

REC_CTL *g_rec_ctl = NULL;


/*----------------------------------------------------------------------------*/
/**@brief  蓝牙录音数据源获取
   @param  无
   @return 无
   @note   void bt_rec_get_data(s16 *buf,u32 len,u8 type)//录音获取pcm数据函数
*/
/*----------------------------------------------------------------------------*/
void bt_rec_get_data(s16 *buf,u32 len,u8 type)//录音获取pcm数据函数
{
    u8 point;
    static s16 bt_buf[64];

    if(p_ladc == NULL)
    {
        return;
    }

    if(p_ladc->source_chl == ENC_BT_CHANNEL)
    {
        if(type == 0)
        {
            memcpy(bt_buf,buf,sizeof(bt_buf));
        }
        else
        {
            for(point = 0; point<64; point++)//输入输出并
            {
                bt_buf[point]+=buf[point];
            }

            if(p_ladc->save_ladc_buf)
            {
                p_ladc->save_ladc_buf((void *)p_ladc, bt_buf, 0 ,len*2);//bt通话只录一个通道
                //p_ladc->save_ladc_buf((void *)p_ladc, bt_buf, 1 ,len*2);
            }
        }
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  ENCODE 模式提示音播放
   @param  无
   @return 无
   @note   void enc_tone_play(void)
*/
/*----------------------------------------------------------------------------*/
void enc_tone_play(void)
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
#ifdef support_rec_recplay_notice	

#ifdef SUPPORT_DOUBLE_VOICE
	 #ifdef SUPPORT_ZY_SA_VOICE
		if(IsVoiceEnable==2)
	            psel_p->file_number[0] = BPF_REC_MP3_EN;
		else
	#endif
#endif	
            psel_p->file_number[0] = BPF_REC_MP3;
		
#endif
        }
        else
        {
            free_fun((void**)&psel_p);
        }
    }
    b_res = play_sel(REC_TASK_NAME, 'A', psel_p);
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
/**@brief  录音通道初始化、文件初始化
   @param  无
   @return 无
   @note   RECORD_OP_API * rec_init(void)
*/
/*----------------------------------------------------------------------------*/
RECORD_OP_API * rec_init(u8 mode)
{
    s16 ret;
    u32 rec_file_num;
    RECORD_OP_API * rec_op_api;

    rec_op_api = malloc(sizeof(RECORD_OP_API));
    ASSERT(rec_op_api);
    memset(rec_op_api,0x00,sizeof(RECORD_OP_API));

    rec_op_api->fop_api = fop_api_init();   //文件操作信息初始化
    printf("-------fop_api_init %x------\n",rec_op_api->fop_api);

    rec_op_api->fw_api = fw_api_init();     //读写接口初始化
    printf("------fw_api_init %x------\n",rec_op_api->fw_api);

    puts("------encode_fs_open-----\n");
    ret = encode_fs_open(rec_op_api, DEV_SEL_SPEC, new_lg_dev_let, rec_folder_name, FA_CREATE_NEW);  //初始化文件系统
    printf("--encode_fs_open ret = %x  \n",ret);

    if(-FILE_OP_ERR_LGDEV_NO_FIND == ret)
    {
        printf("--DEV_SEL_FIRST--\n");
        ret = encode_fs_open(rec_op_api, DEV_SEL_FIRST, new_lg_dev_let, rec_folder_name, FA_CREATE_NEW);  //初始化文件系统
    }

    if(ret == FR_EXIST)
    {
#if REC_FILE
        encode_get_fileinfo(rec_op_api,rec_folder_name,"MP3",&rec_file_num, &rec_total_number);
#else
        encode_get_fileinfo(rec_op_api,rec_folder_name,"WAV",&rec_file_num, &rec_total_number);
#endif
        printf("rec_total_number = %d\n",rec_total_number);
        printf("rec_file_num = %d\n",rec_file_num);
        rec_fname_cnt = rec_file_num+1;

        if((rec_fname_cnt >= 9999)&&(rec_total_number >= 9999))//以超出可使用文件名数
        {
            goto _err_exit;
        }
    }
    else if(ret != FR_OK)//初始化失败，释放资源
    {
        printf("rec_folder_creater fail,ret = %d\n",ret);
        goto _err_exit;
    }
    else
    {
        printf("rec_folder_creater succ\n");
        rec_fname_cnt = 0;       //文件夹不存在，文件数清零
    }

    puts("----enc_run_creat----\n");
    enc_run_creat();        //创建录音线程

    puts("----rec_enc_init----\n");
    if(mode == ENC_MIC_CHANNEL)
    {
#if REC_FILE
        rec_op_api->rec_ctl = init_enc(rec_op_api, mode, enc_bitrate_h[7], LADC_SR48000, MP2_FORMAT); //申请录音资源并启动录音
#else
        rec_op_api->rec_ctl = init_enc(rec_op_api, mode, 1024, LADC_SR48000, ADPCM_FORMAT); //申请录音资源并启动录音
#endif
    }
    else if(mode == ENC_FM_CHANNEL)
    {
        ///FM录音必须32K采样率
#if REC_FILE
        rec_op_api->rec_ctl = init_enc(rec_op_api, mode, enc_bitrate_h[7], LADC_SR32000, MP2_FORMAT); //申请录音资源并启动录音
#else
        rec_op_api->rec_ctl = init_enc(rec_op_api, mode, 1024, LADC_SR32000, ADPCM_FORMAT); //申请录音资源并启动录音
#endif
    }
    else if(mode == ENC_DAC_CHANNEL)
    {
#if REC_FILE
        rec_op_api->rec_ctl = init_enc(rec_op_api, mode, enc_bitrate_h[7], LADC_SR48000, MP2_FORMAT); //申请录音资源并启动录音
#else
        rec_op_api->rec_ctl = init_enc(rec_op_api, mode, 1024, LADC_SR48000, ADPCM_FORMAT); //申请录音资源并启动录音
#endif
    }
    else if(mode == ENC_BT_CHANNEL)
    {
        ///蓝牙通话录音必须8K采样率
#if REC_FILE
        rec_op_api->rec_ctl = init_enc(rec_op_api, mode, enc_bitrate_l[5], LADC_SR8000, MP2_FORMAT); //申请录音资源并启动录音
#else
        rec_op_api->rec_ctl = init_enc(rec_op_api, mode, 1024, LADC_SR8000, ADPCM_FORMAT); //申请录音资源并启动录音
#endif
    }
    g_rec_ctl = rec_op_api->rec_ctl;

    printf("----rec_op_api %x----\n",rec_op_api);
    return rec_op_api;

_err_exit:
    printf("----err_exit----\n");
    encode_fs_close(rec_op_api);
    printf("----encode_fs_close----\n");
    free_fop(rec_op_api);
    printf("----free_fop----\n");
    free(rec_op_api);
    printf("----return NULL;----\n");
    return NULL;
}

void start_rec(RECORD_OP_API ** rec_api)
{
    RECORD_OP_API * rec_op_api;
    s16 ret;
    u16 err_cnt;
    u32 tmp;

    if(!rec_api)
        return;

    rec_op_api = *rec_api;

    err_cnt = 0;    //err_reset

_get_file_name:

    if(rec_fname_cnt > 9999)
    {
        rec_fname_cnt = 0;
    }
#ifdef MODIFY_REC_FILE_NAME_FOR_ZY
	tmp = rec_fname_cnt/1000;
	rec_file_name[10] = (char)(tmp+'0');

	tmp = rec_fname_cnt%1000/100;
	rec_file_name[11] = (char)(tmp+'0');

	tmp = rec_fname_cnt%100/10;
	rec_file_name[12] = (char)(tmp+'0');

	tmp = rec_fname_cnt%10;
	rec_file_name[13] = (char)(tmp+'0');
#else
    tmp = rec_fname_cnt/1000;
    rec_file_name[12] = (char)(tmp+'0');

    tmp = rec_fname_cnt%1000/100;
    rec_file_name[13] = (char)(tmp+'0');

    tmp = rec_fname_cnt%100/10;
    rec_file_name[14] = (char)(tmp+'0');

    tmp = rec_fname_cnt%10;
    rec_file_name[15] = (char)(tmp+'0');
#endif
    printf("--encode_file_open %s--\n",rec_file_name);
    ret = encode_file_open(rec_op_api,rec_file_name,FA_CREATE_NEW|FA_WRITE);  //初始化文件
    if(FR_OK == ret)//文件创建成功
    {
        music_ui.ui_curr_device = (u32)file_operate_ctl(FOP_GET_PHYDEV_INFO,rec_op_api->fop_api,0,0);
        printf("--start_rec-- device %d--- \n",music_ui.ui_curr_device);
        rec_op_api->rec_ctl->file_info.file_del_size = 1; ///0:不自动删除文件 , 非0:删除文件 删除成功自动归0
        os_taskq_post_msg(ENC_RUN_TASK_NAME, 1, rec_op_api); //启动录音
        while(rec_op_api->rec_ctl->enable != ENC_STAR)//等待录音启动线程
        {
            os_time_dly(1);
        }
    }
    else if(FR_EXIST == ret)////文件以存在
    {
        printf("--%s__FR_EXIST--\n",rec_file_name);

        err_cnt++;
        if(err_cnt >= 9999)
        {
            printf("file_open err 9999\n");
            exit_rec_api(rec_api); //停止录音和释放资源
#ifdef FM_AUX_BT_START_REC_KEY_SECOND_PRESS_STOP_REC
			bFmAuxBtRecordCnt=0;
#endif
        }

        rec_fname_cnt++;
        goto _get_file_name;
    }
    else//其他错误
    {
        printf("file_open ret :%x\n",ret);
        exit_rec_api(rec_api); //停止录音和释放资源
#ifdef FM_AUX_BT_START_REC_KEY_SECOND_PRESS_STOP_REC
			 bFmAuxBtRecordCnt=0;
#endif
    }
}
#ifdef SUPPORT_REC_STOP_PLAY_REC_FILE
bool aux_fm_rec_sw;
#endif
void rec_msg_del(RECORD_OP_API ** rec_api_p, int *msg)
{
    switch(msg[0])
    {
        case MSG_REC_START:
            puts("MSG_REC_START\n");
			
	  #ifdef SUPPORT_REC_STOP_PLAY_REC_FILE
	  
	      if((g_rec_ctl)&&(ENC_STOP != g_rec_ctl->enable))
	      	{
	  		stop_rec(*rec_api_p); //停止录音和释放资源
	  		rec_fname_cnt++;//录音文件名序号
	  		(*rec_api_p)->rec_ctl->lost_frame.black_lost_frame = 0;
	  		(*rec_api_p)->rec_ctl->lost_frame.front_lost_frame = 0;
	  		UI_menu(MENU_MAIN);
	  
	  		 	play_rec_last_file=1;   
	  	         os_taskq_post("MainTask", 1, MSG_ONE_KEY_TO_MP3);
	  			
	  		break;
	      	}
	  	
	  #ifdef support_rec_recplay_notice	
	   if((compare_task_name(FM_TASK_NAME))||(compare_task_name(LINEIN_TASK_NAME)))
	   	{
	  	  if(aux_fm_rec_sw==0)
	  	  	{
	  	 	   aux_fm_rec_sw=1;
	  	 	    enc_tone_play(); //ENCODE模式提示音播放	 	    
	  	  	}	    
	   	}
	  #endif 
	  
	  #endif 

         #ifdef FM_AUX_BT_START_REC_KEY_SECOND_PRESS_STOP_REC
			  bFmAuxBtRecordCnt++;
         #endif
         #if LED_SHOW_REC
		 #ifdef SUPPORT_RECORD_MODE_LED_ON
		     	setLedLight(LED_SHOW_REC,led_mode_on,0);
		 	 setLedLight(LED_SHOW_MP3,led_mode_off,0);
		#else		 
	         setLedLight(LED_SHOW_REC,led_mode_flash_fast,0);
		 #endif		
         #endif
          //  led7_show_rec();
            if(*rec_api_p == NULL)
            {
                printf("curr_task_name %s\n",curr_task->name);

                if(compare_task_name(REC_TASK_NAME))
                    *rec_api_p = rec_init(ENC_MIC_CHANNEL);
                else if(compare_task_name(FM_TASK_NAME))
                    *rec_api_p = rec_init(ENC_FM_CHANNEL);
                else if(compare_task_name(LINEIN_TASK_NAME))
                    *rec_api_p = rec_init(ENC_DAC_CHANNEL);
                else if(compare_task_name("BtStackTask"))
                    *rec_api_p = rec_init(ENC_BT_CHANNEL);
                else
                    *rec_api_p = NULL;//err
            }

            if(*rec_api_p)
            {
                if((*rec_api_p)->rec_ctl->enable == ENC_STOP)
                {
                    puts("start_rec\n");
                    start_rec(rec_api_p); //启动录音
                }
            }
			
            #ifdef FM_AUX_BT_START_REC_KEY_SECOND_PRESS_STOP_REC
            if(*rec_api_p){              
			  if((*rec_api_p)->rec_ctl->enable != ENC_STOP){              
             if(compare_task_name(FM_TASK_NAME)||compare_task_name(LINEIN_TASK_NAME)||compare_task_name("BtStackTask"))
             {
                if(bFmAuxBtRecordCnt==2){
                bFmAuxBtRecordCnt=0;
                 if(compare_task_name(LINEIN_TASK_NAME))
				 os_taskq_post_msg(LINEIN_TASK_NAME, 1, MSG_REC_STOP); 
				 else if(compare_task_name(FM_TASK_NAME))
					 os_taskq_post_msg(FM_TASK_NAME, 1, MSG_REC_STOP);
				 else if(compare_task_name("BtStackTask"))
					 os_taskq_post_msg("BtStackTask", 1, MSG_REC_STOP); 
				 }
             }
            }
           }
            #endif
            break;

        case MSG_REC_PP:
            if(*rec_api_p)
            {
                if((*rec_api_p)->rec_ctl->enable == ENC_STAR)
                {
                    (*rec_api_p)->rec_ctl->enable = ENC_PAUS;
                    puts("enc_pause\n");
                   #if LED_SHOW_REC
					setLedLight(LED_SHOW_REC,led_mode_on,0);
                   #endif
                }
                else if((*rec_api_p)->rec_ctl->enable == ENC_PAUS)
                {
                    (*rec_api_p)->rec_ctl->enable = ENC_STAR;
                    puts("enc_star\n");
                 #if LED_SHOW_REC
					setLedLight(LED_SHOW_REC,led_mode_flash_fast,0);
                 #endif
                }
                else
                {
                    puts("--MSG_ENCODE_PP_err\n");
                }
            }
            break;

        case MSG_ENCODE_ERR:
            enc_puts("--REC_MSG_ENCODE_ERR\n");
            if(*rec_api_p)
            {
                exit_rec_api(rec_api_p); //停止录音和释放资源
           #ifdef FM_AUX_BT_START_REC_KEY_SECOND_PRESS_STOP_REC
			bFmAuxBtRecordCnt=0;
           #endif
          #if LED_SHOW_REC
		   setLedLight(LED_SHOW_REC,led_mode_off,0);
          #endif
            }
            break;

        case MSG_REC_STOP:
            puts("--REC_MSG_REC_STOP\n");
            if(*rec_api_p)
            {
                stop_rec(*rec_api_p); //停止录音和释放资源
                rec_fname_cnt++;//录音文件名序号
                (*rec_api_p)->rec_ctl->lost_frame.black_lost_frame = 0;
                (*rec_api_p)->rec_ctl->lost_frame.front_lost_frame = 0;
            }
            UI_menu(MENU_MAIN);
         #if LED_SHOW_REC
			setLedLight(LED_SHOW_REC,led_mode_off,0);
         #endif
       #ifdef SUPPORT_REC_STOP_PLAY_REC_FILE
		         play_rec_last_file=1;          
       #endif
            break;

        case SYS_EVENT_DEV_OFFLINE:
            enc_puts("--enc_SYS_EVENT_DEV_OFFLINE--\n");
            if(*rec_api_p)
            {
                enc_puts("DEV_OFFLINE-00\n");
                if((*rec_api_p)->fop_api->cur_lgdev_info->lg_hdl->phydev_item == msg[1])
                {
                    enc_puts("DEV_OFFLINE-01\n");
                    exit_rec_api(rec_api_p); //停止录音和释放资源
                }
                else
                {   ///<非解码设备，删除该逻辑设备
                    enc_puts("DEV_OFFLINE-02\n");
                    break;
                }

       #ifdef SUPPORT_REC_STOP_PLAY_REC_FILE
		         play_rec_last_file=1;          
       #endif
				
             #ifdef FM_AUX_BT_START_REC_KEY_SECOND_PRESS_STOP_REC
				  bFmAuxBtRecordCnt=0;
             #endif
            }
        #if LED_SHOW_REC
			setLedLight(LED_SHOW_REC,led_mode_off,0);
        #endif
            break;

        default:
            break;
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  ENCODE 控制任务
   @param  p：任务间参数传递指针
   @return 无
   @note   static void encode_task(void *p)
*/
/*----------------------------------------------------------------------------*/
static void rec_task(void *p)
{
    int msg[3];
    RECORD_OP_API * rec_mic_api = NULL;
    #if UI_ENABLE
	SET_UI_MAIN(MENU_RECODE_MAIN);//显示REC
	UI_menu(MENU_RECODE_MAIN);	
	os_time_dly(150);
	#endif
	
   #ifdef SUPPORT_REC_STOP_PLAY_REC_FILE
   	aux_fm_rec_sw=0;
   #endif
   
#ifdef LED_SHOW_REC	
#ifdef SUPPORT_RECORD_MODE_LED_ON
    	setLedLight(LED_SHOW_REC,led_mode_on,0);
	 setLedLight(LED_SHOW_MP3,led_mode_off,0);
#endif
#endif

    enc_puts("\n************************ENCODE TASK********************\n");

	 #ifdef SUPPORT_ZY_SA_VOICE
	 	if(IsVoiceEnable)
	     {
			enc_tone_play(); //ENCODE模式提示音播放
	     }
	     else
	     {
	     	os_taskq_post(REC_TASK_NAME, 1, SYS_EVENT_PLAY_SEL_END);	 
	     }
	 #else	
   		 enc_tone_play(); //ENCODE模式提示音播放
	  #endif
   

    while(1)
    {
        os_taskq_pend(0, ARRAY_SIZE(msg), msg);
        switch(msg[0])
        {
        case SYS_EVENT_DEL_TASK:
            enc_puts("ENCODE_SYS_EVENT_DEL_TASK\n");
            if (os_task_del_req_name(OS_TASK_SELF) == OS_TASK_DEL_REQ)
            {
                UI_menu(MENU_WAIT);
                exit_rec(&rec_mic_api); //停止录音和释放资源
                play_sel_stop();   //关闭提示音
                os_task_del_res_name(OS_TASK_SELF);
            }
            break;

        case SYS_EVENT_PLAY_SEL_END: //提示音结束
            enc_puts("ENCODE_SYS_EVENT_PLAY_SEL_END\n");
            play_sel_stop(); //关闭提示音
            enc_puts("ENC_play_tone_end\n");            
          #ifdef ENTER_INTO_REC_MODE_AUTO_START_REC
			os_taskq_post_msg(REC_TASK_NAME, 1, MSG_REC_START); //触发AUX模块初始化
		  #endif
        case MSG_REC_INIT:
            enc_puts("MSG_REC_INIT\n");
            SET_UI_MAIN(MENU_RECODE_MAIN);//显示REC
            UI_menu(MENU_RECODE_MAIN);
            break;

        case MSG_HALF_SECOND:
            updata_enc_time(rec_mic_api);
            UI_menu(MENU_MAIN);
            UI_menu(MENU_HALF_SEC_REFRESH);
            #if UI_ENABLE
            led7_show_rec_main();
            #endif
			
	 #ifdef SUPPORT_REC_STOP_PLAY_REC_FILE
	     if(play_rec_last_file)
	    	{
	         play_rec_last_file=1;   
	         os_taskq_post("MainTask", 1, MSG_ONE_KEY_TO_MP3);
		   break;
	 	}
	 #endif 
			
            break;

        default:
            rec_msg_del(&rec_mic_api, msg);
            break;
        }
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  ENCODE任务创建
   @param  priv：任务间参数传递指针
   @return 无
   @note   static void encode_task_init(void *priv)
*/
/*----------------------------------------------------------------------------*/
static void rec_task_init(void *priv)
{
    u32 err;

    //初始化ENCODE APP任务
    err = os_task_create(rec_task,
                         (void*)0,
                         TaskEncodePrio,
                         30
#if OS_TIME_SLICE_EN > 0
                         ,1
#endif
                         ,REC_TASK_NAME);

    //按键映射
    if(OS_NO_ERR == err)
    { 
      #if KEY_IO_EN
	    key_msg_register(REC_TASK_NAME, adkey_msg_rec_table, iokey_msg_rec_table, irff00_msg_rec_table, NULL);
      #else
        key_msg_register(REC_TASK_NAME, adkey_msg_rec_table, NULL, irff00_msg_rec_table, NULL);
      #endif
    }
#ifdef AFTER_RECORD_PLAY_LAST_RECORDED_FILE
 bExitRecordModePlayLastRecordedFileFlag=FALSE;
#endif
#ifdef FM_AUX_BT_START_REC_KEY_SECOND_PRESS_STOP_REC
	 bFmAuxBtRecordCnt=0;
#endif

}


/*----------------------------------------------------------------------------*/
/**@brief  ENCODE 任务删除退出
   @param  无
   @return 无
   @note   static void encode_task_exit(void)
*/
/*----------------------------------------------------------------------------*/
static void rec_task_exit(void)
{
    if (os_task_del_req(REC_TASK_NAME) != OS_TASK_NOT_EXIST)
    {
        os_taskq_post_event(REC_TASK_NAME, 1, SYS_EVENT_DEL_TASK);
        do
        {
            OSTimeDly(1);
        }
        while(os_task_del_req(REC_TASK_NAME) != OS_TASK_NOT_EXIST);
        enc_puts("del_encode_task: succ\n");
    }
#if LED_SHOW_REC
	setLedLight(LED_SHOW_REC,led_mode_off,0);
#endif
}


/*----------------------------------------------------------------------------*/
/**@brief  ENCODE 任务信息
   @note   const struct task_info rec_task_info
*/
/*----------------------------------------------------------------------------*/
TASK_REGISTER(rec_task_info) =
{
    .name = REC_TASK_NAME,
    .init = rec_task_init,
    .exit = rec_task_exit,
};
#endif
