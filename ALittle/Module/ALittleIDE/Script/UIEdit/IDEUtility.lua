-- ALittle Generate Lua
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-1105378563, "ALittleIDE.IDETreeUserInfo", {
name = "ALittleIDE.IDETreeUserInfo", ns_name = "ALittleIDE", rl_name = "IDETreeUserInfo", hash_code = -1105378563,
name_list = {"base","default","child_type","root","object","extends","extends_root"},
type_list = {"ALittle.DisplayInfo","ALittle.DisplayInfo","string","bool","ALittle.DisplayObject","bool","bool"},
option_map = {}
})
ALittle.RegStruct(-4982446, "ALittle.DisplayInfo", {
name = "ALittle.DisplayInfo", ns_name = "ALittle", rl_name = "DisplayInfo", hash_code = -4982446,
name_list = {"__target_class","__class_func","__base_attr","__show_attr","loop_map","__class","__include","__extends","__childs","__event","__link","__shows_included","__childs_included","__extends_included","description","text","font_path","font_size","red","green","blue","alpha","bold","italic","underline","deleteline","outline","x","y","x_type","x_value","y_type","y_value","width","height","width_type","width_value","height_type","height_value","scale_x","scale_y","center_x","center_y","angle","flip","hand_cursor","visible","disabled","left_size","right_size","top_size","bottom_size","texture_name","interval","play_loop_count","var_play","base_y","head_size","gap","up_size","down_size","cursor_red","cursor_green","cursor_blue","default_text_alpha","ims_padding","margin_left","margin_right","margin_top","margin_bottom","show_count","body_margin","screen_margin_left","screen_margin_right","screen_margin_top","screen_margin_bottom","start_degree","end_degree","line_spacing","max_line_count","font_red","font_green","font_blue","margin_halign","margin_valign","cursor_margin_up","cursor_margin_down","total_size","show_size","offset_rate","offset_step","grade","row_count","col_count","row_index","col_index","u1","v1","u2","v2","u3","v3","x1","y1","x2","y2","x3","y3","x_gap","y_gap","x_start_gap","y_start_gap","button_gap","button_start","button_margin","tab_index","view_margin","child_width_margin"},
type_list = {"List<string>","any","Map<string,any>","Map<string,any>","Map<string,ALittle.LoopGroupInfo>","string","string","string","List<ALittle.DisplayInfo>","List<ALittle.EventInfo>","string","bool","bool","bool","string","string","string","int","double","double","double","double","bool","bool","bool","bool","bool","double","double","int","double","int","double","double","double","int","double","int","double","double","double","double","double","double","int","bool","bool","bool","double","double","double","double","string","int","int","bool","double","double","double","double","double","double","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","double","double","double","int","int","int","int","int","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(1653869333, "ALittle.LoopGroupInfo", {
name = "ALittle.LoopGroupInfo", ns_name = "ALittle", rl_name = "LoopGroupInfo", hash_code = 1653869333,
name_list = {"childs"},
type_list = {"List<ALittle.LoopListInfo>"},
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
ALittle.RegStruct(-2110455927, "ALittle.EventInfo", {
name = "ALittle.EventInfo", ns_name = "ALittle", rl_name = "EventInfo", hash_code = -2110455927,
name_list = {"type","func"},
type_list = {"string","string"},
option_map = {}
})

function IDEUtility_CalcTextureName(info, map)
	if map == nil then
		map = {}
	end
	for k, v in ___pairs(info) do
		if k == "texture_name" then
			map[v] = true
		elseif ALittle.String_Type(v) == "table" then
			IDEUtility_CalcTextureName(v, map)
		end
	end
	return map
end

function IDEUtility_GetExtends(info, map)
	if map == nil then
		map = {}
	end
	for k, v in ___pairs(info) do
		if ALittle.String_Type(v) == "table" then
			IDEUtility_GetExtends(v, map)
		elseif k == "__extends" or k == "__include" then
			map[v] = true
		end
	end
	return map
end

function IDEUtility_HasTargetClass(info, name)
	local target_class = info.__target_class
	if target_class ~= nil then
		local str = ALittle.String_Join(target_class, ".")
		if ALittle.String_Find(str, name) ~= nil then
			return true
		end
	end
	for k, v in ___pairs(info) do
		if ALittle.String_Type(v) == "table" then
			if IDEUtility_HasTargetClass(v, name) then
				return true
			end
		end
	end
	return false
end

function IDEUtility_HasEventCallback(info, name)
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
			if IDEUtility_HasEventCallback(v, name) then
				return true
			end
		end
	end
	return false
end

function IDEUtility_CheckName(name)
	local len = ALittle.String_Len(name)
	if len == 0 then
		return false, "命名只能支持字母数字下划线，不能以数字开头"
	end
	local i = 1
	while true do
		if not(i <= len) then break end
		local byte = ALittle.String_Byte(name, i)
		local check_all = byte >= 65 and byte <= 90 or byte >= 97 and byte <= 122 or byte >= 48 and byte <= 57 or byte == 95
		if i == 1 then
			local check_first = byte >= 65 and byte <= 90 or byte >= 97 and byte <= 122 or byte == 95
			if check_first == false then
				return false, "命名只能支持字母数字，不能以数字开头"
			end
		else
			if check_all == false then
				return false, "命名只能支持字母数字，不能以数字开头"
			end
		end
		i = i+(1)
	end
	return true, nil
end

function IDEUtility_NewGiveBaseCase(info, object)
	if g_IDEEnum.text_type_display_map[info.__class] then
		info.font_path = g_IDEProject.project.config:GetConfig("default_font_path", nil)
		object.font_path = info.font_path
		local size = g_IDEProject.project.config:GetConfig("default_font_size", 15)
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

function IDEUtility_DragAddGiveBaseCase(info)
	if g_IDEEnum.text_type_display_map[info.__class] then
		info.font_path = g_IDEProject.project.config:GetConfig("default_font_path", nil)
		local size = g_IDEProject.project.config:GetConfig("default_font_size", 15)
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

function IDEUtility_GetBaseInfo(info)
	local base = {}
	for k, v in ___pairs(info) do
		if ALittle.String_Type(v) ~= "table" then
			base[k] = v
		elseif ALittle.String_Type(v) == "table" and k ~= "__childs" then
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

function IDEUtility_GetDefaultInfo(info)
	local default_v = {}
	if info.__extends ~= nil then
		default_v = IDEUtility_GetDefaultInfo(g_IDEProject.project.control_map[info.__extends].info)
		for k, v in ___pairs(info) do
			if k ~= "__extends" then
				default_v[k] = v
			end
		end
	elseif info.__include ~= nil then
		default_v = IDEUtility_GetDefaultInfo(g_IDEProject.project.control_map[info.__include].info)
	elseif info.__class ~= nil then
		local class_default = g_IDEEnum.type_default_map[info.__class]
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

function IDEUtility_CreateTree(control, extends_v, object, child_type, tab_child, root)
	local user_info = {}
	user_info.base = IDEUtility_GetBaseInfo(control)
	if control.__extends ~= nil then
		local control_info = g_IDEProject.project.control_map[control.__extends]
		if control_info == nil then
			g_IDETool:ShowNotice("错误", "extends 的控件不存在:" .. control.__extends)
		end
		user_info.default = IDEUtility_GetDefaultInfo(control_info.info)
	elseif control.__include ~= nil then
		local control_info = g_IDEProject.project.control_map[control.__include]
		if control_info == nil then
			g_IDETool:ShowNotice("错误", "include 的控件不存在:" .. control.__include)
		end
		user_info.default = IDEUtility_GetDefaultInfo(control_info.info)
	elseif control.__class ~= nil then
		user_info.default = g_IDEEnum.type_default_map[control.__class]
	else
		ALittle.Log("error CreateTree: there have no extends,include,class")
	end
	local nature_list = g_IDEEnum.nature_show_map[user_info.default.__class]
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
	if g_IDEEnum.can_add_child_map[user_info.default.__class] or g_IDEEnum.child_show_map[user_info.default.__class] ~= nil then
		tree_logic = IDETree(g_Control, user_info, tab_child)
	else
		tree_logic = IDETreeItem(g_Control, user_info, tab_child)
	end
	if g_IDEEnum.can_add_child_map[user_info.default.__class] and object.childs ~= nil and ALittle.List_MaxN(object.childs) > 0 then
		if control.__childs ~= nil and ALittle.List_MaxN(control.__childs) > 0 then
			local childs = control.__childs
			for k, v in ___ipairs(childs) do
				tree_logic:AddChild(IDEUtility_CreateTree(v, extends_v, object.childs[k], "child", tab_child, false))
			end
		elseif user_info.default.__childs ~= nil and ALittle.List_MaxN(user_info.default.__childs) > 0 then
			local childs = user_info.default.__childs
			for k, v in ___ipairs(childs) do
				tree_logic:AddChild(IDEUtility_CreateTree(v, true, object.childs[k], "child", tab_child, false))
			end
		end
	end
	local show_list = g_IDEEnum.child_show_map[user_info.default.__class]
	if show_list ~= nil then
		for index, name in ___ipairs(show_list) do
			if object[name] ~= nil then
				if control[name] ~= nil then
					tree_logic:AddChild(IDEUtility_CreateTree(control[name], extends_v, object[name], name, tab_child, false))
				elseif user_info.default[name] ~= nil then
					tree_logic:AddChild(IDEUtility_CreateTree(user_info.default[name], true, object[name], name, tab_child, false))
				end
			end
		end
	end
	tree_logic:UpdateDesc()
	return tree_logic
end

function IDEUtility_GenerateGrid9ImageInfo(base_path, image_path)
	local surface = ALittle.System_LoadSurface(base_path .. image_path)
	if surface == nil then
		return nil
	end
	local width = ALittle.System_GetSurfaceWidth(surface)
	local height = ALittle.System_GetSurfaceHeight(surface)
	local helf_width = ALittle.Math_Floor(width / 2)
	local helf_height = ALittle.Math_Floor(height / 2)
	local left = ALittle.System_GetSurfaceGrid9(surface, "left")
	local right = ALittle.System_GetSurfaceGrid9(surface, "right")
	local top = ALittle.System_GetSurfaceGrid9(surface, "top")
	local bottom = ALittle.System_GetSurfaceGrid9(surface, "bottom")
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
	ALittle.System_FreeSurface(surface)
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

