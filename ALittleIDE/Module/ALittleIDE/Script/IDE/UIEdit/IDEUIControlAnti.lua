-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name = "ALittle.UIChangedEvent", ns_name = "ALittle", rl_name = "UIChangedEvent", hash_code = 958494922,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name = "ALittle.UIClickEvent", ns_name = "ALittle", rl_name = "UIClickEvent", hash_code = -449066808,
name_list = {"target","is_drag","count"},
type_list = {"ALittle.DisplayObject","bool","int"},
option_map = {}
})
ALittle.RegStruct(-431205740, "ALittle.UIResizeEvent", {
name = "ALittle.UIResizeEvent", ns_name = "ALittle", rl_name = "UIResizeEvent", hash_code = -431205740,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEAntiFrameLinearItem = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEAntiFrameLinearItem")

function ALittleIDE.IDEAntiFrameLinearItem:Init(panel, frame)
	self._panel = panel
	self._frame_text.text = frame
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEAntiFrameLinkItem = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEAntiFrameLinkItem")

function ALittleIDE.IDEAntiFrameLinkItem:Init(panel, info)
	self._panel = panel
	if info ~= nil then
		if info.link ~= nil then
			self._link_input.text = info.link
		end
		if info.attribute ~= nil then
			self._attribute_dropdown.text = info.attribute
		end
		if info.init ~= nil then
			if info.init == true then
				self._init_input.text = "true"
			elseif info.init == false then
				self._init_input.text = "false"
			else
				self._init_input.text = info.init
			end
		end
	end
end

function ALittleIDE.IDEAntiFrameLinkItem:HandleDeleteClick(event)
	self._panel:RemoveAttr(self._panel.anti_link_linear:GetChildIndex(self))
end

function ALittleIDE.IDEAntiFrameLinkItem:HandleLinkChanged(event)
	local info = self._panel:GetCurLoopInfo()
	if info == nil then
		return
	end
	local child_index = self._panel.anti_link_linear:GetChildIndex(self)
	if child_index <= 0 then
		return
	end
	local child = info.childs[child_index]
	child.link = self._link_input.text
	self._panel.tab_child.save = false
end

function ALittleIDE.IDEAntiFrameLinkItem:HandleAttributeChanged(event)
	local info = self._panel:GetCurLoopInfo()
	if info == nil then
		return
	end
	local child_index = self._panel.anti_link_linear:GetChildIndex(self)
	if child_index <= 0 then
		return
	end
	local child = info.childs[child_index]
	child.attribute = self._attribute_dropdown.text
	if self._init_input.text == "" then
		child.init = nil
	else
		if self._attribute_dropdown.text == "visible" or self._attribute_dropdown.text == "disabled" then
			child.init = self._init_input.text == "true"
		else
			child.init = ALittle.Math_ToDouble(self._init_input.text)
		end
	end
	self._panel.tab_child.save = false
end

function ALittleIDE.IDEAntiFrameLinkItem:HandleInitChanged(event)
	local info = self._panel:GetCurLoopInfo()
	if info == nil then
		return
	end
	local child_index = self._panel.anti_link_linear:GetChildIndex(self)
	if child_index <= 0 then
		return
	end
	local child = info.childs[child_index]
	if self._init_input.text == "" then
		child.init = nil
	else
		if self._attribute_dropdown.text == "visible" or self._attribute_dropdown.text == "disabled" then
			child.init = self._init_input.text == "true"
		else
			child.init = ALittle.Math_ToDouble(self._init_input.text)
		end
	end
	self._panel.tab_child.save = false
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEAntiFrameLoopItem = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEAntiFrameLoopItem")

function ALittleIDE.IDEAntiFrameLoopItem:Init(item, info)
	self._item = item
	self._button.drag_trans_target = self._item.panel.anti_screen
	self._bg_quad.drag_trans_target = self._item.panel.anti_screen
	self._info = info
	self._button.group = self._item.panel.loop_group
	self:UpdateText()
	self:UpdateShow()
end

function ALittleIDE.IDEAntiFrameLoopItem.__getter:info()
	return self._info
end

function ALittleIDE.IDEAntiFrameLoopItem.__getter:button()
	return self._button
end

function ALittleIDE.IDEAntiFrameLoopItem.__getter:item()
	return self._item
end

function ALittleIDE.IDEAntiFrameLoopItem:UpdateText()
	local value = "null"
	if self._info.target == true then
		value = "true"
	elseif self._info.target == false then
		value = "false"
	else
		value = ALittle.String_ToString(self._info.target)
	end
	if self._info.clazz == "LoopLinear" then
		self._button.text = "L(" .. value .. ")"
	elseif self._info.clazz == "LoopAttribute" then
		self._button.text = "A(" .. value .. ")"
	elseif self._info.clazz == "LoopRit" then
		self._button.text = "R(" .. value .. ")"
	end
end

function ALittleIDE.IDEAntiFrameLoopItem:UpdateShow()
	local width = self._item:CalcWidthByTime(self._info.total_time + self._info.delay_time)
	self._button.width = self._item:CalcWidthByTime(self._info.total_time)
	if self._button.width < self._item.panel._MIN_WIDTH then
		self._button.width = self._item.panel._MIN_WIDTH
	end
	if width < self._button.width then
		self._button.x_value = (width - self._button.width) / 2
	else
		self._button.x_value = 0
	end
	self.width = width
end

function ALittleIDE.IDEAntiFrameLoopItem.__getter:info()
	return self._info
end

function ALittleIDE.IDEAntiFrameLoopItem:HandleButtonChanged(event)
	self._item.panel:ShowAntiLoop(self)
end

function ALittleIDE.IDEAntiFrameLoopItem:HandleKeyDown(event)
	if event.sym == 1073741904 then
		local child_index = self._item.container:GetChildIndex(self)
		if child_index > 1 then
			child_index = child_index - 1
			local item = self._item.container:GetChildByIndex(child_index)
			item._button.selected = true
			self._item.panel:ShowAntiLoop(item)
			item._button.focus = true
		end
		event.handled = true
	elseif event.sym == 1073741903 then
		local child_index = self._item.container:GetChildIndex(self)
		if child_index < self._item.container.child_count then
			child_index = child_index + 1
			local item = self._item.container:GetChildByIndex(child_index)
			item._button.selected = true
			self._item.panel:ShowAntiLoop(item)
			item._button.focus = true
		end
		event.handled = true
	end
end

function ALittleIDE.IDEAntiFrameLoopItem:HandleRButtonDown(event)
	ALittleIDE.g_IDECenter.center.control_anti:ShowAntiLoopMenu(self)
end

function ALittleIDE.IDEAntiFrameLoopItem.ValueToString(value)
	if value == nil then
		return ""
	end
	if value == true then
		return "true"
	end
	if value == false then
		return "false"
	end
	return ALittle.String_ToString(value)
end

function ALittleIDE.IDEAntiFrameLoopItem.StringToValue(attribute, value)
	if value == "" then
		return nil
	end
	if attribute == "visible" or attribute == "disabled" then
		if value == "true" then
			return true
		else
			return false
		end
	else
		return ALittle.Math_ToDouble(value)
	end
end

function ALittleIDE.IDEAntiFrameLoopItem:SetTargetValue(text)
	local old_value = self._info.target
	self._info.target = ALittleIDE.IDEAntiFrameLoopItem.StringToValue(self._item.info.attribute, text)
	self:UpdateText()
	if old_value ~= self._info.target then
		local old_value_string = ALittleIDE.IDEAntiFrameLoopItem.ValueToString(old_value)
		local new_value_string = ALittleIDE.IDEAntiFrameLoopItem.ValueToString(self._info.target)
		local revoke = ALittleIDE.IDEAntiLoopTargetValueChangeRevoke(self, old_value_string, new_value_string)
		self._item.panel.tab_child.revoke_list:PushRevoke(revoke)
		self._item.panel.tab_child.save = false
	end
end

function ALittleIDE.IDEAntiFrameLoopItem:SetTotalTime(time)
	if self._info.total_time == time then
		return
	end
	local old_time = self._info.total_time
	self._info.total_time = time
	if self._info.total_time == nil then
		self._info.total_time = 0
	end
	self:UpdateShow()
	self:DispatchEvent(___all_struct[-431205740], {})
	local revoke = ALittleIDE.IDEAntiLoopTotalTimeChangeRevoke(self, old_time, self._info.total_time)
	self._item.panel.tab_child.revoke_list:PushRevoke(revoke)
	self._item.panel.tab_child.save = false
end

function ALittleIDE.IDEAntiFrameLoopItem:SetDelayTime(time)
	if self._info.delay_time == time then
		return
	end
	local old_time = self._info.delay_time
	self._info.delay_time = time
	if self._info.delay_time == nil then
		if self._info.clazz == "LoopAttribute" then
			self._info.delay_time = 1
		else
			self._info.delay_time = 0
		end
	end
	self:UpdateShow()
	self:DispatchEvent(___all_struct[-431205740], {})
	local revoke = ALittleIDE.IDEAntiLoopDelayTimeChangeRevoke(self, old_time, self._info.delay_time)
	self._item.panel.tab_child.revoke_list:PushRevoke(revoke)
	self._item.panel.tab_child.save = false
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEAntiFrameAntiItem = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEAntiFrameAntiItem")

function ALittleIDE.IDEAntiFrameAntiItem:Init(panel, info)
	self._panel = panel
	self._bg_quad.drag_trans_target = self._panel.anti_screen
	self._info = info
	if self._info.childs == nil then
		self._info.childs = {}
	end
	for index, child in ___ipairs(self._info.childs) do
		local loop_item = ALittleIDE.g_Control:CreateControl("ide_anti_screen_loop_item")
		loop_item:Init(self, child)
		self._container:AddChild(loop_item)
	end
end

function ALittleIDE.IDEAntiFrameAntiItem.__getter:panel()
	return self._panel
end

function ALittleIDE.IDEAntiFrameAntiItem.__getter:info()
	return self._info
end

function ALittleIDE.IDEAntiFrameAntiItem.__getter:container()
	return self._container
end

function ALittleIDE.IDEAntiFrameAntiItem:CalcTimeByWidth(width)
	return ALittle.Math_Floor(width / self._panel._FRAME_WIDTH * self._panel._FRAME_TIME)
end

function ALittleIDE.IDEAntiFrameAntiItem:CalcWidthByTime(time)
	return time / self._panel._FRAME_TIME * self._panel._FRAME_WIDTH
end

function ALittleIDE.IDEAntiFrameAntiItem:HandleBgRButtonDown(event)
	local child_index = self._panel.anti_anti_linear:GetChildIndex(self)
	if child_index <= 0 then
		return
	end
	ALittleIDE.g_IDECenter.center.control_anti:ShowAntiAntiMenu(self, child_index, event.rel_x)
end

function ALittleIDE.IDEAntiFrameAntiItem:Insert(rel_x, clazz)
	local child = {}
	child.clazz = clazz
	if self._info.attribute == "visible" or self._info.attribute == "disabled" then
		child.target = true
	else
		child.target = 0
	end
	if clazz == "LoopLinear" or clazz == "LoopRit" then
		child.delay_time = 0
		child.total_time = self:CalcTimeByWidth(rel_x - (self._container.x + self._container.width))
	elseif clazz == "LoopAttribute" then
		child.delay_time = self:CalcTimeByWidth(rel_x - (self._container.x + self._container.width))
		if child.delay_time <= 0 then
			child.delay_time = 1
		end
		child.total_time = 0
	else
		return
	end
	ALittle.List_Push(self._info.childs, child)
	local loop_item = ALittleIDE.g_Control:CreateControl("ide_anti_screen_loop_item")
	loop_item:Init(self, child)
	self._container:AddChild(loop_item)
	local revoke = ALittleIDE.IDEAntiInsertLoopRevoke(self, child, loop_item, ALittle.List_Len(self._info.childs))
	self._panel.tab_child.revoke_list:PushRevoke(revoke)
	loop_item.button.selected = true
	self._panel:ShowAntiLoop(loop_item)
	self._panel.tab_child.save = false
end

function ALittleIDE.IDEAntiFrameAntiItem:ClearLoop()
	if self._container.child_count == 0 then
		return
	end
	self._panel:HideAntiLoop()
	local loop_item_list = {}
	for index, child in ___ipairs(self._container.childs) do
		loop_item_list[index] = child
	end
	local revoke = ALittleIDE.IDEAntiClearLoopRevoke(self, self._info.childs, loop_item_list)
	self._panel.tab_child.revoke_list:PushRevoke(revoke)
	self._info.childs = {}
	self._container:RemoveAllChild()
	self._panel.tab_child.save = false
end

function ALittleIDE.IDEAntiFrameAntiItem:InsertBefore(loop_item, clazz)
	local child = {}
	child.clazz = clazz
	if self._info.attribute == "visible" or self._info.attribute == "disabled" then
		child.target = true
	else
		child.target = 0
	end
	if clazz == "LoopLinear" or clazz == "LoopRit" then
		child.delay_time = 0
		child.total_time = self._panel._INIT_TIME
	elseif clazz == "LoopAttribute" then
		child.delay_time = self._panel._INIT_TIME
		child.total_time = 0
	else
		return
	end
	local child_index = self._container:GetChildIndex(loop_item)
	ALittle.List_Insert(self._info.childs, child_index, child)
	loop_item = ALittleIDE.g_Control:CreateControl("ide_anti_screen_loop_item")
	loop_item:Init(self, child)
	self._container:AddChild(loop_item, child_index)
	local revoke = ALittleIDE.IDEAntiInsertLoopRevoke(self, child, loop_item, child_index)
	self._panel.tab_child.revoke_list:PushRevoke(revoke)
	loop_item.button.selected = true
	self._panel:ShowAntiLoop(loop_item)
	self._panel.tab_child.save = false
end

function ALittleIDE.IDEAntiFrameAntiItem:DeleteLoop(loop_item)
	self._panel:HideAntiLoop(loop_item)
	local child_index = self._container:GetChildIndex(loop_item)
	if child_index <= 0 then
		return
	end
	local child = self._info.childs[child_index]
	ALittle.List_Remove(self._info.childs, child_index)
	self._container:RemoveChild(loop_item)
	local revoke = ALittleIDE.IDEAntiDeleteLoopRevoke(self, child, loop_item, child_index)
	self._panel.tab_child.revoke_list:PushRevoke(revoke)
	self._panel.tab_child.save = false
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEAntiPanel = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEAntiPanel")

function ALittleIDE.IDEAntiPanel:TCtor()
	self._handle_container.visible = false
	self._loop_linear.visible = false
	self._loop_attribute.visible = false
	self._loop_rit.visible = false
	self._cur_loop_item = nil
	self._FRAME_WIDTH = 40
	self._FRAME_TIME = 50
	self._INIT_TIME = 10
	self._MIN_WIDTH = 10
end

function ALittleIDE.IDEAntiPanel.__getter:anti_link_linear()
	return self._anti_link_linear
end

function ALittleIDE.IDEAntiPanel.__getter:anti_anti_linear()
	return self._anti_anti_linear
end

function ALittleIDE.IDEAntiPanel.__getter:anti_screen()
	return self._anti_screen
end

function ALittleIDE.IDEAntiPanel.__getter:loop_group()
	return self._loop_group
end

function ALittleIDE.IDEAntiPanel.__getter:anti_scroll_list()
	return self._anti_scroll_list
end

function ALittleIDE.IDEAntiPanel.__getter:cur_show()
	return self._cur_show
end

function ALittleIDE.IDEAntiPanel.__getter:cur_loop_item()
	return self._cur_loop_item
end

function ALittleIDE.IDEAntiPanel.__getter:linear_target_value()
	return self._linear_target_value
end

function ALittleIDE.IDEAntiPanel.__getter:attribute_target_value()
	return self._attribute_target_value
end

function ALittleIDE.IDEAntiPanel.__getter:rit_target_value()
	return self._rit_target_value
end

function ALittleIDE.IDEAntiPanel.__getter:linear_total_time()
	return self._linear_total_time
end

function ALittleIDE.IDEAntiPanel.__getter:rit_total_time()
	return self._rit_total_time
end

function ALittleIDE.IDEAntiPanel.__getter:linear_delay_time()
	return self._linear_delay_time
end

function ALittleIDE.IDEAntiPanel.__getter:attribute_delay_time()
	return self._attribute_delay_time
end

function ALittleIDE.IDEAntiPanel.__getter:rit_delay_time()
	return self._rit_delay_time
end

function ALittleIDE.IDEAntiPanel:Init(tab_child)
	self._tab_child = tab_child
	self._list_group = ALittle.CreateKeyWeakMap()
	self._loop_group = ALittle.CreateKeyWeakMap()
	local user_info = self._tab_child.tree_object.user_info
	if user_info.base.loop_map ~= nil then
		for name, info in ___pairs(user_info.base.loop_map) do
			local item = ALittleIDE.g_Control:CreateControl("tree_item_radiobutton")
			item.text = name
			item.group = self._list_group
			item:AddEventListener(___all_struct[-1479093282], self, self.HandleAntiListItemRButtonDown)
			item:AddEventListener(___all_struct[958494922], self, self.HandleAntiListItemChanged)
			self._anti_scroll_list:AddChild(item)
		end
	end
	local static_object_hv = ALittleIDE.g_Control:CreateControl("ide_anti_screen_hv")
	local static_object_h = ALittleIDE.g_Control:CreateControl("ide_anti_screen_h", self)
	self._anti_frame_linear.x = static_object_hv.width
	local frame = 0
	while true do
		if not(frame <= 10000) then break end
		local text = ALittleIDE.g_Control:CreateControl("ide_anti_screen_frame_item")
		text.width = self._FRAME_WIDTH
		text:Init(self, frame)
		self._anti_frame_linear:AddChild(text)
		frame = frame+(50)
	end
	static_object_h.width = self._anti_frame_linear.x + self._anti_frame_linear.width
	local static_object_v = ALittleIDE.g_Control:CreateControl("ide_anti_screen_v", self)
	static_object_v.width = static_object_hv.width
	static_object_v.height = static_object_hv.height
	self._anti_link_linear.y = static_object_hv.height
	self._anti_screen.static_object_h = static_object_h
	self._anti_screen.static_object_hv = static_object_hv
	self._anti_screen.static_object_v = static_object_v
	self._anti_anti_linear.x = static_object_hv.width
	self._anti_anti_linear.y = static_object_hv.height
	self._anti_anti_linear.width = static_object_h.width - static_object_hv.width
	self._anti_screen:AdjustScrollBar()
	if self._anti_scroll_list.child_count > 0 then
		self._anti_scroll_list.childs[1].selected = true
		self:ShowAnti(self._anti_scroll_list.childs[1].text)
	end
end

function ALittleIDE.IDEAntiPanel.__getter:tab_child()
	return self._tab_child
end

function ALittleIDE.IDEAntiPanel:GetCurLoopInfo()
	if self._cur_show == nil then
		return nil
	end
	local user_info = self._tab_child.tree_object.user_info
	if user_info.base.loop_map == nil then
		return nil
	end
	return user_info.base.loop_map[self._cur_show]
end

function ALittleIDE.IDEAntiPanel:CreateAnti(name)
	local user_info = self._tab_child.tree_object.user_info
	if user_info.base.loop_map == nil then
		user_info.base.loop_map = {}
	end
	if user_info.base.loop_map[name] ~= nil then
		g_AUITool:ShowNotice("错误", "动画名称已存在")
		return
	end
	local root = {}
	root.childs = {}
	user_info.base.loop_map[name] = root
	local item = ALittleIDE.g_Control:CreateControl("tree_item_radiobutton")
	item.text = name
	item.group = self._list_group
	item:AddEventListener(___all_struct[-1479093282], self, self.HandleAntiListItemRButtonDown)
	item:AddEventListener(___all_struct[-449066808], self, self.HandleAntiListItemClick)
	self._anti_scroll_list:AddChild(item)
	item.selected = true
	self:ShowAnti(name)
	local revoke = ALittleIDE.IDECreateAntiRevoke(self, name, root, item)
	self._tab_child.revoke_list:PushRevoke(revoke)
	self._tab_child.save = false
end

function ALittleIDE.IDEAntiPanel:DeleteAnti(name)
	local user_info = self._tab_child.tree_object.user_info
	if user_info.base.loop_map == nil then
		return
	end
	local root = user_info.base.loop_map[name]
	if root == nil then
		return
	end
	user_info.base.loop_map[name] = nil
	for index, item in ___ipairs(self._anti_scroll_list.childs) do
		if item.text == name then
			item.group = nil
			self._anti_scroll_list:RemoveChild(item)
			local revoke = ALittleIDE.IDEDeleteAntiRevoke(self, name, root, item, index)
			self._tab_child.revoke_list:PushRevoke(revoke)
			break
		end
	end
	if self._anti_scroll_list.child_count == 0 then
		user_info.base.loop_map = nil
	end
	self._tab_child.save = false
	if self._cur_show == name then
		if self._anti_scroll_list.child_count == 0 then
			self:HideAnti()
		else
			self._anti_scroll_list.childs[1].selected = true
			self:ShowAnti(self._anti_scroll_list.childs[1].text)
		end
	end
end

function ALittleIDE.IDEAntiPanel:CopyAndNewAnti(old_name, new_name)
	local user_info = self._tab_child.tree_object.user_info
	if user_info.base.loop_map == nil then
		return
	end
	local root = user_info.base.loop_map[old_name]
	if root == nil then
		return
	end
	if user_info.base.loop_map[new_name] ~= nil then
		g_AUITool:ShowNotice("错误", "新建的动画名称已存在")
		return
	end
	local new_root = ALittle.String_CopyTable(root)
	user_info.base.loop_map[new_name] = new_root
	local item = ALittleIDE.g_Control:CreateControl("ide_common_item_radiobutton")
	item.text = new_name
	item.group = self._list_group
	item:AddEventListener(___all_struct[-1479093282], self, self.HandleAntiListItemRButtonDown)
	item:AddEventListener(___all_struct[-449066808], self, self.HandleAntiListItemClick)
	self._anti_scroll_list:AddChild(item)
	item.selected = true
	self:ShowAnti(new_name)
	local revoke = ALittleIDE.IDECreateAntiRevoke(self, new_name, new_root, item)
	self._tab_child.revoke_list:PushRevoke(revoke)
	self._tab_child.save = false
end

function ALittleIDE.IDEAntiPanel:ShowAnti(name)
	if self._cur_show == name then
		return
	end
	self:HideAnti()
	local user_info = self._tab_child.tree_object.user_info
	if user_info.base.loop_map == nil then
		return
	end
	local info = user_info.base.loop_map[name]
	if info == nil then
		return
	end
	self._cur_show = name
	local static_object_v = self._anti_screen.static_object_v
	self._anti_link_linear:RemoveAllChild()
	self._anti_anti_linear:RemoveAllChild()
	for index, child in ___ipairs(info.childs) do
		local anti_item = ALittleIDE.g_Control:CreateControl("ide_anti_screen_anti_item")
		anti_item:Init(self, child)
		self._anti_anti_linear:AddChild(anti_item)
		local link_item = ALittleIDE.g_Control:CreateControl("ide_anti_screen_link_item")
		link_item:Init(self, child)
		self._anti_link_linear:AddChild(link_item)
	end
	static_object_v.height = self._anti_link_linear.y + self._anti_link_linear.height
	self._anti_screen:AdjustScrollBar()
	self._handle_container.visible = true
end

function ALittleIDE.IDEAntiPanel:HideAnti()
	if self._cur_show == nil then
		return
	end
	self._cur_show = nil
	self._anti_anti_linear:RemoveAllChild()
	self._anti_link_linear:RemoveAllChild()
	self._anti_screen.static_object_v.height = self._anti_link_linear.y
	self._anti_screen:AdjustScrollBar()
	self._handle_container.visible = false
	self._loop_linear.visible = false
	self._loop_attribute.visible = false
	self._loop_rit.visible = false
	self._cur_loop_item = nil
	if self._cur_anti ~= nil then
		self._cur_anti:Stop()
		self._cur_anti = nil
	end
	if self._anti_dialog ~= nil then
		self._anti_dialog.visible = false
	end
end

function ALittleIDE.IDEAntiPanel:HandleAntiListItemRButtonDown(event)
	ALittleIDE.g_IDECenter.center.control_anti:ShowAntiListMenu(self, event.target.text)
end

function ALittleIDE.IDEAntiPanel:HandleAntiListItemClick(event)
	self:ShowAnti(event.target.text)
end

function ALittleIDE.IDEAntiPanel:HandleAntiListItemChanged(event)
	self:ShowAnti(event.target.text)
end

function ALittleIDE.IDEAntiPanel:HandleNewClick(event)
	ALittleIDE.g_IDECenter.center.control_anti:ShowNewAntiDialog(self)
end

function ALittleIDE.IDEAntiPanel:HandleCopyAttrLineClick(event)
	if self._cur_loop_item == nil then
		return
	end
	local info = self:GetCurLoopInfo()
	if info == nil then
		return
	end
	local child = ALittle.String_CopyTable(self._cur_loop_item.item.info)
	ALittle.List_Push(info.childs, child)
	local anti_item = ALittleIDE.g_Control:CreateControl("ide_anti_screen_anti_item")
	anti_item:Init(self, child)
	self._anti_anti_linear:AddChild(anti_item)
	local link_item = ALittleIDE.g_Control:CreateControl("ide_anti_screen_link_item")
	link_item:Init(self, child)
	self._anti_link_linear:AddChild(link_item)
	local static_object_v = self._anti_screen.static_object_v
	static_object_v.height = self._anti_link_linear.y + self._anti_link_linear.height
	self._anti_screen:AdjustScrollBar()
	local revoke = ALittleIDE.IDEAntiAddAttrRevoke(self, self._cur_show, child, anti_item, link_item)
	self._tab_child.revoke_list:PushRevoke(revoke)
	self._tab_child.save = false
end

function ALittleIDE.IDEAntiPanel:HandleAddAttrClick(event)
	local user_info = self._tab_child.tree_object.user_info
	if user_info.base.loop_map == nil then
		return
	end
	local info = user_info.base.loop_map[self._cur_show]
	if info == nil then
		return
	end
	local child = {}
	child.childs = {}
	child.attribute = "x"
	ALittle.List_Push(info.childs, child)
	local anti_item = ALittleIDE.g_Control:CreateControl("ide_anti_screen_anti_item")
	anti_item:Init(self, child)
	self._anti_anti_linear:AddChild(anti_item)
	local link_item = ALittleIDE.g_Control:CreateControl("ide_anti_screen_link_item")
	link_item:Init(self, child)
	self._anti_link_linear:AddChild(link_item)
	local static_object_v = self._anti_screen.static_object_v
	static_object_v.height = self._anti_link_linear.y + self._anti_link_linear.height
	self._anti_screen:AdjustScrollBar()
	local revoke = ALittleIDE.IDEAntiAddAttrRevoke(self, self._cur_show, child, anti_item, link_item)
	self._tab_child.revoke_list:PushRevoke(revoke)
	self._tab_child.save = false
end

function ALittleIDE.IDEAntiPanel:RemoveAttr(child_index)
	local user_info = self._tab_child.tree_object.user_info
	if user_info.base.loop_map == nil then
		return
	end
	local info = user_info.base.loop_map[self._cur_show]
	if info == nil then
		return
	end
	local child = info.childs[child_index]
	ALittle.List_Remove(info.childs, child_index)
	local anti_item = self._anti_anti_linear:GetChildByIndex(child_index)
	self._anti_anti_linear:RemoveChild(anti_item)
	local link_item = self._anti_link_linear:GetChildByIndex(child_index)
	self._anti_link_linear:RemoveChild(link_item)
	self._anti_screen.static_object_v.height = self._anti_link_linear.y + self._anti_link_linear.height
	self._anti_screen:AdjustScrollBar()
	local revoke = ALittleIDE.IDEAntiRemoveAttrRevoke(self, self._cur_show, child, anti_item, link_item, child_index)
	self._tab_child.revoke_list:PushRevoke(revoke)
	self._tab_child.save = false
end

function ALittleIDE.IDEAntiPanel:ShowAntiLoop(loop_item)
	local info = loop_item.info
	if info.clazz == "LoopLinear" then
		self._loop_linear.visible = true
		self._loop_attribute.visible = false
		self._loop_rit.visible = false
		self._cur_loop_item = loop_item
		if info.target == nil then
			self._linear_target_value.text = ""
		elseif info.target == false then
			self._linear_target_value.text = "false"
		elseif info.target == true then
			self._linear_target_value.text = "true"
		else
			self._linear_target_value.text = info.target
		end
		self._linear_total_time.text = info.total_time
		self._linear_delay_time.text = info.delay_time
	elseif info.clazz == "LoopLinear" or info.clazz == "LoopRit" then
		self._loop_rit.visible = true
		self._loop_linear.visible = false
		self._loop_attribute.visible = false
		self._cur_loop_item = loop_item
		if info.target == nil then
			self._rit_target_value.text = ""
		elseif info.target == false then
			self._rit_target_value.text = "false"
		elseif info.target == true then
			self._rit_target_value.text = "true"
		else
			self._rit_target_value.text = info.target
		end
		self._rit_total_time.text = info.total_time
		self._rit_delay_time.text = info.delay_time
	elseif info.clazz == "LoopAttribute" then
		self._loop_linear.visible = false
		self._loop_attribute.visible = true
		self._loop_rit.visible = false
		self._cur_loop_item = loop_item
		if info.target == nil then
			self._attribute_target_value.text = ""
		elseif info.target == false then
			self._attribute_target_value.text = "false"
		elseif info.target == true then
			self._attribute_target_value.text = "true"
		else
			self._attribute_target_value.text = info.target
		end
		self._attribute_delay_time.text = info.delay_time
	end
end

function ALittleIDE.IDEAntiPanel:HideAntiLoop(loop_item)
	if loop_item ~= nil and self._cur_loop_item ~= loop_item then
		return
	end
	self._loop_linear.visible = false
	self._loop_attribute.visible = false
	self._loop_rit.visible = false
	self._cur_loop_item = nil
end

function ALittleIDE.IDEAntiPanel:HandleDeleteLoopClick(event)
	if self._cur_loop_item ~= nil then
		self._cur_loop_item.item:DeleteLoop(self._cur_loop_item)
		self._cur_loop_item = nil
	end
	self:HideAntiLoop()
end

function ALittleIDE.IDEAntiPanel:HandleTargetValueChanged(event)
	if self._cur_loop_item == nil then
		return
	end
	self._cur_loop_item:SetTargetValue(event.target.text)
end

function ALittleIDE.IDEAntiPanel:HandleTotalTimeChanged(event)
	if self._cur_loop_item == nil then
		return
	end
	local time = ALittle.Math_ToInt(event.target.text)
	if time == nil or time < 0 then
		time = 0
		event.target.text = time
	end
	self._cur_loop_item:SetTotalTime(time)
end

function ALittleIDE.IDEAntiPanel:HandleDelayTimeChanged(event)
	if self._cur_loop_item == nil then
		return
	end
	local time = ALittle.Math_ToInt(event.target.text)
	if time == nil or time < 0 then
		time = 0
		event.target.text = time
	end
	self._cur_loop_item:SetDelayTime(time)
end

function ALittleIDE.IDEAntiPanel:PlayImpl(loop)
	local cur_loop_info = self:GetCurLoopInfo()
	if cur_loop_info == nil then
		return
	end
	local save = self._tab_child.save
	self._tab_child.save = true
	if self._anti_dialog == nil then
		self._anti_dialog = ALittleIDE.g_Control:CreateControl("ide_anti_play_dialog", self)
		self._anti_dialog.title = "动画播放窗口"
		self._anti_dialog.visible = false
		ALittleIDE.g_DialogLayer:AddChild(self._anti_dialog)
	end
	if save == false or self._cur_anti == nil or self._anti_dialog.visible == false or self._anti_dialog._user_data ~= self._tab_child.name then
		local map = {}
		local ui_manager = ALittleIDE.g_IDEProject:GetUIManager(self._tab_child.module)
		local object = ui_manager.control:CreateControl(self._tab_child.name, map)
		local anti = ALittle.LoopAnimation(object, cur_loop_info)
		local error = anti:Init(map)
		if error ~= nil then
			g_AUITool:ShowNotice("错误", error)
			return
		end
		self._anti_play_container:RemoveAllChild()
		self._anti_play_container:AddChild(object)
		self._anti_dialog._user_data = self._tab_child.name
		if object.width_type ~= 1 or object.height_type ~= 1 then
			self._anti_dialog.width = ALittleIDE.g_IDEProject.project.config:GetConfig("default_show_width", 800)
			self._anti_dialog.height = ALittleIDE.g_IDEProject.project.config:GetConfig("default_show_height", 800)
		else
			self._anti_dialog.width = object.width + 10
			self._anti_dialog.height = object.height + self._anti_dialog.head_size + 10
		end
		if self._anti_dialog.width < 300 then
			self._anti_dialog.width = 300
		end
		if self._anti_dialog.height < 300 then
			self._anti_dialog.height = 300
		end
		if self._anti_dialog.visible == false then
			self._anti_dialog.x = (A_UISystem.view_width - self._anti_dialog.width) / 2
			self._anti_dialog.y = (A_UISystem.view_height - self._anti_dialog.height) / 2
		end
		self._anti_dialog.visible = true
		self._cur_anti = anti
	end
	self._cur_anti:SetTime(0)
	self._cur_anti:Play(loop)
end

function ALittleIDE.IDEAntiPanel:HandlePlayClick(event)
	self:PlayImpl()
end

function ALittleIDE.IDEAntiPanel:HandleLoopPlayClick(event)
	self:PlayImpl(-1)
end

function ALittleIDE.IDEAntiPanel:HandlePauseClick(event)
	if self._cur_anti ~= nil then
		self._cur_anti:Pause()
	end
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEUIControlAnti = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEUIControlAnti")

function ALittleIDE.IDEUIControlAnti:Setup(tab, control)
	self._main_tab = tab
	self._main_control = control
	self._main_tab:SetChildText(self._main_control, "动画编辑器")
end

function ALittleIDE.IDEUIControlAnti:ShowNewAntiDialog(panel)
	if self._new_anti_dialog == nil then
		self._new_anti_dialog = ALittleIDE.g_Control:CreateControl("ide_new_anti_dialog", self)
		A_LayerManager:AddToModal(self._new_anti_dialog)
	end
	self._new_anti_dialog.visible = true
	self._new_anti_name_input.text = ""
	self._new_anti_dialog._user_data = panel
end

function ALittleIDE.IDEUIControlAnti:HandleNewAntiCancel(event)
	self._new_anti_dialog.visible = false
	self._new_anti_dialog._user_data = nil
end

function ALittleIDE.IDEUIControlAnti:HandleNewAntiConfirm(event)
	self._new_anti_dialog.visible = false
	local panel = self._new_anti_dialog._user_data
	self._new_anti_dialog._user_data = nil
	panel:CreateAnti(self._new_anti_name_input.text)
end

function ALittleIDE.IDEUIControlAnti:ShowAntiListMenu(panel, name)
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("复制并新建", Lua.Bind(self.HandleAntiListRightMenuCopyAnNew, self, panel, name))
	menu:AddItem("删除", Lua.Bind(panel.DeleteAnti, panel, name))
	menu:Show()
end

function ALittleIDE.IDEUIControlAnti:HandleAntiListRightMenuCopyAnNew(panel, name)
	local x, y
	for index, child in ___ipairs(panel.anti_scroll_list.childs) do
		if child.text == name then
			x, y = child:LocalToGlobal()
			break
		end
	end
	local old_name = name
	local new_name = g_AUITool:ShowRename(old_name, x, y, 200)
	if new_name == nil or old_name == new_name then
		return
	end
	panel:CopyAndNewAnti(old_name, new_name)
end
ALittleIDE.IDEUIControlAnti.HandleAntiListRightMenuCopyAnNew = Lua.CoWrap(ALittleIDE.IDEUIControlAnti.HandleAntiListRightMenuCopyAnNew)

function ALittleIDE.IDEUIControlAnti:ShowAntiAntiMenu(item, child_index, rel_x)
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("插入Linear", Lua.Bind(item.Insert, item, rel_x, "LoopLinear"))
	menu:AddItem("插入Rit", Lua.Bind(item.Insert, item, rel_x, "LoopRit"))
	menu:AddItem("插入Attribute", Lua.Bind(item.Insert, item, rel_x, "LoopAttribute"))
	menu:AddItem("清空", Lua.Bind(item.ClearLoop, item))
	menu:Show()
end

function ALittleIDE.IDEUIControlAnti:ShowAntiLoopMenu(loop_item)
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("插入Linear", Lua.Bind(loop_item.item.InsertBefore, loop_item.item, loop_item, "LoopLinear"))
	menu:AddItem("插入Rit", Lua.Bind(loop_item.item.InsertBefore, loop_item.item, loop_item, "LoopRit"))
	menu:AddItem("插入Attribute", Lua.Bind(loop_item.item.InsertBefore, loop_item.item, loop_item, "LoopAttribute"))
	menu:AddItem("清空", Lua.Bind(loop_item.item.DeleteLoop, loop_item.item, loop_item))
	menu:Show()
end

end