/*
	@begin
		@type file
		@version 0.0.1
		@brief 
			Just include the strcmp function
		@detail 
			Just include the strcmp function
		@data 2012.12.17
		@author ZhangYan
	@end
*/
#include "string.h"
/*
	@begin
		@type fun
		@brief 
			Compare strings.
		@detail 
		@param s1 string1
		@param s2 string2
		@return 
			0 : string1 == string2<br/>
			>0 : string1 > string2<br/>
			<0: string1< string2
	@end
*/
u32 cmpString(string s1,string s2)
{
	while (*s1 == *s2++)
		if (*s1++ == 0)
			return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)--s2);
}
