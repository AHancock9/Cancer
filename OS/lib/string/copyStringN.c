
/*
	@begin
		@type file
		@version 0.0.1
		@brief 
			Just include the strncpy function
		@detail 
			Just include the strncpy function
		@date 2012.12.17
		@author ZhangYan
	@end
*/
#include "string.h"
/*
	@begin
		@type fun
		@brief 
			Copy src to dst, truncating or null-padding to always copy n bytes
		@detail 
		@param to The target string
		@param from The source string
		@return 
			Return the copied string
	@end
*/
string copyStringN(string dst, string src, u32 n)
{
	if (n != 0) {
		char * d = dst;
		const char * s = src;
		do {
			if ((*d++ = *s++) == 0) {
				/* NUL pad the remaining n-1 bytes */
				while (--n != 0)
					*d++ = 0;
				break;
			}
		} while (--n != 0);
	}
	return (dst);
}
