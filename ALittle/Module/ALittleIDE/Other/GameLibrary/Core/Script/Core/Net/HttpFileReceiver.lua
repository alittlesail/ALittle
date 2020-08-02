-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.IHttpFileReceiver = Lua.Class(nil, "ALittle.IHttpFileReceiver")

function ALittle.IHttpFileReceiver:StartReceiveFile(file_path, start_size)
	local ___COROUTINE = coroutine.running()
	return "not impl"
end

local __all_callback = {}
function ALittle.RegHttpFileCallback(method, callback)
	if __all_callback[method] ~= nil then
		ALittle.Error("RegHttpFileCallback消息回调函数注册失败，名字为" .. method .. "已存在")
		return
	end
	__all_callback[method] = callback
end

function ALittle.FindHttpFileReceiverCallback(method)
	return __all_callback[method]
end

end