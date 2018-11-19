#ifndef _PLL_MOUDLE_H_
#define _PLL_MOUDLE_H_

#include "config.h"
#include "clock_moudle.h"

//#define PLL_DEBUG

#ifdef PLL_DEBUG

//#define deg			        my_printf
#define pll_puts                puts
#define pll_put_u8              put_u8hex0
#define pll_put_u16             put_u16hex
#define pll_put_u32             put_u32hex
#else

#define deg(...)
#define pll_puts(...)
#define pll_put_u8(...)
#define pll_put_u16(...)
#define pll_put_u32(...)

#endif          /*	NDEBUG	*/


typedef enum
{
    PLL_INPUT_OSC = 0,
	PLL_INPUT_EX_OSC,
	PLL_INPUT_BT_OSC,
	PLL_INPUT_RESERVED,
}PLL_INPUT;

typedef struct _PLL_INTERFACE
{
	void (*io_enable)(bool enable, u32 in_freq);
	void (*input)(void);
	void (*run)(u32 in_freq);

	void (*set_sys_freq)(u32 out_freq);
	void (*set_fm_freq)(u32 out_freq);
	void (*set_rfi_freq)(u32 out_freq);
	void (*set_apc_freq)(u32 out_freq);
}PLL_INTERFACE;


bool pll_interface_set(PLL_INTERFACE *pll_int);

bool pll_io_enable(bool enable, u32 in_freq);

bool pll_input(void);

bool pll_run(u32 in_freq);

bool pll_set_sys_freq(u32 out_freq);

bool pll_set_fm_freq(u32 out_freq);

bool pll_set_rfi_freq(u32 out_freq);

bool pll_set_apc_freq(u32 out_freq);


PLL_INTERFACE *pll_source_regisit(PLL_INPUT pll_in, u32 input_freq);

void pll_moudle_init(PLL_INPUT pll_in, u32 input_freq, u32 out_freq);

extern const u32 pll_clk480_tab[];

extern const u32 pll_clk192_tab[];


#endif
