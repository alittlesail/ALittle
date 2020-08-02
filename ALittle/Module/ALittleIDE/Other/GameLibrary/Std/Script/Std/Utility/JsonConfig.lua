-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.IJsonConfig = Lua.Class(nil, "ALittle.IJsonConfig")

function ALittle.IJsonConfig:GetConfig(key, defaultv)
	return defaultv
end

function ALittle.IJsonConfig:GetBool(key, defaultv)
	return defaultv
end

function ALittle.IJsonConfig:GetInt(key, defaultv)
	return defaultv
end

function ALittle.IJsonConfig:GetDouble(key, defaultv)
	return defaultv
end

function ALittle.IJsonConfig:GetString(key, defaultv)
	return defaultv
end

function ALittle.IJsonConfig:SetConfig(key, value, not_save)
end

function ALittle.IJsonConfig:CoverConfig(msg, save)
end

function ALittle.IJsonConfig:SaveConfig()
end

assert(ALittle.IJsonConfig, " extends class:ALittle.IJsonConfig is nil")
ALittle.JsonConfig = Lua.Class(ALittle.IJsonConfig, "ALittle.JsonConfig")

function ALittle.JsonConfig:Ctor(file_path, print_error)
	___rawset(self, "_file_path", file_path)
	___rawset(self, "_config_map", {})
	local file = self.__class.__element[1]()
	local content = file:Load(self._file_path)
	if content == nil then
		if print_error then
			ALittle.Error("config load failed." .. file_path)
		end
		return
	end
	local error, json_content = Lua.TCall(ALittle.String_JsonDecode, content)
	if error ~= nil then
		ALittle.Log("Json Decode failed." .. file_path .. ", " .. error)
		return
	end
	___rawset(self, "_config_map", json_content)
end

function ALittle.JsonConfig:GetConfig(key, defaultv)
	local value = self._config_map[key]
	if value == nil then
		return defaultv
	end
	return value
end

function ALittle.JsonConfig:GetBool(key, defaultv)
	local value = self:GetConfig(key, defaultv)
	return value ~= nil and value ~= false
end

function ALittle.JsonConfig:GetInt(key, defaultv)
	local value = self:GetConfig(key, defaultv)
	if value == nil then
		value = 0
	end
	return value
end

function ALittle.JsonConfig:GetDouble(key, defaultv)
	local value = self:GetConfig(key, defaultv)
	if value == nil then
		value = 0
	end
	return value
end

function ALittle.JsonConfig:GetString(key, defaultv)
	local value = self:GetConfig(key, defaultv)
	if value == nil then
		value = ""
	end
	return value
end

function ALittle.JsonConfig:SetConfig(key, value, not_save)
	self._config_map[key] = value
	if not not_save then
		self:SaveConfig()
	end
end

function ALittle.JsonConfig:CoverConfig(msg, save)
	for k, v in ___pairs(msg) do
		self._config_map[k] = v
	end
	if not save then
		self:SaveConfig()
	end
end

function ALittle.JsonConfig:SaveConfig()
	local file = self.__class.__element[2]()
	if not file:Save(self._file_path, ALittle.String_JsonEncode(self._config_map)) then
		ALittle.Log("Save Congig Failed.", self._file_path)
	end
end

function ALittle.CreateJsonConfig(file_path, print_error)
	return Lua.Template(ALittle.JsonConfig, "ALittle.JsonConfig<ALittle.LuaFileLoader, ALittle.LuaFileSaver>", ALittle.LuaFileLoader, ALittle.LuaFileSaver)(file_path, print_error)
end

end