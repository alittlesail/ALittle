-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.DeployClient == nil then _G.DeployClient = {} end
local DeployClient = DeployClient
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


assert(DeployClient.CommonJobDialog, " extends class:DeployClient.CommonJobDialog is nil")
DeployClient.CopyFileJobDialog = Lua.Class(DeployClient.CommonJobDialog, "DeployClient.CopyFileJobDialog")

function DeployClient.CopyFileJobDialog.__getter:type()
	return 3
end

function DeployClient.CopyFileJobDialog:ShowDetail(detail)
	if detail ~= nil then
		self._src_dir.text = detail.copyfile_src
		self._dst_dir.text = detail.copyfile_dst
		self._file_list.text = ALittle.String_Join(detail.copyfile_file, "\n")
	else
		self._src_dir.text = ""
		self._dst_dir.text = ""
		self._file_list.text = ""
	end
end

function DeployClient.CopyFileJobDialog:GetDetail()
	local detail = {}
	detail.copyfile_src = self._src_dir.text
	detail.copyfile_dst = self._dst_dir.text
	detail.copyfile_file = ALittle.String_SplitSepList(self._file_list.text, {"\r", "\n"})
	return detail
end

end