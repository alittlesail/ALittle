-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


IDERevokeObject = Lua.Class(nil, "ALittleIDE.IDERevokeObject")

function IDERevokeObject:Forward()
end

function IDERevokeObject:Back()
end

IDERevokeList = Lua.Class(nil, "ALittleIDE.IDERevokeList")

function IDERevokeList:Ctor()
	___rawset(self, "_revoke_list", {})
	___rawset(self, "_revoke_count", 0)
	___rawset(self, "_revoke_index", 0)
	___rawset(self, "_max_count", 100)
end

function IDERevokeList:PushRevoke(revoke)
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

function IDERevokeList:DoRevoke()
	if self._revoke_index >= self._revoke_count then
		return
	end
	self._revoke_index = self._revoke_index + 1
	local revoke = self._revoke_list[self._revoke_index]
	revoke:Forward()
end

function IDERevokeList:UndoRevoke()
	if self._revoke_index == 0 then
		return
	end
	local revoke = self._revoke_list[self._revoke_index]
	revoke:Back()
	self._revoke_index = self._revoke_index - 1
end

assert(ALittleIDE.IDERevokeObject, " extends class:ALittleIDE.IDERevokeObject is nil")
IDERevokeBind = Lua.Class(ALittleIDE.IDERevokeObject, "ALittleIDE.IDERevokeBind")

function IDERevokeBind:Ctor()
	___rawset(self, "_list", {})
	___rawset(self, "_count", 0)
end

function IDERevokeBind:PushRevoke(revoke)
	self._count = self._count + 1
	self._list[self._count] = revoke
end

function IDERevokeBind:Forward()
	for k, revoke in ___ipairs(self._list) do
		revoke:Forward()
	end
end

function IDERevokeBind:Back()
	local i = self._count
	while true do
		if not(i >= 1) then break end
		self._list[i]:Back()
		i = i+(-1)
	end
end

