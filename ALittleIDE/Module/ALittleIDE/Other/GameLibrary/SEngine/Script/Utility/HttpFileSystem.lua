-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.IHttpFileReceiverNative, " extends class:ALittle.IHttpFileReceiverNative is nil")
ALittle.HttpFileReceiverNative = Lua.Class(ALittle.IHttpFileReceiverNative, "ALittle.HttpFileReceiverNative")

function ALittle.HttpFileReceiverNative:Close(http_id)
	__CPPAPI_ServerSchedule:HttpClose(http_id)
end

function ALittle.HttpFileReceiverNative:SendString(http_id, content)
	__CPPAPI_ServerSchedule:HttpSendString(http_id, content)
end

function ALittle.HttpFileReceiverNative:StartReceiveFile(http_id, file_path, start_size)
	__CPPAPI_ServerSchedule:HttpStartReceiveFile(http_id, file_path, start_size)
end

local HttpFileReceiver = Lua.Template(ALittle.HttpFileReceiverTemplate, "ALittle.HttpFileReceiverTemplate<ALittle.HttpFileReceiverNative>", ALittle.HttpFileReceiverNative);
ALittle.HttpFileSystem = Lua.Class(nil, "ALittle.HttpFileSystem")

function ALittle.HttpFileSystem:Ctor()
	___rawset(self, "_http_file_map", {})
end

function ALittle.HttpFileSystem:HandleHttpFileTask(http_id, path, callback, value_map)
	self:HandleHttpFileTaskImpl(http_id, path, callback, value_map)
end
ALittle.HttpFileSystem.HandleHttpFileTask = Lua.CoWrap(ALittle.HttpFileSystem.HandleHttpFileTask)

function ALittle.HttpFileSystem:HandleHttpFileTaskImpl(http_id, path, callback, value_map)
	local ___COROUTINE = coroutine.running()
	local file_client = HttpFileReceiver(http_id, ___COROUTINE)
	self._http_file_map[http_id] = file_client
	local error = nil
	local result = nil
	if callback == nil then
		error = file_client:StartReceiveFile("", 0)
	else
		error, result = Lua.TCall(callback, file_client, value_map)
	end
	if not file_client.received then
		error = file_client:StartReceiveFile("", 0)
	end
	self._http_file_map[http_id] = nil
	if error ~= nil then
		local map = {}
		map["error"] = error
		file_client:SendString(ALittle.String_JsonEncode(map))
		return
	end
	if result == nil then
		local map = {}
		map["error"] = "接口没有返回任何内容"
		file_client:SendString(ALittle.String_JsonEncode(map))
		return
	end
	file_client:SendString(ALittle.String_JsonEncode(result))
end

function ALittle.HttpFileSystem:HandleHttpFileCompletedTask(http_id, reason)
	local file_client = self._http_file_map[http_id]
	if file_client == nil then
		__CPPAPI_ServerSchedule:HttpClose(http_id)
		return
	end
	file_client:HandleReceiveResult(reason)
end

_G.A_HttpFileSystem = ALittle.HttpFileSystem()
end