-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleIDE.DisplayLayoutS, " extends class:ALittleIDE.DisplayLayoutS is nil")
PiechartS = Lua.Class(ALittleIDE.DisplayLayoutS, "ALittleIDE.PiechartS")

function PiechartS:Ctor(user_info, tab_child, tree_logic)
	___rawset(self, "_layer_name", "ide_setting_piechart")
end

function PiechartS:LoadNatureBase()
	DisplayLayoutS.LoadNatureBase(self)
	self:LoadDefaultNilString("texture_name")
	self:LoadValueData("start_degree")
	self:LoadValueData("end_degree")
end

function PiechartS:HandleImageTextureNameFOCUSOUT(event)
	self:DefaultNilStringInputChange("texture_name", false)
end

function PiechartS:HandleImageTextureNameSelect(event)
	g_IDEImageSelectDialog:SetBasePath(g_IDEProject.project.texture_path)
	local path = g_IDEImageSelectDialog:ShowSelect()
	if path == nil then
		return
	end
	self:ImagePathSelectCallback("texture_name", self.HandleImageTextureNameFOCUSOUT, nil, path)
end
PiechartS.HandleImageTextureNameSelect = Lua.CoWrap(PiechartS.HandleImageTextureNameSelect)

function PiechartS:HandleImageStartDegreeFOCUSOUT(event)
	self:ValueNumZInputChange("start_degree", false)
end

function PiechartS:HandleImageEndDegreeFOCUSOUT(event)
	self:ValueNumZInputChange("end_degree", false)
end

