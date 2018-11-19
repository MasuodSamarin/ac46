#ifndef _MANGO_DEV_SPI1_FLASH_H_
#define _MANGO_DEV_SPI1_FLASH_H_

#include "typedef.h"
#include "ioctl.h"
#include "device_driver.h"

#include "mango_dev_spi.h"

#define DEV_GET_DEV_ID          _IOR(DEV_GENERAL_MAGIC,0xe3,u32)	//获取设备的ID。SD/TF 卡返回“sdtf”(0x73647466)
#define DEV_SECTOR_ERASE        _IOW(DEV_GENERAL_MAGIC,0xe4,u32)    //设备页擦除
#define DEV_BLOCK_ERASE         _IOW(DEV_GENERAL_MAGIC,0xe5,u32)    //设备块擦除
#define DEV_CHIP_ERASE          _IOW(DEV_GENERAL_MAGIC,0xe6,u32)    //设备擦除
#define DEV_GET_TYPE            _IOR(DEV_GENERAL_MAGIC,0xe7,u32)    //返回设备的dev_type
#define DEV_CHECK_WPSTA         _IOR(DEV_GENERAL_MAGIC,0xe8,u32)


typedef enum FLASH_MODE
{
	FAST_READ_OUTPUT_MODE = 0x0|SPI_PARM_VALID_MASK,
	FAST_READ_IO_MODE = 0x00001000|SPI_PARM_VALID_MASK,
	FAST_READ_IO_CONTINUOUS_READ_MODE = 0x00002000|SPI_PARM_VALID_MASK,
}FLASH_MODE;
#define FLASH_MODE_MASK         (0x00003000|SPI_PARM_VALID_MASK)

extern const struct DEV_IO * dev_reg_flash(void *parm);

#define SPI0FLASH_MAGIC         'F'
#define SPI0FLASH_READ_ID     _IOR(SPI0FLASH_MAGIC,1,u32)
#define SPI0FLASH_REMAP_CS    _IOW(SPI0FLASH_MAGIC,2,u32)
#define SPI0FLASH_PROTECT     _IOW(SPI0FLASH_MAGIC,2,u8)


#endif //_MANGO_DEV_SPI0_FLASH_H_

