-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleDeploy == nil then _G.ALittleDeploy = {} end
local ALittleDeploy = ALittleDeploy
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleDeploy.CommonJobDialog, " extends class:ALittleDeploy.CommonJobDialog is nil")
ALittleDeploy.WaitProcessExitJobDialog = Lua.Class(ALittleDeploy.CommonJobDialog, "ALittleDeploy.WaitProcessExitJobDialog")

function ALittleDeploy.WaitProcessExitJobDialog.__getter:type()
	return 5
end

function ALittleDeploy.WaitProcessExitJobDialog:ShowDetail(detail)
	if detail ~= nil then
		self._exe_path.text = ALittle.String_Join(detail.wait_p_exit_exe_path, "\n")
	else
		self._exe_path.text = ""
	end
end

function ALittleDeploy.WaitProcessExitJobDialog:GetDetail()
	local detail = {}
	detail.wait_p_exit_exe_path = ALittle.String_SplitSepList(self._exe_path.text, {"\r", "\n"})
	return detail
end

end