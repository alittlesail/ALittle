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
ALittle.RegStruct(1332927881, "ALittleIDE.IDEControlInfo", {
name = "ALittleIDE.IDEControlInfo", ns_name = "ALittleIDE", rl_name = "IDEControlInfo", hash_code = 1332927881,
name_list = {"info","name","extends_this","extends_other"},
type_list = {"ALittle.DisplayInfo","string","Map<string,bool>","Map<string,bool>"},
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

ALittleIDE.IDEUIManager = Lua.Class(nil, "ALittleIDE.IDEUIManager")

function ALittleIDE.IDEUIManager:Ctor()
	___rawset(self, "_control_map", {})
	___rawset(self, "_cur_map_other", {})
	___rawset(self, "_other_map_cur", {})
end

function ALittleIDE.IDEUIManager:Init(module)
	local ___COROUTINE = coroutine.running()
	self._module = module
	self._control = ALittle.ControlSystem(self._module)
	self._control.log_error = false
	self._control.cache_texture = false
	self._control.use_plugin_class = false
	self._base_path = ALittle.File_BaseFilePath() .. "Module/" .. self._module .. "/UI"
	local file_map = ALittle.File_GetFileAttrByDir(self._base_path)
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
						if self._control_map[control_name] ~= nil then
							ALittle.Log("IDEProject:OpenProject control_name:" .. control_name .. " repeat in " .. file_path)
						end
						self._control_map[control_name] = all_info
					end
				else
					ALittle.Log("IDEProject:OpenProject json decode failed:", file_path, content_info_map)
				end
			else
				ALittle.Log("IDEProject:OpenProject failed:", file_path)
			end
		end
	end
	for control_name, all_info in ___pairs(self._control_map) do
		local map = ALittleIDE.IDEUIUtility_GetExtends(self._module, all_info.info)
		for module_name, sub_map in ___pairs(map) do
			for other_name, v in ___pairs(sub_map) do
				if module_name == self._module then
					local other = self._control_map[other_name]
					if other ~= nil then
						other.extends_this[control_name] = true
						all_info.extends_other[other_name] = true
					else
						ALittle.Log("IDEProject:OpenProject calc extends failed:", other_name)
					end
				else
					local full_name = module_name .. "." .. other_name
					local other_map = self._cur_map_other[control_name]
					if other_map == nil then
						other_map = {}
						self._cur_map_other[control_name] = other_map
					end
					other_map[full_name] = true
					local cur_map = self._other_map_cur[full_name]
					if cur_map == nil then
						cur_map = {}
						self._other_map_cur[full_name] = cur_map
					end
					cur_map[control_name] = true
				end
			end
		end
	end
end

function ALittleIDE.IDEUIManager.__getter:control_map()
	return self._control_map
end

function ALittleIDE.IDEUIManager.__getter:control()
	return self._control
end

function ALittleIDE.IDEUIManager.__getter:texture_path()
	return ALittle.File_BaseFilePath() .. "Module/" .. self._module .. "/Texture"
end

function ALittleIDE.IDEUIManager:CalcDeepExtends(name, map, lock_map)
	if map == nil then
		map = {}
	end
	if lock_map == nil then
		lock_map = {}
	end
	local info = self._control_map[name]
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

function ALittleIDE.IDEUIManager:SaveControl(name, info)
	local file_path = self._base_path .. "/" .. name .. ".json"
	local save_info = {}
	save_info[name] = info
	if ALittle.File_SaveFile(file_path, ALittle.String_JsonEncode(save_info), -1) == false then
		return "文件保存失败:" .. file_path
	end
	local all_info = self._control_map[name]
	if all_info ~= nil then
		for other_name, v in ___pairs(all_info.extends_other) do
			local other = self._control_map[other_name]
			if other ~= nil then
				other.extends_this[name] = nil
			else
				ALittle.Log("IDEProject:SaveControl calc extends failed:", other_name)
			end
		end
		local cur_map = self._cur_map_other[name]
		if cur_map ~= nil then
			for full_name, _ in ___pairs(cur_map) do
				local other_map = self._other_map_cur[full_name]
				if other_map ~= nil then
					other_map[name] = nil
				end
				if ALittle.IsEmpty(other_map) then
					self._other_map_cur[full_name] = nil
				end
			end
			self._cur_map_other[name] = nil
		end
		all_info.extends_other = {}
		for other_name, v in ___pairs(all_info.extends_this) do
			local other = self._control_map[other_name]
			if other ~= nil then
				self._control:RegisterInfo(other.name, ALittle.String_CopyTable(other.info))
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
	local map = ALittleIDE.IDEUIUtility_GetExtends(self._module, info)
	for module_name, sub_map in ___pairs(map) do
		for other_name, v in ___pairs(sub_map) do
			if module_name == self._module then
				local other = self._control_map[other_name]
				if other ~= nil then
					other.extends_this[name] = true
					all_info.extends_other[other_name] = true
				else
					ALittle.Log("IDEProject:OpenProject calc extends failed:", other_name)
				end
			else
				local other_map = self._cur_map_other[name]
				if other_map == nil then
					other_map = {}
					self._cur_map_other[name] = other_map
				end
				other_map[module_name .. other_name] = true
				local cur_map = self._other_map_cur[module_name .. other_name]
				if cur_map == nil then
					cur_map = {}
					self._other_map_cur[module_name .. other_name] = cur_map
				end
				cur_map[name] = true
			end
		end
	end
	all_info.info = info
	self._control_map[name] = all_info
	self._control:RegisterInfo(name, ALittle.String_CopyTable(info))
	return nil
end

function ALittleIDE.IDEUIManager:CanDelete(name)
	local all_info = self._control_map[name]
	if all_info == nil then
		return "控件不存在:" .. name
	end
	local extends_name = nil
	for k, v in ___pairs(all_info.extends_this) do
		extends_name = k
		break
	end
	if extends_name ~= nil then
		return "被其他控件引用:" .. extends_name
	end
	local full_name = self._module .. "." .. name
	for module_name, ui_manager in ___pairs(ALittleIDE.g_IDEProject.project.ui) do
		if module_name ~= self._module then
			local cur_map = ui_manager._other_map_cur[full_name]
			if cur_map ~= nil then
				for control_name, _ in ___pairs(cur_map) do
					return "被其他模块控件引用:" .. module_name .. "." .. control_name
				end
			end
		end
	end
	return nil
end

function ALittleIDE.IDEUIManager:DeleteControl(name)
	local error = self:CanDelete(name)
	if error ~= error then
		return error
	end
	local file_path = self._base_path .. "/" .. name .. ".json"
	ALittle.File_DeleteFile(file_path)
	local all_info = self._control_map[name]
	for other_name, v in ___pairs(all_info.extends_other) do
		local other = self._control_map[other_name]
		if other ~= nil then
			other.extends_this[name] = nil
		end
	end
	local cur_map = self._cur_map_other[name]
	if cur_map ~= nil then
		for full_name, _ in ___pairs(cur_map) do
			local other_map = self._other_map_cur[full_name]
			if other_map ~= nil then
				other_map[name] = nil
			end
			if ALittle.IsEmpty(other_map) then
				self._other_map_cur[full_name] = nil
			end
		end
		self._cur_map_other[name] = nil
	end
	local e = {}
	e.module = self._module
	e.name = name
	ALittleIDE.g_IDEProject:DispatchEvent(___all_struct[1962591044], e)
	self._control_map[name] = nil
	self._control:UnRegisterInfo(name)
	return nil
end

function ALittleIDE.IDEUIManager:RenameControl(old_name, new_name)
	local all_info = self._control_map[old_name]
	if all_info == nil then
		return "控件不存在:" .. old_name
	end
	local error = self:CanDelete(old_name)
	if error ~= nil then
		return "控件被其他控件引用，不能重命名"
	end
	if self._control_map[new_name] ~= nil then
		return "控件已存在:" .. new_name
	end
	local e = {}
	e.module = self._module
	e.name = old_name
	ALittleIDE.g_IDEProject:DispatchEvent(___all_struct[1962591044], e)
	self._control_map[old_name] = nil
	self._control:UnRegisterInfo(old_name)
	local file_path = self._base_path .. "/" .. old_name .. ".json"
	ALittle.File_DeleteFile(file_path)
	all_info.name = new_name
	self._control_map[new_name] = all_info
	self._control:RegisterInfo(new_name, ALittle.String_CopyTable(all_info.info))
	file_path = self._base_path .. "/" .. new_name .. ".json"
	local save_info = {}
	save_info[new_name] = all_info.info
	ALittle.File_SaveFile(file_path, ALittle.String_JsonEncode(save_info), -1)
	local ce = {}
	ce.module = self._module
	ce.name = new_name
	ALittleIDE.g_IDEProject:DispatchEvent(___all_struct[-93681239], ce)
	return nil
end

end