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
	if line == nil or self._it_char == 0 then
		self.x = 0
	else
		self.x = line.char_list[self._it_char].pre_width + line.char_list[self._it_char].width
	end
	if show == nil or show then
		self:Show()
	end
end

function IDECodeCursor:OffsetLeft()
end

function IDECodeCursor:OffsetRight()
end

function IDECodeCursor:OffsetHome()
end

function IDECodeCursor:OffsetEnd()
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

