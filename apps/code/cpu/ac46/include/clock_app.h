#ifndef _CLOCK_APP_H_
#define _CLOCK_APP_H_

#include "config.h"

//#define SYS_DEBUG

#ifdef SYS_DEBUG

//#define deg			        my_printf
#define sys_puts                puts
#define sys_put_u8              put_u8hex0
#define sys_put_u16             put_u16hex
#define sys_put_u32             put_u32hex
#else

#define deg(...)
#define sys_puts(...)
#define sys_put_u8(...)
#define sys_put_u16(...)
#define sys_put_u32(...)

#endif          /*	NDEBUG	*/


typedef enum
{
    SYS_CLOCK_INPUT_OSC = 0,
	SYS_CLOCK_INPUT_EX_OSC,
	SYS_CLOCK_INPUT_RTC_OSC,
	SYS_CLOCK_INPUT_RC,

    SYS_CLOCK_INPUT_PLL_OSC,
    SYS_CLOCK_INPUT_PLL_EX_OSC,
    SYS_CLOCK_INPUT_PLL_BT_OSC,
    SYS_CLOCK_INPUT_PLL_RESERVED,
}SYS_CLOCK_INPUT;



typedef struct _CLOCK_INTERFACE
{
	void (*run)(SYS_CLOCK_INPUT sys_in, u32 input_freq, u32 out_freq);

	//<-run �ӿڵ��ú����ʹ�����·�Ƶ�ӿ�
	void (*set_sys_freq)(u32 out_freq);
    u32 (*get_sys_freq);

    //addition
	void (*set_fm_freq)(u32 out_freq);		//<-Ƶ�ʲ��ɱ䣬�̶�96MHz
    u32 (*get_fm_freq);

	void (*set_rfi_freq)(u32 out_freq);		//<-Ƶ�ʲ��ɱ䣬�̶�80MHz
    u32 (*get_rfi_freq);

	void (*set_apc_freq)(u32 out_freq);
    u32 (*get_apc_freq);

    void (*set_lsb_freq)(u32 out_freq);		//<- LSB ΪPLL ���Ƶ����PLL �����Ϸ�Ƶ�����ܳ���80MHz
	u32 (*get_lsb_freq);
}CLOCK_INTERFACE;

void clock_regisit(SYS_CLOCK_INPUT sys_in, u32 input_freq, u32 out_freq);

bool clock_set(CLOCK_INTERFACE *clk_int);

bool clock_run(SYS_CLOCK_INPUT sys_in, u32 input_freq, u32 out_freq);


/*
 *  ʹ��ע�⣬��Ҫѡ����ʷ�Ƶ�ȣ������ڲ������жϣ��ѹ��жϣ���ʱ80us��
 */
    void clock_set_freq_fast(u32 out_freq);
/*
 *      Clock �ӿڲ���
 */

bool clock_set_sys_freq(u32 out_freq);

u32 clock_get_sys_freq(void);

bool clock_set_fm_freq(u32 out_freq);

u32 clock_get_fm_freq(void);

bool clock_set_rfi_freq(u32 out_freq);

u32 clock_get_rfi_freq(void);

bool clock_set_apc_freq(u32 out_freq);

u32 clock_get_apc_freq(void);

bool clock_set_lsb_freq(u32 out_freq);

u32 clock_get_lsb_freq(void);



extern tu8 g_clock_moudle_err;

extern tu8 g_clock_lsb_div;

#endif
