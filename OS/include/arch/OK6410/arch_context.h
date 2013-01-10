#ifndef	__CONTEXT_ENTITY__
#define __CONTEXT_ENTITY__

struct cpu_context_save {
	volatile unsigned long r0;	//#0
	volatile unsigned long r1;	//#4
	volatile unsigned long r2;	//#8
	volatile unsigned long r3;	//#12
	volatile unsigned long r4;	//#16
	volatile unsigned long r5;	//#20
	volatile unsigned long r6;	//#24
	volatile unsigned long r7;	//#28
	volatile unsigned long r8;	//#32
	volatile unsigned long r9;	//#36
	/* r10 by apcs stack limit */
	volatile unsigned long r10;	//#40
	/* r11 by apcs frame pointer */
	volatile unsigned long r11;	//#44
	/* r12 by apcs scratch reg */
	volatile unsigned long r12;	//#48
	volatile unsigned long sp;	//#52
	volatile unsigned long lr;	//#56
	volatile unsigned long pc;	//#60
	volatile unsigned long cpsr;	//#64
};


void dump_cpu_context(void);

void context_switch(struct cpu_context_save *from, struct cpu_context_save *to);
void dump_cpu_context_spec(struct cpu_context_save*);
void ret_from_fork(struct cpu_context_save *entity);
void init_context(struct cpu_context_save *entity,unsigned int stkBase);
void context_exit(int error_code);





#endif
