{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};


ALittleIDE.DisplayObjectS = JavaScript.Class(undefined, {
	Ctor : function(user_info, tab_child, tree_logic) {
		this._layer_name = "ide_setting_displayobject";
		this._base = user_info.base;
		this._default = user_info.default;
		this._object = user_info.object;
		this._tab_child = tab_child;
		this._tree_logic = tree_logic;
	},
	get base() {
		return this._base;
	},
	get default() {
		return this._default;
	},
	get x_value() {
		return this._x_value;
	},
	get y_value() {
		return this._y_value;
	},
	get width_value() {
		return this._width_value;
	},
	get height_value() {
		return this._height_value;
	},
	get title() {
		return this._default.__class;
	},
	get layer() {
		if (this._layer === undefined) {
			this._layer = ALittleIDE.g_Control.CreateControl(this._layer_name, this);
			this.LoadNatureBase();
		}
		return this._layer;
	},
	LoadNatureBase : function() {
		this.LoadEnumData("x_type", ALittleIDE.g_IDEEnum.xy_type);
		if (this._default.x === 0) {
			if (this._base.x !== undefined) {
				this._x_value.text = this._base.x;
			} else if (this._base.x_value !== undefined) {
				this._x_value.text = this._base.x_value;
			} else if (this._default.x_value !== undefined) {
				this._x_value.text = this._default.x_value;
			}
		} else if (this._default.x_value === 0) {
			if (this._base.x !== undefined) {
				this._x_value.text = this._base.x;
			} else if (this._base.x_value !== undefined) {
				this._x_value.text = this._base.x_value;
			} else if (this._default.x !== undefined) {
				this._x_value.text = this._default.x;
			}
		} else if (this._default.x !== 0 && this._default.x_value !== 0) {
			ALittle.Log("x value error");
		}
		this.LoadEnumData("y_type", ALittleIDE.g_IDEEnum.xy_type);
		if (this._default.y === 0) {
			if (this._base.y !== undefined) {
				this._y_value.text = this._base.y;
			} else if (this._base.y_value !== undefined) {
				this._y_value.text = this._base.y_value;
			} else if (this._default.y_value !== undefined) {
				this._y_value.text = this._default.y_value;
			}
		} else if (this._default.y_value === 0) {
			if (this._base.y !== undefined) {
				this._y_value.text = this._base.y;
			} else if (this._base.y_value !== undefined) {
				this._y_value.text = this._base.y_value;
			} else if (this._default.y !== undefined) {
				this._y_value.text = this._default.y;
			}
		} else if (this._default.y !== 0 && this._default.y_value !== 0) {
			ALittle.Log("y value error");
		}
		this.LoadEnumData("width_type", ALittleIDE.g_IDEEnum.wh_type);
		if (this._default.width === 0) {
			if (this._base.width !== undefined) {
				this._width_value.text = this._base.width;
			} else if (this._base.width_value !== undefined) {
				this._width_value.text = this._base.width_value;
			} else if (this._default.width_value !== undefined) {
				this._width_value.text = this._default.width_value;
			}
		} else if (this._default.width_value === 0) {
			if (this._base.width !== undefined) {
				this._width_value.text = this._base.width;
			} else if (this._base.width_value !== undefined) {
				this._width_value.text = this._base.width_value;
			} else if (this._default.width !== undefined) {
				this._width_value.text = this._default.width;
			}
		} else if (this._default.width !== 0 && this._default.width_value !== 0) {
			ALittle.Log("width value error");
		}
		this.LoadEnumData("height_type", ALittleIDE.g_IDEEnum.wh_type);
		if (this._default.height === 0) {
			if (this._base.height !== undefined) {
				this._height_value.text = this._base.height;
			} else if (this._base.height_value !== undefined) {
				this._height_value.text = this._base.height_value;
			} else if (this._default.height_value !== undefined) {
				this._height_value.text = this._default.height_value;
			}
		} else if (this._default.height_value === 0) {
			if (this._base.height !== undefined) {
				this._height_value.text = this._base.height;
			} else if (this._base.height_value !== undefined) {
				this._height_value.text = this._base.height_value;
			} else if (this._default.height !== undefined) {
				this._height_value.text = this._default.height;
			}
		} else if (this._default.height !== 0 && this._default.height_value !== 0) {
			ALittle.Log("height value error");
		}
		this.LoadColorData("red");
		this.LoadColorData("green");
		this.LoadColorData("blue");
		this.LoadColorData("alpha");
		this.LoadValueData("scale_x");
		this.LoadValueData("scale_y");
		this.LoadValueData("center_x");
		this.LoadValueData("center_y");
		this.LoadValueData("angle");
		this.LoadCheckBoolData("hand_cursor", false);
		this.LoadCheckBoolData("visible", true);
		this.LoadCheckBoolData("disabled", true);
		this._hand_cursor_check_text.event_trans_target = this._hand_cursor;
		this._visible_check_text.event_trans_target = this._visible;
		this._disabled_check_text.event_trans_target = this._disabled;
		this.LoadDefaultNilString("__link");
		this.LoadShowTypeData("__event");
		this.LoadShowTypeDataForTargetClass("__target_class");
		this.LoadDefaultNilString("description");
	},
	HandleCommonInputFOCUSIN : function(event) {
		event.target._user_data = event.target.text;
	},
	SetXType : function(x_type, revoke_bind) {
		if (x_type === undefined) {
			return;
		}
		this._x_type.text = ALittleIDE.g_IDEEnum.xy_type.get(x_type);
		let list = ALittleIDE.g_IDEEnum.xy_rtype;
		this.TypeSelectChange("x_type", list, true, revoke_bind);
	},
	HandleXTypeSELECT_CHANGE : function(event) {
		let object = this._object;
		let target_x = object.x;
		let new_x = target_x;
		let list = ALittleIDE.g_IDEEnum.xy_rtype;
		let revoke_bind = ALittle.NewObject(ALittle.RevokeBind);
		this.TypeSelectChange("x_type", list, true, revoke_bind);
		if (object.x_type === 1) {
			new_x = target_x;
		} else if (object.x_type === 2) {
			new_x = target_x;
		} else if (object.x_type === 3) {
			new_x = target_x - (object.show_parent.width - object.width) / 2;
		} else if (object.x_type === 4) {
			new_x = object.show_parent.width - object.width - target_x;
		} else if (object.x_type === 7) {
			if (object.show_parent.width === 0) {
				new_x = 0;
			} else {
				new_x = target_x / object.show_parent.width;
			}
		} else if (object.x_type === 8) {
			if (object.show_parent.width === 0) {
				new_x = 0;
			} else {
				new_x = (target_x - (object.show_parent.width - object.width) / 2) / object.show_parent.width;
			}
		} else if (object.x_type === 9) {
			if (object.show_parent.width - object.width === 0) {
				new_x = 0;
			} else {
				new_x = 1 - target_x / (object.show_parent.width - object.width);
			}
		}
		this.SetXValue(new_x, revoke_bind);
		this._tab_child.revoke_list.PushRevoke(revoke_bind);
	},
	SetYType : function(y_type, revoke_bind) {
		if (y_type === undefined) {
			return;
		}
		this._y_type.text = ALittleIDE.g_IDEEnum.xy_type.get(y_type);
		let list = ALittleIDE.g_IDEEnum.xy_rtype;
		this.TypeSelectChange("y_type", list, true, revoke_bind);
	},
	HandleYTypeSELECT_CHANGE : function(event) {
		let object = this._object;
		let target_y = object.y;
		let new_y = target_y;
		let list = ALittleIDE.g_IDEEnum.xy_rtype;
		let revoke_bind = ALittle.NewObject(ALittle.RevokeBind);
		this.TypeSelectChange("y_type", list, true, revoke_bind);
		if (object.y_type === 1) {
			new_y = target_y;
		} else if (object.y_type === 2) {
			new_y = target_y;
		} else if (object.y_type === 3) {
			new_y = target_y - (object.show_parent.height - object.height) / 2;
		} else if (object.y_type === 4) {
			new_y = object.show_parent.height - object.height - target_y;
		} else if (object.y_type === 7) {
			if (object.show_parent.height === 0) {
				new_y = 0;
			} else {
				new_y = target_y / object.show_parent.height;
			}
		} else if (object.y_type === 8) {
			if (object.show_parent.height === 0) {
				new_y = 0;
			} else {
				new_y = (target_y - (object.show_parent.height - object.height) / 2) / object.show_parent.height;
			}
		} else if (object.y_type === 9) {
			if (object.show_parent.height - object.height === 0) {
				new_y = 0;
			} else {
				new_y = 1 - target_y / (object.show_parent.height - object.height);
			}
		}
		this.SetYValue(new_y, revoke_bind);
		this._tab_child.revoke_list.PushRevoke(revoke_bind);
	},
	SetWType : function(width_type, revoke_bind) {
		if (width_type === undefined) {
			return;
		}
		this._width_type.text = ALittleIDE.g_IDEEnum.wh_type.get(width_type);
		let list = ALittleIDE.g_IDEEnum.wh_rtype;
		this.TypeSelectChange("width_type", list, true, revoke_bind);
	},
	HandleWTypeSELECT_CHANGE : function(event) {
		let list = ALittleIDE.g_IDEEnum.wh_rtype;
		this.TypeSelectChange("width_type", list, true);
	},
	SetHType : function(height_type, revoke_bind) {
		if (height_type === undefined) {
			return;
		}
		this._height_type.text = ALittleIDE.g_IDEEnum.wh_type.get(height_type);
		let list = ALittleIDE.g_IDEEnum.wh_rtype;
		this.TypeSelectChange("height_type", list, true, revoke_bind);
	},
	HandleHTypeSELECT_CHANGE : function(event) {
		let list = ALittleIDE.g_IDEEnum.wh_rtype;
		this.TypeSelectChange("height_type", list, true);
	},
	SetXValue : function(x_value, revoke_bind) {
		if (x_value === undefined) {
			return;
		}
		this._x_value.text = x_value;
		this._base.x = undefined;
		this.ValueNumInputChange("x_value", true, revoke_bind);
	},
	HandleXValueFOCUSOUT : function(event) {
		this._base.x = undefined;
		this.ValueNumInputChange("x_value", true);
	},
	HandleXValueMoveIn : function(event) {
		ALittle.System_SetHDragCursor();
	},
	HandleXValueMoveOut : function(event) {
		ALittle.System_SetNormalCursor();
	},
	HandleXValueTabKey : function(event) {
		this._y_value.focus = true;
		this._y_value.SelectAll();
	},
	HandleXValueDrag : function(event) {
		let value = ALittle.Math_ToDouble(this._x_value.text);
		if (value === undefined) {
			value = 0;
		}
		value = value + event.delta_x;
		this._x_value.text = value;
		this.ValueNumInputChange("x_value", true);
	},
	SetYValue : function(y_value, revoke_bind) {
		if (y_value === undefined) {
			return;
		}
		this._y_value.text = y_value;
		this._base.y = undefined;
		this.ValueNumInputChange("y_value", true, revoke_bind);
	},
	HandleYValueFOCUSOUT : function(event) {
		this._base.y = undefined;
		this.ValueNumInputChange("y_value", true);
	},
	HandleYValueMoveIn : function(event) {
		ALittle.System_SetHDragCursor();
	},
	HandleYValueMoveOut : function(event) {
		ALittle.System_SetNormalCursor();
	},
	HandleYValueTabKey : function(event) {
		this._width_value.focus = true;
		this._width_value.SelectAll();
	},
	HandleYValueDrag : function(event) {
		let value = ALittle.Math_ToDouble(this._y_value.text);
		if (value === undefined) {
			value = 0;
		}
		value = value + event.delta_x;
		this._y_value.text = value;
		this.ValueNumInputChange("y_value", true);
	},
	SetWValue : function(width_value, revoke_bind) {
		if (width_value === undefined) {
			return;
		}
		this._width_value.text = width_value;
		this._base.width = undefined;
		this.ValueNumInputChange("width_value", true, revoke_bind);
	},
	HandleWValueFOCUSOUT : function(event) {
		this._base.width = undefined;
		this.ValueNumInputChange("width_value", true);
	},
	HandleWValueMoveIn : function(event) {
		ALittle.System_SetHDragCursor();
	},
	HandleWValueMoveOut : function(event) {
		ALittle.System_SetNormalCursor();
	},
	HandleWValueTabKey : function(event) {
		this._height_value.focus = true;
		this._height_value.SelectAll();
	},
	HandleWValueDrag : function(event) {
		let value = ALittle.Math_ToDouble(this._width_value.text);
		if (value === undefined) {
			value = 0;
		}
		value = value + event.delta_x;
		this._width_value.text = value;
		this.ValueNumInputChange("width_value", true);
	},
	SetHValue : function(height_value, revoke_bind) {
		if (height_value === undefined) {
			return;
		}
		this._height_value.text = height_value;
		this._base.height = undefined;
		this.ValueNumInputChange("height_value", true, revoke_bind);
	},
	HandleHValueFOCUSOUT : function(event) {
		this._base.height = undefined;
		this.ValueNumInputChange("height_value", true);
	},
	HandleHValueMoveIn : function(event) {
		ALittle.System_SetHDragCursor();
	},
	HandleHValueMoveOut : function(event) {
		ALittle.System_SetNormalCursor();
	},
	HandleHValueTabKey : function(event) {
		this._description.focus = true;
		this._description.SelectAll();
	},
	HandleHValueDrag : function(event) {
		let value = ALittle.Math_ToDouble(this._height_value.text);
		if (value === undefined) {
			value = 0;
		}
		value = value + event.delta_x;
		this._height_value.text = value;
		this.ValueNumInputChange("height_value", true);
	},
	SetAlpha : function(alpha, revoke_bind) {
		if (alpha === undefined) {
			return;
		}
		this._alpha.text = alpha;
		this.ColorValueInputChange("alpha", false, revoke_bind);
	},
	HandleAlphaFOCUSOUT : function(event) {
		this.ColorValueInputChange("alpha", false);
	},
	HandleAlphaValueMoveIn : function(event) {
		ALittle.System_SetHDragCursor();
	},
	HandleAlphaValueMoveOut : function(event) {
		ALittle.System_SetNormalCursor();
	},
	HandleAlphaValueTabKey : function(event) {
		this._x_value.focus = true;
		this._x_value.SelectAll();
	},
	HandleAlphaValueDrag : function(event) {
		let value = ALittle.Math_ToDouble(this._alpha.text);
		if (value === undefined) {
			value = 0;
		}
		value = value + event.delta_x;
		if (value < 0) {
			value = 0;
		} else if (value > 255) {
			value = 255;
		}
		this._alpha.text = value;
		this.ColorValueInputChange("alpha", true);
	},
	SetRed : function(red, revoke_bind) {
		if (red === undefined) {
			return;
		}
		this._red.text = red;
		this.ColorValueInputChange("red", false, revoke_bind);
	},
	HandleRedFOCUSOUT : function(event) {
		this.ColorValueInputChange("red", false);
	},
	HandleRedValueMoveIn : function(event) {
		ALittle.System_SetHDragCursor();
	},
	HandleRedValueMoveOut : function(event) {
		ALittle.System_SetNormalCursor();
	},
	HandleRedValueTabKey : function(event) {
		this._green.focus = true;
		this._green.SelectAll();
	},
	HandleRedValueDrag : function(event) {
		let value = ALittle.Math_ToDouble(this._red.text);
		if (value === undefined) {
			value = 0;
		}
		value = value + event.delta_x;
		if (value < 0) {
			value = 0;
		} else if (value > 255) {
			value = 255;
		}
		this._red.text = value;
		this.ColorValueInputChange("red", true);
	},
	SetGreen : function(green, revoke_bind) {
		if (green === undefined) {
			return;
		}
		this._green.text = green;
		this.ColorValueInputChange("green", false, revoke_bind);
	},
	HandleGreenFOCUSOUT : function(event) {
		this.ColorValueInputChange("green", false);
	},
	HandleGreenValueMoveIn : function(event) {
		ALittle.System_SetHDragCursor();
	},
	HandleGreenValueMoveOut : function(event) {
		ALittle.System_SetNormalCursor();
	},
	HandleGreenValueTabKey : function(event) {
		this._blue.focus = true;
		this._blue.SelectAll();
	},
	HandleGreenValueDrag : function(event) {
		let value = ALittle.Math_ToDouble(this._green.text);
		if (value === undefined) {
			value = 0;
		}
		value = value + event.delta_x;
		if (value < 0) {
			value = 0;
		} else if (value > 255) {
			value = 255;
		}
		this._green.text = value;
		this.ColorValueInputChange("green", true);
	},
	SetBlue : function(blue, revoke_bind) {
		if (blue === undefined) {
			return;
		}
		this._blue.text = blue;
		this.ColorValueInputChange("blue", false, revoke_bind);
	},
	HandleBlueFOCUSOUT : function(event) {
		this.ColorValueInputChange("blue", false);
	},
	HandleBlueValueMoveIn : function(event) {
		ALittle.System_SetHDragCursor();
	},
	HandleBlueValueMoveOut : function(event) {
		ALittle.System_SetNormalCursor();
	},
	HandleBlueValueTabKey : function(event) {
		this._alpha.focus = true;
		this._alpha.SelectAll();
	},
	HandleBlueValueDrag : function(event) {
		let value = ALittle.Math_ToDouble(this._blue.text);
		if (value === undefined) {
			value = 0;
		}
		value = value + event.delta_x;
		if (value < 0) {
			value = 0;
		} else if (value > 255) {
			value = 255;
		}
		this._blue.text = value;
		this.ColorValueInputChange("blue", true);
	},
	HandleScaleXFOCUSOUT : function(event) {
		this.ValueNumInputChange("scale_x", true);
	},
	SetScaleX : function(scale_x, revoke_bind) {
		if (scale_x === undefined) {
			return;
		}
		this._scale_x.text = scale_x;
		this.ValueNumInputChange("scale_x", true, revoke_bind);
	},
	HandleScaleYFOCUSOUT : function(event) {
		this.ValueNumInputChange("scale_y", true);
	},
	SetScaleY : function(scale_y, revoke_bind) {
		if (scale_y === undefined) {
			return;
		}
		this._scale_y.text = scale_y;
		this.ValueNumInputChange("scale_y", true, revoke_bind);
	},
	HandleCenterXFOCUSOUT : function(event) {
		this.ValueNumInputChange("center_x", true);
	},
	SetCenterX : function(center_x, revoke_bind) {
		if (center_x === undefined) {
			return;
		}
		this._center_x.text = center_x;
		this.ValueNumInputChange("center_x", true, revoke_bind);
	},
	HandleCenterYFOCUSOUT : function(event) {
		this.ValueNumInputChange("center_y", true);
	},
	SetCenterY : function(center_y, revoke_bind) {
		if (center_y === undefined) {
			return;
		}
		this._center_y.text = center_y;
		this.ValueNumInputChange("center_y", true, revoke_bind);
	},
	HandleAutoCenter : function(event) {
		this._center_x.text = this._object.width / 2;
		this.ValueNumInputChange("center_x", true);
		this._center_y.text = this._object.height / 2;
		this.ValueNumInputChange("center_y", true);
	},
	HandleAngleMoveIn : function(event) {
		ALittle.System_SetHDragCursor();
	},
	HandleAngleMoveOut : function(event) {
		ALittle.System_SetNormalCursor();
	},
	HandleAngleDrag : function(event) {
		let value = ALittle.Math_ToDouble(this._angle.text);
		if (value === undefined) {
			value = 0;
		}
		value = value + event.delta_x;
		this._angle.text = value;
		this.ValueNumInputChange("angle", true);
	},
	HandleAngleFOCUSOUT : function(event) {
		this.ValueNumInputChange("angle", true);
	},
	SetAngle : function(angle, revoke_bind) {
		if (angle === undefined) {
			return;
		}
		this._angle.text = angle;
		this.ValueNumInputChange("angle", true, revoke_bind);
	},
	SetHandCursor : function(hand_cursor, revoke_bind) {
		if (hand_cursor === undefined) {
			return;
		}
		this._hand_cursor.selected = hand_cursor;
		this.CheckBoolSelectChange("hand_cursor", false, revoke_bind);
	},
	HandleHandCursorChanged : function(event) {
		this.CheckBoolSelectChange("hand_cursor", false);
	},
	SetVisible : function(visible, revoke_bind) {
		if (visible === undefined) {
			return;
		}
		this._visible.selected = visible;
		this.CheckBoolSelectChange("visible", false, revoke_bind);
	},
	HandleVisibleChanged : function(event) {
		this.CheckBoolSelectChange("visible", false);
	},
	SetDisabled : function(disabled, revoke_bind) {
		if (disabled === undefined) {
			return;
		}
		this._disabled.selected = disabled;
		this.CheckBoolSelectChange("disabled", false, revoke_bind);
	},
	HandleDisabledChanged : function(event) {
		this.CheckBoolSelectChange("disabled", false);
	},
	SetDescription : function(description, revoke_bind) {
		if (description === undefined) {
			return;
		}
		this._description.text = description;
		this.DefaultNilStringInputChange("description", false, revoke_bind);
		this._tree_logic.UpdateDesc();
	},
	HandleDescriptionFOCUSOUT : function(event) {
		this.DefaultNilStringInputChange("description", false);
		this._tree_logic.UpdateDesc();
	},
	HandleDescriptionTabKey : function(event) {
		this.___target_class.focus = true;
		this.___target_class.SelectAll();
	},
	SetLink : function(link, revoke_bind) {
		if (link === undefined) {
			return;
		}
		this.___link.text = link;
		this.DefaultNilStringInputChange("__link", false, revoke_bind);
		this._tree_logic.UpdateDesc();
	},
	HandleLinkFOCUSOUT : function(event) {
		this.DefaultNilStringInputChange("__link", false);
		this._tree_logic.UpdateDesc();
	},
	HandleLinkTabKey : function(event) {
		this._id.focus = true;
		this._id.SelectAll();
	},
	GetParentTargetClass : function() {
		let tree = this._tree_logic;
		do {
			let parent = tree.parent;
			if (parent === undefined) {
				break;
			}
			let target_class = parent.user_info.base.__target_class;
			if (target_class === undefined) {
				target_class = parent.user_info.default.__target_class;
			}
			if (target_class !== undefined) {
				let text = ALittle.String_Join(target_class, ".");
				if (text !== "") {
					return text;
				}
			}
			if (parent.is_root) {
				break;
			}
			tree = parent;
		} while (true);
		return undefined;
	},
	HandleLinkEditClick : async function(event) {
		if (ALittleIDE.g_IDEProject.project.code === undefined) {
			return;
		}
		let pre_input = this.GetParentTargetClass();
		if (pre_input === undefined) {
			return;
		}
		let info = await ALittleIDE.g_IDEProject.project.code.FindGoto(pre_input + "." + this.___link.text);
		if (info !== undefined) {
			ALittleIDE.g_IDECenter.center.code_list.OpenByFullPath(info.file_path, info.line_start, info.char_start, info.line_end, info.char_end);
		}
	},
	HandleLinkChanged : async function(event) {
		if (ALittleIDE.g_IDEProject.project.code === undefined) {
			return;
		}
		let pre_input = this.GetParentTargetClass();
		if (pre_input === undefined) {
			return;
		}
		g_AUICodeFilterScreen.ShowComplete(ALittleIDE.g_IDEProject.project.code, pre_input, this.___link);
	},
	SetEvent : function(event, revoke_bind) {
		if (event === undefined) {
			return;
		}
		let content = [];
		let count = 0;
		let ___OBJECT_1 = event;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let event_info = ___OBJECT_1[index - 1];
			if (event_info === undefined) break;
			let data_type = event_info.type + ":";
			let event_string = data_type + event_info.func;
			++ count;
			content[count - 1] = event_string;
		}
		if (count === 0) {
			return;
		}
		this.___event.text = ALittle.String_Join(content, "\n");
		this.TableDataSet("__event", false, revoke_bind);
	},
	HandleEventFOCUSOUT : function(event) {
		let [x, y] = event.target.LocalToGlobal();
		ALittleIDE.g_IDEAttrEventDialog.ShowDialog(this, "__event", false, x + event.target.width + 10, y);
	},
	SetTargetClass : function(target_class, revoke_bind) {
		if (target_class === undefined) {
			return;
		}
		this.___target_class.text = ALittle.String_Join(target_class, ".");
		this.TableDataSetForTargetClass("__target_class", false, revoke_bind);
	},
	HandleTargetClassFOCUSOUT : function(event) {
		this.TableDataSetForTargetClass("__target_class", false);
	},
	HandleTargetClassTabKey : function(event) {
		this.___link.focus = true;
		this.___link.SelectAll();
	},
	HandleTargetClassEditClick : async function(event) {
		if (ALittleIDE.g_IDEProject.project.code === undefined) {
			return;
		}
		let info = await ALittleIDE.g_IDEProject.project.code.FindGoto(this.___target_class.text);
		if (info !== undefined) {
			ALittleIDE.g_IDECenter.center.code_list.OpenByFullPath(info.file_path, info.line_start, info.char_start, info.line_end, info.char_end);
		}
	},
	HandleTargetClassChanged : async function(event) {
		if (ALittleIDE.g_IDEProject.project.code === undefined) {
			return;
		}
		g_AUICodeFilterScreen.ShowComplete(ALittleIDE.g_IDEProject.project.code, "", this.___target_class);
	},
	TypeSelectChange : function(text, list, need_reset, revoke_bind) {
		let old_base = this._base[text];
		let old_object = this._object[text];
		let display_object = this["_" + text];
		if (revoke_bind === undefined && this._object[text] === list[display_object.text]) {
			return;
		}
		this._object[text] = list[display_object.text];
		this._base[text] = list[display_object.text];
		if (this._base[text] === this._default[text]) {
			delete this._base[text];
		}
		this._tab_child.UpdateHandleQuadLayout(this._tree_logic);
		this._tab_child.save = false;
		let new_base = this._base[text];
		let new_object = this._object[text];
		let old_text = undefined;
		if (display_object !== undefined) {
			old_text = display_object.text;
		}
		let revoke = ALittle.NewObject(ALittleIDE.IDENatureChangeRevoke, this._tree_logic, text, old_base, new_base, old_object, new_object, old_text, need_reset);
		if (revoke_bind !== undefined) {
			revoke_bind.PushRevoke(revoke);
		} else {
			this._tab_child.revoke_list.PushRevoke(revoke);
		}
	},
	ValueNumInputChange : function(text, need_reset, revoke_bind) {
		let old_base = this._base[text];
		let old_object = this._object[text];
		let display_object = this["_" + text];
		let value = ALittle.Math_ToDouble(display_object.text);
		if (value === undefined) {
			display_object.text = "0";
			if (revoke_bind === undefined && this._object[text] === 0) {
				return;
			}
			this._object[text] = 0;
			this._base[text] = 0;
		} else {
			if (revoke_bind === undefined && this._object[text] === value) {
				return;
			}
			this._object[text] = value;
			this._base[text] = value;
		}
		if (this._default[text] !== undefined && this._base[text] === this._default[text]) {
			delete this._base[text];
		}
		this._tab_child.UpdateHandleQuadLayout(this._tree_logic);
		this._tab_child.save = false;
		let new_base = this._base[text];
		let new_object = this._object[text];
		let old_text = undefined;
		if (display_object !== undefined) {
			old_text = display_object.text;
		}
		let revoke = ALittle.NewObject(ALittleIDE.IDENatureChangeRevoke, this._tree_logic, text, old_base, new_base, old_object, new_object, old_text, need_reset);
		if (revoke_bind !== undefined) {
			revoke_bind.PushRevoke(revoke);
		} else {
			this._tab_child.revoke_list.PushRevoke(revoke);
		}
	},
	ValueNumZInputChange : function(text, need_reset, revoke_bind) {
		let old_base = this._base[text];
		let old_object = this._object[text];
		let display_object = this["_" + text];
		let value = ALittle.Math_ToDouble(display_object.text);
		if (value === undefined || value < 0) {
			display_object.text = "0";
			if (revoke_bind === undefined && this._object[text] === 0) {
				return;
			}
			this._object[text] = 0;
			this._base[text] = 0;
		} else {
			if (revoke_bind === undefined && this._object[text] === value) {
				return;
			}
			this._object[text] = value;
			this._base[text] = value;
		}
		if (this._default[text] !== undefined && this._base[text] === this._default[text]) {
			delete this._base[text];
		}
		this._tab_child.UpdateHandleQuadLayout(this._tree_logic);
		this._tab_child.save = false;
		let new_base = this._base[text];
		let new_object = this._object[text];
		let old_text = undefined;
		if (display_object !== undefined) {
			old_text = display_object.text;
		}
		let revoke = ALittle.NewObject(ALittleIDE.IDENatureChangeRevoke, this._tree_logic, text, old_base, new_base, old_object, new_object, old_text, need_reset);
		if (revoke_bind !== undefined) {
			revoke_bind.PushRevoke(revoke);
		} else {
			this._tab_child.revoke_list.PushRevoke(revoke);
		}
	},
	ColorValueInputChange : function(text, need_reset, revoke_bind) {
		let old_base = this._base[text];
		let old_object = this._object[text];
		let display_object = this["_" + text];
		let value = ALittle.Math_ToDouble(display_object.text);
		if (value === undefined || value < 0) {
			display_object.text = "0";
			if (revoke_bind === undefined && this._object[text] === 0) {
				return;
			}
			this._object[text] = 0;
			this._base[text] = 0;
		} else if (value > 255) {
			display_object.text = "255";
			if (revoke_bind === undefined && this._object[text] === 1) {
				return;
			}
			this._object[text] = 1;
			this._base[text] = 1;
		} else {
			if (revoke_bind === undefined && ALittle.Math_Ceil(this._object[text] * 255) === value) {
				return;
			}
			value = value / 255;
			this._object[text] = value;
			this._base[text] = value;
		}
		if (this._default[text] !== undefined && this._base[text] === this._default[text]) {
			delete this._base[text];
		}
		this._tab_child.UpdateHandleQuadLayout(this._tree_logic);
		this._tab_child.save = false;
		let new_base = this._base[text];
		let new_object = this._object[text];
		let old_text = undefined;
		if (display_object !== undefined) {
			old_text = display_object.text;
		}
		let revoke = ALittle.NewObject(ALittleIDE.IDENatureChangeRevoke, this._tree_logic, text, old_base, new_base, old_object, new_object, old_text, need_reset);
		if (revoke_bind !== undefined) {
			revoke_bind.PushRevoke(revoke);
		} else {
			this._tab_child.revoke_list.PushRevoke(revoke);
		}
	},
	Z2OValueInputChange : function(text, need_reset, revoke_bind) {
		let old_base = this._base[text];
		let old_object = this._object[text];
		let display_object = this["_" + text];
		let value = ALittle.Math_ToDouble(display_object.text);
		if (value === undefined || value < 0) {
			display_object.text = "0";
			if (revoke_bind === undefined && this._object[text] === 0) {
				return;
			}
			this._object[text] = 0;
			this._base[text] = 0;
		} else if (value > 1) {
			display_object.text = "1";
			if (revoke_bind === undefined && this._object[text] === 1) {
				return;
			}
			this._object[text] = 1;
			this._base[text] = 1;
		} else {
			if (revoke_bind === undefined && this._object[text] === value) {
				return;
			}
			this._object[text] = value;
			this._base[text] = value;
		}
		if (this._base[text] === this._default[text]) {
			delete this._base[text];
		}
		this._tab_child.UpdateHandleQuadLayout(this._tree_logic);
		this._tab_child.save = false;
		let new_base = this._base[text];
		let new_object = this._object[text];
		let old_text = undefined;
		if (display_object !== undefined) {
			old_text = display_object.text;
		}
		let revoke = ALittle.NewObject(ALittleIDE.IDENatureChangeRevoke, this._tree_logic, text, old_base, new_base, old_object, new_object, old_text, need_reset);
		if (revoke_bind !== undefined) {
			revoke_bind.PushRevoke(revoke);
		} else {
			this._tab_child.revoke_list.PushRevoke(revoke);
		}
	},
	DefaultNilStringInputChange : function(text, need_reset, revoke_bind) {
		let old_base = this._base[text];
		let old_object = this._object[text];
		let display_object = this["_" + text];
		if (display_object.text === "") {
			if (revoke_bind === undefined && this._base[text] === display_object.text) {
				return;
			}
			delete this._base[text];
			if (this._default[text] === undefined) {
				delete this._object[text];
			} else {
				this._object[text] = this._default[text];
				display_object.text = this._default[text];
			}
		} else {
			if (revoke_bind === undefined && this._base[text] === display_object.text) {
				return;
			}
			this._base[text] = display_object.text;
			this._object[text] = display_object.text;
			if (this._default[text] !== undefined && this._base[text] === this._default[text]) {
				delete this._base[text];
			}
		}
		this._tab_child.UpdateHandleQuadLayout(this._tree_logic);
		this._tab_child.save = false;
		let new_base = this._base[text];
		let new_object = this._object[text];
		let old_text = undefined;
		if (display_object !== undefined) {
			old_text = display_object.text;
		}
		let revoke = ALittle.NewObject(ALittleIDE.IDENatureChangeRevoke, this._tree_logic, text, old_base, new_base, old_object, new_object, old_text, need_reset);
		if (revoke_bind !== undefined) {
			revoke_bind.PushRevoke(revoke);
		} else {
			this._tab_child.revoke_list.PushRevoke(revoke);
		}
	},
	DefaultNoStringInputChange : function(text, need_reset, revoke_bind) {
		let old_base = this._base[text];
		let old_object = this._object[text];
		let display_object = this["_" + text];
		if (revoke_bind === undefined && this._object[text] === display_object.text) {
			return;
		}
		this._base[text] = display_object.text;
		this._object[text] = display_object.text;
		if (this._default[text] !== undefined && this._base[text] === this._default[text]) {
			delete this._base[text];
		}
		this._tab_child.UpdateHandleQuadLayout(this._tree_logic);
		this._tab_child.save = false;
		let new_base = this._base[text];
		let new_object = this._object[text];
		let old_text = undefined;
		if (display_object !== undefined) {
			old_text = display_object.text;
		}
		let revoke = ALittle.NewObject(ALittleIDE.IDENatureChangeRevoke, this._tree_logic, text, old_base, new_base, old_object, new_object, old_text, need_reset);
		if (revoke_bind !== undefined) {
			revoke_bind.PushRevoke(revoke);
		} else {
			this._tab_child.revoke_list.PushRevoke(revoke);
		}
	},
	SpecialFontPathInputChange : function(text, need_reset, revoke_bind) {
		let old_base = this._base[text];
		let old_object = this._object[text];
		let display_object = this["_" + text];
		if (display_object.text === "") {
			if (revoke_bind === undefined && this._object[text] === undefined) {
				return;
			}
			if (this._default[text] !== undefined) {
				display_object.text = this._default[text];
				delete this._base[text];
				this._object[text] = this._default[text];
			} else {
				display_object.text = this._base[text];
				this._object[text] = this._base[text];
			}
		} else {
			if (revoke_bind === undefined && this._object[text] === display_object.text) {
				return;
			}
			this._base[text] = display_object.text;
			this._object[text] = display_object.text;
			if (this._default[text] !== undefined && this._base[text] === this._default[text]) {
				delete this._base[text];
			}
		}
		this._tab_child.UpdateHandleQuadLayout(this._tree_logic);
		this._tab_child.save = false;
		let new_base = this._base[text];
		let new_object = this._object[text];
		let old_text = undefined;
		if (display_object !== undefined) {
			old_text = display_object.text;
		}
		let revoke = ALittle.NewObject(ALittleIDE.IDENatureChangeRevoke, this._tree_logic, text, old_base, new_base, old_object, new_object, old_text, need_reset);
		if (revoke_bind !== undefined) {
			revoke_bind.PushRevoke(revoke);
		} else {
			this._tab_child.revoke_list.PushRevoke(revoke);
		}
	},
	BoolSelectChange : function(text, need_reset, list, revoke_bind) {
		let old_base = this._base[text];
		let old_object = this._object[text];
		let display_object = this["_" + text];
		if (display_object.text === list.get(true)) {
			if (revoke_bind === undefined && this._object[text] === true) {
				return;
			}
			this._object[text] = true;
			this._base[text] = true;
		} else if (display_object.text === list.get(false)) {
			if (revoke_bind === undefined && this._object[text] === false) {
				return;
			}
			this._object[text] = false;
			this._base[text] = false;
		} else {
			ALittle.Log("bool failed");
		}
		if (this._base[text] === this._default[text]) {
			delete this._base[text];
		}
		this._tab_child.UpdateHandleQuadLayout(this._tree_logic);
		this._tab_child.save = false;
		let new_base = this._base[text];
		let new_object = this._object[text];
		let old_text = undefined;
		if (display_object !== undefined) {
			old_text = display_object.text;
		}
		let revoke = ALittle.NewObject(ALittleIDE.IDENatureChangeRevoke, this._tree_logic, text, old_base, new_base, old_object, new_object, old_text, need_reset);
		if (revoke_bind !== undefined) {
			revoke_bind.PushRevoke(revoke);
		} else {
			this._tab_child.revoke_list.PushRevoke(revoke);
		}
	},
	CheckBoolSelectChange : function(text, need_reset, revoke_bind) {
		let old_base = this._base[text];
		let old_object = this._object[text];
		let display_object = this["_" + text];
		if (display_object.selected) {
			if (revoke_bind === undefined && this._object[text] === true) {
				return;
			}
			this._object[text] = true;
			this._base[text] = true;
		} else {
			if (revoke_bind === undefined && this._object[text] === false) {
				return;
			}
			this._object[text] = false;
			this._base[text] = false;
		}
		if (this._base[text] === this._default[text]) {
			delete this._base[text];
		}
		this._tab_child.UpdateHandleQuadLayout(this._tree_logic);
		this._tab_child.save = false;
		let new_base = this._base[text];
		let new_object = this._object[text];
		let old_text = undefined;
		if (display_object !== undefined) {
			old_text = display_object.text;
		}
		let revoke = ALittle.NewObject(ALittleIDE.IDENatureChangeRevoke, this._tree_logic, text, old_base, new_base, old_object, new_object, old_text, need_reset);
		if (revoke_bind !== undefined) {
			revoke_bind.PushRevoke(revoke);
		} else {
			this._tab_child.revoke_list.PushRevoke(revoke);
		}
	},
	RemoverToNilShowSetForImage : function(text, image_path, grid9, need_reset, revoke_bind) {
		if (image_path === "") {
			this.RemoverToNilShowSet(text, "", need_reset, revoke_bind);
		} else {
			if (grid9) {
				let ui_manager = ALittleIDE.g_IDEProject.GetUIManager(this._tree_logic.user_info.module);
				if (ui_manager === undefined) {
					g_AUITool.ShowNotice("错误", "模块不存在:" + this._tree_logic.user_info.module);
					return;
				}
				let display_info = ALittleIDE.IDEUIUtility_GenerateGrid9ImageInfo(ui_manager.texture_path + "/", image_path);
				if (display_info === undefined) {
					g_AUITool.ShowNotice("错误", "图片不存在:" + image_path);
					return;
				}
				this.RemoverToNilShowSet(text, ALittle.String_JsonEncode(display_info), need_reset, revoke_bind);
			} else {
				let display_info = {};
				display_info.__class = "Image";
				display_info.texture_name = image_path;
				this.RemoverToNilShowSet(text, ALittle.String_JsonEncode(display_info), need_reset, revoke_bind);
			}
		}
	},
	RemoverToNilShowSetForExtends : function(text, extends_name, need_reset, revoke_bind) {
		if (extends_name !== "") {
			let ui_manager = ALittleIDE.g_IDEProject.GetUIManager(this._tree_logic.user_info.module);
			if (ui_manager.control_map[extends_name] === undefined) {
				g_AUITool.ShowNotice("错误", "要继承的控件不存在:" + extends_name);
				return;
			}
			let display_info = {};
			display_info.__module = this._tree_logic.user_info.module;
			display_info.__extends = extends_name;
			this.RemoverToNilShowSet(text, ALittle.String_JsonEncode(display_info), need_reset, revoke_bind);
		} else {
			this.RemoverToNilShowSet(text, "", need_reset, revoke_bind);
		}
	},
	RemoverToNilShowSet : function(text, json_content, need_reset, revoke_bind) {
		let old_base = this._base[text];
		let old_object = this._object[text];
		if (json_content === "") {
			delete this._base[text];
			if (this._default[text] !== undefined && this._default[text].__class !== undefined) {
				let content = this._default[text];
				let [error1, content1] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
				if (error1 === undefined) {
					let [error2, content2] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, content1); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
					let name = "mnbvcxzasdfghjklpoiuytrewq20160121";
					let ui_manager = ALittleIDE.g_IDEProject.GetUIManager(this._tree_logic.user_info.module);
					ui_manager.control.RegisterInfo(name, content2);
					let temp = ui_manager.control.CreateControl(name);
					this._object[text] = temp;
					ui_manager.control.UnRegisterInfo(name);
				}
			} else {
				delete this._object[text];
				this["_" + text].text = "";
			}
		} else {
			let content = json_content;
			let [error1, content1] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
			if (error1 === undefined) {
				let include = content1.__include;
				if (include === undefined) {
					include = content1.__extends;
				}
				if (include !== undefined) {
					let ui_manager = ALittleIDE.g_IDEProject.GetUIManager(content1.__module);
					if (ui_manager.control_map[include] === undefined) {
						g_AUITool.ShowNotice("错误", "指定__include或__extends不存在");
						return;
					}
				}
				this._base[text] = content1;
				let [error2, content2] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
				let name = "mnbvcxzasdfghjklpoiuytrewq20160121";
				let ui_manager = ALittleIDE.g_IDEProject.GetUIManager(this._tree_logic.user_info.module);
				ui_manager.control.RegisterInfo(name, content2);
				let temp = ui_manager.control.CreateControl(name);
				this._object[text] = temp;
				ui_manager.control.UnRegisterInfo(name);
			} else {
				g_AUITool.ShowNotice("错误", "输入show设置错误");
				return;
			}
		}
		this._tab_child.UpdateHandleQuadLayout(this._tree_logic);
		this._tab_child.save = false;
		let new_base = this._base[text];
		let new_object = this._object[text];
		let old_text = undefined;
		let display_object = this["_" + text];
		if (display_object !== undefined) {
			old_text = display_object.text;
		}
		let revoke = ALittle.NewObject(ALittleIDE.IDENatureChangeRevoke, this._tree_logic, text, old_base, new_base, old_object, new_object, old_text, need_reset);
		if (revoke_bind !== undefined) {
			revoke_bind.PushRevoke(revoke);
		} else {
			this._tab_child.revoke_list.PushRevoke(revoke);
		}
	},
	RemoverToNilNoNilShowSet : function(text, need_reset, revoke_bind) {
		let old_base = this._base[text];
		let old_object = this._object[text];
		let display_object = this["_" + text];
		if (display_object.text === "") {
			delete this._base[text];
			if (this._default[text] !== undefined && (this._default[text].__class !== undefined || this._default[text].__include !== undefined || this._default[text].__extends !== undefined)) {
				let content = this._default[text];
				let [error, content1] = (function() { try { let ___VALUE = ALittle.String_JsonEncode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
				if (error !== undefined) {
					display_object.text = content1;
					let [error2, content2] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, content1); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
					let name = "mnbvcxzasdfghjklpoiuytrewq20160121";
					let ui_manager = ALittleIDE.g_IDEProject.GetUIManager(this._tree_logic.user_info.module);
					ui_manager.control.RegisterInfo(name, content2);
					let temp = ui_manager.control.CreateControl(name);
					this._object[text] = temp;
					ui_manager.control.UnRegisterInfo(name);
				}
			} else {
				delete this._object[text];
			}
		} else {
			let content = display_object.text;
			let [error1, content1] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
			if (error1 === undefined) {
				let include = content1.__include;
				if (include === undefined) {
					include = content1.__extends;
				}
				if (include !== undefined) {
					let ui_manager = ALittleIDE.g_IDEProject.GetUIManager(content1.__module);
					if (ui_manager.control_map[include] === undefined) {
						g_AUITool.ShowNotice("错误", "指定__include或__extends不存在");
						display_object.text = "";
						return;
					}
				}
				this._base[text] = content1;
				let [error2, content2] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
				let name = "mnbvcxzasdfghjklpoiuytrewq20160121";
				let ui_manager = ALittleIDE.g_IDEProject.GetUIManager(this._tree_logic.user_info.module);
				ui_manager.control.RegisterInfo(name, content2);
				let temp = ui_manager.control.CreateControl(name);
				this._object[text] = temp;
				ui_manager.control.UnRegisterInfo(name);
			} else {
				g_AUITool.ShowNotice("错误", "输入show设置错误");
				display_object.text = "";
				return;
			}
		}
		this._tab_child.UpdateHandleQuadLayout(this._tree_logic);
		this._tab_child.save = false;
		let new_base = this._base[text];
		let new_object = this._object[text];
		let old_text = undefined;
		if (display_object !== undefined) {
			old_text = display_object.text;
		}
		let revoke = ALittle.NewObject(ALittleIDE.IDENatureChangeRevoke, this._tree_logic, text, old_base, new_base, old_object, new_object, old_text, need_reset);
		if (revoke_bind !== undefined) {
			revoke_bind.PushRevoke(revoke);
		} else {
			this._tab_child.revoke_list.PushRevoke(revoke);
		}
	},
	TableDataSet : function(text, need_reset, revoke_bind) {
		let old_base = this._base[text];
		let old_object = this._object[text];
		let display_object = this["_" + text];
		if (display_object.text === "") {
			delete this._base[text];
			if (this._default[text] !== undefined) {
				let content = this._default[text];
				let [error, content1] = (function() { try { let ___VALUE = ALittle.String_JsonEncode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
				if (error === undefined) {
					display_object.text = content1;
					this._object[text] = content;
				}
			} else {
				delete this._object[text];
			}
		} else {
			let [error, content] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, display_object.text); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
			if (error === undefined) {
				this._base[text] = content;
				this._object[text] = content;
			} else {
				g_AUITool.ShowNotice("输入错误", "输入数据错误");
				display_object.text = "";
				return;
			}
		}
		this._tab_child.UpdateHandleQuadLayout(this._tree_logic);
		this._tab_child.save = false;
		let new_base = this._base[text];
		let new_object = this._object[text];
		let old_text = undefined;
		if (display_object !== undefined) {
			old_text = display_object.text;
		}
		let revoke = ALittle.NewObject(ALittleIDE.IDENatureChangeRevoke, this._tree_logic, text, old_base, new_base, old_object, new_object, old_text, need_reset);
		if (revoke_bind !== undefined) {
			revoke_bind.PushRevoke(revoke);
		} else {
			this._tab_child.revoke_list.PushRevoke(revoke);
		}
	},
	TableDataSetForTargetClass : function(text, need_reset, revoke_bind) {
		let old_base = this._base[text];
		let old_object = this._object[text];
		let default_value = undefined;
		if (this._default[text] !== undefined) {
			default_value = ALittle.String_Join(this._default[text], ".");
		}
		let display_object = this["_" + text];
		if (display_object.text === "" || display_object.text === default_value) {
			if (revoke_bind === undefined && this._base[text] === undefined && this._default[text] === undefined) {
				return;
			}
			delete this._base[text];
			if (this._default[text] !== undefined) {
				this._object[text] = this._default[text];
				display_object.text = default_value;
			} else {
				delete this._object[text];
			}
		} else {
			let old_content = this._base[text];
			if (old_content === undefined) {
				old_content = this._default[text];
			}
			if (revoke_bind === undefined && old_content !== undefined && ALittle.String_Join(old_content, ".") === display_object.text) {
				return;
			}
			let content = ALittle.String_Split(display_object.text, ".");
			this._base[text] = content;
			this._object[text] = content;
		}
		this._tab_child.UpdateHandleQuadLayout(this._tree_logic);
		this._tab_child.save = false;
		let new_base = this._base[text];
		let new_object = this._object[text];
		let old_text = undefined;
		if (display_object !== undefined) {
			old_text = display_object.text;
		}
		let revoke = ALittle.NewObject(ALittleIDE.IDENatureChangeRevoke, this._tree_logic, text, old_base, new_base, old_object, new_object, old_text, need_reset);
		if (revoke_bind !== undefined) {
			revoke_bind.PushRevoke(revoke);
		} else {
			this._tab_child.revoke_list.PushRevoke(revoke);
		}
	},
	LoadShowTypeDataForExtends : function(text) {
		let display_object = this["_" + text];
		let content = this._base[text];
		if (content === undefined) {
			content = this._default[text];
		}
		if (content !== undefined) {
			let include = content.__extends;
			if (include === undefined) {
				include = content.__include;
			}
			if (include !== undefined) {
				display_object.text = include;
			} else {
				display_object.text = "";
			}
		} else {
			display_object.text = "";
		}
	},
	LoadShowTypeDataForImage : function(text) {
		let display_object = this["_" + text];
		let display_object_grid9 = this["_" + text + "_grid9"];
		let content = this._base[text];
		if (content === undefined) {
			content = this._default[text];
		}
		if (content !== undefined) {
			if (content.__class === "Image") {
				if (content.texture_name !== undefined) {
					display_object.text = content.texture_name;
				} else {
					display_object.text = "";
				}
				display_object_grid9.selected = false;
			} else if (content.__class === "Grid9Image") {
				if (content.texture_name !== undefined) {
					display_object.text = content.texture_name;
				} else {
					display_object.text = "";
				}
				display_object_grid9.selected = true;
			} else {
				display_object.text = "";
				display_object_grid9.selected = false;
			}
		} else {
			display_object.text = "";
			display_object_grid9.selected = false;
		}
	},
	LoadShowTypeDataForTargetClass : function(text) {
		let display_object = this["_" + text];
		let content = this._base[text];
		if (content === undefined) {
			content = this._default[text];
		}
		if (content !== undefined) {
			display_object.text = ALittle.String_Join(content, ".");
		} else {
			display_object.text = "";
		}
	},
	LoadShowTypeData : function(text) {
		let display_object = this["_" + text];
		let content = this._base[text];
		if (content === undefined) {
			content = this._default[text];
		}
		if (content !== undefined) {
			let [error, object] = (function() { try { let ___VALUE = ALittle.String_JsonEncode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
			if (error === undefined) {
				display_object.text = object;
			} else {
				ALittle.Log("encode failed:" + error);
			}
		} else {
			display_object.text = "";
		}
	},
	LoadShowTypeNoNilData : function(text) {
		let display_object = this["_" + text];
		if (this._default[text] !== undefined && (this._default[text].__class !== undefined || this._default[text].__include !== undefined || this._default[text].__extends !== undefined)) {
			let content = this._base[text];
			if (content === undefined) {
				content = this._default[text];
			}
			if (content !== undefined) {
				let [error, new_content] = (function() { try { let ___VALUE = ALittle.String_JsonEncode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
				if (error === undefined) {
					display_object.text = new_content;
				} else {
					ALittle.Log("encode failed:" + error);
				}
			} else {
				display_object.text = "";
			}
		} else {
			let content = this._base[text];
			if (content !== undefined) {
				let [error, new_content] = (function() { try { let ___VALUE = ALittle.String_JsonEncode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
				if (error === undefined) {
					display_object.text = new_content;
				} else {
					ALittle.Log("encode failed:" + error);
				}
			} else {
				display_object.text = "";
			}
		}
	},
	LoadValueData : function(text) {
		let display_object = this["_" + text];
		if (this._base[text] !== undefined) {
			display_object.text = this._base[text];
		} else {
			display_object.text = this._default[text];
		}
	},
	LoadEnumData : function(text, list) {
		let display_object = this["_" + text];
		if (this._base[text] !== undefined) {
			display_object.text = list[this._base[text]];
		} else {
			display_object.text = list[this._default[text]];
		}
	},
	LoadColorData : function(text) {
		let display_object = this["_" + text];
		let color = this._base[text];
		if (color === undefined) {
			color = this._default[text];
		}
		display_object.text = ALittle.Math_Floor(color * 255);
	},
	LoadBoolData : function(text, default_bool, list) {
		let display_object = this["_" + text];
		let temp = default_bool;
		if (this._base[text] !== undefined) {
			temp = this._base[text];
		} else {
			temp = this._default[text];
		}
		if (temp) {
			if (display_object !== undefined) {
				display_object.text = list.get(true);
			} else {
				ALittle.Warn(text);
			}
		} else {
			if (display_object !== undefined) {
				display_object.text = list.get(false);
			} else {
				ALittle.Warn(text);
			}
		}
	},
	LoadCheckBoolData : function(text, default_bool) {
		let display_object = this["_" + text];
		let temp = default_bool;
		if (this._base[text] !== undefined) {
			temp = this._base[text];
		} else {
			temp = this._default[text];
		}
		if (display_object !== undefined) {
			display_object.selected = temp;
		} else {
			ALittle.Warn(text);
		}
	},
	LoadTypeSelectData : function(text, list) {
		let content = this._base[text];
		if (content === undefined) {
			content = this._default[text];
		}
		this["_" + text].text = list.get(content);
	},
	LoadDefaultNilString : function(text) {
		let display_object = this["_" + text];
		let content = this._base[text];
		if (content === undefined) {
			content = this._default[text];
		}
		if (content !== undefined) {
			display_object.text = content;
		} else {
			display_object.text = "";
		}
	},
	ImagePathSelectCallback : function(text, callback, revoke_bind, path, need_reset) {
		let ui_manager = ALittleIDE.g_IDEProject.GetUIManager(this._tree_logic.user_info.module);
		if (ui_manager === undefined) {
			g_AUITool.ShowNotice("错误", "模块不存在:" + this._tree_logic.user_info.module);
			return;
		}
		let display_object = this["_" + text];
		display_object.text = path;
		let e = {};
		e.target = display_object;
		callback(this, e);
		if (need_reset) {
			let surface = carp.LoadCarpSurface(ui_manager.texture_path + "/" + path);
			if (surface === undefined) {
				return;
			}
			let w = carp.GetCarpSurfaceWidth(surface);
			let h = carp.GetCarpSurfaceHeight(surface);
			carp.FreeCarpSurface(surface);
			let new_revoke = false;
			if (revoke_bind === undefined) {
				new_revoke = true;
				revoke_bind = ALittle.NewObject(ALittle.RevokeBind);
			}
			this.SetWType(1, revoke_bind);
			this.SetHType(1, revoke_bind);
			this.SetWValue(w, revoke_bind);
			this.SetHValue(h, revoke_bind);
			if (new_revoke) {
				this._tab_child.revoke_list.PushRevoke(revoke_bind);
			}
		}
	},
	SetTextureName : function(texture_name, revoke_bind) {
	},
}, "ALittleIDE.DisplayObjectS");

}