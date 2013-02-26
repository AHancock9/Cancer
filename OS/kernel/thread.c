
/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.27
		@author ZhangYan
		@brief
            Thread Lib.
		@detail
	@end
********************************************************
********************************************************/
#include "thread.h"
#include "interrupt.h"
/*privates*/
_LOCAL os_tid curThreadID[MAX_CPU];

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
_API os_tid CreateThraed(struct ThreadObject *tcb,
                         os_prio              prio,
                         Thread_entryPtr      entry,
                         u32 *                pStkBase,
                         u32                  stkSize)
{
    tcb->prio = prio;
    tcb->threadEntry = entry;
    pStkBase+=stkSize;
    initContextObject(&tcb->tContext,pStkBase);
    initListHead(&tcb->tRdyListHead);
    insertPrioQ(tcb,OPT_PRIO_Q_LAST);
    tcb->tid = (os_tid)tcb;
    return 0;
}
/*******************************************************
********************************************************
	@begin
		@type fun
		@brief
            Using TID to get the threadOjbect.
		@detail
        @param [tid] Thread id
		@return
            If NULL the tid is invalid
	@end
********************************************************
********************************************************/
_API struct ThreadObject * FromTID(os_tid tid)
{

    return (struct ThreadObject *)tid;
}
/*******************************************************
********************************************************
	@begin
		@type fun
		@brief
            Delay a thread.
		@detail
		@param [time]
                The real world time,unit depends on the opt
        @param [opt]
		@return
	@end
********************************************************
********************************************************/
_API os_status DelayThread(u32       time,
                           os_option opt,
                           os_tid    tid)
{
    struct ThreadObject * pThread;
    struct BlockSlot      pSlot;
    os_tick               ticks;

    if(tid==THREAD_SELF)
    {
        pThread = getCurThread();
    }
    else
    {
        pThread = FromTID(tid);
        if(pThread==NULL)
        {
            return ERR_INVALID_TID;
        }
    }
    disableLocalInt();

    switch(opt)
    {
        case OPT_DELAY_MS:
            ticks = MS_TO_TICK(time) + getPrivateTick();
            break;
        case OPT_DELAY_SEC:
            ticks = SEC_TO_TICK(time) + getPrivateTick();
            break;
        case OPT_DELAY_MIN:
            ticks = MIN_TO_TICK(time) + getPrivateTick();
            break;
        case OPT_DELAY_HOUR:
            ticks = HOUR_TO_TICK(time) + getPrivateTick();
            break;
#if CFG_TIME_EN>0
        case OPT_DELAY_HMSM:
            break;
#endif
        default :
            DEBUG_PRINTF("in DelayThread()\n",ERR_INVALID_OPT);
            return ERR_INVALID_OPT;
    }
    DEBUG_PRINTF("0x%x delayed ...\n",pThread);
    initBlockSlot(&pSlot,pThread,ticks);
    insertBlockSlot(&pSlot);
    removePrioQ(pThread);
    enableLocalInt();
    rt_sched();
}
/*******************************************************
********************************************************
	@begin
		@type fun
		@brief
            Get Current ThreadObject
		@detail
		@param
		@return
            Current ThreadObject pointer
	@end
********************************************************
********************************************************/
struct ThreadObject * getCurThread()
{
    return FromTID(getCurThreadID());
}
/*******************************************************
********************************************************
	@begin
		@type fun
		@brief
            Get the current Thread id.
		@detail
		@param
		@return
            TID of ccurrent thread.
	@end
********************************************************
********************************************************/
os_tid getCurThreadID()
{
    os_tid tid = curThreadID[current_cpu];
    return tid;
}
/*******************************************************
********************************************************
	@begin
		@type fun
		@brief
            Set current thread id
		@detail
		@param
		@return
	@end
********************************************************
********************************************************/
void setCurThreadID(os_tid tid)
{
    curThreadID[current_cpu] = tid;
}
