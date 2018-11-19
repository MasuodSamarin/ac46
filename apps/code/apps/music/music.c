#include "app_cfg.h"
#include "os_api.h"
#include "os_cfg.h"
#include "error.h"
#include "mango_dev_sd.h"
//#include "decoder.h"
#include "system_cfg.h"
#include "stdarg.h"
#include "music.h"
#include "msg.h"
#include "task_manage.h"
#include "music_key.h"
#include "music_api.h"
#include "vm_api.h"
#include "play_sel.h"
#include "dac_api.h"
#include "audio_ef_parm.h"
#include "drv_manage.h"
#include "ui_api.h"
#include "led.h"
#include "key.h"
#include "ef_api.h"
#include "music_prompt.h"
#include "music_info.h"
#include "led7_drv.h"
#ifdef SUPPORT_PT2313
#include "pt2313.h"
#endif
#if REC_EN
    #include "tff.h"
    #include "fs_io.h"
#endif
#ifdef EXIT_BLUE_MODE_DISCONNECT_VOICE
extern bool	prev_task_is_blue;
#endif
#if IR_NUM_INPUT_EN
extern u8 ir_num_timeout_cnt;
#endif
#ifdef DURING_FM_EXITING_TASK_NOT_RESPOND_KEY_MSG
extern u8 bExitFMStateCnt;
#endif
#ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE
extern u8 bModeOfAuxContained;
#endif
#ifdef IO_MUTE_DELAY_ALL_STATE
extern u8 bMuteDelayCnt;
#endif
#if LED_SHOW_VOL_MAX
extern u8 bVolMaxChangeToSmallVolMax;
#endif
#ifdef AFTER_RECORD_PLAY_LAST_RECORDED_FILE
extern u8 bExitRecordModePlayLastRecordedFileFlag;
u32 dwLastRecFile=0;
u8 bSendPrevFileCmdCnt=0;
bool bIfRecordFolder=FALSE;
#ifdef SUPPORT_AUX_FM_BT_REPLAY_KEY
u8 bAuxFmBtReplay_cnt=0;
#endif
#endif
#ifdef MUSIC_PROMPT_EN
extern u8 device_file_num;
#endif
#ifdef ONLY_POWER_ON_MUTE
extern u8 bPowerOnMuteCnt;
#endif

#ifdef SUPPORT_MUSIC_INTRO_PLAY
bool mp3_intro_play=FALSE;
u8 bIntro_play_cnt=0;
#endif
#ifdef LED_SHOW_REPEAT_ALL_ONE_FOLDER_NORMAL
u8 repeat_mode=rpt_normal;
#endif
#ifdef EQ_SEQUENCE_ADJ_ANYWAY
#ifdef support_music_eq_default_jazz
u8 eq_sequence_mode=eq_jazz;
#else
u8 eq_sequence_mode=eq_normal;
#endif
#endif
#ifdef SUPPORT_REPLAY_CANCEL_FOLDER_REPEAT_AND_PLAY_NOT_REC_FILES
bool bRecReplayFlag=FALSE;
#endif
#ifdef LED_SHOW_DEL
u8 bLedShowDelCnt;
#endif
#ifdef SUPPORT_REC_STOP_PLAY_REC_FILE
 bool  play_rec_last_file;   
#endif 
#ifdef SUPPORT_LYX_RECPLAY_REPEAT_ONE
bool lyx_recplay_repeat_one_sw;
#endif

#ifdef support_io_det_mute
bool automute_sw;
#endif

#ifdef support_power_on_in_media_pause_state
 u8 media_pause_timer;
#endif

#if REC_EN
extern FS_NAME music_file_name;
#endif
extern void *malloc_fun(void *ptr,u32 len,char *info);
extern void free_fun(void **ptr);
const struct task_info music_task_info;
MUSIC_DIS_VAR music_ui;

bool dec_dev_changed = 0;
extern u8 usb_in_flag;
extern u8 sd_in_flag;
extern u32 try_play_dev(void);

u32 curr_device_using;

const char rpt_str[][7] =
{
    {"ALL"},
    {"FOLDER"},
    {"ONE"},
    {"RANDOM"}
};

#define MUSIC_TONE_NUM 1
#define MUSIC_DEC_PHY_NAME "MusicPhyDec"
#if REC_EN
#ifdef MODIFY_REC_FILE_NAME_FOR_ZY
#define REC_PATH "/JLREC/"
#else
#define REC_PATH "/JL_REC/"
#endif
#endif
extern void *sup_dec_phy_op(void *priv  ,void *data, u32 len);
u8 play_mode = REPEAT_ALL;
#ifdef support_music_eq_default_jazz
u8 eq_mode = 4;
#else
u8 eq_mode = 0;
#endif

#ifdef POWER_ON_KEEP_MUTE_FOR_4S
extern u8 bAmpPowerOnMuteCnt;
#endif

#ifdef SUPPORT_MUSIC_STOP
bool bStop_state=0;
u8 bPause_state=0;
#endif
void music_stop_decoder(MUSIC_OP_API *parm)
{
    _MUSIC_API *mapi;
    mapi=parm->dop_api;
    if(STOP_DEC_GOT_BRKINFO & stop_decoder(&mapi->dec_api))
    {
        file_operate_ctl(FOP_SAVE_BPINFO,parm->fop_api,&mapi->brk->inf,0);
    }
}


u32 music_play_api(MUSIC_OP_API *m_op_api,ENUM_DEV_SEL_MODE dev_sel,u32 dev_let,ENUM_FILE_SELECT_MODE file_sel,void *pra)
{
    u32 err;

    reg_get_id3head(music_get_file_id3);

    err = music_play(m_op_api, dev_sel, dev_let, file_sel, pra);

	
#if 1//UI_ENABLE
    if((err != 0)&&(err != SUCC_MUSIC_START_DEC))
    {
    
        #if !defined LED_SHOW_DEVICE_PLUGIN &&!defined SUPPORT_PLAY_VOICE_NO_SHOW_LOD
		
		UI_menu(MENU_WAIT);
        #endif
		
         printf("=========err======:%d\n",err);

		
    }
    else
    {
        u32 t_fnum;     ///<文件夹总数（根目录为1）
        u32 c_fnum;     ///<当前文件夹编号（根目录为1）
        file_operate_ctl(FOP_GET_FOLDER_INFO,m_op_api->fop_api,&t_fnum,&c_fnum);
         printf("t_fnum = %08x \n",t_fnum);
         printf("c_fnum = %08x \n",c_fnum);
        music_ui.ui_curr_statu = (u32*)&m_op_api->dop_api->dec_api.phy_ops->status;
        music_ui.ui_curr_file = (u32)m_op_api->dop_api->file_num;
        music_ui.ui_total_file =m_op_api->fop_api->cur_lgdev_info->total_file_num;// (u32)file_operate_ctl(FOP_GET_TOTALFILE_NUM,m_op_api->fop_api,m_op_api->dop_api->file_type,0);
        music_ui.ui_curr_device = (u32)file_operate_ctl(FOP_GET_PHYDEV_INFO,m_op_api->fop_api,0,0);

//	printf("-music_play_api--music_ui.ui_curr_file--%d\n",music_ui.ui_curr_file);

        music_file_info(m_op_api);//get_file_info
#ifdef SUPPORT_AUX_FM_BT_REPLAY_KEY
       if(bExitRecordModePlayLastRecordedFileFlag){

	#ifdef support_rec_play_first_mute_after_rec
	   	dac_mute(1,1);
	#endif

	        bExitRecordModePlayLastRecordedFileFlag=FALSE;
			bAuxFmBtReplay_cnt=2;
			
		}

#endif

 	 #ifdef LED_SHOW_REC
	 if(bIfRecordFolder)
	 	{
	 	 	 setLedLight(LED_SHOW_REC,led_mode_flash_slow,0);
	 	 	 setLedLight(LED_SHOW_MP3,led_mode_off,0);
	 	}
	 else
	 	{
	 	 	 setLedLight(LED_SHOW_REC,led_mode_off,0);
	 	 	 setLedLight(LED_SHOW_MP3,led_mode_flash_slow,0);
	 	}	 	
 	 #endif


       #if LED_8NUMS!=7
       #ifdef AFTER_RECORD_PLAY_LAST_RECORDED_FILE
       if(!bSendPrevFileCmdCnt&& !bAuxFmBtReplay_cnt)
       #endif	   
        UI_menu(MENU_FILENUM);
       #endif
    }
#endif
    return err;
}
#if REC_EN
 u32  music_play_by_path_rec(MUSIC_OP_API *mapi)
{
    u32 err;
    u8 *path;
//    path="/folder1/abc.mp3";
#ifdef MODIFY_REC_FILE_NAME_FOR_ZY
     path="/JLREC/";
#else
    path="/JL_REC/";
#endif    
   //   "/R          /"
// path="/JL_REL     /";
    mapi->fop_api->fop_init->filepath=path;
     printf("file path : %s  \n",path);
    mapi->dop_api->file_num= (u32)file_operate_ctl(FOP_GET_TOTALFILE_NUM,mapi->fop_api,0,0);
     mapi->fop_api->fop_init->cur_play_mode = REPEAT_FOLDER;
  // mapi->dop_api->file_num=dwLastRecFile;
  
     bSendPrevFileCmdCnt=2;
    if(mapi->dop_api->file_num){
    //mapi->dop_api->file_num=dwLastRecFile;	
    err = music_play_api(mapi,DEV_SEL_SPEC,0,PLAY_FILE_BYPATH,&(mapi->dop_api->file_num));   
	//err = music_play_api(mapi,DEV_SEL_CUR,0,PLAY_FILE_BYPATH,&(mapi->dop_api->file_num));
    }
    else{
    mapi->dop_api->file_num=1;
	err = music_play_api(mapi,DEV_SEL_SPEC,0,PLAY_FILE_BYPATH,&(mapi->dop_api->file_num));
	}
    return err;
}

 u32  mp3_mode_rec_play_by_path_rec(MUSIC_OP_API *mapi)
{
    u32 err;
    u8 *path;
//    path="/folder1/abc.mp3";
#ifdef MODIFY_REC_FILE_NAME_FOR_ZY
     path="/JLREC/";
#else
    path="/JL_REC/";
#endif    
   //   "/R          /"
// path="/JL_REL     /";
    mapi->fop_api->fop_init->filepath=path;
     printf("file path : %s  \n",path);
    mapi->dop_api->file_num= (u32)file_operate_ctl(FOP_GET_TOTALFILE_NUM,mapi->fop_api,0,0);
    //mapi->dop_api->file_num=dwLastRecFile;
    if(1){
    //if(mapi->dop_api->file_num){
	//if(bIfRecordFolder){
    //mapi->dop_api->file_num=dwLastRecFile;	
 	 #ifdef LED_SHOW_REC	
 	 	 setLedLight(LED_SHOW_REC,led_mode_flash_slow,0);
 	 	 setLedLight(LED_SHOW_MP3,led_mode_off,0);
 	 #endif
	bSendPrevFileCmdCnt=1;
	mapi->fop_api->fop_init->cur_play_mode = REPEAT_FOLDER;
    err = music_play_api(mapi,DEV_SEL_CUR,0,PLAY_FILE_BYPATH,&(mapi->dop_api->file_num));   
    err = music_play_api(mapi,DEV_SEL_SPEC,0,PLAY_FILE_BYPATH,&(mapi->dop_api->file_num));

    if(bIfRecordFolder)
    	{
		play_mode=REPEAT_FOLDER;   	
		mapi->fop_api->fop_init->cur_play_mode = play_mode;
    	}
	else
	{
		play_mode=REPEAT_ALL;   	
		mapi->fop_api->fop_init->cur_play_mode = play_mode;
	}

	
    }
    else{
    mapi->dop_api->file_num=1;
	play_mode=REPEAT_ALL;   		
	mapi->fop_api->fop_init->cur_play_mode = play_mode;
	err = music_play_api(mapi,DEV_SEL_CUR,0,PLAY_NEXT_FILE,&(mapi->dop_api->file_num));	
	}	
    #if 0
    if(err==FILE_OP_ERR_INIT||err==FILE_OP_ERR_OP_HDL||err==FILE_OP_ERR_LGDEV_NULL||err==FILE_OP_ERR_NO_FILE_ALLDEV){
    err=0;
    
	mapi->fop_api->fop_init->cur_play_mode = REPEAT_ALL;
    bSendPrevFileCmdCnt=0;    
    mapi->dop_api->file_num=1;
   // mapi->fop_api->fop_init->filepath="";
    err = music_play_api(mapi,DEV_SEL_CUR,0,PLAY_FIRST_FILE,&(mapi->dop_api->file_num));
   bExitRecordModePlayLastRecordedFileFlag=FALSE;
   //os_taskq_post_event((char *)"CheckTask", 1, SYS_EVENT_LGDEV_ONLINE);
    }
    #endif
    return err;
}
#endif
static u32  music_play_by_path(MUSIC_OP_API *mapi)
{
    u32 err;
    u8 *path;
//    path="/folder1/abc.mp3";
    path="/音乐/";
    mapi->fop_api->fop_init->filepath=path;
     printf("file path : %s  \n",path);
    err = music_play_api(mapi,DEV_SEL_CUR,0,PLAY_FILE_BYPATH,&(mapi->dop_api->file_num));
    err = music_play_api(mapi,DEV_SEL_SPEC,0,PLAY_FILE_BYPATH,&(mapi->dop_api->file_num));
    return err;
}
#if REC_EN
 bool music_judge_JL_REC_folder(void)
{
  //if(music_file_name.tpath==REC_PATH)
  if(strcmp(music_file_name.tpath,"JL_REC     ") == 0)
//  if(music_file_name.tpath=="JL_REC     ")
 //  if(mapi->fop_api->fop_init->filepath=="/JL_REC/")
  return 1;
  else return 0;
}
#endif
static u32  music_play_by_folder(MUSIC_OP_API *mapi)
{
    u32 err;
    u8 *path;
    err = music_play_api(mapi,DEV_SEL_CUR,0,PLAY_PRE_FOLDER,&(mapi->dop_api->file_num));
    return err;
}

//extern _PLAY_SEL_API *psel ;  // jsuo add  20160918 test use 

static void music_task(void *p)
{
    MUSIC_OP_API *mapi=NULL;
    tbool psel_enable = 0;
    u32 err;
    tbool enable = 1;
    tbool file_auto_next = 1;
    u32 wait_exit=0;
     printf("\n************************music TASK********************\n");
#ifdef PA_ENABLE
		pa_umute();
#endif
	
#if 0//def MUSIC_PROMPT_EN
		curr_device_using = try_play_dev();
		if(curr_device_using)
		{
			if(sd0 ==curr_device_using)
			{
        #ifdef MUSIC_PROMPT_EN
				device_file_num = BPF_SD_MP3;
        #endif
			}
			else
			{
        #ifdef MUSIC_PROMPT_EN
				device_file_num = BPF_USB_MP3;
        #endif
			}
		}
#endif

     #ifdef LED_SHOW_MP3
	 setLedLight(LED_SHOW_MP3,led_mode_flash_slow,0);
     #else
    //led_fre_set(15);
     #endif
#ifdef support_power_on_tone	 
	// start on play voice state err when welcom voice !!!   jsuo add 20160918
   	play_sel_stop();
#endif 	 
    #ifdef LED_SHOW_DEVICE_TYPE_SWITCH
	  if(led7_var.blast_play_device)			  
	  UI_menu(MENU_DEIVCE);
   #endif
    mapi = malloc_fun(mapi,sizeof(MUSIC_OP_API),0);
    if(NULL == mapi)
    {
        while(1);
    }
    /*-------解码接口资源申请----------------*/
    mapi->dop_api=malloc_fun(mapi->dop_api,sizeof(_MUSIC_API),0);
    if(NULL==mapi->dop_api)
    {
        // MSG_MUSIC_EQ1(" if(NULL==mapi->dop_api) \r\n");
        while(1);
    }
    /*-------文件操作器资源申请--------------*/
    mapi->fop_api=malloc_fun(mapi->fop_api,sizeof(FILE_OPERATE),0);
    if(NULL==mapi->fop_api)
    {
        // MSG_MUSIC_EQ1(" if(NULL==mapi->fop_api) \r\n");
        while(1);
    }

#ifdef AC46_512K
    mapi->dop_api->dec_api.type_enable |=DEC_PHY_MP3;//使能响应的解码库
    mapi->dop_api->file_type = "MP3";
#else
    mapi->dop_api->dec_api.type_enable |= DEC_PHY_WAV |  DEC_PHY_WMA | DEC_PHY_FLAC | DEC_PHY_APE | DEC_PHY_MP3;//使能响应的解码库
#ifdef SUPPORT_APE_FAST_MODE
    mapi->dop_api->file_type = "WAVWMAMP3FLAAPE";
#else
    mapi->dop_api->file_type = "WAVWMAMP3FLA";
#endif
#endif
    mapi->dop_api->dec_api.dec_phy_name = MUSIC_DEC_PHY_NAME;

    err = os_task_create(decoder_phy_task, 0, TaskMusicPhyDecPrio, 5, mapi->dop_api->dec_api.dec_phy_name);

    if(NULL == mapi->dop_api->io)
    {
        mapi->dop_api->io = malloc_fun(mapi->dop_api->io,sizeof(DEC_API),0);
        if(NULL == mapi->dop_api->io)
        {
            // MSG_MUSIC_EQ1(" if(NULL == mapi->dop_api->dec_io) \r\n");
            while(1);
        }
    }

	mapi->dop_api->io->father_name = "MusicTask";//解码结束的消息返回给谁
	mapi->dop_api->file_num = 1;
	mapi->dop_api->dec_api.eq = eq_mode;
	mapi->dop_api->dec_api.ef_enable = EF_VOL|EF_EQ;//0xff;

	int msg[3];
    _PLAY_SEL_PARA *psel_p = NULL;
    psel_p  = malloc_fun(psel_p ,sizeof(_PLAY_SEL_PARA),0);
    tbool b_res;
    if(NULL != psel_p )
    {
        psel_p->file_number = malloc_fun(psel_p->file_number,sizeof(psel_p->file_number[0])*MUSIC_TONE_NUM,0);
        if(NULL != psel_p->file_number)
        {
            psel_enable = 1;
            psel_p->max_file_number = MUSIC_TONE_NUM;
            psel_p->delay = 1;
            psel_p->rpt_time = 1;
         #ifdef EXIT_BLUE_MODE_DISCONNECT_VOICE
			if(prev_task_is_blue){
			psel_p->file_number[0] = BPF_DISCONNECT_MP3;
			prev_task_is_blue=FALSE;
			}else
        #endif
#ifdef SUPPORT_VOICE_ONOFF
	 if(led7_var.bIfHaveVoice)
#endif

#ifdef SUPPORT_DOUBLE_VOICE
   if(IsVoiceEnable==1)
	{
	       #ifdef MUSIC_PROMPT_EN
	 	  #ifdef MUSIC_PROMPT_MODIFY
	 		power_on_flag=1;
	 		psel_p->file_number[0] = BPF_MUSIC_MP3;
	 	  #else
	 		// if(device_file_num==BPF_USB_MP3)
	 		if(curr_device_using==usb)
	 		 psel_p->file_number[0] = BPF_USB_MP3;
	 		 //else if(device_file_num==BPF_SD_MP3)
	 		 else if(curr_device_using==sd0)
	 		 psel_p->file_number[0] = BPF_SD_MP3;
	 		 else
	 		 psel_p->file_number[0] =BPF_MUSIC_MP3;
	 	 #endif
	      #else
	 		psel_p->file_number[0] = BPF_MUSIC_MP3;
	      #endif
	  }
   else if(IsVoiceEnable==2)
	{
	       #ifdef MUSIC_PROMPT_EN
	 	  #ifdef MUSIC_PROMPT_MODIFY
	 		power_on_flag=1;
	 		psel_p->file_number[0] = BPF_MUSIC_MP3_EN;
	 	  #else
	 		// if(device_file_num==BPF_USB_MP3)
	 		if(curr_device_using==usb)
	 		 psel_p->file_number[0] = BPF_USB_MP3_EN;
	 		 //else if(device_file_num==BPF_SD_MP3)
	 		 else if(curr_device_using==sd0)
	 		 psel_p->file_number[0] = BPF_SD_MP3_EN;
	 		 else
	 		 psel_p->file_number[0] =BPF_MUSIC_MP3_EN;
	 	 #endif
	      #else
	 		psel_p->file_number[0] = BPF_MUSIC_MP3_EN;
	      #endif
	  }   	
#else
//	printf("----psel->file_par--%d\n",psel->file_par);
//	printf("----psel->alive--%d\n",psel->alive);

	 #ifdef SUPPORT_ZY_SA_VOICE	 	 
 	   if(IsVoiceEnable)
	 #endif	   	
	{
	       #ifdef MUSIC_PROMPT_EN
	 	  #ifdef MUSIC_PROMPT_MODIFY
	 		power_on_flag=1;
	 		psel_p->file_number[0] = BPF_MUSIC_MP3;
	 	  #else

	 		// if(device_file_num==BPF_USB_MP3)
	 		if(curr_device_using==usb)
	 		 psel_p->file_number[0] = BPF_USB_MP3;
	 		 //else if(device_file_num==BPF_SD_MP3)
	 		 else if(curr_device_using==sd0)
	 		 psel_p->file_number[0] = BPF_SD_MP3;
	 		 else
	 		 psel_p->file_number[0] =BPF_MUSIC_MP3;
	 	 #endif
	      #else
	 		psel_p->file_number[0] = BPF_MUSIC_MP3;
	      #endif
	  }
#endif
        }
        else
        {
            free_fun((void**)&psel_p);
        }
    }
    b_res = play_sel("MusicTask",'A',psel_p);
    if(psel_enable)
    {
        free_fun((void**)&psel_p->file_number);
        free_fun((void**)&psel_p);
    }
    if(!b_res)
    {
        psel_enable = 0;
    }
    /*-------文件操作器初始化信息资源申请--------------*/
	mapi->fop_api->fop_init = malloc_fun(mapi->fop_api->fop_init,sizeof(FILE_OPERATE_INIT),0);
    if(mapi->fop_api->fop_init==NULL)
    {
        // MSG_MUSIC_EQ1("mem err fop_init \n");
        while(1);
    }
  #ifdef SUPPORT_AUX_FM_BT_REPLAY_KEY
    if(!bExitRecordModePlayLastRecordedFileFlag) { 
		play_mode = REPEAT_ALL;
		mapi->fop_api->fop_init->cur_play_mode = REPEAT_ALL;
		}
    else
  #endif
    mapi->fop_api->fop_init->cur_play_mode = play_mode;
    
    mapi->dop_api->brk = malloc_fun(mapi->dop_api->brk,sizeof(FS_BRK_POINT),0);

    mapi->dop_api->dec_api.bp_buff = &mapi->dop_api->brk->inf.brk_buff[0];

    music_prompt_flag = PROMPT_STATUS_PLAY;


    music_prompt_stopped = 1;


 //    printf("\n *******music start   voice end*************** \n");

	while(1)
	{
		os_taskq_pend(0, ARRAY_SIZE(msg), msg);
        err = 0;

//	 printf("----start  msg[0]---- %08x \r\n",msg[0]);
	 
 
        if ( (!enable) && (SYS_EVENT_DEL_TASK != msg[0]))
        {
            continue;
        }
        if(psel_enable)
        {
            switch(msg[0])
            {
		    case SYS_EVENT_PLAY_SEL_END:
		    case SYS_EVENT_BEGIN_DEC:
            case MSG_MUSIC_NEXT_FILE:
            case MSG_MUSIC_PREV_FILE:
            case MSG_MUSIC_PP:
            case MSG_MUSIC_PLAY:
            case MSG_MUSIC_PAUSE:
            #ifdef SUPPORT_MUSIC_STOP
            case MSG_MUSIC_STOP:
            #endif
            #ifdef SUPPORT_MUSIC_FOLDER_OPERATION
            case MSG_FOLDER_REPEAT:
            case MSG_FOLDER_PREV:
            case MSG_FOLDER_NEXT:
            #endif            
            #ifdef SUPPORT_MUSIC_RANDOM_KEY
			case MSG_MUSIC_RANDOM_PLAY:
            #endif
            #ifdef SUPPORT_MUSIC_INTRO_PLAY
            case MSG_MUSIC_INTRO_PLAY:            
            #endif
            #ifdef LED_SHOW_REPEAT_ALL_ONE_FOLDER_NORMAL
			case MSG_MUSIC_RPT1:
			#endif
                msg[0] = SYS_EVENT_PLAY_SEL_END;
			case SYS_EVENT_DEL_TASK: 				//请求删除music任务
                play_sel_stop();
                psel_enable = 0;
				break;
			default:
                msg[0] = NO_MSG;
				break;
            }
        }

        mapi->dop_api->dec_api.save_brk = 0;
        lg_dev_info *tmplgdev;
        if(wait_exit)
        {   ///<进入删除状态，不再响应其他消息
            if(msg[0]!=SYS_EVENT_DEL_TASK)
            {
                // MSG_MUSIC_EQ1("msg ddddd %08x \r\n",msg[0]);
                continue;
            }
        }
		
        switch(msg[0])
		{
		
		    case SYS_EVENT_PLAY_SEL_END:
		//      printf("\n**** music start   SYS_EVENT_PLAY_SEL_END****\n");
			  
		//	printf("-SYS_EVENT_PLAY_SEL_END-music_ui.ui_curr_file--%d\n",music_ui.ui_curr_file);

	 	      #ifdef  support_power_off_tone
	 	 	if(power_on_flag==0)			
	 	 		{	 	 
	 	 		      #ifdef LED_SHOW_MP3
	 	 		 	   setLedLight(LED_SHOW_MP3,led_mode_off,0);
	 	 		      #endif

	 	 		 	Set_power_on_off_io_is_out();
	 	 		 	Set_power_on_off_io_is_LOW();
	 	 	 	 			
	 	 		 	dac_mute(1,1);
	 	 			 #if defined(PA_ENABLE)
	 	 			 	pa_mute();
	 	 			 #endif
					 
	 				break;	 
	 	 		}
	 	 	 #endif			
	
                // MSG_MUSIC_EQ1("notic music end \r\n");
                dac_channel_on(MUSIC_CHANNEL, FADE_OFF);
                set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);
                SET_UI_MAIN(MENU_MUSIC_MAIN);
        #if !defined LED_SHOW_DEVICE_PLUGIN &&!defined SUPPORT_PLAY_VOICE_NO_SHOW_LOD
               UI_menu(MENU_WAIT);
	#endif
		    case SYS_EVENT_BEGIN_DEC:
                mapi->dop_api->dec_api.save_brk = 0;
		      printf("\n**** music start   SYS_EVENT_BEGIN_DEC**** \n");
			
   #ifdef MUSIC_PROMPT_EN
   
	    #ifdef SUPPORT_REC_STOP_PLAY_REC_FILE
	       if(play_rec_last_file)
	       	{
	       	
	       	    play_rec_last_file=0;
	    //   	      mapi->dop_api->file_num = 1;
	    //              err = music_play_api(mapi,DEV_SEL_PREV,0,PLAY_LAST_FILE,&(mapi->dop_api->file_num));
	    
	    		play_mode = REPEAT_FOLDER;
	    		mapi->fop_api->fop_init->cur_play_mode = play_mode;
	    		mapi->dop_api->file_num = curr_dir_file_num+1;
	    		err = music_play_api(mapi,DEV_SEL_PREV,0,PLAY_SPEC_FILE,&(mapi->dop_api->file_num));
	    		play_mode = REPEAT_ALL;
	    		mapi->fop_api->fop_init->cur_play_mode = play_mode;
	    		
	    	 #ifdef support_rec_recplay_notice			
	 		 #ifdef  SUPPORT_ZY_SA_VOICE
	 		 	if(IsVoiceEnable)	 	 
	 		 #endif
	    	 		music_prompt_play(MSG_REC_REPLAY,mapi);
	    	 #endif
	    		
	       	}
	          else 
	    #endif 
   
                   err = prompt_play_end(mapi);
   #else                

   #ifdef SUPPORT_REC_STOP_PLAY_REC_FILE
      if(play_rec_last_file)
      	{
      	
      	    play_rec_last_file=0;
   //   	      mapi->dop_api->file_num = 1;
   //              err = music_play_api(mapi,DEV_SEL_PREV,0,PLAY_LAST_FILE,&(mapi->dop_api->file_num));
   
   		play_mode = REPEAT_FOLDER;
   		mapi->fop_api->fop_init->cur_play_mode = play_mode;
   		mapi->dop_api->file_num = curr_dir_file_num+1;
   		err = music_play_api(mapi,DEV_SEL_PREV,0,PLAY_SPEC_FILE,&(mapi->dop_api->file_num));
		 #ifdef SUPPORT_RECPLAY_REPEAT_ONE
		    		play_mode = REPEAT_ONE;
		 #else
		    		play_mode = REPEAT_ALL;
		 #endif

   		mapi->fop_api->fop_init->cur_play_mode = play_mode;
   		
   	 #ifdef support_rec_recplay_notice
		 #ifdef  SUPPORT_ZY_SA_VOICE
		 	if(IsVoiceEnable)	 	 
		 #endif
   	 	music_prompt_play(MSG_REC_REPLAY,mapi);
   	 #endif
   		
      	}
         else 
   #endif 
   
                   #ifdef POWER_ON_WITH_USB_AND_SD_PLAY_USB_FIRST
                   if(file_operate_get_total_phydev()>1){                
                   #ifdef LED_SHOW_DEVICE_TYPE_SWITCH
   				  if(led7_var.blast_play_device==1){
   				   err = music_play_api(mapi,DEV_SEL_SPEC,(u32)sd0,PLAY_BREAK_POINT,&(mapi->dop_api->file_num));
   				  }else
   				#endif
   				#if 0//REC_EN
                     #ifdef AFTER_RECORD_PLAY_LAST_RECORDED_FILE
   				  if(bExitRecordModePlayLastRecordedFileFlag){
   				    bExitRecordModePlayLastRecordedFileFlag=FALSE;				    
   					//err = music_play_api(mapi,DEV_SEL_SPEC,(u32)usb,PLAY_LAST_FILE,&(mapi->dop_api->file_num));
   					err = music_play_by_path_rec(mapi);
   				  }else
                     #endif
   				#endif
   				err = music_play_api(mapi,DEV_SEL_SPEC,(u32)usb,PLAY_BREAK_POINT,&(mapi->dop_api->file_num));
   				}
                   else
                   #endif
                   #if 0//REC_EN
                     #ifdef AFTER_RECORD_PLAY_LAST_RECORDED_FILE
   				  if(bExitRecordModePlayLastRecordedFileFlag){
   				    bExitRecordModePlayLastRecordedFileFlag=FALSE;				    
   					//err = music_play_api(mapi,DEV_SEL_SPEC,0,PLAY_LAST_FILE,&(mapi->dop_api->file_num));
   					err = music_play_by_path_rec(mapi);
   				  }else
                    #endif
                  #endif
				  
                   err = music_play_api(mapi,DEV_SEL_SPEC,0,PLAY_BREAK_POINT,&(mapi->dop_api->file_num));


		 printf("=========err=222====:%d\n",err);

   #endif
#ifdef LED_SHOW_DEVICE_TYPE_SWITCH
			   led7_var.blast_play_device=0;
#endif
                break;
            case SYS_EVENT_DEC_FR_END:
            case SYS_EVENT_DEC_FF_END:
            case SYS_EVENT_DEC_END:
                // MSG_MUSIC_EQ1("decoder stop\r\n");
                err = music_play_api(mapi,DEV_SEL_CUR,0,PLAY_AUTO_NEXT,&(mapi->dop_api->file_num));
                break;

            case SYS_EVENT_DEV_OFFLINE:

               #ifdef SUPPORT_MUSIC_STOP
				bStop_state=FALSE;
				bPause_state=0;
               #endif
				
                // MSG_MUSIC_EQ1("music SYS_EVENT_DEV_OFFLINE\r");
                tmplgdev=mapi->fop_api->cur_lgdev_info;
                if(tmplgdev)
                {
                    if(tmplgdev->lg_hdl->phydev_item==msg[1])
                    {
                        if((!mapi->dop_api->dec_api.phy_ops) || (DECODER_PAUSE != mapi->dop_api->dec_api.phy_ops->status))
                        {   ///< 解码设备非暂停状态，有解码自己报错
                       #ifdef MULTIPLE_DEVICE_PLUGOUT_ONE_AUTO_CHANGE_TO_ANOTHER_DEVICE
						if(file_operate_get_total_phydev()){
							//os_taskq_post("MusicTask", 1, MSG_MUSIC_U_SD);
							
                             #ifdef IO_MUTE_DELAY_ALL_STATE
                            	#ifdef PA_ENABLE
								pa_mute();
                                #endif
							  bMuteDelayCnt=5;
                             #endif
                            #ifdef LED_SHOW_DEVICE_TYPE_SWITCH
							UI_menu(MENU_DEVICE_SWITCH);
							os_time_dly(50);
                            #endif
                           
							mapi->dop_api->dec_api.save_brk = 1;
							err = music_play_api(mapi,DEV_SEL_NEXT,0,PLAY_BREAK_POINT,&(mapi->dop_api->file_num));
							}
						else
                       #endif
                        #if defined(PLUG_OUT_DEV_TO_LINEIN_MODE)&&defined(SUPPORT_ONE_KEY_TO_AUX)
                        {                        

					#ifndef SUPPORT_MP3_IDEL_MODE_IN_LINEIN_MODE                        
						SET_UI_MAIN(MENU_AUX_MAIN);
						UI_menu(MENU_AUX_MAIN);
					#endif						
						os_taskq_post("MainTask", 1, MSG_ONE_KEY_TO_AUX);	//MSG_CHANGE_TO_BT_MODE 		
						}
		#endif
                            break;
                        }///else的解码暂停状态，有下一个消息SYS_EVENT_DEC_DEVICE_ERR处理
                    }
                    else
                    {   ///<非解码设备，删除该逻辑设备
                        //file_operate_del_spec_lgdev((void *)&(msg[1]));
                        #ifdef MULTIPLE_DEVICE_PLUGOUT_ONE_AUTO_CHANGE_TO_ANOTHER_DEVICE
						if(file_operate_get_total_phydev()){
							//os_taskq_post("MusicTask", 1, MSG_MUSIC_U_SD);	
							//mapi->dop_api->dec_api.save_brk = 0;
							//err = music_play_api(mapi,DEV_SEL_NEXT,0,PLAY_BREAK_POINT,&(mapi->dop_api->file_num));
							break;
							}
						else
                        #endif
                        #if defined(PLUG_OUT_DEV_TO_LINEIN_MODE)&&defined(SUPPORT_ONE_KEY_TO_AUX)
                        {                        
                        
						#ifndef SUPPORT_MP3_IDEL_MODE_IN_LINEIN_MODE                        
							SET_UI_MAIN(MENU_AUX_MAIN);
							UI_menu(MENU_AUX_MAIN);
						#endif						
						os_taskq_post("MainTask", 1, MSG_ONE_KEY_TO_AUX);	//MSG_CHANGE_TO_BT_MODE 	
				}
                        #endif
                        break;
                    }
                }
                else
                    break;
				
            case SYS_EVENT_DEC_DEVICE_ERR:
                mapi->dop_api->dec_api.save_brk = 1;
                mapi->dop_api->file_num = 1;
                err = music_play_api(mapi,DEV_SEL_NEXT,0,PLAY_BREAK_POINT,&(mapi->dop_api->file_num));
           #if 0//def MUSIC_PROMPT_EN
			  if(sd0 == curr_device_using)
			  {
				  curr_device_using = usb;
			  }
			  else
			  {
				  curr_device_using = sd0;
			  }
			  music_prompt_play(MSG_MUSIC_U_SD,mapi);
          #endif
                break;
            case MSG_MUSIC_NEXT_FILE:
		  // puts("KEY_EVENT_NEXT\r\n");	
		  
               #ifdef TEST_PANEL_LED
               bledGridValue++;
               if(bledGridValue>LED_8GRIDS)
               bledGridValue=0;

		 	 printf("bledGridValue =%x %x \n",bledComValue,bledGridValue);
				break;
	        #endif

		 #ifdef support_prev_next_voice_play	
		 if(music_prompt_stopped==0)
		 	break;
		 #endif
			   
               #ifdef SUPPORT_MUSIC_STOP
                bStop_state=FALSE;
                bPause_state=0;
               #endif
                file_auto_next = 1;
               #ifdef LED_SHOW_MP3
            	setLedLight(LED_SHOW_MP3,led_mode_flash_slow,0);
               #else
                //led_fre_set(15);
               #endif
                 #ifdef IO_MUTE_DELAY_ALL_STATE
                   #ifdef PA_ENABLE
				   pa_mute();
                   #endif
				 bMuteDelayCnt=3;
                #endif
                // MSG_MUSIC_EQ1("KEY_EVENT_NEXT\r\n");
                err = music_play_api(mapi,DEV_SEL_CUR,0,PLAY_NEXT_FILE,&(mapi->dop_api->file_num));
                #ifdef SUPPORT_MUSIC_INTRO_PLAY  //make sure count time is 10s and reset the count if some music total time less than 10s 
                if(mp3_intro_play)bIntro_play_cnt=0;
                #endif

			#ifndef SUPPORT_SSM_VOICE		
			#ifdef  SUPPORT_ZY_SA_VOICE
			
	    			 if(IsVoiceEnable)
	    			 {
					music_prompt_play(msg[0], mapi);
	    			 }
			#endif					
			#endif					

//                err=music_play_by_path(mapi);
//                err=music_play_by_folder(mapi);
                break;
			
            case MSG_MUSIC_PREV_FILE:
		  // puts("MSG_MUSIC_PREV_FILE\r\n");				
			
            #ifdef TEST_PANEL_LED
	                if(bledGridValue)
					bledGridValue--;					
			 	 printf("bledGridValue =%x %x \n",bledComValue,bledGridValue);
			break;
              #endif
			  			  			  
                #ifdef SUPPORT_MUSIC_STOP
	                bStop_state=FALSE;
	                bPause_state=0;
                #endif
                file_auto_next = 0;
                #ifdef LED_SHOW_MP3
			 #ifdef LED_SHOW_REC
			 #ifdef SUPPORT_LYX_RECPLAY_REPEAT_ONE
			 	if(lyx_recplay_repeat_one_sw==1)
			 	{
				 	setLedLight(LED_SHOW_REC,led_mode_flash_slow,0);
				 	setLedLight(LED_SHOW_MP3,led_mode_off,0);
			 	}
				else
			 #endif				
			 #endif				
	            	setLedLight(LED_SHOW_MP3,led_mode_flash_slow,0);
                #else
                //led_fre_set(15);
                #endif
                #ifdef IO_MUTE_DELAY_ALL_STATE
                  #ifdef PA_ENABLE
                    pa_mute();
                  #endif
                  bMuteDelayCnt=3;
                #endif
                // MSG_MUSIC_EQ1("KEY_EVENT_PREV\r\n");
                err = music_play_api(mapi,DEV_SEL_CUR,0,PLAY_PREV_FILE,&(mapi->dop_api->file_num));


			 #ifdef SUPPORT_LYX_RECPLAY_REPEAT_ONE
					 #ifdef SUPPORT_LYX_RECPLAY_REPEAT_ONE
					 if(lyx_recplay_repeat_one_sw==1)
					 	{
					   		play_mode = REPEAT_ONE;					 	
						 	mapi->fop_api->fop_init->cur_play_mode = play_mode;
							lyx_recplay_repeat_one_sw=0;
					 }
					 #endif
			 

			 #endif
			 
			#ifndef SUPPORT_SSM_VOICE
			#ifdef  SUPPORT_ZY_SA_VOICE
				 #ifdef AFTER_RECORD_PLAY_LAST_RECORDED_FILE
				      if(!bIfRecordFolder)
				 #endif					 	

	    			 if(IsVoiceEnable)
	    			 {
					music_prompt_play(msg[0], mapi);
	    			 }
			#endif					
			#endif					

//                mapi->dop_api->file_num = 1;
//                err = music_play_api(mapi,DEV_SEL_SPEC,(u32)usb,PLAY_SPEC_FILE,&(mapi->dop_api->file_num));
                break;
            #ifdef SUPPORT_MUSIC_FOLDER_OPERATION
            case MSG_FOLDER_PREV:               
			   err = music_play_api(mapi,DEV_SEL_CUR,0,PLAY_PRE_FOLDER,&(mapi->dop_api->file_num));
			   UI_menu(MENU_PREV_FOLDER);
			   os_time_dly(2);
               break;
			case MSG_FOLDER_NEXT:
			   err = music_play_api(mapi,DEV_SEL_CUR,0,PLAY_NEXT_FOLDER,&(mapi->dop_api->file_num));
			   UI_menu(MENU_NEXT_FOLDER);
			   os_time_dly(2);
			   break;
			case MSG_FOLDER_REPEAT:			  
			   if(mapi && mapi->fop_api && mapi->fop_api->fop_init)
			   {		
			       if((play_mode!=REPEAT_FOLDER) && (play_mode!=REPEAT_ALL))
			       play_mode=REPEAT_FOLDER;	
			       else if(play_mode==REPEAT_FOLDER)
			       play_mode=REPEAT_ALL;
			       else if(play_mode==REPEAT_ALL)
			       play_mode=REPEAT_FOLDER;
				   mapi->fop_api->fop_init->cur_play_mode = play_mode;
			   }
			   UI_menu(MENU_PLAYMODE);
			   break;
            #endif
            #ifdef SUPPORT_MUSIC_RANDOM_KEY
			case MSG_MUSIC_RANDOM_PLAY:			  
			  if(mapi && mapi->fop_api && mapi->fop_api->fop_init)
			  { 			  
			      if(play_mode!=REPEAT_RANDOM)
				  play_mode=REPEAT_RANDOM;	
				  else
				  play_mode=REPEAT_ALL;	
				  mapi->fop_api->fop_init->cur_play_mode = play_mode;
			  }
			  UI_menu(MENU_PLAYMODE);
			   break;
            #endif
            #ifdef SUPPORT_MUSIC_INTRO_PLAY
            case MSG_MUSIC_INTRO_PLAY:
               mp3_intro_play=!mp3_intro_play;
               UI_menu(MENU_MUSIC_INTRO);               
			   os_time_dly(2);
               break;
            #endif
        #ifdef LED_SHOW_REPEAT_ALL_ONE_FOLDER_NORMAL
			case MSG_MUSIC_RPT1:
				if(mapi && mapi->fop_api && mapi->fop_api->fop_init)
				{
				   repeat_mode++;
				   if(repeat_mode>=rpt_max)repeat_mode=rpt_normal;
				   switch(repeat_mode){
						case rpt_normal:
							play_mode=REPEAT_ALL;
							break;
						case rpt_all:
							play_mode=REPEAT_ALL;
							break;
						case rpt_one:
							play_mode=REPEAT_ONE;
							break;
						case rpt_folder:
							play_mode=REPEAT_FOLDER;
							break;
						default:
						    break;
				   }				  
					mapi->fop_api->fop_init->cur_play_mode = play_mode;
				}
				UI_menu(MENU_USER_REPEAT_MODE);
				// printf("cur_play_mode : %s\r", &rpt_str[mapi->fop_api->fop_init->cur_play_mode-REPEAT_ALL][0] );
				break;
         #endif
#ifdef support_rep_one_all
            case MSG_MUSIC_RPT_ONE:

                #ifdef SUPPORT_MUSIC_STOP
	                bStop_state=FALSE;
	                bPause_state=0;
                #endif				
                if(mapi && mapi->fop_api && mapi->fop_api->fop_init)
                {				   
                        play_mode = REPEAT_ONE;
				   
                   #ifdef LED_SHOW_MP3
					setLedLight(LED_SHOW_MP3,led_mode_flash_fast,0);
                   #endif
                    mapi->fop_api->fop_init->cur_play_mode = play_mode;
                }
                UI_menu(MENU_PLAYMODE);

			#ifndef SUPPORT_SSM_VOICE		
			#ifdef  SUPPORT_ZY_SA_VOICE
	    			 if(IsVoiceEnable)
	    			 {
					music_prompt_play(msg[0], mapi);
	    			 }
			#endif	
			#endif	
		break;
			
            case MSG_MUSIC_RPT_ALL:

                #ifdef SUPPORT_MUSIC_STOP
	                bStop_state=FALSE;
	                bPause_state=0;
                #endif				
                if(mapi && mapi->fop_api && mapi->fop_api->fop_init)
                {

                    {
                        play_mode = REPEAT_ALL;
                    }
                   #ifdef LED_SHOW_MP3
					setLedLight(LED_SHOW_MP3,led_mode_flash_slow,0);
                   #endif
                    mapi->fop_api->fop_init->cur_play_mode = play_mode;
                }
                UI_menu(MENU_PLAYMODE);

			#ifndef SUPPORT_SSM_VOICE		
			#ifdef  SUPPORT_ZY_SA_VOICE
	    			 if(IsVoiceEnable)
	    			 {
					music_prompt_play(msg[0], mapi);
	    			 }
			#endif	
			#endif	
		break;
			
#endif


		 
            case MSG_MUSIC_RPT:

                #ifdef SUPPORT_MUSIC_STOP
	                bStop_state=FALSE;
	                bPause_state=0;
                #endif				
                if(mapi && mapi->fop_api && mapi->fop_api->fop_init)
                {
                   #ifdef REPEAT_NOT_USE_RANDOM_AND_FOLDER
                   if(play_mode==REPEAT_ONE||play_mode==REPEAT_FOLDER)play_mode=REPEAT_ALL;
                   else play_mode=REPEAT_ONE;
                   #elif defined(REPEAT_NOT_USE_FOLDER)                    
				   play_mode++;
				   if(play_mode==REPEAT_FOLDER)play_mode=REPEAT_ONE;
                   #else
                    play_mode++;
                   #endif
                    if(play_mode >= MAX_PLAY_MODE)
                    {
                        play_mode = REPEAT_ALL;
                    }
                   #ifdef LED_SHOW_MP3
                   if(play_mode==REPEAT_ONE)
					setLedLight(LED_SHOW_MP3,led_mode_flash_fast,0);
				   else
					setLedLight(LED_SHOW_MP3,led_mode_flash_slow,0);
                   #endif
                    mapi->fop_api->fop_init->cur_play_mode = play_mode;
                }
                UI_menu(MENU_PLAYMODE);
                 printf("cur_play_mode : %s\r", &rpt_str[mapi->fop_api->fop_init->cur_play_mode-REPEAT_ALL][0] );

			#ifndef SUPPORT_SSM_VOICE		
			#ifdef  SUPPORT_ZY_SA_VOICE
	    			 if(IsVoiceEnable)
	    			 {
					music_prompt_play(msg[0], mapi);
	    			 }
			#endif					
			#endif					
				
                break;

            case MSG_MUSIC_U_SD:
                // MSG_MUSIC_EQ1("MSG_MUSIC_U_SD\r\n");
                if(file_operate_get_total_phydev()>1)
                {
                  #ifdef MUSIC_PROMPT_EN
					dec_dev_changed=1;					  
					mapi->dop_api->dec_api.save_brk = 1;
					if(curr_device_using == sd0)
					{
						curr_device_using = usb;
					}
					else// if(music_ui.ui_curr_device == USB_DEVICE)
					{
						curr_device_using = sd0;
					}

				 #ifdef LED_SHOW_DEVICE_PLUGIN	  
				 	led7_var.dwDeviceID= curr_device_using;			 
				 #endif					
                 #endif
	            #ifdef SUPPORT_MUSIC_STOP
					bStop_state=FALSE;
					bPause_state=0;
	            #endif
				
                    #ifdef LED_SHOW_MP3
                	setLedLight(LED_SHOW_MP3,led_mode_flash_slow,0);
                    #else
                    //led_fre_set(15);
                    #endif
                    #ifdef LED_SHOW_DEVICE_TYPE_SWITCH
                    UI_menu(MENU_DEVICE_SWITCH);
                    os_time_dly(50);
                    #endif
                    mapi->dop_api->dec_api.save_brk = 1;
                #ifdef MUSIC_PROMPT_EN
			 #if  defined SUPPORT_SSM_VOICE
				 #ifdef SUPPORT_VOICE_ONOFF
				 	 if(led7_var.bIfHaveVoice)
				 #endif				
						music_prompt_play(MSG_MUSIC_U_SD,mapi);
				 #ifdef SUPPORT_VOICE_ONOFF
					 else
		 	                 	   err = music_play_api(mapi,DEV_SEL_NEXT,0,PLAY_BREAK_POINT,&(mapi->dop_api->file_num));
				 #endif
			 #else
				 #ifdef SUPPORT_ZY_SA_VOICE	 	 
				 	   if(IsVoiceEnable)
							music_prompt_play(MSG_MUSIC_U_SD,mapi);
						 else
		 	                 	   err = music_play_api(mapi,DEV_SEL_NEXT,0,PLAY_BREAK_POINT,&(mapi->dop_api->file_num));				   	
				   #else
					music_prompt_play(MSG_MUSIC_U_SD,mapi);				   
				 #endif	   	
			 
			 #endif			 	
                #else
                    err = music_play_api(mapi,DEV_SEL_NEXT,0,PLAY_BREAK_POINT,&(mapi->dop_api->file_num));
                #endif
                }
                break;

#ifdef support_EQ_SINGLE_6MODE
			case MSG_MUSIC_EQ1:
			     eq_mode=0;
				 if(mapi && mapi->dop_api)
				 {					
					 mapi->dop_api->dec_api.eq = eq_mode;
					 mapi->dop_api->dec_api.ef_info = ef_eq_info_set(mapi->dop_api->dec_api.ef_info,EF_CHANGE_COEF,mapi->dop_api->dec_api.eq);
				 }
				 // MSG_MUSIC_EQ1("MSG_MUSIC_EQ `%d\r\n",mapi->dop_api->dec_api.eq);
				 UI_menu(MENU_EQ);
				 break;
			case MSG_MUSIC_EQ2:
				eq_mode=2;
				if(mapi && mapi->dop_api)
				{				   
					mapi->dop_api->dec_api.eq = eq_mode;
					mapi->dop_api->dec_api.ef_info = ef_eq_info_set(mapi->dop_api->dec_api.ef_info,EF_CHANGE_COEF,mapi->dop_api->dec_api.eq);
				}
				// MSG_MUSIC_EQ1("MSG_MUSIC_EQ `%d\r\n",mapi->dop_api->dec_api.eq);
				UI_menu(MENU_EQ);
				break;
			case MSG_MUSIC_EQ3:
				eq_mode=1;
				if(mapi && mapi->dop_api)
				{				   
					mapi->dop_api->dec_api.eq = eq_mode;
					mapi->dop_api->dec_api.ef_info = ef_eq_info_set(mapi->dop_api->dec_api.ef_info,EF_CHANGE_COEF,mapi->dop_api->dec_api.eq);
				}
				// MSG_MUSIC_EQ1("MSG_MUSIC_EQ `%d\r\n",mapi->dop_api->dec_api.eq);
				UI_menu(MENU_EQ);
				break;
			case MSG_MUSIC_EQ4:
				eq_mode=4;
				if(mapi && mapi->dop_api)
				{				   
					mapi->dop_api->dec_api.eq = eq_mode;
					mapi->dop_api->dec_api.ef_info = ef_eq_info_set(mapi->dop_api->dec_api.ef_info,EF_CHANGE_COEF,mapi->dop_api->dec_api.eq);
				}
				// MSG_MUSIC_EQ1("MSG_MUSIC_EQ `%d\r\n",mapi->dop_api->dec_api.eq);
				UI_menu(MENU_EQ);
				break;
			case MSG_MUSIC_EQ5:
				eq_mode=3;
				if(mapi && mapi->dop_api)
				{				   
					mapi->dop_api->dec_api.eq = eq_mode;
					mapi->dop_api->dec_api.ef_info = ef_eq_info_set(mapi->dop_api->dec_api.ef_info,EF_CHANGE_COEF,mapi->dop_api->dec_api.eq);
				}
				UI_menu(MENU_EQ);
			break;
			case MSG_MUSIC_EQ6:			
			    eq_mode=5;
	                if(mapi && mapi->dop_api)
	                {                  
	                    mapi->dop_api->dec_api.eq = eq_mode;
	                    mapi->dop_api->dec_api.ef_info = ef_eq_info_set(mapi->dop_api->dec_api.ef_info,EF_CHANGE_COEF,mapi->dop_api->dec_api.eq);
	                }
	                UI_menu(MENU_EQ);
			break;
#endif

				
      #ifdef KEY_DIRECT_TO_EVERY_EQ
			case MSG_EQ_NORMAL:
			     eq_mode=0;
				 if(mapi && mapi->dop_api)
				 {					
					 mapi->dop_api->dec_api.eq = eq_mode;
					 mapi->dop_api->dec_api.ef_info = ef_eq_info_set(mapi->dop_api->dec_api.ef_info,EF_CHANGE_COEF,mapi->dop_api->dec_api.eq);
				 }
				 // MSG_MUSIC_EQ1("MSG_MUSIC_EQ `%d\r\n",mapi->dop_api->dec_api.eq);
				 UI_menu(MENU_EQ);
				#ifdef  SUPPORT_ZY_SA_VOICE
		    			 if(IsVoiceEnable)
		    			 {
						music_prompt_play(MSG_MUSIC_EQ, mapi);
		    			 }
				#endif					
				 break;
			case MSG_EQ_POPULAR:
				eq_mode=2;
				if(mapi && mapi->dop_api)
				{				   
					mapi->dop_api->dec_api.eq = eq_mode;
					mapi->dop_api->dec_api.ef_info = ef_eq_info_set(mapi->dop_api->dec_api.ef_info,EF_CHANGE_COEF,mapi->dop_api->dec_api.eq);
				}
				// MSG_MUSIC_EQ1("MSG_MUSIC_EQ `%d\r\n",mapi->dop_api->dec_api.eq);
				UI_menu(MENU_EQ);
				#ifdef  SUPPORT_ZY_SA_VOICE
		    			 if(IsVoiceEnable)
		    			 {
						music_prompt_play(MSG_MUSIC_EQ, mapi);
		    			 }
				#endif					
				break;
			case MSG_EQ_ROCK:
				eq_mode=1;
				if(mapi && mapi->dop_api)
				{				   
					mapi->dop_api->dec_api.eq = eq_mode;
					mapi->dop_api->dec_api.ef_info = ef_eq_info_set(mapi->dop_api->dec_api.ef_info,EF_CHANGE_COEF,mapi->dop_api->dec_api.eq);
				}
				// MSG_MUSIC_EQ1("MSG_MUSIC_EQ `%d\r\n",mapi->dop_api->dec_api.eq);
				UI_menu(MENU_EQ);
				#ifdef  SUPPORT_ZY_SA_VOICE
		    			 if(IsVoiceEnable)
		    			 {
						music_prompt_play(MSG_MUSIC_EQ, mapi);
		    			 }
				#endif					
				break;
			case MSG_EQ_JAZZ:
				eq_mode=4;
				if(mapi && mapi->dop_api)
				{				   
					mapi->dop_api->dec_api.eq = eq_mode;
					mapi->dop_api->dec_api.ef_info = ef_eq_info_set(mapi->dop_api->dec_api.ef_info,EF_CHANGE_COEF,mapi->dop_api->dec_api.eq);
				}
				// MSG_MUSIC_EQ1("MSG_MUSIC_EQ `%d\r\n",mapi->dop_api->dec_api.eq);
				UI_menu(MENU_EQ);
				#ifdef  SUPPORT_ZY_SA_VOICE
		    			 if(IsVoiceEnable)
		    			 {
						music_prompt_play(MSG_MUSIC_EQ, mapi);
		    			 }
				#endif					
				break;
			case MSG_EQ_CLASSIC:
				eq_mode=3;
				if(mapi && mapi->dop_api)
				{				   
					mapi->dop_api->dec_api.eq = eq_mode;
					mapi->dop_api->dec_api.ef_info = ef_eq_info_set(mapi->dop_api->dec_api.ef_info,EF_CHANGE_COEF,mapi->dop_api->dec_api.eq);
				}
				// MSG_MUSIC_EQ1("MSG_MUSIC_EQ `%d\r\n",mapi->dop_api->dec_api.eq);
				UI_menu(MENU_EQ);
				#ifdef  SUPPORT_ZY_SA_VOICE
		    			 if(IsVoiceEnable)
		    			 {
						music_prompt_play(MSG_MUSIC_EQ, mapi);
		    			 }
				#endif					
				
			break;
			case MSG_EQ_LIVE:			
			    eq_mode=5;
	                if(mapi && mapi->dop_api)
	                {                  
	                    mapi->dop_api->dec_api.eq = eq_mode;
	                    mapi->dop_api->dec_api.ef_info = ef_eq_info_set(mapi->dop_api->dec_api.ef_info,EF_CHANGE_COEF,mapi->dop_api->dec_api.eq);
	                }
	                // MSG_MUSIC_EQ1("MSG_MUSIC_EQ `%d\r\n",mapi->dop_api->dec_api.eq);
	                UI_menu(MENU_EQ);
			#ifdef  SUPPORT_ZY_SA_VOICE
	    			 if(IsVoiceEnable)
	    			 {
					music_prompt_play(MSG_MUSIC_EQ, mapi);
	    			 }
			#endif					
				
			break;
      #endif

            case MSG_MUSIC_EQ:

		 #ifdef TEST_PANEL_LED
		 	if(bledComValue)
		 	bledComValue--;
		 	 printf("bledGridValue =%x %x \n",bledComValue,bledGridValue);
		 	break;
		 
		 #endif

                #ifdef SUPPORT_MUSIC_STOP
	                bStop_state=FALSE;
	                bPause_state=0;
                #endif
				
                if(mapi && mapi->dop_api)
                {
                 #ifdef EQ_SEQUENCE_ADJ_ANYWAY

			#ifdef  SUPPORT_ZY_SA_VOICE
					 eq_mode++;
					 if(eq_mode > 5)
					 {
						 eq_mode = 0;
					 }			
			#else				 
					eq_sequence_mode++;
					if(eq_sequence_mode>=eq_max)
						eq_sequence_mode=eq_normal;
					switch(eq_sequence_mode){
					  case eq_normal:
						  eq_mode=0;
						  break;
					  case eq_pop:
						  eq_mode=2;
						  break;
					  case eq_rock:
						  eq_mode=1;
						  break;
					  case eq_jazz:
						  eq_mode=4;
						  break;
					  case eq_classic:
						  eq_mode=3;
						  break;
					  case eq_country:
						  eq_mode=5;
						  break;
					  case eq_bass:
						  eq_mode=6;
						  break;
					  default:
						  break;
					}
	                  	#endif
                	  #else
					 eq_mode++;
					 if(eq_mode > 5)
					 {
						 eq_mode = 0;
					 }
                  #endif

			#ifndef SUPPORT_SSM_VOICE		
			#ifdef  SUPPORT_ZY_SA_VOICE
	    			 if(IsVoiceEnable)
	    			 {
					music_prompt_play(msg[0], mapi);
	    			 }
			#endif					
			#endif					
                    mapi->dop_api->dec_api.eq = eq_mode;
                    mapi->dop_api->dec_api.ef_info = ef_eq_info_set(mapi->dop_api->dec_api.ef_info,EF_CHANGE_COEF,mapi->dop_api->dec_api.eq);
                }
                // MSG_MUSIC_EQ1("MSG_MUSIC_EQ `%d\r\n",mapi->dop_api->dec_api.eq);
                UI_menu(MENU_EQ);
                break;
           #ifdef SUPPORT_MUSIC_STOP
            case MSG_MUSIC_STOP:            
             if(bPause_state){
             bStop_state=TRUE;
             bPause_state=0;
             }
             else if(!bStop_state){             
   			     _DECODE_STATUS pp_state;
                  pp_state=pp_decode(&mapi->dop_api->dec_api);
                  if(pp_state==DECODER_PAUSE){
                  bStop_state=TRUE;
                  }
                }                
                    #ifdef LED_SHOW_MP3
	                	setLedLight(LED_SHOW_MP3,led_mode_on,0);							
                    #endif

			 
				UI_menu(MENU_MUSIC_STOP);
                   break;
           #endif
            case MSG_MUSIC_PP:
				
           #ifdef TEST_PANEL_LED
	            bledComValue++;
	            if(bledComValue>=LED_COM_MAX)
	            bledComValue=0;
				
		 	 printf("bledGridValue =%x %x \n",bledComValue,bledGridValue);
			
			break;			
            #endif

			
             #ifdef SUPPORT_MUSIC_STOP
			if(bStop_state)
			{
			           #ifdef MUSIC_AFTER_STOP_PLAY_CUR_FILE
			            if(music_ui.ui_curr_file>0)
						mapi->dop_api->file_num = music_ui.ui_curr_file;
						else
						mapi->dop_api->file_num = 1;
						err = music_play_api(mapi,DEV_SEL_CUR,0,PLAY_SPEC_FILE,&(mapi->dop_api->file_num));
			          #else
						err=FILE_OP_ERR_OPEN_BPFILE;
			          #endif
					  
	                     #ifdef LED_SHOW_MP3
	 					if(play_mode==REPEAT_ONE)
	 					setLedLight(LED_SHOW_MP3,led_mode_flash_fast,0);
	 					 else
	                 	setLedLight(LED_SHOW_MP3,led_mode_flash_slow,0);
	                     #else
	                     //led_fre_set(15);
	                     #endif
					  
				bStop_state=FALSE;
				break;
			}
            #endif
		 #if UI_ENABLE
		             if (UI_var.bCurMenu == MENU_INPUT_NUMBER)
		             {
		                 os_taskq_post("MusicTask", 1 , MSG_INPUT_TIMEOUT);
		                 break;
		             }
		 #elif IR_NUM_INPUT_EN
		 			if(ir_num_timeout_cnt)
		             {
		                 os_taskq_post("MusicTask", 1 , MSG_INPUT_TIMEOUT);
		                 break;
		             }
		 #endif

                // puts("MSG_MUSIC_PP\n");
                _DECODE_STATUS pp_s;
                pp_s = pp_decode(&mapi->dop_api->dec_api);
                if(DECODER_PAUSE == pp_s)
                {

					
                    // puts("*PAUSE*\n");
                   #ifdef LED_SHOW_MP3
                	setLedLight(LED_SHOW_MP3,led_mode_on,0);
                   #else
                    //led_fre_set(0);
                   #endif
                   #ifdef SUPPORT_MUSIC_STOP
                  	 bPause_state=1;
                   #endif
	                #ifdef LED_SHOW_MP3_PAUSE
					UI_menu(MENU_MP3_PAUSE);	
	 		#endif

			 #ifdef support_io_det_mute
			   if(auto_mute_sw)
			   {
 			      automute_sw=1;
				pa_mute1();
			   }
			 #endif

			#ifndef SUPPORT_SSM_VOICE		
			#ifdef  SUPPORT_ZY_SA_VOICE
	    			 if(IsVoiceEnable)
	    			 {
					music_prompt_play(MSG_MUSIC_PAUSE, mapi);
	    			 }
			#endif												
			#endif					
                }
                else
                {


	                 #ifdef SUPPORT_MUSIC_STOP
					 bPause_state=0;
	                 #endif
				
                    if(DECODER_PLAY == pp_s)
                    {
                        // puts("*PLAY*\n");
	                 #ifdef SUPPORT_MUSIC_STOP
					 bPause_state=0;
	                 #endif
					 
                    }
                    else
                    {
                        // puts("*STOP*\n");
                    }
                    #ifdef LED_SHOW_MP3
					if(play_mode==REPEAT_ONE)
					setLedLight(LED_SHOW_MP3,led_mode_flash_fast,0);
					 else
                	setLedLight(LED_SHOW_MP3,led_mode_flash_slow,0);
                    #else
                    //led_fre_set(15);
                    #endif
			#ifndef SUPPORT_SSM_VOICE		
			#ifdef  SUPPORT_ZY_SA_VOICE
	    			 if(IsVoiceEnable)
	    			 {
						music_prompt_play(MSG_MUSIC_PLAY, mapi);
	    			 }
			#endif					
			#endif					
                }
                UI_menu(MENU_MUSIC_MAIN);
                break;
            case MSG_MUSIC_FF:
                // MSG_MUSIC_EQ1("ff");
                 #ifdef SUPPORT_MUSIC_STOP
				 bStop_state=FALSE;
				 bPause_state=0;
                 #endif
                if (0 == dec_ff_fr(&mapi->dop_api->dec_api,PLAY_MOD_FF))
                {
                }
                break;
            case MSG_MUSIC_FR:
               #ifdef SUPPORT_MUSIC_STOP
				bStop_state=FALSE;
				bPause_state=0;
               #endif
                // MSG_MUSIC_EQ1("fr");
                if (0 == dec_ff_fr(&mapi->dop_api->dec_api,PLAY_MOD_FB))
                {
                }
                break;
            case MSG_MUSIC_FFR_DONE:
                break;

			case SYS_EVENT_DECODE_END:
				break;
		 #if REC_EN
		 #ifdef SUPPORT_REPLAY_CANCEL_FOLDER_REPEAT_AND_PLAY_NOT_REC_FILES
		 			case MSG_MUSIC_REC_REPLAY_CANCEL:
		 			 if(mapi && mapi->fop_api && mapi->fop_api->fop_init){
		 			 #ifndef SUPPORT_LYX_RECPLAY_REPEAT_ONE
		 			 	if(mapi->fop_api->fop_init->cur_play_mode==REPEAT_FOLDER)
		 			 #endif
		 			 	{
		 					play_mode=REPEAT_ALL;
		 					mapi->fop_api->fop_init->cur_play_mode=REPEAT_ALL;
		 			 	}
		        	    	{
		 
		 		 	 #ifdef LED_SHOW_REC	
		 		 	 	 setLedLight(LED_SHOW_REC,led_mode_off,0);
		 		 	 	 setLedLight(LED_SHOW_MP3,led_mode_flash_slow,0);
		 		 	 #endif
		 					
		 			  err = music_play_api(mapi,DEV_SEL_CUR,0,PLAY_NEXT_FOLDER,&(mapi->dop_api->file_num));			  
		 				#ifdef support_rec_play_first_mute_after_rec
		 				   	dac_mute(0,1);
		 				#endif
		 	           	}	  
		 		  }		
		 			   			 
		 			   break;
		 #endif
		 
		 
		             case MSG_REC_REPLAY:     
		 
		 				
		            #ifdef SUPPORT_REPLAY_CANCEL_FOLDER_REPEAT_AND_PLAY_NOT_REC_FILES
		 			//bRecReplayFlag=!bRecReplayFlag;
		                  if(bIfRecordFolder)
		                  	{
		 				 os_taskq_post("MusicTask", 1 , MSG_MUSIC_REC_REPLAY_CANCEL);
		                  	}
		                  else
		            #endif
		            	{
		 //		     printf("-1111111--(music_play_by_path_rec(mapi)) %d\n",(music_play_by_path_rec(mapi)));
		            	
		 //			if(music_play_by_path_rec(mapi))
		 //			break;
		 			
		                  err =mp3_mode_rec_play_by_path_rec(mapi);
		 
		 	   	 #ifdef support_rec_recplay_notice	
		 		 #ifdef  SUPPORT_ZY_SA_VOICE
		 		 	if(IsVoiceEnable)	 	 
		 		 #endif
		 	   	 	music_prompt_play(MSG_REC_REPLAY,mapi);
		 	   	 #endif				 
		            	} 
		 
		 	#ifdef support_rec_play_first_mute_after_rec
		 	   	dac_mute(0,1);
		 	#endif
		 		   
		 				//err = music_play_api(mapi,DEV_SEL_SPEC,0,PLAY_LAST_FILE,&(mapi->dop_api->file_num));
		                 break;
		             case MSG_MUSIC_DEL_FILE:            
		 			   // if(mapi->fop_api->fop_init->filepath!=REC_PATH)break; //filter not rec file
		 			  #ifdef SUPPORT_REC_DELETE_FILTER_NOT_REC_FILE
		 			    if(!bIfRecordFolder)break;
		 			  #endif	
		 			  
		               #ifdef LED_SHOW_DEL        
		 			 #ifdef SUPPORT_LED_SHOW_DEL			  
		 			 	bLedShowDelCnt=1;
		 			 #else
		 			 
		 			 	//			  SET_UI_MAIN(MENU_REC_DEL);			  
		 			 	UI_menu(MENU_REC_DEL);
		 			 	bLedShowDelCnt=3;
		 			 #endif			  
		 //			  os_time_dly(300);
		               #endif
		                 file_auto_next = 1;
		 			  
		                 #if LED_SHOW_REC
		 
		                 #else			  
		 	                #if LED_SHOW_MP3
		 	                 setLedLight(LED_SHOW_MP3,led_mode_flash_fast_one_period,20);
		 	                #else
		 	                //led_fre_set(15);
		 	                #endif
		                 #endif
		 				
		 //                // MSG_MUSIC_EQ1("KEY_EVENT_NEXT\r\n");
		                 music_stop_decoder(mapi);
		                 _FIL_HDL *f_h=(_FIL_HDL *)(mapi->fop_api->cur_lgdev_info->lg_hdl->file_hdl);
		                 FIL *pf=(FIL *)(f_h->hdl);
		                 err=f_unlink(pf);
		 //                 printf("del file %08x  \n",err);
		                 #if 1
		 		os_time_dly(50);
		 		dac_mute(0,1);
		 		play_mode = REPEAT_ALL;
		 		mapi->fop_api->fop_init->cur_play_mode = play_mode;	
		 		err = music_play_api(mapi,DEV_SEL_CUR,0,PLAY_NEXT_FILE,&(mapi->dop_api->file_num));
		 
		 				
		                 #else
		                // if(mapi->dop_api->file_num)               
		 			   mapi->fop_api->fop_init->cur_play_mode = REPEAT_ALL;
		                 err = music_play_api(mapi,DEV_SEL_CUR,0,PLAY_NEXT_FOLDER,&(mapi->dop_api->file_num));
		                 err = music_play_api(mapi,DEV_SEL_CUR,0,PLAY_NEXT_FILE,&(mapi->dop_api->file_num));
		                 #endif
		                // else                
		                 break;
		 #endif

			case SYS_EVENT_DEV_ONLINE:

               #ifdef SUPPORT_MUSIC_STOP
				bStop_state=FALSE;
				bPause_state=0;
               #endif
			   
				
                // MSG_MUSIC_EQ1("music SYS_EVENT_DEV_ONLINE\r");
                ///music_stop_decoder(mapi->dop_api);
                // MSG_MUSIC_EQ1("AA\r");
                 #ifdef IO_MUTE_DELAY_ALL_STATE
                    #ifdef PA_ENABLE
					pa_mute();
                   #endif
				  bMuteDelayCnt=5;
                #endif
				
                 #ifdef LED_SHOW_DEVICE_PLUGIN	 
				 UI_menu(MENU_DEIVCE);
				 os_time_dly(50);
				// led7_var.dwDeviceID=0;			 
                 #endif
                mapi->dop_api->dec_api.save_brk = 1;
//                mapi->dop_api->dec_api.enable_brk = 1;
                mapi->dop_api->file_num = 1;

			 

          #ifdef MUSIC_PROMPT_EN
			#ifdef SUPPORT_SSM_VOICE	
				if(led7_var.bIfHaveVoice)
					err =music_prompt_play(SYS_EVENT_DEV_ONLINE,mapi);
				else
	              		  err = music_play_api(mapi,DEV_SEL_SPEC,msg[1],PLAY_BREAK_POINT,&(mapi->dop_api->file_num));				
				 #elif defined SUPPORT_ZY_SA_VOICE					 
				 	   if(IsVoiceEnable)
							music_prompt_play(SYS_EVENT_DEV_ONLINE,mapi);
					 else
	              			  err = music_play_api(mapi,DEV_SEL_SPEC,msg[1],PLAY_BREAK_POINT,&(mapi->dop_api->file_num));				
			#else
	              		  err = music_play_api(mapi,DEV_SEL_SPEC,msg[1],PLAY_BREAK_POINT,&(mapi->dop_api->file_num));				
			#endif
          #else
                err = music_play_api(mapi,DEV_SEL_SPEC,msg[1],PLAY_BREAK_POINT,&(mapi->dop_api->file_num));
          #endif
                // MSG_MUSIC_EQ1("BB\r");
				break;
			case SYS_EVENT_DEL_TASK: 				//请求删除music任务
	            #ifdef LED_SHOW_DEVICE_TYPE_SWITCH
					if((music_ui.ui_curr_device == SD0_DEVICE)||(music_ui.ui_curr_device == SD1_DEVICE))
					led7_var.blast_play_device=1;
					else if(music_ui.ui_curr_device == USB_DEVICE)
					led7_var.blast_play_device=2;
	            #endif
	            
                mapi->dop_api->dec_api.save_brk = 1; 
                music_stop_decoder(mapi);
                #ifndef LED_EXIT_MP3_NOT_SHOW_LOAD
                UI_menu(MENU_WAIT);                
                #elif MP3_NEXT_MODE_IS_AUX
                   #ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE
	                switch(bModeOfAuxContained){
	                  case mode_ac3:
						UI_menu(MENU_AC3_MAIN);
	                    break;
					 case mode_aux:
					   UI_menu(MENU_AUX_MAIN);
					   break;                 
	                }
                   #else
			#if REC_EN==0				   
                  		 UI_menu(MENU_AUX_MAIN);
			#endif
                   #endif
                #endif
                dac_channel_off(MUSIC_CHANNEL, FADE_OFF);
//                set_flac_sys_freq(0);//set_sys_clk
			 #ifdef SUPPORT_APE_FAST_MODE
			 	set_sys_freq(FLAC_SYS_Hz);			 
			 #endif
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

				///<关闭文件操作器，释放资源
				file_operate_ctl(FOP_CLOSE_LOGDEV,mapi->fop_api,0,0);
				///<释放文件操作器初始化信息
                if(mapi->fop_api)
                {
                    if(mapi->fop_api->fop_init)
                        free_fun((void**)&mapi->fop_api->fop_init);
                    free_fun((void**)&mapi->fop_api);
                }
                free_fun((void**)&mapi->dop_api->brk);
                free_fun((void**)&mapi->dop_api->io);
                free_fun((void**)&mapi->dop_api);
                free_fun((void**)&mapi);

				if (os_task_del_req_name(OS_TASK_SELF) == OS_TASK_DEL_REQ)
				{
					os_task_del_res_name(OS_TASK_SELF); 	//确认可删除，此函数不再返回
				}

				break;


		 #ifdef  support_power_off_tone
		 	case MSG_VOICE_POWER_OFF:
		    	{
		    		music_prompt_play(msg[0], mapi);
		    	}
		    	break;		 
		 #endif			

#ifdef SUPPORT_VOICE_ONOFF_VOICE	

 		case MSG_MUSIC_VOICE_ONOFF:
		 		
			  if(led7_var.bIfHaveVoice==1)		
			  	led7_var.bIfHaveVoice=0;
			  else 
			  	led7_var.bIfHaveVoice=1;
			  
			 #ifdef LED_SHOW_ONOFF
			 	UI_menu(MENU_ONOFF); 
			 #endif
			 
			 #ifdef support_voice_onoff_mem
			 	vm_write_api(VM_SYS_EQ,&led7_var.bIfHaveVoice);
			 #endif
			     #ifdef SUPPORT_MUSIC_STOP
			         bStop_state=FALSE;
			         bPause_state=0;
			     #endif		
			 music_prompt_play(msg[0],mapi);
				 

			break; 
#endif

#ifdef  SUPPORT_ZY_SA_VOICE

  		case MSG_MUSIC_VOICE_SWITCH:

		 #if defined SUPPORT_DOUBLE_VOICE
			 #ifdef SUPPORT_SSM_VOICE

				 if(IsVoiceEnable)
				 {
				 	voice_save=IsVoiceEnable;
				 	IsVoiceEnable = 0;
				 }
				 else
				 {
				 	IsVoiceEnable=voice_save;										
				 }
				 	led7_var.bIfHaveVoice=IsVoiceEnable;		
					
				 #ifdef LED_SHOW_ONOFF
				 	UI_menu(MENU_ONOFF); 
				 #endif
				 
				 #ifdef support_voice_onoff_mem
				 	vm_write_api(VM_SYS_EQ,&IsVoiceEnable);
				 #endif
				     #ifdef SUPPORT_MUSIC_STOP
				         bStop_state=FALSE;
				         bPause_state=0;
				     #endif		
				 music_prompt_play(msg[0],mapi);

			#else

	 			if(IsVoiceEnable==0)
	 			{
	 				IsVoiceEnable = 1;
	 		 		 #ifdef support_voice_onoff_mem
	 		 		 	vm_write_api(VM_SYS_EQ,&IsVoiceEnable);
	 		 		 #endif
	 				
	 			 	led7_var.bIfHaveVoice=IsVoiceEnable;
	 			 #ifdef LED_SHOW_ONOFF
	 			 	UI_menu(MENU_ONOFF); 
	 			 #endif								
	 			}
	 			else 

			if(IsVoiceEnable==1)
			{
				IsVoiceEnable = 2;
		 		 #ifdef support_voice_onoff_mem
		 		 	vm_write_api(VM_SYS_EQ,&IsVoiceEnable);
		 		 #endif
				
			 	led7_var.bIfHaveVoice=IsVoiceEnable;
			 #ifdef LED_SHOW_ONOFF
			 	UI_menu(MENU_ONOFF); 
			 #endif							
			}
			else if(IsVoiceEnable==2)
			{
				IsVoiceEnable = 0;
		 		 #ifdef support_voice_onoff_mem
		 		 	vm_write_api(VM_SYS_EQ,&IsVoiceEnable);
		 		 #endif
				
			 	led7_var.bIfHaveVoice=IsVoiceEnable;
			 #ifdef LED_SHOW_ONOFF
			 	UI_menu(MENU_ONOFF); 
			 #endif								
			}			
			#endif
		#else				
			 		
			 if(IsVoiceEnable)
			 {
			 	IsVoiceEnable = 0;
			 }
			 else
			 {
			 	IsVoiceEnable = 1;
			 }
			 	led7_var.bIfHaveVoice=!led7_var.bIfHaveVoice;		
				
			 #ifdef LED_SHOW_ONOFF
			 	UI_menu(MENU_ONOFF); 
			 #endif
			 
			 #ifdef support_voice_onoff_mem
			 	vm_write_api(VM_SYS_EQ,&IsVoiceEnable);
			 #endif
			     #ifdef SUPPORT_MUSIC_STOP
			         bStop_state=FALSE;
			         bPause_state=0;
			     #endif		
			 music_prompt_play(msg[0],mapi);
				 
		 #endif

			break; 
		 
	 #ifndef SUPPORT_ONLY_MODE_VOICE
			
		case MSG_VOICE_MUTE:		
		case MSG_VOICE_VOLUME_PLUS:		
		case MSG_VOICE_VOLUME_MINUS:		
	 	case MSG_MAX_VOICE:
	#ifdef  SUPPORT_NUMBER_VOICE
	 	case MSG_VOICE_NUMBER:
	#endif
		if(IsVoiceEnable)
	    	{
	    		music_prompt_play(msg[0], mapi);
	    	}
	    	break;

	 #endif
#endif

#ifdef SUPPORT_KEY_6_VOICE
            case MSG_VOICE_YESE:
            case MSG_VOICE_END:
            case MSG_VOICE_APPLAUD:
            case MSG_VOICE_GUN:
            case MSG_VOICE_ZXC:
           case MSG_VOICE_BEST_PARTNER:
	    		music_prompt_play(msg[0], mapi);
		break;	
#endif

            case MSG_HALF_SECOND:

	//	printf("-------music_ui.ui_curr_device-------%d \n",music_ui.ui_curr_device);

	//	printf("--music_ui.ui_curr_file- half--%d\n",music_ui.ui_curr_file);
		
		 #ifdef support_power_on_in_media_pause_state		 
		 	if(media_pause_timer>1)
		 		media_pause_timer--;
		 	else if(media_pause_timer==1)
		 	{
		 		media_pause_timer=0;
		 		 os_taskq_post("MusicTask", 1 , MSG_MUSIC_PP);
		 		break;
		 	}	
		 #endif



           #ifdef SUPPORT_REC_KEY_FIRST_CANCEL_RECPLAY_STATE
			//bRecReplayFlag=!bRecReplayFlag;
                 if(bCancelRecplayFlag>1)
				 	bCancelRecplayFlag--;
			 else if(bCancelRecplayFlag==1)
                 	{
				bCancelRecplayFlag=0;
//			      task_switch("RECTask", 0,SWITCH_SPEC_TASK);	
    		             os_taskq_post("MainTask", 1 , MSG_ONE_KEY_START_REC);
				  
			 }

           #endif				
				
                //dec_phy_// puts(" Music_H ");
               #ifdef SUPPORT_MUSIC_INTRO_PLAY
	               if(mp3_intro_play){
	                  bIntro_play_cnt++;
	                  if(bIntro_play_cnt>4)
	                  UI_menu(MENU_FILENUM);
	                  if(play_mode!=REPEAT_ALL){
						  if(mapi && mapi->fop_api && mapi->fop_api->fop_init)
						  { 			  
							  play_mode=REPEAT_ALL;			  
							  mapi->fop_api->fop_init->cur_play_mode = play_mode;
						  }
	                  }
	                 if(bIntro_play_cnt==20){
	                 bIntro_play_cnt=0;
	                 os_taskq_post("MusicTask", 1 , MSG_MUSIC_NEXT_FILE);
	                 }                
	               }
               #endif

			 #ifdef support_io_det_mute
			   if(bPause_state==0)
			   {
			     if( automute_sw)
			     	{
				     	automute_sw=0;
					pa_umute1();
			     	}
			   }
			 #endif
			   
              #if UI_ENABLE
			  
		           #ifdef LED_SHOW_DEL 			 
						 if(bLedShowDelCnt){
						 UI_menu(MENU_REC_DEL);
						 bLedShowDelCnt--;
						// os_time_dly(30);
						}else
		          #endif
				  
	                #ifdef SUPPORT_MUSIC_STOP
	                  #ifdef LED_SHOW_MP3_PAUSE
						if(bPause_state)
						UI_menu(MENU_AUX_PAUSE);
						else 
	     			  #endif
					if(bStop_state)
					UI_menu(MENU_MUSIC_STOP);
					else
	                #endif
	                {
	                UI_menu(MENU_MAIN);
	                UI_menu(MENU_HALF_SEC_REFRESH);
			   }
		#endif
			  
               #if IR_NUM_INPUT_EN
				if(ir_num_timeout_cnt){
				ir_num_timeout_cnt--;
				if(ir_num_timeout_cnt==0)				  
				 os_taskq_post_msg("MusicTask", 1, MSG_INPUT_TIMEOUT);
				}
               #endif

//		printf("=========music_ui.ui_total_file %d",music_ui.ui_total_file);
			   
             #ifdef AFTER_RECORD_PLAY_LAST_RECORDED_FILE
               if(bSendPrevFileCmdCnt){
                 bSendPrevFileCmdCnt--;
                 if(!bSendPrevFileCmdCnt){
					 #ifdef SUPPORT_LYX_RECPLAY_REPEAT_ONE
						 lyx_recplay_repeat_one_sw=1;
					 #endif
					 
					#ifdef SUPPORT_MEDIA_ONLY_REC_FOLDER_PROBLEM 
				 	   if(music_ui.ui_total_file>1)
					#endif
				 		{
							 os_taskq_post_msg("MusicTask", 1, MSG_MUSIC_PREV_FILE);
				 		}
					
					#ifdef SUPPORT_MEDIA_ONLY_REC_FOLDER_PROBLEM 					
						else
						{
				 			 #ifdef SUPPORT_LYX_RECPLAY_REPEAT_ONE
				 					 #ifdef SUPPORT_LYX_RECPLAY_REPEAT_ONE
				 					 if(lyx_recplay_repeat_one_sw==1)
				 					 	{
				 					   		play_mode = REPEAT_ONE;					 	
				 						 	mapi->fop_api->fop_init->cur_play_mode = play_mode;
				 							lyx_recplay_repeat_one_sw=0;
				 					 }
				 					 #endif
				 			 			 
				 			 #endif

						}
					#endif
					 //mapi->fop_api->fop_init->cur_play_mode = REPEAT_ALL;
					 }
               }
	             #ifdef SUPPORT_AUX_FM_BT_REPLAY_KEY
	 					  if(bAuxFmBtReplay_cnt){
	 					   bAuxFmBtReplay_cnt--;
	 					    if(bAuxFmBtReplay_cnt){
	 							os_taskq_post_msg("MusicTask", 1, MSG_REC_REPLAY);
	 					    }
	 					   }
	             #endif
             #endif     
			 
	                break;

            case MSG_LOW_POWER:
                // dec_phy_puts("Music_Low_Power\n");
                music_prompt_play(msg[0],mapi);
                break;

            case MSG_INPUT_TIMEOUT:
                /*由红外界面返回*/
                if ((input_number <= mapi->fop_api->cur_lgdev_info->total_file_num)&&(input_number != 0))
                {
                
                  #ifdef IO_MUTE_DELAY_ALL_STATE
                    #ifdef PA_ENABLE
  				   pa_mute();
                    #endif
    				 bMuteDelayCnt=3;
                  #endif
                    mapi->dop_api->file_num = input_number;
                    err = music_play_api(mapi,DEV_SEL_CUR,0,PLAY_SPEC_FILE,&(mapi->dop_api->file_num));
                }
                else
                    UI_menu(MENU_MUSIC_MAIN);

                input_number = 0;
                break;
            case SYS_EVNET_DEV_BEGIN_MOUNT:     ///<新设备开始枚举，结束解码，防止出现新设备枚举慢，当前设备播放
                 printf("new dev mount,stop  \n");   ///<一小段，又切换到新设备
                mapi->dop_api->dec_api.save_brk = 1;
                music_stop_decoder(mapi);
                break;
            case SYS_EVENT_DEV_MOUNT_ERR:       ///<新设备枚举失败，继续当前设备播放
                mapi->dop_api->dec_api.save_brk = 0;
                err = music_play_api(mapi,DEV_SEL_CUR,0,PLAY_BREAK_POINT,&(mapi->dop_api->file_num));
                break;
			default:
                // MSG_MUSIC_EQ1("dev status =%08x \n",err);
				break;
		}
		u32 totalerrfile=0;
		while(0 != err)
		{
		    // MSG_MUSIC_EQ1("err  : %02x\r",err);
		    u32 status;
            switch(err)
            {

	 #if 0 //def support_media_no_file_stop   
	                case FILE_OP_ERR_LGDEV_NULL:        ///<没有设备
 
                case FILE_OP_ERR_NO_FILE_ALLDEV:    ///<没有文件（所有设备）
      //              wait_exit=1;            ///<进入等待退出状态
                  err = 0;
	  
        		break;	
				
	 #endif				  

               case FILE_OP_ERR_INIT:              ///<文件选择器初始化错误
                case FILE_OP_ERR_OP_HDL:            ///<文件选择器指针错误
            case FILE_OP_ERR_LGDEV_NULL:        ///<没有设备
                case FILE_OP_ERR_NO_FILE_ALLDEV:    ///<没有文件（所有设备）

                    wait_exit=1;            ///<进入等待退出状态
                    file_operate_ctl(FOP_CLOSE_LOGDEV,0,0,0);
                 #ifdef SUPPORT_MP3_IDEL_MODE_IN_LINEIN_MODE 
                    {
			//	printf("-----FILE_OP_ERR_NO_FILE_ALLDEV------ %d\n",bModeOfAuxContained);
                    
              	   bModeOfAuxContained=mode_mp3_nodevice;
			   os_taskq_post("MainTask", 1, MSG_ONE_KEY_TO_AUX);	 //MSG_CHANGE_TO_BT_MODE		
			 }
                 #elif defined(usb_sd_out_to_bt_mode)
		         os_taskq_post("MainTask", 1, MSG_ONE_KEY_TO_BT);   //MSG_CHANGE_TO_BT_MODE
	         #elif defined(PLUG_OUT_DEV_TO_LINEIN_MODE)&&defined(SUPPORT_ONE_KEY_TO_AUX)		  
				 os_taskq_post("MainTask", 1, MSG_ONE_KEY_TO_AUX);	 //MSG_CHANGE_TO_BT_MODE		         
                 #else 				
                 	os_taskq_post("MainTask", 1, MSG_CHANGE_WORKMODE);
	        #endif 						
                
                    err = 0;
                    break;
					
			
  
                case FILE_OP_ERR_OPEN_BPFILE:
                    // MSG_MUSIC_EQ1("err  : %02x\r",err);
                    mapi->dop_api->file_num = 1;
                    err = music_play_api(mapi,DEV_SEL_CUR,0,PLAY_FIRST_FILE,&(mapi->dop_api->file_num));
                    break;
                case FILE_OP_ERR_NUM:               ///<选择文件的序号出错
                    mapi->dop_api->file_num = 1;
                    err = music_play_api(mapi,DEV_SEL_CUR,0,PLAY_SPEC_FILE,&(mapi->dop_api->file_num));
                    break;
                case FILE_OP_ERR_LGDEV_MOUNT:
                case FILE_OP_ERR_NO_FILE_ONEDEV:    ///<当前选择的设备没有文件
                    mapi->dop_api->file_num = 1;
                    err = music_play_api(mapi,DEV_SEL_NEXT,0,PLAY_SPEC_FILE,&(mapi->dop_api->file_num));
					
					
                    break;
                case FILE_OP_ERR_LGDEV_NO_FIND:     ///<没找到指定的逻辑设备
                    mapi->dop_api->file_num = 1;
                    err = music_play_api(mapi,DEV_SEL_NEXT,0,PLAY_SPEC_FILE,&(mapi->dop_api->file_num));
                    break;

                case SUCC_MUSIC_START_DEC:
                    err = 0;
                    file_auto_next = 1;
                    // MSG_MUSIC_EQ1("SUCC_MUSIC_START_DEC \r");
                    break;
                case FILE_OP_ERR_OPEN_FILE:         ///<打开文件失败
                case ERR_MUSIC_START_DEC:
                    status=file_operate_ctl(FOP_DEV_STATUS,mapi->fop_api,0,0);
                    if(status==FILE_OP_ERR_OP_HDL)
                    {       ///<逻辑设备不再链表
                        err=FILE_OP_ERR_OP_HDL;
                        break;
                    }
                    else
                        if(!status)
                        {   ///<逻辑设备掉线
                            err=FILE_OP_ERR_LGDEV_NO_FIND;
                            break;
                        }
                    totalerrfile++;
                    // MSG_MUSIC_EQ1("---total err =%08x \n",totalerrfile);
                    // MSG_MUSIC_EQ1("---total_file_num =%08x \n",mapi->fop_api->cur_lgdev_info->total_file_num);
                    if(totalerrfile>=mapi->fop_api->cur_lgdev_info->total_file_num)
                    {   ///<当前设备中音乐文件全部不可以解码，做好标识
                        file_operate_ctl(FOP_ALLFILE_ERR_LGDEV,mapi->fop_api,0,0);
                        err=FILE_OP_ERR_NO_FILE_ONEDEV;
                        totalerrfile=0;
                        break;
                    }
                    if(file_auto_next)
                    {
                        // MSG_MUSIC_EQ1("err next \r");
                        err = music_play_api(mapi,DEV_SEL_CUR,0,PLAY_NEXT_FILE,&(mapi->dop_api->file_num));
                    }
                    else
                    {
                        // MSG_MUSIC_EQ1("err priv \r");
                        err = music_play_api(mapi,DEV_SEL_CUR,0,PLAY_PREV_FILE,&(mapi->dop_api->file_num));
                    }
                    if((err!=FILE_OP_ERR_OPEN_FILE)&&(err!=ERR_MUSIC_START_DEC))
                    {   ///<不再是顺序找，清空错误数字
                        totalerrfile=0;
                    }
                    break;
                case ERR_MUSIC_API_NULL:
                    // printf("err  : %02x\r",err);
                    err = 0;
                    break;
                case FILE_OP_ERR_END_FILE:
                     mapi->dop_api->file_num = 1;
                     err = music_play_api(mapi,DEV_SEL_NEXT,0,PLAY_FIRST_FILE,&(mapi->dop_api->file_num));
                     break;
                case FILE_OP_ERR_PRE_FILE:
                     mapi->dop_api->file_num = 1;
                     err = music_play_api(mapi,DEV_SEL_PREV,0,PLAY_LAST_FILE,&(mapi->dop_api->file_num));
                     break;
                default:
                     printf("err default : %02x\r",err);
                    err = music_play_api(mapi,DEV_SEL_CUR,0,PLAY_NEXT_FILE,0);
                     printf("err my \n");
                    break;
            }
		}

		{
		    //// MSG_MUSIC_EQ1("no err\n");
		}

	}
}


static void music_task_init(void *priv)
{
	u32 err;
#ifdef DURING_FM_EXITING_TASK_NOT_RESPOND_KEY_MSG
	bExitFMStateCnt=2;
#endif
#ifdef POWER_ON_KEEP_MUTE_FOR_4S
	bAmpPowerOnMuteCnt=1;
#endif
#ifdef ONLY_POWER_ON_MUTE
#ifndef  support_standby_on_delay_umute_amp
	  bPowerOnMuteCnt=5;
#else
	  bPowerOnMuteCnt=1;
#endif
#endif

	err = os_task_create(music_task, 0, TaskMusicPrio, 50, "MusicTask");	
    if(OS_NO_ERR == err)
    {
       #if KEY_IO_EN
	    key_msg_register("MusicTask",music_ad_table,music_io_table,music_ir_table,NULL);   	   
	 #elif LED_KEY_MAX
		 #if KEY_AD_EN
	        key_msg_register("MusicTask",music_led_table,music_ad_table,NULL,music_ir_table,NULL);
		 #else
	        key_msg_register("MusicTask",music_ad_table,NULL,music_ir_table,NULL);
		 #endif   	   
       #else
        key_msg_register("MusicTask",music_ad_table,NULL,music_ir_table,NULL);
       #endif
    }
#if MP3_VOL_MAX
		if(bVolMaxChangeToSmallVolMax>=(SYS_VOL_MAX-MP3_VOL_MAX))
		dac_var.cur_sys_vol_l=bVolMaxChangeToSmallVolMax-(SYS_VOL_MAX-MP3_VOL_MAX);
		else
		dac_var.cur_sys_vol_l=0;
		dac_var.cur_sys_vol_r = dac_var.cur_sys_vol_l;
		set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);
     #if defined(PA_EN) 
		pa_umute();
     #endif 
#elif FM_VOL_MAX
		 if(bVolMaxChangeToSmallVolMax>=0)
		 dac_var.cur_sys_vol_l=bVolMaxChangeToSmallVolMax;
		 dac_var.cur_sys_vol_r = dac_var.cur_sys_vol_l;
#if defined(PA_EN) 
		 pa_umute();
#endif 			
		 set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);     
#elif defined(support_mode_change_vol_min_to_min)
		if(dac_var.cur_sys_vol_l<support_mode_change_vol_min_to_min)
		dac_var.cur_sys_vol_l=support_mode_change_vol_min_to_min;
		dac_var.cur_sys_vol_r = dac_var.cur_sys_vol_l;
#if defined(PA_EN) 
		pa_umute();
#endif 			
		set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);
#endif 

#ifdef KOK_DETECT_AUTO_VOL_SET		
	 store_vol= dac_var.cur_sys_vol_l;
#endif

#ifdef SUPPORT_PT2313
	Pt2313_ChangSource(Aud_SwMP3);
#endif    

#ifdef support_amP_ab_d
      Set_amp_ab_d_out() ;
       Set_AMP_IS_D();   
#endif 
#ifdef SUPPORT_FLASH_CHAR
 if(LED_FLASH_CHAR)
 LED_FLASH_CHAR=0;
 #endif

#ifdef  support_led_off_key 
#ifdef  support_change_mode_on_led
  led_on_flag =1;    // 0 关 1 开
#endif
#endif 
#if LED_SHOW_BT
setLedLight(LED_SHOW_BT,led_mode_off,0);
#endif
#ifdef SUPPORT_MUSIC_INTRO_PLAY
mp3_intro_play=FALSE;
#endif
#ifdef TF2025A_CONTROL_PB10_ALONG
TF2025A_SET_PB9_26PIN(1);
#endif
 #ifdef LED_SHOW_DEVICE_PLUGIN	
   UI_menu(MENU_DEIVCE);
   os_time_dly(25);
   //led7_var.dwDeviceID=0; 		   
#endif
#ifdef SUPPORT_MUSIC_STOP
	bStop_state=FALSE;
	bPause_state=0;
#endif

#if defined(LED_ID_JW2781)

led7_var.bEqCircleIfPlay=TRUE;
#endif


#ifdef support_sound_4052_control
	AC4052_IS_MP3();
#endif
#ifdef SUPPORT_USE_ENCODE_AS_MODE_CHANGE	
	bMulitWorkmode=MUSIC_WORK_MODE;
#endif

#ifdef SUPPORT_WOKRMODE
	workmode=MUSIC_WORK_MODE;
//	 printf("music 1111111111 workmode:%d \n",workmode);
#ifdef SUPPORT_MODE_VM
       vm_write_api(VM_SYS_EQ,&workmode);
#endif
//	 printf("music 222222222 workmode:%d \n",workmode);
#ifdef SUPPORT_MODE_VM
#ifdef SUPPORT_MULTIPLE_MODE_IN_LINEIN_MODE
bModeOfAuxContained=mode_aux;
#endif
#endif

#endif

}


static void music_task_exit()
{
	if (os_task_del_req("MusicTask") != OS_TASK_NOT_EXIST)
	{
		os_taskq_post_event("MusicTask", 1, SYS_EVENT_DEL_TASK);
		do{
			OSTimeDly(1);
		} while(os_task_del_req("MusicTask") != OS_TASK_NOT_EXIST);
		// puts("del_music_task: succ\n");
		
#ifdef support_usb_sd_PROMPT_EN	
		power_on_flag=0;
#endif
		
       #ifdef SUPPORT_MUSIC_STOP
		bStop_state=FALSE;
		bPause_state=0;
       #endif
       #ifdef SUPPORT_FLASH_ICON
       LED_FLASH_ICON=0;       
       #endif
       #ifdef SUPPORT_FLASH_CHAR
       LED_FLASH_CHAR=0;
       #endif       
       #ifdef SUPPORT_REPLAY_CANCEL_FOLDER_REPEAT_AND_PLAY_NOT_REC_FILES
	    bRecReplayFlag=FALSE;
       #endif
       #ifdef SUPPORT_MUTE_FLASH
	   b_muteFlag=FALSE;
      #endif
#if REC_EN
#ifdef support_rec_cancel_repeat_state_changemode_and_plus_out
	  play_mode=REPEAT_ALL;			  
#endif
#endif



	}
}


TASK_REGISTER(music_task_info) = {
	.name = "MusicTask",
	.init = music_task_init,
	.exit = music_task_exit,
};

