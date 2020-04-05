{
if (typeof ALittle === "undefined") ALittle = {};


ALittle.System_GetPlatform = function() {
	return "Web";
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
	ALittle.Error("not support System_InstallProgram");
}

ALittle.System_ClearAIFamily = function() {
	ALittle.Error("not support System_ClearAIFamily");
}

ALittle.System_StartProgram = function(package_name) {
	ALittle.Error("not support System_StartProgram");
}

ALittle.System_BackProgram = function() {
	ALittle.Error("not support System_BackProgram");
}

ALittle.System_GetScreenWidth = function() {
	return window.innerWidth;
}

ALittle.System_GetScreenHeight = function() {
	return window.innerHeight;
}

ALittle.System_GetStatusBarHeight = function() {
	return 0;
}

ALittle.System_ForceExit = function() {
	ALittle.Error("not support System_ForceExit");
}

ALittle.System_Exit = function() {
	ALittle.Error("not support System_Exit");
}

ALittle.System_Restart = function() {
	ALittle.Error("not support System_Restart");
}

ALittle.System_SetFPS = function(fps) {
	ALittle.Error("not support System_SetFPS");
}

ALittle.System_SetAppPauseInterval = function(interval) {
	__CPPAPI_ScheduleSystem.SetAppPauseInterval(interval);
}

ALittle.System_GetAppPauseInterval = function() {
	return __CPPAPI_ScheduleSystem.GetAppPauseInterval();
}

ALittle.System_StartServerSystem = function(core_path, modules) {
	let module_list = [];
	let ___OBJECT_1 = modules;
	for (let name in ___OBJECT_1) {
		let path = ___OBJECT_1[name];
		if (path === undefined) continue;
		ALittle.List_Push(module_list, name + "," + path);
	}
	return __CPPAPI_ScheduleSystem.StartServerSystem(core_path, ALittle.String_Join(module_list, ";"));
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
	ALittle.Error("not support System_SetThreadCount");
}

ALittle.System_GetThreadCount = function(thread_type) {
	if (thread_type === undefined) {
		thread_type = ALittle.SystemThreadType.SLOW;
	}
	ALittle.Error("not support System_SetThreadCount");
	return 0;
}

ALittle.System_GetIMESelectList = function() {
	return lua.__CPPAPI_GetIMESelectList();
}

ALittle.System_SetIMEPos = function(x, y) {
	lua.__CPPAPI_SetIMSPos(x, y);
}

ALittle.System_SetIMERect = function(x, y, w, h) {
	lua.__CPPAPI_SetIMSRect(x, y, w, h);
}

ALittle.System_OpenIME = function() {
	lua.__CPPAPI_OpenIME();
}

ALittle.System_CloseIME = function() {
	lua.__CPPAPI_CloseIME();
}

ALittle.System_GetCursorX = function() {
	return lua.__CPPAPI_GetCursorX();
}

ALittle.System_GetCursorY = function() {
	return lua.__CPPAPI_GetCursorY();
}

ALittle.System_SetEditCursor = function() {
	lua.__CPPAPI_SetEditCursor();
}

ALittle.System_SetNormalCursor = function() {
	lua.__CPPAPI_SetNormalCursor();
}

ALittle.System_SetHandCursor = function() {
	lua.__CPPAPI_SetHandCursor();
}

ALittle.System_SetHDragCursor = function() {
	lua.__CPPAPI_SetHDragCursor();
}

ALittle.System_SetVDragCursor = function() {
	lua.__CPPAPI_SetVDragCursor();
}

ALittle.System_SetHVDragCursor = function() {
	lua.__CPPAPI_SetHVDragCursor();
}

ALittle.System_SetHV2DragCursor = function() {
	lua.__CPPAPI_SetHV2DragCursor();
}

ALittle.System_SetCrossDragCursor = function() {
	lua.__CPPAPI_SetCrossDragCursor();
}

ALittle.System_CreateView = function(title, width, height, flag, scale) {
	return JavaScript.JSystem_CreateView(title, width, height, flag, scale);
}

ALittle.System_SetViewTitle = function(title) {
	return JavaScript.JSystem_SetViewTitle(title);
}

ALittle.System_SetViewIcon = function(path) {
	ALittle.Error("not support System_SetViewIcon");
	return false;
}

ALittle.System_SetViewShape = function(path) {
	ALittle.Error("not support System_SetViewShape");
	return false;
}

ALittle.System_SetViewSize = function(width, height) {
	ALittle.Error("not support System_SetViewSize");
}

ALittle.System_SetMaxViewSize = function() {
	ALittle.Error("not support System_SetMaxViewSize");
}

ALittle.System_SetMinViewSize = function() {
	ALittle.Error("not support System_SetMinViewSize");
}

ALittle.System_SetRestoreViewSize = function() {
	ALittle.Error("not support System_SetRestoreViewSize");
}

ALittle.System_RaiseView = function() {
	ALittle.Error("not support System_RaiseView");
}

ALittle.System_ShowView = function() {
	ALittle.Error("not support System_ShowView");
}

ALittle.System_HideView = function() {
	ALittle.Error("not support System_HideView");
}

ALittle.System_GetViewX = function() {
	ALittle.Error("not support System_GetViewX");
	return 0;
}

ALittle.System_GetViewY = function() {
	ALittle.Error("not support System_GetViewY");
	return 0;
}

ALittle.System_SetViewPosition = function(x, y) {
	ALittle.Error("not support SetViewPosition");
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
	ALittle.Error("not support System_GetClipboardText");
	return "";
}

ALittle.System_SetClipboardText = function(content) {
	ALittle.Error("not support System_SetClipboardText");
}

ALittle.System_HasClipboardText = function() {
	ALittle.Error("not support System_HasClipboardText");
	return false;
}

ALittle.System_GetClipboardImage = function() {
	ALittle.Error("not support System_GetClipboardImage");
	return undefined;
}

ALittle.System_SetClipboardImage = function(surface) {
	ALittle.Error("not support System_SetClipboardImage");
}

ALittle.System_HasClipboardImage = function() {
	ALittle.Error("not support System_HasClipboardImage");
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
	ALittle.Error("not support System_EnableScreenSaver");
}

ALittle.System_DisableScreenSaver = function() {
	ALittle.Error("not support System_DisableScreenSaver");
}

ALittle.System_OpenUrlBySystemBrowser = function(url) {
	open(url);
}

ALittle.System_Alert = function(msg) {
	alert(msg);
}

ALittle.System_LoadSurface = function(path) {
	ALittle.Error("not support System_LoadSurface");
	return undefined;
}

ALittle.System_CreateSurface = function(width, height) {
	ALittle.Error("not support System_CreateSurface");
	return undefined;
}

ALittle.System_SaveSurface = function(surface, path) {
	ALittle.Error("not support System_SaveSurface");
	return false;
}

ALittle.System_FreeSurface = function(surface) {
	ALittle.Error("not support System_FreeSurface");
}

ALittle.System_GetSurfaceWidth = function(surface) {
	ALittle.Error("not support System_GetSurfaceWidth");
	return 0;
}

ALittle.System_GetSurfaceHeight = function(surface) {
	ALittle.Error("not support System_GetSurfaceHeight");
	return 0;
}

ALittle.System_CutBlitSurface = function(new_surface, surface, to, from) {
	ALittle.Error("not support System_CutBlitSurface");
	return false;
}

ALittle.System_SetSurfacePixel = function(surface, x, y, color) {
	ALittle.Error("not support System_SetSurfacePixel");
	return false;
}

ALittle.System_GetSurfacePixel = function(surface, x, y) {
	ALittle.Error("not support System_GetSurfacePixel");
	return 0;
}

ALittle.System_GetPixelAlpha = function(color) {
	ALittle.Error("not support System_GetPixelAlpha");
	return 0;
}

ALittle.System_SetPixelAlpha = function(color, alpha) {
	ALittle.Error("not support System_SetPixelAlpha");
	return 0;
}

ALittle.System_GetSurfaceGrid9 = function(surface, type) {
	ALittle.Error("not support System_GetSurfaceGrid9");
	return 0;
}

ALittle.CreateMsgSender = function(heartbeat, check_heartbeat, callback) {
	return ALittle.NewObject(JavaScript.Template(ALittle.MsgSenderTemplate, "ALittle.MsgSenderTemplate<JavaScript.JMsgInterface, JavaScript.JMessageWriteFactory>", JavaScript.JMsgInterface, JavaScript.JMessageWriteFactory), heartbeat, check_heartbeat, A_JSLoopSystem, callback);
}

ALittle.CreateHttpSender = function(ip, port) {
	return ALittle.NewObject(JavaScript.Template(ALittle.HttpSenderTemplate, "ALittle.HttpSenderTemplate<JavaScript.JHttpInterface>", JavaScript.JHttpInterface), ip, port);
}

ALittle.HttpRequest = function(ip, port, path) {
	return new Promise(function(___COROUTINE, ___) {
		let sender = ALittle.CreateHttpSender(ip, port);
		if (___COROUTINE === undefined) {
			___COROUTINE(["当前不是协程", undefined]); return;
		}
		sender.SendRPC(___COROUTINE, path, undefined);
		return;
		___COROUTINE();
	});
}

ALittle.CreateHttpFileSender = function(ip, port, file_path, start_size, callback) {
	return ALittle.NewObject(JavaScript.Template(ALittle.HttpFileSenderTemplate, "ALittle.HttpFileSenderTemplate<JavaScript.JHttpFileInterface>", JavaScript.JHttpFileInterface), ip, port, file_path, start_size, callback);
}

ALittle.HttpDownloadRequest = function(ip, port, file_path, callback) {
	return new Promise(function(___COROUTINE, ___) {
		let sender = ALittle.CreateHttpFileSender(ip, port, file_path, 0, callback);
		if (___COROUTINE === undefined) {
			___COROUTINE(["当前不是协程", undefined]); return;
		}
		sender.SendDownloadRPC(___COROUTINE, file_path, undefined);
		return;
		___COROUTINE();
	});
}

}