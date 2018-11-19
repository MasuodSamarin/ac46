#include "disp.h"
#include "font_out.h"
#include "dc_showres.h"
#include "app_cfg.h"
#include "os_api.h"
#include "ui.h"
#include "msg.h"
#include "menu.h"
#include "ui_api.h"
#include "ui_con.h"
#include "ui_common.h"

extern u8 disp_buf[];

u8 get_u4hex(u8 dat)
{
    dat = 0xf & dat;
    if(dat>9){
        return (dat - 10 + 'A');
    }else{
        return (dat + '0');
    }
}



/*----------------------------------------------------------------------------*/
/**@brief
   @param   void
   @return  void
   @note    void disp_waiting(void)
*/
/*----------------------------------------------------------------------------*/
void disp_waiting(void)
{
    ui_pic(DVcRzImg1_1,NULL,0);
}



/*----------------------------------------------------------------------------*/
/**@brief
   @param   void
   @return  void
   @note    void disp_waiting(void)
*/
/*----------------------------------------------------------------------------*/
void disp_bt_search_device(void)
{
    DTEXT search_txt;
    DTEXT dev_name_txt;
    DTEXT dev_add_txt;


    search_txt.buf = "ËÑË÷ÖÐ";
    //put_buf(search_txt.buf,2);
    search_txt.flags = ANSI;
    search_txt.len = strlen(search_txt.buf);
    ui_text(DVcTxt1_2, &search_txt);

    dev_name_txt.buf = "---------------";
    dev_name_txt.flags = ANSI;
    dev_name_txt.len = strlen(dev_name_txt.buf);
    ui_text(DVcTxt2_2, &dev_name_txt);
//
    dev_add_txt.buf = "--:--:--:--:--:--";
    dev_add_txt.flags = ANSI;
    dev_add_txt.len = strlen(dev_add_txt.buf);
    ui_text(DVcTxt3_2, &dev_add_txt);
    //put_buf(disp_buf,8*128);
}


void disp_bt_connect_device(void)
{
    DTEXT search_txt;
    DTEXT dev_name_txt;
    DTEXT dev_add_txt;

    search_txt.buf = "Á¬½ÓÖÐ";
    //put_buf(search_txt.buf,2);
    search_txt.flags = ANSI;
    search_txt.len = strlen(search_txt.buf);
    ui_text(DVcTxt1_2, &search_txt);
}

void disp_bt_device_add(u8 *targetaddr)
{
    DTEXT dev_add_txt;


    u8 addr_disp_buf[6*2+5+1];

    addr_disp_buf[0]  = get_u4hex(targetaddr[0]>>4);
    addr_disp_buf[1]  = get_u4hex(targetaddr[0]);
    addr_disp_buf[2]  = ':';
    addr_disp_buf[3]  = get_u4hex(targetaddr[1]>>4);
    addr_disp_buf[4]  = get_u4hex(targetaddr[1]);
    addr_disp_buf[5]  = ':';
    addr_disp_buf[6]  = get_u4hex(targetaddr[2]>>4);
    addr_disp_buf[7]  = get_u4hex(targetaddr[2]);
    addr_disp_buf[8]  = ':';
    addr_disp_buf[9]  = get_u4hex(targetaddr[3]>>4);
    addr_disp_buf[10] = get_u4hex(targetaddr[3]);
    addr_disp_buf[11] = ':';
    addr_disp_buf[12] = get_u4hex(targetaddr[4]>>4);
    addr_disp_buf[13] = get_u4hex(targetaddr[4]);
    addr_disp_buf[14] = ':';
    addr_disp_buf[15] = get_u4hex(targetaddr[5]>>4);
    addr_disp_buf[16] = get_u4hex(targetaddr[5]);
    addr_disp_buf[17] = 0;


    dev_add_txt.buf = addr_disp_buf;
    dev_add_txt.flags = ANSI;
    dev_add_txt.len = strlen(dev_add_txt.buf);
    ui_text(DVcTxt3_2, &dev_add_txt);

}

bool device_name_parse_and_display(u8* name)
{
    DTEXT dev_add_txt;
    u32 i = 0;
    u32 pos = 0;
    u16 unicode16;



    u8 name_disp_buf[16];
    memset(name_disp_buf, 0x00, sizeof(name_disp_buf));

    while(1)
    {
        if(name[i] == 0){
            break;
        }

        if( name[i] <= 0x7f ){
            name_disp_buf[pos] = name[i];
            name_disp_buf[pos+1] = 0;
            i += 1;
            pos += 1;
        }else if(name[i] <= 0xdf){
            unicode16 = (((u16)name[i+0] << 6) & 0x07c0) | (((u16)name[i+1]) & 0x003f);
            name_disp_buf[pos+0] = (u8)unicode16;
            name_disp_buf[pos+1] = (u8)(unicode16>>8);
            i += 2;
            pos += 2;
        }else if(name[i] <= 0xef){
            unicode16 = (((u16)name[i+0] << 12) & 0xf000) | (((u16)name[i+1] << 6) & 0x0fc0) | (((u16)name[i+2]) & 0x003f);
            name_disp_buf[pos+0] = (u8)unicode16;
            name_disp_buf[pos+1] = (u8)(unicode16>>8);
            i += 3;
            pos += 2;
        }

    }

    puts("\n---------show name   -----------\n");
    //put_buf(name_disp_buf, 16);

    if(pos == 0){
        return FALSE;
    }

    dc_clear_screen_area(0, 2, 128, 2);

    dev_add_txt.buf = name_disp_buf;
    dev_add_txt.flags = ANSI;
    dev_add_txt.len = strlen(dev_add_txt.buf);
    ui_text(DVcTxt2_2, &dev_add_txt);

    return TRUE;
}

void disp_default_name(void)
{
    DTEXT dev_name_txt;
    DTEXT dev_add_txt;

    dev_name_txt.buf = "---------------";
    dev_name_txt.flags = ANSI;
    dev_name_txt.len = strlen(dev_name_txt.buf);
    ui_text(DVcTxt2_2, &dev_name_txt);
//
    dev_add_txt.buf = "--:--:--:--:--:--";
    dev_add_txt.flags = ANSI;
    dev_add_txt.len = strlen(dev_add_txt.buf);
    ui_text(DVcTxt3_2, &dev_add_txt);

}

void disp_bt_a2dp(void)
{
    DTEXT search_txt;
    DTEXT dev_name_txt;
    DTEXT dev_add_txt;

    search_txt.buf = "²âÊÔ¸ß¼¶ÒôÆµ";
    //put_buf(search_txt.buf,2);
    search_txt.flags = ANSI;
    search_txt.len = strlen(search_txt.buf);
    ui_text(DVcTxt1_2, &search_txt);
}

void disp_bt_hfp(void)
{
    DTEXT search_txt;
    DTEXT dev_name_txt;
    DTEXT dev_add_txt;

    search_txt.buf = "²âÊÔµç»°";
    //put_buf(search_txt.buf,2);
    search_txt.flags = ANSI;
    search_txt.len = strlen(search_txt.buf);
    ui_text(DVcTxt1_2, &search_txt);
}

void disp_bt_hid(void)
{
    DTEXT search_txt;
    DTEXT dev_name_txt;
    DTEXT dev_add_txt;

    search_txt.buf = "²âÊÔ×ÔÅÄ";
    //put_buf(search_txt.buf,2);
    search_txt.flags = ANSI;
    search_txt.len = strlen(search_txt.buf);
    ui_text(DVcTxt1_2, &search_txt);
}

void disp_bt_offset(void)
{
    DTEXT search_txt;
    DTEXT dev_name_txt;
    DTEXT dev_add_txt;

    search_txt.buf = "²âÊÔÆµÆ«";
    //put_buf(search_txt.buf,2);
    search_txt.flags = ANSI;
    search_txt.len = strlen(search_txt.buf);
    ui_text(DVcTxt1_2, &search_txt);
}

void disp_bt_value_offset(u32 value1, s32 value2)
{
    DTEXT search_txt;
    DTEXT dev_name_txt;
    DTEXT dev_add_txt;

    u8 test_buf[16] = "ÆµÆ«: fffffKHZ";

    //put_buf(search_txt.buf,2);

    if(value2 > 0xffff)
    {

    }
    else
    {
        memset(&test_buf[6],' ',5);
        if(value2 > 999)
        {
        if(value1)
        {
            test_buf[6] = '-';
        }
	        else
	        {
	            test_buf[6] = '+';
	        }

        itoa4(value2);
        memcpy(&test_buf[7],(u8 *)bcd_number,4);
        }
        else if(value2 > 99)
        {
            if(value1)
            {
                test_buf[7] = '-';
            }
            else
            {
                test_buf[7] = '+';
            }
            itoa3(value2);
            memcpy(&test_buf[8],(u8 *)bcd_number,3);
        }
        else if(value2 > 9)
        {
            if(value1)
            {
                test_buf[8] = '-';
            }
            else
            {
                test_buf[8] = '+';
            }
            itoa2(value2);
            memcpy(&test_buf[9],(u8 *)bcd_number,2);
        }
        else
        {
            if(value1)
            {
                test_buf[9] = '-';
            }
            else
            {
                test_buf[9] = '+';
            }
            itoa1(value2);
            memcpy(&test_buf[10],(u8 *)bcd_number,1);
        }
    }

    search_txt.buf = test_buf;
    search_txt.flags = ANSI;
    search_txt.len = strlen(search_txt.buf);
    ui_text(DVcTxt4_2, &search_txt);

}
void ui_menu_api(int menu0,int menu1,int menu2)
{

    switch(menu0)
    {
    case BLUETOOTH_CLEAR_LCD:
        lcd_clear();
        break;

    case MENU_WAIT:
        lcd_clear();
        disp_waiting();
        break;

    case MENU_BT_SEARCH_DEVICE:
        lcd_clear();
        disp_bt_search_device();
        break;

    case MENU_BT_CONNECT_DEVICE:
        dc_clear_screen_area(0, 0, 128, 2);
        disp_bt_connect_device();
        break;

    case MENU_BT_DEVICE_ADD:
        dc_clear_screen_area(0, 4, 128, 2);
        disp_bt_device_add((u8 *)menu1);
        break;

    case BLUETOOTH_SHOW_DEVICE_ADDR_NAME_DEFAULT:
        dc_clear_screen_area(0, 2, 128, 4);
        disp_default_name();
        break;

    case MENU_BT_DEVICE_NAME:
        device_name_parse_and_display((u8 *)menu1);
        break;

    case BLUETOOTH_TEST_A2DP:
        dc_clear_screen_area(0, 0, 128, 2);
        disp_bt_a2dp();
        break;

    case BLUETOOTH_TEST_HFP:
        dc_clear_screen_area(0, 0, 128, 2);
        disp_bt_hfp();
        break;

    case BLUETOOTH_TEST_HID:
        dc_clear_screen_area(0, 0, 128, 2);
        disp_bt_hid();
        break;

    case BLUETOOTH_TEST_OFFSET:
        dc_clear_screen_area(0, 0, 128, 2);
        disp_bt_offset();
        break;

    case BLUETOOTH_VALUE_OFFSET:
        dc_clear_screen_area(0, 6, 128, 2);
        disp_bt_value_offset(menu1,menu2);
        break;
    case MENU_HALF_SEC_REFRESH:
        break;
    }
    draw_lcd_buf();
}

static void  disp_task(void *p_arg)
{

    p_arg = p_arg;

    int msg[4];

    lcd_init();

    os_taskq_post("DispTask", 2, MSG_DISP_MENU,MENU_WAIT);
    while(1)
    {
        os_taskq_pend(0, ARRAY_SIZE(msg), &msg);

        switch(msg[0])
        {
        case MSG_DISP_MENU:
            ui_menu_api(msg[1],msg[2],msg[3]);
            break;

        default:
            break;
        }
    }

}

void disp_task_init(void)
{
    puts("disp task init \n");
    os_task_create(disp_task,(void *)0,TaskDispPrio,32,"DispTask");
}

void disp_test_offset(void)
{
    os_taskq_post("DispTask", 2, MSG_DISP_MENU,BLUETOOTH_TEST_OFFSET);
}

void disp_value_offset(u32 en, s32 num)
{
    os_taskq_post("DispTask", 4, MSG_DISP_MENU,BLUETOOTH_VALUE_OFFSET,en,num);
}

