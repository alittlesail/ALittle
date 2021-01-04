-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.ALittleIDE == nil then _G.ALittleIDE = {} end
local ALittleIDE = ALittleIDE
local Lua = Lua
local ALittle = ALittle
local ___rawset = rawset
local ___pairs = pairs
local ___ipairs = ipairs


ALittleIDE.IDEEnum = Lua.Class(nil, "ALittleIDE.IDEEnum")

function ALittleIDE.IDEEnum:Ctor()
	___rawset(self, "xy_type", {})
	self.xy_type[1] = "绝对位置"
	self.xy_type[2] = "起始对齐"
	self.xy_type[3] = "居中对齐"
	self.xy_type[4] = "末尾对齐"
	self.xy_type[7] = "起始百分比"
	self.xy_type[8] = "居中百分比"
	self.xy_type[9] = "末尾百分比"
	___rawset(self, "xy_rtype", {})
	self.xy_rtype["绝对位置"] = 1
	self.xy_rtype["起始对齐"] = 2
	self.xy_rtype["居中对齐"] = 3
	self.xy_rtype["末尾对齐"] = 4
	self.xy_rtype["起始百分比"] = 7
	self.xy_rtype["居中百分比"] = 8
	self.xy_rtype["末尾百分比"] = 9
	___rawset(self, "wh_type", {})
	self.wh_type[1] = "绝对大小"
	self.wh_type[2] = "百分比大小"
	self.wh_type[4] = "边距大小"
	___rawset(self, "wh_rtype", {})
	self.wh_rtype["绝对大小"] = 1
	self.wh_rtype["百分比大小"] = 2
	self.wh_rtype["边距大小"] = 4
	___rawset(self, "HALIGN_type", {})
	self.HALIGN_type[0] = "水平居左"
	self.HALIGN_type[1] = "水平居中"
	self.HALIGN_type[2] = "水平居右"
	___rawset(self, "HALIGN_rtype", {})
	self.HALIGN_rtype["水平居左"] = 0
	self.HALIGN_rtype["水平居中"] = 1
	self.HALIGN_rtype["水平居右"] = 2
	___rawset(self, "VALIGN_type", {})
	self.VALIGN_type[0] = "垂直置顶"
	self.VALIGN_type[1] = "垂直居中"
	self.VALIGN_type[2] = "垂直置底"
	___rawset(self, "VALIGN_rtype", {})
	self.VALIGN_rtype["垂直置顶"] = 0
	self.VALIGN_rtype["垂直居中"] = 1
	self.VALIGN_rtype["垂直置底"] = 2
	___rawset(self, "hv_type", {})
	self.hv_type[1] = "水平"
	self.hv_type[2] = "垂直"
	___rawset(self, "hv_rtype", {})
	self.hv_rtype["水平"] = 1
	self.hv_rtype["垂直"] = 2
	___rawset(self, "fix_type", {})
	self.fix_type[1] = "自由"
	self.fix_type[2] = "锁定"
	___rawset(self, "fix_rtype", {})
	self.fix_rtype["自由"] = 1
	self.fix_rtype["锁定"] = 2
	___rawset(self, "yn_type", {})
	self.yn_type[false] = "否"
	self.yn_type[true] = "是"
	___rawset(self, "yn_rtype", {})
	self.yn_rtype["否"] = false
	self.yn_rtype["是"] = true
	___rawset(self, "aje_type", {})
	self.aje_type[false] = "拒绝默认事件"
	self.aje_type[true] = "接受默认事件"
	___rawset(self, "aje_rtype", {})
	self.aje_rtype["拒绝默认事件"] = false
	self.aje_rtype["接受默认事件"] = true
	___rawset(self, "flip_type", {})
	self.flip_type[0] = "无"
	self.flip_type[1] = "水平"
	self.flip_type[2] = "垂直"
	self.flip_type[3] = "水平+垂直"
	___rawset(self, "flip_rtype", {})
	self.flip_rtype["无"] = 0
	self.flip_rtype["水平"] = 1
	self.flip_rtype["垂直"] = 2
	self.flip_rtype["水平+垂直"] = 3
	___rawset(self, "select_type", {})
	self.select_type[0] = "无"
	self.select_type[1] = "选择文件"
	self.select_type[2] = "选择文件夹"
	___rawset(self, "select_rtype", {})
	self.select_rtype["无"] = 0
	self.select_rtype["选择文件"] = 1
	self.select_rtype["选择文件夹"] = 2
	___rawset(self, "event_type_list", {"UIClickEvent", "UIChangedEvent", "UISelectChangedEvent", "UIFocusInEvent", "UIFocusOutEvent", "UIButtonDragEvent", "UIButtonDragBeginEvent", "UIButtonDragEndEvent", "UILongButtonDownEvent", "UIEnterKeyEvent", "UIDragDownEvent", "UIDragUpEvent", "UIDragLeftEvent", "UIDragRightEvent", "UIMoveInEvent", "UIMoveOutEvent", "UIMouseMoveEvent", "UIDropEvent", "UIDropFileEvent", "UIKeyDownEvent", "UILButtonDownEvent", "UILButtonUpEvent", "UIRButtonDownEvent", "UIRButtonUpEvent", "UIMButtonDownEvent", "UIMButtonUpEvent", "UIMButtonWheelEvent", "UIFClickEvent", "UIMClickEvent", "UITextInputEvent", "UIResizeEvent", "UIShowEvent", "UIHideEvent", "UITabKeyEvent", "UIAtKeyEvent", "UIEscKeyEvent", "UITabCloseEvent", "UIFButtonDownEvent", "UIFButtonUpEvent", "UIFDragBeginEvent", "UIFDragEvent", "UIFDragEndEvent", "UISystemSelectFileEvent", "UISystemSelectSaveEvent", "UISystemSelectDirectoryEvent"})
	___rawset(self, "add_child_change_map", {})
	self.add_child_change_map["Linear"] = true
	___rawset(self, "can_move_child_map", {})
	self.can_move_child_map["FramePlay"] = true
	self.can_move_child_map["DisplayLayout"] = true
	self.can_move_child_map["DisplayView"] = true
	self.can_move_child_map["ScrollScreen"] = true
	self.can_move_child_map["Dialog"] = true
	self.can_move_child_map["SpringButton"] = true
	self.can_move_child_map["SpringDialog"] = true
	___rawset(self, "can_resize_child_map", {})
	self.can_resize_child_map["FramePlay"] = true
	self.can_resize_child_map["DisplayLayout"] = true
	self.can_resize_child_map["DisplayView"] = true
	self.can_resize_child_map["ScrollScreen"] = true
	self.can_resize_child_map["Dialog"] = true
	___rawset(self, "text_type_display_map", {})
	self.text_type_display_map["Text"] = true
	self.text_type_display_map["TextArea"] = true
	self.text_type_display_map["TextEdit"] = true
	self.text_type_display_map["TextInput"] = true
	self.text_type_display_map["ImageEdit"] = true
	self.text_type_display_map["ImageInput"] = true
	self.text_type_display_map["RichEdit"] = true
	self.text_type_display_map["RichInput"] = true
	___rawset(self, "text_edit_display_map", {})
	self.text_edit_display_map["Text"] = true
	self.text_edit_display_map["TextArea"] = true
	self.text_edit_display_map["TextEdit"] = true
	self.text_edit_display_map["TextInput"] = true
	self.text_edit_display_map["ImageEdit"] = true
	self.text_edit_display_map["ImageInput"] = true
	self.text_edit_display_map["TextButton"] = true
	self.text_edit_display_map["TextCheckButton"] = true
	self.text_edit_display_map["TextRadioButton"] = true
	self.text_edit_display_map["SpringTextButton"] = true
	self.text_edit_display_map["SpringNumber"] = true
	___rawset(self, "child_type_list", {"DisplayLayout", "DisplayView", "Quad", "Image", "Grid9Image", "Sprite", "SpringTextButton", "Text", "TextArea", "TextInput", "TextEdit", "Slider", "Grid3", "Grid9", "Linear", "Tab", "DropDown", "ScrollBar", "ScrollList", "ScrollScreen", "Dialog", "TileTable", "TextCheckButton", "TextRadioButton", "ImageEdit", "ImageInput", "RichArea", "RichInput", "RichEdit", "ImagePlay", "SpritePlay", "SpriteNumber", "TextButton", "ScrollButton", "Triangle", "VertexImage", "Piechart", "FramePlay"})
	___rawset(self, "type_default_map", {})
	for k, v in ___ipairs(self.child_type_list) do
		local clazz = ALittle[v]
		if clazz == nil then
			ALittle.Log("没有找到 " .. v .. " 这个类")
		else
			local object = ALittle.NewObject(clazz, ALittleIDE.g_Control)
			local class_info = (object).__class
			local setter_list = class_info.__setter
			local info = {}
			info.__class = v
			for attr, func in ___pairs(setter_list) do
				info[attr] = object[attr]
			end
			self.type_default_map[v] = info
		end
	end
	___rawset(self, "can_add_child_map", {})
	self.can_add_child_map["DisplayLayout"] = true
	self.can_add_child_map["DisplayView"] = true
	self.can_add_child_map["Linear"] = true
	self.can_add_child_map["ScrollScreen"] = true
	self.can_add_child_map["Dialog"] = true
	self.can_add_child_map["Tab"] = true
	self.can_add_child_map["TileTable"] = true
	self.can_add_child_map["ScrollList"] = true
	self.can_add_child_map["FramePlay"] = true
	self.can_add_child_map["SpringButton"] = true
	self.can_add_child_map["SpringCheckButton"] = true
	self.can_add_child_map["SpringRadioButton"] = true
	self.can_add_child_map["SpringDialog"] = true
	___rawset(self, "child_show_map", {})
	self.child_show_map["Grid3"] = {"show_up", "show_center", "show_down"}
	self.child_show_map["Grid9"] = {"show_left_top", "show_left_center", "show_left_bottom", "show_center_top", "show_center_center", "show_center_bottom", "show_right_top", "show_right_center", "show_right_bottom"}
	___rawset(self, "child_show_map_map", {})
	for k, list in ___pairs(self.child_show_map) do
		local map = {}
		for _, name in ___ipairs(list) do
			map[name] = true
		end
		self.child_show_map_map[k] = map
	end
	___rawset(self, "nature_show_map", {})
	self.nature_show_map["TextButton"] = {"show_text", "show_up", "show_down", "show_over", "show_disabled", "show_down_text", "show_over_text", "show_disabled_text"}
	self.nature_show_map["SpringTextButton"] = {"show_text", "show_up", "show_disabled", "show_disabled_text"}
	self.nature_show_map["ScrollButton"] = {"show_text", "show_up", "show_down", "show_over", "show_disabled", "show_down_text", "show_over_text", "show_disabled_text"}
	self.nature_show_map["Tab"] = {"show_head_background"}
	self.nature_show_map["DropDown"] = {"show_text", "show_up", "show_down", "show_over", "show_disabled", "show_selected_up", "show_selected_down", "show_selected_over", "show_selected_disabled", "show_over_text", "show_down_text", "show_disabled_text", "show_selected_text", "show_selected_over_text", "show_selected_down_text", "show_selected_disabled_text", "show_background", "show_scrollbar"}
	self.nature_show_map["ScrollBar"] = {"up_button", "down_button", "bar_button", "bar_background"}
	self.nature_show_map["ScrollScreen"] = {"container", "right_scrollbar", "bottom_scrollbar"}
	self.nature_show_map["Dialog"] = {"show_background", "show_head_drag", "show_title", "show_close_button"}
	self.nature_show_map["TextCheckButton"] = {"show_text", "show_up", "show_down", "show_over", "show_disabled", "show_selected_up", "show_selected_down", "show_selected_over", "show_selected_disabled", "show_over_text", "show_down_text", "show_disabled_text", "show_selected_text", "show_selected_over_text", "show_selected_down_text", "show_selected_disabled_text"}
	self.nature_show_map["TextRadioButton"] = {"show_text", "show_up", "show_down", "show_over", "show_disabled", "show_selected_up", "show_selected_down", "show_selected_over", "show_selected_disabled", "show_over_text", "show_down_text", "show_disabled_text", "show_selected_text", "show_selected_over_text", "show_selected_down_text", "show_selected_disabled_text"}
	self.nature_show_map["ImageEdit"] = {"show_up", "show_down", "show_over", "show_disabled"}
	self.nature_show_map["ImageInput"] = {"show_up", "show_down", "show_over", "show_disabled"}
	self.nature_show_map["Slider"] = {"bar_background", "bar_button"}
	self.nature_show_map["ScrollList"] = {"right_scrollbar"}
	self.nature_show_map["RichEdit"] = {"start_cursor", "end_cursor"}
	self.nature_show_map["RichInput"] = {"start_cursor", "end_cursor"}
	___rawset(self, "nature_show_map_map", {})
	for k, list in ___pairs(self.child_show_map) do
		local map = {}
		for _, name in ___ipairs(list) do
			map[name] = true
		end
		self.nature_show_map_map[k] = map
	end
end

ALittleIDE.g_IDEEnum = ALittleIDE.IDEEnum()
end