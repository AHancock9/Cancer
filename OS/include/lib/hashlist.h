#ifndef _HASHLIST_H_
#define _HASHLIST_H_

/*******************************************************
********************************************************
	@begin
		@type file
		@date 2012.12.17
		@author ZhangYan
		@version 0.0.1
		@brief
			This file contains the hash list structure
			and the operations we need
	@end
********************************************************
********************************************************/
#include "Cancer.h"

/*the define operations we need */

#define hlist_entry(ptr, type, member) container_of(ptr,type,member)

#define hlist_for_each(pos, head) \
	for (pos = (head)->pFirst; pos; pos = pos->pNext)

#define hlist_for_each_entry(tpos, pos, head, member)			 \
	for (pos = (head)->pFirst;					 \
	     pos &&	({ tpos = hlist_entry(pos, typeof(*tpos), member); 1;}); \
	     pos = pos->pNext)

/*the structures we need */
struct HashListHead
{
	struct HashListNode *pFirst;
};
struct HashListNode
{
	struct HashListNode *pNext, **pPrevn;
};

/*inline operations we need*/

static inline void initHashListHead(struct HashListHead *head)
{
	head->pFirst = NULL;
}
static inline void initHashListNode(struct HashListNode *node)
{
	node->pNext = NULL;
	node->pPrevn = NULL;
}

static inline bool isNodeHashed(const struct HashListNode *h)
{
	return !(h->pPrevn == NULL);
}

static inline bool isHashHeadEmpty(const struct HashListHead *h)
{
	return (h->pFirst==NULL);
}

static inline void delete_hash_node(struct HashListNode *node)
{
	struct HashListNode *next = node->pNext;
	struct HashListNode **pprevn = node->pPrevn;
	*pprevn = next;
	if (next)
		next->pPrevn = pprevn;
}

static inline void deleteHashNode(struct HashListNode *node)
{
	delete_hash_node(node);
	initHashListNode(node);
}
static inline void addHashNode(struct HashListNode *node,
					struct HashListHead *head)
{
	struct HashListNode *pFirst = head->pFirst;
	node->pNext = pFirst;
	if (pFirst)
		pFirst->pPrevn = &node->pNext;
	head->pFirst = node;
	node->pPrevn = &head->pFirst;
}

/* next must be != NULL */
static inline void addHashNodeBefore(struct HashListNode *new,
					struct HashListNode *next)
{
	new->pPrevn = next->pPrevn;
	new->pNext = next;
	next->pPrevn = &new->pNext;
	*(new->pPrevn) = new;
}

static inline void addHashNodeAfter(struct HashListNode *new,
					struct HashListNode *next)
{
	new->pNext = next->pNext;
	next->pNext = new;
	new->pPrevn = &next->pNext;
	if(new->pNext)
		new->pNext->pPrevn  = &next->pNext;
}

#endif /*_HASHLIST_H_*/
