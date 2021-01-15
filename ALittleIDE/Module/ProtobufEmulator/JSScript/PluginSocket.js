{
if (typeof Emulator === "undefined") window.Emulator = {};


if (Lua.ISocket === undefined) throw new Error(" extends class:Lua.ISocket is undefined");
Emulator.PluginSocket = JavaScript.Class(Lua.ISocket, {
	ReadMessage : function() {
		return new Promise((function(___COROUTINE, ___) {
			let func = _G["__SOCKET_ReadMessage"];
			if (func === undefined) {
				___COROUTINE(["can't find __SOCKET_ReadMessage", undefined]); return;
			}
			let [call_error, error, msg] = (function() { try { let ___VALUE = func.call(this); ___VALUE.splice(0, 0, undefined);  return ___VALUE; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
			if (call_error !== undefined) {
				___COROUTINE([call_error, undefined]); return;
			}
			___COROUTINE([error, msg]); return;
		}).bind(this));
	},
	WriteMessage : function(full_name, protobuf_msg) {
		let func = _G["__SOCKET_WriteMessage"];
		if (func === undefined) {
			return "can't find __SOCKET_WriteMessage";
		}
		let [call_error, error] = (function() { try { let ___VALUE = func.call(this, full_name, protobuf_msg); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
		if (call_error !== undefined) {
			return call_error;
		}
		if (error !== undefined) {
			return error;
		}
		g_GCenter.AddLogMessage(protobuf_msg);
		return undefined;
	},
	HandleMessage : function(msg) {
		g_GCenter.AddLogMessage(msg);
		let func = _G["__SOCKET_HandleMessage"];
		if (func === undefined) {
			return;
		}
		let error = (function() { try { func.call(this, msg); return undefined; } catch (___ERROR) { return ___ERROR.message; } }).call(this);
	},
}, "Emulator.PluginSocket");

}