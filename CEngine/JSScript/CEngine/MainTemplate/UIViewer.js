{
if (typeof ALittle === "undefined") ALittle = {};

ALittle.RegStruct(1225542858, "ALittle.UIViewModuleDebugInfo", {
name : "ALittle.UIViewModuleDebugInfo", ns_name : "ALittle", rl_name : "UIViewModuleDebugInfo", hash_code : 1225542858,
name_list : ["window_width","window_height","title","ui_name"],
type_list : ["int","int","string","string"],
option_map : {}
})

ALittle.g_Control = undefined;
ALittle.g_LayerGroup = undefined;
ALittle.g_BasePath = undefined;
ALittle.__Module_Setup = function(layer_group, control, base_path, debug) {
	ALittle.g_Control = control;
	ALittle.g_LayerGroup = layer_group;
	ALittle.g_BasePath = base_path;
	let [error, info] = (function() { try { let ___VALUE = lua.json.decode.call(undefined, debug); return [undefined, ___VALUE]; } catch (___ERROR) { return [___ERROR.message]; } })();
	let screen_width = ALittle.System_GetScreenWidth();
	let screen_height = ALittle.System_GetScreenHeight();
	let window_width = info.window_width;
	let window_height = info.window_height;
	let rate = 1.0;
	if (ALittle.System_GetPlatform() !== "Windows") {
		window_width = lua.math.floor(screen_width / screen_height * window_height);
	} else {
		if (window_width > screen_width || window_height > screen_height) {
			rate = 0.5;
		}
	}
	ALittle.System_CreateView(info.title, window_width, window_height, ALittle.UIEnumTypes.VIEW_RESIZABLE, rate);
	let layer = ALittle.NewObject(ALittle.DisplayLayout, ALittle.g_Control);
	layer.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
	layer.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
	ALittle.g_LayerGroup.AddChild(layer);
	ALittle.g_Control.CreateControl(info.ui_name, undefined, layer);
}

ALittle.PreLoadFile = function(ui_name, layer, result) {
}

ALittle.__Module_Shutdown = function() {
}

ALittle.__Module_GetInfo = function(control, base_path) {
	let info = {};
	info.title = "UIViewer";
	info.icon = undefined;
	info.width_type = ALittle.UIEnumTypes.SIZE_MARGIN;
	info.width_value = 0;
	info.height_type = ALittle.UIEnumTypes.SIZE_MARGIN;
	info.height_value = 0;
	return info;
}

ALittle.__Plugin_Setup = function(control, base_path, debug) {
}

ALittle.__Plugin_Shutdown = function() {
}

}