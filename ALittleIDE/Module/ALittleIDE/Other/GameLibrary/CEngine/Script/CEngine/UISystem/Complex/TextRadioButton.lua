-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()


assert(ALittle.TextCheckButton, " extends class:ALittle.TextCheckButton is nil")
ALittle.TextRadioButton = Lua.Class(ALittle.TextCheckButton, "ALittle.TextRadioButton")

function ALittle.TextRadioButton:Ctor(ctrl_sys)
end

function ALittle.TextRadioButton.__setter:group(group)
	if self._group == group then
		return
	end
	if self._group ~= nil then
		self._group[self] = nil
	end
	self._group = group
	if self._group ~= nil then
		self._group[self] = true
	end
end

function ALittle.TextRadioButton.__getter:group()
	return self._group
end

function ALittle.TextRadioButton.SetGroup(list)
	local group = ALittle.CreateKeyWeakMap()
	for index, button in ___ipairs(list) do
		if button._group ~= nil then
			button._group[button] = nil
		end
		button._group = group
		group[button] = true
	end
end

function ALittle.TextRadioButton:HandleLButtonUp(event)
	if event.rel_x >= 0 and event.rel_y >= 0 and event.rel_x < event.target._width and event.rel_y < event.target._height then
		if self._selected == false then
			self._selected = true
			if self._group ~= nil then
				for k, _ in ___pairs(self._group) do
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
		e.count = event.count
		self:DispatchEvent(___all_struct[-449066808], e)
		if ALittle.System_IsPhone() == false then
			self:ShowOver()
		else
			self:ShowUp()
		end
	else
		self:ShowUp()
	end
end

function ALittle.TextRadioButton.__setter:selected(value)
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
	if self._group ~= nil then
		for k, _ in ___pairs(self._group) do
			if k ~= self and k._selected == true then
				k._selected = false
				k:ShowUp()
			end
		end
	end
end

end