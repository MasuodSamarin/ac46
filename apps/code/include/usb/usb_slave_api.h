#ifndef	_USB_SLAVE_API_H_
#define _USB_SLAVE_API_H_

#include "typedef.h"
#include "mango_dev_usb_slave.h"


/*****************************
    API Function Declare
*****************************/
/*----------------------------------------------------------------------------*/
/**@brief   USB Slave API�������뺯��
   @param   *var_p��usbģ�����й�����ʹ�õı���
   @param   *parm�����޲���
   @return  var_pָ��
   @note	s32 usb_slave_var_api(void *var_p, void *parm)
*/
/*----------------------------------------------------------------------------*/
s32 usb_slave_var_api(void *var_p, void *parm);


/*----------------------------------------------------------------------------*/
/**@brief   USB Slave ģ�������ȡ�����ú���(eg.DEV_GET_STATUS/USB_SLAVE_MASS/USB_SLAVE_HID)
   @param	*pram:����
   @param	cmd:��������
   @return	��ȡ��������
   @note	s32 usb_slave_ioctl_api(void *parm , u32 cmd)
*/
/*----------------------------------------------------------------------------*/
s32 usb_slave_ioctl_api(void *parm , u32 cmd);


/*----------------------------------------------------------------------------*/
/**@brief   USB Slave ���߼�⺯��
   @param   ��
   @return  3��״̬��DEV_HOLD/DEV_ONLINE/DEV_OFFLINE
   @note	s32 usb_slave_detect_api(void)
*/
/*----------------------------------------------------------------------------*/
s32 usb_slave_detect_api(void);


/*----------------------------------------------------------------------------*/
/**@brief   USB Slave ����(����ʵ�����жϱ���)
   @param   *pram:��ʱ��������
   @return  0�����سɹ���etc������ʧ��,��ϸ�ɼ������б�
   @note	s32 usb_slave_mount_api(void *pram)
*/
/*----------------------------------------------------------------------------*/
s32 usb_slave_mount_api(void *pram);


/*----------------------------------------------------------------------------*/
/**@brief   USB �ӻ�ж��
   @param   void
   @return  0�����سɹ���etc������ʧ��,��ϸ�ɼ������б�
   @note	s32 usb_slave_unmount_api(void)
*/
/*----------------------------------------------------------------------------*/
s32 usb_slave_unmount_api(void);



/*****************************
ioctl_api Function Declare
*****************************/
/*----------------------------------------------------------------------------*/
/**@brief   USB hid���Ƽ�ֵ����
   @param   key��hid��ֵ������ο�hid audio�����б�
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
