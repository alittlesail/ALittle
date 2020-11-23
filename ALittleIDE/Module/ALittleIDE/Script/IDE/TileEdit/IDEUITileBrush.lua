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

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEUITileBrush = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEUITileBrush")

function ALittleIDE.IDEUITileBrush:TCtor()
	ALittleIDE.g_IDEProject:AddEventListener(___all_struct[-975432877], self, self.HandleProjectOpen)
	ALittleIDE.g_IDEProject:AddEventListener(___all_struct[-332308624], self, self.HandleProjectClose)
	self._file_select:Init({"png", "jpg"})
end

function ALittleIDE.IDEUITileBrush:HandleProjectClose(event)
	self._file_select:SetBasePath(nil)
end

function ALittleIDE.IDEUITileBrush:HandleProjectOpen(event)
	local module_path = ALittle.File_BaseFilePath() .. "Module/" .. event.name .. "/Texture"
	self._file_select:SetBasePath(module_path)
end
ALittleIDE.IDEUITileBrush.HandleProjectOpen = Lua.CoWrap(ALittleIDE.IDEUITileBrush.HandleProjectOpen)

end