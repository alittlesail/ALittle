-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.GatewayServer == nil then _G.GatewayServer = {} end
local GatewayServer = GatewayServer
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1926215703, "GatewayServer.PhoneCodeSendParam", {
name = "GatewayServer.PhoneCodeSendParam", ns_name = "GatewayServer", rl_name = "PhoneCodeSendParam", hash_code = 1926215703,
name_list = {"sid","token","appid","templateid","param","mobile"},
type_list = {"string","string","string","string","string","string"},
option_map = {}
})
ALittle.RegStruct(-1727159013, "GatewayServer.CodeInfo", {
name = "GatewayServer.CodeInfo", ns_name = "GatewayServer", rl_name = "CodeInfo", hash_code = -1727159013,
name_list = {"begin_time","end_time","code","count"},
type_list = {"int","int","string","int"},
option_map = {}
})
ALittle.RegStruct(-801052492, "GatewayServer.QPhoneCode", {
name = "GatewayServer.QPhoneCode", ns_name = "GatewayServer", rl_name = "QPhoneCode", hash_code = -801052492,
name_list = {"phone_number","request_type"},
type_list = {"string","int"},
option_map = {}
})
ALittle.RegStruct(-795717731, "GatewayServer.PhoneCodeSendResult", {
name = "GatewayServer.PhoneCodeSendResult", ns_name = "GatewayServer", rl_name = "PhoneCodeSendResult", hash_code = -795717731,
name_list = {"code","msg"},
type_list = {"string","string"},
option_map = {}
})
ALittle.RegStruct(702085384, "GatewayServer.PhoneCodeCfg", {
name = "GatewayServer.PhoneCodeCfg", ns_name = "GatewayServer", rl_name = "PhoneCodeCfg", hash_code = 702085384,
name_list = {"url","sid","token","appid","templateid"},
type_list = {"string","string","string","string","string"},
option_map = {}
})
ALittle.RegStruct(-247110298, "GatewayServer.APhoneCode", {
name = "GatewayServer.APhoneCode", ns_name = "GatewayServer", rl_name = "APhoneCode", hash_code = -247110298,
name_list = {},
type_list = {},
option_map = {}
})

GatewayServer.PhoneCodeManager = Lua.Class(nil, "GatewayServer.PhoneCodeManager")

function GatewayServer.PhoneCodeManager:Ctor()
	___rawset(self, "_phone_code_map", {})
end

function GatewayServer.PhoneCodeManager:Setup()
	self._phone_code_cfg = GatewayServer.g_ConfigSystem:GetConfig("phone_code_cfg", {})
	local delay_time = ALittle.GetNextTodayBeginTime() - os.time()
	self._timer = A_LoopSystem:AddTimer(delay_time * 1000, Lua.Bind(self.HandleNewDay, self))
end

function GatewayServer.PhoneCodeManager:Shutdown()
	if self._timer ~= nil then
		A_LoopSystem:RemoveTimer(self._timer)
		self._timer = nil
	end
end

function GatewayServer.PhoneCodeManager:HandleNewDay()
	local cur_time = os.time()
	ALittle.Log("PhoneCodeManager:HandleNewDay:" .. os.date("%Y-%m-%d %H:%M:%S", cur_time))
	local remove_list = {}
	for key, info in ___pairs(self._phone_code_map) do
		if info.end_time > cur_time then
			info.count = 0
		else
			ALittle.List_Push(remove_list, key)
		end
	end
	for index, key in ___ipairs(remove_list) do
		self._phone_code_map[key] = nil
	end
	local delay_time = ALittle.GetNextTodayBeginTime() - os.time()
	self._timer = A_LoopSystem:AddTimer(delay_time * 1000, Lua.Bind(self.HandleNewDay, self))
end

function GatewayServer.PhoneCodeManager:CheckPhoneCode(phone_number, phone_code)
	local info = self._phone_code_map[phone_number]
	if info == nil then
		return "无效验证码"
	end
	if info.end_time > os.time(nil) then
		return "您的验证码已过期"
	end
	if info.code ~= phone_code then
		return "您的验证码不正确"
	end
	return nil
end

function GatewayServer.PhoneCodeManager:RemovePhoneCode(phone_number)
	self._phone_code_map[phone_number] = nil
end

function GatewayServer.PhoneCodeManager:AddPhoneCode(phone_number, phone_code)
	local info = self._phone_code_map[phone_number]
	if info ~= nil then
		info.count = info.count + 1
		info.code = phone_code
		info.begin_time = os.time()
		info.end_time = info.begin_time + 300
	else
		info = {}
		info.count = 1
		info.code = phone_code
		info.begin_time = os.time()
		info.end_time = info.begin_time + 300
		self._phone_code_map[phone_number] = info
	end
end

function GatewayServer.PhoneCodeManager:GetPhoneCode(phone_number)
	return self._phone_code_map[phone_number]
end

function GatewayServer.PhoneCodeManager:GetPhoneCodeCfg()
	return self._phone_code_cfg
end

GatewayServer.g_PhoneCodeManager = GatewayServer.PhoneCodeManager()
GatewayServer.PhoneCodeRequestType = {
	PRT_BEGIN = 0,
	PRT_REGISTER = 1,
	PRT_BINDPHONE = 2,
	PRT_FORGOTPWD = 3,
	PRT_LOGIN = 4,
	PRT_END = 5,
}

function GatewayServer.HandleQPhoneCode(client, msg)
	local ___COROUTINE = coroutine.running()
	Lua.Assert(msg.phone_number ~= nil, "手机号码不能为空")
	Lua.Assert(msg.phone_number ~= "", "手机号码不能为空")
	Lua.Assert(msg.request_type > 0 and msg.request_type < 5, "无效的请求方式!")
	if msg.request_type == 3 or msg.request_type == 4 then
		local error, count = A_MysqlSystem:SelectCount(___all_struct[90250184], "phone_number", msg.phone_number)
		if error ~= nil then
			Lua.Throw(error)
		end
		Lua.Assert(count ~= 0, "手机号码不存在!")
	end
	local info = GatewayServer.g_PhoneCodeManager:GetPhoneCode(msg.phone_number)
	if info ~= nil then
		Lua.Assert(info.count < 5, "该手机已经获取验证码满5次，请明天再试!")
		Lua.Assert(os.time() - info.begin_time >= 120, "请在2分钟后再获取验证码!")
	end
	local phone_code_cfg = GatewayServer.g_PhoneCodeManager:GetPhoneCodeCfg()
	Lua.Assert(phone_code_cfg.url ~= nil and phone_code_cfg.url ~= "", "暂时不支持获取验证码")
	if msg.request_type == 1 or msg.request_type == 2 then
		local error, count = A_MysqlSystem:SelectCount(___all_struct[90250184], "phone_number", msg.phone_number)
		if error ~= nil then
			Lua.Throw("数据库操作失败:" .. error)
		end
		Lua.Assert(count > 0, "该号码已经被注册了!")
	end
	local phone_code = tostring(math.random(1000, 9999))
	local cfg = GatewayServer.g_PhoneCodeManager:GetPhoneCodeCfg()
	local send_param = {}
	send_param.sid = cfg.sid
	send_param.token = cfg.token
	send_param.appid = cfg.appid
	send_param.templateid = cfg.templateid
	send_param.param = phone_code .. ",5"
	send_param.mobile = msg.phone_number
	local error, content = A_HttpSystem:PostJson(cfg.url, send_param)
	Lua.Assert(error == nil, "验证码发送失败")
	local result, response = Lua.TCall(ALittle.String_JsonDecode, content)
	Lua.Assert(result == nil, "验证码发送结果解析错误")
	Lua.Assert(response.code == "000000", "验证码发送失败")
	GatewayServer.g_PhoneCodeManager:AddPhoneCode(msg.phone_number, phone_code)
	return {}
end

ALittle.RegMsgRpcCallback(-801052492, GatewayServer.HandleQPhoneCode, -247110298)
end