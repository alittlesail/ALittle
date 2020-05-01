-- ALittle Generate Lua
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayLayoutS, " extends class:ALittleIDE.DisplayLayoutS is nil")
ScrollScreenS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.ScrollScreenS")

function ScrollScreenS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_scrollscreen")
end

function ScrollScreenS:LoadNatureBase()
	DisplayLayoutS.LoadNatureBase(self)
	self:LoadShowTypeDataForExtends("container")
	self:LoadShowTypeDataForExtends("right_scrollbar")
	self:LoadShowTypeDataForExtends("bottom_scrollbar")
	self:LoadBoolData("open_extends_drag", true, g_IDEEnum.yn_type)
end

function ScrollScreenS:HandleContainerFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForExtends("container", self._container.text, false)
end

function ScrollScreenS:HandleRightSFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForExtends("right_scrollbar", self._right_scrollbar.text, false)
end

function ScrollScreenS:HandleBottomBFOCUSOUT(event)
	if event.target._user_data ~= nil then
		if event.target._user_data == event.target.text then
			return
		end
		event.target._user_data = event.target.text
	end
	self:RemoverToNilShowSetForExtends("bottom_scrollbar", self._bottom_scrollbar.text, false)
end

function ScrollScreenS:HandleHandOpenExtendsDragSELECT_CHANGE(event)
	self:BoolSelectChange("open_extends_drag", false, g_IDEEnum.yn_type)
end

