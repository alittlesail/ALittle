-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.Index == nil then _G.Index = {} end
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1632726113, "Index.ItemInfo", {
name = "Index.ItemInfo", ns_name = "Index", rl_name = "ItemInfo", hash_code = -1632726113,
name_list = {"_image","_title"},
type_list = {"ALittle.Image","ALittle.Text"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(1403787970, "Index.ItemData", {
name = "Index.ItemData", ns_name = "Index", rl_name = "ItemData", hash_code = 1403787970,
name_list = {"title","texture_name","path"},
type_list = {"string","string","string"},
option_map = {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name = "ALittle.UIClickEvent", ns_name = "ALittle", rl_name = "UIClickEvent", hash_code = -449066808,
name_list = {"target","is_drag"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})

Index.g_GConfig = nil
Index.GCenter = Lua.Class(nil, "Index.GCenter")

function Index.GCenter:Ctor()
end

function Index.GCenter:Setup()
	Index.g_GConfig = ALittle.CreateConfigSystem(Index.g_ModuleBasePath .. "/User.cfg")
	ALittle.Math_RandomSeed(ALittle.Time_GetCurTime())
	ALittle.System_SetThreadCount(1)
	self._main_layer = ALittle.DisplayLayout(Index.g_Control)
	self._main_layer.width_type = 4
	self._main_layer.height_type = 4
	Index.g_LayerGroup:AddChild(self._main_layer, nil)
	self._dialog_layer = ALittle.DisplayLayout(Index.g_Control)
	self._dialog_layer.width_type = 4
	self._dialog_layer.height_type = 4
	Index.g_LayerGroup:AddChild(self._dialog_layer, nil)
	local main_scene = Index.g_Control:CreateControl("main_scene", self, self._main_layer)
	self._item_tiletable = ALittle.Cast(ALittle.TileTable, ALittle.DisplayGroup, self._item_container.container)
	local data_list = {}
	do
		local data = {}
		data.title = "BattleCity"
		data.texture_name = "BattleCity.png"
		data.path = "BattleCity.html"
		ALittle.List_Push(data_list, data)
		data = {}
		data.title = "SuperMarioBros"
		data.texture_name = "SuperMarioBros.png"
		data.path = "SuperMarioBros.html"
		ALittle.List_Push(data_list, data)
		data = {}
		data.title = "ALittleIDE"
		data.texture_name = "ALittleIDE.png"
		data.path = "ALittleIDE.html"
		ALittle.List_Push(data_list, data)
		data = {}
		data.title = "2048"
		data.texture_name = "G2048.png"
		data.path = "G2048.html"
		ALittle.List_Push(data_list, data)
		data = {}
		data.title = "FlappyBird"
		data.texture_name = "FlappyBird.png"
		data.path = "FlappyBird.html"
		ALittle.List_Push(data_list, data)
		data = {}
		data.title = "NES Emulator"
		data.texture_name = "NESEmulator.png"
		data.path = "NESEmulator.html"
		ALittle.List_Push(data_list, data)
	end
	self._item_width = 0
	for index, data in ___ipairs(data_list) do
		local info = {}
		local item = Index.g_Control:CreateControl("sample_item", info)
		self._item_tiletable:AddChild(item)
		info._image.texture_name = data.texture_name
		info._title.text = data.title
		info._image._user_data = data
		info._image:AddEventListener(___all_struct[-449066808], self, self.HandleImageClick)
		self._item_width = item.width
	end
	if self._item_width > 0 and self._item_tiletable ~= nil then
		self._item_tiletable.col_count = ALittle.Math_Floor(self._item_container.width / self._item_width)
	end
	self._item_container:AdjustScrollBar()
	A_UISystem.view_resize_callback = Lua.Bind(self.HandleViewResized, self)
end

function Index.GCenter:HandleViewResized(width, height)
	if self._item_width > 0 and self._item_tiletable ~= nil then
		self._item_tiletable.col_count = ALittle.Math_Floor(self._item_container.width / self._item_width)
	end
	self._item_container:AdjustScrollBar()
end

function Index.GCenter:HandleImageClick(event)
	local data = event.target._user_data
	local fixed_host = "139.159.176.119"
	local base_url = "http://" .. fixed_host .. "/"
	ALittle.System_OpenUrlBySystemBrowser(base_url .. data.path)
end

function Index.GCenter:HandleGithubClick(event)
	local url = "https://github.com/alittlesail/ALittle.git"
	ALittle.System_OpenUrlBySystemBrowser(url)
end

function Index.GCenter:Shutdown()
end

_G.g_GCenter = Index.GCenter()
end