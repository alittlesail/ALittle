-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
IDEUIProjectDropdown = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEUIProjectDropdown")

function IDEUIProjectDropdown:TCtor()
	self:UpdateProjectList()
	g_IDEProject:AddEventListener(___all_struct[-975432877], self, self.HandleProjectOpen)
	g_IDEProject:AddEventListener(___all_struct[-332308624], self, self.HandleProjectClose)
end

function IDEUIProjectDropdown:Shutdown()
end

function IDEUIProjectDropdown:HandleProjectOpen(event)
	self:UpdateProjectList()
end

function IDEUIProjectDropdown:HandleProjectClose(event)
	self:UpdateProjectList()
end

function IDEUIProjectDropdown:UpdateProjectList()
	if g_IDEProject.project == nil then
		self._current_project_name.text = "当前没有打开的项目"
	else
		self._current_project_name.text = g_IDEProject.project.name
	end
	local data_list = {}
	local data_list_count = 0
	local project_map = g_IDEConfig:GetConfig("project_map", {})
	for k, v in ___pairs(project_map) do
		data_list_count = data_list_count + 1
		data_list[data_list_count] = v
	end
	ALittle.List_Sort(data_list)
	local text = self._current_project_name.text
	self._current_project_name.data_list = data_list
	self._current_project_name.text = text
end

function IDEUIProjectDropdown:HandlePeojectSelectChange(event)
	local name = ""
	if g_IDEProject.project ~= nil then
		name = g_IDEProject.project.name
	end
	local new_name = event.target.text
	if new_name == name then
		return
	end
	if g_IDECenter.center.content_edit:IsSaveAll() then
		local error = g_IDEProject:OpenProject(new_name)
		if error ~= nil then
			g_AUITool:ShowNotice("错误", error)
		end
		return
	end
	event.target.text = name
	local result = g_AUITool:SaveNotice("提示", "是否保存当前项目?")
	if result == "YES" then
		g_IDECenter.center.content_edit:SaveAllTab()
	end
	local error = g_IDEProject:OpenProject(new_name)
	if error ~= nil then
		g_AUITool:ShowNotice("错误", error)
	end
end
IDEUIProjectDropdown.HandlePeojectSelectChange = Lua.CoWrap(IDEUIProjectDropdown.HandlePeojectSelectChange)

