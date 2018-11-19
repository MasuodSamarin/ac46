#ifndef __DEV_PC_H__
#define __DEV_PC_H__

#include "includes.h"
#include "mango_dev_usb_slave.h"

void usb_slave_hid(u32 key);
u32 usb_slave_online_status(void);
void pc_check_api(u32 info);
u8 pc_set_speaker_vol(sUSB_SLAVE_EP0 *ep0_var, u32 pc_mute_status);
void pc_dac_mute(bool mute_status, u8 fade_en);
USB_SLAVE_VAR *usb_slave_init(void);
u32 usb_slave_online_status(void);
void usb_slave_masstorage(sUSB_SLAVE_MASS *var);
void usb_slave_hold(void);
void pc_dac_off(void);

#endif/*__DEV_PC_H__*/
