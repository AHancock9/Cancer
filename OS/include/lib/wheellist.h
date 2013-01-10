#ifndef _WHEELLIST_H_
#define _WHEELLIST_H_

/******************************************************
*******************************************************
	@begin
		@type file
		@version 0.0.1
		@author ZhangYan
		@date 2012.12.18
		@brief
			This files contains the wheel list struecture
			and this is its .h file
		@detail
			This structrue is useful in kernel programming.
			that implements the simple hashtable</br>
			It may used in timer or task delay queue.you can
			also use it as your own structure.
	@end
*******************************************************
*******************************************************/

#include "Cancer.h"
#include "list.h"
#include "hashlist.h"


#define wListNode_entry(ptr,type,member) \
                        container_of(ptr,type,member)

struct WheelNode
{
	struct HashListNode tHashNode;
	struct ListHead     tListHead;  /*the same target node
                                        linked as double list*/
    os_tick             target;     /*the target of being picked off*/
};

struct WheelSpoke
{
	struct HashListHead tHashHead;
	u32                 nodeCounter;
};

struct WheelList
{
	struct WheelSpoke spokes[CFG_WHEEL_LIST_MAX] ;
};

static inline void initWheelNode(struct WheelNode * pNode,
                                 os_tick            tick)
{
	initHashListNode(&pNode->tHashNode);
	pNode->target =tick;
	initListHead(&pNode->tListHead);
}

static inline void initWheelSpoke(struct WheelSpoke * pSpoke)
{
	initHashListHead(&pSpoke->tHashHead);
	pSpoke->nodeCounter = 0;
}

static inline struct WheelNode * trnsHNode2WNode(struct HashListNode * pHashNode)
{
	return hlist_entry(pHashNode,struct WheelNode,tHashNode);
}

static inline struct WheelNode * trnsLHead2WNode(struct ListHead * pListHead)
{
    return list_head_entry(pListHead,struct WheelNode,tListHead);
}

/*externs*/
_IMPORT void initWheelList(struct WheelList * pWheelList);

_IMPORT void insertWheelNode(struct WheelNode * pNode,
                             struct WheelList * pWheelList);

_IMPORT struct WheelNode * pickWheelNode(os_tick            target,
                                         struct WheelList * pWheelList);

_IMPORT void removeWheelNode(struct WheelNode * pNode,
                             struct WheelList * pWheelList);

#endif /*_WHEELLIST_H_*/
