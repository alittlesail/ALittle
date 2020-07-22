-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

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
ALittle.RegStruct(1450277461, "ALittleIDE.IDECodeModuleInfo", {
name = "ALittleIDE.IDECodeModuleInfo", ns_name = "ALittleIDE", rl_name = "IDECodeModuleInfo", hash_code = 1450277461,
name_list = {"module_name","root_path"},
type_list = {"string","string"},
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
	local module_map = g_IDEProject.project.config:GetConfig("code_module", {})
	module_map["Core"] = nil
	module_map["Std"] = nil
	module_map["CEngine"] = nil
	module_map[event.name] = nil
	local info = {}
	info.module_name = event.name
	info.name = "src"
	info.path = ALittle.File_BaseFilePath() .. "Module/" .. event.name .. "/src"
	info.module_path = ALittle.File_BaseFilePath() .. "Module/" .. event.name .. "/"
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
		info.module_path = ALittle.File_BaseFilePath() .. "Module/ALittleIDE/Other/GameLibrary/" .. name .. "/"
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
		info.module_path = ALittle.File_GetFilePathByPath(module.root_path) .. "/"
		info.group = self._group
		info.project = g_IDEProject.project.code
		info.root = true
		local tree = IDECodeTree(g_Control, info)
		self._code_scroll_screen:AddChild(tree)
	end
end

function IDEUICodeList:AddLibrary(name)
	local file_map = ALittle.File_GetFileNameListByDir(ALittle.File_BaseFilePath() .. "Module/ALittleIDE/Other/GameLibrary")
	local attr = file_map[name]
	if attr == nil or attr.mode ~= "directory" then
		return false
	end
	local module_map = g_IDEProject.project.config:GetConfig("code_module", {})
	local module_info = {}
	module_info.module_name = name
	module_info.root_path = ALittle.File_BaseFilePath() .. "Module/ALittleIDE/Other/GameLibrary/" .. name .. "/src"
	module_map[name] = module_info
	g_IDEProject.project.config:SetConfig("code_module", module_map)
	local info = {}
	info.module_name = name
	info.name = "src"
	info.path = ALittle.File_BaseFilePath() .. "Module/ALittleIDE/Other/GameLibrary/" .. name .. "/src"
	info.module_path = ALittle.File_BaseFilePath() .. "Module/ALittleIDE/Other/GameLibrary/" .. name .. "/"
	info.group = self._group
	info.root = true
	info.project = g_IDEProject.project.code
	local tree = IDECodeTree(g_Control, info)
	self._code_scroll_screen:AddChild(tree)
	return true
end

function IDEUICodeList:OpenByFullPath(full_path, line_start, char_start, line_end, char_end)
	for index, child in ___ipairs(self._code_scroll_screen.childs) do
		local item = child:FindFile(full_path)
		if item ~= nil then
			local code_child = g_IDECenter.center.content_edit:StartEditCodeBySelect(item.user_info.name, item.user_info)
			code_child:JumpFocus(line_start, char_start, line_end, char_end)
			return
		end
	end
	if ALittle.File_GetFileAttr(full_path) == nil then
		return
	end
	local user_info = {}
	user_info.name = ALittle.File_GetFileNameByPath(full_path)
	user_info.path = full_path
	g_IDECenter.center.content_edit:StartEditCodeBySelect(user_info.name, user_info)
end

function IDEUICodeList:AddModule(name)
	for index, tree in ___ipairs(self._code_scroll_screen.childs) do
		if tree.user_info.module_name == name then
			return
		end
	end
	local module_map = g_IDEProject.project.config:GetConfig("code_module", {})
	local module_info = {}
	module_info.module_name = name
	module_info.root_path = ALittle.File_BaseFilePath() .. "Module/" .. name .. "/src"
	module_map[name] = module_info
	g_IDEProject.project.config:SetConfig("code_module", module_map)
	local info = {}
	info.module_name = name
	info.name = ALittle.File_GetFileNameByPath(module_info.root_path)
	info.path = module_info.root_path
	info.module_path = ALittle.File_BaseFilePath() .. "Module/" .. name .. "/"
	info.group = self._group
	info.root = true
	info.project = g_IDEProject.project.code
	local tree = IDECodeTree(g_Control, info)
	self._code_scroll_screen:AddChild(tree)
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

