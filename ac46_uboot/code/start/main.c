#include "config.h"
#include "timer.h"
#include "boot.h"
#include "dac_api.h"
#include "dac.h"

#ifdef  UPDATA_LED_REMIND
//#define S10_UPDATE_OK
void led_debug_init(void)
{
    ///*------------------------*/
#ifdef S10_UPDATE_OK
    USB_CON0 |= BIT(0)|BIT(1);//PHY_ON(enable)  IO_MODE(enable)
    USB_IO_CON = 0;
    USB_IO_CON &= ~BIT(3)//USB_DM DIR OUT
#endif
}


void led_debug_finsh(void)
{
    ///*------------------------*/
#ifdef S10_UPDATE_OK
    USB_IO_CON |= BIT(1);//USB_DM OUT 1
#endif
}
#endif


void main(SDF_IO *pSDF, u32 addr, u32 prevApp)
{
    volatile u32 spec_upadta_flag = 0;
    volatile u32 check_res, run_res;
    volatile UPDATA_RESULT updata_res;

    if(TMR0_PRD != 0xffff)
    {
        spec_upadta_flag = 0x552233;
    }

    sys_init(pSDF); //<系统初始化:不可以在该函数前调用打印函数

__ALL_UPDATA_CHECK:
    check_res = flash_data_check(); //<spi初始化检测
    if(0x552233 == spec_upadta_flag)
    {
        check_res = 1;
    }

    ///设备升级
__DEV_UPDATA:
///************************升级前初始化******************************/
#ifdef  UPDATA_LED_REMIND                                           ///
    led_debug_init();                                               ///
#endif                                                              ///
///*******************************************************************/


    updata_res = updata_mode(pSDF, check_res); //<设备升级流程
    if((DEV_UPDATA_FAIL == updata_res) || \
        NO_UPDATA_DEV == updata_res)
    {
        if(0x552233 == spec_upadta_flag)
        {
            goto __DEV_UPDATA;
        }
        else
        {
            goto __APP_RUN;
        }
    }

///***********************升级完成后设置*****************************/
#ifdef  UPDATA_LED_REMIND                                           ///
    led_debug_finsh();                                              ///
#endif                                                              ///
#ifdef  UPDATA_VOICE_REMIND                                         ///
    audio_init();                                                   ///
    audio_set();                                                    ///
#endif                                                              ///
///*******************************************************************/

    deg_puts("\n***********updata ok***************\n");
    while(1)
    {
#ifdef UPDATA_VOICE_REMIND
        send_key_voice(500);
        delay(0x3fffff);
#endif
        //deg_puts("请复位\n");
    }

    ///代码校验跳转
__APP_RUN:
    run_res = app_run();
    if(FALSE == run_res)
    {
        goto __ALL_UPDATA_CHECK;
    }
}

