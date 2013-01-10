#ifndef _TICK_H_
#define _TICK_H_

/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.21
		@author ZhangYan
		@brief
            This file is about
		@detail
	@end
********************************************************
********************************************************/
#include "Cancer.h"

/*common defined operations*/
#define MS_TO_TICK(ms)          ((ms)/CFG_TICK_MS)
#define TICK_TO_MS(tick)        ((tick)*CFG_TICK_MS)
#define SEC_TO_TICK(s)          MS_TO_TICK((s)*1000)
#define TICK_TO_SEC(tick)       (TICK_TO_MS(tick)/1000)
#define MIN_TO_TICK(min)        SEC_TO_TICK((min)*60)
#define TICK_TO_MIN(tick)       (TICK_TO_SEC(tick)/60)
#define HOUR_TO_TICK(hour)      MIN_TO_TICK((hour)*60)
#define TICK_TO_HOUR(tick)      (TICK_TO_MIN(tick)/60)

/*externs*/
_IMPORT void Tick_Lib_Init();
_IMPORT void incPrivateTick();
_IMPORT os_tick getPrivateTick();


#endif /*_TICK_H_*/
