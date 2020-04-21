
module("ABrowser", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})

assert(ABrowser.OPSBaseDialog, " extends class:ABrowser.OPSBaseDialog is nil")
OPSChoiceDialog = Lua.Class(ABrowser.OPSBaseDialog, "ABrowser.OPSChoiceDialog")

function OPSChoiceDialog:Ctor(ctrl_sys)
end

function OPSChoiceDialog:Show()
	self._title.text = self._dialog_config.title
	if self._table_ctrl == nil then
		local sub_menu = {}
		sub_menu.table = self._dialog_config.__table_data
		self._table_ctrl = OPSTableData(g_Control, self._center, sub_menu, true)
		self._table_ctrl:AddEventListener(___all_struct[-1600012379], self, self.HandleChoose)
		self._container:AddChild(self._table_ctrl)
	end
	self:ShowFromModal()
end

function OPSChoiceDialog:HandleChoose(event)
	self:HideFromModal()
	self:DispatchEvent(___all_struct[-1600012379], event)
end

