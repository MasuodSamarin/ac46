/*encoder.h file*/
#include "config.h"
#ifdef SUPPORT_ENCODER

#ifdef ENCODE_PIN_USE_PA6PA4
  #define ENCODE_PORTB_IN()     PORTA_DIR |= BIT(6);   PORTA_PU|= BIT(6);  PORTA_DIR |= BIT(4);    PORTA_PU|= BIT(4);
  #define  BM_DN_IS_H()              PORTA_IN & BIT(6) 
  #define  BM_UP_IS_H()              PORTA_IN & BIT(4) 
#elif defined(ENCODE_PIN_USE_PA6PA7)
  #define ENCODE_PORTB_IN()     PORTA_DIR |= BIT(6);   PORTA_PU|= BIT(6);  PORTA_DIR |= BIT(7);    PORTA_PU|= BIT(7);
  #define  BM_DN_IS_H()              PORTA_IN & BIT(6) 
  #define  BM_UP_IS_H()              PORTA_IN & BIT(7) 
#elif defined(ENCODE_PIN_USE_PA9PA10)
  #define ENCODE_PORTB_IN()     PORTA_DIR |= BIT(9);   PORTA_PU|= BIT(9);  PORTA_DIR |= BIT(10);    PORTA_PU|= BIT(10);
  #define  BM_DN_IS_H()              PORTA_IN & BIT(9) 
  #define  BM_UP_IS_H()              PORTA_IN & BIT(10) 
#elif defined(ENCODE_PIN_USE_PB9PB8)
  #define ENCODE_PORTB_IN()     PORTB_DIR |= BIT(9);   PORTB_PU|= BIT(9);  PORTB_DIR |= BIT(8);    PORTB_PU|= BIT(8);
  #define  BM_DN_IS_H()              PORTB_IN & BIT(9) 
  #define  BM_UP_IS_H()              PORTB_IN & BIT(8) 
#elif defined(ENCODE_PIN_USE_PB7PB6)
  #define ENCODE_PORTB_IN()     PORTB_DIR |= BIT(7);   PORTB_PU|= BIT(7);  PORTB_DIR |= BIT(6);    PORTB_PU|= BIT(6);
  #define  BM_DN_IS_H()              PORTB_IN & BIT(7) 
  #define  BM_UP_IS_H()              PORTB_IN & BIT(6) 
#elif defined(ENCODE_PIN_USE_PB9PB10)  
  #define ENCODE_PORTB_IN()	  PORTB_DIR |= BIT(9);	 PORTB_PU|= BIT(9);  PORTB_DIR |= BIT(10);	 PORTB_PU|= BIT(10);
  #define  BM_DN_IS_H()			   PORTB_IN & BIT(9) 
  #define  BM_UP_IS_H()			   PORTB_IN & BIT(10) 
#elif defined(ENCODE_PIN_USE_PC10PC11)  
  #define ENCODE_PORTB_IN()	  PORTC_DIR |= BIT(11);	 PORTC_PU|= BIT(11);  PORTC_DIR |= BIT(10);	 PORTC_PU|= BIT(10);
  #define  BM_DN_IS_H()			   PORTC_IN & BIT(10) 
  #define  BM_UP_IS_H()			   PORTC_IN & BIT(11)   
#endif
#ifdef SUPPORT_TWO_ENCODER
  #ifdef ENCODER1_PIN_USE_PB7PB6
   #define ENCODE_PORTB_IN1()	  PORTB_DIR |= BIT(7);	 PORTB_PU|= BIT(7);  PORTB_DIR |= BIT(6);	 PORTB_PU|= BIT(6);
   #define  BM_DN_IS_H1()			   PORTB_IN & BIT(7) 
   #define  BM_UP_IS_H1()			   PORTB_IN & BIT(6) 
  #endif
#endif
void ENC_Encoder(void);
#ifdef SUPPORT_ENCODE_flash_led
void ENC_Encoder_Led(void);
#endif
#endif
