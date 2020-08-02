-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.IHttpFileReceiverNative = Lua.Class(nil, "ALittle.IHttpFileReceiverNative")

function ALittle.IHttpFileReceiverNative:Close(http_id)
end

function ALittle.IHttpFileReceiverNative:SendString(http_id, content)
end

function ALittle.IHttpFileReceiverNative:StartReceiveFile(http_id, file_path, start_size)
end

assert(ALittle.IHttpFileReceiver, " extends class:ALittle.IHttpFileReceiver is nil")
ALittle.HttpFileReceiverTemplate = Lua.Class(ALittle.IHttpFileReceiver, "ALittle.HttpFileReceiverTemplate")

function ALittle.HttpFileReceiverTemplate:Ctor(http_id, thread)
	___rawset(self, "_http_id", http_id)
	___rawset(self, "_thread", thread)
	___rawset(self, "_received", false)
	___rawset(self, "_interface", self.__class.__element[1]())
end

function ALittle.HttpFileReceiverTemplate:StartReceiveFile(file_path, start_size)
	local ___COROUTINE = coroutine.running()
	if self._received then
		return "StartReceiveFile已经被调用过"
	end
	self._received = true
	self._interface:StartReceiveFile(self._http_id, file_path, start_size)
	return coroutine.yield()
end

function ALittle.HttpFileReceiverTemplate:HandleReceiveResult(reason)
	local result, error = ALittle.Coroutine.Resume(self._thread, reason)
	if not result then
		ALittle.Error(error)
	end
end

function ALittle.HttpFileReceiverTemplate.__getter:received()
	return self._received
end

function ALittle.HttpFileReceiverTemplate:SendString(content)
	self._interface:SendString(self._http_id, content)
end

function ALittle.HttpFileReceiverTemplate:Clsoe()
	self._interface:Close(self._http_id)
end

end