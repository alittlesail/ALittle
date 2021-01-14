{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};

ALittle.RegStruct(2057209532, "AUIPlugin.AUICodeProjectGotoEvent", {
name : "AUIPlugin.AUICodeProjectGotoEvent", ns_name : "AUIPlugin", rl_name : "AUICodeProjectGotoEvent", hash_code : 2057209532,
name_list : ["target","file_path","line_start","char_start","line_end","char_end"],
type_list : ["ALittle.EventDispatcher","string","int","int","int","int"],
option_map : {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})

AUIPlugin.g_ABnfProjectMap = ALittle.CreateValueWeakMap();
AUIPlugin.g_UpperExtMapABnf = {};
AUIPlugin.g_UpperExtMapABnf["JSON"] = "AJson.abnf";
AUIPlugin.g_UpperExtMapABnf["CFG"] = "AJson.abnf";
AUIPlugin.g_UpperExtMapABnf["XML"] = "AXml.abnf";
AUIPlugin.g_UpperExtMapABnf["LUA"] = "ALua.abnf";
if (ALittle.EventDispatcher === undefined) throw new Error(" extends class:ALittle.EventDispatcher is undefined");
AUIPlugin.AUICodeProject = JavaScript.Class(ALittle.EventDispatcher, {
	Ctor : function(project) {
		this._query_id = 0;
		this._project = project;
		this._map = new Map();
	},
	CreateALittleScriptProject : function() {
		if (lua.alittlescript === undefined) {
			return undefined;
		}
		let abnf_buffer = ALittle.File_ReadTextFromFile(AUIPlugin.g_ModuleBasePath + "Other/ABnf/ALittleScript.abnf");
		let project = ALittle.NewObject(AUIPlugin.AUICodeALittleScriptProject, lua.alittlescript.create_alittlescript_project(abnf_buffer));
		project.Start();
		return project;
	},
	CreateABnfProject : function() {
		if (lua.abnf === undefined) {
			return undefined;
		}
		let abnf_project = AUIPlugin.g_ABnfProjectMap["abnf"];
		if (abnf_project === undefined) {
			let abnf_buffer = ALittle.File_ReadTextFromFile(AUIPlugin.g_ModuleBasePath + "/Other/ABnf/ABnf.abnf");
			abnf_project = ALittle.NewObject(AUIPlugin.AUICodeABnfProject, lua.abnf.create_abnf_project(abnf_buffer));
			AUIPlugin.g_ABnfProjectMap["abnf"] = abnf_project;
			abnf_project.Start();
		}
		return abnf_project;
	},
	SupportUpperExt : function(upper_ext) {
		return AUIPlugin.g_UpperExtMapABnf[upper_ext] !== undefined;
	},
	CreateCommonProject : function(upper_ext) {
		if (lua.alanguage === undefined) {
			return undefined;
		}
		let abnf = AUIPlugin.g_UpperExtMapABnf[upper_ext];
		if (abnf === undefined) {
			return undefined;
		}
		let abnf_project = AUIPlugin.g_ABnfProjectMap[abnf];
		if (abnf_project === undefined) {
			let abnf_buffer = ALittle.File_ReadTextFromFile(AUIPlugin.g_ModuleBasePath + "/Other/ABnf/" + abnf);
			abnf_project = ALittle.NewObject(AUIPlugin.AUICodeCommonProject, lua.alanguage.create_abnfproject(abnf_buffer), upper_ext);
			AUIPlugin.g_ABnfProjectMap[abnf] = abnf_project;
			abnf_project.Start();
		}
		return abnf_project;
	},
	Shutdown : function() {
		let ___OBJECT_1 = AUIPlugin.g_ABnfProjectMap;
		for (let name in ___OBJECT_1) {
			let project = ___OBJECT_1[name];
			if (project === undefined) continue;
			project.Stop();
		}
		AUIPlugin.g_ABnfProjectMap = ALittle.CreateValueWeakMap();
	},
	get upper_ext() {
		return undefined;
	},
	get project() {
		return this._project;
	},
	QueryRuleColor : function() {
		return lua.alanguage.abnfproject_queryrulecolor(this._project);
	},
	UpdateFile : function(module_path, full_path) {
		lua.alanguage.abnfproject_updatefile(this._project, module_path, full_path, 0);
	},
	TempFile : function(module_path, full_path, text) {
		lua.alanguage.abnfproject_tempfile(this._project, module_path, full_path, text, 0);
	},
	RemoveFile : function(full_path) {
		lua.alanguage.abnfproject_removefile(this._project, full_path);
	},
	FindFile : function(text) {
		return new Promise((function(___COROUTINE, ___) {
			let query_id = this.Add(___COROUTINE);
			lua.alanguage.abnfproject_findfile(this._project, query_id, text);
			return;
		}).bind(this));
	},
	FindDefine : function(pre_input, input) {
		return new Promise((function(___COROUTINE, ___) {
			let query_id = this.Add(___COROUTINE);
			lua.alanguage.abnfproject_finddefine(this._project, query_id, pre_input, input);
			return;
		}).bind(this));
	},
	FindGoto : function(text) {
		return new Promise((function(___COROUTINE, ___) {
			let query_id = this.Add(___COROUTINE);
			lua.alanguage.abnfproject_findgoto(this._project, query_id, text);
			return;
		}).bind(this));
	},
	QueryCompleteIcon : function(tag) {
		return undefined;
	},
	Start : function() {
		if (this._loop !== undefined) {
			return;
		}
		this._loop = ALittle.NewObject(ALittle.LoopFrame, this.Update.bind(this));
		A_WeakLoopSystem.AddUpdater(this._loop);
	},
	Add : function(thread) {
		++ this._query_id;
		this._map.set(this._query_id, thread);
		return this._query_id;
	},
	OnTreeMenu : function(full_path, menu) {
	},
	OnTreeItemMenu : function(full_path, menu) {
	},
	Update : function(frame) {
		while (true) {
			let info = lua.alanguage.abnfproject_pollone(this._project);
			if (info === undefined) {
				break;
			}
			let thread = this._map.get(info.query_id);
			if (thread !== undefined) {
				this._map.delete(info.query_id);
				ALittle.Coroutine.Resume(thread, info.result);
			}
		}
	},
	Stop : function() {
		lua.alanguage.abnfproject_clear(this._project);
		if (this._loop === undefined) {
			return;
		}
		A_WeakLoopSystem.RemoveUpdater(this._loop);
		this._loop = undefined;
	},
}, "AUIPlugin.AUICodeProject");

}