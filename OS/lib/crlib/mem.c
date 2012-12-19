/*
	@begin
		@type file
		@version 0.0.1
		@brief 
			This file just contains the common memory operations
		@detail 
			This file just contains the common memory operations
		@date 2012.12.17
		@author ZhangYan
	@end
*/
#include "mem.h"
 /*
	@begin
		@type fun
		@brief 
			Fill a region of memory with the given value
		@detail 
			Fill a region of memory with the given value
		@param dest Pointer to the start of the area.
		@param src The byte to fill the area with
		@param count The size of the area.
		@return 
			Return the needed memory address with void *
	@end
*/
void * setMem(void *src, byte ch, u32 count)
{
	char *pTmp = src;
	while (count--)
		*pTmp++ = ch;
	return src;
}
 /*
	@begin
		@type fun
		@brief 
			Copy one area of memory to another
		@detail 
			Copy one area of memory to another
		@param dest Where to copy to
		@param src Where to copy from
		@param count The size of the area.
		@return 
			Return the needed memory address with void *
	@end
*/
void * copyMem(void *dest, const void *src, u32 count)
{
	char *pTmp = dest;
	const char *pStr = src;
	while (count--)
		*pTmp++ = *pStr++;
	return dest;
}
/*
	@begin
		@type fun
		@brief 
			Clear the memory area to 0
		@detail 
			Clear the memory area to 0
		@param dest Where to clear
		@param count The size of the area.
		@return 
			Return the needed memory address with void *
	@end
*/
void * clearMem(void * dest,u32 count)
{
	return setMem(dest,0,count);
}