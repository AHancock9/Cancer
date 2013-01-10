#include "arch_context.h"
#include "built_in_func.h"
#include "low_level.h"
#include "arch_exception.h"
#include "thread.h"
static struct u_boot_func_sets *funcp = &uboot;
static struct cpu_context_save initContext;

void dump_cpu_context(void)
{
	struct cpu_context_save *cpu_reg_sets;
	asm volatile("cpsid i");
	cpu_reg_sets = __dump_cpu_context();
	funcp->printf("dump  regs:\n");
	funcp->printf("r0: 	 0x%08x\n",cpu_reg_sets->r0);
	funcp->printf("r1: 	 0x%08x\n",cpu_reg_sets->r1);
	funcp->printf("r2: 	 0x%08x\n",cpu_reg_sets->r2);
	funcp->printf("r3: 	 0x%08x\n",cpu_reg_sets->r3);
	funcp->printf("r4: 	 0x%08x\n",cpu_reg_sets->r4);
	funcp->printf("r5: 	 0x%08x\n",cpu_reg_sets->r5);
	funcp->printf("r6: 	 0x%08x\n",cpu_reg_sets->r6);
	funcp->printf("r7: 	 0x%08x\n",cpu_reg_sets->r7);
	funcp->printf("r8: 	 0x%08x\n",cpu_reg_sets->r8);
	funcp->printf("r9: 	 0x%08x\n",cpu_reg_sets->r9);
	funcp->printf("r10:  	 0x%08x\n",cpu_reg_sets->r10);
	funcp->printf("r11:  	 0x%08x\n",cpu_reg_sets->r11);
	funcp->printf("r12:  	 0x%08x\n",cpu_reg_sets->r12);
	funcp->printf("sp:      0x%08x\n",cpu_reg_sets->sp);
	funcp->printf("lr: 	 0x%08x\n",cpu_reg_sets->lr);
	funcp->printf("pc: 	 0x%08x\n",cpu_reg_sets->pc);
	funcp->printf("cpsr: 	 0x%08x\n",cpu_reg_sets->cpsr);
	asm volatile("cpsie i");
}

void dump_cpu_context_spec(struct cpu_context_save *cpu_reg_sets)
{
	funcp->printf("dump	 regs:\n");
	funcp->printf("r0: 	 0x%08x\n",cpu_reg_sets->r0);
	funcp->printf("r1: 	 0x%08x\n",cpu_reg_sets->r1);
	funcp->printf("r2: 	 0x%08x\n",cpu_reg_sets->r2);
	funcp->printf("r3: 	 0x%08x\n",cpu_reg_sets->r3);
	funcp->printf("r4: 	 0x%08x\n",cpu_reg_sets->r4);
	funcp->printf("r5: 	 0x%08x\n",cpu_reg_sets->r5);
	funcp->printf("r6: 	 0x%08x\n",cpu_reg_sets->r6);
	funcp->printf("r7: 	 0x%08x\n",cpu_reg_sets->r7);
	funcp->printf("r8: 	 0x%08x\n",cpu_reg_sets->r8);
	funcp->printf("r9: 	 0x%08x\n",cpu_reg_sets->r9);
	funcp->printf("r10:  	 0x%08x\n",cpu_reg_sets->r10);
	funcp->printf("r11:  	 0x%08x\n",cpu_reg_sets->r11);
	funcp->printf("r12:  	 0x%08x\n",cpu_reg_sets->r12);
	funcp->printf("sp:      0x%08x\n",cpu_reg_sets->sp);
	funcp->printf("lr: 	 0x%08x\n",cpu_reg_sets->lr);
	funcp->printf("pc: 	 0x%08x\n",cpu_reg_sets->pc);
	funcp->printf("cpsr: 	 0x%08x\n",cpu_reg_sets->cpsr);
}
void context_switch_force(struct cpu_context_save *to){
    context_switch(&initContext,to);
}

void context_switch(struct cpu_context_save *from, struct cpu_context_save *to)
{
	disable_interrupt();
	//funcp->printf("ready to context switch:\n");

	//unsigned long *sp = (unsigned long *)to->cpu_context.sp;
	//funcp->printf("lr -> 0x%08x\n",*(sp + 14));
	switch_to(from,to);
	//funcp->printf("after context switch...\n");
	enable_interrupt();
}

void init_context(struct cpu_context_save *regs,unsigned int stkBase)
{
	regs->cpsr = 0x600001d3;
	regs->lr   = (unsigned long)__ret_from_fork;
    regs->sp   = stkBase;
	__setup_stack(regs);
}


void context_exit(int error_code)
{
	while(1);
}

//ret_from_swi
void ret_from_fork(struct cpu_context_save *regs)
{

	struct ThreadObject *thread;
	struct ContextObject * entity;
	//funcp->printf("in ret_from_fork regs->%08x\n",regs);
    entity = container_of(regs, struct ContextObject,context);
    thread = container_of(entity,struct ThreadObject,tContext);
//	asm volatile("cpsie i");
	if (thread->threadEntry == NULL) {
		//funcp->printf("no func to run...hangs\n");
		while(1);
	}
	enable_interrupt();
	//funcp->printf("ret from fork\n");
	thread->threadEntry(thread->pThreadAgr);
	funcp->printf("back...\n");
	while(1);
}


