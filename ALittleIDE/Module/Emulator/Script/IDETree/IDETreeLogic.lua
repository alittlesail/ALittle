-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.Emulator == nil then _G.Emulator = {} end
local Emulator = Emulator
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
Emulator.IDETreeLogic = Lua.Class(ALittle.DisplayLayout, "Emulator.IDETreeLogic")

function Emulator.IDETreeLogic:Ctor(ctrl_sys, root)
	___rawset(self, "_root", root)
end

function Emulator.IDETreeLogic:Init()
	self._upper_description = ALittle.String_Upper(self._item_title.text)
end

function Emulator.IDETreeLogic:IsTree()
	return false
end

function Emulator.IDETreeLogic.__getter:title()
	return self._item_title.text
end

function Emulator.IDETreeLogic.__setter:fold(value)
end

function Emulator.IDETreeLogic.__getter:fold()
	return false
end

function Emulator.IDETreeLogic.__setter:light(value)
	self._light.visible = value
end

function Emulator.IDETreeLogic.__getter:light()
	return self._light.visible
end

function Emulator.IDETreeLogic:SearchBegin()
	self.light = false
end

function Emulator.IDETreeLogic:SearchEnd(list)
	for index, parent in ___ipairs(list) do
		parent.light = true
		if parent ~= self then
			parent = parent.logic_parent
			while parent ~= nil do
				parent.fold = true
				if parent == self then
					break
				end
				parent = parent.logic_parent
			end
		end
	end
end

function Emulator.IDETreeLogic:SearchDescription(name, list)
	if list == nil then
		list = {}
	end
	self.light = false
	if ALittle.String_Find(self._upper_description, name) ~= nil then
		ALittle.List_Push(list, self)
	end
	return list
end

function Emulator.IDETreeLogic:Save()
	local content = protobuf.message_jsonencode(self._root.detail_info.message, false, false)
	if content == nil then
		return
	end
	Emulator.g_GProtoCache:SetConfig(self._root.detail_info.info.full_name, content)
end

end