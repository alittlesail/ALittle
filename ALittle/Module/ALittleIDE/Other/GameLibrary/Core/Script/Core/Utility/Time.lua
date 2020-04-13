
module("ALittle", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


function Time_GetCurTime()
	return os.time()
end

function Time_GetCurDate(time)
	return os.date("%Y-%m-%d-%H-%M-%S", time)
end

function Time_GetCurYMD(time)
	return os.date("%Y-%m-%d", time)
end

