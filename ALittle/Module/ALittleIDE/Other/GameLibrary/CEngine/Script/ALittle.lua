-- ALittle Generate Lua
local ___pairs = pairs
local ___ipairs = ipairs


local __Log
__Log = function(content, level)
	__CPPAPI_ScriptSystemEx:Log(content, level)
end

ALittle.SetLogFunc(__Log)
function RequreCEngine(base_path)
local ___COROUTINE = coroutine.running()
	ALittle.Require(base_path, "CEngine/UISystem/IShow")
	ALittle.Require(base_path, "CEngine/Utility/String")
	ALittle.Require(base_path, "CEngine/Utility/File")
	ALittle.Require(base_path, "CEngine/Utility/System")
	ALittle.Require(base_path, "CEngine/Utility/ConfigSystem")
	ALittle.Require(base_path, "CEngine/Utility/OtherSystem")
	ALittle.Require(base_path, "CEngine/Utility/AudioSystem")
	ALittle.Require(base_path, "CEngine/Utility/CsvConfigManager")
	ALittle.Require(base_path, "CEngine/Utility/Application")
	ALittle.Require(base_path, "CEngine/LoopSystem/LoopAnimation")
	ALittle.Require(base_path, "CEngine/LoopSystem/LoopAttribute")
	ALittle.Require(base_path, "CEngine/LoopSystem/LoopLinear")
	ALittle.Require(base_path, "CEngine/LoopSystem/LoopRit")
	ALittle.Require(base_path, "CEngine/UISystem/UIEnumTypes")
	ALittle.Require(base_path, "CEngine/UISystem/UIEventDispatcher")
	ALittle.Require(base_path, "CEngine/UISystem/Base/Matrix2D")
	ALittle.Require(base_path, "CEngine/UISystem/Base/DisplayObject")
	ALittle.Require(base_path, "CEngine/UISystem/Base/DisplayGroup")
	ALittle.Require(base_path, "CEngine/UISystem/Base/DisplayLayout")
	ALittle.Require(base_path, "CEngine/UISystem/Base/DisplayView")
	ALittle.Require(base_path, "CEngine/UISystem/Base/Quad")
	ALittle.Require(base_path, "CEngine/UISystem/Base/Image")
	ALittle.Require(base_path, "CEngine/UISystem/Base/Sprite")
	ALittle.Require(base_path, "CEngine/UISystem/Base/Text")
	ALittle.Require(base_path, "CEngine/UISystem/Base/TextArea")
	ALittle.Require(base_path, "CEngine/UISystem/Base/TextEdit")
	ALittle.Require(base_path, "CEngine/UISystem/Base/TextInput")
	ALittle.Require(base_path, "CEngine/UISystem/Base/Triangle")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/Grid9Image")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/TextButton")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/TextCheckButton")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/TextRadioButton")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/Grid3")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/Grid9")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/Linear")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/Tab")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/DropDown")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/Slider")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/ScrollBar")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/ScrollScreen")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/Dialog")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/TileTable")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/ImagePlay")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/SpritePlay")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/FramePlay")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/Piechart")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/ImageInput")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/ImageEdit")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/RichArea")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/RichEdit")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/RichInput")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/ScrollList")
	ALittle.Require(base_path, "CEngine/UISystem/Complex/ScrollButton")
	ALittle.Require(base_path, "CEngine/UISystem/Special/SpringTextButton")
	ALittle.Require(base_path, "CEngine/UISystem/Plugin/SpringButton")
	ALittle.Require(base_path, "CEngine/UISystem/Plugin/SpringCheckButton")
	ALittle.Require(base_path, "CEngine/UISystem/Plugin/SpringRadioButton")
	ALittle.Require(base_path, "CEngine/UISystem/Plugin/SpringDialog")
	ALittle.Require(base_path, "CEngine/UISystem/Effect/EffectImage")
	ALittle.Require(base_path, "CEngine/UISystem/UISystem")
	ALittle.Require(base_path, "CEngine/UISystem/LayerManager")
	ALittle.Require(base_path, "CEngine/UISystem/TextureManager")
	ALittle.Require(base_path, "CEngine/UISystem/ControlSystem")
	ALittle.Require(base_path, "CEngine/Version/VersionSystem")
	ALittle.Require(base_path, "CEngine/Version/VersionSystemAndroid")
	ALittle.Require(base_path, "CEngine/Version/VersionSystemIOS")
	ALittle.Require(base_path, "CEngine/Version/VersionSystemWindows")
end

function __ALITTLEAPI_HandleConsoleCmd(cmd)
	ALittle.ExecuteCommand(cmd)
end

function __ALITTLEAPI_FingerMoved(x, y, finger_id, touch_id)
	A_UISystem:HandleFingerMoved(x, y, finger_id, touch_id)
end

function __ALITTLEAPI_FingerDown(x, y, finger_id, touch_id)
	A_UISystem:HandleFingerDown(x, y, finger_id, touch_id)
end

function __ALITTLEAPI_FingerUp(x, y, finger_id, touch_id)
	A_UISystem:HandleFingerUp(x, y, finger_id, touch_id)
end

function __ALITTLEAPI_MouseMoved(x, y)
	A_UISystem:HandleMouseMoved(x, y)
end

function __ALITTLEAPI_LButtonDown(x, y, count)
	A_UISystem:HandleLButtonDown(x, y, count)
end

function __ALITTLEAPI_LButtonUp(x, y)
	A_UISystem:HandleLButtonUp(x, y)
end

function __ALITTLEAPI_MButtonDown(x, y, count)
	A_UISystem:HandleMButtonDown(x, y, count)
end

function __ALITTLEAPI_MButtonUp(x, y)
	A_UISystem:HandleMButtonUp(x, y)
end

function __ALITTLEAPI_RButtonDown(x, y, count)
	A_UISystem:HandleRButtonDown(x, y, count)
end

function __ALITTLEAPI_RButtonUp(x, y)
	A_UISystem:HandleRButtonUp(x, y)
end

function __ALITTLEAPI_MouseWheel(x, y)
	A_UISystem:HandleMouseWheel(x, y)
end

function __ALITTLEAPI_KeyDown(mod, sym, scancode)
	A_UISystem:HandleKeyDown(mod, sym, scancode)
end

function __ALITTLEAPI_KeyUp(mod, sym, scancode)
	A_UISystem:HandleKeyUp(mod, sym, scancode)
end

function __ALITTLEAPI_ViewResized(width, height)
	A_UISystem:HandleViewResized(width, height)
end

function __ALITTLEAPI_TextInput(text)
	A_UISystem:HandleTextInput(text)
end

function __ALITTLEAPI_TextEditing(text, start)
	A_UISystem:HandleTextEditing(text, start)
end

function __ALITTLEAPI_DropFile(path)
	A_UISystem:HandleDropFile(path)
end

function __ALITTLEAPI_WindowEnter()
	A_UISystem:HandleWindowEnter()
end

function __ALITTLEAPI_WindowLeave()
	A_UISystem:HandleWindowLeave()
end

function __ALITTLEAPI_Update(frame_time)
	A_LoopSystem:Update(frame_time)
	A_WeakLoopSystem:Update(frame_time)
end

function __ALITTLEAPI_WillEnterBackground()
	A_OtherSystem:HandleWillEnterBackground()
end

function __ALITTLEAPI_DidEnterBackground()
	A_OtherSystem:HandleDidEnterBackground()
end

function __ALITTLEAPI_WillEnterForeground()
	A_OtherSystem:HandleWillEnterForeground()
end

function __ALITTLEAPI_DidEnterForeground()
	A_OtherSystem:HandleDidEnterForeground()
end

function __ALITTLEAPI_LowMemory()
	A_OtherSystem:HandleLowMemory()
end

function __ALITTLEAPI_TextureLoadSucceed(loader, texture)
	A_LoadTextureManager:HandleTextureLoadSucceed(loader, texture)
end

function __ALITTLEAPI_TextureLoadFailed(loader)
	A_LoadTextureManager:HandleTextureLoadFailed(loader)
end

function __ALITTLEAPI_TextureCutLoadSucceed(loader, texture)
	A_LoadTextureManager:HandleTextureCutLoadSucceed(loader, texture)
end

function __ALITTLEAPI_TextureCutLoadFailed(loader)
	A_LoadTextureManager:HandleTextureCutLoadFailed(loader)
end

function __ALITTLEAPI_CsvFileLoadSucceed(loader, file)
	A_CsvConfigManager:HandleCsvFileLoadSucceed(loader, file)
end

function __ALITTLEAPI_CsvFileLoadFailed(loader)
	A_CsvConfigManager:HandleCsvFileLoadFailed(loader)
end

function __ALITTLEAPI_RenderDeviceReset()
	A_LoadTextureManager:HandleRenderDeviceReset()
end

_G.__ALITTLEAPI_HttpFileSucceed = ALittle.__ALITTLEAPI_HttpFileSucceed
_G.__ALITTLEAPI_HttpFileFailed = ALittle.__ALITTLEAPI_HttpFileFailed
_G.__ALITTLEAPI_HttpFileProcess = ALittle.__ALITTLEAPI_HttpFileProcess
_G.__ALITTLEAPI_HttpClientSucceed = ALittle.__ALITTLEAPI_HttpClientSucceed
_G.__ALITTLEAPI_HttpClientFailed = ALittle.__ALITTLEAPI_HttpClientFailed
_G.__ALITTLEAPI_ConnectSucceed = ALittle.__ALITTLEAPI_ConnectSucceed
_G.__ALITTLEAPI_Disconnect = ALittle.__ALITTLEAPI_Disconnect
_G.__ALITTLEAPI_ConnectFailed = ALittle.__ALITTLEAPI_ConnectFailed
_G.__ALITTLEAPI_Message = ALittle.__ALITTLEAPI_Message
function __ALITTLEAPI_AudioChunkStopedEvent(id)
	A_AudioSystem:HandleAudioChunkStopedEvent(id)
end

function __ALITTLEAPI_NetworkChanged(net_type)
	ALittle.System_ClearAIFamily()
	A_OtherSystem:HandleNetworkChanged(net_type)
end

function __ALITTLEAPI_ALittleJsonRPC(json)
	A_OtherSystem:HandleALittleJsonRPC(json)
end

function __ALITTLEAPI_SystemSelectFile(path)
	A_OtherSystem:HandleSystemSelectFile(path)
end

function __ALITTLEAPI_SystemSaveFile(path)
	A_OtherSystem:HandleSystemSaveFile(path)
end

