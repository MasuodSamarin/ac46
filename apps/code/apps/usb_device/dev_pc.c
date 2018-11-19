#include "usb_device.h"
#include "mango_dev_sd.h"
#include "sd_host_api.h"
#include "mango_dev_usb_slave.h"
#include "dev_pc.h"
#include "msg.h"
#include "device_driver.h"
#include "dac.h"
#include "dac_api.h"
#include "vm_api.h"
#include "usb_slave_api.h"
#include "ladc.h"

#if USB_PC_EN

/*----------------------------------------------------------------------------*/
/**@brief  sd控制器接口初始化
   @param  无
   @return 无
   @note   void usb_slave_SD_MASS(void)
*/
/*----------------------------------------------------------------------------*/
void usb_slave_SD_MASS(void)
{
    /*1、USB 模式设置，参数均为默认设置*/
    usb_class_setting(CLASS_CONFIG); //选择MASS STORAGE、AUDIO和HID功能

    /*2、注册读卡器的SD控制器接口*/
#if SDMMC0_EN
    pc_puts("DEV_SDCRAD_0\n");
    sUSB_DEV_IO sdmmc0_dev;
    my_memset((u8 *)&sdmmc0_dev, 0x0, sizeof(sUSB_DEV_IO));

    sdmmc0_dev.usb_get_dev_capacity = usb_get_sd0_capacity;
    sdmmc0_dev.usb_write_dev = usb_write_sd0;
    sdmmc0_dev.usb_read_dev = usb_read_sd0;
    sdmmc0_dev.usb_dev_init = usb_sd0_init;
    sdmmc0_dev.usb_wiat_sd_end = sd0_rw_wait_idle;
    sdmmc0_dev.bAttr = DEV_SDCRAD_0;

    susb_sd_register(DEV_SDCRAD_0, &sdmmc0_dev); //注册SD0
#endif

#if SDMMC1_EN
    pc_puts("DEV_SDCRAD_1\n");
    sUSB_DEV_IO sdmmc1_dev;
    my_memset((u8 *)&sdmmc1_dev, 0x0, sizeof(sUSB_DEV_IO));

    sdmmc1_dev.usb_get_dev_capacity = usb_get_sd1_capacity;
    sdmmc1_dev.usb_write_dev = usb_write_sd1;
    sdmmc1_dev.usb_read_dev = usb_read_sd1;
    sdmmc1_dev.usb_dev_init = usb_sd1_init;
    sdmmc1_dev.usb_wiat_sd_end = sd1_rw_wait_idle;
    sdmmc1_dev.bAttr = DEV_SDCRAD_1;

    susb_sd_register(DEV_SDCRAD_1, &sdmmc1_dev); //注册SD1
#endif

    /*3、挂载USB SLAVE设备*/
    usb_device_mount();
}


/*----------------------------------------------------------------------------*/
/**@brief  PC 模式AUDIO音量设置消息钩子函数
   @param  msg：需要投递的消息
   @return 无
   @note   void hook_susb_msg(u32 msg)
*/
/*----------------------------------------------------------------------------*/
void hook_susb_msg(u32 msg)
{
    //pc_puts("PC_VOL_POST_MSG\n");
    os_taskq_post_msg(PC_TASK_NAME, 1, msg);
}


/*----------------------------------------------------------------------------*/
/**@brief  PC 模式AUDIO音量初值设置
   @param  chl：左声道；chr：右声道；ep0_var：端点变量指针；
   @return 无
   @note   void set_speaker_volume(u8 chl, u8 chr, sUSB_SLAVE_EP0 *ep0_var)
*/
/*----------------------------------------------------------------------------*/
void set_speaker_volume(u8 chl, u8 chr, sUSB_SLAVE_EP0 *ep0_var)
{
    u16 spk_vol;

    spk_vol = (chl >= MAX_SYS_VOL_L) ? 0xff : chl<<3;
    /*Channel L*/
    ep0_var->usb_class_info.bAudioCurL[0] = spk_vol;
    ep0_var->usb_class_info.bAudioCurL[1] = 0x80;

    spk_vol = (chr >= MAX_SYS_VOL_R) ? 0xff : chr<<3;
    /*Channel R*/
    ep0_var->usb_class_info.bAudioCurR[0] = spk_vol;
    ep0_var->usb_class_info.bAudioCurR[1] = 0x80;
}


/*----------------------------------------------------------------------------*/
/**@brief  PC 模式AUDIO初始化设置
   @param  ep0_var：端点变量指针
   @return 无
   @note   void usb_slave_audio_init(sUSB_SLAVE_EP0 *ep0_var)
*/
/*----------------------------------------------------------------------------*/
void usb_slave_audio_init(sUSB_SLAVE_EP0 *ep0_var)
{
    u8 pc_vol;

    ///for speaker
    susb_msg_set_hook(hook_susb_msg); //传入MSG投递函数
    dac_set_samplerate(48000,0); //DAC采样率设置为48K

    vm_read_api(VM_PC_VOL, &pc_vol); //取出VM保存的上次PC音量值
    pc_printf("vm_pc_vol=%d\n", pc_vol);
    set_speaker_volume(pc_vol, pc_vol, ep0_var); //设置当前PC音量值

    ///for mic
    ladc_reg_init(ENC_MIC_CHANNEL, LADC_SR48000);
}


/*----------------------------------------------------------------------------*/
/**@brief  PC 模式AUDIO音量设置
   @param  ep0_var：端点变量指针；pc_mute_status：mute状态
   @return AUDIO音量
   @note   u8 pc_set_speaker_vol(sUSB_SLAVE_EP0 *ep0_var, u32 pc_mute_status)
*/
/*----------------------------------------------------------------------------*/
u8 pc_set_speaker_vol(sUSB_SLAVE_EP0 *ep0_var, u32 pc_mute_status)
{
    u8 spk_vol_l, spk_vol_r;

    spk_vol_l = ep0_var->usb_class_info.bAudioCurL[0];
    //pc_printf("api_vol=%x, %x\n", ep0_var->usb_class_info.bAudioCurL[0], ep0_var->usb_class_info.bAudioCurR[0]);
    if(spk_vol_l)
    {
        spk_vol_l >>= 3;
        spk_vol_l = (spk_vol_l == 0) ? 1 : spk_vol_l;
        spk_vol_l = (spk_vol_l >= MAX_SYS_VOL_L) ? 30 : spk_vol_l;
    }

    spk_vol_r = ep0_var->usb_class_info.bAudioCurR[0];
    if(spk_vol_r)
    {
        spk_vol_r >>= 3;
        spk_vol_r = (spk_vol_r == 0) ? 1 : spk_vol_r;
        spk_vol_r = (spk_vol_r >= MAX_SYS_VOL_L) ? 30 : spk_vol_r;
    }

    if(pc_mute_status)
    {
        //pc_puts("pc_start_mute\n");
        dac_fade_out(FADE_ON);
        dac_var.bMute = 1;
    }
    else
    {
        dac_var.bMute = 0;
    }
    //pc_printf("pc_vol=%d\n", spk_vol_l);
    set_sys_vol(spk_vol_l, spk_vol_r, FADE_OFF);
    //vm_write_api(VM_PC_VOL, &spk_vol_l);
    vm_cache_write(VM_PC_VOL, &spk_vol_l, 2);

    return spk_vol_l;
}


/*----------------------------------------------------------------------------*/
/**@brief  PC 模式静音状态设置
   @param  mute_status：mute状态控制；fade_en：淡入淡出设置
   @return 无
   @note   void pc_dac_mute(bool mute_status, u8 fade_en)
*/
/*----------------------------------------------------------------------------*/
void pc_dac_mute(bool mute_status, u8 fade_en)
{
    if(mute_status)
    {
        dac_var.bMute = 1;
        dac_fade_out(fade_en);
    }
    else
    {
        dac_var.bMute = 0;
        dac_fade_in(fade_en);
    }
}


/*----------------------------------------------------------------------------*/
/**@brief  PC 模式DAC通道开启和音量设置
   @param  无
   @return 无
   @note   void pc_dac_on(void)
*/
/*----------------------------------------------------------------------------*/
void pc_dac_on(void)
{
    dac_channel_on(UDISK_CHANNEL,FADE_OFF);
    set_sys_vol(dac_var.cur_sys_vol_l, dac_var.cur_sys_vol_r, FADE_OFF);

#ifdef KOK_DETECT_AUTO_VOL_SET		
	 store_vol= dac_var.cur_sys_vol_l;
#endif
	
}


/*----------------------------------------------------------------------------*/
/**@brief  PC 模式DAC通道关闭
   @param  无
   @return 无
   @note   void pc_dac_off(void)
*/
/*----------------------------------------------------------------------------*/
void pc_dac_off(void)
{
    dac_channel_off(UDISK_CHANNEL, FADE_OFF);
    dac_var.bMute = 0;
}


/*----------------------------------------------------------------------------*/
/**@brief  PC 模式初始化函数(包括变量申请，音频系统初始化和读卡器设备注册)
   @param  无
   @return PC申请到的变量指针
   @note   USB_SLAVE_VAR *usb_slave_init(void)
*/
/*----------------------------------------------------------------------------*/
USB_SLAVE_VAR *usb_slave_init(void)
{
    USB_SLAVE_VAR *susb_var;

    susb_var = (USB_SLAVE_VAR *)malloc(sizeof(USB_SLAVE_VAR));
    if (susb_var == 0)
    {
        pc_puts("susb_var 申请失败！");
    }
    memset((u8 *)susb_var, 0x0, sizeof(USB_SLAVE_VAR));

    usb_slave_ioctl_api(&susb_var->ep0_var, USB_SLAVE_EP0_VAR_INIT); //传入端点0需要的内存
    usb_slave_audio_init(&susb_var->ep0_var); //初始化音频输出系统
    pc_dac_on(); //开PC DAC模拟通道
    usb_slave_SD_MASS(); //注册SD设备

    return susb_var;
}


/*----------------------------------------------------------------------------*/
/**@brief  PC 在线列表
   @note   const u8 pc_event_tab[]
*/
/*----------------------------------------------------------------------------*/
const u8 pc_event_tab[] =
{
    SYS_EVENT_PC_OUT, //PC拔出
    SYS_EVENT_PC_IN,  //PC插入
};


/*----------------------------------------------------------------------------*/
/**@brief  PC 在线检测API函数
   @param  无
   @return 无
   @note   void pc_check_api(void)
*/
/*----------------------------------------------------------------------------*/
void pc_check_api(u32 info)
{
    s32 dev_status;

    dev_status = usb_slave_detect_api();
    if(dev_status != DEV_HOLD)
    {
        os_taskq_post_event("MainTask", 2, pc_event_tab[dev_status],info);
    }
}

#endif
