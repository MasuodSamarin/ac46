#include "interrupt_isr.h"
#include "config.h"

void timer2_isr()
{

}

void timer3_isr()
{

}

void uart0_isr()
{

}

void uart1_isr()
{

}

void uart2_isr()
{

}

void iic_isr()
{

}

void spi1_isr()
{

}

#if !RTC_CLK_EN
void rtc_isr()
{

}
#endif

#if !FM_RADIO_EN
void fm_svr()
{

}
void fm_lofc_svr()
{

}
#endif

#if !USB_PC_EN
void usbs_ctl_isr()
{

}
#endif
