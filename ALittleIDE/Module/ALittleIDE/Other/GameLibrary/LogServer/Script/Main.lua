-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.LogServer == nil then _G.LogServer = {} end
local LogServer = LogServer
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(976782632, "LogServer.LogEventInfo", {
name = "LogServer.LogEventInfo", ns_name = "LogServer", rl_name = "LogEventInfo", hash_code = 976782632,
name_list = {"account_id","main_type","sub_type","res_type","res_id","res_num","res_count","param_1","param_2","param_3","param_4","param_5","param_string","create_time","log_time"},
type_list = {"int","int","int","int","int","int","int","int","int","int","int","int","string","int","int"},
option_map = {index="account_id,main_type,sub_type,create_time"}
})
ALittle.RegStruct(200159280, "LogServer.EmptyResult", {
name = "LogServer.EmptyResult", ns_name = "LogServer", rl_name = "EmptyResult", hash_code = 200159280,
name_list = {},
type_list = {},
option_map = {}
})

LogServer.g_ConfigSystem = nil
function LogServer.__Module_Setup(sengine_path, module_path, config_path)
	math.randomseed(os.time(nil))
	LogServer.g_ConfigSystem = ALittle.CreateJsonConfig(config_path, true)
	local wan_ip = LogServer.g_ConfigSystem:GetConfig("wan_ip", "127.0.0.1")
	local yun_ip = LogServer.g_ConfigSystem:GetConfig("yun_ip", "")
	local port_offset = LogServer.g_ConfigSystem:GetConfig("port_offset", 0)
	__CPPAPI_ServerSchedule:StartMysqlQuery(1, LogServer.g_ConfigSystem:GetString("main_conn_ip", nil), LogServer.g_ConfigSystem:GetString("main_conn_username", nil), LogServer.g_ConfigSystem:GetString("main_conn_password", nil), LogServer.g_ConfigSystem:GetInt("main_conn_port", nil), LogServer.g_ConfigSystem:GetString("main_conn_dbname", nil))
	__CPPAPI_ServerSchedule:StartRouteSystem(5, 1)
	__CPPAPI_ServerSchedule:CreateConnectServer(yun_ip, wan_ip, 1300 + port_offset)
end
LogServer.__Module_Setup = Lua.CoWrap(LogServer.__Module_Setup)

function LogServer.__Module_Shutdown()
end

local g_CurDate = ""
function LogServer.HandleLogEventInfo(client, msg)
	local ___COROUTINE = coroutine.running()
	msg.log_time = os.time(nil)
	local cur_date = os.date("%Y_%m_%d", msg.create_time)
	local info = ___all_struct[976782632]
	local table_name = info.rl_name .. "_" .. cur_date
	if g_CurDate ~= cur_date then
		local error = A_MysqlSystem:CreateIfNotExit(___all_struct[976782632], table_name)
		if error ~= nil then
			Lua.Throw("日志表创建失败:" .. table_name)
		end
		g_CurDate = cur_date
	end
	local error = A_MysqlSystem:InsertInto(___all_struct[976782632], msg, table_name)
	if error ~= nil then
		Lua.Throw("数据插入失败:" .. error)
	end
	return {}
end

ALittle.RegMsgRpcCallback(976782632, LogServer.HandleLogEventInfo, 200159280)
end