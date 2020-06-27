-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


RevokeObject = Lua.Class(nil, "ALittle.RevokeObject")

function RevokeObject:Forward()
end

function RevokeObject:Back()
end

RevokeList = Lua.Class(nil, "ALittle.RevokeList")

function RevokeList:Ctor()
	___rawset(self, "_revoke_list", {})
	___rawset(self, "_revoke_count", 0)
	___rawset(self, "_revoke_index", 0)
	___rawset(self, "_max_count", 100)
end

function RevokeList:PushRevoke(revoke)
	if self._revoke_index < self._revoke_count then
		local i = self._revoke_index + 1
		while true do
			if not(i <= self._revoke_count) then break end
			self._revoke_list[i] = nil
			i = i+(1)
		end
		self._revoke_count = self._revoke_index
	end
	self._revoke_index = self._revoke_index + 1
	self._revoke_count = self._revoke_count + 1
	self._revoke_list[self._revoke_index] = revoke
	if self._revoke_count > self._max_count then
		self._revoke_index = self._revoke_index - 1
		self._revoke_count = self._revoke_count - 1
		ALittle.List_Remove(self._revoke_list, 1)
	end
end

function RevokeList:DoRevoke()
	if self._revoke_index >= self._revoke_count then
		return
	end
	self._revoke_index = self._revoke_index + 1
	local revoke = self._revoke_list[self._revoke_index]
	revoke:Forward()
end

function RevokeList:UndoRevoke()
	if self._revoke_index == 0 then
		return
	end
	local revoke = self._revoke_list[self._revoke_index]
	revoke:Back()
	self._revoke_index = self._revoke_index - 1
end

assert(ALittle.RevokeObject, " extends class:ALittle.RevokeObject is nil")
RevokeBind = Lua.Class(ALittle.RevokeObject, "ALittle.RevokeBind")

function RevokeBind:Ctor()
	___rawset(self, "_list", {})
	___rawset(self, "_count", 0)
end

function RevokeBind:PushRevoke(revoke)
	self._count = self._count + 1
	self._list[self._count] = revoke
end

function RevokeBind:Forward()
	for k, revoke in ___ipairs(self._list) do
		revoke:Forward()
	end
end

function RevokeBind:Back()
	local i = self._count
	while true do
		if not(i >= 1) then break end
		self._list[i]:Back()
		i = i+(-1)
	end
end
