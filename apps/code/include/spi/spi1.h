#ifndef _SPI1_H_
#define _SPI1_H_

#include "typedef.h"
//#include "clock.h"
#include "mango_dev_spi.h"


extern s32 spi1_init(spi_mode mode, spi_clk clk);
extern void spi1_cs(u8 cs);
extern void spi1_set_clk(spi_clk clk);
extern void spi1_write_byte(u8 dat);
extern u8 spi1_read_byte(void);
extern s32 spi1_write(u8 *buf, u16 len);
extern s32 spi1_dec_write(u8 *buf, u16 len);
extern s32 spi1_read(u8 *buf, u16 len) ;
extern s32 spi1_dec_read(u8 *buf, u16 len);
extern s32 spi1_write_2bitMode(u8 *buf, u16 len);
void spi1_remap_cs(void (*cs_func)(u8 cs));

#endif  //_SPI1_H_
