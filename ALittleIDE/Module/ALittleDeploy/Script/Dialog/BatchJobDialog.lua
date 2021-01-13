-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleDeploy == nil then _G.ALittleDeploy = {} end
local ALittleDeploy = ALittleDeploy
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleDeploy.CommonJobDialog, " extends class:ALittleDeploy.CommonJobDialog is nil")
ALittleDeploy.BatchJobDialog = Lua.Class(ALittleDeploy.CommonJobDialog, "ALittleDeploy.BatchJobDialog")

function ALittleDeploy.BatchJobDialog.__getter:type()
	return 1
end

function ALittleDeploy.BatchJobDialog:ShowDetail(detail)
	if detail ~= nil then
		self._dir.text = detail.batch_dir
		self._cmd.text = detail.batch_cmd
		self._param.text = detail.batch_param
	else
		self._dir.text = ""
		self._cmd.text = ""
		self._param.text = ""
	end
end

function ALittleDeploy.BatchJobDialog:GetDetail()
	local detail = {}
	detail.batch_dir = self._dir.text
	detail.batch_cmd = self._cmd.text
	detail.batch_param = self._param.text
	return detail
end

end