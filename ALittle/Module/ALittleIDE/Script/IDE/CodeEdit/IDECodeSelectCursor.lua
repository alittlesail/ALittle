-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


IDECodeSelectCursor = Lua.Class(nil, "ALittleIDE.IDECodeSelectCursor")

function IDECodeSelectCursor:Ctor(tab_child)
	___rawset(self, "_clear_quad", true)
	___rawset(self, "_tab_child", tab_child)
end

function IDECodeSelectCursor:ClearQuad()
	if self._clear_quad then
		return
	end
	self._clear_quad = true
	if self._it_line_start ~= nil and self._it_line_end ~= nil then
		if self._it_line_start < self._it_line_end then
			local i = self._it_line_start
			while true do
				if not(i <= self._it_line_end) then break end
				self._tab_child.line_list[i].quad.visible = false
				i = i+(1)
			end
		else
			local i = self._it_line_end
			while true do
				if not(i <= self._it_line_start) then break end
				self._tab_child.line_list[i].quad.visible = false
				i = i+(1)
			end
		end
	end
end

function IDECodeSelectCursor:SetQuad()
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
		local line = self._tab_child.line_list[it_line_start]
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
		local line = self._tab_child.line_list[i]
		if line.char_count > 0 then
			if i == it_line_start then
				if it_char_start < line.char_count then
					line.quad.visible = true
					self._clear_quad = false
					line.quad.x = line.char_list[it_char_start + 1].pre_width
					line.quad.width = line.width - line.quad.x
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
				line.quad.width = line.width
			end
		end
		i = i+(1)
	end
end

function IDECodeSelectCursor.__getter:line_start()
	return self._it_line_start
end

function IDECodeSelectCursor.__getter:char_start()
	return self._it_char_start
end

function IDECodeSelectCursor.__getter:line_end()
	return self._it_line_end
end

function IDECodeSelectCursor.__getter:char_end()
	return self._it_char_end
end

function IDECodeSelectCursor:StartLineChar(line, char)
	self:Hide()
	if self._tab_child.line_count == 0 then
		return
	end
	self._it_line_start = line
	self._it_char_start = char
end

function IDECodeSelectCursor:UpdateLineChar(line, char)
	self:ClearQuad()
	if self._it_line_start == nil then
		return
	end
	self._it_line_end = line
	self._it_char_end = char
	self:SetQuad()
end

function IDECodeSelectCursor:StartOffsetXY(x, y)
	self:Hide()
	if self._tab_child.line_count == 0 then
		return
	end
	self._it_line_start, self._it_char_start = self._tab_child:CalcLineAndChar(x, y)
end

function IDECodeSelectCursor:UpdateOffsetXY(x, y)
	self:ClearQuad()
	if self._it_line_start == nil then
		return
	end
	self._it_line_end, self._it_char_end = self._tab_child:CalcLineAndChar(x, y)
	self:SetQuad()
end

function IDECodeSelectCursor:GetSelectText()
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
		local line = self._tab_child.line_list[it_line_start]
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
		local line = self._tab_child.line_list[i]
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

function IDECodeSelectCursor:Hide()
	self:ClearQuad()
	self._clear_quad = true
	self._it_line_start = nil
	self._it_char_start = nil
	self._it_line_end = nil
	self._it_char_end = nil
end

