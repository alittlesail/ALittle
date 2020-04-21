
module("ABrowser", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1964309472, "ABrowser.AHomePageQuickInfo", {
name = "ABrowser.AHomePageQuickInfo", ns_name = "ABrowser", rl_name = "AHomePageQuickInfo", hash_code = -1964309472,
name_list = {"_quick_image","_quick_button","_quick_title"},
type_list = {"ALittle.Image","ALittle.DisplayObject","ALittle.DisplayObject"},
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
	for k, v in ___ipairs(screen_save.list) do
		local control_line = {}
		local quick = g_Control:CreateControl("abrowser_home_quick", control_line)
		control_line._quick_title.text = v.title
		self._home_screen:AddChild(quick)
		control_line._quick_image:SetTextureCut(v.file_path, math.floor(control_line._quick_image.width), math.floor(control_line._quick_image.height), false)
		control_line._quick_button:AddEventListener(___all_struct[-449066808], self, self.HandleQuickClick)
		local user_data = {}
		user_data.control_line = control_line
		user_data.module_info = v
		control_line._quick_button._user_data = user_data
		quick._user_data = user_data
	end
end

function AHomePage:ShowHomeScene()
	g_ABrowser.browser_tab.tab = self._home_scene
end

function AHomePage:HandleQuickClick(event)
	local user_data = event.target._user_data
	if user_data.module_info.download_info == nil then
		user_data.module_info.download_info = {}
	end
	g_ABrowser:LoadModule(user_data.module_info.module_name, user_data.module_info.download_info.ip, user_data.module_info.download_info.port, user_data.module_info.download_info.account_name)
end
AHomePage.HandleQuickClick = Lua.CoWrap(AHomePage.HandleQuickClick)

function AHomePage:RefreshQuick(module_name, module_info)
	local child_list = {}
	local child_list_count = 0
	local target_child = nil
	for k, v in ___ipairs(self._home_screen.childs) do
		local user_data = v._user_data
		if user_data.module_info.module_name == module_name then
			target_child = v
		else
			child_list_count = child_list_count + 1
			child_list[child_list_count] = v
		end
	end
	self._home_screen:RemoveAllChild()
	if target_child ~= nil then
		local user_data = target_child._user_data
		user_data.module_info = module_info
		local control_line = user_data.control_line
		control_line._quick_title.text = module_info.title
		control_line._quick_image:SetTextureCut(module_info.file_path, math.floor(control_line._quick_image.width), math.floor(control_line._quick_image.height), false)
		self._home_screen:AddChild(target_child)
	else
		local control_line = {}
		local quick = g_Control:CreateControl("abrowser_home_quick", control_line)
		control_line._quick_title.text = module_info.title
		self._home_screen:AddChild(quick)
		control_line._quick_image:SetTextureCut(module_info.file_path, math.floor(control_line._quick_image.width), math.floor(control_line._quick_image.height), false)
		control_line._quick_button:AddEventListener(___all_struct[-449066808], self, self.HandleQuickClick)
		local user_data = {}
		user_data.control_line = control_line
		user_data.module_info = module_info
		control_line._quick_button._user_data = user_data
		quick._user_data = user_data
		self._home_screen:AddChild(quick)
	end
	for k, v in ___ipairs(child_list) do
		self._home_screen:AddChild(v)
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
				table.remove(screen_save.list, k)
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
		table.insert(screen_save.list, 1, info)
		g_ConfigSystemUser:SetConfig("screen_save", screen_save)
		self:RefreshQuick(user_data.module_name, info)
	end
end

g_AHomePage = AHomePage()
