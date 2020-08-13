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
name_list = {"unit_width","unit_height","unit_left","unit_right","unit_top","unit_bottom","unit_real_width","unit_real_height","project_name","texture_path","empty_name","data_path"},
type_list = {"int","int","int","int","int","int","int","int","string","string","string","string"},
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
		self._data.project_name = ""
	end
	if self._data.texture_path == nil then
		self._data.texture_path = ""
	end
	if self._data.empty_name == nil then
		self._data.empty_name = ""
	end
	if self._data.data_path == nil then
		self._data.data_path = ""
	end
	if self._data.unit_width == nil then
		self._data.unit_width = 100
	end
	if self._data.unit_height == nil then
		self._data.unit_height = 100
	end
	if self._data.unit_left == nil then
		self._data.unit_left = 0
	end
	if self._data.unit_right == nil then
		self._data.unit_right = 0
	end
	if self._data.unit_top == nil then
		self._data.unit_top = 0
	end
	if self._data.unit_bottom == nil then
		self._data.unit_bottom = 0
	end
	self._data.unit_real_width = self._data.unit_width - self._data.unit_left - self._data.unit_right
	self._data.unit_real_height = self._data.unit_height - self._data.unit_top - self._data.unit_bottom
	self._setting_project_name_input.text = self._data.project_name
	self._setting_texture_path_input.text = self._data.texture_path
	self._unit_empty_name_input.text = self._data.empty_name
	self._setting_data_path_input.text = self._data.data_path
	self._unit_width_input.text = self._data.unit_width
	self._unit_height_input.text = self._data.unit_height
	self._unit_left_input.text = self._data.unit_left
	self._unit_right_input.text = self._data.unit_right
	self._unit_top_input.text = self._data.unit_top
	self._unit_bottom_input.text = self._data.unit_bottom
end

function GBRMaker.MainSettingDialog:HandleSettingCancelClick(event)
	self.visible = false
end

function GBRMaker.MainSettingDialog:HandleSettingConfirmClick(event)
	local unit_width = ALittle.Math_ToInt(self._unit_width_input.text)
	local unit_height = ALittle.Math_ToInt(self._unit_height_input.text)
	local unit_left = ALittle.Math_ToInt(self._unit_left_input.text)
	local unit_right = ALittle.Math_ToInt(self._unit_right_input.text)
	local unit_top = ALittle.Math_ToInt(self._unit_top_input.text)
	local unit_bottom = ALittle.Math_ToInt(self._unit_bottom_input.text)
	if unit_width == nil or unit_width < 0 or unit_height == nil or unit_height < 0 or unit_left == nil or unit_left < 0 or unit_right == nil or unit_right < 0 or unit_top == nil or unit_top < 0 or unit_bottom == nil or unit_bottom < 0 then
		g_AUITool:ShowNotice("提示", "请输入正整数")
		return
	end
	local module_path = "Module/" .. self._setting_project_name_input.text
	if ALittle.File_GetFileAttr(module_path) == nil then
		g_AUITool:ShowNotice("提示", "项目不存在")
		return
	end
	if ALittle.File_GetFileAttr(module_path .. "/Texture/" .. self._setting_texture_path_input.text) == nil then
		g_AUITool:ShowNotice("提示", "格子图片路径不存在")
		return
	end
	if ALittle.File_GetFileAttr(module_path .. "/Other/" .. self._setting_data_path_input.text) == nil then
		g_AUITool:ShowNotice("提示", "场景数据路径不存在")
		return
	end
	if ALittle.File_GetFileAttr(module_path .. "/Texture/" .. self._setting_texture_path_input.text .. "/" .. self._unit_empty_name_input.text) == nil then
		g_AUITool:ShowNotice("提示", "空格子图片不存在")
		return
	end
	self._data.unit_width = unit_width
	self._data.unit_height = unit_height
	self._data.unit_left = unit_left
	self._data.unit_right = unit_right
	self._data.unit_top = unit_top
	self._data.unit_bottom = unit_bottom
	self._data.unit_real_width = self._data.unit_width - self._data.unit_left - self._data.unit_right
	self._data.unit_real_height = self._data.unit_height - self._data.unit_top - self._data.unit_bottom
	self._data.project_name = self._setting_project_name_input.text
	self._data.texture_path = self._setting_texture_path_input.text
	self._data.data_path = self._setting_data_path_input.text
	self._data.empty_name = self._unit_empty_name_input.text
	GBRMaker.g_GConfig:SetConfig("setting_data", self._data)
	self.visible = false
	local changed_event = {}
	changed_event.data = self._data
	self:DispatchEvent(___all_struct[-449066808], event)
end

end