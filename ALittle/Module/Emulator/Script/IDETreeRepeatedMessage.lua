-- ALittle Generate Lua
module("Emulator", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(Emulator.IDETree, " extends class:Emulator.IDETree is nil")
IDETreeRepeatedMessage = Lua.Class(Emulator.IDETree, "Emulator.IDETreeRepeatedMessage")

function IDETreeRepeatedMessage:Ctor(ctrl_sys, parent, detail_info)
	___rawset(self, "_parent", parent)
	___rawset(self, "_detail_info", detail_info)
	___rawset(self, "_head", ctrl_sys:CreateControl("ide_common_tree_repeated_message", self))
	ALittle.DisplayGroup.AddChild(self, self._head, 1)
	self._item_title.text = "[" .. detail_info.info.name .. "] "
	self._insert_button.x = self._item_title.x + self._item_title.width + 1
	self._delete_button.x = self._insert_button.x + self._insert_button.width + 1
	self._head.width = self._delete_button.x + self._delete_button.width + 1
	self:Init()
end

function IDETreeRepeatedMessage:GetDetailInfo()
	return self._detail_info
end

function IDETreeRepeatedMessage:HandleInsertClick(event)
	self._parent:CreateOneBefore(self)
end

function IDETreeRepeatedMessage:HandleDeleteClick(event)
	self._parent:Delete(self)
end

