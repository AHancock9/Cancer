/*******************************************************
********************************************************
	@begin
		@type file
		@version 0.0.1
		@date 2012.12.21
		@author ZhangYan
		@brief
            Time concept in real world.
		@detail
            File contains many common operations on time.
	@end
********************************************************
********************************************************/
#include "xtime.h"

#if CFG_RTC_EN > 0

/*privates*/
_LOCAL u32 DaysOfmonths [] = {31,28,31,30,31,30,31,31,30,31,30,31};
_LOCAL s32 days_since_epoch(s32 year,s32 yday)
{
	if(year>=0) /* 1970 + */
    	return ( (DAYS_PER_YEAR * year) + (year + 1) / 4  + yday );
	else		/* 1969 - */
    	return ( (DAYS_PER_YEAR * year) + (year - 2) / 4  + yday );
}
_LOCAL s32 _julday(s32 yr, s32 mon,s32 day)
{
    static s32 jdays[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    s32 leap = 0;
    if (isleap (yr + TM_YEAR_BASE))
	{
        /*
         * If it is a leap year, leap only gets set if the day is
         * after beginning of March (SPR #4251).
         */
        if (mon > 1)
        {
            leap = 1;
        }
	}
    return (jdays [mon] + day + leap );
}
_LOCAL void ldiv_r(long numer,long denom,ldiv_t * divStructPtr)
{
    /* calculate quotient */
    divStructPtr->quot = numer / denom;

    /* calculate remainder */
    divStructPtr->rem = numer - (denom * divStructPtr->quot);

    /* check for negative numerator */
    if ((numer < 0) && (divStructPtr->rem > 0))
    {
        divStructPtr->quot++;
        divStructPtr->rem -= denom;
    }
}

/*publics*/
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
bool getTime(const time_t time,struct tm * timeM)
{
    s32	days;
    s32	timeOfDay;
    s32	year;
    s32	mon;
    ldiv_t	result;

    /* Calulate number of days since epoch */

    days = time / SECS_PER_DAY;
    timeOfDay = time % SECS_PER_DAY;

    /* If time of day is negative, subtract one day, and add SECSPERDAY
     * to make it positive.
     */

    if(timeOfDay<0)
    {
        timeOfDay+=SECS_PER_DAY;
        days-=1;
    }

    /* Calulate number of years since epoch */

    year = days / DAYS_PER_YEAR;
    while(days_since_epoch (year, 0) > days)
    	year--;

    /* Calulate the day of the week */

    timeM->tm_wday = (days + EPOCH_WDAY) % DAYS_PER_WEEK;

	/*
	 * If there is a negative weekday, add DAYSPERWEEK to make it positive
	 */
	if(timeM->tm_wday<0)
		timeM->tm_wday+=DAYS_PER_WEEK;

    /* Find year and remaining days */

    days -= days_since_epoch (year, 0);
    year += EPOCH_YEAR;

    /* Find month */
    /* __jullday needs years since TM_YEAR_BASE (SPR 4251) */

    for  ( mon = 0;
         (days >= _julday (year - TM_YEAR_BASE, mon + 1, 0)) && (mon < 11);
         mon++ )
	;

    /* Initialise tm structure */

    timeM->tm_year = year - TM_YEAR_BASE; /* years since 1900 */
    timeM->tm_mon  = mon;
    timeM->tm_mday = (days - _julday (timeM->tm_year, mon, 0)) + 1;
    timeM->tm_yday = _julday (timeM->tm_year, mon, timeM->tm_mday) - 1;
    timeM->tm_hour = timeOfDay / SECS_PER_HOUR;

    timeOfDay  %= SECS_PER_HOUR;
    ldiv_r(timeOfDay, SECS_PER_MIN, &result);
    timeM->tm_min = result.quot;
    timeM->tm_sec = result.rem;

    return true;
}
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
time_t makeTime(struct tm * timeptr)
{
    s32 year = timeptr->tm_year-70;
    s32 thisYear = timeptr->tm_year+TM_YEAR_BASE;
    s32 thisMonth = timeptr->tm_mon;
    s32 thisHour = timeptr->tm_hour;
    s32 thisDate = timeptr->tm_mday;
    s32 thisMin = timeptr->tm_min;
    s32 thisSecond = timeptr->tm_sec;
    time_t result = 0;
    /*Calculate the days passed except for this year*/
    for(year-=1;year>=0;year--)
    {
         if(isleap(year+TM_YEAR_BASE))
         {
            result += (DAYS_PER_YEAR+1)*SECS_PER_DAY;
         }
         else
         {
             result += DAYS_PER_YEAR*SECS_PER_DAY;
         }
    }
    /*calculate this year*/

    /*month*/
    for(thisMonth-=1;thisMonth>=0;thisMonth--)
    {
        result+= (DaysOfmonths[thisMonth]*SECS_PER_DAY);
    }
    if((thisMonth+=1)>1)
    {
        if(isleap(thisYear))
        {
            result += SECS_PER_DAY;
        }
    }
    result += ((thisDate)*SECS_PER_DAY);

    /*calculate the hours*/
    result += (SECS_PER_HOUR*thisHour);
    /*calculate the mins*/
    result += ((SECS_PER_MIN)*thisMin);
    /*calculate the second*/
    result += thisSecond;
    return result;
}

#endif /*CFG_RTC_EN>0*/
