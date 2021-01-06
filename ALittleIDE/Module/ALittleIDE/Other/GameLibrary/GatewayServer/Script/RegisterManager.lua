-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.GatewayServer == nil then _G.GatewayServer = {} end
local GatewayServer = GatewayServer
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-2105123691, "GatewayServer.ARegister", {
name = "GatewayServer.ARegister", ns_name = "GatewayServer", rl_name = "ARegister", hash_code = -2105123691,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-2061561503, "GatewayServer.QChangePwd", {
name = "GatewayServer.QChangePwd", ns_name = "GatewayServer", rl_name = "QChangePwd", hash_code = -2061561503,
name_list = {"account_id","old_pwd","new_pwd"},
type_list = {"int","string","string"},
option_map = {}
})
ALittle.RegStruct(1693893532, "GatewayServer.QNormalRegister", {
name = "GatewayServer.QNormalRegister", ns_name = "GatewayServer", rl_name = "QNormalRegister", hash_code = 1693893532,
name_list = {"account_name","account_pwd","p_user_id"},
type_list = {"string","string","string"},
option_map = {}
})
ALittle.RegStruct(-1343408203, "DataServer.GW2DATA_QLogin", {
name = "DataServer.GW2DATA_QLogin", ns_name = "DataServer", rl_name = "GW2DATA_QLogin", hash_code = -1343408203,
name_list = {"account_id"},
type_list = {"int"},
option_map = {}
})
ALittle.RegStruct(-1289005117, "GatewayServer.QForgotPwd", {
name = "GatewayServer.QForgotPwd", ns_name = "GatewayServer", rl_name = "QForgotPwd", hash_code = -1289005117,
name_list = {"phone_number","phone_code","new_pwd"},
type_list = {"string","string","string"},
option_map = {}
})
ALittle.RegStruct(1231533201, "GatewayServer.C2GW_QLogin", {
name = "GatewayServer.C2GW_QLogin", ns_name = "GatewayServer", rl_name = "C2GW_QLogin", hash_code = 1231533201,
name_list = {"device_id","account_name","account_pwd"},
type_list = {"string","string","string"},
option_map = {}
})
ALittle.RegStruct(1066813511, "GatewayServer.QPhoneRegister", {
name = "GatewayServer.QPhoneRegister", ns_name = "GatewayServer", rl_name = "QPhoneRegister", hash_code = 1066813511,
name_list = {"phone_number","phone_pwd","phone_code","p_user_id"},
type_list = {"string","string","string","string"},
option_map = {}
})
ALittle.RegStruct(945940302, "GatewayServer.QBindPhone", {
name = "GatewayServer.QBindPhone", ns_name = "GatewayServer", rl_name = "QBindPhone", hash_code = 945940302,
name_list = {"account_id","phone_number","phone_code"},
type_list = {"int","string","string"},
option_map = {}
})
ALittle.RegStruct(-937945851, "DataServer.GW2DATA_ALogin", {
name = "DataServer.GW2DATA_ALogin", ns_name = "DataServer", rl_name = "GW2DATA_ALogin", hash_code = -937945851,
name_list = {"client_ip","client_port","session_id"},
type_list = {"string","int","string"},
option_map = {}
})
ALittle.RegStruct(-729612372, "GatewayServer.ABindPhone", {
name = "GatewayServer.ABindPhone", ns_name = "GatewayServer", rl_name = "ABindPhone", hash_code = -729612372,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-147839140, "GatewayServer.AForgotPwd", {
name = "GatewayServer.AForgotPwd", ns_name = "GatewayServer", rl_name = "AForgotPwd", hash_code = -147839140,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(90250184, "GatewayServer.RegisterInfo", {
name = "GatewayServer.RegisterInfo", ns_name = "GatewayServer", rl_name = "RegisterInfo", hash_code = 90250184,
name_list = {"account_id","user_id","p_account_id","phone_number","device_id","account_name","account_pwd","create_time"},
type_list = {"int","string","int","string","string","string","string","int"},
option_map = {primary="account_id",index="user_id,phone_number,device_id,account_name"}
})
ALittle.RegStruct(39013007, "GatewayServer.GW2C_ALogin", {
name = "GatewayServer.GW2C_ALogin", ns_name = "GatewayServer", rl_name = "GW2C_ALogin", hash_code = 39013007,
name_list = {"client_ip","client_port","account_id","session_id"},
type_list = {"string","int","int","string"},
option_map = {}
})
ALittle.RegStruct(38167126, "GatewayServer.AChangePwd", {
name = "GatewayServer.AChangePwd", ns_name = "GatewayServer", rl_name = "AChangePwd", hash_code = 38167126,
name_list = {},
type_list = {},
option_map = {}
})

GatewayServer.RegisterManager = Lua.Class(nil, "GatewayServer.RegisterManager")

function GatewayServer.RegisterManager:Ctor()
end

function GatewayServer.RegisterManager:Setup()
	local ___COROUTINE = coroutine.running()
	local error = A_MysqlSystem:CreateIfNotExit(___all_struct[90250184])
	Lua.Assert(error == nil, error)
end

function GatewayServer.RegisterManager:Shutdown()
end

function GatewayServer.RegisterManager:GenerateUserId()
	local ___COROUTINE = coroutine.running()
	local i = 6
	while true do
		if not(i <= 8) then break end
		local k = 1
		while true do
			if not(k <= 100) then break end
			local min = math.pow(10, i - 1)
			local max = math.pow(10, i) - 1
			local user_id = tostring(math.random(min, max))
			local error, count = A_MysqlSystem:SelectCount(___all_struct[90250184], "user_id", user_id)
			if error ~= nil then
				return nil
			end
			if count <= 0 then
				return user_id
			end
			k = k+(1)
		end
		i = i+(1)
	end
	return nil
end

function GatewayServer.RegisterManager:GenerateAccountId(data_route_num)
	local ___COROUTINE = coroutine.running()
	local max_id = ALittle.MAX_ACCOUNT_ID_BY_DATA_ROUTE_NUM(data_route_num)
	local min_id = ALittle.MIN_ACCOUNT_ID_BY_DATA_ROUTE_NUM(data_route_num)
	local i = 1
	while true do
		if not(i <= 100) then break end
		local account_id = math.random(min_id, max_id)
		local error, count = A_MysqlSystem:SelectCount(___all_struct[90250184], "account_id", account_id)
		if error ~= nil then
			return nil
		end
		if count <= 0 then
			return account_id
		end
		i = i+(1)
	end
	return nil
end

GatewayServer.g_RegisterManager = GatewayServer.RegisterManager()
function GatewayServer.HandleQNormalRegister(client, msg)
	local ___COROUTINE = coroutine.running()
	Lua.Assert(msg.account_name ~= nil and msg.account_name ~= "", "账号名不能为空")
	Lua.Assert(msg.account_pwd ~= nil and msg.account_pwd ~= "", "密码不能为空")
	Lua.Assert(ALittle.String_IsPhoneNumber(msg.account_name), "账号名，不能是手机号码")
	local error, count = A_MysqlSystem:SelectCount(___all_struct[90250184], "account_name", msg.account_name)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	Lua.Assert(count == 0, "账号名已被注册")
	local data_route_info = GatewayServer.g_DataRouteManager:GetRouteInfo()
	Lua.Assert(data_route_info ~= nil, "没有数据代理服务器可以选择")
	local p_info = nil
	if msg.p_user_id ~= nil and msg.p_user_id ~= "" then
		error, p_info = A_MysqlSystem:SelectOneFromByKey(___all_struct[90250184], "user_id", msg.p_user_id)
		if error ~= nil then
			Lua.Throw("数据库操作失败" .. error)
		end
	end
	local user_id = GatewayServer.g_RegisterManager:GenerateUserId()
	Lua.Assert(user_id ~= nil, "编号生成失败")
	local next_id = GatewayServer.g_RegisterManager:GenerateAccountId(data_route_info.route_num)
	Lua.Assert(next_id ~= nil, "账号ID生成失败")
	local info = {}
	info.account_id = next_id
	info.user_id = user_id
	info.p_account_id = 0
	if p_info ~= nil then
		info.p_account_id = p_info.account_id
	end
	info.phone_number = ""
	info.device_id = ""
	info.account_name = msg.account_name
	info.account_pwd = ALittle.String_Md5("ALittle" .. msg.account_pwd .. "ALittle")
	info.create_time = os.time()
	error = A_MysqlSystem:InsertInto(___all_struct[90250184], info)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	return {}
end

ALittle.RegMsgRpcCallback(1693893532, GatewayServer.HandleQNormalRegister, -2105123691)
function GatewayServer.HandleQPhoneRegister(client, msg)
	local ___COROUTINE = coroutine.running()
	Lua.Assert(msg.phone_number ~= nil and msg.phone_number ~= "", "手机号码不能为空")
	Lua.Assert(msg.phone_pwd ~= nil and msg.phone_pwd ~= "", "密码不能为空")
	local error, count = A_MysqlSystem:SelectCount(___all_struct[90250184], "phone_number", msg.phone_number)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	Lua.Assert(count == 0, "手机号码已被注册")
	error = GatewayServer.g_PhoneCodeManager:CheckPhoneCode(msg.phone_number, msg.phone_code)
	Lua.Assert(error == nil, error)
	local dp_route_info = GatewayServer.g_DataRouteManager:GetRouteInfo()
	Lua.Assert(dp_route_info ~= nil, "没有数据代理服务器可以选择")
	local user_id = GatewayServer.g_RegisterManager:GenerateUserId()
	Lua.Assert(user_id ~= nil, "编号生成失败")
	local next_id = GatewayServer.g_RegisterManager:GenerateAccountId(dp_route_info.route_num)
	Lua.Assert(next_id ~= nil, "账号ID生成失败")
	local p_info = nil
	if msg.p_user_id ~= nil and msg.p_user_id ~= "" then
		error, p_info = A_MysqlSystem:SelectOneFromByKey(___all_struct[90250184], "user_id", msg.p_user_id)
		if error ~= nil then
			Lua.Throw("数据库操作失败:" .. error)
		end
	end
	local info = {}
	info.account_id = next_id
	info.user_id = user_id
	info.p_account_id = p_info.account_id
	info.phone_number = msg.phone_number
	info.device_id = ""
	info.account_name = ""
	info.account_pwd = ALittle.String_Md5("ALittle" .. msg.phone_pwd .. "ALittle")
	info.create_time = os.time()
	error = A_MysqlSystem:InsertInto(___all_struct[90250184], info)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	GatewayServer.g_PhoneCodeManager:RemovePhoneCode(msg.phone_number)
	return {}
end

ALittle.RegMsgRpcCallback(1066813511, GatewayServer.HandleQPhoneRegister, -2105123691)
function GatewayServer.HandleQBindPhone(client, msg)
	local ___COROUTINE = coroutine.running()
	Lua.Assert(msg.phone_number ~= nil and msg.phone_number ~= "", "手机号码不能为空")
	local error, info = A_MysqlSystem:SelectOneFromByKey(___all_struct[90250184], "phone_number", msg.phone_number)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	Lua.Assert(info, "手机号码已被其他账号注册，不能绑定")
	error, info = A_MysqlSystem:SelectOneFromByKey(___all_struct[90250184], "account_id", msg.account_id)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	Lua.Assert(info, "要绑定的账号不存在")
	error = GatewayServer.g_PhoneCodeManager:CheckPhoneCode(msg.phone_number, msg.phone_code)
	if error ~= nil then
		Lua.Throw(error)
	end
	error = A_MysqlSystem:UpdateSet(___all_struct[90250184], "phone_number", msg.phone_number, "account_id", msg.account_id)
	if error ~= nil then
		Lua.Throw("绑定失败:" .. error)
	end
	GatewayServer.g_PhoneCodeManager:RemovePhoneCode(msg.phone_number)
	return {}
end

ALittle.RegMsgRpcCallback(945940302, GatewayServer.HandleQBindPhone, -729612372)
function GatewayServer.HandleQLogin(client, msg)
	local ___COROUTINE = coroutine.running()
	local info = nil
	if msg.device_id ~= nil and msg.device_id ~= "" then
		local error = nil
		error, info = A_MysqlSystem:SelectOneFromByKey(___all_struct[90250184], "device_id", msg.device_id)
		if info == nil then
			local data_route_info = GatewayServer.g_DataRouteManager:GetRouteInfo()
			Lua.Assert(data_route_info ~= nil, "没有数据代理服务器可以选择")
			local user_id = GatewayServer.g_RegisterManager:GenerateUserId()
			Lua.Assert(user_id ~= nil, "编号生成失败")
			local next_id = GatewayServer.g_RegisterManager:GenerateAccountId(data_route_info.route_num)
			Lua.Assert(next_id ~= nil, "账号ID生成失败")
			info = {}
			info.account_id = next_id
			info.user_id = user_id
			info.phone_number = ""
			info.account_name = ""
			info.account_pwd = ""
			info.create_time = os.time()
			info.device_id = msg.device_id
			error = A_MysqlSystem:InsertInto(___all_struct[90250184], info)
			if error ~= nil then
				Lua.Throw("数据库操作失败:" .. error)
			end
		end
	else
		Lua.Assert(msg.account_name ~= nil and msg.account_name ~= "", "账号名不能为空")
		Lua.Assert(msg.account_pwd ~= nil and msg.account_pwd ~= "", "密码不能为空")
		local error = nil
		error, info = A_MysqlSystem:SelectOneFromByKey(___all_struct[90250184], "account_name", msg.account_name)
		if error ~= nil then
			Lua.Throw("数据库操作失败:" .. error)
		end
		if info == nil then
			error, info = A_MysqlSystem:SelectOneFromByKey(___all_struct[90250184], "phone_number", msg.account_name)
			if error ~= nil then
				Lua.Throw("数据库操作失败:" .. error)
			end
			Lua.Assert(info ~= nil, "账号或密码错误")
		end
		Lua.Assert(info.account_pwd == ALittle.String_Md5("ALittle" .. msg.account_pwd .. "ALittle"), "账号或密码错误")
	end
	local data_route_num = ALittle.GET_DATA_ROUTE_NUM_BY_ACCOUNT_ID(info.account_id)
	local data_route_info = GatewayServer.g_DataRouteManager:FindRouteInfo(data_route_num)
	Lua.Assert(data_route_info, "没有找到DataServer的路由信息")
	local param = {}
	param.account_id = info.account_id
	local error, result = ALittle.IMsgCommon.InvokeRPC(-1343408203, data_route_info.session, param)
	if error ~= nil then
		Lua.Throw("error")
	end
	local anwser = {}
	anwser.account_id = info.account_id
	anwser.client_ip = result.client_ip
	anwser.client_port = result.client_port
	anwser.session_id = result.session_id
	return anwser
end

ALittle.RegHttpCallback("GatewayServer.C2GW_QLogin", GatewayServer.HandleQLogin)
function GatewayServer.HandleQChangePwd(client, msg)
	local ___COROUTINE = coroutine.running()
	local error, info = A_MysqlSystem:SelectOneFromByKey(___all_struct[90250184], "account_id", msg.account_id)
	if error ~= nil then
		Lua.Throw("密码修改失败:" .. error)
	end
	Lua.Assert(info ~= nil, "账号不存在")
	Lua.Assert(info.account_pwd ~= nil and info.account_pwd == ALittle.String_Md5("ALittle" .. msg.old_pwd .. "ALittle"), "原密码不正确")
	local account_pwd_md5 = ALittle.String_Md5("ALittle" .. msg.new_pwd .. "ALittle")
	error = A_MysqlSystem:UpdateSet(___all_struct[90250184], "account_pwd", account_pwd_md5, "account_id", info.account_id)
	if error ~= nil then
		Lua.Throw("密码修改失败:" .. error)
	end
	return {}
end

ALittle.RegMsgRpcCallback(-2061561503, GatewayServer.HandleQChangePwd, 38167126)
function GatewayServer.HandleQForgotPwd(client, msg)
	local ___COROUTINE = coroutine.running()
	Lua.Assert(msg.phone_number ~= nil and msg.phone_number ~= "", "手机号码不能为空")
	local error, info = A_MysqlSystem:SelectOneFromByKey(___all_struct[90250184], "phone_number", msg.phone_number)
	if error ~= nil then
		Lua.Throw("数据库操作失败:" .. error)
	end
	Lua.Assert(info, "手机号码不存在")
	error = GatewayServer.g_PhoneCodeManager:CheckPhoneCode(msg.phone_number, msg.phone_code)
	if error ~= nil then
		Lua.Throw(error)
	end
	local new_pwd_md5 = ALittle.String_Md5("ALittle" .. msg.new_pwd .. "ALittle")
	error = A_MysqlSystem:UpdateSet(___all_struct[90250184], "account_pwd", new_pwd_md5, "phone_number", msg.phone_number)
	if error ~= nil then
		Lua.Throw("修改失败:" .. error)
	end
	GatewayServer.g_PhoneCodeManager:RemovePhoneCode(msg.phone_number)
	return {}
end

ALittle.RegMsgRpcCallback(-1289005117, GatewayServer.HandleQForgotPwd, -147839140)
end