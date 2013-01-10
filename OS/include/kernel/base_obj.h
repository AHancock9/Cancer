#ifndef _BASE_OBJ_H_
#define _BASE_OBJ_H_

/*
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.24
		@author ZhangYan
		@brief
            The BaseObject.All kernel object should
            extend from this object.
		@detail
            We use this base object to manage all
            objects in kernel uniformly.
	@end
*/
#include "Cancer.h"


#define OBJ_NULL (obj_type)0
#define OBJ_THREAD (obj_type)1
#define OBJ_TYPE_MAX 2;


struct BaseObject
{
    obj_type objType; /*the type of object*/
};

#endif /*_BASE_OBJ_H_*/
