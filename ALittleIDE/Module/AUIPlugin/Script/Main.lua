-- ALittle Generate Lua And Do Not Edit This Line!
do
if _G.AUIPlugin == nil then _G.AUIPlugin = {} end
local AUIPlugin = AUIPlugin
local Lua = Lua
local ALittle = ALittle
local ___pairs = pairs
local ___ipairs = ipairs


function AUIPlugin.__Browser_Setup(layer_group, control, module_base_path, script_base_path, debug)
end
AUIPlugin.__Browser_Setup = Lua.CoWrap(AUIPlugin.__Browser_Setup)

function AUIPlugin.__Browser_AddModule(module_name, layer_group, module_info)
end

function AUIPlugin.__Browser_Shutdown()
end

AUIPlugin.g_Control = nil
AUIPlugin.g_ModuleBasePath = nil
AUIPlugin.g_ScriptBasePath = nil
function AUIPlugin.__Module_Setup(layer_group, control, module_base_path, script_base_path, debug)
end
AUIPlugin.__Module_Setup = Lua.CoWrap(AUIPlugin.__Module_Setup)

function AUIPlugin.__Module_Shutdown()
end

function AUIPlugin.__Module_GetInfo(control, module_base_path, script_base_path)
	return nil
end

function AUIPlugin.__Plugin_Setup(control, module_base_path, script_base_path)
	local ___COROUTINE = coroutine.running()
	AUIPlugin.g_Control = control
	AUIPlugin.g_ModuleBasePath = module_base_path
	AUIPlugin.g_ScriptBasePath = script_base_path
	if ALittle.System_GetPlatform() == "Windows" then
		package.cpath = package.cpath .. ";./" .. module_base_path .. "Other/?.dll"
		require("alanguage")
		require("abnf")
		require("alittlescript")
		require("memory")
		require("protobuf")
		require("socket")
	end
	Require(script_base_path, "Protobuf/Lua/ISocket")
	Require(script_base_path, "Protobuf/Lua/LuaProtobufSchedule")
	RequireFromPaths(script_base_path, "AUI/", {"AUIWebLoginManager.alittle", "AUIVersionManager.alittle", "AUITool.alittle"
		, "AUIStatLayout.alittle", "AUIRightMenu.alittle", "AUIImageCutPlugin.alittle"
		, "AUIIMEManager.alittle", "AUIFileTreeLayout.alittle", "AUIFileSelectLayout.alittle"
		, "AUIFileSelectDialog.alittle", "AUIEditImageDialog.alittle", "AUIDrawingBoard.alittle"})
	RequireFromPaths(script_base_path, "AUICodeEdit/", {"AUICodeSelectCursor.alittle", "AUICodeRevocation.alittle", "AUICodeProject.alittle"
		, "AUICodeParamList.alittle", "AUICodeLineNumber.alittle", "AUICodeLineContainer.alittle"
		, "AUICodeLanguage.alittle", "AUICodeFilterScreen.alittle", "AUICodeEdit.alittle"
		, "AUICodeDefine.alittle", "AUICodeCursor.alittle", "AUICodeComponent.alittle"
		, "AUICodeCompleteScreen.alittle", "ABnf/AUICodeCommon.alittle", "ABnf/AUICodeALittleScript.alittle"
		, "ABnf/AUICodeABnf.alittle"})
	AUIPlugin.g_AUIIMEManager:Setup()
end

function AUIPlugin.__Plugin_Shutdown()
	AUIPlugin.g_AUIIMEManager:Shutdown()
	g_AUITool:Shutdown()
	g_AUICodeFilterScreen:Shutdown()
	AUIPlugin.AUICodeProject.Shutdown()
end

end