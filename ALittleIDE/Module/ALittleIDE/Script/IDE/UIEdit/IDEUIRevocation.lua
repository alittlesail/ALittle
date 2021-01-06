-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-431205740, "ALittle.UIResizeEvent", {
name = "ALittle.UIResizeEvent", ns_name = "ALittle", rl_name = "UIResizeEvent", hash_code = -431205740,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

assert(ALittle.RevokeObject, " extends class:ALittle.RevokeObject is nil")
ALittleIDE.IDETextEditRevoke = Lua.Class(ALittle.RevokeObject, "ALittleIDE.IDETextEditRevoke")

function ALittleIDE.IDETextEditRevoke:Ctor(target, old_text, new_text)
	___rawset(self, "_target", target)
	___rawset(self, "_old_text", old_text)
	___rawset(self, "_new_text", new_text)
end

function ALittleIDE.IDETextEditRevoke:Forward()
	self._target.text = self._new_text
end

function ALittleIDE.IDETextEditRevoke:Back()
	self._target.text = self._old_text
end

assert(ALittle.RevokeObject, " extends class:ALittle.RevokeObject is nil")
ALittleIDE.IDEDeleteRevoke = Lua.Class(ALittle.RevokeObject, "ALittleIDE.IDEDeleteRevoke")

function ALittleIDE.IDEDeleteRevoke:Ctor(parent, current, index)
	___rawset(self, "_parent", parent)
	___rawset(self, "_current", current)
	___rawset(self, "_index", index)
end

function ALittleIDE.IDEDeleteRevoke:Forward()
	local current = self._current
	local parent = self._parent
	local child_type = current.user_info.child_type
	if child_type == nil then
		return
	end
	parent:RemoveChild(current)
	if child_type == "child" then
		parent.user_info.object:RemoveChild(current.user_info.object)
	elseif child_type ~= nil then
		parent.user_info.object[child_type] = nil
	end
	current:RemoveAttributePanel()
	current.tab_child:UpdateHandleQuadRemove(current)
	parent.tab_child:UpdateHandleQuadLayout(parent)
	current.tab_child.save = false
end

function ALittleIDE.IDEDeleteRevoke:Back()
	local current = self._current
	local parent = self._parent
	local index = self._index
	local child_type = current.user_info.child_type
	if child_type == nil then
		return
	end
	parent:AddChild(current, index)
	if child_type == "child" then
		parent.user_info.object:AddChild(current.user_info.object, index)
	elseif child_type ~= nil then
		parent.user_info.object[child_type] = current.user_info.object
	end
	parent.tab_child:UpdateHandleQuadLayout(parent)
	current.tab_child.save = false
end

assert(ALittle.RevokeObject, " extends class:ALittle.RevokeObject is nil")
ALittleIDE.IDEChildShowRevoke = Lua.Class(ALittle.RevokeObject, "ALittleIDE.IDEChildShowRevoke")

function ALittleIDE.IDEChildShowRevoke:Ctor(parent, current, index)
	___rawset(self, "_parent", parent)
	___rawset(self, "_current", current)
	___rawset(self, "_index", index)
end

function ALittleIDE.IDEChildShowRevoke:Forward()
	local current = self._current
	local parent = self._parent
	local index = self._index
	local child_type = current.user_info.child_type
	if child_type == nil then
		return
	end
	parent:AddChild(current, index)
	if child_type == "child" then
		parent.user_info.object:AddChild(current.user_info.object, index)
	elseif child_type ~= nil then
		parent.user_info.object[child_type] = current.user_info.object
	end
	parent.tab_child:UpdateHandleQuadLayout(parent)
	current.tab_child.save = false
end

function ALittleIDE.IDEChildShowRevoke:Back()
	local current = self._current
	local parent = self._parent
	local child_type = current.user_info.child_type
	if child_type == nil then
		return
	end
	parent:RemoveChild(current)
	if child_type == "child" then
		parent.user_info.object:RemoveChild(current.user_info.object)
	elseif child_type ~= nil then
		parent.user_info.object[child_type] = nil
	end
	current:RemoveAttributePanel()
	current.tab_child:UpdateHandleQuadRemove(current)
	parent.tab_child:UpdateHandleQuadLayout(parent)
	current.tab_child.save = false
end

assert(ALittle.RevokeObject, " extends class:ALittle.RevokeObject is nil")
ALittleIDE.IDEDragXYRevoke = Lua.Class(ALittle.RevokeObject, "ALittleIDE.IDEDragXYRevoke")

function ALittleIDE.IDEDragXYRevoke:Ctor(target, delta_x, delta_y)
	___rawset(self, "_target", target)
	___rawset(self, "_delta_x", delta_x)
	___rawset(self, "_delta_y", delta_y)
end

function ALittleIDE.IDEDragXYRevoke:Foward()
	self._target:DragXY(self._delta_x, self._delta_y)
	self._target.tab_child:UpdateHandleQuadLayout(self._target)
	self._target.tab_child.save = false
end

function ALittleIDE.IDEDragXYRevoke:Back()
	self._target:DragXY(-self._delta_x, -self._delta_y)
	self._target.tab_child:UpdateHandleQuadLayout(self._target)
	self._target.tab_child.save = false
end

assert(ALittle.RevokeObject, " extends class:ALittle.RevokeObject is nil")
ALittleIDE.IDEDragWHRevoke = Lua.Class(ALittle.RevokeObject, "ALittleIDE.IDEDragWHRevoke")

function ALittleIDE.IDEDragWHRevoke:Ctor(target, delta_x, delta_y)
	___rawset(self, "_target", target)
	___rawset(self, "_delta_x", delta_x)
	___rawset(self, "_delta_y", delta_y)
end

function ALittleIDE.IDEDragWHRevoke:Foward()
	self._target:DragWH(self._delta_x, self._delta_y)
	self._target.tab_child:UpdateHandleQuadLayout(self._target)
	self._target.tab_child.save = false
end

function ALittleIDE.IDEDragWHRevoke:Back()
	self._target:DragWH(-self._delta_x, -self._delta_y)
	self._target.tab_child:UpdateHandleQuadLayout(self._target)
	self._target.tab_child.save = false
end

assert(ALittle.RevokeObject, " extends class:ALittle.RevokeObject is nil")
ALittleIDE.IDEChildUpDownRevoke = Lua.Class(ALittle.RevokeObject, "ALittleIDE.IDEChildUpDownRevoke")

function ALittleIDE.IDEChildUpDownRevoke:Ctor(parent, current, up_down)
	___rawset(self, "_parent", parent)
	___rawset(self, "_current", current)
	___rawset(self, "_up_down", up_down)
end

function ALittleIDE.IDEChildUpDownRevoke:Forward()
	local parent = self._parent
	local current = self._current
	local text = self._up_down
	local index = parent:GetChildIndex(current)
	if text == "up" then
		index = index - 1
	elseif text == "down" then
		index = index + 1
	end
	parent:SetChildIndex(current, index)
	parent.user_info.object:SetChildIndex(current.user_info.object, index)
end

function ALittleIDE.IDEChildUpDownRevoke:Back()
	local parent = self._parent
	local current = self._current
	local text = self._up_down
	local index = parent:GetChildIndex(current)
	if text == "up" then
		index = index + 1
	elseif text == "down" then
		index = index - 1
	end
	parent:SetChildIndex(current, index)
	parent.user_info.object:SetChildIndex(current.user_info.object, index)
end

assert(ALittle.RevokeObject, " extends class:ALittle.RevokeObject is nil")
ALittleIDE.IDENatureChangeRevoke = Lua.Class(ALittle.RevokeObject, "ALittleIDE.IDENatureChangeRevoke")

function ALittleIDE.IDENatureChangeRevoke:Ctor(target, nature, old_base, new_base, old_object, new_object, text, need_reset)
	___rawset(self, "_target", target)
	___rawset(self, "_nature", nature)
	___rawset(self, "_old_base", old_base)
	___rawset(self, "_new_base", new_base)
	___rawset(self, "_old_object", old_object)
	___rawset(self, "_new_object", new_object)
	___rawset(self, "_need_reset", need_reset)
	___rawset(self, "_text", text)
end

function ALittleIDE.IDENatureChangeRevoke:Forward()
	local user_info = self._target.user_info
	local nature = self._nature
	user_info.base[nature] = self._new_base
	user_info.object[nature] = self._new_object
	if self._target.attr_panel ~= nil and self._text ~= nil then
		self._target.attr_panel["_" .. nature].text = self._text
	end
	if self._need_reset then
		self._target.tab_child:UpdateHandleQuadLayout(self._target)
	end
	self._target.tab_child.save = false
end

function ALittleIDE.IDENatureChangeRevoke:Back()
	local user_info = self._target.user_info
	local nature = self._nature
	user_info.base[nature] = self._old_base
	user_info.object[nature] = self._old_object
	if self._target.attr_panel ~= nil then
		self._target.attr_panel:LoadNatureBase()
	end
	if self._need_reset then
		self._target.tab_child:UpdateHandleQuadLayout(self._target)
	end
	self._target.tab_child.save = false
end

assert(ALittle.RevokeObject, " extends class:ALittle.RevokeObject is nil")
ALittleIDE.IDECreateAntiRevoke = Lua.Class(ALittle.RevokeObject, "ALittleIDE.IDECreateAntiRevoke")

function ALittleIDE.IDECreateAntiRevoke:Ctor(target, name, info, item)
	___rawset(self, "_target", target)
	___rawset(self, "_name", name)
	___rawset(self, "_info", info)
	___rawset(self, "_item", item)
end

function ALittleIDE.IDECreateAntiRevoke:Forward()
	local user_info = self._target.tab_child.tree_object.user_info
	if user_info.base.loop_map == nil then
		user_info.base.loop_map = {}
	end
	user_info.base.loop_map[self._name] = self._info
	self._target.anti_scroll_list:AddChild(self._item)
	self._target.tab_child.save = false
end

function ALittleIDE.IDECreateAntiRevoke:Back()
	local user_info = self._target.tab_child.tree_object.user_info
	if user_info.base.loop_map == nil then
		return
	end
	user_info.base.loop_map[self._name] = nil
	self._target.anti_scroll_list:RemoveChild(self._item)
	self._target.tab_child.save = false
end

assert(ALittle.RevokeObject, " extends class:ALittle.RevokeObject is nil")
ALittleIDE.IDEDeleteAntiRevoke = Lua.Class(ALittle.RevokeObject, "ALittleIDE.IDEDeleteAntiRevoke")

function ALittleIDE.IDEDeleteAntiRevoke:Ctor(target, name, info, item, child_index)
	___rawset(self, "_target", target)
	___rawset(self, "_name", name)
	___rawset(self, "_info", info)
	___rawset(self, "_item", item)
	___rawset(self, "_child_index", child_index)
end

function ALittleIDE.IDEDeleteAntiRevoke:Forward()
	local user_info = self._target.tab_child.tree_object.user_info
	if user_info.base.loop_map == nil then
		return
	end
	user_info.base.loop_map[self._name] = nil
	self._target.anti_scroll_list:RemoveChild(self._item)
	self._target.tab_child.save = false
end

function ALittleIDE.IDEDeleteAntiRevoke:Back()
	local user_info = self._target.tab_child.tree_object.user_info
	if user_info.base.loop_map == nil then
		user_info.base.loop_map = {}
	end
	user_info.base.loop_map[self._name] = self._info
	self._target.anti_scroll_list:AddChild(self._item, self._child_index)
	self._target.tab_child.save = false
end

assert(ALittle.RevokeObject, " extends class:ALittle.RevokeObject is nil")
ALittleIDE.IDEAntiAddAttrRevoke = Lua.Class(ALittle.RevokeObject, "ALittleIDE.IDEAntiAddAttrRevoke")

function ALittleIDE.IDEAntiAddAttrRevoke:Ctor(target, name, info, anti_item, link_item)
	___rawset(self, "_target", target)
	___rawset(self, "_name", name)
	___rawset(self, "_info", info)
	___rawset(self, "_anti_item", anti_item)
	___rawset(self, "_link_item", link_item)
end

function ALittleIDE.IDEAntiAddAttrRevoke:Forward()
	local user_info = self._target.tab_child.tree_object.user_info
	if user_info.base.loop_map == nil then
		return
	end
	local info = user_info.base.loop_map[self._name]
	if info == nil then
		return
	end
	ALittle.List_Push(info.childs, self._info)
	if self._target.cur_show == self._name then
		self._target.anti_anti_linear:AddChild(self._anti_item)
		self._target.anti_link_linear:AddChild(self._link_item)
		local static_object_v = self._target.anti_screen.static_object_v
		static_object_v.height = self._target.anti_link_linear.y + self._target.anti_link_linear.height
		self._target.anti_screen:AdjustScrollBar()
	end
	self._target.tab_child.save = false
end

function ALittleIDE.IDEAntiAddAttrRevoke:Back()
	local user_info = self._target.tab_child.tree_object.user_info
	if user_info.base.loop_map == nil then
		return
	end
	local info = user_info.base.loop_map[self._name]
	if info == nil then
		return
	end
	ALittle.List_Remove(info.childs, ALittle.List_Len(info.childs))
	if self._target.cur_show == self._name then
		self._target.anti_anti_linear:RemoveChild(self._anti_item)
		self._target.anti_link_linear:RemoveChild(self._link_item)
		local static_object_v = self._target.anti_screen.static_object_v
		static_object_v.height = self._target.anti_link_linear.y + self._target.anti_link_linear.height
		self._target.anti_screen:AdjustScrollBar()
	end
	self._target.tab_child.save = false
end

assert(ALittle.RevokeObject, " extends class:ALittle.RevokeObject is nil")
ALittleIDE.IDEAntiRemoveAttrRevoke = Lua.Class(ALittle.RevokeObject, "ALittleIDE.IDEAntiRemoveAttrRevoke")

function ALittleIDE.IDEAntiRemoveAttrRevoke:Ctor(target, name, info, anti_item, link_item, child_index)
	___rawset(self, "_target", target)
	___rawset(self, "_name", name)
	___rawset(self, "_info", info)
	___rawset(self, "_anti_item", anti_item)
	___rawset(self, "_link_item", link_item)
	___rawset(self, "_child_index", child_index)
end

function ALittleIDE.IDEAntiRemoveAttrRevoke:Forward()
	local user_info = self._target.tab_child.tree_object.user_info
	if user_info.base.loop_map == nil then
		return
	end
	local info = user_info.base.loop_map[self._name]
	if info == nil then
		return
	end
	ALittle.List_Remove(info.childs, self._child_index)
	if self._target.cur_show == self._name then
		self._target.anti_anti_linear:RemoveChild(self._anti_item)
		self._target.anti_link_linear:RemoveChild(self._link_item)
		local static_object_v = self._target.anti_screen.static_object_v
		static_object_v.height = self._target.anti_link_linear.y + self._target.anti_link_linear.height
		self._target.anti_screen:AdjustScrollBar()
	end
	self._target.tab_child.save = false
end

function ALittleIDE.IDEAntiRemoveAttrRevoke:Back()
	local user_info = self._target.tab_child.tree_object.user_info
	if user_info.base.loop_map == nil then
		return
	end
	local info = user_info.base.loop_map[self._name]
	if info == nil then
		return
	end
	ALittle.List_Insert(info.childs, self._child_index, self._info)
	if self._target.cur_show == self._name then
		self._target.anti_anti_linear:AddChild(self._anti_item, self._child_index)
		self._target.anti_link_linear:AddChild(self._link_item, self._child_index)
		local static_object_v = self._target.anti_screen.static_object_v
		static_object_v.height = self._target.anti_link_linear.y + self._target.anti_link_linear.height
		self._target.anti_screen:AdjustScrollBar()
	end
	self._target.tab_child.save = false
end

assert(ALittle.RevokeObject, " extends class:ALittle.RevokeObject is nil")
ALittleIDE.IDEAntiInsertLoopRevoke = Lua.Class(ALittle.RevokeObject, "ALittleIDE.IDEAntiInsertLoopRevoke")

function ALittleIDE.IDEAntiInsertLoopRevoke:Ctor(target, info, loop_item, child_index)
	___rawset(self, "_target", target)
	___rawset(self, "_info", info)
	___rawset(self, "_loop_item", loop_item)
	___rawset(self, "_child_index", child_index)
end

function ALittleIDE.IDEAntiInsertLoopRevoke:Forward()
	ALittle.List_Insert(self._target.info.childs, self._child_index, self._info)
	self._target.container:AddChild(self._loop_item, self._child_index)
	self._target.panel.tab_child.save = false
end

function ALittleIDE.IDEAntiInsertLoopRevoke:Back()
	ALittle.List_Remove(self._target.info.childs, self._child_index)
	self._target.container:RemoveChild(self._loop_item)
	if self._target.panel.cur_loop_item == self._loop_item then
		self._target.panel:HideAntiLoop()
	end
	self._target.panel.tab_child.save = false
end

assert(ALittle.RevokeObject, " extends class:ALittle.RevokeObject is nil")
ALittleIDE.IDEAntiDeleteLoopRevoke = Lua.Class(ALittle.RevokeObject, "ALittleIDE.IDEAntiDeleteLoopRevoke")

function ALittleIDE.IDEAntiDeleteLoopRevoke:Ctor(target, info, loop_item, child_index)
	___rawset(self, "_target", target)
	___rawset(self, "_info", info)
	___rawset(self, "_loop_item", loop_item)
	___rawset(self, "_child_index", child_index)
end

function ALittleIDE.IDEAntiDeleteLoopRevoke:Forward()
	ALittle.List_Remove(self._target.info.childs, self._child_index)
	self._target.container:RemoveChild(self._loop_item)
	if self._target.panel.cur_loop_item == self._loop_item then
		self._target.panel:HideAntiLoop()
	end
	self._target.panel.tab_child.save = false
end

function ALittleIDE.IDEAntiDeleteLoopRevoke:Back()
	ALittle.List_Insert(self._target.info.childs, self._child_index, self._info)
	self._target.container:AddChild(self._loop_item, self._child_index)
	self._target.panel.tab_child.save = false
end

assert(ALittle.RevokeObject, " extends class:ALittle.RevokeObject is nil")
ALittleIDE.IDEAntiClearLoopRevoke = Lua.Class(ALittle.RevokeObject, "ALittleIDE.IDEAntiClearLoopRevoke")

function ALittleIDE.IDEAntiClearLoopRevoke:Ctor(target, info_list, loop_item_list)
	___rawset(self, "_target", target)
	___rawset(self, "_info_list", info_list)
	___rawset(self, "_loop_item_list", loop_item_list)
end

function ALittleIDE.IDEAntiClearLoopRevoke:Forward()
	self._target.info.childs = {}
	self._target.container:RemoveAllChild()
	self._target.panel:HideAntiLoop()
	self._target.panel.tab_child.save = false
end

function ALittleIDE.IDEAntiClearLoopRevoke:Back()
	self._target.info.childs = self._info_list
	for index, child in ___ipairs(self._loop_item_list) do
		self._target.container:AddChild(child)
	end
	self._target.panel.tab_child.save = false
end

assert(ALittle.RevokeObject, " extends class:ALittle.RevokeObject is nil")
ALittleIDE.IDEAntiLoopTargetValueChangeRevoke = Lua.Class(ALittle.RevokeObject, "ALittleIDE.IDEAntiLoopTargetValueChangeRevoke")

function ALittleIDE.IDEAntiLoopTargetValueChangeRevoke:Ctor(target, old_value, new_value)
	___rawset(self, "_target", target)
	___rawset(self, "_old_value", old_value)
	___rawset(self, "_new_value", new_value)
end

function ALittleIDE.IDEAntiLoopTargetValueChangeRevoke:Forward()
	self._target.info.target = ALittleIDE.IDEAntiFrameLoopItem.StringToValue(self._target.item.info.attribute, self._new_value)
	self._target:UpdateText()
	if self._target.item.panel.cur_loop_item == self._target then
		if self._target.info.clazz == "LoopLinear" then
			self._target.item.panel.linear_target_value.text = ALittleIDE.IDEAntiFrameLoopItem.ValueToString(self._target.info.target)
		elseif self._target.info.clazz == "LoopAttribute" then
			self._target.item.panel.attribute_target_value.text = ALittleIDE.IDEAntiFrameLoopItem.ValueToString(self._target.info.target)
		elseif self._target.info.clazz == "LoopRit" then
			self._target.item.panel.rit_target_value.text = ALittleIDE.IDEAntiFrameLoopItem.ValueToString(self._target.info.target)
		end
	end
	self._target.item.panel.tab_child.save = false
end

function ALittleIDE.IDEAntiLoopTargetValueChangeRevoke:Back()
	self._target.info.target = ALittleIDE.IDEAntiFrameLoopItem.StringToValue(self._target.item.info.attribute, self._old_value)
	self._target:UpdateText()
	if self._target.item.panel.cur_loop_item == self._target then
		if self._target.info.clazz == "LoopLinear" then
			self._target.item.panel.linear_target_value.text = ALittleIDE.IDEAntiFrameLoopItem.ValueToString(self._target.info.target)
		elseif self._target.info.clazz == "LoopAttribute" then
			self._target.item.panel.attribute_target_value.text = ALittleIDE.IDEAntiFrameLoopItem.ValueToString(self._target.info.target)
		elseif self._target.info.clazz == "LoopRit" then
			self._target.item.panel.rit_target_value.text = ALittleIDE.IDEAntiFrameLoopItem.ValueToString(self._target.info.target)
		end
	end
	self._target.item.panel.tab_child.save = false
end

assert(ALittle.RevokeObject, " extends class:ALittle.RevokeObject is nil")
ALittleIDE.IDEAntiLoopTotalTimeChangeRevoke = Lua.Class(ALittle.RevokeObject, "ALittleIDE.IDEAntiLoopTotalTimeChangeRevoke")

function ALittleIDE.IDEAntiLoopTotalTimeChangeRevoke:Ctor(target, old_value, new_value)
	___rawset(self, "_target", target)
	___rawset(self, "_old_value", old_value)
	___rawset(self, "_new_value", new_value)
end

function ALittleIDE.IDEAntiLoopTotalTimeChangeRevoke:Forward()
	self._target.info.total_time = self._new_value
	self._target:UpdateText()
	if self._target.item.panel.cur_loop_item == self._target then
		if self._target.info.clazz == "LoopLinear" then
			self._target.item.panel.linear_total_time.text = self._target.info.total_time
		elseif self._target.info.clazz == "LoopRit" then
			self._target.item.panel.rit_total_time.text = self._target.info.total_time
		end
	end
	self._target:UpdateShow()
	self._target:DispatchEvent(___all_struct[-431205740], {})
	self._target.item.panel.tab_child.save = false
end

function ALittleIDE.IDEAntiLoopTotalTimeChangeRevoke:Back()
	self._target.info.total_time = self._old_value
	self._target:UpdateText()
	if self._target.item.panel.cur_loop_item == self._target then
		if self._target.info.clazz == "LoopLinear" then
			self._target.item.panel.linear_total_time.text = self._target.info.total_time
		elseif self._target.info.clazz == "LoopRit" then
			self._target.item.panel.rit_total_time.text = self._target.info.total_time
		end
	end
	self._target:UpdateShow()
	self._target:DispatchEvent(___all_struct[-431205740], {})
	self._target.item.panel.tab_child.save = false
end

assert(ALittle.RevokeObject, " extends class:ALittle.RevokeObject is nil")
ALittleIDE.IDEAntiLoopDelayTimeChangeRevoke = Lua.Class(ALittle.RevokeObject, "ALittleIDE.IDEAntiLoopDelayTimeChangeRevoke")

function ALittleIDE.IDEAntiLoopDelayTimeChangeRevoke:Ctor(target, old_value, new_value)
	___rawset(self, "_target", target)
	___rawset(self, "_old_value", old_value)
	___rawset(self, "_new_value", new_value)
end

function ALittleIDE.IDEAntiLoopDelayTimeChangeRevoke:Forward()
	self._target.info.delay_time = self._new_value
	self._target:UpdateText()
	if self._target.item.panel.cur_loop_item == self._target then
		if self._target.info.clazz == "LoopLinear" then
			self._target.item.panel.linear_delay_time.text = self._target.info.delay_time
		elseif self._target.info.clazz == "LoopAttribute" then
			self._target.item.panel.attribute_delay_time.text = self._target.info.delay_time
		elseif self._target.info.clazz == "LoopRit" then
			self._target.item.panel.rit_delay_time.text = self._target.info.delay_time
		end
	end
	self._target:UpdateShow()
	self._target:DispatchEvent(___all_struct[-431205740], {})
	self._target.item.panel.tab_child.save = false
end

function ALittleIDE.IDEAntiLoopDelayTimeChangeRevoke:Back()
	self._target.info.delay_time = self._old_value
	self._target:UpdateText()
	if self._target.item.panel.cur_loop_item == self._target then
		if self._target.info.clazz == "LoopLinear" then
			self._target.item.panel.linear_delay_time.text = self._target.info.delay_time
		elseif self._target.info.clazz == "LoopAttribute" then
			self._target.item.panel.attribute_delay_time.text = self._target.info.delay_time
		elseif self._target.info.clazz == "LoopRit" then
			self._target.item.panel.rit_delay_time.text = self._target.info.delay_time
		end
	end
	self._target:UpdateShow()
	self._target:DispatchEvent(___all_struct[-431205740], {})
	self._target.item.panel.tab_child.save = false
end

end