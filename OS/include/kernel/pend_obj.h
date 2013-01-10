#ifndef _PEND_OBJ_H_
#define _PEND_OBJ_H_

/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.23
		@author ZhangYan
		@brief
		@detail
	@end
********************************************************
********************************************************/

#include "Cancer.h"

/*******************************************************
********************************************************
	@begin
		@type struct
		@brief

		@detail
             Each thread has its own penddata(s)
	@end
********************************************************
********************************************************/
struct PendData
{

};
/*******************************************************
********************************************************
	@begin
		@type struct
		@brief
			Each object which can be pended should
            extend PendOjbect
		@detail
	@end
********************************************************
********************************************************/
struct PendObject
{
    struct BaseObject tBaseObject;  /*base object*/
    struct PendData * pendList;     /*the list of pend data*/
};


#endif /*_PEND_OBJ_H_*/
