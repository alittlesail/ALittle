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
IDEUIProjectList = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEUIProjectList")

function IDEUIProjectList:HandleProjectSearchClick(event)
	self._project_scroll_screen:RemoveAllChild()
	local key = self._project_search_key.text
	local project_map = g_IDEConfig:GetConfig("project_map", {})
	for k, v in ___pairs(project_map) do
		if key == "" or ALittle.String_Find(v, key) ~= nil then
			local item = g_Control:CreateControl("ide_common_item_button")
			item.text = v
			item.drag_trans_target = self._project_scroll_screen
			item:AddEventListener(___all_struct[-641444818], self, self.HandleProjectItemRightClick)
			self._project_scroll_screen:AddChild(item)
		end
	end
end

function IDEUIProjectList:HandleProjectItemRightClick(event)
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("打开", Lua.Bind(self.HandleRightProjectOpen, self, event.target))
	menu:AddItem("关闭", Lua.Bind(self.HandleRightProjectClose, self, event.target))
	menu:AddItem("刷新", Lua.Bind(self.HandleRightProjectRefresh, self, event.target))
	menu:AddItem("移除", Lua.Bind(self.HandleRightProjectRemove, self, event.target))
end

function IDEUIProjectList:HandleRightProjectOpen(target)
	local project_name = target.text
	if not g_IDECenter.center.content_edit:IsSaveAll() then
		local result = g_AUITool:SaveNotice("提示", "是否保存当前项目?")
		if result == "YES" then
			g_IDECenter.center.content_edit:SaveAllTab()
		end
	end
	local error = g_IDEProject:OpenProject(project_name)
	if error ~= nil then
		g_AUITool:ShowNotice("错误", error)
	end
end
IDEUIProjectList.HandleRightProjectOpen = Lua.CoWrap(IDEUIProjectList.HandleRightProjectOpen)

function IDEUIProjectList:HandleRightProjectRemove(target)
	local project_name = target.text
	if g_IDEProject.project ~= nil and g_IDEProject.project.name == project_name then
		g_AUITool:ShowNotice("提示", "当前项目正在编辑，请先关闭")
		return
	end
	self._project_scroll_screen:RemoveChild(target)
	g_IDEProject:RemoveProject(project_name)
end

function IDEUIProjectList:HandleRightProjectClose(target)
	local project_name = target.text
	if g_IDEProject.project == nil or g_IDEProject.project.name ~= project_name then
		return
	end
	if not g_IDECenter.center.content_edit:IsSaveAll() then
		local result = g_AUITool:SaveNotice("提示", "是否保存当前项目?")
		if result == "YES" then
			g_IDECenter.center.content_edit:SaveAllTab()
		end
	end
	g_IDEProject:CloseProject()
end
IDEUIProjectList.HandleRightProjectClose = Lua.CoWrap(IDEUIProjectList.HandleRightProjectClose)

function IDEUIProjectList:RefreshProject()
	if not g_IDECenter.center.content_edit:IsSaveAll() then
		local result = g_AUITool:SaveNotice("提示", "是否保存当前项目?")
		if result == "YES" then
			g_IDECenter.center.content_edit:SaveAllTab()
		end
	end
	g_IDECenter:RefreshProject()
end
IDEUIProjectList.RefreshProject = Lua.CoWrap(IDEUIProjectList.RefreshProject)

function IDEUIProjectList:HandleRightProjectRefresh(target)
	local project_name = target.text
	if g_IDEProject.project == nil or g_IDEProject.project.name ~= project_name then
		return
	end
	self:RefreshProject()
end

