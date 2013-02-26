#ifndef _KTYPE_H_
#define _KTYPE_H_
/******************************************************
*******************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.17
		@brief
			Types in kernel programming
		@detail
			This file contains the types and the other
			type-information used in kernel programming
		@author ZhangYan
	@end
*******************************************************
*******************************************************/
#include "types.h"


#define _API
#define _LOCAL  static
#define _IMPORT extern

/*retype in kernel */

typedef u32     os_option;
typedef u32     os_state;
typedef u8      os_status;   /*the status used in exit code*/
typedef u32     os_prio;
typedef u32     os_vector;   /*the interupt of vector*/
typedef u8      obj_type;    /*the type of object*/
typedef u32     obj_id;      /*the id of object*/
typedef u32     sem_ctr;     /*semaphore couter*/

#if CFG_TICK_64U_EN>  0
    typedef u64     os_tick;     /*the tict in kernel*/
#else
    typedef u32     os_tick;     /*the tict in kernel*/
#endif /*CFG_TICK_64U_EN>0*/

typedef u32     os_tid;      /*the thread ID*/

/*function pointers*/

typedef void      (*Int_entryPtr)   (void * arg);
typedef os_status (*Thread_entryPtr)(void * arg);


#endif /*_KTYPE_H_*/
