-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(485812343, "ALittle.RichAreaLineInfo", {
name = "ALittle.RichAreaLineInfo", ns_name = "ALittle", rl_name = "RichAreaLineInfo", hash_code = 485812343,
name_list = {"childs","child_count","height","width"},
type_list = {"List<ALittle.DisplayObject>","int","double","double"},
option_map = {}
})

local __find = ALittle.String_Find
local __sub = ALittle.String_Sub
local __floor = ALittle.Math_Floor
assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
ALittle.RichArea = Lua.Class(ALittle.DisplayLayout, "ALittle.RichArea")

function ALittle.RichArea:SplitText(char_info, char_info_list, char_info_list_count)
	local text = char_info.text
	while true do
		local start_index_1 = __find(text, "\n")
		local start_index_2 = __find(text, "\t")
		if start_index_1 ~= nil and start_index_2 ~= nil then
			if start_index_1 < start_index_2 then
				start_index_2 = nil
			else
				start_index_1 = nil
			end
		end
		if start_index_1 ~= nil then
			local new_char_info = ALittle.String_CopyTable(char_info)
			new_char_info.text = __sub(text, 1, start_index_1 - 1)
			char_info_list_count = char_info_list_count + 1
			char_info_list[char_info_list_count] = new_char_info
			new_char_info = ALittle.String_CopyTable(char_info)
			new_char_info.text = "\n"
			char_info_list_count = char_info_list_count + 1
			char_info_list[char_info_list_count] = new_char_info
			text = __sub(text, start_index_1 + 1)
		elseif start_index_2 ~= nil then
			local new_char_info = ALittle.String_CopyTable(char_info)
			new_char_info.text = __sub(text, 1, start_index_2 - 1)
			char_info_list_count = char_info_list_count + 1
			char_info_list[char_info_list_count] = new_char_info
			new_char_info = ALittle.String_CopyTable(char_info)
			new_char_info.text = "\t"
			char_info_list_count = char_info_list_count + 1
			char_info_list[char_info_list_count] = new_char_info
			text = __sub(text, start_index_2 + 1)
		else
			if text ~= "" then
				local new_char_info = ALittle.String_CopyTable(char_info)
				new_char_info.text = text
				char_info_list_count = char_info_list_count + 1
				char_info_list[char_info_list_count] = new_char_info
			end
			break
		end
	end
	return char_info_list_count
end

function ALittle.RichArea:Ctor(ctrl_sys)
	___rawset(self, "_enter_key_height", 20)
	___rawset(self, "_line_spacing", 0)
	___rawset(self, "_halign", 0)
	___rawset(self, "_valign", 0)
	___rawset(self, "_display_list", nil)
	___rawset(self, "_line_list", {})
	___rawset(self, "_line_count", 0)
	___rawset(self, "_real_height", 0)
	___rawset(self, "_link_map", ALittle.CreateValueWeakMap())
	___rawset(self, "_max_line_count", 0)
end

function ALittle.RichArea.__getter:link_map()
	return self._link_map
end

function ALittle.RichArea:ClearLinkMap()
	self._link_map = ALittle.CreateValueWeakMap()
end

function ALittle.RichArea.__setter:width(value)
	if self.width == value then
		return
	end
	ALittle.DisplayLayout.__setter.width(self, value)
	self:Refresh()
end

function ALittle.RichArea.__setter:display_list(value)
	self._display_list = value
	self:Refresh()
end

function ALittle.RichArea.__getter:display_list()
	return self._display_list
end

function ALittle.RichArea.__setter:halign(value)
	if self._halign == value then
		return
	end
	self._halign = value
	self:RefreshX()
end

function ALittle.RichArea.__getter:halign()
	return self._halign
end

function ALittle.RichArea.__setter:valign(value)
	if self._valign == value then
		return
	end
	self._valign = value
	self:RefreshY()
end

function ALittle.RichArea.__getter:valign()
	return self._valign
end

function ALittle.RichArea.__getter:lin_count()
	return self._line_count
end

function ALittle.RichArea.__getter:max_line_count()
	return self._max_line_count
end

function ALittle.RichArea.__setter:max_line_count(value)
	if self._max_line_count == value then
		return
	end
	self._max_line_count = value
	self:Refresh()
end

function ALittle.RichArea:GetLineWidth(line_index)
	local count = self._line_count
	if line_index < 1 or line_index > count then
		return 0
	end
	local line = self._line_list[line_index]
	return line.width
end

function ALittle.RichArea.__getter:real_height()
	return self._real_height
end

function ALittle.RichArea.__setter:line_spacing(line_spacing)
	if self._line_spacing == line_spacing then
		return
	end
	self._line_spacing = line_spacing
	self:RefreshY()
end

function ALittle.RichArea.__getter:line_spacing()
	return self._line_spacing
end

function ALittle.RichArea:Refresh()
	self:RemoveAllChild()
	self._line_list = {}
	self._line_count = 0
	local total_width = self.width
	if total_width == 0 then
		return
	end
	if self._display_list == nil then
		return
	end
	local display_list = {}
	local display_list_count = 0
	for index, display_info in ___ipairs(self._display_list) do
		if display_info.__class == "Text" then
			display_list_count = self:SplitText(display_info, display_list, display_list_count)
		else
			display_list_count = display_list_count + 1
			display_list[display_list_count] = display_info
		end
	end
	local line_info = nil
	local display_info = nil
	local display_object = nil
	local display_index = 1
	local remain_width = total_width
	while true do
		if display_info == nil then
			display_info = display_list[display_index]
			if display_info == nil then
				break
			end
		end
		if line_info == nil then
			if self._max_line_count > 0 and self._line_count >= self._max_line_count then
				break
			end
			line_info = {}
			line_info.childs = {}
			line_info.child_count = 0
			line_info.height = 0
			line_info.width = 0
		end
		if display_info.__class == "Text" then
			if display_info.text == "\n" then
				if line_info.height < self._enter_key_height then
					line_info.height = self._enter_key_height
				end
				self._line_count = self._line_count + 1
				self._line_list[self._line_count] = line_info
				line_info = nil
				display_info = nil
				display_object = nil
				display_index = display_index + 1
				remain_width = total_width
			elseif display_info.text == "\t" then
				if display_object == nil then
					local name = "nkacbjbsakcvuqocbakcbjcbvjhciqwojqppwvnwe"
					self._ctrl_sys:RegisterInfo(name, ALittle.String_CopyTable(display_info))
					display_object = self._ctrl_sys:CreateControl(name, self._link_map)
					self._ctrl_sys:UnRegisterInfo(name)
					display_object.text = "    "
				end
				local object_width = display_object.width
				local object_height = display_object.height
				if remain_width >= object_width then
					line_info.child_count = line_info.child_count + 1
					line_info.childs[line_info.child_count] = display_object
					self:AddChild(display_object)
					line_info.width = line_info.width + object_width
					if line_info.height < object_height then
						line_info.height = object_height
					end
					remain_width = remain_width - object_width
					if remain_width <= 0 then
						self._line_count = self._line_count + 1
						self._line_list[self._line_count] = line_info
						line_info = nil
						remain_width = total_width
					end
					display_object = nil
					display_info = nil
					display_index = display_index + 1
				else
					local count = display_object._show:CutTextByWidth(__floor(remain_width), display_info.text, __floor(total_width))
					if count > 0 then
						display_object.text = __sub(display_info.text, 1, count)
						local new_display_info = ALittle.String_CopyTable(display_info)
						new_display_info.text = __sub(display_info.text, count + 1)
						line_info.child_count = line_info.child_count + 1
						line_info.childs[line_info.child_count] = display_object
						self:AddChild(display_object)
						line_info.width = line_info.width + display_object.width
						if line_info.height < object_height then
							line_info.height = object_height
						end
						self._line_count = self._line_count + 1
						self._line_list[self._line_count] = line_info
						line_info = nil
						remain_width = total_width
						display_object = nil
						display_info = new_display_info
					else
						self._line_count = self._line_count + 1
						self._line_list[self._line_count] = line_info
						line_info = nil
						remain_width = total_width
					end
				end
			else
				if display_info.text == "" then
					display_info = nil
					display_index = display_index + 1
				else
					if display_object == nil then
						local name = "nkacbjbsakcvuqocbakcbjcbvjhciqwojqppwvnwe"
						self._ctrl_sys:RegisterInfo(name, ALittle.String_CopyTable(display_info))
						display_object = self._ctrl_sys:CreateControl(name, self._link_map)
						self._ctrl_sys:UnRegisterInfo(name)
					end
					local object_width = display_object.width
					local object_height = display_object.height
					local count = display_object._show:CutTextByWidth(__floor(remain_width), display_info.text, __floor(total_width))
					if count == 0 and line_info.child_count == 0 then
						count = ALittle.String_GetByteCount(display_info.text, 1)
					end
					if count == 0 then
						remain_width = 0
					else
						display_object.text = __sub(display_info.text, 1, count)
						local new_display_info = ALittle.String_CopyTable(display_info)
						new_display_info.text = __sub(display_info.text, count + 1)
						line_info.child_count = line_info.child_count + 1
						line_info.childs[line_info.child_count] = display_object
						self:AddChild(display_object)
						line_info.width = line_info.width + display_object.width
						if line_info.height < object_height then
							line_info.height = object_height
						end
						remain_width = remain_width - display_object.width
						display_object = nil
						display_info = new_display_info
					end
					if remain_width <= 0 then
						self._line_count = self._line_count + 1
						self._line_list[self._line_count] = line_info
						line_info = nil
						remain_width = total_width
					end
				end
			end
		else
			if display_object == nil then
				local name = "nkacbjbsakcvuqocbakcbjcbvjhciqwojqppwvnwe"
				self._ctrl_sys:RegisterInfo(name, ALittle.String_CopyTable(display_info))
				display_object = self._ctrl_sys:CreateControl(name, self._link_map)
				self._ctrl_sys:UnRegisterInfo(name)
			end
			local object_width = display_object.width
			local object_height = display_object.height
			if remain_width >= object_width or (line_info.child_count == 0 and total_width <= object_width) then
				line_info.child_count = line_info.child_count + 1
				line_info.childs[line_info.child_count] = display_object
				self:AddChild(display_object)
				line_info.width = line_info.width + display_object.width
				if line_info.height < object_height then
					line_info.height = object_height
				end
				remain_width = remain_width - object_width
				if remain_width <= 0 then
					self._line_count = self._line_count + 1
					self._line_list[self._line_count] = line_info
					line_info = nil
					remain_width = total_width
				end
				display_object = nil
				display_info = nil
				display_index = display_index + 1
			else
				self._line_count = self._line_count + 1
				self._line_list[self._line_count] = line_info
				line_info = nil
				remain_width = total_width
			end
		end
	end
	if line_info ~= nil then
		self._line_count = self._line_count + 1
		self._line_list[self._line_count] = line_info
	end
	self:RefreshX()
	self:RefreshY()
end

function ALittle.RichArea:RefreshX()
	if self._line_list == nil then
		return
	end
	for k, line in ___ipairs(self._line_list) do
		local offset_x = 0.0
		if self._halign == 1 then
			offset_x = (self.width - line.width) / 2
		elseif self._halign == 2 then
			offset_x = self.width - line.width
		end
		for index, child in ___ipairs(line.childs) do
			child.x = offset_x
			offset_x = offset_x + child.width
		end
	end
end

function ALittle.RichArea:RefreshY()
	if self._line_list == nil then
		return
	end
	self._real_height = 0
	local line_count = 0
	for k, line in ___ipairs(self._line_list) do
		self._real_height = self._real_height + line.height
		line_count = line_count + 1
	end
	self._real_height = self._real_height + (line_count - 1) * self._line_spacing
	local offset_y = 0.0
	if self._valign == 1 then
		offset_y = (self.height - self._real_height) / 2
	elseif self._valign == 2 then
		offset_y = self.height - self._real_height
	end
	for k, line in ___ipairs(self._line_list) do
		for index, child in ___ipairs(line.childs) do
			child.y = line.height - child.height + offset_y
		end
		offset_y = offset_y + line.height + self._line_spacing
	end
end

end