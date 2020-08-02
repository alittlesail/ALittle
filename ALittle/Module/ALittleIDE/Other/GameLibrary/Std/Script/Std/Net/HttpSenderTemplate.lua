-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.IHttpSenderNative = Lua.Class(nil, "ALittle.IHttpSenderNative")

function ALittle.IHttpSenderNative:GetID()
	return 0
end

function ALittle.IHttpSenderNative:SetURL(url, content)
end

function ALittle.IHttpSenderNative:Start()
end

function ALittle.IHttpSenderNative:Stop()
end

function ALittle.IHttpSenderNative:GetResponse()
	return nil
end

local __HttpSenderMap = {}
assert(ALittle.IHttpSender, " extends class:ALittle.IHttpSender is nil")
ALittle.HttpSenderTemplate = Lua.Class(ALittle.IHttpSender, "ALittle.HttpSenderTemplate")

function ALittle.HttpSenderTemplate:Ctor(ip, port)
	___rawset(self, "_interface", self.__class.__element[1]())
	___rawset(self, "_ip", ip)
	___rawset(self, "_port", port)
	if self._port == nil then
		___rawset(self, "_port", 80)
	end
end

function ALittle.HttpSenderTemplate:SendRPC(thread, method, content)
	self._thread = thread
	__HttpSenderMap[self._interface:GetID()] = self
	local url = self._ip .. ":" .. self._port .. "/" .. method
	if ALittle.String_Find(self._ip, "http://") ~= 1 and ALittle.String_Find(self._ip, "https://") ~= 1 then
		if self._port == 443 then
			url = "https://" .. url
		else
			url = "http://" .. url
		end
	end
	if content == nil then
		self._interface:SetURL(url, nil)
	else
		self._interface:SetURL(url, ALittle.String_JsonEncode(content))
	end
	self._interface:Start()
end

function ALittle.HttpSenderTemplate:Stop()
	self._interface:Stop()
end

function ALittle.HttpSenderTemplate:HandleSucceed()
	__HttpSenderMap[self._interface:GetID()] = nil
	local error, param = Lua.TCall(ALittle.String_JsonDecode, self._interface:GetResponse())
	if error ~= nil then
		local result, reason = ALittle.Coroutine.Resume(self._thread, error, nil)
		if result ~= true then
			ALittle.Error(reason)
		end
		return
	end
	if param["error"] ~= nil then
		local result, reason = ALittle.Coroutine.Resume(self._thread, param["error"], nil)
		if result ~= true then
			ALittle.Error(reason)
		end
		return
	end
	local result, reason = ALittle.Coroutine.Resume(self._thread, nil, param)
	if result ~= true then
		ALittle.Error(reason)
	end
end

function ALittle.HttpSenderTemplate:HandleFailed(reason)
	__HttpSenderMap[self._interface:GetID()] = nil
	local result, error = ALittle.Coroutine.Resume(self._thread, reason, nil)
	if result ~= true then
		ALittle.Error(error)
	end
end

function ALittle.__ALITTLEAPI_HttpClientSucceed(id)
	local client = __HttpSenderMap[id]
	if client == nil then
		return
	end
	client:HandleSucceed()
end

function ALittle.__ALITTLEAPI_HttpClientFailed(id, reason)
	local client = __HttpSenderMap[id]
	if client == nil then
		return
	end
	client:HandleFailed(reason)
end

end