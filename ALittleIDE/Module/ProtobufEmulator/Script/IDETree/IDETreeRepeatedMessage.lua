-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ProtobufEmulator == nil then _G.ProtobufEmulator = {} end
local ProtobufEmulator = ProtobufEmulator
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ProtobufEmulator.IDETree, " extends class:ProtobufEmulator.IDETree is nil")
ProtobufEmulator.IDETreeRepeatedMessage = Lua.Class(ProtobufEmulator.IDETree, "ProtobufEmulator.IDETreeRepeatedMessage")

function ProtobufEmulator.IDETreeRepeatedMessage:Ctor(ctrl_sys, root, parent, detail_info)
	___rawset(self, "_parent", parent)
	___rawset(self, "_detail_info", detail_info)
	___rawset(self, "_head", ctrl_sys:CreateControl("ide_common_tree_repeated_message", self))
	ALittle.DisplayGroup.AddChild(self, self._head, 1)
	self._item_title.text = "[" .. detail_info.info.name .. "] "
	self._insert_button.x = self._item_title.x + self._item_title.width + 1
	self._delete_button.x = self._insert_button.x + self._insert_button.width + 1
	self._head.width = self._delete_button.x + self._delete_button.width + 1
	self:Init()
	self._insert_button.disabled = root.for_show
	self._delete_button.disabled = root.for_show
end

function ProtobufEmulator.IDETreeRepeatedMessage:GetDetailInfo()
	return self._detail_info
end

function ProtobufEmulator.IDETreeRepeatedMessage:HandleInsertClick(event)
	self._parent:CreateOneBefore(self)
end

function ProtobufEmulator.IDETreeRepeatedMessage:HandleDeleteClick(event)
	self._parent:Delete(self)
end

end