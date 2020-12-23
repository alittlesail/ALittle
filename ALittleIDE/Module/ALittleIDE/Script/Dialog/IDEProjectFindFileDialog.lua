-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name = "ALittle.UIClickEvent", ns_name = "ALittle", rl_name = "UIClickEvent", hash_code = -449066808,
name_list = {"target","is_drag","count"},
type_list = {"ALittle.DisplayObject","bool","int"},
option_map = {}
})

ALittleIDE.IDEProjectFindFileDialog = Lua.Class(nil, "ALittleIDE.IDEProjectFindFileDialog")

function ALittleIDE.IDEProjectFindFileDialog:ShowFindFile()
	if ALittleIDE.g_IDEProject.project == nil then
		g_AUITool:ShowNotice("错误", "当前没有打开的项目")
		return
	end
	if self._project_find_file_dialog == nil then
		self._project_find_file_dialog = ALittleIDE.g_Control:CreateControl("ide_find_file_dialog", self)
		self._project_find_file_dialog.x = (A_UISystem.view_width - self._project_find_file_dialog.width) / 2
		self._project_find_file_dialog.y = (A_UISystem.view_height - self._project_find_file_dialog.height) / 2
		ALittleIDE.g_DialogLayer:AddChild(self._project_find_file_dialog)
	end
	self._project_find_file_dialog.visible = true
	self._project_find_file_dialog:MoveToTop()
	self._find_input:DelayFocus()
end

function ALittleIDE.IDEProjectFindFileDialog:HideDialog()
	if self._project_find_file_dialog == nil then
		return
	end
	self._project_find_file_dialog.visible = false
end

function ALittleIDE.IDEProjectFindFileDialog:IsShow()
	if self._project_find_file_dialog == nil then
		return false
	end
	return self._project_find_file_dialog.visible
end

function ALittleIDE.IDEProjectFindFileDialog:HandleEnterKeyClick(event)
	self:HandleSearchClick(nil)
end

function ALittleIDE.IDEProjectFindFileDialog:HandleSearchClick(event)
	self._file_scroll_screen:RemoveAllChild()
	local text = ALittle.String_Trim(self._find_input.text)
	if text == nil then
		return
	end
	if ALittleIDE.g_IDEProject.project == nil then
		return
	end
	if ALittleIDE.g_IDEProject.project.code == nil then
		return
	end
	local file_list = ALittleIDE.g_IDEProject.project.code:FindFile(text)
	for index, file_path in ___ipairs(file_list) do
		local item = ALittleIDE.g_Control:CreateControl("scroll_screen_item_checkbutton")
		item:AddEventListener(___all_struct[-449066808], self, self.HandleItemClick)
		item.text = file_path
		item._user_data = file_path
		self._file_scroll_screen:AddChild(item)
	end
end
ALittleIDE.IDEProjectFindFileDialog.HandleSearchClick = Lua.CoWrap(ALittleIDE.IDEProjectFindFileDialog.HandleSearchClick)

function ALittleIDE.IDEProjectFindFileDialog:HandleItemClick(event)
	local code_child = ALittleIDE.g_IDECenter.center.code_list:OpenByFullPath(event.target._user_data, 1, 1, 1, 1)
	if code_child == nil then
		return
	end
	code_child:FindText(self._find_input.text)
end

ALittleIDE.g_IDEProjectFindFileDialog = ALittleIDE.IDEProjectFindFileDialog()
end