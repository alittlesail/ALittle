{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};

ALittle.RegStruct(152169657, "AUIPlugin.ABnfColor", {
name : "AUIPlugin.ABnfColor", ns_name : "AUIPlugin", rl_name : "ABnfColor", hash_code : 152169657,
name_list : ["red","green","blue"],
type_list : ["double","double","double"],
option_map : {}
})

AUIPlugin.AUICodeLanguage = JavaScript.Class(undefined, {
	Ctor : function(project, full_path) {
		this._version = 1;
		this._project = project;
		this._full_path = full_path;
		this._auto_pair = {};
		this._auto_pair["{"] = "}";
		this._auto_pair["["] = "]";
		this._auto_pair["("] = ")";
		this._auto_pair["<"] = ">";
		this._auto_pair["\""] = "\"";
		this._auto_pair["'"] = "'";
	},
	get version() {
		return this._version;
	},
	OnOpen : function(content) {
	},
	OnClose : function() {
	},
	OnShow : function() {
	},
	OnHide : function() {
	},
	OnSave : function() {
	},
	OnTabRightMenu : function(menu) {
	},
	SetText : function(content) {
		this._version = this._version + (1);
		lua.alanguage.abnffile_settext(this._abnf_file, this._version, content);
	},
	InsertText : function(content, it_line, it_char) {
		this._version = this._version + (1);
		lua.alanguage.abnffile_inserttext(this._abnf_file, this._version, content, it_line, it_char);
	},
	DeleteText : function(it_line_start, it_char_start, it_line_end, it_char_end) {
		this._version = this._version + (1);
		lua.alanguage.abnffile_deletetext(this._abnf_file, this._version, it_line_start, it_char_start, it_line_end, it_char_end);
	},
	QueryColor : function(line) {
		return new Promise((function(___COROUTINE, ___) {
			let query_id = this._project.Add(___COROUTINE);
			lua.alanguage.abnffile_querycolor(this._abnf_file, query_id, this._version, line);
			return;
		}).bind(this));
	},
	QueryInfo : function(line, char) {
		return new Promise((function(___COROUTINE, ___) {
			let query_id = this._project.Add(___COROUTINE);
			lua.alanguage.abnffile_queryinfo(this._abnf_file, query_id, this._version, line, char);
			return;
		}).bind(this));
	},
	QueryGoto : function(line, char) {
		return new Promise((function(___COROUTINE, ___) {
			let query_id = this._project.Add(___COROUTINE);
			lua.alanguage.abnffile_querygoto(this._abnf_file, query_id, this._version, line, char);
			return;
		}).bind(this));
	},
	QueryComplete : function(line, char) {
		return new Promise((function(___COROUTINE, ___) {
			let query_id = this._project.Add(___COROUTINE);
			lua.alanguage.abnffile_querycomplete(this._abnf_file, query_id, this._version, line, char);
			return;
		}).bind(this));
	},
	QueryParamList : function(line, char) {
		return new Promise((function(___COROUTINE, ___) {
			let query_id = this._project.Add(___COROUTINE);
			lua.alanguage.abnffile_queryparamlist(this._abnf_file, query_id, this._version, line, char);
			return;
		}).bind(this));
	},
	QueryParamIndex : function(line, char) {
		return [lua.alanguage.abnffile_queryparamindex(this._abnf_file, this._version, line, char)];
	},
	QueryError : function(force) {
		return new Promise((function(___COROUTINE, ___) {
			let query_id = this._project.Add(___COROUTINE);
			lua.alanguage.abnffile_queryerror(this._abnf_file, query_id, this._version, force);
			return;
		}).bind(this));
	},
	QueryDesiredIndent : function(line, char) {
		return lua.alanguage.abnffile_querydesiredindent(this._abnf_file, this._version, line, char);
	},
	QueryFormateIndent : function(line, char) {
		return lua.alanguage.abnffile_queryformateindent(this._abnf_file, this._version, line, char);
	},
	QueryAutoPair : function(line, char, input) {
		let right = this._auto_pair[input];
		if (right === undefined) {
			return undefined;
		}
		if (!lua.alanguage.abnffile_queryautopair(this._abnf_file, this._version, line, char, input, right)) {
			return undefined;
		}
		return right;
	},
	QueryAutoFormat : function(input) {
		return false;
	},
	NeedAutoFormat : function() {
		return false;
	},
	QueryColorValue : function(tag) {
		return undefined;
	},
	QueryCompleteIcon : function(tag) {
		return undefined;
	},
}, "AUIPlugin.AUICodeLanguage");

}