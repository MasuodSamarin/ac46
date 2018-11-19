#include "rtc_low_power.h"
#include "app_cfg.h"
#include "os_api.h"
#include "error.h"
#include "msg.h"
#include "config.h"
#include "irtc.h"
#include "rtc_setting.h"

#if RTC_CLK_EN

/*----------------------------------------------------------------------------*/
/**@brief 	RTC中断服务函数
   @param 	event：  唤醒的IO口，PR0-3，
   @param 	mode：   唤醒的方式，上/下边沿
   @return  void
   @note  	注意：PR3用于32K晶振，使用改口唤醒，可能会导致时钟停止
*/
/*----------------------------------------------------------------------------*/
void rtc_lowpower(u8 event,u8 mode)
{
    int temp = 0;

    ///PDFLG = 0,alm_en = 0 ,RTC wkup to sys en,
    write_RTC_reg(RTC_CON_WR,0x13);

    ///wakeup edge & en cant change at the same time
    temp = (mode &0xf0);
    printf("mode = %x\n",temp);
    write_RTC_reg(RTC_WK_EDG_EN_WR,temp);

    temp |= (event&0x0f);
    printf("mode | event = %x\n",temp);
    write_RTC_reg(RTC_WK_EDG_EN_WR,temp);

    ///CLR RTC IO WKUP PND
    write_RTC_reg(RTC_WK_PND_WR,0xf0);

    ///enter low power
    temp = read_RTC_reg(RTC_CON_RD);
    printf("read_rtc_con = %x\n",temp);
    temp |= BIT(4);

#if RTC_ALM_EN
    if(rtc_set.alarm_set.alarm_sw)
        temp |= BIT(5);//WK_EN  ALM_EN
    else
        temp &=~BIT(5);//WK_EN  ALM_DIS
#endif

    temp &= ~BIT(1);
    printf("temp = %x\n",temp);
    write_RTC_reg(RTC_CON_WR,temp);
}

/*----------------------------------------------------------------------------*/
/**@brief 	RTC低功耗函数
   @param 	void
   @return  void
   @note  	void rtc_lowpower_api(void)
*/
/*----------------------------------------------------------------------------*/
void rtc_lowpower_api(void)
{
    ///设置为输入
    PORTR_DIR(PORTR0,1);
    PORTR_DIR(PORTR1,1);
    PORTR_DIR(PORTR2,1);

    ///设置为输入时候，必须打开HD才能读取输入信号
    PORTR_HD(PORTR0,1);
    PORTR_HD(PORTR1,1);
    PORTR_HD(PORTR2,1);

    ///设置上拉
    PORTR_PU(PORTR0,1);
    PORTR_PU(PORTR1,1);
    PORTR_PU(PORTR2,1);

    ///关闭下拉
    PORTR_PD(PORTR0,0);
    PORTR_PD(PORTR1,0);
    PORTR_PD(PORTR2,0);

    ///设置唤醒信号
    rtc_lowpower(WAKE_UP_PR0|WAKE_UP_PR1|WAKE_UP_PR2, FALL_EDGE_PR0|FALL_EDGE_PR1|FALL_EDGE_PR2);
}
#endif
