#ifndef GLOBAL_IRQ_H
#define GLOBAL_IRQ_H


#include "typedef.h"
#include "list.h"
#include "atomic.h"

struct global_irq_hdl{
	struct list_head notify_head;
	int disable;
};

struct global_irq_notify{
	struct list_head entry;
	void (*fun)(struct global_irq_notify *);
	atomic_t ref;
};

extern struct global_irq_hdl global_irq;

void global_irq_notify_schedule();

int global_interrupt_enable();

void global_irq_notify_set(struct global_irq_notify *notify);

void global_irq_notify_del(struct global_irq_notify *notity);

void global_irq_notify_register(struct global_irq_notify *notify,
		void (*fun)(struct global_irq_notify *));
#endif

