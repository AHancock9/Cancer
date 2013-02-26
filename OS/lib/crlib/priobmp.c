
/******************************************************
*******************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.24
		@author ZhangYan
		@brief
		@detail
	@end
*******************************************************
*******************************************************/
#include "priobmp.h"


/*privates*/

_LOCAL const u8 leadZerosTbl[256] = {
/*   0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F   */
    8u,  7u,  6u,  6u,  5u,  5u,  5u,  5u,  4u,  4u,  4u,  4u,  4u,  4u,  4u,  4u,  /*   0x00 to 0x0F                   */
    3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  /*   0x10 to 0x1F                   */
    2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  /*   0x20 to 0x2F                   */
    2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  /*   0x30 to 0x3F                   */
    1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  /*   0x40 to 0x4F                   */
    1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  /*   0x50 to 0x5F                   */
    1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  /*   0x60 to 0x6F                   */
    1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  /*   0x70 to 0x7F                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0x80 to 0x8F                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0x90 to 0x9F                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0xA0 to 0xAF                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0xB0 to 0xBF                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0xC0 to 0xCF                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0xD0 to 0xDF                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0xE0 to 0xEF                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u   /*   0xF0 to 0xFF                   */
};

_LOCAL u32 count_lead_zeros(u32 val)
{
    u8 ix;
    u32 leadZeros;
    if (val > 0x0000FFFF)
    {
        if (val > 0x00FFFFFF)
        {
            ix = (u8)(val >> 24);
            leadZeros = (u32)(leadZerosTbl[ix] +  0);
        }
        else
        {
            ix = (u8)(val >> 16);
            leadZeros = (u32)(leadZerosTbl[ix] +  8);
        }
    }
    else
    {
        if (val > 0x000000FF)
        {
             ix = (u8)(val >>  8);
             leadZeros = (u32)(leadZerosTbl[ix] + 16);
        }
        else
        {
            ix = (u8)(val >>  0);
            leadZeros = (u32)(leadZerosTbl[ix] + 24);
        }
    }
    return leadZeros;
}

/*externs*/

/*******************************************************
********************************************************
	@begin
		@type fun
		@brief
			Init a bitmap structure.
		@detail
		@param [bmp]
                The PrioBitmap to be inititalized
    @end
********************************************************
********************************************************/
void initBitmap(struct PrioBitmap *bmp)
{
     u32 i;
     for(i = 0; i < BITMAP_SIZE; i++)
     {
         bmp->bits[i] = 0;
     }
}

/*******************************************************
********************************************************
	@begin
		@type fun
		@brief
            Get the highest priority in bitmap
		@detail

		@param [bmp]
                Where to get
		@return
            The hightest priority
	@end
********************************************************
********************************************************/
os_prio getPrioHighest(struct PrioBitmap *bmp)
{
    u32  *p_tbl;
    os_prio prio;
    prio = 0;
    p_tbl = &bmp->bits[0];
    while(*p_tbl == 0)
    {
        prio += INT_BITS;
        p_tbl++;
    }

#if CFG_CPU_LEAD_ZEROS_EN >0
    prio += (os_prio)countLeadZeros(*p_tbl);
#else
    prio += (os_prio)count_lead_zeros(*p_tbl);
#endif
    return prio;

}
/*******************************************************
********************************************************
	@begin
		@type fun
		@brief
			Insert a priority into  PrioBitmap structure
		@detail

		@param [prio]
                What to insert
        @param [bmp]
                Where to insert
		@return
	@end
********************************************************
********************************************************/
void insertBitmap(os_prio prio,struct PrioBitmap *bmp)
{
    u32  bit;
    u32  bit_nbr;
    os_prio ix;
    ix  = prio / INT_BITS;
    bit_nbr = (u32)prio & (INT_BITS - 1);
    bit = 1;
    bit <<= (INT_BITS - 1) - bit_nbr;
    bmp->bits[ix] |= bit;
}
/*******************************************************
********************************************************
	@begin
		@type fun
		@brief
			Remove a priority from PrioBitmap structer
		@detail

		@param [prio]
                What to remove
        @param [bmp]
                Where to remove
		@return
	@end
********************************************************
********************************************************/
void removeBitmap(os_prio prio,struct PrioBitmap *bmp)
{
    u32  bit;
    u32  bit_nbr;
    os_prio   ix;
    ix  = prio / INT_BITS;
    bit_nbr = (u32)prio & (INT_BITS - 1u);
    bit = 1u;
    bit <<= (INT_BITS - 1u) - bit_nbr;
    bmp->bits[ix] &= ~bit;
}
