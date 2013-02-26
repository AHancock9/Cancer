#include "low_level.h"


.global set_vbar	@(void)
.extern _start
set_vbar:

	ldr		r0,		=_start
	mcr		p15, 0, r0, c12, c0, 0
	mov		pc,		lr

.global read_vbar
read_vbar:

	mrc		p15, 0, r0, c12, c0, 0
	mov		pc,		lr

.global enable_irq
enable_irq:

	mrs		r0,		cpsr
	bic		r0,		r0,		#0x00000080
	msr		cpsr,	r0
	mov		pc,		lr

.global disable_irq
disable_irq:

	mrs		r0,		cpsr
	orr		r0,		r0,		#0x00000080
	msr		cpsr,	r0
	mov		pc,		lr

.global enable_fiq
enable_fiq:

	mrs		r0,		cpsr
	bic		r0,		r0,		#0x00000040
	msr		cpsr,	r0
	mov		pc,		lr

.global disable_fiq
disable_fiq:

	mrs		r0,		cpsr
	orr		r0,		r0,		#0x00000040
	msr		cpsr,	r0
	mov		pc,		lr

.global enable_interrupt
enable_interrupt:

	mrs		r0,		cpsr
	bic		r0,		r0,		#0x000000c0
	msr		cpsr,	r0
	mov		pc,		lr

.global disable_interrupt
disable_interrupt:

	mrs		r0,		cpsr
	orr		r0,		r0,		#0x000000c0
	msr		cpsr,	r0
	mov		pc,		lr

.global invalid_instruction_cache
invalid_instruction_cache:

	mov		r0,		#0x0
	mcr		p15, 0, r0, c7, c5, 0
	mov		pc,		lr

.global invalid_data_cache
invalid_data_cache:

	mov		r0,		#0x0
	mcr		p15, 0, r0, c7, c6, 0
	mov		pc,		lr


.global __dsb
__dsb:

	mov		r0,		#0x0
	mcr		p15, 0, r0, c7, c10, 4
	mov		pc,		lr

.global __dmb
__dmb:

	mov		r0,		#0x0
	mcr		p15, 0, r0, c7, c10, 5
	mov		pc,		lr

.global cur_context
.type cur_context, %object
cur_context:
	.fill 17, 4, 0x00000000
	.size	cur_context, . - cur_context

.global __dump_cpu_context
__dump_cpu_context:

	push	{r4}
	ldr		r4,		=cur_context
	stmia	r4!,	{r0-r3}
	add		r4,		r4,	#4
	stmia	r4!,	{r5-r12}
	/* save sp_usr */
	str		sp,		[r4],#4
	str		lr,		[r4],#4
	str		pc,		[r4],#4
	mrs		r0,		cpsr
	str		r0,		[r4]
	ldr		r0,		=cur_context
	mov		r1,		r0
	pop		{r4}
	add		r0,		r0,	#16
	str		r4,		[r0]
	mov		r0,		r1
	mov		pc,		lr





.global __ret_from_irq
__ret_from_irq:

    cpsid   i
	push	{r0-r12}
	cps		#18
	pop		{r0}
	cps		#19
	push	{r0, lr}
	/* save cpsr */
	mrs		r0,		cpsr
	push	{r0}

	bl		ret_from_irq

    cpsid  i
	/* reload cpsr */
	pop		{r0}
	msr		cpsr,	r0
	pop		{r0, lr}
	str		r0,		last_irq_lr
	pop		{r0-r12}
	cpsie  i
	ldr		pc,		last_irq_lr


/* ro points to "from", r1 points to "to" */
/*
--------------------------------------
		r0 -> from
		r1 -> to
					<-sp
56		lr
52		r0
48		r1
44		r2
40		r3
36		r4
32		cpsr
28		r5
24		r6
20		r7
16		r8
12		r9
8		r10
4		r11
		r12			<-sp
*/
.global switch_to
switch_to:
	push	{lr}
	push	{r0-r4}
	mrs		r4,		cpsr
	push	{r4-r12}
	add		r0,		r0,	#52
	str		sp,		[r0]

	str		r1,		__cur_context
	ldr		sp,		[r1,#52]
	pop		{r4-r12}
	msr		cpsr,	r4
	pop		{r0-r4}
	pop		{lr}
	mov		pc,		lr


.global __ret_from_fork
__ret_from_fork:
	ldr		r0,		__cur_context
	b		ret_from_fork	@r0 saves the pointer to cpu_context_save

.global __setup_stack
__setup_stack:
	push	{r0}
	ldr		r2,		[r0, #52]			@get app sp
	ldr		r1,		=__ret_from_fork	@get ret func
	sub		r2,		r2,	#4				@save app sp
	str		r1,		[r2]

	sub		r2,		r2, #4
	str		r0,		[r2]

	sub		r2,		r2,	#4
	str		r1,		[r2]

	mov		r0,		r2
	sub		r2,		r2, #4
	str		r0,		[r2]

	sub		r2,		r2,	#4
	str		r3,		[r2]

	sub		r2,		r2,	#4
	str		r4,		[r2]

	mrs		r1,		cpsr
	stmdb	r2!,	{r1,r5-r12}

	pop		{r0}
	str		r2,		[r0, #52]

	mov		pc,		lr

.global run_entity
run_entity:
	push	{lr}
	push	{r0-r4}
	mrs		r4,		cpsr
	push	{r4-r12}
	str		sp,	[r0, #52]

	str		r1,		__cur_context
	ldr		sp,		[r1, #52]
	ldr		r3,		[sp, #56]
	ldr		r2,		[sp, #32]
	msr		cpsr,	r2
	mov		pc,		r3					@jmp to __ret_from_fork

.global __cur_context
.type __cur_context, %object
__cur_context:
	.long

.global last_irq_lr
.type last_irq_lr, %object
last_irq_lr:
	.long

.global cpsr_from_irq
.type cpsr_from_irq, %object
cpsr_from_irq:
	.long



