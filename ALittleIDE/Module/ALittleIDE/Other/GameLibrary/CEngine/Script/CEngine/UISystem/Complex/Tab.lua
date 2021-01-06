-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-18570489, "ALittle.UITabCloseEvent", {
name = "ALittle.UITabCloseEvent", ns_name = "ALittle", rl_name = "UITabCloseEvent", hash_code = -18570489,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

assert(ALittle.Grid3, " extends class:ALittle.Grid3 is nil")
ALittle.Tab = Lua.Class(ALittle.Grid3, "ALittle.Tab")

function ALittle.Tab:Ctor(ctrl_sys)
	___rawset(self, "_button_inner_gap", 8)
	___rawset(self, "_child_id_map", ALittle.CreateKeyWeakMap())
	___rawset(self, "_group", ALittle.CreateKeyWeakMap())
	self.type = 2
	___rawset(self, "_view", ALittle.DisplayView(self._ctrl_sys))
	self._view.height_type = 4
	self._view.width_type = 4
	___rawset(self, "_linear", ALittle.Linear(self._ctrl_sys))
	self._linear.type = 1
	self._linear.height_type = 4
	self._linear.y_type = 4
	self._view:AddChild(self._linear)
	___rawset(self, "_view_start", 0)
	___rawset(self, "_view_margin", 0)
	local show_up = ALittle.DisplayLayout(self._ctrl_sys)
	show_up:AddChild(self._view)
	self.show_up = show_up
	self.show_center = ALittle.DisplayLayout(self._ctrl_sys)
	___rawset(self, "_pickup_rect", true)
	___rawset(self, "_pickup_child", true)
	___rawset(self, "_tab_index", 0)
	___rawset(self, "_child_width_margin", 0)
end

function ALittle.Tab:RefreshView()
	if self._radiobutton_style == nil or self._text_style == nil or self._closebutton_style == nil or self._selected_text_style == nil or self._selected_closebutton_style == nil then
		return
	end
	local child_list = self._linear.childs
	for k, v in ___ipairs(child_list) do
		local childs = v.childs
		childs[1]:RemoveEventListener(___all_struct[958494922], self, self.HandleRadioButtonChanged)
		childs[1]:RemoveEventListener(___all_struct[1337289812], self, self.HandleRadioButtonDrag)
		childs[1]:RemoveEventListener(___all_struct[1301789264], self, self.HandleRadioButtonDragBegin)
		childs[1]:RemoveEventListener(___all_struct[150587926], self, self.HandleRadioButtonDragEnd)
		childs[1]:RemoveEventListener(___all_struct[-1330840], self, self.HandleRadioButtonMClick)
		childs[1]:RemoveEventListener(___all_struct[-641444818], self, self.HandleRadioButtonRButtonDown)
		childs[1]:RemoveEventListener(___all_struct[-1604617962], self, self.HandleRadioButtonKeyDown)
		childs[3]:RemoveEventListener(___all_struct[-449066808], self, self.HandleCloseButtonClick)
		childs[5]:RemoveEventListener(___all_struct[-449066808], self, self.HandleCloseButtonClick)
		childs[1].group = nil
	end
	self._linear:RemoveAllChild()
	local show_center = self.show_center
	child_list = show_center.childs
	for k, v in ___ipairs(child_list) do
		local radiobutton = self._ctrl_sys:CreateControl(self._radiobutton_style)
		local text = self._ctrl_sys:CreateControl(self._text_style)
		local closebutton = self._ctrl_sys:CreateControl(self._closebutton_style)
		local selected_text = self._ctrl_sys:CreateControl(self._selected_text_style)
		local selected_closebutton = self._ctrl_sys:CreateControl(self._selected_closebutton_style)
		if radiobutton ~= nil and text ~= nil and closebutton ~= nil and selected_text ~= nil and selected_closebutton ~= nil then
			local simplelayout = ALittle.DisplayLayout(self._ctrl_sys)
			radiobutton.selected = (self._tab_index == k)
			radiobutton:AddEventListener(___all_struct[958494922], self, self.HandleRadioButtonChanged)
			radiobutton:AddEventListener(___all_struct[1337289812], self, self.HandleRadioButtonDrag)
			radiobutton:AddEventListener(___all_struct[1301789264], self, self.HandleRadioButtonDragBegin)
			radiobutton:AddEventListener(___all_struct[150587926], self, self.HandleRadioButtonDragEnd)
			radiobutton:AddEventListener(___all_struct[-1330840], self, self.HandleRadioButtonMClick)
			radiobutton:AddEventListener(___all_struct[-641444818], self, self.HandleRadioButtonRButtonDown)
			radiobutton:AddEventListener(___all_struct[-1604617962], self, self.HandleRadioButtonKeyDown)
			radiobutton.group = self._group
			radiobutton.width_type = 4
			radiobutton.height_type = 4
			v.visible = radiobutton.selected
			text.text = self._child_id_map[v]
			text.disabled = true
			text.y_type = 3
			text.y_value = 2
			text.x = self._button_inner_gap
			text.visible = not radiobutton.selected
			selected_text.text = self._child_id_map[v]
			selected_text.disabled = true
			selected_text.y_type = 3
			selected_text.y_value = 2
			selected_text.x = self._button_inner_gap
			selected_text.visible = radiobutton.selected
			closebutton:AddEventListener(___all_struct[-449066808], self, self.HandleCloseButtonClick)
			closebutton.y_type = 3
			closebutton.y_value = 2
			closebutton.x = text.x + text.width + self._button_inner_gap
			closebutton.visible = not radiobutton.selected
			selected_closebutton:AddEventListener(___all_struct[-449066808], self, self.HandleCloseButtonClick)
			selected_closebutton.y_type = 3
			selected_closebutton.y_value = 2
			selected_closebutton.x = selected_text.x + selected_text.width + self._button_inner_gap
			selected_closebutton.visible = radiobutton.selected
			simplelayout.width = self._button_inner_gap * 3 + text.width + closebutton.width
			self._linear:AddChild(simplelayout)
			simplelayout:AddChild(radiobutton)
			simplelayout:AddChild(text)
			simplelayout:AddChild(closebutton)
			simplelayout:AddChild(selected_text)
			simplelayout:AddChild(selected_closebutton)
		end
	end
end

function ALittle.Tab.__setter:radiobutton_style(value)
	if self._radiobutton_style == value then
		return
	end
	self._radiobutton_style = value
	self:RefreshView()
end

function ALittle.Tab.__getter:radiobutton_style()
	return self._radiobutton_style
end

function ALittle.Tab.__setter:closebutton_style(value)
	if self._closebutton_style == value then
		return
	end
	self._closebutton_style = value
	self:RefreshView()
end

function ALittle.Tab.__getter:closebutton_style()
	return self._closebutton_style
end

function ALittle.Tab.__setter:selected_closebutton_style(value)
	if self._selected_closebutton_style == value then
		return
	end
	self._selected_closebutton_style = value
	self:RefreshView()
end

function ALittle.Tab.__getter:selected_closebutton_style()
	return self._selected_closebutton_style
end

function ALittle.Tab.__setter:text_style(value)
	if self._text_style == value then
		return
	end
	self._text_style = value
	self:RefreshView()
end

function ALittle.Tab.__getter:text_style()
	return self._text_style
end

function ALittle.Tab.__setter:selected_text_style(value)
	if self._selected_text_style == value then
		return
	end
	self._selected_text_style = value
	self:RefreshView()
end

function ALittle.Tab.__getter:selected_text_style()
	return self._selected_text_style
end

function ALittle.Tab.__setter:show_head_background(value)
	if self._head_background ~= nil then
		self._view:RemoveChild(self._head_background)
	end
	self._head_background = value
	if self._head_background ~= nil then
		self._head_background.width_type = 4
		self._head_background.width_value = 0
		self._head_background.height_type = 4
		self._head_background.height_value = 0
		self._view:AddChild(self._head_background, 1)
	end
end

function ALittle.Tab.__getter:show_head_background()
	return self._head_background
end

function ALittle.Tab.__setter:button_gap(value)
	self._linear.gap = value
end

function ALittle.Tab.__getter:button_gap()
	return self._linear.gap
end

function ALittle.Tab.__setter:button_start(value)
	self._view.x = value
end

function ALittle.Tab.__getter:button_start()
	return self._view.x
end

function ALittle.Tab.__setter:button_margin(value)
	self._linear.height_value = value
end

function ALittle.Tab.__getter:button_margin()
	return self._linear.height_value
end

function ALittle.Tab.__setter:child_width_margin(value)
	self._child_width_margin = value
	local show_center = self.show_center
	local childs = show_center.childs
	for k, v in ___ipairs(childs) do
		v.width_value = self._child_width_margin
	end
end

function ALittle.Tab.__getter:child_width_margin()
	return self._child_width_margin
end

function ALittle.Tab.__setter:head_size(value)
	self.up_size = value
end

function ALittle.Tab.__getter:head_size()
	return self.up_size
end

function ALittle.Tab.__setter:close_callback(value)
	self._close_callback = value
end

function ALittle.Tab.__getter:close_callback()
	return self._close_callback
end

function ALittle.Tab.__setter:close_post_callback(value)
	self._close_post_callback = value
end

function ALittle.Tab.__getter:close_post_callback()
	return self._close_post_callback
end

function ALittle.Tab.__setter:drag_callback(value)
	self._drag_callback = value
end

function ALittle.Tab.__getter:drag_callback()
	return self._drag_callback
end

function ALittle.Tab.__setter:drag_post_callback(value)
	self._drag_post_callback = value
end

function ALittle.Tab.__getter:drag_post_callback()
	return self._drag_post_callback
end

function ALittle.Tab.__getter:view_margin()
	return self._view.width_value
end

function ALittle.Tab.__setter:view_margin(value)
	self._view.width_value = value
end

function ALittle.Tab.__getter:view()
	return self._view
end

function ALittle.Tab.__getter:view_linear()
	return self._linear
end

function ALittle.Tab:GetChildIndex(child)
	return self.show_center:GetChildIndex(child)
end

function ALittle.Tab:SetChildIndex(child, index)
	local show_center = self.show_center
	local cur_index = show_center:GetChildIndex(child)
	if index > show_center.child_count then
		index = show_center.child_count
	end
	if cur_index == index then
		return true
	end
	local linear = self._linear
	local linear_childs = linear.childs
	local tab_child = self.tab
	local button_child = linear_childs[cur_index]
	if button_child ~= nil then
		linear:SetChildIndex(button_child, index)
	end
	local show_center_childs = show_center.childs
	local body_child = show_center_childs[cur_index]
	show_center:SetChildIndex(body_child, index)
	self._tab_index = show_center:GetChildIndex(tab_child)
	return true
end

function ALittle.Tab:GetChildByIndex(index)
	return self.show_center:GetChildByIndex(index)
end

function ALittle.Tab:GetChildIndex(child)
	return self.show_center:GetChildIndex(child)
end

function ALittle.Tab.__getter:childs()
	local show_center = self.show_center
	return show_center.childs
end

function ALittle.Tab.__getter:child_count()
	local show_center = self.show_center
	return show_center.child_count
end

function ALittle.Tab:AddChild(child, index)
	if child == nil or child == self then
		return false
	end
	if child._show_parent == self.show_center or child._logic_parent == self then
		return true
	end
	if child._logic_parent ~= nil then
		child._logic_parent:RemoveChild(child)
	elseif child._show_parent ~= nil then
		child._show_parent:RemoveChild(child)
	end
	local show_center = self.show_center
	show_center:AddChild(child, index)
	child._logic_parent = self
	child.x = 0
	child.y = 0
	child.width_type = 4
	child.width_value = self._child_width_margin
	child.height_type = 4
	child.height_value = 0
	child.x_type = 4
	self._child_id_map[child] = child.description
	if self._child_id_map[child] == nil then
		self._child_id_map[child] = ""
	end
	if self._radiobutton_style == nil or self._text_style == nil or self._closebutton_style == nil or self._selected_text_style == nil or self._selected_closebutton_style == nil then
		return true
	end
	local radiobutton = self._ctrl_sys:CreateControl(self._radiobutton_style)
	local text = self._ctrl_sys:CreateControl(self._text_style)
	local closebutton = self._ctrl_sys:CreateControl(self._closebutton_style)
	local selected_text = self._ctrl_sys:CreateControl(self._selected_text_style)
	local selected_closebutton = self._ctrl_sys:CreateControl(self._selected_closebutton_style)
	if radiobutton ~= nil and text ~= nil and closebutton ~= nil and selected_text ~= nil and selected_closebutton ~= nil then
		local simplelayout = ALittle.DisplayLayout(self._ctrl_sys)
		radiobutton:AddEventListener(___all_struct[958494922], self, self.HandleRadioButtonChanged)
		radiobutton:AddEventListener(___all_struct[1337289812], self, self.HandleRadioButtonDrag)
		radiobutton:AddEventListener(___all_struct[1301789264], self, self.HandleRadioButtonDragBegin)
		radiobutton:AddEventListener(___all_struct[150587926], self, self.HandleRadioButtonDragEnd)
		radiobutton:AddEventListener(___all_struct[-1330840], self, self.HandleRadioButtonMClick)
		radiobutton:AddEventListener(___all_struct[-641444818], self, self.HandleRadioButtonRButtonDown)
		radiobutton:AddEventListener(___all_struct[-1604617962], self, self.HandleRadioButtonKeyDown)
		radiobutton.group = self._group
		radiobutton.width_type = 4
		radiobutton.width_value = 0
		radiobutton.height_type = 4
		radiobutton.height_value = 0
		child.visible = radiobutton.selected
		text.text = self._child_id_map[child]
		text.disabled = true
		text.y_type = 3
		text.y_value = 2
		text.x = self._button_inner_gap
		text.visible = not radiobutton.selected
		selected_text.text = self._child_id_map[child]
		selected_text.disabled = true
		selected_text.y_type = 3
		selected_text.y_value = 2
		selected_text.x = self._button_inner_gap
		selected_text.visible = radiobutton.selected
		closebutton:AddEventListener(___all_struct[-449066808], self, self.HandleCloseButtonClick)
		closebutton.y_type = 3
		closebutton.y_value = 2
		closebutton.x = text.x + text.width + self._button_inner_gap
		closebutton.visible = not radiobutton.selected
		selected_closebutton:AddEventListener(___all_struct[-449066808], self, self.HandleCloseButtonClick)
		selected_closebutton.y_type = 3
		selected_closebutton.y_value = 2
		selected_closebutton.x = selected_text.x + selected_text.width + self._button_inner_gap
		selected_closebutton.visible = radiobutton.selected
		simplelayout.width = self._button_inner_gap * 3 + text.width + closebutton.width
		self._linear:AddChild(simplelayout, index)
		simplelayout:AddChild(radiobutton)
		simplelayout:AddChild(text)
		simplelayout:AddChild(closebutton)
		simplelayout:AddChild(selected_text)
		simplelayout:AddChild(selected_closebutton)
	end
	if self._tab_index <= 0 then
		self.tab_index = 1
	elseif index ~= nil and self._tab_index >= index then
		self._tab_index = self._tab_index + 1
	end
	return true
end

function ALittle.Tab:RemoveChild(child)
	if child == nil then
		return false
	end
	if child._show_parent ~= self.show_center and child._logic_parent ~= self then
		return false
	end
	local show_center = self.show_center
	local index = show_center:GetChildIndex(child)
	if index == 0 then
		return false
	end
	show_center:RemoveChild(child)
	child.visible = true
	self._child_id_map[child] = nil
	local simplelayout = self._linear:GetChildByIndex(index)
	if simplelayout ~= nil then
		local layout_childs = simplelayout.childs
		layout_childs[1]:RemoveEventListener(___all_struct[958494922], self, self.HandleRadioButtonChanged)
		layout_childs[1]:RemoveEventListener(___all_struct[1337289812], self, self.HandleRadioButtonDrag)
		layout_childs[1]:RemoveEventListener(___all_struct[1301789264], self, self.HandleRadioButtonDragBegin)
		layout_childs[1]:RemoveEventListener(___all_struct[150587926], self, self.HandleRadioButtonDragEnd)
		layout_childs[1]:RemoveEventListener(___all_struct[-1330840], self, self.HandleRadioButtonMClick)
		layout_childs[1]:RemoveEventListener(___all_struct[-641444818], self, self.HandleRadioButtonRButtonDown)
		layout_childs[1]:RemoveEventListener(___all_struct[-1604617962], self, self.HandleRadioButtonKeyDown)
		layout_childs[3]:RemoveEventListener(___all_struct[-449066808], self, self.HandleCloseButtonClick)
		layout_childs[5]:RemoveEventListener(___all_struct[-449066808], self, self.HandleCloseButtonClick)
		layout_childs[1].group = nil
		self._linear:RemoveChild(simplelayout)
	end
	local new_index = 0
	if self._tab_index == index then
		new_index = index
	elseif self._tab_index > index then
		new_index = self._tab_index - 1
	else
		new_index = self._tab_index
	end
	if new_index > show_center.child_count then
		new_index = show_center.child_count
	elseif new_index < 0 then
		new_index = 0
	end
	self.tab_index = new_index
	return true
end

function ALittle.Tab:SpliceChild(index, count)
	local remain_count = self._child_count - index + 1
	if count == nil then
		count = remain_count
	end
	if count <= 0 then
		return 0
	end
	if count > remain_count then
		count = remain_count
	end
	local show_center = self.show_center
	local endv = index + count
	local i = index
	while true do
		if not(i < endv) then break end
		local child = show_center:GetChildByIndex(i)
		if child == nil then
			break
		end
		child.visible = true
		self._child_id_map[child] = nil
		local simplelayout = self._linear:GetChildByIndex(index)
		if simplelayout ~= nil then
			local layout_childs = simplelayout.childs
			layout_childs[1]:RemoveEventListener(___all_struct[958494922], self, self.HandleRadioButtonChanged)
			layout_childs[1]:RemoveEventListener(___all_struct[1337289812], self, self.HandleRadioButtonDrag)
			layout_childs[1]:RemoveEventListener(___all_struct[1301789264], self, self.HandleRadioButtonDragBegin)
			layout_childs[1]:RemoveEventListener(___all_struct[150587926], self, self.HandleRadioButtonDragEnd)
			layout_childs[1]:RemoveEventListener(___all_struct[-1330840], self, self.HandleRadioButtonMClick)
			layout_childs[1]:RemoveEventListener(___all_struct[-641444818], self, self.HandleRadioButtonRButtonDown)
			layout_childs[1]:RemoveEventListener(___all_struct[-1604617962], self, self.HandleRadioButtonKeyDown)
			layout_childs[3]:RemoveEventListener(___all_struct[-449066808], self, self.HandleCloseButtonClick)
			layout_childs[5]:RemoveEventListener(___all_struct[-449066808], self, self.HandleCloseButtonClick)
			layout_childs[1].group = nil
		end
		i = i+(1)
	end
	self._linear:SpliceChild(index, count)
	local result = show_center:SpliceChild(index, count)
	local new_index = 0
	if self._tab_index >= index and self._tab_index < endv then
		new_index = index
	elseif self._tab_index >= endv then
		new_index = self._tab_index - result
	else
		new_index = self._tab_index
	end
	if new_index > show_center.child_count then
		new_index = show_center.child_count
	elseif new_index < 0 then
		new_index = 0
	end
	self.tab_index = new_index
	return result
end

function ALittle.Tab:HasChild(child)
	local show_center = self.show_center
	return show_center:HasChild(child)
end

function ALittle.Tab:RemoveAllChild()
	self._linear:RemoveAllChild()
	local show_center = self.show_center
	local childs = show_center.childs
	for k, v in ___ipairs(childs) do
		v.visible = true
	end
	show_center:RemoveAllChild()
	self._child_id_map = {}
	self._tab_index = 0
end

function ALittle.Tab:HandleRadioButtonChanged(event)
	local button = event.target
	if button.selected then
		local show_center = self.show_center
		local childs = show_center.childs
		for k, v in ___ipairs(childs) do
			v.visible = false
		end
		local simplelayout = button.parent
		local index = self._linear:GetChildIndex(simplelayout)
		local show_center_childs = show_center.childs
		show_center_childs[index].visible = true
		local layout_childs = simplelayout.childs
		layout_childs[3].visible = false
		layout_childs[2].visible = false
		if layout_childs[5].disabled == false then
			layout_childs[5].visible = true
		end
		layout_childs[4].visible = true
		self._tab_index = index
		self:DispatchEvent(___all_struct[444989011], {})
	else
		local simplelayout = button.parent
		local layout_childs = simplelayout.childs
		if layout_childs[3].disabled == false then
			layout_childs[3].visible = true
		end
		layout_childs[2].visible = true
		layout_childs[5].visible = false
		layout_childs[4].visible = false
	end
end

function ALittle.Tab:HandleCloseButtonClick(event)
	local simplelayout = event.target._show_parent
	local index = self._linear:GetChildIndex(simplelayout)
	local show_center = self.show_center
	local show_center_childs = show_center.childs
	local child = show_center_childs[index]
	if self._close_callback ~= nil and self._close_callback(child) == false then
		return
	end
	self:RemoveChild(child)
	self:DispatchEvent(___all_struct[-18570489], {})
	if self._close_post_callback ~= nil then
		self._close_post_callback(child)
	end
end

function ALittle.Tab:HandleRadioButtonDragBegin(event)
	local simplelayout = event.target._show_parent
	local control_x
	local control_y
	control_x, control_y = simplelayout:LocalToGlobal()
	self._tab_image = ALittle.EffectImage(self._ctrl_sys)
	self._tab_image:Action(simplelayout)
	A_LayerManager:AddToTip(self._tab_image)
	self._tab_image.x = control_x
	self._tab_image.y = control_y
	self._tab_image.alpha = 0.9
end

function ALittle.Tab:HandleRadioButtonDrag(event)
	if self._tab_image == nil then
		return
	end
	self._tab_image.x = self._tab_image.x + event.delta_x
	self._tab_image.y = self._tab_image.y + event.delta_y
end

function ALittle.Tab:HandleRadioButtonDragEnd(event)
	local target_index = self._linear.child_count
	if self._scale_x > 0 then
		local linear_x
		local linear_y
		linear_x, linear_y = self._linear:LocalToGlobal()
		local delta_x = (event.abs_x - linear_x) / self._scale_x
		local child_list = self._linear.childs
		for k, v in ___ipairs(child_list) do
			if delta_x < v.x + v.width / 2 then
				target_index = k
				break
			end
		end
	end
	local simplelayout = event.target._show_parent
	local index = self._linear:GetChildIndex(simplelayout)
	local show_center = self.show_center
	local show_center_childs = show_center.childs
	local child = show_center_childs[index]
	if self._drag_callback ~= nil and self._drag_callback(child, target_index) == false then
		return
	end
	self._linear:SetChildIndex(simplelayout, target_index)
	show_center:SetChildIndex(child, target_index)
	if self._drag_post_callback ~= nil then
		self._drag_post_callback(child)
	end
	if self._tab_image ~= nil then
		A_LayerManager:RemoveFromTip(self._tab_image)
		self._tab_image:Clear()
		self._tab_image = nil
	end
end

function ALittle.Tab:HandleRadioButtonMClick(event)
	local simplelayout = event.target._show_parent
	local layout_childs = simplelayout.childs
	if layout_childs[3].disabled and layout_childs[5].disabled then
		return
	end
	local index = self._linear:GetChildIndex(simplelayout)
	local show_center = self.show_center
	local show_center_childs = show_center.childs
	local child = show_center_childs[index]
	if self._close_callback ~= nil and self._close_callback(child) == false then
		return
	end
	self:RemoveChild(child)
	self:DispatchEvent(___all_struct[-18570489], {})
	if self._close_post_callback ~= nil then
		self._close_post_callback(child)
	end
end

function ALittle.Tab:HandleRadioButtonRButtonDown(event)
	local simplelayout = event.target._show_parent
	local index = self._linear:GetChildIndex(simplelayout)
	local show_center = self.show_center
	local show_center_childs = show_center.childs
	local child = show_center_childs[index]
	local e = {}
	e.target = child
	self:DispatchEvent(___all_struct[-641444818], e)
end

function ALittle.Tab:HandleRadioButtonKeyDown(event)
	local simplelayout = event.target._show_parent
	local index = self._linear:GetChildIndex(simplelayout)
	local show_center = self.show_center
	local show_center_childs = show_center.childs
	local child = show_center_childs[index]
	local e = {}
	e.target = child
	e.mod = event.mod
	e.sym = event.sym
	e.scancode = event.scancode
	self:DispatchEvent(___all_struct[-1604617962], e)
	event.handled = e.handled
end

function ALittle.Tab:SetChildText(child, text)
	if self._radiobutton_style == nil then
		return
	end
	local show_center = self.show_center
	local index = show_center:GetChildIndex(child)
	if index == 0 then
		return
	end
	local simplelayout = self._linear:GetChildByIndex(index)
	if simplelayout ~= nil then
		local childs = simplelayout.childs
		local text_control = childs[2]
		local closebutton = childs[3]
		local selected_text_control = childs[4]
		local selected_closebutton = childs[5]
		text_control.text = text
		selected_text_control.text = text
		closebutton.x = text_control.x + text_control.width + self._button_inner_gap
		selected_closebutton.x = selected_text_control.x + selected_text_control.width + self._button_inner_gap
		simplelayout.width = self._button_inner_gap * 3 + text_control.width + closebutton.width
		self._child_id_map[child] = text
		self._linear:Layout(1)
	end
end

function ALittle.Tab:GetChildText(child)
	return self._child_id_map[child]
end

function ALittle.Tab:HasChildText(text)
	for k, v in ___pairs(self._child_id_map) do
		if v == text then
			return true
		end
	end
	return false
end

function ALittle.Tab:GetChildByText(text)
	for k, v in ___pairs(self._child_id_map) do
		if v == text then
			return k
		end
	end
	return nil
end

function ALittle.Tab.__setter:tab(child)
	local show_center = self.show_center
	local index = show_center:GetChildIndex(child)
	if index == 0 then
		return
	end
	self.tab_index = index
end

function ALittle.Tab.__getter:tab()
	local show_center = self.show_center
	local show_center_childs = show_center.childs
	return show_center_childs[self._tab_index]
end

function ALittle.Tab.__setter:tab_index(index)
	local show_center = self.show_center
	local show_center_childs = show_center.childs
	if self._tab_index ~= 0 then
		local cur_child = show_center_childs[self._tab_index]
		if cur_child ~= nil then
			cur_child.visible = false
		end
		local simplelayout = self._linear:GetChildByIndex(self._tab_index)
		if simplelayout ~= nil then
			local childs = simplelayout.childs
			childs[1].selected = false
			childs[2].visible = true
			if childs[3].disabled == false then
				childs[3].visible = true
			end
			childs[4].visible = false
			childs[5].visible = false
		end
		self._tab_index = 0
	end
	self._tab_index = index
	if self._tab_index ~= 0 then
		local child = show_center_childs[self._tab_index]
		if child == nil then
			return
		end
		child.visible = true
		local simplelayout = self._linear:GetChildByIndex(self._tab_index)
		if simplelayout ~= nil then
			local childs = simplelayout.childs
			childs[1].selected = true
			childs[2].visible = false
			childs[3].visible = false
			childs[4].visible = true
			if childs[5].disabled == false then
				childs[5].visible = true
			end
		end
	end
	if self._tab_index < 1 or self._tab_index > show_center.child_count then
		self._tab_index = 0
	end
end

function ALittle.Tab.__getter:tab_index()
	return self._tab_index
end

function ALittle.Tab:DisableCloseButton(child)
	local show_center = self.show_center
	local index = show_center:GetChildIndex(child)
	if index == 0 then
		return
	end
	local linear_childs = self._linear.childs
	local simplelayout = linear_childs[index]
	if simplelayout == nil then
		return
	end
	local layout_childs = simplelayout.childs
	layout_childs[3].visible = false
	layout_childs[3].disabled = true
	layout_childs[2].x_type = 3
	layout_childs[2].x_value = 0
	layout_childs[5].visible = false
	layout_childs[5].disabled = true
	layout_childs[4].x_type = 3
	layout_childs[4].x_value = 0
end

function ALittle.Tab:DisableAllCloseButton()
	local show_center = self.show_center
	local count = show_center.child_count
	local linear_childs = self._linear.childs
	local index = 1
	while true do
		if not(index <= count) then break end
		local simplelayout = linear_childs[index]
		if simplelayout == nil then
			return
		end
		local layout_childs = simplelayout.childs
		layout_childs[3].visible = false
		layout_childs[3].disabled = true
		layout_childs[2].x_type = 3
		layout_childs[2].x_value = 0
		layout_childs[5].visible = false
		layout_childs[5].disabled = true
		layout_childs[4].x_type = 3
		layout_childs[4].x_value = 0
		index = index+(1)
	end
end

function ALittle.Tab:EnableCloseButton(child)
	local show_center = self.show_center
	local index = show_center:GetChildIndex(child)
	if index == 0 then
		return
	end
	local linear_childs = self._linear.childs
	local simplelayout = linear_childs[index]
	if simplelayout == nil then
		return
	end
	local layout_childs = simplelayout.childs
	layout_childs[3].visible = not layout_childs[1].selected
	layout_childs[3].disabled = false
	layout_childs[2].x_type = 1
	layout_childs[2].x = self._button_inner_gap
	layout_childs[5].visible = layout_childs[1].selected
	layout_childs[5].disabled = false
	layout_childs[4].x_type = 1
	layout_childs[4].x = self._button_inner_gap
end

function ALittle.Tab:GetChildHead(child)
	local show_center = self.show_center
	local index = show_center:GetChildIndex(child)
	if index == 0 then
		return nil
	end
	local linear_childs = self._linear.childs
	return linear_childs[index]
end

end