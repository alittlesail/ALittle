-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name = "ALittle.UIChangedEvent", ns_name = "ALittle", rl_name = "UIChangedEvent", hash_code = 958494922,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

assert(ALittle.RevokeObject, " extends class:ALittle.RevokeObject is nil")
AUICodeDeleteLeftRevoke = Lua.Class(ALittle.RevokeObject, "AUIPlugin.AUICodeDeleteLeftRevoke")

function AUICodeDeleteLeftRevoke:Ctor(edit, cursor, old_it_line, old_it_char, new_it_line, new_it_char, content)
	___rawset(self, "_edit", edit)
	___rawset(self, "_cursor", cursor)
	___rawset(self, "_old_it_line", old_it_line)
	___rawset(self, "_old_it_char", old_it_char)
	___rawset(self, "_new_it_line", new_it_line)
	___rawset(self, "_new_it_char", new_it_char)
	___rawset(self, "_content", content)
end

function AUICodeDeleteLeftRevoke:Forward()
	self._cursor:SetLineChar(self._old_it_line, self._old_it_char)
	self._cursor:DeleteLeft(false)
	self._edit:DispatchEvent(___all_struct[958494922], {})
end

function AUICodeDeleteLeftRevoke:Back()
	self._cursor:SetLineChar(self._new_it_line, self._new_it_char)
	self._edit:InsertText(self._content, false)
	self._edit:DispatchEvent(___all_struct[958494922], {})
end

assert(ALittle.RevokeObject, " extends class:ALittle.RevokeObject is nil")
AUICodeDeleteRightRevoke = Lua.Class(ALittle.RevokeObject, "AUIPlugin.AUICodeDeleteRightRevoke")

function AUICodeDeleteRightRevoke:Ctor(edit, cursor, old_it_line, old_it_char, new_it_line, new_it_char, content)
	___rawset(self, "_edit", edit)
	___rawset(self, "_cursor", cursor)
	___rawset(self, "_old_it_line", old_it_line)
	___rawset(self, "_old_it_char", old_it_char)
	___rawset(self, "_new_it_line", new_it_line)
	___rawset(self, "_new_it_char", new_it_char)
	___rawset(self, "_content", content)
end

function AUICodeDeleteRightRevoke:Forward()
	self._cursor:SetLineChar(self._old_it_line, self._old_it_char)
	self._cursor:DeleteRight(false)
	self._edit:DispatchEvent(___all_struct[958494922], {})
end

function AUICodeDeleteRightRevoke:Back()
	self._cursor:SetLineChar(self._new_it_line, self._new_it_char)
	self._edit:InsertText(self._content, false)
	self._cursor:SetLineChar(self._new_it_line, self._new_it_char)
	self._edit:DispatchEvent(___all_struct[958494922], {})
end

