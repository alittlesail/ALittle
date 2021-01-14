{
if (typeof DeployClient === "undefined") window.DeployClient = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(2082241964, "DeployServer.C2SStartTask", {
name : "DeployServer.C2SStartTask", ns_name : "DeployServer", rl_name : "C2SStartTask", hash_code : 2082241964,
name_list : ["task_id"],
type_list : ["int"],
option_map : {}
})
ALittle.RegStruct(-2035971543, "DeployServer.D_JobInfo", {
name : "DeployServer.D_JobInfo", ns_name : "DeployServer", rl_name : "D_JobInfo", hash_code : -2035971543,
name_list : ["job_type","job_name","status","progress","detail"],
type_list : ["int","string","int","double","DeployServer.JobInfoDetail"],
option_map : {}
})
ALittle.RegStruct(-2015558870, "DeployServer.NMoveJob", {
name : "DeployServer.NMoveJob", ns_name : "DeployServer", rl_name : "NMoveJob", hash_code : -2015558870,
name_list : ["task_id","job_index","target_index"],
type_list : ["int","int","int"],
option_map : {}
})
ALittle.RegStruct(1811432266, "DeployServer.D_BuildInfo", {
name : "DeployServer.D_BuildInfo", ns_name : "DeployServer", rl_name : "D_BuildInfo", hash_code : 1811432266,
name_list : ["create_time"],
type_list : ["int"],
option_map : {}
})
ALittle.RegStruct(-1662612614, "DeployServer.NUpdateTaskInfo", {
name : "DeployServer.NUpdateTaskInfo", ns_name : "DeployServer", rl_name : "NUpdateTaskInfo", hash_code : -1662612614,
name_list : ["task_id","task_name","task_desc","web_hook"],
type_list : ["int","string","string","List<string>"],
option_map : {}
})
ALittle.RegStruct(-1533563228, "DeployServer.S2CCreateTask", {
name : "DeployServer.S2CCreateTask", ns_name : "DeployServer", rl_name : "S2CCreateTask", hash_code : -1533563228,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(1487624699, "DeployServer.NCreateBuild", {
name : "DeployServer.NCreateBuild", ns_name : "DeployServer", rl_name : "NCreateBuild", hash_code : 1487624699,
name_list : ["task_id","build_info"],
type_list : ["int","DeployServer.D_BuildInfo"],
option_map : {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(1462309182, "DeployServer.NJobStatus", {
name : "DeployServer.NJobStatus", ns_name : "DeployServer", rl_name : "NJobStatus", hash_code : 1462309182,
name_list : ["task_id","index","status","progress"],
type_list : ["int","int","int","double"],
option_map : {}
})
ALittle.RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name : "ALittle.UIButtonEvent", ns_name : "ALittle", rl_name : "UIButtonEvent", hash_code : -1347278145,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(-1294478047, "DeployServer.S2CDeleteTask", {
name : "DeployServer.S2CDeleteTask", ns_name : "DeployServer", rl_name : "S2CDeleteTask", hash_code : -1294478047,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(1287526271, "DeployServer.C2SCreateTask", {
name : "DeployServer.C2SCreateTask", ns_name : "DeployServer", rl_name : "C2SCreateTask", hash_code : 1287526271,
name_list : ["task_name"],
type_list : ["string"],
option_map : {}
})
ALittle.RegStruct(-1243553967, "DeployServer.NCreateTask", {
name : "DeployServer.NCreateTask", ns_name : "DeployServer", rl_name : "NCreateTask", hash_code : -1243553967,
name_list : ["task_info"],
type_list : ["DeployServer.D_TaskInfo"],
option_map : {}
})
ALittle.RegStruct(1232578034, "DeployServer.JobInfoDetail", {
name : "DeployServer.JobInfoDetail", ns_name : "DeployServer", rl_name : "JobInfoDetail", hash_code : 1232578034,
name_list : ["batch_dir","batch_cmd","batch_param","deepcopy_src","deepcopy_dst","deepcopy_ext","copyfile_src","copyfile_file","copyfile_dst","virtualkey_exepath","virtualkey_cmd","wait_p_exit_exe_path","wait_p_exit_max_time","createprocess_dir","createprocess_cmd","createprocess_param","killprocess_exe_path"],
type_list : ["string","string","string","string","string","string","string","List<string>","string","string","List<string>","List<string>","int","string","string","string","List<string>"],
option_map : {}
})
ALittle.RegStruct(-1164681133, "DeployServer.NDeleteTask", {
name : "DeployServer.NDeleteTask", ns_name : "DeployServer", rl_name : "NDeleteTask", hash_code : -1164681133,
name_list : ["task_id"],
type_list : ["int"],
option_map : {}
})
ALittle.RegStruct(-1050312971, "DeployServer.NDeleteJob", {
name : "DeployServer.NDeleteJob", ns_name : "DeployServer", rl_name : "NDeleteJob", hash_code : -1050312971,
name_list : ["task_id","job_index"],
type_list : ["int","int"],
option_map : {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name : "ALittle.UIChangedEvent", ns_name : "ALittle", rl_name : "UIChangedEvent", hash_code : 958494922,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(917908039, "DeployServer.NCreateJob", {
name : "DeployServer.NCreateJob", ns_name : "DeployServer", rl_name : "NCreateJob", hash_code : 917908039,
name_list : ["task_id","job_index","job_info"],
type_list : ["int","int","DeployServer.D_JobInfo"],
option_map : {}
})
ALittle.RegStruct(816033453, "DeployServer.NTaskStatus", {
name : "DeployServer.NTaskStatus", ns_name : "DeployServer", rl_name : "NTaskStatus", hash_code : 816033453,
name_list : ["task_id","status","progress"],
type_list : ["int","int","double"],
option_map : {}
})
ALittle.RegStruct(808269380, "DeployServer.C2SDeleteTask", {
name : "DeployServer.C2SDeleteTask", ns_name : "DeployServer", rl_name : "C2SDeleteTask", hash_code : 808269380,
name_list : ["task_id"],
type_list : ["int"],
option_map : {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name : "ALittle.UIRButtonDownEvent", ns_name : "ALittle", rl_name : "UIRButtonDownEvent", hash_code : -641444818,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(625732643, "DeployServer.S2CStartTask", {
name : "DeployServer.S2CStartTask", ns_name : "DeployServer", rl_name : "S2CStartTask", hash_code : 625732643,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(-601303991, "DeployServer.S2CCopyTask", {
name : "DeployServer.S2CCopyTask", ns_name : "DeployServer", rl_name : "S2CCopyTask", hash_code : -601303991,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(-542744414, "DeployServer.S2CTaskList", {
name : "DeployServer.S2CTaskList", ns_name : "DeployServer", rl_name : "S2CTaskList", hash_code : -542744414,
name_list : ["task_list"],
type_list : ["List<DeployServer.D_TaskInfo>"],
option_map : {}
})
ALittle.RegStruct(-478034953, "DeployServer.C2SCopyTask", {
name : "DeployServer.C2SCopyTask", ns_name : "DeployServer", rl_name : "C2SCopyTask", hash_code : -478034953,
name_list : ["task_id"],
type_list : ["int"],
option_map : {}
})
ALittle.RegStruct(390627548, "DeployServer.D_TaskInfo", {
name : "DeployServer.D_TaskInfo", ns_name : "DeployServer", rl_name : "D_TaskInfo", hash_code : 390627548,
name_list : ["task_id","task_name","task_desc","web_hook","create_time","status","progress","job_list","build_list"],
type_list : ["int","string","string","List<string>","int","int","double","List<DeployServer.D_JobInfo>","List<DeployServer.D_BuildInfo>"],
option_map : {}
})
ALittle.RegStruct(-369409021, "DeployClient.TaskItemInfo", {
name : "DeployClient.TaskItemInfo", ns_name : "DeployClient", rl_name : "TaskItemInfo", hash_code : -369409021,
name_list : ["item","info","_button","_status","detail"],
type_list : ["ALittle.DisplayObject","DeployServer.D_TaskInfo","ALittle.DisplayObject","ALittle.DisplayObject","DeployClient.DPLUITaskDetail"],
option_map : {}
})
ALittle.RegStruct(-206375730, "DeployServer.NDeleteBuild", {
name : "DeployServer.NDeleteBuild", ns_name : "DeployServer", rl_name : "NDeleteBuild", hash_code : -206375730,
name_list : ["task_id","build_index"],
type_list : ["int","int"],
option_map : {}
})
ALittle.RegStruct(-173628832, "DeployServer.NModifyJob", {
name : "DeployServer.NModifyJob", ns_name : "DeployServer", rl_name : "NModifyJob", hash_code : -173628832,
name_list : ["task_id","job_index","job_info"],
type_list : ["int","int","DeployServer.D_JobInfo"],
option_map : {}
})

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
DeployClient.DPLUITaskCenter = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function() {
		this._group = new Map();
		this._item_map = new Map();
	},
	System_SetVDragCursor : function(event) {
		ALittle.System_SetVDragCursor();
	},
	System_SetNormalCursor : function(event) {
		ALittle.System_SetNormalCursor();
	},
	System_SetHDragCursor : function(event) {
		ALittle.System_SetHDragCursor();
	},
	System_SetHVDragCursor : function(event) {
		ALittle.System_SetHVDragCursor();
	},
	HandleGrid3UpResizeDrag : function(event) {
		let up_size = this._task_grid3.up_size;
		up_size = up_size + event.delta_x;
		let max_size = this._task_grid3.width - this._task_grid3.down_size - 50;
		if (up_size > max_size) {
			up_size = max_size;
		}
		if (up_size < 100) {
			up_size = 100;
		}
		this._task_grid3.up_size = up_size;
	},
	HandleGrid3DownResizeDrag : function(event) {
		let down_size = this._task_grid3.down_size;
		down_size = down_size - event.delta_x;
		let max_size = this._task_grid3.width - this._task_grid3.down_size - 50;
		if (down_size > max_size) {
			down_size = max_size;
		}
		if (down_size < 100) {
			down_size = 100;
		}
		this._task_grid3.down_size = down_size;
	},
	AddTaskItem : function(info) {
		let task_info = {};
		task_info.item = DeployClient.g_Control.CreateControl("dpl_task_item", task_info);
		task_info.info = info;
		task_info._button.text = info.task_name;
		task_info._button._user_data = task_info;
		task_info._button.AddEventListener(___all_struct.get(-641444818), this, this.HandleItemRButtonDown);
		task_info._button.AddEventListener(___all_struct.get(958494922), this, this.HandleItemChanged);
		task_info._button.group = this._group;
		this._scroll_list.AddChild(task_info.item);
		if (info.status === 0) {
			task_info._status.text = "";
		} else {
			task_info._status.text = ALittle.Math_Floor(info.progress * 100) / 100 + "%";
		}
		this._item_map.set(info.task_id, task_info);
	},
	AddJobItem : function(task_id, job_index, info) {
		let task_info = this._item_map.get(task_id);
		if (task_info === undefined) {
			return;
		}
		if (job_index === undefined || job_index <= 0 || job_index > ALittle.List_Len(task_info.info.job_list)) {
			ALittle.List_Push(task_info.info.job_list, info);
			job_index = ALittle.List_Len(task_info.info.job_list);
		} else {
			ALittle.List_Insert(task_info.info.job_list, job_index, info);
		}
		if (task_info.detail !== undefined) {
			task_info.detail.AddJobItem(job_index, info);
		}
	},
	AddBuildItem : function(task_id, info) {
		let task_info = this._item_map.get(task_id);
		if (task_info === undefined) {
			return;
		}
		ALittle.List_Push(task_info.info.build_list, info);
		if (task_info.detail !== undefined) {
			task_info.detail.AddBuildItem(info);
		}
	},
	HandleItemRButtonDown : function(event) {
		let task_info = event.target._user_data;
		let menu = ALittle.NewObject(AUIPlugin.AUIRightMenu);
		if (task_info.info.status === 0) {
			menu.AddItem("执行", this.HandleStartTask.bind(this, task_info));
		}
		menu.AddItem("复制", this.HandleCopyTask.bind(this, task_info));
		if (task_info.info.status === 0) {
			menu.AddItem("删除", this.HandleDeleteTask.bind(this, task_info));
		}
		menu.Show();
	},
	HandleItemChanged : function(event) {
		let task_info = event.target._user_data;
		if (event.target.selected) {
			if (task_info.detail === undefined) {
				task_info.detail = DeployClient.g_Control.CreateControl("dpl_task_detail");
				this._task_detail_container.AddChild(task_info.detail);
				task_info.detail.Init(task_info);
			}
			task_info.detail.Show();
		} else {
			if (task_info.detail !== undefined) {
				task_info.detail.Hide();
			}
		}
	},
	HandleStartTask : async function(task_info) {
		let msg_client = DeployClient.g_DPLWebLoginManager.msg_client;
		if (msg_client === undefined || !msg_client.IsConnected()) {
			g_AUITool.ShowNotice("提示", "当前还未连接成功!");
			return;
		}
		let msg = {};
		msg.task_id = task_info.info.task_id;
		let [error] = await ALittle.IMsgCommon.InvokeRPC(2082241964, msg_client, msg);
		if (error !== undefined) {
			g_AUITool.ShowNotice("提示", error);
		}
	},
	HandleCopyTask : async function(task_info) {
		let msg_client = DeployClient.g_DPLWebLoginManager.msg_client;
		if (msg_client === undefined || !msg_client.IsConnected()) {
			g_AUITool.ShowNotice("提示", "当前还未连接成功!");
			return;
		}
		let msg = {};
		msg.task_id = task_info.info.task_id;
		let [error] = await ALittle.IMsgCommon.InvokeRPC(-478034953, msg_client, msg);
		if (error !== undefined) {
			g_AUITool.ShowNotice("提示", error);
		}
	},
	HandleDeleteTask : async function(task_info) {
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
		msg.task_id = task_info.info.task_id;
		let [error] = await ALittle.IMsgCommon.InvokeRPC(808269380, msg_client, msg);
		if (error !== undefined) {
			g_AUITool.ShowNotice("提示", error);
		}
	},
	RemoveTaskItem : function(task_id) {
		let task_info = this._item_map.get(task_id);
		if (task_info === undefined) {
			return;
		}
		task_info._button.group = undefined;
		this._item_map.delete(task_id);
		this._scroll_list.RemoveChild(task_info.item);
		if (task_info.detail !== undefined) {
			this._task_detail_container.RemoveChild(task_info.detail);
		}
	},
	UpdateTaskItem : function(info) {
		let task_info = this._item_map.get(info.task_id);
		if (task_info === undefined) {
			return;
		}
		task_info.info.task_name = info.task_name;
		task_info._button.text = info.task_name;
		task_info.info.task_desc = info.task_desc;
		task_info.info.web_hook = info.web_hook;
		if (task_info.detail !== undefined) {
			task_info.detail.UpdateTaskInfo();
		}
	},
	UpdateJobItem : function(info) {
		let task_info = this._item_map.get(info.task_id);
		if (task_info === undefined) {
			return;
		}
		let job_info = task_info.info.job_list[info.job_index - 1];
		if (job_info === undefined) {
			return;
		}
		task_info.info.job_list[info.job_index - 1] = info.job_info;
		if (task_info.detail !== undefined) {
			task_info.detail.UpdateJobInfo(info.job_index);
		}
	},
	RemoveJobItem : function(task_id, job_index) {
		let task_info = this._item_map.get(task_id);
		if (task_info === undefined) {
			return;
		}
		if (task_info.detail !== undefined) {
			task_info.detail.RemoveJobItem(job_index);
		}
		ALittle.List_Remove(task_info.info.job_list, job_index);
	},
	MoveJobItem : function(task_id, job_index, target_index) {
		let task_info = this._item_map.get(task_id);
		if (task_info === undefined) {
			return;
		}
		if (task_info.detail !== undefined) {
			task_info.detail.MoveJobItem(job_index, target_index);
		}
		let job = task_info.info.job_list[job_index - 1];
		ALittle.List_Remove(task_info.info.job_list, job_index);
		let job_len = ALittle.List_Len(task_info.info.job_list);
		if (target_index <= 0 || target_index > job_len) {
			ALittle.List_Push(task_info.info.job_list, job);
		} else {
			ALittle.List_Insert(task_info.info.job_list, target_index, job);
		}
	},
	RemoveBuildItem : function(task_id, build_index) {
		let task_info = this._item_map.get(task_id);
		if (task_info === undefined) {
			return;
		}
		if (task_info.detail !== undefined) {
			task_info.detail.RemoveBuildItem(build_index);
		}
		ALittle.List_Remove(task_info.info.build_list, build_index);
	},
	RemoveAllTaskItem : function() {
		this._item_map = new Map();
		this._scroll_list.RemoveAllChild();
		this._task_detail_container.RemoveAllChild();
	},
	UpdateTaskStatus : function(info) {
		let task_info = this._item_map.get(info.task_id);
		if (task_info === undefined) {
			return;
		}
		task_info.info.status = info.status;
		task_info.info.progress = info.progress;
		if (info.status === 0) {
			task_info._status.text = "";
		} else {
			task_info._status.text = ALittle.Math_Floor(info.progress * 100) / 100 + "%";
		}
	},
	UpdateJobStatus : function(msg) {
		let task_info = this._item_map.get(msg.task_id);
		if (task_info === undefined) {
			return;
		}
		let job_info = task_info.info.job_list[msg.index - 1];
		if (job_info === undefined) {
			return;
		}
		job_info.status = msg.status;
		job_info.progress = msg.progress;
		if (task_info.detail !== undefined) {
			task_info.detail.UpdateJobInfo(msg.index);
		}
	},
	HandleNewTaskClick : async function(event) {
		let msg_client = DeployClient.g_DPLWebLoginManager.msg_client;
		if (msg_client === undefined || !msg_client.IsConnected()) {
			g_AUITool.ShowNotice("提示", "当前还未连接成功!");
			return;
		}
		let [x, y] = event.target.LocalToGlobal();
		let result = await g_AUITool.ShowRename("", x, y + event.target.height, 200);
		if (result === undefined || result === "") {
			return;
		}
		let msg = {};
		msg.task_name = result;
		let [error] = await ALittle.IMsgCommon.InvokeRPC(1287526271, msg_client, msg);
		if (error !== undefined) {
			g_AUITool.ShowNotice("提示", error);
		}
	},
}, "DeployClient.DPLUITaskCenter");

DeployClient.HandleS2CTaskList = function(sender, msg) {
	DeployClient.g_DPLCenter.center.task_center.RemoveAllTaskItem();
	let ___OBJECT_1 = msg.task_list;
	for (let index = 1; index <= ___OBJECT_1.length; ++index) {
		let info = ___OBJECT_1[index - 1];
		if (info === undefined) break;
		DeployClient.g_DPLCenter.center.task_center.AddTaskItem(info);
	}
}

ALittle.RegMsgCallback(-542744414, DeployClient.HandleS2CTaskList)
DeployClient.HandleS2CCreateTask = function(sender, msg) {
	DeployClient.g_DPLCenter.center.task_center.AddTaskItem(msg.task_info);
}

ALittle.RegMsgCallback(-1243553967, DeployClient.HandleS2CCreateTask)
DeployClient.HandleNTaskStatus = function(sender, msg) {
	DeployClient.g_DPLCenter.center.task_center.UpdateTaskStatus(msg);
}

ALittle.RegMsgCallback(816033453, DeployClient.HandleNTaskStatus)
DeployClient.HandleNDeleteTask = function(sender, msg) {
	DeployClient.g_DPLCenter.center.task_center.RemoveTaskItem(msg.task_id);
}

ALittle.RegMsgCallback(-1164681133, DeployClient.HandleNDeleteTask)
DeployClient.HandleNUpdateTaskInfo = function(sender, msg) {
	DeployClient.g_DPLCenter.center.task_center.UpdateTaskItem(msg);
}

ALittle.RegMsgCallback(-1662612614, DeployClient.HandleNUpdateTaskInfo)
DeployClient.HandleNCreateJob = function(sender, msg) {
	DeployClient.g_DPLCenter.center.task_center.AddJobItem(msg.task_id, msg.job_index, msg.job_info);
}

ALittle.RegMsgCallback(917908039, DeployClient.HandleNCreateJob)
DeployClient.HandleNJobStatus = function(sender, msg) {
	DeployClient.g_DPLCenter.center.task_center.UpdateJobStatus(msg);
}

ALittle.RegMsgCallback(1462309182, DeployClient.HandleNJobStatus)
DeployClient.HandleNModifyJob = function(sender, msg) {
	DeployClient.g_DPLCenter.center.task_center.UpdateJobItem(msg);
}

ALittle.RegMsgCallback(-173628832, DeployClient.HandleNModifyJob)
DeployClient.HandleNDeleteJob = function(sender, msg) {
	DeployClient.g_DPLCenter.center.task_center.RemoveJobItem(msg.task_id, msg.job_index);
}

ALittle.RegMsgCallback(-1050312971, DeployClient.HandleNDeleteJob)
DeployClient.HandleNMoveJob = function(sender, msg) {
	DeployClient.g_DPLCenter.center.task_center.MoveJobItem(msg.task_id, msg.job_index, msg.target_index);
}

ALittle.RegMsgCallback(-2015558870, DeployClient.HandleNMoveJob)
DeployClient.HandleNCreateBuild = function(sender, msg) {
	DeployClient.g_DPLCenter.center.task_center.AddBuildItem(msg.task_id, msg.build_info);
}

ALittle.RegMsgCallback(1487624699, DeployClient.HandleNCreateBuild)
DeployClient.HandleNDeleteBuild = function(sender, msg) {
	DeployClient.g_DPLCenter.center.task_center.RemoveBuildItem(msg.task_id, msg.build_index);
}

ALittle.RegMsgCallback(-206375730, DeployClient.HandleNDeleteBuild)
}