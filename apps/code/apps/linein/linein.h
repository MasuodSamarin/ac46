#ifndef LINEIN_TASK_H
#define LINEIN_TASK_H

#include "includes.h"

//#define AUX_DEBUG
#ifdef AUX_DEBUG
    #define aux_puts     puts
    #define aux_printf   printf
#else
    #define aux_puts(...)
    #define aux_printf(...)
#endif

#if S10_MODE
//    #define AUX_DETECT_EN       0
#else
  //  #define AUX_DETECT_EN       0
#endif
#define LINEIN_TASK_NAME   "LineinTask"

extern const struct task_info linein_task_info;


#endif

