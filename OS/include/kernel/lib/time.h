#ifndef _TIME_H_
#define _TIME_H_

#if CFG_RTC_EN>0
/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.21
		@author ZhangYan
		@brief
            This file is about time concept in real world
		@detail
	@end
********************************************************
********************************************************/
#include "Cancer.h"

typedef u64 time_t; /*The time in second since midnight Jan 1, 1970*/

#define SECS_PER_MIN      60	/* Seconds per minute */
#define MINS_PER_HOUR     60	/* minutes per hour */
#define HOURS_PER_DAY     24	/* hours per day */
#define DAYS_PER_WEEK     7	/* days per week */
#define MONS_PER_YEAR     12	/* months per year */
#define SECS_PER_HOUR     (SECS_PER_MIN * MINS_PER_HOUR)
#define SECS_PER_DAY      ((s32) SECS_PER_HOUR * HOURS_PER_DAY)

#define DAYS_PER_YEAR  	365	/* days per non-leap year */

#define YEARS_PER_CENTURY	  100 /* years per century */

#define TM_THURSDAY	4	/* Thursday is the fourth day of the week */
#define TM_SUNDAY	0	/* Sunday is the zeroth day of the week */
#define TM_MONDAY	1	/* Monday is the first day of the week */

#define EPOCH_WDAY      TM_THURSDAY
#define EPOCH_YEAR      1970
#define TM_YEAR_BASE    1900	/* There is NO NEED to change this define */
				/* after the year 2000! */
#define isleap(y) ((((y) % 4) == 0 && ((y) % 100) != 0) || ((y) % 400) == 0)

typedef struct { long quot, rem; } ldiv_t;

struct tm
{
	u32 tm_sec;	/* seconds after the minute	- [0, 59] */
	u32 tm_min;	/* minutes after the hour	- [0, 59] */
    u32 tm_hour;	/* hours after midnight		- [0, 23] */
	u32 tm_mday;	/* day of the month		- [1, 31] */
	u32 tm_mon;	/* months since January		- [0, 11] */
	u32 tm_year;	/* years since 1900	*/
	u32 tm_wday;	/* days since Sunday		- [0, 6] */
	u32 tm_yday;	/* days since January 1		- [0, 365] */
	u32 tm_isdst;	/* Daylight Saving Time flag */
};

/*externs*/
_IMPORT bool getTime(time_t time,struct tm * timeM);
_IMPORT time_t makeTime(struct tm * timeptr);

#endif /*CFG_RTC_EN>0*/

#endif /*_TIME_H_*/
