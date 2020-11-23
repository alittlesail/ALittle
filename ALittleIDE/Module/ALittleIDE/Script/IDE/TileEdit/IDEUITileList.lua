-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(2117383637, "AUIPlugin.AUIFileSelectFileEvent", {
name = "AUIPlugin.AUIFileSelectFileEvent", ns_name = "AUIPlugin", rl_name = "AUIFileSelectFileEvent", hash_code = 2117383637,
name_list = {"target","info"},
type_list = {"ALittle.DisplayObject","AUIPlugin.AUIFileTreeUserInfo"},
option_map = {}
})
ALittle.RegStruct(-2082217254, "AUIPlugin.AUIFileCreateFileEvent", {
name = "AUIPlugin.AUIFileCreateFileEvent", ns_name = "AUIPlugin", rl_name = "AUIFileCreateFileEvent", hash_code = -2082217254,
name_list = {"target","path"},
type_list = {"ALittle.DisplayObject","string"},
option_map = {}
})
ALittle.RegStruct(1826926916, "ALittleIDE.IDETileTreeUserInfo", {
name = "ALittleIDE.IDETileTreeUserInfo", ns_name = "ALittleIDE", rl_name = "IDETileTreeUserInfo", hash_code = 1826926916,
name_list = {"info","module_name"},
type_list = {"AUIPlugin.AUIFileTreeUserInfo","string"},
option_map = {}
})
ALittle.RegStruct(-1718818319, "AUIPlugin.AUIFileDeleteDirEvent", {
name = "AUIPlugin.AUIFileDeleteDirEvent", ns_name = "AUIPlugin", rl_name = "AUIFileDeleteDirEvent", hash_code = -1718818319,
name_list = {"target","path"},
type_list = {"ALittle.DisplayObject","string"},
option_map = {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-686652419, "AUIPlugin.AUIFileTreeUserInfo", {
name = "AUIPlugin.AUIFileTreeUserInfo", ns_name = "AUIPlugin", rl_name = "AUIFileTreeUserInfo", hash_code = -686652419,
name_list = {"path","name","root","group","on_right_menu","on_select_file","on_delete_file","on_create_file","on_delete_dir"},
type_list = {"string","string","bool","Map<ALittle.TextRadioButton,bool>","Functor<(AUIPlugin.AUIFileTreeUserInfo,AUIPlugin.AUIRightMenu)>","Functor<(AUIPlugin.AUIFileTreeUserInfo)>","Functor<(string)>","Functor<(string)>","Functor<(string)>"},
option_map = {}
})
ALittle.RegStruct(-545221029, "AUIPlugin.AUIFileDeleteFileEvent", {
name = "AUIPlugin.AUIFileDeleteFileEvent", ns_name = "AUIPlugin", rl_name = "AUIFileDeleteFileEvent", hash_code = -545221029,
name_list = {"target","path"},
type_list = {"ALittle.DisplayObject","string"},
option_map = {}
})

assert(AUIPlugin.AUIFileTreeLayout, " extends class:AUIPlugin.AUIFileTreeLayout is nil")
ALittleIDE.IDEUITileList = Lua.Class(AUIPlugin.AUIFileTreeLayout, "ALittleIDE.IDEUITileList")

function ALittleIDE.IDEUITileList:TCtor()
	ALittleIDE.g_IDEProject:AddEventListener(___all_struct[-975432877], self, self.HandleProjectOpen)
	ALittleIDE.g_IDEProject:AddEventListener(___all_struct[-332308624], self, self.HandleProjectClose)
	self:AddEventListener(___all_struct[2117383637], self, self.HandleSelectFileEvent)
	self:AddEventListener(___all_struct[-545221029], self, self.HandleDeleteFileEvent)
	self:AddEventListener(___all_struct[-2082217254], self, self.HandleCreateFileEvent)
	self:AddEventListener(___all_struct[-1718818319], self, self.HandleDeleteDirEvent)
end

function ALittleIDE.IDEUITileList:HandleSelectFileEvent(event)
	local info = {}
	info.info = event.info
	info.module_name = ALittleIDE.g_IDEProject.project.name
	ALittleIDE.g_IDECenter.center.content_edit:StartEditTileBySelect(info.info.name, info)
end

function ALittleIDE.IDEUITileList:HandleDeleteFileEvent(event)
end

function ALittleIDE.IDEUITileList:HandleCreateFileEvent(event)
end

function ALittleIDE.IDEUITileList:HandleDeleteDirEvent(event)
end

function ALittleIDE.IDEUITileList:OnRightMenu(user_info, menu)
end

function ALittleIDE.IDEUITileList:HandleProjectClose(event)
	self._file_scroll_screen:RemoveAllChild()
end

function ALittleIDE.IDEUITileList:HandleProjectOpen(event)
	local module_path = ALittle.File_BaseFilePath() .. "Module/" .. event.name .. "/Tile"
	self:SetRoot(module_path, Lua.Bind(self.OnRightMenu, self))
end
ALittleIDE.IDEUITileList.HandleProjectOpen = Lua.CoWrap(ALittleIDE.IDEUITileList.HandleProjectOpen)

end