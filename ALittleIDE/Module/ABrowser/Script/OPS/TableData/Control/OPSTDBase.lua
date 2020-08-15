
module("ABrowser", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
OPSTDBase = ALittle.Class(ALittle.DisplayLayout, "ABrowser.OPSTDBase")

function OPSTDBase:GetData()
end

function OPSTDBase:CanOption()
	return false
end

function OPSTDBase:GetCopyString()
	return ""
end

function OPSTDBase:CutText()
end

function OPSTDBase:PasteText()
end

