#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_
/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.23
		@author ZhangYan
		@brief
		@detail
	@end
********************************************************
********************************************************/
#include "Cancer.h"

/*******************************************************
********************************************************
	@begin
		@type struct
		@brief
		@detail
	@end
********************************************************
********************************************************/
struct Semaphore
{
    struct PendObject tPendObject; /*the pend object*/
    sem_ctr           ctr;         /*the valid resource counter*/
};

/*externs*/
_IMPORT bool createSemaphore(struct Semaphore * pSem,
                            string name,
                            sem_ctr ctr);
_IMPORT bool takeSemaphore(struct Semaphore * pSem,u32 timeout_ms);
_IMPORT bool giveSemaphore(struct Semaphore * pSem,os_option option);
_IMPORT bool trySemaphore(struct Semaphore * pSem);
_IMPORT bool setSemaphore(struct Semaphore * pSem , sem_ctr ctr);
_IMPORT bool abortSemaphore(struct Semaphore * pSem, os_option option);
_IMPORT bool deleteSemaphore(struct Semaphore * pSem, pend_opt option);




#endif /*_SEMAPHORE_H_*/
