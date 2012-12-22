#ifndef _STRING_H_
#define _STRING_H_

/*
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.17
		@brief the .h file of string operations lib
		@author ZhangYan
	@end
*/
#include "Cancer.h"

extern string copyStringN(string dst, string src, u32 n);
extern string catString(string src, string append);
extern string copyString(string to, string from);
extern u32 getStrLen(string str);
extern u32 cmpString(string s1 , string s2);
#endif /* _STRING_H_ */
