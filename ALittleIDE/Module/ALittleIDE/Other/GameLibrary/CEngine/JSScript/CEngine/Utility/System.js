{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.System_CalcPortrait = function(src_width, src_height, flag) {
	let scale = 1.0;
	let platform = ALittle.System_GetPlatform();
	if (platform === "iOS" || platform === "Android") {
		let screen_width = ALittle.System_GetScreenWidth();
		let screen_height = ALittle.System_GetScreenHeight();
		src_height = ALittle.Math_Floor(screen_height / screen_width * src_width);
		flag = flag | 0x00000001;
	} else if (platform === "Web") {
		if (flag & 0x00000020 > 0) {
			src_width = ALittle.System_GetScreenWidth();
			src_height = ALittle.System_GetScreenHeight();
		} else {
			scale = ALittle.System_GetScreenHeight() / src_height;
		}
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
		flag = flag | 0x00000001;
	} else if (platform === "Web") {
		if (flag & 0x00000020 > 0) {
			src_width = ALittle.System_GetScreenWidth();
			src_height = ALittle.System_GetScreenHeight();
		} else {
			scale = ALittle.System_GetScreenWidth() / src_width;
		}
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
	if (window.wx !== undefined) {
		return "WeChat";
	} else {
		return "Web";
	}
}

ALittle.System_SetFPS = function(fps) {
}

ALittle.System_GetCurMSTime = function() {
	return Date.now();
}

ALittle.System_GetDeviceID = function() {
	return JavaScript.JSystem_GetDeviceID();
}

ALittle.System_IsPhone = function() {
	let user_agent = navigator.userAgent;
	return ALittle.String_Find(user_agent, "Android") !== undefined || ALittle.String_Find(user_agent, "iPhone") !== undefined || ALittle.String_Find(user_agent, "iPad") !== undefined || ALittle.String_Find(user_agent, "iPod") !== undefined;
}

ALittle.System_InstallProgram = function(file_path) {
}

ALittle.System_GetScreenWidth = function() {
	if (window.wx !== undefined) {
		let info = window.wx.getSystemInfoSync();
		return info.windowWidth * info.pixelRatio;
	} else {
		return window.innerWidth;
	}
}

ALittle.System_GetScreenHeight = function() {
	if (window.wx !== undefined) {
		let info = window.wx.getSystemInfoSync();
		return info.windowHeight * info.pixelRatio;
	} else {
		return window.innerHeight;
	}
}

ALittle.System_ForceExit = function() {
}

ALittle.System_Exit = function() {
}

ALittle.System_Restart = function() {
}

ALittle.System_SetThreadCount = function(count) {
}

ALittle.System_GetThreadCount = function(thread_type) {
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
	if (!ALittle.System_IsPhone()) {
		A_PixiApp.renderer.plugins.interaction.cursorStyles.default = "auto";
		A_PixiApp.renderer.plugins.interaction.setCursorMode("auto");
	}
}

ALittle.System_SetHandCursor = function() {
	if (!ALittle.System_IsPhone()) {
		A_PixiApp.renderer.plugins.interaction.cursorStyles.default = "pointer";
		A_PixiApp.renderer.plugins.interaction.setCursorMode("pointer");
	}
}

ALittle.System_SetHDragCursor = function() {
	if (!ALittle.System_IsPhone()) {
		A_PixiApp.renderer.plugins.interaction.cursorStyles.default = "e-resize";
		A_PixiApp.renderer.plugins.interaction.setCursorMode("e-resize");
	}
}

ALittle.System_SetVDragCursor = function() {
	if (!ALittle.System_IsPhone()) {
		A_PixiApp.renderer.plugins.interaction.cursorStyles.default = "n-resize";
		A_PixiApp.renderer.plugins.interaction.setCursorMode("n-resize");
	}
}

ALittle.System_SetHVDragCursor = function() {
	if (!ALittle.System_IsPhone()) {
		A_PixiApp.renderer.plugins.interaction.cursorStyles.default = "nw-resize";
		A_PixiApp.renderer.plugins.interaction.setCursorMode("nw-resize");
	}
}

ALittle.System_SetHV2DragCursor = function() {
	if (!ALittle.System_IsPhone()) {
		A_PixiApp.renderer.plugins.interaction.cursorStyles.default = "ne-resize";
		A_PixiApp.renderer.plugins.interaction.setCursorMode("ne-resize");
	}
}

ALittle.System_SetCrossDragCursor = function() {
	if (!ALittle.System_IsPhone()) {
		A_PixiApp.renderer.plugins.interaction.cursorStyles.default = "move";
		A_PixiApp.renderer.plugins.interaction.setCursorMode("move");
	}
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

ALittle.System_SetViewSize = function(width, height) {
}

ALittle.System_ShowView = function() {
}

ALittle.System_HideView = function() {
}

ALittle.System_GetMaxTextureWidth = function() {
	return 1024;
}

ALittle.System_GetMaxTextureHeight = function() {
	return 1024;
}

ALittle.System_Render = function() {
	JavaScript.JSystem_Render();
}

ALittle.System_GetClipboardText = function() {
	return "";
}

ALittle.System_SetClipboardText = function(content) {
}

ALittle.System_HasClipboardText = function() {
	return false;
}

ALittle.System_OpenUrlBySystemBrowser = function(url) {
	open(url);
}

ALittle.CreateMsgSender = function(heartbeat, check_heartbeat, callback, rudp) {
	return ALittle.NewObject(JavaScript.Template(ALittle.MsgSenderTemplate, "ALittle.MsgSenderTemplate<JavaScript.JMsgInterface, JavaScript.JMessageWriteFactory>", JavaScript.JMsgInterface, JavaScript.JMessageWriteFactory), heartbeat, check_heartbeat, A_JLoopSystem, callback);
}

ALittle.CreateHttpSender = function(ip, port) {
	if (window.wx !== undefined) {
		return ALittle.NewObject(JavaScript.Template(ALittle.HttpSenderTemplate, "ALittle.HttpSenderTemplate<JavaScript.JHttpWxInterface>", JavaScript.JHttpWxInterface), ip, port);
	} else {
		return ALittle.NewObject(JavaScript.Template(ALittle.HttpSenderTemplate, "ALittle.HttpSenderTemplate<JavaScript.JHttpInterface>", JavaScript.JHttpInterface), ip, port);
	}
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
	if (window.wx !== undefined) {
		return ALittle.NewObject(JavaScript.Template(ALittle.HttpFileSenderTemplate, "ALittle.HttpFileSenderTemplate<JavaScript.JHttpFileWxInterface>", JavaScript.JHttpFileWxInterface), ip, port, file_path, start_size, callback);
	} else {
		return ALittle.NewObject(JavaScript.Template(ALittle.HttpFileSenderTemplate, "ALittle.HttpFileSenderTemplate<JavaScript.JHttpFileInterface>", JavaScript.JHttpFileInterface), ip, port, file_path, start_size, callback);
	}
}

ALittle.HttpDownloadRequest = function(ip, port, file_path, method, callback, array_buffer) {
	return new Promise(function(___COROUTINE, ___) {
		let sender = ALittle.CreateHttpFileSender(ip, port, file_path, 0, callback);
		if (___COROUTINE === undefined) {
			___COROUTINE("当前不是协程"); return;
		}
		sender.SendDownloadRPC(___COROUTINE, method, undefined, array_buffer);
		return;
	});
}

}