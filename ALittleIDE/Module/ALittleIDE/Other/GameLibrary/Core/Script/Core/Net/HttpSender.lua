-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.IHttpSender = Lua.Class(nil, "ALittle.IHttpSender")

function ALittle.IHttpSender:HandleSucceed()
end

function ALittle.IHttpSender:HandleFailed(reason)
end

function ALittle.IHttpSender:Stop()
end

function ALittle.IHttpSender:SendRPC(thread, method, content)
	Lua.Throw("not impl")
end

function ALittle.IHttpSender.Invoke(method, client, content)
	local ___COROUTINE = coroutine.running()
	if ___COROUTINE == nil then
		return "当前不是协程", nil
	end
	client:SendRPC(___COROUTINE, method, content)
	return coroutine.yield()
end

end