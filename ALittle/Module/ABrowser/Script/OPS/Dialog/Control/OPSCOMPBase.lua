
module("ABrowser", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
OPSCOMPBase = Lua.Class(ALittle.DisplayLayout, "ABrowser.OPSCOMPBase")

function OPSCOMPBase:GetData()
	return "", nil
end

function OPSCOMPBase:GetCopyString()
	return ""
end

