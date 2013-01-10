
/******************************************************
*******************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.18
		@author ZhangYan
		@detail
            The WheelList structer and its operations
		@brief
			This file contains the common operations in
			wheellist structure

	@end
*******************************************************
*******************************************************/
#include "wheellist.h"

/*publics*/

/******************************************************
*******************************************************
	@begin
		@type fun
		@brief
			Init the WheelList structure,that will depend
			on</br>the WHEEL_LIST_MAX macro
		@param [pWheelList]
                the target WheelList to init
	@end
*******************************************************
*******************************************************/
void initWheelList(struct WheelList * pWheelList)
{
	u32 i;
	for(i=0;i<CFG_WHEEL_LIST_MAX;i++)
	{
		initWheelSpoke(pWheelList->spokes + i);
	}
}
/******************************************************
*******************************************************
	@begin
		@type fun
		@brief
			Add a new wheel node into the wheel list
		@detail
			This function ensures that the node can
			always be inserted intothe wheel list</br>
            BUT you should make sure the target value
            of WheelNode must != 0
		@param [pInsertNode]
                The node to be inserted
		@param [pWheelList]
                Where to be inserted into
        @return
	@end
*******************************************************
*******************************************************/
void insertWheelNode(struct WheelNode * pInsertNode,
                     struct WheelList * pWheelList)
{
	os_tick target = pInsertNode->target;
	u32 spokeIndex = target % CFG_WHEEL_LIST_MAX;
	struct WheelSpoke * pSpoke = pWheelList->spokes+spokeIndex;
	if(isHashHeadEmpty(&pSpoke->tHashHead))
	{
		addHashNode(&pInsertNode->tHashNode,
                    &pSpoke->tHashHead);
		pSpoke->nodeCounter++;
		return ;
	}
	struct WheelNode * pNode;
	struct HashListNode * pTmp;

	/*that will be O(n)*/
	hlist_for_each_entry(pNode,pTmp,&pSpoke->tHashHead,tHashNode)
	{
		if(target == pNode->target)
		{
			addList(&pInsertNode->tListHead,
                    &pNode->tListHead);
			return;
		}
		else if(target < pNode->target)
		{
			pSpoke->nodeCounter++;
			addHashNodeBefore(&pInsertNode->tHashNode,
                              &pNode->tHashNode);
			return;
		}
		else
		{
			continue;
		}
	}
	pSpoke->nodeCounter++;
	addHashNodeAfter(&pInsertNode->tHashNode,&pNode->tHashNode);
}

/******************************************************
*******************************************************
	@begin
		@type fun
		@brief
			Pick the WheelNode depend on the target value.
		@detail

		@param [target]
                The unsigned int value which used as the target
		@return
			NULL: if no node found </br>
			!=NULL : the WheelNode structure pointer
	@end
*******************************************************
*******************************************************/
struct WheelNode * pickWheelNode(os_tick                target,
                                 struct WheelList * pWheelList)
{
	os_tick spokeIndex = target % CFG_WHEEL_LIST_MAX;
	struct WheelSpoke * spoke = pWheelList->spokes + spokeIndex;
	if(spoke->tHashHead.pFirst != NULL)
	{
		struct WheelNode * pNode;
		pNode = trnsHNode2WNode(spoke->tHashHead.pFirst);
		if(target == pNode->target)
		{
			deleteHashNode(&pNode->tHashNode);
			spoke->nodeCounter--;
			return pNode;
		}
		else
		{
			return NULL;
		}
	}
	return NULL;
}

/******************************************************
*******************************************************
	@begin
		@type fun
		@brief
            Remove a node from wheellist
		@detail

		@param [pNode]
                the node to be removed
		@param [pWheelList]
                the list we remove from
		@return
	@end
*******************************************************
*******************************************************/
void removeWheelNode(struct WheelNode * pNode,
                     struct WheelList * pWheelList)
{
    /*if this node is not hashed in hashlist*/
    if(!isNodeHashed(&pNode->tHashNode))
    {
        if(!isListEmpty(&pNode->tListHead))
        {
            deleteList(&pNode->tListHead);
        }
        return ;
    }
    /*this node is a hash node*/
    u32 target = pNode->target;
    u32 spokeIndex = target % CFG_WHEEL_LIST_MAX;
    struct WheelSpoke *pSpoke = &pWheelList->spokes[spokeIndex];

    /*we have the same target list linked on node*/

    if(!isListEmpty(&pNode->tListHead))
    {
        struct WheelNode * pNodeNext =
                trnsLHead2WNode(pNode->tListHead.pNext);
        deleteHashNode(&pNode->tHashNode);
        deleteList(&pNode->tListHead);
        insertWheelNode(pNodeNext,pWheelList);
    }
    else
    {
        deleteHashNode(&pNode->tHashNode);
        pSpoke->nodeCounter--;
    }
}
