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

#define FM_Hz		96000000L	//<-固定频率
#define RFI_Hz		80000000L	//<-固定频率
#define APC_Hz		96000000L	//<-根据运算能力可调整
#define LSB_Hz      80000000L

#define BT_RCCL_SYS_Hz 24000000L


#define UART_CLK        clock_get_lsb_freq()
#define SYS_CLK         clock_get_sys_freq()

#define SYS_CLOCK_IN    SYS_CLOCK_INPUT_PLL_BT_OSC

/*----------------------------------------------------------------------------*/
/**@brief  时钟初始化，振荡器打开，PLL 使能，切换到主时钟
   @param  sys_in：时钟输入，支持以下参数，对应不同时钟入口
                        SYS_CLOCK_INPUT_OSC = 0,
                        SYS_CLOCK_INPUT_EX_OSC,
                        SYS_CLOCK_INPUT_RTC_OSC,
                        SYS_CLOCK_INPUT_RC,

                        SYS_CLOCK_INPUT_PLL_OSC,
                        SYS_CLOCK_INPUT_PLL_EX_OSC,
                        SYS_CLOCK_INPUT_PLL_BT_OSC,
                        SYS_CLOCK_INPUT_PLL_RESERVED,
   @param  input_freq：输入时钟频率（单位Hz）
   @param  out_freq：输出系统频率（单位z）
   @return void
   @note   支持随时切换，不同入口切换，不同频率切换
*/
/*----------------------------------------------------------------------------*/
void clock_init(SYS_CLOCK_INPUT sys_in, u32 input_freq, u32 out_freq);

/*----------------------------------------------------------------------------*/
/**@brief  时钟频率切换函数
   @param  out_freq：输出系统频率（单位z）
   @return void
   @note   支持随时切换，内部关中断保护
*/
/*----------------------------------------------------------------------------*/
void set_sys_freq(u32 out_freq);


#endif
