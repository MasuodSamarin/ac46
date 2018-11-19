/*--------------------------------------------------------------------------*/
/**@file     key.h
   @brief
   @details
   @author
   @date   2011-4-26
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef _KEY_
#define _KEY_

#include "config.h"

// #define KEY_UART_DEBUG

#ifdef KEY_UART_DEBUG
    #define key_puts           puts
    #define key_printf         printf
    #define key_buf            put_buf
#else
    #define key_puts(...)
    #define key_printf(...)
    #define key_buf(...)
#endif/*KEY_UART_DEBUG*/

/*�������Ͷ���*/
#if 0
#if S10_MODE
    #define KEY_AD_EN       0   ///<AD����ʹ��
    #define KEY_IO_EN       1   ///<IO����ʹ��
#else
    #define KEY_AD_EN       1   ///<AD����ʹ��
    #define KEY_IO_EN       0   ///<IO����ʹ��
#endif

#if S10_MODE
    #define KEY_IR_EN       1   ///<����ң��ʹ��
#else
    #define KEY_IR_EN       1   ///<����ң��ʹ��
#endif
#endif
#define KEY_TCH_EN      0   ///<��������ʹ��

/*��������*/
enum
{

#if KEY_AD_EN
    KEY_TYPE_AD,
#endif
#ifdef SUPPORT_TM1628_KEY_READ
    KEY_TYPE_LED_DRIVER,
#endif

#if KEY_IO_EN
    KEY_TYPE_IO,
#endif

#if KEY_IR_EN
    KEY_TYPE_IR,
#endif

#if KEY_TCH_EN
    KEY_TYPE_TOUCH,
#endif
    MAX_TYPE_KEY,
};

/*�����ż�ֵ*/
#define KEY_BASE_CNT  4
#define KEY_LONG_CNT  75
#define KEY_HOLD_CNT  15
#define KEY_SHORT_CNT 7

/*����״̬*/
#define KEY_SHORT_UP    0x0
#define KEY_LONG        0x1
#define KEY_HOLD        0x2
#define KEY_LONG_UP     0x3

#define NO_KEY          0xff

typedef struct
{
    void    (*key_init)(void);
    u8      (*key_get_value)(void);
    u8      (*key_pressed_to_msg)(u8, u8);
}key_interface_t;

extern char *keymsg_task_name;
extern u32 input_number;	    ///<��������ֵ�ʵ��ֵ


void set_adc_clk(void);
void key_init();

#if ir_max_num

#if AD_KEY_MAX
 #if LED_KEY_MAX 
   void key_msg_register(char *task_name,const u8 led_key_t[4][LED_KEY_MAX],const u8 ad_key_t[4][10],const u8 io_key_t[4][10], 
                             const u8 ir_key_t[4][ir_max_num], const u8 touch_key_t[4][10]);
 #else
void key_msg_register(char *task_name,const u8 ad_key_t[4][AD_KEY_MAX],const u8 io_key_t[4][10],
                   const u8 ir_key_t[4][ir_max_num], const u8 touch_key_t[4][10]);
 #endif


#else
void key_msg_register(char *task_name,const u8 ad_key_t[4][10],const u8 io_key_t[4][10],
                       const u8 ir_key_t[4][ir_max_num], const u8 touch_key_t[4][10]);
#endif   

#else 
void key_msg_register(char *task_name,const u8 ad_key_t[4][10],const u8 io_key_t[4][10],
                       const u8 ir_key_t[4][21], const u8 touch_key_t[4][10]);
#endif         

extern void key_scan(void);
extern void key_drv_init(key_interface_t * interface);


#endif
