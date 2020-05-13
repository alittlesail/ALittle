-- ALittle Generate Lua And Do Not Edit This Line!
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
		local scount = select("#", ...)
		local slist = {}
		local i = 1
		while true do
			if not(i <= scount) then break end
			slist[i] = String_ToString(select(i, ...))
			i = i+(1)
		end
		local s = String_Join(slist, "\t")
		__LOG_FUNC(s, 0)
		return
	end
	print(...)
end

function Warn(...)
	if __LOG_FUNC ~= nil then
		local scount = select("#", ...)
		local slist = {}
		local i = 1
		while true do
			if not(i <= scount) then break end
			slist[i] = String_ToString(select(i, ...))
			i = i+(1)
		end
		local s = String_Join(slist, "\t")
		__LOG_FUNC(s, 1)
		return
	end
	print(...)
end

function Error(...)
	if __LOG_FUNC ~= nil then
		local scount = select("#", ...)
		local slist = {}
		local i = 1
		while true do
			if not(i <= scount) then break end
			slist[i] = String_ToString(select(i, ...))
			i = i+(1)
		end
		local s = String_Join(slist, "\t")
		__LOG_FUNC(s, 2)
		return
	end
	print(...)
end

