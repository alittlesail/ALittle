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
ALittleIDE.ScrollScreenS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.ScrollScreenS")

function ALittleIDE.ScrollScreenS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_scrollscreen")
end

function ALittleIDE.ScrollScreenS:LoadNatureBase()
	ALittleIDE.DisplayLayoutS.LoadNatureBase(self)
	self:LoadShowTypeDataForExtends("container")
	self:LoadShowTypeDataForExtends("right_scrollbar")
	self:LoadShowTypeDataForExtends("bottom_scrollbar")
	self:LoadBoolData("open_extends_drag", true, ALittleIDE.g_IDEEnum.yn_type)
end

function ALittleIDE.ScrollScreenS:HandleContainerFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForExtends("container", self._container.text, false)
end

function ALittleIDE.ScrollScreenS:HandleRightSFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForExtends("right_scrollbar", self._right_scrollbar.text, false)
end

function ALittleIDE.ScrollScreenS:HandleBottomBFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForExtends("bottom_scrollbar", self._bottom_scrollbar.text, false)
end

function ALittleIDE.ScrollScreenS:HandleHandOpenExtendsDragSELECT_CHANGE(event)
	self:BoolSelectChange("open_extends_drag", false, ALittleIDE.g_IDEEnum.yn_type)
end

end