
/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2013.1.8
		@author ZhangYan
		@brief
		@detail
	@end
********************************************************
********************************************************/
#include "hal_init.h"
#include "arch_tick.h"
#include "low_level.h"
#include "arch_exception.h"
#include "hal_int.h"

void Hal_Init()
{
    unsigned long reset_vect;
    unsigned long vec_start = (unsigned long)&_start;
	unsigned long vec_end   = (unsigned long)&_vector_end;
    reset_vect = set_vbar();
    reset_vect = read_vbar();
    /*init the interrupt lib*/
    Hal_Int_Lib_Init();
}
