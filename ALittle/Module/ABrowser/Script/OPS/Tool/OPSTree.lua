
module("ABrowser", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

assert(ALittle.DisplayLayout, " extends class:ALittle.DisplayLayout is nil")
OPSTree = ALittle.Class(ALittle.DisplayLayout, "ABrowser.OPSTree")

function OPSTree.__getter:text()
	return self._head.text
end

function OPSTree.__getter:childs()
	return self._body.childs
end

function OPSTree.__getter:body()
	return self._body
end

function OPSTree.__getter:height()
	if self._body.visible == false then
		return self._body.y
	end
	return self._body.y + self._body.height
end

function OPSTree.__setter:text(value)
	self._head.text = value
end

function OPSTree:TCtor()
	self._head.selected = false
	self.height = self._body.y
	self._body.visible = false
end

function OPSTree:AddItem(item)
	self._body:AddChild(item)
	item._logic_parent = self
end

function OPSTree:RemoveChild(item)
	return self._body:RemoveChild(item)
end

function OPSTree:Show()
	self._body.visible = true
	self._head.selected = true
	self.height = self._body.y + self._body.height
	self:DispatchEventType(ALittle.UIEventTypes.RESIZE)
end

function OPSTree:Hide()
	self._body.visible = false
	self._head.selected = false
	self.height = self._body.y
	self:DispatchEventType(ALittle.UIEventTypes.RESIZE)
end

function OPSTree:HandleHeadChanged(event)
	if self._head.selected then
		self:Show()
	else
		self:Hide()
	end
end

