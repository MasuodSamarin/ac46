#ifndef SPI_0_H
#define SPI_0_H

#include "typedef.h"

#define SPI1_OUT    0


extern void SPI1_init(tbool is3Wrie, tu8 speed);
extern void SPI1_cs(u32 cs);
extern void SPI1_SetSpeed(tu8 speed);
extern void SPI1_WriteByte(tu8 dat);
extern tu8 SPI1_ReadByte(void);
extern void SPI1_DmaWrite(void *buf, tu16 len);
extern void SPI1_DmaRead(void *buf, tu16 len);
extern u32 spi1_flash_read_id();

#endif
