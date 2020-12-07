-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.NESEmulator == nil then _G.NESEmulator = {} end
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(124598654, "ALittle.UISystemSelectFileEvent", {
name = "ALittle.UISystemSelectFileEvent", ns_name = "ALittle", rl_name = "UISystemSelectFileEvent", hash_code = 124598654,
name_list = {"target","path"},
type_list = {"ALittle.DisplayObject","string"},
option_map = {}
})

NESEmulator.g_GConfig = nil
NESEmulator.GCenter = Lua.Class(nil, "NESEmulator.GCenter")

function NESEmulator.GCenter:Ctor()
end

function NESEmulator.GCenter:Setup()
	NESEmulator.g_GConfig = ALittle.CreateConfigSystem(NESEmulator.g_ModuleBasePath .. "/User.cfg")
	ALittle.Math_RandomSeed(ALittle.Time_GetCurTime())
	ALittle.System_SetThreadCount(1)
	self._main_layer = ALittle.DisplayLayout(NESEmulator.g_Control)
	self._main_layer.width_type = 4
	self._main_layer.height_type = 4
	NESEmulator.g_LayerGroup:AddChild(self._main_layer, nil)
	self._dialog_layer = ALittle.DisplayLayout(NESEmulator.g_Control)
	self._dialog_layer.width_type = 4
	self._dialog_layer.height_type = 4
	NESEmulator.g_LayerGroup:AddChild(self._dialog_layer, nil)
	local main_scene = NESEmulator.g_Control:CreateControl("main_scene", self, self._main_layer)
	local group = {}
	self._file_menu.group = group
	self._rom_menu.group = group
	self._help_menu.group = group
	self._file_menu:AddEventListener(___all_struct[124598654], 1, self.HandleSelectFile)
	local screen = ALittle.DynamicImage(NESEmulator.g_Control)
	screen.width_type = 4
	screen.height_type = 4
	screen:SetSurfaceSize(NESEmulator.SCREEN_WIDTH, NESEmulator.SCREEN_HEIGHT, 0)
	self._canvas:AddChild(screen)
	g_GNes:Setup(screen)
end

function NESEmulator.GCenter:HandleFileClick(event)
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("打开", Lua.Bind(self.HandleOpenFile, self))
	menu:AddItem("退出", Lua.Bind(self.HandleExit, self))
	menu:Show(self._file_menu)
end

function NESEmulator.GCenter:HandleRomClick(event)
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("坦克大战", Lua.Bind(self.HandleLoadRom, self, "BattleCity.nes"))
	menu:AddItem("马里奥兄弟", Lua.Bind(self.HandleLoadRom, self, "SuperMarioBros.nes"))
	menu:AddItem("重装机兵", Lua.Bind(self.HandleLoadRom, self, "MetalMax.nes"))
	menu:Show(self._rom_menu)
end

function NESEmulator.GCenter:HandleHelpClick(event)
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("控制器", Lua.Bind(self.HandleShowControl, self))
	menu:AddItem("关于", Lua.Bind(self.HandleShowAbout, self))
	menu:AddItem("版本更新", Lua.Bind(self.HandleVersionUpdate, self))
	menu:Show(self._help_menu)
end

function NESEmulator.GCenter:HandleShowControl()
	g_AUITool:ShowNotice("提示", "左:A    右:D\n上:W    下:D\n选择:G    开始:H\nB键:J    A键:K")
end

function NESEmulator.GCenter:HandleShowAbout()
	g_AUITool:ShowNotice("提示", "本模拟器提供的ROM只提供学习使用，不作为商业用途")
end

function NESEmulator.GCenter:HandleVersionUpdate()
	NESEmulator.g_VersionManager:ShowDialog()
end

function NESEmulator.GCenter:HandleSelectFile(event)
	local error = g_GNes:LoadROMFromPath(event.path)
	if error ~= nil then
		g_AUITool:ShowNotice("错误", error)
	end
end
NESEmulator.GCenter.HandleSelectFile = Lua.CoWrap(NESEmulator.GCenter.HandleSelectFile)

function NESEmulator.GCenter:HandleLoadRom(file_name)
	local error = g_GNes:LoadROMFromOther(file_name)
	if error ~= nil then
		g_AUITool:ShowNotice("错误", error)
	end
end
NESEmulator.GCenter.HandleLoadRom = Lua.CoWrap(NESEmulator.GCenter.HandleLoadRom)

function NESEmulator.GCenter:HandleOpenFile()
	A_OtherSystem:SystemSelectFile(self._file_menu)
end

function NESEmulator.GCenter:HandleExit()
	ALittle.System_Exit()
end

function NESEmulator.GCenter:Shutdown()
	g_GNes:Shutdown()
end

_G.g_GCenter = NESEmulator.GCenter()
end