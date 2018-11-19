/*******************************************************************************************
 File Name: spiflash.h

 Version: 1.00

 Discription:

 Author:yulin deng

 Email :flowingfeeze@163.com

 Date:ÐÇÆÚ¶þ, 10\23\2012   05:39:25ÏÂÎç

 Copyright:(c)JIELI  2011  @ , All Rights Reserved.
*******************************************************************************************/
#ifndef spiflash_h
#define spiflash_h

#include "typedef.h"
#include "spi.h"


/*************************************************/
/*
		COMMAND LIST - WinBond FLASH WX25X10
*/
/*************************************************/
#define WINBOND_WRITE_ENABLE		0x06
#define WINBOND_WRITE_DISABLE	    0x04
#define WINBOND_READ_SR			    0x05
#define WINBOND_WRITE_SR			0x01
#define WINBOND_READ_DATA		    0x03
#define WINBOND_FAST_READ			0x0B
#define WINBOND_FAST_READ_DUAL	    0x3B
#define WINBOND_PAGE_PROGRAM	    0x02
#define WINBOND_SECTOR_ERASE		0x20
#define WINBOND_BLOCK_ERASE		    0xD8
#define WINBOND_CHIP_ERASE		    0xC7
#define WINBOND_POWER_DOWN		    0xB9
#define WINBOND_RELEASE			    0xAB
#define WINBOND_MANUFACTURE		    0x90
#define WINBOND_JEDEC_ID			0x9F



////**********写保护参数**********////
#define PROTECT_NONE		0x0000
///////////////512K Flash///////////////
//////////TOP/////////
#define PROTECT_512K_0		0x0024
#define PROTECT_512K_0_TO_1	0x0028
#define PROTECT_512K_0_TO_3	0x002C
#define PROTECT_512K_0_TO_7	0x0030
/////////Bottom///////
#define PROTECT_512K_7		0x0004
#define PROTECT_512K_6_TO_7	0x0008
#define PROTECT_512K_4_TO_7	0x000C
///////////////////////////////////////

///////////////1M Flash///////////////
//////////TOP/////////
#define PROTECT_1M_0		0x0024
#define PROTECT_1M_0_TO_1	0x0028
#define PROTECT_1M_0_TO_3	0x002C
#define PROTECT_1M_0_TO_7	0x0030
#define PROTECT_1M_0_TO_15	0x0034
/////////Bottom///////
#define PROTECT_1M_15		0x0004
#define PROTECT_1M_14_TO_15	0x0008
#define PROTECT_1M_12_TO_15	0x000C
#define PROTECT_1M_8_TO_15	0x0010
///////////////////////////////////////

///////////////2M Flash///////////////
//////////TOP/////////
#define PROTECT_2M_0		0x0024
#define PROTECT_2M_0_TO_1	0x0028
#define PROTECT_2M_0_TO_3	0x002C
#define PROTECT_2M_0_TO_7	0x0030
#define PROTECT_2M_0_TO_15	0x0034
#define PROTECT_2M_0_TO_31	0x0038
/////////Bottom///////
#define PROTECT_2M_31		0x0004
#define PROTECT_2M_30_TO_31	0x0008
#define PROTECT_2M_28_TO_31	0x000C
#define PROTECT_2M_24_TO_31	0x0010
#define PROTECT_2M_16_TO_31	0x0014
///////////////////////////////////////

///////////////4M Flash///////////////
//////////TOP/////////
#define PROTECT_4M_0		0x0024
#define PROTECT_4M_0_TO_1	0x0028
#define PROTECT_4M_0_TO_3	0x002C
#define PROTECT_4M_0_TO_7	0x0030
#define PROTECT_4M_0_TO_15	0x0034
#define PROTECT_4M_0_TO_31	0x0038
#define PROTECT_4M_0_TO_63	0x003C
/////////Bottom///////
#define PROTECT_4M_63		0x0004
#define PROTECT_4M_62_TO_63	0x0008
#define PROTECT_4M_60_TO_63	0x000C
#define PROTECT_4M_56_TO_63	0x0010
#define PROTECT_4M_48_TO_63	0x0014
#define PROTECT_4M_32_TO_63	0x0018
///////////////////////////////////////

typedef enum _FLASH_ERASER
{
	CHIP_ERASER=0,
	BLOCK_ERASER,
	SECTOR_ERASER,
}FLASH_ERASER;



typedef struct _SPI_FLASH_CMD
{
    u8	eraser[3];			//0(chip)   : 1(block) :  2(sector)
    u8	read;				//¶ÁÃüÁî
    u8	write;   				//Ð´ÃüÁî
    u8	read_sr;				//¶Ásr ¼Ä´æÆ÷ÃüÁî
	u8	write_en;			//Ð´Ê¹ÄÜÃüÁî
	u8	write_sr;			//Ð´½ûÖ¹ÃüÁî
}SPI_FLASH_CMD;

typedef struct _RM_SPI
{
    u8 readCmd;
    u8 readType;
    u8 is3Wrie;
    u8 isDec;
}RM_SPI;

tbool   spi_flash_init(tbool is3Wrie, tu8 speed);

u32		spi_flash_read_id() ;

void	spi_flash_send_cmd(tu8 cmd);

void	spi_flash_send_addr(u32 addr) ;

void	spi_flash_read(void  *buf, u32 addr ,tu16 len);

void	spi_flash_write(void  *buf, u32 addr ,tu16 len);

void	spi_flash_erase(FLASH_ERASER eraser, u32 address) ;

tbool   mask_spi_flash_read(void *param, void  *buf, u32 addr ,tu16 len);

void flash_hook_init(void (*enter)(), void (*leave)());
#endif



