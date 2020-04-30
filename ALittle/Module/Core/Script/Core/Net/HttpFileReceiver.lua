-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___pairs = pairs
local ___ipairs = ipairs


IHttpFileReceiver = Lua.Class(nil, "ALittle.IHttpFileReceiver")

function IHttpFileReceiver:StartReceiveFile(file_path, start_size)
local ___COROUTINE = coroutine.running()
	return "not impl"
end

local __all_callback = {}
function RegHttpFileCallback(method, callback)
	if __all_callback[method] ~= nil then
		Error("RegHttpFileCallback消息回调函数注册失败，名字为" .. method .. "已存在")
		return
	end
	__all_callback[method] = callback
end

function FindHttpFileReceiverCallback(method)
	return __all_callback[method]
end

