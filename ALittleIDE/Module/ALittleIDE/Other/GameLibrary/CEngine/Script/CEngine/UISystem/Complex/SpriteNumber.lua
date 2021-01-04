-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


local __tostring = ALittle.String_ToString
local __len = ALittle.String_Len
local __byte = ALittle.String_Byte
assert(ALittle.Linear, " extends class:ALittle.Linear is nil")
ALittle.SpriteNumber = Lua.Class(ALittle.Linear, "ALittle.SpriteNumber")

function ALittle.SpriteNumber:Ctor()
	___rawset(self, "_col_count", 1)
	___rawset(self, "_text", "")
	___rawset(self, "_cell_width", 0)
	___rawset(self, "_sprite_pool", {})
	___rawset(self, "_pool_count", 0)
end

function ALittle.SpriteNumber.__getter:texture_name()
	return self._texture_name
end

function ALittle.SpriteNumber.__getter:cell_width()
	return self._cell_width
end

function ALittle.SpriteNumber.__setter:cell_width(value)
	self._cell_width = value
	for index, child in ___ipairs(self._childs) do
		child.width = value
	end
	for index, child in ___ipairs(self._sprite_pool) do
		child.width = value
	end
	self:Layout(1)
end

function ALittle.SpriteNumber.__setter:texture_name(value)
	if self._texture_name == value then
		return
	end
	self._texture_name = value
	for index, child in ___ipairs(self._childs) do
		child.texture_name = value
	end
	for index, child in ___ipairs(self._sprite_pool) do
		child.texture_name = value
	end
end

function ALittle.SpriteNumber.__getter:col_count()
	return self._col_count
end

function ALittle.SpriteNumber.__setter:col_count(value)
	if value < 1 then
		value = 1
	end
	self._col_count = value
	for index, child in ___ipairs(self._childs) do
		child.col_count = value
	end
	for index, child in ___ipairs(self._sprite_pool) do
		child.col_count = value
	end
end

function ALittle.SpriteNumber.__getter:text()
	return self._text
end

function ALittle.SpriteNumber.__setter:text(value)
	if value == nil then
		return
	end
	value = __tostring(value)
	if self._text == value then
		return
	end
	self._text = value
	local len = __len(value)
	if self._child_count > len then
		local index = len + 1
		while true do
			if not(index <= self._child_count) then break end
			self._pool_count = self._pool_count + (1)
			self._sprite_pool[self._pool_count] = self._childs[index]
			index = index+(1)
		end
		self:SpliceChild(len + 1)
	elseif self._child_count < len then
		local index = self._child_count + 1
		while true do
			if not(index <= len) then break end
			local child
			if self._pool_count > 1 then
				child = self._sprite_pool[self._pool_count]
				self._sprite_pool[self._pool_count] = nil
				self._pool_count = self._pool_count - (1)
			else
				child = ALittle.Sprite(self._ctrl_sys)
				child.col_count = self._col_count
				child.texture_name = self._texture_name
				child.width = self._cell_width
			end
			self:AddChild(child)
			index = index+(1)
		end
	end
	local byte = 0
	for index, child in ___ipairs(self._childs) do
		byte = __byte(value, index)
		if byte >= 48 and byte <= 57 then
			child.col_index = byte - 47
		elseif byte == 43 then
			child.col_index = 11
		elseif byte == 45 then
			child.col_index = 12
		elseif byte == 46 then
			child.col_index = 13
		elseif byte == 47 then
			child.col_index = 14
		else
			child.col_index = 1
		end
	end
end

end