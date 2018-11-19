


extern volatile u32 dac_energy_value;

void  led_disp_eq(void)  
{


	u8  eq_count;
	static u8 rgb_led_coumt;
	static u8 rgb_disp_mode=6;
	static u8 no_singal_time;


     if( dac_energy_value<0x1000)   //无信号计时
              no_singal_time++;
        else 
              no_singal_time=0;
      
         if(no_singal_time>100)
      	         no_singal_time=110;
      	
        set_all_led_io_is_out();  	                                          

if (no_singal_time>100)  //无信号
     {
	rgb_led_coumt++;
	if(rgb_led_coumt>50)
	{
	rgb_led_coumt=0;
	rgb_disp_mode++;
	}
	else 
	return;

	if(rgb_disp_mode>9)
	 rgb_disp_mode=0; 

	 set_all_led_io_off();   
	 
	switch(rgb_disp_mode)
			{
			case 0:   Set_1_led_io_is_on(); 	return; 
			case 9:
			case 1:   Set_2_led_io_is_on(); 	return; 
			case 8:
			case 2:   Set_3_led_io_is_on(); 	return; 
			case 7:
			case 3:   Set_4_led_io_is_on(); 	return; 
			case 6:
			case 4:   Set_5_led_io_is_on(); 	return; 
			case 5:   Set_6_led_io_is_on(); 	return; 
			}
	}
   
    else     /*频谱显示模式*/
	{

rgb_disp_mode=20;
                          
                          		rgb_led_coumt++;
                          		if(rgb_led_coumt>8)
                          		{
                          		rgb_led_coumt=0;
                          		}
                          		else 
                          		return;                      
                                     
			    eq_count =(dac_energy_value>>12)/5%7;
			
                          		set_all_led_io_off(); 
                          
                          	//	eq_count=eq_count%4;    
                          
                          		switch(eq_count)
                                           {
						case 0:       	break;
						case 1: 
	  						Set_1_led_io_is_on(); 	
	  						break;

						case 2: 
							Set_1_led_io_is_on(); Set_2_led_io_is_on(); 
							break;
						case 3: 
							Set_1_led_io_is_on(); Set_2_led_io_is_on(); Set_3_led_io_is_on(); 
							break;        
						case 4: 
							Set_1_led_io_is_on(); Set_2_led_io_is_on(); Set_3_led_io_is_on(); 
							Set_4_led_io_is_on(); 
							break;      
						case 5: 
						         Set_1_led_io_is_on(); 	Set_2_led_io_is_on(); Set_3_led_io_is_on(); 
						         Set_4_led_io_is_on(); 	Set_5_led_io_is_on(); 
						break;            
						case 6: 
							  Set_1_led_io_is_on(); 	Set_2_led_io_is_on(); Set_3_led_io_is_on(); 
						         Set_4_led_io_is_on(); 	Set_5_led_io_is_on(); Set_6_led_io_is_on(); 
						break;      
                                                                   
                                 
                                     
                                           }
                          
         }
}










