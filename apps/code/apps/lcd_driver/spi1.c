#include "spi1.h"
#include "config.h"

void spi_flash_read(u8 *buf,u32 addr,u32 len)
{
    flash_read(buf,addr,len);
}

void SPI1_init(tbool is3Wrie, tu8 speed)
{
    SPI1_BAUD = speed;

    SPI1_CON = 0x4021;//0100 0000 0010 0001

    IOMC1 |= BIT(4);
    PORTB_DIR &= ~(BIT(6) | BIT(7));
    if(is3Wrie)
    {
        SPI1_CON |= BIT(3);
        PORTB_DIR |= BIT(5);
    }
}

#define WAIT_SPI1_OK()    while (!(SPI1_CON & BIT(15)));SPI1_CON |= BIT(14)


void SPI1_cs(u32 cs)
{
    PORTB_DIR &= ~BIT(10);

    if(cs)
    {
        delay(100);
        PORTB_OUT |= BIT(10) ;
    }
    else
    {
        PORTB_OUT &= ~BIT(10) ;
        delay(100);
    }

}

/*
 ********************************************************************************
 *               void SPI1_SetSpeed(u8 speed)
 *
 * Description : 设置spi flash 接口速度
 *
 * Arguments   : speed -- 速度值
 *
 * Returns     :
 *
 * Notes       : clk = sys clk/(speed+1) ;
 *
 ********************************************************************************
 */

void SPI1_SetSpeed(tu8 speed)
{
    SPI1_BAUD = speed ;
}
/*
 ********************************************************************************
 *
 *
 * Description : spi 接口轮询方式发送一个byte
 *
 * Arguments   : 发送的数据
 *
 * Returns     :
 *
 * Notes       :
 *
 ********************************************************************************
 */
void SPI1_WriteByte(tu8 dat)
{
    //put_u16hex(dat);
    SPI1_CON &= ~BIT(12);
    SPI1_BUF = dat;
    WAIT_SPI1_OK();
    //printf("ok");
}
/*
 ********************************************************************************
 *
 *
 * Description : spi 接口轮询方式接受一个byte 数据
 *
 * Arguments   : 无
 *
 * Returns     :  读到的数据
 *
 * Notes       :
 *
 ********************************************************************************
 */
tu8 SPI1_ReadByte(void)
{
    SPI1_CON |= BIT(12);

    SPI1_BUF = 0xff;

    WAIT_SPI1_OK();

    return SPI1_BUF;
}

/*
 ********************************************************************************
 *
 *
 * Description : 通过dma 方式发送数据
 *
 * Arguments   : buf --数据指针
 								 len --数据长度
 *
 * Returns     :
 *
 * Notes       :
 *
 ********************************************************************************
 */
void SPI1_DmaWrite(void *buf, tu16 len)
{
    SPI1_CON &= ~BIT(12);


    SPI1_ADR = (u32) buf;
    SPI1_CNT = len;

    WAIT_SPI1_OK();
}


/*
 ********************************************************************************
 *
 *
 * Description : 通过DMA 方式读入数据
 *
 * Arguments   : buf --数据指针
 *							 len --读取数据长度
 * Returns     :
 *
 * Notes       :
 *
 ********************************************************************************
 */
void SPI1_DmaRead(void *buf, tu16 len)
{
    SPI1_CON |= BIT(12);      //[12]:DIR

    SPI1_ADR = (u32) buf;
    SPI1_CNT = len;

    WAIT_SPI1_OK();
}

#if 0

#include "spiflash.h"
//#include "interrupt.h"

static SPI_FLASH_CMD const g_default_cmd =
{
    {
        WINBOND_CHIP_ERASE,
        WINBOND_BLOCK_ERASE,
        WINBOND_SECTOR_ERASE
    },
    WINBOND_READ_DATA,
    WINBOND_PAGE_PROGRAM,
    WINBOND_READ_SR,
    WINBOND_WRITE_ENABLE,
    WINBOND_WRITE_DISABLE,
};

void spi0_flash_wait_ok(void)
{
    SPI0_cs(0);

    SPI1_WriteByte(g_default_cmd.read_sr);

    while(SPI0_ReadByte() & 0x01)
    {
        delay(20);
    }

    SPI0_cs(1);
}

/*----------------------------------------------------------------------------*/
/** @brief:write a normal cmd to spi flash and wait ok
    @param:
    @return:
    @author:Juntham
    @note:
    @date: 2012-03-15,15:01
*/
/*----------------------------------------------------------------------------*/
void spi0_flash_send_cmd(tu8 cmd)
{
    spi0_flash_wait_ok();

    SPI0_cs(0);

    SPI1_WriteByte(cmd);

    SPI0_cs(1);
}

/*
 ********************************************************************************
 *              void spi0_flash_send_addr(u32 addr)
 *
 * Description : 发送spi flash 读写地址
 *
 * Arguments   : addr -- 地址
 *
 * Returns     :
 *
 * Notes       :
 *
 ********************************************************************************
 */

void spi0_flash_send_addr(u32 addr)
{
    SPI1_WriteByte(addr >> 16);
    SPI1_WriteByte(addr >> 8);
    SPI1_WriteByte(addr);
}

/*
 ********************************************************************************
 *              void spi_flash_read_id(u8  *buf)
 *
 * Description : 读取spi flash id号。
 *
 * Arguments   : buf -- 存放id buffer，深度要求为3byte
 *
 * Returns     :
 *
 * Notes       :
 *
 ********************************************************************************
 */
u32 spi0_flash_read_id()
{
    tu8 i;
    u8 r[3];

    SPI0_cs(0);

    SPI1_WriteByte(WINBOND_JEDEC_ID);

    for(i = 0; i < 3; i++)
    {
        r[i] = SPI0_ReadByte();
        if(r[i] == 0xff)
        {
            return 0x0;
        }
    }
    SPI0_cs(1);

    return r[0] << 16 | r[1] << 8 | r[2];
}




/*
 ********************************************************************************
 *              void spi_read(u32 addr ,u8 _ *buf, u16 len)
 *
 * Description : 读取指定spi flash 地址数据
 *
 * Arguments   :
 *
 * Returns     :
 *
 * Notes       :
 *
 ********************************************************************************
 */
void spi0_flash_read(void *buf, u32 addr , tu16 len)
{
    spi0_flash_wait_ok();

    SPI0_cs(0);
    SPI1_WriteByte(g_default_cmd.read);
    spi0_flash_send_addr(addr);
    delay(10);

//	SPI1_ReadByte();				//read a dummy byte
    SPI0_DmaRead(buf, len);

    SPI0_cs(1);
}

void spi0_flash_eraser(FLASH_ERASER eraser, u32 address)
{
    spi0_flash_send_cmd(g_default_cmd.write_en);

    SPI0_cs(0);

    SPI1_WriteByte(g_default_cmd.eraser[eraser]);
    if(eraser != CHIP_ERASER)
    {
        spi0_flash_send_addr(address) ;
    }

    SPI0_cs(1);

//	spi_flash_send_cmd(g_pflash_cmd->write_dis);
}

/*----------------------------------------------------------------------------*/
/** @brief: spi flash write
    @param:
    @return:
    @author:Juntham
    @note:
    @date: 2012-03-15,15:30
*/
/*----------------------------------------------------------------------------*/
void spi0_flash_write(void *buf, u32 addr, tu16 len)
{
    while(len)
    {
        spi0_flash_send_cmd(g_default_cmd.write_en);

        SPI0_cs(0);

        SPI1_WriteByte(g_default_cmd.write);

        spi0_flash_send_addr(addr) ;
        delay(20);

        SPI1_DmaWrite(buf, 256);

        SPI0_cs(1);

//		spi0_flash_send_cmd(g_default_cmd.write_dis);

        len -= 256;
        addr += 256;
        buf	= ((u8*) buf) + 256;
    }
}

void spi0_flash_write_protect(u16 cmd)
{
    spi0_flash_send_cmd(g_default_cmd.write_en);

    SPI0_cs(0);

    SPI1_WriteByte(01);

    SPI1_WriteByte((u8) cmd); 		//低byte
    SPI1_WriteByte((u8)(cmd >> 8));	//高byte

    SPI0_cs(1);
}


#endif
