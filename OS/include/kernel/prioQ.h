#ifndef _PRIORITYLIST_H_
#define _PRIORITYLIST_H_


/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.24
		@author ZhangYan
		@brief
            The priority list lib.
		@detail
            This lib is necessary for kernel cause the
            kernel use this structrue to make the
            ready queue.
	@end
********************************************************
********************************************************/
#include "Cancer.h"
#include "priobmp.h"
#include "list.h"
#include "thread.h"

#define hightest_thread_f() \
               getThreadInPrioQ( \
               getHighestPrio(),OPT_PRIO_Q_FIRST)

#define hightest_thread_l() \
               getThreadInPrioQ( \
               getHighestPrio(),OPT_PRIO_Q_LAST)

struct PrioQueue
{
    u32                 threadCtr;              /*the counter of threads in list*/
    struct ListHead     tListHead[CFG_MAX_PRIO];/*table driven prio list*/
    struct PrioBitmap   tPrioBmp;               /*the priority bitmap*/
};

/*externs*/
_IMPORT void RdyQ_Lib_Init();

_IMPORT void insertPrioQ(struct ThreadObject *pThread,
                         os_option            option);

_IMPORT os_prio getHighestPrio();

_IMPORT struct ThreadObject* getThreadInPrioQ(os_prio prio,os_option opt);

_IMPORT void removePrioQ(struct ThreadObject * pThread);


#endif /*_PRIORITYLIST_H_*/
