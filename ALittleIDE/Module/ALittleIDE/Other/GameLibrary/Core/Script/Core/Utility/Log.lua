-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.LogLevel = {
	INFO = 0,
	WARN = 1,
	ERROR = 2,
}

local __LOG_FUNC = nil
function ALittle.SetLogFunc(func)
	__LOG_FUNC = func
end

function ALittle.Log(...)
	if __LOG_FUNC ~= nil then
		local scount = select("#", ...)
		local slist = {}
		local i = 1
		while true do
			if not(i <= scount) then break end
			slist[i] = ALittle.String_ToString(select(i, ...))
			i = i+(1)
		end
		local s = ALittle.String_Join(slist, "\t")
		__LOG_FUNC(s, 0)
		return
	end
	print(...)
end

function ALittle.Warn(...)
	if __LOG_FUNC ~= nil then
		local scount = select("#", ...)
		local slist = {}
		local i = 1
		while true do
			if not(i <= scount) then break end
			slist[i] = ALittle.String_ToString(select(i, ...))
			i = i+(1)
		end
		local s = ALittle.String_Join(slist, "\t")
		__LOG_FUNC(s, 1)
		return
	end
	print(...)
end

function ALittle.Error(...)
	if __LOG_FUNC ~= nil then
		local scount = select("#", ...)
		local slist = {}
		local i = 1
		while true do
			if not(i <= scount) then break end
			slist[i] = ALittle.String_ToString(select(i, ...))
			i = i+(1)
		end
		local s = ALittle.String_Join(slist, "\t")
		__LOG_FUNC(s, 2)
		return
	end
	print(...)
end

end