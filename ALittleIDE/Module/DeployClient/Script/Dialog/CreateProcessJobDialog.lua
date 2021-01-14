-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DeployClient == nil then _G.DeployClient = {} end
local DeployClient = DeployClient
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


assert(DeployClient.CommonJobDialog, " extends class:DeployClient.CommonJobDialog is nil")
DeployClient.CreateProcessJobDialog = Lua.Class(DeployClient.CommonJobDialog, "DeployClient.CreateProcessJobDialog")

function DeployClient.CreateProcessJobDialog.__getter:type()
	return 6
end

function DeployClient.CreateProcessJobDialog:ShowDetail(detail)
	if detail ~= nil then
		self._dir.text = detail.createprocess_dir
		self._cmd.text = detail.createprocess_cmd
		self._param.text = detail.createprocess_param
	else
		self._dir.text = ""
		self._cmd.text = ""
		self._param.text = ""
	end
end

function DeployClient.CreateProcessJobDialog:GetDetail()
	local detail = {}
	detail.createprocess_dir = self._dir.text
	detail.createprocess_cmd = self._cmd.text
	detail.createprocess_param = self._param.text
	return detail
end

end