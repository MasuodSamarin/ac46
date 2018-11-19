#include "config.h"
#include "lcd_spi.h"
#include "ui_api.h"

#if LCD_128X64_EN

#define WAIT_SPI1_OK()    while (!(SPI1_CON & BIT(15)));SPI1_CON |= BIT(14)


void spi_flash_read(u8 *buf, u32 addr, u32 len)
{
    flash_read(buf, addr, len);
}


void SPI1_init(bool is3Wrie, u8 speed)
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


void SPI1_WriteByte(u8 dat)
{
    //put_u16hex(dat);
    SPI1_CON &= ~BIT(12);
    SPI1_BUF = dat;
    WAIT_SPI1_OK();
    //printf("ok");
}


void SPI1_DmaWrite(void *buf, u16 len)
{
    SPI1_CON &= ~BIT(12);
    SPI1_ADR = (u32) buf;
    SPI1_CNT = len;

    WAIT_SPI1_OK();
}

#if 0
u8 SPI1_ReadByte(void)
{
    SPI1_CON |= BIT(12);
    SPI1_BUF = 0xff;
    WAIT_SPI1_OK();

    return SPI1_BUF;
}

void SPI1_DmaRead(void *buf, tu16 len)
{
    SPI1_CON |= BIT(12);      //[12]:DIR
    SPI1_ADR = (u32) buf;
    SPI1_CNT = len;
    WAIT_SPI1_OK();
}
#endif

#endif/*LCD_128x64_EN*/
