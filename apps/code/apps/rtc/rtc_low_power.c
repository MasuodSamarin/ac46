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
/**@brief 	RTC�жϷ�����
   @param 	event��  ���ѵ�IO�ڣ�PR0-3��
   @param 	mode��   ���ѵķ�ʽ����/�±���
   @return  void
   @note  	ע�⣺PR3����32K����ʹ�øĿڻ��ѣ����ܻᵼ��ʱ��ֹͣ
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
/**@brief 	RTC�͹��ĺ���
   @param 	void
   @return  void
   @note  	void rtc_lowpower_api(void)
*/
/*----------------------------------------------------------------------------*/
void rtc_lowpower_api(void)
{
    ///����Ϊ����
    PORTR_DIR(PORTR0,1);
    PORTR_DIR(PORTR1,1);
    PORTR_DIR(PORTR2,1);

    ///����Ϊ����ʱ�򣬱����HD���ܶ�ȡ�����ź�
    PORTR_HD(PORTR0,1);
    PORTR_HD(PORTR1,1);
    PORTR_HD(PORTR2,1);

    ///��������
    PORTR_PU(PORTR0,1);
    PORTR_PU(PORTR1,1);
    PORTR_PU(PORTR2,1);

    ///�ر�����
    PORTR_PD(PORTR0,0);
    PORTR_PD(PORTR1,0);
    PORTR_PD(PORTR2,0);

    ///���û����ź�
    rtc_lowpower(WAKE_UP_PR0|WAKE_UP_PR1|WAKE_UP_PR2, FALL_EDGE_PR0|FALL_EDGE_PR1|FALL_EDGE_PR2);
}
#endif
