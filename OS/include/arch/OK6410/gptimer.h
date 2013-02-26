#ifndef __GPTIMER_H__
#define __GPTIMER_H__

#define TCFG0		0x7f006000
#define	TCFG1		0x7f006004
#define	TCON		0x7f006008
#define	TCNTB0		0x7f00600c
#define TCMPB0		0x7f006010
#define TCNTO0		0x7f006014
#define	TCNTB1		0X7f006018
#define TCMPB1		0x7f00601c
#define	TCNTO1		0x7f006020
#define TCNTB2		0x7f006024
#define TCNTO2		0x7f00602c
#define TCNTB3		0x7f006030
#define TCNTO3		0x7f006038
#define TCNTB4		0x7f00603c
#define TCNTO4		0x7f006040
#define TINT_CSTAT	0x7f006044

#define HZ			1

#define PRESCAL_VAL 	125
//16
#define DIVIDER_VAL		0x4
#define SECOND_TICK_NUM	33250
#define MS_TICK_NUM		3325
#define _NUM_           MS_TICK_NUM

struct system_timer{
	unsigned long tick;
	void	(*init)(void);
	void	(*suspend)(void);
	void	(*resume)(void);
	void	(*start)(void);
	void    (*isr)(void);
};

extern struct system_timer s3c64xx_timer;


#endif
