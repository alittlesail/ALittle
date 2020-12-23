-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


ALittleIDE.IDECenter = Lua.Class(nil, "ALittleIDE.IDECenter")

function ALittleIDE.IDECenter:Setup()
	local ___COROUTINE = coroutine.running()
	ALittleIDE.g_Control:CreateControl("ide_main_scene", self, ALittleIDE.g_MainLayer)
	ALittleIDE.g_IDEProject:OpenLastProject()
	A_UISystem.keydown_callback = Lua.Bind(self.HandleShortcutKey, self)
	A_UISystem.quit_callback = Lua.Bind(self.HandleQuit, self)
end

function ALittleIDE.IDECenter:Shutdown()
	if self._account ~= nil then
		self._account:Shutdown()
	end
	if self._main_menu ~= nil then
		self._main_menu:Shutdown()
	end
end

function ALittleIDE.IDECenter.__getter:center()
	return self._center
end

function ALittleIDE.IDECenter:RefreshProject()
	if not self._center.content_edit:IsSaveAll() then
		local result = g_AUITool:SaveNotice("提示", "是否保存当前项目?")
		if result == "YES" then
			self._center.content_edit:SaveAllTab()
		end
	end
	ALittleIDE.g_IDEProject:RefreshProject()
end
ALittleIDE.IDECenter.RefreshProject = Lua.CoWrap(ALittleIDE.IDECenter.RefreshProject)

function ALittleIDE.IDECenter:HandleShortcutKey(mod, sym, scancode)
	if A_UISystem.sym_map[1073741886] then
		if ALittleIDE.g_IDEProject:IsDebug() then
			ALittleIDE.g_IDEProject:ContinueDebug()
		else
			ALittleIDE.g_IDEProject:RunProject(true)
			ALittleIDE.g_IDEProject:StartDebugProject()
		end
		return
	end
	if A_UISystem.sym_map[1073741887] then
		ALittleIDE.g_IDEProject:StopDebugProject()
		ALittleIDE.g_IDEProject:RunProject(false)
		return
	end
	if A_UISystem.sym_map[1073741891] then
		if ALittleIDE.g_IDEProject:IsDebug() then
			ALittleIDE.g_IDEProject:NextLineDebug()
		end
		return
	end
	if self._center ~= nil then
		self._center:HandleShortcutKey()
	end
end

function ALittleIDE.IDECenter:HandleQuit()
	if self._center.content_edit:IsSaveAll() then
		return true
	end
	self:HandleQuitImpl()
	return false
end

function ALittleIDE.IDECenter:HandleQuitImpl()
	local result = g_AUITool:SaveNotice("提示", "是否保存当前项目?")
	if result == "YES" then
		self._center.content_edit:SaveAllTab()
	end
	ALittle.System_Exit()
end
ALittleIDE.IDECenter.HandleQuitImpl = Lua.CoWrap(ALittleIDE.IDECenter.HandleQuitImpl)

ALittleIDE.g_IDECenter = ALittleIDE.IDECenter()
end