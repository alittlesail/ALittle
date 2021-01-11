-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleDeploy == nil then _G.ALittleDeploy = {} end
local ALittleDeploy = ALittleDeploy
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


ALittleDeploy.Task = Lua.Class(nil, "ALittleDeploy.Task")

function ALittleDeploy.Task:Ctor(info)
	___rawset(self, "_job_list", {})
	___rawset(self, "_info", info)
	___rawset(self, "_upper_name", ALittle.String_Upper(info.task_name))
	for index, job_info in ___ipairs(info.job_list) do
		local job = ALittleDeploy.CreateJob(job_info)
		self._job_list[index] = job
	end
end

function ALittleDeploy.Task:Start()
end

function ALittleDeploy.Task:StartByWebHook(url)
	for key, open in ___pairs(self._info.web_hook) do
		if key == url and open then
			self:Start()
			break
		end
	end
end

function ALittleDeploy.Task.__getter:info()
	return self._info
end

function ALittleDeploy.Task.__getter:upper_name()
	return self._upper_name
end

end