-- ALittle Generate Lua And Do Not Edit This Line!
module("AUIPlugin", package.seeall)

local ___pairs = pairs
local ___ipairs = ipairs

ALittle.RegStruct(-2130019625, "AUIPlugin.AUICodeErrorInfo", {
name = "AUIPlugin.AUICodeErrorInfo", ns_name = "AUIPlugin", rl_name = "AUICodeErrorInfo", hash_code = -2130019625,
name_list = {"_focus_quad","info"},
type_list = {"ALittle.DisplayObject","lua.ABnfQueryError"},
option_map = {}
})
ALittle.RegStruct(-1898137181, "AUIPlugin.AUICodeEditJumpEvent", {
name = "AUIPlugin.AUICodeEditJumpEvent", ns_name = "AUIPlugin", rl_name = "AUICodeEditJumpEvent", hash_code = -1898137181,
name_list = {"target","file_path","it_line","it_char"},
type_list = {"ALittle.DisplayObject","string","int","int"},
option_map = {}
})
ALittle.RegStruct(1494749965, "AUIPlugin.AUICodeCharInfo", {
name = "AUIPlugin.AUICodeCharInfo", ns_name = "AUIPlugin", rl_name = "AUICodeCharInfo", hash_code = 1494749965,
name_list = {"char","text","red","green","blue","pre_width","width"},
type_list = {"string","ALittle.Text","double","double","double","double","double"},
option_map = {}
})
ALittle.RegStruct(-1479093282, "ALittle.UIEvent", {
name = "ALittle.UIEvent", ns_name = "ALittle", rl_name = "UIEvent", hash_code = -1479093282,
name_list = {"target"},
type_list = {"ALittle.DisplayObject"},
option_map = {}
})
ALittle.RegStruct(1421505194, "AUIPlugin.AUICodeLineInfo", {
name = "AUIPlugin.AUICodeLineInfo", ns_name = "AUIPlugin", rl_name = "AUICodeLineInfo", hash_code = 1421505194,
name_list = {"char_list","char_count","container","edit"},
type_list = {"List<AUIPlugin.AUICodeCharInfo>","int","AUIPlugin.AUICodeLineContainer","AUIPlugin.AUICodeEdit"},
option_map = {}
})
ALittle.RegStruct(-1073016186, "AUIPlugin.AUICodeFindInfo", {
name = "AUIPlugin.AUICodeFindInfo", ns_name = "AUIPlugin", rl_name = "AUICodeFindInfo", hash_code = -1073016186,
name_list = {"_focus_quad","it_line","it_char_start","it_char_end"},
type_list = {"ALittle.DisplayObject","int","int","int"},
option_map = {}
})
ALittle.RegStruct(-947960184, "lua.ABnfQueryError", {
name = "lua.ABnfQueryError", ns_name = "lua", rl_name = "ABnfQueryError", hash_code = -947960184,
name_list = {"line_start","char_start","line_end","char_end","error"},
type_list = {"int","int","int","int","string"},
option_map = {}
})
ALittle.RegStruct(631224630, "AUIPlugin.AUICodeEditGotoEvent", {
name = "AUIPlugin.AUICodeEditGotoEvent", ns_name = "AUIPlugin", rl_name = "AUICodeEditGotoEvent", hash_code = 631224630,
name_list = {"target","file_path","line_start","char_start","line_end","char_end"},
type_list = {"ALittle.DisplayObject","string","int","int","int","int"},
option_map = {}
})

CODE_LINE_HEIGHT = 18
CODE_LINE_NUMBER_WIDTH = 40
CODE_PAD_LINES = 5
CODE_FONT_SIZE = 14
CODE_FONT_PATH = "YaHei-Consolas.ttf"
CODE_FONT_RED = 169 / 255
CODE_FONT_GREEN = 183 / 255
CODE_FONT_BLUE = 198 / 255
CODE_SELECT_RED = 33 / 255
CODE_SELECT_GREEN = 66 / 255
CODE_SELECT_BLUE = 131 / 255
CODE_FIND_RED = 50 / 255
CODE_FIND_GREEN = 89 / 255
CODE_FIND_BLUE = 61 / 255
CODE_LINE_NUMBER_RED = 100 / 255
CODE_LINE_NUMBER_GREEN = 100 / 255
CODE_LINE_NUMBER_BLUE = 100 / 255
CODE_FOCUS_RED = 88 / 255
CODE_FOCUS_GREEN = 157 / 255
CODE_FOCUS_BLUE = 246 / 255
CODE_DEFAULT_COLOR = {}
CODE_DEFAULT_COLOR.red = CODE_FONT_RED
CODE_DEFAULT_COLOR.green = CODE_FONT_GREEN
CODE_DEFAULT_COLOR.blue = CODE_FONT_BLUE
