-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.Lua == nil then _G.Lua = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


local __LUAMSG_MAXID = 0
assert(ALittle.IMsgCommonNative, " extends class:ALittle.IMsgCommonNative is nil")
Lua.LuaMsgInterface = Lua.Class(ALittle.IMsgCommonNative, "Lua.LuaMsgInterface")

function Lua.LuaMsgInterface:Ctor()
	__LUAMSG_MAXID = __LUAMSG_MAXID + 1
	___rawset(self, "_id", __LUAMSG_MAXID)
end

function Lua.LuaMsgInterface:GetID()
	return self._id
end

function Lua.LuaMsgInterface:Connect(ip, port)
	net.connect(A_LuaSchedule._net, self._id, ip, port)
end

function Lua.LuaMsgInterface:Close()
	net.close(A_LuaSchedule._net, self._id)
end

function Lua.LuaMsgInterface:IsConnected()
	return net.isconnected(A_LuaSchedule._net, self._id)
end

function Lua.LuaMsgInterface:SendFactory(factory)
	net.send(A_LuaSchedule._net, self._id, factory._factory)
end

end