
module("Lua", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


local wcreate = net.createwfactory
local wsetid = net.wfactorysetid
local wsetrpcid = net.wfactorysetrpcid
local wresetoffset = net.wfactoryresetoffset
local wgetoffset = net.wfactorygetoffset
local wsetint = net.wfactorysetint
local writebool = net.wfactorywritebool
local writeint = net.wfactorywriteint
local writelong = net.wfactorywritelong
local writestring = net.wfactorywritestring
local writedouble = net.wfactorywritedouble
assert(ALittle.IMessageWriteFactory, " extends class:ALittle.IMessageWriteFactory is nil")
LuaMessageWriteFactory = Lua.Class(ALittle.IMessageWriteFactory, "Lua.LuaMessageWriteFactory")

function LuaMessageWriteFactory:Ctor()
	___rawset(self, "_factory", wcreate())
end

function LuaMessageWriteFactory:SetID(id)
	wsetid(self._factory, id)
end

function LuaMessageWriteFactory:SetRpcID(id)
	wsetrpcid(self._factory, id)
end

function LuaMessageWriteFactory:ResetOffset()
	wresetoffset(self._factory)
end

function LuaMessageWriteFactory:GetOffset()
	return wgetoffset(self._factory)
end

function LuaMessageWriteFactory:SetInt(offset, value)
	wsetint(self._factory, offset, value)
end

function LuaMessageWriteFactory:WriteBool(value)
	return writebool(self._factory, value)
end

function LuaMessageWriteFactory:WriteInt(value)
	return writeint(self._factory, value)
end

function LuaMessageWriteFactory:WriteLong(value)
	return writelong(self._factory, value)
end

function LuaMessageWriteFactory:WriteString(value)
	return writestring(self._factory, value)
end

function LuaMessageWriteFactory:WriteDouble(value)
	return writedouble(self._factory, value)
end

local getdatasize = net.rfactorygetdatasize
local readbool = net.rfactoryreadbool
local readint = net.rfactoryreadint
local readlong = net.rfactoryreadlong
local readstring = net.rfactoryreadstring
local readdouble = net.rfactoryreaddouble
local getreadsize = net.rfactorygetreadsize
assert(ALittle.IMessageReadFactory, " extends class:ALittle.IMessageReadFactory is nil")
LuaMessageReadFactory = Lua.Class(ALittle.IMessageReadFactory, "Lua.LuaMessageReadFactory")

function LuaMessageReadFactory:SetFactory(factory)
	self._factory = factory
end

function LuaMessageReadFactory:GetDataSize()
	return getdatasize(self._factory)
end

function LuaMessageReadFactory:ReadBool()
	return readbool(self._factory)
end

function LuaMessageReadFactory:ReadInt()
	return readint(self._factory)
end

function LuaMessageReadFactory:ReadLong()
	return readlong(self._factory)
end

function LuaMessageReadFactory:ReadString()
	return readstring(self._factory)
end

function LuaMessageReadFactory:ReadDouble()
	return readdouble(self._factory)
end

function LuaMessageReadFactory:GetReadSize()
	return getreadsize(self._factory)
end

