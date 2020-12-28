-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})
ALittle.RegStruct(1575666720, "ALittleIDE.IDEUITileBrushInfo", {
name = "ALittleIDE.IDEUITileBrushInfo", ns_name = "ALittleIDE", rl_name = "IDEUITileBrushInfo", hash_code = 1575666720,
name_list = {"_image","_item","tex_path","module_path"},
type_list = {"ALittle.Image","ALittle.DisplayLayout","string","string"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name = "ALittle.UIButtonEvent", ns_name = "ALittle", rl_name = "UIButtonEvent", hash_code = -1347278145,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
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
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name = "ALittle.UIRButtonDownEvent", ns_name = "ALittle", rl_name = "UIRButtonDownEvent", hash_code = -641444818,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(-343663763, "ALittle.TileLayer", {
name = "ALittle.TileLayer", ns_name = "ALittle", rl_name = "TileLayer", hash_code = -343663763,
name_list = {"name","cell_map"},
type_list = {"string","Map<int,Map<int,ALittle.TileCell>>"},
option_map = {}
})
ALittle.RegStruct(274315553, "ALittleIDE.IDEUITileLayerInfo", {
name = "ALittleIDE.IDEUITileLayerInfo", ns_name = "ALittleIDE", rl_name = "IDEUITileLayerInfo", hash_code = 274315553,
name_list = {"_button","_item","_see_image","_layer","_user_info","_group","_linear_1","_linear_2"},
type_list = {"ALittle.TextRadioButton","ALittle.DisplayLayout","ALittle.Image","ALittle.TileLayer","ALittleIDE.IDETileTreeUserInfo","ALittle.DisplayGroup","ALittle.Linear","ALittle.Linear"},
option_map = {}
})
ALittle.RegStruct(7944876, "ALittle.TileCell", {
name = "ALittle.TileCell", ns_name = "ALittle", rl_name = "TileCell", hash_code = 7944876,
name_list = {"tex_id"},
type_list = {"int"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEUITileBrushEdit = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEUITileBrushEdit")

function ALittleIDE.IDEUITileBrushEdit:TCtor()
	ALittleIDE.g_IDEProject:AddEventListener(___all_struct[-975432877], self, self.HandleProjectOpen)
	ALittleIDE.g_IDEProject:AddEventListener(___all_struct[-332308624], self, self.HandleProjectClose)
end

function ALittleIDE.IDEUITileBrushEdit.__getter:layer_container()
	return self._layer_container
end

function ALittleIDE.IDEUITileBrushEdit:HandleClearBrushClick(event)
	self._brush_list:RemoveAllChild()
end

function ALittleIDE.IDEUITileBrushEdit:HandleProjectOpen(event)
	self._brush_list:RemoveAllChild()
end

function ALittleIDE.IDEUITileBrushEdit:HandleProjectClose(event)
	self._brush_list:RemoveAllChild()
end

function ALittleIDE.IDEUITileBrushEdit:AddBrushList(module_path_list, tex_path_list, ctrl)
	if not ctrl then
		self._brush_list:RemoveAllChild()
	end
	for index, module_path in ___ipairs(module_path_list) do
		local tex_path = tex_path_list[index]
		local info = {}
		info._item = ALittleIDE.g_Control:CreateControl("ide_tile_brush_item", info)
		info._image:SetTextureCut(module_path, 0, 0, true)
		info.tex_path = tex_path
		info.module_path = module_path
		info._item._user_data = info
		self._brush_list:AddChild(info._item)
	end
end

function ALittleIDE.IDEUITileBrushEdit:GetBrush()
	local child_count = self._brush_list.child_count
	if child_count == 0 then
		return nil
	end
	if child_count == 1 then
		return self._brush_list.childs[1]._user_data
	end
	local index = ALittle.Math_RandomInt(1, child_count)
	return self._brush_list.childs[index]._user_data
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEUITileLayerEdit = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEUITileLayerEdit")

function ALittleIDE.IDEUITileLayerEdit:Ctor()
	___rawset(self, "_group", {})
end

function ALittleIDE.IDEUITileLayerEdit:Init(tab_child, user_info)
	self._tab_child = tab_child
	self._user_info = user_info
	for index, layer in ___ipairs(user_info.tile_map.layer_list) do
		local info = {}
		info._user_info = self._user_info
		info._item = ALittleIDE.g_Control:CreateControl("ide_tile_layer_item", info)
		info._button.text = layer.name
		info._button.group = self._group
		info._button._user_data = info
		info._button:AddEventListener(___all_struct[-641444818], self, self.HandleRButtonDown)
		info._item._user_data = info
		self._layer_list:AddChild(info._item)
		info._layer = layer
		info._group, info._linear_1, info._linear_2 = self._tab_child:GetLayer(index)
	end
	if self._layer_list.child_count > 0 then
		local info = self._layer_list.childs[self._layer_list.child_count]._user_data
		info._button.selected = true
	end
end

function ALittleIDE.IDEUITileLayerEdit.__getter:layer_list()
	return self._layer_list
end

function ALittleIDE.IDEUITileLayerEdit:GetCurLayerInfo()
	for index, child in ___ipairs(self._layer_list.childs) do
		local info = child._user_data
		if info._button.selected then
			return info, index
		end
	end
	return nil, nil
end

function ALittleIDE.IDEUITileLayerEdit:HandleAddLayerClick(event)
	local x, y = event.target:LocalToGlobal()
	local name = g_AUITool:ShowRename("", x, y + event.target.height, 200)
	if name == nil or name == "" then
		return
	end
	local info = {}
	info._user_info = self._user_info
	info._item = ALittleIDE.g_Control:CreateControl("ide_tile_layer_item", info)
	info._button.text = name
	info._button.group = self._group
	info._button._user_data = info
	info._button:AddEventListener(___all_struct[-641444818], self, self.HandleRButtonDown)
	info._item._user_data = info
	self._layer_list:AddChild(info._item)
	if self._layer_list.child_count == 1 then
		info._button.selected = true
	end
	info._layer = {}
	info._layer.name = name
	info._layer.cell_map = {}
	ALittle.List_Push(self._user_info.tile_map.layer_list, info._layer)
	info._group, info._linear_1, info._linear_2 = self._tab_child:CreateLayer()
	local revoke = ALittleIDE.IDETileAddLayerRevoke(self._tab_child, info)
	self._tab_child.revoke_list:PushRevoke(revoke)
	self._tab_child.save = false
end
ALittleIDE.IDEUITileLayerEdit.HandleAddLayerClick = Lua.CoWrap(ALittleIDE.IDEUITileLayerEdit.HandleAddLayerClick)

function ALittleIDE.IDEUITileLayerEdit:HandleRButtonDown(event)
	local info = event.target._user_data
	local menu = AUIPlugin.AUIRightMenu()
	menu:AddItem("重命名", Lua.Bind(self.HandleRenameLayer, self, info))
	menu:AddItem("删除", Lua.Bind(self.HandleDeleteLayer, self, info))
	menu:AddItem("上移", Lua.Bind(self.HandleUpLayer, self, info))
	menu:AddItem("下移", Lua.Bind(self.HandleDownLayer, self, info))
	if info._see_image.visible then
		menu:AddItem("隐藏", Lua.Bind(self.HandleHideLayer, self, info))
	else
		menu:AddItem("显示", Lua.Bind(self.HandleShowLayer, self, info))
	end
	menu:Show()
end

function ALittleIDE.IDEUITileLayerEdit:HandleRenameLayer(info)
	local x, y = info._button:LocalToGlobal()
	local name = g_AUITool:ShowRename(info._button.text, x, y + info._button.height, 200)
	if name == nil or name == "" then
		return
	end
	local old_name = info._layer.name
	info._button.text = name
	info._layer.name = name
	local revoke = ALittleIDE.IDETileRenameLayerRevoke(self._tab_child, info, old_name, name)
	self._tab_child.revoke_list:PushRevoke(revoke)
	self._tab_child.save = false
end
ALittleIDE.IDEUITileLayerEdit.HandleRenameLayer = Lua.CoWrap(ALittleIDE.IDEUITileLayerEdit.HandleRenameLayer)

function ALittleIDE.IDEUITileLayerEdit:HandleDeleteLayer(info)
	if g_AUITool:DeleteNotice("删除", "确定要删除该图层吗?") ~= "YES" then
		return
	end
	local index = self._layer_list:GetChildIndex(info._item)
	self._layer_list:RemoveChild(info._item)
	if info._button.selected and self._layer_list.child_count > 0 then
		self._layer_list.childs[1]._user_data._button.selected = true
	end
	ALittle.List_Remove(info._user_info.tile_map.layer_list, index)
	self._tab_child:RemoveLayer(info._group)
	local revoke = ALittleIDE.IDETileDeleteLayerRevoke(self._tab_child, info, index)
	self._tab_child.revoke_list:PushRevoke(revoke)
	self._tab_child.save = false
end
ALittleIDE.IDEUITileLayerEdit.HandleDeleteLayer = Lua.CoWrap(ALittleIDE.IDEUITileLayerEdit.HandleDeleteLayer)

function ALittleIDE.IDEUITileLayerEdit:HandleUpLayer(info)
	local index = self._layer_list:GetChildIndex(info._item)
	if index == nil or index == 1 then
		return
	end
	self._layer_list:SetChildIndex(info._item, index - 1)
	ALittle.List_Remove(info._user_info.tile_map.layer_list, index)
	ALittle.List_Insert(info._user_info.tile_map.layer_list, index - 1, info._layer)
	self._tab_child:SetLayerIndex(info._group, index)
	local revoke = ALittleIDE.IDETileSetLayerIndexRevoke(self._tab_child, info, index, index - 1)
	self._tab_child.revoke_list:PushRevoke(revoke)
	self._tab_child.save = false
end

function ALittleIDE.IDEUITileLayerEdit:HandleDownLayer(info)
	local index = self._layer_list:GetChildIndex(info._item)
	if index == nil or index == self._layer_list.child_count then
		return
	end
	self._layer_list:SetChildIndex(info._item, index + 1)
	ALittle.List_Remove(info._user_info.tile_map.layer_list, index)
	ALittle.List_Insert(info._user_info.tile_map.layer_list, index + 1, info._layer)
	self._tab_child:SetLayerIndex(info._group, index + 1)
	local revoke = ALittleIDE.IDETileSetLayerIndexRevoke(self._tab_child, info, index, index + 1)
	self._tab_child.revoke_list:PushRevoke(revoke)
	self._tab_child.save = false
end

function ALittleIDE.IDEUITileLayerEdit:HandleHideLayer(info)
	info._see_image.visible = false
	info._linear_1.visible = false
	info._linear_2.visible = false
end

function ALittleIDE.IDEUITileLayerEdit:HandleShowLayer(info)
	info._see_image.visible = true
	info._linear_1.visible = true
	info._linear_2.visible = true
end

end