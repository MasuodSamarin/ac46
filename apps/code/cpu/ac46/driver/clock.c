#include "includes.h"

#include "key.h"

#include "key_drv_ir.h"
#include "timer.h"
OS_EVENT  sys_clk_chg_sem;

extern void bt_close_eninv();
extern void bt_open_eninv();

AT(.flushinv_icache)
void set_spi_speed(u8 sp)
{
    while(!(DSPCON & BIT(5)));
    SPI2_BAUD = sp;
}
void set_sys_freq(u32 out_freq)
{
    if(out_freq == SYS_CLK)
        return;

    os_mutex_pend(&sys_clk_chg_sem,0);


    bt_close_eninv();

    clock_set_freq_fast(out_freq);//该函数里面会先跑rc，这时会导致蓝牙有问题

    bt_open_eninv();

    os_mutex_post(&sys_clk_chg_sem);

    set_tick_timer(OS_TICKS_PER_SEC);

    uart1_init();
    //puts("clock \n");
    timer0_init();

#if KEY_AD_EN
    set_adc_clk();
#endif

#if KEY_IR_EN
    set_ir_clk();
#endif
}
