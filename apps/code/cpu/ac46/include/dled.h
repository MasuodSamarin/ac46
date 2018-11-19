#ifndef _DLED_H_
#define _DLED_H_

#include "typedef.h"





enum
{
    POWER_ONING=1,           //开机，绿灯平均快闪，5下
    DISCONNECT_OK,           //开机自动连接不成功，绿灯快闪2s一下
    POWER_ON_OK,            //长按超过5s正常开机后，绿灯和红灯交替闪
    CONNECT_OK,             //连接成功，绿灯慢闪8s一下
    POWER_OFFING,           //关机，红灯长亮闪3s
};


void dled_init(void);
void set_dled_mode(u8 mode);
void dled_control(void);


#endif

