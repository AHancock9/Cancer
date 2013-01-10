
/*
	@begin
		@type file
		@version 0.0.1
		@date 2013.1.5
		@author ZhangYan
		@brief
		@detail
	@end
*/
#include "kernel.h"


/*globals*/
_LOCAL bool isCancerRunning;

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
bool isOSStart()
{
    return isCancerRunning;
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
void setCancerStart(bool flag)
{
    isCancerRunning = flag;
}
