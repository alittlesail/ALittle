-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.Emulator == nil then _G.Emulator = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(Emulator.IDETreeLogic, " extends class:Emulator.IDETreeLogic is nil")
Emulator.IDETreeBoolMapBool = Lua.Class(Emulator.IDETreeLogic, "Emulator.IDETreeBoolMapBool")

function Emulator.IDETreeBoolMapBool:Ctor(ctrl_sys, root, parent, rflct, msg, key_field, value_field)
	___rawset(self, "_parent", parent)
	___rawset(self, "_rflct", rflct)
	___rawset(self, "_msg", msg)
	___rawset(self, "_key_field", key_field)
	___rawset(self, "_value_field", value_field)
	local key = protobuf.reflection_getbool(self._rflct, self._msg, self._key_field)
	local value = protobuf.reflection_getbool(self._rflct, self._msg, self._value_field)
	___rawset(self, "_item", ctrl_sys:CreateControl("ide_common_tree_bool_map_bool", self))
	self:AddChild(self._item)
	self.width = self._item.width
	self.height = self._item.height
	self._item_title.text = "[" .. protobuf.fielddescriptor_cpptypename(key_field) .. " " .. protobuf.fielddescriptor_cpptypename(value_field) .. "] : "
	if key then
		self._key_dropdown.text = "true"
	else
		self._key_dropdown.text = "false"
	end
	if value then
		self._value_dropdown.text = "true"
	else
		self._value_dropdown.text = "false"
	end
	self._key_dropdown.x = self._item_title.width + self._item_title.x + 1
	self._value_dropdown.x = self._key_dropdown.width + self._key_dropdown.x + 1
	self._insert_button.x = self._value_dropdown.x + self._value_dropdown.width + 1
	self._delete_button.x = self._insert_button.x + self._insert_button.width + 1
	self._item.width = self._delete_button.x + self._delete_button.width + 1
	self.width = self._item.width
	self:Init()
	self._key_dropdown.disabled = root.for_show
	self._value_dropdown.disabled = root.for_show
	self._insert_button.disabled = root.for_show
	self._delete_button.disabled = root.for_show
end

function Emulator.IDETreeBoolMapBool:HandleKeySelectChanegd(event)
	if self._key_dropdown.text == "true" then
		protobuf.reflection_setbool(self._rflct, self._msg, self._key_field, true)
	else
		protobuf.reflection_setbool(self._rflct, self._msg, self._key_field, false)
	end
	self:Save()
end

function Emulator.IDETreeBoolMapBool:HandleValueSelectChanegd(event)
	if self._value_dropdown.text == "true" then
		protobuf.reflection_setbool(self._rflct, self._msg, self._value_field, true)
	else
		protobuf.reflection_setbool(self._rflct, self._msg, self._value_field, false)
	end
	self:Save()
end

function Emulator.IDETreeBoolMapBool:HandleInsertClick(event)
	self._parent:CreateOneBefore(self)
end

function Emulator.IDETreeBoolMapBool:HandleDeleteClick(event)
	self._parent:Delete(self)
end

end