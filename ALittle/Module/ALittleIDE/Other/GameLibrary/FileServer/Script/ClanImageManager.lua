
module("FileServer", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1164907202, "ALittle.CacheData", {
name = "ALittle.CacheData", ns_name = "ALittle", rl_name = "CacheData", hash_code = -1164907202,
name_list = {"id"},
type_list = {"int"},
option_map = {primary="id"}
})
ALittle.RegStruct(319415465, "FileServer.ClanImageInfo", {
name = "FileServer.ClanImageInfo", ns_name = "FileServer", rl_name = "ClanImageInfo", hash_code = 319415465,
name_list = {"id","image_md5","create_time"},
type_list = {"int","string","int"},
option_map = {primary="id"}
})
ALittle.RegStruct(-1420108834, "FileServer.ClanImageInfoDelete", {
name = "FileServer.ClanImageInfoDelete", ns_name = "FileServer", rl_name = "ClanImageInfoDelete", hash_code = -1420108834,
name_list = {"clan_id","create_time"},
type_list = {"int","int"},
option_map = {}
})
ALittle.RegStruct(1459438620, "FileServer.QCheckClanImage", {
name = "FileServer.QCheckClanImage", ns_name = "FileServer", rl_name = "QCheckClanImage", hash_code = 1459438620,
name_list = {"gs_route_id","account_id","session_code","target_clan_id","target_image_md5"},
type_list = {"int","int","string","int","string"},
option_map = {}
})
ALittle.RegStruct(246409882, "FileServer.ACheckClanImage", {
name = "FileServer.ACheckClanImage", ns_name = "FileServer", rl_name = "ACheckClanImage", hash_code = 246409882,
name_list = {"is_exist","need_download"},
type_list = {"bool","bool"},
option_map = {}
})
ALittle.RegStruct(-2092316375, "ALittle.SS2GS_QCheckSessionCode", {
name = "ALittle.SS2GS_QCheckSessionCode", ns_name = "ALittle", rl_name = "SS2GS_QCheckSessionCode", hash_code = -2092316375,
name_list = {"account_id","session_code"},
type_list = {"int","string"},
option_map = {}
})
ALittle.RegStruct(-1766835499, "ALittle.GS2SS_ACheckSessionCode", {
name = "ALittle.GS2SS_ACheckSessionCode", ns_name = "ALittle", rl_name = "GS2SS_ACheckSessionCode", hash_code = -1766835499,
name_list = {},
type_list = {},
option_map = {}
})
ALittle.RegStruct(305225743, "FileServer.QDownloadClanImage", {
name = "FileServer.QDownloadClanImage", ns_name = "FileServer", rl_name = "QDownloadClanImage", hash_code = 305225743,
name_list = {"gs_route_id","account_id","session_code","target_clan_id"},
type_list = {"int","int","string","int"},
option_map = {}
})
ALittle.RegStruct(869197325, "FileServer.QUploadClanImage", {
name = "FileServer.QUploadClanImage", ns_name = "FileServer", rl_name = "QUploadClanImage", hash_code = 869197325,
name_list = {"gs_route_id","account_id","session_code","target_image_md5"},
type_list = {"int","int","string","string"},
option_map = {}
})
ALittle.RegStruct(1113162002, "FileServer.AUploadClanImage", {
name = "FileServer.AUploadClanImage", ns_name = "FileServer", rl_name = "AUploadClanImage", hash_code = 1113162002,
name_list = {},
type_list = {},
option_map = {}
})

ClanImageManager = ALittle.Class(nil, "FileServer.ClanImageManager")

function ClanImageManager:Ctor()
	___rawset(self, "_cache", ALittle.Template(ALittle.CacheDataSet, "ALittle.CacheDataSet<FileServer.ClanImageInfo>", ___all_struct[319415465])(30 * 1000, 60 * 1000))
end

function ClanImageManager.__getter:cache()
	return self._cache
end

function ClanImageManager:Setup()
	local error = self._cache:Init()
	if error ~= nil then
		return error
	end
	self._base_path = g_ConfigSystem:GetString("clan_image_path", "")
	if self._base_path ~= "" then
		ALittle.File_MakeDeepDir(self._base_path)
	end
	local delay_time = ALittle.GetNextTodayBeginTime() - os.time()
	self._timer = A_LoopSystem:AddTimer(delay_time * 1000, ALittle.Bind(self.HandleNewDay, self))
	return nil
end

function ClanImageManager:Shutdown()
	if self._timer ~= nil then
		A_LoopSystem:RemoveTimer(self._timer)
		self._timer = nil
	end
	self._cache:Release()
end

function ClanImageManager:GetImagePath(id, create_time)
	local ymd = os.date("%Y-%m-%d", create_time)
	local hms = os.date("%H-%M-%S", create_time)
	return self._base_path .. "/" .. ymd .. "/" .. hms .. "/" .. id .. "_" .. ymd .. "_" .. hms .. ".png"
end

function ClanImageManager:HandleNewDay()
	local error, select_list = A_MysqlSystem:SelectListFromByMap(___all_struct[-1420108834], nil)
	if error ~= nil then
		ALittle.Error(error)
	end
	if select_list ~= nil then
		for index, info in ___ipairs(select_list) do
			local file_path = self:GetImagePath(info.clan_id, info.create_time)
			if not ALittle.File_DeleteFile(file_path) then
				ALittle.Warn("�ļ�ɾ��ʧ��:" .. file_path)
			end
		end
	end
	error = A_MysqlSystem:DeleteFromByMap(___all_struct[319415465], nil)
	if error ~= nil then
		ALittle.Error(error)
	end
	local delay_time = ALittle.GetNextTodayBeginTime() - os.time()
	self._timer = A_LoopSystem:AddTimer(delay_time * 1000, ALittle.Bind(self.HandleNewDay, self))
end
ClanImageManager.HandleNewDay = ALittle.CoWrap(ClanImageManager.HandleNewDay)

g_ClanImageManager = ClanImageManager()
function HandleCheckClanImage(client, msg)
	local error, session = A_SessionSystem:ConnectSession(7, msg.gs_route_id)
	if error ~= nil then
		ALittle.Throw(error)
	end
	do
		local param = {}
		param.account_id = msg.account_id
		param.session_code = msg.session_code
		error = ALittle.IMsgCommon.InvokeRPC(-2092316375, session, param)
		if error ~= nil then
			ALittle.Throw(error)
		end
	end
	do
		local data = g_ClanImageManager.cache:GetData(msg.target_clan_id)
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

ALittle.RegHttpCallback("FileServer.QCheckClanImage", HandleCheckClanImage)
function HandleDownloadClanImage(client, msg)
	local error, session = A_SessionSystem:ConnectSession(7, msg.gs_route_id)
	if error ~= nil then
		ALittle.Throw(error)
	end
	do
		local param = {}
		param.account_id = msg.account_id
		param.session_code = msg.session_code
		error = ALittle.IMsgCommon.InvokeRPC(-2092316375, session, param)
		if error ~= nil then
			ALittle.Throw(error)
		end
	end
	do
		local data = g_ClanImageManager.cache:GetData(msg.target_clan_id)
		ALittle.Assert(data, "ͷ�񲻴���")
		return g_ClanImageManager:GetImagePath(data.id, data.create_time), 0
	end
end

ALittle.RegHttpDownloadCallback("FileServer.QDownloadClanImage", HandleDownloadClanImage)
function HandleQUploadClanImage(client, msg)
	local error, session = A_SessionSystem:ConnectSession(7, msg.gs_route_id)
	if error ~= nil then
		ALittle.Throw(error)
	end
	do
		local param = {}
		param.account_id = msg.account_id
		param.session_code = msg.session_code
		error = ALittle.IMsgCommon.InvokeRPC(-2092316375, session, param)
		if error ~= nil then
			ALittle.Throw(error)
		end
	end
	local create_time = os.time()
	do
		local data = g_ClanImageManager.cache:GetData(msg.account_id)
		if data ~= nil and data.create_time == create_time then
			ALittle.Throw("�Ѿ���ͷ�������ϴ�")
		end
		local file_path = g_ClanImageManager:GetImagePath(msg.account_id, create_time)
		local file_dir = ALittle.File_GetFilePathByPath(file_path)
		ALittle.File_MakeDeepDir(file_dir)
		error = client:StartReceiveFile(file_path, 0)
		if error ~= nil then
			ALittle.Throw(error)
		end
	end
	local data = g_ClanImageManager.cache:GetData(msg.account_id)
	if data ~= nil then
		g_ClanImageManager.cache:DeleteData(data.id)
		local delete = {}
		delete.clan_id = data.id
		delete.create_time = data.create_time
		error = A_MysqlSystem:InsertInto(___all_struct[-1420108834], delete)
		if error ~= nil then
			ALittle.Error(error)
		end
	end
	local new_data = {}
	new_data.id = msg.account_id
	new_data.create_time = create_time
	new_data.image_md5 = msg.target_image_md5
	g_ClanImageManager.cache:CreateData(new_data)
	return {}
end

ALittle.RegHttpFileCallback("FileServer.QUploadClanImage", HandleQUploadClanImage)
