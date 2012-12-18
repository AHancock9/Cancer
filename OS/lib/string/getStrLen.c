/*
	@begin
		@type file
		@version 0.0.1
		@brief 
			Just include the strcat function
		@detail 
			Just include the strcat function
		@date 2012.12.17
		@author ZhangYan
	@end
*/
#include "string.h"
/*
	@begin
		@type fun
		@brief 
			append string1 to string2
		@detail 
		@param src The source  string
		@param append The string appended to source string
		@return 
			Return the needed string
	@end
*/
u32 getStrLen(string str)
{
	const char *s;
	for (s = str; *s; ++s);
	return (s - str);
}

