#ifndef __BT_KEY_DEAL_H__
#define __BT_KEY_DEAL_H__

#include "config.h"

extern void create_bt_msg_task(char *task_name);
extern void TaskBtMsgStack(void *p_arg);
extern void user_ctrl_prompt_tone_play(u8 status,void *ptr);
extern void updata_connection_channels_for_tester(int state, int channel);

#endif
