
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


MsgSessionTemplate = Lua.Class(nil, "ALittle.MsgSessionTemplate")

function MsgSessionTemplate:Ctor(connect_key, route_type, route_num)
	___rawset(self, "_interface", self.__class.__element[1]())
	self._interface:SetID(connect_key)
	___rawset(self, "_write_factory", self.__class.__element[2]())
	___rawset(self, "_is_connected", true)
	___rawset(self, "_connect_key", connect_key)
	___rawset(self, "_route_type", route_type)
	___rawset(self, "_route_num", route_num)
end

function MsgSessionTemplate.__getter:route_type()
	return self._route_type
end

function MsgSessionTemplate.__getter:route_num()
	return self._route_num
end

function MsgSessionTemplate:IsConnected()
	return self._is_connected
end

function MsgSessionTemplate:HandleConnected()
	self._is_connected = true
end

function MsgSessionTemplate:HandleDisconnected()
	self._is_connected = false
	self:ClearRPC("连接断开了")
end

function MsgSessionTemplate:Close(reason)
	if not self._is_connected then
		return
	end
	self._is_connected = false
	if reason == nil then
		reason = "主动关闭连接"
	end
	self:ClearRPC(reason)
	self._interface:Close()
end

