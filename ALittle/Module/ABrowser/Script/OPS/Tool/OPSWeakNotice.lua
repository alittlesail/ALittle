
module("ABrowser", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

OPSWeakNotice = ALittle.Class(nil, "ABrowser.OPSWeakNotice")

function OPSWeakNotice:Ctor(center)
	___rawset(self, "_center", center)
end

function OPSWeakNotice:Show(content, succeed)
	if self._weak_notice == nil then
		self._weak_notice = g_Control:CreateControl("ops_weak_notice", self)
		self._center.tip_layer:AddChild(self._weak_notice)
	end
	if succeed then
		self._weak_notice_textgreen.visible = true
		self._weak_notice_textred.visible = false
		self._weak_notice_textgreen.text = content
		self._weak_notice.width = self._weak_notice_textgreen.width + 200
		self._weak_notice_red.visible = false
		self._weak_notice_green.visible = true
	else
		self._weak_notice_textgreen.visible = false
		self._weak_notice_textred.visible = true
		self._weak_notice_textred.text = content
		self._weak_notice.width = self._weak_notice_textred.width + 200
		self._weak_notice_red.visible = true
		self._weak_notice_green.visible = false
	end
	self._weak_notice:UpdateLayout()
	if self._weak_notice_loop ~= nil then
		A_LoopSystem:RemoveUpdater(self._weak_notice_loop)
	end
	self._weak_notice.alpha = 0
	self._weak_notice_loop = ALittle.LoopList()
	local loop_1 = ALittle.LoopLinear(self._weak_notice, "alpha", 1, 1000, 0)
	self._weak_notice_loop:AddUpdater(loop_1)
	local loop_2 = ALittle.LoopLinear(self._weak_notice, "alpha", 0, 1000, 2000)
	self._weak_notice_loop:AddUpdater(loop_2)
	A_LoopSystem:AddUpdater(self._weak_notice_loop)
end

