#ifndef SYS_IDLE_H
#define SYS_IDLE_H

#include "typedef.h"



extern u8 sys_idle_cnt;
extern u8 sys_idle_num;



#define SYS_EXIT_IDLE()     sys_idle_cnt=0

#define  sys_idle_check_enable() sys_idle_num = 20




void sys_idle_check();

void sys_idle_now();



#endif
