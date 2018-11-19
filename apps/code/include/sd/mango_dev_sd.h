#ifndef _MANGO_DEV_SD_H_
#define _MANGO_DEV_SD_H_

#include "typedef.h"
#include "device_driver.h"
#include "os_api.h"

/**---------------------enum类----------------------**/
/**---------------------------------------------------**/
/*sd调用失败列表*/
enum
{
    SD_SUCC = 0x0,
    SD_ERR_NOT_MOUNTED,             ///<设备未挂载
    SD_ERR_OVER_CAPACITY,           ///<读容量超出范围
    SD_ERR_UNKNOWN_CLASS,           ///<设备未知 Class
    SD_ERR_DEV_BUSY,                ///<控制器繁忙

    SD_ERR_READ = 0x10,             ///<读出错
    SD_ERR_READ_MULTIPLE_BLOCK,

    SD_ERR_WRITE = 0x20,            ///<写出错
    SD_ERR_WRITE_MULTIPLE_BLOCK,

    SD_ERR_TIMEOUT = 0x30,          ///<传输超时
    SD_ERR_TIMEOUT_COMMAND,         ///<命令回应超时
    SD_ERR_TIMEOUT_DATA,            ///<数据传输超时
    SD_ERR_TIMEOUT_READ,            ///<传输超时 读数据阶段
    SD_ERR_TIMEOUT_WRITE,           ///<传输超时 写数据阶段

    SD_ERR_OFFLINE = 0x40,          ///<设备不在线
    SD_ERR_OFFLINE_READ,
    SD_ERR_OFFLINE_WRITE,

    SD_ERR_CRC16 = 0x50,
    SD_ERR_CRC16_COMMAND,
    SD_ERR_CRC16_DATA,
    SD_ERR_CRC16_READ,
    SD_ERR_CRC16_WRITE,

    SD_STOP_ERR = 0x60,            ///<暂停
    SD_STOP_ERR_READ,
    SD_STOP_ERR_WRITE,
    SD_IDENTIFICATION_RETRY_ERR,   ///<发送无效 控制传输阶段
};

/*SD四线模式设置*/
typedef enum
{
    SD_4WIRE_MODE = 0,
    SD_1WIRE_MODE = BIT(0),
    SD_HI_SPEED = BIT(1),
}SD_NWRITE_SPEED_MODE;

/*SD控制器对应IO出口*/
typedef enum
{
    SD0_IO_A = 1, //sd0控制器A出口
    SD0_IO_B,     //sd0控制器B出口

    SD1_IO_A,     //sd1控制器A出口
    SD1_IO_B,     //sd1控制器B出口
}SD_CONTROLLER_IO;

/*SD在线检测方式*/
typedef enum
{
    SD_CMD_CHECK = 1, //SD卡命令检测
    SD_CLK_CHECK,     //SD卡CLK检测
    SD_IO_CHECK,      //SD卡IO检测
}SD_CHECK_WAY;

/*SD读写函数选择*/
typedef enum
{
    SD_READ_WRITE_WAIT = 1, //SD卡读写等待完成
    SD_READ_WRITE_NOT_WAIT, //SD卡读写不等待完成
}SD_RW_WAY;

/*SD控制器状态*/
typedef enum
{
    SD_CTLLER_NOT_BUSY = 0,
    SD_CTLLER_BUSY,
}SD_CTLLER_STATUS;

/*SD CMD设置*/
typedef enum
{
    SD_CMD_UNLOCK = 0,
    SD_CMD_LOCK,
}SD_CMD_SET;

/**---------------------struct类----------------------**/
/**---------------------------------------------------**/
typedef struct _SD_NOT_CLEAR/*在sd模块生存周期里不会被清0的变量*/
{
    u8  control_type;      //<控制器类型(sd0或者sd1)
    u8  control_io;        //<控制器IO出口
    u8  online_check_way;  //<sd卡在线检测方式：cmd和clk
    u8  max_data_baud;     //<数据传输最大波特率
    u16 wDevTimeOutMax;    //<设备操作超时上限
    u8  per_online_status; //<sd卡前一次在线状态变量
    u8  hc_mode;           //<sd卡四线模式和高速模式设置
    u8  (*io_det_func)(void); //<io口检测函数
}sSD_NOT_CLEAR;/*按照4个bytes对齐：共8个bytes*/

typedef struct _SD_HOST_VAR
{
    /*-----设备公共属性-------*/
    u32 dwDevCapacity;          //<设备容量
    u32 dwDevCurLBA;            //<当前设备操作逻辑地址
    u8  bDevOperation;          //<设备操作状态
    u8  bDevStatus;
    volatile u8 bDevBusy;       //<控制器繁忙（新增volatile 声明，防止编译器对while的优化）
    u8  bDevError;              //<设备操作错误

    /*-----设备特有属性-------*/
    volatile u8  bDevOnline;
    u8  bClass;
    u8  bmFeat;                 //<SD 卡特性 [0]SDMMC Hispeed [1]SDMMC 4 wires [2]SDMMC HC
    u8  bBusWidth;              //<SD Bus Width support

    u8  bWCRCError;
    u8  bRCRCError;
    u16 wDevRCA;

    u32 dect_init_flag;
    u8  bSDSpec;
    u8  align_reserve[3];  //align byte
}sSD_HOST_VAR;/*按照4个bytes对齐：共28个bytes*/

typedef struct _SD_CMD_DETECT
{
    u8  bCheckCnt;
    u8  bCMDStatus;
    u8  bOcState;               //<Command 检测状态机
    u8  bLockCMD;               //<Command 检测
    u8  bCheckStep;
    volatile u8 bOnceCheck;
    u8  bBaudMax;           //<SD 传输速度上限
    u8  bBaudMin;           //<SD 传输速度下限
}sSD_CMD_DETECT;/*按照4个bytes对齐：共8个bytes*/

typedef struct _SD_VAR
{
    sSD_NOT_CLEAR    var_not_clr; //在sd模块生存周期里不会被清0的变量
    sSD_HOST_VAR     host_var;    //普通sd变量
    sSD_CMD_DETECT   cmd_detect;  //cmd检测变量
    OS_SEM  sd_sem;     //SD信号量
    u8  sd_ctller_flag; //IIC复用标志位
    u8  rw_way;         //读写函数选择：默认选择“等待读写完函数”
}sSD_VAR __attribute__((aligned(4)));


typedef struct _SD_API_SET
{
    u8  controller_io;     //<控制器IO出口
    u8  online_check_way;  //<sd卡在线检测方式：cmd和clk
    u8  max_data_baud;     //<数据传输最大波特率
    u8  hc_mode;           //<sd卡四线模式和高速模式设置
    u8  (*io_det_func)(void); //<io口检测函数
    u8  rw_way;               //读写函数选择：默认选择“等待读写完函数”
}sSD_API_SET __attribute__((aligned(4)));

typedef struct __SD_REG_VAR
{
    dev_io_t sd_io;
    OS_MUTEX sd_rwmutex;
}SD_REG_VAR;


/**---------------------外部声明----------------------**/
/**---------------------------------------------------**/
extern const struct DEV_IO * dev_reg_sd0(void *parm);
extern const struct DEV_IO * dev_reg_sd1(void *parm);

#define SD0_MAGIC                'S'
#define SD0_SET_CLK              _IOW(SD0_MAGIC,1,SD_CLK)
#define DEV_GET_VAR_ADDR         _IOR(DEV_GENERAL_MAGIC,0xe3,u32)    //获取存储设备的块总数
#define DEV_GET_CTLLER_STATUS    _IOR(DEV_GENERAL_MAGIC,0xe4,u32)    //获取SD控制器繁忙状态
#define DEV_SET_CMD_LOCK         _IOR(DEV_GENERAL_MAGIC,0xe5,u32)    //设置CMD线是否锁定
#define DEV_SET_CTLLER_FLAG      _IOR(DEV_GENERAL_MAGIC,0xe6,u32)    //设置CMD线是否锁定
#define DEV_MEM_FREE             _IOR(DEV_GENERAL_MAGIC,0xe7,u32)    //释放SD申请的变量空间
#define DEV_GET_BUSY             _IOR(DEV_GENERAL_MAGIC,0xe8,u32)    //获取SD BUSY状态
#define DEV_CLOSE_CONTROLLER     _IOR(DEV_GENERAL_MAGIC,0xe9,u32)    //suspend SD卡并关闭SD控制器(不再占用IO口)
#define DEV_RELEASE_CONTROLLER   _IOR(DEV_GENERAL_MAGIC,0xea,u32)    //重新打开SD控制器和占据相应IO口

#endif/*_MANGO_DEV_SD_H_*/

