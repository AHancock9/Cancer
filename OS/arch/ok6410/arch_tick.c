#include "arch_tick.h"
#include "built_in_func.h"

static struct system_timer *sys_timer_p = &s3c64xx_timer;
static struct u_boot_func_sets *funcp = &uboot;


void setup_system_tick(void)
{
	sys_timer_p->tick = 0;
	sys_timer_p->init();
	sys_timer_p->start();
}


void tick(void)
{
	//funcp->printf("tick! cur tick val is %ld\n",sys_timer_p->tick);
	Hal_Interrupt_Entry(0);
}


