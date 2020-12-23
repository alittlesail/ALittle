-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


ALittleIDE.IDEProjectOpenDialog = Lua.Class(nil, "ALittleIDE.IDEProjectOpenDialog")

function ALittleIDE.IDEProjectOpenDialog:ShowOpenProject()
	if self._project_open_dialog == nil then
		self._project_open_dialog = ALittleIDE.g_Control:CreateControl("ide_open_project_dialog", self)
		A_LayerManager:AddToModal(self._project_open_dialog)
	end
	self._project_open_name.text = ""
	self._project_open_dialog.visible = true
	local module_list = {}
	local file_map = ALittle.File_GetNameListByDir(ALittleIDE.g_ModuleBasePath .. "..")
	for name, info in ___pairs(file_map) do
		if info.directory then
			ALittle.List_Push(module_list, name)
		end
	end
	self._project_dropdown.data_list = module_list
	self._project_dropdown.text = ""
	A_UISystem.focus = self._project_open_name.show_input
end

function ALittleIDE.IDEProjectOpenDialog:HandleOpenProjectSelect(event)
	self._project_open_name.text = event.target.text
	event.target.text = ""
end

function ALittleIDE.IDEProjectOpenDialog:HandleOpenProjectCancel(event)
	self._project_open_dialog.visible = false
end

function ALittleIDE.IDEProjectOpenDialog:HandleOpenProjectConfirm(event)
	self._project_open_dialog.visible = false
	local name = self._project_open_name.text
	if not ALittleIDE.g_IDECenter.center.content_edit:IsSaveAll() then
		local result = g_AUITool:SaveNotice("提示", "是否保存当前项目?")
		if result == "YES" then
			ALittleIDE.g_IDECenter.center.content_edit:SaveAllTab()
		end
	end
	local error = ALittleIDE.g_IDEProject:OpenProject(name)
	if error ~= nil then
		g_AUITool:ShowNotice("错误", error)
		return
	end
end
ALittleIDE.IDEProjectOpenDialog.HandleOpenProjectConfirm = Lua.CoWrap(ALittleIDE.IDEProjectOpenDialog.HandleOpenProjectConfirm)

ALittleIDE.g_IDEProjectOpenDialog = ALittleIDE.IDEProjectOpenDialog()
end