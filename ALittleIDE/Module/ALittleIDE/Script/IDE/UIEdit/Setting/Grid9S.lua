-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayLayoutS, " extends class:ALittleIDE.DisplayLayoutS is nil")
ALittleIDE.Grid9S = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.Grid9S")

function ALittleIDE.Grid9S:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_grid9")
end

function ALittleIDE.Grid9S:LoadNatureBase()
	ALittleIDE.DisplayLayoutS.LoadNatureBase(self)
	self:LoadValueData("left_size")
	self:LoadValueData("right_size")
	self:LoadValueData("top_size")
	self:LoadValueData("bottom_size")
end

function ALittleIDE.Grid9S:HandleGrid9LeftFOCUSOUT(event)
	self:ValueNumInputChange("left_size", false)
end

function ALittleIDE.Grid9S:HandleGrid9RightFOCUSOUT(event)
	self:ValueNumInputChange("right_size", false)
end

function ALittleIDE.Grid9S:HandleGrid9TopFOCUSOUT(event)
	self:ValueNumInputChange("top_size", false)
end

function ALittleIDE.Grid9S:HandleGrid9BottomFOCUSOUT(event)
	self:ValueNumInputChange("bottom_size", false)
end

function ALittleIDE.Grid9S:HandleAutoCut(event)
	local revoke_bind = ALittle.RevokeBind()
	self._left_size.text = 0
	self:ValueNumInputChange("left_size", false, revoke_bind)
	self._right_size.text = 0
	self:ValueNumInputChange("right_size", false, revoke_bind)
	self._top_size.text = 0
	self:ValueNumInputChange("top_size", false, revoke_bind)
	self._bottom_size.text = 0
	self:ValueNumInputChange("bottom_size", false, revoke_bind)
	self._tab_child.revoke_list:PushRevoke(revoke_bind)
end

end