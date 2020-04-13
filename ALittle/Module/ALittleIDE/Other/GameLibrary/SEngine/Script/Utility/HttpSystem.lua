
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine


assert(IHttpReceiverNative, " extends class:IHttpReceiverNative is nil")
HttpReceiverNative = Class(IHttpReceiverNative, "ALittle.HttpReceiverNative")

function HttpReceiverNative:Close(http_id)
	__CPPAPI_ServerSchedule:HttpClose(http_id)
end

function HttpReceiverNative:SendString(http_id, content)
	__CPPAPI_ServerSchedule:HttpSendString(http_id, content)
end

function HttpReceiverNative:SendFile(http_id, file_path, start_size)
	__CPPAPI_ServerSchedule:HttpSendFile(http_id, file_path, start_size)
end

local HttpReceiver = Template(HttpReceiverTemplate, "ALittle.HttpReceiverTemplate<ALittle.HttpReceiverNative>", HttpReceiverNative);
HttpSystem = Class(nil, "ALittle.HttpSystem")

function HttpSystem:Ctor()
	___rawset(self, "_request_map", {})
	___rawset(self, "_id_creator", SafeIDCreator())
end

function HttpSystem:Get(url)
	local co = coroutine.running()
	if co == nil then
		return "当前不是协程", nil
	end
	local id = self._id_creator:CreateID()
	self._request_map[id] = co
	__CPPAPI_ServerSchedule:HttpGet(id, url)
	return ___coroutine.yield()
end

function HttpSystem:PostJson(url, content)
	local co = coroutine.running()
	if co == nil then
		return "当前不是协程", nil
	end
	local id = self._id_creator:CreateID()
	self._request_map[id] = co
	__CPPAPI_ServerSchedule:HttpPost(id, url, "application/json", json.encode(content))
	return ___coroutine.yield()
end

function HttpSystem:HandleHttpSucceed(id, response)
	self._id_creator:ReleaseID(id)
	local co = self._request_map[id]
	self._request_map[id] = nil
	local result, reason = coroutine.resume(co, nil, response)
	if result ~= true then
		Error(reason)
	end
end

function HttpSystem:HandleHttpFailed(id, reason)
	self._id_creator:ReleaseID(id)
	local co = self._request_map[id]
	self._request_map[id] = nil
	local result, reason = coroutine.resume(co, reason, nil)
	if result ~= true then
		Error(reason)
	end
end

function HttpSystem.HandleHttpTask(http_id, callback, value_map)
	local client = HttpReceiver(http_id)
	local error, result = TCall(callback, client, value_map)
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
HttpSystem.HandleHttpTask = CoWrap(HttpSystem.HandleHttpTask)

function HttpSystem.HandleHttpDownloadTask(http_id, callback, value_map)
	local client = HttpReceiver(http_id)
	local error, file_path, start_size = TCall(callback, client, value_map)
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
HttpSystem.HandleHttpDownloadTask = CoWrap(HttpSystem.HandleHttpDownloadTask)

_G.A_HttpSystem = HttpSystem()
