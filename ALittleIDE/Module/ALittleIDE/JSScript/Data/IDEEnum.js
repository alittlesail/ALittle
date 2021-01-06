{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


ALittleIDE.IDEEnum = JavaScript.Class(undefined, {
	Ctor : function() {
		this.xy_type = new Map();
		this.xy_type.set(1, "绝对位置");
		this.xy_type.set(2, "起始对齐");
		this.xy_type.set(3, "居中对齐");
		this.xy_type.set(4, "末尾对齐");
		this.xy_type.set(7, "起始百分比");
		this.xy_type.set(8, "居中百分比");
		this.xy_type.set(9, "末尾百分比");
		this.xy_rtype = {};
		this.xy_rtype["绝对位置"] = 1;
		this.xy_rtype["起始对齐"] = 2;
		this.xy_rtype["居中对齐"] = 3;
		this.xy_rtype["末尾对齐"] = 4;
		this.xy_rtype["起始百分比"] = 7;
		this.xy_rtype["居中百分比"] = 8;
		this.xy_rtype["末尾百分比"] = 9;
		this.wh_type = new Map();
		this.wh_type.set(1, "绝对大小");
		this.wh_type.set(2, "百分比大小");
		this.wh_type.set(4, "边距大小");
		this.wh_rtype = {};
		this.wh_rtype["绝对大小"] = 1;
		this.wh_rtype["百分比大小"] = 2;
		this.wh_rtype["边距大小"] = 4;
		this.HALIGN_type = new Map();
		this.HALIGN_type.set(0, "水平居左");
		this.HALIGN_type.set(1, "水平居中");
		this.HALIGN_type.set(2, "水平居右");
		this.HALIGN_rtype = {};
		this.HALIGN_rtype["水平居左"] = 0;
		this.HALIGN_rtype["水平居中"] = 1;
		this.HALIGN_rtype["水平居右"] = 2;
		this.VALIGN_type = new Map();
		this.VALIGN_type.set(0, "垂直置顶");
		this.VALIGN_type.set(1, "垂直居中");
		this.VALIGN_type.set(2, "垂直置底");
		this.VALIGN_rtype = {};
		this.VALIGN_rtype["垂直置顶"] = 0;
		this.VALIGN_rtype["垂直居中"] = 1;
		this.VALIGN_rtype["垂直置底"] = 2;
		this.hv_type = new Map();
		this.hv_type.set(1, "水平");
		this.hv_type.set(2, "垂直");
		this.hv_rtype = {};
		this.hv_rtype["水平"] = 1;
		this.hv_rtype["垂直"] = 2;
		this.fix_type = new Map();
		this.fix_type.set(1, "自由");
		this.fix_type.set(2, "锁定");
		this.fix_rtype = {};
		this.fix_rtype["自由"] = 1;
		this.fix_rtype["锁定"] = 2;
		this.yn_type = new Map();
		this.yn_type.set(false, "否");
		this.yn_type.set(true, "是");
		this.yn_rtype = {};
		this.yn_rtype["否"] = false;
		this.yn_rtype["是"] = true;
		this.aje_type = new Map();
		this.aje_type.set(false, "拒绝默认事件");
		this.aje_type.set(true, "接受默认事件");
		this.aje_rtype = {};
		this.aje_rtype["拒绝默认事件"] = false;
		this.aje_rtype["接受默认事件"] = true;
		this.flip_type = new Map();
		this.flip_type.set(0, "无");
		this.flip_type.set(1, "水平");
		this.flip_type.set(2, "垂直");
		this.flip_type.set(3, "水平+垂直");
		this.flip_rtype = {};
		this.flip_rtype["无"] = 0;
		this.flip_rtype["水平"] = 1;
		this.flip_rtype["垂直"] = 2;
		this.flip_rtype["水平+垂直"] = 3;
		this.select_type = new Map();
		this.select_type.set(0, "无");
		this.select_type.set(1, "选择文件");
		this.select_type.set(2, "选择文件夹");
		this.select_rtype = {};
		this.select_rtype["无"] = 0;
		this.select_rtype["选择文件"] = 1;
		this.select_rtype["选择文件夹"] = 2;
		this.event_type_list = ["UIClickEvent", "UIChangedEvent", "UISelectChangedEvent", "UIFocusInEvent", "UIFocusOutEvent", "UIButtonDragEvent", "UIButtonDragBeginEvent", "UIButtonDragEndEvent", "UILongButtonDownEvent", "UIEnterKeyEvent", "UIDragDownEvent", "UIDragUpEvent", "UIDragLeftEvent", "UIDragRightEvent", "UIMoveInEvent", "UIMoveOutEvent", "UIMouseMoveEvent", "UIDropEvent", "UIDropFileEvent", "UIKeyDownEvent", "UILButtonDownEvent", "UILButtonUpEvent", "UIRButtonDownEvent", "UIRButtonUpEvent", "UIMButtonDownEvent", "UIMButtonUpEvent", "UIMButtonWheelEvent", "UIFClickEvent", "UIMClickEvent", "UITextInputEvent", "UIResizeEvent", "UIShowEvent", "UIHideEvent", "UITabKeyEvent", "UIAtKeyEvent", "UIEscKeyEvent", "UITabCloseEvent", "UIFButtonDownEvent", "UIFButtonUpEvent", "UIFDragBeginEvent", "UIFDragEvent", "UIFDragEndEvent", "UISystemSelectFileEvent", "UISystemSelectSaveEvent", "UISystemSelectDirectoryEvent"];
		this.add_child_change_map = {};
		this.add_child_change_map["Linear"] = true;
		this.can_move_child_map = {};
		this.can_move_child_map["FramePlay"] = true;
		this.can_move_child_map["DisplayLayout"] = true;
		this.can_move_child_map["DisplayView"] = true;
		this.can_move_child_map["ScrollScreen"] = true;
		this.can_move_child_map["Dialog"] = true;
		this.can_move_child_map["SpringButton"] = true;
		this.can_move_child_map["SpringDialog"] = true;
		this.can_resize_child_map = {};
		this.can_resize_child_map["FramePlay"] = true;
		this.can_resize_child_map["DisplayLayout"] = true;
		this.can_resize_child_map["DisplayView"] = true;
		this.can_resize_child_map["ScrollScreen"] = true;
		this.can_resize_child_map["Dialog"] = true;
		this.text_type_display_map = {};
		this.text_type_display_map["Text"] = true;
		this.text_type_display_map["TextArea"] = true;
		this.text_type_display_map["TextEdit"] = true;
		this.text_type_display_map["TextInput"] = true;
		this.text_type_display_map["ImageEdit"] = true;
		this.text_type_display_map["ImageInput"] = true;
		this.text_type_display_map["RichEdit"] = true;
		this.text_type_display_map["RichInput"] = true;
		this.text_edit_display_map = {};
		this.text_edit_display_map["Text"] = true;
		this.text_edit_display_map["TextArea"] = true;
		this.text_edit_display_map["TextEdit"] = true;
		this.text_edit_display_map["TextInput"] = true;
		this.text_edit_display_map["ImageEdit"] = true;
		this.text_edit_display_map["ImageInput"] = true;
		this.text_edit_display_map["TextButton"] = true;
		this.text_edit_display_map["TextCheckButton"] = true;
		this.text_edit_display_map["TextRadioButton"] = true;
		this.text_edit_display_map["SpringTextButton"] = true;
		this.text_edit_display_map["SpringNumber"] = true;
		this.child_type_list = ["DisplayLayout", "DisplayView", "Quad", "Image", "Grid9Image", "Sprite", "SpringTextButton", "Text", "TextArea", "TextInput", "TextEdit", "Slider", "Grid3", "Grid9", "Linear", "Tab", "DropDown", "ScrollBar", "ScrollList", "ScrollScreen", "Dialog", "TileTable", "TextCheckButton", "TextRadioButton", "ImageEdit", "ImageInput", "RichArea", "RichInput", "RichEdit", "ImagePlay", "SpritePlay", "SpriteNumber", "TextButton", "ScrollButton", "Triangle", "VertexImage", "Piechart", "FramePlay"];
		this.type_default_map = {};
		let ___OBJECT_1 = this.child_type_list;
		for (let k = 1; k <= ___OBJECT_1.length; ++k) {
			let v = ___OBJECT_1[k - 1];
			if (v === undefined) break;
			let clazz = ALittle[v];
			if (clazz === undefined) {
				ALittle.Log("没有找到 " + v + " 这个类");
			} else {
				let object = ALittle.NewObject(clazz, ALittleIDE.g_Control);
				let class_info = (object).__class;
				let setter_list = class_info.__setter;
				let info = {};
				info.__class = v;
				let ___OBJECT_2 = setter_list;
				for (let attr in ___OBJECT_2) {
					let func = ___OBJECT_2[attr];
					if (func === undefined) continue;
					info[attr] = object[attr];
				}
				this.type_default_map[v] = info;
			}
		}
		this.can_add_child_map = {};
		this.can_add_child_map["DisplayLayout"] = true;
		this.can_add_child_map["DisplayView"] = true;
		this.can_add_child_map["Linear"] = true;
		this.can_add_child_map["ScrollScreen"] = true;
		this.can_add_child_map["Dialog"] = true;
		this.can_add_child_map["Tab"] = true;
		this.can_add_child_map["TileTable"] = true;
		this.can_add_child_map["ScrollList"] = true;
		this.can_add_child_map["FramePlay"] = true;
		this.can_add_child_map["SpringButton"] = true;
		this.can_add_child_map["SpringCheckButton"] = true;
		this.can_add_child_map["SpringRadioButton"] = true;
		this.can_add_child_map["SpringDialog"] = true;
		this.child_show_map = {};
		this.child_show_map["Grid3"] = ["show_up", "show_center", "show_down"];
		this.child_show_map["Grid9"] = ["show_left_top", "show_left_center", "show_left_bottom", "show_center_top", "show_center_center", "show_center_bottom", "show_right_top", "show_right_center", "show_right_bottom"];
		this.child_show_map_map = {};
		let ___OBJECT_3 = this.child_show_map;
		for (let k in ___OBJECT_3) {
			let list = ___OBJECT_3[k];
			if (list === undefined) continue;
			let map = {};
			let ___OBJECT_4 = list;
			for (let _ = 1; _ <= ___OBJECT_4.length; ++_) {
				let name = ___OBJECT_4[_ - 1];
				if (name === undefined) break;
				map[name] = true;
			}
			this.child_show_map_map[k] = map;
		}
		this.nature_show_map = {};
		this.nature_show_map["TextButton"] = ["show_text", "show_up", "show_down", "show_over", "show_disabled", "show_down_text", "show_over_text", "show_disabled_text"];
		this.nature_show_map["SpringTextButton"] = ["show_text", "show_up", "show_disabled", "show_disabled_text"];
		this.nature_show_map["ScrollButton"] = ["show_text", "show_up", "show_down", "show_over", "show_disabled", "show_down_text", "show_over_text", "show_disabled_text"];
		this.nature_show_map["Tab"] = ["show_head_background"];
		this.nature_show_map["DropDown"] = ["show_text", "show_up", "show_down", "show_over", "show_disabled", "show_selected_up", "show_selected_down", "show_selected_over", "show_selected_disabled", "show_over_text", "show_down_text", "show_disabled_text", "show_selected_text", "show_selected_over_text", "show_selected_down_text", "show_selected_disabled_text", "show_background", "show_scrollbar"];
		this.nature_show_map["ScrollBar"] = ["up_button", "down_button", "bar_button", "bar_background"];
		this.nature_show_map["ScrollScreen"] = ["container", "right_scrollbar", "bottom_scrollbar"];
		this.nature_show_map["Dialog"] = ["show_background", "show_head_drag", "show_title", "show_close_button"];
		this.nature_show_map["TextCheckButton"] = ["show_text", "show_up", "show_down", "show_over", "show_disabled", "show_selected_up", "show_selected_down", "show_selected_over", "show_selected_disabled", "show_over_text", "show_down_text", "show_disabled_text", "show_selected_text", "show_selected_over_text", "show_selected_down_text", "show_selected_disabled_text"];
		this.nature_show_map["TextRadioButton"] = ["show_text", "show_up", "show_down", "show_over", "show_disabled", "show_selected_up", "show_selected_down", "show_selected_over", "show_selected_disabled", "show_over_text", "show_down_text", "show_disabled_text", "show_selected_text", "show_selected_over_text", "show_selected_down_text", "show_selected_disabled_text"];
		this.nature_show_map["ImageEdit"] = ["show_up", "show_down", "show_over", "show_disabled"];
		this.nature_show_map["ImageInput"] = ["show_up", "show_down", "show_over", "show_disabled"];
		this.nature_show_map["Slider"] = ["bar_background", "bar_button"];
		this.nature_show_map["ScrollList"] = ["right_scrollbar"];
		this.nature_show_map["RichEdit"] = ["start_cursor", "end_cursor"];
		this.nature_show_map["RichInput"] = ["start_cursor", "end_cursor"];
		this.nature_show_map_map = {};
		let ___OBJECT_5 = this.child_show_map;
		for (let k in ___OBJECT_5) {
			let list = ___OBJECT_5[k];
			if (list === undefined) continue;
			let map = {};
			let ___OBJECT_6 = list;
			for (let _ = 1; _ <= ___OBJECT_6.length; ++_) {
				let name = ___OBJECT_6[_ - 1];
				if (name === undefined) break;
				map[name] = true;
			}
			this.nature_show_map_map[k] = map;
		}
	},
}, "ALittleIDE.IDEEnum");

ALittleIDE.g_IDEEnum = ALittle.NewObject(ALittleIDE.IDEEnum);
}