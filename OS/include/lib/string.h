#ifndef _STRING_H_
#define _STRING_H_

#include "ktype.h"
extern string copyStringN(string dst, string src, u32 n);
extern string catString(string src, string append);
extern string copyString(string s1, string s2);
extern u32 getStrLen(string str);
extern u32 cmpString(string s1 , string s2);
#endif /* _STRING_H_ */
