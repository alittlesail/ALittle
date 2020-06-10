
module("ABrowser", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs
local ___coroutine = coroutine

assert(OPSBaseDialog, " extends class:OPSBaseDialog is nil")
OPSCustomDialog = ALittle.Class(OPSBaseDialog, "ABrowser.OPSCustomDialog")

function OPSCustomDialog:Ctor(ctrl_sys)
end

function OPSCustomDialog:Show()
	self._title.text = self._dialog_config.title
	self._ctrl_list = {}
	local ctrl_list_count = 0
	for k, field_config in ___ipairs(self._dialog_config.field) do
		local clazz = _G["ABrowser"][field_config.input_type]
		if clazz ~= nil then
			ctrl_list_count = ctrl_list_count + 1
			self._ctrl_list[ctrl_list_count] = ALittle.NewObject(clazz, g_Control, self._center, field_config, self._data)
		else
			ALittle.Log("找不到类:" .. field_config.input_type)
		end
	end
	self._container:RemoveAllChild()
	local max_width = self._container.width
	for k, control in ___ipairs(self._ctrl_list) do
		if control.width > max_width then
			max_width = control.width
		end
		self._container:AddChild(control)
	end
	local dialog_width = 0.0
	dialog_width = dialog_width + max_width
	dialog_width = dialog_width + self._container.width_value
	dialog_width = dialog_width + self._layer.width_value
	self.height = dialog_width
	local dialog_height = 0.0
	dialog_height = dialog_height + self._g3.up_size
	dialog_height = dialog_height + self._g3.down_size
	dialog_height = dialog_height + self._container.real_height
	dialog_height = dialog_height + self._container.height_value
	dialog_height = dialog_height + self._layer.height_value
	if dialog_height > A_UISystem.view_height then
		dialog_height = A_UISystem.view_height
	end
	self.height = dialog_height
	self:ShowFromModal()
end

