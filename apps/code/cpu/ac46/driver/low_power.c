#include "config.h"
#include "low_power.h"
#include "clock_app.h"
#include "clock_api.h"
#include "hwi.h"
/*----------------------------------------------------------------------------*/
/**@brief   低功耗函数
   @param   wakeup_cfg:唤醒的IO配置
   @param   wakeup_edge:唤醒边沿
            WAKEUP_UP_EDGE上升沿唤醒  WAKEUP_DOWN_EDGE：下降沿唤醒
   @return  void
   @author
   @note    void low_power_mode(u16 wakeup_cfg,u8 wakeup_edge)
*/
/*----------------------------------------------------------------------------*/
void low_power_mode(u16 wakeup_cfg, u8 wakeup_edge)
{
    puts("\n\n*****************Enter Low Power Mode****************\n");

    /**************关中断切时钟****************/
    DISABLE_INT();
    clock_init(SYS_CLOCK_INPUT_RC, OSC_Hz, SYS_Hz);
    delay(200);

    /**************关闭耗电模块***************/
    LDO_CON &= ~(BIT(0)|BIT(1));//VBGB_EN BTLDO_EN

    TMR0_CON = 0;
    TMR1_CON = 0;
    TMR2_CON = 0;
    TMR3_CON = 0;

    //IRFLT_CON = 0;
    //ALNK_CON0 = 0;
    ADC_CON &= ~BIT(3);
    LADC_CON1 &= ~BIT(12);       //关闭LADC模拟模块
    DAC_CON = 0;

    //UART
    UT0_CON &= ~BIT(0);
    UT1_CON &= ~BIT(0);
    UT2_CON &= ~BIT(0);

    //PLL
    PLL_CON = 0;

    //LVD
    LVD_CON = 0;

    //VCM
    DAA_CON0 = 0;
    DAA_CON1 = 0;
    DAA_CON2 = 0;
    DAA_CON3 = 0;

    //USB
    USB_CON0 = 0;
    USB_IO_CON |= BIT(4);  //USB DP PULL DOWN

    //SD
    SD0_CON1  = 0;
    SD1_CON1  = 0;

    /************IO设置****************/
    PORTA_DIR |= 0xFFFF;
	PORTA_PU &= ~0xFFFF;
	PORTA_PD |= 0xFFFF;
	PORTA_DIE &= ~0xFFFF;

	PORTB_DIR |= 0xFFF;
	PORTB_PU &= ~0xFFF;
	PORTB_PD |= 0xFFF;
	PORTB_DIE &= ~0xFFF;

	PORTC_DIR |= 0xFFFF;
	PORTC_PU &= ~0xFFFF;
	PORTC_PD |= 0xFFFF;
	PORTC_DIE &= ~0xFFFF;

	PORTD_DIR |= 0xFF;
    PORTD_PU &= ~0xFF;
    PORTD_DIE &= ~0xFF;

    /*********** 唤醒设置 ************/
	WKUP_CON0 = 0;      //wakeup enbale
	WKUP_CON1 = 0;      //wakeup edge
	WKUP_CON2 = 0xffff; //wakeup pending(clear)

    switch(wakeup_cfg)
    {
        case WAKEUP_0:
            break;

        case WAKEUP_1:
            break;

        case WAKEUP_2:
            PORTA_DIR |= BIT(0);
            PORTA_DIE |= BIT(0);
            if(wakeup_edge == WAKEUP_DOWN_EDGE)
            {
                PORTA_PU |= BIT(0);     //开内部上拉
                PORTA_PD &= ~BIT(0);    //关内部下拉
                WKUP_CON1 |= BIT(2);    //下降沿wakeup
            }
            else
            {
                PORTA_PU &= ~BIT(0);    //关内部上拉
                PORTA_PD |= BIT(0);     //开内部下拉
                WKUP_CON1 &= ~BIT(2);   //上升沿wakeup
            }
            WKUP_CON0 |= BIT(2);        //wakeup enable
            break;

        case WAKEUP_3:
            PORTA_DIR |= BIT(8);
            PORTA_DIE |= BIT(8);
            if(wakeup_edge == WAKEUP_DOWN_EDGE)
            {
                PORTA_PU |= BIT(8);     //开内部上拉
                PORTA_PD &= ~BIT(8);    //关内部下拉
                WKUP_CON1 |= BIT(3);    //下降沿wakeup
            }
            else
            {
                PORTA_PU &= ~BIT(8);    //关内部上拉
                PORTA_PD |= BIT(8);     //开内部下拉
                WKUP_CON1 &= ~BIT(3);   //上升沿wakeup
            }
            WKUP_CON0 |= BIT(3);        //wakeup enable
            break;

        case WAKEUP_4:
            PORTB_DIR |= BIT(5);
            PORTB_DIE |= BIT(5);
            if(wakeup_edge == WAKEUP_DOWN_EDGE)
            {
                PORTB_PU |= BIT(5);     //开内部上拉
                PORTB_PD &= ~BIT(5);    //关内部下拉
                WKUP_CON1 |= BIT(4);    //下降沿wakeup
            }
            else
            {
                PORTB_PU &= ~BIT(5);    //关内部上拉
                PORTB_PD |= BIT(5);     //开内部下拉
                WKUP_CON1 &= ~BIT(4);   //上升沿wakeup
            }
            WKUP_CON0 |= BIT(4);        //wakeup enable
            break;

        case WAKEUP_5:
            break;

        case WAKEUP_6:
            break;

        case WAKEUP_7:
            break;

        case WAKEUP_8:
            PORTA_DIR |= BIT(4);
            PORTA_DIE |= BIT(4);
            if(wakeup_edge == WAKEUP_DOWN_EDGE)
            {
                PORTA_PU |= BIT(4);     //开内部上拉
                PORTA_PD &= ~BIT(4);    //关内部下拉
                WKUP_CON1 |= BIT(8);    //下降沿wakeup
            }
            else
            {
                PORTA_PU &= ~BIT(4);    //关内部上拉
                PORTA_PD |= BIT(4);     //开内部下拉
                WKUP_CON1 &= ~BIT(8);   //上升沿wakeup
            }
            WKUP_CON0 |= BIT(8);        //wakeup enable
            break;

        case WAKEUP_9:
            PORTA_DIR |= BIT(6);
            PORTA_DIE |= BIT(6);
            if(wakeup_edge == WAKEUP_DOWN_EDGE)
            {
                PORTA_PU |= BIT(6);     //开内部上拉
                PORTA_PD &= ~BIT(6);    //关内部下拉
                WKUP_CON1 |= BIT(9);    //下降沿wakeup
            }
            else
            {
                PORTA_PU &= ~BIT(6);    //关内部上拉
                PORTA_PD |= BIT(6);     //开内部下拉
                WKUP_CON1 &= ~BIT(9);   //上升沿wakeup
            }
            WKUP_CON0 |= BIT(9);        //wakeup enable
            break;

        case WAKEUP_10:
            PORTA_DIR |= BIT(10);
            PORTA_DIE |= BIT(10);
            if(wakeup_edge == WAKEUP_DOWN_EDGE)
            {
                PORTA_PU |= BIT(10);     //开内部上拉
                PORTA_PD &= ~BIT(10);    //关内部下拉
                WKUP_CON1 |= BIT(10);    //下降沿wakeup
            }
            else
            {
                PORTA_PU &= ~BIT(10);    //关内部上拉
                PORTA_PD |= BIT(10);     //开内部下拉
                WKUP_CON1 &= ~BIT(10);   //上升沿wakeup
            }
            WKUP_CON0 |= BIT(10);        //wakeup enable
            break;

        case WAKEUP_11:
            PORTB_DIR |= BIT(0);
            PORTB_DIE |= BIT(0);
            if(wakeup_edge == WAKEUP_DOWN_EDGE)
            {
                PORTB_PU |= BIT(0);     //开内部上拉
                PORTB_PD &= ~BIT(0);    //关内部下拉
                WKUP_CON1 |= BIT(11);    //下降沿wakeup
            }
            else
            {
                PORTB_PU &= ~BIT(0);    //关内部上拉
                PORTB_PD |= BIT(0);     //开内部下拉
                WKUP_CON1 &= ~BIT(11);   //上升沿wakeup
            }
            WKUP_CON0 |= BIT(11);        //wakeup enable
            break;

        case WAKEUP_12:
            PORTA_DIR |= BIT(10);
            PORTA_DIE |= BIT(10);
            if(wakeup_edge == WAKEUP_DOWN_EDGE)
            {
                PORTA_PU |= BIT(10);     //开内部上拉
                PORTA_PD &= ~BIT(10);    //关内部下拉
                WKUP_CON1 |= BIT(12);    //下降沿wakeup
            }
            else
            {
                PORTA_PU &= ~BIT(10);    //关内部上拉
                PORTA_PD |= BIT(10);     //开内部下拉
                WKUP_CON1 &= ~BIT(12);   //上升沿wakeup
            }
            WKUP_CON0 |= BIT(12);        //wakeup enable
            break;

        case WAKEUP_13:
            PORTA_DIR |= BIT(14);
            PORTA_DIE |= BIT(14);
            if(wakeup_edge == WAKEUP_DOWN_EDGE)
            {
                PORTA_PU |= BIT(14);     //开内部上拉
                PORTA_PD &= ~BIT(14);    //关内部下拉
                WKUP_CON1 |= BIT(13);    //下降沿wakeup
            }
            else
            {
                PORTA_PU &= ~BIT(14);    //关内部上拉
                PORTA_PD |= BIT(14);     //开内部下拉
                WKUP_CON1 &= ~BIT(13);   //上升沿wakeup
            }
            WKUP_CON0 |= BIT(13);        //wakeup enable
            break;

        case WAKEUP_14:
            break;

        case WAKEUP_15:
            break;

        default:
            return;
    }

	PWR_CON &= ~BIT(3);      //wake up wait 8ms
	PWR_CON |= BIT(2);       //Enter Sleep Mode

//    LDO_CON |= (BIT(0)|BIT(1));
//    delay(100);
//    clock_init(SYS_CLOCK_IN, OSC_Hz, SYS_Hz);
//    delay(500);
//    uart1_init();
//    puts("\n\n********************Wakeup********************\n\n");

    ///*******唤醒后处理*********/
    PWR_CON |= BIT(4); //reset
}


