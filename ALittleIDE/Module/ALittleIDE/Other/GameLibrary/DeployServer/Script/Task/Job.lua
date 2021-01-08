-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleDeploy == nil then _G.ALittleDeploy = {} end
local ALittleDeploy = ALittleDeploy
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


ALittleDeploy.Job = Lua.Class(nil, "ALittleDeploy.Job")

function ALittleDeploy.Job:Ctor(info)
	___rawset(self, "_info", info)
end

function ALittleDeploy.Job.__getter:info()
	return self._info
end

function ALittleDeploy.CreateJob(info)
	return nil
end

end