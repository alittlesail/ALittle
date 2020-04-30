-- ALittle Generate Lua
module("Lua", package.seeall)

local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.IMessageWriteFactory, " extends class:ALittle.IMessageWriteFactory is nil")
LuaMessageWriteFactory = Lua.Class(ALittle.IMessageWriteFactory, "Lua.LuaMessageWriteFactory")

function LuaMessageWriteFactory:Ctor()
	___rawset(self, "_factory", net.createwfactory())
end

function LuaMessageWriteFactory:SetID(id)
	net.wfactorysetid(self._factory, id)
end

function LuaMessageWriteFactory:SetRpcID(id)
	net.wfactorysetrpcid(self._factory, id)
end

function LuaMessageWriteFactory:ResetOffset()
	net.wfactoryresetoffset(self._factory)
end

function LuaMessageWriteFactory:GetOffset()
	return net.wfactorygetoffset(self._factory)
end

function LuaMessageWriteFactory:SetInt(offset, value)
	net.wfactorysetint(self._factory, offset, value)
end

function LuaMessageWriteFactory:WriteBool(value)
	return net.wfactorywritebool(self._factory, value)
end

function LuaMessageWriteFactory:WriteInt(value)
	return net.wfactorywriteint(self._factory, value)
end

function LuaMessageWriteFactory:WriteLong(value)
	return net.wfactorywritelong(self._factory, value)
end

function LuaMessageWriteFactory:WriteString(value)
	return net.wfactorywritestring(self._factory, value)
end

function LuaMessageWriteFactory:WriteDouble(value)
	return net.wfactorywritedouble(self._factory, value)
end

assert(ALittle.IMessageReadFactory, " extends class:ALittle.IMessageReadFactory is nil")
LuaMessageReadFactory = Lua.Class(ALittle.IMessageReadFactory, "Lua.LuaMessageReadFactory")

function LuaMessageReadFactory:SetFactory(factory)
	self._factory = factory
end

function LuaMessageReadFactory:GetDataSize()
	return net.rfactorygetdatasize(self._factory)
end

function LuaMessageReadFactory:ReadBool()
	return net.rfactoryreadbool(self._factory)
end

function LuaMessageReadFactory:ReadInt()
	return net.rfactoryreadint(self._factory)
end

function LuaMessageReadFactory:ReadLong()
	return net.rfactoryreadlong(self._factory)
end

function LuaMessageReadFactory:ReadString()
	return net.rfactoryreadstring(self._factory)
end

function LuaMessageReadFactory:ReadDouble()
	return net.rfactoryreaddouble(self._factory)
end

function LuaMessageReadFactory:GetReadSize()
	return net.rfactorygetreadsize(self._factory)
end

