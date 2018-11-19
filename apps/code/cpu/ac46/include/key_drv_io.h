#ifndef __KEY_DRV_IO_H__
#define __KEY_DRV_IO_H__

#include "config.h"
#include "sys_detect.h"

#if KEY_IO_EN

#if S10_MODE
    #if S10_UART_DEBUG
    #define IS_KEY0_DOWN()    (!(PORTA_IN&BIT(14)))//pp
    #define IS_KEY1_DOWN()    (!USB_DP_IN())       //next
    #define IS_KEY2_DOWN()    (!(PORTA_IN&BIT(8))) //prev
    #define KEY_INIT()        do{PORTA_PU |= BIT(8)|BIT(14);PORTA_DIR |= BIT(8)|BIT(14);}while(0)
    #else
    #define IS_KEY0_DOWN()    (!(PORTA_IN&BIT(14)))//pp
    #define IS_KEY1_DOWN()    (!(USB_DP_IN()))     //next
    #define IS_KEY2_DOWN()    (!(PORTA_IN&BIT(8))) //prev
    #define KEY_INIT()        do{PORTA_PU |= BIT(8)|BIT(14);USB_DP_PU(1);PORTA_DIR |= BIT(8)|BIT(14);USB_DP_DIR(1);}while(0)
    #endif/*S10_UART_DEBUG*/
#elif defined(support_io_scan_key_user_PA0_PA4_PA6)
	
    #define IS_KEY1_DOWN()    (!(PORTA_IN&BIT(0)))//pp
    #define IS_KEY2_DOWN()   (!(PORTA_IN&BIT(4)))//pp
    #define IS_KEY3_DOWN()    (!(PORTA_IN&BIT(6))) //prev
    #define KEY_INIT()              do{ PORTA_PU |=BIT(0)|BIT(4)|BIT(6); PORTA_DIR |=BIT(0)|BIT(4)|BIT(6);}while(0)
		
   #define   SET_KEY2_LOW()    do{ PORTA_DIR &= ~BIT(4);PORTA_PU &=~BIT(4);} while(0);   PORTA_OUT &= ~BIT(4);
    #define  SET_KEY2_HIGH()   do{ PORTA_DIR &= ~BIT(4);PORTA_PU &=~BIT(4);} while(0);   PORTA_OUT |= BIT(4);
	
#elif defined(support_io_scan_key_user_PB7_PB8_PB9_PB10)

   #define IS_KEY0_DOWN()	  (!(PORTB_IN&BIT(7)))	
    #define IS_KEY1_DOWN()    (!(PORTB_IN&BIT(8)))
    #define IS_KEY2_DOWN()   (!(PORTB_IN&BIT(9)))
    #define IS_KEY3_DOWN()    (!(PORTB_IN&BIT(10))) 
	
    #define KEY_INIT()              do{ PORTB_PU |=BIT(7)|BIT(8)|BIT(9)|BIT(10); PORTB_DIR |=BIT(7)|BIT(8)|BIT(9)|BIT(10);}while(0)
#elif defined(SUPPORT_IO_SCAN_USE_PB10__PB6)
    #define IS_KEY0_DOWN()	  (!(PORTB_IN&BIT(10)))
    #define IS_KEY1_DOWN()    (!(PORTB_IN&BIT(9)))
    #define IS_KEY2_DOWN()   (!(PORTB_IN&BIT(8)))
    #define IS_KEY3_DOWN()    (!(PORTB_IN&BIT(7))) 
    #define IS_KEY4_DOWN()    (!(PORTB_IN&BIT(6))) 
    #define KEY_INIT()              do{ PORTB_PU |=BIT(6)|BIT(7)|BIT(8)|BIT(9)|BIT(10); PORTB_DIR |=BIT(6)|BIT(7)|BIT(8)|BIT(9)|BIT(10);}while(0)
	
    #define  SET_KEY4_LOW()	do{ PORTB_DIR &= ~BIT(6);PORTB_PU &=~BIT(6);} while(0);   PORTB_OUT &= ~BIT(6);
    #define  SET_KEY4_HIGH()	do{ PORTB_DIR &= ~BIT(6);PORTB_PU &=~BIT(6);} while(0);   PORTB_OUT |= BIT(6);
	
#elif defined(support_io_scan_key_user_PA5_PA6_PA7)
	
    #define IS_KEY1_DOWN()    (!(PORTA_IN&BIT(5)))//pp
    #define IS_KEY2_DOWN()   (!(PORTA_IN&BIT(6)))//pp
    #define IS_KEY3_DOWN()    (!(PORTA_IN&BIT(7))) //prev
    #define KEY_INIT()              do{ PORTA_PU |=BIT(5)|BIT(6)|BIT(7); PORTA_DIR |=BIT(5)|BIT(6)|BIT(7);}while(0)
		
   #define   SET_KEY2_LOW()    do{ PORTA_DIR &= ~BIT(6);PORTA_PU &=~BIT(6);} while(0);   PORTA_OUT &= ~BIT(6);
    #define  SET_KEY2_HIGH()   do{ PORTA_DIR &= ~BIT(6);PORTA_PU &=~BIT(6);} while(0);   PORTA_OUT |= BIT(6);
#elif defined(support_io_scan_key_user_PA5_PA6_PA7_PA8_PA9_PA10)
	
      #define IS_KEY1_DOWN()    (!(PORTA_IN&BIT(5)))
      #define IS_KEY2_DOWN()   (!(PORTA_IN&BIT(6)))
      #define IS_KEY3_DOWN()    (!(PORTA_IN&BIT(7))) 
      #define IS_KEY4_DOWN()    (!(PORTA_IN&BIT(8))) 
      #define IS_KEY5_DOWN()    (!(PORTA_IN&BIT(9))) 
      #define IS_KEY6_DOWN()    (!(PORTA_IN&BIT(10))) 
	
		
    #define KEY_INIT()              do{ PORTA_PU |=BIT(5)|BIT(6)|BIT(7)|BIT(8)|BIT(9)|BIT(10);\
														  PORTA_DIR |=BIT(5)|BIT(6)|BIT(7)|BIT(8)|BIT(9)|BIT(10);}while(0)
		
	//	 #define   SET_KEY2_LOW()	 do{ PORTA_DIR &= ~BIT(6);PORTA_PU &=~BIT(6);} while(0);   PORTA_OUT &= ~BIT(6);
	 //   #define  SET_KEY2_HIGH()	 do{ PORTA_DIR &= ~BIT(6);PORTA_PU &=~BIT(6);} while(0);   PORTA_OUT |= BIT(6);		
#else
    #define IS_KEY0_DOWN()    (!(PORTB_IN&BIT(9)))
    #define IS_KEY1_DOWN()    (!(PORTB_IN&BIT(10)))
    #define IS_KEY2_DOWN()    (!(PORTB_IN&BIT(11)))
    //#define KEY1_OUT_L()      do{PORTA_DIR &= ~BIT(13);PORTA_OUT &= ~BIT(13);}while(0)
    #define KEY_INIT()        do{PORTB_PU |= BIT(9)|BIT(10)|BIT(11);PORTB_DIR |= BIT(9)|BIT(10)|BIT(11);}while(0)
#endif/*S10_MODE*/

tu8 get_iokey_value(void);
extern void io_key_init(void);
extern  u8  io_key_get_value(void);
extern  u8  io_key_pressed_to_msg(u8 key_style, u8 key_num);

#endif/*KEY_IO_EN*/
#endif/*__KEY_DRV_IO_H__*/
