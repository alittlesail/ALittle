-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


ALittle.SafeIDCreator = Lua.Class(nil, "ALittle.SafeIDCreator")

function ALittle.SafeIDCreator:Ctor()
	___rawset(self, "_max_id", 0)
	___rawset(self, "_map", {})
end

function ALittle.SafeIDCreator:CreateID()
	local id = nil
	for k, v in ___pairs(self._map) do
		id = k
		break
	end
	if id ~= nil then
		self._map[id] = nil
		return id
	end
	self._max_id = self._max_id + 1
	return self._max_id
end

function ALittle.SafeIDCreator:ReleaseID(id)
	self._map[id] = true
end

function ALittle.SafeIDCreator:PrintStatus()
	local count = 0
	for k, v in ___pairs(self._map) do
		count = count + 1
	end
	ALittle.Log("SafeIDCreator:PrintStatus count:" .. count .. " max_id:" .. self._max_id)
end

end