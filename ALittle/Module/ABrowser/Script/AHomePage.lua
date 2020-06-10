-- ALittle Generate Lua And Do Not Edit This Line!
module("ABrowser", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1964309472, "ABrowser.AHomePageQuickInfo", {
name = "ABrowser.AHomePageQuickInfo", ns_name = "ABrowser", rl_name = "AHomePageQuickInfo", hash_code = -1964309472,
name_list = {"_quick","_quick_image","_quick_button","_quick_title","_quick_close"},
type_list = {"ALittle.DisplayObject","ALittle.Image","ALittle.DisplayObject","ALittle.DisplayObject","ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-436192718, "ABrowser.AHomePageScreenSaveInfoDetail", {
name = "ABrowser.AHomePageScreenSaveInfoDetail", ns_name = "ABrowser", rl_name = "AHomePageScreenSaveInfoDetail", hash_code = -436192718,
name_list = {"module_name","title","download_info","file_path"},
type_list = {"string","string","ABrowser.AModuleInfo","string"},
option_map = {}
})
ALittle.RegStruct(-24542868, "ABrowser.AHomePageScreenSaveInfo", {
name = "ABrowser.AHomePageScreenSaveInfo", ns_name = "ABrowser", rl_name = "AHomePageScreenSaveInfo", hash_code = -24542868,
name_list = {"list"},
type_list = {"List<ABrowser.AHomePageScreenSaveInfoDetail>"},
option_map = {}
})
ALittle.RegStruct(773055577, "ABrowser.AHomePageQuickUserData", {
name = "ABrowser.AHomePageQuickUserData", ns_name = "ABrowser", rl_name = "AHomePageQuickUserData", hash_code = 773055577,
name_list = {"control_line","module_info"},
type_list = {"ABrowser.AHomePageQuickInfo","ABrowser.AHomePageScreenSaveInfoDetail"},
option_map = {}
})
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

AHomePage = Lua.Class(nil, "ABrowser.AHomePage")

function AHomePage:Ctor()
end

function AHomePage:Setup()
	self._home_scene = g_Control:CreateControl("abrowser_home_scene", self)
	g_ABrowser.browser_tab:AddChild(self._home_scene)
	g_ABrowser.browser_tab:SetChildText(self._home_scene, "首页")
	g_ABrowser.browser_tab:DisableCloseButton(self._home_scene)
	g_ABrowser.browser_tab.tab = self._home_scene
	local screen_save = g_ConfigSystemUser:GetConfig("screen_save", {})
	if screen_save.list == nil then
		screen_save.list = {}
	end
	local module_map = self:GetExistModuleMap()
	for k, v in ___ipairs(screen_save.list) do
		module_map[v.module_name] = nil
	end
	local new_add = false
	for module_name, _ in ___pairs(module_map) do
		local info = {}
		info.module_name = module_name
		info.title = module_name
		ALittle.List_Push(screen_save.list, info)
		new_add = true
	end
	if new_add then
		g_ConfigSystemUser:SetConfig("screen_save", screen_save)
	end
	for k, v in ___ipairs(screen_save.list) do
		self:CreateQuickItem(v)
	end
end

function AHomePage:GetExistModuleMap()
	local module_map = {}
	local file_map = ALittle.File_GetFileNameListByDir(g_ModuleBasePath .. "..")
	for name, info in ___pairs(file_map) do
		if info.mode == "directory" then
			module_map[name] = true
		end
	end
	return module_map
end

function AHomePage:CreateQuickItem(info)
	local control_line = {}
	control_line._quick = g_Control:CreateControl("abrowser_home_quick", control_line)
	control_line._quick_title.text = info.title
	self._home_screen:AddChild(control_line._quick)
	if info.file_path ~= nil and ALittle.File_GetFileAttr(info.file_path) ~= nil then
		control_line._quick_image:SetTextureCut(info.file_path, ALittle.Math_Floor(control_line._quick_image.width), ALittle.Math_Floor(control_line._quick_image.height), false)
	end
	control_line._quick_button:AddEventListener(___all_struct[-449066808], self, self.HandleQuickLoadClick)
	control_line._quick_close:AddEventListener(___all_struct[-449066808], self, self.HandleQuickDeleteClick)
	local user_data = {}
	user_data.control_line = control_line
	user_data.module_info = info
	control_line._quick_close._user_data = user_data
	control_line._quick_button._user_data = user_data
	control_line._quick._user_data = user_data
end

function AHomePage:ShowHomeScene()
	g_ABrowser.browser_tab.tab = self._home_scene
end

function AHomePage:HandleQuickLoadClick(event)
	local user_data = event.target._user_data
	if user_data.module_info.download_info == nil then
		user_data.module_info.download_info = {}
	end
	g_ABrowser:LoadModule(user_data.module_info.module_name, user_data.module_info.download_info.ip, user_data.module_info.download_info.port, user_data.module_info.download_info.account_name)
end
AHomePage.HandleQuickLoadClick = Lua.CoWrap(AHomePage.HandleQuickLoadClick)

function AHomePage:HandleQuickDeleteClick(event)
	local user_data = event.target._user_data
	local index = self._home_screen:GetChildIndex(user_data.control_line._quick)
	self._home_screen:RemoveChild(user_data.control_line._quick)
	local screen_save = g_ConfigSystemUser:GetConfig("screen_save", {})
	if screen_save.list == nil then
		screen_save.list = {}
	end
	ALittle.List_Remove(screen_save.list, index)
end
AHomePage.HandleQuickDeleteClick = Lua.CoWrap(AHomePage.HandleQuickDeleteClick)

function AHomePage:RefreshQuick(module_name, module_info)
	local find = false
	for k, v in ___ipairs(self._home_screen.childs) do
		local user_data = v._user_data
		if user_data.module_info.module_name == module_name then
			user_data.module_info = module_info
			local control_line = user_data.control_line
			control_line._quick_title.text = module_info.title
			control_line._quick_image:SetTextureCut(module_info.file_path, ALittle.Math_Floor(control_line._quick_image.width), ALittle.Math_Floor(control_line._quick_image.height), false)
			break
		end
	end
	if not find then
		self:CreateQuickItem(module_info)
	end
end

function AHomePage:SaveModuleScreen(child)
	local loop = ALittle.LoopFunction(Lua.Bind(self.SaveModuleScreenImpl, self, child), 1, 1, 2000)
	loop:Start()
end

function AHomePage:SaveModuleScreenImpl(child)
	local user_data = child._user_data
	ALittle.File_MakeDir(g_ModuleBasePathEx .. "/ModuleScreenSave")
	local file_path = g_ModuleBasePathEx .. "/ModuleScreenSave/" .. ALittle.String_MD5(user_data.module_name) .. ".png"
	local result = g_Control:SaveControlToFile(child, file_path, 720 / ALittle.System_GetScreenWidth())
	if result then
		local screen_save = g_ConfigSystemUser:GetConfig("screen_save", {})
		if screen_save.list == nil then
			screen_save.list = {}
		end
		for k, v in ___ipairs(screen_save.list) do
			if v.module_name == user_data.module_name then
				ALittle.List_Remove(screen_save.list, k)
				self._home_screen:RemoveChild(self._home_screen:GetChildByIndex(k))
				break
			end
		end
		local info = {}
		info.module_name = user_data.module_name
		info.title = user_data.module_name
		if user_data.module_info ~= nil and user_data.module_info.title ~= nil then
			info.title = user_data.module_info.title
		end
		info.download_info = g_AModuleDownload:GetDownloadInfo(user_data.module_name)
		if info.download_info == nil then
			info.download_info = {}
		end
		info.file_path = file_path
		ALittle.List_Insert(screen_save.list, 1, info)
		g_ConfigSystemUser:SetConfig("screen_save", screen_save)
		self:RefreshQuick(user_data.module_name, info)
	end
end

g_AHomePage = AHomePage()
