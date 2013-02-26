#ifndef _AUTOCFG_H_
#define _AUTOCFG_H_

/******************************************************
*******************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.21
		@author ZhangYan
		@brief
            Kenerl auto-config in GUI/CUI shell.
		@detail
	@end
*******************************************************
*******************************************************/


#define CFG_SMP_EN              0         /*smp or up system*/
#define CFG_DEBUG_EN            1         /*as debug*/
#define CFG_TICK_MS             100       /*HZ = 1000/tick */
#define CFG_MAX_PRIO            128       /*the max priority 0~127*/

/*cpu config*/
#if CFG_SMP_EN > 0
    #define MAX_CPU 1
#else
    #define MAX_CPU 1
#endif


/*Kernel lib config*/
#define CFG_TIMER_EN            0       /*the timer lib*/
#define CFG_RTC_EN              0       /*the real time clock*/
#define CFG_MUTEX_EN            0       /*mutex lib*/
#define CFG_MSG_BOX_EN          0       /*message box lib*/
#define CFG_ERROR_EN            0       /*error lib*/
#define CFG_WHEEL_LIST_MAX      20      /*wheel list node max numbers*/
#define CFG_TICK_64U_EN         0       /*if tick in 64-bit*/
#define CFG_CPU_LEAD_ZEROS_EN   0       /*if using cpu to find the lead zero*/



#endif /*_AUTOCFG_H_*/
