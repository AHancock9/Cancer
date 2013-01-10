#ifndef _PRIOBMP_H_
#define _PRIOBMP_H_

/******************************************************
*******************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.24
		@author ZhangYan
		@brief
            The bitmap operations lib
		@detail
	@end
*******************************************************
*******************************************************/

#include "Cancer.h"
#include "cpu.h"


#define BITMAP_SIZE (((CFG_MAX_PRIO-1)/INT_BITS)+1)

/*just support for the 0-127 bits*/
struct PrioBitmap
{
    u32 bits[BITMAP_SIZE];  /*the bits*/
};

void initBitmap(struct PrioBitmap *bmp);
os_prio getPrioHighest(struct PrioBitmap *bmp);
void insertBitmap(os_prio prio,struct PrioBitmap *bmp);
void removeBitmap(os_prio prio,struct PrioBitmap *bmp);

#endif /*_PRIOBMP_H_ */
