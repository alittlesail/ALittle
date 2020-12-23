-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittleIDE.IDEControlTreeLogic = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDEControlTreeLogic")

function ALittleIDE.IDEControlTreeLogic:Ctor(ctrl_sys, user_info)
	___rawset(self, "_user_info", user_info)
end

function ALittleIDE.IDEControlTreeLogic.__getter:user_info()
	return self._user_info
end

function ALittleIDE.IDEControlTreeLogic.__getter:is_tree()
	return false
end

function ALittleIDE.IDEControlTreeLogic.__getter:is_root()
	return self._user_info.root
end

function ALittleIDE.IDEControlTreeLogic.__setter:fold(value)
end

function ALittleIDE.IDEControlTreeLogic:ShowSelect()
	if self._item_button ~= nil then
		self._item_button.selected = true
	end
end

function ALittleIDE.IDEControlTreeLogic:Refresh()
end

function ALittleIDE.IDEControlTreeLogic:SearchFile(name, list)
	if list == nil then
		list = {}
	end
	return list
end

function ALittleIDE.IDEControlTreeLogic:FindFile(full_path)
	return nil
end

function ALittleIDE.IDEControlTreeLogic:OnDelete()
end

end