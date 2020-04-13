{
if (typeof ALittle === "undefined") ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(976782632, "LogServer.LogEventInfo", {
name : "LogServer.LogEventInfo", ns_name : "LogServer", rl_name : "LogEventInfo", hash_code : 976782632,
name_list : ["account_id","main_type","sub_type","res_type","res_id","res_num","res_count","param_1","param_2","param_3","param_4","param_5","param_string","create_time","log_time"],
type_list : ["int","int","int","int","int","int","int","int","int","int","int","int","string","int","int"],
option_map : {index : "account_id,main_type,sub_type,create_time"}
})
ALittle.RegStruct(200159280, "LogServer.EmptyResult", {
name : "LogServer.EmptyResult", ns_name : "LogServer", rl_name : "EmptyResult", hash_code : 200159280,
name_list : [],
type_list : [],
option_map : {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})

ALittle.LogEventMainType = {
	LEMT_OPS : 1,
}

ALittle.LogEventSubType = {
	LEST_OPS_ADDRES : 1,
}

ALittle.LogEventSystem = JavaScript.Class(undefined, {
	Ctor : function() {
		this._init = false;
		this._list = [];
		this._count = 0;
	},
	HandleSessionConnected : async function(event) {
		if (event.route_num !== ALittle.RouteType.RT_LOG && event.route_num !== ALittle.RouteNum.RN_DEFAULT) {
			return;
		}
		this._session = event.session;
		await this.Flush();
	},
	HandleSessionDisconnected : function(event) {
		if (event.route_num !== ALittle.RouteType.RT_LOG && event.route_num !== ALittle.RouteNum.RN_DEFAULT) {
			return;
		}
		this._session = undefined;
	},
	Flush : function() {
		return new Promise((async function(___COROUTINE, ___) {
			let ___OBJECT_1 = this._list;
			for (let index = 1; index <= ___OBJECT_1.length; ++index) {
				let info = ___OBJECT_1[index - 1];
				if (info === undefined) break;
				await this.Send(info);
			}
			this._list = [];
			this._count = 0;
			___COROUTINE();
		}).bind(this));
	},
	Send : function(info) {
		return new Promise((function(___COROUTINE, ___) {
			let [error, result] = await ALittle.IMsgCommon.InvokeRPC(976782632, this._session, info);
			if (error !== undefined) {
				ALittle.Warn("日志发送失败:" + error + " 数据:" + lua.json.encode(info));
			}
			___COROUTINE();
		}).bind(this));
	},
	SendLogEvent : async function(info) {
		if (!this._init) {
			A_SessionSystem.AddConnectSession(ALittle.RouteType.RT_LOG, ALittle.RouteNum.RN_DEFAULT);
			A_SessionSystem.AddEventListener(___all_struct.get(888437463), this, this.HandleSessionConnected);
			A_SessionSystem.AddEventListener(___all_struct.get(-36908822), this, this.HandleSessionDisconnected);
			this._init = true;
		}
		if (this._session === undefined) {
			ALittle.List_Push(this._list, info);
			++ this._count;
			if (this._count > 1000) {
				ALittle.Warn("消息队列太大，移除掉第一个, 数据:" + lua.json.encode(this._list[1 - 1]));
				lua.table.remove(this._list, 1);
				-- this._count;
			}
		} else {
			await this.Send(info);
		}
	},
}, "ALittle.LogEventSystem");

window.A_LogEventSystem = ALittle.NewObject(ALittle.LogEventSystem);
}