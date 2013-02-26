#include "exception.h"

.extern main
.global _start
    /* interrupt vector all 16bytes*/
_start:
	b		reset
	ldr		pc,		_undefined_instruction
	ldr		pc,		_software_interrupt
	ldr		pc,		_prefetch_abort
	ldr		pc,		_data_abort
	ldr		pc,		_not_used
	ldr		pc,		_irq
	ldr		pc,		_fiq

_undefined_instruction:
	.word	undefined_instruction
_software_interrupt:
	.word	software_interrupt
_prefetch_abort:
	.word	prefetch_abort
_data_abort:
	.word	data_abort
_not_used:
	.word	not_used
_irq:
	.word	irq
_fiq:
	.word	fiq
_pad:
	.word	0x12345678

.global _vector_end
_vector_end:
	.balignl 16, 0xdeadbeef

reset:

	ldr		r0, 	=0x70000000
	orr		r0,		r0,		#0x13
	mcr		p15, 0, r0, c15, c2, 4

	/* stop watchdog */
	ldr		r0,		=0x7e004000
	mov		r1,		#0
	str		r1,		[r0]


	/* set vectors to 0x00000000 */
	mrc		p15, 0, r0, c1, c0, 0
	bic		r0,		r0,		#0x00002000
	ldr		r1,		=0x00001020	@enable Instruction Cache
	orr     r0,     r0, r1
	mcr		p15, 0, r0, c1, c0, 0

	/* undef sp starts from 56003000 */
	mrs		r1,		cpsr
	bic		r1,		r1,		#0x1f
	orr		r1,		r1,		#0xdb
	msr		cpsr,	r1

	ldr		sp,		=0x56003000
	/* swi not use */

	/* abort sp starts from 56006000*/
	mrs		r1,		cpsr
	bic		r1,		r1,		#0x1f
	orr		r1,		r1,		#0xd7
	msr		cpsr,	r1

	ldr		sp,		=0x56006000
	/* irq sp starts from 56500000 */
	mrs		r1,		cpsr
	bic		r1,		r1,		#0x1f
	orr		r1,		r1,		#0xd2
	msr		cpsr,	r1

	ldr		sp,		=0x56500000
	/* fiq sp starts from 57000000*/
	mrs		r1,		cpsr
	bic		r1,		r1,		#0x1f
	orr		r1,		r1,		#0xd1
	msr		cpsr,	r1

	ldr		sp,		=0x57000000
	/* SVC starts from 56000000*/
	mrs		r1,		cpsr
	bic		r1,		r1,		#0x1f
	orr		r1,		r1,		#0xd3
	msr		cpsr,	r1

	ldr		sp,		=0x56000000

clean_bss:

	ldr		r0,		=bss_start
	ldr		r1,		=bss_end
	mov		r3,		#0x0
	cmp		r1,		r0
	beq		done

clean_loop:

	str		r3,		[r0],#4
	cmp		r0,		r1
	bne		clean_loop

done:
	bl 		main

halt:
	b		halt




.extern unexception_abort
.align 5
undefined_instruction:
	bl 			debug_undefined
	mov			r1,		#0x0
	mov			r2,		lr
	bl			unexception_abort

.extern swi
.align 5
software_interrupt:
	bl	swi

.align 5
prefetch_abort:
	sub			lr,		lr,	#4
	push 		{lr}
	bl 			debug_abort
	mov 		r1,		#0x1
	pop			{lr}
	mov			r2,		lr
	bl			unexception_abort

.align 5
data_abort:
	sub			lr,		lr,	#8
	push		{lr}
	bl 			debug_abort
	mov			r1,		#0x2
	pop			{lr}
	mov			r2,		lr
	bl			unexception_abort

.align 5
not_used:
	b	not_used

.align 5
.extern last_irq_lr
.extern irq_exception
.extern find_vic_num
.extern debug_check
.extern __ret_from_irq
irq:
	sub 	lr, 	lr, #4
	push	{lr}

	push	{r0-r12}
	/* when irq returns, it will back to __ret_from_irq */
	ldr		lr,		=__ret_from_irq
	pop		{r0-r12}

	/* save lr_irq  and spsr_irq to SVC_mode stack*/
	srsdb	sp!,	#19
	/* switch to svc mode */
	cps		#19
	push	{r0-r12 ,lr}

	and		r1,		sp,	#4
	sub		sp,		sp,	r1

	push	{r0-r1, lr}
	bl		find_vic_num

	cpsie	i

	/* r0 hold the num*/
	bl	irq_exception

	cpsid	i

	pop		{r0-r1,	lr}
	/* balance stack */
	add		sp,		sp,	r1
	pop		{r0-r12, lr}
	rfeia	sp!


.align 5
.extern fiq_exception
fiq:
	bl	fiq_exception



.extern debug_abort
debug_abort:
	mrs 	r0,		cpsr
	bic		r0,		r0,	#0xff
	orr		r0,		r0,	#0xd3
	msr		cpsr,	r0

	mov		r1,		sp

	mrs		r0,		cpsr
	bic		r0,		r0, #0xff
	orr		r0,		r0,	#0xd7
	msr		cpsr,	r0

	mov		r0,		r1
	mov		pc,		lr

.extern debug_undefined
debug_undefined:
	mrs 	r0,		cpsr
	bic		r0,		r0,	#0xff
	orr		r0,		r0,	#0xd3
	msr		cpsr,	r0

	mov		r1,		sp

	mrs		r0,		cpsr
	bic		r0,		r0, #0xff
	orr		r0,		r0,	#0xdb
	msr		cpsr,	r0

	mov		r0,		r1
	mov		pc,		lr

.end
