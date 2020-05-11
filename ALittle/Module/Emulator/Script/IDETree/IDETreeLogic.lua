-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
IDETreeLogic = Lua.Class(ALittle.DisplayLayout, "Emulator.IDETreeLogic")

function IDETreeLogic:Ctor(ctrl_sys, root)
	___rawset(self, "_root", root)
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

function IDETreeLogic.__setter:light(value)
	self._light.visible = value
end

function IDETreeLogic.__getter:light()
	return self._light.visible
end

function IDETreeLogic:SearchDescription(name, list)
	return nil
end

function IDETreeLogic:Save()
	local content = protobuf.message_jsonencode(self._root.detail_info.message)
	if content == nil then
		return
	end
	g_GProtoCache:SetConfig(self._root.detail_info.info.full_name, content)
end

