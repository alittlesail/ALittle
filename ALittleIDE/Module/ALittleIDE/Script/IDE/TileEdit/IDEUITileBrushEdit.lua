-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
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
name_list = {"_image","_item","tex_path"},
type_list = {"ALittle.Image","ALittle.DisplayLayout","string"},
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
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name = "ALittle.UIChangedEvent", ns_name = "ALittle", rl_name = "UIChangedEvent", hash_code = 958494922,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name = "ALittle.UIRButtonDownEvent", ns_name = "ALittle", rl_name = "UIRButtonDownEvent", hash_code = -641444818,
name_list = {"target","abs_x","abs_y","rel_x","rel_y","count","is_drag"},
type_list = {"ALittle.DisplayObject","double","double","double","double","int","bool"},
option_map = {}
})
ALittle.RegStruct(274315553, "ALittleIDE.IDEUITileLayerInfo", {
name = "ALittleIDE.IDEUITileLayerInfo", ns_name = "ALittleIDE", rl_name = "IDEUITileLayerInfo", hash_code = 274315553,
name_list = {"_button","_item","_see_image"},
type_list = {"ALittle.TextRadioButton","ALittle.DisplayLayout","ALittle.Image"},
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
		info._item._user_data = info
		self._brush_list:AddChild(info._item)
	end
end

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEUITileLayerEdit = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEUITileLayerEdit")

function ALittleIDE.IDEUITileLayerEdit:Ctor()
	___rawset(self, "_group", {})
end

function ALittleIDE.IDEUITileLayerEdit:HandleAddLayerClick(event)
	local x, y = event.target:LocalToGlobal()
	local name = g_AUITool:ShowRename("", x, y + event.target.height, 200)
	if name == nil or name == "" then
		return
	end
	local info = {}
	info._item = ALittleIDE.g_Control:CreateControl("ide_tile_layer_item", info)
	info._button.text = name
	info._button.group = self._group
	info._button._user_data = info
	info._button:AddEventListener(___all_struct[-641444818], self, self.HandleRButtonDown)
	info._button:AddEventListener(___all_struct[958494922], self, self.HandleChanged)
	self._layer_list:AddChild(info._item)
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
	info._button.text = name
end
ALittleIDE.IDEUITileLayerEdit.HandleRenameLayer = Lua.CoWrap(ALittleIDE.IDEUITileLayerEdit.HandleRenameLayer)

function ALittleIDE.IDEUITileLayerEdit:HandleDeleteLayer(info)
	if g_AUITool:DeleteNotice("删除", "确定要删除该图层吗?") ~= "YES" then
		return
	end
	self._layer_list:RemoveChild(info._item)
end
ALittleIDE.IDEUITileLayerEdit.HandleDeleteLayer = Lua.CoWrap(ALittleIDE.IDEUITileLayerEdit.HandleDeleteLayer)

function ALittleIDE.IDEUITileLayerEdit:HandleUpLayer(info)
	local index = self._layer_list:GetChildIndex(info._item)
	if index == nil or index == 1 then
		return
	end
	self._layer_list:SetChildIndex(info._item, index - 1)
end

function ALittleIDE.IDEUITileLayerEdit:HandleDownLayer(info)
	local index = self._layer_list:GetChildIndex(info._item)
	if index == nil then
		return
	end
	self._layer_list:SetChildIndex(info._item, index + 1)
end

function ALittleIDE.IDEUITileLayerEdit:HandleChanged(event)
	local info = event.target._user_data
	local index = self._layer_list:GetChildIndex(info._item)
end

function ALittleIDE.IDEUITileLayerEdit:HandleHideLayer(info)
	info._see_image.visible = false
end

function ALittleIDE.IDEUITileLayerEdit:HandleShowLayer(info)
	info._see_image.visible = true
end

end