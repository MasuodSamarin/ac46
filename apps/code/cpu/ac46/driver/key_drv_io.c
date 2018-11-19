#include "includes.h"
#include "key.h"
#include "key_drv_io.h"
#include "key_msg.h"

#if KEY_IO_EN

/*----------------------------------------------------------------------------*/
/**@brief   io按键初始化
   @param   void
   @param   void
   @return  void
   @note    void io_key_init(void)
*/
/*----------------------------------------------------------------------------*/
void io_key_init(void)
{
    KEY_INIT();
}

/*----------------------------------------------------------------------------*/
/**@brief   获取IO按键电平值
   @param   void
   @param   void
   @return  key_num:io按键号
   @note    tu8 get_iokey_value(void)
*/
/*----------------------------------------------------------------------------*/
tu8 get_iokey_value(void)
{
	
#ifdef support_sw005_io_scan_mode
		tu8 key_num = NO_KEY;
	
		KEY_INIT();
		
		if(IS_KEY1_DOWN())
		{
			return	6;	 // mode 
		}
		 if(IS_KEY2_DOWN())
		{
			//key_puts("KEY1\n");
			return	7;	//next
		}
	  if(IS_KEY3_DOWN())
		{
			//key_puts("KEY2\n");
			return	8;	//prev
		}
	
	
			SET_KEY2_LOW(); 	
			delay(200);
			
			  if(IS_KEY3_DOWN())
				{
				   //key_puts("KEY2\n");
				 key_num= 9;  //pp 
				}
			
		  SET_KEY2_HIGH();	
	
		return key_num;
#elif defined(support_YHD328_io_scan_mode)
	
		tu8 key_num = NO_KEY;
	
		KEY_INIT();
		
		if(IS_KEY1_DOWN())
		{
			return	PKEY_NEXT;	
		}
		 if(IS_KEY2_DOWN())
		{
			//key_puts("KEY1\n");
			return	PKEY_PREV; 
		}
	  if(IS_KEY3_DOWN())
		{
			//key_puts("KEY2\n");
			return	PKEY_PP;  //prev
		}
	
	
			SET_KEY2_LOW(); 	
			delay(200);
			
			  if(IS_KEY3_DOWN())
				{
				   //key_puts("KEY2\n");
				 key_num= PKEY_MODE;  //pp 
				}
			
		  SET_KEY2_HIGH();	
	
		return key_num;

#elif defined(IO_KEY_BJ001_SCAN_MODE)
	  tu8 key_num = NO_KEY;

// PB7-V- PB8-PP PB9-V+ PB10-MODE

	  KEY_INIT();
	  
	  if(IS_KEY0_DOWN())
	  {
		  key_puts("KEY1 \n");
	  
		  return  PKEY_PREV;	
	  }
	  if(IS_KEY1_DOWN())
	  {
		  key_puts("KEY 2 \n");
		  return  PKEY_PP;  
	  }
	   if(IS_KEY2_DOWN())
	  {
		  key_puts("KEY 3 \n");
		  return  PKEY_NEXT; 
	  }
	if(IS_KEY3_DOWN())
	  {
		  key_puts("KEY 4 \n");
		  return  PKEY_MODE;	
	  }
		
	  return key_num;		
#elif defined(IO_KEY_MSJ_VFD35_BOARD_SCAN_MODE)
	  tu8 key_num = NO_KEY;
	
	  KEY_INIT();
	  
	  if(IS_KEY0_DOWN())
	  {
		  return  PKEY_PP;	
	  }
	  if(IS_KEY1_DOWN())
	  {
		  return  PKEY_PREV;  
	  }
	   if(IS_KEY2_DOWN())
	  {
		  //key_puts("KEY1\n");
		  return  PKEY_NEXT; 
	  }
	if(IS_KEY3_DOWN())
	  {
		  //key_puts("KEY2\n");
		  return  PKEY_STOP;	//prev
	  }
		  if(IS_KEY4_DOWN())
			{
				//key_puts("KEY2\n");
				return	PKEY_REPEAT;	  //prev
			}
		  SET_KEY4_LOW();	  
		  delay(200);
		  
			if(IS_KEY0_DOWN())
			  {
				 //key_puts("KEY2\n");
			   key_num= PKEY_EQ;	//pp 
			  }
		  
		  if(IS_KEY1_DOWN())
			{
			   //key_puts("KEY2\n");
			 key_num= PKEY_VOL_DN;	  //pp 
			}
		  if(IS_KEY2_DOWN())
			{
			   //key_puts("KEY2\n");
			 key_num= PKEY_VOL_UP;	  //pp 
			}
		  if(IS_KEY3_DOWN())
			{
			   //key_puts("KEY2\n");
			 key_num= PKEY_MODE;	  //pp 
			}
		SET_KEY4_HIGH();  
		
	  return key_num;
	
#elif defined(SUPPORT_MSJ_K1719_IO_KEY_VALUE)
	  tu8 key_num = NO_KEY;
	
	  KEY_INIT();
	  
	  if(IS_KEY1_DOWN())
	  {
		  return  PKEY_MODE; //NEXT  
	  }
	   if(IS_KEY2_DOWN())
	  {
		  //key_puts("KEY1\n");
		  return  PKEY_NEXT;//PKEY_PREV; 
	  }
	if(IS_KEY3_DOWN())
	  {
		  //key_puts("KEY2\n");
		  return  PKEY_PREV;//PKEY_PP;	
	  }
	
	
		  SET_KEY2_LOW();	  
		  delay(200);
		  
			if(IS_KEY3_DOWN())
			  {
				 //key_puts("KEY2\n");
			   key_num= PKEY_PP;	//MODE 
			  }
		  
		SET_KEY2_HIGH();  
	
	  return key_num;
#else 
	
		//key_puts("get_iokey_value\n");
		tu8 key_num = NO_KEY;
	
		KEY_INIT();
		if(IS_KEY0_DOWN())
		{
			//key_puts("KEY0\n");
			return 0;
		}
		if(IS_KEY1_DOWN())
		{
			//key_puts("KEY1\n");
			return 1;
		}
		if(IS_KEY2_DOWN())
		{
			//key_puts("KEY2\n");
			return 2;
		}
	
	//	  KEY1_OUT_L();
	//	  if(IS_KEY2_DOWN())//
	//	  {
	//		  PORTA_OUT |= BIT(13);
	//		  return 4;
	//	  }
		return key_num;
	
#endif 
}

#endif/*KEY_IO_EN*/
