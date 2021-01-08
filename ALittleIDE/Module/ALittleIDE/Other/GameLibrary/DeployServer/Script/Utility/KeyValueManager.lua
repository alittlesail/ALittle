-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleDeploy == nil then _G.ALittleDeploy = {} end
local ALittleDeploy = ALittleDeploy
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-761159939, "ALittleDeploy.TextContent", {
name = "ALittleDeploy.TextContent", ns_name = "ALittleDeploy", rl_name = "TextContent", hash_code = -761159939,
name_list = {"text"},
type_list = {"string"},
option_map = {}
})
ALittle.RegStruct(274010638, "ALittleDeploy.KeyValueInfo", {
name = "ALittleDeploy.KeyValueInfo", ns_name = "ALittleDeploy", rl_name = "KeyValueInfo", hash_code = 274010638,
name_list = {"key","value"},
type_list = {"string","ALittleDeploy.TextContent"},
option_map = {primary="key"}
})

ALittleDeploy.KeyValueManager = Lua.Class(nil, "ALittleDeploy.KeyValueManager")

function ALittleDeploy.KeyValueManager:Ctor()
	___rawset(self, "_map", {})
end

function ALittleDeploy.KeyValueManager:Setup()
	local ___COROUTINE = coroutine.running()
	local error = A_MysqlSystem:CreateIfNotExit(___all_struct[274010638])
	Lua.Assert(error == nil, error)
	local list
	error, list = A_MysqlSystem:SelectListFromByMap(___all_struct[274010638], {})
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

function ALittleDeploy.KeyValueManager:SetConfig(key, value)
	self._map[key] = value
	local info = {}
	info.key = key
	info.value = {}
	info.value.text = ajson.encode(value)
	local error = A_MysqlSystem:UpdateOne(___all_struct[274010638], info, "key", key)
	if error ~= nil then
		ALittle.Error(error)
	end
end
ALittleDeploy.KeyValueManager.SetConfig = Lua.CoWrap(ALittleDeploy.KeyValueManager.SetConfig)

function ALittleDeploy.KeyValueManager:GetConfig(T, key, default)
	local value = self._map[key]
	if value ~= nil then
		return value
	end
	return default
end

function ALittleDeploy.KeyValueManager:Shutdown()
end

_G.g_KeyValueManager = ALittleDeploy.KeyValueManager()
ALittleDeploy.KeyValueType = {
	SETTING = "setting",
}

end