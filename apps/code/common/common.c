/*--------------------------------------------------------------------------*/
/**@file     common.c
   @brief    常用公共函数
   @details
   @author
   @date    2011-3-7
   @note    CD003
*/
/*----------------------------------------------------------------------------*/
#include "typedef.h"
#include "common.h"

volatile u16 delay_cnt;

struct mem_stats sys_mem_sta;

//void delay_count() sec(.comm);
void delay_count()
{
    if(delay_cnt){
        delay_cnt--;
    }
}

void delay_2ms(u32 cnt)
{
    delay_cnt = cnt;
    while(delay_cnt);
}

inline void delay(u32 d)
{
	__delay(d);
}

#if 0
/*----------------------------------------------------------------------------*/
/**@brief   内存拷贝
   @param   void
   @return  void
   @author  Change.tsai
   @note    void my_memcpy(void * dst, void * src, tu16 len)
*/
/*----------------------------------------------------------------------------*/
void my_memcpy(void * dst, const void * src, tu16 len)
{
    //tu16 ilen;

    if ((src == dst) || (len == 0))
        return;
    else if ((src > dst) || (src + len) < dst)
    {
        while (len)
        {
            *(u8*)dst++ = *(u8*)src++;
            --len;
        }
    }
    else
    {
        while (len)
        {
            --len;
            *(u8*)(dst+len) = *(u8*)(src+len);
        }
    }
}
/*----------------------------------------------------------------------------*/
/**@brief   内存设置
   @param   void
   @return  void
   @author  Change.tsai
   @note    void my_memset(void * dst, u8 dat, tu16 len)
*/
/*----------------------------------------------------------------------------*/
void my_memset(void * dst, u8 dat, tu16 len)
{
    while (len)
    {
        *(u8*)dst++ = dat;
        --len;
    }
}
#endif

void my_memzero(u32 * dst, tu16 len)
{
    while (len)
    {
        *(u32*)dst++ = 0;
        len -= 4;
    }
}



void store_word(void *buf, u32 index, u32 word)
{
    u8 *p = ((u8 *)buf) + index;
    p[0] = (u8)word;
    p[1] = (u8)(word>>8);
}

void store_dword(void *buf, u32 index, u32 word)
{
    u8 *p = ((u8 *)buf) + index;
    p[0] = (u8)word;
    p[1] = (u8)(word>>8);
    p[2] = (u8)(word>>16);
    p[3] = (u8)(word>>24);
}


