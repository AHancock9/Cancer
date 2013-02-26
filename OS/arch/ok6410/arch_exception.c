#include "arch_exception.h"
#include "built_in_func.h"
#include "low_level.h"
#include "arch_context.h"


static struct u_boot_func_sets *funcp = &uboot;

void (*isr[64])(void);

void vic_init(void)
{
	unsigned long tmp;
	/* no fiq */
	tmp = readl(VIC0_BASE + VIC_INT_SELECT_OFFSET);
	tmp &= 0x0;
	writel(tmp, VIC0_BASE + VIC_INT_SELECT_OFFSET);

	tmp = readl(VIC1_BASE + VIC_INT_SELECT_OFFSET);
	tmp &= 0x0;
	writel(tmp, VIC1_BASE + VIC_INT_SELECT_OFFSET);

	/* disable all irq route*/
	tmp = readl(VIC0_BASE + VIC_INT_ENCLEAR_OFFSET);
	tmp |= (0xffffffff);
	writel(tmp, VIC0_BASE + VIC_INT_ENCLEAR_OFFSET);

	tmp = readl(VIC1_BASE + VIC_INT_ENCLEAR_OFFSET);
	tmp |= (0xffffffff);
	writel(tmp, VIC1_BASE + VIC_INT_ENCLEAR_OFFSET);


	/* no swi interrupt */
	tmp = readl(VIC0_BASE + VIC_SOFT_INT_CLEAR_OFFSET);
	tmp |= (0xffffffff);
	writel(tmp, VIC0_BASE + VIC_SOFT_INT_CLEAR_OFFSET);

	tmp = readl(VIC1_BASE + VIC_SOFT_INT_CLEAR_OFFSET);
	tmp |= (0xffffffff);
	writel(tmp, VIC1_BASE + VIC_SOFT_INT_CLEAR_OFFSET);

	/* no fiq only irq */
	disable_fiq();
	enable_irq();
}

void irq_ack_mask(int num)
{
	int tmp;
	if (num < 32) {
		tmp = readl(VIC0_BASE + VIC_INT_ENCLEAR_OFFSET);
		tmp |= (1 << num);
		writel(tmp, VIC0_BASE + VIC_INT_ENCLEAR_OFFSET);
	} else {
		tmp = readl(VIC1_BASE + VIC_INT_ENCLEAR_OFFSET);
		tmp |= (1 << (num - 32));
		writel(tmp, VIC1_BASE + VIC_INT_ENCLEAR_OFFSET);
	}
}

void irq_unmask(int num)
{
	int tmp;
	if (num < 32) {
		tmp = readl(VIC0_BASE + VIC_INT_ENABLE_OFFSET);
		tmp |= (1 << num);
		writel(tmp, VIC0_BASE + VIC_INT_ENABLE_OFFSET);
	} else {
		tmp = readl(VIC1_BASE + VIC_INT_ENABLE_OFFSET);
		tmp |= (1<< (num - 32));
		writel(tmp, VIC1_BASE + VIC_INT_ENABLE_OFFSET);
	}
}

int irq_request(int num, void(*isr_func)(void))
{
	int ret = 0;
	int vic;
	int tmp;

	if (num < 0 || num >63) {
		funcp->printf("illegal isr num\n");
		ret = -1;
		return ret;
	}

	if (isr_func == NULL) {
		funcp->printf("isr func is null\n");
		ret = -1;
		return ret;
	}

	if (num < 32)
		vic = 0;
	else
		vic = 1;

	if (!vic) {
		tmp = readl(VIC0_BASE + VIC_INT_ENABLE_OFFSET);
		tmp |= (1 << num);
		writel(tmp, VIC0_BASE + VIC_INT_ENABLE_OFFSET);
//		writel(isr_func, VIC0_VECT_ADDR(num));
	} else {
		tmp = readl(VIC1_BASE + VIC_INT_ENABLE_OFFSET);
		tmp |= (1 << (num - 32));
		writel(tmp, VIC1_BASE + VIC_INT_ENABLE_OFFSET);
//		writel(isr_func, VIC1_VECT_ADDR(num - 32));
	}
	isr[num] = isr_func;

	return ret;
}


void irq_free(int num)
{
	if (isr[num] == NULL) {
		funcp->printf("isr not exist!check your brain\n");
		return;
	}

	irq_ack_mask(num);
	isr[num] = NULL;
}

static int find_first_bit(int tmp)
{
	int i;
	for (i = 0;i < 32;i++) {
		if ((1 << i)&(tmp & (1 << i))) {
            return i;
		}
	}
	return -1;
}


/* context in irq mode with irq disabled*/
/* FIXME: need to ack vic_addr */
int find_vic_num(void)
{
	int tmp,num;
	tmp = readl(VIC0_BASE + VIC_IRQ_STATUS_OFFSET);
	num = find_first_bit(tmp);

	if (num < 0) {
		tmp = readl(VIC1_BASE + VIC_IRQ_STATUS_OFFSET);
		num = find_first_bit(tmp);

		if (num < 0) {
			funcp->printf("irq occur but num is -1\n");
			return -1;
		} else {
			irq_ack_mask(num + 32);
		}

	} else {
		irq_ack_mask(num);
	}
	return num;
}


void unexception_abort(unsigned long sp, int kind, unsigned long pc)
{
	funcp->printf("UNEXCEPTION ABORT!!! KIND IS %d!!! PC IS %08x SP IS %08x\n", kind, pc, sp);
	funcp->printf("board hangs...\n");
	while(1);
}
void swi(void)
{
	funcp->printf("SWI NOT SUPPORT NOW!!!\n");
	funcp->printf("board hangs...\n");
	while(1);
}

void irq_exception(int num){
	void (*isr_p)(void);
	isr_p = isr[num];

	if (isr_p == NULL) {
		funcp->printf("ISR is NULL, num is %d\n",num);
		goto done;
	}

	isr_p();
done:
	irq_unmask(num);
	return;
}

void fiq_exception(void){
	funcp->printf("FIQ NOT SUPPORT NOW!!!\n");
	funcp->printf("board hangs...\n");
	while(1);
}


void ret_from_irq(void){
    /*call the schedler to run the next thread*/
    //funcp->printf("ret from irq\n");
    rt_sched();
}

void debug_check(unsigned long lr){
	funcp->printf("jump to %08x\n",lr);
}
void irq_bootomhalf(void){

}

