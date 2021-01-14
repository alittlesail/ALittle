{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};


if (AUIPlugin.AUICodeLanguage === undefined) throw new Error(" extends class:AUIPlugin.AUICodeLanguage is undefined");
AUIPlugin.AUICodeCommon = JavaScript.Class(AUIPlugin.AUICodeLanguage, {
	Ctor : function(project, full_path) {
		if (this._project === undefined) {
			this._project = AUIPlugin.AUICodeProject.CreateCommonProject(ALittle.File_GetFileExtByPathAndUpper(full_path));
		}
		this._abnf_color = this._project.QueryRuleColor();
		this._abnf_file = lua.alanguage.create_abnffile(this._project.project, full_path, "");
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
		return this._abnf_color.get(tag);
	},
	OnRightMenu : function(menu) {
	},
}, "AUIPlugin.AUICodeCommon");

if (AUIPlugin.AUICodeProject === undefined) throw new Error(" extends class:AUIPlugin.AUICodeProject is undefined");
AUIPlugin.AUICodeCommonProject = JavaScript.Class(AUIPlugin.AUICodeProject, {
	Ctor : function(project, upper_ext) {
		this._upper_ext = upper_ext;
	},
	get upper_ext() {
		return this._upper_ext;
	},
	OnTreeMenu : function(full_path, menu) {
	},
	OnTreeItemMenu : function(full_path, menu) {
	},
}, "AUIPlugin.AUICodeCommonProject");

}