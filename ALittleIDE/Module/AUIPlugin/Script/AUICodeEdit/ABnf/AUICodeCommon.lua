-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.AUIPlugin == nil then _G.AUIPlugin = {} end
local AUIPlugin = AUIPlugin
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(AUIPlugin.AUICodeLanguage, " extends class:AUIPlugin.AUICodeLanguage is nil")
AUIPlugin.AUICodeCommon = Lua.Class(AUIPlugin.AUICodeLanguage, "AUIPlugin.AUICodeCommon")

function AUIPlugin.AUICodeCommon:Ctor(project, full_path)
	if self._project == nil then
		___rawset(self, "_project", AUIPlugin.AUICodeProject.CreateCommonProject(ALittle.File_GetFileExtByPathAndUpper(full_path)))
	end
	___rawset(self, "_abnf_color", self._project:QueryRuleColor())
	___rawset(self, "_abnf_file", alanguage.create_abnffile(self._project.project, full_path, ""))
end

function AUIPlugin.AUICodeCommon:OnOpen(content)
	if content ~= nil then
		self._project:TempFile("", self._full_path, content)
	else
		self._project:UpdateFile("", self._full_path)
	end
end

function AUIPlugin.AUICodeCommon:OnShow()
end

function AUIPlugin.AUICodeCommon:OnHide()
end

function AUIPlugin.AUICodeCommon:OnClose()
	self._project:RemoveFile(self._full_path)
end

function AUIPlugin.AUICodeCommon:QueryColorValue(tag)
	return self._abnf_color[tag]
end

function AUIPlugin.AUICodeCommon:OnRightMenu(menu)
end

assert(AUIPlugin.AUICodeProject, " extends class:AUIPlugin.AUICodeProject is nil")
AUIPlugin.AUICodeCommonProject = Lua.Class(AUIPlugin.AUICodeProject, "AUIPlugin.AUICodeCommonProject")

function AUIPlugin.AUICodeCommonProject:Ctor(project, upper_ext)
	___rawset(self, "_upper_ext", upper_ext)
end

function AUIPlugin.AUICodeCommonProject.__getter:upper_ext()
	return self._upper_ext
end

function AUIPlugin.AUICodeCommonProject:OnTreeMenu(full_path, menu)
end

function AUIPlugin.AUICodeCommonProject:OnTreeItemMenu(full_path, menu)
end

end