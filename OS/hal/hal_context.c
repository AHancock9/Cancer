
/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2013.1.5
		@author ZhangYan
		@brief
		@detail
	@end
********************************************************
********************************************************/
#include "hal_context.h"

/*******************************************************
********************************************************
	@begin
		@type fun
		@brief
		@detail
		@param
		@return
	@end
********************************************************
********************************************************/
void initContextObject(struct ContextObject * pContext,
                       u32 *                  pStkBase)
{
    init_context(&pContext->context,(u32)pStkBase);
}
