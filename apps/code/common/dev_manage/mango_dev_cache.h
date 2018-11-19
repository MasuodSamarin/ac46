#ifndef _MANGO_DEV_CACHE_H_
#define _MANGO_DEV_CACHE_H_

#include "includes.h"

enum
{
    CACHE_SUCC = 0x0,
    CACHE_OFFLINE,
};

void set_cache_base(u32 base);
extern const struct DEV_IO * dev_reg_cache(void *parm);

#endif
