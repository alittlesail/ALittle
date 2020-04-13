
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = GetAllStruct()


TextRadioButtonManager = Lua.Class(nil, "ALittle.TextRadioButtonManager")

function TextRadioButtonManager:Ctor()
	___rawset(self, "_name_map_group", {})
	___rawset(self, "_group_id", 0)
end

function TextRadioButtonManager:CreateGroupName()
	self._group_id = self._group_id + 1
	return "__TextRadioButtonManager_" .. self._group_id
end

function TextRadioButtonManager:SetGroupName(object, old_name, new_name)
	if old_name ~= nil then
		local group = self._name_map_group[old_name]
		if group ~= nil then
			group[object] = nil
		end
	end
	if new_name ~= nil then
		local group = self._name_map_group[new_name]
		if group == nil then
			group = CreateKeyWeakMap()
			self._name_map_group[new_name] = group
		end
		group[object] = true
	end
end

function TextRadioButtonManager:GetGroupByName(name)
	return self._name_map_group[name]
end

_G.A_TextRadioButtonManager = TextRadioButtonManager()
assert(ALittle.TextCheckButton, " extends class:ALittle.TextCheckButton is nil")
TextRadioButton = Lua.Class(ALittle.TextCheckButton, "ALittle.TextRadioButton")

function TextRadioButton:Ctor(ctrl_sys)
	___rawset(self, "_group_name", nil)
end

function TextRadioButton.__setter:group_name(name)
	A_TextRadioButtonManager:SetGroupName(self, self._group_name, name)
	self._group_name = name
end

function TextRadioButton.__getter:group_name()
	return self._group_name
end

function TextRadioButton:HandleLButtonUp(event)
	if event.rel_x >= 0 and event.rel_y >= 0 and event.rel_x < event.target._width and event.rel_y < event.target._height then
		if self._selected == false then
			self._selected = true
			local group = A_TextRadioButtonManager:GetGroupByName(self._group_name)
			if group ~= nil then
				for k, _ in ___pairs(group) do
					if k ~= self and k._selected == true then
						k._selected = false
						k:ShowUp()
						k:DispatchEvent(___all_struct[958494922], {})
					end
				end
			end
			self:DispatchEvent(___all_struct[958494922], {})
		end
		local e = {}
		e.is_drag = event.is_drag
		self:DispatchEvent(___all_struct[-449066808], e)
		if System_IsPhone == false then
			self:ShowOver()
		else
			self:ShowUp()
		end
	else
		self:ShowUp()
	end
end

function TextRadioButton.__setter:selected(value)
	if self._selected == value then
		return
	end
	self._selected = value
	if self._abs_disabled then
		self:ShowDisabled()
	else
		self:ShowUp()
	end
	if self._selected == false then
		return
	end
	local group = A_TextRadioButtonManager:GetGroupByName(self._group_name)
	if group ~= nil then
		for k, _ in ___pairs(group) do
			if k ~= self and k._selected == true then
				k._selected = false
				k:ShowUp()
			end
		end
	end
end

