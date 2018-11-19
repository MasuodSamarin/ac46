#ifndef __UI_CON1_H__
#define __UI_CON1_H__

#include "typedef.h"
#include "font_out.h"
#include "imb_module.h"
#include "syd_file.h"
#include "ui_con.h"

#ifdef WIN32
#pragma pack(push)
#pragma pack(1)
#endif

//�ؼ�����
enum
{
	TYPE_PIC,
	TYPE_TEXT,
	TYPE_TIME,
	TYPE_MENU,
	TYPE_NUMBER,
	TYPE_SLIDER,
	TYPE_PROGRESS,
	TYPE_RADIO,
	TYPE_CHECKBOX,
	TYPE_BUTTON,
	TYPE_LAYER,
	TYPE_CLRSCR,
	TYPE_DRAWSTR,
	TYPE_DRAWPIC,
};

typedef struct
{
	u32 flag;
	u16 fileversion;
	u16 filecount;
}STYFILEHEADER;

typedef struct
{
	u32 num;			//����ؼ�����
	u32 offset;			//����ؼ�ƫ�Ƶ�ַ
} __attribute__((packed)) CONTROL_HEADER;		//8 bytes

typedef struct
{
	u16 x;
	u16 y;
	u16 id;
}PIC;

//1.ͼƬ�ؼ�
typedef struct
{
	u8 layer;
	u16 x;		//x����
	u16 y;		//y����
	u16 width;	//ͼƬ���
	u16 height;	//ͼƬ�߶�
	u16 id;		//ͼƬid��
} __attribute__((packed)) CPIC; //11 Bytes

//2.�ı��ؼ�
typedef enum
{
	UI_STATIC_TEXT,			//��̬��ʾ
	UI_SCROLL_TEXT,			//������ʾ
	UI_KLOK_TEXT,			//����OK������ʾ
}DISP_MODE;

typedef struct
{
	u8 layer;				//ͼ��
	u16 x;					//��ʼx����
	u16 y;					//��ʼy����
	u16 width;				//��ʾ����Ŀ�
	u16 height;				//��ʾ����ĸ�
	u16 backpicture;		//����ͼƬ 0:�ޱ���ͼƬ,������ɫ��Ч ����:����ͼƬID��,������ɫ��Ч
	u8 backcolor;			//������ɫ
	u8 forecolor;			//ǰ����ɫ
	u8 /*FONT_SIZE*/ font_size;	//�ֺ�,֧��С(16x16),��(20x20),��(24x24)�����ֺ�
	u8 /*DISP_MODE*/ dispmode;		//��ʾ��ʽ
	//u8 ttt;
} __attribute__((packed)) CTEXT; //16 Bytes
//˵��:������ɫ��ǰ����ɫΪ8λɫ

//ʱ��ؼ�����
//0:	hh:mm					ʱ�ӣ�����
//1:	hh:mm:ss				ʱ�ӣ����ӣ�����
//2:	yyyy-mm-dd hh:mm:ss		��-��-�� ʱ�ӣ����ӣ�����

//3.ʱ��ؼ�
typedef struct
{
	u8 layer;
	u16 x;				//��ʼx����
	u16 y;				//��ʼy����
	u16 width;			//�ؼ����
	u16 height;			//�ؼ��߶�
	u8  type;			//ʱ����ʾ����
	u16 num_id[12];		//0~9Ϊ���ֵ�ID�ţ�10~11Ϊ�ָ���ID��,ǰ�������ͼ�¼��num_id[10],���һ�ּ�¼��num_id[11]
}__attribute__((packed)) CTIME;// 26 Bytes

//4.�˵��ؼ�
typedef struct
{
	u8 layer;
	u16 x;					//��ʼx����
	u16 y;					//��ʼy����
	u16 width;				//�˵����
	u16 height;				//�˵��߶�
	u16 mItemWidth;			//�˵������ͼ����
	u16 mItemHeight;		//�˵���߶�
	u16 backpic;			//����ͼƬ				ͼƬ�ؼ�id��
	u16 titlepic;			//������ͼƬ
	u16 bottompic;			//״̬��ͼƬ
	u16 activepic;			//���ͼ��
	u16 unactivepic;		//�ǻ��ͼ��
	u16 OneChoiceSel;		//��ѡ��ѡ��ͼ��
	u16 OneChoiceNoSel;		//��ѡδѡ��ͼ��
	u16 MultiChoiceSel;		//��ѡ��ѡ��ͼ��
	u16 MultiChoiceNoSel;	//��ѡδѡ��ͼ��
	u16 selpic;				//����ѡ��ͼƬ1
	u16 scrollbar;			//������
	u16 scrollbar_p;		//������ͼƬID��
	u8 menuNumber;          //�˵�����
}__attribute__((packed)) CMENU; //40 Bytes

//5.�������ؼ�
typedef struct
{
	u8 layer;
	u16 x;				//��ʼx����
	u16 y;				//��ʼy����
	u16 width;			//�ؼ����
	u16 height;			//�ؼ��߶�
	PIC bar;			//������ͼƬid��
	PIC slider;			//������ͼƬid��
	u16 cnum[3];		//���ֿؼ���id��,�ֱ��ʾ��Сֵ/��ǰֵ/���ֵ		���ֿؼ�id
	u16 backpic;		//����ͼƬ�ؼ�ID��								ͼƬ�ؼ�id
}__attribute__((packed)) CSLIDER;

//6.�������ؼ�
typedef struct
{
	u8 layer;
	u16 x;				//��ʼx����
	u16 y;				//��ʼy����
	u16 width;			//�ؼ����
	u16 height;			//�ؼ��߶�
	PIC bar;			//����С����
	PIC progress;		//������
	PIC percent;        //�ٷֺ�
	u16 number;			//���ֿؼ�id��
	u16 backpicture;	//����ͼƬ					ͼƬ�ؼ�id
}__attribute__((packed)) CPROGRESS;//31byte

//7.���ֿؼ�
typedef struct
{
	u8 layer;
    u16 x;          //��ʼx����
	u16 y;          //��ʼy����
	u16 width;      //�ؼ����
	u16 height;	   //�ؼ��߶�
    u16 num_id[10];  //����0-9��ͼƬID��
    u16 num_bits;   //��ֵ��Чλ��
}__attribute__((packed)) CNUMBER;

//8.��ѡ�ؼ�
typedef struct
{
	u8 layer;
	u16 x;		//x����
	u16 y;		//y����
	u16 width;	//�ؼ����
	u16 height;	//�ؼ��߶�
	PIC sel;	//ѡ��ͼ��
	PIC unsel;	//δѡ��ͼ��
	PIC strid;  //�ַ���id��
}__attribute__((packed)) CRADIO;//27

//9.��ѡ�ؼ�
typedef struct
{
	u8 layer;
	u16 x;			//x����
	u16 y;			//y����
	u16 width;		//�ؼ����
	u16 height;		//�ؼ��߶�
	PIC sel;		//ѡ��ͼ��
	PIC unsel;		//δѡ��ͼ��
	PIC strid;		//�ַ���id��
	u8 status;      //Ĭ����ѡ��״̬����δѡ��״̬
}__attribute__((packed)) CHECKBOX;//28

//10.��ť�ؼ�
typedef struct
{
	u8 layer;
	u16 x;			//x����
	u16 y;			//y����
	u16 width;		//�ؼ����
	u16 height;		//�ؼ��߶�
	PIC picid;		//��ťͼƬ
	PIC strid;		//��ť�ı�
}__attribute__((packed)) CBUTTON;

//11.ͼ��
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

bool ui_init(u16 width,u16 height);
bool ui_pic(u16 id,GUI_POINT *point,u8 flags);
bool ui_menu(u16 id,MPARAM *pMenu);
bool ui_lcd_menu(u16 id,MPARAM *pMenu);
bool ui_number(u16 id,u32 num,u16 x,u16 y,u8 flags);
bool ui_time(u16 id,TIME *time,u16 x,u16 y,u8 flags);
bool ui_text(u16 id,DTEXT *text);
bool ui_progress(u16 id,u8 percent);
bool ui_slider(u16 id,SLIDER_HOOK hook,u8 cmd);
bool ui_layer(u16 id,LAYER *layer);
bool ui_radio(u16 id,u8 status);
bool ui_check(u16 id,u8 status);
bool ui_button(u16 id);

#endif
