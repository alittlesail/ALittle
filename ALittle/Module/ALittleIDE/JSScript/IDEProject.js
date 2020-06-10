{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(1910687721, "ALittleIDE.IDEProjectEvent", {
name : "ALittleIDE.IDEProjectEvent", ns_name : "ALittleIDE", rl_name : "IDEProjectEvent", hash_code : 1910687721,
name_list : ["target","name"],
type_list : ["ALittle.EventDispatcher","string"],
option_map : {}
})
ALittle.RegStruct(-975432877, "ALittleIDE.IDEProjectOpenEvent", {
name : "ALittleIDE.IDEProjectOpenEvent", ns_name : "ALittleIDE", rl_name : "IDEProjectOpenEvent", hash_code : -975432877,
name_list : ["target","name"],
type_list : ["ALittle.EventDispatcher","string"],
option_map : {}
})
ALittle.RegStruct(-332308624, "ALittleIDE.IDEProjectCloseEvent", {
name : "ALittleIDE.IDEProjectCloseEvent", ns_name : "ALittleIDE", rl_name : "IDEProjectCloseEvent", hash_code : -332308624,
name_list : ["target","name"],
type_list : ["ALittle.EventDispatcher","string"],
option_map : {}
})
ALittle.RegStruct(-93681239, "ALittleIDE.IDEProjectCreateControlEvent", {
name : "ALittleIDE.IDEProjectCreateControlEvent", ns_name : "ALittleIDE", rl_name : "IDEProjectCreateControlEvent", hash_code : -93681239,
name_list : ["target","name"],
type_list : ["ALittle.EventDispatcher","string"],
option_map : {}
})
ALittle.RegStruct(-4982446, "ALittle.DisplayInfo", {
name : "ALittle.DisplayInfo", ns_name : "ALittle", rl_name : "DisplayInfo", hash_code : -4982446,
name_list : ["__target_class","__class_func","__base_attr","__show_attr","loop_map","__class","__include","__extends","__childs","__event","__link","__shows_included","__childs_included","__extends_included","description","text","font_path","font_size","red","green","blue","alpha","bold","italic","underline","deleteline","outline","x","y","x_type","x_value","y_type","y_value","width","height","width_type","width_value","height_type","height_value","scale_x","scale_y","center_x","center_y","angle","flip","hand_cursor","visible","disabled","left_size","right_size","top_size","bottom_size","texture_name","interval","play_loop_count","var_play","base_y","head_size","gap","up_size","down_size","cursor_red","cursor_green","cursor_blue","default_text_alpha","ims_padding","margin_left","margin_right","margin_top","margin_bottom","show_count","body_margin","screen_margin_left","screen_margin_right","screen_margin_top","screen_margin_bottom","start_degree","end_degree","line_spacing","max_line_count","font_red","font_green","font_blue","margin_halign","margin_valign","cursor_margin_up","cursor_margin_down","total_size","show_size","offset_rate","offset_step","grade","row_count","col_count","row_index","col_index","u1","v1","u2","v2","u3","v3","x1","y1","x2","y2","x3","y3","x_gap","y_gap","x_start_gap","y_start_gap","button_gap","button_start","button_margin","tab_index","view_margin","child_width_margin"],
type_list : ["List<string>","any","Map<string,any>","Map<string,any>","Map<string,ALittle.LoopGroupInfo>","string","string","string","List<ALittle.DisplayInfo>","List<ALittle.EventInfo>","string","bool","bool","bool","string","string","string","int","double","double","double","double","bool","bool","bool","bool","bool","double","double","int","double","int","double","double","double","int","double","int","double","double","double","double","double","double","int","bool","bool","bool","double","double","double","double","string","int","int","bool","double","double","double","double","double","double","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","double","double","double","int","int","int","int","int","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(374071006, "ALittleIDE.IDEProjectChangeControlEvent", {
name : "ALittleIDE.IDEProjectChangeControlEvent", ns_name : "ALittleIDE", rl_name : "IDEProjectChangeControlEvent", hash_code : 374071006,
name_list : ["target","name"],
type_list : ["ALittle.EventDispatcher","string"],
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
ALittle.RegStruct(1962591044, "ALittleIDE.IDEProjectDeleteControlEvent", {
name : "ALittleIDE.IDEProjectDeleteControlEvent", ns_name : "ALittleIDE", rl_name : "IDEProjectDeleteControlEvent", hash_code : 1962591044,
name_list : ["target","name"],
type_list : ["ALittle.EventDispatcher","string"],
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
ALittle.RegStruct(489101099, "ALittleIDE.IDEControlCopyInfo", {
name : "ALittleIDE.IDEControlCopyInfo", ns_name : "ALittleIDE", rl_name : "IDEControlCopyInfo", hash_code : 489101099,
name_list : ["index","info"],
type_list : ["int","ALittle.DisplayInfo"],
option_map : {}
})
ALittle.RegStruct(934918978, "ALittleIDE.IDEProjectInfo", {
name : "ALittleIDE.IDEProjectInfo", ns_name : "ALittleIDE", rl_name : "IDEProjectInfo", hash_code : 934918978,
name_list : ["name","base_path","save","control","config","control_map"],
type_list : ["string","string","bool","ALittle.ControlSystem","ALittle.IJsonConfig","Map<string,ALittleIDE.IDEControlInfo>"],
option_map : {}
})

if (ALittle.EventDispatcher === undefined) throw new Error(" extends class:ALittle.EventDispatcher is undefined");
ALittleIDE.IDEProject = JavaScript.Class(ALittle.EventDispatcher, {
	Ctor : function() {
	},
	AddProjectConfig : function(name) {
		let project_map = ALittleIDE.g_IDEConfig.GetConfig("project_map", {});
		if (project_map[name] === undefined) {
			project_map[name] = name;
			ALittleIDE.g_IDEConfig.SetConfig("project_map", project_map);
		}
	},
	RemoveProjectConfig : function(name) {
		let project_map = ALittleIDE.g_IDEConfig.GetConfig("project_map", {});
		if (project_map[name] === undefined) {
			return;
		}
		delete project_map[name];
		ALittleIDE.g_IDEConfig.SetConfig("project_map", project_map);
	},
	NewProject : function(name, window_width, window_height, font_path, font_size) {
		ALittle.File_MakeDeepDir(ALittle.File_BaseFilePath() + "Module/" + name);
		ALittle.File_MakeDir(ALittle.File_BaseFilePath() + "Module/" + name + "/Texture");
		ALittle.File_MakeDir(ALittle.File_BaseFilePath() + "Module/" + name + "/Texture/" + name);
		ALittle.File_MakeDir(ALittle.File_BaseFilePath() + "Module/" + name + "/Font");
		ALittle.File_MakeDir(ALittle.File_BaseFilePath() + "Module/" + name + "/Sound");
		ALittle.File_MakeDir(ALittle.File_BaseFilePath() + "Module/" + name + "/Other");
		ALittle.File_MakeDir(ALittle.File_BaseFilePath() + "Module/" + name + "/Script");
		ALittle.File_MakeDir(ALittle.File_BaseFilePath() + "Module/" + name + "/UI");
		ALittle.File_MakeDir(ALittle.File_BaseFilePath() + "Module/" + name + "/Icon");
		ALittle.File_WriteTextToFile("", ALittle.File_BaseFilePath() + "Module/" + name + "/NoCrypt.ali");
		let base_path = ALittle.File_BaseFilePath() + "Module/ALittleIDE/Other/GameTemplate";
		let target_path = ALittle.File_BaseFilePath() + "Module/" + name + "/";
		let file_map = ALittle.File_GetFileAttrByDir(base_path);
		let ___OBJECT_1 = file_map;
		for (let file_path in ___OBJECT_1) {
			let attr = ___OBJECT_1[file_path];
			if (attr === undefined) continue;
			let rel_path = ALittle.String_Sub(file_path, ALittle.String_Len(base_path) + 1);
			let full_path = target_path + rel_path;
			full_path = ALittle.String_Replace(full_path, "abcd@module_name@abcd", name);
			full_path = ALittle.String_Replace(full_path, "abcd@upper_module_name@abcd", ALittle.String_Upper(name));
			full_path = ALittle.String_Replace(full_path, "abcd@lower_module_name@abcd", ALittle.String_Lower(name));
			ALittle.File_MakeDeepDir(ALittle.File_GetFilePathByPath(full_path));
			let ext = ALittle.String_Upper(ALittle.File_GetFileExtByPath(file_path));
			if (ext === "JSON" || ext === "LUA" || ext === "CFG" || ext === "TXT" || ext === "ALITTLE" || ext === "XML" || ext === "NAME" || ext === "SLN" || ext === "VCXPROJ" || ext === "FILTERS" || ext === "USER") {
				let content = ALittle.File_ReadTextFromFile(file_path);
				if (content !== undefined) {
					content = ALittle.String_Replace(content, "abcd@module_name@abcd", name);
					content = ALittle.String_Replace(content, "abcd@upper_module_name@abcd", ALittle.String_Upper(name));
					content = ALittle.String_Replace(content, "abcd@lower_module_name@abcd", ALittle.String_Lower(name));
					content = ALittle.String_Replace(content, "abcd@view_width@abcd", "" + window_width);
					content = ALittle.String_Replace(content, "abcd@view_height@abcd", "" + window_height);
					content = ALittle.String_Replace(content, "abcd@font_path@abcd", font_path);
					ALittle.File_WriteTextToFile(content, full_path);
				}
			} else {
				ALittle.File_CopyFile(file_path, full_path);
			}
		}
		ALittle.File_CopyFile("Export/Icon/install.ico", ALittle.File_BaseFilePath() + "Module/" + name + "/Icon/install.ico");
		ALittle.File_CopyFile("Export/Icon/install.png", ALittle.File_BaseFilePath() + "Module/" + name + "/Icon/install.png");
		let config = ALittle.CreateConfigSystem("Module/" + name + "/ALittleIDE.cfg");
		config.SetConfig("default_show_width", window_width, true);
		config.SetConfig("default_show_height", window_height, true);
		config.SetConfig("default_font_path", font_path, true);
		config.SetConfig("default_font_size", font_size, true);
		config.SaveConfig();
		this.AddProjectConfig(name);
		return true;
	},
	OpenProject : function(name) {
		this.AddProjectConfig(name);
		this._project = {};
		this._project.name = name;
		this._project.base_path = ALittle.File_BaseFilePath() + "Module/" + name + "/";
		this._project.save = true;
		this._project.control = ALittle.NewObject(ALittle.ControlSystem, name);
		this._project.control.log_error = false;
		this._project.control.cache_texture = false;
		this._project.config = ALittle.CreateConfigSystem("Module/" + name + "/ALittleIDE.cfg");
		let control_map = {};
		this._project.control_map = control_map;
		let path = ALittle.File_BaseFilePath() + "Module/" + name + "/UI";
		let file_map = ALittle.File_GetFileAttrByDir(path);
		let ___OBJECT_2 = file_map;
		for (let file_path in ___OBJECT_2) {
			let attr = ___OBJECT_2[file_path];
			if (attr === undefined) continue;
			let ext = ALittle.String_Upper(ALittle.File_GetFileExtByPath(file_path));
			if (ext === "JSON") {
				let content = ALittle.File_ReadTextFromFile(file_path);
				if (content !== undefined) {
					let [error, content_info_map] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
					if (error === undefined) {
						let ___OBJECT_3 = content_info_map;
						for (let control_name in ___OBJECT_3) {
							let control_info = ___OBJECT_3[control_name];
							if (control_info === undefined) continue;
							let all_info = {};
							all_info.info = control_info;
							all_info.name = control_name;
							all_info.extends_this = {};
							all_info.extends_other = {};
							if (control_map[control_name] !== undefined) {
								ALittle.Log("IDEProject:OpenProject control_name:" + control_name + " repeat in " + file_path);
							}
							control_map[control_name] = all_info;
						}
					} else {
						ALittle.Log("IDEProject:OpenProject json decode failed:", file_path, content_info_map);
					}
				} else {
					ALittle.Log("IDEProject:OpenProject failed:", file_path);
				}
			}
		}
		let ___OBJECT_4 = control_map;
		for (let control_name in ___OBJECT_4) {
			let all_info = ___OBJECT_4[control_name];
			if (all_info === undefined) continue;
			let map = ALittleIDE.IDEUtility_GetExtends(all_info.info);
			let ___OBJECT_5 = map;
			for (let other_name in ___OBJECT_5) {
				let v = ___OBJECT_5[other_name];
				if (v === undefined) continue;
				let other = control_map[other_name];
				if (other !== undefined) {
					other.extends_this[control_name] = true;
					all_info.extends_other[other_name] = true;
				} else {
					ALittle.Log("IDEProject:OpenProject calc extends failed:", other_name);
				}
			}
		}
		ALittleIDE.g_IDEConfig.SetConfig("last_project", name);
		let e = {};
		e.name = name;
		this.DispatchEvent(___all_struct.get(-975432877), e);
		return true;
	},
	IsControlExist : function(name) {
		if (this._project === undefined) {
			return false;
		}
		return this._project.control_map[name] !== undefined;
	},
	CalcDeepExtends : function(name, map, lock_map) {
		if (map === undefined) {
			map = {};
		}
		if (lock_map === undefined) {
			lock_map = {};
		}
		let info = this._project.control_map[name];
		if (info === undefined) {
			return map;
		}
		map[name] = true;
		let ___OBJECT_6 = info.extends_other;
		for (let other_name in ___OBJECT_6) {
			let v = ___OBJECT_6[other_name];
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
		let file_path = this._project.base_path + "UI/" + name + ".json";
		let save_info = {};
		save_info[name] = info;
		if (ALittle.File_SaveFile(file_path, ALittle.String_JsonEncode(save_info), -1) === false) {
			return [false, "文件保存失败:" + file_path];
		}
		let all_info = this._project.control_map[name];
		if (all_info !== undefined) {
			let ___OBJECT_7 = all_info.extends_other;
			for (let other_name in ___OBJECT_7) {
				let v = ___OBJECT_7[other_name];
				if (v === undefined) continue;
				let other = this._project.control_map[other_name];
				if (other !== undefined) {
					delete other.extends_this[name];
				} else {
					ALittle.Log("IDEProject:SaveControl calc extends failed:", other_name);
				}
			}
			all_info.extends_other = {};
			let ___OBJECT_8 = all_info.extends_this;
			for (let other_name in ___OBJECT_8) {
				let v = ___OBJECT_8[other_name];
				if (v === undefined) continue;
				let other = this._project.control_map[other_name];
				if (other !== undefined) {
					this._project.control.RegisterInfo(other.name, ALittle.String_CopyTable(other.info));
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
		let map = ALittleIDE.IDEUtility_GetExtends(info);
		let ___OBJECT_9 = map;
		for (let other_name in ___OBJECT_9) {
			let v = ___OBJECT_9[other_name];
			if (v === undefined) continue;
			let other = this._project.control_map[other_name];
			if (other !== undefined) {
				other.extends_this[name] = true;
				all_info.extends_other[other_name] = true;
			} else {
				ALittle.Log("IDEProject:SaveControl calc extends failed:", other_name);
			}
		}
		all_info.info = info;
		this._project.control_map[name] = all_info;
		this._project.control.RegisterInfo(name, ALittle.String_CopyTable(info));
		let e = {};
		e.name = name;
		this.DispatchEvent(___all_struct.get(374071006), e);
		return [true, undefined];
	},
	CanDelete : function(name) {
		let all_info = this._project.control_map[name];
		if (all_info === undefined) {
			return [false, "控件不存在:" + name];
		}
		let extends_name = undefined;
		let ___OBJECT_10 = all_info.extends_this;
		for (let k in ___OBJECT_10) {
			let v = ___OBJECT_10[k];
			if (v === undefined) continue;
			extends_name = k;
			break;
		}
		if (extends_name !== undefined) {
			return [false, "被其他控件引用:" + extends_name];
		}
		return [true, undefined];
	},
	DeleteControl : function(name) {
		let [result, content] = this.CanDelete(name);
		if (result === false) {
			return [result, content];
		}
		let file_path = this._project.base_path + "UI/" + name + ".json";
		ALittle.File_DeleteFile(file_path);
		let all_info = this._project.control_map[name];
		let ___OBJECT_11 = all_info.extends_other;
		for (let other_name in ___OBJECT_11) {
			let v = ___OBJECT_11[other_name];
			if (v === undefined) continue;
			let other = this._project.control_map[other_name];
			if (other !== undefined) {
				delete other.extends_this[name];
			}
		}
		let e = {};
		e.name = name;
		this.DispatchEvent(___all_struct.get(1962591044), e);
		delete this._project.control_map[name];
		this._project.control.UnRegisterInfo(name);
		return [true, undefined];
	},
	RenameControl : function(old_name, new_name) {
		let all_info = this._project.control_map[old_name];
		if (all_info === undefined) {
			return [false, "控件不存在:" + old_name];
		}
		let [result, content] = this.CanDelete(old_name);
		if (result === false) {
			return [result, "控件被其他控件引用，不能重命名"];
		}
		if (this._project.control_map[new_name] !== undefined) {
			return [false, "控件已存在:" + new_name];
		}
		let e = {};
		e.name = old_name;
		this.DispatchEvent(___all_struct.get(1962591044), e);
		delete this._project.control_map[old_name];
		this._project.control.UnRegisterInfo(old_name);
		let file_path = this._project.base_path + "UI/" + old_name + ".json";
		ALittle.File_DeleteFile(file_path);
		all_info.name = new_name;
		this._project.control_map[new_name] = all_info;
		this._project.control.RegisterInfo(new_name, ALittle.String_CopyTable(all_info.info));
		file_path = this._project.base_path + "UI/" + new_name + ".json";
		let save_info = {};
		save_info[new_name] = all_info.info;
		ALittle.File_SaveFile(file_path, ALittle.String_JsonEncode(save_info), -1);
		let ce = {};
		ce.name = new_name;
		this.DispatchEvent(___all_struct.get(-93681239), ce);
		return [true, undefined];
	},
	CloseProject : function() {
		if (this._project === undefined) {
			return [false, "当前没有项目"];
		}
		let e = {};
		e.name = this._project.name;
		this.DispatchEvent(___all_struct.get(-332308624), e);
		this._project = undefined;
		return [true, undefined];
	},
	RemoveProject : function(name) {
		if (this._project !== undefined && this._project.name === name) {
			return [false, "请先关闭项目，再移除"];
		}
		this.RemoveProjectConfig(name);
		let project_name = ALittleIDE.g_IDEConfig.GetConfig("last_project", "");
		if (project_name === name) {
			ALittleIDE.g_IDEConfig.SetConfig("last_project", "");
		}
		return [true, undefined];
	},
	get project() {
		return this._project;
	},
}, "ALittleIDE.IDEProject");

ALittleIDE.g_IDEProject = ALittle.NewObject(ALittleIDE.IDEProject);
}