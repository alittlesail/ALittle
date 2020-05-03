{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.System_CalcPortrait = function(src_width, src_height, flag) {
	let scale = 1.0;
	let platform = ALittle.System_GetPlatform();
	if (platform === "iOS" || platform === "Android") {
		let screen_width = ALittle.System_GetScreenWidth();
		let screen_height = ALittle.System_GetScreenHeight();
		src_height = ALittle.Math_Floor(screen_height / screen_width * src_width);
		flag = ALittle.BitOr(flag, ALittle.UIEnumTypes.VIEW_FULLSCREEN);
	} else if (platform === "Web") {
		scale = ALittle.System_GetScreenHeight() / src_height;
	} else if (platform === "WeChat") {
		let screen_width = ALittle.System_GetScreenWidth();
		let screen_height = ALittle.System_GetScreenHeight();
		src_height = ALittle.Math_Floor(screen_height / screen_width * src_width);
		scale = screen_width / src_width;
	} else if (platform === "Windows") {
		if (src_height > ALittle.System_GetScreenHeight()) {
			scale = 0.5;
		}
	}
	return [src_width, src_height, flag, scale];
}

ALittle.System_CalcLandscape = function(src_width, src_height, flag) {
	let scale = 1.0;
	let platform = ALittle.System_GetPlatform();
	if (platform === "iOS" || platform === "Android") {
		let screen_width = ALittle.System_GetScreenWidth();
		let screen_height = ALittle.System_GetScreenHeight();
		src_width = ALittle.Math_Floor(screen_width / screen_height * src_height);
		flag = ALittle.BitOr(flag, ALittle.UIEnumTypes.VIEW_FULLSCREEN);
	} else if (platform === "Web") {
		scale = ALittle.System_GetScreenWidth() / src_width;
	} else if (platform === "WeChat") {
		let screen_width = ALittle.System_GetScreenWidth();
		let screen_height = ALittle.System_GetScreenHeight();
		src_width = ALittle.Math_Floor(screen_width / screen_height * src_height);
		scale = screen_height / src_height;
	} else if (platform === "Windows") {
		if (src_width > ALittle.System_GetScreenWidth()) {
			scale = 0.5;
		}
	}
	return [src_width, src_height, flag, scale];
}

ALittle.System_GetPlatform = function() {
	if (window["wx"] !== undefined) {
		return "WeChat";
	} else {
		return "Web";
	}
}

ALittle.System_GetDeviceID = function() {
	return JavaScript.JSystem_GetDeviceID();
}

ALittle.System_GetLocalIPList = function() {
	return "[]";
}

ALittle.System_IsPhone = function() {
	let user_agent = navigator.userAgent;
	return ALittle.String_Find(user_agent, "Android") !== undefined || ALittle.String_Find(user_agent, "iPhone") !== undefined || ALittle.String_Find(user_agent, "iPad") !== undefined || ALittle.String_Find(user_agent, "iPod") !== undefined;
}

ALittle.System_InstallProgram = function(file_path) {
}

ALittle.System_ClearAIFamily = function() {
}

ALittle.System_StartProgram = function(package_name) {
}

ALittle.System_BackProgram = function() {
}

ALittle.System_GetScreenWidth = function() {
	if (window["wx"] !== undefined) {
		let wx = window["wx"];
		let info = wx["getSystemInfoSync"]();
		return info["windowWidth"] * info["pixelRatio"];
	} else {
		return window.innerWidth;
	}
}

ALittle.System_GetScreenHeight = function() {
	if (window["wx"] !== undefined) {
		let wx = window["wx"];
		let info = wx["getSystemInfoSync"]();
		return info["windowHeight"] * info["pixelRatio"];
	} else {
		return window.innerHeight;
	}
}

ALittle.System_GetStatusBarHeight = function() {
	return 0;
}

ALittle.System_ForceExit = function() {
}

ALittle.System_Exit = function() {
}

ALittle.System_Restart = function() {
}

ALittle.System_SetFPS = function(fps) {
}

ALittle.System_SetAppPauseInterval = function(interval) {
}

ALittle.System_GetAppPauseInterval = function() {
	return 0;
}

ALittle.SystemThreadType = {
	FAST : 0,
	MIDDLE : 1,
	SLOW : 2,
}

ALittle.System_SetThreadCount = function(count, thread_type) {
	if (thread_type === undefined) {
		thread_type = ALittle.SystemThreadType.SLOW;
	}
}

ALittle.System_GetThreadCount = function(thread_type) {
	if (thread_type === undefined) {
		thread_type = ALittle.SystemThreadType.SLOW;
	}
	return 0;
}

ALittle.System_GetIMESelectList = function() {
	return "";
}

ALittle.System_SetIMEPos = function(x, y) {
}

ALittle.System_SetIMERect = function(x, y, w, h) {
}

ALittle.System_OpenIME = function() {
}

ALittle.System_CloseIME = function() {
}

ALittle.System_GetCursorX = function() {
	return 0;
}

ALittle.System_GetCursorY = function() {
	return 0;
}

ALittle.System_SetEditCursor = function() {
}

ALittle.System_SetNormalCursor = function() {
}

ALittle.System_SetHandCursor = function() {
}

ALittle.System_SetHDragCursor = function() {
}

ALittle.System_SetVDragCursor = function() {
}

ALittle.System_SetHVDragCursor = function() {
}

ALittle.System_SetHV2DragCursor = function() {
}

ALittle.System_SetCrossDragCursor = function() {
}

ALittle.System_CreateView = function(title, width, height, flag, scale) {
	return JavaScript.JSystem_CreateView(title, width, height, flag, scale);
}

ALittle.System_SetViewTitle = function(title) {
	return JavaScript.JSystem_SetViewTitle(title);
}

ALittle.System_SetViewIcon = function(path) {
	return false;
}

ALittle.System_SetViewShape = function(path) {
	return false;
}

ALittle.System_SetViewSize = function(width, height) {
}

ALittle.System_SetMaxViewSize = function() {
}

ALittle.System_SetMinViewSize = function() {
}

ALittle.System_SetRestoreViewSize = function() {
}

ALittle.System_RaiseView = function() {
}

ALittle.System_ShowView = function() {
}

ALittle.System_HideView = function() {
}

ALittle.System_GetViewX = function() {
	return 0;
}

ALittle.System_GetViewY = function() {
	return 0;
}

ALittle.System_SetViewPosition = function(x, y) {
}

ALittle.System_GetMaxTextureWidth = function() {
	return 1024;
}

ALittle.System_GetMaxTextureHeight = function() {
	return 1024;
}

ALittle.System_Render = function() {
	return JavaScript.JSystem_Render();
}

ALittle.System_GetClipboardText = function() {
	return "";
}

ALittle.System_SetClipboardText = function(content) {
}

ALittle.System_HasClipboardText = function() {
	return false;
}

ALittle.System_GetClipboardImage = function() {
	return undefined;
}

ALittle.System_SetClipboardImage = function(surface) {
}

ALittle.System_HasClipboardImage = function() {
	return false;
}

ALittle.SystemOrientationType = {
	SDL_ORIENTATION_UNKNOWN : 0,
	SDL_ORIENTATION_LANDSCAPE : 1,
	SDL_ORIENTATION_LANDSCAPE_FLIPPED : 2,
	SDL_ORIENTATION_PORTRAIT : 3,
	SDL_ORIENTATION_PORTRAIT_FLIPPED : 4,
}

ALittle.System_GetDisplayOrientation = function() {
	let match = matchMedia("(orientation: portrait)");
	if (match !== undefined && match.matches) {
		return ALittle.SystemOrientationType.SDL_ORIENTATION_PORTRAIT;
	}
	return ALittle.SystemOrientationType.SDL_ORIENTATION_LANDSCAPE;
}

ALittle.System_EnableScreenSaver = function() {
}

ALittle.System_DisableScreenSaver = function() {
}

ALittle.System_OpenUrlBySystemBrowser = function(url) {
	open(url);
}

ALittle.System_Alert = function(msg) {
	alert(msg);
}

ALittle.System_LoadSurface = function(path) {
	return undefined;
}

ALittle.System_CreateSurface = function(width, height) {
	return undefined;
}

ALittle.System_SaveSurface = function(surface, path) {
	return false;
}

ALittle.System_FreeSurface = function(surface) {
}

ALittle.System_GetSurfaceWidth = function(surface) {
	return 0;
}

ALittle.System_GetSurfaceHeight = function(surface) {
	return 0;
}

ALittle.System_CutBlitSurface = function(new_surface, surface, to, from) {
	return false;
}

ALittle.System_SetSurfacePixel = function(surface, x, y, color) {
	return false;
}

ALittle.System_GetSurfacePixel = function(surface, x, y) {
	return 0;
}

ALittle.System_GetPixelAlpha = function(color) {
	return 0;
}

ALittle.System_SetPixelAlpha = function(color, alpha) {
	return 0;
}

ALittle.System_GetSurfaceGrid9 = function(surface, type) {
	return 0;
}

ALittle.CreateMsgSender = function(heartbeat, check_heartbeat, callback) {
	return ALittle.NewObject(JavaScript.Template(ALittle.MsgSenderTemplate, "ALittle.MsgSenderTemplate<JavaScript.JMsgInterface, JavaScript.JMessageWriteFactory>", JavaScript.JMsgInterface, JavaScript.JMessageWriteFactory), heartbeat, check_heartbeat, A_JLoopSystem, callback);
}

ALittle.CreateHttpSender = function(ip, port) {
	return ALittle.NewObject(JavaScript.Template(ALittle.HttpSenderTemplate, "ALittle.HttpSenderTemplate<JavaScript.JHttpInterface>", JavaScript.JHttpInterface), ip, port);
}

ALittle.HttpRequest = function(ip, port, method) {
	return new Promise(function(___COROUTINE, ___) {
		let sender = ALittle.CreateHttpSender(ip, port);
		if (___COROUTINE === undefined) {
			___COROUTINE(["当前不是协程", undefined]); return;
		}
		sender.SendRPC(___COROUTINE, method, undefined);
		return;
	});
}

ALittle.CreateHttpFileSender = function(ip, port, file_path, start_size, callback) {
	return ALittle.NewObject(JavaScript.Template(ALittle.HttpFileSenderTemplate, "ALittle.HttpFileSenderTemplate<JavaScript.JHttpFileInterface>", JavaScript.JHttpFileInterface), ip, port, file_path, start_size, callback);
}

ALittle.HttpDownloadRequest = function(ip, port, file_path, method, callback) {
	return new Promise(function(___COROUTINE, ___) {
		let sender = ALittle.CreateHttpFileSender(ip, port, file_path, 0, callback);
		if (___COROUTINE === undefined) {
			___COROUTINE("当前不是协程"); return;
		}
		sender.SendDownloadRPC(___COROUTINE, method, undefined);
		return;
	});
}

}