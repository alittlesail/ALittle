-- ALittle Generate Lua And Do Not Edit This Line!
module("Emulator", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


LWProtobuf = Lua.Class(nil, "Emulator.LWProtobuf")

function LWProtobuf:Ctor()
	___rawset(self, "_id_map_name", {})
	___rawset(self, "_name_map_id", {})
end

function LWProtobuf:Clear()
	self._id_map_name = {}
	self._name_map_id = {}
end

function LWProtobuf:Refresh()
	self:Clear()
	local enum_descriptor = A_LuaSocketSchedule:GetEnumDescriptor("EMsgTypes")
	if enum_descriptor == nil then
		return
	end
	local count = protobuf.enumdescriptor_valuecount(enum_descriptor)
	local i = 0
	while true do
		if not(i < count) then break end
		local enumvalue_descriptor = protobuf.enumdescriptor_value(enum_descriptor, i)
		if enumvalue_descriptor ~= nil then
			local field_name = protobuf.enumvaluedescriptor_name(enumvalue_descriptor)
			local field_number = protobuf.enumvaluedescriptor_number(enumvalue_descriptor)
			self._id_map_name[field_number] = field_name
			self._name_map_id[field_name] = field_number
		end
		i = i+(1)
	end
end

g_LWProtobuf = LWProtobuf()
