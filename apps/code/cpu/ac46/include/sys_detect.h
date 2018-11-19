#ifndef _SYS_DETECT_H_
#define _SYS_DETECT_H_

//#define SYS_DETECT_DBG
#ifdef SYS_DETECT_DBG
    #define sys_det_puts           puts
    #define sys_det_printf         printf
    #define sys_det_buf            put_buf
#else
    #define sys_det_puts(...)
    #define sys_det_printf(...)
    #define sys_det_buf(...)
#endif/*SYS_DETECT_DBG*/

#define POWERUP_TASK_BT  0x01
#define POWERUP_TASK_MP3 0x02

#define USB_DP_OUT(x)      USB_IO_CON = ((USB_IO_CON & ~BIT(0)) | ((x & 0x1)<<0))
#define USB_DM_OUT(x)      USB_IO_CON = ((USB_IO_CON & ~BIT(1)) | ((x & 0x1)<<1))
#define USB_DP_DIR(x)      USB_IO_CON = ((USB_IO_CON & ~BIT(2)) | ((x & 0x1)<<2))
#define USB_DM_DIR(x)      USB_IO_CON = ((USB_IO_CON & ~BIT(3)) | ((x & 0x1)<<3))
#define USB_DP_PD(x)       USB_IO_CON = ((USB_IO_CON & ~BIT(4)) | ((x & 0x1)<<4))
#define USB_DM_PD(x)       USB_IO_CON = ((USB_IO_CON & ~BIT(5)) | ((x & 0x1)<<5))
#define USB_DP_PU(x)       USB_IO_CON = ((USB_IO_CON & ~BIT(6)) | ((x & 0x1)<<6))
#define USB_DM_PU(x)       USB_IO_CON = ((USB_IO_CON & ~BIT(7)) | ((x & 0x1)<<7))
#define USB_DP_IN()        USB_CON0&BIT(17)
#define USB_DM_IN()        USB_CON0&BIT(16)

#ifdef support_io_det_mute
void  pa_automute(void);
#endif
void pa_mute();
void pa_umute();
void battery_check();
void sys_power_up_check(void);
void sys_init(void);
u16 get_battery_value();
u8 bt_mp3_detect(void);
u32 power_up_task(void);
#ifdef support_send_ir_code
void   IRSendInital(u8  ComData);
void   IRSendLongInital(void);
void   IRSendData(void);
#endif
#ifdef support_battery_mode_check
void  LED_io_display_bat_mode(void);
#endif
#endif/*_SYS_DETECT_H_*/
