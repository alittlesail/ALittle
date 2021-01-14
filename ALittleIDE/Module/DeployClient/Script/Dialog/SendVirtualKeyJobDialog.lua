-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleDeploy == nil then _G.ALittleDeploy = {} end
local ALittleDeploy = ALittleDeploy
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleDeploy.CommonJobDialog, " extends class:ALittleDeploy.CommonJobDialog is nil")
ALittleDeploy.SendVirtualKeyJobDialog = Lua.Class(ALittleDeploy.CommonJobDialog, "ALittleDeploy.SendVirtualKeyJobDialog")

function ALittleDeploy.SendVirtualKeyJobDialog.__getter:type()
	return 4
end

function ALittleDeploy.SendVirtualKeyJobDialog:ShowDetail(detail)
	if detail ~= nil then
		self._exe_path.text = detail.virtualkey_exepath
		self._cmd_list.text = ALittle.String_Join(detail.virtualkey_cmd, "\n")
	else
		self._exe_path.text = ""
		self._cmd_list.text = ""
	end
end

function ALittleDeploy.SendVirtualKeyJobDialog:GetDetail()
	local detail = {}
	detail.virtualkey_exepath = self._exe_path.text
	detail.virtualkey_cmd = ALittle.String_SplitSepList(self._cmd_list.text, {"\r", "\n"})
	return detail
end

end