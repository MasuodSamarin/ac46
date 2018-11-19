/***********************************Jieli tech************************************************
  File : mmu.h
  By   : Juntham
  date : 2014-08-05 16:38
********************************************************************************************/
#ifndef __MMU__
#define __MMU__

#include "includes.h"

#define MMU_TAG_ADDR    (0x17800)
#define MMU_PAGE_SIZE   256
#define MMU_PAGE_TOTAL  127
#define MMU_LOGIC_ADDR  0x20000
#define MMU_PHY_ADDR    0x8000

#define MMU_STACK_SIZE  0x1000
#define MMU_STACK  (0x20000+MMU_STACK_SIZE)
#define MMU_STACK_PAGE  (MMU_STACK_SIZE/MMU_PAGE_SIZE)
#if 0
void mmu_init(void);
void mmu_apply(unsigned char * table, unsigned int pages);
void mmu_release(unsigned char *table, unsigned int size);
void mmu_stack_init(unsigned char *table, unsigned int pages);
#endif



#endif
