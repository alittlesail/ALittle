-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


IDECenter = Lua.Class(nil, "ALittleIDE.IDECenter")

function IDECenter:Ctor()
end

function IDECenter:Setup()
	local ___COROUTINE = coroutine.running()
	g_Control:CreateControl("ide_main_scene", self, g_MainLayer)
	g_IDEProject:OpenLastProject()
	A_UISystem.keydown_callback = Lua.Bind(self.HandleShortcutKey, self)
end

function IDECenter:Shutdown()
	if self._account ~= nil then
		self._account:Shutdown()
	end
	if self._main_menu ~= nil then
		self._main_menu:Shutdown()
	end
	if self._center ~= nil then
		self._center:Shutdown()
	end
end

function IDECenter.__getter:center()
	return self._center
end

function IDECenter:RefreshProject()
	if g_IDEProject.project == nil then
		return
	end
	local project_name = g_IDEProject.project.name
	local name_list = g_IDECenter.center.content_edit:GetTabNameList()
	local tab_index = g_IDECenter.center.content_edit:GetCurTabIndex()
	g_IDEProject:CloseProject()
	g_IDEProject:OpenProject(project_name)
	local count = ALittle.List_MaxN(name_list)
	if count > 0 then
		local i = count
		while true do
			if not(i >= 1) then break end
			local control_info = g_IDEProject.project.ui.control_map[name_list[i]]
			if control_info ~= nil then
				g_IDECenter.center.content_edit:StartEditControlBySelect(control_info.name, control_info.info)
			end
			i = i+(-1)
		end
		g_IDECenter.center.content_edit:SetCurTabIndex(tab_index)
	end
end

function IDECenter:HandleShortcutKey(mod, sym, scancode)
	if A_UISystem.sym_map[1073741886] then
		g_IDEProject:RunProject()
		return
	end
	if self._center ~= nil then
		self._center:HandleShortcutKey()
	end
end

g_IDECenter = IDECenter()
