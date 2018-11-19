#ifndef __AVCTP_USER_H__
#define __AVCTP_USER_H__


#include "typedef.h"

///***ע�⣺���ļ���ö��������������أ���Ҫ�Ǹ��û��ṩ�������á��û������Լ����м����ֵ��*/
////----user (command) codes----////
typedef enum
{
/*
ʹ��user_send_cmd_prepare(USER_CMD_TYPE cmd,u8 param_len,u8 *param)��������
//����0��֧�ֲ���������ȷ������1��֧�֣�2�ǲ�������
Ҫ����������û����˵�����������param_len��0��param��NULL
*/
    //��ѯ��汾��
    USER_CTRL_BT_LIB_VERSION        ,   //ֱ�ӷ���һ��U32ֵ������汾�š�����ͻ���ѯ
    USER_CTRL_LMP_LIB_VERSION       ,   //ֱ�ӷ���һ��U32ֵ������汾�š�����ͻ���ѯ
    USER_CTRL_STACK_LIB_VERSION     ,   //ֱ�ӷ���һ��U32ֵ������汾�š�����ͻ���ѯ

    //hfp��·����
    //���ƴ�绰����
    USER_CTRL_HFP_CALL_VOLUME_UP    ,
    USER_CTRL_HFP_CALL_VOLUME_DOWN  ,
    //��ͨ�绰
    USER_CTRL_HFP_CALL_ANSWER       ,
    //�Ҷϵ绰
    USER_CTRL_HFP_CALL_HANGUP       ,
    //�ز���һ������绰
    USER_CTRL_HFP_CALL_LAST_NO      ,
    //��ȡ��ǰͨ���绰����
    USER_CTRL_HFP_CALL_CURRENT      ,
    //���ӻ�Ͽ�SCO��esco,ѡ�����������Զ��ж�Ҫ�Ͽ���������sco
    USER_CTRL_SCO_LINK              ,
    //����SCO��esco
    USER_CTRL_CONN_SCO              ,
    //�Ͽ�sco��esco
    USER_CTRL_DISCONN_SCO           ,
    //���ݵ绰���벦��
    /**�����в���������Ҫ�������ȴ�������
    param_len�Ǻ��볤�ȣ�param�ɴ���������ָ��*/
    USER_CTRL_DIAL_NUMBER           ,
    //���͵���  /**Ҫ������HFP������*/
    USER_CTRL_SEND_BATTERY          ,


    //���ֿ��Ʋ���
    //���ֲ���
    USER_CTRL_AVCTP_OPID_PLAY       ,
    //������ͣ
    USER_CTRL_AVCTP_OPID_PAUSE      ,
    //����ֹͣ
    USER_CTRL_AVCTP_OPID_STOP       ,
    //������һ��
    USER_CTRL_AVCTP_OPID_NEXT       ,
    //������һ��
    USER_CTRL_AVCTP_OPID_PREV       ,


    //��·��������
    //����
    USER_CTRL_START_CONNECTION      ,
    //�Ͽ�����
    USER_CTRL_DISCONNECTION_HCI      ,
    //���ж������ģ������������Ӹ߼���Ƶ�������ֻ���Ҳ�Զ���������
    USER_CTRL_AUTO_CONN_A2DP         ,
    //���Ӹ߼���Ƶ
    USER_CTRL_CONN_A2DP              ,
    //�Ͽ��߼���Ƶ
    USER_CTRL_DISCONN_A2DP           ,
    //�Ͽ�SDP
    USER_CTRL_DISCONN_SDP_MASTER     ,
    //�����ر�
    USER_CTRL_POWER_OFF              ,
    USER_CTRL_READ_SCAN_ENABLE       ,
    //�ر������ɷ���
    USER_CTRL_WRITE_SCAN_DISABLE     ,
    //�������ɷ���
    USER_CTRL_WRITE_SCAN_ENABLE     ,

    ///*hid��������*/
    //��������
    USER_CTRL_HID_CONN               ,
    //ֻ��һ����������׿�ֻ�ʹ��
    USER_CTRL_HID_ANDROID            ,
    //ֻ��һ��������ƻ���Ͳ��ְ�׿�ֻ�����
    USER_CTRL_HID_IOS                ,
    //���������հ���
    USER_CTRL_HID_BOTH               ,
    //HID�Ͽ�
    USER_CTRL_HID_DISCONNECT         ,

    ///�������ڷ�������
    /**USER_CTRL_SPP_SEND_DATA�����в������������ȴ�������
    param_len�����ݳ��ȣ�param��������ָ��
    ����0,��ʾ׼���ɹ���
    2��ʾ����buf����ռ�ʧ��
    3��ʾ��һ������û���꣬�û�Ҫ�жϴ���*/
    USER_CTRL_SPP_SEND_DATA         ,


    //������������
    //ɾ�����µ�һ���豸����
    USER_CTRL_DEL_LAST_REMOTE_INFO   ,
    //ɾ�������豸����
    USER_CTRL_DEL_ALL_REMOTE_INFO    ,

    USER_CTRL_LAST
}USER_CMD_TYPE;


////----�������ͻ�ʹ�õ�״̬----////
typedef enum
{
     /*������һЩ��ʱ������״̬����get_bt_newest_status()��ȡ*/
    BT_STATUS_POWER_ON   = 1   ,/*�ϵ�*/
    BT_STATUS_POWER_OFF  = 2   ,
    BT_STATUS_INIT_OK          ,/*��ʼ�����*/
    BT_STATUS_CONNECTED        ,/*���ӳɹ�*/
    BT_STATUS_DISCONNECT       ,/*�Ͽ�����*/
    BT_STATUS_PHONE_INCOME     ,/*����*/
    BT_STATUS_PHONE_NUMBER     ,/*���绰����*/
    BT_STATUS_PHONE_OUT        ,/*����绰*/
    BT_STATUS_PHONE_ACTIVE     ,/*��ͨ�绰*/
    BT_STATUS_PHONE_HANGUP     ,/*�Ҷϵ绰*/
    BT_STATUS_BEGIN_AUTO_CON   ,/*�������*/
    BT_STATUS_MUSIC_SOUND_COME ,/*���м���auto mute�ж����ֲ��ſ�ʼ*/
    BT_STATUS_MUSIC_SOUND_GO   ,/*���м���auto mute�ж����ֲ�����ͣ*/
    BT_STATUS_RESUME           ,/*��̨��Ч���ֶ��л�����*/
    BT_STATUS_RESUME_BTSTACK   ,/*��̨��Ч����̨ʱ�����л�����*/
    BT_STATUS_SUSPEND          ,/*���������˳�����*/
    BT_STATUS_TONE_BY_FILE_NUM   ,/*ֱ��ʹ���ļ��Ų�����ʾ��*/

   /*������6��������״̬����get_bt_connect_status()��ȡ*/
    BT_STATUS_INITING          ,/*���ڳ�ʼ��*/
    BT_STATUS_WAITINT_CONN     ,/*�ȴ�����*/
    BT_STATUS_CONNECTING       ,/*�����ӣ�û�е绰�������ڻ*/
    BT_STATUS_AUTO_CONNECTINT  ,/*���ڻ���*/
    BT_STATUS_TAKEING_PHONE    ,/*���ڵ绰*/
    BT_STATUS_PLAYING_MUSIC    ,/*��������*/
}STATUS_FOR_USER;

typedef enum
{
    BT_CALL_BATTERY_CHG = 0, //��ص����ı�
    BT_CALL_SIGNAL_CHG,      //�����źŸı�
    BT_CALL_INCOMING,   //�绰����
    BT_CALL_OUTGOING,   //�绰���
    BT_CALL_ACTIVE,     //��ͨ�绰
    BT_CALL_HANGUP,      //�绰�Ҷ�
    BT_CALL_ALERT,       //Զ��reach
	BT_CALL_VOL_CHANGED,
}BT_CALL_IND_STA;

typedef enum
{
    BT_MACRO_AEC_SD_PRIO = 1 ,  //���ȼ���
    BT_MACRO_SBC_PRIO       ,
    BT_MACRO_BTLMP_PRIO     ,
    BT_MACRO_BTSTACK_PRIO   ,
    BT_MACRO_RESOURCE_PRIO  ,
    BT_MACRO_MAX_SYS_VOL_L  ,  //�����������
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
}BT_MUSIC_STATE;   //����״̬

///---sdp service record profile- �û�ѡ��֧��Э��--///
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

//#define BT_PROMPT_EN     //����ʱ�䰴���ļ��Ų��ļ�

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
u8 get_curr_channel_state();  ��  channel  �ж�����
������ȡ��ǰ��·������״̬�����������ж�����Щ��·��������
*/
extern u8 get_curr_channel_state();
/*
u8 get_last_call_type();
���ڻ�ȡǰһ��ʹ������ͨ��ʱ���绹�Ǵ��
*/
extern u8 get_last_call_type();

/*
u8 get_call_status(); ��BT_CALL_IND_STA ö�ٵ�ֵ�ж�
���ڻ�ȡ��ǰ�����绰��״̬
*/
extern u8 get_call_status();
extern void user_cmd_ctrl_init();

extern void bt_info_init(void);
extern void bt_test_info_init(void);
extern void hook_bt_trim_backup(s16 i_dc,s16 q_dc);
extern u8 hook_bt_trim_check_crc(void);

extern void bt_cfg_default_init(u8 support);
/*�û��������õ�ַ��6��byte*/
extern void __set_bt_mac_addr(u8* addr);
/*�û����ö���hid��name,�32���ַ�*/
extern void __set_hid_name(char *name,u8 len);
/*�û���������name,�32���ַ�*/
extern void __set_host_name(char *name,u8 len);
/*�û���������pin code*/
extern void __set_pin_code(char *code);
/*�ýӿ����������ϵ������Ҫ���������豸�ĸ�����*/
extern void __set_auto_conn_device_num(u8 num);
/*�ýӿ����ڷ��������������ֵ���Чʹ�ܡ�*/
extern void __set_a2dp_music_ef_enable(u8 enable,u8 eq);

extern void __set_a2dp_music_eq(u8 eq_mode);
/*//�����ĳ�ʱ���á�ms��λ�����Ƕ��ֻ������������û���õ�*/
extern void __set_super_timeout_value(u32 time );
/*�ӿ������ǲ��Ժ�ģʽ��������SDK*/
extern void __set_test_masetr_enable(u8 en);
/*�ṩ�ӿ������Ƿ��Զ��Ͽ��ֻ���HID����*/
extern int __set_hid_auto_disconn_en(u8 flag);
/*�ⲿ����֧��ʲôЭ��*/
extern void bt_cfg_default_init(u8 support);
/*hid��Ϊ����ģʽʱҪ����*/
extern void set_hid_independent_info();

/*�ṩ��̬���������Զ����ŵĽӿڡ�
  �ýӿ�ʹ�õ�ʱ�����Ҫ��Ҫ��A2DP����֮ǰ����
   */
extern void __bt_set_a2dp_auto_play_flag(u8 flag);

/*�ṩ�����ӿ������Ƿ���Ҫ��̨���ַ���*/
extern void __bt_set_music_back_play_flag(u8 flag);

/*�ṩ�ӿ��ⲿ������Է�ʽ*/
extern void __set_simple_pair_flag(u8 flag);

extern bool get_remote_test_flag();
/*��ȡ��ǰ�Ƿ��Ƕ�����HIDģʽ*/
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
