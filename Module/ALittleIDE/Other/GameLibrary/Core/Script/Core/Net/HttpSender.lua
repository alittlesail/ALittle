
module("ALittle", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


IHttpSender = Lua.Class(nil, "ALittle.IHttpSender")

function IHttpSender:HandleSucceed()
end

function IHttpSender:HandleFailed(reason)
end

function IHttpSender:SendRPC(thread, method, content)
	Lua.Throw("not impl")
end

function IHttpSender.Invoke(method, client, content)
local ___COROUTINE = coroutine.running()
	if ___COROUTINE == nil then
		return "当前不是协程", nil
	end
	client:SendRPC(___COROUTINE, method, content)
	return coroutine.yield()
end

