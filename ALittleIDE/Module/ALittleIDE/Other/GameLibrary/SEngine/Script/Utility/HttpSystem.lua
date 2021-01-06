-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.IHttpReceiverNative, " extends class:ALittle.IHttpReceiverNative is nil")
ALittle.HttpReceiverNative = Lua.Class(ALittle.IHttpReceiverNative, "ALittle.HttpReceiverNative")

function ALittle.HttpReceiverNative:Close(http_id)
	__CPPAPI_ServerSchedule:HttpClose(http_id)
end

function ALittle.HttpReceiverNative:SendString(http_id, content)
	__CPPAPI_ServerSchedule:HttpSendString(http_id, content)
end

function ALittle.HttpReceiverNative:SendFile(http_id, file_path, start_size)
	__CPPAPI_ServerSchedule:HttpSendFile(http_id, file_path, start_size)
end

local HttpReceiver = Lua.Template(ALittle.HttpReceiverTemplate, "ALittle.HttpReceiverTemplate<ALittle.HttpReceiverNative>", ALittle.HttpReceiverNative);
ALittle.HttpSystem = Lua.Class(nil, "ALittle.HttpSystem")

function ALittle.HttpSystem:Ctor()
	___rawset(self, "_request_map", {})
	___rawset(self, "_id_creator", ALittle.SafeIDCreator())
end

function ALittle.HttpSystem.HandleHttpTask(method, http_id, callback, value_map)
	local client = HttpReceiver(method, http_id)
	local error, result = Lua.TCall(callback, client, value_map)
	if error ~= nil then
		local map = {}
		map["error"] = error
		client:SendString(ALittle.String_JsonEncode(map))
		return
	end
	if result == nil then
		local map = {}
		map["error"] = "接口没有返回任何内容"
		client:SendString(ALittle.String_JsonEncode(map))
		return
	end
	client:SendString(ALittle.String_JsonEncode(result))
end
ALittle.HttpSystem.HandleHttpTask = Lua.CoWrap(ALittle.HttpSystem.HandleHttpTask)

function ALittle.HttpSystem.HandleHttpDownloadTask(method, http_id, callback, value_map)
	local client = HttpReceiver(method, http_id)
	local error, file_path, start_size = Lua.TCall(callback, client, value_map)
	if error ~= nil then
		client:Close()
		return
	end
	if file_path == nil then
		client:Close()
		return
	end
	client:SendFile(file_path, start_size)
end
ALittle.HttpSystem.HandleHttpDownloadTask = Lua.CoWrap(ALittle.HttpSystem.HandleHttpDownloadTask)

function ALittle.HttpSystem:Get(url)
	local ___COROUTINE = coroutine.running()
	if ___COROUTINE == nil then
		return "当前不是协程", nil
	end
	local id = self._id_creator:CreateID()
	self._request_map[id] = ___COROUTINE
	__CPPAPI_ServerSchedule:HttpGet(id, url)
	return coroutine.yield()
end

function ALittle.HttpSystem:PostJson(url, content)
	local ___COROUTINE = coroutine.running()
	if ___COROUTINE == nil then
		return "当前不是协程", nil
	end
	local id = self._id_creator:CreateID()
	self._request_map[id] = ___COROUTINE
	__CPPAPI_ServerSchedule:HttpPost(id, url, "application/json", ALittle.String_JsonEncode(content))
	return coroutine.yield()
end

function ALittle.HttpSystem:HandleHttpSucceed(id, response)
	self._id_creator:ReleaseID(id)
	local thread = self._request_map[id]
	self._request_map[id] = nil
	local result, reason = coroutine.resume(thread, nil, response)
	if result ~= true then
		ALittle.Error(reason)
	end
end

function ALittle.HttpSystem:HandleHttpFailed(id, reason)
	self._id_creator:ReleaseID(id)
	local thread = self._request_map[id]
	self._request_map[id] = nil
	local result, error = coroutine.resume(thread, reason, nil)
	if result ~= true then
		ALittle.Error(error)
	end
end

_G.A_HttpSystem = ALittle.HttpSystem()
end