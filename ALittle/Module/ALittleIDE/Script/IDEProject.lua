-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(1910687721, "ALittleIDE.IDEProjectEvent", {
name = "ALittleIDE.IDEProjectEvent", ns_name = "ALittleIDE", rl_name = "IDEProjectEvent", hash_code = 1910687721,
name_list = {"target","name"},
type_list = {"ALittle.EventDispatcher","string"},
option_map = {}
})
ALittle.RegStruct(-975432877, "ALittleIDE.IDEProjectOpenEvent", {
name = "ALittleIDE.IDEProjectOpenEvent", ns_name = "ALittleIDE", rl_name = "IDEProjectOpenEvent", hash_code = -975432877,
name_list = {"target","name"},
type_list = {"ALittle.EventDispatcher","string"},
option_map = {}
})
ALittle.RegStruct(-332308624, "ALittleIDE.IDEProjectCloseEvent", {
name = "ALittleIDE.IDEProjectCloseEvent", ns_name = "ALittleIDE", rl_name = "IDEProjectCloseEvent", hash_code = -332308624,
name_list = {"target","name"},
type_list = {"ALittle.EventDispatcher","string"},
option_map = {}
})
ALittle.RegStruct(-93681239, "ALittleIDE.IDEProjectCreateControlEvent", {
name = "ALittleIDE.IDEProjectCreateControlEvent", ns_name = "ALittleIDE", rl_name = "IDEProjectCreateControlEvent", hash_code = -93681239,
name_list = {"target","name"},
type_list = {"ALittle.EventDispatcher","string"},
option_map = {}
})
ALittle.RegStruct(1962591044, "ALittleIDE.IDEProjectDeleteControlEvent", {
name = "ALittleIDE.IDEProjectDeleteControlEvent", ns_name = "ALittleIDE", rl_name = "IDEProjectDeleteControlEvent", hash_code = 1962591044,
name_list = {"target","name"},
type_list = {"ALittle.EventDispatcher","string"},
option_map = {}
})
ALittle.RegStruct(374071006, "ALittleIDE.IDEProjectChangeControlEvent", {
name = "ALittleIDE.IDEProjectChangeControlEvent", ns_name = "ALittleIDE", rl_name = "IDEProjectChangeControlEvent", hash_code = 374071006,
name_list = {"target","name"},
type_list = {"ALittle.EventDispatcher","string"},
option_map = {}
})
ALittle.RegStruct(1332927881, "ALittleIDE.IDEControlInfo", {
name = "ALittleIDE.IDEControlInfo", ns_name = "ALittleIDE", rl_name = "IDEControlInfo", hash_code = 1332927881,
name_list = {"info","name","extends_this","extends_other"},
type_list = {"ALittle.DisplayInfo","string","Map<string,bool>","Map<string,bool>"},
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
ALittle.RegStruct(489101099, "ALittleIDE.IDEControlCopyInfo", {
name = "ALittleIDE.IDEControlCopyInfo", ns_name = "ALittleIDE", rl_name = "IDEControlCopyInfo", hash_code = 489101099,
name_list = {"index","info"},
type_list = {"int","ALittle.DisplayInfo"},
option_map = {}
})
ALittle.RegStruct(934918978, "ALittleIDE.IDEProjectInfo", {
name = "ALittleIDE.IDEProjectInfo", ns_name = "ALittleIDE", rl_name = "IDEProjectInfo", hash_code = 934918978,
name_list = {"name","base_path","save","control","config","control_map"},
type_list = {"string","string","bool","ALittle.ControlSystem","ALittle.IJsonConfig","Map<string,ALittleIDE.IDEControlInfo>"},
option_map = {}
})

assert(ALittle.EventDispatcher, " extends class:ALittle.EventDispatcher is nil")
IDEProject = Lua.Class(ALittle.EventDispatcher, "ALittleIDE.IDEProject")

function IDEProject:Ctor()
end

function IDEProject:AddProjectConfig(name)
	local project_map = g_IDEConfig:GetConfig("project_map", {})
	if project_map[name] == nil then
		project_map[name] = name
		g_IDEConfig:SetConfig("project_map", project_map)
	end
end

function IDEProject:RemoveProjectConfig(name)
	local project_map = g_IDEConfig:GetConfig("project_map", {})
	if project_map[name] == nil then
		return
	end
	project_map[name] = nil
	g_IDEConfig:SetConfig("project_map", project_map)
end

function IDEProject:NewProject(name, window_width, window_height, font_path, font_size)
	ALittle.File_MakeDeepDir(ALittle.File_BaseFilePath() .. "Module/" .. name)
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Texture")
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Texture/" .. name)
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Font")
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Sound")
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Other")
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Protocol")
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Script")
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/UI")
	ALittle.File_MakeDir(ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Icon")
	ALittle.File_WriteTextToFile("", ALittle.File_BaseFilePath() .. "Module/" .. name .. "/NoCrypt.ali")
	local base_path = ALittle.File_BaseFilePath() .. "Module/ALittleIDE/Other/GameTemplate"
	local target_path = ALittle.File_BaseFilePath() .. "Module/" .. name .. "/"
	local file_map = ALittle.File_GetFileAttrByDir(base_path)
	for file_path, attr in ___pairs(file_map) do
		local rel_path = ALittle.String_Sub(file_path, ALittle.String_Len(base_path) + 1)
		local full_path = target_path .. rel_path
		full_path = ALittle.String_Replace(full_path, "abcd@module_name@abcd", name)
		full_path = ALittle.String_Replace(full_path, "abcd@upper_module_name@abcd", ALittle.String_Upper(name))
		full_path = ALittle.String_Replace(full_path, "abcd@lower_module_name@abcd", ALittle.String_Lower(name))
		ALittle.File_MakeDeepDir(ALittle.File_GetFilePathByPath(full_path))
		local ext = ALittle.String_Upper(ALittle.File_GetFileExtByPath(file_path))
		if ext == "JSON" or ext == "LUA" or ext == "CFG" or ext == "TXT" or ext == "ALITTLE" or ext == "XML" or ext == "NAME" then
			local content = ALittle.File_ReadTextFromFile(file_path)
			if content ~= nil then
				content = ALittle.String_Replace(content, "abcd@module_name@abcd", name)
				content = ALittle.String_Replace(content, "abcd@upper_module_name@abcd", ALittle.String_Upper(name))
				content = ALittle.String_Replace(content, "abcd@lower_module_name@abcd", ALittle.String_Lower(name))
				content = ALittle.String_Replace(content, "abcd@view_width@abcd", "" .. window_width)
				content = ALittle.String_Replace(content, "abcd@view_height@abcd", "" .. window_height)
				content = ALittle.String_Replace(content, "abcd@font_path@abcd", font_path)
				ALittle.File_WriteTextToFile(content, full_path)
			end
		else
			ALittle.File_CopyFile(file_path, full_path)
		end
	end
	ALittle.File_CopyFile("Export/Icon/install.ico", ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Icon/install.ico")
	ALittle.File_CopyFile("Export/Icon/install.png", ALittle.File_BaseFilePath() .. "Module/" .. name .. "/Icon/install.png")
	local config = ALittle.CreateConfigSystem("Module/" .. name .. "/ALittleIDE.cfg")
	config:SetConfig("default_show_width", window_width, true)
	config:SetConfig("default_show_height", window_height, true)
	config:SetConfig("default_font_path", font_path, true)
	config:SetConfig("default_font_size", font_size, true)
	config:SaveConfig()
	self:AddProjectConfig(name)
	return true
end

function IDEProject:OpenProject(name)
	self:AddProjectConfig(name)
	self._project = {}
	self._project.name = name
	self._project.base_path = ALittle.File_BaseFilePath() .. "Module/" .. name .. "/"
	self._project.save = true
	self._project.control = ALittle.ControlSystem(name)
	self._project.control.log_error = false
	self._project.control.cache_texture = false
	self._project.config = ALittle.CreateConfigSystem("Module/" .. name .. "/ALittleIDE.cfg")
	local control_map = {}
	self._project.control_map = control_map
	local path = ALittle.File_BaseFilePath() .. "Module/" .. name .. "/UI"
	local file_map = ALittle.File_GetFileAttrByDir(path)
	for file_path, attr in ___pairs(file_map) do
		local ext = ALittle.String_Upper(ALittle.File_GetFileExtByPath(file_path))
		if ext == "JSON" then
			local content = ALittle.File_ReadTextFromFile(file_path)
			if content ~= nil then
				local error, content_info_map = Lua.TCall(ALittle.String_JsonDecode, content)
				if error == nil then
					for control_name, control_info in ___pairs(content_info_map) do
						local all_info = {}
						all_info.info = control_info
						all_info.name = control_name
						all_info.extends_this = {}
						all_info.extends_other = {}
						if control_map[control_name] ~= nil then
							ALittle.Log("IDEProject:OpenProject control_name:" .. control_name .. " repeat in " .. file_path)
						end
						control_map[control_name] = all_info
					end
				else
					ALittle.Log("IDEProject:OpenProject json decode failed:", file_path, content_info_map)
				end
			else
				ALittle.Log("IDEProject:OpenProject failed:", file_path)
			end
		end
	end
	for control_name, all_info in ___pairs(control_map) do
		local map = IDEUtility_GetExtends(all_info.info)
		for other_name, v in ___pairs(map) do
			local other = control_map[other_name]
			if other ~= nil then
				other.extends_this[control_name] = true
				all_info.extends_other[other_name] = true
			else
				ALittle.Log("IDEProject:OpenProject calc extends failed:", other_name)
			end
		end
	end
	g_IDEConfig:SetConfig("last_project", name)
	local e = {}
	e.name = name
	self:DispatchEvent(___all_struct[-975432877], e)
	return true
end

function IDEProject:IsControlExist(name)
	if self._project == nil then
		return false
	end
	return self._project.control_map[name] ~= nil
end

function IDEProject:CalcDeepExtends(name, map, lock_map)
	if map == nil then
		map = {}
	end
	if lock_map == nil then
		lock_map = {}
	end
	local info = self._project.control_map[name]
	if info == nil then
		return map
	end
	map[name] = true
	for other_name, v in ___pairs(info.extends_other) do
		if lock_map[other_name] == nil then
			lock_map[other_name] = true
			self:CalcDeepExtends(other_name, map, lock_map)
		end
		map[other_name] = true
	end
	return map
end

function IDEProject:SaveControl(name, info)
	local file_path = self._project.base_path .. "UI/" .. name .. ".json"
	local save_info = {}
	save_info[name] = info
	if ALittle.File_SaveFile(file_path, ALittle.String_JsonEncode(save_info), -1) == false then
		return false, "文件保存失败:" .. file_path
	end
	local all_info = self._project.control_map[name]
	if all_info ~= nil then
		for other_name, v in ___pairs(all_info.extends_other) do
			local other = self._project.control_map[other_name]
			if other ~= nil then
				other.extends_this[name] = nil
			else
				ALittle.Log("IDEProject:SaveControl calc extends failed:", other_name)
			end
		end
		all_info.extends_other = {}
		for other_name, v in ___pairs(all_info.extends_this) do
			local other = self._project.control_map[other_name]
			if other ~= nil then
				self._project.control:RegisterInfo(other.name, ALittle.String_CopyTable(other.info))
			else
				ALittle.Log("IDEProject:SaveControl calc extends failed:", other_name)
			end
		end
	else
		all_info = {}
		all_info.info = info
		all_info.name = name
		all_info.extends_this = {}
		all_info.extends_other = {}
	end
	local map = IDEUtility_GetExtends(info)
	for other_name, v in ___pairs(map) do
		local other = self._project.control_map[other_name]
		if other ~= nil then
			other.extends_this[name] = true
			all_info.extends_other[other_name] = true
		else
			ALittle.Log("IDEProject:SaveControl calc extends failed:", other_name)
		end
	end
	all_info.info = info
	self._project.control_map[name] = all_info
	self._project.control:RegisterInfo(name, ALittle.String_CopyTable(info))
	local e = {}
	e.name = name
	self:DispatchEvent(___all_struct[374071006], e)
	return true, nil
end

function IDEProject:CanDelete(name)
	local all_info = self._project.control_map[name]
	if all_info == nil then
		return false, "控件不存在:" .. name
	end
	local extends_name = nil
	for k, v in ___pairs(all_info.extends_this) do
		extends_name = k
		break
	end
	if extends_name ~= nil then
		return false, "被其他控件引用:" .. extends_name
	end
	return true, nil
end

function IDEProject:DeleteControl(name)
	local result, content = self:CanDelete(name)
	if result == false then
		return result, content
	end
	local file_path = self._project.base_path .. "UI/" .. name .. ".json"
	ALittle.File_DeleteFile(file_path)
	local all_info = self._project.control_map[name]
	for other_name, v in ___pairs(all_info.extends_other) do
		local other = self._project.control_map[other_name]
		if other ~= nil then
			other.extends_this[name] = nil
		end
	end
	local e = {}
	e.name = name
	self:DispatchEvent(___all_struct[1962591044], e)
	self._project.control_map[name] = nil
	self._project.control:UnRegisterInfo(name)
	return true, nil
end

function IDEProject:RenameControl(old_name, new_name)
	local all_info = self._project.control_map[old_name]
	if all_info == nil then
		return false, "控件不存在:" .. old_name
	end
	local result, content = self:CanDelete(old_name)
	if result == false then
		return result, "控件被其他控件引用，不能重命名"
	end
	if self._project.control_map[new_name] ~= nil then
		return false, "控件已存在:" .. new_name
	end
	local e = {}
	e.name = old_name
	self:DispatchEvent(___all_struct[1962591044], e)
	self._project.control_map[old_name] = nil
	self._project.control:UnRegisterInfo(old_name)
	local file_path = self._project.base_path .. "UI/" .. old_name .. ".json"
	ALittle.File_DeleteFile(file_path)
	all_info.name = new_name
	self._project.control_map[new_name] = all_info
	self._project.control:RegisterInfo(new_name, ALittle.String_CopyTable(all_info.info))
	file_path = self._project.base_path .. "UI/" .. new_name .. ".json"
	local save_info = {}
	save_info[new_name] = all_info.info
	ALittle.File_SaveFile(file_path, ALittle.String_JsonEncode(save_info), -1)
	local ce = {}
	ce.name = new_name
	self:DispatchEvent(___all_struct[-93681239], ce)
	return true, nil
end

function IDEProject:CloseProject()
	if self._project == nil then
		return false, "当前没有项目"
	end
	local e = {}
	e.name = self._project.name
	self:DispatchEvent(___all_struct[-332308624], e)
	self._project = nil
	return true, nil
end

function IDEProject:RemoveProject(name)
	if self._project ~= nil and self._project.name == name then
		return false, "请先关闭项目，再移除"
	end
	self:RemoveProjectConfig(name)
	local project_name = g_IDEConfig:GetConfig("last_project", "")
	if project_name == name then
		g_IDEConfig:SetConfig("last_project", "")
	end
	return true, nil
end

function IDEProject.__getter:project()
	return self._project
end

g_IDEProject = IDEProject()
