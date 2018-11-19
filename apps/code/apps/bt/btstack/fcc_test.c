
#include "config.h"
#include "fcc_test.h"
#include "clock.h"
#include "hwi.h"


//在这里要添加uart和电脑通信获取fcc配置

//usb口用作uart 使用uart1

//接收到数据回pc的状态
#define NACK  0xdd
#define ACK   0xcc

typedef struct _UartComm{
    u8 fcc_uart_sync[3]; //0xaa01bb
    u8 start;
    u16 len;
    u8 packet_type;    //DH135  2-DH135
	u8 channel;       //信道  0 - 78
	u8 data_type;      //PN9   单载
	u8 hopping_mode;       //跳频开关
	u8 tx_power;      //发射功率 0 - 15
	u8 sum;
	u8 end;
}__attribute__((packed)) UartComm;


UartComm fcc_uart_buf;

u8 writepos;//记录buf写的位置

void fcc_uart_write(char a)
{
    if(a == '\n'){
        UT1_BUF = '\r';
        while((UT1_CON & BIT(15)) == 0);
    }
    UT1_BUF = a;
    while((UT1_CON & BIT(15)) == 0);     //TX IDLE
}



void fcc_uart_isr()
{
    u8 * ptr;
    if((UT1_CON & BIT(14)))
    {
        //putchar('U');
        ptr = (u8 *)&fcc_uart_buf;
        ptr[writepos]=UT1_BUF;
        UT1_CON |= BIT(12);
        //接收 sync
        if(writepos == 0)
        {
            if(ptr[writepos]==0xaa)
            {
                writepos=1;
            }
        }
        else if(writepos == 1)
        {
            if(ptr[writepos]==0x01)
            {
                writepos=2;
            }
            else
            {
                writepos=0;
            }
        }
        else if(writepos == 2)
        {
            if(ptr[writepos]==0xbb)
            {
                fcc_uart_write(ACK); //接收 sync 0xaa01bb 正确
                putchar('S');
                writepos=3;
            }
            else
            {
                writepos=0;
            }
        }
        else  //接收有效数据
        {
            writepos++;
            if(writepos > sizeof(UartComm))
            {
                writepos = 0;
                set_test_fcc_info(ptr);
            }
        }

        if(writepos > sizeof(UartComm))
        {
            writepos = 0;
        }
    }
    DSP_CLR_ILAT = BIT(UART1_INIT);
}

extern void clear_ie(u32 index);

void fcc_uart_init()
{
    INTALL_HWI(UART1_INIT,fcc_uart_isr,5);
    writepos= 0;

    //usb 设为普通io
    clear_ie(USB_SOF);
    clear_ie(USB_CTRL);

    USB_IO_CON |= BIT(3); //DP & DM in en 该位设为1是设置DP DM为输入
    USB_IO_CON &=~BIT(2); //pd:out

    USB_IO_CON &=~(BIT(4) | BIT(5)); //DP & DM pull down disable
    USB_IO_CON &= ~(BIT(6) | BIT(7)); //DP & DM pull up disable

    USB_CON0 |= 0x0003;       //I/O mode

    //设置uart1使用usb io
    IOMC1 &=~0x0c;
    IOMC1 |=3<<2;

    UT1_BAUD = (UART_CLK/9600)/4 - 1;
    UT1_CON = BIT(14)|BIT(13) | BIT(12) | BIT(3)|BIT(0);       //rx_ie , CLR RX PND
}



void set_test_fcc_info(u8 *buf)
{
    u32 sum;
    u8 trx_mode_temp;
    UartComm *p;
    p=(UartComm *)buf;
    sum = p->packet_type+p->channel+p->data_type+
            p->hopping_mode+p->tx_power;

    if(sum==p->sum)
    {
        fcc_uart_write(ACK);
        //putchar('A');
        //put_u16hex(sizeof(UartComm));
        if(p->tx_power&BIT((7))) //接收模式  slave
        {
            trx_mode_temp = 1;
        }
        else    //发送模式   master
        {
            trx_mode_temp = 0;
        }
        __set_fcc_default_info(trx_mode_temp,
                               p->channel,
                               p->packet_type,
                               p->data_type,
                               p->tx_power,
                               p->hopping_mode);

//        printf("trx_mode :0x%x \n",trx_mode_temp);
//        printf("tx_fre :%d \n",p->tx_fre);
//        printf("packet_type :0x%x \n",p->packet_type);
//        printf("data_type :0x%x \n",p->data_type);
//        printf("tx_power :0x%x \n",p->tx_power);
//        printf("hopping_mode :0x%x \n",p->hopping_mode);

    }
    else
    {
        fcc_uart_write(NACK);
       // putchar('N');
    }

  //  put_buf(buf,sizeof(UartComm));

}

/*void __set_fcc_default_info(u8 trx_mode,u8 fre,u8 p_type,u8 d_type,u8 tx_power,hop_mode)
  是FCC认证默认初始化， 参1是1:rx  0:tx；参2是20:2402+20-2为中心频率  参3是 1-6:dh1 dh3 dh5  2dh1 2dh3 2dh5
  参4是//1：single carrier 0xff 0:伪随机  参5是发射功率  参6是跳频模式
*/
//fcc 默认初始化配置
void test_fcc_default_info()
{
   __set_fcc_default_info(0, 20, 2, 1, 6, 0);
}


