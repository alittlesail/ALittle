
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

RegStruct(2129851601, "ALittle.VersionInstallInfo", {
name = "ALittle.VersionInstallInfo", ns_name = "ALittle", rl_name = "VersionInstallInfo", hash_code = 2129851601,
name_list = {"c_file_path","c_file_size","start_size"},
type_list = {"string","int","int"},
option_map = {}
})
RegStruct(-600814285, "ALittle.SmallVersionInfo", {
name = "ALittle.SmallVersionInfo", ns_name = "ALittle", rl_name = "SmallVersionInfo", hash_code = -600814285,
name_list = {"c_file_path","c_file_size","c_type","c_width","c_height","c_md5","c_update_time","c_update_index","c_is_delete"},
type_list = {"string","int","string","int","int","string","int","int","int"},
option_map = {}
})
RegStruct(-245594234, "ALittle.VersionDownloadInfo", {
name = "ALittle.VersionDownloadInfo", ns_name = "ALittle", rl_name = "VersionDownloadInfo", hash_code = -245594234,
name_list = {"c_file_path","c_file_size","c_type","c_width","c_height","c_md5","c_update_time","c_update_index","c_is_delete","start_size"},
type_list = {"string","int","string","int","int","string","int","int","int","int"},
option_map = {}
})
RegStruct(1916591200, "ALittle.BigVersionInfo", {
name = "ALittle.BigVersionInfo", ns_name = "ALittle", rl_name = "BigVersionInfo", hash_code = 1916591200,
name_list = {"c_big_version","c_install_version","c_db_version"},
type_list = {"string","string","string"},
option_map = {}
})
RegStruct(-1881042933, "ALittle.VersionLogInfo", {
name = "ALittle.VersionLogInfo", ns_name = "ALittle", rl_name = "VersionLogInfo", hash_code = -1881042933,
name_list = {"c_content","c_create_time","c_create_index"},
type_list = {"string","int","int"},
option_map = {}
})

local HttpSender = Lua.Template(HttpSenderTemplate, "ALittle.HttpSenderTemplate<lua.__CPPAPIHttpInterface>", __CPPAPIHttpInterface);
local HttpFileSender = Lua.Template(HttpFileSenderTemplate, "ALittle.HttpFileSenderTemplate<lua.__CPPAPIHttpFileInterface>", __CPPAPIHttpFileInterface);
VersionProcess = {
	VERSION_NONEED_UPDATE = 1,
	VERSION_NEED_UPDATE_ADD = 2,
	VERSION_NEED_UPDATE_FORCE = 3,
	UPDATE_VERSION_FAILED = 11,
	UPDATE_VERSION_SUCCEED = 12,
	UPDATE_VERSION_INSTALL = 13,
}

VersionSystem = Lua.Class(nil, "ALittle.VersionSystem")

function VersionSystem.UpdateTimeIndexComp(a, b)
	if a == nil and b == nil then
		return 0
	end
	if b == nil then
		return 1
	end
	if a == nil then
		return -1
	end
	if a.c_update_time > b.c_update_time then
		return 1
	end
	if a.c_update_time < b.c_update_time then
		return -1
	end
	if a.c_update_index > b.c_update_index then
		return 1
	end
	if a.c_update_index < b.c_update_index then
		return -1
	end
	return 0
end

function VersionSystem:Ctor(account_name, module_name)
	___rawset(self, "_account_name", account_name)
	___rawset(self, "_module_name", module_name)
	___rawset(self, "_install_name", "install.xxx")
	___rawset(self, "_module_path", "Module/" .. module_name .. "/")
	___rawset(self, "_update_path", "Update/" .. module_name .. "/")
	___rawset(self, "_check", nil)
	___rawset(self, "_callback", nil)
	___rawset(self, "_cur_in_version", "CurVersion.db")
	___rawset(self, "_cur_in_version_tmp", "CurVersionTmp.db")
	___rawset(self, "_tmp_in_version", "TmpVersion.db")
	___rawset(self, "_new_in_version", "NewVersion.db")
	___rawset(self, "_new_version_tmp", "NewVersionTmp.db")
	___rawset(self, "_doing", false)
	___rawset(self, "_big_version", false)
	___rawset(self, "_install_info", nil)
	___rawset(self, "_download_list", {})
	___rawset(self, "_download_list_count", 0)
	___rawset(self, "_total_repeat_count", 0)
	___rawset(self, "_remain_repeat_count", 0)
	___rawset(self, "_cur_file_index", 0)
	___rawset(self, "_file_count", 0)
	___rawset(self, "_total_update_size", 0)
	___rawset(self, "_current_update_size", 0)
	___rawset(self, "_current_file_size", 0)
	___rawset(self, "_current_request", nil)
	___rawset(self, "_ask_update_request", nil)
end

function VersionSystem.CreateVersionSystem(account_name, module_name)
	local platform = System_GetPlatform()
	if platform == "Android" then
		return VersionSystemAndroid(account_name, module_name)
	elseif platform == "iOS" then
		return VersionSystemIOS(account_name, module_name)
	elseif platform == "Windows" then
		return VersionSystemWindows(account_name, module_name)
	end
	return nil
end

function VersionSystem.RefreshVersion()
	local platform = System_GetPlatform()
	if platform == "Android" then
		VersionSystemAndroid.RefreshVersion()
	elseif platform == "iOS" then
		VersionSystemIOS.RefreshVersion()
	elseif platform == "Windows" then
		VersionSystemWindows.RefreshVersion()
	end
end

function VersionSystem:GetVersionInfo(db_path, get_log_count)
	if File_GetFileAttr(db_path) == nil then
		return nil, nil, nil
	end
	local big_version
	local small_version
	local sqlite = sqlite3.open(db_path)
	local stmt = sqlite:prepare("SELECT * FROM BigVersion")
	for row in stmt:nrows() do
		big_version = row
	end
	stmt:reset()
	stmt = sqlite:prepare("SELECT * FROM SmallVersion ORDER BY c_update_time DESC,c_update_index DESC LIMIT 1")
	for row in stmt:nrows() do
		small_version = row
	end
	stmt:reset()
	if get_log_count == nil then
		get_log_count = 1
	end
	stmt = sqlite:prepare("SELECT * FROM VersionLog ORDER BY c_create_time DESC,c_create_index DESC LIMIT ?")
	stmt:bind_values(get_log_count)
	local log_list = {}
	local log_list_count = 0
	for row in stmt:nrows() do
		log_list_count = log_list_count + 1
		log_list[log_list_count] = row.c_content
	end
	stmt:reset()
	sqlite:close()
	return big_version, small_version, log_list
end

function VersionSystem:GetCurVersion(get_log_count)
	return self:GetVersionInfo(File_BaseFilePath() .. self._module_path .. self._cur_in_version, get_log_count)
end

function VersionSystem:GetNewVersion(get_log_count)
	return self:GetVersionInfo(File_BaseFilePath() .. self._update_path .. self._new_in_version, get_log_count)
end

function VersionSystem:GetNewLogList()
	if self._update_info == nil then
		return nil
	end
	return self._update_info.log_list
end

function VersionSystem.__getter:doing()
	return self._doing
end

function VersionSystem.__getter:total_update_size()
	return self._total_update_size
end

function VersionSystem.__getter:current_update_size()
	return self._current_update_size + self._current_file_size
end

function VersionSystem:UpdateModule()
	local update_path = File_BaseFilePath() .. "Update/" .. self._module_name
	local module_path = File_BaseFilePath() .. "Module/" .. self._module_name
	if File_GetFileAttr(module_path .. "/CurVersion.db") == nil then
		File_MakeDeepDir(module_path)
		File_CopyFileFromAsset("Module/" .. self._module_name .. "/CurVersion.db", module_path .. "/CurVersionInstall.db")
		File_RenameFile(module_path .. "/CurVersionInstall.db", module_path .. "/CurVersion.db")
	end
	if File_GetFileAttr(update_path) == nil then
		return
	end
	local tmp_version = update_path .. "/" .. self._tmp_in_version
	if File_GetFileAttr(tmp_version) ~= nil then
		return
	end
	local cur_big_version, cur_small_version = self:GetCurVersion()
	local new_big_version, new_small_version = self:GetNewVersion()
	if VersionSystem.UpdateTimeIndexComp(cur_small_version, new_small_version) >= 0 then
		File_DeleteDeepDir(update_path, false)
		return
	end
	local install_path = update_path .. "/" .. self._install_name
	if File_GetFileAttr(install_path) ~= nil then
		File_CopyFile(update_path .. "/" .. self._new_in_version, update_path .. "/" .. self._tmp_in_version)
	else
		File_MakeDeepDir(module_path)
		Log("Update目录的文件全部复制到Module中.", update_path, module_path)
		File_CopyDeepDir(update_path, module_path, nil, true)
		local sqlite_new = sqlite3.open(update_path .. "/" .. self._new_in_version)
		local stmt = sqlite_new:prepare("SELECT * FROM SmallVersion WHERE (c_update_time>? OR (c_update_time=? AND c_update_index>?)) AND c_is_delete=1")
		if cur_small_version == nil then
			stmt:bind_values(0, 0, 0)
		else
			stmt:bind_values(cur_small_version.c_update_time, cur_small_version.c_update_time, cur_small_version.c_update_index)
		end
		for row in stmt:nrows() do
			Log("删掉残留文件.", module_path .. "/" .. row.c_file_path)
			File_DeleteFile(module_path .. "/" .. row.c_file_path)
		end
		stmt:reset()
		if cur_big_version ~= nil and cur_big_version.c_db_version ~= new_big_version.c_db_version then
			local sqlite_cur = sqlite3.open(module_path .. "/" .. self._cur_in_version)
			if sqlite_cur ~= nil then
				local stmt_cur = sqlite_cur:prepare("SELECT * FROM SmallVersion WHERE c_is_delete=0")
				local stmt_new = sqlite_new:prepare("SELECT * FROM SmallVersion WHERE c_is_delete=0 AND c_file_path=?")
				for row in stmt_cur:nrows() do
					stmt_new:bind_values(row.c_file_path)
					local has = false
					for _ in stmt_new:nrows() do
						has = true
						break
					end
					stmt_new:reset()
					if has == false then
						Log("删掉残留文件.", module_path .. "/" .. row.c_file_path)
						File_DeleteFile(module_path .. "/" .. row.c_file_path)
					end
				end
				stmt_cur:reset()
				sqlite_cur:close()
			end
		end
		sqlite_new:close()
		File_CopyFile(update_path .. "/" .. self._new_in_version, module_path .. "/" .. self._cur_in_version_tmp)
		File_DeleteFile(module_path .. "/" .. self._cur_in_version)
		File_RenameFile(module_path .. "/" .. self._cur_in_version_tmp, module_path .. "/" .. self._cur_in_version)
		Log("删除Update目录的全部文件", update_path)
		File_DeleteDeepDir(update_path, true)
	end
end

function VersionSystem:UpdateVersion(ip, port, callback, check, repeat_count)
local ___COROUTINE = coroutine.running()
	if self._doing == true then
		Log("VersionSystem.UpdateVersion, already in updating!")
		return VersionProcess.UPDATE_VERSION_FAILED
	end
	if ip == nil then
		Log("VersionSystem.UpdateVersion, ip must not be null!")
		return VersionProcess.UPDATE_VERSION_FAILED
	end
	if port == nil then
		Log("VersionSystem.UpdateVersion, port must not be null!")
		return VersionProcess.UPDATE_VERSION_FAILED
	end
	self._callback = callback
	self._check = check
	self._ip = ip
	self._port = port
	self._install_info = nil
	self._update_info = nil
	self._download_list = {}
	self._download_list_count = 0
	if repeat_count == nil then
		repeat_count = 0
	end
	self._total_repeat_count = repeat_count
	if self._total_repeat_count < 0 then
		self._total_repeat_count = 0
	end
	self._remain_repeat_count = self._total_repeat_count
	self._cur_file_index = 0
	self._file_count = 0
	self._total_update_size = 0
	self._current_update_size = 0
	self._current_file_size = 0
	self._cur_big_version, self._cur_small_version = self:GetCurVersion()
	do
		local param = {}
		if self._cur_big_version ~= nil then
			param.big_version = self._cur_big_version.c_big_version
			param.install_version = self._cur_big_version.c_install_version
		end
		if self._cur_small_version ~= nil then
			param.small_version_time = self._cur_small_version.c_update_time
			param.small_version_index = self._cur_small_version.c_update_index
		end
		param.platform = System_GetPlatform()
		param.module_name = self._module_name
		param.account_name = self._account_name
		self._ask_update_request = HttpSender(self._ip, self._port)
		self._doing = true
		local error, result = ALittle.IHttpSender.Invoke("VersionServer.QUpdateVersion", self._ask_update_request, param)
		self._ask_update_request = nil
		if error ~= nil then
			Log("VersionSystem.UpdateVersion" .. error)
			self._doing = false
			return VersionProcess.UPDATE_VERSION_FAILED
		end
		self._ask_update_request = nil
		if error ~= nil then
			Log("VersionSystem error:" .. error)
			self._doing = false
			return VersionProcess.UPDATE_VERSION_FAILED
		end
		if result.result == false then
			self._doing = false
			return VersionProcess.VERSION_NONEED_UPDATE
		end
		self._update_info = result
		if self._check then
			self._doing = false
			if self._cur_big_version == nil or result.version_info.big_version ~= self._cur_big_version.c_big_version then
				return VersionProcess.VERSION_NEED_UPDATE_FORCE
			else
				return VersionProcess.VERSION_NEED_UPDATE_ADD
			end
		end
		if self._cur_big_version == nil or self._update_info.version_info.install_version ~= self._cur_big_version.c_install_version then
			self._install_info = {}
			self._install_info.c_file_path = self._install_name
			self._install_info.c_file_size = self._update_info.version_info.install_size
			self._install_info.start_size = 0
		else
			self._install_info = nil
		end
		File_MakeDeepDir(File_BaseFilePath() .. "Update/" .. self._module_name)
	end
	do
		local param = {}
		param.platform = System_GetPlatform()
		param.version_id = self._update_info.version_info.version_id
		param.file_path = "CurVersion.db"
		self._current_request = HttpFileSender(self._ip, self._port, File_BaseFilePath() .. self._update_path .. self._new_version_tmp, 0, nil)
		local error = ALittle.IHttpFileSender.InvokeDownload("VersionServer.QDownloadVersionFile", self._current_request, param)
		self._current_request = nil
		if error ~= nil then
			self._doing = false
			return VersionProcess.UPDATE_VERSION_FAILED
		end
		File_RenameFile(File_BaseFilePath() .. self._update_path .. self._new_version_tmp, File_BaseFilePath() .. self._update_path .. self._new_in_version)
		local sqlite_new = sqlite3.open(File_BaseFilePath() .. self._update_path .. self._new_in_version)
		if sqlite_new ~= nil then
			local stmt = sqlite_new:prepare("SELECT * FROM SmallVersion WHERE (c_update_time>? OR (c_update_time=? AND c_update_index>?)) AND c_is_delete=0")
			if self._cur_small_version == nil then
				stmt:bind_values(0, 0, 0)
			else
				stmt:bind_values(self._cur_small_version.c_update_time, self._cur_small_version.c_update_time, self._cur_small_version.c_update_index)
			end
			for row in stmt:nrows() do
				row.start_size = 0
				self._download_list_count = self._download_list_count + 1
				self._download_list[self._download_list_count] = row
			end
			stmt:reset()
			sqlite_new:close()
		else
			Log("VersionSystem error. new_version_db open failed!")
			File_DeleteDeepDir(File_BaseFilePath() .. "Update/" .. self._module_name, false)
			self._doing = false
			return VersionProcess.UPDATE_VERSION_FAILED
		end
		if self._module_name ~= A_ModuleSystem:GetMainModuleName() then
			self._install_info = nil
		end
		if self._install_info ~= nil then
			self._download_list = {}
			self._download_list_count = 1
			local download_info = {}
			download_info.c_file_path = self._install_info.c_file_path
			download_info.c_file_size = self._install_info.c_file_size
			download_info.start_size = self._install_info.start_size
			self._download_list[self._download_list_count] = download_info
		end
		self._file_count = self._download_list_count
		self._cur_file_index = 0
		if self._file_count > 0 then
			for k, v in ___ipairs(self._download_list) do
				self._total_update_size = self._total_update_size + v.c_file_size
			end
			local new_md5 = __CPPAPI_ScriptSystemEx:FileMD5(File_BaseFilePath() .. self._update_path .. self._new_in_version)
			local tmp_md5 = nil
			if File_GetFileAttr(File_BaseFilePath() .. self._update_path .. self._tmp_in_version) ~= nil then
				tmp_md5 = __CPPAPI_ScriptSystemEx:FileMD5(File_BaseFilePath() .. self._update_path .. self._tmp_in_version)
			end
			if new_md5 == tmp_md5 then
				local new_download_list = {}
				local new_download_list_count = 0
				for k, v in ___ipairs(self._download_list) do
					local file_attr = File_GetFileAttr(File_BaseFilePath() .. self._update_path .. v.c_file_path)
					if file_attr == nil then
						new_download_list_count = new_download_list_count + 1
						new_download_list[new_download_list_count] = v
					elseif file_attr.size < v.c_file_size then
						v.start_size = file_attr.size
						new_download_list_count = new_download_list_count + 1
						table.insert(new_download_list, 1, v)
					else
						self._current_update_size = self._current_update_size + file_attr.size
					end
				end
				self._download_list = new_download_list
				self._download_list_count = new_download_list_count
			else
				File_CopyFile(File_BaseFilePath() .. self._update_path .. self._new_in_version, File_BaseFilePath() .. self._update_path .. self._tmp_in_version)
			end
			self._remain_repeat_count = self._total_repeat_count
			self:DownloadNext()
		else
			self._doing = false
			return VersionProcess.VERSION_NONEED_UPDATE
		end
	end
	return nil
end

function VersionSystem:DownloadNext()
local ___COROUTINE = coroutine.running()
	local count = self._download_list_count
	if count == 0 then
		self._doing = false
		File_DeleteFile(File_BaseFilePath() .. self._update_path .. self._tmp_in_version)
		if self._install_info ~= nil then
			return VersionProcess.UPDATE_VERSION_INSTALL
		end
		if File_GetFileAttr(File_BaseFilePath() .. self._update_path .. "Engine") ~= nil then
			File_MakeDir(File_BaseFilePath() .. self._module_path .. "Engine")
			File_CopyDeepDir(File_BaseFilePath() .. self._update_path .. "Engine", File_BaseFilePath() .. self._module_path .. "Engine", nil, false)
		end
		return VersionProcess.UPDATE_VERSION_SUCCEED
	end
	self._cur_file_index = self._cur_file_index + 1
	local file_info = self._download_list[1]
	table.remove(self._download_list, 1)
	self._download_list_count = self._download_list_count - 1
	local file_full_path = File_BaseFilePath() .. self._update_path .. file_info.c_file_path
	local file_path = File_GetFilePathByPath(file_info.c_file_path)
	Log("begin download remain_count(" .. self._remain_repeat_count .. ")." .. file_full_path, "start size." .. file_info.start_size)
	if file_path ~= "" then
		File_MakeDeepDir(File_BaseFilePath() .. self._update_path .. file_path)
	end
	self._current_file_size = file_info.start_size
	local param = {}
	param.platform = System_GetPlatform()
	param.start_size = file_info.start_size
	param.version_id = self._update_info.version_info.version_id
	param.file_path = file_info.c_file_path
	self._current_request = HttpFileSender(self._ip, self._port, file_full_path, file_info.start_size, Lua.Bind(self.DownloadUpdateFileCallback, self, file_info, self._current_request))
	local error = ALittle.IHttpFileSender.InvokeDownload("VersionServer.QDownloadVersionFile", self._current_request, param)
	self._current_request = nil
	if error ~= nil then
		if self._remain_repeat_count <= 0 then
			self._doing = false
			return VersionProcess.UPDATE_VERSION_FAILED
		end
		self._remain_repeat_count = self._remain_repeat_count - 1
		self._cur_file_index = self._cur_file_index - 1
		table.insert(self._download_list, 1, file_info)
		self._download_list_count = self._download_list_count + 1
		file_info.start_size = 0
		local file_attr = File_GetFileAttr(file_full_path)
		if file_attr ~= nil then
			file_info.start_size = file_attr.size
		end
		self._current_file_size = file_info.start_size
	else
		Log("download succeed." .. file_full_path)
		self._current_update_size = self._current_update_size + self._current_request:GetTotalSize()
		self._remain_repeat_count = self._total_repeat_count
		self._current_file_size = 0
	end
	return self:DownloadNext()
end

function VersionSystem:DownloadUpdateFileCallback(file_info, file)
	local file_name = file:GetFilePath()
	local cur_size = file:GetCurSize()
	local total_size = file:GetTotalSize()
	self._callback(file_name, cur_size, total_size, self._cur_file_index, self._file_count)
	self._current_file_size = cur_size
end

function VersionSystem:StopUpdate()
	if self._doing ~= true then
		return
	end
	if self._ask_update_request ~= nil then
		self._ask_update_request:Stop()
		self._ask_update_request = nil
	end
	if self._current_request ~= nil then
		self._current_request:Stop()
		self._current_request = nil
	end
end

function VersionSystem:Install(install_name)
end

