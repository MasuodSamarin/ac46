#ifndef _DECODER_PHY_H_
#define _DECODER_PHY_H_

//#include "if_dec_file.h"
#include "if_decoder_ctrl.h"
#include "os_api.h"
#include "stdarg.h"
#include "sup_dec_op.h"


//#define UART_DEC_PHY_DEG
#ifdef UART_DEC_PHY_DEG
    #define dec_phy_puts           puts
    #define dec_phy_u32d           put_u32d
    #define dec_phy_u32hex0        put_u32hex0
    #define dec_phy_u32hex         put_u32hex
    #define dec_phy_printf         printf

    #define dec_phy_without_lock0  printf_without_lock
    #define dec_phy_without_lock1  puts_without_lock
    #define dec_phy_u16hex         put_u16hex
    #define dec_phy_u8hex0         put_u8hex0
    #define dec_phy_u8hex          put_u8hex
    #define dec_phy_buf            put_buf
    #define dec_phy_buf0           printf_buf
    #define dec_phy_char           putchar
#else
    #define dec_phy_puts(...)
    #define dec_phy_u32d(...)
    #define dec_phy_u32hex0(...)
    #define dec_phy_u32hex(...)
    #define dec_phy_printf(...)

    #define dec_phy_without_lock0(...)
    #define dec_phy_without_lock1(...)
    #define dec_phy_u16hex(...)
    #define dec_phy_u8hex0(...)
    #define dec_phy_u8hex(...)
    #define dec_phy_buf(...)
    #define dec_phy_buf0(...)
    #define dec_phy_char(...)
#endif



enum
{   MAD_ERROR_FILE_END         = 0x40,
    MAD_ERROR_FILESYSTEM_ERR   = 0x41,              // NO USED
    MAD_ERROR_DISK_ERR         = 0x42,              // NO USED
    MAD_ERROR_SYNC_LIMIT       = 0x43,              // �ļ�����
    MAD_ERROR_FF_FR_FILE_END   = 0x44,              //�������
    MAD_ERROR_FF_FR_END        = 0x45,              // NO USED
    MAD_ERROR_FF_FR_FILE_START = 0x46,              //���˵�ͷ
    MAD_ERROR_LIMIT            = 0x47,              // NO USED
    MAD_ERROR_NODATA           = 0x48,              // NO USED
};

typedef enum __DECODE_STATUS
{
    DECODER_STOP = 0,
    DECODER_PAUSE,
    DECODER_PLAY = 0x55aa,
}_DECODE_STATUS;

typedef enum __FORMAT_STATUS
{
    FORMAT_OK = 0,
    FORMAT_OK_BUT_NO_SUPPORT,                  //��ʽ��ȷ����֧�ֵ�ʱ�򣬲��ټ������
    FORMAT_ERR,
    FORMAT_NOT_DETECTED,
}_FORMAT_STATUS;

typedef struct __FF_FR
{
    tbool ff_fr_enable;
    u32 ff_disable_time;  //��������л�����ʱ�������������ܿ��������
    u32 fr_disable_time;  //���˵����л�����ʱ�������������ܿ��˵�����
    bool fr_stop_dec;     //�����и���ʹ��
    volatile u8 ff_fr;
}_FF_FR;

struct if_dec_file {
	int (*read)(void *priv, void *data, int len);
	int (*seek)(void *priv, int from, int offset);
};


typedef struct _DEC_PHY
{
	const char *father_name;
	decoder_ops_t *dec_ops;
	void *dc_buf;
	struct if_decoder_io dec_io;
	struct if_dec_file *file_ops;
	void *dec_dev_priv;
	u32 (*dev_online)(void *priv);
	volatile _DECODE_STATUS status;
	volatile u8 busy;
	_FF_FR ff_fr;
}DEC_PHY;


typedef struct _DEC_API_IO
{
    void *father_name;
    void *f_p;
    u16(*f_read)(void *fp , void *buff, u16 len);
    u32 (*f_seek)(void *fp , u8 type, u32 offsiz);
    u32 (*set_music_info)(dec_inf_t *inf,tbool wait);
    _OP_IO output;
    u32 op_cnt; //����������ۼ���
    volatile tbool dev_active;
}DEC_API_IO;

///*AAC����*/
typedef enum
{
    SET_DEFAULT_NOTING,
    SET_AAC_SR_NCH_BR ,
}_MUSIC_DEC_CONFIG;

typedef struct _AAC_DEFAULT_SETTING
{
    u32 samplerate;
    u32 nchannels;
    u32 bitrate;
}AAC_DEFAULT_SETTING;


typedef struct _DEC_API
{
    DEC_PHY *phy_ops;
    void *format_name;
    void *op_priv;
    void *(*dec_op_clr)(void *priv);
    tbool *(*dec_op_over)(void *priv);
    void *dec_phy_name;
    AAC_DEFAULT_SETTING AAC_info;
    tbool save_brk;
//    tbool enable_brk;
    u32 bp_size; //�ϵ㳤��
    u8 *bp_buff; //�ϵ㳤��
    dec_inf_t *inf;
    u32 type_enable;
    u8 ef_enable;
    void *ef_info;
    u8 eq;
}DEC_API;

#ifdef AC46_512K
enum
{
   DEC_TYPE_SBC          =0,
   DEC_TYPE_MP3          ,
};
#define DEC_PHY_SBC  BIT(DEC_TYPE_SBC)
#define DEC_PHY_MP3  BIT(DEC_TYPE_MP3)
#else
#define DEC_TYPE_FLAC_ENABLE
#define DEC_TYPE_APE_ENABLE

enum
{   DEC_TYPE_WAV         = 0,
    DEC_TYPE_WMA         ,
    DEC_TYPE_SBC         ,
    DEC_TYPE_AAC         ,
#ifdef DEC_TYPE_FLAC_ENABLE
    DEC_TYPE_FLAC        ,
#endif

#ifdef DEC_TYPE_APE_ENABLE
    DEC_TYPE_APE         ,
#endif
    DEC_TYPE_MP3         ,

};

    #define DEC_PHY_WAV  BIT(DEC_TYPE_WAV)
    #define DEC_PHY_WMA  BIT(DEC_TYPE_WMA)
    #define DEC_PHY_SBC  BIT(DEC_TYPE_SBC)
    #define DEC_PHY_AAC  BIT(DEC_TYPE_AAC)

#ifdef DEC_TYPE_FLAC_ENABLE
    #define DEC_PHY_FLAC BIT(DEC_TYPE_FLAC)
#else
    #define DEC_PHY_FLAC 0
#endif

#ifdef DEC_TYPE_APE_ENABLE
    #define DEC_PHY_APE  BIT(DEC_TYPE_APE)
#else
    #define DEC_PHY_APE 0
#endif

    #define DEC_PHY_MP3  BIT(DEC_TYPE_MP3)
#endif



//DEC_PHY_WAV |  DEC_PHY_WMA | DEC_PHY_SBC | DEC_PHY_AAC | DEC_PHY_FLAC | DEC_PHY_APE | DEC_PHY_MP3

#define MIDI_CMD_SAMPLERATE   0

#define MIDI_SAMPLE_R22050   22050
#define MIDI_SAMPLE_R16000   16000
#define MIDI_SAMPLE_R12000   12000
#define MIDI_SAMPLE_R8000    8000

#define STOP_DEC_NULL           BIT(0)
#define HAS_STOP_DEC_OPT        BIT(1)
#define STOP_DEC_GOT_BRKINFO    BIT(2)

void *malloc_fun(void *ptr,u32 len,char *info);
void free_fun(void **ptr);

u8 dec_ff_fr(void *priv,u8 ff_fr);
void decoder_phy_task(void *p_arg);
u32 stop_decoder(DEC_API *dec_api);
u32 start_decoder(DEC_API *dec_api,DEC_API_IO *api_io,void *bp_buf);
u32 kick_start_decoder(DEC_API *dec_api);
_DECODE_STATUS pp_decode(DEC_API *dec_api);
#endif
