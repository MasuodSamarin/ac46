/*******************************************************************************************
File Name: 	SD_Host_API.h

Version: 	1.00

Discription SD Host 接口函数

Author: 	Caibingquan

Email:  	change.tsai@gmail.com

Date:		2013.01.02

Copyright (c) 2010 - 2012 JieLi. All Rights Reserved.
*******************************************************************************************/
#ifndef _SD0_Host_API_H_
#define _SD0_Host_API_H_

#include "typedef.h"

/*****************************
        Function Declare
*****************************/
/*----------------------------------------------------------------------------*/
/**@brief   SD/MMC 模块参数读取与设置函数(eg.DEV_GET_BLOCK_NUM/DEV_GET_STATUS/DEV_GET_BLOCK_SIZE)
   @param	*pram:参数设置(只定义了SD传输波特率设置)
   @param	cmd:参数设置(只定义了SD传输波特率设置)
   @return	读取参数返回
   @note	s32 sd0_mount_api(void *pram)
*/
/*----------------------------------------------------------------------------*/
s32 sd0_ioctl_api(void *parm , u32 cmd);
s32 sd1_ioctl_api(void *parm , u32 cmd);


/*----------------------------------------------------------------------------*/
/**@brief   SD/MMC power设置函数
   @param	mode：DEV_POWER_STANDBY有效
   @return	0：读成功；etc：读失败，详细见错误列表
   @note	s32 sd0_power_api(u32 mode)
*/
/*----------------------------------------------------------------------------*/
s32 sd0_power_api(u32 mode);
s32 sd1_power_api(u32 mode);


/*----------------------------------------------------------------------------*/
/**@brief   SD/MMC 模块初始化函数,包括IO,寄存器初始化,鉴定卡流程
   @param	*pram:单/四线模式设置
   @return	成功返回0,etc：设置失败，详细见错误列表
   @note	s32 sd0_mount_api(void *pram)
*/
/*----------------------------------------------------------------------------*/
s32 sd0_mount_api(void *pram);
s32 sd1_mount_api(void *pram);


/*----------------------------------------------------------------------------*/
/**@brief    SD Host 卸载，关闭控制器，I/O恢复为普通I/O
   @param    void
   @return   0：读成功；etc：读失败，详细见错误列表
   @note	 s32 sd0_unmount_api(void)
*/
/*----------------------------------------------------------------------------*/
s32 sd0_unmount_api(void);
s32 sd1_unmount_api(void);


/*---------------------------------------------------------------------------*/
/**@brief	SD 读接口，等待读操作完成
   @param	buf：读数据缓冲区；
   @param	lba：物理地址
   @param	len：多少个扇区(sector)
   @return  0：读成功；etc：读失败，详细见错误列表
   @note    s32 sd0_read_api(u8 *buf, u32 lba, u32 len);
*/
/*---------------------------------------------------------------------------*/
s32 sd0_read_api(u8 *buf, u32 lba, u32 len);
s32 sd1_read_api(u8 *buf, u32 lba, u32 len);


/*----------------------------------------------------------------------------*/
/**@brief	SD 写接口，等待写操作完成
   @param	buf：读数据缓冲区；
   @param	lba：物理地址
   @param	len：多少个扇区(sector)
   @return  0：写成功；etc：写失败，详细见错误列表
   @note	s32 sd0_write_api(u8 *buf, u32 lba, u32 len)
*/
/*-----------------------------------------------------------------------------*/
s32 sd0_write_api(u8 *buf, u32 lba, u32 len);
s32 sd1_write_api(u8 *buf, u32 lba, u32 len);


/*----------------------------------------------------------------------------*/
/**@brief   SD Host 在线检测函数
   @param   无
   @return  3种状态：DEV_HOLD /DEV_ONLINE/DEV_OFFLINE
   @note	s32 sd0_det_api(void)
*/
/*----------------------------------------------------------------------------*/
s32 sd0_det_api(void);
s32 sd1_det_api(void);


/*----------------------------------------------------------------------------*/
/**@brief   SD Host API变量传入函数
   @param   *var_p：sd模块运行过程中使用的变量
   @param   *parm：对应controller_io/online_check_way/max_data_baud数据
   @return  var_p指针
   @note	s32 sd0_var_api(void *var_p, void *parm)
*/
/*----------------------------------------------------------------------------*/
s32 sd0_var_api(void *var_p, void *parm);
s32 sd1_var_api(void *var_p, void *parm);


/*usb读卡器接口*/
u8 sd0_mount_only(void); //不进行中断初始化
u8 sd1_mount_only(void);
s32 sd0_read_go(u8 *buf, u32 lba); //不等待read完成
s32 sd1_read_go(u8 *buf, u32 lba);
s32 sd0_write_go(u8 *buf, u32 lba); //不等待write完成
s32 sd1_write_go(u8 *buf, u32 lba);
u8 sd0_rw_wait_idle(u8 rw_ctl, u8 retry); //读卡器wait idle
u8 sd1_rw_wait_idle(u8 rw_ctl, u8 retry);

/*sd控制器接口*/
u32  get_sd0_dev_busy_status_api(void);
void close_sd0_controller(void);
void release_sd0_controller(void);
u32  get_sd1_dev_busy_status_api(void);
void close_sd1_controller(void);
void release_sd1_controller(void);

#endif/*_SD0_Host_API_H_*/
