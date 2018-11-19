#ifndef _CLOCK_MOUDLE_H_
#define _CLOCK_MOUDLE_H_

#include "config.h"
#include "clock_hal.h"


//#define CLOCK_DEBUG

#ifdef CLOCK_DEBUG

//#define deg			        my_printf
#define deg_puts   		 	puts
#define deg_put_u8    	    put_u8hex0
#define deg_put_u16    	    put_u16hex
#define deg_put_u32    	    put_u32hex
#else

#define deg(...)
#define deg_puts(...)
#define deg_put_u8(...)
#define deg_put_u16(...)
#define deg_put_u32(...)

#endif          /*	NDEBUG	*/

void clock_moudle_rc_init(bool enable);

void clock_moudle_osc_init(bool enable, u32 in_freq);

void clock_moudle_exosc_init(bool enable, u32 in_freq);

void clock_moudle_bt_osc_init(bool enable, u32 in_freq);

void clock_moudle_rtc_osc_init(bool enable, u32 in_freq);

void clock_moudle_exio_init(bool enable, u32 in_freq);



void clock_moudle_osc_input_osc(void);

void clock_moudle_osc_input_bt_osc(void);

void clock_moudle_osc_input_rtc_osc(void);

void clock_moudle_osc_input_exio(void);



void clock_moudle_pll_enable(bool enable);

void clock_moudle_pll_input_osc(void);

void clock_moudle_pll_input_bt_osc(void);

void clock_moudle_pll_input_reserved(void);

void clock_moudle_pll_ref_src(tu8 src);

void clock_moudle_pll_ref_clk(tu32 in_freq, tu8 ref_clk);



void clock_moudle_main_clk_input(tu8 input);

void clock_moudle_sys_clk_rc(void);

void clock_moudle_sys_clk_main(void);

void clock_moudle_lsb_clk_div(tu8 div);



void clock_out_PA4(tu8 out);

void clock_out_PA5(tu8 out);



void clock_moudle_pll_sys_clk(tu8 src, tu8 div);

void clock_moudle_pll_fm_clk(tu8 src, tu8 div);

void clock_moudle_pll_rfi_clk(tu8 src, tu8 div);

void clock_moudle_pll_apc_clk(tu8 src, tu8 div);


void peripherals_moudle_usb_clk(tu8 src);

void peripherals_moudle_dac_clk(tu8 src);

void peripherals_moudle_ladc_clk(tu8 src);

void peripherals_moudle_apc_clk(tu8 src);

void peripherals_moudle_lcd_clk(tu8 src);

void peripherals_moudle_uart_clk(tu8 src);

void peripherals_moudle_fm_clk(tu8 src);

void peripherals_moudle_bt_clk(tu8 src);



extern tu8 g_clock_moudle_err;
extern tu8 g_clock_lsb_div;
#endif
