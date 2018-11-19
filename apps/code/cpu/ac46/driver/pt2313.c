/***********************************************************************************************
 *	Processer :
 *	Compiler :
 *	File:
 *	Description:
 *	Date: 2012.07.30
 *	Author :	fengxu
***********************************************************************************************/

#define _AUDIO_2313_C_
#include "config.h"

 #include "m62429.h"

/*
 PIN9-R3 PIN10-R2 PIN11-R1 
 PIN13-L3 PIN14-L2 PIN15-L1 
 0X02 	    0X01 		0X00
 */
 

#ifdef SUPPORT_PT2313
#include "msg.h"
#include "os_api.h"

#include "pt2313.h"
//#include "iic.h"
//extern void iic_init(void);

#define PT2313_iic_delay()      delay(20)
#ifdef supper_jc_dm_8008_panel
extern u8 vol_zero_flagh;   
#endif
#ifdef SWVOL_LED_SHOW_MAX
extern u8 swvol_temp_vol;
#endif

#ifdef SUPPORT_PT2314
bool pt2314_flag;
#endif


#ifdef SUPPORT_PT2314
const unsigned char PT2314Tab[7][2]=
{
    {AudAdd_VOL,AudVOLMAX},
    {AudAdd_RL,AudswLMAX},
    {AudAdd_RR,AudswLMAX},
    {AudAdd_FL,AudBALMAX},
    {AudAdd_FR,AudBALMAX},   
    {AudAdd_BASS,MAX_TONE},
    {AudAdd_TREB,MAX_TONE}
};
#endif


#if 1//defined  MUSIC_APP || defined (RECORDE_APP)|| defined (BLUETOOTH_APP)|| defined (MAIN_APP)

void  PT2313_init_io(void)
{
    PT2313_data_out();         //SDA设置成输出
    PT2313_clk_out();         //SCL设置成输出
    PT2313_data_h();
    PT2313_clk_h();
}

/*----------------------------------------------------------------------------*/
/**@brief   读取ACK
   @param   无
   @return  都会的ACK/NACK的电平
   @note    bool r_ack(void)
*/
/*----------------------------------------------------------------------------*/
void  PT2313iic_start(void)
{
    PT2313_init_io();
    PT2313_iic_delay();
    PT2313_data_l();
    PT2313_iic_delay();
    PT2313_clk_l();
    PT2313_iic_delay();
    PT2313_data_h();
}

/*----------------------------------------------------------------------------*/
/**@brief   STOP IIC
   @param   无
   @return  无
   @note    void iic_stop(void)
*/
/*----------------------------------------------------------------------------*/
void PT2313iic_stop(void)
{
    PT2313_data_out();
    PT2313_data_l();
    PT2313_iic_delay();
    PT2313_clk_h();
    PT2313_iic_delay();
    PT2313_data_h();
    PT2313_iic_delay();
}
#if 1
/*----------------------------------------------------------------------------*/
/**@brief   读取ACK
   @param   无
   @return  都会的ACK/NACK的电平
   @note    bool r_ack(void)
*/
/*----------------------------------------------------------------------------*/
u8  PT2313r_ack(void)
{
    u8 nack;
    PT2313_data_in();
    PT2313_iic_delay();
    PT2313_clk_h();
    PT2313_iic_delay();
    PT2313_iic_delay();
    PT2313_iic_delay();
    PT2313_iic_delay();
    PT2313_iic_delay();
    nack =  PT2313_data();
    PT2313_clk_l();
    PT2313_iic_delay();
    return nack;
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief   向IIC总线发送一个BYTE的数据
   @param   byte ：要写的EEROM的地址
   @return  无
   @note    void iic_sendbyte_io(u8 byte)
*/
/*----------------------------------------------------------------------------*/
void  PT2313iic_sendbyte(u8 byte)
{
    u8 i;
    PT2313_data_out();
    PT2313_iic_delay();
    for (i = 0; i < 8; i++)
    {
        if (byte & BIT(7))
            PT2313_data_h();                //最高位是否为1,为1则SDA= 1,否则 SDA=0
        else
            PT2313_data_l();
        PT2313_iic_delay();
        PT2313_clk_h();
        PT2313_iic_delay();
        byte <<= 1;                   //数据左移一位,进入下一轮送数
        PT2313_clk_l();
    }
    PT2313r_ack();
}

void AUD_Write(unsigned char Data)
{
    /*unsigned char bResult;
    StartI2c();
    bResult =I2Cm_TxData(Aud_PT72313Adr);
    bResult =I2Cm_TxData(Data);
    StopI2c();
    Wait1ms(2);	*/

    PT2313iic_start();                //I2C启动
    PT2313iic_sendbyte(Aud_PT2313Adr);         //写命令
    PT2313iic_sendbyte(Data);
    PT2313iic_stop();                 //I2C停止时序


    //iic_write(Aud_PT2313Adr,0xff,&Data,1);
}
#if 0
extern void  iic_write(u8 chip_id,u8 iic_addr,u8 *iic_dat,u8 n);

void AUD_Write(unsigned char Data)
{
    iic_write(Aud_PT2313Adr,0xff,&Data,1);
}
#endif



extern unsigned char pt2313data[8];

u8  pt2313_eq_mode;

bool pt2313loud;

#define PT2313SUBADDR	0
#define PT2313VALMAX	1

#ifndef AUD_EqMAX
#define AUD_EqMAX			4
#endif
const unsigned char PT2313Tab[7][2]=
{
    {AudAdd_VOL,AudVOLMAX},
    {AudAdd_RL,AudswLMAX},
    {AudAdd_RR,AudswLMAX},
    {AudAdd_FL,AudBALMAX},
    {AudAdd_FR,AudBALMAX},   
    {AudAdd_BASS,MAX_TONE},
    {AudAdd_TREB,MAX_TONE}
};

const unsigned char Pt2313EQTable[9][2]=
{
    {7,7},
    {8,14},
    {5,12},
    {3,8},
    {7,12},
    {13,10},
    {13,14},
    {2,12},
    {5,8}
};

#if defined( JC_2271_TW1628_PT2313_62429)
u8  PT2313VolChange(u8 cvol)
{
    u8 temp;
    if (cvol==0)
        temp=0x3F;
    else if (cvol==1)
        temp=0x3A;
    else if (cvol<35)
        temp=57-cvol;
    else if (cvol<80)
    {
        temp=23-(cvol-34)/2;
    }
    else
        temp=0;
    return temp;
}
#endif

// 41--82(21----62)      1--41  (1-20 2+)
// 0--25==0--30   26--83==30--60     20160620 modify
#if defined(AZS_AZS020_AC4601)
u8 PT2313VolChange(u8 cvol)
{
	u8 temp;
	if(cvol==0)
		temp=63;
	else if(cvol<=100)
	        temp=63-cvol*3/5;
	else
		temp=3;
	return temp;
}

u8 PT2313SubChange(u8 cvol)
{
	u8 temp;
	if(cvol==0)
		temp=31;
	else if(cvol<=100)
	        temp=31-cvol*31/100;
	else
		temp=0;
	return temp;
}

#else
u8 PT2313VolChange(u8 cvol)
{
    u8 temp;
    if (cvol==0)
        temp=0x3F;
    else if (cvol==1)
        temp=0x3B;
    else
        temp=0x3F-cvol;

#if 0//def SUPPORT_ENCODE_flash_led
	if(cvol==0)
                ENCODE_flash_led_time=1;
	else
		{
                ENCODE_flash_led_time=0;		
		 #ifdef supper_jc_dm_8008_panel				
			 vol_zero_flagh=1;				
		 #endif
		}
#endif				

    return temp;
}
#endif






// PT_VOL_NOMAL	0x00     PT_VOL_UP	0x01       PT_VOL_DN		0x02
// PT_RL_NOMAL	0x03     PT_RL_UP		0x04       PT_RL_DN	      0x05
// PT_RR_NOMAL	0x06     PT_RR_UP		 0x07      PT_RR_DN		0x08
// PT_FL_NOMAL	0x09     PT_FL_UP	        0x0A      PT_FL_DN		0x0B
// PT_FR_NOMAL	0x0C    PT_FR_UP		0x0D       PT_FR_DN		0x0E
// PT_BASS_NOMAL	0x0F    PT_BASS_UP		0x10    PT_BASS_DN		0x11
// PT_TREB_NOMAL	0x12    PT_TREB_UP		0x13   PT_TREB_DN		0x14
#ifdef SUPPORT_PT2314
void AT(.PT2313) PT2314SetData(unsigned char dir,unsigned char snum)
{
    unsigned char tempdir,tempy,tempdata,i;

    tempy=dir/3;
    tempdir=dir%3;

	pt2314_flag=1;
    
    for (i=0; i<snum; i++)
    {
        if (tempdir==1)
        {
            if (pt2314data[tempy]<PT2314Tab[tempy][PT2313VALMAX])
                pt2314data[tempy]++;
        }
        else if (tempdir==2)
        {
            if (pt2314data[tempy]>0)
            {
                pt2314data[tempy]--;
            }
        }


        if (tempy==PT_VOLUME)
            tempdata=PT2313VolChange(pt2314data[tempy]);
        else

                if (tempy<PT_BASS)
                    tempdata=PT2314Tab[tempy][PT2313VALMAX]-pt2314data[tempy];
               else if (tempy==PT_BASS)
		   {
	                 if(pt2314data[tempy]<=2)
	                    tempdata=2;		   
	                else if(pt2314data[tempy]<8)
	                    tempdata=pt2314data[tempy];
	                else if(pt2314data[tempy]>=12)
	                    tempdata=10;                    
	                else
	                    tempdata=22-pt2314data[tempy];
                   }
		else if(pt2314data[tempy]<8)
			tempdata=pt2314data[tempy];
		else
			tempdata=22-pt2314data[tempy];                

	  
        tempdata|=PT2314Tab[tempy][PT2313SUBADDR];

        AUD_Write(tempdata);

        tempy++;
    }
	pt2314_flag=0;    
}
#endif


void  PT2313SetData(unsigned char dir,unsigned char snum)
{
    unsigned char tempdir,tempy,tempdata,i;


    tempy=dir/3;
    tempdir=dir%3;
#if SWVOL_LED_SHOW_MAX==62
	  if(tempy==PT_RL){
		 if(tempdir==1){
		 if(swvol_temp_vol<SWVOL_LED_SHOW_MAX)
			 swvol_temp_vol++;
		 if(swvol_temp_vol>=61)return;
		 if(swvol_temp_vol%2 !=0)return;
		 }
		 else if(tempdir==2){
			 if(swvol_temp_vol>0)
			 swvol_temp_vol--;
			 if(swvol_temp_vol%2 !=0)return;
			}
		 }
#endif
    for (i=0; i<snum; i++)
    {
        if (tempdir==1)
        {   
            if (pt2313data[tempy]<PT2313Tab[tempy][PT2313VALMAX])
                pt2313data[tempy]++;
            //	if(pt2313data[0]==1)   //muzhe add  20121029  pt2313 max vol ctrl
            //	dac_mute(0,1);
        }
        else if (tempdir==2)
        {
            if (pt2313data[tempy]>0)
            {
                pt2313data[tempy]--;
                //	if(pt2313data[0]==0)  //muzhe add  20121029  pt2313 max vol ctrl
                //    dac_mute(1,1);
            }
        }



//     puts("\n 1:");
//    put_u16hex(pt2313data[tempy]);
//     puts("\n tempy:");
//    put_u16hex(tempy);

#if 1//defined( JC_2271_TW1628_PT2313_62429)
        if (tempy==PT_VOLUME)
            tempdata=PT2313VolChange(pt2313data[tempy]);
        else
#endif
#ifdef SWVOL_MAX
            if (tempy==PT_RL ||tempy==PT_RR)
                tempdata=PT2313SubChange(pt2313data[tempy]);
            else
#endif
//-7 6 5 4 3 2 1 0 1 2 3 4 5 6 7 
//0 1 2 3 4 5 6 7  8 9 10 11 12 13 14
//0 1 2 3 4 5 6 7 14 13 12 11 10 9 8

                if (tempy<PT_BASS)
                    tempdata=PT2313Tab[tempy][PT2313VALMAX]-pt2313data[tempy];
#if 1//def gw_911bt_ne
               else if (tempy==PT_BASS)
		   {
	                 if(pt2313data[tempy]<=2)
	                    tempdata=2;		   
	                else if(pt2313data[tempy]<8)
	                    tempdata=pt2313data[tempy];
	                else if(pt2313data[tempy]>=12)
	                    tempdata=10;                    
	                else
	                    tempdata=22-pt2313data[tempy];

			 #ifdef SUPPORT_BASS_TREB_VM	   						 
			 	vm_write_api(VM_BASS,&pt2313data[PT_BASS]);
			 	os_time_dly(1);
			 #endif					
                   }
               else if (tempy==PT_TREB)
		   {
	                 if(pt2313data[tempy]<=2)
	                    tempdata=2;		   
	                else if(pt2313data[tempy]<8)
	                    tempdata=pt2313data[tempy];
	                else if(pt2313data[tempy]>=12)
	                    tempdata=10;                    
	                else
	                    tempdata=22-pt2313data[tempy];
			 #ifdef SUPPORT_BASS_TREB_VM	   
			 	vm_write_api(VM_TREBL,&pt2313data[PT_TREB]);
			 	os_time_dly(1);
			 #endif
					
                   }
			   
		else if(pt2313data[tempy]<8)
			tempdata=pt2313data[tempy];
		else
			tempdata=22-pt2313data[tempy];                
#else
                else if(pt2313data[tempy]<8)
                    tempdata=pt2313data[tempy];
                else
                    tempdata=22-pt2313data[tempy];
#endif

        puts("\n 2:");

  	  put_u16hex(tempdata);
	  
        tempdata|=PT2313Tab[tempy][PT2313SUBADDR];


        AUD_Write(tempdata);

        tempy++;
    }
}

void  PT2313Mute(unsigned char OnOff)
{
	
    if(OnOff)
    {
        AUD_Write(Aud_FLMuteVal);		// FL MUTE
        AUD_Write(Aud_FRMuteVal);		//FR MUTE
        AUD_Write(Aud_RLMuteVal);		//RL	MUTE
        AUD_Write(Aud_RRMuteVal);		//RR MUTE
    }
    else
    {
        PT2313SetData(PT_RL_NOMAL,4);
    }
}

void AUD_SetLoud(bool OnOff)
{
    if(OnOff)
    {
        pt2313data[PT_SWITCH] &= ~Aud_SwLoud;   //开响度   BIT3  清0
    }
    else
    {
        pt2313data[PT_SWITCH]|=Aud_SwLoud;      //关响度   BIT3  SET 1

    }
    AUD_Write(pt2313data[PT_SWITCH]);
}


void  PT2313_SetVol(unsigned char AUD_VolVal)
{
    unsigned char Temp;

#if 1//defined( JC_2271_TW1628_PT2313_62429)
    Temp=PT2313VolChange(AUD_VolVal);
#else
    Temp=0x3F-AUD_VolVal;
#endif
    AUD_Write(Temp);
}

void  Pt2313_ChangSource(u8 I_curmode)
{

#ifdef SUPPORT_PT2314
	pt2314_flag=0;
#endif

    pt2313data[PT_SWITCH]&=0xfC;
    pt2313data[PT_SWITCH]|=I_curmode;
    if (Aud_SwAUX==I_curmode)
        pt2313data[PT_SWITCH]|=0x08;
    else
        pt2313data[PT_SWITCH]&=0xf7;

    AUD_Write(pt2313data[PT_SWITCH]);
	
}

//extern u8 _xdata my_music_vol;

void  PT2313_Init(void)
{
 #ifdef SUPPORT_BASS_TREB_VM	
 
 u8 bass_val,trebl_val;
#endif
    //     iic_init();
 #ifdef gw_911bt_ne
 	pt2313data[PT_VOLUME]=31;
 	pt2313data[PT_RL]=31;
 	pt2313data[PT_RR]=31;
 	pt2313data[PT_FL]=31;
 	pt2313data[PT_FR]=31;
 	pt2313data[PT_BASS]=7;
 	pt2313data[PT_TREB]=10;
 	pt2313data[PT_SWITCH]=0x47;   //0x47   +11.25db  通道4(空)  响度关
 #else
	 #ifdef LED_AUTO_SHOW_VOL_FROM_ZERO_TO_DEFAULT
	 	pt2313data[PT_VOLUME]=0;
	 #else
	 	pt2313data[PT_VOLUME]=VOLUME_DEFUALT;
	 #endif
 	pt2313data[PT_RL]=SWVOL_DEFUALT;
 	pt2313data[PT_RR]=SWVOL_DEFUALT;
 	pt2313data[PT_FL]=FLFR_DEFUALT;
 	pt2313data[PT_FR]=FLFR_DEFUALT;
	
 #ifdef SUPPORT_BASS_TREB_VM	
 

	vm_read_api(VM_BASS,&bass_val);
	os_time_dly(2);	  
	 
	if(bass_val>MAX_TONE)	
	 	pt2313data[PT_BASS]=BASS_DEFAULT;
	else
	 	pt2313data[PT_BASS]=bass_val;
	
	vm_read_api(VM_TREBL,&trebl_val);
	os_time_dly(2);

	if(trebl_val>MAX_TONE)	
 		pt2313data[PT_TREB]=TREBLE_DEFAULT;
	else
	 	pt2313data[PT_TREB]=trebl_val;
		
#else	
	#ifdef BASS_DEFAULT
 	pt2313data[PT_BASS]=BASS_DEFAULT;
	#else
 	pt2313data[PT_BASS]=7;
	#endif
	#ifdef TREBLE_DEFAULT
 	pt2313data[PT_TREB]=TREBLE_DEFAULT;
	#else
 	pt2313data[PT_TREB]=7;
	#endif
#endif

 	pt2313data[PT_SWITCH]=0x47;   //0x47   +11.25db  通道4(空)  响度关
 #endif

    PT2313SetData(PT_VOL_NOMAL,8);

#ifdef SUPPORT_PT2314
	pt2314data[PT_VOLUME]=60;
	pt2314data[PT_RL]=15;
	pt2314data[PT_RR]=15;
	pt2314data[PT_FL]=15;
	pt2314data[PT_FR]=15;	
	pt2314data[PT_BASS]=7;
	pt2314data[PT_TREB]=7;
	pt2314data[PT_SWITCH]=0x47;   //0x47   +11.25db  通道4(空)  响度关
	PT2314SetData(PT_VOL_NOMAL,8);
//	pt2314_flag=0;
#endif

    //menumode=MENU_SWVOL;
    //  PT2313MenuPro(0);

}

void  PT2313_reset(void)
{
    pt2313data[PT_VOLUME]=VOLUME_DEFUALT;
    pt2313data[PT_RL]=SWVOL_DEFUALT;
    pt2313data[PT_RR]=SWVOL_DEFUALT;
    #ifdef HY_MK_JL2_V20
    pt2313data[PT_BASS]=BASS_DEFAULT;//Pt2313EQTable[pt2313_eq_mode][0];
    pt2313data[PT_TREB]=TREBLE_DEFAULT;//Pt2313EQTable[pt2313_eq_mode][1];
    #else
    pt2313data[PT_BASS]=Pt2313EQTable[pt2313_eq_mode][0];
    pt2313data[PT_TREB]=Pt2313EQTable[pt2313_eq_mode][1];
   #endif
    PT2313SetData(PT_VOL_NOMAL,8);

#ifdef SUPPORT_PT2314
	pt2314data[PT_VOLUME]=60;
	pt2314data[PT_RL]=15;
	pt2314data[PT_RR]=15;
	pt2314data[PT_FL]=15;
	pt2314data[PT_FR]=15;	
	pt2314data[PT_BASS]=7;
	pt2314data[PT_TREB]=7;
	pt2314data[PT_SWITCH]=0x47;   //0x47   +11.25db  通道4(空)  响度关
	PT2314SetData(PT_VOL_NOMAL,8);
	//	pt2314_flag=0;
#endif
    
}


void  PT2313SetEQ(unsigned char dir)
{
    if (dir)
    {
        if(pt2313_eq_mode>=AUD_EqMAX)
            pt2313_eq_mode=0;
        else
            pt2313_eq_mode++;
    }
    pt2313data[PT_BASS]=Pt2313EQTable[pt2313_eq_mode][0];
    pt2313data[PT_TREB]=Pt2313EQTable[pt2313_eq_mode][1];
    PT2313SetData(PT_BASS_NOMAL,2);
}


/*
const unsigned char PT2313MenuTab[4]=
{
	PT_VOL_NOMAL,PT_TREB_NOMAL,PT_BASS_NOMAL,PT_RL_NOMAL
};
*/

void  PT2313MenuPro(unsigned char dir)
{
    unsigned char tempdir;

//	tempdir=PT2313MenuTab[menumode]+dir;
//	if (menumode==MENU_SWVOLL_MODE)
    //	PT2313SetData(tempdir,2);
//	else

    PT2313SetData(tempdir,1);


}

void PT2313_KEY_PROCESS(u8 menuMode,bool volPlusMinus)
{
  u8 vol_dir=0,adj_num=1;
  switch(menuMode){
     case MENU_MAIN_VOL_MODE:
	     if(volPlusMinus)
	       vol_dir=PT_VOL_UP;
	     else
		   vol_dir=PT_VOL_DN;		   
	     break;
     case MENU_SL_MODE:
	     if(volPlusMinus)
	       vol_dir=PT_RL_UP;
	     else
		   vol_dir=PT_RL_DN;
     break;
     case MENU_SR_MODE:
	     if(volPlusMinus)
	       vol_dir=PT_RR_UP;
	     else
		   vol_dir=PT_RR_DN;
	     break;
	 case MENU_FRONT_LEFT_MODE:
		 if(volPlusMinus)
		   vol_dir=PT_FL_UP;
		 else
		   vol_dir=PT_FL_DN;
		 break;
	 case MENU_FRONT_RIGHT_MODE:
		 if(volPlusMinus)
		   vol_dir=PT_FR_UP;
		 else
		   vol_dir=PT_FR_DN;
		 break;
  #ifdef Support_MSG_BASS
	case MENU_BASS_MODE:
		if(volPlusMinus)
		  vol_dir=PT_BASS_UP;
		else
		  vol_dir=PT_BASS_DN;
	    break;
  #endif
  #ifdef Support_MSG_TREBLE
	case MENU_TREBLE_MODE:
		if(volPlusMinus)
		  vol_dir=PT_TREB_UP;
		else
		  vol_dir=PT_TREB_DN;
		break;
  #endif
  #ifdef Support_MSG_SWVOL
	case MENU_SWVOLL_MODE:
      #ifdef pt2313_use_rf_lf_as_sub	// 0x0a    
		if(volPlusMinus)
		  vol_dir=PT_FL_UP;
		else
		  vol_dir=PT_FL_DN;
      #else
	   if(volPlusMinus)
		 vol_dir=PT_RL_UP;
	   else
		 vol_dir=PT_RL_DN;
     #endif		 
       adj_num=2;
	   break;
  #endif
  #ifdef Support_MSG_MIC_ECO_VOL_KEY
    case MENU_OK_VOL_MODE:
	  if(volPlusMinus)
	  os_taskq_post("MainTask", 1, MSG_MIC_UP);
	  else
	  os_taskq_post("MainTask", 1, MSG_MIC_DN);
      break;
    case MENU_ECHO_MODE:
		if(volPlusMinus)
		os_taskq_post("MainTask", 1, MSG_ECHO_UP);
		else
		os_taskq_post("MainTask", 1, MSG_ECHO_DN);
      break;
  #endif
  }
#ifdef Support_MSG_MIC_ECO_VOL_KEY
  if((menuMode!=MENU_OK_VOL_MODE) && (MENU_OK_VOL_MODE!=MENU_ECHO_MODE))
#endif  
  PT2313SetData(vol_dir,adj_num);

}
#else

void AT(.comm)  PT2313_init_io(void)
{
    PT2313_data_out();         //SDA设置成输出
    PT2313_clk_out();         //SCL设置成输出
    PT2313_data_h();
    PT2313_clk_h();
}

/*----------------------------------------------------------------------------*/
/**@brief   读取ACK
   @param   无
   @return  都会的ACK/NACK的电平
   @note    bool r_ack(void)
*/
/*----------------------------------------------------------------------------*/
void  AT(.comm)  PT2313iic_start(void)
{
    PT2313_init_io();
    PT2313_iic_delay();
    PT2313_data_l();
    PT2313_iic_delay();
    PT2313_clk_l();
    PT2313_iic_delay();
    PT2313_data_h();
}

/*----------------------------------------------------------------------------*/
/**@brief   STOP IIC
   @param   无
   @return  无
   @note    void iic_stop(void)
*/
/*----------------------------------------------------------------------------*/
void  AT(.comm)  PT2313iic_stop(void)
{
    PT2313_data_out();
    PT2313_data_l();
    PT2313_iic_delay();
    PT2313_clk_h();
    PT2313_iic_delay();
    PT2313_data_h();
    PT2313_iic_delay();
}
#if 1
/*----------------------------------------------------------------------------*/
/**@brief   读取ACK
   @param   无
   @return  都会的ACK/NACK的电平
   @note    bool r_ack(void)
*/
/*----------------------------------------------------------------------------*/
u8  AT(.comm)  PT2313r_ack(void)
{
    u8 nack;
    PT2313_data_in();
    PT2313_iic_delay();
    PT2313_clk_h();
    PT2313_iic_delay();
    PT2313_iic_delay();
    PT2313_iic_delay();
    PT2313_iic_delay();
    PT2313_iic_delay();
    nack =  PT2313_data();
    PT2313_clk_l();
    PT2313_iic_delay();
    return nack;
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief   向IIC总线发送一个BYTE的数据
   @param   byte ：要写的EEROM的地址
   @return  无
   @note    void iic_sendbyte_io(u8 byte)
*/
/*----------------------------------------------------------------------------*/
void AT(.comm) PT2313iic_sendbyte(u8 byte)
{
    u8 i;
    PT2313_data_out();
    PT2313_iic_delay();
    for (i = 0; i < 8; i++)
    {
        if (byte & BIT(7))
            PT2313_data_h();                //最高位是否为1,为1则SDA= 1,否则 SDA=0
        else
            PT2313_data_l();
        PT2313_iic_delay();
        PT2313_clk_h();
        PT2313_iic_delay();
        byte <<= 1;                   //数据左移一位,进入下一轮送数
        PT2313_clk_l();
    }
    PT2313r_ack();
}

void AT(.comm) AUD_Write(unsigned char Data)
{
    /*unsigned char bResult;
    StartI2c();
    bResult =I2Cm_TxData(Aud_PT72313Adr);
    bResult =I2Cm_TxData(Data);
    StopI2c();
    Wait1ms(2);	*/

    PT2313iic_start();                //I2C启动
    PT2313iic_sendbyte(Aud_PT2313Adr);         //写命令
    PT2313iic_sendbyte(Data);
    PT2313iic_stop();                 //I2C停止时序


    //iic_write(Aud_PT2313Adr,0xff,&Data,1);
}
#if 0
extern void  iic_write(u8 chip_id,u8 iic_addr,u8 *iic_dat,u8 n);

void AUD_Write(unsigned char Data)
{
    iic_write(Aud_PT2313Adr,0xff,&Data,1);
}
#endif



extern unsigned char pt2313data[8];

u8  pt2313_eq_mode;

bool pt2313loud;

#define PT2313SUBADDR	0
#define PT2313VALMAX	1

#ifndef AUD_EqMAX
#define AUD_EqMAX			4
#endif
const unsigned char PT2313Tab[7][2]=
{
    {AudAdd_VOL,AudVOLMAX},
    {AudAdd_RL,AudswLMAX},
    {AudAdd_RR,AudswLMAX},
    {AudAdd_FL,AudBALMAX},
    {AudAdd_FR,AudBALMAX},   
    {AudAdd_BASS,MAX_TONE},
    {AudAdd_TREB,MAX_TONE}
};


const unsigned char Pt2313EQTable[9][2]=
{
    {7,7},
    {8,14},
    {5,12},
    {3,8},
    {7,12},
    {13,10},
    {13,14},
    {2,12},
    {5,8}
};

#if defined( JC_2271_TW1628_PT2313_62429)
u8 AT(.comm)  PT2313VolChange(u8 cvol)
{
    u8 temp;
    if (cvol==0)
        temp=0x3F;
    else if (cvol==1)
        temp=0x3A;
    else if (cvol<35)
        temp=57-cvol;
    else if (cvol<80)
    {
        temp=23-(cvol-34)/2;
    }
    else
        temp=0;
    return temp;
}
#endif

#if 1//def CUSTOM_JLH
u8 PT2313VolChange(u8 cvol)
{
    u8 temp;
    if (cvol==0)
        temp=0x3F;
    else if (cvol==1)
        temp=0x3B;
    else
        temp=0x3F-cvol;

#if 0//def SUPPORT_ENCODE_flash_led
	if(cvol==0)
                ENCODE_flash_led_time=1;
	else
		{
                ENCODE_flash_led_time=0;		
		 #ifdef supper_jc_dm_8008_panel				
			 vol_zero_flagh=1;				
		 #endif
		}
#endif				

    return temp;
}
#endif





#ifdef SUPPORT_PT2314

void AT(.comm) PT2314SetData(unsigned char dir,unsigned char snum)
{
    unsigned char tempdir,tempy,tempdata,i;

    tempy=dir/3;
    tempdir=dir%3;

	pt2314_flag=1;
    
    for (i=0; i<snum; i++)
    {
        if (tempdir==1)
        {
            if (pt2314data[tempy]<PT2314Tab[tempy][PT2313VALMAX])
                pt2314data[tempy]++;
        }
        else if (tempdir==2)
        {
            if (pt2314data[tempy]>0)
            {
                pt2314data[tempy]--;
            }
        }


        if (tempy==PT_VOLUME)
            tempdata=PT2313VolChange(pt2314data[tempy]);
        else

                if (tempy<PT_BASS)
                    tempdata=PT2314Tab[tempy][PT2313VALMAX]-pt2314data[tempy];
               else if (tempy==PT_BASS)
		   {
	                 if(pt2314data[tempy]<=2)
	                    tempdata=2;		   
	                else if(pt2314data[tempy]<8)
	                    tempdata=pt2314data[tempy];
	                else if(pt2314data[tempy]>=12)
	                    tempdata=10;                    
	                else
	                    tempdata=22-pt2314data[tempy];
                   }
		else if(pt2314data[tempy]<8)
			tempdata=pt2314data[tempy];
		else
			tempdata=22-pt2314data[tempy];                

	  
        tempdata|=PT2314Tab[tempy][PT2313SUBADDR];

        AUD_Write(tempdata);

        tempy++;
    }
	pt2314_flag=0;    
}
#endif

void AT(.comm) PT2313SetData(unsigned char dir,unsigned char snum)
{
    unsigned char tempdir,tempy,tempdata,i;


    tempy=dir/3;
    tempdir=dir%3;
	
   #if SWVOL_LED_SHOW_MAX==62
	 if(tempy==PT_RL){
	 	if(tempdir==1){
		if(swvol_temp_vol<SWVOL_LED_SHOW_MAX)
			swvol_temp_vol++;
		if(swvol_temp_vol>=61)return;
		if(swvol_temp_vol%2 !=0)return;
		}
		else if(tempdir==2){
			if(swvol_temp_vol>0)
			swvol_temp_vol--;
			if(swvol_temp_vol%2 !=0)return;
		   }
		}
   #endif

    for (i=0; i<snum; i++)
    {
        if (tempdir==1)
        {   
            if (pt2313data[tempy]<PT2313Tab[tempy][PT2313VALMAX])
                pt2313data[tempy]++;
            //	if(pt2313data[0]==1)   //muzhe add  20121029  pt2313 max vol ctrl
            //	dac_mute(0,1);
        }
        else if (tempdir==2)
        {
            if (pt2313data[tempy]>0)
            {
                pt2313data[tempy]--;
                //	if(pt2313data[0]==0)  //muzhe add  20121029  pt2313 max vol ctrl
                //    dac_mute(1,1);
            }
        }



//     puts("\n 1:");
//    put_u16hex(pt2313data[tempy]);
//     puts("\n tempy:");
//    put_u16hex(tempy);

#if 1//defined( JC_2271_TW1628_PT2313_62429)
        if (tempy==PT_VOLUME)
            tempdata=PT2313VolChange(pt2313data[tempy]);
        else
#endif
#if  0//AudswLMAX== 62
            if (tempy==PT_RL ||tempy==PT_RR)
                tempdata=(PT2313Tab[tempy][PT2313VALMAX]-pt2313data[tempy])/2;
            else
#endif
//-7 6 5 4 3 2 1 0 1 2 3 4 5 6 7 
//0 1 2 3 4 5 6 7  8 9 10 11 12 13 14
//0 1 2 3 4 5 6 7 14 13 12 11 10 9 8

                if (tempy<PT_BASS)
                    tempdata=PT2313Tab[tempy][PT2313VALMAX]-pt2313data[tempy];
#if 1//def gw_911bt_ne
               else if (tempy==PT_BASS)
		   {
	                 if(pt2313data[tempy]<=2)
	                    tempdata=2;		   
	                else if(pt2313data[tempy]<8)
	                    tempdata=pt2313data[tempy];
	                else if(pt2313data[tempy]>=12)
	                    tempdata=10;                    
	                else
	                    tempdata=22-pt2313data[tempy];
                   }
		else if(pt2313data[tempy]<8)
			tempdata=pt2313data[tempy];
		else
			tempdata=22-pt2313data[tempy];                
#else
                else if(pt2313data[tempy]<8)
                    tempdata=pt2313data[tempy];
                else
                    tempdata=22-pt2313data[tempy];
#endif

        puts("\n 2:");

  	  put_u16hex(tempdata);
	  
        tempdata|=PT2313Tab[tempy][PT2313SUBADDR];


        AUD_Write(tempdata);

        tempy++;
    }
}

void AT(.comm) PT2313Mute(unsigned char OnOff)
{
    if(OnOff)
    {
       #if 0
        AUD_Write(Aud_FLMuteVal);		// FL MUTE
        AUD_Write(Aud_FRMuteVal);		//FR MUTE
        AUD_Write(Aud_RLMuteVal);		//RL	MUTE
        AUD_Write(Aud_RRMuteVal);		//RR MUTE
	#endif
	Pt2313_ChangSource(Aud_SwNoting);

    }
    else
    {
	 Pt2313_ChangSource(Aud_SwAUX);
     //   PT2313SetData(PT_RL_NOMAL,4);
    }
}

void AT(.comm) AUD_SetLoud(bool OnOff)
{
    if(OnOff)
    {
        pt2313data[PT_SWITCH] &= ~Aud_SwLoud;   //开响度   BIT3  清0
    }
    else
    {
        pt2313data[PT_SWITCH]|=Aud_SwLoud;      //关响度   BIT3  SET 1

    }
    AUD_Write(pt2313data[PT_SWITCH]);
}


void AT(.comm) PT2313_SetVol(unsigned char AUD_VolVal)
{
    unsigned char Temp;

#if 1//defined( JC_2271_TW1628_PT2313_62429)
    Temp=PT2313VolChange(AUD_VolVal);
#else
    Temp=0x3F-AUD_VolVal;
#endif
    AUD_Write(Temp);
}

void AT(.comm) Pt2313_ChangSource(u8 I_curmode)
{

    pt2313data[PT_SWITCH]&=0xfC;
    pt2313data[PT_SWITCH]|=I_curmode;
    if (Aud_SwAUX==I_curmode)
        pt2313data[PT_SWITCH]|=0x08;
    else
        pt2313data[PT_SWITCH]&=0xf7;

    AUD_Write(pt2313data[PT_SWITCH]);
	
}

//extern u8 _xdata my_music_vol;

void AT(.comm) PT2313_Init(void)
{
	//     iic_init();
#ifdef gw_911bt_ne
	pt2313data[PT_VOLUME]=31;
	pt2313data[PT_RL]=31;
	pt2313data[PT_RR]=31;
	pt2313data[PT_FL]=31;
	pt2313data[PT_FR]=31;
	pt2313data[PT_BASS]=7;
	pt2313data[PT_TREB]=10;
	pt2313data[PT_SWITCH]=0x47;   //0x47   +11.25db  通道4(空)  响度关
#else
    #ifdef LED_AUTO_SHOW_VOL_FROM_ZERO_TO_DEFAULT
	pt2313data[PT_VOLUME]=0;
	#else
	pt2313data[PT_VOLUME]=VOLUME_DEFUALT;
	#endif
	pt2313data[PT_RL]=SWVOL_DEFUALT;
	pt2313data[PT_RR]=SWVOL_DEFUALT;
	pt2313data[PT_FL]=FLFR_DEFUALT;
	pt2313data[PT_FR]=FLFR_DEFUALT;
	#ifdef BASS_DEFAULT
 	pt2313data[PT_BASS]=BASS_DEFAULT;
	#else
 	pt2313data[PT_BASS]=7;
	#endif
	#ifdef TREBLE_DEFAULT
 	pt2313data[PT_TREB]=TREBLE_DEFAULT;
	#else
 	pt2313data[PT_TREB]=7;
	#endif
	pt2313data[PT_SWITCH]=0x47;   //0x47   +11.25db  通道4(空)  响度关
#endif
	PT2313SetData(PT_VOL_NOMAL,8);

#ifdef SUPPORT_PT2314
	pt2314data[PT_VOLUME]=60;
	pt2314data[PT_RL]=15;
	pt2314data[PT_RR]=15;
	pt2314data[PT_FL]=15;
	pt2314data[PT_FR]=15;	
	pt2314data[PT_BASS]=7;
	pt2314data[PT_TREB]=7;
	pt2314data[PT_SWITCH]=0x47;   //0x47   +11.25db  通道4(空)  响度关
	PT2314SetData(PT_VOL_NOMAL,8);
//	pt2314_flag=0;
#endif
	//menumode=MENU_SWVOL;
	//  PT2313MenuPro(0);

}

void AT(.comm) PT2313_Rest(void)
{
    pt2313data[PT_VOLUME]=VOLUME_DEFUALT;
    pt2313data[PT_RL]=SWVOL_DEFUALT;
    pt2313data[PT_RR]=SWVOL_DEFUALT;
    #ifdef HY_MK_JL2_V20
    pt2313data[PT_BASS]=BASS_DEFAULT;//Pt2313EQTable[pt2313_eq_mode][0];
    pt2313data[PT_TREB]=TREBLE_DEFAULT;//Pt2313EQTable[pt2313_eq_mode][1];
    #else
    pt2313data[PT_BASS]=Pt2313EQTable[pt2313_eq_mode][0];
    pt2313data[PT_TREB]=Pt2313EQTable[pt2313_eq_mode][1];
    #endif
    PT2313SetData(PT_VOL_NOMAL,8);
    
#ifdef SUPPORT_PT2314
	pt2314data[PT_VOLUME]=60;
	pt2314data[PT_RL]=15;
	pt2314data[PT_RR]=15;
	pt2314data[PT_FL]=15;
	pt2314data[PT_FR]=15;	
	pt2314data[PT_BASS]=7;
	pt2314data[PT_TREB]=7;
	pt2314data[PT_SWITCH]=0x47;   //0x47   +11.25db  通道4(空)  响度关
	PT2314SetData(PT_VOL_NOMAL,8);
#endif
    
}


void AT(.comm) PT2313SetEQ(unsigned char dir)
{
    if (dir)
    {
        if(pt2313_eq_mode>=AUD_EqMAX)
            pt2313_eq_mode=0;
        else
            pt2313_eq_mode++;
    }
    pt2313data[PT_BASS]=Pt2313EQTable[pt2313_eq_mode][0];
    pt2313data[PT_TREB]=Pt2313EQTable[pt2313_eq_mode][1];
    PT2313SetData(PT_BASS_NOMAL,2);
}


/*
const unsigned char PT2313MenuTab[4]=
{
	PT_VOL_NOMAL,PT_TREB_NOMAL,PT_BASS_NOMAL,PT_RL_NOMAL
};
*/

void AT(.comm)  PT2313MenuPro(unsigned char dir)
{
    unsigned char tempdir;

//	tempdir=PT2313MenuTab[menumode]+dir;
//	if (menumode==MENU_SWVOLL_MODE)
    //	PT2313SetData(tempdir,2);
//	else

    PT2313SetData(tempdir,1);


}
#endif
#endif











