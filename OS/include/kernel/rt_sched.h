#ifndef _RT_SCHED_H_
#define _RT_SCHED_H_

/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.25
		@author ZhangYan
		@brief
            Merry Chrismas.It's the real time scheduler.
		@detail
            Merry Chrismas.It's the real time scheduler</br>
            for the real time thread.This scheduler</br>
            comforms to the priority of thread strictly</br>
            That means the priority of thread could NOT</br>
            be changed.Highest priority of thread could</br>
            preempt the other thread.
	@end
********************************************************
********************************************************/
#include "Cancer.h"
#include "thread.h"

_IMPORT void rt_sched();
_IMPORT void rt_sched0();


#endif /*_RT_SCHED_H_*/
