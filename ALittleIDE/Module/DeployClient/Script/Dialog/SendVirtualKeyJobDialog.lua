-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DeployClient == nil then _G.DeployClient = {} end
local DeployClient = DeployClient
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


assert(DeployClient.CommonJobDialog, " extends class:DeployClient.CommonJobDialog is nil")
DeployClient.SendVirtualKeyJobDialog = Lua.Class(DeployClient.CommonJobDialog, "DeployClient.SendVirtualKeyJobDialog")

function DeployClient.SendVirtualKeyJobDialog.__getter:type()
	return 4
end

function DeployClient.SendVirtualKeyJobDialog:ShowDetail(detail)
	if detail ~= nil then
		self._exe_path.text = detail.virtualkey_exepath
		self._cmd_list.text = ALittle.String_Join(detail.virtualkey_cmd, "\n")
	else
		self._exe_path.text = ""
		self._cmd_list.text = ""
	end
end

function DeployClient.SendVirtualKeyJobDialog:GetDetail()
	local detail = {}
	detail.virtualkey_exepath = self._exe_path.text
	detail.virtualkey_cmd = ALittle.String_SplitSepList(self._cmd_list.text, {"\r", "\n"})
	return detail
end

end