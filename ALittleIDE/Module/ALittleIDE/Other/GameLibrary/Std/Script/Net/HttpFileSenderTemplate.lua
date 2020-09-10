-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.IHttpFileSenderNative = Lua.Class(nil, "ALittle.IHttpFileSenderNative")

function ALittle.IHttpFileSenderNative:GetID()
	return 0
end

function ALittle.IHttpFileSenderNative:SetURL(url, file_path, download, start_size, array_buffer)
end

function ALittle.IHttpFileSenderNative:Start()
end

function ALittle.IHttpFileSenderNative:Stop()
end

function ALittle.IHttpFileSenderNative:GetPath()
	return ""
end

local __HttpFileSenderMap = {}
assert(ALittle.IHttpFileSender, " extends class:ALittle.IHttpFileSender is nil")
ALittle.HttpFileSenderTemplate = Lua.Class(ALittle.IHttpFileSender, "ALittle.HttpFileSenderTemplate")

function ALittle.HttpFileSenderTemplate:Ctor(ip, port, file_path, start_size, callback)
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

function ALittle.HttpFileSenderTemplate:SendDownloadRPC(thread, method, content, array_buffer)
	self._thread = thread
	__HttpFileSenderMap[self._interface:GetID()] = self
	if self._start_size == nil then
		self._start_size = 0
	end
	local url = self._ip .. ":" .. self._port .. "/" .. method
	if ALittle.String_Find(self._ip, "http://") ~= 1 and ALittle.String_Find(self._ip, "https://") ~= 1 then
		if self._port == 443 then
			url = "https://" .. url
		else
			url = "http://" .. url
		end
	end
	self._interface:SetURL(self:HttpUrlAppendParamMap(url, content), self._file_path, true, self._start_size, array_buffer)
	self._interface:Start()
end

function ALittle.HttpFileSenderTemplate:SendUploadRPC(thread, method, content, array_buffer)
	self._thread = thread
	__HttpFileSenderMap[self._interface:GetID()] = self
	if self._start_size == nil then
		self._start_size = 0
	end
	local url = "http://" .. self._ip .. ":" .. self._port .. "/" .. method
	self._interface:SetURL(self:HttpUrlAppendParamMap(url, content), self._file_path, false, self._start_size, array_buffer)
	self._interface:Start()
end

function ALittle.HttpFileSenderTemplate:Stop()
	self._interface:Stop()
end

function ALittle.HttpFileSenderTemplate:GetFilePath()
	return self._file_path
end

function ALittle.HttpFileSenderTemplate:GetTotalSize()
	return self._total_size
end

function ALittle.HttpFileSenderTemplate:GetCurSize()
	return self._cur_size
end

function ALittle.HttpFileSenderTemplate:HandleSucceed()
	__HttpFileSenderMap[self._interface:GetID()] = nil
	local result, reason = ALittle.Coroutine.Resume(self._thread, nil)
	if result ~= true then
		ALittle.Error(reason)
	end
end

function ALittle.HttpFileSenderTemplate:HandleFailed(reason)
	__HttpFileSenderMap[self._interface:GetID()] = nil
	local result, error = ALittle.Coroutine.Resume(self._thread, reason)
	if result ~= true then
		ALittle.Error(error)
	end
end

function ALittle.HttpFileSenderTemplate:HandleProcess(cur_size, total_size)
	self._cur_size = cur_size
	self._total_size = total_size
	if self._callback ~= nil then
		self._callback(self)
	end
end

function ALittle.HttpFileSenderTemplate:HttpUrlAppendParamMap(url, param)
	if param == nil then
		return url
	end
	local list = {}
	local count = 0
	for key, value in ___pairs(param) do
		count = count + 1
		list[count] = key .. "=" .. ALittle.String_ToString(value)
	end
	if ALittle.String_Find(url, "?") == nil then
		url = url .. "?"
	else
		url = url .. "&"
	end
	return url .. ALittle.String_Join(list, "&")
end

function ALittle.__ALITTLEAPI_HttpFileSucceed(id)
	local client = __HttpFileSenderMap[id]
	if client == nil then
		return
	end
	client:HandleSucceed()
end

function ALittle.__ALITTLEAPI_HttpFileFailed(id, reason)
	local client = __HttpFileSenderMap[id]
	if client == nil then
		return
	end
	client:HandleFailed(reason)
end

function ALittle.__ALITTLEAPI_HttpFileProcess(id, cur_size, total_size)
	local client = __HttpFileSenderMap[id]
	if client == nil then
		return
	end
	client:HandleProcess(cur_size, total_size)
end

function ALittle.DownloadFile(ip, port, method, file_path, array_buffer)
	local ___COROUTINE = coroutine.running()
	local sender
	sender = Lua.Template(ALittle.HttpFileSenderTemplate, "ALittle.HttpFileSenderTemplate<Lua.LuaHttpFileInterface>", Lua.LuaHttpFileInterface)(ip, port, file_path, 0)
	return ALittle.IHttpFileSender.InvokeDownload(method, sender, nil, array_buffer)
end

function ALittle.UploadFile(ip, port, method, file_path, array_buffer)
	local ___COROUTINE = coroutine.running()
	local sender
	sender = Lua.Template(ALittle.HttpFileSenderTemplate, "ALittle.HttpFileSenderTemplate<Lua.LuaHttpFileInterface>", Lua.LuaHttpFileInterface)(ip, port, file_path, 0)
	local error = ALittle.IHttpFileSender.InvokeUpload(method, sender, nil, array_buffer)
	return error
end

end