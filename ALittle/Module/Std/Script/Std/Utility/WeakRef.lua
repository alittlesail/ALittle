-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___pairs = pairs
local ___ipairs = ipairs


function CreateKeyWeakMap()
	local mt = {}
	mt["__mode"] = "k"
	local table = {}
	setmetatable(table, mt)
	return table
end

function CreateValueWeakMap()
	local mt = {}
	mt["__mode"] = "v"
	local table = {}
	setmetatable(table, mt)
	return table
end

