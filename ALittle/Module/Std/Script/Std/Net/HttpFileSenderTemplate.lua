-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


IHttpFileSenderNative = Lua.Class(nil, "ALittle.IHttpFileSenderNative")

function IHttpFileSenderNative:GetID()
	return 0
end

function IHttpFileSenderNative:SetURL(url, file_path, download, start_size)
end

function IHttpFileSenderNative:Start()
end

function IHttpFileSenderNative:Stop()
end

function IHttpFileSenderNative:GetPath()
	return ""
end

local __HttpFileSenderMap = {}
assert(ALittle.IHttpFileSender, " extends class:ALittle.IHttpFileSender is nil")
HttpFileSenderTemplate = Lua.Class(ALittle.IHttpFileSender, "ALittle.HttpFileSenderTemplate")

function HttpFileSenderTemplate:Ctor(ip, port, file_path, start_size, callback)
	___rawset(self, "_interface", self.__class.__element[1]())
	___rawset(self, "_ip", ip)
	___rawset(self, "_port", port)
	if self._port == nil then
		___rawset(self, "_port", 80)
	end
	___rawset(self, "_file_path", file_path)
	___rawset(self, "_start_size", start_size)
	___rawset(self, "_callback", callback)
	___rawset(self, "_cur_size", 0)
	___rawset(self, "_total_size", 0)
end

function HttpFileSenderTemplate:SendDownloadRPC(thread, method, content)
	self._thread = thread
	__HttpFileSenderMap[self._interface:GetID()] = self
	if self._start_size == nil then
		self._start_size = 0
	end
	local url = self._ip .. ":" .. self._port .. "/" .. method
	if String_Find(self._ip, "http://") ~= 1 and String_Find(self._ip, "https://") ~= 1 then
		if self._port == 443 then
			url = "https://" .. url
		else
			url = "http://" .. url
		end
	end
	self._interface:SetURL(self:HttpUrlAppendParamMap(url, content), self._file_path, true, self._start_size)
	self._interface:Start()
end

function HttpFileSenderTemplate:SendUploadRPC(thread, method, content)
	self._thread = thread
	__HttpFileSenderMap[self._interface:GetID()] = self
	if self._start_size == nil then
		self._start_size = 0
	end
	local url = "http://" .. self._ip .. ":" .. self._port .. "/" .. method
	self._interface:SetURL(self:HttpUrlAppendParamMap(url, content), self._file_path, false, self._start_size)
	self._interface:Start()
end

function HttpFileSenderTemplate:Stop()
	self._interface:Stop()
end

function HttpFileSenderTemplate:GetFilePath()
	return self._file_path
end

function HttpFileSenderTemplate:GetTotalSize()
	return self._total_size
end

function HttpFileSenderTemplate:GetCurSize()
	return self._cur_size
end

function HttpFileSenderTemplate:HandleSucceed()
	__HttpFileSenderMap[self._interface:GetID()] = nil
	local result, reason = Coroutine.Resume(self._thread, nil)
	if result ~= true then
		Error(reason)
	end
end

function HttpFileSenderTemplate:HandleFailed(reason)
	__HttpFileSenderMap[self._interface:GetID()] = nil
	local result, error = Coroutine.Resume(self._thread, reason)
	if result ~= true then
		Error(error)
	end
end

function HttpFileSenderTemplate:HandleProcess(cur_size, total_size)
	self._cur_size = cur_size
	self._total_size = total_size
	if self._callback ~= nil then
		self._callback(self)
	end
end

function HttpFileSenderTemplate:HttpUrlAppendParamMap(url, param)
	if param == nil then
		return url
	end
	local list = {}
	local count = 0
	for key, value in ___pairs(param) do
		count = count + 1
		list[count] = key .. "=" .. String_ToString(value)
	end
	if String_Find(url, "?") == nil then
		url = url .. "?"
	else
		url = url .. "&"
	end
	return url .. String_Join(list, "&")
end

function __ALITTLEAPI_HttpFileSucceed(id)
	local client = __HttpFileSenderMap[id]
	if client == nil then
		return
	end
	client:HandleSucceed()
end

function __ALITTLEAPI_HttpFileFailed(id, reason)
	local client = __HttpFileSenderMap[id]
	if client == nil then
		return
	end
	client:HandleFailed(reason)
end

function __ALITTLEAPI_HttpFileProcess(id, cur_size, total_size)
	local client = __HttpFileSenderMap[id]
	if client == nil then
		return
	end
	client:HandleProcess(cur_size, total_size)
end

function DownloadFile(ip, port, method, file_path)
local ___COROUTINE = coroutine.running()
	local sender
	sender = Lua.Template(HttpFileSenderTemplate, "ALittle.HttpFileSenderTemplate<Lua.LuaHttpFileInterface>", Lua.LuaHttpFileInterface)(ip, port, file_path, 0)
	return IHttpFileSender.InvokeDownload(method, sender, nil)
end

function UploadFile(ip, port, method, file_path)
local ___COROUTINE = coroutine.running()
	local sender
	sender = Lua.Template(HttpFileSenderTemplate, "ALittle.HttpFileSenderTemplate<Lua.LuaHttpFileInterface>", Lua.LuaHttpFileInterface)(ip, port, file_path, 0)
	local error = IHttpFileSender.InvokeUpload(method, sender, nil)
	return error
end

