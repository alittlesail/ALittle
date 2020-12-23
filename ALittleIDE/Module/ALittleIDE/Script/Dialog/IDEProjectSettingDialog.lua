-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})

ALittleIDE.IDEProjectSettingDialog = Lua.Class(nil, "ALittleIDE.IDEProjectSettingDialog")

function ALittleIDE.IDEProjectSettingDialog:ShowSettingProject()
	if ALittleIDE.g_IDEProject.project == nil then
		g_AUITool:ShowNotice("错误", "当前没有打开的项目")
		return
	end
	if self._project_setting_dialog == nil then
		self._project_setting_dialog = ALittleIDE.g_Control:CreateControl("ide_setting_project_dialog", self)
		A_LayerManager:AddToModal(self._project_setting_dialog)
	end
	self._project_setting_dialog.visible = true
	self._default_show_width.text = ALittleIDE.g_IDEProject.project.config:GetConfig("default_show_width", 800)
	self._default_show_height.text = ALittleIDE.g_IDEProject.project.config:GetConfig("default_show_height", 600)
	self._default_font_path.text = ALittleIDE.g_IDEProject.project.config:GetConfig("default_font_path", "")
	self._default_font_size.text = ALittleIDE.g_IDEProject.project.config:GetConfig("default_font_size", 15)
end

function ALittleIDE.IDEProjectSettingDialog:HandleSettingProjectCancel(event)
	self._project_setting_dialog.visible = false
end

function ALittleIDE.IDEProjectSettingDialog:HandleSettingProjectConfirm(event)
	local default_show_width = ALittle.Math_ToInt(self._default_show_width.text)
	if default_show_width == nil or default_show_width <= 0 then
		g_AUITool:ShowNotice("错误", "默认宽度不合法")
		return
	end
	local default_show_height = ALittle.Math_ToInt(self._default_show_height.text)
	if default_show_height == nil or default_show_height <= 0 then
		g_AUITool:ShowNotice("错误", "默认高度不合法")
		return
	end
	local default_font_path = self._default_font_path.text
	local default_font_size = ALittle.Math_ToInt(self._default_font_size.text)
	if default_font_size == nil or default_font_size <= 0 then
		g_AUITool:ShowNotice("错误", "默认字体大小不合法")
		return
	end
	ALittleIDE.g_IDEProject.project.config:SetConfig("default_show_width", default_show_width)
	ALittleIDE.g_IDEProject.project.config:SetConfig("default_show_height", default_show_height)
	ALittleIDE.g_IDEProject.project.config:SetConfig("default_font_path", default_font_path)
	ALittleIDE.g_IDEProject.project.config:SetConfig("default_font_size", default_font_size)
	local changed_event = {}
	changed_event.default_show_width = default_show_width
	changed_event.default_show_height = default_show_height
	changed_event.default_font_path = default_font_path
	changed_event.default_font_size = default_font_size
	ALittleIDE.g_IDEProject:DispatchEvent(___all_struct[1787992834], changed_event)
	self._project_setting_dialog.visible = false
end

ALittleIDE.g_IDEProjectSettingDialog = ALittleIDE.IDEProjectSettingDialog()
end