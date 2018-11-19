


/**********************  MUZHE IO SET  **************************/

/*  line 检测   */

#ifdef  AUX_DETECT_EN
              #ifdef support_line_chack_user_PC10
                  #define AUX_IO_BIT    BIT(10)
                  #define AUX_DIR_SET    (PORTC_DIR |= AUX_IO_BIT)
                  #define AUX_PU_SET      (PORTC_PU  |= AUX_IO_BIT)
                  #define AUX_IN_CHECK  (PORTC_IN  &  AUX_IO_BIT)
				  
              #elif defined(support_line_chack_user_PC11)
                     #define AUX_IO_BIT    BIT(11)
                     #define AUX_DIR_SET    (PORTC_DIR |= AUX_IO_BIT)
                     #define AUX_PU_SET      (PORTC_PU  |= AUX_IO_BIT)
                     #define AUX_IN_CHECK  (PORTC_IN  &  AUX_IO_BIT)	
              #elif defined(support_line_chack_user_PA5) 
                    #define AUX_IO_BIT    BIT(5)
                    #define AUX_DIR_SET   (PORTA_DIR |= AUX_IO_BIT)
                    #define AUX_PU_SET    (PORTA_PU  |= AUX_IO_BIT)
                    #define AUX_IN_CHECK  (PORTA_IN  &  AUX_IO_BIT)  	
              #elif defined(support_line_chack_user_PA8) 
                   #define AUX_IO_BIT    BIT(8)
                   #define AUX_DIR_SET   (PORTA_DIR |= AUX_IO_BIT)
                   #define AUX_PU_SET    (PORTA_PU  |= AUX_IO_BIT)
                   #define AUX_IN_CHECK  (PORTA_IN  &  AUX_IO_BIT)  	              
              #elif defined(support_line_chack_user_PA10) 
                   #define AUX_IO_BIT    BIT(10)
                   #define AUX_DIR_SET   (PORTA_DIR |= AUX_IO_BIT)
                   #define AUX_PU_SET    (PORTA_PU  |= AUX_IO_BIT)
                   #define AUX_IN_CHECK  (PORTA_IN  &  AUX_IO_BIT)  
              #elif defined(support_line_chack_user_ad) 
                   #define AUX_IO_BIT  
                   #define AUX_DIR_SET 
                   #define AUX_PU_SET   
                   #define AUX_IN_CHECK 
				   
              #else 
              #error("请设置	line det IO ")
              #endif 
#endif 
#if AUX_DGND_DETECT_EN
#ifdef AUX_DGND_DETECT_USE_PC11
#define AUX_IO_BIT	  BIT(11)
#define AUX_DIR_SET    (PORTC_DIR |= AUX_IO_BIT)
#define AUX_PU_SET	  (PORTC_PU  |= AUX_IO_BIT)
#define AUX_IN_CHECK   (PORTC_IN  &	AUX_IO_BIT)   
#elif defined(AUX_DGND_DETECT_USE_PB8)
#define AUX_IO_BIT	  BIT(8)
#define AUX_DIR_SET    (PORTB_DIR |= AUX_IO_BIT)
#define AUX_PU_SET	  (PORTB_PU  |= AUX_IO_BIT)
#define AUX_IN_CHECK   (PORTB_IN  &	AUX_IO_BIT)   
#else
#error("设置收音检测脚")
#endif

#endif

/*  耳机  检测   */

#ifdef PHONE_CHECK_ENABLE
#ifdef   support_phone_chack_user_PA9
	    #define PHONE_IO_BIT    BIT(9)
	    #define PHONE_DIR_SET   (PORTA_DIR |= PHONE_IO_BIT)
	    #define PHONE_PU_SET    (PORTA_PU  |= PHONE_IO_BIT)
	    #define PHONE_IN_CHECK  (PORTA_IN  &  PHONE_IO_BIT)  	
#else 
             #error("请设置耳机 det IO ")
#endif 
#endif 

#if FM_DGND_DETECT_EN
#ifdef FM_DGND_DETECT_USE_PC10
#define FM_IO_BIT	  BIT(10)
#define FM_DIR_SET    (PORTC_DIR |= FM_IO_BIT)
#define FM_PU_SET	  (PORTC_PU  |= FM_IO_BIT)
#define FM_PD_SET	  (PORTC_PD  &=~ FM_IO_BIT)
#define FM_IN_CHECK   (PORTC_IN  &	FM_IO_BIT)  
#elif defined(FM_DGND_DETECT_USE_PB6)
#define FM_IO_BIT	  BIT(6)
#define FM_DIR_SET    (PORTB_DIR |= FM_IO_BIT)
#define FM_PU_SET	  (PORTB_PU  |= FM_IO_BIT)
#define FM_PD_SET	  (PORTB_PD  &=~ FM_IO_BIT)
#define FM_IN_CHECK   (PORTB_IN  &	FM_IO_BIT)  
#elif defined(FM_DGND_DETECT_USE_PB7)
#define FM_IO_BIT	  BIT(7)
#define FM_DIR_SET    (PORTB_DIR |= FM_IO_BIT)
#define FM_PU_SET	  (PORTB_PU  |= FM_IO_BIT)
#define FM_PD_SET	  (PORTB_PD  &=~ FM_IO_BIT)
#define FM_IN_CHECK   (PORTB_IN  &	FM_IO_BIT)  
#else
#error("设置收音检测脚")
#endif

#endif
   
#if IR_SAME_SYSCODE_DETECT_EN
#ifdef IR_DETECT_USE_PB6
#define IR_IO_BIT	  BIT(6)
#define IR_DIR_SET    (PORTB_DIR |= IR_IO_BIT)
#define IR_DET_PU_SET	  (PORTB_PU  |= IR_IO_BIT)
#define IR_DET_PD_SET	  (PORTB_PD  &=~ IR_IO_BIT)
#define IR_DET_CHECK   (PORTB_IN  &	IR_IO_BIT)  
#endif
#endif

#if EXTERN_KOK_DETECT_USE_IO_EN
#ifndef KOK_DETECT_USE_IO_ADC_VALUE
  #ifdef KOK_DETECT_USE_PA4
#ifdef kok_det_low_hight_swap  
   #define KOK_DETECT_IO_IN() PORTA_DIR|=BIT(4);PORTA_PU|=BIT(4);PORTA_PD&=~BIT(4)
   #define KOK_IN_CHECK() (PORTA_IN&BIT(4))
   #else
   #define KOK_DETECT_IO_IN() PORTA_DIR|=BIT(4);PORTA_PU&=~BIT(4);PORTA_PD|=BIT(4)
   #define KOK_IN_CHECK() !(PORTA_IN&BIT(4))
   #endif
  #elif defined(KOK_DETECT_USE_PA6)
   #define KOK_DETECT_IO_IN() PORTA_DIR|=BIT(6);PORTA_PU&=~BIT(6);PORTA_PD|=BIT(6)
   #define KOK_IN_CHECK() !(PORTA_IN&BIT(6))
#elif defined(KOK_DETECT_USE_PB8)
 #define KOK_DETECT_IO_IN() PORTB_DIR|=BIT(8);PORTB_PU&=~BIT(8);PORTB_PD|=BIT(8)
 #define KOK_IN_CHECK() !(PORTB_IN&BIT(8))
#elif defined(KOK_DETECT_USE_PB7)
#ifdef kok_det_low_hight_swap  
   #define KOK_DETECT_IO_IN() PORTB_DIR|=BIT(7);PORTB_PU|=BIT(7);PORTB_PD&=~BIT(7)
   #define KOK_IN_CHECK() (PORTB_IN&BIT(7))
   #else
 #define KOK_DETECT_IO_IN() PORTB_DIR|=BIT(7);PORTB_PU&=~BIT(7);PORTB_PD|=BIT(7)
 #define KOK_IN_CHECK() !(PORTB_IN&BIT(7))
   #endif

#elif defined(KOK_DETECT_USE_PB6)
 #define KOK_DETECT_IO_IN() PORTB_DIR|=BIT(6);PORTB_PU|=BIT(6);PORTB_PD&=~BIT(6)
 #define KOK_IN_CHECK() (PORTB_IN&BIT(6)) 
#elif defined(KOK_DETECT_USE_PB9)
// LOW  ENABLE
   #define KOK_DETECT_IO_IN() PORTB_DIR|=BIT(9);PORTB_PU|=BIT(9);PORTB_PD&=~BIT(9)
   #define KOK_IN_CHECK() (PORTB_IN&BIT(9))
// HIGH ENABLE
//   #define KOK_DETECT_IO_IN() PORTB_DIR|=BIT(9);PORTB_PU&=~BIT(9);PORTB_PD|=BIT(9)
//   #define KOK_IN_CHECK() !(PORTB_IN&BIT(9))
   
#elif defined(KOK_DETECT_USE_PC15)
 #define KOK_DETECT_IO_IN() PORTC_DIR|=BIT(15);PORTC_PU&=~BIT(15);PORTC_PD|=BIT(15)
 #define KOK_IN_CHECK() !(PORTC_IN&BIT(15))
  #endif
#endif
#endif

/*  PP LED    */

#if LED_EN
     #ifdef PP_LED_USER_PB7
         #define LED_BIT                BIT(7)
         #define LED_INIT_EN()     {PORTB_PU &= ~LED_BIT;PORTB_PD &= ~LED_BIT;PORTB_DIR &= ~LED_BIT;}
         #define LED_INIT_DIS()    {PORTB_PU &= ~LED_BIT;PORTB_PD &= ~LED_BIT;PORTB_DIR |= LED_BIT;}
         #define B_LED_ON()          PORTB_OUT |= LED_BIT;
         #define B_LED_OFF()        PORTB_OUT &= ~LED_BIT;
     #elif defined(PP_LED_USER_PB6)	 
	 #define LED_BIT                BIT(6)
         #define LED_INIT_EN()     {PORTB_PU &= ~LED_BIT;PORTB_PD &= ~LED_BIT;PORTB_DIR &= ~LED_BIT;}
         #define LED_INIT_DIS()    {PORTB_PU &= ~LED_BIT;PORTB_PD &= ~LED_BIT;PORTB_DIR |= LED_BIT;}
         #define B_LED_ON()           PORTB_OUT |= LED_BIT;
         #define B_LED_OFF()         PORTB_OUT &= ~LED_BIT;
     #elif defined(PP_LED_USER_PB9)	 
	 #define LED_BIT                BIT(9)
         #define LED_INIT_EN()     {PORTB_PU &= ~LED_BIT;PORTB_PD &= ~LED_BIT;PORTB_DIR &= ~LED_BIT;}
         #define LED_INIT_DIS()    {PORTB_PU &= ~LED_BIT;PORTB_PD &= ~LED_BIT;PORTB_DIR |= LED_BIT;}
         #define B_LED_ON()           PORTB_OUT |= LED_BIT;
         #define B_LED_OFF()         PORTB_OUT &= ~LED_BIT;
		 
	#elif defined(PP_LED_USER_PA4)	
         #define LED_BIT                BIT(4)
         #define LED_INIT_EN()     {PORTA_PU &= ~LED_BIT;PORTA_PD &= ~LED_BIT;PORTA_DIR &= ~LED_BIT;}
         #define LED_INIT_DIS()    {PORTA_PU &= ~LED_BIT;PORTA_PD &= ~LED_BIT;PORTA_DIR |= LED_BIT;}
         #define B_LED_ON()           PORTA_OUT |= LED_BIT;
         #define B_LED_OFF()         PORTA_OUT &= ~LED_BIT;	 
     #elif defined(PP_LED_USER_PA6)	
         #define LED_BIT                BIT(6)
         #define LED_INIT_EN()     {PORTA_PU &= ~LED_BIT;PORTA_PD &= ~LED_BIT;PORTA_DIR &= ~LED_BIT;}
         #define LED_INIT_DIS()    {PORTA_PU &= ~LED_BIT;PORTA_PD &= ~LED_BIT;PORTA_DIR |= LED_BIT;}
         #define B_LED_ON()           PORTA_OUT |= LED_BIT;
         #define B_LED_OFF()         PORTA_OUT &= ~LED_BIT;
     #elif defined(PP_LED_USER_PA7)	
         #define LED_BIT                BIT(7)
         #define LED_INIT_EN()     {PORTA_PU &= ~LED_BIT;PORTA_PD &= ~LED_BIT;PORTA_DIR &= ~LED_BIT;}
         #define LED_INIT_DIS()    {PORTA_PU &= ~LED_BIT;PORTA_PD &= ~LED_BIT;PORTA_DIR |= LED_BIT;}
         #define B_LED_ON()           PORTA_OUT |= LED_BIT;
         #define B_LED_OFF()         PORTA_OUT &= ~LED_BIT;		 
     #elif defined(PP_LED_USER_PA8)	
         #define LED_BIT                BIT(8)
         #define LED_INIT_EN()     {PORTA_PU &= ~LED_BIT;PORTA_PD &= ~LED_BIT;PORTA_DIR &= ~LED_BIT;}
         #define LED_INIT_DIS()    {PORTA_PU &= ~LED_BIT;PORTA_PD &= ~LED_BIT;PORTA_DIR |= LED_BIT;}
         #define B_LED_ON()           PORTA_OUT |= LED_BIT;
         #define B_LED_OFF()         PORTA_OUT &= ~LED_BIT;
     #elif defined(PP_LED_USER_PA15)	
         #define LED_BIT                BIT(15)
         #define LED_INIT_EN()     {PORTA_PU &= ~LED_BIT;PORTA_PD &= ~LED_BIT;PORTA_DIR &= ~LED_BIT;}
         #define LED_INIT_DIS()    {PORTA_PU &= ~LED_BIT;PORTA_PD &= ~LED_BIT;PORTA_DIR |= LED_BIT;}
         #define B_LED_ON()           PORTA_OUT |= LED_BIT;
         #define B_LED_OFF()         PORTA_OUT &= ~LED_BIT;	
     #elif defined(PP_LED_USER_PA11)	
         #define LED_BIT                BIT(11)
         #define LED_INIT_EN()     {PORTA_PU &= ~LED_BIT;PORTA_PD &= ~LED_BIT;PORTA_DIR &= ~LED_BIT;}
         #define LED_INIT_DIS()    {PORTA_PU &= ~LED_BIT;PORTA_PD &= ~LED_BIT;PORTA_DIR |= LED_BIT;}
         #define B_LED_ON()           PORTA_OUT |= LED_BIT;
         #define B_LED_OFF()         PORTA_OUT &= ~LED_BIT;		
     #elif defined(PP_LED_USER_PA14)	
         #define LED_BIT                BIT(14)
         #define LED_INIT_EN()     {PORTA_PU &= ~LED_BIT;PORTA_PD &= ~LED_BIT;PORTA_DIR &= ~LED_BIT;}
         #define LED_INIT_DIS()    {PORTA_PU &= ~LED_BIT;PORTA_PD &= ~LED_BIT;PORTA_DIR |= LED_BIT;}
         #define B_LED_ON()           PORTA_OUT |= LED_BIT;
         #define B_LED_OFF()         PORTA_OUT &= ~LED_BIT;				 
     #else 
               #error("请设置	PP 灯IO ")
     #endif 	
#else
    #define LED_INIT_EN()     
    #define LED_INIT_DIS()    
    #define B_LED_ON()          
    #define B_LED_OFF()      
#endif 
#ifdef NEW_LED_SHOW_METHOD
#ifdef GW_827BT 
#define LED3_OFF()	{PORTB_OUT &=~ BIT(8);PORTB_PU &=~BIT(8);PORTB_PD |= BIT(8);PORTB_DIR &= ~BIT(8);}///COM1 BLUE
#define LED3_ON() 	{PORTB_OUT |= BIT(8);PORTB_PU |=BIT(8);PORTB_PD &=~ BIT(8);PORTB_DIR &= ~BIT(8);}
#define LED2_OFF()	{PORTB_OUT &=~ BIT(7);PORTB_PU &=~BIT(7);PORTB_PD |= BIT(7);PORTB_DIR &= ~BIT(7);}//COM2 GREEN
#define LED2_ON() 	{PORTB_OUT |= BIT(7);PORTB_PU |=BIT(7);PORTB_PD &=~ BIT(7);PORTB_DIR &= ~BIT(7);}
#define LED1_OFF()	{PORTB_OUT &=~ BIT(6);PORTB_PU &=~BIT(6);PORTB_PD |= BIT(6);PORTB_DIR &= ~BIT(6);}//COM3 RED
#define LED1_ON() 	{PORTB_OUT |= BIT(6);PORTB_PU |=BIT(6);PORTB_PD &=~ BIT(6);PORTB_DIR &= ~BIT(6);}
#define LED4_ON()	{PORTA_OUT &=~ BIT(4);PORTA_PU &=~BIT(4);PORTA_PD |= BIT(4);PORTA_DIR &= ~BIT(4);LED_STATUS|=LED_BT;}//BLUE LIGHT
#define LED4_OFF() 	{PORTA_OUT |= BIT(4);PORTA_PU |=BIT(4);PORTA_PD &=~ BIT(4);PORTA_DIR &= ~BIT(4);LED_STATUS&=~LED_BT;}  
#elif defined(SL_AC4601_V10)||defined(GW_310T_BT_AC4601)
#define LED1_ON()	{PORTA_OUT &=~ BIT(4);PORTA_PU &=~BIT(4);PORTA_PD |= BIT(4);PORTA_DIR &= ~BIT(4);}//BLUE LIGHT
#define LED1_OFF() 	{PORTA_OUT |= BIT(4);PORTA_PU |=BIT(4);PORTA_PD &=~ BIT(4);PORTA_DIR &= ~BIT(4);}  
#elif defined(SS_003M_AC4601)
#define LED1_OFF()	{PORTA_OUT &=~ BIT(4);PORTA_PU &=~BIT(4);PORTA_PD |= BIT(4);PORTA_DIR &= ~BIT(4);}//BLUE LIGHT
#define LED1_ON() 	{PORTA_OUT |= BIT(4);PORTA_PU |=BIT(4);PORTA_PD &=~ BIT(4);PORTA_DIR &= ~BIT(4);}  
#elif defined(TY_4601_Z)||defined(SW013_K1759_AC4601_V10)
#define LED1_OFF()	{PORTA_OUT &=~ BIT(6);PORTA_PU &=~BIT(6);PORTA_PD |= BIT(6);PORTA_DIR &= ~BIT(6);}//BLUE LIGHT
#define LED1_ON() 	{PORTA_OUT |= BIT(6);PORTA_PU |=BIT(6);PORTA_PD &=~ BIT(6);PORTA_DIR &= ~BIT(6);}  
#elif defined(TF_2008A)||defined(TF_DY015_AC46)||defined(TF_2025A)
#define LED1_OFF()	{PORTA_OUT &=~ BIT(4);PORTA_PU &=~BIT(4);PORTA_PD |= BIT(4);PORTA_DIR &= ~BIT(4);}//BLUE LIGHT
#define LED1_ON() 	{PORTA_OUT |= BIT(4);PORTA_PU |=BIT(4);PORTA_PD &=~ BIT(4);PORTA_DIR &= ~BIT(4);}  
#define LED2_ON()   LED_STATUS|=LED_BT
#define LED2_OFF()  LED_STATUS&=~LED_BT
#elif defined(GW_216BT_AC4601)
	 #define LED1_OFF()	{PORTB_OUT &=~ BIT(7);PORTB_PU &=~BIT(7);PORTB_PD |= BIT(7);PORTB_DIR &= ~BIT(7);}//COM2 GREEN
	 #define LED1_ON() 	{PORTB_OUT |= BIT(7);PORTB_PU |=BIT(7);PORTB_PD &=~ BIT(7);PORTB_DIR &= ~BIT(7);}
#elif defined(NTQ_K1724_AC4601_V10)||defined(ZY_3058B_AC4601_BT_V10)||defined(ZY_3058B_AC4601_BT_CY_V10)\
      ||defined(ZY_3058B_AC4601_BT_CY_V10_1)||defined(NTQ_K1737_AC4601_V10)||defined(HW_HD09_AC4601)\
      ||defined(ZY_5011AMP_V10_AC4601)||defined(ZY_5011AMP_MIN_V10_AC4601)||defined(ZY_3058B_AC4601_SDX8812_LED)\
      ||defined(ZY_3058A_YG_AC4601)||defined(ZY_5011B_SUOAI01_AC4601)||defined(ZY_3058_3608_JC_AC4601)\
      ||defined(ZY_3058B_4018_LS_AC4601)||defined(ZY_3058B_4018_LS_NOFM_AC4601)||defined(ZY_3058A_REC_YG_AC4601)\
      ||defined(ZY_3058_3608_Bluetooth_DMWN_AC4601)||defined(ZY_5011B_SANMU01_AC4601)||defined(ZY_3058B_88N48_AC4601)\
      ||defined(ZY_3058A_BT_BLUETOOTH_LX_AC4601)||defined(ZY_3058_4018_LS_XSPFJ)||defined(ZY_3058A_88N48_AC4601)\
       ||defined(ZY_3058B_88N48_LS_AC4601) ||defined(ZY_3058A_YH_AC4601)||defined(ZY_3058_4018_LS_VOICE)||defined(ZY_5011C_SANMU02_AC4601)\
       ||defined(ZY_3058B_BT_TK_AC4601) ||defined(ZY_3058A_BT_HY_AC4601)  ||defined(ZY_3058B_8812_OB_AC4601) \
         ||defined(ZY_5011_WB01_AC4601) ||defined(ZY_3058B_OB_8426_AC4601)||defined(ZY_3058B_ZF_AC4601)||defined(ZY_5011C_NOREC_4018_AC4601)\
         ||defined(ZY_5011C_NOREC_88N48_AC4601)  ||defined(ZY_3058A_88N48_NOAUX_AC4601)||defined(HX_L158USB_REC_AC4601)\
          ||defined(ZY_5011C_NOREC_88N48_HX_AC4601) ||defined(ZY_3058B_40N18_KIPTECH_AC4601)  ||defined(ZY_5011C_4018_B_AC4601) \
           ||defined(ZY_3058B_4018_2REC_AC4601)||defined(ZY_3058_JW_8426C7_1B_AC4601)||defined(ZY_5011C_4018_D_AC4601)\
        ||defined(ZY_5011C_88N48_C_NOREC_AC4601)   ||defined(ZY_5011C_NOREC_JW4018D_AC4601) ||defined(ZY_3058A_BT_JUNSHENG_AC4601) \     
         ||defined(ZY_3058_4018_LS_REC_AC4601) ||defined(ZY_3058B_JW54627_1BB_AC4601) ||defined(ZY_3058B_JW_4018D71B_AC4601) \
          ||defined(ZY_3058B_88N48_LS_NOREC_AC4601) ||defined(ZY_3058B_4018_BLUC_AC4601)||defined(ZY_3058B_4018_LS_BT_AC4601)\
          ||defined(ZY_3058B_4018_LS_BT_NOAUX_AC4601) ||defined(ZY_3058A_88N48_NOP_AC4601)
	 #define LED2_OFF()	{PORTB_OUT &=~ BIT(7);PORTB_PU &=~BIT(7);PORTB_PD |= BIT(7);PORTB_DIR &= ~BIT(7);}//COM2 GREEN
	 #define LED2_ON() 	{PORTB_OUT |= BIT(7);PORTB_PU |=BIT(7);PORTB_PD &=~ BIT(7);PORTB_DIR &= ~BIT(7);}
	 #define LED1_OFF()	{PORTB_OUT &=~ BIT(6);PORTB_PU &=~BIT(6);PORTB_PD |= BIT(6);PORTB_DIR &= ~BIT(6);}//COM3 RED
	 #define LED1_ON() 	{PORTB_OUT |= BIT(6);PORTB_PU |=BIT(6);PORTB_PD &=~ BIT(6);PORTB_DIR &= ~BIT(6);}
#elif defined(ZY_3058_AC4602)||defined(ZX_K1722_AC4602_V10)||defined(GW_805B_806B_AC4602)||defined(ZY_3080A_B_BT_AC4602)\
      ||defined(TF_2010_BTL_AC4602)||defined(HC_HT603BT_K1733_AC4602)||defined(GW_805B_806B_AC4602_PCB_SAME_AS_ZY)\
      ||defined(ZX_K1722_AC4602_V10_ZY_ADK_RESISTENCE)||defined(ZY_3080A_B_BT_CY_AC4602)||defined(SL_SP61_AC4602)\
      ||defined(GW_BT01_AC4602)||defined(ZX_602YG_K1722_AC4602_V10)||defined(ZX_HL18_K1755_AC4602_V10)\
      ||defined(ZX_K1757_AC4602_V10)||defined(ZY_3088_CY_AC4602)||defined(ZY_3088B_XH_AC4602)||defined(ZY_5018_SG_AC4602)\
      ||defined(ZY_5015_SG_AC4602)||defined(JH_K1789_AC4602)||defined(ZX_HL602UD_V10_AC4602_KOK_PRIORY)
#define LED1_OFF()	{PORTA_OUT &=~ BIT(11);PORTA_PU &=~BIT(11);PORTA_PD |= BIT(11);PORTA_DIR &= ~BIT(11);}//BLUE LIGHT
#define LED1_ON() 	{PORTA_OUT |= BIT(11);PORTA_PU |=BIT(11);PORTA_PD &=~ BIT(11);PORTA_DIR &= ~BIT(11);}  
#elif defined(ZY_3088_MM_AC4602)
#define LED1_OFF()	{PORTA_OUT &=~ BIT(11);PORTA_PU &=~BIT(11);PORTA_PD |= BIT(11);PORTA_DIR &= ~BIT(11);}//BLUE LIGHT
#define LED1_ON() 	{PORTA_OUT |= BIT(11);PORTA_PU |=BIT(11);PORTA_PD &=~ BIT(11);PORTA_DIR &= ~BIT(11);}  
#define LED2_OFF()	{PORTA_OUT &=~ BIT(10);PORTA_PU &=~BIT(10);PORTA_PD |= BIT(10);PORTA_DIR &= ~BIT(10);}//BLUE LIGHT
#define LED2_ON() 	{PORTA_OUT |= BIT(10);PORTA_PU |=BIT(10);PORTA_PD &=~ BIT(10);PORTA_DIR &= ~BIT(10);}  

#elif defined(ZY_6401LCD_AC4601)

//#define LED2_OFF()	{PORTC_OUT &=~ BIT(11);PORTC_PU &=~BIT(11);PORTC_PD |= BIT(11);PORTC_DIR &= ~BIT(11);}//BLUE LIGHT
//#define LED2_ON() 	{PORTC_OUT |= BIT(11);PORTC_PU |=BIT(11);PORTC_PD &=~ BIT(11);PORTC_DIR &= ~BIT(11);}  
#define LED1_OFF()	{PORTC_OUT &=~ BIT(10);PORTC_PU &=~BIT(10);PORTC_PD |= BIT(10);PORTC_DIR &= ~BIT(10);}//BLUE LIGHT
#define LED1_ON() 	{PORTC_OUT |= BIT(10);PORTC_PU |=BIT(10);PORTC_PD &=~ BIT(10);PORTC_DIR &= ~BIT(10);}  

#elif defined(ZY_Q5_BTL_V10_K1730_SEC_LCD)||defined(SM_SM006A_V2_AC4601)||defined(ZY_3016_REC_AC4601_V10)||defined(SM_SM004B_AC4601)\
      ||defined(SM_D300A_AC4601)||defined(GW_004_BT_AC4601)
#define LED1_ON()   LED_STATUS|=LED_BT
#define LED1_OFF()  LED_STATUS&=~LED_BT
#elif defined(MSJ_K1734_VFD35_AC4601)||defined(SSM_HS_T18W1_1_K1725_8426_AC4601)||defined(ZY_3096_HL_Q1_AC4601)
#define LED1_OFF()	{PORTC_OUT &=~ BIT(10);PORTC_PU &=~BIT(10);PORTC_PD |= BIT(10);PORTC_DIR &= ~BIT(10);}//COM3 RED
#define LED1_ON() 	{PORTC_OUT |= BIT(10);PORTC_PU |=BIT(10);PORTC_PD &=~ BIT(10);PORTC_DIR &= ~BIT(10);}
#elif defined(ZY_3096_AC4601_V10)||defined(ZY_3096_XH_V10_AC4601)||defined(ZY_3096_YS3608_V10_AC4601)||defined(ZY_3096_SEVEN_8NUM_LED)\
      ||defined(ZY_3096_LT_AC4601)
#define LED1_OFF()	{PORTC_OUT &=~ BIT(11);PORTC_PU &=~BIT(11);PORTC_PD |= BIT(11);PORTC_DIR &= ~BIT(11);}//COM3 RED
#define LED1_ON() 	{PORTC_OUT |= BIT(11);PORTC_PU |=BIT(11);PORTC_PD &=~ BIT(11);PORTC_DIR &= ~BIT(11);}
#elif defined(ZX_601LR_AC4601_V10)||defined(ZX_601LR_BL_AC4601)||defined(ZX_601P_AC4601_V10)||defined(ZX_HY601LR_SDX4018N_2_AC4601_V10)
#define LED2_OFF()	{PORTB_OUT &=~ BIT(10);PORTB_PU &=~BIT(10);PORTB_PD |= BIT(10);PORTB_DIR &= ~BIT(10);}//COM2 GREEN
#define LED2_ON() 	{PORTB_OUT |= BIT(10);PORTB_PU |=BIT(10);PORTB_PD &=~ BIT(10);PORTB_DIR &= ~BIT(10);}
#define LED1_OFF()	{PORTA_OUT &=~ BIT(0);PORTA_PU &=~BIT(0);PORTA_PD |= BIT(0);PORTA_DIR &= ~BIT(0);LED2_OFF();}//BLUE LIGHT
#define LED1_ON() 	{PORTA_OUT |= BIT(0);PORTA_PU |=BIT(0);PORTA_PD &=~ BIT(0);PORTA_DIR &= ~BIT(0);LED2_ON();}  


#elif defined(ZX_601LR_AC4601_V10_YUNKE)
#define LED1_OFF()	{PORTA_OUT &=~ BIT(0);PORTA_PU &=~BIT(0);PORTA_PD |= BIT(0);PORTA_DIR &= ~BIT(0);}//BLUE LIGHT
#define LED1_ON() 	{PORTA_OUT |= BIT(0);PORTA_PU |=BIT(0);PORTA_PD &=~ BIT(0);PORTA_DIR &= ~BIT(0);}  
#define LED2_OFF()	{PORTA_OUT &=~ BIT(10);PORTA_PU &=~BIT(10);PORTA_PD |= BIT(10);PORTA_DIR &= ~BIT(10); } //COM2 GREEN
#define LED2_ON() 	{PORTA_OUT |= BIT(10);PORTA_PU |=BIT(10);PORTA_PD &=~ BIT(10);PORTA_DIR &= ~BIT(10); }

#elif defined(SM_4003_V1_AC4603)||defined(SSM_K1729_AC4603)
//#define LED1_OFF()	{PORTA_OUT &=~ BIT(14);PORTA_PU &=~BIT(14);PORTA_PD |= BIT(14);PORTA_DIR &= ~BIT(14);}//BLUE LIGHT
//#define LED1_ON() 	{PORTA_OUT |= BIT(14);PORTA_PU |=BIT(14);PORTA_PD &=~ BIT(14);PORTA_DIR &= ~BIT(14);}  
#define LED1_OFF()	{PORTC_OUT &=~ BIT(15);PORTC_PU &=~BIT(15);PORTC_PD |= BIT(15);PORTC_DIR &= ~BIT(15);}//BLUE LIGHT
#define LED1_ON() 	{PORTC_OUT |= BIT(15);PORTC_PU |=BIT(15);PORTC_PD &=~ BIT(15);PORTC_DIR &= ~BIT(15);}  
#elif defined(MSJ_K1739_V10_AC4601)||defined(SSM_Q6_K1725_AC4601)||defined(K1725_AC461_V10)||defined(SSM_SF_K1725_AC4601)\
	||defined(SSM_K1725_PANEL_AL221_AC4601_V10)||defined(JH_001_REC_K1725_AC4601)||defined(JH_002_REC_K1725_AC4601)\
	||defined(SSM_Q535_AC461_V10) ||defined(SSM_Q535_2REC_AC461_V10)||defined(SSM_Q535B_AC461_V10)||defined(SSM_Q535_78_AC461_V10)\
	||defined(SSM_Q535_DBL_AC461_V10) ||defined(SSM_Q535_8426_NOAUX_AC461)||defined(SSM_Q538_2PANEL_AC4601)||defined(ZX_HL601_QGN_2314_AC4601)\
	||defined(ZY_3112_88N48_AC4601) ||defined(SSM_Q535_4052_AC461)||defined(SSM_Q535_VOICE_AC4601)\
	||defined(SSM_Q535_OPTI_04FB_AC4601)||defined(SSM_Q535_8426_04FB_AC461)||defined(SSM_Q535B_4018_04FB_AC461) \
	||defined(SSM_Q535B_4018_INTRO_04FB_AC461)  ||defined(LH_QH_01_AC4601)   ||defined(SSM_Q535B_4018_04FB_VOICE_AC461)  \
	||defined(SSM_Q535_DBL_4018_AC461)  ||defined(SSM_Q535B_4018_SA_AC461) ||defined(SSM_Q18_8426_04FB_AC4601) \
	||defined(SSM_Q535_8426_04FB_B_AC461)  ||defined(SSM_Q535_OPTI_04FB_8426_AC4601)  ||defined(SSM_Q535B_4018_04FB_NOBT_AC461) \
	||defined(SSM_Q535_DBL_4018_NOAUX_AC461) ||defined(SSM_Q535_DBL_4018_6VIOCE_AC461)
     
#define LED1_OFF()	{PORTB_OUT &=~ BIT(10);PORTB_PU &=~BIT(10);PORTB_PD |= BIT(10);PORTB_DIR &= ~BIT(10);}//COM2 GREEN
#define LED1_ON() 	{PORTB_OUT |= BIT(10);PORTB_PU |=BIT(10);PORTB_PD &=~ BIT(10);PORTB_DIR &= ~BIT(10);}

#elif defined(SSM_Q535B_4018_04FB_DLED_AC461)

#define LED1_OFF()	{PORTB_OUT &=~ BIT(10);PORTB_PU &=~BIT(10);PORTB_PD |= BIT(10);PORTB_DIR &= ~BIT(10);}//COM2 GREEN
#define LED1_ON() 	{PORTB_OUT |= BIT(10);PORTB_PU |=BIT(10);PORTB_PD &=~ BIT(10);PORTB_DIR &= ~BIT(10);}
#define LED2_OFF()	{PORTB_OUT &=~ BIT(9);PORTB_PU &=~BIT(9);PORTB_PD |= BIT(9);PORTB_DIR &= ~BIT(9);}///green
#define LED2_ON() 	{PORTB_OUT |= BIT(9);PORTB_PU |=BIT(9);PORTB_PD &=~ BIT(9);PORTB_DIR &= ~BIT(9);}

#elif defined(GW_011_AC4601)||defined(TEST_JL_V13_SOFTWARE)||defined(GW_1015_AC4601)
#define LED1_OFF()	{PORTB_OUT &=~ BIT(8);PORTB_PU &=~BIT(8);PORTB_PD |= BIT(8);PORTB_DIR &= ~BIT(8);}///COM1 BLUE
#define LED1_ON() 	{PORTB_OUT |= BIT(8);PORTB_PU |=BIT(8);PORTB_PD &=~ BIT(8);PORTB_DIR &= ~BIT(8);}
#elif defined(DJ_AC4601D_AC4601)||defined(DJ_AC4601E_AC4601)
#define LED1_OFF()	{PORTB_OUT &=~ BIT(10);PORTB_PU &=~BIT(10);PORTB_PD |= BIT(10);PORTB_DIR &= ~BIT(10);}//red 
#define LED1_ON() 	{PORTB_OUT |= BIT(10);PORTB_PU |=BIT(10);PORTB_PD &=~ BIT(10);PORTB_DIR &= ~BIT(10);}
#define LED2_OFF()	{PORTB_OUT &=~ BIT(8);PORTB_PU &=~BIT(8);PORTB_PD |= BIT(8);PORTB_DIR &= ~BIT(8);}///green
#define LED2_ON() 	{PORTB_OUT |= BIT(8);PORTB_PU |=BIT(8);PORTB_PD &=~ BIT(8);PORTB_DIR &= ~BIT(8);}
#define LED3_OFF()	{PORTB_OUT &=~ BIT(7);PORTB_PU &=~BIT(7);PORTB_PD |= BIT(7);PORTB_DIR &= ~BIT(7);}///blue
#define LED3_ON() 	{PORTB_OUT |= BIT(7);PORTB_PU |=BIT(7);PORTB_PD &=~ BIT(7);PORTB_DIR &= ~BIT(7);}
//#define LIGHT_IO_INIT() PORTB_DIR &= ~(BIT(10)|BIT(8)|BIT(7));PORTB_PU|= (BIT(10)|BIT(8)|BIT(7))
//#define LIGHT_01(x) if(x) PORTB_OUT|= BIT(10); else PORTB_OUT&=~ BIT(10) //red
//#define LIGHT_02(x) if(x) PORTB_OUT|= BIT(8); else PORTB_OUT&=~ BIT(8) //green
//#define LIGHT_03(x) if(x) PORTB_OUT|= BIT(7); else PORTB_OUT&=~ BIT(7) //blue
#define LED4_OFF()	{PORTB_OUT &=~ BIT(6);PORTB_PU &=~BIT(6);PORTB_PD |= BIT(6);PORTB_DIR &= ~BIT(6);}//led
#define LED4_ON() 	{PORTB_OUT |= BIT(6);PORTB_PU |=BIT(6);PORTB_PD &=~ BIT(6);PORTB_DIR &= ~BIT(6);}
#elif defined(FS_K88_AC4602)
#define LED1_OFF()	{PORTA_OUT &=~ BIT(14);PORTA_PU &=~BIT(14);PORTA_PD |= BIT(14);PORTA_DIR &= ~BIT(14);}//BLUE LIGHT
#define LED1_ON() 	{PORTA_OUT |= BIT(14);PORTA_PU |=BIT(14);PORTA_PD &=~ BIT(14);PORTA_DIR &= ~BIT(14);}  
#elif defined(WTW_WT16450_AC4603)
#define LED1_ON()	{PORTA_OUT &=~ BIT(14);PORTA_PU &=~BIT(14);PORTA_PD |= BIT(14);PORTA_DIR &= ~BIT(14);}//BLUE LIGHT
#define LED1_OFF() 	{PORTA_OUT |= BIT(14);PORTA_PU |=BIT(14);PORTA_PD &=~ BIT(14);PORTA_DIR &= ~BIT(14);}  

#elif defined(GW_020_GZY_REC_AC4601)
#ifdef GW_020L_AC4601
#define LED1_OFF()	{PORTA_OUT &=~ BIT(15);PORTA_PU &=~BIT(15);PORTA_PD |= BIT(15);PORTA_DIR &= ~BIT(15);}///COM1 BLUE
#define LED1_ON() 	{PORTA_OUT |= BIT(15);PORTA_PU |=BIT(15);PORTA_PD &=~ BIT(15);PORTA_DIR &= ~BIT(15);}
#else
#define LED1_OFF()	{PORTB_OUT &=~ BIT(8);PORTB_PU &=~BIT(8);PORTB_PD |= BIT(8);PORTB_DIR &= ~BIT(8);}///COM1 BLUE
#define LED1_ON() 	{PORTB_OUT |= BIT(8);PORTB_PU |=BIT(8);PORTB_PD &=~ BIT(8);PORTB_DIR &= ~BIT(8);}
#endif

#elif defined(ZY_4602_SP_LED_AC4601) 
#define LED1_ON()	{PORTA_OUT &=~ BIT(0);PORTA_PU &=~BIT(0);PORTA_PD |= BIT(0);PORTA_DIR &= ~BIT(0);}//BLUE LIGHT
#define LED1_OFF() 	{PORTA_OUT |= BIT(0);PORTA_PU |=BIT(0);PORTA_PD &=~ BIT(0);PORTA_DIR &= ~BIT(0);}  

#elif defined(ZY_3058B_7G8_HD6992_AC4601)||defined(ZY_3058B_7G8_REC_AC4601)||defined(ZY_3058B_LS_7G8_C_AC4601)\
	||defined(ZY_3058B_7G8_JS_REC_AC4601)||defined(ZY_3096BT_7G8_AC4601)||defined(ZY_3058B_7G8_BLUC_AC4601)
#define LED1_OFF()	{PORTB_OUT &=~ BIT(6);PORTB_PU &=~BIT(6);PORTB_PD |= BIT(6);PORTB_DIR &= ~BIT(6);}///COM1 BLUE
#define LED1_ON() 	{PORTB_OUT |= BIT(6);PORTB_PU |=BIT(6);PORTB_PD &=~ BIT(6);PORTB_DIR &= ~BIT(6);}
#elif defined(XF_01_REC_AC4602)
#define LED1_OFF()	{PORTA_OUT &=~ BIT(14);PORTA_PU &=~BIT(14);PORTA_PD |= BIT(14);PORTA_DIR &= ~BIT(14);}//BLUE LIGHT
#define LED1_ON() 	{PORTA_OUT |= BIT(14);PORTA_PU |=BIT(14);PORTA_PD &=~ BIT(14);PORTA_DIR &= ~BIT(14);}  
#define LED2_OFF()	{PORTA_OUT &=~ BIT(11);PORTA_PU &=~BIT(11);PORTA_PD |= BIT(11);PORTA_DIR &= ~BIT(11);}//BLUE LIGHT
#define LED2_ON() 	{PORTA_OUT |= BIT(11);PORTA_PU |=BIT(11);PORTA_PD &=~ BIT(11);PORTA_DIR &= ~BIT(11);}  
#elif defined(ZY_5017_SG_AC4601)||defined(ZY_5021_SG_AC4601)||defined(ZY_5028_tm1628_AC4601)\
	||defined(ZY_5021_MX_SG_AC4601)||defined(LTDQ_ZY5021_AC4601)||defined(LTDQ_MX_303_AC4601)\
	||defined(LTDQ_MX_177505_AC4601)||defined(ZY_5028_TM1628_HD7369_D_AC4601)||defined(ZY_5028_TM1628_HD7369_C_AC4601)
#if  defined LTDQ_ZY5021_RGB_AC4601 ||defined(LTDQ_MX_177505_AC4601)||defined(LTDQ_MX_303_AC4601)

#define LED1_OFF()
#define LED1_ON() 

#else
#define LED1_OFF()	{PORTA_OUT &=~ BIT(15);PORTA_PU &=~BIT(15);PORTA_PD |= BIT(15);PORTA_DIR &= ~BIT(15);}//BLUE LIGHT
#define LED1_ON() 	{PORTA_OUT |= BIT(15);PORTA_PU |=BIT(15);PORTA_PD &=~ BIT(15);PORTA_DIR &= ~BIT(15);}  
#endif
#endif
#endif

   
// mute 
#ifdef support_amp_power_control
 #ifdef USE_PA14_CONTROL_AMP_POWER
  #define AMP_POWER_ONOFF(x) if(x){PORTA_OUT |= BIT(14);PORTA_PU |=BIT(14);PORTA_PD &=~ BIT(14);PORTA_DIR &= ~BIT(14);}else{PORTA_OUT &=~ BIT(14);PORTA_PU &=~BIT(14);PORTA_PD |= BIT(14);PORTA_DIR &= ~BIT(14);}
 #elif defined(USE_PB10_CONTROL_AMP_POWER)
   #define AMP_POWER_ONOFF(x) if(x){PORTB_OUT |= BIT(10);PORTB_PU |=BIT(10);PORTB_PD &=~ BIT(10);PORTB_DIR &= ~BIT(10);}else{PORTB_OUT &=~ BIT(10);PORTB_PU &=~BIT(10);PORTB_PD |= BIT(10);PORTB_DIR &= ~BIT(10);}
 #elif defined(USE_PB7_CONTROL_AMP_POWER)
   #define AMP_POWER_ONOFF(x) if(x){PORTB_OUT |= BIT(7);PORTB_PU |=BIT(7);PORTB_PD &=~ BIT(7);PORTB_DIR &= ~BIT(7);}else{PORTB_OUT &=~ BIT(7);PORTB_PU &=~BIT(7);PORTB_PD |= BIT(7);PORTB_DIR &= ~BIT(7);}
 #endif
#endif

 #ifdef support_low_power_use_extern_io
#ifdef support_low_power_io_pb9
   #define low_power_onoff(x) if(x){PORTB_OUT |= BIT(9);PORTB_PU |=BIT(9);PORTB_PD &=~ BIT(9);PORTB_DIR &= ~BIT(9);}else{PORTB_OUT &=~ BIT(9);PORTB_PU &=~BIT(9);PORTB_PD |= BIT(9);PORTB_DIR &= ~BIT(9);}
 #elif defined(support_low_power_io_pc10)
   #define low_power_onoff(x) if(x){PORTC_OUT |= BIT(10);PORTC_PU |=BIT(10);PORTC_PD &=~ BIT(10);PORTC_DIR &= ~BIT(10);}else{PORTC_OUT &=~ BIT(10);PORTC_PU &=~BIT(10);PORTC_PD |= BIT(10);PORTC_DIR &= ~BIT(10);}
 #elif defined(support_low_power_io_pb6)
   #define low_power_onoff(x) if(x){PORTB_OUT |= BIT(6);PORTB_PU |=BIT(6);PORTB_PD &=~ BIT(6);PORTB_DIR &= ~BIT(6);}else{PORTB_OUT &=~ BIT(6);PORTB_PU &=~BIT(6);PORTB_PD |= BIT(6);PORTB_DIR &= ~BIT(6);}
 #elif defined(support_low_power_io_pb7)
   #define low_power_onoff(x) if(x){PORTB_OUT |= BIT(7);PORTB_PU |=BIT(7);PORTB_PD &=~ BIT(7);PORTB_DIR &= ~BIT(7);}else{PORTB_OUT &=~ BIT(7);PORTB_PU &=~BIT(7);PORTB_PD |= BIT(7);PORTB_DIR &= ~BIT(7);}
#endif
#endif

#ifdef AMP_IC_WORK_ONFF
#ifdef USE_PB7_CONTROL_AMP_POWER
#define Set_amp_power_out()		   PORTB_DIR &= ~BIT(7); PORTB_PU |= BIT(7) 
#define Set_AMP_OFF()				   PORTB_OUT &= ~BIT(7) 
#define Set_AMP_ON()				   PORTB_OUT|= BIT(7)
#else
#define Set_amp_power_out()		   PORTB_DIR &= ~BIT(9); PORTB_PU |= BIT(9) 
#define Set_AMP_OFF()				   PORTB_OUT &= ~BIT(9) 
#define Set_AMP_ON()				   PORTB_OUT|= BIT(9)
#endif
#endif


#if PA_EN

        #ifdef suppoet_mute_user_PD1
        
        
            #define set_mute_io_is_out()         PORTD_DIR &= ~BIT(1)	
            #define set_mute_io_high()            PORTD_OUT |= BIT(1)          
            #define set_mute_io_low()             PORTD_OUT &= ~BIT(1)    
        
        #elif defined( suppoet_mute_user_PD0)
        
        
            #define set_mute_io_is_out()         PORTD_DIR &= ~BIT(0)	
            #define set_mute_io_high()            PORTD_OUT |= BIT(0)          
            #define set_mute_io_low()             PORTD_OUT &= ~BIT(0)        
        	
        #elif defined(suppoet_mute_user_PA6)
        
        
            #define set_mute_io_is_out()      PORTA_DIR &= ~BIT(6)	
            #define set_mute_io_high()        PORTA_OUT |= BIT(6)          
            #define set_mute_io_low()         PORTA_OUT &= ~BIT(6) 
        #elif defined(suppoet_mute_user_PA4)
										
			#define set_mute_io_is_out()	  PORTA_DIR &= ~BIT(4)	
			#define set_mute_io_high()		  PORTA_OUT |= BIT(4)		   
			#define set_mute_io_low()		  PORTA_OUT &= ~BIT(4) 
        #elif defined(suppoet_mute_user_PA7)
        
            #define set_mute_io_is_out()      PORTA_DIR &= ~BIT(7)	
            #define set_mute_io_high()        PORTA_OUT |= BIT(7)          
            #define set_mute_io_low()         PORTA_OUT &= ~BIT(7)     
        
          #elif defined(suppoet_mute_user_PA13)
        
            #define set_mute_io_is_out()      PORTA_DIR &= ~BIT(13)	
            #define set_mute_io_high()        PORTA_OUT |= BIT(13)          
            #define set_mute_io_low()         PORTA_OUT &= ~BIT(13)     
         #elif defined(suppoet_mute_user_PA14)
         			
           #define set_mute_io_is_out()		PORTA_DIR &= ~BIT(14) 
           #define set_mute_io_high()		PORTA_OUT |= BIT(14)		  
           #define set_mute_io_low() 		PORTA_OUT &= ~BIT(14)	  
         #elif defined(suppoet_mute_user_PA15)
         					  
           #define set_mute_io_is_out()	   PORTA_DIR &= ~BIT(15) 
           #define set_mute_io_high()	   PORTA_OUT |= BIT(15) 		 
           #define set_mute_io_low() 	   PORTA_OUT &= ~BIT(15)	 
        #elif defined(suppoet_mute_user_PB11)
        
            #define set_mute_io_is_out()      PORTB_DIR &= ~BIT(11)	
            #define set_mute_io_high()        PORTB_OUT |= BIT(11)          
            #define set_mute_io_low()         PORTB_OUT &= ~BIT(11)     
        
        #elif defined(suppoet_mute_user_PB1)
        
            #define set_mute_io_is_out()      PORTB_DIR &= ~BIT(1)	
            #define set_mute_io_high()        PORTB_OUT |= BIT(1)          
            #define set_mute_io_low()         PORTB_OUT &= ~BIT(1)     	
	 #elif defined(suppoet_mute_user_PB10)
        
            #define set_mute_io_is_out()      PORTB_DIR &= ~BIT(10)	
            #define set_mute_io_high()        PORTB_OUT |= BIT(10)          
            #define set_mute_io_low()         PORTB_OUT &= ~BIT(10)  
			
     #elif defined(suppoet_mute_user_PB6)
     			   
     	   #define set_mute_io_is_out() 	 PORTB_DIR &= ~BIT(6) 
     	   #define set_mute_io_high()		 PORTB_OUT |= BIT(6)		   
     	   #define set_mute_io_low()		 PORTB_OUT &= ~BIT(6)		   
    #elif defined(suppoet_mute_user_PB8)
    						 
    	  #define set_mute_io_is_out()		PORTB_DIR &= ~BIT(8) 
    	  #define set_mute_io_high()		PORTB_OUT |= BIT(8) 		  
    	  #define set_mute_io_low() 		PORTB_OUT &= ~BIT(8)		  
        #elif defined(suppoet_mute_user_PB14)
        
            #define set_mute_io_is_out()      PORTB_DIR &= ~BIT(14)	
            #define set_mute_io_high()        PORTB_OUT |= BIT(14)          
            #define set_mute_io_low()         PORTB_OUT &= ~BIT(14)  
         #elif defined(suppoet_mute_user_PB15)
        
            #define set_mute_io_is_out()      PORTB_DIR &= ~BIT(15)	
            #define set_mute_io_high()        PORTB_OUT |= BIT(15)          
            #define set_mute_io_low()         PORTB_OUT &= ~BIT(15)     
         #elif defined(pa_mute_use_pin_PC11)
         
            #define  set_mute_io_is_out()        PORTC_DIR &= ~BIT(11)
            #define  set_mute_io_high()       PORTC_OUT|= BIT(11)
            #define  set_mute_io_low()        PORTC_OUT &= ~BIT(11)   
         #elif defined(suppoet_mute_user_PC14)         
            #define  set_mute_io_is_out()        PORTC_DIR &= ~BIT(14)
            #define  set_mute_io_high()       PORTC_OUT|= BIT(14)
            #define  set_mute_io_low()        PORTC_OUT &= ~BIT(14)   
			
         #elif defined(pa_mute_use_pin_PC10)
         
            #define  set_mute_io_is_out()        PORTC_DIR &= ~BIT(10);PORTC_PU |=BIT(10)
            #define  set_mute_io_high()       PORTC_OUT|= BIT(10)
            #define  set_mute_io_low()        PORTC_OUT &= ~BIT(10)   			
        #elif defined(pa_mute_use_pin_PC15)
        			
           #define	set_mute_io_is_out()		PORTC_DIR &= ~BIT(15)
           #define	set_mute_io_high()		 PORTC_OUT|= BIT(15)
           #define	set_mute_io_low()		 PORTC_OUT &= ~BIT(15)	 
         #elif defined(pa_mute_use_pin_PA8)
					
		   #define	set_mute_io_is_out()		PORTA_DIR &= ~BIT(8)
		   #define	set_mute_io_high()		 PORTA_OUT|= BIT(8)
		   #define	set_mute_io_low()		 PORTA_OUT &= ~BIT(8)	 
         #elif defined(pa_mute_use_pin_PA2)
					
		   #define	set_mute_io_is_out()		PORTA_DIR &= ~BIT(2)
		   #define	set_mute_io_high()		 PORTA_OUT|= BIT(2)
		   #define	set_mute_io_low()		 PORTA_OUT &= ~BIT(2)
       #elif defined(pa_mute_use_pin_PA14)
       					  
         #define  set_mute_io_is_out() 	   PORTA_DIR &= ~BIT(14)
         #define  set_mute_io_high()		PORTA_OUT|= BIT(14)
         #define  set_mute_io_low()		PORTA_OUT &= ~BIT(14)	
        #elif defined(pa_mute_use_pin_PA10)
        					  
          #define  set_mute_io_is_out() 	   PORTA_DIR &= ~BIT(10)
          #define  set_mute_io_high()		PORTA_OUT|= BIT(10)
          #define  set_mute_io_low()		PORTA_OUT &= ~BIT(10)	
         #elif defined(pa_mute_use_pin_PB8)
         					  
           #define  set_mute_io_is_out() 	   PORTB_DIR &= ~BIT(8)
           #define  set_mute_io_high()		PORTB_OUT|= BIT(8)
           #define  set_mute_io_low()		PORTB_OUT &= ~BIT(8)	
        #elif defined(pa_mute_use_pin_PB9)
        								
          #define  set_mute_io_is_out() 	  PORTB_DIR &= ~BIT(9)
          #define  set_mute_io_high()	   PORTB_OUT|= BIT(9)
          #define  set_mute_io_low()	   PORTB_OUT &= ~BIT(9)    
         #elif defined(pa_mute_use_pin_PC12)
            #define  set_mute_io_is_out()        PORTC_DIR &= ~BIT(12)
            #define  set_mute_io_high()       PORTC_OUT|= BIT(12)
            #define  set_mute_io_low()        PORTC_OUT &= ~BIT(12)   
         #elif defined(pa_mute_use_pin_PC15)
            #define  set_mute_io_is_out()        PORTC_DIR &= ~BIT(15)
            #define  set_mute_io_high()       PORTC_OUT|= BIT(15)
            #define  set_mute_io_low()        PORTC_OUT &= ~BIT(15)   
        	
         #elif defined(pa_mute_use_pin_PC2)
            #define  set_mute_io_is_out()        PORTC_DIR &= ~BIT(2)
            #define  set_mute_io_high()       PORTC_OUT|= BIT(2)
            #define  set_mute_io_low()        PORTC_OUT &= ~BIT(2)   		
        #elif defined(supper_two_pin_mute_pa7_pa6)
        
        #else   //defined(suppoet_mute_user_PA6)
        
            #define set_mute_io_is_out()      PORTA_DIR &= ~BIT(6)	
            #define set_mute_io_high()        PORTA_OUT |= BIT(6)          
            #define set_mute_io_low()         PORTA_OUT &= ~BIT(6)         
        
          //      #error(" 请设置 检测mute IO ") 
        #endif 

#ifdef support_io_det_mute
#ifdef auto_mute_det_io_use_pb10
  #define AUTOMUTE_IO    BIT(10)
  #define AUTOMUTE_IO_SET    {PORTB_DIR |= AUTOMUTE_IO;PORTB_PU  |= AUTOMUTE_IO;}
  #define AUTOMUTE_IO_CHECK  (PORTB_IN  &  AUTOMUTE_IO)
  #elif defined(auto_mute_det_io_use_pb6)
  #define AUTOMUTE_IO    BIT(6)
  #define AUTOMUTE_IO_SET    {PORTB_DIR |= AUTOMUTE_IO;PORTB_PU  |= AUTOMUTE_IO;}
  #define AUTOMUTE_IO_CHECK  (PORTB_IN  &  AUTOMUTE_IO)
#endif
#endif

#endif 


// 频谱显示
#ifdef  support_led_eq_disp    //支持发光管频谱显示
   #ifdef  support_led_eq_user_PA15PB6PB7PB8PB9PB10
             #define  set_all_led_io_is_out()     PORTB_DIR &= ~(BIT(6)|BIT(7)|BIT(8)|BIT(9)|BIT(10));\
              		                                               PORTB_PU |= BIT(6)|BIT(7)|BIT(8)|BIT(9)|BIT(10);\
              		                                               PORTA_DIR &= ~(BIT(15));\
              		                                               PORTA_PU |= BIT(15)
             
             #define  set_all_led_io_off()          PORTB_OUT  &= ~(BIT(6)|BIT(7)|BIT(8)|BIT(9)|BIT(10)) ;\
             		                                                     PORTA_OUT&= ~(BIT(15));  

     #ifdef support_rdt_2536_mode
                   #define    Set_6_led_io_is_on()                  PORTA_OUT|= BIT(15) 
                  #define    Set_5_led_io_is_on()           	  PORTB_OUT|= BIT(6) 
                  #define    Set_4_led_io_is_on()           	  PORTB_OUT|= BIT(7) 
                  #define    Set_3_led_io_is_on()                 PORTB_OUT|= BIT(8)       
                  #define    Set_2_led_io_is_on()     	         PORTB_OUT|= BIT(9)          
                  #define    Set_1_led_io_is_on()                 PORTB_OUT|= BIT(10) 	
     #else                  
                  #define    Set_1_led_io_is_on()                  PORTA_OUT|= BIT(15) 
                  #define    Set_6_led_io_is_on()           	  PORTB_OUT|= BIT(6) 
                  #define    Set_5_led_io_is_on()           	  PORTB_OUT|= BIT(7) 
                  #define    Set_4_led_io_is_on()                 PORTB_OUT|= BIT(8)       
                  #define    Set_3_led_io_is_on()     	         PORTB_OUT|= BIT(9)          
                  #define    Set_2_led_io_is_on()                 PORTB_OUT|= BIT(10) 	
     #endif 	

    #elif defined(support_led_eq_user_PA9PA10PA11PA14PA15)
	  #define  set_all_led_io_is_out()     PORTA_DIR &= ~(BIT(9)|BIT(10)|BIT(11)|BIT(14)|BIT(15));\
              		                                           PORTA_PU |= BIT(9)|BIT(10)|BIT(11)|BIT(14)|BIT(15);\
     
             
         #define  set_all_led_io_off()          PORTA_OUT  &= ~(BIT(9)|BIT(10)|BIT(11)|BIT(14)|BIT(15)) ;\
             		                                                 

          #define    Set_5_led_io_is_on()           	        PORTA_OUT|= BIT(9) 
          #define    Set_4_led_io_is_on()                    PORTA_OUT|= BIT(10)       
          #define    Set_3_led_io_is_on()     	         PORTA_OUT|= BIT(11)          
          #define    Set_2_led_io_is_on()                    PORTA_OUT|= BIT(14) 	
	   #define    Set_1_led_io_is_on()                    PORTA_OUT|= BIT(15) 	
	  
		  
    #elif defined(support_led_eq_user_PA9PA10PA11PA14)
	  #define  set_all_led_io_is_out()     PORTA_DIR &= ~(BIT(9)|BIT(10)|BIT(11)|BIT(14));\
              		                                           PORTA_PU |= BIT(9)|BIT(10)|BIT(11)|BIT(14);\
     
             
         #define  set_all_led_io_off()          PORTA_OUT  &= ~(BIT(9)|BIT(10)|BIT(11)|BIT(14)) ;\
             		                                                 

          #define    Set_1_led_io_is_on()           	        PORTA_OUT|= BIT(9) 
          #define    Set_2_led_io_is_on()                    PORTA_OUT|= BIT(10)       
          #define    Set_3_led_io_is_on()     	         PORTA_OUT|= BIT(11)          
          #define    Set_4_led_io_is_on()                    PORTA_OUT|= BIT(14) 	
    #elif defined(support_led_eq_user_PA15PA14PA11PA10)
	  #define  set_all_led_io_is_out()     PORTA_DIR &= ~(BIT(15)|BIT(14)|BIT(11)|BIT(10));\
              		                                           PORTA_PU |= BIT(15)|BIT(14)|BIT(11)|BIT(10);\
     
             
         #define  set_all_led_io_off()          PORTA_OUT  &= ~(BIT(15)|BIT(14)|BIT(11)|BIT(10)) ;\
             		                                                 

          #define    Set_1_led_io_is_on()           	  PORTA_OUT|= BIT(10) 
          #define    Set_2_led_io_is_on()                    PORTA_OUT|= BIT(11)       
          #define    Set_3_led_io_is_on()     	         PORTA_OUT|= BIT(15)          
          #define    Set_4_led_io_is_on()                    PORTA_OUT|= BIT(14) 	


   #elif defined(support_led_eq_user_PB6PB7PB8PB9PB10)
             #define  set_all_led_io_is_out()     PORTB_DIR &= ~(BIT(6)|BIT(7)|BIT(8)|BIT(9)|BIT(10));\
              		                                               PORTB_PU |= BIT(6)|BIT(7)|BIT(8)|BIT(9)|BIT(10)

             
             #define  set_all_led_io_off()          PORTB_OUT  &= ~(BIT(6)|BIT(7)|BIT(8)|BIT(9)|BIT(10))              
             
             #define    Set_5_led_io_is_on()           	  PORTB_OUT|= BIT(6) 
             #define    Set_4_led_io_is_on()           	  PORTB_OUT|= BIT(7) 
             #define    Set_3_led_io_is_on()                 PORTB_OUT|= BIT(8)       
             #define    Set_2_led_io_is_on()     	         PORTB_OUT|= BIT(9)          
             #define    Set_1_led_io_is_on()                 PORTB_OUT|= BIT(10) 	
			 
   #else 
    #error(" 请设置eq led  IO ") 
   #endif 
#endif 




/* 软开机   用IO口来打开MOS管 */
#ifdef   support_io_power_on_off   //IO 口控制MOS管开关
       #ifdef      power_on_off_user_PA7
       #define    Set_power_on_off_io_is_out()        PORTA_DIR &= ~BIT(7); PORTA_PU |= BIT(7)
       #define    Set_power_on_off_io_is_HIGH()       PORTA_OUT|= BIT(7)
       #define    Set_power_on_off_io_is_LOW()        PORTA_OUT &= ~BIT(7)  
   #elif defined( power_on_off_user_PA4)
       #define    Set_power_on_off_io_is_out()         PORTA_DIR &= ~BIT(4); PORTA_PU |= BIT(4)
       #define    Set_power_on_off_io_is_HIGH()       PORTA_OUT|= BIT(4)
       #define    Set_power_on_off_io_is_LOW()        PORTA_OUT &= ~BIT(4)       	   
   #elif defined( power_on_off_user_PA12)
       #define    Set_power_on_off_io_is_out()        PORTA_DIR &= ~BIT(12); PORTA_PU |= BIT(12)
       #define    Set_power_on_off_io_is_HIGH()       PORTA_OUT|= BIT(12)
       #define    Set_power_on_off_io_is_LOW()        PORTA_OUT &= ~BIT(12)       
   #elif defined( power_on_off_user_PA13)
       #define    Set_power_on_off_io_is_out()        PORTA_DIR &= ~BIT(13); PORTA_PU |= BIT(13)
       #define    Set_power_on_off_io_is_HIGH()       PORTA_OUT|= BIT(13)
       #define    Set_power_on_off_io_is_LOW()        PORTA_OUT &= ~BIT(13) 
   #elif defined(power_on_off_user_PB8)
        #define POWER_EN_BIT    BIT(8)
        #define    Set_power_on_off_io_is_out()        PORTB_DIR &= ~POWER_EN_BIT; PORTB_PU |= POWER_EN_BIT
        #define    Set_power_on_off_io_is_HIGH()       PORTB_OUT|= POWER_EN_BIT
        #define    Set_power_on_off_io_is_LOW()        PORTB_OUT &= ~POWER_EN_BIT      
   #elif defined(power_on_off_user_PB11)
       #define    Set_power_on_off_io_is_out()        PORTB_DIR &= ~BIT(11); PORTB_PU |= BIT(11)
       #define    Set_power_on_off_io_is_HIGH()       PORTB_OUT|= BIT(11)
       #define    Set_power_on_off_io_is_LOW()        PORTB_OUT &= ~BIT(11)      
   #elif defined( power_on_off_user_PB12)
       #define    Set_power_on_off_io_is_out()        PORTB_DIR &= ~BIT(12); PORTB_PU |= BIT(12)
       #define    Set_power_on_off_io_is_HIGH()       PORTB_OUT|= BIT(12)
       #define    Set_power_on_off_io_is_LOW()        PORTB_OUT &= ~BIT(12)      
   #elif defined( power_on_off_user_PB14)
       #define    Set_power_on_off_io_is_out()        PORTB_DIR &= ~BIT(14); PORTB_PU |= BIT(14)
       #define    Set_power_on_off_io_is_HIGH()       PORTB_OUT|= BIT(14)
       #define    Set_power_on_off_io_is_LOW()        PORTB_OUT &= ~BIT(14)     
   #elif defined( power_on_off_user_PB15)
       #define    Set_power_on_off_io_is_out()        PORTB_DIR &= ~BIT(15); PORTB_PU |= BIT(15)
       #define    Set_power_on_off_io_is_HIGH()       PORTB_OUT|= BIT(15)
       #define    Set_power_on_off_io_is_LOW()        PORTB_OUT &= ~BIT(15)     
   #elif defined(power_on_off_user_PC2)	   
       #define    Set_power_on_off_io_is_out()        PORTC_DIR &= ~BIT(2); PORTC_PU |= BIT(2)
       #define    Set_power_on_off_io_is_HIGH()       PORTC_OUT|= BIT(2)
       #define    Set_power_on_off_io_is_LOW()        PORTC_OUT &= ~BIT(2)  
   #elif defined(power_on_off_user_PC15)	   
       #define    Set_power_on_off_io_is_out()        PORTC_DIR &= ~BIT(15); PORTC_PU |= BIT(15)
       #define    Set_power_on_off_io_is_HIGH()       PORTC_OUT|= BIT(15)
       #define    Set_power_on_off_io_is_LOW()        PORTC_OUT &= ~BIT(15)  
   #elif defined(power_on_off_user_PC13)	   
       #define    Set_power_on_off_io_is_out()        PORTC_DIR &= ~BIT(13); PORTC_PU |= BIT(13)
       #define    Set_power_on_off_io_is_HIGH()       PORTC_OUT|= BIT(13)
       #define    Set_power_on_off_io_is_LOW()        PORTC_OUT &= ~BIT(13)  	   
  #elif defined(power_on_off_user_PD0)	   
        #define    Set_power_on_off_io_is_out()        PORTD_DIR &= ~BIT(0); PORTD_PU |= BIT(0)
        #define    Set_power_on_off_io_is_HIGH()       PORTD_OUT|= BIT(0)
        #define    Set_power_on_off_io_is_LOW()        PORTD_OUT &= ~BIT(0)      
  #elif defined(power_on_off_user_PD1)	   
        #define    Set_power_on_off_io_is_out()        PORTD_DIR &= ~BIT(1); PORTD_PU |= BIT(1)
        #define    Set_power_on_off_io_is_HIGH()       PORTD_OUT|= BIT(1)
        #define    Set_power_on_off_io_is_LOW()        PORTD_OUT &= ~BIT(1)    		
   #else 
         #error(" 请设置 MOS 管控制 io ") 
      #endif 
#endif 






#ifdef  support_ic_chack_dc_in  //检测是否外接电源
     #ifdef  chack_dc_in_user_PD0	   
       #define     DC_DET_IO_IS_IN()    PORTD_DIR |= BIT(0);   PORTD_PU &= ~BIT(0); PORTD_PD  |= BIT(0);
	#define     DC_DET_READ()           PORTD_IN & BIT(0) 
    #elif defined(chack_dc_in_user_PD1)	
         #ifdef support_ext_down_10k
		 #define     DC_DET_IO_IS_IN()    PORTD_DIR |= BIT(1);   PORTD_PU &= ~BIT(1); 
		 #define     DC_DET_READ()           PORTD_IN & BIT(1) 
         #else 
      	 	#define     DC_DET_IO_IS_IN()    PORTD_DIR |= BIT(1);   PORTD_PU &= ~BIT(1); PORTD_PD   |=BIT(1);
      	 	#define     DC_DET_READ()           PORTD_IN & BIT(1) 
     	#endif  
    #elif defined(chack_dc_in_user_PA7)	
           #ifdef support_ext_down_10k
   	 #define     DC_DET_IO_IS_IN()    PORTA_DIR |= BIT(7);   PORTA_PU &= ~BIT(7); PORTA_PD   &=~BIT(7);
   	#define     DC_DET_READ()           PORTA_IN & BIT(7) 	
          #else      
   	 #define     DC_DET_IO_IS_IN()    PORTA_DIR |= BIT(7);   PORTA_PU &= ~BIT(7); PORTA_PD   |=BIT(7);
   	#define     DC_DET_READ()           PORTA_IN & BIT(7) 	
   	#endif 
    #elif defined(chack_dc_in_user_PA12)	
           #ifdef support_ext_down_10k
    	 #define     DC_DET_IO_IS_IN()    PORTA_DIR |= BIT(12);   PORTA_PU &= ~BIT(12); PORTA_PD   &=~BIT(12);
    	#define     DC_DET_READ()           PORTA_IN & BIT(12) 	
          #else      
   	 #define     DC_DET_IO_IS_IN()    PORTA_DIR |= BIT(12);   PORTA_PU &= ~BIT(12); PORTA_PD   |=BIT(12);
   	#define     DC_DET_READ()           PORTA_IN & BIT(12) 	
   	#endif 
    #elif defined(chack_dc_in_user_PA13)	
           #ifdef support_ext_down_10k
   	 #define     DC_DET_IO_IS_IN()    PORTA_DIR |= BIT(13);   PORTA_PU &= ~BIT(13); PORTA_PD   &=~BIT(13);
   	#define     DC_DET_READ()           PORTA_IN & BIT(13) 	
          #else      
   	 #define     DC_DET_IO_IS_IN()    PORTA_DIR |= BIT(13);   PORTA_PU &= ~BIT(13); PORTA_PD   |=BIT(13);
   	#define     DC_DET_READ()           PORTA_IN & BIT(13) 	
   	#endif 
    #elif defined(chack_dc_in_user_PB10)	
           #ifdef support_ext_down_10k
   	 #define     DC_DET_IO_IS_IN()    PORTB_DIR |= BIT(10);   PORTB_PU &= ~BIT(10); PORTB_PD   &=~BIT(10);
   	#define     DC_DET_READ()           PORTB_IN & BIT(10) 	
          #else      
   	 #define     DC_DET_IO_IS_IN()    PORTB_DIR |= BIT(10);   PORTB_PU &= ~BIT(10); PORTB_PD   |=BIT(10);
   	#define     DC_DET_READ()           PORTB_IN & BIT(10) 	
   	#endif 	
    #elif defined(chack_dc_in_user_PC15)	
         #ifdef support_ext_down_10k
         #define     DC_DET_IO_IS_IN()    PORTC_DIR |= BIT(15);   PORTC_PU &= ~BIT(15); PORTC_PD   &=~BIT(15);
         #define     DC_DET_READ()           PORTC_IN & BIT(15) 	
         #else      
         #define     DC_DET_IO_IS_IN()    PORTC_DIR |= BIT(15);   PORTC_PU &= ~BIT(15); PORTC_PD   |=BIT(15);
         #define     DC_DET_READ()           PORTC_IN & BIT(15) 	
         #endif 
    #else 
        #error(" 请设置 检测外接电源检测IO ") 
    #endif 
#endif 

//功放AB/D类切换  
#ifdef   support_amP_ab_d
#ifdef    amp_ab_d_user_PC2
            #define Set_amp_ab_d_out()         PORTC_DIR &= ~BIT(2); PORTC_PU |= BIT(2) 
            #define Set_FM_IS_AB()                 PORTC_OUT &= ~BIT(2) 
            #define Set_AMP_IS_D()                 PORTC_OUT|= BIT(2)
#elif defined(amp_ab_d_user_PC14)
            #define Set_amp_ab_d_out()         PORTC_DIR &= ~BIT(14); PORTC_PU |= BIT(14) 
            #define Set_FM_IS_AB()                 PORTC_OUT &= ~BIT(14) 
            #define Set_AMP_IS_D()                 PORTC_OUT|= BIT(14)
#elif defined(amp_ab_d_user_PC11)
            #define Set_amp_ab_d_out()         PORTC_DIR &= ~BIT(11); PORTC_PU |= BIT(11) 
            #define Set_FM_IS_AB()                 PORTC_OUT &= ~BIT(11) 
            #define Set_AMP_IS_D()                 PORTC_OUT|= BIT(11)
#elif   defined(amp_ab_d_user_PD1)
            #define Set_amp_ab_d_out()          PORTD_DIR &= ~BIT(1); PORTC_PU |= BIT(1) 
            #define Set_FM_IS_AB()              PORTD_OUT &= ~BIT(1) 
            #define Set_AMP_IS_D()              PORTD_OUT|= BIT(1)	
#elif   defined(amp_ab_d_user_PD0)
            #define Set_amp_ab_d_out()          PORTD_DIR &= ~BIT(0); PORTD_PU |= BIT(0) 
            #define Set_FM_IS_AB()              PORTD_OUT &= ~BIT(0) 
            #define Set_AMP_IS_D()              PORTD_OUT|= BIT(0)	
#elif   defined(amp_ab_d_user_PA7)
            #define Set_amp_ab_d_out()           PORTA_DIR &= ~BIT(7); PORTA_PU |= BIT(7) 
            #define Set_FM_IS_AB()               PORTA_OUT &= ~BIT(7) 
            #define Set_AMP_IS_D()               PORTA_OUT|= BIT(7)	
#elif   defined(amp_ab_d_user_PA9)
            #define Set_amp_ab_d_out()           PORTA_DIR &= ~BIT(9); PORTA_PU |= BIT(9) 
            #define Set_FM_IS_AB()               PORTA_OUT &= ~BIT(9) 
            #define Set_AMP_IS_D()               PORTA_OUT|= BIT(9)	
#elif defined(amp_ab_d_user_PD1_PA7)
		    #define Set_amp_ab_d_out()          PORTD_DIR &= ~BIT(1); PORTC_PU |= BIT(1);PORTA_DIR &= ~BIT(7); PORTA_PU |= BIT(7)  
            #define Set_FM_IS_AB()              PORTD_OUT &= ~BIT(1) ; PORTA_OUT|= BIT(7)
            #define Set_AMP_IS_D()              PORTD_OUT|= BIT(1)	; PORTA_OUT &= ~BIT(7)
#elif   defined(amp_ab_d_user_PB9)
            #define Set_amp_ab_d_out()          PORTB_DIR &= ~BIT(9); PORTB_PU |= BIT(9) 
            #ifdef AB_D_HI_LOW_REVISE
             #define Set_FM_IS_AB()				PORTB_OUT |=BIT(9) 
             #define Set_AMP_IS_D()				PORTB_OUT&=~BIT(9)			  
            #else
              #define Set_FM_IS_AB()              PORTB_OUT &= ~BIT(9) 
              #define Set_AMP_IS_D()              PORTB_OUT|= BIT(9)	          
            #endif
#elif   defined(amp_ab_d_user_PB7)
            #define Set_amp_ab_d_out()          PORTB_DIR &= ~BIT(7); PORTB_PU |= BIT(7)          
            #define Set_FM_IS_AB()              PORTB_OUT &= ~BIT(7) 
            #define Set_AMP_IS_D()              PORTB_OUT|= BIT(7)	          
#elif   defined(amp_ab_d_user_PB1)
            #define Set_amp_ab_d_out()          PORTB_DIR &= ~BIT(1); PORTB_PU |= BIT(1)          
            #define Set_FM_IS_AB()              PORTB_OUT &= ~BIT(1) 
            #define Set_AMP_IS_D()              PORTB_OUT|= BIT(1)	          
#elif   defined(amp_ab_d_user_PB13)
            #define Set_amp_ab_d_out()          PORTB_DIR &= ~BIT(13); PORTB_PU |= BIT(13)          
            #define Set_FM_IS_AB()              PORTB_OUT &= ~BIT(13) 
            #define Set_AMP_IS_D()              PORTB_OUT|= BIT(13)	            

#elif   defined(amp_ab_d_user_PB12)
            #define Set_amp_ab_d_out()          PORTB_DIR &= ~BIT(12); PORTB_PU |= BIT(12)          
            #define Set_FM_IS_AB()              PORTB_OUT &= ~BIT(12) 
            #define Set_AMP_IS_D()              PORTB_OUT|= BIT(12)	         
#elif   defined(amp_ab_d_user_PA11)
            #define Set_amp_ab_d_out()          PORTA_DIR &= ~BIT(11); PORTA_PU |= BIT(11)          
            #define Set_FM_IS_AB()              PORTA_OUT &= ~BIT(11) 
            #define Set_AMP_IS_D()              PORTA_OUT|= BIT(11)	     			
#elif   defined(amp_ab_d_user_PA12)
            #define Set_amp_ab_d_out()          PORTA_DIR &= ~BIT(12); PORTA_PU |= BIT(12)          
            #define Set_FM_IS_AB()              PORTA_OUT &= ~BIT(12) 
            #define Set_AMP_IS_D()              PORTA_OUT|= BIT(12)	     
#elif   defined(amp_ab_d_user_PA13)
            #define Set_amp_ab_d_out()          PORTA_DIR &= ~BIT(13); PORTA_PU |= BIT(13)          
            #define Set_FM_IS_AB()              PORTA_OUT &= ~BIT(13) 
            #define Set_AMP_IS_D()              PORTA_OUT|= BIT(13)	
#elif   defined(amp_ab_d_user_PA14)
            #define Set_amp_ab_d_out()          PORTA_DIR &= ~BIT(14); PORTA_PU |= BIT(14)          
            #define Set_FM_IS_AB()              PORTA_OUT &= ~BIT(14) 
            #define Set_AMP_IS_D()              PORTA_OUT|= BIT(14)	    
#elif   defined(amp_ab_d_user_PC15)
            #define Set_amp_ab_d_out()          PORTC_DIR &= ~BIT(15); PORTC_PU |= BIT(15)          
            #define Set_FM_IS_AB()              PORTC_OUT &= ~BIT(15) 
            #define Set_AMP_IS_D()              PORTC_OUT|= BIT(15)	    
#elif   defined(amp_ab_d_user_PC12)
            #define Set_amp_ab_d_out()          PORTC_DIR &= ~BIT(12); PORTC_PU |= BIT(12)          
            #define Set_FM_IS_AB()              PORTC_OUT &= ~BIT(12) 
            #define Set_AMP_IS_D()              PORTC_OUT|= BIT(12)	     			
#elif   defined(amp_ab_d_user_PC10)
            #define Set_amp_ab_d_out()          PORTC_DIR &= ~BIT(10); PORTC_PU |= BIT(10)          
            #define Set_FM_IS_AB()              PORTC_OUT &= ~BIT(10) 
            #define Set_AMP_IS_D()              PORTC_OUT|= BIT(10)	     			
#elif   defined(amp_ab_d_user_PB15)
      #ifdef amp_amp_add_mos
              #define Set_amp_ab_d_out()          PORTB_DIR &= ~BIT(15); PORTB_PU |= BIT(15) 
              #define Set_FM_IS_AB()                   PORTB_OUT|= BIT(15)	
              #define Set_AMP_IS_D()                  PORTB_OUT &= ~BIT(15)  
      #else 
           #define Set_amp_ab_d_out()          PORTB_DIR &= ~BIT(15); PORTB_PU |= BIT(15) 
           #define Set_FM_IS_AB()                   PORTB_OUT &= ~BIT(15) 
           #define Set_AMP_IS_D()                  PORTB_OUT|= BIT(15)	     	
      #endif 		
#ifdef customer_MLH_LFFD            
            #define Set_FM_IS_AB()             // PORTB_OUT &= ~BIT(15) 
            #define Set_AMP_IS_D()              PORTB_OUT|= BIT(15)	           
#else 
            
            #define Set_FM_IS_AB()              PORTB_OUT &= ~BIT(15) 
            #define Set_AMP_IS_D()              PORTB_OUT|= BIT(15)	            
#endif 
#else 
    #error("please support_amP_ab_d ")

#endif 
#endif 

#ifdef support_backlight_led
#ifdef backlight_led_pc11
#define backlight_led_d_out()          PORTC_DIR &= ~BIT(11); //PORTC_PU |= BIT(11)          
#define Set_backlight_led_l()              PORTC_OUT &= ~BIT(11) 
#define Set_backlight_led_h()              PORTC_OUT|= BIT(11)	
#endif
#endif


#ifdef SUPPORT_ENCODE_flash_led
#ifdef ENC_led_io_PC10

     #define ENC_LED_BIT                BIT(10)
     #define ENC_LED_INIT_EN()     {PORTC_PU &= ~ENC_LED_BIT;PORTC_PD &= ~ENC_LED_BIT;PORTC_DIR &= ~ENC_LED_BIT;}
     #define ENC_LED_ON()          PORTC_OUT |= ENC_LED_BIT;
     #define ENC_LED_OFF()        PORTC_OUT &= ~ENC_LED_BIT;
#elif defined support_encode_use_tm1628_io
     #define ENC_LED_BIT            
     #define ENC_LED_INIT_EN()  
     #define ENC_LED_ON()         
     #define ENC_LED_OFF()       

#endif
#endif

#ifdef support_sound_4052_control

#ifdef sound_4052_io_ab_pb7pb8
#define AC4052_A_OFF()	{PORTB_OUT &=~ BIT(7);PORTB_PU &=~BIT(7);PORTB_PD |= BIT(7);PORTB_DIR &= ~BIT(7);}//A 
#define AC4052_A_ON() 	{PORTB_OUT |= BIT(7);PORTB_PU |=BIT(7);PORTB_PD &=~ BIT(7);PORTB_DIR &= ~BIT(7);}
#define AC4052_B_OFF()	{PORTB_OUT &=~ BIT(8);PORTB_PU &=~BIT(8);PORTB_PD |= BIT(8);PORTB_DIR &= ~BIT(8);}//B 
#define AC4052_B_ON() 	{PORTB_OUT |= BIT(8);PORTB_PU |=BIT(8);PORTB_PD &=~ BIT(8);PORTB_DIR &= ~BIT(8);}
#elif defined sound_4052_io_ab_p6pb7
#define AC4052_A_OFF()	{PORTB_OUT &=~ BIT(6);PORTB_PU &=~BIT(6);PORTB_PD |= BIT(6);PORTB_DIR &= ~BIT(6);}//B 
#define AC4052_A_ON() 	{PORTB_OUT |= BIT(6);PORTB_PU |=BIT(6);PORTB_PD &=~ BIT(6);PORTB_DIR &= ~BIT(6);}
#define AC4052_B_OFF()	{PORTB_OUT &=~ BIT(7);PORTB_PU &=~BIT(7);PORTB_PD |= BIT(7);PORTB_DIR &= ~BIT(7);}//A 
#define AC4052_B_ON() 	{PORTB_OUT |= BIT(7);PORTB_PU |=BIT(7);PORTB_PD &=~ BIT(7);PORTB_DIR &= ~BIT(7);}
#elif defined sound_4052_io_ab_pb10pb9
#define AC4052_A_OFF()	{PORTB_OUT &=~ BIT(10);PORTB_PU &=~BIT(10);PORTB_PD |= BIT(10);PORTB_DIR &= ~BIT(10);}//A 
#define AC4052_A_ON() 	{PORTB_OUT |= BIT(10);PORTB_PU |=BIT(10);PORTB_PD &=~ BIT(10);PORTB_DIR &= ~BIT(10);}
#define AC4052_B_OFF()	{PORTB_OUT &=~ BIT(9);PORTB_PU &=~BIT(9);PORTB_PD |= BIT(9);PORTB_DIR &= ~BIT(9);}//B 
#define AC4052_B_ON() 	{PORTB_OUT |= BIT(9);PORTB_PU |=BIT(9);PORTB_PD &=~ BIT(9);PORTB_DIR &= ~BIT(9);}
#elif defined sound_4052_io_abcdef_pa9pa10pa11pa15pa14pa8
#define AC4052_A_OFF()	{PORTA_OUT &=~ BIT(9);PORTA_PU &=~BIT(9);PORTB_PD |= BIT(9);PORTA_DIR &= ~BIT(9);}//A 
#define AC4052_A_ON() 	{PORTA_OUT |= BIT(9);PORTA_PU |=BIT(9);PORTA_PD &=~ BIT(9);PORTA_DIR &= ~BIT(9);}
#define AC4052_B_OFF()	{PORTA_OUT &=~ BIT(10);PORTA_PU &=~BIT(10);PORTA_PD |= BIT(10);PORTA_DIR &= ~BIT(10);}//B 
#define AC4052_B_ON() 	{PORTA_OUT |= BIT(10);PORTA_PU |=BIT(10);PORTA_PD &=~ BIT(10);PORTA_DIR &= ~BIT(10);}
#define AC4052_C_OFF()	{PORTA_OUT &=~ BIT(11);PORTA_PU &=~BIT(11);PORTA_PD |= BIT(11);PORTA_DIR &= ~BIT(11);}//A 
#define AC4052_C_ON() 	{PORTA_OUT |= BIT(11);PORTA_PU |=BIT(11);PORTA_PD &=~ BIT(11);PORTA_DIR &= ~BIT(11);}
#define AC4052_D_OFF()	{PORTA_OUT &=~ BIT(15);PORTA_PU &=~BIT(15);PORTA_PD |= BIT(15);PORTA_DIR &= ~BIT(15);}//B 
#define AC4052_D_ON() 	{PORTA_OUT |= BIT(15);PORTA_PU |=BIT(15);PORTA_PD &=~ BIT(15);PORTA_DIR &= ~BIT(15);}
#define AC4052_E_OFF()	{PORTA_OUT &=~ BIT(14);PORTA_PU &=~BIT(14);PORTA_PD |= BIT(14);PORTA_DIR &= ~BIT(14);}//A 
#define AC4052_E_ON() 	{PORTA_OUT |= BIT(14);PORTA_PU |=BIT(14);PORTA_PD &=~ BIT(14);PORTA_DIR &= ~BIT(14);}
#define AC4052_F_OFF()	{PORTA_OUT &=~ BIT(8);PORTA_PU &=~BIT(8);PORTA_PD |= BIT(8);PORTA_DIR &= ~BIT(8);}//B 
#define AC4052_F_ON() 	{PORTA_OUT |= BIT(8);PORTA_PU |=BIT(8);PORTA_PD &=~ BIT(8);PORTA_DIR &= ~BIT(8);}

#endif
	
#ifdef  sound_4052_io_mode_1
/*
		A B
DVD		0 0
CD		1 0
AUX		0 1
MP3/BT	1 1
*/
#define AC4052_IS_DVD()	{AC4052_A_OFF();AC4052_B_OFF();}
#define AC4052_IS_CD() 	{AC4052_A_ON();AC4052_B_OFF();}
#define AC4052_IS_AUX()	{AC4052_A_OFF();AC4052_B_ON();}
#define AC4052_IS_MP3() 	{AC4052_A_ON();AC4052_B_ON();}

#elif defined sound_4052_io_mode_2
/*
		A B
DVD		0 1
CD		1 0
AUX		1 1
MP3/BT	0 0
*/

#define AC4052_IS_DVD()	{AC4052_A_OFF();AC4052_B_ON();}
#define AC4052_IS_CD() 	{AC4052_A_ON();AC4052_B_OFF();}
#define AC4052_IS_AUX()	{AC4052_A_ON();AC4052_B_ON();}
#define AC4052_IS_MP3() 	{AC4052_A_OFF();AC4052_B_OFF();}

#elif defined sound_4052_io_mode_3
/*
		A B
DVD		0 0
CD		1 0
AUX		1 1
MP3/BT	0 1
*/

#define AC4052_IS_DVD()	{AC4052_A_OFF();AC4052_B_OFF();}
#define AC4052_IS_CD() 	{AC4052_A_ON();AC4052_B_OFF();}
#define AC4052_IS_AUX()	{AC4052_A_ON();AC4052_B_ON();}
#define AC4052_IS_MP3() 	{AC4052_A_OFF();AC4052_B_ON();}
#elif defined sound_4052_io_mode_4

/*
		A B
DVD		1 0
CD		0 1
AUX		0 0
MP3/BT	1 1

*/
#define AC4052_IS_DVD()	{AC4052_A_ON();AC4052_B_OFF();}
#define AC4052_IS_CD() 	{AC4052_A_OFF();AC4052_B_ON();}
#define AC4052_IS_AUX()	{AC4052_A_OFF();AC4052_B_OFF();}
#define AC4052_IS_MP3() 	{AC4052_A_ON();AC4052_B_ON();}

#elif defined sound_4052_io_mode_5

/*
		ABCDEF
AC3		100010
DVD		010001
CD		001011
MP3/BT	000100



*/

#define AC4052_IS_AC3()	{AC4052_A_ON();AC4052_B_OFF();AC4052_C_OFF();AC4052_D_OFF();AC4052_E_ON();AC4052_F_OFF();}
#define AC4052_IS_DVD() 	{AC4052_A_OFF();AC4052_B_ON();AC4052_C_OFF();AC4052_D_OFF();AC4052_E_OFF();AC4052_F_ON();}
#define AC4052_IS_CD()	{AC4052_A_OFF();AC4052_B_OFF();AC4052_C_ON();AC4052_D_OFF();AC4052_E_ON();AC4052_F_ON();}
#define AC4052_IS_MP3() 	{AC4052_A_OFF();AC4052_B_OFF();AC4052_C_OFF();AC4052_D_ON();AC4052_E_OFF();AC4052_F_OFF();}

#define AC4052_IS_AUX() 	{AC4052_A_OFF();AC4052_B_OFF();AC4052_C_OFF();AC4052_D_ON();AC4052_E_OFF();AC4052_F_OFF();}
#define AC4052_IS_MP3() 	{AC4052_A_OFF();AC4052_B_OFF();AC4052_C_OFF();AC4052_D_ON();AC4052_E_OFF();AC4052_F_OFF();}
#define AC4052_IS_FM() 	{AC4052_A_OFF();AC4052_B_OFF();AC4052_C_OFF();AC4052_D_ON();AC4052_E_OFF();AC4052_F_OFF();}
#define AC4052_IS_BT() 	{AC4052_A_OFF();AC4052_B_OFF();AC4052_C_OFF();AC4052_D_ON();AC4052_E_OFF();AC4052_F_OFF();}

#elif defined sound_4052_io_mode_6

/*
		ABCDEF
AC3		011110
DVD		101101
CD		110111
MP3/BT	111000



*/
#define AC4052_IS_AC3()	{AC4052_A_OFF();AC4052_B_ON();AC4052_C_ON();AC4052_D_ON();AC4052_E_ON();AC4052_F_OFF();}
#define AC4052_IS_DVD() 	{AC4052_A_ON();AC4052_B_OFF();AC4052_C_ON();AC4052_D_ON();AC4052_E_OFF();AC4052_F_ON();}
#define AC4052_IS_CD()	{AC4052_A_ON();AC4052_B_ON();AC4052_C_OFF();AC4052_D_ON();AC4052_E_ON();AC4052_F_ON();}
#define AC4052_IS_MP3() 	{AC4052_A_ON();AC4052_B_ON();AC4052_C_ON();AC4052_D_OFF();AC4052_E_OFF();AC4052_F_OFF();}

#elif defined sound_4052_io_mode_7
/*
			A B
DVD			0 0
CD/TAPE		1 0
AC3/BGM	0 1
MP3/BT		1 1

*/
#define AC4052_IS_DVD()	{AC4052_A_OFF();AC4052_B_OFF();}
#define AC4052_IS_CD() 	{AC4052_A_ON();AC4052_B_OFF();}
#define AC4052_IS_AC3()	{AC4052_A_OFF();AC4052_B_ON();}
#define AC4052_IS_MP3() 	{AC4052_A_ON();AC4052_B_ON();}
#define AC4052_IS_AUX() 


#endif
#endif

#ifdef support_vol_io_control
#ifdef support_vol_io_pa7pa6  // pa7- pa6+
#define VOL_DEC_OFF()	{PORTA_OUT &=~ BIT(7);PORTA_PU &=~BIT(7);PORTA_PD |= BIT(7);PORTA_DIR &= ~BIT(7);}//B 
#define VOL_DEC_ON() 	{PORTA_OUT |= BIT(7);PORTA_PU |=BIT(7);PORTA_PD &=~ BIT(7);PORTA_DIR &= ~BIT(7);}
#define VOL_INC_OFF()	{PORTA_OUT &=~ BIT(6);PORTA_PU &=~BIT(6);PORTA_PD |= BIT(6);PORTA_DIR &= ~BIT(6);}//B 
#define VOL_INC_ON() 	{PORTA_OUT |= BIT(6);PORTA_PU |=BIT(6);PORTA_PD &=~ BIT(6);PORTA_DIR &= ~BIT(6);}
#endif

#define VOL_DEC_SET()	{VOL_DEC_ON();VOL_INC_OFF();}
#define VOL_INC_SET() 	{VOL_DEC_OFF();VOL_INC_ON();}

#define VOL_IO_OFF() 	{VOL_DEC_OFF();VOL_INC_OFF();}

#endif



#ifdef SUPPORT_ZY_4LED_RGB
#define LED_R_OFF()	{PORTA_OUT &=~ BIT(14);PORTA_PU &=~BIT(14);PORTA_PD |= BIT(10);PORTA_DIR &= ~BIT(14);}//red 
#define LED_R_ON() 	{PORTA_OUT |= BIT(14);PORTA_PU |=BIT(14);PORTA_PD &=~ BIT(14);PORTA_DIR &= ~BIT(14);}
#define LED_G_OFF()	{PORTC_OUT &=~ BIT(12);PORTC_PU &=~BIT(12);PORTC_PD |= BIT(12);PORTC_DIR &= ~BIT(12);}///green
#define LED_G_ON() 	{PORTC_OUT |= BIT(12);PORTC_PU |=BIT(12);PORTC_PD &=~ BIT(12);PORTC_DIR &= ~BIT(12);}
#define LED_B_OFF()	{PORTA_OUT &=~ BIT(11);PORTA_PU &=~BIT(11);PORTA_PD |= BIT(11);PORTA_DIR &= ~BIT(11);}///blue
#define LED_B_ON() 	{PORTA_OUT |= BIT(11);PORTA_PU |=BIT(11);PORTA_PD &=~ BIT(11);PORTA_DIR &= ~BIT(11);}
#define LED_W_OFF()	{PORTA_OUT &=~ BIT(10);PORTA_PU &=~BIT(10);PORTA_PD |= BIT(10);PORTA_DIR &= ~BIT(10);}//white led
#define LED_W_ON() 	{PORTA_OUT |= BIT(10);PORTA_PU |=BIT(10);PORTA_PD &=~ BIT(10);PORTA_DIR &= ~BIT(10);}
#endif

#ifdef SUPPORT_RGB_BREATH_LAMP
#ifdef RGB_BREATH_LAMP_IO_PC11PC10PC12
#define LED_R_OFF()	{PORTC_OUT &=~ BIT(11);PORTC_PU &=~BIT(11);PORTA_PD |= BIT(11);PORTC_DIR &= ~BIT(11);}//red 
#define LED_R_ON() 	{PORTC_OUT |= BIT(11);PORTC_PU |=BIT(11);PORTA_PD &=~ BIT(11);PORTC_DIR &= ~BIT(11);}
#define LED_G_OFF()	{PORTC_OUT &=~ BIT(10);PORTC_PU &=~BIT(10);PORTC_PD |= BIT(10);PORTC_DIR &= ~BIT(10);}///green
#define LED_G_ON() 	{PORTC_OUT |= BIT(10);PORTC_PU |=BIT(10);PORTC_PD &=~ BIT(10);PORTC_DIR &= ~BIT(10);}
#define LED_B_OFF()	{PORTC_OUT &=~ BIT(12);PORTC_PU &=~BIT(12);PORTC_PD |= BIT(12);PORTC_DIR &= ~BIT(12);}///blue
#define LED_B_ON() 	{PORTC_OUT |= BIT(12);PORTC_PU |=BIT(12);PORTC_PD &=~ BIT(12);PORTC_DIR &= ~BIT(12);}
#elif defined RGB_BREATH_LAMP_IO_PC11PC10PB10
#define LED_R_OFF()	{PORTC_OUT &=~ BIT(11);PORTC_PU &=~BIT(11);PORTC_PD |= BIT(11);PORTC_DIR &= ~BIT(11);}//red 
#define LED_R_ON() 	{PORTC_OUT |= BIT(11);PORTC_PU |=BIT(11);PORTC_PD &=~ BIT(11);PORTC_DIR &= ~BIT(11);}
#define LED_G_OFF()	{PORTC_OUT &=~ BIT(10);PORTC_PU &=~BIT(10);PORTC_PD |= BIT(10);PORTC_DIR &= ~BIT(10);}///green
#define LED_G_ON() 	{PORTC_OUT |= BIT(10);PORTC_PU |=BIT(10);PORTC_PD &=~ BIT(10);PORTC_DIR &= ~BIT(10);}
#define LED_B_OFF()	{PORTB_OUT &=~ BIT(10);PORTB_PU &=~BIT(10);PORTB_PD |= BIT(10);PORTB_DIR &= ~BIT(10);}///blue
#define LED_B_ON() 	{PORTB_OUT |= BIT(10);PORTB_PU |=BIT(10);PORTB_PD &=~ BIT(10);PORTB_DIR &= ~BIT(10);}
#endif
#endif


#ifdef support_battery_show_use_io_led
#ifdef led_battery_show_use_io_pa3pa2pa1
#define LED_BAT_1_OFF(){PORTA_OUT &=~ BIT(3);PORTA_PU &=~BIT(3);PORTA_PD |= BIT(3);PORTA_DIR &= ~BIT(3);}
#define LED_BAT_1_ON()  {PORTA_OUT |= BIT(3);PORTA_PU |=BIT(3);PORTA_PD &=~ BIT(3);PORTA_DIR &= ~BIT(3);}
#define LED_BAT_2_OFF(){PORTA_OUT &=~ BIT(2);PORTA_PU &=~BIT(2);PORTA_PD |= BIT(2);PORTA_DIR &= ~BIT(2);}
#define LED_BAT_2_ON()  {PORTA_OUT |= BIT(2);PORTA_PU |=BIT(2);PORTA_PD &=~ BIT(2);PORTA_DIR &= ~BIT(2);}
#define LED_BAT_3_OFF()	{PORTA_OUT &=~ BIT(1);PORTA_PU &=~BIT(1);PORTA_PD |= BIT(1);PORTA_DIR &= ~BIT(1);}
#define LED_BAT_3_ON()   {PORTA_OUT |= BIT(1);PORTA_PU |=BIT(1);PORTA_PD &=~ BIT(1);PORTA_DIR &= ~BIT(1);}
#endif 
#endif 

#ifdef support_send_ir_code
#define hw_IRsend_Pin_Init()          PORTB_DIR &= ~BIT(6); PORTB_PU |= BIT(6)          
#define hw_IRsend_Pin_in_Init()          PORTB_DIR |= BIT(6); PORTB_PU &=~BIT(6)          
#define hw_ClrIRsend_Pin()              PORTB_OUT &= ~BIT(6) 
#define hw_SetIRsend_Pin()              PORTB_OUT|= BIT(6)	     			
#endif

// out  power  control
#ifdef SUPPORT_OUT_POWER_CONTROL
#ifdef OUT_POWER_DETECT_USE_PA9
#define     OUT_POWER_DET_IO_IS_IN()    PORTA_DIR |= BIT(9); PORTA_PU &= ~BIT(9); PORTA_HD &= ~BIT(9);PORTA_PD|=BIT(9);
#define     OUT_POWER_DET_READ()           PORTA_IN & BIT(9)
#endif
#endif



#define support_music_pp_state  // jsuo 20151102 add
#ifdef support_music_pp_state
extern u8  bPause_state;
#endif
#ifdef SUPPORT_MUTE_FLASH
extern bool b_muteFlag;
#endif



