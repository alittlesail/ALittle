{
if (typeof ALittleIDE === "undefined") window.ALittleIDE = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-1898137181, "AUIPlugin.AUICodeEditJumpEvent", {
name : "AUIPlugin.AUICodeEditJumpEvent", ns_name : "AUIPlugin", rl_name : "AUICodeEditJumpEvent", hash_code : -1898137181,
name_list : ["target","file_path","it_line","it_char"],
type_list : ["ALittle.DisplayObject","string","int","int"],
option_map : {}
})
ALittle.RegStruct(1575183661, "AUIPlugin.AUICodeEditBreakPointEvent", {
name : "AUIPlugin.AUICodeEditBreakPointEvent", ns_name : "AUIPlugin", rl_name : "AUICodeEditBreakPointEvent", hash_code : 1575183661,
name_list : ["target","add_or_remove","file_path","file_line"],
type_list : ["ALittle.DisplayObject","bool","string","int"],
option_map : {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name : "ALittle.UIChangedEvent", ns_name : "ALittle", rl_name : "UIChangedEvent", hash_code : 958494922,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(631224630, "AUIPlugin.AUICodeEditGotoEvent", {
name : "AUIPlugin.AUICodeEditGotoEvent", ns_name : "AUIPlugin", rl_name : "AUICodeEditGotoEvent", hash_code : 631224630,
name_list : ["target","file_path","line_start","char_start","line_end","char_end"],
type_list : ["ALittle.DisplayObject","string","int","int","int","int"],
option_map : {}
})

if (ALittleIDE.IDETabChild === undefined) throw new Error(" extends class:ALittleIDE.IDETabChild is undefined");
ALittleIDE.IDECodeTabChild = JavaScript.Class(ALittleIDE.IDETabChild, {
	Ctor : function(ctrl_sys, module, name, save, user_info) {
		this._user_info = user_info;
		this._edit = ALittleIDE.g_AUIPluinControl.CreateControl("code_tab_screen", this);
		this._edit.AddEventListener(___all_struct.get(958494922), this, this.HandleChangedEvent);
		this._edit.AddEventListener(___all_struct.get(631224630), this, this.HandleEditGotoEvent);
		this._edit.AddEventListener(___all_struct.get(-1898137181), this, this.HandleJumpCodeEvent);
		this._edit.AddEventListener(___all_struct.get(1575183661), this, this.HandleBreakPointEvent);
		this._edit._user_data = this;
	},
	OnUndo : function() {
		this._edit.OnUnDo();
	},
	OnRedo : function() {
	},
	OnHide : function() {
		this._edit.OnHide();
		ALittleIDE.g_IDECenter.center.tool_code.visible = false;
	},
	OnShow : function() {
		this._edit.OnShow();
		ALittleIDE.g_IDECenter.center.tool_code.visible = true;
	},
	OnClose : function() {
		this._edit.OnClose();
	},
	OnOpen : function() {
		this._revoke_list = ALittle.NewObject(ALittle.RevokeList, 10000);
		this._edit.Load(this._user_info.path, undefined, this._revoke_list, this._language, ALittleIDE.g_IDEProject.GetBreakPoint(this._user_info.path));
	},
	OnTabRightMenu : function(menu) {
		this._edit.OnTabRightMenu(menu);
		menu.AddItem("获取焦点", this.ShowControlFocus.bind(this));
	},
	ShowControlFocus : function() {
		let tree = ALittleIDE.g_IDECenter.center.code_list.GetCodeTree(this._user_info.path);
		if (tree === undefined) {
			return;
		}
		ALittleIDE.g_IDECenter.center.project_edit_tab.tab = ALittleIDE.g_IDECenter.center.code_list;
		ALittleIDE.g_IDECenter.center.code_list.ShowTreeItemFocus(tree);
	},
	HandleEditGotoEvent : function(event) {
		let info = {};
		info.file_path = event.file_path;
		info.it_line = event.line_start;
		info.it_char = event.char_start;
		ALittleIDE.g_IDECenter.center.code_list.AddCodeJump(info);
		ALittleIDE.g_IDECenter.center.code_list.OpenByFullPath(event.file_path, event.line_start, event.char_start, event.line_end, event.char_end);
	},
	HandleJumpCodeEvent : function(event) {
		let info = {};
		info.file_path = event.file_path;
		info.it_line = event.it_line;
		info.it_char = event.it_char;
		ALittleIDE.g_IDECenter.center.code_list.AddCodeJump(info);
	},
	HandleBreakPointEvent : function(event) {
		if (event.add_or_remove) {
			ALittleIDE.g_IDEProject.AddBreakPoint(event.file_path, event.file_line);
		} else {
			ALittleIDE.g_IDEProject.RemoveBreakPoint(event.file_path, event.file_line);
		}
	},
	HandleChangedEvent : function(event) {
		this.save = false;
	},
	get tab_body() {
		return this._edit;
	},
	set save(value) {
		if (this._save === value) {
			return;
		}
		if (value === false) {
			this._save = false;
			this.UpdateTitle();
			return;
		}
		this._edit.Save();
		this._save = value;
		this.UpdateTitle();
	},
	get id() {
		return this._user_info.path;
	},
	Rename : function(name) {
		this._name = name;
		this.UpdateTitle();
	},
	UpdateTitle : function() {
		let text = this._name;
		if (this._save === false) {
			text = text + " *";
		}
		ALittleIDE.g_IDECenter.center.content_edit.main_tab.SetChildText(this._edit, text);
	},
	get title() {
		return this._name;
	},
	UpdateUserInfo : function(info) {
		this.OnClose();
		this._language = undefined;
		this._user_info = info;
		this.OnOpen();
	},
	CreateBySelect : function(info) {
		this._user_info = info;
		this._edit.EditFocus(0, 0, undefined, undefined, true);
	},
	JumpFocus : function(line_start, char_start, line_end, char_end) {
		this._edit.EditFocus(line_start, char_start, line_end, char_end, true);
	},
	FindText : function(text) {
		this._edit.FindNext(text);
	},
	get edit() {
		return this._edit;
	},
}, "ALittleIDE.IDECodeTabChild");

}