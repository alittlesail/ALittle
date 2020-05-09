-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(Emulator.IDETree, " extends class:Emulator.IDETree is nil")
IDETreeRepeatedMessage = Lua.Class(Emulator.IDETree, "Emulator.IDETreeRepeatedMessage")

function IDETreeRepeatedMessage:Ctor(ctrl_sys, field_name, detail_info, field, index)
	___rawset(self, "_detail_info", detail_info)
	___rawset(self, "_head", ctrl_sys:CreateControl("ide_common_tree_message", self))
	ALittle.DisplayGroup.AddChild(self, self._head, 1)
	self._item_title.text = "[" .. detail_info.info.name .. "] " .. field_name
	self:Init()
end

function IDETreeRepeatedMessage:GetDetailInfo()
	return self._detail_info
end

