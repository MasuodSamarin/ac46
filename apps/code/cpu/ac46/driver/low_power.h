#ifndef __LOW_POWER_H__
#define __LOW_POWER_H__

#include "typedef.h"

enum{
    WAKEUP_0  = 0,
    WAKEUP_1,
    WAKEUP_2,
    WAKEUP_3,
    WAKEUP_4,
    WAKEUP_5,
    WAKEUP_6,
    WAKEUP_7,
    WAKEUP_8,
    WAKEUP_9,
    WAKEUP_10,
    WAKEUP_11,
    WAKEUP_12,
    WAKEUP_13,
    WAKEUP_14,
    WAKEUP_15,
};

#define WAKEUP_UP_EDGE        0X0F   //…œ…˝—ÿªΩ–—
#define WAKEUP_DOWN_EDGE      0XF0   //œ¬Ωµ—ÿªΩ–—

///ªΩ–—‘¥
#define WAKEUP_PA9_EVENT()                (WKUP_CON0 & BIT(8))
#define WAKEUP_PA11_EVENT()               (WKUP_CON0 & BIT(9))
#define WAKEUP_PA13_EVENT()               (WKUP_CON0 & BIT(10))
#define WAKEUP_PA15_EVENT()               (WKUP_CON0 & BIT(11))
//#define WAKEUP_UART0_RX_EVENT()           (WKUP_CON0 & BIT(12))
#define WAKEUP_IIC_SDA_EVENT()            (WKUP_CON0 & BIT(13))
#define WAKEUP_SPI0_CLK_EVENT()           (WKUP_CON0 & BIT(14))
#define WAKEUP_UART0_RX_EVENT()           (WKUP_CON0 & BIT(15))


///«ÂªΩ–—±Í÷æ
#define CLR_WAKEUP_PA9_EVENT()                (WKUP_CON1 |= BIT(8))
#define CLR_WAKEUP_PA11_EVENT()               (WKUP_CON1 |= BIT(9))
#define CLR_WAKEUP_PA13_EVENT()               (WKUP_CON1 |= BIT(10))
#define CLR_WAKEUP_PA15_EVENT()               (WKUP_CON1 |= BIT(11))
//#define CLR_WAKEUP_UART0_RX_EVENT()           (WKUP_CON1 |= BIT(12))
#define CLR_WAKEUP_IIC_SDA_EVENT()            (WKUP_CON1 |= BIT(13))
#define CLR_WAKEUP_SPI0_CLK_EVENT()           (WKUP_CON1 |= BIT(14))
#define CLR_WAKEUP_UART0_RX_EVENT()           (WKUP_CON1 |= BIT(15))


#define	LOFC_CKG0(SW)           ((SW)? (CLK_GAT0 &= ~((u16)1 << 13)): (CLK_GAT0 |= ((u16)1 << 13)))
#define	PAP_CKG0(SW)        ((SW)? (CLK_GAT0 &= ~((u16)1 << 9)): (CLK_GAT0 |= ((u16)1 << 9)))
#define	LCD_CKG1(SW)            ((SW)? (CLK_GAT1 &= ~((u16)1 << 15)): (CLK_GAT1 |= ((u16)1 << 15)))
#define	IRDA_FLT_CKG1(SW)       ((SW)? (CLK_GAT1 &= ~((u16)1 << 1)): (CLK_GAT1 |= ((u16)1 << 1)))
#define	CTMU_CKG1(SW)             ((SW)? (CLK_GAT1 &= ~((u16)1 << 0)): (CLK_GAT1 |= ((u16)1 << 0)))
#define	USB_BRIDGE_CKG1(SW)      ((SW)? (CLK_GAT1 &= ~((u16)1 << 8)): (CLK_GAT1 |= ((u16)1 << 8)))
#define	ISP_CKG0(SW)         ((SW)? (CLK_GAT0 &= ~((u16)1 << 2)): (CLK_GAT0 |= ((u16)1 << 2)))
#define	AUDIO_LINK_CKG0(SW)   ((SW)? (CLK_GAT0 &= ~((u16)1 << 5)): (CLK_GAT0 |= ((u16)1 << 5)))
#define	SDRAM_CKG1(SW)          ((SW)? (CLK_GAT1 &= ~((u16)1 << 9)): (CLK_GAT1 |= ((u16)1 << 9)))
#define	SDRAM_MAIN_CKG1(SW)       ((SW)? (CLK_GAT1 &= ~((u16)1 << 12)): (CLK_GAT1 |= ((u16)1 << 12)))
#define	SENSOR_CKG0(SW)         ((SW)? (CLK_GAT0 &= ~((u16)1 << 12)): (CLK_GAT0 |= ((u16)1 << 12)))
#define	JPEG_CKG1(SW)            ((SW)? (CLK_GAT1 &= ~((u16)1 << 7)): (CLK_GAT1 |= ((u16)1 << 7)))

#define CORE_1_91V      0
#define CORE_1_84V      1
#define CORE_1_80V      2
#define CORE_1_75V      3
#define CORE_1_70V      4
#define CORE_1_65V      5
#define CORE_1_60V      6
#define CORE_1_57V      7

#define IO_3V5          0
#define IO_3V3          1
#define IO_3V1          2
#define IO_3V0          3

#define SET_CORE_VOL(dat)   (LDO_CON |= (dat << 4))
#define SET_IO_VOL(dat)     (LDO_CON |= (dat << 2))

void low_power_mode(u16 wakeup_cfg, u8 wakeup_edge);

#endif


