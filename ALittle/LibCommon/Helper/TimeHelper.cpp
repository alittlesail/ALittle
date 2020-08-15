
#include "TimeHelper.h"

#include <time.h>
#include <vector>
#include <chrono>
#include <sys/stat.h>
#include <ctype.h>

#ifdef _WIN32
#include <direct.h>
#endif

namespace ALittle
{
	
long long TimeHelper::GetCurMSTime()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

time_t TimeHelper::GetCurTime()
{
	return time(0);
}

time_t TimeHelper::GetTodayBeginTime()
{
	return CalcTodayBeginTime(GetCurTime());
}

time_t TimeHelper::GetNextTodayBeginTime()
{
	return CalcTodayBeginTime(GetCurTime()) + ONE_DAY_SECONDS;
}

time_t TimeHelper::GetMonthBeginTime()
{
    return CalcMonthBeginTime(GetCurTime());
}

time_t TimeHelper::CalcMonthBeginTime(time_t cur_time)
{
    tm* ptr_time;
#ifdef _WIN32
    tm st_time;
    ptr_time = &st_time;
    localtime_s(ptr_time, &cur_time);
#else
    ptr_time = localtime(&cur_time);
#endif

    tm st_time_tmp;
    st_time_tmp.tm_year = ptr_time->tm_year;
    st_time_tmp.tm_mon = ptr_time->tm_mon;
    st_time_tmp.tm_mday = 1;
    st_time_tmp.tm_hour = 0;
    st_time_tmp.tm_min = 0;
    st_time_tmp.tm_sec = 0;

    return mktime(&st_time_tmp);
}

time_t TimeHelper::GetNextMonthBeginTime()
{
    return CalcNextMonthBeginTime(GetCurTime());
}

time_t TimeHelper::CalcNextMonthBeginTime(time_t cur_time)
{
    tm* ptr_time;
#ifdef _WIN32
    tm st_time;
    ptr_time = &st_time;
    localtime_s(ptr_time, &cur_time);
#else
    ptr_time = localtime(&cur_time);
#endif

    tm st_time_tmp;
    st_time_tmp.tm_year = ptr_time->tm_year;
    st_time_tmp.tm_mon = ptr_time->tm_mon + 1;
    if (st_time_tmp.tm_mon >= 12)
    {
        st_time_tmp.tm_year += 1;
        st_time_tmp.tm_mon = 0;
    }
    st_time_tmp.tm_mday = 1;
    st_time_tmp.tm_hour = 0;
    st_time_tmp.tm_min = 0;
    st_time_tmp.tm_sec = 0;

    return mktime(&st_time_tmp);
}

time_t TimeHelper::CalcTodayBeginTime(time_t cur_time)
{
	tm* ptr_time;
#ifdef _WIN32
	tm st_time;
	ptr_time = &st_time;
	localtime_s(ptr_time, &cur_time);
#else
	ptr_time = localtime(&cur_time);
#endif

	tm st_time_tmp;
	st_time_tmp.tm_year = ptr_time->tm_year;
	st_time_tmp.tm_mon = ptr_time->tm_mon;
	st_time_tmp.tm_mday = ptr_time->tm_mday;
	st_time_tmp.tm_hour = 0;
	st_time_tmp.tm_min = 0;
	st_time_tmp.tm_sec = 0;

	return mktime(&st_time_tmp);
}

void TimeHelper::FormatTime(time_t time, std::string* YMD, char ymd_split, std::string* HMS, char hms_split)
{
	tm* ptr_time;
#ifdef _WIN32
	tm st_time;
	ptr_time = &st_time;
	localtime_s(ptr_time, &time);
#else
	ptr_time = localtime(&time);
#endif

	if (HMS)
	{
		char hms[16];
		if (hms_split != 0)
		{
#ifdef _WIN32
			sprintf_s(hms, 16, "%02d%c%02d%c%02d", ptr_time->tm_hour, hms_split, ptr_time->tm_min, hms_split, ptr_time->tm_sec);
#else
			sprintf(hms, "%02d%c%02d%c%02d", ptr_time->tm_hour, hms_split, ptr_time->tm_min, hms_split, ptr_time->tm_sec);
#endif
		}
		else
		{
#ifdef _WIN32
			sprintf_s(hms, 16, "%02d%02d%02d", ptr_time->tm_hour, ptr_time->tm_min, ptr_time->tm_sec);
#else
			sprintf(hms, "%02d%02d%02d", ptr_time->tm_hour, ptr_time->tm_min, ptr_time->tm_sec);
#endif
		}
		*HMS = hms;
	}

	if (YMD)
	{
		char date[16];
		if (ymd_split != 0)
		{
#ifdef _WIN32
			sprintf_s(date, 16, "%4d%c%02d%c%02d", (ptr_time->tm_year + 1900), ymd_split, ptr_time->tm_mon + 1, ymd_split, ptr_time->tm_mday);
#else
			sprintf(date, "%4d%c%02d%c%02d", (ptr_time->tm_year + 1900), ymd_split, ptr_time->tm_mon + 1, ymd_split, ptr_time->tm_mday);
#endif
		}
		else
		{
#ifdef _WIN32
			sprintf_s(date, 16, "%4d%02d%02d", (ptr_time->tm_year + 1900), ptr_time->tm_mon + 1, ptr_time->tm_mday);
#else
			sprintf(date, "%4d%02d%02d", (ptr_time->tm_year + 1900), ptr_time->tm_mon + 1, ptr_time->tm_mday);
#endif
		}
		*YMD = date;
	}
}

std::string TimeHelper::FormatTime(time_t time)
{
	std::string YMD, HMS;
	FormatTime(time, &YMD, '-', &HMS, ':');
	return YMD + " " + HMS;
}

} // ALittle