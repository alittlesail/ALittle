-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___pairs = pairs
local ___ipairs = ipairs


IHttpReceiver = Lua.Class(nil, "ALittle.IHttpReceiver")

local __all_callback = {}
function RegHttpCallback(method, callback)
	if __all_callback[method] ~= nil then
		Error("RegHttpCallback消息回调函数注册失败，名字为" .. method .. "已存在")
		return
	end
	__all_callback[method] = callback
end

function FindHttpCallback(method)
	return __all_callback[method]
end

local __all_download_callback = {}
function RegHttpDownloadCallback(method, callback)
	if __all_download_callback[method] ~= nil then
		Error("RegHttpDownloadCallback消息回调函数注册失败，名字为" .. method .. "已存在")
		return
	end
	__all_download_callback[method] = callback
end

function FindHttpDownloadCallback(method)
	return __all_download_callback[method]
end

