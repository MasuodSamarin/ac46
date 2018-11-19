#ifndef _VM_H_
#define _VM_H_

typedef enum vm_run_mode
{
    //1bit mode
    WINBOND_READ_DATA_MODE = (1<<0),
    WINBOND_FAST_READ_MODE = (1<<1),
    //2bit mode
    WINBOND_FAST_READ_DUAL_IO_NORMAL_READ_MODE  = (1<<2),
    WINBOND_FAST_READ_DUAL_IO_CONTINUOUS_READ_MODE = (1<<3),
    WINBOND_FAST_READ_DUAL_OUTPUT_MODE     = (1<<4),
    //4bit mode
    WINBOND_FAST_READ_QUAD_IO_NORMAL_READ_MODE   = (1<<5),
    WINBOND_FAST_READ_QUAD_IO_CONTINUOUS_READ_MODE = (1<<6),
    WINBOND_FAST_READ_QUAD_OUTPUT_MODE     = (1<<7),

}vm_run_mode;


typedef enum _vm_err
{
    VM_ERR_NONE = 0,
    VM_WRITE_OVERFLOW,
    VM_READ_INDEX_INVAIL,
    VM_READ_CRC_ERR,
    VM_BUSY,
    VM_ARG_ERR,
}vm_err;

typedef void *vm_hdl;

/*格式化VM_区域*/
extern void vm_eraser(void);

/*
每次上电初始化VM系统,
need_defrag_when_write_full: 当vm区域写满时是否需要整理碎片
*/
extern vm_err vm_init(u32 vm_addr, u32 spi_base, vm_run_mode mode, bool need_defrag_when_write_full);

/*
在 vm_write,vm_read 前必须先打开 指定index 获得句柄,
允许多次打开: vm_read/vm_write(vm_open(index,data_len),data_buf)
*/
extern vm_hdl vm_open(u8 index, u8 data_len);

/*不再需用调用vm_write,vm_read 时可以关闭句柄释放内存*/
extern vm_err vm_close(vm_hdl hdl);

extern vm_err vm_write(vm_hdl hdl, const void *data_buf);
extern vm_err vm_read(vm_hdl hdl, void * data_buf);

/*侦查 vm 区域 使用情况, 返回使用的百分比*/
extern int vm_status(void);

#endif  //_VM_H_



