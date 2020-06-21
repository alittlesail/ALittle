-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


AUICodeSelectCursor = Lua.Class(nil, "AUIPlugin.AUICodeSelectCursor")

function AUICodeSelectCursor:Ctor(edit)
	___rawset(self, "_clear_quad", true)
	___rawset(self, "_edit", edit)
end

function AUICodeSelectCursor:ClearQuad()
	if self._clear_quad then
		return
	end
	self._clear_quad = true
	if self._it_line_start ~= nil and self._it_line_end ~= nil then
		if self._it_line_start < self._it_line_end then
			local i = self._it_line_start
			while true do
				if not(i <= self._it_line_end) then break end
				self._edit.line_list[i].quad.visible = false
				i = i+(1)
			end
		else
			local i = self._it_line_end
			while true do
				if not(i <= self._it_line_start) then break end
				self._edit.line_list[i].quad.visible = false
				i = i+(1)
			end
		end
	end
end

function AUICodeSelectCursor:SetQuad()
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
		line.quad.visible = true
		self._clear_quad = false
		line.quad.x = line.char_list[it_char_start + 1].pre_width
		line.quad.width = line.char_list[it_char_end].pre_width + line.char_list[it_char_end].width - line.quad.x
		return
	end
	local i = it_line_start
	while true do
		if not(i <= it_line_end) then break end
		local line = self._edit.line_list[i]
		if line.char_count > 0 then
			if i == it_line_start then
				if it_char_start < line.char_count then
					line.quad.visible = true
					self._clear_quad = false
					line.quad.x = line.char_list[it_char_start + 1].pre_width
					line.quad.width = line.container.width - line.quad.x
				end
			elseif i == it_line_end then
				if it_char_end > 0 then
					line.quad.visible = true
					self._clear_quad = false
					line.quad.x = 0
					line.quad.width = line.char_list[it_char_end].pre_width + line.char_list[it_char_end].width
				end
			else
				line.quad.visible = true
				self._clear_quad = false
				line.quad.x = 0
				line.quad.width = line.container.width
			end
		end
		i = i+(1)
	end
end

function AUICodeSelectCursor.__getter:line_start()
	return self._it_line_start
end

function AUICodeSelectCursor.__getter:char_start()
	return self._it_char_start
end

function AUICodeSelectCursor.__getter:line_end()
	return self._it_line_end
end

function AUICodeSelectCursor.__getter:char_end()
	return self._it_char_end
end

function AUICodeSelectCursor:StartLineChar(line, char)
	self:Hide()
	if self._edit.line_count == 0 then
		return
	end
	self._it_line_start = line
	self._it_char_start = char
end

function AUICodeSelectCursor:UpdateLineChar(line, char)
	self:ClearQuad()
	self._it_line_end = line
	self._it_char_end = char
	self:SetQuad()
end

function AUICodeSelectCursor:StartOffsetXY(x, y)
	self:Hide()
	if self._edit.line_count == 0 then
		return
	end
	self._it_line_start, self._it_char_start = self._edit:CalcLineAndChar(x, y)
end

function AUICodeSelectCursor:UpdateOffsetXY(x, y)
	self:ClearQuad()
	if self._it_line_start == nil then
		return
	end
	self._it_line_end, self._it_char_end = self._edit:CalcLineAndChar(x, y)
	self:SetQuad()
end

function AUICodeSelectCursor:GetSelectText()
	if self._it_line_start == nil then
		return nil
	end
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
			return ""
		end
		local line = self._edit.line_list[it_line_start]
		if line.char_count == 0 then
			return ""
		end
		local text = ""
		local i = it_char_start + 1
		while true do
			if not(i <= it_char_end) then break end
			text = text .. line.char_list[i].char
			i = i+(1)
		end
		return text
	end
	local text = ""
	local i = it_line_start
	while true do
		if not(i <= it_line_end) then break end
		local line = self._edit.line_list[i]
		if line.char_count > 0 then
			if i == it_line_start then
				if it_char_start < line.char_count then
					local j = it_char_start + 1
					while true do
						if not(j <= line.char_count) then break end
						text = text .. line.char_list[j].char
						j = j+(1)
					end
				end
			elseif i == it_line_end then
				if it_char_end > 0 then
					local j = 1
					while true do
						if not(j <= it_char_end) then break end
						text = text .. line.char_list[j].char
						j = j+(1)
					end
				end
			else
				local j = 1
				while true do
					if not(j <= line.char_count) then break end
					text = text .. line.char_list[j].char
					j = j+(1)
				end
			end
		end
		i = i+(1)
	end
	return text
end

function AUICodeSelectCursor:DeleteSelect()
	if self._it_line_start == nil then
		return false, nil, nil
	end
	if self._it_line_start == self._it_line_end then
		if self._it_char_start == self._it_char_end then
			self:Hide()
			return false, nil, nil
		end
		local line = self._edit.line_list[self._it_line_start]
		if line == nil then
			return false, nil, nil
		end
		local it_line_start = self._it_line_start
		local it_char_start = self._it_char_start
		local it_char_end = self._it_char_end
		if it_char_start > it_char_end then
			local temp = it_char_start
			it_char_start = it_char_end
			it_char_end = temp
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
		local i = it_char_start + 1
		while true do
			if not(i <= it_char_end) then break end
			local char = line.char_list[i]
			if char.text ~= nil then
				line.container:RemoveChild(char.text)
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
		for index, line_info in ___ipairs(self._edit.line_list) do
			if line_info.container.width > line.container.width then
				rejust = false
				break
			end
		end
		if rejust then
			self._edit.container.width = line.container.width
			self._edit:RejustScrollBar()
		end
		return true, it_line_start, it_char_start
	end
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
	self:Hide()
	local line_count = it_line_end - it_line_start - 1
	if line_count > 0 then
		local it_line = it_line_start + 1
		while true do
			if not(it_line < it_line_end) then break end
			self._edit.code_linear:RemoveChild(self._edit.line_list[it_line].container)
			it_line = it_line+(1)
		end
		ALittle.List_Splice(self._edit.line_list, it_line_start + 1, line_count)
		self._edit.line_count = self._edit.line_count - (line_count)
		it_line_end = it_line_end - (line_count)
	end
	local start_line = self._edit.line_list[it_line_start]
	local it_char = it_char_start + 1
	while true do
		if not(it_char <= start_line.char_count) then break end
		local char = start_line.char_list[it_char]
		if char.text ~= nil then
			start_line.container:RemoveChild(char.text)
		end
		it_char = it_char+(1)
	end
	local count = start_line.char_count - it_char_start
	start_line.char_count = start_line.char_count - (count)
	ALittle.List_Splice(start_line.char_list, it_char_start + 1, count)
	local end_line = self._edit.line_list[it_line_end]
	local pre_width = 0.0
	local last_char = start_line.char_list[start_line.char_count]
	if last_char ~= nil then
		pre_width = last_char.pre_width + last_char.width
	end
	local i = it_char_end + 1
	while true do
		if not(i <= end_line.char_count) then break end
		local char = end_line.char_list[i]
		char.pre_width = pre_width
		if char.text ~= nil then
			char.text.x = pre_width
			start_line.container:AddChild(char.text)
		elseif char.width > 0 then
			start_line.container:Dirty()
		end
		pre_width = pre_width + (char.width)
		start_line.char_count = start_line.char_count + (1)
		start_line.char_list[start_line.char_count] = char
		i = i+(1)
	end
	start_line.container.width = pre_width
	self._edit.code_linear:RemoveChild(end_line.container)
	self._edit.line_count = self._edit.line_count - (1)
	ALittle.List_Remove(self._edit.line_list, it_line_end)
	local max_width = 0.0
	local text = ""
	for index, line in ___ipairs(self._edit.line_list) do
		if max_width < line.container.width then
			max_width = line.container.width
		end
		text = text .. index
		for kk, char in ___ipairs(line.char_list) do
			text = text .. char.char
		end
	end
	self._edit.container.width = max_width
	self._edit:RejustScrollBar()
	return true, it_line_start, it_char_start
end

function AUICodeSelectCursor:TryHide()
	if self._it_line_start == nil or self._it_line_end == nil or self._it_char_start == nil or self._it_char_end == nil then
		self:Hide()
		return
	end
	if self._it_line_start == self._it_line_end and self._it_char_start == self._it_char_end then
		self:Hide()
		return
	end
end

function AUICodeSelectCursor:Hide()
	self:ClearQuad()
	self._clear_quad = true
	self._it_line_start = nil
	self._it_char_start = nil
	self._it_line_end = nil
	self._it_char_end = nil
end

