#ifndef _THREAD_H_
#define _THREAD_H_

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
#include "Cancer.h"
#include "list.h"
#include "hal_context.h"
#include "blockQ.h"


/*from tRdyListHead to ThreadObject*/
#define transLHead2Thread(pListHead) \
    list_head_entry(pListHead,struct ThreadObject,tRdyListHead);

/*******************************************************
********************************************************
	@begin
		@type struct
		@brief
            The so-called TCB structure
		@detail
            As we konw,the thread contrl block(TCB)</br>
            but we call it 'ThreadObject',that name may</br>
            be better.
	@end
********************************************************
********************************************************/
struct ThreadObject
{
    struct BaseObject       tBaseObject;    /*the base object in kernel*/
    struct ListHead         tRdyListHead ;  /*the list head which is in rdyqueue*/
    os_prio                 prio;           /*the priority of task*/
    Thread_entryPtr         threadEntry;    /*the entry of thread*/
    void *                  pThreadAgr;     /* the argument of thread*/
    struct ContextObject    tContext;       /*cpu context*/
    os_tid                  tid;            /*the thread id*/
};

_IMPORT os_tid CreateThraed(struct ThreadObject *tcb,
                            os_prio              prio,
                            Thread_entryPtr      entry,
                            u32 *                pStkBase,
                            u32                  stkSize);

_IMPORT struct ThreadObject * FromTID(os_tid tid);

_IMPORT os_status DelayThread(u32        time,
                              os_option  opt,
                              os_tid     tid);

_IMPORT os_status SuspendThread();

_IMPORT os_tid getCurThreadID();

_IMPORT struct ThreadObject * getCurThread();

_IMPORT void setCurThreadID(os_tid tid);



#endif /*_THREAD_H_*/
