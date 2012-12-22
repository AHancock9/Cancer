#include "wheellist.h"

/*
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.18
		@brief
			This file contains the common operations in wheellist structure
		@author ZhangYan
	@end
*/

/*
	@begin
		@type fun
		@brief
			Init the WheelList structure,that will depend on</br>
			the WHEEL_LIST_MAX macro
		@param pWheelList the target WheelList to init
	@end
*/
void initWheelList(struct WheelList * pWheelList)
{
	u32 i;
	for(i=0;i<WHEEL_LIST_MAX;i++)
	{
		initWheelSpoke(pWheelList->spokes + i);
	}
}

/*
	@begin
		@type fun
		@brief
			Add a new wheel node into the wheel list
		@detail
			This function ensures that the node can always be inserted into
			the wheel list</br>But you should make sure the target value of
			WheelNode must != 0
		@param pInsertNode The node to be inserted
		@param pWheelList Where to be inserted into
	@end
*/
void addWheelNode(struct WheelNode * pInsertNode,
			struct WheelList * pWheelList)
{
	u32 target = pInsertNode->target;
	u32 spokeIndex = target % WHEEL_LIST_MAX;
	struct WheelSpoke * pSpoke = pWheelList->spokes+spokeIndex;
	if(isHashHeadEmpty(&pSpoke->tHashHead))
	{
		addHashNode(&pInsertNode->tHashNode,&pSpoke->tHashHead);
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
			addList(&pInsertNode->tListHead,&pNode->tListHead);
			return;
		}
		else if(target < pNode->target)
		{
			pSpoke->nodeCounter++;
			addHashNodeBefore(&pInsertNode->tHashNode,&pNode->tHashNode);
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

/*
	@begin
		@type fun
		@brief
			Pick the WheelNode depend on the target value.
		@detail

		@param target The unsigned int value which used as the target
		@return
			NULL: if no node found </br>
			!=NULL : the WheelNode structure pointer
	@end
*/
struct WheelNode * pickWheelNode(u32 target,struct WheelList * pWheelList)
{
	u32 spokeIndex = target % WHEEL_LIST_MAX;
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
