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

//文本编码
#define ANSI			0x01
#define UNICODE_BE		0x02
#define UNICODE_LE		0x04
#define	SCROLL_RESET	0x08

typedef struct
{
	u8 *buf;
	u16 len;
	u8 flags;		//编码类型 UNICODE_BE、UNICODE_LE、ANSI
}DTEXT;

typedef struct
{
	u16 year;		//年
	u8 month;		//月
	u8 day;			//日
	u8 hour;		//时
	u8 minute;		//分
	u8 second;		//秒
}TIME;

#define MENU_NODE  u8

enum
{
	MENU_INIT,
	MENU_ACTIVE,
	MENU_SELECT,
};


#define OTHER_SCREEN		0xfe//其他界面
#define NO_MENU				0xff

typedef u8 (*MenuFun)(u16 id, u8 mode);//菜单函数指针
typedef struct
{
    u16 id;					//菜单项索引号
    MENU_NODE child_node;	//下一级菜单 NO_MENU:无下级菜单 其他:下级菜单索引
} S_MENU;

typedef struct
{
	u8 layer;
	u8 color;
}BORDER;//图层蒙板

//菜单样式
typedef enum
{
    STYLE_NORMAL,       //正常
    STYLE_ONE_CHOICE,   //单选
    STYLE_MULTI_CHOICE, //多选
    STYLE_USER_DEFINED, //自定义
	STYLE_CONFIRM,		//确认
} MENU_STYLE;

//菜单消息
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
    MENU_NODE father_node;  //上一级菜单
    MENU_NODE node;			//当前菜单索引
    u16 title;				//菜单标题,0无标题,非0有标题
    MENU_STYLE style;		//菜单样式 0:正常 1:单选 2:多选 3.自定义
    const S_MENU  *menu;	//菜单项 指向S_MENU的指针
    const u16  *pic;		//图标 指向菜单项图标的指针,只有选择自定义样式有效,	没有则设为NULL
    MenuFun fun;			//菜单回调函数
    u8 menuCnt;				//该级菜单个数
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
	u16 timeout;		//超时退出时间设置(单位：秒),为0则禁止超时退出
	OSDCOLOR act_color;		//活动菜单项字体颜色
	OSDCOLOR unact_color;	//非活动菜单项背景颜色
	BORDER border;			//图层蒙板边框
	u16 selpic2;			//高亮选中图片2(子菜单)
	s16 icon_offset;        //菜单左侧图标偏移
	s16 child_area_x;       //子菜单区域x偏移
	s16 child_area_y;       //子菜单区域y偏移
	s16 child_area_width;   //子菜单区域width偏移
	s16 child_area_height;  //子菜单区域height偏移
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
//mode：表示获取当前值，前一位置值，后一位置值


typedef struct
{
	u16 id;				//id号
	u8 type;			//控件类型
	void *p;			//参数
	u8 state;			//状态 显示/隐藏/重绘
	GUI_RECT rect;		//区域
	void *pNextObj;		//指向下一个控件
}WIN;

#ifndef _STRUCT_LAYER
#define _STRUCT_LAYER
typedef struct
{
	u8 /*LAYER_TYPE*/type;	//图层序号
	u8 alpha;			//图层透明度，64 level(0~63)
	u16 x;				//x坐标
	u16 y;				//y坐标
	u16 width;			//图层宽度
	u16 height;			//图层高度
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
