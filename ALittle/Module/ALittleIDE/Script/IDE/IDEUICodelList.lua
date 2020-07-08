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
ALittle.RegStruct(-889634858, "ALittleIDE.IDECodeFileSearchInfo", {
name = "ALittleIDE.IDECodeFileSearchInfo", ns_name = "ALittleIDE", rl_name = "IDECodeFileSearchInfo", hash_code = -889634858,
name_list = {"list","count","index","name"},
type_list = {"List<ALittleIDE.IDECodeTreeLogic>","int","int","string"},
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
	info.project = g_IDEProject.project.code
	self._code_scroll_screen:AddChild(IDECodeTree(g_Control, info))
	local std_list = {"Core", "Std", "CEngine"}
	for index, name in ___ipairs(std_list) do
		info = {}
		info.module_name = name
		info.name = "src"
		info.path = ALittle.File_BaseFilePath() .. "Module/ALittleIDE/Other/GameLibrary/" .. name .. "/src"
		info.group = self._group
		info.root = true
		info.project = g_IDEProject.project.code
		local tree = IDECodeTree(g_Control, info)
		self._code_scroll_screen:AddChild(tree)
	end
	for index, module in ___pairs(module_map) do
		info = {}
		info.module_name = module.module_name
		info.name = ALittle.File_GetFileNameByPath(module.root_path)
		info.path = module.root_path
		info.group = self._group
		info.project = g_IDEProject.project.code
		local tree = IDECodeTree(g_Control, info)
		self._code_scroll_screen:AddChild(tree)
	end
end

function IDEUICodeList:ShowTreeItemFocus(target)
	target:ShowSelect()
	if target ~= self._code_scroll_screen then
		local parent = target.logic_parent
		while parent ~= nil and parent ~= self._code_scroll_screen do
			parent.fold = true
			parent = parent.logic_parent
		end
	end
	self._code_scroll_screen:RejustScrollBar()
	local x, y = target:LocalToGlobal(self._code_scroll_screen.container)
	local target_x = (self._code_scroll_screen.view_width - target.width / 2) / 2 - x
	local target_y = (self._code_scroll_screen.view_height - target.height) / 2 - y
	if self._tree_loop_x ~= nil then
		self._tree_loop_x:Stop()
		self._tree_loop_x = nil
	end
	if self._tree_loop_y ~= nil then
		self._tree_loop_y:Stop()
		self._tree_loop_y = nil
	end
	self._tree_loop_x = ALittle.LoopLinear(self._code_scroll_screen, "container_x", target_x, 300, 0)
	self._tree_loop_x:Start()
	self._tree_loop_y = ALittle.LoopLinear(self._code_scroll_screen, "container_y", target_y, 300, 0)
	self._tree_loop_y:Start()
end

function IDEUICodeList:HandleCodeSearchClick(event)
	if self._search_info == nil or self._search_info.name ~= self._code_search_key.text then
		self._search_info = {}
		self._search_info.name = self._code_search_key.text
		self._search_info.index = 0
		self._search_info.list = {}
		for index, child in ___ipairs(self._code_scroll_screen.childs) do
			child:SearchFile(self._search_info.name, self._search_info.list)
		end
		self._search_info.count = ALittle.List_MaxN(self._search_info.list)
	end
	if self._search_info.count <= 0 then
		return
	end
	self._search_info.index = self._search_info.index + (1)
	if self._search_info.index > self._search_info.count then
		self._search_info.index = 1
	end
	local item = self._search_info.list[self._search_info.index]
	self:ShowTreeItemFocus(item)
end

