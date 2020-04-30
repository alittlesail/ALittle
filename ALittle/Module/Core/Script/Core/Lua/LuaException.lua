-- ALittle Generate Lua
module("Lua", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___pairs = pairs
local ___ipairs = ipairs


local error = error
function TCall(...)
	local out_list = {pcall(...)}
	if out_list[1] ~= true then
		if out_list[2] == nil then
			return "nil"
		end
		return out_list[2]
	end
	local l = table.maxn(out_list)
	out_list[1] = nil
	return unpack(out_list, 1, l)
end

function Throw(msg)
	error(msg)
end

function Assert(value, msg)
	if value ~= nil and value ~= false then
		return
	end
	if msg == nil then
		msg = "Assert failed"
	end
	error(msg)
end

