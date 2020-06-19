-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
IDECodeTreeLogic = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDECodeTreeLogic")

function IDECodeTreeLogic:Ctor(ctrl_sys, user_info)
	___rawset(self, "_user_info", user_info)
end

function IDECodeTreeLogic.__getter:user_info()
	return self._user_info
end

function IDECodeTreeLogic.__getter:is_tree()
	return false
end

function IDECodeTreeLogic.__getter:is_root()
	return self._user_info.root
end

function IDECodeTreeLogic.__setter:fold(value)
end

function IDECodeTreeLogic:Refresh()
end

function IDECodeTreeLogic:SearchFile(name, list)
	if list == nil then
		list = {}
	end
	return list
end

function IDECodeTreeLogic:SearchDefine(name, list)
	if list == nil then
		list = {}
	end
	return list
end

