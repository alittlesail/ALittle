-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittle", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


IHttpFileSender = Lua.Class(nil, "ALittle.IHttpFileSender")

function IHttpFileSender:HandleSucceed()
end

function IHttpFileSender:HandleProcess(cur_size, total_size)
end

function IHttpFileSender:HandleFailed(reason)
end

function IHttpFileSender:Stop()
end

function IHttpFileSender:GetFilePath()
	return nil
end

function IHttpFileSender:GetTotalSize()
	return 0
end

function IHttpFileSender:GetCurSize()
	return 0
end

function IHttpFileSender:SendDownloadRPC(thread, method, content)
	Lua.Throw("not impl")
end

function IHttpFileSender:SendUploadRPC(thread, method, content)
	Lua.Throw("not impl")
end

function IHttpFileSender.InvokeDownload(method, client, content)
local ___COROUTINE = coroutine.running()
	if ___COROUTINE == nil then
		return "当前不是协程"
	end
	client:SendDownloadRPC(___COROUTINE, method, content)
	return coroutine.yield()
end

function IHttpFileSender.InvokeUpload(method, client, content)
local ___COROUTINE = coroutine.running()
	if ___COROUTINE == nil then
		return "当前不是协程"
	end
	client:SendUploadRPC(___COROUTINE, method, content)
	return coroutine.yield()
end

