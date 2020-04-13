
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine


assert(DisplayObjectS, " extends class:DisplayObjectS is nil")
QuadS = ALittle.Class(DisplayObjectS, "ALittleIDE.QuadS")

function QuadS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_quad")
end

