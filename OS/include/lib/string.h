#ifndef _STRING_H_
#define _STRING_H_

/******************************************************
*******************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.17
		@brief
            the .h file of string operations lib
		@author ZhangYan
	@end
*******************************************************
*******************************************************/
#include "Cancer.h"


/*externs*/

_IMPORT string copyStringN(string dst, string src, u32 n);
_IMPORT string catString(string src, string append);
_IMPORT string copyString(string to, string from);
_IMPORT u32    getStrLen(string str);
_IMPORT u32    cmpString(string s1 , string s2);


#endif /* _STRING_H_ */
