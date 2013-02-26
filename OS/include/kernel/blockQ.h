#ifndef _BLOCKQ_H_
#define _BLOCKQ_H_

/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.24
		@author ZhangYan
		@brief
            File contains the blocklist which is
            the necessary structure in kernel.
		@detail
	@end
********************************************************
********************************************************/

#include "Cancer.h"
#include "wheellist.h"
#include "thread.h"

struct BlockSlot
{
    struct WheelNode        tWheelNode;         /*the wheel node object*/
    struct ThreadObject *   pThread;            /*the owner thread*/
};



/*externs*/

_IMPORT void initBlockSlot(struct BlockSlot *    pSlot,
                           struct ThreadObject * pThread,
                           os_tick               tick);
_IMPORT void insertBlockSlot(struct BlockSlot * pSlot);
_IMPORT void removeBlockSlot(struct BlockSlot * pSlot);
_IMPORT void Block_Lib_Init();
_IMPORT void refreshBlockQ(os_tick target);

#endif /*_BLOCKQ_H_*/
