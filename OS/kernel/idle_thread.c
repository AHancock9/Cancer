
/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2013.1.6
		@author ZhangYan
		@brief
            Idle thread lib
		@detail
	@end
********************************************************
********************************************************/
#include "idle_thread.h"

/*privates*/
_LOCAL struct ThreadObject idleThread;
_LOCAL u32  idleStack[512];


os_status Idle_Thread_Entry(void * arg)
{
    DEBUG_PUTS("idle thread starts...");
    while(1)
    {

    }
}

void Idle_Thread_Lib_Init()
{
    CreateThraed(&idleThread,
                 CFG_MAX_PRIO-1,
                 Idle_Thread_Entry,
                 idleStack,
                 512);
}
