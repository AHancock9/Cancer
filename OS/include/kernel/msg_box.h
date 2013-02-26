#ifndef _MSG_BOX_H_
#define _MSG_BOX_H_

#if CFG_MSG_BOX_EN >0

/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date
		@author ZhangYan
		@brief
		@detail
	@end
********************************************************
********************************************************/
#include "Cancer.h"

struct MessageBox
{
    struct PendObject tPendObject;
};

#endif /*CFG_MSG_BOX_EN*/

#endif /*_MSG_BOX_H_*/
