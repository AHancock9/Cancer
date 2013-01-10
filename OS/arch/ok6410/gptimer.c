#include "gptimer.h"
#include "built_in_func.h"
#include "arch_exception.h"
#include "arch_tick.h"

static struct u_boot_func_sets *funcp = &uboot;

void system_timer_start(void)
{
	funcp->printf("timer start\n");
	s3c64xx_timer.start();
}

static void s3c64xx_system_timer_isr(void)
{
	unsigned long tint;
	s3c64xx_timer.tick++;
	tick();
	/* clear int in tint */
	tint = readl(TINT_CSTAT);
	tint |= (1 << 9);
	writel(tint, TINT_CSTAT);
}

static void s3c64xx_system_timer_setup(void)
{
	unsigned long tcon;
	unsigned long tcnt;
	unsigned long tcfg0;
	unsigned long tcfg1;
	unsigned long tint_cstat;
	unsigned long pclk;

	unsigned long pre_scale;
	unsigned long div_val;
	unsigned long load;

	pclk = funcp->get_PCLK();

	if (pclk == 0) {
		funcp->printf("error...read pclk 0\n");
		return;
	}

	pre_scale = PRESCAL_VAL - 1;
	div_val = DIVIDER_VAL;
	load = _NUM_;


	tcon = readl(TCON);
	tcfg0 = readl(TCFG0);
	tcfg1 = readl(TCFG1);

	tcfg0 &= ~(0xff << 8);
	tcfg0 |= (pre_scale << 8);
	funcp->printf("set timer4 pre_scale with %ld\n",pre_scale);
	writel(tcfg0, TCFG0);

	tcfg1 &= ~(0xf << 16);
	tcfg1 |= (div_val << 16);
	funcp->printf("set timer4 div with %ld\n",div_val);
	writel(tcfg1, TCFG1);

	tint_cstat = readl(TINT_CSTAT);
	tint_cstat &= ~(0x1 << 4);
	/* enable tick interrupt! */
	tint_cstat |= (0x1 << 4);
	writel(tint_cstat, TINT_CSTAT);

	funcp->printf("timer4 load %ld\n",load);
	writel(load, TCNTB4);
	tcon &= ~(7 << 20);
	/* reload */
	tcon |= (1 << 22);
	/* update */
	tcon |= (1 << 21);
	writel(tcon, TCON);
	funcp->printf("timer4 loading complete!\n");
}

static void s3c64xx_system_timer_init(void)
{
	s3c64xx_system_timer_setup();
	irq_request(INT_TIMER4, s3c64xx_timer.isr);
}

static void s3c64xx_system_timer_start(void)
{
	unsigned long tcon;
	tcon = readl(TCON);

	if (tcon & (1 << 20) != 0) {
		funcp->printf("timer4 has started!\n");
		return;
	}

	tcon |= (1 << 20);
	tcon &= ~(1 << 21);
	writel(tcon, TCON);
	funcp->printf("timer4 starts!\n");
}

struct system_timer s3c64xx_timer = {
	.init = s3c64xx_system_timer_init,
	.isr  = s3c64xx_system_timer_isr,
	.start = s3c64xx_system_timer_start,
};


