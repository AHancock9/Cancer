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
#include "rt_sched.h"
#include "prioQ.h"
#include "interrupt.h"
#include "thread.h"
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
void rt_sched0()
{
    struct ThreadObject *thread = hightest_thread_f();
    setCurThreadID(thread->tid);
    /*switch to the rtbf thread*/
    CONTEXT_SWITCH_FORCE(&thread->tContext);
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
void rt_sched()
{
    disableLocalInt();
    struct ThreadObject *pHightestThread = hightest_thread_f();
    struct ThreadObject *pCurrentThread = getCurThread();

   // DEBUG_PRINTF("0x%x\n",pHightestThread);
   // DEBUG_PRINTF("0x%x\n",pCurrentThread);
    if(pHightestThread != pCurrentThread)
    {
        setCurThreadID(pHightestThread->tid);
        enableLocalInt();
        CONTEXT_SWITCH(&pCurrentThread->tContext,&pHightestThread->tContext);
    }
}
