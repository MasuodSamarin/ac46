#include "dev_ctl.h"
#include "drv_manage.h"
#include "mango_dev_sd.h"
#include "mango_dev_usb.h"
#include "mango_dev_cache.h"
#include "app_cfg.h"
#include "logic_dev_list.h"
#include "linein.h"
#include "dev_pc.h"


DEV_HANDLE volatile sd0;        ///>设备句柄
DEV_HANDLE volatile sd1;        ///>设备句柄
DEV_HANDLE volatile usb;        ///>设备句柄
DEV_HANDLE volatile cache;        ///>设备句柄
extern tbool syd_test(void *p_hdev);
extern OS_EVENT  sys_clk_chg_sem;

#if SDMMC0_EN
///sd0 io检测函数
u8 sd0_io_check(void)
{
    return TRUE;  //检测到
    return FALSE; //没检测到
}
#endif


#if SDMMC1_EN
///sd1 io检测函数
u8 sd1_io_check(void)
{
    return TRUE;  //检测到
    return FALSE; //没检测到
}
#endif


static void dev_reg_ctrl(void)
{

#if SDMMC0_EN
    sSD_API_SET sd0_api_set;
    memset(&sd0_api_set, 0x0, sizeof(sSD_API_SET));
    sd0_api_set.controller_io = SD0_IO_B;        //SD0_IO_A：SD0控制器B出口，SD0_IO_B：SD0控制器B出口
    sd0_api_set.online_check_way = SD_CLK_CHECK;//SD_CMD_CHECK; //CMD检测方式：SD_CMD_CHECK，CLK检测方式：SD_CLK_CHECK，IO检测方式：SD_IO_CHECK

#ifdef	PROMOTE_SD_PROCESS_SPEED
    sd0_api_set.max_data_baud = 3;               //数据传输波特率(0为最快速度)
    sd0_api_set.hc_mode = SD_1WIRE_MODE|SD_HI_SPEED;//SD_4WIRE_MODE;         //1线模式：SD_1WIRE_MODE，4线模式：SD_4WIRE_MODE，高速模式：SD_HI_SPEED
#else
    sd0_api_set.max_data_baud = 5;               //数据传输波特率(0为最快速度)
    sd0_api_set.hc_mode = SD_1WIRE_MODE;//SD_4WIRE_MODE;         //1线模式：SD_1WIRE_MODE，4线模式：SD_4WIRE_MODE，高速模式：SD_HI_SPEED
#endif											  //--(SD_1WIRE_MODE|SD_HI_SPEED 表示1线高速模式)                                                    //--(SD_1WIRE_MODE|SD_HI_SPEED 表示1线高速模式)
    if(SD_IO_CHECK == sd0_api_set.online_check_way)
    {
        sd0_api_set.io_det_func = sd0_io_check;  //传入io检测函数
    }
	DEVICE_REG(sd0,&sd0_api_set);                ///<注册sd0到系统

    sd0 = dev_open("sd0", 0);
#endif

#if SDMMC1_EN

    sSD_API_SET sd1_api_set;
    memset(&sd1_api_set, 0x0, sizeof(sSD_API_SET));
    sd1_api_set.controller_io = SD1_IO_B;        //SD1_IO_A：SD1控制器B出口，SD1_IO_B：SD1控制器B出口
    sd1_api_set.online_check_way = SD_CLK_CHECK; //CMD检测方式：SD_CMD_CHECK，CLK检测方式：SD_CLK_CHECK，IO检测方式：SD_IO_CHECK
    sd1_api_set.max_data_baud = 5;               //数据传输波特率(0为最快速度)
    sd1_api_set.hc_mode = SD_1WIRE_MODE;         //1线模式：SD_1WIRE_MODE，4线模式：SD_4WIRE_MODE，高速模式：SD_HI_SPEED
                                                    //--(SD_1WIRE_MODE|SD_HI_SPEED 表示1线高速模式)
    if(SD_IO_CHECK == sd1_api_set.online_check_way)
    {
        sd1_api_set.io_det_func = sd1_io_check;  //传入io检测函数
    }
	DEVICE_REG(sd1,&sd1_api_set);                ///<注册sd1到系统

    sd1 = dev_open("sd1", 0);
#endif

#if USB_DISK_EN
    DEVICE_REG(usb, NULL); ///<注册usb到系统
    usb = dev_open("usb", 0);
#endif

    DEVICE_REG(cache, NULL);
    cache= dev_open("cache", 0);

}

u32 dev_detect_fun(u32 info)
{
#if AUX_DETECT_EN
    aux_check_api(info); //linein检测
#endif
#if USB_PC_EN
    pc_check_api(info);  //PC检测
#endif
#if EXTERN_KOK_DETECT_USE_IO_EN
	kok_check_api(info);
#endif

    return 0;
}

void dev_ctrl_sys_init(void *parm)
{
    ///逻辑设备链表初始化
    lg_dev_list_init();

    ///物理设备链表初始化
    phy_dev_list_init();

    ///注册设备(所有设备先在此处注册)
	dev_reg_ctrl();

    ///启动设备管理器线程
    dev_init(TaskDevCheckPrio,TaskDevMountPrio,(void*)dev_detect_fun);

    os_mutex_create(&sys_clk_chg_sem);

}


