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
ALittleIDE.IDECodeTreeLogic = Lua.Class(ALittle.DisplayLayout, "ALittleIDE.IDECodeTreeLogic")

function ALittleIDE.IDECodeTreeLogic:Ctor(ctrl_sys, user_info)
	___rawset(self, "_user_info", user_info)
end

function ALittleIDE.IDECodeTreeLogic.__getter:user_info()
	return self._user_info
end

function ALittleIDE.IDECodeTreeLogic.__getter:is_tree()
	return false
end

function ALittleIDE.IDECodeTreeLogic.__getter:is_root()
	return self._user_info.root
end

function ALittleIDE.IDECodeTreeLogic.__setter:fold(value)
end

function ALittleIDE.IDECodeTreeLogic:ShowSelect()
	if self._item_button ~= nil then
		self._item_button.selected = true
	end
end

function ALittleIDE.IDECodeTreeLogic:Refresh()
end

function ALittleIDE.IDECodeTreeLogic:SearchFile(name, list)
	if list == nil then
		list = {}
	end
	return list
end

function ALittleIDE.IDECodeTreeLogic:FindFile(full_path)
	return nil
end

function ALittleIDE.IDECodeTreeLogic:OnDelete()
end

end