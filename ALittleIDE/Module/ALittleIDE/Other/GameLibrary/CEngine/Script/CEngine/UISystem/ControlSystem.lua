-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


local __byte = ALittle.String_Byte
local __type = ALittle.String_Type
ALittle.ControlSystem = Lua.Class(nil, "ALittle.ControlSystem")

function ALittle.ControlSystem:Ctor(module_name, crypt_mode)
	___rawset(self, "_log_error", true)
	___rawset(self, "_use_plugin_class", true)
	___rawset(self, "_font_map", {})
	___rawset(self, "_child_plugin_map", {})
	___rawset(self, "_parent_plugin_map", {})
	___rawset(self, "_name_map_info", {})
	___rawset(self, "_name_map_info_cache", {})
	___rawset(self, "_module_name", module_name)
	___rawset(self, "_crypt_mode", crypt_mode or false)
	___rawset(self, "_base_path", "Module/" .. module_name .. "/")
	___rawset(self, "_ui_path", self._base_path .. "UI/")
	___rawset(self, "_font_path", self._base_path .. "Font/")
	___rawset(self, "_sound_path", self._base_path .. "Sound/")
	___rawset(self, "_other_path", self._base_path .. "Other/")
	___rawset(self, "_texture_mgr", ALittle.TextureManager(module_name, self._crypt_mode))
	A_LoadTextureManager:RegisterTexmgrControl(self._texture_mgr)
end

function ALittle.ControlSystem.__getter:crypt_mode()
	return self._crypt_mode
end

function ALittle.ControlSystem.__getter:log_error()
	return self._log_error
end

function ALittle.ControlSystem.__setter:log_error(value)
	self._log_error = value
end

function ALittle.ControlSystem.__getter:info_map()
	return self._name_map_info
end

function ALittle.ControlSystem:RegisterFont(src, dst)
	self._font_map[src] = dst
end

function ALittle.ControlSystem:RegisterPlugin(module_name, plugin)
	self._child_plugin_map[module_name] = plugin
	plugin._parent_plugin_map[self._module_name] = self
end

function ALittle.ControlSystem:UnRegisterPlugin(module_name)
	local plugin = self._child_plugin_map[module_name]
	if plugin == nil then
		return
	end
	self._child_plugin_map[module_name] = nil
	plugin._parent_plugin_map[self._module_name] = nil
end

function ALittle.ControlSystem:RegisterInfoByHttp()
	local ___COROUTINE = coroutine.running()
	local path = self._ui_path .. "../JSUI/ui_all_in_one.json"
	ALittle.File_MakeDeepDir(ALittle.File_GetFilePathByPath(path))
	local error = ALittle.HttpDownloadRequest(self._host, self._port, path, path, nil, true)
	if error ~= nil then
		ALittle.Error("ui load failed:" .. error)
		return
	end
	local content, buffer = JavaScript.File_LoadFile(path)
	if buffer == nil then
		ALittle.Error("ui load failed:" .. error)
		return
	end
	content = javascript.UTF8ArrayToString(javascript.Uint8Array(buffer))
	JavaScript.File_DeleteFile(path)
	local jerror, json = Lua.TCall(ALittle.String_JsonDecode, content)
	if jerror ~= nil then
		ALittle.Error("ui json decode failed:" .. jerror)
		return
	end
	for name, value in ___pairs(json) do
		self:RegisterInfo(name, value)
	end
end

function ALittle.ControlSystem:LoadMessageFromFile(T, path)
	local ___COROUTINE = coroutine.running()
	local path_prefix = "Module/" .. self._module_name .. "/"
	local module_path = path
	if ALittle.String_Find(module_path, path_prefix) == 1 then
		path = ALittle.String_Sub(path, ALittle.String_Len(path_prefix) + 1)
	else
		module_path = path_prefix .. path
	end
	local factory = nil
	do
		local lua_factory = carp.CarpMessageReadFactory()
		if not lua_factory:ReadFromStdFile(module_path) then
			return nil
		end
		factory = lua_factory
	end
	local rflct = T
	local invoke_info = ALittle.CreateMessageInfo(rflct.name)
	if invoke_info == nil then
		ALittle.Error("CreateMessageInfo fialed:", module_path)
		return nil
	end
	local data = ALittle.PS_ReadMessage(factory, invoke_info, nil, factory:GetDataSize())
	if data == nil then
		ALittle.Error("PS_ReadMessage fialed:", module_path)
		return nil
	end
	return data
end

function ALittle.ControlSystem:WriteMessageToFile(T, msg, path)
	local path_prefix = "Module/" .. self._module_name .. "/"
	local module_path = path
	if ALittle.String_Find(module_path, path_prefix) == 1 then
		path = ALittle.String_Sub(path, ALittle.String_Len(path_prefix) + 1)
	else
		module_path = path_prefix .. path
	end
	local factory
	factory = carp.CarpMessageWriteFactory()
	if factory == nil then
		return "factory create failed"
	end
	local rflct = T
	local invoke_info = ALittle.CreateMessageInfo(rflct.name)
	if invoke_info == nil then
		return "create message info failed:" .. rflct.name
	end
	ALittle.PS_WriteMessage(factory, invoke_info, nil, msg)
	local result = factory:WriteToStdFile(ALittle.File_BaseFilePath() .. module_path)
	if not result then
		return "WriteToStdFile failed"
	end
	return nil
end

function ALittle.ControlSystem:RegisterInfo(name, info)
	self._name_map_info[name] = info
	self._name_map_info_cache[name] = nil
end

function ALittle.ControlSystem:UnRegisterInfo(name)
	self._name_map_info[name] = nil
	self._name_map_info_cache[name] = nil
end

function ALittle.ControlSystem:ClearAllInfo()
	self._name_map_info = {}
	self._name_map_info_cache = {}
end

function ALittle.ControlSystem:CreateControlObject(info)
	if info.__module ~= nil and info.__module ~= self._module_name then
		local plugin = self._child_plugin_map[info.__module]
		if plugin == nil then
			plugin = self._parent_plugin_map[info.__module]
		end
		if plugin == nil then
			ALittle.Log("unknow module " .. info.__module .. " cur_module:" .. self._module_name)
			return nil
		end
		return plugin:CreateControlObject(info)
	end
	local target_class = info.__target_class
	if self._use_plugin_class and target_class ~= nil then
		local class_func = info.__class_func
		if class_func == nil then
			class_func = _G
			for index, value in ___ipairs(target_class) do
				class_func = class_func[value]
				if class_func == nil then
					break
				end
			end
			info.__class_func = class_func
		end
		if class_func ~= nil then
			return ALittle.NewObject(class_func, self)
		else
			ALittle.Log("unknow target class." .. ALittle.String_Join(target_class, "."))
		end
	end
	local clazz = info.__class
	if clazz == nil then
		ALittle.Log("__class is null")
		return nil
	end
	local class_func = info.__class_func
	if class_func == nil then
		class_func = ALittle[clazz]
		info.__class_func = class_func
	end
	if class_func == nil then
		ALittle.Log("unknow class." .. clazz)
		return nil
	end
	return ALittle.NewObject(class_func, self)
end

function ALittle.ControlSystem:StartChunk(file_path, loop, callback)
	return A_AudioSystem:StartChunk(self._sound_path .. file_path, loop, callback)
end

function ALittle.ControlSystem:StopChunk(channel)
	A_AudioSystem:StopChunk(channel)
end

function ALittle.ControlSystem:SetTexture(object, name)
	self._texture_mgr:SetTexture(object, name)
end

function ALittle.ControlSystem:PrepareTexture(ui_list, callback)
	local name_map = {}
	if ui_list ~= nil then
		for index, ui in ___ipairs(ui_list) do
			self:CollectTextureName(ui, name_map)
		end
	end
	self._texture_mgr:PrepareTexture(name_map, callback)
end

function ALittle.ControlSystem:PrepareCsv(csv_map, callback)
	local new_csv_map = {}
	for file_path, config in ___pairs(csv_map) do
		new_csv_map[self._other_path .. file_path] = config
	end
	A_CsvConfigManager:PrepareCsv(new_csv_map, callback)
end

function ALittle.ControlSystem.__setter:cache_texture(cache)
	self._texture_mgr.cache_texture = cache
end

function ALittle.ControlSystem.__getter:cache_texture()
	return self._texture_mgr.cache_texture
end

function ALittle.ControlSystem.__setter:use_plugin_class(use)
	self._use_plugin_class = use
end

function ALittle.ControlSystem.__getter:use_plugin_class()
	return self._use_plugin_class
end

function ALittle.ControlSystem:SetFont(object, font_path, font_size)
	local dst = self._font_map[font_path]
	if dst == nil then
		dst = font_path
	end
	object.native_show:SetFont(self._font_path .. dst, font_size)
end

function ALittle.ControlSystem:SaveControlToFile(control, file_path, scale)
	if control == nil then
		return false
	end
	if scale == nil then
		scale = 1
	end
	local texture = __CPPAPIRenderTexture()
	local x = control.x
	local y = control.y
	local width = control.width
	local height = control.height
	local visible = control.visible
	local clip = control.clip
	control.native_show:SetX(0)
	control.native_show:SetY(0)
	control.visible = true
	control.clip = false
	local result = texture:Save(file_path, control.native_show, ALittle.Math_Floor(width), ALittle.Math_Floor(height), scale)
	control.native_show:SetX(x)
	control.native_show:SetY(y)
	control.visible = visible
	control.clip = clip
	texture:Clear()
	return result
end

function ALittle.ControlSystem:CreateControlImpl(name, target_logic, parent)
	local info = self:LoadInfo(name)
	if info == nil then
		return nil
	end
	local object = self:CreateControlObject(info)
	if object == nil then
		return nil
	end
	object:Deserialize(info, target_logic, parent)
	return object
end

function ALittle.ControlSystem:CreateControl(name, target_logic, parent)
	local object = self:CreateControlImpl(name, target_logic, parent)
	if object ~= nil then
		return object
	end
	for module_name, plugin in ___pairs(self._child_plugin_map) do
		object = plugin:CreateControlImpl(name, target_logic, parent)
		if object ~= nil then
			return object
		end
	end
	ALittle.Log("can't find control name:" .. name)
	return nil
end

function ALittle.ControlSystem:CollectTextureName(name, map)
	local info = self:LoadInfo(name)
	if info == nil then
		for module_name, plugin in ___pairs(self._child_plugin_map) do
			info = plugin:LoadInfo(name)
			if info ~= nil then
				break
			end
		end
		for module_name, plugin in ___pairs(self._parent_plugin_map) do
			info = plugin:LoadInfo(name)
			if info ~= nil then
				break
			end
		end
	end
	if info == nil then
		ALittle.Log("can't find control name:" .. name)
		return nil
	end
	return self:CollectTextureNameImpl(info, map)
end

function ALittle.ControlSystem:LoadInfo(name)
	if self._name_map_info_cache[name] then
		return self._name_map_info[name]
	end
	local info = self._name_map_info[name]
	if info == nil then
		local json = ALittle.File_ReadJsonFromFile(self._ui_path .. name .. ".json", self._crypt_mode)
		if json == nil then
			return nil
		end
		for key, value in ___pairs(json) do
			self:RegisterInfo(key, value)
		end
	end
	info = self:CreateInfo(self._name_map_info[name])
	self._name_map_info[name] = info
	self._name_map_info_cache[name] = true
	return self._name_map_info[name]
end

function ALittle.ControlSystem:CreateInfo(info)
	if info == nil then
		return nil
	end
	if info.__include ~= nil then
		if info.__module == nil or info.__module == self._module_name then
			return self:LoadInfo(info.__include)
		end
		local plugin = self._child_plugin_map[info.__module]
		if plugin == nil then
			plugin = self._parent_plugin_map[info.__module]
		end
		if plugin ~= nil then
			return plugin:LoadInfo(info.__include)
		end
		return nil
	end
	local extendsv = info.__extends
	if extendsv ~= nil then
		if info.__extends_included ~= true then
			local control = nil
			if info.__module == nil or info.__module == self._module_name then
				control = self:LoadInfo(extendsv)
				if control == nil then
					ALittle.Log("ControlSystem CreateInfo extends Failed, can't find control. extends:" .. extendsv .. " module:" .. self._module_name)
					return nil
				end
			else
				local plugin = self._child_plugin_map[info.__module]
				if plugin == nil then
					plugin = self._parent_plugin_map[info.__module]
				end
				if plugin == nil then
					ALittle.Log("ControlSystem CreateInfo extends Failed, can't find plugin. extends:" .. extendsv .. " module:" .. info.__module)
					return nil
				end
				control = plugin:LoadInfo(extendsv)
				if control == nil then
					ALittle.Log("ControlSystem CreateInfo extends Failed, can't find control. extends:" .. extendsv .. " module:" .. info.__module)
					return nil
				end
			end
			local copy = {}
			for key, value in ___pairs(control) do
				copy[key] = value
			end
			for key, value in ___pairs(info) do
				copy[key] = value
			end
			info = copy
			info.__extends_included = true
			info.__shows_included = nil
			info.__childs_included = nil
			info.__base_attr = nil
			info.__show_attr = nil
		end
	end
	if info.__shows_included ~= true then
		for key, value in ___pairs(info) do
			if __byte(key, 1) ~= 95 and __type(value) == "table" and (value.__include ~= nil or value.__extends ~= nil or value.__class ~= nil) then
				info[key] = self:CreateInfo(value)
			end
		end
		info.__shows_included = true
	end
	local childs = info.__childs
	if childs ~= nil then
		if info.__childs_included ~= true then
			for index, child in ___ipairs(childs) do
				childs[index] = self:CreateInfo(childs[index])
			end
			info.__childs_included = true
		end
	end
	return info
end

function ALittle.ControlSystem:CollectTextureNameImpl(info, map)
	if map == nil then
		map = {}
	end
	local texture_name = info.texture_name
	if texture_name ~= nil and texture_name ~= "" then
		map[texture_name] = true
	end
	local info_t = info
	for key, value in ___pairs(info_t) do
		if __type(value) == "table" and value.__class ~= nil then
			self:CollectTextureNameImpl(value, map)
		end
	end
	local childs = info.__childs
	if childs ~= nil then
		for index, value in ___ipairs(childs) do
			self:CollectTextureNameImpl(value, map)
		end
	end
	return map
end

end