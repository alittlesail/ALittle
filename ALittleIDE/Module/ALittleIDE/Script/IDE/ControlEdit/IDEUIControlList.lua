-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
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
ALittle.RegStruct(-1807692147, "ALittleIDE.IDEControlFileSearchInfo", {
name = "ALittleIDE.IDEControlFileSearchInfo", ns_name = "ALittleIDE", rl_name = "IDEControlFileSearchInfo", hash_code = -1807692147,
name_list = {"list","count","index","name"},
type_list = {"List<ALittleIDE.IDEControlTreeLogic>","int","int","string"},
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
ALittle.RegStruct(-925381158, "ALittle.LoopChildInfo", {
name = "ALittle.LoopChildInfo", ns_name = "ALittle", rl_name = "LoopChildInfo", hash_code = -925381158,
name_list = {"clazz","target","total_time","delay_time"},
type_list = {"string","any","int","int"},
option_map = {}
})
ALittle.RegStruct(-427855371, "ALittleIDE.IDEControlModuleInfo", {
name = "ALittleIDE.IDEControlModuleInfo", ns_name = "ALittleIDE", rl_name = "IDEControlModuleInfo", hash_code = -427855371,
name_list = {"module_name","root_path"},
type_list = {"string","string"},
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
name_list = {"__target_class","__class_func","__base_attr","__show_attr","loop_map","__module","__class","__include","__extends","__childs","__event","__link","__shows_included","__childs_included","__extends_included","description","text","font_path","font_size","red","green","blue","alpha","bold","italic","underline","deleteline","x","y","x_type","x_value","y_type","y_value","width","height","width_type","width_value","height_type","height_value","scale_x","scale_y","center_x","center_y","angle","flip","hand_cursor","visible","disabled","left_size","right_size","top_size","bottom_size","texture_name","interval","play_loop_count","var_play","base_y","head_size","gap","up_size","down_size","cursor_red","cursor_green","cursor_blue","default_text_alpha","ims_padding","margin_left","margin_right","margin_top","margin_bottom","show_count","body_margin","screen_margin_left","screen_margin_right","screen_margin_top","screen_margin_bottom","start_degree","end_degree","line_spacing","max_line_count","font_red","font_green","font_blue","margin_halign","margin_valign","cursor_margin_up","cursor_margin_down","total_size","show_size","offset_rate","offset_step","grade","row_count","col_count","row_index","col_index","u1","v1","u2","v2","u3","v3","x1","y1","x2","y2","x3","y3","x_gap","y_gap","x_start_gap","y_start_gap","button_gap","button_start","button_margin","tab_index","view_margin","child_width_margin"},
type_list = {"List<string>","any","Map<string,any>","Map<string,ALittle.DisplayInfo>","Map<string,ALittle.LoopGroupInfo>","string","string","string","string","List<ALittle.DisplayInfo>","List<ALittle.EventInfo>","string","bool","bool","bool","string","string","string","int","double","double","double","double","bool","bool","bool","bool","double","double","int","double","int","double","double","double","int","double","int","double","double","double","double","double","double","int","bool","bool","bool","double","double","double","double","string","int","int","bool","double","double","double","double","double","double","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","double","double","double","int","int","int","int","int","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEUIControlList = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEUIControlList")

function ALittleIDE.IDEUIControlList:Ctor(ctrl_sys)
	___rawset(self, "_group", {})
end

function ALittleIDE.IDEUIControlList:TCtor()
	ALittleIDE.g_IDEProject:AddEventListener(___all_struct[-975432877], self, self.HandleProjectOpen)
	ALittleIDE.g_IDEProject:AddEventListener(___all_struct[-332308624], self, self.HandleProjectClose)
end

function ALittleIDE.IDEUIControlList:HandleProjectClose(event)
	self._control_scroll_screen:RemoveAllChild()
end

function ALittleIDE.IDEUIControlList:HandleProjectOpen(event)
	local module_map = ALittleIDE.g_IDEProject.project.config:GetConfig("control_module", {})
	module_map[event.name] = nil
	local ui = ALittleIDE.IDEUIManager(event.name)
	ALittleIDE.g_IDEProject.project.ui[event.name] = ui
	local info = {}
	info.ui = ui
	info.module_name = event.name
	info.name = "ui"
	info.path = ALittle.File_BaseFilePath() .. "Module/" .. event.name .. "/UI"
	info.module_path = ALittle.File_BaseFilePath() .. "Module/" .. event.name .. "/"
	info.group = self._group
	info.root = true
	self._control_scroll_screen:AddChild(ALittleIDE.IDEControlTree(ALittleIDE.g_Control, info))
	for index, module in ___pairs(module_map) do
		info = {}
		info.ui = ALittleIDE.IDEUIManager(module.module_name)
		info.module_name = module.module_name
		info.name = ALittle.File_GetFileNameByPath(module.root_path)
		info.path = module.root_path
		info.module_path = ALittle.File_GetFilePathByPath(module.root_path) .. "/"
		info.group = self._group
		info.root = true
		ALittleIDE.g_IDEProject.project.ui[module.module_name] = info.ui
		ui.control:RegisterPlugin(module.module_name, info.ui.control)
		local tree = ALittleIDE.IDEControlTree(ALittleIDE.g_Control, info)
		self._control_scroll_screen:AddChild(tree)
	end
end

function ALittleIDE.IDEUIControlList:GetControlTree(module)
	for index, child in ___ipairs(self._control_scroll_screen.childs) do
		if child.user_info.module_name == module then
			return child
		end
	end
	return nil
end

function ALittleIDE.IDEUIControlList:AddModule(name)
	local ui_manager = ALittleIDE.g_IDEProject:GetUIManager(nil)
	if ui_manager == nil then
		return
	end
	for index, tree in ___ipairs(self._control_scroll_screen.childs) do
		if tree.user_info.module_name == name then
			return
		end
	end
	local module_map = ALittleIDE.g_IDEProject.project.config:GetConfig("control_module", {})
	local module_info = {}
	module_info.module_name = name
	module_info.root_path = ALittle.File_BaseFilePath() .. "Module/" .. name .. "/UI"
	module_map[name] = module_info
	ALittleIDE.g_IDEProject.project.config:SetConfig("control_module", module_map)
	local info = {}
	info.module_name = name
	info.name = "ui"
	info.path = module_info.root_path
	info.module_path = ALittle.File_BaseFilePath() .. "Module/" .. name .. "/"
	info.group = self._group
	info.root = true
	info.ui = ALittleIDE.IDEUIManager(name)
	ALittleIDE.g_IDEProject.project.ui[name] = info.ui
	ui_manager.control:RegisterPlugin(name, info.ui.control)
	local tree = ALittleIDE.IDEControlTree(ALittleIDE.g_Control, info)
	self._control_scroll_screen:AddChild(tree)
end

function ALittleIDE.IDEUIControlList:ShowTreeItemFocus(target)
	target:ShowSelect()
	if target ~= self._control_scroll_screen then
		local parent = target.logic_parent
		while parent ~= nil and parent ~= self._control_scroll_screen do
			parent.fold = true
			parent = parent.logic_parent
		end
	end
	self._control_scroll_screen:RejustScrollBar()
	local x, y = target:LocalToGlobal(self._control_scroll_screen.container)
	local target_x = (self._control_scroll_screen.view_width - target.width / 2) / 2 - x
	local target_y = (self._control_scroll_screen.view_height - target.height) / 2 - y
	if self._tree_loop_x ~= nil then
		self._tree_loop_x:Stop()
		self._tree_loop_x = nil
	end
	if self._tree_loop_y ~= nil then
		self._tree_loop_y:Stop()
		self._tree_loop_y = nil
	end
	self._tree_loop_x = ALittle.LoopLinear(self._control_scroll_screen, "container_x", target_x, 300, 0)
	self._tree_loop_x:Start()
	self._tree_loop_y = ALittle.LoopLinear(self._control_scroll_screen, "container_y", target_y, 300, 0)
	self._tree_loop_y:Start()
end

function ALittleIDE.IDEUIControlList:HandleControlSearchClick(event)
	if self._search_info == nil or self._search_info.name ~= self._control_search_key.text then
		self._search_info = {}
		self._search_info.name = self._control_search_key.text
		self._search_info.index = 0
		self._search_info.list = {}
		for index, child in ___ipairs(self._control_scroll_screen.childs) do
			child:SearchFile(self._search_info.name, self._search_info.list)
		end
		self._search_info.count = ALittle.List_MaxN(self._search_info.list)
	end
	if self._search_info.count <= 0 then
		return
	end
	self._search_info.index = self._search_info.index + (1)
	if self._search_info.index > self._search_info.count then
		self._search_info.index = 1
	end
	local item = self._search_info.list[self._search_info.index]
	self:ShowTreeItemFocus(item)
end

function ALittleIDE.IDEUIControlList:ShowNewControl()
	if ALittleIDE.g_IDEProject.project == nil then
		g_AUITool:ShowNotice("提示", "当前没有打开的项目")
		return
	end
	if self._control_new_dialog == nil then
		self._control_new_dialog = ALittleIDE.g_Control:CreateControl("ide_new_control_dialog", self)
		A_LayerManager:AddToModal(self._control_new_dialog)
		self._control_new_type.data_list = ALittleIDE.g_IDEEnum.child_type_list
	end
	local data_list = {}
	for name, ui in ___pairs(ALittleIDE.g_IDEProject.project.ui) do
		ALittle.List_Push(data_list, name)
	end
	self._control_new_module.data_list = data_list
	self._control_new_name.text = ""
	self._control_new_dialog.visible = true
	A_UISystem.focus = self._control_new_name.show_input
end

function ALittleIDE.IDEUIControlList:HandleNewControlCancel(event)
	self._control_new_dialog.visible = false
end

function ALittleIDE.IDEUIControlList:HandleNewControlConfirm(event)
	local project = ALittleIDE.g_IDEProject.project
	if project == nil then
		g_AUITool:ShowNotice("错误", "当前没有打开的项目")
		return
	end
	local name = self._control_new_name.text
	if name == "" then
		g_AUITool:ShowNotice("错误", "请输入控件名")
		return
	end
	if ALittleIDE.IDEUtility_CheckName(name) ~= nil then
		g_AUITool:ShowNotice("错误", "控件名不合法:" .. name)
		return
	end
	local ui_manager = project.ui[self._control_new_module.text]
	if ui_manager == nil then
		g_AUITool:ShowNotice("错误", "模块不存在")
		return
	end
	if ui_manager.control_map[name] ~= nil then
		g_AUITool:ShowNotice("错误", "控件已存在:" .. name)
		return
	end
	if ALittleIDE.g_IDECenter.center.content_edit:GetTabById(ALittleIDE.IDEUITabChild, name) ~= nil then
		g_AUITool:ShowNotice("错误", "控件名已存在:" .. name)
		return
	end
	local control_type = self._control_new_type.text
	if control_type == "" then
		g_AUITool:ShowNotice("错误", "请选择控件类型")
		return
	end
	ALittleIDE.g_IDECenter.center.content_edit:StartEditControlByNew(self._control_new_module.text, name, control_type)
	self._control_new_dialog.visible = false
end

function ALittleIDE.IDEUIControlList:HandleControlDragBegin(event)
	self._drag_shift = (A_UISystem.sym_map[1073742049] ~= nil or A_UISystem.sym_map[1073742053] ~= nil)
	if self._drag_shift == false then
		event.target = self._control_scroll_screen
		self._control_scroll_screen:DispatchEvent(___all_struct[1301789264], event)
		return
	end
	local x, y = event.target:LocalToGlobal()
	self._drag_effect = ALittle.EffectImage(ALittleIDE.g_Control)
	self._drag_effect:Action(event.target)
	A_LayerManager:AddToTip(self._drag_effect)
	self._drag_effect.x = x
	self._drag_effect.y = y
	self._drag_effect.alpha = 0.6
	local info = event.target._user_data
	if info.presee ~= true then
		return
	end
	local child = ALittleIDE.g_IDECenter.center.content_edit:GetTabById(ALittleIDE.IDEUITabChild, info.control_info.name)
	if child == nil then
		return
	end
	ALittleIDE.g_IDECenter.center.content_edit:CloseTab(child)
	if info.pre_index ~= nil then
		ALittleIDE.g_IDECenter.center.content_edit:SetCurTabIndex(info.pre_index)
	end
end

function ALittleIDE.IDEUIControlList:HandleControlDrag(event)
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

function ALittleIDE.IDEUIControlList:HandleControlDragEnd(event)
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
	local tab_child = ALittle.Cast(ALittleIDE.IDEUITabChild, ALittleIDE.IDETabChild, ALittleIDE.g_IDECenter.center.content_edit.cur_tab_child)
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

end