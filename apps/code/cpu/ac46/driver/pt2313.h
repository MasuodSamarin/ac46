
/***********************************************************************************************
 *	Processer :
 *	Compiler :
 *	File:
 *	Description:
 *	Date: 2007.04.26
 *	Last update time:
 *	Writer :	SQG
 *	revision:1.00

***********************************************************************************************/


#ifndef _AUDIO_2313_H_
#define _AUDIO_2313_H_

#ifdef _AUDIO_2313_C_
#define _AUDIO_2313_
#else
#define _AUDIO_2313_	extern
#endif
#include "config.h"





#define Aud_PT2313Adr			0x88

#define Aud_FLMuteVal			0x9F
#define Aud_FRMuteVal			0xBF
#define Aud_RLMuteVal			0xDF
#define Aud_RRMuteVal			0xFF


//pt2313 地址
#define AudAdd_VOL			0x00
#define AudAdd_RL			0xC0
#define AudAdd_RR			0xE0
#define AudAdd_FL			0x80
#define AudAdd_FR			0xA0
#define AudAdd_SWITCH		0x40
#define AudAdd_BASS			0x60
#define AudAdd_TREB			0x70


/* pt2313data[8]  划分*/
#define PT_VOLUME			0
#define PT_RL				1
#define PT_RR				2
#define PT_FL				3
#define PT_FR				4
#define PT_BASS				5
#define PT_TREB				6
#define PT_SWITCH			7



/*vol plus or minus*/
#define PT2313_VOL_PLUS 0
#define PT2313_VOL_MINUS 1

//void PT2313SetData(unsigned char dir,unsigned char snum)
//dir  对应的功能

#define PT_VOL_NOMAL	0x00
#define PT_VOL_UP		0x01
#define PT_VOL_DN		0x02

#define PT_RL_NOMAL		0x03
#define PT_RL_UP		0x04
#define PT_RL_DN		0x05

#define PT_RR_NOMAL	0x06
#define PT_RR_UP		0x07
#define PT_RR_DN		0x08

#define PT_FL_NOMAL		0x09
#define PT_FL_UP		0x0A
#define PT_FL_DN		0x0B

#define PT_FR_NOMAL	0x0C
#define PT_FR_UP		0x0D
#define PT_FR_DN		0x0E

#define PT_BASS_NOMAL	0x0F
#define PT_BASS_UP		0x10
#define PT_BASS_DN		0x11

#define PT_TREB_NOMAL	0x12
#define PT_TREB_UP		0x13
#define PT_TREB_DN		0x14

//  最大 VOL  设置
#ifdef gw_911bt_ne
#define AudVOLMAX			62
#elif defined(MAIN_VOL_MAX)
#define AudVOLMAX			MAIN_VOL_MAX
#else
#define AudVOLMAX			0x3F
#endif
#ifdef SWVOL_MAX
#define AudBALMAX		       SWVOL_MAX //重低音
#define AudswLMAX			SWVOL_MAX //环绕 
#else
#define AudBALMAX		       0x1f //重低音
#define AudswLMAX			0x1f //环绕 
#endif
#ifdef BASS_TREB_MAX
#define MAX_TONE		    	BASS_TREB_MAX
#else
#define MAX_TONE		    	14
#endif
//----------Aud Switch--------
//***bit 8,7,6 must be 010
//---------------------------------
//bit 0 and bit 1
//bit 2
#define Aud_SwLoud				0x04
//bit 3 and bit 4
//#define Aud_Sw11_25dB			0x00
//#define Aud_Sw7_5dB				0x08
//#define Aud_Sw3_75dB			0x10
//#define Aud_Sw0dB				0x18


#if defined support_pt2314_iic_user_pb1datpd0clk

#define PT2313_data_out()   PORTB_DIR &= ~(BIT(1));      PORTB_PU |= (BIT(1))
#define PT2313_data_h()     PORTB_OUT  |= (BIT(1))
#define PT2313_data_l()     PORTB_OUT  &=~ (BIT(1))

#define PT2313_data_in()     PORTB_DIR |= (BIT(1));          PORTB_PU |= (BIT(1))
#define PT2313_data()     ((PORTB_IN>>1)&(BIT(0)))

#define PT2313_clk_out()   {\
							if(pt2314_flag==0) {PORTB_DIR &= ~(BIT(11)); PORTB_PU |= (BIT(11));} else {PORTD_DIR &= ~(BIT(1));     PORTD_PU |= (BIT(1));}\
						}
#define PT2313_clk_h()      {\
							if(pt2314_flag==0) {PORTB_OUT  |= (BIT(11));} else {PORTD_OUT  |= (BIT(1));}\
						}
#define PT2313_clk_l()      {\
							if(pt2314_flag==0) {  PORTB_OUT  &=~ (BIT(11));} else {  PORTD_OUT  &=~ (BIT(1));}\
						}
#elif defined(PT2313_CLK_DATA_USE_PA15PA14)
   #define PT2313_data_out()   PORTA_DIR &= ~(BIT(14));      PORTA_PU |= (BIT(14))
   #define PT2313_data_h()     PORTA_OUT  |= (BIT(14))
   #define PT2313_data_l()     PORTA_OUT  &=~ (BIT(14))
   
   #define PT2313_data_in()     PORTA_DIR |= (BIT(14));          PORTA_PU |= (BIT(14))
   #define PT2313_data()     ((PORTA_IN>>14)&(BIT(0)))
   
   #define PT2313_clk_out()    PORTA_DIR &= ~(BIT(15));     PORTA_PU |= (BIT(15))
   #define PT2313_clk_h()      PORTA_OUT  |= (BIT(15))
   #define PT2313_clk_l()      PORTA_OUT  &=~ (BIT(15))
#elif defined(PT2313_CLK_DATA_USE_PA6PA7)
   #define PT2313_data_out()   PORTA_DIR &= ~(BIT(7));      PORTA_PU |= (BIT(7))
   #define PT2313_data_h()     PORTA_OUT  |= (BIT(7))
   #define PT2313_data_l()     PORTA_OUT  &=~ (BIT(7))
   
   #define PT2313_data_in()     PORTA_DIR |= (BIT(7));          PORTA_PU |= (BIT(7))
   #define PT2313_data()     ((PORTA_IN>>7)&(BIT(0)))
   
   #define PT2313_clk_out()    PORTA_DIR &= ~(BIT(6));     PORTA_PU |= (BIT(6))
   #define PT2313_clk_h()      PORTA_OUT  |= (BIT(6))
   #define PT2313_clk_l()      PORTA_OUT  &=~ (BIT(6))  
   
 #elif defined(PT2313_CLK_DATA_USE_PA11PA14)
   #define PT2313_data_out()   PORTA_DIR &= ~(BIT(14));      PORTA_PU |= (BIT(14))
   #define PT2313_data_h()     PORTA_OUT  |= (BIT(14))
   #define PT2313_data_l()     PORTA_OUT  &=~ (BIT(14))
   
   #define PT2313_data_in()     PORTA_DIR |= (BIT(14));          PORTA_PU |= (BIT(14))
   #define PT2313_data()     ((PORTA_IN>>14)&(BIT(0)))
   
   #define PT2313_clk_out()    PORTA_DIR &= ~(BIT(11));     PORTA_PU |= (BIT(11))
   #define PT2313_clk_h()      PORTA_OUT  |= (BIT(11))
   #define PT2313_clk_l()      PORTA_OUT  &=~ (BIT(11))  
#elif defined(PT2313_CLK_DATA_USE_PC10PA6)
   #define PT2313_data_out()   PORTA_DIR &= ~(BIT(6));      PORTA_PU |= (BIT(6))
   #define PT2313_data_h()     PORTA_OUT  |= (BIT(6))
   #define PT2313_data_l()     PORTA_OUT  &=~ (BIT(6))
   
   #define PT2313_data_in()     PORTA_DIR |= (BIT(6));          PORTA_PU |= (BIT(6))
   #define PT2313_data()     ((PORTA_IN>>6)&(BIT(0)))
   
   #define PT2313_clk_out()    PORTC_DIR &= ~(BIT(10));     PORTC_PU |= (BIT(10))
   #define PT2313_clk_h()      PORTC_OUT  |= (BIT(10))
   #define PT2313_clk_l()      PORTC_OUT  &=~ (BIT(10))
#elif defined(PT2313_CLK_DATA_USE_PB10PB9)
   #define PT2313_data_out()   PORTB_DIR &= ~(BIT(9));      PORTB_PU |= (BIT(9))
   #define PT2313_data_h()     PORTB_OUT  |= (BIT(9))
   #define PT2313_data_l()     PORTB_OUT  &=~ (BIT(9))
   
   #define PT2313_data_in()     PORTB_DIR |= (BIT(9));          PORTB_PU |= (BIT(9))
   #define PT2313_data()     ((PORTB_IN>>9)&(BIT(0)))
   
   #define PT2313_clk_out()    PORTB_DIR &= ~(BIT(10));     PORTB_PU |= (BIT(10))
   #define PT2313_clk_h()      PORTB_OUT  |= (BIT(10))
   #define PT2313_clk_l()      PORTB_OUT  &=~ (BIT(10))

#elif defined(PT2313_CLK_DATA_USE_PB7PB6)
   #define PT2313_data_out()   PORTB_DIR &= ~(BIT(6));      PORTB_PU |= (BIT(6))
   #define PT2313_data_h()     PORTB_OUT  |= (BIT(6))
   #define PT2313_data_l()     PORTB_OUT  &=~ (BIT(6))
   
   #define PT2313_data_in()     PORTB_DIR |= (BIT(6));          PORTB_PU |= (BIT(6))
   #define PT2313_data()     ((PORTB_IN>>6)&(BIT(0)))
   
   #define PT2313_clk_out()    PORTB_DIR &= ~(BIT(7));     PORTB_PU |= (BIT(7))
   #define PT2313_clk_h()      PORTB_OUT  |= (BIT(7))
   #define PT2313_clk_l()      PORTB_OUT  &=~ (BIT(7))   
#elif defined(PT2313_CLK_DATA_USE_PB8PB7)
   #define PT2313_data_out()   PORTB_DIR &= ~(BIT(7));      PORTB_PU |= (BIT(7))
   #define PT2313_data_h()     PORTB_OUT  |= (BIT(7))
   #define PT2313_data_l()     PORTB_OUT  &=~ (BIT(7))
   
   #define PT2313_data_in()     PORTB_DIR |= (BIT(7));          PORTB_PU |= (BIT(7))
   #define PT2313_data()     ((PORTB_IN>>7)&(BIT(0)))
   
   #define PT2313_clk_out()    PORTB_DIR &= ~(BIT(8));     PORTB_PU |= (BIT(8))
   #define PT2313_clk_h()      PORTB_OUT  |= (BIT(8))
   #define PT2313_clk_l()      PORTB_OUT  &=~ (BIT(8))
#endif


//-------------Aud Item-----------

_AUDIO_2313_ u8  pt2313data[8];
_AUDIO_2313_ void Pt2313_ChangSource(u8 curmode);
_AUDIO_2313_ void PT2313_Init(void);
_AUDIO_2313_ void PT2313SetEQ(u8 dir);
_AUDIO_2313_ void PT2313_SetVol(u8  AUD_VolVal);
_AUDIO_2313_ void PT2313Mute(u8 OnOff);
_AUDIO_2313_ void PT2313SetData(u8 dir,u8 snum);
_AUDIO_2313_ void PT2313MenuPro(u8  dir);

_AUDIO_2313_  void AUD_SetLoud(bool OnOff);
_AUDIO_2313_ void  PT2313_reset(void);

#ifdef SUPPORT_PT2314
extern  u8 pt2314data[8];
_AUDIO_2313_ void PT2314SetData(u8 dir,u8 snum);
#endif
void PT2313_KEY_PROCESS(u8 menuMode,bool volPlusMinus);










#endif

