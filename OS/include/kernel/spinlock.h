#ifndef _SPIN_LOCK_H
#define _SPIN_LOCK_H
/*******************************************************
********************************************************
	@begin
		@type file
		@author ZhangYan
		@date 2012.12.20
		@version 0.0.1
		@brief
			This file is about the spinlock
		@detail
			This file contains the spinlock sturctures and
			the operations whick is independ in specific
			architecture
	@end
********************************************************
********************************************************/
#include "ktype.h"

/*The interupt level spin lock*/
struct SpinLockIsr
{
	vu32 lock;
};
/*The task level spin lock*/
struct SpinLockTask
{
	vu32 lock;
};

/*The task level and isr level spin lock*/
struct SpinLock
{
	vu32 lock;
};
/*externs*/
/*The operations for the interupt level spin lock*/
void initSpinLockIsr(struct SpinLockIsr* pLock);
void giveSpinLockIsr(struct SpinlockIsr* pLock);
void takeSpinLockIsr(struct SpinlockIsr* pLock);
void trySpinLockIsr(struct SpinlockIsr* pLock);

/*The operations for the task level spin lock*/
void initSpinLockTask(struct SpinLockTask* pLock);
void giveSpinLockTask(struct SpinLockTask* pLock);
void takeSpinLockTask(struct SpinLockTask* pLock);
void trySpinLockTask(struct SpinLockTask* pLock);

/*The operations for spin lock*/
void initSpinLock(struct SpinLock* pLock);
void giveSpinLock(struct SpinLock* pLock);
void takeSpinLock(struct SpinLock* pLock);
void trySpinLock(struct SpinlockIsr* pLock);

#endif /*_SPIN_LOCK_H*/
