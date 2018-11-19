#ifndef __BOOT_H__
#define __BOOT_H__

#include "typedef.h"

typedef struct _SDF_IO
{
    void *param;
    u32 addOffset;
    u32 devOnline;
    tbool(*disk_read)(void *param, void *, u32, u32);
}SDF_IO;


typedef enum
{
    DEV_UPDATA_SUCC = 1,
    DEV_UPDATA_FAIL,
    NO_UPDATA_DEV,
}UPDATA_RESULT;

void sys_init(SDF_IO *pSDF);
u32 flash_data_check(void);
u32 app_run(void);
UPDATA_RESULT updata_mode(SDF_IO *pSDF, u8 updata_type);

#endif/*__BOOT_H__*/
