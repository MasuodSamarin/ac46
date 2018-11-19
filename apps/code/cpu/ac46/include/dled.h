#ifndef _DLED_H_
#define _DLED_H_

#include "typedef.h"





enum
{
    POWER_ONING=1,           //�������̵�ƽ��������5��
    DISCONNECT_OK,           //�����Զ����Ӳ��ɹ����̵ƿ���2sһ��
    POWER_ON_OK,            //��������5s�����������̵ƺͺ�ƽ�����
    CONNECT_OK,             //���ӳɹ����̵�����8sһ��
    POWER_OFFING,           //�ػ�����Ƴ�����3s
};


void dled_init(void);
void set_dled_mode(u8 mode);
void dled_control(void);


#endif

