
module("ABrowser", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


assert(ABrowser.OPSTDStringInput, " extends class:ABrowser.OPSTDStringInput is nil")
OPSTDNumberInput = Lua.Class(ABrowser.OPSTDStringInput, "ABrowser.OPSTDNumberInput")

function OPSTDNumberInput:GetData()
	local map = {}
	local value = tonumber(self._input.text)
	if value == nil then
		return false, nil, self._field_config.name .. " 不是数字"
	end
	map[self._field_config.query_param] = value
	return true, map, nil
end

