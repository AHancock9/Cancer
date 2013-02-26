/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.21
		@author ZhangYan
		@brief
            This file is about the real-time bottom half thread.
 		@detail
            This real-time bottom half thread is the necessary </br>
            lib in Cancer OS.

	@end
********************************************************
********************************************************/
#include "rtbf_thread.h"
#include "interrupt.h"

/*privates*/

_LOCAL struct ThreadObject rtbfThread;
_LOCAL u32  rtbfStack[512];
/*******************************************************
********************************************************
	@begin
		@type fun
		@brief

		@detail
		@param
		@return
	@end
********************************************************
********************************************************/
_LOCAL os_status Rtbf_Thread_Entry(void * arg)
{
    /*the first run of rtbf thread.after the os_start()*/
    /*select the next hightest thread to run*/
    removePrioQ(&rtbfThread);
    enableLocalInt();
    DEBUG_PUTS("rtbf_first_run\n");
    rt_sched();
    while(1)
    {
        //DEBUG_PUTS("rtbf_run\n");
        disableLocalInt();
        /*refresh the praivate time*/
        incPrivateTick();
        //DEBUG_PRINTF("private tick %lld\n",getPrivateTick());
        /*call the real-time bottom half thread*/
        removePrioQ(&rtbfThread);
        refreshBlockQ(getPrivateTick());
        enableLocalInt();
        rt_sched();
    }
}

/*publics*/

/*******************************************************
********************************************************
	@begin
		@type fun
		@brief
		@detail
		@param
		@return
	@end
********************************************************
********************************************************/
struct ThreadObject * getRtbfThread()
{
    return &rtbfThread;
}
/*******************************************************
********************************************************
	@begin
		@type fun
		@brief
		@detail
		@param
		@return
	@end
********************************************************
********************************************************/
void Rtbf_Lib_Init()
{
    CreateThraed(&rtbfThread,0,Rtbf_Thread_Entry,rtbfStack,512);
}
