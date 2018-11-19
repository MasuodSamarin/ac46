/***********************************Jieli tech************************************************
File : Random.c
By   : Juntham
date : 2014-07-03 14:34
 ********************************************************************************************/

#include "includes.h"
#include "app_cfg.h"
#include "timer.h"
#include "drv_manage.h"
#include "mango_dev_sd.h"
#include "if_decoder_ctrl.h"
#include "dac.h"
#include "vm.h"
#include "error.h"
#include "sys_cfg.h"
#include "key.h"
#include "clock_api.h"
#include "clock_hal.h"
#include "mango_dev_cache.h"
#include "syd_file.h"
/*
 *********************************************************************************************************
 *                                               CONSTANTS
 *********************************************************************************************************
 */


/*
 *********************************************************************************************************
 *                                               VARIABLES
 *********************************************************************************************************
 */
#if OS_CPU_MMU == 0
u32 TaskStartStk[TASK_STK_SIZE];
u32 TaskUIStk[TASK_STK_SIZE];
u32 TaskTestStk[TASK_STK_SIZE];
#endif
void       *TaskStartQ[4], *TaskUIQ[4];
void *TaskBtStackQ[4];
/* OS_TCB     TaskStartTCB;   [> Tasks TCBs                                    <] */
void  TaskStart (void *p_arg);
void TaskUI(void *p_arg);
void TaskTest(void *p_arg);
void TaskBtStack(void *p);
void TaskBtLmp(void *p);


/*$PAGE*/
/*
 *********************************************************************************************************
 *                                                MAIN
 *********************************************************************************************************
 */

void exception_isr(void )
{
    ADC_CON = 0;

#ifdef __DEBUG
    puts_without_lock("\n\n\n\n---------- exception_isr -----------\n\n\n\n");
    put_u32hex(DEBUG_MSG);
    while(1);           //调试时用
#else
    PWR_CON |= BIT(4); //异常后软复位
#endif
}


void CLR_WDT()
{

}


void vm_init_api(struct flash_cfg *cfg)
{
    u32 tmp;
    vm_run_mode vm_mode;

    if(((cfg->spi_run_mode & 3) == 0) || ((cfg->spi_run_mode & 3) == 1)) {
        //spi2_parm = SPI_ODD_MODE;
        vm_mode = WINBOND_READ_DATA_MODE;
    } else if((cfg->spi_run_mode & 3) == 2) {
        //spi2_parm = SPI_DUAL_MODE;
        if(cfg->spi_run_mode & BIT(3)) {
            vm_mode = WINBOND_FAST_READ_DUAL_OUTPUT_MODE;
        } else {
            if(cfg->spi_run_mode & BIT(2)) {
                vm_mode = WINBOND_FAST_READ_DUAL_IO_CONTINUOUS_READ_MODE;
            } else {
                vm_mode = WINBOND_FAST_READ_DUAL_IO_NORMAL_READ_MODE;
            }
        }
    } else {
        if(cfg->spi_run_mode & BIT(3)) {
            vm_mode = WINBOND_FAST_READ_QUAD_OUTPUT_MODE;
        } else {
            if(cfg->spi_run_mode & BIT(2)) {
                vm_mode = WINBOND_FAST_READ_QUAD_IO_CONTINUOUS_READ_MODE;
            } else {
                vm_mode = WINBOND_FAST_READ_QUAD_IO_NORMAL_READ_MODE;
            }
        }
    }

    tmp = cfg->flash_size - cfg->flash_file_size;
    if(tmp < 68L*1024)
    {
        puts("\n\n\n\n----WARN-vm_not_enough_space----\n");
        printf("space : %d byte\n",tmp);
		while(1);
    }

	printf("flash_size=%x, flash_base=%x, vm_mode=%x\n", cfg->flash_size, cfg->flash_base, vm_mode);
    if(vm_init(cfg->flash_size - (68L*1024), cfg->flash_base, vm_mode, 0)!= VM_ERR_NONE)
    {
        puts("\n\n\n\n----WARN-vm_init_err----\n");
		while(1);
    }
}


u16 crc_value;


extern void delay_n2ms(u32 a);

extern void soft_irq_handler();
#define FLASH_BASE_ADDR 0x01000000
__attribute__((noreturn)) void  main(u32 cfg_addr,u32 addr,u32 res)
{
	memcpy(&g_sys_cfg,(void*)(0x01000000+cfg_addr),sizeof(g_sys_cfg));
    crc_value = CRC_REG;
    hwi_init();

    set_spi_speed(0);
    clock_init(SYS_CLOCK_IN, OSC_Hz, SYS_Hz);

    set_bt_pll_para(OSC_Hz);

    uart1_init();
    dac_on_init();
    puts_without_lock("*************************************************************\n");
    puts_without_lock("                                AC46                         \n");
    puts_without_lock("*************************************************************\n");
    //while(1);
#if 0
    puts("clock_get_sys_freq : ");put_u32hex(clock_get_sys_freq());
    puts("\nclock_get_fm_freq : ");put_u32hex(clock_get_fm_freq());
    puts("\nclock_get_rfi_freq : ");put_u32hex(clock_get_rfi_freq());
    puts("\nclock_get_apc_freq : ");put_u32hex(clock_get_apc_freq());
    puts("\nclock_get_lsb_freq : ");put_u32hex(clock_get_lsb_freq());

    puts("\ng_clock_moudle_err : ");put_u8hex(g_clock_moudle_err);

    puts("\nCLK_CON0 : ");put_u32hex0(CLK_CON0);
    puts("\nCLK_CON1 : ");put_u32hex0(CLK_CON1);
    puts("\nCLK_CON2 SYS: ");put_u32hex0(CLK_CON2 & 0x3f);
    puts("\nCLK_CON2 FM: ");put_u32hex0((CLK_CON2 & 0x3f<<6)>>6);
    puts("\nCLK_CON2 RFI: ");put_u32hex0((CLK_CON2 & 0x3f<<12)>>12);
    puts("\nCLK_CON2 APC: ");put_u32hex0((CLK_CON2 & 0x3f<<18>>18));
    puts("\nPLL_CON : ");put_u32hex0(PLL_CON);
    puts("\nSYS_DIV : ");put_u32hex0(SYS_DIV);

    //clock_set_lsb_freq(LSB_Hz);
    puts("\nclock_get_lsb_freq : ");put_u32hex(clock_get_lsb_freq());


    printf("flash_id : %x\n",   g_sys_cfg.flash_cfg.flash_id);
    printf("flash_size : %x\n",   g_sys_cfg.flash_cfg.flash_size);
    printf("flash_file_size : %x\n",   g_sys_cfg.flash_cfg.flash_file_size);
    printf("sdfile_head_addr : %x\n",   g_sys_cfg.flash_cfg.sdfile_head_addr);
    printf("spi_run_mode : %x\n",   g_sys_cfg.flash_cfg.spi_run_mode);//
    printf("spi_div : %x\n",   g_sys_cfg.flash_cfg.spi_div);
    printf("flash_base : %x\n",   g_sys_cfg.flash_cfg.flash_base);
    printf("protected_arg : %x\n",   g_sys_cfg.flash_cfg.protected_arg);
    printf("cfg_zone_addr : %x\n",   g_sys_cfg.flash_cfg.cfg_zone_addr);
    printf("cfg_zone_size : %x\n",   g_sys_cfg.flash_cfg.cfg_zone_size);

    printf("sdram_refresh_cycle : %x\n",   g_sys_cfg.sdr_cfg.sdram_refresh_cycle);
    printf("sdram_refresh_time : %x\n",   g_sys_cfg.sdr_cfg.sdram_refresh_time);
    printf("sdram_cas_latency : %x\n",   g_sys_cfg.sdr_cfg.sdram_cas_latency);
    printf("sdram_trfc : %x\n",   g_sys_cfg.sdr_cfg.sdram_trfc);
    printf("sdram_trp : %x\n",   g_sys_cfg.sdr_cfg.sdram_trp);
    printf("sdram_trcd : %x\n",   g_sys_cfg.sdr_cfg.sdram_trcd);
    printf("sdram_colum : %x\n",   g_sys_cfg.sdr_cfg.sdram_colum);
    printf("sdram_clk_hd_en : %x\n",   g_sys_cfg.sdr_cfg.sdram_clk_hd_en);
    printf("sdram_trrd : %x\n",   g_sys_cfg.sdr_cfg.sdram_trrd);
    printf("sdram_clkoe : %x\n",   g_sys_cfg.sdr_cfg.sdram_clkoe);
    printf("sdram_size : %x\n",   g_sys_cfg.sdr_cfg.sdram_size);
    printf("sdram_fast_clock_rate : %x\n",   g_sys_cfg.sdr_cfg.sdram_fast_clock_rate);

    printf("pll_sel : %x\n",   g_sys_cfg.clk_cfg.pll_sel);
    printf("osc_freq : %x\n",   g_sys_cfg.clk_cfg.osc_freq);
    printf("osc_src :%x\n",   g_sys_cfg.clk_cfg.osc_src);
    printf("osc_hc_en : %x\n",   g_sys_cfg.clk_cfg.osc_hc_en);
    printf("osc_1pin_en : %x\n",   g_sys_cfg.clk_cfg.osc_1pin_en);
    printf("---------------------------------------------\r\n");
#endif
    set_sydf_header_base(g_sys_cfg.flash_cfg.sdfile_head_addr);
    set_cache_base(FLASH_BASE_ADDR);
    HWI_Install(1, exception_isr, 0);
	HWI_Install(31-OS_CPU_ID,OSCtxSw, 0);
	INTALL_HWI(30, soft_irq_handler, 6);

  #ifdef support_low_power_use_extern_io
	low_power_onoff(1);
 #endif


    vm_start();
    vm_init_api(&g_sys_cfg.flash_cfg);

    vm_open_all();

    bt_trim_init();
    bt_trim_rccl();
    os_init();

    init_uart_mutex() ;

    timer0_init();
	init_tick_timer(OS_TICKS_PER_SEC);
	sys_init();

#ifdef BT_TESTER
    test_led_init();
    tester_setting_init();
    cfg_test_box_and_work_mode(get_shoot_mode_able(),BT_MODE);
#else
    cfg_test_box_and_work_mode(NON_TEST,BT_MODE);
#endif

#if(BT_MODE!=NORMAL_MODE)
//    vm_start();
//    bt_trim_init();
    test_analog_var(0x22);
    TaskBtTest();
#endif

	main_task_init();

    os_start();                               /*Start multitasking*/
    puts("os5\n") ;

    ENABLE_INT() ;
    while(1)
    {
  
        asm ("idle");
    }
}


volatile unsigned long jiffies;
