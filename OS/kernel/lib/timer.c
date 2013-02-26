/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.20
		@author ZhangYan
		@brief
            This file contains the timer operations
		@detail
	@end
********************************************************
********************************************************/

#include "timer.h"

#if CFG_TIMER_EN >0

/*privates*/

static void init_timerSlot(struct TimerSlot* pTimer)
{
    /*TO DO*/
    /*kobject to init*/
    /*TO DO*/
    pTimer->pCallback = NULL;
    pTimer->pCallbackArg = NULL;
    pTimer->match = 0;
    pTimer->remain = 0;
    pTimer->period = 0;
    pTimer->delay = 0;
    pTimer->option = OPT_TMR_NONE;
    pTimer->state = STA_TMR_UNUSED;
}

/*publics*/
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
bool stopTimer(struct TimerSlot * pTimer,
                tmr_opt stopOpt,
                void * pCallbackArg)
{
    return false;
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
bool startTimer(struct TimerSlot * pTimer)
{
    return false;
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
bool createTimer(struct TimerSlot * pTimer,
                        os_tick delay,
                        os_tick period,
                        tmr_opt option,
                        Tmr_callbackPtr pCallback,
                        void * pCallbackArg)
{
    init_timerSlot(pTimer);
    //initWheelNode(&pTimer->tTimerNode,pTimer->match);
    return false;
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
bool deleteTimer(struct TimerSlot * pTimer,
                 tmr_opt optino,
                 void * pCallbackArg)
{
    return false;
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
os_tick getTimerRemain(struct TimerSlot * pTimer)
{
    return 0;
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
tmr_state getTimerState(struct TimerSlot * pTimer)
{
    return 0;
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
tmr_opt getTimerOpt(struct TimerSlot * pTimer)
{
    return 0;
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
bool Timer_Lib_Init()
{
    return false;
}

#endif /*CFG_TIMER_EN*/

