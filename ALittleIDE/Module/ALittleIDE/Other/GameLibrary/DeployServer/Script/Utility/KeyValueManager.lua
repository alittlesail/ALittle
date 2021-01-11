-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DeployServer == nil then _G.DeployServer = {} end
local DeployServer = DeployServer
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1947700139, "DeployServer.KeyValueInfo", {
name = "DeployServer.KeyValueInfo", ns_name = "DeployServer", rl_name = "KeyValueInfo", hash_code = -1947700139,
name_list = {"key","value"},
type_list = {"string","DeployServer.TextContent"},
option_map = {primary="key"}
})
ALittle.RegStruct(1001867448, "DeployServer.TextContent", {
name = "DeployServer.TextContent", ns_name = "DeployServer", rl_name = "TextContent", hash_code = 1001867448,
name_list = {"text"},
type_list = {"string"},
option_map = {}
})

DeployServer.KeyValueManager = Lua.Class(nil, "DeployServer.KeyValueManager")

function DeployServer.KeyValueManager:Ctor()
	___rawset(self, "_map", {})
end

function DeployServer.KeyValueManager:Setup()
	local ___COROUTINE = coroutine.running()
	local error = A_MysqlSystem:CreateIfNotExit(___all_struct[-1947700139])
	Lua.Assert(error == nil, error)
	local list
	error, list = A_MysqlSystem:SelectListFromByMap(___all_struct[-1947700139], {})
	Lua.Assert(error == nil, error)
	for index, info in ___ipairs(list) do
		local succeed = false
		if info.value ~= nil and info.value.text ~= nil then
			local result, object = pcall(ajson.decode, info.value.text)
			if result then
				self._map[info.key] = object
				succeed = true
			end
		end
		if not succeed then
			self._map[info.key] = {}
		end
	end
end

function DeployServer.KeyValueManager:SetConfig(key, value)
	self._map[key] = value
	local info = {}
	info.key = key
	info.value = {}
	info.value.text = ajson.encode(value)
	local error = A_MysqlSystem:UpdateOne(___all_struct[-1947700139], info, "key", key)
	if error ~= nil then
		ALittle.Error(error)
	end
end
DeployServer.KeyValueManager.SetConfig = Lua.CoWrap(DeployServer.KeyValueManager.SetConfig)

function DeployServer.KeyValueManager:GetConfig(T, key, default)
	local value = self._map[key]
	if value ~= nil then
		return value
	end
	return default
end

function DeployServer.KeyValueManager:Shutdown()
end

_G.g_KeyValueManager = DeployServer.KeyValueManager()
DeployServer.KeyValueType = {
	SETTING = "setting",
}

end