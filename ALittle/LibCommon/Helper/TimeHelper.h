
#ifndef _ALITTLE_TIMEHELPER_H_
#define _ALITTLE_TIMEHELPER_H_

#include <string>
#include <time.h>

namespace ALittle
{

const int ONE_MINUTE_SECONDS = 60;						// 每分钟对应的秒数
const int ONE_HOUR_SECONDS = 60 * ONE_MINUTE_SECONDS;	// 每小时对应的秒数
const int ONE_DAY_SECONDS = 24 * ONE_HOUR_SECONDS;		// 一天的秒数
const int ONE_WEEK_DAY = 7;								// 一周需要的天数
const int ONE_WEEK_SECONDS = 7 * ONE_DAY_SECONDS;		// 一周需要的秒数

class TimeHelper
{
public:
	// 获取当前时间，单位毫秒
	static long long GetCurMSTime();
	// 获取当前时间，单位秒
	static time_t GetCurTime();
	// 获取今天0点的时间，单位秒
	static time_t GetTodayBeginTime();
    static time_t CalcTodayBeginTime(time_t cur_time);
    // 获取第二天0点的时间，单位秒
	static time_t GetNextTodayBeginTime();

    // 获取这个月0店时间，单位秒
    static time_t GetMonthBeginTime();
    static time_t CalcMonthBeginTime(time_t cur_time);
    // 获取下个月0店时间，单位秒
    static time_t GetNextMonthBeginTime();
    static time_t CalcNextMonthBeginTime(time_t cur_time);

	/* 格式化时间
	 * @param time: the time to format
	 * @return YMD: YYYY-MM-DD
	 * @param ymd_split 年月日切割字符
	 * @return HMS: HH:MM:SS
	 * @param hms_split 时分秒切割字符
	 */
	static void FormatTime(time_t time, std::string* YMD, char ymd_split, std::string* HMS, char hms_split);
	static std::string FormatTime(time_t time);
};

} // ALittle

#endif // _ALITTLE_TIMEHELPER_H_
