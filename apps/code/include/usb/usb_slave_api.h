#ifndef	_USB_SLAVE_API_H_
#define _USB_SLAVE_API_H_

#include "typedef.h"
#include "mango_dev_usb_slave.h"


/*****************************
    API Function Declare
*****************************/
/*----------------------------------------------------------------------------*/
/**@brief   USB Slave API变量传入函数
   @param   *var_p：usb模块运行过程中使用的变量
   @param   *parm：暂无参数
   @return  var_p指针
   @note	s32 usb_slave_var_api(void *var_p, void *parm)
*/
/*----------------------------------------------------------------------------*/
s32 usb_slave_var_api(void *var_p, void *parm);


/*----------------------------------------------------------------------------*/
/**@brief   USB Slave 模块参数读取与设置函数(eg.DEV_GET_STATUS/USB_SLAVE_MASS/USB_SLAVE_HID)
   @param	*pram:暂无
   @param	cmd:参数设置
   @return	读取参数返回
   @note	s32 usb_slave_ioctl_api(void *parm , u32 cmd)
*/
/*----------------------------------------------------------------------------*/
s32 usb_slave_ioctl_api(void *parm , u32 cmd);


/*----------------------------------------------------------------------------*/
/**@brief   USB Slave 在线检测函数
   @param   无
   @return  3种状态：DEV_HOLD/DEV_ONLINE/DEV_OFFLINE
   @note	s32 usb_slave_detect_api(void)
*/
/*----------------------------------------------------------------------------*/
s32 usb_slave_detect_api(void);


/*----------------------------------------------------------------------------*/
/**@brief   USB Slave 挂载(函数实现有判断保护)
   @param   *pram:暂时不用设置
   @return  0：挂载成功；etc：挂载失败,详细可见错误列表
   @note	s32 usb_slave_mount_api(void *pram)
*/
/*----------------------------------------------------------------------------*/
s32 usb_slave_mount_api(void *pram);


/*----------------------------------------------------------------------------*/
/**@brief   USB 从机卸载
   @param   void
   @return  0：挂载成功；etc：挂载失败,详细可见错误列表
   @note	s32 usb_slave_unmount_api(void)
*/
/*----------------------------------------------------------------------------*/
s32 usb_slave_unmount_api(void);



/*****************************
ioctl_api Function Declare
*****************************/
/*----------------------------------------------------------------------------*/
/**@brief   USB hid控制键值设置
   @param   key：hid键值，具体参考hid audio控制列表
   @return  void
   @note    void usb_hid_control(u32 key)
*/
/*----------------------------------------------------------------------------*/
void usb_hid_control(u32 key);


void susb_msg_set_hook(void *func);
void usb_slave_hold(void);
u32 usb_slave_online_status(void);
u8 usb_sd0_init(void);
u32 usb_read_sd0(void *buf, u32 lba);
u32 usb_write_sd0(void *buf, u32 lba);
u32 usb_get_sd0_capacity(void);
u8 usb_sd1_init(void);
u32 usb_read_sd1(void *buf, u32 lba);
u32 usb_write_sd1(void *buf, u32 lba);
u32 usb_get_sd1_capacity(void);
void usb_slave_masstorage(sUSB_SLAVE_MASS *var);
void usb_slave_hid(u32 key);

#endif	/*	_USB_SLAVE_API_H_	*/
