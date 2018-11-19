#include "config.h"
#if EXTERN_KOK_DETECT_USE_IO_EN	
#include "kok_detect.h"
#include "device_driver.h"
#include "msg.h"
#ifdef KOK_DETECT_USE_IO_ADC_VALUE
#include "key_drv_ad.h"
#endif
//ȫ�ֱ���
KOK_VAR g_kok_var; ///<line in������

#ifdef KOK_DETECT_USE_IO_ADC_VALUE
#ifdef GW_020_GZY_REC_AC4601
#define KOK_VOLATAGE_05 1023*15/33
#else
#define KOK_VOLATAGE_05 1023*5/33
#endif
u16 kok_check_adc_value(void)
{
    if(adc_value[AD_CH_KOK]>KOK_VOLATAGE_05)
      return FALSE;
    else
      return TRUE;
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief  LINE IN ���߼��ʵ�庯��
   @param  cnt������˲�����
   @return �������
*/
/*----------------------------------------------------------------------------*/
KOK_STATUS kok_check(u8 cnt)
{
    u16 cur_kok_status;
    #ifdef KOK_DETECT_USE_IO_ADC_VALUE
    cur_kok_status=kok_check_adc_value();
    #else
    cur_kok_status = KOK_IN_CHECK(); //��ȡ��ǰAUX״̬
    #endif

    if(cur_kok_status != g_kok_var.pre_status)
    {
        g_kok_var.pre_status = cur_kok_status;
        g_kok_var.status_cnt = 0;
    }
    else
    {
        g_kok_var.status_cnt++;
    }
    if(g_kok_var.status_cnt < cnt) //����
    {
        if(g_kok_var.bDevOnline==KOK_ON) //����������������û�������һ��ʱ��ſ�����
        return NULL_KOK;
    }
    g_kok_var.status_cnt = 0;

    ///��⵽AUX����
    if((KOK_OFF == g_kok_var.bDevOnline) && (!g_kok_var.pre_status))
    {
        g_kok_var.bDevOnline = KOK_ON;
        return KOK_ON;
    }
    ///��⵽AUX�γ�
    else if((KOK_ON == g_kok_var.bDevOnline) && g_kok_var.pre_status)
    {
        g_kok_var.bDevOnline = KOK_OFF;
        return KOK_OFF;
    }

    return NULL_KOK;
}


/*----------------------------------------------------------------------------*/
/**@brief  LINE IN ���߼����Ⱥ���
   @param  ��
   @return �������
*/
/*----------------------------------------------------------------------------*/
s32 kok_detect(void)
{
    u32 dev_cur_sta = DEV_HOLD;
    KOK_STATUS res;
	
#ifdef KOK_DETECT_AUTO_VOL_SET			
	res = kok_check(50); //aux���߼�⣬ȥ������Ϊ50
#else
	res = kok_check(50); //aux���߼�⣬ȥ������Ϊ50
#endif

    if(KOK_OFF == res)
    {
       // aux_puts("phone_off\n");
        dev_cur_sta = DEV_OFFLINE;
    }
    else if(KOK_ON == res)
    {
       // aux_puts("phone_on\n");
        dev_cur_sta = DEV_ONLINE;
    }

    if(g_kok_var.last_sta == dev_cur_sta)
    {
        return DEV_HOLD;//�豸״̬���ֲ���
    }
	
    g_kok_var.last_sta = dev_cur_sta;

    return dev_cur_sta;
}


/*----------------------------------------------------------------------------*/
/**@brief  LINE IN ����״̬
   @param  ��
   @return LINE IN�������
   @note   u8 aux_is_online(void)
*/
/*----------------------------------------------------------------------------*/
u32 kok_is_online(void)
{
    return g_kok_var.bDevOnline;
}


/*----------------------------------------------------------------------------*/
/**@brief  LINE IN ģ���ʼ������
   @param  ��
   @return ��
   @note   void aux_init_api(void)
*/
/*----------------------------------------------------------------------------*/
void kok_init_api(void)
{
#if !defined(KOK_DETECT_USE_IO_ADC_VALUE)
    KOK_DETECT_IO_IN();
#endif    
    my_memset((u8 *)&g_kok_var, 0, sizeof(KOK_VAR));
}






/*----------------------------------------------------------------------------*/
/**@brief  LINE IN �����б�
   @note   const u8 aux_event_tab[]
*/
/*----------------------------------------------------------------------------*/
#if 0
const u8 kok_event_tab[] =
{
    SYS_EVENT_KOK_OUT, //PHONE  IN�γ�
    SYS_EVENT_KOK_IN,  //PHONE IN����
};
#endif

/*----------------------------------------------------------------------------*/
/**@brief  LINE IN ���߼��API����
   @param  ��
   @return ��
   @note   void aux_check_api(void)
*/
/*----------------------------------------------------------------------------*/

 #ifdef KOK_DETECT_AUTO_VOL_SET			
 bool auto_vol_sw; // 0 off   1 on
 u8 store_vol; // 
 #include "dac_api.h"
 #include "key.h"
#endif

void kok_check_api (u32 info)
{
    s32 dev_status;
#if !defined(KOK_DETECT_USE_IO_ADC_VALUE)
		KOK_DETECT_IO_IN();
#endif    
    dev_status = kok_detect();

        //    printf("1111111 jsuo 1111 g_kok_var.bKokKeyOpenFlag  %d \n",g_kok_var.bKokKeyOpenFlag); 

    if(dev_status != DEV_HOLD)
    {
        //os_taskq_post_event("MainTask", 2, kok_event_tab[dev_status],info);
        
        if(dev_status==DEV_ONLINE)  {
		 #ifdef KOK_DETECT_AUTO_VOL_SET			
			auto_vol_sw=1;
		 #else
		 
			 #if defined(KOK_DETECT_USE_KEY)
			 	if(g_kok_var.bKokKeyOpenFlag)
			 #endif
			 	dac_mute(1,1);
			 #if defined(KOK_DETECT_USE_KEY)
			 	else
			 	dac_mute(0,1);
			 #endif
	     #endif		  
           }
        else if(dev_status==DEV_OFFLINE)
			 #ifdef KOK_DETECT_AUTO_VOL_SET			
				auto_vol_sw=0;
			#else
			  dac_mute(0,1);
			#endif

    }
}
#endif 
