-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.RevokeObject, " extends class:ALittle.RevokeObject is nil")
ALittleIDE.IDETileAddLayerRevoke = Lua.Class(ALittle.RevokeObject, "ALittleIDE.IDETileAddLayerRevoke")

function ALittleIDE.IDETileAddLayerRevoke:Ctor(tab_child, layer_info)
	___rawset(self, "_tab_child", tab_child)
	___rawset(self, "_layer_info", layer_info)
end

function ALittleIDE.IDETileAddLayerRevoke:Forward()
	self._tab_child.layer_edit.layer_list:AddChild(self._layer_info._item)
	ALittle.List_Push(self._layer_info._user_info.tile_map.layer_list, self._layer_info._layer)
end

function ALittleIDE.IDETileAddLayerRevoke:Back()
	self._tab_child.layer_edit.layer_list:RemoveChild(self._layer_info._item)
	local index = ALittle.List_IndexOf(self._layer_info._user_info.tile_map.layer_list, self._layer_info._layer)
	ALittle.List_Remove(self._layer_info._user_info.tile_map.layer_list, index)
end

assert(ALittle.RevokeObject, " extends class:ALittle.RevokeObject is nil")
ALittleIDE.IDETileDeleteLayerRevoke = Lua.Class(ALittle.RevokeObject, "ALittleIDE.IDETileDeleteLayerRevoke")

function ALittleIDE.IDETileDeleteLayerRevoke:Ctor(tab_child, layer_info, index)
	___rawset(self, "_tab_child", tab_child)
	___rawset(self, "_layer_info", layer_info)
	___rawset(self, "_index", index)
end

function ALittleIDE.IDETileDeleteLayerRevoke:Forward()
	self._tab_child.layer_edit.layer_list:RemoveChild(self._layer_info._item)
	local index = ALittle.List_IndexOf(self._layer_info._user_info.tile_map.layer_list, self._layer_info._layer)
	ALittle.List_Remove(self._layer_info._user_info.tile_map.layer_list, index)
	self._tab_child:RemoveLayer(self._layer_info._linear_1, self._layer_info._linear_2)
end

function ALittleIDE.IDETileDeleteLayerRevoke:Back()
	self._tab_child.layer_edit.layer_list:AddChild(self._layer_info._item, self._index)
	ALittle.List_Insert(self._layer_info._user_info.tile_map.layer_list, self._index, self._layer_info._layer)
	self._tab_child:AddLayer(self._layer_info._linear_1, self._layer_info._linear_2, self._index)
end

assert(ALittle.RevokeObject, " extends class:ALittle.RevokeObject is nil")
ALittleIDE.IDETileSetLayerIndexRevoke = Lua.Class(ALittle.RevokeObject, "ALittleIDE.IDETileSetLayerIndexRevoke")

function ALittleIDE.IDETileSetLayerIndexRevoke:Ctor(tab_child, layer_info, old_index, new_index)
	___rawset(self, "_tab_child", tab_child)
	___rawset(self, "_layer_info", layer_info)
	___rawset(self, "_old_index", old_index)
	___rawset(self, "_new_index", new_index)
end

function ALittleIDE.IDETileSetLayerIndexRevoke:Forward()
	self._tab_child.layer_edit.layer_list:SetChildIndex(self._layer_info._item, self._new_index)
	ALittle.List_Remove(self._layer_info._user_info.tile_map.layer_list, self._old_index)
	ALittle.List_Insert(self._layer_info._user_info.tile_map.layer_list, self._new_index, self._layer_info._layer)
	self._tab_child:SetLayerIndex(self._layer_info._linear_1, self._layer_info._linear_2, self._new_index)
end

function ALittleIDE.IDETileSetLayerIndexRevoke:Back()
	self._tab_child.layer_edit.layer_list:SetChildIndex(self._layer_info._item, self._old_index)
	ALittle.List_Remove(self._layer_info._user_info.tile_map.layer_list, self._new_index)
	ALittle.List_Insert(self._layer_info._user_info.tile_map.layer_list, self._old_index, self._layer_info._layer)
	self._tab_child:SetLayerIndex(self._layer_info._linear_1, self._layer_info._linear_2, self._old_index)
end

assert(ALittle.RevokeObject, " extends class:ALittle.RevokeObject is nil")
ALittleIDE.IDETileRenameLayerRevoke = Lua.Class(ALittle.RevokeObject, "ALittleIDE.IDETileRenameLayerRevoke")

function ALittleIDE.IDETileRenameLayerRevoke:Ctor(tab_child, layer_info, old_name, new_name)
	___rawset(self, "_tab_child", tab_child)
	___rawset(self, "_layer_info", layer_info)
	___rawset(self, "_old_name", old_name)
	___rawset(self, "_new_name", new_name)
end

function ALittleIDE.IDETileRenameLayerRevoke:Forward()
	self._layer_info._button.text = self._new_name
	self._layer_info._layer.name = self._new_name
end

function ALittleIDE.IDETileRenameLayerRevoke:Back()
	self._layer_info._button.text = self._old_name
	self._layer_info._layer.name = self._old_name
end

end