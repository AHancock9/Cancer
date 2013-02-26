#ifndef _HAL_DEBUG_
#define _HAL_DEBUG_


/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2013.1.5
		@author ZhangYan
		@brief
		@detail
	@end
********************************************************
********************************************************/

#include "Cancer.h"
#include "built_in_func.h"

_IMPORT struct u_boot_func_sets *ubootOps;

#if CFG_DEBUG_EN > 0

    #define DEBUG_PRINTF(arg,...) \
                ubootOps->printf(arg,__VA_ARGS__ )
    #define DEBUG_PUTS(arg) \
                 ubootOps->printf(arg)
#else

    #define DEBUG_PRINTF
    #define DEBUG_PUTS

#endif  /*CFG_DEBUG_EN>0*/


#endif /*_HAL_DEBUG_*/
