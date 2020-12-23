-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.AUIPlugin == nil then _G.AUIPlugin = {} end
local AUIPlugin = AUIPlugin
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.Quad, " extends class:ALittle.Quad is nil")
AUIPlugin.AUICodeQuad = Lua.Class(ALittle.Quad, "AUIPlugin.AUICodeQuad")

function AUIPlugin.AUICodeQuad:Ctor()
	___rawset(self, "_ediable", true)
end

function AUIPlugin.AUICodeQuad.__getter:is_input()
	return true
end

function AUIPlugin.AUICodeQuad.__getter:editable()
	return self._ediable
end

function AUIPlugin.AUICodeQuad.__setter:editable(value)
	self._ediable = value
end

function AUIPlugin.AUICodeQuad.__getter:font_size()
	return AUIPlugin.CODE_FONT_SIZE
end

function AUIPlugin.AUICodeQuad.__getter:cursor_x()
	local tab_child = self._user_data
	return tab_child.cursor.x
end

function AUIPlugin.AUICodeQuad.__getter:cursor_y()
	local tab_child = self._user_data
	return tab_child.cursor.y
end

function AUIPlugin.AUICodeQuad.__getter:cursor_b()
	local tab_child = self._user_data
	return tab_child.cursor.y + tab_child.cursor.height
end

assert(ALittle.Linear, " extends class:ALittle.Linear is nil")
AUIPlugin.AUICodeLinear = Lua.Class(ALittle.Linear, "AUIPlugin.AUICodeLinear")

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
AUIPlugin.AUICodeEditContainer = Lua.Class(ALittle.DisplayLayout, "AUIPlugin.AUICodeEditContainer")

function AUIPlugin.AUICodeEditContainer:ClipRect(x, y, width, height, h_move, v_move)
	self._user_data:ClipRect(x - self._x, y - self._y, width - self._x, height - self._y, h_move, v_move)
end

end