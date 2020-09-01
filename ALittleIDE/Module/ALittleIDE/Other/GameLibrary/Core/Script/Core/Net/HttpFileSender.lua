-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.IHttpFileSender = Lua.Class(nil, "ALittle.IHttpFileSender")

function ALittle.IHttpFileSender:HandleSucceed()
end

function ALittle.IHttpFileSender:HandleProcess(cur_size, total_size)
end

function ALittle.IHttpFileSender:HandleFailed(reason)
end

function ALittle.IHttpFileSender:Stop()
end

function ALittle.IHttpFileSender:GetFilePath()
	return nil
end

function ALittle.IHttpFileSender:GetTotalSize()
	return 0
end

function ALittle.IHttpFileSender:GetCurSize()
	return 0
end

function ALittle.IHttpFileSender:SendDownloadRPC(thread, method, content, array_buffer)
	Lua.Throw("not impl")
end

function ALittle.IHttpFileSender:SendUploadRPC(thread, method, content, array_buffer)
	Lua.Throw("not impl")
end

function ALittle.IHttpFileSender.InvokeDownload(method, client, content, array_buffer)
	local ___COROUTINE = coroutine.running()
	if ___COROUTINE == nil then
		return "当前不是协程"
	end
	client:SendDownloadRPC(___COROUTINE, method, content, array_buffer)
	return coroutine.yield()
end

function ALittle.IHttpFileSender.InvokeUpload(method, client, content, array_buffer)
	local ___COROUTINE = coroutine.running()
	if ___COROUTINE == nil then
		return "当前不是协程"
	end
	client:SendUploadRPC(___COROUTINE, method, content, array_buffer)
	return coroutine.yield()
end

end