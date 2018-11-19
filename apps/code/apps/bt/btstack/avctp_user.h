#ifndef __AVCTP_USER_H__
#define __AVCTP_USER_H__


#include "typedef.h"

///***注意：该文件的枚举与库编译密切相关，主要是给用户提供调用所用。用户不能自己在中间添加值。*/
////----user (command) codes----////
typedef enum
{
/*
使用user_send_cmd_prepare(USER_CMD_TYPE cmd,u8 param_len,u8 *param)发送命令
//返回0表支持参数个数正确，返回1表不支持，2是参数错误
要三个参数，没参数说明的命令参数param_len传0，param传NULL
*/
    //查询库版本号
    USER_CTRL_BT_LIB_VERSION        ,   //直接返回一个U32值，代表版本号。方便客户查询
    USER_CTRL_LMP_LIB_VERSION       ,   //直接返回一个U32值，代表版本号。方便客户查询
    USER_CTRL_STACK_LIB_VERSION     ,   //直接返回一个U32值，代表版本号。方便客户查询

    //hfp链路部分
    //控制打电话音量
    USER_CTRL_HFP_CALL_VOLUME_UP    ,
    USER_CTRL_HFP_CALL_VOLUME_DOWN  ,
    //接通电话
    USER_CTRL_HFP_CALL_ANSWER       ,
    //挂断电话
    USER_CTRL_HFP_CALL_HANGUP       ,
    //回拨上一个打出电话
    USER_CTRL_HFP_CALL_LAST_NO      ,
    //获取当前通话电话号码
    USER_CTRL_HFP_CALL_CURRENT      ,
    //连接或断开SCO或esco,选择这个命令会自动判断要断开还是连接sco
    USER_CTRL_SCO_LINK              ,
    //连接SCO或esco
    USER_CTRL_CONN_SCO              ,
    //断开sco或esco
    USER_CTRL_DISCONN_SCO           ,
    //根据电话号码拨号
    /**命令有参数，参数要用数组先存起来，
    param_len是号码长度，param可传参数数组指针*/
    USER_CTRL_DIAL_NUMBER           ,
    //发送电量  /**要连接上HFP才有用*/
    USER_CTRL_SEND_BATTERY          ,


    //音乐控制部分
    //音乐播放
    USER_CTRL_AVCTP_OPID_PLAY       ,
    //音乐暂停
    USER_CTRL_AVCTP_OPID_PAUSE      ,
    //音乐停止
    USER_CTRL_AVCTP_OPID_STOP       ,
    //音乐下一首
    USER_CTRL_AVCTP_OPID_NEXT       ,
    //音乐上一首
    USER_CTRL_AVCTP_OPID_PREV       ,


    //链路操作部分
    //回连
    USER_CTRL_START_CONNECTION      ,
    //断开连接
    USER_CTRL_DISCONNECTION_HCI      ,
    //有判断条件的，回连过程连接高级音频，避免手机连也自动发起连接
    USER_CTRL_AUTO_CONN_A2DP         ,
    //连接高级音频
    USER_CTRL_CONN_A2DP              ,
    //断开高级音频
    USER_CTRL_DISCONN_A2DP           ,
    //断开SDP
    USER_CTRL_DISCONN_SDP_MASTER     ,
    //蓝牙关闭
    USER_CTRL_POWER_OFF              ,
    USER_CTRL_READ_SCAN_ENABLE       ,
    //关闭蓝牙可发现
    USER_CTRL_WRITE_SCAN_DISABLE     ,
    //打开蓝牙可发现
    USER_CTRL_WRITE_SCAN_ENABLE     ,

    ///*hid操作定义*/
    //按键连接
    USER_CTRL_HID_CONN               ,
    //只发一个按键，安卓手机使用
    USER_CTRL_HID_ANDROID            ,
    //只发一个按键，苹果和部分安卓手机适用
    USER_CTRL_HID_IOS                ,
    //发两个拍照按键
    USER_CTRL_HID_BOTH               ,
    //HID断开
    USER_CTRL_HID_DISCONNECT         ,

    ///蓝牙串口发送命令
    /**USER_CTRL_SPP_SEND_DATA命令有参数，参数会先存起来，
    param_len是数据长度，param发送数据指针
    返回0,表示准备成功，
    2表示发送buf申请空间失败
    3表示上一包数据没发完，用户要判断处理*/
    USER_CTRL_SPP_SEND_DATA         ,


    //蓝牙其他操作
    //删除最新的一个设备记忆
    USER_CTRL_DEL_LAST_REMOTE_INFO   ,
    //删除所有设备记忆
    USER_CTRL_DEL_ALL_REMOTE_INFO    ,

    USER_CTRL_LAST
}USER_CMD_TYPE;


////----反馈给客户使用的状态----////
typedef enum
{
     /*下面是一些即时反馈的状态，是get_bt_newest_status()获取*/
    BT_STATUS_POWER_ON   = 1   ,/*上电*/
    BT_STATUS_POWER_OFF  = 2   ,
    BT_STATUS_INIT_OK          ,/*初始化完成*/
    BT_STATUS_CONNECTED        ,/*连接成功*/
    BT_STATUS_DISCONNECT       ,/*断开连接*/
    BT_STATUS_PHONE_INCOME     ,/*来电*/
    BT_STATUS_PHONE_NUMBER     ,/*来电话好吗*/
    BT_STATUS_PHONE_OUT        ,/*打出电话*/
    BT_STATUS_PHONE_ACTIVE     ,/*接通电话*/
    BT_STATUS_PHONE_HANGUP     ,/*挂断电话*/
    BT_STATUS_BEGIN_AUTO_CON   ,/*发起回连*/
    BT_STATUS_MUSIC_SOUND_COME ,/*库中加入auto mute判断音乐播放开始*/
    BT_STATUS_MUSIC_SOUND_GO   ,/*库中加入auto mute判断音乐播放暂停*/
    BT_STATUS_RESUME           ,/*后台有效，手动切回蓝牙*/
    BT_STATUS_RESUME_BTSTACK   ,/*后台有效，后台时来电切回蓝牙*/
    BT_STATUS_SUSPEND          ,/*蓝牙挂起，退出蓝牙*/
    BT_STATUS_TONE_BY_FILE_NUM   ,/*直接使用文件号播放提示音*/

   /*下面是6个持续的状态，是get_bt_connect_status()获取*/
    BT_STATUS_INITING          ,/*正在初始化*/
    BT_STATUS_WAITINT_CONN     ,/*等待连接*/
    BT_STATUS_CONNECTING       ,/*已连接，没有电话和音乐在活动*/
    BT_STATUS_AUTO_CONNECTINT  ,/*正在回连*/
    BT_STATUS_TAKEING_PHONE    ,/*正在电话*/
    BT_STATUS_PLAYING_MUSIC    ,/*正在音乐*/
}STATUS_FOR_USER;

typedef enum
{
    BT_CALL_BATTERY_CHG = 0, //电池电量改变
    BT_CALL_SIGNAL_CHG,      //网络信号改变
    BT_CALL_INCOMING,   //电话打入
    BT_CALL_OUTGOING,   //电话打出
    BT_CALL_ACTIVE,     //接通电话
    BT_CALL_HANGUP,      //电话挂断
    BT_CALL_ALERT,       //远端reach
	BT_CALL_VOL_CHANGED,
}BT_CALL_IND_STA;

typedef enum
{
    BT_MACRO_AEC_SD_PRIO = 1 ,  //优先级宏
    BT_MACRO_SBC_PRIO       ,
    BT_MACRO_BTLMP_PRIO     ,
    BT_MACRO_BTSTACK_PRIO   ,
    BT_MACRO_RESOURCE_PRIO  ,
    BT_MACRO_MAX_SYS_VOL_L  ,  //音乐最大音量
    BT_MACRO_MAX_SYS_VOL_R  ,
    BT_MACRO_SYSCFG_REMOTE_DB ,
    BT_MACRO_SYSCFG_REMOTE_DB_HID,
    BT_MACRO_MSG_LAST_WORKMOD ,
    BT_MACRO_SYS_EVENT_TASK_RUN_REQ,
    BT_MACRO_MSG_BT_STACK_STATUS_CHANGE ,
}BT_STACK_MACRO;




typedef enum
{
    BT_MUSIC_STATUS_IDLE = 0,
    BT_MUSIC_STATUS_STARTING,
    BT_MUSIC_STATUS_SUSPENDING,
}BT_MUSIC_STATE;   //音乐状态

///---sdp service record profile- 用户选择支持协议--///
#define USER_SUPPORT_PROFILE_SPP    0
#define USER_SUPPORT_PROFILE_HSP    0

#if 1//SUPPORT_BT_TALK_EN
//#define USER_SUPPORT_PROFILE_HFP    1
#else
//#define USER_SUPPORT_PROFILE_HFP    0
#endif
#define USER_SUPPORT_PROFILE_A2DP   1
#define USER_SUPPORT_PROFILE_AVCTP  1
#ifndef BT_TESTER
    #ifdef AC46_512K
        #define USER_SUPPORT_PROFILE_HID    0    ///512K HID
    #else
        #define USER_SUPPORT_PROFILE_HID    0
    #endif
#else
    #define USER_SUPPORT_PROFILE_HID    1
#endif

//#define BT_PROMPT_EN     //任意时间按照文件号播文件

#define    SPP_CH       0x01
#define    HFP_CH       0x02
#define    A2DP_CH      0x04    //media
#define    AVCTP_CH     0x08
#define    HID_CH       0x10
#define    AVDTP_CH     0x20

typedef void (*bt_simple_fun_handle)(void);

extern u32 user_send_cmd_prepare(USER_CMD_TYPE cmd,u8 param_len,u8 *param);

extern void usre_cmd_timeout_check(void);

/*
u8 get_curr_channel_state();  与  channel  判断区分
主动获取当前链路的连接状态，可以用来判断有哪些链路连接上了
*/
extern u8 get_curr_channel_state();
/*
u8 get_last_call_type();
用于获取前一次使用蓝牙通话时来电还是打出
*/
extern u8 get_last_call_type();

/*
u8 get_call_status(); 与BT_CALL_IND_STA 枚举的值判断
用于获取当前蓝牙电话的状态
*/
extern u8 get_call_status();
extern void user_cmd_ctrl_init();

extern void bt_info_init(void);
extern void bt_test_info_init(void);
extern void hook_bt_trim_backup(s16 i_dc,s16 q_dc);
extern u8 hook_bt_trim_check_crc(void);

extern void bt_cfg_default_init(u8 support);
/*用户调试设置地址，6个byte*/
extern void __set_bt_mac_addr(u8* addr);
/*用户设置独立hid的name,最长32个字符*/
extern void __set_hid_name(char *name,u8 len);
/*用户调试设置name,最长32个字符*/
extern void __set_host_name(char *name,u8 len);
/*用户调试设置pin code*/
extern void __set_pin_code(char *code);
/*该接口用于设置上电回连需要依次搜索设备的个数。*/
extern void __set_auto_conn_device_num(u8 num);
/*该接口用于返回设置蓝牙音乐的音效使能。*/
extern void __set_a2dp_music_ef_enable(u8 enable,u8 eq);

extern void __set_a2dp_music_eq(u8 eq_mode);
/*//回连的超时设置。ms单位。但是对手机发起的连接是没作用的*/
extern void __set_super_timeout_value(u32 time );
/*接口配置是测试盒模式还是蓝牙SDK*/
extern void __set_test_masetr_enable(u8 en);
/*提供接口配置是否自动断开手机的HID连接*/
extern int __set_hid_auto_disconn_en(u8 flag);
/*外部设置支持什么协议*/
extern void bt_cfg_default_init(u8 support);
/*hid作为独立模式时要设置*/
extern void set_hid_independent_info();

/*提供动态设置音乐自动播放的接口。
  该接口使用的时间点有要求，要在A2DP连接之前设置
   */
extern void __bt_set_a2dp_auto_play_flag(u8 flag);

/*提供函数接口设置是否需要后台音乐返回*/
extern void __bt_set_music_back_play_flag(u8 flag);

/*提供接口外部设置配对方式*/
extern void __set_simple_pair_flag(u8 flag);

extern bool get_remote_test_flag();
/*获取当前是否是独立的HID模式*/
extern u8 __get_hid_independent_flag();

extern u8 get_bt_newest_status(void);
extern void update_bt_current_status(u8 new_status,u8 conn_status);
extern u8 get_bt_connect_status(void);
extern u8 get_bt_prev_status(void);
extern void update_bt_prev_status(u8 status);
extern bool get_suspend_flag();
extern void hook_btstack_suspend();
extern u8 __bt_get_macro_value(BT_STACK_MACRO type);
#endif
