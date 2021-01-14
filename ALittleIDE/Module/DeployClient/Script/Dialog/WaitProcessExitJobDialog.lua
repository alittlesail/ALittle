-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DeployClient == nil then _G.DeployClient = {} end
local DeployClient = DeployClient
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


assert(DeployClient.CommonJobDialog, " extends class:DeployClient.CommonJobDialog is nil")
DeployClient.WaitProcessExitJobDialog = Lua.Class(DeployClient.CommonJobDialog, "DeployClient.WaitProcessExitJobDialog")

function DeployClient.WaitProcessExitJobDialog.__getter:type()
	return 5
end

function DeployClient.WaitProcessExitJobDialog:ShowDetail(detail)
	if detail ~= nil then
		self._exe_path.text = ALittle.String_Join(detail.wait_p_exit_exe_path, "\n")
		self._max_time.text = detail.wait_p_exit_max_time
	else
		self._exe_path.text = ""
		self._max_time.text = ""
	end
end

function DeployClient.WaitProcessExitJobDialog:GetDetail()
	local detail = {}
	detail.wait_p_exit_exe_path = ALittle.String_SplitSepList(self._exe_path.text, {"\r", "\n"})
	detail.wait_p_exit_max_time = ALittle.Math_ToIntOrZero(self._max_time.text)
	return detail
end

end