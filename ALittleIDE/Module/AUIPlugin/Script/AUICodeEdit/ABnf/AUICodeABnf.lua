-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.AUIPlugin == nil then _G.AUIPlugin = {} end
local AUIPlugin = AUIPlugin
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


local g_ABnfColor = nil
AUIPlugin.ABnfColorType = {
	ABnfKeyWord = 1,
	ABnfId = 2,
	ABnfComment = 3,
	ABnfKey = 4,
	ABnfString = 5,
	ABnfRegex = 6,
	ABnfNodeTail = 7,
	ABnfNumber = 8,
}

assert(AUIPlugin.AUICodeLanguage, " extends class:AUIPlugin.AUICodeLanguage is nil")
AUIPlugin.AUICodeABnf = Lua.Class(AUIPlugin.AUICodeLanguage, "AUIPlugin.AUICodeABnf")

function AUIPlugin.AUICodeABnf:Ctor(project, full_path)
	if self._project == nil then
		___rawset(self, "_project", AUIPlugin.AUICodeProject.CreateABnfProject())
	end
	if g_ABnfColor == nil then
		g_ABnfColor = {}
		local color
		do
			color = {}
			color.red = 255 / 255
			color.green = 198 / 255
			color.blue = 109 / 255
			g_ABnfColor[1] = color
		end
		do
			color = {}
			color.red = 204 / 255
			color.green = 120 / 255
			color.blue = 50 / 255
			g_ABnfColor[2] = color
		end
		do
			color = {}
			color.red = 128 / 255
			color.green = 128 / 255
			color.blue = 128 / 255
			g_ABnfColor[3] = color
		end
		do
			color = {}
			color.red = 53 / 255
			color.green = 155 / 255
			color.blue = 185 / 255
			g_ABnfColor[4] = color
		end
		do
			color = {}
			color.red = 85 / 255
			color.green = 134 / 255
			color.blue = 74 / 255
			g_ABnfColor[5] = color
		end
		do
			color = {}
			color.red = 152 / 255
			color.green = 118 / 255
			color.blue = 170 / 255
			g_ABnfColor[6] = color
		end
		do
			color = {}
			color.red = 152 / 255
			color.green = 118 / 255
			color.blue = 170 / 255
			g_ABnfColor[8] = color
		end
	end
	___rawset(self, "_abnf_file", abnf.create_abnf_file(self._project.project, full_path, ""))
end

function AUIPlugin.AUICodeABnf:OnOpen(content)
	if content ~= nil then
		self._project:TempFile("", self._full_path, content)
	else
		self._project:UpdateFile("", self._full_path)
	end
end

function AUIPlugin.AUICodeABnf:OnShow()
end

function AUIPlugin.AUICodeABnf:OnHide()
end

function AUIPlugin.AUICodeABnf:OnClose()
	self._project:RemoveFile(self._full_path)
end

function AUIPlugin.AUICodeABnf:QueryColorValue(tag)
	return g_ABnfColor[tag]
end

function AUIPlugin.AUICodeABnf:OnRightMenu(menu)
	menu:AddItem("生成", Lua.Bind(self.GenerateABnf, self))
end

function AUIPlugin.AUICodeABnf:OnTabRightMenu(menu)
	menu:AddItem("生成", Lua.Bind(self.GenerateABnf, self))
end

function AUIPlugin.AUICodeABnf:GenerateABnf()
	local file_name = ALittle.File_GetJustFileNameByPath(self._full_path)
	local path = g_AUITool:ShowSelectDir("选择生成的文件夹", self._generate_dir)
	if path == nil then
		return
	end
	local attr = ALittle.File_GetFileAttr(path)
	if attr == nil or attr.directory ~= true then
		g_AUITool:ShowNotice("错误", "文件夹不存在")
		return
	end
	self._generate_dir = path
	ALittle.File_DeleteDeepDir(path .. "/Generate")
	ALittle.File_MakeDeepDir(path .. "/Generate")
	local error = self:Generate(path .. "/Generate", file_name)
	if error ~= nil then
		g_AUITool:ShowNotice("错误", error)
		return
	end
	g_AUITool:ShowNotice("提示", "生成成功")
end
AUIPlugin.AUICodeABnf.GenerateABnf = Lua.CoWrap(AUIPlugin.AUICodeABnf.GenerateABnf)

function AUIPlugin.AUICodeABnf:Generate(target_path, language_name)
	local ___COROUTINE = coroutine.running()
	local query_id = self._project:Add(___COROUTINE)
	abnf.abnffile_generate(self._abnf_file, query_id, self._version, target_path, language_name)
	return coroutine.yield()
end

assert(AUIPlugin.AUICodeProject, " extends class:AUIPlugin.AUICodeProject is nil")
AUIPlugin.AUICodeABnfProject = Lua.Class(AUIPlugin.AUICodeProject, "AUIPlugin.AUICodeABnfProject")

function AUIPlugin.AUICodeABnfProject.__getter:upper_ext()
	return "ABNF"
end

function AUIPlugin.AUICodeABnfProject:OnTreeMenu(full_path, menu)
end

function AUIPlugin.AUICodeABnfProject:OnTreeItemMenu(full_path, menu)
end

end