-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


local __byte = String_Byte
local __type = String_Type
ControlSystem = Lua.Class(nil, "ALittle.ControlSystem")

function ControlSystem:Ctor(module_name, crypt_mode)
	___rawset(self, "_log_error", true)
	___rawset(self, "_font_map", {})
	___rawset(self, "_name_map_info", {})
	___rawset(self, "_name_map_info_cache", {})
	___rawset(self, "_module_name", module_name)
	___rawset(self, "_crypt_mode", crypt_mode or false)
	___rawset(self, "_base_path", "Module/" .. module_name .. "/")
	___rawset(self, "_ui_path", self._base_path .. "UI/")
	___rawset(self, "_font_path", self._base_path .. "Font/")
	___rawset(self, "_sound_path", self._base_path .. "Sound/")
	___rawset(self, "_other_path", self._base_path .. "Other/")
	___rawset(self, "_texture_mgr", TextureManager(module_name, self._crypt_mode))
	A_LoadTextureManager:RegisterTexmgrControl(self._texture_mgr)
end

function ControlSystem.__getter:crypt_mode()
	return self._crypt_mode
end

function ControlSystem.__getter:log_error()
	return self._log_error
end

function ControlSystem.__setter:log_error(value)
	self._log_error = value
end

function ControlSystem:RegisterFont(src, dst)
	self._font_map[src] = dst
end

function ControlSystem:RegisterInfoByHttp()
	local ___COROUTINE = coroutine.running()
	local path = self._ui_path .. "../ui_all_in_one.json"
	ALittle.File_MakeDeepDir(ALittle.File_GetFilePathByPath(path))
	local error = ALittle.HttpDownloadRequest(self._host, self._port, path, path)
	if error ~= nil then
		ALittle.Error("ui load failed:" .. error)
		return
	end
	local content = JavaScript.File_LoadFile(path)
	if content == nil then
		ALittle.Error("ui load failed:" .. error)
		return
	end
	JavaScript.File_DeleteFile(path)
	local jerror, json = Lua.TCall(ALittle.String_JsonDecode, content)
	if jerror ~= nil then
		ALittle.Error("ui json decode failed:" .. jerror)
		return
	end
	for name, value in ___pairs(json) do
		self:RegisterInfo(name, value)
	end
	for name, value in ___pairs(json) do
		local info = self:CreateInfo(self._name_map_info[name])
		self._name_map_info[name] = info
		self._name_map_info_cache[name] = true
	end
end

function ControlSystem:RegisterInfo(name, info)
	self._name_map_info[name] = info
	self._name_map_info_cache[name] = nil
end

function ControlSystem:UnRegisterInfo(name)
	self._name_map_info[name] = nil
	self._name_map_info_cache[name] = nil
end

function ControlSystem:ClearAllInfo()
	self._name_map_info = {}
	self._name_map_info_cache = {}
end

function ControlSystem:CreateControlObject(info)
	local target_class = info.__target_class
	if target_class ~= nil then
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
			return NewObject(class_func, self)
		else
			Log("unknow target class." .. String_Join(target_class, "."))
		end
	end
	local clazz = info.__class
	if clazz == nil then
		Log("__class is null")
		return nil
	end
	local class_func = info.__class_func
	if class_func == nil then
		class_func = ALittle[clazz]
		info.__class_func = class_func
	end
	if class_func == nil then
		Log("unknow class." .. clazz)
		return nil
	end
	return ALittle.NewObject(class_func, self)
end

function ControlSystem:StartChunk(file_path, loop, callback)
	return A_AudioSystem:StartChunk(self._sound_path .. file_path, loop, callback)
end

function ControlSystem:StopChunk(channel)
	A_AudioSystem:StopChunk(channel)
end

function ControlSystem:StartMusic(file_path, loop)
	return A_AudioSystem:StartMusic(self._sound_path .. file_path, loop)
end

function ControlSystem:StopMusic()
	A_AudioSystem:StopMusic()
end

function ControlSystem:SetTexture(object, name)
	self._texture_mgr:SetTexture(object, name)
end

function ControlSystem:PrepareTexture(ui_list, callback)
	local name_map = {}
	if ui_list ~= nil then
		for index, ui in ___ipairs(ui_list) do
			self:CollectTextureName(ui, name_map)
		end
	end
	self._texture_mgr:PrepareTexture(name_map, callback)
end

function ControlSystem:PrepareCsv(csv_map, callback)
	local new_csv_map = {}
	for file_path, config in ___pairs(csv_map) do
		new_csv_map[self._other_path .. file_path] = config
	end
	A_CsvConfigManager:PrepareCsv(new_csv_map, callback)
end

function ControlSystem.__setter:cache_texture(cache)
	self._texture_mgr.cache_texture = cache
end

function ControlSystem.__getter:cache_texture()
	return self._texture_mgr.cache_texture
end

function ControlSystem:SetFont(object, font_path, font_size)
	local dst = self._font_map[font_path]
	if dst == nil then
		dst = font_path
	end
	object.native_show:SetFont(self._font_path .. dst, font_size)
end

function ControlSystem:SaveControlToFile(control, file_path, scale)
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
	local result = texture:Save(file_path, control.native_show, Math_Floor(width), Math_Floor(height), scale)
	control.native_show:SetX(x)
	control.native_show:SetY(y)
	control.visible = visible
	control.clip = clip
	texture:Clear()
	return result
end

function ControlSystem:CreateControl(name, target_logic, parent)
	local info = self:LoadInfo(name)
	if info == nil then
		Log("can't find control name:" .. name)
		return nil
	end
	local object = self:CreateControlObject(info)
	if object == nil then
		return nil
	end
	object:Deserialize(info, target_logic, parent)
	return object
end

function ControlSystem:CollectTextureName(name, map)
	local info = self:LoadInfo(name)
	if info == nil then
		Log("can't find control name:" .. name)
		return nil
	end
	return self:CollectTextureNameImpl(info, map)
end

function ControlSystem:LoadInfo(name)
	if self._name_map_info_cache[name] then
		return self._name_map_info[name]
	end
	local info = self._name_map_info[name]
	if info == nil then
		local json = File_ReadJsonFromFile(self._ui_path .. name .. ".json", self._crypt_mode)
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

function ControlSystem:CreateInfo(info)
	if info == nil then
		return nil
	end
	if info.__include ~= nil then
		return self:LoadInfo(info.__include)
	end
	local extendsv = info.__extends
	if extendsv ~= nil then
		if info.__extends_included ~= true then
			local control = self:LoadInfo(extendsv)
			if control == nil then
				Log("ControlSystem CreateInfo extends Failed:" .. extendsv)
				return nil
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

function ControlSystem:CollectTextureNameImpl(info, map)
	if map == nil then
		map = {}
	end
	local class_func = nil
	local target_class = info.__target_class
	if target_class ~= nil then
		class_func = _G
		for index, value in ___ipairs(target_class) do
			class_func = class_func[value]
			if class_func == nil then
				break
			end
		end
		if class_func == nil then
			Log("unknow target class." .. String_Join(target_class, "."))
		end
	end
	if class_func == nil then
		class_func = ALittle[info.__class]
	end
	if class_func == nil then
		Log("unknow class." .. info.__class)
		return map
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

