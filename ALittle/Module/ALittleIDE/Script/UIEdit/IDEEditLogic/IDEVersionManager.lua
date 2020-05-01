-- ALittle Generate Lua
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


IDEVersionManager = Lua.Class(nil, "ALittleIDE.IDEVersionManager")

function IDEVersionManager:Ctor()
	___rawset(self, "_version_system", ALittle.VersionSystem.CreateVersionSystem("alittle", "ALittleIDE"))
end

function IDEVersionManager:Shutdown()
	if self._version_system == nil then
		return
	end
	self._version_system:StopUpdate()
end

function IDEVersionManager:CreateDialog()
	if self._dialog == nil then
		self._dialog = g_Control:CreateControl("ide_version_dialog", self)
		A_LayerManager:AddToModal(self._dialog)
		self._notice_content.text = ""
		self._notice_content.visible = true
		self._notice_edit.text = ""
		self._notice_edit.visible = false
		self._process_bg.visible = false
		self._process_bar.visible = false
		self._noupdate_btn.visible = false
		self._update_btn.visible = false
		self._check_btn.visible = false
		self._install_btn.visible = false
		self._restart_btn.visible = false
	end
end

function IDEVersionManager:ShowDialog()
	self:CreateDialog()
	self._dialog.visible = true
	self:UpdateVersion(true)
end

function IDEVersionManager:HandleCheckClick(event)
	self:UpdateVersion(true)
end

function IDEVersionManager:HandleUpdateClick(event)
	self:UpdateVersion(false)
end

function IDEVersionManager:HandleNoUpdateClick(event)
	self._dialog.visible = false
end

function IDEVersionManager:HandleInstallClick(event)
	self._version_system:Install(nil)
end

function IDEVersionManager:HandleRestartClick(event)
	ALittle.System_Restart()
end

function IDEVersionManager:CheckVersionUpdate()
	local loop = ALittle.LoopFunction(Lua.Bind(self.CheckVersionUpdateImpl, self), -1, 3600000, 0)
	loop:Start()
end

function IDEVersionManager:CheckVersionUpdateImpl()
	if self._version_system.doing then
		return
	end
	local result = self._version_system:UpdateVersion(g_IDELoginManager.version_ip, g_IDELoginManager.version_port, nil, true)
	if result == 2 or result == 3 then
		g_IDETool:ShowTipHelp("有最新版本，需要就更新~", 10000)
	end
end
IDEVersionManager.CheckVersionUpdateImpl = Lua.CoWrap(IDEVersionManager.CheckVersionUpdateImpl)

function IDEVersionManager:UpdateVersion(check)
	self:CreateDialog()
	if self._version_system.doing then
		return
	end
	if check then
		self._notice_content.text = "正在检查版本..."
		self._notice_content.visible = true
		self._notice_edit.visible = false
		self._process_bg.visible = false
		self._process_bar.visible = false
		self._noupdate_btn.visible = false
		self._update_btn.visible = false
		self._check_btn.visible = true
		self._install_btn.visible = false
	else
		self._notice_content.text = "正在更新版本..."
		self._notice_content.visible = true
		self._notice_edit.visible = false
		self._process_bg.visible = false
		self._process_bar.visible = false
		self._noupdate_btn.visible = false
		self._update_btn.visible = false
		self._check_btn.visible = false
		self._install_btn.visible = false
	end
	local result = self._version_system:UpdateVersion(g_IDELoginManager.version_ip, g_IDELoginManager.version_port, Lua.Bind(self.HandleUpdateVersion, self), check)
	if result == 2 or result == 3 then
		local text = "有最新版本，您是否更新?"
		local new_big_version, new_small_version, new_log_list = self._version_system:GetNewVersion(5)
		if new_log_list ~= nil then
			text = text .. "\n" .. ALittle.String_Join(new_log_list, "\n")
		end
		self._notice_edit.text = text
		self._notice_content.visible = false
		self._notice_edit.visible = true
		self._process_bg.visible = false
		self._process_bar.visible = false
		self._noupdate_btn.visible = true
		self._update_btn.visible = true
		self._check_btn.visible = false
		self._install_btn.visible = false
		self._restart_btn.visible = false
	elseif result == 1 then
		self._notice_content.text = "您当前已经是最新版本"
		self._notice_content.visible = true
		self._notice_edit.visible = false
		self._process_bg.visible = false
		self._process_bar.visible = false
		self._noupdate_btn.visible = false
		self._update_btn.visible = false
		self._check_btn.visible = true
		self._install_btn.visible = false
		self._restart_btn.visible = false
	elseif result == 11 then
		self._notice_content.text = "版本更新失败"
		self._notice_content.visible = true
		self._notice_edit.visible = false
		self._process_bg.visible = false
		self._process_bar.visible = false
		self._noupdate_btn.visible = false
		self._update_btn.visible = false
		self._check_btn.visible = true
		self._install_btn.visible = false
		self._restart_btn.visible = false
	elseif result == 12 then
		self._notice_content.text = "版本更新成功，重启软件生效"
		self._notice_content.visible = true
		self._notice_edit.visible = false
		self._process_bg.visible = true
		self._process_bar.visible = true
		self._noupdate_btn.visible = false
		self._update_btn.visible = false
		self._check_btn.visible = false
		self._install_btn.visible = false
		self._restart_btn.visible = true
	elseif result == 13 then
		self._notice_content.text = "版本更新成功，需要重新安装"
		self._notice_content.visible = true
		self._notice_edit.visible = false
		self._process_bg.visible = true
		self._process_bar.visible = true
		self._noupdate_btn.visible = false
		self._update_btn.visible = false
		self._check_btn.visible = false
		self._install_btn.visible = true
		self._restart_btn.visible = false
	end
end
IDEVersionManager.UpdateVersion = Lua.CoWrap(IDEVersionManager.UpdateVersion)

function IDEVersionManager:HandleUpdateVersion(file_name, cur_size, total_size, cur_file_index, file_count)
	self._notice_content.text = "版本正在更新..." .. ALittle.Math_Floor(self._version_system.current_update_size / self._version_system.total_update_size * 100) .. "%"
	self._notice_content.visible = true
	self._notice_edit.visible = false
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

g_IDEVersionManager = IDEVersionManager()
