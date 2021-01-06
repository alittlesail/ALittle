{
if (typeof JavaScript === "undefined") window.JavaScript = {};


let __pixel_ratio = 1;
let KEY_CODE_MAP = new Map();
let SCAN_CODE_MAP = new Map();
KEY_CODE_MAP.set(65, 97);
SCAN_CODE_MAP.set(65, 4);
KEY_CODE_MAP.set(83, 115);
SCAN_CODE_MAP.set(83, 22);
KEY_CODE_MAP.set(68, 100);
SCAN_CODE_MAP.set(68, 7);
KEY_CODE_MAP.set(87, 119);
SCAN_CODE_MAP.set(87, 26);
KEY_CODE_MAP.set(71, 103);
SCAN_CODE_MAP.set(71, 10);
KEY_CODE_MAP.set(72, 104);
SCAN_CODE_MAP.set(72, 11);
KEY_CODE_MAP.set(74, 106);
SCAN_CODE_MAP.set(74, 13);
KEY_CODE_MAP.set(75, 107);
SCAN_CODE_MAP.set(75, 14);
KEY_CODE_MAP.set(37, 1073741904);
SCAN_CODE_MAP.set(37, 80);
KEY_CODE_MAP.set(40, 1073741905);
SCAN_CODE_MAP.set(40, 81);
KEY_CODE_MAP.set(39, 1073741903);
SCAN_CODE_MAP.set(39, 79);
KEY_CODE_MAP.set(38, 1073741906);
SCAN_CODE_MAP.set(38, 82);
KEY_CODE_MAP.set(97, 1073741913);
SCAN_CODE_MAP.set(97, 89);
KEY_CODE_MAP.set(98, 1073741914);
SCAN_CODE_MAP.set(98, 90);
KEY_CODE_MAP.set(100, 1073741916);
SCAN_CODE_MAP.set(100, 92);
KEY_CODE_MAP.set(101, 1073741917);
SCAN_CODE_MAP.set(101, 93);
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
		if (window.wx === undefined) {
			document.cookie = ALittle.String_JsonEncode(json);
		}
	}
	return id;
}

window.A_PixiApp = undefined;
let JSystem_FingerDown = function(event) {
	let func = window["__ALITTLEAPI_FingerDown"];
	if (func === undefined) {
		return;
	}
	let offsetLeft = 0;
	let offsetTop = 0;
	if (event.srcElement !== undefined) {
		offsetLeft = event.srcElement.offsetLeft;
		offsetTop = event.srcElement.offsetTop;
	}
	let ___OBJECT_1 = event.changedTouches;
	for (let index = 1; index <= ___OBJECT_1.length; ++index) {
		let touch = ___OBJECT_1[index - 1];
		if (touch === undefined) break;
		func((touch.pageX - offsetLeft) / A_PixiApp.stage.scale.x * __pixel_ratio, (touch.pageY - offsetTop) / A_PixiApp.stage.scale.y * __pixel_ratio, touch.identifier, 1);
	}
}

let JSystem_FingerUp = function(event) {
	let func = window["__ALITTLEAPI_FingerUp"];
	if (func === undefined) {
		return;
	}
	let offsetLeft = 0;
	let offsetTop = 0;
	if (event.srcElement !== undefined) {
		offsetLeft = event.srcElement.offsetLeft;
		offsetTop = event.srcElement.offsetTop;
	}
	let ___OBJECT_2 = event.changedTouches;
	for (let index = 1; index <= ___OBJECT_2.length; ++index) {
		let touch = ___OBJECT_2[index - 1];
		if (touch === undefined) break;
		func((touch.pageX - offsetLeft) / A_PixiApp.stage.scale.x * __pixel_ratio, (touch.pageY - offsetTop) / A_PixiApp.stage.scale.y * __pixel_ratio, touch.identifier, 1);
	}
}

let JSystem_FingerMoved = function(event) {
	let func = window["__ALITTLEAPI_FingerMoved"];
	if (func === undefined) {
		return;
	}
	let offsetLeft = 0;
	let offsetTop = 0;
	if (event.srcElement !== undefined) {
		offsetLeft = event.srcElement.offsetLeft;
		offsetTop = event.srcElement.offsetTop;
	}
	let ___OBJECT_3 = event.changedTouches;
	for (let index = 1; index <= ___OBJECT_3.length; ++index) {
		let touch = ___OBJECT_3[index - 1];
		if (touch === undefined) break;
		func((touch.pageX - offsetLeft) / A_PixiApp.stage.scale.x * __pixel_ratio, (touch.pageY - offsetTop) / A_PixiApp.stage.scale.y * __pixel_ratio, touch.identifier, 1);
	}
}

let JSystem_MouseMoved = function(event) {
	let func = window["__ALITTLEAPI_MouseMoved"];
	if (func === undefined) {
		return;
	}
	func((event.pageX - event.srcElement.offsetLeft) / A_PixiApp.stage.scale.x, (event.pageY - event.srcElement.offsetTop) / A_PixiApp.stage.scale.y);
}

let JSystem_MouseDown = function(event) {
	let func = undefined;
	if (event.which === 1) {
		func = window["__ALITTLEAPI_LButtonDown"];
	} else if (event.which === 2) {
		func = window["__ALITTLEAPI_MButtonDown"];
	} else if (event.which === 3) {
		func = window["__ALITTLEAPI_RButtonDown"];
	}
	if (func === undefined) {
		return;
	}
	func((event.pageX - event.srcElement.offsetLeft) / A_PixiApp.stage.scale.x, (event.pageY - event.srcElement.offsetTop) / A_PixiApp.stage.scale.y, 1);
}

let JSystem_MouseUp = function(event) {
	let func = undefined;
	if (event.which === 1) {
		func = window["__ALITTLEAPI_LButtonUp"];
	} else if (event.which === 2) {
		func = window["__ALITTLEAPI_MButtonUp"];
	} else if (event.which === 3) {
		func = window["__ALITTLEAPI_RButtonUp"];
	}
	if (func === undefined) {
		return;
	}
	func((event.pageX - event.srcElement.offsetLeft) / A_PixiApp.stage.scale.x, (event.pageY - event.srcElement.offsetTop) / A_PixiApp.stage.scale.y);
}

let JSystem_MouseWheel = function(event) {
	let func = window["__ALITTLEAPI_MouseWheel"];
	if (func === undefined) {
		return;
	}
	let x = event.wheelDelta;
	if (x === undefined) {
		x = event.detail;
	}
	let y = event.wheelDelta;
	if (y === undefined) {
		y = event.detail;
	}
	func(x, y);
}

let JSystem_MouseOut = function(event) {
	let func = window["__ALITTLEAPI_WindowLeave"];
	if (func === undefined) {
		return;
	}
	if (event.pageX - event.srcElement.offsetLeft > 0 && event.pageY - event.srcElement.offsetTop > 0) {
		return;
	}
	func();
}

let JSystem_KeyDown = function(event) {
	let func = window["__ALITTLEAPI_KeyDown"];
	if (func === undefined) {
		return;
	}
	let mod = 0;
	if (event.altKey) {
		mod = 0x0300 | mod;
	}
	if (event.ctrlKey) {
		mod = 0x00c0 | mod;
	}
	if (event.shiftKey) {
		mod = 0x0003 | mod;
	}
	let key_code = KEY_CODE_MAP.get(event.keyCode);
	if (key_code === undefined) {
		key_code = 0;
	}
	let scan_code = SCAN_CODE_MAP.get(event.keyCode);
	if (scan_code === undefined) {
		scan_code = 0;
	}
	func(mod, key_code, scan_code);
}

let JSystem_KeyUp = function(event) {
	let func = window["__ALITTLEAPI_KeyUp"];
	if (func === undefined) {
		return;
	}
	let mod = 0;
	if (event.altKey) {
		mod = 0x0300 | mod;
	}
	if (event.ctrlKey) {
		mod = 0x00c0 | mod;
	}
	if (event.shiftKey) {
		mod = 0x0003 | mod;
	}
	let key_code = KEY_CODE_MAP.get(event.keyCode);
	if (key_code === undefined) {
		key_code = 0;
	}
	let scan_code = SCAN_CODE_MAP.get(event.keyCode);
	if (scan_code === undefined) {
		scan_code = 0;
	}
	func(mod, key_code, scan_code);
}

JavaScript.JSystem_CreateView = function(title, width, height, flag, scale) {
	if (A_PixiApp !== undefined) {
		return true;
	}
	let data = {};
	if (window.wx !== undefined) {
		let info = window.wx.getSystemInfoSync();
		__pixel_ratio = info.pixelRatio;
		data.view = window.canvas;
	} else {
		data.forceCanvas = !PIXI.utils.isWebGLSupported();
	}
	data.width = ALittle.Math_Floor(width * scale);
	data.height = ALittle.Math_Floor(height * scale);
	A_PixiApp = new PIXI.Application(data);
	document.body.appendChild(A_PixiApp.view);
	if (window.wx === undefined) {
		document.title = title;
	}
	A_PixiApp.stage.scale.x = scale;
	A_PixiApp.stage.scale.y = scale;
	if (window.wx !== undefined) {
		window.wx.onTouchStart(JSystem_FingerDown);
		window.wx.onTouchMove(JSystem_FingerMoved);
		window.wx.onTouchEnd(JSystem_FingerUp);
		window.wx.onTouchCancel(JSystem_FingerUp);
	} else if (ALittle.System_IsPhone()) {
		A_PixiApp.view.ontouchstart = JSystem_FingerDown;
		A_PixiApp.view.ontouchmove = JSystem_FingerMoved;
		A_PixiApp.view.ontouchend = JSystem_FingerUp;
		A_PixiApp.view.ontouchcancel = JSystem_FingerUp;
	} else {
		A_PixiApp.view.onmousedown = JSystem_MouseDown;
		A_PixiApp.view.onmousemove = JSystem_MouseMoved;
		A_PixiApp.view.onmouseup = JSystem_MouseUp;
		A_PixiApp.view.onmousewheel = JSystem_MouseWheel;
		A_PixiApp.view.onmouseout = JSystem_MouseOut;
		document.onkeydown = JSystem_KeyDown;
		document.onkeyup = JSystem_KeyUp;
	}
	A_JDisplaySystem.AddToStage(A_PixiApp.stage);
	let func = window["__ALITTLEAPI_ViewResized"];
	if (func !== undefined) {
		func(width, height);
	}
	window.onresize = JavaScript.JSystem_HandleViewResized;
	A_PixiApp.ticker.add(JavaScript.JSystem_MainLoop);
	return true;
}

JavaScript.JSystem_HandleViewResized = function() {
	let func = window["__ALITTLEAPI_ViewResized"];
	if (func !== undefined) {
		func(ALittle.System_GetScreenWidth(), ALittle.System_GetScreenHeight());
	}
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

JavaScript.JSystem_GetStage = function() {
	if (A_PixiApp === undefined) {
		return undefined;
	}
	return A_PixiApp.stage;
}

let LOOP_LAST_TIME = 0;
JavaScript.JSystem_MainLoop = function(delta) {
	if (LOOP_LAST_TIME === 0) {
		LOOP_LAST_TIME = Date.now();
		return;
	}
	let cur_time = Date.now();
	let delta_time = cur_time - LOOP_LAST_TIME;
	LOOP_LAST_TIME = cur_time;
	let func = window["__ALITTLEAPI_Update"];
	if (func !== undefined) {
		func(delta_time);
	}
}

}