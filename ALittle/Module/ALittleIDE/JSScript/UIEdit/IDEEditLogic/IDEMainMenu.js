{
if (typeof ALittleIDE === "undefined") ALittleIDE = {};

ALittle.RegStruct(1255897792, "ALittleIDE.IDEMainMenuImageInfo", {
name : "ALittleIDE.IDEMainMenuImageInfo", ns_name : "ALittleIDE", rl_name : "IDEMainMenuImageInfo", hash_code : 1255897792,
name_list : ["file_name","x","y","width","height"],
type_list : ["string","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(1020446174, "ALittleIDE.IDEMainMenuFramePlayInfo", {
name : "ALittleIDE.IDEMainMenuFramePlayInfo", ns_name : "ALittleIDE", rl_name : "IDEMainMenuFramePlayInfo", hash_code : 1020446174,
name_list : ["width","height","root_path","image_list","image_count"],
type_list : ["double","double","string","List<ALittleIDE.IDEMainMenuImageInfo>","int"],
option_map : {}
})

ALittleIDE.IDEMainMenu = JavaScript.Class(undefined, {
	ShowFileMenu : function(event) {
		if (this._menu_file_menu === undefined) {
			this._menu_file_menu = ALittleIDE.g_Control.CreateControl("ide_file_menu", this);
		}
		let [x, y] = event.target.LocalToGlobal();
		this._menu_file_menu.x = x;
		this._menu_file_menu.y = y + event.target.height;
		A_LayerManager.ShowFromRight(this._menu_file_menu);
	},
	HandleNewProject : function(event) {
		A_LayerManager.HideFromRight(this._menu_file_menu);
		ALittleIDE.g_IDEProjectManager.ShowNewProject();
	},
	HandleOpenProject : function(event) {
		A_LayerManager.HideFromRight(this._menu_file_menu);
		ALittleIDE.g_IDEProjectManager.ShowOpenProject();
	},
	HandleSettingProject : function(event) {
		A_LayerManager.HideFromRight(this._menu_file_menu);
		ALittleIDE.g_IDEProjectManager.ShowSettingProject(undefined);
	},
	HandleSaveProject : function(event) {
		A_LayerManager.HideFromRight(this._menu_file_menu);
		ALittleIDE.g_IDETabManager.SaveAllTab();
	},
	HandleRefreshProject : function(event) {
		A_LayerManager.HideFromRight(this._menu_file_menu);
		ALittleIDE.g_IDEProjectManager.RefreshProject();
	},
	HandleExportProject : function(event) {
		A_LayerManager.HideFromRight(this._menu_file_menu);
		ALittleIDE.g_IDEProjectManager.ShowExportProject();
	},
	HandleRun : function(event) {
		A_LayerManager.HideFromRight(this._menu_file_menu);
		ALittleIDE.g_IDEProjectManager.RunProject();
	},
	ShowEditMenu : function(event) {
		if (this._menu_edit_menu === undefined) {
			this._menu_edit_menu = ALittleIDE.g_Control.CreateControl("ide_edit_menu", this);
		}
		let [x, y] = event.target.LocalToGlobal();
		this._menu_edit_menu.x = x;
		this._menu_edit_menu.y = y + event.target.height;
		A_LayerManager.ShowFromRight(this._menu_edit_menu);
	},
	HandleNewControl : function(event) {
		A_LayerManager.HideFromRight(this._menu_edit_menu);
		ALittleIDE.g_IDEControlManager.ShowNewControl();
	},
	HandleUndoRevoke : function(event) {
		A_LayerManager.HideFromRight(this._menu_edit_menu);
		ALittleIDE.g_IDEUICenter.HandleUndoRevoke(undefined);
	},
	HandleDoRevoke : function(event) {
		A_LayerManager.HideFromRight(this._menu_edit_menu);
		ALittleIDE.g_IDEUICenter.HandleDoRevoke(undefined);
	},
	ShowToolMenu : function(event) {
		if (this._menu_tool_menu === undefined) {
			this._menu_tool_menu = ALittleIDE.g_Control.CreateControl("ide_tool_menu", this);
		}
		let [x, y] = event.target.LocalToGlobal();
		this._menu_tool_menu.x = x;
		this._menu_tool_menu.y = y + event.target.height;
		A_LayerManager.ShowFromRight(this._menu_tool_menu);
	},
	HandleGenJsonTemplateCodeClick : function(event) {
		A_LayerManager.HideFromRight(this._menu_tool_menu);
		if (this._gen_json_template_code_dialog === undefined) {
			this._gen_json_template_code_dialog = ALittleIDE.g_Control.CreateControl("ide_gen_json_template_code_dialog", this, ALittleIDE.g_IDECenter.dialog_layer);
		}
		this._gen_json_template_code_dialog.visible = true;
	},
	GenTemplate : function(num) {
		let code = "#define JSON_MACRO_" + ((num * 2 + 1)) + "(Name";
		for (let i = 0; i <= num - 1; i += 1) {
			code = code + ", t" + i + ", m" + i;
		}
		code = code + ") \\\n";
		code = code + "class Name : public ALittle::Json { \\\n";
		code = code + "public: \\\n";
		code = code + "\tvirtual const char* GetID() const { return #Name; } \\\n";
		code = code + "\tinline static const char* GetStaticID() { return #Name; } \\\n";
		code = code + "public: \\\n";
		code = code + "\tvirtual void Serialize(ALittle::JsonValue& v, ALittle::JsonAlloc& a) const { \\\n";
		for (let i = 0; i <= num - 1; i += 1) {
			code = code + "\t\tALittle::JsonTemplate::Json_Serialize(m" + i + ", #m" + i + ", (int)sizeof(#m" + i + ")-1, v, a); \\\n";
		}
		code = code + "\t} \\\n";
		code = code + "\tvirtual void Deserialize(const ALittle::JsonValue& v) { \\\n";
		for (let i = 0; i <= num - 1; i += 1) {
			code = code + "\t\tALittle::JsonTemplate::Json_Deserialize(m" + i + ", #m" + i + ", (int)sizeof(#m" + i + ")-1, v); \\\n";
		}
		code = code + "\t} \\\n";
		code = code + "\tvirtual void Serialize(ALittle::ValueMap& v) const { \\\n";
		for (let i = 0; i <= num - 1; i += 1) {
			code = code + "\t\tALittle::JsonTemplate::Json_SerializeValueMap(m" + i + ", #m" + i + ", v); \\\n";
		}
		code = code + "\t} \\\n";
		code = code + "\tvirtual void Deserialize(const ALittle::ValueMap& v) { \\\n";
		for (let i = 0; i <= num - 1; i += 1) {
			code = code + "\t\tALittle::JsonTemplate::Json_DeserializeValueMap(m" + i + ", #m" + i + ", v); \\\n";
		}
		code = code + "\t} \\\n";
		code = code + "\tvirtual const std::vector<std::string>& GetNameList() const { \\\n";
		code = code + "\t\tstatic std::vector<std::string> s_list; \\\n";
		code = code + "\t\tif (s_list.empty()) { \\\n";
		for (let i = 0; i <= num - 1; i += 1) {
			code = code + "\t\t\ts_list.push_back(#m" + i + "); \\\n";
		}
		code = code + "\t\t} return s_list; \\\n";
		code = code + "\t} \\\n";
		code = code + "\tvirtual const std::vector<std::string>& GetTypeList() const { \\\n";
		code = code + "\t\tstatic std::vector<std::string> s_list; \\\n";
		code = code + "\t\tif (s_list.empty()) { \\\n";
		for (let i = 0; i <= num - 1; i += 1) {
			code = code + "\t\t\ts_list.push_back(#t" + i + "); \\\n";
		}
		code = code + "\t\t} return s_list; \\\n";
		code = code + "\t} \\\n";
		code = code + "\tvirtual void Reset() { *this = Name(); } \\\n";
		code = code + "\tvirtual ~Name() { } \\\n";
		code = code + "\tName() : ";
		for (let i = 0; i <= num - 1; i += 1) {
			if (i > 0) {
				code = code + ", ";
			}
			code = code + "m" + i + "()";
		}
		code = code + " {} \\\n";
		code = code + "\t";
		for (let i = 0; i <= num - 1; i += 1) {
			if (i > 0) {
				code = code + " ";
			}
			code = code + "t" + i + " m" + i + ";";
		}
		code = code + " \\\n";
		code = code + "}\n";
		return code;
	},
	HandleGenJsonTemplateCode : function(event) {
		let template_count = ALittle.Math_ToInt(this._json_template_count.text);
		if (template_count === undefined) {
			template_count = 20;
		}
		let file_count = ALittle.Math_ToInt(this._json_template_file_count.text);
		if (file_count === undefined) {
			file_count = 0;
		}
		let num = 1;
		for (let file_index = 1; file_index <= file_count; file_index += 1) {
			let code_head = "\n#ifndef _ALITTLE_JSON_" + file_index + "_H_\n#define _ALITTLE_JSON_" + file_index + "_H_\n\n";
			code_head = code_head + "#include \"Json.h\"\n\n";
			let code_foot = "\n#endif // _ALITTLE_JSON_" + file_index + "_H_\n";
			let code_list = [];
			let index = 1;
			code_list[index - 1] = code_head;
			for (let template_index = 1; template_index <= template_count; template_index += 1) {
				++ index;
				code_list[index - 1] = ALittleIDE.IDEMainMenu.GenTemplate(num);
				++ num;
			}
			++ index;
			code_list[index - 1] = code_foot;
			let content = ALittle.String_Join(code_list, "");
			ALittle.File_WriteTextToFile(content, "Json_" + file_index + ".h");
		}
		let code = "\n#ifndef _ALITTLE_JSON_ALL_H_\n#define _ALITTLE_JSON_ALL_H_\n\n";
		for (let file_index = 1; file_index <= file_count; file_index += 1) {
			code = code + "#include \"Json_" + file_index + ".h\"\n";
		}
		let max_count = file_count * template_count * 2 + 1;
		code = code + "\n#define VA_JSON_EXPAND(...) __VA_ARGS__\n";
		code = code + "#define VA_JSON_FILTER_(";
		for (let i = 1; i <= max_count; i += 1) {
			if (i > 1) {
				code = code + ",";
			}
			code = code + "_" + i;
		}
		code = code + ",_N,...) _N\n";
		code = code + "#define VA_JSON_NUMBER_() ";
		for (let i = max_count; i >= 1; i += -1) {
			if (i < max_count) {
				code = code + ",";
			}
			code = code + i;
		}
		code = code + "\n";
		code = code + "#define VA_JSON_HELPER(...) VA_JSON_EXPAND(VA_JSON_FILTER_(__VA_ARGS__))\n";
		code = code + "#define VA_JSON_COUNT(...) VA_JSON_HELPER(__VA_ARGS__, VA_JSON_NUMBER_())\n";
		code = code + "#define VA_JSON_CAT(X, Y) X##Y\n";
		code = code + "#define VA_JSON_JOIN(X, Y) VA_JSON_CAT(X, Y)\n";
		code = code + "#define VA_JSON_PROXY(F, ...) VA_JSON_EXPAND(F(__VA_ARGS__))\n";
		code = code + "\n#define JSON_MACRO(...) VA_JSON_PROXY(VA_JSON_JOIN(JSON_MACRO_, VA_JSON_COUNT(__VA_ARGS__)), __VA_ARGS__)\n";
		code = code + "\ntypedef JSON_MACRO(EmptyJson) EmptyJson;\ntypedef JSON_MACRO(ResultJson, bool, result, std::string, reason) ResultJson;\n";
		code = code + "\n#endif // _ALITTLE_JSON_ALL_H_\n";
		ALittle.File_WriteTextToFile(code, "Json_ALL.h");
		ALittleIDE.g_IDETool.ShowNotice("提示", "生成成功");
	},
	HandleGenServerModuleCodeClick : function(event) {
		A_LayerManager.HideFromRight(this._menu_tool_menu);
		if (this._gen_server_module_code_dialog === undefined) {
			this._gen_server_module_code_dialog = ALittleIDE.g_Control.CreateControl("ide_gen_server_module_code_dialog", this, ALittleIDE.g_IDECenter.dialog_layer);
		}
		this._gen_server_module_code_dialog.visible = true;
	},
	HandleGenServerModuleCode : function(event) {
		let module_name = this._server_module_code_name.text;
		let base_path = ALittleIDE.g_ModuleBasePathEx + "/ServerModuleCode/" + module_name;
		ALittle.File_MakeDeepDir(base_path);
		let file_map = ALittle.File_GetFileAttrByDir(ALittleIDE.g_ModuleBasePath + "/Other/ServerTemplate");
		let ___OBJECT_1 = file_map;
		for (let file_path in ___OBJECT_1) {
			let attr = ___OBJECT_1[file_path];
			if (attr === undefined) continue;
			let file_name = ALittle.File_GetFileNameByPath(file_path);
			file_name = ALittle.String_Replace(file_name, "abcd@module_name@abcd", module_name);
			file_name = ALittle.String_Replace(file_name, "abcd@upper_module_name@abcd", ALittle.String_Upper(module_name));
			file_name = ALittle.String_Replace(file_name, "abcd@lower_module_name@abcd", ALittle.String_Lower(module_name));
			let content = ALittle.File_ReadTextFromFile(file_path);
			if (content !== undefined) {
				content = ALittle.String_Replace(content, "abcd@module_name@abcd", module_name);
				content = ALittle.String_Replace(content, "abcd@upper_module_name@abcd", ALittle.String_Upper(module_name));
				content = ALittle.String_Replace(content, "abcd@lower_module_name@abcd", ALittle.String_Lower(module_name));
				let full_path = base_path + "/" + file_name;
				ALittle.File_WriteTextToFile(content, full_path);
			}
		}
		ALittleIDE.g_IDETool.ShowNotice("提示", "生成成功");
	},
	HandleFramePlayFromPList : function(event) {
		A_LayerManager.HideFromRight(this._menu_tool_menu);
		if (this._frameplay_plist_dialog === undefined) {
			this._frameplay_plist_dialog = ALittleIDE.g_Control.CreateControl("ide_frameplay_plist_dialog", this, ALittleIDE.g_IDECenter.dialog_layer);
		}
		this._frameplay_plist_dialog.visible = true;
	},
	ImageListInFramePlayCmp : function(a, b) {
		return a.file_name < a.file_name;
	},
	HandleViewLog : function(event) {
		A_LayerManager.HideFromRight(this._menu_tool_menu);
		if (this._view_log_dialog === undefined) {
			this._view_log_dialog = ALittleIDE.g_Control.CreateControl("ide_view_log_dialog", this, ALittleIDE.g_IDECenter.dialog_layer);
			this.HandleViewLogRefresh(undefined);
		}
		this._view_log_dialog.visible = true;
	},
	HandleViewLogRefresh : function(event) {
		let file_name = ALittle.Time_GetCurYMD(ALittle.Time_GetCurTime()) + ".log";
		let file_path = ALittle.File_BaseFilePath() + "Log/" + file_name;
		let content = ALittle.File_ReadTextFromFile(file_path, false);
		if (content === undefined) {
			return;
		}
		let content_list = ALittle.String_Split(content, "\n");
		let content_len = ALittle.List_MaxN(content_list);
		let copy_len = content_len - 100;
		if (copy_len < 1) {
			copy_len = 1;
		}
		let log_list = [];
		let log_list_count = 0;
		for (let i = content_len; i >= copy_len; i += -1) {
			++ log_list_count;
			log_list[log_list_count - 1] = content_list[i - 1];
		}
		this._view_log_content.text = ALittle.String_Join(log_list, "\n");
	},
	HandleViewLogClose : function(event) {
		this._view_log_dialog.visible = false;
	},
}, "ALittleIDE.IDEMainMenu");

ALittleIDE.g_IDEMainMenu = ALittle.NewObject(ALittleIDE.IDEMainMenu);
}