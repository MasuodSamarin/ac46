#include "task_manage.h"
#include "os_api.h"
#include "msg.h"
#include "linein.h"
#include "usb_device.h"
#include "fm_radio.h"
#include "music.h"
#include "file_op.h"
#include "usb_slave_api.h"
#include "dev_linein.h"
#include "idle.h"
#include "rtc.h"

#if REC_EN
    #include "record.h"
    #include "encode.h"
#endif

struct task_info *curr_task;                 ///<当前处于前台运行的任务指针
struct task_info last_task_info;
extern TASK_REGISTER(btstack_task_info);
extern TASK_REGISTER(bt_hid_task_info);
#ifdef support_mode_key_user_usb_sd
extern bool  usb_to_sd_flag;    // USB SD 转换一次标记
#endif 

///任务切换
const struct task_info *task_list[] =
{
#ifdef MP3_AUX_BT_FM
        &music_task_info,
	 #ifndef support_off_line        
	     &linein_task_info,
	 #endif        
		&btstack_task_info,

      #if FM_RADIO_EN
		  &fm_radio_task_info,
      #endif
	  
#elif defined(AUX_MP3_BT_FM) 
	 #ifndef support_off_line        
	     &linein_task_info,
	 #endif        
        &music_task_info,
	&btstack_task_info,

      #if FM_RADIO_EN
		  &fm_radio_task_info,
      #endif
#elif defined(MP3_FM_AUX_BT) 

        &music_task_info,
        
      #if FM_RADIO_EN
		  &fm_radio_task_info,
      #endif	
	  
	 #ifndef support_off_line        
	     &linein_task_info,
	 #endif        
		&btstack_task_info,



#elif defined(MP3_BT) 

	  &music_task_info,
//	  &linein_task_info,
	  &btstack_task_info,
	  
#elif defined(MP3_AUX_FM_BT) 
	  &music_task_info,
	  &linein_task_info,
    #if FM_RADIO_EN
	  &fm_radio_task_info,
    #endif
	  &btstack_task_info,
    #if BT_HID_INDEPENDENT_MODE
	  &bt_hid_task_info,
    #endif
#elif defined(MP3_BT_FM_AUX)      
	  &music_task_info,
	  &btstack_task_info,
    #if BT_HID_INDEPENDENT_MODE
 	  &bt_hid_task_info,
    #endif
    #if FM_RADIO_EN
		&fm_radio_task_info,
    #endif
	 #ifndef support_off_line        	
	&linein_task_info,
	#endif	
#else
    &btstack_task_info,
#if BT_HID_INDEPENDENT_MODE
    &bt_hid_task_info,
#endif

    &music_task_info,

#if FM_RADIO_EN
    &fm_radio_task_info,
#endif

    &linein_task_info,
#endif


#if USB_PC_EN
    &pc_task_info,
#endif

#if RTC_CLK_EN
    &rtc_task_info,///<RTC
#endif

#if REC_EN
    &rec_task_info,///<REC
#endif

    &idle_task_info,
};

/*----------------------------------------------------------------------------*/
/**@brief  根据任务名字，获取任务指针
   @param  name：任务名字
   @return 指向传入任务名字的指针或者NULL
   @note
*/
/*----------------------------------------------------------------------------*/
static u32 __get_task(const char *name)
{
	u32 max_cnt;
	u32 task_cnt;

    max_cnt = sizeof(task_list)/sizeof(int);

	for(task_cnt = 0; task_cnt < max_cnt; task_cnt++)
	{
        if (!strcmp(task_list[task_cnt]->name, name))
		{
	//	    printf("task_list_cnt=0x%x\n", task_cnt);
		    return task_cnt;
		}
	}

	return -1;
}


/*----------------------------------------------------------------------------*/
/**@brief  任务筛选
   @param  ×task_cnt: 当前任务号
   @return  成功或者错误信息
   @note
*/
/*----------------------------------------------------------------------------*/
const struct task_dev_info music_task_2_dev =
{
    .name = "MusicTask",
    .dev_check = file_operate_get_total_phydev,
};

#if AUX_DETECT_EN
const struct task_dev_info linein_task_2_dev =
{
    .name = "LineinTask",
    .dev_check = aux_is_online,
};
#endif/*AUX_DETECT_EN*/

#if USB_PC_EN
const struct task_dev_info pc_task_2_dev =
{
    .name = "USBdevTask",
    .dev_check = usb_slave_online_status,
};
#endif/*USB_PC_EN*/

const struct task_dev_info *task_connect_dev[] =
{
    &music_task_2_dev,
#if AUX_DETECT_EN
    &linein_task_2_dev,
#endif/*AUX_DETECT_EN*/
#if USB_PC_EN
    &pc_task_2_dev,
#endif/*USB_PC_EN*/
};

static u32 skip_task_without_dev(u32 *task_cnt)
{
    u8 i;
    u32 max_cnt;
    u32 dev_cnt;

    max_cnt = (sizeof(task_list)/sizeof(int))-1;
    dev_cnt = sizeof(task_connect_dev)/sizeof(int);

    for(i = 0; i < dev_cnt; i++)
    {
        if(!strcmp(task_list[*task_cnt]->name, task_connect_dev[i]->name))
        {
            if(!task_connect_dev[i]->dev_check())
            {
                (*task_cnt)++;
                if(*task_cnt >= max_cnt)
                {
                #if S10_MODE
                    *task_cnt = 1;
                #else
                    *task_cnt = 0;
                #endif
                }

                if(skip_task_without_dev(task_cnt))
                    return TRUE;
                else
                    return FALSE;
            }
            else
                return TRUE;
        }
    }

    if(i == dev_cnt)
        return TRUE;
}


/*----------------------------------------------------------------------------*/
/**@brief  任务切换
   @param  task:     任务信息
   @param  priv:     给启动任务的参数
   @param  cur_mode：切换方式
   @return  成功或者错误信息
   @note
*/
/*----------------------------------------------------------------------------*/
static RUN_TASK_STATUS run_task(u32 task_cnt, void *priv, TASK_SWITCH_MODE cur_mode)
{
    u32 max_cnt;

    max_cnt = (sizeof(task_list)/sizeof(int))-1;

	if(cur_mode == SWITCH_SPEC_TASK)
	{
        if(task_list[task_cnt] == curr_task) ///<指定运行的任务，与当前正在运行的任务一致
            return RUN_TASK_ERR_HAS_RPT;
	}
    else
        if(cur_mode == SWITCH_NEXT_TASK)
        {
            task_cnt++;
            if (task_cnt >= max_cnt)
            {
#if S10_MODE
                task_cnt = 1;
#else
                task_cnt = 0;
#endif
            }
        }
    else
        if(cur_mode == SWITCH_PRE_TASK)
        {
            task_cnt--;
            if (task_cnt < 0)
            {
                task_cnt = max_cnt - 1;
            }
        }
    else if(cur_mode == SWITCH_LAST_TASK)
         {

         }
    skip_task_without_dev(&task_cnt); //忽略设备不在线的任务
    
#if REC_EN
  #ifdef MODE_CHANGE_SKIP_REC_CASE
			if((task_list[task_cnt]->name=="RECTask")&&(!compare_task_name("MusicTask"))){ //music录音时要进入REC模式，所以排除此条件
							task_cnt++;
							if (task_cnt >= max_cnt)
							{
					 #if S10_MODE
								task_cnt = 1;
					 #else
								task_cnt = 0;
					 #endif
							}
			}			
			skip_task_without_dev(&task_cnt); //忽略设备不在线的任务
  #endif
#endif
//    printf("*****Next_Task_Name2:%s\n",task_list[task_cnt]->name);

    task_list[task_cnt]->init((void *)(task_list[task_cnt]->name));
    curr_task = (struct task_info *)task_list[task_cnt];

    return RUN_TASK_SUCC;
}


RUN_TASK_STATUS task_switch(char *task_name,void *priv,TASK_SWITCH_MODE cur_mode)
{
    RUN_TASK_STATUS status;
    struct task_info *task;
    u32 task_cnt;
#ifdef support_mode_key_user_usb_sd
		usb_to_sd_flag=0;
#endif 

    GET_SYS_MEM_STAT();

    if(task_name)
    {
       task_cnt = __get_task(task_name);
       if(-1 == task_cnt)
       {
  //         puts("1111\n");
           return RUN_TASK_ERR_NO_TAG;
       }
       task = (struct task_info *)task_list[task_cnt];
       if(task==curr_task)
       {
   //        puts("2222\n");
           return RUN_TASK_ERR_HAS_RPT;
       }
    }
    else
    {
       if(curr_task)
       {
           task_cnt = __get_task(curr_task->name);
           if(-1 == task_cnt)
           {
    //           puts("3333\n");
               return RUN_TASK_ERR_NO_TAG;
           }
       }
       else            ///<当前没有运行任务，也没指定需要运行的任务
            return RUN_TASK_ERR_NO_TAG;
    }
//     puts("4444\n");

#if REC_EN
     //stop_rec(rec_op_api); //启动录音
#endif

    if(curr_task)
    {
        curr_task->exit(); //退出相应任务
        //puts(curr_task->name);
    }
    if(SWITCH_LAST_TASK == cur_mode)
    {
  //      puts("last mode\n");
        task_cnt = __get_task(last_task_info.name);
        // task_cnt = __get_task(last_task_info.name);
        //memcpy(&curr_task,last_task_info,sizeof(struct task_info));
    }else{
        memcpy(&last_task_info,curr_task,sizeof(struct task_info));
    }
    dac_mute(0,1);    //要完全退出之前的模式再解mute，不然会上个模式的尾音
    status = run_task(task_cnt, priv, cur_mode);

    return status;
}
/*----------------------------------------------------------------------------*/
/**@brief  删除一个任务
   @param  task_name：删除任务的名字
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void os_task_delete(char *task_name)
{
    if (os_task_del_req(task_name) != OS_TASK_NOT_EXIST)
	{
		os_taskq_post_event(task_name, 1, SYS_EVENT_DEL_TASK);
		do
		{
			OSTimeDly(1);
		} while(os_task_del_req(task_name) != OS_TASK_NOT_EXIST);
//		printf("delete task succ =%s \n",task_name);
	}
}

/*----------------------------------------------------------------------------*/
/**@brief  把任务设置为可删除状态
   @return
   @note   此函数由被删除的任务自己调用设置，在释放完占用的资源后，调用此
           函数，进入此函数后，不再返回，整个任务从这里结束
*/
/*----------------------------------------------------------------------------*/
void os_task_ready_delete()
{
    os_task_del_res(OS_TASK_SELF);
}


u32 compare_task_name(char *task_name)
{
    struct task_info *task;
    u32 task_cnt;

    if(task_name)
    {
       task_cnt = __get_task(task_name);
       if(-1 == task_cnt)
       {
  //         puts("curr_task---22\n");
           return 0;
       }
       task = (struct task_info *)task_list[task_cnt];
       if(task==curr_task)
       {
  //         puts("curr_task---1\n");
           return 1;
       }
    }
//    puts("curr_task---222\n");
    return 0;
}
