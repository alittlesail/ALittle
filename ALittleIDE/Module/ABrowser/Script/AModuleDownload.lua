-- ALittle Generate Lua And Do Not Edit This Line!
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-1207920090, "ABrowser.AModuleInfo", {
name = "ABrowser.AModuleInfo", ns_name = "ABrowser", rl_name = "AModuleInfo", hash_code = -1207920090,
name_list = {"ip","port","account_name"},
type_list = {"string","int","string"},
option_map = {}
})

AModuleDownload = Lua.Class(nil, "ABrowser.AModuleDownload")

function AModuleDownload:Ctor()
	___rawset(self, "_version_system", nil)
	___rawset(self, "_cur_module_name", nil)
	___rawset(self, "_module_map_info", {})
end

function AModuleDownload.__getter:is_doing()
	return self._version_system ~= nil
end

function AModuleDownload:GetDownloadInfo(module_name)
	return self._module_map_info[module_name]
end

function AModuleDownload:Download(module_name, ip, port, account_name)
	if self._version_system ~= nil then
		return
	end
	local info = {}
	info.ip = ip
	info.port = port
	info.account_name = account_name
	self._module_map_info[module_name] = info
	if self._version_dialog == nil then
		self._version_dialog = g_Control:CreateControl(g_ABrowser.ui_pre .. "abrowser_module_download_dialog", self)
		A_LayerManager:AddToModal(self._version_dialog)
	end
	self._version_dialog.visible = true
	self._version_dialog.show_close_button.visible = false
	self._process_bg.visible = false
	self._process_bar.visible = false
	self._version_system = ALittle.VersionSystem.CreateVersionSystem(account_name, module_name)
	self._cur_module_name = module_name
	local result = self._version_system:UpdateVersion(ip, port, Lua.Bind(self.HandleUpdateVersion, self), false)
	if result == 2 or result == 3 then
	elseif result == 1 then
		g_ABrowser:LoadModule(self._cur_module_name)
		self._version_dialog.visible = false
		self._version_system = nil
	elseif result == 11 then
		self._version_dialog.show_close_button.visible = true
		self._notice_content.text = "下载失败"
		self._process_bg.visible = false
		self._process_bar.visible = false
		self._version_system = nil
		if ALittle.File_GetFileAttr(ALittle.File_BaseFilePath() .. "Module/" .. self._cur_module_name) ~= nil then
			g_ABrowser:LoadModule(self._cur_module_name)
		end
	elseif result == 12 then
		self._version_dialog.show_close_button.visible = true
		g_ABrowser:LoadModule(self._cur_module_name)
		self._version_dialog.visible = false
		self._version_system = nil
	elseif result == 13 then
	end
end
AModuleDownload.Download = Lua.CoWrap(AModuleDownload.Download)

function AModuleDownload:HandleUpdateVersion(file_name, cur_size, total_size, cur_file_index, file_count)
	self._notice_content.text = "模块正在下载..." .. math.floor(self._version_system.current_update_size / self._version_system.total_update_size * 100) .. "%"
	self._process_bg.visible = true
	self._process_bar.visible = true
	self._process_bar.x = self._process_bg.x
	self._process_bar.width = (self._version_system.current_update_size / self._version_system.total_update_size) * self._process_bg.width
end

g_AModuleDownload = AModuleDownload()
