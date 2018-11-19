/*--------------------------------------------------------------------------*/
/**@file    LED.c
   @brief   LED 模块驱动接口函数
   @details
   @author  bingquan Cai
   @date    2012-8-30
   @note    AC319N
*/
/*----------------------------------------------------------------------------*/
#include "ui_api.h"

#if UI_ENABLE

#include "ui_common.h"
#include "led7_drv.h"
#include "fm_radio.h"
#include "decoder_phy.h"
#include "music.h"
#include "timer.h"
#include "key.h"
#include "file_operate.h"
//#include "play_file.h"
#include "dac.h"
#include "irtc.h"
#include "rtc_setting.h"

LED7_VAR led7_var;

const  u8 LED_NUMBER[10] =
{
    /*0*/
    (u8)(LED_A | LED_B | LED_C | LED_D | LED_E | LED_F),
    /*1*/
    (u8)(LED_B | LED_C),
    /*2*/
    (u8)(LED_A | LED_B | LED_D | LED_E | LED_G),
    /*3*/
    (u8)(LED_A | LED_B | LED_C | LED_D | LED_G),
    /*4*/
    (u8)(LED_B | LED_C | LED_F | LED_G),
    /*5*/
    (u8)(LED_A | LED_C | LED_D | LED_F | LED_G),
    /*6*/
    (u8)(LED_A | LED_C | LED_D | LED_E | LED_F | LED_G),
    /*7*/
    (u8)(LED_A | LED_B | LED_C),
    /*8*/
    (u8)(LED_A | LED_B | LED_C | LED_D | LED_E | LED_F | LED_G),
    /*9*/
    (u8)(LED_A | LED_B | LED_C | LED_D | LED_F | LED_G),
};

const  u8 LED_LARGE_LETTER[26] =
{
    0x77,0x40,0x39,0x3f,0x79,///<ABCDE
    0x71,0x40,0x76,0x06,0x40,///<FGHIJ
    0x40,0x38,0x40,0x37,0x3f,///<KLMNO
    0x73,0x40,0x50,0x6d,0x78,///<PQRST
    0x3e,0x3e,0x40,0x76,0x40,///<UVWXY
    0x40///<Z
};

const  u8 LED_SMALL_LETTER[26] =
{
    0x77,0x7c,0x58,0x5e,0x79,///<abcde
    0x71,0x40,0x40,0x40,0x40,///<fghij
    0x40,0x38,0x40,0x54,0x5c,///<klmno
    0x73,0x67,0x50,0x40,0x78,///<pqrst
    0x3e,0x3e,0x40,0x40,0x40,///<uvwxy
    0x40///<z
};

/* 通过测试 7断的真值表
   0    1    2     3     4     5     6
0  X    1A   1B    1E    SD   播放   X
1  1F   X    2A    2B    2E   2D     X
2  1G   2F   X     :     3B   ||     MP3
3  1C   2G   3F    X     3C   4E     X
4  1D   2C   3G    3A    X    4C     4G
5  3D   U    3E    4D    4F   X      4B
6  X    X    MHz    X    X    4A     X
*/
/*
// 7断数码管转换表
const u8 led_7[35][2] =
{
  {0,1},//1A
  {0,2},//1B
  {3,0},//1C
  {4,0},//1D
  {0,3},//1E
  {1,0},//1F
  {2,0},//1G

  {1,2},//2A
  {1,3},//2B
  {4,1},//2C
  {1,5},//2D
  {1,4},//2E
  {2,1},//2F
  {3,1},//2G

  {4,3},//3A
  {2,4},//3B
  {3,4},//3C
  {5,0},//3D
  {5,2},//3E
  {3,2},//3F
  {4,2},//3G

  {6,5},//4A
  {5,6},//4B
  {4,5},//4C
  {5,3},//4D
  {3,5},//4E
  {5,4},//4F
  {4,6},//4G

  {0,5},//LED_PLAY
  {2,5},//LED_PAUSE
  {5,1},//LED_USB
  {0,4},//LED_SD
  {2,3},//LED_2POINT
  {6,2},//LED_MHZ
  {2,6},//LED_MP3
};
*/
/***********新7段数码管真值表**************/
/* 0    1     2     3     4     5     6
0  X    2A    2B    2C    2D    2E    2F
1  1A   X     2G    :     .     MHz   MP3
2  1B   X     X     4A    4B    4C    4D
3  1C   PLAY  3A    X     4E    4F    4G
4  1D   PAUSE 3B    3E    X     X     X
5  1E   USB   3C    3F    X     X     X
6  1F   SD    3D    3G    X     X     X
*/
const u8 led_7[36][2] = ///< 新7断数码管转换表
{
  {1,0},//1A
  {2,0},//1B
  {3,0},//1C
  {4,0},//1D
  {5,0},//1E
  {6,0},//1F
  {2,1},//1G

  {0,1},//2A
  {0,2},//2B
  {0,3},//2C
  {0,4},//2D
  {0,5},//2E
  {0,6},//2F
  {1,2},//2G

  {3,2},//3A
  {4,2},//3B
  {5,2},//3C
  {6,2},//3D
  {4,3},//3E
  {5,3},//3F
  {6,3},//3G

  {2,3},//4A
  {2,4},//4B
  {2,5},//4C
  {2,6},//4D
  {3,4},//4E
  {3,5},//4F
  {3,6},//4G

  {3,1},//LED_PLAY
  {4,1},//LED_PAUSE
  {5,1},//LED_USB
  {6,1},//SD
  {1,3},//:
  {1,5},//MHz
  {1,4},//.
  {1,6},//MP3
};

//按位于 查表
const u8 bit_table[8] =
{
  0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,
};

const u8 playmodestr[][5] =
{
    " ALL",
    "Fold",
    " ONE",
    " rAn",
};

const u8 menu_string[][5] =
{
    " HI ",
    "Lod ",
    "bLUE",
    " PC ",
    " UP ",
    " dN ",
    " AUX",
    "-AL-"
};
const u8 other_string[][5]=
{
    "Eq ",
    "V ",
    "P ",
    " NOP",
};

/*----------------------------------------------------------------------------*/
/**@brief   led7_drv 状态位缓存清除函数
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_clear_icon(void)
*/
/*----------------------------------------------------------------------------*/
void led7_clear_icon(void)
{
    led7_var.bFlashChar = 0;
    led7_var.bFlashIcon = 0;
    led7_var.bShowBuff[4] = 0;
}

/*----------------------------------------------------------------------------*/
/**@brief   led7_drv 显示坐标设置
   @param   x：显示横坐标
   @return  void
   @author  Change.tsai
   @note    void led7_setX(u8 X)
*/
/*----------------------------------------------------------------------------*/
void led7_setX(u8 X)
{
    led7_var.bCoordinateX = X;
}

/*----------------------------------------------------------------------------*/
/**@brief   LED 清屏函数
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_show_null(void)
*/
/*----------------------------------------------------------------------------*/
void led7_show_null(void)
{
    led7_clear_icon();
    led7_var.bShowBuff[0] = 0;
    led7_var.bShowBuff[1] = 0;
    led7_var.bShowBuff[2] = 0;
    led7_var.bShowBuff[3] = 0;
}

/*----------------------------------------------------------------------------*/
/**@brief   led7_drv 扫描函数
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_init(void)
*/
/*----------------------------------------------------------------------------*/
void led7_init(void)
{
    led7_clear();
}

/*----------------------------------------------------------------------------*/
/**@brief   led7_drv 单个字符显示函数
   @param   chardata：显示字符
   @return  void
   @author  Change.tsai
   @note    void led7_show_char(u8 chardata)
*/
/*----------------------------------------------------------------------------*/
void led7_show_char(u8 chardata)
{
    //必须保证传入的参数符合范围，程序不作判断
    //if ((chardata < ' ') || (chardata > '~') || (led7_var.bCoordinateX > 4))
    //{
    //    return;
    //}
    if ((chardata >= '0') && (chardata <= '9'))
    {
        led7_var.bShowBuff[led7_var.bCoordinateX++] = LED_NUMBER[chardata - '0'];
    }
    else if ((chardata >= 'a') && (chardata <= 'z'))
    {
        led7_var.bShowBuff[led7_var.bCoordinateX++] = LED_SMALL_LETTER[chardata - 'a'];
    }
    else if ((chardata >= 'A') && (chardata <= 'Z'))
    {
        led7_var.bShowBuff[led7_var.bCoordinateX++] = LED_LARGE_LETTER[chardata - 'A'];
    }
    else if (chardata == ':')
    {
        LED_STATUS |= LED_2POINT;
    }
    else if (chardata == ' ')
    {
        led7_var.bShowBuff[led7_var.bCoordinateX++] = 0;
    }
    else //if (chardata == '-')     //不可显示
    {
        led7_var.bShowBuff[led7_var.bCoordinateX++] = BIT(6);
    }
}

/*----------------------------------------------------------------------------*/
/**@brief   led7_drv 字符串显示函数
   @param   *str：字符串的指针   offset：显示偏移量
   @return  void
   @author  Change.tsai
   @note    void led7_show_string(u8 *str)
*/
/*----------------------------------------------------------------------------*/
void led7_show_string(u8 *str)
{
    while (0 != *str)
    {
        led7_show_char(*str++);
    }
}

/*----------------------------------------------------------------------------*/
/**@brief   Music模式 设备显示
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_show_dev(void)
*/
/*----------------------------------------------------------------------------*/
void led7_show_dev(void)
{
//    /*Music Device type*/

    if((music_ui.ui_curr_device == SD0_DEVICE)||(music_ui.ui_curr_device == SD1_DEVICE))
    {
        LED_STATUS |= LED_SD;
    }
    else if(music_ui.ui_curr_device == USB_DEVICE)
    {
        LED_STATUS |= LED_USB;
    }
}

/*----------------------------------------------------------------------------*/
/** @brief:
    @param:
    @return:
    @author:
    @note:
*/
/*----------------------------------------------------------------------------*/
void led7_show_string_menu(u8 menu)
{
    led7_show_string((u8 *)menu_string[menu]);
}

/*----------------------------------------------------------------------------*/
/**@brief   Music 播放文件号显示函数
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_show_filenumber(void)
*/
/*----------------------------------------------------------------------------*/
void led7_show_filenumber(void)
{
    /*Music File Number info*/
    //printf("ui_music.ui_play_file_num = %u----\n",ui_music.ui_play_file_num);
    itoa4(music_ui.ui_curr_file);
    led7_show_string((u8 *)bcd_number);
    //led7_show_dev();
}


/*----------------------------------------------------------------------------*/
/**@brief   红外输入文件号显示函数
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_show_IR_number(void)
*/
/*----------------------------------------------------------------------------*/
void led7_show_IR_number(void)
{
    /*IR File Number info*/
    itoa4(input_number);
    led7_show_string((u8 *)bcd_number);
}

/*----------------------------------------------------------------------------*/
/**@brief   Music模式 显示界面
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_show_music_main(void)
*/
/*----------------------------------------------------------------------------*/
extern u32 get_decode_time(void);
void led7_show_music_main(void)
{
    //led7_show_string((u8*)"MUSI");
    u16 play_time;

    /*Music Play time info*/
    play_time = get_decode_time();

    itoa2(play_time/60);
    led7_show_string((u8 *)bcd_number);

    itoa2(play_time%60);
    led7_show_string((u8 *)bcd_number);

    led7_show_dev();

    LED_STATUS |= LED_2POINT | LED_MP3;

    if (*music_ui.ui_curr_statu == DECODER_PLAY)
    {
        LED_STATUS |= LED_PLAY;
        LED_STATUS &= ~LED_PAUSE;
        led7_var.bFlashIcon |= LED_2POINT;
    }
    else if (*music_ui.ui_curr_statu == DECODER_PAUSE)
    {
        LED_STATUS &= ~LED_PLAY;
        LED_STATUS |= LED_PAUSE;
    }
//
//    if(mute)
//    {
//        led7_var.bFlashIcon |= LED_MP3;
//        led7_var.bFlashChar = 0x0f;
//    }
//    else
//    {
//        led7_var.bFlashIcon &= ~LED_MP3;
//        led7_var.bFlashChar = 0x00;
//    }
}

/*----------------------------------------------------------------------------*/
/**@brief   EQ显示函数
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_show_volume(void)
*/
/*----------------------------------------------------------------------------*/
//extern u8 eq_mode;
void led7_show_eq(void)
{
    led7_show_string((u8 *)other_string[0]);
    led7_show_char(eq_mode%10 + '0');
}


/*----------------------------------------------------------------------------*/
/**@brief   循环模式显示函数
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_show_volume(void)
*/
/*----------------------------------------------------------------------------*/
//extern u8 play_mode;
void led7_show_playmode(void)
{
    led7_show_string((u8 *)&playmodestr[play_mode-FOP_MAX-1][0]);
}

/*----------------------------------------------------------------------------*/
/**@brief   音量显示函数
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_show_volume(void)
*/
/*----------------------------------------------------------------------------*/
void led7_show_volume(void)
{
    led7_show_string((u8 *)other_string[1]);
    itoa2(dac_var.cur_sys_vol_l);
    led7_show_string((u8 *)bcd_number);
}

/*----------------------------------------------------------------------------*/
/**@brief   FM 模式主界面
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_show_fm_main(void)
*/
/*----------------------------------------------------------------------------*/
void led7_show_fm_main(void)
{
    /*FM - Frequency*/
    itoa4(fm_mode_var->wFreq);

    if (fm_mode_var->wFreq <= 999)
        bcd_number[0] = ' ';

    led7_show_string((u8 *)bcd_number);
    LED_STATUS |= LED_MHZ;
}

/*----------------------------------------------------------------------------*/
/**@brief   FM 模式主界面
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_show_fm_main(void)
*/
/*----------------------------------------------------------------------------*/
void led7_show_fm_station(void)
{
//    /*FM - Station*/
    led7_show_string((u8 *)other_string[2]);
    itoa2(fm_mode_var->wFreChannel);
    led7_show_string((u8 *)bcd_number);
}

#if RTC_CLK_EN
/*----------------------------------------------------------------------------*/
/**@brief   RTC 显示界面
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_show_RTC_main(void)
*/
/*----------------------------------------------------------------------------*/
void led7_show_RTC_main(void)
{
    itoa2(current_time.bHour);
    led7_show_string((u8 *)bcd_number);
    itoa2(current_time.bMin);
    led7_show_string((u8 *)bcd_number);

    led7_var.bFlashIcon |= LED_2POINT;
    LED_STATUS |= LED_2POINT;

    if(rtc_set.rtc_set_mode == RTC_SET_MODE)
    {
        if(rtc_set.calendar_set.coordinate == COORDINATE_MIN)
            led7_var.bFlashChar = BIT(0)|BIT(1);
        else
            led7_var.bFlashChar = BIT(2)|BIT(3);
    }
    else
        led7_var.bFlashChar = 0;

}

/*----------------------------------------------------------------------------*/
/**@brief   Alarm 显示界面
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_show_alarm(void)
*/
/*----------------------------------------------------------------------------*/
#if RTC_ALM_EN
void led7_show_alarm(void)
{
    puts("led7_show_alarm\n");
    itoa2(current_alarm.bHour);
    led7_show_string((u8 *)bcd_number);
    itoa2(current_alarm.bMin);
    led7_show_string((u8 *)bcd_number);

    LED_STATUS |= LED_2POINT;

    if(rtc_set.rtc_set_mode == ALM_SET_MODE)
    {
        if(rtc_set.alarm_set.coordinate == COORDINATE_MIN)
            led7_var.bFlashChar = BIT(0)|BIT(1);
        else
            led7_var.bFlashChar = BIT(2)|BIT(3);
    }

    /*Alarm info - Switch On/Off*/
    if (rtc_set.alarm_set.alarm_sw)
    {
        LED_STATUS |= LED_PLAY;
    }
    else
    {
        LED_STATUS |= LED_PAUSE;
    }
}
#endif
#endif

void music_flash(void)
{
//    led7_var.bFlashIcon |= LED_2POINT | LED_MP3;
//    if (Music_Play_var.bPlayStatus == MAD_PLAY)
//        led7_var.bFlashIcon |= LED_PLAY;
//    else if (Music_Play_var.bPlayStatus == MAD_PAUSE)
//        led7_var.bFlashIcon |= LED_PAUSE;
//    if (device_active == DEVICE_SDMMCA)
//        led7_var.bFlashIcon |= LED_SD;
//    else if (device_active == DEVICE_UDISK)
//        led7_var.bFlashIcon |= LED_USB;
}

void LED_drive7(void)
{
    u8 k,i,j,temp;
    k=0;

//    led7_var.bShowBuff[0]=0xff;
//    led7_var.bShowBuff[1]=0xff;
//    led7_var.bShowBuff[2]=0xff;
//    led7_var.bShowBuff[3]=0xff;
//    led7_var.bShowBuff[4]=0xff;

    led7_var.bShowBuff1[0]=0;
    led7_var.bShowBuff1[1]=0;
    led7_var.bShowBuff1[2]=0;
    led7_var.bShowBuff1[3]=0;
    led7_var.bShowBuff1[4]=0;
    led7_var.bShowBuff1[5]=0;
    led7_var.bShowBuff1[6]=0;

    for(i=0;i<5;i++)
    {
        temp = led7_var.bShowBuff[i];
        if (sys_halfsec)
        {
            if ((led7_var.bFlashIcon) && (i == 4))
            {
                temp = LED_STATUS & (~led7_var.bFlashIcon);
            }
            else if (led7_var.bFlashChar & BIT(i))
            {
                temp = 0x0;
            }
        }

        for(j=0;j<7;j++)
        {
            if(temp & bit_table[j])
            {
                led7_var.bShowBuff1[led_7[k][0]] |= bit_table[led_7[k][1]];
            }
            k++;
        }
        if(j == 7)
        {
            if(temp & bit_table[j])
                led7_var.bShowBuff1[led_7[35][0]] |= bit_table[led_7[35][1]];
        }
    }
}

/*----------------------------------------------------------------------------*/
/**@brief   LED清屏函数
   @param   x：显示横坐标
   @return  void
   @author  Change.tsai
   @note    void led7_clear(void)
*/
/*----------------------------------------------------------------------------*/
void led7_clear(void)
{
    PORTC_OUT &= ~(BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8)|BIT(9));
    PORTC_DIR |=  (BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8)|BIT(9));
    PORTC_PU  &= ~(BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8)|BIT(9));
    PORTC_PD  &= ~(BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8)|BIT(9));
    PORTC_HD  &= ~(BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8)|BIT(9));
}

/*----------------------------------------------------------------------------*/
/**@brief   LED扫描函数
   @param   void
   @return  void
   @author  Change.tsai
   @note    void led7_scan(void)
*/
/*----------------------------------------------------------------------------*/
void led7_scan(void)
{
    static u8 cnt;
    u8 seg;

    LED_drive7();

    seg = led7_var.bShowBuff1[cnt];

    led7_clear();

    switch(cnt)
    {
    case 0:
        PORTC_OUT|= BIT(3);
        PORTC_HD |= BIT(3);
        PORTC_DIR &= ~BIT(3);
        break;

    case 1:
        PORTC_OUT|= BIT(4);
        PORTC_HD |= BIT(4);
        PORTC_DIR &= ~BIT(4);
        break;

    case 2:
        PORTC_OUT|= BIT(5);
        PORTC_HD |= BIT(5);
        PORTC_DIR &= ~BIT(5);
        break;

    case 3:
        PORTC_OUT|= BIT(6);
        PORTC_HD |= BIT(6);
        PORTC_DIR &= ~BIT(6);
        break;

    case 4:
        PORTC_OUT|= BIT(7);
        PORTC_HD |= BIT(7);
        PORTC_DIR &= ~BIT(7);
        break;

    case 5:
        PORTC_OUT|= BIT(8);
        PORTC_HD |= BIT(8);
        PORTC_DIR &= ~BIT(8);
        break;

    case 6:
        PORTC_OUT|= BIT(9);
        PORTC_HD |= BIT(9);
        PORTC_DIR &= ~BIT(9);
        break;

    default :
        break;
    }

    if(seg & BIT(0))
    {
        PORTC_OUT &= ~BIT(3);
        PORTC_DIR &= ~BIT(3);
    }

    if(seg & BIT(1))
    {
        PORTC_OUT &= ~BIT(4);
        PORTC_DIR &= ~BIT(4);
    }

    if(seg & BIT(2))
    {
        PORTC_OUT &= ~BIT(5);
        PORTC_DIR &= ~BIT(5);
    }

    if(seg & BIT(3))
    {
        PORTC_OUT &= ~BIT(6);
        PORTC_DIR &= ~BIT(6);
    }

    if(seg & BIT(4))
    {
       PORTC_OUT &= ~BIT(7);
       PORTC_DIR &= ~BIT(7);
    }

    if(seg & BIT(5))
    {
        PORTC_OUT &= ~BIT(8);
        PORTC_DIR &= ~BIT(8);
    }

    if(seg & BIT(6))
    {
        PORTC_OUT &= ~BIT(9);
        PORTC_DIR &= ~BIT(9);
    }
    cnt = (cnt >= 7) ? 0 : cnt+1;
}
#endif
