#include "built_in_func.h"

struct u_boot_func_sets uboot = {
	.printf = (void(*)(const char* fmt,...))0xc7e11988,
	.getc = (int(*)(void))0xc7e11920,
	.get_HCLK = (unsigned long (*)(void))0xc7e025f0,
	.get_FCLK = (unsigned long (*)(void))0xc7e025e8,
	.get_PCLK = (unsigned long (*)(void))0xc7e02644,
	.get_UCLK = (unsigned long (*)(void))0xc7e02698,
	.get_ARMCLK = (unsigned long (*)(void))0xc7e025c0,
};

void init_built_in_func(void)
{
	struct u_boot_func_sets *uboot_p = &uboot;
	uboot_p->printf("Using built in function from Uboot\nDo not overwrite uboot\n");
}





