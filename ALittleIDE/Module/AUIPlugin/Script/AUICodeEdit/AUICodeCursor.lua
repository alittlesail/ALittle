-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.AUIPlugin == nil then _G.AUIPlugin = {} end
local AUIPlugin = AUIPlugin
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.Quad, " extends class:ALittle.Quad is nil")
AUIPlugin.AUICodeCursor = Lua.Class(ALittle.Quad, "AUIPlugin.AUICodeCursor")

function AUIPlugin.AUICodeCursor:Ctor(ctrl_sys, edit)
	___rawset(self, "_flash_alpha", 0)
	___rawset(self, "_flash_dir", 0.05)
	___rawset(self, "_it_line", 1)
	___rawset(self, "_it_char", 0)
	___rawset(self, "_virtual_indent", 0)
	___rawset(self, "_move_acc_width", 0)
	___rawset(self, "_edit", edit)
end

function AUIPlugin.AUICodeCursor.__getter:line()
	return self._it_line
end

function AUIPlugin.AUICodeCursor.__getter:char()
	return self._it_char
end

function AUIPlugin.AUICodeCursor.__getter:virtual_indent()
	if self._virtual_indent == 0 then
		return ""
	end
	local indent = self._virtual_indent
	local indent_str = ""
	local i = 1
	while true do
		if not(i <= indent) then break end
		indent_str = indent_str .. " "
		i = i+(1)
	end
	return indent_str
end

function AUIPlugin.AUICodeCursor:Show(x, y)
	if self._loop == nil then
		self._loop = ALittle.LoopFunction(Lua.Bind(self.Update, self), -1, 1, 1)
	end
	if not A_LoopSystem:HasUpdater(self._loop) then
		A_LoopSystem:AddUpdater(self._loop)
	end
	self.visible = true
end

function AUIPlugin.AUICodeCursor:GetCurCharInLine()
	local line = self._edit.line_list[self._it_line]
	if line == nil then
		return nil
	end
	local index = self._it_char + 1
	if index > line.char_count then
		return nil
	end
	return line.char_list[index].char
end

function AUIPlugin.AUICodeCursor:GetNextCharInLine()
	local line = self._edit.line_list[self._it_line]
	if line == nil then
		return nil
	end
	local index = self._it_char + 2
	if index > line.char_count then
		return nil
	end
	return line.char_list[index].char
end

function AUIPlugin.AUICodeCursor:CalcSelectWord()
	local line = self._edit.line_list[self._it_line]
	if line == nil then
		return nil, nil
	end
	local count = line.char_count
	while count > 0 and line.char_list[count].width <= 0 do
		count = count - 1
	end
	local cur_char = line.char_list[self._it_char + 1]
	local is_word = ALittle.String_IsWordChar(cur_char.char)
	local it_end = self._it_char
	local i = self._it_char + 1
	while true do
		if not(i <= count) then break end
		if ALittle.String_IsWordChar(line.char_list[i].char) ~= is_word then
			break
		end
		it_end = i
		i = i+(1)
	end
	local it_start = self._it_char
	local i = self._it_char
	while true do
		if not(i >= 1) then break end
		if ALittle.String_IsWordChar(line.char_list[i].char) ~= is_word then
			break
		end
		it_start = i - 1
		i = i+(-1)
	end
	if it_start == it_end then
		return nil, nil
	end
	return it_start, it_end
end

function AUIPlugin.AUICodeCursor:SetOffsetXY(x, y, show)
	if self._edit.line_count <= 0 then
		self._it_line = 1
		self._it_char = 0
	else
		self._it_line, self._it_char = self._edit:CalcLineAndChar(x, y)
	end
	self.y = (self._it_line - 1) * AUIPlugin.CODE_LINE_HEIGHT
	local line = self._edit.line_list[self._it_line]
	if line == nil or self._it_char == 0 then
		self.x = 0
	else
		local char = line.char_list[self._it_char]
		self.x = char.pre_width + char.width
	end
	if show == nil or show then
		self:Show()
	end
	self._virtual_indent = 0
	self._move_acc_width = self.x
end

function AUIPlugin.AUICodeCursor:SetLineChar(it_line, it_char)
	self:SetLineCharInner(it_line, it_char)
	self._move_acc_width = self.x
end

function AUIPlugin.AUICodeCursor:SetLineCharInner(it_line, it_char)
	self._it_line = it_line
	self._it_char = it_char
	self.y = (self._it_line - 1) * AUIPlugin.CODE_LINE_HEIGHT
	local line = self._edit.line_list[self._it_line]
	if line == nil or self._it_char <= 0 then
		self.x = 0
	else
		self.x = line.char_list[self._it_char].pre_width + line.char_list[self._it_char].width
	end
	self._virtual_indent = 0
end

function AUIPlugin.AUICodeCursor:CurLineHasChar()
	local line = self._edit.line_list[self._it_line]
	if line == nil then
		return false
	end
	if line.char_count < 1 or line.char_list[1].char == "\r" or line.char_list[1].char == "\n" then
		return false
	end
	return true
end

function AUIPlugin.AUICodeCursor:AdjustShowCursor()
	local line = self._edit.line_list[self._it_line]
	if line == nil then
		return
	end
	if line.char_count < 1 or line.char_list[1].char == "\r" or line.char_list[1].char == "\n" then
		if self._edit.language ~= nil then
			self._virtual_indent = self._edit.language:QueryDesiredIndent(self._it_line, self._it_char)
			if self._virtual_indent > 0 then
				self.x = self._virtual_indent * self._edit.ascii_width
				if self.x > self._move_acc_width then
					self._move_acc_width = self.x
				end
			end
		end
	end
end

function AUIPlugin.AUICodeCursor:UpdateVirtualIndent()
	if self._edit.language ~= nil then
		self._virtual_indent = self._edit.language:QueryDesiredIndent(self._it_line, self._it_char)
	end
end

function AUIPlugin.AUICodeCursor:OffsetUp()
	if self._it_line <= 1 then
		return
	end
	local it_line = self._it_line - 1
	local line = self._edit.line_list[it_line]
	if line == nil then
		return
	end
	local it_char = line.char_count
	while it_char > 0 and line.char_list[it_char].width <= 0 do
		it_char = it_char - 1
	end
	while it_char > 0 do
		if line.char_list[it_char].pre_width + line.char_list[it_char].width <= self._move_acc_width then
			break
		end
		it_char = it_char - 1
	end
	self:SetLineCharInner(it_line, it_char)
end

function AUIPlugin.AUICodeCursor:OffsetDown()
	if self._it_line >= self._edit.line_count then
		return
	end
	local it_line = self._it_line + 1
	local line = self._edit.line_list[it_line]
	if line == nil then
		return
	end
	local it_char = line.char_count
	while it_char > 0 and line.char_list[it_char].width <= 0 do
		it_char = it_char - 1
	end
	while it_char > 0 do
		if line.char_list[it_char].pre_width + line.char_list[it_char].width <= self._move_acc_width then
			break
		end
		it_char = it_char - 1
	end
	self:SetLineCharInner(it_line, it_char)
end

function AUIPlugin.AUICodeCursor:OffsetLeft(ctrl)
	if self._it_char > 0 then
		if not ctrl then
			self:SetLineChar(self._it_line, self._it_char - 1)
			return
		end
		local line = self._edit.line_list[self._it_line]
		if line == nil then
			return
		end
		local cur_char = line.char_list[self._it_char]
		local is_word = ALittle.String_IsWordChar(cur_char.char)
		local it_char = self._it_char - 1
		while it_char > 0 do
			if ALittle.String_IsWordChar(line.char_list[it_char].char) ~= is_word then
				self:SetLineChar(self._it_line, it_char)
				return
			end
			it_char = it_char - 1
		end
		self:SetLineChar(self._it_line, 0)
		return
	end
	if self._it_line > 1 then
		local it_line = self._it_line - 1
		local line = self._edit.line_list[it_line]
		local it_char = line.char_count
		while it_char > 0 and line.char_list[it_char].width <= 0 do
			it_char = it_char - 1
		end
		self:SetLineChar(it_line, it_char)
		return
	end
	self:SetLineChar(1, 0)
end

function AUIPlugin.AUICodeCursor:OffsetRight(ctrl)
	if self._edit.line_count <= 0 then
		return
	end
	local line = self._edit.line_list[self._it_line]
	local count = line.char_count
	while count > 0 and line.char_list[count].width <= 0 do
		count = count - 1
	end
	if self._it_char < count then
		if not ctrl then
			self:SetLineChar(self._it_line, self._it_char + 1)
			return
		end
		local cur_char = line.char_list[self._it_char + 1]
		local is_word = ALittle.String_IsWordChar(cur_char.char)
		local it_char = self._it_char + 1
		while it_char <= count do
			if ALittle.String_IsWordChar(line.char_list[it_char + 1].char) ~= is_word then
				self:SetLineChar(self._it_line, it_char)
				return
			end
			it_char = it_char + 1
		end
		self:SetLineChar(self._it_line, count)
		return
	end
	if self._it_line >= self._edit.line_count then
		return
	end
	self:SetLineChar(self._it_line + 1, 0)
end

function AUIPlugin.AUICodeCursor:OffsetHome()
	if self._it_char <= 0 then
		return
	end
	local line = self._edit.line_list[self._it_line]
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
		self:SetLineChar(self._it_line, 0)
	else
		self:SetLineChar(self._it_line, it_char - 1)
	end
end

function AUIPlugin.AUICodeCursor:OffsetEnd()
	local line = self._edit.line_list[self._it_line]
	if line == nil then
		return
	end
	local count = line.char_count
	while count > 0 and line.char_list[count].width <= 0 do
		count = count - 1
	end
	if self._it_char < count then
		self:SetLineChar(self._it_line, count)
	end
end

function AUIPlugin.AUICodeCursor:DeleteLeft(need_revoke, revoke_bind)
	local old_it_line = self._it_line
	local old_it_char = self._it_char
	if self._it_char > 0 then
		local line = self._edit.line_list[self._it_line]
		if line == nil then
			return false
		end
		local char = line.char_list[self._it_char]
		local revoke_content = char.char
		if char.text ~= nil then
			line.container._text:RemoveChild(char.text)
		end
		line.char_count = line.char_count - (1)
		ALittle.List_Remove(line.char_list, self._it_char)
		local i = self._it_char
		while true do
			if not(i <= line.char_count) then break end
			line.char_list[i].pre_width = line.char_list[i].pre_width - (char.width)
			if line.char_list[i].text ~= nil then
				line.char_list[i].text.x = line.char_list[i].text.x - (char.width)
			end
			i = i+(1)
		end
		self:SetLineChar(self._it_line, self._it_char - 1)
		if self._edit.language ~= nil then
			self._edit.language:DeleteText(self._it_line, self._it_char, self._it_line, self._it_char)
		end
		local last_char = line.char_list[line.char_count]
		if last_char ~= nil then
			line.container.width = last_char.pre_width + last_char.width
		else
			line.container.width = 0
		end
		local rejust = true
		for index, line_info in ___ipairs(self._edit.line_list) do
			if line_info.container.width > line.container.width then
				rejust = false
				break
			end
		end
		if rejust then
			self._edit.code_screen.container.width = line.container.width + AUIPlugin.CODE_LINE_NUMBER_WIDTH
			self._edit.code_screen:AdjustScrollBar()
		end
		if need_revoke then
			local new_it_line = self._it_line
			local new_it_char = self._it_char
			local revoke = AUIPlugin.AUICodeDeleteLeftRevoke(self._edit, self, old_it_line, old_it_char, new_it_line, new_it_char, revoke_content, revoke_bind == nil)
			if revoke_bind ~= nil then
				revoke_bind:PushRevoke(revoke)
			else
				self._edit.revoke_list:PushRevoke(revoke)
			end
		end
		self._edit:UpdateLineFind(self._it_line)
		return true
	end
	if self._it_line <= 1 then
		return false
	end
	local pre_line = self._edit.line_list[self._it_line - 1]
	if pre_line == nil then
		return false
	end
	local cur_line = self._edit.line_list[self._it_line]
	if cur_line == nil then
		return false
	end
	local old_char_count = pre_line.char_count
	local it_char = pre_line.char_count
	local revoke_content = ""
	while it_char > 0 and pre_line.char_list[it_char].width <= 0 do
		revoke_content = pre_line.char_list[it_char].char .. revoke_content
		pre_line.char_count = pre_line.char_count - (1)
		pre_line.char_list[it_char] = nil
		it_char = it_char - (1)
	end
	local new_it_line = self._it_line - 1
	local new_it_char = it_char
	if self._edit.language ~= nil then
		self._edit.language:DeleteText(new_it_line, new_it_char, new_it_line, old_char_count - 1)
	end
	local pre_width = 0.0
	if pre_line.char_count > 0 then
		local last_char = pre_line.char_list[pre_line.char_count]
		pre_width = last_char.pre_width + last_char.width
	end
	local i = 1
	while true do
		if not(i <= cur_line.char_count) then break end
		local char = cur_line.char_list[i]
		char.pre_width = pre_width
		if char.text ~= nil then
			char.text.x = pre_width
		end
		pre_line.container:AddChar(char)
		pre_width = pre_width + (char.width)
		pre_line.char_count = pre_line.char_count + (1)
		pre_line.char_list[pre_line.char_count] = char
		i = i+(1)
	end
	pre_line.container.width = pre_width
	self._edit.code_linear:RemoveChild(cur_line.container)
	self._edit.line_count = self._edit.line_count - (1)
	ALittle.List_Remove(self._edit.line_list, self._it_line)
	self:SetLineChar(new_it_line, new_it_char)
	if self._edit.code_screen.container.width < pre_line.container.width + AUIPlugin.CODE_LINE_NUMBER_WIDTH then
		self._edit.code_screen.container.width = pre_line.container.width + AUIPlugin.CODE_LINE_NUMBER_WIDTH
	end
	self._edit.code_screen:AdjustScrollBar()
	if need_revoke then
		local revoke = AUIPlugin.AUICodeDeleteLeftRevoke(self._edit, self, old_it_line, old_it_char, new_it_line, new_it_char, revoke_content, revoke_bind == nil)
		if revoke_bind ~= nil then
			revoke_bind:PushRevoke(revoke)
		else
			self._edit.revoke_list:PushRevoke(revoke)
		end
	end
	self._edit:UpdateLineFind(self._it_line)
	self._edit:UpdateLineNumber()
	return true
end

function AUIPlugin.AUICodeCursor:DeleteRight(need_revoke, revoke_bind)
	local old_it_line = self._it_line
	local old_it_char = self._it_char
	local line = self._edit.line_list[self._it_line]
	if line == nil then
		return false
	end
	local count = line.char_count
	while count > 0 and line.char_list[count].width <= 0 do
		count = count - 1
	end
	if self._it_char < count then
		if self._edit.language ~= nil then
			self._edit.language:DeleteText(self._it_line, self._it_char, self._it_line, self._it_char)
		end
		local char = line.char_list[self._it_char + 1]
		local revoke_content = char.char
		if char.text ~= nil then
			line.container._text:RemoveChild(char.text)
		end
		line.char_count = line.char_count - (1)
		ALittle.List_Remove(line.char_list, self._it_char + 1)
		local i = self._it_char + 1
		while true do
			if not(i <= line.char_count) then break end
			line.char_list[i].pre_width = line.char_list[i].pre_width - (char.width)
			if line.char_list[i].text ~= nil then
				line.char_list[i].text.x = line.char_list[i].text.x - (char.width)
			end
			i = i+(1)
		end
		self:SetLineChar(self._it_line, self._it_char)
		local last_char = line.char_list[line.char_count]
		if last_char ~= nil then
			line.container.width = last_char.pre_width + last_char.width
		else
			line.container.width = 0
		end
		local rejust = true
		for index, line_info in ___ipairs(self._edit.line_list) do
			if line_info.container.width > line.container.width then
				rejust = false
				break
			end
		end
		if rejust then
			self._edit.code_screen.container.width = line.container.width + AUIPlugin.CODE_LINE_NUMBER_WIDTH
			self._edit.code_screen:AdjustScrollBar()
		end
		local new_it_line = self._it_line
		local new_it_char = self._it_char
		if need_revoke then
			local revoke = AUIPlugin.AUICodeDeleteRightRevoke(self._edit, self, old_it_line, old_it_char, new_it_line, new_it_char, revoke_content, revoke_bind == nil)
			if revoke_bind ~= nil then
				revoke_bind:PushRevoke(revoke)
			else
				self._edit.revoke_list:PushRevoke(revoke)
			end
		end
		self._edit:UpdateLineFind(self._it_line)
		return true
	end
	if self._it_line >= self._edit.line_count then
		return false
	end
	local cur_line = line
	local next_line = self._edit.line_list[self._it_line + 1]
	if next_line == nil then
		return false
	end
	local old_char_count = cur_line.char_count
	local it_char = cur_line.char_count
	local revoke_content = ""
	while it_char > 0 and (cur_line.char_list[it_char].char == "\r" or cur_line.char_list[it_char].char == "\n") do
		revoke_content = cur_line.char_list[it_char].char .. revoke_content
		cur_line.char_count = cur_line.char_count - (1)
		cur_line.char_list[it_char] = nil
		it_char = it_char - (1)
	end
	local new_it_line = self._it_line
	local new_it_char = it_char
	if self._edit.language ~= nil then
		self._edit.language:DeleteText(self._it_line, it_char, self._it_line, old_char_count - 1)
	end
	local pre_width = 0.0
	if cur_line.char_count > 0 then
		local last_char = cur_line.char_list[cur_line.char_count]
		pre_width = last_char.pre_width + last_char.width
	end
	local i = 1
	while true do
		if not(i <= next_line.char_count) then break end
		local char = next_line.char_list[i]
		char.pre_width = pre_width
		if char.text ~= nil then
			char.text.x = pre_width
		end
		cur_line.container:AddChar(char)
		pre_width = pre_width + (char.width)
		cur_line.char_count = cur_line.char_count + (1)
		cur_line.char_list[cur_line.char_count] = char
		i = i+(1)
	end
	cur_line.container.width = pre_width
	self._edit.code_linear:RemoveChild(next_line.container)
	self._edit.line_count = self._edit.line_count - (1)
	ALittle.List_Remove(self._edit.line_list, self._it_line + 1)
	self:SetLineChar(new_it_line, new_it_char)
	if self._edit.code_screen.container.width < cur_line.container.width + AUIPlugin.CODE_LINE_NUMBER_WIDTH then
		self._edit.code_screen.container.width = cur_line.container.width + AUIPlugin.CODE_LINE_NUMBER_WIDTH
	end
	self._edit.code_screen:AdjustScrollBar()
	if need_revoke then
		local revoke = AUIPlugin.AUICodeDeleteRightRevoke(self._edit, self, old_it_line, old_it_char, new_it_line, new_it_char, revoke_content, revoke_bind == nil)
		if revoke_bind ~= nil then
			revoke_bind:PushRevoke(revoke)
		else
			self._edit.revoke_list:PushRevoke(revoke)
		end
	end
	self._edit:UpdateLineFind(self._it_line)
	self._edit:UpdateLineNumber()
	return true
end

function AUIPlugin.AUICodeCursor:Hide()
	if self._loop ~= nil then
		self._loop:Stop()
		self._loop = nil
	end
	self.visible = false
end

function AUIPlugin.AUICodeCursor:Update()
	if self.abs_visible then
		self._flash_alpha = self._flash_alpha + self._flash_dir
		if (self._flash_dir < 0 and self._flash_alpha < -0.05) or (self._flash_dir > 0 and self._flash_alpha > 1.5) then
			self._flash_dir = -self._flash_dir
		end
		self.alpha = self._flash_alpha
	end
end

end