-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(1962364004, "ALittleIDE.IDEPackageInfo", {
name = "ALittleIDE.IDEPackageInfo", ns_name = "ALittleIDE", rl_name = "IDEPackageInfo", hash_code = 1962364004,
name_list = {"platform","project_name","project_path","export_path","export_module_path","export_module_base_path","version_info","install_info"},
type_list = {"string","string","string","string","string","string","ALittleIDE.IDEVersionInfo","ALittleIDE.IDEInstallInfo"},
option_map = {}
})
ALittle.RegStruct(1916591200, "ALittle.BigVersionInfo", {
name = "ALittle.BigVersionInfo", ns_name = "ALittle", rl_name = "BigVersionInfo", hash_code = 1916591200,
name_list = {"c_big_version","c_install_version","c_db_version"},
type_list = {"string","string","string"},
option_map = {}
})
ALittle.RegStruct(-1247620677, "ALittleIDE.IDEVersionInfo", {
name = "ALittleIDE.IDEVersionInfo", ns_name = "ALittleIDE", rl_name = "IDEVersionInfo", hash_code = -1247620677,
name_list = {"install_version","big_version","version_number","plugin_list"},
type_list = {"string","string","string","string"},
option_map = {}
})
ALittle.RegStruct(1243834211, "ALittleIDE.IDEInstallInfo", {
name = "ALittleIDE.IDEInstallInfo", ns_name = "ALittleIDE", rl_name = "IDEInstallInfo", hash_code = 1243834211,
name_list = {"new_log","install_name","auto_start","package_name","screen","fullscreen","res_ip","res_port","res_base_path","file_name"},
type_list = {"string","string","bool","string","string","bool","string","int","string","string"},
option_map = {}
})
ALittle.RegStruct(-1093384145, "ALittleIDE.IDEExportSubmitInfo", {
name = "ALittleIDE.IDEExportSubmitInfo", ns_name = "ALittleIDE", rl_name = "IDEExportSubmitInfo", hash_code = -1093384145,
name_list = {"upload_list","project_path","export_module_path","is_login","module_name","platform","small_version_time","small_version_index","update_time","update_index","big_version","version_number","install_version","plugin_list","log_list","install_name","install_size","completed","version_id"},
type_list = {"List<string>","string","string","bool","string","string","int","int","int","int","string","string","string","string","List<string>","string","int","bool","string"},
option_map = {}
})
ALittle.RegStruct(1084005584, "ALittleIDE.IDEExportFileInfo", {
name = "ALittleIDE.IDEExportFileInfo", ns_name = "ALittleIDE", rl_name = "IDEExportFileInfo", hash_code = 1084005584,
name_list = {"path","crypt_mode"},
type_list = {"string","bool"},
option_map = {}
})
ALittle.RegStruct(1033286911, "ALittleIDE.ANewVersionInfo", {
name = "ALittleIDE.ANewVersionInfo", ns_name = "ALittleIDE", rl_name = "ANewVersionInfo", hash_code = 1033286911,
name_list = {"result","reason","version_id"},
type_list = {"bool","string","string"},
option_map = {}
})
ALittle.RegStruct(900617833, "ALittleIDE.IDEExportFileAttr", {
name = "ALittleIDE.IDEExportFileAttr", ns_name = "ALittleIDE", rl_name = "IDEExportFileAttr", hash_code = 900617833,
name_list = {"attr","md5","file_type","file_path"},
type_list = {"ALittle.PathAttribute","string","string","string"},
option_map = {}
})
ALittle.RegStruct(839664979, "ALittle.PathAttribute", {
name = "ALittle.PathAttribute", ns_name = "ALittle", rl_name = "PathAttribute", hash_code = 839664979,
name_list = {"directory","size"},
type_list = {"bool","int"},
option_map = {}
})
ALittle.RegStruct(-600814285, "ALittle.SmallVersionInfo", {
name = "ALittle.SmallVersionInfo", ns_name = "ALittle", rl_name = "SmallVersionInfo", hash_code = -600814285,
name_list = {"c_file_path","c_file_size","c_type","c_width","c_height","c_md5","c_update_time","c_update_index","c_is_delete"},
type_list = {"string","int","string","int","int","string","int","int","int"},
option_map = {}
})
ALittle.RegStruct(-435045833, "ALittleIDE.IDEExportVersionInfo", {
name = "ALittleIDE.IDEExportVersionInfo", ns_name = "ALittleIDE", rl_name = "IDEExportVersionInfo", hash_code = -435045833,
name_list = {"small_version","big_version"},
type_list = {"Map<string,ALittle.SmallVersionInfo>","ALittle.BigVersionInfo"},
option_map = {}
})

ALittleIDE.IDEExport = Lua.Class(nil, "ALittleIDE.IDEExport")

function ALittleIDE.IDEExport:Ctor()
	___rawset(self, "_submit_dialog", nil)
	___rawset(self, "_is_in_submit", false)
end

function ALittleIDE.IDEExport:PackagePlatform(project_name, version_info, install_info, platform)
	local ___COROUTINE = coroutine.running()
	ALittle.Log("========PackagePlatform" .. project_name .. "========")
	local project_path = ALittle.File_BaseFilePath() .. "Module/" .. project_name
	Lua.Assert(ALittle.File_GetFileAttr(project_path) ~= nil, "项目文件夹不存在:" .. project_path)
	local export_path = project_path .. "/Export/" .. platform
	ALittle.File_DeleteDeepDir(export_path)
	ALittle.File_MakeDeepDir(export_path)
	local export_module_base_path = export_path .. "/Module"
	if platform == "Android" then
		export_module_base_path = export_path .. "/assets/Module"
	end
	local export_module_path = export_module_base_path .. "/" .. project_name
	ALittle.File_MakeDeepDir(export_module_path)
	local package_info = {}
	package_info.platform = platform
	package_info.project_name = project_name
	package_info.project_path = project_path
	package_info.export_path = export_path
	package_info.export_module_path = export_module_path
	package_info.export_module_base_path = export_module_base_path
	package_info.version_info = version_info
	package_info.install_info = install_info
	self:PackageVersion(package_info)
end

function ALittleIDE.IDEExport:RepairPNG(path)
	ALittle.Log("========RepairPNG:" .. path .. "========")
	Lua.Assert(ALittle.File_GetFileAttr(path) ~= nil, "IDEExport:RepairPNG path is not exist:" .. path)
	local file_map = ALittle.File_GetFileAttrByDir(path)
	for file_path, attr in ___pairs(file_map) do
		if ALittle.File_GetFileExtByPath(file_path) == "png" then
			local surface = carp.LoadCarpSurface(file_path)
			if surface ~= nil then
				carp.SaveCarpSurface(surface, file_path)
				carp.FreeCarpSurface(surface)
			end
		end
	end
end

function ALittleIDE.IDEExport:GenerateAtlas(path)
	ALittle.Log("========GenerateAtlas:" .. path .. "========")
	Lua.Assert(ALittle.File_GetFileAttr(path) ~= nil, "IDEExport:GenerateAtlas path is not exist:" .. path)
	local texture_list = {}
	local count = 0
	local file_map = ALittle.File_GetFileAttrByDir(path)
	for file_path, attr in ___pairs(file_map) do
		if ALittle.File_GetFileExtByPath(file_path) == "png" then
			local surface = carp.LoadCarpSurface(file_path)
			if surface == nil then
				ALittle.Error("ALittle.System_LoadSurface failed! path:" .. file_path)
			else
				local width = carp.GetCarpSurfaceWidth(surface)
				local height = carp.GetCarpSurfaceHeight(surface)
				carp.FreeCarpSurface(surface)
				local texture_info = {}
				texture_info.path = ALittle.String_Sub(file_path, ALittle.String_Len(path) + 2)
				texture_info.width = width
				texture_info.height = height
				count = count + 1
				texture_list[count] = texture_info
			end
		end
	end
	local big_list = ALittle.AltasBinary.GenerateAltas(texture_list, 1024, 1024, 1)
	ALittle.File_WriteJsonToFile(big_list, path .. "/Atlas.ali")
end

function ALittleIDE.IDEExport:PackagePath(src_path, dst_path, file_type, crypt_mode)
	ALittle.Log("========PackagePath:" .. src_path .. "========")
	if ALittle.File_GetFileAttr(src_path) == nil then
		return {}
	end
	if ALittle.File_GetFileAttr(dst_path) == nil then
		ALittle.File_MakeDeepDir(dst_path)
	end
	local file_map = ALittle.File_GetFileAttrByDir(src_path)
	local out_file_map = {}
	for file_path, attr in ___pairs(file_map) do
		local start_index = ALittle.String_Find(file_path, src_path)
		local rel_path = ALittle.String_Sub(file_path, start_index + ALittle.String_Len(src_path))
		local ext = ALittle.File_GetFileExtByPath(file_path)
		ext = ALittle.String_Upper(ext)
		local file = carp.CarpLocalFile()
		file:SetPath(file_path)
		Lua.Assert(file:Load(false), "IDEExport:PackagePath, 文件加载失败:" .. file_path)
		if crypt_mode then
			file:Encrypt(nil)
		end
		ALittle.File_MakeDeepDir(ALittle.File_GetFilePathByPath(dst_path .. rel_path))
		file:Save(dst_path .. rel_path)
		local new_attr = {}
		new_attr.attr = attr
		new_attr.md5 = ALittle.File_Md5(dst_path .. rel_path)
		new_attr.file_type = file_type
		new_attr.file_path = file_type .. rel_path
		out_file_map[file_path] = new_attr
		file:Clear()
	end
	return out_file_map
end

function ALittleIDE.IDEExport:PackageCommon(export_path, project_path, project_name, platform, is_plugin)
	ALittle.Log("========PackageCommon:" .. project_path .. "========")
	Lua.Assert(ALittle.File_GetFileAttr(project_path) ~= nil, "项目文件夹不存在:" .. project_path)
	if ALittle.File_GetFileAttr(export_path) == nil then
		ALittle.File_MakeDeepDir(export_path)
	end
	local export_common_path = export_path .. "/" .. project_name
	ALittle.File_DeleteDeepDir(export_common_path)
	if ALittle.File_GetFileAttr(export_common_path) == nil then
		ALittle.File_MakeDeepDir(export_common_path)
	end
	self:GenerateAtlas(project_path .. "/Texture")
	local file_list = {}
	local count = 0
	local file_info = nil
	if platform ~= "Web" and platform ~= "WeChat" then
		file_info = {}
		file_info.path = "Font"
		file_info.crypt_mode = false
		count = count + 1
		file_list[count] = file_info
	end
	file_info = {}
	file_info.path = "Other"
	file_info.crypt_mode = false
	count = count + 1
	file_list[count] = file_info
	file_info = {}
	file_info.path = "Tile"
	file_info.crypt_mode = false
	count = count + 1
	file_list[count] = file_info
	if platform == "Web" or platform == "WeChat" then
		file_info = {}
		file_info.path = "JSScript"
		file_info.crypt_mode = false
		count = count + 1
		file_list[count] = file_info
	else
		file_info = {}
		file_info.path = "Script"
		file_info.crypt_mode = true
		count = count + 1
		file_list[count] = file_info
	end
	file_info = {}
	file_info.path = "Sound"
	file_info.crypt_mode = false
	count = count + 1
	file_list[count] = file_info
	if platform == "Web" or platform == "WeChat" then
		file_info = {}
		file_info.path = "Texture"
		file_info.crypt_mode = false
		count = count + 1
		file_list[count] = file_info
		local all_in_one = {}
		local map = ALittle.File_GetFileAttrByDir(ALittle.File_BaseFilePath() .. "Module/" .. project_name .. "/UI")
		for path, _ in ___pairs(map) do
			local json = ALittle.File_ReadJsonFromStdFile(path)
			for name, o in ___pairs(json) do
				all_in_one[name] = o
			end
		end
		ALittle.File_MakeDeepDir(ALittle.File_BaseFilePath() .. "Module/" .. project_name .. "/JSUI")
		ALittle.File_WriteJsonFromStdFile(all_in_one, ALittle.File_BaseFilePath() .. "Module/" .. project_name .. "/JSUI/ui_all_in_one.json")
		file_info = {}
		file_info.path = "JSUI"
		file_info.crypt_mode = false
		count = count + 1
		file_list[count] = file_info
	else
		file_info = {}
		file_info.path = "Texture"
		file_info.crypt_mode = true
		count = count + 1
		file_list[count] = file_info
		file_info = {}
		file_info.path = "UI"
		file_info.crypt_mode = true
		count = count + 1
		file_list[count] = file_info
	end
	if ALittle.File_GetFileAttr(project_path .. "/NoCrypt.ali") == nil then
		for k, v in ___ipairs(file_list) do
			v.crypt_mode = false
		end
	end
	local map_list = {}
	count = 0
	for k, v in ___ipairs(file_list) do
		local result = self:PackagePath(project_path .. "/" .. v.path, export_common_path .. "/" .. v.path, v.path, v.crypt_mode)
		if result ~= nil then
			count = count + 1
			map_list[count] = result
		end
	end
	if not is_plugin then
		if platform == "Web" or platform == "WeChat" then
			local result = self:PackagePath(ALittle.File_BaseFilePath() .. "Module/ALittleIDE/Other/GameLibrary/Core/JSNative", export_common_path .. "/JSNative", "JSNative", false)
			if result ~= nil then
				count = count + 1
				map_list[count] = result
			end
			result = self:PackagePath(ALittle.File_BaseFilePath() .. "Module/ALittleIDE/Other/GameLibrary/Std/JSNative", export_common_path .. "/JSNative", "JSNative", false)
			if result ~= nil then
				count = count + 1
				map_list[count] = result
			end
			result = self:PackagePath(ALittle.File_BaseFilePath() .. "Module/ALittleIDE/Other/GameLibrary/CEngine/JSNative", export_common_path .. "/JSNative", "JSNative", false)
			if result ~= nil then
				count = count + 1
				map_list[count] = result
			end
		else
			local result = self:PackagePath(ALittle.File_BaseFilePath() .. "Module/ALittleIDE/Other/GameLibrary/Core/Script", export_common_path .. "/Core", "Core", true)
			if result ~= nil then
				count = count + 1
				map_list[count] = result
			end
			result = self:PackagePath(ALittle.File_BaseFilePath() .. "Module/ALittleIDE/Other/GameLibrary/Std/Script", export_common_path .. "/Std", "Std", true)
			if result ~= nil then
				count = count + 1
				map_list[count] = result
			end
			result = self:PackagePath(ALittle.File_BaseFilePath() .. "Module/ALittleIDE/Other/GameLibrary/CEngine/Script", export_common_path .. "/CEngine", "CEngine", true)
			if result ~= nil then
				count = count + 1
				map_list[count] = result
			end
		end
	end
	return map_list
end

function ALittleIDE.IDEExport:PackageVersion(package_info)
	local ___COROUTINE = coroutine.running()
	ALittle.Log("========PackageVersion========")
	if ALittleIDE.g_IDEWebLoginManager:IsLogin() then
		g_AUITool:ShowAlertDialog("提示", "正在请求新的版本号")
		local param = {}
		param.__account_id = ALittleIDE.g_IDEWebLoginManager.account_id
		param.__session_id = ALittleIDE.g_IDEWebLoginManager.session_id
		local client = ALittle.CreateHttpSender(ALittleIDE.g_IDEWebLoginManager.http_ip, ALittleIDE.g_IDEWebLoginManager.http_port)
		local error, result = ALittle.IHttpSender.Invoke("VersionServer.QNewUpdateTimeIndex", client, param)
		self:HandleAskNewUpdateTimeIndex(error, result, package_info, true)
	else
		self:HandleAskNewUpdateTimeIndexImpl(package_info, false, ALittle.Time_GetCurTime(), 0)
	end
end

function ALittleIDE.IDEExport:HandleAskNewUpdateTimeIndex(error, result, package_info, is_login)
	local ___COROUTINE = coroutine.running()
	g_AUITool:HideAlertDialog()
	if error ~= nil then
		g_AUITool:ShowNotice("错误", "新版本号获取失败:" .. error)
		return
	end
	self:HandleAskNewUpdateTimeIndexImpl(package_info, is_login, result.update_time, result.update_index)
end

function ALittleIDE.IDEExport:HandleAskNewUpdateTimeIndexImpl(package_info, is_login, update_time, update_index)
	local ___COROUTINE = coroutine.running()
	if is_login then
		g_AUITool:ShowAlertDialog("提示", "正在请求CurVersion.db的文件的位置")
		local param = {}
		param.__account_id = ALittleIDE.g_IDEWebLoginManager.account_id
		param.__session_id = ALittleIDE.g_IDEWebLoginManager.session_id
		param.platform = package_info.platform
		param.module_name = package_info.project_name
		local client = ALittle.CreateHttpSender(ALittleIDE.g_IDEWebLoginManager.http_ip, ALittleIDE.g_IDEWebLoginManager.http_port)
		local error, result = ALittle.IHttpSender.Invoke("VersionServer.QNewCurVersion", client, param)
		self:HandleQueryNewCurVersion(error, result, package_info, is_login, update_time, update_index)
	else
		self:HandleQueryNewCurVersionImpl(package_info, is_login, update_time, update_index, nil)
	end
end

function ALittleIDE.IDEExport:HandleQueryNewCurVersion(error, result, package_info, is_login, update_time, update_index)
	local ___COROUTINE = coroutine.running()
	g_AUITool:HideAlertDialog()
	if error ~= nil then
		g_AUITool:ShowNotice("错误", "CurVersion.db的文件的位置获取失败:" .. error)
		return
	end
	if result.version_info == nil or result.version_info.version_id == nil or result.version_info.version_id == "" then
		self:HandleQueryNewCurVersionImpl(package_info, is_login, update_time, update_index, false)
	else
		g_AUITool:ShowAlertDialog("提示", "下载最新的版本文件")
		ALittle.File_MakeDeepDir(package_info.project_path .. "/Export")
		local target_path = package_info.project_path .. "/Export" .. "/CurVersionOld_" .. package_info.platform .. ".db"
		local param = {}
		param.platform = package_info.platform
		param.version_id = result.version_info.version_id
		param.file_path = "CurVersion.db"
		local client = ALittle.CreateHttpFileSender(result.http_ip, result.http_port, target_path, 0)
		error = ALittle.IHttpFileSender.InvokeDownload("VersionServer.QDownloadVersionFile", client, param)
		self:HandleDownloadCurVersion(error, package_info, is_login, update_time, update_index)
	end
end

function ALittleIDE.IDEExport:HandleDownloadCurVersion(error, package_info, is_login, update_time, update_index)
	if error ~= nil then
		g_AUITool:HideAlertDialog()
		g_AUITool:ShowNotice("错误", "最新版本文件下载失败:" .. error)
		return
	end
	g_AUITool:HideAlertDialog()
	self:HandleQueryNewCurVersionImpl(package_info, is_login, update_time, update_index, true)
end

function ALittleIDE.IDEExport:HandleQueryNewCurVersionImpl(package_info, is_login, update_time, update_index, has_db_version)
	g_AUITool:ShowAlertDialog("提示", "正在生成版本")
	ALittle.System_Render()
	local small_version_time = update_time
	local small_version_index = update_index
	local version_info = nil
	if has_db_version then
		g_AUITool:ShowAlertDialog("提示", "获取上一个版本的信息")
		ALittle.System_Render()
		local db_version_path = package_info.project_path .. "/Export/CurVersionOld_" .. package_info.platform .. ".db"
		local sqlite = sqlite3.open(db_version_path)
		if sqlite == nil then
			g_AUITool:ShowNotice("错误", "CurVersion.db文件打开失败")
			return
		end
		version_info = {}
		local stmt = sqlite:prepare("SELECT * FROM BigVersion")
		if stmt == nil then
			sqlite:close()
			g_AUITool:ShowNotice("错误", "CurVersion.db中BigVersion读取失败")
			return
		end
		for row in stmt:nrows() do
			version_info.big_version = row
		end
		stmt:reset()
		stmt = sqlite:prepare("SELECT * FROM SmallVersion")
		if stmt == nil then
			sqlite:close()
			g_AUITool:ShowNotice("错误", "CurVersion.db中SmallVersion读取失败")
			return
		end
		version_info.small_version = {}
		for row in stmt:nrows() do
			version_info.small_version[row.c_file_path] = row
		end
		stmt:reset()
		sqlite:close()
	end
	g_AUITool:ShowAlertDialog("提示", "打包当前版本")
	ALittle.System_Render()
	ALittle.File_DeleteDeepDir(package_info.project_path .. "/Export/Common")
	local error, version_info_list = Lua.TCall(self.PackageCommon, self, package_info.project_path .. "/Export/Common", package_info.project_path, package_info.project_name, package_info.platform, false)
	if error ~= nil then
		g_AUITool:ShowNotice("错误", "PackageCommon 调用失败:" .. error)
		return
	end
	local plugin_list = ALittle.String_Split(package_info.version_info.plugin_list, ",")
	for index, plugin in ___ipairs(plugin_list) do
		local plugin_error, _ = Lua.TCall(self.PackageCommon, self, package_info.project_path .. "/Export/Common", ALittle.File_BaseFilePath() .. "Module/" .. plugin, plugin, package_info.platform, true)
		if plugin_error ~= nil then
			g_AUITool:ShowNotice("错误", "PackageCommon 调用失败:" .. plugin_error)
			return
		end
	end
	if package_info.platform == "Android" then
		ALittle.File_MakeDir(package_info.export_path .. "/assets/Module")
		ALittle.File_SaveFile(package_info.export_path .. "/assets/Module/Enter.ali", package_info.project_name, -1)
	else
		ALittle.File_MakeDir(package_info.export_path .. "/Module")
		ALittle.File_SaveFile(package_info.export_path .. "/Module/Enter.ali", package_info.project_name, -1)
	end
	ALittle.File_CopyDeepDir(package_info.project_path .. "/Export/Common", package_info.export_module_base_path)
	local submit_info = {}
	submit_info.upload_list = {}
	local update_list_count = 0
	g_AUITool:ShowAlertDialog("提示", "生成新的CurVersion.db")
	ALittle.System_Render()
	local package_notice = ""
	ALittle.File_DeleteFile(package_info.export_module_path .. "/CurVersion.db")
	local sqlite = sqlite3.open(package_info.export_module_path .. "/CurVersion.db")
	if sqlite ~= nil then
		local sql = "CREATE TABLE IF NOT EXISTS [BigVersion] ("
		sql = sql .. "[c_big_version] [nvarchar](255) NOT NULL default '',"
		sql = sql .. "[c_install_version] [nvarchar](255) NOT NULL default '',"
		sql = sql .. "[c_db_version] [nvarchar](255) NOT NULL default ''"
		sql = sql .. ")"
		sqlite:exec(sql)
		sql = "CREATE TABLE IF NOT EXISTS [VersionLog] ("
		sql = sql .. "[c_content] [nvarchar](255) NOT NULL default '',"
		sql = sql .. "[c_create_time] [int] NOT NULL default 0,"
		sql = sql .. "[c_create_index] [int] NOT NULL default 0"
		sql = sql .. ")"
		sqlite:exec(sql)
		local new_log = ALittle.String_Split(package_info.install_info.new_log, "\n")
		local create_time = ALittle.Time_GetCurTime()
		local create_index = 0
		for k, v in ___ipairs(new_log) do
			if v ~= "" then
				sqlite:exec("INSERT INTO VersionLog (c_content,c_create_time,c_create_index) VALUES ('" .. v .. "'," .. create_time .. "," .. create_index .. ")")
				create_index = create_index + 1
			end
		end
		sql = "CREATE TABLE IF NOT EXISTS [SmallVersion] ("
		sql = sql .. "[c_file_path] [nvarchar](255) UNIQUE NOT NULL default '',"
		sql = sql .. "[c_file_size] [int] NOT NULL default 0,"
		sql = sql .. "[c_type] [nvarchar](255) NOT NULL default '',"
		sql = sql .. "[c_md5] [nvarchar](32) NOT NULL default '',"
		sql = sql .. "[c_update_time] [int] NOT NULL default 0,"
		sql = sql .. "[c_update_index] [int] NOT NULL default 0,"
		sql = sql .. "[c_is_delete] [int] NOT NULL default 0"
		sql = sql .. ")"
		sqlite:exec(sql)
		sqlite:exec("CREATE INDEX IF NOT EXISTS update_time_index ON SmallVersion (c_update_time);")
		sqlite:exec("BEGIN;")
		local has_change = false
		local change_count = 0
		local add_count = 0
		local delete_count = 0
		for k, map in ___ipairs(version_info_list) do
			for file_path, attr in ___pairs(map) do
				if version_info == nil then
					sqlite:exec("INSERT INTO SmallVersion (c_file_path,c_file_size,c_type,c_md5,c_update_time,c_update_index,c_is_delete) VALUES ('" .. attr.file_path .. "'," .. attr.attr.size .. ",'" .. attr.file_type .. "','" .. attr.md5 .. "'," .. update_time .. "," .. update_index .. ",0)")
					add_count = add_count + 1
					has_change = true
				else
					local old_attr = version_info.small_version[attr.file_path]
					if old_attr == nil or old_attr.c_md5 ~= attr.md5 or old_attr.c_is_delete ~= 0 then
						sqlite:exec("INSERT INTO SmallVersion (c_file_path,c_file_size,c_type,c_md5,c_update_time,c_update_index,c_is_delete) VALUES ('" .. attr.file_path .. "'," .. attr.attr.size .. ",'" .. attr.file_type .. "','" .. attr.md5 .. "'," .. update_time .. "," .. update_index .. ",0)")
						if old_attr == nil or old_attr.c_is_delete ~= 0 then
							add_count = add_count + 1
						else
							change_count = change_count + 1
						end
						has_change = true
					else
						sqlite:exec("INSERT INTO SmallVersion (c_file_path,c_file_size,c_type,c_md5,c_update_time,c_update_index,c_is_delete) VALUES ('" .. attr.file_path .. "'," .. attr.attr.size .. ",'" .. attr.file_type .. "','" .. attr.md5 .. "'," .. old_attr.c_update_time .. "," .. old_attr.c_update_index .. ",0)")
					end
					version_info.small_version[attr.file_path] = nil
				end
				update_list_count = update_list_count + 1
				submit_info.upload_list[update_list_count] = attr.file_path
			end
		end
		if version_info ~= nil then
			for k, v in ___pairs(version_info.small_version) do
				if v.c_is_delete ~= 0 then
					sqlite:exec("INSERT INTO SmallVersion (c_file_path,c_file_size,c_type,c_md5,c_update_time,c_update_index,c_is_delete) VALUES ('" .. v.c_file_path .. "'," .. v.c_file_size .. ",'" .. v.c_type .. "','" .. v.c_md5 .. "'," .. v.c_update_time .. "," .. v.c_update_index .. ",1)")
				else
					sqlite:exec("INSERT INTO SmallVersion (c_file_path,c_file_size,c_type,c_md5,c_update_time,c_update_index,c_is_delete) VALUES ('" .. v.c_file_path .. "'," .. v.c_file_size .. ",'" .. v.c_type .. "','" .. v.c_md5 .. "'," .. update_time .. "," .. update_index .. ",1)")
					delete_count = delete_count + 1
					has_change = true
				end
			end
		end
		local db_version = ALittle.Time_GetCurDate()
		if version_info ~= nil then
			db_version = version_info.big_version.c_db_version
		end
		if db_version == nil then
			db_version = ALittle.Time_GetCurDate()
		end
		if version_info ~= nil and version_info.big_version.c_install_version < package_info.version_info.install_version then
			has_change = true
		end
		sqlite:exec("INSERT INTO BigVersion (c_big_version,c_install_version,c_db_version) VALUES ('" .. package_info.version_info.big_version .. "','" .. package_info.version_info.install_version .. "','" .. db_version .. "')")
		sqlite:exec("COMMIT;")
		local stmt = sqlite:prepare("SELECT c_update_time,c_update_index FROM SmallVersion ORDER BY c_update_time DESC, c_update_index DESC LIMIT 1")
		if stmt ~= nil then
			for row in stmt:nrows() do
				small_version_time = row.c_update_time
				small_version_index = row.c_update_index
				break
			end
			stmt:reset()
		end
		sqlite:exec("VACUUM;")
		sqlite:close()
		ALittle.File_CopyFile(package_info.export_module_path .. "/CurVersion.db", package_info.export_module_path .. "/CurVersionNoDelete.db")
		local sqlite_no_delete = sqlite3.open(package_info.export_module_path .. "/CurVersionNoDelete.db")
		if sqlite_no_delete == nil then
			g_AUITool:ShowNotice("错误", "CurVersionNoDelete.db文件生成失败:" .. package_info.export_module_path .. "/CurVersionNoDelete.db")
			return
		end
		sqlite_no_delete:exec("DELETE FROM SmallVersion WHERE c_is_delete=1")
		db_version = ALittle.Time_GetCurDate()
		sqlite_no_delete:exec("UPDATE BigVersion SET c_db_version='" .. db_version .. "'")
		sqlite_no_delete:exec("VACUUM;")
		sqlite_no_delete:close()
		local sqlite_attr = ALittle.File_GetFileAttr(package_info.export_module_path .. "/CurVersion.db")
		local sqlite_no_delete_attr = ALittle.File_GetFileAttr(package_info.export_module_path .. "/CurVersionNoDelete.db")
		package_notice = "\n文件添加数量:" .. add_count .. "\n文件删除数量:" .. delete_count .. "\n文件修改数量:" .. change_count .. "\n原始DB文件大小:" .. sqlite_attr.size .. "\n优化DB文件大小:" .. sqlite_no_delete_attr.size
		local need_use_no_delete = false
		if sqlite_attr.size < 200 * 1024 then
		elseif sqlite_attr.size < 500 * 1024 then
			if sqlite_no_delete_attr.size / sqlite_attr.size < 0.8 then
				need_use_no_delete = true
			end
		else
			if sqlite_no_delete_attr.size / sqlite_attr.size < 0.7 then
				need_use_no_delete = true
			end
		end
		if need_use_no_delete then
			ALittle.File_DeleteFile(package_info.export_module_path .. "/CurVersion.db")
			ALittle.File_RenameFile(package_info.export_module_path .. "/CurVersionNodelete.db", package_info.export_module_path .. "/CurVersion.db")
		else
			ALittle.File_DeleteFile(package_info.export_module_path .. "/CurVersionNodelete.db")
		end
		if has_change == false then
			g_AUITool:HideAlertDialog()
			g_AUITool:ShowNotice("提示", "当前没有任何变化，不需要制作版本")
			return
		end
	else
		g_AUITool:ShowNotice("错误", "CurVersion.db文件生成失败:" .. package_info.export_module_path .. "/CurVersion.db")
		return
	end
	g_AUITool:ShowAlertDialog("提示", "开始打包安装包")
	ALittle.System_Render()
	local install_name = nil
	if package_info.platform == "Windows" then
		install_name = self:GenerateExe(package_info)
	elseif package_info.platform == "Android" then
		install_name = self:GenerateApk(package_info)
	elseif package_info.platform == "iOS" then
		install_name = self:GenerateIpa(package_info)
	elseif package_info.platform == "Web" then
		install_name = self:GenerateWeb(package_info)
	elseif package_info.platform == "WeChat" then
		install_name = self:GenerateWeChat(package_info)
	elseif package_info.platform == "Emscripten" then
		install_name = self:GenerateEmscripten(package_info)
	end
	submit_info.project_path = package_info.project_path
	submit_info.export_module_path = package_info.export_module_path
	submit_info.is_login = is_login
	submit_info.module_name = package_info.project_name
	submit_info.platform = package_info.platform
	submit_info.small_version_time = small_version_time
	submit_info.small_version_index = small_version_index
	submit_info.update_time = update_time
	submit_info.update_index = update_index
	submit_info.big_version = package_info.version_info.big_version
	submit_info.version_number = package_info.version_info.version_number
	submit_info.install_version = package_info.version_info.install_version
	submit_info.plugin_list = package_info.version_info.plugin_list
	submit_info.log_list = ALittle.String_Split(package_info.install_info.new_log, "\n")
	submit_info.install_name = install_name
	local install_attr = ALittle.File_GetFileAttr(package_info.project_path .. "/Export/" .. install_name)
	if install_attr == nil then
		g_AUITool:HideAlertDialog()
		g_AUITool:ShowNotice("提示", "版本生成失败")
		return
	end
	submit_info.install_size = install_attr.size
	ALittle.File_WriteJsonToFile(submit_info, package_info.project_path .. "/Export/SubmitInfo_" .. package_info.platform .. ".json")
	ALittle.Log("版本生成成功")
	g_AUITool:HideAlertDialog()
	g_AUITool:ShowNotice("提示", "版本生成成功" .. package_notice)
end

function ALittleIDE.IDEExport:SubmitPlatform(project_name, platform)
	local ___COROUTINE = coroutine.running()
	if self._is_in_submit == true then
		self._submit_dialog.visible = true
		return
	end
	ALittle.Log("==================SubmitPlatform:" .. platform .. "==================")
	if ALittleIDE.g_IDEWebLoginManager:IsLogin() == false then
		g_AUITool:ShowNotice("错误", "您还未登录，无法上传版本")
		return
	end
	local project_path = ALittle.File_BaseFilePath() .. "Module/" .. project_name
	local submit_info_path = project_path .. "/Export/SubmitInfo_" .. platform .. ".json"
	if ALittle.File_GetFileAttr(submit_info_path) == nil then
		g_AUITool:ShowNotice("错误", "版本PackageInfo_" .. platform .. ".json不存在")
		return
	end
	local submit_info = ALittle.File_ReadJsonFromFile(submit_info_path)
	if submit_info == nil then
		g_AUITool:ShowNotice("错误", "PackageInfo_" .. platform .. ".json文件解析失败")
		return
	end
	if submit_info.is_login ~= true then
		g_AUITool:ShowNotice("错误", "当前打包的版本不是在登录的状态下打包的，请登录之后重新打包")
		return
	end
	if submit_info.completed == true then
		g_AUITool:ShowNotice("错误", "版本已经上传成功了，不能重复上传")
		return
	end
	if submit_info.version_id == nil then
		g_AUITool:ShowAlertDialog("提示", "正在创建一个新的版本")
		local param = {}
		param.__account_id = ALittleIDE.g_IDEWebLoginManager.account_id
		param.__session_id = ALittleIDE.g_IDEWebLoginManager.session_id
		param.module_name = submit_info.module_name
		param.platform = submit_info.platform
		param.big_version = submit_info.big_version
		param.version_number = submit_info.version_number
		param.install_version = submit_info.install_version
		param.plugin_list = submit_info.plugin_list
		param.install_size = submit_info.install_size
		param.log_list = submit_info.log_list
		param.small_version_time = submit_info.small_version_time
		param.small_version_index = submit_info.small_version_index
		param.update_time = submit_info.update_time
		param.update_index = submit_info.update_index
		local client = ALittle.CreateHttpSender(ALittleIDE.g_IDEWebLoginManager.http_ip, ALittleIDE.g_IDEWebLoginManager.http_port)
		local error, result = ALittle.IHttpSender.Invoke("VersionServer.QNewVersionInfo", client, param)
		self:HandleNewVersionInfo(error, result, submit_info)
	else
		self:HandleNewVersionInfoImpl(submit_info)
	end
end

function ALittleIDE.IDEExport:HandleNewVersionInfo(error, result, submit_info)
	local ___COROUTINE = coroutine.running()
	g_AUITool:HideAlertDialog()
	if error ~= nil then
		g_AUITool:ShowNotice("错误", "版本创建失败:" .. error)
		return
	end
	submit_info.version_id = result.version_id
	ALittle.File_WriteJsonToFile(submit_info, submit_info.project_path .. "/Export/SubmitInfo_" .. submit_info.platform .. ".json")
	self:HandleNewVersionInfoImpl(submit_info)
end

function ALittleIDE.IDEExport:HandleNewVersionInfoImpl(submit_info)
	local ___COROUTINE = coroutine.running()
	if self._submit_dialog == nil then
		self._submit_dialog = ALittleIDE.g_Control:CreateControl("ide_submit_dialog", self)
		A_LayerManager:AddToModal(self._submit_dialog)
	end
	self._submit_dialog.visible = true
	self._submit_process_bar.width = 0
	self._submit_cancel_btn.visible = true
	self._is_in_submit = true
	local upload_index = 0
	local total_count = ALittle.List_Len(submit_info.upload_list) + 2
	local param = {}
	param.__account_id = ALittleIDE.g_IDEWebLoginManager.account_id
	param.__session_id = ALittleIDE.g_IDEWebLoginManager.session_id
	param.platform = submit_info.platform
	param.module_name = submit_info.module_name
	param.version_id = submit_info.version_id
	local error = nil
	local result = nil
	for k, file_path in ___ipairs(submit_info.upload_list) do
		upload_index = upload_index + 1
		self._submit_content.text = "正在上传:" .. upload_index .. "/" .. total_count .. "\n" .. submit_info.export_module_path .. "/" .. file_path
		param.file_path = file_path
		param.__account_id = ALittleIDE.g_IDEWebLoginManager.account_id
		param.__session_id = ALittleIDE.g_IDEWebLoginManager.session_id
		local repeat_count = 0
		while repeat_count < 1 do
			repeat_count = repeat_count + 1
			self._submit_client = ALittle.CreateHttpFileSender(ALittleIDE.g_IDEWebLoginManager.http_ip, ALittleIDE.g_IDEWebLoginManager.http_port, submit_info.export_module_path .. "/" .. file_path, 0, Lua.Bind(self.HandleSubmitVersionUpload, self, upload_index, total_count))
			error = ALittle.IHttpFileSender.InvokeUpload("VersionServer.QUploadVersionFile", self._submit_client, param)
			if error == nil then
				break
			end
		end
		if error ~= nil then
			self._submit_content.text = "版本上传失败:" .. error
			self._is_in_submit = false
			return
		end
	end
	do
		upload_index = upload_index + 1
		self._submit_content.text = "正在上传:" .. upload_index .. "/" .. total_count .. "\n" .. submit_info.project_path .. "/Export/" .. submit_info.install_name
		param.file_path = submit_info.install_name
		param.__account_id = ALittleIDE.g_IDEWebLoginManager.account_id
		param.__session_id = ALittleIDE.g_IDEWebLoginManager.session_id
		local repeat_count = 0
		while repeat_count < 100 do
			repeat_count = repeat_count + 1
			self._submit_client = ALittle.CreateHttpFileSender(ALittleIDE.g_IDEWebLoginManager.http_ip, ALittleIDE.g_IDEWebLoginManager.http_port, submit_info.project_path .. "/Export/" .. submit_info.install_name, 0, Lua.Bind(self.HandleSubmitVersionUpload, self, upload_index, total_count))
			error = ALittle.IHttpFileSender.InvokeUpload("VersionServer.QUploadVersionFile", self._submit_client, param)
			if error == nil then
				break
			end
		end
		if error ~= nil then
			self._submit_content.text = "版本上传失败:" .. error
			self._is_in_submit = false
			return
		end
	end
	do
		upload_index = upload_index + 1
		self._submit_content.text = "正在上传:" .. upload_index .. "/" .. total_count .. "\n" .. submit_info.export_module_path .. "/CurVersion.db"
		param.file_path = "CurVersion.db"
		param.__account_id = ALittleIDE.g_IDEWebLoginManager.account_id
		param.__session_id = ALittleIDE.g_IDEWebLoginManager.session_id
		local repeat_count = 0
		while repeat_count < 100 do
			repeat_count = repeat_count + 1
			self._submit_client = ALittle.CreateHttpFileSender(ALittleIDE.g_IDEWebLoginManager.http_ip, ALittleIDE.g_IDEWebLoginManager.http_port, submit_info.export_module_path .. "/CurVersion.db", 0, Lua.Bind(self.HandleSubmitVersionUpload, self, upload_index, total_count))
			error = ALittle.IHttpFileSender.InvokeUpload("VersionServer.QUploadVersionFile", self._submit_client, param)
			if error == nil then
				break
			end
		end
		if error ~= nil then
			self._submit_content.text = "版本上传失败:" .. error
			self._is_in_submit = false
			return
		end
	end
	self._submit_client = nil
	self._submit_content.text = "版本上传成功"
	self._submit_cancel_btn.visible = false
	self._is_in_submit = false
	submit_info.completed = true
	ALittle.File_WriteJsonToFile(submit_info, submit_info.project_path .. "/Export/SubmitInfo_" .. submit_info.platform .. ".json")
end

function ALittleIDE.IDEExport:HandleSubmitVersionCancel(event)
	if self._submit_client ~= nil then
		self._submit_client:Stop()
		self._submit_client = nil
	end
	self._submit_dialog.visible = false
end

function ALittleIDE.IDEExport:HandleSubmitVersionUpload(upload_index, total_count, file)
	local file_path = file:GetFilePath()
	local cur_size = file:GetCurSize()
	local total_size = file:GetTotalSize()
	self._submit_content.text = "正在上传:" .. upload_index .. "/" .. total_count .. "\n" .. file_path
	self._submit_process_bar.x = self._submit_process_bg.x
	self._submit_process_bar.width = (cur_size / total_size) * self._submit_process_bg.width
end

function ALittleIDE.IDEExport:GenerateExe(package_info)
	ALittle.Log("==================GenerateExe:" .. package_info.project_name .. "==================")
	if ALittle.File_GetFileAttr(package_info.project_path) == nil then
		ALittle.Log("IDEExport:GenerateExe project_path is not exist:", package_info.project_path)
		return nil
	end
	ALittle.File_CopyFile("ALittleClient.exe", "Export/Windows/Engine/ALittleClient.exe")
	ALittle.File_CopyFile("ALittleClientWin.exe", "Export/Windows/Engine/ALittleClientWin.exe")
	ALittle.File_CopyFile("ALittleServer.exe", "Export/Windows/Engine/ALittleServer.exe")
	ALittle.File_CopyFile("SDL2.dll", "Export/Windows/Engine/SDL2.dll")
	ALittle.File_CopyFile("libcrypto-1_1-x64.dll", "Export/Windows/Engine/libcrypto-1_1-x64.dll")
	ALittle.File_CopyFile("libssl-1_1-x64.dll", "Export/Windows/Engine/libssl-1_1-x64.dll")
	ALittle.File_CopyFile("libtcmalloc_minimal.dll", "Export/Windows/Engine/libtcmalloc_minimal.dll")
	ALittle.File_CopyFile("libmysql.dll", "Export/Windows/Engine/libmysql.dll")
	ALittle.File_CopyDeepDir("Export/Windows/Engine", package_info.export_path)
	local install_ico = package_info.project_path .. "/Icon/install.ico"
	if ALittle.File_GetFileAttr(install_ico) == nil then
		ALittle.File_CopyFile(ALittle.File_BaseFilePath() .. "Export/Icon/install.ico", package_info.project_path .. "/Export/Windows/install.ico")
	else
		ALittle.File_CopyFile(install_ico, package_info.project_path .. "/Export/Windows/install.ico")
	end
	local template = ALittle.File_ReadTextFromFile(ALittle.File_BaseFilePath() .. "Export/Windows/Tool/ExportTemplate.iss")
	if package_info.install_info.install_name == nil then
		ALittle.Log("IDEExport:GenerateExe install_name is null")
		return nil
	end
	template = ALittle.String_Replace(template, "VERSION_NUMBER", package_info.version_info.version_number)
	local install_name_gbk = package_info.install_info.install_name
	template = ALittle.String_Replace(template, "INSTALL_NAME", install_name_gbk)
	local guid = ALittle.String_Md5(package_info.project_name .. "-" .. package_info.install_info.install_name)
	guid = ALittle.String_Upper(guid)
	guid = ALittle.String_Sub(guid, 1, 8) .. "-" .. ALittle.String_Sub(guid, 9, 13) .. "-" .. ALittle.String_Sub(guid, 14, 18) .. "-" .. ALittle.String_Sub(guid, 19, 23) .. "-" .. ALittle.String_Sub(guid, 24, 32)
	template = ALittle.String_Replace(template, "INSTALL_GUID", guid)
	if package_info.install_info.auto_start == true then
		template = template .. "[Registry]\nRoot: HKLM; Subkey: \"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\"; ValueType: string; ValueName: \"" .. install_name_gbk .. "\"; ValueData: \"{app}\\ALittleClientWin.exe\""
	end
	if ALittle.File_SaveFile(package_info.project_path .. "/Export/Install.iss", template, -1) == false then
		return nil
	end
	os.execute("call \"Export/Windows/Tool/Inno Setup 5/iscc\" /Q " .. package_info.project_path .. "/Export/Install.iss")
	return "Install.exe"
end

function ALittleIDE.IDEExport:GenerateApk(package_info)
	ALittle.Log("==================GenerateApk:" .. package_info.project_name .. "==================")
	if ALittle.File_GetFileAttr(package_info.project_path) == nil then
		ALittle.Log("IDEExport:GenerateApk project_path is not exist:", package_info.project_path)
		return nil
	end
	if package_info.install_info.package_name == nil then
		ALittle.Log("IDEExport:GenerateApk package_name is null")
		return nil
	end
	if package_info.install_info.install_name == nil then
		ALittle.Log("IDEExport:GenerateApk install_name is null")
		return nil
	end
	local file = carp.CarpLocalFile()
	file:SetPath(ALittle.File_BaseFilePath() .. "Export/Android/AndroidManifestTemplate.xml")
	if file:Load(false) then
		local content = file:GetContent()
		content = ALittle.String_Replace(content, "abcd@package_name@abcd", package_info.install_info.package_name)
		content = ALittle.String_Replace(content, "abcd@version_number@abcd", package_info.version_info.version_number)
		content = ALittle.String_Replace(content, "abcd@app_name@abcd", package_info.install_info.install_name)
		if package_info.install_info.screen == "竖屏" then
			content = ALittle.String_Replace(content, "abcd@screen@abcd", "portrait")
		elseif package_info.install_info.screen == "横屏" then
			content = ALittle.String_Replace(content, "abcd@screen@abcd", "landscape")
		else
			content = ALittle.String_Replace(content, "abcd@screen@abcd", "sensor")
		end
		if package_info.install_info.fullscreen then
			content = ALittle.String_Replace(content, "abcd@fullscreen@abcd", "style/Theme.NoTitleBar.Fullscreen")
		else
			content = ALittle.String_Replace(content, "abcd@fullscreen@abcd", "style/Theme.NoTitleBar")
		end
		ALittle.File_SaveFile(package_info.project_path .. "/Export/Android/AndroidManifest.xml", content, -1)
	end
	ALittle.File_CopyFile(ALittle.File_BaseFilePath() .. "Export/Android/ExportAPK.bat", package_info.project_path .. "/Export/Android/ExportAPK.bat")
	ALittle.File_MakeDeepDir(package_info.project_path .. "/Export/Android/assets")
	ALittle.File_CopyDeepDir(ALittle.File_BaseFilePath() .. "Export/Android/assets", package_info.project_path .. "/Export/Android/assets")
	ALittle.File_MakeDeepDir(package_info.project_path .. "/Export/Android/res")
	ALittle.File_CopyDeepDir(ALittle.File_BaseFilePath() .. "Export/Android/res", package_info.project_path .. "/Export/Android/res")
	local install_png = package_info.project_path .. "/Icon/install.png"
	if ALittle.File_GetFileAttr(install_png) == nil then
		install_png = ALittle.File_BaseFilePath() .. "Export/Icon/install.png"
	end
	local surface = carp.LoadCarpSurface(install_png)
	if surface ~= nil then
		local surface_width = carp.GetCarpSurfaceWidth(surface)
		local surface_height = carp.GetCarpSurfaceHeight(surface)
		local new_surface = carp.CreateCarpSurface(24, 24)
		local new_surface_width = carp.GetCarpSurfaceWidth(new_surface)
		local new_surface_height = carp.GetCarpSurfaceHeight(new_surface)
		carp.CutBlitCarpSurface(surface, new_surface, "0,0," .. surface_width .. "," .. surface_height, "0,0," .. new_surface_width .. "," .. new_surface_height)
		carp.SaveCarpSurface(new_surface, package_info.project_path .. "/Export/Android/res/drawable-ldpi/icon.png")
		carp.FreeCarpSurface(new_surface)
		new_surface = carp.CreateCarpSurface(48, 48)
		new_surface_width = carp.GetCarpSurfaceWidth(new_surface)
		new_surface_height = carp.GetCarpSurfaceHeight(new_surface)
		carp.CutBlitCarpSurface(surface, new_surface, "0,0," .. surface_width .. "," .. surface_height, "0,0," .. new_surface_width .. "," .. new_surface_height)
		carp.SaveCarpSurface(new_surface, package_info.project_path .. "/Export/Android/res/drawable-mdpi/icon.png")
		carp.FreeCarpSurface(new_surface)
		new_surface = carp.CreateCarpSurface(72, 72)
		new_surface_width = carp.GetCarpSurfaceWidth(new_surface)
		new_surface_height = carp.GetCarpSurfaceHeight(new_surface)
		carp.CutBlitCarpSurface(surface, new_surface, "0,0," .. surface_width .. "," .. surface_height, "0,0," .. new_surface_width .. "," .. new_surface_height)
		carp.SaveCarpSurface(new_surface, package_info.project_path .. "/Export/Android/res/drawable-hdpi/icon.png")
		carp.FreeCarpSurface(new_surface)
		new_surface = carp.CreateCarpSurface(96, 96)
		new_surface_width = carp.GetCarpSurfaceWidth(new_surface)
		new_surface_height = carp.GetCarpSurfaceHeight(new_surface)
		carp.CutBlitCarpSurface(surface, new_surface, "0,0," .. surface_width .. "," .. surface_height, "0,0," .. new_surface_width .. "," .. new_surface_height)
		carp.SaveCarpSurface(new_surface, package_info.project_path .. "/Export/Android/res/drawable-xhdpi/icon.png")
		carp.FreeCarpSurface(new_surface)
		new_surface = carp.CreateCarpSurface(144, 144)
		new_surface_width = carp.GetCarpSurfaceWidth(new_surface)
		new_surface_height = carp.GetCarpSurfaceHeight(new_surface)
		carp.CutBlitCarpSurface(surface, new_surface, "0,0," .. surface_width .. "," .. surface_height, "0,0," .. new_surface_width .. "," .. new_surface_height)
		carp.SaveCarpSurface(new_surface, package_info.project_path .. "/Export/Android/res/drawable-xxhdpi/icon.png")
		carp.FreeCarpSurface(new_surface)
		carp.FreeCarpSurface(surface)
	end
	local package_name_list = ALittle.String_Split(package_info.install_info.package_name, ".")
	local default_src_path = package_info.project_path .. "/Export/Android/src/org/libsdl/app"
	ALittle.File_MakeDeepDir(default_src_path)
	ALittle.File_CopyDeepDir("Export/Android/src/org/libsdl/app", default_src_path)
	local package_src_path = package_info.project_path .. "/Export/Android/src/" .. ALittle.String_Join(package_name_list, "/")
	ALittle.File_MakeDeepDir(package_src_path)
	ALittle.File_CopyDeepDir("Export/Android/src/package_src", package_src_path)
	local javac_string = ""
	local java_file_map = {}
	ALittle.File_GetFileAttrByDir(default_src_path, java_file_map)
	for file_path, java_file in ___pairs(java_file_map) do
		javac_string = javac_string .. ALittle.String_Replace(file_path, package_info.project_path .. "/Export/Android/", "") .. "\n"
		local content = ALittle.File_ReadTextFromFile(file_path)
		content = ALittle.String_Replace(content, "abcd@package_name@abcd", package_info.install_info.package_name)
		ALittle.File_SaveFile(file_path, content, -1)
	end
	java_file_map = {}
	ALittle.File_GetFileAttrByDir(package_src_path, java_file_map)
	for file_path, java_file in ___pairs(java_file_map) do
		javac_string = javac_string .. ALittle.String_Replace(file_path, package_info.project_path .. "/Export/Android/", "") .. "\n"
		local content = ALittle.File_ReadTextFromFile(file_path)
		content = ALittle.String_Replace(content, "abcd@package_name@abcd", package_info.install_info.package_name)
		ALittle.File_SaveFile(file_path, content, -1)
	end
	javac_string = ALittle.String_Replace(javac_string, "/", "\\")
	ALittle.File_SaveFile(package_info.project_path .. "/Export/Android/src_list.txt", javac_string, -1)
	os.execute("call \"" .. package_info.project_path .. "/Export/Android/ExportAPK.bat\" " .. ALittle.String_Join(package_name_list, "\\"))
	return "Install.apk"
end

function ALittleIDE.IDEExport:GenerateIpa(package_info)
	ALittle.Log("==================GenerateIpa:" .. package_info.project_name .. "==================")
	if ALittle.File_GetFileAttr(package_info.project_path) == nil then
		ALittle.Log("IDEExport:GenerateIpa project_path is not exist:", package_info.project_path)
		return nil
	end
	if package_info.install_info.package_name == nil then
		ALittle.Log("IDEExport:GenerateIpa package_name is null")
		return nil
	end
	if package_info.install_info.install_name == nil then
		ALittle.Log("IDEExport:GenerateIpa install_name is null")
		return nil
	end
	ALittle.File_CopyDeepDir(ALittle.File_BaseFilePath() .. "Export/iOS/ALittleClient", package_info.export_path)
	local install_png = package_info.project_path .. "/Icon/install.png"
	if ALittle.File_GetFileAttr(install_png) == nil then
		install_png = ALittle.File_BaseFilePath() .. "Export/Icon/install.png"
	end
	local surface = carp.LoadCarpSurface(install_png)
	if surface ~= nil then
		local surface_width = carp.GetCarpSurfaceWidth(surface)
		local surface_height = carp.GetCarpSurfaceHeight(surface)
		local new_surface = carp.CreateCarpSurface(40, 40)
		local new_surface_width = carp.GetCarpSurfaceWidth(new_surface)
		local new_surface_height = carp.GetCarpSurfaceHeight(new_surface)
		carp.CutBlitCarpSurface(surface, new_surface, "0,0," .. surface_width .. "," .. surface_height, "0,0," .. new_surface_width .. "," .. new_surface_height)
		carp.SaveCarpSurface(new_surface, package_info.export_path .. "/ALittleClient/Assets.xcassets/AppIcon.appiconset/icon.png")
		carp.FreeCarpSurface(new_surface)
		new_surface = carp.CreateCarpSurface(60, 60)
		new_surface_width = carp.GetCarpSurfaceWidth(new_surface)
		new_surface_height = carp.GetCarpSurfaceHeight(new_surface)
		carp.CutBlitCarpSurface(surface, new_surface, "0,0," .. surface_width .. "," .. surface_height, "0,0," .. new_surface_width .. "," .. new_surface_height)
		carp.SaveCarpSurface(new_surface, package_info.export_path .. "/ALittleClient/Assets.xcassets/AppIcon.appiconset/icon-1.png")
		carp.FreeCarpSurface(new_surface)
		new_surface = carp.CreateCarpSurface(58, 58)
		new_surface_width = carp.GetCarpSurfaceWidth(new_surface)
		new_surface_height = carp.GetCarpSurfaceHeight(new_surface)
		carp.CutBlitCarpSurface(surface, new_surface, "0,0," .. surface_width .. "," .. surface_height, "0,0," .. new_surface_width .. "," .. new_surface_height)
		carp.SaveCarpSurface(new_surface, package_info.export_path .. "/ALittleClient/Assets.xcassets/AppIcon.appiconset/icon-2.png")
		carp.FreeCarpSurface(new_surface)
		new_surface = carp.CreateCarpSurface(87, 87)
		new_surface_width = carp.GetCarpSurfaceWidth(new_surface)
		new_surface_height = carp.GetCarpSurfaceHeight(new_surface)
		carp.CutBlitCarpSurface(surface, new_surface, "0,0," .. surface_width .. "," .. surface_height, "0,0," .. new_surface_width .. "," .. new_surface_height)
		carp.SaveCarpSurface(new_surface, package_info.export_path .. "/ALittleClient/Assets.xcassets/AppIcon.appiconset/icon-3.png")
		carp.FreeCarpSurface(new_surface)
		new_surface = carp.CreateCarpSurface(80, 80)
		new_surface_width = carp.GetCarpSurfaceWidth(new_surface)
		new_surface_height = carp.GetCarpSurfaceHeight(new_surface)
		carp.CutBlitCarpSurface(surface, new_surface, "0,0," .. surface_width .. "," .. surface_height, "0,0," .. new_surface_width .. "," .. new_surface_height)
		carp.SaveCarpSurface(new_surface, package_info.export_path .. "/ALittleClient/Assets.xcassets/AppIcon.appiconset/icon-4.png")
		carp.FreeCarpSurface(new_surface)
		new_surface = carp.CreateCarpSurface(120, 120)
		new_surface_width = carp.GetCarpSurfaceWidth(new_surface)
		new_surface_height = carp.GetCarpSurfaceHeight(new_surface)
		carp.CutBlitCarpSurface(surface, new_surface, "0,0," .. surface_width .. "," .. surface_height, "0,0," .. new_surface_width .. "," .. new_surface_height)
		carp.SaveCarpSurface(new_surface, package_info.export_path .. "/ALittleClient/Assets.xcassets/AppIcon.appiconset/icon-5.png")
		carp.FreeCarpSurface(new_surface)
		new_surface = carp.CreateCarpSurface(120, 120)
		new_surface_width = carp.GetCarpSurfaceWidth(new_surface)
		new_surface_height = carp.GetCarpSurfaceHeight(new_surface)
		carp.CutBlitCarpSurface(surface, new_surface, "0,0," .. surface_width .. "," .. surface_height, "0,0," .. new_surface_width .. "," .. new_surface_height)
		carp.SaveCarpSurface(new_surface, package_info.export_path .. "/ALittleClient/Assets.xcassets/AppIcon.appiconset/icon-6.png")
		carp.FreeCarpSurface(new_surface)
		new_surface = carp.CreateCarpSurface(180, 180)
		new_surface_width = carp.GetCarpSurfaceWidth(new_surface)
		new_surface_height = carp.GetCarpSurfaceHeight(new_surface)
		carp.CutBlitCarpSurface(surface, new_surface, "0,0," .. surface_width .. "," .. surface_height, "0,0," .. new_surface_width .. "," .. new_surface_height)
		carp.SaveCarpSurface(new_surface, package_info.export_path .. "/ALittleClient/Assets.xcassets/AppIcon.appiconset/icon-7.png")
		carp.FreeCarpSurface(new_surface)
		new_surface = carp.CreateCarpSurface(20, 20)
		new_surface_width = carp.GetCarpSurfaceWidth(new_surface)
		new_surface_height = carp.GetCarpSurfaceHeight(new_surface)
		carp.CutBlitCarpSurface(surface, new_surface, "0,0," .. surface_width .. "," .. surface_height, "0,0," .. new_surface_width .. "," .. new_surface_height)
		carp.SaveCarpSurface(new_surface, package_info.export_path .. "/ALittleClient/Assets.xcassets/AppIcon.appiconset/icon-8.png")
		carp.FreeCarpSurface(new_surface)
		new_surface = carp.CreateCarpSurface(40, 40)
		new_surface_width = carp.GetCarpSurfaceWidth(new_surface)
		new_surface_height = carp.GetCarpSurfaceHeight(new_surface)
		carp.CutBlitCarpSurface(surface, new_surface, "0,0," .. surface_width .. "," .. surface_height, "0,0," .. new_surface_width .. "," .. new_surface_height)
		carp.SaveCarpSurface(new_surface, package_info.export_path .. "/ALittleClient/Assets.xcassets/AppIcon.appiconset/icon-9.png")
		carp.FreeCarpSurface(new_surface)
		new_surface = carp.CreateCarpSurface(29, 29)
		new_surface_width = carp.GetCarpSurfaceWidth(new_surface)
		new_surface_height = carp.GetCarpSurfaceHeight(new_surface)
		carp.CutBlitCarpSurface(surface, new_surface, "0,0," .. surface_width .. "," .. surface_height, "0,0," .. new_surface_width .. "," .. new_surface_height)
		carp.SaveCarpSurface(new_surface, package_info.export_path .. "/ALittleClient/Assets.xcassets/AppIcon.appiconset/icon-10.png")
		carp.FreeCarpSurface(new_surface)
		new_surface = carp.CreateCarpSurface(58, 58)
		new_surface_width = carp.GetCarpSurfaceWidth(new_surface)
		new_surface_height = carp.GetCarpSurfaceHeight(new_surface)
		carp.CutBlitCarpSurface(surface, new_surface, "0,0," .. surface_width .. "," .. surface_height, "0,0," .. new_surface_width .. "," .. new_surface_height)
		carp.SaveCarpSurface(new_surface, package_info.export_path .. "/ALittleClient/Assets.xcassets/AppIcon.appiconset/icon-11.png")
		carp.FreeCarpSurface(new_surface)
		new_surface = carp.CreateCarpSurface(40, 40)
		new_surface_width = carp.GetCarpSurfaceWidth(new_surface)
		new_surface_height = carp.GetCarpSurfaceHeight(new_surface)
		carp.CutBlitCarpSurface(surface, new_surface, "0,0," .. surface_width .. "," .. surface_height, "0,0," .. new_surface_width .. "," .. new_surface_height)
		carp.SaveCarpSurface(new_surface, package_info.export_path .. "/ALittleClient/Assets.xcassets/AppIcon.appiconset/icon-12.png")
		carp.FreeCarpSurface(new_surface)
		new_surface = carp.CreateCarpSurface(80, 80)
		new_surface_width = carp.GetCarpSurfaceWidth(new_surface)
		new_surface_height = carp.GetCarpSurfaceHeight(new_surface)
		carp.CutBlitCarpSurface(surface, new_surface, "0,0," .. surface_width .. "," .. surface_height, "0,0," .. new_surface_width .. "," .. new_surface_height)
		carp.SaveCarpSurface(new_surface, package_info.export_path .. "/ALittleClient/Assets.xcassets/AppIcon.appiconset/icon-13.png")
		carp.FreeCarpSurface(new_surface)
		new_surface = carp.CreateCarpSurface(76, 76)
		new_surface_width = carp.GetCarpSurfaceWidth(new_surface)
		new_surface_height = carp.GetCarpSurfaceHeight(new_surface)
		carp.CutBlitCarpSurface(surface, new_surface, "0,0," .. surface_width .. "," .. surface_height, "0,0," .. new_surface_width .. "," .. new_surface_height)
		carp.SaveCarpSurface(new_surface, package_info.export_path .. "/ALittleClient/Assets.xcassets/AppIcon.appiconset/icon-14.png")
		carp.FreeCarpSurface(new_surface)
		new_surface = carp.CreateCarpSurface(152, 152)
		new_surface_width = carp.GetCarpSurfaceWidth(new_surface)
		new_surface_height = carp.GetCarpSurfaceHeight(new_surface)
		carp.CutBlitCarpSurface(surface, new_surface, "0,0," .. surface_width .. "," .. surface_height, "0,0," .. new_surface_width .. "," .. new_surface_height)
		carp.SaveCarpSurface(new_surface, package_info.export_path .. "/ALittleClient/Assets.xcassets/AppIcon.appiconset/icon-15.png")
		carp.FreeCarpSurface(new_surface)
		new_surface = carp.CreateCarpSurface(167, 167)
		new_surface_width = carp.GetCarpSurfaceWidth(new_surface)
		new_surface_height = carp.GetCarpSurfaceHeight(new_surface)
		carp.CutBlitCarpSurface(surface, new_surface, "0,0," .. surface_width .. "," .. surface_height, "0,0," .. new_surface_width .. "," .. new_surface_height)
		carp.SaveCarpSurface(new_surface, package_info.export_path .. "/ALittleClient/Assets.xcassets/AppIcon.appiconset/icon-16.png")
		carp.FreeCarpSurface(new_surface)
		new_surface = carp.CreateCarpSurface(1024, 1024)
		new_surface_width = carp.GetCarpSurfaceWidth(new_surface)
		new_surface_height = carp.GetCarpSurfaceHeight(new_surface)
		carp.CutBlitCarpSurface(surface, new_surface, "0,0," .. surface_width .. "," .. surface_height, "0,0," .. new_surface_width .. "," .. new_surface_height)
		carp.SaveCarpSurface(new_surface, package_info.export_path .. "/ALittleClient/Assets.xcassets/AppIcon.appiconset/icon-17.png")
		carp.FreeCarpSurface(new_surface)
		carp.FreeCarpSurface(surface)
	end
	local share_file = carp.CarpLocalFile()
	share_file:SetPath(package_info.export_path .. "/ALittleClient.xcodeproj/project.pbxproj")
	if share_file:Load(false) then
		local content = share_file:GetContent()
		content = ALittle.String_Replace(content, "abcd@package_name@abcd", package_info.install_info.package_name)
		ALittle.File_SaveFile(package_info.export_path .. "/ALittleClient.xcodeproj/project.pbxproj", content, -1)
	end
	share_file = carp.CarpLocalFile()
	share_file:SetPath(package_info.export_path .. "/ALittleClient/ALittleClient.entitlements")
	if share_file:Load(false) then
		local content = share_file:GetContent()
		content = ALittle.String_Replace(content, "abcd@package_name@abcd", package_info.install_info.package_name)
		ALittle.File_SaveFile(package_info.export_path .. "/ALittleClient/ALittleClient.entitlements", content, -1)
	end
	share_file = carp.CarpLocalFile()
	share_file:SetPath(package_info.export_path .. "/ALittleClient/Info.plist")
	if share_file:Load(false) then
		local content = share_file:GetContent()
		content = ALittle.String_Replace(content, "abcd@version_number@abcd", package_info.version_info.version_number)
		content = ALittle.String_Replace(content, "abcd@app_name@abcd", package_info.install_info.install_name)
		if package_info.install_info.screen == "竖屏" then
			content = ALittle.String_Replace(content, "abcd@screen@abcd", "<string>UIInterfaceOrientationPortrait</string>")
			content = ALittle.String_Replace(content, "abcd@screen@abcd", "<string>UIInterfaceOrientationPortrait</string>")
		elseif package_info.install_info.screen == "横屏" then
			content = ALittle.String_Replace(content, "abcd@screen@abcd", "<string>UIInterfaceOrientationLandscapeLeft</string><string>UIInterfaceOrientationLandscapeRight</string>")
			content = ALittle.String_Replace(content, "abcd@screen@abcd", "<string>UIInterfaceOrientationLandscapeLeft</string><string>UIInterfaceOrientationLandscapeRight</string>")
		else
			content = ALittle.String_Replace(content, "abcd@screen@abcd", "<string>UIInterfaceOrientationPortrait</string><string>UIInterfaceOrientationLandscapeLeft</string><string>UIInterfaceOrientationLandscapeRight</string>")
			content = ALittle.String_Replace(content, "abcd@screen@abcd", "<string>UIInterfaceOrientationPortrait</string><string>UIInterfaceOrientationLandscapeLeft</string><string>UIInterfaceOrientationLandscapeRight</string>")
		end
		if package_info.install_info.fullscreen then
			content = ALittle.String_Replace(content, "abcd@fullscreen@abcd", "<key>Status bar is initially hidden</key><true/>")
		else
			content = ALittle.String_Replace(content, "abcd@fullscreen@abcd", "<key>Status bar is initially hidden</key><false/>")
		end
		ALittle.File_SaveFile(package_info.export_path .. "/ALittleClient/Info.plist", content, -1)
	end
	ALittle.File_SaveFile(package_info.project_path .. "/Export/Install.ipa", "Install.ipa", -1)
	return "Install.ipa"
end

function ALittleIDE.IDEExport:GenerateWeb(package_info)
	ALittle.Log("==================GenerateWeb:" .. package_info.project_name .. "==================")
	if ALittle.File_GetFileAttr(package_info.project_path) == nil then
		ALittle.Log("IDEExport:GenerateWeb project_path is not exist:", package_info.project_path)
		return nil
	end
	local install_ico = package_info.project_path .. "/Icon/install.ico"
	if ALittle.File_GetFileAttr(install_ico) == nil then
		ALittle.File_CopyFile(ALittle.File_BaseFilePath() .. "Export/Icon/install.ico", package_info.project_path .. "/Export/Web/favicon.ico")
	else
		ALittle.File_CopyFile(install_ico, package_info.project_path .. "/Export/Web/favicon.ico")
	end
	local file = carp.CarpLocalFile()
	file:SetPath(ALittle.File_BaseFilePath() .. "Export/Web/index.html")
	if file:Load(false) then
		local content = file:GetContent()
		content = ALittle.String_Replace(content, "abcd@project_name@abcd", package_info.project_name)
		ALittle.File_SaveFile(package_info.project_path .. "/Export/Web/" .. package_info.project_name .. ".html", content, -1)
		ALittle.File_SaveFile(package_info.project_path .. "/Export/Install.html", content, -1)
	end
	return "Install.html"
end

function ALittleIDE.IDEExport:GenerateWeChat(package_info)
	ALittle.Log("==================GenerateWeChat:" .. package_info.project_name .. "==================")
	if ALittle.File_GetFileAttr(package_info.project_path) == nil then
		ALittle.Log("IDEExport:GenerateWeChat project_path is not exist:", package_info.project_path)
		return nil
	end
	local install_ico = package_info.project_path .. "/Icon/install.ico"
	if ALittle.File_GetFileAttr(install_ico) == nil then
		ALittle.File_CopyFile(ALittle.File_BaseFilePath() .. "Export/Icon/install.ico", package_info.project_path .. "/Export/WeChat/favicon.ico")
	else
		ALittle.File_CopyFile(install_ico, package_info.project_path .. "/Export/WeChat/favicon.ico")
	end
	local game_js = carp.CarpLocalFile()
	game_js:SetPath(ALittle.File_BaseFilePath() .. "Export/WeChat/game.js")
	if game_js:Load(false) then
		local content = game_js:GetContent()
		content = ALittle.String_Replace(content, "abcd@project_name@abcd", package_info.project_name)
		content = ALittle.String_Replace(content, "abcd@res_ip@abcd", package_info.install_info.res_ip)
		content = ALittle.String_Replace(content, "abcd@res_port@abcd", ALittle.String_ToString(package_info.install_info.res_port))
		content = ALittle.String_Replace(content, "abcd@res_base_path@abcd", package_info.install_info.res_base_path)
		ALittle.File_SaveFile(package_info.project_path .. "/Export/WeChat/game.js", content, -1)
		ALittle.File_SaveFile(package_info.project_path .. "/Export/Install.js", content, -1)
	end
	local game_json = carp.CarpLocalFile()
	game_json:SetPath(ALittle.File_BaseFilePath() .. "Export/WeChat/game.json")
	if game_json:Load(false) then
		local content = game_json:GetContent()
		if package_info.install_info.screen == "竖屏" then
			content = ALittle.String_Replace(content, "abcd@screen@abcd", "portrait")
		else
			content = ALittle.String_Replace(content, "abcd@screen@abcd", "landscape")
		end
		ALittle.File_SaveFile(package_info.project_path .. "/Export/WeChat/game.json", content, -1)
	end
	local project_config_json = carp.CarpLocalFile()
	project_config_json:SetPath(ALittle.File_BaseFilePath() .. "Export/WeChat/project.config.json")
	if project_config_json:Load(false) then
		local content = project_config_json:GetContent()
		ALittle.File_SaveFile(package_info.project_path .. "/Export/WeChat/project.config.json", content, -1)
	end
	return "Install.js"
end

function ALittleIDE.IDEExport:GenerateEmscripten(package_info)
	ALittle.Log("==================GenerateEmscripten:" .. package_info.project_name .. "==================")
	if ALittle.File_GetFileAttr(package_info.project_path) == nil then
		ALittle.Log("IDEExport:GenerateEmscripten project_path is not exist:", package_info.project_path)
		return nil
	end
	local install_ico = package_info.project_path .. "/Icon/install.ico"
	if ALittle.File_GetFileAttr(install_ico) == nil then
		ALittle.File_CopyFile(ALittle.File_BaseFilePath() .. "Export/Icon/install.ico", package_info.project_path .. "/Export/Web/favicon.ico")
	else
		ALittle.File_CopyFile(install_ico, package_info.project_path .. "/Export/Emscripten/favicon.ico")
	end
	local file = carp.CarpLocalFile()
	file:SetPath(ALittle.File_BaseFilePath() .. "Export/Emscripten/index.js")
	if file:Load(false) then
		local content = file:GetContent()
		content = ALittle.String_Replace(content, "abcd@project_name@abcd", package_info.project_name)
		ALittle.File_SaveFile(package_info.project_path .. "/Export/Emscripten/" .. package_info.project_name .. ".js", content, -1)
	end
	file = carp.CarpLocalFile()
	file:SetPath(ALittle.File_BaseFilePath() .. "Export/Emscripten/index.html")
	if file:Load(false) then
		local content = file:GetContent()
		content = ALittle.String_Replace(content, "abcd@project_name@abcd", package_info.project_name)
		ALittle.File_SaveFile(package_info.project_path .. "/Export/Emscripten/" .. package_info.project_name .. ".html", content, -1)
		ALittle.File_SaveFile(package_info.project_path .. "/Export/Install.html", content, -1)
	end
	return "Install.html"
end

ALittleIDE.g_IDEExport = ALittleIDE.IDEExport()
end