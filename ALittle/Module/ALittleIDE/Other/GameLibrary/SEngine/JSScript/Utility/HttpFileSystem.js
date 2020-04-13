{
if (typeof ALittle === "undefined") ALittle = {};


if (ALittle.IHttpFileReceiverNative === undefined) throw new Error(" extends class:ALittle.IHttpFileReceiverNative is undefined");
ALittle.HttpFileReceiverNative = JavaScript.Class(ALittle.IHttpFileReceiverNative, {
	Close : function(http_id) {
		__CPPAPI_ServerSchedule.HttpClose(http_id);
	},
	SendString : function(http_id, content) {
		__CPPAPI_ServerSchedule.HttpSendString(http_id, content);
	},
	StartReceiveFile : function(http_id, file_path, start_size) {
		__CPPAPI_ServerSchedule.HttpStartReceiveFile(http_id, file_path, start_size);
	},
}, "ALittle.HttpFileReceiverNative");

let HttpFileReceiver = JavaScript.Template(ALittle.HttpFileReceiverTemplate, "ALittle.HttpFileReceiverTemplate<ALittle.HttpFileReceiverNative>", ALittle.HttpFileReceiverNative);
ALittle.HttpFileSystem = JavaScript.Class(undefined, {
	Ctor : function() {
		this._http_file_map = new Map();
	},
	HandleHttpFileTask : async function(http_id, path, callback, value_map) {
		await this.HandleHttpFileTaskImpl(http_id, path, callback, value_map);
	},
	HandleHttpFileTaskImpl : function(http_id, path, callback, value_map) {
		return new Promise((async function(___COROUTINE, ___) {
			let file_client = ALittle.NewObject(ALittle.HttpFileReceiver, http_id, ___COROUTINE);
			this._http_file_map.set(http_id, file_client);
			let error = undefined;
			let result = undefined;
			if (callback === undefined) {
				error = await file_client.StartReceiveFile("", 0);
			} else {
				[error, result] = await (async function() { try { let ___VALUE = await callback.call(file_client, value_map); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
			}
			if (!file_client.received) {
				error = await file_client.StartReceiveFile("", 0);
			}
			this._http_file_map.delete(http_id);
			if (error !== undefined) {
				let map = {};
				map["error"] = error;
				file_client.SendString(lua.json.encode(map));
				___COROUTINE(); return;
			}
			if (result === undefined) {
				let map = {};
				map["error"] = "接口没有返回任何内容";
				file_client.SendString(lua.json.encode(map));
				___COROUTINE(); return;
			}
			file_client.SendString(lua.json.encode(result));
			___COROUTINE();
		}).bind(this));
	},
	HandleHttpFileCompletedTask : function(http_id, reason) {
		let file_client = this._http_file_map.get(http_id);
		if (file_client === undefined) {
			__CPPAPI_ServerSchedule.HttpClose(http_id);
			return;
		}
		file_client.HandleReceiveResult(reason);
	},
}, "ALittle.HttpFileSystem");

window.A_HttpFileSystem = ALittle.NewObject(ALittle.HttpFileSystem);
}