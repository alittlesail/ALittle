-- ALittle Generate Lua
module("ALittle", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
SpringDialog = Lua.Class(ALittle.DisplayLayout, "ALittle.SpringDialog")

function SpringDialog:Ctor(ctrl_sys)
	___rawset(self, "_is_show", false)
	self.visible = false
end

function SpringDialog.__getter:show()
	return self._is_show
end

function SpringDialog.__setter:show(value)
	if self._is_show == value then
		return
	end
	self._is_show = value
	if self._anti_loop ~= nil then
		self._anti_loop:SetCompleted()
		self._anti_loop:Stop()
		self._anti_loop = nil
	end
	if value then
		self:ShowAnti(1.1, 200, 200)
	else
		self:HideAnti(1.1, 200)
	end
end

function SpringDialog:ShowAnti(scale, scale_big_ms, scale_return_ms)
	if self._show_dialog == nil then
		return
	end
	self.visible = true
	self.alpha = 0
	self._show_dialog.scale_x = 1
	self._show_dialog.scale_y = 1
	self._anti_loop = LoopList()
	local group = LoopGroup()
	group:AddUpdater(LoopLinear(self._show_dialog, "scale_x", scale, scale_big_ms, 1))
	group:AddUpdater(LoopLinear(self._show_dialog, "scale_y", scale, scale_big_ms, 1))
	group:AddUpdater(LoopLinear(self, "alpha", 1, scale_big_ms, 1))
	self._anti_loop:AddUpdater(group)
	group = LoopGroup()
	group:AddUpdater(LoopLinear(self._show_dialog, "scale_x", 1, scale_return_ms, 1))
	group:AddUpdater(LoopLinear(self._show_dialog, "scale_y", 1, scale_return_ms, 1))
	self._anti_loop:AddUpdater(group)
	self._anti_loop:Start()
end

function SpringDialog:HideAnti(scale, scale_big_ms)
	if self._show_dialog == nil then
		return
	end
	self._anti_loop = LoopList()
	local group = LoopGroup()
	group:AddUpdater(LoopLinear(self._show_dialog, "scale_x", scale, scale_big_ms, 1))
	group:AddUpdater(LoopLinear(self._show_dialog, "scale_y", scale, scale_big_ms, 1))
	group:AddUpdater(LoopLinear(self, "alpha", 0, scale_big_ms, 1))
	self._anti_loop:AddUpdater(group)
	self._anti_loop:AddUpdater(LoopAttribute(self, "visible", false, 1))
	self._anti_loop:Start()
end

