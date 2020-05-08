-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


IHttpReceiverNative = Lua.Class(nil, "ALittle.IHttpReceiverNative")

function IHttpReceiverNative:Close(http_id)
end

function IHttpReceiverNative:SendString(http_id, content)
end

function IHttpReceiverNative:SendFile(http_id, file_path, start_size)
end

assert(ALittle.IHttpReceiver, " extends class:ALittle.IHttpReceiver is nil")
HttpReceiverTemplate = Lua.Class(ALittle.IHttpReceiver, "ALittle.HttpReceiverTemplate")

function HttpReceiverTemplate:Ctor(http_id)
	___rawset(self, "_http_id", http_id)
	___rawset(self, "_interface", self.__class.__element[1]())
end

function HttpReceiverTemplate:Close()
	self._interface:Close(self._http_id)
end

function HttpReceiverTemplate:SendString(content)
	self._interface:SendString(self._http_id, content)
end

function HttpReceiverTemplate:SendFile(file_path, start_size)
	self._interface:SendFile(self._http_id, file_path, start_size)
end

