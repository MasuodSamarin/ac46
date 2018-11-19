#include "os_api.h"
#include "config.h"
#include "msg.h"
#include "irtc.h"
#include "rtc_setting.h"
#include "task_manage.h"

#if RTC_CLK_EN
/*----------------------------------------------------------------------------*/
/**@brief 	RTC�жϷ�����
   @param 	void
   @return  void
   @note  	void rtc_isr(void)
*/
/*----------------------------------------------------------------------------*/
void rtc_isr(void)
{

    volatile u16 rtc_con = IRTC_CON;

    rtc_puts("--enter rtc_isr --\n");

    IRTC_CON |= BIT(15)|BIT(13)|BIT(11);  //clr irtc wkup pnd
    DSP_CLR_ILAT = BIT(8);

#if RTC_ALM_EN
    if(rtc_con & BIT(7))///<WKUP_PND
    {
        rtc_puts("--ALM-ON--\n");
        //IRTC_WKCLRPND;

        rtc_set.alarm_set.alarm_sw = 0;
        alm_sw(rtc_set.alarm_set.alarm_sw);//���ֺ�ر�����

        rtc_set.alarm_set.alarm_flag = 1;
        if(!compare_task_name(RTC_TASK_NAME))
        {
            os_taskq_post_msg("MainTask", 1, MSG_ALM_ON);
            //task_switch(RTC_TASK_NAME,0,SWITCH_SPEC_TASK);
        }
    }
#endif
    if(rtc_con & BIT(5))///<X512_PND
    {
        rtc_puts("--X512--\n");
        //IRTC_X512CLRPND;
    }

    if(rtc_con & BIT(3))///<X2_PND
    {
        rtc_puts("--X2--\n");
        //IRTC_X2CLRPND;
    }
}

/*----------------------------------------------------------------------------*/
/**@brief 	��дRTC�Ĵ���
   @param 	dat���Ĵ���ֵ
   @return  IRTC_BUF
   @note  	u8 irtc_sr_byte(u8 dat)
*/
/*----------------------------------------------------------------------------*/
u8 irtc_sr_byte(u8 dat)
{
    IRTC_BUF = dat;                 //add��д����Ĵ���������һ�η����ݣ�һ���ֽڣ�
    asm("CSYNC;");
    while (!(IRTC_CON & BIT(1)));   //ͨ����ɣ��Զ���1
    return IRTC_BUF;                //ͨ����ɺ󣬶��üĴ����õ����յ�����
}

/*----------------------------------------------------------------------------*/
/**@brief 	дRTC�Ĵ���
   @param 	cmd���Ĵ���ֵ
   @return  void
   @note  	void write_RTC_reg(u8 reg, u8 dat)
*/
/*----------------------------------------------------------------------------*/
void write_RTC_reg(u8 reg, u8 dat)
{
    IRTC_CS_EN;
    irtc_sr_byte(reg);      //reg
    irtc_sr_byte(dat);      //dat
    IRTC_CS_DIS;
}

/*----------------------------------------------------------------------------*/
/**@brief 	��RTC�Ĵ���
   @param 	reg���Ĵ���ֵ
   @return  void
   @note  	u8 read_RTC_reg(u8 reg)
*/
/*----------------------------------------------------------------------------*/
u8 read_RTC_reg(u8 reg)
{
    u8 dat;

    IRTC_CS_EN;
    irtc_sr_byte(reg);
    dat = irtc_sr_byte(0);
    IRTC_CS_DIS;

    return dat;
}

void PORTR_DIR(u8 port, u8 val)
{
    u8 reg;
    reg = read_RTC_reg(RTC_PR_DIR_OUT_RD);
    port<<=4;
    if(val)
    {
        reg |= port;//BIT(port);
    }
    else
    {
        reg &=~port;//BIT(port);
    }
    //printf("DIR_reg:%x\n",reg);
    write_RTC_reg(RTC_PR_DIR_OUT_WR,reg);
}

void PORTR_OUT(u8 port, u8 val)
{
    u8 reg;
    reg = read_RTC_reg(RTC_PR_DIR_OUT_RD);
    //port<<=4;
    if(val)
    {
        reg |= port;//BIT(port);
    }
    else
    {
        reg &=~port;//BIT(port);
    }
    //printf("OUT_reg:%x\n",reg);
    write_RTC_reg(RTC_PR_DIR_OUT_WR,reg);
}

void PORTR_HD(u8 port, u8 val)
{
    u8 reg;
    reg = read_RTC_reg(RTC_PR_HD_IN_RD);
    port<<=4;
    if(val)
    {
        reg |= port;//BIT(port);
    }
    else
    {
        reg &=~port;//BIT(port);
    }
    //printf("HD_reg:%x\n",reg);
    write_RTC_reg(RTC_PR_HD_IN_WR,reg);
}

void PORTR_PU(u8 port, u8 val)
{
    u8 reg;
    reg = read_RTC_reg(RTC_PR_PD_PU_RD);
    //port<<=4;
    if(val)
    {
        reg |= port;//BIT(port);
    }
    else
    {
        reg &=~port;//BIT(port);
    }
    write_RTC_reg(RTC_PR_PD_PU_WR,reg);
}

void PORTR_PD(u8 port, u8 val)
{
    u8 reg;
    reg = read_RTC_reg(RTC_PR_PD_PU_RD);
    port<<=4;
    if(val)
    {
        reg |= port;//BIT(port);
    }
    else
    {
        reg &=~port;//BIT(port);
    }
    write_RTC_reg(RTC_PR_PD_PU_WR,reg);
}
/*
void PORTR_DIE(u8 port, u8 val)
{
    u8 reg;
    reg = read_RTC_reg(RTC_PR_DIR_OUT_RD);
    port<<=4;
    if(val)
    {
        reg |= BIT(port);
    }
    else
    {
        reg &=~BIT(port);
    }
    write_RTC_reg(RTC_PR_DIR_OUT_WR,reg);
}
*/

void PORTR_ADCEN(u8 port,u8 val)
{
    u8 reg;
    reg = read_RTC_reg(RTC_CON_RD);
    port <<= 2;
    if(val)
    {
        reg |= port;
    }
    else
    {
        reg &= ~port;
    }
    write_RTC_reg(RTC_CON_WR,reg);
}

u8 PORTR_IN(u8 port)
{
    u8 reg;
    PORTR_HD(port,1);//��ȡ����״̬��������HD
    reg = read_RTC_reg(RTC_PR_HD_IN_RD);
    return (reg & port);
}

/*----------------------------------------------------------------------------*/
/**@brief 	дIRTC
   @param 	cmd��дָ�� w_time:д������
   @return  void
   @note  	void write_irtc_time(u8 cmd, sRTC_TIME *w_time)
*/
/*----------------------------------------------------------------------------*/
void write_irtc_time(tu8 cmd, RTC_TIME *w_time)
{
    tu8 buf;
    u16 w_day;

    IRTC_CS_EN;
    irtc_sr_byte(cmd);

    w_day = ymd_to_day(w_time);

    buf = (u8)(w_day>>8);
    irtc_sr_byte(buf);
    buf = (u8)(w_day);
    irtc_sr_byte(buf);

    buf = w_time->bHour;
    irtc_sr_byte(buf);

    buf = w_time->bMin;
    irtc_sr_byte(buf);

    buf = w_time->bSec;
    irtc_sr_byte(buf);

    IRTC_CS_DIS;
}

/*----------------------------------------------------------------------------*/
/**@brief 	��IRTC
   @param 	cmd����ָ�� r_time������������
   @return  void
   @note  	void read_IRTC(u8 cmd, sRTC_TIME *r_time)
*/
/*----------------------------------------------------------------------------*/
void read_irtc_time(u8 cmd, RTC_TIME *r_time)
{
    u16 r_day;

    IRTC_CS_EN;
    irtc_sr_byte(cmd);//READ_RTC

    r_day = irtc_sr_byte(0x0);
    r_day <<=8;
    r_day += irtc_sr_byte(0x0);

    day_to_ymd(r_day, r_time);  //add�����������ɣ���-��-��
    r_time->bHour = irtc_sr_byte(0x0);//putbyte('h'); printf(" %d\n",((r_time->bHour)));
    r_time->bMin  = irtc_sr_byte(0x0);//putbyte('m');printf(" %d\n",((r_time->bMin)));
    r_time->bSec  = irtc_sr_byte(0x0);//putbyte('s');printf(" %d\n",((r_time->bSec)));
    //add��day day hour minute second
    //add: �����ɸߵ��ͣ�һ�ζ�1��byte
    IRTC_CS_DIS;
}

/*----------------------------------------------------------------------------*/
/**@brief 	дRTCʱ��
   @param 	void
   @return  void
   @note  	void write_RTC(sRTC_TIME *curr_time)
*/
/*----------------------------------------------------------------------------*/
void write_rtc_time(RTC_TIME *curr_time)
{
    write_irtc_time(WRITE_RTC, curr_time);
}

/*----------------------------------------------------------------------------*/
/**@brief 	��RTCʱ��
   @param 	void
   @return  void
   @note  	void write_RTC(sRTC_TIME *curr_time)
*/
/*----------------------------------------------------------------------------*/
void read_rtc_time(RTC_TIME *curr_time)
{
    read_irtc_time(READ_RTC, curr_time);
}

/*----------------------------------------------------------------------------*/
/**@brief 	дRTCʱ��
   @param 	void
   @return  void
   @note  	void write_RTC(sRTC_TIME *curr_time)
*/
/*----------------------------------------------------------------------------*/
void write_alm_time(RTC_TIME *curr_time)
{
    write_irtc_time(WRITE_ALM, curr_time);
}

/*----------------------------------------------------------------------------*/
/**@brief 	��RTCʱ��
   @param 	void
   @return  void
   @note  	void write_RTC(sRTC_TIME *curr_time)
*/
/*----------------------------------------------------------------------------*/
void read_alm_time(RTC_TIME *curr_time)
{
    read_irtc_time(READ_ALM, curr_time);
}

/*----------------------------------------------------------------------------*/
/**@brief 	updata_alm_time
   @param 	void
   @return  void
   @note  	void updata_alm_time(RTC_TIME *curr_time,RTC_TIME *curr_alm)������ʱ�䵽����
*/
/*----------------------------------------------------------------------------*/
void updata_alm_time(RTC_TIME *curr_time,RTC_TIME *curr_alm)
{
    curr_alm->dYear = curr_time->dYear;
    curr_alm->bMonth = curr_time->bMonth;
    curr_alm->bDay = curr_time->bDay;

    curr_alm->bSec = 0;                 //������Ĭ��Ϊ0

    write_alm_time(curr_alm);
}
/*----------------------------------------------------------------------------*/
/**@brief 	��λRTCʱ��
   @param 	void
   @return  void
   @note  	void reset_irtc(void)�����ݵ�ǰʱ����Чֵ�������Ƿ�λʱ��
*/
/*----------------------------------------------------------------------------*/
void reset_irtc(RTC_TIME *curr_time,RTC_TIME *curr_alm)
{
    u8 reg;

    read_rtc_time(curr_time);
    read_alm_time(curr_alm);

    reg = read_RTC_reg(RTC_CON_RD);
    if (((curr_time->dYear > 2100)
            || (curr_time->dYear < 2000))
            || (curr_time->bMonth >= 12)
            || (curr_time->bHour >= 24)
            || (curr_time->bMin >= 60)
            || (curr_time->bSec >= 60)
            ||(reg & BIT(7))//PD_FLAG�����¿���
          )
    {
        puts("\n--------RTC RESET--------\n");
        curr_time->dYear = 2015;
        curr_time->bMonth = 1;
        curr_time->bDay = 1;
        curr_time->bHour = 0;
        curr_time->bMin = 0;
        curr_time->bSec = 0;

        puts("\n--------ALM RESET--------\n");
        curr_alm->bHour = 0;
        curr_alm->bMin = 0;

        write_rtc_time(curr_time);
    }

    rtc_set.alarm_set.alarm_sw = (reg&BIT(5));//

    write_RTC_reg(RTC_CON_WR,reg&(~(BIT(4)|BIT(7))));

//    write_RTC_reg(RTC_OSC_WR,0x0A);///PORTR3 ���������������CAPSEL:BIT(2~3)��iSEL:BIT(0~1)

    updata_alm_time(curr_time, curr_alm);

//    rtc_printf("current_time = %d",curr_time->bHour);
//    rtc_printf(":%d",curr_time->bMin);
//    rtc_printf(":%d\n",curr_time->bSec);
//
//    rtc_printf("current_alm = %d",curr_alm->bHour);
//    rtc_printf(":%d",curr_alm->bMin);
//    rtc_printf(":%d\n",curr_alm->bSec);
}

/*----------------------------------------------------------------------------*/
/**@brief 	RTC�ж�ע��
   @param 	void
   @return  void
   @note  	void irtc_hw_init(void)
*/
/*----------------------------------------------------------------------------*/
void irtc_hw_init(void)
{
    u8 reg;

    reg = read_RTC_reg(RTC_CON_RD);
    if(reg & BIT(6))
    {
        rtc_set.alarm_set.alarm_flag = 1;
    }
    else
    {
        rtc_set.alarm_set.alarm_flag = 0;
    }

    printf("\n\n-----------flag %x--------\n\n\n",rtc_set.alarm_set.alarm_flag);

    IRTC_WKCLRPND;
    IRTC_X512CLRPND;
    IRTC_X2CLRPND;

    write_RTC_reg(RTC_WK_EDG_EN_WR,0x00);//��ֹ����
    write_RTC_reg(RTC_WK_PND_WR, 0xf0);//clr_pnd

    IRTC_CON |= BIT(15);    //clr irtc wkup pnd
    IRTC_CON |= BIT(6);     //irtc wkup ie
    INTALL_HWI(RTC_INIT,rtc_isr,1) ;

    reset_irtc(&current_time,&current_alarm);
}

/*----------------------------------------------------------------------------*/
/**@brief 	��ʼ��IRTC
   @param 	void
   @return  void
   @note  	void rtc_init(void)
*/
/*----------------------------------------------------------------------------*/
void irtc_init(void)
{
#if RTC_ALM_EN
    IRTC_WKIE(1);                           //WKUPIE �����ж�
#else
    IRTC_WKIE(0);                           //WKUPIE �����ж�
#endif
}

#endif
