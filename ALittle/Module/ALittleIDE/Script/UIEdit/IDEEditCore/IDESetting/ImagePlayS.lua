
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine


assert(DisplayObjectS, " extends class:DisplayObjectS is nil")
ImagePlayS = ALittle.Class(DisplayObjectS, "ALittleIDE.ImagePlayS")

function ImagePlayS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_imageplay")
end

function ImagePlayS:LoadNatureBase()
	DisplayObjectS.LoadNatureBase(self)
	self:LoadValueData("interval")
	self:LoadShowTypeData("path_list")
end

function ImagePlayS:HandleIntervalFOCUSOUT(event)
	self:ValueNumZInputChange("interval", false)
end

function ImagePlayS:HandlePathListFOCUSOUT(event)
	self:TableDataSet("path_list", false)
end

