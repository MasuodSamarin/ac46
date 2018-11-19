/*************************************************************
File: typedef.h
Author:Juntham
Discriptor:
    数据类型重定义
Version:
Date：
*************************************************************/
#ifndef _typedef_h_
#define _typedef_h_

#ifdef __GNUC__
#define sec(x) __attribute__((section(#x)))
#define AT(x) __attribute__((section(#x)))
#define SET(x) __attribute__((x))
#define _GNU_PACKED_	__attribute__((packed))
#else
#define sec(x)
#define AT(x)
#define SET(x)
#define _GNU_PACKED_
#endif

#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN
#endif

typedef unsigned char	u8;
typedef char			s8;
typedef unsigned short	u16;
typedef signed short	s16;
typedef unsigned int	u32 , bool , tu8, tu16 , tbool , tu32;
typedef signed int		s32;
#define NULL    0


#define	LD_WORD(ptr)		(u16)(*(u16*)(u8*)(ptr))
#define	LD_DWORD(ptr)		(u32)(*(u32*)(u8*)(ptr))
#define	ST_WORD(ptr,val)	*(u16*)(u8*)(ptr)=(u16)(val)
#define	ST_DWORD(ptr,val)	*(u32*)(u8*)(ptr)=(u32)(val)


#define FALSE	0
#define TRUE    1

#define false	0
#define true    1

#define _banked_func
#define _xdata
#define _data
#define _root
#define _no_init
#define my_memset memset
#define my_memcpy memcpy


#define     BIT(n)	            (1 << (n))
#define     BitSET(REG,POS)     (REG |= (1 << POS))
#define     BitCLR(REG,POS)     (REG &= (~(1 << POS)))
#define     BitXOR(REG,POS)     (REG ^= (~(1 << POS)))
#define     BitCHK_1(REG,POS)   ((REG & (1 << POS)) == (1 << POS))
#define     BitCHK_0(REG,POS)   ((REG & (1 << POS)) == 0x00)
#define     testBit(REG,POS)    (REG & (1 << POS))

#define     clrBit(x,y)         x &= ~(1L << y)
#define     setBit(x,y)         x |= (1L << y)

#endif
