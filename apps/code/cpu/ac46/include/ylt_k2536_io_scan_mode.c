

tu8 get_iokey_value(void)
{

    tu8 key_num = NO_KEY;

    KEY_INIT();

  if(IS_KEY1_DOWN())
    {
      return  PKEY_PREV;   
    }
     if(IS_KEY2_DOWN())
    {
      return  PKEY_PP_MODE;    
    }
  if(IS_KEY3_DOWN())
    {
        return  PKEY_NEXT;  
    }

    return key_num;
}

