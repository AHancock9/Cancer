#ifndef _SPIN_LOCK_H
#define _SPIN_LOCK_H
#include "ktype.h"

/*
	@begin
		@type file
		@author ZhangYan
		@date 2012.12.20
		@version 0.0.1
		@brief 
			This file is about the spinlock
		@detail 
			This file contains the spinlock sturctures and 
			the operations whick is independ in specific architecture
	@end
*/
/*The interupt level spin lock*/
struct SpinLockIsr
{
	vu32 lock;
}
/*The task level spin lock*/
struct SpinLockTask
{
	vu32 lock;
}

/*The operations for the interupt level spin lock*/
void spinLockIsrInit(struct SpinLockIsr* pLock);
void spinLockIsrGive(struct SpinlockIsr* pLock);
void spinLockIsrTake(struct SpinlockIsr* pLock);

/*The operations for the task level spin lock*/
void spinLockTaskInit(struct SpinLockTask* pLock);
void spinLockTaskGive(struct SpinLockTask* pLock);
void spinLockTaskTake(struct SpinLockTask* pLock);



#endif /*_SPIN_LOCK_H*/