-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.AUIPlugin == nil then _G.AUIPlugin = {} end
local AUIPlugin = AUIPlugin
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


AUIPlugin.AUICodeSelectCursor = Lua.Class(nil, "AUIPlugin.AUICodeSelectCursor")

function AUIPlugin.AUICodeSelectCursor:Ctor(edit)
	___rawset(self, "_clear_quad", true)
	___rawset(self, "_edit", edit)
end

function AUIPlugin.AUICodeSelectCursor:ClearQuad()
	if self._clear_quad then
		return
	end
	self._clear_quad = true
	if self._it_line_start ~= nil and self._it_line_end ~= nil then
		if self._it_line_start < self._it_line_end then
			local line_list = self._edit.line_list
			local it_line_end = self._it_line_end
			local i = self._it_line_start
			while true do
				if not(i <= it_line_end) then break end
				line_list[i].container._select.visible = false
				i = i+(1)
			end
		else
			local line_list = self._edit.line_list
			local it_line_start = self._it_line_start
			local i = self._it_line_end
			while true do
				if not(i <= it_line_start) then break end
				line_list[i].container._select.visible = false
				i = i+(1)
			end
		end
	end
end

function AUIPlugin.AUICodeSelectCursor:SetQuad()
	local it_line_start = self._it_line_start
	local it_char_start = self._it_char_start
	local it_line_end = self._it_line_end
	local it_char_end = self._it_char_end
	local swap = false
	if it_line_start > it_line_end then
		swap = true
	elseif it_line_start == it_line_end then
		swap = it_char_start > it_char_end
	end
	if swap then
		local temp = it_line_start
		it_line_start = it_line_end
		it_line_end = temp
		temp = it_char_start
		it_char_start = it_char_end
		it_char_end = temp
	end
	if it_line_start == it_line_end then
		if self._it_char_start == self._it_char_end then
			return
		end
		local line = self._edit.line_list[it_line_start]
		if line.char_count == 0 then
			return
		end
		line.container._select.visible = true
		self._clear_quad = false
		line.container._select.x = line.char_list[it_char_start + 1].pre_width
		line.container._select.width = line.char_list[it_char_end].pre_width + line.char_list[it_char_end].width - line.container._select.x
		return
	end
	local line_list = self._edit.line_list
	local i = it_line_start
	while true do
		if not(i <= it_line_end) then break end
		local line = line_list[i]
		if line.char_count > 0 then
			if i == it_line_start then
				if it_char_start < line.char_count then
					line.container._select.visible = true
					self._clear_quad = false
					line.container._select.x = line.char_list[it_char_start + 1].pre_width
					line.container._select.width = line.container.width - line.container._select.x
				end
			elseif i == it_line_end then
				if it_char_end > 0 then
					line.container._select.visible = true
					self._clear_quad = false
					line.container._select.x = 0
					line.container._select.width = line.char_list[it_char_end].pre_width + line.char_list[it_char_end].width
				end
			else
				line.container._select.visible = true
				self._clear_quad = false
				line.container._select.x = 0
				line.container._select.width = line.container.width
			end
			if line.container._select.width <= 0 then
				line.container._select.width = self._edit.ascii_width
			end
		else
			line.container._select.visible = true
			self._clear_quad = false
			line.container._select.x = 0
			line.container._select.width = self._edit.ascii_width
		end
		i = i+(1)
	end
end

function AUIPlugin.AUICodeSelectCursor.__getter:line_start()
	return self._it_line_start
end

function AUIPlugin.AUICodeSelectCursor.__getter:char_start()
	return self._it_char_start
end

function AUIPlugin.AUICodeSelectCursor.__getter:line_end()
	return self._it_line_end
end

function AUIPlugin.AUICodeSelectCursor.__getter:char_end()
	return self._it_char_end
end

function AUIPlugin.AUICodeSelectCursor:GetLineCharCloseToEnd()
	if self._it_line_start < self._it_line_end then
		return self._it_line_end, self._it_char_end
	end
	if self._it_line_start > self._it_line_end then
		return self._it_line_start, self._it_char_start
	end
	if self._it_char_start < self._it_char_end then
		return self._it_line_end, self._it_char_end
	end
	return self._it_line_start, self._it_char_start
end

function AUIPlugin.AUICodeSelectCursor:GetLineCharCloseToHome()
	if self._it_line_start > self._it_line_end then
		return self._it_line_end, self._it_char_end
	end
	if self._it_line_start < self._it_line_end then
		return self._it_line_start, self._it_char_start
	end
	if self._it_char_start > self._it_char_end then
		return self._it_line_end, self._it_char_end
	end
	return self._it_line_start, self._it_char_start
end

function AUIPlugin.AUICodeSelectCursor:StartLineChar(line, char)
	self:Hide()
	if self._edit.line_count == 0 then
		return
	end
	self._it_line_start = line
	self._it_char_start = char
end

function AUIPlugin.AUICodeSelectCursor:UpdateLineChar(it_line, it_char)
	self:ClearQuad()
	self._it_line_end = it_line
	local line = self._edit.line_list[it_line]
	if line == nil then
		self._it_char_end = 0
	elseif line.char_count < it_char then
		self._it_line_end = line.char_count
	else
		self._it_char_end = it_char
	end
	self:SetQuad()
end

function AUIPlugin.AUICodeSelectCursor:StartOffsetXY(x, y)
	self:Hide()
	if self._edit.line_count == 0 then
		return
	end
	self._it_line_start, self._it_char_start = self._edit:CalcLineAndChar(x, y)
end

function AUIPlugin.AUICodeSelectCursor:UpdateOffsetXY(x, y)
	self:ClearQuad()
	if self._it_line_start == nil then
		return
	end
	self._it_line_end, self._it_char_end = self._edit:CalcLineAndChar(x, y)
	self:SetQuad()
end

function AUIPlugin.AUICodeSelectCursor:GetTargetText(it_line_start, it_char_start, it_line_end, it_char_end)
	local swap = false
	if it_line_start > it_line_end then
		swap = true
	elseif it_line_start == it_line_end then
		swap = it_char_start > it_char_end
	end
	if swap then
		local temp = it_line_start
		it_line_start = it_line_end
		it_line_end = temp
		temp = it_char_start
		it_char_start = it_char_end
		it_char_end = temp
	end
	if it_line_start == it_line_end then
		if it_char_start == it_char_end then
			return ""
		end
		local line = self._edit.line_list[it_line_start]
		if line.char_count == 0 then
			return ""
		end
		local text = {}
		local text_count = 0
		local i = it_char_start + 1
		while true do
			if not(i <= it_char_end) then break end
			text_count = text_count + 1
			text[text_count] = line.char_list[i].char
			i = i+(1)
		end
		return ALittle.String_Join(text, "")
	end
	local text = {}
	local text_count = 0
	local i = it_line_start
	while true do
		if not(i <= it_line_end) then break end
		local line = self._edit.line_list[i]
		if line.char_count > 0 then
			if i == it_line_start then
				local j = it_char_start + 1
				while true do
					if not(j <= line.char_count) then break end
					text_count = text_count + 1
					text[text_count] = line.char_list[j].char
					j = j+(1)
				end
			elseif i == it_line_end then
				local j = 1
				while true do
					if not(j <= it_char_end) then break end
					text_count = text_count + 1
					text[text_count] = line.char_list[j].char
					j = j+(1)
				end
			else
				local j = 1
				while true do
					if not(j <= line.char_count) then break end
					text_count = text_count + 1
					text[text_count] = line.char_list[j].char
					j = j+(1)
				end
			end
		end
		i = i+(1)
	end
	return ALittle.String_Join(text, "")
end

function AUIPlugin.AUICodeSelectCursor:GetSelectText()
	if self._it_line_start == nil then
		return nil
	end
	return self:GetTargetText(self._it_line_start, self._it_char_start, self._it_line_end, self._it_char_end)
end

function AUIPlugin.AUICodeSelectCursor:DeleteSelect(need_revoke, revoke_bind)
	if self._it_line_start == nil then
		return false, nil, nil
	end
	local edit_line_list = self._edit.line_list
	if self._it_line_start == self._it_line_end then
		if self._it_char_start == self._it_char_end then
			self:Hide()
			return false, nil, nil
		end
		local line = edit_line_list[self._it_line_start]
		if line == nil then
			return false, nil, nil
		end
		local old_it_line_start = self._it_line_start
		local old_it_char_start = self._it_char_start
		local old_it_line_end = self._it_line_end
		local old_it_char_end = self._it_char_end
		local it_line_start = self._it_line_start
		local it_char_start = self._it_char_start
		local it_char_end = self._it_char_end
		if it_char_start > it_char_end then
			local temp = it_char_start
			it_char_start = it_char_end
			it_char_end = temp
		end
		if self._edit.language ~= nil then
			self._edit.language:DeleteText(it_line_start, it_char_start, it_line_start, it_char_end - 1)
		end
		self:Hide()
		local acc_width = 0.0
		local i = it_char_start + 1
		while true do
			if not(i <= it_char_end) then break end
			acc_width = acc_width + (line.char_list[i].width)
			i = i+(1)
		end
		local i = it_char_end + 1
		while true do
			if not(i <= line.char_count) then break end
			local char = line.char_list[i]
			char.pre_width = char.pre_width - (acc_width)
			if char.text ~= nil then
				char.text.x = char.text.x - (acc_width)
			end
			i = i+(1)
		end
		local revoke_content = ""
		local i = it_char_start + 1
		while true do
			if not(i <= it_char_end) then break end
			local char = line.char_list[i]
			revoke_content = revoke_content .. char.char
			if char.text ~= nil then
				line.container._text:RemoveChild(char.text)
			end
			i = i+(1)
		end
		local count = it_char_end - it_char_start
		line.char_count = line.char_count - (count)
		ALittle.List_Splice(line.char_list, it_char_start + 1, count)
		local last_char = line.char_list[line.char_count]
		if last_char ~= nil then
			line.container.width = last_char.pre_width + last_char.width
		else
			line.container.width = 0
		end
		local rejust = true
		for index, line_info in ___ipairs(edit_line_list) do
			if line_info.container.width > line.container.width then
				rejust = false
				break
			end
		end
		if rejust then
			self._edit:AdjustCodeScreen(line.container.width + AUIPlugin.CODE_LINE_NUMBER_WIDTH)
		end
		if need_revoke then
			local revoke = AUIPlugin.AUICodeDeleteSelectRevoke(self._edit, self._edit.cursor, self, old_it_line_start, old_it_char_start, old_it_line_end, old_it_char_end, it_line_start, it_char_start, revoke_content, revoke_bind == nil)
			if revoke_bind ~= nil then
				revoke_bind:PushRevoke(revoke)
			else
				self._edit.revoke_list:PushRevoke(revoke)
			end
		end
		self._edit:UpdateLineFind(it_line_start)
		return true, it_line_start, it_char_start
	end
	local old_it_line_start = self._it_line_start
	local old_it_char_start = self._it_line_start
	local old_it_line_end = self._it_line_end
	local old_it_char_end = self._it_char_end
	local it_line_start = self._it_line_start
	local it_char_start = self._it_char_start
	local it_line_end = self._it_line_end
	local it_char_end = self._it_char_end
	if it_line_start > it_line_end then
		local temp = it_line_start
		it_line_start = it_line_end
		it_line_end = temp
		temp = it_char_start
		it_char_start = it_char_end
		it_char_end = temp
	end
	if self._edit.language ~= nil then
		local delete_line_end = it_line_end
		local delete_char_end = it_char_end - 1
		if delete_char_end < 0 then
			delete_line_end = delete_line_end - (1)
			delete_char_end = edit_line_list[delete_line_end].char_count - 1
		end
		self._edit.language:DeleteText(it_line_start, it_char_start, delete_line_end, delete_char_end)
	end
	self:Hide()
	local revoke_center = {}
	local revoke_c_count = 0
	local line_count = it_line_end - it_line_start - 1
	if line_count > 0 then
		local it_line = it_line_start + 1
		while true do
			if not(it_line < it_line_end) then break end
			local line = edit_line_list[it_line]
			local it_char = 1
			while true do
				if not(it_char <= line.char_count) then break end
				revoke_c_count = revoke_c_count + (1)
				revoke_center[revoke_c_count] = line.char_list[it_char].char
				it_char = it_char+(1)
			end
			it_line = it_line+(1)
		end
		self._edit.code_linear:SpliceChild(it_line_start + 1, line_count)
		ALittle.List_Splice(edit_line_list, it_line_start + 1, line_count)
		self._edit.line_count = self._edit.line_count - (line_count)
		it_line_end = it_line_end - (line_count)
	end
	local revoke_start = ""
	local start_line = edit_line_list[it_line_start]
	local it_char = it_char_start + 1
	while true do
		if not(it_char <= start_line.char_count) then break end
		local char = start_line.char_list[it_char]
		revoke_start = revoke_start .. char.char
		if char.text ~= nil then
			start_line.container._text:RemoveChild(char.text)
		end
		it_char = it_char+(1)
	end
	local count = start_line.char_count - it_char_start
	start_line.char_count = start_line.char_count - (count)
	ALittle.List_Splice(start_line.char_list, it_char_start + 1, count)
	local end_line = edit_line_list[it_line_end]
	local pre_width = 0.0
	local last_char = start_line.char_list[start_line.char_count]
	if last_char ~= nil then
		pre_width = last_char.pre_width + last_char.width
	end
	local revoke_end = ""
	local i = 1
	while true do
		if not(i <= it_char_end) then break end
		revoke_end = revoke_end .. end_line.char_list[i].char
		i = i+(1)
	end
	local i = it_char_end + 1
	while true do
		if not(i <= end_line.char_count) then break end
		local char = end_line.char_list[i]
		char.pre_width = pre_width
		if char.text ~= nil then
			char.text.x = pre_width
		end
		start_line.container:AddChar(char)
		pre_width = pre_width + (char.width)
		start_line.char_count = start_line.char_count + (1)
		start_line.char_list[start_line.char_count] = char
		i = i+(1)
	end
	start_line.container.width = pre_width
	self._edit.code_linear:RemoveChild(end_line.container)
	self._edit.line_count = self._edit.line_count - (1)
	ALittle.List_Remove(edit_line_list, it_line_end)
	local max_width = 0.0
	for index, line in ___ipairs(edit_line_list) do
		if max_width < line.container.width then
			max_width = line.container.width
		end
	end
	self._edit:AdjustCodeScreen(max_width)
	if need_revoke then
		local revoke = AUIPlugin.AUICodeDeleteSelectRevoke(self._edit, self._edit.cursor, self, old_it_line_start, old_it_char_start, old_it_line_end, old_it_char_end, it_line_start, it_char_start, revoke_start .. ALittle.String_Join(revoke_center, "") .. revoke_end, revoke_bind == nil)
		if revoke_bind ~= nil then
			revoke_bind:PushRevoke(revoke)
		else
			self._edit.revoke_list:PushRevoke(revoke)
		end
	end
	local i = it_line_start
	while true do
		if not(i <= it_line_end) then break end
		self._edit:UpdateLineFind(i)
		i = i+(1)
	end
	self._edit:UpdateLineNumber()
	return true, it_line_start, it_char_start
end

function AUIPlugin.AUICodeSelectCursor:TryHide()
	if self._it_line_start == nil or self._it_line_end == nil or self._it_char_start == nil or self._it_char_end == nil then
		self:Hide()
		return
	end
	if self._it_line_start == self._it_line_end and self._it_char_start == self._it_char_end then
		self:Hide()
		return
	end
end

function AUIPlugin.AUICodeSelectCursor:Hide()
	self:ClearQuad()
	self._clear_quad = true
	self._it_line_start = nil
	self._it_char_start = nil
	self._it_line_end = nil
	self._it_char_end = nil
end

end