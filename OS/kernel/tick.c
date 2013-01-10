/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.21
		@author ZhangYan
		@brief
            Tick interupt handler in real-time bottom half
		@detail
	@end
********************************************************
********************************************************/
#include "tick.h"
#include "interrupt.h"
/*private*/
_LOCAL os_tick globalTick;/*the global tick each cpu maintains*/
_LOCAL os_tick privateTick[MAX_CPU]; /*the priavate tick counter*/
_LOCAL struct IntObjcet tickIntObject; /*tick interruption object*/

/*******************************************************
********************************************************
	@begin
		@type fun
		@brief
			Kernel handler of tick interruption.
		@detail
		@param
		@return
	@end
********************************************************
********************************************************/
_LOCAL void Tick_Kernel_Entry(void * ptr)
{
    /*take the spinlock*/
    globalTick++;
    /*give the spinlock*/
    /*insert rtbf thread into the ready queue*/
    //DEBUG_PRINTF("tick%d\n",globalTick);
    disableLocalInt();
    insertPrioQ(getRtbfThread(),OPT_PRIO_Q_FIRST);
    enableLocalInt();
}

/*publics*/

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
void incPrivateTick()
{
    privateTick[current_cpu]++;
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
os_tick getPrivateTick()
{
    return privateTick[current_cpu];
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
void Tick_Lib_Init()
{
    int i=0;
    initIntObject(&tickIntObject,Tick_Kernel_Entry,0,0);
    globalTick = 0;
    for(;i<MAX_CPU;i++)
    {
        privateTick[i] = 0;
    }
    /*set up the tick interruption object*/
    connectIntObj(&tickIntObject);
}
