-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DeployClient == nil then _G.DeployClient = {} end
local DeployClient = DeployClient
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


assert(DeployClient.CommonJobDialog, " extends class:DeployClient.CommonJobDialog is nil")
DeployClient.DeepCopyJobDialog = Lua.Class(DeployClient.CommonJobDialog, "DeployClient.DeepCopyJobDialog")

function DeployClient.DeepCopyJobDialog.__getter:type()
	return 2
end

function DeployClient.DeepCopyJobDialog:ShowDetail(detail)
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

function DeployClient.DeepCopyJobDialog:GetDetail()
	local detail = {}
	detail.deepcopy_src = self._src_dir.text
	detail.deepcopy_dst = self._dst_dir.text
	detail.deepcopy_ext = self._ext.text
	return detail
end

end