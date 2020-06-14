-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
IDEUIProjectList = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEUIProjectList")

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

