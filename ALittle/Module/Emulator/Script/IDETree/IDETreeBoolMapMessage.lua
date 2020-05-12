-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(Emulator.IDETree, " extends class:Emulator.IDETree is nil")
IDETreeBoolMapMessage = Lua.Class(Emulator.IDETree, "Emulator.IDETreeBoolMapMessage")

function IDETreeBoolMapMessage:Ctor(ctrl_sys, root, parent, rflct, msg, key_field, detail_info)
	___rawset(self, "_detail_info", detail_info)
	___rawset(self, "_parent", parent)
	___rawset(self, "_rflct", rflct)
	___rawset(self, "_msg", msg)
	___rawset(self, "_key_field", key_field)
	local key = protobuf.reflection_getbool(self._rflct, self._msg, self._key_field)
	___rawset(self, "_head", ctrl_sys:CreateControl("ide_common_tree_bool_map_message", self))
	ALittle.DisplayGroup.AddChild(self, self._head, 1)
	self._item_title.text = "[" .. protobuf.fielddescriptor_cpptypename(key_field) .. " " .. detail_info.info.name .. "] : "
	if key then
		self._key_dropdown.text = "true"
	else
		self._key_dropdown.text = "false"
	end
	self._key_dropdown.x = self._item_title.width + self._item_title.x + 1
	self._insert_button.x = self._key_dropdown.x + self._key_dropdown.width + 1
	self._delete_button.x = self._insert_button.x + self._insert_button.width + 1
	self._head.width = self._delete_button.x + self._delete_button.width + 1
	self:Init()
	self._key_dropdown.disabled = root.for_show
	self._insert_button.disabled = root.for_show
	self._delete_button.disabled = root.for_show
end

function IDETreeBoolMapMessage:GetDetailInfo()
	return self._detail_info
end

function IDETreeBoolMapMessage:HandleKeySelectChanegd(event)
	if self._key_dropdown.text == "true" then
		protobuf.reflection_setbool(self._rflct, self._msg, self._key_field, true)
	else
		protobuf.reflection_setbool(self._rflct, self._msg, self._key_field, false)
	end
	self:Save()
end

function IDETreeBoolMapMessage:HandleInsertClick(event)
	self._parent:CreateOneBefore(self)
end

function IDETreeBoolMapMessage:HandleDeleteClick(event)
	self._parent:Delete(self)
end

