
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine


assert(DisplayObjectS, " extends class:DisplayObjectS is nil")
DisplayLayoutS = ALittle.Class(DisplayObjectS, "ALittleIDE.DisplayLayoutS")

function DisplayLayoutS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_displaylayout")
end

