#ifndef _HAL_CONTEXT_H_
#define _HAL_CONTEXT_H_

#include "Cancer.h"
#include "arch_context.h"

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

#define CONTEXT_SWITCH(from,to) \
                context_switch(&((from)->context),&((to)->context))

#define CONTEXT_SWITCH_FORCE(to) \
                context_switch_force(&((to)->context))

struct ContextObject
{
    struct cpu_context_save context;
};

/*externs*/
_IMPORT void initContextObject(struct ContextObject * pContext,
                               u32 *                  pStkBase);

#endif /*_HAL_OCNTEXT_H_*/
