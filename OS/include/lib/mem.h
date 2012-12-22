#ifndef _MEM_H_
#define _MEM_H_
#include "Cancer.h"

void * setMem(void *src, byte ch, u32 count);
void *copyMem(void *dest, const void *src, u32 count);
void * clearMem(void * dest,u32 count);
#endf /*_MEM_H_*/