/*******************************************************************************************
 File Name: alink.h

 Version: 1.00

 Discription:


 Author:yulin deng

 Email :flowingfeeze@163.com

 Date:2014-01-13 17:09:41

 Copyright:(c)JIELI  2011  @ , All Rights Reserved.
*******************************************************************************************/
#ifndef alink_h
#define alink_h

#include "circular_buf.h"
#include "dac.h"

/* #define DAC_SAMPLE_POINT    (32*2*2*2) */
#define DAC_BUF_LEN         (DAC_SAMPLE_POINT*2*2)
#define DAC_DUAL_BUF_LEN    (DAC_SAMPLE_POINT * 2)

extern cbuffer_t dac_cb ;
#endif
