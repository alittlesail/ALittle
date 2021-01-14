-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleDeploy == nil then _G.ALittleDeploy = {} end
local ALittleDeploy = ALittleDeploy
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittleDeploy.CommonJobDialog, " extends class:ALittleDeploy.CommonJobDialog is nil")
ALittleDeploy.DeepCopyJobDialog = Lua.Class(ALittleDeploy.CommonJobDialog, "ALittleDeploy.DeepCopyJobDialog")

function ALittleDeploy.DeepCopyJobDialog.__getter:type()
	return 2
end

function ALittleDeploy.DeepCopyJobDialog:ShowDetail(detail)
	if detail ~= nil then
		self._src_dir.text = detail.deepcopy_src
		self._dst_dir.text = detail.deepcopy_dst
		self._ext.text = detail.deepcopy_ext
	else
		self._src_dir.text = ""
		self._dst_dir.text = ""
		self._ext.text = ""
	end
end

function ALittleDeploy.DeepCopyJobDialog:GetDetail()
	local detail = {}
	detail.deepcopy_src = self._src_dir.text
	detail.deepcopy_dst = self._dst_dir.text
	detail.deepcopy_ext = self._ext.text
	return detail
end

end