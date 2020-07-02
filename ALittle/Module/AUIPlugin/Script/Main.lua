-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs


function __Browser_Setup(layer_group, control, module_base_path, script_base_path, debug)
end
__Browser_Setup = Lua.CoWrap(__Browser_Setup)

function __Browser_AddModule(module_name, layer_group, module_info)
end

function __Browser_Shutdown()
end

g_Control = nil
g_ModuleBasePath = nil
g_ScriptBasePath = nil
function __Module_Setup(layer_group, control, module_base_path, script_base_path, debug)
end
__Module_Setup = Lua.CoWrap(__Module_Setup)

function __Module_Shutdown()
end

function __Module_GetInfo(control, module_base_path, script_base_path)
	return nil
end

function __Plugin_Setup(control, module_base_path, script_base_path)
	g_Control = control
	g_ModuleBasePath = module_base_path
	g_ScriptBasePath = script_base_path
	RequireFromPaths(script_base_path, "AUI/", {"AUIEditImageDialog.alittle", "AUIFileSelectDialog.alittle", "AUIImageCutPlugin.alittle", "AUIIMEManager.alittle", "AUIRightMenu.alittle", "AUITool.alittle", "AUIVersionManager.alittle", "AUIWebLoginManager.alittle"})
	RequireFromPaths(script_base_path, "AUICodeEdit/", {"AUICodeCompleteScreen.alittle", "AUICodeCursor.alittle", "AUICodeEdit.alittle", "AUICodeLanguage.alittle", "AUICodeProject.alittle", "AUICodeRevocation.alittle", "AUICodeSelectCursor.alittle", "ABnf/AUICodeABnf.alittle", "ABnf/AUICodeALittleScript.alittle"})
	g_AUIIMEManager:Setup()
end
__Plugin_Setup = Lua.CoWrap(__Plugin_Setup)

function __Plugin_Shutdown()
	g_AUIIMEManager:Shutdown()
	g_AUITool:Shutdown()
	g_AUICodeCompleteScreen:Shutdown()
	if g_ABnfProjectInfo ~= nil and g_ABnfProjectInfo.project ~= nil then
		g_ABnfProjectInfo.project:Stop()
	end
end

