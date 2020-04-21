
module("ABrowser", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
OPSTDBase = Lua.Class(ALittle.DisplayLayout, "ABrowser.OPSTDBase")

function OPSTDBase:GetData()
	return false, nil, nil
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

