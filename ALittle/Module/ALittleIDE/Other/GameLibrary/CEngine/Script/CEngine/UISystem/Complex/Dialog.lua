-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = GetAllStruct()

RegStruct(1517533145, "ALittle.DialogDragEvent", {
name = "ALittle.DialogDragEvent", ns_name = "ALittle", rl_name = "DialogDragEvent", hash_code = 1517533145,
name_list = {"target","delta_x","delta_y"},
type_list = {"ALittle.DisplayObject","double","double"},
option_map = {}
})
RegStruct(1971745271, "ALittle.DialogDragBeginEvent", {
name = "ALittle.DialogDragBeginEvent", ns_name = "ALittle", rl_name = "DialogDragBeginEvent", hash_code = 1971745271,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
RegStruct(-1482649531, "ALittle.DialogDragEndEvent", {
name = "ALittle.DialogDragEndEvent", ns_name = "ALittle", rl_name = "DialogDragEndEvent", hash_code = -1482649531,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
Dialog = Lua.Class(ALittle.DisplayLayout, "ALittle.Dialog")

function Dialog:Ctor(ctrl_sys)
	___rawset(self, "_pickup_rect", true)
	___rawset(self, "_pickup_child", true)
	___rawset(self, "_title_text", "")
	___rawset(self, "_head", DisplayLayout(self._ctrl_sys))
	___rawset(self, "_body", DisplayLayout(self._ctrl_sys))
	___rawset(self, "_grid3", Grid3(self._ctrl_sys))
	self._grid3.width_type = UIEnumTypes.SIZE_MARGIN
	self._grid3.width_value = 0
	self._grid3.height_type = UIEnumTypes.SIZE_MARGIN
	self._grid3.height_value = 0
	self._grid3.type = UIEnumTypes.TYPE_V
	self._grid3.show_up = self._head
	self._grid3.show_center = self._body
	DisplayLayout.AddChild(self, self._grid3)
end

function Dialog:GetChildOffset()
	return 0, self._grid3.up_size
end

function Dialog.__setter:head_size(value)
	self._grid3.up_size = value
	if self._background ~= nil then
		self._background.height_value = self._grid3.up_size
	end
	if self._close_button ~= nil then
		self._close_button.x_value = (value - self._close_button.height) / 2
	end
	if self._title ~= nil then
		self._title.x_value = (value - self._title.font_height)
	end
end

function Dialog.__getter:head_size()
	return self._grid3.up_size
end

function Dialog:ResetHeadOrder()
	local index = 1
	if self._head_drag ~= nil then
		self._head:SetChildIndex(self._head_drag, index)
		index = index + 1
	end
	if self._title ~= nil then
		self._head:SetChildIndex(self._title, index)
		index = index + 1
	end
	if self._close_button ~= nil then
		self._head:SetChildIndex(self._close_button, index)
		index = index + 1
	end
end

function Dialog.__setter:show_background(value)
	if self._background ~= nil then
		DisplayLayout.RemoveChild(self, self._background)
	end
	self._background = value
	if self._background ~= nil then
		self._background.width_type = UIEnumTypes.SIZE_MARGIN
		self._background.width_value = 0
		self._background.height_type = UIEnumTypes.SIZE_MARGIN
		self._background.height_value = self._grid3.up_size
		self._background.y_type = UIEnumTypes.POS_ALIGN_ENDING
		DisplayLayout.AddChild(self, self._background, 1)
		self:ResetHeadOrder()
	end
end

function Dialog.__getter:show_background()
	return self._background
end

function Dialog.__setter:show_head_drag(value)
	if self._head_drag ~= nil then
		self._head:RemoveChild(self._head_drag)
		self._head_drag:RemoveEventListener(___all_struct[1301789264], self, self.HandleHeadDragBegin)
		self._head_drag:RemoveEventListener(___all_struct[1337289812], self, self.HandleHeadDrag)
		self._head_drag:RemoveEventListener(___all_struct[150587926], self, self.HandleHeadDragEnd)
	end
	self._head_drag = value
	if self._head_drag ~= nil then
		self._head_drag.width_type = UIEnumTypes.SIZE_MARGIN
		self._head_drag.width_value = 0
		self._head_drag.height_type = UIEnumTypes.SIZE_MARGIN
		self._head_drag.height_value = 0
		self._head:AddChild(self._head_drag)
		self:ResetHeadOrder()
		self._head_drag:AddEventListener(___all_struct[1301789264], self, self.HandleHeadDragBegin)
		self._head_drag:AddEventListener(___all_struct[1337289812], self, self.HandleHeadDrag)
		self._head_drag:AddEventListener(___all_struct[150587926], self, self.HandleHeadDragEnd)
	end
end

function Dialog.__getter:show_head_drag()
	return self._head_drag
end

function Dialog.__setter:show_title(value)
	if self._title ~= nil then
		self._title_text = self._title.text
		self._head:RemoveChild(self._title)
	end
	self._title = value
	if self._title ~= nil then
		self._title.text = self._title_text
		self._title.disabled = true
		self._title.y_type = UIEnumTypes.POS_ALIGN_CENTER
		self._title.y_value = 0
		self._head:AddChild(self._title)
		self._title.x_type = UIEnumTypes.POS_ABS
		self._title.x_value = (self._grid3.up_size - self._title.font_height)
		self:ResetHeadOrder()
	end
end

function Dialog.__getter:show_title()
	return self._title
end

function Dialog.__setter:title(value)
	self._title_text = value
	if self._title ~= nil then
		self._title.text = value
	end
end

function Dialog.__getter:title()
	if self._title ~= nil then
		return self._title.text
	end
	return self._title_text
end

function Dialog.__setter:show_close_button(value)
	if self._close_button ~= nil then
		self._head:RemoveChild(self._close_button)
		self._close_button:RemoveEventListener(___all_struct[-449066808], self, self.HandleCloseButtonClicked)
	end
	self._close_button = value
	if self._close_button ~= nil then
		self._close_button.y_value = 0
		self._close_button.y_type = UIEnumTypes.POS_ALIGN_CENTER
		self._head:AddChild(self._close_button)
		self._close_button.x_type = UIEnumTypes.POS_ALIGN_ENDING
		self._close_button.x_value = (self._grid3.up_size - self._close_button.height) / 2
		self:ResetHeadOrder()
		self._close_button:AddEventListener(___all_struct[-449066808], self, self.HandleCloseButtonClicked)
	end
end

function Dialog.__getter:show_close_button()
	return self._close_button
end

function Dialog.__setter:close_callback(value)
	self._close_callback = value
end

function Dialog.__getter:close_callback()
	return self._close_callback
end

function Dialog:HandleCloseButtonClicked(event)
	self.visible = false
	if self._close_callback ~= nil then
		self._close_callback()
	end
end

function Dialog:HandleHeadDragBegin(event)
	self:DispatchEvent(___all_struct[1971745271], {})
end

function Dialog:HandleHeadDrag(event)
	self.x = self.x + (event.delta_x)
	self.y = self.y + (event.delta_y)
	local new_event = {}
	new_event.target = self
	new_event.delta_x = event.delta_x
	new_event.delta_y = event.delta_y
	self:DispatchEvent(___all_struct[1517533145], new_event)
end

function Dialog:HandleHeadDragEnd(event)
	self:DispatchEvent(___all_struct[-1482649531], {})
end

function Dialog:GetChildIndex(child)
	return self._body:GetChildIndex(child)
end

function Dialog:SetChildIndex(child, index)
	return self._body:SetChildIndex(child, index)
end

function Dialog:GetChildByIndex(index)
	return self._body:GetChildByIndex(index)
end

function Dialog:GetChildIndex(child)
	return self._body:GetChildIndex(child)
end

function Dialog.__getter:childs()
	return self._body.childs
end

function Dialog.__getter:child_count()
	return self._body.child_count
end

function Dialog:AddChild(child, index)
	if child == nil or child == self then
		return false
	end
	if child._show_parent == self._body or child._logic_parent == self then
		return true
	end
	if child._logic_parent ~= nil then
		child._logic_parent:RemoveChild(child)
	elseif child._show_parent ~= nil then
		child._show_parent:RemoveChild(child)
	end
	local result = self._body:AddChild(child, index)
	child._logic_parent = self
	return result
end

function Dialog:RemoveChild(child)
	if child == nil then
		return false
	end
	if child._show_parent ~= self._body and child._logic_parent ~= self then
		return false
	end
	local index = self._body:GetChildIndex(child)
	if index == 0 then
		return false
	end
	return self._body:RemoveChild(child)
end

function Dialog:SpliceChild(index, count)
	return self._body:SpliceChild(index, count)
end

function Dialog:HasChild(child)
	return self._body:HasChild(child)
end

function Dialog:RemoveAllChild()
	self._body:RemoveAllChild()
end

