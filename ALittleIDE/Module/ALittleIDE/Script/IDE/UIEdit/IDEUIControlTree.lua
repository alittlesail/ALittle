-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs

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
ALittle.RegStruct(1653869333, "ALittle.LoopGroupInfo", {
name = "ALittle.LoopGroupInfo", ns_name = "ALittle", rl_name = "LoopGroupInfo", hash_code = 1653869333,
name_list = {"childs"},
type_list = {"List<ALittle.LoopListInfo>"},
option_map = {}
})
ALittle.RegStruct(1025287370, "ALittleIDE.IDEPasteControlUserData", {
name = "ALittleIDE.IDEPasteControlUserData", ns_name = "ALittleIDE", rl_name = "IDEPasteControlUserData", hash_code = 1025287370,
name_list = {"target","info","child_index","revoke_bind","callback"},
type_list = {"ALittleIDE.IDEUITreeLogic","ALittle.DisplayInfo","int","ALittle.RevokeBind","Functor<(bool,List<ALittleIDE.IDEUITreeLogic>)>"},
option_map = {}
})
ALittle.RegStruct(-925381158, "ALittle.LoopChildInfo", {
name = "ALittle.LoopChildInfo", ns_name = "ALittle", rl_name = "LoopChildInfo", hash_code = -925381158,
name_list = {"clazz","target","total_time","delay_time"},
type_list = {"string","any","int","int"},
option_map = {}
})
ALittle.RegStruct(-4982446, "ALittle.DisplayInfo", {
name = "ALittle.DisplayInfo", ns_name = "ALittle", rl_name = "DisplayInfo", hash_code = -4982446,
name_list = {"__target_class","__class_func","__base_attr","__show_attr","loop_map","__module","__class","__include","__extends","__childs","__event","__link","__shows_included","__childs_included","__extends_included","description","text","font_path","font_size","red","green","blue","alpha","bold","italic","underline","deleteline","x","y","x_type","x_value","y_type","y_value","width","height","width_type","width_value","height_type","height_value","scale_x","scale_y","center_x","center_y","angle","flip","hand_cursor","visible","disabled","left_size","right_size","top_size","bottom_size","texture_name","interval","play_loop_count","var_play","base_y","head_size","gap","up_size","down_size","cursor_red","cursor_green","cursor_blue","default_text_alpha","ims_padding","margin_left","margin_right","margin_top","margin_bottom","show_count","body_margin","screen_margin_left","screen_margin_right","screen_margin_top","screen_margin_bottom","start_degree","end_degree","line_spacing","max_line_count","font_red","font_green","font_blue","margin_halign","margin_valign","cursor_margin_up","cursor_margin_down","total_size","show_size","offset_rate","offset_step","grade","row_count","col_count","row_index","col_index","u1","v1","u2","v2","u3","v3","x1","y1","x2","y2","x3","y3","x_gap","y_gap","x_start_gap","y_start_gap","button_gap","button_start","button_margin","tab_index","view_margin","child_width_margin"},
type_list = {"List<string>","any","Map<string,any>","Map<string,ALittle.DisplayInfo>","Map<string,ALittle.LoopGroupInfo>","string","string","string","string","List<ALittle.DisplayInfo>","List<ALittle.EventInfo>","string","bool","bool","bool","string","string","string","int","double","double","double","double","bool","bool","bool","bool","double","double","int","double","int","double","double","double","int","double","int","double","double","double","double","double","double","int","bool","bool","bool","double","double","double","double","string","int","int","bool","double","double","double","double","double","double","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","double","double","double","int","int","int","int","int","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEUIControlTree = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEUIControlTree")

function ALittleIDE.IDEUIControlTree:HandleControlTreeItemRightClick(event)
	local target = event.target._user_data
	if target.user_info.extends then
		return
	end
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("设置", Lua.Bind(self.ShowSettingDialog, self, target))
	menu:AddItem("上移", Lua.Bind(target.TransferUp, target), target.user_info.root or target.user_info.child_type ~= "child", false)
	menu:AddItem("下移", Lua.Bind(target.TransferDown, target), target.user_info.root or target.user_info.child_type ~= "child", false)
	menu:AddItem("添加", Lua.Bind(self.ShowAddDialog, self, target), not target.is_tree)
	menu:AddItem("添加Image", Lua.Bind(self.ShowAddImageDialog, self, target), not target.is_tree)
	menu:AddItem("添加Text", Lua.Bind(self.ShowAddTextDialog, self, target), not target.is_tree)
	menu:AddItem("复制", Lua.Bind(target.CopyToClipboard, target))
	menu:AddItem("粘贴", Lua.Bind(target.PasteFromClipboard, target))
	menu:AddItem("剪切", Lua.Bind(target.CutToClipboard, target), target.user_info.root)
	menu:AddItem("删除", Lua.Bind(target.TreeDelete, target, nil), target.user_info.root)
	menu:AddItem("跳转", Lua.Bind(self.ControlTreeJump, self, target), not target.user_info.extends_root)
	menu:AddItem("描述", Lua.Bind(self.ControlTreeDesc, self, target))
	menu:Show()
end

function ALittleIDE.IDEUIControlTree:ShowSettingDialog(item)
	item:ShowFocus(false)
	ALittleIDE.g_IDEAttrControlDialog:ShowDialog(item.user_info.object)
end

function ALittleIDE.IDEUIControlTree:ShowAddImageDialog(target)
	local ui_manager = ALittleIDE.g_IDEProject:GetUIManager(target.user_info.module)
	if ui_manager == nil then
		g_AUITool:ShowNotice("错误", "模块不存在:" .. target.user_info.module)
		return
	end
	ALittleIDE.g_IDEImageSelectDialog:SetBasePath(ui_manager.texture_path)
	local path = ALittleIDE.g_IDEImageSelectDialog:ShowSelect()
	if path == nil then
		return
	end
	if target:CanAddChild() == false then
		g_AUITool:ShowNotice("提示", "当前控件不能添加子控件")
		return
	end
	local tree_object = target:TreeAdd(nil, "", "Image", "child")
	if tree_object == nil then
		g_AUITool:ShowNotice("提示", "添加失败")
		return
	end
	tree_object.attr_panel:SetTextureName(path, nil)
	tree_object:ShowFocus(false)
end
ALittleIDE.IDEUIControlTree.ShowAddImageDialog = Lua.CoWrap(ALittleIDE.IDEUIControlTree.ShowAddImageDialog)

function ALittleIDE.IDEUIControlTree:ShowAddTextDialog(target)
	if target:CanAddChild() == false then
		g_AUITool:ShowNotice("提示", "当前控件不能添加子控件")
		return
	end
	local tree_object = target:TreeAdd(nil, "", "Text", "child")
	if tree_object == nil then
		g_AUITool:ShowNotice("提示", "添加失败")
		return
	end
	tree_object:ShowFocus(false)
end

function ALittleIDE.IDEUIControlTree:ShowAddDialog(target)
	if self._control_add_dialog == nil then
		self._control_add_dialog = ALittleIDE.g_Control:CreateControl("ide_add_control_dialog", self)
		self._control_add_new_type.data_list = ALittleIDE.g_IDEEnum.child_type_list
		A_LayerManager:AddToModal(self._control_add_dialog)
		self._control_add_dialog.visible = false
	end
	local data_list = target:GetDataListForAdd()
	if ALittle.List_Len(data_list) == 0 then
		g_AUITool:ShowNotice("提示", "当前控件不能添加子控件")
		return
	end
	self._control_add_dialog._user_data = target
	self._control_add_type.data_list = data_list
	self._control_add_dialog.visible = true
end

function ALittleIDE.IDEUIControlTree:HandleAddControlCancel(event)
	self._control_add_dialog.visible = false
	self._control_add_dialog._user_data = nil
end

function ALittleIDE.IDEUIControlTree:HandleAddControlConfirm(event)
	local target = self._control_add_dialog._user_data
	self._control_add_dialog._user_data = nil
	self._control_add_dialog.visible = false
	local child_type = self._control_add_type.text
	local class_name = self._control_add_new_type.text
	local tree_object = target:TreeAdd(nil, "", class_name, child_type)
	if tree_object ~= nil then
		tree_object:ShowFocus(false)
	end
end

function ALittleIDE.IDEUIControlTree:ShowPasteDialog(target, info, child_index, revoke_bind, callback)
	local data_list = target:GetDataListForAdd()
	if ALittle.List_Len(data_list) == 0 then
		g_AUITool:ShowNotice("提示", "当前控件不能添加子控件")
		if callback ~= nil then
			callback(false, nil)
		end
		return
	end
	if self._paste_control_dialog == nil then
		self._paste_control_dialog = ALittleIDE.g_Control:CreateControl("ide_paste_control_dialog", self)
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

function ALittleIDE.IDEUIControlTree:HandlePasteControlCancel(event)
	self._paste_control_dialog.visible = false
	local user_data = self._paste_control_dialog._user_data
	local callback = user_data.callback
	if callback ~= nil then
		callback(false, nil)
	end
	self._paste_control_dialog._user_data = nil
end

function ALittleIDE.IDEUIControlTree:HandlePasteControlConfirm(event)
	self._paste_control_dialog.visible = false
	local user_data = self._paste_control_dialog._user_data
	self._paste_control_dialog._user_data = nil
	user_data.target.tab_child:ClearHandQuad()
	local add_list = {}
	local child_index = nil
	if user_data.child_index ~= nil then
		child_index = user_data.child_index + 1
	end
	local tree_object = user_data.target:TreePaste(user_data.info, self._control_paste_type.text, child_index, false, user_data.revoke_bind)
	add_list[1] = tree_object
	if user_data.callback ~= nil then
		user_data.callback(true, add_list)
	end
end

function ALittleIDE.IDEUIControlTree:ControlTreeJump(target)
	local extends_module = target.user_info.base.__module
	if extends_module == nil then
		extends_module = target.user_info.module
	end
	local extends_name = target.user_info.base.__extends
	local ui_manager = ALittleIDE.g_IDEProject:GetUIManager(extends_module)
	if ui_manager == nil then
		g_AUITool:ShowNotice("错误", "模块不存在:" .. extends_module)
		return
	end
	local control_info = ui_manager.control_map[extends_name]
	if control_info == nil then
		g_AUITool:ShowNotice("错误", "控件不存在:" .. extends_name)
		return
	end
	ALittleIDE.g_IDECenter.center.content_edit:StartEditControlBySelect(extends_module, extends_name)
end

function ALittleIDE.IDEUIControlTree:ControlTreeDesc(target)
	local x, y = target:LocalToGlobal()
	local desc = target:GetDesc()
	local name = g_AUITool:ShowRename(desc, x, y, target.width)
	if name == nil then
		return
	end
	target:SetDesc(name)
end
ALittleIDE.IDEUIControlTree.ControlTreeDesc = Lua.CoWrap(ALittleIDE.IDEUIControlTree.ControlTreeDesc)

function ALittleIDE.IDEUIControlTree:HandleTreeSearchClick(event)
	local tab = ALittleIDE.g_IDECenter.center.content_edit.cur_tab
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

end