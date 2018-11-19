

tu8 get_iokey_value(void)
{

    tu8 key_num = NO_KEY;

    KEY_INIT();

  if(IS_KEY1_DOWN())
    {
      return  PKEY_ONLY_NEXT;   
    }
     if(IS_KEY2_DOWN())
    {
      return  PKEY_ONLY_PREV;    
    }
  if(IS_KEY3_DOWN())
    {
        return  PKEY_PP;  
    }

  if(IS_KEY4_DOWN())
    {
      return  PKEY_MODE;   
    }
     if(IS_KEY5_DOWN())
    {
      return  PKEY_VOL_UP;    
    }
  if(IS_KEY6_DOWN())
    {
        return  PKEY_VOL_DN;  
    }
    return key_num;
}

