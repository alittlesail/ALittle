-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.Quad, " extends class:ALittle.Quad is nil")
AUICodeQuad = Lua.Class(ALittle.Quad, "AUIPlugin.AUICodeQuad")

function AUICodeQuad:Ctor()
	___rawset(self, "_ediable", true)
end

function AUICodeQuad.__getter:is_input()
	return true
end

function AUICodeQuad.__getter:editable()
	return self._ediable
end

function AUICodeQuad.__setter:editable(value)
	self._ediable = value
end

function AUICodeQuad.__getter:font_size()
	return CODE_FONT_SIZE
end

function AUICodeQuad.__getter:cursor_x()
	local tab_child = self._user_data
	return tab_child.cursor.x
end

function AUICodeQuad.__getter:cursor_y()
	local tab_child = self._user_data
	return tab_child.cursor.y
end

function AUICodeQuad.__getter:cursor_b()
	local tab_child = self._user_data
	return tab_child.cursor.y + tab_child.cursor.height
end

assert(ALittle.Linear, " extends class:ALittle.Linear is nil")
AUICodeLinear = Lua.Class(ALittle.Linear, "AUIPlugin.AUICodeLinear")

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
AUICodeEditContainer = Lua.Class(ALittle.DisplayLayout, "AUIPlugin.AUICodeEditContainer")

function AUICodeEditContainer:ClipRect(x, y, width, height, h_move, v_move)
	self._user_data:ClipRect(x - self._x, y - self._y, width - self._x, height - self._y, h_move, v_move)
end

