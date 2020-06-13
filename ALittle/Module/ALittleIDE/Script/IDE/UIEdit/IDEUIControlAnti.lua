-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-926666950, "ALittleIDE.IDEAntiAntiMenuUserData", {
name = "ALittleIDE.IDEAntiAntiMenuUserData", ns_name = "ALittleIDE", rl_name = "IDEAntiAntiMenuUserData", hash_code = -926666950,
name_list = {"item","child_index","rel_x"},
type_list = {"ALittleIDE.IDEAntiFrameAntiItem","int","double"},
option_map = {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name = "ALittle.UIClickEvent", ns_name = "ALittle", rl_name = "UIClickEvent", hash_code = -449066808,
name_list = {"target","is_drag"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})
ALittle.RegStruct(-431205740, "ALittle.UIResizeEvent", {
name = "ALittle.UIResizeEvent", ns_name = "ALittle", rl_name = "UIResizeEvent", hash_code = -431205740,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(36084947, "ALittleIDE.IDEAntiListMenuUserData", {
name = "ALittleIDE.IDEAntiListMenuUserData", ns_name = "ALittleIDE", rl_name = "IDEAntiListMenuUserData", hash_code = 36084947,
name_list = {"panel","name"},
type_list = {"ALittleIDE.IDEAntiPanel","string"},
option_map = {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name = "ALittle.UIChangedEvent", ns_name = "ALittle", rl_name = "UIChangedEvent", hash_code = 958494922,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1347472615, "ALittleIDE.IDEAntiLoopMenuUserData", {
name = "ALittleIDE.IDEAntiLoopMenuUserData", ns_name = "ALittleIDE", rl_name = "IDEAntiLoopMenuUserData", hash_code = -1347472615,
name_list = {"loop_item"},
type_list = {"ALittleIDE.IDEAntiFrameLoopItem"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
IDEAntiFrameLinearItem = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEAntiFrameLinearItem")

function IDEAntiFrameLinearItem:Init(panel, frame)
	self._panel = panel
	self._frame_text.text = frame
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
IDEAntiFrameLinkItem = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEAntiFrameLinkItem")

function IDEAntiFrameLinkItem:Init(panel, info)
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

function IDEAntiFrameLinkItem:HandleDeleteClick(event)
	self._panel:RemoveAttr(self._panel.anti_link_linear:GetChildIndex(self))
end

function IDEAntiFrameLinkItem:HandleLinkChanged(event)
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
	self._panel.tab_child:Save(false)
end

function IDEAntiFrameLinkItem:HandleAttributeChanged(event)
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
	self._panel.tab_child:Save(false)
end

function IDEAntiFrameLinkItem:HandleInitChanged(event)
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
	self._panel.tab_child:Save(false)
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
IDEAntiFrameLoopItem = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEAntiFrameLoopItem")

function IDEAntiFrameLoopItem:Init(item, info)
	self._item = item
	self._button.drag_trans_target = self._item.panel.anti_screen
	self._bg_quad.drag_trans_target = self._item.panel.anti_screen
	self._info = info
	self._button.group = self._item.panel.loop_group
	self:UpdateText()
	self:UpdateShow()
end

function IDEAntiFrameLoopItem.__getter:info()
	return self._info
end

function IDEAntiFrameLoopItem.__getter:button()
	return self._button
end

function IDEAntiFrameLoopItem.__getter:item()
	return self._item
end

function IDEAntiFrameLoopItem:UpdateText()
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

function IDEAntiFrameLoopItem:UpdateShow()
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

function IDEAntiFrameLoopItem.__getter:info()
	return self._info
end

function IDEAntiFrameLoopItem:HandleButtonChanged(event)
	self._item.panel:ShowAntiLoop(self)
end

function IDEAntiFrameLoopItem:HandleKeyDown(event)
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

function IDEAntiFrameLoopItem:HandleRButtonDown(event)
	g_IDECenter.center.control_anti:ShowAntiLoopMenu(self)
end

function IDEAntiFrameLoopItem.ValueToString(value)
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

function IDEAntiFrameLoopItem.StringToValue(attribute, value)
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

function IDEAntiFrameLoopItem:SetTargetValue(text)
	local old_value = self._info.target
	self._info.target = IDEAntiFrameLoopItem.StringToValue(self._item.info.attribute, text)
	self:UpdateText()
	if old_value ~= self._info.target then
		local old_value_string = IDEAntiFrameLoopItem.ValueToString(old_value)
		local new_value_string = IDEAntiFrameLoopItem.ValueToString(self._info.target)
		local revoke = IDEAntiLoopTargetValueChangeRevoke(self, old_value_string, new_value_string)
		self._item.panel.tab_child.revoke_list:PushRevoke(revoke)
		self._item.panel.tab_child:Save(false)
	end
end

function IDEAntiFrameLoopItem:SetTotalTime(time)
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
	local revoke = IDEAntiLoopTotalTimeChangeRevoke(self, old_time, self._info.total_time)
	self._item.panel.tab_child.revoke_list:PushRevoke(revoke)
	self._item.panel.tab_child:Save(false)
end

function IDEAntiFrameLoopItem:SetDelayTime(time)
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
	local revoke = IDEAntiLoopDelayTimeChangeRevoke(self, old_time, self._info.delay_time)
	self._item.panel.tab_child.revoke_list:PushRevoke(revoke)
	self._item.panel.tab_child:Save(false)
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
IDEAntiFrameAntiItem = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEAntiFrameAntiItem")

function IDEAntiFrameAntiItem:Init(panel, info)
	self._panel = panel
	self._bg_quad.drag_trans_target = self._panel.anti_screen
	self._info = info
	if self._info.childs == nil then
		self._info.childs = {}
	end
	for index, child in ___ipairs(self._info.childs) do
		local loop_item = g_Control:CreateControl("ide_anti_screen_loop_item")
		loop_item:Init(self, child)
		self._container:AddChild(loop_item)
	end
end

function IDEAntiFrameAntiItem.__getter:panel()
	return self._panel
end

function IDEAntiFrameAntiItem.__getter:info()
	return self._info
end

function IDEAntiFrameAntiItem.__getter:container()
	return self._container
end

function IDEAntiFrameAntiItem:CalcTimeByWidth(width)
	return ALittle.Math_Floor(width / self._panel._FRAME_WIDTH * self._panel._FRAME_TIME)
end

function IDEAntiFrameAntiItem:CalcWidthByTime(time)
	return time / self._panel._FRAME_TIME * self._panel._FRAME_WIDTH
end

function IDEAntiFrameAntiItem:HandleBgRButtonDown(event)
	local child_index = self._panel.anti_anti_linear:GetChildIndex(self)
	if child_index <= 0 then
		return
	end
	g_IDECenter.center.control_anti:ShowAntiAntiMenu(self, child_index, event.rel_x)
end

function IDEAntiFrameAntiItem:Insert(rel_x, clazz)
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
	local loop_item = g_Control:CreateControl("ide_anti_screen_loop_item")
	loop_item:Init(self, child)
	self._container:AddChild(loop_item)
	local revoke = IDEAntiInsertLoopRevoke(self, child, loop_item, ALittle.List_MaxN(self._info.childs))
	self._panel.tab_child.revoke_list:PushRevoke(revoke)
	loop_item.button.selected = true
	self._panel:ShowAntiLoop(loop_item)
	self._panel.tab_child:Save(false)
end

function IDEAntiFrameAntiItem:ClearLoop()
	if self._container.child_count == 0 then
		return
	end
	self._panel:HideAntiLoop()
	local loop_item_list = {}
	for index, child in ___ipairs(self._container.childs) do
		loop_item_list[index] = child
	end
	local revoke = IDEAntiClearLoopRevoke(self, self._info.childs, loop_item_list)
	self._panel.tab_child.revoke_list:PushRevoke(revoke)
	self._info.childs = {}
	self._container:RemoveAllChild()
	self._panel.tab_child:Save(false)
end

function IDEAntiFrameAntiItem:InsertBefore(loop_item, clazz)
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
	loop_item = g_Control:CreateControl("ide_anti_screen_loop_item")
	loop_item:Init(self, child)
	self._container:AddChild(loop_item, child_index)
	local revoke = IDEAntiInsertLoopRevoke(self, child, loop_item, child_index)
	self._panel.tab_child.revoke_list:PushRevoke(revoke)
	loop_item.button.selected = true
	self._panel:ShowAntiLoop(loop_item)
	self._panel.tab_child:Save(false)
end

function IDEAntiFrameAntiItem:DeleteLoop(loop_item)
	local child_index = self._container:GetChildIndex(loop_item)
	if child_index <= 0 then
		return
	end
	local child = self._info.childs[child_index]
	ALittle.List_Remove(self._info.childs, child_index)
	self._container:RemoveChild(loop_item)
	local revoke = IDEAntiDeleteLoopRevoke(self, child, loop_item, child_index)
	self._panel.tab_child.revoke_list:PushRevoke(revoke)
	self._panel.tab_child:Save(false)
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
IDEAntiPanel = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEAntiPanel")

function IDEAntiPanel:TCtor()
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

function IDEAntiPanel.__getter:anti_link_linear()
	return self._anti_link_linear
end

function IDEAntiPanel.__getter:anti_anti_linear()
	return self._anti_anti_linear
end

function IDEAntiPanel.__getter:anti_screen()
	return self._anti_screen
end

function IDEAntiPanel.__getter:loop_group()
	return self._loop_group
end

function IDEAntiPanel.__getter:anti_scroll_list()
	return self._anti_scroll_list
end

function IDEAntiPanel.__getter:cur_show()
	return self._cur_show
end

function IDEAntiPanel.__getter:cur_loop_item()
	return self._cur_loop_item
end

function IDEAntiPanel.__getter:linear_target_value()
	return self._linear_target_value
end

function IDEAntiPanel.__getter:attribute_target_value()
	return self._attribute_target_value
end

function IDEAntiPanel.__getter:rit_target_value()
	return self._rit_target_value
end

function IDEAntiPanel.__getter:linear_total_time()
	return self._linear_total_time
end

function IDEAntiPanel.__getter:rit_total_time()
	return self._rit_total_time
end

function IDEAntiPanel.__getter:linear_delay_time()
	return self._linear_delay_time
end

function IDEAntiPanel.__getter:attribute_delay_time()
	return self._attribute_delay_time
end

function IDEAntiPanel.__getter:rit_delay_time()
	return self._rit_delay_time
end

function IDEAntiPanel:Init(tab_child)
	self._tab_child = tab_child
	self._list_group = ALittle.CreateKeyWeakMap()
	self._loop_group = ALittle.CreateKeyWeakMap()
	local user_info = self._tab_child.tree_object.user_info
	if user_info.base.loop_map ~= nil then
		for name, info in ___pairs(user_info.base.loop_map) do
			local item = g_Control:CreateControl("ide_common_item_radiobutton")
			item.text = name
			item.group = self._list_group
			item:AddEventListener(___all_struct[-1479093282], self, self.HandleAntiListItemRButtonDown)
			item:AddEventListener(___all_struct[958494922], self, self.HandleAntiListItemChanged)
			self._anti_scroll_list:AddChild(item)
		end
	end
	local static_object_hv = g_Control:CreateControl("ide_anti_screen_hv")
	local static_object_h = g_Control:CreateControl("ide_anti_screen_h", self)
	self._anti_frame_linear.x = static_object_hv.width
	local frame = 0
	while true do
		if not(frame <= 10000) then break end
		local text = g_Control:CreateControl("ide_anti_screen_frame_item")
		text.width = self._FRAME_WIDTH
		text:Init(self, frame)
		self._anti_frame_linear:AddChild(text)
		frame = frame+(50)
	end
	static_object_h.width = self._anti_frame_linear.x + self._anti_frame_linear.width
	local static_object_v = g_Control:CreateControl("ide_anti_screen_v", self)
	static_object_v.width = static_object_hv.width
	static_object_v.height = static_object_hv.height
	self._anti_link_linear.y = static_object_hv.height
	self._anti_screen.static_object_h = static_object_h
	self._anti_screen.static_object_hv = static_object_hv
	self._anti_screen.static_object_v = static_object_v
	self._anti_anti_linear.x = static_object_hv.width
	self._anti_anti_linear.y = static_object_hv.height
	self._anti_anti_linear.width = static_object_h.width - static_object_hv.width
	self._anti_screen:RejustScrollBar()
	if self._anti_scroll_list.child_count > 0 then
		self._anti_scroll_list.childs[1].selected = true
		self:ShowAnti(self._anti_scroll_list.childs[1].text)
	end
end

function IDEAntiPanel.__getter:tab_child()
	return self._tab_child
end

function IDEAntiPanel:GetCurLoopInfo()
	if self._cur_show == nil then
		return nil
	end
	local user_info = self._tab_child.tree_object.user_info
	if user_info.base.loop_map == nil then
		return nil
	end
	return user_info.base.loop_map[self._cur_show]
end

function IDEAntiPanel:CreateAnti(name)
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
	local item = g_Control:CreateControl("ide_common_item_radiobutton")
	item.text = name
	item.group = self._list_group
	item:AddEventListener(___all_struct[-1479093282], self, self.HandleAntiListItemRButtonDown)
	item:AddEventListener(___all_struct[-449066808], self, self.HandleAntiListItemClick)
	self._anti_scroll_list:AddChild(item)
	item.selected = true
	self:ShowAnti(name)
	local revoke = IDECreateAntiRevoke(self, name, root, item)
	self._tab_child.revoke_list:PushRevoke(revoke)
	self._tab_child:Save(false)
end

function IDEAntiPanel:DeleteAnti(name)
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
			local revoke = IDEDeleteAntiRevoke(self, name, root, item, index)
			self._tab_child.revoke_list:PushRevoke(revoke)
			break
		end
	end
	if self._anti_scroll_list.child_count == 0 then
		user_info.base.loop_map = nil
	end
	self._tab_child:Save(false)
	if self._cur_show == name then
		if self._anti_scroll_list.child_count == 0 then
			self:HideAnti()
		else
			self._anti_scroll_list.childs[1].selected = true
			self:ShowAnti(self._anti_scroll_list.childs[1].text)
		end
	end
end

function IDEAntiPanel:CopyAndNewAnti(old_name, new_name)
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
	local item = g_Control:CreateControl("ide_common_item_radiobutton")
	item.text = new_name
	item.group = self._list_group
	item:AddEventListener(___all_struct[-1479093282], self, self.HandleAntiListItemRButtonDown)
	item:AddEventListener(___all_struct[-449066808], self, self.HandleAntiListItemClick)
	self._anti_scroll_list:AddChild(item)
	item.selected = true
	self:ShowAnti(new_name)
	local revoke = IDECreateAntiRevoke(self, new_name, new_root, item)
	self._tab_child.revoke_list:PushRevoke(revoke)
	self._tab_child:Save(false)
end

function IDEAntiPanel:ShowAnti(name)
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
		local anti_item = g_Control:CreateControl("ide_anti_screen_anti_item")
		anti_item:Init(self, child)
		self._anti_anti_linear:AddChild(anti_item)
		local link_item = g_Control:CreateControl("ide_anti_screen_link_item")
		link_item:Init(self, child)
		self._anti_link_linear:AddChild(link_item)
	end
	static_object_v.height = self._anti_link_linear.y + self._anti_link_linear.height
	self._anti_screen:RejustScrollBar()
	self._handle_container.visible = true
end

function IDEAntiPanel:HideAnti()
	if self._cur_show == nil then
		return
	end
	self._cur_show = nil
	self._anti_anti_linear:RemoveAllChild()
	self._anti_link_linear:RemoveAllChild()
	self._anti_screen.static_object_v.height = self._anti_link_linear.y
	self._anti_screen:RejustScrollBar()
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

function IDEAntiPanel:HandleAntiListItemRButtonDown(event)
	g_IDECenter.center.control_anti:ShowAntiListMenu(self, event.target.text)
end

function IDEAntiPanel:HandleAntiListItemClick(event)
	self:ShowAnti(event.target.text)
end

function IDEAntiPanel:HandleAntiListItemChanged(event)
	self:ShowAnti(event.target.text)
end

function IDEAntiPanel:HandleNewClick(event)
	g_IDECenter.center.control_anti:ShowNewAntiDialog(self)
end

function IDEAntiPanel:HandleCopyAttrLineClick(event)
	if self._cur_loop_item == nil then
		return
	end
	local info = self:GetCurLoopInfo()
	if info == nil then
		return
	end
	local child = ALittle.String_CopyTable(self._cur_loop_item.item.info)
	ALittle.List_Push(info.childs, child)
	local anti_item = g_Control:CreateControl("ide_anti_screen_anti_item")
	anti_item:Init(self, child)
	self._anti_anti_linear:AddChild(anti_item)
	local link_item = g_Control:CreateControl("ide_anti_screen_link_item")
	link_item:Init(self, child)
	self._anti_link_linear:AddChild(link_item)
	local static_object_v = self._anti_screen.static_object_v
	static_object_v.height = self._anti_link_linear.y + self._anti_link_linear.height
	self._anti_screen:RejustScrollBar()
	local revoke = IDEAntiAddAttrRevoke(self, self._cur_show, child, anti_item, link_item)
	self._tab_child.revoke_list:PushRevoke(revoke)
	self._tab_child:Save(false)
end

function IDEAntiPanel:HandleAddAttrClick(event)
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
	local anti_item = g_Control:CreateControl("ide_anti_screen_anti_item")
	anti_item:Init(self, child)
	self._anti_anti_linear:AddChild(anti_item)
	local link_item = g_Control:CreateControl("ide_anti_screen_link_item")
	link_item:Init(self, child)
	self._anti_link_linear:AddChild(link_item)
	local static_object_v = self._anti_screen.static_object_v
	static_object_v.height = self._anti_link_linear.y + self._anti_link_linear.height
	self._anti_screen:RejustScrollBar()
	local revoke = IDEAntiAddAttrRevoke(self, self._cur_show, child, anti_item, link_item)
	self._tab_child.revoke_list:PushRevoke(revoke)
	self._tab_child:Save(false)
end

function IDEAntiPanel:RemoveAttr(child_index)
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
	self._anti_screen:RejustScrollBar()
	local revoke = IDEAntiRemoveAttrRevoke(self, self._cur_show, child, anti_item, link_item, child_index)
	self._tab_child.revoke_list:PushRevoke(revoke)
	self._tab_child:Save(false)
end

function IDEAntiPanel:ShowAntiLoop(loop_item)
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

function IDEAntiPanel:HideAntiLoop(loop_item)
	if loop_item ~= nil and self._cur_loop_item ~= loop_item then
		return
	end
	self._loop_linear.visible = false
	self._loop_attribute.visible = false
	self._loop_rit.visible = false
	self._cur_loop_item = nil
end

function IDEAntiPanel:HandleDeleteLoopClick(event)
	if self._cur_loop_item ~= nil then
		self._cur_loop_item.item:DeleteLoop(self._cur_loop_item)
		self._cur_loop_item = nil
	end
	self:HideAntiLoop()
end

function IDEAntiPanel:HandleTargetValueChanged(event)
	if self._cur_loop_item == nil then
		return
	end
	self._cur_loop_item:SetTargetValue(event.target.text)
end

function IDEAntiPanel:HandleTotalTimeChanged(event)
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

function IDEAntiPanel:HandleDelayTimeChanged(event)
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

function IDEAntiPanel:PlayImpl(loop)
	local cur_loop_info = self:GetCurLoopInfo()
	if cur_loop_info == nil then
		return
	end
	local save = self._tab_child.save
	self._tab_child:Save(true)
	if self._anti_dialog == nil then
		self._anti_dialog = g_Control:CreateControl("ide_anti_play_dialog", self)
		self._anti_dialog.title = "动画播放窗口"
		self._anti_dialog.visible = false
		g_DialogLayer:AddChild(self._anti_dialog)
	end
	if save == false or self._cur_anti == nil or self._anti_dialog.visible == false or self._anti_dialog._user_data ~= self._tab_child.name then
		local map = {}
		local object = g_IDEProject.project.control:CreateControl(self._tab_child.name, map)
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
			self._anti_dialog.width = g_IDEProject.project.config:GetConfig("default_show_width", 800)
			self._anti_dialog.height = g_IDEProject.project.config:GetConfig("default_show_height", 800)
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

function IDEAntiPanel:HandlePlayClick(event)
	self:PlayImpl()
end

function IDEAntiPanel:HandleLoopPlayClick(event)
	self:PlayImpl(-1)
end

function IDEAntiPanel:HandlePauseClick(event)
	if self._cur_anti ~= nil then
		self._cur_anti:Pause()
	end
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
IDEUIControlAnti = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEUIControlAnti")

function IDEUIControlAnti:Setup(tab, control)
	self._main_tab = tab
	self._main_control = control
	self._main_tab:SetChildText(self._main_control, "动画编辑器")
end

function IDEUIControlAnti:ShowNewAntiDialog(panel)
	if self._new_anti_dialog == nil then
		self._new_anti_dialog = g_Control:CreateControl("ide_new_anti_dialog", self)
		A_LayerManager:AddToModal(self._new_anti_dialog)
	end
	self._new_anti_dialog.visible = true
	self._new_anti_name_input.text = ""
	self._new_anti_dialog._user_data = panel
end

function IDEUIControlAnti:HandleNewAntiCancel(event)
	self._new_anti_dialog.visible = false
	self._new_anti_dialog._user_data = nil
end

function IDEUIControlAnti:HandleNewAntiConfirm(event)
	self._new_anti_dialog.visible = false
	local panel = self._new_anti_dialog._user_data
	self._new_anti_dialog._user_data = nil
	panel:CreateAnti(self._new_anti_name_input.text)
end

function IDEUIControlAnti:ShowAntiListMenu(panel, name)
	if self._anti_list_right_menu == nil then
		self._anti_list_right_menu = g_Control:CreateControl("ide_anti_list_right_menu", self)
	end
	A_LayerManager:ShowFromRight(self._anti_list_right_menu)
	self._anti_list_right_menu.x = A_UISystem.mouse_x
	self._anti_list_right_menu.y = A_UISystem.mouse_y
	if self._anti_list_right_menu.x + self._anti_list_right_menu.width > A_UISystem.view_width then
		self._anti_list_right_menu.x = A_UISystem.view_width - self._anti_list_right_menu.width
	end
	if self._anti_list_right_menu.y + self._anti_list_right_menu.height > A_UISystem.view_height then
		self._anti_list_right_menu.y = A_UISystem.view_height - self._anti_list_right_menu.height
	end
	local user_data = {}
	user_data.panel = panel
	user_data.name = name
	self._anti_list_right_menu._user_data = user_data
end

function IDEUIControlAnti:HandleAntiListRightMenuDelete(event)
	A_LayerManager:HideFromRight(self._anti_list_right_menu)
	local user_data = self._anti_list_right_menu._user_data
	self._anti_list_right_menu._user_data = nil
	user_data.panel:DeleteAnti(user_data.name)
end

function IDEUIControlAnti:HandleAntiListRightMenuCopyAnNew(event)
	A_LayerManager:HideFromRight(self._anti_list_right_menu)
	local user_data = self._anti_list_right_menu._user_data
	self._anti_list_right_menu._user_data = nil
	local x, y
	for index, child in ___ipairs(user_data.panel.anti_scroll_list.childs) do
		if child.text == user_data.name then
			x, y = child:LocalToGlobal()
			break
		end
	end
	local old_name = user_data.name
	local new_name = g_AUITool:ShowRename(old_name, x, y, event.target.width)
	if new_name == nil or old_name == new_name then
		return
	end
	user_data.panel:CopyAndNewAnti(old_name, new_name)
end
IDEUIControlAnti.HandleAntiListRightMenuCopyAnNew = Lua.CoWrap(IDEUIControlAnti.HandleAntiListRightMenuCopyAnNew)

function IDEUIControlAnti:ShowAntiAntiMenu(item, child_index, rel_x)
	if self._anti_anti_right_menu == nil then
		self._anti_anti_right_menu = g_Control:CreateControl("ide_anti_anti_right_menu", self)
	end
	A_LayerManager:ShowFromRight(self._anti_anti_right_menu)
	self._anti_anti_right_menu.x = A_UISystem.mouse_x
	self._anti_anti_right_menu.y = A_UISystem.mouse_y
	if self._anti_anti_right_menu.x + self._anti_anti_right_menu.width > A_UISystem.view_width then
		self._anti_anti_right_menu.x = A_UISystem.view_width - self._anti_anti_right_menu.width
	end
	if self._anti_anti_right_menu.y + self._anti_anti_right_menu.height > A_UISystem.view_height then
		self._anti_anti_right_menu.y = A_UISystem.view_height - self._anti_anti_right_menu.height
	end
	local user_data = {}
	user_data.item = item
	user_data.child_index = child_index
	user_data.rel_x = rel_x
	self._anti_anti_right_menu._user_data = user_data
end

function IDEUIControlAnti:HandleAntiAntiInsertLinear(event)
	A_LayerManager:HideFromRight(self._anti_anti_right_menu)
	local user_data = self._anti_anti_right_menu._user_data
	self._anti_anti_right_menu._user_data = nil
	user_data.item:Insert(user_data.rel_x, "LoopLinear")
end

function IDEUIControlAnti:HandleAntiAntiInsertRit(event)
	A_LayerManager:HideFromRight(self._anti_anti_right_menu)
	local user_data = self._anti_anti_right_menu._user_data
	self._anti_anti_right_menu._user_data = nil
	user_data.item:Insert(user_data.rel_x, "LoopRit")
end

function IDEUIControlAnti:HandleAntiAntiInsertAttribute(event)
	A_LayerManager:HideFromRight(self._anti_anti_right_menu)
	local user_data = self._anti_anti_right_menu._user_data
	self._anti_anti_right_menu._user_data = nil
	user_data.item:Insert(user_data.rel_x, "LoopAttribute")
end

function IDEUIControlAnti:HandleAntiAntiClear(event)
	A_LayerManager:HideFromRight(self._anti_anti_right_menu)
	local user_data = self._anti_anti_right_menu._user_data
	self._anti_anti_right_menu._user_data = nil
	user_data.item:ClearLoop()
end

function IDEUIControlAnti:ShowAntiLoopMenu(loop_item)
	if self._anti_loop_right_menu == nil then
		self._anti_loop_right_menu = g_Control:CreateControl("ide_anti_loop_right_menu", self)
	end
	A_LayerManager:ShowFromRight(self._anti_loop_right_menu)
	self._anti_loop_right_menu.x = A_UISystem.mouse_x
	self._anti_loop_right_menu.y = A_UISystem.mouse_y
	if self._anti_loop_right_menu.x + self._anti_loop_right_menu.width > A_UISystem.view_width then
		self._anti_loop_right_menu.x = A_UISystem.view_width - self._anti_loop_right_menu.width
	end
	if self._anti_loop_right_menu.y + self._anti_loop_right_menu.height > A_UISystem.view_height then
		self._anti_loop_right_menu.y = A_UISystem.view_height - self._anti_loop_right_menu.height
	end
	local user_data = {}
	user_data.loop_item = loop_item
	self._anti_loop_right_menu._user_data = user_data
end

function IDEUIControlAnti:HandleAntiLoopInsertLinear(event)
	A_LayerManager:HideFromRight(self._anti_loop_right_menu)
	local user_data = self._anti_loop_right_menu._user_data
	self._anti_loop_right_menu._user_data = nil
	user_data.loop_item.item:InsertBefore(user_data.loop_item, "LoopLinear")
end

function IDEUIControlAnti:HandleAntiLoopInsertRit(event)
	A_LayerManager:HideFromRight(self._anti_loop_right_menu)
	local user_data = self._anti_loop_right_menu._user_data
	self._anti_loop_right_menu._user_data = nil
	user_data.loop_item.item:InsertBefore(user_data.loop_item, "LoopRit")
end

function IDEUIControlAnti:HandleAntiLoopInsertAttribute(event)
	A_LayerManager:HideFromRight(self._anti_loop_right_menu)
	local user_data = self._anti_loop_right_menu._user_data
	self._anti_loop_right_menu._user_data = nil
	user_data.loop_item.item:InsertBefore(user_data.loop_item, "LoopAttribute")
end

function IDEUIControlAnti:HandleAntiLoopDelete(event)
	A_LayerManager:HideFromRight(self._anti_loop_right_menu)
	local user_data = self._anti_loop_right_menu._user_data
	self._anti_loop_right_menu._user_data = nil
	user_data.loop_item.item.panel:HideAntiLoop(user_data.loop_item)
	user_data.loop_item.item:DeleteLoop(user_data.loop_item)
end

