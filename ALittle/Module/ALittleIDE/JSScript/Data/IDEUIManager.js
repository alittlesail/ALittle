{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-4982446, "ALittle.DisplayInfo", {
name : "ALittle.DisplayInfo", ns_name : "ALittle", rl_name : "DisplayInfo", hash_code : -4982446,
name_list : ["__target_class","__class_func","__base_attr","__show_attr","loop_map","__class","__include","__extends","__childs","__event","__link","__shows_included","__childs_included","__extends_included","description","text","font_path","font_size","red","green","blue","alpha","bold","italic","underline","deleteline","outline","x","y","x_type","x_value","y_type","y_value","width","height","width_type","width_value","height_type","height_value","scale_x","scale_y","center_x","center_y","angle","flip","hand_cursor","visible","disabled","left_size","right_size","top_size","bottom_size","texture_name","interval","play_loop_count","var_play","base_y","head_size","gap","up_size","down_size","cursor_red","cursor_green","cursor_blue","default_text_alpha","ims_padding","margin_left","margin_right","margin_top","margin_bottom","show_count","body_margin","screen_margin_left","screen_margin_right","screen_margin_top","screen_margin_bottom","start_degree","end_degree","line_spacing","max_line_count","font_red","font_green","font_blue","margin_halign","margin_valign","cursor_margin_up","cursor_margin_down","total_size","show_size","offset_rate","offset_step","grade","row_count","col_count","row_index","col_index","u1","v1","u2","v2","u3","v3","x1","y1","x2","y2","x3","y3","x_gap","y_gap","x_start_gap","y_start_gap","button_gap","button_start","button_margin","tab_index","view_margin","child_width_margin"],
type_list : ["List<string>","any","Map<string,any>","Map<string,ALittle.DisplayInfo>","Map<string,ALittle.LoopGroupInfo>","string","string","string","List<ALittle.DisplayInfo>","List<ALittle.EventInfo>","string","bool","bool","bool","string","string","string","int","double","double","double","double","bool","bool","bool","bool","bool","double","double","int","double","int","double","double","double","int","double","int","double","double","double","double","double","double","int","bool","bool","bool","double","double","double","double","string","int","int","bool","double","double","double","double","double","double","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","double","double","double","int","int","int","int","int","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(1332927881, "ALittleIDE.IDEControlInfo", {
name : "ALittleIDE.IDEControlInfo", ns_name : "ALittleIDE", rl_name : "IDEControlInfo", hash_code : 1332927881,
name_list : ["info","name","extends_this","extends_other"],
type_list : ["ALittle.DisplayInfo","string","Map<string,bool>","Map<string,bool>"],
option_map : {}
})
ALittle.RegStruct(1653869333, "ALittle.LoopGroupInfo", {
name : "ALittle.LoopGroupInfo", ns_name : "ALittle", rl_name : "LoopGroupInfo", hash_code : 1653869333,
name_list : ["childs"],
type_list : ["List<ALittle.LoopListInfo>"],
option_map : {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(-2110455927, "ALittle.EventInfo", {
name : "ALittle.EventInfo", ns_name : "ALittle", rl_name : "EventInfo", hash_code : -2110455927,
name_list : ["type","func"],
type_list : ["string","string"],
option_map : {}
})
ALittle.RegStruct(-1741432339, "ALittle.LoopListInfo", {
name : "ALittle.LoopListInfo", ns_name : "ALittle", rl_name : "LoopListInfo", hash_code : -1741432339,
name_list : ["link","attribute","init","childs"],
type_list : ["string","string","any","List<ALittle.LoopChildInfo>"],
option_map : {}
})
ALittle.RegStruct(-925381158, "ALittle.LoopChildInfo", {
name : "ALittle.LoopChildInfo", ns_name : "ALittle", rl_name : "LoopChildInfo", hash_code : -925381158,
name_list : ["clazz","target","total_time","delay_time"],
type_list : ["string","any","int","int"],
option_map : {}
})

ALittleIDE.IDEUIManager = JavaScript.Class(undefined, {
	Ctor : function(name, control) {
		this._control = control;
		this._control_map = {};
		this._base_path = ALittle.File_BaseFilePath() + "Module/" + name + "/UI";
		let file_map = ALittle.File_GetFileAttrByDir(this._base_path);
		let ___OBJECT_1 = file_map;
		for (let file_path in ___OBJECT_1) {
			let attr = ___OBJECT_1[file_path];
			if (attr === undefined) continue;
			let ext = ALittle.String_Upper(ALittle.File_GetFileExtByPath(file_path));
			if (ext === "JSON") {
				let content = ALittle.File_ReadTextFromFile(file_path);
				if (content !== undefined) {
					let [error, content_info_map] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
					if (error === undefined) {
						let ___OBJECT_2 = content_info_map;
						for (let control_name in ___OBJECT_2) {
							let control_info = ___OBJECT_2[control_name];
							if (control_info === undefined) continue;
							let all_info = {};
							all_info.info = control_info;
							all_info.name = control_name;
							all_info.extends_this = {};
							all_info.extends_other = {};
							if (this._control_map[control_name] !== undefined) {
								ALittle.Log("IDEProject:OpenProject control_name:" + control_name + " repeat in " + file_path);
							}
							this._control_map[control_name] = all_info;
						}
					} else {
						ALittle.Log("IDEProject:OpenProject json decode failed:", file_path, content_info_map);
					}
				} else {
					ALittle.Log("IDEProject:OpenProject failed:", file_path);
				}
			}
		}
		let ___OBJECT_3 = this._control_map;
		for (let control_name in ___OBJECT_3) {
			let all_info = ___OBJECT_3[control_name];
			if (all_info === undefined) continue;
			let map = ALittleIDE.IDEUIUtility_GetExtends(all_info.info);
			let ___OBJECT_4 = map;
			for (let other_name in ___OBJECT_4) {
				let v = ___OBJECT_4[other_name];
				if (v === undefined) continue;
				let other = this._control_map[other_name];
				if (other !== undefined) {
					other.extends_this[control_name] = true;
					all_info.extends_other[other_name] = true;
				} else {
					ALittle.Log("IDEProject:OpenProject calc extends failed:", other_name);
				}
			}
		}
	},
	get control_map() {
		return this._control_map;
	},
	CalcDeepExtends : function(name, map, lock_map) {
		if (map === undefined) {
			map = {};
		}
		if (lock_map === undefined) {
			lock_map = {};
		}
		let info = this._control_map[name];
		if (info === undefined) {
			return map;
		}
		map[name] = true;
		let ___OBJECT_5 = info.extends_other;
		for (let other_name in ___OBJECT_5) {
			let v = ___OBJECT_5[other_name];
			if (v === undefined) continue;
			if (lock_map[other_name] === undefined) {
				lock_map[other_name] = true;
				this.CalcDeepExtends(other_name, map, lock_map);
			}
			map[other_name] = true;
		}
		return map;
	},
	SaveControl : function(name, info) {
		let file_path = this._base_path + "/" + name + ".json";
		let save_info = {};
		save_info[name] = info;
		if (ALittle.File_SaveFile(file_path, ALittle.String_JsonEncode(save_info), -1) === false) {
			return "文件保存失败:" + file_path;
		}
		let all_info = this._control_map[name];
		if (all_info !== undefined) {
			let ___OBJECT_6 = all_info.extends_other;
			for (let other_name in ___OBJECT_6) {
				let v = ___OBJECT_6[other_name];
				if (v === undefined) continue;
				let other = this._control_map[other_name];
				if (other !== undefined) {
					delete other.extends_this[name];
				} else {
					ALittle.Log("IDEProject:SaveControl calc extends failed:", other_name);
				}
			}
			all_info.extends_other = {};
			let ___OBJECT_7 = all_info.extends_this;
			for (let other_name in ___OBJECT_7) {
				let v = ___OBJECT_7[other_name];
				if (v === undefined) continue;
				let other = this._control_map[other_name];
				if (other !== undefined) {
					this._control.RegisterInfo(other.name, ALittle.String_CopyTable(other.info));
				} else {
					ALittle.Log("IDEProject:SaveControl calc extends failed:", other_name);
				}
			}
		} else {
			all_info = {};
			all_info.info = info;
			all_info.name = name;
			all_info.extends_this = {};
			all_info.extends_other = {};
		}
		let map = ALittleIDE.IDEUIUtility_GetExtends(info);
		let ___OBJECT_8 = map;
		for (let other_name in ___OBJECT_8) {
			let v = ___OBJECT_8[other_name];
			if (v === undefined) continue;
			let other = this._control_map[other_name];
			if (other !== undefined) {
				other.extends_this[name] = true;
				all_info.extends_other[other_name] = true;
			} else {
				ALittle.Log("IDEProject:SaveControl calc extends failed:", other_name);
			}
		}
		all_info.info = info;
		this._control_map[name] = all_info;
		this._control.RegisterInfo(name, ALittle.String_CopyTable(info));
		return undefined;
	},
	CanDelete : function(name) {
		let all_info = this._control_map[name];
		if (all_info === undefined) {
			return "控件不存在:" + name;
		}
		let extends_name = undefined;
		let ___OBJECT_9 = all_info.extends_this;
		for (let k in ___OBJECT_9) {
			let v = ___OBJECT_9[k];
			if (v === undefined) continue;
			extends_name = k;
			break;
		}
		if (extends_name !== undefined) {
			return "被其他控件引用:" + extends_name;
		}
		return undefined;
	},
	DeleteControl : function(name) {
		let error = this.CanDelete(name);
		if (error !== error) {
			return error;
		}
		let file_path = this._base_path + "/" + name + ".json";
		ALittle.File_DeleteFile(file_path);
		let all_info = this._control_map[name];
		let ___OBJECT_10 = all_info.extends_other;
		for (let other_name in ___OBJECT_10) {
			let v = ___OBJECT_10[other_name];
			if (v === undefined) continue;
			let other = this._control_map[other_name];
			if (other !== undefined) {
				delete other.extends_this[name];
			}
		}
		let e = {};
		e.name = name;
		ALittleIDE.g_IDEProject.DispatchEvent(___all_struct.get(1962591044), e);
		delete this._control_map[name];
		this._control.UnRegisterInfo(name);
		return undefined;
	},
	RenameControl : function(old_name, new_name) {
		let all_info = this._control_map[old_name];
		if (all_info === undefined) {
			return "控件不存在:" + old_name;
		}
		let error = this.CanDelete(old_name);
		if (error !== undefined) {
			return "控件被其他控件引用，不能重命名";
		}
		if (this._control_map[new_name] !== undefined) {
			return "控件已存在:" + new_name;
		}
		let e = {};
		e.name = old_name;
		ALittleIDE.g_IDEProject.DispatchEvent(___all_struct.get(1962591044), e);
		delete this._control_map[old_name];
		this._control.UnRegisterInfo(old_name);
		let file_path = this._base_path + "UI/" + old_name + ".json";
		ALittle.File_DeleteFile(file_path);
		all_info.name = new_name;
		this._control_map[new_name] = all_info;
		this._control.RegisterInfo(new_name, ALittle.String_CopyTable(all_info.info));
		file_path = this._base_path + "/" + new_name + ".json";
		let save_info = {};
		save_info[new_name] = all_info.info;
		ALittle.File_SaveFile(file_path, ALittle.String_JsonEncode(save_info), -1);
		let ce = {};
		ce.name = new_name;
		ALittleIDE.g_IDEProject.DispatchEvent(___all_struct.get(-93681239), ce);
		return undefined;
	},
}, "ALittleIDE.IDEUIManager");

}