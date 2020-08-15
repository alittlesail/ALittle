-- ALittle Generate Lua And Do Not Edit This Line!
module("ABrowser", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


AVersionManager = Lua.Class(nil, "ABrowser.AVersionManager")

function AVersionManager:Setup(debug)
	self._debug = debug
	if self._debug ~= "debug" then
		self:CheckVersionUpdate()
	end
end

function AVersionManager:Shutdown()
	if self._timer ~= nil then
		A_LoopSystem:RemoveTimer(self._timer)
		self._timer = nil
	end
	if self._version_system == nil then
		return
	end
	self._version_system:StopUpdate()
end

function AVersionManager:CreateDialog()
	if self._dialog == nil then
		self._dialog = g_Control:CreateControl(g_ABrowser.ui_pre .. "abrowser_version_download_dialog", self)
		A_LayerManager:AddToModal(self._dialog)
		self._dialog.visible = false
		self._notice_content.text = ""
		self._process_bg.visible = false
		self._process_bar.visible = false
		self._noupdate_btn.visible = false
		self._update_btn.visible = false
		self._check_btn.visible = false
		self._install_btn.visible = false
		self._restart_btn.visible = false
	end
end

function AVersionManager:ShowDialog()
	self:CreateDialog()
	self._dialog.visible = true
	self:UpdateVersion(true)
end

function AVersionManager:HandleCheckClick(event)
	self:UpdateVersion(true)
end

function AVersionManager:HandleUpdateClick(event)
	self:UpdateVersion(false)
end

function AVersionManager:HandleNoUpdateClick(event)
	self._dialog.visible = false
end

function AVersionManager:HandleInstallClick(event)
	self._version_system:Install()
end

function AVersionManager:HandleRestartClick(event)
	ALittle.System_Restart()
end

function AVersionManager:HandleUpdateVersion(file_name, cur_size, total_size, cur_file_index, file_count)
	self._notice_content.text = "版本正在更新..." .. ALittle.Math_Floor(self._version_system.current_update_size / self._version_system.total_update_size * 100) .. "%"
	self._process_bg.visible = true
	self._process_bar.visible = true
	self._process_bar.x = self._process_bg.x
	self._process_bar.width = (self._version_system.current_update_size / self._version_system.total_update_size) * self._process_bg.width
	self._noupdate_btn.visible = false
	self._update_btn.visible = false
	self._check_btn.visible = false
	self._install_btn.visible = false
	self._restart_btn.visible = false
end

function AVersionManager:CheckVersionUpdate()
	if self._timer ~= nil then
		return
	end
	self._timer = A_LoopSystem:AddTimer(1, Lua.Bind(self.CheckVersionUpdateImpl, self), 0, 3600000)
end

function AVersionManager:CheckVersionUpdateImpl()
	if self._version_system == nil then
		self._version_system = ALittle.VersionSystem.CreateVersionSystem("alittle", "ABrowser")
	end
	if self._version_system.doing then
		return
	end
	local result = self._version_system:UpdateVersion("139.159.176.119", 1100, nil, true)
	if result == 2 or result == 3 then
		local platform = ALittle.System_GetPlatform()
		if platform == "Windows" or A_OtherSystem:GetNetworkType() == "OtherSystem_NotifyNetwork_wifi" then
			if self._debug == "debug" then
				self:ShowDialog()
			else
				self:CreateDialog()
				self._dialog.visible = true
				self:UpdateVersion(false)
			end
		end
	end
end
AVersionManager.CheckVersionUpdateImpl = Lua.CoWrap(AVersionManager.CheckVersionUpdateImpl)

function AVersionManager:UpdateVersion(check)
	self:CreateDialog()
	if self._version_system == nil then
		self._version_system = ALittle.VersionSystem.CreateVersionSystem("alittle", "ABrowser")
	end
	if self._version_system.doing then
		return
	end
	if check then
		self._notice_content.text = "正在检查版本..."
		self._process_bg.visible = false
		self._process_bar.visible = false
		self._noupdate_btn.visible = false
		self._update_btn.visible = false
		self._check_btn.visible = true
		self._install_btn.visible = false
	else
		self._notice_content.text = "正在更新版本..."
		self._process_bg.visible = false
		self._process_bar.visible = false
		self._noupdate_btn.visible = false
		self._update_btn.visible = false
		self._check_btn.visible = false
		self._install_btn.visible = false
	end
	local result = self._version_system:UpdateVersion("139.159.176.119", 1100, Lua.Bind(self.HandleUpdateVersion, self), check)
	if result == 2 or result == 3 then
		self._notice_content.text = "有最新版本，您是否更新?"
		self._process_bg.visible = false
		self._process_bar.visible = false
		self._noupdate_btn.visible = true
		self._update_btn.visible = true
		self._check_btn.visible = false
		self._install_btn.visible = false
		self._restart_btn.visible = false
	elseif result == 1 then
		self._notice_content.text = "您当前已经是最新版本"
		self._process_bg.visible = false
		self._process_bar.visible = false
		self._noupdate_btn.visible = false
		self._update_btn.visible = false
		self._check_btn.visible = true
		self._install_btn.visible = false
		self._restart_btn.visible = false
	elseif result == 11 then
		self._notice_content.text = "版本更新失败"
		self._process_bg.visible = false
		self._process_bar.visible = false
		self._noupdate_btn.visible = false
		self._update_btn.visible = false
		self._check_btn.visible = true
		self._install_btn.visible = false
		self._restart_btn.visible = false
	elseif result == 12 then
		self._notice_content.text = "版本更新成功，重启软件生效"
		self._process_bg.visible = true
		self._process_bar.visible = true
		self._noupdate_btn.visible = false
		self._update_btn.visible = false
		self._check_btn.visible = false
		self._install_btn.visible = false
		self._restart_btn.visible = true
	elseif result == 13 then
		self._notice_content.text = "版本更新成功，需要重新安装"
		self._process_bg.visible = true
		self._process_bar.visible = true
		self._noupdate_btn.visible = false
		self._update_btn.visible = false
		self._check_btn.visible = false
		self._install_btn.visible = true
		self._restart_btn.visible = false
	end
end
AVersionManager.UpdateVersion = Lua.CoWrap(AVersionManager.UpdateVersion)

g_AVersionManager = AVersionManager()
