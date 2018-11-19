#ifndef _CLOCK_API_H_
#define _CLOCK_API_H_

#include "config.h"
#include "clock_app.h"
#include "clock_moudle.h"

#define RTC_OSC_Hz  32768L
#define RC_OSC_Hz   250000L
#ifdef BT_TESTER
#define OSC_Hz      24000000L
#else
#define OSC_Hz      24000000L
#endif

#ifndef ZY_5017_SG_2_AC4601 //def SUPPORT_ZY_4LED_RGB
#define SYS_Hz      120000000L
#else
#define SYS_Hz      96000000L

#endif
#define FM_SYS_Hz   38400000L       //38.4M
#define BT_SYS_Hz  120000000L
#define FLAC_SYS_Hz  120000000L

#define FM_Hz		96000000L	//<-�̶�Ƶ��
#define RFI_Hz		80000000L	//<-�̶�Ƶ��
#define APC_Hz		96000000L	//<-�������������ɵ���
#define LSB_Hz      80000000L

#define BT_RCCL_SYS_Hz 24000000L


#define UART_CLK        clock_get_lsb_freq()
#define SYS_CLK         clock_get_sys_freq()

#define SYS_CLOCK_IN    SYS_CLOCK_INPUT_PLL_BT_OSC

/*----------------------------------------------------------------------------*/
/**@brief  ʱ�ӳ�ʼ���������򿪣�PLL ʹ�ܣ��л�����ʱ��
   @param  sys_in��ʱ�����룬֧�����²�������Ӧ��ͬʱ�����
                        SYS_CLOCK_INPUT_OSC = 0,
                        SYS_CLOCK_INPUT_EX_OSC,
                        SYS_CLOCK_INPUT_RTC_OSC,
                        SYS_CLOCK_INPUT_RC,

                        SYS_CLOCK_INPUT_PLL_OSC,
                        SYS_CLOCK_INPUT_PLL_EX_OSC,
                        SYS_CLOCK_INPUT_PLL_BT_OSC,
                        SYS_CLOCK_INPUT_PLL_RESERVED,
   @param  input_freq������ʱ��Ƶ�ʣ���λHz��
   @param  out_freq�����ϵͳƵ�ʣ���λz��
   @return void
   @note   ֧����ʱ�л�����ͬ����л�����ͬƵ���л�
*/
/*----------------------------------------------------------------------------*/
void clock_init(SYS_CLOCK_INPUT sys_in, u32 input_freq, u32 out_freq);

/*----------------------------------------------------------------------------*/
/**@brief  ʱ��Ƶ���л�����
   @param  out_freq�����ϵͳƵ�ʣ���λz��
   @return void
   @note   ֧����ʱ�л����ڲ����жϱ���
*/
/*----------------------------------------------------------------------------*/
void set_sys_freq(u32 out_freq);


#endif
