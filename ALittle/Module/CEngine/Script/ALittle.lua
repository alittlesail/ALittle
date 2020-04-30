-- ALittle Generate Lua
local ___thispath = select('1', ...):match("(.+[/\\]).+$") or ""
local ___pairs = pairs
local ___ipairs = ipairs


require(___thispath.."../../Std/Script/ALittle")
local __Log
__Log = function(content, level)
	__CPPAPI_ScriptSystemEx:Log(content, level)
end

ALittle.SetLogFunc(__Log)
require(___thispath.."CEngine/UISystem/IShow")
require(___thispath.."CEngine/Utility/String")
require(___thispath.."CEngine/Utility/File")
require(___thispath.."CEngine/Utility/System")
require(___thispath.."CEngine/Utility/ConfigSystem")
require(___thispath.."CEngine/Utility/OtherSystem")
require(___thispath.."CEngine/Utility/AudioSystem")
require(___thispath.."CEngine/Utility/CsvConfigManager")
require(___thispath.."CEngine/Utility/Application")
require(___thispath.."CEngine/LoopSystem/LoopAnimation")
require(___thispath.."CEngine/LoopSystem/LoopAttribute")
require(___thispath.."CEngine/LoopSystem/LoopLinear")
require(___thispath.."CEngine/LoopSystem/LoopRit")
require(___thispath.."CEngine/UISystem/UIEnumTypes")
require(___thispath.."CEngine/UISystem/UIEventDispatcher")
require(___thispath.."CEngine/UISystem/Base/Matrix2D")
require(___thispath.."CEngine/UISystem/Base/DisplayObject")
require(___thispath.."CEngine/UISystem/Base/DisplayGroup")
require(___thispath.."CEngine/UISystem/Base/DisplayLayout")
require(___thispath.."CEngine/UISystem/Base/DisplayView")
require(___thispath.."CEngine/UISystem/Base/Quad")
require(___thispath.."CEngine/UISystem/Base/Image")
require(___thispath.."CEngine/UISystem/Base/Sprite")
require(___thispath.."CEngine/UISystem/Base/Text")
require(___thispath.."CEngine/UISystem/Base/TextArea")
require(___thispath.."CEngine/UISystem/Base/TextEdit")
require(___thispath.."CEngine/UISystem/Base/TextInput")
require(___thispath.."CEngine/UISystem/Base/Triangle")
require(___thispath.."CEngine/UISystem/Complex/Grid9Image")
require(___thispath.."CEngine/UISystem/Complex/TextButton")
require(___thispath.."CEngine/UISystem/Complex/TextCheckButton")
require(___thispath.."CEngine/UISystem/Complex/TextRadioButton")
require(___thispath.."CEngine/UISystem/Complex/Grid3")
require(___thispath.."CEngine/UISystem/Complex/Grid9")
require(___thispath.."CEngine/UISystem/Complex/Linear")
require(___thispath.."CEngine/UISystem/Complex/Tab")
require(___thispath.."CEngine/UISystem/Complex/DropDown")
require(___thispath.."CEngine/UISystem/Complex/Slider")
require(___thispath.."CEngine/UISystem/Complex/ScrollBar")
require(___thispath.."CEngine/UISystem/Complex/ScrollScreen")
require(___thispath.."CEngine/UISystem/Complex/Dialog")
require(___thispath.."CEngine/UISystem/Complex/TileTable")
require(___thispath.."CEngine/UISystem/Complex/ImagePlay")
require(___thispath.."CEngine/UISystem/Complex/SpritePlay")
require(___thispath.."CEngine/UISystem/Complex/FramePlay")
require(___thispath.."CEngine/UISystem/Complex/Piechart")
require(___thispath.."CEngine/UISystem/Complex/ImageInput")
require(___thispath.."CEngine/UISystem/Complex/ImageEdit")
require(___thispath.."CEngine/UISystem/Complex/RichArea")
require(___thispath.."CEngine/UISystem/Complex/RichEdit")
require(___thispath.."CEngine/UISystem/Complex/RichInput")
require(___thispath.."CEngine/UISystem/Complex/ScrollList")
require(___thispath.."CEngine/UISystem/Complex/ScrollButton")
require(___thispath.."CEngine/UISystem/Special/SpringTextButton")
require(___thispath.."CEngine/UISystem/Plugin/SpringButton")
require(___thispath.."CEngine/UISystem/Plugin/SpringCheckButton")
require(___thispath.."CEngine/UISystem/Plugin/SpringRadioButton")
require(___thispath.."CEngine/UISystem/Plugin/SpringDialog")
require(___thispath.."CEngine/UISystem/Effect/EffectImage")
require(___thispath.."CEngine/UISystem/UISystem")
require(___thispath.."CEngine/UISystem/LayerManager")
require(___thispath.."CEngine/UISystem/TextureManager")
require(___thispath.."CEngine/UISystem/ControlSystem")
require(___thispath.."CEngine/Version/VersionSystem")
require(___thispath.."CEngine/Version/VersionSystemAndroid")
require(___thispath.."CEngine/Version/VersionSystemIOS")
require(___thispath.."CEngine/Version/VersionSystemWindows")
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

