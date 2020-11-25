{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(2057209532, "AUIPlugin.AUICodeProjectGotoEvent", {
name : "AUIPlugin.AUICodeProjectGotoEvent", ns_name : "AUIPlugin", rl_name : "AUICodeProjectGotoEvent", hash_code : 2057209532,
name_list : ["target","file_path","line_start","char_start","line_end","char_end"],
type_list : ["ALittle.EventDispatcher","string","int","int","int","int"],
option_map : {}
})
ALittle.RegStruct(1962591044, "ALittleIDE.IDEProjectDeleteControlEvent", {
name : "ALittleIDE.IDEProjectDeleteControlEvent", ns_name : "ALittleIDE", rl_name : "IDEProjectDeleteControlEvent", hash_code : 1962591044,
name_list : ["target","module","name"],
type_list : ["ALittle.EventDispatcher","string","string"],
option_map : {}
})
ALittle.RegStruct(1910687721, "ALittleIDE.IDEProjectEvent", {
name : "ALittleIDE.IDEProjectEvent", ns_name : "ALittleIDE", rl_name : "IDEProjectEvent", hash_code : 1910687721,
name_list : ["target","module","name"],
type_list : ["ALittle.EventDispatcher","string","string"],
option_map : {}
})
ALittle.RegStruct(1787992834, "ALittleIDE.IDEProjectSettingChanged", {
name : "ALittleIDE.IDEProjectSettingChanged", ns_name : "ALittleIDE", rl_name : "IDEProjectSettingChanged", hash_code : 1787992834,
name_list : ["target","default_show_width","default_show_height","default_font_path","default_font_size"],
type_list : ["ALittle.EventDispatcher","double","double","string","int"],
option_map : {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(-975432877, "ALittleIDE.IDEProjectOpenEvent", {
name : "ALittleIDE.IDEProjectOpenEvent", ns_name : "ALittleIDE", rl_name : "IDEProjectOpenEvent", hash_code : -975432877,
name_list : ["target","module","name"],
type_list : ["ALittle.EventDispatcher","string","string"],
option_map : {}
})
ALittle.RegStruct(934918978, "ALittleIDE.IDEProjectInfo", {
name : "ALittleIDE.IDEProjectInfo", ns_name : "ALittleIDE", rl_name : "IDEProjectInfo", hash_code : 934918978,
name_list : ["name","config","ui","code"],
type_list : ["string","ALittle.IJsonConfig","Map<string,ALittleIDE.IDEUIManager>","AUIPlugin.AUICodeProject"],
option_map : {}
})
ALittle.RegStruct(-685984390, "ALittleIDE.IDEProjectAddEvent", {
name : "ALittleIDE.IDEProjectAddEvent", ns_name : "ALittleIDE", rl_name : "IDEProjectAddEvent", hash_code : -685984390,
name_list : ["target","module","name"],
type_list : ["ALittle.EventDispatcher","string","string"],
option_map : {}
})
ALittle.RegStruct(374071006, "ALittleIDE.IDEProjectChangeControlEvent", {
name : "ALittleIDE.IDEProjectChangeControlEvent", ns_name : "ALittleIDE", rl_name : "IDEProjectChangeControlEvent", hash_code : 374071006,
name_list : ["target","module","name"],
type_list : ["ALittle.EventDispatcher","string","string"],
option_map : {}
})
ALittle.RegStruct(-332308624, "ALittleIDE.IDEProjectCloseEvent", {
name : "ALittleIDE.IDEProjectCloseEvent", ns_name : "ALittleIDE", rl_name : "IDEProjectCloseEvent", hash_code : -332308624,
name_list : ["target","module","name"],
type_list : ["ALittle.EventDispatcher","string","string"],
option_map : {}
})
ALittle.RegStruct(-277092447, "ALittleIDE.IDEProjectRemoveEvent", {
name : "ALittleIDE.IDEProjectRemoveEvent", ns_name : "ALittleIDE", rl_name : "IDEProjectRemoveEvent", hash_code : -277092447,
name_list : ["target","module","name"],
type_list : ["ALittle.EventDispatcher","string","string"],
option_map : {}
})
ALittle.RegStruct(-93681239, "ALittleIDE.IDEProjectCreateControlEvent", {
name : "ALittleIDE.IDEProjectCreateControlEvent", ns_name : "ALittleIDE", rl_name : "IDEProjectCreateControlEvent", hash_code : -93681239,
name_list : ["target","module","name"],
type_list : ["ALittle.EventDispatcher","string","string"],
option_map : {}
})

if (ALittle.EventDispatcher === undefined) throw new Error(" extends class:ALittle.EventDispatcher is undefined");
ALittleIDE.IDEProject = JavaScript.Class(ALittle.EventDispatcher, {
	Ctor : function() {
		this._in_debug = false;
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
	GetBreakPoint : function(file_path) {
		if (this._project === undefined) {
			return undefined;
		}
		let map = this._project.config.GetConfig("break_points", undefined);
		if (map === undefined) {
			return undefined;
		}
		return map[file_path];
	},
	AddBreakPoint : function(file_path, line) {
		if (this._project === undefined) {
			return;
		}
		let map = this._project.config.GetConfig("break_points", undefined);
		if (map === undefined) {
			map = {};
		}
		let lines = map[file_path];
		if (lines === undefined) {
			lines = [];
			map[file_path] = lines;
		}
		if (ALittle.List_IndexOf(lines, line) === undefined) {
			ALittle.List_Push(lines, line);
		}
		this._project.config.SetConfig("break_points", map);
		if (this._debug_client !== undefined) {
			this._debug_client.AddBreakPoint(file_path, line);
		}
	},
	RemoveBreakPoint : function(file_path, line) {
		if (this._project === undefined) {
			return;
		}
		let map = this._project.config.GetConfig("break_points", undefined);
		if (map === undefined) {
			return;
		}
		let lines = map[file_path];
		if (lines === undefined) {
			return;
		}
		let index = ALittle.List_IndexOf(lines, line);
		if (index !== undefined) {
			ALittle.List_Remove(lines, index);
		}
		if (ALittle.IsEmpty(lines)) {
			delete map[file_path];
		}
		this._project.config.SetConfig("break_points", map);
		if (this._debug_client !== undefined) {
			this._debug_client.RemoveBreakPoint(file_path, line);
		}
	},
	NewProject : function(name, window_width, window_height, font_path, font_size) {
		ALittle.File_MakeDeepDir(ALittle.File_BaseFilePath() + "Module/" + name);
		ALittle.File_MakeDir(ALittle.File_BaseFilePath() + "Module/" + name + "/Texture");
		ALittle.File_MakeDir(ALittle.File_BaseFilePath() + "Module/" + name + "/Font");
		ALittle.File_MakeDir(ALittle.File_BaseFilePath() + "Module/" + name + "/Sound");
		ALittle.File_MakeDir(ALittle.File_BaseFilePath() + "Module/" + name + "/Other");
		ALittle.File_MakeDir(ALittle.File_BaseFilePath() + "Module/" + name + "/JSScript");
		ALittle.File_MakeDir(ALittle.File_BaseFilePath() + "Module/" + name + "/Script");
		ALittle.File_MakeDir(ALittle.File_BaseFilePath() + "Module/" + name + "/UI");
		ALittle.File_MakeDir(ALittle.File_BaseFilePath() + "Module/" + name + "/Tile");
		ALittle.File_MakeDir(ALittle.File_BaseFilePath() + "Module/" + name + "/Icon");
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
		let event = {};
		event.name = name;
		this.DispatchEvent(___all_struct.get(-685984390), event);
		return true;
	},
	RefreshProject : function() {
		if (this._project === undefined) {
			return;
		}
		let name = this._project.name;
		this.CloseProject();
		this.OpenProject(name);
	},
	OpenProject : function(name) {
		if (name === "" || name === undefined) {
			return "请输入项目名";
		}
		this.CloseProject();
		this.AddProjectConfig(name);
		this._project = {};
		this._project.name = name;
		this._project.config = ALittle.CreateConfigSystem("Module/" + name + "/ALittleIDE.cfg");
		this._project.ui = {};
		ALittleIDE.g_IDEConfig.SetConfig("last_project", name);
		let e = {};
		e.name = name;
		this.DispatchEvent(___all_struct.get(-975432877), e);
		return undefined;
	},
	HandleCodeProjectGoToEvent : function(event) {
		ALittleIDE.g_IDECenter.center.code_list.OpenByFullPath(event.file_path, event.line_start, event.char_start, event.line_end, event.char_end);
	},
	OpenLastProject : function() {
		let default_name = "BattleCity";
		let name = ALittleIDE.g_IDEConfig.GetString("last_project", default_name);
		if (name === undefined) {
			return;
		}
		this.OpenProject(name);
	},
	CloseProject : function() {
		if (this._project === undefined) {
			return "当前没有项目";
		}
		let e = {};
		e.name = this._project.name;
		this.DispatchEvent(___all_struct.get(-332308624), e);
		if (this._project.code !== undefined) {
			this._project.code.RemoveEventListener(___all_struct.get(2057209532), this, this.HandleCodeProjectGoToEvent);
			this._project.code.Stop();
		}
		this._project = undefined;
		if (this._debug_loop !== undefined) {
			this._debug_loop.Stop();
			this._debug_loop = undefined;
		}
		if (this._debug_client !== undefined) {
			this._debug_client.Close();
			this._debug_client = undefined;
		}
		this._in_debug = false;
		return undefined;
	},
	RemoveProject : function(name) {
		if (this._project !== undefined && this._project.name === name) {
			return "请先关闭项目，再移除";
		}
		this.RemoveProjectConfig(name);
		let project_name = ALittleIDE.g_IDEConfig.GetConfig("last_project", "");
		if (project_name === name) {
			ALittleIDE.g_IDEConfig.SetConfig("last_project", "");
		}
		let event = {};
		event.name = name;
		this.DispatchEvent(___all_struct.get(-277092447), event);
		return undefined;
	},
	RunProject : function(debug) {
		if (this._project === undefined) {
			g_AUITool.ShowNotice("提示", "当前没有打开的项目");
			return;
		}
		let debug_info = "";
		if (debug) {
			debug_info = "debug";
		}
	},
	IsDebug : function() {
		return this._in_debug;
	},
	StartDebugProject : function() {
		if (this._project === undefined) {
			g_AUITool.ShowNotice("提示", "当前没有打开的项目");
			return;
		}
		if (this._in_debug) {
			g_AUITool.ShowNotice("提示", "已启动调试");
			return;
		}
		if (this._debug_client === undefined) {
			this._debug_client = ALittle.NewObject(carp.CarpLuaDebugClient);
		}
		this._debug_client.Start("127.0.0.1", 1001);
		this._in_debug = true;
		if (this._debug_loop === undefined) {
			this._debug_loop = ALittle.NewObject(ALittle.LoopFrame, this.HandleDebugFrame.bind(this));
		}
		this._debug_loop.Start();
		let break_map = this._project.config.GetConfig("break_points", undefined);
		let ___OBJECT_2 = break_map;
		for (let file_path in ___OBJECT_2) {
			let lines = ___OBJECT_2[file_path];
			if (lines === undefined) continue;
			let ___OBJECT_3 = lines;
			for (let index = 1; index <= ___OBJECT_3.length; ++index) {
				let line = ___OBJECT_3[index - 1];
				if (line === undefined) break;
				this._debug_client.AddBreakPoint(file_path, line);
			}
		}
	},
	ContinueDebug : function() {
		if (this._debug_client === undefined) {
			return;
		}
		this._debug_client.DoContinue();
	},
	NextLineDebug : function() {
		if (this._debug_client === undefined) {
			return;
		}
		this._debug_client.DoNextLine();
	},
	HandleDebugFrame : function(frame_time) {
		let event = this._debug_client.HandleEvent();
		if (event === undefined) {
			return;
		}
		if (event.type === 1) {
			ALittleIDE.g_IDECenter.center.code_list.OpenByFullPath(event.file_path, event.file_line, 1, event.file_line, 1);
		} else if (event.type === 2) {
		}
	},
	StopDebugProject : function() {
		if (this._project === undefined) {
			g_AUITool.ShowNotice("提示", "当前没有打开的项目");
			return;
		}
		if (this._debug_loop !== undefined) {
			this._debug_loop.Stop();
			this._debug_loop = undefined;
		}
		if (this._debug_client !== undefined) {
			this._debug_client.Close();
			this._debug_client = undefined;
		}
		this._in_debug = false;
	},
	get project() {
		return this._project;
	},
	GetUIManager : function(module_name) {
		if (this._project === undefined) {
			return undefined;
		}
		if (module_name === undefined) {
			module_name = this._project.name;
		}
		return this._project.ui[module_name];
	},
}, "ALittleIDE.IDEProject");

ALittleIDE.g_IDEProject = ALittle.NewObject(ALittleIDE.IDEProject);
}