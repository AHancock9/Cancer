/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2013.1.9
		@author ZhangYan
		@brief
		@detail
	@end
********************************************************
********************************************************/
#include "error.h"

#if CFG_ERROR_EN >0

_LOCAL string errorStrings[] =
{
    /*common strings*/
    "STATUS: ERROR\n",
    "STATUS: OK\n",
    "STATUS: Invalid Thread ID\n",
    "STATUS: Invalid Option(s)\n"
};

/*******************************************************
********************************************************
	@begin
		@type fun
		@brief
            Get error string using error code
		@detail
		@param [[errorCode] error code
		@return
            if NULL errorCode does NOT exist.
	@end
********************************************************
********************************************************/
_API string * GetErrorString(os_status errorCode)
{
    if(errorCode>0 && errorCode<MAX_ERROR_CODE)
    {
        return &errorStrings[errorCode];
    }
    else if(errorCode==-1)
    {
        return &errorStrings[0]
    }
    else
    {
        return NULL;
    }
}

#endif /*CFG_ERROR_EN>0*/
