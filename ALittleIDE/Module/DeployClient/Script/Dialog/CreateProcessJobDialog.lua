-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleDeploy == nil then _G.ALittleDeploy = {} end
local ALittleDeploy = ALittleDeploy
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleDeploy.CommonJobDialog, " extends class:ALittleDeploy.CommonJobDialog is nil")
ALittleDeploy.CreateProcessJobDialog = Lua.Class(ALittleDeploy.CommonJobDialog, "ALittleDeploy.CreateProcessJobDialog")

function ALittleDeploy.CreateProcessJobDialog.__getter:type()
	return 6
end

function ALittleDeploy.CreateProcessJobDialog:ShowDetail(detail)
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

function ALittleDeploy.CreateProcessJobDialog:GetDetail()
	local detail = {}
	detail.createprocess_dir = self._dir.text
	detail.createprocess_cmd = self._cmd.text
	detail.createprocess_param = self._param.text
	return detail
end

end