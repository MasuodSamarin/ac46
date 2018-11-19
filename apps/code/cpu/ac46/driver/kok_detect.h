#ifndef __DEV_KOK_H__
#define __DEV_KOK_H__
#include "config.h"

#if EXTERN_KOK_DETECT_USE_IO_EN
#include "typedef.h"


typedef enum __KOK_STATUS
{
    KOK_OFF = 0,
    KOK_ON,
    NULL_KOK,
}KOK_STATUS;

typedef struct __KOK_VAR
{
    u16 pre_status;
    u8  status_cnt;
    u8  bDevOnline;
    u32 last_sta;
    #ifdef KOK_DETECT_USE_KEY
    bool bKokKeyOpenFlag;
    #endif
}KOK_VAR;

extern KOK_VAR g_kok_var; ///<line in¼ì²â±äÁ¿

void kok_init_api(void);
void kok_check_api(u32 info);
//void kok_check_api(void);
u32 kok_is_online(void);

#endif
#endif/*__DEV_KOK_H__*/

