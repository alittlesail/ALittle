
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = GetAllStruct()


assert(ALittle.SpringCheckButton, " extends class:ALittle.SpringCheckButton is nil")
SpringRadioButton = Lua.Class(ALittle.SpringCheckButton, "ALittle.SpringRadioButton")

function SpringRadioButton:Ctor(ctrl_sys)
	___rawset(self, "_cancel_select", false)
end

function SpringRadioButton.__setter:group_name(value)
	A_TextRadioButtonManager:SetGroupName(self, self._group_name, value)
	self._group_name = value
end

function SpringRadioButton.__getter:group_name()
	return self._group_name
end

function SpringRadioButton.__setter:cancel_select(value)
	self._cancel_select = value
end

function SpringRadioButton.__getter:cancel_select()
	return self._cancel_select
end

function SpringRadioButton:HandleLButtonUp(event)
	if event.rel_x >= 0 and event.rel_y >= 0 and event.rel_x < event.target._width and event.rel_y < event.target._height then
		if self._selected == false then
			self._selected = true
			local group = A_TextRadioButtonManager:GetGroupByName(self._group_name)
			if group ~= nil then
				for k, v in ___pairs(group) do
					if k ~= self and v._selected == true then
						v._selected = false
						v:ShowUp()
						v:DispatchEvent(___all_struct[958494922], {})
					end
				end
			end
			self:DispatchEvent(___all_struct[958494922], {})
		elseif self._cancel_select then
			self._selected = false
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

function SpringRadioButton.__setter:selected(value)
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
		for k, v in ___pairs(group) do
			if k ~= self and v._selected == true then
				v._selected = false
				v:ShowUp()
			end
		end
	end
end

