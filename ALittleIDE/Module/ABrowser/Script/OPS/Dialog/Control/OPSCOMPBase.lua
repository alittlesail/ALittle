
module("ABrowser", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
OPSCOMPBase = ALittle.Class(ALittle.DisplayLayout, "ABrowser.OPSCOMPBase")

function OPSCOMPBase:GetData()
end

function OPSCOMPBase:GetCopyString()
	return ""
end

