
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayObjectS, " extends class:ALittleIDE.DisplayObjectS is nil")
DisplayLayoutS = Lua.Class(ALittleIDE.DisplayObjectS, "ALittleIDE.DisplayLayoutS")

function DisplayLayoutS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_displaylayout")
end

