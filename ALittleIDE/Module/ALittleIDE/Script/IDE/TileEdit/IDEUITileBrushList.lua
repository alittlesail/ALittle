-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

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
ALittle.RegStruct(1206110359, "AUIPlugin.AUIFileSelectFileClickUIEvent", {
name = "AUIPlugin.AUIFileSelectFileClickUIEvent", ns_name = "AUIPlugin", rl_name = "AUIFileSelectFileClickUIEvent", hash_code = 1206110359,
name_list = {"target","path","ctrl"},
type_list = {"ALittle.DisplayObject","string","bool"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEUITileBrushList = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEUITileBrushList")

function ALittleIDE.IDEUITileBrushList:TCtor()
	ALittleIDE.g_IDEProject:AddEventListener(___all_struct[-975432877], self, self.HandleProjectOpen)
	ALittleIDE.g_IDEProject:AddEventListener(___all_struct[-332308624], self, self.HandleProjectClose)
	self._file_select:Init({"png", "jpg"})
	self._file_select:AddEventListener(___all_struct[1206110359], self, self.HandleImageSelect)
end

function ALittleIDE.IDEUITileBrushList:HandleProjectClose(event)
	self._file_select:SetBasePath(nil)
end

function ALittleIDE.IDEUITileBrushList:HandleProjectOpen(event)
	local module_path = ALittle.File_BaseFilePath() .. "Module/" .. event.name .. "/Texture"
	self._file_select:SetBasePath(module_path)
end
ALittleIDE.IDEUITileBrushList.HandleProjectOpen = Lua.CoWrap(ALittleIDE.IDEUITileBrushList.HandleProjectOpen)

function ALittleIDE.IDEUITileBrushList:HandleImageSelect(event)
	ALittleIDE.g_IDECenter.center.tile_brush_edit:AddBrush(self._file_select.base_path, event.path, event.ctrl)
end

end