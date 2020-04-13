{
if (typeof ALittle === "undefined") ALittle = {};


if (ALittle.IHttpReceiverNative === undefined) throw new Error(" extends class:ALittle.IHttpReceiverNative is undefined");
ALittle.HttpReceiverNative = JavaScript.Class(ALittle.IHttpReceiverNative, {
	Close : function(http_id) {
		__CPPAPI_ServerSchedule.HttpClose(http_id);
	},
	SendString : function(http_id, content) {
		__CPPAPI_ServerSchedule.HttpSendString(http_id, content);
	},
	SendFile : function(http_id, file_path, start_size) {
		__CPPAPI_ServerSchedule.HttpSendFile(http_id, file_path, start_size);
	},
}, "ALittle.HttpReceiverNative");

let HttpReceiver = JavaScript.Template(ALittle.HttpReceiverTemplate, "ALittle.HttpReceiverTemplate<ALittle.HttpReceiverNative>", ALittle.HttpReceiverNative);
ALittle.HttpSystem = JavaScript.Class(undefined, {
	Ctor : function() {
		this._request_map = new Map();
		this._id_creator = ALittle.NewObject(ALittle.SafeIDCreator);
	},
	HandleHttpTask : async function(http_id, callback, value_map) {
		let client = ALittle.NewObject(ALittle.HttpReceiver, http_id);
		let [error, result] = await (async function() { try { let ___VALUE = await callback.call(client, value_map); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } })();
		if (error !== undefined) {
			let map = {};
			map["error"] = error;
			client.SendString(lua.json.encode(map));
			return;
		}
		if (result === undefined) {
			let map = {};
			map["error"] = "接口没有返回任何内容";
			client.SendString(lua.json.encode(map));
			return;
		}
		client.SendString(lua.json.encode(result));
	},
	HandleHttpDownloadTask : async function(http_id, callback, value_map) {
		let client = ALittle.NewObject(ALittle.HttpReceiver, http_id);
		let [error, file_path, start_size] = await (async function() { try { let ___VALUE = await callback.call(client, value_map); ___VALUE.splice(0, 0, undefined);  return ___VALUE; } catch (___ERROR) { return [___ERROR.message]; } })();
		if (error !== undefined) {
			client.Close();
			return;
		}
		if (file_path === undefined) {
			client.Close();
			return;
		}
		client.SendFile(file_path, start_size);
	},
	Get : function(url) {
		return new Promise((function(___COROUTINE, ___) {
			if (___COROUTINE === undefined) {
				___COROUTINE(["当前不是协程", undefined]); return;
			}
			let id = this._id_creator.CreateID();
			this._request_map.set(id, ___COROUTINE);
			__CPPAPI_ServerSchedule.HttpGet(id, url);
			return;
			___COROUTINE();
		}).bind(this));
	},
	PostJson : function(url, content) {
		return new Promise((function(___COROUTINE, ___) {
			if (___COROUTINE === undefined) {
				___COROUTINE(["当前不是协程", undefined]); return;
			}
			let id = this._id_creator.CreateID();
			this._request_map.set(id, ___COROUTINE);
			__CPPAPI_ServerSchedule.HttpPost(id, url, "application/json", lua.json.encode(content));
			return;
			___COROUTINE();
		}).bind(this));
	},
	HandleHttpSucceed : function(id, response) {
		this._id_creator.ReleaseID(id);
		let thread = this._request_map.get(id);
		this._request_map.delete(id);
		let [result, reason] = lua.coroutine.resume(thread, undefined, response);
		if (result !== true) {
			ALittle.Error(reason);
		}
	},
	HandleHttpFailed : function(id, reason) {
		this._id_creator.ReleaseID(id);
		let thread = this._request_map.get(id);
		this._request_map.delete(id);
		let [result, reason] = lua.coroutine.resume(thread, reason, undefined);
		if (result !== true) {
			ALittle.Error(reason);
		}
	},
}, "ALittle.HttpSystem");

window.A_HttpSystem = ALittle.NewObject(ALittle.HttpSystem);
}