
/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.25
		@author ZhangYan
		@brief
		@detail
	@end
********************************************************
********************************************************/
#include "osinit.h"
#include "hal_init.h"
#include "interrupt.h"
#include "prioQ.h"
#include "blockQ.h"
#include "rtbf_thread.h"
#include "hal_context.h"

/*******************************************************
********************************************************
	@begin
		@type fun
		@brief
		@detail
		@param
		@return
	@end
********************************************************
********************************************************/
void Cancer_Init()
{
    setCancerStart(false);
    Hal_Init();
    /*disable the interrupt*/
    disableLocalInt();
    /*init the block lib*/
    Block_Lib_Init();
    /*init the ready queue lib*/
    RdyQ_Lib_Init();
    /*init the real-time bottom half thread*/
    Rtbf_Lib_Init();
    /*init the idle thread*/
    Idle_Thread_Lib_Init();

#if CFG_TIMER_EN > 0
    /*init the timer lib*/
    Timer_Lib_Init();
#endif

    /*init the interruption lib*/
    Int_Lib_Init();
}
/*******************************************************
********************************************************
	@begin
		@type fun
		@brief
		@detail
		@param
		@return
	@end
********************************************************
********************************************************/
void Cancer_Start()
{
    setCancerStart(true);
    rt_sched0();
    /*no return here*/
    while(1);
}
