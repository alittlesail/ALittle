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
ALittle.RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name = "ALittle.UIButtonEvent", ns_name = "ALittle", rl_name = "UIButtonEvent", hash_code = -1347278145,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name = "ALittle.UIRButtonDownEvent", ns_name = "ALittle", rl_name = "UIRButtonDownEvent", hash_code = -641444818,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEUIProjectList = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEUIProjectList")

function ALittleIDE.IDEUIProjectList:HandleProjectSearchClick(event)
	self._project_scroll_screen:RemoveAllChild()
	local key = self._project_search_key.text
	local project_map = ALittleIDE.g_IDEConfig:GetConfig("project_map", {})
	for k, v in ___pairs(project_map) do
		if key == "" or ALittle.String_Find(v, key) ~= nil then
			local item = ALittleIDE.g_Control:CreateControl("aui_menu_item_button")
			item.text = v
			item.drag_trans_target = self._project_scroll_screen
			item:AddEventListener(___all_struct[-641444818], self, self.HandleProjectItemRightClick)
			self._project_scroll_screen:AddChild(item)
		end
	end
end

function ALittleIDE.IDEUIProjectList:HandleProjectItemRightClick(event)
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("打开", Lua.Bind(self.HandleRightProjectOpen, self, event.target))
	menu:AddItem("关闭", Lua.Bind(self.HandleRightProjectClose, self, event.target))
	menu:AddItem("移除", Lua.Bind(self.HandleRightProjectRemove, self, event.target))
	menu:Show()
end

function ALittleIDE.IDEUIProjectList:HandleRightProjectOpen(target)
	local project_name = target.text
	if not ALittleIDE.g_IDECenter.center.content_edit:IsSaveAll() then
		local result = g_AUITool:SaveNotice("提示", "是否保存当前项目?")
		if result == "YES" then
			ALittleIDE.g_IDECenter.center.content_edit:SaveAllTab()
		end
	end
	local error = ALittleIDE.g_IDEProject:OpenProject(project_name)
	if error ~= nil then
		g_AUITool:ShowNotice("错误", error)
	end
end
ALittleIDE.IDEUIProjectList.HandleRightProjectOpen = Lua.CoWrap(ALittleIDE.IDEUIProjectList.HandleRightProjectOpen)

function ALittleIDE.IDEUIProjectList:HandleRightProjectRemove(target)
	local project_name = target.text
	if ALittleIDE.g_IDEProject.project ~= nil and ALittleIDE.g_IDEProject.project.name == project_name then
		g_AUITool:ShowNotice("提示", "当前项目正在编辑，请先关闭")
		return
	end
	self._project_scroll_screen:RemoveChild(target)
	ALittleIDE.g_IDEProject:RemoveProject(project_name)
end

function ALittleIDE.IDEUIProjectList:HandleRightProjectClose(target)
	local project_name = target.text
	if ALittleIDE.g_IDEProject.project == nil or ALittleIDE.g_IDEProject.project.name ~= project_name then
		return
	end
	if not ALittleIDE.g_IDECenter.center.content_edit:IsSaveAll() then
		local result = g_AUITool:SaveNotice("提示", "是否保存当前项目?")
		if result == "YES" then
			ALittleIDE.g_IDECenter.center.content_edit:SaveAllTab()
		end
	end
	ALittleIDE.g_IDEProject:CloseProject()
end
ALittleIDE.IDEUIProjectList.HandleRightProjectClose = Lua.CoWrap(ALittleIDE.IDEUIProjectList.HandleRightProjectClose)

end