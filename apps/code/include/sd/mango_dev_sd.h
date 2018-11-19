#ifndef _MANGO_DEV_SD_H_
#define _MANGO_DEV_SD_H_

#include "typedef.h"
#include "device_driver.h"
#include "os_api.h"

/**---------------------enum��----------------------**/
/**---------------------------------------------------**/
/*sd����ʧ���б�*/
enum
{
    SD_SUCC = 0x0,
    SD_ERR_NOT_MOUNTED,             ///<�豸δ����
    SD_ERR_OVER_CAPACITY,           ///<������������Χ
    SD_ERR_UNKNOWN_CLASS,           ///<�豸δ֪ Class
    SD_ERR_DEV_BUSY,                ///<��������æ

    SD_ERR_READ = 0x10,             ///<������
    SD_ERR_READ_MULTIPLE_BLOCK,

    SD_ERR_WRITE = 0x20,            ///<д����
    SD_ERR_WRITE_MULTIPLE_BLOCK,

    SD_ERR_TIMEOUT = 0x30,          ///<���䳬ʱ
    SD_ERR_TIMEOUT_COMMAND,         ///<�����Ӧ��ʱ
    SD_ERR_TIMEOUT_DATA,            ///<���ݴ��䳬ʱ
    SD_ERR_TIMEOUT_READ,            ///<���䳬ʱ �����ݽ׶�
    SD_ERR_TIMEOUT_WRITE,           ///<���䳬ʱ д���ݽ׶�

    SD_ERR_OFFLINE = 0x40,          ///<�豸������
    SD_ERR_OFFLINE_READ,
    SD_ERR_OFFLINE_WRITE,

    SD_ERR_CRC16 = 0x50,
    SD_ERR_CRC16_COMMAND,
    SD_ERR_CRC16_DATA,
    SD_ERR_CRC16_READ,
    SD_ERR_CRC16_WRITE,

    SD_STOP_ERR = 0x60,            ///<��ͣ
    SD_STOP_ERR_READ,
    SD_STOP_ERR_WRITE,
    SD_IDENTIFICATION_RETRY_ERR,   ///<������Ч ���ƴ���׶�
};

/*SD����ģʽ����*/
typedef enum
{
    SD_4WIRE_MODE = 0,
    SD_1WIRE_MODE = BIT(0),
    SD_HI_SPEED = BIT(1),
}SD_NWRITE_SPEED_MODE;

/*SD��������ӦIO����*/
typedef enum
{
    SD0_IO_A = 1, //sd0������A����
    SD0_IO_B,     //sd0������B����

    SD1_IO_A,     //sd1������A����
    SD1_IO_B,     //sd1������B����
}SD_CONTROLLER_IO;

/*SD���߼�ⷽʽ*/
typedef enum
{
    SD_CMD_CHECK = 1, //SD��������
    SD_CLK_CHECK,     //SD��CLK���
    SD_IO_CHECK,      //SD��IO���
}SD_CHECK_WAY;

/*SD��д����ѡ��*/
typedef enum
{
    SD_READ_WRITE_WAIT = 1, //SD����д�ȴ����
    SD_READ_WRITE_NOT_WAIT, //SD����д���ȴ����
}SD_RW_WAY;

/*SD������״̬*/
typedef enum
{
    SD_CTLLER_NOT_BUSY = 0,
    SD_CTLLER_BUSY,
}SD_CTLLER_STATUS;

/*SD CMD����*/
typedef enum
{
    SD_CMD_UNLOCK = 0,
    SD_CMD_LOCK,
}SD_CMD_SET;

/**---------------------struct��----------------------**/
/**---------------------------------------------------**/
typedef struct _SD_NOT_CLEAR/*��sdģ�����������ﲻ�ᱻ��0�ı���*/
{
    u8  control_type;      //<����������(sd0����sd1)
    u8  control_io;        //<������IO����
    u8  online_check_way;  //<sd�����߼�ⷽʽ��cmd��clk
    u8  max_data_baud;     //<���ݴ����������
    u16 wDevTimeOutMax;    //<�豸������ʱ����
    u8  per_online_status; //<sd��ǰһ������״̬����
    u8  hc_mode;           //<sd������ģʽ�͸���ģʽ����
    u8  (*io_det_func)(void); //<io�ڼ�⺯��
}sSD_NOT_CLEAR;/*����4��bytes���룺��8��bytes*/

typedef struct _SD_HOST_VAR
{
    /*-----�豸��������-------*/
    u32 dwDevCapacity;          //<�豸����
    u32 dwDevCurLBA;            //<��ǰ�豸�����߼���ַ
    u8  bDevOperation;          //<�豸����״̬
    u8  bDevStatus;
    volatile u8 bDevBusy;       //<��������æ������volatile ��������ֹ��������while���Ż���
    u8  bDevError;              //<�豸��������

    /*-----�豸��������-------*/
    volatile u8  bDevOnline;
    u8  bClass;
    u8  bmFeat;                 //<SD ������ [0]SDMMC Hispeed [1]SDMMC 4 wires [2]SDMMC HC
    u8  bBusWidth;              //<SD Bus Width support

    u8  bWCRCError;
    u8  bRCRCError;
    u16 wDevRCA;

    u32 dect_init_flag;
    u8  bSDSpec;
    u8  align_reserve[3];  //align byte
}sSD_HOST_VAR;/*����4��bytes���룺��28��bytes*/

typedef struct _SD_CMD_DETECT
{
    u8  bCheckCnt;
    u8  bCMDStatus;
    u8  bOcState;               //<Command ���״̬��
    u8  bLockCMD;               //<Command ���
    u8  bCheckStep;
    volatile u8 bOnceCheck;
    u8  bBaudMax;           //<SD �����ٶ�����
    u8  bBaudMin;           //<SD �����ٶ�����
}sSD_CMD_DETECT;/*����4��bytes���룺��8��bytes*/

typedef struct _SD_VAR
{
    sSD_NOT_CLEAR    var_not_clr; //��sdģ�����������ﲻ�ᱻ��0�ı���
    sSD_HOST_VAR     host_var;    //��ͨsd����
    sSD_CMD_DETECT   cmd_detect;  //cmd������
    OS_SEM  sd_sem;     //SD�ź���
    u8  sd_ctller_flag; //IIC���ñ�־λ
    u8  rw_way;         //��д����ѡ��Ĭ��ѡ�񡰵ȴ���д�꺯����
}sSD_VAR __attribute__((aligned(4)));


typedef struct _SD_API_SET
{
    u8  controller_io;     //<������IO����
    u8  online_check_way;  //<sd�����߼�ⷽʽ��cmd��clk
    u8  max_data_baud;     //<���ݴ����������
    u8  hc_mode;           //<sd������ģʽ�͸���ģʽ����
    u8  (*io_det_func)(void); //<io�ڼ�⺯��
    u8  rw_way;               //��д����ѡ��Ĭ��ѡ�񡰵ȴ���д�꺯����
}sSD_API_SET __attribute__((aligned(4)));

typedef struct __SD_REG_VAR
{
    dev_io_t sd_io;
    OS_MUTEX sd_rwmutex;
}SD_REG_VAR;


/**---------------------�ⲿ����----------------------**/
/**---------------------------------------------------**/
extern const struct DEV_IO * dev_reg_sd0(void *parm);
extern const struct DEV_IO * dev_reg_sd1(void *parm);

#define SD0_MAGIC                'S'
#define SD0_SET_CLK              _IOW(SD0_MAGIC,1,SD_CLK)
#define DEV_GET_VAR_ADDR         _IOR(DEV_GENERAL_MAGIC,0xe3,u32)    //��ȡ�洢�豸�Ŀ�����
#define DEV_GET_CTLLER_STATUS    _IOR(DEV_GENERAL_MAGIC,0xe4,u32)    //��ȡSD��������æ״̬
#define DEV_SET_CMD_LOCK         _IOR(DEV_GENERAL_MAGIC,0xe5,u32)    //����CMD���Ƿ�����
#define DEV_SET_CTLLER_FLAG      _IOR(DEV_GENERAL_MAGIC,0xe6,u32)    //����CMD���Ƿ�����
#define DEV_MEM_FREE             _IOR(DEV_GENERAL_MAGIC,0xe7,u32)    //�ͷ�SD����ı����ռ�
#define DEV_GET_BUSY             _IOR(DEV_GENERAL_MAGIC,0xe8,u32)    //��ȡSD BUSY״̬
#define DEV_CLOSE_CONTROLLER     _IOR(DEV_GENERAL_MAGIC,0xe9,u32)    //suspend SD�����ر�SD������(����ռ��IO��)
#define DEV_RELEASE_CONTROLLER   _IOR(DEV_GENERAL_MAGIC,0xea,u32)    //���´�SD��������ռ����ӦIO��

#endif/*_MANGO_DEV_SD_H_*/

