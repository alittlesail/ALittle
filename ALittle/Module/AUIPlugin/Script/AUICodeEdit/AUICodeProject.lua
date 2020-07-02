-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


AUICodeProject = Lua.Class(nil, "AUIPlugin.AUICodeProject")

function AUICodeProject:Ctor(project)
	___rawset(self, "_query_id", 0)
	___rawset(self, "_project", project)
	___rawset(self, "_map", {})
end

function AUICodeProject.__getter:project()
	return self._project
end

function AUICodeProject:UpdateFile(full_path)
	alanguage.abnfproject_updatefile(self._project, full_path)
end

function AUICodeProject:RemoveFile(full_path)
	alanguage.abnfproject_removefile(self._project, full_path)
end

function AUICodeProject:Start()
	if self._loop ~= nil then
		return
	end
	self._loop = ALittle.LoopFrame(Lua.Bind(self.Update, self))
	self._loop:Start()
end

function AUICodeProject:Add(thread)
	self._query_id = self._query_id + 1
	self._map[self._query_id] = thread
	return self._query_id
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
	if self._loop == nil then
		return
	end
	self._loop:Stop()
	self._loop = nil
end

