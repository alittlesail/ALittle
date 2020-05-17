-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayObjectS, " extends class:ALittleIDE.DisplayObjectS is nil")
DisplayViewS = Lua.Class(ALittleIDE.DisplayObjectS, "ALittleIDE.DisplayViewS")

function DisplayViewS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_displayview")
end

