/*
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.21
		@author ZhangYan
		@brief
            Interupt handling in kernel level
		@detail
	@end
*/
#include "interrupt.h"
/*privates*/
_LOCAL u32 intNestingCtr;
_LOCAL struct IntObjcet *intTable[1];

_LOCAL void intExit()
{
    intNestingCtr--;
}
_LOCAL void intEnter()
{
    intNestingCtr++;
}

/*
	@begin
		@type fun
		@brief
			The interrupt handler
		@detail
		@param
		@return
	@end
*/
void Kernel_Interrupt_Entry(os_vector vector)
{
    if(!isOSStart())
    {
        return ;
    }
    intEnter();
    intTable[0]->entry(intTable[0]->pArg);
    intExit();
}
/*
	@begin
		@type fun
		@brief
			The initializer of interrupt lib
		@detail
	@end
*/
void Int_Lib_Init()
{
    intNestingCtr = 0;
    /*init tick lib*/
    Tick_Lib_Init();
}
/*
	@begin
		@type fun
		@brief
			Set up a interruption object in the global int-table
		@detail
		@param
		@return
	@end
*/
bool connectIntObj(struct IntObjcet* pIntObject)
{
    os_vector vector = pIntObject->vector;
    intTable[vector] = pIntObject;
    return false;
}
void initIntObject(struct IntObjcet* pIntObject,
                Int_entryPtr pEntry,void * pArg,
                os_vector vector)
{
    pIntObject->entry = pEntry;;
    pIntObject->vector = vector;
    pIntObject->pArg = pArg;
}
bool isIntContext()
{
    return intNestingCtr > 0;
}
