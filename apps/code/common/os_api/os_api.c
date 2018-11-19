
#include "os_api.h"


/*----------------------------------------------------------------------------*/
/**@brief  创建一个任务
   @param  task：入口功能函数
   @param  p_arg：入口函数传入参数
   @param  prio：优先级
   @param  qsize:消息池大小，请采用双数
   @param  name：标识此任务的字符串
   @return
   @note   由于系统靠name区分不同任务，所以请保证name的唯一
*/
/*----------------------------------------------------------------------------*/
u8 os_task_create(void (*task)(void *p_arg), void *p_arg, u8 prio, QS qsize,s8 *name)
{
#if MEM_MALLOC == 1
    OS_TCB *task_tcb;
    void **start;
    task_tcb = malloc(sizeof(OS_TCB)+qsize*sizeof(void *));
    start = (void *)task_tcb + sizeof(OS_TCB);
#endif

    return OSTaskCreate(task,
                        task_tcb,
                        p_arg,
                        prio,
#if OS_TASKQ_EN > 0
                        start,
                        qsize
#endif
                        ,name
            );
}
/*----------------------------------------------------------------------------*/
/**@brief  发送消息通过先入先出方式，此发送方式会保证消息发送成功，如果消息池满，会等到消息池空就发送
   @param  name：线程的字符串表示，表示接受此消息的线程
   @param  argc：消息数量
   @param  ...：列举出各个消息
   @return  0发送成功
   @note
*/
/*----------------------------------------------------------------------------*/
extern u8  os_taskq_post_event (char *name, int argc, ...);
/*----------------------------------------------------------------------------*/
/**@brief  发送消息通过先入先出方式，不检查当前消息buffer是否满，不保证发送成功
   @param  name：线程的字符串表示，表示接受此消息的线程
   @param  argc：消息数量
   @param  ...：列举出各个消息
   @return  0发送成功
   @note
*/
/*----------------------------------------------------------------------------*/
extern u8 os_taskq_post_msg(char *name, int argc, ...);
/*----------------------------------------------------------------------------*/
/**@brief  获取消息
   @param  Timeout： 获取消息等待（默认请使用0）
   @param  Arge:  用于获取消息的buffer的大小
   @param  Argv：  用于获取消息的buffer的指针
   @return 0：没有错误  ；其它值错误状态
   @note
*/
/*----------------------------------------------------------------------------*/
extern u8 os_taskq_pend(u16 timeout, int argc, int *argv);
/*----------------------------------------------------------------------------*/
/**@brief  创建信号量
   @param  p_sem： 信号量指针
   @param  cnt：信号量初始值
   @return 0：没有错误  ；其它值错误状态
   @note
*/
/*----------------------------------------------------------------------------*/
extern u8 os_sem_create (OS_EVENT *p_sem,u16   cnt);
/*----------------------------------------------------------------------------*/
/**@brief  发送信号量
   @param  p_sem： 信号量指针
   @return 0：没有错误  ；其它值错误状态
   @note
*/
/*----------------------------------------------------------------------------*/
extern u8  os_sem_post (OS_EVENT  *p_sem);
/*----------------------------------------------------------------------------*/
/**@brief  等待信号量
   @param  p_sem： 信号量指针
   @param  timeout： 超时时间（0为不超时）
   @return 0：没有错误  ；其它值错误状态
   @note
*/
/*----------------------------------------------------------------------------*/
extern u8 os_sem_pend (OS_EVENT   *p_sem, u16   timeout);
/*----------------------------------------------------------------------------*/
/**@brief  设置信号量的值
   @param  p_sem： 信号量指针
   @param  cnt： 信号量的值
   @return 0：没有错误  ；其它值错误状态
   @note
*/
/*----------------------------------------------------------------------------*/
extern u8  os_sem_set (OS_EVENT   *p_sem, u16   cnt);


void OS_TASK_DEL_HOOK(OS_TCB *ptcb)
{
    vfree(ptcb->frame);
    free(ptcb);
}
