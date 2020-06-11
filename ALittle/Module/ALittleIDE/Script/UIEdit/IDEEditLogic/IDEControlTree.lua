-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-4982446, "ALittle.DisplayInfo", {
name = "ALittle.DisplayInfo", ns_name = "ALittle", rl_name = "DisplayInfo", hash_code = -4982446,
name_list = {"__target_class","__class_func","__base_attr","__show_attr","loop_map","__class","__include","__extends","__childs","__event","__link","__shows_included","__childs_included","__extends_included","description","text","font_path","font_size","red","green","blue","alpha","bold","italic","underline","deleteline","outline","x","y","x_type","x_value","y_type","y_value","width","height","width_type","width_value","height_type","height_value","scale_x","scale_y","center_x","center_y","angle","flip","hand_cursor","visible","disabled","left_size","right_size","top_size","bottom_size","texture_name","interval","play_loop_count","var_play","base_y","head_size","gap","up_size","down_size","cursor_red","cursor_green","cursor_blue","default_text_alpha","ims_padding","margin_left","margin_right","margin_top","margin_bottom","show_count","body_margin","screen_margin_left","screen_margin_right","screen_margin_top","screen_margin_bottom","start_degree","end_degree","line_spacing","max_line_count","font_red","font_green","font_blue","margin_halign","margin_valign","cursor_margin_up","cursor_margin_down","total_size","show_size","offset_rate","offset_step","grade","row_count","col_count","row_index","col_index","u1","v1","u2","v2","u3","v3","x1","y1","x2","y2","x3","y3","x_gap","y_gap","x_start_gap","y_start_gap","button_gap","button_start","button_margin","tab_index","view_margin","child_width_margin"},
type_list = {"List<string>","any","Map<string,any>","Map<string,any>","Map<string,ALittle.LoopGroupInfo>","string","string","string","List<ALittle.DisplayInfo>","List<ALittle.EventInfo>","string","bool","bool","bool","string","string","string","int","double","double","double","double","bool","bool","bool","bool","bool","double","double","int","double","int","double","double","double","int","double","int","double","double","double","double","double","double","int","bool","bool","bool","double","double","double","double","string","int","int","bool","double","double","double","double","double","double","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","double","double","double","int","int","int","int","int","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(1025287370, "ALittleIDE.IDEPasteControlUserData", {
name = "ALittleIDE.IDEPasteControlUserData", ns_name = "ALittleIDE", rl_name = "IDEPasteControlUserData", hash_code = 1025287370,
name_list = {"target","info","child_index","revoke_bind","callback"},
type_list = {"ALittleIDE.IDETreeLogic","ALittle.DisplayInfo","int","ALittleIDE.IDERevokeBind","Functor<(bool,List<ALittleIDE.IDETreeLogic>)>"},
option_map = {}
})
ALittle.RegStruct(1653869333, "ALittle.LoopGroupInfo", {
name = "ALittle.LoopGroupInfo", ns_name = "ALittle", rl_name = "LoopGroupInfo", hash_code = 1653869333,
name_list = {"childs"},
type_list = {"List<ALittle.LoopListInfo>"},
option_map = {}
})
ALittle.RegStruct(-2110455927, "ALittle.EventInfo", {
name = "ALittle.EventInfo", ns_name = "ALittle", rl_name = "EventInfo", hash_code = -2110455927,
name_list = {"type","func"},
type_list = {"string","string"},
option_map = {}
})
ALittle.RegStruct(-1741432339, "ALittle.LoopListInfo", {
name = "ALittle.LoopListInfo", ns_name = "ALittle", rl_name = "LoopListInfo", hash_code = -1741432339,
name_list = {"link","attribute","init","childs"},
type_list = {"string","string","any","List<ALittle.LoopChildInfo>"},
option_map = {}
})
ALittle.RegStruct(-925381158, "ALittle.LoopChildInfo", {
name = "ALittle.LoopChildInfo", ns_name = "ALittle", rl_name = "LoopChildInfo", hash_code = -925381158,
name_list = {"clazz","target","total_time","delay_time"},
type_list = {"string","any","int","int"},
option_map = {}
})

IDEControlTree = Lua.Class(nil, "ALittleIDE.IDEControlTree")

function IDEControlTree:ShowTip(content)
	if self._tip_dialog == nil then
		self._tip_dialog = g_Control:CreateControl("ide_tool_tip", self)
		A_LayerManager:AddToTip(self._tip_dialog)
	end
	self._tip_dialog.visible = true
	self._tip_text.text = content
	self._tip_dialog.width = self._tip_text.width + 10
	self._tip_dialog.height = self._tip_text.height + 10
end

function IDEControlTree:MoveTip(x, y)
	if self._tip_dialog == nil then
		return
	end
	self._tip_dialog.x = x
	self._tip_dialog.y = y
end

function IDEControlTree:HideTip()
	if self._tip_dialog == nil then
		return
	end
	self._tip_dialog.visible = false
end

function IDEControlTree:HandleControlTreeItemRightClick(event)
	local target = event.target._user_data
	if target.user_info.extends then
		return
	end
	if self._control_tree_menu == nil then
		self._control_tree_menu = g_Control:CreateControl("ide_control_tree_menu", self)
	end
	self._right_control_tree_up.disabled = target.user_info.root or target.user_info.child_type ~= "child"
	self._right_control_tree_down.disabled = target.user_info.root or target.user_info.child_type ~= "child"
	self._right_control_tree_add.disabled = not target:IsTree()
	self._right_control_tree_add_image.disabled = not target:IsTree()
	self._right_control_tree_add_text.disabled = not target:IsTree()
	self._right_control_tree_cut.disabled = target.user_info.root
	self._right_control_tree_jump.disabled = not target.user_info.extends_root
	self._right_control_tree_delete.disabled = target.user_info.root
	self._right_control_tree_replace.disabled = target.user_info.root
	self._control_tree_menu._user_data = target
	self._control_tree_menu.x = A_UISystem.mouse_x
	self._control_tree_menu.y = A_UISystem.mouse_y
	if self._control_tree_menu.x + self._control_tree_menu.width > A_UISystem.view_width then
		self._control_tree_menu.x = A_UISystem.view_width - self._control_tree_menu.width
	end
	if self._control_tree_menu.y + self._control_tree_menu.height > A_UISystem.view_height then
		self._control_tree_menu.y = A_UISystem.view_height - self._control_tree_menu.height
	end
	A_LayerManager:ShowFromRight(self._control_tree_menu)
end

function IDEControlTree:HandleRightControlTreeUp(event)
	local target = self._control_tree_menu._user_data
	target:TransferUp()
end

function IDEControlTree:HandleRightControlTreeDown(event)
	local target = self._control_tree_menu._user_data
	target:TransferDown()
end

function IDEControlTree:HandleRightControlTreeAdd(event)
	A_LayerManager:HideFromRight(self._control_tree_menu)
	local target = self._control_tree_menu._user_data
	self._control_tree_menu._user_data = nil
	self:ShowAddDialog(target)
end

function IDEControlTree:HandleRightControlTreeAddImage(event)
	A_LayerManager:HideFromRight(self._control_tree_menu)
	local target = self._control_tree_menu._user_data
	self._control_tree_menu._user_data = nil
	local func = Lua.Bind(self.ImagePathSelectCallback, self, target)
	g_IDEAttrImageDialog:ShowDialog(nil, func)
end

function IDEControlTree:ImagePathSelectCallback(target, path)
	if target:CanAddChild() == false then
		g_AUITool:ShowNotice("提示", "当前控件不能添加子控件")
		return
	end
	local tree_object = target:TreeAdd("", "Image", "child")
	if tree_object == nil then
		g_AUITool:ShowNotice("提示", "添加失败")
		return
	end
	tree_object.attr_panel:SetTextureName(path, nil)
	tree_object:ShowFocus(false)
end

function IDEControlTree:HandleRightControlTreeAddText(event)
	A_LayerManager:HideFromRight(self._control_tree_menu)
	local target = self._control_tree_menu._user_data
	self._control_tree_menu._user_data = nil
	if target:CanAddChild() == false then
		g_AUITool:ShowNotice("提示", "当前控件不能添加子控件")
		return
	end
	local tree_object = target:TreeAdd("", "Text", "child")
	if tree_object == nil then
		g_AUITool:ShowNotice("提示", "添加失败")
		return
	end
	tree_object:ShowFocus(false)
end

function IDEControlTree:HandleRightControlTreeReplace(event)
	A_LayerManager:HideFromRight(self._control_tree_menu)
	local target = self._control_tree_menu._user_data
	self._control_tree_menu._user_data = nil
	self:ShowReplaceDialog(target)
end

function IDEControlTree:ShowAddDialog(target)
	if self._control_add_dialog == nil then
		self._control_add_dialog = g_Control:CreateControl("ide_add_control_dialog", self)
		self._control_add_new_type.data_list = g_IDEEnum.child_type_list
		A_LayerManager:AddToModal(self._control_add_dialog)
		self._control_add_dialog.visible = false
	end
	local data_list = target:GetDataListForAdd()
	if ALittle.List_MaxN(data_list) == 0 then
		g_AUITool:ShowNotice("提示", "当前控件不能添加子控件")
		return
	end
	self._control_add_dialog._user_data = target
	self._control_add_type.data_list = data_list
	self._control_add_dialog.visible = true
	self._control_add_extends_name.text = ""
end

function IDEControlTree:HandleAddControlCancel(event)
	self._control_add_dialog.visible = false
	self._control_add_dialog._user_data = nil
end

function IDEControlTree:HandleAddControlConfirm(event)
	local target = self._control_add_dialog._user_data
	self._control_add_dialog._user_data = nil
	local extends_name = self._control_add_extends_name.text
	if extends_name ~= "" and g_IDEProject.project.control_map[extends_name] == nil then
		g_AUITool:ShowNotice("错误", "继承控件不存在:" .. extends_name)
		return
	end
	self._control_add_dialog.visible = false
	local child_type = self._control_add_type.text
	local class_name = self._control_add_new_type.text
	local tree_object = target:TreeAdd(extends_name, class_name, child_type)
	if tree_object ~= nil then
		tree_object:ShowFocus(false)
	end
end

function IDEControlTree:ShowReplaceDialog(target)
	if target:IsTree() and target.child_count > 0 then
		g_AUITool:ShowNotice("提示", "当前控件有子控件，不能替换")
		return
	end
	local target_parent = target.logic_parent
	if target_parent == nil then
		return
	end
	local child_type = target.user_info.child_type
	if self._control_replace_dialog == nil then
		self._control_replace_dialog = g_Control:CreateControl("ide_replace_control_dialog", self)
		self._control_replace_new_type.data_list = g_IDEEnum.child_type_list
		A_LayerManager:AddToModal(self._control_replace_dialog)
		self._control_replace_dialog.visible = false
	end
	local data_list = target_parent:GetDataListForAdd()
	local child_type_exist = false
	for k, v in ___ipairs(data_list) do
		if v == child_type then
			child_type_exist = true
			break
		end
	end
	if child_type_exist == false then
		ALittle.List_Push(data_list, child_type)
	end
	self._control_replace_dialog._user_data = target
	self._control_replace_type.data_list = data_list
	self._control_replace_dialog.visible = true
	self._control_replace_extends_name.text = ""
end

function IDEControlTree:HandleReplaceControlCancel(event)
	self._control_replace_dialog.visible = false
	self._control_replace_dialog._user_data = nil
end

function IDEControlTree:HandleReplaceControlConfirm(event)
	local target = self._control_replace_dialog._user_data
	self._control_replace_dialog._user_data = nil
	local extends_name = self._control_replace_extends_name.text
	if extends_name ~= "" and g_IDEProject.project.control_map[extends_name] == nil then
		g_AUITool:ShowNotice("错误", "继承控件不存在:" .. extends_name)
		return
	end
	self._control_replace_dialog.visible = false
	local child_type = self._control_replace_type.text
	local class_name = self._control_replace_new_type.text
	target:TreeReplace(extends_name, class_name, child_type)
end

function IDEControlTree:HandleRightControlTreeCopy(event)
	A_LayerManager:HideFromRight(self._control_tree_menu)
	local target = self._control_tree_menu._user_data
	self._control_tree_menu._user_data = nil
	local info = {}
	info.index = 1
	info.info = target:CalcInfo()
	local copy_list = {}
	copy_list[1] = info
	ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list))
end

function IDEControlTree:ShowPasteDialog(target, info, child_index, revoke_bind, callback)
	local data_list = target:GetDataListForAdd()
	if ALittle.List_MaxN(data_list) == 0 then
		g_AUITool:ShowNotice("提示", "当前控件不能添加子控件")
		if callback ~= nil then
			callback(false, nil)
		end
		return
	end
	if self._paste_control_dialog == nil then
		self._paste_control_dialog = g_Control:CreateControl("ide_paste_control_dialog", self)
		A_LayerManager:AddToModal(self._paste_control_dialog)
	end
	self._paste_control_dialog.visible = true
	self._control_paste_type.data_list = data_list
	local user_data = {}
	self._paste_control_dialog._user_data = user_data
	user_data.target = target
	user_data.info = info
	user_data.child_index = child_index
	user_data.revoke_bind = revoke_bind
	user_data.callback = callback
end

function IDEControlTree:HandlePasteControlCancel(event)
	self._paste_control_dialog.visible = false
	local user_data = self._paste_control_dialog._user_data
	local callback = user_data.callback
	if callback ~= nil then
		callback(false, nil)
	end
	self._paste_control_dialog._user_data = nil
end

function IDEControlTree:HandlePasteControlConfirm(event)
	self._paste_control_dialog.visible = false
	local user_data = self._paste_control_dialog._user_data
	self._paste_control_dialog._user_data = nil
	local add_list = {}
	local tree_object = user_data.target:TreePaste(user_data.info, self._control_paste_type.text, user_data.child_index, false, user_data.revoke_bind)
	add_list[1] = tree_object
	if user_data.callback ~= nil then
		user_data.callback(true, add_list)
	end
end

function IDEControlTree:HandleRightControlTreePaste(event)
	A_LayerManager:HideFromRight(self._control_tree_menu)
	local target = self._control_tree_menu._user_data
	self._control_tree_menu._user_data = nil
	if target:IsTree() then
		target.tab_child:RightControlTreePasteImpl(target, nil, nil)
	else
		local common_parent = target.logic_parent
		local child_index = 1
		if common_parent == nil then
			common_parent = target
		else
			child_index = common_parent:GetChildIndex(target) + 1
		end
		target.tab_child:RightControlTreePasteImpl(common_parent, nil, child_index)
	end
end

function IDEControlTree:HandleRightControlTreeDelete(event)
	A_LayerManager:HideFromRight(self._control_tree_menu)
	local target = self._control_tree_menu._user_data
	self._control_tree_menu._user_data = nil
	target.tab_child:HideHandleQuad(target, true)
	target:TreeDelete()
end

function IDEControlTree:HandleRightControlTreeCut(event)
	A_LayerManager:HideFromRight(self._control_tree_menu)
	local target = self._control_tree_menu._user_data
	self._control_tree_menu._user_data = nil
	local info = {}
	info.index = 1
	info.info = target:CalcInfo()
	local copy_list = {}
	copy_list[1] = info
	ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list))
	target:TreeCut()
end

function IDEControlTree:HandleRightControlTreeJump(event)
	A_LayerManager:HideFromRight(self._control_tree_menu)
	local target = self._control_tree_menu._user_data
	self._control_tree_menu._user_data = nil
	local extends_name = target.user_info.base.__extends
	local control_info = g_IDEProject.project.control_map[extends_name]
	if control_info == nil then
		g_AUITool:ShowNotice("错误", "控件不存在:" .. extends_name)
		return
	end
	g_IDETabManager:StartEditControlBySelect(control_info.name, control_info.info)
end

function IDEControlTree:HandleRightControlTreeDesc(event)
	A_LayerManager:HideFromRight(self._control_tree_menu)
	local target = self._control_tree_menu._user_data
	self._control_tree_menu._user_data = nil
	local x, y = target:LocalToGlobal()
	local desc = target:GetDesc()
	local name = g_AUITool:ShowRename(desc, x, y, target.width)
	if name == nil then
		return
	end
	target:SetDesc(name)
end
IDEControlTree.HandleRightControlTreeDesc = Lua.CoWrap(IDEControlTree.HandleRightControlTreeDesc)

function IDEControlTree:HandleTreeSearchClick(event)
	local tab = g_IDETabManager.cur_tab
	if tab == nil then
		return
	end
	local tab_child = tab._user_data
	local search_key = self._tree_search_key.text
	local search_type = self._tree_search_type.text
	if search_type == "描述" then
		tab_child:SearchDescription(search_key)
	elseif search_type == "绑定设置" then
		tab_child:SearchLink(search_key)
	elseif search_type == "事件设置" then
		tab_child:SearchEvent(search_key)
	elseif search_type == "插件名" then
		tab_child:SearchTargetClass(search_key)
	elseif search_type == "图片路径" then
		tab_child:SearchTextureName(search_key)
	end
end

g_IDEControlTree = IDEControlTree()
