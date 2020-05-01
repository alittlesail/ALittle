-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.IHttpReceiverNative, " extends class:ALittle.IHttpReceiverNative is nil")
HttpReceiverNative = Lua.Class(ALittle.IHttpReceiverNative, "ALittle.HttpReceiverNative")

function HttpReceiverNative:Close(http_id)
	__CPPAPI_ServerSchedule:HttpClose(http_id)
end

function HttpReceiverNative:SendString(http_id, content)
	__CPPAPI_ServerSchedule:HttpSendString(http_id, content)
end

function HttpReceiverNative:SendFile(http_id, file_path, start_size)
	__CPPAPI_ServerSchedule:HttpSendFile(http_id, file_path, start_size)
end

local HttpReceiver = Lua.Template(HttpReceiverTemplate, "ALittle.HttpReceiverTemplate<ALittle.HttpReceiverNative>", HttpReceiverNative);
HttpSystem = Lua.Class(nil, "ALittle.HttpSystem")

function HttpSystem:Ctor()
	___rawset(self, "_request_map", {})
	___rawset(self, "_id_creator", SafeIDCreator())
end

function HttpSystem.HandleHttpTask(http_id, callback, value_map)
	local client = HttpReceiver(http_id)
	local error, result = Lua.TCall(callback, client, value_map)
	if error ~= nil then
		local map = {}
		map["error"] = error
		client:SendString(json.encode(map))
		return
	end
	if result == nil then
		local map = {}
		map["error"] = "接口没有返回任何内容"
		client:SendString(json.encode(map))
		return
	end
	client:SendString(json.encode(result))
end
HttpSystem.HandleHttpTask = Lua.CoWrap(HttpSystem.HandleHttpTask)

function HttpSystem.HandleHttpDownloadTask(http_id, callback, value_map)
	local client = HttpReceiver(http_id)
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
HttpSystem.HandleHttpDownloadTask = Lua.CoWrap(HttpSystem.HandleHttpDownloadTask)

function HttpSystem:Get(url)
local ___COROUTINE = coroutine.running()
	if ___COROUTINE == nil then
		return "当前不是协程", nil
	end
	local id = self._id_creator:CreateID()
	self._request_map[id] = ___COROUTINE
	__CPPAPI_ServerSchedule:HttpGet(id, url)
	return coroutine.yield()
end

function HttpSystem:PostJson(url, content)
local ___COROUTINE = coroutine.running()
	if ___COROUTINE == nil then
		return "当前不是协程", nil
	end
	local id = self._id_creator:CreateID()
	self._request_map[id] = ___COROUTINE
	__CPPAPI_ServerSchedule:HttpPost(id, url, "application/json", json.encode(content))
	return coroutine.yield()
end

function HttpSystem:HandleHttpSucceed(id, response)
	self._id_creator:ReleaseID(id)
	local thread = self._request_map[id]
	self._request_map[id] = nil
	local result, reason = coroutine.resume(thread, nil, response)
	if result ~= true then
		Error(reason)
	end
end

function HttpSystem:HandleHttpFailed(id, reason)
	self._id_creator:ReleaseID(id)
	local thread = self._request_map[id]
	self._request_map[id] = nil
	local result, reason = coroutine.resume(thread, reason, nil)
	if result ~= true then
		Error(reason)
	end
end

_G.A_HttpSystem = HttpSystem()
