-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
IDETreeLogic = Lua.Class(ALittle.DisplayLayout, "Emulator.IDETreeLogic")

function IDETreeLogic:Ctor(ctrl_sys)
end

function IDETreeLogic:IsTree()
	return false
end

function IDETreeLogic.__getter:title()
	return self._item_title.text
end

function IDETreeLogic.__setter:fold(value)
end

function IDETreeLogic.__getter:fold()
	return false
end

function IDETreeLogic:HandleClick(event)
end

function IDETreeLogic:HandleMoveIn(event)
end

function IDETreeLogic:HandleMouseMove(event)
end

function IDETreeLogic:HandleMoveOut(event)
end

function IDETreeLogic:SearchDescription(name, list)
	return nil
end

