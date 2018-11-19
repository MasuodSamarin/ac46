

tu8 get_iokey_value(void)
{

    tu8 key_num = NO_KEY;

    KEY_INIT();

  if(IS_KEY1_DOWN())   //pb7
    {
      return  PKEY_PP_MODE;   
    }
     if(IS_KEY2_DOWN())  //PB8
    {
      return  PKEY_NEXT;    
    }
  if(IS_KEY3_DOWN())  //PB9
    {
        return  PKEY_PREV;  
    }
  if(IS_KEY4_DOWN())  //pb10
    {
        return  PKEY_LIGHT;  
    }
    return key_num;
}

