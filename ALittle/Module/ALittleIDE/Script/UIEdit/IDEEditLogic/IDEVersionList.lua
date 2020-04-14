
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-590627586, "ALittleIDE.IDEVersionInfoItem", {
name = "ALittleIDE.IDEVersionInfoItem", ns_name = "ALittleIDE", rl_name = "IDEVersionInfoItem", hash_code = -590627586,
name_list = {"_item_button","_item_title"},
type_list = {"ALittle.TextRadioButton","ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1510712093, "ALittleIDE.IDEVersionInfoItemUserData", {
name = "ALittleIDE.IDEVersionInfoItemUserData", ns_name = "ALittleIDE", rl_name = "IDEVersionInfoItemUserData", hash_code = -1510712093,
name_list = {"info","data"},
type_list = {"VersionServer.AVersionInfo","VersionServer.D_VersionInfo"},
option_map = {}
})
ALittle.RegStruct(129933683, "VersionServer.AVersionInfo", {
name = "VersionServer.AVersionInfo", ns_name = "VersionServer", rl_name = "AVersionInfo", hash_code = 129933683,
name_list = {"version_list","close_list","log_list"},
type_list = {"List<VersionServer.D_VersionInfo>","List<VersionServer.D_VersionClose>","List<VersionServer.D_VersionLog>"},
option_map = {}
})
ALittle.RegStruct(1657250345, "VersionServer.D_VersionInfo", {
name = "VersionServer.D_VersionInfo", ns_name = "VersionServer", rl_name = "D_VersionInfo", hash_code = 1657250345,
name_list = {"version_id","account_id","module_name","platform","big_version","version_number","install_version","install_size","status","small_version_time","small_version_index","create_time","create_index","update_time","update_index"},
type_list = {"string","string","string","string","string","string","string","int","int","int","int","int","int","int","int"},
option_map = {}
})
ALittle.RegStruct(929252339, "VersionServer.D_VersionClose", {
name = "VersionServer.D_VersionClose", ns_name = "VersionServer", rl_name = "D_VersionClose", hash_code = 929252339,
name_list = {"account_id","module_name","platform","close_version","submit_platform","create_time","create_index","update_time","update_index"},
type_list = {"string","string","string","string","string","int","int","int","int"},
option_map = {}
})
ALittle.RegStruct(-637772875, "VersionServer.D_VersionLog", {
name = "VersionServer.D_VersionLog", ns_name = "VersionServer", rl_name = "D_VersionLog", hash_code = -637772875,
name_list = {"version_id","account_id","module_name","platform","content","create_time","create_index","update_time","update_index"},
type_list = {"string","string","string","string","string","int","int","int","int"},
option_map = {}
})
ALittle.RegStruct(-1810358206, "ALittleIDE.IDEVersionCloseItemUserData", {
name = "ALittleIDE.IDEVersionCloseItemUserData", ns_name = "ALittleIDE", rl_name = "IDEVersionCloseItemUserData", hash_code = -1810358206,
name_list = {"info","data"},
type_list = {"VersionServer.AVersionInfo","VersionServer.D_VersionClose"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name = "ALittle.UIChangedEvent", ns_name = "ALittle", rl_name = "UIChangedEvent", hash_code = 958494922,
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
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name = "ALittle.UIRButtonDownEvent", ns_name = "ALittle", rl_name = "UIRButtonDownEvent", hash_code = -641444818,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
IDEVersionList = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEVersionList")

function IDEVersionList:Ctor(ctrl_sys)
	___rawset(self, "_platform", "Windows")
	___rawset(self, "_config_key", "")
end

function IDEVersionList:TCtor()
end

function IDEVersionList.__setter:platform(value)
	self._platform = value
end

function IDEVersionList.__getter:platform()
	return self._platform
end

function IDEVersionList.__setter:config_key(value)
	self._config_key = value
end

function IDEVersionList.__getter:config_key()
	return self._config_key
end

function IDEVersionList.__getter:export_old_log()
	return self._export_old_log
end

function IDEVersionList:HandleRefreshVersionList(event)
	if g_IDEProject.project == nil then
		g_IDETool:ShowNotice("错误", "当前没有打开的项目")
		return
	end
	self._export_refresh_btn.disabled = true
	self._version_list:RemoveAllChild()
	self._close_list:RemoveAllChild()
	local param = {}
	param.__account_id = g_IDELoginManager.account_id
	param.__session_id = g_IDELoginManager.session_id
	param.platform = self._platform
	param.module_name = g_IDEProject.project.name
	local client = ALittle.CreateHttpSender(g_IDELoginManager.http_ip, g_IDELoginManager.http_port)
	local error, result = ALittle.IHttpSender.Invoke("VersionServer.QVersionInfo", client, param)
	self._export_refresh_btn.disabled = false
	if error ~= nil then
		g_IDETool:ShowNotice("错误", "刷新失败:" .. error)
		return
	end
	local group_name = A_TextRadioButtonManager:CreateGroupName()
	local version_list = result.version_list
	if version_list == nil then
		version_list = {}
	end
	ALittle.List_Sort(version_list, IDEVersionList.VersionInfoCmp)
	local first_version_info = nil
	for k, v in ___ipairs(version_list) do
		local control_line = {}
		local item = self._ctrl_sys:CreateControl("ide_common_tree_item", control_line, self._version_list)
		control_line._item_button.group_name = group_name
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
		local item = self._ctrl_sys:CreateControl("ide_common_tree_item", control_line, self._close_list)
		control_line._item_button.group_name = group_name
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
IDEVersionList.HandleRefreshVersionList = Lua.CoWrap(IDEVersionList.HandleRefreshVersionList)

function IDEVersionList.VersionInfoCmp(a, b)
	if a.update_time ~= b.update_time then
		return a.update_time > b.update_time
	end
	return a.update_index > b.update_index
end

function IDEVersionList:HandleVersionListMenu(event)
	if self._version_menu == nil then
		self._version_menu = self._ctrl_sys:CreateControl("ide_version_menu", self)
	end
	A_LayerManager:ShowFromRight(self._version_menu)
	self._version_menu.x = A_UISystem.mouse_x
	self._version_menu.y = A_UISystem.mouse_y
	self._version_menu._user_data = event.target._user_data
end

function IDEVersionList:HandleVersionDelete(event)
	A_LayerManager:HideFromRight(self._version_menu)
	local version_info = self._version_menu._user_data
	if version_info == nil then
		return
	end
	local callback = Lua.Bind(self.VersionDeleteImpl, self, version_info)
	g_IDETool:DeleteNotice("删除", "确定要删除" .. ALittle.Time_GetCurDate(version_info.data.update_time) .. "(版本时间)这个版本吗?", callback)
end

function IDEVersionList:VersionDeleteImpl(version_info)
	local param = {}
	param.__account_id = g_IDELoginManager.account_id
	param.__session_id = g_IDELoginManager.session_id
	param.platform = self._platform
	param.module_name = g_IDEProject.project.name
	param.version_id = version_info.data.version_id
	local client = ALittle.CreateHttpSender(g_IDELoginManager.http_ip, g_IDELoginManager.http_port)
	local error, result = ALittle.IHttpSender.Invoke("VersionServer.QDeleteVersionInfo", client, param)
	if error ~= nil then
		g_IDETool:ShowNotice("提示", "删除失败:" .. error)
		return
	end
	self:HandleRefreshVersionList(nil)
end
IDEVersionList.VersionDeleteImpl = Lua.CoWrap(IDEVersionList.VersionDeleteImpl)

function IDEVersionList:HandleVersionListSelectChange(event)
	if g_IDEProject.project == nil then
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

function IDEVersionList:ShowVersionInfo(version_info)
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

function IDEVersionList:HandleVersionCloseListMenu(event)
	if self._version_close_menu == nil then
		self._version_close_menu = self._ctrl_sys:CreateControl("ide_version_close_menu", self)
	end
	A_LayerManager:ShowFromRight(self._version_close_menu)
	self._version_close_menu.x = A_UISystem.mouse_x
	self._version_close_menu.y = A_UISystem.mouse_y
	self._version_close_menu._user_data = event.target._user_data
end

function IDEVersionList:HandleVersionCloseDelete(event)
	A_LayerManager:HideFromRight(self._version_close_menu)
	local version_info = self._version_close_menu._user_data
	if version_info == nil then
		return
	end
	local callback = Lua.Bind(self.VersionCloseDeleteImpl, self, version_info)
	g_IDETool:DeleteNotice("删除", "确定要删除" .. version_info.data.close_version .. "(" .. version_info.data.submit_platform .. ")这个拦截版本吗?", callback)
end

function IDEVersionList:VersionCloseDeleteImpl(version_info)
	local param = {}
	param.__account_id = g_IDELoginManager.account_id
	param.__session_id = g_IDELoginManager.session_id
	param.platform = self._platform
	param.module_name = g_IDEProject.project.name
	param.close_version = version_info.data.close_version
	local client = ALittle.CreateHttpSender(g_IDELoginManager.http_ip, g_IDELoginManager.http_port)
	local error, result = ALittle.IHttpSender.Invoke("VersionServer.QDeleteVersionClose", client, param)
	if error ~= nil then
		g_IDETool:ShowNotice("提示", "删除失败:" .. error)
		return
	end
	self:HandleRefreshVersionList(nil)
end
IDEVersionList.VersionCloseDeleteImpl = Lua.CoWrap(IDEVersionList.VersionCloseDeleteImpl)

function IDEVersionList:HandleAddVersionClose(event)
	if self._version_close_dialog == nil then
		self._version_close_dialog = self._ctrl_sys:CreateControl("ide_add_version_close_dialog", self)
		g_IDECenter.dialog_layer:AddChild(self._version_close_dialog)
	end
	self._version_close_version.text = ""
	self._version_submit_platform.text = ""
	self._version_close_dialog.visible = true
	self._version_close_dialog:MoveToTop()
end

function IDEVersionList:HandleAddVersionCloseClick(event)
	self._version_close_dialog.visible = false
	local param = {}
	param.__account_id = g_IDELoginManager.account_id
	param.__session_id = g_IDELoginManager.session_id
	param.platform = self._platform
	param.module_name = g_IDEProject.project.name
	param.close_version = self._version_close_version.text
	param.submit_platform = self._version_submit_platform.text
	local client = ALittle.CreateHttpSender(g_IDELoginManager.http_ip, g_IDELoginManager.http_port)
	local error, result = ALittle.IHttpSender.Invoke("VersionServer.QAddVersionClose", client, param)
	if error ~= nil then
		g_IDETool:ShowNotice("提示", "添加失败:" .. error)
		return
	end
	self:HandleRefreshVersionList(nil)
end
IDEVersionList.HandleAddVersionCloseClick = Lua.CoWrap(IDEVersionList.HandleAddVersionCloseClick)

function IDEVersionList:LoadConfig()
	local export_info = g_IDEProject.project.config:GetConfig(self._config_key, {})
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
end

function IDEVersionList:CheckDateString(content)
	local list = ALittle.String_Split(content, "-")
	if ALittle.List_MaxN(list) ~= 6 then
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

function IDEVersionList:CheckVersionString(content)
	local list = ALittle.String_Split(content, ".")
	if ALittle.List_MaxN(list) ~= 3 then
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

function IDEVersionList:GetConfig()
	local version_info = {}
	version_info.big_version = self._export_big_version.text
	if self:CheckDateString(version_info.big_version) == false then
		g_IDETool:ShowNotice("错误", "大版本格式不正确，请调整格式为：YYYY-mm-dd-HH-MM-SS")
		return nil
	end
	version_info.install_version = self._export_install_version.text
	if self:CheckDateString(version_info.install_version) == false then
		g_IDETool:ShowNotice("错误", "安装包版本格式不正确，请调整格式为：YYYY-mm-dd-HH-MM-SS")
		return nil
	end
	version_info.version_number = self._export_version_number.text
	if self:CheckVersionString(version_info.version_number) == false then
		g_IDETool:ShowNotice("错误", "软件版本号格式不正确，请调整格式为：数字.数字.数字")
		return nil
	end
	return version_info
end

function IDEVersionList:HandleGenBigVersionImpl()
	self._export_big_version.text = ALittle.Time_GetCurDate()
end

function IDEVersionList:HandleGenBigVersion(event)
	local func = Lua.Bind(self.HandleGenBigVersionImpl, self)
	g_IDETool:DeleteNotice("更新大版本号", "更新大版本号会引起强制更新，确定更新吗？", func)
end

function IDEVersionList:HandleGenInstallVersionImpl()
	self._export_install_version.text = ALittle.Time_GetCurDate()
end

function IDEVersionList:HandleGenInstallVersion(event)
	local func = Lua.Bind(self.HandleGenInstallVersionImpl, self)
	g_IDETool:DeleteNotice("更新安装包版本号", "更新安装包版本号会引起重新安装，确定更新吗？", func)
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
IDEVersionWindows = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEVersionWindows")

function IDEVersionWindows:Ctor(ctrl_sys)
end

function IDEVersionWindows:TCtor()
	self._version_list.platform = "Windows"
	self._version_list.config_key = "windows_export_info"
end

function IDEVersionWindows.__setter:config_key(value)
	self._version_list.config_key = value
end

function IDEVersionWindows.__getter:config_key()
	return self._version_list.config_key
end

function IDEVersionWindows:LoadConfigImpl()
	if g_IDEProject.project == nil then
		g_IDETool:ShowNotice("错误", "当前没有打开的项目")
		return false
	end
	self._version_list:LoadConfig()
	self._version_list:HandleRefreshVersionList(nil)
	self._version_list.export_old_log.text = ""
	local export_info = g_IDEProject.project.config:GetConfig(self.config_key, {})
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

function IDEVersionWindows:SaveConfigImpl()
	if g_IDEProject.project == nil then
		g_IDETool:ShowNotice("错误", "当前没有打开的项目")
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
		g_IDETool:ShowNotice("错误", "安装包名不能为空")
		return false
	end
	install_info.new_log = self._export_new_log.text
	g_IDEProject.project.config:SetConfig(self.config_key, export_info)
	return true
end

function IDEVersionWindows:HandleSaveConfig(event)
	if self:SaveConfigImpl() == false then
		return
	end
	g_IDETool:ShowNotice("提示", "配置保存成功")
end

function IDEVersionWindows:HandleExport(event)
	if self:SaveConfigImpl() == false then
		return
	end
	local export_info = g_IDEProject.project.config:GetConfig(self.config_key, nil)
	if export_info == nil then
		return
	end
	g_IDEExport:PackagePlatform(g_IDEProject.project.name, export_info.version_info, export_info.install_info, "Windows")
end
IDEVersionWindows.HandleExport = Lua.CoWrap(IDEVersionWindows.HandleExport)

function IDEVersionWindows:HandleSubmit(event)
	g_IDEExport:SubmitPlatform(g_IDEProject.project.name, "Windows")
end
IDEVersionWindows.HandleSubmit = Lua.CoWrap(IDEVersionWindows.HandleSubmit)

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
IDEVersionAndroid = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEVersionAndroid")

function IDEVersionAndroid:Ctor(ctrl_sys)
end

function IDEVersionAndroid:TCtor()
	self._version_list.platform = "Android"
	self._version_list.config_key = "android_export_info"
end

function IDEVersionAndroid.__setter:config_key(value)
	self._version_list.config_key = value
end

function IDEVersionAndroid.__getter:config_key()
	return self._version_list.config_key
end

function IDEVersionAndroid:LoadConfigImpl()
	if g_IDEProject.project == nil then
		g_IDETool:ShowNotice("错误", "当前没有打开的项目")
		return false
	end
	self._version_list:LoadConfig()
	self._version_list:HandleRefreshVersionList(nil)
	self._version_list.export_old_log.text = ""
	local export_info = g_IDEProject.project.config:GetConfig(self.config_key, {})
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

function IDEVersionAndroid:SaveConfigImpl()
	if g_IDEProject.project == nil then
		g_IDETool:ShowNotice("错误", "当前没有打开的项目")
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
		g_IDETool:ShowNotice("错误", "安装包名不能为空")
		return false
	end
	if install_info.package_name == "" then
		g_IDETool:ShowNotice("错误", "Android包名不能为空")
		return false
	end
	install_info.new_log = self._export_new_log.text
	g_IDEProject.project.config:SetConfig(self.config_key, export_info)
	return true
end

function IDEVersionAndroid:HandleSaveConfig(event)
	if self:SaveConfigImpl() == false then
		return
	end
	g_IDETool:ShowNotice("提示", "配置保存成功")
end

function IDEVersionAndroid:HandleExport(event)
	if self:SaveConfigImpl() == false then
		return
	end
	local export_info = g_IDEProject.project.config:GetConfig(self.config_key, nil)
	if export_info == nil then
		return
	end
	g_IDEExport:PackagePlatform(g_IDEProject.project.name, export_info.version_info, export_info.install_info, "Android")
end
IDEVersionAndroid.HandleExport = Lua.CoWrap(IDEVersionAndroid.HandleExport)

function IDEVersionAndroid:HandleSubmit(event)
	g_IDEExport:SubmitPlatform(g_IDEProject.project.name, "Android")
end
IDEVersionAndroid.HandleSubmit = Lua.CoWrap(IDEVersionAndroid.HandleSubmit)

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
IDEVersioniOS = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEVersioniOS")

function IDEVersioniOS:Ctor(ctrl_sys)
end

function IDEVersioniOS:TCtor()
	self._version_list.platform = "iOS"
	self._version_list.config_key = "ios_export_info"
end

function IDEVersioniOS.__setter:config_key(value)
	self._version_list.config_key = value
end

function IDEVersioniOS.__getter:config_key()
	return self._version_list.config_key
end

function IDEVersioniOS:LoadConfigImpl()
	if g_IDEProject.project == nil then
		g_IDETool:ShowNotice("错误", "当前没有打开的项目")
		return false
	end
	self._version_list:LoadConfig()
	self._version_list:HandleRefreshVersionList(nil)
	self._version_list.export_old_log.text = ""
	local export_info = g_IDEProject.project.config:GetConfig(self.config_key, {})
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

function IDEVersioniOS:SaveConfigImpl()
	if g_IDEProject.project == nil then
		g_IDETool:ShowNotice("错误", "当前没有打开的项目")
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
		g_IDETool:ShowNotice("错误", "安装包名不能为空")
		return false
	end
	if install_info.package_name == "" then
		g_IDETool:ShowNotice("错误", "iOS包名不能为空")
		return false
	end
	install_info.new_log = self._export_new_log.text
	g_IDEProject.project.config:SetConfig(self.config_key, export_info)
	return true
end

function IDEVersioniOS:HandleSaveConfig(event)
	if self:SaveConfigImpl() == false then
		return
	end
	g_IDETool:ShowNotice("提示", "配置保存成功")
end

function IDEVersioniOS:HandleExport(event)
	if self:SaveConfigImpl() == false then
		return
	end
	local export_info = g_IDEProject.project.config:GetConfig(self.config_key, nil)
	if export_info == nil then
		return
	end
	g_IDEExport:PackagePlatform(g_IDEProject.project.name, export_info.version_info, export_info.install_info, "iOS")
end
IDEVersioniOS.HandleExport = Lua.CoWrap(IDEVersioniOS.HandleExport)

function IDEVersioniOS:HandleSubmit(event)
	g_IDEExport:SubmitPlatform(g_IDEProject.project.name, "iOS")
end
IDEVersioniOS.HandleSubmit = Lua.CoWrap(IDEVersioniOS.HandleSubmit)

