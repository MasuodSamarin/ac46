#include "key_drv_ir.h"
#include "includes.h"
#include "timer.h"
#include "key.h"
#if TEST_IR_EN
#include "led7_drv.h"
#endif
#ifdef support_send_ir_code
#include "msg.h"
#endif

#ifdef DURING_FM_EXITING_TASK_NOT_RESPOND_KEY_MSG
extern u8 bExitFMStateCnt;
#endif

#if KEY_IR_EN

#define IR_FF00	 0xff00
IR_CODE  ir_code;       ///<红外遥控信息
u16 timer1_pad;

#ifdef IR_USER_KPL_001
     #include "irc_kpl_001.c"
#elif defined(IR_USER_KPL_002)
     #include "IR_USER_KPL_002.c"
#elif defined IR_USER_ty_001_FTC334M_7F80
     #include "IR_USER_ty_001_FTC334M_7F80.c"
#elif defined(IR_TY_DOUBLE_00FF_807F_23KEY)
     #include "IR_TY_DOUBLE_00FF_807F_23KEY.c"
#elif defined(IR_GW_K16_28_DF20_GENERAL_10KEY)
     #include "IR_GW_K16_28_DF20_GENERAL_10KEY.c"
#elif defined(IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_OK)
     #include "IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_OK.c"
#elif defined(IR_FF00_003_21KEY)
     #include "irc_FF00_003_21KEY.c"	 
#elif defined(IR_FF00_004_21KEY)    
     #include "IR_FF00_004_21KEY.c"	
#elif defined(IR_ZY_01FE_MP5_IR_21KEY)    
     #include "IR_ZY_01FE_MP5_IR_21KEY.c"	
#elif defined(IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_11)    
     #include "IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_11.c"	
#elif defined(IR_HX_FF00_21KEY)    
     #include "IR_HX_FF00_21KEY.c"	
#elif defined(IR_FF00_005_21KEY)    
     #include "IR_FF00_005_21KEY.c"	
#elif defined(IR_ZY_DOUBLE_GENERAL_TY_00FF_807F_22KEY)    
     #include "IR_ZY_DOUBLE_GENERAL_TY_00FF_807F_22KEY.c"	
#elif defined(IR_ZY_DOUBLE_GENERAL_YK2119_00FF_ALP102_807F_22KEY)    
     #include "IR_ZY_DOUBLE_GENERAL_YK2119_00FF_ALP102_807F_22KEY.c"	
#elif defined(IR_SSM_THREE_GENERAL_FF00_7F80_FE01_REC_7)    
     #include "IR_SSM_THREE_GENERAL_FF00_7F80_FE01.c"	
#elif defined(IR_FF00_006_21KEY)    
     #include "IR_FF00_006_21KEY.c"	
#elif defined(IR_FE01_007_26KEY)    
     #include "IR_FE01_007_26KEY.c"	
#elif defined(IR_SL_SP61P_FF00_008_21KEY)    
     #include "IR_SL_SP61P_FF00_008_21KEY.c"	
#elif defined(IR_FS_BF00_009_18KEY)    
     #include "IR_FS_BF00_009_18KEY.c"	
#elif defined(IR_TY_DOUBLE_00FF_807F_26KEY)    
     #include "IR_TY_DOUBLE_00FF_807F_26KEY.c"	
#elif defined(IR_ZY_JERRY_00FF_21KEY)    
     #include "IR_ZY_JERRY_00FF_21KEY.c"	
#elif defined(IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY)  ||defined(IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_9)   
     #include "IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY.c"	
#elif defined(IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_REC)    
     #include "IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_REC.c"	
#elif defined(IR_ZY_DOUBLE_GENERAL_00FF_807F_22KEY)    
     #include "IR_ZY_DOUBLE_GENERAL_00FF_807F_22KEY.c"	
#elif defined(IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_7)    
     #include "IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_7.c"	
#elif defined(IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_SA)    
     #include "IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_SA.c"	
#elif defined(IR_SSM_SA_00FF_IR_25KEY)    
     #include "IR_SSM_SA_00FF_IR_25KEY.c"	
#elif defined(IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_10)    
     #include "IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_10.c"	
#elif defined(IR_ZY_THREE_YK2119_FF00_807F_CF30_25KEY)    
     #include "IR_ZY_THREE_YK2119_FF00_807F_CF30_25KEY.c"	
#elif defined(IR_ZY_THREE_hd6992_FF00_807F_CF30_25KEY)    
     #include "IR_ZY_THREE_hd6992_FF00_807F_CF30_25KEY.c"	
#elif defined(IR_ZY_HD7369_807F_25KEY)    
     #include "IR_ZY_HD7369_807F_25KEY.c"	
#elif defined(IR_ZY_HD7369_807F_25KEY_2)    
     #include "IR_ZY_HD7369_807F_25KEY_2.c"	
#elif defined(IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_2)    
     #include "IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_2.c"	
#elif defined(IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_8)    
     #include "IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_8.c"	
#elif defined(IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_6)    
     #include "IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_6.c"	
#elif defined(IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_3)    
     #include "IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_3.c"	
#elif defined(IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_4)    
     #include "IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_4.c"	
#elif defined(IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_5)    
     #include "IR_ZY_DOUBLE_GENERAL_YK2119_00FF_807F_22KEY_5.c"	
#elif defined(IR_ZY_NEW_DOUBLE_GENERAL_00FF_807F_26KEY)    
     #include "IR_ZY_NEW_DOUBLE_GENERAL_00FF_807F_26KEY.c"	
#elif defined(IR_ZY_DOUBLE_GENERAL_YK2119_00FF_HD7369_807F_26KEY)    
     #include "IR_ZY_DOUBLE_GENERAL_YK2119_00FF_HD7369_807F_26KEY.c"	
#elif defined(IR_ZY_NEW_DOUBLE_GENERAL_00FF_ADJ_BRAND_807F_26KEY)    
     #include "IR_ZY_NEW_DOUBLE_GENERAL_00FF_ADJ_BRAND_807F_26KEY.c"	
#elif defined(IR_ZY_THREE_GENERAL_YK2119_00FF_807F_01FE_25KEY)    
     #include "IR_ZY_THREE_GENERAL_YK2119_00FF_807F_01FE_25KEY.c"	
#elif defined(IR_TF_THREE_GENERAL_FF00_FD02_7F80)    
     #include "IR_TF_THREE_GENERAL_FF00_FD02_7F80.c"	
#elif defined(IR_ZY_THREE_GENERAL_YK2119_00FF_807F_FE01_25KEY)    
     #include "IR_ZY_THREE_GENERAL_YK2119_00FF_807F_FE01_25KEY.c"	
#elif defined(IR_MSJ_DOUBLE_GENERAL_FF00_7F80)    
     #include "IR_MSJ_DOUBLE_GENERAL_FF00_7F80.c"	
#elif defined(IR_MSJ_THREE_FF00_7F80_FE01_SPEC_24KEY)    
     #include "IR_MSJ_THREE_FF00_7F80_FE01_SPEC_24KEY.c"	
#elif defined(IR_SSM_THREE_GENERAL_FF00_7F80_FE01)||defined(IR_SSM_THREE_GENERAL_FF00_7F80_FE01_REC_5)	||defined(IR_SSM_THREE_GENERAL_FF00_7F80_FE01_REC_1)\
	||defined(IR_SSM_THREE_GENERAL_FF00_7F80_FE01_REC) ||defined(IR_SSM_THREE_GENERAL_FF00_7F80_FE01_REC_6) \
||defined(IR_SSM_THREE_GENERAL_FF00_7F80_FE01_REC_8)	
     #include "IR_SSM_THREE_GENERAL_FF00_7F80_FE01.c"	
	 
#elif defined(IR_SSM_THREE_GENERAL_FF00_7F80_FE01_REC_2)  
     #include "IR_SSM_THREE_GENERAL_FF00_7F80_FE01_2.c"	 
#elif defined(IR_SSM_THREE_GENERAL_FF00_7F80_FE01_REC_3)  
     #include "IR_SSM_THREE_GENERAL_FF00_7F80_FE01_REC_3.c"	 
#elif defined(IR_SSM_THREE_GENERAL_FF00_7F80_FE01_REC_4)  
     #include "IR_SSM_THREE_GENERAL_FF00_7F80_FE01_REC_4.c"	 
#elif defined(IR_SSM_THREE_GENERAL_FF00_7F80_04FB_REC) 
     #include "IR_SSM_THREE_GENERAL_FF00_7F80_04FB_REC.c"	 
#elif defined(IR_SSM_THREE_GENERAL_FE01_7F80_04FB_REC) 
     #include "IR_SSM_THREE_GENERAL_FE01_7F80_04FB_REC.c"	 
#elif defined(IR_SSM_THREE_GENERAL_FF00_7F80_04FB_REC_SA) 
     #include "IR_SSM_THREE_GENERAL_FF00_7F80_04FB_REC_SA.c"	 
#elif defined(IR_SSM_THREE_GENERAL_FF00_7F80_04FB_VOICE) 
     #include "IR_SSM_THREE_GENERAL_FF00_7F80_04FB_VOICE.c"	 
#elif defined(IR_SSM_THREE_GENERAL_FF00_7F80_04FB_INTROL) 
     #include "IR_SSM_THREE_GENERAL_FF00_7F80_04FB_INTROL.c"	 
	 
#elif defined(IR_ZX_ONE_00FF_GENERAL_21KEY)    
     #include "IR_ZX_ONE_00FF_GENERAL_21KEY.c"	 
#elif defined(IR_SM_TWO_FF00_24KEY)    
     #include "IR_SM_TWO_FF00_24KEY.c"	 
#elif defined(IR_HC_ONE_GENERAL_00FF_10KEY)    
     #include "IR_HC_ONE_GENERAL_00FF_10KEY.c"	 
#elif defined(IR_GW_FF00_GENERAL_23KEY)    
     #include "IR_GW_FF00_GENERAL_23KEY.c"	 
#elif defined(IR_ZY_k16ty27_FF00_GENERAL_23KEY)    
     #include "IR_ZY_k16ty27_FF00_GENERAL_23KEY.c"	 
#elif defined(IR_ZY_k16ty27_FF00_GENERAL_23KEY_TY)    
     #include "IR_ZY_k16ty27_FF00_GENERAL_23KEY_TY.c"	 
#elif defined(IR_DJ_THREE_GENERAL_00FF_807F_24KEY)    
     #include "IR_DJ_THREE_GENERAL_00FF_807F_24KEY.c"	 
#elif defined(IR_ZX_HL601_QGN_FF00_35KEY)    
     #include "IR_ZX_HL601_QGN_FF00_35KEY.c"	 
#elif defined(IR_ZX_TY13_7F80_33KEY)    
     #include "IR_ZX_TY13_7F80_33KEY.c"	 
#elif defined(IR_ZX_HD7175_FE01_25KEY)    
     #include "IR_ZX_HD7175_FE01_25KEY.c"	 
#elif defined(IR_JH_001_FF00_22_KEY)    
     #include "IR_JH_001_FF00_22_KEY.c"	 
#elif defined(IR_GW_SA_001_FF00_21KEY)    
     #include "IR_GW_SA_001_FF00_21KEY.c"	
#elif defined(IR_USE_HL_Q1_FF00_22KEY)    
     #include "IR_USE_HL_Q1_FF00_22KEY.c"	 
#elif defined(IR_SUOAI_001_FF00_21KEY)
     #include "IR_SUOAI_001_FF00_21KEY.c"	
#elif defined(IR_SUOAI_001_FF00_21KEY_VOICE)
     #include "IR_SUOAI_001_FF00_21KEY_VOICE.c"		 
#elif defined(IR_SUOAI_001_FF00_21KEY_VOICE_1)
     #include "IR_SUOAI_001_FF00_21KEY_VOICE_1.c"		 
#elif defined(IR_XF_FF00_807F_25KEY)    
     #include "IR_XF_FF00_807F_25KEY.c"	 
#elif defined(IR_JH_FF00_GENERAL_21KEY)    
     #include "IR_JH_FF00_GENERAL_21KEY.c"	 
#else 
/*user code is 0xFF00*/
const u8 IRTabFF00[] =
{
 #if 1
 0xff
 #else
    NKEY_00, NKEY_01, NKEY_02, NKEY_03, NKEY_04, NKEY_05, NKEY_06, IR_06, IR_15, IR_08, NKEY_0A, NKEY_0B, IR_12, IR_11, NKEY_0E, NKEY_0F,
    NKEY_10, NKEY_11, NKEY_12, NKEY_13, NKEY_14, IR_07, IR_09, NKEY_17, IR_13, IR_10, NKEY_1A, NKEY_1B, IR_16, NKEY_1D, NKEY_1E, NKEY_1F,
    NKEY_20, NKEY_21, NKEY_22, NKEY_23, NKEY_24, NKEY_25, NKEY_26, NKEY_27, NKEY_28, NKEY_29, NKEY_2A, NKEY_2B, NKEY_2C, NKEY_2D, NKEY_2E, NKEY_2F,
    NKEY_30, NKEY_31, NKEY_32, NKEY_33, NKEY_34, NKEY_35, NKEY_36, NKEY_37, NKEY_38, NKEY_39, NKEY_3A, NKEY_3B, NKEY_3C, NKEY_3D, NKEY_3E, NKEY_3F,
    IR_04, NKEY_41, IR_18, IR_05, IR_03, IR_00, IR_01, IR_02, NKEY_48, NKEY_49, IR_20, NKEY_4B, NKEY_4C, NKEY_4D, NKEY_4E, NKEY_4F,
    NKEY_50, NKEY_51, IR_19, NKEY_53, NKEY_54, NKEY_55, NKEY_56, NKEY_57, NKEY_58, NKEY_59, IR_17, NKEY_5B, NKEY_5C, NKEY_5D, IR_14, NKEY_5F,
#endif
};
#endif
/*----------------------------------------------------------------------------*/
/**@brief   ad按键初始化
   @param   void
   @param   void
   @return  void
   @note    void ad_key0_init(void)
*/
/*----------------------------------------------------------------------------*/
void ir_timeout(void)
{
    ir_code.boverflow++;
    if (ir_code.boverflow > 56) //56*2ms ~= 112ms
    {
        ir_code.bState = 0;
    }
}

/*----------------------------------------------------------------------------*/
/**@brief   time1红外中断服务函数
   @param   void
   @param   void
   @return  void
   @note    void timer1_ir_isr(void)
*/
/*----------------------------------------------------------------------------*/
void timer1_isr(void)
{
    u16 bCap1;
    u8 cap = 0;
    TMR1_CON |= BIT(14);
    DSP_CLR_ILAT = BIT(TIME1_INIT);
    bCap1 = TMR1_PRD;
    TMR1_CNT =0;
    cap = bCap1 /timer1_pad;

    if (cap <= 1)
    {
        ir_code.wData >>= 1;
        ir_code.bState++;
        ir_code.boverflow = 0;
    }
    else if (cap == 2)
    {
        ir_code.wData >>= 1;
        ir_code.bState++;
        ir_code.wData |= 0x8000;
        ir_code.boverflow = 0;
    }
    /*13ms-Sync*/
    /*
    else if ((cap == 13) || (cap < 8) || (cap > 110))
    {
        ir_code.bState = 0;
    }
    else
    {
        ir_code.boverflow = 0;
    }
    */
    else if((cap == 13)&&(ir_code.boverflow < 8))
    {
        ir_code.bState = 0;
    }
    else if((cap < 8)&&(ir_code.boverflow < 5))
    {
        ir_code.bState = 0;
    }
    else if((cap >110)&&(ir_code.boverflow > 53))
    {
        ir_code.bState = 0;
    }
    else if((cap >20)&&(ir_code.boverflow > 53)) //溢出情况下 （12M 48M）
    {
        ir_code.bState = 0;
    }
    else
    {
        ir_code.boverflow = 0;
    }
    if (ir_code.bState == 16)
    {
        ir_code.wUserCode = ir_code.wData;
    }
    if (ir_code.bState == 32)
    {

    }
}
/*----------------------------------------------------------------------------*/
/**@brief   ir按键初始化
   @param   void
   @param   void
   @return  void
   @note    void set_ir_clk(void)

   ((cnt - 1)* 分频数)/lsb_clk = 1ms
*/
/*----------------------------------------------------------------------------*/
#define MAX_TIME_CNT 0x07ff //分频准确范围，更具实际情况调整
#define MIN_TIME_CNT 0x0030
void set_ir_clk(void)
{
    u32 clk;
    u32 prd_cnt;
    u8 index;

    clk = OSC_Hz;//clock_get_lsb_freq();
    //printf("\ntimer0_init---\nlsb = %u\n",clk);

    clk /=1000;
    clk *=1;//1ms for cnt

    for(index=0; index<(sizeof(timer_div)/sizeof(timer_div[0])); index++)
    {
        prd_cnt = (clk+timer_div[index])/timer_div[index];
        if(prd_cnt>MIN_TIME_CNT && prd_cnt<MAX_TIME_CNT)
        {
            break;
        }
    }

    timer1_pad = prd_cnt;
    TMR1_CON = ((index<<4)| BIT(3)|BIT(1)|BIT(0));

    //printf("-------------\ntimmer2 prd_cnt = %x\n\n\n\n\n",prd_cnt);
    //printf("timmer2 index = %x\n\n\n\n\n",index);
}

/*----------------------------------------------------------------------------*/
/**@brief   ir按键初始化
   @param   void
   @param   void
   @return  void
   @note    void ir_key_init(void)
*/
/*----------------------------------------------------------------------------*/
void ir_key_init(void)
{

#ifdef support_send_ir_code
	hw_IRsend_Pin_Init();
#endif

    //timer1
    key_puts("ir key init\n");
    INTALL_HWI(TIME1_INIT, timer1_isr, 4) ; //timer0_isr
    IRFLT_CON = 0xa1;
    IOMC0 &= ~(BIT(10)|BIT(9)|BIT(8));
    IOMC0 |= BIT(10)|BIT(8);                   //IRFLT output to timer1
    IOMC2 &= ~(BIT(13)|BIT(12)|BIT(11)|BIT(10)|BIT(9)|BIT(8));
#ifdef Ir_user_pa5
	IOMC2 |= BIT(10)|BIT(8);   // 5   0B 0101
	PORTA_DIR |= BIT(5);	
#elif defined(Ir_user_pa3)    
	IOMC2 |= BIT(9)|BIT(8);   // 5   0B 0011
	PORTA_DIR |= BIT(3);		
#elif defined(Ir_user_pa10)    
	IOMC2 |= BIT(11)|BIT(9);   // 10  0B 1010
	PORTA_DIR |= BIT(10);	
#elif defined(Ir_user_pa1)    
    IOMC2 |= BIT(8);   // 1   0B 0001
     PORTA_DIR |= BIT(1);
#elif defined(Ir_user_pa14)  //14    001110
	IOMC2 |= BIT(11)|BIT(10)|BIT(9);  
	PORTA_DIR |= BIT(14);	
#elif defined(Ir_user_pc15) 
	IOMC2 |=  BIT(13)|BIT(11)|BIT(9)|BIT(8);   // 43  0B 101011
	PORTC_DIR |= BIT(15);	
#else		
    IOMC2 |= BIT(12)|BIT(10)|BIT(9);
    PORTB_DIR |= BIT(6);
#endif
    //timer1_pad = 187;
    //TMR1_CON = BIT(0)|BIT(1)|BIT(4)|BIT(5);//

    set_ir_clk();

}

/*----------------------------------------------------------------------------*/
/**@brief   获取ir按键值
   @param   void
   @param   void
   @return  void
   @note    void get_irkey_value(void)
*/

/*----------------------------------------------------------------------------*/
tu8 get_irkey_value(void)
{
    tu8 tkey = 0xff;
	tu8 ir_code_temp = 0xff;
	
#ifdef DURING_FM_EXITING_TASK_NOT_RESPOND_KEY_MSG
			  if(bExitFMStateCnt){
			  return tkey;
			  }
#endif


    if (ir_code.bState != 32)
    {
	  #ifdef support_send_ir_code
	  	send_val=ir_code_temp;
	  	send_timer=0;
 	     vol_key_sw=0;		  	
	  #endif
        return tkey;
    }
	
    ir_code_temp = (u8)ir_code.wData;
	
#ifdef TEST_IR_CODE_MACHINE	
    ir_code_data=ir_code.wData;	
    sys_code=ir_code.wUserCode;	
    return tkey;
#endif

//	printf("111111 ir_code.bState %x \n",ir_code.bState);
// 	printf("111111 ir_code_temp %x \n",ir_code_temp);

	
    if ((((u8*)&ir_code.wData)[0] ^ ((u8*)&ir_code.wData)[1]) == 0xff)
    {
        #if TEST_IR_EN
				led7_var.testIrCode=(u8)ir_code.wData;
        #endif
    #if IR_SYS_CODE
		if (ir_code.wUserCode == IR_SYS_CODE)
    #else 	
		if (ir_code.wUserCode == 0xFF00)
    #endif 			
        {

	 #ifdef support_send_ir_code
	 #if 1
		if((workmode==AC3_WORK_MODE))	 
		  if((ir_code_temp!=0x13)&&(ir_code_temp!=0x10)&&(ir_code_temp!=0x1A)&&(ir_code_temp!=0x17)&&(ir_code_temp!=0x12))
		  	{
			  if(send_val==ir_code_temp)
			  	send_timer++;
			  else
			  	send_timer=1;	
			  
			 	send_val=ir_code_temp;
		  	}
		  else
		  {
		  	send_val=ir_code_temp;
		  	send_timer=0;
		  }
	 #else
		  if((ir_code_temp!=0x1A)&&(ir_code_temp!=0x17)&&(ir_code_temp!=0x12))
		  	{
			  if(send_val==ir_code_temp)
			  	send_timer++;
			  else
			  	send_timer=1;	
			  
			 	send_val=ir_code_temp;
		  	}
		  
		  if((ir_code_temp==0x13)||(ir_code_temp==0x10))
	 	    vol_key_sw=1;		    	
		  #endif
	 #endif
		
         if(ir_code_temp>0x20)
	 	ir_code_temp-=0X20;
       #if IR_SAME_SYSCODE_DETECT_EN
    	   #ifdef IR_DETECT_PIN_HIGHT_VALID
			 	   if(IR_DET_CHECK)
    	   #else
			 	   if(!IR_DET_CHECK)
    	   #endif
					tkey = IRTab1[ir_code_temp];
				   else
       #endif
	//	printf("ir_code.wUserCode: %x    ir_code_temp :%d  \n",ir_code.wUserCode,ir_code_temp);
	   
	         tkey = IRTab0[ir_code_temp];
           // tkey = IRTabFF00[(u8)ir_code.wData];
        }

	
 #if IR_NUMS>=2
		 else if(ir_code.wUserCode == IR_SYS_CODE1)
			 {
			  ir_code_temp=(u8)ir_code.wData;

	 	 		 #ifdef IR_USER_ty_001_FTC334M_7F80
	 	 		   if(ir_code_temp>0xA0)
	 	 			 ir_code_temp-=0X60;
	 	 		 #endif
			  
			  if(ir_code_temp>0x20)
			  ir_code_temp -=0x20;
			  tkey = IRTab1[ir_code_temp];	  
			 //  tkey = IRTab1[(u8)ir_code.wData];
			 }
#endif

 #if IR_NUMS>=3
 

#if defined IR_SSM_THREE_GENERAL_FF00_7F80_04FB_REC||defined SSM_Q535_OPTI_FE01_04FB_REC_AC4601||defined IR_SSM_THREE_GENERAL_FF00_7F80_04FB_INTROL

#if 0
/*0x20*/ IRC_PLAY_PAUSE,//68
/*0x21*/IRC_NUM9,// 78
/*0x22*/IRC_MODE,//80
/*0x23*/IRC_NUM2,//98
/*0x24*/IRC_STANBY,//c0
/*0x25*/IRC_NUM1,//d8
/*0x26*/IRC_REPEAT,//e0
/*0x27*/ IRC_NUM8,//e8
/*0x28*/IRC_NUM0,//f8
/*0x29*/IRC_PREV,//a8
/*0x2b*/IRC_NUM5,//b8

#endif

		 else if(ir_code.wUserCode == IR_SYS_CODE2)
			 {
				  ir_code_temp=(u8)ir_code.wData;
				  
				  if(ir_code_temp==0x68)
				   ir_code_temp =0x20;
				  else if(ir_code_temp==0x78)
				   ir_code_temp =0x21;
				  else if(ir_code_temp==0x80)
				   ir_code_temp =0x22;
				  else if(ir_code_temp==0x98)
				   ir_code_temp =0x23;
				  else if(ir_code_temp==0xc0)
				   ir_code_temp =0x24;
				  else if(ir_code_temp==0xd8)
				   ir_code_temp =0x25;
				  else if(ir_code_temp==0xe0)
				   ir_code_temp =0x26;
				  else if(ir_code_temp==0xe8)
				   ir_code_temp =0x27;
				  else if(ir_code_temp==0xf8)
				   ir_code_temp =0x28;
				  else if(ir_code_temp==0xa8)
				   ir_code_temp =0x29;
				  else if(ir_code_temp==0xb8)
				   ir_code_temp =0x2b;				  
				  
				  tkey = IRTab2[ir_code_temp];	  
			 }		 
#else
		 else if(ir_code.wUserCode == IR_SYS_CODE2)
			 {
			  ir_code_temp=(u8)ir_code.wData;
			  if(ir_code_temp>0x20)
			  ir_code_temp -=0x20;
			  tkey = IRTab2[ir_code_temp];	  
			 //  tkey = IRTab1[(u8)ir_code.wData];
			 }
#endif		 
#endif
    }
    else
    {
        ir_code.bState = 0;
    }
    return tkey;
}
#else
void timer1_isr(void)
{

}
#endif/*KEY_IR_EN*/
