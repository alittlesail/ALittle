-- ALittle Generate Lua And Do Not Edit This Line!
module("ALittleIDE", package.seeall)

local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name = "ALittle.UIChangedEvent", ns_name = "ALittle", rl_name = "UIChangedEvent", hash_code = 958494922,
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

assert(ALittleIDE.IDETabChild, " extends class:ALittleIDE.IDETabChild is nil")
IDECodeTabChild = Lua.Class(ALittleIDE.IDETabChild, "ALittleIDE.IDECodeTabChild")

function IDECodeTabChild:Ctor(ctrl_sys, name, save)
	___rawset(self, "_edit", g_AUIPluinControl:CreateControl("ide_code_tab_screen", self))
	self._edit:AddEventListener(___all_struct[958494922], self, self.HandleChangedEvent)
	self._edit._user_data = self
end

function IDECodeTabChild:OnHide()
	self._edit:OnHide()
end

function IDECodeTabChild:OnShow()
	self._edit:OnShow()
end

function IDECodeTabChild:OnClose()
	self._edit:OnClose()
end

function IDECodeTabChild:OnOpen()
	self._edit:Load(self._user_info.path)
end

function IDECodeTabChild:HandleChangedEvent(event)
	self.save = false
end

function IDECodeTabChild.__getter:tab_screen()
	return self._edit
end

function IDECodeTabChild.__setter:save(value)
	if self._save == value then
		return
	end
	if value == false then
		self._save = false
		self:UpdateTitle()
		return
	end
	self._edit:Save()
	self._save = value
	self:UpdateTitle()
end

function IDECodeTabChild.__getter:id()
	return self._user_info.path
end

function IDECodeTabChild:Rename(name)
	self._name = name
	self:UpdateTitle()
end

function IDECodeTabChild:UpdateTitle()
	local text = self._name
	if self._save == false then
		text = text .. " *"
	end
	g_IDECenter.center.content_edit.main_tab:SetChildText(self._edit, text)
end

function IDECodeTabChild.__getter:title()
	return self._name
end

function IDECodeTabChild:CreateBySelect(info)
	self._user_info = info
	self._edit:EditFocus()
end

