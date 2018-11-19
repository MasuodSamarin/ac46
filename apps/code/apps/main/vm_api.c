#include "vm_api.h"
#include "dac_api.h"
#include "sys_cfg.h"
#define MAX_VM_CACHE 2
vm_hdl *vm_ptr = 0;
_VM_CACHE *vm_cache = 0;

extern void free_fun(void **ptr);
extern void *malloc_fun(void *ptr,u32 len,char *info);
/*----------------------------------------------------------------------------*/
/** @brief: 开辟的各个存储单元的长度
    @param: MAX_VM：开辟的存储单元数目
    @return:void
    @author:lj
    @note:  const u8 vm_index_len[MAX_VM]
*/
/*----------------------------------------------------------------------------*/
const u8 vm_index_len[MAX_VM] =
{
    VM_SYS_VOL_LEN,/* VM_SYS_VOL = 0,  */
    VM_SYS_EQ_LEN,/*VM_SYS_EQ         */
    VM_DEV0_BK_LEN,/* VM_DEV_BREAKPOINT0, */
    VM_DEV1_BK_LEN,/* VM_DEV_BREAKPOINT1, */
    VM_DEV2_BK_LEN,/* VM_DEV_BREAKPOINT2, */
    VM_DEV3_BK_LEN,/* VM_DEV_BREAKPOINT3, */
    VM_MUSIC_DEVICE_LEN,
 #ifdef support_vm_mode_bass_treb_echo	
    VM_MIC_ECHO_LEN, /*PC VOL*/
    VM_TREBL_LEN, /*PC VOL*/
    VM_BASS_LEN, /*PC VOL*/    
#endif    
    VM_PC_VOL_LEN, /*PC VOL*/
    VM_FM_INFO_LEN,
    /* MAX_VM,          */
};

/*----------------------------------------------------------------------------*/
/** @brief: 初始化VM，并打开所有存储单元
    @param: void
    @return:void
    @author:lj
    @note:  void vm_open_all(void
*/
/*----------------------------------------------------------------------------*/
void vm_open_all(void)
{
    u32 i;
    vm_ptr = 0;
    vm_cache = 0;
    vm_ptr = (vm_hdl *)malloc_fun(vm_ptr,sizeof(vm_hdl)*MAX_VM,0);
    vm_cache = (_VM_CACHE *)malloc_fun(vm_cache,sizeof(_VM_CACHE)*MAX_VM_CACHE,0);
    vm_cache[0].index = VM_SYS_VOL;
    vm_cache[1].index = VM_PC_VOL;

    for(i = 0;i < MAX_VM;i++)
    {
        if(vm_index_len[i])
        {
            vm_ptr[i] = vm_open(i,vm_index_len[i]);
        }

    }
//    vm_read_api(VM_SYS_VOL,&dac_var.cur_sys_vol_l);
}

/*----------------------------------------------------------------------------*/
/** @brief: 按照索引号写存储信息
    @param: index：存储单元索引
    @param: data_buf：需要存储的数据的指针
    @return:vm_err：操作结果
    @author:lj
    @note:  vm_err vm_write_api(u8 index ,const void *data_buf)
*/
/*----------------------------------------------------------------------------*/
vm_err vm_write_api(u8 index ,const void *data_buf)
{
    if (data_buf && vm_index_len[index])
    {
        return vm_write(vm_ptr[index],data_buf);
    }
    else
    {
        return VM_ARG_ERR;
    }

}
/*----------------------------------------------------------------------------*/
/** @brief: 按照索引号读存储信息
    @param: index：存储单元索引
    @param: data_buf：需要读取的数据的指针
    @return:vm_err：操作结果
    @author:lj
    @note:  vm_err vm_read_api(u8 index, void * data_buf)
*/
/*----------------------------------------------------------------------------*/
vm_err vm_read_api(u8 index, void * data_buf)
{
    if (data_buf && vm_index_len[index])
    {
        if(VM_READ_INDEX_INVAIL == vm_read(vm_ptr[index],data_buf))     //读取为空
        {
            memset(data_buf,0xff,vm_index_len[index]);
            return VM_READ_INDEX_INVAIL;
        }
        return VM_ERR_NONE;
    }
    else
    {
        return VM_ARG_ERR;
    }

}
/*----------------------------------------------------------------------------*/
/** @brief: 按照索引号缓存存储信息，但是不直接写入VM
    @param: index：存储单元索引
    @param: data_buf：需要读取的数据的指针
    @param: cnt ：在cnt个节拍之后，将数据存入VM
    @return:vm_err：操作结果
    @author:lj
    @note:  vm_err vm_cache_write(u8 index ,const void *data_buf,u8 cnt)
*/
/*----------------------------------------------------------------------------*/
vm_err vm_cache_write(u8 index ,const void *data_buf,u8 cnt)
{
    u32 i;
    for(i = 0;i < MAX_VM_CACHE;i++)
    {
        if(vm_cache[i].index == index)
        {
            if(-1 != vm_cache[i].cnt)
            {
                vm_cache[i].buff = (void *)malloc_fun(vm_cache[i].buff,vm_index_len[i],0);
                memcpy(vm_cache[i].buff,data_buf,vm_index_len[i]);
                vm_cache[i].cnt = cnt;
                return VM_ERR_NONE;
            }
            else
            {
                return VM_BUSY;
            }

        }
    }
    return VM_WRITE_OVERFLOW;//vm_write(vm_ptr[index],data_buf);
}
/*----------------------------------------------------------------------------*/
/** @brief: 扫描缓存，提交需要写入VM的数据
    @param: void
    @return:vm_err：操作结果
    @author:lj
    @note:  vm_err vm_cache_submit(void)
*/
/*----------------------------------------------------------------------------*/
vm_err vm_cache_submit(void)
{
    u32 i;

    for(i = 0;i < MAX_VM_CACHE;i++)
    {
        if(vm_cache[i].cnt)
        {
            vm_cache[i].cnt--;
            if(0 == vm_cache[i].cnt)
            {
                vm_err err;
                vm_cache[i].cnt = -1;
                //deg_puts("submit vm\n");
                err = vm_write_api(vm_cache[i].index,vm_cache[i].buff);
                if(VM_ERR_NONE != err)
                {
                    deg_puts("submit vm err\n");
                    vm_cache[i].cnt = 1;
                }
                else
                {
                    free_fun(&vm_cache[i].buff);
                    vm_cache[i].cnt = 0;
                    deg_puts("submit vm succ\n");
                }

            }
        }
    }
    return VM_ERR_NONE;
}


//void vm_init_api(void)
//{
//    vm_run_mode vm_mode;
//    if(((g_sys_cfg.flash_cfg.spi_run_mode & 3) == 0) || ((g_sys_cfg.flash_cfg.spi_run_mode & 3) == 1))
//    {
//        //spi2_parm = SPI_ODD_MODE;
//        vm_mode = WINBOND_READ_DATA_MODE;
//
//    }
//    else if((g_sys_cfg.flash_cfg.spi_run_mode & 3) == 2)
//    {
//        //spi2_parm = SPI_DUAL_MODE;
//        if(g_sys_cfg.flash_cfg.spi_run_mode & BIT(3))
//        {
//            vm_mode = WINBOND_FAST_READ_DUAL_OUTPUT_MODE;
//        }
//        else
//        {
//            if(g_sys_cfg.flash_cfg.spi_run_mode & BIT(2))
//            {
//                vm_mode = WINBOND_FAST_READ_DUAL_IO_CONTINUOUS_READ_MODE;
//            }
//            else
//            {
//                vm_mode = WINBOND_FAST_READ_DUAL_IO_NORMAL_READ_MODE;
//            }
//        }
//    }
//    else
//    {
//        if(g_sys_cfg.flash_cfg.spi_run_mode & BIT(3))
//        {
//            vm_mode = WINBOND_FAST_READ_QUAD_OUTPUT_MODE;
//        }
//        else
//        {
//            if(g_sys_cfg.flash_cfg.spi_run_mode & BIT(2))
//            {
//                vm_mode = WINBOND_FAST_READ_QUAD_IO_CONTINUOUS_READ_MODE;
//            }
//            else
//            {
//                vm_mode = WINBOND_FAST_READ_QUAD_IO_NORMAL_READ_MODE;
//            }
//        }
//    }
//    vm_init(g_sys_cfg.flash_cfg.flash_size - (68L*1024), g_sys_cfg.flash_cfg.flash_base,vm_mode ,0);
//}







