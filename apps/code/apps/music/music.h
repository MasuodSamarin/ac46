#ifndef MUSIC_TASK_H
#define MUSIC_TASK_H


#include "typedef.h"

typedef enum{
    SD0_DEVICE,
    SD1_DEVICE,
    USB_DEVICE,
    NO_DEVICE = 0xff,
}UI_DEVICE;

typedef struct _MUSIC_DIS_VAR
{
    UI_DEVICE ui_curr_device;
    u32 ui_curr_file;
    u32 ui_total_file;
    u32 *ui_curr_statu;
}MUSIC_DIS_VAR;

struct music_cfg{
	const char *dev;
};

extern MUSIC_DIS_VAR music_ui;
extern const struct task_info music_task_info;

extern u8 play_mode;
extern u8 eq_mode;

#endif
