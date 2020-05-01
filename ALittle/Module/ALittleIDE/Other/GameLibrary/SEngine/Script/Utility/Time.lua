-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


local __VersionTime = 0
local __VersionIndex = 0
function NewTimeAndIndex()
	local cur_time = os.time()
	if __VersionTime == cur_time then
		__VersionIndex = __VersionIndex + 1
	elseif cur_time > __VersionTime then
		__VersionTime = cur_time
		__VersionIndex = 0
	end
	return __VersionTime, __VersionIndex
end

TimeSecond = {
	ONE_MINUTE_SECONDS = 60,
	ONE_HOUR_SECONDS = 3600,
	ONE_DAY_SECONDS = 86400,
	ONE_WEEK_DAY = 7,
	ONE_WEEK_SECONDS = 604800,
}

function DateInfo(time)
	return os.date("*t", time)
end

function GetNextTodayBeginTime()
	local date = DateInfo()
	date.hour = 0
	date.min = 0
	date.sec = 0
	return os.time(date) + TimeSecond.ONE_DAY_SECONDS
end

