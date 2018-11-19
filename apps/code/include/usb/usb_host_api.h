/*******************************************************************************************
File Name: USB_Host_API.h

Version: 1.00

Discription

Author: Caibingquan

Email:  change.tsai@gmail.com

Date:2012.02.06

Copyright:(c) 2012 , All Rights Reserved.
*******************************************************************************************/
#ifndef _USB_Host_API_H_
#define _USB_Host_API_H_

#include "typedef.h"

/*****************************
        Function Declare
*****************************/
/*----------------------------------------------------------------------------*/
/**@brief   USB HOST 模块参数读取与设置函数(eg.DEV_GET_BLOCK_NUM/DEV_GET_STATUS/DEV_GET_BLOCK_SIZE)
   @param	*pram:暂无
   @param	cmd:参数设置
   @return	读取参数返回
   @note	s32 usb_ioctl_api(void *parm , u32 cmd)
*/
/*----------------------------------------------------------------------------*/
s32 usb_ioctl_api(void *parm , u32 cmd);


/*----------------------------------------------------------------------------*/
/**@brief   USB HOST power设置函数
   @param	mode：DEV_POWER_STANDBY有效
   @return	0：读成功；etc：读失败，详细见错误列表
   @note	s32 usb_power_api(u32 mode)
*/
/*----------------------------------------------------------------------------*/
s32 usb_power_api(u32 mode);


/*----------------------------------------------------------------------------*/
/**@brief   USB Host 挂载(函数实现有判断保护)
   @param   *pram:暂时不用设置
   @return  0：挂载成功；etc：挂载失败,详细可见错误列表
   @note	s32 usb_host_mount_api(void *pram)
*/
/*----------------------------------------------------------------------------*/
s32 usb_host_mount_api(void *pram);


/*----------------------------------------------------------------------------*/
/**@brief   USB 主机卸载，不能执行读写操作，I/O恢复为普通I/O模式
   @param   void
   @return  0：挂载成功；etc：挂载失败,详细可见错误列表
   @note	s32 usb_host_unmount_api(void)
*/
/*----------------------------------------------------------------------------*/
s32 usb_host_unmount_api(void);


/*----------------------------------------------------------------------------*/
/**@brief   USB Host 读接口，支持多LBA Sector容量大于512B设备的读操作(函数实现有判断保护)
   @param   buf：数据缓冲区；
   @param   lba：物理地址
   @param	len：多少个扇区(sector)
   @return  0：读成功；etc：读失败，详细见错误列表
   @note	s32 usb_host_read_api(u8 *buf, u32 lba, u32 len)
*/
/*----------------------------------------------------------------------------*/
s32 usb_host_read_api(u8 *buf, u32 lba, u32 len);


/*----------------------------------------------------------------------------*/
/**@brief   USB Host 写接口，仅支持多LBA Sector容量为512B设备的写操作(函数实现有判断保护)
   @param   buf：数据缓冲区；
   @param   lba：物理地址
   @param	len：多少个扇区(sector)
   @return  0：读成功；etc：读失败，详细见错误列表
   @note	s32 usb_host_write_api(u8 *buf, u32 lba, u32 len)
*/
/*----------------------------------------------------------------------------*/
s32 usb_host_write_api(u8 *buf, u32 lba, u32 len);


/*----------------------------------------------------------------------------*/
/**@brief   USB Host 在线检测函数
   @param   无
   @return  3种状态：DEV_HOLD/DEV_ONLINE/DEV_OFFLINE
   @note	s32 usb_host_detect_api(void)
*/
/*----------------------------------------------------------------------------*/
s32 usb_host_detect_api(void);


/*----------------------------------------------------------------------------*/
/**@brief   USB Host API变量传入函数
   @param   *var_p：usb模块运行过程中使用的变量
   @param   *parm：暂无参数
   @return  var_p指针
   @note	s32 usb_var_api(void *var_p, void *parm)
*/
/*----------------------------------------------------------------------------*/
s32 usb_var_api(void *var_p, void *parm);


#endif /*_USB_HOST_API_H_*/
