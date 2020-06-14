-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


IDEProjectExportDialog = Lua.Class(nil, "ALittleIDE.IDEProjectExportDialog")

function IDEProjectExportDialog:ShowExportProject()
	if g_IDEProject.project == nil then
		g_AUITool:ShowNotice("错误", "当前没有打开的项目")
		return
	end
	if self._export_dialog == nil then
		self._export_dialog = g_Control:CreateControl("ide_export_dialog", self)
		g_DialogLayer:AddChild(self._export_dialog)
		self._main_export_tab:DisableAllCloseButton()
		self._main_export_tab.tab_index = 1
		self._export_windows_official.config_key = "export_windows_official"
		self._export_android_official.config_key = "export_android_official"
		self._export_ios_official.config_key = "export_ios_official"
	end
	self._export_dialog.visible = true
	self._export_windows_official:LoadConfigImpl()
	self._export_android_official:LoadConfigImpl()
	self._export_ios_official:LoadConfigImpl()
end

g_IDEProjectExportDialog = IDEProjectExportDialog()
