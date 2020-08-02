-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.Lua == nil then _G.Lua = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.IMessageWriteFactory, " extends class:ALittle.IMessageWriteFactory is nil")
Lua.LuaMessageWriteFactory = Lua.Class(ALittle.IMessageWriteFactory, "Lua.LuaMessageWriteFactory")

function Lua.LuaMessageWriteFactory:Ctor()
	___rawset(self, "_factory", net.createwfactory())
end

function Lua.LuaMessageWriteFactory:SetID(id)
	net.wfactorysetid(self._factory, id)
end

function Lua.LuaMessageWriteFactory:SetRpcID(id)
	net.wfactorysetrpcid(self._factory, id)
end

function Lua.LuaMessageWriteFactory:ResetOffset()
	net.wfactoryresetoffset(self._factory)
end

function Lua.LuaMessageWriteFactory:GetOffset()
	return net.wfactorygetoffset(self._factory)
end

function Lua.LuaMessageWriteFactory:SetInt(offset, value)
	net.wfactorysetint(self._factory, offset, value)
end

function Lua.LuaMessageWriteFactory:WriteBool(value)
	return net.wfactorywritebool(self._factory, value)
end

function Lua.LuaMessageWriteFactory:WriteInt(value)
	return net.wfactorywriteint(self._factory, value)
end

function Lua.LuaMessageWriteFactory:WriteLong(value)
	return net.wfactorywritelong(self._factory, value)
end

function Lua.LuaMessageWriteFactory:WriteString(value)
	return net.wfactorywritestring(self._factory, value)
end

function Lua.LuaMessageWriteFactory:WriteDouble(value)
	return net.wfactorywritedouble(self._factory, value)
end

assert(ALittle.IMessageReadFactory, " extends class:ALittle.IMessageReadFactory is nil")
Lua.LuaMessageReadFactory = Lua.Class(ALittle.IMessageReadFactory, "Lua.LuaMessageReadFactory")

function Lua.LuaMessageReadFactory:SetFactory(factory)
	self._factory = factory
end

function Lua.LuaMessageReadFactory:GetDataSize()
	return net.rfactorygetdatasize(self._factory)
end

function Lua.LuaMessageReadFactory:ReadBool()
	return net.rfactoryreadbool(self._factory)
end

function Lua.LuaMessageReadFactory:ReadInt()
	return net.rfactoryreadint(self._factory)
end

function Lua.LuaMessageReadFactory:ReadLong()
	return net.rfactoryreadlong(self._factory)
end

function Lua.LuaMessageReadFactory:ReadString()
	return net.rfactoryreadstring(self._factory)
end

function Lua.LuaMessageReadFactory:ReadDouble()
	return net.rfactoryreaddouble(self._factory)
end

function Lua.LuaMessageReadFactory:GetReadSize()
	return net.rfactorygetreadsize(self._factory)
end

end