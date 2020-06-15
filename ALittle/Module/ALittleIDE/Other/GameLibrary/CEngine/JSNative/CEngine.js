{


window.RequireCEngine = function(base_path) {
	return new Promise(async function(___COROUTINE, ___) {
		await Require(base_path, "CEngine/UISystem/IShow");
		await Require(base_path, "../JSNative/pixi.min");
		await Require(base_path, "../JSNative/pixi-textinput");
		await Require(base_path, "Adapter/PIXI/JSystem");
		await Require(base_path, "Adapter/PIXI/JShow");
		await Require(base_path, "Adapter/PIXI/JCsvLoader");
		await Require(base_path, "CEngine/Utility/String");
		await Require(base_path, "CEngine/Utility/File");
		await Require(base_path, "CEngine/Utility/System");
		await Require(base_path, "CEngine/Utility/ConfigSystem");
		await Require(base_path, "CEngine/Utility/OtherSystem");
		await Require(base_path, "CEngine/Utility/AudioSystem");
		await Require(base_path, "CEngine/Utility/ModuleSystem");
		await Require(base_path, "CEngine/Utility/CsvConfigManager");
		await Require(base_path, "CEngine/LoopSystem/LoopAnimation");
		await Require(base_path, "CEngine/LoopSystem/LoopAttribute");
		await Require(base_path, "CEngine/LoopSystem/LoopLinear");
		await Require(base_path, "CEngine/LoopSystem/LoopRit");
		await Require(base_path, "CEngine/UISystem/UIEnumTypes");
		await Require(base_path, "CEngine/UISystem/UIEventDispatcher");
		await Require(base_path, "CEngine/UISystem/Base/Matrix2D");
		await Require(base_path, "CEngine/UISystem/Base/DisplayObject");
		await Require(base_path, "CEngine/UISystem/Base/DisplayGroup");
		await Require(base_path, "CEngine/UISystem/Base/DisplayLayout");
		await Require(base_path, "CEngine/UISystem/Base/DisplayView");
		await Require(base_path, "CEngine/UISystem/Base/Quad");
		await Require(base_path, "CEngine/UISystem/Base/Image");
		await Require(base_path, "CEngine/UISystem/Base/Sprite");
		await Require(base_path, "CEngine/UISystem/Base/Text");
		await Require(base_path, "CEngine/UISystem/Base/TextArea");
		await Require(base_path, "CEngine/UISystem/Base/TextEdit");
		await Require(base_path, "CEngine/UISystem/Base/TextInput");
		await Require(base_path, "CEngine/UISystem/Base/Triangle");
		await Require(base_path, "CEngine/UISystem/Complex/Grid9Image");
		await Require(base_path, "CEngine/UISystem/Complex/TextButton");
		await Require(base_path, "CEngine/UISystem/Complex/TextCheckButton");
		await Require(base_path, "CEngine/UISystem/Complex/TextRadioButton");
		await Require(base_path, "CEngine/UISystem/Complex/Grid3");
		await Require(base_path, "CEngine/UISystem/Complex/Grid9");
		await Require(base_path, "CEngine/UISystem/Complex/Linear");
		await Require(base_path, "CEngine/UISystem/Complex/Tab");
		await Require(base_path, "CEngine/UISystem/Complex/DropDown");
		await Require(base_path, "CEngine/UISystem/Complex/Slider");
		await Require(base_path, "CEngine/UISystem/Complex/ScrollBar");
		await Require(base_path, "CEngine/UISystem/Complex/ScrollScreen");
		await Require(base_path, "CEngine/UISystem/Complex/Dialog");
		await Require(base_path, "CEngine/UISystem/Complex/TileTable");
		await Require(base_path, "CEngine/UISystem/Complex/ImagePlay");
		await Require(base_path, "CEngine/UISystem/Complex/SpritePlay");
		await Require(base_path, "CEngine/UISystem/Complex/FramePlay");
		await Require(base_path, "CEngine/UISystem/Complex/Piechart");
		await Require(base_path, "CEngine/UISystem/Complex/ImageInput");
		await Require(base_path, "CEngine/UISystem/Complex/ImageEdit");
		await Require(base_path, "CEngine/UISystem/Complex/RichArea");
		await Require(base_path, "CEngine/UISystem/Complex/RichEdit");
		await Require(base_path, "CEngine/UISystem/Complex/RichInput");
		await Require(base_path, "CEngine/UISystem/Complex/ScrollList");
		await Require(base_path, "CEngine/UISystem/Complex/ScrollButton");
		await Require(base_path, "CEngine/UISystem/Special/SpringTextButton");
		await Require(base_path, "CEngine/UISystem/Plugin/SpringButton");
		await Require(base_path, "CEngine/UISystem/Plugin/SpringCheckButton");
		await Require(base_path, "CEngine/UISystem/Plugin/SpringRadioButton");
		await Require(base_path, "CEngine/UISystem/Plugin/SpringDialog");
		await Require(base_path, "CEngine/UISystem/Effect/EffectImage");
		await Require(base_path, "CEngine/UISystem/UISystem");
		await Require(base_path, "CEngine/UISystem/LayerManager");
		await Require(base_path, "CEngine/UISystem/TextureManager");
		await Require(base_path, "CEngine/UISystem/ControlSystem");
		___COROUTINE();
	});
}

window.__ALITTLEAPI_HandleConsoleCmd = function(cmd) {
	ALittle.ExecuteCommand(cmd);
}

window.__ALITTLEAPI_FingerMoved = function(x, y, finger_id, touch_id) {
	A_UISystem.HandleFingerMoved(x, y, finger_id, touch_id);
}

window.__ALITTLEAPI_FingerDown = function(x, y, finger_id, touch_id) {
	A_UISystem.HandleFingerDown(x, y, finger_id, touch_id);
}

window.__ALITTLEAPI_FingerUp = function(x, y, finger_id, touch_id) {
	A_UISystem.HandleFingerUp(x, y, finger_id, touch_id);
}

window.__ALITTLEAPI_MouseMoved = function(x, y) {
	A_UISystem.HandleMouseMoved(x, y);
}

window.__ALITTLEAPI_LButtonDown = function(x, y, count) {
	A_UISystem.HandleLButtonDown(x, y, count);
}

window.__ALITTLEAPI_LButtonUp = function(x, y) {
	A_UISystem.HandleLButtonUp(x, y);
}

window.__ALITTLEAPI_MButtonDown = function(x, y, count) {
	A_UISystem.HandleMButtonDown(x, y, count);
}

window.__ALITTLEAPI_MButtonUp = function(x, y) {
	A_UISystem.HandleMButtonUp(x, y);
}

window.__ALITTLEAPI_RButtonDown = function(x, y, count) {
	A_UISystem.HandleRButtonDown(x, y, count);
}

window.__ALITTLEAPI_RButtonUp = function(x, y) {
	A_UISystem.HandleRButtonUp(x, y);
}

window.__ALITTLEAPI_MouseWheel = function(x, y) {
	A_UISystem.HandleMouseWheel(x, y);
}

window.__ALITTLEAPI_KeyDown = function(mod, sym, scancode) {
	A_UISystem.HandleKeyDown(mod, sym, scancode);
}

window.__ALITTLEAPI_KeyUp = function(mod, sym, scancode) {
	A_UISystem.HandleKeyUp(mod, sym, scancode);
}

window.__ALITTLEAPI_ViewResized = function(width, height) {
	A_UISystem.HandleViewResized(width, height);
}

window.__ALITTLEAPI_TextInput = function(text) {
	A_UISystem.HandleTextInput(text);
}

window.__ALITTLEAPI_TextEditing = function(text, start) {
	A_UISystem.HandleTextEditing(text, start);
}

window.__ALITTLEAPI_DropFile = function(path) {
	A_UISystem.HandleDropFile(path);
}

window.__ALITTLEAPI_WindowEnter = function() {
	A_UISystem.HandleWindowEnter();
}

window.__ALITTLEAPI_WindowLeave = function() {
	A_UISystem.HandleWindowLeave();
}

window.__ALITTLEAPI_Update = function(frame_time) {
	A_LoopSystem.Update(frame_time);
	A_WeakLoopSystem.Update(frame_time);
}

window.__ALITTLEAPI_WillEnterBackground = function() {
	A_OtherSystem.HandleWillEnterBackground();
}

window.__ALITTLEAPI_DidEnterBackground = function() {
	A_OtherSystem.HandleDidEnterBackground();
}

window.__ALITTLEAPI_WillEnterForeground = function() {
	A_OtherSystem.HandleWillEnterForeground();
}

window.__ALITTLEAPI_DidEnterForeground = function() {
	A_OtherSystem.HandleDidEnterForeground();
}

window.__ALITTLEAPI_LowMemory = function() {
	A_OtherSystem.HandleLowMemory();
}

window.__ALITTLEAPI_TextureLoadSucceed = function(loader, texture) {
	A_LoadTextureManager.HandleTextureLoadSucceed(loader, texture);
}

window.__ALITTLEAPI_TextureLoadFailed = function(loader) {
	A_LoadTextureManager.HandleTextureLoadFailed(loader);
}

window.__ALITTLEAPI_TextureCutLoadSucceed = function(loader, texture) {
	A_LoadTextureManager.HandleTextureCutLoadSucceed(loader, texture);
}

window.__ALITTLEAPI_TextureCutLoadFailed = function(loader) {
	A_LoadTextureManager.HandleTextureCutLoadFailed(loader);
}

window.__ALITTLEAPI_CsvFileLoadSucceed = function(loader, file) {
	A_CsvConfigManager.HandleCsvFileLoadSucceed(loader, file);
}

window.__ALITTLEAPI_CsvFileLoadFailed = function(loader) {
	A_CsvConfigManager.HandleCsvFileLoadFailed(loader);
}

window.__ALITTLEAPI_RenderDeviceReset = function() {
	A_LoadTextureManager.HandleRenderDeviceReset();
}

window.__ALITTLEAPI_HttpFileSucceed = ALittle.__ALITTLEAPI_HttpFileSucceed;
window.__ALITTLEAPI_HttpFileFailed = ALittle.__ALITTLEAPI_HttpFileFailed;
window.__ALITTLEAPI_HttpFileProcess = ALittle.__ALITTLEAPI_HttpFileProcess;
window.__ALITTLEAPI_HttpClientSucceed = ALittle.__ALITTLEAPI_HttpClientSucceed;
window.__ALITTLEAPI_HttpClientFailed = ALittle.__ALITTLEAPI_HttpClientFailed;
window.__ALITTLEAPI_ConnectSucceed = ALittle.__ALITTLEAPI_ConnectSucceed;
window.__ALITTLEAPI_Disconnect = ALittle.__ALITTLEAPI_Disconnect;
window.__ALITTLEAPI_ConnectFailed = ALittle.__ALITTLEAPI_ConnectFailed;
window.__ALITTLEAPI_Message = ALittle.__ALITTLEAPI_Message;
window.__ALITTLEAPI_AudioChunkStopedEvent = function(id) {
	A_AudioSystem.HandleAudioChunkStopedEvent(id);
}

window.__ALITTLEAPI_NetworkChanged = function(net_type) {
	ALittle.System_ClearAIFamily();
	A_OtherSystem.HandleNetworkChanged(net_type);
}

window.__ALITTLEAPI_ALittleJsonRPC = function(json) {
	A_OtherSystem.HandleALittleJsonRPC(json);
}

window.__ALITTLEAPI_SystemSelectFile = function(path) {
	A_OtherSystem.HandleSystemSelectFile(path);
}

window.__ALITTLEAPI_SystemSelectDirectory = function(path) {
	A_OtherSystem.HandleSystemSelectDirectory(path);
}

window.__ALITTLEAPI_SystemSaveFile = function(path) {
	A_OtherSystem.HandleSystemSaveFile(path);
}

window.__ALITTLEAPI_SetupMainModule = function(base_path, module_name, debug_info) {
	A_ModuleSystem.MainSetup(base_path, module_name, debug_info);
}

window.__ALITTLEAPI_ShutdownMainModule = function() {
	A_ModuleSystem.MainShutdown();
}

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.IDisplayObject = JavaScript.Class(undefined, {
	SetX : function(value) {
	},
	SetY : function(value) {
	},
	SetScaleX : function(value) {
	},
	SetScaleY : function(value) {
	},
	SetCenterX : function(value) {
	},
	SetCenterY : function(value) {
	},
	SetAngle : function(value) {
	},
	SetRed : function(value) {
	},
	SetGreen : function(value) {
	},
	SetBlue : function(value) {
	},
	SetAlpha : function(value) {
	},
	SetClip : function(value) {
	},
	SetWidth : function(value) {
	},
	SetHeight : function(value) {
	},
	SetVisible : function(value) {
	},
	RemoveChild : function(value) {
	},
	AddChild : function(value) {
	},
	AddChildBefore : function(value1, value2) {
	},
	RemoveAllChild : function() {
	},
	SetFont : function(path, size) {
	},
	ClearTexture : function() {
	},
	SetTexture : function(texture) {
	},
	SetTextureCoord : function(t, b, l, r) {
	},
	SetFlip : function(value) {
	},
	SetRowColCount : function(row_count, col_count) {
	},
	SetRowColIndex : function(row, col) {
	},
	NeedDraw : function() {
	},
	SetText : function(value) {
	},
	SetBold : function(value) {
	},
	SetItalic : function(value) {
	},
	SetUnderline : function(value) {
	},
	SetDeleteline : function(value) {
	},
	SetOutline : function(value) {
	},
	GetRealWidth : function() {
		return 0;
	},
	GetRealHeight : function() {
		return 0;
	},
	GetFontHeight : function() {
		return 0;
	},
	SetHAlign : function(value) {
	},
	SetVAlign : function(value) {
	},
	SetCursorAlpha : function(value) {
	},
	GetLineWidth : function(value) {
		return 0;
	},
	GetLineCount : function() {
		return 0;
	},
	GetScrollOffset : function() {
		return 0;
	},
	IsDefaultText : function() {
		return false;
	},
	SetDefaultText : function(defaultv, value) {
	},
	SetDefaultTextAlpha : function(value) {
	},
	GetCursorX : function() {
		return 0;
	},
	GetCursorY : function() {
		return 0;
	},
	GetText : function() {
		return undefined;
	},
	SetCursorToEnd : function() {
	},
	SetCursorToHome : function() {
	},
	ShowCursor : function(value) {
	},
	ClickCursor : function(x, y) {
	},
	ClickWordCursor : function(x, y) {
		return false;
	},
	SelectAll : function() {
	},
	GetSelectText : function() {
		return undefined;
	},
	InsertText : function(value) {
		return false;
	},
	CursorOffsetLR : function(value) {
	},
	SelectCursorOffsetLR : function(value) {
	},
	CursorOffsetUD : function(value) {
	},
	SelectCursorOffsetUD : function(value) {
	},
	DeleteText : function(value) {
		return false;
	},
	DeleteSelectText : function() {
		return false;
	},
	DragCursorBegin : function() {
	},
	DragCursor : function(x, y) {
	},
	SetCursorRed : function(value) {
	},
	SetCursorGreen : function(value) {
	},
	SetCursorBlue : function(value) {
	},
	SetPasswordMode : function(value) {
	},
	CursorOffset : function(value) {
	},
	SelectCursorOffset : function(value) {
	},
	SetTexUV : function(index, u, v) {
	},
	SetPosXY : function(index, x, y) {
	},
	SetLeftSize : function(value) {
	},
	SetRightSize : function(value) {
	},
	SetTopSize : function(value) {
	},
	SetBottomSize : function(value) {
	},
	CutTextByWidth : function(remain_width, text, total_width) {
		return 0;
	},
	ClearCutWidthCache : function() {
	},
	GetCutWidthListCount : function() {
		return 0;
	},
	GetCutWidthByIndex : function(index) {
		return 0;
	},
	CalcTextWidth : function(value) {
		return 0;
	},
}, "ALittle.IDisplayObject");

if (ALittle.IDisplayObject === undefined) throw new Error(" extends class:ALittle.IDisplayObject is undefined");
ALittle.IDisplayObjects = JavaScript.Class(ALittle.IDisplayObject, {
}, "ALittle.IDisplayObjects");

if (ALittle.IDisplayObject === undefined) throw new Error(" extends class:ALittle.IDisplayObject is undefined");
ALittle.IDisplayView = JavaScript.Class(ALittle.IDisplayObject, {
}, "ALittle.IDisplayView");

if (ALittle.IDisplayObject === undefined) throw new Error(" extends class:ALittle.IDisplayObject is undefined");
ALittle.IImage = JavaScript.Class(ALittle.IDisplayObject, {
}, "ALittle.IImage");

if (ALittle.IDisplayObject === undefined) throw new Error(" extends class:ALittle.IDisplayObject is undefined");
ALittle.IQuad = JavaScript.Class(ALittle.IDisplayObject, {
}, "ALittle.IQuad");

if (ALittle.IDisplayObject === undefined) throw new Error(" extends class:ALittle.IDisplayObject is undefined");
ALittle.ISprite = JavaScript.Class(ALittle.IDisplayObject, {
}, "ALittle.ISprite");

if (ALittle.IDisplayObject === undefined) throw new Error(" extends class:ALittle.IDisplayObject is undefined");
ALittle.IText = JavaScript.Class(ALittle.IDisplayObject, {
}, "ALittle.IText");

if (ALittle.IDisplayObject === undefined) throw new Error(" extends class:ALittle.IDisplayObject is undefined");
ALittle.ITextArea = JavaScript.Class(ALittle.IDisplayObject, {
}, "ALittle.ITextArea");

if (ALittle.IDisplayObject === undefined) throw new Error(" extends class:ALittle.IDisplayObject is undefined");
ALittle.ITextEdit = JavaScript.Class(ALittle.IDisplayObject, {
}, "ALittle.ITextEdit");

if (ALittle.IDisplayObject === undefined) throw new Error(" extends class:ALittle.IDisplayObject is undefined");
ALittle.ITextInput = JavaScript.Class(ALittle.IDisplayObject, {
}, "ALittle.ITextInput");

if (ALittle.IDisplayObject === undefined) throw new Error(" extends class:ALittle.IDisplayObject is undefined");
ALittle.ITriangle = JavaScript.Class(ALittle.IDisplayObject, {
}, "ALittle.ITriangle");

if (ALittle.IDisplayObject === undefined) throw new Error(" extends class:ALittle.IDisplayObject is undefined");
ALittle.IGrid9Image = JavaScript.Class(ALittle.IDisplayObject, {
}, "ALittle.IGrid9Image");

ALittle.IDisplaySystem = JavaScript.Class(undefined, {
	AddSpecialChild : function(value) {
	},
	AddChild : function(value) {
	},
	AddChildBefore : function(value1, value2) {
	},
	RemoveChild : function(value) {
	},
	RemoveAllChild : function() {
	},
}, "ALittle.IDisplaySystem");

ALittle.ITexture = JavaScript.Class(undefined, {
	Clear : function() {
	},
	GetTexture : function() {
		return this;
	},
	GetWidth : function() {
		return 0;
	},
	GetHeight : function() {
		return 0;
	},
}, "ALittle.ITexture");

if (ALittle.ITexture === undefined) throw new Error(" extends class:ALittle.ITexture is undefined");
ALittle.IRenderTexture = JavaScript.Class(ALittle.ITexture, {
	Save : function(file_path, show, width, height, scale) {
		return false;
	},
	Draw : function(show, width, height, scale) {
		return false;
	},
}, "ALittle.IRenderTexture");

ALittle.ITextureLoader = JavaScript.Class(undefined, {
	SetPath : function(big_path, altas, big_width, big_height, crypt_mode) {
	},
	Start : function() {
	},
	GetID : function() {
		return 0;
	},
	GetPath : function() {
		return undefined;
	},
}, "ALittle.ITextureLoader");

ALittle.ITextureCutLoader = JavaScript.Class(undefined, {
	SetPath : function(path, max_width, max_height) {
	},
	Start : function() {
	},
	GetID : function() {
		return 0;
	},
	GetPath : function() {
		return undefined;
	},
	GetMaxWidth : function() {
		return 0;
	},
	GetMaxHeight : function() {
		return 0;
	},
}, "ALittle.ITextureCutLoader");

}
{
if (typeof JavaScript === "undefined") window.JavaScript = {};


let __pixel_ratio = 1;
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
	func((event.pageX - offsetLeft) / A_PixiApp.stage.scale.x * __pixel_ratio, (event.pageY - offsetTop) / A_PixiApp.stage.scale.y * __pixel_ratio, 1, 1);
}

let JSystem_WXFingerDown = function(event) {
	JSystem_FingerDown(event.touches[1 - 1]);
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
	func((event.pageX - offsetLeft) / A_PixiApp.stage.scale.x * __pixel_ratio, (event.pageY - offsetTop) / A_PixiApp.stage.scale.y * __pixel_ratio, 1, 1);
}

let JSystem_WXFingerUp = function(event) {
	JSystem_FingerUp(event.changedTouches[1 - 1]);
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
	func((event.pageX - offsetLeft) / A_PixiApp.stage.scale.x * __pixel_ratio, (event.pageY - offsetTop) / A_PixiApp.stage.scale.y * __pixel_ratio, 1, 1);
}

let JSystem_WXFingerMoved = function(event) {
	JSystem_FingerMoved(event.touches[1 - 1]);
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
	func(0, event.keyCode, 0);
}

let JSystem_KeyUp = function(event) {
	let func = window["__ALITTLEAPI_KeyUp"];
	if (func === undefined) {
		return;
	}
	func(0, event.keyCode, 0);
}

JavaScript.JSystem_CreateView = function(title, width, height, flag, scale) {
	if (A_PixiApp !== undefined) {
		return true;
	}
	let data = {};
	let wx = window["wx"];
	if (wx !== undefined) {
		let info = wx["getSystemInfoSync"]();
		__pixel_ratio = info["pixelRatio"];
		data.view = window["canvas"];
	} else {
		data.forceCanvas = !PIXI.utils.isWebGLSupported();
	}
	data.width = ALittle.Math_Floor(width * scale);
	data.height = ALittle.Math_Floor(height * scale);
	A_PixiApp = new PIXI.Application(data);
	document.body.appendChild(A_PixiApp.view);
	document.title = title;
	A_PixiApp.stage.scale.x = scale;
	A_PixiApp.stage.scale.y = scale;
	if (wx !== undefined) {
		wx["onTouchStart"](JSystem_WXFingerDown);
		wx["onTouchMove"](JSystem_WXFingerMoved);
		wx["onTouchEnd"](JSystem_WXFingerUp);
	} else if (ALittle.System_IsPhone()) {
		A_PixiApp.view.ontouchstart = JSystem_FingerDown;
		A_PixiApp.view.ontouchmove = JSystem_FingerMoved;
		A_PixiApp.view.ontouchend = JSystem_FingerUp;
	} else {
		A_PixiApp.view.onmousedown = JSystem_MouseDown;
		A_PixiApp.view.onmousemove = JSystem_MouseMoved;
		A_PixiApp.view.onmouseup = JSystem_MouseUp;
		A_PixiApp.view.onmousewheel = JSystem_MouseWheel;
		A_PixiApp.view.onmouseout = JSystem_MouseOut;
		A_PixiApp.view.onkeydown = JSystem_KeyDown;
		A_PixiApp.view.onkeyup = JSystem_KeyUp;
	}
	A_JDisplaySystem.AddToStage(A_PixiApp.stage);
	let func = window["__ALITTLEAPI_ViewResized"];
	if (func !== undefined) {
		func(width, height);
	}
	A_PixiApp.ticker.add(JavaScript.JSystem_MainLoop);
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
{
if (typeof JavaScript === "undefined") window.JavaScript = {};


JavaScript.RGBToHex = function(r, g, b) {
	let hex = (r * 65536 + g * 256 + b).toString(16);
	if (hex.length <= 0) {
		return "#000000";
	}
	if (hex.length <= 1) {
		return "#00000" + hex;
	}
	if (hex.length <= 2) {
		return "#0000" + hex;
	}
	if (hex.length <= 3) {
		return "#000" + hex;
	}
	if (hex.length <= 4) {
		return "#00" + hex;
	}
	if (hex.length <= 5) {
		return "#0" + hex;
	}
	return "#" + hex;
}

JavaScript.RGBCombine = function(r, g, b) {
	return r * 65536 + g * 256 + b;
}

if (ALittle.IDisplayObject === undefined) throw new Error(" extends class:ALittle.IDisplayObject is undefined");
JavaScript.JDisplayObject = JavaScript.Class(ALittle.IDisplayObject, {
	Ctor : function() {
		this._scale = new PIXI.Point(1, 1);
		this._pivot = new PIXI.Point(0, 0);
		this._clip = false;
		this._visible = true;
		this._x = 0;
		this._y = 0;
	},
	get native() {
		return this._native;
	},
	SetX : function(x) {
		this._x = x;
		this._native.x = Math.floor(x + this._pivot.x);
	},
	SetY : function(y) {
		this._y = y;
		this._native.y = Math.floor(y + this._pivot.y);
	},
	SetScaleX : function(value) {
		this._scale.x = value;
		this._native.scale = this._scale;
	},
	SetScaleY : function(value) {
		this._scale.y = value;
		this._native.scale = this._scale;
	},
	SetCenterX : function(value) {
		this._pivot.x = value;
		this._native.pivot = this._pivot;
		this._native.x = Math.floor(this._x + this._pivot.x);
	},
	SetCenterY : function(value) {
		this._pivot.y = value;
		this._native.pivot = this._pivot;
		this._native.y = Math.floor(this._y + this._pivot.y);
	},
	SetAngle : function(value) {
		this._native.angle = value;
	},
	SetWidth : function(value) {
	},
	SetHeight : function(value) {
	},
	SetVisible : function(value) {
		this._visible = value;
		this._native.visible = value && !this._clip;
	},
	SetClip : function(value) {
		this._clip = value;
		this._native.visible = value && this._visible;
	},
	SetAlpha : function(value) {
		this._native.alpha = value;
	},
	SetRed : function(value) {
	},
	SetGreen : function(value) {
	},
	SetBlue : function(value) {
	},
	RemoveChild : function(value) {
	},
	AddChild : function(value) {
	},
	AddChildBefore : function(value1, value2) {
	},
	RemoveAllChild : function() {
	},
	SetFont : function(path, size) {
	},
	ClearTexture : function() {
	},
	SetTexture : function(texture) {
	},
	SetTextureCoord : function(t, b, l, r) {
	},
	SetFlip : function(value) {
	},
	SetRowColCount : function(row_count, col_count) {
	},
	SetRowColIndex : function(row, col) {
	},
	NeedDraw : function() {
	},
	SetText : function(value) {
	},
	SetBold : function(value) {
	},
	SetItalic : function(value) {
	},
	SetUnderline : function(value) {
	},
	SetDeleteline : function(value) {
	},
	SetOutline : function(value) {
	},
	GetRealWidth : function() {
		return 0;
	},
	GetRealHeight : function() {
		return 0;
	},
	GetFontHeight : function() {
		return 0;
	},
	SetHAlign : function(value) {
	},
	SetVAlign : function(value) {
	},
	SetCursorAlpha : function(value) {
	},
	GetLineWidth : function(value) {
		return 0;
	},
	GetLineCount : function() {
		return 0;
	},
	GetScrollOffset : function() {
		return 0;
	},
	IsDefaultText : function() {
		return false;
	},
	SetDefaultText : function(defaultv, value) {
	},
	SetDefaultTextAlpha : function(value) {
	},
	GetCursorX : function() {
		return 0;
	},
	GetCursorY : function() {
		return 0;
	},
	GetText : function() {
		return undefined;
	},
	SetCursorToEnd : function() {
	},
	SetCursorToHome : function() {
	},
	ShowCursor : function(value) {
	},
	ClickCursor : function(x, y) {
	},
	ClickWordCursor : function(x, y) {
		return false;
	},
	SelectAll : function() {
	},
	GetSelectText : function() {
		return undefined;
	},
	InsertText : function(value) {
		return false;
	},
	CursorOffsetLR : function(value) {
	},
	SelectCursorOffsetLR : function(value) {
	},
	CursorOffsetUD : function(value) {
	},
	SelectCursorOffsetUD : function(value) {
	},
	DeleteText : function(value) {
		return false;
	},
	DeleteSelectText : function() {
		return false;
	},
	DragCursorBegin : function() {
	},
	DragCursor : function(x, y) {
	},
	SetCursorRed : function(value) {
	},
	SetCursorGreen : function(value) {
	},
	SetCursorBlue : function(value) {
	},
	SetPasswordMode : function(value) {
	},
	CursorOffset : function(value) {
	},
	SelectCursorOffset : function(value) {
	},
	SetTexUV : function(index, u, v) {
	},
	SetPosXY : function(index, x, y) {
	},
	SetLeftSize : function(value) {
	},
	SetRightSize : function(value) {
	},
	SetTopSize : function(value) {
	},
	SetBottomSize : function(value) {
	},
	CutTextByWidth : function(remain_width, text, total_width) {
		return 0;
	},
	ClearCutWidthCache : function() {
	},
	GetCutWidthListCount : function() {
		return 0;
	},
	GetCutWidthByIndex : function(index) {
		return 0;
	},
	CalcTextWidth : function(value) {
		return 0;
	},
}, "JavaScript.JDisplayObject");

if (JavaScript.JDisplayObject === undefined) throw new Error(" extends class:JavaScript.JDisplayObject is undefined");
JavaScript.JDisplayObjects = JavaScript.Class(JavaScript.JDisplayObject, {
	Ctor : function() {
		this._native = new PIXI.Container();
	},
	RemoveChild : function(value) {
		this._native.removeChild(value._native);
	},
	AddChild : function(value) {
		this._native.addChild(value._native);
	},
	AddChildBefore : function(back, value) {
		let index = this._native.getChildAt(value._native);
		this._native.addChildAt(value._native, index - 1);
	},
	RemoveAllChild : function() {
		this._native.removeChildren(0);
	},
}, "JavaScript.JDisplayObjects");

if (JavaScript.JDisplayObjects === undefined) throw new Error(" extends class:JavaScript.JDisplayObjects is undefined");
JavaScript.JDisplayView = JavaScript.Class(JavaScript.JDisplayObjects, {
	Ctor : function() {
		this._container = new PIXI.Container();
		this._graphics = new PIXI.Graphics();
		this._container.mask = this._graphics;
		this._native.addChild(this._graphics);
		this._native.addChild(this._container);
		this._width = 0;
		this._height = 0;
	},
	SetWidth : function(width) {
		this._width = width;
		this.Draw();
	},
	SetHeight : function(height) {
		this._height = height;
		this.Draw();
	},
	Draw : function() {
		this._graphics.clear();
		this._graphics.beginFill();
		this._graphics.drawRect(0, 0, this._width, this._height);
		this._graphics.endFill();
	},
	RemoveChild : function(value) {
		this._container.removeChild(value._native);
	},
	AddChild : function(value) {
		this._container.addChild(value._native);
	},
	AddChildBefore : function(back, value) {
		let index = this._container.getChildAt(value._native);
		this._container.addChildAt(value._native, index - 1);
	},
	RemoveAllChild : function() {
		this._container.removeChildren(0);
	},
}, "JavaScript.JDisplayView");

if (ALittle.IDisplaySystem === undefined) throw new Error(" extends class:ALittle.IDisplaySystem is undefined");
JavaScript.JDisplaySystem = JavaScript.Class(ALittle.IDisplaySystem, {
	Ctor : function() {
		this._layer = new PIXI.Container();
		this._special_layer = new PIXI.Container();
	},
	AddToStage : function(stage) {
		this._layer.width = stage.width;
		this._layer.height = stage.height;
		this._special_layer.width = stage.width;
		this._special_layer.height = stage.height;
		stage.addChild(this._layer);
		stage.addChild(this._special_layer);
	},
	AddSpecialChild : function(value) {
		this._special_layer.addChild(value.native);
	},
	AddChild : function(value) {
		this._layer.addChild(value.native);
	},
	AddChildBefore : function(back, value) {
		let index = this._layer.getChildAt(value.native);
		this._layer.addChildAt(value.native, index - 1);
	},
	RemoveChild : function(value) {
		this._layer.removeChild(value.native);
	},
	RemoveAllChild : function() {
		this._layer.removeChildren(0);
		this._special_layer.removeChildren(0);
	},
}, "JavaScript.JDisplaySystem");

window.A_JDisplaySystem = ALittle.NewObject(JavaScript.JDisplaySystem);
if (JavaScript.JDisplayObject === undefined) throw new Error(" extends class:JavaScript.JDisplayObject is undefined");
JavaScript.JQuad = JavaScript.Class(JavaScript.JDisplayObject, {
	Ctor : function() {
		this._native = new PIXI.Graphics();
		this._red = 255;
		this._green = 255;
		this._blue = 255;
		this._color = this._red * 65536 + this._green * 256 + this._blue;
		this._alpha = 1;
		this._width = 0;
		this._height = 0;
	},
	Draw : function() {
		this._native.clear();
		this._native.beginFill(this._color, this._alpha);
		this._native.drawRect(0, 0, this._width, this._height);
		this._native.endFill();
	},
	SetWidth : function(value) {
		this._width = value;
		this.Draw();
	},
	SetHeight : function(value) {
		this._height = value;
		this.Draw();
	},
	SetRed : function(value) {
		this._red = Math.floor(value * 255);
		this._color = this._red * 65536 + this._green * 256 + this._blue;
		this.Draw();
	},
	SetGreen : function(value) {
		this._green = Math.floor(value * 255);
		this._color = this._red * 65536 + this._green * 256 + this._blue;
		this.Draw();
	},
	SetBlue : function(value) {
		this._blue = Math.floor(value * 255);
		this._color = this._red * 65536 + this._green * 256 + this._blue;
		this.Draw();
	},
	SetAlpha : function(value) {
		this._alpha = value;
		this.Draw();
	},
}, "JavaScript.JQuad");

if (JavaScript.JDisplayObject === undefined) throw new Error(" extends class:JavaScript.JDisplayObject is undefined");
JavaScript.JImage = JavaScript.Class(JavaScript.JDisplayObject, {
	Ctor : function() {
		this._native = new PIXI.Sprite();
	},
	SetWidth : function(width) {
		this._native.width = width;
	},
	SetHeight : function(height) {
		this._native.height = height;
	},
	ClearTexture : function() {
		this._native.texture = undefined;
	},
	SetTexture : function(texture) {
		this._native.texture = texture.native;
	},
	SetTextureCoord : function(t, b, l, r) {
	},
}, "JavaScript.JImage");

if (JavaScript.JDisplayObject === undefined) throw new Error(" extends class:JavaScript.JDisplayObject is undefined");
JavaScript.JGrid9Image = JavaScript.Class(JavaScript.JDisplayObject, {
	Ctor : function() {
		this._native = new PIXI.Container();
		this._leftWidth = 0;
		this._rightWidth = 0;
		this._topHeight = 0;
		this._bottomHeight = 0;
		this._width = 0;
		this._height = 0;
	},
	ClearTexture : function() {
		this._native.removeChildren(0);
		this._nine = undefined;
	},
	SetTexture : function(texture) {
		if (this._nine === undefined) {
			this._nine = new PIXI.NineSlicePlane(texture.native, this._leftWidth, this._topHeight, this._rightWidth, this._bottomHeight);
			this._native.addChild(this._nine);
			this._nine.width = this._width;
			this._nine.height = this._height;
		} else {
			this._native.texture = texture.native;
		}
	},
	SetTextureCoord : function(t, b, l, r) {
	},
	SetWidth : function(width) {
		this._width = width;
		if (this._nine !== undefined) {
			this._nine.width = width;
		}
	},
	SetHeight : function(height) {
		this._height = height;
		if (this._nine !== undefined) {
			this._nine.height = height;
		}
	},
	SetLeftSize : function(value) {
		this._leftWidth = value;
		if (this._nine !== undefined) {
			this._nine.leftWidth = value;
		}
	},
	SetRightSize : function(value) {
		this._rightWidth = value;
		if (this._nine !== undefined) {
			this._nine.rightWidth = value;
		}
	},
	SetTopSize : function(value) {
		this._topHeight = value;
		if (this._nine !== undefined) {
			this._nine.topHeight = value;
		}
	},
	SetBottomSize : function(value) {
		this._bottomHeight = value;
		if (this._nine !== undefined) {
			this._nine.bottomHeight = value;
		}
	},
}, "JavaScript.JGrid9Image");

if (JavaScript.JDisplayObject === undefined) throw new Error(" extends class:JavaScript.JDisplayObject is undefined");
JavaScript.JSprite = JavaScript.Class(JavaScript.JDisplayObject, {
	Ctor : function() {
		this._row_count = 1;
		this._col_count = 1;
		this._row = 0;
		this._col = 0;
		this._tex_width = 0;
		this._tex_height = 0;
		this._native = new PIXI.Sprite();
	},
	SetWidth : function(width) {
		this._native.width = width;
	},
	SetHeight : function(height) {
		this._native.height = height;
	},
	ClearTexture : function() {
		this._texture = undefined;
		this._tex_width = 0;
		this._tex_height = 0;
		this._native.texture = undefined;
	},
	SetTexture : function(texture) {
		this._tex_width = texture.GetWidth();
		this._tex_height = texture.GetHeight();
		let tile_width = this._tex_width / this._col_count;
		let tile_height = this._tex_height / this._row_count;
		let row = this._row;
		let col = this._col;
		if (row < 0 || row >= this._row_count) {
			row = 0;
		}
		if (col < 0 || col >= this._col_count) {
			col = 0;
		}
		let frame = new PIXI.Rectangle(col * tile_width, row * tile_height, tile_width, tile_height);
		this._texture = new PIXI.Texture(texture.native.baseTexture, frame, texture.native.orig, texture.native.trim, texture.native.rotate);
		this._native.texture = this._texture;
	},
	SetTextureCoord : function(t, b, l, r) {
	},
	SetRowColCount : function(row_count, col_count) {
		this._row_count = row_count;
		if (this._row_count < 1) {
			this._row_count = 1;
		}
		this._col_count = col_count;
		if (this._col_count < 1) {
			this._col_count = 1;
		}
		this.UpdateFrame();
	},
	SetRowColIndex : function(row, col) {
		this._row = row - 1;
		this._col = col - 1;
		this.UpdateFrame();
	},
	UpdateFrame : function() {
		if (this._texture === undefined) {
			return;
		}
		let tile_width = this._tex_width / this._col_count;
		let tile_height = this._tex_height / this._row_count;
		let row = this._row;
		let col = this._col;
		if (row < 0 || row >= this._row_count) {
			row = 0;
		}
		if (col < 0 || col >= this._col_count) {
			col = 0;
		}
		this._texture.frame = new PIXI.Rectangle(col * tile_width, row * tile_height, tile_width, tile_height);
	},
}, "JavaScript.JSprite");

if (JavaScript.JDisplayObject === undefined) throw new Error(" extends class:JavaScript.JDisplayObject is undefined");
JavaScript.JTriangle = JavaScript.Class(JavaScript.JDisplayObject, {
	Ctor : function() {
		this._native = new PIXI.Container();
		this._uv = [];
		for (let i = 0; i < 6; i += 1) {
			this._uv[i /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = 0;
		}
		this._xy = [];
		for (let i = 0; i < 6; i += 1) {
			this._xy[i /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = 0;
		}
		this._index = [];
		for (let i = 0; i < 3; i += 1) {
			this._index[i /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = i;
		}
	},
	ClearTexture : function() {
		if (this._mesh !== undefined) {
			this._mesh.texture = undefined;
		}
	},
	SetTexture : function(texture) {
		if (this._mesh === undefined) {
			this._mesh = new PIXI.SimpleMesh(texture.native, this._xy, this._uv, this._index);
			this._native.addChild(this._mesh);
		} else {
			this._mesh.texture = texture.native;
		}
	},
	SetTextureCoord : function(t, b, l, r) {
	},
	SetTexUV : function(index, u, v) {
		if (this._mesh === undefined) {
			this._uv[index * 2 /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = u;
			this._uv[index * 2 + 1 /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = v;
		} else {
			this._mesh.uvBuffer.data[index * 2 + 1 - 1] = u;
			this._mesh.uvBuffer.data[(index + 1) * 2 - 1] = v;
		}
	},
	SetPosXY : function(index, x, y) {
		if (this._mesh === undefined) {
			this._xy[index * 2 /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = x;
			this._xy[index * 2 + 1 /*因为使用了Native修饰，下标从0开始，不做减1处理*/] = y;
		} else {
			this._mesh.verticesBuffer.data[index * 2 + 1 - 1] = x;
			this._mesh.verticesBuffer.data[(index + 1) * 2 - 1] = y;
		}
	},
}, "JavaScript.JTriangle");

if (JavaScript.JDisplayObject === undefined) throw new Error(" extends class:JavaScript.JDisplayObject is undefined");
JavaScript.JText = JavaScript.Class(JavaScript.JDisplayObject, {
	Ctor : function() {
		this._native = new PIXI.Text();
		this._style = new PIXI.TextStyle();
		this._real_width = 0;
		this._real_height = 0;
		this._red = 255;
		this._green = 255;
		this._blue = 255;
		this._style.fill = JavaScript.RGBCombine(this._red, this._green, this._blue);
		this._text = "";
	},
	SetBold : function(value) {
		if (value) {
			this._style.fontWeight = "bold";
		} else {
			this._style.fontWeight = "normal";
		}
		this._native.style = this._style;
	},
	SetItalic : function(value) {
		if (value) {
			this._style.fontStyle = "italic";
		} else {
			this._style.fontStyle = "normal";
		}
		this._native.style = this._style;
	},
	SetText : function(value) {
		this._text = value;
		this._native.text = value;
		let m = PIXI.TextMetrics.measureText(this._text, this._style);
		this._real_width = m.width;
		this._real_height = m.height;
	},
	SetFont : function(path, size) {
		this._style.fontFamily = path;
		this._style.fontSize = size;
		this._native.style = this._style;
		let m = PIXI.TextMetrics.measureText(this._text, this._style);
		this._real_width = m.width;
		this._real_height = m.height;
	},
	SetRed : function(value) {
		this._red = Math.floor(value * 255);
		this._style.fill = JavaScript.RGBCombine(this._red, this._green, this._blue);
		this._native.style = this._style;
	},
	SetGreen : function(value) {
		this._green = Math.floor(value * 255);
		this._style.fill = JavaScript.RGBCombine(this._red, this._green, this._blue);
		this._native.style = this._style;
	},
	SetBlue : function(value) {
		this._blue = Math.floor(value * 255);
		this._style.fill = JavaScript.RGBCombine(this._red, this._green, this._blue);
		this._native.style = this._style;
	},
	GetRealWidth : function() {
		return this._real_width;
	},
	GetRealHeight : function() {
		return this._real_height;
	},
	GetFontHeight : function() {
		return this._real_height;
	},
}, "JavaScript.JText");

if (JavaScript.JDisplayObject === undefined) throw new Error(" extends class:JavaScript.JDisplayObject is undefined");
JavaScript.JTextArea = JavaScript.Class(JavaScript.JDisplayObject, {
	Ctor : function() {
		this._native = new PIXI.Text();
		this._style = new PIXI.TextStyle();
		this._red = 255;
		this._green = 255;
		this._blue = 255;
		this._style.fill = JavaScript.RGBCombine(this._red, this._green, this._blue);
		this._style.wordWrap = true;
		this._style.breakWords = true;
		this._text = "";
		this._width = 0;
		this._height = 0;
		this._real_width = 0;
		this._real_height = 0;
		this._h_align = 0;
		this._v_align = 0;
	},
	SetBold : function(value) {
		if (value) {
			this._style.fontWeight = "bold";
		} else {
			this._style.fontWeight = "normal";
		}
		this._native.style = this._style;
	},
	SetItalic : function(value) {
		if (value) {
			this._style.fontStyle = "italic";
		} else {
			this._style.fontStyle = "normal";
		}
		this._native.style = this._style;
	},
	SetHAlign : function(align) {
		if (this._h_align === align) {
			return;
		}
		this._h_align = align;
		if (this._h_align === ALittle.UIEnumTypes.HALIGN_LEFT) {
			this._style.align = "left";
		} else if (this._h_align === ALittle.UIEnumTypes.HALIGN_CENTER) {
			this._style.align = "center";
		} else {
			this._style.align = "right";
		}
		this._native.style = this._style;
		this.UpdateShow();
	},
	SetVAlign : function(align) {
		if (this._v_align === align) {
			return;
		}
		this._v_align = align;
		this.UpdateShow();
	},
	SetX : function(x) {
		this._x = x;
		this.UpdateShow();
	},
	SetY : function(y) {
		this._y = y;
		this.UpdateShow();
	},
	SetWidth : function(width) {
		this._width = width;
		this._style.wordWrapWidth = Math.floor(width);
		this._native.style = this._style;
		let m = PIXI.TextMetrics.measureText(this._text, this._style);
		this._real_width = m.width;
		this._real_height = m.height;
		this.UpdateShow();
	},
	SetHeight : function(height) {
		this._height = height;
		this.UpdateShow();
	},
	SetText : function(value) {
		this._text = value;
		this._native.text = value;
		this._native.style = this._style;
		let m = PIXI.TextMetrics.measureText(this._text, this._style);
		this._real_width = m.width;
		this._real_height = m.height;
		this.UpdateShow();
	},
	SetFont : function(path, size) {
		this._style.fontFamily = path;
		this._style.fontSize = size;
		this._native.style = this._style;
		let m = PIXI.TextMetrics.measureText(this._text, this._style);
		this._real_width = m.width;
		this._real_height = m.height;
		this.UpdateShow();
	},
	SetRed : function(value) {
		this._red = Math.floor(value * 255);
		this._style.fill = JavaScript.RGBCombine(this._red, this._green, this._blue);
		this._native.style = this._style;
	},
	SetGreen : function(value) {
		this._green = Math.floor(value * 255);
		this._style.fill = JavaScript.RGBCombine(this._red, this._green, this._blue);
		this._native.style = this._style;
	},
	SetBlue : function(value) {
		this._blue = Math.floor(value * 255);
		this._style.fill = JavaScript.RGBCombine(this._red, this._green, this._blue);
		this._native.style = this._style;
	},
	GetRealHeight : function() {
		return this._real_height;
	},
	UpdateShow : function() {
		if (this._h_align === ALittle.UIEnumTypes.HALIGN_LEFT) {
			this._native.x = Math.floor(this._x);
		} else if (this._h_align === ALittle.UIEnumTypes.HALIGN_CENTER) {
			this._native.x = Math.floor((this._width - this._real_width) / 2 + this._x);
		} else {
			this._native.x = Math.floor(this._width - this._real_width + this._x);
		}
		if (this._v_align === ALittle.UIEnumTypes.VALIGN_TOP) {
			this._native.y = Math.floor(this._y);
		} else if (this._v_align === ALittle.UIEnumTypes.VALIGN_CENTER) {
			this._native.y = Math.floor((this._height - this._real_height) / 2 + this._y);
		} else {
			this._native.y = Math.floor(this._height - this._real_height + this._y);
		}
	},
}, "JavaScript.JTextArea");

if (JavaScript.JDisplayObject === undefined) throw new Error(" extends class:JavaScript.JDisplayObject is undefined");
JavaScript.JTextInput = JavaScript.Class(JavaScript.JDisplayObject, {
	Ctor : function() {
		this._is_default_text = false;
		this._default_text = "";
		let style = {};
		this._native = new PIXI.TextInput(style);
		this._native.disabled = true;
	},
	SetDisabled : function(value) {
		this._native.disabled = value;
	},
	IsDefaultText : function() {
		return this._is_default_text;
	},
	SetDefaultText : function(value, text) {
		this._is_default_text = value;
		this._default_text = text;
		if (this._is_default_text) {
			this._native.placeholder = text;
		} else {
			this._native.placeholder = "";
		}
	},
	SetPasswordMode : function(value) {
		if (value) {
			this._native.htmlInput.type = "password";
		} else {
			this._native.htmlInput.type = "text";
		}
	},
	SetWidth : function(width) {
		this._native.setInputStyle("width", Math.floor(width) + "px");
	},
	SetBold : function(value) {
		if (value) {
			this._native.setInputStyle("fontWeight", "bold");
		} else {
			this._native.setInputStyle("fontWeight", "normal");
		}
	},
	SetItalic : function(value) {
		if (value) {
			this._native.setInputStyle("fontStyle", "italic");
		} else {
			this._native.setInputStyle("fontStyle", "normal");
		}
	},
	SetText : function(value) {
		this._native.text = value;
	},
	GetText : function() {
		return this._native.text;
	},
	SetFont : function(path, size) {
		this._native.setInputStyle("fontSize", size + "px");
		this._native.setInputStyle("fontFamily", path);
	},
	SetRed : function(value) {
		this._red = Math.floor(value * 255);
		this._native.setInputStyle("color", JavaScript.RGBToHex(this._red, this._green, this._blue));
	},
	SetGreen : function(value) {
		this._green = Math.floor(value * 255);
		this._native.setInputStyle("color", JavaScript.RGBToHex(this._red, this._green, this._blue));
	},
	SetBlue : function(value) {
		this._blue = Math.floor(value * 255);
		this._native.setInputStyle("color", JavaScript.RGBToHex(this._red, this._green, this._blue));
	},
}, "JavaScript.JTextInput");

if (JavaScript.JDisplayObject === undefined) throw new Error(" extends class:JavaScript.JDisplayObject is undefined");
JavaScript.JTextEdit = JavaScript.Class(JavaScript.JDisplayObject, {
	Ctor : function() {
		let style = {};
		style.input = {};
		style.input.multiline = true;
		this._native = new PIXI.TextInput(style);
		this._native.disabled = true;
	},
	SetDisabled : function(value) {
		this._native.disabled = value;
	},
	SetWidth : function(width) {
		this._native.setInputStyle("width", Math.floor(width) + "px");
	},
	SetHeight : function(height) {
		this._native.setInputStyle("height", Math.floor(height) + "px");
	},
	SetBold : function(value) {
		if (value) {
			this._native.setInputStyle("fontWeight", "bold");
		} else {
			this._native.setInputStyle("fontWeight", "normal");
		}
	},
	SetItalic : function(value) {
		if (value) {
			this._native.setInputStyle("fontStyle", "italic");
		} else {
			this._native.setInputStyle("fontStyle", "normal");
		}
	},
	SetText : function(value) {
		this._native.text = value;
	},
	GetText : function() {
		return this._native.text;
	},
	SetFont : function(path, size) {
		this._native.setInputStyle("fontSize", size + "px");
		this._native.setInputStyle("fontFamily", path);
	},
	SetRed : function(value) {
		this._red = Math.floor(value * 255);
		this._native.setInputStyle("color", JavaScript.RGBToHex(this._red, this._green, this._blue));
	},
	SetGreen : function(value) {
		this._green = Math.floor(value * 255);
		this._native.setInputStyle("color", JavaScript.RGBToHex(this._red, this._green, this._blue));
	},
	SetBlue : function(value) {
		this._blue = Math.floor(value * 255);
		this._native.setInputStyle("color", JavaScript.RGBToHex(this._red, this._green, this._blue));
	},
}, "JavaScript.JTextEdit");

let __TEXTURELOADER_MAXID = 0;
if (ALittle.ITexture === undefined) throw new Error(" extends class:ALittle.ITexture is undefined");
JavaScript.JTexture = JavaScript.Class(ALittle.ITexture, {
	Ctor : function(texture, width, height) {
		this._texture = texture;
		this._width = width;
		this._height = height;
	},
	Clear : function() {
		this._texture = undefined;
	},
	get native() {
		return this._texture;
	},
	GetTexture : function() {
		return this;
	},
	GetWidth : function() {
		return this._width;
	},
	GetHeight : function() {
		return this._height;
	},
}, "JavaScript.JTexture");

if (ALittle.ITextureLoader === undefined) throw new Error(" extends class:ALittle.ITextureLoader is undefined");
JavaScript.JTextureLoader = JavaScript.Class(ALittle.ITextureLoader, {
	Ctor : function() {
		++ __TEXTURELOADER_MAXID;
		this._id = __TEXTURELOADER_MAXID;
		this._load_failed = false;
	},
	SetPath : function(big_path, altas, big_width, big_height, crypt_mode) {
		this._file_path = big_path;
		this._atlas_info = altas;
		this._width = big_width;
		this._height = big_height;
		this._altas = altas;
	},
	Start : function() {
		let real_path = undefined;
		let altas_list = ALittle.String_Split(this._altas, ";");
		let ___OBJECT_1 = altas_list;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let altas = ___OBJECT_1[index - 1];
			if (altas === undefined) break;
			let split = ALittle.String_Split(altas, ",");
			if (split[1 - 1] !== undefined) {
				real_path = split[1 - 1];
			}
		}
		if (real_path === undefined) {
			this.HandleLoadFailed();
			return;
		}
		let loader = new PIXI.Loader();
		loader.onError.add(this.HandleLoadFailed.bind(this));
		loader.add(this._file_path, real_path).load(this.HandleLoadSucceed.bind(this));
	},
	GetID : function() {
		return this._id;
	},
	GetPath : function() {
		return this._file_path;
	},
	HandleLoadSucceed : function(loader, resources) {
		if (this._load_failed) {
			return;
		}
		let resource = resources[this._file_path];
		if (resource === undefined || resource.texture === undefined) {
			this.HandleLoadFailed();
			return;
		}
		let func = window["__ALITTLEAPI_TextureLoadSucceed"];
		if (func === undefined) {
			return;
		}
		func(this, ALittle.NewObject(JavaScript.JTexture, resource.texture, resource.texture.orig.width, resource.texture.orig.height));
	},
	HandleLoadFailed : function() {
		if (this._load_failed) {
			return;
		}
		this._load_failed = true;
		let func = window["__ALITTLEAPI_TextureLoadFailed"];
		if (func === undefined) {
			return;
		}
		func(this);
	},
}, "JavaScript.JTextureLoader");

if (ALittle.ITextureCutLoader === undefined) throw new Error(" extends class:ALittle.ITextureCutLoader is undefined");
JavaScript.JTextureCutLoader = JavaScript.Class(ALittle.ITextureCutLoader, {
	Ctor : function() {
		++ __TEXTURELOADER_MAXID;
		this._id = __TEXTURELOADER_MAXID;
	},
	SetPath : function(path, max_width, max_height) {
	},
	Start : function() {
	},
	GetID : function() {
		return this._id;
	},
	GetPath : function() {
		return undefined;
	},
	GetMaxWidth : function() {
		return undefined;
	},
	GetMaxHeight : function() {
		return undefined;
	},
}, "JavaScript.JTextureCutLoader");

}
{
if (typeof JavaScript === "undefined") window.JavaScript = {};


let __CSVFILE_MAXID = 0;
if (ALittle.ICsvFileLoader === undefined) throw new Error(" extends class:ALittle.ICsvFileLoader is undefined");
JavaScript.JCsvFileLoader = JavaScript.Class(ALittle.ICsvFileLoader, {
	Ctor : function() {
		++ __CSVFILE_MAXID;
		this._id = __CSVFILE_MAXID;
	},
	Start : function() {
		this.StartImpl();
	},
	StartImpl : async function() {
		let host = location.hostname;
		let port = ALittle.Math_ToInt(location.port);
		if (port === undefined) {
			if (location.protocol === "https:") {
				port = 443;
			} else {
				port = 80;
			}
		}
		let path = this._file_path;
		ALittle.File_MakeDeepDir(ALittle.File_GetFilePathByPath(path));
		let error = await ALittle.HttpDownloadRequest(host, port, path, path);
		if (error !== undefined) {
			let func = window["__ALITTLEAPI_CsvFileLoadFailed"];
			if (func !== undefined) {
				func(this);
			}
			return;
		}
		let file = ALittle.NewObject(JavaScript.JCsvFile);
		if (!file.Load(path)) {
			let func = window["__ALITTLEAPI_CsvFileLoadFailed"];
			if (func !== undefined) {
				func(this);
			}
			return;
		}
		ALittle.File_DeleteFile(path);
		let func = window["__ALITTLEAPI_CsvFileLoadSucceed"];
		if (func !== undefined) {
			func(this, file);
		}
	},
	SetPath : function(file_path, only_from_asset) {
		this._file_path = file_path;
	},
	GetPath : function() {
		return this._file_path;
	},
	GetID : function() {
		return this._id;
	},
}, "JavaScript.JCsvFileLoader");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.String_CryptPassword = function(account_name, pwd) {
	let device_id_md5 = ALittle.String_MD5(ALittle.System_GetDeviceID());
	let account_name_md5 = ALittle.String_MD5(account_name);
	let device_id_md5_ex = ALittle.String_MD5("ALittle" + ALittle.System_GetDeviceID() + "ALittle");
	let account_name_md5_ex = ALittle.String_MD5("ALittle" + account_name + "ALittle");
	let device_id_md5_base64 = ALittle.String_Base64Encode(device_id_md5);
	let account_name_md5_base64 = ALittle.String_Base64Encode(account_name_md5);
	return ALittle.String_Base64Encode(device_id_md5_base64 + (ALittle.String_Base64Encode(device_id_md5_ex + pwd + account_name_md5_ex)) + account_name_md5_base64);
}

ALittle.String_DecryptPassword = function(account_name, pwd) {
	pwd = ALittle.String_Base64Decode(pwd);
	let device_id_md5 = ALittle.String_MD5(ALittle.System_GetDeviceID());
	let account_name_md5 = ALittle.String_MD5(account_name);
	let device_id_md5_ex = ALittle.String_MD5("ALittle" + ALittle.System_GetDeviceID() + "ALittle");
	let account_name_md5_ex = ALittle.String_MD5("ALittle" + account_name + "ALittle");
	let device_id_md5_base64 = ALittle.String_Base64Encode(device_id_md5);
	let account_name_md5_base64 = ALittle.String_Base64Encode(account_name_md5);
	let start_index = ALittle.String_Find(pwd, device_id_md5_base64);
	if (start_index === undefined) {
		return undefined;
	}
	pwd = ALittle.String_Sub(pwd, start_index + lua.String.len(device_id_md5_base64));
	start_index = ALittle.String_Find(pwd, account_name_md5_base64);
	if (start_index === undefined) {
		return undefined;
	}
	pwd = ALittle.String_Sub(pwd, 1, start_index - 1);
	pwd = ALittle.String_Base64Decode(pwd);
	start_index = ALittle.String_Find(pwd, device_id_md5_ex);
	if (start_index === undefined) {
		return undefined;
	}
	pwd = ALittle.String_Sub(pwd, start_index + lua.String.len(device_id_md5_ex));
	start_index = ALittle.String_Find(pwd, account_name_md5_ex);
	if (start_index === undefined) {
		return undefined;
	}
	pwd = ALittle.String_Sub(pwd, 1, start_index - 1);
	return pwd;
}

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.File_BaseFilePath = function() {
	return "";
}

ALittle.File_ExternalFilePath = function() {
	return "";
}

ALittle.File_CopyFile = function(src_path, dst_path) {
	return JavaScript.File_CopyFile(src_path, dst_path);
}

ALittle.File_CopyFileFromAsset = function(src_path, dst_path) {
	return JavaScript.File_CopyFile(src_path, dst_path);
}

ALittle.File_SaveFile = function(target_path, content, size) {
	return JavaScript.File_SaveFile(target_path, content);
}

ALittle.File_MD5 = function(path) {
	let content = JavaScript.File_LoadFile(path);
	if (content === undefined) {
		return "";
	}
	return md5(content);
}

ALittle.File_CopyDeepDir = function(src_path, dest_path, ext, log) {
	JavaScript.File_CopyDeepDir(src_path, dest_path, ext, log);
}

ALittle.File_ReadTextFromFile = function(file_path, crypt_mode) {
	return JavaScript.File_LoadFile(file_path);
}

ALittle.File_WriteTextToFile = function(content, file_path) {
	return ALittle.File_SaveFile(file_path, content, -1);
}

ALittle.File_ReadJsonFromFile = function(file_path, crypt_mode) {
	return [ALittle.File_ReadJsonFromStdFile(file_path)];
}

ALittle.File_ReadJsonFromAsset = function(file_path, crypt_mode) {
	return [ALittle.File_ReadJsonFromStdFile(file_path)];
}

ALittle.File_WriteJsonToFile = function(content, file_path) {
	return ALittle.File_SaveFile(file_path, lua.json.encode(content), -1);
}

ALittle.DeleteLog = function(day_count_before) {
}

}
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
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.IFileLoader === undefined) throw new Error(" extends class:ALittle.IFileLoader is undefined");
ALittle.JClientFileLoader = JavaScript.Class(ALittle.IFileLoader, {
	Load : function(file_path) {
		let content = undefined;
		let json = undefined;
		if (document.cookie !== undefined && document.cookie !== "") {
			let error = undefined;
			[error, json] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, document.cookie); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
			if (error !== undefined) {
				json = undefined;
			}
		}
		if (json === undefined) {
			return undefined;
		}
		return json[file_path];
	},
}, "ALittle.JClientFileLoader");

if (ALittle.IFileSaver === undefined) throw new Error(" extends class:ALittle.IFileSaver is undefined");
ALittle.JClientFileSaver = JavaScript.Class(ALittle.IFileSaver, {
	Save : function(file_path, content) {
		let json = undefined;
		if (document.cookie !== undefined && document.cookie !== "") {
			let error = undefined;
			[error, json] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, document.cookie); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
			if (error !== undefined) {
				json = undefined;
			}
		}
		if (json === undefined) {
			json = {};
		}
		json[file_path] = content;
		document.cookie = ALittle.String_JsonEncode(json);
		return true;
	},
}, "ALittle.JClientFileSaver");

ALittle.CreateConfigSystem = function(file_path, print_error) {
	return ALittle.NewObject(JavaScript.Template(ALittle.JsonConfig, "ALittle.JsonConfig<ALittle.JClientFileLoader, ALittle.JClientFileSaver>", ALittle.JClientFileLoader, ALittle.JClientFileSaver), file_path, print_error);
}

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(-1440165311, "ALittle.AppWillEnterBackground", {
name : "ALittle.AppWillEnterBackground", ns_name : "ALittle", rl_name : "AppWillEnterBackground", hash_code : -1440165311,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(521107426, "ALittle.AppDidEnterBackground", {
name : "ALittle.AppDidEnterBackground", ns_name : "ALittle", rl_name : "AppDidEnterBackground", hash_code : 521107426,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(708183011, "ALittle.NetChangeEvent", {
name : "ALittle.NetChangeEvent", ns_name : "ALittle", rl_name : "NetChangeEvent", hash_code : 708183011,
name_list : ["target","net_type"],
type_list : ["ALittle.EventDispatcher","int"],
option_map : {}
})
ALittle.RegStruct(760325696, "ALittle.AppDidEnterForeground", {
name : "ALittle.AppDidEnterForeground", ns_name : "ALittle", rl_name : "AppDidEnterForeground", hash_code : 760325696,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(812594882, "ALittle.AppWillEnterForeground", {
name : "ALittle.AppWillEnterForeground", ns_name : "ALittle", rl_name : "AppWillEnterForeground", hash_code : 812594882,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(1452333751, "ALittle.AppLowMemory", {
name : "ALittle.AppLowMemory", ns_name : "ALittle", rl_name : "AppLowMemory", hash_code : 1452333751,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})
ALittle.RegStruct(1720966934, "ALittle.NewIntentEvent", {
name : "ALittle.NewIntentEvent", ns_name : "ALittle", rl_name : "NewIntentEvent", hash_code : 1720966934,
name_list : ["target","url"],
type_list : ["ALittle.EventDispatcher","string"],
option_map : {}
})
ALittle.RegStruct(1755750412, "ALittle.ALittleJsonRPCInfo", {
name : "ALittle.ALittleJsonRPCInfo", ns_name : "ALittle", rl_name : "ALittleJsonRPCInfo", hash_code : 1755750412,
name_list : ["method","param"],
type_list : ["string","any"],
option_map : {}
})
ALittle.RegStruct(-840570937, "ALittle.NotifyJsonRPCEvent", {
name : "ALittle.NotifyJsonRPCEvent", ns_name : "ALittle", rl_name : "NotifyJsonRPCEvent", hash_code : -840570937,
name_list : ["target","method","param"],
type_list : ["ALittle.EventDispatcher","string","any"],
option_map : {}
})

ALittle.NetworkType = {
	NONE : "OtherSystem_NotifyNetwork_none",
	WIFI : "OtherSystem_NotifyNetwork_wifi",
	LINE : "OtherSystem_NotifyNetwork_line",
}

if (ALittle.EventDispatcher === undefined) throw new Error(" extends class:ALittle.EventDispatcher is undefined");
ALittle.OtherSystem = JavaScript.Class(ALittle.EventDispatcher, {
	Ctor : function() {
		this._network_started = false;
		this._system_select_directory = undefined;
		this._system_select_file = undefined;
		this._system_save_file = undefined;
		this._third_share_callback = undefined;
		this._third_login_callback = undefined;
		this._third_login_ing = false;
	},
	HandleWillEnterBackground : function() {
		this.DispatchEvent(___all_struct.get(-1440165311), {});
	},
	HandleDidEnterBackground : function() {
		this.DispatchEvent(___all_struct.get(521107426), {});
	},
	HandleWillEnterForeground : function() {
		this.DispatchEvent(___all_struct.get(812594882), {});
	},
	HandleDidEnterForeground : function() {
		this.DispatchEvent(___all_struct.get(760325696), {});
	},
	HandleLowMemory : function() {
		this.DispatchEvent(___all_struct.get(1452333751), {});
	},
	HandleNewIntent : function(url) {
		let event = {};
		event.url = url;
		this.DispatchEvent(___all_struct.get(1720966934), event);
	},
	AddEventListener : function(T, object, callback) {
		return ALittle.EventDispatcher.AddEventListener.call(this, T, object, callback);
	},
	HandleNetworkChanged : function(net_type) {
		let event = {};
		event.net_type = net_type;
		this.DispatchEvent(___all_struct.get(708183011), event);
	},
	GetNetworkType : function() {
		return ALittle.NetworkType.LINE;
	},
	HandleALittleJsonRPC : function(json) {
		let [error, content] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, json); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
		if (error !== undefined) {
			ALittle.Log("OtherSystem:HandleALittleJsonRPC:", error, json);
			return;
		}
		if (content.method === undefined) {
			return;
		}
		if (content.param === undefined) {
			return;
		}
		let event = {};
		event.target = this;
		event.method = content.method;
		event.param = content.param;
		this.DispatchEvent(___all_struct.get(-840570937), event);
	},
	SystemSelectDirectory : function(target, init_dir) {
		ALittle.Error("not support SystemSelectDirectory");
	},
	HandleSystemSelectDirectory : function(path) {
		if (this._system_select_directory === undefined) {
			return;
		}
		let tmp = this._system_select_directory;
		this._system_select_directory = undefined;
		let event = {};
		event.target = tmp;
		event.path = path;
		tmp.DispatchEvent(___all_struct.get(1800966813), event);
	},
	SystemSelectFile : function(target, init_dir) {
		ALittle.Error("not support SystemSelectFile");
	},
	HandleSystemSelectFile : function(path) {
		if (this._system_select_file === undefined) {
			return;
		}
		let tmp = this._system_select_file;
		this._system_select_file = undefined;
		let event = {};
		event.target = tmp;
		event.path = path;
		tmp.DispatchEvent(___all_struct.get(124598654), event);
	},
	SystemSaveFile : function(target, file_name, path) {
		ALittle.Error("not support SystemSelectFile");
	},
	HandleSystemSaveFile : function(path) {
		if (this._system_save_file === undefined) {
			return;
		}
		let tmp = this._system_save_file;
		this._system_save_file = undefined;
		let event = {};
		event.target = tmp;
		event.path = path;
		tmp.DispatchEvent(___all_struct.get(-1676610185), event);
	},
}, "ALittle.OtherSystem");

window.A_OtherSystem = ALittle.NewObject(ALittle.OtherSystem);
}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(384201948, "ALittle.ChunkInfo", {
name : "ALittle.ChunkInfo", ns_name : "ALittle", rl_name : "ChunkInfo", hash_code : 384201948,
name_list : ["file_path","callback","channel","volume","mute"],
type_list : ["string","Functor<(string,int)>","int","double","bool"],
option_map : {}
})
ALittle.RegStruct(1715346212, "ALittle.Event", {
name : "ALittle.Event", ns_name : "ALittle", rl_name : "Event", hash_code : 1715346212,
name_list : ["target"],
type_list : ["ALittle.EventDispatcher"],
option_map : {}
})

ALittle.AudioSystem = JavaScript.Class(undefined, {
	Ctor : function() {
		this._chunk_map = new Map();
		this._app_background = false;
		this._all_chunk_mute = false;
		this._music_mute = false;
		this._music_valume = 1;
		A_OtherSystem.AddEventListener(___all_struct.get(521107426), this, this.HandleDidEnterBackground);
		A_OtherSystem.AddEventListener(___all_struct.get(760325696), this, this.HandleDidEnterForeground);
	},
	HandleDidEnterBackground : function(event) {
		this._app_background = true;
		this.UpdateAllChunkVolume();
		this.UpdateMusicVolume();
	},
	HandleDidEnterForeground : function(event) {
		this._app_background = false;
		this.UpdateAllChunkVolume();
		this.UpdateMusicVolume();
	},
	UpdateChunkVolume : function(info) {
		let real_volume = info.volume;
		if (info.mute || this._app_background || this._all_chunk_mute) {
			real_volume = 0;
		}
		__CPPAPI_AudioSystem.SetChunkVolume(info.channel, real_volume);
	},
	UpdateMusicVolume : function() {
		let real_volume = this._music_valume;
		if (this._music_mute || this._app_background) {
			real_volume = 0;
		}
		__CPPAPI_AudioSystem.SetMusicVolume(real_volume);
	},
	UpdateAllChunkVolume : function() {
		for (let [k, v] of this._chunk_map) {
			if (v === undefined) continue;
			this.UpdateChunkVolume(v);
		}
	},
	SetAllChunkMute : function(mute) {
		if (this._all_chunk_mute === mute) {
			return;
		}
		this._all_chunk_mute = mute;
		this.UpdateAllChunkVolume();
	},
	SetMusicMute : function(mute) {
		if (this._music_mute === mute) {
			return;
		}
		this._music_mute = mute;
		this.UpdateMusicVolume();
	},
	GetAllChunkMute : function() {
		return this._all_chunk_mute;
	},
	GetMusicMute : function() {
		return this._music_mute;
	},
	AddChunkCache : function(file_path) {
		__CPPAPI_AudioSystem.AddChunkCache(file_path);
	},
	RemoveChunkCache : function(file_path) {
		__CPPAPI_AudioSystem.RemoveChunkCache(file_path);
	},
	StartChunk : function(file_path, loop, callback) {
		if (loop === undefined) {
			loop = 1;
		}
		let channel = __CPPAPI_AudioSystem.StartChunk(file_path, loop);
		if (channel < 0) {
			return -1;
		}
		let info = {};
		info.file_path = file_path;
		info.callback = callback;
		info.channel = channel;
		info.volume = __CPPAPI_AudioSystem.GetChunkVolume(channel);
		info.mute = false;
		this._chunk_map.set(channel, info);
		this.UpdateChunkVolume(info);
		return channel;
	},
	StopChunk : function(channel) {
		let info = this._chunk_map.get(channel);
		if (info === undefined) {
			return;
		}
		this._chunk_map.delete(channel);
		__CPPAPI_AudioSystem.StopChunk(channel);
	},
	SetChunkMute : function(channel, mute) {
		let info = this._chunk_map.get(channel);
		if (info === undefined) {
			return;
		}
		if (info.mute === mute) {
			return;
		}
		info.mute = mute;
		this.UpdateChunkVolume(info);
	},
	GetChunkMute : function(channel) {
		let info = this._chunk_map.get(channel);
		if (info === undefined) {
			return false;
		}
		return info.mute;
	},
	SetChunkVolume : function(channel, volume) {
		let info = this._chunk_map.get(channel);
		if (info === undefined) {
			return;
		}
		info.volume = volume;
		this.UpdateChunkVolume(info);
	},
	GetChunkVolume : function(channel) {
		let info = this._chunk_map.get(channel);
		if (info === undefined) {
			return 0;
		}
		return info.volume;
	},
	HandleAudioChunkStopedEvent : function(channel) {
		let info = this._chunk_map.get(channel);
		if (info === undefined) {
			return;
		}
		this._chunk_map.delete(channel);
		if (info.callback === undefined) {
			return;
		}
		info.callback(info.file_path, info.channel);
	},
	StartMusic : function(file_path, loop) {
		if (loop === undefined) {
			loop = 1;
		}
		let result = __CPPAPI_AudioSystem.StartMusic(file_path, loop);
		if (result) {
			return false;
		}
		this._music_valume = __CPPAPI_AudioSystem.GetMusicVolume();
		this.UpdateMusicVolume();
		return result;
	},
	StopMusic : function() {
		__CPPAPI_AudioSystem.StopMusic();
	},
	StartRecord : function(file_path) {
		return __CPPAPI_AudioSystem.StartRecord(file_path);
	},
	IsRecording : function() {
		return __CPPAPI_AudioSystem.IsRecording();
	},
	StopRecord : function() {
		__CPPAPI_AudioSystem.StopRecord();
	},
}, "ALittle.AudioSystem");

window.A_AudioSystem = ALittle.NewObject(ALittle.AudioSystem);
}
{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(1376035901, "ALittle.ModuleInfo", {
name : "ALittle.ModuleInfo", ns_name : "ALittle", rl_name : "ModuleInfo", hash_code : 1376035901,
name_list : ["name","crypt_mode","control","module","plugin_loaded","module_loaded","browser_loaded","layer_group","browser_setup","browser_addmodule","browser_shutdown","module_setup","module_shutdown","module_getinfo","plugin_setup","plugin_shutdown"],
type_list : ["string","bool","ALittle.ControlSystem","any","bool","bool","bool","ALittle.DisplayLayout","Functor<(ALittle.DisplayLayout,ALittle.ControlSystem,string,string)>","Functor<(string,ALittle.DisplayLayout,ALittle.ModuleShortInfo):bool>","Functor<()>","Functor<(ALittle.DisplayLayout,ALittle.ControlSystem,string,string)>","Functor<()>","Functor<(ALittle.ControlSystem,string):ALittle.ModuleShortInfo>","Functor<(ALittle.ControlSystem,string,string)>","Functor<()>"],
option_map : {}
})
ALittle.RegStruct(-1652314301, "ALittle.ModuleShortInfo", {
name : "ALittle.ModuleShortInfo", ns_name : "ALittle", rl_name : "ModuleShortInfo", hash_code : -1652314301,
name_list : ["title","icon","width_type","width_value","height_type","height_value"],
type_list : ["string","string","int","int","int","int"],
option_map : {}
})

ALittle.ModuleSystem = JavaScript.Class(undefined, {
	Ctor : function() {
		this._name_module_map = {};
		this._main_module = undefined;
	},
	GetMainModuleName : function() {
		if (this._main_module === undefined) {
			return undefined;
		}
		return this._main_module.name;
	},
	GetDebugInfo : function() {
		return this._debug_info;
	},
	LoadModuleImpl : function(module_base_path, name) {
		return new Promise((async function(___COROUTINE, ___) {
			let info = {};
			info.name = name;
			if (window[name] === undefined) {
				await Require(module_base_path, "JSScript/Main");
			}
			info.module = window[name];
			if (info.module === undefined) {
				___COROUTINE(undefined); return;
			}
			info.crypt_mode = false;
			info.control = ALittle.NewObject(ALittle.ControlSystem, name, info.crypt_mode);
			await info.control.RegisterInfoByHttp();
			this._name_module_map[name] = info;
			info.browser_setup = info.module["__Browser_Setup"];
			info.browser_addmodule = info.module["__Browser_AddModule"];
			info.browser_shutdown = info.module["__Browser_Shutdown"];
			info.module_setup = info.module["__Module_Setup"];
			info.module_shutdown = info.module["__Module_Shutdown"];
			info.module_getinfo = info.module["__Module_GetInfo"];
			info.plugin_setup = info.module["__Plugin_Setup"];
			info.plugin_shutdown = info.module["__Plugin_Shutdown"];
			let control = info.control;
			if (this._main_module !== undefined) {
				control = this._main_module.control;
			}
			info.layer_group = ALittle.NewObject(ALittle.DisplayLayout, control);
			___COROUTINE(info); return;
		}).bind(this));
	},
	RemoveModule : function(name) {
		if (this._main_module !== undefined && this._main_module.name === name) {
			return false;
		}
		let info = this._name_module_map[name];
		if (info === undefined) {
			return false;
		}
		let module_shutdown = info.module_shutdown;
		if (module_shutdown !== undefined) {
			module_shutdown();
		}
		delete this._name_module_map[name];
		A_LayerManager.RemoveChild(info.layer_group);
		delete window[name];
		return true;
	},
	LoadPlugin : function(module_name) {
		return new Promise((async function(___COROUTINE, ___) {
			let module_base_path = "Module/" + module_name + "/";
			if (module_name === undefined) {
				ALittle.Log("module_name is null!");
				___COROUTINE(undefined); return;
			}
			let info = this._name_module_map[module_name];
			if (info === undefined) {
				info = await this.LoadModuleImpl(module_base_path, module_name);
				if (info === undefined) {
					ALittle.Log("Module:" + module_name + " load failed!");
					___COROUTINE(undefined); return;
				}
			}
			if (info.plugin_loaded) {
				___COROUTINE(info.control); return;
			}
			let setup_func = info.plugin_setup;
			if (setup_func === undefined) {
				ALittle.Log("can't find Plugin_Setup funciton in Module:" + module_name);
				___COROUTINE(undefined); return;
			}
			info.plugin_loaded = true;
			setup_func(info.control, module_base_path, module_base_path + "JSScript/");
			___COROUTINE(info.control); return;
		}).bind(this));
	},
	LoadModule : function(module_base_path, module_name) {
		return new Promise((async function(___COROUTINE, ___) {
			if (module_name === undefined) {
				ALittle.Log("module_name is null!");
				___COROUTINE(false); return;
			}
			let info = this._name_module_map[module_name];
			if (info === undefined) {
				info = await this.LoadModuleImpl(module_base_path, module_name);
				if (info === undefined) {
					ALittle.Log("Module:" + module_name + " load failed!");
					___COROUTINE(false); return;
				}
			}
			if (info.module_loaded) {
				ALittle.Log(module_name + ":__Module_Setup already invoked!");
				___COROUTINE(false); return;
			}
			let setup_func = info.module_setup;
			if (setup_func === undefined) {
				ALittle.Log("can't find Module_Setup funciton in Module:" + module_name);
				___COROUTINE(false); return;
			}
			info.module_loaded = true;
			if (this._main_module.name !== module_name) {
				let result = false;
				if (this._main_module !== undefined && this._main_module.browser_addmodule !== undefined) {
					let module_info = undefined;
					if (info.module_getinfo !== undefined) {
						module_info = info.module_getinfo(info.control, module_base_path);
					}
					result = this._main_module.browser_addmodule(module_name, info.layer_group, module_info);
				}
				if (!result) {
					A_LayerManager.AddChild(info.layer_group, A_LayerManager.group_count - 1);
				}
			}
			setup_func(info.layer_group, info.control, module_base_path, module_base_path + "JSScript/");
			___COROUTINE(true); return;
		}).bind(this));
	},
	MainSetup : async function(base_path, module_name, debug_info) {
		if (this._main_module !== undefined) {
			return;
		}
		if (module_name === undefined) {
			module_name = ALittle.File_ReadTextFromFile("Module/Enter.ali", false);
		}
		if (module_name === undefined) {
			ALittle.Log("Load Enter.ali failed!");
			return;
		}
		let info = await this.LoadModuleImpl(base_path, module_name);
		if (info === undefined) {
			ALittle.Log("Module:" + module_name + " load failed!");
			return;
		}
		A_LayerManager.AddChild(info.layer_group, A_LayerManager.group_count - 1);
		this._main_module = info;
		this._debug_info = debug_info;
		let module_base_path = "Module/" + module_name + "/";
		this._main_module.browser_loaded = true;
		let setup_func = this._main_module.browser_setup;
		if (setup_func === undefined) {
			await this.LoadModule(module_base_path, this._main_module.name);
			return;
		}
		setup_func(this._main_module.layer_group, this._main_module.control, module_base_path, module_base_path + "JSScript/");
	},
	MainShutdown : function() {
		if (this._main_module === undefined) {
			return;
		}
		let ___OBJECT_1 = this._name_module_map;
		for (let name in ___OBJECT_1) {
			let info = ___OBJECT_1[name];
			if (info === undefined) continue;
			let shutdown_func = info.module_shutdown;
			if (shutdown_func !== undefined && info.module_loaded) {
				let error = (function() { try { shutdown_func.call(); return undefined; } catch (___ERROR) { return ___ERROR.message; } }).call(this);
				if (error !== undefined) {
					ALittle.Log("ModuleSystem:MainShutdown invoke __Module_Shutdown error:", error);
				}
			}
			shutdown_func = info.plugin_shutdown;
			if (shutdown_func !== undefined && info.plugin_loaded) {
				let error = (function() { try { shutdown_func.call(); return undefined; } catch (___ERROR) { return ___ERROR.message; } }).call(this);
				if (error !== undefined) {
					ALittle.Log("ModuleSystem:MainShutdown invoke __Plugin_Shutdown error:", error);
				}
			}
		}
		let shutdown_func = this._main_module.browser_shutdown;
		if (shutdown_func === undefined) {
			return;
		}
		shutdown_func();
	},
}, "ALittle.ModuleSystem");

window.A_ModuleSystem = ALittle.NewObject(ALittle.ModuleSystem);
}
{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(-1040774381, "ALittle.CsvPreloadInfo", {
name : "ALittle.CsvPreloadInfo", ns_name : "ALittle", rl_name : "CsvPreloadInfo", hash_code : -1040774381,
name_list : ["total","succeed","failed","loader_map","callback"],
type_list : ["int","int","int","Map<int,ALittle.CsvPreloadInfoDetail>","Functor<(int,int,int)>"],
option_map : {}
})
ALittle.RegStruct(332955965, "ALittle.CsvPreloadInfoDetail", {
name : "ALittle.CsvPreloadInfoDetail", ns_name : "ALittle", rl_name : "CsvPreloadInfoDetail", hash_code : 332955965,
name_list : ["loader","config"],
type_list : ["ALittle.ICsvFileLoader","ALittle.CsvConfig"],
option_map : {}
})

ALittle.CsvConfigManager = JavaScript.Class(undefined, {
	Ctor : function() {
		this._preload_map = new Map();
	},
	PrepareCsv : function(csv_map, callback) {
		let preload_info = {};
		preload_info.total = 0;
		preload_info.succeed = 0;
		preload_info.failed = 0;
		preload_info.loader_map = new Map();
		preload_info.callback = callback;
		let ___OBJECT_1 = csv_map;
		for (let file_path in ___OBJECT_1) {
			let config = ___OBJECT_1[file_path];
			if (config === undefined) continue;
			let loader = undefined;
			loader = ALittle.NewObject(JavaScript.JCsvFileLoader);
			loader.SetPath(file_path, false);
			let detail = {};
			detail.loader = loader;
			detail.config = config;
			preload_info.loader_map.set(loader.GetID(), detail);
			loader.Start();
			++ preload_info.total;
		}
		if (preload_info.total > preload_info.succeed + preload_info.failed) {
			this._preload_map.set(preload_info, true);
		}
		if (callback !== undefined) {
			callback(preload_info.total, preload_info.succeed, preload_info.failed);
		}
	},
	HandleCsvFileLoadSucceed : function(loader, file) {
		let id = loader.GetID();
		for (let [info, value] of this._preload_map) {
			if (value === undefined) continue;
			let detail = info.loader_map.get(id);
			if (detail !== undefined) {
				++ info.succeed;
				if (detail.config !== undefined) {
					detail.config.Init(file);
				}
				if (info.callback !== undefined) {
					info.callback(info.total, info.succeed, info.failed);
				}
				if (info.total === info.succeed + info.failed) {
					this._preload_map.delete(info);
				}
				return;
			}
		}
	},
	HandleCsvFileLoadFailed : function(loader) {
		ALittle.Error("csv load failed! path:" + loader.GetPath());
		let id = loader.GetID();
		for (let [info, value] of this._preload_map) {
			if (value === undefined) continue;
			let detail = info.loader_map.get(id);
			if (detail !== undefined) {
				++ info.failed;
				if (detail.config !== undefined) {
					detail.config.Init(undefined);
				}
				if (info.callback !== undefined) {
					info.callback(info.total, info.succeed, info.failed);
				}
				if (info.total === info.succeed + info.failed) {
					this._preload_map.delete(info);
				}
				return;
			}
		}
	},
}, "ALittle.CsvConfigManager");

window.A_CsvConfigManager = ALittle.NewObject(ALittle.CsvConfigManager);
}
{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(1653869333, "ALittle.LoopGroupInfo", {
name : "ALittle.LoopGroupInfo", ns_name : "ALittle", rl_name : "LoopGroupInfo", hash_code : 1653869333,
name_list : ["childs"],
type_list : ["List<ALittle.LoopListInfo>"],
option_map : {}
})
ALittle.RegStruct(-1741432339, "ALittle.LoopListInfo", {
name : "ALittle.LoopListInfo", ns_name : "ALittle", rl_name : "LoopListInfo", hash_code : -1741432339,
name_list : ["link","attribute","init","childs"],
type_list : ["string","string","any","List<ALittle.LoopChildInfo>"],
option_map : {}
})
ALittle.RegStruct(-925381158, "ALittle.LoopChildInfo", {
name : "ALittle.LoopChildInfo", ns_name : "ALittle", rl_name : "LoopChildInfo", hash_code : -925381158,
name_list : ["clazz","target","total_time","delay_time"],
type_list : ["string","any","int","int"],
option_map : {}
})

ALittle.LoopAnimation = JavaScript.Class(undefined, {
	Ctor : function(from, info) {
		this._from = from;
		this._info = info;
	},
	Init : function(map) {
		this.Stop();
		this._group = ALittle.NewObject(ALittle.LoopGroup);
		this._group.complete_callback = this.Completed.bind(this);
		this._save_value_map = new Map();
		this._init_value_map = new Map();
		let ___OBJECT_1 = this._info.childs;
		for (let _ = 1; _ <= ___OBJECT_1.length; ++_) {
			let list = ___OBJECT_1[_ - 1];
			if (list === undefined) break;
			let target = undefined;
			if (map !== undefined) {
				target = map[list.link];
			}
			if (target === undefined && this._from !== undefined) {
				target = this._from[list.link];
			}
			if (target === undefined) {
				this._group = undefined;
				this._save_value_map = undefined;
				this._init_value_map = undefined;
				return "can't find link:" + list.link + " from map or object";
			}
			let value_map = this._save_value_map.get(target);
			if (value_map === undefined) {
				value_map = {};
				this._save_value_map.set(target, value_map);
			}
			value_map[list.attribute] = target[list.attribute];
			if (list.init !== undefined) {
				target[list.attribute] = list.init;
				value_map = this._init_value_map.get(target);
				if (value_map === undefined) {
					value_map = {};
					this._init_value_map.set(target, value_map);
				}
				value_map[list.attribute] = list.init;
			}
			let loop_list = ALittle.NewObject(ALittle.LoopList);
			let ___OBJECT_2 = list.childs;
			for (let index = 1; index <= ___OBJECT_2.length; ++index) {
				let info = ___OBJECT_2[index - 1];
				if (info === undefined) break;
				if (info.clazz === "LoopLinear") {
					loop_list.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, target, list.attribute, info.target, info.total_time, info.delay_time));
				} else if (info.clazz === "LoopAttribute") {
					loop_list.AddUpdater(ALittle.NewObject(ALittle.LoopAttribute, target, list.attribute, info.target, info.delay_time));
				} else if (info.clazz === "LoopRit") {
					loop_list.AddUpdater(ALittle.NewObject(ALittle.LoopRit, target, list.attribute, info.target, info.total_time, info.delay_time));
				}
			}
			this._group.AddUpdater(loop_list);
		}
		return undefined;
	},
	Completed : function() {
		if (this._loop === 0) {
			this.ReleaseCo(undefined);
			return;
		}
		if (this._loop > 0) {
			-- this._loop;
			if (this._loop <= 0) {
				this.ReleaseCo(undefined);
				return;
			}
		}
		this.SetTime(0);
		this._group.Start();
	},
	Play : function(loop) {
		this.ReleaseCo("Play被调用");
		if (this._group === undefined) {
			return;
		}
		if (loop === undefined) {
			this._loop = 1;
		} else if (loop === 0) {
			this._loop = -1;
		} else {
			this._loop = loop;
		}
		this._group.Start();
	},
	AsyncPlay : function(loop) {
		return new Promise((function(___COROUTINE, ___) {
			this.ReleaseCo("AsyncPlay被调用");
			if (this._group === undefined) {
				___COROUTINE("this._group == null"); return;
			}
			if (___COROUTINE === undefined) {
				___COROUTINE("当前不是协程"); return;
			}
			this._co = ___COROUTINE;
			if (loop === undefined) {
				this._loop = 1;
			} else if (loop === 0) {
				this._loop = -1;
			} else {
				this._loop = loop;
			}
			this._group.Start();
			return;
		}).bind(this));
	},
	ReleaseCo : function(reason) {
		if (this._co === undefined) {
			return;
		}
		let [result, error] = ALittle.Coroutine.Resume(this._co, reason);
		if (result !== true) {
			ALittle.Error(error);
		}
		this._co = undefined;
	},
	Pause : function() {
		if (this._group === undefined) {
			return;
		}
		this._group.Stop();
	},
	SetTime : function(time) {
		this.ReleaseCo("SetTime被调用");
		if (this._group === undefined) {
			return;
		}
		if (this._save_value_map !== undefined) {
			for (let [object, value_map] of this._save_value_map) {
				if (value_map === undefined) continue;
				let ___OBJECT_3 = value_map;
				for (let attr in ___OBJECT_3) {
					let param = ___OBJECT_3[attr];
					if (param === undefined) continue;
					object[attr] = param;
				}
			}
		}
		if (this._init_value_map !== undefined) {
			for (let [object, value_map] of this._init_value_map) {
				if (value_map === undefined) continue;
				let ___OBJECT_4 = value_map;
				for (let attr in ___OBJECT_4) {
					let param = ___OBJECT_4[attr];
					if (param === undefined) continue;
					object[attr] = param;
				}
			}
		}
		this._group.SetTime(time);
	},
	Stop : function() {
		this.ReleaseCo("Stop被调用");
		if (this._group !== undefined) {
			this._group.Stop();
			this._group = undefined;
		}
		if (this._save_value_map !== undefined) {
			for (let [object, value_map] of this._save_value_map) {
				if (value_map === undefined) continue;
				let ___OBJECT_5 = value_map;
				for (let attr in ___OBJECT_5) {
					let param = ___OBJECT_5[attr];
					if (param === undefined) continue;
					object[attr] = param;
				}
			}
			this._save_value_map = undefined;
		}
		this._init_value_map = undefined;
	},
}, "ALittle.LoopAnimation");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.LoopObject === undefined) throw new Error(" extends class:ALittle.LoopObject is undefined");
ALittle.LoopAttribute = JavaScript.Class(ALittle.LoopObject, {
	Ctor : function(target, property, target_value, delay_time) {
		this._target = target;
		this._property = property;
		this._target_value = target_value;
		if (delay_time === undefined || delay_time < 0) {
			delay_time = 0;
		}
		this._total_delay_time = delay_time;
		this._accumulate_count = 0;
		this._accumulate_delay_time = 0;
		this._complete_callback = undefined;
	},
	get complete_callback() {
		return this._complete_callback;
	},
	set complete_callback(value) {
		this._complete_callback = value;
	},
	Reset : function() {
		this._accumulate_count = 0;
		this._accumulate_delay_time = 0;
	},
	Completed : function() {
		if (this._complete_callback !== undefined) {
			this._complete_callback();
		}
	},
	IsCompleted : function() {
		return this._accumulate_count >= 1;
	},
	SetCompleted : function() {
		if (this._accumulate_count >= 1) {
			return;
		}
		this._accumulate_count = 1;
		this._accumulate_delay_time = this._total_delay_time;
		this._target[this._property] = this._target_value;
	},
	SetTime : function(time) {
		this._accumulate_count = 0;
		this._accumulate_delay_time = 0;
		if (time <= 0) {
			return [0, false];
		}
		if (time <= this._total_delay_time) {
			this._accumulate_delay_time = time;
			return [0, false];
		}
		this._accumulate_delay_time = this._total_delay_time;
		this._accumulate_count = 1;
		this._target[this._property] = this._target_value;
		return [time - this._total_delay_time, true];
	},
	Update : function(frame_time) {
		if (this._accumulate_delay_time < this._total_delay_time) {
			this._accumulate_delay_time = this._accumulate_delay_time + (frame_time);
			if (this._accumulate_delay_time < this._total_delay_time) {
				return;
			}
			this._accumulate_delay_time = this._total_delay_time;
		}
		if (this._accumulate_count >= 1) {
			return;
		}
		this._accumulate_count = 1;
		this._target[this._property] = this._target_value;
	},
}, "ALittle.LoopAttribute");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.LoopObject === undefined) throw new Error(" extends class:ALittle.LoopObject is undefined");
ALittle.LoopLinear = JavaScript.Class(ALittle.LoopObject, {
	Ctor : function(target, property, target_value, total_time, delay_time, func) {
		this._target = target;
		this._target_value = target_value;
		this._func = func;
		if (total_time === undefined || total_time < 0) {
			total_time = 0;
		}
		this._total_time = total_time;
		if (delay_time === undefined || delay_time < 0) {
			delay_time = 0;
		}
		this._total_delay_time = delay_time;
		this._accumulate_time = 0;
		this._accumulate_delay_time = 0;
		if (target === undefined || target[property] === undefined) {
			this._accumulate_time = this._total_time;
			ALittle.Log("LoopLinear create failed:loop_target is nil or property is nil");
			return;
		}
		this._property = property;
		this._complete_callback = undefined;
		this._speed = undefined;
		this._init_value = undefined;
	},
	get complete_callback() {
		return this._complete_callback;
	},
	set complete_callback(value) {
		this._complete_callback = value;
	},
	get speed() {
		if (this._speed !== undefined) {
			return this._speed;
		}
		if (this._init_value === undefined) {
			this._init_value = this._target[this._property];
		}
		this._speed = (this._target_value - this._init_value) / this._total_time;
		return this._speed;
	},
	Reset : function() {
		this._accumulate_time = 0;
		this._accumulate_delay_time = 0;
		this._init_value = undefined;
	},
	SetTime : function(time) {
		this._accumulate_delay_time = 0;
		this._accumulate_time = 0;
		if (time <= 0) {
			return [0, false];
		}
		if (time <= this._total_delay_time) {
			this._accumulate_delay_time = time;
			return [0, false];
		}
		this._accumulate_delay_time = this._total_delay_time;
		time = time - (this._total_delay_time);
		if (time < this._total_time) {
			this._accumulate_time = time;
			if (this._init_value === undefined) {
				this._init_value = this._target[this._property];
			}
			let current_value = (this._accumulate_time * this._target_value + (this._total_time - this._accumulate_time) * this._init_value) / this._total_time;
			this._target[this._property] = current_value;
			return [0, false];
		}
		this._target[this._property] = this._target_value;
		this._accumulate_time = this._total_time;
		if (this._func !== undefined) {
			this._func();
		}
		return [time - this._total_time, true];
	},
	IsCompleted : function() {
		return this._accumulate_time >= this._total_time;
	},
	Completed : function() {
		if (this._complete_callback !== undefined) {
			this._complete_callback();
		}
	},
	SetCompleted : function() {
		if (this._accumulate_time >= this._total_time) {
			return;
		}
		this.SetTime(this._total_time + this._total_delay_time);
	},
	Update : function(frame_time) {
		if (this._accumulate_delay_time < this._total_delay_time) {
			this._accumulate_delay_time = this._accumulate_delay_time + (frame_time);
			if (this._accumulate_delay_time < this._total_delay_time) {
				return;
			}
			frame_time = this._accumulate_delay_time - this._total_delay_time;
			this._accumulate_delay_time = this._total_delay_time;
		}
		if (this._init_value === undefined) {
			this._init_value = this._target[this._property];
		}
		this._accumulate_time = this._accumulate_time + (frame_time);
		if (this._accumulate_time > this._total_time) {
			this._accumulate_time = this._total_time;
		}
		let current_value = (this._accumulate_time * this._target_value + (this._total_time - this._accumulate_time) * this._init_value) / this._total_time;
		this._target[this._property] = current_value;
		if (this._func !== undefined) {
			this._func();
		}
	},
}, "ALittle.LoopLinear");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.LoopObject === undefined) throw new Error(" extends class:ALittle.LoopObject is undefined");
ALittle.LoopRit = JavaScript.Class(ALittle.LoopObject, {
	Ctor : function(target, property, target_value, total_time, delay_time, func) {
		this._target = target;
		this._target_value = target_value;
		this._func = func;
		if (total_time === undefined || total_time < 0) {
			total_time = 0;
		}
		this._total_time = total_time;
		if (delay_time === undefined || delay_time < 0) {
			delay_time = 0;
		}
		this._total_delay_time = delay_time;
		this._accumulate_time = 0;
		this._accumulate_delay_time = 0;
		if (target === undefined || target[property] === undefined) {
			this._accumulate_time = this._total_time;
			ALittle.Log("LoopRit create failed:loop_target is nil or property is nil");
			return;
		}
		this._property = property;
		this._init_value = undefined;
		this._complete_callback = undefined;
	},
	get complete_callback() {
		return this._complete_callback;
	},
	set complete_callback(value) {
		this._complete_callback = value;
	},
	Reset : function() {
		this._accumulate_time = 0;
		this._accumulate_delay_time = 0;
		this._init_value = undefined;
	},
	Completed : function() {
		if (this._complete_callback !== undefined) {
			this._complete_callback();
		}
	},
	IsCompleted : function() {
		return this._accumulate_time >= this._total_time;
	},
	SetCompleted : function() {
		if (this._accumulate_time >= this._total_time) {
			return;
		}
		this.SetTime(this._total_time + this._total_delay_time);
	},
	SetTime : function(time) {
		this._accumulate_delay_time = 0;
		this._accumulate_time = 0;
		if (time <= 0) {
			return [0, false];
		}
		if (time <= this._total_delay_time) {
			this._accumulate_delay_time = time;
			return [0, false];
		}
		this._accumulate_delay_time = this._total_delay_time;
		time = time - (this._total_delay_time);
		if (time < this._total_time) {
			this._accumulate_time = time;
			let current_value = (this._target_value - this._init_value) * ALittle.Math_Sin((this._accumulate_time / this._total_time) * 1.57) + this._init_value;
			this._target[this._property] = current_value;
			return [0, false];
		}
		this._target[this._property] = this._target_value;
		this._accumulate_time = this._total_time;
		if (this._func !== undefined) {
			this._func();
		}
		return [time - this._total_time, true];
	},
	Update : function(frame_time) {
		if (this._accumulate_delay_time < this._total_delay_time) {
			this._accumulate_delay_time = this._accumulate_delay_time + (frame_time);
			if (this._accumulate_delay_time < this._total_delay_time) {
				return;
			}
			frame_time = this._accumulate_delay_time - this._total_delay_time;
			this._accumulate_delay_time = this._total_delay_time;
		}
		if (this._init_value === undefined) {
			this._init_value = this._target[this._property];
		}
		this._accumulate_time = this._accumulate_time + (frame_time);
		if (this._accumulate_time > this._total_time) {
			this._accumulate_time = this._total_time;
		}
		let current_value = (this._target_value - this._init_value) * ALittle.Math_Sin((this._accumulate_time / this._total_time) * 1.57) + this._init_value;
		this._target[this._property] = current_value;
		if (this._func !== undefined) {
			this._func();
		}
	},
}, "ALittle.LoopRit");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


ALittle.UIEnumTypes = {
	FLIP_NONE : 0,
	FLIP_H : 1,
	FLIP_V : 2,
	FLIP_HV : 3,
	POS_ABS : 1,
	POS_ALIGN_STARTING : 2,
	POS_ALIGN_CENTER : 3,
	POS_ALIGN_ENDING : 4,
	POS_PERCENT_STARTING : 7,
	POS_PERCENT_CENTER : 8,
	POS_PERCENT_ENDING : 9,
	SIZE_ABS : 1,
	SIZE_PERCENT : 2,
	SIZE_MARGIN : 4,
	HALIGN_LEFT : 0,
	HALIGN_CENTER : 1,
	HALIGN_RIGHT : 2,
	VALIGN_TOP : 0,
	VALIGN_CENTER : 1,
	VALIGN_BOTTOM : 2,
	TYPE_H : 1,
	TYPE_V : 2,
	DIR_UP : 1,
	DIR_DOWN : 2,
	DIR_LEFT : 3,
	DIR_RIGHT : 4,
	FREE : 1,
	FIXED : 2,
	SELECT_NONE : 0,
	SELECT_FILE : 1,
	SELECT_DIR : 2,
	KMOD_NONE : 0x0000,
	KMOD_LSHIFT : 0x0001,
	KMOD_RSHIFT : 0x0002,
	KMOD_LCTRL : 0x0040,
	KMOD_RCTRL : 0x0080,
	KMOD_LALT : 0x0100,
	KMOD_RALT : 0x0200,
	KMOD_LGUI : 0x0400,
	KMOD_RGUI : 0x0800,
	KMOD_NUM : 0x1000,
	KMOD_CAPS : 0x2000,
	KMOD_MODE : 0x4000,
	KMOD_RESERVED : 0x8000,
	KMOD_CTRL : 0x00c0,
	KMOD_SHIFT : 0x0003,
	KMOD_ALT : 0x0300,
	KMOD_GUI : 0x0c00,
	Z : 122,
	S : 115,
	N : 110,
	F5 : 1073741886,
	CTRL : 1073742048,
	VIEW_FULLSCREEN : 0x00000001,
	VIEW_OPENGL : 0x00000002,
	VIEW_SHOWN : 0x00000004,
	VIEW_HIDDEN : 0x00000008,
	VIEW_BORDERLESS : 0x00000010,
	VIEW_RESIZABLE : 0x00000020,
	VIEW_MINIMIZED : 0x00000040,
	VIEW_MAXIMIZED : 0x00000080,
	VIEW_INPUT_GRABBED : 0x00000100,
	VIEW_INPUT_FOCUS : 0x00000200,
	VIEW_MOUSE_FOCUS : 0x00000400,
	VIEW_FULLSCREEN_DESKTOP : 0x00001001,
	VIEW_FOREIGN : 0x00000800,
	VIEW_ALLOW_HIGHDPI : 0x00002000,
	VIEW_MOUSE_CAPTURE : 0x00004000,
	VIEW_SHAPED_WINDOW : 0x10000000,
}

}
{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(544684311, "ALittle.UIMoveInEvent", {
name : "ALittle.UIMoveInEvent", ns_name : "ALittle", rl_name : "UIMoveInEvent", hash_code : 544684311,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(683647260, "ALittle.UIMButtonUpEvent", {
name : "ALittle.UIMButtonUpEvent", ns_name : "ALittle", rl_name : "UIMButtonUpEvent", hash_code : 683647260,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(734860930, "ALittle.UIFingerUpEvent", {
name : "ALittle.UIFingerUpEvent", ns_name : "ALittle", rl_name : "UIFingerUpEvent", hash_code : 734860930,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","finger_key","is_sfc","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","string","bool","bool"],
option_map : {}
})
ALittle.RegStruct(776398171, "ALittle.UIEnterKeyEvent", {
name : "ALittle.UIEnterKeyEvent", ns_name : "ALittle", rl_name : "UIEnterKeyEvent", hash_code : 776398171,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(809518110, "ALittle.UIDragUpEvent", {
name : "ALittle.UIDragUpEvent", ns_name : "ALittle", rl_name : "UIDragUpEvent", hash_code : 809518110,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(882286932, "ALittle.UIKeyEvent", {
name : "ALittle.UIKeyEvent", ns_name : "ALittle", rl_name : "UIKeyEvent", hash_code : 882286932,
name_list : ["target","mod","sym","scancode","custom","handled"],
type_list : ["ALittle.DisplayObject","int","int","int","bool","bool"],
option_map : {}
})
ALittle.RegStruct(958494922, "ALittle.UIChangedEvent", {
name : "ALittle.UIChangedEvent", ns_name : "ALittle", rl_name : "UIChangedEvent", hash_code : 958494922,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(1213009422, "ALittle.UIKeyUpEvent", {
name : "ALittle.UIKeyUpEvent", ns_name : "ALittle", rl_name : "UIKeyUpEvent", hash_code : 1213009422,
name_list : ["target","mod","sym","scancode","custom","handled"],
type_list : ["ALittle.DisplayObject","int","int","int","bool","bool"],
option_map : {}
})
ALittle.RegStruct(1301789264, "ALittle.UIButtonDragBeginEvent", {
name : "ALittle.UIButtonDragBeginEvent", ns_name : "ALittle", rl_name : "UIButtonDragBeginEvent", hash_code : 1301789264,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(1309977874, "ALittle.UIChangedEndEvent", {
name : "ALittle.UIChangedEndEvent", ns_name : "ALittle", rl_name : "UIChangedEndEvent", hash_code : 1309977874,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(1337289812, "ALittle.UIButtonDragEvent", {
name : "ALittle.UIButtonDragEvent", ns_name : "ALittle", rl_name : "UIButtonDragEvent", hash_code : 1337289812,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(1354499457, "ALittle.UIDropEvent", {
name : "ALittle.UIDropEvent", ns_name : "ALittle", rl_name : "UIDropEvent", hash_code : 1354499457,
name_list : ["target","drop_target"],
type_list : ["ALittle.DisplayObject","ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(1598008698, "ALittle.UIFingerDragBeginEvent", {
name : "ALittle.UIFingerDragBeginEvent", ns_name : "ALittle", rl_name : "UIFingerDragBeginEvent", hash_code : 1598008698,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y","finger_key","is_sfc"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double","string","bool"],
option_map : {}
})
ALittle.RegStruct(1800966813, "ALittle.UISystemSelectDirectoryEvent", {
name : "ALittle.UISystemSelectDirectoryEvent", ns_name : "ALittle", rl_name : "UISystemSelectDirectoryEvent", hash_code : 1800966813,
name_list : ["target","path"],
type_list : ["ALittle.DisplayObject","string"],
option_map : {}
})
ALittle.RegStruct(1816229739, "ALittle.UIAtKeyEvent", {
name : "ALittle.UIAtKeyEvent", ns_name : "ALittle", rl_name : "UIAtKeyEvent", hash_code : 1816229739,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(1848466169, "ALittle.UIDragDownEvent", {
name : "ALittle.UIDragDownEvent", ns_name : "ALittle", rl_name : "UIDragDownEvent", hash_code : 1848466169,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(1862557463, "ALittle.UIShowEvent", {
name : "ALittle.UIShowEvent", ns_name : "ALittle", rl_name : "UIShowEvent", hash_code : 1862557463,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(1883782801, "ALittle.UILButtonDownEvent", {
name : "ALittle.UILButtonDownEvent", ns_name : "ALittle", rl_name : "UILButtonDownEvent", hash_code : 1883782801,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(2024735182, "ALittle.UITabKeyEvent", {
name : "ALittle.UITabKeyEvent", ns_name : "ALittle", rl_name : "UITabKeyEvent", hash_code : 2024735182,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-2050069067, "ALittle.UIFingerDragEndEvent", {
name : "ALittle.UIFingerDragEndEvent", ns_name : "ALittle", rl_name : "UIFingerDragEndEvent", hash_code : -2050069067,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y","finger_key","is_sfc"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double","string","bool"],
option_map : {}
})
ALittle.RegStruct(-1737121315, "ALittle.UIMButtonWheelEvent", {
name : "ALittle.UIMButtonWheelEvent", ns_name : "ALittle", rl_name : "UIMButtonWheelEvent", hash_code : -1737121315,
name_list : ["target","delta_x","delta_y"],
type_list : ["ALittle.DisplayObject","double","double"],
option_map : {}
})
ALittle.RegStruct(-1676610185, "ALittle.UISystemSaveFileEvent", {
name : "ALittle.UISystemSaveFileEvent", ns_name : "ALittle", rl_name : "UISystemSaveFileEvent", hash_code : -1676610185,
name_list : ["target","path"],
type_list : ["ALittle.DisplayObject","string"],
option_map : {}
})
ALittle.RegStruct(-1604617962, "ALittle.UIKeyDownEvent", {
name : "ALittle.UIKeyDownEvent", ns_name : "ALittle", rl_name : "UIKeyDownEvent", hash_code : -1604617962,
name_list : ["target","mod","sym","scancode","custom","handled"],
type_list : ["ALittle.DisplayObject","int","int","int","bool","bool"],
option_map : {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-1347278145, "ALittle.UIButtonEvent", {
name : "ALittle.UIButtonEvent", ns_name : "ALittle", rl_name : "UIButtonEvent", hash_code : -1347278145,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(-1234078962, "ALittle.UITextInputEvent", {
name : "ALittle.UITextInputEvent", ns_name : "ALittle", rl_name : "UITextInputEvent", hash_code : -1234078962,
name_list : ["target","text","custom"],
type_list : ["ALittle.DisplayObject","string","bool"],
option_map : {}
})
ALittle.RegStruct(-1233353463, "ALittle.UIFingerDownEvent", {
name : "ALittle.UIFingerDownEvent", ns_name : "ALittle", rl_name : "UIFingerDownEvent", hash_code : -1233353463,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","finger_key","is_sfc","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","string","bool","bool"],
option_map : {}
})
ALittle.RegStruct(-1202439334, "ALittle.UIMoveOutEvent", {
name : "ALittle.UIMoveOutEvent", ns_name : "ALittle", rl_name : "UIMoveOutEvent", hash_code : -1202439334,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-1001723540, "ALittle.UIMouseMoveEvent", {
name : "ALittle.UIMouseMoveEvent", ns_name : "ALittle", rl_name : "UIMouseMoveEvent", hash_code : -1001723540,
name_list : ["target","abs_x","abs_y","rel_x","rel_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(-839083637, "ALittle.UIDragRightEvent", {
name : "ALittle.UIDragRightEvent", ns_name : "ALittle", rl_name : "UIDragRightEvent", hash_code : -839083637,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-644464135, "ALittle.UIFocusInEvent", {
name : "ALittle.UIFocusInEvent", ns_name : "ALittle", rl_name : "UIFocusInEvent", hash_code : -644464135,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-641444818, "ALittle.UIRButtonDownEvent", {
name : "ALittle.UIRButtonDownEvent", ns_name : "ALittle", rl_name : "UIRButtonDownEvent", hash_code : -641444818,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(-569321214, "ALittle.UIRButtonUpEvent", {
name : "ALittle.UIRButtonUpEvent", ns_name : "ALittle", rl_name : "UIRButtonUpEvent", hash_code : -569321214,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(-567702959, "ALittle.UIDragLeftEvent", {
name : "ALittle.UIDragLeftEvent", ns_name : "ALittle", rl_name : "UIDragLeftEvent", hash_code : -567702959,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-525850898, "ALittle.UIFingerEvent", {
name : "ALittle.UIFingerEvent", ns_name : "ALittle", rl_name : "UIFingerEvent", hash_code : -525850898,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","finger_key","is_sfc","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","string","bool","bool"],
option_map : {}
})
ALittle.RegStruct(-449066808, "ALittle.UIClickEvent", {
name : "ALittle.UIClickEvent", ns_name : "ALittle", rl_name : "UIClickEvent", hash_code : -449066808,
name_list : ["target","is_drag"],
type_list : ["ALittle.DisplayObject","bool"],
option_map : {}
})
ALittle.RegStruct(-439548260, "ALittle.UILongButtonDownEvent", {
name : "ALittle.UILongButtonDownEvent", ns_name : "ALittle", rl_name : "UILongButtonDownEvent", hash_code : -439548260,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(-431205740, "ALittle.UIResizeEvent", {
name : "ALittle.UIResizeEvent", ns_name : "ALittle", rl_name : "UIResizeEvent", hash_code : -431205740,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-338112738, "ALittle.UIDropFileEvent", {
name : "ALittle.UIDropFileEvent", ns_name : "ALittle", rl_name : "UIDropFileEvent", hash_code : -338112738,
name_list : ["target","path"],
type_list : ["ALittle.DisplayObject","string"],
option_map : {}
})
ALittle.RegStruct(-51419723, "ALittle.UIFingerDragEvent", {
name : "ALittle.UIFingerDragEvent", ns_name : "ALittle", rl_name : "UIFingerDragEvent", hash_code : -51419723,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y","finger_key","is_sfc"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double","string","bool"],
option_map : {}
})
ALittle.RegStruct(-1330840, "ALittle.UIMClickEvent", {
name : "ALittle.UIMClickEvent", ns_name : "ALittle", rl_name : "UIMClickEvent", hash_code : -1330840,
name_list : ["target","is_drag"],
type_list : ["ALittle.DisplayObject","bool"],
option_map : {}
})
ALittle.RegStruct(40651933, "ALittle.UILButtonUpEvent", {
name : "ALittle.UILButtonUpEvent", ns_name : "ALittle", rl_name : "UILButtonUpEvent", hash_code : 40651933,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(124598654, "ALittle.UISystemSelectFileEvent", {
name : "ALittle.UISystemSelectFileEvent", ns_name : "ALittle", rl_name : "UISystemSelectFileEvent", hash_code : 124598654,
name_list : ["target","path"],
type_list : ["ALittle.DisplayObject","string"],
option_map : {}
})
ALittle.RegStruct(150587926, "ALittle.UIButtonDragEndEvent", {
name : "ALittle.UIButtonDragEndEvent", ns_name : "ALittle", rl_name : "UIButtonDragEndEvent", hash_code : 150587926,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(286797479, "ALittle.UIFClickEvent", {
name : "ALittle.UIFClickEvent", ns_name : "ALittle", rl_name : "UIFClickEvent", hash_code : 286797479,
name_list : ["target","is_drag"],
type_list : ["ALittle.DisplayObject","bool"],
option_map : {}
})
ALittle.RegStruct(292776509, "ALittle.UIFocusOutEvent", {
name : "ALittle.UIFocusOutEvent", ns_name : "ALittle", rl_name : "UIFocusOutEvent", hash_code : 292776509,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(348388800, "ALittle.UIHideEvent", {
name : "ALittle.UIHideEvent", ns_name : "ALittle", rl_name : "UIHideEvent", hash_code : 348388800,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(349963892, "ALittle.UIMButtonDownEvent", {
name : "ALittle.UIMButtonDownEvent", ns_name : "ALittle", rl_name : "UIMButtonDownEvent", hash_code : 349963892,
name_list : ["target","abs_x","abs_y","rel_x","rel_y","count","is_drag"],
type_list : ["ALittle.DisplayObject","double","double","double","double","int","bool"],
option_map : {}
})
ALittle.RegStruct(444989011, "ALittle.UISelectChangedEvent", {
name : "ALittle.UISelectChangedEvent", ns_name : "ALittle", rl_name : "UISelectChangedEvent", hash_code : 444989011,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})

ALittle.UIEventDispatcher = JavaScript.Class(undefined, {
	Ctor : function() {
		this._trans_target = ALittle.CreateValueWeakMap();
		this._listeners = {};
		this._abs_disabled = false;
	},
	get event_trans_target() {
		return this._trans_target.get("event");
	},
	set event_trans_target(value) {
		let old_value = this._trans_target.get("event");
		if (old_value === value) {
			return;
		}
		this._trans_target.set("event", value);
	},
	get drag_trans_target() {
		return this._trans_target.get("drag");
	},
	set drag_trans_target(value) {
		let old_value = this._trans_target.get("drag");
		if (old_value === value) {
			return;
		}
		this._trans_target.set("drag", value);
	},
	get abs_disabled() {
		return this._abs_disabled;
	},
	set abs_disabled(value) {
		this._abs_disabled = value;
	},
	AddEventListener : function(T, object, callback) {
		let rflt = T;
		return this.AddEventListenerImpl(rflt.name, object, callback);
	},
	AddEventListenerImpl : function(event_type, object, callback) {
		if (object === undefined) {
			return false;
		}
		if (callback === undefined) {
			return false;
		}
		let callback_table = this._listeners[event_type];
		if (callback_table === undefined) {
			callback_table = ALittle.CreateKeyWeakMap();
			this._listeners[event_type] = callback_table;
		}
		let callback_value = callback_table.get(object);
		if (callback_value === undefined) {
			callback_value = new Map();
			callback_table.set(object, callback_value);
		}
		callback_value.set(callback, true);
		return true;
	},
	RemoveEventListener : function(T, object, callback) {
		let rflt = T;
		let callback_table = this._listeners[rflt.name];
		if (callback_table === undefined) {
			return;
		}
		if (callback === undefined) {
			callback_table.delete(object);
		} else {
			let callback_value = callback_table.get(object);
			if (callback_value === undefined) {
				return;
			}
			callback_value.delete(callback);
		}
	},
	ClearEventListener : function() {
		this._listeners = {};
	},
	DispatchEvent : function(T, event) {
		let rflt = T;
		if (event.target === undefined) {
			event.target = this;
		}
		let event_target = this;
		if (this._trans_target.get("event") !== undefined) {
			event_target = this._trans_target.get("event");
		} else if (this._trans_target.get("drag") !== undefined) {
			if (rflt.name === "ALittle.UIButtonDragEvent" || rflt.name === "ALittle.UIButtonDragBeginEvent") {
				event_target = this._trans_target.get("drag");
			} else if (rflt.name === "ALittle.UIButtonDragEndEvent") {
				event_target = this._trans_target.get("drag");
				A_UISystem.focus = this._trans_target.get("drag");
			}
		}
		if (event_target._abs_disabled) {
			return;
		}
		let callback_table = event_target._listeners[rflt.name];
		if (callback_table === undefined) {
			return;
		}
		for (let [object, callback_value] of callback_table) {
			if (callback_value === undefined) continue;
			for (let [func, _] of callback_value) {
				if (_ === undefined) continue;
				func.call(object, event);
			}
		}
	},
}, "ALittle.UIEventDispatcher");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


let __cos = ALittle.Math_Cos;
let __sin = ALittle.Math_Sin;
ALittle.Matrix2D = JavaScript.Class(undefined, {
	Ctor : function() {
		let m = new Map();
		m.set(0, new Map());
		m.set(1, new Map());
		m.set(2, new Map());
		this._m = m;
		this.SetIdentity();
	},
	SetIdentity : function() {
		let m = this._m;
		m.get(0).set(0, 1);
		m.get(0).set(1, 0);
		m.get(0).set(2, 0);
		m.get(1).set(0, 0);
		m.get(1).set(1, 1);
		m.get(1).set(2, 0);
		m.get(2).set(0, 0);
		m.get(2).set(1, 0);
		m.get(2).set(2, 1);
	},
	SetRotate : function(rad) {
		let m = this._m;
		m.get(0).set(0, __cos(rad));
		m.get(0).set(1, __sin(rad));
		m.get(0).set(2, 0);
		m.get(1).set(0, -m.get(0).get(1));
		m.get(1).set(1, m.get(0).get(0));
		m.get(1).set(2, 0);
		m.get(2).set(0, 0);
		m.get(2).set(1, 0);
		m.get(2).set(2, 1);
	},
	Rotate : function(rad) {
		let m = ALittle.NewObject(ALittle.Matrix2D);
		m.SetRotate(rad);
		this.Multiply(m);
	},
	SetTranslation : function(x, y) {
		let m = this._m;
		m.get(0).set(0, 1);
		m.get(0).set(1, 0);
		m.get(0).set(2, 0);
		m.get(1).set(0, 0);
		m.get(1).set(1, 1);
		m.get(1).set(2, 0);
		m.get(2).set(0, x);
		m.get(2).set(1, y);
		m.get(2).set(2, 1);
	},
	Translation : function(x, y) {
		let m = ALittle.NewObject(ALittle.Matrix2D);
		m.SetTranslation(x, y);
		this.Multiply(m);
	},
	SetScale : function(x, y) {
		let m = this._m;
		m.get(0).set(0, x);
		m.get(0).set(1, 0);
		m.get(0).set(2, 0);
		m.get(1).set(0, 0);
		m.get(1).set(1, y);
		m.get(1).set(2, 0);
		m.get(2).set(0, 0);
		m.get(2).set(1, 0);
		m.get(2).set(2, 1);
	},
	Scale : function(x, y) {
		let m = ALittle.NewObject(ALittle.Matrix2D);
		m.SetScale(x, y);
		this.Multiply(m);
	},
	Multiply : function(right) {
		let r = new Map();
		let m = this._m;
		let rm = right._m;
		r.set(0, new Map());
		r.get(0).set(0, m.get(0).get(0) * rm.get(0).get(0) + m.get(0).get(1) * rm.get(1).get(0) + m.get(0).get(2) * rm.get(2).get(0));
		r.get(0).set(1, m.get(0).get(0) * rm.get(0).get(1) + m.get(0).get(1) * rm.get(1).get(1) + m.get(0).get(2) * rm.get(2).get(1));
		r.get(0).set(2, m.get(0).get(0) * rm.get(0).get(2) + m.get(0).get(1) * rm.get(1).get(2) + m.get(0).get(2) * rm.get(2).get(2));
		r.set(1, new Map());
		r.get(1).set(0, m.get(1).get(0) * rm.get(0).get(0) + m.get(1).get(1) * rm.get(1).get(0) + m.get(1).get(2) * rm.get(2).get(0));
		r.get(1).set(1, m.get(1).get(0) * rm.get(0).get(1) + m.get(1).get(1) * rm.get(1).get(1) + m.get(1).get(2) * rm.get(2).get(1));
		r.get(1).set(2, m.get(1).get(0) * rm.get(0).get(2) + m.get(1).get(1) * rm.get(1).get(2) + m.get(1).get(2) * rm.get(2).get(2));
		r.set(2, new Map());
		r.get(2).set(0, m.get(2).get(0) * rm.get(0).get(0) + m.get(2).get(1) * rm.get(1).get(0) + m.get(2).get(2) * rm.get(2).get(0));
		r.get(2).set(1, m.get(2).get(0) * rm.get(0).get(1) + m.get(2).get(1) * rm.get(1).get(1) + m.get(2).get(2) * rm.get(2).get(1));
		r.get(2).set(2, m.get(2).get(0) * rm.get(0).get(2) + m.get(2).get(1) * rm.get(1).get(2) + m.get(2).get(2) * rm.get(2).get(2));
		this._m = r;
	},
}, "ALittle.Matrix2D");

ALittle.Vector2D = JavaScript.Class(undefined, {
	Ctor : function(xx, yy) {
		this._x = xx;
		this._y = yy;
	},
	Multiply : function(right) {
		let rm = right._m;
		let xx = this._x * rm.get(0).get(0) + this._y * rm.get(1).get(0) + 1 * rm.get(2).get(0);
		let yy = this._x * rm.get(0).get(1) + this._y * rm.get(1).get(1) + 1 * rm.get(2).get(1);
		this._x = xx;
		this._y = yy;
	},
}, "ALittle.Vector2D");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-2110455927, "ALittle.EventInfo", {
name : "ALittle.EventInfo", ns_name : "ALittle", rl_name : "EventInfo", hash_code : -2110455927,
name_list : ["type","func"],
type_list : ["string","string"],
option_map : {}
})
ALittle.RegStruct(-4982446, "ALittle.DisplayInfo", {
name : "ALittle.DisplayInfo", ns_name : "ALittle", rl_name : "DisplayInfo", hash_code : -4982446,
name_list : ["__target_class","__class_func","__base_attr","__show_attr","loop_map","__class","__include","__extends","__childs","__event","__link","__shows_included","__childs_included","__extends_included","description","text","font_path","font_size","red","green","blue","alpha","bold","italic","underline","deleteline","outline","x","y","x_type","x_value","y_type","y_value","width","height","width_type","width_value","height_type","height_value","scale_x","scale_y","center_x","center_y","angle","flip","hand_cursor","visible","disabled","left_size","right_size","top_size","bottom_size","texture_name","interval","play_loop_count","var_play","base_y","head_size","gap","up_size","down_size","cursor_red","cursor_green","cursor_blue","default_text_alpha","ims_padding","margin_left","margin_right","margin_top","margin_bottom","show_count","body_margin","screen_margin_left","screen_margin_right","screen_margin_top","screen_margin_bottom","start_degree","end_degree","line_spacing","max_line_count","font_red","font_green","font_blue","margin_halign","margin_valign","cursor_margin_up","cursor_margin_down","total_size","show_size","offset_rate","offset_step","grade","row_count","col_count","row_index","col_index","u1","v1","u2","v2","u3","v3","x1","y1","x2","y2","x3","y3","x_gap","y_gap","x_start_gap","y_start_gap","button_gap","button_start","button_margin","tab_index","view_margin","child_width_margin"],
type_list : ["List<string>","any","Map<string,any>","Map<string,ALittle.DisplayInfo>","Map<string,ALittle.LoopGroupInfo>","string","string","string","List<ALittle.DisplayInfo>","List<ALittle.EventInfo>","string","bool","bool","bool","string","string","string","int","double","double","double","double","bool","bool","bool","bool","bool","double","double","int","double","int","double","double","double","int","double","int","double","double","double","double","double","double","int","bool","bool","bool","double","double","double","double","string","int","int","bool","double","double","double","double","double","double","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","int","double","double","double","double","double","double","double","double","double","double","double","int","int","int","int","int","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double","double"],
option_map : {}
})

let __cos = ALittle.Math_Cos;
let __sin = ALittle.Math_Sin;
let __byte = ALittle.String_Byte;
let __type = ALittle.String_Type;
if (ALittle.UIEventDispatcher === undefined) throw new Error(" extends class:ALittle.UIEventDispatcher is undefined");
ALittle.DisplayObject = JavaScript.Class(ALittle.UIEventDispatcher, {
	Ctor : function(ctrl_sys) {
		this._ctrl_sys = ctrl_sys;
		this._clip = false;
		this._ignore = false;
		this._x = 0;
		this._y = 0;
		this._x_type = ALittle.UIEnumTypes.POS_ABS;
		this._x_value = 0;
		this._y_type = ALittle.UIEnumTypes.POS_ABS;
		this._y_value = 0;
		this._width = 0;
		this._height = 0;
		this._width_type = ALittle.UIEnumTypes.SIZE_ABS;
		this._width_value = 0;
		this._height_type = ALittle.UIEnumTypes.SIZE_ABS;
		this._height_value = 0;
		this._scale_x = 1;
		this._scale_y = 1;
		this._angle = 0;
		this._center_x = 0;
		this._center_y = 0;
		this._red = 1;
		this._green = 1;
		this._blue = 1;
		this._alpha = 1;
		this._abs_alpha = 1;
		this._visible = true;
		this._abs_visible = true;
		this._hand_cursor = false;
		this._disabled = false;
		this._modal = false;
		this._pickup_rect = true;
		this._pickup_child = false;
		this._pickup_this = false;
		this._can_scroll = false;
	},
	set hand_cursor(value) {
		if (this._hand_cursor === value) {
			return;
		}
		this._hand_cursor = value;
		if (value) {
			this.AddEventListener(___all_struct.get(544684311), this, this.HandleMoveInForCursor);
			this.AddEventListener(___all_struct.get(-1202439334), this, this.HandleMoveOutForCursor);
		} else {
			this.RemoveEventListener(___all_struct.get(544684311), this, this.HandleMoveInForCursor);
			this.RemoveEventListener(___all_struct.get(-1202439334), this, this.HandleMoveOutForCursor);
		}
	},
	get hand_cursor() {
		return this._hand_cursor;
	},
	HandleMoveInForCursor : function(event) {
		if (this._hand_cursor === false) {
			return;
		}
		ALittle.System_SetHandCursor();
	},
	HandleMoveOutForCursor : function(event) {
		if (this._hand_cursor === false) {
			return;
		}
		ALittle.System_SetNormalCursor();
	},
	get native_show() {
		return this._show;
	},
	get text() {
		return undefined;
	},
	set text(value) {
	},
	get group() {
		return undefined;
	},
	set group(group) {
	},
	get selected() {
		return undefined;
	},
	set selected(value) {
	},
	get font_height() {
		return undefined;
	},
	SetTextureCoord : function(t, b, l, r) {
	},
	get texture() {
		return undefined;
	},
	set texture(value) {
	},
	get texture_name() {
		return undefined;
	},
	set texture_name(value) {
	},
	Redraw : function() {
	},
	get childs() {
		return undefined;
	},
	get child_count() {
		return undefined;
	},
	SetChildIndex : function(child, index) {
		return false;
	},
	AddChild : function(child, index) {
		return false;
	},
	RemoveChild : function(child) {
		return false;
	},
	RemoveAllChild : function() {
	},
	GetChildOffset : function() {
		return [0, 0];
	},
	get editable() {
		return false;
	},
	get font_size() {
		return undefined;
	},
	get cursor_x() {
		return undefined;
	},
	get cursor_y() {
		return undefined;
	},
	get is_focus() {
		return A_UISystem.focus === this;
	},
	DelayFocus : function() {
		let loop = ALittle.NewObject(ALittle.LoopTimer, this.HandleDelayFocus.bind(this), 1);
		loop.Start();
	},
	HandleDelayFocus : function() {
		this.focus = true;
	},
	set focus(value) {
		if (value) {
			A_UISystem.focus = this;
		} else {
			if (A_UISystem.focus === this) {
				A_UISystem.focus = undefined;
			}
		}
	},
	get is_input() {
		return false;
	},
	set can_scroll(value) {
		this._can_scroll = value;
	},
	get can_scroll() {
		return this._can_scroll;
	},
	set description(value) {
		this._description = value;
	},
	get description() {
		return this._description;
	},
	set loop_map(value) {
		this._loop_map = value;
	},
	get loop_map() {
		return this._loop_map;
	},
	CreateLoopAnimation : function(name) {
		if (this._loop_map === undefined) {
			return undefined;
		}
		let info = this._loop_map[name];
		if (info === undefined) {
			return undefined;
		}
		return ALittle.NewObject(ALittle.LoopAnimation, this, info);
	},
	set modal(value) {
		this._modal = value;
	},
	get modal() {
		return this._modal;
	},
	set clip(value) {
		this._clip = value;
		this._show.SetClip(value);
	},
	get clip() {
		return this._clip;
	},
	set ignore(value) {
		this._ignore = value;
	},
	get ignore() {
		return this._ignore;
	},
	IsMouseIn : function() {
		let [abs_x, abs_y] = this.LocalToGlobal();
		let mouse_x = A_UISystem.mouse_x;
		let mouse_y = A_UISystem.mouse_y;
		if (mouse_x < abs_x) {
			return false;
		}
		if (mouse_y < abs_y) {
			return false;
		}
		if (mouse_x > abs_x + this.width * this.scale_x) {
			return false;
		}
		if (mouse_y > abs_y + this.height * this.scale_y) {
			return false;
		}
		return true;
	},
	LocalToGlobal : function(target) {
		let x = 0.0;
		let y = 0.0;
		let parent = this;
		while (parent !== undefined) {
			let scale_x = 1.0;
			let scale_y = 1.0;
			let show_parent = parent._show_parent;
			if (show_parent !== undefined) {
				scale_x = show_parent.scale_x;
				scale_y = show_parent.scale_y;
			}
			x = x + (scale_x * parent.x);
			y = y + (scale_y * parent.y);
			if (target === show_parent) {
				break;
			}
			parent = show_parent;
		}
		return [x, y];
	},
	LocalToGlobalMatrix2D : function(target) {
		let result = ALittle.NewObject(ALittle.Matrix2D);
		let list = [];
		let count = 0;
		let parent = this;
		while (parent !== undefined) {
			if (target === parent) {
				break;
			}
			++ count;
			list[count - 1] = parent;
			parent = parent._show_parent;
		}
		for (let index = count; index >= 1; index += -1) {
			let object = list[index - 1];
			let m = ALittle.NewObject(ALittle.Matrix2D);
			if (index === 1) {
				m.Scale(object.width, object.height);
			}
			m.Translation(-object.center_x, -object.center_y);
			m.Rotate(3.1415926 * object.angle / 180);
			m.Translation(object.center_x, object.center_y);
			m.Scale(object.scale_x, object.scale_y);
			m.Translation(object.x, object.y);
			m.Multiply(result);
			result = m;
		}
		return result;
	},
	GlobalToLocalMatrix2D : function(x, y, target) {
		let list = [];
		let count = 0;
		let parent = this;
		while (parent !== undefined) {
			if (target === parent) {
				break;
			}
			++ count;
			list[count - 1] = parent;
			parent = parent._show_parent;
		}
		let pick = undefined;
		for (let index = count; index >= 1; index += -1) {
			[pick, x, y] = list[index - 1].PickUpSelf(x, y);
		}
		return [x, y];
	},
	RemoveFromParent : function() {
		let parent = this._show_parent;
		if (parent === undefined) {
			parent = this._logic_parent;
		}
		if (parent === undefined) {
			return;
		}
		parent.RemoveChild(this);
	},
	IsGrandParent : function(target) {
		let parent = this;
		while (parent !== undefined) {
			parent = parent._show_parent;
			if (target === parent) {
				return true;
			}
		}
		return false;
	},
	get parent() {
		if (this._logic_parent !== undefined) {
			return this._logic_parent;
		}
		return this._show_parent;
	},
	get show_parent() {
		return this._show_parent;
	},
	get logic_parent() {
		return this._logic_parent;
	},
	MoveToTop : function() {
		if (this._show_parent !== undefined) {
			this._show_parent.SetChildIndex(this, this._show_parent.child_count);
		}
	},
	set x(value) {
		this._x = value;
		if (this._x_type === ALittle.UIEnumTypes.POS_ABS) {
			this._x_value = value;
		}
		this._show.SetX(value);
	},
	get x() {
		return this._x;
	},
	set x_type(value) {
		if (this._x_type === value) {
			return;
		}
		this._x_type = value;
		if (this._show_parent !== undefined) {
			this._show_parent.UpdateXLayout(this);
		}
	},
	set x_value(value) {
		if (this._x_value === value) {
			return;
		}
		this._x_value = value;
		if (this._show_parent !== undefined) {
			this._show_parent.UpdateXLayout(this);
		}
	},
	get x_type() {
		return this._x_type;
	},
	get x_value() {
		return this._x_value;
	},
	set y(value) {
		this._y = value;
		if (this._y_type === ALittle.UIEnumTypes.POS_ABS) {
			this._y_value = value;
		}
		this._show.SetY(value);
	},
	get y() {
		return this._y;
	},
	set y_type(value) {
		if (this._y_type === value) {
			return;
		}
		this._y_type = value;
		if (this._show_parent !== undefined) {
			this._show_parent.UpdateYLayout(this);
		}
	},
	set y_value(value) {
		if (this._y_value === value) {
			return;
		}
		this._y_value = value;
		if (this._show_parent !== undefined) {
			this._show_parent.UpdateYLayout(this);
		}
	},
	get y_type() {
		return this._y_type;
	},
	get y_value() {
		return this._y_value;
	},
	set width(value) {
		this._width = value;
		if (this._width_type === ALittle.UIEnumTypes.SIZE_ABS) {
			this._width_value = value;
		}
		this._show.SetWidth(value);
	},
	get width() {
		return this._width;
	},
	set width_type(value) {
		if (this._width_type === value) {
			return;
		}
		this._width_type = value;
		if (this._show_parent !== undefined) {
			this._show_parent.UpdateWidthLayout(this);
			if (this._x_type !== ALittle.UIEnumTypes.POS_ABS && this._x_type !== ALittle.UIEnumTypes.POS_ALIGN_STARTING && this._x_type !== ALittle.UIEnumTypes.POS_PERCENT_STARTING) {
				this._show_parent.UpdateXLayout(this);
			}
		} else if (this._width_type === ALittle.UIEnumTypes.SIZE_ABS) {
			this.width = this._width_value;
		}
	},
	set width_value(value) {
		if (this._width_value === value) {
			return;
		}
		this._width_value = value;
		if (this._show_parent !== undefined) {
			this._show_parent.UpdateWidthLayout(this);
			if (this._x_type !== ALittle.UIEnumTypes.POS_ABS && this._x_type !== ALittle.UIEnumTypes.POS_ALIGN_STARTING && this._x_type !== ALittle.UIEnumTypes.POS_PERCENT_STARTING) {
				this._show_parent.UpdateXLayout(this);
			}
		} else if (this._width_type === ALittle.UIEnumTypes.SIZE_ABS) {
			this.width = this._width_value;
		}
	},
	get width_type() {
		return this._width_type;
	},
	get width_value() {
		return this._width_value;
	},
	set height(value) {
		this._height = value;
		if (this._height_type === ALittle.UIEnumTypes.SIZE_ABS) {
			this._height_value = value;
		}
		this._show.SetHeight(value);
	},
	get height() {
		return this._height;
	},
	set height_type(value) {
		if (this._height_type === value) {
			return;
		}
		this._height_type = value;
		if (this._show_parent !== undefined) {
			this._show_parent.UpdateHeightLayout(this);
			if (this._y_type !== ALittle.UIEnumTypes.POS_ABS && this._y_type !== ALittle.UIEnumTypes.POS_ALIGN_STARTING && this._y_type !== ALittle.UIEnumTypes.POS_PERCENT_STARTING) {
				this._show_parent.UpdateYLayout(this);
			}
		} else if (this._height_type === ALittle.UIEnumTypes.SIZE_ABS) {
			this.height = this._height_value;
		}
	},
	set height_value(value) {
		if (this._height_value === value) {
			return;
		}
		this._height_value = value;
		if (this._show_parent !== undefined) {
			this._show_parent.UpdateHeightLayout(this);
			if (this._y_type !== ALittle.UIEnumTypes.POS_ABS && this._y_type !== ALittle.UIEnumTypes.POS_ALIGN_STARTING && this._y_type !== ALittle.UIEnumTypes.POS_PERCENT_STARTING) {
				this._show_parent.UpdateYLayout(this);
			}
		} else if (this._height_type === ALittle.UIEnumTypes.SIZE_ABS) {
			this.height = this._height_value;
		}
	},
	get height_type() {
		return this._height_type;
	},
	get height_value() {
		return this._height_value;
	},
	set scale_x(value) {
		this._scale_x = value;
		this._show.SetScaleX(value);
	},
	get scale_x() {
		return this._scale_x;
	},
	set scale_y(value) {
		this._scale_y = value;
		this._show.SetScaleY(value);
	},
	get scale_y() {
		return this._scale_y;
	},
	set center_x(value) {
		this._center_x = value;
		this._show.SetCenterX(value);
	},
	get center_x() {
		return this._center_x;
	},
	set center_y(value) {
		this._center_y = value;
		this._show.SetCenterY(value);
	},
	get center_y() {
		return this._center_y;
	},
	set angle(value) {
		this._angle = value;
		this._show.SetAngle(value);
	},
	get angle() {
		return this._angle;
	},
	set red(value) {
		this._red = value;
		this._show.SetRed(value);
	},
	get red() {
		return this._red;
	},
	set green(value) {
		this._green = value;
		this._show.SetGreen(value);
	},
	get green() {
		return this._green;
	},
	set blue(value) {
		this._blue = value;
		this._show.SetBlue(value);
	},
	get blue() {
		return this._blue;
	},
	set alpha(value) {
		this._alpha = value;
		this._abs_alpha = 1;
		if (this._show_parent !== undefined) {
			this._abs_alpha = this._show_parent.abs_alpha * value;
		} else {
			this._abs_alpha = value;
		}
		this._show.SetAlpha(this._abs_alpha);
	},
	get alpha() {
		return this._alpha;
	},
	get abs_alpha() {
		return this._abs_alpha;
	},
	set visible(value) {
		if (value === false && this === A_UISystem.focus) {
			A_UISystem.focus = undefined;
		}
		this._visible = value;
		if (this._show_parent !== undefined) {
			this._abs_visible = this._show_parent.abs_visible && value;
		} else {
			this._abs_visible = value;
		}
		this._show.SetVisible(this._abs_visible);
	},
	get visible() {
		return this._visible;
	},
	get abs_visible() {
		return this._abs_visible;
	},
	set disabled(value) {
		if (value === true && this === A_UISystem.focus) {
			A_UISystem.focus = undefined;
		}
		this._disabled = value;
		if (this._show_parent !== undefined) {
			this._abs_disabled = this._show_parent.abs_disabled || value;
		} else {
			this._abs_disabled = value;
		}
	},
	get disabled() {
		return this._disabled;
	},
	get abs_disabled() {
		return this._abs_disabled;
	},
	UpdateLayout : function() {
		if (this._show_parent === undefined) {
			return;
		}
		this._show_parent.UpdateWidthLayout(this);
		this._show_parent.UpdateHeightLayout(this);
		this._show_parent.UpdateXLayout(this);
		this._show_parent.UpdateYLayout(this);
	},
	PickUp : function(x, y) {
		if (this._ignore || this._abs_disabled || this._abs_visible === false) {
			return [undefined, undefined, undefined];
		}
		let rel_x = x - this._x;
		let rel_y = y - this._y;
		let xx = rel_x - this._center_x;
		let yy = rel_y - this._center_y;
		if (this._angle !== 0) {
			let rad = 3.1415926 * -this._angle / 180.0;
			let cos = __cos(rad);
			let sin = __sin(rad);
			let xxx = xx * cos + yy * -sin;
			let yyy = xx * sin + yy * cos;
			xx = xxx;
			yy = yyy;
		}
		if (this._scale_x > 0) {
			xx = xx / (this._scale_x);
		}
		if (this._scale_y > 0) {
			yy = yy / (this._scale_y);
		}
		rel_x = xx + this._center_x;
		rel_y = yy + this._center_y;
		if (this._scale_x <= 0 || this._scale_y <= 0) {
			if (this._modal) {
				return [this, rel_x, rel_y];
			}
			return [undefined, rel_x, rel_y];
		}
		if (this._modal) {
			return [this, rel_x, rel_y];
		}
		if (this._pickup_rect && rel_x >= 0 && rel_y >= 0 && rel_x < this._width && rel_y < this._height) {
			return [this, rel_x, rel_y];
		} else {
			return [undefined, rel_x, rel_y];
		}
	},
	PickUpSelf : function(x, y) {
		let rel_x = x - this._x;
		let rel_y = y - this._y;
		let xx = rel_x - this._center_x;
		let yy = rel_y - this._center_y;
		if (this._angle !== 0) {
			let rad = 3.1415926 * -this._angle / 180.0;
			let cos = __cos(rad);
			let sin = __sin(rad);
			let xxx = xx * cos + yy * -sin;
			let yyy = xx * sin + yy * cos;
			xx = xxx;
			yy = yyy;
		}
		if (this._scale_x > 0) {
			xx = xx / (this._scale_x);
		}
		if (this._scale_y > 0) {
			yy = yy / (this._scale_y);
		}
		rel_x = xx + this._center_x;
		rel_y = yy + this._center_y;
		if (this._scale_x <= 0 || this._scale_y <= 0) {
			return [undefined, rel_x, rel_y];
		}
		if (this._abs_visible && rel_x >= 0 && rel_y >= 0 && rel_x < this.width && rel_y < this.height) {
			return [this, rel_x, rel_y];
		}
		return [undefined, rel_x, rel_y];
	},
	ClipRect : function(x, y, width, height, h_move, v_move) {
	},
	DeepLayout : function() {
	},
	DeserializeSetter : function(info) {
		let base_attr = info.__base_attr;
		if (base_attr === undefined) {
			base_attr = {};
			let ___OBJECT_1 = info;
			for (let key in ___OBJECT_1) {
				let value = ___OBJECT_1[key];
				if (value === undefined) continue;
				if (__byte(key, 1) !== 95 && (__type(value) !== "table" || value.__class === undefined)) {
					base_attr[key] = value;
				}
			}
			info.__base_attr = base_attr;
		}
		let ___OBJECT_2 = base_attr;
		for (let key in ___OBJECT_2) {
			let value = ___OBJECT_2[key];
			if (value === undefined) continue;
			this[key] = value;
		}
	},
	DeserializeShowChild : function(info, target_logic) {
		if (info.__target_class !== undefined && this._ctrl_sys._use_plugin_class) {
			target_logic = this;
		}
		let show_attr = info.__show_attr;
		if (show_attr === undefined) {
			show_attr = {};
			let ___OBJECT_3 = info;
			for (let key in ___OBJECT_3) {
				let value = ___OBJECT_3[key];
				if (value === undefined) continue;
				if (__byte(key, 1) !== 95 && __type(value) === "table" && value.__class !== undefined) {
					show_attr[key] = value;
				}
			}
			info.__show_attr = show_attr;
		}
		let ___OBJECT_4 = show_attr;
		for (let key in ___OBJECT_4) {
			let value = ___OBJECT_4[key];
			if (value === undefined) continue;
			let object = this._ctrl_sys.CreateControlObject(value);
			if (object !== undefined) {
				object.DeserializeSetter(value);
				this[key] = object;
				object.DeserializeShowChild(value, target_logic);
				if (target_logic !== undefined) {
					object.DeserializeLinkEvent(value, target_logic);
				}
				if (value.__target_class !== undefined && this._ctrl_sys._use_plugin_class) {
					let tctor = object["TCtor"];
					if (tctor !== undefined) {
						tctor.call(object);
					}
				}
			}
		}
		let childs = info.__childs;
		if (childs !== undefined) {
			let ___OBJECT_5 = childs;
			for (let index = 1; index <= ___OBJECT_5.length; ++index) {
				let value = ___OBJECT_5[index - 1];
				if (value === undefined) break;
				let object = this._ctrl_sys.CreateControlObject(value);
				if (object !== undefined) {
					object.Deserialize(value, target_logic, this);
				}
			}
		}
	},
	DeserializeLinkEvent : function(info, target_logic) {
		let event_list = info.__event;
		if (event_list !== undefined) {
			let ___OBJECT_6 = event_list;
			for (let index = 1; index <= ___OBJECT_6.length; ++index) {
				let einfo = ___OBJECT_6[index - 1];
				if (einfo === undefined) break;
				let func = undefined;
				if (einfo.func !== undefined) {
					func = target_logic[einfo.func];
					if (func === undefined && this._ctrl_sys.log_error) {
						ALittle.Log("can't find event func:\"" + einfo.func + "\" in " + ALittle.String_ToString(target_logic));
					}
				}
				if (einfo.type !== undefined && func !== undefined) {
					this.AddEventListenerImpl(einfo.type, target_logic, func);
				}
			}
		}
		if (info.__link !== undefined) {
			target_logic[info.__link] = this;
		}
	},
	Deserialize : function(info, target_logic, parent) {
		this.DeserializeSetter(info);
		if (this._pickup_rect) {
			if (parent !== undefined) {
				parent.AddChild(this);
			}
			this.DeserializeShowChild(info, target_logic);
			if (target_logic !== undefined) {
				this.DeserializeLinkEvent(info, target_logic);
			}
		} else {
			this.DeserializeShowChild(info, target_logic);
			if (target_logic !== undefined) {
				this.DeserializeLinkEvent(info, target_logic);
			}
			if (parent !== undefined) {
				parent.AddChild(this);
			}
		}
		if (info.__target_class !== undefined && this._ctrl_sys._use_plugin_class) {
			let tctor = this["TCtor"];
			if (tctor !== undefined) {
				tctor.call(this);
			}
		}
	},
}, "ALittle.DisplayObject");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


let __remove = ALittle.List_Remove;
let __insert = ALittle.List_Insert;
let __cos = ALittle.Math_Cos;
let __sin = ALittle.Math_Sin;
if (ALittle.DisplayObject === undefined) throw new Error(" extends class:ALittle.DisplayObject is undefined");
ALittle.DisplayGroup = JavaScript.Class(ALittle.DisplayObject, {
	Ctor : function(ctrl_sys) {
		this._childs = [];
		this._child_count = 0;
		this._show = ALittle.NewObject(JavaScript.JDisplayObjects);
		this._pickup_rect = false;
		this._pickup_child = true;
		this._pickup_this = false;
	},
	GetChildIndex : function(child) {
		if (child === undefined) {
			return 0;
		}
		if (child._show_parent !== this && child._logic_parent !== this) {
			return 0;
		}
		let ___OBJECT_1 = this._childs;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let value = ___OBJECT_1[index - 1];
			if (value === undefined) break;
			if (value === child) {
				return index;
			}
		}
		return 0;
	},
	SetChildIndex : function(child, index) {
		let cur_index = this.GetChildIndex(child);
		if (cur_index === 0) {
			return false;
		}
		if (cur_index === index) {
			return true;
		}
		if (index < 1) {
			index = 1;
		}
		if (index > this._child_count) {
			index = this._child_count;
		}
		__remove(this._childs, cur_index);
		this._show.RemoveChild(child._show);
		let back_child = this._childs[index - 1];
		if (back_child !== undefined) {
			this._show.AddChildBefore(back_child._show, child._show);
		} else {
			this._show.AddChild(child._show);
		}
		__insert(this._childs, index, child);
		return true;
	},
	GetChildByIndex : function(index) {
		return this._childs[index - 1];
	},
	get childs() {
		return this._childs;
	},
	get child_count() {
		return this._child_count;
	},
	AddChild : function(child, index) {
		if (child === undefined || child === this) {
			return false;
		}
		if (child._show_parent === this || child._logic_parent === this) {
			return true;
		}
		if (child._logic_parent !== undefined) {
			child._logic_parent.RemoveChild(child);
		} else if (child._show_parent !== undefined) {
			child._show_parent.RemoveChild(child);
		}
		child._show_parent = this;
		child._logic_parent = undefined;
		if (index === undefined || index > this._child_count || this._child_count < 1) {
			++ this._child_count;
			this._childs[this._child_count - 1] = child;
			this._show.AddChild(child._show);
		} else {
			if (index < 1) {
				index = 1;
			}
			let back_child = this._childs[index - 1];
			this._show.AddChildBefore(back_child._show, child._show);
			__insert(this._childs, index, child);
			++ this._child_count;
		}
		child.visible = child._visible;
		child.alpha = child._alpha;
		child.disabled = child._disabled;
		child.UpdateLayout();
		return true;
	},
	RemoveChild : function(child) {
		if (child === undefined) {
			return false;
		}
		if (child._show_parent !== this && child._logic_parent !== this) {
			return false;
		}
		let ___OBJECT_2 = this._childs;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let value = ___OBJECT_2[index - 1];
			if (value === undefined) break;
			if (value === child) {
				__remove(this._childs, index);
				this._show.RemoveChild(child._show);
				child._show_parent = undefined;
				child._logic_parent = undefined;
				-- this._child_count;
				return true;
			}
		}
		return false;
	},
	HasChild : function(child) {
		if (child === undefined) {
			return false;
		}
		return child._show_parent === this || child._logic_parent === this;
	},
	get parent() {
		if (this._logic_parent !== undefined) {
			return this._logic_parent;
		}
		return this._show_parent;
	},
	RemoveAllChild : function() {
		let ___OBJECT_3 = this._childs;
		for (let index = 1; index <= ___OBJECT_3.length; ++index) {
			let value = ___OBJECT_3[index - 1];
			if (value === undefined) break;
			value._show_parent = undefined;
			value._logic_parent = undefined;
		}
		this._show.RemoveAllChild();
		this._childs = [];
		this._child_count = 0;
	},
	set alpha(value) {
		this._alpha = value;
		if (this._show_parent !== undefined) {
			this._abs_alpha = this._show_parent._abs_alpha * value;
		} else {
			this._abs_alpha = value;
		}
		let ___OBJECT_4 = this._childs;
		for (let index = 1; index <= ___OBJECT_4.length; ++index) {
			let value = ___OBJECT_4[index - 1];
			if (value === undefined) break;
			value.alpha = value.alpha;
		}
	},
	set visible(value) {
		this._visible = value;
		if (this._show_parent !== undefined) {
			this._abs_visible = this._show_parent._abs_visible && value;
		} else {
			this._abs_visible = value;
		}
		this._show.SetVisible(this._abs_visible);
		let ___OBJECT_5 = this._childs;
		for (let index = 1; index <= ___OBJECT_5.length; ++index) {
			let value = ___OBJECT_5[index - 1];
			if (value === undefined) break;
			value.visible = value.visible;
		}
	},
	set disabled(value) {
		this._disabled = value;
		if (this._show_parent !== undefined) {
			this._abs_disabled = this._show_parent._abs_disabled || value;
		} else {
			this._abs_disabled = value;
		}
		let ___OBJECT_6 = this._childs;
		for (let index = 1; index <= ___OBJECT_6.length; ++index) {
			let value = ___OBJECT_6[index - 1];
			if (value === undefined) break;
			value.disabled = value.disabled;
		}
	},
	PickUp : function(x, y) {
		if (this._ignore || this._abs_disabled || this._abs_visible === false) {
			return [undefined, undefined, undefined];
		}
		let rel_x = x - this._x;
		let rel_y = y - this._y;
		let xx = rel_x - this._center_x;
		let yy = rel_y - this._center_y;
		if (this._angle !== 0) {
			let rad = 3.1415926 * -this._angle / 180.0;
			let cos = __cos(rad);
			let sin = __sin(rad);
			let xxx = xx * cos + yy * -sin;
			let yyy = xx * sin + yy * cos;
			xx = xxx;
			yy = yyy;
		}
		if (this._scale_x > 0) {
			xx = xx / (this._scale_x);
		}
		if (this._scale_y > 0) {
			yy = yy / (this._scale_y);
		}
		rel_x = xx + this._center_x;
		rel_y = yy + this._center_y;
		if (this._scale_x <= 0 || this._scale_y <= 0) {
			if (this._modal) {
				return [this, rel_x, rel_y];
			}
			return [undefined, rel_x, rel_y];
		}
		if (this._pickup_rect && (rel_x < 0 || rel_y < 0 || rel_x >= this._width || rel_y >= this._height)) {
			if (this._modal) {
				return [this, rel_x, rel_y];
			}
			return [undefined, rel_x, rel_y];
		}
		if (this._pickup_child) {
			let childs = this._childs;
			for (let index = this._child_count; index >= 1; index += -1) {
				let [v_focus, v_x, v_y] = childs[index - 1].PickUp(rel_x, rel_y);
				if (v_focus !== undefined) {
					return [v_focus, v_x, v_y];
				}
			}
		}
		if (this._modal || (this._pickup_rect && this._pickup_child === false) || this._pickup_this) {
			return [this, rel_x, rel_y];
		}
		return [undefined, undefined, undefined];
	},
	set width(value) {
		this._show.SetWidth(value);
	},
	set height(value) {
		this._show.SetHeight(value);
	},
	get width() {
		if (this._pickup_rect) {
			return this._width;
		}
		return this.bound_width;
	},
	get height() {
		if (this._pickup_rect) {
			return this._height;
		}
		return this.bound_height;
	},
	get bound_width() {
		let min_x = undefined;
		let max_x = undefined;
		let ___OBJECT_7 = this._childs;
		for (let index = 1; index <= ___OBJECT_7.length; ++index) {
			let value = ___OBJECT_7[index - 1];
			if (value === undefined) break;
			if (min_x === undefined || min_x > value._x) {
				min_x = value._x;
			}
			let width = value.width;
			let right = width + value._x;
			if (max_x === undefined || max_x < right) {
				max_x = right;
			}
		}
		if (max_x === undefined) {
			max_x = 0;
		}
		if (min_x === undefined) {
			min_x = 0;
		}
		let real_width = max_x - min_x;
		if (real_width < 0) {
			real_width = 0;
		}
		return real_width;
	},
	get bound_height() {
		let min_y = undefined;
		let max_y = undefined;
		let ___OBJECT_8 = this._childs;
		for (let index = 1; index <= ___OBJECT_8.length; ++index) {
			let value = ___OBJECT_8[index - 1];
			if (value === undefined) break;
			if (min_y === undefined || min_y > value._y) {
				min_y = value._y;
			}
			let height = value.height;
			let bottom = height + value._y;
			if (max_y === undefined || max_y < bottom) {
				max_y = bottom;
			}
		}
		if (max_y === undefined) {
			max_y = 0;
		}
		if (min_y === undefined) {
			min_y = 0;
		}
		let real_height = max_y - min_y;
		if (real_height < 0) {
			real_height = 0;
		}
		return real_height;
	},
	get max_right() {
		let max_x = undefined;
		let ___OBJECT_9 = this._childs;
		for (let index = 1; index <= ___OBJECT_9.length; ++index) {
			let value = ___OBJECT_9[index - 1];
			if (value === undefined) break;
			let width = value.width;
			let right = width + value.x;
			if (max_x === undefined || max_x < right) {
				max_x = right;
			}
		}
		if (max_x === undefined) {
			max_x = 0;
		}
		return max_x;
	},
	get max_bottom() {
		let max_y = undefined;
		let ___OBJECT_10 = this._childs;
		for (let index = 1; index <= ___OBJECT_10.length; ++index) {
			let value = ___OBJECT_10[index - 1];
			if (value === undefined) break;
			let height = value.height;
			let bottom = height + value.y;
			if (max_y === undefined || max_y < bottom) {
				max_y = bottom;
			}
		}
		if (max_y === undefined) {
			max_y = 0;
		}
		return max_y;
	},
	UpdateXLayout : function(child) {
	},
	UpdateYLayout : function(child) {
	},
	UpdateWidthLayout : function(child) {
	},
	UpdateHeightLayout : function(child) {
	},
}, "ALittle.DisplayGroup");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.DisplayGroup === undefined) throw new Error(" extends class:ALittle.DisplayGroup is undefined");
ALittle.DisplayLayout = JavaScript.Class(ALittle.DisplayGroup, {
	Ctor : function(ctrl_sys) {
		this._pickup_rect = true;
		this._pickup_child = true;
	},
	set width(value) {
		if (value === this._width) {
			return;
		}
		this._width = value;
		if (this._width_type === ALittle.UIEnumTypes.SIZE_ABS) {
			this._width_value = this._width;
		}
		let ___OBJECT_1 = this._childs;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let value = ___OBJECT_1[index - 1];
			if (value === undefined) break;
			this.UpdateWidthLayout(value);
			this.UpdateXLayout(value);
		}
		this._show.SetWidth(value);
	},
	set height(value) {
		if (value === this._height) {
			return;
		}
		this._height = value;
		if (this._height_type === ALittle.UIEnumTypes.SIZE_ABS) {
			this._height_value = this._height;
		}
		let ___OBJECT_2 = this._childs;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let value = ___OBJECT_2[index - 1];
			if (value === undefined) break;
			this.UpdateHeightLayout(value);
			this.UpdateYLayout(value);
		}
		this._show.SetHeight(value);
	},
	UpdateXLayout : function(child) {
		if (child === undefined || child._show_parent !== this) {
			return;
		}
		if (child._x_type === ALittle.UIEnumTypes.POS_ABS) {
			child.x = child._x_value;
		} else if (child._x_type === ALittle.UIEnumTypes.POS_ALIGN_STARTING) {
			child.x = child._x_value;
		} else if (child._x_type === ALittle.UIEnumTypes.POS_ALIGN_CENTER) {
			child.x = (this._width - child.width) / 2 + child._x_value;
		} else if (child._x_type === ALittle.UIEnumTypes.POS_ALIGN_ENDING) {
			child.x = this._width - child.width - child._x_value;
		} else if (child._x_type === ALittle.UIEnumTypes.POS_PERCENT_STARTING) {
			child.x = this._width * child._x_value;
		} else if (child._x_type === ALittle.UIEnumTypes.POS_PERCENT_CENTER) {
			child.x = (this._width - child.width) / 2 + this._width * child._x_value;
		} else if (child._x_type === ALittle.UIEnumTypes.POS_PERCENT_ENDING) {
			child.x = (this._width - child.width) * (1 - child._x_value);
		}
	},
	UpdateYLayout : function(child) {
		if (child === undefined || child._show_parent !== this) {
			return;
		}
		if (child._y_type === ALittle.UIEnumTypes.POS_ABS) {
			child.y = child._y_value;
		} else if (child._y_type === ALittle.UIEnumTypes.POS_ALIGN_STARTING) {
			child.y = child._y_value;
		} else if (child._y_type === ALittle.UIEnumTypes.POS_ALIGN_CENTER) {
			child.y = (this._height - child.height) / 2 + child._y_value;
		} else if (child._y_type === ALittle.UIEnumTypes.POS_ALIGN_ENDING) {
			child.y = this._height - child.height - child._y_value;
		} else if (child._y_type === ALittle.UIEnumTypes.POS_PERCENT_STARTING) {
			child.y = this._height * child._y_value;
		} else if (child._y_type === ALittle.UIEnumTypes.POS_PERCENT_CENTER) {
			child.y = (this._height - child.height) / 2 + this._height * child._y_value;
		} else if (child._y_type === ALittle.UIEnumTypes.POS_PERCENT_ENDING) {
			child.y = (this._height - child.height) * (1 - child._y_value);
		}
	},
	UpdateWidthLayout : function(child) {
		if (child === undefined || child._show_parent !== this) {
			return;
		}
		if (child._width_type === ALittle.UIEnumTypes.SIZE_PERCENT) {
			let real_width = this._width * child._width_value;
			if (real_width < 0) {
				real_width = 0;
			}
			child.width = real_width;
		} else if (child._width_type === ALittle.UIEnumTypes.SIZE_MARGIN) {
			let real_width = this._width - child._width_value;
			if (real_width < 0) {
				real_width = 0;
			}
			child.width = real_width;
		} else if (child._width_type === ALittle.UIEnumTypes.SIZE_ABS) {
			let real_width = child._width_value;
			if (real_width < 0) {
				real_width = 0;
			}
			child.width = real_width;
		}
	},
	UpdateHeightLayout : function(child) {
		if (child === undefined || child._show_parent !== this) {
			return;
		}
		if (child._height_type === ALittle.UIEnumTypes.SIZE_PERCENT) {
			let real_height = this._height * child._height_value;
			if (real_height < 0) {
				real_height = 0;
			}
			child.height = real_height;
		} else if (child._height_type === ALittle.UIEnumTypes.SIZE_MARGIN) {
			let real_height = this._height - child._height_value;
			if (real_height < 0) {
				real_height = 0;
			}
			child.height = real_height;
		} else if (child._height_type === ALittle.UIEnumTypes.SIZE_ABS) {
			let real_height = child._height_value;
			if (real_height < 0) {
				real_height = 0;
			}
			child.height = real_height;
		}
	},
	get max_right() {
		return this._width;
	},
	get max_bottom() {
		return this._height;
	},
}, "ALittle.DisplayLayout");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.DisplayView = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._show = ALittle.NewObject(JavaScript.JDisplayView);
		this._pickup_rect = true;
		this._pickup_child = true;
	},
}, "ALittle.DisplayView");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.DisplayObject === undefined) throw new Error(" extends class:ALittle.DisplayObject is undefined");
ALittle.Quad = JavaScript.Class(ALittle.DisplayObject, {
	Ctor : function(ctrl_sys) {
		this._show = ALittle.NewObject(JavaScript.JQuad);
		this.AddEventListener(___all_struct.get(40651933), this, this.HandleLButtonUp);
		this.AddEventListener(___all_struct.get(683647260), this, this.HandleMButtonUp);
		this.AddEventListener(___all_struct.get(734860930), this, this.HandleFLButtonUp);
	},
	HandleLButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let c_event = {};
			c_event.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(-449066808), c_event);
		}
	},
	HandleMButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let c_event = {};
			c_event.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(-1330840), c_event);
		}
	},
	HandleFLButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let c_event = {};
			c_event.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(286797479), c_event);
		}
	},
}, "ALittle.Quad");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.DisplayObject === undefined) throw new Error(" extends class:ALittle.DisplayObject is undefined");
ALittle.Image = JavaScript.Class(ALittle.DisplayObject, {
	Ctor : function(ctrl_sys) {
		this._show = ALittle.NewObject(JavaScript.JImage);
		this._texture_width = 0;
		this._texture_height = 0;
		this._tex_coord_t = 0;
		this._tex_coord_b = 1;
		this._tex_coord_l = 0;
		this._tex_coord_r = 1;
		this._flip = 0;
		this.AddEventListener(___all_struct.get(40651933), this, this.HandleLButtonUp);
		this.AddEventListener(___all_struct.get(683647260), this, this.HandleMButtonUp);
		this.AddEventListener(___all_struct.get(734860930), this, this.HandleFLButtonUp);
	},
	HandleLButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let c_event = {};
			c_event.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(-449066808), c_event);
		}
	},
	HandleMButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let c_event = {};
			c_event.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(-1330840), c_event);
		}
	},
	HandleFLButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let c_event = {};
			c_event.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(286797479), c_event);
		}
	},
	Redraw : function() {
		this._show.ClearTexture();
		if (this._texture !== undefined) {
			this._texture.Clear();
			this._texture = undefined;
		}
		if (this._texture_name === undefined) {
			return;
		}
		if (this._texture_cut !== undefined) {
			A_LoadTextureManager.SetTextureCut(this, this._texture_name, this._texture_cut.max_width, this._texture_cut.max_height, this._texture_cut.cache);
		} else {
			this._ctrl_sys.SetTexture(this, this._texture_name);
		}
	},
	CopyTextureRef : function(image) {
		if (image === undefined || image._texture === undefined) {
			return;
		}
		this._texture_name = image._texture_name;
		this._texture_cut = undefined;
		if (image._texture_cut !== undefined) {
			this._texture_cut = {};
			this._texture_cut.max_width = image._texture_cut.max_width;
			this._texture_cut.max_height = image._texture_cut.max_height;
			this._texture_cut.cache = image._texture_cut.cache;
		}
		this._texture = image._texture;
		this._show.SetTexture(image._texture.GetTexture());
		this.SetTextureCoord(image._tex_coord_t, image._tex_coord_b, image._tex_coord_l, image._tex_coord_r);
		this._texture_width = image._texture_width;
		this._texture_height = image._texture_height;
	},
	set texture_name(value) {
		if (this._texture_name === value) {
			return;
		}
		if (this._texture_name !== undefined) {
			this._show.ClearTexture();
			this._texture = undefined;
		}
		this._texture_name = value;
		if (this._texture_name !== undefined) {
			this._texture_cut = undefined;
			this._ctrl_sys.SetTexture(this, value);
		}
	},
	SetTextureCut : function(texture_name, max_width, max_height, cache, callback) {
		if (this._texture_name !== undefined) {
			this._show.ClearTexture();
			this._texture = undefined;
		}
		this._texture_name = texture_name;
		if (this._texture_name !== undefined) {
			this._texture_cut = {};
			if (max_width === undefined) {
				max_width = 0;
			}
			this._texture_cut.max_width = max_width;
			if (max_height === undefined) {
				max_height = 0;
			}
			this._texture_cut.max_height = max_height;
			this._texture_cut.cache = cache;
			A_LoadTextureManager.SetTextureCut(this, texture_name, max_width, max_height, cache, callback);
		}
	},
	set texture_cut(param) {
		this.SetTextureCut(param.texture_name, param.max_width, param.max_height, param.cache);
	},
	get texture_cut() {
		if (this._texture_cut === undefined) {
			return undefined;
		}
		let texture_cut = {};
		texture_cut.max_width = this._texture_cut.max_width;
		texture_cut.max_height = this._texture_cut.max_height;
		texture_cut.texture_name = this._texture_name;
		return texture_cut;
	},
	get texture_name() {
		return this._texture_name;
	},
	set texture(value) {
		this._show.SetTexture(value.GetTexture());
		this._texture_width = value.GetWidth();
		this._texture_height = value.GetHeight();
		this._texture = value;
	},
	get texture() {
		return this._texture;
	},
	SetTextureCoord : function(t, b, l, r) {
		this._tex_coord_t = t;
		this._tex_coord_b = b;
		this._tex_coord_l = l;
		this._tex_coord_r = r;
		this._show.SetTextureCoord(t, b, l, r);
	},
	get texture_width() {
		return this._texture_width;
	},
	get texture_height() {
		return this._texture_height;
	},
	get flip() {
		return this._flip;
	},
	set flip(value) {
		this._flip = value;
		this._show.SetFlip(value);
	},
}, "ALittle.Image");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.DisplayObject === undefined) throw new Error(" extends class:ALittle.DisplayObject is undefined");
ALittle.Sprite = JavaScript.Class(ALittle.DisplayObject, {
	Ctor : function(ctrl_sys) {
		this._show = ALittle.NewObject(JavaScript.JSprite);
		this._texture_width = 0;
		this._texture_height = 0;
		this._tex_coord_t = 0;
		this._tex_coord_b = 1;
		this._tex_coord_l = 0;
		this._tex_coord_r = 1;
		this._row_count = 1;
		this._col_count = 1;
		this._row_index = 1;
		this._col_index = 1;
		this._flip = 0;
		this.AddEventListener(___all_struct.get(40651933), this, this.HandleLButtonUp);
		this.AddEventListener(___all_struct.get(683647260), this, this.HandleMButtonUp);
		this.AddEventListener(___all_struct.get(734860930), this, this.HandleFLButtonUp);
	},
	HandleLButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let c_event = {};
			c_event.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(-449066808), c_event);
		}
	},
	HandleMButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let c_event = {};
			c_event.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(-1330840), c_event);
		}
	},
	HandleFLButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let c_event = {};
			c_event.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(286797479), c_event);
		}
	},
	Redraw : function() {
		this._show.ClearTexture();
		if (this._texture !== undefined) {
			this._texture.Clear();
			this._texture = undefined;
		}
		if (this._texture_name === undefined) {
			return;
		}
		if (this._texture_cut !== undefined) {
			A_LoadTextureManager.SetTextureCut(this, this._texture_name, 0, 0, this._texture_cut.cache);
		} else {
			this._ctrl_sys.SetTexture(this, this._texture_name);
		}
	},
	CopyTextureRef : function(sprite) {
		if (sprite === undefined || sprite._texture === undefined) {
			return;
		}
		this._texture_name = sprite._texture_name;
		this._texture_cut = undefined;
		if (sprite._texture_cut !== undefined) {
			this._texture_cut = {};
			this._texture_cut.max_width = sprite._texture_cut.max_width;
			this._texture_cut.max_height = sprite._texture_cut.max_height;
			this._texture_cut.cache = sprite._texture_cut.cache;
		}
		this._texture = sprite._texture;
		this._show.SetTexture(sprite._texture.GetTexture());
		this.SetTextureCoord(sprite._tex_coord_t, sprite._tex_coord_b, sprite._tex_coord_l, sprite._tex_coord_r);
		this._texture_width = sprite._texture_width;
		this._texture_height = sprite._texture_height;
		this.row_count = sprite.row_count;
		this.col_count = sprite.col_count;
		this.row_index = sprite.row_index;
		this.col_index = sprite.col_index;
	},
	set texture_name(value) {
		if (this._texture_name === value) {
			return;
		}
		if (this._texture_name !== undefined) {
			this._show.ClearTexture();
			this._texture = undefined;
		}
		this._texture_name = value;
		if (this._texture_name !== undefined) {
			this._texture_cut = undefined;
			this._ctrl_sys.SetTexture(this, value);
		}
	},
	SetTextureCut : function(texture_name, cache, index) {
		if (this._texture_name !== undefined) {
			this._show.ClearTexture();
			this._texture = undefined;
		}
		this._texture_name = texture_name;
		if (this._texture_name !== undefined) {
			this._texture_cut = {};
			this._texture_cut.cache = cache;
			A_LoadTextureManager.SetTextureCut(this, texture_name, 0, 0, cache);
		}
	},
	get texture_name() {
		return this._texture_name;
	},
	set texture(value) {
		this._show.SetTexture(value.GetTexture());
		this._texture_width = value.GetWidth();
		this._texture_height = value.GetHeight();
		this._texture = value;
	},
	get texture() {
		return this._texture;
	},
	SetTextureCoord : function(t, b, l, r) {
		this._tex_coord_t = t;
		this._tex_coord_b = b;
		this._tex_coord_l = l;
		this._tex_coord_r = r;
		this._show.SetTextureCoord(t, b, l, r);
	},
	get texture_width() {
		return this._texture_width;
	},
	get texture_height() {
		return this._texture_height;
	},
	set row_count(value) {
		this._row_count = value;
		this._show.SetRowColCount(this._row_count, this._col_count);
	},
	get row_count() {
		return this._row_count;
	},
	set col_count(value) {
		this._col_count = value;
		this._show.SetRowColCount(this._row_count, this._col_count);
	},
	get col_count() {
		return this._col_count;
	},
	set row_index(value) {
		this._row_index = value;
		this._show.SetRowColIndex(this._row_index, this._col_index);
	},
	get row_index() {
		return this._row_index;
	},
	set col_index(value) {
		this._col_index = value;
		this._show.SetRowColIndex(this._row_index, this._col_index);
	},
	get col_index() {
		return this._col_index;
	},
	SetRowCol : function(row, col) {
		this._row_index = row;
		this._col_index = col;
		this._show.SetRowColIndex(this._row_index, this._col_index);
	},
	get flip() {
		return this._flip;
	},
	set flip(value) {
		this._flip = value;
		this._show.SetFlip(value);
	},
}, "ALittle.Sprite");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


let __tostring = ALittle.String_ToString;
let __byte = ALittle.String_Byte;
let __type = ALittle.String_Type;
if (ALittle.DisplayObject === undefined) throw new Error(" extends class:ALittle.DisplayObject is undefined");
ALittle.Text = JavaScript.Class(ALittle.DisplayObject, {
	Ctor : function(ctrl_sys) {
		this._text = "";
		this._bold = false;
		this._italic = false;
		this._underline = false;
		this._deleteline = false;
		this._outline = false;
		this._flip = 0;
		this._show = ALittle.NewObject(JavaScript.JText);
	},
	Redraw : function() {
		this._show.NeedDraw();
	},
	set font_path(value) {
		this._font_path = value;
		if (this._font_path === undefined || this._font_size === undefined) {
			return;
		}
		this._ctrl_sys.SetFont(this, this._font_path, this._font_size);
		this.RejuseSize();
	},
	set font_size(value) {
		this._font_size = value;
		if (this._font_path === undefined || this._font_size === undefined) {
			return;
		}
		this._ctrl_sys.SetFont(this, this._font_path, this._font_size);
		this.RejuseSize();
	},
	get font_path() {
		return this._font_path;
	},
	get font_size() {
		return this._font_size;
	},
	set text(value) {
		if (value === undefined) {
			return;
		}
		value = __tostring(value);
		if (this._text === value) {
			return;
		}
		this._text = value;
		this._show.SetText(value);
		this.RejuseSize();
	},
	get text() {
		return this._text;
	},
	set bold(value) {
		if (this._bold === value) {
			return;
		}
		this._bold = value;
		this._show.SetBold(value);
		this.RejuseSize();
	},
	get bold() {
		return this._bold;
	},
	set italic(value) {
		if (this._italic === value) {
			return;
		}
		this._italic = value;
		this._show.SetItalic(value);
		this.RejuseSize();
	},
	get italic() {
		return this._italic;
	},
	set underline(value) {
		if (this._underline === value) {
			return;
		}
		this._underline = value;
		this._show.SetUnderline(value);
		this.RejuseSize();
	},
	get underline() {
		return this._underline;
	},
	set deleteline(value) {
		if (this._deleteline === value) {
			return;
		}
		this._deleteline = value;
		this._show.SetDeleteline(value);
		this.RejuseSize();
	},
	get deleteline() {
		return this._deleteline;
	},
	set outline(value) {
		if (this._outline === value) {
			return;
		}
		this._outline = value;
		this._show.SetOutline(value);
		this.RejuseSize();
	},
	get outline() {
		return this._outline;
	},
	RejuseSize : function() {
		if (this._font_path === undefined || this._font_size === undefined) {
			return;
		}
		this.width = this._show.GetRealWidth();
		this.height = this._show.GetRealHeight();
		this.UpdateLayout();
	},
	set rejust_size(value) {
		if (value !== true) {
			return;
		}
		this.RejuseSize();
	},
	DeserializeSetter : function(info) {
		let base_attr = info.__base_attr;
		if (base_attr === undefined) {
			base_attr = {};
			let ___OBJECT_1 = info;
			for (let key in ___OBJECT_1) {
				let value = ___OBJECT_1[key];
				if (value === undefined) continue;
				if (__byte(key, 1) !== 95 && (__type(value) !== "table" || value.__class === undefined) && key !== "file_path") {
					base_attr[key] = value;
				}
			}
			info.__base_attr = base_attr;
		}
		let ___OBJECT_2 = base_attr;
		for (let key in ___OBJECT_2) {
			let value = ___OBJECT_2[key];
			if (value === undefined) continue;
			this[key] = value;
		}
		if (info.font_path !== undefined) {
			this["font_path"] = info.font_path;
		}
	},
	get font_height() {
		return this._show.GetFontHeight();
	},
	get flip() {
		return this._flip;
	},
	set flip(value) {
		this._flip = value;
		this._show.SetFlip(value);
	},
}, "ALittle.Text");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


let __tostring = ALittle.String_ToString;
if (ALittle.DisplayObject === undefined) throw new Error(" extends class:ALittle.DisplayObject is undefined");
ALittle.TextArea = JavaScript.Class(ALittle.DisplayObject, {
	Ctor : function(ctrl_sys) {
		this._text = "";
		this._bold = false;
		this._italic = false;
		this._underline = false;
		this._deleteline = false;
		this._outline = false;
		this._flip = 0;
		this._halign_type = ALittle.UIEnumTypes.HALIGN_LEFT;
		this._valign_type = ALittle.UIEnumTypes.VALIGN_TOP;
		this._show = ALittle.NewObject(JavaScript.JTextArea);
	},
	Redraw : function() {
		this._show.NeedDraw();
	},
	set font_path(value) {
		this._font_path = value;
		if (this._font_path === undefined || this._font_size === undefined) {
			return;
		}
		this._ctrl_sys.SetFont(this, this._font_path, this._font_size);
	},
	set font_size(value) {
		this._font_size = value;
		if (this._font_path === undefined || this._font_size === undefined) {
			return;
		}
		this._ctrl_sys.SetFont(this, this._font_path, this._font_size);
	},
	get font_path() {
		return this._font_path;
	},
	get font_size() {
		return this._font_size;
	},
	set text(value) {
		if (value === undefined) {
			return;
		}
		value = __tostring(value);
		if (this._text === value) {
			return;
		}
		this._text = value;
		this._show.SetText(value);
	},
	get text() {
		return this._text;
	},
	set bold(value) {
		if (this._bold === value) {
			return;
		}
		this._bold = value;
		this._show.SetBold(value);
	},
	get bold() {
		return this._bold;
	},
	set italic(value) {
		if (this._italic === value) {
			return;
		}
		this._italic = value;
		this._show.SetItalic(value);
	},
	get italic() {
		return this._italic;
	},
	set underline(value) {
		if (this._underline === value) {
			return;
		}
		this._underline = value;
		this._show.SetUnderline(value);
	},
	get underline() {
		return this._underline;
	},
	set deleteline(value) {
		if (this._deleteline === value) {
			return;
		}
		this._deleteline = value;
		this._show.SetDeleteline(value);
	},
	get deleteline() {
		return this._deleteline;
	},
	set outline(value) {
		if (this._outline === value) {
			return;
		}
		this._outline = value;
		this._show.SetOutline(value);
	},
	get outline() {
		return this._outline;
	},
	set halign(value) {
		if (this._halign_type === value) {
			return;
		}
		this._halign_type = value;
		this._show.SetHAlign(value);
	},
	get halign() {
		return this._halign_type;
	},
	set valign(value) {
		if (this._valign_type === value) {
			return;
		}
		this._valign_type = value;
		this._show.SetVAlign(value);
	},
	get valign() {
		return this._valign_type;
	},
	get real_height() {
		return this._show.GetRealHeight();
	},
	get flip() {
		return this._flip;
	},
	set flip(value) {
		this._flip = value;
		this._show.SetFlip(value);
	},
}, "ALittle.TextArea");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


let __type = ALittle.String_Type;
let __tonumber = ALittle.Math_ToDouble;
let __tostring = ALittle.String_ToString;
let __floor = ALittle.Math_Floor;
let __sub = ALittle.String_Sub;
let __find = ALittle.String_Find;
if (ALittle.DisplayObject === undefined) throw new Error(" extends class:ALittle.DisplayObject is undefined");
ALittle.TextEdit = JavaScript.Class(ALittle.DisplayObject, {
	Ctor : function(ctrl_sys) {
		this._show = ALittle.NewObject(JavaScript.JTextEdit);
		this._cursor_red = 1;
		this._cursor_green = 1;
		this._cursor_blue = 1;
		this._bold = false;
		this._italic = false;
		this._underline = false;
		this._deleteline = false;
		this._outline = false;
		this._default_text = "";
		this._default_text_alpha = 1;
		this._flip = 0;
		this._current_flash_alpha = 1;
		this._current_flash_dir = -0.05;
		this._is_selecting = false;
		this._can_scroll = true;
		this._editable = true;
		this._ims_padding = 0;
		this._regex = "";
		this._limit_len = 0;
		this.AddEventListener(___all_struct.get(-644464135), this, this.HandleFocusIn);
		this.AddEventListener(___all_struct.get(292776509), this, this.HandleFocusOut);
		this.AddEventListener(___all_struct.get(544684311), this, this.HandleMoveIn);
		this.AddEventListener(___all_struct.get(-1202439334), this, this.HandleMoveOut);
		this.AddEventListener(___all_struct.get(1883782801), this, this.HandleLButtonDown);
		this.AddEventListener(___all_struct.get(-1234078962), this, this.HandleTextInput);
		this.AddEventListener(___all_struct.get(-1604617962), this, this.HandleKeyDown);
		this.AddEventListener(___all_struct.get(1301789264), this, this.HandleDragBegin);
		this.AddEventListener(___all_struct.get(1337289812), this, this.HandleDrag);
		this.AddEventListener(___all_struct.get(-1737121315), this, this.HandleMButtonWheel);
		this._move_in = false;
		this._focus_in = false;
	},
	Redraw : function() {
		this._show.NeedDraw();
	},
	Update : function() {
		if (this._is_selecting === false) {
			this._current_flash_alpha = this._current_flash_alpha + this._current_flash_dir;
			if ((this._current_flash_dir < 0 && this._current_flash_alpha < -0.05) || (this._current_flash_dir > 0 && this._current_flash_alpha > 1.5)) {
				this._current_flash_dir = -this._current_flash_dir;
			}
		} else {
			this._current_flash_alpha = 0.5;
		}
		this._show.SetCursorAlpha(this._current_flash_alpha);
	},
	get is_input() {
		return true;
	},
	GetRealHeight : function() {
		return this._show.GetRealHeight();
	},
	GetLineWidth : function(line_index) {
		-- line_index;
		return this._show.GetLineWidth(line_index);
	},
	GetLineCount : function() {
		return this._show.GetLineCount();
	},
	GetScrollOffset : function() {
		return this._show.GetScrollOffset();
	},
	set default_text(value) {
		this._default_text = value;
		if (this._default_text === undefined) {
			this._default_text = "";
		}
		if (this._show.IsDefaultText()) {
			this._show.SetDefaultText(true, this._default_text);
		}
	},
	get default_text() {
		return this._default_text;
	},
	set default_text_alpha(value) {
		if (__type(value) !== "number") {
			value = __tonumber(value);
		}
		if (value === undefined || this._default_text_alpha === value) {
			return;
		}
		this._default_text_alpha = value;
		this._show.SetDefaultTextAlpha(value);
	},
	get default_text_alpha() {
		return this._default_text_alpha;
	},
	get cursor_x() {
		return this._show.GetCursorX();
	},
	get cursor_y() {
		return this._show.GetCursorY();
	},
	set editable(value) {
		this._editable = value;
	},
	get editable() {
		return this._editable;
	},
	set font_path(value) {
		this._font_path = value;
		if (this._font_path === undefined || this._font_size === undefined) {
			return;
		}
		this._ctrl_sys.SetFont(this, this._font_path, this._font_size);
	},
	set font_size(value) {
		this._font_size = value;
		if (this._font_path === undefined || this._font_size === undefined) {
			return;
		}
		this._ctrl_sys.SetFont(this, this._font_path, this._font_size);
	},
	get font_path() {
		return this._font_path;
	},
	get font_size() {
		return this._font_size;
	},
	set text(value) {
		if (value === undefined) {
			return;
		}
		value = __tostring(value);
		this._is_selecting = false;
		if (value === "") {
			if (this._default_text === undefined) {
				this._default_text = "";
			}
			this._show.SetDefaultText(true, this._default_text);
		} else {
			this._show.SetDefaultText(false, "");
			this._show.SetText(value);
		}
	},
	get text() {
		if (this._show.IsDefaultText()) {
			return "";
		}
		return this._show.GetText();
	},
	set bold(value) {
		if (this._bold === value) {
			return;
		}
		this._bold = value;
		this._show.SetBold(value);
	},
	get bold() {
		return this._bold;
	},
	set italic(value) {
		if (this._italic === value) {
			return;
		}
		this._italic = value;
		this._show.SetItalic(value);
	},
	get italic() {
		return this._italic;
	},
	set underline(value) {
		if (this._underline === value) {
			return;
		}
		this._underline = value;
		this._show.SetUnderline(value);
	},
	get underline() {
		return this._underline;
	},
	set deleteline(value) {
		if (this._deleteline === value) {
			return;
		}
		this._deleteline = value;
		this._show.SetDeleteline(value);
	},
	get deleteline() {
		return this._deleteline;
	},
	set outline(value) {
		if (this._outline === value) {
			return;
		}
		this._outline = value;
		this._show.SetOutline(value);
	},
	get outline() {
		return this._outline;
	},
	SetCursorToEnd : function() {
		this._is_selecting = false;
		this._show.SetCursorToEnd();
	},
	SetCursorToHome : function() {
		this._is_selecting = false;
		this._show.SetCursorToHome();
	},
	set ims_padding(value) {
		this._ims_padding = value;
	},
	get ims_padding() {
		return this._ims_padding;
	},
	get regex() {
		return this._regex;
	},
	set regex(value) {
		if (value === undefined) {
			value = "";
		}
		this._regex = value;
	},
	get limit_len() {
		return this._limit_len;
	},
	set limit_len(value) {
		if (value === undefined) {
			value = 0;
		}
		this._limit_len = value;
	},
	HandleFocusIn : function(event) {
		this._show.ShowCursor(true);
		if (this._loop === undefined) {
			this._loop = ALittle.NewObject(ALittle.LoopFunction, this.Update.bind(this), -1, 1, 1);
		}
		A_LoopSystem.AddUpdater(this._loop);
		if (this._editable) {
			let [global_x, global_y] = this.LocalToGlobal();
			global_x = global_x + (this.cursor_x);
			global_y = global_y + ((this.cursor_y + this.font_size) * this.scale_y);
			ALittle.System_SetIMERect(__floor(global_x), __floor(global_y), 10, 5 + this._ims_padding);
			ALittle.System_OpenIME();
		}
		if (this._show.IsDefaultText()) {
			this._show.SetDefaultText(false, "");
		}
		this._focus_in = true;
		this._show.SetDisabled(false);
	},
	HandleFocusOut : function(event) {
		this._focus_in = false;
		this._show.SetDisabled(!this._move_in);
		this._is_selecting = false;
		this._show.ShowCursor(false);
		A_LoopSystem.RemoveUpdater(this._loop);
		ALittle.System_CloseIME();
		if (this.text === "") {
			if (this._default_text === undefined) {
				this._default_text = "";
			}
			this._show.SetDefaultText(true, this._default_text);
		}
	},
	HandleLButtonDown : function(event) {
		if (this._editable) {
			let [global_x, global_y] = this.LocalToGlobal();
			global_x = global_x + (this.cursor_x);
			global_y = global_y + ((this.cursor_y + this.font_size) * this.scale_y);
			ALittle.System_SetIMERect(__floor(global_x), __floor(global_y), 10, 5 + this._ims_padding);
			ALittle.System_OpenIME();
		}
		if (event.count % 3 === 1) {
			this._is_selecting = false;
			this._show.ClickCursor(event.rel_x, event.rel_y);
		} else if (event.count % 3 === 2) {
			this._is_selecting = this._show.ClickWordCursor(event.rel_x, event.rel_y);
		} else {
			this._is_selecting = true;
			this._show.SelectAll();
		}
	},
	CheckTextRegexLimit : function(text) {
		if (this._limit_len > 0) {
			let text_len = ALittle.String_GetWordCount(text);
			if (text_len > this._limit_len) {
				return false;
			}
			let select_len = ALittle.String_GetWordCount(this._show.GetSelectText());
			let total_len = ALittle.String_GetWordCount(this.text);
			if (total_len - select_len + text_len > this._limit_len) {
				return false;
			}
		}
		if (this._regex !== "") {
			while (text !== "") {
				let byte_count = ALittle.String_GetByteCount(text, 1);
				let sub_text = __sub(text, 1, byte_count);
				let start_it = __find(sub_text, this._regex);
				if (start_it === undefined) {
					return false;
				}
				text = __sub(text, byte_count + 1);
			}
		}
		return true;
	},
	HandleTextInput : function(event) {
		if (this._editable || event.custom) {
			this._is_selecting = false;
			if (this.CheckTextRegexLimit(event.text) === false) {
				return;
			}
			let is_change = this._show.InsertText(event.text);
			if (is_change) {
				this.DispatchEvent(___all_struct.get(958494922), {});
			}
		}
	},
	HandleKeyDown : function(event) {
		let is_change = false;
		if (event.sym === 9) {
			if (this._editable || event.custom) {
				this._is_selecting = false;
				if (this.CheckTextRegexLimit("\t") === false) {
					return;
				}
				is_change = this._show.InsertText("\t");
				if (is_change) {
					this.DispatchEvent(___all_struct.get(958494922), {});
				}
				event.handled = true;
			}
		} else if (event.sym === 1073741904) {
			if (ALittle.BitAnd(event.mod, ALittle.UIEnumTypes.KMOD_SHIFT) === 0) {
				this._is_selecting = false;
				this._show.CursorOffsetLR(true);
			} else {
				this._is_selecting = true;
				this._show.SelectCursorOffsetLR(true);
			}
			event.handled = true;
		} else if (event.sym === 1073741903) {
			if (ALittle.BitAnd(event.mod, ALittle.UIEnumTypes.KMOD_SHIFT) === 0) {
				this._is_selecting = false;
				this._show.CursorOffsetLR(false);
			} else {
				this._is_selecting = true;
				this._show.SelectCursorOffsetLR(false);
			}
			event.handled = true;
		} else if (event.sym === 1073741906) {
			if (ALittle.BitAnd(event.mod, ALittle.UIEnumTypes.KMOD_SHIFT) === 0) {
				this._is_selecting = false;
				this._show.CursorOffsetUD(true);
			} else {
				this._is_selecting = true;
				this._show.SelectCursorOffsetUD(true);
			}
			event.handled = true;
		} else if (event.sym === 1073741905) {
			if (ALittle.BitAnd(event.mod, ALittle.UIEnumTypes.KMOD_SHIFT) === 0) {
				this._is_selecting = false;
				this._show.CursorOffsetUD(false);
			} else {
				this._is_selecting = true;
				this._show.SelectCursorOffsetUD(false);
			}
			event.handled = true;
		} else if (event.sym === 8) {
			if (this._editable || event.custom) {
				this._is_selecting = false;
				is_change = this._show.DeleteText(true);
				event.handled = true;
			}
		} else if (event.sym === 127) {
			if (this._editable || event.custom) {
				this._is_selecting = false;
				is_change = this._show.DeleteText(false);
				event.handled = true;
			}
		} else if (event.sym === 1073741898) {
			this._is_selecting = false;
			this._show.SetCursorToHome();
			event.handled = true;
		} else if (event.sym === 1073741901) {
			this._is_selecting = false;
			this._show.SetCursorToEnd();
			event.handled = true;
		} else if (event.sym === 13 || event.sym === 1073741912) {
			if (this._editable || event.custom) {
				this._is_selecting = false;
				if (this.CheckTextRegexLimit("\n") === false) {
					return;
				}
				is_change = this._show.InsertText("\n");
				if (is_change) {
					this.DispatchEvent(___all_struct.get(958494922), {});
				}
				event.handled = true;
			}
		} else if (event.sym === 120 && ALittle.BitAnd(event.mod, ALittle.UIEnumTypes.KMOD_CTRL) !== 0) {
			if (this._editable || event.custom) {
				this._is_selecting = false;
				let select_text = this._show.GetSelectText();
				if (select_text !== "") {
					ALittle.System_SetClipboardText(select_text);
					is_change = this._show.DeleteSelectText();
				}
				event.handled = true;
			}
		} else if (event.sym === 99 && ALittle.BitAnd(event.mod, ALittle.UIEnumTypes.KMOD_CTRL) !== 0) {
			let select_text = this._show.GetSelectText();
			if (select_text !== "") {
				ALittle.System_SetClipboardText(select_text);
			}
			event.handled = true;
		} else if (event.sym === 118 && ALittle.BitAnd(event.mod, ALittle.UIEnumTypes.KMOD_CTRL) !== 0) {
			if (this._editable || event.custom) {
				this._is_selecting = false;
				if (ALittle.System_HasClipboardText()) {
					let clip_board_text = ALittle.System_GetClipboardText();
					if (this.CheckTextRegexLimit(clip_board_text) === false) {
						return;
					}
					is_change = this._show.InsertText(clip_board_text);
				}
				event.handled = true;
			}
		} else if (event.sym === 97 && ALittle.BitAnd(event.mod, ALittle.UIEnumTypes.KMOD_CTRL) !== 0) {
			this._is_selecting = true;
			this._show.SelectAll();
			event.handled = true;
		}
		if (is_change) {
			this.DispatchEvent(___all_struct.get(958494922), {});
			this._current_flash_alpha = 1.5;
		}
	},
	SelectAll : function() {
		this._is_selecting = true;
		this._show.SelectAll();
	},
	CopyText : function() {
		let select_text = this._show.GetSelectText();
		if (select_text === "") {
			select_text = this.text;
		}
		if (select_text !== "") {
			ALittle.System_SetClipboardText(select_text);
		}
	},
	PasteText : function() {
		if (this._editable === false) {
			return;
		}
		if (this._show.IsDefaultText()) {
			this._show.SetDefaultText(false, "");
		}
		this._is_selecting = false;
		if (ALittle.System_HasClipboardText()) {
			let clip_board_text = ALittle.System_GetClipboardText();
			if (this.CheckTextRegexLimit(clip_board_text) === false) {
				return;
			}
			this._show.InsertText(clip_board_text);
		}
	},
	CutText : function() {
		if (this._editable === false) {
			return;
		}
		this._is_selecting = false;
		let select_text = this._show.GetSelectText();
		if (select_text !== "") {
			ALittle.System_SetClipboardText(select_text);
			this._show.DeleteSelectText();
		}
	},
	InsertText : function(text) {
		if (this._editable === false) {
			return;
		}
		if (this._show.IsDefaultText()) {
			this._show.SetDefaultText(false, "");
		}
		this._is_selecting = false;
		if (text !== undefined) {
			if (this.CheckTextRegexLimit(text) === false) {
				return;
			}
			this._show.InsertText(text);
		}
	},
	HandleDragBegin : function(event) {
		this._is_selecting = true;
		this._show.DragCursorBegin();
	},
	HandleDrag : function(event) {
		if (this._is_selecting === false) {
			return;
		}
		this._show.DragCursor(event.rel_x, event.rel_y);
	},
	HandleMButtonWheel : function(event) {
		if (event.delta_y > 0) {
			this._is_selecting = false;
			this._show.CursorOffsetUD(true);
		} else if (event.delta_y < 0) {
			this._is_selecting = false;
			this._show.CursorOffsetUD(false);
		}
		if (event.delta_x > 0) {
			this._is_selecting = false;
			this._show.SelectCursorOffsetLR(true);
		} else if (event.delta_x < 0) {
			this._is_selecting = false;
			this._show.SelectCursorOffsetLR(false);
		}
	},
	HandleMoveIn : function(event) {
		this._move_in = true;
		this._show.SetDisabled(false);
		ALittle.System_SetEditCursor();
	},
	HandleMoveOut : function(event) {
		this._move_in = false;
		this._show.SetDisabled(!this._focus_in);
		ALittle.System_SetNormalCursor();
	},
	set cursor_red(value) {
		if (this._cursor_red === value) {
			return;
		}
		this._cursor_red = value;
		this._show.SetCursorRed(value);
	},
	get cursor_red() {
		return this._cursor_red;
	},
	set cursor_green(value) {
		if (this._cursor_green === value) {
			return;
		}
		this._cursor_green = value;
		this._show.SetCursorGreen(value);
	},
	get cursor_green() {
		return this._cursor_green;
	},
	set cursor_blue(value) {
		if (this._cursor_blue === value) {
			return;
		}
		this._cursor_blue = value;
		this._show.SetCursorBlue(value);
	},
	get cursor_blue() {
		return this._cursor_blue;
	},
	get flip() {
		return this._flip;
	},
	set flip(value) {
		this._flip = value;
		this._show.SetFlip(value);
	},
}, "ALittle.TextEdit");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


let __type = ALittle.String_Type;
let __tonumber = ALittle.Math_ToDouble;
let __tostring = ALittle.String_ToString;
let __floor = ALittle.Math_Floor;
let __sub = ALittle.String_Sub;
let __find = ALittle.String_Find;
if (ALittle.DisplayObject === undefined) throw new Error(" extends class:ALittle.DisplayObject is undefined");
ALittle.TextInput = JavaScript.Class(ALittle.DisplayObject, {
	Ctor : function(ctrl_sys) {
		this._show = ALittle.NewObject(JavaScript.JTextInput);
		this._cursor_red = 1;
		this._cursor_green = 1;
		this._cursor_blue = 1;
		this._bold = false;
		this._italic = false;
		this._underline = false;
		this._deleteline = false;
		this._outline = false;
		this._password_mode = false;
		this._default_text = "";
		this._default_text_alpha = 1;
		this._flip = 0;
		this._current_flash_alpha = 1;
		this._current_flash_dir = -0.05;
		this._is_selecting = false;
		this._editable = true;
		this._ims_padding = 0;
		this._regex = "";
		this._limit_len = 0;
		this.AddEventListener(___all_struct.get(-644464135), this, this.HandleFocusIn);
		this.AddEventListener(___all_struct.get(292776509), this, this.HandleFocusOut);
		this.AddEventListener(___all_struct.get(544684311), this, this.HandleMoveIn);
		this.AddEventListener(___all_struct.get(-1202439334), this, this.HandleMoveOut);
		this.AddEventListener(___all_struct.get(1883782801), this, this.HandleLButtonDown);
		this.AddEventListener(___all_struct.get(-1234078962), this, this.HandleTextInput);
		this.AddEventListener(___all_struct.get(-1604617962), this, this.HandleKeyDown);
		this.AddEventListener(___all_struct.get(1301789264), this, this.HandleDragBegin);
		this.AddEventListener(___all_struct.get(1337289812), this, this.HandleDrag);
		this._move_in = false;
		this._focus_in = false;
	},
	Redraw : function() {
		this._show.NeedDraw();
	},
	get is_input() {
		return true;
	},
	set default_text(value) {
		this._default_text = value;
		if (this._default_text === undefined) {
			this._default_text = "";
		}
		if (this._show.IsDefaultText()) {
			this._show.SetDefaultText(true, this._default_text);
		}
	},
	get default_text() {
		return this._default_text;
	},
	set default_text_alpha(value) {
		if (this._default_text_alpha === value) {
			return;
		}
		this._default_text_alpha = value;
		this._show.SetDefaultTextAlpha(value);
	},
	get default_text_alpha() {
		return this._default_text_alpha;
	},
	Update : function() {
		if (this._is_selecting === false) {
			this._current_flash_alpha = this._current_flash_alpha + this._current_flash_dir;
			if ((this._current_flash_dir < 0 && this._current_flash_alpha < -0.05) || (this._current_flash_dir > 0 && this._current_flash_alpha > 1.5)) {
				this._current_flash_dir = -this._current_flash_dir;
			}
		} else {
			this._current_flash_alpha = 0.5;
		}
		this._show.SetCursorAlpha(this._current_flash_alpha);
	},
	get cursor_x() {
		return this._show.GetCursorX();
	},
	get cursor_y() {
		return this._show.GetCursorY();
	},
	set editable(value) {
		this._editable = value;
	},
	get editable() {
		return this._editable;
	},
	set font_path(value) {
		this._font_path = value;
		if (this._font_path === undefined || this._font_size === undefined) {
			return;
		}
		this._ctrl_sys.SetFont(this, this._font_path, this._font_size);
	},
	set font_size(value) {
		this._font_size = value;
		if (this._font_path === undefined || this._font_size === undefined) {
			return;
		}
		this._ctrl_sys.SetFont(this, this._font_path, this._font_size);
	},
	get font_path() {
		return this._font_path;
	},
	get font_size() {
		return this._font_size;
	},
	set text(value) {
		if (value === undefined) {
			return;
		}
		value = __tostring(value);
		this._is_selecting = false;
		if (value === "") {
			if (this._default_text === undefined) {
				this._default_text = "";
			}
			this._show.SetDefaultText(true, this._default_text);
		} else {
			this._show.SetDefaultText(false, "");
			this._show.SetText(value);
		}
	},
	get text() {
		if (this._show.IsDefaultText()) {
			return "";
		}
		return this._show.GetText();
	},
	set bold(value) {
		if (this._bold === value) {
			return;
		}
		this._bold = value;
		this._show.SetBold(value);
	},
	get bold() {
		return this._bold;
	},
	set italic(value) {
		if (this._italic === value) {
			return;
		}
		this._italic = value;
		this._show.SetItalic(value);
	},
	get italic() {
		return this._italic;
	},
	set underline(value) {
		if (this._underline === value) {
			return;
		}
		this._underline = value;
		this._show.SetUnderline(value);
	},
	get underline() {
		return this._underline;
	},
	set deleteline(value) {
		if (this._deleteline === value) {
			return;
		}
		this._deleteline = value;
		this._show.SetDeleteline(value);
	},
	get deleteline() {
		return this._deleteline;
	},
	set outline(value) {
		if (this._outline === value) {
			return;
		}
		this._outline = value;
		this._show.SetOutline(value);
	},
	get outline() {
		return this._outline;
	},
	set password_mode(value) {
		this._is_selecting = false;
		if (this._password_mode === value) {
			return;
		}
		this._password_mode = value;
		this._show.SetPasswordMode(value);
	},
	get password_mode() {
		return this._password_mode;
	},
	set ims_padding(value) {
		this._ims_padding = value;
	},
	get ims_padding() {
		return this._ims_padding;
	},
	get regex() {
		return this._regex;
	},
	set regex(value) {
		if (value === undefined) {
			value = "";
		}
		this._regex = value;
	},
	get limit_len() {
		return this._limit_len;
	},
	set limit_len(value) {
		if (value === undefined) {
			value = 0;
		}
		this._limit_len = value;
	},
	HandleFocusIn : function(event) {
		this._show.ShowCursor(true);
		if (this._loop === undefined) {
			this._loop = ALittle.NewObject(ALittle.LoopFunction, this.Update.bind(this), -1, 1, 1);
		}
		A_LoopSystem.AddUpdater(this._loop);
		if (this._editable) {
			let [global_x, global_y] = this.LocalToGlobal();
			ALittle.System_SetIMERect(__floor(global_x), __floor(global_y), __floor(this._width * this.scale_x), __floor(this._height * this.scale_y) + this._ims_padding);
			ALittle.System_OpenIME();
		}
		if (this._show.IsDefaultText()) {
			this._show.SetDefaultText(false, "");
		}
		this._focus_in = true;
		this._show.SetDisabled(false);
	},
	HandleFocusOut : function(event) {
		this._focus_in = false;
		this._show.SetDisabled(!this._move_in);
		this._is_selecting = false;
		this._show.ShowCursor(false);
		A_LoopSystem.RemoveUpdater(this._loop);
		ALittle.System_CloseIME();
		if (this.text === "") {
			if (this._default_text === undefined) {
				this._default_text = "";
			}
			this._show.SetDefaultText(true, this._default_text);
		}
	},
	HandleLButtonDown : function(event) {
		if (this._editable) {
			let [global_x, global_y] = this.LocalToGlobal();
			ALittle.System_SetIMERect(__floor(global_x), __floor(global_y), __floor(this._width * this.scale_x), __floor(this._height * this.scale_y) + this._ims_padding);
			ALittle.System_OpenIME();
		}
		if (event.count % 3 === 1) {
			this._is_selecting = false;
			this._show.ClickCursor(event.rel_x, 0.0);
		} else if (event.count % 3 === 2) {
			this._is_selecting = this._show.ClickWordCursor(event.rel_x, 0.0);
		} else {
			this._is_selecting = true;
			this._show.SelectAll();
		}
	},
	CheckTextRegexLimit : function(text) {
		if (this._limit_len > 0) {
			let text_len = ALittle.String_GetWordCount(text);
			if (text_len > this._limit_len) {
				return false;
			}
			let select_len = ALittle.String_GetWordCount(this._show.GetSelectText());
			let total_len = ALittle.String_GetWordCount(this.text);
			if (total_len - select_len + text_len > this._limit_len) {
				return false;
			}
		}
		if (this._regex !== "") {
			while (text !== "") {
				let byte_count = ALittle.String_GetByteCount(text, 1);
				let sub_text = __sub(text, 1, byte_count);
				let start_it = __find(sub_text, this._regex);
				if (start_it === undefined) {
					return false;
				}
				text = __sub(text, byte_count + 1);
			}
		}
		return true;
	},
	HandleTextInput : function(event) {
		if (this._editable || event.custom) {
			this._is_selecting = false;
			if (this.CheckTextRegexLimit(event.text) === false) {
				return;
			}
			let is_change = this._show.InsertText(event.text);
			if (is_change) {
				this.DispatchEvent(___all_struct.get(958494922), {});
			}
		}
	},
	HandleKeyDown : function(event) {
		let is_change = false;
		if (event.sym === 1073741904) {
			if (ALittle.BitAnd(event.mod, ALittle.UIEnumTypes.KMOD_SHIFT) === 0) {
				this._is_selecting = false;
				this._show.CursorOffset(true);
			} else {
				this._is_selecting = true;
				this._show.SelectCursorOffset(true);
			}
			event.handled = true;
		} else if (event.sym === 1073741903) {
			if (ALittle.BitAnd(event.mod, ALittle.UIEnumTypes.KMOD_SHIFT) === 0) {
				this._is_selecting = false;
				this._show.CursorOffset(false);
			} else {
				this._is_selecting = true;
				this._show.SelectCursorOffset(false);
			}
			event.handled = true;
		} else if (event.sym === 8) {
			if (this._editable || event.custom) {
				this._is_selecting = false;
				is_change = this._show.DeleteText(true);
				event.handled = true;
			}
		} else if (event.sym === 127) {
			if (this._editable || event.custom) {
				this._is_selecting = false;
				is_change = this._show.DeleteText(false);
				event.handled = true;
			}
		} else if (event.sym === 1073741898) {
			this._is_selecting = false;
			this._show.SetCursorToHome();
			event.handled = true;
		} else if (event.sym === 1073741901) {
			this._is_selecting = false;
			this._show.SetCursorToEnd();
			event.handled = true;
		} else if (event.sym === 13 || event.sym === 1073741912) {
			if (this._editable || event.custom) {
				this.DispatchEvent(___all_struct.get(776398171), {});
				event.handled = true;
			}
		} else if (event.sym === 120 && ALittle.BitAnd(event.mod, ALittle.UIEnumTypes.KMOD_CTRL) !== 0) {
			if (this._editable || event.custom) {
				this._is_selecting = false;
				let select_text = this._show.GetSelectText();
				if (select_text !== "" && (!this._password_mode)) {
					ALittle.System_SetClipboardText(select_text);
					is_change = this._show.DeleteSelectText();
				}
				event.handled = true;
			}
		} else if (event.sym === 99 && ALittle.BitAnd(event.mod, ALittle.UIEnumTypes.KMOD_CTRL) !== 0) {
			let select_text = this._show.GetSelectText();
			if (select_text !== "" && (!this._password_mode)) {
				ALittle.System_SetClipboardText(select_text);
			}
			event.handled = true;
		} else if (event.sym === 118 && ALittle.BitAnd(event.mod, ALittle.UIEnumTypes.KMOD_CTRL) !== 0) {
			if (this._editable || event.custom) {
				this._is_selecting = false;
				if (ALittle.System_HasClipboardText()) {
					let clip_board_text = ALittle.System_GetClipboardText();
					if (this.CheckTextRegexLimit(clip_board_text) === false) {
						return;
					}
					is_change = this._show.InsertText(clip_board_text);
				}
				event.handled = true;
			}
		} else if (event.sym === 97 && ALittle.BitAnd(event.mod, ALittle.UIEnumTypes.KMOD_CTRL) !== 0) {
			this._is_selecting = true;
			this._show.SelectAll();
			event.handled = true;
		} else if (event.sym === 9) {
			this.DispatchEvent(___all_struct.get(2024735182), {});
		}
		if (is_change) {
			this.DispatchEvent(___all_struct.get(958494922), {});
			this._current_flash_alpha = 1.5;
		}
	},
	SetCursorToHome : function() {
		this._is_selecting = false;
		this._show.SetCursorToHome();
	},
	SetCursorToEnd : function() {
		this._is_selecting = false;
		this._show.SetCursorToEnd();
	},
	SelectAll : function() {
		this._is_selecting = true;
		this._show.SelectAll();
	},
	CopyText : function() {
		let select_text = this._show.GetSelectText();
		if (select_text === "") {
			select_text = this.text;
		}
		if (select_text !== "") {
			ALittle.System_SetClipboardText(select_text);
		}
	},
	PasteText : function() {
		if (this._editable === false) {
			return;
		}
		if (this._show.IsDefaultText()) {
			this._show.SetDefaultText(false, "");
		}
		this._is_selecting = false;
		if (ALittle.System_HasClipboardText()) {
			let clip_board_text = ALittle.System_GetClipboardText();
			if (this.CheckTextRegexLimit(clip_board_text) === false) {
				return;
			}
			this._show.InsertText(clip_board_text);
		}
	},
	CutText : function() {
		if (this._editable === false) {
			return;
		}
		this._is_selecting = false;
		let select_text = this._show.GetSelectText();
		if (select_text !== "") {
			ALittle.System_SetClipboardText(select_text);
			this._show.DeleteSelectText();
		}
	},
	InsertText : function(text) {
		if (this._editable === false) {
			return;
		}
		if (this._show.IsDefaultText()) {
			this._show.SetDefaultText(false, "");
		}
		this._is_selecting = false;
		if (text !== undefined) {
			if (this.CheckTextRegexLimit(text) === false) {
				return;
			}
			this._show.InsertText(text);
		}
	},
	HandleDragBegin : function(event) {
		this._is_selecting = true;
		this._show.DragCursorBegin();
	},
	HandleDrag : function(event) {
		if (this._is_selecting === false) {
			return;
		}
		this._show.DragCursor(event.rel_x, event.rel_y);
	},
	HandleMoveIn : function(event) {
		this._move_in = true;
		this._show.SetDisabled(false);
		ALittle.System_SetEditCursor();
	},
	HandleMoveOut : function(event) {
		this._move_in = false;
		this._show.SetDisabled(!this._focus_in);
		ALittle.System_SetNormalCursor();
	},
	set cursor_red(value) {
		if (this._cursor_red === value) {
			return;
		}
		this._cursor_red = value;
		this._show.SetCursorRed(value);
	},
	get cursor_red() {
		return this._cursor_red;
	},
	set cursor_green(value) {
		if (this._cursor_green === value) {
			return;
		}
		this._cursor_green = value;
		this._show.SetCursorGreen(value);
	},
	get cursor_green() {
		return this._cursor_green;
	},
	set cursor_blue(value) {
		if (this._cursor_blue === value) {
			return;
		}
		this._cursor_blue = value;
		this._show.SetCursorBlue(value);
	},
	get cursor_blue() {
		return this._cursor_blue;
	},
	get flip() {
		return this._flip;
	},
	set flip(value) {
		this._flip = value;
		this._show.SetFlip(value);
	},
}, "ALittle.TextInput");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.DisplayObject === undefined) throw new Error(" extends class:ALittle.DisplayObject is undefined");
ALittle.Triangle = JavaScript.Class(ALittle.DisplayObject, {
	Ctor : function(ctrl_sys) {
		this._show = ALittle.NewObject(JavaScript.JTriangle);
		this._u1 = 0;
		this._v1 = 0;
		this._u2 = 0;
		this._v2 = 0;
		this._u3 = 0;
		this._v3 = 0;
		this._x1 = 0;
		this._y1 = 0;
		this._x2 = 0;
		this._y2 = 0;
		this._x3 = 0;
		this._y3 = 0;
		this._texture_width = 0;
		this._texture_height = 0;
		this._auto_rejust = false;
	},
	Redraw : function() {
		this._show.ClearTexture();
		if (this._texture !== undefined) {
			this._texture.Clear();
			this._texture = undefined;
		}
		if (this._texture_name === undefined) {
			return;
		}
		if (this._texture_cut !== undefined) {
			A_LoadTextureManager.SetTextureCut(this, this._texture_name, this._texture_cut.max_width, this._texture_cut.max_height, this._texture_cut.cache);
		} else {
			this._ctrl_sys.SetTexture(this, this._texture_name);
		}
	},
	set texture_name(value) {
		if (this._texture_name === value) {
			return;
		}
		if (this._texture_name !== undefined) {
			this._show.ClearTexture();
			this._texture = undefined;
		}
		this._texture_name = value;
		if (this._texture_name !== undefined) {
			this._texture_cut = undefined;
			this._ctrl_sys.SetTexture(this, value);
		}
	},
	SetTextureCut : function(texture_name, auto_rejust, max_width, max_height, cache, index) {
		if (this._texture_name !== undefined) {
			this._show.ClearTexture();
			this._texture = undefined;
		}
		this._texture_name = texture_name;
		if (this._texture_name !== undefined) {
			this._texture_cut = {};
			this._texture_cut.max_width = max_width;
			this._texture_cut.max_height = max_height;
			this._texture_cut.cache = cache;
			this._auto_rejust = auto_rejust || false;
			A_LoadTextureManager.SetTextureCut(this, texture_name, max_width, max_height, cache);
		}
	},
	set texture_cut(param) {
		this.SetTextureCut(param.texture_name, true, param.max_width, param.max_height, param.cache, undefined);
	},
	get texture_cut() {
		if (this._texture_cut === undefined) {
			return undefined;
		}
		let texture_cut = {};
		texture_cut.max_width = this._texture_cut.max_width;
		texture_cut.max_height = this._texture_cut.max_height;
		texture_cut.texture_name = this._texture_name;
		return texture_cut;
	},
	get texture_name() {
		return this._texture_name;
	},
	set texture(value) {
		this._show.SetTexture(value.GetTexture());
		this._texture_width = value.GetWidth();
		this._texture_height = value.GetHeight();
		this._texture = value;
		if (this._auto_rejust) {
			this.width = this._texture_width;
			this.height = this._texture_height;
		}
	},
	get texture() {
		return this._texture;
	},
	SetTextureCoord : function(t, b, l, r) {
		this._show.SetTextureCoord(t, b, l, r);
	},
	get texture_width() {
		return this._texture_width;
	},
	get texture_height() {
		return this._texture_height;
	},
	get u1() {
		return this._u1;
	},
	get v1() {
		return this._v1;
	},
	get u2() {
		return this._u2;
	},
	get v2() {
		return this._v2;
	},
	get u3() {
		return this._u3;
	},
	get v3() {
		return this._v3;
	},
	set u1(v) {
		this._u1 = v;
		this._show.SetTexUV(0, this._u1, this._v1);
	},
	set v1(v) {
		this._v1 = v;
		this._show.SetTexUV(0, this._u1, this._v1);
	},
	set u2(v) {
		this._u2 = v;
		this._show.SetTexUV(1, this._u2, this._v2);
	},
	set v2(v) {
		this._v2 = v;
		this._show.SetTexUV(1, this._u2, this._v2);
	},
	set u3(v) {
		this._u3 = v;
		this._show.SetTexUV(2, this._u3, this._v3);
	},
	set v3(v) {
		this._v3 = v;
		this._show.SetTexUV(2, this._u3, this._v3);
	},
	get x1() {
		return this._x1;
	},
	get y1() {
		return this._y1;
	},
	get x2() {
		return this._x2;
	},
	get y2() {
		return this._y2;
	},
	get x3() {
		return this._x3;
	},
	get y3() {
		return this._y3;
	},
	set x1(v) {
		this._x1 = v;
		this._show.SetPosXY(0, this._x1, this._y1);
	},
	set y1(v) {
		this._y1 = v;
		this._show.SetPosXY(0, this._x1, this._y1);
	},
	set x2(v) {
		this._x2 = v;
		this._show.SetPosXY(1, this._x2, this._y2);
	},
	set y2(v) {
		this._y2 = v;
		this._show.SetPosXY(1, this._x2, this._y2);
	},
	set x3(v) {
		this._x3 = v;
		this._show.SetPosXY(2, this._x3, this._y3);
	},
	set y3(v) {
		this._y3 = v;
		this._show.SetPosXY(2, this._x3, this._y3);
	},
	RejuseSize : function() {
		let max = this._x1;
		if (max < this._x2) {
			max = this._x2;
		}
		if (max < this._x3) {
			max = this._x3;
		}
		this.width = max;
		max = this._y1;
		if (max < this._y2) {
			max = this._y2;
		}
		if (max < this._y3) {
			max = this._y3;
		}
		this.height = max;
		this.UpdateLayout();
	},
}, "ALittle.Triangle");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.DisplayObject === undefined) throw new Error(" extends class:ALittle.DisplayObject is undefined");
ALittle.Grid9Image = JavaScript.Class(ALittle.DisplayObject, {
	Ctor : function(ctrl_sys) {
		this._show = ALittle.NewObject(JavaScript.JGrid9Image);
		this._texture_width = 0;
		this._texture_height = 0;
		this._flip = 0;
		this._tex_coord_t = 0;
		this._tex_coord_b = 1;
		this._tex_coord_l = 0;
		this._tex_coord_r = 1;
		this._left_size = 0;
		this._right_size = 0;
		this._top_size = 0;
		this._bottom_size = 0;
		this.AddEventListener(___all_struct.get(40651933), this, this.HandleLButtonUp);
		this.AddEventListener(___all_struct.get(683647260), this, this.HandleMButtonUp);
		this.AddEventListener(___all_struct.get(734860930), this, this.HandleFLButtonUp);
	},
	HandleLButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let c_event = {};
			c_event.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(-449066808), c_event);
		}
	},
	HandleMButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let c_event = {};
			c_event.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(-1330840), c_event);
		}
	},
	HandleFLButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let c_event = {};
			c_event.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(286797479), c_event);
		}
	},
	Redraw : function() {
		this._show.ClearTexture();
		if (this._texture !== undefined) {
			this._texture.Clear();
			this._texture = undefined;
		}
		if (this._texture_name === undefined) {
			return;
		}
		if (this._texture_cut !== undefined) {
			A_LoadTextureManager.SetTextureCut(this, this._texture_name, this._texture_cut.max_width, this._texture_cut.max_height, this._texture_cut.cache);
		} else {
			this._ctrl_sys.SetTexture(this, this._texture_name);
		}
	},
	CopyTextureRef : function(image) {
		if (image === undefined || image._texture === undefined) {
			return;
		}
		this._texture_name = image._texture_name;
		this._texture_cut = undefined;
		if (image._texture_cut !== undefined) {
			this._texture_cut = {};
			this._texture_cut.max_width = image._texture_cut.max_width;
			this._texture_cut.max_height = image._texture_cut.max_height;
			this._texture_cut.cache = image._texture_cut.cache;
		}
		this._texture = image._texture;
		this._show.SetTexture(image._texture.GetTexture());
		this.SetTextureCoord(image._tex_coord_t, image._tex_coord_b, image._tex_coord_l, image._tex_coord_r);
		this._texture_width = image._texture_width;
		this._texture_height = image._texture_height;
		this.left_size = image.left_size;
		this.right_size = image.right_size;
		this.top_size = image.top_size;
		this.bottom_size = image.bottom_size;
	},
	set texture_name(value) {
		if (this._texture_name === value) {
			return;
		}
		if (this._texture_name !== undefined) {
			this._show.ClearTexture();
			this._texture = undefined;
		}
		this._texture_name = value;
		if (this._texture_name !== undefined) {
			this._texture_cut = undefined;
			this._ctrl_sys.SetTexture(this, value);
		}
	},
	SetTextureCut : function(texture_name, max_width, max_height, cache, index, callback) {
		if (this._texture_name !== undefined) {
			this._show.ClearTexture();
			this._texture = undefined;
		}
		this._texture_name = texture_name;
		if (this._texture_name !== undefined) {
			this._texture_cut = {};
			this._texture_cut.max_width = max_width;
			this._texture_cut.max_height = max_height;
			this._texture_cut.cache = cache;
			A_LoadTextureManager.SetTextureCut(this, texture_name, max_width, max_height, cache, callback);
		}
	},
	set texture_cut(param) {
		this.SetTextureCut(param.texture_name, param.max_width, param.max_height, param.cache, undefined);
	},
	get texture_cut() {
		if (this._texture_cut === undefined) {
			return undefined;
		}
		let texture_cut = {};
		texture_cut.max_width = this._texture_cut.max_width;
		texture_cut.max_height = this._texture_cut.max_height;
		texture_cut.texture_name = this._texture_name;
		return texture_cut;
	},
	get texture_name() {
		return this._texture_name;
	},
	set texture(value) {
		this._show.SetTexture(value.GetTexture());
		this._texture_width = value.GetWidth();
		this._texture_height = value.GetHeight();
		this._texture = value;
	},
	get texture() {
		return this._texture;
	},
	SetTextureCoord : function(t, b, l, r) {
		this._tex_coord_t = t;
		this._tex_coord_b = b;
		this._tex_coord_l = l;
		this._tex_coord_r = r;
		this._show.SetTextureCoord(t, b, l, r);
	},
	set left_size(value) {
		this._left_size = value;
		this._show.SetLeftSize(value);
	},
	get left_size() {
		return this._left_size;
	},
	set right_size(value) {
		this._right_size = value;
		this._show.SetRightSize(value);
	},
	get right_size() {
		return this._right_size;
	},
	set top_size(value) {
		this._top_size = value;
		this._show.SetTopSize(value);
	},
	get top_size() {
		return this._top_size;
	},
	set bottom_size(value) {
		this._bottom_size = value;
		this._show.SetBottomSize(value);
	},
	get bottom_size() {
		return this._bottom_size;
	},
	get texture_width() {
		return this._texture_width;
	},
	get texture_height() {
		return this._texture_height;
	},
	get flip() {
		return this._flip;
	},
	set flip(value) {
		this._flip = value;
		this._show.SetFlip(value);
	},
}, "ALittle.Grid9Image");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.TextButton = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._show_text = ({});
		this._show_text.width = 0;
		this._show_text.height = 0;
		this._show_text.text = "";
		this._show_text.x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this._show_text.x_value = 0;
		this._show_text.visible = true;
		this._show_down_text = ({});
		this._show_down_text.width = 0;
		this._show_down_text.height = 0;
		this._show_down_text.text = "";
		this._show_down_text.x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this._show_down_text.x_value = 0;
		this._show_down_text.visible = false;
		this._show_over_text = ({});
		this._show_over_text.width = 0;
		this._show_over_text.height = 0;
		this._show_over_text.text = "";
		this._show_over_text.x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this._show_over_text.x_value = 0;
		this._show_over_text.visible = false;
		this._show_disabled_text = ({});
		this._show_disabled_text.width = 0;
		this._show_disabled_text.height = 0;
		this._show_disabled_text.text = "";
		this._show_disabled_text.x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this._show_disabled_text.x_value = 0;
		this._show_disabled_text.visible = false;
		this._file_select = ALittle.UIEnumTypes.SELECT_NONE;
		this.AddEventListener(___all_struct.get(544684311), this, this.HandleMoveIn);
		this.AddEventListener(___all_struct.get(-1202439334), this, this.HandleMoveOut);
		this.AddEventListener(___all_struct.get(1883782801), this, this.HandleLButtonDown);
		this.AddEventListener(___all_struct.get(40651933), this, this.HandleLButtonUp);
		this.AddEventListener(___all_struct.get(349963892), this, this.HandleMButtonDown);
		this.AddEventListener(___all_struct.get(683647260), this, this.HandleMButtonUp);
		this.AddEventListener(___all_struct.get(292776509), this, this.ShowUp);
		this.AddEventListener(___all_struct.get(-1233353463), this, this.HandleFButtonDown);
		this.AddEventListener(___all_struct.get(734860930), this, this.HandleFButtonUp);
		this._pickup_rect = true;
		this._pickup_child = false;
	},
	set disabled(value) {
		ALittle.DisplayObject.__setter.disabled.call(this, value);
		if (value) {
			this.ShowDisabled();
		} else {
			this.ShowUp(undefined);
		}
	},
	HandleMoveIn : function(event) {
		this.ShowOver();
	},
	HandleMoveOut : function(event) {
		this.ShowUp(undefined);
	},
	HandleLButtonDown : function(event) {
		this.ShowDown();
	},
	HandleLButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let e = {};
			e.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(-449066808), e);
			if (this._file_select === ALittle.UIEnumTypes.SELECT_FILE) {
				A_OtherSystem.SystemSelectFile(this);
			} else if (this._file_select === ALittle.UIEnumTypes.SELECT_DIR) {
				A_OtherSystem.SystemSelectDirectory(this);
			}
			if (ALittle.System_IsPhone === false) {
				this.ShowOver();
			} else {
				this.ShowUp(undefined);
			}
		} else {
			this.ShowUp(undefined);
		}
	},
	HandleMButtonDown : function(event) {
		this.ShowDown();
	},
	HandleMButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let e = {};
			e.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(-1330840), e);
			if (ALittle.System_IsPhone === false) {
				this.ShowOver();
			} else {
				this.ShowUp(undefined);
			}
		} else {
			this.ShowUp(undefined);
		}
	},
	HandleFButtonDown : function(event) {
		if (event.is_sfc === false) {
			this.ShowDown();
		}
	},
	HandleFButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let e = {};
			e.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(286797479), e);
		}
		if (event.is_sfc === false) {
			this.ShowUp(undefined);
		}
	},
	set text(value) {
		this._show_text.text = value;
		this._show_over_text.text = value;
		this._show_disabled_text.text = value;
		this._show_down_text.text = value;
	},
	get text() {
		return this._show_text.text;
	},
	set text_x_type(value) {
		this._show_text.x_type = value;
		this._show_over_text.x_type = value;
		this._show_disabled_text.x_type = value;
		this._show_down_text.x_type = value;
	},
	get text_x_type() {
		return this._show_text.x_type;
	},
	set text_x_value(value) {
		this._show_text.x_value = value;
		this._show_over_text.x_value = value;
		this._show_disabled_text.x_value = value;
		this._show_down_text.x_value = value;
	},
	get text_x_value() {
		return this._show_text.x_value;
	},
	ShowUp : function(event) {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._show_up !== undefined) {
			this._show_up.alpha = 1;
		}
		if (this._show_over !== undefined) {
			this._show_over.alpha = 0;
		}
		if (this._show_down !== undefined) {
			this._show_down.alpha = 0;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 0;
		}
		this._show_text.visible = true;
		this._show_down_text.visible = false;
		this._show_over_text.visible = false;
		this._show_disabled_text.visible = false;
	},
	ShowDown : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._show_up !== undefined) {
			this._show_up.alpha = 0;
		}
		if (this._show_over !== undefined) {
			this._show_over.alpha = 0;
		}
		if (this._show_down !== undefined) {
			this._show_down.alpha = 1;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 0;
		}
		this._show_text.visible = true;
		if (this._show_down_text._show !== undefined) {
			this._show_text.visible = false;
		}
		this._show_down_text.visible = true;
		this._show_over_text.visible = false;
		this._show_disabled_text.visible = false;
	},
	ShowOver : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._show_up !== undefined) {
			this._show_up.alpha = 0;
		}
		if (this._show_over !== undefined) {
			this._show_over.alpha = 1;
		}
		if (this._show_down !== undefined) {
			this._show_down.alpha = 0;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 0;
		}
		this._show_text.visible = true;
		if (this._show_over_text._show !== undefined) {
			this._show_text.visible = false;
		}
		this._show_down_text.visible = false;
		this._show_over_text.visible = true;
		this._show_disabled_text.visible = false;
	},
	ShowDisabled : function() {
		if (this._show_up !== undefined) {
			this._show_up.alpha = 0;
		}
		if (this._show_over !== undefined) {
			this._show_over.alpha = 0;
		}
		if (this._show_down !== undefined) {
			this._show_down.alpha = 0;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 1;
		}
		this._show_text.visible = true;
		if (this._show_disabled_text._show !== undefined) {
			this._show_text.visible = false;
		}
		this._show_disabled_text.visible = true;
		this._show_over_text.visible = false;
		this._show_down_text.visible = false;
	},
	set show_text(value) {
		if (value === undefined) {
			let show = this._show_text;
			this.RemoveChild(show);
			this._show_text = ({});
			this._show_text.width = 0;
			this._show_text.height = 0;
			this._show_text.text = show.text;
			this._show_text.visible = show.visible;
			this._show_text.x_type = show.x_type;
			this._show_text.x_value = show.x_value;
			return;
		}
		value.text = this._show_text.text;
		value.visible = this._show_text.visible;
		value.x_type = this._show_text.x_type;
		value.x_value = this._show_text.x_value;
		this.RemoveChild(this._show_text);
		this._show_text = value;
		this._show_text.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this.AddChild(this._show_text, 6);
	},
	get show_text() {
		if (this._show_text._show === undefined) {
			return undefined;
		}
		return this._show_text;
	},
	set show_over_text(value) {
		if (value === undefined) {
			let show = this._show_over_text;
			this.RemoveChild(show);
			this._show_over_text = ({});
			this._show_over_text.width = 0;
			this._show_over_text.height = 0;
			this._show_over_text.text = show.text;
			this._show_over_text.visible = show.visible;
			this._show_over_text.x_type = show.x_type;
			this._show_over_text.x_value = show.x_value;
			return;
		}
		value.text = this._show_over_text.text;
		value.visible = this._show_over_text.visible;
		value.x_type = this._show_over_text.x_type;
		value.x_value = this._show_over_text.x_value;
		this.RemoveChild(this._show_over_text);
		this._show_over_text = value;
		this._show_over_text.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this.AddChild(this._show_over_text, 6);
	},
	get show_over_text() {
		if (this._show_over_text._show === undefined) {
			return undefined;
		}
		return this._show_over_text;
	},
	set show_down_text(value) {
		if (value === undefined) {
			let show = this.show_down_text;
			this.RemoveChild(show);
			this._show_down_text = ({});
			this._show_down_text.width = 0;
			this._show_down_text.height = 0;
			this._show_down_text.text = show.text;
			this._show_down_text.visible = show.visible;
			this._show_down_text.x_type = show.x_type;
			this._show_down_text.x_value = show.x_value;
			return;
		}
		value.text = this._show_down_text.text;
		value.visible = this._show_down_text.visible;
		value.x_type = this._show_down_text.x_type;
		value.x_value = this._show_down_text.x_value;
		this.RemoveChild(this._show_down_text);
		this._show_down_text = value;
		this._show_down_text.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this.AddChild(this._show_down_text, 6);
	},
	get show_down_text() {
		if (this._show_down_text._show === undefined) {
			return undefined;
		}
		return this._show_down_text;
	},
	set show_disabled_text(value) {
		if (value === undefined) {
			let show = this._show_disabled_text;
			this.RemoveChild(show);
			this._show_disabled_text = ({});
			this._show_disabled_text.width = 0;
			this._show_disabled_text.height = 0;
			this._show_disabled_text.text = show.text;
			this._show_disabled_text.visible = show.visible;
			this._show_disabled_text.x_type = show.x_type;
			this._show_disabled_text.x_value = show.x_value;
			return;
		}
		value.text = this._show_disabled_text.text;
		value.visible = this._show_disabled_text.visible;
		value.x_type = this._show_disabled_text.x_type;
		value.x_value = this._show_disabled_text.x_value;
		this.RemoveChild(this._show_disabled_text);
		this._show_disabled_text = value;
		this._show_disabled_text.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this.AddChild(this._show_disabled_text, 6);
	},
	get show_disabled_text() {
		if (this._show_disabled_text._show === undefined) {
			return undefined;
		}
		return this._show_disabled_text;
	},
	set show_up(value) {
		this.RemoveChild(this._show_up);
		this._show_up = value;
		if (this._show_up !== undefined) {
			this._show_up.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_up.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_up.width_value = 0;
			this._show_up.height_value = 0;
			this.AddChild(this._show_up, 1);
		}
		if (this._abs_disabled || this._disabled) {
			this.ShowDisabled();
		} else {
			this.ShowUp(undefined);
		}
	},
	get show_up() {
		return this._show_up;
	},
	set show_down(value) {
		this.RemoveChild(this._show_down);
		this._show_down = value;
		if (this._show_down !== undefined) {
			this._show_down.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_down.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_down.width_value = 0;
			this._show_down.height_value = 0;
			this.AddChild(this._show_down, 1);
		}
		if (this._abs_disabled || this._disabled) {
			this.ShowDisabled();
		} else {
			this.ShowUp(undefined);
		}
	},
	get show_down() {
		return this._show_down;
	},
	set show_over(value) {
		this.RemoveChild(this._show_over);
		this._show_over = value;
		if (this._show_over !== undefined) {
			this._show_over.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_over.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_over.width_value = 0;
			this._show_over.height_value = 0;
			this.AddChild(this._show_over, 1);
		}
		if (this._abs_disabled || this._disabled) {
			this.ShowDisabled();
		} else {
			this.ShowUp(undefined);
		}
	},
	get show_over() {
		return this._show_over;
	},
	set show_disabled(value) {
		this.RemoveChild(this._show_disabled);
		this._show_disabled = value;
		if (this._show_disabled !== undefined) {
			this._show_disabled.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_disabled.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_disabled.width_value = 0;
			this._show_disabled.height_value = 0;
			this.AddChild(this._show_disabled, 1);
		}
		if (this._abs_disabled || this._disabled) {
			this.ShowDisabled();
		} else {
			this.ShowUp(undefined);
		}
	},
	get show_disabled() {
		return this._show_disabled;
	},
	set file_select(value) {
		this._file_select = value;
	},
	get file_select() {
		return this._file_select;
	},
}, "ALittle.TextButton");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.TextCheckButton = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._show_text = ({});
		this._show_text.width = 0;
		this._show_text.height = 0;
		this._show_text.text = "";
		this._show_text.x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this._show_text.x_value = 0;
		this._show_text.visible = true;
		this._show_over_text = ({});
		this._show_over_text.width = 0;
		this._show_over_text.height = 0;
		this._show_over_text.text = "";
		this._show_over_text.x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this._show_over_text.x_value = 0;
		this._show_over_text.visible = false;
		this._show_down_text = ({});
		this._show_down_text.width = 0;
		this._show_down_text.height = 0;
		this._show_down_text.text = "";
		this._show_down_text.x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this._show_down_text.x_value = 0;
		this._show_down_text.visible = false;
		this._show_disabled_text = ({});
		this._show_disabled_text.width = 0;
		this._show_disabled_text.height = 0;
		this._show_disabled_text.text = "";
		this._show_disabled_text.x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this._show_disabled_text.x_value = 0;
		this._show_disabled_text.visible = false;
		this._show_selected_text = ({});
		this._show_selected_text.width = 0;
		this._show_selected_text.height = 0;
		this._show_selected_text.text = "";
		this._show_selected_text.x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this._show_selected_text.x_value = 0;
		this._show_selected_text.visible = false;
		this._show_selected_over_text = ({});
		this._show_selected_over_text.width = 0;
		this._show_selected_over_text.height = 0;
		this._show_selected_over_text.text = "";
		this._show_selected_over_text.x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this._show_selected_over_text.x_value = 0;
		this._show_selected_over_text.visible = false;
		this._show_selected_down_text = ({});
		this._show_selected_down_text.width = 0;
		this._show_selected_down_text.height = 0;
		this._show_selected_down_text.text = "";
		this._show_selected_down_text.x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this._show_selected_down_text.x_value = 0;
		this._show_selected_down_text.visible = false;
		this._show_selected_disabled_text = ({});
		this._show_selected_disabled_text.width = 0;
		this._show_selected_disabled_text.height = 0;
		this._show_selected_disabled_text.text = "";
		this._show_selected_disabled_text.x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this._show_selected_disabled_text.x_value = 0;
		this._show_selected_disabled_text.visible = false;
		this._selected = false;
		this.AddEventListener(___all_struct.get(544684311), this, this.HandleMoveIn);
		this.AddEventListener(___all_struct.get(-1202439334), this, this.HandleMoveOut);
		this.AddEventListener(___all_struct.get(1883782801), this, this.HandleLButtonDown);
		this.AddEventListener(___all_struct.get(40651933), this, this.HandleLButtonUp);
		this.AddEventListener(___all_struct.get(349963892), this, this.HandleMButtonDown);
		this.AddEventListener(___all_struct.get(683647260), this, this.HandleMButtonUp);
		this._pickup_rect = true;
		this._pickup_child = false;
	},
	set disabled(value) {
		ALittle.DisplayObject.__setter.disabled.call(this, value);
		if (this._abs_disabled) {
			this.ShowDisabled();
		} else {
			this.ShowUp();
		}
	},
	HandleMoveIn : function(event) {
		this.ShowOver();
	},
	HandleMoveOut : function(event) {
		this.ShowUp();
	},
	HandleLButtonDown : function(event) {
		this.ShowDown();
	},
	HandleLButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			this._selected = (this._selected === false);
			let e = {};
			e.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(-449066808), e);
			this.DispatchEvent(___all_struct.get(958494922), {});
			if (ALittle.System_IsPhone === false) {
				this.ShowOver();
			} else {
				this.ShowUp();
			}
		} else {
			this.ShowUp();
		}
	},
	HandleMButtonDown : function(event) {
		this.ShowDown();
	},
	HandleMButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let e = {};
			e.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(-1330840), e);
			if (ALittle.System_IsPhone === false) {
				this.ShowOver();
			} else {
				this.ShowUp();
			}
		} else {
			this.ShowUp();
		}
	},
	set text(value) {
		this._show_text.text = value;
		this._show_over_text.text = value;
		this._show_down_text.text = value;
		this._show_disabled_text.text = value;
		this._show_selected_text.text = value;
		this._show_selected_over_text.text = value;
		this._show_selected_down_text.text = value;
		this._show_selected_disabled_text.text = value;
	},
	get text() {
		return this._show_text.text;
	},
	set text_x_type(value) {
		this._show_text.x_type = value;
		this._show_over_text.x_type = value;
		this._show_down_text.x_type = value;
		this._show_disabled_text.x_type = value;
		this._show_selected_text.x_type = value;
		this._show_selected_over_text.x_type = value;
		this._show_selected_down_text.x_type = value;
		this._show_selected_disabled_text.x_type = value;
	},
	get text_x_type() {
		return this._show_text.x_type;
	},
	set text_x_value(value) {
		this._show_text.x_value = value;
		this._show_over_text.x_value = value;
		this._show_down_text.x_value = value;
		this._show_disabled_text.x_value = value;
		this._show_selected_text.x_value = value;
		this._show_selected_over_text.x_value = value;
		this._show_selected_down_text.x_value = value;
		this._show_selected_disabled_text.x_value = value;
	},
	get text_x_value() {
		return this._show_text.x_value;
	},
	set selected(value) {
		if (this._selected === value) {
			return;
		}
		this._selected = value;
		if (this._abs_disabled) {
			this.ShowDisabled();
		} else {
			this.ShowUp();
		}
	},
	get selected() {
		return this._selected;
	},
	HideAllShow : function() {
		if (this._show_selected_up !== undefined) {
			this._show_selected_up.alpha = 0;
		}
		if (this._show_selected_over !== undefined) {
			this._show_selected_over.alpha = 0;
		}
		if (this._show_selected_down !== undefined) {
			this._show_selected_down.alpha = 0;
		}
		if (this._show_selected_disabled !== undefined) {
			this._show_selected_disabled.alpha = 0;
		}
		if (this._show_up !== undefined) {
			this._show_up.alpha = 0;
		}
		if (this._show_over !== undefined) {
			this._show_over.alpha = 0;
		}
		if (this._show_down !== undefined) {
			this._show_down.alpha = 0;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 0;
		}
	},
	ShowUp : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		this.HideAllShow();
		if (this._selected) {
			if (this._show_selected_up !== undefined) {
				this._show_selected_up.alpha = 1;
			}
			if (this._show_up !== undefined) {
				this._show_up.alpha = 0;
			}
		} else {
			if (this._show_selected_up !== undefined) {
				this._show_selected_up.alpha = 0;
			}
			if (this._show_up !== undefined) {
				this._show_up.alpha = 1;
			}
		}
		if (this._selected) {
			this._show_text.visible = true;
			this._show_down_text.visible = false;
			this._show_over_text.visible = false;
			this._show_disabled_text.visible = false;
			if (this._show_selected_text._show !== undefined) {
				this._show_text.visible = false;
			}
			this._show_selected_text.visible = true;
			this._show_selected_down_text.visible = false;
			this._show_selected_over_text.visible = false;
			this._show_selected_disabled_text.visible = false;
		} else {
			this._show_text.visible = true;
			this._show_down_text.visible = false;
			this._show_over_text.visible = false;
			this._show_disabled_text.visible = false;
			this._show_selected_text.visible = false;
			this._show_selected_down_text.visible = false;
			this._show_selected_over_text.visible = false;
			this._show_selected_disabled_text.visible = false;
		}
	},
	ShowDown : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		this.HideAllShow();
		if (this._selected) {
			if (this._show_selected_down !== undefined) {
				this._show_selected_down.alpha = 1;
			}
			if (this._show_down !== undefined) {
				this._show_down.alpha = 0;
			}
		} else {
			if (this._show_selected_down !== undefined) {
				this._show_selected_down.alpha = 0;
			}
			if (this._show_down !== undefined) {
				this._show_down.alpha = 1;
			}
		}
		if (this._selected) {
			this._show_text.visible = true;
			this._show_down_text.visible = false;
			this._show_over_text.visible = false;
			this._show_disabled_text.visible = false;
			this._show_selected_text.visible = false;
			if (this._show_selected_down_text._show !== undefined) {
				this._show_text.visible = false;
			}
			this._show_selected_down_text.visible = true;
			this._show_selected_over_text.visible = false;
			this._show_selected_disabled_text.visible = false;
		} else {
			this._show_text.visible = true;
			if (this._show_down_text._show !== undefined) {
				this._show_text.visible = false;
			}
			this._show_down_text.visible = true;
			this._show_over_text.visible = false;
			this._show_disabled_text.visible = false;
			this._show_selected_text.visible = false;
			this._show_selected_down_text.visible = false;
			this._show_selected_over_text.visible = false;
			this._show_selected_disabled_text.visible = false;
		}
	},
	ShowOver : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		this.HideAllShow();
		if (this._selected) {
			if (this._show_selected_over !== undefined) {
				this._show_selected_over.alpha = 1;
			}
			if (this._show_over !== undefined) {
				this._show_over.alpha = 0;
			}
		} else {
			if (this._show_selected_over !== undefined) {
				this._show_selected_over.alpha = 0;
			}
			if (this._show_over !== undefined) {
				this._show_over.alpha = 1;
			}
		}
		if (this._selected) {
			this._show_text.visible = true;
			this._show_down_text.visible = false;
			this._show_over_text.visible = false;
			this._show_disabled_text.visible = false;
			this._show_selected_text.visible = false;
			this._show_selected_down_text.visible = false;
			if (this._show_selected_over_text._show !== undefined) {
				this._show_text.visible = false;
			}
			this._show_selected_over_text.visible = true;
			this._show_selected_disabled_text.visible = false;
		} else {
			this._show_text.visible = true;
			this._show_down_text.visible = false;
			if (this._show_over_text._show !== undefined) {
				this._show_text.visible = false;
			}
			this._show_over_text.visible = true;
			this._show_disabled_text.visible = false;
			this._show_selected_text.visible = false;
			this._show_selected_down_text.visible = false;
			this._show_selected_over_text.visible = false;
			this._show_selected_disabled_text.visible = false;
		}
	},
	ShowDisabled : function() {
		this.HideAllShow();
		if (this._selected) {
			if (this._show_selected_disabled !== undefined) {
				this._show_selected_disabled.alpha = 1;
			}
			if (this._show_disabled !== undefined) {
				this._show_disabled.alpha = 0;
			}
		} else {
			if (this._show_selected_disabled !== undefined) {
				this._show_selected_disabled.alpha = 0;
			}
			if (this._show_disabled !== undefined) {
				this._show_disabled.alpha = 1;
			}
		}
		if (this._selected) {
			this._show_text.visible = true;
			this._show_down_text.visible = false;
			this._show_over_text.visible = false;
			this._show_disabled_text.visible = false;
			this._show_selected_text.visible = false;
			this._show_selected_down_text.visible = false;
			this._show_selected_over_text.visible = false;
			if (this._show_selected_disabled_text._show !== undefined) {
				this._show_text.visible = false;
			}
			this._show_selected_disabled_text.visible = true;
		} else {
			this._show_text.visible = true;
			this._show_down_text.visible = false;
			this._show_over_text.visible = false;
			if (this._show_disabled_text._show !== undefined) {
				this._show_text.visible = false;
			}
			this._show_disabled_text.visible = true;
			this._show_selected_text.visible = false;
			this._show_selected_down_text.visible = false;
			this._show_selected_over_text.visible = false;
			this._show_selected_disabled_text.visible = false;
		}
	},
	set show_text(value) {
		if (value === undefined) {
			let show = this._show_text;
			this.RemoveChild(show);
			this._show_text = ({});
			this._show_text.width = 0;
			this._show_text.height = 0;
			this._show_text.text = show.text;
			this._show_text.visible = show.visible;
			this._show_text.x_type = show.x_type;
			this._show_text.x_value = show.x_value;
			return;
		}
		if (this._show_text !== undefined && this._show_text.text !== "") {
			value.text = this._show_text.text;
		}
		value.visible = this._show_text.visible;
		value.x_type = this._show_text.x_type;
		value.x_value = this._show_text.x_value;
		this.RemoveChild(this._show_text);
		this._show_text = value;
		this._show_text.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this.AddChild(this._show_text, 10);
	},
	get show_text() {
		if (this._show_text._show === undefined) {
			return undefined;
		}
		return this._show_text;
	},
	set show_over_text(value) {
		if (value === undefined) {
			let show = this._show_over_text;
			this.RemoveChild(show);
			this._show_over_text = ({});
			this._show_over_text.width = 0;
			this._show_over_text.height = 0;
			this._show_over_text.text = show.text;
			this._show_over_text.visible = show.visible;
			this._show_over_text.x_type = show.x_type;
			this._show_over_text.x_value = show.x_value;
			return;
		}
		if (this._show_over_text !== undefined && this._show_over_text.text !== "") {
			value.text = this._show_over_text.text;
		}
		value.visible = this._show_over_text.visible;
		value.x_type = this._show_over_text.x_type;
		value.x_value = this._show_over_text.x_value;
		this.RemoveChild(this._show_over_text);
		this._show_over_text = value;
		this._show_over_text.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this.AddChild(this._show_over_text, 10);
	},
	get show_over_text() {
		if (this._show_over_text._show === undefined) {
			return undefined;
		}
		return this._show_over_text;
	},
	set show_down_text(value) {
		if (value === undefined) {
			let show = this._show_down_text;
			this.RemoveChild(show);
			this._show_down_text = ({});
			this._show_down_text.width = 0;
			this._show_down_text.height = 0;
			this._show_down_text.text = show.text;
			this._show_down_text.visible = show.visible;
			this._show_down_text.x_type = show.x_type;
			this._show_down_text.x_value = show.x_value;
			return;
		}
		if (this._show_down_text !== undefined && this._show_down_text.text !== "") {
			value.text = this._show_down_text.text;
		}
		value.visible = this._show_down_text.visible;
		value.x_type = this._show_down_text.x_type;
		value.x_value = this._show_down_text.x_value;
		this.RemoveChild(this._show_down_text);
		this._show_down_text = value;
		this._show_down_text.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this.AddChild(this._show_down_text, 10);
	},
	get show_down_text() {
		if (this._show_down_text._show === undefined) {
			return undefined;
		}
		return this._show_down_text;
	},
	set show_disabled_text(value) {
		if (value === undefined) {
			let show = this._show_disabled_text;
			this.RemoveChild(show);
			this._show_disabled_text = ({});
			this._show_disabled_text.width = 0;
			this._show_disabled_text.height = 0;
			this._show_disabled_text.text = show.text;
			this._show_disabled_text.visible = show.visible;
			this._show_disabled_text.x_type = show.x_type;
			this._show_disabled_text.x_value = show.x_value;
			return;
		}
		if (this._show_disabled_text !== undefined && this._show_disabled_text.text !== "") {
			value.text = this._show_disabled_text.text;
		}
		value.visible = this._show_disabled_text.visible;
		value.x_type = this._show_disabled_text.x_type;
		value.x_value = this._show_disabled_text.x_value;
		this.RemoveChild(this._show_disabled_text);
		this._show_disabled_text = value;
		this._show_disabled_text.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this.AddChild(this._show_disabled_text, 10);
	},
	get show_disabled_text() {
		if (this._show_disabled_text._show === undefined) {
			return undefined;
		}
		return this._show_disabled_text;
	},
	set show_selected_text(value) {
		if (value === undefined) {
			let show = this._show_selected_text;
			this.RemoveChild(show);
			this._show_selected_text = ({});
			this._show_selected_text.width = 0;
			this._show_selected_text.height = 0;
			this._show_selected_text.text = show.text;
			this._show_selected_text.visible = show.visible;
			this._show_selected_text.x_type = show.x_type;
			this._show_selected_text.x_value = show.x_value;
			return;
		}
		if (this._show_selected_text !== undefined && this._show_selected_text.text !== "") {
			value.text = this._show_selected_text.text;
		}
		value.visible = this._show_selected_text.visible;
		value.x_type = this._show_selected_text.x_type;
		value.x_value = this._show_selected_text.x_value;
		this.RemoveChild(this._show_selected_text);
		this._show_selected_text = value;
		this._show_selected_text.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this.AddChild(this._show_selected_text, 10);
	},
	get show_selected_text() {
		if (this._show_selected_text._show === undefined) {
			return undefined;
		}
		return this._show_selected_text;
	},
	set show_selected_over_text(value) {
		if (value === undefined) {
			let show = this._show_selected_over_text;
			this.RemoveChild(show);
			this._show_selected_over_text = ({});
			this._show_selected_over_text.width = 0;
			this._show_selected_over_text.height = 0;
			this._show_selected_over_text.text = show.text;
			this._show_selected_over_text.visible = show.visible;
			this._show_selected_over_text.x_type = show.x_type;
			this._show_selected_over_text.x_value = show.x_value;
			return;
		}
		if (this._show_selected_over_text !== undefined && this._show_selected_over_text.text !== "") {
			value.text = this._show_selected_over_text.text;
		}
		value.visible = this._show_selected_over_text.visible;
		value.x_type = this._show_selected_over_text.x_type;
		value.x_value = this._show_selected_over_text.x_value;
		this.RemoveChild(this._show_selected_over_text);
		this._show_selected_over_text = value;
		this._show_selected_over_text.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this.AddChild(this._show_selected_over_text, 10);
	},
	get show_selected_over_text() {
		if (this._show_selected_over_text._show === undefined) {
			return undefined;
		}
		return this._show_selected_over_text;
	},
	set show_selected_down_text(value) {
		if (value === undefined) {
			let show = this._show_selected_down_text;
			this.RemoveChild(show);
			this._show_selected_down_text = ({});
			this._show_selected_down_text.width = 0;
			this._show_selected_down_text.height = 0;
			this._show_selected_down_text.text = show.text;
			this._show_selected_down_text.visible = show.visible;
			this._show_selected_down_text.x_type = show.x_type;
			this._show_selected_down_text.x_value = show.x_value;
			return;
		}
		if (this._show_selected_down_text !== undefined && this._show_selected_down_text.text !== "") {
			value.text = this._show_selected_down_text.text;
		}
		value.visible = this._show_selected_down_text.visible;
		value.x_type = this._show_selected_down_text.x_type;
		value.x_value = this._show_selected_down_text.x_value;
		this.RemoveChild(this._show_selected_down_text);
		this._show_selected_down_text = value;
		this._show_selected_down_text.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this.AddChild(this._show_selected_down_text, 10);
	},
	get show_selected_down_text() {
		if (this._show_selected_down_text._show === undefined) {
			return undefined;
		}
		return this._show_selected_down_text;
	},
	set show_selected_disabled_text(value) {
		if (value === undefined) {
			let show = this._show_selected_disabled_text;
			this.RemoveChild(show);
			this._show_selected_disabled_text = ({});
			this._show_selected_disabled_text.width = 0;
			this._show_selected_disabled_text.height = 0;
			this._show_selected_disabled_text.text = show.text;
			this._show_selected_disabled_text.visible = show.visible;
			this._show_selected_disabled_text.x_type = show.x_type;
			this._show_selected_disabled_text.x_value = show.x_value;
			return;
		}
		if (this._show_selected_disabled_text !== undefined && this._show_selected_disabled_text.text !== "") {
			value.text = this._show_selected_disabled_text.text;
		}
		value.visible = this._show_selected_disabled_text.visible;
		value.x_type = this._show_selected_disabled_text.x_type;
		value.x_value = this._show_selected_disabled_text.x_value;
		this.RemoveChild(this._show_selected_disabled_text);
		this._show_selected_disabled_text = value;
		this._show_selected_disabled_text.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this.AddChild(this._show_selected_disabled_text, 10);
	},
	get show_selected_disabled_text() {
		if (this._show_selected_disabled_text._show === undefined) {
			return undefined;
		}
		return this._show_selected_disabled_text;
	},
	set show_up(value) {
		this.RemoveChild(this._show_up);
		this._show_up = value;
		if (this._show_up !== undefined) {
			this._show_up.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_up.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_up.width_value = 0;
			this._show_up.height_value = 0;
			this.AddChild(this._show_up, 1);
		}
		this.ShowUp();
	},
	get show_up() {
		return this._show_up;
	},
	set show_down(value) {
		this.RemoveChild(this._show_down);
		this._show_down = value;
		if (this._show_down !== undefined) {
			this._show_down.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_down.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_down.width_value = 0;
			this._show_down.height_value = 0;
			this.AddChild(this._show_down, 1);
		}
		this.ShowUp();
	},
	get show_down() {
		return this._show_down;
	},
	set show_over(value) {
		this.RemoveChild(this._show_over);
		this._show_over = value;
		if (this._show_over !== undefined) {
			this._show_over.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_over.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_over.width_value = 0;
			this._show_over.height_value = 0;
			this.AddChild(this._show_over, 1);
		}
		this.ShowUp();
	},
	get show_over() {
		return this._show_over;
	},
	set show_disabled(value) {
		this.RemoveChild(this._show_disabled);
		this._show_disabled = value;
		if (this._show_disabled !== undefined) {
			this._show_disabled.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_disabled.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_disabled.width_value = 0;
			this._show_disabled.height_value = 0;
			this.AddChild(this._show_disabled, 1);
		}
		this.ShowUp();
	},
	get show_disabled() {
		return this._show_disabled;
	},
	set show_selected_up(value) {
		this.RemoveChild(this._show_selected_up);
		this._show_selected_up = value;
		if (this._show_selected_up !== undefined) {
			this._show_selected_up.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_selected_up.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_selected_up.width_value = 0;
			this._show_selected_up.height_value = 0;
			this.AddChild(this._show_selected_up, 1);
		}
		this.ShowUp();
	},
	get show_selected_up() {
		return this._show_selected_up;
	},
	set show_selected_down(value) {
		this.RemoveChild(this._show_selected_down);
		this._show_selected_down = value;
		if (this._show_selected_down !== undefined) {
			this._show_selected_down.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_selected_down.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_selected_down.width_value = 0;
			this._show_selected_down.height_value = 0;
			this.AddChild(this._show_selected_down, 1);
		}
		this.ShowUp();
	},
	get show_selected_down() {
		return this._show_selected_down;
	},
	set show_selected_over(value) {
		this.RemoveChild(this._show_selected_over);
		this._show_selected_over = value;
		if (this._show_selected_over !== undefined) {
			this._show_selected_over.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_selected_over.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_selected_over.width_value = 0;
			this._show_selected_over.height_value = 0;
			this.AddChild(this._show_selected_over, 1);
		}
		this.ShowUp();
	},
	get show_selected_over() {
		return this._show_selected_over;
	},
	set show_selected_disabled(value) {
		this.RemoveChild(this._show_selected_disabled);
		this._show_selected_disabled = value;
		if (this._show_selected_disabled !== undefined) {
			this._show_selected_disabled.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_selected_disabled.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_selected_disabled.width_value = 0;
			this._show_selected_disabled.height_value = 0;
			this.AddChild(this._show_selected_disabled, 1);
		}
		this.ShowUp();
	},
	get show_selected_disabled() {
		return this._show_selected_disabled;
	},
}, "ALittle.TextCheckButton");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.TextCheckButton === undefined) throw new Error(" extends class:ALittle.TextCheckButton is undefined");
ALittle.TextRadioButton = JavaScript.Class(ALittle.TextCheckButton, {
	Ctor : function(ctrl_sys) {
	},
	set group(group) {
		if (this._group === group) {
			return;
		}
		if (this._group !== undefined) {
			this._group.delete(this);
		}
		this._group = group;
		if (this._group !== undefined) {
			this._group.set(this, true);
		}
	},
	get group() {
		return this._group;
	},
	SetGroup : function(list) {
		let group = ALittle.CreateKeyWeakMap();
		let ___OBJECT_1 = list;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let button = ___OBJECT_1[index - 1];
			if (button === undefined) break;
			if (button._group !== undefined) {
				button._group.delete(button);
			}
			button._group = group;
			group.set(button, true);
		}
	},
	HandleLButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			if (this._selected === false) {
				this._selected = true;
				if (this._group !== undefined) {
					for (let [k, _] of this._group) {
						if (_ === undefined) continue;
						if (k !== this && k._selected === true) {
							k._selected = false;
							k.ShowUp();
							k.DispatchEvent(___all_struct.get(958494922), {});
						}
					}
				}
				this.DispatchEvent(___all_struct.get(958494922), {});
			}
			let e = {};
			e.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(-449066808), e);
			if (ALittle.System_IsPhone === false) {
				this.ShowOver();
			} else {
				this.ShowUp();
			}
		} else {
			this.ShowUp();
		}
	},
	set selected(value) {
		if (this._selected === value) {
			return;
		}
		this._selected = value;
		if (this._abs_disabled) {
			this.ShowDisabled();
		} else {
			this.ShowUp();
		}
		if (this._selected === false) {
			return;
		}
		if (this._group !== undefined) {
			for (let [k, _] of this._group) {
				if (_ === undefined) continue;
				if (k !== this && k._selected === true) {
					k._selected = false;
					k.ShowUp();
				}
			}
		}
	},
}, "ALittle.TextRadioButton");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.DisplayGroup === undefined) throw new Error(" extends class:ALittle.DisplayGroup is undefined");
ALittle.Grid3 = JavaScript.Class(ALittle.DisplayGroup, {
	Ctor : function(ctrl_sys) {
		this._type = ALittle.UIEnumTypes.TYPE_V;
		this._child_map = [];
		this._logic_up = 0;
		this._logic_down = 0;
		this._logic_gap = 0;
		this._real_up = 0;
		this._real_down = 0;
		this._real_gap = 0;
		this._pickup_rect = true;
		this._pickup_child = true;
	},
	set type(value) {
		if (this._type === value) {
			return;
		}
		this._type = value;
		this.CalcRealWidthCutting();
		this.CalcRealHeightCutting();
	},
	get type() {
		return this._type;
	},
	set show_up(child) {
		this.SetShow(1, child);
	},
	get show_up() {
		return this._child_map[1 - 1];
	},
	set show_center(child) {
		this.SetShow(2, child);
	},
	get show_center() {
		return this._child_map[2 - 1];
	},
	set show_down(child) {
		this.SetShow(3, child);
	},
	get show_down() {
		return this._child_map[3 - 1];
	},
	SetShow : function(index, child) {
		if (this._child_map[index - 1] !== undefined) {
			ALittle.DisplayGroup.RemoveChild.call(this, this._child_map[index - 1]);
		}
		this._child_map[index - 1] = undefined;
		if (child === undefined) {
			return;
		}
		this._child_map[index - 1] = child;
		ALittle.DisplayGroup.AddChild.call(this, child);
		if (this._type === ALittle.UIEnumTypes.TYPE_V) {
			child.x = 0;
			child.width = this._width;
			let y = 0.0;
			let height = 0.0;
			if (index === 1) {
				y = 0;
				height = this._real_up;
			} else if (index === 2) {
				y = this._real_up + this._real_gap;
				height = this._height - this._real_gap * 2 - this._real_up - this._real_down;
			} else if (index === 3) {
				y = this._height - this._real_down;
				height = this._real_down;
			}
			child.y = y;
			child.height = height;
		} else {
			child.y = 0;
			child.height = this._height;
			let x = 0.0;
			let width = 0.0;
			if (index === 1) {
				x = 0;
				width = this._real_up;
			} else if (index === 2) {
				x = this._real_up + this._real_gap;
				width = this._width - this._real_gap * 2 - this._real_up - this._real_down;
			} else if (index === 3) {
				x = this._width - this._real_down;
				width = this._real_down;
			}
			child.x = x;
			child.width = width;
		}
	},
	get center_size() {
		let size = 0.0;
		if (this._type === ALittle.UIEnumTypes.TYPE_V) {
			size = this._height - this._real_gap * 2 - this._real_up - this._real_down;
		} else {
			size = this._width - this._real_gap * 2 - this._real_up - this._real_down;
		}
		return size;
	},
	get real_gap() {
		return this._real_gap;
	},
	get gap() {
		return this._logic_gap;
	},
	get real_up_size() {
		return this._real_up;
	},
	get up_size() {
		return this._logic_up;
	},
	get real_down_size() {
		return this._real_down;
	},
	get down_size() {
		return this._logic_down;
	},
	set up_size(value) {
		this._logic_up = value;
		this.CalcRealWidthCutting();
		this.CalcRealHeightCutting();
	},
	set down_size(value) {
		this._logic_down = value;
		this.CalcRealWidthCutting();
		this.CalcRealHeightCutting();
	},
	set gap(value) {
		this._logic_gap = value;
		this.CalcRealWidthCutting();
		this.CalcRealHeightCutting();
	},
	set width(value) {
		if (value === this._width) {
			return;
		}
		this._width = value;
		if (this._width_type === ALittle.UIEnumTypes.SIZE_ABS) {
			this._width_value = this._width;
		}
		this.CalcRealWidthCutting();
	},
	set height(value) {
		if (value === this._height) {
			return;
		}
		this._height = value;
		if (this._height_type === ALittle.UIEnumTypes.SIZE_ABS) {
			this._height_value = this._height;
		}
		this.CalcRealHeightCutting();
	},
	CalcRealWidthCutting : function() {
		if (this._type === ALittle.UIEnumTypes.TYPE_V) {
			for (let index = 1; index <= 3; index += 1) {
				if (this._child_map[index - 1] !== undefined) {
					this._child_map[index - 1].x = 0;
					this._child_map[index - 1].width = this._width;
				}
			}
			return;
		}
		if (this._width === 0) {
			this._real_up = 0;
			this._real_down = 0;
			this._real_gap = 0;
		} else if (this._width >= this._logic_up + this._logic_down + this._logic_gap * 2) {
			this._real_up = this._logic_up;
			this._real_down = this._logic_down;
			this._real_gap = this._logic_gap;
		} else if (this._width >= this._logic_up + this._logic_down) {
			let last_gap = this._width - this._logic_up - this._logic_down;
			this._real_up = this._logic_up;
			this._real_down = this._logic_down;
			this._real_gap = last_gap / 2;
		} else {
			let logic_up_add_down = this._logic_up + this._logic_down;
			if (logic_up_add_down === 0) {
				this._real_up = 0;
				this._real_down = 0;
				this._real_gap = 0;
			} else {
				let rate_up = this._logic_up / logic_up_add_down;
				let rate_down = this._logic_down / logic_up_add_down;
				this._real_up = this._width * rate_up;
				this._real_down = this._width * rate_down;
				this._real_gap = 0;
			}
		}
		let offset_list = [];
		offset_list[1 - 1] = 0;
		offset_list[2 - 1] = this._real_up + this._real_gap;
		offset_list[3 - 1] = this._width - this._real_down;
		let width_list = [];
		width_list[1 - 1] = this._real_up;
		width_list[2 - 1] = this._width - this._real_gap * 2 - this._real_up - this._real_down;
		width_list[3 - 1] = this._real_down;
		for (let index = 1; index <= 3; index += 1) {
			if (this._child_map[index - 1] !== undefined) {
				this._child_map[index - 1].x = offset_list[index - 1];
				this._child_map[index - 1].width = width_list[index - 1];
			}
		}
	},
	CalcRealHeightCutting : function() {
		if (this._type === ALittle.UIEnumTypes.TYPE_H) {
			for (let index = 1; index <= 3; index += 1) {
				if (this._child_map[index - 1] !== undefined) {
					this._child_map[index - 1].y = 0;
					this._child_map[index - 1].height = this._height;
				}
			}
			return;
		}
		if (this._height === 0) {
			this._real_up = 0;
			this._real_down = 0;
			this._real_gap = 0;
		} else if (this._height >= this._logic_up + this._logic_down + this._logic_gap * 2) {
			this._real_up = this._logic_up;
			this._real_down = this._logic_down;
			this._real_gap = this._logic_gap;
		} else if (this._height >= this._logic_up + this._logic_down) {
			let last_gap = this._height - this._logic_up - this._logic_down;
			this._real_up = this._logic_up;
			this._real_down = this._logic_down;
			this._real_gap = last_gap / 2;
		} else {
			let logic_up_add_down = this._logic_up + this._logic_down;
			if (logic_up_add_down === 0) {
				this._real_up = 0;
				this._real_down = 0;
				this._real_gap = 0;
			} else {
				let rate_up = this._logic_up / logic_up_add_down;
				let rate_down = this._logic_down / logic_up_add_down;
				this._real_up = this._height * rate_up;
				this._real_down = this._height * rate_down;
				this._real_gap = 0;
			}
		}
		let offset_list = [];
		offset_list[1 - 1] = 0;
		offset_list[2 - 1] = this._real_up + this._real_gap;
		offset_list[3 - 1] = this._height - this._real_down;
		let height_list = [];
		height_list[1 - 1] = this._real_up;
		height_list[2 - 1] = this._height - this._real_gap * 2 - this._real_up - this._real_down;
		height_list[3 - 1] = this._real_down;
		for (let index = 1; index <= 3; index += 1) {
			if (this._child_map[index - 1] !== undefined) {
				this._child_map[index - 1].y = offset_list[index - 1];
				this._child_map[index - 1].height = height_list[index - 1];
			}
		}
	},
}, "ALittle.Grid3");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


let __ceil = ALittle.Math_Ceil;
if (ALittle.DisplayGroup === undefined) throw new Error(" extends class:ALittle.DisplayGroup is undefined");
ALittle.Grid9 = JavaScript.Class(ALittle.DisplayGroup, {
	Ctor : function(ctrl_sys) {
		this._child_map = new Map();
		this._child_map.set(1, new Map());
		this._child_map.set(2, new Map());
		this._child_map.set(3, new Map());
		this._logic_left = 0;
		this._logic_top = 0;
		this._logic_right = 0;
		this._logic_bottom = 0;
		this._real_left = 0;
		this._real_top = 0;
		this._real_right = 0;
		this._real_bottom = 0;
		this._pickup_rect = true;
		this._pickup_child = true;
	},
	set show_left_top(child) {
		this.SetShow(1, 1, child);
	},
	get show_left_top() {
		return this._child_map.get(1).get(1);
	},
	set show_left_center(child) {
		this.SetShow(1, 2, child);
	},
	get show_left_center() {
		return this._child_map.get(1).get(2);
	},
	set show_left_bottom(child) {
		this.SetShow(1, 3, child);
	},
	get show_left_bottom() {
		return this._child_map.get(1).get(3);
	},
	set show_center_top(child) {
		this.SetShow(2, 1, child);
	},
	get show_center_top() {
		return this._child_map.get(2).get(1);
	},
	set show_center_center(child) {
		this.SetShow(2, 2, child);
	},
	get show_center_center() {
		return this._child_map.get(2).get(2);
	},
	set show_center_bottom(child) {
		this.SetShow(2, 3, child);
	},
	get show_center_bottom() {
		return this._child_map.get(2).get(3);
	},
	set show_right_top(child) {
		this.SetShow(3, 1, child);
	},
	get show_right_top() {
		return this._child_map.get(3).get(1);
	},
	set show_right_center(child) {
		this.SetShow(3, 2, child);
	},
	get show_right_center() {
		return this._child_map.get(3).get(2);
	},
	set show_right_bottom(child) {
		this.SetShow(3, 3, child);
	},
	get show_right_bottom() {
		return this._child_map.get(3).get(3);
	},
	SetShow : function(col, row, child) {
		if (this._child_map.get(col).get(row) !== undefined) {
			this.RemoveChild(this._child_map.get(col).get(row));
		}
		this._child_map.get(col).set(row, child);
		if (child === undefined) {
			return;
		}
		this.AddChild(child);
		let x = 0.0;
		let y = 0.0;
		let width = 0.0;
		let height = 0.0;
		if (col === 1) {
			x = 0;
			width = this._real_left;
		} else if (col === 2) {
			x = this._real_left;
			width = this._width - this._real_left - this._real_right;
		} else if (col === 3) {
			x = this._width - this._real_right;
			width = this._real_right;
		}
		if (row === 1) {
			y = 0;
			height = this._real_top;
		} else if (row === 2) {
			y = this._real_top;
			height = this._height - this._real_top - this._real_bottom;
		} else if (row === 3) {
			y = this._height - this._real_bottom;
			height = this._real_bottom;
		}
		child.x = x;
		child.y = y;
		child.width = width;
		child.height = height;
	},
	set width(value) {
		if (value === this._width) {
			return;
		}
		this._width = value;
		if (this._width_type === ALittle.UIEnumTypes.SIZE_ABS) {
			this._width_value = this._width;
		}
		this.CalcRealWidthCutting();
	},
	set height(value) {
		if (value === this._height) {
			return;
		}
		this._height = value;
		if (this._height_type === ALittle.UIEnumTypes.SIZE_ABS) {
			this._height_value = this._height;
		}
		this.CalcRealHeightCutting();
	},
	set left_size(value) {
		this._logic_left = value;
		this.CalcRealWidthCutting();
	},
	get left_size() {
		return this._logic_left;
	},
	set right_size(value) {
		this._logic_right = value;
		this.CalcRealWidthCutting();
	},
	get right_size() {
		return this._logic_right;
	},
	set top_size(value) {
		this._logic_top = value;
		this.CalcRealHeightCutting();
	},
	get top_size() {
		return this._logic_top;
	},
	set bottom_size(value) {
		this._logic_bottom = value;
		this.CalcRealHeightCutting();
	},
	get bottom_size() {
		return this._logic_bottom;
	},
	CalcRealWidthCutting : function() {
		let real_center = 0.0;
		let logic_left = __ceil(this._logic_left);
		let logic_right = __ceil(this._logic_right);
		if (this._width === 0) {
			this._real_left = 0;
			this._real_right = 0;
			real_center = 0;
		} else if (this._width >= logic_left + logic_right) {
			this._real_left = logic_left;
			this._real_right = logic_right;
			real_center = __ceil(this._width - this._real_left - this._real_right);
		} else {
			let logic_left_add_right = this._logic_left + this._logic_right;
			real_center = 0;
			if (logic_left_add_right === 0) {
				this._real_left = 0;
				this._real_right = 0;
			} else {
				let rate_left = this._logic_left / logic_left_add_right;
				let rate_right = this._logic_right / logic_left_add_right;
				this._real_left = this._width * rate_left;
				this._real_right = this._width * rate_right;
			}
		}
		let offset_list = [];
		offset_list[1 - 1] = 0;
		offset_list[2 - 1] = this._real_left;
		offset_list[3 - 1] = this._real_left + real_center;
		let width_list = [];
		width_list[1 - 1] = this._real_left;
		width_list[2 - 1] = real_center;
		width_list[3 - 1] = this._real_right;
		for (let col = 1; col <= 3; col += 1) {
			let row_childs = this._child_map.get(col);
			for (let row = 1; row <= 3; row += 1) {
				if (row_childs.get(row) !== undefined) {
					row_childs.get(row).x = offset_list[col - 1];
					row_childs.get(row).width = width_list[col - 1];
				}
			}
		}
	},
	CalcRealHeightCutting : function() {
		let real_center = 0.0;
		let logic_top = __ceil(this._logic_top);
		let logic_bottom = __ceil(this._logic_bottom);
		if (this._height === 0) {
			this._real_top = 0;
			this._real_bottom = 0;
			real_center = 0;
		} else if (this._height >= logic_top + logic_bottom) {
			this._real_top = logic_top;
			this._real_bottom = logic_bottom;
			real_center = __ceil(this._height - this._real_top - this._real_bottom);
		} else {
			let logic_top_add_bottom = this._logic_top + this._logic_bottom;
			real_center = 0;
			if (logic_top_add_bottom === 0) {
				this._real_top = 0;
				this._real_bottom = 0;
			} else {
				let rate_top = this._logic_top / logic_top_add_bottom;
				let rate_bottom = this._logic_bottom / logic_top_add_bottom;
				this._real_top = this._height * rate_top;
				this._real_bottom = this._height * rate_bottom;
			}
		}
		let offset_list = [];
		offset_list[1 - 1] = 0;
		offset_list[2 - 1] = this._real_top;
		offset_list[3 - 1] = this._real_top + real_center;
		let height_list = [];
		height_list[1 - 1] = this._real_top;
		height_list[2 - 1] = real_center;
		height_list[3 - 1] = this._real_bottom;
		for (let col = 1; col <= 3; col += 1) {
			let row_childs = this._child_map.get(col);
			for (let row = 1; row <= 3; row += 1) {
				if (row_childs.get(row) !== undefined) {
					row_childs.get(row).y = offset_list[row - 1];
					row_childs.get(row).height = height_list[row - 1];
				}
			}
		}
	},
}, "ALittle.Grid9");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


let __ceil = ALittle.Math_Ceil;
if (ALittle.DisplayGroup === undefined) throw new Error(" extends class:ALittle.DisplayGroup is undefined");
ALittle.Linear = JavaScript.Class(ALittle.DisplayGroup, {
	Ctor : function(ctrl_sys) {
		this._type = ALittle.UIEnumTypes.TYPE_H;
		this._size_fixed = true;
		this._gap = 0;
		this._clip_up_index = 0;
		this._clip_down_index = 0;
		this._child_width_map = ALittle.CreateKeyWeakMap();
		this._child_height_map = ALittle.CreateKeyWeakMap();
		this._show_child_map = ALittle.CreateKeyWeakMap();
		this._pickup_rect = false;
		this._pickup_child = true;
	},
	get clip_up_index() {
		return this._clip_up_index;
	},
	get clip_down_index() {
		return this._clip_down_index;
	},
	get size_fixed() {
		return this._size_fixed;
	},
	set size_fixed(value) {
		if (this._size_fixed === value) {
			return;
		}
		this._size_fixed = value;
		this.UpdateSize();
	},
	set type(value) {
		if (this._type === value) {
			return;
		}
		this._type = value;
		this.UpdateSize();
		this.Layout(1);
	},
	get type() {
		return this._type;
	},
	set gap(value) {
		if (this._gap === value) {
			return;
		}
		this._gap = value;
		this.Layout(1);
	},
	get gap() {
		return this._gap;
	},
	AddChild : function(child, index) {
		if (ALittle.DisplayGroup.AddChild.call(this, child, index) === false) {
			return false;
		}
		if (index === undefined) {
			this.Layout(this.child_count);
		} else {
			this.Layout(index);
		}
		this._child_width_map.set(child, child.width);
		this._child_height_map.set(child, child.height);
		if (this._size_fixed) {
			if (this._type === ALittle.UIEnumTypes.TYPE_H) {
				child.height = this._height;
			} else {
				child.width = this._width;
			}
		}
		child.AddEventListener(___all_struct.get(-431205740), this, this.HandleChildResize);
		return true;
	},
	RemoveChild : function(child) {
		let child_index = this.GetChildIndex(child);
		if (child_index === 0) {
			return false;
		}
		if (ALittle.DisplayGroup.RemoveChild.call(this, child) === false) {
			return false;
		}
		this._child_width_map.delete(child);
		this._child_height_map.delete(child);
		this._show_child_map.delete(child);
		child.RemoveEventListener(___all_struct.get(-431205740), this);
		this.Layout(child_index);
		return true;
	},
	RemoveAllChild : function() {
		let ___OBJECT_1 = this._childs;
		for (let i = 1; i <= ___OBJECT_1.length; ++i) {
			let child = ___OBJECT_1[i - 1];
			if (child === undefined) break;
			child.RemoveEventListener(___all_struct.get(-431205740), this);
		}
		this._child_width_map = ALittle.CreateKeyWeakMap();
		this._child_height_map = ALittle.CreateKeyWeakMap();
		this._show_child_map = ALittle.CreateKeyWeakMap();
		this._clip_up_index = 0;
		this._clip_down_index = 0;
		ALittle.DisplayGroup.RemoveAllChild.call(this);
	},
	SetChildIndex : function(child, index) {
		ALittle.DisplayGroup.SetChildIndex.call(this, child, index);
		this.Layout(1);
		return true;
	},
	set width(value) {
		this._width = value;
		if (this._width_type === ALittle.UIEnumTypes.SIZE_ABS) {
			this._width_value = this._width;
		}
		if (this._type !== ALittle.UIEnumTypes.TYPE_H && this._size_fixed) {
			let ___OBJECT_2 = this._childs;
			for (let index = 1; index <= ___OBJECT_2.length; ++index) {
				let child = ___OBJECT_2[index - 1];
				if (child === undefined) break;
				child.width = value;
			}
		}
	},
	get width() {
		if (this._size_fixed) {
			if (this._type === ALittle.UIEnumTypes.TYPE_H) {
				if (this._child_count === 0) {
					return 0;
				}
				let child = this._childs[this._child_count - 1];
				return child.x + child.width;
			}
			return this._width;
		}
		return ALittle.DisplayGroup.__getter.max_right.call(this);
	},
	set height(value) {
		this._height = value;
		if (this._height_type === ALittle.UIEnumTypes.SIZE_ABS) {
			this._height_value = this._height;
		}
		if (this._type !== ALittle.UIEnumTypes.TYPE_V && this._size_fixed) {
			let ___OBJECT_3 = this._childs;
			for (let index = 1; index <= ___OBJECT_3.length; ++index) {
				let child = ___OBJECT_3[index - 1];
				if (child === undefined) break;
				child.height = value;
			}
		}
	},
	get height() {
		if (this._size_fixed) {
			if (this._type === ALittle.UIEnumTypes.TYPE_V) {
				if (this._child_count === 0) {
					return 0;
				}
				let child = this._childs[this._child_count - 1];
				return child.y + child.height;
			}
			return this._height;
		}
		return ALittle.DisplayGroup.__getter.max_bottom.call(this);
	},
	UpdateSize : function() {
		if (this._size_fixed) {
			if (this._type === ALittle.UIEnumTypes.TYPE_H) {
				for (let [k, v] of this._child_width_map) {
					if (v === undefined) continue;
					k.width = v;
					k.height = this._height;
				}
			} else {
				for (let [k, v] of this._child_height_map) {
					if (v === undefined) continue;
					k.width = this._width;
					k.height = v;
				}
			}
		} else {
			for (let [k, v] of this._child_width_map) {
				if (v === undefined) continue;
				k.width = v;
			}
			for (let [k, v] of this._child_height_map) {
				if (v === undefined) continue;
				k.height = v;
			}
		}
	},
	Layout : function(index) {
		this._clip_up_index = 0;
		this._clip_down_index = 0;
		let child_count = this.child_count;
		if (index > child_count) {
			return;
		}
		if (this._type === ALittle.UIEnumTypes.TYPE_H) {
			let offset = 0.0;
			if (index > 1) {
				offset = this._childs[index - 1 - 1].x + this._childs[index - 1 - 1].width + this._gap;
			}
			for (let i = index; i <= child_count; i += 1) {
				this._childs[i - 1].x = offset;
				this._childs[i - 1].y = 0;
				offset = offset + this._childs[i - 1].width + this._gap;
			}
		} else {
			let offset = 0.0;
			if (index > 1) {
				offset = this._childs[index - 1 - 1].y + this._childs[index - 1 - 1].height + this._gap;
			}
			for (let i = index; i <= child_count; i += 1) {
				this._childs[i - 1].y = offset;
				this._childs[i - 1].x = 0;
				offset = offset + this._childs[i - 1].height + this._gap;
			}
		}
	},
	DeepLayout : function() {
		this._clip_up_index = 0;
		this._clip_down_index = 0;
		let child_count = this.child_count;
		if (child_count === 0) {
			return;
		}
		if (this._type === ALittle.UIEnumTypes.TYPE_H) {
			let offset = 0.0;
			for (let i = 1; i <= child_count; i += 1) {
				let child = this._childs[i - 1];
				if (child.DeepLayout !== undefined) {
					child.DeepLayout();
				}
				child.x = offset;
				child.y = 0;
				offset = offset + child.width + this._gap;
			}
		} else {
			let offset = 0.0;
			for (let i = 1; i <= child_count; i += 1) {
				let child = this._childs[i - 1];
				if (child.DeepLayout !== undefined) {
					child.DeepLayout();
				}
				child.y = offset;
				child.x = 0;
				offset = offset + child.height + this._gap;
			}
		}
	},
	HandleChildResize : function(event) {
		this.Layout(this.GetChildIndex(event.target));
		if (this._show_parent !== undefined) {
			if (this._type === ALittle.UIEnumTypes.TYPE_H) {
				this._show_parent.UpdateXLayout(this);
			} else {
				this._show_parent.UpdateYLayout(this);
			}
		}
		this.DispatchEvent(___all_struct.get(-431205740), {});
	},
	get max_right() {
		if (this._size_fixed) {
			return this.width;
		}
		return ALittle.DisplayGroup.__getter.max_right.call(this);
	},
	get max_bottom() {
		if (this._size_fixed) {
			return this.height;
		}
		return ALittle.DisplayGroup.__getter.max_bottom.call(this);
	},
	UpdateWidthLayout : function(child) {
		this.Layout(this.GetChildIndex(child));
	},
	UpdateHeightLayout : function(child) {
		this.Layout(this.GetChildIndex(child));
	},
	ClipRect : function(left, top, right, bottom, h_move, v_move) {
		left = left - this._x;
		if (left < 0) {
			left = 0;
		}
		top = top - (this._y);
		if (top < 0) {
			top = 0;
		}
		right = right - (this._x);
		if (right > this.width) {
			right = this.width;
		}
		bottom = bottom - (this._y);
		if (bottom > this.height) {
			bottom = this.height;
		}
		if (left >= right || top >= bottom) {
			this.clip = true;
			return;
		}
		this.clip = false;
		let child_count = this.child_count;
		if (child_count === 0) {
			return;
		}
		let childs = this.childs;
		let new_show_map = ALittle.CreateKeyWeakMap();
		this._show.RemoveAllChild();
		let max_index = child_count;
		let min_index = 1;
		let index = min_index;
		if (this._type === ALittle.UIEnumTypes.TYPE_H) {
			if (h_move === undefined || this._clip_up_index === 0) {
				do {
					if (childs[index - 1].x > left) {
						max_index = index;
						index = __ceil((max_index + min_index) / 2);
					} else if (childs[index - 1].x + childs[index - 1].width < left) {
						min_index = index;
						index = __ceil((max_index + min_index) / 2);
					} else {
						break;
					}
				} while (index !== min_index && index !== max_index);
			} else {
				index = this._clip_up_index;
				if (h_move < 0) {
					while (index < max_index) {
						if (childs[index - 1].x + childs[index - 1].width >= left) {
							break;
						}
						++ index;
					}
				} else if (h_move > 0) {
					while (index > min_index) {
						if (childs[index - 1].x <= left) {
							break;
						}
						-- index;
					}
				}
			}
			this._clip_up_index = index;
			for (let i = index; i <= child_count; i += 1) {
				if (childs[i - 1].x < right) {
					this._show.AddChild(childs[i - 1]._show);
					new_show_map.set(childs[i - 1], true);
					if (childs[i - 1].ClipRect !== undefined) {
						childs[i - 1].ClipRect(left, top, right, bottom, h_move, v_move);
					}
					this._clip_down_index = i;
				} else {
					break;
				}
			}
		} else {
			if (v_move === undefined || this._clip_up_index === 0) {
				do {
					if (childs[index - 1].y > top) {
						max_index = index;
						index = __ceil((max_index + min_index) / 2);
					} else if (childs[index - 1].y + childs[index - 1].height < top) {
						min_index = index;
						index = __ceil((max_index + min_index) / 2);
					} else {
						break;
					}
				} while (index !== min_index && index !== max_index);
			} else {
				index = this._clip_up_index;
				if (v_move < 0) {
					while (index < max_index) {
						if (childs[index - 1].y + childs[index - 1].height >= top) {
							break;
						}
						++ index;
					}
				} else if (v_move > 0) {
					while (index > min_index) {
						if (childs[index - 1].y <= top) {
							break;
						}
						-- index;
					}
				}
			}
			this._clip_up_index = index;
			for (let i = index; i <= child_count; i += 1) {
				if (childs[i - 1].y < bottom) {
					this._show.AddChild(childs[i - 1]._show);
					new_show_map.set(childs[i - 1], true);
					if (childs[i - 1].ClipRect !== undefined) {
						childs[i - 1].ClipRect(left, top, right, bottom, h_move, v_move);
					}
					this._clip_down_index = i;
				} else {
					break;
				}
			}
		}
		for (let [child, v] of new_show_map) {
			if (v === undefined) continue;
			if (this._show_child_map.get(child) === undefined) {
				child.DispatchEvent(___all_struct.get(1862557463), {});
			} else {
				this._show_child_map.delete(child);
			}
		}
		for (let [child, v] of this._show_child_map) {
			if (v === undefined) continue;
			child.DispatchEvent(___all_struct.get(348388800), {});
		}
		this._show_child_map = new_show_map;
	},
}, "ALittle.Linear");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-18570489, "ALittle.UITabCloseEvent", {
name : "ALittle.UITabCloseEvent", ns_name : "ALittle", rl_name : "UITabCloseEvent", hash_code : -18570489,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})

if (ALittle.Grid3 === undefined) throw new Error(" extends class:ALittle.Grid3 is undefined");
ALittle.Tab = JavaScript.Class(ALittle.Grid3, {
	Ctor : function(ctrl_sys) {
		this._button_inner_gap = 8;
		this._child_id_map = ALittle.CreateKeyWeakMap();
		this._group = ALittle.CreateKeyWeakMap();
		this.type = ALittle.UIEnumTypes.TYPE_V;
		this._view = ALittle.NewObject(ALittle.DisplayView, this._ctrl_sys);
		this._view.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
		this._view.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
		this._linear = ALittle.NewObject(ALittle.Linear, this._ctrl_sys);
		this._linear.type = ALittle.UIEnumTypes.TYPE_H;
		this._linear.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
		this._linear.y_type = ALittle.UIEnumTypes.POS_ALIGN_ENDING;
		this._view.AddChild(this._linear);
		this._view_start = 0;
		this._view_margin = 0;
		let show_up = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
		show_up.AddChild(this._view);
		this.show_up = show_up;
		this.show_center = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
		this._pickup_rect = true;
		this._pickup_child = true;
		this._tab_index = 0;
		this._child_width_margin = 0;
	},
	RefreshView : function() {
		if (this._radiobutton_style === undefined || this._text_style === undefined || this._closebutton_style === undefined || this._selected_text_style === undefined || this._selected_closebutton_style === undefined) {
			return;
		}
		let child_list = this._linear.childs;
		let ___OBJECT_1 = child_list;
		for (let k = 1; k <= ___OBJECT_1.length; ++k) {
			let v = ___OBJECT_1[k - 1];
			if (v === undefined) break;
			let childs = v.childs;
			childs[1 - 1].RemoveEventListener(___all_struct.get(958494922), this, this.HandleRadioButtonChanged);
			childs[1 - 1].RemoveEventListener(___all_struct.get(1337289812), this, this.HandleRadioButtonDrag);
			childs[1 - 1].RemoveEventListener(___all_struct.get(1301789264), this, this.HandleRadioButtonDragBegin);
			childs[1 - 1].RemoveEventListener(___all_struct.get(150587926), this, this.HandleRadioButtonDragEnd);
			childs[1 - 1].RemoveEventListener(___all_struct.get(-1330840), this, this.HandleRadioButtonMClick);
			childs[1 - 1].RemoveEventListener(___all_struct.get(-641444818), this, this.HandleRadioButtonRButtonDown);
			childs[1 - 1].RemoveEventListener(___all_struct.get(-1604617962), this, this.HandleRadioButtonKeyDown);
			childs[3 - 1].RemoveEventListener(___all_struct.get(-449066808), this, this.HandleCloseButtonClick);
			childs[5 - 1].RemoveEventListener(___all_struct.get(-449066808), this, this.HandleCloseButtonClick);
			childs[1 - 1].group = undefined;
		}
		this._linear.RemoveAllChild();
		let show_center = this.show_center;
		child_list = show_center.childs;
		let ___OBJECT_2 = child_list;
		for (let k = 1; k <= ___OBJECT_2.length; ++k) {
			let v = ___OBJECT_2[k - 1];
			if (v === undefined) break;
			let radiobutton = this._ctrl_sys.CreateControl(this._radiobutton_style);
			let text = this._ctrl_sys.CreateControl(this._text_style);
			let closebutton = this._ctrl_sys.CreateControl(this._closebutton_style);
			let selected_text = this._ctrl_sys.CreateControl(this._selected_text_style);
			let selected_closebutton = this._ctrl_sys.CreateControl(this._selected_closebutton_style);
			if (radiobutton !== undefined && text !== undefined && closebutton !== undefined && selected_text !== undefined && selected_closebutton !== undefined) {
				let simplelayout = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
				radiobutton.selected = (this._tab_index === k);
				radiobutton.AddEventListener(___all_struct.get(958494922), this, this.HandleRadioButtonChanged);
				radiobutton.AddEventListener(___all_struct.get(1337289812), this, this.HandleRadioButtonDrag);
				radiobutton.AddEventListener(___all_struct.get(1301789264), this, this.HandleRadioButtonDragBegin);
				radiobutton.AddEventListener(___all_struct.get(150587926), this, this.HandleRadioButtonDragEnd);
				radiobutton.AddEventListener(___all_struct.get(-1330840), this, this.HandleRadioButtonMClick);
				radiobutton.AddEventListener(___all_struct.get(-641444818), this, this.HandleRadioButtonRButtonDown);
				radiobutton.AddEventListener(___all_struct.get(-1604617962), this, this.HandleRadioButtonKeyDown);
				radiobutton.group = this._group;
				radiobutton.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
				radiobutton.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
				v.visible = radiobutton.selected;
				text.text = this._child_id_map.get(v);
				text.disabled = true;
				text.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
				text.y_value = 2;
				text.x = this._button_inner_gap;
				text.visible = !radiobutton.selected;
				selected_text.text = this._child_id_map.get(v);
				selected_text.disabled = true;
				selected_text.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
				selected_text.y_value = 2;
				selected_text.x = this._button_inner_gap;
				selected_text.visible = radiobutton.selected;
				closebutton.AddEventListener(___all_struct.get(-449066808), this, this.HandleCloseButtonClick);
				closebutton.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
				closebutton.y_value = 2;
				closebutton.x = text.x + text.width + this._button_inner_gap;
				closebutton.visible = !radiobutton.selected;
				selected_closebutton.AddEventListener(___all_struct.get(-449066808), this, this.HandleCloseButtonClick);
				selected_closebutton.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
				selected_closebutton.y_value = 2;
				selected_closebutton.x = selected_text.x + selected_text.width + this._button_inner_gap;
				selected_closebutton.visible = radiobutton.selected;
				simplelayout.width = this._button_inner_gap * 3 + text.width + closebutton.width;
				this._linear.AddChild(simplelayout);
				simplelayout.AddChild(radiobutton);
				simplelayout.AddChild(text);
				simplelayout.AddChild(closebutton);
				simplelayout.AddChild(selected_text);
				simplelayout.AddChild(selected_closebutton);
			}
		}
	},
	set radiobutton_style(value) {
		if (this._radiobutton_style === value) {
			return;
		}
		this._radiobutton_style = value;
		this.RefreshView();
	},
	get radiobutton_style() {
		return this._radiobutton_style;
	},
	set closebutton_style(value) {
		if (this._closebutton_style === value) {
			return;
		}
		this._closebutton_style = value;
		this.RefreshView();
	},
	get closebutton_style() {
		return this._closebutton_style;
	},
	set selected_closebutton_style(value) {
		if (this._selected_closebutton_style === value) {
			return;
		}
		this._selected_closebutton_style = value;
		this.RefreshView();
	},
	get selected_closebutton_style() {
		return this._selected_closebutton_style;
	},
	set text_style(value) {
		if (this._text_style === value) {
			return;
		}
		this._text_style = value;
		this.RefreshView();
	},
	get text_style() {
		return this._text_style;
	},
	set selected_text_style(value) {
		if (this._selected_text_style === value) {
			return;
		}
		this._selected_text_style = value;
		this.RefreshView();
	},
	get selected_text_style() {
		return this._selected_text_style;
	},
	set show_head_background(value) {
		if (this._head_background !== undefined) {
			this._view.RemoveChild(this._head_background);
		}
		this._head_background = value;
		if (this._head_background !== undefined) {
			this._head_background.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._head_background.width_value = 0;
			this._head_background.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._head_background.height_value = 0;
			this._view.AddChild(this._head_background, 1);
		}
	},
	get show_head_background() {
		return this._head_background;
	},
	set button_gap(value) {
		this._linear.gap = value;
	},
	get button_gap() {
		return this._linear.gap;
	},
	set button_start(value) {
		this._view.x = value;
	},
	get button_start() {
		return this._view.x;
	},
	set button_margin(value) {
		this._linear.height_value = value;
	},
	get button_margin() {
		return this._linear.height_value;
	},
	set child_width_margin(value) {
		this._child_width_margin = value;
		let show_center = this.show_center;
		let childs = show_center.childs;
		let ___OBJECT_3 = childs;
		for (let k = 1; k <= ___OBJECT_3.length; ++k) {
			let v = ___OBJECT_3[k - 1];
			if (v === undefined) break;
			v.width_value = this._child_width_margin;
		}
	},
	get child_width_margin() {
		return this._child_width_margin;
	},
	set head_size(value) {
		this.up_size = value;
	},
	get head_size() {
		return this.up_size;
	},
	set close_callback(value) {
		this._close_callback = value;
	},
	get close_callback() {
		return this._close_callback;
	},
	set close_post_callback(value) {
		this._close_post_callback = value;
	},
	get close_post_callback() {
		return this._close_post_callback;
	},
	set drag_callback(value) {
		this._drag_callback = value;
	},
	get drag_callback() {
		return this._drag_callback;
	},
	set drag_post_callback(value) {
		this._drag_post_callback = value;
	},
	get drag_post_callback() {
		return this._drag_post_callback;
	},
	get view_margin() {
		return this._view.width_value;
	},
	set view_margin(value) {
		this._view.width_value = value;
	},
	get view() {
		return this._view;
	},
	get view_linear() {
		return this._linear;
	},
	GetChildIndex : function(child) {
		return this.show_center.GetChildIndex(child);
	},
	SetChildIndex : function(child, index) {
		let show_center = this.show_center;
		let cur_index = show_center.GetChildIndex(child);
		if (index > show_center.child_count) {
			index = show_center.child_count;
		}
		if (cur_index === index) {
			return true;
		}
		let linear = this._linear;
		let linear_childs = linear.childs;
		let tab_child = this.tab;
		let button_child = linear_childs[cur_index - 1];
		if (button_child !== undefined) {
			linear.SetChildIndex(button_child, index);
		}
		let show_center_childs = show_center.childs;
		let body_child = show_center_childs[cur_index - 1];
		show_center.SetChildIndex(body_child, index);
		this._tab_index = show_center.GetChildIndex(tab_child);
		return true;
	},
	GetChildByIndex : function(index) {
		return this.show_center.GetChildByIndex(index);
	},
	GetChildIndex : function(child) {
		return this.show_center.GetChildIndex(child);
	},
	get childs() {
		let show_center = this.show_center;
		return show_center.childs;
	},
	get child_count() {
		let show_center = this.show_center;
		return show_center.child_count;
	},
	AddChild : function(child, index) {
		if (child === undefined || child === this) {
			return false;
		}
		if (child._show_parent === this.show_center || child._logic_parent === this) {
			return true;
		}
		if (child._logic_parent !== undefined) {
			child._logic_parent.RemoveChild(child);
		} else if (child._show_parent !== undefined) {
			child._show_parent.RemoveChild(child);
		}
		let show_center = this.show_center;
		show_center.AddChild(child, index);
		child._logic_parent = this;
		child.x = 0;
		child.y = 0;
		child.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
		child.width_value = this._child_width_margin;
		child.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
		child.height_value = 0;
		child.x_type = ALittle.UIEnumTypes.POS_ALIGN_ENDING;
		this._child_id_map.set(child, child.description);
		if (this._child_id_map.get(child) === undefined) {
			this._child_id_map.set(child, "");
		}
		if (this._radiobutton_style === undefined || this._text_style === undefined || this._closebutton_style === undefined || this._selected_text_style === undefined || this._selected_closebutton_style === undefined) {
			return true;
		}
		let radiobutton = this._ctrl_sys.CreateControl(this._radiobutton_style);
		let text = this._ctrl_sys.CreateControl(this._text_style);
		let closebutton = this._ctrl_sys.CreateControl(this._closebutton_style);
		let selected_text = this._ctrl_sys.CreateControl(this._selected_text_style);
		let selected_closebutton = this._ctrl_sys.CreateControl(this._selected_closebutton_style);
		if (radiobutton !== undefined && text !== undefined && closebutton !== undefined && selected_text !== undefined && selected_closebutton !== undefined) {
			let simplelayout = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
			radiobutton.AddEventListener(___all_struct.get(958494922), this, this.HandleRadioButtonChanged);
			radiobutton.AddEventListener(___all_struct.get(1337289812), this, this.HandleRadioButtonDrag);
			radiobutton.AddEventListener(___all_struct.get(1301789264), this, this.HandleRadioButtonDragBegin);
			radiobutton.AddEventListener(___all_struct.get(150587926), this, this.HandleRadioButtonDragEnd);
			radiobutton.AddEventListener(___all_struct.get(-1330840), this, this.HandleRadioButtonMClick);
			radiobutton.AddEventListener(___all_struct.get(-641444818), this, this.HandleRadioButtonRButtonDown);
			radiobutton.AddEventListener(___all_struct.get(-1604617962), this, this.HandleRadioButtonKeyDown);
			radiobutton.group = this._group;
			radiobutton.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			radiobutton.width_value = 0;
			radiobutton.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			radiobutton.height_value = 0;
			child.visible = radiobutton.selected;
			text.text = this._child_id_map.get(child);
			text.disabled = true;
			text.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
			text.y_value = 2;
			text.x = this._button_inner_gap;
			text.visible = !radiobutton.selected;
			selected_text.text = this._child_id_map.get(child);
			selected_text.disabled = true;
			selected_text.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
			selected_text.y_value = 2;
			selected_text.x = this._button_inner_gap;
			selected_text.visible = radiobutton.selected;
			closebutton.AddEventListener(___all_struct.get(-449066808), this, this.HandleCloseButtonClick);
			closebutton.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
			closebutton.y_value = 2;
			closebutton.x = text.x + text.width + this._button_inner_gap;
			closebutton.visible = !radiobutton.selected;
			selected_closebutton.AddEventListener(___all_struct.get(-449066808), this, this.HandleCloseButtonClick);
			selected_closebutton.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
			selected_closebutton.y_value = 2;
			selected_closebutton.x = selected_text.x + selected_text.width + this._button_inner_gap;
			selected_closebutton.visible = radiobutton.selected;
			simplelayout.width = this._button_inner_gap * 3 + text.width + closebutton.width;
			this._linear.AddChild(simplelayout, index);
			simplelayout.AddChild(radiobutton);
			simplelayout.AddChild(text);
			simplelayout.AddChild(closebutton);
			simplelayout.AddChild(selected_text);
			simplelayout.AddChild(selected_closebutton);
		}
		if (this._tab_index <= 0) {
			this.tab_index = 1;
		} else if (index !== undefined && this._tab_index >= index) {
			this._tab_index = this._tab_index + 1;
		}
		return true;
	},
	RemoveChild : function(child) {
		if (child === undefined) {
			return false;
		}
		if (child._show_parent !== this.show_center && child._logic_parent !== this) {
			return false;
		}
		let show_center = this.show_center;
		let index = show_center.GetChildIndex(child);
		if (index === 0) {
			return false;
		}
		show_center.RemoveChild(child);
		child.visible = true;
		this._child_id_map.delete(child);
		let simplelayout = this._linear.GetChildByIndex(index);
		if (simplelayout !== undefined) {
			let layout_childs = simplelayout.childs;
			layout_childs[1 - 1].RemoveEventListener(___all_struct.get(958494922), this, this.HandleRadioButtonChanged);
			layout_childs[1 - 1].RemoveEventListener(___all_struct.get(1337289812), this, this.HandleRadioButtonDrag);
			layout_childs[1 - 1].RemoveEventListener(___all_struct.get(1301789264), this, this.HandleRadioButtonDragBegin);
			layout_childs[1 - 1].RemoveEventListener(___all_struct.get(150587926), this, this.HandleRadioButtonDragEnd);
			layout_childs[1 - 1].RemoveEventListener(___all_struct.get(-1330840), this, this.HandleRadioButtonMClick);
			layout_childs[1 - 1].RemoveEventListener(___all_struct.get(-641444818), this, this.HandleRadioButtonRButtonDown);
			layout_childs[1 - 1].RemoveEventListener(___all_struct.get(-1604617962), this, this.HandleRadioButtonKeyDown);
			layout_childs[3 - 1].RemoveEventListener(___all_struct.get(-449066808), this, this.HandleCloseButtonClick);
			layout_childs[5 - 1].RemoveEventListener(___all_struct.get(-449066808), this, this.HandleCloseButtonClick);
			layout_childs[1 - 1].group = undefined;
			this._linear.RemoveChild(simplelayout);
		}
		let new_index = 0;
		if (this._tab_index === index) {
			new_index = index;
		} else if (this._tab_index > index) {
			new_index = this._tab_index - 1;
		} else {
			new_index = this._tab_index;
		}
		if (new_index > show_center.child_count) {
			new_index = show_center.child_count;
		} else if (new_index < 0) {
			new_index = 0;
		}
		this.tab_index = new_index;
		return true;
	},
	HasChild : function(child) {
		let show_center = this.show_center;
		return show_center.HasChild(child);
	},
	RemoveAllChild : function() {
		this._linear.RemoveAllChild();
		let show_center = this.show_center;
		let childs = show_center.childs;
		let ___OBJECT_4 = childs;
		for (let k = 1; k <= ___OBJECT_4.length; ++k) {
			let v = ___OBJECT_4[k - 1];
			if (v === undefined) break;
			v.visible = true;
		}
		show_center.RemoveAllChild();
		this._child_id_map = new Map();
		this._tab_index = 0;
	},
	HandleRadioButtonChanged : function(event) {
		let button = event.target;
		if (button.selected) {
			let show_center = this.show_center;
			let childs = show_center.childs;
			let ___OBJECT_5 = childs;
			for (let k = 1; k <= ___OBJECT_5.length; ++k) {
				let v = ___OBJECT_5[k - 1];
				if (v === undefined) break;
				v.visible = false;
			}
			let simplelayout = button.parent;
			let index = this._linear.GetChildIndex(simplelayout);
			let show_center_childs = show_center.childs;
			show_center_childs[index - 1].visible = true;
			let layout_childs = simplelayout.childs;
			layout_childs[3 - 1].visible = false;
			layout_childs[2 - 1].visible = false;
			if (layout_childs[5 - 1].disabled === false) {
				layout_childs[5 - 1].visible = true;
			}
			layout_childs[4 - 1].visible = true;
			this._tab_index = index;
			this.DispatchEvent(___all_struct.get(444989011), {});
		} else {
			let simplelayout = button.parent;
			let layout_childs = simplelayout.childs;
			if (layout_childs[3 - 1].disabled === false) {
				layout_childs[3 - 1].visible = true;
			}
			layout_childs[2 - 1].visible = true;
			layout_childs[5 - 1].visible = false;
			layout_childs[4 - 1].visible = false;
		}
	},
	HandleCloseButtonClick : function(event) {
		let simplelayout = event.target._show_parent;
		let index = this._linear.GetChildIndex(simplelayout);
		let show_center = this.show_center;
		let show_center_childs = show_center.childs;
		let child = show_center_childs[index - 1];
		if (this._close_callback !== undefined && this._close_callback(child) === false) {
			return;
		}
		this.RemoveChild(child);
		this.DispatchEvent(___all_struct.get(-18570489), {});
		if (this._close_post_callback !== undefined) {
			this._close_post_callback(child);
		}
	},
	HandleRadioButtonDragBegin : function(event) {
		let simplelayout = event.target._show_parent;
		let control_x = undefined;
		let control_y = undefined;
		[control_x, control_y] = simplelayout.LocalToGlobal();
		this._tab_image = ALittle.NewObject(ALittle.EffectImage, this._ctrl_sys);
		this._tab_image.Action(simplelayout);
		A_LayerManager.AddToTip(this._tab_image);
		this._tab_image.x = control_x;
		this._tab_image.y = control_y;
		this._tab_image.alpha = 0.9;
	},
	HandleRadioButtonDrag : function(event) {
		if (this._tab_image === undefined) {
			return;
		}
		this._tab_image.x = this._tab_image.x + event.delta_x;
		this._tab_image.y = this._tab_image.y + event.delta_y;
	},
	HandleRadioButtonDragEnd : function(event) {
		let target_index = this._linear.child_count;
		if (this._scale_x > 0) {
			let linear_x = undefined;
			let linear_y = undefined;
			[linear_x, linear_y] = this._linear.LocalToGlobal();
			let delta_x = (event.abs_x - linear_x) / this._scale_x;
			let child_list = this._linear.childs;
			let ___OBJECT_6 = child_list;
			for (let k = 1; k <= ___OBJECT_6.length; ++k) {
				let v = ___OBJECT_6[k - 1];
				if (v === undefined) break;
				if (delta_x < v.x + v.width / 2) {
					target_index = k;
					break;
				}
			}
		}
		let simplelayout = event.target._show_parent;
		let index = this._linear.GetChildIndex(simplelayout);
		let show_center = this.show_center;
		let show_center_childs = show_center.childs;
		let child = show_center_childs[index - 1];
		if (this._drag_callback !== undefined && this._drag_callback(child, target_index) === false) {
			return;
		}
		this._linear.SetChildIndex(simplelayout, target_index);
		show_center.SetChildIndex(child, target_index);
		if (this._drag_post_callback !== undefined) {
			this._drag_post_callback(child);
		}
		if (this._tab_image !== undefined) {
			A_LayerManager.RemoveFromTip(this._tab_image);
			this._tab_image.Clear();
			this._tab_image = undefined;
		}
	},
	HandleRadioButtonMClick : function(event) {
		let simplelayout = event.target._show_parent;
		let layout_childs = simplelayout.childs;
		if (layout_childs[3 - 1].disabled && layout_childs[5 - 1].disabled) {
			return;
		}
		let index = this._linear.GetChildIndex(simplelayout);
		let show_center = this.show_center;
		let show_center_childs = show_center.childs;
		let child = show_center_childs[index - 1];
		if (this._close_callback !== undefined && this._close_callback(child) === false) {
			return;
		}
		this.RemoveChild(child);
		this.DispatchEvent(___all_struct.get(-18570489), {});
		if (this._close_post_callback !== undefined) {
			this._close_post_callback(child);
		}
	},
	HandleRadioButtonRButtonDown : function(event) {
		let simplelayout = event.target._show_parent;
		let index = this._linear.GetChildIndex(simplelayout);
		let show_center = this.show_center;
		let show_center_childs = show_center.childs;
		let child = show_center_childs[index - 1];
		let e = {};
		e.target = child;
		this.DispatchEvent(___all_struct.get(-641444818), e);
	},
	HandleRadioButtonKeyDown : function(event) {
		let simplelayout = event.target._show_parent;
		let index = this._linear.GetChildIndex(simplelayout);
		let show_center = this.show_center;
		let show_center_childs = show_center.childs;
		let child = show_center_childs[index - 1];
		let e = {};
		e.target = child;
		e.mod = event.mod;
		e.sym = event.sym;
		e.scancode = event.scancode;
		this.DispatchEvent(___all_struct.get(-1604617962), e);
		event.handled = e.handled;
	},
	SetChildText : function(child, text) {
		if (this._radiobutton_style === undefined) {
			return;
		}
		let show_center = this.show_center;
		let index = show_center.GetChildIndex(child);
		if (index === 0) {
			return;
		}
		let simplelayout = this._linear.GetChildByIndex(index);
		if (simplelayout !== undefined) {
			let childs = simplelayout.childs;
			let text_control = childs[2 - 1];
			let closebutton = childs[3 - 1];
			let selected_text_control = childs[4 - 1];
			let selected_closebutton = childs[5 - 1];
			text_control.text = text;
			selected_text_control.text = text;
			closebutton.x = text_control.x + text_control.width + this._button_inner_gap;
			selected_closebutton.x = selected_text_control.x + selected_text_control.width + this._button_inner_gap;
			simplelayout.width = this._button_inner_gap * 3 + text_control.width + closebutton.width;
			this._child_id_map.set(child, text);
			this._linear.Layout(1);
		}
	},
	GetChildText : function(child) {
		return this._child_id_map.get(child);
	},
	HasChildText : function(text) {
		for (let [k, v] of this._child_id_map) {
			if (v === undefined) continue;
			if (v === text) {
				return true;
			}
		}
		return false;
	},
	GetChildByText : function(text) {
		for (let [k, v] of this._child_id_map) {
			if (v === undefined) continue;
			if (v === text) {
				return k;
			}
		}
		return undefined;
	},
	set tab(child) {
		let show_center = this.show_center;
		let index = show_center.GetChildIndex(child);
		if (index === 0) {
			return;
		}
		this.tab_index = index;
	},
	get tab() {
		let show_center = this.show_center;
		let show_center_childs = show_center.childs;
		return show_center_childs[this._tab_index - 1];
	},
	set tab_index(index) {
		let show_center = this.show_center;
		let show_center_childs = show_center.childs;
		if (this._tab_index !== 0) {
			let cur_child = show_center_childs[this._tab_index - 1];
			if (cur_child !== undefined) {
				cur_child.visible = false;
			}
			let simplelayout = this._linear.GetChildByIndex(this._tab_index);
			if (simplelayout !== undefined) {
				let childs = simplelayout.childs;
				childs[1 - 1].selected = false;
				childs[2 - 1].visible = true;
				if (childs[3 - 1].disabled === false) {
					childs[3 - 1].visible = true;
				}
				childs[4 - 1].visible = false;
				childs[5 - 1].visible = false;
			}
			this._tab_index = 0;
		}
		this._tab_index = index;
		if (this._tab_index !== 0) {
			let child = show_center_childs[this._tab_index - 1];
			if (child === undefined) {
				return;
			}
			child.visible = true;
			let simplelayout = this._linear.GetChildByIndex(this._tab_index);
			if (simplelayout !== undefined) {
				let childs = simplelayout.childs;
				childs[1 - 1].selected = true;
				childs[2 - 1].visible = false;
				childs[3 - 1].visible = false;
				childs[4 - 1].visible = true;
				if (childs[5 - 1].disabled === false) {
					childs[5 - 1].visible = true;
				}
			}
		}
		if (this._tab_index < 1 || this._tab_index > show_center.child_count) {
			this._tab_index = 0;
		}
	},
	get tab_index() {
		return this._tab_index;
	},
	DisableCloseButton : function(child) {
		let show_center = this.show_center;
		let index = show_center.GetChildIndex(child);
		if (index === 0) {
			return;
		}
		let linear_childs = this._linear.childs;
		let simplelayout = linear_childs[index - 1];
		if (simplelayout === undefined) {
			return;
		}
		let layout_childs = simplelayout.childs;
		layout_childs[3 - 1].visible = false;
		layout_childs[3 - 1].disabled = true;
		layout_childs[2 - 1].x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		layout_childs[2 - 1].x_value = 0;
		layout_childs[5 - 1].visible = false;
		layout_childs[5 - 1].disabled = true;
		layout_childs[4 - 1].x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		layout_childs[4 - 1].x_value = 0;
	},
	DisableAllCloseButton : function() {
		let show_center = this.show_center;
		let count = show_center.child_count;
		let linear_childs = this._linear.childs;
		for (let index = 1; index <= count; index += 1) {
			let simplelayout = linear_childs[index - 1];
			if (simplelayout === undefined) {
				return;
			}
			let layout_childs = simplelayout.childs;
			layout_childs[3 - 1].visible = false;
			layout_childs[3 - 1].disabled = true;
			layout_childs[2 - 1].x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
			layout_childs[2 - 1].x_value = 0;
			layout_childs[5 - 1].visible = false;
			layout_childs[5 - 1].disabled = true;
			layout_childs[4 - 1].x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
			layout_childs[4 - 1].x_value = 0;
		}
	},
	EnableCloseButton : function(child) {
		let show_center = this.show_center;
		let index = show_center.GetChildIndex(child);
		if (index === 0) {
			return;
		}
		let linear_childs = this._linear.childs;
		let simplelayout = linear_childs[index - 1];
		if (simplelayout === undefined) {
			return;
		}
		let layout_childs = simplelayout.childs;
		layout_childs[3 - 1].visible = !layout_childs[1 - 1].selected;
		layout_childs[3 - 1].disabled = false;
		layout_childs[2 - 1].x_type = ALittle.UIEnumTypes.POS_ABS;
		layout_childs[2 - 1].x = this._button_inner_gap;
		layout_childs[5 - 1].visible = layout_childs[1 - 1].selected;
		layout_childs[5 - 1].disabled = false;
		layout_childs[4 - 1].x_type = ALittle.UIEnumTypes.POS_ABS;
		layout_childs[4 - 1].x = this._button_inner_gap;
	},
	GetChildHead : function(child) {
		let show_center = this.show_center;
		let index = show_center.GetChildIndex(child);
		if (index === 0) {
			return undefined;
		}
		let linear_childs = this._linear.childs;
		return linear_childs[index - 1];
	},
}, "ALittle.Tab");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.TextCheckButton === undefined) throw new Error(" extends class:ALittle.TextCheckButton is undefined");
ALittle.DropDown = JavaScript.Class(ALittle.TextCheckButton, {
	Ctor : function(ctrl_sys) {
		this._body = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
		this._body.__right_data = this;
		this._body.visible = false;
		this._linear = ALittle.NewObject(ALittle.Linear, this._ctrl_sys);
		this._linear.type = ALittle.UIEnumTypes.TYPE_V;
		this._linear.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
		this._linear.width_value = 0;
		this._linear.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
		this._linear.height_value = 0;
		this._scroll_screen = ALittle.NewObject(ALittle.ScrollScreen, this._ctrl_sys);
		this._scroll_screen.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
		this._scroll_screen.width_value = 0;
		this._scroll_screen.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
		this._scroll_screen.height_value = 0;
		this._scroll_screen.container = this._linear;
		this._body.AddChild(this._scroll_screen);
		this._body_margin = 0;
		this._screen_margin_left = 0;
		this._screen_margin_right = 0;
		this._screen_margin_top = 0;
		this._screen_margin_bottom = 0;
		this._show_count = 0;
		this.AddEventListener(___all_struct.get(958494922), this, this.HandleButtonChange);
		this._body.AddEventListener(___all_struct.get(348388800), this, this.HandleBodyHide);
	},
	set show_background(value) {
		if (this._background === value) {
			return;
		}
		this._body.RemoveChild(this._background);
		this._background = value;
		if (this._background !== undefined) {
			this._background.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._background.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._background.width_value = 0;
			this._background.height_value = 0;
			this._body.AddChild(this._background, 0);
		}
	},
	get show_background() {
		return this._background;
	},
	set show_scrollbar(value) {
		if (this._scrollbar === value) {
			return;
		}
		this._scrollbar = value;
		if (this._scrollbar === undefined) {
			this._scroll_screen.right_scrollbar = undefined;
		}
		this.Layout();
	},
	get show_scrollbar() {
		return this._scrollbar;
	},
	set show_count(value) {
		if (this._show_count === value) {
			return;
		}
		this._show_count = value;
		this.Layout();
	},
	get show_count() {
		return this._show_count;
	},
	set button_style(value) {
		if (this._button_style === value) {
			return;
		}
		let child_list = this._scroll_screen.childs;
		let ___OBJECT_1 = child_list;
		for (let k = 1; k <= ___OBJECT_1.length; ++k) {
			let v = ___OBJECT_1[k - 1];
			if (v === undefined) break;
			v.RemoveEventListener(___all_struct.get(-449066808), this, this.HandleItemButtonClick);
		}
		this._scroll_screen.RemoveAllChild();
		this._button_style = value;
		let button = undefined;
		if (this._button_style !== undefined && this._data_list !== undefined) {
			let ___OBJECT_2 = this._data_list;
			for (let k = 1; k <= ___OBJECT_2.length; ++k) {
				let v = ___OBJECT_2[k - 1];
				if (v === undefined) break;
				button = this._ctrl_sys.CreateControl(this._button_style, undefined, this._scroll_screen);
				button.AddEventListener(___all_struct.get(-449066808), this, this.HandleItemButtonClick);
				button.text = v;
				button.drag_trans_target = this._scroll_screen;
			}
		}
		if (this._show_count === 0 || this._show_count >= this._linear.child_count) {
			this._body.height = this._linear.height + this._screen_margin_top + this._screen_margin_bottom;
		} else if (button !== undefined) {
			this._body.height = button.height * this._show_count + this._screen_margin_top + this._screen_margin_bottom;
		} else {
			this._body.height = 0;
		}
	},
	get button_style() {
		return this._button_style;
	},
	set body_margin(value) {
		this._body_margin = value;
	},
	get body_margin() {
		return this._body_margin;
	},
	set screen_margin_left(value) {
		this._screen_margin_left = value;
	},
	get screen_margin_left() {
		return this._screen_margin_left;
	},
	set screen_margin_right(value) {
		this._screen_margin_right = value;
	},
	get screen_margin_right() {
		return this._screen_margin_right;
	},
	set screen_margin_top(value) {
		this._screen_margin_top = value;
	},
	get screen_margin_top() {
		return this._screen_margin_top;
	},
	set screen_margin_bottom(value) {
		this._screen_margin_bottom = value;
	},
	get screen_margin_bottom() {
		return this._screen_margin_bottom;
	},
	set data_list(value) {
		if (value === undefined) {
			value = [];
		}
		let button_style = this._button_style;
		this._button_style = undefined;
		this._data_list = value;
		this.button_style = button_style;
		if (ALittle.List_MaxN(value) > 0) {
			this.text = value[1 - 1];
		} else {
			this.text = "";
		}
		this.Layout();
	},
	get data_list() {
		return this._data_list;
	},
	HandleItemButtonClick : function(event) {
		A_LayerManager.HideFromRight(this._body);
		if (this.text === event.target.text) {
			return;
		}
		this.text = event.target.text;
		this.DispatchEvent(___all_struct.get(444989011), {});
	},
	HandleButtonChange : function(event) {
		if (event.target.selected === false) {
			A_LayerManager.HideFromRight(this._body);
		} else {
			let [abs_x, abs_y] = this.LocalToGlobal();
			let rejust_y = abs_y + this.height * this.scale_y;
			if (A_UISystem.view_height < rejust_y + this._scroll_screen.height * this.scale_y) {
				rejust_y = abs_y - this._scroll_screen.height * this.scale_y;
			}
			this._body.y = rejust_y;
			this._body.width = this.width + this._body_margin;
			this._body.x = abs_x - this._body_margin / 2;
			this._body.scale_x = this.scale_x;
			this._body.scale_y = this.scale_y;
			this._scroll_screen.x = this._screen_margin_left;
			this._scroll_screen.y = this._screen_margin_top;
			this._scroll_screen.width_value = this._screen_margin_left + this._screen_margin_right;
			this._scroll_screen.height_value = this._screen_margin_top + this._screen_margin_bottom;
			A_LayerManager.ShowFromRight(this._body);
			A_UISystem.focus = this._scroll_screen;
		}
	},
	HandleBodyHide : function(event) {
		if (this.selected === false) {
			return;
		}
		this.selected = false;
	},
	Layout : function() {
		if (this._show_count === 0 || this._scrollbar === undefined || this._show_count >= this._linear.child_count) {
			this._scroll_screen.right_scrollbar = undefined;
			this._body.height = this._linear.height + this._screen_margin_top + this._screen_margin_bottom;
		} else {
			this._scroll_screen.right_scrollbar = this._scrollbar;
			let button = this._linear.childs[1 - 1];
			if (button !== undefined) {
				this._body.height = button.height * this._show_count + this._screen_margin_top + this._screen_margin_bottom;
			} else {
				this._body.height = 0;
			}
		}
	},
}, "ALittle.DropDown");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.Slider = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._pickup_rect = false;
		this._type = ALittle.UIEnumTypes.TYPE_V;
		this._offset_rate = 0;
		this._drag_point_rate = 0;
		this._fixed = ALittle.UIEnumTypes.FREE;
		this._grade = 2;
		this._grade_list = [];
	},
	set width(value) {
		ALittle.DisplayLayout.__setter.width.call(this, value);
		this.RejustBarButton();
	},
	set height(value) {
		ALittle.DisplayLayout.__setter.height.call(this, value);
		this.RejustBarButton();
	},
	get width() {
		return this._width;
	},
	get height() {
		return this._height;
	},
	set type(value) {
		if (this._type === value) {
			return;
		}
		this._type = value;
		this.RejustBarButton();
	},
	get type() {
		return this._type;
	},
	set offset_rate(value) {
		this._offset_rate = value;
		if (this._offset_rate < 0) {
			this._offset_rate = 0;
		} else if (this._offset_rate > 1) {
			this._offset_rate = 1;
		}
		this.RejustBarButton();
	},
	get offset_rate() {
		return this._offset_rate;
	},
	set grade_value(value) {
		if (this._fixed === ALittle.UIEnumTypes.FREE) {
			this.offset_rate = value;
			return;
		}
		this.offset_rate = (lua.math.floor(value) - 1) / (this.grade - 1);
	},
	get grade_value() {
		if (this._fixed === ALittle.UIEnumTypes.FREE) {
			return this._offset_rate;
		}
		return lua.math.floor(this._offset_rate * (this._grade - 1)) + 1;
	},
	set bar_background(value) {
		if (this._bar_background !== undefined) {
			this._bar_background.RemoveEventListener(___all_struct.get(1883782801), this, this.HandleBarBackgroudLButtonDown);
			this.RemoveChild(this._bar_background);
		}
		this._bar_background = value;
		if (value !== undefined) {
			this.AddChild(value, 1);
			value.AddEventListener(___all_struct.get(1883782801), this, this.HandleBarBackgroudLButtonDown);
		}
		this.RejustBarButton();
	},
	HandleBarBackgroudLButtonDown : function(event) {
		let rel_x = event.rel_x;
		let rel_y = event.rel_y;
		let real_width = this.width;
		let real_height = this.height;
		let bar_width = this._bar_button.width;
		let bar_height = this._bar_button.height;
		if (this._type === ALittle.UIEnumTypes.TYPE_V) {
			let offset = rel_y / real_height;
			if (offset > 1) {
				offset = 1;
			} else if (offset < 0) {
				offset = 0;
			}
			if (this._fixed === ALittle.UIEnumTypes.FREE) {
				if (this._offset_rate === offset) {
					return;
				}
				this._offset_rate = offset;
				this._bar_button.y = this._offset_rate * real_height - bar_height / 2;
			} else {
				let offset_grade = (1 / (this._grade - 1)) / 2;
				let offset_up = offset + offset_grade;
				let offset_down = offset - offset_grade;
				let ___OBJECT_1 = this._grade_list;
				for (let k = 1; k <= ___OBJECT_1.length; ++k) {
					let v = ___OBJECT_1[k - 1];
					if (v === undefined) break;
					if (v > offset_down && v <= offset_up) {
						this._offset_rate = v;
						this._bar_button.y = this._offset_rate * real_height - bar_height / 2;
						break;
					}
				}
			}
		} else {
			let offset = rel_x / real_width;
			if (offset > 1) {
				offset = 1;
			} else if (offset < 0) {
				offset = 0;
			}
			if (this._fixed === ALittle.UIEnumTypes.FREE) {
				if (this._offset_rate === offset) {
					return;
				}
				this._offset_rate = offset;
				this._bar_button.x = this._offset_rate * real_width - bar_width / 2;
			} else {
				let offset_grade = (1 / (this._grade - 1)) / 2;
				let offset_up = offset + offset_grade;
				let offset_down = offset - offset_grade;
				let ___OBJECT_2 = this._grade_list;
				for (let k = 1; k <= ___OBJECT_2.length; ++k) {
					let v = ___OBJECT_2[k - 1];
					if (v === undefined) break;
					if (v > offset_down && v <= offset_up) {
						this._offset_rate = v;
						this._bar_button.x = this._offset_rate * real_width - bar_width / 2;
						break;
					}
				}
			}
		}
		this.DispatchEvent(___all_struct.get(958494922), {});
	},
	get bar_background() {
		return this._bar_background;
	},
	set bar_button(value) {
		if (this._bar_button !== undefined) {
			this._bar_button.RemoveEventListener(___all_struct.get(1337289812), this, this.HandleBarButtonDrag);
			this._bar_button.RemoveEventListener(___all_struct.get(1301789264), this, this.HandleBarButtonDragBegin);
			this._bar_button.RemoveEventListener(___all_struct.get(-1737121315), this, this.HandleBarButtonScroll);
			this.RemoveChild(this._bar_button);
		}
		this._bar_button = value;
		if (value !== undefined) {
			this.AddChild(value);
			value.AddEventListener(___all_struct.get(1337289812), this, this.HandleBarButtonDrag);
			value.AddEventListener(___all_struct.get(1301789264), this, this.HandleBarButtonDragBegin);
			value.AddEventListener(___all_struct.get(-1737121315), this, this.HandleBarButtonScroll);
			value._can_scroll = true;
		}
		this.RejustBarButton();
	},
	get bar_button() {
		return this._bar_button;
	},
	set fixed(value) {
		if (this._fixed === value) {
			return;
		}
		this._fixed = value;
		if (this._fixed === ALittle.UIEnumTypes.FIXED && this._grade !== undefined) {
			this._grade_list = [];
			this._grade_list[1 - 1] = 0;
			let dist = 1 / (this._grade - 1);
			for (let i = 1; i <= this._grade - 2; i += 1) {
				this._grade_list[i + 1 - 1] = i * dist;
			}
			let num = lua.table.maxn(this._grade_list);
			this._grade_list[num + 1 - 1] = 1;
		}
		this.RejustBarButton();
	},
	get fixed() {
		return this._fixed;
	},
	set grade(value) {
		if (this._grade === value || value < 2) {
			return;
		}
		this._grade = value;
		if (this._fixed === ALittle.UIEnumTypes.FIXED && value !== undefined) {
			this._grade_list = [];
			this._grade_list[1 - 1] = 0;
			let dist = 1 / (value - 1);
			for (let i = 1; i <= value - 2; i += 1) {
				this._grade_list[i + 1 - 1] = i * dist;
			}
			let num = lua.table.maxn(this._grade_list);
			this._grade_list[num + 1 - 1] = 1;
		}
		this.RejustBarButton();
	},
	get grade() {
		return this._grade;
	},
	HandleBarButtonDragBegin : function(event) {
		let rel_x = undefined;
		let rel_y = undefined;
		[rel_x, rel_y] = this._bar_button.GlobalToLocalMatrix2D(event.abs_x, event.abs_y);
		if (this._type === ALittle.UIEnumTypes.TYPE_V) {
			let height = this._bar_button.height;
			this._drag_point_rate = 0;
			if (height > 0) {
				this._drag_point_rate = rel_y / height;
			}
		} else {
			let width = this._bar_button.width;
			this._drag_point_rate = 0;
			if (width > 0) {
				this._drag_point_rate = rel_x / width;
			}
		}
	},
	HandleBarButtonDrag : function(event) {
		let rel_x = undefined;
		let rel_y = undefined;
		[rel_x, rel_y] = this._bar_button.GlobalToLocalMatrix2D(event.abs_x, event.abs_y);
		let abs_x = undefined;
		let abs_y = undefined;
		[abs_x, abs_y] = this._bar_background.GlobalToLocalMatrix2D(event.abs_x, event.abs_y);
		let real_width = this.width;
		let real_height = this.height;
		let bar_width = this._bar_button.width;
		let bar_height = this._bar_button.height;
		if (this._type === ALittle.UIEnumTypes.TYPE_V) {
			if (this._fixed === ALittle.UIEnumTypes.FREE) {
				if ((event.delta_y > 0 && rel_y < bar_height * this._drag_point_rate) || (event.delta_y < 0 && rel_y > bar_height * this._drag_point_rate)) {
					return;
				}
				let offset = (this._bar_button.y + bar_height / 2 + event.delta_y) / real_height;
				if (offset > 1) {
					offset = 1;
				} else if (offset < 0) {
					offset = 0;
				}
				if (this._offset_rate === offset) {
					return;
				}
				this._offset_rate = offset;
				this._bar_button.y = this._offset_rate * real_height - bar_height / 2;
			} else {
				let offset = abs_y / real_height;
				if (offset > 1) {
					offset = 1;
				} else if (offset < 0) {
					offset = 0;
				}
				let offset_grade = (1 / (this._grade - 1)) / 2;
				let offset_up = offset + offset_grade;
				let offset_down = offset - offset_grade;
				let ___OBJECT_3 = this._grade_list;
				for (let k = 1; k <= ___OBJECT_3.length; ++k) {
					let v = ___OBJECT_3[k - 1];
					if (v === undefined) break;
					if (v > offset_down && v <= offset_up) {
						this._offset_rate = v;
						this._bar_button.y = this._offset_rate * real_height - bar_height / 2;
						break;
					}
				}
			}
		} else {
			if (this._fixed === ALittle.UIEnumTypes.FREE) {
				if ((event.delta_x > 0 && rel_x < bar_height * this._drag_point_rate) || (event.delta_x < 0 && rel_x > bar_height * this._drag_point_rate)) {
					return;
				}
				let offset = (this._bar_button.x + bar_width / 2 + event.delta_x) / real_width;
				if (offset > 1) {
					offset = 1;
				} else if (offset < 0) {
					offset = 0;
				}
				if (this._offset_rate === offset) {
					return;
				}
				this._offset_rate = offset;
				this._bar_button.x = this._offset_rate * real_width - bar_width / 2;
			} else {
				let offset = abs_x / real_width;
				if (offset > 1) {
					offset = 1;
				} else if (offset < 0) {
					offset = 0;
				}
				let offset_grade = (1 / (this._grade - 1)) / 2;
				let offset_up = offset + offset_grade;
				let offset_down = offset - offset_grade;
				let ___OBJECT_4 = this._grade_list;
				for (let k = 1; k <= ___OBJECT_4.length; ++k) {
					let v = ___OBJECT_4[k - 1];
					if (v === undefined) break;
					if (v > offset_down && v <= offset_up) {
						this._offset_rate = v;
						this._bar_button.x = this._offset_rate * real_width - bar_width / 2;
						break;
					}
				}
			}
		}
		this.DispatchEvent(___all_struct.get(958494922), {});
	},
	HandleBarButtonScroll : function(event) {
		let step = undefined;
		if (this._fixed === ALittle.UIEnumTypes.FREE) {
			step = 0.01;
		} else {
			step = 1 / (this._grade - 1);
		}
		if (this._type === ALittle.UIEnumTypes.TYPE_V) {
			if (event.delta_y > 0) {
				this.HandleUpDownButton(-1 * step);
			} else if (event.delta_y < 0) {
				this.HandleUpDownButton(step);
			}
		} else {
			if (event.delta_x > 0) {
				this.HandleUpDownButton(-1 * step);
			} else if (event.delta_x < 0) {
				this.HandleUpDownButton(step);
			}
		}
	},
	HandleUpDownButton : function(step) {
		this._offset_rate = this._offset_rate + step;
		if (this._offset_rate < 0) {
			this._offset_rate = 0;
		}
		if (this._offset_rate > 1) {
			this._offset_rate = 1;
		}
		if (this._type === ALittle.UIEnumTypes.TYPE_V) {
			this._bar_button.y = this._offset_rate * this.height - this._bar_button.height / 2;
		} else {
			this._bar_button.x = this._offset_rate * this.width - this._bar_button.width / 2;
		}
		this.DispatchEvent(___all_struct.get(958494922), {});
	},
	RejustBarButton : function() {
		if (this._bar_background !== undefined) {
			this._bar_background.x = 0;
			this._bar_background.y = 0;
			this._bar_background.width = this.width;
			this._bar_background.height = this.height;
		}
		if (this._bar_button !== undefined) {
			if (this._type === ALittle.UIEnumTypes.TYPE_V) {
				this._bar_button.x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
				this._bar_button.x_value = 0;
				this._bar_button.y_type = ALittle.UIEnumTypes.POS_ABS;
				this._bar_button.y_value = this._offset_rate * this.height - this._bar_button.height / 2;
			} else {
				this._bar_button.x_type = ALittle.UIEnumTypes.POS_ABS;
				this._bar_button.x_value = this._offset_rate * this.width - this._bar_button.width / 2;
				this._bar_button.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
				this._bar_button.y_value = 0;
			}
		}
	},
}, "ALittle.Slider");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.Grid3 === undefined) throw new Error(" extends class:ALittle.Grid3 is undefined");
ALittle.ScrollBar = JavaScript.Class(ALittle.Grid3, {
	Ctor : function(ctrl_sys) {
		this._bar_container = ALittle.NewObject(ALittle.DisplayGroup, this._ctrl_sys);
		this.show_center = this._bar_container;
		this._offset_step = 0;
		this._offset_rate = 0;
		this._show_size = 0;
		this._center_size = 0;
		this._logic_total_size = 0;
		this._logic_show_size = 0;
		this._drag_point_rate = 0;
		this._pickup_rect = true;
		this._pickup_child = true;
	},
	set type(value) {
		ALittle.Grid3.__setter.type.call(this, value);
		this.UpdateShowSize();
		this.RejustBarButton();
	},
	set up_size(value) {
		ALittle.Grid3.__setter.up_size.call(this, value);
		this.UpdateShowSize();
		this.RejustBarButton();
	},
	set down_size(value) {
		ALittle.Grid3.__setter.down_size.call(this, value);
		this.UpdateShowSize();
		this.RejustBarButton();
	},
	set gap(value) {
		ALittle.Grid3.__setter.gap.call(this, value);
		this.UpdateShowSize();
		this.RejustBarButton();
	},
	set total_size(value) {
		this._logic_total_size = value;
		this.UpdateShowSize();
		this.RejustBarButton();
	},
	get total_size() {
		return this._logic_total_size;
	},
	set show_size(value) {
		this._logic_show_size = value;
		this.UpdateShowSize();
		this.RejustBarButton();
	},
	get show_size() {
		return this._logic_show_size;
	},
	set offset_rate(value) {
		this._offset_rate = value;
		if (this._offset_rate < 0) {
			this._offset_rate = 0;
		} else if (this._offset_rate > 1) {
			this._offset_rate = 1;
		}
		this.RejustBarButton();
	},
	get offset_rate() {
		return this._offset_rate;
	},
	set offset_step(value) {
		this._offset_step = value;
	},
	get offset_step() {
		return this._offset_step;
	},
	UpdateShowSize : function() {
		this._show_size = 0;
		this._center_size = this.center_size;
		if (this._logic_show_size < this._logic_total_size) {
			this._show_size = this._logic_show_size / this._logic_total_size * this._center_size;
		}
	},
	SetToDown : function() {
		this._offset_rate = 1;
		this.RejustBarButton();
	},
	set width(value) {
		if (this._width === value) {
			return;
		}
		ALittle.Grid3.__setter.width.call(this, value);
		this.UpdateShowSize();
		this.RejustBarButton();
	},
	set height(value) {
		if (this._height === value) {
			return;
		}
		ALittle.Grid3.__setter.height.call(this, value);
		this.UpdateShowSize();
		this.RejustBarButton();
	},
	set up_button(value) {
		if (this._up_button !== undefined) {
			this._up_button.RemoveEventListener(___all_struct.get(-449066808), this, this.HandleUpButtonClick);
		}
		this._up_button = value;
		this.show_up = value;
		if (value !== undefined) {
			value.AddEventListener(___all_struct.get(-449066808), this, this.HandleUpButtonClick);
		}
	},
	get up_button() {
		return this._up_button;
	},
	HandleUpButtonClick : function(event) {
		this._offset_rate = this._offset_rate - this._offset_step;
		if (this._offset_rate < 0) {
			this._offset_rate = 0;
		}
		if (this._bar_button !== undefined) {
			let offset = this._offset_rate * (this._center_size - this._show_size);
			if (this._type === ALittle.UIEnumTypes.TYPE_V) {
				this._bar_button.y = offset;
			} else {
				this._bar_button.x = offset;
			}
		}
		this.DispatchEvent(___all_struct.get(958494922), {});
		this.DispatchEvent(___all_struct.get(1309977874), {});
	},
	set down_button(value) {
		if (this._down_button !== undefined) {
			this._down_button.RemoveEventListener(___all_struct.get(-449066808), this, this.HandleDownButtonClick);
		}
		this._down_button = value;
		this.show_down = value;
		if (value !== undefined) {
			value.AddEventListener(___all_struct.get(-449066808), this, this.HandleDownButtonClick);
		}
	},
	get down_button() {
		return this._down_button;
	},
	HandleDownButtonClick : function(event) {
		this._offset_rate = this._offset_rate + this._offset_step;
		if (this._offset_rate > 1) {
			this._offset_rate = 1;
		}
		if (this._bar_button !== undefined) {
			let offset = this._offset_rate * (this._center_size - this._show_size);
			if (this._type === ALittle.UIEnumTypes.TYPE_V) {
				this._bar_button.y = offset;
			} else {
				this._bar_button.x = offset;
			}
		}
		this.DispatchEvent(___all_struct.get(958494922), {});
		this.DispatchEvent(___all_struct.get(1309977874), {});
	},
	set bar_button(value) {
		if (this._bar_button !== undefined) {
			this._bar_button.RemoveEventListener(___all_struct.get(1337289812), this, this.HandleBarButtonDrag);
			this._bar_button.RemoveEventListener(___all_struct.get(1301789264), this, this.HandleBarButtonDragBegin);
			this._bar_button.RemoveEventListener(___all_struct.get(150587926), this, this.HandleBarButtonDragEnd);
			this._bar_button.RemoveEventListener(___all_struct.get(-1737121315), this, this.HandleBarButtonScroll);
			this._bar_container.RemoveChild(this._bar_button);
		}
		this._bar_button = value;
		if (value !== undefined) {
			this._bar_container.AddChild(value);
			value.AddEventListener(___all_struct.get(1337289812), this, this.HandleBarButtonDrag);
			value.AddEventListener(___all_struct.get(1301789264), this, this.HandleBarButtonDragBegin);
			value.AddEventListener(___all_struct.get(150587926), this, this.HandleBarButtonDragEnd);
			value.AddEventListener(___all_struct.get(-1737121315), this, this.HandleBarButtonScroll);
		}
		this.RejustBarButton();
	},
	get bar_button() {
		return this._bar_button;
	},
	set bar_background(value) {
		if (this._bar_background !== undefined) {
			this._bar_container.RemoveChild(this._bar_background);
		}
		this._bar_background = value;
		if (value !== undefined) {
			this._bar_container.AddChild(value, 1);
		}
		this.RejustBarButton();
	},
	get bar_background() {
		return this._bar_background;
	},
	HandleBarButtonDragBegin : function(event) {
		if (this._type === ALittle.UIEnumTypes.TYPE_V) {
			let height = this._bar_button.height;
			this._drag_point_rate = 0;
			if (height > 0) {
				this._drag_point_rate = event.rel_y / height;
			}
		} else {
			let width = this._bar_button.width;
			this._drag_point_rate = 0;
			if (width > 0) {
				this._drag_point_rate = event.rel_x / width;
			}
		}
	},
	HandleBarButtonScroll : function(event) {
		if (this._type === ALittle.UIEnumTypes.TYPE_V) {
			if (event.delta_y > 0) {
				this.HandleUpButtonClick(undefined);
			} else if (event.delta_y < 0) {
				this.HandleDownButtonClick(undefined);
			}
		} else {
			if (event.delta_x > 0) {
				this.HandleUpButtonClick(undefined);
			} else if (event.delta_x < 0) {
				this.HandleDownButtonClick(undefined);
			}
		}
	},
	HandleBarButtonDragEnd : function(event) {
		this.DispatchEvent(___all_struct.get(1309977874), {});
	},
	HandleBarButtonDrag : function(event) {
		let real_size = this._center_size - this._show_size;
		if (this._type === ALittle.UIEnumTypes.TYPE_V) {
			if ((event.delta_y > 0 && event.rel_y < this._show_size * this._drag_point_rate) || (event.delta_y < 0 && event.rel_y > this._show_size * this._drag_point_rate)) {
				return;
			}
			let offset = (this._bar_button.y + event.delta_y) / real_size;
			if (offset > 1) {
				offset = 1;
			} else if (offset < 0) {
				offset = 0;
			}
			if (this._offset_rate === offset) {
				return;
			}
			this._offset_rate = offset;
			this._bar_button.y = this._offset_rate * real_size;
		} else {
			if ((event.delta_x > 0 && event.rel_x < this._show_size * this._drag_point_rate) || (event.delta_x < 0 && event.rel_x > this._show_size * this._drag_point_rate)) {
				return;
			}
			let offset = (this._bar_button.x + event.delta_x) / real_size;
			if (offset > 1) {
				offset = 1;
			} else if (offset < 0) {
				offset = 0;
			}
			if (this._offset_rate === offset) {
				return;
			}
			this._offset_rate = offset;
			this._bar_button.x = this._offset_rate * real_size;
		}
		this.DispatchEvent(___all_struct.get(958494922), {});
	},
	RejustBarButton : function() {
		let real_size = this._center_size - this._show_size;
		if (this._type === ALittle.UIEnumTypes.TYPE_V) {
			if (this._bar_button !== undefined) {
				this._bar_button.x = 0;
				this._bar_button.width = this._width;
				this._bar_button.y = this._offset_rate * real_size;
				this._bar_button.height = this._show_size;
			}
			if (this._bar_background !== undefined) {
				this._bar_background.x = 0;
				this._bar_background.y = 0;
				this._bar_background.width = this._width;
				this._bar_background.height = this._center_size;
			}
		} else {
			if (this._bar_button !== undefined) {
				this._bar_button.x = this._offset_rate * real_size;
				this._bar_button.width = this._show_size;
				this._bar_button.y = 0;
				this._bar_button.height = this._height;
			}
			if (this._bar_background !== undefined) {
				this._bar_background.x = 0;
				this._bar_background.y = 0;
				this._bar_background.width = this._center_size;
				this._bar_background.height = this._height;
			}
		}
	},
}, "ALittle.ScrollBar");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


let __sin = ALittle.Math_Sin;
if (ALittle.DisplayGroup === undefined) throw new Error(" extends class:ALittle.DisplayGroup is undefined");
ALittle.ScrollScreen = JavaScript.Class(ALittle.DisplayGroup, {
	Ctor : function(ctrl_sys) {
		this._width = 0;
		this._height = 0;
		this._content_width = 0;
		this._content_height = 0;
		this._drag_rate = 0.2;
		this._open_extends_drag = false;
		this._drag_delta_x = 0;
		this._drag_delta_y = 0;
		this._scroll_view = ALittle.NewObject(ALittle.DisplayView, this._ctrl_sys);
		ALittle.DisplayGroup.AddChild.call(this, this._scroll_view);
		this._scroll_content = ALittle.NewObject(ALittle.DisplayGroup, this._ctrl_sys);
		this._scroll_view.AddChild(this._scroll_content);
		this._pickup_rect = true;
		this._pickup_child = true;
		this._pickup_this = true;
		this._can_scroll = true;
		this.AddEventListener(___all_struct.get(-1737121315), this, this.HandleMButtonWheel);
		this.AddEventListener(___all_struct.get(1337289812), this, this.HandleDrag);
		this.AddEventListener(___all_struct.get(150587926), this, this.HandleDragEnd);
		this.AddEventListener(___all_struct.get(1301789264), this, this.HandleDragBegin);
	},
	HandleMButtonWheel : function(event) {
		if (this._bottom_scroll_bar !== undefined && event.delta_x !== 0) {
			this._bottom_scroll_bar.offset_rate = this._bottom_scroll_bar.offset_rate - 0.1 * event.delta_x;
		}
		if (this._right_scroll_bar !== undefined && event.delta_y !== 0) {
			let offset = this._content_height * 0.1 * event.delta_y;
			if (offset > 40) {
				offset = 40;
			} else if (offset < -40) {
				offset = -40;
			}
			if (offset !== 0) {
				this._right_scroll_bar.offset_rate = this._right_scroll_bar.offset_rate - offset / this._content_height;
			}
		}
		this.RejustScrollBar();
	},
	get open_extends_drag() {
		return this._open_extends_drag;
	},
	set open_extends_drag(value) {
		this._open_extends_drag = value;
	},
	get container() {
		return this._scroll_content;
	},
	get view() {
		return this._scroll_view;
	},
	set container(value) {
		if (value === undefined) {
			value = ALittle.NewObject(ALittle.DisplayGroup, this._ctrl_sys);
		}
		let child_list = [];
		let child_list_count = 0;
		let old_child_list = this._scroll_content.childs;
		let ___OBJECT_1 = old_child_list;
		for (let k = 1; k <= ___OBJECT_1.length; ++k) {
			let v = ___OBJECT_1[k - 1];
			if (v === undefined) break;
			++ child_list_count;
			child_list[child_list_count - 1] = v;
		}
		this._scroll_content.RemoveEventListener(___all_struct.get(-431205740), this, this.HandleContainerResize);
		this._scroll_view.RemoveChild(this._scroll_content);
		this._scroll_content = value;
		let ___OBJECT_2 = child_list;
		for (let k = 1; k <= ___OBJECT_2.length; ++k) {
			let v = ___OBJECT_2[k - 1];
			if (v === undefined) break;
			value.AddChild(v);
		}
		this._scroll_content.AddEventListener(___all_struct.get(-431205740), this, this.HandleContainerResize);
		this._scroll_view.AddChild(this._scroll_content, 1);
		this.RejustScrollBar();
	},
	SetContainer : function(value) {
		if (value === undefined) {
			value = ALittle.NewObject(ALittle.DisplayGroup, this._ctrl_sys);
		}
		this._scroll_content.RemoveEventListener(___all_struct.get(-431205740), this, this.HandleContainerResize);
		this._scroll_view.RemoveChild(this._scroll_content);
		this._scroll_content = value;
		this._scroll_content.AddEventListener(___all_struct.get(-431205740), this, this.HandleContainerResize);
		this._scroll_view.AddChild(this._scroll_content, 1);
		this.RejustScrollBar();
	},
	set container_y(value) {
		if (this._scroll_content === undefined) {
			return;
		}
		this._scroll_content.y = value;
		this.YScrollBarChange();
		this.RejustScrollBar();
	},
	get container_y() {
		if (this._scroll_content === undefined) {
			return 0;
		}
		return this._scroll_content.y;
	},
	set container_x(value) {
		if (this._scroll_content === undefined) {
			return;
		}
		this._scroll_content.x = value;
		this.XScrollBarChange();
		this.RejustScrollBar();
	},
	get container_x() {
		if (this._scroll_content === undefined) {
			return 0;
		}
		return this._scroll_content.x;
	},
	get static_object_h() {
		return this._static_object_h;
	},
	set static_object_h(value) {
		if (this._static_object_h === value) {
			return;
		}
		this._scroll_view.RemoveChild(this._static_object_h);
		this._static_object_h = value;
		if (this._static_object_h === undefined) {
			return;
		}
		this._scroll_view.AddChild(this._static_object_h, 3);
		this._static_object_h.y = 0;
		this._static_object_h.x = this._scroll_content.x;
	},
	get static_object_v() {
		return this._static_object_v;
	},
	set static_object_v(value) {
		if (this._static_object_v === value) {
			return;
		}
		this._scroll_view.RemoveChild(this._static_object_v);
		this._static_object_v = value;
		if (this._static_object_v === undefined) {
			return;
		}
		this._scroll_view.AddChild(this._static_object_v, 2);
		this._static_object_v.y = this._scroll_content.y;
		this._static_object_v.x = 0;
	},
	get static_object_hv() {
		return this._static_object_hv;
	},
	set static_object_hv(value) {
		if (this._static_object_hv === value) {
			return;
		}
		this._scroll_view.RemoveChild(this._static_object_hv);
		this._static_object_hv = value;
		if (this._static_object_hv === undefined) {
			return;
		}
		this._scroll_view.AddChild(this._static_object_hv, 3);
		this._static_object_hv.y = 0;
		this._static_object_hv.x = 0;
	},
	GetChildIndex : function(child) {
		return this._scroll_content.GetChildIndex(child);
	},
	SetChildIndex : function(child, index) {
		return this._scroll_content.SetChildIndex(child, index);
	},
	GetChildByIndex : function(index) {
		return this._scroll_content.GetChildByIndex(index);
	},
	get childs() {
		return this._scroll_content.childs;
	},
	get child_count() {
		return this._scroll_content.child_count;
	},
	AddChild : function(child, index) {
		if (child === undefined) {
			return false;
		}
		if (this._scroll_content.AddChild(child, index) === false) {
			return false;
		}
		this.RejustScrollBar();
		return true;
	},
	RemoveChild : function(child) {
		if (child === undefined) {
			return false;
		}
		if (this._scroll_content.RemoveChild(child) === false) {
			return false;
		}
		this.RejustScrollBar();
		return true;
	},
	HasChild : function(child) {
		return this._scroll_content.HasChild(child);
	},
	RemoveAllChild : function() {
		A_LoopSystem.RemoveUpdater(this._drag_loop_x);
		A_LoopSystem.RemoveUpdater(this._drag_loop_y);
		A_LoopSystem.RemoveUpdater(this._drag_delta_loop_x);
		A_LoopSystem.RemoveUpdater(this._drag_delta_loop_y);
		A_LoopSystem.RemoveUpdater(this._x_type_dispatch);
		A_LoopSystem.RemoveUpdater(this._y_type_dispatch);
		this._scroll_content.RemoveAllChild();
		this.RejustScrollBar();
	},
	set width(value) {
		if (this._width === value) {
			return;
		}
		this._width = value;
		if (this._width_type === ALittle.UIEnumTypes.SIZE_ABS) {
			this._width_value = this._width;
		}
		let width = 0.0;
		if (this._right_scroll_bar !== undefined) {
			width = this._right_scroll_bar.width;
		}
		let remain_width = this._width - width;
		if (remain_width < 0) {
			this._scroll_view.width = this._width;
			if (this._right_scroll_bar !== undefined) {
				this._right_scroll_bar.visible = false;
				this._right_scroll_bar.x = this._width;
				this._right_scroll_bar.y = 0;
			}
		} else {
			this._scroll_view.width = remain_width;
			if (this._right_scroll_bar !== undefined) {
				this._right_scroll_bar.visible = true;
				this._right_scroll_bar.x = remain_width;
				this._right_scroll_bar.y = 0;
			}
		}
		if (this._right_scroll_bar !== undefined) {
			this._right_scroll_bar.height = this._scroll_view.height;
		}
		if (this._bottom_scroll_bar !== undefined) {
			let rate = this._bottom_scroll_bar.offset_rate;
			if (this._content_width < this._scroll_view.width) {
				rate = 0;
			}
			this._bottom_scroll_bar.width = this._scroll_view.width;
			this._bottom_scroll_bar.total_size = this._content_width;
			this._bottom_scroll_bar.show_size = this._scroll_view.width;
			this._bottom_scroll_bar.offset_rate = rate;
			this._bottom_scroll_bar.offset_step = 0.1;
			let x = 0.0;
			let content_width = this._content_width;
			if (content_width > this._scroll_view.width) {
				let total_width = content_width - this._scroll_view.width;
				x = -total_width * rate;
			}
			this._scroll_content.x = x;
			if (this._static_object_h !== undefined) {
				this._static_object_h.x = x;
			}
		}
	},
	set height(value) {
		if (this._height === value) {
			return;
		}
		this._height = value;
		if (this._height_type === ALittle.UIEnumTypes.SIZE_ABS) {
			this._height_value = this._height;
		}
		let height = 0.0;
		if (this._bottom_scroll_bar !== undefined) {
			height = this._bottom_scroll_bar.height;
		}
		let remain_height = this._height - height;
		if (remain_height < 0) {
			this._scroll_view.height = this._height;
			if (this._bottom_scroll_bar !== undefined) {
				this._bottom_scroll_bar.visible = false;
				this._bottom_scroll_bar.y = this._height;
			}
		} else {
			this._scroll_view.height = remain_height;
			if (this._bottom_scroll_bar !== undefined) {
				this._bottom_scroll_bar.visible = true;
				this._bottom_scroll_bar.y = remain_height;
			}
		}
		if (this._bottom_scroll_bar !== undefined) {
			this._bottom_scroll_bar.width = this._scroll_view.width;
		}
		if (this._right_scroll_bar !== undefined) {
			let rate = this._right_scroll_bar.offset_rate;
			if (this._content_height < this._scroll_view.height) {
				rate = 0;
			}
			this._right_scroll_bar.height = this._scroll_view.height;
			this._right_scroll_bar.total_size = this._content_height;
			this._right_scroll_bar.show_size = this._scroll_view.height;
			this._right_scroll_bar.offset_rate = rate;
			this._right_scroll_bar.offset_step = 0.1;
			let y = 0.0;
			let content_height = this._content_height;
			if (content_height > this._scroll_view.height) {
				let total_height = content_height - this._scroll_view.height;
				y = -total_height * rate;
			}
			this._scroll_content.y = y;
			if (this._static_object_v !== undefined) {
				this._static_object_v.y = y;
			}
		}
	},
	get view_width() {
		return this._scroll_view.width;
	},
	get view_height() {
		return this._scroll_view.height;
	},
	set right_scrollbar(value) {
		if (this._right_scroll_bar !== undefined) {
			ALittle.DisplayGroup.RemoveChild.call(this, this._right_scroll_bar);
			this._right_scroll_bar.RemoveEventListener(___all_struct.get(958494922), this, this.HandleRightScrollBarChange);
		}
		this._right_scroll_bar = value;
		let width = 0.0;
		if (this._right_scroll_bar !== undefined) {
			this._right_scroll_bar.type = ALittle.UIEnumTypes.TYPE_V;
			width = this._right_scroll_bar.width;
			ALittle.DisplayGroup.AddChild.call(this, this._right_scroll_bar);
			this._right_scroll_bar.AddEventListener(___all_struct.get(958494922), this, this.HandleRightScrollBarChange);
			this._right_scroll_bar.height = this._scroll_view.height;
			this._right_scroll_bar.y = 0;
		}
		let remain_width = this._width - width;
		if (remain_width < 0) {
			this._scroll_view.width = this._width;
			if (this._right_scroll_bar !== undefined) {
				this._right_scroll_bar.visible = false;
				this._right_scroll_bar.x = this._width;
			}
		} else {
			this._scroll_view.width = remain_width;
			if (this._right_scroll_bar !== undefined) {
				this._right_scroll_bar.visible = true;
				this._right_scroll_bar.x = remain_width;
			}
		}
		if (this._right_scroll_bar !== undefined) {
			this._right_scroll_bar.total_size = this._content_height;
			this._right_scroll_bar.show_size = this._scroll_view.height;
			this._right_scroll_bar.offset_rate = 0;
			this._right_scroll_bar.offset_step = 0.1;
		}
		if (this._bottom_scroll_bar !== undefined) {
			let rate = this._bottom_scroll_bar.offset_rate;
			if (this._content_width < this._scroll_view.width) {
				rate = 0;
			}
			this._bottom_scroll_bar.width = this._scroll_view.width;
			this._bottom_scroll_bar.total_size = this._content_width;
			this._bottom_scroll_bar.show_size = this._scroll_view.width;
			this._bottom_scroll_bar.offset_rate = rate;
			this._bottom_scroll_bar.offset_step = 0.1;
		}
	},
	get right_scrollbar() {
		return this._right_scroll_bar;
	},
	ScrollToBottom : function() {
		if (this._right_scroll_bar === undefined) {
			return;
		}
		this._right_scroll_bar.offset_rate = 1;
		this._right_scroll_bar.DispatchEvent(___all_struct.get(958494922), {});
	},
	ScrollToRight : function() {
		if (this._bottom_scroll_bar === undefined) {
			return;
		}
		this._bottom_scroll_bar.offset_rate = 1;
		this._bottom_scroll_bar.DispatchEvent(___all_struct.get(958494922), {});
	},
	set bottom_scrollbar(value) {
		if (this._bottom_scroll_bar !== undefined) {
			ALittle.DisplayGroup.RemoveChild.call(this, this._bottom_scroll_bar);
			this._bottom_scroll_bar.RemoveEventListener(___all_struct.get(958494922), this, this.HandleBottomScrollBarChange);
		}
		this._bottom_scroll_bar = value;
		let height = 0.0;
		if (this._bottom_scroll_bar !== undefined) {
			this._bottom_scroll_bar.type = ALittle.UIEnumTypes.TYPE_H;
			height = this._bottom_scroll_bar.height;
			ALittle.DisplayGroup.AddChild.call(this, this._bottom_scroll_bar);
			this._bottom_scroll_bar.AddEventListener(___all_struct.get(958494922), this, this.HandleBottomScrollBarChange);
			this._bottom_scroll_bar.width = this._scroll_view.width;
			this._bottom_scroll_bar.x = 0;
		}
		let remain_height = this._height - height;
		if (remain_height < 0) {
			this._scroll_view.height = this._height;
			if (this._bottom_scroll_bar !== undefined) {
				this._bottom_scroll_bar.visible = false;
				this._bottom_scroll_bar.y = this._height;
			}
		} else {
			this._scroll_view.height = remain_height;
			if (this._bottom_scroll_bar !== undefined) {
				this._bottom_scroll_bar.visible = true;
				this._bottom_scroll_bar.y = remain_height;
			}
		}
		if (this._bottom_scroll_bar !== undefined) {
			this._bottom_scroll_bar.total_size = this._content_width;
			this._bottom_scroll_bar.show_size = this._scroll_view.width;
			this._bottom_scroll_bar.offset_rate = 0;
			this._bottom_scroll_bar.offset_step = 0.1;
		}
		if (this._right_scroll_bar !== undefined) {
			let rate = this._right_scroll_bar.offset_rate;
			if (this._content_height < this._scroll_view.height) {
				rate = 0;
			}
			this._right_scroll_bar.height = this._scroll_view.height;
			this._right_scroll_bar.total_size = this._content_height;
			this._right_scroll_bar.show_size = this._scroll_view.height;
			this._right_scroll_bar.offset_rate = rate;
			this._right_scroll_bar.offset_step = 0.1;
		}
	},
	get bottom_scrollbar() {
		return this._bottom_scroll_bar;
	},
	RejustScrollBar : function() {
		this._content_width = this._scroll_content.max_right;
		if (this._static_object_h !== undefined) {
			if (this._static_object_h.width > this._content_width) {
				this._content_width = this._static_object_h.width;
			}
		}
		this._content_height = this._scroll_content.max_bottom;
		if (this._bottom_scroll_bar !== undefined) {
			let rate = this._bottom_scroll_bar.offset_rate;
			if (this._content_width < this._scroll_view.width) {
				rate = 0;
			}
			this._bottom_scroll_bar.total_size = this._content_width;
			this._bottom_scroll_bar.show_size = this._scroll_view.width;
			this._bottom_scroll_bar.offset_rate = rate;
			this._bottom_scroll_bar.offset_step = 0.1;
			this.HandleBottomScrollBarChange(undefined);
		}
		if (this._right_scroll_bar !== undefined) {
			let rate = this._right_scroll_bar.offset_rate;
			if (this._content_height < this._scroll_view.height) {
				rate = 0;
			}
			this._right_scroll_bar.height = this._scroll_view.height;
			this._right_scroll_bar.total_size = this._content_height;
			this._right_scroll_bar.show_size = this._scroll_view.height;
			this._right_scroll_bar.offset_rate = rate;
			this._right_scroll_bar.offset_step = 0.1;
			this.HandleRightScrollBarChange(undefined);
		}
	},
	HandleRightScrollBarChange : function(event) {
		let rate = this._right_scroll_bar.offset_rate;
		let y = 0.0;
		let content_height = this._content_height;
		if (content_height > this._scroll_view.height) {
			let total_height = content_height - this._scroll_view.height;
			y = -total_height * rate;
		}
		this._scroll_content.y = y;
		if (this._static_object_v !== undefined) {
			this._static_object_v.y = y;
		}
	},
	HandleBottomScrollBarChange : function(event) {
		let rate = this._bottom_scroll_bar.offset_rate;
		let x = 0.0;
		let content_width = this._content_width;
		if (content_width > this._scroll_view.width) {
			let total_width = content_width - this._scroll_view.width;
			x = -total_width * rate;
		}
		this._scroll_content.x = x;
		if (this._static_object_h !== undefined) {
			this._static_object_h.x = x;
		}
	},
	HandleContainerResize : function(event) {
		this.RejustScrollBar();
	},
	HandleDragBegin : function(event) {
	},
	HandleDrag : function(event) {
		this._drag_delta_x = event.delta_x;
		this._drag_delta_y = event.delta_y;
		this._content_width = this._scroll_content.max_right;
		if (this._static_object_h !== undefined) {
			if (this._static_object_h.width > this._content_width) {
				this._content_width = this._static_object_h.width;
			}
		}
		this._content_height = this._scroll_content.max_bottom;
		if (event.delta_x !== 0 && this._bottom_scroll_bar !== undefined) {
			if (event.delta_x > 0) {
				let min_x = 0.0;
				let max_x = this._scroll_view.width * this._drag_rate;
				let x = this._scroll_content.x;
				if (x > min_x) {
					x = x + event.delta_x * __sin((1 - x / (this._scroll_view.width * this._drag_rate)) * 1.57);
					if (x > max_x) {
						x = max_x;
					}
				} else {
					x = x + event.delta_x;
				}
				if (this._open_extends_drag === false && x > min_x) {
					x = min_x;
				}
				this._scroll_content.x = x;
				if (this._static_object_h !== undefined) {
					this._static_object_h.x = x;
				}
				if (this._bottom_scroll_bar !== undefined) {
					this._bottom_scroll_bar.offset_rate = -x / (this._content_width - this._scroll_view.width);
				}
			} else {
				let x = this._scroll_content.x;
				if (this._content_width < this._scroll_view.width) {
					x = x + event.delta_x;
					if (x < 0) {
						x = 0;
					}
				} else {
					let max_x = -this._content_width + this._scroll_view.width;
					let min_x = max_x - this._scroll_view.width * this._drag_rate;
					if (x < max_x) {
						x = x + event.delta_x * __sin((x - min_x) / (this._scroll_view.width * this._drag_rate) * 1.57);
						if (x < min_x) {
							x = min_x;
						}
					} else {
						x = x + event.delta_x;
					}
					if (this._open_extends_drag === false && x < max_x) {
						x = max_x;
					}
				}
				this._scroll_content.x = x;
				if (this._static_object_h !== undefined) {
					this._static_object_h.x = x;
				}
				if (this._bottom_scroll_bar !== undefined) {
					this._bottom_scroll_bar.offset_rate = -x / (this._content_width - this._scroll_view.width);
				}
			}
		}
		if (event.delta_y !== 0 && this._right_scroll_bar !== undefined) {
			if (event.delta_y > 0) {
				let min_y = 0.0;
				let max_y = this._scroll_view.height * this._drag_rate;
				let y = this._scroll_content.y;
				if (y > min_y) {
					y = y + event.delta_y * __sin((1 - y / (this._scroll_view.height * this._drag_rate)) * 1.57);
					if (y > max_y) {
						y = max_y;
					}
				} else {
					y = y + event.delta_y;
				}
				if (this._open_extends_drag === false && y > min_y) {
					y = min_y;
				}
				this._scroll_content.y = y;
				if (this._static_object_v !== undefined) {
					this._static_object_v.y = y;
				}
				if (this._right_scroll_bar !== undefined) {
					this._right_scroll_bar.offset_rate = -y / (this._content_height - this._scroll_view.height);
				}
			} else {
				let y = this._scroll_content.y;
				if (this._content_height < this._scroll_view.height) {
					y = y + event.delta_y;
					if (y < 0) {
						y = 0;
					}
				} else {
					let max_y = -this._content_height + this._scroll_view.height;
					let min_y = max_y - this._scroll_view.height * this._drag_rate;
					if (y < max_y) {
						y = y + event.delta_y * __sin((y - min_y) / (this._scroll_view.height * this._drag_rate) * 1.57);
						if (y < min_y) {
							y = min_y;
						}
					} else {
						y = y + event.delta_y;
					}
					if (this._open_extends_drag === false && y < max_y) {
						y = max_y;
					}
				}
				this._scroll_content.y = y;
				if (this._static_object_v !== undefined) {
					this._static_object_v.y = y;
				}
				if (this._right_scroll_bar !== undefined) {
					this._right_scroll_bar.offset_rate = -y / (this._content_height - this._scroll_view.height);
				}
			}
		}
	},
	HandleDragEnd : function(event) {
		this._content_width = this._scroll_content.max_right;
		if (this._static_object_h !== undefined) {
			if (this._static_object_h.width > this._content_width) {
				this._content_width = this._static_object_h.width;
			}
		}
		this._content_height = this._scroll_content.max_bottom;
		if (this._scroll_content.x > 0) {
			if (this._scroll_content.x >= this._scroll_view.width * this._drag_rate * 0.9) {
				this.DispatchEvent(___all_struct.get(-839083637), {});
			}
			let func = undefined;
			if (this._static_object_h !== undefined) {
				func = ALittle.ScrollScreen.XStaticObjectChange.bind(this);
			}
			A_LoopSystem.RemoveUpdater(this._drag_loop_x);
			this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_content, "x", 0, 200, 0, func);
			A_LoopSystem.AddUpdater(this._drag_loop_x);
		} else if (this._scroll_content.x < -this._content_width + this._scroll_view.width) {
			if (this._scroll_content.x <= -this._content_width + this._scroll_view.width - this._scroll_view.width * this._drag_rate * 0.9) {
				this.DispatchEvent(___all_struct.get(-567702959), {});
			}
			if (this._scroll_content.x < 0) {
				let func = undefined;
				if (this._static_object_h !== undefined) {
					func = ALittle.ScrollScreen.XStaticObjectChange.bind(this);
				}
				A_LoopSystem.RemoveUpdater(this._drag_loop_x);
				this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_content, "x", -this._content_width + this._scroll_view.width, 200, 0, func);
				A_LoopSystem.AddUpdater(this._drag_loop_x);
			}
		} else if (this._scroll_content.x !== 0 && this._scroll_content.x !== -this._content_width + this._scroll_view.width) {
			let target_x = this._scroll_content.x + this._drag_delta_x * 10;
			let event_dispatch = undefined;
			if (this._drag_delta_x < 0) {
				let max_x = -this._content_width + this._scroll_view.width;
				let min_x = max_x - this._scroll_view.width * this._drag_rate;
				if (target_x < min_x) {
					target_x = min_x;
					event_dispatch = ALittle.ScrollScreen.ScrollDispatchDragLeftEvent.bind(this);
				}
				if (target_x >= min_x && target_x <= max_x) {
					let func = undefined;
					if (this._static_object_h !== undefined) {
						func = ALittle.ScrollScreen.XStaticObjectChange.bind(this);
					}
					A_LoopSystem.RemoveUpdater(this._drag_loop_x);
					this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_content, "x", -this._content_width + this._scroll_view.width, 200, 300, func);
					A_LoopSystem.AddUpdater(this._drag_loop_x);
				}
			} else if (this._drag_delta_x > 0) {
				let max_x = this._scroll_view.width * this._drag_rate;
				let min_x = 0;
				if (target_x > max_x) {
					target_x = max_x;
					event_dispatch = ALittle.ScrollScreen.ScrollDispatchDragRightEvent.bind(this);
				}
				if (target_x >= min_x && target_x <= max_x) {
					let func = undefined;
					if (this._static_object_h !== undefined) {
						func = ALittle.ScrollScreen.XStaticObjectChange.bind(this);
					}
					A_LoopSystem.RemoveUpdater(this._drag_loop_x);
					this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_content, "x", 0, 200, 300, func);
					A_LoopSystem.AddUpdater(this._drag_loop_x);
				}
			}
			let func = undefined;
			if (this._static_object_h !== undefined && this._bottom_scroll_bar === undefined) {
				func = ALittle.ScrollScreen.XStaticObjectChange.bind(this);
			} else if (this._static_object_h === undefined && this._bottom_scroll_bar !== undefined) {
				func = ALittle.ScrollScreen.XScrollBarChange.bind(this);
			} else if (this._static_object_h !== undefined && this._bottom_scroll_bar !== undefined) {
				func = ALittle.ScrollScreen.XStaticObjectAndScrollBarChange.bind(this);
			}
			A_LoopSystem.RemoveUpdater(this._x_type_dispatch);
			if (event_dispatch !== undefined) {
				this._x_type_dispatch = ALittle.NewObject(ALittle.LoopFunction, event_dispatch, 1, 0, 300);
				A_LoopSystem.AddUpdater(this._x_type_dispatch);
			}
			if (this._open_extends_drag === false) {
				if (target_x > 0) {
					target_x = 0;
				} else if (target_x < -this._content_width + this._scroll_view.width) {
					target_x = -this._content_width + this._scroll_view.width;
				}
			}
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_x);
			this._drag_delta_loop_x = ALittle.NewObject(ALittle.LoopRit, this._scroll_content, "x", target_x, 300, 0, func);
			A_LoopSystem.AddUpdater(this._drag_delta_loop_x);
		}
		if (this._scroll_content.y > 0) {
			if (this._scroll_content.y >= this._scroll_view.height * this._drag_rate * 0.9) {
				this.DispatchEvent(___all_struct.get(1848466169), {});
			}
			let func = undefined;
			if (this._static_object_v !== undefined) {
				func = ALittle.ScrollScreen.YStaticObjectChange.bind(this);
			}
			A_LoopSystem.RemoveUpdater(this._drag_loop_y);
			this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_content, "y", 0, 200, 0, func);
			A_LoopSystem.AddUpdater(this._drag_loop_y);
		} else if (this._scroll_content.y < -this._content_height + this._scroll_view.height) {
			if (this._scroll_content.y <= -this._content_height + this._scroll_view.height - this._scroll_view.height * this._drag_rate * 0.9) {
				this.DispatchEvent(___all_struct.get(809518110), {});
			}
			if (this._scroll_content.y < 0) {
				let func = undefined;
				if (this._static_object_v !== undefined) {
					func = ALittle.ScrollScreen.YStaticObjectChange.bind(this);
				}
				A_LoopSystem.RemoveUpdater(this._drag_loop_y);
				this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_content, "y", -this._content_height + this._scroll_view.height, 200, 0, func);
				A_LoopSystem.AddUpdater(this._drag_loop_y);
			}
		} else if (this._scroll_content.y !== 0 && this._scroll_content.y !== -this._content_height + this._scroll_view.height) {
			let event_dispatch = undefined;
			let target_y = this._scroll_content.y + this._drag_delta_y * 10;
			if (this._drag_delta_y < 0) {
				let max_y = -this._content_height + this._scroll_view.height;
				let min_y = max_y - this._scroll_view.height * this._drag_rate;
				if (target_y < min_y) {
					target_y = min_y;
					event_dispatch = ALittle.ScrollScreen.ScrollDispatchDragUpEvent.bind(this);
				}
				if (target_y >= min_y && target_y <= max_y) {
					let func = undefined;
					if (this._static_object_v !== undefined) {
						func = ALittle.ScrollScreen.YStaticObjectChange.bind(this);
					}
					A_LoopSystem.RemoveUpdater(this._drag_loop_y);
					this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_content, "y", -this._content_height + this._scroll_view.height, 200, 300, func);
					A_LoopSystem.AddUpdater(this._drag_loop_y);
				}
			} else if (this._drag_delta_y > 0) {
				let max_y = this._scroll_view.height * this._drag_rate;
				let min_y = 0.0;
				if (target_y > max_y) {
					target_y = max_y;
					event_dispatch = ALittle.ScrollScreen.ScrollDispatchDragDownEvent.bind(this);
				}
				if (target_y >= min_y && target_y <= max_y) {
					let func = undefined;
					if (this._static_object_v !== undefined) {
						func = ALittle.ScrollScreen.YStaticObjectChange.bind(this);
					}
					A_LoopSystem.RemoveUpdater(this._drag_loop_y);
					this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_content, "y", 0, 200, 300, func);
					A_LoopSystem.AddUpdater(this._drag_loop_y);
				}
			}
			let func = undefined;
			if (this._static_object_v !== undefined && this._right_scroll_bar === undefined) {
				func = ALittle.ScrollScreen.YStaticObjectChange.bind(this);
			} else if (this._static_object_v === undefined && this._right_scroll_bar !== undefined) {
				func = ALittle.ScrollScreen.YScrollBarChange.bind(this);
			} else if (this._static_object_v !== undefined && this._right_scroll_bar !== undefined) {
				func = ALittle.ScrollScreen.YStaticObjectAndScrollBarChange.bind(this);
			}
			A_LoopSystem.RemoveUpdater(this._y_type_dispatch);
			if (event_dispatch !== undefined) {
				this._y_type_dispatch = ALittle.NewObject(ALittle.LoopFunction, event_dispatch, 1, 0, 300);
				A_LoopSystem.AddUpdater(this._y_type_dispatch);
			}
			if (this._open_extends_drag === false) {
				if (target_y > 0) {
					target_y = 0;
				} else if (target_y < -this._content_height + this._scroll_view.height) {
					target_y = -this._content_height + this._scroll_view.height;
				}
			}
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_y);
			this._drag_delta_loop_y = ALittle.NewObject(ALittle.LoopRit, this._scroll_content, "y", target_y, 300, 0, func);
			A_LoopSystem.AddUpdater(this._drag_delta_loop_y);
		}
		this._drag_delta_x = 0;
		this._drag_delta_y = 0;
	},
	XStaticObjectAndScrollBarChange : function() {
		this._static_object_h.x = this._scroll_content.x;
		this._bottom_scroll_bar.offset_rate = -this._scroll_content.x / (this._content_width - this._scroll_view.width);
	},
	XStaticObjectChange : function() {
		this._static_object_h.x = this._scroll_content.x;
	},
	YStaticObjectAndScrollBarChange : function() {
		this._static_object_v.y = this._scroll_content.y;
		this._right_scroll_bar.offset_rate = -this._scroll_content.y / (this._content_height - this._scroll_view.height);
	},
	YStaticObjectChange : function() {
		this._static_object_v.y = this._scroll_content.y;
	},
	XScrollBarChange : function() {
		this._bottom_scroll_bar.offset_rate = -this._scroll_content.x / (this._content_width - this._scroll_view.width);
	},
	YScrollBarChange : function() {
		this._right_scroll_bar.offset_rate = -this._scroll_content.y / (this._content_height - this._scroll_view.height);
	},
	ScrollDispatchDragDownEvent : function() {
		this.DispatchEvent(___all_struct.get(1848466169), {});
	},
	ScrollDispatchDragUpEvent : function() {
		this.DispatchEvent(___all_struct.get(809518110), {});
	},
	ScrollDispatchDragLeftEvent : function() {
		this.DispatchEvent(___all_struct.get(-567702959), {});
	},
	ScrollDispatchDragRightEvent : function() {
		this.DispatchEvent(___all_struct.get(-839083637), {});
	},
}, "ALittle.ScrollScreen");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1517533145, "ALittle.DialogDragEvent", {
name : "ALittle.DialogDragEvent", ns_name : "ALittle", rl_name : "DialogDragEvent", hash_code : 1517533145,
name_list : ["target","delta_x","delta_y"],
type_list : ["ALittle.DisplayObject","double","double"],
option_map : {}
})
ALittle.RegStruct(1971745271, "ALittle.DialogDragBeginEvent", {
name : "ALittle.DialogDragBeginEvent", ns_name : "ALittle", rl_name : "DialogDragBeginEvent", hash_code : 1971745271,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-1482649531, "ALittle.DialogDragEndEvent", {
name : "ALittle.DialogDragEndEvent", ns_name : "ALittle", rl_name : "DialogDragEndEvent", hash_code : -1482649531,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})

if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.Dialog = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._pickup_rect = true;
		this._pickup_child = true;
		this._title_text = "";
		this._head = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
		this._body = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
		this._grid3 = ALittle.NewObject(ALittle.Grid3, this._ctrl_sys);
		this._grid3.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
		this._grid3.width_value = 0;
		this._grid3.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
		this._grid3.height_value = 0;
		this._grid3.type = ALittle.UIEnumTypes.TYPE_V;
		this._grid3.show_up = this._head;
		this._grid3.show_center = this._body;
		ALittle.DisplayLayout.AddChild.call(this, this._grid3);
	},
	GetChildOffset : function() {
		return [0, this._grid3.up_size];
	},
	set head_size(value) {
		this._grid3.up_size = value;
		if (this._background !== undefined) {
			this._background.height_value = this._grid3.up_size;
		}
		if (this._close_button !== undefined) {
			this._close_button.x_value = (value - this._close_button.height) / 2;
		}
		if (this._title !== undefined) {
			this._title.x_value = (value - this._title.font_height);
		}
	},
	get head_size() {
		return this._grid3.up_size;
	},
	ResetHeadOrder : function() {
		let index = 1;
		if (this._head_drag !== undefined) {
			this._head.SetChildIndex(this._head_drag, index);
			++ index;
		}
		if (this._title !== undefined) {
			this._head.SetChildIndex(this._title, index);
			++ index;
		}
		if (this._close_button !== undefined) {
			this._head.SetChildIndex(this._close_button, index);
			++ index;
		}
	},
	set show_background(value) {
		if (this._background !== undefined) {
			ALittle.DisplayLayout.RemoveChild.call(this, this._background);
		}
		this._background = value;
		if (this._background !== undefined) {
			this._background.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._background.width_value = 0;
			this._background.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._background.height_value = this._grid3.up_size;
			this._background.y_type = ALittle.UIEnumTypes.POS_ALIGN_ENDING;
			ALittle.DisplayLayout.AddChild.call(this, this._background, 1);
			this.ResetHeadOrder();
		}
	},
	get show_background() {
		return this._background;
	},
	set show_head_drag(value) {
		if (this._head_drag !== undefined) {
			this._head.RemoveChild(this._head_drag);
			this._head_drag.RemoveEventListener(___all_struct.get(1301789264), this, this.HandleHeadDragBegin);
			this._head_drag.RemoveEventListener(___all_struct.get(1337289812), this, this.HandleHeadDrag);
			this._head_drag.RemoveEventListener(___all_struct.get(150587926), this, this.HandleHeadDragEnd);
		}
		this._head_drag = value;
		if (this._head_drag !== undefined) {
			this._head_drag.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._head_drag.width_value = 0;
			this._head_drag.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._head_drag.height_value = 0;
			this._head.AddChild(this._head_drag);
			this.ResetHeadOrder();
			this._head_drag.AddEventListener(___all_struct.get(1301789264), this, this.HandleHeadDragBegin);
			this._head_drag.AddEventListener(___all_struct.get(1337289812), this, this.HandleHeadDrag);
			this._head_drag.AddEventListener(___all_struct.get(150587926), this, this.HandleHeadDragEnd);
		}
	},
	get show_head_drag() {
		return this._head_drag;
	},
	set show_title(value) {
		if (this._title !== undefined) {
			this._title_text = this._title.text;
			this._head.RemoveChild(this._title);
		}
		this._title = value;
		if (this._title !== undefined) {
			this._title.text = this._title_text;
			this._title.disabled = true;
			this._title.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
			this._title.y_value = 0;
			this._head.AddChild(this._title);
			this._title.x_type = ALittle.UIEnumTypes.POS_ABS;
			this._title.x_value = (this._grid3.up_size - this._title.font_height);
			this.ResetHeadOrder();
		}
	},
	get show_title() {
		return this._title;
	},
	set title(value) {
		this._title_text = value;
		if (this._title !== undefined) {
			this._title.text = value;
		}
	},
	get title() {
		if (this._title !== undefined) {
			return this._title.text;
		}
		return this._title_text;
	},
	set show_close_button(value) {
		if (this._close_button !== undefined) {
			this._head.RemoveChild(this._close_button);
			this._close_button.RemoveEventListener(___all_struct.get(-449066808), this, this.HandleCloseButtonClicked);
		}
		this._close_button = value;
		if (this._close_button !== undefined) {
			this._close_button.y_value = 0;
			this._close_button.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
			this._head.AddChild(this._close_button);
			this._close_button.x_type = ALittle.UIEnumTypes.POS_ALIGN_ENDING;
			this._close_button.x_value = (this._grid3.up_size - this._close_button.height) / 2;
			this.ResetHeadOrder();
			this._close_button.AddEventListener(___all_struct.get(-449066808), this, this.HandleCloseButtonClicked);
		}
	},
	get show_close_button() {
		return this._close_button;
	},
	set close_callback(value) {
		this._close_callback = value;
	},
	get close_callback() {
		return this._close_callback;
	},
	HandleCloseButtonClicked : function(event) {
		this.visible = false;
		if (this._close_callback !== undefined) {
			this._close_callback();
		}
	},
	HandleHeadDragBegin : function(event) {
		this.DispatchEvent(___all_struct.get(1971745271), {});
	},
	HandleHeadDrag : function(event) {
		this.x = this.x + (event.delta_x);
		this.y = this.y + (event.delta_y);
		let new_event = {};
		new_event.target = this;
		new_event.delta_x = event.delta_x;
		new_event.delta_y = event.delta_y;
		this.DispatchEvent(___all_struct.get(1517533145), new_event);
	},
	HandleHeadDragEnd : function(event) {
		this.DispatchEvent(___all_struct.get(-1482649531), {});
	},
	GetChildIndex : function(child) {
		return this._body.GetChildIndex(child);
	},
	SetChildIndex : function(child, index) {
		return this._body.SetChildIndex(child, index);
	},
	GetChildByIndex : function(index) {
		return this._body.GetChildByIndex(index);
	},
	GetChildIndex : function(child) {
		return this._body.GetChildIndex(child);
	},
	get childs() {
		return this._body.childs;
	},
	get child_count() {
		return this._body.child_count;
	},
	AddChild : function(child, index) {
		if (child === undefined || child === this) {
			return false;
		}
		if (child._show_parent === this._body || child._logic_parent === this) {
			return true;
		}
		if (child._logic_parent !== undefined) {
			child._logic_parent.RemoveChild(child);
		} else if (child._show_parent !== undefined) {
			child._show_parent.RemoveChild(child);
		}
		let result = this._body.AddChild(child, index);
		child._logic_parent = this;
		return result;
	},
	RemoveChild : function(child) {
		if (child === undefined) {
			return false;
		}
		if (child._show_parent !== this._body && child._logic_parent !== this) {
			return false;
		}
		let index = this._body.GetChildIndex(child);
		if (index === 0) {
			return false;
		}
		return this._body.RemoveChild(child);
	},
	HasChild : function(child) {
		return this._body.HasChild(child);
	},
	RemoveAllChild : function() {
		this._body.RemoveAllChild();
	},
}, "ALittle.Dialog");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


let __ceil = ALittle.Math_Ceil;
if (ALittle.DisplayGroup === undefined) throw new Error(" extends class:ALittle.DisplayGroup is undefined");
ALittle.TileTable = JavaScript.Class(ALittle.DisplayGroup, {
	Ctor : function(ctrl_sys) {
		this._x_gap = 0;
		this._y_gap = 0;
		this._x_start_gap = 0;
		this._y_start_gap = 0;
		this._col_count = 1;
		this._clip_left_index = 0;
		this._clip_right_index = 0;
		this._clip_top_index = 0;
		this._clip_bottom_index = 0;
		this._show_child_map = ALittle.CreateKeyWeakMap();
		this._pickup_rect = false;
		this._pickup_child = true;
		this._width = 0;
		this._height = 0;
	},
	get width() {
		return this._width;
	},
	get height() {
		return this._height;
	},
	set x_start_gap(value) {
		if (this._x_start_gap === value) {
			return;
		}
		this._x_start_gap = value;
		this.Layout(1);
	},
	get x_start_gap() {
		return this._x_start_gap;
	},
	set y_start_gap(value) {
		if (this._y_start_gap === value) {
			return;
		}
		this._y_start_gap = value;
		this.Layout(1);
	},
	get y_start_gap() {
		return this._y_start_gap;
	},
	set x_gap(value) {
		if (this._x_gap === value) {
			return;
		}
		this._x_gap = value;
		this.Layout(1);
	},
	get x_gap() {
		return this._x_gap;
	},
	set y_gap(value) {
		if (this._y_gap === value) {
			return;
		}
		this._y_gap = value;
		this.Layout(1);
	},
	get y_gap() {
		return this._y_gap;
	},
	set col_count(value) {
		if (value <= 0 || this._col_count === value) {
			return;
		}
		this._col_count = value;
		this.Layout(1);
	},
	get col_count() {
		return this._col_count;
	},
	AddChild : function(child, index) {
		let result = ALittle.DisplayGroup.AddChild.call(this, child, index);
		if (result === false) {
			return false;
		}
		if (index === undefined) {
			this.Layout(this.child_count);
		} else {
			this.Layout(index);
		}
		child.AddEventListener(___all_struct.get(-431205740), this, this.HandleChildResize);
		return true;
	},
	RemoveChild : function(child) {
		let child_index = this.GetChildIndex(child);
		if (child_index === 0) {
			return false;
		}
		let result = ALittle.DisplayGroup.RemoveChild.call(this, child);
		if (result === false) {
			return false;
		}
		this._show_child_map.delete(child);
		child.RemoveEventListener(___all_struct.get(-431205740), this);
		this.Layout(child_index);
		return true;
	},
	RemoveAllChild : function() {
		let ___OBJECT_1 = this._childs;
		for (let k = 1; k <= ___OBJECT_1.length; ++k) {
			let child = ___OBJECT_1[k - 1];
			if (child === undefined) break;
			child.RemoveEventListener(___all_struct.get(-431205740), this);
		}
		this._show_child_map = ALittle.CreateKeyWeakMap();
		this._clip_left_index = 0;
		this._clip_right_index = 0;
		this._clip_top_index = 0;
		this._clip_bottom_index = 0;
		ALittle.DisplayGroup.RemoveAllChild.call(this);
	},
	SetChildIndex : function(child, index) {
		let result = ALittle.DisplayGroup.SetChildIndex.call(this, child, index);
		this.Layout(1);
		return result;
	},
	Layout : function(index) {
		let child_count = this.child_count;
		if (child_count === 0) {
			this._width = 0;
			this._height = 0;
			return;
		}
		if (index > child_count) {
			index = child_count;
		}
		let child_list = this.childs;
		let start_index = 1;
		let start_x = this._x_start_gap;
		let start_y = this._y_start_gap;
		if (index > 1) {
			start_index = index;
			let current_child = child_list[index - 1 - 1];
			if ((index - 1) % this._col_count === 0) {
				start_x = this._x_start_gap;
				start_y = current_child.y + current_child.height + this._y_gap;
			} else {
				start_x = current_child.x + current_child.width + this._x_gap;
				start_y = current_child.y;
			}
		}
		for (let i = start_index; i <= child_count; i += 1) {
			child_list[i - 1].x = start_x;
			child_list[i - 1].y = start_y;
			if (i % this._col_count === 0) {
				start_x = this._x_start_gap;
				start_y = start_y + child_list[i - 1].height + this._y_gap;
			} else {
				start_x = start_x + child_list[i - 1].width + this._x_gap;
			}
		}
		this._width = 0;
		this._height = 0;
		let ___OBJECT_2 = child_list;
		for (let k = 1; k <= ___OBJECT_2.length; ++k) {
			let child = ___OBJECT_2[k - 1];
			if (child === undefined) break;
			let width = child.x + child.width + this._x_start_gap;
			if (width > this._width) {
				this._width = width;
			}
			let height = child.y + child.height + this._y_start_gap;
			if (height > this._height) {
				this._height = height;
			}
		}
	},
	HandleChildResize : function(event) {
		this.Layout(this.GetChildIndex(event.target));
		this.DispatchEvent(___all_struct.get(-431205740), {});
	},
	ClipRect : function(left, top, right, bottom, h_move, v_move) {
		left = left - this._x;
		if (left < 0) {
			left = 0;
		}
		top = top - this._y;
		if (top < 0) {
			top = 0;
		}
		right = right - this._x;
		if (right > this.width) {
			right = this.width;
		}
		bottom = bottom - this._y;
		if (bottom > this.height) {
			bottom = this.height;
		}
		if (left >= right || top >= bottom) {
			this.clip = true;
			return;
		}
		this.clip = false;
		let child_count = this.child_count;
		if (child_count === 0) {
			return;
		}
		let childs = this.childs;
		let new_show_map = ALittle.CreateKeyWeakMap();
		this._show.RemoveAllChild();
		let max_index = this._col_count;
		if (this._child_count < max_index) {
			max_index = this._child_count;
		}
		let min_index = 1;
		let index = min_index;
		if (h_move === undefined || this._clip_left_index === 0) {
			do {
				if (childs[index - 1].x > left) {
					max_index = index;
					index = __ceil((max_index + min_index) / 2);
				} else if (childs[index - 1].x + childs[index - 1].width < left) {
					min_index = index;
					index = __ceil((max_index + min_index) / 2);
				} else {
					break;
				}
			} while (index !== min_index && index !== max_index);
		} else {
			index = this._clip_left_index;
			if (h_move < 0) {
				while (index < max_index) {
					if (childs[index - 1].x + childs[index - 1].width >= left) {
						break;
					}
					++ index;
				}
			} else if (h_move > 0) {
				while (index > min_index) {
					if (childs[index - 1].x <= left) {
						break;
					}
					-- index;
				}
			}
		}
		this._clip_left_index = index;
		max_index = this._col_count;
		if (this._child_count < max_index) {
			max_index = this._child_count;
		}
		for (let i = index; i <= max_index; i += 1) {
			if (childs[i - 1].x < right) {
				this._clip_right_index = i;
			} else {
				break;
			}
		}
		max_index = __ceil(this._child_count / this._col_count);
		min_index = 1;
		index = min_index;
		if (v_move === undefined || this._clip_top_index === 0) {
			do {
				let child_index = this._col_count * (index - 1) + 1;
				if (childs[child_index - 1].y > top) {
					max_index = index;
					index = __ceil((max_index + min_index) / 2);
				} else if (childs[child_index - 1].y + childs[child_index - 1].height < top) {
					min_index = index;
					index = __ceil((max_index + min_index) / 2);
				} else {
					break;
				}
			} while (index !== min_index && index !== max_index);
		} else {
			index = this._clip_top_index;
			if (v_move < 0) {
				while (index < max_index) {
					let child_index = this._col_count * (index - 1) + 1;
					if (childs[child_index - 1].y + childs[child_index - 1].height >= top) {
						break;
					}
					++ index;
				}
			} else if (v_move > 0) {
				while (index > min_index) {
					let child_index = this._col_count * (index - 1) + 1;
					if (childs[child_index - 1].y <= top) {
						break;
					}
					-- index;
				}
			}
		}
		this._clip_top_index = index;
		max_index = __ceil(this._child_count / this._col_count);
		let child_index = this._col_count * (index - 1) + 1;
		for (let i = index; i <= max_index; i += 1) {
			if (childs[child_index - 1].y < bottom) {
				this._clip_bottom_index = i;
			} else {
				break;
			}
			child_index = child_index + (this._col_count);
		}
		let base_index = this._col_count * (this._clip_top_index - 1);
		for (let i = this._clip_top_index; i <= this._clip_bottom_index; i += 1) {
			for (let j = this._clip_left_index; j <= this._clip_right_index; j += 1) {
				let child = childs[base_index + j - 1];
				if (child !== undefined) {
					this._show.AddChild(child._show);
					new_show_map.set(child, true);
					if (child.ClipRect !== undefined) {
						child.ClipRect(left, top, right, bottom, h_move, v_move);
					}
				}
			}
			base_index = base_index + (this._col_count);
		}
		for (let [child, v] of new_show_map) {
			if (v === undefined) continue;
			if (this._show_child_map.get(child) === undefined) {
				let e = {};
				e.target = child;
				child.DispatchEvent(___all_struct.get(1862557463), e);
			} else {
				this._show_child_map.delete(child);
			}
		}
		for (let [child, v] of this._show_child_map) {
			if (v === undefined) continue;
			let e = {};
			e.target = child;
			child.DispatchEvent(___all_struct.get(348388800), e);
		}
		this._show_child_map = new_show_map;
	},
}, "ALittle.TileTable");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.ImagePlay = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._interval = 0;
		this._play_index = 0;
	},
	set path_list(value) {
		this._path_list = value;
		this.RemoveAllChild();
		if (this._path_list === undefined) {
			if (this._play_loop !== undefined) {
				A_WeakLoopSystem.RemoveUpdater(this._play_loop);
				this._play_loop = undefined;
			}
			return;
		}
		let ___OBJECT_1 = this._path_list;
		for (let k = 1; k <= ___OBJECT_1.length; ++k) {
			let v = ___OBJECT_1[k - 1];
			if (v === undefined) break;
			let image = ALittle.NewObject(ALittle.Image, this._ctrl_sys);
			image.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			image.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			image.texture_name = v;
			image.visible = false;
			this.AddChild(image);
		}
		this.Play();
	},
	get path_list() {
		return this._path_list;
	},
	set interval(value) {
		if (this._interval === value) {
			return;
		}
		this._interval = value;
		this.Play();
	},
	get interval() {
		return this._interval;
	},
	Play : function() {
		if (this._play_loop !== undefined) {
			A_WeakLoopSystem.RemoveUpdater(this._play_loop);
			this._play_loop = undefined;
		}
		if (this._path_list === undefined) {
			return;
		}
		this._play_index = 0;
		let ___OBJECT_2 = this._childs;
		for (let k = 1; k <= ___OBJECT_2.length; ++k) {
			let v = ___OBJECT_2[k - 1];
			if (v === undefined) break;
			v.visible = false;
		}
		this._play_loop = ALittle.NewObject(ALittle.LoopFunction, this.PlayUpdate.bind(this), -1, this._interval, 0);
		A_WeakLoopSystem.AddUpdater(this._play_loop);
	},
	Stop : function() {
		if (this._play_loop !== undefined) {
			A_WeakLoopSystem.RemoveUpdater(this._play_loop);
			this._play_loop = undefined;
		}
	},
	PlayUpdate : function() {
		if (this._child_count === 0) {
			return;
		}
		if (this._play_index > 0) {
			this._childs[this._play_index - 1].visible = false;
		}
		this._play_index = this._play_index + 1;
		if (this._play_index > this._child_count) {
			this._play_index = 1;
		}
		this._childs[this._play_index - 1].visible = true;
	},
}, "ALittle.ImagePlay");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.Sprite === undefined) throw new Error(" extends class:ALittle.Sprite is undefined");
ALittle.SpritePlay = JavaScript.Class(ALittle.Sprite, {
	Ctor : function(ctrl_sys) {
		this._interval = 0;
		this._play_index = 0;
	},
	set interval(value) {
		if (this._interval === value) {
			return;
		}
		this._interval = value;
		this.Play();
	},
	get interval() {
		return this._interval;
	},
	Play : function() {
		if (this._play_loop !== undefined) {
			A_LoopSystem.RemoveUpdater(this._play_loop);
			this._play_loop = undefined;
		}
		this._play_index = 0;
		this._row_index = 1;
		this._col_index = 1;
		this._play_loop = ALittle.NewObject(ALittle.LoopFunction, this.PlayUpdate.bind(this), -1, this._interval, 0);
		A_LoopSystem.AddUpdater(this._play_loop);
	},
	Stop : function() {
		if (this._play_loop !== undefined) {
			A_LoopSystem.RemoveUpdater(this._play_loop);
			this._play_loop = undefined;
		}
	},
	PlayUpdate : function() {
		let total_count = this._row_count * this._col_count;
		++ this._play_index;
		this._play_index = this._play_index % total_count;
		this.row_index = ALittle.Math_Floor(this._play_index / this._row_count) + 1;
		this.col_index = this._play_index % this._col_count + 1;
	},
}, "ALittle.SpritePlay");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.FramePlay = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._interval = 0;
		this._play_child_index = 0;
		this._play_loop_count = 1;
		this._play_loop_index = 0;
		this._auto_play = false;
	},
	set base_y(value) {
		this._base_y = value;
	},
	get base_y() {
		if (this._base_y !== undefined) {
			return this._base_y;
		}
		return this.height;
	},
	set auto_play(value) {
		this._auto_play = value;
		if (value) {
			this.Play();
		}
	},
	get auto_play() {
		return this._auto_play;
	},
	AddChild : function(child, index) {
		if (ALittle.DisplayLayout.AddChild.call(this, child, index) === false) {
			return false;
		}
		child.visible = false;
		return true;
	},
	set interval(value) {
		if (this._interval === value) {
			return;
		}
		this._interval = value;
		if (this._play_loop !== undefined) {
			this.Play();
		}
	},
	get interval() {
		return this._interval;
	},
	set play_loop_count(value) {
		if (this._play_loop_count === value) {
			return;
		}
		this._play_loop_count = value;
		if (this._play_loop !== undefined) {
			this.Play();
		}
	},
	get play_loop_count() {
		return this._play_loop_count;
	},
	Play : function() {
		if (this._play_loop !== undefined) {
			A_WeakLoopSystem.RemoveUpdater(this._play_loop);
			this._play_loop = undefined;
		}
		this._play_child_index = 0;
		this._play_loop_index = 0;
		this.HideAllChild();
		this._play_loop = ALittle.NewObject(ALittle.LoopFunction, this.PlayUpdateLoop.bind(this), -1, this._interval, 0);
		A_WeakLoopSystem.AddUpdater(this._play_loop);
	},
	Stop : function() {
		if (this._play_loop !== undefined) {
			A_WeakLoopSystem.RemoveUpdater(this._play_loop);
			this._play_loop = undefined;
		}
	},
	HideAllChild : function() {
		let ___OBJECT_1 = this._childs;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let child = ___OBJECT_1[index - 1];
			if (child === undefined) break;
			child.visible = false;
			if ((child).__class === ALittle.FramePlay) {
				child.HideAllChild();
			}
		}
	},
	ShowAllChild : function() {
		let ___OBJECT_2 = this._childs;
		for (let index = 1; index <= ___OBJECT_2.length; ++index) {
			let child = ___OBJECT_2[index - 1];
			if (child === undefined) break;
			child.visible = true;
			if ((child).__class === ALittle.FramePlay) {
				child.ShowAllChild();
			}
		}
	},
	PlayUpdateLoop : function() {
		this.PlayUpdate();
	},
	PlayUpdate : function() {
		if (this._child_count === 0 || (this._play_loop_count > 0 && this._play_loop_index > this._play_loop_count)) {
			if (this._play_loop !== undefined) {
				this._play_loop.SetCompleted();
				this._play_loop = undefined;
			}
			return false;
		}
		if (this._play_child_index > 0) {
			let child = this._childs[this._play_child_index - 1];
			if ((child).__class === ALittle.FramePlay) {
				if (child.PlayUpdate()) {
					return true;
				}
			}
			child = this._childs[this._play_child_index - 1];
			if (child !== undefined) {
				child.visible = false;
			}
		}
		++ this._play_child_index;
		if (this._play_child_index > this._child_count) {
			this._play_child_index = 1;
			if (this._play_loop_count > 0) {
				++ this._play_loop_index;
				if (this._play_loop_index >= this._play_loop_count) {
					if (this._play_loop !== undefined) {
						this._play_loop.SetCompleted();
						this._play_loop = undefined;
					}
					return false;
				}
			}
		}
		this._childs[this._play_child_index - 1].visible = true;
		let child = this._childs[this._play_child_index - 1];
		if ((child).__class === ALittle.FramePlay) {
			child._play_loop_index = 0;
			child._play_child_index = 0;
			if (child.PlayUpdate()) {
				return true;
			}
		}
		return true;
	},
}, "ALittle.FramePlay");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.Piechart = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._start_degree = 0;
		this._end_degree = 0;
		this._tri_list = [];
		for (let i = 1; i <= 5; i += 1) {
			let triangle = ALittle.NewObject(ALittle.Triangle, this._ctrl_sys);
			triangle.u2 = 0.5;
			triangle.v2 = 0.5;
			triangle.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			triangle.width_value = 0;
			triangle.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			triangle.height_value = 0;
			this._tri_list[i - 1] = triangle;
			ALittle.DisplayLayout.AddChild.call(this, triangle);
		}
		this._start_degree = 0;
		this._end_degree = 360;
		this.SetDegree(0, 360);
		this._pie_texture_name = undefined;
	},
	set start_degree(value) {
		let tmp = value % 360;
		if (tmp < 0) {
			tmp = tmp + (360);
		}
		if (tmp === 0 && value / 360 !== 0) {
			tmp = 360;
		}
		this._start_degree = tmp;
		this.SetDegree(tmp, this._end_degree);
	},
	get start_degree() {
		return this._start_degree;
	},
	set end_degree(value) {
		let tmp = value % 360;
		if (tmp < 0) {
			tmp = tmp + (360);
		}
		if (tmp === 0 && value / 360 !== 0) {
			tmp = 360;
		}
		this._end_degree = tmp;
		this.SetDegree(this._start_degree, tmp);
	},
	get end_degree() {
		return this._end_degree;
	},
	set red(value) {
		if (this.red === value) {
			return;
		}
		this.red = value;
		for (let i = 1; i <= 5; i += 1) {
			this._tri_list[i - 1].red = value;
		}
	},
	set green(value) {
		if (this.green === value) {
			return;
		}
		this.green = value;
		for (let i = 1; i <= 5; i += 1) {
			this._tri_list[i - 1].green = value;
		}
	},
	set blue(value) {
		if (this.blue === value) {
			return;
		}
		this.blue = value;
		for (let i = 1; i <= 5; i += 1) {
			this._tri_list[i - 1].blue = value;
		}
	},
	set width(value) {
		if (value === this._width) {
			return;
		}
		this._width = value;
		if (this._width_type === ALittle.UIEnumTypes.SIZE_ABS) {
			this._width_value = this._width;
		}
		let ___OBJECT_1 = this._tri_list;
		for (let k = 1; k <= ___OBJECT_1.length; ++k) {
			let v = ___OBJECT_1[k - 1];
			if (v === undefined) break;
			v.x1 = v.u1 * value;
			v.x2 = v.u2 * value;
			v.x3 = v.u3 * value;
			this.UpdateWidthLayout(v);
			this.UpdateXLayout(v);
		}
		this._show.SetWidth(value);
	},
	set height(value) {
		if (value === this._height) {
			return;
		}
		this._height = value;
		if (this._height_type === ALittle.UIEnumTypes.SIZE_ABS) {
			this._height_value = this._height;
		}
		let ___OBJECT_2 = this._tri_list;
		for (let k = 1; k <= ___OBJECT_2.length; ++k) {
			let v = ___OBJECT_2[k - 1];
			if (v === undefined) break;
			v.y1 = v.v1 * value;
			v.y2 = v.v2 * value;
			v.y3 = v.v3 * value;
			this.UpdateHeightLayout(v);
			this.UpdateYLayout(v);
		}
		this._show.SetHeight(value);
	},
	set texture_name(value) {
		if (this._pie_texture_name === value) {
			return;
		}
		this._pie_texture_name = value;
		let ___OBJECT_3 = this._tri_list;
		for (let k = 1; k <= ___OBJECT_3.length; ++k) {
			let v = ___OBJECT_3[k - 1];
			if (v === undefined) break;
			v.texture_name = value;
		}
	},
	get texture_name() {
		return this._pie_texture_name;
	},
	SetDegree : function(start_c, end_c) {
		if (end_c <= start_c) {
			return;
		}
		let width = this.width;
		let height = this.height;
		let ___OBJECT_4 = this._tri_list;
		for (let k = 1; k <= ___OBJECT_4.length; ++k) {
			let v = ___OBJECT_4[k - 1];
			if (v === undefined) break;
			v.visible = false;
		}
		let e_offset = 0.0;
		let s_offset = 0.0;
		if (end_c >= 0 && end_c <= 45) {
			s_offset = (45 - start_c) / 90;
			e_offset = (45 - end_c) / 90;
			this.SetTriangleUV(this._tri_list[1 - 1], 1, e_offset, 1, s_offset);
			this.SetTriangleXY(this._tri_list[1 - 1], width, e_offset * height, width, s_offset * height);
		} else if (end_c <= 135) {
			e_offset = (135 - end_c) / 90;
			if (start_c < 45) {
				s_offset = (45 - start_c) / 90;
				this.SetTriangleUV(this._tri_list[1 - 1], 1, 0, 1, s_offset);
				this.SetTriangleXY(this._tri_list[1 - 1], width, 0, width, s_offset * height);
				this.SetTriangleUV(this._tri_list[2 - 1], e_offset, 0, this._tri_list[1 - 1].u1, this._tri_list[1 - 1].v1);
				this.SetTriangleXY(this._tri_list[2 - 1], e_offset * width, 0, this._tri_list[1 - 1].x1, this._tri_list[1 - 1].y1);
			} else {
				e_offset = (135 - end_c) / 90;
				s_offset = (135 - start_c) / 90;
				this.SetTriangleUV(this._tri_list[2 - 1], e_offset, 0, s_offset, 0);
				this.SetTriangleXY(this._tri_list[2 - 1], e_offset * width, 0, s_offset * width, 0);
			}
		} else if (end_c <= 225) {
			e_offset = (end_c - 135) / 90;
			if (start_c < 45) {
				s_offset = (45 - start_c) / 90;
				this.SetTriangleUV(this._tri_list[1 - 1], 1, 0, 1, s_offset);
				this.SetTriangleXY(this._tri_list[1 - 1], width, 0, width, s_offset * height);
				this.SetTriangleUV(this._tri_list[2 - 1], 0, 0, this._tri_list[1 - 1].u1, this._tri_list[1 - 1].v1);
				this.SetTriangleXY(this._tri_list[2 - 1], 0, 0, this._tri_list[1 - 1].x1, this._tri_list[1 - 1].y1);
				this.SetTriangleUV(this._tri_list[3 - 1], this._tri_list[2 - 1].u1, this._tri_list[2 - 1].v1, 0, e_offset);
				this.SetTriangleXY(this._tri_list[3 - 1], this._tri_list[2 - 1].x1, this._tri_list[2 - 1].y1, 0, e_offset * height);
			} else if (start_c < 135) {
				s_offset = (135 - start_c) / 90;
				this.SetTriangleUV(this._tri_list[2 - 1], 0, 0, s_offset, 0);
				this.SetTriangleXY(this._tri_list[2 - 1], 0, 0, s_offset * width, 0);
				this.SetTriangleUV(this._tri_list[3 - 1], this._tri_list[2 - 1].u1, this._tri_list[2 - 1].v1, 0, e_offset);
				this.SetTriangleXY(this._tri_list[3 - 1], this._tri_list[2 - 1].x1, this._tri_list[2 - 1].y1, 0, e_offset * height);
			} else {
				s_offset = (start_c - 135) / 90;
				this.SetTriangleUV(this._tri_list[3 - 1], 0, s_offset, 0, e_offset);
				this.SetTriangleXY(this._tri_list[3 - 1], 0, s_offset * height, 0, e_offset * height);
			}
		} else if (end_c <= 315) {
			e_offset = (end_c - 225) / 90;
			if (start_c < 45) {
				s_offset = (45 - start_c) / 90;
				this.SetTriangleUV(this._tri_list[1 - 1], 1, 0, 1, s_offset);
				this.SetTriangleXY(this._tri_list[1 - 1], width, 0, width, s_offset * height);
				this.SetTriangleUV(this._tri_list[2 - 1], 0, 0, this._tri_list[1 - 1].u1, this._tri_list[1 - 1].v1);
				this.SetTriangleXY(this._tri_list[2 - 1], 0, 0, this._tri_list[1 - 1].x1, this._tri_list[1 - 1].y1);
				this.SetTriangleUV(this._tri_list[3 - 1], this._tri_list[2 - 1].u1, this._tri_list[2 - 1].v1, 0, 1);
				this.SetTriangleXY(this._tri_list[3 - 1], this._tri_list[2 - 1].x1, this._tri_list[2 - 1].y1, 0, height);
				this.SetTriangleUV(this._tri_list[4 - 1], this._tri_list[3 - 1].u3, this._tri_list[3 - 1].v3, e_offset, 1);
				this.SetTriangleXY(this._tri_list[4 - 1], this._tri_list[3 - 1].x3, this._tri_list[3 - 1].y3, e_offset * width, height);
			} else if (start_c < 135) {
				s_offset = (135 - start_c) / 90;
				this.SetTriangleUV(this._tri_list[2 - 1], 0, 0, s_offset, 0);
				this.SetTriangleXY(this._tri_list[2 - 1], 0, 0, s_offset * width, 0);
				this.SetTriangleUV(this._tri_list[3 - 1], this._tri_list[2 - 1].u1, this._tri_list[2 - 1].v1, 0, 1);
				this.SetTriangleXY(this._tri_list[3 - 1], this._tri_list[2 - 1].x1, this._tri_list[2 - 1].y1, 0, height);
				this.SetTriangleUV(this._tri_list[4 - 1], this._tri_list[3 - 1].u3, this._tri_list[3 - 1].v3, e_offset, 1);
				this.SetTriangleXY(this._tri_list[4 - 1], this._tri_list[3 - 1].x3, this._tri_list[3 - 1].y3, e_offset * width, height);
			} else if (start_c < 225) {
				s_offset = (start_c - 135) / 90;
				this.SetTriangleUV(this._tri_list[3 - 1], 0, s_offset, 0, 1);
				this.SetTriangleXY(this._tri_list[3 - 1], 0, s_offset * height, 0, height);
				this.SetTriangleUV(this._tri_list[4 - 1], this._tri_list[3 - 1].u3, this._tri_list[3 - 1].v3, e_offset, 1);
				this.SetTriangleXY(this._tri_list[4 - 1], this._tri_list[3 - 1].x3, this._tri_list[3 - 1].y3, e_offset * width, height);
			} else {
				s_offset = (start_c - 225) / 90;
				this.SetTriangleUV(this._tri_list[4 - 1], s_offset, 1, e_offset, 1);
				this.SetTriangleXY(this._tri_list[4 - 1], s_offset * width, height, e_offset * width, height);
			}
		} else {
			e_offset = (405 - end_c) / 90;
			if (start_c < 45) {
				s_offset = (45 - start_c) / 90;
				this.SetTriangleUV(this._tri_list[1 - 1], 1, 0, 1, s_offset);
				this.SetTriangleXY(this._tri_list[1 - 1], width, 0, width, s_offset * height);
				this.SetTriangleUV(this._tri_list[2 - 1], 0, 0, this._tri_list[1 - 1].u1, this._tri_list[1 - 1].v1);
				this.SetTriangleXY(this._tri_list[2 - 1], 0, 0, this._tri_list[1 - 1].x1, this._tri_list[1 - 1].y1);
				this.SetTriangleUV(this._tri_list[3 - 1], this._tri_list[2 - 1].u1, this._tri_list[2 - 1].v1, 0, 1);
				this.SetTriangleXY(this._tri_list[3 - 1], this._tri_list[2 - 1].x1, this._tri_list[2 - 1].y1, 0, height);
				this.SetTriangleUV(this._tri_list[4 - 1], this._tri_list[3 - 1].u3, this._tri_list[3 - 1].v3, 1, 1);
				this.SetTriangleXY(this._tri_list[4 - 1], this._tri_list[3 - 1].x3, this._tri_list[3 - 1].y3, width, height);
				this.SetTriangleUV(this._tri_list[5 - 1], 1, e_offset, this._tri_list[4 - 1].u3, this._tri_list[4 - 1].v3);
				this.SetTriangleXY(this._tri_list[5 - 1], width, e_offset * height, this._tri_list[4 - 1].x3, this._tri_list[4 - 1].y3);
			} else if (start_c < 135) {
				s_offset = (135 - start_c) / 90;
				this.SetTriangleUV(this._tri_list[2 - 1], 0, 0, s_offset, 0);
				this.SetTriangleXY(this._tri_list[2 - 1], 0, 0, s_offset * width, 0);
				this.SetTriangleUV(this._tri_list[3 - 1], this._tri_list[2 - 1].u1, this._tri_list[2 - 1].v1, 0, 1);
				this.SetTriangleXY(this._tri_list[3 - 1], this._tri_list[2 - 1].x1, this._tri_list[2 - 1].y1, 0, height);
				this.SetTriangleUV(this._tri_list[4 - 1], this._tri_list[3 - 1].u3, this._tri_list[3 - 1].v3, 1, 1);
				this.SetTriangleXY(this._tri_list[4 - 1], this._tri_list[3 - 1].x3, this._tri_list[3 - 1].y3, width, height);
				this.SetTriangleUV(this._tri_list[1 - 1], 1, e_offset, this._tri_list[4 - 1].u3, this._tri_list[4 - 1].v3);
				this.SetTriangleXY(this._tri_list[1 - 1], width, e_offset * height, this._tri_list[4 - 1].x3, this._tri_list[4 - 1].y3);
			} else if (start_c < 225) {
				s_offset = (start_c - 135) / 90;
				this.SetTriangleUV(this._tri_list[3 - 1], 0, s_offset, 0, 1);
				this.SetTriangleXY(this._tri_list[3 - 1], 0, s_offset * height, 0, height);
				this.SetTriangleUV(this._tri_list[4 - 1], this._tri_list[3 - 1].u3, this._tri_list[3 - 1].v3, 1, 1);
				this.SetTriangleXY(this._tri_list[4 - 1], this._tri_list[3 - 1].x3, this._tri_list[3 - 1].y3, width, height);
				this.SetTriangleUV(this._tri_list[1 - 1], 1, e_offset, this._tri_list[4 - 1].u3, this._tri_list[4 - 1].v3);
				this.SetTriangleXY(this._tri_list[1 - 1], width, e_offset * height, this._tri_list[4 - 1].x3, this._tri_list[4 - 1].y3);
			} else if (start_c < 315) {
				s_offset = (start_c - 225) / 90;
				this.SetTriangleUV(this._tri_list[4 - 1], s_offset, 1, 1, 1);
				this.SetTriangleXY(this._tri_list[4 - 1], s_offset * width, height, width, height);
				this.SetTriangleUV(this._tri_list[1 - 1], 1, e_offset, this._tri_list[4 - 1].u3, this._tri_list[4 - 1].v3);
				this.SetTriangleXY(this._tri_list[1 - 1], width, e_offset * height, this._tri_list[4 - 1].x3, this._tri_list[4 - 1].y3);
			} else {
				s_offset = (405 - start_c) / 90;
				this.SetTriangleUV(this._tri_list[1 - 1], 1, e_offset, 1, s_offset);
				this.SetTriangleXY(this._tri_list[1 - 1], width, e_offset * height, width, s_offset * height);
			}
		}
	},
	SetTriangleXY : function(tri, x1, y1, x3, y3) {
		tri.x1 = x1;
		tri.y1 = y1;
		tri.x3 = x3;
		tri.y3 = y3;
		tri.visible = true;
	},
	SetTriangleUV : function(tri, u1, v1, u3, v3) {
		tri.u1 = u1;
		tri.v1 = v1;
		tri.u3 = u3;
		tri.v3 = v3;
	},
}, "ALittle.Piechart");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


let __cos = ALittle.Math_Cos;
let __sin = ALittle.Math_Sin;
if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.ImageInput = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._show_input = ALittle.NewObject(ALittle.TextInput, this._ctrl_sys);
		this._show_input.x_type = ALittle.UIEnumTypes.POS_ALIGN_STARTING;
		this._show_input.y_type = ALittle.UIEnumTypes.POS_ALIGN_STARTING;
		this._show_input.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
		this._show_input.width_value = 0;
		this._show_input.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
		this._show_input.height_value = 0;
		this.AddChild(this._show_input, 5);
		this._logic_left = 0;
		this._logic_right = 0;
		this._logic_top = 0;
		this._logic_bottom = 0;
		this._ims_padding = 0;
		this._show_disabled = undefined;
		this._pickup_this = true;
		this._show_input.AddEventListener(___all_struct.get(-644464135), this, this.HandleFocusIn);
		this._show_input.AddEventListener(___all_struct.get(292776509), this, this.HandleFocusOut);
		this._show_input.AddEventListener(___all_struct.get(544684311), this, this.HandleMoveIn);
		this._show_input.AddEventListener(___all_struct.get(-1202439334), this, this.HandleMoveOut);
		this._show_input.AddEventListener(___all_struct.get(1883782801), this, this.HandleImageInputTransformLButtonDown);
		this._show_input.AddEventListener(___all_struct.get(-1234078962), this, this.HandleImageInputTransformTextInput);
		this._show_input.AddEventListener(___all_struct.get(-1604617962), this, this.HandleImageInputTransformKeyDown);
		this._show_input.AddEventListener(___all_struct.get(1301789264), this, this.HandleImageInputTransformDragBegin);
		this._show_input.AddEventListener(___all_struct.get(1337289812), this, this.HandleImageInputTransformDrag);
		this._show_input.AddEventListener(___all_struct.get(150587926), this, this.HandleImageInputTransformDragEnd);
		this._show_input.AddEventListener(___all_struct.get(-1737121315), this, this.HandleImageInputTransformMButtonWheel);
		this._show_input.AddEventListener(___all_struct.get(958494922), this, this.HandleImageInputTransformChangd);
		this._show_input.AddEventListener(___all_struct.get(776398171), this, this.HandleImageInputTransformEnterKey);
		this._show_input.AddEventListener(___all_struct.get(2024735182), this, this.HandleImageInputTransformTabKey);
		this._show_input.AddEventListener(___all_struct.get(-641444818), this, this.HandleImageInputTransformRButtonDown);
		this._show_input.AddEventListener(___all_struct.get(-569321214), this, this.HandleImageInputTransformRButtonUp);
		this._show_input.AddEventListener(___all_struct.get(-439548260), this, this.HandleImageInputTransformLongButtonDown);
	},
	set disabled(value) {
		ALittle.DisplayObject.__setter.disabled.call(this, value);
		if (value) {
			this.ShowDisabled();
		} else {
			this.ShowUp();
		}
	},
	get is_focus() {
		return A_UISystem.focus === this._show_input;
	},
	set focus(value) {
		if (value) {
			A_UISystem.focus = this._show_input;
		} else {
			if (A_UISystem.focus === this._show_input) {
				A_UISystem.focus = undefined;
			}
		}
	},
	get is_input() {
		return true;
	},
	get regex() {
		return this._show_input.regex;
	},
	set regex(value) {
		if (value === undefined) {
			value = "";
		}
		this._show_input.regex = value;
	},
	get limit_len() {
		return this._show_input.limit_len;
	},
	set limit_len(value) {
		if (value === undefined) {
			value = 0;
		}
		this._show_input.limit_len = value;
	},
	set default_text(value) {
		this._show_input.default_text = value;
	},
	get default_text() {
		return this._show_input.default_text;
	},
	set default_text_alpha(value) {
		this._show_input.default_text_alpha = value;
	},
	get default_text_alpha() {
		return this._show_input.default_text_alpha;
	},
	get cursor_x() {
		return this._show_input.cursor_x;
	},
	get cursor_y() {
		return this._show_input.cursor_y;
	},
	set editable(value) {
		this._show_input.editable = value;
	},
	get editable() {
		return this._show_input.editable;
	},
	set font_path(value) {
		this._show_input.font_path = value;
	},
	set font_size(value) {
		this._show_input.font_size = value;
	},
	get font_path() {
		return this._show_input.font_path;
	},
	get font_size() {
		return this._show_input.font_size;
	},
	set text(value) {
		this._show_input.text = value;
	},
	get text() {
		return this._show_input.text;
	},
	set bold(value) {
		this._show_input.bold = value;
	},
	get bold() {
		return this._show_input.bold;
	},
	set italic(value) {
		this._show_input.italic = value;
	},
	get italic() {
		return this._show_input.italic;
	},
	set underline(value) {
		this._show_input.underline = value;
	},
	get underline() {
		return this._show_input.underline;
	},
	set deleteline(value) {
		this._show_input.deleteline = value;
	},
	get deleteline() {
		return this._show_input.deleteline;
	},
	set outline(value) {
		this._show_input.outline = value;
	},
	get outline() {
		return this._show_input.outline;
	},
	set password_mode(value) {
		this._show_input.password_mode = value;
	},
	get password_mode() {
		return this._show_input.password_mode;
	},
	set cursor_red(value) {
		this._show_input.cursor_red = value;
	},
	get cursor_red() {
		return this._show_input.cursor_red;
	},
	set cursor_green(value) {
		this._show_input.cursor_green = value;
	},
	get cursor_green() {
		return this._show_input.cursor_green;
	},
	set cursor_blue(value) {
		this._show_input.cursor_blue = value;
	},
	get cursor_blue() {
		return this._show_input.cursor_blue;
	},
	set red(value) {
		this._show_input.red = value;
	},
	get red() {
		return this._show_input.red;
	},
	set green(value) {
		this._show_input.green = value;
	},
	get green() {
		return this._show_input.green;
	},
	set blue(value) {
		this._show_input.blue = value;
	},
	get blue() {
		return this._show_input.blue;
	},
	set ims_padding(value) {
		this._ims_padding = value;
		this._show_input.ims_padding = ALittle.Math_Floor(value + this._logic_bottom);
	},
	get ims_padding() {
		return this._ims_padding;
	},
	HandleFocusIn : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(-644464135), event);
		this.ShowDown();
	},
	HandleFocusOut : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(292776509), event);
		this.ShowUp();
	},
	HandleImageInputTransformLButtonDown : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(1883782801), event);
	},
	HandleImageInputTransformTextInput : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(-1234078962), event);
	},
	HandleImageInputTransformKeyDown : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(-1604617962), event);
	},
	HandleImageInputTransformDragBegin : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(1301789264), event);
	},
	HandleImageInputTransformDrag : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(1337289812), event);
	},
	HandleImageInputTransformDragEnd : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(150587926), event);
	},
	HandleImageInputTransformMButtonWheel : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(-1737121315), event);
	},
	HandleImageInputTransformChangd : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(958494922), event);
	},
	HandleImageInputTransformEnterKey : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(776398171), event);
	},
	HandleImageInputTransformTabKey : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(2024735182), event);
	},
	HandleImageInputTransformRButtonDown : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(-641444818), event);
	},
	HandleImageInputTransformRButtonUp : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(-569321214), event);
	},
	HandleImageInputTransformLongButtonDown : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(-439548260), event);
	},
	HandleMoveIn : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(544684311), event);
		if (A_UISystem.focus !== this._show_input) {
			this.ShowOver();
		}
	},
	HandleMoveOut : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(-1202439334), event);
		if (A_UISystem.focus !== this._show_input) {
			this.ShowUp();
		}
	},
	ShowUp : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._show_up !== undefined) {
			this._show_up.alpha = 1;
		}
		if (this._show_over !== undefined) {
			this._show_over.alpha = 0;
		}
		if (this._show_down !== undefined) {
			this._show_down.alpha = 0;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 0;
		}
	},
	ShowDown : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._show_up !== undefined) {
			this._show_up.alpha = 0;
		}
		if (this._show_over !== undefined) {
			this._show_over.alpha = 0;
		}
		if (this._show_down !== undefined) {
			this._show_down.alpha = 1;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 0;
		}
	},
	ShowOver : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._show_up !== undefined) {
			this._show_up.alpha = 0;
		}
		if (this._show_over !== undefined) {
			this._show_over.alpha = 1;
		}
		if (this._show_down !== undefined) {
			this._show_down.alpha = 0;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 0;
		}
	},
	ShowDisabled : function() {
		if (this._show_up !== undefined) {
			this._show_up.alpha = 0;
		}
		if (this._show_over !== undefined) {
			this._show_over.alpha = 0;
		}
		if (this._show_down !== undefined) {
			this._show_down.alpha = 0;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 1;
		}
	},
	set show_up(value) {
		this.RemoveChild(this._show_up);
		this._show_up = value;
		if (this._show_up !== undefined) {
			this._show_up.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_up.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_up.width_value = 0;
			this._show_up.height_value = 0;
			this._show_up.disabled = true;
			this.AddChild(this._show_up, 1);
		}
		this.ShowUp();
	},
	get show_up() {
		return this._show_up;
	},
	set show_down(value) {
		this.RemoveChild(this._show_down);
		this._show_down = value;
		if (this._show_down !== undefined) {
			this._show_down.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_down.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_down.width_value = 0;
			this._show_down.height_value = 0;
			this._show_down.disabled = true;
			this.AddChild(this._show_down, 1);
		}
		this.ShowUp();
	},
	get show_down() {
		return this._show_down;
	},
	set show_over(value) {
		this.RemoveChild(this._show_over);
		this._show_over = value;
		if (this._show_over !== undefined) {
			this._show_over.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_over.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_over.width_value = 0;
			this._show_over.height_value = 0;
			this._show_over.disabled = true;
			this.AddChild(this._show_over, 1);
		}
		this.ShowUp();
	},
	get show_over() {
		return this._show_over;
	},
	set show_disabled(value) {
		this.RemoveChild(this._show_disabled);
		this._show_disabled = value;
		if (this._show_disabled !== undefined) {
			this._show_disabled.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_disabled.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_disabled.width_value = 0;
			this._show_disabled.height_value = 0;
			this._show_disabled.disabled = true;
			this.AddChild(this._show_disabled, 1);
		}
		this.ShowUp();
	},
	get show_disabled() {
		return this._show_disabled;
	},
	get show_input() {
		return this._show_input;
	},
	set margin_left(value) {
		this._logic_left = value;
		this.Layout();
	},
	get margin_left() {
		return this._logic_left;
	},
	set margin_right(value) {
		this._logic_right = value;
		this.Layout();
	},
	get margin_right() {
		return this._logic_right;
	},
	set margin_top(value) {
		this._logic_top = value;
		this.Layout();
	},
	get margin_top() {
		return this._logic_top;
	},
	set margin_bottom(value) {
		this._logic_bottom = value;
		this.Layout();
		this._show_input.ims_padding = ALittle.Math_Floor(this._ims_padding + this._logic_bottom);
	},
	get margin_bottom() {
		return this._logic_bottom;
	},
	Layout : function() {
		this.SetChildIndex(this._show_input, 5);
		this._show_input.x_value = this._logic_left;
		this._show_input.y_value = this._logic_top;
		this._show_input.width_value = this._logic_left + this._logic_right;
		this._show_input.height_value = this._logic_top + this._logic_bottom;
	},
	PickUp : function(x, y) {
		if (this._ignore || this._abs_disabled || this._abs_visible === false) {
			return [undefined, undefined, undefined];
		}
		let rel_x = x - this._x;
		let rel_y = y - this._y;
		let xx = rel_x - this._center_x;
		let yy = rel_y - this._center_y;
		if (this._angle !== 0) {
			let rad = 3.1415926 * -this._angle / 180.0;
			let cos = __cos(rad);
			let sin = __sin(rad);
			let xxx = xx * cos + yy * -sin;
			let yyy = xx * sin + yy * cos;
			xx = xxx;
			yy = yyy;
		}
		if (this._scale_x > 0) {
			xx = xx / (this._scale_x);
		}
		if (this._scale_y > 0) {
			yy = yy / (this._scale_y);
		}
		rel_x = xx + this._center_x;
		rel_y = yy + this._center_y;
		if (this._scale_x <= 0 || this._scale_y <= 0) {
			if (this._modal) {
				return [this, rel_x, rel_y];
			}
			return [undefined, rel_x, rel_y];
		}
		if (this._pickup_rect && (rel_x < 0 || rel_y < 0 || rel_x >= this._width || rel_y >= this._height)) {
			if (this._modal) {
				return [this, rel_x, rel_y];
			}
			return [undefined, undefined, undefined];
		}
		if (this._pickup_child) {
			let [v_focus, v_x, v_y] = this._show_input.PickUp(rel_x, rel_y);
			return [this._show_input, v_x, v_y];
		}
		if (this._modal || (this._pickup_rect && this._pickup_child === false) || this._pickup_this) {
			return [this, rel_x, rel_y];
		}
		return [undefined, undefined, undefined];
	},
	SetCursorToHome : function() {
		this._show_input.SetCursorToHome();
	},
	SetCursorToEnd : function() {
		this._show_input.SetCursorToEnd();
	},
	SelectAll : function() {
		this._show_input.SelectAll();
	},
	CopyText : function() {
		this._show_input.CopyText();
	},
	PasteText : function() {
		this._show_input.PasteText();
	},
	CutText : function() {
		this._show_input.CutText();
	},
	InsertText : function(text) {
		this._show_input.InsertText(text);
	},
}, "ALittle.ImageInput");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


let __cos = ALittle.Math_Cos;
let __sin = ALittle.Math_Sin;
if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.ImageEdit = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._show_edit = ALittle.NewObject(ALittle.TextEdit, this._ctrl_sys);
		this._show_edit.x_type = ALittle.UIEnumTypes.POS_ALIGN_STARTING;
		this._show_edit.y_type = ALittle.UIEnumTypes.POS_ALIGN_STARTING;
		this._show_edit.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
		this._show_edit.width_value = 0;
		this._show_edit.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
		this._show_edit.height_value = 0;
		this.AddChild(this._show_edit, 5);
		this._logic_left = 0;
		this._logic_right = 0;
		this._logic_top = 0;
		this._logic_bottom = 0;
		this._show_edit.AddEventListener(___all_struct.get(-644464135), this, this.HandleFocusIn);
		this._show_edit.AddEventListener(___all_struct.get(292776509), this, this.HandleFocusOut);
		this._show_edit.AddEventListener(___all_struct.get(544684311), this, this.HandleMoveIn);
		this._show_edit.AddEventListener(___all_struct.get(-1202439334), this, this.HandleMoveOut);
		this._show_edit.AddEventListener(___all_struct.get(1883782801), this, this.HandleImageEditTransformLButtonDown);
		this._show_edit.AddEventListener(___all_struct.get(-1234078962), this, this.HandleImageEditTransformTextInput);
		this._show_edit.AddEventListener(___all_struct.get(-1604617962), this, this.HandleImageEditTransformKeyDown);
		this._show_edit.AddEventListener(___all_struct.get(1301789264), this, this.HandleImageEditTransformDragBegin);
		this._show_edit.AddEventListener(___all_struct.get(1337289812), this, this.HandleImageEditTransformDrag);
		this._show_edit.AddEventListener(___all_struct.get(150587926), this, this.HandleImageEditTransformDragEnd);
		this._show_edit.AddEventListener(___all_struct.get(-1737121315), this, this.HandleImageEditTransformMButtonWheel);
		this._show_edit.AddEventListener(___all_struct.get(958494922), this, this.HandleImageEditTransformChangd);
		this._show_edit.AddEventListener(___all_struct.get(776398171), this, this.HandleImageEditTransformEnterKey);
		this._show_edit.AddEventListener(___all_struct.get(2024735182), this, this.HandleImageEditTransformTabKey);
		this._show_edit.AddEventListener(___all_struct.get(-641444818), this, this.HandleImageEditTransformRButtonDown);
		this._show_edit.AddEventListener(___all_struct.get(-569321214), this, this.HandleImageEditTransformRButtonUp);
		this._show_edit.AddEventListener(___all_struct.get(-439548260), this, this.HandleImageEditTransformLongButtonDown);
	},
	set disabled(value) {
		ALittle.DisplayObject.__setter.disabled.call(this, value);
		if (value) {
			this.ShowDisabled();
		} else {
			this.ShowUp();
		}
	},
	get is_focus() {
		return A_UISystem.focus === this._show_edit;
	},
	set focus(value) {
		if (value) {
			A_UISystem.focus = this._show_edit;
		} else {
			if (A_UISystem.focus === this._show_edit) {
				A_UISystem.focus = undefined;
			}
		}
	},
	get is_input() {
		return true;
	},
	get show_edit() {
		return this._show_edit;
	},
	get cursor_x() {
		return this._show_edit.cursor_x;
	},
	get cursor_y() {
		return this._show_edit.cursor_y;
	},
	set editable(value) {
		this._show_edit.editable = value;
	},
	get editable() {
		return this._show_edit.editable;
	},
	set font_path(value) {
		this._show_edit.font_path = value;
	},
	set font_size(value) {
		this._show_edit.font_size = value;
	},
	get font_path() {
		return this._show_edit.font_path;
	},
	get font_size() {
		return this._show_edit.font_size;
	},
	get regex() {
		return this._show_edit.regex;
	},
	set regex(value) {
		if (value === undefined) {
			value = "";
		}
		this._show_edit.regex = value;
	},
	get limit_len() {
		return this._show_edit.limit_len;
	},
	set limit_len(value) {
		if (value === undefined) {
			value = 0;
		}
		this._show_edit.limit_len = value;
	},
	set text(value) {
		this._show_edit.text = value;
	},
	get text() {
		return this._show_edit.text;
	},
	set bold(value) {
		this._show_edit.bold = value;
	},
	get bold() {
		return this._show_edit.bold;
	},
	set italic(value) {
		this._show_edit.italic = value;
	},
	get italic() {
		return this._show_edit.italic;
	},
	set underline(value) {
		this._show_edit.underline = value;
	},
	get underline() {
		return this._show_edit.underline;
	},
	set deleteline(value) {
		this._show_edit.deleteline = value;
	},
	get deleteline() {
		return this._show_edit.deleteline;
	},
	set outline(value) {
		this._show_edit.outline = value;
	},
	get outline() {
		return this._show_edit.outline;
	},
	set cursor_red(value) {
		this._show_edit.cursor_red = value;
	},
	get cursor_red() {
		return this._show_edit.cursor_red;
	},
	set cursor_green(value) {
		this._show_edit.cursor_green = value;
	},
	get cursor_green() {
		return this._show_edit.cursor_green;
	},
	set cursor_blue(value) {
		this._show_edit.cursor_blue = value;
	},
	get cursor_blue() {
		return this._show_edit.cursor_blue;
	},
	set red(value) {
		this._show_edit.red = value;
	},
	get red() {
		return this._show_edit.red;
	},
	set green(value) {
		this._show_edit.green = value;
	},
	get green() {
		return this._show_edit.green;
	},
	set blue(value) {
		this._show_edit.blue = value;
	},
	get blue() {
		return this._show_edit.blue;
	},
	set ims_padding(value) {
		this._show_edit.ims_padding = value;
	},
	get ims_padding() {
		return this._show_edit.ims_padding;
	},
	HandleFocusIn : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(-644464135), event);
		this.ShowDown();
	},
	HandleFocusOut : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(292776509), event);
		this.ShowUp();
	},
	HandleImageEditTransformLButtonDown : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(1883782801), event);
	},
	HandleImageEditTransformTextInput : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(-1234078962), event);
	},
	HandleImageEditTransformKeyDown : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(-1604617962), event);
	},
	HandleImageEditTransformDragBegin : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(1301789264), event);
	},
	HandleImageEditTransformDrag : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(1337289812), event);
	},
	HandleImageEditTransformDragEnd : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(150587926), event);
	},
	HandleImageEditTransformMButtonWheel : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(-1737121315), event);
	},
	HandleImageEditTransformChangd : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(958494922), event);
	},
	HandleImageEditTransformEnterKey : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(776398171), event);
	},
	HandleImageEditTransformTabKey : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(2024735182), event);
	},
	HandleImageEditTransformRButtonDown : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(-641444818), event);
	},
	HandleImageEditTransformRButtonUp : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(-569321214), event);
	},
	HandleImageEditTransformLongButtonDown : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(-439548260), event);
	},
	HandleMoveIn : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(544684311), event);
		if (A_UISystem.focus !== this._show_edit) {
			this.ShowOver();
		}
	},
	HandleMoveOut : function(event) {
		event.target = this;
		this.DispatchEvent(___all_struct.get(-1202439334), event);
		if (A_UISystem.focus !== this._show_edit) {
			this.ShowUp();
		}
	},
	ShowUp : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._show_up !== undefined) {
			this._show_up.alpha = 1;
		}
		if (this._show_over !== undefined) {
			this._show_over.alpha = 0;
		}
		if (this._show_down !== undefined) {
			this._show_down.alpha = 0;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 0;
		}
	},
	ShowDown : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._show_up !== undefined) {
			this._show_up.alpha = 0;
		}
		if (this._show_over !== undefined) {
			this._show_over.alpha = 0;
		}
		if (this._show_down !== undefined) {
			this._show_down.alpha = 1;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 0;
		}
	},
	ShowOver : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._show_up !== undefined) {
			this._show_up.alpha = 0;
		}
		if (this._show_over !== undefined) {
			this._show_over.alpha = 1;
		}
		if (this._show_down !== undefined) {
			this._show_down.alpha = 0;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 0;
		}
	},
	ShowDisabled : function() {
		if (this._show_up !== undefined) {
			this._show_up.alpha = 0;
		}
		if (this._show_over !== undefined) {
			this._show_over.alpha = 0;
		}
		if (this._show_down !== undefined) {
			this._show_down.alpha = 0;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 1;
		}
	},
	set show_up(value) {
		this.RemoveChild(this._show_up);
		this._show_up = value;
		if (this._show_up !== undefined) {
			this._show_up.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_up.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_up.width_value = 0;
			this._show_up.height_value = 0;
			this.AddChild(this._show_up, 1);
		}
		this.ShowUp();
	},
	get show_up() {
		return this._show_up;
	},
	set show_down(value) {
		this.RemoveChild(this._show_down);
		this._show_down = value;
		if (this._show_down !== undefined) {
			this._show_down.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_down.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_down.width_value = 0;
			this._show_down.height_value = 0;
			this.AddChild(this._show_down, 1);
		}
		this.ShowUp();
	},
	get show_down() {
		return this._show_down;
	},
	set show_over(value) {
		this.RemoveChild(this._show_over);
		this._show_over = value;
		if (this._show_over !== undefined) {
			this._show_over.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_over.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_over.width_value = 0;
			this._show_over.height_value = 0;
			this.AddChild(this._show_over, 1);
		}
		this.ShowUp();
	},
	get show_over() {
		return this._show_over;
	},
	set show_disabled(value) {
		this.RemoveChild(this._show_disabled);
		this._show_disabled = value;
		if (this._show_disabled !== undefined) {
			this._show_disabled.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_disabled.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_disabled.width_value = 0;
			this._show_disabled.height_value = 0;
			this.AddChild(this._show_disabled, 1);
		}
		this.ShowUp();
	},
	get show_disabled() {
		return this._show_disabled;
	},
	set margin_left(value) {
		this._logic_left = value;
		this.Layout();
	},
	get margin_left() {
		return this._logic_left;
	},
	set margin_right(value) {
		this._logic_right = value;
		this.Layout();
	},
	get margin_right() {
		return this._logic_right;
	},
	set margin_top(value) {
		this._logic_top = value;
		this.Layout();
	},
	get margin_top() {
		return this._logic_top;
	},
	set margin_bottom(value) {
		this._logic_bottom = value;
		this.Layout();
	},
	get margin_bottom() {
		return this._logic_bottom;
	},
	Layout : function() {
		this.SetChildIndex(this._show_edit, 5);
		this._show_edit.x_value = this._logic_left;
		this._show_edit.y_value = this._logic_top;
		this._show_edit.width_value = this._logic_left + this._logic_right;
		this._show_edit.height_value = this._logic_top + this._logic_bottom;
	},
	PickUp : function(x, y) {
		if (this._ignore || this._abs_disabled || this._abs_visible === false) {
			return [undefined, undefined, undefined];
		}
		let rel_x = x - this._x;
		let rel_y = y - this._y;
		let xx = rel_x - this._center_x;
		let yy = rel_y - this._center_y;
		if (this._angle !== 0) {
			let rad = 3.1415926 * -this._angle / 180.0;
			let cos = __cos(rad);
			let sin = __sin(rad);
			let xxx = xx * cos + yy * -sin;
			let yyy = xx * sin + yy * cos;
			xx = xxx;
			yy = yyy;
		}
		if (this._scale_x > 0) {
			xx = xx / (this._scale_x);
		}
		if (this._scale_y > 0) {
			yy = yy / (this._scale_y);
		}
		rel_x = xx + this._center_x;
		rel_y = yy + this._center_y;
		if (this._scale_x <= 0 || this._scale_y <= 0) {
			if (this._modal) {
				return [this, rel_x, rel_y];
			}
			return [undefined, rel_x, rel_y];
		}
		if (this._pickup_rect && (rel_x < 0 || rel_y < 0 || rel_x >= this._width || rel_y >= this._height)) {
			if (this._modal) {
				return [this, rel_x, rel_y];
			}
			return [undefined, undefined, undefined];
		}
		if (this._pickup_child) {
			let [v_focus, v_x, v_y] = this._show_edit.PickUp(rel_x, rel_y);
			return [this._show_edit, v_x, v_y];
		}
		if (this._modal || (this._pickup_rect && this._pickup_child === false) || this._pickup_this) {
			return [this, rel_x, rel_y];
		}
		return [undefined, undefined, undefined];
	},
	SetCursorToHome : function() {
		this._show_edit.SetCursorToHome();
	},
	SetCursorToEnd : function() {
		this._show_edit.SetCursorToEnd();
	},
	SelectAll : function() {
		this._show_edit.SelectAll();
	},
	CopyText : function() {
		this._show_edit.CopyText();
	},
	PasteText : function() {
		this._show_edit.PasteText();
	},
	CutText : function() {
		this._show_edit.CutText();
	},
	InsertText : function(value) {
		this._show_edit.InsertText(value);
	},
}, "ALittle.ImageEdit");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(485812343, "ALittle.RichAreaLineInfo", {
name : "ALittle.RichAreaLineInfo", ns_name : "ALittle", rl_name : "RichAreaLineInfo", hash_code : 485812343,
name_list : ["childs","child_count","height","width"],
type_list : ["List<ALittle.DisplayObject>","int","double","double"],
option_map : {}
})

let __find = ALittle.String_Find;
let __sub = ALittle.String_Sub;
let __floor = ALittle.Math_Floor;
if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.RichArea = JavaScript.Class(ALittle.DisplayLayout, {
	SplitText : function(char_info, char_info_list, char_info_list_count) {
		let text = char_info.text;
		while (true) {
			let start_index_1 = __find(text, "\n");
			let start_index_2 = __find(text, "\t");
			if (start_index_1 !== undefined && start_index_2 !== undefined) {
				if (start_index_1 < start_index_2) {
					start_index_2 = undefined;
				} else {
					start_index_1 = undefined;
				}
			}
			if (start_index_1 !== undefined) {
				let new_char_info = ALittle.String_CopyTable(char_info);
				new_char_info.text = __sub(text, 1, start_index_1 - 1);
				++ char_info_list_count;
				char_info_list[char_info_list_count - 1] = new_char_info;
				new_char_info = ALittle.String_CopyTable(char_info);
				new_char_info.text = "\n";
				++ char_info_list_count;
				char_info_list[char_info_list_count - 1] = new_char_info;
				text = __sub(text, start_index_1 + 1);
			} else if (start_index_2 !== undefined) {
				let new_char_info = ALittle.String_CopyTable(char_info);
				new_char_info.text = __sub(text, 1, start_index_2 - 1);
				++ char_info_list_count;
				char_info_list[char_info_list_count - 1] = new_char_info;
				new_char_info = ALittle.String_CopyTable(char_info);
				new_char_info.text = "\t";
				++ char_info_list_count;
				char_info_list[char_info_list_count - 1] = new_char_info;
				text = __sub(text, start_index_2 + 1);
			} else {
				if (text !== "") {
					let new_char_info = ALittle.String_CopyTable(char_info);
					new_char_info.text = text;
					++ char_info_list_count;
					char_info_list[char_info_list_count - 1] = new_char_info;
				}
				break;
			}
		}
		return char_info_list_count;
	},
	Ctor : function(ctrl_sys) {
		this._enter_key_height = 20;
		this._line_spacing = 0;
		this._halign = ALittle.UIEnumTypes.HALIGN_LEFT;
		this._valign = ALittle.UIEnumTypes.VALIGN_TOP;
		this._display_list = undefined;
		this._line_list = [];
		this._line_count = 0;
		this._real_height = 0;
		this._link_map = ALittle.CreateValueWeakMap();
		this._max_line_count = 0;
	},
	get link_map() {
		return this._link_map;
	},
	ClearLinkMap : function() {
		this._link_map = ALittle.CreateValueWeakMap();
	},
	set width(value) {
		if (this.width === value) {
			return;
		}
		ALittle.DisplayLayout.__setter.width.call(this, value);
		this.Refresh();
	},
	set display_list(value) {
		this._display_list = value;
		this.Refresh();
	},
	get display_list() {
		return this._display_list;
	},
	set halign(value) {
		if (this._halign === value) {
			return;
		}
		this._halign = value;
		this.RefreshX();
	},
	get halign() {
		return this._halign;
	},
	set valign(value) {
		if (this._valign === value) {
			return;
		}
		this._valign = value;
		this.RefreshY();
	},
	get valign() {
		return this._valign;
	},
	get lin_count() {
		return this._line_count;
	},
	get max_line_count() {
		return this._max_line_count;
	},
	set max_line_count(value) {
		if (this._max_line_count === value) {
			return;
		}
		this._max_line_count = value;
		this.Refresh();
	},
	GetLineWidth : function(line_index) {
		let count = this._line_count;
		if (line_index < 1 || line_index > count) {
			return 0;
		}
		let line = this._line_list[line_index - 1];
		return line.width;
	},
	get real_height() {
		return this._real_height;
	},
	set line_spacing(line_spacing) {
		if (this._line_spacing === line_spacing) {
			return;
		}
		this._line_spacing = line_spacing;
		this.RefreshY();
	},
	get line_spacing() {
		return this._line_spacing;
	},
	Refresh : function() {
		this.RemoveAllChild();
		this._line_list = [];
		this._line_count = 0;
		let total_width = this.width;
		if (total_width === 0) {
			return;
		}
		if (this._display_list === undefined) {
			return;
		}
		let display_list = [];
		let display_list_count = 0;
		let ___OBJECT_1 = this._display_list;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let display_info = ___OBJECT_1[index - 1];
			if (display_info === undefined) break;
			if (display_info.__class === "Text") {
				display_list_count = this.SplitText(display_info, display_list, display_list_count);
			} else {
				++ display_list_count;
				display_list[display_list_count - 1] = display_info;
			}
		}
		let line_info = undefined;
		let display_info = undefined;
		let display_object = undefined;
		let display_index = 1;
		let remain_width = total_width;
		while (true) {
			if (display_info === undefined) {
				display_info = display_list[display_index - 1];
				if (display_info === undefined) {
					break;
				}
			}
			if (line_info === undefined) {
				if (this._max_line_count > 0 && this._line_count >= this._max_line_count) {
					break;
				}
				line_info = {};
				line_info.childs = [];
				line_info.child_count = 0;
				line_info.height = 0;
				line_info.width = 0;
			}
			if (display_info.__class === "Text") {
				if (display_info.text === "\n") {
					if (line_info.height < this._enter_key_height) {
						line_info.height = this._enter_key_height;
					}
					++ this._line_count;
					this._line_list[this._line_count - 1] = line_info;
					line_info = undefined;
					display_info = undefined;
					display_object = undefined;
					++ display_index;
					remain_width = total_width;
				} else if (display_info.text === "\t") {
					if (display_object === undefined) {
						let name = "nkacbjbsakcvuqocbakcbjcbvjhciqwojqppwvnwe";
						this._ctrl_sys.RegisterInfo(name, ALittle.String_CopyTable(display_info));
						display_object = this._ctrl_sys.CreateControl(name, this._link_map);
						this._ctrl_sys.UnRegisterInfo(name);
						display_object.text = "    ";
					}
					let object_width = display_object.width;
					let object_height = display_object.height;
					if (remain_width >= object_width) {
						++ line_info.child_count;
						line_info.childs[line_info.child_count - 1] = display_object;
						this.AddChild(display_object);
						line_info.width = line_info.width + object_width;
						if (line_info.height < object_height) {
							line_info.height = object_height;
						}
						remain_width = remain_width - object_width;
						if (remain_width <= 0) {
							++ this._line_count;
							this._line_list[this._line_count - 1] = line_info;
							line_info = undefined;
							remain_width = total_width;
						}
						display_object = undefined;
						display_info = undefined;
						++ display_index;
					} else {
						let count = display_object._show.CutTextByWidth(__floor(remain_width), display_info.text, __floor(total_width));
						if (count > 0) {
							display_object.text = __sub(display_info.text, 1, count);
							let new_display_info = ALittle.String_CopyTable(display_info);
							new_display_info.text = __sub(display_info.text, count + 1);
							++ line_info.child_count;
							line_info.childs[line_info.child_count - 1] = display_object;
							this.AddChild(display_object);
							line_info.width = line_info.width + display_object.width;
							if (line_info.height < object_height) {
								line_info.height = object_height;
							}
							++ this._line_count;
							this._line_list[this._line_count - 1] = line_info;
							line_info = undefined;
							remain_width = total_width;
							display_object = undefined;
							display_info = new_display_info;
						} else {
							++ this._line_count;
							this._line_list[this._line_count - 1] = line_info;
							line_info = undefined;
							remain_width = total_width;
						}
					}
				} else {
					if (display_info.text === "") {
						display_info = undefined;
						++ display_index;
					} else {
						if (display_object === undefined) {
							let name = "nkacbjbsakcvuqocbakcbjcbvjhciqwojqppwvnwe";
							this._ctrl_sys.RegisterInfo(name, ALittle.String_CopyTable(display_info));
							display_object = this._ctrl_sys.CreateControl(name, this._link_map);
							this._ctrl_sys.UnRegisterInfo(name);
						}
						let object_width = display_object.width;
						let object_height = display_object.height;
						let count = display_object._show.CutTextByWidth(__floor(remain_width), display_info.text, __floor(total_width));
						if (count === 0 && line_info.child_count === 0) {
							count = ALittle.String_GetByteCount(display_info.text, 1);
						}
						if (count === 0) {
							remain_width = 0;
						} else {
							display_object.text = __sub(display_info.text, 1, count);
							let new_display_info = ALittle.String_CopyTable(display_info);
							new_display_info.text = __sub(display_info.text, count + 1);
							++ line_info.child_count;
							line_info.childs[line_info.child_count - 1] = display_object;
							this.AddChild(display_object);
							line_info.width = line_info.width + display_object.width;
							if (line_info.height < object_height) {
								line_info.height = object_height;
							}
							remain_width = remain_width - display_object.width;
							display_object = undefined;
							display_info = new_display_info;
						}
						if (remain_width <= 0) {
							++ this._line_count;
							this._line_list[this._line_count - 1] = line_info;
							line_info = undefined;
							remain_width = total_width;
						}
					}
				}
			} else {
				if (display_object === undefined) {
					let name = "nkacbjbsakcvuqocbakcbjcbvjhciqwojqppwvnwe";
					this._ctrl_sys.RegisterInfo(name, ALittle.String_CopyTable(display_info));
					display_object = this._ctrl_sys.CreateControl(name, this._link_map);
					this._ctrl_sys.UnRegisterInfo(name);
				}
				let object_width = display_object.width;
				let object_height = display_object.height;
				if (remain_width >= object_width || (line_info.child_count === 0 && total_width <= object_width)) {
					++ line_info.child_count;
					line_info.childs[line_info.child_count - 1] = display_object;
					this.AddChild(display_object);
					line_info.width = line_info.width + display_object.width;
					if (line_info.height < object_height) {
						line_info.height = object_height;
					}
					remain_width = remain_width - object_width;
					if (remain_width <= 0) {
						++ this._line_count;
						this._line_list[this._line_count - 1] = line_info;
						line_info = undefined;
						remain_width = total_width;
					}
					display_object = undefined;
					display_info = undefined;
					++ display_index;
				} else {
					++ this._line_count;
					this._line_list[this._line_count - 1] = line_info;
					line_info = undefined;
					remain_width = total_width;
				}
			}
		}
		if (line_info !== undefined) {
			++ this._line_count;
			this._line_list[this._line_count - 1] = line_info;
		}
		this.RefreshX();
		this.RefreshY();
	},
	RefreshX : function() {
		if (this._line_list === undefined) {
			return;
		}
		let ___OBJECT_2 = this._line_list;
		for (let k = 1; k <= ___OBJECT_2.length; ++k) {
			let line = ___OBJECT_2[k - 1];
			if (line === undefined) break;
			let offset_x = 0.0;
			if (this._halign === ALittle.UIEnumTypes.HALIGN_CENTER) {
				offset_x = (this.width - line.width) / 2;
			} else if (this._halign === ALittle.UIEnumTypes.HALIGN_RIGHT) {
				offset_x = this.width - line.width;
			}
			let ___OBJECT_3 = line.childs;
			for (let index = 1; index <= ___OBJECT_3.length; ++index) {
				let child = ___OBJECT_3[index - 1];
				if (child === undefined) break;
				child.x = offset_x;
				offset_x = offset_x + child.width;
			}
		}
	},
	RefreshY : function() {
		if (this._line_list === undefined) {
			return;
		}
		this._real_height = 0;
		let line_count = 0;
		let ___OBJECT_4 = this._line_list;
		for (let k = 1; k <= ___OBJECT_4.length; ++k) {
			let line = ___OBJECT_4[k - 1];
			if (line === undefined) break;
			this._real_height = this._real_height + line.height;
			++ line_count;
		}
		this._real_height = this._real_height + (line_count - 1) * this._line_spacing;
		let offset_y = 0.0;
		if (this._valign === ALittle.UIEnumTypes.VALIGN_CENTER) {
			offset_y = (this.height - this._real_height) / 2;
		} else if (this._valign === ALittle.UIEnumTypes.VALIGN_BOTTOM) {
			offset_y = this.height - this._real_height;
		}
		let ___OBJECT_5 = this._line_list;
		for (let k = 1; k <= ___OBJECT_5.length; ++k) {
			let line = ___OBJECT_5[k - 1];
			if (line === undefined) break;
			let ___OBJECT_6 = line.childs;
			for (let index = 1; index <= ___OBJECT_6.length; ++index) {
				let child = ___OBJECT_6[index - 1];
				if (child === undefined) break;
				child.y = line.height - child.height + offset_y;
			}
			offset_y = offset_y + line.height + this._line_spacing;
		}
	},
}, "ALittle.RichArea");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1949279026, "ALittle.RichEditFontChangedEvent", {
name : "ALittle.RichEditFontChangedEvent", ns_name : "ALittle", rl_name : "RichEditFontChangedEvent", hash_code : 1949279026,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-1053992999, "ALittle.RichEditCursorClickEvent", {
name : "ALittle.RichEditCursorClickEvent", ns_name : "ALittle", rl_name : "RichEditCursorClickEvent", hash_code : -1053992999,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-923963966, "ALittle.RichEditCharInfo", {
name : "ALittle.RichEditCharInfo", ns_name : "ALittle", rl_name : "RichEditCharInfo", hash_code : -923963966,
name_list : ["acc_width","pre_width","text_info","text_object","text","ctrl_info","ctrl"],
type_list : ["double","double","ALittle.DisplayInfo","ALittle.Text","string","ALittle.DisplayInfo","ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-203792390, "ALittle.RichEditMultiDragEndEvent", {
name : "ALittle.RichEditMultiDragEndEvent", ns_name : "ALittle", rl_name : "RichEditMultiDragEndEvent", hash_code : -203792390,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(9565867, "ALittle.RichEditMultiDragBeginEvent", {
name : "ALittle.RichEditMultiDragBeginEvent", ns_name : "ALittle", rl_name : "RichEditMultiDragBeginEvent", hash_code : 9565867,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(291295687, "ALittle.RichEditMultiDragEvent", {
name : "ALittle.RichEditMultiDragEvent", ns_name : "ALittle", rl_name : "RichEditMultiDragEvent", hash_code : 291295687,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(556044369, "ALittle.RichEditLineInfo", {
name : "ALittle.RichEditLineInfo", ns_name : "ALittle", rl_name : "RichEditLineInfo", hash_code : 556044369,
name_list : ["char_list","char_count","child_list","child_count","container","acc_height","pre_height","force_line"],
type_list : ["List<ALittle.RichEditCharInfo>","int","List<ALittle.DisplayObject>","int","ALittle.DisplayLayout","double","double","bool"],
option_map : {}
})
ALittle.RegStruct(774620468, "ALittle.UIRichEditLongClickEvent", {
name : "ALittle.UIRichEditLongClickEvent", ns_name : "ALittle", rl_name : "UIRichEditLongClickEvent", hash_code : 774620468,
name_list : ["target","abs_x","abs_y","rel_x","rel_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double"],
option_map : {}
})

let __byte = ALittle.String_Byte;
let __sub = ALittle.String_Sub;
let __find = ALittle.String_Find;
let __floor = ALittle.Math_Floor;
let __len = ALittle.String_Len;
let __abs = ALittle.Math_Abs;
let __type = ALittle.String_Type;
if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.RichEdit = JavaScript.Class(ALittle.DisplayLayout, {
	CharIsNumber : function(str) {
		let c = __byte(str, 1);
		return c >= 48 && c <= 57;
	},
	CharIsLetter : function(str) {
		let c = __byte(str, 1);
		return c >= 65 && c <= 90 || c >= 97 && c <= 122;
	},
	CompareTextInfo : function(a, b) {
		if (a.font_path !== b.font_path) {
			return false;
		}
		if (a.font_size !== b.font_size) {
			return false;
		}
		if (a.red !== b.red) {
			return false;
		}
		if (a.green !== b.green) {
			return false;
		}
		if (a.blue !== b.blue) {
			return false;
		}
		if (a.bold !== b.bold) {
			return false;
		}
		if (a.italic !== b.italic) {
			return false;
		}
		if (a.underline !== b.underline) {
			return false;
		}
		if (a.deleteline !== b.deleteline) {
			return false;
		}
		if (a.outline !== b.outline) {
			return false;
		}
		return true;
	},
	CopyTextInfo : function(b) {
		let a = {};
		a.__class = "Text";
		a.font_path = b.font_path;
		a.font_size = b.font_size;
		a.red = b.red;
		a.green = b.green;
		a.blue = b.blue;
		a.bold = b.bold;
		a.italic = b.italic;
		a.underline = b.underline;
		a.deleteline = b.deleteline;
		a.outline = b.outline;
		return a;
	},
	InitTextInfo : function() {
		let font_text = this._font_text;
		let a = {};
		a.__class = "Text";
		a.font_path = font_text.font_path;
		a.font_size = font_text.font_size;
		a.red = font_text.red;
		a.green = font_text.green;
		a.blue = font_text.blue;
		a.bold = font_text.bold;
		a.italic = font_text.italic;
		a.underline = font_text.underline;
		a.deleteline = font_text.deleteline;
		a.outline = font_text.outline;
		return a;
	},
	SetDrawText : function(font_text) {
		let draw_text = this._draw_text;
		draw_text.font_path = font_text.font_path;
		draw_text.font_size = font_text.font_size;
		draw_text.red = font_text.red;
		draw_text.green = font_text.green;
		draw_text.blue = font_text.blue;
		draw_text.bold = font_text.bold;
		draw_text.italic = font_text.italic;
		draw_text.underline = font_text.underline;
		draw_text.deleteline = font_text.deleteline;
		draw_text.outline = font_text.outline;
	},
	UpdateFontText : function() {
		let line_list = this._line_list;
		let char_info = line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1];
		let is_change = false;
		let font_text = this._font_text;
		let text_info = char_info.text_info;
		if (font_text.font_path !== text_info.font_path) {
			font_text.font_path = text_info.font_path;
			is_change = true;
		}
		if (font_text.font_size !== text_info.font_size) {
			font_text.font_size = text_info.font_size;
			is_change = true;
		}
		if (font_text.red !== text_info.red) {
			font_text.red = text_info.red;
			is_change = true;
		}
		if (font_text.green !== text_info.green) {
			font_text.green = text_info.green;
			is_change = true;
		}
		if (font_text.blue !== text_info.blue) {
			font_text.blue = text_info.blue;
			is_change = true;
		}
		if (font_text.bold !== text_info.bold) {
			font_text.bold = text_info.bold;
			is_change = true;
		}
		if (font_text.italic !== text_info.italic) {
			font_text.italic = text_info.italic;
			is_change = true;
		}
		if (font_text.underline !== text_info.underline) {
			font_text.underline = text_info.underline;
			is_change = true;
		}
		if (font_text.deleteline !== text_info.deleteline) {
			font_text.deleteline = text_info.deleteline;
			is_change = true;
		}
		if (font_text.outline !== text_info.outline) {
			font_text.outline = text_info.outline;
			is_change = true;
		}
		if (is_change) {
			this.DispatchEvent(___all_struct.get(1949279026), {});
		}
	},
	CheckDisplayList : function(content) {
		let ___OBJECT_1 = content;
		for (let k = 1; k <= ___OBJECT_1.length; ++k) {
			let v = ___OBJECT_1[k - 1];
			if (v === undefined) break;
			if (v.__class === undefined) {
				return false;
			}
		}
		return true;
	},
	DisplayListToCharInfoList : function(display_list, default_text_info) {
		let char_info_list = [];
		let char_info_list_count = 0;
		let last_text_info = default_text_info;
		let ___OBJECT_2 = display_list;
		for (let display_index = 1; display_index <= ___OBJECT_2.length; ++display_index) {
			let display_info = ___OBJECT_2[display_index - 1];
			if (display_info === undefined) break;
			if (display_info.__class === "Text") {
				let new_char_info = {};
				new_char_info.acc_width = 0;
				new_char_info.pre_width = 0;
				new_char_info.text_info = this.CopyTextInfo(display_info);
				new_char_info.text_object = undefined;
				new_char_info.text = display_info.text;
				new_char_info.ctrl_info = undefined;
				new_char_info.ctrl = undefined;
				++ char_info_list_count;
				char_info_list[char_info_list_count - 1] = new_char_info;
				last_text_info = new_char_info.text_info;
			} else {
				if (last_text_info === undefined) {
					last_text_info = this.InitTextInfo();
				}
				let new_char_info = {};
				new_char_info.acc_width = 0;
				new_char_info.pre_width = 0;
				new_char_info.text_info = last_text_info;
				new_char_info.text_object = undefined;
				new_char_info.text = "";
				new_char_info.ctrl_info = display_info;
				new_char_info.ctrl = undefined;
				++ char_info_list_count;
				char_info_list[char_info_list_count - 1] = new_char_info;
			}
		}
		return char_info_list;
	},
	GetCharInfoList : function() {
		let char_info_list = [];
		let char_info_list_count = 0;
		let ___OBJECT_3 = this._line_list;
		for (let line_index = 1; line_index <= ___OBJECT_3.length; ++line_index) {
			let line_info = ___OBJECT_3[line_index - 1];
			if (line_info === undefined) break;
			let ___OBJECT_4 = line_info.char_list;
			for (let char_index = 1; char_index <= ___OBJECT_4.length; ++char_index) {
				let char_info = ___OBJECT_4[char_index - 1];
				if (char_info === undefined) break;
				++ char_info_list_count;
				char_info_list[char_info_list_count - 1] = char_info;
			}
		}
		return char_info_list;
	},
	JoinCharInfoList : function(char_info_list) {
		let new_char_info_list = [];
		let new_char_info_list_count = 0;
		let text_info = undefined;
		let text_list = undefined;
		let text_list_count = 0;
		let ___OBJECT_5 = char_info_list;
		for (let char_index = 1; char_index <= ___OBJECT_5.length; ++char_index) {
			let char_info = ___OBJECT_5[char_index - 1];
			if (char_info === undefined) break;
			if (char_info.ctrl_info === undefined) {
				if (text_info === undefined) {
					text_info = char_info.text_info;
					text_list = [];
					text_list_count = 1;
					text_list[text_list_count - 1] = char_info.text;
				} else if (text_info === char_info.text_info) {
					++ text_list_count;
					text_list[text_list_count - 1] = char_info.text;
				} else {
					if (this.CompareTextInfo(text_info, char_info.text_info)) {
						++ text_list_count;
						text_list[text_list_count - 1] = char_info.text;
					} else {
						let text = ALittle.String_Join(text_list, "");
						if (text !== "") {
							let new_char_info = {};
							new_char_info.acc_width = 0;
							new_char_info.pre_width = 0;
							new_char_info.text_info = text_info;
							new_char_info.text_object = undefined;
							new_char_info.text = text;
							new_char_info.ctrl_info = undefined;
							new_char_info.ctrl = undefined;
							++ new_char_info_list_count;
							new_char_info_list[new_char_info_list_count - 1] = new_char_info;
						}
						text_info = char_info.text_info;
						text_list = [];
						text_list_count = 1;
						text_list[text_list_count - 1] = char_info.text;
					}
				}
			} else {
				if (text_info !== undefined) {
					let text = ALittle.String_Join(text_list, "");
					if (text !== "") {
						let new_char_info = {};
						new_char_info.acc_width = 0;
						new_char_info.pre_width = 0;
						new_char_info.text_info = text_info;
						new_char_info.text_object = undefined;
						new_char_info.text = text;
						new_char_info.ctrl_info = undefined;
						new_char_info.ctrl = undefined;
						++ new_char_info_list_count;
						new_char_info_list[new_char_info_list_count - 1] = new_char_info;
					}
					text_info = undefined;
					text_list = undefined;
					text_list_count = 0;
				}
				let new_char_info = {};
				new_char_info.acc_width = 0;
				new_char_info.pre_width = 0;
				new_char_info.text_info = text_info;
				new_char_info.text_object = undefined;
				new_char_info.text = undefined;
				new_char_info.ctrl_info = char_info.ctrl_info;
				new_char_info.ctrl = char_info.ctrl;
				++ new_char_info_list_count;
				new_char_info_list[new_char_info_list_count - 1] = new_char_info;
			}
		}
		if (text_info !== undefined) {
			let text = ALittle.String_Join(text_list, "");
			if (text !== "") {
				let new_char_info = {};
				new_char_info.acc_width = 0;
				new_char_info.pre_width = 0;
				new_char_info.text_info = text_info;
				new_char_info.text_object = undefined;
				new_char_info.text = text;
				new_char_info.ctrl_info = undefined;
				new_char_info.ctrl = undefined;
				++ new_char_info_list_count;
				new_char_info_list[new_char_info_list_count - 1] = new_char_info;
			}
		}
		return new_char_info_list;
	},
	CharInfoListToDisplayList : function(list) {
		let display_list = [];
		let display_list_count = 0;
		let text_info = undefined;
		let text_list = undefined;
		let text_list_count = 0;
		let ___OBJECT_6 = list;
		for (let char_index = 1; char_index <= ___OBJECT_6.length; ++char_index) {
			let char_info = ___OBJECT_6[char_index - 1];
			if (char_info === undefined) break;
			if (char_info.ctrl_info === undefined) {
				if (text_info === undefined) {
					text_info = char_info.text_info;
					text_list = [];
					text_list_count = 1;
					text_list[text_list_count - 1] = char_info.text;
				} else if (text_info === char_info.text_info) {
					++ text_list_count;
					text_list[text_list_count - 1] = char_info.text;
				} else {
					if (this.CompareTextInfo(text_info, char_info.text_info)) {
						++ text_list_count;
						text_list[text_list_count - 1] = char_info.text;
					} else {
						let text = ALittle.String_Join(text_list, "");
						if (text !== "") {
							let text_ctrl = ALittle.String_CopyTable(text_info);
							text_ctrl.__class = "Text";
							text_ctrl.text = text;
							++ display_list_count;
							display_list[display_list_count - 1] = text_ctrl;
						}
						text_info = char_info.text_info;
						text_list = [];
						text_list_count = 1;
						text_list[text_list_count - 1] = char_info.text;
					}
				}
			} else {
				if (text_info !== undefined) {
					let text = ALittle.String_Join(text_list, "");
					if (text !== "") {
						let text_ctrl = ALittle.String_CopyTable(text_info);
						text_ctrl.__class = "Text";
						text_ctrl.text = text;
						++ display_list_count;
						display_list[display_list_count - 1] = text_ctrl;
					}
					text_info = undefined;
					text_list = undefined;
					text_list_count = 0;
				}
				++ display_list_count;
				display_list[display_list_count - 1] = ALittle.String_CopyTable(char_info.ctrl_info);
			}
		}
		if (text_info !== undefined) {
			let text = ALittle.String_Join(text_list, "");
			if (text !== "") {
				let text_ctrl = ALittle.String_CopyTable(text_info);
				text_ctrl.__class = "Text";
				text_ctrl.text = text;
				++ display_list_count;
				display_list[display_list_count - 1] = text_ctrl;
			}
		}
		return display_list;
	},
	CharInfoListToWord : function(list) {
		let text_list = [];
		let text_list_count = 0;
		let ___OBJECT_7 = list;
		for (let char_index = 1; char_index <= ___OBJECT_7.length; ++char_index) {
			let char_info = ___OBJECT_7[char_index - 1];
			if (char_info === undefined) break;
			if (char_info.ctrl_info === undefined) {
				++ text_list_count;
				text_list[text_list_count - 1] = char_info.text;
			}
		}
		return ALittle.String_Join(text_list, "");
	},
	SplitText : function(char_info, char_info_list, char_info_list_count) {
		let text = char_info.text;
		while (true) {
			let start_index_1 = __find(text, "\n");
			let start_index_2 = __find(text, "\t");
			if (start_index_1 !== undefined && start_index_2 !== undefined) {
				if (start_index_1 < start_index_2) {
					start_index_2 = undefined;
				} else {
					start_index_1 = undefined;
				}
			}
			if (start_index_1 !== undefined) {
				let new_char_info = ALittle.String_CopyTable(char_info);
				new_char_info.text = __sub(text, 1, start_index_1 - 1);
				++ char_info_list_count;
				char_info_list[char_info_list_count - 1] = new_char_info;
				new_char_info = ALittle.String_CopyTable(char_info);
				new_char_info.text = "\n";
				++ char_info_list_count;
				char_info_list[char_info_list_count - 1] = new_char_info;
				text = __sub(text, start_index_1 + 1);
			} else if (start_index_2 !== undefined) {
				let new_char_info = ALittle.String_CopyTable(char_info);
				new_char_info.text = __sub(text, 1, start_index_2 - 1);
				++ char_info_list_count;
				char_info_list[char_info_list_count - 1] = new_char_info;
				new_char_info = ALittle.String_CopyTable(char_info);
				new_char_info.text = "\t";
				++ char_info_list_count;
				char_info_list[char_info_list_count - 1] = new_char_info;
				text = __sub(text, start_index_2 + 1);
			} else {
				if (text !== "") {
					let new_char_info = ALittle.String_CopyTable(char_info);
					new_char_info.text = text;
					++ char_info_list_count;
					char_info_list[char_info_list_count - 1] = new_char_info;
				}
				break;
			}
		}
		return char_info_list_count;
	},
	GetCursorWidth : function(font_size) {
		if (font_size === undefined || font_size < 15) {
			return 1;
		}
		if (font_size > 100) {
			return 10;
		}
		return __floor((font_size / 100) * 10);
	},
	Ctor : function(ctrl_sys) {
		this._enter_key_height = 20;
		this._line_list = [];
		this._line_count = 0;
		this._font_text = ALittle.NewObject(ALittle.Text, this._ctrl_sys);
		this._draw_text = ALittle.NewObject(ALittle.Text, this._ctrl_sys);
		this._line_start_it = undefined;
		this._line_cursor_it = undefined;
		this._char_cursor_it = undefined;
		this._line_select_it = undefined;
		this._char_select_it = undefined;
		this._scroll_list = ALittle.NewObject(ALittle.ScrollList, this._ctrl_sys);
		this._scroll_list.right_scrollbar = ALittle.NewObject(ALittle.ScrollBar, this._ctrl_sys);
		this._scroll_list.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
		this._scroll_list.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
		this._scroll_list.x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this._scroll_list.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this.AddChild(this._scroll_list);
		this._current_flash_alpha = 1;
		this._current_flash_dir = -0.05;
		this._cursor = ALittle.NewObject(ALittle.Quad, this._ctrl_sys);
		this.AddChild(this._cursor);
		this._cursor.visible = false;
		this._cursor.width = 1;
		this._select_1 = ALittle.NewObject(ALittle.Quad, this._ctrl_sys);
		this.AddChild(this._select_1);
		this._select_1.visible = false;
		this._select_1.alpha = 0.5;
		this._select_2 = ALittle.NewObject(ALittle.Quad, this._ctrl_sys);
		this.AddChild(this._select_2);
		this._select_2.visible = false;
		this._select_2.alpha = 0.5;
		this._select_3 = ALittle.NewObject(ALittle.Quad, this._ctrl_sys);
		this.AddChild(this._select_3);
		this._select_3.visible = false;
		this._select_3.alpha = 0.5;
		this._start_cursor = ALittle.NewObject(ALittle.Quad, this._ctrl_sys);
		this._start_cursor.width = 1;
		this._end_cursor = ALittle.NewObject(ALittle.Quad, this._ctrl_sys);
		this._end_cursor.width = 1;
		this._start_cursor_data = undefined;
		this._end_cursor_data = undefined;
		this._focus_cursor = true;
		this._is_focus = false;
		this._event_start_x = 0;
		this._event_end_x = 0;
		this._event_start_y = 0;
		this._event_end_y = 0;
		this._start_it_delta = 0;
		this._click_drag_delta_x = 0;
		this._click_drag_delta_y = 0;
		this._is_click = false;
		this._is_longclick = false;
		this._is_click_cursor = false;
		this._is_click_cursor_name = "";
		this._drag_delta_x = 0;
		this._drag_delta_y = 0;
		this.AddChild(this._start_cursor);
		this.AddChild(this._end_cursor);
		this._start_cursor.visible = false;
		this._end_cursor.visible = false;
		this._cursor_margin_up = 0;
		this._cursor_margin_down = 0;
		this._margin_halign = 0;
		this._margin_valign = 0;
		this._line_spacing = 0;
		this._is_drag_begin = false;
		this._ims_padding = 0;
		this._default_text_area = ALittle.NewObject(ALittle.TextArea, this._ctrl_sys);
		this._default_text_area.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
		this._default_text_area.height = 0;
		this._default_text_area.x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this._default_text_area.y = 0;
		this.AddChild(this._default_text_area);
		this._link_map = ALittle.CreateValueWeakMap();
		this._pickup_rect = true;
		this._pickup_child = false;
		this._pickup_this = true;
		this._editable = true;
		this._is_selecting = false;
		this._can_drag_text = true;
		this._auto_ims = true;
		this._multi_cursor = false;
		this._can_scroll = true;
		this._regex = "";
		this._limit_len = 0;
		this.AddEventListener(___all_struct.get(292776509), this, this.HandleFocusOut);
		this.AddEventListener(___all_struct.get(-644464135), this, this.HandleFocusIn);
		this.AddEventListener(___all_struct.get(544684311), this, this.HandleMoveIn);
		this.AddEventListener(___all_struct.get(-1202439334), this, this.HandleMoveOut);
		this.AddEventListener(___all_struct.get(1883782801), this, this.HandleLButtonDown);
		this.AddEventListener(___all_struct.get(40651933), this, this.HandleLButtonUp);
		this.AddEventListener(___all_struct.get(-1234078962), this, this.HandleTextInput);
		this.AddEventListener(___all_struct.get(-1604617962), this, this.HandleKeyDown);
		this.AddEventListener(___all_struct.get(1301789264), this, this.HandleDragBegin);
		this.AddEventListener(___all_struct.get(1337289812), this, this.HandleDrag);
		this.AddEventListener(___all_struct.get(150587926), this, this.HandleDragEnd);
		this.AddEventListener(___all_struct.get(-1737121315), this, this.HandleMButtonWheel);
		this.AddEventListener(___all_struct.get(-439548260), this, this.HandleLongLButtonDown);
		this.ClearText();
		if (this._loop === undefined) {
			this._loop = ALittle.NewObject(ALittle.LoopFunction, this.Update.bind(this), -1, 1, 1);
		}
		A_LoopSystem.AddUpdater(this._loop);
	},
	GetCursor : function() {
		return this._cursor;
	},
	get link_map() {
		return this._link_map;
	},
	ClearLinkMap : function() {
		this._link_map = ALittle.CreateValueWeakMap();
	},
	get real_height() {
		return this._line_list[this._line_count - 1].acc_height;
	},
	get real_edit_height() {
		let line_list = this._line_list;
		let last_line = line_list[this._line_count - 1];
		if (last_line.acc_height !== last_line.pre_height) {
			return last_line.acc_height;
		}
		return last_line.acc_height + this._enter_key_height;
	},
	get can_drag_text() {
		return this._can_drag_text;
	},
	set can_drag_text(value) {
		this._can_drag_text = value;
	},
	set auto_ims(value) {
		this._auto_ims = value;
	},
	get auto_ims() {
		return this._auto_ims;
	},
	get multi_cursor() {
		return this._multi_cursor;
	},
	set width(value) {
		if (this.width === value) {
			return;
		}
		ALittle.DisplayLayout.__setter.width.call(this, value);
		let char_info_list = this.GetCharInfoList();
		this.ClearText();
		this.InsertTextImpl(char_info_list, false);
		this.ResetCursor();
	},
	set height(value) {
		if (this.height === value) {
			return;
		}
		ALittle.DisplayLayout.__setter.height.call(this, value);
		this._default_text_area.y = this._scroll_list.y;
		this._default_text_area.height = this._default_text_area.real_height;
		if (this._default_text_area.height > this._scroll_list.height) {
			this._default_text_area.height = this._scroll_list.height;
		}
		this.ResetCursorLine();
		this.ResetCursor();
	},
	set cursor_red(value) {
		this._cursor.red = value;
		this._select_1.red = value;
		this._select_2.red = value;
		this._select_3.red = value;
	},
	get cursor_red() {
		return this._cursor.red;
	},
	set cursor_green(value) {
		this._cursor.green = value;
		this._select_1.green = value;
		this._select_2.green = value;
		this._select_3.green = value;
	},
	get cursor_green() {
		return this._cursor.green;
	},
	set cursor_blue(value) {
		this._cursor.blue = value;
		this._select_1.blue = value;
		this._select_2.blue = value;
		this._select_3.blue = value;
	},
	get cursor_blue() {
		return this._cursor.blue;
	},
	ShowCursor : function(value) {
		if (this._multi_cursor === false) {
			if (value) {
				if (this._select_1.visible === false) {
					this._cursor.visible = value;
				} else {
					this._cursor.visible = false;
				}
			} else {
				this._cursor.visible = (this._select_1.visible === false);
			}
		}
	},
	set font_bold(value) {
		if (this._font_text.bold === value) {
			return;
		}
		this._font_text.bold = value;
		this._default_text_area.bold = value;
		let char_info_list = this.GetCharInfoList();
		this.ClearText();
		this.InsertTextImpl(char_info_list, false);
		this.ResetCursor();
	},
	set font_underline(value) {
		if (this._font_text.underline === value) {
			return;
		}
		this._font_text.underline = value;
		this._default_text_area.underline = value;
	},
	set font_deleteline(value) {
		if (this._font_text.deleteline === value) {
			return;
		}
		this._font_text.deleteline = value;
		this._default_text_area.deleteline = value;
	},
	set font_italic(value) {
		if (this._font_text.italic === value) {
			return;
		}
		this._font_text.italic = value;
		this._default_text_area.italic = value;
	},
	set font_outline(value) {
		if (this._font_text.outline === value) {
			return;
		}
		this._font_text.outline = value;
		this._default_text_area.outline = value;
	},
	set font_path(value) {
		if (this._font_text.font_path === value) {
			return;
		}
		this._font_text.font_path = value;
		this._default_text_area.font_path = value;
		this._default_text_area.height = this._default_text_area.real_height;
		if (this._default_text_area.height > this._scroll_list.height) {
			this._default_text_area.height = this._scroll_list.height;
		}
		if (this._font_text.font_path !== undefined && this._font_text.font_size !== undefined) {
			this._enter_key_height = this._font_text.native_show.GetFontHeight();
			let char_info_list = this.GetCharInfoList();
			this.ClearText();
			this.InsertTextImpl(char_info_list, false);
			this.ResetCursor();
		}
	},
	set font_size(value) {
		if (this._font_text.font_size === value) {
			return;
		}
		this._font_text.font_size = value;
		this._default_text_area.font_size = value;
		this._default_text_area.height = this._default_text_area.real_height;
		if (this._default_text_area.height > this._scroll_list.height) {
			this._default_text_area.height = this._scroll_list.height;
		}
		if (this._font_text.font_path !== undefined && this._font_text.font_size !== undefined) {
			this._enter_key_height = this._font_text.native_show.GetFontHeight();
			let char_info_list = this.GetCharInfoList();
			this.ClearText();
			this.InsertTextImpl(char_info_list, false);
			this.ResetCursor();
		}
	},
	get font_path() {
		return this._font_text.font_path;
	},
	get font_size() {
		return this._font_text.font_size;
	},
	set font_red(value) {
		if (this._font_text.red === value) {
			return;
		}
		this._font_text.red = value;
		this._default_text_area.red = value;
	},
	get font_red() {
		return this._font_text.red;
	},
	set font_green(value) {
		if (this._font_text.green === value) {
			return;
		}
		this._font_text.green = value;
		this._default_text_area.green = value;
	},
	get font_green() {
		return this._font_text.green;
	},
	set font_blue(value) {
		if (this._font_text.blue === value) {
			return;
		}
		this._font_text.blue = value;
		this._default_text_area.blue = value;
	},
	get font_blue() {
		return this._font_text.blue;
	},
	set default_text(value) {
		this._default_text_area.text = value;
		this._default_text_area.height = this._default_text_area.real_height;
		if (this._default_text_area.height > this._scroll_list.height) {
			this._default_text_area.height = this._scroll_list.height;
		}
	},
	set text(value) {
		this.ClearText();
		this.InsertTextNative(value);
		this.ShowDefaultText();
	},
	get text() {
		let displaylist = this.CharInfoListToDisplayList(this.GetCharInfoList());
		let text = "";
		let ___OBJECT_8 = displaylist;
		for (let k = 1; k <= ___OBJECT_8.length; ++k) {
			let v = ___OBJECT_8[k - 1];
			if (v === undefined) break;
			if (v.__class === "Text") {
				text = text + v.text;
			}
		}
		return text;
	},
	get default_text() {
		return this._default_text_area.text;
	},
	set default_text_alpha(value) {
		this._default_text_area.alpha = value;
	},
	get default_text_alpha() {
		return this._default_text_area.alpha;
	},
	set display_list(value) {
		let char_info_list = this.DisplayListToCharInfoList(value);
		this.ClearText();
		this.InsertTextImpl(char_info_list, false);
		this.ResetCursor();
		this.ShowDefaultText();
	},
	get display_list() {
		return this.CharInfoListToDisplayList(this.GetCharInfoList());
	},
	set start_cursor(value) {
		if (value === this._start_cursor) {
			return;
		}
		this.RemoveChild(this._start_cursor);
		value.x_type = ALittle.UIEnumTypes.POS_ABS;
		value.y_type = ALittle.UIEnumTypes.POS_ABS;
		value.width_type = ALittle.UIEnumTypes.SIZE_ABS;
		value.height_type = ALittle.UIEnumTypes.SIZE_ABS;
		this._start_cursor = value;
		this.AddChild(this._start_cursor);
		this._start_cursor.visible = false;
		this.ResetCursor();
	},
	get start_cursor() {
		return this._start_cursor;
	},
	set end_cursor(value) {
		if (value === this._end_cursor) {
			return;
		}
		this.RemoveChild(this._end_cursor);
		value.x_type = ALittle.UIEnumTypes.POS_ABS;
		value.y_type = ALittle.UIEnumTypes.POS_ABS;
		value.width_type = ALittle.UIEnumTypes.SIZE_ABS;
		value.height_type = ALittle.UIEnumTypes.SIZE_ABS;
		this._end_cursor = value;
		this.AddChild(this._end_cursor);
		this._end_cursor.visible = false;
		this.ResetCursor();
	},
	get end_cursor() {
		return this._end_cursor;
	},
	set cursor_margin_up(value) {
		if (value === this._cursor_margin_up) {
			return;
		}
		this._cursor_margin_up = value;
		this.ResetCursor();
	},
	get cursor_margin_up() {
		return this._cursor_margin_up;
	},
	set cursor_margin_down(value) {
		if (value === this._cursor_margin_down) {
			return;
		}
		this._cursor_margin_down = value;
		this.ResetCursor();
	},
	get cursor_margin_down() {
		return this._cursor_margin_down;
	},
	set margin_halign(value) {
		if (value === this._margin_halign) {
			return;
		}
		this._margin_halign = value;
		this._scroll_list.width_value = this._margin_halign * 2;
		this._default_text_area.width_value = this._margin_halign * 2;
		let char_info_list = this.GetCharInfoList();
		this.ClearText();
		this.InsertTextImpl(char_info_list, false);
		this.ResetCursor();
	},
	get margin_halign() {
		return this._margin_halign;
	},
	set margin_valign(value) {
		if (value === this._margin_valign) {
			return;
		}
		this._margin_valign = value;
		this._scroll_list.height_value = this._margin_valign * 2;
		this._default_text_area.y = this._scroll_list.y;
		this._default_text_area.height = this._default_text_area.real_height;
		if (this._default_text_area.height > this._scroll_list.height) {
			this._default_text_area.height = this._scroll_list.height;
		}
		let char_info_list = this.GetCharInfoList();
		this.ClearText();
		this.InsertTextImpl(char_info_list, false);
		this.ResetCursor();
	},
	set line_spacing(value) {
		if (this._line_spacing === this._line_spacing) {
			return;
		}
		this._line_spacing = value;
		this._scroll_list.gap = value;
	},
	get line_spacing() {
		return this._line_spacing;
	},
	get margin_valign() {
		return this._margin_valign;
	},
	set focus_cursor(value) {
		this._focus_cursor = value;
	},
	get focus_cursor() {
		return this._focus_cursor;
	},
	get cursor_x() {
		return this._cursor.x;
	},
	get cursor_y() {
		return this._cursor.y;
	},
	get start_cursor_x() {
		return this._event_start_x;
	},
	get start_cursor_y() {
		return this._event_start_y;
	},
	get end_cursor_x() {
		return this._event_end_x;
	},
	get end_cursor_y() {
		return this._event_end_y;
	},
	get regex() {
		return this._regex;
	},
	set regex(value) {
		if (value === undefined) {
			value = "";
		}
		this._regex = value;
	},
	get limit_len() {
		return this._limit_len;
	},
	set limit_len(value) {
		if (value === undefined) {
			value = 0;
		}
		this._limit_len = value;
	},
	GetLineWidth : function(value) {
		let line = this._line_list[value - 1];
		if (line === undefined) {
			return 0;
		}
		return line.char_list[line.char_count - 1].acc_width;
	},
	GetScrollOffset : function() {
		if (this._line_start_it === undefined) {
			return 0;
		}
		return this._line_list[this._line_start_it - 1].pre_height + this._start_it_delta;
	},
	GetLineCount : function() {
		return this._line_count;
	},
	Update : function() {
		if (this._cursor.abs_visible) {
			this._current_flash_alpha = this._current_flash_alpha + this._current_flash_dir;
			if ((this._current_flash_dir < 0 && this._current_flash_alpha < -0.05) || (this._current_flash_dir > 0 && this._current_flash_alpha > 1.5)) {
				this._current_flash_dir = -this._current_flash_dir;
			}
			this._cursor.alpha = this._current_flash_alpha;
		}
	},
	GetSelectText : function() {
		let line_list = this._line_list;
		let select_text = [];
		let select_text_count = 0;
		if (this._char_select_it > line_list[this._line_select_it - 1].char_count) {
			return [];
		}
		if (line_list[this._line_select_it - 1].pre_height > line_list[this._line_cursor_it - 1].pre_height) {
			let line_it = this._line_cursor_it;
			while (true) {
				let char_it = undefined;
				let char_end = undefined;
				if (line_it === this._line_cursor_it) {
					char_it = this._char_cursor_it;
					char_it = char_it + 1;
				} else {
					char_it = 1;
				}
				if (line_it === this._line_select_it) {
					char_end = this._char_select_it;
					char_end = char_end + 1;
				} else {
					char_end = line_list[line_it - 1].char_count + 1;
				}
				let line = line_list[line_it - 1];
				while (char_it !== char_end) {
					++ select_text_count;
					select_text[select_text_count - 1] = line.char_list[char_it - 1];
					char_it = char_it + 1;
				}
				if (line_it === this._line_select_it) {
					break;
				}
				line_it = line_it + 1;
			}
		} else if (line_list[this._line_select_it - 1].pre_height < line_list[this._line_cursor_it - 1].pre_height) {
			let line_it = this._line_select_it;
			while (true) {
				let char_it = undefined;
				let char_end = undefined;
				if (line_it === this._line_select_it) {
					char_it = this._char_select_it;
					char_it = char_it + 1;
				} else {
					char_it = 1;
				}
				if (line_it === this._line_cursor_it) {
					char_end = this._char_cursor_it;
					char_end = char_end + 1;
				} else {
					char_end = line_list[line_it - 1].char_count + 1;
				}
				let line = line_list[line_it - 1];
				while (char_it !== char_end) {
					++ select_text_count;
					select_text[select_text_count - 1] = line.char_list[char_it - 1];
					char_it = char_it + 1;
				}
				if (line_it === this._line_cursor_it) {
					break;
				}
				line_it = line_it + 1;
			}
		} else {
			if (line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width > line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width) {
				let char_it = this._char_select_it;
				let char_end = this._char_cursor_it;
				char_end = char_end + 1;
				char_it = char_it + 1;
				let line = line_list[this._line_cursor_it - 1];
				while (char_it !== char_end) {
					++ select_text_count;
					select_text[select_text_count - 1] = line.char_list[char_it - 1];
					char_it = char_it + 1;
				}
			} else if (line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width < line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width) {
				let char_it = this._char_cursor_it;
				let char_end = this._char_select_it;
				char_end = char_end + 1;
				char_it = char_it + 1;
				let line = line_list[this._line_cursor_it - 1];
				while (char_it !== char_end) {
					++ select_text_count;
					select_text[select_text_count - 1] = line.char_list[char_it - 1];
					char_it = char_it + 1;
				}
			}
		}
		return this.CharInfoListToDisplayList(select_text);
	},
	GetSelectWord : function() {
		let line_list = this._line_list;
		let select_text = [];
		let select_text_count = 0;
		if (this._char_select_it > line_list[this._line_select_it - 1].char_count) {
			return "";
		}
		if (line_list[this._line_select_it - 1].pre_height > line_list[this._line_cursor_it - 1].pre_height) {
			let line_it = this._line_cursor_it;
			while (true) {
				let char_it = undefined;
				let char_end = undefined;
				if (line_it === this._line_cursor_it) {
					char_it = this._char_cursor_it;
					char_it = char_it + 1;
				} else {
					char_it = 1;
				}
				if (line_it === this._line_select_it) {
					char_end = this._char_select_it;
					char_end = char_end + 1;
				} else {
					char_end = line_list[line_it - 1].char_count + 1;
				}
				let line = line_list[line_it - 1];
				while (char_it !== char_end) {
					++ select_text_count;
					select_text[select_text_count - 1] = line.char_list[char_it - 1];
					char_it = char_it + 1;
				}
				if (line_it === this._line_select_it) {
					break;
				}
				line_it = line_it + 1;
			}
		} else if (line_list[this._line_select_it - 1].pre_height < line_list[this._line_cursor_it - 1].pre_height) {
			let line_it = this._line_select_it;
			while (true) {
				let char_it = undefined;
				let char_end = undefined;
				if (line_it === this._line_select_it) {
					char_it = this._char_select_it;
					char_it = char_it + 1;
				} else {
					char_it = 1;
				}
				if (line_it === this._line_cursor_it) {
					char_end = this._char_cursor_it;
					char_end = char_end + 1;
				} else {
					char_end = line_list[line_it - 1].char_count + 1;
				}
				let line = line_list[line_it - 1];
				while (char_it !== char_end) {
					++ select_text_count;
					select_text[select_text_count - 1] = line.char_list[char_it - 1];
					char_it = char_it + 1;
				}
				if (line_it === this._line_cursor_it) {
					break;
				}
				line_it = line_it + 1;
			}
		} else {
			if (line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width > line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width) {
				let char_it = this._char_select_it;
				let char_end = this._char_cursor_it;
				char_end = char_end + 1;
				char_it = char_it + 1;
				let line = line_list[this._line_cursor_it - 1];
				while (char_it !== char_end) {
					++ select_text_count;
					select_text[select_text_count - 1] = line.char_list[char_it - 1];
					char_it = char_it + 1;
				}
			} else if (line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width < line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width) {
				let char_it = this._char_cursor_it;
				let char_end = this._char_select_it;
				char_end = char_end + 1;
				char_it = char_it + 1;
				let line = line_list[this._line_cursor_it - 1];
				while (char_it !== char_end) {
					++ select_text_count;
					select_text[select_text_count - 1] = line.char_list[char_it - 1];
					char_it = char_it + 1;
				}
			}
		}
		return this.CharInfoListToWord(select_text);
	},
	DeleteSelectText : function() {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return false;
		}
		let line_list = this._line_list;
		if (this._char_select_it > line_list[this._line_select_it - 1].char_count) {
			return false;
		}
		let line_begin_it = undefined;
		let begin_it = undefined;
		let line_end_it = undefined;
		let end_it = undefined;
		if (line_list[this._line_select_it - 1].pre_height > line_list[this._line_cursor_it - 1].pre_height) {
			line_begin_it = this._line_cursor_it;
			begin_it = this._char_cursor_it;
			line_end_it = this._line_select_it;
			end_it = this._char_select_it;
		} else if (line_list[this._line_select_it - 1].pre_height < line_list[this._line_cursor_it - 1].pre_height) {
			line_begin_it = this._line_select_it;
			begin_it = this._char_select_it;
			line_end_it = this._line_cursor_it;
			end_it = this._char_cursor_it;
		} else {
			line_begin_it = this._line_select_it;
			line_end_it = this._line_cursor_it;
			begin_it = this._char_select_it;
			end_it = this._char_cursor_it;
			if (line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width > line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width) {
				begin_it = this._char_select_it;
				end_it = this._char_cursor_it;
			} else if (line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width < line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width) {
				begin_it = this._char_cursor_it;
				end_it = this._char_select_it;
			}
		}
		if (begin_it === 1) {
			if (line_begin_it !== 1 && line_list[line_begin_it - 1].force_line === false) {
				line_begin_it = line_begin_it - 1;
				begin_it = line_list[line_begin_it - 1].char_count + 1;
				begin_it = begin_it - 1;
			}
		}
		this.DeleteTextImpl(line_begin_it, begin_it, line_end_it, end_it);
		this.ResetCursor();
		return true;
	},
	CheckTextRegexLimit : function(text) {
		if (this._limit_len !== 0) {
			let text_len = ALittle.String_GetWordCount(text);
			if (text_len > this._limit_len) {
				return false;
			}
			let select_len = 0;
			let displaylist = this.GetSelectText();
			let ___OBJECT_9 = displaylist;
			for (let k = 1; k <= ___OBJECT_9.length; ++k) {
				let v = ___OBJECT_9[k - 1];
				if (v === undefined) break;
				if (v.__class === "Text") {
					select_len = select_len + ALittle.String_GetWordCount(v.text);
				}
			}
			displaylist = this.display_list;
			let total_len = 0;
			let ___OBJECT_10 = displaylist;
			for (let k = 1; k <= ___OBJECT_10.length; ++k) {
				let v = ___OBJECT_10[k - 1];
				if (v === undefined) break;
				if (v.__class === "Text") {
					total_len = total_len + ALittle.String_GetWordCount(v.text);
				}
			}
			if (total_len - select_len + text_len > this._limit_len) {
				return false;
			}
		}
		if (this._regex !== "") {
			while (text !== "") {
				let byte_count = ALittle.String_GetByteCount(text, 1);
				let sub_text = __sub(text, 1, byte_count);
				let start_it = __find(sub_text, this._regex);
				if (start_it === undefined) {
					return false;
				}
				text = __sub(text, byte_count + 1);
			}
		}
		return true;
	},
	InsertTextNative : function(text) {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return false;
		}
		if (this.CheckTextRegexLimit(text) === false) {
			return false;
		}
		this.DeleteSelectText();
		let char_info_list = [];
		let char_info_list_count = 0;
		let new_char_info = {};
		new_char_info.acc_width = 0;
		new_char_info.pre_width = 0;
		new_char_info.text_info = this.InitTextInfo();
		new_char_info.text_object = undefined;
		new_char_info.text = text;
		new_char_info.ctrl_info = undefined;
		new_char_info.ctrl = undefined;
		++ char_info_list_count;
		char_info_list[char_info_list_count - 1] = new_char_info;
		this.InsertTextImpl(char_info_list, false);
		this.ResetCursorLine();
		this.ResetCursor();
		return true;
	},
	CheckDisplayListRegexLimit : function(display_list) {
		if (this._regex === "") {
			return false;
		}
		let text = "";
		let ___OBJECT_11 = display_list;
		for (let k = 1; k <= ___OBJECT_11.length; ++k) {
			let v = ___OBJECT_11[k - 1];
			if (v === undefined) break;
			if (v.__class !== "Text") {
				return false;
			}
			text = text + v.text;
		}
		return this.CheckTextRegexLimit(text);
	},
	InsertDisplayListNative : function(display_list, selected) {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return false;
		}
		if (this.CheckDisplayListRegexLimit(display_list) === false) {
			return false;
		}
		this.DeleteSelectText();
		let line_list = this._line_list;
		let char_info = line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1];
		let char_info_list = this.DisplayListToCharInfoList(display_list, char_info.text_info);
		this.InsertTextImpl(char_info_list, selected);
		this.UpdateFontText();
		this.ResetCursorLine();
		this.ResetCursor();
		return true;
	},
	DeleteText : function(left) {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return false;
		}
		if (this.DeleteSelectText()) {
			return true;
		}
		let line_list = this._line_list;
		if (left) {
			if (this._line_cursor_it === 1 && this._char_cursor_it === 1) {
				return false;
			}
			let line_begin_it = this._line_cursor_it;
			let begin_it = this._char_cursor_it;
			let line_end_it = this._line_cursor_it;
			let end_it = this._char_cursor_it;
			if (begin_it === 1) {
				if (line_begin_it !== 1) {
					line_begin_it = line_begin_it - 1;
					begin_it = line_list[line_begin_it - 1].char_count + 1;
					begin_it = begin_it - 1;
				}
			} else {
				begin_it = begin_it - 1;
				if (begin_it === 1 && line_list[line_begin_it - 1].force_line === false) {
					if (line_begin_it !== 1) {
						line_begin_it = line_begin_it - 1;
						begin_it = line_list[line_begin_it - 1].char_count + 1;
						begin_it = begin_it - 1;
					}
				}
			}
			this.DeleteTextImpl(line_begin_it, begin_it, line_end_it, end_it);
		} else {
			let end_line = this._line_count + 1;
			end_line = end_line - 1;
			let end_char = line_list[end_line - 1].char_count + 1;
			end_char = end_char - 1;
			if (this._line_cursor_it === end_line && this._char_cursor_it === end_char) {
				return false;
			}
			let line_begin_it = this._line_cursor_it;
			let begin_it = this._char_cursor_it;
			let line_end_it = this._line_cursor_it;
			let end_it = this._char_cursor_it;
			end_char = line_list[line_end_it - 1].char_count + 1;
			end_char = end_char - 1;
			if (end_it === end_char) {
				if (line_end_it !== end_line) {
					line_end_it = line_end_it + 1;
					end_it = 1;
					if (line_list[line_end_it - 1].force_line === false) {
						end_it = end_it + 1;
						if (end_it > line_list[line_end_it - 1].char_count) {
							end_it = end_it - 1;
						}
					}
				}
			} else {
				end_it = end_it + 1;
			}
			this.DeleteTextImpl(line_begin_it, begin_it, line_end_it, end_it);
		}
		this.ResetCursorLine();
		this.ResetCursor();
		return true;
	},
	ClearText : function() {
		this._line_list = [];
		this._line_count = 0;
		let line_info = {};
		line_info.char_list = [];
		line_info.child_list = [];
		line_info.char_count = 0;
		line_info.child_count = 0;
		line_info.pre_height = 0;
		line_info.acc_height = 0;
		line_info.force_line = false;
		line_info.container = undefined;
		++ this._line_count;
		this._line_list[this._line_count - 1] = line_info;
		let char_info = {};
		char_info.acc_width = 0;
		char_info.pre_width = 0;
		char_info.text_info = this.InitTextInfo();
		char_info.text_object = undefined;
		char_info.text = "";
		char_info.ctrl_info = undefined;
		char_info.ctrl = undefined;
		++ line_info.char_count;
		line_info.char_list[line_info.char_count - 1] = char_info;
		this._line_start_it = 1;
		this._start_it_delta = 0;
		this._line_cursor_it = 1;
		this._char_cursor_it = 1;
		this._line_select_it = 1;
		this._char_select_it = 2;
		this.Draw();
	},
	SetStartIt : function(line_index) {
		if (line_index < 1 || line_index > this._line_count) {
			return;
		}
		this._line_start_it = line_index;
		this._start_it_delta = 0;
		this.RejustContentY();
	},
	ResetCursor : function() {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return;
		}
		let line_list = this._line_list;
		if ((this._char_select_it > line_list[this._line_select_it - 1].char_count) || (this._line_select_it === this._line_cursor_it && this._char_select_it === this._char_cursor_it)) {
			this._select_1.visible = false;
			this._select_2.visible = false;
			this._select_3.visible = false;
			this._start_cursor.visible = false;
			this._end_cursor.visible = false;
			this._start_cursor_data = undefined;
			this._end_cursor_data = undefined;
			this._event_start_x = 0;
			this._event_end_x = 0;
			this._event_start_y = 0;
			this._event_end_y = 0;
			if (this._focus_cursor) {
				this._cursor.visible = this._is_focus;
			} else {
				this._cursor.visible = true;
			}
			let cursor_width = 0.0;
			let line = line_list[this._line_cursor_it - 1];
			let char = line.char_list[this._char_cursor_it - 1];
			if (char.ctrl !== undefined) {
				this._cursor.height = char.ctrl.height;
				cursor_width = 2;
			} else {
				if (char.text_object !== undefined) {
					this._cursor.height = char.text_object.height;
					cursor_width = this.GetCursorWidth(char.text_object.font_size);
				} else {
					let next_char = line.char_list[this._char_cursor_it + 1 - 1];
					if (next_char !== undefined) {
						if (next_char.ctrl !== undefined) {
							this._cursor.height = next_char.ctrl.height;
							cursor_width = 2;
						} else if (next_char.text_object !== undefined) {
							this._cursor.height = next_char.text_object.height;
							cursor_width = this.GetCursorWidth(next_char.text_object.font_size);
						} else {
							this._cursor.height = this._font_text.native_show.GetFontHeight();
							cursor_width = this.GetCursorWidth(this._font_text.font_size);
						}
					} else {
						this._cursor.height = this._font_text.native_show.GetFontHeight();
						cursor_width = this.GetCursorWidth(this._font_text.font_size);
					}
				}
			}
			this._cursor.width = cursor_width;
			let line_height = line_list[this._line_cursor_it - 1].acc_height - line_list[this._line_cursor_it - 1].pre_height;
			let offset_y = line_height - this._cursor.height;
			if (offset_y <= 0) {
				offset_y = 0;
			}
			this._cursor.y = this._scroll_list.y + line_list[this._line_cursor_it - 1].pre_height - line_list[this._line_start_it - 1].pre_height + offset_y - this._start_it_delta;
			this._cursor.x = this._scroll_list.x + line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width;
			return;
		}
		if (this._multi_cursor === false) {
			this._cursor.visible = false;
		}
		if (line_list[this._line_select_it - 1].pre_height > line_list[this._line_cursor_it - 1].pre_height) {
			let line_it = this._line_cursor_it;
			this._select_1.visible = true;
			let select_1_y = line_list[this._line_cursor_it - 1].pre_height - line_list[this._line_start_it - 1].pre_height - this._start_it_delta;
			let select_1_height = line_list[this._line_cursor_it - 1].acc_height - line_list[this._line_cursor_it - 1].pre_height;
			if (select_1_y < 0) {
				select_1_height = select_1_y + select_1_height;
				select_1_y = 0;
			}
			if (select_1_y + select_1_height > this._scroll_list.height) {
				select_1_height = this._scroll_list.height - select_1_y;
			}
			if (select_1_height <= 0) {
				this._select_1.visible = false;
			}
			this._select_1.y = this._scroll_list.y + select_1_y;
			this._select_1.x = this._scroll_list.x + line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width;
			this._select_1.height = select_1_height;
			this._select_1.width = this._scroll_list.width - line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width;
			this._select_3.visible = (line_list[this._line_cursor_it - 1].acc_height !== line_list[this._line_select_it - 1].pre_height);
			let select_3_y = line_list[this._line_cursor_it - 1].acc_height - line_list[this._line_start_it - 1].pre_height - this._start_it_delta;
			let select_3_height = line_list[this._line_select_it - 1].pre_height - line_list[this._line_cursor_it - 1].acc_height;
			if (select_3_y < 0) {
				select_3_height = select_3_y + select_3_height;
				select_3_y = 0;
			}
			if (select_3_y + select_3_height > this._scroll_list.height) {
				select_3_height = this._scroll_list.height - select_3_y;
			}
			if (select_3_height <= 0) {
				this._select_3.visible = false;
			}
			this._select_3.y = this._scroll_list.y + select_3_y;
			this._select_3.x = this._scroll_list.x;
			this._select_3.height = select_3_height;
			this._select_3.width = this._scroll_list.width;
			line_it = this._line_select_it;
			this._select_2.visible = true;
			let select_2_y = line_list[this._line_select_it - 1].pre_height - line_list[this._line_start_it - 1].pre_height - this._start_it_delta;
			let select_2_height = line_list[this._line_select_it - 1].acc_height - line_list[this._line_select_it - 1].pre_height;
			if (select_2_y < 0) {
				select_2_height = select_2_y + select_2_height;
				select_2_y = 0;
			}
			if (select_2_y + select_2_height > this._scroll_list.height) {
				select_2_height = this._scroll_list.height - select_2_y;
			}
			if (select_2_height <= 0) {
				this._select_2.visible = false;
			}
			this._select_2.y = this._scroll_list.y + select_2_y;
			this._select_2.x = this._scroll_list.x;
			this._select_2.height = select_2_height;
			this._select_2.width = line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width;
			if (this._multi_cursor === true) {
				this._cursor.visible = false;
				this._start_cursor.x = this._select_1.x - this._start_cursor.width;
				this._start_cursor.height = this._select_1.height + this._cursor_margin_up + this._cursor_margin_down;
				this._start_cursor.y = this._select_1.y - this._cursor_margin_up;
				this._end_cursor.x = this._select_2.x + this._select_2.width;
				this._end_cursor.height = this._select_2.height + this._cursor_margin_up + this._cursor_margin_down;
				this._end_cursor.y = this._select_2.y - this._cursor_margin_up;
				this._start_cursor.visible = this._select_1.visible;
				this._end_cursor.visible = this._select_2.visible;
				this._start_cursor_data = "cursor";
				this._end_cursor_data = "select";
				this._event_start_x = this._select_1.x;
				this._event_start_y = this._select_1.y;
				this._event_end_x = this._select_2.x + this._select_2.width;
				this._event_end_y = this._select_2.y + this._select_2.height;
			}
		} else if (line_list[this._line_select_it - 1].pre_height < line_list[this._line_cursor_it - 1].pre_height) {
			let line_it = this._line_select_it;
			this._select_1.visible = true;
			let select_1_y = line_list[this._line_select_it - 1].pre_height - line_list[this._line_start_it - 1].pre_height - this._start_it_delta;
			let select_1_height = line_list[this._line_select_it - 1].acc_height - line_list[this._line_select_it - 1].pre_height;
			if (select_1_y < 0) {
				select_1_height = select_1_y + select_1_height;
				select_1_y = 0;
			}
			if (select_1_y + select_1_height > this._scroll_list.height) {
				select_1_height = this._scroll_list.height - select_1_y;
			}
			if (select_1_height <= 0) {
				this._select_1.visible = false;
			}
			this._select_1.y = this._scroll_list.y + select_1_y;
			this._select_1.x = this._scroll_list.x + line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width;
			this._select_1.height = select_1_height;
			this._select_1.width = this._scroll_list.width - line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width;
			line_it = this._line_cursor_it;
			this._select_2.visible = true;
			let select_2_y = line_list[this._line_cursor_it - 1].pre_height - line_list[this._line_start_it - 1].pre_height - this._start_it_delta;
			let select_2_height = line_list[this._line_cursor_it - 1].acc_height - line_list[this._line_cursor_it - 1].pre_height;
			if (select_2_y < 0) {
				select_2_height = select_2_y + select_2_height;
				select_2_y = 0;
			}
			if (select_2_y + select_2_height > this._scroll_list.height) {
				select_2_height = this._scroll_list.height - select_2_y;
			}
			if (select_2_height <= 0) {
				this._select_2.visible = false;
			}
			this._select_2.y = this._scroll_list.y + select_2_y;
			this._select_2.x = this._scroll_list.x;
			this._select_2.height = select_2_height;
			this._select_2.width = line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width;
			this._select_3.visible = (line_list[this._line_select_it - 1].acc_height !== line_list[this._line_cursor_it - 1].pre_height);
			let select_3_y = line_list[this._line_select_it - 1].acc_height - line_list[this._line_start_it - 1].pre_height - this._start_it_delta;
			let select_3_height = line_list[this._line_cursor_it - 1].pre_height - line_list[this._line_select_it - 1].acc_height;
			if (select_3_y < 0) {
				select_3_height = select_3_y + select_3_height;
				select_3_y = 0;
			}
			if (select_3_y + select_3_height > this._scroll_list.height) {
				select_3_height = this._scroll_list.height - select_3_y;
			}
			if (select_3_height <= 0) {
				this._select_3.visible = false;
			}
			this._select_3.y = this._scroll_list.y + select_3_y;
			this._select_3.x = this._scroll_list.x;
			this._select_3.width = this._scroll_list.width;
			this._select_3.height = select_3_height;
			if (this._multi_cursor === true) {
				this._cursor.visible = false;
				this._start_cursor.x = this._select_1.x - this._start_cursor.width;
				this._start_cursor.height = this._select_1.height + this._cursor_margin_up + this._cursor_margin_down;
				this._start_cursor.y = this._select_1.y - this._cursor_margin_up;
				this._end_cursor.x = this._select_2.x + this._select_2.width;
				this._end_cursor.height = this._select_2.height + this._cursor_margin_up + this._cursor_margin_down;
				this._end_cursor.y = this._select_2.y - this._cursor_margin_up;
				this._start_cursor.visible = this._select_1.visible;
				this._end_cursor.visible = this._select_2.visible;
				this._start_cursor_data = "select";
				this._end_cursor_data = "cursor";
				this._event_start_x = this._select_1.x;
				this._event_start_y = this._select_1.y;
				this._event_end_x = this._select_2.x + this._select_2.width;
				this._event_end_y = this._select_2.y + this._select_2.height;
			}
		} else {
			this._select_1.visible = false;
			this._select_2.visible = false;
			this._select_3.visible = false;
			if (line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width > line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width) {
				this._select_1.visible = true;
				let select_1_y = line_list[this._line_cursor_it - 1].pre_height - line_list[this._line_start_it - 1].pre_height - this._start_it_delta;
				let select_1_height = line_list[this._line_cursor_it - 1].acc_height - line_list[this._line_cursor_it - 1].pre_height;
				if (select_1_y < 0) {
					select_1_height = select_1_y + select_1_height;
					select_1_y = 0;
				}
				if (select_1_y + select_1_height > this._scroll_list.height) {
					select_1_height = this._scroll_list.height - select_1_y;
				}
				if (select_1_height <= 0) {
					this._select_1.visible = false;
				}
				this._select_1.x = this._scroll_list.x + line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width;
				this._select_1.y = this._scroll_list.y + select_1_y;
				this._select_1.height = select_1_height;
				this._select_1.width = line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width - line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width;
				if (this._multi_cursor === true) {
					this._cursor.visible = false;
					this._start_cursor.x = this._select_1.x - this._start_cursor.width;
					this._start_cursor.height = this._select_1.height + this._cursor_margin_up + this._cursor_margin_down;
					this._start_cursor.y = this._select_1.y - this._cursor_margin_up;
					this._end_cursor.x = this._select_1.x + this._select_1.width;
					this._end_cursor.height = this._start_cursor.height;
					this._end_cursor.y = this._start_cursor.y;
					this._start_cursor.visible = this._select_1.visible;
					this._end_cursor.visible = this._select_1.visible;
					this._start_cursor_data = "select";
					this._end_cursor_data = "cursor";
					this._event_start_x = this._select_1.x;
					this._event_start_y = this._select_1.y;
					this._event_end_x = this._select_1.x + this._select_1.width;
					this._event_end_y = this._select_1.y + this._select_1.height;
				}
			} else if (line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width < line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width) {
				this._select_1.visible = true;
				let select_1_y = line_list[this._line_cursor_it - 1].pre_height - line_list[this._line_start_it - 1].pre_height - this._start_it_delta;
				let select_1_height = line_list[this._line_cursor_it - 1].acc_height - line_list[this._line_cursor_it - 1].pre_height;
				if (select_1_y < 0) {
					select_1_height = select_1_y + select_1_height;
					select_1_y = 0;
				}
				if (select_1_y + select_1_height > this._scroll_list.height) {
					select_1_height = this._scroll_list.height - select_1_y;
				}
				if (select_1_height <= 0) {
					this._select_1.visible = false;
				}
				this._select_1.x = this._scroll_list.x + line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width;
				this._select_1.y = this._scroll_list.y + select_1_y;
				this._select_1.height = select_1_height;
				this._select_1.width = line_list[this._line_select_it - 1].char_list[this._char_select_it - 1].acc_width - line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width;
				if (this._multi_cursor === true) {
					this._cursor.visible = false;
					this._start_cursor.x = this._select_1.x - this._start_cursor.width;
					this._start_cursor.height = this._select_1.height + this._cursor_margin_up + this._cursor_margin_down;
					this._start_cursor.y = this._select_1.y - this._cursor_margin_up;
					this._end_cursor.x = this._select_1.x + this._select_1.width;
					this._end_cursor.height = this._start_cursor.height;
					this._end_cursor.y = this._start_cursor.y;
					this._start_cursor.visible = this._select_1.visible;
					this._end_cursor.visible = this._select_1.visible;
					this._start_cursor_data = "cursor";
					this._end_cursor_data = "select";
					this._event_start_x = this._select_1.x;
					this._event_start_y = this._select_1.y;
					this._event_end_x = this._select_1.x + this._select_1.width;
					this._event_end_y = this._select_1.y + this._select_1.height;
				}
			}
		}
	},
	DeleteTextImpl : function(line_begin_it, begin_it, line_end_it, end_it) {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return;
		}
		let line_list = this._line_list;
		let line_delete_begin = line_begin_it;
		let line_delete_end = line_end_it;
		let char_delete_begin = begin_it;
		let char_delete_end = end_it;
		if (line_list[line_begin_it - 1].pre_height > line_list[line_end_it - 1].pre_height) {
			line_delete_begin = line_end_it;
			char_delete_begin = end_it;
			line_delete_end = line_begin_it;
			char_delete_end = begin_it;
		} else if (line_list[line_begin_it - 1].pre_height === line_list[line_end_it - 1].pre_height) {
			if (line_list[line_begin_it - 1].char_list[begin_it - 1].acc_width > line_list[line_end_it - 1].char_list[end_it - 1].acc_width) {
				char_delete_begin = end_it;
				char_delete_end = begin_it;
			}
		}
		if (line_list[this._line_start_it - 1].pre_height >= line_list[line_delete_begin - 1].pre_height) {
			this._line_start_it = line_delete_begin;
			this._start_it_delta = 0;
		}
		let calc_text_1 = [];
		let calc_text_1_count = 0;
		let char_it = 1;
		char_it = char_it + 1;
		char_delete_begin = char_delete_begin + 1;
		let line = line_list[line_delete_begin - 1];
		while (char_it !== char_delete_begin) {
			++ calc_text_1_count;
			calc_text_1[calc_text_1_count - 1] = line.char_list[char_it - 1];
			char_it = char_it + 1;
		}
		let calc_text_2 = [];
		let calc_text_2_count = 0;
		char_it = char_delete_end;
		char_it = char_it + 1;
		line = line_list[line_delete_end - 1];
		while (char_it <= line.char_count) {
			++ calc_text_2_count;
			calc_text_2[calc_text_2_count - 1] = line.char_list[char_it - 1];
			char_it = char_it + 1;
		}
		let line_it = line_delete_end;
		line_it = line_it + 1;
		let free_line_it = 0;
		while (line_it <= this._line_count) {
			char_it = 1;
			line = line_list[line_it - 1];
			if (line.force_line) {
				free_line_it = line_it;
				break;
			}
			while (char_it <= line.char_count) {
				++ calc_text_2_count;
				calc_text_2[calc_text_2_count - 1] = line.char_list[char_it - 1];
				char_it = char_it + 1;
			}
			line_it = line_it + 1;
		}
		let char_info = line_list[line_delete_begin - 1].char_list[1 - 1];
		line_list[line_delete_begin - 1].char_list = [];
		line_list[line_delete_begin - 1].char_count = 1;
		line_list[line_delete_begin - 1].char_list[1 - 1] = char_info;
		line_list[line_delete_begin - 1].child_list = [];
		line_list[line_delete_begin - 1].child_count = 0;
		line_list[line_delete_begin - 1].acc_height = line_list[line_delete_begin - 1].pre_height;
		line_list[line_delete_begin - 1].container = undefined;
		let free_line_list = undefined;
		let free_line_list_count = 0;
		if (free_line_it > 0) {
			free_line_list = [];
			for (let i = free_line_it; i <= this._line_count; i += 1) {
				++ free_line_list_count;
				free_line_list[free_line_list_count - 1] = line_list[i - 1];
			}
		}
		line_it = line_delete_begin;
		line_it = line_it + 1;
		for (let i = line_it; i <= this._line_count; i += 1) {
			line_list[i - 1] = undefined;
		}
		this._line_count = line_delete_begin;
		calc_text_1 = this.JoinCharInfoList(calc_text_1);
		calc_text_2 = this.JoinCharInfoList(calc_text_2);
		[this._line_cursor_it, this._char_cursor_it] = this.InsertTextUtil(calc_text_1);
		this.InsertTextUtil(calc_text_2);
		if (free_line_list !== undefined) {
			let last_line = line_list[this._line_count - 1];
			if (last_line.char_count === 1 && last_line.force_line) {
				last_line.acc_height = last_line.pre_height + this._enter_key_height;
			}
			let start_y = last_line.acc_height;
			let ___OBJECT_12 = free_line_list;
			for (let k = 1; k <= ___OBJECT_12.length; ++k) {
				let line_v = ___OBJECT_12[k - 1];
				if (line_v === undefined) break;
				this._line_count = this._line_count + 1;
				line_list[this._line_count - 1] = line_v;
				let line_height = line_v.acc_height - line_v.pre_height;
				line_v.pre_height = start_y;
				start_y = start_y + line_height;
				line_v.acc_height = start_y;
			}
		}
		this._line_select_it = this._line_count + 1;
		this._line_select_it = this._line_select_it - 1;
		this._char_select_it = line_list[this._line_select_it - 1].char_count + 1;
		this.Draw();
	},
	InsertTextImpl : function(char_info_list, selected) {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return;
		}
		if (char_info_list[1 - 1] === undefined) {
			return;
		}
		let line_list = this._line_list;
		let line_cursor_it_tmp = this._line_cursor_it;
		let char_cursor_it_tmp = this._char_cursor_it;
		let calc_text_1 = [];
		let calc_text_1_count = 0;
		let char_it = 1;
		char_it = char_it + 1;
		let char_end_it = this._char_cursor_it;
		char_end_it = char_end_it + 1;
		let line = line_list[this._line_cursor_it - 1];
		while (char_it !== char_end_it) {
			++ calc_text_1_count;
			calc_text_1[calc_text_1_count - 1] = line.char_list[char_it - 1];
			char_it = char_it + 1;
		}
		let ___OBJECT_13 = char_info_list;
		for (let k = 1; k <= ___OBJECT_13.length; ++k) {
			let v = ___OBJECT_13[k - 1];
			if (v === undefined) break;
			++ calc_text_1_count;
			calc_text_1[calc_text_1_count - 1] = v;
		}
		let calc_text_2 = [];
		let calc_text_2_count = 0;
		char_it = this._char_cursor_it;
		char_it = char_it + 1;
		line = line_list[this._line_cursor_it - 1];
		while (char_it <= line.char_count) {
			++ calc_text_2_count;
			calc_text_2[calc_text_2_count - 1] = line.char_list[char_it - 1];
			char_it = char_it + 1;
		}
		let line_it = this._line_cursor_it;
		line_it = line_it + 1;
		let free_line_it = 0;
		while (line_it <= this._line_count) {
			char_it = 1;
			line = line_list[line_it - 1];
			if (line.force_line) {
				free_line_it = line_it;
				break;
			}
			while (char_it <= line.char_count) {
				++ calc_text_2_count;
				calc_text_2[calc_text_2_count - 1] = line.char_list[char_it - 1];
				char_it = char_it + 1;
			}
			line_it = line_it + 1;
		}
		let char_info = line_list[this._line_cursor_it - 1].char_list[1 - 1];
		line_list[this._line_cursor_it - 1].char_list = [];
		line_list[this._line_cursor_it - 1].char_count = 1;
		line_list[this._line_cursor_it - 1].char_list[1 - 1] = char_info;
		line_list[this._line_cursor_it - 1].child_list = [];
		line_list[this._line_cursor_it - 1].child_count = 0;
		line_list[this._line_cursor_it - 1].acc_height = line_list[this._line_cursor_it - 1].pre_height;
		line_list[this._line_cursor_it - 1].container = undefined;
		let free_line_list = undefined;
		let free_line_list_count = 0;
		if (free_line_it > 0) {
			free_line_list = [];
			for (let i = free_line_it; i <= this._line_count; i += 1) {
				++ free_line_list_count;
				free_line_list[free_line_list_count - 1] = line_list[i - 1];
			}
		}
		line_it = this._line_cursor_it;
		line_it = line_it + 1;
		for (let i = line_it; i <= this._line_count; i += 1) {
			line_list[i - 1] = undefined;
		}
		this._line_count = this._line_cursor_it;
		calc_text_1 = this.JoinCharInfoList(calc_text_1);
		calc_text_2 = this.JoinCharInfoList(calc_text_2);
		[this._line_cursor_it, this._char_cursor_it] = this.InsertTextUtil(calc_text_1);
		this.InsertTextUtil(calc_text_2);
		if (free_line_list !== undefined) {
			let last_line = line_list[this._line_count - 1];
			if (last_line.char_count === 1 && last_line.force_line) {
				last_line.acc_height = last_line.pre_height + this._enter_key_height;
			}
			let start_y = last_line.acc_height;
			let ___OBJECT_14 = free_line_list;
			for (let k1 = 1; k1 <= ___OBJECT_14.length; ++k1) {
				let line_v = ___OBJECT_14[k1 - 1];
				if (line_v === undefined) break;
				this._line_count = this._line_count + 1;
				line_list[this._line_count - 1] = line_v;
				let line_height = line_v.acc_height - line_v.pre_height;
				line_v.pre_height = start_y;
				start_y = start_y + line_height;
				line_v.acc_height = start_y;
			}
		}
		if (selected) {
			this._line_select_it = line_cursor_it_tmp;
			this._char_select_it = char_cursor_it_tmp;
		} else {
			this._line_select_it = this._line_count + 1;
			this._line_select_it = this._line_select_it - 1;
			this._char_select_it = line_list[this._line_select_it - 1].char_count + 1;
		}
		this.Draw();
	},
	InsertTextUtil : function(char_info_list) {
		let line_list = this._line_list;
		let total_width = this._scroll_list.width;
		let new_char_info_list = [];
		let new_char_info_list_count = 0;
		let ___OBJECT_15 = char_info_list;
		for (let index = 1; index <= ___OBJECT_15.length; ++index) {
			let char_info = ___OBJECT_15[index - 1];
			if (char_info === undefined) break;
			if (char_info.ctrl_info === undefined) {
				new_char_info_list_count = this.SplitText(char_info, new_char_info_list, new_char_info_list_count);
			} else {
				++ new_char_info_list_count;
				new_char_info_list[new_char_info_list_count - 1] = char_info;
			}
		}
		char_info_list = new_char_info_list;
		let line_it = this._line_count + 1;
		line_it = line_it - 1;
		let line_info = line_list[line_it - 1];
		let begin_it = line_info.char_count + 1;
		begin_it = begin_it - 1;
		if (line_it === 1 && begin_it === 1) {
			line_info.char_list[1 - 1].text_info = this.InitTextInfo();
		}
		let display_info = undefined;
		let display_object = undefined;
		let display_index = 1;
		let remain_width = total_width - line_info.char_list[line_info.char_count - 1].acc_width;
		while (true) {
			if (display_info === undefined) {
				display_info = char_info_list[display_index - 1];
				if (display_info === undefined) {
					break;
				}
			}
			if (display_info.ctrl_info === undefined) {
				if (display_info.text === "\n") {
					if (line_info.char_count === 1) {
						line_info.acc_height = line_info.pre_height + this._enter_key_height;
					}
					let new_line_info = {};
					new_line_info.char_list = [];
					new_line_info.child_list = [];
					new_line_info.char_count = 0;
					new_line_info.child_count = 0;
					new_line_info.pre_height = line_info.acc_height + this._line_spacing;
					new_line_info.acc_height = line_info.acc_height;
					new_line_info.force_line = true;
					new_line_info.container = undefined;
					this._line_count = this._line_count + 1;
					line_list[this._line_count - 1] = new_line_info;
					let char_info = {};
					char_info.acc_width = 0;
					char_info.pre_width = 0;
					char_info.text_info = display_info.text_info;
					char_info.text_object = undefined;
					char_info.text = "\n";
					char_info.ctrl_info = undefined;
					char_info.ctrl = undefined;
					new_line_info.char_count = new_line_info.char_count + 1;
					new_line_info.char_list[new_line_info.char_count - 1] = char_info;
					line_info = new_line_info;
					display_info = undefined;
					display_object = undefined;
					display_index = display_index + 1;
					remain_width = total_width;
				} else if (display_info.text === "\t") {
					if (display_object === undefined) {
						let name = "nkacbjbsakcvuqocbakcbjcbvjhciqwojqppwvnwe";
						this._ctrl_sys.RegisterInfo(name, ALittle.String_CopyTable(display_info.text_info));
						display_object = this._ctrl_sys.CreateControl(name, this._link_map);
						this._ctrl_sys.UnRegisterInfo(name);
						display_object.text = "    ";
					}
					let object_width = display_object.width;
					let object_height = display_object.height;
					this.SetDrawText(display_object);
					let calc_text = "\t";
					while (calc_text !== "") {
						let byte_count = ALittle.String_GetByteCount(calc_text, 1);
						let sub_text = __sub(calc_text, 1, byte_count);
						let text_width = this._draw_text.native_show.CalcTextWidth("    ");
						let char_info = {};
						char_info.pre_width = line_info.char_list[line_info.char_count - 1].acc_width;
						char_info.acc_width = char_info.pre_width + text_width;
						char_info.text_info = display_info.text_info;
						char_info.text_object = display_object;
						char_info.text = sub_text;
						char_info.ctrl_info = undefined;
						char_info.ctrl = undefined;
						line_info.char_count = line_info.char_count + 1;
						line_info.char_list[line_info.char_count - 1] = char_info;
						calc_text = __sub(calc_text, byte_count + 1);
					}
					++ line_info.child_count;
					line_info.child_list[line_info.child_count - 1] = display_object;
					if (line_info.acc_height - line_info.pre_height < object_height) {
						line_info.acc_height = line_info.pre_height + object_height;
					}
					remain_width = remain_width - object_width;
					if (remain_width <= 0) {
						let new_line_info = {};
						new_line_info.char_list = [];
						new_line_info.child_list = [];
						new_line_info.char_count = 0;
						new_line_info.child_count = 0;
						new_line_info.pre_height = line_info.acc_height + this._line_spacing;
						new_line_info.acc_height = line_info.acc_height;
						new_line_info.force_line = false;
						new_line_info.container = undefined;
						this._line_count = this._line_count + 1;
						line_list[this._line_count - 1] = new_line_info;
						let char_info = {};
						char_info.acc_width = 0;
						char_info.pre_width = 0;
						char_info.text_info = display_info.text_info;
						char_info.text_object = undefined;
						char_info.text = "";
						char_info.ctrl_info = undefined;
						char_info.ctrl = undefined;
						new_line_info.char_count = new_line_info.char_count + 1;
						new_line_info.char_list[new_line_info.char_count - 1] = char_info;
						line_info = new_line_info;
						remain_width = total_width;
					}
					display_object = undefined;
					display_info = undefined;
					display_index = display_index + 1;
				} else {
					while (true) {
						if (display_info.text === "") {
							display_info = undefined;
							display_index = display_index + 1;
							break;
						}
						if (display_object === undefined) {
							let name = "nkacbjbsakcvuqocbakcbjcbvjhciqwojqppwvnwe";
							this._ctrl_sys.RegisterInfo(name, ALittle.String_CopyTable(display_info.text_info));
							display_object = this._ctrl_sys.CreateControl(name, this._link_map);
							this._ctrl_sys.UnRegisterInfo(name);
						}
						let count = display_object._show.CutTextByWidth(__floor(remain_width), display_info.text, __floor(total_width));
						if (count === 0 && line_info.char_count <= 1) {
							count = ALittle.String_GetByteCount(display_info.text, 1);
						}
						if (count === 0) {
							remain_width = 0;
						} else {
							let calc_text = __sub(display_info.text, 1, count);
							display_object.text = calc_text;
							let object_width = display_object.width;
							let object_height = display_object.height;
							this.SetDrawText(display_object);
							let char_count = display_object._show.GetCutWidthListCount();
							for (let i = 1; i <= char_count; i += 1) {
								let byte_count = ALittle.String_GetByteCount(calc_text, 1);
								let sub_text = __sub(calc_text, 1, byte_count);
								let text_width = display_object._show.GetCutWidthByIndex(i - 1);
								let char_info = {};
								char_info.pre_width = line_info.char_list[line_info.char_count - 1].acc_width;
								char_info.acc_width = text_width;
								char_info.text_info = display_info.text_info;
								char_info.text_object = display_object;
								char_info.text = sub_text;
								char_info.ctrl_info = undefined;
								char_info.ctrl = undefined;
								line_info.char_count = line_info.char_count + 1;
								line_info.char_list[line_info.char_count - 1] = char_info;
								calc_text = __sub(calc_text, byte_count + 1);
							}
							remain_width = remain_width - object_width;
							display_object._show.ClearCutWidthCache();
							let new_display_info = ALittle.String_CopyTable(display_info);
							new_display_info.text = __sub(display_info.text, count + 1);
							++ line_info.child_count;
							line_info.child_list[line_info.child_count - 1] = display_object;
							if (line_info.acc_height - line_info.pre_height < object_height) {
								line_info.acc_height = line_info.pre_height + object_height;
							}
							display_info = new_display_info;
							display_object = undefined;
						}
						if (remain_width <= 0) {
							let new_line_info = {};
							new_line_info.char_list = [];
							new_line_info.child_list = [];
							new_line_info.char_count = 0;
							new_line_info.child_count = 0;
							new_line_info.pre_height = line_info.acc_height + this._line_spacing;
							new_line_info.acc_height = line_info.acc_height;
							new_line_info.force_line = false;
							new_line_info.container = undefined;
							this._line_count = this._line_count + 1;
							line_list[this._line_count - 1] = new_line_info;
							let char_info = {};
							char_info.acc_width = 0;
							char_info.pre_width = 0;
							char_info.text_info = display_info.text_info;
							char_info.text_object = undefined;
							char_info.text = "";
							char_info.ctrl_info = undefined;
							char_info.ctrl = undefined;
							new_line_info.char_count = new_line_info.char_count + 1;
							new_line_info.char_list[new_line_info.char_count - 1] = char_info;
							line_info = new_line_info;
							remain_width = total_width;
						}
					}
				}
			} else {
				if (display_object === undefined) {
					if (display_info.ctrl === undefined) {
						let name = "nkacbjbsakcvuqocbakcbjcbvjhciqwojqppwvnwe";
						this._ctrl_sys.RegisterInfo(name, ALittle.String_CopyTable(display_info.ctrl_info));
						display_object = this._ctrl_sys.CreateControl(name, this._link_map);
						this._ctrl_sys.UnRegisterInfo(name);
					} else {
						display_object = display_info.ctrl;
					}
				}
				let object_width = display_object.width;
				let object_height = display_object.height;
				if (remain_width >= object_width || (line_info.char_count === 1 && total_width <= object_width)) {
					let char_info = {};
					char_info.pre_width = line_info.char_list[line_info.char_count - 1].acc_width;
					char_info.acc_width = char_info.pre_width + display_object.width;
					char_info.text_info = line_info.char_list[line_info.char_count - 1].text_info;
					char_info.text_object = undefined;
					char_info.text = undefined;
					char_info.ctrl_info = display_info.ctrl_info;
					char_info.ctrl = display_object;
					line_info.char_count = line_info.char_count + 1;
					line_info.char_list[line_info.char_count - 1] = char_info;
					++ line_info.child_count;
					line_info.child_list[line_info.child_count - 1] = display_object;
					if (line_info.acc_height - line_info.pre_height < object_height) {
						line_info.acc_height = line_info.pre_height + object_height;
					}
					remain_width = remain_width - object_width;
					if (remain_width <= 0) {
						let new_line_info = {};
						new_line_info.char_list = [];
						new_line_info.child_list = [];
						new_line_info.char_count = 0;
						new_line_info.child_count = 0;
						new_line_info.pre_height = line_info.acc_height + this._line_spacing;
						new_line_info.acc_height = line_info.acc_height;
						new_line_info.force_line = false;
						new_line_info.container = undefined;
						this._line_count = this._line_count + 1;
						line_list[this._line_count - 1] = new_line_info;
						char_info = {};
						char_info.acc_width = 0;
						char_info.pre_width = 0;
						char_info.text_info = line_info.char_list[line_info.char_count - 1].text_info;
						char_info.text_object = undefined;
						char_info.text = "";
						char_info.ctrl_info = undefined;
						char_info.ctrl = undefined;
						new_line_info.char_count = new_line_info.char_count + 1;
						new_line_info.char_list[new_line_info.char_count - 1] = char_info;
						line_info = new_line_info;
						remain_width = total_width;
					}
					display_object = undefined;
					display_info = undefined;
					display_index = display_index + 1;
				} else {
					let new_line_info = {};
					new_line_info.char_list = [];
					new_line_info.child_list = [];
					new_line_info.char_count = 0;
					new_line_info.child_count = 0;
					new_line_info.pre_height = line_info.acc_height + this._line_spacing;
					new_line_info.acc_height = line_info.acc_height;
					new_line_info.force_line = false;
					new_line_info.container = undefined;
					this._line_count = this._line_count + 1;
					line_list[this._line_count - 1] = new_line_info;
					let char_info = {};
					char_info.acc_width = 0;
					char_info.pre_width = 0;
					char_info.text_info = line_info.char_list[line_info.char_count - 1].text_info;
					char_info.text_object = undefined;
					char_info.text = "";
					char_info.ctrl_info = undefined;
					char_info.ctrl = undefined;
					new_line_info.char_count = new_line_info.char_count + 1;
					new_line_info.char_list[new_line_info.char_count - 1] = char_info;
					line_info = new_line_info;
					remain_width = total_width;
				}
			}
		}
		if (line_info.char_count === 1) {
			line_info.acc_height = line_info.pre_height + this._enter_key_height;
		}
		let line_begin_it = this._line_count + 1;
		line_begin_it = line_begin_it - 1;
		begin_it = line_list[line_begin_it - 1].char_count + 1;
		begin_it = begin_it - 1;
		return [line_begin_it, begin_it];
	},
	DrawImpl : function() {
		this._scroll_list.RemoveAllChild();
		let ___OBJECT_16 = this._line_list;
		for (let line_index = 1; line_index <= ___OBJECT_16.length; ++line_index) {
			let line_info = ___OBJECT_16[line_index - 1];
			if (line_info === undefined) break;
			let displayout = line_info.container;
			if (displayout === undefined) {
				displayout = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
				line_info.container = displayout;
				displayout.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
				displayout.height = line_info.acc_height - line_info.pre_height;
				let offset_x = 0.0;
				let ___OBJECT_17 = line_info.child_list;
				for (let child_index = 1; child_index <= ___OBJECT_17.length; ++child_index) {
					let child = ___OBJECT_17[child_index - 1];
					if (child === undefined) break;
					child.x = offset_x;
					offset_x = offset_x + child.width;
					child.y = displayout.height - child.height;
					displayout.AddChild(child);
				}
			}
			this._scroll_list.AddChild(displayout);
		}
		let child = this._scroll_list.GetChildByIndex(this._line_start_it);
		this._scroll_list.scroll_offset = -child.y - this._start_it_delta;
		this._scroll_list.RefreshClipDisLine();
		this._scroll_list.RejustScrollBar();
		this._draw_loop = undefined;
	},
	RejustContentY : function() {
		if (this._draw_loop !== undefined) {
			return;
		}
		let child = this._scroll_list.GetChildByIndex(this._line_start_it);
		this._scroll_list.scroll_offset = -child.y - this._start_it_delta;
		this._scroll_list.RefreshClipDisLine();
		this._scroll_list.RejustScrollBar();
	},
	Draw : function() {
		if (this._draw_loop !== undefined) {
			return;
		}
		this._draw_loop = ALittle.NewObject(ALittle.LoopFunction, this.DrawImpl.bind(this), 1, 0, 1);
		A_LoopSystem.AddUpdater(this._draw_loop);
	},
	CursorOffsetLR : function(left) {
		let line_list = this._line_list;
		if (this._char_select_it <= line_list[this._line_select_it - 1].char_count) {
			this._char_select_it = line_list[this._line_select_it - 1].char_count + 1;
			this.ResetCursor();
			return;
		}
		this.CursorOffsetLRImpl(left);
	},
	CursorOffsetUD : function(up) {
		let line_list = this._line_list;
		if (this._char_select_it <= line_list[this._line_select_it - 1].char_count) {
			this._char_select_it = line_list[this._line_select_it - 1].char_count + 1;
			this.ResetCursor();
			return;
		}
		this.CursorOffsetUDImpl(up);
	},
	SelectCursorOffsetLR : function(left) {
		let line_list = this._line_list;
		if (this._char_select_it > line_list[this._line_select_it - 1].char_count) {
			this._line_select_it = this._line_cursor_it;
			this._char_select_it = this._char_cursor_it;
		}
		this.CursorOffsetLRImpl(left);
	},
	SelectCursorOffsetUD : function(up) {
		let line_list = this._line_list;
		if (this._char_select_it > line_list[this._line_select_it - 1].char_count) {
			this._line_select_it = this._line_cursor_it;
			this._char_select_it = this._char_cursor_it;
		}
		this.CursorOffsetUDImpl(up);
	},
	SetCursorToHome : function() {
		let line_list = this._line_list;
		this._char_select_it = line_list[this._line_select_it - 1].char_count + 1;
		this._char_cursor_it = 1;
		this.ResetCursor();
	},
	SetCursorToEnd : function() {
		let line_list = this._line_list;
		this._char_select_it = line_list[this._line_select_it - 1].char_count + 1;
		this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count + 1;
		this._char_cursor_it = this._char_cursor_it - 1;
		this.ResetCursor();
	},
	SelectAll : function() {
		let line_list = this._line_list;
		this._line_select_it = 1;
		this._char_select_it = 1;
		this._line_cursor_it = this._line_count + 1;
		this._line_cursor_it = this._line_cursor_it - 1;
		this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count + 1;
		this._char_cursor_it = this._char_cursor_it - 1;
		this.ResetCursorLine();
		this.ResetCursor();
	},
	ResetCursorLine : function() {
		let line_list = this._line_list;
		if (this._line_cursor_it === this._line_count) {
			if (line_list[this._line_cursor_it - 1].acc_height > this._scroll_list.height && this._scroll_list.scroll_offset < 0) {
				this._scroll_list.scroll_offset = this._scroll_list.height - line_list[this._line_cursor_it - 1].acc_height;
				this._scroll_list.RefreshClipDisLine();
				this._scroll_list.RejustScrollBar();
				while (line_list[this._line_start_it - 1].pre_height > -this._scroll_list.scroll_offset) {
					this._line_start_it = this._line_start_it - 1;
				}
				this._start_it_delta = -this._scroll_list.scroll_offset - line_list[this._line_start_it - 1].pre_height;
				return;
			}
			if (line_list[this._line_cursor_it - 1].acc_height <= this._scroll_list.height) {
				this._scroll_list.scroll_offset = 0;
				this._scroll_list.RefreshClipDisLine();
				this._scroll_list.RejustScrollBar();
				this._line_start_it = 1;
				this._start_it_delta = 0;
				return;
			}
		}
		if (line_list[this._line_cursor_it - 1].pre_height <= -this._scroll_list.scroll_offset) {
			this._scroll_list.scroll_offset = -line_list[this._line_cursor_it - 1].pre_height;
			this._scroll_list.RefreshClipDisLine();
			this._scroll_list.RejustScrollBar();
			this._line_start_it = this._line_cursor_it;
		} else if (line_list[this._line_cursor_it - 1].acc_height >= this._scroll_list.height - this._scroll_list.scroll_offset) {
			this._scroll_list.scroll_offset = this._scroll_list.height - line_list[this._line_cursor_it - 1].acc_height;
			this._scroll_list.RefreshClipDisLine();
			this._scroll_list.RejustScrollBar();
			while (line_list[this._line_start_it - 1].acc_height <= -this._scroll_list.scroll_offset) {
				this._line_start_it = this._line_start_it + 1;
			}
		}
		this._start_it_delta = -this._scroll_list.scroll_offset - line_list[this._line_start_it - 1].pre_height;
	},
	ClickCursor : function(offset_x, offset_y) {
		let line_list = this._line_list;
		this._char_select_it = line_list[this._line_select_it - 1].char_count + 1;
		[this._line_cursor_it, this._char_cursor_it] = this.GetIteratorByOffset(offset_x, offset_y);
		this.ResetCursorLine();
		this.UpdateFontText();
		this.ResetCursor();
	},
	ClickWordCursor : function(offset_x, offset_y) {
		let line_list = this._line_list;
		[this._line_cursor_it, this._char_cursor_it] = this.GetIteratorByOffset(offset_x, offset_y);
		this._char_select_it = this._char_cursor_it;
		this._line_select_it = this._line_cursor_it;
		while (true) {
			let has_find = false;
			while (true) {
				let str = line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].text;
				if (str !== undefined && __len(str) === 1 && str !== "_" && this.CharIsNumber(str) === false && this.CharIsLetter(str) === false) {
					has_find = true;
					break;
				}
				if (this._char_cursor_it === 1) {
					break;
				}
				this._char_cursor_it = this._char_cursor_it - 1;
			}
			if (has_find) {
				break;
			}
			if (this._line_cursor_it === 1) {
				break;
			}
			this._line_cursor_it = this._line_cursor_it - 1;
			this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count + 1;
			this._char_cursor_it = this._char_cursor_it - 1;
		}
		let cursor_tmp = this._char_select_it;
		let line_cursor_tmp = this._line_select_it;
		while (true) {
			cursor_tmp = cursor_tmp + 1;
			if (cursor_tmp > line_list[this._line_select_it - 1].char_count) {
				line_cursor_tmp = line_cursor_tmp + 1;
				if (line_cursor_tmp > this._line_count) {
					break;
				}
				cursor_tmp = 1;
			}
			let str = line_list[line_cursor_tmp - 1].char_list[cursor_tmp - 1].text;
			if (str !== undefined && __len(str) === 1 && str !== "_" && this.CharIsNumber(str) === false && this.CharIsLetter(str) === false) {
				break;
			}
			this._char_select_it = cursor_tmp;
			this._line_select_it = line_cursor_tmp;
		}
		if (this._line_select_it > this._line_count) {
			this._line_select_it = this._line_select_it - 1;
			this._char_select_it = line_list[this._line_select_it - 1].char_count + 1;
		}
		if (this._char_select_it > line_list[this._line_select_it - 1].char_count) {
			this._char_select_it = this._char_select_it - 1;
		}
		if (this._line_select_it === this._line_cursor_it && this._char_select_it === this._char_cursor_it) {
			this._char_select_it = line_list[this._line_select_it - 1].char_count + 1;
		}
		this.ResetCursorLine();
		this.UpdateFontText();
		this.ResetCursor();
		return this._char_select_it <= line_list[this._line_select_it - 1].char_count;
	},
	DragCursorBegin : function() {
		let line_list = this._line_list;
		this._line_select_it = this._line_cursor_it;
		this._char_select_it = this._char_cursor_it;
	},
	DragCursor : function(offset_x, offset_y) {
		let line_list = this._line_list;
		[this._line_cursor_it, this._char_cursor_it] = this.GetIteratorByOffset(offset_x, offset_y);
		if (line_list[this._line_cursor_it - 1].pre_height === -this._scroll_list.scroll_offset && this._line_cursor_it !== 1 && offset_y < 0) {
			this._line_cursor_it = this._line_cursor_it - 1;
			if (this._char_cursor_it > line_list[this._line_cursor_it - 1].char_count) {
				this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count;
			}
		}
		if (this._line_cursor_it === this._line_count && line_list[this._line_cursor_it - 1].pre_height === line_list[this._line_cursor_it - 1].acc_height && this._line_cursor_it !== 1) {
			this._line_cursor_it = this._line_cursor_it - 1;
			this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count;
		}
		this.ResetCursorLine();
		this.ResetCursor();
	},
	DragEdit : function(delta_y) {
		let event = {};
		event.target = this._scroll_list;
		event.delta_x = 0;
		event.delta_y = delta_y;
		this._scroll_list.HandleDrag(event);
		let line_list = this._line_list;
		if (line_list[this._line_start_it - 1].acc_height <= -this._scroll_list.scroll_offset) {
			this._line_start_it = this._line_start_it + 1;
			while (line_list[this._line_start_it - 1].acc_height <= -this._scroll_list.scroll_offset) {
				this._line_start_it = this._line_start_it + 1;
			}
		} else if (line_list[this._line_start_it - 1].pre_height > -this._scroll_list.scroll_offset) {
			this._line_start_it = this._line_start_it - 1;
			while (line_list[this._line_start_it - 1].pre_height > -this._scroll_list.scroll_offset) {
				this._line_start_it = this._line_start_it - 1;
			}
		}
		this._start_it_delta = -this._scroll_list.scroll_offset - line_list[this._line_start_it - 1].pre_height;
		this.ResetCursor();
	},
	CheckMultiCursor : function(offset_x, offset_y, trans) {
		let line_list = this._line_list;
		let line_cursor_it = undefined;
		let char_cursor_it = undefined;
		if (trans) {
			line_cursor_it = this._line_cursor_it;
			char_cursor_it = this._char_cursor_it;
		} else {
			[line_cursor_it, char_cursor_it] = this.GetIteratorByOffset(offset_x, offset_y);
		}
		if (char_cursor_it !== 1) {
			this._line_cursor_it = line_cursor_it;
			this._char_cursor_it = char_cursor_it;
			this._line_select_it = line_cursor_it;
			this._char_select_it = char_cursor_it - 1;
		} else {
			if (line_list[line_cursor_it - 1].char_count > 1) {
				this._line_cursor_it = line_cursor_it;
				this._char_cursor_it = char_cursor_it + 1;
				this._line_select_it = line_cursor_it;
				this._char_select_it = char_cursor_it;
			} else {
				if (line_cursor_it > 1) {
					this._line_cursor_it = line_cursor_it;
					this._char_cursor_it = char_cursor_it;
					this._line_select_it = line_cursor_it - 1;
					this._char_select_it = line_list[this._line_select_it - 1].char_count - 1;
					if (this._char_select_it === 0) {
						this._char_select_it = 1;
					}
				} else {
					if (this._line_count > 1) {
						this._line_cursor_it = line_cursor_it + 1;
						if (line_list[this._line_cursor_it - 1].char_count === 1) {
							this._char_cursor_it = 1;
						} else {
							this._char_cursor_it = 2;
						}
						this._line_select_it = line_cursor_it;
						this._char_select_it = char_cursor_it;
					} else {
						return false;
					}
				}
			}
		}
		return true;
	},
	ClickMultiCursor : function() {
		this.UpdateFontText();
		this.ResetCursorLine();
		this.ResetCursor();
	},
	DragMultiCursor : function(offset_x, offset_y) {
		let line_list = this._line_list;
		offset_x = offset_x + this._drag_delta_x;
		offset_y = offset_y + this._drag_delta_y;
		[this._line_cursor_it, this._char_cursor_it] = this.GetIteratorByOffset(offset_x, offset_y);
		if (line_list[this._line_cursor_it - 1].pre_height === -this._scroll_list.scroll_offset && this._line_cursor_it !== 1 && offset_y < 0) {
			this._line_cursor_it = this._line_cursor_it - 1;
			if (this._char_cursor_it > line_list[this._line_cursor_it - 1].char_count) {
				this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count;
			}
		}
		if (this._line_cursor_it === this._line_count && line_list[this._line_cursor_it - 1].pre_height === line_list[this._line_cursor_it - 1].acc_height && this._line_cursor_it !== 1) {
			this._line_cursor_it = this._line_cursor_it - 1;
			this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count;
		}
		this.ResetCursorLine();
		this.ResetCursor();
	},
	ShowDefaultText : function() {
		if (this._is_focus === false) {
			if (this._focus_cursor && this.is_empty) {
				this._default_text_area.visible = true;
			} else {
				this._default_text_area.visible = false;
			}
		} else {
			this._default_text_area.visible = false;
		}
	},
	CursorOffsetLRImpl : function(left) {
		let line_list = this._line_list;
		if (left) {
			if (this._line_cursor_it === 1 && this._char_cursor_it === 1) {
				return;
			}
			if (this._line_cursor_it === this._line_start_it) {
				if (this._char_cursor_it === 1) {
					this._line_cursor_it = this._line_cursor_it - 1;
					this._line_start_it = this._line_start_it - 1;
					this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count + 1;
					this._char_cursor_it = this._char_cursor_it - 1;
				} else {
					this._char_cursor_it = this._char_cursor_it - 1;
				}
			} else {
				if (this._char_cursor_it === 1) {
					this._line_cursor_it = this._line_cursor_it - 1;
					this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count + 1;
					this._char_cursor_it = this._char_cursor_it - 1;
				} else {
					this._char_cursor_it = this._char_cursor_it - 1;
				}
			}
			if (this._line_cursor_it === this._line_count && line_list[this._line_cursor_it - 1].pre_height === line_list[this._line_cursor_it - 1].acc_height && this._line_cursor_it !== 1) {
				this._line_cursor_it = this._line_cursor_it - 1;
				this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count;
			}
			this.ResetCursorLine();
			this.ResetCursor();
			return;
		}
		let end_line_it = this._line_count + 1;
		end_line_it = end_line_it - 1;
		let end_char_it = line_list[end_line_it - 1].char_count + 1;
		end_char_it = end_char_it - 1;
		if (this._line_cursor_it === end_line_it && this._char_cursor_it === end_char_it) {
			return;
		}
		end_char_it = line_list[this._line_cursor_it - 1].char_count + 1;
		end_char_it = end_char_it - 1;
		if (this._char_cursor_it === end_char_it) {
			this._line_cursor_it = this._line_cursor_it + 1;
			this._char_cursor_it = 1;
		} else {
			this._char_cursor_it = this._char_cursor_it + 1;
		}
		if (this._line_cursor_it === this._line_count && line_list[this._line_cursor_it - 1].pre_height === line_list[this._line_cursor_it - 1].acc_height && this._line_cursor_it !== 1) {
			this._line_cursor_it = this._line_cursor_it - 1;
			this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count;
		}
		this.ResetCursorLine();
		this.ResetCursor();
	},
	CursorOffsetUDImpl : function(up) {
		let line_list = this._line_list;
		if (up) {
			if (this._line_cursor_it === 1) {
				return;
			}
			let offset_x = line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width;
			if (this._line_cursor_it === this._line_start_it) {
				this._line_start_it = this._line_start_it - 1;
			}
			this._line_cursor_it = this._line_cursor_it - 1;
			this._char_cursor_it = 1;
			let end_char_it = line_list[this._line_cursor_it - 1].char_count + 1;
			while (this._char_cursor_it !== end_char_it) {
				if (line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width >= offset_x) {
					break;
				}
				this._char_cursor_it = this._char_cursor_it + 1;
			}
			if (this._char_cursor_it === end_char_it) {
				end_char_it = end_char_it - 1;
				this._char_cursor_it = end_char_it;
			}
			if (this._line_cursor_it === this._line_count && line_list[this._line_cursor_it - 1].pre_height === line_list[this._line_cursor_it - 1].acc_height && this._line_cursor_it !== 1) {
				this._line_cursor_it = this._line_cursor_it - 1;
				this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count;
			}
			this.ResetCursorLine();
			this.ResetCursor();
			return;
		}
		let line_end_test_it = this._line_count + 1;
		line_end_test_it = line_end_test_it - 1;
		if (this._line_cursor_it === line_end_test_it) {
			this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count;
			this.ResetCursorLine();
			this.ResetCursor();
			return;
		}
		let offset_x = line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width;
		this._line_cursor_it = this._line_cursor_it + 1;
		this._char_cursor_it = 1;
		let end_char_it = line_list[this._line_cursor_it - 1].char_count + 1;
		while (this._char_cursor_it !== end_char_it) {
			if (line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1].acc_width >= offset_x) {
				break;
			}
			this._char_cursor_it = this._char_cursor_it + 1;
		}
		if (this._char_cursor_it === end_char_it) {
			end_char_it = end_char_it - 1;
			this._char_cursor_it = end_char_it;
		}
		if (this._line_cursor_it === this._line_count && line_list[this._line_cursor_it - 1].pre_height === line_list[this._line_cursor_it - 1].acc_height && this._line_cursor_it !== 1) {
			this._line_cursor_it = this._line_cursor_it - 1;
			this._char_cursor_it = line_list[this._line_cursor_it - 1].char_count;
		}
		this.ResetCursorLine();
		this.ResetCursor();
	},
	GetIteratorByOffset : function(offset_x, offset_y) {
		let line_list = this._line_list;
		let line_it = this._line_start_it;
		let line_end_it = this._line_count + 1;
		let real_offset_y = offset_y + line_list[this._line_start_it - 1].pre_height + this._start_it_delta;
		while (line_it !== line_end_it) {
			if (real_offset_y <= line_list[line_it - 1].acc_height) {
				let half_line_height = (line_list[line_it - 1].acc_height - line_list[line_it - 1].pre_height) * 0.5;
				if (real_offset_y - line_list[line_it - 1].acc_height > half_line_height) {
					line_it = line_it + 1;
				}
				break;
			} else {
				line_it = line_it + 1;
			}
		}
		if (line_it === line_end_it) {
			line_end_it = line_end_it - 1;
			line_it = line_end_it;
		}
		let line_it_result = line_it;
		let real_offset_x = offset_x;
		let char_it = 1;
		let char_end_it = line_list[line_it - 1].char_count + 1;
		let line = line_list[line_it - 1];
		while (char_it !== char_end_it) {
			if (real_offset_x <= line.char_list[char_it - 1].acc_width) {
				let half_char_width = (line.char_list[char_it - 1].acc_width - line.char_list[char_it - 1].pre_width) * 0.5;
				if (real_offset_x - line.char_list[char_it - 1].pre_width < half_char_width && char_it !== 1) {
					char_it = char_it - 1;
				}
				break;
			} else {
				char_it = char_it + 1;
			}
		}
		if (char_it === char_end_it) {
			char_end_it = char_end_it - 1;
			char_it = char_end_it;
		}
		let char_it_result = char_it;
		return [line_it_result, char_it_result];
	},
	get is_input() {
		return true;
	},
	get is_empty() {
		return this._line_count === 1 && this._line_list[1 - 1].char_count === 1;
	},
	get editable() {
		return this._editable;
	},
	set editable(value) {
		this._editable = value;
	},
	set ims_padding(value) {
		this._ims_padding = value;
	},
	get ims_padding() {
		return this._ims_padding;
	},
	SetCursor : function(rel_x, rel_y) {
		if (this._auto_ims) {
			this.OpenIME();
		}
		this._is_selecting = false;
		if (this._multi_cursor) {
			this._multi_cursor = false;
			this._start_cursor.visible = false;
			this._end_cursor.visible = false;
			this._cursor.visible = true;
			this.ClickCursor(rel_x - this._scroll_list.x, rel_y - this._scroll_list.y);
		} else {
			this.ClickCursor(rel_x - this._scroll_list.x, rel_y - this._scroll_list.y);
		}
	},
	SetMultiCursor : function(rel_x, rel_y) {
		if (this._auto_ims) {
			this.OpenIME();
		}
		let result = this.CheckMultiCursor(rel_x - this._scroll_list.x, rel_y - this._scroll_list.y, false);
		if (result === false) {
			return false;
		}
		this._is_selecting = true;
		if (this._multi_cursor === false) {
			this._multi_cursor = true;
			this._cursor.visible = false;
			this._start_cursor.visible = true;
			this._end_cursor.visible = true;
			this.ClickMultiCursor();
		} else {
			this.ClickMultiCursor();
		}
		return true;
	},
	TransToCursor : function() {
		if (this._multi_cursor === false) {
			return;
		}
		let line_list = this._line_list;
		if (this._end_cursor_data === "select") {
			this._line_cursor_it = this._line_select_it;
			this._char_cursor_it = this._char_select_it;
		}
		this._char_select_it = line_list[this._line_select_it - 1].char_count + 1;
		this._is_selecting = false;
		this._multi_cursor = false;
		this._start_cursor.visible = false;
		this._end_cursor.visible = false;
		this._cursor.visible = true;
		this.UpdateFontText();
		this.ResetCursorLine();
		this.ResetCursor();
	},
	TransToMulti : function() {
		if (this._multi_cursor) {
			return false;
		}
		let result = this.CheckMultiCursor(undefined, undefined, true);
		if (result === false) {
			return false;
		}
		this._is_selecting = true;
		this._multi_cursor = true;
		this._cursor.visible = false;
		this._start_cursor.visible = true;
		this._end_cursor.visible = true;
		this.UpdateFontText();
		this.ResetCursorLine();
		this.ResetCursor();
		return true;
	},
	OpenIME : function(x, y, width, height) {
		if (this._editable) {
			this.ResetCursor();
			if (x !== undefined && y !== undefined && width !== undefined && height !== undefined) {
				ALittle.System_SetIMERect(__floor(x), __floor(y), __floor(width), __floor(height));
			} else {
				let [global_x, global_y] = this.LocalToGlobal();
				global_x = global_x + this.cursor_x;
				global_y = global_y + (this.cursor_y + this.font_size) * this.scale_y;
				ALittle.System_SetIMERect(__floor(global_x), __floor(global_y), 10, __floor(5 + this._ims_padding));
			}
			ALittle.System_OpenIME();
		}
	},
	CloseIME : function() {
		ALittle.System_CloseIME();
	},
	HandleFocusOut : function(event) {
		if (this._auto_ims) {
			ALittle.System_CloseIME();
		}
		this._is_focus = false;
		if (this._focus_cursor) {
			if (this._multi_cursor === false) {
				this._cursor.visible = false;
			}
		}
		this.ShowDefaultText();
	},
	HandleFocusIn : function(event) {
		if (this._auto_ims) {
			this.OpenIME();
		}
		this._is_focus = true;
		if (this._multi_cursor === false) {
			this._cursor.visible = true;
		}
		this.ShowDefaultText();
	},
	HandleLButtonDown : function(event) {
		if (this._multi_cursor === false) {
			this._is_longclick = false;
			if (event.rel_x >= this._scroll_list.x && event.rel_x <= this._scroll_list.x + this._scroll_list.width && event.rel_y >= this._scroll_list.y && event.rel_y <= this._scroll_list.y + this._scroll_list.height) {
				if (event.count % 3 === 1) {
					this._is_selecting = false;
					this.ClickCursor(event.rel_x - this._scroll_list.x, event.rel_y - this._scroll_list.y);
					this.DispatchEvent(___all_struct.get(-1053992999), {});
				} else if (event.count % 3 === 2) {
					this._is_selecting = this.ClickWordCursor(event.rel_x - this._scroll_list.x, event.rel_y - this._scroll_list.y);
				} else {
					this._is_selecting = true;
					this.SelectAll();
				}
				this._is_click = true;
			} else {
				this._is_click = false;
			}
		} else {
			this._click_drag_delta_x = 0;
			this._click_drag_delta_y = 0;
			this._is_click = false;
			this._is_click_cursor = false;
			this._is_click_cursor_name = "";
			this._is_longclick = false;
			if (this._start_cursor.visible && event.rel_x >= this._start_cursor.x && event.rel_x <= this._start_cursor.x + this._start_cursor.width && event.rel_y >= this._start_cursor.y && event.rel_y <= this._start_cursor.y + this._start_cursor.height) {
				this._is_click_cursor = true;
				this._is_click_cursor_name = "start";
			} else if (this._end_cursor.visible && event.rel_x >= this._end_cursor.x && event.rel_x <= this._end_cursor.x + this._end_cursor.width && event.rel_y >= this._end_cursor.y && event.rel_y <= this._end_cursor.y + this._end_cursor.height) {
				this._is_click_cursor = true;
				this._is_click_cursor_name = "end";
			} else {
				if (event.rel_x >= this._scroll_list.x && event.rel_x <= this._scroll_list.x + this._scroll_list.width && event.rel_y >= this._scroll_list.y && event.rel_y <= this._scroll_list.y + this._scroll_list.height) {
					this._is_click = true;
				}
			}
		}
	},
	HandleLButtonUp : function(event) {
		if (this._multi_cursor === true) {
			if (this._is_click && this._is_longclick === false && this._click_drag_delta_x < 2 && this._click_drag_delta_y < 2) {
				this._multi_cursor = false;
				this._start_cursor.visible = false;
				this._end_cursor.visible = false;
				this._cursor.visible = true;
				this.ClickCursor(event.rel_x - this._scroll_list.x, event.rel_y - this._scroll_list.y);
				this.DispatchEvent(___all_struct.get(-1053992999), {});
			}
		}
	},
	HandleLongLButtonDown : function(event) {
		if (this._is_click) {
			if (this.editable === false) {
				let result = this.CheckMultiCursor(event.rel_x - this._scroll_list.x, event.rel_y - this._scroll_list.y, false);
				if (result) {
					this._is_selecting = true;
					if (this._multi_cursor === false) {
						this._multi_cursor = true;
						this._cursor.visible = false;
						this._start_cursor.visible = true;
						this._end_cursor.visible = true;
						this.ClickMultiCursor();
					} else {
						this.ClickMultiCursor();
					}
				}
			} else {
				this._multi_cursor = false;
				this._start_cursor.visible = false;
				this._end_cursor.visible = false;
				this._cursor.visible = true;
				this.ClickCursor(event.rel_x - this._scroll_list.x, event.rel_y - this._scroll_list.y);
			}
			let e = {};
			e.target = this;
			e.abs_x = event.abs_x;
			e.abs_y = event.abs_y;
			e.rel_x = event.rel_x;
			e.rel_y = event.rel_y;
			this.DispatchEvent(___all_struct.get(774620468), e);
			this._is_longclick = true;
		}
	},
	CheckAtKeyInput : function(input_text) {
		if (input_text !== "@") {
			return false;
		}
		let line_list = this._line_list;
		let line_cursor_it = this._line_cursor_it;
		let char_cursor_it = this._char_cursor_it;
		if (this._line_cursor_it === 1 && this._char_cursor_it === 1) {
			this.DispatchEvent(___all_struct.get(1816229739), {});
			return true;
		}
		if (this._line_cursor_it > 1 && this._char_cursor_it === 1) {
			line_cursor_it = line_cursor_it - 1;
			char_cursor_it = line_list[line_cursor_it - 1].char_count;
		}
		let char_info = line_list[this._line_cursor_it - 1].char_list[this._char_cursor_it - 1];
		let forward_text = char_info.text;
		if (forward_text === undefined || !(this.CharIsNumber(forward_text) || this.CharIsLetter(forward_text))) {
			this.DispatchEvent(___all_struct.get(1816229739), {});
			return true;
		}
		return false;
	},
	HandleTextInput : function(event) {
		if (this._multi_cursor === false) {
			if ((this._editable || event.custom)) {
				if (this.CheckAtKeyInput(event.text)) {
					return;
				}
				this._is_selecting = false;
				let is_change = this.InsertTextNative(event.text);
				if (is_change) {
					this.DispatchEvent(___all_struct.get(958494922), {});
					this.ShowDefaultText();
				}
			}
		} else {
			if (this._is_selecting && this._editable) {
				this._is_selecting = false;
				let is_change = this.InsertTextNative(event.text);
				if (is_change) {
					this.DispatchEvent(___all_struct.get(958494922), {});
					this.ShowDefaultText();
				}
				this._multi_cursor = false;
			}
		}
	},
	HandleDragBegin : function(event) {
		if (this._can_drag_text === false) {
			return;
		}
		if (this._multi_cursor === false) {
			if (this._is_click) {
				this._is_drag_begin = true;
				this._is_selecting = true;
				this.DragCursorBegin();
			} else {
				this._is_drag_begin = false;
			}
		} else {
			if (this._is_click_cursor) {
				if ((this._is_click_cursor_name === "start" && this._start_cursor_data === "select") || (this._is_click_cursor_name === "end" && this._end_cursor_data === "select")) {
					let line_temp_it = this._line_select_it;
					let char_temp_it = this._char_select_it;
					this._line_select_it = this._line_cursor_it;
					this._char_select_it = this._char_cursor_it;
					this._line_cursor_it = line_temp_it;
					this._char_cursor_it = char_temp_it;
				}
				if (this._is_click_cursor_name === "start") {
					this._drag_delta_x = this._start_cursor.x + this._start_cursor.width - event.rel_x;
					this._drag_delta_y = this._start_cursor.y + this._cursor_margin_up + (this._start_cursor.height - this._cursor_margin_up - this._cursor_margin_down) / 2 - event.rel_y;
				} else if (this._is_click_cursor_name === "end") {
					this._drag_delta_x = this._end_cursor.x - event.rel_x;
					this._drag_delta_y = this._end_cursor.y + this._cursor_margin_up + (this._end_cursor.height - this._cursor_margin_up - this._cursor_margin_down) / 2 - event.rel_y;
				}
				this._is_drag_begin = true;
				this.DispatchEvent(___all_struct.get(9565867), {});
			} else if (this._is_click) {
				this._is_drag_begin = true;
				this.DispatchEvent(___all_struct.get(9565867), {});
			} else {
				this._is_drag_begin = false;
			}
		}
	},
	HandleDrag : function(event) {
		if (this._can_drag_text === false) {
			return;
		}
		if (this._is_drag_begin === false) {
			return;
		}
		if (this._multi_cursor === false) {
			if (this._is_selecting === false) {
				return;
			}
			this.DragCursor(event.rel_x - this._scroll_list.x, event.rel_y - this._scroll_list.y);
		} else {
			if (this._is_click_cursor) {
				this.DragMultiCursor(event.rel_x - this._scroll_list.x, event.rel_y - this._scroll_list.y);
			} else {
				if (this._line_list[1 - 1] !== undefined && this._line_list[1 - 1].acc_height !== this._line_list[1 - 1].pre_height) {
					this._click_drag_delta_x = this._click_drag_delta_x + __abs(event.delta_x);
					this._click_drag_delta_y = this._click_drag_delta_y + __abs(event.delta_y);
					this.DragEdit(event.delta_y);
				}
			}
			this.DispatchEvent(___all_struct.get(291295687), {});
		}
	},
	HandleDragEnd : function(event) {
		if (this._can_drag_text === false) {
			return;
		}
		if (this._is_drag_begin === false) {
			return;
		}
		if (this._multi_cursor) {
			if (this._cursor.visible) {
				this._multi_cursor = false;
			}
			this.DispatchEvent(___all_struct.get(-203792390), {});
		}
	},
	HandleMButtonWheel : function(event) {
		if (this._multi_cursor === false) {
			if (event.delta_y > 0) {
				this._is_selecting = false;
				this.CursorOffsetUD(true);
			} else if (event.delta_y < 0) {
				this._is_selecting = false;
				this.CursorOffsetUD(false);
			}
			if (event.delta_x > 0) {
				this._is_selecting = false;
				this.SelectCursorOffsetLR(true);
			} else if (event.delta_x < 0) {
				this._is_selecting = false;
				this.SelectCursorOffsetLR(false);
			}
		} else {
			this.DragEdit(event.delta_y);
		}
	},
	HandleMoveIn : function(event) {
		ALittle.System_SetEditCursor();
	},
	HandleMoveOut : function(event) {
		ALittle.System_SetNormalCursor();
	},
	HandleKeyDown : function(event) {
		let is_change = false;
		if (event.sym === 9) {
			if (this._multi_cursor === false) {
				if (this._editable || event.custom) {
					this._is_selecting = false;
					is_change = this.InsertTextNative("\t");
				}
			} else {
				if (this._is_selecting && this._editable) {
					this._is_selecting = false;
					is_change = this.InsertTextNative("\t");
					event.handled = true;
					this._multi_cursor = false;
				}
			}
		} else if (event.sym === 1073741904) {
			if (this._multi_cursor === false) {
				if (lua.bit.band(event.mod, ALittle.UIEnumTypes.KMOD_SHIFT) === 0) {
					this._is_selecting = false;
					this.CursorOffsetLR(true);
					this.UpdateFontText();
				} else {
					this._is_selecting = true;
					this.SelectCursorOffsetLR(true);
				}
			}
			event.handled = true;
		} else if (event.sym === 1073741903) {
			if (this._multi_cursor === false) {
				if (lua.bit.band(event.mod, ALittle.UIEnumTypes.KMOD_SHIFT) === 0) {
					this._is_selecting = false;
					this.CursorOffsetLR(false);
					this.UpdateFontText();
				} else {
					this._is_selecting = true;
					this.SelectCursorOffsetLR(false);
				}
			}
			event.handled = true;
		} else if (event.sym === 1073741906) {
			if (this._multi_cursor === false) {
				if (lua.bit.band(event.mod, ALittle.UIEnumTypes.KMOD_SHIFT) === 0) {
					this._is_selecting = false;
					this.CursorOffsetUD(true);
					this.UpdateFontText();
				} else {
					this._is_selecting = true;
					this.SelectCursorOffsetUD(true);
				}
			}
			event.handled = true;
		} else if (event.sym === 1073741905) {
			if (this._multi_cursor === false) {
				if (lua.bit.band(event.mod, ALittle.UIEnumTypes.KMOD_SHIFT) === 0) {
					this._is_selecting = false;
					this.CursorOffsetUD(false);
					this.UpdateFontText();
				} else {
					this._is_selecting = true;
					this.SelectCursorOffsetUD(false);
				}
			}
			event.handled = true;
		} else if (event.sym === 8) {
			if (this._multi_cursor === false) {
				if (this._editable || event.custom) {
					this._is_selecting = false;
					is_change = this.DeleteText(true);
					event.handled = true;
					this.UpdateFontText();
				}
			} else {
				if (this._is_selecting && this._editable) {
					this._is_selecting = false;
					is_change = this.DeleteText(true);
					event.handled = true;
					this.UpdateFontText();
					this._multi_cursor = false;
				}
			}
		} else if (event.sym === 127) {
			if (this._multi_cursor === false) {
				if (this._editable || event.custom) {
					this._is_selecting = false;
					is_change = this.DeleteText(false);
					event.handled = true;
					this.UpdateFontText();
				}
			} else {
				if (this._is_selecting && this._editable) {
					this._is_selecting = false;
					is_change = this.DeleteText(false);
					event.handled = true;
					this.UpdateFontText();
					this._multi_cursor = false;
				}
			}
		} else if (event.sym === 1073741898) {
			this._is_selecting = false;
			this.SetCursorToHome();
			event.handled = true;
			this.UpdateFontText();
		} else if (event.sym === 1073741901) {
			this._is_selecting = false;
			this.SetCursorToEnd();
			event.handled = true;
			this.UpdateFontText();
		} else if (event.sym === 13 || event.sym === 1073741912) {
			if (this._multi_cursor === false) {
				if (this._editable || event.custom) {
					this._is_selecting = false;
					is_change = this.InsertTextNative("\n");
					event.handled = true;
					this.UpdateFontText();
				}
			} else {
				if (this._is_selecting && this._editable) {
					this._is_selecting = false;
					is_change = this.InsertTextNative("\n");
					event.handled = true;
					this.UpdateFontText();
					this._multi_cursor = false;
				}
			}
		} else if (event.sym === 120 && lua.bit.band(event.mod, ALittle.UIEnumTypes.KMOD_CTRL) !== 0) {
			if (this._multi_cursor === false) {
				if (this._editable || event.custom) {
					this._is_selecting = false;
					let select_text = this.GetSelectText();
					if (select_text[1 - 1] !== undefined) {
						ALittle.System_SetClipboardText(lua.json.encode(select_text));
						is_change = this.DeleteSelectText();
					}
					this.UpdateFontText();
					event.handled = true;
				}
			} else {
				if (this._is_selecting && this._editable) {
					this._is_selecting = false;
					let select_text = this.GetSelectText();
					if (select_text[1 - 1] !== undefined) {
						ALittle.System_SetClipboardText(lua.json.encode(select_text));
						is_change = this.DeleteSelectText();
					}
					this.UpdateFontText();
					event.handled = true;
					this._multi_cursor = false;
				}
			}
		} else if (event.sym === 99 && lua.bit.band(event.mod, ALittle.UIEnumTypes.KMOD_CTRL) !== 0) {
			let select_text = this.GetSelectText();
			if (select_text[1 - 1] !== undefined) {
				ALittle.System_SetClipboardText(lua.json.encode(select_text));
			}
			event.handled = true;
		} else if (event.sym === 118 && lua.bit.band(event.mod, ALittle.UIEnumTypes.KMOD_CTRL) !== 0) {
			if (this._multi_cursor === false) {
				if (this._editable || event.custom) {
					this._is_selecting = false;
					if (ALittle.System_HasClipboardText()) {
						let content = ALittle.System_GetClipboardText();
						let [error, new_content] = (function() { try { let ___VALUE = lua.json.decode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
						if (error === undefined && __type(new_content) === "table" && this.CheckDisplayList(new_content)) {
							if (this.CheckAtKeyInput(new_content)) {
								return;
							}
							is_change = this.InsertDisplayListNative(new_content, false);
						} else {
							if (this.CheckAtKeyInput(content)) {
								return;
							}
							is_change = this.InsertTextNative(content);
						}
					}
				}
			} else {
				if (this._is_selecting && this._editable) {
					this._is_selecting = false;
					if (ALittle.System_HasClipboardText()) {
						let content = ALittle.System_GetClipboardText();
						let [error, new_content] = (function() { try { let ___VALUE = lua.json.decode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
						if (error === undefined && __type(new_content) === "table" && this.CheckDisplayList(new_content)) {
							is_change = this.InsertDisplayListNative(new_content, false);
						} else {
							is_change = this.InsertTextNative(content);
						}
					}
					event.handled = true;
					this._multi_cursor = false;
				}
			}
		} else if (event.sym === 97 && lua.bit.band(event.mod, ALittle.UIEnumTypes.KMOD_CTRL) !== 0) {
			this._is_selecting = true;
			this.SelectAll();
			event.handled = true;
		}
		if (is_change) {
			this.DispatchEvent(___all_struct.get(958494922), {});
			this._current_flash_alpha = 1.5;
			this.ShowDefaultText();
		}
	},
	InsertText : function(display_list, selected) {
		if (this._editable === false) {
			return;
		}
		if (this._multi_cursor && this._is_selecting === false) {
			return;
		}
		this._is_selecting = false;
		this.InsertDisplayListNative(display_list, selected);
		this._multi_cursor = false;
		this.ShowDefaultText();
	},
	InsertWord : function(word_text) {
		if (this._editable === false) {
			return;
		}
		if (this._multi_cursor && this._is_selecting === false) {
			return;
		}
		this._is_selecting = false;
		this.InsertTextNative(word_text);
		this.TransToCursor();
		this.ShowDefaultText();
	},
	CopyText : function(return_cursor) {
		let select_text = this.GetSelectText();
		if (select_text[1 - 1] !== undefined) {
			ALittle.System_SetClipboardText(lua.json.encode(select_text));
		}
		if (return_cursor) {
			this.TransToCursor();
		}
		this.ShowDefaultText();
	},
	CopyWord : function(return_cursor) {
		let select_text = this.GetSelectWord();
		if (select_text !== undefined) {
			ALittle.System_SetClipboardText(select_text);
		}
		if (return_cursor) {
			this.TransToCursor();
		}
		this.ShowDefaultText();
	},
	CutText : function() {
		if (this._editable === false) {
			return;
		}
		if (this._multi_cursor && this._is_selecting === false) {
			return;
		}
		this._is_selecting = false;
		let select_text = this.GetSelectText();
		if (select_text[1 - 1] !== undefined) {
			ALittle.System_SetClipboardText(lua.json.encode(select_text));
			this.DeleteSelectText();
			this.UpdateFontText();
			this.TransToCursor();
		}
		this.ShowDefaultText();
	},
	CutWord : function() {
		if (this._editable === false) {
			return;
		}
		if (this._multi_cursor && this._is_selecting === false) {
			return;
		}
		this._is_selecting = false;
		let select_text = this.GetSelectWord();
		if (select_text !== undefined) {
			ALittle.System_SetClipboardText(select_text);
			this.DeleteSelectText();
			this.UpdateFontText();
			this.TransToCursor();
		}
		this.ShowDefaultText();
	},
	PasteText : function() {
		if (this._editable === false) {
			return;
		}
		if (this._multi_cursor && this._is_selecting === false) {
			return;
		}
		this._is_selecting = false;
		if (ALittle.System_HasClipboardText()) {
			let content = ALittle.System_GetClipboardText();
			let [error, new_content] = (function() { try { let ___VALUE = lua.json.decode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
			if (error === undefined && __type(new_content) === "table" && this.CheckDisplayList(new_content)) {
				if (this.CheckAtKeyInput(new_content)) {
					return;
				}
				this.InsertDisplayListNative(new_content, false);
			} else {
				if (this.CheckAtKeyInput(content)) {
					return;
				}
				this.InsertTextNative(content);
			}
			this.TransToCursor();
		}
		this.ShowDefaultText();
	},
	PasteWord : function() {
		if (this._editable === false) {
			return;
		}
		if (this._multi_cursor && this._is_selecting === false) {
			return;
		}
		this._is_selecting = false;
		if (ALittle.System_HasClipboardText()) {
			let content = ALittle.System_GetClipboardText();
			this.InsertTextNative(content);
			this.TransToCursor();
		}
		this.ShowDefaultText();
	},
	Clear : function() {
		this.ClearText();
		this.ShowDefaultText();
	},
	Delete : function() {
		if (this._editable === false) {
			return;
		}
		if (this._multi_cursor && this._is_selecting === false) {
			return;
		}
		this._is_selecting = false;
		this.DeleteText(true);
		this.TransToCursor();
		this.ShowDefaultText();
	},
}, "ALittle.RichEdit");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(-256576702, "ALittle.RichInputFontChangedEvent", {
name : "ALittle.RichInputFontChangedEvent", ns_name : "ALittle", rl_name : "RichInputFontChangedEvent", hash_code : -256576702,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(1424993548, "ALittle.RichInputMultiDragBeginEvent", {
name : "ALittle.RichInputMultiDragBeginEvent", ns_name : "ALittle", rl_name : "RichInputMultiDragBeginEvent", hash_code : 1424993548,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(1640499878, "ALittle.UIRichInputLongClickEvent", {
name : "ALittle.UIRichInputLongClickEvent", ns_name : "ALittle", rl_name : "UIRichInputLongClickEvent", hash_code : 1640499878,
name_list : ["target","abs_x","abs_y","rel_x","rel_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(1818243950, "ALittle.RichInputCharInfo", {
name : "ALittle.RichInputCharInfo", ns_name : "ALittle", rl_name : "RichInputCharInfo", hash_code : 1818243950,
name_list : ["acc_width","pre_width","text_info","text","password_text","text_object","ctrl_info","ctrl"],
type_list : ["double","double","ALittle.DisplayInfo","string","string","ALittle.Text","ALittle.DisplayInfo","ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-884368490, "ALittle.RichInputMultiDragEndEvent", {
name : "ALittle.RichInputMultiDragEndEvent", ns_name : "ALittle", rl_name : "RichInputMultiDragEndEvent", hash_code : -884368490,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-683607428, "ALittle.RichInputCursorClickEvent", {
name : "ALittle.RichInputCursorClickEvent", ns_name : "ALittle", rl_name : "RichInputCursorClickEvent", hash_code : -683607428,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-605767802, "ALittle.RichInputMultiDragEvent", {
name : "ALittle.RichInputMultiDragEvent", ns_name : "ALittle", rl_name : "RichInputMultiDragEvent", hash_code : -605767802,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})

let __byte = ALittle.String_Byte;
let __sub = ALittle.String_Sub;
let __find = ALittle.String_Find;
let __floor = ALittle.Math_Floor;
let __len = ALittle.String_Len;
let __abs = ALittle.Math_Abs;
let __type = ALittle.String_Type;
if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.RichInput = JavaScript.Class(ALittle.DisplayLayout, {
	CheckDisplayList : function(content) {
		let ___OBJECT_1 = content;
		for (let k = 1; k <= ___OBJECT_1.length; ++k) {
			let v = ___OBJECT_1[k - 1];
			if (v === undefined) break;
			if (v.__class === undefined) {
				return false;
			}
		}
		return true;
	},
	CharIsNumber : function(str) {
		let c = __byte(str, 1);
		return c >= 48 && c <= 57;
	},
	CharIsLetter : function(str) {
		let c = __byte(str, 1);
		return c >= 65 && c <= 90 || c >= 97 && c <= 122;
	},
	CompareTextInfo : function(a, b) {
		if (a.font_path !== b.font_path) {
			return false;
		}
		if (a.font_size !== b.font_size) {
			return false;
		}
		if (a.red !== b.red) {
			return false;
		}
		if (a.green !== b.green) {
			return false;
		}
		if (a.blue !== b.blue) {
			return false;
		}
		if (a.bold !== b.bold) {
			return false;
		}
		if (a.italic !== b.italic) {
			return false;
		}
		if (a.underline !== b.underline) {
			return false;
		}
		if (a.deleteline !== b.deleteline) {
			return false;
		}
		if (a.outline !== b.outline) {
			return false;
		}
		return true;
	},
	CopyTextInfo : function(b) {
		let a = {};
		a.__class = "Text";
		a.font_path = b.font_path;
		a.font_size = b.font_size;
		a.red = b.red;
		a.green = b.green;
		a.blue = b.blue;
		a.bold = b.bold;
		a.italic = b.italic;
		a.underline = b.underline;
		a.deleteline = b.deleteline;
		a.outline = b.outline;
		return a;
	},
	InitTextInfo : function() {
		let font_text = this._font_text;
		let a = {};
		a.__class = "Text";
		a.font_path = font_text.font_path;
		a.font_size = font_text.font_size;
		a.red = font_text.red;
		a.green = font_text.green;
		a.blue = font_text.blue;
		a.bold = font_text.bold;
		a.italic = font_text.italic;
		a.underline = font_text.underline;
		a.deleteline = font_text.deleteline;
		a.outline = font_text.outline;
		return a;
	},
	SetDrawText : function(font_text) {
		let draw_text = this._draw_text;
		draw_text.font_path = font_text.font_path;
		draw_text.font_size = font_text.font_size;
		draw_text.red = font_text.red;
		draw_text.green = font_text.green;
		draw_text.blue = font_text.blue;
		draw_text.bold = font_text.bold;
		draw_text.italic = font_text.italic;
		draw_text.underline = font_text.underline;
		draw_text.deleteline = font_text.deleteline;
		draw_text.outline = font_text.outline;
	},
	SplitText : function(char_info, char_info_list, char_info_list_count) {
		let text = char_info.text;
		while (true) {
			let start_index_1 = __find(text, "\n");
			let start_index_2 = __find(text, "\t");
			if (start_index_1 !== undefined && start_index_2 !== undefined) {
				if (start_index_1 < start_index_2) {
					start_index_2 = undefined;
				} else {
					start_index_1 = undefined;
				}
			}
			if (start_index_1 !== undefined) {
				let sub_text = __sub(text, 1, start_index_1 - 1);
				text = __sub(text, start_index_1 + 1);
				if (sub_text !== "") {
					let new_char_info = ALittle.String_CopyTable(char_info);
					new_char_info.text = sub_text;
					++ char_info_list_count;
					char_info_list[char_info_list_count - 1] = new_char_info;
				}
			} else if (start_index_2 !== undefined) {
				let sub_text = __sub(text, 1, start_index_2 - 1);
				text = __sub(text, start_index_2 + 1);
				if (sub_text !== "") {
					let new_char_info = ALittle.String_CopyTable(char_info);
					new_char_info.text = sub_text;
					++ char_info_list_count;
					char_info_list[char_info_list_count - 1] = new_char_info;
				}
			} else {
				if (text !== "") {
					let new_char_info = ALittle.String_CopyTable(char_info);
					new_char_info.text = text;
					++ char_info_list_count;
					char_info_list[char_info_list_count - 1] = new_char_info;
				}
				break;
			}
		}
		return char_info_list_count;
	},
	DisplayListToCharInfoList : function(display_list, default_text_info) {
		let char_info_list = [];
		let char_info_list_count = 0;
		let last_text_info = default_text_info;
		let ___OBJECT_2 = display_list;
		for (let display_index = 1; display_index <= ___OBJECT_2.length; ++display_index) {
			let display_info = ___OBJECT_2[display_index - 1];
			if (display_info === undefined) break;
			if (display_info.__class === "Text") {
				let new_char_info = {};
				new_char_info.acc_width = 0;
				new_char_info.pre_width = 0;
				new_char_info.text_info = this.CopyTextInfo(display_info);
				new_char_info.text_object = undefined;
				new_char_info.text = display_info.text;
				new_char_info.ctrl_info = undefined;
				new_char_info.ctrl = undefined;
				++ char_info_list_count;
				char_info_list[char_info_list_count - 1] = new_char_info;
				last_text_info = new_char_info.text_info;
			} else {
				if (last_text_info === undefined) {
					last_text_info = this.InitTextInfo();
				}
				let new_char_info = {};
				new_char_info.acc_width = 0;
				new_char_info.pre_width = 0;
				new_char_info.text_info = last_text_info;
				new_char_info.text_object = undefined;
				new_char_info.text = "";
				new_char_info.ctrl_info = display_info;
				new_char_info.ctrl = undefined;
				++ char_info_list_count;
				char_info_list[char_info_list_count - 1] = new_char_info;
			}
		}
		return char_info_list;
	},
	CharInfoListToDisplayList : function(list) {
		let display_list = [];
		let display_list_count = 0;
		let text_info = undefined;
		let text_list = undefined;
		let text_list_count = 0;
		let ___OBJECT_3 = list;
		for (let char_index = 1; char_index <= ___OBJECT_3.length; ++char_index) {
			let char_info = ___OBJECT_3[char_index - 1];
			if (char_info === undefined) break;
			if (char_info.ctrl_info === undefined) {
				if (text_info === undefined) {
					text_info = char_info.text_info;
					text_list = [];
					text_list_count = 1;
					text_list[text_list_count - 1] = char_info.text;
				} else if (text_info === char_info.text_info) {
					++ text_list_count;
					text_list[text_list_count - 1] = char_info.text;
				} else {
					if (this.CompareTextInfo(text_info, char_info.text_info)) {
						++ text_list_count;
						text_list[text_list_count - 1] = char_info.text;
					} else {
						let text = ALittle.String_Join(text_list, "");
						if (text !== "") {
							let text_ctrl = ALittle.String_CopyTable(text_info);
							text_ctrl.__class = "Text";
							text_ctrl.text = text;
							++ display_list_count;
							display_list[display_list_count - 1] = text_ctrl;
						}
						text_info = char_info.text_info;
						text_list = [];
						text_list_count = 1;
						text_list[text_list_count - 1] = char_info.text;
					}
				}
			} else {
				if (text_info !== undefined) {
					let text = ALittle.String_Join(text_list, "");
					if (text !== "") {
						let text_ctrl = ALittle.String_CopyTable(text_info);
						text_ctrl.__class = "Text";
						text_ctrl.text = text;
						++ display_list_count;
						display_list[display_list_count - 1] = text_ctrl;
					}
					text_info = undefined;
					text_list = undefined;
					text_list_count = 0;
				}
				++ display_list_count;
				display_list[display_list_count - 1] = ALittle.String_CopyTable(char_info.ctrl_info);
			}
		}
		if (text_info !== undefined) {
			let text = ALittle.String_Join(text_list, "");
			if (text !== "") {
				let text_ctrl = ALittle.String_CopyTable(text_info);
				text_ctrl.__class = "Text";
				text_ctrl.text = text;
				++ display_list_count;
				display_list[display_list_count - 1] = text_ctrl;
			}
		}
		return display_list;
	},
	CharInfoListToWord : function(list) {
		let text_list = [];
		let text_list_count = 0;
		let ___OBJECT_4 = list;
		for (let char_index = 1; char_index <= ___OBJECT_4.length; ++char_index) {
			let char_info = ___OBJECT_4[char_index - 1];
			if (char_info === undefined) break;
			if (char_info.ctrl_info === undefined) {
				++ text_list_count;
				text_list[text_list_count - 1] = char_info.text;
			}
		}
		return ALittle.String_Join(text_list, "");
	},
	UpdateFontText : function() {
		let char_info = this._char_info_list[this._char_cursor_it - 1];
		let is_change = false;
		let font_text = this._font_text;
		let text_info = char_info.text_info;
		if (font_text.font_path !== text_info.font_path) {
			font_text.font_path = text_info.font_path;
			is_change = true;
		}
		if (font_text.font_size !== text_info.font_size) {
			font_text.font_size = text_info.font_size;
			is_change = true;
		}
		if (font_text.red !== text_info.red) {
			font_text.red = text_info.red;
			is_change = true;
		}
		if (font_text.green !== text_info.green) {
			font_text.green = text_info.green;
			is_change = true;
		}
		if (font_text.blue !== text_info.blue) {
			font_text.blue = text_info.blue;
			is_change = true;
		}
		if (font_text.bold !== text_info.bold) {
			font_text.bold = text_info.bold;
			is_change = true;
		}
		if (font_text.italic !== text_info.italic) {
			font_text.italic = text_info.italic;
			is_change = true;
		}
		if (font_text.underline !== text_info.underline) {
			font_text.underline = text_info.underline;
			is_change = true;
		}
		if (font_text.deleteline !== text_info.deleteline) {
			font_text.deleteline = text_info.deleteline;
			is_change = true;
		}
		if (font_text.outline !== text_info.outline) {
			font_text.outline = text_info.outline;
			is_change = true;
		}
		if (is_change) {
			this.DispatchEvent(___all_struct.get(-256576702), {});
		}
	},
	GetCursorWidth : function(font_size) {
		if (font_size === undefined || font_size < 15) {
			return 1;
		}
		if (font_size > 100) {
			return 10;
		}
		return __floor((font_size / 100) * 10);
	},
	Ctor : function(ctrl_sys) {
		this._char_info_list = [];
		this._char_count = 0;
		this._font_text = ALittle.NewObject(ALittle.Text, this._ctrl_sys);
		this._draw_text = ALittle.NewObject(ALittle.Text, this._ctrl_sys);
		this._char_cursor_it = 1;
		this._char_select_it = 1;
		this._display_view = ALittle.NewObject(ALittle.DisplayView, this._ctrl_sys);
		this._display_view.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
		this._display_view.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
		this._display_view.x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this._display_view.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this.AddChild(this._display_view);
		this._display_show = ALittle.NewObject(ALittle.DisplayLayout, this._ctrl_sys);
		this._display_show.width = 0;
		this._display_show.height = 0;
		this._display_show.x = 0;
		this._display_show.y_type = ALittle.UIEnumTypes.POS_ALIGN_ENDING;
		this._display_show.y_value = 0;
		this._display_view.AddChild(this._display_show);
		this._current_flash_alpha = 1;
		this._current_flash_dir = -0.05;
		this._cursor = ALittle.NewObject(ALittle.Quad, this._ctrl_sys);
		this._cursor.width = 1;
		this.AddChild(this._cursor);
		this._cursor.visible = false;
		this._select = ALittle.NewObject(ALittle.Quad, this._ctrl_sys);
		this.AddChild(this._select);
		this._select.visible = false;
		this._select.alpha = 0.5;
		this._start_cursor = ALittle.NewObject(ALittle.Quad, this._ctrl_sys);
		this._start_cursor.width = 1;
		this.AddChild(this._start_cursor);
		this._start_cursor.visible = false;
		this._end_cursor = ALittle.NewObject(ALittle.Quad, this._ctrl_sys);
		this._end_cursor.width = 1;
		this.AddChild(this._end_cursor);
		this._end_cursor.visible = false;
		this._start_cursor_data = undefined;
		this._end_cursor_data = undefined;
		this._focus_cursor = true;
		this._is_focus = false;
		this._event_start_x = 0;
		this._event_end_x = 0;
		this._event_start_y = 0;
		this._event_end_y = 0;
		this._click_drag_delta_x = 0;
		this._click_drag_delta_y = 0;
		this._is_click = false;
		this._is_longclick = false;
		this._is_click_cursor = false;
		this._is_click_cursor_name = "";
		this._drag_delta_x = 0;
		this._drag_delta_y = 0;
		this._cursor_margin_up = 0;
		this._cursor_margin_down = 0;
		this._margin_halign = 0;
		this._margin_valign = 0;
		this._is_drag_begin = false;
		this._password_mode = false;
		this._ims_padding = 0;
		this._default_text = ALittle.NewObject(ALittle.Text, this._ctrl_sys);
		this._default_text.y_type = ALittle.UIEnumTypes.POS_ALIGN_ENDING;
		this._default_text.y_value = 0;
		this._display_view.AddChild(this._default_text);
		this._default_font_height = 20;
		this._link_map = ALittle.CreateValueWeakMap();
		this._pickup_rect = true;
		this._pickup_child = false;
		this._pickup_this = true;
		this._editable = true;
		this._is_selecting = false;
		this._can_drag_text = true;
		this._auto_ims = true;
		this._multi_cursor = false;
		this._input_align = false;
		this._regex = "";
		this._limit_len = 0;
		this.AddEventListener(___all_struct.get(292776509), this, this.HandleFocusOut);
		this.AddEventListener(___all_struct.get(-644464135), this, this.HandleFocusIn);
		this.AddEventListener(___all_struct.get(544684311), this, this.HandleMoveIn);
		this.AddEventListener(___all_struct.get(-1202439334), this, this.HandleMoveOut);
		this.AddEventListener(___all_struct.get(1883782801), this, this.HandleLButtonDown);
		this.AddEventListener(___all_struct.get(40651933), this, this.HandleLButtonUp);
		this.AddEventListener(___all_struct.get(-1234078962), this, this.HandleTextInput);
		this.AddEventListener(___all_struct.get(-1604617962), this, this.HandleKeyDown);
		this.AddEventListener(___all_struct.get(1301789264), this, this.HandleDragBegin);
		this.AddEventListener(___all_struct.get(1337289812), this, this.HandleDrag);
		this.AddEventListener(___all_struct.get(150587926), this, this.HandleDragEnd);
		this.AddEventListener(___all_struct.get(-439548260), this, this.HandleLongLButtonDown);
		this.ClearCharInfo();
		if (this._loop === undefined) {
			this._loop = ALittle.NewObject(ALittle.LoopFunction, this.Update.bind(this), -1, 1, 1);
		}
		A_LoopSystem.AddUpdater(this._loop);
	},
	GetCursor : function() {
		return this._cursor;
	},
	ClearLinkMap : function() {
		this._link_map = ALittle.CreateValueWeakMap();
	},
	get real_width() {
		return this._char_info_list[this._char_count - 1].acc_width;
	},
	get real_height() {
		return this._display_show.height;
	},
	get can_drag_text() {
		return this._can_drag_text;
	},
	set can_drag_text(value) {
		this._can_drag_text = value;
	},
	set auto_ims(value) {
		this._auto_ims = value;
	},
	get auto_ims() {
		return this._auto_ims;
	},
	get multi_cursor() {
		return this._multi_cursor;
	},
	set width(value) {
		if (this.width === value) {
			return;
		}
		ALittle.DisplayLayout.__setter.width.call(this, value);
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	set height(value) {
		if (this.height === value) {
			return;
		}
		ALittle.DisplayLayout.__setter.height.call(this, value);
		this.ResetCursor();
	},
	set cursor_red(value) {
		this._cursor.red = value;
		this._select.red = value;
	},
	get cursor_red() {
		return this._cursor.red;
	},
	set cursor_green(value) {
		this._cursor.green = value;
		this._select.green = value;
	},
	get cursor_green() {
		return this._cursor.green;
	},
	set cursor_blue(value) {
		this._cursor.blue = value;
		this._select.blue = value;
	},
	get cursor_blue() {
		return this._cursor.blue;
	},
	set font_bold(value) {
		if (this._font_text.bold === value) {
			return;
		}
		this._font_text.bold = value;
		this._default_text.bold = value;
		if (this._char_info_list[1 - 1] !== undefined) {
			this._char_info_list[1 - 1].text_info.bold = value;
		}
	},
	set font_underline(value) {
		if (this._font_text.underline === value) {
			return;
		}
		this._font_text.underline = value;
		this._default_text.underline = value;
		if (this._char_info_list[1 - 1] !== undefined) {
			this._char_info_list[1 - 1].text_info.underline = value;
		}
	},
	set font_deleteline(value) {
		if (this._font_text.deleteline === value) {
			return;
		}
		this._font_text.deleteline = value;
		this._default_text.deleteline = value;
		if (this._char_info_list[1 - 1] !== undefined) {
			this._char_info_list[1 - 1].text_info.deleteline = value;
		}
	},
	set font_italic(value) {
		if (this._font_text.italic === value) {
			return;
		}
		this._font_text.italic = value;
		this._default_text.italic = value;
		if (this._char_info_list[1 - 1] !== undefined) {
			this._char_info_list[1 - 1].text_info.italic = value;
		}
	},
	set font_outline(value) {
		if (this._font_text.outline === value) {
			return;
		}
		this._font_text.outline = value;
		this._default_text.outline = value;
		if (this._char_info_list[1 - 1] !== undefined) {
			this._char_info_list[1 - 1].text_info.outline = value;
		}
	},
	set font_path(value) {
		if (this._font_text.font_path === value) {
			return;
		}
		this._font_text.font_path = value;
		this._default_text.font_path = value;
		if (this._char_info_list[1 - 1] !== undefined) {
			this._char_info_list[1 - 1].text_info.font_path = value;
		}
	},
	set font_size(value) {
		if (this._font_text.font_size === value) {
			return;
		}
		this._font_text.font_size = value;
		this._default_text.font_size = value;
		if (this._char_info_list[1 - 1] !== undefined) {
			this._char_info_list[1 - 1].text_info.font_size = value;
		}
	},
	get font_path() {
		return this._font_text.font_path;
	},
	get font_size() {
		return this._font_text.font_size;
	},
	set font_red(value) {
		if (this._font_text.red === value) {
			return;
		}
		this._font_text.red = value;
		this._default_text.red = value;
		if (this._char_info_list[1 - 1] !== undefined) {
			this._char_info_list[1 - 1].text_info.red = value;
		}
	},
	get font_red() {
		return this._font_text.red;
	},
	set font_green(value) {
		if (this._font_text.green === value) {
			return;
		}
		this._font_text.green = value;
		this._default_text.green = value;
		if (this._char_info_list[1 - 1] !== undefined) {
			this._char_info_list[1 - 1].text_info.green = value;
		}
	},
	get font_green() {
		return this._font_text.green;
	},
	set font_blue(value) {
		if (this._font_text.blue === value) {
			return;
		}
		this._font_text.blue = value;
		this._default_text.blue = value;
		if (this._char_info_list[1 - 1] !== undefined) {
			this._char_info_list[1 - 1].text_info.blue = value;
		}
	},
	get font_blue() {
		return this._font_text.blue;
	},
	set text(value) {
		this.ClearCharInfo();
		this.InsertTextNative(value);
		this.ResetShowXByCursor();
		this.ShowDefaultText();
	},
	get text() {
		let displaylist = this.CharInfoListToDisplayList(this._char_info_list);
		let text = "";
		let ___OBJECT_5 = displaylist;
		for (let k = 1; k <= ___OBJECT_5.length; ++k) {
			let v = ___OBJECT_5[k - 1];
			if (v === undefined) break;
			if (v.__class === "Text") {
				text = text + v.text;
			}
		}
		return text;
	},
	set default_text(value) {
		this._default_text.text = value;
	},
	get default_text() {
		return this._default_text.text;
	},
	set default_text_alpha(value) {
		this._default_text.alpha = value;
	},
	get default_text_alpha() {
		return this._default_text.alpha;
	},
	set display_list(value) {
		let char_info_list = this.DisplayListToCharInfoList(value);
		this.ClearCharInfo();
		this.InsertCharInfo(char_info_list, false);
		this.ResetCursor();
		this.ShowDefaultText();
	},
	get display_list() {
		return this.CharInfoListToDisplayList(this._char_info_list);
	},
	set start_cursor(value) {
		if (value === undefined) {
			return;
		}
		if (value === this._start_cursor) {
			return;
		}
		this.RemoveChild(this._start_cursor);
		value.x_type = ALittle.UIEnumTypes.POS_ABS;
		value.y_type = ALittle.UIEnumTypes.POS_ABS;
		value.width_type = ALittle.UIEnumTypes.SIZE_ABS;
		value.height_type = ALittle.UIEnumTypes.SIZE_ABS;
		this._start_cursor = value;
		this.AddChild(this._start_cursor);
		this._start_cursor.visible = false;
		this.ResetCursor();
	},
	get start_cursor() {
		return this._start_cursor;
	},
	set end_cursor(value) {
		if (value === undefined) {
			return;
		}
		if (value === this._end_cursor) {
			return;
		}
		this.RemoveChild(this._end_cursor);
		value.x_type = ALittle.UIEnumTypes.POS_ABS;
		value.y_type = ALittle.UIEnumTypes.POS_ABS;
		value.width_type = ALittle.UIEnumTypes.SIZE_ABS;
		value.height_type = ALittle.UIEnumTypes.SIZE_ABS;
		this._end_cursor = value;
		this.AddChild(this._end_cursor);
		this._end_cursor.visible = false;
		this.ResetCursor();
	},
	get end_cursor() {
		return this._end_cursor;
	},
	set cursor_margin_up(value) {
		if (value === this._cursor_margin_up) {
			return;
		}
		this._cursor_margin_up = value;
		this.ResetCursor();
	},
	get cursor_margin_up() {
		return this._cursor_margin_up;
	},
	set cursor_margin_down(value) {
		if (value === this._cursor_margin_down) {
			return;
		}
		this._cursor_margin_down = value;
		this.ResetCursor();
	},
	get cursor_margin_down() {
		return this._cursor_margin_down;
	},
	set margin_halign(value) {
		if (value === this._margin_halign) {
			return;
		}
		this._margin_halign = value;
		this._display_view.width_value = this._margin_halign * 2;
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	get margin_halign() {
		return this._margin_halign;
	},
	set margin_valign(value) {
		if (value === this._margin_valign) {
			return;
		}
		this._margin_valign = value;
		this._display_view.height_value = this._margin_valign * 2;
		this.ResetCursor();
	},
	get margin_valign() {
		return this._margin_valign;
	},
	set focus_cursor(value) {
		this._focus_cursor = value;
	},
	get focus_cursor() {
		return this._focus_cursor;
	},
	get cursor_x() {
		return this._cursor.x;
	},
	get cursor_y() {
		return this._cursor.y;
	},
	get start_cursor_x() {
		return this._event_start_x;
	},
	get start_cursor_y() {
		return this._event_start_y;
	},
	get end_cursor_x() {
		return this._event_end_x;
	},
	get end_cursor_y() {
		return this._event_end_y;
	},
	get is_input() {
		return true;
	},
	get is_empty() {
		return this._char_count === 1;
	},
	get editable() {
		return this._editable;
	},
	set editable(value) {
		this._editable = value;
	},
	set ims_padding(value) {
		this._ims_padding = value;
	},
	get ims_padding() {
		return this._ims_padding;
	},
	set password_mode(value) {
		if (this._password_mode === value) {
			return;
		}
		this._password_mode = value;
		let display_list = this.CharInfoListToDisplayList(this._char_info_list);
		let char_info_list = this.DisplayListToCharInfoList(display_list);
		this.ClearCharInfo();
		this.InsertCharInfo(char_info_list, false);
		this.ResetCursor();
		this.ShowDefaultText();
	},
	get password_mode() {
		return this._password_mode;
	},
	get regex() {
		return this._regex;
	},
	set regex(value) {
		if (value === undefined) {
			value = "";
		}
		this._regex = value;
	},
	get limit_len() {
		return this._limit_len;
	},
	set limit_len(value) {
		if (value === undefined) {
			value = 0;
		}
		this._limit_len = value;
	},
	set input_align(value) {
		if (this._input_align === value) {
			return;
		}
		this._input_align = value;
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	get input_align() {
		return this._input_align;
	},
	Update : function() {
		if (this._cursor.abs_visible) {
			this._current_flash_alpha = this._current_flash_alpha + this._current_flash_dir;
			if ((this._current_flash_dir < 0 && this._current_flash_alpha < -0.05) || (this._current_flash_dir > 0 && this._current_flash_alpha > 1.5)) {
				this._current_flash_dir = -this._current_flash_dir;
			}
			this._cursor.alpha = this._current_flash_alpha;
		}
	},
	Draw : function() {
		if (this._draw_loop !== undefined) {
			return;
		}
		this._draw_loop = ALittle.NewObject(ALittle.LoopFunction, this.DrawImpl.bind(this), 1, 0, 1);
		A_LoopSystem.AddUpdater(this._draw_loop);
	},
	DrawImpl : function() {
		this._display_show.RemoveAllChild();
		let real_height = 0.0;
		let offset_x = 0.0;
		let last_child = undefined;
		let ___OBJECT_6 = this._char_info_list;
		for (let k = 1; k <= ___OBJECT_6.length; ++k) {
			let char_info = ___OBJECT_6[k - 1];
			if (char_info === undefined) break;
			let child = char_info.text_object;
			if (child === undefined) {
				child = char_info.ctrl;
			}
			if (child !== undefined && child !== last_child) {
				last_child = child;
				child.x_type = ALittle.UIEnumTypes.POS_ALIGN_STARTING;
				child.x_value = offset_x;
				child.y_type = ALittle.UIEnumTypes.POS_ALIGN_ENDING;
				child.y_value = 0;
				this._display_show.AddChild(child);
				offset_x = offset_x + child.width;
				if (child.height > real_height) {
					real_height = child.height;
				}
			}
		}
		this._display_show.height_value = real_height;
		this._draw_loop = undefined;
	},
	ClearCharInfo : function() {
		this._char_info_list = [];
		this._char_count = 0;
		let char_info = {};
		char_info.acc_width = 0;
		char_info.pre_width = 0;
		char_info.text_info = this.InitTextInfo();
		char_info.text_object = undefined;
		char_info.text = "";
		char_info.password_text = "";
		char_info.ctrl_info = undefined;
		char_info.ctrl = undefined;
		this._char_count = this._char_count + 1;
		this._char_info_list[this._char_count - 1] = char_info;
		this._char_cursor_it = 1;
		this._char_select_it = 2;
		this.Draw();
	},
	InsertCharInfo : function(char_info_list, selected) {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return;
		}
		if (char_info_list[1 - 1] === undefined) {
			return;
		}
		let char_cursor_it_tmp = this._char_cursor_it;
		let x_char_info_list = [];
		let x_char_info_list_count = 0;
		let ___OBJECT_7 = char_info_list;
		for (let index = 1; index <= ___OBJECT_7.length; ++index) {
			let char_info = ___OBJECT_7[index - 1];
			if (char_info === undefined) break;
			if (char_info.ctrl_info === undefined) {
				x_char_info_list_count = this.SplitText(char_info, x_char_info_list, x_char_info_list_count);
			} else {
				++ x_char_info_list_count;
				x_char_info_list[x_char_info_list_count - 1] = char_info;
			}
		}
		char_info_list = x_char_info_list;
		let new_char_info_list = [];
		let new_char_count = 0;
		let text_info = undefined;
		let text_object = undefined;
		let char_acc_width = 0.0;
		for (let i = 1; i <= char_cursor_it_tmp; i += 1) {
			let char_info = this._char_info_list[i - 1];
			if (i !== 1 && char_info.ctrl_info === undefined) {
				text_info = char_info.text_info;
				text_object = char_info.text_object;
			} else {
				text_info = undefined;
				text_object = undefined;
			}
			char_acc_width = char_info.acc_width;
			new_char_count = new_char_count + 1;
			new_char_info_list[new_char_count - 1] = char_info;
		}
		let insert_count = 0;
		let ___OBJECT_8 = char_info_list;
		for (let key = 1; key <= ___OBJECT_8.length; ++key) {
			let display_info = ___OBJECT_8[key - 1];
			if (display_info === undefined) break;
			if (display_info.ctrl_info === undefined) {
				let display_object = undefined;
				if (text_info !== undefined && this.CompareTextInfo(display_info.text_info, text_info)) {
					display_object = text_object;
				} else {
					text_info = display_info.text_info;
					let name = "nkacbjbsakcvuqocbakcbjcbvjhciqwojqppwvnwe";
					this._ctrl_sys.RegisterInfo(name, ALittle.String_CopyTable(display_info.text_info));
					text_object = this._ctrl_sys.CreateControl(name, this._link_map);
					this._ctrl_sys.UnRegisterInfo(name);
					display_object = text_object;
				}
				this.SetDrawText(display_object);
				let object_text = "";
				let calc_text = display_info.text;
				let password_width = undefined;
				while (calc_text !== "") {
					let byte_count = ALittle.String_GetByteCount(calc_text, 1);
					let real_text = __sub(calc_text, 1, byte_count);
					let password_text = "*";
					let text_width = 0.0;
					calc_text = __sub(calc_text, byte_count + 1);
					if (this._password_mode) {
						if (password_width === undefined) {
							password_width = this._draw_text.native_show.CalcTextWidth(password_text);
						}
						text_width = password_width;
					} else {
						password_text = real_text;
						text_width = this._draw_text.native_show.CalcTextWidth(real_text);
					}
					let char_info = {};
					char_info.pre_width = char_acc_width;
					char_info.acc_width = char_info.pre_width + text_width;
					char_info.text_info = display_info.text_info;
					char_info.text_object = display_object;
					char_info.text = real_text;
					char_info.password_text = password_text;
					char_info.ctrl_info = undefined;
					char_info.ctrl = undefined;
					object_text = object_text + char_info.password_text;
					char_acc_width = char_info.acc_width;
					new_char_count = new_char_count + 1;
					new_char_info_list[new_char_count - 1] = char_info;
					insert_count = insert_count + 1;
				}
			} else if (display_info.ctrl_info !== undefined) {
				text_info = undefined;
				text_object = undefined;
				let name = "nkacbjbsakcvuqocbakcbjcbvjhciqwojqppwvnwe";
				this._ctrl_sys.RegisterInfo(name, ALittle.String_CopyTable(display_info.ctrl_info));
				let display_object = this._ctrl_sys.CreateControl(name, this._link_map);
				this._ctrl_sys.UnRegisterInfo(name);
				let char_info = {};
				char_info.pre_width = char_acc_width;
				char_info.acc_width = char_info.pre_width + display_object.width;
				char_info.text_info = display_info.text_info;
				char_info.text_object = undefined;
				char_info.text = undefined;
				char_info.password_text = undefined;
				char_info.ctrl_info = display_info.ctrl_info;
				char_info.ctrl = display_object;
				char_acc_width = char_info.acc_width;
				new_char_count = new_char_count + 1;
				new_char_info_list[new_char_count - 1] = char_info;
				insert_count = insert_count + 1;
			}
		}
		for (let i = char_cursor_it_tmp + 1; i <= this._char_count; i += 1) {
			let char_info = this._char_info_list[i - 1];
			if (char_info.ctrl_info === undefined && text_info !== undefined && this.CompareTextInfo(char_info.text_info, text_info)) {
				char_info.text_object = text_object;
			} else {
				text_info = undefined;
				text_object = undefined;
			}
			let width = char_info.acc_width - char_info.pre_width;
			char_info.pre_width = char_acc_width;
			char_info.acc_width = char_info.pre_width + width;
			char_acc_width = char_info.acc_width;
			new_char_count = new_char_count + 1;
			new_char_info_list[new_char_count - 1] = char_info;
		}
		let text = "";
		let object = undefined;
		let ___OBJECT_9 = new_char_info_list;
		for (let i = 1; i <= ___OBJECT_9.length; ++i) {
			let char_info = ___OBJECT_9[i - 1];
			if (char_info === undefined) break;
			if (object === undefined) {
				if (char_info.text_object !== undefined) {
					object = char_info.text_object;
					text = char_info.password_text;
				}
			} else {
				if (char_info.text_object === undefined) {
					object.text = text;
					object = undefined;
					text = "";
				} else if (char_info.text_object !== object) {
					object.text = text;
					object = char_info.text_object;
					text = char_info.password_text;
				} else {
					text = text + char_info.password_text;
				}
			}
		}
		if (object !== undefined) {
			object.text = text;
		}
		this._char_info_list = new_char_info_list;
		this._char_count = new_char_count;
		this._char_cursor_it = char_cursor_it_tmp + insert_count;
		if (selected) {
			this._char_select_it = char_cursor_it_tmp;
		} else {
			this._char_select_it = this._char_count + 1;
		}
		this.Draw();
	},
	DeleteCharInfo : function(begin_char_it, end_char_it) {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return;
		}
		let new_char_info_list = [];
		let new_char_count = 0;
		let text_info = undefined;
		let text_object = undefined;
		let char_acc_width = 0.0;
		for (let i = 1; i <= begin_char_it; i += 1) {
			let char_info = this._char_info_list[i - 1];
			if (i !== 1 && char_info.ctrl_info === undefined) {
				text_info = char_info.text_info;
				text_object = char_info.text_object;
			}
			char_acc_width = char_info.acc_width;
			new_char_count = new_char_count + 1;
			new_char_info_list[new_char_count - 1] = char_info;
		}
		for (let i = end_char_it + 1; i <= this._char_count; i += 1) {
			let char_info = this._char_info_list[i - 1];
			if (char_info.ctrl_info === undefined && text_info !== undefined && this.CompareTextInfo(char_info.text_info, text_info)) {
				char_info.text_object = text_object;
			} else {
				text_info = undefined;
				text_object = undefined;
			}
			let width = char_info.acc_width - char_info.pre_width;
			char_info.pre_width = char_acc_width;
			char_info.acc_width = char_info.pre_width + width;
			char_acc_width = char_info.acc_width;
			new_char_count = new_char_count + 1;
			new_char_info_list[new_char_count - 1] = char_info;
		}
		let text = "";
		let object = undefined;
		let ___OBJECT_10 = new_char_info_list;
		for (let i = 1; i <= ___OBJECT_10.length; ++i) {
			let char_info = ___OBJECT_10[i - 1];
			if (char_info === undefined) break;
			if (object === undefined) {
				if (char_info.text_object !== undefined) {
					object = char_info.text_object;
					text = char_info.password_text;
				}
			} else {
				if (char_info.text_object === undefined) {
					object.text = text;
					object = undefined;
					text = "";
				} else if (char_info.text_object !== object) {
					object.text = text;
					object = char_info.text_object;
					text = char_info.password_text;
				} else {
					text = text + char_info.password_text;
				}
			}
		}
		if (object !== undefined) {
			object.text = text;
		}
		this._char_info_list = new_char_info_list;
		this._char_count = new_char_count;
		this._char_cursor_it = begin_char_it;
		this._char_select_it = this._char_count + 1;
		this.Draw();
	},
	GetIteratorByOffset : function(offset_x) {
		let real_offset_x = offset_x - this._display_show.x;
		if (real_offset_x < 0) {
			return 1;
		}
		let char_it = 1;
		let char_end_it = this._char_count + 1;
		while (char_it !== char_end_it) {
			let char_info = this._char_info_list[char_it - 1];
			if (real_offset_x <= char_info.acc_width) {
				let half_char_width = (char_info.acc_width - char_info.pre_width) * 0.5;
				if (real_offset_x - char_info.pre_width < half_char_width && char_it !== 1) {
					char_it = char_it - 1;
				}
				break;
			} else {
				char_it = char_it + 1;
			}
		}
		if (char_it === char_end_it) {
			char_end_it = char_end_it - 1;
			char_it = char_end_it;
		}
		return char_it;
	},
	ClickCursorToHome : function() {
		this._char_select_it = this._char_count + 1;
		this._char_cursor_it = 1;
		this.UpdateFontText();
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	ClickCursorToEnd : function() {
		this._char_select_it = this._char_count + 1;
		this._char_cursor_it = this._char_count;
		this.UpdateFontText();
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	ClickCursor : function(offset_x) {
		this._char_select_it = this._char_count + 1;
		this._char_cursor_it = this.GetIteratorByOffset(offset_x);
		this.UpdateFontText();
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	ClickMultiCursor : function(offset_x, trans) {
		let char_cursor_it = undefined;
		if (trans) {
			char_cursor_it = this._char_cursor_it;
		} else {
			char_cursor_it = this.GetIteratorByOffset(offset_x);
		}
		if (char_cursor_it !== 1) {
			this._char_cursor_it = char_cursor_it;
			this._char_select_it = char_cursor_it - 1;
		} else {
			if (this._char_count !== 1) {
				this._char_cursor_it = char_cursor_it + 1;
				this._char_select_it = char_cursor_it;
			} else {
				this._char_cursor_it = 1;
				this._char_select_it = 2;
			}
		}
		this.UpdateFontText();
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	ClickWordCursor : function(offset_x) {
		this._char_cursor_it = this.GetIteratorByOffset(offset_x);
		this._char_select_it = this._char_cursor_it;
		while (true) {
			let str = this._char_info_list[this._char_select_it - 1].password_text;
			if (str !== undefined && __len(str) === 1 && str !== "_" && this.CharIsNumber(str) === false && this.CharIsLetter(str) === false) {
				break;
			}
			if (this._char_select_it === 1) {
				break;
			}
			this._char_select_it = this._char_select_it - 1;
		}
		while (true) {
			let str = this._char_info_list[this._char_cursor_it - 1].password_text;
			if (str !== undefined && __len(str) === 1 && str !== "_" && this.CharIsNumber(str) === false && this.CharIsLetter(str) === false) {
				this._char_cursor_it = this._char_cursor_it - 1;
				break;
			}
			if (this._char_cursor_it === this._char_count) {
				break;
			}
			this._char_cursor_it = this._char_cursor_it + 1;
		}
		if (this._char_select_it < 1) {
			this._char_select_it = this._char_count + 1;
		}
		this.UpdateFontText();
		this.ResetShowXByCursor();
		this.ResetCursor();
		return this._char_select_it <= this._char_count;
	},
	SelectAll : function() {
		this._char_select_it = 1;
		this._char_cursor_it = this._char_count;
		this.UpdateFontText();
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	CursorOffsetLR : function(left) {
		if (this._char_select_it <= this._char_count && this._char_select_it !== this._char_cursor_it) {
			if (this._char_cursor_it > this._char_select_it && left) {
				this._char_cursor_it = this._char_select_it;
			} else if (this._char_cursor_it < this._char_select_it && !left) {
				this._char_cursor_it = this._char_select_it;
			}
			this._char_select_it = this._char_count + 1;
			return;
		}
		if (left) {
			if (this._char_cursor_it === 1) {
				return;
			}
			this._char_cursor_it = this._char_cursor_it - 1;
		} else {
			if (this._char_cursor_it === this._char_count) {
				return;
			}
			this._char_cursor_it = this._char_cursor_it + 1;
		}
		this.UpdateFontText();
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	SelectCursorOffsetLR : function(left) {
		if (this._char_select_it > this._char_count) {
			this._char_select_it = this._char_cursor_it;
		}
		if (left) {
			if (this._char_cursor_it === 1) {
				return;
			}
			this._char_cursor_it = this._char_cursor_it - 1;
		} else {
			if (this._char_cursor_it === this._char_count) {
				return;
			}
			this._char_cursor_it = this._char_cursor_it + 1;
		}
		this.UpdateFontText();
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	DragCursorBegin : function() {
		this._char_select_it = this._char_cursor_it;
	},
	DragCursor : function(offset_x) {
		this._char_cursor_it = this.GetIteratorByOffset(offset_x);
		if (this._char_info_list[this._char_cursor_it - 1].pre_width === -this._display_show.x && this._char_cursor_it !== 1 && offset_x < 0) {
			this._char_cursor_it = this._char_cursor_it - 1;
		}
		if (this._char_info_list[this._char_cursor_it - 1].acc_width === this._display_view.width - this._display_show.x && this._char_cursor_it !== this._char_count && offset_x > this._display_view.width) {
			this._char_cursor_it = this._char_cursor_it - 1;
		}
		this.UpdateFontText();
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	DragMultiCursor : function(offset_x) {
		offset_x = offset_x + this._drag_delta_x;
		this._char_cursor_it = this.GetIteratorByOffset(offset_x);
		if (this._char_info_list[this._char_cursor_it - 1].pre_width === -this._display_show.x && this._char_cursor_it !== 1 && offset_x < 0) {
			this._char_cursor_it = this._char_cursor_it - 1;
		}
		if (this._char_info_list[this._char_cursor_it - 1].acc_width === this._display_view.width - this._display_show.x && this._char_cursor_it !== this._char_count && offset_x > this._display_view.width) {
			this._char_cursor_it = this._char_cursor_it - 1;
		}
		this.UpdateFontText();
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	DragInput : function(delta_x) {
		let display_show_x = this._display_show.x + delta_x;
		let display_show_width = this._char_info_list[this._char_count - 1].acc_width;
		if (this._display_show.width < this._display_view.width || display_show_x > 0) {
			display_show_x = 0;
		} else if (display_show_x < this._display_view.width - display_show_width) {
			display_show_x = this._display_view.width - display_show_width;
		}
		this._display_show.x = display_show_x;
		this.ResetCursor();
	},
	ResetShowXByCursor : function() {
		let char_info = this._char_info_list[this._char_cursor_it - 1];
		let next_char_info = this._char_info_list[this._char_cursor_it + 1 - 1];
		let max_char_info = this._char_info_list[this._char_count - 1];
		if (next_char_info === undefined) {
			next_char_info = char_info;
		}
		let display_show_x = 0.0;
		if (char_info.pre_width < -this._display_show.x) {
			this._display_show.x = -char_info.pre_width;
		} else if (next_char_info.acc_width > this._display_view.width - this._display_show.x) {
			this._display_show.x = this._display_view.width - next_char_info.acc_width;
		} else if (max_char_info.acc_width + this._display_show.x < this._display_view.width && this._display_show.x < 0) {
			let display_x = this._display_view.width - max_char_info.acc_width;
			if (display_x > 0) {
				display_x = 0;
			}
			this._display_show.x = display_x;
		} else if (this._input_align && max_char_info.acc_width < this._display_view.width) {
			this._display_show.x = this._display_view.width - max_char_info.acc_width;
		}
	},
	ResetCursor : function() {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return;
		}
		let max_height = this._display_show.height;
		if (max_height > this._display_view.height) {
			max_height = this._display_view.height;
		}
		if (this._char_select_it > this._char_count || this._char_select_it === this._char_cursor_it) {
			this._select.visible = false;
			this._start_cursor.visible = false;
			this._end_cursor.visible = false;
			this._start_cursor_data = undefined;
			this._end_cursor_data = undefined;
			this._event_start_x = 0;
			this._event_end_x = 0;
			this._event_start_y = 0;
			this._event_end_y = 0;
			if (this._focus_cursor) {
				this._cursor.visible = this._is_focus;
			} else {
				this._cursor.visible = true;
			}
			let cursor_x = this._display_view.x + this._char_info_list[this._char_cursor_it - 1].acc_width + this._display_show.x;
			if (cursor_x < this._display_view.x || cursor_x > this._display_view.x + this._display_view.width) {
				this._cursor.visible = false;
			}
			let cursor_height = 0.0;
			let cursor_width = 0.0;
			let char = this._char_info_list[this._char_cursor_it - 1];
			if (char.ctrl !== undefined) {
				cursor_height = char.ctrl.height;
				cursor_width = 2;
			} else {
				if (char.text_object !== undefined) {
					cursor_height = char.text_object.height;
					cursor_width = this.GetCursorWidth(char.text_object.font_size);
				} else {
					let next_char = this._char_info_list[this._char_cursor_it + 1 - 1];
					if (next_char !== undefined) {
						if (next_char.ctrl !== undefined) {
							cursor_height = next_char.ctrl.height;
							cursor_width = 2;
						} else if (next_char.text_object !== undefined) {
							cursor_height = next_char.text_object.height;
							cursor_width = this.GetCursorWidth(next_char.text_object.font_size);
						} else {
							cursor_height = this._font_text.native_show.GetFontHeight();
							cursor_width = this.GetCursorWidth(this._font_text.font_size);
						}
					} else {
						cursor_height = this._font_text.native_show.GetFontHeight();
						cursor_width = this.GetCursorWidth(this._font_text.font_size);
					}
				}
			}
			if (cursor_height > max_height) {
				cursor_height = max_height;
			}
			if (cursor_height === 0) {
				cursor_height = this._default_text.font_height;
				if (cursor_height === 0) {
					cursor_height = this._default_font_height;
				}
			}
			this._cursor.width = cursor_width;
			this._cursor.height = cursor_height;
			this._cursor.x = cursor_x;
			this._cursor.y = this._margin_valign + (this._display_view.height - cursor_height);
			return;
		}
		if (this._multi_cursor === false) {
			this._cursor.visible = false;
		}
		this._select.visible = true;
		let select_x = this._display_view.x + this._char_info_list[this._char_select_it - 1].acc_width + this._display_show.x;
		let cursor_x = this._display_view.x + this._char_info_list[this._char_cursor_it - 1].acc_width + this._display_show.x;
		if (this._char_cursor_it > this._char_select_it) {
			if (cursor_x < this._display_view.x) {
				this._select.visible = false;
			}
			if (select_x > this._display_view.x + this._display_view.width) {
				this._select.visible = false;
			}
			let select_x_1 = select_x;
			let cursor_x_1 = cursor_x;
			if (select_x_1 < this._display_view.x) {
				select_x_1 = this._display_view.x;
			}
			if (cursor_x_1 > this._display_view.x + this._display_view.width) {
				cursor_x_1 = this._display_view.x + this._display_view.width;
			}
			this._select.y = this._margin_valign + (this._display_view.height - max_height);
			this._select.height = max_height;
			this._select.x = select_x_1;
			this._select.width = cursor_x_1 - select_x_1;
			if (this._multi_cursor === true) {
				this._cursor.visible = false;
				if (select_x < this._display_view.x || select_x > this._display_view.x + this._display_view.width) {
					this._start_cursor.visible = false;
				} else {
					this._start_cursor.visible = true;
					this._start_cursor.x = select_x - this._start_cursor.width;
					this._start_cursor.height = this._select.height + this._cursor_margin_up + this._cursor_margin_down;
					this._start_cursor.y = this._select.y - this._cursor_margin_up;
				}
				if (cursor_x > this._display_view.x + this._display_view.width || cursor_x < this._display_view.x) {
					this._end_cursor.visible = false;
				} else {
					this._end_cursor.visible = true;
					this._end_cursor.x = cursor_x;
					this._end_cursor.height = this._select.height + this._cursor_margin_up + this._cursor_margin_down;
					this._end_cursor.y = this._select.y - this._cursor_margin_up;
				}
				this._start_cursor_data = "select";
				this._end_cursor_data = "cursor";
				this._event_start_x = this._select.x;
				this._event_start_y = this._select.y;
				this._event_end_x = this._select.x + this._select.width;
				this._event_end_y = this._select.y;
			}
		} else if (this._char_cursor_it < this._char_select_it) {
			if (select_x < this._display_view.x) {
				this._select.visible = false;
			}
			if (cursor_x > this._display_view.x + this._display_view.width) {
				this._select.visible = false;
			}
			let select_x_1 = select_x;
			let cursor_x_1 = cursor_x;
			if (cursor_x_1 < this._display_view.x) {
				cursor_x_1 = this._display_view.x;
			}
			if (select_x_1 > this._display_view.x + this._display_view.width) {
				select_x_1 = this._display_view.x + this._display_view.width;
			}
			this._select.y = this._margin_valign + (this._display_view.height - max_height);
			this._select.height = max_height;
			this._select.x = cursor_x_1;
			this._select.width = select_x_1 - cursor_x_1;
			if (this._multi_cursor === true) {
				this._cursor.visible = false;
				if (cursor_x < this._display_view.x || cursor_x > this._display_view.x + this._display_view.width) {
					this._start_cursor.visible = false;
				} else {
					this._start_cursor.visible = true;
					this._start_cursor.x = cursor_x - this._start_cursor.width;
					this._start_cursor.height = this._select.height + this._cursor_margin_up + this._cursor_margin_down;
					this._start_cursor.y = this._select.y - this._cursor_margin_up;
				}
				if (select_x > this._display_view.x + this._display_view.width || select_x < this._display_view.x) {
					this._end_cursor.visible = false;
				} else {
					this._end_cursor.visible = true;
					this._end_cursor.x = select_x;
					this._end_cursor.height = this._select.height + this._cursor_margin_up + this._cursor_margin_down;
					this._end_cursor.y = this._select.y - this._cursor_margin_up;
				}
				this._start_cursor_data = "cursor";
				this._end_cursor_data = "select";
				this._event_start_x = this._select.x;
				this._event_start_y = this._select.y;
				this._event_end_x = this._select.x + this._select.width;
				this._event_end_y = this._select.y;
			}
		}
	},
	ShowDefaultText : function() {
		if (this._is_focus === false) {
			if (this._focus_cursor && this.is_empty) {
				this._default_text.visible = true;
			} else {
				this._default_text.visible = false;
			}
		} else {
			this._default_text.visible = false;
		}
	},
	DeleteSelectText : function() {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return false;
		}
		if (this._char_select_it > this._char_count) {
			return false;
		}
		if (this._char_select_it === this._char_cursor_it) {
			return false;
		}
		let begin_char_it = undefined;
		let end_char_it = undefined;
		if (this._char_select_it > this._char_cursor_it) {
			begin_char_it = this._char_cursor_it;
			end_char_it = this._char_select_it;
		} else {
			end_char_it = this._char_cursor_it;
			begin_char_it = this._char_select_it;
		}
		this.DeleteCharInfo(begin_char_it, end_char_it);
		this.ResetCursor();
		return true;
	},
	CheckDisplayListRegexLimit : function(display_list) {
		if (this._regex === "") {
			return false;
		}
		let text = "";
		let ___OBJECT_11 = display_list;
		for (let k = 1; k <= ___OBJECT_11.length; ++k) {
			let v = ___OBJECT_11[k - 1];
			if (v === undefined) break;
			if (v.__class !== "Text") {
				return false;
			}
			text = text + v.text;
		}
		return this.CheckTextRegexLimit(text);
	},
	InsertDisplayListNative : function(display_list, selected) {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return false;
		}
		if (this.CheckDisplayListRegexLimit(display_list) === false) {
			return false;
		}
		this.DeleteSelectText();
		let char_info = this._char_info_list[this._char_cursor_it - 1];
		let char_info_list = this.DisplayListToCharInfoList(display_list, char_info.text_info);
		this.InsertCharInfo(char_info_list, selected);
		return true;
	},
	CheckTextRegexLimit : function(text) {
		if (this._limit_len > 0) {
			let text_len = ALittle.String_GetWordCount(text);
			if (text_len > this._limit_len) {
				return false;
			}
			let select_len = 0;
			let displaylist = this.GetSelectText();
			let ___OBJECT_12 = displaylist;
			for (let k = 1; k <= ___OBJECT_12.length; ++k) {
				let v = ___OBJECT_12[k - 1];
				if (v === undefined) break;
				if (v.__class === "Text") {
					select_len = select_len + ALittle.String_GetWordCount(v.text);
				}
			}
			displaylist = this.display_list;
			let total_len = 0;
			let ___OBJECT_13 = displaylist;
			for (let k = 1; k <= ___OBJECT_13.length; ++k) {
				let v = ___OBJECT_13[k - 1];
				if (v === undefined) break;
				if (v.__class === "Text") {
					total_len = total_len + ALittle.String_GetWordCount(v.text);
				}
			}
			if (total_len - select_len + text_len > this._limit_len) {
				return false;
			}
		}
		if (this._regex !== "") {
			while (text !== "") {
				let byte_count = ALittle.String_GetByteCount(text, 1);
				let sub_text = __sub(text, 1, byte_count);
				let start_it = __find(sub_text, this._regex);
				if (start_it === undefined) {
					return false;
				}
				text = __sub(text, byte_count + 1);
			}
		}
		return true;
	},
	InsertTextNative : function(text) {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return false;
		}
		if (this.CheckTextRegexLimit(text) === false) {
			return false;
		}
		this.DeleteSelectText();
		let char_info_list = [];
		let new_char_info = {};
		new_char_info.acc_width = 0;
		new_char_info.pre_width = 0;
		new_char_info.text_info = this.InitTextInfo();
		new_char_info.text_object = undefined;
		new_char_info.text = text;
		new_char_info.ctrl_info = undefined;
		new_char_info.ctrl = undefined;
		char_info_list[1 - 1] = new_char_info;
		this.InsertCharInfo(char_info_list, false);
		return true;
	},
	GetSelectText : function() {
		let select_text = [];
		let select_text_count = 0;
		if (this._char_select_it > this._char_count) {
			return [];
		}
		if (this._char_select_it === this._char_cursor_it) {
			return [];
		}
		let char_it = undefined;
		let char_end = undefined;
		if (this._char_select_it > this._char_cursor_it) {
			char_it = this._char_cursor_it + 1;
			char_end = this._char_select_it;
		} else {
			char_end = this._char_cursor_it;
			char_it = this._char_select_it + 1;
		}
		while (char_it <= char_end) {
			++ select_text_count;
			select_text[select_text_count - 1] = this._char_info_list[char_it - 1];
			char_it = char_it + 1;
		}
		return this.CharInfoListToDisplayList(select_text);
	},
	GetSelectWord : function() {
		let select_text = [];
		let select_text_count = 0;
		if (this._char_select_it > this._char_count) {
			return "";
		}
		if (this._char_select_it === this._char_cursor_it) {
			return "";
		}
		let char_it = undefined;
		let char_end = undefined;
		if (this._char_select_it > this._char_cursor_it) {
			char_it = this._char_cursor_it + 1;
			char_end = this._char_select_it;
		} else {
			char_end = this._char_cursor_it;
			char_it = this._char_select_it + 1;
		}
		while (char_it <= char_end) {
			++ select_text_count;
			select_text[select_text_count - 1] = this._char_info_list[char_it - 1];
			char_it = char_it + 1;
		}
		return this.CharInfoListToWord(select_text);
	},
	DeleteText : function(left) {
		if (this._font_text.font_path === undefined || this._font_text.font_size === undefined) {
			return false;
		}
		if (this.DeleteSelectText()) {
			return true;
		}
		if (left) {
			if (this._char_cursor_it === 1) {
				return false;
			}
			let end_it = this._char_cursor_it;
			let begin_it = this._char_cursor_it - 1;
			this.DeleteCharInfo(begin_it, end_it);
		} else {
			if (this._char_cursor_it === this._char_count) {
				return false;
			}
			let begin_it = this._char_cursor_it;
			let end_it = this._char_cursor_it + 1;
			this.DeleteCharInfo(begin_it, end_it);
		}
		return true;
	},
	SetCursor : function(rel_x, rel_y) {
		if (this._auto_ims) {
			this.OpenIME();
		}
		this._is_selecting = false;
		if (this._multi_cursor) {
			this._multi_cursor = false;
			this._start_cursor.visible = false;
			this._end_cursor.visible = false;
			this._cursor.visible = true;
			this.ClickCursor(rel_x - this._display_view.x);
		} else {
			this.ClickCursor(rel_x - this._display_view.x);
		}
	},
	SetMultiCursor : function(rel_x, rel_y) {
		if (this._auto_ims) {
			this.OpenIME();
		}
		this._is_selecting = true;
		if (this._multi_cursor === false) {
			this._multi_cursor = true;
			this._cursor.visible = false;
			this._start_cursor.visible = true;
			this._end_cursor.visible = true;
			this.ClickMultiCursor(rel_x - this._display_view.x, false);
		} else {
			this.ClickMultiCursor(rel_x - this._display_view.x, false);
		}
	},
	TransToCursor : function() {
		if (this._end_cursor_data === "select") {
			this._char_cursor_it = this._char_select_it;
		}
		this._char_select_it = this._char_count + 1;
		this._is_selecting = false;
		this._multi_cursor = false;
		this._start_cursor.visible = false;
		this._end_cursor.visible = false;
		this._cursor.visible = true;
		this.UpdateFontText();
		this.ResetShowXByCursor();
		this.ResetCursor();
	},
	TransToMulti : function() {
		if (this._multi_cursor) {
			return;
		}
		this._is_selecting = true;
		this._multi_cursor = true;
		this._cursor.visible = false;
		this._start_cursor.visible = true;
		this._end_cursor.visible = true;
		this.ClickMultiCursor(undefined, true);
	},
	OpenIME : function(x, y, width, height) {
		if (this._editable) {
			if (x !== undefined && y !== undefined && width !== undefined && height !== undefined) {
				ALittle.System_SetIMERect(__floor(x), __floor(y), __floor(width), __floor(height));
			} else {
				let [global_x, global_y] = this.LocalToGlobal();
				global_x = global_x + this.cursor_x;
				global_y = global_y + (this.cursor_y + this.font_size) * this.scale_y;
				ALittle.System_SetIMERect(__floor(global_x), __floor(global_y), 10, __floor(5 + this._ims_padding));
			}
			ALittle.System_OpenIME();
			this.ResetCursor();
		}
	},
	CloseIME : function() {
		ALittle.System_CloseIME();
	},
	InsertText : function(display_list, selected) {
		if (this._editable === false) {
			return;
		}
		if (this._multi_cursor && this._is_selecting === false) {
			return;
		}
		this.InsertDisplayListNative(display_list, selected);
		this._is_selecting = false;
		this._multi_cursor = false;
		this.UpdateFontText();
		this.ResetShowXByCursor();
		this.ResetCursor();
		this.ShowDefaultText();
	},
	InsertWord : function(word_text) {
		if (this._editable === false) {
			return;
		}
		if (this._multi_cursor && this._is_selecting === false) {
			return;
		}
		this.InsertTextNative(word_text);
		this._is_selecting = false;
		this.TransToCursor();
		this.ShowDefaultText();
	},
	CopyText : function(return_cursor) {
		if (this._password_mode) {
			return;
		}
		let select_text = this.GetSelectText();
		if (select_text[1 - 1] !== undefined) {
			ALittle.System_SetClipboardText(lua.json.encode(select_text));
		}
		if (return_cursor) {
			this.TransToCursor();
		}
		this.ShowDefaultText();
	},
	CopyWord : function(return_cursor) {
		if (this._password_mode) {
			return;
		}
		let select_text = this.GetSelectWord();
		if (select_text !== undefined) {
			ALittle.System_SetClipboardText(select_text);
		}
		if (return_cursor) {
			this.TransToCursor();
		}
		this.ShowDefaultText();
	},
	CutText : function() {
		if (this._password_mode) {
			return;
		}
		if (this._editable === false) {
			return;
		}
		if (this._multi_cursor && this._is_selecting === false) {
			return;
		}
		this._is_selecting = false;
		let select_text = this.GetSelectText();
		if (select_text[1 - 1] !== undefined) {
			ALittle.System_SetClipboardText(lua.json.encode(select_text));
			this.DeleteSelectText();
			this.TransToCursor();
		}
		this.ShowDefaultText();
	},
	CutWord : function() {
		if (this._password_mode) {
			return;
		}
		if (this._editable === false) {
			return;
		}
		if (this._multi_cursor && this._is_selecting === false) {
			return;
		}
		this._is_selecting = false;
		let select_text = this.GetSelectWord();
		if (select_text !== undefined) {
			ALittle.System_SetClipboardText(select_text);
			this.DeleteSelectText();
			this.TransToCursor();
		}
		this.ShowDefaultText();
	},
	PasteText : function() {
		if (this._editable === false) {
			return;
		}
		if (this._multi_cursor && this._is_selecting === false) {
			return;
		}
		this._is_selecting = false;
		if (ALittle.System_HasClipboardText()) {
			let content = ALittle.System_GetClipboardText();
			let [error, new_content] = (function() { try { let ___VALUE = lua.json.decode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
			if (error === undefined && __type(new_content) === "table" && this.CheckDisplayList(new_content)) {
				if (this.CheckAtKeyInput(new_content)) {
					return;
				}
				this.InsertDisplayListNative(new_content, false);
			} else {
				if (this.CheckAtKeyInput(content)) {
					return;
				}
				this.InsertTextNative(content);
			}
			this.TransToCursor();
		}
		this.ShowDefaultText();
	},
	PasteWord : function() {
		if (this._editable === false) {
			return;
		}
		if (this._multi_cursor && this._is_selecting === false) {
			return;
		}
		this._is_selecting = false;
		if (ALittle.System_HasClipboardText()) {
			let content = ALittle.System_GetClipboardText();
			this.InsertTextNative(content);
			this.TransToCursor();
		}
		this.ShowDefaultText();
	},
	Clear : function() {
		this.ClearCharInfo();
		this.ShowDefaultText();
	},
	Delete : function() {
		if (this._editable === false) {
			return;
		}
		if (this._multi_cursor && this._is_selecting === false) {
			return;
		}
		this._is_selecting = false;
		this.DeleteText(true);
		this.TransToCursor();
		this.ShowDefaultText();
	},
	GetWord : function() {
		return this.CharInfoListToWord(this._char_info_list);
	},
	HandleFocusOut : function(event) {
		if (this._auto_ims) {
			ALittle.System_CloseIME();
		}
		this._is_focus = false;
		if (this._focus_cursor) {
			if (this._multi_cursor === false) {
				this._cursor.visible = false;
			}
		}
		this.ShowDefaultText();
	},
	HandleFocusIn : function(event) {
		if (this._auto_ims) {
			this.OpenIME();
		}
		this._is_focus = true;
		this.ResetShowXByCursor();
		this.ResetCursor();
		this.ShowDefaultText();
	},
	HandleMoveIn : function(event) {
		ALittle.System_SetEditCursor();
	},
	HandleMoveOut : function(event) {
		ALittle.System_SetNormalCursor();
	},
	HandleLButtonDown : function(event) {
		if (this._multi_cursor === false) {
			this._is_longclick = false;
			if (event.rel_x > this._display_view.x && event.rel_x <= this._display_view.x + this._display_view.width && event.rel_y >= this._display_view.y && event.rel_y <= this._display_view.y + this._display_view.height) {
				if (event.count % 3 === 1) {
					this._is_selecting = false;
					this.ClickCursor(event.rel_x - this._display_view.x);
					this.DispatchEvent(___all_struct.get(-683607428), {});
				} else if (event.count % 3 === 2) {
					this._is_selecting = this.ClickWordCursor(event.rel_x - this._display_view.x);
				} else {
					this._is_selecting = true;
					this.SelectAll();
				}
				this._is_click = true;
			} else {
				this._is_click = false;
			}
		} else {
			this._click_drag_delta_x = 0;
			this._click_drag_delta_y = 0;
			this._is_click = false;
			this._is_click_cursor = false;
			this._is_click_cursor_name = "";
			this._is_longclick = false;
			if (this._start_cursor.visible && event.rel_x >= this._start_cursor.x && event.rel_x <= this._start_cursor.x + this._start_cursor.width && event.rel_y >= this._start_cursor.y && event.rel_y <= this._start_cursor.y + this._start_cursor.height) {
				this._is_click_cursor = true;
				this._is_click_cursor_name = "start";
			} else if (this._end_cursor.visible && event.rel_x >= this._end_cursor.x && event.rel_x <= this._end_cursor.x + this._end_cursor.width && event.rel_y >= this._end_cursor.y && event.rel_y <= this._end_cursor.y + this._end_cursor.height) {
				this._is_click_cursor = true;
				this._is_click_cursor_name = "end";
			} else {
				if (event.rel_x >= this._display_view.x && event.rel_x <= this._display_view.x + this._display_view.width && event.rel_y >= this._display_view.y && event.rel_y <= this._display_view.y + this._display_view.height) {
					this._is_click = true;
				}
			}
		}
	},
	HandleLButtonUp : function(event) {
		if (this._multi_cursor === true) {
			if (this._is_click && this._is_longclick === false && this._click_drag_delta_x < 2 && this._click_drag_delta_y < 2) {
				this._multi_cursor = false;
				this._start_cursor.visible = false;
				this._end_cursor.visible = false;
				this._cursor.visible = true;
				this.ClickCursor(event.rel_x - this._display_view.x);
				this.DispatchEvent(___all_struct.get(-683607428), {});
			}
		}
	},
	CheckAtKeyInput : function(input_text) {
		if (input_text !== "@") {
			return false;
		}
		let char_cursor_it = this._char_cursor_it;
		if (this._char_cursor_it === 1) {
			this.DispatchEvent(___all_struct.get(1816229739), {});
			return true;
		}
		let char_info = this._char_info_list[this._char_cursor_it - 1];
		let forward_text = char_info.text;
		if (!(this.CharIsNumber(forward_text) || this.CharIsLetter(forward_text))) {
			this.DispatchEvent(___all_struct.get(1816229739), {});
			return true;
		}
		return false;
	},
	HandleTextInput : function(event) {
		let is_change = false;
		if (this._multi_cursor === false) {
			if ((this._editable || event.custom)) {
				if (this.CheckAtKeyInput(event.text)) {
					return;
				}
				this._is_selecting = false;
				is_change = this.InsertTextNative(event.text);
			}
		} else {
			if (this._is_selecting && this._editable) {
				this._is_selecting = false;
				is_change = this.InsertTextNative(event.text);
				this._multi_cursor = false;
			}
		}
		if (is_change) {
			this.DispatchEvent(___all_struct.get(958494922), {});
			this.UpdateFontText();
			this.ResetShowXByCursor();
			this.ResetCursor();
			this.ShowDefaultText();
		}
	},
	HandleKeyDown : function(event) {
		let is_change = false;
		if (event.sym === 1073741904) {
			if (this._multi_cursor === false) {
				if (lua.bit.band(event.mod, ALittle.UIEnumTypes.KMOD_SHIFT) === 0) {
					this._is_selecting = false;
					this.CursorOffsetLR(true);
				} else {
					this._is_selecting = true;
					this.SelectCursorOffsetLR(true);
				}
			}
			event.handled = true;
		} else if (event.sym === 1073741903) {
			if (this._multi_cursor === false) {
				if (lua.bit.band(event.mod, ALittle.UIEnumTypes.KMOD_SHIFT) === 0) {
					this._is_selecting = false;
					this.CursorOffsetLR(false);
				} else {
					this._is_selecting = true;
					this.SelectCursorOffsetLR(false);
				}
			}
			event.handled = true;
		} else if (event.sym === 8) {
			if (this._multi_cursor === false) {
				if (this._editable || event.custom) {
					this._is_selecting = false;
					is_change = this.DeleteText(true);
				}
			} else {
				if (this._is_selecting && this._editable) {
					this._is_selecting = false;
					is_change = this.DeleteText(true);
					this._multi_cursor = false;
				}
			}
			event.handled = true;
		} else if (event.sym === 127) {
			if (this._multi_cursor === false) {
				if (this._editable || event.custom) {
					this._is_selecting = false;
					is_change = this.DeleteText(false);
				}
			} else {
				if (this._is_selecting && this._editable) {
					this._is_selecting = false;
					is_change = this.DeleteText(false);
					this._multi_cursor = false;
				}
			}
			event.handled = true;
		} else if (event.sym === 1073741898) {
			this._is_selecting = false;
			this.ClickCursorToHome();
			event.handled = true;
		} else if (event.sym === 1073741901) {
			this._is_selecting = false;
			this.ClickCursorToEnd();
			event.handled = true;
		} else if (event.sym === 13 || event.sym === 1073741912) {
			if (this._editable || event.custom) {
				this._is_selecting = false;
				this.DispatchEvent(___all_struct.get(776398171), {});
				event.handled = true;
			}
		} else if (event.sym === 120 && lua.bit.band(event.mod, ALittle.UIEnumTypes.KMOD_CTRL) !== 0) {
			if (this._multi_cursor === false) {
				if ((this._editable || event.custom) && !this._password_mode) {
					this._is_selecting = false;
					let select_text = this.GetSelectText();
					if (select_text[1 - 1] !== undefined) {
						ALittle.System_SetClipboardText(lua.json.encode(select_text));
						is_change = this.DeleteSelectText();
					}
				}
			} else {
				if ((this._is_selecting && this._editable) && !this._password_mode) {
					this._is_selecting = false;
					let select_text = this.GetSelectText();
					if (select_text[1 - 1] !== undefined) {
						ALittle.System_SetClipboardText(lua.json.encode(select_text));
						is_change = this.DeleteSelectText();
					}
					this._multi_cursor = false;
				}
			}
			event.handled = true;
		} else if (event.sym === 99 && lua.bit.band(event.mod, ALittle.UIEnumTypes.KMOD_CTRL) !== 0) {
			if (!this._password_mode) {
				let select_text = this.GetSelectText();
				if (select_text[1 - 1] !== undefined) {
					ALittle.System_SetClipboardText(lua.json.encode(select_text));
				}
			}
			event.handled = true;
		} else if (event.sym === 118 && lua.bit.band(event.mod, ALittle.UIEnumTypes.KMOD_CTRL) !== 0) {
			if (this._multi_cursor === false) {
				if (this._editable || event.custom) {
					this._is_selecting = false;
					if (ALittle.System_HasClipboardText()) {
						let content = ALittle.System_GetClipboardText();
						let [error, new_content] = (function() { try { let ___VALUE = lua.json.decode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
						if (error === undefined && __type(new_content) === "table" && this.CheckDisplayList(new_content)) {
							if (this.CheckAtKeyInput(new_content)) {
								return;
							}
							is_change = this.InsertDisplayListNative(new_content, false);
						} else {
							if (this.CheckAtKeyInput(content)) {
								return;
							}
							is_change = this.InsertTextNative(content);
						}
					}
				}
			} else {
				if (this._is_selecting && this._editable) {
					this._is_selecting = false;
					if (ALittle.System_HasClipboardText()) {
						let content = ALittle.System_GetClipboardText();
						let [error, new_content] = (function() { try { let ___VALUE = lua.json.decode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
						if (error === undefined && __type(new_content) === "table" && this.CheckDisplayList(new_content)) {
							is_change = this.InsertDisplayListNative(new_content, false);
						} else {
							is_change = this.InsertTextNative(content);
						}
					}
					this._multi_cursor = false;
				}
			}
			event.handled = true;
		} else if (event.sym === 97 && lua.bit.band(event.mod, ALittle.UIEnumTypes.KMOD_CTRL) !== 0) {
			this._is_selecting = true;
			this.SelectAll();
			event.handled = true;
		}
		if (is_change) {
			this.DispatchEvent(___all_struct.get(958494922), {});
			this._current_flash_alpha = 1.5;
			this.UpdateFontText();
			this.ResetShowXByCursor();
			this.ResetCursor();
			this.ShowDefaultText();
		}
	},
	HandleDragBegin : function(event) {
		if (this._can_drag_text === false) {
			return;
		}
		if (this._multi_cursor === false) {
			if (this._is_click) {
				this._is_drag_begin = true;
				this._is_selecting = true;
				this.DragCursorBegin();
			} else {
				this._is_drag_begin = false;
			}
		} else {
			if (this._is_click_cursor) {
				if ((this._is_click_cursor_name === "start" && this._start_cursor_data === "select") || (this._is_click_cursor_name === "end" && this._end_cursor_data === "select")) {
					let char_temp_it = this._char_select_it;
					this._char_select_it = this._char_cursor_it;
					this._char_cursor_it = char_temp_it;
				}
				if (this._is_click_cursor_name === "start") {
					this._drag_delta_x = this._start_cursor.x + this._start_cursor.width - event.rel_x;
					this._drag_delta_y = this._start_cursor.y + this._cursor_margin_up + (this._start_cursor.height - this._cursor_margin_up - this._cursor_margin_down) / 2 - event.rel_y;
				} else if (this._is_click_cursor_name === "end") {
					this._drag_delta_x = this._end_cursor.x - event.rel_x;
					this._drag_delta_y = this._end_cursor.y + this._cursor_margin_up + (this._end_cursor.height - this._cursor_margin_up - this._cursor_margin_down) / 2 - event.rel_y;
				}
				this._is_drag_begin = true;
				this.DispatchEvent(___all_struct.get(1424993548), {});
			} else if (this._is_click) {
				this._is_drag_begin = true;
				this.DispatchEvent(___all_struct.get(1424993548), {});
			} else {
				this._is_drag_begin = false;
			}
		}
	},
	HandleDrag : function(event) {
		if (this._can_drag_text === false) {
			return;
		}
		if (this._is_drag_begin === false) {
			return;
		}
		if (this._multi_cursor === false) {
			if (this._is_selecting === false) {
				return;
			}
			this.DragCursor(event.rel_x - this._display_view.x);
		} else {
			if (this._is_click_cursor) {
				this.DragMultiCursor(event.rel_x - this._display_view.x);
			} else {
				this._click_drag_delta_x = this._click_drag_delta_x + __abs(event.delta_x);
				this._click_drag_delta_y = this._click_drag_delta_y + __abs(event.delta_y);
				this.DragInput(event.delta_x);
			}
			this.DispatchEvent(___all_struct.get(-605767802), {});
		}
	},
	HandleDragEnd : function(event) {
		if (this._can_drag_text === false) {
			return;
		}
		if (this._is_drag_begin === false) {
			return;
		}
		if (this._multi_cursor) {
			if (this._cursor.visible) {
				this._multi_cursor = false;
			}
			this.DispatchEvent(___all_struct.get(-884368490), {});
		}
	},
	HandleLongLButtonDown : function(event) {
		if (this._is_click) {
			if (this.editable === false) {
				this._is_selecting = true;
				if (this._multi_cursor === false) {
					this._multi_cursor = true;
					this._cursor.visible = false;
					this._start_cursor.visible = true;
					this._end_cursor.visible = true;
					this.ClickMultiCursor(event.rel_x - this._display_view.x, false);
				} else {
					this.ClickMultiCursor(event.rel_x - this._display_view.x, false);
				}
			} else {
				this._multi_cursor = false;
				this._start_cursor.visible = false;
				this._end_cursor.visible = false;
				this._cursor.visible = true;
				this.ClickCursor(event.rel_x - this._display_view.x);
			}
			let e = {};
			e.target = this;
			e.abs_x = event.abs_x;
			e.abs_y = event.abs_y;
			e.rel_x = event.rel_x;
			e.rel_y = event.rel_y;
			this.DispatchEvent(___all_struct.get(1640499878), e);
			this._is_longclick = true;
		}
	},
}, "ALittle.RichInput");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


let __floor = ALittle.Math_Floor;
let __remove = ALittle.List_Remove;
let __sin = ALittle.Math_Sin;
if (ALittle.DisplayView === undefined) throw new Error(" extends class:ALittle.DisplayView is undefined");
ALittle.ScrollList = JavaScript.Class(ALittle.DisplayView, {
	Ctor : function(ctrl_sys) {
		this._width = 0;
		this._height = 0;
		this._drag_delta_x = 0;
		this._drag_delta_y = 0;
		this._drag_delta_table = [];
		this._drag_delta_table_count = 0;
		this._drag_rate = 0.2;
		this._open_extends_drag = false;
		this._clip_atonce = false;
		this._drag_time = 0;
		this._max_speed = 40;
		this._type = ALittle.UIEnumTypes.TYPE_V;
		this._scroll_linear = ALittle.NewObject(ALittle.Linear, this._ctrl_sys);
		this._scroll_linear.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
		this._scroll_linear.type = ALittle.UIEnumTypes.TYPE_V;
		ALittle.DisplayView.AddChild.call(this, this._scroll_linear);
		this._scroll_linear.AddEventListener(___all_struct.get(-431205740), this, this.HandleLinearResize);
		this._pickup_rect = true;
		this._pickup_child = true;
		this._pickup_this = true;
		this._can_scroll = true;
		this.AddEventListener(___all_struct.get(-1737121315), this, this.HandleMButtonWheel);
		this.AddEventListener(___all_struct.get(1337289812), this, this.HandleDrag);
		this.AddEventListener(___all_struct.get(150587926), this, this.HandleDragEnd);
		this.AddEventListener(___all_struct.get(1301789264), this, this.HandleDragBegin);
		this.RefreshClipDisLine();
	},
	GetChildIndex : function(child) {
		return this._scroll_linear.GetChildIndex(child);
	},
	SetChildIndex : function(child, index) {
		this._scroll_linear.SetChildIndex(child, index);
		this.RefreshClipDisLine();
		return true;
	},
	GetChildByIndex : function(index) {
		return this._scroll_linear.GetChildByIndex(index);
	},
	get childs() {
		return this._scroll_linear.childs;
	},
	get child_count() {
		return this._scroll_linear.child_count;
	},
	set type(value) {
		if (this._type === value) {
			return;
		}
		this._type = value;
		if (this._type === ALittle.UIEnumTypes.TYPE_H) {
			this._scroll_linear.width_type = ALittle.UIEnumTypes.SIZE_ABS;
			this._scroll_linear.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._scroll_linear.type = ALittle.UIEnumTypes.TYPE_H;
		} else {
			this._scroll_linear.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._scroll_linear.height_type = ALittle.UIEnumTypes.SIZE_ABS;
			this._scroll_linear.type = ALittle.UIEnumTypes.TYPE_V;
		}
		this.RefreshChild(false);
	},
	get type() {
		return this._type;
	},
	AddChild : function(child, index) {
		if (child === undefined) {
			return false;
		}
		if (this._scroll_linear.AddChild(child, index) === false) {
			return false;
		}
		this.RefreshChild(false);
		return true;
	},
	RemoveChild : function(child) {
		if (child === undefined) {
			return false;
		}
		if (this._scroll_linear.RemoveChild(child) === false) {
			return false;
		}
		this.RefreshChild(false);
		return true;
	},
	AddChildEffect : function(child, up) {
		if (child === undefined) {
			return false;
		}
		if (up) {
			if (this._type === ALittle.UIEnumTypes.TYPE_H) {
				let target_value = this._scroll_linear.x + this._scroll_linear.width;
				if (this._scroll_linear.AddChild(child, 1) === false) {
					return false;
				}
				this._scroll_linear.x = target_value - this._scroll_linear.width;
			} else {
				let target_value = this._scroll_linear.y + this._scroll_linear.height;
				if (this._scroll_linear.AddChild(child, 1) === false) {
					return false;
				}
				this._scroll_linear.y = target_value - this._scroll_linear.height;
			}
		} else {
			if (this._scroll_linear.AddChild(child) === false) {
				return false;
			}
		}
		this.RefreshChild(false);
		return true;
	},
	RemoveChildEffect : function(up, loop) {
		if (up) {
			if (this._type === ALittle.UIEnumTypes.TYPE_H) {
				let child = this._scroll_linear.GetChildByIndex(1);
				let target_value = this._scroll_linear.x + this._scroll_linear.width;
				if (this._scroll_linear.RemoveChild(child) === false) {
					return false;
				}
				this._scroll_linear.x = target_value - this._scroll_linear.width;
			} else {
				let child = this._scroll_linear.GetChildByIndex(1);
				let target_value = this._scroll_linear.y + this._scroll_linear.height;
				if (this._scroll_linear.RemoveChild(child) === false) {
					return false;
				}
				this._scroll_linear.y = target_value - this._scroll_linear.height;
			}
		} else {
			let child = this._scroll_linear.GetChildByIndex(this._scroll_linear.child_count);
			if (this._scroll_linear.RemoveChild(child) === false) {
				return false;
			}
		}
		if (loop) {
			this.RefreshChild(true);
		} else {
			this.RefreshChild(false);
		}
		return true;
	},
	HasChild : function(child) {
		return this._scroll_linear.HasChild(child);
	},
	RemoveAllChild : function() {
		if (this._type === ALittle.UIEnumTypes.TYPE_H) {
			A_LoopSystem.RemoveUpdater(this._drag_loop_x);
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_x);
			this._scroll_linear.x = 0;
		} else {
			A_LoopSystem.RemoveUpdater(this._drag_loop_y);
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_y);
			this._scroll_linear.y = 0;
		}
		this._scroll_linear.RemoveAllChild();
		this.UpdateLoadingShow();
		this.RejustScrollBar();
	},
	RefreshChild : function(loop) {
		if (this._type === ALittle.UIEnumTypes.TYPE_H) {
			let linear_width = this._scroll_linear.width;
			let target_x = undefined;
			if (linear_width >= this._width) {
				if (this._scroll_linear.x > 0) {
					target_x = 0;
				} else if (this._scroll_linear.x < -linear_width + this._width) {
					target_x = -linear_width + this._width;
				}
			} else {
				target_x = 0;
			}
			if (target_x === undefined || target_x === this._scroll_linear.x) {
				A_LoopSystem.RemoveUpdater(this._drag_loop_x);
				this.RefreshClipDisLine();
				this.RejustScrollBar();
				return;
			}
			if (this._drag_loop_x !== undefined && this._drag_loop_x.IsCompleted() === false) {
				let speed = this._drag_loop_x.speed;
				let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
				A_LoopSystem.RemoveUpdater(this._drag_loop_x);
				let time = (target_x - this._scroll_linear.x) / speed;
				this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "x", target_x, __floor(time), 0, func);
				A_LoopSystem.AddUpdater(this._drag_loop_x);
			} else {
				if (loop) {
					let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
					A_LoopSystem.RemoveUpdater(this._drag_loop_x);
					this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "x", target_x, 200, 0, func);
					A_LoopSystem.AddUpdater(this._drag_loop_x);
				} else {
					this._scroll_linear.x = target_x;
				}
			}
		} else {
			let linear_height = this._scroll_linear.height;
			let target_y = undefined;
			if (linear_height >= this._height) {
				if (this._scroll_linear.y > 0) {
					target_y = 0;
				} else if (this._scroll_linear.y < -linear_height + this._height) {
					target_y = -linear_height + this._height;
				}
			} else {
				target_y = 0;
			}
			if (target_y === undefined || target_y === this._scroll_linear.y) {
				A_LoopSystem.RemoveUpdater(this._drag_loop_y);
				this.RefreshClipDisLine();
				this.RejustScrollBar();
				return;
			}
			if (this._drag_loop_y !== undefined && this._drag_loop_y.IsCompleted() === false) {
				let speed = this._drag_loop_y.speed;
				let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
				A_LoopSystem.RemoveUpdater(this._drag_loop_y);
				let time = (target_y - this._scroll_linear.y) / speed;
				this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "y", target_y, __floor(time), 0, func);
				A_LoopSystem.AddUpdater(this._drag_loop_y);
			} else {
				if (loop) {
					let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
					A_LoopSystem.RemoveUpdater(this._drag_loop_y);
					this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "y", target_y, 200, 0, func);
					A_LoopSystem.AddUpdater(this._drag_loop_y);
				} else {
					this._scroll_linear.y = target_y;
				}
			}
		}
		this.RefreshClipDisLine();
		this.RejustScrollBar();
	},
	set clip_atonce(value) {
		this._clip_atonce = value;
	},
	get clip_atonce() {
		return this._clip_atonce;
	},
	set scroll_offset(value) {
		if (this._type === ALittle.UIEnumTypes.TYPE_H) {
			A_LoopSystem.RemoveUpdater(this._drag_loop_x);
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_x);
			if (value > 0) {
				value = 0;
			}
			let total_width = this.width;
			let linear_width = this._scroll_linear.width;
			if (total_width < linear_width) {
				let delta = total_width - linear_width;
				if (value < delta) {
					value = delta;
				}
			}
			this._scroll_linear.x = value;
			this.RejustScrollBar();
		} else {
			A_LoopSystem.RemoveUpdater(this._drag_loop_y);
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_y);
			if (value > 0) {
				value = 0;
			}
			let total_height = this.height;
			let linear_height = this._scroll_linear.height;
			if (total_height < linear_height) {
				let delta = total_height - linear_height;
				if (value < delta) {
					value = delta;
				}
			}
			this._scroll_linear.y = value;
			this.RejustScrollBar();
		}
	},
	get scroll_offset() {
		if (this._type === ALittle.UIEnumTypes.TYPE_H) {
			return this._scroll_linear.x;
		}
		return this._scroll_linear.y;
	},
	ScrollToBottom : function() {
		if (this.height >= this.real_height) {
			return;
		}
		this.scroll_offset = this.height - this.real_height;
	},
	set gap(value) {
		if (value === undefined) {
			value = 0;
		}
		this._scroll_linear.gap = value;
		this.RefreshClipDisLine();
		this.RejustScrollBar();
	},
	get gap() {
		return this._scroll_linear.gap;
	},
	get real_height() {
		return this._scroll_linear.height;
	},
	get real_width() {
		return this._scroll_linear.width;
	},
	set width(value) {
		if (this._type === ALittle.UIEnumTypes.TYPE_V) {
			ALittle.DisplayView.__setter.width.call(this, value);
			return;
		}
		if (this._width === value) {
			return;
		}
		this._width = value;
		if (this._width_type === ALittle.UIEnumTypes.SIZE_ABS) {
			this._width_value = this._width;
		}
		this._show.SetWidth(this._width);
		if (this._scroll_bar !== undefined) {
			let linear_width = this._scroll_linear.width;
			let rate = this._scroll_bar.offset_rate;
			if (linear_width < this._width) {
				rate = 0;
			}
			this._scroll_bar.width = this._width;
			this._scroll_bar.total_size = linear_width;
			this._scroll_bar.show_size = this._width;
			this._scroll_bar.offset_rate = rate;
			this._scroll_bar.offset_step = 0.1;
			let x = 0.0;
			if (linear_width > this._width) {
				let total_width = linear_width - this._width;
				x = -total_width * rate;
			}
			this._scroll_linear.x = x;
		}
		this.RefreshClipDisLine();
	},
	set height(value) {
		if (this._type === ALittle.UIEnumTypes.TYPE_H) {
			ALittle.DisplayView.__setter.height.call(this, value);
			return;
		}
		if (this._height === value) {
			return;
		}
		this._height = value;
		if (this._height_type === ALittle.UIEnumTypes.SIZE_ABS) {
			this._height_value = this._height;
		}
		this._show.SetHeight(this._height);
		if (this._scroll_bar !== undefined) {
			let linear_height = this._scroll_linear.height;
			let rate = this._scroll_bar.offset_rate;
			if (linear_height < this._height) {
				rate = 0;
			}
			this._scroll_bar.height = this._height;
			this._scroll_bar.total_size = linear_height;
			this._scroll_bar.show_size = this._height;
			this._scroll_bar.offset_rate = rate;
			this._scroll_bar.offset_step = 0.1;
			let y = 0.0;
			if (linear_height > this._height) {
				let total_height = linear_height - this._height;
				y = -total_height * rate;
			}
			this._scroll_linear.y = y;
		}
		this.RefreshClipDisLine();
	},
	set right_scrollbar(value) {
		if (this._scroll_bar !== undefined) {
			A_LoopSystem.RemoveUpdater(this._scroll_bar_loop);
			ALittle.DisplayView.RemoveChild.call(this, this._scroll_bar);
			this._scroll_bar.RemoveEventListener(___all_struct.get(958494922), this, this.HandleRightScrollBarChange);
			this._scroll_bar.RemoveEventListener(___all_struct.get(1309977874), this, this.HandleRightScrollBarChangeEnd);
		}
		this._scroll_bar = value;
		if (this._scroll_bar !== undefined) {
			if (this._type === ALittle.UIEnumTypes.TYPE_H) {
				this._scroll_bar.alpha = 0;
				this._scroll_bar.visible = false;
				this._scroll_bar.type = ALittle.UIEnumTypes.TYPE_H;
				this._scroll_bar.y_type = ALittle.UIEnumTypes.POS_ALIGN_ENDING;
				ALittle.DisplayView.AddChild.call(this, this._scroll_bar);
				this._scroll_bar.AddEventListener(___all_struct.get(958494922), this, this.HandleRightScrollBarChange);
				this._scroll_bar.AddEventListener(___all_struct.get(1309977874), this, this.HandleRightScrollBarChangeEnd);
				this._scroll_bar.width = this._width;
				this._scroll_bar.x = 0;
				this._scroll_bar.total_size = this._scroll_linear.width;
				this._scroll_bar.show_size = this._width;
				this._scroll_bar.offset_rate = 0;
				this._scroll_bar.offset_step = 0.1;
			} else {
				this._scroll_bar.alpha = 0;
				this._scroll_bar.visible = false;
				this._scroll_bar.type = ALittle.UIEnumTypes.TYPE_V;
				this._scroll_bar.x_type = ALittle.UIEnumTypes.POS_ALIGN_ENDING;
				ALittle.DisplayView.AddChild.call(this, this._scroll_bar);
				this._scroll_bar.AddEventListener(___all_struct.get(958494922), this, this.HandleRightScrollBarChange);
				this._scroll_bar.AddEventListener(___all_struct.get(1309977874), this, this.HandleRightScrollBarChangeEnd);
				this._scroll_bar.height = this._height;
				this._scroll_bar.y = 0;
				this._scroll_bar.total_size = this._scroll_linear.height;
				this._scroll_bar.show_size = this._height;
				this._scroll_bar.offset_rate = 0;
				this._scroll_bar.offset_step = 0.1;
			}
		}
	},
	get right_scrollbar() {
		return this._scroll_bar;
	},
	RejustScrollBar : function() {
		if (this._type === ALittle.UIEnumTypes.TYPE_H) {
			let linear_width = this._scroll_linear.width;
			if (this._scroll_bar !== undefined) {
				let rate = 0.0;
				if (linear_width <= this._width) {
					rate = 0;
				} else {
					rate = -this._scroll_linear.x / (linear_width - this._width);
				}
				this._scroll_bar.width = this._width;
				this._scroll_bar.total_size = linear_width;
				this._scroll_bar.show_size = this._width;
				this._scroll_bar.offset_rate = rate;
				this._scroll_bar.offset_step = 0.1;
			}
		} else {
			let linear_height = this._scroll_linear.height;
			if (this._scroll_bar !== undefined) {
				let rate = 0.0;
				if (linear_height <= this._height) {
					rate = 0;
				} else {
					rate = -this._scroll_linear.y / (linear_height - this._height);
				}
				this._scroll_bar.height = this._height;
				this._scroll_bar.total_size = linear_height;
				this._scroll_bar.show_size = this._height;
				this._scroll_bar.offset_rate = rate;
				this._scroll_bar.offset_step = 0.1;
			}
		}
	},
	get loading_show_up() {
		return this._loading_show_up;
	},
	set loading_show_up(value) {
		if (this._loading_show_up !== value) {
			ALittle.DisplayView.RemoveChild.call(this, this._loading_show_up);
			this._loading_show_up = undefined;
		}
		if (value !== undefined) {
			this._loading_show_up = value;
			ALittle.DisplayView.AddChild.call(this, this._loading_show_up);
			if (this._type === ALittle.UIEnumTypes.TYPE_H) {
				this._loading_show_up.x = this._scroll_linear.x - this._loading_show_up.width;
			} else {
				this._loading_show_up.y = this._scroll_linear.y - this._loading_show_up.height;
			}
		}
	},
	get loading_show_down() {
		return this._loading_show_down;
	},
	set loading_show_down(value) {
		if (this._loading_show_down !== value) {
			ALittle.DisplayView.RemoveChild.call(this, this._loading_show_down);
			this._loading_show_down = undefined;
		}
		if (value !== undefined) {
			this._loading_show_down = value;
			ALittle.DisplayView.AddChild.call(this, this._loading_show_down);
			if (this._type === ALittle.UIEnumTypes.TYPE_H) {
				this._loading_show_down.x = this._scroll_linear.x + this._scroll_linear.width;
			} else {
				this._loading_show_down.y = this._scroll_linear.y + this._scroll_linear.height;
			}
		}
	},
	UpdateLoadingShow : function() {
		if (this._type === ALittle.UIEnumTypes.TYPE_H) {
			if (this._loading_show_up !== undefined) {
				this._loading_show_up.x = this._scroll_linear.x - this._loading_show_up.width;
			}
			if (this._loading_show_down !== undefined) {
				this._loading_show_down.x = this._scroll_linear.x + this._scroll_linear.width;
			}
		} else {
			if (this._loading_show_up !== undefined) {
				this._loading_show_up.y = this._scroll_linear.y - this._loading_show_up.height;
			}
			if (this._loading_show_down !== undefined) {
				this._loading_show_down.y = this._scroll_linear.y + this._scroll_linear.height;
			}
		}
	},
	Layout : function(index) {
		this._scroll_linear.Layout(index);
		this.RefreshClipDisLine();
	},
	DeepLayout : function() {
		this._scroll_linear.DeepLayout();
		this.RefreshClipDisLine();
	},
	HandleLinearResize : function(event) {
		this.RejustScrollBar();
		this.RefreshClipDisLine();
	},
	HandleRightScrollBarChange : function(event) {
		if (this._type === ALittle.UIEnumTypes.TYPE_H) {
			let rate = this._scroll_bar.offset_rate;
			let x = 0.0;
			let linear_width = this._scroll_linear.width;
			if (linear_width > this._width) {
				let total_width = linear_width - this._width;
				x = -total_width * rate;
			}
			this._scroll_linear.x = x;
		} else {
			let rate = this._scroll_bar.offset_rate;
			let y = 0.0;
			let linear_height = this._scroll_linear.height;
			if (linear_height > this._height) {
				let total_height = linear_height - this._height;
				y = -total_height * rate;
			}
			this._scroll_linear.y = y;
		}
		this.RefreshClipDisLine();
		this.ShowRightScrollBar();
	},
	HandleRightScrollBarChangeEnd : function(event) {
		this.HideRightScrollBar();
	},
	HandleMButtonWheel : function(event) {
		if (this._scroll_bar !== undefined && event.delta_y !== 0) {
			let offset = this._scroll_linear.height * 0.1 * event.delta_y;
			if (offset > 40) {
				offset = 40;
			} else if (offset < -40) {
				offset = -40;
			}
			if (offset !== 0) {
				this._scroll_bar.offset_rate = this._scroll_bar.offset_rate - offset / this._scroll_linear.height;
			}
			this.HandleRightScrollBarChange(undefined);
			this.HideRightScrollBar();
		}
	},
	get open_extends_drag() {
		return this._open_extends_drag;
	},
	set open_extends_drag(value) {
		this._open_extends_drag = value;
	},
	HandleDragBegin : function(event) {
		this._drag_delta_table = [];
		this._drag_delta_table_count = 0;
		A_LoopSystem.RemoveUpdater(this._scroll_bar_loop);
		if (this._scroll_bar !== undefined) {
			this._scroll_bar.visible = true;
			this._scroll_bar.alpha = 1;
		}
		if (this._type === ALittle.UIEnumTypes.TYPE_H) {
			A_LoopSystem.RemoveUpdater(this._drag_loop_x);
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_x);
		} else {
			A_LoopSystem.RemoveUpdater(this._drag_loop_y);
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_y);
		}
	},
	HandleDrag : function(event) {
		if (this._type === ALittle.UIEnumTypes.TYPE_H) {
			if (this._drag_delta_table_count < 3) {
				++ this._drag_delta_table_count;
				this._drag_delta_table[this._drag_delta_table_count - 1] = event.delta_x;
			} else {
				__remove(this._drag_delta_table, 1);
				this._drag_delta_table[this._drag_delta_table_count - 1] = event.delta_x;
			}
			this._drag_time = ALittle.Time_GetCurTime();
			let linear_width = this._scroll_linear.width;
			if (event.delta_x !== 0 && this._scroll_bar !== undefined) {
				if (event.delta_x > 0) {
					let min_x = 0.0;
					let max_x = this._width * this._drag_rate;
					let x = this._scroll_linear.x;
					if (x > min_x) {
						x = x + event.delta_x * __sin((1 - x / (this._width * this._drag_rate)) * 1.57);
						if (x > max_x) {
							x = max_x;
						}
					} else {
						x = x + (event.delta_x);
					}
					if (x >= min_x && !this._open_extends_drag) {
						x = min_x;
					}
					this._scroll_linear.x = x;
					if (this._scroll_bar !== undefined) {
						this._scroll_bar.offset_rate = -x / (linear_width - this._width);
					}
				} else {
					let x = this._scroll_linear.x;
					if (linear_width < this._width) {
						x = x + (event.delta_x);
						if (x < 0) {
							x = 0;
						}
					} else {
						let max_x = -linear_width + this._width;
						let min_x = max_x - this._width * this._drag_rate;
						if (x < max_x) {
							x = x + (event.delta_x * __sin((x - min_x) / (this._width * this._drag_rate) * 1.57));
							if (x < min_x) {
								x = min_x;
							}
						} else {
							x = x + (event.delta_x);
						}
						if (x <= max_x && !this._open_extends_drag) {
							x = max_x;
						}
					}
					this._scroll_linear.x = x;
					if (this._scroll_bar !== undefined) {
						this._scroll_bar.offset_rate = -x / (linear_width - this._width);
					}
				}
				this.RefreshClipDisLine(event.delta_x);
			}
		} else {
			if (this._drag_delta_table_count < 3) {
				++ this._drag_delta_table_count;
				this._drag_delta_table[this._drag_delta_table_count - 1] = event.delta_y;
			} else {
				__remove(this._drag_delta_table, 1);
				this._drag_delta_table[this._drag_delta_table_count - 1] = event.delta_y;
			}
			this._drag_time = ALittle.Time_GetCurTime();
			let linear_height = this._scroll_linear.height;
			if (event.delta_y !== 0 && this._scroll_bar !== undefined) {
				if (event.delta_y > 0) {
					let min_y = 0.0;
					let max_y = this._height * this._drag_rate;
					let y = this._scroll_linear.y;
					if (y > min_y) {
						y = y + event.delta_y * __sin((1 - y / (this._height * this._drag_rate)) * 1.57);
						if (y > max_y) {
							y = max_y;
						}
					} else {
						y = y + (event.delta_y);
					}
					if (y >= min_y && !this._open_extends_drag) {
						y = min_y;
					}
					this._scroll_linear.y = y;
					if (this._scroll_bar !== undefined) {
						this._scroll_bar.offset_rate = -y / (linear_height - this._height);
					}
				} else {
					let y = this._scroll_linear.y;
					if (linear_height < this._height) {
						y = y + (event.delta_y);
						if (y < 0) {
							y = 0;
						}
					} else {
						let max_y = -linear_height + this._height;
						let min_y = max_y - this._height * this._drag_rate;
						if (y < max_y) {
							y = y + (event.delta_y * __sin((y - min_y) / (this._height * this._drag_rate) * 1.57));
							if (y < min_y) {
								y = min_y;
							}
						} else {
							y = y + (event.delta_y);
						}
						if (y <= max_y && !this._open_extends_drag) {
							y = max_y;
						}
					}
					this._scroll_linear.y = y;
					if (this._scroll_bar !== undefined) {
						this._scroll_bar.offset_rate = -y / (linear_height - this._height);
					}
				}
				this.RefreshClipDisLine(event.delta_y);
			}
		}
	},
	HandleDragEnd : function(event) {
		if (this._type === ALittle.UIEnumTypes.TYPE_H) {
			let linear_width = this._scroll_linear.width;
			if (this._scroll_linear.x > 0) {
				A_LoopSystem.RemoveUpdater(this._drag_loop_x);
				let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
				this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "x", 0, 200, 0, func);
				A_LoopSystem.AddUpdater(this._drag_loop_x);
				this.HideRightScrollBar();
				if (this._scroll_linear.x >= this._width * this._drag_rate * 0.9) {
					this.DispatchEvent(___all_struct.get(1848466169), {});
				}
			} else if (this._scroll_linear.x < -linear_width + this._width) {
				if (this._scroll_linear.x < 0) {
					let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
					A_LoopSystem.RemoveUpdater(this._drag_loop_x);
					this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "x", -linear_width + this._width, 200, 0, func);
					A_LoopSystem.AddUpdater(this._drag_loop_x);
					this.HideRightScrollBar();
				}
				if (this._scroll_linear.x <= -linear_width + this._width - this._width * this._drag_rate * 0.9) {
					this.DispatchEvent(___all_struct.get(809518110), {});
				}
			} else if (this._scroll_linear.x !== 0 && this._scroll_linear.x !== -linear_width + this._width) {
				let count = this._drag_delta_table_count;
				let drag_delta_x = 0.0;
				let drag_end_time = ALittle.Time_GetCurTime() - this._drag_time;
				if (drag_end_time < 50) {
					if (count === 1 || count === 2) {
						drag_delta_x = this._drag_delta_table[1 - 1];
					} else if (count === 3) {
						drag_delta_x = __floor((this._drag_delta_table[count - 1 - 1] + this._drag_delta_table[count - 2 - 1]) / 2);
					} else {
						drag_delta_x = 0;
					}
				} else {
					if (count !== 0) {
						drag_delta_x = this._drag_delta_table[count - 1];
					} else {
						drag_delta_x = 0;
					}
				}
				if (drag_delta_x < 0 && drag_delta_x < -this._max_speed) {
					drag_delta_x = -this._max_speed;
				} else if (drag_delta_x > 0 && drag_delta_x > this._max_speed) {
					drag_delta_x = this._max_speed;
				}
				this._drag_delta_x = drag_delta_x;
				A_LoopSystem.RemoveUpdater(this._drag_delta_loop_x);
				this._drag_delta_loop_x = ALittle.NewObject(ALittle.LoopFunction, this.RefreshLinearX.bind(this), -1, 1, 0);
				A_LoopSystem.AddUpdater(this._drag_delta_loop_x);
			}
		} else {
			let linear_height = this._scroll_linear.height;
			if (this._scroll_linear.y > 0) {
				A_LoopSystem.RemoveUpdater(this._drag_loop_y);
				let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
				this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "y", 0, 200, 0, func);
				A_LoopSystem.AddUpdater(this._drag_loop_y);
				this.HideRightScrollBar();
				if (this._scroll_linear.y >= this._height * this._drag_rate * 0.9) {
					this.DispatchEvent(___all_struct.get(1848466169), {});
				}
			} else if (this._scroll_linear.y < -linear_height + this._height) {
				if (this._scroll_linear.y < 0) {
					let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
					A_LoopSystem.RemoveUpdater(this._drag_loop_y);
					this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "y", -linear_height + this._height, 200, 0, func);
					A_LoopSystem.AddUpdater(this._drag_loop_y);
					this.HideRightScrollBar();
				}
				if (this._scroll_linear.y <= -linear_height + this._height - this._height * this._drag_rate * 0.9) {
					this.DispatchEvent(___all_struct.get(809518110), {});
				}
			} else if (this._scroll_linear.y !== 0 && this._scroll_linear.y !== -linear_height + this._height) {
				let count = this._drag_delta_table_count;
				let drag_delta_y = 0.0;
				let drag_end_time = ALittle.Time_GetCurTime() - this._drag_time;
				if (drag_end_time < 50) {
					if (count === 1 || count === 2) {
						drag_delta_y = this._drag_delta_table[1 - 1];
					} else if (count === 3) {
						drag_delta_y = __floor((this._drag_delta_table[count - 1 - 1] + this._drag_delta_table[count - 2 - 1]) / 2);
					} else {
						drag_delta_y = 0;
					}
				} else {
					if (count !== 0) {
						drag_delta_y = this._drag_delta_table[count - 1];
					} else {
						drag_delta_y = 0;
					}
				}
				if (drag_delta_y < 0 && drag_delta_y < -this._max_speed) {
					drag_delta_y = -this._max_speed;
				} else if (drag_delta_y > 0 && drag_delta_y > this._max_speed) {
					drag_delta_y = this._max_speed;
				}
				this._drag_delta_y = drag_delta_y;
				A_LoopSystem.RemoveUpdater(this._drag_delta_loop_y);
				this._drag_delta_loop_y = ALittle.NewObject(ALittle.LoopFunction, this.RefreshLinearY.bind(this), -1, 1, 0);
				A_LoopSystem.AddUpdater(this._drag_delta_loop_y);
			}
		}
	},
	RefreshLinearX : function() {
		this._scroll_linear.x = this._scroll_linear.x + this._drag_delta_x;
		let linear_width = this._scroll_linear.width;
		let loop_end = false;
		if (this._drag_delta_x !== 0 && this._scroll_bar !== undefined) {
			if (this._drag_delta_x > 0) {
				let min_x = 0.0;
				let max_x = this._width * this._drag_rate;
				let x = this._scroll_linear.x;
				if (x > min_x) {
					x = x + this._drag_delta_x * __sin((1 - x / (this._width * this._drag_rate)) * 1.57);
					if (x > max_x) {
						x = max_x;
						loop_end = true;
					}
				} else {
					x = x + (this._drag_delta_x);
				}
				if (x >= min_x && !this._open_extends_drag) {
					x = min_x;
				}
				this._scroll_linear.x = x;
				if (this._scroll_bar !== undefined) {
					this._scroll_bar.offset_rate = -x / (linear_width - this._width);
				}
			} else {
				let x = this._scroll_linear.x;
				if (linear_width < this._width) {
					x = x + (this._drag_delta_x);
					if (x < 0) {
						x = 0;
					}
				} else {
					let max_x = -linear_width + this._width;
					let min_x = max_x - this._width * this._drag_rate;
					if (x < max_x) {
						x = x + (this._drag_delta_x * __sin((x - min_x) / (this._width * this._drag_rate) * 1.57));
						if (x < min_x) {
							x = min_x;
							loop_end = true;
						}
					} else {
						x = x + (this._drag_delta_x);
					}
					if (x <= max_x && !this._open_extends_drag) {
						x = max_x;
					}
				}
				this._scroll_linear.x = x;
				if (this._scroll_bar !== undefined) {
					this._scroll_bar.offset_rate = -x / (linear_width - this._width);
				}
			}
			this.RefreshClipDisLine();
		}
		if (this._drag_delta_x < 0) {
			this._drag_delta_x = this._drag_delta_x + 1;
			if (this._drag_delta_x >= 0) {
				loop_end = true;
			}
		} else if (this._drag_delta_x > 0) {
			this._drag_delta_x = this._drag_delta_x - 1;
			if (this._drag_delta_x <= 0) {
				loop_end = true;
			}
		} else {
			loop_end = true;
		}
		if (loop_end) {
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_x);
			if (this._scroll_linear.x > 0) {
				let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
				A_LoopSystem.RemoveUpdater(this._drag_loop_x);
				this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "x", 0, 200, 0, func);
				A_LoopSystem.AddUpdater(this._drag_loop_x);
				if (this._scroll_linear.x >= this._width * this._drag_rate * 0.9) {
					this.DispatchEvent(___all_struct.get(1848466169), {});
				}
			} else if (this._scroll_linear.x < -linear_width + this._width) {
				if (this._scroll_linear.x < 0) {
					let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
					A_LoopSystem.RemoveUpdater(this._drag_loop_x);
					this._drag_loop_x = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "x", -linear_width + this._width, 200, 0, func);
					A_LoopSystem.AddUpdater(this._drag_loop_x);
				}
				if (this._scroll_linear.x <= -linear_width + this._width - this._width * this._drag_rate * 0.9) {
					this.DispatchEvent(___all_struct.get(809518110), {});
				}
			}
			this.HideRightScrollBar();
		}
	},
	RefreshLinearY : function() {
		this._scroll_linear.y = this._scroll_linear.y + this._drag_delta_y;
		let linear_height = this._scroll_linear.height;
		let loop_end = false;
		if (this._drag_delta_y !== 0 && this._scroll_bar !== undefined) {
			if (this._drag_delta_y > 0) {
				let min_y = 0.0;
				let max_y = this._height * this._drag_rate;
				let y = this._scroll_linear.y;
				if (y > min_y) {
					y = y + (this._drag_delta_y * __sin((1 - y / (this._height * this._drag_rate)) * 1.57));
					if (y > max_y) {
						y = max_y;
						loop_end = true;
					}
				} else {
					y = y + (this._drag_delta_y);
				}
				if (y >= min_y && !this._open_extends_drag) {
					y = min_y;
				}
				this._scroll_linear.y = y;
				if (this._scroll_bar !== undefined) {
					this._scroll_bar.offset_rate = -y / (linear_height - this._height);
				}
			} else {
				let y = this._scroll_linear.y;
				if (linear_height < this._height) {
					y = y + (this._drag_delta_y);
					if (y < 0) {
						y = 0;
					}
				} else {
					let max_y = -linear_height + this._height;
					let min_y = max_y - this._height * this._drag_rate;
					if (y < max_y) {
						y = y + (this._drag_delta_y * __sin((y - min_y) / (this._height * this._drag_rate) * 1.57));
						if (y < min_y) {
							y = min_y;
							loop_end = true;
						}
					} else {
						y = y + (this._drag_delta_y);
					}
					if (y <= max_y && !this._open_extends_drag) {
						y = max_y;
					}
				}
				this._scroll_linear.y = y;
				if (this._scroll_bar !== undefined) {
					this._scroll_bar.offset_rate = -y / (linear_height - this._height);
				}
			}
			this.RefreshClipDisLine();
		}
		if (this._drag_delta_y < 0) {
			this._drag_delta_y = this._drag_delta_y + 1;
			if (this._drag_delta_y >= 0) {
				loop_end = true;
			}
		} else if (this._drag_delta_y > 0) {
			this._drag_delta_y = this._drag_delta_y - 1;
			if (this._drag_delta_y <= 0) {
				loop_end = true;
			}
		} else {
			loop_end = true;
		}
		if (loop_end) {
			A_LoopSystem.RemoveUpdater(this._drag_delta_loop_y);
			if (this._scroll_linear.y > 0) {
				let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
				A_LoopSystem.RemoveUpdater(this._drag_loop_y);
				this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "y", 0, 200, 0, func);
				A_LoopSystem.AddUpdater(this._drag_loop_y);
				if (this._scroll_linear.y >= this._height * this._drag_rate * 0.9) {
					this.DispatchEvent(___all_struct.get(1848466169), {});
				}
			} else if (this._scroll_linear.y < -linear_height + this._height) {
				if (this._scroll_linear.y < 0) {
					let func = ALittle.ScrollList.RefreshClipDisLine.bind(this, undefined);
					A_LoopSystem.RemoveUpdater(this._drag_loop_y);
					this._drag_loop_y = ALittle.NewObject(ALittle.LoopLinear, this._scroll_linear, "y", -linear_height + this._height, 200, 0, func);
					A_LoopSystem.AddUpdater(this._drag_loop_y);
				}
				if (this._scroll_linear.y <= -linear_height + this._height - this._height * this._drag_rate * 0.9) {
					this.DispatchEvent(___all_struct.get(809518110), {});
				}
			}
			this.HideRightScrollBar();
		}
	},
	YScrollBarChange : function() {
		this._scroll_bar.offset_rate = -this._scroll_linear.y / (this._linear_height - this._height);
	},
	XScrollBarChange : function() {
		this._scroll_bar.offset_rate = -this._scroll_linear.x / (this._linear_width - this._width);
	},
	RefreshClipDisLineImpl : function(v_move) {
		this._scroll_linear.ClipRect(0, 0, this.width, this.height, undefined, v_move);
		this._clip_loop = undefined;
	},
	RefreshClipDisLine : function(v_move) {
		this.UpdateLoadingShow();
		if (this._clip_atonce) {
			this._scroll_linear.ClipRect(0, 0, this.width, this.height, undefined, undefined);
			return;
		}
		if (this._clip_loop !== undefined && this._clip_loop._user_data === undefined) {
			return;
		}
		this._clip_loop = ALittle.NewObject(ALittle.LoopFunction, this.RefreshClipDisLineImpl.bind(this, v_move), 1, 0, 1);
		this._clip_loop._user_data = v_move;
		A_LoopSystem.AddUpdater(this._clip_loop);
	},
	HideRightScrollBar : function() {
		if (this._scroll_bar !== undefined) {
			this._scroll_bar_loop = ALittle.NewObject(ALittle.LoopList);
			this._scroll_bar_loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._scroll_bar, "alpha", 0, 2000, 1000));
			this._scroll_bar_loop.AddUpdater(ALittle.NewObject(ALittle.LoopAttribute, this._scroll_bar, "visible", false, 1));
			A_LoopSystem.AddUpdater(this._scroll_bar_loop);
		}
	},
	ShowRightScrollBar : function() {
		if (this._scroll_bar_loop !== undefined) {
			A_LoopSystem.RemoveUpdater(this._scroll_bar_loop);
			this._scroll_bar_loop = undefined;
			if (this._scroll_bar !== undefined) {
				this._scroll_bar.visible = true;
				this._scroll_bar.alpha = 1;
			}
		}
	},
}, "ALittle.ScrollList");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(2101017097, "ALittle.ScrollButtonDragEndEvent", {
name : "ALittle.ScrollButtonDragEndEvent", ns_name : "ALittle", rl_name : "ScrollButtonDragEndEvent", hash_code : 2101017097,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(-2129379001, "ALittle.ScrollButtonDragBeginEvent", {
name : "ALittle.ScrollButtonDragBeginEvent", ns_name : "ALittle", rl_name : "ScrollButtonDragBeginEvent", hash_code : -2129379001,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(-646882501, "ALittle.ScrollButtonDragEvent", {
name : "ALittle.ScrollButtonDragEvent", ns_name : "ALittle", rl_name : "ScrollButtonDragEvent", hash_code : -646882501,
name_list : ["target","rel_x","rel_y","delta_x","delta_y","abs_x","abs_y"],
type_list : ["ALittle.DisplayObject","double","double","double","double","double","double"],
option_map : {}
})

let __abs = ALittle.Math_Abs;
if (ALittle.TextButton === undefined) throw new Error(" extends class:ALittle.TextButton is undefined");
ALittle.ScrollButton = JavaScript.Class(ALittle.TextButton, {
	Ctor : function(ctrl_sys) {
		this.AddEventListener(___all_struct.get(1301789264), this, this.HandleDragBegin);
		this.AddEventListener(___all_struct.get(1337289812), this, this.HandleDrag);
		this.AddEventListener(___all_struct.get(150587926), this, this.HandleDragEnd);
		this._button_down = false;
		this._drag_begin_x = 0;
		this._drag_begin_y = 0;
		this._btn_drag = false;
		this._can_drag_trans = true;
		this._can_set_drag_trans = true;
	},
	set can_drag_trans(value) {
		if (this._can_set_drag_trans === false) {
			return;
		}
		this._can_drag_trans = value;
	},
	get can_drag_trans() {
		return this._can_drag_trans;
	},
	HandleDragBegin : function(event) {
		this._drag_begin_x = event.abs_x;
		this._drag_begin_y = event.abs_y;
	},
	HandleDrag : function(event) {
		if (this._btn_drag === false) {
			if (__abs(event.abs_x - this._drag_begin_x) > 2 || __abs(event.abs_y - this._drag_begin_y) > 2) {
				this._button_down = false;
				this.ShowUp(undefined);
				let e = {};
				e.target = this;
				e.delta_x = event.delta_x;
				e.delta_y = event.delta_y;
				e.abs_x = event.abs_x;
				e.abs_y = event.abs_y;
				this.DispatchEvent(___all_struct.get(-2129379001), e);
				this._can_set_drag_trans = false;
				if (this._can_drag_trans && this._trans_target.get("drag") !== undefined) {
					let ue = {};
					ue.target = this._trans_target.get("drag");
					ue.delta_x = event.delta_x;
					ue.delta_y = event.delta_y;
					ue.abs_x = event.abs_x;
					ue.abs_y = event.abs_y;
					this._trans_target.get("drag").DispatchEvent(___all_struct.get(-2129379001), e);
				}
				this._btn_drag = true;
			}
		} else if (this._btn_drag === true) {
			let e = {};
			e.target = this;
			e.delta_x = event.delta_x;
			e.delta_y = event.delta_y;
			e.abs_x = event.abs_x;
			e.abs_y = event.abs_y;
			this.DispatchEvent(___all_struct.get(-646882501), e);
			if (this._can_drag_trans && this._trans_target.get("drag") !== undefined) {
				let ue = {};
				ue.target = this._trans_target.get("drag");
				ue.delta_x = event.delta_x;
				ue.delta_y = event.delta_y;
				ue.abs_x = event.abs_x;
				ue.abs_y = event.abs_y;
				this.DispatchEvent(___all_struct.get(-646882501), e);
			}
		}
	},
	HandleDragEnd : function(event) {
		if (this._btn_drag) {
			if (this._can_drag_trans && this._trans_target.get("drag") !== undefined) {
				let e = {};
				e.target = this._trans_target.get("drag");
				e.delta_x = event.delta_x;
				e.delta_y = event.delta_y;
				e.abs_x = event.abs_x;
				e.abs_y = event.abs_y;
				this._trans_target.get("drag").DispatchEvent(___all_struct.get(150587926), e);
			}
			this._can_set_drag_trans = true;
			let e = {};
			e.target = this;
			e.delta_x = event.delta_x;
			e.delta_y = event.delta_y;
			e.abs_x = event.abs_x;
			e.abs_y = event.abs_y;
			this.DispatchEvent(___all_struct.get(2101017097), e);
		}
	},
	HandleLButtonDown : function(event) {
		this._drag_begin_x = 0;
		this._drag_begin_y = 0;
		this._btn_drag = false;
		this._button_down = true;
		this._button_down_loop = ALittle.NewObject(ALittle.LoopFunction, this.HandleLButtonDownFunc.bind(this, undefined), 1, 0, 100);
		A_LoopSystem.AddUpdater(this._button_down_loop);
	},
	HandleLButtonUp : function(event) {
		if (this._btn_drag) {
			return;
		}
		if (this._button_down === false) {
			this.HandleLButtonUpFunc(event);
		} else {
			this.ShowDown();
			this._button_up_loop = ALittle.NewObject(ALittle.LoopFunction, this.HandleLButtonUpFunc.bind(this, event), 1, 0, 60);
			this._button_up_loop.Start();
		}
	},
	DispatchEvent : function(T, event) {
		let rflt = T;
		let event_target = this;
		if (this._trans_target.get("event") !== undefined) {
			event_target = this._trans_target.get("event");
		}
		if (event_target._abs_disabled) {
			return;
		}
		if (event_target._abs_disabled) {
			return;
		}
		let callback_table = event_target._listeners[rflt.name];
		if (callback_table === undefined) {
			return;
		}
		for (let [object, callback_value] of callback_table) {
			if (callback_value === undefined) continue;
			for (let [func, _] of callback_value) {
				if (_ === undefined) continue;
				func(object, event);
			}
		}
	},
	HandleLButtonDownFunc : function(event) {
		if (this._button_down === true) {
			this.ShowDown();
			this._button_down = false;
		}
		A_LoopSystem.RemoveUpdater(this._button_down_loop);
	},
	HandleLButtonUpFunc : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let e = {};
			e.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(-449066808), e);
			if (ALittle.System_IsPhone === false) {
				this.ShowOver();
			} else {
				this.ShowUp(undefined);
			}
		} else {
			this.ShowUp(undefined);
		}
		A_LoopSystem.RemoveUpdater(this._button_up_loop);
	},
}, "ALittle.ScrollButton");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.SpringTextButton = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._show_text = ({});
		this._show_text.width = 0;
		this._show_text.height = 0;
		this._show_text.text = "";
		this._show_text.visible = true;
		this._show_disabled_text = ({});
		this._show_disabled_text.width = 0;
		this._show_disabled_text.height = 0;
		this._show_disabled_text.text = "";
		this._show_disabled_text.visible = false;
		this._big_or_small = false;
		this._file_select = false;
		this.AddEventListener(___all_struct.get(544684311), this, this.HandleMoveIn);
		this.AddEventListener(___all_struct.get(-1202439334), this, this.HandleMoveOut);
		this.AddEventListener(___all_struct.get(1883782801), this, this.HandleLButtonDown);
		this.AddEventListener(___all_struct.get(40651933), this, this.HandleLButtonUp);
		this.AddEventListener(___all_struct.get(349963892), this, this.HandleMButtonDown);
		this.AddEventListener(___all_struct.get(683647260), this, this.HandleMButtonUp);
		this.AddEventListener(___all_struct.get(292776509), this, this.ShowUp);
		this.AddEventListener(___all_struct.get(-1233353463), this, this.HandleFButtonDown);
		this.AddEventListener(___all_struct.get(734860930), this, this.HandleFButtonUp);
		this._pickup_rect = true;
		this._pickup_child = false;
	},
	set disabled(value) {
		ALittle.DisplayObject.__setter.disabled.call(this, value);
		if (value) {
			this.ShowDisabled();
		} else {
			this.ShowUp(undefined);
		}
	},
	HandleMoveIn : function(event) {
		this.ShowOver();
	},
	HandleMoveOut : function(event) {
		this.ShowUp(undefined);
	},
	HandleLButtonDown : function(event) {
		this.ShowDown();
	},
	HandleLButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let e = {};
			e.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(-449066808), e);
			if (this._file_select) {
				A_OtherSystem.SystemSelectFile(this);
			}
			if (ALittle.System_IsPhone === false) {
				this.ShowOver();
			} else {
				this.ShowUp(undefined);
			}
		} else {
			this.ShowUp(undefined);
		}
	},
	HandleMButtonDown : function(event) {
		this.ShowDown();
	},
	HandleMButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let e = {};
			e.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(-1330840), e);
			if (ALittle.System_IsPhone === false) {
				this.ShowOver();
			} else {
				this.ShowUp(undefined);
			}
		} else {
			this.ShowUp(undefined);
		}
	},
	HandleFButtonDown : function(event) {
		if (event.is_sfc === false) {
			this.ShowDown();
		}
	},
	HandleFButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let e = {};
			e.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(286797479), e);
		}
		if (event.is_sfc === false) {
			this.ShowUp(undefined);
		}
	},
	set text(value) {
		this._show_text.text = value;
		this._show_disabled_text.text = value;
	},
	get text() {
		return this._show_text.text;
	},
	ShowUp : function(event) {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._show_up !== undefined) {
			this._show_up.alpha = 1;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 0;
		}
		this._show_text.visible = true;
		this._show_disabled_text.visible = false;
		this.ScaleTo(false, 200);
	},
	ShowDown : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._show_up !== undefined) {
			this._show_up.alpha = 1;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 0;
		}
		this._show_text.visible = true;
		this._show_disabled_text.visible = false;
		this.ScaleTo(true, 200);
	},
	ScaleTo : function(big_or_small, time_in_ms) {
		if (this._big_or_small === big_or_small) {
			return;
		}
		this._big_or_small = big_or_small;
		let scale = 1.0;
		if (this._big_or_small) {
			scale = 1.2;
		}
		if (this._anti_loop !== undefined) {
			this._anti_loop.Stop();
			this._anti_loop = undefined;
		}
		this._anti_loop = ALittle.NewObject(ALittle.LoopGroup);
		this._anti_loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this, "scale_x", scale, time_in_ms, 1));
		this._anti_loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this, "scale_y", scale, time_in_ms, 1));
		this._anti_loop.Start();
	},
	ShowOver : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._show_up !== undefined) {
			this._show_up.alpha = 1;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 0;
		}
		this._show_text.visible = true;
		this._show_disabled_text.visible = false;
		this.ScaleTo(false, 200);
	},
	ShowDisabled : function() {
		this.ScaleTo(false, 200);
		if (this._show_up !== undefined) {
			this._show_up.alpha = 0;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 1;
		}
		this._show_text.visible = false;
		this._show_disabled_text.visible = true;
	},
	set show_text(value) {
		if (value === undefined) {
			let show = this._show_text;
			this.RemoveChild(show);
			this._show_text = ({});
			this._show_text.width = 0;
			this._show_text.height = 0;
			this._show_text.text = show.text;
			this._show_text.visible = show.visible;
			return;
		}
		value.text = this._show_text.text;
		value.visible = this._show_text.visible;
		this.RemoveChild(this._show_text);
		this._show_text = value;
		this._show_text.x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this._show_text.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this.AddChild(this._show_text, 6);
	},
	get show_text() {
		if (this._show_text._show === undefined) {
			return undefined;
		}
		return this._show_text;
	},
	set show_disabled_text(value) {
		if (value === undefined) {
			let show = this._show_disabled_text;
			this.RemoveChild(show);
			this._show_disabled_text = ({});
			this._show_disabled_text.width = 0;
			this._show_disabled_text.height = 0;
			this._show_disabled_text.text = show.text;
			this._show_disabled_text.visible = show.visible;
			return;
		}
		value.text = this._show_disabled_text.text;
		value.visible = this._show_disabled_text.visible;
		this.RemoveChild(this._show_disabled_text);
		this._show_disabled_text = value;
		this._show_disabled_text.x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this._show_disabled_text.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		this.AddChild(this._show_disabled_text, 6);
	},
	get show_disabled_text() {
		if (this._show_disabled_text._show === undefined) {
			return undefined;
		}
		return this._show_disabled_text;
	},
	set show_up(value) {
		this.RemoveChild(this._show_up);
		this._show_up = value;
		if (this._show_up !== undefined) {
			this._show_up.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_up.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_up.width_value = 0;
			this._show_up.height_value = 0;
			this.AddChild(this._show_up, 1);
		}
		if (this._abs_disabled || this._disabled) {
			this.ShowDisabled();
		} else {
			this.ShowUp(undefined);
		}
	},
	get show_up() {
		return this._show_up;
	},
	set show_disabled(value) {
		this.RemoveChild(this._show_disabled);
		this._show_disabled = value;
		if (this._show_disabled !== undefined) {
			this._show_disabled.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_disabled.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
			this._show_disabled.width_value = 0;
			this._show_disabled.height_value = 0;
			this.AddChild(this._show_disabled, 1);
		}
		if (this._abs_disabled || this._disabled) {
			this.ShowDisabled();
		} else {
			this.ShowUp(undefined);
		}
	},
	get show_disabled() {
		return this._show_disabled;
	},
	set file_select(value) {
		this._file_select = value;
	},
	get file_select() {
		return this._file_select;
	},
}, "ALittle.SpringTextButton");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.SpringButton = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._big_or_small = false;
		this.AddEventListener(___all_struct.get(544684311), this, this.HandleMoveIn);
		this.AddEventListener(___all_struct.get(-1202439334), this, this.HandleMoveOut);
		this.AddEventListener(___all_struct.get(1883782801), this, this.HandleLButtonDown);
		this.AddEventListener(___all_struct.get(40651933), this, this.HandleLButtonUp);
		this.AddEventListener(___all_struct.get(349963892), this, this.HandleMButtonDown);
		this.AddEventListener(___all_struct.get(683647260), this, this.HandleMButtonUp);
		this.AddEventListener(___all_struct.get(292776509), this, this.ShowUp);
		this.AddEventListener(___all_struct.get(-1233353463), this, this.HandleFButtonDown);
		this.AddEventListener(___all_struct.get(734860930), this, this.HandleFButtonUp);
		this._pickup_rect = true;
		this._pickup_child = false;
	},
	get text() {
		if (this._show_text === undefined) {
			return "";
		}
		return this._show_text.text;
	},
	set text(text) {
		if (this._show_text === undefined) {
			return;
		}
		this._show_text.text = text;
	},
	set disabled(value) {
		ALittle.DisplayObject.__setter.disabled.call(this, value);
		if (value) {
			this.ShowDisabled();
		} else {
			this.ShowUp(undefined);
		}
	},
	HandleMoveIn : function(event) {
		this.ShowOver();
	},
	HandleMoveOut : function(event) {
		this.ShowUp(undefined);
	},
	HandleLButtonDown : function(event) {
		this.ShowDown();
	},
	HandleLButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let e = {};
			e.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(-449066808), e);
			if (ALittle.System_IsPhone === false) {
				this.ShowOver();
			} else {
				this.ShowUp(undefined);
			}
		} else {
			this.ShowUp(undefined);
		}
	},
	HandleMButtonDown : function(event) {
		this.ShowDown();
	},
	HandleMButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let e = {};
			e.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(-1330840), e);
			if (ALittle.System_IsPhone === false) {
				this.ShowOver();
			} else {
				this.ShowUp(undefined);
			}
		} else {
			this.ShowUp(undefined);
		}
	},
	HandleFButtonDown : function(event) {
		if (event.is_sfc === false) {
			this.ShowDown();
		}
	},
	HandleFButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let e = {};
			e.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(286797479), e);
		}
		if (event.is_sfc === false) {
			this.ShowUp(undefined);
		}
	},
	ScaleTo : function(big_or_small, time_in_ms) {
		if (this._big_or_small === big_or_small) {
			return;
		}
		this._big_or_small = big_or_small;
		let scale = 1.0;
		if (this._big_or_small) {
			scale = 1.2;
		}
		if (this._anti_loop !== undefined) {
			this._anti_loop.Stop();
			this._anti_loop = undefined;
		}
		this._anti_loop = ALittle.NewObject(ALittle.LoopGroup);
		this._anti_loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this, "scale_x", scale, time_in_ms, 1));
		this._anti_loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this, "scale_y", scale, time_in_ms, 1));
		this._anti_loop.Start();
	},
	ShowUp : function(event) {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._show_up !== undefined) {
			this._show_up.visible = true;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.visible = false;
		}
		this.ScaleTo(false, 200);
	},
	ShowDown : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._show_up !== undefined) {
			this._show_up.visible = true;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.visible = false;
		}
		this.ScaleTo(true, 200);
	},
	ShowOver : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._show_up !== undefined) {
			this._show_up.visible = true;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.visible = false;
		}
		this.ScaleTo(false, 200);
	},
	ShowDisabled : function() {
		this.ScaleTo(false, 200);
		if (this._show_up !== undefined) {
			this._show_up.visible = false;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.visible = true;
		} else {
			this._show_up.visible = true;
		}
	},
}, "ALittle.SpringButton");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.SpringCheckButton = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._big_or_small = false;
		this._selected = false;
		this.AddEventListener(___all_struct.get(544684311), this, this.HandleMoveIn);
		this.AddEventListener(___all_struct.get(-1202439334), this, this.HandleMoveOut);
		this.AddEventListener(___all_struct.get(1883782801), this, this.HandleLButtonDown);
		this.AddEventListener(___all_struct.get(40651933), this, this.HandleLButtonUp);
		this.AddEventListener(___all_struct.get(349963892), this, this.HandleMButtonDown);
		this.AddEventListener(___all_struct.get(683647260), this, this.HandleMButtonUp);
		this._pickup_rect = true;
		this._pickup_child = false;
	},
	set disabled(value) {
		ALittle.DisplayObject.__setter.disabled.call(this, value);
		if (this._abs_disabled) {
			this.ShowDisabled();
		} else {
			this.ShowUp();
		}
	},
	HandleMoveIn : function(event) {
		this.ShowOver();
	},
	HandleMoveOut : function(event) {
		this.ShowUp();
	},
	HandleLButtonDown : function(event) {
		this.ShowDown();
	},
	HandleLButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			this._selected = (this._selected === false);
			let e = {};
			e.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(-449066808), e);
			this.DispatchEvent(___all_struct.get(958494922), {});
			if (ALittle.System_IsPhone === false) {
				this.ShowOver();
			} else {
				this.ShowUp();
			}
		} else {
			this.ShowUp();
		}
	},
	HandleMButtonDown : function(event) {
		this.ShowDown();
	},
	HandleMButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			let e = {};
			e.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(-1330840), e);
			if (ALittle.System_IsPhone === false) {
				this.ShowOver();
			} else {
				this.ShowUp();
			}
		} else {
			this.ShowUp();
		}
	},
	set selected(value) {
		if (this._selected === value) {
			return;
		}
		this._selected = value;
		if (this._abs_disabled) {
			this.ShowDisabled();
		} else {
			this.ShowUp();
		}
	},
	get selected() {
		return this._selected;
	},
	ScaleTo : function(big_or_small, time_in_ms) {
		if (this._big_or_small === big_or_small) {
			return;
		}
		this._big_or_small = big_or_small;
		let scale = 1.0;
		if (this._big_or_small) {
			scale = 1.2;
		}
		if (this._anti_loop !== undefined) {
			this._anti_loop.Stop();
			this._anti_loop = undefined;
		}
		this._anti_loop = ALittle.NewObject(ALittle.LoopGroup);
		this._anti_loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this, "scale_x", scale, time_in_ms, 1));
		this._anti_loop.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this, "scale_y", scale, time_in_ms, 1));
		this._anti_loop.Start();
	},
	ShowUp : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._selected) {
			if (this._show_selected_up !== undefined) {
				this._show_selected_up.visible = true;
			}
			if (this._show_up !== undefined) {
				this._show_up.visible = false;
			}
		} else {
			if (this._show_selected_up !== undefined) {
				this._show_selected_up.visible = false;
			}
			if (this._show_up !== undefined) {
				this._show_up.visible = true;
			}
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.visible = false;
		}
		this.ScaleTo(false, 200);
	},
	ShowDown : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._selected) {
			if (this._show_selected_up !== undefined) {
				this._show_selected_up.visible = true;
			}
			if (this._show_up !== undefined) {
				this._show_up.visible = false;
			}
		} else {
			if (this._show_selected_up !== undefined) {
				this._show_selected_up.visible = false;
			}
			if (this._show_up !== undefined) {
				this._show_up.visible = true;
			}
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.visible = false;
		}
		this.ScaleTo(true, 200);
	},
	ShowOver : function() {
		if (this._abs_disabled || this._disabled) {
			return;
		}
		if (this._selected) {
			if (this._show_selected_up !== undefined) {
				this._show_selected_up.visible = true;
			}
			if (this._show_up !== undefined) {
				this._show_up.visible = false;
			}
		} else {
			if (this._show_selected_up !== undefined) {
				this._show_selected_up.visible = false;
			}
			if (this._show_up !== undefined) {
				this._show_up.visible = true;
			}
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.alpha = 0;
		}
		this.ScaleTo(false, 200);
	},
	ShowDisabled : function() {
		this.ScaleTo(false, 200);
		if (this._show_up !== undefined) {
			this._show_up.visible = false;
		}
		if (this._show_selected_up !== undefined) {
			this._show_selected_up.visible = false;
		}
		if (this._show_disabled !== undefined) {
			this._show_disabled.visible = true;
		} else {
			if (this._selected) {
				this._show_selected_up.visible = true;
			} else {
				this._show_up.visible = true;
			}
		}
	},
}, "ALittle.SpringCheckButton");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.DisplayLayout === undefined) throw new Error(" extends class:ALittle.DisplayLayout is undefined");
ALittle.SpringDialog = JavaScript.Class(ALittle.DisplayLayout, {
	Ctor : function(ctrl_sys) {
		this._is_show = false;
		this.visible = false;
	},
	get show() {
		return this._is_show;
	},
	set show(value) {
		if (this._is_show === value) {
			return;
		}
		this._is_show = value;
		if (this._anti_loop !== undefined) {
			this._anti_loop.SetCompleted();
			this._anti_loop.Stop();
			this._anti_loop = undefined;
		}
		if (value) {
			this.ShowAnti(1.1, 200, 200);
		} else {
			this.HideAnti(1.1, 200);
		}
	},
	ShowAnti : function(scale, scale_big_ms, scale_return_ms) {
		if (this._show_dialog === undefined) {
			return;
		}
		this.visible = true;
		this.alpha = 0;
		this._show_dialog.scale_x = 1;
		this._show_dialog.scale_y = 1;
		this._anti_loop = ALittle.NewObject(ALittle.LoopList);
		let group = ALittle.NewObject(ALittle.LoopGroup);
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._show_dialog, "scale_x", scale, scale_big_ms, 1));
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._show_dialog, "scale_y", scale, scale_big_ms, 1));
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this, "alpha", 1, scale_big_ms, 1));
		this._anti_loop.AddUpdater(group);
		group = ALittle.NewObject(ALittle.LoopGroup);
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._show_dialog, "scale_x", 1, scale_return_ms, 1));
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._show_dialog, "scale_y", 1, scale_return_ms, 1));
		this._anti_loop.AddUpdater(group);
		this._anti_loop.Start();
	},
	HideAnti : function(scale, scale_big_ms) {
		if (this._show_dialog === undefined) {
			return;
		}
		this._anti_loop = ALittle.NewObject(ALittle.LoopList);
		let group = ALittle.NewObject(ALittle.LoopGroup);
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._show_dialog, "scale_x", scale, scale_big_ms, 1));
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this._show_dialog, "scale_y", scale, scale_big_ms, 1));
		group.AddUpdater(ALittle.NewObject(ALittle.LoopLinear, this, "alpha", 0, scale_big_ms, 1));
		this._anti_loop.AddUpdater(group);
		this._anti_loop.AddUpdater(ALittle.NewObject(ALittle.LoopAttribute, this, "visible", false, 1));
		this._anti_loop.Start();
	},
}, "ALittle.SpringDialog");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


if (ALittle.SpringCheckButton === undefined) throw new Error(" extends class:ALittle.SpringCheckButton is undefined");
ALittle.SpringRadioButton = JavaScript.Class(ALittle.SpringCheckButton, {
	Ctor : function(ctrl_sys) {
		this._cancel_select = false;
	},
	set group(group) {
		if (this._group === group) {
			return;
		}
		if (this._group !== undefined) {
			this._group.delete(this);
		}
		this._group = group;
		if (this._group !== undefined) {
			this._group.set(this, true);
		}
	},
	get group() {
		return this._group;
	},
	SetGroup : function(list) {
		let group = ALittle.CreateKeyWeakMap();
		let ___OBJECT_1 = list;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let button = ___OBJECT_1[index - 1];
			if (button === undefined) break;
			if (button._group !== undefined) {
				button._group.delete(button);
			}
			button._group = group;
			group.set(button, true);
		}
	},
	set cancel_select(value) {
		this._cancel_select = value;
	},
	get cancel_select() {
		return this._cancel_select;
	},
	HandleLButtonUp : function(event) {
		if (event.rel_x >= 0 && event.rel_y >= 0 && event.rel_x < event.target._width && event.rel_y < event.target._height) {
			if (this._selected === false) {
				this._selected = true;
				if (this._group !== undefined) {
					for (let [k, _] of this._group) {
						if (_ === undefined) continue;
						if (k !== this && k._selected === true) {
							k._selected = false;
							k.ShowUp();
							k.DispatchEvent(___all_struct.get(958494922), {});
						}
					}
				}
				this.DispatchEvent(___all_struct.get(958494922), {});
			} else if (this._cancel_select) {
				this._selected = false;
				this.DispatchEvent(___all_struct.get(958494922), {});
			}
			let e = {};
			e.is_drag = event.is_drag;
			this.DispatchEvent(___all_struct.get(-449066808), e);
			if (ALittle.System_IsPhone === false) {
				this.ShowOver();
			} else {
				this.ShowUp();
			}
		} else {
			this.ShowUp();
		}
	},
	set selected(value) {
		if (this._selected === value) {
			return;
		}
		this._selected = value;
		if (this._abs_disabled) {
			this.ShowDisabled();
		} else {
			this.ShowUp();
		}
		if (this._selected === false) {
			return;
		}
		if (this._group !== undefined) {
			for (let [k, _] of this._group) {
				if (_ === undefined) continue;
				if (k !== this && k._selected === true) {
					k._selected = false;
					k.ShowUp();
				}
			}
		}
	},
}, "ALittle.SpringRadioButton");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


if (ALittle.DisplayObject === undefined) throw new Error(" extends class:ALittle.DisplayObject is undefined");
ALittle.EffectImage = JavaScript.Class(ALittle.DisplayObject, {
	Ctor : function(ctrl_sys) {
	},
	Action : function(control) {
		if (control === undefined) {
			return;
		}
		this._show = ALittle.NewObject(lua.__CPPAPIImage);
		this._texture = ALittle.NewObject(lua.__CPPAPIRenderTexture);
		this.x = control.x;
		this.y = control.y;
		this.width = control.width;
		this.height = control.height;
		control._show.SetX(0);
		control._show.SetY(0);
		control.visible = true;
		control.clip = false;
		let result = this._texture.Draw(control._show, lua.math.floor(this.width), lua.math.floor(this.height), 1);
		control._show.SetX(this._x);
		control._show.SetY(this._y);
		if (result) {
			this._show.SetTexture(this._texture);
		}
		this._show.SetTextureCoord(0, 1, 0, 1);
		this.disabled = true;
	},
	Clear : function() {
		if (this._texture === undefined) {
			return;
		}
		this._texture.Clear();
	},
}, "ALittle.EffectImage");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();

ALittle.RegStruct(1031172931, "ALittle.FingerInfo", {
name : "ALittle.FingerInfo", ns_name : "ALittle", rl_name : "FingerInfo", hash_code : 1031172931,
name_list : ["key","mouse_x","mouse_y","last_mouse_x","last_mouse_y","dl","mfc","mfc_rel_x","mfc_rel_y","is_sfc"],
type_list : ["string","double","double","double","double","bool","ALittle.DisplayObject","double","double","bool"],
option_map : {}
})

let __abs = ALittle.Math_Abs;
ALittle.UISystem = JavaScript.Class(undefined, {
	Ctor : function() {
		this._view_width = 0;
		this._view_height = 0;
		this._mouse_x = 0;
		this._mouse_y = 0;
		this._last_mouse_x = 0;
		this._last_mouse_y = 0;
		this._lbutton_down = false;
		this._lbutton_finger_id = undefined;
		this._lbutton_touch_id = undefined;
		this._mfc = undefined;
		this._mfc_rel_x = 0;
		this._mfc_rel_y = 0;
		this._mfd = undefined;
		this._sfc = undefined;
		this._wfc = undefined;
		this._pfc = undefined;
		this._button_type = undefined;
		this._sl = false;
		this._dl = false;
		this._dl_delta_x = 0;
		this._dl_delta_y = 0;
		this._max_dl_delta = 10;
		this._max_lp_delta = 2;
		if (ALittle.System_GetPlatform() === "Windows") {
			this._max_dl_delta = 1;
			this._max_lp_delta = 0;
		}
		this._ime_editing = false;
		this._ime_editing_callback = undefined;
		this._sym_map = new Map();
		this._keydown_callback = undefined;
		this._view_resize_callback = undefined;
		this._long_press = undefined;
		this._finger_info = {};
	},
	set view_resize_callback(value) {
		this._view_resize_callback = value;
	},
	get view_resize_callback() {
		return this._view_resize_callback;
	},
	set keydown_callback(value) {
		this._keydown_callback = value;
	},
	get keydown_callback() {
		return this._keydown_callback;
	},
	get sym_map() {
		return this._sym_map;
	},
	set ime_callback(value) {
		this._ime_editing_callback = value;
	},
	get ime_callback() {
		return this._ime_editing_callback;
	},
	get mouse_x() {
		return this._mouse_x;
	},
	get mouse_y() {
		return this._mouse_y;
	},
	set focus(control) {
		if (this._sfc === control) {
			return;
		}
		this._wfc = undefined;
		if (this._sfc !== undefined) {
			if (this._dl === true) {
				this._dl = false;
				this._dl_delta_x = 0;
				this._dl_delta_y = 0;
				if (this._button_type === "ALittle.UILButtonDownEvent") {
					let event = {};
					event.target = this._sfc;
					event.rel_x = this._mfc_rel_x;
					event.rel_y = this._mfc_rel_y;
					if (this._mfc !== this._sfc) {
						[event.rel_x, event.rel_y] = this._sfc.GlobalToLocalMatrix2D(this._mouse_x, this._mouse_y);
					}
					event.delta_x = this._mouse_x - this._last_mouse_x;
					event.delta_y = this._mouse_y - this._last_mouse_y;
					event.abs_x = this._mouse_x;
					event.abs_y = this._mouse_y;
					this._sfc.DispatchEvent(___all_struct.get(150587926), event);
				}
			}
			let sfc = this._sfc;
			if (this._ime_editing_callback !== undefined) {
				this._ime_editing_callback(false, undefined, undefined, undefined, undefined);
			}
			this._sfc = undefined;
			this._sl = false;
			sfc.DispatchEvent(___all_struct.get(292776509), {});
		}
		this._sfc = control;
		if (this._sfc !== undefined) {
			this._sfc.DispatchEvent(___all_struct.get(-644464135), {});
		}
	},
	get focus() {
		return this._sfc;
	},
	set pick(control) {
		if (this._pfc !== undefined) {
			A_LayerManager.RemoveFromTip(this._pfc);
		}
		this._pfc = control;
		if (this._pfc !== undefined) {
			A_LayerManager.AddToTip(this._pfc);
		}
	},
	get pick() {
		return this._pfc;
	},
	get view_width() {
		return this._view_width;
	},
	get view_height() {
		return this._view_height;
	},
	HandleMouseMoved : function(x, y) {
		let delta_x = x - this._mouse_x;
		let delta_y = y - this._mouse_y;
		this._last_mouse_x = this._mouse_x;
		this._last_mouse_y = this._mouse_y;
		this._mouse_x = x;
		this._mouse_y = y;
		if (this._long_press !== undefined && __abs(delta_x) <= this._max_lp_delta && __abs(delta_y) <= this._max_lp_delta) {
			return false;
		}
		if (this._long_press !== undefined) {
			this._long_press.Stop();
			this._long_press = undefined;
		}
		if (this._pfc !== undefined) {
			this._pfc.x = this._pfc.x + (delta_x);
			this._pfc.y = this._pfc.y + (delta_y);
		}
		if (this._sl && this._button_type === "ALittle.UILButtonDownEvent") {
			if (this._dl === true) {
				let event = {};
				event.target = this._sfc;
				[event.rel_x, event.rel_y] = this._sfc.GlobalToLocalMatrix2D(x, y);
				if (this._dl_delta_x > 0) {
					delta_x = this._dl_delta_x + delta_x;
					this._dl_delta_x = 0;
				}
				if (this._dl_delta_y > 0) {
					delta_y = this._dl_delta_y + delta_y;
					this._dl_delta_y = 0;
				}
				event.abs_x = x;
				event.abs_y = y;
				event.delta_x = delta_x;
				event.delta_y = delta_y;
				this._sfc.DispatchEvent(___all_struct.get(1337289812), event);
				return true;
			}
			if (this._dl === false) {
				this._dl_delta_x = this._dl_delta_x + (delta_x);
				this._dl_delta_y = this._dl_delta_y + (delta_y);
				if (__abs(this._dl_delta_x) >= this._max_dl_delta || __abs(this._dl_delta_y) >= this._max_dl_delta) {
					this._dl = true;
					let event = {};
					event.target = this._sfc;
					[event.rel_x, event.rel_y] = this._sfc.GlobalToLocalMatrix2D(this._mouse_x, this._mouse_y);
					event.abs_x = x;
					event.abs_y = y;
					event.delta_x = this._dl_delta_x;
					event.delta_y = this._dl_delta_y;
					this._sfc.DispatchEvent(___all_struct.get(1301789264), event);
				}
			}
			return true;
		}
		this.UpdateMoveFocus(x, y);
		return this._mfc !== undefined;
	},
	HandleLButtonDown : function(x, y, count) {
		this._lbutton_down = true;
		this._lbutton_finger_id = undefined;
		this._lbutton_touch_id = undefined;
		return this.HandleButtonDown(___all_struct.get(1883782801), x, y, count);
	},
	HandleLButtonUp : function(x, y) {
		this._lbutton_down = false;
		return this.HandleButtonUp(___all_struct.get(40651933), x, y);
	},
	HandleMButtonDown : function(x, y, count) {
		return this.HandleButtonDown(___all_struct.get(349963892), x, y, count);
	},
	HandleMButtonUp : function(x, y) {
		return this.HandleButtonUp(___all_struct.get(683647260), x, y);
	},
	HandleButtonDown : function(T, x, y, count) {
		let rflt = T;
		this._wfc = undefined;
		A_LayerManager.HandleLRButtonDown(x, y);
		this.UpdateMoveFocus(x, y);
		if (this._mfc !== undefined) {
			this._sl = true;
			this._button_type = rflt.name;
			if (this._pfc !== undefined && rflt.name === "ALittle.UILButtonDownEvent") {
				let event = {};
				event.target = this._mfc;
				event.drop_target = this._pfc;
				this._mfc.DispatchEvent(___all_struct.get(1354499457), event);
				A_LayerManager.RemoveFromTip(this._pfc);
				this._pfc = undefined;
			}
			if (this._mfd !== undefined) {
				let layer = this._mfd.show_parent;
				layer.SetChildIndex(this._mfd, layer.child_count);
			}
			let event = {};
			event.target = this._mfc;
			event.abs_x = x;
			event.abs_y = y;
			event.rel_x = this._mfc_rel_x;
			event.rel_y = this._mfc_rel_y;
			event.count = count;
			event.is_drag = false;
			this._mfc.DispatchEvent(T, event);
			if (rflt.name === "ALittle.UILButtonDownEvent") {
				if (this._long_press !== undefined) {
					this._long_press.Stop();
				}
				let long_event = {};
				long_event.target = this._mfc;
				long_event.abs_x = x;
				long_event.abs_y = y;
				long_event.rel_x = this._mfc_rel_x;
				long_event.rel_y = this._mfc_rel_y;
				long_event.is_drag = false;
				this._long_press = ALittle.NewObject(ALittle.LoopFunction, ALittle.UISystem.DispatchLongButtonEvent.bind(undefined, this._mfc, long_event), 1, 500, 1);
				this._long_press.Start();
			}
			if (this._sfc === undefined) {
				this._sfc = this._mfc;
				this._sfc.DispatchEvent(___all_struct.get(-644464135), {});
			} else if (this._mfc !== this._sfc) {
				this._sfc.DispatchEvent(___all_struct.get(292776509), {});
				if (this._ime_editing_callback !== undefined) {
					this._ime_editing_callback(false, undefined, undefined, undefined, undefined);
				}
				this._sfc = this._mfc;
				this._sfc.DispatchEvent(___all_struct.get(-644464135), {});
			}
			return true;
		} else {
			if (this._sfc !== undefined) {
				this._sfc.DispatchEvent(___all_struct.get(292776509), {});
				if (this._ime_editing_callback !== undefined) {
					this._ime_editing_callback(false, undefined, undefined, undefined, undefined);
				}
				this._sfc = undefined;
				this._sl = false;
			}
		}
		return false;
	},
	DispatchLongButtonEvent : function(mfc, event) {
		mfc.DispatchEvent(___all_struct.get(-439548260), event);
	},
	HandleButtonUp : function(T, x, y) {
		if (this._sl === false) {
			return false;
		}
		if (this._long_press !== undefined) {
			this._long_press.Stop();
			this._long_press = undefined;
		}
		this._sl = false;
		let [rel_x, rel_y] = this._sfc.GlobalToLocalMatrix2D(x, y);
		let save_dl = this._dl;
		if (this._dl === true) {
			this._dl = false;
			this._dl_delta_x = 0;
			this._dl_delta_y = 0;
			let event = {};
			event.target = this._sfc;
			event.abs_x = x;
			event.abs_y = y;
			event.delta_x = this._mouse_x - this._last_mouse_x;
			event.delta_y = this._mouse_y - this._last_mouse_y;
			event.rel_x = rel_x;
			event.rel_y = rel_y;
			this._sfc.DispatchEvent(___all_struct.get(150587926), event);
		}
		if (this._sfc !== undefined) {
			let event = {};
			event.target = this._sfc;
			event.abs_x = x;
			event.abs_y = y;
			event.rel_x = rel_x;
			event.rel_y = rel_y;
			event.is_drag = save_dl;
			this._sfc.DispatchEvent(T, event);
		}
		this.UpdateMoveFocus(x, y);
		return this._mfc !== undefined;
	},
	HandleRButtonDown : function(x, y, count) {
		A_LayerManager.HandleLRButtonDown(x, y);
		if (this._sl) {
			return false;
		}
		this.UpdateMoveFocus(x, y);
		if (this._mfc !== undefined) {
			let event = {};
			event.target = this._mfc;
			event.abs_x = x;
			event.abs_y = y;
			event.rel_x = this._mfc_rel_x;
			event.rel_y = this._mfc_rel_y;
			event.count = count;
			event.is_drag = false;
			this._mfc.DispatchEvent(___all_struct.get(-641444818), event);
			return true;
		}
		return false;
	},
	HandleRButtonUp : function(x, y) {
		return false;
	},
	HandleTextInput : function(text) {
		this._ime_editing = false;
		if (this._ime_editing_callback !== undefined) {
			this._ime_editing_callback(false, undefined, undefined, undefined, undefined);
		}
		if (this._sfc !== undefined) {
			let event = {};
			event.target = this._sfc;
			event.text = text;
			this._sfc.DispatchEvent(___all_struct.get(-1234078962), event);
			return true;
		}
		return false;
	},
	HandleTextEditing : function(text, start) {
		if (text === "") {
			if (this._ime_editing === false) {
				return;
			}
			this._ime_editing = false;
			if (this._ime_editing_callback !== undefined) {
				this._ime_editing_callback(false, undefined, undefined, undefined, undefined);
			}
		} else {
			this._ime_editing = true;
			if (this._sfc === undefined || this._sfc.is_input === false || this._sfc.editable === false || this._sfc.font_size === undefined) {
				return;
			}
			if (this._ime_editing_callback !== undefined) {
				let list = ALittle.String_Split(ALittle.System_GetIMESelectList(), " ");
				let new_list = [];
				let count = 0;
				let ___OBJECT_1 = list;
				for (let index = 1; index <= ___OBJECT_1.length; ++index) {
					let value = ___OBJECT_1[index - 1];
					if (value === undefined) break;
					if (value !== "") {
						++ count;
						new_list[count - 1] = value;
					}
				}
				this._ime_editing_callback(true, text, start, new_list, this._sfc);
				ALittle.System_SetIMEPos(ALittle.System_GetScreenWidth(), ALittle.System_GetScreenHeight());
			} else {
				let [abs_x, abs_y] = this._sfc.LocalToGlobal();
				abs_x = abs_x + (this._sfc.cursor_x);
				abs_y = abs_y + ((this._sfc.cursor_y + this._sfc.font_size) * this._sfc.scale_y);
				ALittle.System_SetIMEPos(lua.math.floor(abs_x), lua.math.floor(abs_y));
			}
		}
	},
	HandleKeyDown : function(mod, sym, scancode) {
		this._sym_map.set(sym, true);
		let result = false;
		if (ALittle.System_GetIMESelectList() === "" && this._ime_editing) {
			this._ime_editing = false;
			if (this._ime_editing_callback !== undefined) {
				this._ime_editing_callback(false, undefined, undefined, undefined, undefined);
			}
			return;
		}
		let event = {};
		event.target = this._sfc;
		event.mod = mod;
		event.sym = sym;
		event.scancode = scancode;
		if (this._sfc !== undefined && this._ime_editing === false) {
			this._sfc.DispatchEvent(___all_struct.get(-1604617962), event);
		}
		if (!event.handled && this._ime_editing === false && this._keydown_callback !== undefined) {
			this._keydown_callback(mod, sym, scancode);
		}
	},
	HandleKeyUp : function(mod, sym, scancode) {
		this._sym_map.delete(sym);
	},
	HandleMouseWheel : function(x, y) {
		if (this._mfc === undefined || this._sl) {
			return false;
		}
		if (this._wfc === undefined) {
			let control = this._mfc;
			while (control !== undefined) {
				if (control.can_scroll === true) {
					this._wfc = control;
					break;
				}
				control = control.show_parent;
			}
		}
		if (this._wfc !== undefined) {
			let event = {};
			event.target = this._wfc;
			event.delta_x = x;
			event.delta_y = y;
			this._wfc.DispatchEvent(___all_struct.get(-1737121315), event);
		}
		return true;
	},
	UpdateMoveFocus : function(x, y) {
		let mfc = undefined;
		let mfd = undefined;
		[mfc, mfd, this._mfc_rel_x, this._mfc_rel_y] = A_LayerManager.PickUp(x, y);
		this._mfd = mfd;
		if (this._mfc === mfc) {
			if (mfc !== undefined) {
				let event = {};
				event.target = mfc;
				event.abs_x = x;
				event.abs_y = y;
				event.rel_x = this._mfc_rel_x;
				event.rel_y = this._mfc_rel_y;
				mfc.DispatchEvent(___all_struct.get(-1001723540), event);
			}
			return;
		}
		if (this._mfc !== undefined) {
			this._mfc.DispatchEvent(___all_struct.get(-1202439334), {});
		}
		if (mfc !== undefined) {
			mfc.DispatchEvent(___all_struct.get(544684311), {});
		}
		this._mfc = mfc;
		this._wfc = undefined;
	},
	HandleViewResized : function(width, height) {
		if (this._view_width === width && this._view_height === height) {
			return;
		}
		this._view_width = width;
		this._view_height = height;
		A_LayerManager.HandleViewResized(width, height);
		if (this._view_resize_callback !== undefined) {
			this._view_resize_callback(width, height);
		}
	},
	HandleDropFile : function(path) {
		let x = ALittle.System_GetCursorX() - ALittle.System_GetViewX();
		let y = ALittle.System_GetCursorY() - ALittle.System_GetViewY();
		this.HandleMouseMoved(x, y);
		if (this._mfc === undefined) {
			return;
		}
		let event = {};
		event.target = this._mfc;
		event.path = path;
		this._mfc.DispatchEvent(___all_struct.get(-338112738), event);
	},
	HandleWindowEnter : function() {
	},
	HandleWindowLeave : function() {
		if (this._lbutton_down) {
			this.HandleLButtonUp(this._mouse_x, this._mouse_y);
		}
	},
	HandleFingerDown : function(x, y, finger_id, touch_id) {
		if (this._lbutton_down === false) {
			this._lbutton_down = true;
			this._lbutton_finger_id = finger_id;
			this._lbutton_touch_id = touch_id;
			this._mouse_x = x;
			this._mouse_y = y;
			return this.HandleButtonDown(___all_struct.get(1883782801), x, y, 1);
		}
		let key = finger_id + "_" + touch_id;
		let info = {};
		info.key = key;
		info.mouse_x = x;
		info.mouse_y = y;
		info.last_mouse_x = 0;
		info.last_mouse_y = 0;
		info.dl = false;
		info.mfc = undefined;
		info.mfc_rel_x = 0;
		info.mfc_rel_y = 0;
		info.is_sfc = false;
		let mfd = undefined;
		[info.mfc, mfd, info.mfc_rel_x, info.mfc_rel_y] = A_LayerManager.PickUp(x, y);
		if (info.mfc === undefined) {
			return false;
		}
		info.is_sfc = (this._sl && (info.mfc === this._mfc || info.mfc === this._sfc));
		let event = {};
		event.target = info.mfc;
		event.abs_x = x;
		event.abs_y = y;
		event.rel_x = info.mfc_rel_x;
		event.rel_y = info.mfc_rel_y;
		event.finger_key = info.key;
		event.is_sfc = info.is_sfc;
		event.is_drag = false;
		info.mfc.DispatchEvent(___all_struct.get(-1233353463), event);
		this._finger_info[key] = info;
		return true;
	},
	HandleFingerUp : function(x, y, finger_id, touch_id) {
		if (this._lbutton_down && this._lbutton_finger_id === finger_id && this._lbutton_touch_id === touch_id) {
			this._lbutton_down = false;
			return this.HandleButtonUp(___all_struct.get(40651933), x, y);
		}
		let key = finger_id + "_" + touch_id;
		let info = this._finger_info[key];
		if (info === undefined) {
			return false;
		}
		delete this._finger_info[key];
		info.last_mouse_x = info.mouse_x;
		info.last_mouse_y = info.mouse_y;
		info.mouse_x = x;
		info.mouse_y = y;
		let save_dl = info.dl;
		if (info.dl === true) {
			info.dl = false;
			let event = {};
			event.target = info.mfc;
			event.abs_x = x;
			event.abs_y = y;
			event.rel_x = info.mfc_rel_x;
			event.rel_y = info.mfc_rel_y;
			event.delta_x = info.mouse_x - info.last_mouse_x;
			event.delta_y = info.mouse_y - info.last_mouse_y;
			event.finger_key = key;
			event.is_sfc = info.is_sfc;
			info.mfc.DispatchEvent(___all_struct.get(-2050069067), event);
		}
		let event = {};
		event.target = info.mfc;
		event.abs_x = x;
		event.abs_y = y;
		event.rel_x = info.mfc_rel_x;
		event.rel_y = info.mfc_rel_y;
		event.finger_key = info.key;
		event.is_sfc = info.is_sfc;
		event.is_drag = save_dl;
		info.mfc.DispatchEvent(___all_struct.get(734860930), event);
		return true;
	},
	HandleFingerMoved : function(x, y, finger_id, touch_id) {
		if (this._lbutton_down && this._lbutton_finger_id === finger_id && this._lbutton_touch_id === touch_id) {
			return this.HandleMouseMoved(x, y);
		}
		let key = finger_id + "_" + touch_id;
		let info = this._finger_info[key];
		if (info === undefined) {
			return false;
		}
		let delta_x = x - info.mouse_x;
		let delta_y = y - info.mouse_y;
		info.last_mouse_x = info.mouse_x;
		info.last_mouse_y = info.mouse_y;
		info.mouse_x = x;
		info.mouse_y = y;
		if (info.mfc !== undefined) {
			[info.mfc_rel_x, info.mfc_rel_y] = info.mfc.GlobalToLocalMatrix2D(x, y);
		}
		if (info.dl === true) {
			let event = {};
			event.target = info.mfc;
			event.delta_x = delta_x;
			event.delta_y = delta_y;
			event.abs_x = x;
			event.abs_y = y;
			event.rel_x = info.mfc_rel_x;
			event.rel_y = info.mfc_rel_y;
			event.finger_key = info.key;
			event.is_sfc = info.is_sfc;
			info.mfc.DispatchEvent(___all_struct.get(-51419723), event);
			return true;
		}
		if (info.dl === false) {
			info.dl = true;
			let event = {};
			event.target = info.mfc;
			event.delta_x = delta_x;
			event.delta_y = delta_y;
			event.abs_x = x;
			event.abs_y = y;
			event.rel_x = info.mfc_rel_x;
			event.rel_y = info.mfc_rel_y;
			event.finger_key = info.key;
			event.is_sfc = info.is_sfc;
			info.mfc.DispatchEvent(___all_struct.get(1598008698), event);
			return true;
		}
		return false;
	},
}, "ALittle.UISystem");

window.A_UISystem = ALittle.NewObject(ALittle.UISystem);
}
{
if (typeof ALittle === "undefined") window.ALittle = {};
let ___all_struct = ALittle.GetAllStruct();


ALittle.LayerManager = JavaScript.Class(undefined, {
	Ctor : function() {
		this._normal_groups = [];
		this._normal_group_count = 0;
		this._modal_layer = ALittle.NewObject(ALittle.DisplayLayout, undefined);
		A_JDisplaySystem.AddSpecialChild(this._modal_layer.native_show);
		this._right_layer = ALittle.NewObject(ALittle.DisplayLayout, undefined);
		this._right_show = undefined;
		A_JDisplaySystem.AddSpecialChild(this._right_layer.native_show);
		this._tip_layer = ALittle.NewObject(ALittle.DisplayLayout, undefined);
		this._tip_layer.disabled = true;
		A_JDisplaySystem.AddSpecialChild(this._tip_layer.native_show);
	},
	Shutdown : function() {
		A_JDisplaySystem.RemoveAllChild();
	},
	get group_count() {
		return this._normal_group_count;
	},
	AddChild : function(child, index) {
		if (child === undefined) {
			return;
		}
		if (index === undefined || index > this._normal_group_count || this._normal_group_count < 1) {
			++ this._normal_group_count;
			this._normal_groups[this._normal_group_count - 1] = child;
			A_JDisplaySystem.AddChild(child.native_show);
		} else {
			if (index < 1) {
				index = 1;
			}
			let back_child = this._normal_groups[index - 1];
			A_JDisplaySystem.AddChildBefore(back_child.native_show, child.native_show);
			ALittle.List_Insert(this._normal_groups, index, child);
			++ this._normal_group_count;
		}
		child.width = A_UISystem.view_width;
		child.height = A_UISystem.view_height;
	},
	RemoveChild : function(child) {
		if (child === undefined) {
			return;
		}
		let has_layer = false;
		let ___OBJECT_1 = this._normal_groups;
		for (let index = 1; index <= ___OBJECT_1.length; ++index) {
			let value = ___OBJECT_1[index - 1];
			if (value === undefined) break;
			if (value === child) {
				ALittle.List_Remove(this._normal_groups, index);
				has_layer = true;
				break;
			}
		}
		if (has_layer === false) {
			return;
		}
		A_JDisplaySystem.RemoveChild(child.native_show);
		-- this._normal_group_count;
	},
	HandleViewResized : function(width, height) {
		let ___OBJECT_2 = this._normal_groups;
		for (let group_index = 1; group_index <= ___OBJECT_2.length; ++group_index) {
			let group = ___OBJECT_2[group_index - 1];
			if (group === undefined) break;
			group.width = width;
			group.height = height;
		}
		this._modal_layer.width = width;
		this._modal_layer.height = height;
		this._right_layer.width = width;
		this._right_layer.height = height;
		this._tip_layer.width = width;
		this._tip_layer.height = height;
		this.HideCurrentFromRight();
	},
	AddToModal : function(dialog, index) {
		if (dialog === undefined) {
			return;
		}
		dialog.x_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		dialog.x_value = 0;
		dialog.y_type = ALittle.UIEnumTypes.POS_ALIGN_CENTER;
		dialog.y_value = 0;
		dialog.modal = true;
		dialog.visible = false;
		this._modal_layer.AddChild(dialog, index);
	},
	RemoveFromModal : function(dialog) {
		if (dialog === undefined) {
			return;
		}
		dialog.modal = false;
		dialog.visible = true;
		this._modal_layer.RemoveChild(dialog);
	},
	ShowFromRight : function(dialog, focus) {
		if (focus === undefined) {
			focus = true;
		}
		if (this._right_show === dialog) {
			return;
		}
		if (this._right_show !== undefined) {
			this._right_show.DispatchEvent(___all_struct.get(348388800), {});
			this._right_layer.RemoveChild(this._right_show);
			this._right_show = undefined;
		}
		this._right_show = dialog;
		if (this._right_show !== undefined) {
			this._right_layer.AddChild(this._right_show);
			if (focus) {
				this._right_show.focus = true;
			}
			dialog.DispatchEvent(___all_struct.get(1862557463), {});
			dialog.visible = true;
		}
	},
	HideFromRight : function(dialog) {
		if (this._right_show !== dialog) {
			return;
		}
		if (this._right_show === undefined) {
			return;
		}
		this._right_show.DispatchEvent(___all_struct.get(348388800), {});
		this._right_layer.RemoveChild(this._right_show);
		this._right_show.focus = false;
		this._right_show = undefined;
	},
	HideCurrentFromRight : function() {
		if (this._right_show === undefined) {
			return false;
		}
		this.HideFromRight(this._right_show);
		return true;
	},
	IsCurrentRight : function(dialog) {
		return this._right_show === dialog;
	},
	AddToTip : function(dialog) {
		this._tip_layer.AddChild(dialog);
	},
	RemoveFromTip : function(dialog) {
		this._tip_layer.RemoveChild(dialog);
	},
	PickUp : function(x, y) {
		let mfc_rel_x = undefined;
		let mfc_rel_y = undefined;
		let mfc = undefined;
		let mfd = undefined;
		[mfc, mfc_rel_x, mfc_rel_y] = this._right_layer.PickUp(x, y);
		if (mfc !== undefined) {
			return [mfc, undefined, mfc_rel_x, mfc_rel_y];
		}
		[mfc, mfc_rel_x, mfc_rel_y] = this._modal_layer.PickUp(x, y);
		if (mfc !== undefined) {
			return [mfc, undefined, mfc_rel_x, mfc_rel_y];
		}
		let normal_groups = this._normal_groups;
		for (let group_index = this._normal_group_count; group_index > 0; group_index += -1) {
			let normal_layers = normal_groups[group_index - 1];
			let layer_list = normal_layers.childs;
			for (let layer_index = normal_layers.child_count; layer_index > 0; layer_index += -1) {
				let layer = layer_list[layer_index - 1];
				[mfc, mfd, mfc_rel_x, mfc_rel_y] = this.LayerPickup(layer, x, y);
				if (mfc !== undefined) {
					return [mfc, mfd, mfc_rel_x, mfc_rel_y];
				}
			}
		}
		return [undefined, undefined, undefined, undefined];
	},
	LayerPickup : function(layer, x, y) {
		let mfc_rel_x = undefined;
		let mfc_rel_y = undefined;
		let mfc = undefined;
		let mfd = undefined;
		if (layer.visible && layer.disabled === false && layer.childs !== undefined) {
			let rel_x = x - layer.x;
			let rel_y = y - layer.y;
			let child_list = layer.childs;
			for (let index = layer.child_count; index > 0; index += -1) {
				let dialog = child_list[index - 1];
				[mfc, mfc_rel_x, mfc_rel_y] = dialog.PickUp(rel_x, rel_y);
				if (mfc !== undefined) {
					mfd = dialog;
					break;
				}
			}
		}
		return [mfc, mfd, mfc_rel_x, mfc_rel_y];
	},
	HandleLRButtonDown : function(x, y) {
		if (this._right_show === undefined) {
			return;
		}
		let [left, top] = this._right_show.LocalToGlobal();
		let right = this._right_show.width * this._right_show.scale_x + left;
		let bottom = this._right_show.height * this._right_show.scale_y + top;
		if (x >= left && x < right && y >= top && y < bottom) {
			return;
		}
		let link_control = this._right_show.__right_data;
		if (link_control !== undefined) {
			let [abs_x, abs_y] = link_control.LocalToGlobal();
			if (x >= abs_x && x < abs_x + link_control.width * link_control.scale_x && y >= abs_y && y < abs_y + link_control.height * link_control.scale_y) {
				return;
			}
		}
		this._right_show.DispatchEvent(___all_struct.get(348388800), {});
		this._right_show.visible = false;
		this._right_show = undefined;
	},
}, "ALittle.LayerManager");

window.A_LayerManager = ALittle.NewObject(ALittle.LayerManager);
}
{
if (typeof ALittle === "undefined") window.ALittle = {};

ALittle.RegStruct(1002517605, "ALittle.LoadingTextureObjectInfo", {
name : "ALittle.LoadingTextureObjectInfo", ns_name : "ALittle", rl_name : "LoadingTextureObjectInfo", hash_code : 1002517605,
name_list : ["callback"],
type_list : ["Functor<(ALittle.DisplayObject,bool)>"],
option_map : {}
})
ALittle.RegStruct(1266404893, "ALittle.LoadTextureInfo", {
name : "ALittle.LoadTextureInfo", ns_name : "ALittle", rl_name : "LoadTextureInfo", hash_code : 1266404893,
name_list : ["loader","cut_loader","texture_mgr"],
type_list : ["ALittle.ITextureLoader","ALittle.ITextureCutLoader","ALittle.TextureManager"],
option_map : {}
})
ALittle.RegStruct(1754262532, "ALittle.LoadingTextureInfo", {
name : "ALittle.LoadingTextureInfo", ns_name : "ALittle", rl_name : "LoadingTextureInfo", hash_code : 1754262532,
name_list : ["cache","object_map"],
type_list : ["bool","Map<ALittle.DisplayObject,ALittle.LoadingTextureObjectInfo>"],
option_map : {}
})
ALittle.RegStruct(1812223610, "ALittle.LoadAtlasInfo", {
name : "ALittle.LoadAtlasInfo", ns_name : "ALittle", rl_name : "LoadAtlasInfo", hash_code : 1812223610,
name_list : ["big_path","atlas","big_width","big_height"],
type_list : ["string","List<string>","int","int"],
option_map : {}
})
ALittle.RegStruct(-1815508639, "ALittle.TextureCutInfo", {
name : "ALittle.TextureCutInfo", ns_name : "ALittle", rl_name : "TextureCutInfo", hash_code : -1815508639,
name_list : ["texture_name","max_width","max_height","cache"],
type_list : ["string","int","int","bool"],
option_map : {}
})
ALittle.RegStruct(-451991995, "ALittle.AltasTextureInfo", {
name : "ALittle.AltasTextureInfo", ns_name : "ALittle", rl_name : "AltasTextureInfo", hash_code : -451991995,
name_list : ["width","height","path"],
type_list : ["int","int","string"],
option_map : {}
})
ALittle.RegStruct(-60039899, "ALittle.AltasInfo", {
name : "ALittle.AltasInfo", ns_name : "ALittle", rl_name : "AltasInfo", hash_code : -60039899,
name_list : ["big_path","atlas","big_width","big_height","t","b","l","r"],
type_list : ["string","List<string>","int","int","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(1305876767, "ALittle.PrepareInfo", {
name : "ALittle.PrepareInfo", ns_name : "ALittle", rl_name : "PrepareInfo", hash_code : 1305876767,
name_list : ["total","succeed","failed","map","callback"],
type_list : ["int","int","int","Map<string,bool>","Functor<(int,int,int)>"],
option_map : {}
})
ALittle.RegStruct(1390702448, "ALittle.AltasCollectInfo", {
name : "ALittle.AltasCollectInfo", ns_name : "ALittle", rl_name : "AltasCollectInfo", hash_code : 1390702448,
name_list : ["count","list"],
type_list : ["int","List<List<any>>"],
option_map : {}
})

ALittle.LoadTextureManager = JavaScript.Class(undefined, {
	Ctor : function() {
		this._id_map_info = new Map();
		this._path_map_texture_cut = ALittle.CreateValueWeakMap();
		this._path_map_objects_cut = {};
		this._redraw_map_redraw = ALittle.CreateKeyWeakMap();
		this._texmgr_map_texmgr = ALittle.CreateKeyWeakMap();
	},
	CreateTexture : function(texture_mgr, atlas) {
		let loader = undefined;
		loader = ALittle.NewObject(JavaScript.JTextureLoader);
		loader.SetPath(atlas.big_path, ALittle.String_Join(atlas.atlas, ";"), atlas.big_width, atlas.big_height, texture_mgr.crypt_mode);
		let info = {};
		this._id_map_info.set(loader.GetID(), info);
		info.texture_mgr = texture_mgr;
		info.loader = loader;
		loader.Start();
	},
	HandleTextureLoadSucceed : function(loader, texture) {
		let loader_id = loader.GetID();
		let info = this._id_map_info.get(loader_id);
		if (info === undefined) {
			return;
		}
		this._id_map_info.delete(loader_id);
		info.texture_mgr.HandleTextureLoadSucceed(loader, texture);
	},
	HandleTextureLoadFailed : function(loader) {
		let loader_id = loader.GetID();
		let info = this._id_map_info.get(loader_id);
		if (info === undefined) {
			return;
		}
		this._id_map_info.delete(loader_id);
		info.texture_mgr.HandleTextureLoadFailed(loader);
	},
	GetTextureCut : function(path, max_width, max_height) {
		let texture_id = path + "_" + max_width + "_" + max_height;
		return this._path_map_texture_cut[texture_id];
	},
	ClearTextureCut : function(path, max_width, max_height) {
		let texture_id = path + "_" + max_width + "_" + max_height;
		delete this._path_map_texture_cut[texture_id];
	},
	IsLoadingTextureCut : function(path, max_width, max_height) {
		let texture_id = path + "_" + max_width + "_" + max_height;
		return this._path_map_objects_cut[texture_id] !== undefined;
	},
	SetTextureCut : function(object, path, max_width, max_height, cache, callback) {
		object.SetTextureCoord(0, 1, 0, 1);
		if (max_width === undefined) {
			max_width = 0;
		}
		max_width = ALittle.Math_Floor(max_width);
		if (max_height === undefined) {
			max_height = 0;
		}
		max_height = ALittle.Math_Floor(max_height);
		if (cache === undefined) {
			cache = false;
		}
		let texture_id = path + "_" + max_width + "_" + max_height;
		let texture = this._path_map_texture_cut[texture_id];
		if (texture !== undefined) {
			object.texture = texture;
			if (callback !== undefined) {
				callback(object, true);
			}
			return;
		}
		let loading_info = this._path_map_objects_cut[texture_id];
		if (loading_info !== undefined) {
			let object_info = {};
			object_info.callback = callback;
			loading_info.object_map.set(object, object_info);
			return;
		}
		loading_info = {};
		loading_info.cache = cache;
		this._path_map_objects_cut[texture_id] = loading_info;
		loading_info.object_map = ALittle.CreateKeyWeakMap();
		let object_info = {};
		object_info.callback = callback;
		loading_info.object_map.set(object, object_info);
		let loader = undefined;
		loader = ALittle.NewObject(JavaScript.JTextureCutLoader);
		loader.SetPath(path, max_width, max_height);
		let info = {};
		this._id_map_info.set(loader.GetID(), info);
		info.cut_loader = loader;
		loader.Start();
	},
	HandleTextureCutLoadSucceed : function(loader, texture) {
		let loader_id = loader.GetID();
		let info = this._id_map_info.get(loader_id);
		if (info === undefined) {
			return;
		}
		this._id_map_info.delete(loader_id);
		let path = loader.GetPath();
		let max_width = loader.GetMaxWidth();
		let max_height = loader.GetMaxHeight();
		let texture_id = path + "_" + max_width + "_" + max_height;
		let loading_info = this._path_map_objects_cut[texture_id];
		if (loading_info === undefined) {
			return;
		}
		if (loading_info.cache) {
			this._path_map_texture_cut[texture_id] = texture;
		}
		for (let [object, value] of loading_info.object_map) {
			if (value === undefined) continue;
			if (object.texture_name === path) {
				object.texture = texture;
				if (value.callback !== undefined) {
					value.callback(object, true);
				}
			}
		}
		delete this._path_map_objects_cut[texture_id];
	},
	HandleTextureCutLoadFailed : function(loader) {
		let loader_id = loader.GetID();
		let info = this._id_map_info.get(loader_id);
		if (info === undefined) {
			return;
		}
		this._id_map_info.delete(loader_id);
		let path = loader.GetPath();
		let max_width = loader.GetMaxWidth();
		let max_height = loader.GetMaxHeight();
		let texture_id = path + "_" + max_width + "_" + max_height;
		let loading_info = this._path_map_objects_cut[texture_id];
		if (loading_info === undefined) {
			return;
		}
		for (let [object, value] of loading_info.object_map) {
			if (value === undefined) continue;
			if (value.callback !== undefined) {
				value.callback(object, false);
			}
		}
		delete this._path_map_objects_cut[texture_id];
	},
	RegisterRedrawControl : function(control) {
		this._redraw_map_redraw.set(control, true);
	},
	RegisterTexmgrControl : function(control) {
		this._texmgr_map_texmgr.delete(control);
	},
	HandleRenderDeviceReset : function() {
		this._path_map_texture_cut = ALittle.CreateValueWeakMap();
		for (let [texmgr, _] of this._texmgr_map_texmgr) {
			if (_ === undefined) continue;
			texmgr.ClearCache();
		}
		for (let [control, _] of this._redraw_map_redraw) {
			if (_ === undefined) continue;
			control.Redraw();
		}
	},
}, "ALittle.LoadTextureManager");

window.A_LoadTextureManager = ALittle.NewObject(ALittle.LoadTextureManager);
ALittle.AltasBinary = JavaScript.Class(undefined, {
	Ctor : function(x, y, width, height) {
		this._width = width;
		this._height = height;
		this._x = x;
		this._y = y;
		this._texture_x = undefined;
		this._texture_y = undefined;
		this._texture_w = undefined;
		this._texture_h = undefined;
		this._texture_path = undefined;
		this._left = undefined;
		this._right = undefined;
	},
	Fill : function(texture_info, padding) {
		if (this._left !== undefined) {
			if (this._left.Fill(texture_info, padding)) {
				return true;
			}
		}
		if (this._right !== undefined) {
			if (this._right.Fill(texture_info, padding)) {
				return true;
			}
		}
		if (this._texture_path === undefined) {
			let real_width = texture_info.width + padding * 2;
			let real_height = texture_info.height + padding * 2;
			if (real_width > this._width) {
				return false;
			}
			if (real_height > this._height) {
				return false;
			}
			this._texture_w = texture_info.width;
			this._texture_h = texture_info.height;
			this._texture_x = this._x + padding;
			this._texture_y = this._y + padding;
			this._texture_path = texture_info.path;
			this._left = ALittle.NewObject(ALittle.AltasBinary, this._x + real_width, this._y, this._width - real_width, real_height);
			this._right = ALittle.NewObject(ALittle.AltasBinary, this._x, this._y + real_height, this._width, this._height - real_height);
			return true;
		}
		return false;
	},
	GetInfo : function(list_info) {
		if (list_info === undefined) {
			list_info = {};
			list_info.count = 0;
			list_info.list = [];
		}
		if (this._texture_path !== undefined) {
			let info = [];
			info[1 - 1] = this._texture_path;
			info[2 - 1] = this._texture_x;
			info[3 - 1] = this._texture_y;
			info[4 - 1] = this._texture_w;
			info[5 - 1] = this._texture_h;
			++ list_info.count;
			list_info.list[list_info.count - 1] = info;
		}
		if (this._left !== undefined) {
			this._left.GetInfo(list_info);
		}
		if (this._right !== undefined) {
			this._right.GetInfo(list_info);
		}
		return list_info.list;
	},
	TextureListComp : function(a, b) {
		if (a.height > b.height) {
			return true;
		} else if (a.height === b.height) {
			if (a.width > b.width) {
				return true;
			} else if (a.width === b.width) {
				if (a.path > b.path) {
					return true;
				}
			}
		}
		return false;
	},
	GenerateAltas : function(texture_list, max_width, max_height, padding) {
		ALittle.List_Sort(texture_list, ALittle.AltasBinary.TextureListComp);
		let big_list = [];
		let big_list_count = 0;
		++ big_list_count;
		big_list[big_list_count - 1] = max_width;
		++ big_list_count;
		big_list[big_list_count - 1] = max_height;
		while (true) {
			let altas = ALittle.NewObject(ALittle.AltasBinary, 0, 0, max_width, max_height);
			let left_list = [];
			let left_list_count = 0;
			let ___OBJECT_1 = texture_list;
			for (let index = 1; index <= ___OBJECT_1.length; ++index) {
				let texture_info = ___OBJECT_1[index - 1];
				if (texture_info === undefined) break;
				let real_width = texture_info.width + padding * 2;
				let real_height = texture_info.height + padding * 2;
				if (real_width <= max_width && real_height <= max_height) {
					if (altas.Fill(texture_info, padding) !== true) {
						++ left_list_count;
						left_list[left_list_count - 1] = texture_info;
					}
				}
			}
			let list = altas.GetInfo();
			if (list[2 - 1] !== undefined) {
				++ big_list_count;
				big_list[big_list_count - 1] = list;
			}
			texture_list = left_list;
			if (texture_list[1 - 1] === undefined) {
				break;
			}
		}
		return big_list;
	},
}, "ALittle.AltasBinary");

ALittle.TextureManager = JavaScript.Class(undefined, {
	Ctor : function(module_name, crypt_mode) {
		this._cache_texture = true;
		this._base_path = "Module/" + module_name + "/Texture/";
		this._crypt_mode = crypt_mode || false;
		this._path_map_texture = ALittle.CreateValueWeakMap();
		this._prepare_map = new Map();
		this._path_map_objects = {};
		this.LoadAtlas();
	},
	LoadAtlas : function() {
		this._name_map_atlas = {};
		if (!this._crypt_mode) {
			return;
		}
		let [big_list] = ALittle.File_ReadJsonFromFile(this._base_path + "Atlas.ali", this._crypt_mode);
		if (big_list === undefined) {
			return;
		}
		let big_list_count = ALittle.List_MaxN(big_list);
		if (big_list_count < 2) {
			return;
		}
		let texture_width = big_list[1 - 1];
		let texture_height = big_list[2 - 1];
		for (let index = 3; index <= big_list_count; index += 1) {
			let list = big_list[index - 1];
			let big_path = index + ".atlas";
			let info = [];
			let info_count = 0;
			let ___OBJECT_2 = list;
			for (let index = 1; index <= ___OBJECT_2.length; ++index) {
				let value = ___OBJECT_2[index - 1];
				if (value === undefined) break;
				let path = value[1 - 1];
				let x = value[2 - 1];
				let y = value[3 - 1];
				let w = value[4 - 1];
				let h = value[5 - 1];
				let atlas = {};
				atlas.big_path = big_path;
				atlas.t = y / texture_height;
				atlas.b = (y + h) / texture_height;
				atlas.l = x / texture_width;
				atlas.r = (x + w) / texture_width;
				atlas.big_width = texture_width;
				atlas.big_height = texture_height;
				atlas.atlas = info;
				this._name_map_atlas[path] = atlas;
				++ info_count;
				info[info_count - 1] = this._base_path + path + "," + y + "," + ((y + h)) + "," + x + "," + ((x + w)) + "," + w + "," + h;
			}
		}
	},
	GetAtlas : function(name) {
		let atlas = this._name_map_atlas[name];
		if (atlas !== undefined) {
			return atlas;
		}
		atlas = {};
		this._name_map_atlas[name] = atlas;
		atlas.big_path = name;
		atlas.t = 0;
		atlas.b = 1;
		atlas.l = 0;
		atlas.r = 1;
		atlas.big_width = 0;
		atlas.big_height = 0;
		atlas.atlas = [];
		atlas.atlas[1 - 1] = this._base_path + name + ",0,0,0,0,0,0";
		return atlas;
	},
	set cache_texture(cache) {
		this._cache_texture = cache;
	},
	get cache_texture() {
		return this._cache_texture;
	},
	get crypt_mode() {
		return this._crypt_mode;
	},
	ClearCache : function() {
		this._path_map_texture = ALittle.CreateValueWeakMap();
		this._prepare_map = new Map();
	},
	PrepareTexture : function(name_map, callback) {
		let new_name_map = {};
		let ___OBJECT_3 = name_map;
		for (let name in ___OBJECT_3) {
			let value = ___OBJECT_3[name];
			if (value === undefined) continue;
			let atlas = this.GetAtlas(name);
			if (new_name_map[atlas.big_path] === undefined) {
				let texture = this._path_map_texture[atlas.big_path];
				if (texture === undefined) {
					let loading_map = this._path_map_objects[atlas.big_path];
					if (loading_map === undefined) {
						loading_map = ALittle.CreateKeyWeakMap();
						this._path_map_objects[atlas.big_path] = loading_map;
					}
					A_LoadTextureManager.CreateTexture(this, atlas);
					new_name_map[atlas.big_path] = false;
				} else {
					new_name_map[atlas.big_path] = true;
				}
			}
		}
		let prepare_info = {};
		prepare_info.total = 0;
		prepare_info.succeed = 0;
		prepare_info.failed = 0;
		prepare_info.map = new_name_map;
		prepare_info.callback = callback;
		let ___OBJECT_4 = new_name_map;
		for (let name in ___OBJECT_4) {
			let value = ___OBJECT_4[name];
			if (value === undefined) continue;
			++ prepare_info.total;
			if (value) {
				++ prepare_info.succeed;
			}
		}
		if (prepare_info.total > prepare_info.succeed + prepare_info.failed) {
			this._prepare_map.set(prepare_info, true);
		}
		if (callback !== undefined) {
			callback(prepare_info.total, prepare_info.succeed, prepare_info.failed);
		}
	},
	SetTexture : function(object, name) {
		let atlas = this.GetAtlas(name);
		object.SetTextureCoord(atlas.t, atlas.b, atlas.l, atlas.r);
		let texture = this._path_map_texture[atlas.big_path];
		if (texture !== undefined) {
			object.texture = texture;
			return;
		}
		let loading_map = this._path_map_objects[atlas.big_path];
		if (loading_map !== undefined) {
			loading_map.set(object, name);
			return;
		}
		loading_map = ALittle.CreateKeyWeakMap();
		this._path_map_objects[atlas.big_path] = loading_map;
		loading_map.set(object, name);
		A_LoadTextureManager.CreateTexture(this, atlas);
	},
	HandleTextureLoadSucceed : function(loader, texture) {
		let path = loader.GetPath();
		let loading_map = this._path_map_objects[path];
		if (loading_map !== undefined) {
			if (this._cache_texture) {
				this._path_map_texture[path] = texture;
			}
			for (let [k, v] of loading_map) {
				if (v === undefined) continue;
				if (k.texture_name === v) {
					k.texture = texture;
				}
			}
			delete this._path_map_objects[path];
		}
		let copy_map = new Map();
		for (let [k, v] of this._prepare_map) {
			if (v === undefined) continue;
			copy_map.set(k, v);
		}
		let erase_map = new Map();
		for (let [info, v] of copy_map) {
			if (v === undefined) continue;
			if (info.map[path] === false) {
				++ info.succeed;
				info.map[path] = true;
				if (info.callback !== undefined) {
					info.callback(info.total, info.succeed, info.failed);
				}
				if (info.total <= info.succeed + info.failed) {
					erase_map.set(info, true);
				}
			}
		}
		for (let [info, v] of erase_map) {
			if (v === undefined) continue;
			this._prepare_map.delete(info);
		}
	},
	HandleTextureLoadFailed : function(loader) {
		let path = loader.GetPath();
		delete this._path_map_objects[path];
		let erase_map = new Map();
		for (let [info, v] of this._prepare_map) {
			if (v === undefined) continue;
			if (info.map[path] === false) {
				++ info.failed;
				info.map[path] = true;
				if (info.callback !== undefined) {
					info.callback(info.total, info.succeed, info.failed);
				}
				if (info.total <= info.succeed + info.failed) {
					erase_map.set(info, true);
				}
			}
		}
		for (let [info, v] of erase_map) {
			if (v === undefined) continue;
			this._prepare_map.delete(info);
		}
	},
}, "ALittle.TextureManager");

}
{
if (typeof ALittle === "undefined") window.ALittle = {};


let __byte = ALittle.String_Byte;
let __type = ALittle.String_Type;
ALittle.ControlSystem = JavaScript.Class(undefined, {
	Ctor : function(module_name, crypt_mode) {
		this._log_error = true;
		this._use_plugin_class = true;
		this._font_map = {};
		this._name_map_info = {};
		this._name_map_info_cache = {};
		this._module_name = module_name;
		this._crypt_mode = crypt_mode || false;
		if (window["alittle_hostname"] !== undefined) {
			this._host = window["alittle_hostname"];
		} else {
			this._host = location.hostname;
		}
		if (window["alittle_port"] !== undefined) {
			this._port = window["alittle_port"];
		} else {
			this._port = ALittle.Math_ToInt(location.port);
		}
		if (window["alittle_base_url"] !== undefined) {
			this._base_url = window["alittle_base_url"];
		} else {
			this._base_url = ALittle.File_GetFilePathByPath(location.pathname) + "/";
		}
		if (this._port === undefined) {
			if (location.protocol === "https:") {
				this._port = 443;
			} else {
				this._port = 80;
			}
		}
		this._base_path = "Module/" + module_name + "/";
		this._base_path = this._base_url + this._base_path;
		this._ui_path = this._base_path + "UI/";
		this._font_path = this._base_path + "Font/";
		this._sound_path = this._base_path + "Sound/";
		this._other_path = this._base_path + "Other/";
		this._texture_mgr = ALittle.NewObject(ALittle.TextureManager, module_name, this._crypt_mode);
		A_LoadTextureManager.RegisterTexmgrControl(this._texture_mgr);
	},
	get crypt_mode() {
		return this._crypt_mode;
	},
	get log_error() {
		return this._log_error;
	},
	set log_error(value) {
		this._log_error = value;
	},
	RegisterFont : function(src, dst) {
		this._font_map[src] = dst;
	},
	RegisterInfoByHttp : function() {
		return new Promise((async function(___COROUTINE, ___) {
			let path = this._ui_path + "../JSUI/ui_all_in_one.json";
			ALittle.File_MakeDeepDir(ALittle.File_GetFilePathByPath(path));
			let error = await ALittle.HttpDownloadRequest(this._host, this._port, path, path);
			if (error !== undefined) {
				ALittle.Error("ui load failed:" + error);
				___COROUTINE(); return;
			}
			let content = JavaScript.File_LoadFile(path);
			if (content === undefined) {
				ALittle.Error("ui load failed:" + error);
				___COROUTINE(); return;
			}
			JavaScript.File_DeleteFile(path);
			let [jerror, json] = (function() { try { let ___VALUE = ALittle.String_JsonDecode.call(undefined, content); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } }).call(this);
			if (jerror !== undefined) {
				ALittle.Error("ui json decode failed:" + jerror);
				___COROUTINE(); return;
			}
			let ___OBJECT_1 = json;
			for (let name in ___OBJECT_1) {
				let value = ___OBJECT_1[name];
				if (value === undefined) continue;
				this.RegisterInfo(name, value);
			}
			let ___OBJECT_2 = json;
			for (let name in ___OBJECT_2) {
				let value = ___OBJECT_2[name];
				if (value === undefined) continue;
				let info = this.CreateInfo(this._name_map_info[name]);
				this._name_map_info[name] = info;
				this._name_map_info_cache[name] = true;
			}
			___COROUTINE();
		}).bind(this));
	},
	RegisterInfo : function(name, info) {
		this._name_map_info[name] = info;
		delete this._name_map_info_cache[name];
	},
	UnRegisterInfo : function(name) {
		delete this._name_map_info[name];
		delete this._name_map_info_cache[name];
	},
	ClearAllInfo : function() {
		this._name_map_info = {};
		this._name_map_info_cache = {};
	},
	CreateControlObject : function(info) {
		let target_class = info.__target_class;
		if (this._use_plugin_class && target_class !== undefined) {
			let class_func = info.__class_func;
			if (class_func === undefined) {
				class_func = window;
				let ___OBJECT_3 = target_class;
				for (let index = 1; index <= ___OBJECT_3.length; ++index) {
					let value = ___OBJECT_3[index - 1];
					if (value === undefined) break;
					class_func = class_func[value];
					if (class_func === undefined) {
						break;
					}
				}
				info.__class_func = class_func;
			}
			if (class_func !== undefined) {
				return ALittle.NewObject(class_func, this);
			} else {
				ALittle.Log("unknow target class." + ALittle.String_Join(target_class, "."));
			}
		}
		let clazz = info.__class;
		if (clazz === undefined) {
			ALittle.Log("__class is null");
			return undefined;
		}
		let class_func = info.__class_func;
		if (class_func === undefined) {
			class_func = ALittle[clazz];
			info.__class_func = class_func;
		}
		if (class_func === undefined) {
			ALittle.Log("unknow class." + clazz);
			return undefined;
		}
		return ALittle.NewObject(class_func, this);
	},
	StartChunk : function(file_path, loop, callback) {
		return A_AudioSystem.StartChunk(this._sound_path + file_path, loop, callback);
	},
	StopChunk : function(channel) {
		A_AudioSystem.StopChunk(channel);
	},
	StartMusic : function(file_path, loop) {
		return A_AudioSystem.StartMusic(this._sound_path + file_path, loop);
	},
	StopMusic : function() {
		A_AudioSystem.StopMusic();
	},
	SetTexture : function(object, name) {
		this._texture_mgr.SetTexture(object, name);
	},
	PrepareTexture : function(ui_list, callback) {
		let name_map = {};
		if (ui_list !== undefined) {
			let ___OBJECT_4 = ui_list;
			for (let index = 1; index <= ___OBJECT_4.length; ++index) {
				let ui = ___OBJECT_4[index - 1];
				if (ui === undefined) break;
				this.CollectTextureName(ui, name_map);
			}
		}
		this._texture_mgr.PrepareTexture(name_map, callback);
	},
	PrepareCsv : function(csv_map, callback) {
		let new_csv_map = {};
		let ___OBJECT_5 = csv_map;
		for (let file_path in ___OBJECT_5) {
			let config = ___OBJECT_5[file_path];
			if (config === undefined) continue;
			new_csv_map[this._other_path + file_path] = config;
		}
		A_CsvConfigManager.PrepareCsv(new_csv_map, callback);
	},
	set cache_texture(cache) {
		this._texture_mgr.cache_texture = cache;
	},
	get cache_texture() {
		return this._texture_mgr.cache_texture;
	},
	set use_plugin_class(use) {
		this._use_plugin_class = use;
	},
	get use_plugin_class() {
		return this._use_plugin_class;
	},
	SetFont : function(object, font_path, font_size) {
		let dst = this._font_map[font_path];
		if (dst === undefined) {
			dst = "Arial";
		}
		object.native_show.SetFont(dst, font_size);
	},
	SaveControlToFile : function(control, file_path, scale) {
		if (control === undefined) {
			return false;
		}
		if (scale === undefined) {
			scale = 1;
		}
		let texture = ALittle.NewObject(lua.__CPPAPIRenderTexture);
		let x = control.x;
		let y = control.y;
		let width = control.width;
		let height = control.height;
		let visible = control.visible;
		let clip = control.clip;
		control.native_show.SetX(0);
		control.native_show.SetY(0);
		control.visible = true;
		control.clip = false;
		let result = texture.Save(file_path, control.native_show, ALittle.Math_Floor(width), ALittle.Math_Floor(height), scale);
		control.native_show.SetX(x);
		control.native_show.SetY(y);
		control.visible = visible;
		control.clip = clip;
		texture.Clear();
		return result;
	},
	CreateControl : function(name, target_logic, parent) {
		let info = this.LoadInfo(name);
		if (info === undefined) {
			ALittle.Log("can't find control name:" + name);
			return undefined;
		}
		let object = this.CreateControlObject(info);
		if (object === undefined) {
			return undefined;
		}
		object.Deserialize(info, target_logic, parent);
		return object;
	},
	CollectTextureName : function(name, map) {
		let info = this.LoadInfo(name);
		if (info === undefined) {
			ALittle.Log("can't find control name:" + name);
			return undefined;
		}
		return this.CollectTextureNameImpl(info, map);
	},
	LoadInfo : function(name) {
		if (this._name_map_info_cache[name]) {
			return this._name_map_info[name];
		}
		let info = this._name_map_info[name];
		if (info === undefined) {
			let [json] = ALittle.File_ReadJsonFromFile(this._ui_path + name + ".json", this._crypt_mode);
			if (json === undefined) {
				return undefined;
			}
			let ___OBJECT_6 = json;
			for (let key in ___OBJECT_6) {
				let value = ___OBJECT_6[key];
				if (value === undefined) continue;
				this.RegisterInfo(key, value);
			}
		}
		info = this.CreateInfo(this._name_map_info[name]);
		this._name_map_info[name] = info;
		this._name_map_info_cache[name] = true;
		return this._name_map_info[name];
	},
	CreateInfo : function(info) {
		if (info === undefined) {
			return undefined;
		}
		if (info.__include !== undefined) {
			return this.LoadInfo(info.__include);
		}
		let extendsv = info.__extends;
		if (extendsv !== undefined) {
			if (info.__extends_included !== true) {
				let control = this.LoadInfo(extendsv);
				if (control === undefined) {
					ALittle.Log("ControlSystem CreateInfo extends Failed:" + extendsv);
					return undefined;
				}
				let copy = {};
				let ___OBJECT_7 = control;
				for (let key in ___OBJECT_7) {
					let value = ___OBJECT_7[key];
					if (value === undefined) continue;
					copy[key] = value;
				}
				let ___OBJECT_8 = info;
				for (let key in ___OBJECT_8) {
					let value = ___OBJECT_8[key];
					if (value === undefined) continue;
					copy[key] = value;
				}
				info = copy;
				info.__extends_included = true;
				info.__shows_included = undefined;
				info.__childs_included = undefined;
				info.__base_attr = undefined;
				info.__show_attr = undefined;
			}
		}
		if (info.__shows_included !== true) {
			let ___OBJECT_9 = info;
			for (let key in ___OBJECT_9) {
				let value = ___OBJECT_9[key];
				if (value === undefined) continue;
				if (__byte(key, 1) !== 95 && __type(value) === "table" && (value.__include !== undefined || value.__extends !== undefined || value.__class !== undefined)) {
					info[key] = this.CreateInfo(value);
				}
			}
			info.__shows_included = true;
		}
		let childs = info.__childs;
		if (childs !== undefined) {
			if (info.__childs_included !== true) {
				let ___OBJECT_10 = childs;
				for (let index = 1; index <= ___OBJECT_10.length; ++index) {
					let child = ___OBJECT_10[index - 1];
					if (child === undefined) break;
					childs[index - 1] = this.CreateInfo(childs[index - 1]);
				}
				info.__childs_included = true;
			}
		}
		return info;
	},
	CollectTextureNameImpl : function(info, map) {
		if (map === undefined) {
			map = {};
		}
		let class_func = undefined;
		let target_class = info.__target_class;
		if (this._use_plugin_class && target_class !== undefined) {
			class_func = window;
			let ___OBJECT_11 = target_class;
			for (let index = 1; index <= ___OBJECT_11.length; ++index) {
				let value = ___OBJECT_11[index - 1];
				if (value === undefined) break;
				class_func = class_func[value];
				if (class_func === undefined) {
					break;
				}
			}
			if (class_func === undefined) {
				ALittle.Log("unknow target class." + ALittle.String_Join(target_class, "."));
			}
		}
		if (class_func === undefined) {
			class_func = ALittle[info.__class];
		}
		if (class_func === undefined) {
			ALittle.Log("unknow class." + info.__class);
			return map;
		}
		let texture_name = info.texture_name;
		if (texture_name !== undefined && texture_name !== "") {
			map[texture_name] = true;
		}
		let info_t = info;
		let ___OBJECT_12 = info_t;
		for (let key in ___OBJECT_12) {
			let value = ___OBJECT_12[key];
			if (value === undefined) continue;
			if (__type(value) === "table" && value.__class !== undefined) {
				this.CollectTextureNameImpl(value, map);
			}
		}
		let childs = info.__childs;
		if (childs !== undefined) {
			let ___OBJECT_13 = childs;
			for (let index = 1; index <= ___OBJECT_13.length; ++index) {
				let value = ___OBJECT_13[index - 1];
				if (value === undefined) break;
				this.CollectTextureNameImpl(value, map);
			}
		}
		return map;
	},
}, "ALittle.ControlSystem");

}