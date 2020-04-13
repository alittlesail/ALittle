
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(1337289812, "ALittle.UIButtonDragEvent", {
name = "ALittle.UIButtonDragEvent", ns_name = "ALittle", rl_name = "UIButtonDragEvent", hash_code = 1337289812,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(1301789264, "ALittle.UIButtonDragBeginEvent", {
name = "ALittle.UIButtonDragBeginEvent", ns_name = "ALittle", rl_name = "UIButtonDragBeginEvent", hash_code = 1301789264,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(150587926, "ALittle.UIButtonDragEndEvent", {
name = "ALittle.UIButtonDragEndEvent", ns_name = "ALittle", rl_name = "UIButtonDragEndEvent", hash_code = 150587926,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
IDETreeLogic = ALittle.Class(ALittle.DisplayLayout, "ALittleIDE.IDETreeLogic")

function IDETreeLogic:Ctor(ctrl_sys, user_info, tab_child)
	___rawset(self, "_tab_child", tab_child)
	___rawset(self, "_user_info", user_info)
	___rawset(self, "_attr_panel", nil)
	___rawset(self, "_drag_effect", nil)
	___rawset(self, "_drag_shift", false)
end

function IDETreeLogic.__getter:user_info()
	return self._user_info
end

function IDETreeLogic.__getter:tab_child()
	return self._tab_child
end

function IDETreeLogic.__getter:user_info()
	return self._user_info
end

function IDETreeLogic.__getter:attr_panel()
	return self._attr_panel
end

function IDETreeLogic.__getter:title()
	return self._item_title.text
end

function IDETreeLogic.__setter:fold(value)
end

function IDETreeLogic:IsRoot()
	return self._user_info.root
end

function IDETreeLogic:IsTree()
	return false
end

function IDETreeLogic:CanAddChild()
	return false
end

function IDETreeLogic:GetDesc()
	local desc = self._user_info.base.description
	if desc ~= nil then
		return desc
	end
	desc = self._user_info.default.description
	if desc ~= nil then
		return desc
	end
	return ""
end

function IDETreeLogic:SetDesc(text)
	self._user_info.base.description = text
	if self._user_info.base.description == "" or self._user_info.base.description == self._user_info.default.description then
		self._user_info.base.description = nil
	end
	self._tab_child:Save(false)
	self:UpdateDesc()
end

function IDETreeLogic:UpdateDesc()
	local title = ""
	if self._user_info.extends_root then
		title = "[E]" .. title
	end
	if self._user_info.child_type ~= nil and self._user_info.child_type ~= "child" then
		title = title .. "[" .. self._user_info.child_type .. "]"
	end
	title = title .. "[" .. self._user_info.default.__class .. "]"
	if self._user_info.base.description ~= nil then
		title = title .. self._user_info.base.description
	elseif self._user_info.default.description ~= nil then
		title = title .. self._user_info.default.description
	elseif self._user_info.base.text ~= nil then
		title = title .. self._user_info.base.text
	elseif self._user_info.default.text ~= nil then
		title = title .. self._user_info.default.text
	end
	self._item_title.text = title
	if self._user_info.child_type == nil then
		self._tab_child:UpdateTitle()
	end
end

function IDETreeLogic:RemoveAttributePanel()
	if self._attr_panel == nil then
		return
	end
	self._tab_child.control_screen:RemoveChild(self._attr_panel.layer)
	g_IDEAttributeManager:SetTitle("")
end

function IDETreeLogic:ShowAttributePanel()
	self._tab_child.control_screen:RemoveAllChild()
	self._item_button.selected = true
	if self._attr_panel == nil then
		local class_name = self._user_info.default.__class .. "S"
		local clazz = ALittleIDE[class_name]
		self._attr_panel = ALittle.NewObject(clazz, self._user_info, self._tab_child, self)
		self._attr_panel.layer._user_data = self._attr_panel
		self._attr_panel.layer.disabled = self._user_info.extends
	end
	g_IDEAttributeManager:SetTitle(self._attr_panel.title)
	self._tab_child.control_screen:AddChild(self._attr_panel.layer)
end

function IDETreeLogic:ShowFocus(is_group)
	self:ShowAttributePanel()
	self._tab_child:ShowTreeItemFocus(self)
	self._tab_child:ShowHandleQuad(self, is_group)
end

function IDETreeLogic:HandleClick(event)
	if self._user_info.extends then
		self:ShowAttributePanel()
		return
	end
	local shift = (A_UISystem.sym_map[1073742049] ~= nil or A_UISystem.sym_map[1073742053] ~= nil)
	if shift and self._tab_child:IsShowHandleQuad(self) then
		self._tab_child:HideHandleQuad(self)
	else
		self._tab_child:ShowHandleQuad(self)
	end
end

function IDETreeLogic:HandleMoveIn(event)
	local link = self._user_info.base.__link
	if link == nil then
		link = self._user_info.default.__link
	end
	if link == nil then
		return
	end
	g_IDEControlTree:ShowTip(link)
	g_IDEControlTree:MoveTip(A_UISystem.mouse_x + 10, A_UISystem.mouse_y + 20)
end

function IDETreeLogic:HandleMouseMove(event)
	local link = self._user_info.base.__link
	if link == nil then
		link = self._user_info.default.__link
	end
	if link == nil then
		return
	end
	g_IDEControlTree:MoveTip(A_UISystem.mouse_x + 10, A_UISystem.mouse_y + 20)
end

function IDETreeLogic:HandleMoveOut(event)
	local link = self._user_info.base.__link
	if link == nil then
		link = self._user_info.default.__link
	end
	if link == nil then
		return
	end
	g_IDEControlTree:HideTip()
end

function IDETreeLogic:HandleDragBegin(event)
	self._drag_shift = (A_UISystem.sym_map[1073742049] ~= nil or A_UISystem.sym_map[1073742053] ~= nil)
	if self._drag_shift == false then
		event.target = self._tab_child.tree_screen
		self._tab_child.tree_screen:DispatchEvent(___all_struct[1301789264], event)
		return
	end
	local button = self._head
	if button == nil then
		button = self._item
	end
	local x, y = button:LocalToGlobal()
	self._drag_effect = ALittle.EffectImage(g_Control)
	self._drag_effect:Action(button)
	A_LayerManager:AddToTip(self._drag_effect)
	self._drag_effect.x = x
	self._drag_effect.y = y
	self._drag_effect.alpha = 0.6
end

function IDETreeLogic:HandleDrag(event)
	if self._drag_shift == false then
		event.target = self._tab_child.tree_screen
		self._tab_child.tree_screen:DispatchEvent(___all_struct[1337289812], event)
		return
	end
	if self._drag_effect == nil then
		return
	end
	self._drag_effect.x = self._drag_effect.x + event.delta_x
	self._drag_effect.y = self._drag_effect.y + event.delta_y
end

function IDETreeLogic:HandleDragEnd(event)
	if self._drag_shift == false then
		event.target = self._tab_child.tree_screen
		self._tab_child.tree_screen:DispatchEvent(___all_struct[150587926], event)
		return
	end
	if self._drag_effect ~= nil then
		A_LayerManager:RemoveFromTip(self._drag_effect)
		self._drag_effect:Clear()
		self._drag_effect = nil
	end
	if self._tab_child.tree_object == self then
		return
	end
	local x, y = self._tab_child.tree_object:LocalToGlobal()
	local delta_x = event.abs_x - x
	local delta_y = event.abs_y - y
	local target = self._tab_child.tree_object:PickUp(delta_x, delta_y)
	if target == nil then
		ALittle.Log("IDETreeLogic:HandleDrag} target null")
		return
	end
	local tree = target._user_data
	if tree:IsGrandParent(self) then
		g_IDETool:ShowNotice("提示", "目标是自己的子控件，移动失败")
		return
	end
	if tree._user_info.extends then
		g_IDETool:ShowNotice("提示", "目标控件不能操作，移动失败")
		return
	end
	local copy_list = {}
	local info = {}
	info.index = 1
	info.info = self:CalcInfo()
	copy_list[1] = info
	ALittle.System_SetClipboardText(json.encode(copy_list))
	local revoke_bind = IDERevokeBind()
	if tree:IsTree() then
		self._tab_child:RightControlTreePasteImpl(tree, nil, 1, revoke_bind, ALittle.Bind(self.HandleDragEndAndCut, self, revoke_bind))
	else
		local common_parent = tree._logic_parent
		if common_parent == nil then
			g_IDETool:ShowNotice("提示", "当前是根节点，并且不是容器，移动失败")
			return
		end
		local child_index = common_parent:GetChildIndex(tree)
		x, y = target:LocalToGlobal()
		y = y + target.height / 2
		if event.abs_y > y then
			child_index = child_index + 1
		end
		self._tab_child:RightControlTreePasteImpl(common_parent, nil, child_index, revoke_bind, ALittle.Bind(self.HandleDragEndAndCut, self, revoke_bind))
	end
end

function IDETreeLogic:HandleDragEndAndCut(revoke_bind, result, list)
	if result == false then
		return
	end
	self:TreeCut(revoke_bind)
	self._tab_child.revoke_list:PushRevoke(revoke_bind)
end

function IDETreeLogic:TransferUp()
	local parent = self._logic_parent
	if parent == nil then
		return
	end
	local index = parent:GetChildIndex(self)
	if index == 1 then
		return
	end
	index = index - 1
	parent:SetChildIndex(self, index)
	parent.user_info.object:SetChildIndex(self._user_info.object, index)
	self.tab_child:Save(false)
	local revoke = IDEChildUpDownRevoke(parent, self, "up")
	self._tab_child.revoke_list:PushRevoke(revoke)
end

function IDETreeLogic:TransferDown()
	local parent = self._logic_parent
	if parent == nil then
		return
	end
	local index = parent:GetChildIndex(self)
	if index == parent.child_count then
		return
	end
	index = index + 1
	parent:SetChildIndex(self, index)
	parent.user_info.object:SetChildIndex(self._user_info.object, index)
	self.tab_child:Save(false)
	local revoke = IDEChildUpDownRevoke(parent, self, "down")
	self._tab_child.revoke_list:PushRevoke(revoke)
end

function IDETreeLogic:TreePaste(info, child_type, child_index, is_group, revoke_bind)
	local inner_revoke_bind = IDERevokeBind()
	if child_type ~= "child" and self._user_info.object[child_type] ~= nil then
		self._user_info.object[child_type] = nil
		for k, v in ___ipairs(self.childs) do
			if v.user_info.child_type == child_type then
				self:RemoveChild(v)
				local revoke = IDEDeleteRevoke(self, v, k)
				inner_revoke_bind:PushRevoke(revoke)
				break
			end
		end
	end
	local control_name = "alittleide201601291343"
	g_IDEProject.project.control:RegisterInfo(control_name, ALittle.String_CopyTable(info))
	local object = g_IDEProject.project.control:CreateControl(control_name)
	g_IDEProject.project.control:UnRegisterInfo(control_name)
	if child_type == "child" then
		self._user_info.object:AddChild(object, child_index)
	else
		self._user_info.object[child_type] = object
	end
	local tree_object = IDEUtility_CreateTree(info, false, object, child_type, self._tab_child, false)
	self:AddChild(tree_object, child_index)
	self._tab_child:Save(false)
	local index = self:GetChildIndex(tree_object)
	local revoke = IDEChildShowRevoke(self, tree_object, index)
	inner_revoke_bind:PushRevoke(revoke)
	if revoke_bind ~= nil then
		revoke_bind:PushRevoke(inner_revoke_bind)
	else
		self.tab_child.revoke_list:PushRevoke(inner_revoke_bind)
	end
	tree_object:ShowFocus(is_group)
	return tree_object
end

function IDETreeLogic:TreeAdd(extends_name, class_name, child_type)
	local extends_info = g_IDEProject.project.control_map[extends_name]
	if extends_name ~= "" and extends_info == nil then
		return nil
	end
	local revoke_bind = IDERevokeBind()
	if child_type ~= "child" and self._user_info.object[child_type] ~= nil then
		self._user_info.object[child_type] = nil
		for k, v in ___ipairs(self.childs) do
			if v.user_info.child_type == child_type then
				self:RemoveChild(v)
				local revoke = IDEDeleteRevoke(self, v, k)
				revoke_bind:PushRevoke(revoke)
				break
			end
		end
	end
	local tree_object = nil
	if extends_info == nil then
		local info = {}
		info.__class = class_name
		local object = ALittle.NewObject(ALittle[info.__class], g_IDEProject.project.control)
		IDEUtility_NewGiveBaseCase(info, object)
		if child_type == "child" then
			self._user_info.object:AddChild(object)
		else
			self._user_info.object[child_type] = object
		end
		tree_object = IDEUtility_CreateTree(info, false, object, child_type, self._tab_child, false)
		self:AddChild(tree_object)
		self._tab_child:Save(false)
		local index = self:GetChildIndex(tree_object)
		local revoke = IDEChildShowRevoke(self, tree_object, index)
		revoke_bind:PushRevoke(revoke)
		tree_object:ShowAttributePanel()
		self._tab_child:ShowTreeItemFocus(tree_object)
	else
		local info = {}
		info.__extends = extends_name
		local object = g_IDEProject.project.control:CreateControl(extends_name)
		if child_type == "child" then
			self._user_info.object:AddChild(object)
		else
			self._user_info.object[child_type] = object
		end
		tree_object = IDEUtility_CreateTree(info, false, object, child_type, self._tab_child, false)
		self:AddChild(tree_object)
		self._tab_child:Save(false)
		local index = self:GetChildIndex(tree_object)
		local revoke = IDEChildShowRevoke(self, tree_object, index)
		revoke_bind:PushRevoke(revoke)
		tree_object:ShowAttributePanel()
		self._tab_child:ShowTreeItemFocus(tree_object)
	end
	self._tab_child.revoke_list:PushRevoke(revoke_bind)
	return tree_object
end

function IDETreeLogic:TreeReplace(extends_name, class_name, child_type)
	local extends_info = g_IDEProject.project.control_map[extends_name]
	if extends_name ~= "" and extends_info == nil then
		return
	end
	local revoke_bind = IDERevokeBind()
	local target_parent = self._logic_parent
	local child_index = nil
	if self._user_info.child_type ~= "child" then
		target_parent._user_info.object[child_type] = nil
		for k, v in ___ipairs(target_parent.childs) do
			if v._user_info.child_type == child_type then
				target_parent:RemoveChild(v)
				local revoke = IDEDeleteRevoke(target_parent, v, k)
				revoke_bind:PushRevoke(revoke)
				break
			end
		end
	else
		child_index = target_parent:GetChildIndex(self)
		target_parent._user_info.object:RemoveChild(self._user_info.object)
		target_parent:RemoveChild(self)
		local revoke = IDEDeleteRevoke(target_parent, self, child_index)
		revoke_bind:PushRevoke(revoke)
	end
	local tree_object = nil
	if extends_info == nil then
		local info = {}
		info.__class = class_name
		local object = ALittle.NewObject(ALittle[info.__class], g_IDEProject.project.control)
		IDEUtility_NewGiveBaseCase(info, object)
		if child_type == "child" then
			target_parent._user_info.object:AddChild(object, child_index)
		else
			target_parent._user_info.object[child_type] = object
		end
		tree_object = IDEUtility_CreateTree(info, false, object, child_type, target_parent._tab_child, false)
		target_parent:AddChild(tree_object, child_index)
		target_parent._tab_child:Save(false)
		local index = target_parent:GetChildIndex(tree_object)
		local revoke = IDEChildShowRevoke(target_parent, tree_object, index)
		revoke_bind:PushRevoke(revoke)
	else
		local info = {}
		info.__extends = extends_name
		local object = g_IDEProject.project.control:CreateControl(extends_name)
		if child_type == "child" then
			target_parent._user_info.object:AddChild(object, child_index)
		else
			target_parent._user_info.object[child_type] = object
		end
		tree_object = IDEUtility_CreateTree(info, false, object, child_type, target_parent._tab_child, false)
		target_parent:AddChild(tree_object, child_index)
		target_parent._tab_child:Save(false)
		local index = target_parent:GetChildIndex(tree_object)
		local revoke = IDEChildShowRevoke(target_parent, tree_object, index)
		revoke_bind:PushRevoke(revoke)
	end
	tree_object:ShowAttributePanel()
	if self._user_info.base.x_type ~= nil then
		tree_object._attr_panel:SetXType(self._user_info.base.x_type, revoke_bind)
	else
		tree_object._attr_panel:SetXType(self._user_info.default.x_type, revoke_bind)
	end
	if self._user_info.base.y_type ~= nil then
		tree_object._attr_panel:SetYType(self._user_info.base.y_type, revoke_bind)
	else
		tree_object._attr_panel:SetYType(self._user_info.default.y_type, revoke_bind)
	end
	if self._user_info.base.x_value ~= nil then
		tree_object._attr_panel:SetXValue(self._user_info.base.x_value, revoke_bind)
	else
		tree_object._attr_panel:SetXValue(self._user_info.default.x_value, revoke_bind)
	end
	if self._user_info.base.y_value ~= nil then
		tree_object._attr_panel:SetYValue(self._user_info.base.y_value, revoke_bind)
	else
		tree_object._attr_panel:SetYValue(self._user_info.default.y_value, revoke_bind)
	end
	if self._user_info.base.width_type ~= nil then
		tree_object._attr_panel:SetWType(self._user_info.base.width_type, revoke_bind)
	else
		tree_object._attr_panel:SetWType(self._user_info.default.width_type, revoke_bind)
	end
	if self._user_info.base.height_type ~= nil then
		tree_object._attr_panel:SetHType(self._user_info.base.height_type, revoke_bind)
	else
		tree_object._attr_panel:SetHType(self._user_info.default.height_type, revoke_bind)
	end
	if self._user_info.base.width_value ~= nil then
		tree_object._attr_panel:SetWValue(self._user_info.base.width_value, revoke_bind)
	else
		tree_object._attr_panel:SetWValue(self._user_info.default.width_value, revoke_bind)
	end
	if self._user_info.base.height_value ~= nil then
		tree_object._attr_panel:SetHValue(self._user_info.base.height_value, revoke_bind)
	else
		tree_object._attr_panel:SetHValue(self._user_info.default.height_value, revoke_bind)
	end
	if self._user_info.base.alpha ~= nil then
		tree_object._attr_panel:SetAlpha(self._user_info.base.alpha * 255, revoke_bind)
	else
		tree_object._attr_panel:SetAlpha(self._user_info.default.alpha * 255, revoke_bind)
	end
	if self._user_info.base.red ~= nil then
		tree_object._attr_panel:SetRed(self._user_info.base.red * 255, revoke_bind)
	else
		tree_object._attr_panel:SetRed(self._user_info.default.red * 255, revoke_bind)
	end
	if self._user_info.base.green ~= nil then
		tree_object._attr_panel:SetGreen(self._user_info.base.green * 255, revoke_bind)
	else
		tree_object._attr_panel:SetGreen(self._user_info.default.green * 255, revoke_bind)
	end
	if self._user_info.base.blue ~= nil then
		tree_object._attr_panel:SetBlue(self._user_info.base.blue * 255, revoke_bind)
	else
		tree_object._attr_panel:SetBlue(self._user_info.default.blue * 255, revoke_bind)
	end
	if self._user_info.base.scale_x ~= nil then
		tree_object._attr_panel:SetScaleX(self._user_info.base.scale_x, revoke_bind)
	else
		tree_object._attr_panel:SetScaleX(self._user_info.default.scale_x, revoke_bind)
	end
	if self._user_info.base.scale_y ~= nil then
		tree_object._attr_panel:SetScaleY(self._user_info.base.scale_y, revoke_bind)
	else
		tree_object._attr_panel:SetScaleY(self._user_info.default.scale_y, revoke_bind)
	end
	if self._user_info.base.center_x ~= nil then
		tree_object._attr_panel:SetCenterX(self._user_info.base.center_x, revoke_bind)
	else
		tree_object._attr_panel:SetCenterX(self._user_info.default.center_x, revoke_bind)
	end
	if self._user_info.base.center_y ~= nil then
		tree_object._attr_panel:SetCenterY(self._user_info.base.center_y, revoke_bind)
	else
		tree_object._attr_panel:SetCenterY(self._user_info.default.center_y, revoke_bind)
	end
	if self._user_info.base.angle ~= nil then
		tree_object._attr_panel:SetAngle(self._user_info.base.angle, revoke_bind)
	else
		tree_object._attr_panel:SetAngle(self._user_info.default.angle, revoke_bind)
	end
	if self._user_info.base.hand_cursor ~= nil then
		tree_object._attr_panel:SetHandCursor(self._user_info.base.hand_cursor, revoke_bind)
	else
		tree_object._attr_panel:SetHandCursor(self._user_info.default.hand_cursor, revoke_bind)
	end
	if self._user_info.base.visible ~= nil then
		tree_object._attr_panel:SetVisible(self._user_info.base.visible, revoke_bind)
	else
		tree_object._attr_panel:SetVisible(self._user_info.default.visible, revoke_bind)
	end
	if self._user_info.base.disabled ~= nil then
		tree_object._attr_panel:SetDisabled(self._user_info.base.disabled, revoke_bind)
	else
		tree_object._attr_panel:SetDisabled(self._user_info.default.disabled, revoke_bind)
	end
	if self._user_info.base.description ~= nil then
		tree_object._attr_panel:SetDescription(self._user_info.base.description, revoke_bind)
	else
		tree_object._attr_panel:SetDescription(self._user_info.default.description, revoke_bind)
	end
	if self._user_info.base.__link ~= nil then
		tree_object._attr_panel:SetLink(self._user_info.base.__link, revoke_bind)
	else
		tree_object._attr_panel:SetLink(self._user_info.default.__link, revoke_bind)
	end
	if self._user_info.base.__target_class ~= nil then
		tree_object._attr_panel:SetTargetClass(self._user_info.base.__target_class, revoke_bind)
	else
		tree_object._attr_panel:SetTargetClass(self._user_info.default.__target_class, revoke_bind)
	end
	if self._user_info.base.__event ~= nil then
		tree_object._attr_panel:SetEvent(self._user_info.base.__event, revoke_bind)
	else
		tree_object._attr_panel:SetEvent(self._user_info.default.__event, revoke_bind)
	end
	self._tab_child:ShowTreeItemFocus(tree_object)
	target_parent._tab_child.revoke_list:PushRevoke(revoke_bind)
end

function IDETreeLogic:TreeDelete(revoke_bind)
	local parent = self._logic_parent
	if parent == nil then
		return
	end
	local child_type = self._user_info.child_type
	if child_type == "child" then
		parent.user_info.object:RemoveChild(self._user_info.object)
	else
		parent.user_info.object[child_type] = nil
	end
	local index = parent:GetChildIndex(self)
	local revoke = IDEDeleteRevoke(parent, self, index)
	if revoke_bind ~= nil then
		revoke_bind:PushRevoke(revoke)
	else
		self._tab_child.revoke_list:PushRevoke(revoke)
	end
	self._tab_child:Save(false)
	parent:RemoveChild(self)
	self:RemoveAttributePanel()
	self._tab_child:UpdateHandleQuadRemove(self)
	parent.tab_child:UpdateHandleQuadLayout(parent)
end

function IDETreeLogic:TreeCut(revoke_bind)
	local parent = self._logic_parent
	if parent == nil then
		return
	end
	local child_type = self._user_info.child_type
	if child_type == "child" then
		parent._user_info.object:RemoveChild(self._user_info.object)
	else
		parent._user_info.object[child_type] = nil
	end
	local index = parent:GetChildIndex(self)
	local revoke = IDEDeleteRevoke(parent, self, index)
	if revoke_bind ~= nil then
		revoke_bind:PushRevoke(revoke)
	else
		self._tab_child.revoke_list:PushRevoke(revoke)
	end
	self._tab_child:Save(false)
	parent:RemoveChild(self)
	self._tab_child:UpdateHandleQuadRemove(self)
	parent.tab_child:UpdateHandleQuadLayout(parent)
end

function IDETreeLogic:ChangeText(text)
	local object = self._user_info.object
	local old_base = self._user_info.base.text
	local old_object = object.text
	object.text = text
	self._user_info.base.text = object.text
	if self._user_info.base.text == self._user_info.default.text then
		self._user_info.base.text = nil
	end
	if self._attr_panel ~= nil then
		local text_object = self._attr_panel["_text"]
		text_object.text = object.text
	end
	self._tab_child:UpdateHandleQuadLayout(self)
	self._tab_child:Save(false)
	local new_base = self._user_info.base.text
	local new_object = object.text
	local old_text = nil
	local revoke = IDENatureChangeRevoke(self, "text", old_base, new_base, old_object, new_object, old_text, true)
	self._tab_child.revoke_list:PushRevoke(revoke)
end

function IDETreeLogic:DragXY(x, y)
	local object = self._user_info.object
	local old_x = object.x
	local old_y = object.y
	local target_x = old_x + x
	local target_y = old_y + y
	if object.x_type == 1 then
		object.x_value = target_x
	elseif object.x_type == 2 then
		object.x_value = target_x
	elseif object.x_type == 3 then
		object.x_value = target_x - (object._show_parent.width - object.width) / 2
	elseif object.x_type == 4 then
		object.x_value = object._show_parent.width - object.width - target_x
	elseif object.x_type == 7 then
		if object._show_parent.width == 0 then
			object.x_value = 0
		else
			object.x_value = target_x / object._show_parent.width
		end
	elseif object.x_type == 8 then
		if object._show_parent.width == 0 then
			object.x_value = 0
		else
			object.x_value = (target_x - (object._show_parent.width - object.width) / 2) / object._show_parent.width
		end
	elseif object.x_type == 9 then
		if object._show_parent.width - object.width == 0 then
			object.x_value = 0
		else
			object.x_value = 1 - target_x / (object._show_parent.width - object.width)
		end
	end
	self._user_info.base.x_value = object.x_value
	if self._user_info.base.x_value == self._user_info.default.x_value then
		self._user_info.base.x_value = nil
	end
	if object.y_type == 1 then
		object.y_value = target_y
	elseif object.y_type == 2 then
		object.y_value = target_y
	elseif object.y_type == 3 then
		object.y_value = target_y - (object._show_parent.height - object.height) / 2
	elseif object.y_type == 4 then
		object.y_value = object._show_parent.height - object.height - target_y
	elseif object.y_type == 7 then
		if object._show_parent.height == 0 then
			object.y_value = 0
		else
			object.y_value = target_y / object._show_parent.height
		end
	elseif object.y_type == 8 then
		if object._show_parent.height == 0 then
			object.y_value = 0
		else
			object.y_value = (target_y - (object._show_parent.height - object.height) / 2) / object._show_parent.height
		end
	elseif object.y_type == 9 then
		if object._show_parent.height - object.height == 0 then
			object.y_value = 0
		else
			object.y_value = 1 - target_y / (object._show_parent.height - object.height)
		end
	end
	self._user_info.base.y_value = object.y_value
	if self._user_info.base.y_value == self._user_info.default.y_value then
		self._user_info.base.y_value = nil
	end
	if self._attr_panel ~= nil then
		self._attr_panel.x_value.text = object.x_value
		self._attr_panel.y_value.text = object.y_value
	end
end

function IDETreeLogic:DragWH(width, height)
	local object = self._user_info.object
	local old_width = object.width
	local old_height = object.height
	local target_width = old_width + width
	local target_height = old_height + height
	if object.width_type == 1 then
		object.width_value = target_width
	elseif object.width_type == 4 then
		object.width_value = object._show_parent.width - target_width
	elseif object.width_type == 2 then
		if object._show_parent.width == 0 then
			object.width_value = 0
		else
			object.width_value = target_width / object._show_parent.width
		end
	end
	self._user_info.base.width_value = object.width_value
	if self._user_info.base.width_value == self._user_info.default.width_value then
		self._user_info.base.width_value = nil
	end
	if object.height_type == 1 then
		object.height_value = target_height
	elseif object.height_type == 4 then
		object.height_value = object._show_parent.height - target_height
	elseif object.height_type == 2 then
		if object._show_parent.height == 0 then
			object.height_value = 0
		else
			object.height_value = target_height / object._show_parent.height
		end
	end
	self._user_info.base.height_value = object.height_value
	if self._user_info.base.height_value == self._user_info.default.height_value then
		self._user_info.base.height_value = nil
	end
	if self._attr_panel ~= nil then
		self._attr_panel.width_value.text = object.width_value
		self._attr_panel.height_value.text = object.height_value
	end
end

function IDETreeLogic:CalcInfo()
	return nil
end

function IDETreeLogic:SearchLink(name, list)
	return nil
end

function IDETreeLogic:SearchEvent(name, list)
	return nil
end

function IDETreeLogic:SearchDescription(name, list)
	return nil
end

function IDETreeLogic:SearchTargetClass(name, list)
	return nil
end

function IDETreeLogic:SearchTextureName(name, list)
	return nil
end

function IDETreeLogic:EditPickUp(x, y)
	return nil
end

function IDETreeLogic:QuickPickUp(x, y, list)
end

function IDETreeLogic:SelectPickUp(x, y)
	return nil, nil
end

function IDETreeLogic:GetDataListForAdd()
	return nil
end

