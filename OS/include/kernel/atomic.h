#ifndef _ATMIC_H_
#define _ATMIC_H_
/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.20
		@author ZhangYan
		@brief
			Atomic structures and its operations.
		@detail
			This file contains the atomic structure and</br>
			operations please DO NOT operate the Atomic</br>
			yourself directly,let the operations do it</br>
	@end
********************************************************
********************************************************/
#include "ktype.h"

/*The basic structure for atomic opeation*/
struct Atomic
{
	vs32 value;
}
struct Atomic64
{
	vs64 value;
}
/*The common operation for ATOMIC32*/
_IMPORT u32 readAtomic(struct * Atomic atomic);
_IMPORT void writeAtomic(struct * Atomic atomic,s32 newValue);
_IMPORT s32 addAtomic(struct * Atomic atomic,s32 plusValue);
_IMPORT s32 subAtomic(struct * Atomic atomic,s32 subValue);
_IMPORT s32 clearAtomic(struct * Atomic atmoic);
_IMPORT s32 incAtomic(struct * Atomic atomic);
_IMPORT s32 decAtomic(struct * Atomic atomic);
/*atomic bit operations*/
_IMPORT s32 orAtomic(struct * Atomic atomic1,struct * Atomic atomic2);
_IMPORT s32 andAtomic(struct * Atomic atomic1,struct * Atomic atomic2);
_IMPORT s32 xorAtomic(struct * Atomic atomic1,struct * Atomic atomic2);
_IMPORT s32 orAtomic(struct * Atomic atomic1,struct * Atomic atomic2);
_IMPORT s32 nandAtomic(struct * Atomic atomic1,struct * Atomic atomic2);
/*The common operation for ATOMIC64*/

_IMPORT u32 readAtomic64(struct * Atomic64 atomic);
_IMPORT void writeAtomic64(struct * Atomic64 atomic,s32 newValue);
_IMPORT s32 addAtomic64(struct * Atomic64 atomic,s32 plusValue);
_IMPORT s32 subAtomic64(struct * Atomic64 atomic,s32 subValue);
_IMPORT s32 clearAtomic64(struct * Atomic64 atmoic);
_IMPORT s32 incAtomic64(struct * Atomic64 atomic);
_IMPORT s32 decAtomic64(struct * Atomic64 atomic);

/*atomic bit operations*/
_IMPORT s32 orAtomic64(struct * Atomic64 atomic1,struct * Atomic64 atomic2);
_IMPORT s32 andAtomic64(struct * Atomic64 atomic1,struct * Atomic64 atomic2);
_IMPORT s32 xorAtomic64(struct * Atomic64 atomic1,struct * Atomic64 atomic2);
_IMPORT s32 orAtomic64(struct * Atomic64 atomic1,struct * Atomic64 atomic2);
_IMPORT s32 nandAtomic64(struct * Atomic64 atomic1,struct * Atomic64 atomic2);


#endif /*_ATMIC_H_*/
