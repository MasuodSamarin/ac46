#ifndef JIFFIES_H
#define JIFFIES_H


extern volatile unsigned long jiffies;


#define time_after_bt(a,b)						 ((long)(b) - (long)(a) < 0)
#define time_before_bt(a,b)			     time_after_bt(b, a)


#define msecs_to_jiffies(msec)       ((msec)/2)








#endif

