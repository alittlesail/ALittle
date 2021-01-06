-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1810358206, "ALittleIDE.IDEVersionCloseItemUserData", {
name = "ALittleIDE.IDEVersionCloseItemUserData", ns_name = "ALittleIDE", rl_name = "IDEVersionCloseItemUserData", hash_code = -1810358206,
name_list = {"info","data"},
type_list = {"VersionServer.AVersionInfo","VersionServer.D_VersionClose"},
option_map = {}
})
ALittle.RegStruct(1657250345, "VersionServer.D_VersionInfo", {
name = "VersionServer.D_VersionInfo", ns_name = "VersionServer", rl_name = "D_VersionInfo", hash_code = 1657250345,
name_list = {"version_id","account_id","module_name","platform","big_version","version_number","install_version","plugin_list","install_size","status","small_version_time","small_version_index","create_time","create_index","update_time","update_index"},
type_list = {"string","string","string","string","string","string","string","string","int","int","int","int","int","int","int","int"},
option_map = {}
})
ALittle.RegStruct(-1510712093, "ALittleIDE.IDEVersionInfoItemUserData", {
name = "ALittleIDE.IDEVersionInfoItemUserData", ns_name = "ALittleIDE", rl_name = "IDEVersionInfoItemUserData", hash_code = -1510712093,
name_list = {"info","data"},
type_list = {"VersionServer.AVersionInfo","VersionServer.D_VersionInfo"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name = "ALittle.UIButtonEvent", ns_name = "ALittle", rl_name = "UIButtonEvent", hash_code = -1347278145,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name = "ALittle.UIChangedEvent", ns_name = "ALittle", rl_name = "UIChangedEvent", hash_code = 958494922,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(929252339, "VersionServer.D_VersionClose", {
name = "VersionServer.D_VersionClose", ns_name = "VersionServer", rl_name = "D_VersionClose", hash_code = 929252339,
name_list = {"account_id","module_name","platform","close_version","submit_platform","create_time","create_index","update_time","update_index"},
type_list = {"string","string","string","string","string","int","int","int","int"},
option_map = {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name = "ALittle.UIRButtonDownEvent", ns_name = "ALittle", rl_name = "UIRButtonDownEvent", hash_code = -641444818,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(-637772875, "VersionServer.D_VersionLog", {
name = "VersionServer.D_VersionLog", ns_name = "VersionServer", rl_name = "D_VersionLog", hash_code = -637772875,
name_list = {"version_id","account_id","module_name","platform","content","create_time","create_index","update_time","update_index"},
type_list = {"string","string","string","string","string","int","int","int","int"},
option_map = {}
})
ALittle.RegStruct(-590627586, "ALittleIDE.IDEVersionInfoItem", {
name = "ALittleIDE.IDEVersionInfoItem", ns_name = "ALittleIDE", rl_name = "IDEVersionInfoItem", hash_code = -590627586,
name_list = {"_item_button","_item_title"},
type_list = {"ALittle.TextRadioButton","ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(129933683, "VersionServer.AVersionInfo", {
name = "VersionServer.AVersionInfo", ns_name = "VersionServer", rl_name = "AVersionInfo", hash_code = 129933683,
name_list = {"version_list","close_list","log_list"},
type_list = {"List<VersionServer.D_VersionInfo>","List<VersionServer.D_VersionClose>","List<VersionServer.D_VersionLog>"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEVersionList = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEVersionList")

function ALittleIDE.IDEVersionList:Ctor(ctrl_sys)
	___rawset(self, "_platform", "Windows")
	___rawset(self, "_config_key", "")
end

function ALittleIDE.IDEVersionList:TCtor()
end

function ALittleIDE.IDEVersionList.__setter:platform(value)
	self._platform = value
end

function ALittleIDE.IDEVersionList.__getter:platform()
	return self._platform
end

function ALittleIDE.IDEVersionList.__setter:config_key(value)
	self._config_key = value
end

function ALittleIDE.IDEVersionList.__getter:config_key()
	return self._config_key
end

function ALittleIDE.IDEVersionList.__getter:export_old_log()
	return self._export_old_log
end

function ALittleIDE.IDEVersionList:HandleRefreshVersionList(event)
	if ALittleIDE.g_IDEProject.project == nil then
		g_AUITool:ShowNotice("错误", "当前没有打开的项目")
		return
	end
	if not ALittleIDE.g_IDEWebLoginManager:IsLogin() then
		g_AUITool:ShowNotice("错误", "请先登陆")
		return
	end
	self._export_refresh_btn.disabled = true
	self._version_list:RemoveAllChild()
	self._close_list:RemoveAllChild()
	local group = ALittle.CreateKeyWeakMap()
	local param = {}
	param.__account_id = ALittleIDE.g_IDEWebLoginManager.account_id
	param.__session_id = ALittleIDE.g_IDEWebLoginManager.session_id
	param.platform = self._platform
	param.module_name = ALittleIDE.g_IDEProject.project.name
	local client = ALittle.CreateHttpSender(ALittleIDE.g_IDEWebLoginManager.http_ip, ALittleIDE.g_IDEWebLoginManager.http_port)
	local error, result = ALittle.IHttpSender.Invoke("VersionServer.QVersionInfo", client, param)
	self._export_refresh_btn.disabled = false
	if error ~= nil then
		g_AUITool:ShowNotice("错误", "刷新失败:" .. error)
		return
	end
	local version_list = result.version_list
	if version_list == nil then
		version_list = {}
	end
	ALittle.List_Sort(version_list, ALittleIDE.IDEVersionList.VersionInfoCmp)
	local first_version_info = nil
	for k, v in ___ipairs(version_list) do
		local control_line = {}
		local item = ALittleIDE.g_Control:CreateControl("ide_version_item", control_line, self._version_list)
		control_line._item_button.group = group
		local user_data = {}
		control_line._item_button._user_data = user_data
		user_data.info = result
		user_data.data = v
		control_line._item_button.drag_trans_target = self._version_list
		control_line._item_button:AddEventListener(___all_struct[958494922], self, self.HandleVersionListSelectChange)
		control_line._item_button:AddEventListener(___all_struct[-641444818], self, self.HandleVersionListMenu)
		local status_str = "上传失败"
		if v.status == 1 then
			status_str = "上传成功"
		end
		control_line._item_title.text = "版本时间:" .. ALittle.Time_GetCurDate(v.update_time) .. "(" .. status_str .. ")"
		if first_version_info == nil then
			control_line._item_button.selected = true
			first_version_info = user_data
		end
	end
	local close_list = result.close_list
	if close_list == nil then
		close_list = {}
	end
	for k, v in ___ipairs(close_list) do
		local control_line = {}
		local item = self._ctrl_sys:CreateControl("tree_item", control_line, self._close_list)
		control_line._item_button.group = group
		local user_data = {}
		control_line._item_button._user_data = user_data
		user_data.info = result
		user_data.data = v
		control_line._item_button.drag_trans_target = self._close_list
		control_line._item_button:AddEventListener(___all_struct[-641444818], self, self.HandleVersionCloseListMenu)
		control_line._item_title.text = v.close_version .. "(" .. v.submit_platform .. ")"
	end
	if first_version_info ~= nil then
		self:ShowVersionInfo(first_version_info)
	end
end
ALittleIDE.IDEVersionList.HandleRefreshVersionList = Lua.CoWrap(ALittleIDE.IDEVersionList.HandleRefreshVersionList)

function ALittleIDE.IDEVersionList.VersionInfoCmp(a, b)
	if a.update_time ~= b.update_time then
		return a.update_time > b.update_time
	end
	return a.update_index > b.update_index
end

function ALittleIDE.IDEVersionList:HandleVersionListMenu(event)
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("删除", Lua.Bind(self.HandleVersionDelete, self, event.target._user_data))
	menu:Show()
end

function ALittleIDE.IDEVersionList:HandleVersionDelete(version_info)
	local delete_result = g_AUITool:DeleteNotice("删除", "确定要删除" .. ALittle.Time_GetCurDate(version_info.data.update_time) .. "(版本时间)这个版本吗?")
	if delete_result ~= "YES" then
		return
	end
	local param = {}
	param.__account_id = ALittleIDE.g_IDEWebLoginManager.account_id
	param.__session_id = ALittleIDE.g_IDEWebLoginManager.session_id
	param.platform = self._platform
	param.module_name = ALittleIDE.g_IDEProject.project.name
	param.version_id = version_info.data.version_id
	local client = ALittle.CreateHttpSender(ALittleIDE.g_IDEWebLoginManager.http_ip, ALittleIDE.g_IDEWebLoginManager.http_port)
	local error, result = ALittle.IHttpSender.Invoke("VersionServer.QDeleteVersionInfo", client, param)
	if error ~= nil then
		g_AUITool:ShowNotice("提示", "删除失败:" .. error)
		return
	end
	self:HandleRefreshVersionList(nil)
end
ALittleIDE.IDEVersionList.HandleVersionDelete = Lua.CoWrap(ALittleIDE.IDEVersionList.HandleVersionDelete)

function ALittleIDE.IDEVersionList:HandleVersionListSelectChange(event)
	if ALittleIDE.g_IDEProject.project == nil then
		return
	end
	if event.target.selected == false then
		return
	end
	local version_info = event.target._user_data
	if version_info == nil then
		self:LoadConfig()
		return
	end
	self:ShowVersionInfo(version_info)
end

function ALittleIDE.IDEVersionList:ShowVersionInfo(version_info)
	if version_info.data.big_version ~= nil then
		self._export_big_version.text = version_info.data.big_version
	else
		self._export_big_version.text = ""
	end
	if version_info.data.install_version ~= nil then
		self._export_install_version.text = version_info.data.install_version
	else
		self._export_install_version.text = ""
	end
	if version_info.data.version_number ~= nil then
		self._export_version_number.text = version_info.data.version_number
	else
		self._export_version_number.text = ""
	end
	if version_info.data.plugin_list ~= nil then
		self._export_plugin_list.text = version_info.data.plugin_list
	else
		self._export_plugin_list.text = ""
	end
	local log_list = {}
	local last_create_time = 0
	local log_index = 1
	for k, v in ___ipairs(version_info.info.log_list) do
		if v.create_time ~= last_create_time then
			last_create_time = v.create_time
			log_index = 1
			log_list[log_index] = ALittle.Time_GetCurDate(last_create_time)
		end
		log_list[log_index + 1] = "\t" .. log_index .. "." .. v.content
		log_index = log_index + 1
	end
	self._export_old_log.text = ALittle.String_Join(log_list, "\n")
end

function ALittleIDE.IDEVersionList:HandleVersionCloseListMenu(event)
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("删除", Lua.Bind(self.HandleVersionCloseDelete, self, event.target._user_data))
	menu:Show()
end

function ALittleIDE.IDEVersionList:HandleVersionCloseDelete(version_info)
	local delete_result = g_AUITool:DeleteNotice("删除", "确定要删除" .. version_info.data.close_version .. "(" .. version_info.data.submit_platform .. ")这个拦截版本吗?")
	if delete_result ~= "YES" then
		return
	end
	local param = {}
	param.__account_id = ALittleIDE.g_IDEWebLoginManager.account_id
	param.__session_id = ALittleIDE.g_IDEWebLoginManager.session_id
	param.platform = self._platform
	param.module_name = ALittleIDE.g_IDEProject.project.name
	param.close_version = version_info.data.close_version
	local client = ALittle.CreateHttpSender(ALittleIDE.g_IDEWebLoginManager.http_ip, ALittleIDE.g_IDEWebLoginManager.http_port)
	local error, result = ALittle.IHttpSender.Invoke("VersionServer.QDeleteVersionClose", client, param)
	if error ~= nil then
		g_AUITool:ShowNotice("提示", "删除失败:" .. error)
		return
	end
	self:HandleRefreshVersionList(nil)
end
ALittleIDE.IDEVersionList.HandleVersionCloseDelete = Lua.CoWrap(ALittleIDE.IDEVersionList.HandleVersionCloseDelete)

function ALittleIDE.IDEVersionList:HandleAddVersionClose(event)
	if self._version_close_dialog == nil then
		self._version_close_dialog = self._ctrl_sys:CreateControl("ide_add_version_close_dialog", self)
		ALittleIDE.g_DialogLayer:AddChild(self._version_close_dialog)
	end
	self._version_close_version.text = ""
	self._version_submit_platform.text = ""
	self._version_close_dialog.visible = true
	self._version_close_dialog:MoveToTop()
end

function ALittleIDE.IDEVersionList:HandleAddVersionCloseClick(event)
	self._version_close_dialog.visible = false
	local param = {}
	param.__account_id = ALittleIDE.g_IDEWebLoginManager.account_id
	param.__session_id = ALittleIDE.g_IDEWebLoginManager.session_id
	param.platform = self._platform
	param.module_name = ALittleIDE.g_IDEProject.project.name
	param.close_version = self._version_close_version.text
	param.submit_platform = self._version_submit_platform.text
	local client = ALittle.CreateHttpSender(ALittleIDE.g_IDEWebLoginManager.http_ip, ALittleIDE.g_IDEWebLoginManager.http_port)
	local error, result = ALittle.IHttpSender.Invoke("VersionServer.QAddVersionClose", client, param)
	if error ~= nil then
		g_AUITool:ShowNotice("提示", "添加失败:" .. error)
		return
	end
	self:HandleRefreshVersionList(nil)
end
ALittleIDE.IDEVersionList.HandleAddVersionCloseClick = Lua.CoWrap(ALittleIDE.IDEVersionList.HandleAddVersionCloseClick)

function ALittleIDE.IDEVersionList:LoadConfig()
	local export_info = ALittleIDE.g_IDEProject.project.config:GetConfig(self._config_key, {})
	local version_info = export_info.version_info
	if version_info == nil then
		version_info = {}
	end
	local version = ALittle.Time_GetCurDate(ALittle.Time_GetCurTime())
	if version_info.big_version ~= nil then
		self._export_big_version.text = version_info.big_version
	else
		self._export_big_version.text = version
	end
	if version_info.install_version ~= nil then
		self._export_install_version.text = version_info.install_version
	else
		self._export_install_version.text = version
	end
	if version_info.version_number ~= nil then
		self._export_version_number.text = version_info.version_number
	else
		self._export_version_number.text = ""
	end
	if version_info.plugin_list ~= nil then
		self._export_plugin_list.text = version_info.plugin_list
	else
		self._export_plugin_list.text = ""
	end
end

function ALittleIDE.IDEVersionList:CheckDateString(content)
	local list = ALittle.String_Split(content, "-")
	if ALittle.List_Len(list) ~= 6 then
		return false
	end
	if ALittle.String_Len(list[1]) ~= 4 then
		return false
	end
	if ALittle.Math_ToInt(list[1]) == nil then
		return false
	end
	local i = 2
	while true do
		if not(i <= 6) then break end
		if ALittle.String_Len(list[i]) ~= 2 then
			return false
		end
		if ALittle.Math_ToInt(list[i]) == nil then
			return false
		end
		i = i+(1)
	end
	return true
end

function ALittleIDE.IDEVersionList:CheckVersionString(content)
	local list = ALittle.String_Split(content, ".")
	if ALittle.List_Len(list) ~= 3 then
		return false
	end
	local i = 1
	while true do
		if not(i <= 2) then break end
		if ALittle.Math_ToInt(list[i]) == nil then
			return false
		end
		i = i+(1)
	end
	return true
end

function ALittleIDE.IDEVersionList:GetConfig()
	local version_info = {}
	version_info.big_version = self._export_big_version.text
	if self:CheckDateString(version_info.big_version) == false then
		g_AUITool:ShowNotice("错误", "大版本格式不正确，请调整格式为：YYYY-mm-dd-HH-MM-SS")
		return nil
	end
	version_info.install_version = self._export_install_version.text
	if self:CheckDateString(version_info.install_version) == false then
		g_AUITool:ShowNotice("错误", "安装包版本格式不正确，请调整格式为：YYYY-mm-dd-HH-MM-SS")
		return nil
	end
	version_info.version_number = self._export_version_number.text
	if self:CheckVersionString(version_info.version_number) == false then
		g_AUITool:ShowNotice("错误", "软件版本号格式不正确，请调整格式为：数字.数字.数字")
		return nil
	end
	version_info.plugin_list = self._export_plugin_list.text
	local module_list = ALittle.String_Split(version_info.plugin_list, ",")
	for index, module in ___ipairs(module_list) do
		if ALittle.File_GetFileAttr(ALittle.File_BaseFilePath() .. "Module/" .. module) == nil then
			g_AUITool:ShowNotice("错误", "引入的插件不存在:" .. module)
			return nil
		end
	end
	return version_info
end

function ALittleIDE.IDEVersionList:HandleGenBigVersion(event)
	local result = g_AUITool:DeleteNotice("更新大版本号", "更新大版本号会引起强制更新，确定更新吗？")
	if result == "YES" then
		self._export_big_version.text = ALittle.Time_GetCurDate()
	end
end
ALittleIDE.IDEVersionList.HandleGenBigVersion = Lua.CoWrap(ALittleIDE.IDEVersionList.HandleGenBigVersion)

function ALittleIDE.IDEVersionList:HandleGenInstallVersion(event)
	local result = g_AUITool:DeleteNotice("更新安装包版本号", "更新安装包版本号会引起重新安装，确定更新吗？")
	if result == "YES" then
		self._export_install_version.text = ALittle.Time_GetCurDate()
	end
end
ALittleIDE.IDEVersionList.HandleGenInstallVersion = Lua.CoWrap(ALittleIDE.IDEVersionList.HandleGenInstallVersion)

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEVersionWindows = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEVersionWindows")

function ALittleIDE.IDEVersionWindows:Ctor(ctrl_sys)
end

function ALittleIDE.IDEVersionWindows:TCtor()
	self._version_list.platform = "Windows"
	self._version_list.config_key = "windows_export_info"
end

function ALittleIDE.IDEVersionWindows.__setter:config_key(value)
	self._version_list.config_key = value
end

function ALittleIDE.IDEVersionWindows.__getter:config_key()
	return self._version_list.config_key
end

function ALittleIDE.IDEVersionWindows:LoadConfigImpl()
	if ALittleIDE.g_IDEProject.project == nil then
		g_AUITool:ShowNotice("错误", "当前没有打开的项目")
		return false
	end
	self._version_list:LoadConfig()
	self._version_list:HandleRefreshVersionList(nil)
	self._version_list.export_old_log.text = ""
	local export_info = ALittleIDE.g_IDEProject.project.config:GetConfig(self.config_key, {})
	local install_info = export_info.install_info
	if install_info == nil then
		install_info = {}
	end
	if install_info.install_name ~= nil then
		self._export_install_name.text = install_info.install_name
	else
		self._export_install_name.text = ""
	end
	if install_info.auto_start then
		self._export_auto_start.text = "是"
	else
		self._export_auto_start.text = "否"
	end
	if install_info.new_log ~= nil then
		self._export_new_log.text = install_info.new_log
	else
		self._export_new_log.text = ""
	end
	return true
end

function ALittleIDE.IDEVersionWindows:SaveConfigImpl()
	if ALittleIDE.g_IDEProject.project == nil then
		g_AUITool:ShowNotice("错误", "当前没有打开的项目")
		return false
	end
	local version_info = self._version_list:GetConfig()
	if version_info == nil then
		return false
	end
	local export_info = {}
	export_info.version_info = version_info
	local install_info = {}
	export_info.install_info = install_info
	install_info.file_name = "Install.exe"
	install_info.install_name = self._export_install_name.text
	if self._export_auto_start.text == "是" then
		install_info.auto_start = true
	else
		install_info.auto_start = false
	end
	if install_info.install_name == "" then
		g_AUITool:ShowNotice("错误", "安装包名不能为空")
		return false
	end
	install_info.new_log = self._export_new_log.text
	ALittleIDE.g_IDEProject.project.config:SetConfig(self.config_key, export_info)
	return true
end

function ALittleIDE.IDEVersionWindows:HandleSaveConfig(event)
	if self:SaveConfigImpl() == false then
		return
	end
	g_AUITool:ShowNotice("提示", "配置保存成功")
end

function ALittleIDE.IDEVersionWindows:HandleExport(event)
	if self:SaveConfigImpl() == false then
		return
	end
	local export_info = ALittleIDE.g_IDEProject.project.config:GetConfig(self.config_key, nil)
	if export_info == nil then
		return
	end
	ALittleIDE.g_IDEExport:PackagePlatform(ALittleIDE.g_IDEProject.project.name, export_info.version_info, export_info.install_info, "Windows")
end
ALittleIDE.IDEVersionWindows.HandleExport = Lua.CoWrap(ALittleIDE.IDEVersionWindows.HandleExport)

function ALittleIDE.IDEVersionWindows:HandleSubmit(event)
	ALittleIDE.g_IDEExport:SubmitPlatform(ALittleIDE.g_IDEProject.project.name, "Windows")
end
ALittleIDE.IDEVersionWindows.HandleSubmit = Lua.CoWrap(ALittleIDE.IDEVersionWindows.HandleSubmit)

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEVersionAndroid = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEVersionAndroid")

function ALittleIDE.IDEVersionAndroid:Ctor(ctrl_sys)
end

function ALittleIDE.IDEVersionAndroid:TCtor()
	self._version_list.platform = "Android"
	self._version_list.config_key = "android_export_info"
end

function ALittleIDE.IDEVersionAndroid.__setter:config_key(value)
	self._version_list.config_key = value
end

function ALittleIDE.IDEVersionAndroid.__getter:config_key()
	return self._version_list.config_key
end

function ALittleIDE.IDEVersionAndroid:LoadConfigImpl()
	if ALittleIDE.g_IDEProject.project == nil then
		g_AUITool:ShowNotice("错误", "当前没有打开的项目")
		return false
	end
	self._version_list:LoadConfig()
	self._version_list:HandleRefreshVersionList(nil)
	self._version_list.export_old_log.text = ""
	local export_info = ALittleIDE.g_IDEProject.project.config:GetConfig(self.config_key, {})
	local install_info = export_info.install_info
	if install_info == nil then
		install_info = {}
	end
	if install_info.install_name ~= nil then
		self._export_install_name.text = install_info.install_name
	else
		self._export_install_name.text = ""
	end
	if install_info.package_name ~= nil then
		self._export_package_name.text = install_info.package_name
	else
		self._export_package_name.text = ""
	end
	if install_info.screen ~= nil then
		self._export_screen.text = install_info.screen
	else
		self._export_screen.text = "竖屏"
	end
	if install_info.fullscreen then
		self._export_full_screen.text = "是"
	else
		self._export_full_screen.text = "否"
	end
	if install_info.new_log ~= nil then
		self._export_new_log.text = install_info.new_log
	else
		self._export_new_log.text = ""
	end
	return true
end

function ALittleIDE.IDEVersionAndroid:SaveConfigImpl()
	if ALittleIDE.g_IDEProject.project == nil then
		g_AUITool:ShowNotice("错误", "当前没有打开的项目")
		return false
	end
	local version_info = self._version_list:GetConfig()
	if version_info == nil then
		return false
	end
	local export_info = {}
	export_info.version_info = version_info
	local install_info = {}
	export_info.install_info = install_info
	install_info.file_name = "Install.apk"
	install_info.install_name = self._export_install_name.text
	install_info.package_name = self._export_package_name.text
	install_info.screen = self._export_screen.text
	install_info.fullscreen = (self._export_full_screen.text == "是")
	if install_info.install_name == "" then
		g_AUITool:ShowNotice("错误", "安装包名不能为空")
		return false
	end
	if install_info.package_name == "" then
		g_AUITool:ShowNotice("错误", "Android包名不能为空")
		return false
	end
	install_info.new_log = self._export_new_log.text
	ALittleIDE.g_IDEProject.project.config:SetConfig(self.config_key, export_info)
	return true
end

function ALittleIDE.IDEVersionAndroid:HandleSaveConfig(event)
	if self:SaveConfigImpl() == false then
		return
	end
	g_AUITool:ShowNotice("提示", "配置保存成功")
end

function ALittleIDE.IDEVersionAndroid:HandleExport(event)
	if self:SaveConfigImpl() == false then
		return
	end
	local export_info = ALittleIDE.g_IDEProject.project.config:GetConfig(self.config_key, nil)
	if export_info == nil then
		return
	end
	ALittleIDE.g_IDEExport:PackagePlatform(ALittleIDE.g_IDEProject.project.name, export_info.version_info, export_info.install_info, "Android")
end
ALittleIDE.IDEVersionAndroid.HandleExport = Lua.CoWrap(ALittleIDE.IDEVersionAndroid.HandleExport)

function ALittleIDE.IDEVersionAndroid:HandleSubmit(event)
	ALittleIDE.g_IDEExport:SubmitPlatform(ALittleIDE.g_IDEProject.project.name, "Android")
end
ALittleIDE.IDEVersionAndroid.HandleSubmit = Lua.CoWrap(ALittleIDE.IDEVersionAndroid.HandleSubmit)

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEVersioniOS = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEVersioniOS")

function ALittleIDE.IDEVersioniOS:Ctor(ctrl_sys)
end

function ALittleIDE.IDEVersioniOS:TCtor()
	self._version_list.platform = "iOS"
	self._version_list.config_key = "ios_export_info"
end

function ALittleIDE.IDEVersioniOS.__setter:config_key(value)
	self._version_list.config_key = value
end

function ALittleIDE.IDEVersioniOS.__getter:config_key()
	return self._version_list.config_key
end

function ALittleIDE.IDEVersioniOS:LoadConfigImpl()
	if ALittleIDE.g_IDEProject.project == nil then
		g_AUITool:ShowNotice("错误", "当前没有打开的项目")
		return false
	end
	self._version_list:LoadConfig()
	self._version_list:HandleRefreshVersionList(nil)
	self._version_list.export_old_log.text = ""
	local export_info = ALittleIDE.g_IDEProject.project.config:GetConfig(self.config_key, {})
	local install_info = export_info.install_info
	if install_info == nil then
		install_info = {}
	end
	if install_info.install_name ~= nil then
		self._export_install_name.text = install_info.install_name
	else
		self._export_install_name.text = ""
	end
	if install_info.package_name ~= nil then
		self._export_package_name.text = install_info.package_name
	else
		self._export_package_name.text = ""
	end
	if install_info.screen ~= nil then
		self._export_screen.text = install_info.screen
	else
		self._export_screen.text = "竖屏"
	end
	if install_info.fullscreen then
		self._export_full_screen.text = "是"
	else
		self._export_full_screen.text = "否"
	end
	if install_info.new_log ~= nil then
		self._export_new_log.text = install_info.new_log
	else
		self._export_new_log.text = ""
	end
	return true
end

function ALittleIDE.IDEVersioniOS:SaveConfigImpl()
	if ALittleIDE.g_IDEProject.project == nil then
		g_AUITool:ShowNotice("错误", "当前没有打开的项目")
		return false
	end
	local version_info = self._version_list:GetConfig()
	if version_info == nil then
		return false
	end
	local export_info = {}
	export_info.version_info = version_info
	local install_info = {}
	export_info.install_info = install_info
	install_info.file_name = "Install.ipa"
	install_info.install_name = self._export_install_name.text
	install_info.package_name = self._export_package_name.text
	install_info.screen = self._export_screen.text
	install_info.fullscreen = (self._export_full_screen.text == "是")
	if install_info.install_name == "" then
		g_AUITool:ShowNotice("错误", "安装包名不能为空")
		return false
	end
	if install_info.package_name == "" then
		g_AUITool:ShowNotice("错误", "iOS包名不能为空")
		return false
	end
	install_info.new_log = self._export_new_log.text
	ALittleIDE.g_IDEProject.project.config:SetConfig(self.config_key, export_info)
	return true
end

function ALittleIDE.IDEVersioniOS:HandleSaveConfig(event)
	if self:SaveConfigImpl() == false then
		return
	end
	g_AUITool:ShowNotice("提示", "配置保存成功")
end

function ALittleIDE.IDEVersioniOS:HandleExport(event)
	if self:SaveConfigImpl() == false then
		return
	end
	local export_info = ALittleIDE.g_IDEProject.project.config:GetConfig(self.config_key, nil)
	if export_info == nil then
		return
	end
	ALittleIDE.g_IDEExport:PackagePlatform(ALittleIDE.g_IDEProject.project.name, export_info.version_info, export_info.install_info, "iOS")
end
ALittleIDE.IDEVersioniOS.HandleExport = Lua.CoWrap(ALittleIDE.IDEVersioniOS.HandleExport)

function ALittleIDE.IDEVersioniOS:HandleSubmit(event)
	ALittleIDE.g_IDEExport:SubmitPlatform(ALittleIDE.g_IDEProject.project.name, "iOS")
end
ALittleIDE.IDEVersioniOS.HandleSubmit = Lua.CoWrap(ALittleIDE.IDEVersioniOS.HandleSubmit)

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEVersionWeb = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEVersionWeb")

function ALittleIDE.IDEVersionWeb:Ctor(ctrl_sys)
end

function ALittleIDE.IDEVersionWeb:TCtor()
	self._version_list.platform = "Web"
	self._version_list.config_key = "web_export_info"
end

function ALittleIDE.IDEVersionWeb.__setter:config_key(value)
	self._version_list.config_key = value
end

function ALittleIDE.IDEVersionWeb.__getter:config_key()
	return self._version_list.config_key
end

function ALittleIDE.IDEVersionWeb:LoadConfigImpl()
	if ALittleIDE.g_IDEProject.project == nil then
		g_AUITool:ShowNotice("错误", "当前没有打开的项目")
		return false
	end
	self._version_list:LoadConfig()
	self._version_list:HandleRefreshVersionList(nil)
	self._version_list.export_old_log.text = ""
	local export_info = ALittleIDE.g_IDEProject.project.config:GetConfig(self.config_key, {})
	local install_info = export_info.install_info
	if install_info == nil then
		install_info = {}
	end
	if install_info.new_log ~= nil then
		self._export_new_log.text = install_info.new_log
	else
		self._export_new_log.text = ""
	end
	return true
end

function ALittleIDE.IDEVersionWeb:SaveConfigImpl()
	if ALittleIDE.g_IDEProject.project == nil then
		g_AUITool:ShowNotice("错误", "当前没有打开的项目")
		return false
	end
	local version_info = self._version_list:GetConfig()
	if version_info == nil then
		return false
	end
	local export_info = {}
	export_info.version_info = version_info
	local install_info = {}
	export_info.install_info = install_info
	install_info.file_name = "Install.html"
	install_info.new_log = self._export_new_log.text
	ALittleIDE.g_IDEProject.project.config:SetConfig(self.config_key, export_info)
	return true
end

function ALittleIDE.IDEVersionWeb:HandleSaveConfig(event)
	if self:SaveConfigImpl() == false then
		return
	end
	g_AUITool:ShowNotice("提示", "配置保存成功")
end

function ALittleIDE.IDEVersionWeb:HandleExport(event)
	if self:SaveConfigImpl() == false then
		return
	end
	local export_info = ALittleIDE.g_IDEProject.project.config:GetConfig(self.config_key, nil)
	if export_info == nil then
		return
	end
	ALittleIDE.g_IDEExport:PackagePlatform(ALittleIDE.g_IDEProject.project.name, export_info.version_info, export_info.install_info, "Web")
end
ALittleIDE.IDEVersionWeb.HandleExport = Lua.CoWrap(ALittleIDE.IDEVersionWeb.HandleExport)

function ALittleIDE.IDEVersionWeb:HandleSubmit(event)
	ALittleIDE.g_IDEExport:SubmitPlatform(ALittleIDE.g_IDEProject.project.name, "Web")
end
ALittleIDE.IDEVersionWeb.HandleSubmit = Lua.CoWrap(ALittleIDE.IDEVersionWeb.HandleSubmit)

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEVersionWeChat = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEVersionWeChat")

function ALittleIDE.IDEVersionWeChat:Ctor(ctrl_sys)
end

function ALittleIDE.IDEVersionWeChat:TCtor()
	self._version_list.platform = "WeChat"
	self._version_list.config_key = "wechat_export_info"
end

function ALittleIDE.IDEVersionWeChat.__setter:config_key(value)
	self._version_list.config_key = value
end

function ALittleIDE.IDEVersionWeChat.__getter:config_key()
	return self._version_list.config_key
end

function ALittleIDE.IDEVersionWeChat:LoadConfigImpl()
	if ALittleIDE.g_IDEProject.project == nil then
		g_AUITool:ShowNotice("错误", "当前没有打开的项目")
		return false
	end
	self._version_list:LoadConfig()
	self._version_list:HandleRefreshVersionList(nil)
	self._version_list.export_old_log.text = ""
	local export_info = ALittleIDE.g_IDEProject.project.config:GetConfig(self.config_key, {})
	local install_info = export_info.install_info
	if install_info == nil then
		install_info = {}
	end
	if install_info.new_log ~= nil then
		self._export_new_log.text = install_info.new_log
	else
		self._export_new_log.text = ""
	end
	if install_info.res_ip ~= nil then
		self._export_res_ip.text = install_info.res_ip
	else
		self._export_res_ip.text = ""
	end
	if install_info.res_port ~= nil then
		self._export_res_port.text = install_info.res_port
	else
		self._export_res_port.text = ""
	end
	if install_info.res_base_path ~= nil then
		self._export_res_base_path.text = install_info.res_base_path
	else
		self._export_res_base_path.text = ""
	end
	if install_info.screen ~= nil then
		self._export_screen.text = install_info.screen
	else
		self._export_screen.text = "竖屏"
	end
	return true
end

function ALittleIDE.IDEVersionWeChat:SaveConfigImpl()
	if ALittleIDE.g_IDEProject.project == nil then
		g_AUITool:ShowNotice("错误", "当前没有打开的项目")
		return false
	end
	local version_info = self._version_list:GetConfig()
	if version_info == nil then
		return false
	end
	local export_info = {}
	export_info.version_info = version_info
	local install_info = {}
	export_info.install_info = install_info
	install_info.file_name = "Install.js"
	install_info.new_log = self._export_new_log.text
	install_info.res_ip = self._export_res_ip.text
	install_info.res_port = ALittle.Math_ToIntOrZero(self._export_res_port.text)
	install_info.res_base_path = self._export_res_base_path.text
	install_info.screen = self._export_screen.text
	ALittleIDE.g_IDEProject.project.config:SetConfig(self.config_key, export_info)
	return true
end

function ALittleIDE.IDEVersionWeChat:HandleSaveConfig(event)
	if self:SaveConfigImpl() == false then
		return
	end
	g_AUITool:ShowNotice("提示", "配置保存成功")
end

function ALittleIDE.IDEVersionWeChat:HandleExport(event)
	if self:SaveConfigImpl() == false then
		return
	end
	local export_info = ALittleIDE.g_IDEProject.project.config:GetConfig(self.config_key, nil)
	if export_info == nil then
		return
	end
	ALittleIDE.g_IDEExport:PackagePlatform(ALittleIDE.g_IDEProject.project.name, export_info.version_info, export_info.install_info, "WeChat")
end
ALittleIDE.IDEVersionWeChat.HandleExport = Lua.CoWrap(ALittleIDE.IDEVersionWeChat.HandleExport)

function ALittleIDE.IDEVersionWeChat:HandleSubmit(event)
	ALittleIDE.g_IDEExport:SubmitPlatform(ALittleIDE.g_IDEProject.project.name, "WeChat")
end
ALittleIDE.IDEVersionWeChat.HandleSubmit = Lua.CoWrap(ALittleIDE.IDEVersionWeChat.HandleSubmit)

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEVersionEmscripten = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEVersionEmscripten")

function ALittleIDE.IDEVersionEmscripten:Ctor(ctrl_sys)
end

function ALittleIDE.IDEVersionEmscripten:TCtor()
	self._version_list.platform = "Emscripten"
	self._version_list.config_key = "emscripten_export_info"
end

function ALittleIDE.IDEVersionEmscripten.__setter:config_key(value)
	self._version_list.config_key = value
end

function ALittleIDE.IDEVersionEmscripten.__getter:config_key()
	return self._version_list.config_key
end

function ALittleIDE.IDEVersionEmscripten:LoadConfigImpl()
	if ALittleIDE.g_IDEProject.project == nil then
		g_AUITool:ShowNotice("错误", "当前没有打开的项目")
		return false
	end
	self._version_list:LoadConfig()
	self._version_list:HandleRefreshVersionList(nil)
	self._version_list.export_old_log.text = ""
	local export_info = ALittleIDE.g_IDEProject.project.config:GetConfig(self.config_key, {})
	local install_info = export_info.install_info
	if install_info == nil then
		install_info = {}
	end
	if install_info.new_log ~= nil then
		self._export_new_log.text = install_info.new_log
	else
		self._export_new_log.text = ""
	end
	return true
end

function ALittleIDE.IDEVersionEmscripten:SaveConfigImpl()
	if ALittleIDE.g_IDEProject.project == nil then
		g_AUITool:ShowNotice("错误", "当前没有打开的项目")
		return false
	end
	local version_info = self._version_list:GetConfig()
	if version_info == nil then
		return false
	end
	local export_info = {}
	export_info.version_info = version_info
	local install_info = {}
	export_info.install_info = install_info
	install_info.file_name = "Install.html"
	if install_info.install_name == "" then
		g_AUITool:ShowNotice("错误", "安装包名不能为空")
		return false
	end
	install_info.new_log = self._export_new_log.text
	ALittleIDE.g_IDEProject.project.config:SetConfig(self.config_key, export_info)
	return true
end

function ALittleIDE.IDEVersionEmscripten:HandleSaveConfig(event)
	if self:SaveConfigImpl() == false then
		return
	end
	g_AUITool:ShowNotice("提示", "配置保存成功")
end

function ALittleIDE.IDEVersionEmscripten:HandleExport(event)
	if self:SaveConfigImpl() == false then
		return
	end
	local export_info = ALittleIDE.g_IDEProject.project.config:GetConfig(self.config_key, nil)
	if export_info == nil then
		return
	end
	ALittleIDE.g_IDEExport:PackagePlatform(ALittleIDE.g_IDEProject.project.name, export_info.version_info, export_info.install_info, "Emscripten")
end
ALittleIDE.IDEVersionEmscripten.HandleExport = Lua.CoWrap(ALittleIDE.IDEVersionEmscripten.HandleExport)

function ALittleIDE.IDEVersionEmscripten:HandleSubmit(event)
	ALittleIDE.g_IDEExport:SubmitPlatform(ALittleIDE.g_IDEProject.project.name, "Emscripten")
end
ALittleIDE.IDEVersionEmscripten.HandleSubmit = Lua.CoWrap(ALittleIDE.IDEVersionEmscripten.HandleSubmit)

end