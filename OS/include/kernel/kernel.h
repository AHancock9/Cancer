#ifndef _KERNEL_H_
#define _KERNEL_H_

/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.17
		@author ZhangYan
		@brief
		@detail
	@end
********************************************************
********************************************************/
#include "Cancer.h"

/*common operations*/

/*swap*/
#define swap(a, b) \
	do { typeof(a) __tmp = (a); (a) = (b); (b) = __tmp; } while (0)

/*abs*/
#define abs(x) ({				\
		long __x = (x);			\
		(__x < 0) ? -__x : __x;		\
	})

/*min*/
#define min(x, y) ({				\
	typeof(x) _min1 = (x);			\
	typeof(y) _min2 = (y);			\
	(void) (&_min1 == &_min2);		\
	_min1 < _min2 ? _min1 : _min2; })

/*max*/
#define max(x, y) ({				\
	typeof(x) _max1 = (x);			\
	typeof(y) _max2 = (y);			\
	(void) (&_max1 == &_max2);		\
	_max1 > _max2 ? _max1 : _max2; })

/*offset_of*/
#define offset_of(TYPE, MEMBER) ((u32) &((TYPE *)0)->MEMBER)

/*container_of*/
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offset_of(type,member) );})

/*common MAX VALUE and MIN VALUE*/
#define USHORT_MAX	        ((unsigned short)(~0U))
#define SHORT_MAX	        ((signed short)(USHORT_MAX>>1))
#define SHORT_MIN	        (-SHORT_MAX - 1)
#define INT_MAX		        ((int)(~0U>>1))
#define INT_MIN		        (-INT_MAX - 1)
#define UINT_MAX	        (~0U)
#define LONG_MAX	        ((long)(~0UL>>1))
#define LONG_MIN	        (-LONG_MAX - 1)
#define ULONG_MAX	        (~0UL)
#define LLONG_MAX	        ((long long)(~0ULL>>1))
#define LLONG_MIN	        (-LLONG_MAX - 1)
#define ULLONG_MAX	        (~0ULL)


/*priority queue lib*/
#define OPT_PRIO_Q_FIRST    1       /*first entry*/
#define OPT_PRIO_Q_LAST     2       /*last entry*/

/*thread lib*/
#define THREAD_SELF         0       /*the thread self*/

/*delay units*/
#define OPT_DELAY_MS        0       /*milli*/
#define OPT_DELAY_SEC       1       /*second*/
#define OPT_DELAY_MIN       2       /*minutes*/
#define OPT_DELAY_HOUR      3       /*hours*/

/*make sure to use time lib*/
#if CFG_TIME_EN >0
    #define OPT_DELAY_HMSM  4       /*hour mintues second and milli*/
#endif



_IMPORT bool isOSStart();
_IMPORT void setCancerStart(bool flag);

#endif /*_KERNEL_H_*/
