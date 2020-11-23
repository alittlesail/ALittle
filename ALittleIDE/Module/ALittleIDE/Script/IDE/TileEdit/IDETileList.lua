-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-2082217254, "AUIPlugin.AUIFileCreateFileEvent", {
name = "AUIPlugin.AUIFileCreateFileEvent", ns_name = "AUIPlugin", rl_name = "AUIFileCreateFileEvent", hash_code = -2082217254,
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

assert(AUIPlugin.AUIFileTreeLayout, " extends class:AUIPlugin.AUIFileTreeLayout is nil")
ALittleIDE.IDETileList = Lua.Class(AUIPlugin.AUIFileTreeLayout, "ALittleIDE.IDETileList")

function ALittleIDE.IDETileList:TCtor()
	ALittleIDE.g_IDEProject:AddEventListener(___all_struct[-975432877], self, self.HandleProjectOpen)
	ALittleIDE.g_IDEProject:AddEventListener(___all_struct[-332308624], self, self.HandleProjectClose)
	self:AddEventListener(___all_struct[-2082217254], self, self.HandleFileCreateEvent)
end

function ALittleIDE.IDETileList:HandleFileCreateEvent(event)
end

function ALittleIDE.IDETileList:OnRightMenu(user_info, menu)
end

function ALittleIDE.IDETileList:HandleProjectClose(event)
	self._file_scroll_screen:RemoveAllChild()
end

function ALittleIDE.IDETileList:HandleProjectOpen(event)
	local module_path = ALittle.File_BaseFilePath() .. "Module/" .. event.name .. "/Tile"
	self:SetRoot(module_path, Lua.Bind(self.OnRightMenu, self))
end
ALittleIDE.IDETileList.HandleProjectOpen = Lua.CoWrap(ALittleIDE.IDETileList.HandleProjectOpen)

end