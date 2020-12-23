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

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(1337289812, "ALittle.UIButtonDragEvent", {
name = "ALittle.UIButtonDragEvent", ns_name = "ALittle", rl_name = "UIButtonDragEvent", hash_code = 1337289812,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name = "ALittle.UIChangedEvent", ns_name = "ALittle", rl_name = "UIChangedEvent", hash_code = 958494922,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(150587926, "ALittle.UIButtonDragEndEvent", {
name = "ALittle.UIButtonDragEndEvent", ns_name = "ALittle", rl_name = "UIButtonDragEndEvent", hash_code = 150587926,
name_list = {"target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"},
type_list = {"ALittle.DisplayObject","double","double","double","double","double","double"},
option_map = {}
})

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
AUIPlugin.AUIDrawingBoard = Lua.Class(ALittle.DisplayLayout, "AUIPlugin.AUIDrawingBoard")

function AUIPlugin.AUIDrawingBoard:Ctor()
	___rawset(self, "_pan_size", 5)
	___rawset(self, "_pan_color", 0)
	___rawset(self, "_draw_width", 0)
	___rawset(self, "_draw_height", 0)
end

function AUIPlugin.AUIDrawingBoard:TCtor()
	self._image = ALittle.DynamicImage(self._ctrl_sys)
	self._image.width_type = 4
	self._image.height_type = 4
	self._image:SetRenderMode(1)
	self:AddChild(self._image)
	self._image:AddEventListener(___all_struct[1337289812], self, self.HandleDrag)
	self._image:AddEventListener(___all_struct[150587926], self, self.HandleDragEnd)
end

function AUIPlugin.AUIDrawingBoard:SetPan(size, color)
	self._pan_size = size
	if self._pan_size < 1 then
		self._pan_size = 1
	end
	self._pan_color = color
end

function AUIPlugin.AUIDrawingBoard:SetDrawSize(width, height, color)
	self._draw_width = width
	self._draw_height = height
	if self._draw_width < 0 then
		self._draw_width = 0
	end
	if self._draw_height < 0 then
		self._draw_height = 0
	end
	self._image:SetSurfaceSize(self._draw_width, self._draw_height, color)
end

function AUIPlugin.AUIDrawingBoard:ClearContent(color)
	self._image:SetSurfaceSize(self._draw_width, self._draw_height, color)
end

function AUIPlugin.AUIDrawingBoard.__getter:surface()
	return self._image:GetSurface(false)
end

function AUIPlugin.AUIDrawingBoard:HandleDrag(event)
	local x_rate = event.rel_x / event.target.width
	if x_rate > 1 then
		x_rate = 1
	end
	local y_rate = event.rel_y / event.target.height
	if y_rate > 1 then
		y_rate = 1
	end
	local x = ALittle.Math_Floor(self._draw_width * x_rate)
	local y = ALittle.Math_Floor(self._draw_height * y_rate)
	local surface = self._image:GetSurface(true)
	local range = ALittle.Math_Floor((self._pan_size - 1) / 2)
	local col = x - range
	while true do
		if not(col <= x + range) then break end
		local row = y - range
		while true do
			if not(row <= y + range) then break end
			carp.SetCarpSurfacePixel(surface, col, row, self._pan_color)
			row = row+(1)
		end
		col = col+(1)
	end
end

function AUIPlugin.AUIDrawingBoard:HandleDragEnd(event)
	self:DispatchEvent(___all_struct[958494922], {})
end

end