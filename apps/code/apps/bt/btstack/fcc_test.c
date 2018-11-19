
#include "config.h"
#include "fcc_test.h"
#include "clock.h"
#include "hwi.h"


//������Ҫ���uart�͵���ͨ�Ż�ȡfcc����

//usb������uart ʹ��uart1

//���յ����ݻ�pc��״̬
#define NACK  0xdd
#define ACK   0xcc

typedef struct _UartComm{
    u8 fcc_uart_sync[3]; //0xaa01bb
    u8 start;
    u16 len;
    u8 packet_type;    //DH135  2-DH135
	u8 channel;       //�ŵ�  0 - 78
	u8 data_type;      //PN9   ����
	u8 hopping_mode;       //��Ƶ����
	u8 tx_power;      //���书�� 0 - 15
	u8 sum;
	u8 end;
}__attribute__((packed)) UartComm;


UartComm fcc_uart_buf;

u8 writepos;//��¼bufд��λ��

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
        //���� sync
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
                fcc_uart_write(ACK); //���� sync 0xaa01bb ��ȷ
                putchar('S');
                writepos=3;
            }
            else
            {
                writepos=0;
            }
        }
        else  //������Ч����
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

    //usb ��Ϊ��ͨio
    clear_ie(USB_SOF);
    clear_ie(USB_CTRL);

    USB_IO_CON |= BIT(3); //DP & DM in en ��λ��Ϊ1������DP DMΪ����
    USB_IO_CON &=~BIT(2); //pd:out

    USB_IO_CON &=~(BIT(4) | BIT(5)); //DP & DM pull down disable
    USB_IO_CON &= ~(BIT(6) | BIT(7)); //DP & DM pull up disable

    USB_CON0 |= 0x0003;       //I/O mode

    //����uart1ʹ��usb io
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
        if(p->tx_power&BIT((7))) //����ģʽ  slave
        {
            trx_mode_temp = 1;
        }
        else    //����ģʽ   master
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
  ��FCC��֤Ĭ�ϳ�ʼ���� ��1��1:rx  0:tx����2��20:2402+20-2Ϊ����Ƶ��  ��3�� 1-6:dh1 dh3 dh5  2dh1 2dh3 2dh5
  ��4��//1��single carrier 0xff 0:α���  ��5�Ƿ��书��  ��6����Ƶģʽ
*/
//fcc Ĭ�ϳ�ʼ������
void test_fcc_default_info()
{
   __set_fcc_default_info(0, 20, 2, 1, 6, 0);
}


