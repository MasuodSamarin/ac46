#ifndef __UI_CON_H__
#define __UI_CON_H__

#include "typedef.h"
#include "font_out.h"
#include "imb_module.h"
#include "syd_file.h"


#ifdef WIN32
#pragma pack(push)
#pragma pack(1)
#endif


#define USE_ORIG_COLOR      0x00
#define USE_NEW_COLOR       0x01
#define ERASE_BACKGROUND    0x02

//�ı�����
#define ANSI			0x01
#define UNICODE_BE		0x02
#define UNICODE_LE		0x04
#define	SCROLL_RESET	0x08

typedef struct
{
	u8 *buf;
	u16 len;
	u8 flags;		//�������� UNICODE_BE��UNICODE_LE��ANSI
}DTEXT;

typedef struct
{
	u16 year;		//��
	u8 month;		//��
	u8 day;			//��
	u8 hour;		//ʱ
	u8 minute;		//��
	u8 second;		//��
}TIME;

#define MENU_NODE  u8

enum
{
	MENU_INIT,
	MENU_ACTIVE,
	MENU_SELECT,
};


#define OTHER_SCREEN		0xfe//��������
#define NO_MENU				0xff

typedef u8 (*MenuFun)(u16 id, u8 mode);//�˵�����ָ��
typedef struct
{
    u16 id;					//�˵���������
    MENU_NODE child_node;	//��һ���˵� NO_MENU:���¼��˵� ����:�¼��˵�����
} S_MENU;

typedef struct
{
	u8 layer;
	u8 color;
}BORDER;//ͼ���ɰ�

//�˵���ʽ
typedef enum
{
    STYLE_NORMAL,       //����
    STYLE_ONE_CHOICE,   //��ѡ
    STYLE_MULTI_CHOICE, //��ѡ
    STYLE_USER_DEFINED, //�Զ���
	STYLE_CONFIRM,		//ȷ��
} MENU_STYLE;

//�˵���Ϣ
enum
{
	UI_MSG_PREV,
	UI_MSG_NEXT,
	UI_MSG_CONFIRM,
	UI_MSG_100MS,
	UI_MSG_200MS,
	UI_MSG_500MS,
	UI_MSG_RETURN,
	UI_MSG_EXIT,
	UI_MSG_INVALID,
};

typedef struct
{
	u8 layer;
	u16 x;
	u16 y;
	u16 width;
	u16 height;
	u16 currpage;
	u16 totalpage;
}MENU_INFO;

typedef struct
{
    MENU_NODE father_node;  //��һ���˵�
    MENU_NODE node;			//��ǰ�˵�����
    u16 title;				//�˵�����,0�ޱ���,��0�б���
    MENU_STYLE style;		//�˵���ʽ 0:���� 1:��ѡ 2:��ѡ 3.�Զ���
    const S_MENU  *menu;	//�˵��� ָ��S_MENU��ָ��
    const u16  *pic;		//ͼ�� ָ��˵���ͼ���ָ��,ֻ��ѡ���Զ�����ʽ��Ч,	û������ΪNULL
    MenuFun fun;			//�˵��ص�����
    u8 menuCnt;				//�ü��˵�����
}S_MENULIST;

typedef void (*MenuHook)(MENU_INFO *info);
typedef u16 (*MsgHook)(void);
typedef void (*KeyHook)(void);
//typedef void (*LcdHook)(u8 start_page, u8 page_len,u8 * pbuf);
typedef struct
{
	MenuHook title;
	MenuHook bottom;
	MsgHook  msg_hook;
	KeyHook  key_in_hook;
	KeyHook  key_out_hook;
//	LcdHook  lcd_draw;
	S_MENULIST *list;
	u16 timeout;		//��ʱ�˳�ʱ������(��λ����),Ϊ0���ֹ��ʱ�˳�
	OSDCOLOR act_color;		//��˵���������ɫ
	OSDCOLOR unact_color;	//�ǻ�˵������ɫ
	BORDER border;			//ͼ���ɰ�߿�
	u16 selpic2;			//����ѡ��ͼƬ2(�Ӳ˵�)
	s16 icon_offset;        //�˵����ͼ��ƫ��
	s16 child_area_x;       //�Ӳ˵�����xƫ��
	s16 child_area_y;       //�Ӳ˵�����yƫ��
	s16 child_area_width;   //�Ӳ˵�����widthƫ��
	s16 child_area_height;  //�Ӳ˵�����heightƫ��
}MPARAM;


typedef struct
{
	u32 min_val;
	u32 curr_val;
	u32 max_val;
	u16 total_len;
	u16 curr_pos;
}DSLIDER;


#define UI_SLIDER_CURR   0
#define UI_SLIDER_PREV   1
#define UI_SLIDER_NEXT   2
typedef u16 (*SLIDER_HOOK)(u8 mode,DSLIDER *s_param);
//mode����ʾ��ȡ��ǰֵ��ǰһλ��ֵ����һλ��ֵ


typedef struct
{
	u16 id;				//id��
	u8 type;			//�ؼ�����
	void *p;			//����
	u8 state;			//״̬ ��ʾ/����/�ػ�
	GUI_RECT rect;		//����
	void *pNextObj;		//ָ����һ���ؼ�
}WIN;

#ifndef _STRUCT_LAYER
#define _STRUCT_LAYER
typedef struct
{
	u8 /*LAYER_TYPE*/type;	//ͼ�����
	u8 alpha;			//ͼ��͸���ȣ�64 level(0~63)
	u16 x;				//x����
	u16 y;				//y����
	u16 width;			//ͼ����
	u16 height;			//ͼ��߶�
}__attribute__((packed)) LAYER;//10 bytes
#endif

#ifdef WIN32
#pragma pack(pop)
#endif

extern sdfile_t resfile;
extern sdfile_t styfile;

enum
{
	SHOW_CURR_VALUE,
	SHOW_NEXT_VALUE,
	SHOW_PREV_VALUE,
};

bool ui_init(u16 width,u16 height);
u8   ui_get_layer_num();
bool ui_layer(u16 id,LAYER *layer);
//bool ui_process();
bool ui_screen_to_layer(u8 layer,u16 x,u16 y,u16 w,u16 h,GUI_POINT *point);
void ui_clear_screen(u8 layer,u16 x,u16 y,u16 width,u16 height,u32 color);

#endif
