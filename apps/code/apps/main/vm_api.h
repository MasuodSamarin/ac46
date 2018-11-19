#ifndef _VM_API_H_
#define _VM_API_H_

#include "includes.h"
#include "vm.h"
//_VM_H_

//

 #ifdef support_vm_mode_bass_treb_echo	
 enum
{
    VM_SYS_VOL = 0,
    VM_SYS_EQ,
     VM_DEV0_BREAKPOINT,
   VM_DEV1_BREAKPOINT,
    VM_DEV2_BREAKPOINT,
    VM_DEV3_BREAKPOINT,
    VM_MUSIC_DEVICE,
    VM_MIC_ECHO,
    VM_TREBL,
    VM_BASS,
    VM_PC_VOL,
    VM_FM_INFO,
    MAX_VM,
    SYSCFG_BTSTACK,
    SYSCFG_FILE_BREAKPOINT,
    SYSCFG_REMOTE_DB = 14,
    SYSCFG_REMOTE_DB_END = (14+20),
    SYSCFG_REMOTE_DB_HID = 35,
    SYSCFG_REMOTE_DB_HID_END = (35+20),
};

#define VM_MIC_ECHO_LEN          1
#define VM_TREBL_LEN          1
#define VM_BASS_LEN          1

#else
enum
{
    VM_SYS_VOL = 0,
    VM_SYS_EQ,
     VM_DEV0_BREAKPOINT,
   VM_DEV1_BREAKPOINT,
    VM_DEV2_BREAKPOINT,
    VM_DEV3_BREAKPOINT,
    VM_MUSIC_DEVICE,
    VM_PC_VOL,
    VM_FM_INFO,
    MAX_VM,
    SYSCFG_BTSTACK,
    SYSCFG_FILE_BREAKPOINT,
    SYSCFG_REMOTE_DB = 14,
    SYSCFG_REMOTE_DB_END = (14+20),
    SYSCFG_REMOTE_DB_HID = 35,
    SYSCFG_REMOTE_DB_HID_END = (35+20),
};
#endif

#define VM_FILE_BK_LEN          20

#define VM_SYS_VOL_LEN          1
#define VM_SYS_EQ_LEN           1

#define VM_DEV0_BK_LEN          VM_FILE_BK_LEN///(VM_FILE_BK_LEN+8)
#define VM_DEV1_BK_LEN          VM_FILE_BK_LEN///(VM_FILE_BK_LEN+8)
#define VM_DEV2_BK_LEN          VM_FILE_BK_LEN///(VM_FILE_BK_LEN+8)
#define VM_DEV3_BK_LEN          VM_FILE_BK_LEN///(VM_FILE_BK_LEN+8)
#define VM_MUSIC_DEVICE_LEN     1

#define VM_PC_VOL_LEN           1
#define VM_FM_INFO_LEN          32


typedef struct __VM_CACHE
{
    void *buff;
    u8 index;
    u8 cnt;
} _VM_CACHE;

void vm_open_all(void);
vm_err vm_write_api(u8 index ,const void *data_buf);
vm_err vm_read_api(u8 index, void * data_buf);
vm_err vm_cache_write(u8 index ,const void *data_buf,u8 cnt);
vm_err vm_cache_submit(void);
//void vm_init_api(void);
#endif
