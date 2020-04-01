{
if (typeof JavaScript === "undefined") JavaScript = {};


JavaScript.JSystem_GetDeviceID = function() {
	let id = undefined;
	let json = undefined;
	if (document.cookie !== undefined && document.cookie !== "") {
		let error = undefined;
		[error, json] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, document.cookie); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } })();
		if (error !== undefined) {
			json = undefined;
		}
	}
	if (json !== undefined) {
		id = json["device_id"];
	}
	if (id === undefined) {
		let rand = ALittle.Math_RandomInt(0, 10000);
		let time = ALittle.Time_GetCurTime();
		if (json === undefined) {
			json = {};
		}
		id = "device_id_" + rand + "_" + time;
		json["device_id"] = id;
		document.cookie = ALittle.String_JsonEncode(json);
	}
	return id;
}

window.A_PixiApp = undefined;
JavaScript.JSystem_CreateView = function(title, width, height, flag, scale) {
	if (A_PixiApp !== undefined) {
		return true;
	}
	let data = {};
	data.width = width;
	data.height = height;
	A_PixiApp = new PIXI.Application(data);
	document.body.appendChild(A_PixiApp.view);
	document.title = title;
	return true;
}

JavaScript.JSystem_SetViewTitle = function(title) {
	document.title = title;
	return true;
}

JavaScript.JSystem_Render = function() {
	if (A_PixiApp === undefined) {
		return false;
	}
	A_PixiApp.render();
	return true;
}

}