#include "app_cfg.h"
#include "error.h"
#include "mango_dev_sd.h"
#include "system_cfg.h"
#include "stdarg.h"
#include "music_info.h"
#include "msg.h"
#include "task_manage.h"
#include "play_sel.h"
#include "dac_api.h"
#include "drv_manage.h"
#include "ui_api.h"

#include "tff.h"
#include "fs_io.h"

#ifdef AFTER_RECORD_PLAY_LAST_RECORDED_FILE
extern u32 dwLastRecFile;
extern bool bIfRecordFolder;
#endif

FS_NAME music_file_name;
LONG_FILE_NAME lfn_music;
//MP3_ID3 *mp3_head;



#ifdef SUPPORT_APE_FAST_MODE
void get_decode_ops_name(char *name)
{
	if(0==strcmp("FLA",name))
	{
		set_sys_freq(FLAC_SYS_Hz);
	}
	else if(0==strcmp("APE",name))
	{
		set_sys_freq(160000000L);
	}
}
#else

void set_flac_sys_freq(u8 flag)
{
    if(flag)
    {
        puts("\nSYS = 120M\n");
        set_sys_freq(FLAC_SYS_Hz);
    }
    else
    {
        puts("\nSYS = 96M\n");
        set_sys_freq(SYS_Hz);
    }
}

#endif

void * music_get_file_id3(u32 len)
{
    u8* id3_buf = NULL;

    if(len <= 3*1024)
        id3_buf = malloc(len);

//    // printf("------len = %x byte\n",len);
//    // printf("id3_buf malloc = %x byte----\n",id3_buf);

    return id3_buf;
}

void music_file_info(MUSIC_OP_API *m_op_api)
{
    file_operate_ctl(FOP_GET_FILE_NAME,m_op_api->fop_api,0,&music_file_name);
//        music_file_name = fs_file_name(m_op_api->fop_api->cur_lgdev_info->lg_hdl->file_hdl);
    // printf("music_file_path %s\n",music_file_name.tpath);

    // printf("----long_file_name %d\n",music_file_name.lfn_cnt);
    // printf_buf(music_file_name.lfn,music_file_name.lfn_cnt);

    // printf("----long_folder_name %d\n",music_file_name.ldn_cnt);
    // printf_buf(music_file_name.lfn+LFN_MAX_SIZE,music_file_name.ldn_cnt);
    
#ifdef AFTER_RECORD_PLAY_LAST_RECORDED_FILE
   // if(get_floder_name(music_file_name.lfn,music_file_name.tpath[2]))
   // /JL_REC     /AC460001MP3
  // if(&music_file_name.tpath[2]=="/JL_REL     /")

#ifdef MODIFY_REC_FILE_NAME_FOR_ZY
    if(strstr(music_file_name.tpath,"/JLREC")!=NULL)
#else
    if(strstr(music_file_name.tpath,"/JL_REC")!=NULL)
#endif
	bIfRecordFolder=TRUE;
	else
	bIfRecordFolder=FALSE;
#endif
 //       // printf("-1111111111--bIfRecordFolder %d\n",bIfRecordFolder);

//    decode_lfn((void *)&lfn_music,music_file_name.lfn,music_file_name.lfn_cnt);
}
#if 0
bool bCompareFolderName(char* ptr)
{
  if(strcmp(ptr,"JL_REC 	") == 0)
  return 1;
  else return 0;
}
#endif
u8 get_floder_name(char* ptr,u32 filecount)
{
#ifdef MODIFY_REC_FILE_NAME_FOR_ZY
    if(strcmp(ptr,"JLREC	 ") == 0)
#else
    if(strcmp(ptr,"JL_REC     ") == 0)
#endif
    {
        // printf("-11111111--ptr %s--\n",ptr);
        // printf("-11111111--filecount %d\n",filecount);
        #ifdef AFTER_RECORD_PLAY_LAST_RECORDED_FILE
        //bIfRecordFolder=TRUE;
        #endif
        return 1;
    }
   // "JL_REC     "
   #ifdef AFTER_RECORD_PLAY_LAST_RECORDED_FILE
    //bIfRecordFolder=FALSE;
   #endif
    return 0;
}

#ifdef SUPPORT_REC_STOP_PLAY_REC_FILE
u32 curr_dir_file_num;
#endif
void get_floder_totalfile(u32 filecount)
{
    // printf("-1111111--totalfile %d\n",filecount);

#ifdef SUPPORT_REC_STOP_PLAY_REC_FILE
	curr_dir_file_num=filecount;
#endif
    //    // printf("-1111111--dir_exsit %d\n",dir_exsit);

#ifdef AFTER_RECORD_PLAY_LAST_RECORDED_FILE
	dwLastRecFile=filecount;
#endif
}
