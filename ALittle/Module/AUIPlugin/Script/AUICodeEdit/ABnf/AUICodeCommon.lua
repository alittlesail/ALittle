-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(AUIPlugin.AUICodeLanguage, " extends class:AUIPlugin.AUICodeLanguage is nil")
AUICodeCommon = Lua.Class(AUIPlugin.AUICodeLanguage, "AUIPlugin.AUICodeCommon")

function AUICodeCommon:Ctor(project, full_path)
	if self._project == nil then
		___rawset(self, "_project", AUICodeProject.CreateCommonProject(ALittle.File_GetFileExtByPathAndUpper(full_path)))
	end
	___rawset(self, "_abnf_color", self._project:QueryRuleColor())
	___rawset(self, "_abnf_file", alanguage.create_abnffile(self._project.project, full_path, ""))
end

function AUICodeCommon:OnOpen()
	self._project:UpdateFile("", self._full_path)
end

function AUICodeCommon:OnShow()
end

function AUICodeCommon:OnHide()
end

function AUICodeCommon:OnClose()
	self._project:RemoveFile(self._full_path)
end

function AUICodeCommon:QueryColorValue(tag)
	return self._abnf_color[tag]
end

function AUICodeCommon:OnRightMenu(menu)
end

assert(AUIPlugin.AUICodeProject, " extends class:AUIPlugin.AUICodeProject is nil")
AUICodeCommonProject = Lua.Class(AUIPlugin.AUICodeProject, "AUIPlugin.AUICodeCommonProject")

function AUICodeCommonProject:Ctor(project, upper_ext)
	___rawset(self, "_upper_ext", upper_ext)
end

function AUICodeCommonProject.__getter:upper_ext()
	return self._upper_ext
end

function AUICodeCommonProject:OnTreeMenu(full_path, menu)
end

function AUICodeCommonProject:OnTreeItemMenu(full_path, menu)
end

