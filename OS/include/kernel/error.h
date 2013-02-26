#ifndef _ERROR_H_
#define _ERROR_H_

/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2013.1.9
		@author ZhangYan
		@brief
            Error lib.
		@detail
	@end
********************************************************
********************************************************/

#define  MAX_ERROR_CODE
/*error code infine*/

#define ERROR                   (-1)
#define OK                        0
#define ERR_INVALID_TID           1
#define ERR_INVALID_OPT           2

#if CFG_ERROR_EN >0

_IMPORT string * GetErrorString(os_status errorCode);

#endif /*CFG_ERROR_EN>0*/

#endif /*_ERROR_H_*/
