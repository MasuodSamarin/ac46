#include "config.h"
#include "ef_api.h"
#include "logic_dev_list.h"
#include "play_sel.h"

//EQ_TableCode：各个中心频点对应的增益值
#ifdef EQ_SEQUENCE_ADJ_ANYWAY
int const EQ_TableCode[7][5] =
#else
int const EQ_TableCode[6][5] =
#endif
{
    /*125Hz,500Hz,1KHz,4kHz,8KHzртио*/
	{0,0,0,0,0},      //zero                        //0
	{-4,8,-3,-1,7},   //ROCK                        //-2
	{7, 0,-7,0,6},    //POP                         //-3
	{0, 9, 0, 0, 2},  //CLASSIC                     //-3
	{-1,4,0,5,5},     //JAZZ                        //-3
	{-3,1,4,1,5 },    //country                     //-2	
#ifdef EQ_SEQUENCE_ADJ_ANYWAY
	{-3, 9, 0, 0, 0},	  //bass			//-2
#endif	
};

//EQ_GainTableCode：整个频带的增益值
//注：一般某个EQ的某个中心频点增益调太大,导致失真的话可以通过调小对应的整个频带的增益
#ifdef EQ_SEQUENCE_ADJ_ANYWAY
int const EQ_GainTableCode[7] ={0,-2,-3,-3,-3,-3,-3};
#else
int const EQ_GainTableCode[6] ={0,-2,-3,-3,-3,-3};
#endif

//生成的滤波器系数表
int const eq_filt_0[]=
{
    2085695, -1037202,5686,0,-1,
    2051076, -1003802,22386,0,-1,
    1908928, -879892,84341,0,-1,
    1294610, -489051,279762,0,-1,
    -204920, 733766,891171,0,-1
};

int const eq_filt_1[]=
{
    2074197, -1025950,11312,0,-1,
    2004339, -960860,43857,0,-1,
    1710960, -734277,157149,0,-1,
    476453, -91892,478341,0,-1,
    -888290,-316058,119086,-2,1
};

int const eq_filt_2[]=
{
    2051076, -1003802,22386,0,-1,
    1908928, -879892,84341,0,-1,
    1365668,-573448,237564,0,-1,
    -831964,-229527,409525,0,-1,
    0,0,0,0,0
};

/*----------------------------------------------------------------------------*/
/**@brief  eq滤波器系数表配置
   @param  filt_0、filt_1、filt_2滤波器系数表
   @return void
   @note   读配置成功，使用配置系数表
           读配置失败，使用默认系数表
*/
/*----------------------------------------------------------------------------*/
void eq_filter_config(unsigned int *eq_info_filt,unsigned int *filt_0,unsigned int *filt_1,unsigned int *filt_2)
{
    tbool ret;

#if EQ_FILTER_EN
    /*EQ_FILTER_EN = 1表示可以自行修改EQ各个滤波器的中心频率和带宽，=0表示使用默认配置*/
    ret = read_cfg_file((u8*)eq_info_filt,EQ_CFG_FILE,EQ_FILTER_CFG_LEN);
#else
    ret = 0;
#endif

    if(ret)
    {
        //puts("Use eq_filter config\n");
        *filt_0 =  (u32*)eq_info_filt+1;
        *filt_1 =  (u32*)eq_info_filt+1+25;
        *filt_2 =  (u32*)eq_info_filt+1+50;
    }
    else
    {
        //puts("\n\n*************Use eq_filter default**********\n\n");
        *filt_0 =  eq_filt_0;
        *filt_1 =  eq_filt_1;
        *filt_2 =  eq_filt_2;
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  配置文件读取函数
   @param  buff 存放配置文件的buff
           cfg_file_num 配置文件号
           cfg_len 配置文件的总长度
   @return ture配置文件读取成功  false配置文件读取失败
   @note   bool read_cfg_file(u8 *buff,u8 cfg_file_num,u16 cfg_len)
*/
/*----------------------------------------------------------------------------*/
bool read_cfg_file(u8 *buff,u8 cfg_file_num,u16 cfg_len)
{
    lg_dev_list * pnode;
    void *fs_hdl = NULL;  //文件系统句柄
    void *file_hdl = NULL;//文件句柄
    //puts("read_cfg_file\n");
    pnode = lg_dev_find('A');

    if(!syd_drive_open(&fs_hdl,pnode->cur_dev.lg_hdl->phydev_item,0))//打开文件系统
    {
        //puts("syd_drive_open err!\n");
        return FALSE;
    }
    if(!syd_get_file_byindex(fs_hdl,&file_hdl,cfg_file_num,0))
    {
        //puts("syd_get_file_byindex err!\n");
        //以下两部顺序不能变
        syd_file_close(fs_hdl,&file_hdl);//失败的情况下关闭文件
        syd_drive_close(&fs_hdl);//失败的情况下关闭文件系统
        return FALSE;
    }

    syd_read(file_hdl,buff,cfg_len);//读取文件
    //puts("cfg_info:");put_buf(buff,cfg_len);
    if(*(u16 *)buff == CRC16((u8*)buff+2,cfg_len-2))
    {
        //puts("cfg_file_crc_succ\n");
        //以下两部顺序不能变
        syd_file_close(fs_hdl,&file_hdl);//完成操作后，关闭文件
        syd_drive_close(&fs_hdl);  //完成操作后，关闭文件系统
        return true;
    }
    else
    {
        //puts("cfg_file_crc_err\n");
        //以下两部顺序不能变
        syd_file_close(fs_hdl,&file_hdl);//完成操作后，关闭文件
        syd_drive_close(&fs_hdl);  //完成操作后，关闭文件系统
        return false;
    }
}


