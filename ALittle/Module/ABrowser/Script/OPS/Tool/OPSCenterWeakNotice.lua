
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

OPSCenterWeakNotice = ALittle.Class(nil, "ABrowser.OPSCenterWeakNotice")

function OPSCenterWeakNotice:Ctor(center)
	___rawset(self, "_center", center)
end

function OPSCenterWeakNotice:Show(content, succeed)
	if self._center_weak_notice == nil then
		self._center_weak_notice = g_Control:CreateControl("ops_center_weak_notice", self)
		self._center.tip_layer:AddChild(self._center_weak_notice)
	end
	if succeed then
		self._center_weak_notice_textgreen.visible = true
		self._center_weak_notice_textred.visible = false
		self._center_weak_notice_textgreen.text = content
		self._center_weak_notice_red.visible = false
		self._center_weak_notice_green.visible = true
	else
		self._center_weak_notice_textgreen.visible = false
		self._center_weak_notice_textred.visible = true
		self._center_weak_notice_textred.text = content
		self._center_weak_notice_red.visible = true
		self._center_weak_notice_green.visible = false
	end
	self._center_weak_notice:UpdateLayout()
	if self._center_weak_notice_loop ~= nil then
		A_LoopSystem:RemoveUpdater(self._center_weak_notice_loop)
	end
	self._center_weak_notice.alpha = 0
	self._center_weak_notice_loop = ALittle.LoopList()
	local loop_1 = ALittle.LoopLinear(self._center_weak_notice, "alpha", 1, 1000, 0)
	self._center_weak_notice_loop:AddUpdater(loop_1)
	local loop_2 = ALittle.LoopLinear(self._center_weak_notice, "alpha", 0, 1000, 2000)
	self._center_weak_notice_loop:AddUpdater(loop_2)
	A_LoopSystem:AddUpdater(self._center_weak_notice_loop)
end

