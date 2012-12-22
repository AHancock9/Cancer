#ifndef _TIMER_H_
#define _TIMER_H_
#include "Cancer.h"
#include "wheellist.h"
/*
	@begin 
		@type file
		@version 0.0.1
		@author ZhangYan
		@date 2012.12.20
		@brief
			This files contains the Timer Lib head file.
		@detail
			For SMP system ,each cpu has its own timer list in Cancer OS,</br>
			so , we are able to ignore the synchronization between </br>
			two cpus,we just use taskLock to lock the time list structure.
	@end
*/


/*The timer key word*/
typedef u8 tmr_opt
typedef u8 tmr_state

/*The Timer option */
#define OPT_TMR_ONE_SHOT 0		/*one shot time mode*/
#define OPT_TMR_PERIOD 1		/*period time mode*/

/*The Timer stop option used as an argument for stopTimer*/
#define OPT_TMR_STOP_NONE 0
#define	OPT_TMR_STOP_CALL 1
#deffine OPT_TMR_STOP_CALL_ARG 2

/*The timer state*/
#define  STA_TMR_UNUSED 0
#define  STA_TMR_STOPPED 1
#define  STA_TMR_RUNNING 2
#define  STA_TMR_COMPLETED 3

typedef *(tmr_callbackPtr)(void * pTimer,void * pTimerArg);

/*
	@begin 
		@type struct
		@brief 
			TimerSlot for Cancer timer lib.It's the basic</br>
			structrue for timerlib,you can also disable this lib </br>
			in kernel config
			
	@end
*/
struct TimerSlot
{
	struct KObject object; /*kernel object */
	struct WheelNode tTimerNode; /* timer node in timer list*/
	tmr_callbackPtr pCallback; /*the timer callback function*/
	void * pCallbackArg; /*the callbackk argument*/
	tick_t match;	/*the absolute tick to match*/
	tick_t remain;	/*the left tick to match*/
	tick_t delay;	/*the delay to start the timer*/
	tick_t period;	/*the period of timer*/
	tmr_opt option; /*option for a timer*/
	tmr_state state; /*timer state*/
}
extern void initTimerLib();
/*The operations we need to manipulate timer*/
//void initTimerSlot(struct TimerSlot* pTimer);
extern bool stopTimer(struct TimerSlot * pTimer);
extern bool startTimer(struct TimerSlot * pTimer);
extern bool createTimer(struct TimerSlot * pTimer,
				tick_t delay,
				tick_t period,
				tmr_opt option,
				tmr_callbackPtr pCallback,
				void * pCallbackArg);
extern bool deleteTimer(struct TimerSlot * pTimer,tmr_opt optino,
				void * pCallbackArg;);
extern tict_t getTimerRemain(struct TimerSlot * pTimer);
extern tmr_state getTimerState(struct TimerSlot * pTimer);
extern tmr_opt getTimerOpt(struct TimerSlot * pTimer);
#endif /*_TIMER_H_*/