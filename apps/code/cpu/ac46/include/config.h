/*--------------------------------------------------------------------------*/
/**@file     config.h
   @brief    œµÕ≥≈‰÷√
   @details
   @author
   @date    2011-3-7
   @note    CD003
*/
/*----------------------------------------------------------------------------*/

#ifndef _CONFIG_
#define _CONFIG_

#include "typedef.h"
#include "common.h"
#include "printf.h"
#include "uart.h"
#include "interrupt.h"
#include "string.h"


  // √ä√∑√é¬∞
//#define customer_sw005_4601  //¬≥¬§LED √Ü√Å
//#define KPL_K2516_AC4601_V10  //kpl√ë√π¬∞√• lyx

  // √ì√Æ¬∫√Ü¬¥√Ø 
//#define customer_yhd_318LED_4601  
//#define customer_yhd_6001_4601  
//#define customer_yhd_216_4601  

 // √ë√Ö√Ä¬∂√ç¬º
//#define customer_k2536_4601  

 //√à√≥¬¥√Ø√å¬©
//#define customer_rdt_k2536_4601  

 // ¬∫¬∫¬∑√°  
//#define customer_hf560_4601  

 // √î√Å¬º√ë¬∫√™  
//#define customer_YJH001_4601  

  // ¬∞¬Æ¬∫¬∫
//#define customer_008_4601   ////¬≥¬§LED √Ü√Å

  // √Å¬™√ä¬§
//#define customer_K2525_4601   //¬≥¬§LED √Ü√Å


 //√É√Ä√Å¬™¬ª√î
//#define customer_mlh_q18_4601  


 //√ñ√ú¬ª√õ√ç¬®
//#define customer_zht_k3606_4601     //5¬∏√∂¬µ√Ü 3KEY+LIGHT-KEY

//√ñ√û¬ª√£√ç¬®
//#define ZHT_Z102N_V10
//#define ZHT_Z109E_V10

//π˙Õ˛
//#define GW_K1703_V10
//#define GW_827BT
// #define GW_805B_806B_AC4602
// #define GW_805B_806B_AC4602_PCB_SAME_AS_ZY
// #define GW_LCD_SEG_001_1_AC4601
// #define GW_BT01_AC4602
// #define GW_310T_BT_AC4601
// #define GW_004_BT_AC4601
// #define GW_011_AC4601
//  #define GW_1015_AC4601
//  #define GW_020_GZY_REC_AC4601  // JSUO 20160507 ADD
//  #define GW_216BT_AC4601  // JSUO 20161011 ADD
// #define GW_001_1_ZSLCD_REC_AC4601 // 20161011 ADD
 

//–¬¿º
//#define SL_AC4601_V10

//ÃÏ‘œ
//#define TY_4601_Z

//’˝—Ù
//#define ZY_3115_BT_V10
//#define ZY_3058_AC4602
// #define ZY_Q5_BTL_V10_K1730_SEC_LCD  //LCD¬∂√é√Ç√´√Ü√Å
// #define ZY_Q5_BTL_V10_K1730_LED  //LED
// #define ZY_3080A_B_BT_AC4602
// #define ZY_3080A_B_BT_CY_AC4602
//  #define ZY_3088_MM_AC4602   //ƒ™π§
//  #define ZY_3088_CY_AC4602 //ƒ™π§
// #define ZY_3068_BT_AC4601 
//  #define ZY_3027_BT_AC4601_V10 // ZY_3027_BT_REC_AC4601  ZY_3027_BT_IR102_AC4601
// #define ZY_3058B_AC4601_BT_V10 
// #define ZY_3058B_AC4601_BT_CY_V10
//  #define ZY_3058B_AC4601_BT_CY_V10_1 //√¢√ó¬π¬§use sdx-8848 led
//  #define ZY_3058B_AC4601_SDX8812_LED //ÃÔπ§
//  #define ZY_5011AMP_V10_AC4601
//   #define ZY_5011AMP_MIN_V10_AC4601
//#define ZY_3053_AC4601_V10  //√Ñ¬™¬π¬§
// #define ZY_3096_AC4601_V10 //lcd seg8 com5 bias 1/3
// #define ZY_3096_XH_V10_AC4601 //TM1628
// #define ZY_3096_YS3608_V10_AC4601 //–°8LED∆¡
//   #define ZY_3096_SEVEN_8NUM_LED  //ZY-2036-LED-8 PANEL BOARD
//  #define ZY_3050_AC4601_V10  //À’π§pt2313
//  #define ZY_3058B_LG_BOM_AC4601
//  #define ZY_3058A_YG_AC4601
//  #define ZY_3088B_XH_AC4602
//  #define ZY_3096_LT_AC4601  //ÃÔπ§£¨12Ω≈∆¡,eq÷±—°
//   #define ZY_3096_HL_Q1_AC4601 // pt2313
//   #define ZY_5012_SG_AC4601 
//   #define ZY_5018_SG_AC4602 //AB/D
//    #define ZY_5015_SG_AC4602
//  #define ZY_3016_REC_AC4601_V10
//  #define ZY_5011B_SUOAI01_AC4601 //YG
//  #define ZY_3058_3608_JC_AC4601 //MG
//  #define ZY_3058B_4018_LS_AC4601 //MG base on ZY_3058A_YG_AC4601 ZY_3058B_4018_LS_B_AC4601 ZY_3058B_88N48_LS_2_AC4601 ZY_3058B_4018_LS_VOL25_AC4601
//  #define ZY_3058B_4018_LS_NOFM_AC4601 //MG base on ZY_3058A_YG_AC4601
//  #define ZY_3058A_REC_YG_AC4601 //tg
//  #define ZY_3058_3608_Bluetooth_DMWN_AC4601 //MG base on ZY_3058B_4018_LS_AC4601 ZY_3058_DMWN_B_AC4601
//  #define ZY_5011B_SANMU01_AC4601 //YG ∏ﬂÀŸ¥ÔZY_5011B_SANMU01_FM_AC4601
//    #define ZY_3058A_BT_BLUETOOTH_LX_AC4601  // ZY_3058A_BT_88N48_YLD(off fm)   ZY_3058A_BT_BC_AC4601(BLUETOOTH)
//    #define ZY_3058_4018_LS_XSPFJ //mg
//   #define ZY_5021_SG_AC4601   ///  ZY_5021B
//   #define ZY_5017_SG_AC4601   ///  
//    #define ZY_3058A_88N48_AC4601   // no rec 
//  #define ZY_3058B_88N48_AC4601 // rec  ZY_3058B_88N48_NOFM_AC4601
// #define ZY_3058B_88N48_LS_AC4601 
//   #define ZY_3058A_YH_AC4601 // VELIKKA      ZY_3058A_FOLDER ZY_3058A_YH_NOFM_AC4601 
//  #define ZY_5011C_SANMU02_AC4601 //JSUIO 20151111 ADD ZY_5011C_4018_AC4601 ZY_5011C_SANMU02_NOFM_AC4601
//   #define ZY_3058A_LG_AC4601 // 
//    #define ZY_3058_4018_LS_VOICE //mg jsuo 20151123 add ===ZY_3091_4018_LS_VOICE_AC4601  ZY_3091_4018_LS_B_AC4601
// #define ZY_3058B_BT_TK_AC4601 // ¥¯±‡¬Î∆˜   ZY_3058A_FOLDER_AC4601  ZY_3058B_TK_4018_AC4601 ZY_3058B_TK_4018_NOFM_AC4601 ZY_3058B_TK_4018_2_AC4601
// #define ZY_3058A_BT_HY_AC4601
//  #define ZY_3058B_8812_OB_AC4601  // 20151209 ADD ZY_3058B_8812_VOL32_AC4601
//  #define ZY_5011_WB01_AC4601
//  #define ZY_3058B_OB_8426_AC4601 // ¥¯±‡¬Î∆˜  
//   #define ZY_5028_tm1628_AC4601   ///   ZY_5028_tm1628_MJ_AC4601
//  #define ZY_3058B_ZF_AC4601   // BT  USB  k415 BT_NAME
//   #define ZY_5021_MX_SG_AC4601    // ZY_5021_8848_MX_SG_AC4601 ZY_5021_8848_24_AC4601 ZY_5021_MX_4018N_2_AC4601 ZY_5021_MX_88N48_NOREC_AC4601
//  #define ZY_3058B_7G8_REC_AC4601  // ZY_3058B_7G8_REC_NOFM_AC4601 ZY_3058B_7G8_REC_FOLDER_AC4601 ZY_3058B_7G8_VOICE_AC4601
// #define ZY_5011C_NOREC_4018_AC4601 //JSUIO 20151118 ADD
//  #define ZY_6401LCD_AC4601 // jsuo 20160121 add ∂œ¬Î∆Ω
//   #define ZY_3112_88N48_AC4601   //jsuo 20160229 add ZY_3112_88N48_NOFM_AC4601
//  #define ZY_5011C_NOREC_88N48_AC4601 //JSUIO 20151118 ADD 
//    #define ZY_3058A_88N48_NOAUX_AC4601   // DEFAULT BT  only use bt mp3 ◊®”√ƒ£ Ω“ÙZY_3058A_88N48_NOAUX_◊®”√”¢Œƒ_AC4601
//  #define ZY_5011C_NOREC_88N48_HX_AC4601 //JSUIO 20160317 ADD ZY_5011C_NOREC_4018_HX_AC4601 ZY_5011C_NOREC_NOFM_4018_HX_AC4601

/* ZY_5011C_4018_B_FM_AC4601 ZY_5011C_88N48_B_AC4601 
ZY_5011C_88N48_C_AC4601 ZY_5011C_88N48_C_NOFM_AC4601 ZY_5011C_4018_C_NOFM_AC4601
ZY_5011C_4018_C_AC4601 ZY_5011C_4018_B_27_AC4601*/
// #define ZY_5011C_4018_B_AC4601 

//  #define ZY_4602_SP_LED_AC4601 // K1842   JSUIO 20160322 ADD
// #define ZY_3058B_40N18_KIPTECH_AC4601 
//  #define ZY_6003_AC4601  // ZY_6003_B_AC4601
//  #define ZY_3058B_4018_2REC_AC4601 // JSUO 20160504 ADD
//  #define ZY_3058_JW_8426C7_1B_AC4601 
// #define ZY_5011C_4018_D_AC4601  // JSUO 20160510 ADD
//  #define ZY_6003_DWQ_AC4601  //    ZY_6008_AC4601  
//  #define ZY_6003_MP5_AC4601  // 20160525 AD  SEND_IR_CODE
//  #define ZY_5011C_NOREC_JW4018D_AC4601 //JSUIO 20160608 ADD 
//  #define ZY_6003_4018D_3_AC4601  // 20160615 ADD
//  #define ZY_5011C_88N48_C_NOREC_AC4601 //JSUIO 20160625 ADD 
//  #define ZY_6003_LAX_MAX_AC4601  // 20160627 MODIFY IR
//  #define ZY_6003_CH_KLOK_AC4601  //    20160709 add   
//  #define ZY_3058B_7G8_JS_REC_AC4601  
//  #define ZY_6003_TM_K16TY27_AC4601    
// #define ZY_6003_CH_AC4601   // ZY_6003_CH_REC_AC4601 ZY_6003_CH_BAT_AC4601
//  #define ZY_6003_TM_K16TY27_88N48_AC4601    // ZY_6003_TM_K16TY27_88N48_NOFM_AC4601
// #define ZY_3058A_BT_JUNSHENG_AC4601  //20160801 add
//#define ZY_3058_4018_LS_REC_AC4601 // 20160806 ADD
//  #define ZY_3058B_7G8_HD6992_AC4601 
//   #define ZY_6003_TM_HT7369_88N48_AC4601   //ZY_6003_TM_HT7369_88N48_AC4601  
// #define ZY_3058B_JW_4018D71B_AC4601 
// #define ZY_3058B_JW54627_1BB_AC4601 
//  #define ZY_6003_88N48_NOBAT_AC4601  //  ZY_6003_88N48_NOBAT_NOFM_AC4601
//  #define ZY_3058B_88N48_LS_TYIR_AC4601 
//  #define ZY_3058B_4018_LS_BT_AC4601
//   #define ZY_6003_TM_HT7369_KOK_AC4601     //ZY_6003_TM_HT7369_KOK_B_AC4601 
//  #define ZY_3058B_4018_BLUC_AC4601
//  #define ZY_3058B_7G8_BLUC_AC4601  
//  #define ZY_6003_JW4018D3_AC4601  // 20160917 ADD
//  #define ZY_3058B_4018_LS_BT_NOAUX_AC4601
//   #define ZY_5028_TM1628_HD7369_C_AC4601   ///   20160922 ADD
//   #define ZY_5028_TM1628_HD7369_D_AC4601   ///   20160927 ADD
// #define ZY_3058B_HT1621C_HD6992_AC4601   
//    #define ZY_3058A_88N48_NOP_AC4601   // USB SD BT+NOP ZY_3058A_88N48_NOP_B_AC4601
//  #define ZY_3058B_4018_NOAUX_AC4601 //20161026 ADD CD+AC3+DVD+AC4052
//#define ZY_3058B_LS_7G8_C_AC4601 //  20161028 add 
  #define ZY_LX003_BT_AC4601  // 20161028 ADD
  

//ƒœÃ˙«Ú
//#define NTQ_K1724_AC4601_V10
//#define NTQ_K1737_AC4601_V10

//√˜ ¢º—
//#define MSJ_K1719_V10 //AC4601
// #define MSJ_K1734_VFD35_AC4601
// #define MSJ_K1734_VFD35_AC4601_USE_LED8848

// #define MSJ_K1739_V10_AC4601


//ÃÏ∑Â
//#define TF_2008A_HT1628  //ac4601 
//#define TF_2008A  //ac4601 tm1628
//#define TF_2025A //base on 2008A only control pb9 high in mp3/aux mode and low in radio mode
// #define TF_2010_BTL_AC4602 //up/down left/right board
// #define TF_DY015_AC4601  //pt2313

//‘Û–À
//#define HY_601BT
//#define ZX_K1722_AC4602_V10 //HY602BT
//#define ZX_K1722_AC4602_V10_ZY_ADK_RESISTENCE //HY602BT
//#define ZX_602YG_K1722_AC4602_V10
//#define ZX_601P_AC4601_V10 //base on ZX_601LR_AC4601_V10,only reverse led pin
//#define KPL_K2516_AC4601_V10_ZX_SPEC
//#define ZX_HL18_K1755_AC4602_V10
//#define ZX_601LR_AC4601_V10_YUNKE //k1724
//#define ZX_K1757_AC4602_V10  //only mp3 and BT
//#define ZX_HL601_QGN_K1764_AC4601 //AMP pt2313
//#define ZX_HY601LR_SDX4018N_2_AC4601_V10
// #define ZX_HL601_QGN2_K1764_AC4601 //tm1628 /two encoder
//#define ZX_K1764_CYCLE_CLOCK_AC4601
//#define ZX_HL601_1_QGN2_K1764_AC4601 //tm1628 /two encoder
//  #define ZX_HL602UD_V10_AC4602_KOK_PRIORY  // ‘ÛˆŒ  ¥¯okø™πÿ   BOCK ¿∂—¿√˚  ZX_HL602AMP_KOK_AC4602
// #define ZX_HL601_QGN_2314_AC4601 
// #define ZX_HL601UD_ZX10638A_AC4601 //seven 8nums led  20160128 add
// #define ZX_HL601_QGN_JM4169_AC4601 //tm1628 /one encoder 
// #define ZX_HL601_QGN_JM950_AC4601 //tm1628 /one encoder 
// #define ZX_601LR_AC4601_V10  // ZX_601LR_VOICE_AC4601  USE  20160408 ADD JSUO 
// #define ZX_601LR_BL_AC4601  // 20160415 add


//…˘ ”√¿
//#define K1725_AC461_V10
// #define SSM_K1729_AC4603
// #define SSM_Q6_K1725_AC4601  
//#define SSM_SF_K1725_AC4601 //ÀÆ∫¯
// #define SSM_Q8_K1725_AC4601 //led screen same as Q6 ,so not use this define 
// #define SSM_HS_T18W1_1_K1725_8426_AC4601
//#define SSM_K1725_PANEL_AL221_AC4601_V10 //base on K1725_AC461_V10;TM1628
//  #define SSM_Q535_AC461_V10  //  SSM_Q535_8426_AC461_V10 // SSM_Q535B_OPTI_AC461_V10 SSM_Q535_8426_INTRO_AC461
// #define SSM_Q535_2REC_AC461_V10  //
//  #define SSM_Q535B_AC461_V10  //  ∏ƒ“£øÿ    SSM_Q535B_4018_INTRO_AC461
//  #define SSM_Q535_78_AC461_V10  // TM1628_78
// #define SSM_Q535_DBL_AC461_V10  //  ∏ƒ“£øÿ SSM_Q535_DBL_4018_NOBT_AC461  SSM_Q535_DBL_8426_AC461
// #define SSM_Q535_DBL_4018_AC461  // 20160704 add
//  #define SSM_Q535_8426_NOAUX_AC461  //  øÿƒ£ Ω œ‘ æNODi
///  #define SSM_Q538_2PANEL_AC4601  // TM1628_ 2 PANEL SSM_Q538_2PANEL_ADD5_AC4601
//  #define SSM_Q535_4052_AC461   // SSM_Q535_8426_4052_A_AC461 SSM_Q535_8426_4052_B_AC461 SSM_Q535_4018_4052_B_AC461
//  #define SSM_Q535_AC4606B
//  #define SSM_Q535_VOICE_AC4601 // SSM_Q535_8426_NOAUX_VOICE_AC4601
//  #define SSM_Q535_OPTI_04FB_AC4601 // JSUO 20160518 ADD SSM_Q535_OPTI_REC_AC4601 SSM_Q535_OPTI_INTRO_AC4601
// #define SSM_Q535_8426_04FB_AC461 // SSM_Q535_8426_04FB_INTRO
//  #define SSM_Q535B_4018_04FB_AC461
//  #define SSM_Q535B_4018_INTRO_04FB_AC461
//  #define SSM_Q535_4018_4052_B_AC461 
//   #define SSM_Q535B_4018_04FB_VOICE_AC461  // ch_en_double_voice  20160630 add
//  #define SSM_Q535B_4018_04FB_DLED_AC461  // ADD REC_LED-PB9
// #define SSM_Q18_8426_04FB_AC4601 
//    #define SSM_Q535_4018_4052_C_AC461   //20160718 ADD SSM_Q535_8426_4052_C_AC4601
//  #define SSM_Q535B_4018_SA_AC461 // SSM_Q535B_4018_SA_K9_AC461
//   #define SSM_Q535_8426_04FB_B_AC461  // aux rec_mute
// #define SSM_Q535_DBL_4018_NOAUX_AC461 
// #define SSM_Q535_OPTI_04FB_8426_AC4601 // JSUO 20160923 ADD 8426
//   #define SSM_Q535_DBL_4018_6VIOCE_AC461
//   #define SSM_Q535B_4018_04FB_NOBT_AC461
   

//¬∫√™¬≥√â
//#define HC_HT603BT_K1733_AC4602

//À´¬Ì
// #define SM_SM006A_V2_AC4601
//  #define SM_SM004B_AC4601 //base on SM_SM006A_V2_AC4601
//#define SM_D300A_AC4601 //base on SM_SM006A_V2_AC4601
//  #define SM_4003_V1_AC4603
// #define SM_202A_AC4601 //20161013 ADD

//…˘¿÷
//#define SL_SP61_AC4602  //up down card board

//∑˚ œ
//#define FS_K85_AC4601
//#define FS_K88_AC4602
//#define FS_K52_AC4601

//∫ÍŒ∞  œÚπ§
//#define HW_HD09_AC4601 //power on into idle mode 

 //∂´æ∞
// #define DJ_AC4601C_V10
// #define DJ_AC4601D_AC4601

//ÀÿŒ∞
//#define SW013_K1759_AC4601_V10

//À……–
//#define SS_003M_AC4601 

//∞ŸÕº
//#define BT_SY1308_SSM_JL_B_AC4602

//ø•∫¿
//#define JH_001_REC_K1725_AC4601 //∞ÂÕ¨…˘ ”√¿
//#define JH_002_REC_K1725_AC4601 //∞ÂÕ¨…˘ ”√¿
// #define JH_K1789_AC4602  // JH-335

//ˆŒ∑È
//#define XF_01_REC_AC4602  

//lyx
//#define TEST_JL_V13_SOFTWARE

//ª™–«
// #define HX_L158USB_REC_AC4601

// ¿ÀÕ•µÁ∆˜
//   #define LTDQ_ZY5021_AC4601    
//   #define LTDQ_MX_177505_AC4601      // 20160801 ADD
 //  #define LTDQ_MX_303_AC4601    


//   #define LT815_AC4601    //--

// LH  ∆Ù∫Ω
//   #define LH_QH_01_AC4601    
//   #define LH_QH_004_AC4601    

// ø∆∆’∫¿
//   #define KPH_BJ001_AC4601   
//   #define KPH_K1890_AC4601    //20160905 ADD

// ∞¬÷Æ…≠
//  #define AZS_AZS019_AC4601
//  #define AZS_AZS020_AC4601  // 20160903 add 7g8_1628 2313


// Œ÷ÃÿÕ˛
//  #define WTW_WT16450_AC4603

//æ€≥ø
//  #define JC_S1018_AC4601  // 20161013 ADD


#ifdef customer_sw005_4601
    #include "customer_sw005_4601.h"
#elif defined(HX_L158USB_REC_AC4601)
    #include "config_HX_L158USB_REC_AC4601.h"
#elif defined(customer_K2525_4601)
    #include "customer_K2525_4601.h"
#elif defined(customer_yhd_318LED_4601)	
    #include "customer_yhd_318LED_4601.h"
#elif defined(customer_yhd_6001_4601)	
    #include "customer_yhd_6001_4601.h"	
#elif defined(customer_yhd_216_4601)
    #include "customer_yhd_216_4601.h"	
#elif defined(customer_k2536_4601)
    #include "customer_k2536_4601.h"
#elif defined(customer_rdt_k2536_4601  )
    #include "customer_rdt_k2536_4601.h"
#elif defined(customer_hf560_4601)
    #include "customer_hf560_4601.h"	
#elif defined(customer_YJH001_4601)
    #include "customer_YJH001_4601.h"	
#elif defined(customer_008_4601)
    #include "customer_ah008_4601.h"	
#elif defined(customer_mlh_q18_4601)
    #include "customer_mlh_q18_4601.h"	
#elif defined(customer_zht_k3606_4601)
    #include "customer_zht_k3606_4601.h"	
#elif defined(ZHT_Z102N_V10)
    #include "config_ZHT_Z102N_V10.h"
#elif defined(ZHT_Z109E_V10)
    #include "config_ZHT_Z109E_V10.h"
#elif defined(GW_K1703_V10)
    #include "config_GW_K1703_V10.h"
#elif defined(GW_827BT)
    #include "config_GW_827BT.h"
#elif defined(SL_AC4601_V10)
    #include "config_SL_AC4601_V10.h"
#elif defined(TY_4601_Z)
    #include "config_TY_4601_Z.h"
#elif defined(ZY_3115_BT_V10)
    #include "config_ZY_3115_BT_V10.h"
#elif defined(NTQ_K1724_AC4601_V10)
    #include "config_NTQ_K1724_AC4601_V10.h"
#elif defined(MSJ_K1719_V10)
    #include "config_MSJ_K1719_V10.h"
#elif defined(TF_2008A)
    #include "config_TF_2008A.h"
#elif defined(TF_2008A_HT1628)
    #include "config_TF_2008A_HT1628.h"
#elif defined(TF_2025A)
    #include "config_TF_2025A.h"
#elif defined(HY_601BT)
    #include "config_HY_601BT.h"
#elif defined(K1725_AC461_V10)
    #include "config_K1725_AC461_V10.h"
#elif defined(SSM_Q535_AC461_V10)
    #include "config_SSM_Q535_AC461_V10.h"
#elif defined(SSM_Q535B_4018_INTRO_04FB_AC461)
    #include "config_SSM_Q535B_4018_INTRO_04FB_AC461.h"
#elif defined(SSM_Q535_8426_04FB_AC461)
    #include "config_SSM_Q535_8426_04FB_AC461.h"
#elif defined(SSM_Q535_8426_04FB_B_AC461)
    #include "config_SSM_Q535_8426_04FB_B_AC461.h"
#elif defined(SSM_Q18_8426_04FB_AC4601)
    #include "config_SSM_Q18_8426_04FB_AC4601.h"
#elif defined(SSM_Q535_OPTI_04FB_AC4601)
    #include "config_SSM_Q535_OPTI_04FB_AC4601.h"
#elif defined(SSM_Q535_OPTI_04FB_8426_AC4601)
    #include "config_SSM_Q535_OPTI_04FB_8426_AC4601.h"
#elif defined(SSM_Q535_VOICE_AC4601)
    #include "config_SSM_Q535_VOICE_AC4601.h"
#elif defined(SSM_Q535B_4018_04FB_VOICE_AC461)
    #include "config_SSM_Q535B_4018_04FB_VOICE_AC461.h"
#elif defined(SSM_Q535_AC4606B)
    #include "config_SSM_Q535_AC4606B.h"
#elif defined(SSM_Q535_4052_AC461)
    #include "config_SSM_Q535_4052_AC461.h"
#elif defined(SSM_Q535_4018_4052_B_AC461)
    #include "config_SSM_Q535_4018_4052_B_AC461.h"
#elif defined(SSM_Q535_4018_4052_C_AC461)
    #include "config_SSM_Q535_4018_4052_C_AC461.h"
#elif defined(SSM_Q535_8426_NOAUX_AC461)
    #include "config_SSM_Q535_8426_NOAUX_AC461.h"
#elif defined(SSM_Q535_78_AC461_V10)
    #include "config_SSM_Q535_78_AC461_V10.h"
#elif defined(SSM_Q538_2PANEL_AC4601)
    #include "config_SSM_Q538_2PANEL_AC4601.h"
#elif defined(SSM_Q535B_AC461_V10)
    #include "config_SSM_Q535B_AC461_V10.h"
#elif defined(SSM_Q535B_4018_04FB_AC461)
    #include "config_SSM_Q535B_4018_04FB_AC461.h"
#elif defined(SSM_Q535B_4018_04FB_NOBT_AC461)
    #include "config_SSM_Q535B_4018_04FB_NOBT_AC461.h"
#elif defined(SSM_Q535B_4018_SA_AC461)
    #include "config_SSM_Q535B_4018_SA_AC461.h"
#elif defined(SSM_Q535B_4018_04FB_DLED_AC461)
    #include "config_SSM_Q535B_4018_04FB_DLED_AC461.h"
#elif defined(SSM_Q535_DBL_AC461_V10)
    #include "config_SSM_Q535_DBL_AC461_V10.h"
#elif defined(SSM_Q535_DBL_4018_AC461)
    #include "config_SSM_Q535_DBL_4018_AC461.h"
#elif defined(SSM_Q535_DBL_4018_6VIOCE_AC461)
    #include "config_SSM_Q535_DBL_4018_6VIOCE_AC461.h"
#elif defined(SSM_Q535_DBL_4018_NOAUX_AC461)
    #include "config_SSM_Q535_DBL_4018_NOAUX_AC461.h"
#elif defined(SSM_Q535_2REC_AC461_V10)
    #include "config_SSM_Q535_2REC_AC461_V10.h"
#elif defined(ZY_3058_AC4602)
    #include "config_ZY_3058_AC4602.h"
#elif defined(ZX_K1722_AC4602_V10)
    #include "config_ZX_K1722_AC4602_V10.h"
#elif defined(ZX_HL18_K1755_AC4602_V10)
    #include "config_ZX_HL18_K1755_AC4602_V10.h"
#elif defined(ZX_K1722_AC4602_V10_ZY_ADK_RESISTENCE)
    #include "config_ZX_K1722_AC4602_V10_ZY_ADK_RESISTENCE.h"
#elif defined(ZX_602YG_K1722_AC4602_V10)
    #include "config_ZX_602YG_K1722_AC4602_V10.h"
#elif defined(ZY_Q5_BTL_V10_K1730_SEC_LCD)
    #include "config_ZY_Q5_BTL_V10_K1730_SEC_LCD.h"
#elif defined(ZY_Q5_BTL_V10_K1730_LED)
    #include "config_ZY_Q5_BTL_V10_K1730_LED.h"
#elif defined(KPL_K2516_AC4601_V10)
    #include "config_KPL_K2516_AC4601_V10.h"
#elif defined(GW_805B_806B_AC4602)
    #include "config_GW_805B_806B_AC4602.h"
#elif defined(GW_805B_806B_AC4602_PCB_SAME_AS_ZY)
    #include "config_GW_805B_806B_AC4602_PCB_SAME_AS_ZY.h"
#elif defined(ZY_3080A_B_BT_AC4602)
    #include "config_ZY_3080A_B_BT_AC4602.h"
#elif defined(ZY_3080A_B_BT_CY_AC4602)
    #include "config_ZY_3080A_B_BT_CY_AC4602.h"
#elif defined(ZY_3068_BT_AC4601)
    #include "config_ZY_3068_BT_AC4601.h"
#elif defined(TF_2010_BTL_AC4602)
    #include "config_TF_2010_BTL_AC4602.h"    
#elif defined(MSJ_K1734_VFD35_AC4601)
    #include "config_MSJ_K1734_VFD35_AC4601.h"   
#elif defined(MSJ_K1734_VFD35_AC4601_USE_LED8848)
    #include "config_MSJ_K1734_VFD35_AC4601_USE_LED8848.h"   
#elif defined(GW_LCD_SEG_001_1_AC4601)
    #include "config_GW_LCD_SEG_001_1_AC4601.h"   
#elif defined(GW_001_1_ZSLCD_REC_AC4601)
    #include "config_GW_001_1_ZSLCD_REC_AC4601.h"   
#elif defined(GW_BT01_AC4602)
    #include "config_GW_BT01_AC4602.h"   
#elif defined(TF_DY015_AC4601)
    #include "config_TF_DY015_AC4601.h"   
#elif defined(ZX_601LR_AC4601_V10)
    #include "config_ZX_601LR_AC4601_V10.h"  
#elif defined(ZX_601LR_BL_AC4601)
    #include "config_ZX_601LR_BL_AC4601.h"  
#elif defined(ZY_3027_BT_AC4601_V10)
    #include "config_ZY_3027_BT_AC4601_V10.h"
#elif defined(ZX_601P_AC4601_V10)
    #include "config_ZX_601P_AC4601_V10.h"
#elif defined(SM_SM006A_V2_AC4601)
    #include "config_SM_SM006A_V2_AC4601.h"
#elif defined(SM_SM004B_AC4601)
    #include "config_SM_SM004B_AC4601.h"
#elif defined(SM_D300A_AC4601)
    #include "config_SM_D300A_AC4601.h"
#elif defined(SM_202A_AC4601)
    #include "config_SM_202A_AC4601.h"
#elif defined(KPL_K2516_AC4601_V10_ZX_SPEC)
    #include "config_KPL_K2516_AC4601_V10_ZX_SPEC.h"
#elif defined(HC_HT603BT_K1733_AC4602)
    #include "config_HC_HT603BT_K1733_AC4602.h"
#elif defined(SM_4003_V1_AC4603)
    #include "config_SM_4003_V1_AC4603.h"
#elif defined(WTW_WT16450_AC4603)
    #include "config_WTW_WT16450_AC4603.h"
#elif defined(SSM_K1729_AC4603)
    #include "config_SSM_K1729_AC4603.h"
#elif defined(ZY_3058B_AC4601_BT_V10)
    #include "config_ZY_3058B_AC4601_BT_V10.h"
#elif defined(ZY_3058B_AC4601_BT_CY_V10)
    #include "config_ZY_3058B_AC4601_BT_CY_V10.h"
#elif defined(ZY_3058B_AC4601_BT_CY_V10_1)
    #include "config_ZY_3058B_AC4601_BT_CY_V10_1.h"
#elif defined(ZY_5011AMP_V10_AC4601)
    #include "config_ZY_5011AMP_V10_AC4601.h"
#elif defined(ZY_5011AMP_MIN_V10_AC4601)
    #include "config_ZY_5011AMP_MIN_V10_AC4601.h"
#elif defined(ZY_3016_REC_AC4601_V10)
    #include "config_ZY_3016_REC_AC4601_V10.h"
#elif defined(SL_SP61_AC4602)
    #include "config_SL_SP61_AC4602.h"
#elif defined(MSJ_K1739_V10_AC4601)
    #include "config_MSJ_K1739_V10_AC4601.h"
#elif defined(GW_310T_BT_AC4601)
    #include "config_GW_310T_BT_AC4601.h"
#elif defined(GW_004_BT_AC4601)
    #include "config_GW_004_BT_AC4601.h"
#elif defined(SSM_Q6_K1725_AC4601)
    #include "config_SSM_Q6_K1725_AC4601.h"
#elif defined(SSM_Q8_K1725_AC4601)
    #include "config_SSM_Q8_K1725_AC4601.h"
#elif defined(FS_K85_AC4601)
    #include "config_FS_K85_AC4601.h"
#elif defined(GW_011_AC4601)
    #include "config_GW_011_AC4601.h"
#elif defined(ZY_3053_AC4601_V10)
    #include "config_ZY_3053_AC4601_V10.h"
#elif defined(NTQ_K1737_AC4601_V10)
    #include "config_NTQ_K1737_AC4601_V10.h"    
#elif defined(HW_HD09_AC4601)
    #include "config_HW_HD09_AC4601.h"   
#elif defined(ZY_3096_AC4601_V10)
    #include "config_ZY_3096_AC4601_V10.h"    
#elif defined(ZY_3096_XH_V10_AC4601)
    #include "config_ZY_3096_XH_V10_AC4601.h"
#elif defined(ZY_3096_SEVEN_8NUM_LED)
    #include "config_ZY_3096_SEVEN_8NUM_LED.h"    
#elif defined(ZX_601LR_AC4601_V10_YUNKE)
    #include "config_ZX_601LR_AC4601_V10_YUNKE.h"    
#elif defined(ZX_K1757_AC4602_V10)
    #include "config_ZX_K1757_AC4602_V10.h"  
#elif defined(ZY_3096_YS3608_V10_AC4601)
    #include "config_ZY_3096_YS3608_V10_AC4601.h"  
#elif defined(ZY_3050_AC4601_V10)
    #include "config_ZY_3050_AC4601_V10.h"  
#elif defined(SSM_SF_K1725_AC4601)
    #include "config_SSM_SF_K1725_AC4601.h"  
#elif defined(DJ_AC4601C_V10)
    #include "config_DJ_AC4601C_V10.h"  
#elif defined(ZY_3088_MM_AC4602)
    #include "config_ZY_3088_MM_AC4602.h"  
#elif defined(ZY_3088_CY_AC4602)
    #include "config_ZY_3088_CY_AC4602.h"  
#elif defined(ZX_HL601_QGN_K1764_AC4601)
    #include "config_ZX_HL601_QGN_K1764_AC4601.h"  
#elif defined(ZX_HL601_QGN_2314_AC4601)
    #include "config_ZX_HL601_QGN_2314_AC4601.h"  
#elif defined(ZX_HL601UD_ZX10638A_AC4601)
    #include "config_ZX_HL601UD_ZX10638A_AC4601.h"  
#elif defined(ZY_3058B_AC4601_SDX8812_LED)
    #include "config_ZY_3058B_AC4601_SDX8812_LED.h"  
#elif defined(SSM_HS_T18W1_1_K1725_8426_AC4601)
    #include "config_SSM_HS_T18W1_1_K1725_8426_AC4601.h"  
#elif defined(SW013_K1759_AC4601_V10)
    #include "config_SW013_K1759_AC4601_V10.h"  
#elif defined(SS_003M_AC4601)
    #include "config_SS_003M_AC4601.h"  
#elif defined(ZX_HY601LR_SDX4018N_2_AC4601_V10)
    #include "config_ZX_HY601LR_SDX4018N_2_AC4601_V10.h"  
#elif defined(ZY_3058B_LG_BOM_AC4601)
    #include "config_ZY_3058B_LG_BOM_AC4601.h"  	
#elif defined(TEST_JL_V13_SOFTWARE)
    #include "config_TEST_JL_V13_SOFTWARE.h"  	
#elif defined(ZX_K1764_CYCLE_CLOCK_AC4601)    
    #include "config_ZX_K1764_CYCLE_CLOCK_AC4601.h"	
#elif defined(ZX_HL601_QGN2_K1764_AC4601)    
    #include "config_ZX_HL601_QGN2_K1764_AC4601.h"	
#elif defined(ZX_HL601_QGN_JM4169_AC4601)    
    #include "config_ZX_HL601_QGN_JM4169_AC4601.h"	
#elif defined(ZX_HL601_QGN_JM950_AC4601)    
    #include "config_ZX_HL601_QGN_JM950_AC4601.h"	
#elif defined(BT_SY1308_SSM_JL_B_AC4602)    
    #include "config_BT_SY1308_SSM_JL_B_AC4602.h"	
#elif defined(SSM_K1725_PANEL_AL221_AC4601_V10)    
    #include "config_SSM_K1725_PANEL_AL221_AC4601_V10.h"	
#elif defined(ZY_3058A_YG_AC4601)    
    #include "config_ZY_3058A_YG_AC4601.h"	
#elif defined(ZY_3088B_XH_AC4602)    
    #include "config_ZY_3088B_XH_AC4602.h"	
#elif defined(ZY_3096_LT_AC4601)    
    #include "config_ZY_3096_LT_AC4601.h"	
#elif defined(JH_001_REC_K1725_AC4601)    
    #include "config_JH_001_REC_K1725_AC4601.h"	
#elif defined(ZY_3096_HL_Q1_AC4601)    
    #include "config_ZY_3096_HL_Q1_AC4601.h"	
#elif defined(GW_1015_AC4601)    
    #include "config_GW_1015_AC4601.h"	
#elif defined(DJ_AC4601D_AC4601)    
    #include "config_DJ_AC4601D_AC4601.h"	
#elif defined(ZY_5012_SG_AC4601)    
    #include "config_ZY_5012_SG_AC4601.h"	
#elif defined(ZY_5018_SG_AC4602)    
    #include "config_ZY_5018_SG_AC4602.h"	
#elif defined(ZY_5011B_SUOAI01_AC4601)    
    #include "config_ZY_5011B_SUOAI01_AC4601.h"	
#elif defined(ZY_3058_3608_JC_AC4601)    
    #include "config_ZY_3058_3608_JC_AC4601.h"	
#elif defined(ZY_3058B_4018_LS_AC4601)    
    #include "config_ZY_3058B_4018_LS_AC4601.h"	
#elif defined(ZY_3058B_4018_NOAUX_AC4601)    
    #include "config_ZY_3058B_4018_NOAUX_AC4601.h"	
#elif defined(ZY_3058B_LS_7G8_C_AC4601)    
    #include "config_ZY_3058B_LS_7G8_C_AC4601.h"	
#elif defined(ZY_3058B_4018_LS_BT_AC4601)    
    #include "config_ZY_3058B_4018_LS_BT_AC4601.h"	
#elif defined(ZY_3058B_4018_LS_BT_NOAUX_AC4601)    
    #include "config_ZY_3058B_4018_LS_BT_NOAUX_AC4601.h"	
#elif defined(ZY_3058B_4018_BLUC_AC4601)    
    #include "config_ZY_3058B_4018_BLUC_AC4601.h"	
#elif defined(ZY_3058B_88N48_LS_TYIR_AC4601)    
    #include "config_ZY_3058B_88N48_LS_TYIR_AC4601.h"	
#elif defined(ZY_LX003_BT_AC4601)    
    #include "config_ZY_LX003_BT_AC4601.h"	
#elif defined(ZY_3058_4018_LS_REC_AC4601)    
    #include "config_ZY_3058_4018_LS_REC_AC4601.h"	
#elif defined(ZY_3058A_BT_JUNSHENG_AC4601)    
    #include "config_ZY_3058A_BT_JUNSHENG_AC4601.h"	
#elif defined(ZY_3058B_4018_2REC_AC4601)    
    #include "config_ZY_3058B_4018_2REC_AC4601.h"	
#elif defined(ZY_3058B_88N48_LS_AC4601)    
    #include "config_ZY_3058B_88N48_LS_AC4601.h"	
#elif defined(ZY_3058B_88N48_AC4601)    
    #include "config_ZY_3058B_88N48_AC4601.h"	
#elif defined(ZY_3112_88N48_AC4601)    
    #include "config_ZY_3112_88N48_AC4601.h"	
#elif defined(ZY_3058A_YH_AC4601)    
    #include "config_ZY_3058A_YH_AC4601.h"	
#elif defined(ZY_3058B_BT_TK_AC4601)    
    #include "config_ZY_3058B_BT_TK_AC4601.h"	
#elif defined(ZY_3058B_40N18_KIPTECH_AC4601)    
    #include "config_ZY_3058B_40N18_KIPTECH_AC4601.h"	
#elif defined(ZY_3058B_JW_4018D71B_AC4601)    
    #include "config_ZY_3058B_JW_4018D71B_AC4601.h"	
#elif defined(ZY_3058B_JW54627_1BB_AC4601)    
    #include "config_ZY_3058B_JW54627_1BB_AC4601.h"	
#elif defined(ZY_3058B_ZF_AC4601)    
    #include "config_ZY_3058B_ZF_AC4601.h"	
#elif defined(ZY_3058B_OB_8426_AC4601)    
    #include "config_ZY_3058B_OB_8426_AC4601.h"	
#elif defined(ZY_3058B_8812_OB_AC4601)    
    #include "config_ZY_3058B_8812_OB_AC4601.h"	
#elif defined(ZY_3058A_BT_HY_AC4601)    
    #include "config_ZY_3058A_BT_HY_AC4601.h"	
#elif defined(ZY_4602_SP_LED_AC4601)    
    #include "config_ZY_4602_SP_LED_AC4601.h"	
#elif defined(ZY_3058A_LG_AC4601)    
    #include "config_ZY_3058A_LG_AC4601.h"	
#elif defined(FS_K88_AC4602)    
    #include "config_FS_K88_AC4602.h"	
#elif defined(ZX_HL601_1_QGN2_K1764_AC4601)    
    #include "config_ZX_HL601_1_QGN2_K1764_AC4601.h"	
#elif defined(JH_002_REC_K1725_AC4601)    
    #include "config_JH_002_REC_K1725_AC4601.h"	
#elif defined(ZY_3058B_4018_LS_NOFM_AC4601)    
    #include "config_ZY_3058B_4018_LS_NOFM_AC4601.h"	
#elif defined(XF_01_REC_AC4602)    
    #include "config_XF_01_REC_AC4602.h"	
#elif defined(ZY_5015_SG_AC4602)    
    #include "config_ZY_5015_SG_AC4602.h"	
#elif defined(ZY_3058A_REC_YG_AC4601)    
    #include "config_ZY_3058A_REC_YG_AC4601.h"	
#elif defined(ZY_3058_3608_Bluetooth_DMWN_AC4601)    
    #include "config_ZY_3058_3608_Bluetooth_DMWN_AC4601.h"	
#elif defined(ZY_3058_JW_8426C7_1B_AC4601)    
    #include "config_ZY_3058_JW_8426C7_1B_AC4601.h"	
#elif defined(FS_K52_AC4601)    
    #include "config_FS_K52_AC4601.h"	
#elif defined(JH_K1789_AC4602)    
    #include "config_JH_K1789_AC4602.h"	
#elif defined(ZY_5011B_SANMU01_AC4601)    
    #include "config_ZY_5011B_SANMU01_AC4601.h"	
#elif defined(ZY_5011_WB01_AC4601)    
    #include "config_ZY_5011_WB01_AC4601.h"	
#elif defined(ZY_5011C_SANMU02_AC4601)    
    #include "config_ZY_5011C_SANMU02_AC4601.h"	
#elif defined(ZY_5011C_NOREC_4018_AC4601)    
    #include "config_ZY_5011C_NOREC_4018_AC4601.h"	
#elif defined(ZY_6003_AC4601)    
    #include "config_ZY_6003_AC4601.h"	
#elif defined(ZY_6003_JW4018D3_AC4601)    
    #include "config_ZY_6003_JW4018D3_AC4601.h"	
#elif defined(ZY_6003_88N48_NOBAT_AC4601)    
    #include "config_ZY_6003_88N48_NOBAT_AC4601.h"	
#elif defined(ZY_6003_LAX_MAX_AC4601)    
    #include "config_ZY_6003_LAX_MAX_AC4601.h"	
#elif defined(ZY_6003_4018D_3_AC4601)    
    #include "config_ZY_6003_4018D_3_AC4601.h"	
#elif defined(ZY_6003_DWQ_AC4601)    
    #include "config_ZY_6003_DWQ_AC4601.h"	
#elif defined(ZY_6003_TM_K16TY27_AC4601)    
    #include "config_ZY_6003_TM_K16TY27_AC4601.h"	
#elif defined(ZY_6003_TM_K16TY27_88N48_AC4601)    
    #include "config_ZY_6003_TM_K16TY27_88N48_AC4601.h"	
#elif defined(ZY_6003_TM_HT7369_88N48_AC4601)    
    #include "config_ZY_6003_TM_HT7369_88N48_AC4601.h"	
#elif defined(ZY_6003_TM_HT7369_KOK_AC4601)    
    #include "config_ZY_6003_TM_HT7369_KOK_AC4601.h"	
#elif defined(ZY_6003_CH_AC4601)    
    #include "config_ZY_6003_CH_AC4601.h"	
#elif defined(ZY_6003_CH_KLOK_AC4601)    
    #include "config_ZY_6003_CH_KLOK_AC4601.h"	
#elif defined(ZY_6003_MP5_AC4601)    
    #include "config_ZY_6003_MP5_AC4601.h"	
#elif defined(ZY_5011C_NOREC_88N48_AC4601)    
    #include "config_ZY_5011C_NOREC_88N48_AC4601.h"	
#elif defined(ZY_5011C_NOREC_JW4018D_AC4601)    
    #include "config_ZY_5011C_NOREC_JW4018D_AC4601.h"	
#elif defined(ZY_5011C_NOREC_88N48_HX_AC4601)    
    #include "config_ZY_5011C_NOREC_88N48_HX_AC4601.h"	
#elif defined(ZY_5011C_4018_B_AC4601)    
    #include "config_ZY_5011C_4018_B_AC4601.h"	
#elif defined(ZY_5011C_88N48_C_NOREC_AC4601)    
    #include "config_ZY_5011C_88N48_C_NOREC_AC4601.h"	
#elif defined(ZY_5011C_4018_D_AC4601)    
    #include "config_ZY_5011C_4018_D_AC4601.h"	
#elif defined(ZY_6401LCD_AC4601)    
    #include "config_ZY_6401LCD_AC4601.h"	
#elif defined(ZY_3058A_BT_BLUETOOTH_LX_AC4601)    
    #include "config_ZY_3058A_BT_BLUETOOTH_LX_AC4601.h"	
#elif defined(ZY_3058A_88N48_AC4601)    
    #include "config_ZY_3058A_88N48_AC4601.h"	
#elif defined(ZY_3058A_88N48_NOP_AC4601)    
    #include "config_ZY_3058A_88N48_NOP_AC4601.h"	
#elif defined(ZY_3058A_88N48_NOAUX_AC4601)    
    #include "config_ZY_3058A_88N48_NOAUX_AC4601.h"	
#elif defined(ZY_3058_4018_LS_XSPFJ)    
    #include "config_ZY_3058_4018_LS_XSPFJ.h"	
#elif defined(ZY_3058_4018_LS_VOICE)    
    #include "config_ZY_3058_4018_LS_VOICE.h"	
#elif defined(ZY_5017_SG_AC4601)    
    #include "config_ZY_5017_SG_AC4601.h"	
#elif defined(ZY_5021_SG_AC4601)    
    #include "config_ZY_5021_SG_AC4601.h"	
#elif defined(ZY_5021_MX_SG_AC4601)    
    #include "config_ZY_5021_MX_SG_AC4601.h"	
#elif defined(LTDQ_ZY5021_AC4601)    
    #include "config_LTDQ_ZY5021_AC4601.h"
#elif defined(LTDQ_MX_303_AC4601)    
    #include "config_LTDQ_MX_303_AC4601.h"
#elif defined(LTDQ_MX_177505_AC4601)    
    #include "config_LTDQ_MX_177505_AC4601.h"
#elif defined(LT815_AC4601)    
    #include "config_LT815_AC4601.h"
#elif defined(LH_QH_01_AC4601)    
    #include "config_LH_QH_01_AC4601.h"
#elif defined(LH_QH_004_AC4601)    
    #include "config_LH_QH_004_AC4601.h"
#elif defined(KPH_BJ001_AC4601)    
    #include "config_KPH_BJ001_AC4601.h"
#elif defined(KPH_K1890_AC4601)    
    #include "config_KPH_K1890_AC4601.h"
#elif defined(AZS_AZS019_AC4601)    
    #include "config_AZS_AZS019_AC4601.h"
#elif defined(AZS_AZS020_AC4601)    
    #include "config_AZS_AZS020_AC4601.h"
#elif defined(JC_S1018_AC4601)    
    #include "config_JC_S1018_AC4601.h"
#elif defined(ZY_3058B_7G8_REC_AC4601)    
    #include "config_ZY_3058B_7G8_REC_AC4601.h"	
#elif defined(ZY_3058B_7G8_BLUC_AC4601)    
    #include "config_ZY_3058B_7G8_BLUC_AC4601.h"	
#elif defined(ZY_3058B_7G8_HD6992_AC4601)    
    #include "config_ZY_3058B_7G8_HD6992_AC4601.h"	
#elif defined(ZY_3058B_HT1621C_HD6992_AC4601)    
    #include "config_ZY_3058B_HT1621C_HD6992_AC4601.h"	
#elif defined(ZY_3058B_7G8_JS_REC_AC4601)    
    #include "config_ZY_3058B_7G8_JS_REC_AC4601.h"	
#elif defined(ZY_3096BT_7G8_AC4601)    
    #include "config_ZY_3096BT_7G8_AC4601.h"	
#elif defined(ZY_5028_tm1628_AC4601)    
    #include "config_ZY_5028_tm1628_AC4601.h"	
#elif defined(ZY_5028_TM1628_HD7369_C_AC4601)    
    #include "config_ZY_5028_TM1628_HD7369_C_AC4601.h"	
#elif defined(ZY_5028_TM1628_HD7369_D_AC4601)    
    #include "config_ZY_5028_TM1628_HD7369_D_AC4601.h"	
#elif defined(ZX_HL602UD_V10_AC4602_KOK_PRIORY)    
    #include "config_ZX_HL602UD_V10_AC4602_KOK_PRIORY.h"	
#elif defined(GW_020_GZY_REC_AC4601)    
    #include "config_GW_020_GZY_REC_AC4601.h"	
#elif defined(GW_216BT_AC4601)    
    #include "config_GW_216BT_AC4601.h"	
#else 
 #error("√á√´√â√®√ñ√É¬ø√ç¬ª¬ß√Ö√§√ñ√É√é√Ñ¬º√æ ")
#endif 

#include "config_mu_gpio_set.h"

 #define SUPPORT_WOKRMODE
 #ifdef SUPPORT_WOKRMODE
 extern u8 workmode;
 #endif
 
#ifdef SUPPORT_BT_PHONE_EN
#define USER_SUPPORT_PROFILE_HFP    1
#else
#define USER_SUPPORT_PROFILE_HFP    0
#endif

#define MUSIC_TASK_NAME "MusicTask"

#endif
