/*******************************************************************************************
File Name: 	SD_Host_API.h

Version: 	1.00

Discription SD Host �ӿں���

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
/**@brief   SD/MMC ģ�������ȡ�����ú���(eg.DEV_GET_BLOCK_NUM/DEV_GET_STATUS/DEV_GET_BLOCK_SIZE)
   @param	*pram:��������(ֻ������SD���䲨��������)
   @param	cmd:��������(ֻ������SD���䲨��������)
   @return	��ȡ��������
   @note	s32 sd0_mount_api(void *pram)
*/
/*----------------------------------------------------------------------------*/
s32 sd0_ioctl_api(void *parm , u32 cmd);
s32 sd1_ioctl_api(void *parm , u32 cmd);


/*----------------------------------------------------------------------------*/
/**@brief   SD/MMC power���ú���
   @param	mode��DEV_POWER_STANDBY��Ч
   @return	0�����ɹ���etc����ʧ�ܣ���ϸ�������б�
   @note	s32 sd0_power_api(u32 mode)
*/
/*----------------------------------------------------------------------------*/
s32 sd0_power_api(u32 mode);
s32 sd1_power_api(u32 mode);


/*----------------------------------------------------------------------------*/
/**@brief   SD/MMC ģ���ʼ������,����IO,�Ĵ�����ʼ��,����������
   @param	*pram:��/����ģʽ����
   @return	�ɹ�����0,etc������ʧ�ܣ���ϸ�������б�
   @note	s32 sd0_mount_api(void *pram)
*/
/*----------------------------------------------------------------------------*/
s32 sd0_mount_api(void *pram);
s32 sd1_mount_api(void *pram);


/*----------------------------------------------------------------------------*/
/**@brief    SD Host ж�أ��رտ�������I/O�ָ�Ϊ��ͨI/O
   @param    void
   @return   0�����ɹ���etc����ʧ�ܣ���ϸ�������б�
   @note	 s32 sd0_unmount_api(void)
*/
/*----------------------------------------------------------------------------*/
s32 sd0_unmount_api(void);
s32 sd1_unmount_api(void);


/*---------------------------------------------------------------------------*/
/**@brief	SD ���ӿڣ��ȴ����������
   @param	buf�������ݻ�������
   @param	lba�������ַ
   @param	len�����ٸ�����(sector)
   @return  0�����ɹ���etc����ʧ�ܣ���ϸ�������б�
   @note    s32 sd0_read_api(u8 *buf, u32 lba, u32 len);
*/
/*---------------------------------------------------------------------------*/
s32 sd0_read_api(u8 *buf, u32 lba, u32 len);
s32 sd1_read_api(u8 *buf, u32 lba, u32 len);


/*----------------------------------------------------------------------------*/
/**@brief	SD д�ӿڣ��ȴ�д�������
   @param	buf�������ݻ�������
   @param	lba�������ַ
   @param	len�����ٸ�����(sector)
   @return  0��д�ɹ���etc��дʧ�ܣ���ϸ�������б�
   @note	s32 sd0_write_api(u8 *buf, u32 lba, u32 len)
*/
/*-----------------------------------------------------------------------------*/
s32 sd0_write_api(u8 *buf, u32 lba, u32 len);
s32 sd1_write_api(u8 *buf, u32 lba, u32 len);


/*----------------------------------------------------------------------------*/
/**@brief   SD Host ���߼�⺯��
   @param   ��
   @return  3��״̬��DEV_HOLD /DEV_ONLINE/DEV_OFFLINE
   @note	s32 sd0_det_api(void)
*/
/*----------------------------------------------------------------------------*/
s32 sd0_det_api(void);
s32 sd1_det_api(void);


/*----------------------------------------------------------------------------*/
/**@brief   SD Host API�������뺯��
   @param   *var_p��sdģ�����й�����ʹ�õı���
   @param   *parm����Ӧcontroller_io/online_check_way/max_data_baud����
   @return  var_pָ��
   @note	s32 sd0_var_api(void *var_p, void *parm)
*/
/*----------------------------------------------------------------------------*/
s32 sd0_var_api(void *var_p, void *parm);
s32 sd1_var_api(void *var_p, void *parm);


/*usb�������ӿ�*/
u8 sd0_mount_only(void); //�������жϳ�ʼ��
u8 sd1_mount_only(void);
s32 sd0_read_go(u8 *buf, u32 lba); //���ȴ�read���
s32 sd1_read_go(u8 *buf, u32 lba);
s32 sd0_write_go(u8 *buf, u32 lba); //���ȴ�write���
s32 sd1_write_go(u8 *buf, u32 lba);
u8 sd0_rw_wait_idle(u8 rw_ctl, u8 retry); //������wait idle
u8 sd1_rw_wait_idle(u8 rw_ctl, u8 retry);

/*sd�������ӿ�*/
u32  get_sd0_dev_busy_status_api(void);
void close_sd0_controller(void);
void release_sd0_controller(void);
u32  get_sd1_dev_busy_status_api(void);
void close_sd1_controller(void);
void release_sd1_controller(void);

#endif/*_SD0_Host_API_H_*/
