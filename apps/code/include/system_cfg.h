#ifndef SYSTEM_CFG_H
#define SYSTEM_CFG_H

#include "typedef.h"

#define SYSCFG_RW_SINGLE_FILE  0
#define SYSCFG_RW_MULTI_FILE   1

struct tag_type{
	u8 rw:2;
	u8 payload:1;
	u8 init:1;
	u8 res:4;
}__attribute((packed));

struct syscfg_tag{
	struct  tag_type h;
	u8  tag_id;
	u16 tag_len;
	u8 data[0];
}__attribute((packed));


struct syscfg_file{
	int (*open)(int id, int fsize);
	int (*read)(void *buf, int len);
	int (*write)(void *buf, int len);
	int (*seek)(int from, int pos);   //from: 0 begin  1 curr
	int (*close)();
};

#define SYS_TAG_RO    1
#define SYS_TAG_RW    2
#define SYS_TAG_RRW    (SYS_TAG_RO|SYS_TAG_RW)

#define SYS_TAG_INIT_EN 	1
#define SYS_TAG_INIT_DIS 	0


//#define  SYSCFG_BTSTACK 				(0)	//协议配置
//#define  SYSCFG_UDISK 					(1)	//udisk配置
//#define  SYSCFG_LED_SHOW       			(2)	//LED显示配置
//#define  SYSCFG_MIC_GAIN                (3) //设置mic增益最大值0x3FF
//#define  SYSCFG_PROMPT_TONE  			(4)	//提示音配置
//#define  SYSCFG_KEY_MSG  				(5)	//按键消息配置
//#define  SYSCFG_DONGLE_USB_CFG          (6)  //dongle USB配置
//#define  SYSCFG_REMOTE_DB               (7)
//#define  SYSCFG_REMOTE_DB_END           (7+20)
//#define  SYSCFG_FILE_BREAKPOINT         (28)


#ifndef offsetof
 #define offsetof(type, memb) \
	((unsigned long)(&((type *)0)->memb))
#endif


#define system_cfg_define(name) \
	struct tag_##name { \
		struct tag_type h; \
		u8 tag_id; \
		u16 tag_len; \

#define system_cfg_define_end() \
		u16 _crc16; \
		u8 _tag_end[0]; \
	}__attribute__((packed));

#define system_cfg_register(name, id, _rw, _init) \
	static struct tag_##name name __attribute__((section(".system_cfg"))) = { \
		.h = { \
			.rw = _rw, \
			.payload = 1, \
			.init = _init, \
		}, \
		.tag_id = id,

#define system_cfg_register_end(name) \
	   .tag_len = offsetof(struct tag_##name, _tag_end)-sizeof(struct syscfg_tag), \
	};

#define __system_cfg_register(name, id, len) \
	static struct syscfg_tag name __attribute__((section(".system_cfg"))) = { \
		.h = { \
			.rw = SYS_TAG_RW, \
			.payload = 0, \
			.init = 0, \
		}, \
		.tag_id = id, \
		.tag_len = len, \
	};


#define system_cfg_read(tag)  \
	__system_cfg_read((struct syscfg_tag *)tag, ((struct syscfg_tag *)(tag))->data, 0, (tag)->tag_len)


#define system_cfg_write(tag)  \
	do { \
		u8 *data = ((struct syscfg_tag *)(tag))->data; 		\
		(tag)->_crc16 = crc16(data, (tag)->tag_len-2); 		\
		__system_cfg_write((struct syscfg_tag *)(tag), data, 0, (tag)->tag_len); 	\
	}while(0)


#define system_cfg_write_member(tag, memb)  \
	do { \
		u8 *data = ((struct syscfg_tag *)(tag))->data; 		\
		(tag)->_crc16 = crc16(data, (tag)->tag_len-2); 		\
		__system_cfg_write((struct syscfg_tag *)tag, data, \
				offsetof(typeof(*tag), memb), sizeof((tag)->memb)); \
		__system_cfg_write((struct syscfg_tag *)tag, &(tag)->_crc16, \
				offsetof(typeof(*tag), _crc16), sizeof((tag)->_crc16)); \
	}while(0)


#define sys_tag_list_for_each(t)  \
	for (t=system_cfg_begin; t<system_cfg_end; \
			t=(typeof(*t) *)((u8 *)t+sizeof(*t)+ \
				((!t->h.payload)?0:t->tag_len)))

extern struct syscfg_tag system_cfg_begin[];
extern struct syscfg_tag system_cfg_end[];

int __system_cfg_read(struct syscfg_tag *t, void *buf, int offset, int len);

int __system_cfg_write(struct syscfg_tag *tag, void *buf, int offset, int len);

void system_cfg_init(const struct syscfg_file *ro_file,
					 const struct syscfg_file *rw_file);


#endif

