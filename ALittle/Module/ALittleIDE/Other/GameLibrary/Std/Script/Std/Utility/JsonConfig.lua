-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


IJsonConfig = Lua.Class(nil, "ALittle.IJsonConfig")

function IJsonConfig:GetConfig(key, defaultv)
	return defaultv
end

function IJsonConfig:GetBool(key, defaultv)
	return defaultv
end

function IJsonConfig:GetInt(key, defaultv)
	return defaultv
end

function IJsonConfig:GetDouble(key, defaultv)
	return defaultv
end

function IJsonConfig:GetString(key, defaultv)
	return defaultv
end

function IJsonConfig:SetConfig(key, value, not_save)
end

function IJsonConfig:CoverConfig(msg, save)
end

function IJsonConfig:SaveConfig()
end

assert(ALittle.IJsonConfig, " extends class:ALittle.IJsonConfig is nil")
JsonConfig = Lua.Class(ALittle.IJsonConfig, "ALittle.JsonConfig")

function JsonConfig:Ctor(file_path, print_error)
	___rawset(self, "_file_path", file_path)
	___rawset(self, "_config_map", {})
	local file = self.__class.__element[1]()
	local content = file:Load(self._file_path)
	if content == nil then
		if print_error then
			Error("config load failed." .. file_path)
		end
		return
	end
	local error, json_content = Lua.TCall(String_JsonDecode, content)
	if error ~= nil then
		Log("Json Decode failed." .. file_path .. ", " .. error)
		return
	end
	___rawset(self, "_config_map", json_content)
end

function JsonConfig:GetConfig(key, defaultv)
	local value = self._config_map[key]
	if value == nil then
		return defaultv
	end
	return value
end

function JsonConfig:GetBool(key, defaultv)
	local value = self:GetConfig(key, defaultv)
	return value ~= nil and value ~= false
end

function JsonConfig:GetInt(key, defaultv)
	local value = self:GetConfig(key, defaultv)
	if value == nil then
		value = 0
	end
	return value
end

function JsonConfig:GetDouble(key, defaultv)
	local value = self:GetConfig(key, defaultv)
	if value == nil then
		value = 0
	end
	return value
end

function JsonConfig:GetString(key, defaultv)
	local value = self:GetConfig(key, defaultv)
	if value == nil then
		value = ""
	end
	return value
end

function JsonConfig:SetConfig(key, value, not_save)
	self._config_map[key] = value
	if not not_save then
		self:SaveConfig()
	end
end

function JsonConfig:CoverConfig(msg, save)
	for k, v in ___pairs(msg) do
		self._config_map[k] = v
	end
	if not save then
		self:SaveConfig()
	end
end

function JsonConfig:SaveConfig()
	local file = self.__class.__element[2]()
	if not file:Save(self._file_path, String_JsonEncode(self._config_map)) then
		Log("Save Congig Failed.", self._file_path)
	end
end

function CreateJsonConfig(file_path, print_error)
	return Lua.Template(JsonConfig, "ALittle.JsonConfig<ALittle.LuaFileLoader, ALittle.LuaFileSaver>", LuaFileLoader, LuaFileSaver)(file_path, print_error)
end

