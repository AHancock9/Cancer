#ifndef __BUILT_IN_FUNC__
#define __BUILT_IN_FUNC__

#include "Cancer.h"
struct u_boot_func_sets {
	/* printf at c7e11988*/
	void (*printf)(const char* fmt,...);
	/* getc at c7e11920*/
	int (*getc)(void);
	/* return hz not mhz */
	unsigned long (*get_FCLK)(void);
	unsigned long (*get_HCLK)(void);
	/*66500000*/
	unsigned long (*get_PCLK)(void);
	unsigned long (*get_UCLK)(void);
	unsigned long (*get_ARMCLK)(void);
};


extern struct u_boot_func_sets uboot;
void init_built_in_func(void);

#define __getl(a)		(*(volatile unsigned long *)(a))
#define __putl(v, a) 	(*(volatile unsigned long *)(a) = (v))

#define writel(v, a)	__putl(v, a)
#define readl(a)		__getl(a)


#endif
