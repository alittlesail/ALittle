{
if (typeof Emulator === "undefined") window.Emulator = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1618605759, "Emulator.DetailInfo", {
name : "Emulator.DetailInfo", ns_name : "Emulator", rl_name : "DetailInfo", hash_code : 1618605759,
name_list : ["tree","message","reflection","info"],
type_list : ["Emulator.IDETreeLogic","lua.protobuf_message","lua.protobuf_reflection","Lua.lua_socket_schedule_message_info"],
option_map : {}
})
ALittle.RegStruct(-628015380, "lua.protobuf_message", {
name : "lua.protobuf_message", ns_name : "lua", rl_name : "protobuf_message", hash_code : -628015380,
name_list : [],
type_list : [],
option_map : {}
})
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
ALittle.RegStruct(-297098024, "lua.protobuf_descriptor", {
name : "lua.protobuf_descriptor", ns_name : "lua", rl_name : "protobuf_descriptor", hash_code : -297098024,
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
ALittle.RegStruct(-888044440, "Emulator.LogItemUserData", {
name : "Emulator.LogItemUserData", ns_name : "Emulator", rl_name : "LogItemUserData", hash_code : -888044440,
name_list : ["msg","info","upper_name","detail_info"],
type_list : ["lua.protobuf_message","Lua.lua_socket_schedule_message_info","string","Emulator.DetailInfo"],
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
		A_LuaSocketSchedule.Setup();
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
			let error = A_LuaSocketSchedule.LoadProto(proto_root);
			if (error === undefined) {
				let func = _G["__PLUGIN_ProtoRefresh"];
				if (func !== undefined) {
					error = (function() { try { func.call(); return undefined; } catch (___ERROR) { return ___ERROR.message; } }).call(this);
					if (error !== undefined) {
						ALittle.Log(error);
					}
				}
				this.RefreshProtoList();
			}
		}
		let login_proto = Emulator.g_GConfig.GetString("login_proto", "");
		let msg_info = A_LuaSocketSchedule.GetMessageInfo(login_proto);
		if (msg_info !== undefined) {
			this._login_detail_info = Emulator.Utility_CreateTreeForEdit(msg_info);
			this._login_scroll_screen.SetContainer(this._login_detail_info.tree);
		}
		this._login_button.visible = true;
		this._logout_button.visible = false;
		this._login_ip_input.text = Emulator.g_GConfig.GetString("login_ip", "127.0.0.1");
		this._login_port_input.text = ALittle.String_ToString(Emulator.g_GConfig.GetInt("login_port", 0));
		this._right_grad3_ud.up_size = Emulator.g_GConfig.GetDouble("right_grid3_up_size", this._right_grad3_ud.up_size);
		this._main_grid3_lr.down_size = Emulator.g_GConfig.GetDouble("main_grid3_down_size", this._main_grid3_lr.down_size);
		this._send_button.disabled = true;
		this._frame_loop = ALittle.NewObject(ALittle.LoopFrame, this.UpdateFrame.bind(this));
		this._frame_loop.Start();
	},
	UpdateFrame : function(frame_time) {
		A_LuaSocketSchedule.RunInFrame();
	},
	HandleShowSettingDialog : function(event) {
		this._setting_dialog.visible = true;
		this._proto_root_input.text = Emulator.g_GConfig.GetString("proto_root", "");
		this._login_proto_input.text = Emulator.g_GConfig.GetString("login_proto", "");
		this._plugin_file_input.text = Emulator.g_GConfig.GetString("plugin_script", "");
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
			Emulator.g_IDETool.ShowNotice("错误", "文件夹不存在");
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
			Emulator.g_IDETool.ShowNotice("错误", "插件脚本必须是lua脚本");
			return;
		}
		this._setting_dialog.visible = false;
		Emulator.g_GConfig.SetConfig("proto_root", this._proto_root_input.text);
		let error = A_LuaSocketSchedule.LoadProto(this._proto_root_input.text);
		let func = _G["__PLUGIN_ProtoRefresh"];
		if (func !== undefined) {
			error = (function() { try { func.call(); return undefined; } catch (___ERROR) { return ___ERROR.message; } }).call(this);
			if (error !== undefined) {
				ALittle.Log(error);
			}
		}
		if (error !== undefined) {
			Emulator.g_IDETool.ShowNotice("错误", error);
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
		let msg_info = A_LuaSocketSchedule.GetMessageInfo(login_proto);
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
		let ___OBJECT_1 = this._protobuf_scroll_screen.childs;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let child = ___OBJECT_1[index - 1];
			if (child === undefined) break;
			child.group = undefined;
		}
		this._protobuf_scroll_screen.RemoveAllChild();
		let list = A_LuaSocketSchedule.FindMessageByUpperKey(key);
		let ___OBJECT_2 = list;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let info = ___OBJECT_2[index - 1];
			if (info === undefined) break;
			let item = this._proto_search_item_pool[info.name];
			if (item === undefined) {
				item = Emulator.g_Control.CreateControl("emulator_common_item_radiobutton");
				item.text = info.name;
				this._proto_search_item_pool[info.name] = item;
				item.drag_trans_target = this._protobuf_scroll_screen;
				item._user_data = info;
				item.AddEventListener(___all_struct.get(958494922), this, this.HandleProtoItemSelected);
			}
			item.group = this._proto_search_group;
			this._protobuf_scroll_screen.AddChild(item);
		}
		this._protobuf_scroll_screen.RejustScrollBar();
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
		this._detail_scroll_screen.RejustScrollBar();
	},
	HandleLogSearchClick : function(event) {
		this.RefreshLogList();
	},
	RefreshLogList : function() {
		let key = this._log_search_key.text;
		key = ALittle.String_Upper(key);
		let ___OBJECT_3 = this._log_scroll_screen.childs;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let child = ___OBJECT_3[index - 1];
			if (child === undefined) break;
			child.group = undefined;
		}
		this._log_scroll_screen.RemoveAllChild();
		let ___OBJECT_4 = this._log_item_list;
		for (let index = 1; index <= ___OBJECT_4.length; ++index) {
			let button = ___OBJECT_4[index - 1];
			if (button === undefined) break;
			let user_data = button._user_data;
			if (ALittle.String_Find(user_data.upper_name, key) !== undefined) {
				button.group = this._log_search_group;
				this._log_scroll_screen.AddChild(button);
			}
		}
		this._log_scroll_screen.RejustScrollBar();
	},
	AddLogMessage : function(msg) {
		if (this._log_item_count > 500) {
			let item = this._log_item_list[1 - 1];
			let user_data = item._user_data;
			if (this._cur_item_user_data === user_data) {
				this._show_scroll_screen.SetContainer(undefined);
			}
			this._log_scroll_screen.RemoveChild(item);
			item.group = undefined;
			ALittle.List_Remove(this._log_item_list, 1);
		}
		let user_data = {};
		user_data.info = A_LuaSocketSchedule.GetMessageInfoByMessage(msg);
		user_data.msg = lua.protobuf.clonemessage(msg);
		user_data.upper_name = ALittle.String_Upper(user_data.info.name);
		let item = Emulator.g_Control.CreateControl("emulator_common_item_radiobutton");
		item.text = user_data.info.name;
		item.drag_trans_target = this._log_scroll_screen;
		item._user_data = user_data;
		item.AddEventListener(___all_struct.get(958494922), this, this.HandleLogItemSelected);
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
		if (this._cur_item_user_data.detail_info === undefined) {
			this._cur_item_user_data.detail_info = Emulator.Utility_CreateTreeForShow(this._cur_item_user_data.msg);
		}
		this._show_scroll_screen.SetContainer(this._cur_item_user_data.detail_info.tree);
	},
	HandleShowSearchClick : function(event) {
		if (this._cur_item_user_data === undefined) {
			return;
		}
		let key = this._show_search_key.text;
		key = ALittle.String_Upper(key);
		let tree = this._cur_item_user_data.detail_info.tree;
		tree.SearchBegin();
		let list = tree.SearchDescription(key);
		tree.SearchEnd(list);
	},
	HandleClientSocketDisconnected : function(socket) {
		this._client_socket = undefined;
		this._send_button.disabled = true;
		this._login_button.visible = true;
		this._logout_button.visible = false;
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
			Emulator.g_IDETool.ShowNotice("提示", "请使用正确的端口");
			return;
		}
		if (this._login_detail_info === undefined) {
			Emulator.g_IDETool.ShowNotice("提示", "请设置登陆协议");
			return;
		}
		if (this._login_status === Emulator.LoginStatus.EMULATOR_LOGINING) {
			Emulator.g_IDETool.ShowNotice("提示", "当前正在登陆，请先断开");
			return;
		}
		if (this._login_status === Emulator.LoginStatus.EMULATOR_LOGINED) {
			Emulator.g_IDETool.ShowNotice("提示", "当前已登录，请先断开");
			return;
		}
		Emulator.g_GConfig.SetConfig("login_ip", ip);
		Emulator.g_GConfig.SetConfig("login_port", port);
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
			Emulator.g_IDETool.ShowNotice("提示", error);
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