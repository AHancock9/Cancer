#ifndef _LIST_H_
#define _LIST_H_

/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.17
		@brief
			This file contains the common structure and
			operations in kernel programming</br>
		@author ZhangYan
	@end
********************************************************
********************************************************/

#include "Cancer.h"

/*the define operations we need*/
#define list_head_entry(ptr, type, member) \
	container_of(ptr, type, member)

#define list_for_each(pos, head) \
	for (pos = (head)->pNext; pos != (head);pos = pos->pNext)

#define list_for_each_entry(pos, head, member)				\
	for (pos = list_head_entry((head)->pNext, typeof(*pos), member);	\
	     &pos->member != (head); 	\
	     pos = list_head_entry(pos->member.pNext, typeof(*pos), member))

/*the structures we need*/
struct ListHead
{
	struct ListHead * pNext, *pPrev;
};

/*the inline operations we need*/
static inline void initListHead(struct ListHead * ptr)
{
	ptr->pNext = ptr;
	ptr->pPrev = ptr;
}

static inline void add_list(struct ListHead *new,
			      struct ListHead *prev,
			      struct ListHead *next)
{
	next->pPrev = new;
	new->pNext = next;
	new->pPrev = prev;
	prev->pNext = new;
}

static inline void addList2Tail(struct ListHead *new, struct ListHead *head)
{
	add_list(new, head->pPrev, head);
}

static inline void addList(struct ListHead *new, struct ListHead *head)
{
	add_list(new, head, head->pNext);
}

static inline void delete_list(struct ListHead * prev, struct ListHead * next)
{
	next->pPrev = prev;
	prev->pNext = next;
}

static inline void deleteList(struct ListHead *entry)
{
	delete_list(entry->pPrev, entry->pNext);
	initListHead(entry);
}

static inline bool isListEmpty(const struct ListHead *head)
{
	return head->pNext == head;
}

#endif /*_LIST_H_*/
