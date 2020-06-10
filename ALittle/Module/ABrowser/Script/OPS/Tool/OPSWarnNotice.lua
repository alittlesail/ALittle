
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

OPSWarnNotice = ALittle.Class(nil, "ABrowser.OPSWarnNotice")

function OPSWarnNotice:Ctor(center)
	___rawset(self, "_center", center)
end

function OPSWarnNotice:Show(target, content)
	if self._warn_notice == nil then
		self._warn_notice = g_Control:CreateControl("ops_warn_notice", self)
	end
	self._warn_notice_text.text = content
	self._warn_notice.width = self._warn_notice_text.width + 50
	local x, y = target:LocalToGlobal()
	y = y + target.height
	local x_offset = 15
	x = x + target.width / 2 - x_offset
	self._warn_notice.x = x
	self._warn_notice.y = y
	A_LayerManager:ShowFromRight(self._warn_notice)
	if self._warn_notice_loop ~= nil then
		A_LoopSystem:RemoveUpdater(self._warn_notice_loop)
	end
	self._warn_notice.alpha = 0
	self._warn_notice_loop = ALittle.LoopLinear(self._warn_notice, "alpha", 1, 300, 0)
	A_LoopSystem:AddUpdater(self._warn_notice_loop)
end

