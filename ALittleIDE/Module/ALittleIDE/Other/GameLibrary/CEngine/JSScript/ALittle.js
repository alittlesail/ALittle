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
		await Require(base_path, "CEngine/Utility/Revocation");
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
		await Require(base_path, "CEngine/UISystem/Base/VertexImage");
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
		await Require(base_path, "CEngine/UISystem/Complex/SpriteNumber");
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
		await Require(base_path, "CEngine/UISystem/Tile/TileDefine");
		await Require(base_path, "CEngine/UISystem/Plugin/SpringButton");
		await Require(base_path, "CEngine/UISystem/Plugin/SpringCheckButton");
		await Require(base_path, "CEngine/UISystem/Plugin/SpringRadioButton");
		await Require(base_path, "CEngine/UISystem/Plugin/SpringDialog");
		await Require(base_path, "CEngine/UISystem/Effect/EffectImage");
		await Require(base_path, "CEngine/UISystem/Effect/DynamicImage");
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

window.__ALITTLEAPI_Quit = function() {
	A_UISystem.HandleQuit();
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
window.__ALITTLEAPI_Disconnected = ALittle.__ALITTLEAPI_Disconnected;
window.__ALITTLEAPI_ConnectFailed = ALittle.__ALITTLEAPI_ConnectFailed;
window.__ALITTLEAPI_Message = ALittle.__ALITTLEAPI_Message;
window.__ALITTLEAPI_AudioChunkStoppedEvent = function(id) {
	A_AudioSystem.HandleAudioChunkStoppedEvent(id);
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