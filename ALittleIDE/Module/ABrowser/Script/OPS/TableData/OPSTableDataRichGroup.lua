
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
OPSTableDataRichGroup = ALittle.Class(ALittle.DisplayLayout, "ABrowser.OPSTableDataRichGroup")

function OPSTableDataRichGroup:Ctor(ctrl_sys)
	___rawset(self, "_enter_key_height", 20)
	___rawset(self, "_line_spacing", 0)
	___rawset(self, "_column_spacing", 0)
	___rawset(self, "_halign", ALittle.UIEnumTypes.HALIGN_LEFT)
	___rawset(self, "_valign", ALittle.UIEnumTypes.VALIGN_TOP)
	___rawset(self, "_show_line", {})
	___rawset(self, "_show_childs", {})
	___rawset(self, "_remain_width", 0)
end

function OPSTableDataRichGroup.__getter:halign()
	return self._halign
end

function OPSTableDataRichGroup.__getter:valign()
	return self._valign
end

function OPSTableDataRichGroup.__getter:line_spacing()
	return self._line_spacing
end

function OPSTableDataRichGroup.__getter:column_spacing()
	return self._column_spacing
end

function OPSTableDataRichGroup.__setter:width(value)
	if self.width == value then
		return
	end
	ALittle.DisplayLayout.__setter.width(self, value)
	self:Refresh()
end

function OPSTableDataRichGroup.__setter:halign(value)
	if self._halign == value then
		return
	end
	self._halign = value
	self:Refresh()
end

function OPSTableDataRichGroup.__setter:valign(value)
	if self._valign == value then
		return
	end
	self._valign = value
	self:Refresh()
end

function OPSTableDataRichGroup.__setter:line_spacing(value)
	if self._line_spacing == value then
		return
	end
	self._line_spacing = value
	self:Refresh()
end

function OPSTableDataRichGroup.__setter:column_spacing(value)
	if self._column_spacing == value then
		return
	end
	self._column_spacing = value
	self:Refresh()
end

function OPSTableDataRichGroup:SetChildList(child_list)
	self._show_childs = {}
	local show_child_count = 0
	for index, child in ___ipairs(child_list) do
		show_child_count = show_child_count + 1
		self._show_childs[show_child_count] = child
	end
	self:Refresh()
end

function OPSTableDataRichGroup:AddBr()
	local child = {}
	child["__class"] = "Br"
	local child_count = table.maxn(self._show_childs)
	child_count = child_count + 1
	self._show_childs[child_count] = child
	self:Refresh()
end

function OPSTableDataRichGroup:Clear()
	self._show_childs = {}
	self:Refresh()
end

function OPSTableDataRichGroup:Refresh()
	self._show_line = {}
	local show_line_count = 0
	local cur_line = {}
	cur_line.height = 0
	cur_line.width = 0
	cur_line.childs = {}
	cur_line.child_count = 0
	local child_index = 1
	self._remain_width = self.width
	while true do
		local child = self._show_childs[child_index]
		if child == nil then
			break
		end
		if child["__class"] == "Br" then
			if cur_line.child_count == 0 then
				cur_line.height = self._enter_key_height
				cur_line.width = 0
				show_line_count = show_line_count + 1
				self._show_line[show_line_count] = cur_line
				cur_line = {}
				cur_line.height = 0
				cur_line.width = 0
				cur_line.childs = {}
				cur_line.child_count = 0
				self._remain_width = self.width
			else
				show_line_count = show_line_count + 1
				self._show_line[show_line_count] = cur_line
				cur_line = {}
				cur_line.height = 0
				cur_line.width = 0
				cur_line.childs = {}
				cur_line.child_count = 0
				self._remain_width = self.width
			end
		else
			if cur_line.child_count == 0 then
				cur_line.height = child["height"]
				cur_line.width = child["width"]
				cur_line.child_count = 1
				cur_line.childs[cur_line.child_count] = child
				self._remain_width = self._remain_width - child["width"]
				if self._remain_width <= 0 then
					show_line_count = show_line_count + 1
					self._show_line[show_line_count] = cur_line
					cur_line = {}
					cur_line.height = 0
					cur_line.width = 0
					cur_line.childs = {}
					cur_line.child_count = 0
					self._remain_width = self.width
				end
			else
				self._remain_width = self._remain_width - child["width"] - self._column_spacing
				if self._remain_width < 0 then
					show_line_count = show_line_count + 1
					self._show_line[show_line_count] = cur_line
					cur_line = {}
					cur_line.height = child["height"]
					cur_line.width = child["width"]
					cur_line.childs = {}
					cur_line.child_count = 1
					cur_line.childs[cur_line.child_count] = child
					self._remain_width = self.width - child["width"]
					if self._remain_width < 0 then
						show_line_count = show_line_count + 1
						self._show_line[show_line_count] = cur_line
						cur_line = {}
						cur_line.height = 0
						cur_line.width = 0
						cur_line.childs = {}
						cur_line.child_count = 0
						self._remain_width = self.width
					end
				else
					cur_line.width = cur_line.width + child["width"] + self._column_spacing
					if cur_line.height < child["height"] then
						cur_line.height = child["height"]
					end
					cur_line.child_count = cur_line.child_count + 1
					cur_line.childs[cur_line.child_count] = child
				end
			end
		end
		child_index = child_index + 1
	end
	if cur_line.child_count > 0 then
		show_line_count = show_line_count + 1
		self._show_line[show_line_count] = cur_line
	end
	self:RemoveAllChild()
	local offset_y = 0
	for k, v in ___ipairs(self._show_line) do
		local offset_x = 0
		if self._halign == ALittle.UIEnumTypes.HALIGN_CENTER then
			offset_x = (self.width - v.width) / 2
		elseif self._halign == ALittle.UIEnumTypes.HALIGN_RIGHT then
			offset_x = self.width - v.width
		else
			offset_x = 0
		end
		for index, child in ___ipairs(v.childs) do
			self:AddChild(child)
			child.x = offset_x
			if self._valign == ALittle.UIEnumTypes.VALIGN_CENTER then
				child.y = offset_y + (v.height - child.height) / 2
			elseif self._valign == ALittle.UIEnumTypes.VALIGN_BOTTOM then
				child.y = offset_y + (v.height - child.height)
			else
				child.y = offset_y
			end
			offset_x = offset_x + child.width + self._column_spacing
		end
		offset_y = offset_y + self._line_spacing + v.height
	end
	self.height = offset_y - self._line_spacing
	self:DispatchEventType(ALittle.UIEventTypes.RESIZE)
end

