/***********************************Jieli tech************************************************
  File : cpu.h
  By   : Juntham
  date : 2014-10-30 16:05
********************************************************************************************/
#ifndef _CPU_H_
#define _CPU_H_
#include "ac46.h"

#ifndef __ASSEMBLY__
#include "asm_type.h"
#endif

#define LITTLE_ENDIAN
#define  OS_STK_GROWTH        1                             /* Stack grows from HIGH to LOW memory on 80x86  */

#define OS_CPU_CORE               1
#define OS_CPU_MMU                1
#define SDRAM                     0
#define MEM_MALLOC                1

#if SDRAM > 0
#define PAGE_SHIFT 14
#define SDRAM_BEGIN_ADDR        (0x800000)
#define MAX_SDRAM_SIZE          (4*1024*1024)
#define MMU_MAX_SIZE            (4*1024*1024)  // mmu 管理的最大地址空间
#define MMU_ADDR_BEGIN          (0x400000)
#define MMU_ADDR_END            (0x800000)
#define STACK_TASK_SIZE         (1024*64)
#define STACK_START             MMU_ADDR_BEGIN
#define STACK_END               (MMU_ADDR_BEGIN+STACK_TASK_SIZE)
#else
#define PAGE_SHIFT 9
//#define SDRAM_BEGIN_ADDR        (0x0)
#define MAX_SDRAM_SIZE          (128*1024-PAGE_SIZE)
#define MMU_MAX_SIZE            (128*1024-PAGE_SIZE)  // mmu 管理的最大地址空间
#define MMU_ADDR_BEGIN          (0x80000)
#define MMU_ADDR_END            (MMU_ADDR_BEGIN+MMU_MAX_SIZE)
#define STACK_TASK_SIZE         (1024*4)
#define STACK_START             MMU_ADDR_BEGIN
#define STACK_END               (MMU_ADDR_BEGIN+STACK_TASK_SIZE)
#endif
#define PAGE_SIZE   (1UL << PAGE_SHIFT)
#define PAGE_MASK   (~(PAGE_SIZE-1))
#define PAGE_ALIGN(addr)    (((addr)+PAGE_SIZE-1)&PAGE_MASK)

#define MMU_TAG_ADDR0   0x49800
#define APP_BEGIN_ADDR  MMU_ADDR_BEGIN

#if OS_CPU_CORE > 1
#define MMU_TAG_ADDR1   0x6a000
#endif

#if (MAX_SDRAM_SIZE/PAGE_SIZE  > 256 )
#define ufat_t u16
#else
#define ufat_t u8
#endif

#ifndef __ASSEMBLY__

extern int processor_id();


#if OS_CPU_CORE > 1
#define OS_CPU_ID                 processor_id()
#else
#define OS_CPU_ID                 0
#endif

#endif
/*
*********************************************************************************************************
*                                              Defines
*********************************************************************************************************
*/


#endif
