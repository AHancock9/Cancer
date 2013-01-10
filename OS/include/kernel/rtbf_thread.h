#ifndef _RTBF_THREAD_H_
#define _RTBF_THREAD_H_
/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.21
		@author ZhangYan
		@brief
            Real-time bottom half thread
		@detail

	@end
********************************************************
********************************************************/
#include "Cancer.h"
#include "thread.h"

_IMPORT void Rtbf_Lib_Init();
_IMPORT struct ThreadObject * getRtbfThread();


#endif /*_RTBF_THREAD_H_*/

