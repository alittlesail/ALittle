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
ALittle.RegStruct(-1133828708, "ALittleIDE.IDEUITreeUserInfo", {
name = "ALittleIDE.IDEUITreeUserInfo", ns_name = "ALittleIDE", rl_name = "IDEUITreeUserInfo", hash_code = -1133828708,
name_list = {"base","default","child_type","root","object","extends","extends_root","module"},
type_list = {"ALittle.DisplayInfo","ALittle.DisplayInfo","string","bool","ALittle.DisplayObject","bool","bool","string"},
option_map = {}
})
ALittle.RegStruct(-925381158, "ALittle.LoopChildInfo", {
name = "ALittle.LoopChildInfo", ns_name = "ALittle", rl_name = "LoopChildInfo", hash_code = -925381158,
name_list = {"clazz","target","total_time","delay_time"},
type_list = {"string","any","int","int"},
option_map = {}
})
ALittle.RegStruct(489101099, "ALittleIDE.IDEControlCopyInfo", {
name = "ALittleIDE.IDEControlCopyInfo", ns_name = "ALittleIDE", rl_name = "IDEControlCopyInfo", hash_code = 489101099,
name_list = {"index","module","info"},
type_list = {"int","string","ALittle.DisplayInfo"},
option_map = {}
})
ALittle.RegStruct(-4982446, "ALittle.DisplayInfo", {
name = "ALittle.DisplayInfo", ns_name = "ALittle", rl_name = "DisplayInfo", hash_code = -4982446,
name_list = {"__target_class","__class_func","__base_attr","__show_attr","loop_map","__module","__class","__include","__extends","__childs","__event","__link","__shows_included","__childs_included","__extends_included","description","text","font_path","font_size","red","green","blue","alpha","bold","italic","underline","deleteline","x","y","x_type","x_value","y_type","y_value","width","height","width_type","width_value","height_type","height_value","scale_x","scale_y","center_x","center_y","angle","flip","hand_cursor","visible","disabled","left_size","right_size","top_size","bottom_size","texture_name","interval","play_loop_count","var_play","base_y","head_size","gap","up_size","down_size","cursor_red","cursor_green","cursor_blue","default_text_alpha","ims_padding","margin_left","margin_right","margin_top","margin_bottom","show_count","body_margin","screen_margin_left","screen_margin_right","screen_margin_top","screen_margin_bottom","start_degree","end_degree","line_spacing","max_line_count","font_red","font_green","font_blue","margin_halign","margin_valign","cursor_margin_up","cursor_margin_down","total_size","show_size","offset_rate","offset_step","grade","row_count","col_count","row_index","col_index","u1","v1","u2","v2","u3","v3","x1","y1","x2","y2","x3","y3","x_gap","y_gap","x_start_gap","y_start_gap","button_gap","button_start","button_margin","tab_index","view_margin","child_width_margin"},
type_list = {"List<string>","any","Map<string,any>","Map<string,ALittle.DisplayInfo>","Map<string,ALittle.LoopGroupInfo>","string","string","string","string","List<ALittle.DisplayInfo>","List<ALittle.EventInfo>","string","bool","bool","bool","string","string","string","int","double","double","double","double","bool","bool","bool","bool","double","double","int","double","int","double","double","double","int","double","int","double","double","double","double","double","double","int","bool","bool","bool","double","double","double","double","string","int","int","bool","double","double","double","double","double","double","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","double","double","double","int","int","int","int","int","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double"},
option_map = {}
})

function ALittleIDE.IDEUIUtility_CalcTextureName(info, map)
	if map == nil then
		map = {}
	end
	for k, v in ___pairs(info) do
		if k == "texture_name" then
			map[v] = true
		elseif ALittle.String_Type(v) == "table" then
			ALittleIDE.IDEUIUtility_CalcTextureName(v, map)
		end
	end
	return map
end

function ALittleIDE.IDEUIUtility_GetExtends(module, info, map)
	if map == nil then
		map = {}
	end
	for k, v in ___pairs(info) do
		if ALittle.String_Type(v) == "table" then
			ALittleIDE.IDEUIUtility_GetExtends(module, v, map)
		elseif k == "__extends" or k == "__include" then
			local module_name = module
			if info.__module ~= nil then
				module_name = info.__module
			end
			local sub_map = map[module_name]
			if sub_map == nil then
				sub_map = {}
				map[module_name] = sub_map
			end
			sub_map[v] = true
		end
	end
	return map
end

function ALittleIDE.IDEUIUtility_HasTargetClass(info, name)
	local target_class = info.__target_class
	if target_class ~= nil then
		local str = ALittle.String_Join(target_class, ".")
		if ALittle.String_Find(str, name) ~= nil then
			return true
		end
	end
	for k, v in ___pairs(info) do
		if ALittle.String_Type(v) == "table" then
			if ALittleIDE.IDEUIUtility_HasTargetClass(v, name) then
				return true
			end
		end
	end
	return false
end

function ALittleIDE.IDEUIUtility_HasEventCallback(info, name)
	local event = info.__event
	if event ~= nil then
		local content_list = {}
		local count = 0
		for index, event_info in ___ipairs(event) do
			local data_type = event_info.type .. ":"
			local event_string = data_type .. event_info.func
			count = count + 1
			content_list[count] = event_string
		end
		local content = ALittle.String_Join(content_list, "\n")
		if ALittle.String_Find(content, name) ~= nil then
			return true
		end
	end
	for k, v in ___pairs(info) do
		if ALittle.String_Type(v) == "table" then
			if ALittleIDE.IDEUIUtility_HasEventCallback(v, name) then
				return true
			end
		end
	end
	return false
end

function ALittleIDE.IDEUIUtility_NewGiveBaseCase(info, object)
	if ALittleIDE.g_IDEEnum.text_type_display_map[info.__class] then
		info.font_path = ALittleIDE.g_IDEProject.project.config:GetConfig("default_font_path", nil)
		object.font_path = info.font_path
		local size = ALittleIDE.g_IDEProject.project.config:GetConfig("default_font_size", 15)
		info.font_size = size
		object.font_size = size
		if info.__class == "Text" then
			info.text = "123456789"
			object.text = "123456789"
			object:RejuseSize()
		else
			info.width_type = 4
			object.width_type = 4
			info.height_type = 4
			object.height_type = 4
		end
	else
		info.width_type = 4
		object.width_type = 4
		info.height_type = 4
		object.height_type = 4
	end
end

function ALittleIDE.IDEUIUtility_DragAddGiveBaseCase(info)
	if ALittleIDE.g_IDEEnum.text_type_display_map[info.__class] then
		info.font_path = ALittleIDE.g_IDEProject.project.config:GetConfig("default_font_path", nil)
		local size = ALittleIDE.g_IDEProject.project.config:GetConfig("default_font_size", 15)
		info.font_size = size
		if info.__class ~= "Text" then
			info.width_value = 100
			info.height_value = 100
		else
			info.text = "123456789"
		end
	else
		info.width_value = 100
		info.height_value = 100
	end
end

function ALittleIDE.IDEUIUtility_GetBaseInfo(info)
	local base = {}
	for k, v in ___pairs(info) do
		if ALittle.String_Type(v) ~= "table" then
			base[k] = v
		elseif not (k == "__childs" or (ALittleIDE.g_IDEEnum.nature_show_map_map[info.__class] ~= nil and ALittleIDE.g_IDEEnum.nature_show_map_map[info.__class][k]) or (ALittleIDE.g_IDEEnum.child_show_map_map[info.__class] ~= nil and ALittleIDE.g_IDEEnum.child_show_map_map[info.__class][k])) then
			base[k] = ALittle.String_CopyTable(v)
		end
	end
	local link = info.__link
	if link ~= nil then
		base.__link = link
	end
	local event = info.__event
	if event ~= nil then
		base.__event = ALittle.String_CopyTable(event)
	end
	return base
end

function ALittleIDE.IDEUIUtility_GetDefaultInfo(module_name, info)
	local default_v = {}
	if info.__extends ~= nil then
		if info.__module ~= nil then
			module_name = info.__module
		end
		local ui_manager = ALittleIDE.g_IDEProject:GetUIManager(module_name)
		default_v = ALittleIDE.IDEUIUtility_GetDefaultInfo(module_name, ui_manager.control_map[info.__extends].info)
		for k, v in ___pairs(info) do
			if k ~= "__extends" and k ~= "__module" then
				default_v[k] = v
			end
		end
	elseif info.__include ~= nil then
		if info.__module ~= nil then
			module_name = info.__module
		end
		local ui_manager = ALittleIDE.g_IDEProject:GetUIManager(module_name)
		default_v = ALittleIDE.IDEUIUtility_GetDefaultInfo(module_name, ui_manager.control_map[info.__include].info)
	elseif info.__class ~= nil then
		local class_default = ALittleIDE.g_IDEEnum.type_default_map[info.__class]
		default_v = {}
		for k, v in ___pairs(class_default) do
			if ALittle.String_Type(v) ~= "table" then
				default_v[k] = v
			end
		end
		for k, v in ___pairs(info) do
			default_v[k] = v
		end
	else
		ALittle.Log("error GetDefaultInfo: there have not extends, include, class")
	end
	return default_v
end

function ALittleIDE.IDEUIUtility_CreateTree(control, module, extends_v, object, child_type, tab_child, root)
	local user_info = {}
	user_info.module = module
	user_info.base = ALittleIDE.IDEUIUtility_GetBaseInfo(control)
	if control.__extends ~= nil then
		local module_name = user_info.module
		if control.__module ~= nil then
			module_name = control.__module
		end
		local ui_manager = ALittleIDE.g_IDEProject:GetUIManager(module_name)
		local control_info = ui_manager.control_map[control.__extends]
		if control_info == nil then
			g_AUITool:ShowNotice("错误", "extends 的控件不存在:" .. control.__extends)
			return nil
		end
		user_info.default = ALittleIDE.IDEUIUtility_GetDefaultInfo(module_name, control_info.info)
	elseif control.__include ~= nil then
		local module_name = user_info.module
		if control.__module ~= nil then
			module_name = control.__module
		end
		local ui_manager = ALittleIDE.g_IDEProject:GetUIManager(module_name)
		local control_info = ui_manager.control_map[control.__include]
		if control_info == nil then
			g_AUITool:ShowNotice("错误", "include 的控件不存在:" .. control.__include)
			return nil
		end
		user_info.default = ALittleIDE.IDEUIUtility_GetDefaultInfo(module_name, control_info.info)
	elseif control.__class ~= nil then
		user_info.default = ALittleIDE.g_IDEEnum.type_default_map[control.__class]
	else
		g_AUITool:ShowNotice("错误", "控件内容没有定义:extends,include,class")
		return nil
	end
	local nature_list = ALittleIDE.g_IDEEnum.nature_show_map[user_info.default.__class]
	if nature_list ~= nil then
		for index, name in ___ipairs(nature_list) do
			if control[name] ~= nil then
				user_info.base[name] = ALittle.String_CopyTable(control[name])
			end
		end
	end
	user_info.child_type = child_type
	user_info.root = root
	user_info.object = object
	user_info.extends = extends_v
	user_info.extends_root = control.__extends ~= nil
	local tree_logic = nil
	if ALittleIDE.g_IDEEnum.can_add_child_map[user_info.default.__class] or ALittleIDE.g_IDEEnum.child_show_map[user_info.default.__class] ~= nil then
		tree_logic = ALittleIDE.IDEUITree(ALittleIDE.g_Control, user_info, tab_child)
	else
		tree_logic = ALittleIDE.IDEUITreeItem(ALittleIDE.g_Control, user_info, tab_child)
	end
	if ALittleIDE.g_IDEEnum.can_add_child_map[user_info.default.__class] and object.childs ~= nil and ALittle.List_Len(object.childs) > 0 then
		if control.__childs ~= nil and ALittle.List_Len(control.__childs) > 0 then
			local childs = control.__childs
			for k, v in ___ipairs(childs) do
				local tree = ALittleIDE.IDEUIUtility_CreateTree(v, module, extends_v, object.childs[k], "child", tab_child, false)
				if tree == nil then
					return nil
				end
				tree_logic:AddChild(tree)
			end
		elseif user_info.default.__childs ~= nil and ALittle.List_Len(user_info.default.__childs) > 0 then
			local module_name = module
			if control.__module ~= nil then
				module_name = control.__module
			end
			local childs = user_info.default.__childs
			for k, v in ___ipairs(childs) do
				local tree = ALittleIDE.IDEUIUtility_CreateTree(v, module_name, true, object.childs[k], "child", tab_child, false)
				if tree == nil then
					return nil
				end
				tree_logic:AddChild(tree)
			end
		end
	end
	local show_list = ALittleIDE.g_IDEEnum.child_show_map[user_info.default.__class]
	if show_list ~= nil then
		for index, name in ___ipairs(show_list) do
			if object[name] ~= nil then
				if control[name] ~= nil then
					local tree = ALittleIDE.IDEUIUtility_CreateTree(control[name], module, extends_v, object[name], name, tab_child, false)
					if tree == nil then
						return nil
					end
					tree_logic:AddChild(tree)
				elseif user_info.default[name] ~= nil then
					local module_name = module
					if control.__module ~= nil then
						module_name = control.__module
					end
					local tree = ALittleIDE.IDEUIUtility_CreateTree(user_info.default[name], module_name, true, object[name], name, tab_child, false)
					if tree == nil then
						return nil
					end
					tree_logic:AddChild(tree)
				end
			end
		end
	end
	tree_logic:UpdateDesc()
	return tree_logic
end

function ALittleIDE.IDEUIUtility_GenerateGrid9ImageInfo(base_path, image_path)
	local surface = carp.LoadCarpSurface(base_path .. image_path)
	if surface == nil then
		return nil
	end
	local width = carp.GetCarpSurfaceWidth(surface)
	local height = carp.GetCarpSurfaceHeight(surface)
	local helf_width = ALittle.Math_Floor(width / 2)
	local helf_height = ALittle.Math_Floor(height / 2)
	local left = carp.GetCarpSurfaceGrid9(surface, "left")
	local right = carp.GetCarpSurfaceGrid9(surface, "right")
	local top = carp.GetCarpSurfaceGrid9(surface, "top")
	local bottom = carp.GetCarpSurfaceGrid9(surface, "bottom")
	if left == 0 then
		left = 1
	elseif left == helf_width then
		left = left - 2
	else
		left = left + 1
	end
	if right == width then
		right = 1
	elseif right == helf_width then
		right = right + 2
	else
		right = width - right + 1
	end
	if top == 0 then
		top = 1
	elseif top == helf_height then
		top = top - 2
	else
		top = top + 1
	end
	if bottom == height then
		bottom = 1
	elseif bottom == helf_height then
		bottom = bottom + 2
	else
		bottom = height - bottom + 1
	end
	carp.FreeCarpSurface(surface)
	local display_info = {}
	display_info.__class = "Grid9Image"
	display_info.texture_name = image_path
	display_info.width_type = 1
	display_info.width_value = width
	display_info.height_type = 1
	display_info.height_value = height
	display_info.left_size = left
	display_info.right_size = right
	display_info.top_size = top
	display_info.bottom_size = bottom
	return display_info
end

end