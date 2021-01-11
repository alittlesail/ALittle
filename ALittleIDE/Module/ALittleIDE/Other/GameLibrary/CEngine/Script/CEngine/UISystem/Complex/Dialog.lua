-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1971745271, "ALittle.DialogDragBeginEvent", {
name = "ALittle.DialogDragBeginEvent", ns_name = "ALittle", rl_name = "DialogDragBeginEvent", hash_code = 1971745271,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(1517533145, "ALittle.DialogDragEvent", {
name = "ALittle.DialogDragEvent", ns_name = "ALittle", rl_name = "DialogDragEvent", hash_code = 1517533145,
name_list = {"target","delta_x","delta_y"},
type_list = {"ALittle.DisplayObject","double","double"},
option_map = {}
})
ALittle.RegStruct(-1482649531, "ALittle.DialogDragEndEvent", {
name = "ALittle.DialogDragEndEvent", ns_name = "ALittle", rl_name = "DialogDragEndEvent", hash_code = -1482649531,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittle.Dialog = Lua.Class(ALittle.DisplayLayout, "ALittle.Dialog")

function ALittle.Dialog:Ctor(ctrl_sys)
	___rawset(self, "_pickup_rect", true)
	___rawset(self, "_pickup_child", true)
	___rawset(self, "_title_text", "")
	___rawset(self, "_head", ALittle.DisplayLayout(self._ctrl_sys))
	___rawset(self, "_head_container", ALittle.DisplayLayout(self._ctrl_sys))
	self._head_container.width_type = 4
	self._head_container.height_type = 4
	self._head:AddChild(self._head_container)
	___rawset(self, "_head_left_margin", 0)
	___rawset(self, "_head_right_margin", 0)
	___rawset(self, "_head_top_margin", 0)
	___rawset(self, "_head_bottom_margin", 0)
	___rawset(self, "_body", ALittle.DisplayLayout(self._ctrl_sys))
	___rawset(self, "_grid3", ALittle.Grid3(self._ctrl_sys))
	self._grid3.width_type = 4
	self._grid3.width_value = 0
	self._grid3.height_type = 4
	self._grid3.height_value = 0
	self._grid3.type = 2
	self._grid3.show_up = self._head
	self._grid3.show_center = self._body
	ALittle.DisplayLayout.AddChild(self, self._grid3)
end

function ALittle.Dialog:GetChildOffset()
	return 0, self._grid3.up_size
end

function ALittle.Dialog.__setter:head_size(value)
	self._grid3.up_size = value
	if self._background ~= nil then
		self._background.height_value = self._grid3.up_size
	end
	if self._close_button ~= nil then
		self._close_button.x_value = (value - self._close_button.height) / 2
	end
end

function ALittle.Dialog.__getter:head_size()
	return self._grid3.up_size
end

function ALittle.Dialog.__getter:head_left_margin()
	return self._head_left_margin
end

function ALittle.Dialog.__setter:head_left_margin(value)
	self._head_left_margin = value
	self._head_container.x = value
	self._head_container.width_value = self._head_left_margin + self._head_right_margin
end

function ALittle.Dialog.__getter:head_right_margin()
	return self._head_right_margin
end

function ALittle.Dialog.__setter:head_right_margin(value)
	self._head_right_margin = value
	self._head_container.width_value = self._head_left_margin + self._head_right_margin
end

function ALittle.Dialog.__getter:head_top_margin()
	return self._head_top_margin
end

function ALittle.Dialog.__setter:head_top_margin(value)
	self._head_top_margin = value
	self._head_container.y = value
	self._head_container.height_value = self._head_top_margin + self._head_bottom_margin
end

function ALittle.Dialog.__getter:head_bottom_margin()
	return self._head_bottom_margin
end

function ALittle.Dialog.__setter:head_bottom_margin(value)
	self._head_bottom_margin = value
	self._head_container.height_value = self._head_top_margin + self._head_bottom_margin
end

function ALittle.Dialog.__setter:show_background(value)
	if self._background ~= nil then
		ALittle.DisplayLayout.RemoveChild(self, self._background)
	end
	self._background = value
	if self._background ~= nil then
		self._background.width_type = 4
		self._background.width_value = 0
		self._background.height_type = 4
		self._background.height_value = self._grid3.up_size
		self._background.y_type = 4
		ALittle.DisplayLayout.AddChild(self, self._background, 1)
	end
end

function ALittle.Dialog.__getter:show_background()
	return self._background
end

function ALittle.Dialog.__setter:show_head_drag(value)
	if self._head_drag ~= nil then
		self._head:RemoveChild(self._head_drag)
		self._head_drag:RemoveEventListener(___all_struct[1301789264], self, self.HandleHeadDragBegin)
		self._head_drag:RemoveEventListener(___all_struct[1337289812], self, self.HandleHeadDrag)
		self._head_drag:RemoveEventListener(___all_struct[150587926], self, self.HandleHeadDragEnd)
	end
	self._head_drag = value
	if self._head_drag ~= nil then
		self._head_drag.width_type = 4
		self._head_drag.width_value = 0
		self._head_drag.height_type = 4
		self._head_drag.height_value = 0
		self._head:AddChild(self._head_drag, 1)
		self._head_drag:AddEventListener(___all_struct[1301789264], self, self.HandleHeadDragBegin)
		self._head_drag:AddEventListener(___all_struct[1337289812], self, self.HandleHeadDrag)
		self._head_drag:AddEventListener(___all_struct[150587926], self, self.HandleHeadDragEnd)
	end
end

function ALittle.Dialog.__getter:show_head_drag()
	return self._head_drag
end

function ALittle.Dialog.__setter:show_title(value)
	if self._title ~= nil then
		self._title_text = self._title.text
		self._head_container:RemoveChild(self._title)
	end
	self._title = value
	if self._title ~= nil then
		self._title.text = self._title_text
		self._title.disabled = true
		self._title.y_type = 3
		self._title.y_value = 0
		self._title.x = 0
		self._head_container:AddChild(self._title)
	end
end

function ALittle.Dialog.__getter:show_title()
	return self._title
end

function ALittle.Dialog.__setter:title(value)
	self._title_text = value
	if self._title ~= nil then
		self._title.text = value
	end
end

function ALittle.Dialog.__getter:title()
	if self._title ~= nil then
		return self._title.text
	end
	return self._title_text
end

function ALittle.Dialog.__setter:show_close_button(value)
	if self._close_button ~= nil then
		self._head_container:RemoveChild(self._close_button)
		self._close_button:RemoveEventListener(___all_struct[-449066808], self, self.HandleCloseButtonClicked)
	end
	self._close_button = value
	if self._close_button ~= nil then
		self._close_button.y_value = 0
		self._close_button.y_type = 3
		self._head_container:AddChild(self._close_button)
		self._close_button.x_type = 4
		self._close_button.x_value = (self._grid3.up_size - self._close_button.height) / 2
		self._close_button:AddEventListener(___all_struct[-449066808], self, self.HandleCloseButtonClicked)
	end
end

function ALittle.Dialog.__getter:show_close_button()
	return self._close_button
end

function ALittle.Dialog.__setter:close_callback(value)
	self._close_callback = value
end

function ALittle.Dialog.__getter:close_callback()
	return self._close_callback
end

function ALittle.Dialog:HandleCloseButtonClicked(event)
	if self._close_callback ~= nil and not self._close_callback() then
		return
	end
	self.visible = false
end

function ALittle.Dialog:HandleHeadDragBegin(event)
	self:DispatchEvent(___all_struct[1971745271], {})
end

function ALittle.Dialog:HandleHeadDrag(event)
	self.x = self.x + (event.delta_x)
	self.y = self.y + (event.delta_y)
	local new_event = {}
	new_event.target = self
	new_event.delta_x = event.delta_x
	new_event.delta_y = event.delta_y
	self:DispatchEvent(___all_struct[1517533145], new_event)
end

function ALittle.Dialog:HandleHeadDragEnd(event)
	self:DispatchEvent(___all_struct[-1482649531], {})
end

function ALittle.Dialog:GetChildIndex(child)
	return self._body:GetChildIndex(child)
end

function ALittle.Dialog:SetChildIndex(child, index)
	return self._body:SetChildIndex(child, index)
end

function ALittle.Dialog:GetChildByIndex(index)
	return self._body:GetChildByIndex(index)
end

function ALittle.Dialog:GetChildIndex(child)
	return self._body:GetChildIndex(child)
end

function ALittle.Dialog.__getter:childs()
	return self._body.childs
end

function ALittle.Dialog.__getter:child_count()
	return self._body.child_count
end

function ALittle.Dialog:AddChild(child, index)
	if child == nil or child == self then
		return false
	end
	if child._show_parent == self._body or child._logic_parent == self then
		return true
	end
	local result = self._body:AddChild(child, index)
	child._logic_parent = self
	return result
end

function ALittle.Dialog:RemoveChild(child)
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

function ALittle.Dialog:SpliceChild(index, count)
	return self._body:SpliceChild(index, count)
end

function ALittle.Dialog:HasChild(child)
	return self._body:HasChild(child)
end

function ALittle.Dialog:RemoveAllChild()
	self._body:RemoveAllChild()
end

end