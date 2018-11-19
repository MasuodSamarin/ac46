/*--------------------------------------------------------------------------*/
/**@file    fm_api.c
   @brief   FM ģʽ���ܽӿں���
   @details
   @author  guowei
   @date    2014-9-15
   @note    DV10
*/
/*----------------------------------------------------------------------------*/
#include "fm_radio.h"
#include "fm_api.h"
#include "msg.h"
#include "dac.h"
#include "os_api.h"
#include "config.h"
#include "vm_api.h"
#include "fm_prompt.h"
#include "ladc.h"

#if FM_RADIO_EN

#define FM_PIONTS (32*2*2)
#define FM_CIR_BUF_SIZE FM_PIONTS*80L  ///>32points * 2byte *2channel * 10cnt

extern void free_fun(void **ptr);
extern void *malloc_fun(void *ptr,u32 len,char *info);

FM_RS_USE *fm_rs_objt;      ///>FM�����
cbuffer_t *fm_dac_cb;       ///>FMԴ��Ƶcbuf
s16 * fm_dac_buf;           ///>FMԴ��Ƶbuf [10][32*2];   ///>32point*2channel * 10
bool fm_init_flag = 0;
u8 *fm_rec_buf = NULL;               ///>FM¼������buf
//volatile LADC_CTL *fm_ladc;
/*----------------------------------------------------------------------------*/
/**@brief  FM�ж�ע��
   @param  NULL
   @return NULL
   @note   void fm_hw_init(void)
*/
/*----------------------------------------------------------------------------*/
void fm_hw_init(void)
{
    INTALL_HWI(FM_LOFC_INIT, fm_lofc_svr, 0);
    INTALL_HWI(FM_INIT, fm_svr, 0);
}

/*----------------------------------------------------------------------------*/
/**@brief  fm_auto_set
   @param  NULL
   @return NULL
   @note   void fm_auto_set(void)
*/
/*----------------------------------------------------------------------------*/
void fm_auto_set(void)
{
    u8 dat1, dat2;

//  printf("\n rssi:%d",  fmrx_get_rssi());
//  printf("\n plot:%d",  fmrx_get_pilot());

    dat1 = fmrx_get_rssi();
    dat2 = fmrx_get_pilot();
    fmrx_set_abw(dat1);

//    if(dat2 == 128)
//    {
//       fmrx_set_stereo(dat1);
//    }
//    else
    {
       fmrx_set_stereo(0);
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  FMԴ��Ƶcbuf����
   @param  buf����ַ��len������
   @return ����
   @note   u32 fm_cbuf_write(s16 * buf,u32 len)
*/
/*----------------------------------------------------------------------------*/
u32 fm_cbuf_write(s16 * buf,u32 len)
{
    if(fm_dac_cb == NULL)
    {
        return 0;
    }

    return cbuf_write(fm_dac_cb,(void *)buf,len);
}

/*----------------------------------------------------------------------------*/
/**@brief  FMԴ��Ƶcbuf����
   @param  buf����ַ��len������
   @return ����
   @note   u32 fm_cbuf_read(s16 * buf,u32 len)
*/
/*----------------------------------------------------------------------------*/
u8 * fm_cbuf_read_start(u32 * len)
{
    if(fm_dac_cb == NULL)
    {
        return 0;
    }

    return cbuf_read_alloc(fm_dac_cb,len);
}

/*----------------------------------------------------------------------------*/
/**@brief  FMԴ��Ƶcbuf����
   @param  buf����ַ��len������
   @return ����
   @note   u32 fm_cbuf_read(s16 * buf,u32 len)
*/
/*----------------------------------------------------------------------------*/
u8 fm_cbuf_read_over(u32 len)
{
    if(fm_dac_cb == NULL)
    {
        return 0;
    }

    cbuf_read_updata(fm_dac_cb,len);
    return 1;
}

/*----------------------------------------------------------------------------*/
/**@brief  FMԴ��Ƶcbuf����
   @param  NULL
   @return NULL
   @note   void fm_cbuf_init(void)
*/
/*----------------------------------------------------------------------------*/
void fm_cbuf_init(void)
{
    fm_dac_buf = (s16 *)malloc(FM_CIR_BUF_SIZE);
    if(!fm_dac_buf)
    {
        fm_puts("fm_cbuf_init_err-1\n");
        while(1);
    }

    fm_dac_cb = (cbuffer_t *)malloc(sizeof(cbuffer_t));
    if(!fm_dac_cb)
    {
        fm_puts("fm_cbuf_init_err-2\n");
        while(1);
    }

    cbuf_init(fm_dac_cb, (void *)fm_dac_buf, FM_CIR_BUF_SIZE);
    cbuf_clear(fm_dac_cb);
}

/*----------------------------------------------------------------------------*/
/**@brief  FMԴ��Ƶcbuf����
   @param  NULL
   @return NULL
   @note   void fm_cbuf_close(void)
*/
/*----------------------------------------------------------------------------*/
void fm_cbuf_close(void)
{
    free_fun((void **)&fm_dac_cb);
    free_fun((void **)&fm_dac_buf);
}

/*----------------------------------------------------------------------------*/
/**@brief  FM������������
   @param  buf��FM��Ƶ���ݵ�ַ
   @param  len��FM��Ƶ���ݳ���
   @return ��
   @note   ���������������
*/
/*----------------------------------------------------------------------------*/
#include "record.h"
#include "encode.h"

extern RECORD_OP_API * rec_fm_api;

u16 * fm_rec_buffer;
void fm_output_data(void *priv,char *buf, short len)            //�����len���ǰ�����Byte����ġ�
{
    u32 buf_len;
    u16 fram_size;


    static u16 * w_point;

    cbuf_write_dac((s16 *)buf, (u32)len);

#if REC_EN
    if(p_ladc)//fm_rec
    {
        fram_size = rec_fm_api->rec_ctl->enc_fram_size;
        if(fm_rec_buffer == NULL)
        {
            fm_rec_buffer = (u16 *)malloc(5*1024);//5K ����
            ASSERT(fm_rec_buffer);
            w_point = fm_rec_buffer;
        }

        memcpy(w_point, buf,len);
        w_point = w_point+(len/2);

        buf_len =(u32)(w_point-fm_rec_buffer);

        if(buf_len >= fram_size)//4608byte
        {
            rec_fm_api->rec_ctl->enc_ops_t->run(rec_fm_api->rec_ctl->buf_ptr, (void *)fm_rec_buffer);
            rec_fm_api->rec_ctl->file_info.enc_frame_cnt +=fram_size;
            buf_len-=fram_size;
            if(buf_len>0)
            {
                memcpy(fm_rec_buffer,(fm_rec_buffer+fram_size),buf_len*2);//4608byte
            }
            w_point = fm_rec_buffer+buf_len;
        }
    }
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief  FMƵ������
   @param  ��
   @return ��
   @note   ��Χ87500K��108000K,step�ֱ���25K
*/
/*----------------------------------------------------------------------------*/
tbool freq_set(u32 fre)
{
    u8 udat8;
    fre = fre*FM_STEP;
    udat8 = fmrx_set_freq(fre);

    //tmp_u32 = fm_pf_function(fre);
    fm_printf("fre = %u\n", fre);

    return udat8;
}

/*----------------------------------------------------------------------------*/
/**@brief  FM�������������
   @param  ��
   @return ��
   @note   fm_sr_convert_start
*/
/*----------------------------------------------------------------------------*/
void src_fun(long *fm_out)
{
    u8 i;
    static u8 cnt;

    s16 dac_buf_tmp[FM_PIONTS/2];

#ifdef FM_PROMPT_EN
    if(!fm_prompt_stopped)
        return;
#endif

    for(i=0; i<(FM_PIONTS/2); i++)
    {
        dac_buf_tmp[i] = (s16)fm_out[i];
    }

    if(!fm_cbuf_write(dac_buf_tmp, FM_PIONTS))
    {
        putbyte('l');//��֡
    }

    cnt++;
    if(cnt>=10)
    {
        cnt = 0;
        os_taskq_post_msg(FM_DAC_TASK_NAME, 1, MSG_SRC);
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  FM�����ֹͣ����
   @param  ��
   @return ��
   @note   fm_sr_convert_stop
*/
/*----------------------------------------------------------------------------*/
void fm_sr_convert_stop(void)
{
    free_fun((void **)&fm_rs_objt->tmpbuf);
    free_fun((void **)&fm_rs_objt);

    free_fun((void **)&fm_rec_buf);//rec_buf_free

    fm_cbuf_close();
}

/*----------------------------------------------------------------------------*/
/**@brief  FM�������������
   @param  ��
   @return ��
   @note   fm_sr_convert_start
*/
/*----------------------------------------------------------------------------*/
void fm_sr_convert_start(void)
{
    u32 tmpSIZE;
    FM_RS_IO fmIO;

    fm_rs_objt = (FM_RS_USE *)malloc(sizeof(FM_RS_USE));
    if(!fm_rs_objt)
    {
        fm_puts("FM_err-1\n");
        while(1);
    }

    fm_rs_objt->fm_testIO = &fmIO;

    fm_rs_objt->fm_testIO->priv =NULL;
    fm_rs_objt->fm_testIO->output_data=fm_output_data;
    fm_rs_objt->frc=get_fmRS_ops();

    tmpSIZE = fm_rs_objt->frc->need_buf();

    fm_rs_objt->tmpbuf = malloc(tmpSIZE);
    if(!fm_rs_objt->tmpbuf)
    {
        fm_puts("FM_err-2\n");
        while(1);
    }
    memset(fm_rs_objt->tmpbuf,0,tmpSIZE);

    fm_rs_objt->frc->open(fm_rs_objt->tmpbuf,fm_rs_objt->fm_testIO);
    fm_rs_objt->frc->set_config(fm_rs_objt->tmpbuf,FM_SR,DEST_32K,2);
}

/*----------------------------------------------------------------------------*/
/**@brief  FM������߳�
   @param  ��
   @return ��
   @note   void fm_src_task(void *p)
*/
/*----------------------------------------------------------------------------*/
static void fm_src_task(void *p)
{
    int msg[3];
    char *read_buf;
    u32 buf_len;
    u32 cnt;

    fm_cbuf_init();
    dac_set_samplerate(32000,1);
    fm_sr_convert_start();

    while(1)
    {
        os_taskq_pend(0, ARRAY_SIZE(msg), msg);

        switch(msg[0])
        {
        case SYS_EVENT_DEL_TASK:
            if (os_task_del_req_name(OS_TASK_SELF) == OS_TASK_DEL_REQ)
            {
                fm_sr_convert_stop();       //free fm_sr_convert source
                free_fun((void **)&fm_rec_buffer);
                os_task_del_res_name(OS_TASK_SELF);
            }
            break;

        case MSG_SRC:
            read_buf = (char *)fm_cbuf_read_start(&buf_len);
            cnt = (buf_len/(FM_PIONTS));
            while(cnt)
            {
                if(fm_mode_var->fm_mute)//unmute
                {
                    //fm_rs_objt->frc->run((u8 *)fm_rs_objt->tmpbuf, (char *)read_buf, 32);
                    memset(read_buf, 0x00, FM_PIONTS);
                }
                fm_rs_objt->frc->run((u8 *)fm_rs_objt->tmpbuf, (char *)read_buf, 32);
                read_buf+=FM_PIONTS;
                fm_cbuf_read_over(FM_PIONTS);
                cnt--;
            }
            break;

        default:
            break;
        }
    }
}
/*----------------------------------------------------------------------------*/
/**@brief  FM������ʼ������
   @param  ��
   @return ��
   @note   void fm_open(void)
*/
/*----------------------------------------------------------------------------*/
void fm_open(void)
{
    fm_mode_var = (FM_MODE_VAR *)malloc(sizeof(FM_MODE_VAR));
    if(!fm_mode_var)
    {
        fm_puts("fm_open_err-1\n");
        while(1);
    }
    memset(fm_mode_var, 0x00, sizeof(FM_MODE_VAR));

    fm_info = (FM_INFO *)malloc(sizeof(FM_INFO));
    if(!fm_info)
    {
        fm_puts("fm_open_err-2\n");
        while(1);
    }
    memset(fm_info, 0x00, sizeof(FM_INFO));
}

/*----------------------------------------------------------------------------*/
/**@brief   FMģ���ʼ���ӿں���
   @param
   @return   ��ʼ���ɹ�����TRUE
   @note   tbool init_fm_rev(void)
*/
/*----------------------------------------------------------------------------*/
tbool init_fm_rev(void)
{
    /*init fm src task*/
    os_task_create(fm_src_task,
                   (void*)0,
                   TaskFMsrcPrio,
                   30
#if OS_TIME_SLICE_EN > 0
                   ,1
#endif
                   ,FM_DAC_TASK_NAME);
    set_fm_osc(OSC_Hz);
	
#if 0
   @param   nrs����Χ:2-7
   @param   nc1����Χ:50-100
   @param   nc2����Χ:30-80
   @param   ncc����Χ:20-60
            ����4������Ϊ��̨�źŷ�ֵ���ѵ���̨��ֵ������趨��nrsֵ��
            ����ͬʱ��С��nc1��nc2��ncc��3��ֵ��Ϊ��̨������Ϊ��̨

#endif

#ifdef support_fm_scan_set_mod1 	
    set_fm_scan(3,90,70,50,0x16);//��̨�����ο���fmrx_driver.h
#elif defined support_fm_scan_set_mod2
    set_fm_scan(4,60,60,40,0x16);//��̨�����ο���fmrx_driver.h
#else
    set_fm_scan(4,80,60,40,0x16);//��̨�����ο���fmrx_driver.h
#endif   

    set_fm_printf(0);
    fmrx_initial(1);

    fm_info_init();//read from vm

    /*---------FM MAIN UI--------------*/
    SET_UI_MAIN(MENU_FM_MAIN);
    UI_menu(MENU_FM_MAIN);

    return TRUE;
}

/*----------------------------------------------------------------------------*/
/**@brief  FMģ��رպ���
   @param  ��
   @return ��
   @note   fm_power_off(void)
*/
/*----------------------------------------------------------------------------*/
void fm_rev_powerdown(void)
{
    fmrx_initial(0);

    free_fun((void **)&fm_mode_var);
    free_fun((void **)&fm_info);
}

/*----------------------------------------------------------------------------*/
/**@brief   ��ȡһ��byte���м���λ����һ
   @param   byte ��������ȥ��byte
   @return  ����һλ��
   @note    tu8 get_total_mem_channel(void)
*/
/*----------------------------------------------------------------------------*/
tu8 my_get_one_count(u8 byte)
{
    u8  i,b=0;
    for (i = 0; i < 8; i++)
    {
        if (byte & BIT(7))
        {
            b++;
        }
        byte <<= 1;                   //��������һλ,������һ������
    }
    return b;
}
/*----------------------------------------------------------------------------*/
/**@brief ��ȡȫ����¼��Ƶ��
   @param 	��
   @return  Ƶ������
   @note  tu8 get_total_mem_channel(void)
*/
/*----------------------------------------------------------------------------*/
tu8 get_total_mem_channel(void)
{
    u8 i,j;
    u8 total;
    total = 0;
    for (i = 0; i < MEM_FM_LEN; i++)
    {
        j = fm_info->dat[FM_CHANNL + i];
        total += my_get_one_count(j);
    }
    if (total > MAX_CHANNL)
        total = MAX_CHANNL;

    return total;
}
/*----------------------------------------------------------------------------*/
/**@brief ����Ƶ��ƫ������ȡƵ��
   @param 	channel��Ƶ��
   @return  Ƶ��
   @note  tu8 get_channel_via_fre(u8 fre)

*/
/*----------------------------------------------------------------------------*/
tu8 get_channel_via_fre(u8 fre)
{
    u8 i,j, k;
    u8 total;
    total = 0;
    for (i = 0; i < MEM_FM_LEN; i++)
    {
        j = fm_info->dat[FM_CHANNL + i];
        for (k = 0; k < 8; k++)
        {
            if (j & (BIT(k)))
            {
                total++;
                if (fre == (i * 8 + k))
                {
                    return total;		 //return fre index
                }
            }
        }
    }
    return fm_mode_var->wFreChannel;						    //find none
}
/*----------------------------------------------------------------------------*/
/**@brief ͨ��Ƶ����ȡƵ��
   @param 	channel��Ƶ��
   @return  ��Ч��Ƶ��ƫ����
   @note  u8 get_fre_via_channle(u8 channel)
*/
/*----------------------------------------------------------------------------*/
tu8 get_fre_via_channle(u8 channel)
{
    u8 i,j, k;
    u8 total;

    total = 0;
    for (i = 0; i < MEM_FM_LEN; i++)
    {
        j = fm_info->dat[FM_CHANNL + i];
        for (k = 0; k < 8; k++)
        {
            if (j & (BIT(k)))
            {
                total++;
                if (total == channel)
                {
                    return i * 8 + k;		 //fre = MIN_FRE + return val
                }
            }
        }

    }
    return 0xff;							//find none
}

//void fm_check_channel(void)
//{
//    fm_mode_var->wTotalChannel = get_total_mem_channel();
//    if (fm_mode_var->wTotalChannel)
//    {
//        //put_u8hex0(fm_mode_var->wFreChannel);
//        //put_u8hex0(fm_mode_var->wTotalChannel);
//        if( fm_mode_var->wFreChannel>fm_mode_var->wTotalChannel)
//            fm_mode_var->wFreChannel = fm_mode_var->wTotalChannel;
//        else if( fm_mode_var->wFreChannel==0)
//            fm_mode_var->wFreChannel = 1;
//        fm_mode_var->wFreq = get_fre_via_channle(fm_mode_var->wFreChannel) + MIN_FRE;
//    }
//    else
//    {
//        fm_mode_var->wFreChannel = 0;
//        fm_mode_var->wFreq = 875;
//    }
//    set_fre(FM_CUR_FRE);
//    fm_info->dat[FM_FRE]=fm_mode_var->wFreq - MIN_FRE;
//    fm_info->dat[FM_CHAN]=fm_mode_var->wFreChannel;
////    fm_save_info();
//    //ui_menu(MENU_FM_FIND_STATION);
//}

/*----------------------------------------------------------------------------*/
/**@brief ɾ��Ƶ��
   @param 	��
   @return  ��
   @note  void delete_fm_point(u8 fre)
*/
/*----------------------------------------------------------------------------*/
void delete_fm_point(u8 fre)
{
    u8 i,j,k;
    i = fre / 8;
    k = fre % 8;
    j=fm_info->dat[FM_CHANNL + i] & (~BIT(k));
    fm_info->dat[FM_CHANNL + i]=j;
    fm_save_info();
}
/*----------------------------------------------------------------------------*/
/**@brief ����Ƶ��
   @param 	��
   @return  ��
   @note  u8 ch_save(void)
*/
/*----------------------------------------------------------------------------*/
void ch_save(void)
{
    save_fm_point(fm_mode_var->wFreq - MIN_FRE);
    fm_mode_var->wFreChannel = get_channel_via_fre(fm_mode_var->wFreq - MIN_FRE);
    fm_mode_var->wTotalChannel = get_total_mem_channel();
}

/*----------------------------------------------------------------------------*/
/**@brief   FMģ��Mute����
   @param   flag��Muteʹ��λ 0��������  1��������
   @return  ��
   @note    void fm_module_mute(u8 flag)
*/
/*----------------------------------------------------------------------------*/
void fm_module_mute(u8 flag)
{
    //fmrx_set_amute(flag);
    //(* fm_mute[fm_mode_var->bAddr])(flag);
    fm_mode_var->fm_mute = flag;
}

/*----------------------------------------------------------------------------*/
/**@brief   ����һ��FMƵ��Ľӿں���
   @param   mode = 0: ʹ��frequency�е�ֵ��= 1:Ƶ���1�� = 2:Ƶ���1
   @return  1����̨��0����̨
   @note    tbool set_fre(u8 mode)
*/
/*----------------------------------------------------------------------------*/
tbool set_fre(u8 mode)
{
    fm_module_mute(1);

    if (mode == FM_FRE_INC)
    {
        fm_mode_var->wFreq++;
    }
    else if (mode == FM_FRE_DEC)
    {
        fm_mode_var->wFreq--;
    }
    if (fm_mode_var->wFreq > MAX_FRE)
        fm_mode_var->wFreq = MIN_FRE;
    if (fm_mode_var->wFreq < MIN_FRE)
        fm_mode_var->wFreq = MAX_FRE;

    //fm_printf("fm_mode_var->wFreq = %d\n",fm_mode_var->wFreq);
    return freq_set(fm_mode_var->wFreq);
}

/*----------------------------------------------------------------------------*/
/**@brief ��vm�������Ƶ����Ϣ
   @param 	��
   @return  ��
   @note  void clear_all_fm_point(void)
*/
/*----------------------------------------------------------------------------*/
void clear_all_fm_point(void)
{
    u8 i;

    for (i = FM_CHANNL; i <= (FM_CHANNL + MEM_FM_LEN); i++)
    {
        fm_info->dat[i]=0x00;
    }
    fm_save_info();
}
/*----------------------------------------------------------------------------*/
/**@brief ����Ƶ��ƫ�������浽��Ӧ��Ƶ��λ������vm
   @param 	fre��Ƶ��ƫ����
   @return  ��
   @note  void save_fm_point(u8 fre)
*/
/*----------------------------------------------------------------------------*/
void save_fm_point(u8 fre)
{
    u8 i,j, k;
    i = fre / 8;
    k = fre % 8;
    fm_read_info();
    j=fm_info->dat[FM_CHANNL + i]| BIT(k);
    fm_info->dat[FM_CHANNL+i]=j;
    fm_save_info();
}

/*----------------------------------------------------------------------------*/
/**@brief    ȫƵ������
   @param    mode: 0ȫƵ��, 1:��һ����ЧƵ�㣬 2:��һ����ЧƵ��
   @return   0:δ�ҵ�Ƶ�� 1:������� 2:�˳�FMģʽ
   @note     tbool fm_scan(u8 mode)
*/
/*----------------------------------------------------------------------------*/
tbool fm_scan(u8 mode)
{
    bool tres;

    if (mode == FM_SCAN_PREV)
        tres = set_fre(FM_FRE_DEC);
    else if((mode == FM_SCAN_NEXT)||(mode == FM_SCAN_ALL))
        tres = set_fre(FM_FRE_INC);
    else    //��̨״̬����
        return FALSE;

    fm_mode_var->wFreChannel = 0;

    //ȫƵ����Ƶ����ʾ
    SET_UI_LOCK(MENU_FM_DISP_FRE);
    UI_menu(MENU_FM_DISP_FRE);

    if (tres)						//�ҵ�һ��̨
    {
        if(fm_mode_var->fm_mute)
        {
            fm_module_mute(0);
        }
        fm_info->dat[FM_FRE] = fm_mode_var->wFreq - MIN_FRE;
        //fm_save_info();
        save_fm_point(fm_mode_var->wFreq - MIN_FRE);
        fm_mode_var->wFreChannel = get_channel_via_fre(fm_mode_var->wFreq - MIN_FRE);
        fm_mode_var->wTotalChannel = get_total_mem_channel();

        //��ʾ�ѵ���Ƶ��
        SET_UI_LOCK(MENU_FM_FIND_STATION);
        UI_menu(MENU_FM_FIND_STATION);
        return TRUE;
    }

    return FALSE;
}

/*----------------------------------------------------------------------------*/
/**@brief  FM ģʽ��Ϣ��ʼ��
   @param  ��
   @return ��
   @note   void fm_info_init(void)
*/
/*----------------------------------------------------------------------------*/
void fm_info_init(void)
{
    fm_mode_var->scan_mode = FM_ACTIVE;

    fm_read_info();

    fm_mode_var->wFreq = fm_info->dat[FM_FRE];
    if(fm_mode_var->wFreq > (MAX_FRE - MIN_FRE))
    {
        fm_mode_var->wFreq = MIN_FRE;
    }
    else
    {
        fm_mode_var->wFreq += MIN_FRE;
    }

    fm_mode_var->wTotalChannel = get_total_mem_channel();
    if(!fm_mode_var->wTotalChannel)
    {
        fm_mode_var->wTotalChannel = 1;
    }

    fm_mode_var->wFreChannel = fm_info->dat[FM_CHAN];
    if(fm_mode_var->wFreChannel > MAX_CHANNL)					//̨��Ϊ1;��̨��Ϊ1
    {
        fm_mode_var->wFreChannel = 1;
        fm_mode_var->wTotalChannel = 1;
    }
    else if(!fm_mode_var->wFreChannel)
    {
        fm_mode_var->wFreChannel = 1;
    }

    fm_mode_var->wFreChannel = get_channel_via_fre(fm_mode_var->wFreq - MIN_FRE);
    if(0xff == fm_mode_var->wFreChannel)
    {
        fm_mode_var->wFreChannel = 1;
    }

    set_fre(FM_CUR_FRE);
    fm_module_mute(0);
    fm_mode_var->scan_mode = FM_SCAN_STOP;

    /*---------FM MAIN UI--------------*/
    //set_ui_main(MENU_FM_MAIN);
    //ui_menu_api(MENU_FM_MAIN);
}

/*----------------------------------------------------------------------------*/
/**@brief  ������Ϣ��fm_buf
   @param  ��
   @return ��
   @note  void fm_save_info()
*/
/*----------------------------------------------------------------------------*/
void fm_save_info(void)
{
    vm_write_api(VM_FM_INFO, fm_info);
}

/*----------------------------------------------------------------------------*/
/**@brief  ��vm��ȡ��Ϣ
   @param  ��
   @return ��
   @note  void fm_read_info()
*/
/*----------------------------------------------------------------------------*/
void fm_read_info(void)
{
    vm_read_api(VM_FM_INFO, fm_info);
}

#endif
