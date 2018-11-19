#ifndef _RTC_LOW_POWER_H_
#define _RTC_LOW_POWER_H_

/////////////////RTC LOWPOWER//////////////////////
//rtc_lowpower(WAKE_UP_PR0|WAKE_UP_PR1|WAKE_UP_PR2|WAKE_UP_PR3,FALL_EDGE_PR0|FALL_EDGE_PR1|FALL_EDGE_PR2|FALL_EDGE_PR3);
#define    WAKE_UP_PR0  0X01
#define    WAKE_UP_PR1  0X02
#define    WAKE_UP_PR2  0X04
#define    WAKE_UP_PR3  0X08

#define    FALL_EDGE_PR0    0x10
#define    FALL_EDGE_PR1    0x20
#define    FALL_EDGE_PR2    0x40
#define    FALL_EDGE_PR3    0x80
/////////////////////////////////////////////////////

extern void rtc_lowpower_api(void);
#endif
