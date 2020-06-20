-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.Quad, " extends class:ALittle.Quad is nil")
IDECodeCursor = Lua.Class(ALittle.Quad, "ALittleIDE.IDECodeCursor")

function IDECodeCursor:Ctor(ctrl_sys, tab_child)
	___rawset(self, "_flash_alpha", 0)
	___rawset(self, "_flash_dir", 0.05)
	___rawset(self, "_it_line", 1)
	___rawset(self, "_it_char", 0)
	___rawset(self, "_tab_child", tab_child)
end

function IDECodeCursor.__getter:line()
	return self._it_line
end

function IDECodeCursor.__getter:char()
	return self._it_char
end

function IDECodeCursor:Show(x, y)
	if self._loop == nil then
		self._loop = ALittle.LoopFunction(Lua.Bind(self.Update, self), -1, 1, 1)
	end
	if not A_LoopSystem:HasUpdater(self._loop) then
		A_LoopSystem:AddUpdater(self._loop)
	end
	self.visible = true
end

function IDECodeCursor:CalcSelectWord()
	local line = self._tab_child.line_list[self._it_line]
	if line == nil then
		return nil, nil
	end
	local count = line.char_count
	while count > 0 and line.char_list[count].width <= 0 do
		count = count - 1
	end
	local it_end = self._it_char
	local i = self._it_char + 1
	while true do
		if not(i <= count) then break end
		local char = line.char_list[i].char
		local byte = ALittle.String_Byte(char, 1)
		local check = byte >= 65 and byte <= 90 or byte >= 97 and byte <= 122 or byte == 95
		if not check then
			break
		end
		it_end = i
		i = i+(1)
	end
	local it_start = self._it_char
	local i = self._it_char
	while true do
		if not(i >= 1) then break end
		local char = line.char_list[i].char
		local byte = ALittle.String_Byte(char, 1)
		local check = byte >= 65 and byte <= 90 or byte >= 97 and byte <= 122 or byte == 95
		if not check then
			break
		end
		it_start = i
		i = i+(-1)
	end
	if it_start == it_end then
		return nil, nil
	end
	it_start = it_start - (1)
	if it_start < 0 then
		it_start = 0
	end
	return it_start, it_end
end

function IDECodeCursor:SetOffsetXY(x, y, show)
	if self._tab_child.line_count <= 0 then
		self._it_line = 1
		self._it_char = 0
	else
		self._it_line, self._it_char = self._tab_child:CalcLineAndChar(x, y)
	end
	self.y = (self._it_line - 1) * self._tab_child.line_height
	local line = self._tab_child.line_list[self._it_line]
	if line == nil or self._it_char == 0 then
		self.x = 0
	else
		self.x = line.char_list[self._it_char].pre_width + line.char_list[self._it_char].width
	end
	if show == nil or show then
		self:Show()
	end
end

function IDECodeCursor:SetLineChar(it_line, it_char, show)
	self._it_line = it_line
	self._it_char = it_char
	self.y = (self._it_line - 1) * self._tab_child.line_height
	local line = self._tab_child.line_list[self._it_line]
	if line == nil or self._it_char <= 0 then
		self.x = 0
	else
		self.x = line.char_list[self._it_char].pre_width + line.char_list[self._it_char].width
	end
	if show == nil or show then
		self:Show()
	end
end

function IDECodeCursor:OffsetUp()
	if self._it_line <= 1 then
		return
	end
	local it_line = self._it_line - 1
	local line = self._tab_child.line_list[it_line]
	if line == nil then
		return
	end
	local it_char = line.char_count
	while it_char > 0 and line.char_list[it_char].width <= 0 do
		it_char = it_char - 1
	end
	if self._it_char < it_char then
		it_char = self._it_char
	end
	self:SetLineChar(it_line, it_char, false)
end

function IDECodeCursor:OffsetDown()
	if self._it_line >= self._tab_child.line_count then
		return
	end
	local it_line = self._it_line + 1
	local line = self._tab_child.line_list[it_line]
	if line == nil then
		return
	end
	local it_char = line.char_count
	while it_char > 0 and line.char_list[it_char].width <= 0 do
		it_char = it_char - 1
	end
	if self._it_char < it_char then
		it_char = self._it_char
	end
	self:SetLineChar(it_line, it_char, false)
end

function IDECodeCursor:OffsetLeft()
	if self._it_char > 0 then
		self:SetLineChar(self._it_line, self._it_char - 1, false)
		return
	end
	if self._it_line > 1 then
		local it_line = self._it_line - 1
		local line = self._tab_child.line_list[it_line]
		local it_char = line.char_count
		while it_char > 0 and line.char_list[it_char].width <= 0 do
			it_char = it_char - 1
		end
		self:SetLineChar(it_line, it_char, false)
		return
	end
	self:SetLineChar(1, 0, false)
end

function IDECodeCursor:OffsetRight()
	if self._tab_child.line_count <= 0 then
		return
	end
	local line = self._tab_child.line_list[self._it_line]
	local count = line.char_count
	while count > 0 and line.char_list[count].width <= 0 do
		count = count - 1
	end
	if self._it_char < count then
		self:SetLineChar(self._it_line, self._it_char + 1, false)
		return
	end
	if self._it_line >= self._tab_child.line_count then
		return
	end
	self:SetLineChar(self._it_line + 1, 0, false)
end

function IDECodeCursor:OffsetHome()
	if self._it_char <= 0 then
		return
	end
	local line = self._tab_child.line_list[self._it_line]
	if line == nil then
		return
	end
	local it_char = 1
	while it_char <= line.char_count do
		local char = line.char_list[it_char]
		if char.char ~= " " and char.char ~= "\t" then
			break
		end
		it_char = it_char + 1
	end
	if self._it_char == it_char - 1 then
		self:SetLineChar(self._it_line, 0, false)
	else
		self:SetLineChar(self._it_line, it_char - 1, false)
	end
end

function IDECodeCursor:OffsetEnd()
	local line = self._tab_child.line_list[self._it_line]
	if line == nil then
		return
	end
	local count = line.char_count
	while count > 0 and line.char_list[count].width <= 0 do
		count = count - 1
	end
	if self._it_char < count then
		self:SetLineChar(self._it_line, count, false)
	end
end

function IDECodeCursor:Hide()
	if self._loop ~= nil then
		self._loop:Stop()
	end
	self.visible = false
end

function IDECodeCursor:Update()
	if self.abs_visible then
		self._flash_alpha = self._flash_alpha + self._flash_dir
		if (self._flash_dir < 0 and self._flash_alpha < -0.05) or (self._flash_dir > 0 and self._flash_alpha > 1.5) then
			self._flash_dir = -self._flash_dir
		end
		self.alpha = self._flash_alpha
	end
end

