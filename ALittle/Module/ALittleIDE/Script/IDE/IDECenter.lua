-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


IDECenter = Lua.Class(nil, "ALittleIDE.IDECenter")

function IDECenter:Ctor()
end

function IDECenter:Setup()
	local ___COROUTINE = coroutine.running()
	Require(g_ScriptBasePath, "UIEdit/IDEUICenter")
	g_Control:CreateControl("ide_main_scene", self, g_MainLayer)
	g_IDEUICenter:Setup(self._edit_container)
	g_IDEUICenter:Show()
	A_UISystem.keydown_callback = Lua.Bind(self.HandleShortcutKey, self)
	g_IDEProjectManager:OpenLastProject()
end

function IDECenter:Shutdown()
	if self._account ~= nil then
		self._account:Shutdown()
	end
	if self._main_menu ~= nil then
		self._main_menu:Shutdown()
	end
	g_IDEUICenter:Shutdown()
end

function IDECenter:OpenProject(name)
	g_IDEProject:OpenProject(name)
end

function IDECenter:CloseProject()
	g_IDEControlManager:ClearControlItem()
	g_IDETabManager:CloseAllTab()
	g_IDEProject:CloseProject()
end

function IDECenter:RefreshProject()
	if g_IDEProject.project == nil then
		return
	end
	local project_name = g_IDEProject.project.name
	local name_list = g_IDETabManager:GetTabNameList()
	local tab_index = g_IDETabManager:GetCurTabIndex()
	self:CloseProject()
	self:OpenProject(project_name)
	local count = ALittle.List_MaxN(name_list)
	if count > 0 then
		local i = count
		while true do
			if not(i >= 1) then break end
			local control_info = g_IDEProject.project.ui.control_map[name_list[i]]
			if control_info ~= nil then
				g_IDETabManager:StartEditControlBySelect(control_info.name, control_info.info)
			end
			i = i+(-1)
		end
		g_IDETabManager:SetCurTabIndex(tab_index)
	end
end

function IDECenter:HandleShortcutKey(mod, sym, scancode)
	if A_UISystem.sym_map[1073741886] then
		g_IDEProjectManager:RunProject()
		return
	end
	g_IDEUICenter:HandleShortcutKey()
end

g_IDECenter = IDECenter()
