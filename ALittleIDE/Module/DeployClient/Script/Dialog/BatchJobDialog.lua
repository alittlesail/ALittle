-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DeployClient == nil then _G.DeployClient = {} end
local DeployClient = DeployClient
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


assert(DeployClient.CommonJobDialog, " extends class:DeployClient.CommonJobDialog is nil")
DeployClient.BatchJobDialog = Lua.Class(DeployClient.CommonJobDialog, "DeployClient.BatchJobDialog")

function DeployClient.BatchJobDialog.__getter:type()
	return 1
end

function DeployClient.BatchJobDialog:ShowDetail(detail)
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

function DeployClient.BatchJobDialog:GetDetail()
	local detail = {}
	detail.batch_dir = self._dir.text
	detail.batch_cmd = self._cmd.text
	detail.batch_param = self._param.text
	return detail
end

end