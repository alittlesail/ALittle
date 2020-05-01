-- ALittle Generate Lua
module("Lua", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


local __LUAMSG_MAXID = 0
assert(ALittle.IMsgCommonNative, " extends class:ALittle.IMsgCommonNative is nil")
LuaMsgInterface = Lua.Class(ALittle.IMsgCommonNative, "Lua.LuaMsgInterface")

function LuaMsgInterface:Ctor()
	__LUAMSG_MAXID = __LUAMSG_MAXID + 1
	___rawset(self, "_id", __LUAMSG_MAXID)
end

function LuaMsgInterface:GetID()
	return self._id
end

function LuaMsgInterface:Connect(ip, port)
	net.connect(A_LuaSchedule._net, self._id, ip, port)
end

function LuaMsgInterface:Close()
	net.close(A_LuaSchedule._net, self._id)
end

function LuaMsgInterface:IsConnected()
	return net.isconnected(A_LuaSchedule._net, self._id)
end

function LuaMsgInterface:SendFactory(factory)
	net.send(A_LuaSchedule._net, self._id, factory._factory)
end

