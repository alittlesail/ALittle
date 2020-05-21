-- ALittle Generate Lua And Do Not Edit This Line!
module("Lua", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


local __LUAHTTP_MAXID = 0
assert(ALittle.IHttpSenderNative, " extends class:ALittle.IHttpSenderNative is nil")
LuaHttpInterface = Lua.Class(ALittle.IHttpSenderNative, "Lua.LuaHttpInterface")

function LuaHttpInterface:Ctor()
	__LUAHTTP_MAXID = __LUAHTTP_MAXID + 1
	___rawset(self, "_id", __LUAHTTP_MAXID)
end

function LuaHttpInterface:GetID()
	return self._id
end

function LuaHttpInterface:SetURL(url, content)
	self._url = url
	self._content = content
end

function LuaHttpInterface:Start()
	if self._content == nil then
		net.get(A_LuaSchedule._net, self._id, self._url)
	else
		net.post(A_LuaSchedule._net, self._id, self._url, "application/json", self._content)
	end
end

function LuaHttpInterface:Stop()
	if self._content == nil then
		net.stopget(A_LuaSchedule._net, self._id)
	else
		net.stoppost(A_LuaSchedule._net, self._id)
	end
end

function LuaHttpInterface:GetResponse()
	return self._response
end
