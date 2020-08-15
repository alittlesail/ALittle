
module("ABrowser", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

assert(OPSCOMPStringInput, " extends class:OPSCOMPStringInput is nil")
OPSCOMPNumberInput = ALittle.Class(OPSCOMPStringInput, "ABrowser.OPSCOMPNumberInput")

function OPSCOMPNumberInput:GetData()
	return self._field_config.invoke_param, tonumber(self._input_ctrl.text)
end

