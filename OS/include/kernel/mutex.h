#ifndef _MUTEX_H_
#define _MUTEX_H_

#if CFG_MUTEX_EN>0

/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.23
		@author ZhangYan
		@brief
		@detail
	@end
********************************************************
********************************************************/
#include "Cancer.h"

struct Mutex
{
    struct PendObject tPendObject;
};




#endif /*CFG_MUTEX_EN>0*/

#endif /*_MUTEX_H_*/

