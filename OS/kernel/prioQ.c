
/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.24
		@author ZhangYan
		@brief
		@detail
	@end
********************************************************
********************************************************/
#include "prioQ.h"

/*privates*/
_LOCAL struct PrioQueue rdyQueue[MAX_CPU]; /*the ready queue*/

static void init_prio_queue(struct PrioQueue * pQueue)
{
    int i;
    pQueue->threadCtr = 0;
    for(i=0;i<CFG_MAX_PRIO;i++)
    {
        initListHead(&pQueue->tListHead[i]);
    }
    initBitmap(&pQueue->tPrioBmp);
}

/*publics*/

/*******************************************************
********************************************************
	@begin
		@type fun
		@brief
            Insert a thread object into priority queue.
		@detail
		@param
            pThread The thread ojbect to be inserted
            option The option
		@return
	@end
********************************************************
********************************************************/
void insertPrioQ(struct ThreadObject *pThread,os_option option)
{
    struct PrioQueue * pPrioQ = &rdyQueue[current_cpu];
    os_prio prio = pThread->prio;
    struct PrioBitmap *pPrioBmp = &pPrioQ->tPrioBmp;
    struct ListHead * pList = pPrioQ->tListHead;
    /*insert the biStmap*/
    insertBitmap(prio,pPrioBmp);
    switch(option)
    {
        case OPT_PRIO_Q_FIRST:
            /*insert the thread at the first entry*/
            addList(&pThread->tRdyListHead,&pList[prio]);
            break;
        case OPT_PRIO_Q_LAST:
            /*insert the thread at the last entry*/
            addList2Tail(&pThread->tRdyListHead,&pList[prio]);
            break;
    }
    pPrioQ->threadCtr++;
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
os_prio getHighestPrio()
{
    struct PrioQueue * pCurrentQ = &rdyQueue[current_cpu];
    os_prio prio = getPrioHighest(&pCurrentQ->tPrioBmp);
    return prio;
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
void RdyQ_Lib_Init()
{
    int i ;
    for(i=0;i<MAX_CPU;i++)
    {
        init_prio_queue(&rdyQueue[i]);
    }
}
/*******************************************************
********************************************************
	@begin
		@type fun
		@brief
			Get the thread in the priority given.
		@detail

		@param [prio]
                The priority given
        @prarm [opt]
                option we need
		@return
            The thread object pointer.NULL if no thread
            linked in this priority of queue.
	@end
********************************************************
********************************************************/
struct ThreadObject* getThreadInPrioQ(os_prio prio,os_option opt)
{
    struct PrioQueue * pCurrentQ = &rdyQueue[current_cpu];
    struct ListHead * pList= &pCurrentQ->tListHead[prio];
    struct ThreadObject * pThreadRtn = NULL;
    if(isListEmpty(pList))
    {
        return pThreadRtn;
    }
    else
    {
        switch(opt)
        {
            case OPT_PRIO_Q_FIRST:
                /*get the first thread*/
                pThreadRtn = transLHead2Thread(pList->pNext);
                break;
            case OPT_PRIO_Q_LAST:
                pThreadRtn= transLHead2Thread(pList->pPrev);
                break;
            default:break;
        }
    }
    return pThreadRtn;
}

/*******************************************************
********************************************************
	@begin
		@type fun
		@brief
            Remove thread object from current ready list
		@detail

		@param [pThread]
                The thread to be removed
		@return
	@end
********************************************************
********************************************************/
void removePrioQ(struct ThreadObject * pThread)
{
    struct PrioQueue * pCurrentQ = &rdyQueue[current_cpu];
    pCurrentQ->threadCtr--;
    os_prio prio = pThread->prio;
    deleteList(&pThread->tRdyListHead);
    struct ListHead * pList = &pCurrentQ->tListHead[prio];

    /*if no thread linked in this priority list we should remove it*/
    if(isListEmpty(pList))
    {
        removeBitmap(prio,&pCurrentQ->tPrioBmp);
    }

    return ;
}
