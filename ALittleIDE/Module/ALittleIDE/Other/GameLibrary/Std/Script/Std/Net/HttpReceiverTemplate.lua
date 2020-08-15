-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.IHttpReceiverNative = Lua.Class(nil, "ALittle.IHttpReceiverNative")

function ALittle.IHttpReceiverNative:Close(http_id)
end

function ALittle.IHttpReceiverNative:SendString(http_id, content)
end

function ALittle.IHttpReceiverNative:SendFile(http_id, file_path, start_size)
end

assert(ALittle.IHttpReceiver, " extends class:ALittle.IHttpReceiver is nil")
ALittle.HttpReceiverTemplate = Lua.Class(ALittle.IHttpReceiver, "ALittle.HttpReceiverTemplate")

function ALittle.HttpReceiverTemplate:Ctor(http_id)
	___rawset(self, "_http_id", http_id)
	___rawset(self, "_interface", self.__class.__element[1]())
end

function ALittle.HttpReceiverTemplate:Close()
	self._interface:Close(self._http_id)
end

function ALittle.HttpReceiverTemplate:SendString(content)
	self._interface:SendString(self._http_id, content)
end

function ALittle.HttpReceiverTemplate:SendFile(file_path, start_size)
	self._interface:SendFile(self._http_id, file_path, start_size)
end

end