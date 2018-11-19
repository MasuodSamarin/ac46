#include "config.h"
#if EXTERN_KOK_DETECT_USE_IO_EN	
#include "kok_detect.h"
#include "device_driver.h"
#include "msg.h"
#ifdef KOK_DETECT_USE_IO_ADC_VALUE
#include "key_drv_ad.h"
#endif
//全局变量
KOK_VAR g_kok_var; ///<line in检测变量

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
/**@brief  LINE IN 在线检测实体函数
   @param  cnt：检测滤波次数
   @return 在线情况
*/
/*----------------------------------------------------------------------------*/
KOK_STATUS kok_check(u8 cnt)
{
    u16 cur_kok_status;
    #ifdef KOK_DETECT_USE_IO_ADC_VALUE
    cur_kok_status=kok_check_adc_value();
    #else
    cur_kok_status = KOK_IN_CHECK(); //获取当前AUX状态
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
    if(g_kok_var.status_cnt < cnt) //消抖
    {
        if(g_kok_var.bDevOnline==KOK_ON) //有声音立即静音，没声音后隔一段时间才开静音
        return NULL_KOK;
    }
    g_kok_var.status_cnt = 0;

    ///检测到AUX插入
    if((KOK_OFF == g_kok_var.bDevOnline) && (!g_kok_var.pre_status))
    {
        g_kok_var.bDevOnline = KOK_ON;
        return KOK_ON;
    }
    ///检测到AUX拔出
    else if((KOK_ON == g_kok_var.bDevOnline) && g_kok_var.pre_status)
    {
        g_kok_var.bDevOnline = KOK_OFF;
        return KOK_OFF;
    }

    return NULL_KOK;
}


/*----------------------------------------------------------------------------*/
/**@brief  LINE IN 在线检测调度函数
   @param  无
   @return 在线情况
*/
/*----------------------------------------------------------------------------*/
s32 kok_detect(void)
{
    u32 dev_cur_sta = DEV_HOLD;
    KOK_STATUS res;
	
#ifdef KOK_DETECT_AUTO_VOL_SET			
	res = kok_check(50); //aux在线检测，去抖计数为50
#else
	res = kok_check(50); //aux在线检测，去抖计数为50
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
        return DEV_HOLD;//设备状态保持不变
    }
	
    g_kok_var.last_sta = dev_cur_sta;

    return dev_cur_sta;
}


/*----------------------------------------------------------------------------*/
/**@brief  LINE IN 在线状态
   @param  无
   @return LINE IN在线情况
   @note   u8 aux_is_online(void)
*/
/*----------------------------------------------------------------------------*/
u32 kok_is_online(void)
{
    return g_kok_var.bDevOnline;
}


/*----------------------------------------------------------------------------*/
/**@brief  LINE IN 模块初始化函数
   @param  无
   @return 无
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
/**@brief  LINE IN 在线列表
   @note   const u8 aux_event_tab[]
*/
/*----------------------------------------------------------------------------*/
#if 0
const u8 kok_event_tab[] =
{
    SYS_EVENT_KOK_OUT, //PHONE  IN拔出
    SYS_EVENT_KOK_IN,  //PHONE IN插入
};
#endif

/*----------------------------------------------------------------------------*/
/**@brief  LINE IN 在线检测API函数
   @param  无
   @return 无
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
