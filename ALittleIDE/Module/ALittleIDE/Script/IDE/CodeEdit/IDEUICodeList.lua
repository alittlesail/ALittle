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
ALittle.RegStruct(-1701308094, "ALittleIDE.IDECodeJumpInfo", {
name = "ALittleIDE.IDECodeJumpInfo", ns_name = "ALittleIDE", rl_name = "IDECodeJumpInfo", hash_code = -1701308094,
name_list = {"file_path","it_line","it_char"},
type_list = {"string","int","int"},
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
ALittleIDE.IDEUICodeList = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEUICodeList")

function ALittleIDE.IDEUICodeList:Ctor(ctrl_sys)
	___rawset(self, "_jump_list", {})
	___rawset(self, "_jump_count", 0)
	___rawset(self, "_jump_index", 0)
	___rawset(self, "_group", {})
end

function ALittleIDE.IDEUICodeList:TCtor()
	ALittleIDE.g_IDEProject:AddEventListener(___all_struct[-975432877], self, self.HandleProjectOpen)
	ALittleIDE.g_IDEProject:AddEventListener(___all_struct[-332308624], self, self.HandleProjectClose)
end

function ALittleIDE.IDEUICodeList:AddCodeJump(info)
	if self._jump_count > 0 and self._jump_index < self._jump_count then
		ALittle.List_Splice(self._jump_list, self._jump_index + 1, self._jump_count - self._jump_index)
		self._jump_count = self._jump_index
	end
	self._jump_count = self._jump_count + (1)
	self._jump_index = self._jump_count
	self._jump_list[self._jump_count] = info
end

function ALittleIDE.IDEUICodeList:JumpPreCode()
	if self._jump_count == 0 then
		return nil
	end
	if self._jump_index <= 1 then
		return nil
	end
	self._jump_index = self._jump_index - (1)
	return self._jump_list[self._jump_index]
end

function ALittleIDE.IDEUICodeList:JumpNextCode()
	if self._jump_count == 0 then
		return nil
	end
	if self._jump_index >= self._jump_count then
		return nil
	end
	self._jump_index = self._jump_index + (1)
	return self._jump_list[self._jump_index]
end

function ALittleIDE.IDEUICodeList:HandleProjectClose(event)
	self._code_scroll_screen:RemoveAllChild()
	self._jump_count = 0
	self._jump_index = 0
	self._jump_list = {}
end

function ALittleIDE.IDEUICodeList:HandleProjectOpen(event)
	self._jump_count = 0
	self._jump_index = 0
	self._jump_list = {}
	local module_map = ALittleIDE.g_IDEProject.project.config:GetConfig("code_module", {})
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
	info.project = ALittleIDE.g_IDEProject.project.code
	self._code_scroll_screen:AddChild(ALittleIDE.IDECodeTree(ALittleIDE.g_Control, info))
	local std_list = {"Core", "Std", "CEngine"}
	for index, name in ___ipairs(std_list) do
		info = {}
		info.module_name = name
		info.name = "src"
		info.path = ALittle.File_BaseFilePath() .. "Module/ALittleIDE/Other/GameLibrary/" .. name .. "/src"
		info.module_path = ALittle.File_BaseFilePath() .. "Module/ALittleIDE/Other/GameLibrary/" .. name .. "/"
		info.group = self._group
		info.root = true
		info.project = ALittleIDE.g_IDEProject.project.code
		local tree = ALittleIDE.IDECodeTree(ALittleIDE.g_Control, info)
		self._code_scroll_screen:AddChild(tree)
	end
	for index, module in ___pairs(module_map) do
		info = {}
		info.module_name = module.module_name
		info.name = ALittle.File_GetFileNameByPath(module.root_path)
		info.path = module.root_path
		info.module_path = ALittle.File_GetFilePathByPath(module.root_path) .. "/"
		info.group = self._group
		info.project = ALittleIDE.g_IDEProject.project.code
		info.root = true
		local tree = ALittleIDE.IDECodeTree(ALittleIDE.g_Control, info)
		self._code_scroll_screen:AddChild(tree)
	end
end

function ALittleIDE.IDEUICodeList:AddLibrary(name)
	local file_map = ALittle.File_GetNameListByDir(ALittle.File_BaseFilePath() .. "Module/ALittleIDE/Other/GameLibrary")
	local attr = file_map[name]
	if attr == nil or not attr.directory then
		return false
	end
	local module_map = ALittleIDE.g_IDEProject.project.config:GetConfig("code_module", {})
	local module_info = {}
	module_info.module_name = name
	module_info.root_path = ALittle.File_BaseFilePath() .. "Module/ALittleIDE/Other/GameLibrary/" .. name .. "/src"
	module_map[name] = module_info
	ALittleIDE.g_IDEProject.project.config:SetConfig("code_module", module_map)
	local info = {}
	info.module_name = name
	info.name = "src"
	info.path = ALittle.File_BaseFilePath() .. "Module/ALittleIDE/Other/GameLibrary/" .. name .. "/src"
	info.module_path = ALittle.File_BaseFilePath() .. "Module/ALittleIDE/Other/GameLibrary/" .. name .. "/"
	info.group = self._group
	info.root = true
	info.project = ALittleIDE.g_IDEProject.project.code
	local tree = ALittleIDE.IDECodeTree(ALittleIDE.g_Control, info)
	self._code_scroll_screen:AddChild(tree)
	return true
end

function ALittleIDE.IDEUICodeList:OpenByFullPath(full_path, line_start, char_start, line_end, char_end)
	if full_path == nil or full_path == "" then
		return nil
	end
	for index, child in ___ipairs(self._code_scroll_screen.childs) do
		local item = child:FindFile(full_path)
		if item ~= nil then
			local code_child = ALittleIDE.g_IDECenter.center.content_edit:StartEditCodeBySelect(item.user_info.name, item.user_info)
			code_child:JumpFocus(line_start, char_start, line_end, char_end)
			return code_child
		end
	end
	if ALittle.File_GetFileAttr(full_path) == nil then
		return nil
	end
	local user_info = {}
	user_info.name = ALittle.File_GetFileNameByPath(full_path)
	user_info.path = full_path
	local child = ALittleIDE.g_IDECenter.center.content_edit:StartEditCodeBySelect(user_info.name, user_info)
	if child == nil then
		return nil
	end
	child:JumpFocus(line_start, char_start, line_end, char_end)
	return child
end

function ALittleIDE.IDEUICodeList:GetCodeTree(full_path)
	for index, child in ___ipairs(self._code_scroll_screen.childs) do
		local item = child:FindFile(full_path)
		if item ~= nil then
			return item
		end
	end
	return nil
end

function ALittleIDE.IDEUICodeList:AddModule(name)
	for index, tree in ___ipairs(self._code_scroll_screen.childs) do
		if tree.user_info.module_name == name then
			return
		end
	end
	local module_map = ALittleIDE.g_IDEProject.project.config:GetConfig("code_module", {})
	local module_info = {}
	module_info.module_name = name
	module_info.root_path = ALittle.File_BaseFilePath() .. "Module/" .. name .. "/src"
	module_map[name] = module_info
	ALittleIDE.g_IDEProject.project.config:SetConfig("code_module", module_map)
	local info = {}
	info.module_name = name
	info.name = ALittle.File_GetFileNameByPath(module_info.root_path)
	info.path = module_info.root_path
	info.module_path = ALittle.File_BaseFilePath() .. "Module/" .. name .. "/"
	info.group = self._group
	info.root = true
	info.project = ALittleIDE.g_IDEProject.project.code
	local tree = ALittleIDE.IDECodeTree(ALittleIDE.g_Control, info)
	self._code_scroll_screen:AddChild(tree)
end

function ALittleIDE.IDEUICodeList:ShowTreeItemFocus(target)
	target:ShowSelect()
	if target ~= self._code_scroll_screen then
		local parent = target.logic_parent
		while parent ~= nil and parent ~= self._code_scroll_screen do
			parent.fold = true
			parent = parent.logic_parent
		end
	end
	self._code_scroll_screen:AdjustScrollBar()
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

function ALittleIDE.IDEUICodeList:HandleCodeSearchClick(event)
	if self._search_info == nil or self._search_info.name ~= self._code_search_key.text then
		self._search_info = {}
		self._search_info.name = self._code_search_key.text
		self._search_info.index = 0
		self._search_info.list = {}
		for index, child in ___ipairs(self._code_scroll_screen.childs) do
			child:SearchFile(self._search_info.name, self._search_info.list)
		end
		self._search_info.count = ALittle.List_Len(self._search_info.list)
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

function ALittleIDE.IDEUICodeList:SetCutTreeItem(item)
	self._cut_item = item
	self._copy_item = nil
end

function ALittleIDE.IDEUICodeList:GetCutTreeItem()
	return self._cut_item
end

function ALittleIDE.IDEUICodeList:SetCopyTreeItem(item)
	self._copy_item = item
	self._cut_item = nil
end

function ALittleIDE.IDEUICodeList:GetCopyTreeItem()
	return self._copy_item
end

function ALittleIDE.IDEUICodeList:ClearCutAndCopy()
	self._cut_item = nil
	self._copy_item = nil
end

end