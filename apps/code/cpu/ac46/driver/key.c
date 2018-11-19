#include "includes.h"
#include "bt_key_msg.h"
#include "key.h"
#include "msg.h"
#include "key_drv_ad.h"
#include "key_drv_io.h"
#include "key_drv_ir.h"
#include "key_drv_tch.h"
#include "key_voice.h"
#ifdef SUPPORT_TM1628_KEY_READ
#include "led7_drv.h"
#endif

u8 key_type;        ///<按键类型
char *keymsg_task_name;
u32 input_number;	    ///<输入的数字的实际值

#if AD_KEY_MAX
u8 ad_msg_table[4][AD_KEY_MAX];
#else
u8 ad_msg_table[4][10];
#endif
u8 io_msg_table[4][10];
#if ir_max_num
  u8 ir_msg_table[4][ir_max_num];
#else 
u8 ir_msg_table[4][21];
#endif 
#ifdef SUPPORT_TM1628_KEY_READ
  #if LED_KEY_MAX
  u8 led_msg_table[4][10];
  #else
  u8 led_msg_table[4][10];
  #endif
#endif

u8 touch_msg_table[4][10];


tu8 (*get_key_tab[])(void) =
{
#if KEY_AD_EN
    get_adkey_value,
#endif
#ifdef SUPPORT_TM1628_KEY_READ
    get_led_driver_key_value,
#endif

#if KEY_IO_EN
    get_iokey_value,
#endif

#if KEY_IR_EN
    get_irkey_value,
#endif

#if KEY_TCH_EN
    get_tchkey_value,
#endif
};

void key_init()
{
    key_puts("key init\n");
    keymsg_task_name = NULL;
#if 1//KEY_AD_EN
    ad_key0_init();
#endif

#if KEY_IO_EN
//    io_key_init();
#endif

#if KEY_IR_EN
    ir_key_init();
#endif

#if KEY_TCH_EN
    tch_key_init();
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief   按键-消息转换函数
   @param   key_status：按键状态
   @param   back_last_key：最后按键值
   @return  void
   @note
*/
/*----------------------------------------------------------------------------*/
void key2msg_filter(u8 key_status, u8 back_last_key)
{
    tu8 msg = NO_MSG;
#if KEY_TONE_EN
#if (!S10_MODE)
 //   send_key_voice(500);
#endif
#endif

#ifdef SUPPORT_TM1628_KEY_READ 
    if(KEY_TYPE_LED_DRIVER== key_type)
    {    
        msg = led_msg_table[key_status][back_last_key];
    }
#endif

#if KEY_IR_EN
    if(KEY_TYPE_IR == key_type)
    {
        msg = ir_msg_table[key_status][back_last_key];
    }
#endif

#if KEY_IO_EN
    if(KEY_TYPE_IO == key_type)
    {
//        msg = io_msg_table[key_status][back_last_key];
       msg = ad_msg_table[key_status][back_last_key];

//		printf("----msg----%d\n",msg);
    }
#endif

#if KEY_AD_EN
    if(KEY_TYPE_AD == key_type)
    {
        msg = ad_msg_table[key_status][back_last_key];
    }
#endif

//    key_printf("msg:0x%02x\n",msg);
    if(msg < MSG_MAIN_MAX)
    {
        #if S10_MODE
        if((!strcmp(keymsg_task_name,"btmsg")) && (msg==MSG_CHANGE_WORKMODE))
            os_taskq_post_msg(keymsg_task_name, 1, MSG_BT_CALL_REJECT);
        else
        #endif
         os_taskq_post_msg("MainTask", 1, msg);
    }
    else if(keymsg_task_name)
    {
        os_taskq_post_msg(keymsg_task_name, 1, msg);
    }
}

/*----------------------------------------------------------------------------*/
/**@brief   按键去抖函数，输出稳定键值
   @param   key：键值
   @return  稳定按键
   @note    tu8 key_filter(tu8 key)
*/
/*----------------------------------------------------------------------------*/
static tu8 key_filter(tu8 key)
{
    static tu8 used_key = NO_KEY;
    static tu8 old_key;
    static tu8 key_counter;

    if (old_key != key)
    {
        key_counter = 0;
        old_key = key;
    }
    else
    {
        key_counter++;
        if (key_counter == KEY_BASE_CNT)
        {
            used_key = key;
        }
    }

    return used_key;
}

/*----------------------------------------------------------------------------*/
/**@brief   按键-消息转换函数,按键产生顺序：短按抬起/长按-->连按
   @param
   @param
   @return  void
   @note
*/
/*----------------------------------------------------------------------------*/
tu8 get_key_value(void)
{
    tu8 i;

    for(i = 0; i < MAX_TYPE_KEY; i++)
    {
        tu8 msg;
        tu8 (*get_key)(void);

        get_key = get_key_tab[i];
        if(NULL != get_key)
        {

        
#if KEY_IR_EN
            if(i == KEY_TYPE_IR)
            {
                msg = get_key();
            }
            else
#endif
#if  KEY_TCH_EN
            if(i == KEY_TYPE_TOUCH)
            {
                msg = get_key();
            }
            else
#endif

            {
                msg = key_filter(get_key());
            }

            if(NO_KEY != msg)
            {
	//		printf("msg=========%x\n",msg);            
                key_type = i;
			
                return msg;
            }
        }
    }
    return NO_KEY;

}

/*----------------------------------------------------------------------------*/
/**@brief   按键-消息转换函数,按键产生顺序：短按抬起/长按-->连按
   @param
   @param
   @return  void
   @note
*/
/*----------------------------------------------------------------------------*/
void key_scan(void)
{
    static tu8 last_key = NO_KEY;
    static tu8 key_press_counter;
    static u8  key_press_flag = 0;
    tu8 cur_key, key_status, back_last_key;

    if(key_press_flag)
    {
        key_press_flag++;
        if(key_press_flag > 50)
        {
            key_puts(" One_Click ");
            key_press_flag = 0;
            key2msg_filter(KEY_SHORT_UP, 0);
        }
    }

    cur_key = NO_KEY;
    back_last_key = last_key;
    cur_key = get_key_value();

    if (cur_key == last_key)                            //长时间按键
    {
        if (cur_key == NO_KEY)
        {
            return;
        }

        key_press_counter++;

        if (key_press_counter == KEY_LONG_CNT)          //长按
        {
            key_status = KEY_LONG;
        }
        else if (key_press_counter == (KEY_LONG_CNT + KEY_HOLD_CNT))        //连按
        {
            key_status = KEY_HOLD;
            key_press_counter = KEY_LONG_CNT;
        }
        else
        {
            return;
        }
    }
    else  //cur_key = NO_KEY, 抬键
    {
        last_key = cur_key;
        if ((key_press_counter < KEY_LONG_CNT) && (cur_key != NO_KEY))
        {
        }
        if ((key_press_counter < KEY_LONG_CNT) && (cur_key == NO_KEY))      //短按抬起
        {        
            key_press_counter = 0;
            key_status = KEY_SHORT_UP;
        }
        else
        {
            key_press_counter = 0;
            return;
        }
    }
#ifdef KEY_DOUBLE_CLICK
    if(!strcmp(keymsg_task_name,"btmsg"))//蓝牙模式才有按键双击功能
    {
        if((back_last_key==0)&&(key_status==KEY_SHORT_UP))
        {
            if(key_press_flag == 0)
                key_press_flag = 1;
            if((key_press_flag > 15) && (key_press_flag < 50))
            {
                key_puts(" Double_Click ");
                key_press_flag = 0;
                key2msg_filter(key_status, 9);
            }
        }
        else
        {
            key2msg_filter(key_status, back_last_key);
        }
    }
    else
#endif/*KEY_DOUBLE_CLICK*/
    key2msg_filter(key_status, back_last_key);
}

/*----------------------------------------------------------------------------*/
/**@brief   按键消息注册
   @param
   @param
   @return  void
   @note
*/
/*----------------------------------------------------------------------------*/
#if ir_max_num
#if AD_KEY_MAX
#if LED_KEY_MAX
  void key_msg_register(char *task_name,const u8 led_key_t[4][LED_KEY_MAX],const u8 ad_key_t[4][10],const u8 io_key_t[4][10], const u8 ir_key_t[4][ir_max_num], const u8 touch_key_t[4][10])
#else
void key_msg_register(char *task_name,const u8 ad_key_t[4][AD_KEY_MAX],const u8 io_key_t[4][10], const u8 ir_key_t[4][ir_max_num], const u8 touch_key_t[4][10])
#endif

#else
  void key_msg_register(char *task_name,const u8 ad_key_t[4][10],const u8 io_key_t[4][10], const u8 ir_key_t[4][ir_max_num], const u8 touch_key_t[4][10])
#endif  
#else 
void key_msg_register(char *task_name,const u8 ad_key_t[4][10],const u8 io_key_t[4][10], const u8 ir_key_t[4][21], const u8 touch_key_t[4][10])
#endif
{
    keymsg_task_name = task_name;


#ifdef SUPPORT_TM1628_KEY_READ
  if(led_key_t)
  #if LED_KEY_MAX
   memcpy(led_msg_table,led_key_t,4*LED_KEY_MAX);
  #else
  memcpy(led_msg_table,led_key_t,4*10);
  #endif
#endif

#if KEY_AD_EN
#if USE_AD_KEY0
    if(ad_key_t)
       #if AD_KEY_MAX
        memcpy(ad_msg_table,ad_key_t,4*AD_KEY_MAX);
       #else
        memcpy(ad_msg_table,ad_key_t,4*10);
       #endif
#endif
#if USE_AD_KEY1
    if(ad_key_t)
        memcpy(ad_msg_table,ad_key_t,4*10);
#endif
#endif

#if KEY_IO_EN
    if(io_key_t)
//        memcpy(io_msg_table,io_key_t,4*10);
	  memcpy(ad_msg_table,ad_key_t,4*10);
#endif

#if KEY_IR_EN
   if(ir_key_t)
   #if ir_max_num
		memcpy(ir_msg_table,ir_key_t,4*ir_max_num);
   #else 
		memcpy(ir_msg_table,ir_key_t,4*21);
   #endif 	
#endif

#if KEY_TCH_EN
    if(touch_key_t)
        memcpy(touch_msg_table,touch_key_t,4*10);
#endif
}
