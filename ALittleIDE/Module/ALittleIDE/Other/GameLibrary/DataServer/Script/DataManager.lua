-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DataServer == nil then _G.DataServer = {} end
local DataServer = DataServer
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(1847150134, "ALittle.StructInfo", {
name = "ALittle.StructInfo", ns_name = "ALittle", rl_name = "StructInfo", hash_code = 1847150134,
name_list = {"name","ns_name","rl_name","hash_code","name_list","type_list","option_map"},
type_list = {"string","string","string","int","List<string>","List<string>","Map<string,string>"},
option_map = {}
})
ALittle.RegStruct(1821069430, "ALittle.ProtocolAnyStruct", {
name = "ALittle.ProtocolAnyStruct", ns_name = "ALittle", rl_name = "ProtocolAnyStruct", hash_code = 1821069430,
name_list = {"hash_code","value"},
type_list = {"int","any"},
option_map = {}
})
ALittle.RegStruct(-1546420203, "DataServer.TableReadyInfo", {
name = "DataServer.TableReadyInfo", ns_name = "DataServer", rl_name = "TableReadyInfo", hash_code = -1546420203,
name_list = {"total","ready"},
type_list = {"int","Map<int,bool>"},
option_map = {}
})
ALittle.RegStruct(1463647694, "DataServer.GS2DATA_NBackupStruct", {
name = "DataServer.GS2DATA_NBackupStruct", ns_name = "DataServer", rl_name = "GS2DATA_NBackupStruct", hash_code = 1463647694,
name_list = {"account_id","data"},
type_list = {"int","ALittle.ProtocolAnyStruct"},
option_map = {}
})
ALittle.RegStruct(-1121683527, "DataServer.GS2DATA_QLoadStruct", {
name = "DataServer.GS2DATA_QLoadStruct", ns_name = "DataServer", rl_name = "GS2DATA_QLoadStruct", hash_code = -1121683527,
name_list = {"account_id","hash_code"},
type_list = {"int","int"},
option_map = {}
})
ALittle.RegStruct(-1010453448, "DataServer.GS2DATA_NRegStruct", {
name = "DataServer.GS2DATA_NRegStruct", ns_name = "DataServer", rl_name = "GS2DATA_NRegStruct", hash_code = -1010453448,
name_list = {"rflt_list","table_map"},
type_list = {"List<ALittle.StructInfo>","Map<int,bool>"},
option_map = {}
})

local TABLE_REGISTER_MAP = {}
function DataServer.HandleQRegStruct(common, msg)
	local connect_key = common:GetID()
	local register_map = TABLE_REGISTER_MAP[connect_key]
	if register_map == nil then
		register_map = {}
		TABLE_REGISTER_MAP[connect_key] = register_map
	end
	for index, info in ___ipairs(msg.rflt_list) do
		ALittle.RegStruct(info.hash_code, info.name, info)
	end
	register_map.total = 0
	for key, _ in ___pairs(msg.table_map) do
		register_map.total = register_map.total + 1
	end
	register_map.ready = {}
	for index, info in ___ipairs(msg.rflt_list) do
		if msg.table_map[info.hash_code] ~= nil and register_map.ready[info.hash_code] == nil then
			local error = A_MysqlSystem:CreateIfNotExitByReflect(info, info.rl_name)
			if error ~= nil then
				ALittle.Error(error)
			end
			register_map.ready[info.hash_code] = error == nil
		end
	end
end
DataServer.HandleQRegStruct = Lua.CoWrap(DataServer.HandleQRegStruct)

ALittle.RegMsgCallback(-1010453448, DataServer.HandleQRegStruct)
function DataServer.HandleQLoadStruct(client, msg)
	local ___COROUTINE = coroutine.running()
	local connect_key = client:GetID()
	local register_map = TABLE_REGISTER_MAP[connect_key]
	Lua.Assert(register_map, "表结构尚未注册")
	local info = ALittle.FindStructById(msg.hash_code)
	Lua.Assert(info, "反射信息查找失败")
	local thread_id = carp.JSHash(msg.account_id .. "_" .. info.rl_name)
	local primary = info.option_map["primary"]
	Lua.Assert(primary, "找不到主键:" .. info.rl_name)
	local wait_total = register_map.total
	while register_map.ready[info.hash_code] == nil and wait_total > 0 do
		A_MysqlSystem:ExecuteEmpty()
		wait_total = wait_total - 1
	end
	local error, data = A_MysqlSystem:SelectOneFromByKeyByReflect(info, primary, msg.account_id, thread_id)
	if error ~= nil then
		Lua.Throw("数据加载失败:" .. error)
	end
	if data == nil then
		local map = {}
		map[primary] = msg.account_id
		error = A_MysqlSystem:InsertIntoByReflect(info, map, nil, thread_id)
		if error ~= nil then
			Lua.Throw("数据加载失败:" .. error)
		end
		data = map
	end
	local param = {}
	param.hash_code = info.hash_code
	param.value = data
	return param
end

ALittle.RegMsgRpcCallback(-1121683527, DataServer.HandleQLoadStruct, 1821069430)
function DataServer.HandleNBackupStruct(client, msg)
	local session = client
	if session.route_type ~= 7 then
		return
	end
	if not DataServer.g_LeaseManager:CheckLease(msg.account_id, session.route_num) then
		ALittle.Warn("CheckLease failed! account_id:" .. msg.account_id .. ", route_num:" .. session.route_num .. ", hash_code:" .. msg.data.hash_code)
		return
	end
	local register_map = TABLE_REGISTER_MAP[session:GetID()]
	Lua.Assert(register_map, "表结构尚未注册")
	local info = ALittle.FindStructById(msg.data.hash_code)
	Lua.Assert(info, "反射信息查找失败")
	local thread_id = carp.JSHash(msg.account_id .. "_" .. info.rl_name)
	local primary = info.option_map["primary"]
	Lua.Assert(primary, "找不到主键:" .. info.rl_name)
	local wait_total = register_map.total
	while register_map.ready[info.hash_code] == nil and wait_total > 0 do
		A_MysqlSystem:ExecuteEmpty()
		wait_total = wait_total - 1
	end
	local error = A_MysqlSystem:UpdateOneByReflect(info, msg.data.value, primary, msg.account_id, thread_id)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
end
DataServer.HandleNBackupStruct = Lua.CoWrap(DataServer.HandleNBackupStruct)

ALittle.RegMsgCallback(1463647694, DataServer.HandleNBackupStruct)
end