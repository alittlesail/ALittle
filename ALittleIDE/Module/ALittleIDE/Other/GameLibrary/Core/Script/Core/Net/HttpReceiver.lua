-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.IHttpReceiver = Lua.Class(nil, "ALittle.IHttpReceiver")

local __all_callback = {}
function ALittle.RegHttpCallback(method, callback)
	if __all_callback[method] ~= nil then
		ALittle.Error("RegHttpCallback消息回调函数注册失败，名字为" .. method .. "已存在")
		return
	end
	__all_callback[method] = callback
end

function ALittle.FindHttpCallback(method)
	return __all_callback[method]
end

local __all_download_callback = {}
function ALittle.RegHttpDownloadCallback(method, callback)
	if __all_download_callback[method] ~= nil then
		ALittle.Error("RegHttpDownloadCallback消息回调函数注册失败，名字为" .. method .. "已存在")
		return
	end
	__all_download_callback[method] = callback
end

function ALittle.FindHttpDownloadCallback(method)
	return __all_download_callback[method]
end

end