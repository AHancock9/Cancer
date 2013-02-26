#ifndef _TYPES_H_
#define _TYPES_H_

/******************************************************
*******************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.17
		@brief
			Types independent on specific cpu architecture
		@detail
			This file contains the common types which
			are independent on specific cpu architecture
		@author ZhangYan
	@end
*******************************************************
*******************************************************/

#define NULL        ((void *)0)
#define true            1
#define false           0
#define INT_BITS        32

/* the common type*/

typedef char *                          string;
typedef signed char                     s8;
typedef signed short                    s16;
typedef signed int                      s32;
typedef signed long long                s64;
typedef unsigned char                   u8;
typedef unsigned short                  u16;
typedef unsigned int                    u32;
typedef unsigned long long              u64;
typedef volatile unsigned char          vu8;
typedef volatile unsigned short         vu16;
typedef volatile unsigned int           vu32;
typedef volatile unsigned int           vu64;
typedef signed int                      bool;
typedef unsigned char                   byte;


#endif /*_TYPES_H_*/
