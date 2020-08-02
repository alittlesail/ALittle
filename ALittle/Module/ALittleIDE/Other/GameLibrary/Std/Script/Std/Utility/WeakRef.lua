-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


function ALittle.CreateKeyWeakMap()
	local mt = {}
	mt["__mode"] = "k"
	local table = {}
	setmetatable(table, mt)
	return table
end

function ALittle.CreateValueWeakMap()
	local mt = {}
	mt["__mode"] = "v"
	local table = {}
	setmetatable(table, mt)
	return table
end

end