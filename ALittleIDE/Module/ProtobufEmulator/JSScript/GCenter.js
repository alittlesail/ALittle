{
if (typeof Emulator === "undefined") window.Emulator = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1835920059, "lua.protobuf_reflection", {
name : "lua.protobuf_reflection", ns_name : "lua", rl_name : "protobuf_reflection", hash_code : 1835920059,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(1628431371, "Lua.lua_socket_schedule_message_info", {
name : "Lua.lua_socket_schedule_message_info", ns_name : "Lua", rl_name : "lua_socket_schedule_message_info", hash_code : 1628431371,
name_list : ["descriptor","full_name","name"],
type_list : ["lua.protobuf_descriptor","string","string"],
option_map : {}
})
ALittle.RegStruct(1618605759, "Emulator.DetailInfo", {
name : "Emulator.DetailInfo", ns_name : "Emulator", rl_name : "DetailInfo", hash_code : 1618605759,
name_list : ["tree","message","reflection","info"],
type_list : ["Emulator.IDETreeLogic","lua.protobuf_message","lua.protobuf_reflection","Lua.lua_socket_schedule_message_info"],
option_map : {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name : "ALittle.UIButtonEvent", ns_name : "ALittle", rl_name : "UIButtonEvent", hash_code : -1347278145,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name : "ALittle.UIChangedEvent", ns_name : "ALittle", rl_name : "UIChangedEvent", hash_code : 958494922,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-888044440, "Emulator.LogItemUserData", {
name : "Emulator.LogItemUserData", ns_name : "Emulator", rl_name : "LogItemUserData", hash_code : -888044440,
name_list : ["msg","info","upper_name","json_content"],
type_list : ["lua.protobuf_message","Lua.lua_socket_schedule_message_info","string","string"],
option_map : {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name : "ALittle.UIRButtonDownEvent", ns_name : "ALittle", rl_name : "UIRButtonDownEvent", hash_code : -641444818,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(-628015380, "lua.protobuf_message", {
name : "lua.protobuf_message", ns_name : "lua", rl_name : "protobuf_message", hash_code : -628015380,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(398889456, "Emulator.RootInfo", {
name : "Emulator.RootInfo", ns_name : "Emulator", rl_name : "RootInfo", hash_code : 398889456,
name_list : ["detail_info","for_show"],
type_list : ["Emulator.DetailInfo","bool"],
option_map : {}
})
ALittle.RegStruct(-297098024, "lua.protobuf_descriptor", {
name : "lua.protobuf_descriptor", ns_name : "lua", rl_name : "protobuf_descriptor", hash_code : -297098024,
name_list : [],
type_list : [],
option_map : {}
})

Emulator.g_GConfig = undefined;
Emulator.g_GProtoCache = undefined;
Emulator.LoginStatus = {
	EMULATOR_IDLE : 0,
	EMULATOR_LOGINING : 1,
	EMULATOR_LOGINED : 2,
}

Emulator.GCenter = JavaScript.Class(undefined, {
	Ctor : function() {
		this._proto_search_item_pool = {};
		this._proto_search_group = new Map();
		this._detail_tree_item_pool = {};
		this._log_search_group = new Map();
		this._log_item_list = [];
		this._log_item_count = 0;
		this._login_status = Emulator.LoginStatus.EMULATOR_IDLE;
	},
	Setup : function() {
		Emulator.g_GConfig = ALittle.CreateConfigSystem(Emulator.g_ModuleBasePath + "/User.cfg");
		Emulator.g_GProtoCache = ALittle.CreateConfigSystem(Emulator.g_ModuleBasePath + "/ProtoCache.cfg");
		ALittle.Math_RandomSeed(ALittle.Time_GetCurTime());
		ALittle.System_SetThreadCount(1, 2);
		this._main_layer = ALittle.NewObject(ALittle.DisplayLayout, Emulator.g_Control);
		this._main_layer.width_type = 4;
		this._main_layer.height_type = 4;
		Emulator.g_LayerGroup.AddChild(this._main_layer, undefined);
		this._dialog_layer = ALittle.NewObject(ALittle.DisplayLayout, Emulator.g_Control);
		this._dialog_layer.width_type = 4;
		this._dialog_layer.height_type = 4;
		Emulator.g_LayerGroup.AddChild(this._dialog_layer, undefined);
		Emulator.g_Control.CreateControl("main_scene", this, this._main_layer);
		this._setting_dialog = Emulator.g_Control.CreateControl("main_setting_dialog", this);
		A_LayerManager.AddToModal(this._setting_dialog);
		this._proto_item_msg_menu = Emulator.g_Control.CreateControl("main_msg_menu", this);
		this._log_item_msg_menu = Emulator.g_Control.CreateControl("main_msg_menu", this);
		this._log_fliter_dialog = Emulator.g_Control.CreateControl("main_log_fliter_dialog", this);
		this._dialog_layer.AddChild(this._log_fliter_dialog);
		this._log_fliter_dialog.visible = false;
		this._fliter_map = {};
		let fliter_list = Emulator.g_GConfig.GetConfig("fliter_list", []);
		let ___OBJECT_1 = fliter_list;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let fliter = ___OBJECT_1[index - 1];
			if (fliter === undefined) break;
			this._fliter_map[fliter] = true;
		}
		let plugin_path = Emulator.g_GConfig.GetString("plugin_script", "");
		if (ALittle.File_GetFileExtByPathAndUpper(plugin_path) === "LUA") {
			let plugin_script = ALittle.File_ReadTextFromStdFile(plugin_path);
			if (plugin_script !== undefined) {
				__CPPAPI_ScriptSystemEx.RunScript(plugin_script, plugin_path);
			} else {
				this.HandleShowSettingDialog(undefined);
			}
		} else {
			this.HandleShowSettingDialog(undefined);
		}
		let proto_root = Emulator.g_GConfig.GetString("proto_root", "");
		if (proto_root !== "" && ALittle.File_GetFileAttr(proto_root) !== undefined) {
			let error = A_LuaProtobufSchedule.LoadProto(proto_root);
			if (error === undefined) {
				let func = _G["__PLUGIN_ProtoRefresh"];
				if (func !== undefined) {
					error = (function() { try { func.call(); return undefined; } catch (___ERROR) { return ___ERROR.message; } }).call(this);
					if (error !== undefined) {
						ALittle.Log(error);
					}
				}
				this.RefreshProtoList();
			} else {
				this.HandleShowSettingDialog(undefined);
			}
		}
		let login_proto = Emulator.g_GConfig.GetString("login_proto", "");
		let msg_info = A_LuaProtobufSchedule.GetMessageInfo(login_proto);
		if (msg_info !== undefined) {
			this._login_detail_info = Emulator.Utility_CreateTreeForEdit(msg_info);
			this._login_scroll_screen.SetContainer(this._login_detail_info.tree);
		}
		this._login_button.visible = true;
		this._logout_button.visible = false;
		this._login_ip_input.text = Emulator.g_GConfig.GetString("login_ip", "127.0.0.1");
		let data_list = Emulator.g_GConfig.GetConfig("login_ip_list", []);
		if (ALittle.List_Find(data_list, this._login_ip_input.text) === undefined) {
			ALittle.List_Push(data_list, this._login_ip_input.text);
		}
		this._ip_dropdown.data_list = data_list;
		this._ip_dropdown.text = "";
		this._login_port_input.text = ALittle.String_ToString(Emulator.g_GConfig.GetInt("login_port", 0));
		this._right_grad3_ud.up_size = Emulator.g_GConfig.GetDouble("right_grid3_up_size", this._right_grad3_ud.up_size);
		this._main_grid3_lr.down_size = Emulator.g_GConfig.GetDouble("main_grid3_down_size", this._main_grid3_lr.down_size);
		this._send_button.disabled = true;
		this._frame_loop = ALittle.NewObject(ALittle.LoopFrame, this.UpdateFrame.bind(this));
		this._frame_loop.Start();
		this._json_codeedit = AUIPlugin.AUICodeEdit.Create();
		this._json_codeedit.editable = false;
		this._json_container.AddChild(this._json_codeedit);
	},
	UpdateFrame : function(frame_time) {
		A_LuaProtobufSchedule.RunInFrame();
	},
	HandleIpSelectChanged : function(event) {
		this._login_ip_input.text = this._ip_dropdown.text;
	},
	HandleShowSettingDialog : function(event) {
		this._setting_dialog.visible = true;
		this._proto_root_input.text = Emulator.g_GConfig.GetString("proto_root", "");
		this._login_proto_input.text = Emulator.g_GConfig.GetString("login_proto", "");
		this._plugin_file_input.text = Emulator.g_GConfig.GetString("plugin_script", "");
	},
	HandleShowVersionDialog : function(event) {
	},
	HandleSettingSelectProtoRootClick : function(event) {
		if (event.path === undefined) {
			return;
		}
		this._proto_root_input.text = event.path;
	},
	HandleSettingSelectPluginScriptClick : function(event) {
		if (event.path === undefined) {
			return;
		}
		this._plugin_file_input.text = event.path;
	},
	HandleSettingGeneratePluginScriptClick : function(event) {
		if (event.path === undefined) {
			return;
		}
		this._plugin_file_input.text = event.path + "\\TemplatePlugin.lua";
		Emulator.g_GConfig.SetConfig("plugin_script", this._plugin_file_input.text);
		ALittle.File_CopyFile(Emulator.g_ModuleBasePath + "Other/TemplatePlugin.lua", this._plugin_file_input.text);
	},
	HandleSettingConfirmClick : function(event) {
		let attr = ALittle.File_GetFileAttr(this._proto_root_input.text);
		if (attr === undefined || attr.mode !== "directory") {
			g_AUITool.ShowNotice("错误", "文件夹不存在");
			return;
		}
		let error = A_LuaProtobufSchedule.LoadProto(this._proto_root_input.text);
		if (error !== undefined) {
			g_AUITool.ShowNotice("错误", error);
			return;
		}
		if (ALittle.File_GetFileExtByPathAndUpper(this._plugin_file_input.text) === "LUA") {
			delete _G["__PLUGIN_ProtoRefresh"];
			delete _G["__PLUGIN_StartLogin"];
			delete _G["__SOCKET_ReadMessage"];
			delete _G["__SOCKET_WriteMessage"];
			delete _G["__SOCKET_HandleMessage"];
			let plugin_script = ALittle.File_ReadTextFromStdFile(this._plugin_file_input.text);
			if (plugin_script !== undefined) {
				__CPPAPI_ScriptSystemEx.RunScript(plugin_script, this._plugin_file_input.text);
			}
		} else {
			g_AUITool.ShowNotice("错误", "插件脚本必须是lua脚本");
			return;
		}
		this._setting_dialog.visible = false;
		Emulator.g_GConfig.SetConfig("proto_root", this._proto_root_input.text);
		let func = _G["__PLUGIN_ProtoRefresh"];
		if (func !== undefined) {
			error = (function() { try { func.call(); return undefined; } catch (___ERROR) { return ___ERROR.message; } }).call(this);
			if (error !== undefined) {
				ALittle.Log(error);
			}
		}
		if (error !== undefined) {
			g_AUITool.ShowNotice("错误", error);
			return;
		}
		this._protobuf_scroll_screen.RemoveAllChild();
		this._proto_search_item_pool = {};
		this._proto_search_group = new Map();
		this.RefreshProtoList();
		this._detail_scroll_screen.SetContainer(undefined);
		this._detail_tree_item_pool = {};
		this._log_search_group = new Map();
		this._log_item_list = [];
		this._log_item_count = 0;
		this._log_scroll_screen.RemoveAllChild();
		this.RefreshLogList();
		this._login_detail_info = undefined;
		let login_proto = this._login_proto_input.text;
		let msg_info = A_LuaProtobufSchedule.GetMessageInfo(login_proto);
		if (msg_info !== undefined) {
			this._login_detail_info = Emulator.Utility_CreateTreeForEdit(msg_info);
			this._login_scroll_screen.SetContainer(this._login_detail_info.tree);
		} else {
			this._login_scroll_screen.SetContainer(undefined);
		}
		Emulator.g_GConfig.SetConfig("login_proto", login_proto);
		Emulator.g_GConfig.SetConfig("plugin_script", this._plugin_file_input.text);
	},
	HandleSettingCancelClick : function(event) {
		this._setting_dialog.visible = false;
	},
	HandleProtoSearchClick : function(event) {
		this.RefreshProtoList();
	},
	RefreshProtoList : function() {
		let key = this._proto_search_key.text;
		key = ALittle.String_Upper(key);
		let key_list = ALittle.String_SplitSepList(key, [" ", "\t"]);
		let ___OBJECT_2 = this._protobuf_scroll_screen.childs;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let child = ___OBJECT_2[index - 1];
			if (child === undefined) break;
			child.group = undefined;
		}
		this._protobuf_scroll_screen.RemoveAllChild();
		let list = undefined;
		if (ALittle.List_MaxN(key_list) === 0) {
			list = A_LuaProtobufSchedule.FindMessageByUpperKey("");
		} else {
			list = A_LuaProtobufSchedule.FindMessageByUpperKeyList(key_list);
		}
		let ___OBJECT_3 = list;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let info = ___OBJECT_3[index - 1];
			if (info === undefined) break;
			let item = this._proto_search_item_pool[info.name];
			if (item === undefined) {
				item = Emulator.g_Control.CreateControl("emulator_common_item_radiobutton");
				item.text = info.name;
				this._proto_search_item_pool[info.name] = item;
				item.drag_trans_target = this._protobuf_scroll_screen;
				item._user_data = info;
				item.AddEventListener(___all_struct.get(958494922), this, this.HandleProtoItemSelected);
				item.AddEventListener(___all_struct.get(-641444818), this, this.HandleProtoItemRButtonDown);
			}
			let detail_info = this._detail_tree_item_pool[info.full_name];
			item.selected = detail_info !== undefined && detail_info.tree === this._detail_scroll_screen.container;
			item.group = this._proto_search_group;
			this._protobuf_scroll_screen.AddChild(item);
		}
		this._protobuf_scroll_screen.AdjustScrollBar();
	},
	HandleProtoItemSelected : function(event) {
		let info = event.target._user_data;
		let detail_info = this._detail_tree_item_pool[info.full_name];
		if (detail_info === undefined) {
			detail_info = Emulator.Utility_CreateTreeForEdit(info);
			if (detail_info === undefined) {
				return;
			}
			this._detail_tree_item_pool[info.full_name] = detail_info;
		}
		this._detail_scroll_screen.SetContainer(detail_info.tree);
		this._detail_scroll_screen.AdjustScrollBar();
	},
	HandleProtoItemRButtonDown : function(event) {
		A_LayerManager.ShowFromRight(this._proto_item_msg_menu);
		this._proto_item_msg_menu.x = A_UISystem.mouse_x;
		this._proto_item_msg_menu.y = A_UISystem.mouse_y;
		this._proto_item_msg_menu._user_data = event.target._user_data;
	},
	HandleLogSearchClick : function(event) {
		this.RefreshLogList();
	},
	HandleLogClearClick : function(event) {
		this._log_search_key.text = "";
		this._log_item_list = [];
		this._log_item_count = 0;
		this._log_scroll_screen.RemoveAllChild();
		this._cur_item_user_data = undefined;
		this._json_codeedit.OnClose();
	},
	HandleLogFliterClick : function(event) {
		this._log_fliter_dialog.visible = true;
		let fliter_list = Emulator.g_GConfig.GetConfig("fliter_list", []);
		this._log_fliter_edit.text = ALittle.String_Join(fliter_list, "\n");
	},
	HandleLogFliterCancelClick : function(event) {
		this._log_fliter_dialog.visible = false;
	},
	HandleLogFliterConfirmClick : function(event) {
		this._log_fliter_dialog.visible = false;
		let fliter_list = ALittle.String_SplitSepList(this._log_fliter_edit.text, ["\r", "\n"]);
		Emulator.g_GConfig.SetConfig("fliter_list", fliter_list);
		this._fliter_map = {};
		let ___OBJECT_4 = fliter_list;
		for (let index = 1; index <= ___OBJECT_4.length; ++index) {
			let fliter = ___OBJECT_4[index - 1];
			if (fliter === undefined) break;
			this._fliter_map[fliter] = true;
		}
	},
	RefreshLogList : function() {
		let key = this._log_search_key.text;
		key = ALittle.String_Upper(key);
		let ___OBJECT_5 = this._log_scroll_screen.childs;
		for (let index = 1; index <= ___OBJECT_5.length; ++index) {
			let child = ___OBJECT_5[index - 1];
			if (child === undefined) break;
			child.group = undefined;
		}
		this._log_scroll_screen.RemoveAllChild();
		let ___OBJECT_6 = this._log_item_list;
		for (let index = 1; index <= ___OBJECT_6.length; ++index) {
			let button = ___OBJECT_6[index - 1];
			if (button === undefined) break;
			let user_data = button._user_data;
			if (ALittle.String_Find(user_data.upper_name, key) !== undefined) {
				button.group = this._log_search_group;
				this._log_scroll_screen.AddChild(button);
			}
		}
		this._log_scroll_screen.AdjustScrollBar();
	},
	AddLogMessage : function(msg) {
		let descriptor = lua.protobuf.message_getdescriptor(msg);
		let full_name = lua.protobuf.messagedescriptor_fullname(descriptor);
		if (this._fliter_map[full_name] !== undefined) {
			return;
		}
		if (this._log_item_count > 500) {
			let item = this._log_item_list[1 - 1];
			let user_data = item._user_data;
			if (this._cur_item_user_data === user_data) {
				this._json_codeedit.OnClose();
			}
			this._log_scroll_screen.RemoveChild(item);
			item.group = undefined;
			ALittle.List_Remove(this._log_item_list, 1);
		}
		let user_data = {};
		user_data.info = A_LuaProtobufSchedule.GetMessageInfoByMessage(msg);
		user_data.msg = lua.protobuf.clonemessage(msg);
		user_data.upper_name = ALittle.String_Upper(user_data.info.name);
		let item = Emulator.g_Control.CreateControl("emulator_common_item_radiobutton");
		item.text = user_data.info.name;
		item.drag_trans_target = this._log_scroll_screen;
		item._user_data = user_data;
		item.AddEventListener(___all_struct.get(958494922), this, this.HandleLogItemSelected);
		item.AddEventListener(___all_struct.get(-641444818), this, this.HandleProtoLogRButtonDown);
		++ this._log_item_count;
		this._log_item_list[this._log_item_count - 1] = item;
		let key = this._log_search_key.text;
		key = ALittle.String_Upper(key);
		if (ALittle.String_Find(user_data.upper_name, key) !== undefined) {
			let bottom = this._log_scroll_screen.right_scrollbar.offset_rate >= 0.95 || this._log_scroll_screen.container.height < this._log_scroll_screen.view_height;
			item.group = this._log_search_group;
			this._log_scroll_screen.AddChild(item);
			if (bottom) {
				this._log_scroll_screen.ScrollToBottom();
			}
		}
	},
	HandleLogItemSelected : function(event) {
		this._show_search_key.text = "";
		this._cur_item_user_data = event.target._user_data;
		if (this._cur_item_user_data.json_content === undefined) {
			this._cur_item_user_data.json_content = lua.protobuf.message_jsonencode(this._cur_item_user_data.msg, false);
		}
		this._json_codeedit.OnClose();
		this._json_codeedit.Load("temp.json", this._cur_item_user_data.json_content, undefined);
	},
	HandleProtoLogRButtonDown : function(event) {
		A_LayerManager.ShowFromRight(this._log_item_msg_menu);
		this._log_item_msg_menu.x = A_UISystem.mouse_x;
		this._log_item_msg_menu.y = A_UISystem.mouse_y;
		this._log_item_msg_menu._user_data = event.target._user_data;
	},
	HandleShowSearchClick : function(event) {
		if (this._cur_item_user_data === undefined) {
			return;
		}
		let key = this._show_search_key.text;
		this._json_codeedit.FindNext(key);
	},
	HandleMsgCopyFullName : function(event) {
		if (A_LayerManager.IsCurrentRight(this._proto_item_msg_menu)) {
			let info = this._proto_item_msg_menu._user_data;
			ALittle.System_SetClipboardText(info.full_name);
		} else if (A_LayerManager.IsCurrentRight(this._log_item_msg_menu)) {
			let info = this._log_item_msg_menu._user_data;
			ALittle.System_SetClipboardText(info.info.full_name);
		}
		A_LayerManager.HideCurrentFromRight();
	},
	HandleMsgCopyName : function(event) {
		if (A_LayerManager.IsCurrentRight(this._proto_item_msg_menu)) {
			let info = this._proto_item_msg_menu._user_data;
			ALittle.System_SetClipboardText(info.name);
		} else if (A_LayerManager.IsCurrentRight(this._log_item_msg_menu)) {
			let info = this._log_item_msg_menu._user_data;
			ALittle.System_SetClipboardText(info.info.name);
		}
		A_LayerManager.HideCurrentFromRight();
	},
	HandleMsgAddToFliter : function(event) {
		let full_name = undefined;
		if (A_LayerManager.IsCurrentRight(this._proto_item_msg_menu)) {
			let info = this._proto_item_msg_menu._user_data;
			full_name = info.full_name;
		} else if (A_LayerManager.IsCurrentRight(this._log_item_msg_menu)) {
			let info = this._log_item_msg_menu._user_data;
			full_name = info.info.full_name;
		}
		this._fliter_map[full_name] = true;
		let list = [];
		let ___OBJECT_7 = this._fliter_map;
		for (let name in ___OBJECT_7) {
			let _ = ___OBJECT_7[name];
			if (_ === undefined) continue;
			ALittle.List_Push(list, name);
		}
		Emulator.g_GConfig.SetConfig("fliter_list", list);
		A_LayerManager.HideCurrentFromRight();
	},
	HandleClientSocketDisconnected : function(socket) {
		this._client_socket = undefined;
		this._send_button.disabled = true;
		this._login_button.visible = true;
		this._logout_button.visible = false;
		if (this._login_status === Emulator.LoginStatus.EMULATOR_LOGINED) {
			let func = _G["__PLUGIN_HandleLogout"];
			if (func !== undefined) {
				let error = (function() { try { func.call(); return undefined; } catch (___ERROR) { return ___ERROR.message; } }).call(this);
				if (error !== undefined) {
					ALittle.Log(error);
				}
			}
		}
		this._login_status = Emulator.LoginStatus.EMULATOR_IDLE;
	},
	HandleSendClick : function(event) {
		let tree = this._detail_scroll_screen.container;
		if (tree === undefined) {
			return;
		}
		let detail_info = tree.GetDetailInfo();
		if (this._client_socket !== undefined) {
			this._client_socket.SendMessage(detail_info.message);
		}
	},
	HandleLoginClick : async function(event) {
		let ip = this._login_ip_input.text;
		let port = ALittle.Math_ToInt(this._login_port_input.text);
		if (port === undefined || port <= 0) {
			g_AUITool.ShowNotice("提示", "请使用正确的端口");
			return;
		}
		if (this._login_detail_info === undefined) {
			g_AUITool.ShowNotice("提示", "请设置登陆协议");
			return;
		}
		if (this._login_status === Emulator.LoginStatus.EMULATOR_LOGINING) {
			g_AUITool.ShowNotice("提示", "当前正在登陆，请先断开");
			return;
		}
		if (this._login_status === Emulator.LoginStatus.EMULATOR_LOGINED) {
			g_AUITool.ShowNotice("提示", "当前已登录，请先断开");
			return;
		}
		Emulator.g_GConfig.SetConfig("login_ip", ip);
		Emulator.g_GConfig.SetConfig("login_port", port);
		let data_list = ALittle.List_Copy(Emulator.g_GConfig.GetConfig("login_ip_list", []));
		if (ALittle.List_Find(data_list, ip) === undefined) {
			ALittle.List_Push(data_list, ip);
		}
		Emulator.g_GConfig.SetConfig("login_ip_list", data_list);
		this._ip_dropdown.data_list = data_list;
		this._ip_dropdown.text = "";
		this._login_button.visible = false;
		this._logout_button.visible = true;
		this._login_status = Emulator.LoginStatus.EMULATOR_LOGINING;
		let error = undefined;
		if (this._client_socket !== undefined) {
			this._client_socket.Close();
			this._client_socket = undefined;
		}
		let login_func = _G["__PLUGIN_StartLogin"];
		if (login_func === undefined) {
			error = "还未加载插件";
		} else {
			let call_error = undefined;
			[call_error, error, this._client_socket] = await (async function() { try { let ___VALUE = await login_func.call(ip, port, this._login_detail_info.message); ___VALUE.splice(0, 0, undefined);  return ___VALUE; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
			if (call_error !== undefined) {
				error = call_error;
			}
		}
		if (error === undefined) {
			if (this._client_socket !== undefined) {
				this._client_socket.disconnect_callback = this.HandleClientSocketDisconnected.bind(this);
				this._client_socket.ReceiveMessage();
			}
			this._login_status = Emulator.LoginStatus.EMULATOR_LOGINED;
			this._send_button.disabled = false;
		} else {
			g_AUITool.ShowNotice("提示", error);
			this._login_status = Emulator.LoginStatus.EMULATOR_IDLE;
			this._login_button.visible = true;
			this._logout_button.visible = false;
		}
	},
	HandleLogoutClick : function(event) {
		if (this._client_socket !== undefined) {
			this._client_socket.Close();
			this._client_socket = undefined;
		}
		this._send_button.disabled = true;
		this._login_button.visible = true;
		this._logout_button.visible = false;
		if (this._login_status === Emulator.LoginStatus.EMULATOR_LOGINED) {
			let func = _G["__PLUGIN_HandleLogout"];
			if (func !== undefined) {
				let error = (function() { try { func.call(); return undefined; } catch (___ERROR) { return ___ERROR.message; } }).call(this);
				if (error !== undefined) {
					ALittle.Log(error);
				}
			}
		}
		this._login_status = Emulator.LoginStatus.EMULATOR_IDLE;
	},
	HandleDragRightQuadUD : function(event) {
		this._right_grad3_ud.up_size = this._right_grad3_ud.up_size + (event.delta_y);
	},
	HandleDragEndRightQuadUD : function(event) {
		Emulator.g_GConfig.SetConfig("right_grid3_up_size", this._right_grad3_ud.up_size);
	},
	HandleDragRightQuadLR : function(event) {
		this._main_grid3_lr.down_size = this._main_grid3_lr.down_size - (event.delta_x);
	},
	HandleDragEndRightQuadLR : function(event) {
		Emulator.g_GConfig.SetConfig("main_grid3_down_size", this._main_grid3_lr.down_size);
	},
	HandleSetVDragCursor : function(event) {
		ALittle.System_SetVDragCursor();
	},
	HandleSetHDragCursor : function(event) {
		ALittle.System_SetHDragCursor();
	},
	HandleSetNormalCursor : function(event) {
		ALittle.System_SetNormalCursor();
	},
	Shutdown : function() {
		this._frame_loop.Stop();
	},
}, "Emulator.GCenter");

window.g_GCenter = ALittle.NewObject(Emulator.GCenter);
}