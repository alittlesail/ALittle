-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

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
name_list = {"target","is_drag"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})

IDEProjectFindFileDialog = Lua.Class(nil, "ALittleIDE.IDEProjectFindFileDialog")

function IDEProjectFindFileDialog:ShowFindFile()
	if g_IDEProject.project == nil then
		g_AUITool:ShowNotice("错误", "当前没有打开的项目")
		return
	end
	if self._project_find_file_dialog == nil then
		self._project_find_file_dialog = g_Control:CreateControl("ide_find_file_dialog", self)
		A_LayerManager:AddToModal(self._project_find_file_dialog)
	end
	self._project_find_file_dialog.visible = true
end

function IDEProjectFindFileDialog:HandleSearchClick(event)
	self._file_scroll_screen:RemoveAllChild()
	local text = ALittle.String_Trim(self._find_input.text)
	if text == nil then
		return
	end
	if g_IDEProject.project == nil then
		return
	end
	if g_IDEProject.project.code == nil then
		return
	end
	local file_list = g_IDEProject.project.code:FindFile(text)
	for index, file_path in ___ipairs(file_list) do
		local item = g_Control:CreateControl("ide_common_item_checkbutton")
		item:AddEventListener(___all_struct[-449066808], self, self.HandleItemClick)
		item.text = file_path
		item._user_data = file_path
		self._file_scroll_screen:AddChild(item)
	end
end
IDEProjectFindFileDialog.HandleSearchClick = Lua.CoWrap(IDEProjectFindFileDialog.HandleSearchClick)

function IDEProjectFindFileDialog:HandleItemClick(event)
	local code_child = g_IDECenter.center.code_list:OpenByFullPath(event.target._user_data, 1, 1, 1, 1)
	if code_child == nil then
		return
	end
	code_child:FindText(self._find_input.text)
end

g_IDEProjectFindFileDialog = IDEProjectFindFileDialog()
