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

    bt_cfg_default_init(support_profile);/*�ⲿ����֧��ʲôЭ��*/

#if BT_HID_INDEPENDENT_MODE
    set_hid_independent_info();//Ҫ�� bt_cfg_default_init()���ú�
#endif

}

void bt_configs_check()
{
    puts("bt_cfg_init\n");
    btcfg_aec_init();
    if(btstack_info_init)
    {
       btstack_info_init(); /*��ȡflash�������ļ�*/
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
    /*������������ѡ������*/
    u8 debug_addr[6] = {0x76, 0x46, 0x96, 0x66, 0x36, 0x76};
    __set_host_name(HOST_NAME,sizeof(HOST_NAME));
    __set_hid_name(HID_NAME,sizeof(HID_NAME));
    __set_pin_code("4567");
    __set_bt_mac_addr(debug_addr);

    clear_AAC_format();

    __bt_set_display_battery_enable(1); /*�����Ƿ�ʹ��iphone�ֻ��ĵ�����ʾ����*/
    #if A2DP_AUTO_PLAY_EN
    __bt_set_a2dp_auto_play_flag(1); /*�߼���Ƶ��������Զ����Ÿ���ʹ��, 0��ʹ�ܣ�1ʹ��*/
    #else
    __bt_set_a2dp_auto_play_flag(0); /*�߼���Ƶ��������Զ����Ÿ���ʹ��, 0��ʹ�ܣ�1ʹ��*/
    #endif
    __bt_set_music_back_play_flag(0);/*���������Ӻ����������̨��Ϊ0�Ǻ�̨�����������ֲ�����,1�ɷ���*/
    __set_simple_pair_flag(1);    /*�ṩ�ӿ��ⲿ������Է�ʽ,1ʹ�ܼ�����ԡ�0ʹ��pin code*/
    __set_a2dp_music_ef_enable(0,0); /*�ṩ�ӿ�ѡ���Ƿ�EQ����һ����������ʹ�ܣ�1ʹ��0��ʹ�ܡ��ڶ�������ʼEQֵ*/
    __set_auto_conn_device_num(0);   /*�ýӿ����������ϵ������Ҫ���������豸�ĸ�����0��1��ʾ�������µ�1��������1��ʾ���ض��������20��Ч*/

#ifdef BT_TESTER  /*���Ժ�*/
    __set_hid_auto_disconn_en(0);
    __set_test_masetr_enable(0);
    __set_super_timeout_value(1000);
#else
    __set_hid_auto_disconn_en(1);   /*�Ƿ��Զ��Ͽ��ֻ���HID����,1��Ͽ���0�Ǳ���HID����*/
    __set_test_masetr_enable(1);    /*�ӿ������ǲ��Ժ�ģʽ��������SDK*/
    __set_super_timeout_value(8000);/*����ʱ��ʱ�������á�ms��λ�����Ƕ��ֻ������������û���õ�*/

#endif
}

 /*
    ������һЩ��Ĺ��Ӻ���ע�ᣬһ�����ڸı������
    Ϊ�˼��ݲ�ͬ�ͻ��Բ�ͬ�������������й��Ӻ�����ע�Ὣʹ��Ĭ�ϲ�����
 */
/*�����ȼ��仯*/
int bt_get_battery_value()
{   //ֻ֧��0-9ֱ�ӵ�ֵ��10���ȼ�
    #if SYS_LVD_EN
    return get_battery_value() - 34;
    #else
    return 8;
    #endif
}

/*�绰ʱ�ı�������״ֵ̬*/
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
{   //���ֻ����ɹ����Ǳ����ɹ�
    if(auto_conn_flag)
    {
        //�����ɹ�
    }else{
        //�����ɹ�
    }
}
/*��������ʱ�䳤������*/
//u32 hook_get_page_timeout()
//{   //��������ʱ�䣬7000����7s����Χ5000-10000
//    return 7000;
//}
//register_page_timeout_param(hook_get_page_timeout); //��ʹ�øú���ע��ʹ��

/*
�������õ���һϵ�п����ò������ã�ͨ��handle����ʽ��
�����û��Ͳ��ÿ��ǵ������ú����ľ���λ�á���Ҫ�ı����ע�ᣬ����Ҫ������Ĭ�ϲ���
*/
void bt_stack_handle_register()
{
     bt_function_select_init();/*�൱��Ĭ�����ã�Ҫ��Э��ջ��ʼ��ǰ����*/
#ifdef BT_TESTER  /*���Ժ�*/
     btstack_info_init_register(bt_test_info_init);
     bt_stack_handle_register_for_test();
#else
     btstack_info_init_register(bt_info_init);  /*���Թ��̿���ע����ʹ��bt_configs�ṹ��������Ϣ*/
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

//�ú�����Ҫ����Ϊ��һЩ���ֵ���ܻᱻ�û����޸�Ӱ�쵽������Ҫͨ���ӿڻ�ȡ��
///*�ر�ע�ⷵ��ֵ�ķ�Χ*///
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


