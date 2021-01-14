{
if (typeof DeployClient === "undefined") window.DeployClient = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-2127611090, "DeployClient.BuildItemInfo", {
name : "DeployClient.BuildItemInfo", ns_name : "DeployClient", rl_name : "BuildItemInfo", hash_code : -2127611090,
name_list : ["item","info","_button","_download_button"],
type_list : ["ALittle.DisplayObject","DeployServer.D_BuildInfo","ALittle.DisplayObject","ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-2035971543, "DeployServer.D_JobInfo", {
name : "DeployServer.D_JobInfo", ns_name : "DeployServer", rl_name : "D_JobInfo", hash_code : -2035971543,
name_list : ["job_type","job_name","status","progress","detail"],
type_list : ["int","string","int","double","DeployServer.JobInfoDetail"],
option_map : {}
})
ALittle.RegStruct(-2031251578, "DeployServer.C2SCopyJob", {
name : "DeployServer.C2SCopyJob", ns_name : "DeployServer", rl_name : "C2SCopyJob", hash_code : -2031251578,
name_list : ["task_id","job_index"],
type_list : ["int","int"],
option_map : {}
})
ALittle.RegStruct(1984174335, "DeployServer.S2CDeleteBuild", {
name : "DeployServer.S2CDeleteBuild", ns_name : "DeployServer", rl_name : "S2CDeleteBuild", hash_code : 1984174335,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(1811432266, "DeployServer.D_BuildInfo", {
name : "DeployServer.D_BuildInfo", ns_name : "DeployServer", rl_name : "D_BuildInfo", hash_code : 1811432266,
name_list : ["create_time"],
type_list : ["int"],
option_map : {}
})
ALittle.RegStruct(1809409109, "DeployServer.S2CDeleteJob", {
name : "DeployServer.S2CDeleteJob", ns_name : "DeployServer", rl_name : "S2CDeleteJob", hash_code : 1809409109,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(1800966813, "ALittle.UISystemSelectDirectoryEvent", {
name : "ALittle.UISystemSelectDirectoryEvent", ns_name : "ALittle", rl_name : "UISystemSelectDirectoryEvent", hash_code : 1800966813,
name_list : ["target","path"],
type_list : ["ALittle.DisplayObject","string"],
option_map : {}
})
ALittle.RegStruct(1624339767, "DeployServer.S2CMoveJob", {
name : "DeployServer.S2CMoveJob", ns_name : "DeployServer", rl_name : "S2CMoveJob", hash_code : 1624339767,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(1566214727, "DeployServer.S2CUpdateTaskInfo", {
name : "DeployServer.S2CUpdateTaskInfo", ns_name : "DeployServer", rl_name : "S2CUpdateTaskInfo", hash_code : 1566214727,
name_list : [],
type_list : [],
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
ALittle.RegStruct(-1320965296, "DeployServer.C2SDeleteJob", {
name : "DeployServer.C2SDeleteJob", ns_name : "DeployServer", rl_name : "C2SDeleteJob", hash_code : -1320965296,
name_list : ["task_id","job_index"],
type_list : ["int","int"],
option_map : {}
})
ALittle.RegStruct(1254025721, "DeployServer.C2SDeleteBuild", {
name : "DeployServer.C2SDeleteBuild", ns_name : "DeployServer", rl_name : "C2SDeleteBuild", hash_code : 1254025721,
name_list : ["task_id","build_index"],
type_list : ["int","int"],
option_map : {}
})
ALittle.RegStruct(1232578034, "DeployServer.JobInfoDetail", {
name : "DeployServer.JobInfoDetail", ns_name : "DeployServer", rl_name : "JobInfoDetail", hash_code : 1232578034,
name_list : ["batch_dir","batch_cmd","batch_param","deepcopy_src","deepcopy_dst","deepcopy_ext","copyfile_src","copyfile_file","copyfile_dst","virtualkey_exepath","virtualkey_cmd","wait_p_exit_exe_path","wait_p_exit_max_time","createprocess_dir","createprocess_cmd","createprocess_param","killprocess_exe_path"],
type_list : ["string","string","string","string","string","string","string","List<string>","string","string","List<string>","List<string>","int","string","string","string","List<string>"],
option_map : {}
})
ALittle.RegStruct(1149037254, "DeployServer.C2SUpdateTaskInfo", {
name : "DeployServer.C2SUpdateTaskInfo", ns_name : "DeployServer", rl_name : "C2SUpdateTaskInfo", hash_code : 1149037254,
name_list : ["task_id","task_name","task_desc","web_hook"],
type_list : ["int","string","string","List<string>"],
option_map : {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name : "ALittle.UIChangedEvent", ns_name : "ALittle", rl_name : "UIChangedEvent", hash_code : 958494922,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(874244823, "DeployServer.S2CCopyJob", {
name : "DeployServer.S2CCopyJob", ns_name : "DeployServer", rl_name : "S2CCopyJob", hash_code : 874244823,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name : "ALittle.UIRButtonDownEvent", ns_name : "ALittle", rl_name : "UIRButtonDownEvent", hash_code : -641444818,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(629373421, "DeployClient.JobItemInfo", {
name : "DeployClient.JobItemInfo", ns_name : "DeployClient", rl_name : "JobItemInfo", hash_code : 629373421,
name_list : ["item","info","_button","_status"],
type_list : ["ALittle.DisplayObject","DeployServer.D_JobInfo","ALittle.DisplayObject","ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-616678126, "DeployServer.C2SMoveJob", {
name : "DeployServer.C2SMoveJob", ns_name : "DeployServer", rl_name : "C2SMoveJob", hash_code : -616678126,
name_list : ["task_id","job_index","target_index"],
type_list : ["int","int","int"],
option_map : {}
})

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
DeployClient.DPLUITaskDetail = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function() {
		this._job_group = new Map();
		this._build_group = new Map();
	},
	Init : function(task_item) {
		this._task_item = task_item;
		this.UpdateTaskInfo();
		this.RefreshJobInfo();
		this.RefreshBuildInfo();
	},
	Show : function() {
		this.visible = true;
		if (!this._save_button.disabled) {
			this.UpdateTaskInfo();
		}
	},
	Hide : function() {
		this.visible = false;
	},
	UpdateTaskInfo : function() {
		this._save_button.disabled = true;
		this._task_name_input.text = this._task_item.info.task_name;
		this._task_desc_input.text = this._task_item.info.task_desc;
		this._webhook_input.text = ALittle.String_Join(this._task_item.info.web_hook, "\n");
	},
	UpdateJobInfo : function(index) {
		let job_info = this._task_item.info.job_list[index - 1];
		if (job_info === undefined) {
			return;
		}
		let job_item = this._job_list.childs[index - 1]._user_data;
		job_item.info = job_info;
		this.RefreshJobItem(job_item);
	},
	RemoveJobItem : function(index) {
		let job_info = this._task_item.info.job_list[index - 1];
		if (job_info === undefined) {
			return;
		}
		this._job_list.SpliceChild(index, 1);
	},
	MoveJobItem : function(index, target_index) {
		let job_info = this._task_item.info.job_list[index - 1];
		if (job_info === undefined) {
			return;
		}
		this._job_list.SetChildIndex(this._job_list.GetChildByIndex(index), target_index);
	},
	RemoveBuildItem : function(index) {
		let build_info = this._task_item.info.build_list[index - 1];
		if (build_info === undefined) {
			return;
		}
		this._build_list.SpliceChild(index, 1);
	},
	RefreshJobInfo : function() {
		this._job_list.RemoveAllChild();
		let ___OBJECT_1 = this._task_item.info.job_list;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let job_info = ___OBJECT_1[index - 1];
			if (job_info === undefined) break;
			this.AddJobItem(undefined, job_info);
		}
	},
	RefreshBuildInfo : function() {
		this._build_list.RemoveAllChild();
		let ___OBJECT_2 = this._task_item.info.build_list;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let build_info = ___OBJECT_2[index - 1];
			if (build_info === undefined) break;
			this.AddBuildItem(build_info);
		}
	},
	HandleTaskBaseChanged : function(event) {
		this._save_button.disabled = false;
	},
	HandleTaskStart : function() {
		let ___OBJECT_3 = this._job_list.childs;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let child = ___OBJECT_3[index - 1];
			if (child === undefined) break;
			let job_item = child._user_data;
			job_item._status.text = "等待";
		}
	},
	HandleTaskSaveClick : async function(event) {
		let msg_client = DeployClient.g_DPLWebLoginManager.msg_client;
		if (msg_client === undefined || !msg_client.IsConnected()) {
			g_AUITool.ShowNotice("提示", "当前还未连接成功!");
			return;
		}
		if (this._task_name_input.text === "") {
			g_AUITool.ShowNotice("提示", "任务名称不能为空!");
			return;
		}
		let msg = {};
		msg.task_id = this._task_item.info.task_id;
		msg.task_name = this._task_name_input.text;
		msg.task_desc = this._task_desc_input.text;
		msg.web_hook = ALittle.String_SplitSepList(this._webhook_input.text, ["\r", "\n"]);
		let [error] = await ALittle.IMsgCommon.InvokeRPC(1149037254, msg_client, msg);
		if (error !== undefined) {
			g_AUITool.ShowNotice("提示", error);
		}
	},
	HandleNewJobClick : function(event) {
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.AddItem("批处理", this.HandleNewCommonJob.bind(this, "batch_job_dialog"));
		menu.AddItem("复制目录", this.HandleNewCommonJob.bind(this, "deepcopy_job_dialog"));
		menu.AddItem("复制文件", this.HandleNewCommonJob.bind(this, "copyfile_job_dialog"));
		menu.AddItem("发送命令", this.HandleNewCommonJob.bind(this, "sendvirtualkey_job_dialog"));
		menu.AddItem("等待进程退出", this.HandleNewCommonJob.bind(this, "waitprocessexit_job_dialog"));
		menu.AddItem("创建进程", this.HandleNewCommonJob.bind(this, "createprocess_job_dialog"));
		menu.AddItem("杀死进程", this.HandleNewCommonJob.bind(this, "killprocess_job_dialog"));
		menu.Show();
	},
	HandleStartTaskClick : function(event) {
		DeployClient.g_DPLCenter.center.task_center.HandleStartTask(this._task_item);
	},
	HandleNewCommonJob : function(ui) {
		let dialog = DeployClient.g_Control.CreateControl(ui);
		dialog.Show(this._task_item.info.task_id, undefined, undefined);
	},
	AddJobItem : function(job_index, job_info) {
		let job_item = {};
		job_item.info = job_info;
		job_item.item = DeployClient.g_Control.CreateControl("dpl_job_item", job_item);
		job_item.item._user_data = job_item;
		job_item._button._user_data = job_item;
		job_item._button.group = this._job_group;
		job_item._button.AddEventListener(___all_struct.get(-641444818), this, this.HandleJobRButtonDown);
		this._job_list.AddChild(job_item.item, job_index);
		this.RefreshJobItem(job_item);
	},
	AddBuildItem : function(build_info) {
		let build_item = {};
		build_item.info = build_info;
		build_item.item = DeployClient.g_Control.CreateControl("dpl_build_item", build_item);
		build_item.item._user_data = build_item;
		build_item._button._user_data = build_item;
		build_item._button.group = this._build_group;
		build_item._button.AddEventListener(___all_struct.get(-641444818), this, this.HandleBuildRButtonDown);
		build_item._button.AddEventListener(___all_struct.get(958494922), this, this.HandlePreSeeBuild);
		build_item._download_button.AddEventListener(___all_struct.get(1800966813), this, this.HandleDownloadBuild);
		build_item._download_button._user_data = build_item;
		this._build_list.AddChild(build_item.item);
		this._build_list.ScrollToBottom();
		build_item._button.text = ALittle.Time_GetCurDate(build_info.create_time);
	},
	RefreshJobItem : function(job_item) {
		if (job_item.info.job_type === 1) {
			job_item._button.text = "[批处理] " + job_item.info.job_name + ":" + job_item.info.detail.batch_cmd;
		} else if (job_item.info.job_type === 2) {
			job_item._button.text = "[复制目录] " + job_item.info.job_name + ":" + job_item.info.detail.deepcopy_src + "->" + job_item.info.detail.deepcopy_dst;
		} else if (job_item.info.job_type === 3) {
			job_item._button.text = "[复制文件] " + job_item.info.job_name + ":" + job_item.info.detail.copyfile_src + "->" + job_item.info.detail.copyfile_dst;
		} else if (job_item.info.job_type === 4) {
			job_item._button.text = "[发送命令] " + job_item.info.job_name + ":" + job_item.info.detail.virtualkey_exepath;
		} else if (job_item.info.job_type === 5) {
			job_item._button.text = "[等待进程退出] " + job_item.info.job_name;
		} else if (job_item.info.job_type === 6) {
			job_item._button.text = "[创建进程] " + job_item.info.job_name + ":" + job_item.info.detail.createprocess_cmd;
		} else if (job_item.info.job_type === 7) {
			job_item._button.text = "[杀死进程] " + job_item.info.job_name;
		}
		if (this._task_item.info.status === 0) {
			job_item._status.text = "";
		} else {
			if (job_item.info.status === 0) {
				job_item._status.text = "等待";
			} else if (job_item.info.status === 1) {
				job_item._status.text = ALittle.Math_Floor(job_item.info.progress * 10000) / 100 + "%";
			} else if (job_item.info.status === 2) {
				job_item._status.text = "完成";
			} else if (job_item.info.status === 3) {
				job_item._status.text = "失败";
			}
		}
	},
	HandleJobRButtonDown : function(event) {
		let job_item = event.target._user_data;
		let job_index = this._job_list.GetChildIndex(job_item.item);
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.AddItem("修改", this.HandleModifyJob.bind(this, job_item, job_index));
		menu.AddItem("上移", this.HandleMoveJob.bind(this, job_item, job_index, job_index - 1));
		menu.AddItem("下移", this.HandleMoveJob.bind(this, job_item, job_index, job_index + 1));
		menu.AddItem("复制", this.HandleCopyJob.bind(this, job_item, job_index));
		menu.AddItem("删除", this.HandleDeleteJob.bind(this, job_item, job_index));
		menu.Show();
	},
	HandleBuildRButtonDown : function(event) {
		let build_item = event.target._user_data;
		let build_index = this._build_list.GetChildIndex(build_item.item);
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		menu.AddItem("删除", this.HandleDeleteBuild.bind(this, build_item, build_index));
		menu.Show();
	},
	HandlePreSeeBuild : async function(event) {
		let build_item = event.target._user_data;
		let build_index = this._build_list.GetChildIndex(build_item.item);
		DeployClient.g_DPLCenter.center.task_center._build_edit.text = "";
		let msg = {};
		msg.task_id = this._task_item.info.task_id;
		msg.build_index = build_index;
		let sender = DeployClient.g_DPLCenter.CreateHttpSender();
		let [error, rsp] = await ALittle.IHttpSender.Invoke("DeployServer.QPreSeeBuild", sender, msg);
		if (error !== undefined) {
			g_AUITool.ShowNotice("提示", error);
			return;
		}
		DeployClient.g_DPLCenter.center.task_center._build_edit.text = ALittle.String_Join(rsp.log_list, "\r\n");
	},
	HandleDownloadBuild : async function(event) {
		if (event.path === undefined || event.path === "") {
			return;
		}
		let build_item = event.target._user_data;
		let build_index = this._build_list.GetChildIndex(build_item.item);
		let msg = {};
		msg.task_id = this._task_item.info.task_id;
		msg.build_index = build_index;
		let sender = DeployClient.g_DPLCenter.CreateHttpFileSender(event.path + "/" + ALittle.Time_GetCurDate(build_item.info.create_time) + ".log");
		let [error] = await ALittle.IHttpFileSender.InvokeDownload("DeployServer.QDownloadBuild", sender, msg);
		if (error !== undefined) {
			g_AUITool.ShowNotice("提示", error);
		}
	},
	HandleModifyJob : function(info, index) {
		let ui = undefined;
		if (info.info.job_type === 1) {
			ui = "batch_job_dialog";
		} else if (info.info.job_type === 2) {
			ui = "deepcopy_job_dialog";
		} else if (info.info.job_type === 3) {
			ui = "copyfile_job_dialog";
		} else if (info.info.job_type === 4) {
			ui = "sendvirtualkey_job_dialog";
		} else if (info.info.job_type === 5) {
			ui = "waitprocessexit_job_dialog";
		} else if (info.info.job_type === 6) {
			ui = "createprocess_job_dialog";
		} else if (info.info.job_type === 7) {
			ui = "killprocess_job_dialog";
		}
		if (ui !== undefined) {
			let dialog = DeployClient.g_Control.CreateControl(ui);
			dialog.Show(this._task_item.info.task_id, index, info.info);
		}
	},
	HandleMoveJob : async function(info, index, new_index) {
		let msg_client = DeployClient.g_DPLWebLoginManager.msg_client;
		if (msg_client === undefined || !msg_client.IsConnected()) {
			g_AUITool.ShowNotice("提示", "当前还未连接成功!");
			return;
		}
		let msg = {};
		msg.task_id = this._task_item.info.task_id;
		msg.job_index = index;
		msg.target_index = new_index;
		let [error] = await ALittle.IMsgCommon.InvokeRPC(-616678126, msg_client, msg);
		if (error !== undefined) {
			g_AUITool.ShowNotice("提示", error);
		}
	},
	HandleCopyJob : async function(info, index) {
		let msg_client = DeployClient.g_DPLWebLoginManager.msg_client;
		if (msg_client === undefined || !msg_client.IsConnected()) {
			g_AUITool.ShowNotice("提示", "当前还未连接成功!");
			return;
		}
		let msg = {};
		msg.task_id = this._task_item.info.task_id;
		msg.job_index = index;
		let [error] = await ALittle.IMsgCommon.InvokeRPC(-2031251578, msg_client, msg);
		if (error !== undefined) {
			g_AUITool.ShowNotice("提示", error);
		}
	},
	HandleDeleteJob : async function(info, index) {
		let msg_client = DeployClient.g_DPLWebLoginManager.msg_client;
		if (msg_client === undefined || !msg_client.IsConnected()) {
			g_AUITool.ShowNotice("提示", "当前还未连接成功!");
			return;
		}
		let result = await g_AUITool.DeleteNotice("删除", "确定要删除该任务吗?");
		if (result !== "YES") {
			return;
		}
		let msg = {};
		msg.task_id = this._task_item.info.task_id;
		msg.job_index = index;
		let [error] = await ALittle.IMsgCommon.InvokeRPC(-1320965296, msg_client, msg);
		if (error !== undefined) {
			g_AUITool.ShowNotice("提示", error);
		}
	},
	HandleDeleteBuild : async function(info, index) {
		let msg_client = DeployClient.g_DPLWebLoginManager.msg_client;
		if (msg_client === undefined || !msg_client.IsConnected()) {
			g_AUITool.ShowNotice("提示", "当前还未连接成功!");
			return;
		}
		let result = await g_AUITool.DeleteNotice("删除", "确定要删除该构建信息吗?");
		if (result !== "YES") {
			return;
		}
		let msg = {};
		msg.task_id = this._task_item.info.task_id;
		msg.build_index = index;
		let [error] = await ALittle.IMsgCommon.InvokeRPC(1254025721, msg_client, msg);
		if (error !== undefined) {
			g_AUITool.ShowNotice("提示", error);
		}
	},
}, "DeployClient.DPLUITaskDetail");

}