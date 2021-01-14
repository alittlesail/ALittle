{
if (typeof AUIPlugin === "undefined") window.AUIPlugin = {};

ALittle.RegStruct(-2130019625, "AUIPlugin.AUICodeErrorInfo", {
name : "AUIPlugin.AUICodeErrorInfo", ns_name : "AUIPlugin", rl_name : "AUICodeErrorInfo", hash_code : -2130019625,
name_list : ["_focus_quad","info","item"],
type_list : ["ALittle.DisplayObject","lua.ABnfQueryError","ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(-1898137181, "AUIPlugin.AUICodeEditJumpEvent", {
name : "AUIPlugin.AUICodeEditJumpEvent", ns_name : "AUIPlugin", rl_name : "AUICodeEditJumpEvent", hash_code : -1898137181,
name_list : ["target","file_path","it_line","it_char"],
type_list : ["ALittle.DisplayObject","string","int","int"],
option_map : {}
})
ALittle.RegStruct(1575183661, "AUIPlugin.AUICodeEditBreakPointEvent", {
name : "AUIPlugin.AUICodeEditBreakPointEvent", ns_name : "AUIPlugin", rl_name : "AUICodeEditBreakPointEvent", hash_code : 1575183661,
name_list : ["target","add_or_remove","file_path","file_line"],
type_list : ["ALittle.DisplayObject","bool","string","int"],
option_map : {}
})
ALittle.RegStruct(1494749965, "AUIPlugin.AUICodeCharInfo", {
name : "AUIPlugin.AUICodeCharInfo", ns_name : "AUIPlugin", rl_name : "AUICodeCharInfo", hash_code : 1494749965,
name_list : ["char","text","red","green","blue","pre_width","width"],
type_list : ["string","ALittle.Text","double","double","double","double","double"],
option_map : {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name : "ALittle.UIEvent", ns_name : "ALittle", rl_name : "UIEvent", hash_code : -1479093282,
name_list : ["target"],
type_list : ["ALittle.DisplayObject"],
option_map : {}
})
ALittle.RegStruct(1421505194, "AUIPlugin.AUICodeLineInfo", {
name : "AUIPlugin.AUICodeLineInfo", ns_name : "AUIPlugin", rl_name : "AUICodeLineInfo", hash_code : 1421505194,
name_list : ["char_list","char_count","container","edit"],
type_list : ["List<AUIPlugin.AUICodeCharInfo>","int","AUIPlugin.AUICodeLineContainer","AUIPlugin.AUICodeEdit"],
option_map : {}
})
ALittle.RegStruct(-1073016186, "AUIPlugin.AUICodeFindInfo", {
name : "AUIPlugin.AUICodeFindInfo", ns_name : "AUIPlugin", rl_name : "AUICodeFindInfo", hash_code : -1073016186,
name_list : ["_focus_quad","it_char_start","it_char_end"],
type_list : ["ALittle.DisplayObject","int","int"],
option_map : {}
})
ALittle.RegStruct(-947960184, "lua.ABnfQueryError", {
name : "lua.ABnfQueryError", ns_name : "lua", rl_name : "ABnfQueryError", hash_code : -947960184,
name_list : ["line_start","char_start","line_end","char_end","error"],
type_list : ["int","int","int","int","string"],
option_map : {}
})
ALittle.RegStruct(631224630, "AUIPlugin.AUICodeEditGotoEvent", {
name : "AUIPlugin.AUICodeEditGotoEvent", ns_name : "AUIPlugin", rl_name : "AUICodeEditGotoEvent", hash_code : 631224630,
name_list : ["target","file_path","line_start","char_start","line_end","char_end"],
type_list : ["ALittle.DisplayObject","string","int","int","int","int"],
option_map : {}
})

AUIPlugin.CODE_LINE_HEIGHT = 20;
AUIPlugin.CODE_LINE_NUMBER_WIDTH = 40;
AUIPlugin.CODE_PAD_LINES = 5;
AUIPlugin.CODE_FONT_SIZE = 14;
AUIPlugin.CODE_FONT_PATH = "YaHei-Consolas.ttf";
AUIPlugin.CODE_FONT_RED = 169 / 255;
AUIPlugin.CODE_FONT_GREEN = 183 / 255;
AUIPlugin.CODE_FONT_BLUE = 198 / 255;
AUIPlugin.CODE_SELECT_RED = 33 / 255;
AUIPlugin.CODE_SELECT_GREEN = 66 / 255;
AUIPlugin.CODE_SELECT_BLUE = 131 / 255;
AUIPlugin.CODE_FIND_RED = 50 / 255;
AUIPlugin.CODE_FIND_GREEN = 89 / 255;
AUIPlugin.CODE_FIND_BLUE = 61 / 255;
AUIPlugin.CODE_LINE_NUMBER_RED = 100 / 255;
AUIPlugin.CODE_LINE_NUMBER_GREEN = 100 / 255;
AUIPlugin.CODE_LINE_NUMBER_BLUE = 100 / 255;
AUIPlugin.CODE_FOCUS_RED = 88 / 255;
AUIPlugin.CODE_FOCUS_GREEN = 157 / 255;
AUIPlugin.CODE_FOCUS_BLUE = 246 / 255;
AUIPlugin.CODE_BACKGROUND_RED = 30 / 255;
AUIPlugin.CODE_BACKGROUND_GREEN = 30 / 255;
AUIPlugin.CODE_BACKGROUND_BLUE = 30 / 255;
AUIPlugin.CODE_PARAMLIST_RED = 128 / 255;
AUIPlugin.CODE_PARAMLIST_GREEN = 128 / 255;
AUIPlugin.CODE_PARAMLIST_BLUE = 128 / 255;
AUIPlugin.CODE_PARAMLIST_FOCUS_RED = 226 / 255;
AUIPlugin.CODE_PARAMLIST_FOCUS_GREEN = 226 / 255;
AUIPlugin.CODE_PARAMLIST_FOCUS_BLUE = 226 / 255;
AUIPlugin.CODE_DEFAULT_COLOR = {};
AUIPlugin.CODE_DEFAULT_COLOR.red = AUIPlugin.CODE_FONT_RED;
AUIPlugin.CODE_DEFAULT_COLOR.green = AUIPlugin.CODE_FONT_GREEN;
AUIPlugin.CODE_DEFAULT_COLOR.blue = AUIPlugin.CODE_FONT_BLUE;
}