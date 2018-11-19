#ifndef __DEV_CTL_H__
#define __DEV_CTL_H__

#include "config.h"
#include "drv_manage.h"
enum
{
    UPDATA_SD0 = 0,
    UPDATA_SD1,
    UPDATA_USB,
    UPDATA_PC,
};

typedef enum
{
    DEV_UPDATA = 1,
    PC_UPDATA,
}UPDATA_WAY;

void  dev_updata_mode(DEV_HANDLE dev_hl, UPDATA_WAY updata_way);

void dev_ctrl_sys_init(void *parm);

#endif
