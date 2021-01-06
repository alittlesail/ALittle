{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})

let g_ALittleScriptColor = undefined;
AUIPlugin.ALittleScriptColorType = {
	COMMENT : 1,
	DEFINE_NAME : 2,
	VAR_NAME : 3,
	CUSTOM_NAME : 4,
	CTRL_KEYWORD : 5,
	KEYWORD : 6,
	METHOD_NAME : 7,
	DEFAULT : 8,
	TEXT : 9,
}

AUIPlugin.ALittleScriptIconType = {
	CLASS : 1,
	STRUCT : 2,
	PROPERTY : 3,
	NAMESPACE : 4,
	TEMPLATE : 5,
	ENUM : 6,
	LANGUAGE : 7,
	GLOBAL_METHOD : 8,
	MEMBER_METHOD : 9,
	FIELD_METHOD : 10,
	STATIC_METHOD : 11,
	INSTANCE : 12,
	PARAM : 13,
	VARIABLE : 14,
}

let g_ALittleScriptIcon = new Map();
g_ALittleScriptIcon.set(1, "ABnf/ALittleScript/ALittleScriptClassIcon.png");
g_ALittleScriptIcon.set(2, "ABnf/ALittleScript/ALittleScriptStructIcon.png");
g_ALittleScriptIcon.set(3, "ABnf/ALittleScript/ALittleScriptPropertyIcon.png");
g_ALittleScriptIcon.set(4, "ABnf/ALittleScript/ALittleScriptNamespaceIcon.png");
g_ALittleScriptIcon.set(5, "ABnf/ALittleScript/ALittleScriptTemplateIcon.png");
g_ALittleScriptIcon.set(6, "ABnf/ALittleScript/ALittleScriptEnumIcon.png");
g_ALittleScriptIcon.set(7, "ABnf/ALittleScript/ALittleScriptNamespaceIcon.png");
g_ALittleScriptIcon.set(8, "ABnf/ALittleScript/ALittleScriptStaticIcon.png");
g_ALittleScriptIcon.set(9, "ABnf/ALittleScript/ALittleScriptMethodIcon.png");
g_ALittleScriptIcon.set(10, "ABnf/ALittleScript/ALittleScriptFieldIcon.png");
g_ALittleScriptIcon.set(11, "ABnf/ALittleScript/ALittleScriptStaticIcon.png");
g_ALittleScriptIcon.set(12, "ABnf/ALittleScript/ALittleScriptInstanceIcon.png");
g_ALittleScriptIcon.set(13, "ABnf/ALittleScript/ALittleScriptParamIcon.png");
g_ALittleScriptIcon.set(14, "ABnf/ALittleScript/ALittleScriptVariableIcon.png");
if (AUIPlugin.AUICodeLanguage === undefined) throw new Error(" extends class:AUIPlugin.AUICodeLanguage is undefined");
AUIPlugin.AUICodeALittleScript = JavaScript.Class(AUIPlugin.AUICodeLanguage, {
	Ctor : function(project, full_path, module_path) {
		if (g_ALittleScriptColor === undefined) {
			g_ALittleScriptColor = new Map();
			let color = undefined;
			{
				color = {};
				color.red = 87 / 255;
				color.green = 166 / 255;
				color.blue = 74 / 255;
				g_ALittleScriptColor.set(1, color);
			}
			{
				color = {};
				color.red = 78 / 255;
				color.green = 201 / 255;
				color.blue = 176 / 255;
				g_ALittleScriptColor.set(2, color);
			}
			{
				color = {};
				color.red = 218 / 255;
				color.green = 218 / 255;
				color.blue = 218 / 255;
				g_ALittleScriptColor.set(3, color);
			}
			{
				color = {};
				color.red = 146 / 255;
				color.green = 210 / 255;
				color.blue = 244 / 255;
				g_ALittleScriptColor.set(4, color);
			}
			{
				color = {};
				color.red = 216 / 255;
				color.green = 160 / 255;
				color.blue = 223 / 255;
				g_ALittleScriptColor.set(5, color);
			}
			{
				color = {};
				color.red = 86 / 255;
				color.green = 156 / 255;
				color.blue = 214 / 255;
				g_ALittleScriptColor.set(6, color);
			}
			{
				color = {};
				color.red = 210 / 255;
				color.green = 210 / 255;
				color.blue = 160 / 255;
				g_ALittleScriptColor.set(7, color);
			}
			{
				color = {};
				color.red = 169 / 255;
				color.green = 183 / 255;
				color.blue = 198 / 255;
				g_ALittleScriptColor.set(8, color);
			}
			{
				color = {};
				color.red = 214 / 255;
				color.green = 157 / 255;
				color.blue = 133 / 255;
				g_ALittleScriptColor.set(9, color);
			}
		}
		this._abnf_file = lua.alittlescript.create_alittlescript_file(project.project, module_path, full_path, "");
	},
	OnRightMenu : function(menu) {
		menu.AddItem("生成", this.GenerateLanguage.bind(this, true));
	},
	OnSave : function() {
		this.GenerateLanguage(false);
	},
	GenerateLanguage : async function(notice) {
		let error = await this.Generate(this._full_path);
		if (error !== undefined) {
			if (notice) {
				g_AUITool.ShowNotice("错误", error.error + " 文件路径" + error.full_path);
			}
			return;
		}
		if (notice) {
			g_AUITool.ShowNotice("提示", "生成成功");
		}
	},
	QueryColorValue : function(tag) {
		return g_ALittleScriptColor.get(tag);
	},
	QueryAutoFormat : function(input) {
		return input === ";" || input === "}";
	},
	NeedAutoFormat : function() {
		return true;
	},
	SetTargetLanguage : function(target_languaeg) {
		lua.alittlescript.alittlescriptproject_settargetlanguage(this._project.project, target_languaeg);
	},
	Generate : function(full_path) {
		return new Promise((function(___COROUTINE, ___) {
			let query_id = this._project.Add(___COROUTINE);
			lua.alittlescript.alittlescriptproject_generate(this._project.project, query_id, full_path);
			return;
		}).bind(this));
	},
	QueryCompleteIcon : function(tag) {
		return g_ALittleScriptIcon.get(tag);
	},
}, "AUIPlugin.AUICodeALittleScript");

if (AUIPlugin.AUICodeProject === undefined) throw new Error(" extends class:AUIPlugin.AUICodeProject is undefined");
AUIPlugin.AUICodeALittleScriptProject = JavaScript.Class(AUIPlugin.AUICodeProject, {
	get upper_ext() {
		return "ALITTLE";
	},
	OnTreeMenu : function(full_path, menu) {
		menu.AddItem("生成目标代码", this.GenerateDir.bind(this, full_path));
	},
	OnTreeItemMenu : function(full_path, menu) {
		menu.AddItem("生成目标代码", this.GenerateFile.bind(this, full_path));
		menu.AddItem("打开Lua代码", this.OpenTargetLuaFile.bind(this, full_path));
		menu.AddItem("打开JavaScript代码", this.OpenTargetJavaScriptFile.bind(this, full_path));
		menu.AddItem("打开Lua字节码", this.OpenTargetLuaByteCode.bind(this, full_path));
	},
	GenerateDir : async function(full_path) {
		let index = ALittle.String_Find(full_path, "/src");
		if (index === undefined) {
			g_AUITool.ShowNotice("提示", "当前不是/src的子目录");
			return;
		}
		let pre = "";
		if (lua.alittlescript.alittlescriptproject_gettargetlanguage(this._project) === "JavaScript") {
			pre = "JS";
		}
		let new_path = ALittle.String_Sub(full_path, 1, index) + pre + "Script" + (ALittle.String_Sub(full_path, index + 4));
		ALittle.File_DeleteDeepDir(new_path);
		ALittle.File_MakeDeepDir(new_path);
		let file_map = ALittle.File_GetFileAttrByDir(full_path);
		let ___OBJECT_1 = file_map;
		for (let file_path in ___OBJECT_1) {
			let attr = ___OBJECT_1[file_path];
			if (attr === undefined) continue;
			let error = await this.Generate(file_path);
			if (error !== undefined) {
				if ("YES" === await g_AUITool.DeleteNotice("错误", error.error + "\n 文件路径" + file_path + "\n是否打开该文件?")) {
					let goto_event = {};
					goto_event.file_path = error.full_path;
					if (goto_event.file_path === undefined) {
						goto_event.file_path = file_path;
					}
					goto_event.line_start = error.line_start;
					goto_event.char_start = error.char_start;
					goto_event.line_end = error.line_end;
					goto_event.char_end = error.char_end;
					this.DispatchEvent(___all_struct.get(2057209532), goto_event);
				}
				return;
			}
		}
		g_AUITool.ShowNotice("提示", "生成成功");
	},
	GenerateFile : async function(full_path) {
		let error = await this.Generate(full_path);
		if (error !== undefined) {
			g_AUITool.ShowNotice("错误", error.error + " 文件路径" + error.full_path);
			return;
		}
		g_AUITool.ShowNotice("提示", "生成成功");
	},
	OpenTargetLuaFile : function(full_path) {
		full_path = ALittle.File_ChangeFileExtByPath(full_path, "lua");
		let index = ALittle.String_Find(full_path, "/src/");
		if (index === undefined) {
			return;
		}
		let new_path = ALittle.String_Sub(full_path, 1, index) + "Script/" + (ALittle.String_Sub(full_path, index + 5));
		let event = {};
		event.file_path = new_path;
		this.DispatchEvent(___all_struct.get(2057209532), event);
	},
	OpenTargetLuaByteCode : function(full_path) {
		full_path = ALittle.File_ChangeFileExtByPath(full_path, "lua");
		let index = ALittle.String_Find(full_path, "/src/");
		if (index === undefined) {
			return;
		}
		let new_path = ALittle.String_Sub(full_path, 1, index) + "Script/" + (ALittle.String_Sub(full_path, index + 5));
		let out_path = ALittle.String_Sub(full_path, 1, index) + "ByteCode/" + (ALittle.String_Sub(full_path, index + 5));
		let out_dir = ALittle.File_GetFilePathByPath(out_path);
		ALittle.File_MakeDeepDir(out_dir);
		out_path = ALittle.File_ChangeFileExtByPath(out_path, "txt");
		let decompile = ALittle.NewObject(carp.CarpLuaDecompile);
		decompile.Decompile(new_path, out_path);
		let event = {};
		event.file_path = out_path;
		this.DispatchEvent(___all_struct.get(2057209532), event);
	},
	OpenTargetJavaScriptFile : function(full_path) {
		full_path = ALittle.File_ChangeFileExtByPath(full_path, "js");
		let index = ALittle.String_Find(full_path, "/src/");
		if (index === undefined) {
			return;
		}
		let new_path = ALittle.String_Sub(full_path, 1, index) + "JSScript/" + (ALittle.String_Sub(full_path, index + 5));
		let event = {};
		event.file_path = new_path;
		this.DispatchEvent(___all_struct.get(2057209532), event);
	},
	Generate : function(full_path) {
		return new Promise((function(___COROUTINE, ___) {
			let query_id = this.Add(___COROUTINE);
			lua.alittlescript.alittlescriptproject_generate(this._project, query_id, full_path);
			return;
		}).bind(this));
	},
	QueryCompleteIcon : function(tag) {
		return g_ALittleScriptIcon.get(tag);
	},
}, "AUIPlugin.AUICodeALittleScriptProject");

}