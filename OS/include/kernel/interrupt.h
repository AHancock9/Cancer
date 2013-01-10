#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_
/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.21
		@author ZhangYan
		@brief
            Interupt handle in kernel level
		@detail
	@end
********************************************************
********************************************************/
#include "Cancer.h"
#include "tick.h"
#include "low_level.h"

/*defines wrapped for kernel used*/
#define enableLocalInt() enable_interrupt()
#define disableLocalInt() disable_interrupt()


struct IntObjcet
{
    os_vector    vector; /*the vector*/
    Int_entryPtr entry;  /*interruption handler*/
    void *       pArg;   /*the argument for entry function */
};


/*externs*/
_IMPORT bool isIntContext();
_IMPORT void Kernel_Interrupt_Entry(os_vector vector);
_IMPORT void Int_Lib_Init();
_IMPORT bool connectIntObj(struct IntObjcet* pIntObject);
_IMPORT void initIntObject(struct IntObjcet* pIntObject,
                          Int_entryPtr pEntry,
                          void * pArg,
                          os_vector vector);
#endif /*_INTERRUPT_H_*/
