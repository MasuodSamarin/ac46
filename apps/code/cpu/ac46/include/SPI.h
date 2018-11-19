/*******************************************************************************************
 File Name: SPI.h

 Version: 1.00

 Discription:

 Author:yulin deng

 Email :flowingfeeze@163.com

 Date:ÐÇÆÚÒ», 10\22\2012   08:41:17ÏÂÎç

 Copyright:(c)JIELI  2011  @ , All Rights Reserved.
*******************************************************************************************/
#ifndef SPI_h
#define SPI_h

#include"typedef.h"

void    spi_cs(u32 cs);

void    SPI1_init(tbool is3Wrie, tu8 speed);

void	SPI1_SetSpeed(tu8 speed);

tu8     SPI1_ReadByte(void) ;

void	SPI1_WriteByte(tu8 dat);

void	SPI1_DmaWrite(void *buf, tu16 len);

void	SPI1_DmaRead(void *buf, tu16 len, tu8 is2bit);


#endif


