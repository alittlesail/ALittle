
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine


assert(IHttpFileReceiverNative, " extends class:IHttpFileReceiverNative is nil")
HttpFileReceiverNative = Class(IHttpFileReceiverNative, "ALittle.HttpFileReceiverNative")

function HttpFileReceiverNative:Close(http_id)
	__CPPAPI_ServerSchedule:HttpClose(http_id)
end

function HttpFileReceiverNative:SendString(http_id, content)
	__CPPAPI_ServerSchedule:HttpSendString(http_id, content)
end

function HttpFileReceiverNative:StartReceiveFile(http_id, file_path, start_size)
	__CPPAPI_ServerSchedule:HttpStartReceiveFile(http_id, file_path, start_size)
end

local HttpFileReceiver = Template(HttpFileReceiverTemplate, "ALittle.HttpFileReceiverTemplate<ALittle.HttpFileReceiverNative>", HttpFileReceiverNative);
HttpFileSystem = Class(nil, "ALittle.HttpFileSystem")

function HttpFileSystem:Ctor()
	___rawset(self, "_http_file_map", {})
end

function HttpFileSystem:HandleHttpFileTask(http_id, path, callback, value_map)
	local file_client = HttpFileReceiver(http_id, coroutine.running())
	self._http_file_map[http_id] = file_client
	local error = nil
	local result = nil
	if callback == nil then
		error = file_client:StartReceiveFile("", 0)
	else
		error, result = TCall(callback, file_client, value_map)
	end
	if not file_client.received then
		error = file_client:StartReceiveFile("", 0)
	end
	self._http_file_map[http_id] = nil
	if error ~= nil then
		local map = {}
		map["error"] = error
		file_client:SendString(json.encode(map))
		return
	end
	if result == nil then
		local map = {}
		map["error"] = "接口没有返回任何内容"
		file_client:SendString(json.encode(map))
		return
	end
	file_client:SendString(json.encode(result))
end
HttpFileSystem.HandleHttpFileTask = CoWrap(HttpFileSystem.HandleHttpFileTask)

function HttpFileSystem:HandleHttpFileCompletedTask(http_id, reason)
	local file_client = self._http_file_map[http_id]
	if file_client == nil then
		__CPPAPI_ServerSchedule:HttpClose(http_id)
		return
	end
	file_client:HandleReceiveResult(reason)
end

_G.A_HttpFileSystem = HttpFileSystem()
