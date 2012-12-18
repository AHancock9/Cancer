

/*
	@begin
		@type file
		@version 0.0.1
		@brief 
			Just include the strcpy function
		@detail 
			Just include the strcpy function
		@data 2012.12.17
		@author ZhangYan
	@end
*/
#include "string.h"
/*
	@begin
		@type fun
		@brief 
			'strcpy' copys src to dst
		@detail 
			No checking in this function,please MAKE SURE that 
			the size of 'to' must be no less than the size of 'from'
		@param to The target string
		@param from The source string
		@return 
			Return the copied string
	@end
*/
string copyString(string to, string from)
{
	string save = to;
	for (; (*to = *from) != '\0'; ++from, ++to);
	return(save);
}
