-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(2057209532, "AUIPlugin.AUICodeProjectGotoEvent", {
name = "AUIPlugin.AUICodeProjectGotoEvent", ns_name = "AUIPlugin", rl_name = "AUICodeProjectGotoEvent", hash_code = 2057209532,
name_list = {"target","file_path","line_start","char_start","line_end","char_end"},
type_list = {"ALittle.EventDispatcher","string","int","int","int","int"},
option_map = {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name = "ALittle.Event", ns_name = "ALittle", rl_name = "Event", hash_code = 1715346212,
name_list = {"target"},
type_list = {"ALittle.EventDispatcher"},
option_map = {}
})

g_ABnfProjectMap = ALittle.CreateValueWeakMap()
g_UpperExtMapABnf = {}
g_UpperExtMapABnf["JSON"] = "AJson.abnf"
g_UpperExtMapABnf["CFG"] = "AJson.abnf"
g_UpperExtMapABnf["XML"] = "AXml.abnf"
assert(ALittle.EventDispatcher, " extends class:ALittle.EventDispatcher is nil")
AUICodeProject = Lua.Class(ALittle.EventDispatcher, "AUIPlugin.AUICodeProject")

function AUICodeProject:Ctor(project)
	___rawset(self, "_query_id", 0)
	___rawset(self, "_project", project)
	___rawset(self, "_map", {})
end

function AUICodeProject.CreateALittleScriptProject()
	local abnf_buffer = ALittle.File_ReadTextFromFile(g_ModuleBasePath .. "Other/ABnf/ALittleScript.abnf")
	local project = AUICodeALittleScriptProject(alittlescript.create_alittlescript_project(abnf_buffer))
	project:Start()
	return project
end

function AUICodeProject.CreateABnfProject()
	local abnf_project = g_ABnfProjectMap["abnf"]
	if abnf_project == nil then
		local abnf_buffer = ALittle.File_ReadTextFromFile(g_ModuleBasePath .. "/Other/ABnf/ABnf.abnf")
		abnf_project = AUICodeABnfProject(abnf.create_abnf_project(abnf_buffer))
		g_ABnfProjectMap["abnf"] = abnf_project
		abnf_project:Start()
	end
	return abnf_project
end

function AUICodeProject.SupportUpperExt(upper_ext)
	return g_UpperExtMapABnf[upper_ext] ~= nil
end

function AUICodeProject.CreateCommonProject(upper_ext)
	local abnf = g_UpperExtMapABnf[upper_ext]
	if abnf == nil then
		return nil
	end
	local abnf_project = g_ABnfProjectMap[abnf]
	if abnf_project == nil then
		local abnf_buffer = ALittle.File_ReadTextFromFile(g_ModuleBasePath .. "/Other/ABnf/" .. abnf)
		abnf_project = AUICodeCommonProject(alanguage.create_abnfproject(abnf_buffer), upper_ext)
		g_ABnfProjectMap[abnf] = abnf_project
		abnf_project:Start()
	end
	return abnf_project
end

function AUICodeProject.Shutdown()
	for name, project in ___pairs(g_ABnfProjectMap) do
		project:Stop()
	end
	g_ABnfProjectMap = ALittle.CreateValueWeakMap()
end

function AUICodeProject.__getter:upper_ext()
	return nil
end

function AUICodeProject.__getter:project()
	return self._project
end

function AUICodeProject:QueryRuleColor()
	return alanguage.abnfproject_queryrulecolor(self._project)
end

function AUICodeProject:UpdateFile(module_path, full_path)
	alanguage.abnfproject_updatefile(self._project, module_path, full_path, 0)
end

function AUICodeProject:TempFile(module_path, full_path, text)
	alanguage.abnfproject_tempfile(self._project, module_path, full_path, text, 0)
end

function AUICodeProject:RemoveFile(full_path)
	alanguage.abnfproject_removefile(self._project, full_path)
end

function AUICodeProject:FindFile(text)
	local ___COROUTINE = coroutine.running()
	local query_id = self:Add(___COROUTINE)
	alanguage.abnfproject_findfile(self._project, query_id, text)
	return coroutine.yield()
end

function AUICodeProject:Start()
	if self._loop ~= nil then
		return
	end
	self._loop = ALittle.LoopFrame(Lua.Bind(self.Update, self))
	A_WeakLoopSystem:AddUpdater(self._loop)
end

function AUICodeProject:Add(thread)
	self._query_id = self._query_id + 1
	self._map[self._query_id] = thread
	return self._query_id
end

function AUICodeProject:OnTreeMenu(full_path, menu)
end

function AUICodeProject:OnTreeItemMenu(full_path, menu)
end

function AUICodeProject:Update(frame)
	while true do
		local info = alanguage.abnfproject_pollone(self._project)
		if info == nil then
			break
		end
		local thread = self._map[info.query_id]
		if thread ~= nil then
			self._map[info.query_id] = nil
			ALittle.Coroutine.Resume(thread, info.result)
		end
	end
end

function AUICodeProject:Stop()
	alanguage.abnfproject_clear(self._project)
	if self._loop == nil then
		return
	end
	A_WeakLoopSystem:RemoveUpdater(self._loop)
	self._loop = nil
end

