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
#include "blockQ.h"

/*privates*/

static struct WheelList blockWheelList[MAX_CPU];

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
void Block_Lib_Init()
{
    u32 i;
    for(i=0;i<MAX_CPU;i++)
    {
        initWheelList(&blockWheelList[i]);
    }
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
void initBlockSlot(struct BlockSlot *    pSlot ,
                   struct ThreadObject * pThread,
                   os_tick               tick)
{
    initWheelNode(&pSlot->tWheelNode,tick);
    pSlot->pThread = pThread;
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
void insertBlockSlot(struct BlockSlot * pSlot)
{
    struct WheelList * pWheelList = &blockWheelList[current_cpu];
    insertWheelNode(&pSlot->tWheelNode,pWheelList);
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
void removeBlockSlot(struct BlockSlot * pSlot)
{
    struct WheelList * pWheelList = &blockWheelList[current_cpu];
    removeWheelNode(&pSlot->tWheelNode,pWheelList);
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
void refreshBlockQ(os_tick target)
{
    struct WheelList * pWheelList = &blockWheelList[current_cpu];
    struct WheelNode * node = pickWheelNode(target,pWheelList);
    //DEBUG_PRINTF("target:%lld\n",target);
    if(node == NULL)
    {
        return ;
    }
    //DEBUG_PUTS("delay ok\n");
    struct WheelNode * tmp;
    struct BlockSlot *slot;
    /*insert first*/
    slot= wListNode_entry(node,struct BlockSlot,tWheelNode);
    //DEBUG_PRINTF("insert 0x%x:\n",slot->pThread);
    insertPrioQ(slot->pThread,OPT_PRIO_Q_FIRST);
    /*foreach wheelnode*/
    list_for_each_entry(tmp,&node->tListHead,tListHead)
    {
        slot= wListNode_entry(tmp,struct BlockSlot,tWheelNode);
        //DEBUG_PRINTF("insert 0x%x:\n",slot->pThread);
        insertPrioQ(slot->pThread,OPT_PRIO_Q_FIRST);
    }
}
