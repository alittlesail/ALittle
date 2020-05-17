-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


assert(Lua.ISocket, " extends class:Lua.ISocket is nil")
PluginSocket = Lua.Class(Lua.ISocket, "Emulator.PluginSocket")

function PluginSocket:ReadMessage()
	local ___COROUTINE = coroutine.running()
	local func = _G["__SOCKET_ReadMessage"]
	if func == nil then
		return "can't find __SOCKET_ReadMessage", nil
	end
	local call_error, error, msg = Lua.TCall(func, self)
	if call_error ~= nil then
		return call_error, nil
	end
	return error, msg
end

function PluginSocket:WriteMessage(full_name, protobuf_msg)
	local func = _G["__SOCKET_WriteMessage"]
	if func == nil then
		return "can't find __SOCKET_WriteMessage"
	end
	local call_error, error = Lua.TCall(func, self, full_name, protobuf_msg)
	if call_error ~= nil then
		return call_error
	end
	if error ~= nil then
		return error
	end
	g_GCenter:AddLogMessage(protobuf_msg)
	return nil
end

function PluginSocket:HandleMessage(msg)
	g_GCenter:AddLogMessage(msg)
	local func = _G["__SOCKET_HandleMessage"]
	if func == nil then
		return
	end
	local error = Lua.TCall(func, self, msg)
end

