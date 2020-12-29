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

ALittle.RegStruct(-1898137181, "AUIPlugin.AUICodeEditJumpEvent", {
name = "AUIPlugin.AUICodeEditJumpEvent", ns_name = "AUIPlugin", rl_name = "AUICodeEditJumpEvent", hash_code = -1898137181,
name_list = {"target","file_path","it_line","it_char"},
type_list = {"ALittle.DisplayObject","string","int","int"},
option_map = {}
})
ALittle.RegStruct(1575183661, "AUIPlugin.AUICodeEditBreakPointEvent", {
name = "AUIPlugin.AUICodeEditBreakPointEvent", ns_name = "AUIPlugin", rl_name = "AUICodeEditBreakPointEvent", hash_code = 1575183661,
name_list = {"target","add_or_remove","file_path","file_line"},
type_list = {"ALittle.DisplayObject","bool","string","int"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name = "ALittle.UIChangedEvent", ns_name = "ALittle", rl_name = "UIChangedEvent", hash_code = 958494922,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(631224630, "AUIPlugin.AUICodeEditGotoEvent", {
name = "AUIPlugin.AUICodeEditGotoEvent", ns_name = "AUIPlugin", rl_name = "AUICodeEditGotoEvent", hash_code = 631224630,
name_list = {"target","file_path","line_start","char_start","line_end","char_end"},
type_list = {"ALittle.DisplayObject","string","int","int","int","int"},
option_map = {}
})

assert(ALittleIDE.IDETabChild, " extends class:ALittleIDE.IDETabChild is nil")
ALittleIDE.IDECodeTabChild = Lua.Class(ALittleIDE.IDETabChild, "ALittleIDE.IDECodeTabChild")

function ALittleIDE.IDECodeTabChild:Ctor(ctrl_sys, module, name, save, user_info)
	___rawset(self, "_user_info", user_info)
	___rawset(self, "_edit", ALittleIDE.g_AUIPluinControl:CreateControl("code_tab_screen", self))
	self._edit:AddEventListener(___all_struct[958494922], self, self.HandleChangedEvent)
	self._edit:AddEventListener(___all_struct[631224630], self, self.HandleEditGotoEvent)
	self._edit:AddEventListener(___all_struct[-1898137181], self, self.HandleJumpCodeEvent)
	self._edit:AddEventListener(___all_struct[1575183661], self, self.HandleBreakPointEvent)
	self._edit._user_data = self
end

function ALittleIDE.IDECodeTabChild:OnUndo()
	self._edit:OnUnDo()
end

function ALittleIDE.IDECodeTabChild:OnRedo()
end

function ALittleIDE.IDECodeTabChild:OnHide()
	self._edit:OnHide()
	ALittleIDE.g_IDECenter.center.tool_code.visible = false
end

function ALittleIDE.IDECodeTabChild:OnShow()
	self._edit:OnShow()
	ALittleIDE.g_IDECenter.center.tool_code.visible = true
end

function ALittleIDE.IDECodeTabChild:OnClose()
	self._edit:OnClose()
end

function ALittleIDE.IDECodeTabChild:OnOpen()
	self._revoke_list = ALittle.RevokeList(10000)
	if self._language == nil and self._user_info.project ~= nil and ALittle.File_GetFileExtByPathAndUpper(self._user_info.path) == self._user_info.project.upper_ext then
		self._language = AUIPlugin.AUICodeALittleScript(self._user_info.project, self._user_info.path, self._user_info.module_path)
	end
	self._edit:Load(self._user_info.path, nil, self._revoke_list, self._language, ALittleIDE.g_IDEProject:GetBreakPoint(self._user_info.path))
end

function ALittleIDE.IDECodeTabChild:OnTabRightMenu(menu)
	self._edit:OnTabRightMenu(menu)
	menu:AddItem("获取焦点", Lua.Bind(self.ShowControlFocus, self))
end

function ALittleIDE.IDECodeTabChild:ShowControlFocus()
	local tree = ALittleIDE.g_IDECenter.center.code_list:GetCodeTree(self._user_info.path)
	if tree == nil then
		return
	end
	ALittleIDE.g_IDECenter.center.project_edit_tab.tab = ALittleIDE.g_IDECenter.center.code_list
	ALittleIDE.g_IDECenter.center.code_list:ShowTreeItemFocus(tree)
end

function ALittleIDE.IDECodeTabChild:HandleEditGotoEvent(event)
	local info = {}
	info.file_path = event.file_path
	info.it_line = event.line_start
	info.it_char = event.char_start
	ALittleIDE.g_IDECenter.center.code_list:AddCodeJump(info)
	ALittleIDE.g_IDECenter.center.code_list:OpenByFullPath(event.file_path, event.line_start, event.char_start, event.line_end, event.char_end)
end

function ALittleIDE.IDECodeTabChild:HandleJumpCodeEvent(event)
	local info = {}
	info.file_path = event.file_path
	info.it_line = event.it_line
	info.it_char = event.it_char
	ALittleIDE.g_IDECenter.center.code_list:AddCodeJump(info)
end

function ALittleIDE.IDECodeTabChild:HandleBreakPointEvent(event)
	if event.add_or_remove then
		ALittleIDE.g_IDEProject:AddBreakPoint(event.file_path, event.file_line)
	else
		ALittleIDE.g_IDEProject:RemoveBreakPoint(event.file_path, event.file_line)
	end
end

function ALittleIDE.IDECodeTabChild:HandleChangedEvent(event)
	self.save = false
end

function ALittleIDE.IDECodeTabChild.__getter:tab_body()
	return self._edit
end

function ALittleIDE.IDECodeTabChild.__setter:save(value)
	if self._save == value then
		return
	end
	if value == false then
		self._save = false
		self:UpdateTitle()
		return
	end
	self._edit:Save()
	self._save = value
	self:UpdateTitle()
end

function ALittleIDE.IDECodeTabChild.__getter:id()
	return self._user_info.path
end

function ALittleIDE.IDECodeTabChild:Rename(name)
	self._name = name
	self:UpdateTitle()
end

function ALittleIDE.IDECodeTabChild:UpdateTitle()
	local text = self._name
	if self._save == false then
		text = text .. " *"
	end
	ALittleIDE.g_IDECenter.center.content_edit.main_tab:SetChildText(self._edit, text)
end

function ALittleIDE.IDECodeTabChild.__getter:title()
	return self._name
end

function ALittleIDE.IDECodeTabChild:UpdateUserInfo(info)
	self:OnClose()
	self._language = nil
	self._user_info = info
	self:OnOpen()
end

function ALittleIDE.IDECodeTabChild:CreateBySelect(info)
	self._user_info = info
	self._edit:EditFocus(0, 0, nil, nil, true)
end

function ALittleIDE.IDECodeTabChild:JumpFocus(line_start, char_start, line_end, char_end)
	self._edit:EditFocus(line_start, char_start, line_end, char_end, true)
end

function ALittleIDE.IDECodeTabChild:FindText(text)
	self._edit:FindNext(text)
end

function ALittleIDE.IDECodeTabChild.__getter:edit()
	return self._edit
end

end