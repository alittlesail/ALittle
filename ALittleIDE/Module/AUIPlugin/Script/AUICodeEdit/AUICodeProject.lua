-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.AUIPlugin == nil then _G.AUIPlugin = {} end
local AUIPlugin = AUIPlugin
local Lua = Lua
local ALittle = ALittle
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

AUIPlugin.g_ABnfProjectMap = ALittle.CreateValueWeakMap()
AUIPlugin.g_UpperExtMapABnf = {}
AUIPlugin.g_UpperExtMapABnf["JSON"] = "AJson.abnf"
AUIPlugin.g_UpperExtMapABnf["CFG"] = "AJson.abnf"
AUIPlugin.g_UpperExtMapABnf["XML"] = "AXml.abnf"
AUIPlugin.g_UpperExtMapABnf["LUA"] = "ALua.abnf"
assert(ALittle.EventDispatcher, " extends class:ALittle.EventDispatcher is nil")
AUIPlugin.AUICodeProject = Lua.Class(ALittle.EventDispatcher, "AUIPlugin.AUICodeProject")

function AUIPlugin.AUICodeProject:Ctor(project)
	___rawset(self, "_query_id", 0)
	___rawset(self, "_project", project)
	___rawset(self, "_map", {})
end

function AUIPlugin.AUICodeProject.CreateALittleScriptProject()
	if alittlescript == nil then
		return nil
	end
	local abnf_buffer = ALittle.File_ReadTextFromFile(AUIPlugin.g_ModuleBasePath .. "Other/ABnf/ALittleScript.abnf")
	local project = AUIPlugin.AUICodeALittleScriptProject(alittlescript.create_alittlescript_project(abnf_buffer))
	project:Start()
	return project
end

function AUIPlugin.AUICodeProject.CreateABnfProject()
	if abnf == nil then
		return nil
	end
	local abnf_project = AUIPlugin.g_ABnfProjectMap["abnf"]
	if abnf_project == nil then
		local abnf_buffer = ALittle.File_ReadTextFromFile(AUIPlugin.g_ModuleBasePath .. "/Other/ABnf/ABnf.abnf")
		abnf_project = AUIPlugin.AUICodeABnfProject(abnf.create_abnf_project(abnf_buffer))
		AUIPlugin.g_ABnfProjectMap["abnf"] = abnf_project
		abnf_project:Start()
	end
	return abnf_project
end

function AUIPlugin.AUICodeProject.SupportUpperExt(upper_ext)
	return AUIPlugin.g_UpperExtMapABnf[upper_ext] ~= nil
end

function AUIPlugin.AUICodeProject.CreateCommonProject(upper_ext)
	if alanguage == nil then
		return nil
	end
	local abnf = AUIPlugin.g_UpperExtMapABnf[upper_ext]
	if abnf == nil then
		return nil
	end
	local abnf_project = AUIPlugin.g_ABnfProjectMap[abnf]
	if abnf_project == nil then
		local abnf_buffer = ALittle.File_ReadTextFromFile(AUIPlugin.g_ModuleBasePath .. "/Other/ABnf/" .. abnf)
		abnf_project = AUIPlugin.AUICodeCommonProject(alanguage.create_abnfproject(abnf_buffer), upper_ext)
		AUIPlugin.g_ABnfProjectMap[abnf] = abnf_project
		abnf_project:Start()
	end
	return abnf_project
end

function AUIPlugin.AUICodeProject.Shutdown()
	for name, project in ___pairs(AUIPlugin.g_ABnfProjectMap) do
		project:Stop()
	end
	AUIPlugin.g_ABnfProjectMap = ALittle.CreateValueWeakMap()
end

function AUIPlugin.AUICodeProject.__getter:upper_ext()
	return nil
end

function AUIPlugin.AUICodeProject.__getter:project()
	return self._project
end

function AUIPlugin.AUICodeProject:QueryRuleColor()
	return alanguage.abnfproject_queryrulecolor(self._project)
end

function AUIPlugin.AUICodeProject:UpdateFile(module_path, full_path)
	alanguage.abnfproject_updatefile(self._project, module_path, full_path, 0)
end

function AUIPlugin.AUICodeProject:TempFile(module_path, full_path, text)
	alanguage.abnfproject_tempfile(self._project, module_path, full_path, text, 0)
end

function AUIPlugin.AUICodeProject:RemoveFile(full_path)
	alanguage.abnfproject_removefile(self._project, full_path)
end

function AUIPlugin.AUICodeProject:FindFile(text)
	local ___COROUTINE = coroutine.running()
	local query_id = self:Add(___COROUTINE)
	alanguage.abnfproject_findfile(self._project, query_id, text)
	return coroutine.yield()
end

function AUIPlugin.AUICodeProject:FindDefine(pre_input, input)
	local ___COROUTINE = coroutine.running()
	local query_id = self:Add(___COROUTINE)
	alanguage.abnfproject_finddefine(self._project, query_id, pre_input, input)
	return coroutine.yield()
end

function AUIPlugin.AUICodeProject:FindGoto(text)
	local ___COROUTINE = coroutine.running()
	local query_id = self:Add(___COROUTINE)
	alanguage.abnfproject_findgoto(self._project, query_id, text)
	return coroutine.yield()
end

function AUIPlugin.AUICodeProject:QueryCompleteIcon(tag)
	return nil
end

function AUIPlugin.AUICodeProject:Start()
	if self._loop ~= nil then
		return
	end
	self._loop = ALittle.LoopFrame(Lua.Bind(self.Update, self))
	A_WeakLoopSystem:AddUpdater(self._loop)
end

function AUIPlugin.AUICodeProject:Add(thread)
	self._query_id = self._query_id + 1
	self._map[self._query_id] = thread
	return self._query_id
end

function AUIPlugin.AUICodeProject:OnTreeMenu(full_path, menu)
end

function AUIPlugin.AUICodeProject:OnTreeItemMenu(full_path, menu)
end

function AUIPlugin.AUICodeProject:Update(frame)
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

function AUIPlugin.AUICodeProject:Stop()
	alanguage.abnfproject_clear(self._project)
	if self._loop == nil then
		return
	end
	A_WeakLoopSystem:RemoveUpdater(self._loop)
	self._loop = nil
end

end