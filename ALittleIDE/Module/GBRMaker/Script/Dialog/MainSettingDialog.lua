-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.GBRMaker == nil then _G.GBRMaker = {} end
local ___pairs = pairs
local ___ipairs = ipairs
local ___all_struct = ALittle.GetAllStruct()

ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(-1302885650, "GBRMaker.UIMainSettingChangedEvent", {
name = "GBRMaker.UIMainSettingChangedEvent", ns_name = "GBRMaker", rl_name = "UIMainSettingChangedEvent", hash_code = -1302885650,
name_list = {"target","data"},
type_list = {"ALittle.DisplayObject","GBRMaker.MainSettingData"},
option_map = {}
})
ALittle.RegStruct(-982324742, "GBRMaker.MainSettingData", {
name = "GBRMaker.MainSettingData", ns_name = "GBRMaker", rl_name = "MainSettingData", hash_code = -982324742,
name_list = {"center_x","center_y","image_w","image_h","unit_length","project_name","data_path"},
type_list = {"int","int","int","int","int","string","string"},
option_map = {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name = "ALittle.UIClickEvent", ns_name = "ALittle", rl_name = "UIClickEvent", hash_code = -449066808,
name_list = {"target","is_drag"},
type_list = {"ALittle.DisplayObject","bool"},
option_map = {}
})

assert(ALittle.Dialog, " extends class:ALittle.Dialog is nil")
GBRMaker.MainSettingDialog = Lua.Class(ALittle.Dialog, "GBRMaker.MainSettingDialog")

function GBRMaker.MainSettingDialog.__getter:data()
	return self._data
end

function GBRMaker.MainSettingDialog:TCtor()
	self._data = GBRMaker.g_GConfig:GetConfig("setting_data", {})
	if self._data.project_name == nil then
		self._data.project_name = "GBR"
	end
	if self._data.data_path == nil then
		self._data.data_path = "Scene"
	end
	if self._data.center_x == nil then
		self._data.center_x = 0
	end
	if self._data.center_y == nil then
		self._data.center_y = 0
	end
	if self._data.image_w == nil then
		self._data.image_w = 100
	end
	if self._data.image_h == nil then
		self._data.image_h = 100
	end
	if self._data.unit_length == nil then
		self._data.unit_length = 100
	end
	self._project_name_input.text = self._data.project_name
	self._data_path_input.text = self._data.data_path
	self._center_x_input.text = self._data.center_x
	self._center_y_input.text = self._data.center_y
	self._image_w_input.text = self._data.image_w
	self._image_h_input.text = self._data.image_h
	self._unit_length_input.text = self._data.unit_length
end

function GBRMaker.MainSettingDialog:HandleSettingCancelClick(event)
	self.visible = false
end

function GBRMaker.MainSettingDialog:HandleSettingConfirmClick(event)
	local center_x = ALittle.Math_ToInt(self._center_x_input.text)
	local center_y = ALittle.Math_ToInt(self._center_y_input.text)
	local image_w = ALittle.Math_ToInt(self._image_w_input.text)
	local image_h = ALittle.Math_ToInt(self._image_h_input.text)
	local unit_length = ALittle.Math_ToInt(self._unit_length_input.text)
	if center_x == nil or center_x < 0 or center_y == nil or center_y < 0 or image_w == nil or image_w < 0 or image_h == nil or image_h < 0 or unit_length == nil or unit_length < 0 then
		g_AUITool:ShowNotice("提示", "请输入正整数")
		return
	end
	local module_path = "Module/" .. self._project_name_input.text
	if ALittle.File_GetFileAttr(module_path) == nil then
		g_AUITool:ShowNotice("提示", "项目不存在")
		return
	end
	if ALittle.File_GetFileAttr(module_path .. "/Other/" .. self._data_path_input.text) == nil then
		g_AUITool:ShowNotice("提示", "场景数据路径不存在")
		return
	end
	self._data.center_x = center_x
	self._data.center_y = center_y
	self._data.image_w = image_w
	self._data.image_h = image_h
	self._data.unit_length = unit_length
	self._data.project_name = self._project_name_input.text
	self._data.data_path = self._data_path_input.text
	GBRMaker.g_GConfig:SetConfig("setting_data", self._data)
	self.visible = false
	local changed_event = {}
	changed_event.data = self._data
	self:DispatchEvent(___all_struct[-449066808], event)
end

end