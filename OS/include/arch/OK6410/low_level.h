#ifndef __LOW_LEVEL_H__
#define __LOW_LEVEL_H__

#include "arch_context.h"

/* set vector base address to _start*/
unsigned long set_vbar(void);
unsigned long read_vbar(void);


void enable_irq(void);
void disable_irq(void);

void enable_fiq(void);
void disable_fiq(void);

void enable_interrupt(void);
void disable_interrupt(void);

void invalid_instruction_cache(void);
void invalid_data_cache(void);

void switch_to(struct cpu_context_save *from, struct cpu_context_save *to);
void *__dump_cpu_context(void);
void __save_init_context(struct cpu_context_save *cpu_regs);
void __ret_from_fork(void);
void __ret_from_irq(void);
void __setup_stack(struct cpu_context_save *regs);
void run_entity(struct cpu_context_save *from_regs, struct cpu_context_save *to_regs);


extern unsigned long _start;
extern unsigned long _vector_end;



#endif
