
/*******************************************************
********************************************************
 	@begin
 		@type file
 		@version 0.0.1
 		@date 2012.1225
 		@author ZhangYan
 		@brief
            Interruption handled in HAL level
 		@detail
    @end
********************************************************
********************************************************/

#include "Cancer.h"
#include "interrupt.h"
#include "hal_int.h"
#include "arch_tick.h"
#include "low_level.h"
#include "arch_exception.h"


/*externs*/

/*******************************************************
********************************************************
	@begin
		@type fun
		@brief
		@detail
		@param
		@return
	@end
********************************************************
********************************************************/
void Hal_Int_Lib_Init()
{
    vic_init();
    setup_system_tick();
}
/*******************************************************
********************************************************
	@begin
		@type fun
		@brief
		@detail
		@param
		@return
	@end
********************************************************
********************************************************/
void Hal_Interrupt_Entry(u32 vector)
{
    /*push the interrupt into kernel*/
    Kernel_Interrupt_Entry(INT_TICK_VECTOR);
}
