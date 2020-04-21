
module("ABrowser", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


assert(ABrowser.OPSCOMPStringInput, " extends class:ABrowser.OPSCOMPStringInput is nil")
OPSCOMPNumberInput = Lua.Class(ABrowser.OPSCOMPStringInput, "ABrowser.OPSCOMPNumberInput")

function OPSCOMPNumberInput:GetData()
	return self._field_config.invoke_param, tonumber(self._input_ctrl.text)
end

