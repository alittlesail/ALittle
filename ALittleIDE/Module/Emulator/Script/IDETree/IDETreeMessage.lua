-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.Emulator == nil then _G.Emulator = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(Emulator.IDETree, " extends class:Emulator.IDETree is nil")
Emulator.IDETreeMessage = Lua.Class(Emulator.IDETree, "Emulator.IDETreeMessage")

function Emulator.IDETreeMessage:Ctor(ctrl_sys, root, field_name, detail_info)
	___rawset(self, "_detail_info", detail_info)
	___rawset(self, "_head", ctrl_sys:CreateControl("ide_common_tree_message", self))
	ALittle.DisplayGroup.AddChild(self, self._head, 1)
	self._item_title.text = "[" .. detail_info.info.name .. "] " .. field_name .. " "
	self._head.width = self._item_title.x + self._item_title.width + 1
	self:Init()
end

function Emulator.IDETreeMessage:GetDetailInfo()
	return self._detail_info
end

end