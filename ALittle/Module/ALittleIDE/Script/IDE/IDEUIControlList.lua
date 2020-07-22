-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

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
ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(1653869333, "ALittle.LoopGroupInfo", {
name = "ALittle.LoopGroupInfo", ns_name = "ALittle", rl_name = "LoopGroupInfo", hash_code = 1653869333,
name_list = {"childs"},
type_list = {"List<ALittle.LoopListInfo>"},
option_map = {}
})
ALittle.RegStruct(-1604617962, "ALittle.UIKeyDownEvent", {
name = "ALittle.UIKeyDownEvent", ns_name = "ALittle", rl_name = "UIKeyDownEvent", hash_code = -1604617962,
name_list = {"target","mod","sym","scancode","custom","handled"},
type_list = {"ALittle.DisplayObject","int","int","int","bool","bool"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name = "ALittle.UIButtonEvent", ns_name = "ALittle", rl_name = "UIButtonEvent", hash_code = -1347278145,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
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
ALittle.RegStruct(-925381158, "ALittle.LoopChildInfo", {
name = "ALittle.LoopChildInfo", ns_name = "ALittle", rl_name = "LoopChildInfo", hash_code = -925381158,
name_list = {"clazz","target","total_time","delay_time"},
type_list = {"string","any","int","int"},
option_map = {}
})
ALittle.RegStruct(882286932, "ALittle.UIKeyEvent", {
name = "ALittle.UIKeyEvent", ns_name = "ALittle", rl_name = "UIKeyEvent", hash_code = 882286932,
name_list = {"target","mod","sym","scancode","custom","handled"},
type_list = {"ALittle.DisplayObject","int","int","int","bool","bool"},
option_map = {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name = "ALittle.UIRButtonDownEvent", ns_name = "ALittle", rl_name = "UIRButtonDownEvent", hash_code = -641444818,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name = "ALittle.UIClickEvent", ns_name = "ALittle", rl_name = "UIClickEvent", hash_code = -449066808,
name_list = {"target","is_drag"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})
ALittle.RegStruct(150587926, "ALittle.UIButtonDragEndEvent", {
name = "ALittle.UIButtonDragEndEvent", ns_name = "ALittle", rl_name = "UIButtonDragEndEvent", hash_code = 150587926,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(-11865120, "ALittleIDE.IDEControlItemUserData", {
name = "ALittleIDE.IDEControlItemUserData", ns_name = "ALittleIDE", rl_name = "IDEControlItemUserData", hash_code = -11865120,
name_list = {"pre_index","presee","control_info"},
type_list = {"int","bool","ALittleIDE.IDEControlInfo"},
option_map = {}
})
ALittle.RegStruct(-4982446, "ALittle.DisplayInfo", {
name = "ALittle.DisplayInfo", ns_name = "ALittle", rl_name = "DisplayInfo", hash_code = -4982446,
name_list = {"__target_class","__class_func","__base_attr","__show_attr","loop_map","__class","__include","__extends","__childs","__event","__link","__shows_included","__childs_included","__extends_included","description","text","font_path","font_size","red","green","blue","alpha","bold","italic","underline","deleteline","x","y","x_type","x_value","y_type","y_value","width","height","width_type","width_value","height_type","height_value","scale_x","scale_y","center_x","center_y","angle","flip","hand_cursor","visible","disabled","left_size","right_size","top_size","bottom_size","texture_name","interval","play_loop_count","var_play","base_y","head_size","gap","up_size","down_size","cursor_red","cursor_green","cursor_blue","default_text_alpha","ims_padding","margin_left","margin_right","margin_top","margin_bottom","show_count","body_margin","screen_margin_left","screen_margin_right","screen_margin_top","screen_margin_bottom","start_degree","end_degree","line_spacing","max_line_count","font_red","font_green","font_blue","margin_halign","margin_valign","cursor_margin_up","cursor_margin_down","total_size","show_size","offset_rate","offset_step","grade","row_count","col_count","row_index","col_index","u1","v1","u2","v2","u3","v3","x1","y1","x2","y2","x3","y3","x_gap","y_gap","x_start_gap","y_start_gap","button_gap","button_start","button_margin","tab_index","view_margin","child_width_margin"},
type_list = {"List<string>","any","Map<string,any>","Map<string,ALittle.DisplayInfo>","Map<string,ALittle.LoopGroupInfo>","string","string","string","List<ALittle.DisplayInfo>","List<ALittle.EventInfo>","string","bool","bool","bool","string","string","string","int","double","double","double","double","bool","bool","bool","bool","double","double","int","double","int","double","double","double","int","double","int","double","double","double","double","double","double","int","bool","bool","bool","double","double","double","double","string","int","int","bool","double","double","double","double","double","double","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","double","double","double","int","int","int","int","int","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
IDEUIControlList = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEUIControlList")

function IDEUIControlList:Ctor(ctrl_sys)
	___rawset(self, "_drag_effect", nil)
	___rawset(self, "_drag_shift", false)
	___rawset(self, "_item_pool", {})
	___rawset(self, "_item_pool_count", 0)
	___rawset(self, "_item_used", {})
end

function IDEUIControlList:TCtor()
	g_IDEProject:AddEventListener(___all_struct[-332308624], self, self.HandleProjectClose)
end

function IDEUIControlList:HandleProjectClose(event)
	self:ClearControlItem()
end

function IDEUIControlList.ControlInfoCmp(a, b)
	return a.name < b.name
end

function IDEUIControlList:HandleControlSearchClick(event)
	self._control_scroll_screen:RemoveAllChild()
	for k, item in ___ipairs(self._item_used) do
		self._item_pool_count = self._item_pool_count + 1
		self._item_pool[self._item_pool_count] = item
	end
	self._item_used = {}
	local item_used_count = 0
	local project = g_IDEProject.project
	if project == nil then
		g_AUITool:ShowNotice("提示", "当前没有打开的项目")
		return
	end
	local key = self._control_search_key.text
	local search_type = self._control_search_type.text
	local control_info_list = {}
	local control_info_count = 0
	local control_map = project.ui.control_map
	for control_name, control_info in ___pairs(control_map) do
		if search_type == "控件名|描述" then
			if key == "" or ALittle.String_Find(control_name, key) ~= nil or (control_info.info.description ~= nil and ALittle.String_Find(control_info.info.description, key) ~= nil) then
				control_info_count = control_info_count + 1
				control_info_list[control_info_count] = control_info
			end
		elseif search_type == "插件名" then
			if IDEUIUtility_HasTargetClass(control_info.info, key) then
				control_info_count = control_info_count + 1
				control_info_list[control_info_count] = control_info
			end
		elseif search_type == "事件设置" then
			if IDEUIUtility_HasEventCallback(control_info.info, key) then
				control_info_count = control_info_count + 1
				control_info_list[control_info_count] = control_info
			end
		end
	end
	local tabname_map = g_IDECenter.center.content_edit:GetTabIdMap(IDEUITabChild)
	local search_count = 0
	local last_control_info = nil
	ALittle.List_Sort(control_info_list, IDEUIControlList.ControlInfoCmp)
	for index, control_info in ___ipairs(control_info_list) do
		local item = nil
		if self._item_pool_count > 0 then
			item = self._item_pool[self._item_pool_count]
			self._item_pool_count = self._item_pool_count - 1
		end
		if item == nil then
			item = g_Control:CreateControl("ide_common_item_checkbutton")
			item:AddEventListener(___all_struct[-449066808], self, self.HandleControlItemClick)
			item:AddEventListener(___all_struct[-641444818], self, self.HandleControlItemRightClick)
			item:AddEventListener(___all_struct[-1604617962], self, self.HandleControlKeyDown)
			item:AddEventListener(___all_struct[1301789264], self, self.HandleControlDragBegin)
			item:AddEventListener(___all_struct[1337289812], self, self.HandleControlDrag)
			item:AddEventListener(___all_struct[150587926], self, self.HandleControlDragEnd)
		end
		item_used_count = item_used_count + 1
		self._item_used[item_used_count] = item
		if control_info.info.description ~= nil and control_info.info.description ~= "" then
			item.text = control_info.name .. "(" .. control_info.info.description .. ")"
		else
			item.text = control_info.name
		end
		item.selected = tabname_map[control_info.name] ~= nil
		local user_data = {}
		item._user_data = user_data
		user_data.presee = false
		user_data.control_info = control_info
		self._control_scroll_screen:AddChild(item)
		search_count = search_count + 1
		last_control_info = control_info
	end
	if search_count == 1 then
		g_IDECenter.center.content_edit:StartEditControlBySelect(last_control_info.name, last_control_info.info)
	end
end

function IDEUIControlList:HandleControlItemClick(event)
	local info = event.target._user_data
	info.presee = false
	event.target.selected = true
	g_IDECenter.center.content_edit:StartEditControlBySelect(info.control_info.name, info.control_info.info)
end

function IDEUIControlList:HandleControlPreseeMoveIn(event)
	local info = event.target._user_data
	info.presee = true
	if g_IDECenter.center.content_edit:GetTabById(IDEUITabChild, info.control_info.name) ~= nil then
		info.presee = false
		return
	end
	info.pre_index = g_IDECenter.center.content_edit:GetCurTabIndex()
	g_IDECenter.center.content_edit:StartEditControlBySelect(info.control_info.name, info.control_info.info)
end

function IDEUIControlList:HandleControlPreseeMoveOut(event)
	local info = event.target._user_data
	if info.presee ~= true then
		return
	end
	local child = g_IDECenter.center.content_edit:GetTabById(IDEUITabChild, info.control_info.name)
	if child == nil then
		return
	end
	g_IDECenter.center.content_edit:CloseTab(child)
	if info.pre_index ~= nil then
		g_IDECenter.center.content_edit:SetCurTabIndex(info.pre_index)
	end
end

function IDEUIControlList:HandleControlKeyDown(event)
	if event.sym == 1073741883 then
		self:ControlRename(event.target)
	end
end
IDEUIControlList.HandleControlKeyDown = Lua.CoWrap(IDEUIControlList.HandleControlKeyDown)

function IDEUIControlList:HandleControlDragBegin(event)
	self._drag_shift = (A_UISystem.sym_map[1073742049] ~= nil or A_UISystem.sym_map[1073742053] ~= nil)
	if self._drag_shift == false then
		event.target = self._control_scroll_screen
		self._control_scroll_screen:DispatchEvent(___all_struct[1301789264], event)
		return
	end
	local x, y = event.target:LocalToGlobal()
	self._drag_effect = ALittle.EffectImage(g_Control)
	self._drag_effect:Action(event.target)
	A_LayerManager:AddToTip(self._drag_effect)
	self._drag_effect.x = x
	self._drag_effect.y = y
	self._drag_effect.alpha = 0.6
	local info = event.target._user_data
	if info.presee ~= true then
		return
	end
	local child = g_IDECenter.center.content_edit:GetTabById(IDEUITabChild, info.control_info.name)
	if child == nil then
		return
	end
	g_IDECenter.center.content_edit:CloseTab(child)
	if info.pre_index ~= nil then
		g_IDECenter.center.content_edit:SetCurTabIndex(info.pre_index)
	end
end

function IDEUIControlList:HandleControlDrag(event)
	if self._drag_shift == false then
		event.target = self._control_scroll_screen
		self._control_scroll_screen:DispatchEvent(___all_struct[1337289812], event)
		return
	end
	if self._drag_effect == nil then
		return
	end
	self._drag_effect.x = self._drag_effect.x + event.delta_x
	self._drag_effect.y = self._drag_effect.y + event.delta_y
end

function IDEUIControlList:HandleControlDragEnd(event)
	if self._drag_shift == false then
		event.target = self._control_scroll_screen
		self._control_scroll_screen:DispatchEvent(___all_struct[150587926], event)
		return
	end
	if self._drag_effect ~= nil then
		A_LayerManager:RemoveFromTip(self._drag_effect)
		self._drag_effect:Clear()
		self._drag_effect = nil
	end
	local tab_child = ALittle.Cast(IDEUITabChild, IDETabChild, g_IDECenter.center.content_edit.cur_tab_child)
	if tab_child == nil then
		return
	end
	local x, y = tab_child.tree_object:LocalToGlobal()
	local delta_x = event.abs_x - x
	local delta_y = event.abs_y - y
	local target = tab_child.tree_object:PickUp(delta_x, delta_y)
	if target == nil then
		ALittle.Log("IDEUITreeLogic:HandleDrag} target null")
		return
	end
	local tree = target._user_data
	local user_data = event.target._user_data
	local save_info = {}
	save_info["__extends"] = user_data.control_info.name
	local copy_list = {}
	local info = {}
	info["index"] = 1
	info["info"] = save_info
	copy_list[1] = info
	ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list))
	if tree.is_tree then
		tab_child:RightControlTreePasteImpl(tree, nil, 1)
	else
		local common_parent = tree.logic_parent
		if common_parent == nil then
			g_AUITool:ShowNotice("提示", "当前是根节点，并且不是容器，粘帖失败")
			return
		end
		local child_index = common_parent:GetChildIndex(tree)
		x, y = target:LocalToGlobal()
		y = y + target.height / 2
		if event.abs_y > y then
			child_index = child_index + 1
		end
		tab_child:RightControlTreePasteImpl(common_parent, nil, child_index)
	end
end

function IDEUIControlList:ClearControlItem()
	self._control_scroll_screen:RemoveAllChild()
end

function IDEUIControlList:ShowNewControl()
	if g_IDEProject.project == nil then
		g_AUITool:ShowNotice("提示", "当前没有打开的项目")
		return
	end
	if self._control_new_dialog == nil then
		self._control_new_dialog = g_Control:CreateControl("ide_new_control_dialog", self)
		A_LayerManager:AddToModal(self._control_new_dialog)
		self._control_new_type.data_list = g_IDEEnum.child_type_list
	end
	self._control_new_name.text = ""
	self._control_new_extends_name.text = ""
	self._control_new_dialog.visible = true
	A_UISystem.focus = self._control_new_name.show_input
end

function IDEUIControlList:HandleNewControlCancel(event)
	self._control_new_dialog.visible = false
end

function IDEUIControlList:HandleNewControlConfirm(event)
	local project = g_IDEProject.project
	if project == nil then
		g_AUITool:ShowNotice("错误", "当前没有打开的项目")
		return
	end
	local name = self._control_new_name.text
	if name == "" then
		g_AUITool:ShowNotice("错误", "请输入控件名")
		return
	end
	if IDEUtility_CheckName(name) ~= nil then
		g_AUITool:ShowNotice("错误", "控件名不合法:" .. name)
		return
	end
	if project.ui.control_map[name] ~= nil then
		g_AUITool:ShowNotice("错误", "控件已存在:" .. name)
		return
	end
	if g_IDECenter.center.content_edit:GetTabById(IDEUITabChild, name) ~= nil then
		g_AUITool:ShowNotice("错误", "控件名已存在:" .. name)
		return
	end
	local control_type = self._control_new_type.text
	if control_type == "" then
		g_AUITool:ShowNotice("错误", "请选择控件类型")
		return
	end
	local extends_name = self._control_new_extends_name.text
	if extends_name ~= "" then
		g_IDECenter.center.content_edit:StartEditControlByExtends(name, extends_name)
	else
		g_IDECenter.center.content_edit:StartEditControlByNew(name, control_type)
	end
	self._control_new_dialog.visible = false
end

function IDEUIControlList:HandleControlItemRightClick(event)
	local user_data = event.target._user_data
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("复制控件名", Lua.Bind(self.CopyName, self, event.target))
	menu:AddItem("复制并新建控件", Lua.Bind(self.CopyInfo, self, event.target))
	menu:AddItem("复制继承代码", Lua.Bind(self.CopyExtends, self, event.target))
	menu:AddItem("修改控件名", Lua.Bind(self.ControlRename, self, event.target))
	menu:AddItem("删除", Lua.Bind(self.Delete, self, event.target))
	menu:Show()
end

function IDEUIControlList:Delete(target)
	local user_data = target._user_data
	local name = user_data.control_info.name
	local error = g_IDEProject.project.ui:CanDelete(name)
	if error ~= nil then
		g_AUITool:ShowNotice("错误", error)
		return
	end
	error = g_IDECenter.center.content_edit:CanDelete(name)
	if error ~= nil then
		g_AUITool:ShowNotice("错误", error)
		return
	end
	local del_result = g_AUITool:DeleteNotice("提示", "确定要删除" .. target.text .. "吗?")
	if del_result == "YES" then
		self._control_scroll_screen:RemoveChild(target)
		error = g_IDEProject.project.ui:DeleteControl(user_data.control_info.name)
		if error ~= nil then
			g_AUITool:ShowNotice("提示", error)
			return
		end
		local tab = g_IDECenter.center.content_edit:GetTabById(IDEUITabChild, user_data.control_info.name)
		if tab == nil then
			return
		end
		g_IDECenter.center.content_edit:CloseTab(tab)
	end
end
IDEUIControlList.Delete = Lua.CoWrap(IDEUIControlList.Delete)

function IDEUIControlList:CopyName(target)
	local user_data = target._user_data
	local name = user_data.control_info.name
	ALittle.System_SetClipboardText(name)
end

function IDEUIControlList:CopyInfo(target)
	local user_data = target._user_data
	local old_name = user_data.control_info.name
	local x, y = target:LocalToGlobal()
	local new_name = g_AUITool:ShowRename(old_name, x, y, target.width)
	if new_name == nil or old_name == new_name then
		return
	end
	self:ControlCopyInfo(old_name, new_name)
end
IDEUIControlList.CopyInfo = Lua.CoWrap(IDEUIControlList.CopyInfo)

function IDEUIControlList:ControlCopyInfo(target_name, new_name)
	local error = IDEUtility_CheckName(new_name)
	if error ~= nil then
		g_AUITool:ShowNotice("错误", error)
		return
	end
	local info = g_IDEProject.project.ui.control_map[new_name]
	if info ~= nil then
		g_AUITool:ShowNotice("错误", "控件名已存在:" .. new_name)
		return
	end
	info = g_IDEProject.project.ui.control_map[target_name]
	if info == nil then
		g_AUITool:ShowNotice("错误", "控件不存在:" .. target_name)
		return
	end
	g_IDEProject.project.ui:SaveControl(new_name, ALittle.String_CopyTable(info.info))
	info = g_IDEProject.project.ui.control_map[new_name]
	if info == nil then
		g_AUITool:ShowNotice("错误", "控件新建失败:" .. new_name)
		return
	end
	g_IDECenter.center.content_edit:StartEditControlBySelect(new_name, info.info)
end

function IDEUIControlList:ControlRename(target)
	local user_data = target._user_data
	local old_name = user_data.control_info.name
	local error = g_IDEProject.project.ui:CanDelete(old_name)
	if error ~= nil then
		g_AUITool:ShowNotice("错误", error)
		return
	end
	error = g_IDECenter.center.content_edit:CanDelete(old_name)
	if error ~= nil then
		g_AUITool:ShowNotice("错误", error)
		return
	end
	local x, y = target:LocalToGlobal()
	local new_name = g_AUITool:ShowRename(old_name, x, y, target.width)
	if new_name == nil or old_name == new_name then
		return
	end
	error = g_IDEProject.project.ui:RenameControl(old_name, new_name)
	if error ~= nil then
		g_AUITool:ShowNotice("错误", error)
		return
	end
	target.text = new_name
	local tab = g_IDECenter.center.content_edit:GetTabById(IDEUITabChild, old_name)
	if tab == nil then
		return
	end
	local tab_child = tab._user_data
	tab_child:Rename(new_name)
end
IDEUIControlList.ControlRename = Lua.CoWrap(IDEUIControlList.ControlRename)

function IDEUIControlList:CopyExtends(target)
	local user_data = target._user_data
	local name = user_data.control_info.name
	local save_info = {}
	save_info["__extends"] = name
	local copy_list = {}
	local info = {}
	info["index"] = 1
	info["info"] = save_info
	copy_list[1] = info
	ALittle.System_SetClipboardText(ALittle.String_JsonEncode(copy_list))
end

