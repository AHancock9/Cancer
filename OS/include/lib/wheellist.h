#ifndef _WHEELLIST_H_
#define _WHEELLIST_H_

#include "Cancer.h"
#include "list.h"
/*
	@begin
		@type file
		@version 0.0.1
		@author ZhangYan
		@date 2012.12.18
		@brief
			This files contains the wheel list struecture
			and this is its .h file
		@detail
			Wheel list structrue is useful in kernel programming.
			that implements the simple hashtable</br>
			It may used in timer and task delay queue or you can
			use it as your own structure.

	@end
*/
#define WHEEL_LIST_MAX 20

#define wListNode_entry(ptr,type,member) container_of(ptr,type,member)

struct WheelNode
{
	struct HashListNode tHashNode;
	struct ListHead tListHead;  /*the same target node
								linked as double list*/
	u32 target;
};

struct WheelSpoke
{
	struct HashListHead tHashHead;
	u32 nodeCounter;
};

struct WheelList
{
	struct WheelSpoke spokes[WHEEL_LIST_MAX] ;
};

static inline void initWheelNode(struct WheelNode * pNode)
{
	initHashListNode(&pNode->tHashNode);
	pNode->target =0;
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

void initWheelList(struct WheelList * pWheelList);
void addWheelNode(struct WheelNode * pNode,struct WheelList * pWheelList);
struct WheelNode * pickWheelNode(u32 target,struct WheelList * pWheelList);

#endif /*_WHEELLIST_H_*/
