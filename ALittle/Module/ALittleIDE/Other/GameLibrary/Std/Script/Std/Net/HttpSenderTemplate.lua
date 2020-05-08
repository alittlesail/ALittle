-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


IHttpSenderNative = Lua.Class(nil, "ALittle.IHttpSenderNative")

function IHttpSenderNative:GetID()
	return 0
end

function IHttpSenderNative:SetURL(url, content)
end

function IHttpSenderNative:Start()
end

function IHttpSenderNative:Stop()
end

function IHttpSenderNative:GetResponse()
	return nil
end

local __HttpSenderMap = {}
assert(ALittle.IHttpSender, " extends class:ALittle.IHttpSender is nil")
HttpSenderTemplate = Lua.Class(ALittle.IHttpSender, "ALittle.HttpSenderTemplate")

function HttpSenderTemplate:Ctor(ip, port)
	___rawset(self, "_interface", self.__class.__element[1]())
	___rawset(self, "_ip", ip)
	___rawset(self, "_port", port)
	if self._port == nil then
		___rawset(self, "_port", 80)
	end
end

function HttpSenderTemplate:SendRPC(thread, method, content)
	self._thread = thread
	__HttpSenderMap[self._interface:GetID()] = self
	local url = self._ip .. ":" .. self._port .. "/" .. method
	if String_Find(self._ip, "http://") ~= 1 and String_Find(self._ip, "https://") ~= 1 then
		if self._port == 443 then
			url = "https://" .. url
		else
			url = "http://" .. url
		end
	end
	if content == nil then
		self._interface:SetURL(url, nil)
	else
		self._interface:SetURL(url, String_JsonEncode(content))
	end
	self._interface:Start()
end

function HttpSenderTemplate:Stop()
	self._interface:Stop()
end

function HttpSenderTemplate:HandleSucceed()
	__HttpSenderMap[self._interface:GetID()] = nil
	local error, param = Lua.TCall(String_JsonDecode, self._interface:GetResponse())
	if error ~= nil then
		local result, reason = Coroutine.Resume(self._thread, error, nil)
		if result ~= true then
			Error(reason)
		end
		return
	end
	if param["error"] ~= nil then
		local result, reason = Coroutine.Resume(self._thread, param["error"], nil)
		if result ~= true then
			Error(reason)
		end
		return
	end
	local result, reason = Coroutine.Resume(self._thread, nil, param)
	if result ~= true then
		Error(reason)
	end
end

function HttpSenderTemplate:HandleFailed(reason)
	__HttpSenderMap[self._interface:GetID()] = nil
	local result, error = Coroutine.Resume(self._thread, reason, nil)
	if result ~= true then
		Error(error)
	end
end

function __ALITTLEAPI_HttpClientSucceed(id)
	local client = __HttpSenderMap[id]
	if client == nil then
		return
	end
	client:HandleSucceed()
end

function __ALITTLEAPI_HttpClientFailed(id, reason)
	local client = __HttpSenderMap[id]
	if client == nil then
		return
	end
	client:HandleFailed(reason)
end

