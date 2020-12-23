-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
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
name_list = {"info","module_name","tile_map","tex_id_map","tex_id_max"},
type_list = {"AUIPlugin.AUIFileTreeUserInfo","string","ALittle.TileMap","Map<string,int>","int"},
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
ALittle.RegStruct(-1281734132, "ALittle.TileMap", {
name = "ALittle.TileMap", ns_name = "ALittle", rl_name = "TileMap", hash_code = -1281734132,
name_list = {"tile_type","side_len","tile_width","tile_height","tile_x","tile_y","col_count","row_count","tex_map","layer_list"},
type_list = {"int","int","int","int","int","int","int","int","Map<int,string>","List<ALittle.TileLayer>"},
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
ALittle.RegStruct(-343663763, "ALittle.TileLayer", {
name = "ALittle.TileLayer", ns_name = "ALittle", rl_name = "TileLayer", hash_code = -343663763,
name_list = {"name","cell_map"},
type_list = {"string","Map<int,Map<int,ALittle.TileCell>>"},
option_map = {}
})
ALittle.RegStruct(7944876, "ALittle.TileCell", {
name = "ALittle.TileCell", ns_name = "ALittle", rl_name = "TileCell", hash_code = 7944876,
name_list = {"tex_id"},
type_list = {"int"},
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
	local ui = ALittleIDE.g_IDEProject.project.ui[ALittleIDE.g_IDEProject.project.name]
	if ui == nil then
		g_AUITool:ShowNotice("提示", "ui不存在")
		return
	end
	local tile_map = ui.control:LoadMessageFromFile(___all_struct[-1281734132], event.info.path)
	if tile_map == nil then
		g_AUITool:ShowNotice("提示", "地图文件读取失败")
		return
	end
	if tile_map.tile_type == 0 or tile_map.side_len <= 0 then
		ALittleIDE.g_IDETileSettingDialog:ShowDialog(tile_map)
		if tile_map.tile_type == 0 or tile_map.side_len <= 0 then
			g_AUITool:ShowNotice("提示", "请设置有效的格子类型和格子边长不能小于或等于0")
			return
		end
		ui.control:WriteMessageToFile(___all_struct[-1281734132], tile_map, event.info.path)
	end
	local info = {}
	info.info = event.info
	info.module_name = ALittleIDE.g_IDEProject.project.name
	info.tile_map = tile_map
	ALittleIDE.g_IDECenter.center.content_edit:StartEditTileBySelect(info.info.name, info)
end
ALittleIDE.IDEUITileList.HandleSelectFileEvent = Lua.CoWrap(ALittleIDE.IDEUITileList.HandleSelectFileEvent)

function ALittleIDE.IDEUITileList:HandleDeleteFileEvent(event)
	local tab_child = ALittleIDE.g_IDECenter.center.content_edit:GetTabChildById(ALittleIDE.IDETileTabChild, event.path)
	if tab_child == nil then
		return
	end
	ALittleIDE.g_IDECenter.center.content_edit:CloseTab(tab_child.tab_body)
end

function ALittleIDE.IDEUITileList:HandleCreateFileEvent(event)
end

function ALittleIDE.IDEUITileList:HandleDeleteDirEvent(event)
	local map = ALittleIDE.g_IDECenter.center.content_edit:GetTabIdMap(ALittleIDE.IDETileTabChild)
	for id, tab_child in ___pairs(map) do
		if ALittle.String_Find(id, event.path) == 1 then
			ALittleIDE.g_IDECenter.center.content_edit:CloseTab(tab_child.tab_body)
		end
	end
end

function ALittleIDE.IDEUITileList:OnRightMenu(user_info, menu)
	menu:AddItem("设置", Lua.Bind(self.ShowSetting, self, user_info))
end

function ALittleIDE.IDEUITileList:HandleProjectClose(event)
	self._file_scroll_screen:RemoveAllChild()
end

function ALittleIDE.IDEUITileList:HandleProjectOpen(event)
	local module_path = ALittle.File_BaseFilePath() .. "Module/" .. event.name .. "/Tile"
	self:SetRoot(module_path, Lua.Bind(self.OnRightMenu, self))
end
ALittleIDE.IDEUITileList.HandleProjectOpen = Lua.CoWrap(ALittleIDE.IDEUITileList.HandleProjectOpen)

function ALittleIDE.IDEUITileList:ShowSetting(user_info)
	local tab_child = ALittleIDE.g_IDECenter.center.content_edit:GetTabChildById(ALittleIDE.IDETileTabChild, user_info.path)
	if tab_child ~= nil then
		g_AUITool:ShowNotice("提示", "请先关闭编辑页面再设置")
		return
	end
	local ui = ALittleIDE.g_IDEProject.project.ui[ALittleIDE.g_IDEProject.project.name]
	if ui == nil then
		g_AUITool:ShowNotice("提示", "ui不存在")
		return
	end
	local tile_map = ui.control:LoadMessageFromFile(___all_struct[-1281734132], user_info.path)
	if tile_map == nil then
		g_AUITool:ShowNotice("提示", "地图文件读取失败")
		return
	end
	if not ALittleIDE.g_IDETileSettingDialog:ShowDialog(tile_map) then
		return
	end
	local error = ui.control:WriteMessageToFile(___all_struct[-1281734132], tile_map, user_info.path)
	if error ~= nil then
		g_AUITool:ShowNotice("提示", "保存失败:" .. error)
		return
	end
end
ALittleIDE.IDEUITileList.ShowSetting = Lua.CoWrap(ALittleIDE.IDEUITileList.ShowSetting)

end