#ifndef RUN_LOOP_H
#define RUN_LOOP_H


#include "typedef.h"
#include "list.h"




struct run_loop {
	struct list_head entry;
	void (*run)(struct run_loop *loop);
};

typedef struct run_loop data_source_t;

struct timeout{
	u32 jiffies;
	struct list_head entry;
	void (*fun)(struct timeout *);
};


typedef struct timeout  timer_source_t;





extern void __timer_register(struct list_head *head, struct timeout *time,
		 void (*fun)(struct timeout *time));

extern void __timer_set(struct list_head *head, struct timeout *time);


extern void __delete_region(struct list_head *head, void *begin, void *end);

extern void __timer_schedule_hi(struct list_head *head, unsigned long _jiffies);

extern void __timer_schedule(struct list_head *head, unsigned long _jiffies);


extern void __run_loop_register(struct list_head *head, struct run_loop *loop,
		void(*run)(struct run_loop *loop));

extern void __run_loop_schedule(struct list_head *head);

extern void __timer_delete(struct list_head *entry);
extern void __timer_delete_region(struct list_head *head, void *begin, void *end);

extern void __timer_delete(struct list_head *entry);

extern void __timer_delete_region(struct list_head *head, void *begin, void *end);

#endif

