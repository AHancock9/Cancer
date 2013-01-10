#ifndef _HALINT_H_
#define _HALINT_H_

/*
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.21
		@author ZhangYan
		@brief
            Interupt handler in HAL level
		@detail
	@end
*/
#define INT_TICK_VECTOR 0

_IMPORT void Hal_Interrupt_Entry();
_IMPORT void Hal_Int_Lib_Init();

#endif /*_HALINT_H_*/
