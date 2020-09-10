-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.Lua == nil then _G.Lua = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


local __LUAHTTPFILE_MAXID = 0
assert(ALittle.IHttpFileSenderNative, " extends class:ALittle.IHttpFileSenderNative is nil")
Lua.LuaHttpFileInterface = Lua.Class(ALittle.IHttpFileSenderNative, "Lua.LuaHttpFileInterface")

function Lua.LuaHttpFileInterface:Ctor()
	__LUAHTTPFILE_MAXID = __LUAHTTPFILE_MAXID + 1
	___rawset(self, "_id", __LUAHTTPFILE_MAXID)
end

function Lua.LuaHttpFileInterface:GetID()
	return self._id
end

function Lua.LuaHttpFileInterface:SetURL(url, file_path, download, start_size, array_buffer)
	self._url = url
	self._file_path = file_path
	self._download = download
end

function Lua.LuaHttpFileInterface:Start()
	if self._download then
		net.download(A_LuaSchedule._net, self._id, self._url, self._file_path)
	else
		net.upload(A_LuaSchedule._net, self._id, self._url, self._file_path)
	end
end

function Lua.LuaHttpFileInterface:Stop()
	if self._download then
		net.stopdownload(A_LuaSchedule._net, self._id)
	else
		net.stopupload(A_LuaSchedule._net, self._id)
	end
end

function Lua.LuaHttpFileInterface:GetPath()
	return self._file_path
end

end