-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


ALittleIDE.IDEProjectNewDialog = Lua.Class(nil, "ALittleIDE.IDEProjectNewDialog")

function ALittleIDE.IDEProjectNewDialog:ShowNewProject()
	if self._project_new_dialog == nil then
		self._project_new_dialog = ALittleIDE.g_Control:CreateControl("ide_new_project_dialog", self)
		A_LayerManager:AddToModal(self._project_new_dialog)
	end
	self._project_new_name.text = ""
	self._project_new_dialog.visible = true
	A_UISystem.focus = self._project_new_name.show_input
end

function ALittleIDE.IDEProjectNewDialog:HandleNewProjectCancel(event)
	self._project_new_dialog.visible = false
end

function ALittleIDE.IDEProjectNewDialog:HandleNewProjectConfirm(event)
	local name = self._project_new_name.text
	if name == "" then
		g_AUITool:ShowNotice("错误", "请输入项目名")
		return
	end
	if ALittleIDE.IDEUtility_CheckName(name) ~= nil then
		g_AUITool:ShowNotice("错误", "项目名不合法:" .. name)
		return
	end
	if ALittle.File_GetFileAttr(ALittle.File_BaseFilePath() .. name) ~= nil then
		g_AUITool:ShowNotice("错误", "项目已存在:" .. name)
		return
	end
	local size_list = ALittle.String_Split(self._view_size_dropdown.text, "x")
	local window_width = ALittle.Math_ToInt(size_list[1])
	if window_width == nil then
		window_width = 800
	end
	local window_height = ALittle.Math_ToInt(size_list[2])
	if window_height == nil then
		window_height = 600
	end
	local font_path = self._default_font_path.text
	local font_size = ALittle.Math_ToInt(self._default_font_size.text)
	if font_size == nil then
		font_size = 25
	end
	ALittleIDE.g_IDEProject:NewProject(name, ALittle.Math_Floor(window_width), ALittle.Math_Floor(window_height), font_path, ALittle.Math_Floor(font_size))
	if ALittleIDE.g_IDEProject.project == nil then
		ALittleIDE.g_IDEProject:OpenProject(name)
	end
	self._project_new_dialog.visible = false
end

ALittleIDE.g_IDEProjectNewDialog = ALittleIDE.IDEProjectNewDialog()
end