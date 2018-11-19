#include "config.h"
#include "dev_linein.h"
#include "device_driver.h"
#include "msg.h"
#include "linein.h"

//ȫ�ֱ���
AUX_VAR g_aux_var; ///<line in������

#ifdef support_line_chack_user_ad  //330K
#include "key_drv_ad.h"


u16 aux_check_adc_value(void)
{
    if(adc_value[AD_CH_KEY]>VOL_AD_NOKEY)
	      return TRUE;
    else if((adc_value[AD_CH_KEY]<VOL_AD_NOKEY)&&(adc_value[AD_CH_KEY]>VOL_AD_AUX_IN))
       return FALSE;

}
#endif


/*----------------------------------------------------------------------------*/
/**@brief  LINE IN ���߼��ʵ�庯��
   @param  cnt������˲�����
   @return �������
   @note   AUX_STATUS linein_check(u8 cnt)
*/
/*----------------------------------------------------------------------------*/
AUX_STATUS linein_check(u8 cnt)
{
    u16 cur_aux_status;

#ifdef BT_TESTER
    cur_aux_status = test_aux_check();

#else
    #if AUX_DETECT_EN
#ifdef support_line_chack_user_ad  //330K
    cur_aux_status = aux_check_adc_value();; //��ȡ��ǰAUX״̬
#else	
    cur_aux_status = AUX_IN_CHECK; //��ȡ��ǰAUX״̬
#endif    
    #endif
#endif
    if(cur_aux_status != g_aux_var.pre_status)
    {
        g_aux_var.pre_status = cur_aux_status;
        g_aux_var.status_cnt = 0;
    }
    else
    {
        g_aux_var.status_cnt++;
    }

#ifdef AUX_OUT_WITHOUT_CNT
///*//////�γ���ȥ��////////
    if((AUX_ON == g_aux_var.bDevOnline) && g_aux_var.pre_status)
    {
        g_aux_var.bDevOnline = AUX_OFF;
        return AUX_OFF;
    }
///*/////////////////////
#endif

    if(g_aux_var.status_cnt < cnt) //����
    {
        return NULL_AUX;
    }
    g_aux_var.status_cnt = 0;

    ///��⵽AUX����
    if((AUX_OFF == g_aux_var.bDevOnline) && (!g_aux_var.pre_status))
    {
        g_aux_var.bDevOnline = AUX_ON;
        return AUX_ON;
    }
#ifndef AUX_OUT_WITHOUT_CNT
    ///��⵽AUX�γ�
    else if((AUX_ON == g_aux_var.bDevOnline) && g_aux_var.pre_status)
    {
        g_aux_var.bDevOnline = AUX_OFF;
        return AUX_OFF;
    }
#endif

    return NULL_AUX;
}


/*----------------------------------------------------------------------------*/
/**@brief  LINE IN ���߼����Ⱥ���
   @param  ��
   @return �������
   @note   s32 aux_detect(void)
*/
/*----------------------------------------------------------------------------*/
s32 aux_detect(void)
{
    u32 dev_cur_sta = DEV_HOLD;
    AUX_STATUS res;
	

    res = linein_check(50); //aux���߼�⣬ȥ������Ϊ50


    if(AUX_OFF == res)
    {
        aux_puts("AUX_off\n");
        dev_cur_sta = DEV_OFFLINE;
    }
    else if(AUX_ON == res)
    {
        aux_puts("AUX_on\n");
        dev_cur_sta = DEV_ONLINE;
    }

    if(g_aux_var.last_sta == dev_cur_sta)
    {
        return DEV_HOLD;//�豸״̬���ֲ���
    }

    g_aux_var.last_sta = dev_cur_sta;

    return dev_cur_sta;
}


/*----------------------------------------------------------------------------*/
/**@brief  LINE IN ����״̬
   @param  ��
   @return LINE IN�������
   @note   u32 aux_is_online(void)
*/
/*----------------------------------------------------------------------------*/
u32 aux_is_online(void)
{
    return g_aux_var.bDevOnline;
}


/*----------------------------------------------------------------------------*/
/**@brief  LINE IN ģ���ʼ������
   @param  ��
   @return ��
   @note   void aux_init_api(void)
*/
/*----------------------------------------------------------------------------*/
void aux_init_api(void)
{
    /*linein check port set*/
#ifdef BT_TESTER
    set_aux_check_init();
#else
    #if AUX_DETECT_EN
    AUX_DIR_SET;
    AUX_PU_SET;
    #endif
#endif
    my_memset((u8 *)&g_aux_var, 0, sizeof(AUX_VAR));
}


/*----------------------------------------------------------------------------*/
/**@brief  LINE IN �����б�
   @note   const u8 aux_event_tab[]
*/
/*----------------------------------------------------------------------------*/
const u8 aux_event_tab[] =
{
    SYS_EVENT_AUX_OUT, //LINE IN�γ�
    SYS_EVENT_AUX_IN,  //LINE IN����
};


/*----------------------------------------------------------------------------*/
/**@brief  LINE IN ���߼��API����
   @param  ��
   @return ��
   @note   void aux_check_api(void)
*/
/*----------------------------------------------------------------------------*/
void aux_check_api(u32 info)
{
    s32 dev_status;

    dev_status = aux_detect();
    if(dev_status != DEV_HOLD)
    {
        os_taskq_post_event("MainTask", 2, aux_event_tab[dev_status],info);
    }
}
