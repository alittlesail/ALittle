
module("ALittle", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayObject, " extends class:ALittle.DisplayObject is nil")
EffectImage = Lua.Class(ALittle.DisplayObject, "ALittle.EffectImage")

function EffectImage:Ctor(ctrl_sys)
end

function EffectImage:Action(control)
	if control == nil then
		return
	end
	self._show = __CPPAPIImage()
	self._texture = __CPPAPIRenderTexture()
	self.x = control.x
	self.y = control.y
	self.width = control.width
	self.height = control.height
	control._show:SetX(0)
	control._show:SetY(0)
	control.visible = true
	control.clip = false
	local result = self._texture:Draw(control._show, math.floor(self.width), math.floor(self.height), 1)
	control._show:SetX(self._x)
	control._show:SetY(self._y)
	if result then
		self._show:SetTexture(self._texture)
	end
	self._show:SetTextureCoord(0, 1, 0, 1)
	self.disabled = true
end

function EffectImage:Clear()
	if self._texture == nil then
		return
	end
	self._texture:Clear()
end

