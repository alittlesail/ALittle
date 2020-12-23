-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


ALittleIDE.IDEProjectExportDialog = Lua.Class(nil, "ALittleIDE.IDEProjectExportDialog")

function ALittleIDE.IDEProjectExportDialog:ShowExportProject()
	if ALittleIDE.g_IDEProject.project == nil then
		g_AUITool:ShowNotice("错误", "当前没有打开的项目")
		return
	end
	if self._export_dialog == nil then
		self._export_dialog = ALittleIDE.g_Control:CreateControl("ide_export_dialog", self)
		ALittleIDE.g_DialogLayer:AddChild(self._export_dialog)
		self._main_export_tab:DisableAllCloseButton()
		self._main_export_tab.tab_index = 1
	end
	self._export_dialog.visible = true
	self._export_windows:LoadConfigImpl()
	self._export_android:LoadConfigImpl()
	self._export_ios:LoadConfigImpl()
	self._export_web:LoadConfigImpl()
	self._export_wechat:LoadConfigImpl()
end

ALittleIDE.g_IDEProjectExportDialog = ALittleIDE.IDEProjectExportDialog()
end