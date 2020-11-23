-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.IDETabChild, " extends class:ALittleIDE.IDETabChild is nil")
ALittleIDE.IDETileTabChild = Lua.Class(ALittleIDE.IDETabChild, "ALittleIDE.IDETileTabChild")

function ALittleIDE.IDETileTabChild:Ctor(ctrl_sys, module, name, save, user_info)
	___rawset(self, "_user_info", user_info)
	___rawset(self, "_tab_screen", ALittleIDE.g_Control:CreateControl("ide_tile_tab_screen", self))
	self._tab_screen._user_data = self
end

function ALittleIDE.IDETileTabChild:OnUndo()
end

function ALittleIDE.IDETileTabChild:OnRedo()
end

function ALittleIDE.IDETileTabChild:OnHide()
end

function ALittleIDE.IDETileTabChild:OnShow()
end

function ALittleIDE.IDETileTabChild:OnClose()
end

function ALittleIDE.IDETileTabChild:OnOpen()
	self._revoke_list = ALittle.RevokeList()
end

function ALittleIDE.IDETileTabChild:OnTabRightMenu(menu)
	menu:AddItem("获取焦点", Lua.Bind(self.ShowTileFocus, self))
end

function ALittleIDE.IDETileTabChild:ShowTileFocus()
	local tree = ALittleIDE.g_IDECenter.center.tile_list:GetFileTree(self._user_info.info.path)
	if tree == nil then
		return
	end
	ALittleIDE.g_IDECenter.center.project_edit_tab.tab = ALittleIDE.g_IDECenter.center.tile_list
	ALittleIDE.g_IDECenter.center.tile_list:ShowTreeItemFocus(tree)
end

function ALittleIDE.IDETileTabChild.__getter:tab_body()
	return self._tab_screen
end

function ALittleIDE.IDETileTabChild.__setter:save(value)
	if self._save == value then
		return
	end
	if value == false then
		self._save = false
		self:UpdateTitle()
		return
	end
	self._save = value
	self:UpdateTitle()
end

function ALittleIDE.IDETileTabChild.__getter:id()
	return self._user_info.info.path
end

function ALittleIDE.IDETileTabChild:Rename(name)
	self._name = name
	self:UpdateTitle()
end

function ALittleIDE.IDETileTabChild:UpdateTitle()
	local text = self._name
	if self._save == false then
		text = text .. " *"
	end
	ALittleIDE.g_IDECenter.center.content_edit.main_tab:SetChildText(self._tab_screen, text)
end

function ALittleIDE.IDETileTabChild.__getter:title()
	return self._name
end

function ALittleIDE.IDETileTabChild:UpdateUserInfo(info)
	self._user_info = info
end

function ALittleIDE.IDETileTabChild:CreateBySelect(info)
	self._user_info = info
end

end