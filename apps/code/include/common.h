/*--------------------------------------------------------------------------*/
/**@file     common.h
   @brief
   @details
   @author
   @date    2011-3-7
   @note    CD003
*/
/*----------------------------------------------------------------------------*/
#ifndef _COMMON_
#define _COMMON_

#include "typedef.h"

extern volatile u16 delay_cnt;

struct mem_stats
{
    const char *name;
    unsigned int avail;
    unsigned int used;
    unsigned int max;
    unsigned long err;
    unsigned long illegal;
};

extern struct mem_stats sys_mem_sta;

#define GET_SYS_MEM_STAT() get_malloc_stats(&sys_mem_sta);\
    printf("get_malloc_stats\nMEM_HEAP %s\n\t", sys_mem_sta.name);\
    printf("avail: %u\n\t", (u32)sys_mem_sta.avail);\
    printf("used: %u\n\t", (u32)sys_mem_sta.used);\
    printf("max: %u\n\t", (u32)sys_mem_sta.max);\
    printf("err: %u\n", (u32)sys_mem_sta.err)

void delay(u32  t);
void delay_2ms(u32 t);
void delay_count();

//void my_memcpy(void * dst, const void * src, unsigned int len);
//void my_memset(void * dst, unsigned char dat, unsigned int len);
void my_memzero(u32 * dst, tu16 len);


void store_dword(void *buf, u32 index, u32 word);
void store_word(void *buf, u32 index, u32 word);

#endif
