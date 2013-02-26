#ifndef _MEM_H_
#define _MEM_H_

/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.17
		@author ZhangYan
		@brief
            Memory common operations lib
		@detail
	@end
********************************************************
********************************************************/

#include "Cancer.h"

/*externs*/
void * setMem(void *src, byte ch, u32 count);
void *copyMem(void *dest, const void *src, u32 count);
void * clearMem(void * dest,u32 count);

#endf /*_MEM_H_*/
