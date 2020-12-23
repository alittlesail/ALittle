-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittle == nil then _G.ALittle = {} end
local ALittle = ALittle
local Lua = Lua
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()


assert(ALittle.DisplayObject, " extends class:ALittle.DisplayObject is nil")
ALittle.Quad = Lua.Class(ALittle.DisplayObject, "ALittle.Quad")

function ALittle.Quad:Ctor(ctrl_sys)
	___rawset(self, "_show", __CPPAPIQuad())
	self:AddEventListener(___all_struct[40651933], self, self.HandleLButtonUp)
	self:AddEventListener(___all_struct[683647260], self, self.HandleMButtonUp)
	self:AddEventListener(___all_struct[734860930], self, self.HandleFLButtonUp)
end

function ALittle.Quad:HandleLButtonUp(event)
	if event.rel_x >= 0 and event.rel_y >= 0 and event.rel_x < event.target._width and event.rel_y < event.target._height then
		local c_event = {}
		c_event.is_drag = event.is_drag
		c_event.count = event.count
		self:DispatchEvent(___all_struct[-449066808], c_event)
	end
end

function ALittle.Quad:HandleMButtonUp(event)
	if event.rel_x >= 0 and event.rel_y >= 0 and event.rel_x < event.target._width and event.rel_y < event.target._height then
		local c_event = {}
		c_event.is_drag = event.is_drag
		self:DispatchEvent(___all_struct[-1330840], c_event)
	end
end

function ALittle.Quad:HandleFLButtonUp(event)
	if event.rel_x >= 0 and event.rel_y >= 0 and event.rel_x < event.target._width and event.rel_y < event.target._height then
		local c_event = {}
		c_event.is_drag = event.is_drag
		self:DispatchEvent(___all_struct[286797479], c_event)
	end
end

end