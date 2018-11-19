#include "avctp_user.h"
#include "system_cfg.h"
#include "aec_api.h"
#include "app_cfg.h"
#include "dac_api.h"
#include "vm_api.h"
#include "msg.h"
extern void get_battery_value_register(btstack_get_param_handle handle);
extern void hook_bt_trim_backup_register(void (*handle)(s16 i_dc,s16 q_dc));
extern void call_vol_change_handle_register(void (*handle)(int vol));
void bt_trim_check_handle_register(u8 (*handle)(void));
extern void read_remote_name_handle_register(void (*handle)(u8 *addr));
extern void discon_complete_handle_register(void (*handle)(int reason));
extern void bt_discon_complete_handle(int reason);
#if SYS_LVD_EN
extern u16 get_battery_value();
#endif
bt_simple_fun_handle btstack_info_init = NULL;

void btstack_info_init_register(bt_simple_fun_handle handle)
{
    btstack_info_init = handle;
}

void bt_profile_select_init(void)
{
    u8 support_profile;
    support_profile = SPP_CH | HFP_CH | A2DP_CH | AVCTP_CH | HID_CH | AVDTP_CH;
#if (USER_SUPPORT_PROFILE_HFP==0)
    support_profile &= ~HFP_CH;
#endif
#if (USER_SUPPORT_PROFILE_AVCTP==0)
    support_profile &= ~AVCTP_CH;
#endif
#if (USER_SUPPORT_PROFILE_A2DP==0)
    support_profile &= ~A2DP_CH;
    support_profile &= ~AVCTP_CH;
    support_profile &= ~AVDTP_CH;
#endif
#if (USER_SUPPORT_PROFILE_SPP==0)
    support_profile &= ~SPP_CH;
#endif
#if (USER_SUPPORT_PROFILE_HID== 0)
    support_profile &= ~HID_CH;
#endif

    bt_cfg_default_init(support_profile);/*外部设置支持什么协议*/

#if BT_HID_INDEPENDENT_MODE
    set_hid_independent_info();//要在 bt_cfg_default_init()设置后
#endif

}

void bt_configs_check()
{
    puts("bt_cfg_init\n");
    btcfg_aec_init();
    if(btstack_info_init)
    {
       btstack_info_init(); /*读取flash的配置文件*/
    }

    bt_profile_select_init();

    set_bt_name_len();

}

#if S10_MODE
    #define HOST_NAME "S10"
    #define HID_NAME "S10_HID"
#else
    #define HOST_NAME "AC46_SDK_DEBUG"
    #define HID_NAME "AC46_SDK_HID"
#endif

void bt_function_select_init()
{
    /*蓝牙功能流程选择配置*/
    u8 debug_addr[6] = {0x76, 0x46, 0x96, 0x66, 0x36, 0x76};
    __set_host_name(HOST_NAME,sizeof(HOST_NAME));
    __set_hid_name(HID_NAME,sizeof(HID_NAME));
    __set_pin_code("4567");
    __set_bt_mac_addr(debug_addr);

    clear_AAC_format();

    __bt_set_display_battery_enable(1); /*设置是否使能iphone手机的电量显示功能*/
    #if A2DP_AUTO_PLAY_EN
    __bt_set_a2dp_auto_play_flag(1); /*高级音频连接完成自动播放歌曲使能, 0不使能，1使能*/
    #else
    __bt_set_a2dp_auto_play_flag(0); /*高级音频连接完成自动播放歌曲使能, 0不使能，1使能*/
    #endif
    __bt_set_music_back_play_flag(0);/*当蓝牙连接后正常进入后台，为0是后台播放蓝牙音乐不返回,1可返回*/
    __set_simple_pair_flag(1);    /*提供接口外部设置配对方式,1使能简易配对。0使用pin code*/
    __set_a2dp_music_ef_enable(0,0); /*提供接口选择是否开EQ，第一个参数控制使能，1使能0不使能。第二参数初始EQ值*/
    __set_auto_conn_device_num(0);   /*该接口用于设置上电回连需要依次搜索设备的个数。0和1表示搜索最新的1个，大于1表示搜素多个。大于20无效*/

#ifdef BT_TESTER  /*测试盒*/
    __set_hid_auto_disconn_en(0);
    __set_test_masetr_enable(0);
    __set_super_timeout_value(1000);
#else
    __set_hid_auto_disconn_en(1);   /*是否自动断开手机的HID连接,1会断开，0是保留HID连接*/
    __set_test_masetr_enable(1);    /*接口配置是测试盒模式还是蓝牙SDK*/
    __set_super_timeout_value(8000);/*回连时超时参数设置。ms单位。但是对手机发起的连接是没作用的*/

#endif
}

 /*
    以下是一些库的钩子函数注册，一般用于改变参数。
    为了兼容不同客户对不同参数的需求，所有钩子函数不注册将使用默认参数。
 */
/*电量等级变化*/
int bt_get_battery_value()
{   //只支持0-9直接的值，10个等级
    #if SYS_LVD_EN
    return get_battery_value() - 34;
    #else
    return 8;
    #endif
}

/*电话时改变音量的状态值*/
void call_vol_change(int vol)
{
    printf("vol %d",vol);
}

void bt_read_remote_name(u8 *name)
{
    puts("\n remote name : ");
    puts((char *)name);
}

void bt_is_auto_conn(u8 auto_conn_flag)
{   //区分回连成功还是被连成功
    if(auto_conn_flag)
    {
        //回连成功
    }else{
        //被连成功
    }
}
/*回连搜索时间长度设置*/
//u32 hook_get_page_timeout()
//{   //回连搜索时间，7000代表7s，范围5000-10000
//    return 7000;
//}
//register_page_timeout_param(hook_get_page_timeout); //可使用该函数注册使用

/*
蓝牙库用到的一系列可设置参数配置，通过handle的形式。
这样用户就不用考虑调用配置函数的具体位置。需要改变可以注册，不需要设置有默认参数
*/
void bt_stack_handle_register()
{
     bt_function_select_init();/*相当于默认设置，要在协议栈初始化前设置*/
#ifdef BT_TESTER  /*测试盒*/
     btstack_info_init_register(bt_test_info_init);
     bt_stack_handle_register_for_test();
#else
     btstack_info_init_register(bt_info_init);  /*调试过程可以注掉，使用bt_configs结构体配置信息*/
     get_battery_value_register(bt_get_battery_value);
     hook_bt_trim_backup_register(hook_bt_trim_backup);
     bt_trim_check_handle_register(hook_bt_trim_check_crc);
     call_vol_change_handle_register(call_vol_change);
     read_remote_name_handle_register(bt_read_remote_name);
     discon_complete_handle_register(bt_discon_complete_handle);
#endif

}

int __bt_aec_priority()
{
	return TaskBtAecPrio;
}

//该函数主要是因为有一些宏的值可能会被用户的修改影响到，所以要通过接口获取。
///*特别注意返回值的范围*///
u8 __bt_get_macro_value(BT_STACK_MACRO type)
{
    switch(type)
    {
        case BT_MACRO_AEC_SD_PRIO:
            return TaskBtAecPrio;
        case BT_MACRO_SBC_PRIO:
            return TaskSbcPrio;
        case BT_MACRO_BTLMP_PRIO:
            return TaskBtLmpPrio;
        case BT_MACRO_BTSTACK_PRIO:
            return TaskBtStackPrio;
        case BT_MACRO_RESOURCE_PRIO:
            return TaskResoursrPrio;
        case BT_MACRO_MAX_SYS_VOL_L:
            return MAX_SYS_VOL_L;
        case BT_MACRO_MAX_SYS_VOL_R:
            return MAX_SYS_VOL_R;
        case BT_MACRO_SYSCFG_REMOTE_DB:
            return SYSCFG_REMOTE_DB;
        case BT_MACRO_SYSCFG_REMOTE_DB_HID:
            return SYSCFG_REMOTE_DB_HID;
        case BT_MACRO_MSG_LAST_WORKMOD:
            return MSG_LAST_WORKMOD;
        case BT_MACRO_SYS_EVENT_TASK_RUN_REQ:
            return SYS_EVENT_TASK_RUN_REQ;
        case BT_MACRO_MSG_BT_STACK_STATUS_CHANGE:
            return MSG_BT_STACK_STATUS_CHANGE;
        default:
            puts("check the lib\n");
            break;
    }
}


