-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.AUIPlugin == nil then _G.AUIPlugin = {} end
local AUIPlugin = AUIPlugin
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(1862557463, "ALittle.UIShowEvent", {
name = "ALittle.UIShowEvent", ns_name = "ALittle", rl_name = "UIShowEvent", hash_code = 1862557463,
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
ALittle.RegStruct(348388800, "ALittle.UIHideEvent", {
name = "ALittle.UIHideEvent", ns_name = "ALittle", rl_name = "UIHideEvent", hash_code = 348388800,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
AUIPlugin.AUICodeLineContainer = Lua.Class(ALittle.DisplayLayout, "AUIPlugin.AUICodeLineContainer")

function AUIPlugin.AUICodeLineContainer:Ctor(ctrl_sys)
	___rawset(self, "_showd", false)
	___rawset(self, "_version", 0)
	___rawset(self, "_delay_loop", nil)
	local find = ALittle.DisplayLayout(ctrl_sys)
	find.width_type = 4
	find.height_type = 4
	self:AddChild(find)
	___rawset(self, "_find", find)
	local quad = ALittle.Quad(ctrl_sys)
	quad = ALittle.Quad(AUIPlugin.g_Control)
	quad.red = AUIPlugin.CODE_SELECT_RED
	quad.green = AUIPlugin.CODE_SELECT_GREEN
	quad.blue = AUIPlugin.CODE_SELECT_BLUE
	quad.height = AUIPlugin.CODE_LINE_HEIGHT
	quad.visible = false
	self:AddChild(quad)
	___rawset(self, "_select", quad)
	local text = ALittle.DisplayLayout(ctrl_sys)
	text.width_type = 4
	text.height_type = 4
	self:AddChild(text)
	___rawset(self, "_text", text)
	local error = ALittle.DisplayLayout(ctrl_sys)
	error.width_type = 4
	error.height_type = 4
	self:AddChild(error)
	___rawset(self, "_error", error)
	self:AddEventListener(___all_struct[348388800], self, self.HandleHide)
	self:AddEventListener(___all_struct[1862557463], self, self.HandleShow)
end

function AUIPlugin.AUICodeLineContainer:AddChar(char)
	if char.text ~= nil then
		self._text:AddChild(char.text)
	end
	if not self._showd then
		return
	end
	if char.text == nil and char.width > 0 and char.char ~= " " and char.char ~= "\t" then
		char.text = ALittle.Text(AUIPlugin.g_Control)
		char.text.disabled = true
		char.text.red = char.red
		char.text.green = char.green
		char.text.blue = char.blue
		char.text.font_path = AUIPlugin.CODE_FONT_PATH
		char.text.font_size = AUIPlugin.CODE_FONT_SIZE
		char.text.text = char.char
		char.text.x = char.pre_width
		self._text:AddChild(char.text)
	end
	local line = self._user_data
	if self._delay_loop == nil and line.edit.language ~= nil and line.edit.language.version ~= self._version then
		self._delay_loop = ALittle.LoopTimer(Lua.Bind(self.HandleColor, self), 1)
		self._delay_loop:Start()
	end
end

function AUIPlugin.AUICodeLineContainer:RestoreColor()
	self._set_color = nil
	if self._delay_loop ~= nil then
		return
	end
	self._version = 0
	self._delay_loop = ALittle.LoopTimer(Lua.Bind(self.HandleColor, self), 1)
	self._delay_loop:Start()
end

function AUIPlugin.AUICodeLineContainer:SetColor(char_start, char_end, red, green, blue)
	if self._delay_loop ~= nil then
		self._set_color = Lua.Bind(self.SetColor, self, char_start, char_end, red, green, blue)
		return
	end
	local line = self._user_data
	local i = char_start
	while true do
		if not(i <= char_end) then break end
		local child = line.char_list[i]
		if child ~= nil and child.text ~= nil then
			child.text.red = red
			child.text.green = green
			child.text.blue = blue
		end
		i = i+(1)
	end
end

function AUIPlugin.AUICodeLineContainer:HandleColor()
	self._delay_loop = nil
	if self.parent == nil then
		return
	end
	local line = self._user_data
	if self._version == line.edit.language.version then
		return
	end
	self._version = line.edit.language.version
	local line_index = ALittle.Math_Floor(self.y / AUIPlugin.CODE_LINE_HEIGHT) + 1
	if line_index < 1 or line_index > line.edit.line_count then
		return
	end
	local list = line.edit.language:QueryColor(line_index)
	for index, info in ___ipairs(list) do
		local char_start = 1
		if info.line_start == line_index then
			char_start = info.char_start
		end
		local char_end = line.char_count
		if info.line_end == line_index then
			char_end = info.char_end
		end
		local color = line.edit.language:QueryColorValue(info.tag)
		if color == nil then
			color = AUIPlugin.CODE_DEFAULT_COLOR
		end
		local i = char_start
		while true do
			if not(i <= char_end) then break end
			local child = line.char_list[i]
			if child ~= nil and child.text ~= nil then
				child.text.red = color.red
				child.text.green = color.green
				child.text.blue = color.blue
				if info.blur then
					child.text.alpha = 0.5
				else
					child.text.alpha = 1
				end
			end
			i = i+(1)
		end
	end
	if self._set_color ~= nil then
		self._set_color()
		self._set_color = nil
	end
end
AUIPlugin.AUICodeLineContainer.HandleColor = Lua.CoWrap(AUIPlugin.AUICodeLineContainer.HandleColor)

function AUIPlugin.AUICodeLineContainer:HandleHide(event)
end

function AUIPlugin.AUICodeLineContainer:HandleShow(event)
	if not self._showd then
		self._showd = true
		local line = self._user_data
		for index, char in ___ipairs(line.char_list) do
			if char.text == nil and char.width > 0 and char.char ~= " " and char.char ~= "\t" then
				char.text = ALittle.Text(AUIPlugin.g_Control)
				char.text.disabled = true
				char.text.red = AUIPlugin.CODE_FONT_RED
				char.text.green = AUIPlugin.CODE_FONT_GREEN
				char.text.blue = AUIPlugin.CODE_FONT_BLUE
				char.text.font_path = AUIPlugin.CODE_FONT_PATH
				char.text.font_size = AUIPlugin.CODE_FONT_SIZE
				char.text.text = char.char
				char.text.x = char.pre_width
				self._text:AddChild(char.text)
			end
		end
	end
	local line = self._user_data
	if self._delay_loop == nil and line.edit.language ~= nil and line.edit.language.version ~= self._version then
		self._delay_loop = ALittle.LoopTimer(Lua.Bind(self.HandleColor, self), 1)
		self._delay_loop:Start()
	end
end

end