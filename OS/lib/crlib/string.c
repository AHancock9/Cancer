/*
	@begin
		@type file
		@version 0.0.1
		@brief 
			This file contains the common string operations
		@detail 
			This file contains the common string operations
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
string catString(string src, string append)
{
	string save = src;
	for (; *src; ++src);
	while ((*src++ = *append++) != '\0');
	return(save);
}