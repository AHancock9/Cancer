#ifndef _TIMER_H_
#define _TIMER_H_

#if CFG_TIMER_EN >0

/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@author ZhangYan
		@date 2012.12.20
		@brief
			This files contains the Timer Lib head file.
		@detail
			For SMP system ,each cpu has its own timer list</br>
			in Cancer OS,so , we are able to ignore the</br>
			synchronization between two cpus,we just use</br>
			taskLock to lock the time list structure.</br>
	@end
********************************************************
********************************************************/
#include "Cancer.h"
#include "wheellist.h"

/*The timer key word*/
typedef     os_option   tmr_opt;
typedef     os_state    tmr_state;
typedef     void (* Tmr_callbackPtr)(void * pTimer,
                                     void * pTimerArg);

/*The Timer option */
#define OPT_TMR_NONE 0          /*none options.INIT*/
#define OPT_TMR_ONE_SHOT 1		/*one shot time mode*/
#define OPT_TMR_PERIOD 2		/*period time mode*/

/*The Timer stop option used as an argument for stopTimer*/
#define OPT_TMR_STOP_NONE 0
#define	OPT_TMR_STOP_CALL 1
#define OPT_TMR_STOP_CALL_ARG 2

/*The timer state*/
#define  STA_TMR_UNUSED 0
#define  STA_TMR_STOPPED 1
#define  STA_TMR_RUNNING 2
#define  STA_TMR_COMPLETED 3

/*******************************************************
********************************************************
	@begin
		@type struct
		@brief
			TimerSlot for Cancer timer lib.It's the basic</br>
			structrue for timerlib,you can also disable this</br>
			lib in kernel config
	@end
********************************************************
********************************************************/
struct TimerSlot
{
	struct BaseObject tBaseObject;  /*kernel base object */
	struct WheelNode  tTimerNode;   /*timer node in timer list*/
	Tmr_callbackPtr   pCallback;    /*the timer callback function*/
	void *            pCallbackArg; /*the callbackk argument*/
	os_tick           match;	    /*the absolute tick to match*/
	os_tick           remain;	    /*the left tick to match*/
	os_tick           delay;	    /*the delay to start the timer*/
	os_tick           period;	    /*the period of timer*/
	tmr_opt           option;       /*option for a timer*/
	tmr_state         state;        /*timer state*/
};

/*externs*/

_IMPORT bool stopTimer(struct TimerSlot * pTimer,
                       tmr_opt stopOpt,
                       void * pCallbackArg);
_IMPORT bool startTimer(struct TimerSlot * pTimer);
_IMPORT bool createTimer(struct TimerSlot * pTimer,
                         os_tick delay,
                         os_tick period,
                         tmr_opt option,
                         Tmr_callbackPtr pCallback,
                         void * pCallbackArg);
_IMPORT bool deleteTimer(struct TimerSlot * pTimer,
                         tmr_opt optino,
                         void * pCallbackArg);
_IMPORT os_tick getTimerRemain(struct TimerSlot * pTimer);
_IMPORT tmr_state getTimerState(struct TimerSlot * pTimer);
_IMPORT tmr_opt getTimerOpt(struct TimerSlot * pTimer);
_IMPORT bool Timer_Lib_Init();

#endif /*CFG_TIMER_EN >0*/

#endif /*_TIMER_H_*/
