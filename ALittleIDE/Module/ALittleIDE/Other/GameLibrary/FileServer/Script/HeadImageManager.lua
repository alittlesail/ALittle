-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.FileServer == nil then _G.FileServer = {} end
local FileServer = FileServer
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-2092316375, "ALittle.SS2GS_QCheckSessionCode", {
name = "ALittle.SS2GS_QCheckSessionCode", ns_name = "ALittle", rl_name = "SS2GS_QCheckSessionCode", hash_code = -2092316375,
name_list = {"account_id","session_code"},
type_list = {"int","string"},
option_map = {}
})
ALittle.RegStruct(2049961865, "FileServer.AUploadHeadImage", {
name = "FileServer.AUploadHeadImage", ns_name = "FileServer", rl_name = "AUploadHeadImage", hash_code = 2049961865,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(-1925387704, "FileServer.HeadImageInfo", {
name = "FileServer.HeadImageInfo", ns_name = "FileServer", rl_name = "HeadImageInfo", hash_code = -1925387704,
name_list = {"id","image_md5","create_time"},
type_list = {"int","string","int"},
option_map = {primary="id"}
})
ALittle.RegStruct(-1766835499, "ALittle.GS2SS_ACheckSessionCode", {
name = "ALittle.GS2SS_ACheckSessionCode", ns_name = "ALittle", rl_name = "GS2SS_ACheckSessionCode", hash_code = -1766835499,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(1696187693, "FileServer.HeadImageInfoDelete", {
name = "FileServer.HeadImageInfoDelete", ns_name = "FileServer", rl_name = "HeadImageInfoDelete", hash_code = 1696187693,
name_list = {"account_id","create_time"},
type_list = {"int","int"},
option_map = {}
})
ALittle.RegStruct(1301042862, "FileServer.ACheckHeadImage", {
name = "FileServer.ACheckHeadImage", ns_name = "FileServer", rl_name = "ACheckHeadImage", hash_code = 1301042862,
name_list = {"is_exist","need_download"},
type_list = {"bool","bool"},
option_map = {}
})
ALittle.RegStruct(-1164907202, "ALittle.CacheData", {
name = "ALittle.CacheData", ns_name = "ALittle", rl_name = "CacheData", hash_code = -1164907202,
name_list = {"id"},
type_list = {"int"},
option_map = {primary="id"}
})
ALittle.RegStruct(-969892976, "GatewayServer.ConnectInfo", {
name = "GatewayServer.ConnectInfo", ns_name = "GatewayServer", rl_name = "ConnectInfo", hash_code = -969892976,
name_list = {"client_ip","client_port","http_ip","http_port"},
type_list = {"string","int","string","int"},
option_map = {}
})
ALittle.RegStruct(888437463, "ALittle.SessionConnectEvent", {
name = "ALittle.SessionConnectEvent", ns_name = "ALittle", rl_name = "SessionConnectEvent", hash_code = 888437463,
name_list = {"target","connect_key","route_type","route_num","session"},
type_list = {"ALittle.EventDispatcher","int","int","int","ALittle.MsgSessionTemplate<ALittle.MsgSessionNative,carp.CarpMessageWriteFactory>"},
option_map = {}
})
ALittle.RegStruct(-747163608, "FileServer.QDownloadHeadImage", {
name = "FileServer.QDownloadHeadImage", ns_name = "FileServer", rl_name = "QDownloadHeadImage", hash_code = -747163608,
name_list = {"gs_route_id","account_id","session_code","target_account_id"},
type_list = {"int","int","string","int"},
option_map = {}
})
ALittle.RegStruct(-370290946, "GatewayServer.NUpdateRouteInfo", {
name = "GatewayServer.NUpdateRouteInfo", ns_name = "GatewayServer", rl_name = "NUpdateRouteInfo", hash_code = -370290946,
name_list = {"route_weight","route_info"},
type_list = {"int","GatewayServer.ConnectInfo"},
option_map = {}
})
ALittle.RegStruct(-195273260, "FileServer.QUploadHeadImage", {
name = "FileServer.QUploadHeadImage", ns_name = "FileServer", rl_name = "QUploadHeadImage", hash_code = -195273260,
name_list = {"gs_route_id","account_id","session_code","target_image_md5"},
type_list = {"int","int","string","string"},
option_map = {}
})
ALittle.RegStruct(174098031, "FileServer.QCheckHeadImage", {
name = "FileServer.QCheckHeadImage", ns_name = "FileServer", rl_name = "QCheckHeadImage", hash_code = 174098031,
name_list = {"gs_route_id","account_id","session_code","target_account_id","target_image_md5"},
type_list = {"int","int","string","int","string"},
option_map = {}
})
ALittle.RegStruct(-36908822, "ALittle.SessionDisconnectEvent", {
name = "ALittle.SessionDisconnectEvent", ns_name = "ALittle", rl_name = "SessionDisconnectEvent", hash_code = -36908822,
name_list = {"target","connect_key","route_type","route_num","session"},
type_list = {"ALittle.EventDispatcher","int","int","int","ALittle.MsgSessionTemplate<ALittle.MsgSessionNative,carp.CarpMessageWriteFactory>"},
option_map = {}
})

FileServer.HeadImageManager = Lua.Class(nil, "FileServer.HeadImageManager")

function FileServer.HeadImageManager:Ctor()
	___rawset(self, "_cache", Lua.Template(ALittle.CacheDataSet, "ALittle.CacheDataSet<FileServer.HeadImageInfo>", ___all_struct[-1925387704])(30 * 1000, 60 * 1000))
end

function FileServer.HeadImageManager:Setup()
	local ___COROUTINE = coroutine.running()
	local error = self._cache:Init()
	if error ~= nil then
		return error
	end
	self._base_path = FileServer.g_ConfigSystem:GetString("head_image_path", "")
	if self._base_path ~= "" then
		ALittle.File_MakeDeepDir(self._base_path)
	end
	A_SessionSystem:AddEventListener(___all_struct[-36908822], self, self.HandleSessionDisconnect)
	A_SessionSystem:AddEventListener(___all_struct[888437463], self, self.HandleSessionConnect)
	A_SessionSystem:AddConnectSession(1, 1)
	local delay_time = ALittle.GetNextTodayBeginTime() - os.time()
	self._timer = A_LoopSystem:AddTimer(delay_time * 1000, Lua.Bind(self.HandleNewDay, self))
	return nil
end

function FileServer.HeadImageManager:Shutdown()
	if self._timer ~= nil then
		A_LoopSystem:RemoveTimer(self._timer)
		self._timer = nil
	end
	self._cache:Release()
end

function FileServer.HeadImageManager:GetImagePath(id, create_time)
	local ymd = os.date("%Y-%m-%d", create_time)
	local hms = os.date("%H-%M-%S", create_time)
	return self._base_path .. "/" .. ymd .. "/" .. hms .. "/" .. id .. "_" .. ymd .. "_" .. hms .. ".png"
end

function FileServer.HeadImageManager.__getter:cache()
	return self._cache
end

function FileServer.HeadImageManager:HandleNewDay()
	local error, select_list = A_MysqlSystem:SelectListFromByMap(___all_struct[1696187693], nil)
	if error ~= nil then
		ALittle.Error(error)
	end
	if select_list ~= nil then
		for index, info in ___ipairs(select_list) do
			local file_path = self:GetImagePath(info.account_id, info.create_time)
			if not ALittle.File_DeleteFile(file_path) then
				ALittle.Warn("文件删除失败:" .. file_path)
			end
		end
	end
	error = A_MysqlSystem:DeleteFromByMap(___all_struct[-1925387704], nil)
	if error ~= nil then
		ALittle.Error(error)
	end
	local delay_time = ALittle.GetNextTodayBeginTime() - os.time()
	self._timer = A_LoopSystem:AddTimer(delay_time * 1000, Lua.Bind(self.HandleNewDay, self))
end
FileServer.HeadImageManager.HandleNewDay = Lua.CoWrap(FileServer.HeadImageManager.HandleNewDay)

function FileServer.HeadImageManager:HandleSessionDisconnect(event)
	if event.route_type ~= 1 then
		return
	end
	self._gw_session = nil
end

function FileServer.HeadImageManager:HandleSessionConnect(event)
	if event.route_type ~= 1 then
		return
	end
	self._gw_session = event.session
	local param = {}
	param.route_weight = 0
	param.route_info = {}
	param.route_info.http_ip = __CPPAPI_ServerSchedule:GetHttpServerYunIp()
	if param.route_info.http_ip == nil or param.route_info.http_ip == "" then
		param.route_info.http_ip = __CPPAPI_ServerSchedule:GetHttpServerIp()
	end
	param.route_info.http_port = __CPPAPI_ServerSchedule:GetHttpServerPort()
	event.session:SendMsg(___all_struct[-370290946], param)
end

FileServer.g_HeadImageManager = FileServer.HeadImageManager()
function FileServer.HandleCheckHeadImage(client, msg)
	local ___COROUTINE = coroutine.running()
	local error, session = A_SessionSystem:ConnectSession(7, msg.gs_route_id)
	if error ~= nil then
		Lua.Throw(error)
	end
	do
		local param = {}
		param.account_id = msg.account_id
		param.session_code = msg.session_code
		error = ALittle.IMsgCommon.InvokeRPC(-2092316375, session, param)
		if error ~= nil then
			Lua.Throw(error)
		end
	end
	do
		local data = FileServer.g_HeadImageManager.cache:GetData(msg.target_account_id)
		if data == nil then
			local param = {}
			param.is_exist = false
			return param
		end
		local param = {}
		param.is_exist = true
		param.need_download = data.image_md5 ~= msg.target_image_md5
		return param
	end
end

ALittle.RegHttpCallback("FileServer.QCheckHeadImage", FileServer.HandleCheckHeadImage)
function FileServer.HandleDownloadHeadImage(client, msg)
	local ___COROUTINE = coroutine.running()
	local error, session = A_SessionSystem:ConnectSession(7, msg.gs_route_id)
	if error ~= nil then
		Lua.Throw(error)
	end
	do
		local param = {}
		param.account_id = msg.account_id
		param.session_code = msg.session_code
		error = ALittle.IMsgCommon.InvokeRPC(-2092316375, session, param)
		if error ~= nil then
			Lua.Throw(error)
		end
	end
	do
		local data = FileServer.g_HeadImageManager.cache:GetData(msg.target_account_id)
		Lua.Assert(data, "头像不存在")
		return FileServer.g_HeadImageManager:GetImagePath(data.id, data.create_time), 0
	end
end

ALittle.RegHttpDownloadCallback("FileServer.QDownloadHeadImage", FileServer.HandleDownloadHeadImage)
function FileServer.HandleQUploadHeadImage(client, msg)
	local ___COROUTINE = coroutine.running()
	local error, session = A_SessionSystem:ConnectSession(7, msg.gs_route_id)
	if error ~= nil then
		Lua.Throw(error)
	end
	do
		local param = {}
		param.account_id = msg.account_id
		param.session_code = msg.session_code
		error = ALittle.IMsgCommon.InvokeRPC(-2092316375, session, param)
		if error ~= nil then
			Lua.Throw(error)
		end
	end
	local create_time = os.time()
	do
		local data = FileServer.g_HeadImageManager.cache:GetData(msg.account_id)
		if data ~= nil and data.create_time == create_time then
			Lua.Throw("已经有头像正在上传")
		end
		local file_path = FileServer.g_HeadImageManager:GetImagePath(msg.account_id, create_time)
		local file_dir = ALittle.File_GetFilePathByPath(file_path)
		ALittle.File_MakeDeepDir(file_dir)
		error = client:StartReceiveFile(file_path, 0)
		if error ~= nil then
			Lua.Throw(error)
		end
	end
	local data = FileServer.g_HeadImageManager.cache:GetData(msg.account_id)
	if data ~= nil then
		FileServer.g_HeadImageManager.cache:DeleteData(data.id)
		local delete = {}
		delete.account_id = data.id
		delete.create_time = data.create_time
		error = A_MysqlSystem:InsertInto(___all_struct[1696187693], delete)
		if error ~= nil then
			ALittle.Error(error)
		end
	end
	local new_data = {}
	new_data.id = msg.account_id
	new_data.create_time = create_time
	new_data.image_md5 = msg.target_image_md5
	FileServer.g_HeadImageManager.cache:CreateData(new_data)
end

ALittle.RegHttpFileCallback("FileServer.QUploadHeadImage", FileServer.HandleQUploadHeadImage)
end