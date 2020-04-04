
module("ALittle", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


LogLevel = {
	INFO = 0,
	WARN = 1,
	ERROR = 2,
}

local __LOG_FUNC = nil
function SetLogFunc(func)
	__LOG_FUNC = func
end

function Log(...)
	if __LOG_FUNC ~= nil then
		local slist = {...}
		for index, value in ___ipairs(slist) do
			slist[index] = String_ToString(value)
		end
		local s = String_Join(slist, "\t")
		__LOG_FUNC(s, 0)
		return
	end
	print(...)
end

function Warn(...)
	if __LOG_FUNC ~= nil then
		local slist = {...}
		for index, value in ___ipairs(slist) do
			slist[index] = String_ToString(value)
		end
		local s = String_Join(slist, "\t")
		__LOG_FUNC(s, 1)
		return
	end
	print(...)
end

function Error(...)
	if __LOG_FUNC ~= nil then
		local slist = {...}
		for index, value in ___ipairs(slist) do
			slist[index] = String_ToString(value)
		end
		local s = String_Join(slist, "\t")
		__LOG_FUNC(s, 2)
		return
	end
	print(...)
end

