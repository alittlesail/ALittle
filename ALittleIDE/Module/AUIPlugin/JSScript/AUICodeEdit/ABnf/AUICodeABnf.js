{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};


let g_ABnfColor = undefined;
AUIPlugin.ABnfColorType = {
	ABnfKeyWord : 1,
	ABnfId : 2,
	ABnfComment : 3,
	ABnfKey : 4,
	ABnfString : 5,
	ABnfRegex : 6,
	ABnfNodeTail : 7,
	ABnfNumber : 8,
}

if (AUIPlugin.AUICodeLanguage === undefined) throw new Error(" extends class:AUIPlugin.AUICodeLanguage is undefined");
AUIPlugin.AUICodeABnf = JavaScript.Class(AUIPlugin.AUICodeLanguage, {
	Ctor : function(project, full_path) {
		if (this._project === undefined) {
			this._project = AUIPlugin.AUICodeProject.CreateABnfProject();
		}
		if (g_ABnfColor === undefined) {
			g_ABnfColor = new Map();
			let color = undefined;
			{
				color = {};
				color.red = 255 / 255;
				color.green = 198 / 255;
				color.blue = 109 / 255;
				g_ABnfColor.set(1, color);
			}
			{
				color = {};
				color.red = 204 / 255;
				color.green = 120 / 255;
				color.blue = 50 / 255;
				g_ABnfColor.set(2, color);
			}
			{
				color = {};
				color.red = 128 / 255;
				color.green = 128 / 255;
				color.blue = 128 / 255;
				g_ABnfColor.set(3, color);
			}
			{
				color = {};
				color.red = 53 / 255;
				color.green = 155 / 255;
				color.blue = 185 / 255;
				g_ABnfColor.set(4, color);
			}
			{
				color = {};
				color.red = 85 / 255;
				color.green = 134 / 255;
				color.blue = 74 / 255;
				g_ABnfColor.set(5, color);
			}
			{
				color = {};
				color.red = 152 / 255;
				color.green = 118 / 255;
				color.blue = 170 / 255;
				g_ABnfColor.set(6, color);
			}
			{
				color = {};
				color.red = 152 / 255;
				color.green = 118 / 255;
				color.blue = 170 / 255;
				g_ABnfColor.set(8, color);
			}
		}
		this._abnf_file = lua.abnf.create_abnf_file(this._project.project, full_path, "");
	},
	OnOpen : function(content) {
		if (content !== undefined) {
			this._project.TempFile("", this._full_path, content);
		} else {
			this._project.UpdateFile("", this._full_path);
		}
	},
	OnShow : function() {
	},
	OnHide : function() {
	},
	OnClose : function() {
		this._project.RemoveFile(this._full_path);
	},
	QueryColorValue : function(tag) {
		return g_ABnfColor.get(tag);
	},
	OnRightMenu : function(menu) {
		menu.AddItem("生成", this.GenerateABnf.bind(this));
	},
	OnTabRightMenu : function(menu) {
		menu.AddItem("生成", this.GenerateABnf.bind(this));
	},
	GenerateABnf : async function() {
		let file_name = ALittle.File_GetJustFileNameByPath(this._full_path);
		let path = await g_AUITool.ShowSelectDir("选择生成的文件夹", this._generate_dir);
		if (path === undefined) {
			return;
		}
		let attr = ALittle.File_GetFileAttr(path);
		if (attr === undefined || attr.directory !== true) {
			g_AUITool.ShowNotice("错误", "文件夹不存在");
			return;
		}
		this._generate_dir = path;
		ALittle.File_DeleteDeepDir(path + "/Generate");
		ALittle.File_MakeDeepDir(path + "/Generate");
		let error = await this.Generate(path + "/Generate", file_name);
		if (error !== undefined) {
			g_AUITool.ShowNotice("错误", error);
			return;
		}
		g_AUITool.ShowNotice("提示", "生成成功");
	},
	Generate : function(target_path, language_name) {
		return new Promise((function(___COROUTINE, ___) {
			let query_id = this._project.Add(___COROUTINE);
			lua.abnf.abnffile_generate(this._abnf_file, query_id, this._version, target_path, language_name);
			return;
		}).bind(this));
	},
}, "AUIPlugin.AUICodeABnf");

if (AUIPlugin.AUICodeProject === undefined) throw new Error(" extends class:AUIPlugin.AUICodeProject is undefined");
AUIPlugin.AUICodeABnfProject = JavaScript.Class(AUIPlugin.AUICodeProject, {
	get upper_ext() {
		return "ABNF";
	},
	OnTreeMenu : function(full_path, menu) {
	},
	OnTreeItemMenu : function(full_path, menu) {
	},
}, "AUIPlugin.AUICodeABnfProject");

}