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
ProtobufEmulator.IDETreeMessage = Lua.Class(ProtobufEmulator.IDETree, "ProtobufEmulator.IDETreeMessage")

function ProtobufEmulator.IDETreeMessage:Ctor(ctrl_sys, root, field_name, detail_info)
	___rawset(self, "_detail_info", detail_info)
	___rawset(self, "_head", ctrl_sys:CreateControl("ide_common_tree_message", self))
	ALittle.DisplayGroup.AddChild(self, self._head, 1)
	self._item_title.text = "[" .. detail_info.info.name .. "] " .. field_name .. " "
	self._head.width = self._item_title.x + self._item_title.width + 1
	self:Init()
end

function ProtobufEmulator.IDETreeMessage:GetDetailInfo()
	return self._detail_info
end

end