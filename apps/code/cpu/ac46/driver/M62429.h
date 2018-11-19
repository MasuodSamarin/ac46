/*M62429 header file */
#include "config.h"

#ifdef M62429_CLK_DATA_USE_PA10PA9
  #define M62429_CLK_OUT()       PORTA_DIR &= ~BIT(10); PORTA_PU |= BIT(10) ;PORTA_DIR &= ~BIT(10); PORTA_PU |= BIT(10) 
  
  #define M62429_CLK_h()         PORTA_OUT|= BIT(10)
  #define M62429_CLK_l()          PORTA_OUT &= ~BIT(10)
  
  #define M62429_DAT_h()  	      PORTA_OUT|= BIT(9)
  #define M62429_DAT_l()  	      PORTA_OUT &= ~BIT(9)
  
 #elif defined(M62429_CLK_DATA_USE_PB9PB8)  


  #define M62429_CLK_OUT()	   PORTB_DIR &= ~BIT(9); PORTB_PU |= BIT(9) ;PORTB_DIR &= ~BIT(8); PORTB_PU |= BIT(8) 

  #define M62429_CLK_h()		   PORTB_OUT|= BIT(9)
  #define M62429_CLK_l()			PORTB_OUT &= ~BIT(9)
  
  #define M62429_DAT_h()			PORTB_OUT|= BIT(8)
  #define M62429_DAT_l()			PORTB_OUT &= ~BIT(8)
 
#elif defined(M62429_CLK_DATA_USE_PA4PA6)  
  #define M62429_CLK_OUT()	   PORTA_DIR &= ~BIT(4); PORTA_PU |= BIT(4) ;PORTA_DIR &= ~BIT(6); PORTA_PU |= BIT(6) 
  
  #define M62429_CLK_h()		   PORTA_OUT|= BIT(4)
  #define M62429_CLK_l()			PORTA_OUT &= ~BIT(4)
  
  #define M62429_DAT_h()			PORTA_OUT|= BIT(6)
  #define M62429_DAT_l()			PORTA_OUT &= ~BIT(6)
#endif
#ifdef ZX_HL601_QGN_JM4169_AC4601
#define OKVOLMAX	30
#define ECHOMAX		10
#else
#define OKVOLMAX	30
#define ECHOMAX		18
#endif

#define OKVOL_NOMAL		0
#define OKVOL_DN		1
#define OKVOL_UP		2

#define ECHO_NOMAL		3
#define ECHO_DN			4
#define ECHO_UP			5
#ifdef gw_911bt_ne
#define OKVOL_DEFAULT	0
#define ECHO_DEFAULT	0
#else
#if KARAOKE_MIC_DEFAULT_VOL
#define OKVOL_DEFAULT	KARAOKE_MIC_DEFAULT_VOL
#else
#define OKVOL_DEFAULT	15
#endif
#if KARAOKE_ECHO_DEFAULT_VOL
#define ECHO_DEFAULT	KARAOKE_ECHO_DEFAULT_VOL
#else
#define ECHO_DEFAULT	10
#endif
#endif
//u16 okvolbak;
#ifdef MIC_LED_SHOW_MAX
extern u8 mic_temp_vol;
#endif
#ifdef MIC_ECHO_LED_SHOW_MAX
extern u8 mic_echo_temp_vol;
#endif

extern  u8 M62429Data[2];
 void M62429MenuPro(u8 dir);
 void M62429Init(void);
 void SetM62429Data(u8 dir);

