-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1450277461, "ALittleIDE.IDECodeModuleInfo", {
name = "ALittleIDE.IDECodeModuleInfo", ns_name = "ALittleIDE", rl_name = "IDECodeModuleInfo", hash_code = 1450277461,
name_list = {"module_name","root_path"},
type_list = {"string","string"},
option_map = {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
IDEUICodeList = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEUICodeList")

function IDEUICodeList:Ctor(ctrl_sys)
	___rawset(self, "_group", {})
end

function IDEUICodeList:TCtor()
	g_IDEProject:AddEventListener(___all_struct[-975432877], self, self.HandleProjectOpen)
	g_IDEProject:AddEventListener(___all_struct[-332308624], self, self.HandleProjectClose)
end

function IDEUICodeList:HandleProjectClose(event)
	self._code_scroll_screen:RemoveAllChild()
end

function IDEUICodeList:HandleProjectOpen(event)
	local module_map = g_IDEConfig:GetConfig("code_module", {})
	module_map["Core"] = nil
	module_map["Std"] = nil
	module_map["CEngine"] = nil
	module_map[event.name] = nil
	local info = {}
	info.module_name = event.name
	info.name = "src"
	info.path = ALittle.File_BaseFilePath() .. "Module/" .. event.name .. "/src"
	info.group = self._group
	info.root = true
	self._code_scroll_screen:AddChild(IDECodeTree(g_Control, info))
	local std_list = {"Core", "Std", "CEngine"}
	for index, name in ___ipairs(std_list) do
		info = {}
		info.module_name = name
		info.name = "src"
		info.path = ALittle.File_BaseFilePath() .. "Module/ALittleIDE/Other/GameLibrary/" .. name .. "/src"
		info.group = self._group
		info.root = true
		self._code_scroll_screen:AddChild(IDECodeTree(g_Control, info))
	end
	for index, module in ___pairs(module_map) do
		info = {}
		info.module_name = module.module_name
		info.name = ALittle.File_GetFileNameByPath(module.root_path)
		info.path = module.root_path
		info.group = self._group
		local tree = IDECodeTree(g_Control, info)
		self._code_scroll_screen:AddChild(tree)
	end
end

function IDEUICodeList:HandleCodeSearchClick(event)
end

