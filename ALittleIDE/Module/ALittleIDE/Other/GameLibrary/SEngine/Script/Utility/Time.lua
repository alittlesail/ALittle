-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___pairs = pairs
local ___ipairs = ipairs


local __VersionTime = 0
local __VersionIndex = 0
function ALittle.NewTimeAndIndex()
	local cur_time = os.time()
	if __VersionTime == cur_time then
		__VersionIndex = __VersionIndex + 1
	elseif cur_time > __VersionTime then
		__VersionTime = cur_time
		__VersionIndex = 0
	end
	return __VersionTime, __VersionIndex
end

ALittle.TimeSecond = {
	ONE_MINUTE_SECONDS = 60,
	ONE_HOUR_SECONDS = 3600,
	ONE_DAY_SECONDS = 86400,
	ONE_WEEK_DAY = 7,
	ONE_WEEK_SECONDS = 604800,
}

function ALittle.DateInfo(time)
	return os.date("*t", time)
end

function ALittle.GetNextTodayBeginTime()
	local date = ALittle.DateInfo()
	date.hour = 0
	date.min = 0
	date.sec = 0
	return os.time(date) + 86400
end

end